/*!
*******************************************************************************
**
** \file      gh_vo_dve.h
**
** \brief     Digital Video Effect.
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
#ifndef _GH_VO_DVE_H
#define _GH_VO_DVE_H

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

#define GH_VO_DVE_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_DVE_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_DVE_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_DVE_ENABLE_DEBUG_PRINT
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
#define REG_VO_DVE_PHASE_INC_B0                             FIO_ADDRESS(VO_DVE,0x90004080) /* read/write */
#define REG_VO_DVE_PHASE_INC_B1                             FIO_ADDRESS(VO_DVE,0x90004084) /* read/write */
#define REG_VO_DVE_PHASE_INC_B2                             FIO_ADDRESS(VO_DVE,0x90004088) /* read/write */
#define REG_VO_DVE_PHASE_INC_B3                             FIO_ADDRESS(VO_DVE,0x9000408C) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B0                          FIO_ADDRESS(VO_DVE,0x90004090) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B1                          FIO_ADDRESS(VO_DVE,0x90004094) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B2                          FIO_ADDRESS(VO_DVE,0x90004098) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B3                          FIO_ADDRESS(VO_DVE,0x9000409C) /* read/write */
#define REG_VO_DVE_CNFG_F                                   FIO_ADDRESS(VO_DVE,0x900040A0) /* read/write */
#define REG_VO_DVE_BLACK_LVL                                FIO_ADDRESS(VO_DVE,0x900040A8) /* read/write */
#define REG_VO_DVE_BLANK_LVL                                FIO_ADDRESS(VO_DVE,0x900040AC) /* read/write */
#define REG_VO_DVE_CLAMP_LVL                                FIO_ADDRESS(VO_DVE,0x900040B0) /* read/write */
#define REG_VO_DVE_SYNC_LVL                                 FIO_ADDRESS(VO_DVE,0x900040B4) /* read/write */
#define REG_VO_DVE_CNFG_Y                                   FIO_ADDRESS(VO_DVE,0x900040B8) /* read/write */
#define REG_VO_DVE_CNFG_O                                   FIO_ADDRESS(VO_DVE,0x900040BC) /* read/write */
#define REG_VO_DVE_NBA                                      FIO_ADDRESS(VO_DVE,0x900040C8) /* read/write */
#define REG_VO_DVE_PBA                                      FIO_ADDRESS(VO_DVE,0x900040CC) /* read/write */
#define REG_VO_DVE_CNFG_C                                   FIO_ADDRESS(VO_DVE,0x900040D0) /* read/write */
#define REG_VO_DVE_INOUT_MODE                               FIO_ADDRESS(VO_DVE,0x900040E0) /* read/write */
#define REG_VO_DVE_INPUT_SEL                                FIO_ADDRESS(VO_DVE,0x900040E4) /* read/write */
#define REG_VO_DVE_VSYNC_OFF                                FIO_ADDRESS(VO_DVE,0x900040E8) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_H                              FIO_ADDRESS(VO_DVE,0x900040EC) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_L                              FIO_ADDRESS(VO_DVE,0x900040F0) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_H                            FIO_ADDRESS(VO_DVE,0x900040F4) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_L                            FIO_ADDRESS(VO_DVE,0x900040F8) /* read/write */
#define REG_VO_DVE_CC_DATA_H                                FIO_ADDRESS(VO_DVE,0x90004104) /* read/write */
#define REG_VO_DVE_CC_DATA_L                                FIO_ADDRESS(VO_DVE,0x90004108) /* read/write */
#define REG_VO_DVE_CC_EN                                    FIO_ADDRESS(VO_DVE,0x90004114) /* read/write */
#define REG_VO_DVE_MVP_N0                                   FIO_ADDRESS(VO_DVE,0x90004120) /* read/write */
#define REG_VO_DVE_MVP_N1                                   FIO_ADDRESS(VO_DVE,0x90004124) /* read/write */
#define REG_VO_DVE_MVP_N2                                   FIO_ADDRESS(VO_DVE,0x90004128) /* read/write */
#define REG_VO_DVE_MVP_N3                                   FIO_ADDRESS(VO_DVE,0x9000412C) /* read/write */
#define REG_VO_DVE_MVP_N4                                   FIO_ADDRESS(VO_DVE,0x90004130) /* read/write */
#define REG_VO_DVE_MVP_N567                                 FIO_ADDRESS(VO_DVE,0x90004134) /* read/write */
#define REG_VO_DVE_MVP_N8                                   FIO_ADDRESS(VO_DVE,0x90004138) /* read/write */
#define REG_VO_DVE_MVP_N9                                   FIO_ADDRESS(VO_DVE,0x9000413C) /* read/write */
#define REG_VO_DVE_MVP_N10                                  FIO_ADDRESS(VO_DVE,0x90004140) /* read/write */
#define REG_VO_DVE_MVP_N11_H                                FIO_ADDRESS(VO_DVE,0x90004144) /* read/write */
#define REG_VO_DVE_MVP_N11_L                                FIO_ADDRESS(VO_DVE,0x90004148) /* read/write */
#define REG_VO_DVE_MVP_N12_H                                FIO_ADDRESS(VO_DVE,0x9000414C) /* read/write */
#define REG_VO_DVE_MVP_N12_L                                FIO_ADDRESS(VO_DVE,0x90004150) /* read/write */
#define REG_VO_DVE_MVP_N13                                  FIO_ADDRESS(VO_DVE,0x90004154) /* read/write */
#define REG_VO_DVE_MVP_N14                                  FIO_ADDRESS(VO_DVE,0x90004158) /* read/write */
#define REG_VO_DVE_MVP_N15                                  FIO_ADDRESS(VO_DVE,0x9000415C) /* read/write */
#define REG_VO_DVE_BURST_ZONE_12                            FIO_ADDRESS(VO_DVE,0x90004160) /* read/write */
#define REG_VO_DVE_BURST_ZONE_EN                            FIO_ADDRESS(VO_DVE,0x90004164) /* read/write */
#define REG_VO_DVE_MVP_N21_L                                FIO_ADDRESS(VO_DVE,0x90004168) /* read/write */
#define REG_VO_DVE_MVP_N21_H                                FIO_ADDRESS(VO_DVE,0x9000416C) /* read/write */
#define REG_VO_DVE_TEST_F                                   FIO_ADDRESS(VO_DVE,0x90004180) /* read/write */
#define REG_VO_DVE_TEST_YO                                  FIO_ADDRESS(VO_DVE,0x90004184) /* read/write */
#define REG_VO_DVE_TEST_C                                   FIO_ADDRESS(VO_DVE,0x9000418C) /* read/write */
#define REG_VO_DVE_MACV_TEST                                FIO_ADDRESS(VO_DVE,0x90004190) /* read/write */
#define REG_VO_DVE_HLINE_VRST_H                             FIO_ADDRESS(VO_DVE,0x900041B4) /* read/write */
#define REG_VO_DVE_HLINE_VRST_L                             FIO_ADDRESS(VO_DVE,0x900041B8) /* read/write */
#define REG_VO_DVE_VSM_VRST                                 FIO_ADDRESS(VO_DVE,0x900041BC) /* read/write */
#define REG_VO_DVE_SYNC_START                               FIO_ADDRESS(VO_DVE,0x900041D0) /* read/write */
#define REG_VO_DVE_SYNC_END                                 FIO_ADDRESS(VO_DVE,0x900041D4) /* read/write */
#define REG_VO_DVE_SYNC_SREND                               FIO_ADDRESS(VO_DVE,0x900041D8) /* read/write */
#define REG_VO_DVE_SYNC_EQEND                               FIO_ADDRESS(VO_DVE,0x900041DC) /* read/write */
#define REG_VO_DVE_ACTIVE_START                             FIO_ADDRESS(VO_DVE,0x900041E0) /* read/write */
#define REG_VO_DVE_ACTIVE_END                               FIO_ADDRESS(VO_DVE,0x900041E4) /* read/write */
#define REG_VO_DVE_WBRST_START                              FIO_ADDRESS(VO_DVE,0x900041E8) /* read/write */
#define REG_VO_DVE_NBRST_START                              FIO_ADDRESS(VO_DVE,0x900041EC) /* read/write */
#define REG_VO_DVE_NBRST_END                                FIO_ADDRESS(VO_DVE,0x900041F0) /* read/write */
#define REG_VO_DVE_CLOSED_CAPTION                           FIO_ADDRESS(VO_DVE,0x90004200) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DVE_CNFG_F */
    U8 all;
    struct {
        U8 reset                        : 1;
        U8 config                       : 7;
    } bitc;
} GH_VO_DVE_CNFG_F_S;

typedef union { /* VO_DVE_CNFG_Y */
    U8 all;
    struct {
        U8 gain                         : 1;
        U8 lpf_select                   : 1;
        U8 delay_config                 : 3;
        U8 colorbar_en                  : 1;
        U8 interpolation_mode           : 2;
    } bitc;
} GH_VO_DVE_CNFG_Y_S;

typedef union { /* VO_DVE_CNFG_O */
    U8 all;
    struct {
        U8 y_tsel_yuv                   : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_CNFG_O_S;

typedef union { /* VO_DVE_INOUT_MODE */
    U8 all;
    struct {
        U8 tencd_mode                   : 3;
        U8                              : 1;
        U8 tsync_mode                   : 2;
        U8 vsync                        : 1;
        U8 hsync                        : 1;
    } bitc;
} GH_VO_DVE_INOUT_MODE_S;

typedef union { /* VO_DVE_INPUT_SEL */
    U8 all;
    struct {
        U8 delay                        : 1;
        U8                              : 3;
        U8 t_fsync_phs                  : 1;
        U8 vsync_in                     : 1;
        U8 clk_div                      : 2;
    } bitc;
} GH_VO_DVE_INPUT_SEL_S;

typedef union { /* VO_DVE_HSYNC_OFF_H */
    U8 all;
    struct {
        U8 delay                        : 3;
        U8                              : 5;
    } bitc;
} GH_VO_DVE_HSYNC_OFF_H_S;

typedef union { /* VO_DVE_HLINE_LNGTH_H */
    U8 all;
    struct {
        U8 hlc                          : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_HLINE_LNGTH_H_S;

typedef union { /* VO_DVE_CC_EN */
    U8 all;
    struct {
        U8 odd                          : 1;
        U8 even                         : 1;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_CC_EN_S;

typedef union { /* VO_DVE_MVP_N2 */
    U8 all;
    struct {
        U8 spacing                      : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N2_S;

typedef union { /* VO_DVE_MVP_N4 */
    U8 all;
    struct {
        U8 spacing                      : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N4_S;

typedef union { /* VO_DVE_MVP_N567 */
    U8 all;
    struct {
        U8 csln                         : 2;
        U8 csnum                        : 3;
        U8 cssp                         : 3;
    } bitc;
} GH_VO_DVE_MVP_N567_S;

typedef union { /* VO_DVE_MVP_N8 */
    U8 all;
    struct {
        U8 psd                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N8_S;

typedef union { /* VO_DVE_MVP_N9 */
    U8 all;
    struct {
        U8 psl                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N9_S;

typedef union { /* VO_DVE_MVP_N10 */
    U8 all;
    struct {
        U8 pss                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_MVP_N10_S;

typedef union { /* VO_DVE_MVP_N11_H */
    U8 all;
    struct {
        U8 sync_line                    : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_MVP_N11_H_S;

typedef union { /* VO_DVE_MVP_N12_H */
    U8 all;
    struct {
        U8 sync_line                    : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_MVP_N12_H_S;

typedef union { /* VO_DVE_BURST_ZONE_12 */
    U8 all;
    struct {
        U8 zone2                        : 4;
        U8 zone1                        : 4;
    } bitc;
} GH_VO_DVE_BURST_ZONE_12_S;

typedef union { /* VO_DVE_BURST_ZONE_EN */
    U8 all;
    struct {
        U8 invert                       : 3;
        U8 advanced                     : 1;
        U8 zone3                        : 4;
    } bitc;
} GH_VO_DVE_BURST_ZONE_EN_S;

typedef union { /* VO_DVE_MVP_N21_H */
    U8 all;
    struct {
        U8 invert                       : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_MVP_N21_H_S;

typedef union { /* VO_DVE_TEST_F */
    U8 all;
    struct {
        U8 enable                       : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_TEST_F_S;

typedef union { /* VO_DVE_TEST_YO */
    U8 all;
    struct {
        U8 ou                           : 4;
        U8 yu                           : 4;
    } bitc;
} GH_VO_DVE_TEST_YO_S;

typedef union { /* VO_DVE_TEST_C */
    U8 all;
    struct {
        U8 channel                      : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_TEST_C_S;

typedef union { /* VO_DVE_HLINE_VRST_H */
    U8 all;
    struct {
        U8 hlr                          : 2;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_HLINE_VRST_H_S;

typedef union { /* VO_DVE_VSM_VRST */
    U8 all;
    struct {
        U8 vsmr                         : 5;
        U8                              : 3;
    } bitc;
} GH_VO_DVE_VSM_VRST_S;

typedef union { /* VO_DVE_SYNC_START */
    U8 all;
    struct {
        U8 start                        : 4;
        U8                              : 4;
    } bitc;
} GH_VO_DVE_SYNC_START_S;

typedef union { /* VO_DVE_SYNC_END */
    U8 all;
    struct {
        U8 end                          : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_SYNC_END_S;

typedef union { /* VO_DVE_SYNC_EQEND */
    U8 all;
    struct {
        U8 end                          : 6;
        U8                              : 2;
    } bitc;
} GH_VO_DVE_SYNC_EQEND_S;

typedef union { /* VO_DVE_WBRST_START */
    U8 all;
    struct {
        U8 start                        : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_WBRST_START_S;

typedef union { /* VO_DVE_NBRST_START */
    U8 all;
    struct {
        U8 start                        : 7;
        U8                              : 1;
    } bitc;
} GH_VO_DVE_NBRST_START_S;

typedef union { /* VO_DVE_CLOSED_CAPTION */
    U8 all;
    struct {
        U8 edstat                       : 1;
        U8 ccstat                       : 1;
        U8                              : 6;
    } bitc;
} GH_VO_DVE_CLOSED_CAPTION_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B0 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B0'. */
void GH_VO_DVE_set_PHASE_INC_B0(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B0'. */
U8   GH_VO_DVE_get_PHASE_INC_B0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B0] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B0,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B0] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B1'. */
void GH_VO_DVE_set_PHASE_INC_B1(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B1'. */
U8   GH_VO_DVE_get_PHASE_INC_B1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B1] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B1,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B1] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B2'. */
void GH_VO_DVE_set_PHASE_INC_B2(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B2'. */
U8   GH_VO_DVE_get_PHASE_INC_B2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B2] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B2,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B2] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B3'. */
void GH_VO_DVE_set_PHASE_INC_B3(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B3'. */
U8   GH_VO_DVE_get_PHASE_INC_B3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_INC_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_INC_B3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_INC_B3] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B3,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_INC_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_INC_B3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_INC_B3] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_INC_B3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B0 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B0'. */
void GH_VO_DVE_set_PHASE_OFFSET_B0(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B0'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B0] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B0,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B0] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B1 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B1'. */
void GH_VO_DVE_set_PHASE_OFFSET_B1(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B1'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B1] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B1,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B1] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B2 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B2'. */
void GH_VO_DVE_set_PHASE_OFFSET_B2(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B2'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B2(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B2] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B2,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B2] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B2,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B3 (read/write)                               */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B3'. */
void GH_VO_DVE_set_PHASE_OFFSET_B3(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B3'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PHASE_OFFSET_B3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PHASE_OFFSET_B3] <-- 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B3,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_PHASE_OFFSET_B3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_PHASE_OFFSET_B3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PHASE_OFFSET_B3] --> 0x%08x\n",
                        REG_VO_DVE_PHASE_OFFSET_B3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CNFG_F'. */
void GH_VO_DVE_set_CNFG_F(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_F'. */
U8   GH_VO_DVE_get_CNFG_F(void);
/*! \brief Writes the bit group 'reset' of register 'VO_DVE_CNFG_F'. */
void GH_VO_DVE_set_CNFG_F_reset(U8 data);
/*! \brief Reads the bit group 'reset' of register 'VO_DVE_CNFG_F'. */
U8   GH_VO_DVE_get_CNFG_F_reset(void);
/*! \brief Writes the bit group 'config' of register 'VO_DVE_CNFG_F'. */
void GH_VO_DVE_set_CNFG_F_config(U8 data);
/*! \brief Reads the bit group 'config' of register 'VO_DVE_CNFG_F'. */
U8   GH_VO_DVE_get_CNFG_F_config(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CNFG_F(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_F = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_CNFG_F_reset(U8 data)
{
    GH_VO_DVE_CNFG_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F;
    d.bitc.reset = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F_reset] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F_reset(void)
{
    GH_VO_DVE_CNFG_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F_reset] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return tmp_value.bitc.reset;
}
GH_INLINE void GH_VO_DVE_set_CNFG_F_config(U8 data)
{
    GH_VO_DVE_CNFG_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_F;
    d.bitc.config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_F_config] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_F,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_F_config(void)
{
    GH_VO_DVE_CNFG_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_F_config] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_F,value);
    #endif
    return tmp_value.bitc.config;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLACK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_BLACK_LVL'. */
void GH_VO_DVE_set_BLACK_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_BLACK_LVL'. */
U8   GH_VO_DVE_get_BLACK_LVL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_BLACK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLACK_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BLACK_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_BLACK_LVL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BLACK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLACK_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BLACK_LVL] --> 0x%08x\n",
                        REG_VO_DVE_BLACK_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLANK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_BLANK_LVL'. */
void GH_VO_DVE_set_BLANK_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_BLANK_LVL'. */
U8   GH_VO_DVE_get_BLANK_LVL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_BLANK_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BLANK_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BLANK_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_BLANK_LVL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BLANK_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BLANK_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BLANK_LVL] --> 0x%08x\n",
                        REG_VO_DVE_BLANK_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLAMP_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CLAMP_LVL'. */
void GH_VO_DVE_set_CLAMP_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_CLAMP_LVL'. */
U8   GH_VO_DVE_get_CLAMP_LVL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CLAMP_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CLAMP_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CLAMP_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_CLAMP_LVL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CLAMP_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLAMP_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLAMP_LVL] --> 0x%08x\n",
                        REG_VO_DVE_CLAMP_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_LVL (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_SYNC_LVL'. */
void GH_VO_DVE_set_SYNC_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_LVL'. */
U8   GH_VO_DVE_get_SYNC_LVL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_SYNC_LVL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_LVL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_LVL] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_LVL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_LVL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_LVL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_LVL] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_LVL,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_Y (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y(void);
/*! \brief Writes the bit group 'gain' of register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y_gain(U8 data);
/*! \brief Reads the bit group 'gain' of register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y_gain(void);
/*! \brief Writes the bit group 'LPF_select' of register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y_LPF_select(U8 data);
/*! \brief Reads the bit group 'LPF_select' of register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y_LPF_select(void);
/*! \brief Writes the bit group 'delay_config' of register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y_delay_config(U8 data);
/*! \brief Reads the bit group 'delay_config' of register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y_delay_config(void);
/*! \brief Writes the bit group 'colorbar_en' of register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y_colorbar_en(U8 data);
/*! \brief Reads the bit group 'colorbar_en' of register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y_colorbar_en(void);
/*! \brief Writes the bit group 'interpolation_mode' of register 'VO_DVE_CNFG_Y'. */
void GH_VO_DVE_set_CNFG_Y_interpolation_mode(U8 data);
/*! \brief Reads the bit group 'interpolation_mode' of register 'VO_DVE_CNFG_Y'. */
U8   GH_VO_DVE_get_CNFG_Y_interpolation_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CNFG_Y(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_gain(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.gain = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_gain] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_gain(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_gain] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.gain;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_LPF_select(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.lpf_select = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_LPF_select] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_LPF_select(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_LPF_select] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.lpf_select;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_delay_config(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.delay_config = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_delay_config] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_delay_config(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_delay_config] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.delay_config;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_colorbar_en(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.colorbar_en = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_colorbar_en] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_colorbar_en(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_colorbar_en] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.colorbar_en;
}
GH_INLINE void GH_VO_DVE_set_CNFG_Y_interpolation_mode(U8 data)
{
    GH_VO_DVE_CNFG_Y_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_Y;
    d.bitc.interpolation_mode = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_Y = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_Y_interpolation_mode] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_Y_interpolation_mode(void)
{
    GH_VO_DVE_CNFG_Y_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_Y);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_Y_interpolation_mode] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_Y,value);
    #endif
    return tmp_value.bitc.interpolation_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_O (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CNFG_O'. */
void GH_VO_DVE_set_CNFG_O(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_O'. */
U8   GH_VO_DVE_get_CNFG_O(void);
/*! \brief Writes the bit group 'Y_TSEL_YUV' of register 'VO_DVE_CNFG_O'. */
void GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV(U8 data);
/*! \brief Reads the bit group 'Y_TSEL_YUV' of register 'VO_DVE_CNFG_O'. */
U8   GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CNFG_O(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_O = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_O] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_O,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_O(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_O);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_O] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_O,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV(U8 data)
{
    GH_VO_DVE_CNFG_O_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CNFG_O;
    d.bitc.y_tsel_yuv = data;
    *(volatile U8 *)REG_VO_DVE_CNFG_O = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_O,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV(void)
{
    GH_VO_DVE_CNFG_O_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_O);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_O,value);
    #endif
    return tmp_value.bitc.y_tsel_yuv;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_NBA'. */
void GH_VO_DVE_set_NBA(U32 data);
/*! \brief Reads the register 'VO_DVE_NBA'. */
U32  GH_VO_DVE_get_NBA(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_NBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_NBA = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBA] <-- 0x%08x\n",
                        REG_VO_DVE_NBA,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DVE_get_NBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_NBA);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBA] --> 0x%08x\n",
                        REG_VO_DVE_NBA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_PBA'. */
void GH_VO_DVE_set_PBA(U32 data);
/*! \brief Reads the register 'VO_DVE_PBA'. */
U32  GH_VO_DVE_get_PBA(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_PBA(U32 data)
{
    *(volatile U32 *)REG_VO_DVE_PBA = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_PBA] <-- 0x%08x\n",
                        REG_VO_DVE_PBA,data,data);
    #endif
}
GH_INLINE U32  GH_VO_DVE_get_PBA(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DVE_PBA);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_PBA] --> 0x%08x\n",
                        REG_VO_DVE_PBA,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CNFG_C'. */
void GH_VO_DVE_set_CNFG_C(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_C'. */
U8   GH_VO_DVE_get_CNFG_C(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CNFG_C(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CNFG_C = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CNFG_C] <-- 0x%08x\n",
                        REG_VO_DVE_CNFG_C,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CNFG_C(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CNFG_C);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CNFG_C] --> 0x%08x\n",
                        REG_VO_DVE_CNFG_C,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INOUT_MODE (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_INOUT_MODE'. */
void GH_VO_DVE_set_INOUT_MODE(U8 data);
/*! \brief Reads the register 'VO_DVE_INOUT_MODE'. */
U8   GH_VO_DVE_get_INOUT_MODE(void);
/*! \brief Writes the bit group 'tencd_mode' of register 'VO_DVE_INOUT_MODE'. */
void GH_VO_DVE_set_INOUT_MODE_tencd_mode(U8 data);
/*! \brief Reads the bit group 'tencd_mode' of register 'VO_DVE_INOUT_MODE'. */
U8   GH_VO_DVE_get_INOUT_MODE_tencd_mode(void);
/*! \brief Writes the bit group 'tsync_mode' of register 'VO_DVE_INOUT_MODE'. */
void GH_VO_DVE_set_INOUT_MODE_tsync_mode(U8 data);
/*! \brief Reads the bit group 'tsync_mode' of register 'VO_DVE_INOUT_MODE'. */
U8   GH_VO_DVE_get_INOUT_MODE_tsync_mode(void);
/*! \brief Writes the bit group 'vsync' of register 'VO_DVE_INOUT_MODE'. */
void GH_VO_DVE_set_INOUT_MODE_vsync(U8 data);
/*! \brief Reads the bit group 'vsync' of register 'VO_DVE_INOUT_MODE'. */
U8   GH_VO_DVE_get_INOUT_MODE_vsync(void);
/*! \brief Writes the bit group 'hsync' of register 'VO_DVE_INOUT_MODE'. */
void GH_VO_DVE_set_INOUT_MODE_hsync(U8 data);
/*! \brief Reads the bit group 'hsync' of register 'VO_DVE_INOUT_MODE'. */
U8   GH_VO_DVE_get_INOUT_MODE_hsync(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_INOUT_MODE(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_tencd_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.tencd_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_tencd_mode] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_tencd_mode(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_tencd_mode] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.tencd_mode;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_tsync_mode(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.tsync_mode = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_tsync_mode] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_tsync_mode(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_tsync_mode] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.tsync_mode;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_vsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.vsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_vsync] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_vsync(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_vsync] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.vsync;
}
GH_INLINE void GH_VO_DVE_set_INOUT_MODE_hsync(U8 data)
{
    GH_VO_DVE_INOUT_MODE_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INOUT_MODE;
    d.bitc.hsync = data;
    *(volatile U8 *)REG_VO_DVE_INOUT_MODE = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INOUT_MODE_hsync] <-- 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INOUT_MODE_hsync(void)
{
    GH_VO_DVE_INOUT_MODE_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INOUT_MODE);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INOUT_MODE_hsync] --> 0x%08x\n",
                        REG_VO_DVE_INOUT_MODE,value);
    #endif
    return tmp_value.bitc.hsync;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INPUT_SEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_INPUT_SEL'. */
void GH_VO_DVE_set_INPUT_SEL(U8 data);
/*! \brief Reads the register 'VO_DVE_INPUT_SEL'. */
U8   GH_VO_DVE_get_INPUT_SEL(void);
/*! \brief Writes the bit group 'delay' of register 'VO_DVE_INPUT_SEL'. */
void GH_VO_DVE_set_INPUT_SEL_delay(U8 data);
/*! \brief Reads the bit group 'delay' of register 'VO_DVE_INPUT_SEL'. */
U8   GH_VO_DVE_get_INPUT_SEL_delay(void);
/*! \brief Writes the bit group 'T_FSYNC_PHS' of register 'VO_DVE_INPUT_SEL'. */
void GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS(U8 data);
/*! \brief Reads the bit group 'T_FSYNC_PHS' of register 'VO_DVE_INPUT_SEL'. */
U8   GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS(void);
/*! \brief Writes the bit group 'vsync_in' of register 'VO_DVE_INPUT_SEL'. */
void GH_VO_DVE_set_INPUT_SEL_vsync_in(U8 data);
/*! \brief Reads the bit group 'vsync_in' of register 'VO_DVE_INPUT_SEL'. */
U8   GH_VO_DVE_get_INPUT_SEL_vsync_in(void);
/*! \brief Writes the bit group 'clk_div' of register 'VO_DVE_INPUT_SEL'. */
void GH_VO_DVE_set_INPUT_SEL_clk_div(U8 data);
/*! \brief Reads the bit group 'clk_div' of register 'VO_DVE_INPUT_SEL'. */
U8   GH_VO_DVE_get_INPUT_SEL_clk_div(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_INPUT_SEL(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_delay(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_delay] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_delay(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_delay] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.delay;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.t_fsync_phs = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_T_FSYNC_PHS] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_T_FSYNC_PHS] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.t_fsync_phs;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_vsync_in(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.vsync_in = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_vsync_in] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_vsync_in(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_vsync_in] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.vsync_in;
}
GH_INLINE void GH_VO_DVE_set_INPUT_SEL_clk_div(U8 data)
{
    GH_VO_DVE_INPUT_SEL_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_INPUT_SEL;
    d.bitc.clk_div = data;
    *(volatile U8 *)REG_VO_DVE_INPUT_SEL = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_INPUT_SEL_clk_div] <-- 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_INPUT_SEL_clk_div(void)
{
    GH_VO_DVE_INPUT_SEL_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_INPUT_SEL);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_INPUT_SEL_clk_div] --> 0x%08x\n",
                        REG_VO_DVE_INPUT_SEL,value);
    #endif
    return tmp_value.bitc.clk_div;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSYNC_OFF (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_VSYNC_OFF'. */
void GH_VO_DVE_set_VSYNC_OFF(U8 data);
/*! \brief Reads the register 'VO_DVE_VSYNC_OFF'. */
U8   GH_VO_DVE_get_VSYNC_OFF(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_VSYNC_OFF(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_VSYNC_OFF = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSYNC_OFF] <-- 0x%08x\n",
                        REG_VO_DVE_VSYNC_OFF,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_VSYNC_OFF(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSYNC_OFF);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSYNC_OFF] --> 0x%08x\n",
                        REG_VO_DVE_VSYNC_OFF,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_H (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HSYNC_OFF_H'. */
void GH_VO_DVE_set_HSYNC_OFF_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HSYNC_OFF_H'. */
U8   GH_VO_DVE_get_HSYNC_OFF_H(void);
/*! \brief Writes the bit group 'delay' of register 'VO_DVE_HSYNC_OFF_H'. */
void GH_VO_DVE_set_HSYNC_OFF_H_delay(U8 data);
/*! \brief Reads the bit group 'delay' of register 'VO_DVE_HSYNC_OFF_H'. */
U8   GH_VO_DVE_get_HSYNC_OFF_H_delay(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_H] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_H] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_H_delay(U8 data)
{
    GH_VO_DVE_HSYNC_OFF_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H;
    d.bitc.delay = data;
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_H_delay] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_H_delay(void)
{
    GH_VO_DVE_HSYNC_OFF_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_H_delay] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_H,value);
    #endif
    return tmp_value.bitc.delay;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_L (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HSYNC_OFF_L'. */
void GH_VO_DVE_set_HSYNC_OFF_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HSYNC_OFF_L'. */
U8   GH_VO_DVE_get_HSYNC_OFF_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HSYNC_OFF_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HSYNC_OFF_L] <-- 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HSYNC_OFF_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HSYNC_OFF_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HSYNC_OFF_L] --> 0x%08x\n",
                        REG_VO_DVE_HSYNC_OFF_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_H (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HLINE_LNGTH_H'. */
void GH_VO_DVE_set_HLINE_LNGTH_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_LNGTH_H'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_H(void);
/*! \brief Writes the bit group 'HLC' of register 'VO_DVE_HLINE_LNGTH_H'. */
void GH_VO_DVE_set_HLINE_LNGTH_H_HLC(U8 data);
/*! \brief Reads the bit group 'HLC' of register 'VO_DVE_HLINE_LNGTH_H'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_H_HLC(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_H] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_H] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_H_HLC(U8 data)
{
    GH_VO_DVE_HLINE_LNGTH_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H;
    d.bitc.hlc = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_H_HLC] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_H_HLC(void)
{
    GH_VO_DVE_HLINE_LNGTH_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_H_HLC] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_H,value);
    #endif
    return tmp_value.bitc.hlc;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_L (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HLINE_LNGTH_L'. */
void GH_VO_DVE_set_HLINE_LNGTH_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_LNGTH_L'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HLINE_LNGTH_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_LNGTH_L] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_LNGTH_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_LNGTH_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_LNGTH_L] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_LNGTH_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CC_DATA_H'. */
void GH_VO_DVE_set_CC_DATA_H(U8 index, U8 data);
/*! \brief Reads the register 'VO_DVE_CC_DATA_H'. */
U8   GH_VO_DVE_get_CC_DATA_H(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CC_DATA_H(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_DATA_H] <-- 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CC_DATA_H(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_DATA_H] --> 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_H + index * FIO_MOFFSET(VO_DVE,0x00000008)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CC_DATA_L'. */
void GH_VO_DVE_set_CC_DATA_L(U8 index, U8 data);
/*! \brief Reads the register 'VO_DVE_CC_DATA_L'. */
U8   GH_VO_DVE_get_CC_DATA_L(U8 index);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CC_DATA_L(U8 index, U8 data)
{
    *(volatile U8 *)(REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)) = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_DATA_L] <-- 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)),data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CC_DATA_L(U8 index)
{
    U8 value = (*(volatile U8 *)(REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)));

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_DATA_L] --> 0x%08x\n",
                        (REG_VO_DVE_CC_DATA_L + index * FIO_MOFFSET(VO_DVE,0x00000008)),value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_EN (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_CC_EN'. */
void GH_VO_DVE_set_CC_EN(U8 data);
/*! \brief Reads the register 'VO_DVE_CC_EN'. */
U8   GH_VO_DVE_get_CC_EN(void);
/*! \brief Writes the bit group 'odd' of register 'VO_DVE_CC_EN'. */
void GH_VO_DVE_set_CC_EN_odd(U8 data);
/*! \brief Reads the bit group 'odd' of register 'VO_DVE_CC_EN'. */
U8   GH_VO_DVE_get_CC_EN_odd(void);
/*! \brief Writes the bit group 'even' of register 'VO_DVE_CC_EN'. */
void GH_VO_DVE_set_CC_EN_even(U8 data);
/*! \brief Reads the bit group 'even' of register 'VO_DVE_CC_EN'. */
U8   GH_VO_DVE_get_CC_EN_even(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_CC_EN(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_CC_EN = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_CC_EN_odd(U8 data)
{
    GH_VO_DVE_CC_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN;
    d.bitc.odd = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN_odd] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN_odd(void)
{
    GH_VO_DVE_CC_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN_odd] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return tmp_value.bitc.odd;
}
GH_INLINE void GH_VO_DVE_set_CC_EN_even(U8 data)
{
    GH_VO_DVE_CC_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_CC_EN;
    d.bitc.even = data;
    *(volatile U8 *)REG_VO_DVE_CC_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_CC_EN_even] <-- 0x%08x\n",
                        REG_VO_DVE_CC_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_CC_EN_even(void)
{
    GH_VO_DVE_CC_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CC_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CC_EN_even] --> 0x%08x\n",
                        REG_VO_DVE_CC_EN,value);
    #endif
    return tmp_value.bitc.even;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N0 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N0'. */
void GH_VO_DVE_set_MVP_N0(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N0'. */
U8   GH_VO_DVE_get_MVP_N0(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N0(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N0 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N0] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N0,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N0(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N0);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N0] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N0,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N1 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N1'. */
void GH_VO_DVE_set_MVP_N1(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N1'. */
U8   GH_VO_DVE_get_MVP_N1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N1(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N1 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N1] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N1,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N1(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N1);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N1] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N1,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N2 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N2'. */
void GH_VO_DVE_set_MVP_N2(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N2'. */
U8   GH_VO_DVE_get_MVP_N2(void);
/*! \brief Writes the bit group 'spacing' of register 'VO_DVE_MVP_N2'. */
void GH_VO_DVE_set_MVP_N2_spacing(U8 data);
/*! \brief Reads the bit group 'spacing' of register 'VO_DVE_MVP_N2'. */
U8   GH_VO_DVE_get_MVP_N2_spacing(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N2(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N2 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N2] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N2,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N2(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N2);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N2] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N2,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N2_spacing(U8 data)
{
    GH_VO_DVE_MVP_N2_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N2;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N2 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N2_spacing] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N2,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N2_spacing(void)
{
    GH_VO_DVE_MVP_N2_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N2);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N2_spacing] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N2,value);
    #endif
    return tmp_value.bitc.spacing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N3 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N3'. */
void GH_VO_DVE_set_MVP_N3(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N3'. */
U8   GH_VO_DVE_get_MVP_N3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N3(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N3 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N3] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N3,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N3(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N3);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N3] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N3,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N4 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N4'. */
void GH_VO_DVE_set_MVP_N4(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N4'. */
U8   GH_VO_DVE_get_MVP_N4(void);
/*! \brief Writes the bit group 'spacing' of register 'VO_DVE_MVP_N4'. */
void GH_VO_DVE_set_MVP_N4_spacing(U8 data);
/*! \brief Reads the bit group 'spacing' of register 'VO_DVE_MVP_N4'. */
U8   GH_VO_DVE_get_MVP_N4_spacing(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N4(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N4 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N4] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N4,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N4(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N4);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N4] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N4,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N4_spacing(U8 data)
{
    GH_VO_DVE_MVP_N4_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N4;
    d.bitc.spacing = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N4 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N4_spacing] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N4,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N4_spacing(void)
{
    GH_VO_DVE_MVP_N4_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N4);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N4_spacing] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N4,value);
    #endif
    return tmp_value.bitc.spacing;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N567 (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N567'. */
void GH_VO_DVE_set_MVP_N567(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N567'. */
U8   GH_VO_DVE_get_MVP_N567(void);
/*! \brief Writes the bit group 'CSLN' of register 'VO_DVE_MVP_N567'. */
void GH_VO_DVE_set_MVP_N567_CSLN(U8 data);
/*! \brief Reads the bit group 'CSLN' of register 'VO_DVE_MVP_N567'. */
U8   GH_VO_DVE_get_MVP_N567_CSLN(void);
/*! \brief Writes the bit group 'CSNUM' of register 'VO_DVE_MVP_N567'. */
void GH_VO_DVE_set_MVP_N567_CSNUM(U8 data);
/*! \brief Reads the bit group 'CSNUM' of register 'VO_DVE_MVP_N567'. */
U8   GH_VO_DVE_get_MVP_N567_CSNUM(void);
/*! \brief Writes the bit group 'CSSP' of register 'VO_DVE_MVP_N567'. */
void GH_VO_DVE_set_MVP_N567_CSSP(U8 data);
/*! \brief Reads the bit group 'CSSP' of register 'VO_DVE_MVP_N567'. */
U8   GH_VO_DVE_get_MVP_N567_CSSP(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N567(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSLN(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.csln = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSLN] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSLN(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSLN] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.csln;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSNUM(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.csnum = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSNUM] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSNUM(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSNUM] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.csnum;
}
GH_INLINE void GH_VO_DVE_set_MVP_N567_CSSP(U8 data)
{
    GH_VO_DVE_MVP_N567_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N567;
    d.bitc.cssp = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N567 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N567_CSSP] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N567,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N567_CSSP(void)
{
    GH_VO_DVE_MVP_N567_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N567);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N567_CSSP] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N567,value);
    #endif
    return tmp_value.bitc.cssp;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N8 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N8'. */
void GH_VO_DVE_set_MVP_N8(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N8'. */
U8   GH_VO_DVE_get_MVP_N8(void);
/*! \brief Writes the bit group 'PSD' of register 'VO_DVE_MVP_N8'. */
void GH_VO_DVE_set_MVP_N8_PSD(U8 data);
/*! \brief Reads the bit group 'PSD' of register 'VO_DVE_MVP_N8'. */
U8   GH_VO_DVE_get_MVP_N8_PSD(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N8(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N8 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N8] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N8,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N8(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N8);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N8] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N8,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N8_PSD(U8 data)
{
    GH_VO_DVE_MVP_N8_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N8;
    d.bitc.psd = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N8 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N8_PSD] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N8,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N8_PSD(void)
{
    GH_VO_DVE_MVP_N8_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N8);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N8_PSD] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N8,value);
    #endif
    return tmp_value.bitc.psd;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N9 (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N9'. */
void GH_VO_DVE_set_MVP_N9(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N9'. */
U8   GH_VO_DVE_get_MVP_N9(void);
/*! \brief Writes the bit group 'PSL' of register 'VO_DVE_MVP_N9'. */
void GH_VO_DVE_set_MVP_N9_PSL(U8 data);
/*! \brief Reads the bit group 'PSL' of register 'VO_DVE_MVP_N9'. */
U8   GH_VO_DVE_get_MVP_N9_PSL(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N9(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N9 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N9] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N9,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N9(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N9);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N9] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N9,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N9_PSL(U8 data)
{
    GH_VO_DVE_MVP_N9_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N9;
    d.bitc.psl = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N9 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N9_PSL] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N9,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N9_PSL(void)
{
    GH_VO_DVE_MVP_N9_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N9);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N9_PSL] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N9,value);
    #endif
    return tmp_value.bitc.psl;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N10 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N10'. */
void GH_VO_DVE_set_MVP_N10(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N10'. */
U8   GH_VO_DVE_get_MVP_N10(void);
/*! \brief Writes the bit group 'PSS' of register 'VO_DVE_MVP_N10'. */
void GH_VO_DVE_set_MVP_N10_PSS(U8 data);
/*! \brief Reads the bit group 'PSS' of register 'VO_DVE_MVP_N10'. */
U8   GH_VO_DVE_get_MVP_N10_PSS(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N10(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N10 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N10] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N10,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N10(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N10);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N10] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N10,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N10_PSS(U8 data)
{
    GH_VO_DVE_MVP_N10_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N10;
    d.bitc.pss = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N10 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N10_PSS] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N10,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N10_PSS(void)
{
    GH_VO_DVE_MVP_N10_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N10);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N10_PSS] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N10,value);
    #endif
    return tmp_value.bitc.pss;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N11_H'. */
void GH_VO_DVE_set_MVP_N11_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N11_H'. */
U8   GH_VO_DVE_get_MVP_N11_H(void);
/*! \brief Writes the bit group 'sync_line' of register 'VO_DVE_MVP_N11_H'. */
void GH_VO_DVE_set_MVP_N11_H_sync_line(U8 data);
/*! \brief Reads the bit group 'sync_line' of register 'VO_DVE_MVP_N11_H'. */
U8   GH_VO_DVE_get_MVP_N11_H_sync_line(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N11_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N11_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N11_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N11_H;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N11_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_H_sync_line] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_H_sync_line(void)
{
    GH_VO_DVE_MVP_N11_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_H_sync_line] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_H,value);
    #endif
    return tmp_value.bitc.sync_line;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N11_L'. */
void GH_VO_DVE_set_MVP_N11_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N11_L'. */
U8   GH_VO_DVE_get_MVP_N11_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N11_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N11_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N11_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N11_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N11_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N11_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N11_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N11_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N12_H'. */
void GH_VO_DVE_set_MVP_N12_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N12_H'. */
U8   GH_VO_DVE_get_MVP_N12_H(void);
/*! \brief Writes the bit group 'sync_line' of register 'VO_DVE_MVP_N12_H'. */
void GH_VO_DVE_set_MVP_N12_H_sync_line(U8 data);
/*! \brief Reads the bit group 'sync_line' of register 'VO_DVE_MVP_N12_H'. */
U8   GH_VO_DVE_get_MVP_N12_H_sync_line(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N12_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N12_H_sync_line(U8 data)
{
    GH_VO_DVE_MVP_N12_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N12_H;
    d.bitc.sync_line = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N12_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_H_sync_line] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_H_sync_line(void)
{
    GH_VO_DVE_MVP_N12_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_H_sync_line] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_H,value);
    #endif
    return tmp_value.bitc.sync_line;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N12_L'. */
void GH_VO_DVE_set_MVP_N12_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N12_L'. */
U8   GH_VO_DVE_get_MVP_N12_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N12_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N12_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N12_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N12_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N12_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N12_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N12_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N12_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N13 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N13'. */
void GH_VO_DVE_set_MVP_N13(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N13'. */
U8   GH_VO_DVE_get_MVP_N13(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N13(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N13 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N13] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N13,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N13(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N13);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N13] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N13,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N14 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N14'. */
void GH_VO_DVE_set_MVP_N14(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N14'. */
U8   GH_VO_DVE_get_MVP_N14(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N14(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N14 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N14] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N14,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N14(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N14);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N14] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N14,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N15 (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N15'. */
void GH_VO_DVE_set_MVP_N15(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N15'. */
U8   GH_VO_DVE_get_MVP_N15(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N15(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N15 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N15] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N15,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N15(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N15);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N15] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N15,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_12 (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_BURST_ZONE_12'. */
void GH_VO_DVE_set_BURST_ZONE_12(U8 data);
/*! \brief Reads the register 'VO_DVE_BURST_ZONE_12'. */
U8   GH_VO_DVE_get_BURST_ZONE_12(void);
/*! \brief Writes the bit group 'zone2' of register 'VO_DVE_BURST_ZONE_12'. */
void GH_VO_DVE_set_BURST_ZONE_12_zone2(U8 data);
/*! \brief Reads the bit group 'zone2' of register 'VO_DVE_BURST_ZONE_12'. */
U8   GH_VO_DVE_get_BURST_ZONE_12_zone2(void);
/*! \brief Writes the bit group 'zone1' of register 'VO_DVE_BURST_ZONE_12'. */
void GH_VO_DVE_set_BURST_ZONE_12_zone1(U8 data);
/*! \brief Reads the bit group 'zone1' of register 'VO_DVE_BURST_ZONE_12'. */
U8   GH_VO_DVE_get_BURST_ZONE_12_zone1(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12_zone2(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12;
    d.bitc.zone2 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12_zone2] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12_zone2(void)
{
    GH_VO_DVE_BURST_ZONE_12_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12_zone2] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return tmp_value.bitc.zone2;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_12_zone1(U8 data)
{
    GH_VO_DVE_BURST_ZONE_12_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12;
    d.bitc.zone1 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_12 = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_12_zone1] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_12_zone1(void)
{
    GH_VO_DVE_BURST_ZONE_12_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_12);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_12_zone1] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_12,value);
    #endif
    return tmp_value.bitc.zone1;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_EN (read/write)                                 */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_BURST_ZONE_EN'. */
void GH_VO_DVE_set_BURST_ZONE_EN(U8 data);
/*! \brief Reads the register 'VO_DVE_BURST_ZONE_EN'. */
U8   GH_VO_DVE_get_BURST_ZONE_EN(void);
/*! \brief Writes the bit group 'invert' of register 'VO_DVE_BURST_ZONE_EN'. */
void GH_VO_DVE_set_BURST_ZONE_EN_invert(U8 data);
/*! \brief Reads the bit group 'invert' of register 'VO_DVE_BURST_ZONE_EN'. */
U8   GH_VO_DVE_get_BURST_ZONE_EN_invert(void);
/*! \brief Writes the bit group 'advanced' of register 'VO_DVE_BURST_ZONE_EN'. */
void GH_VO_DVE_set_BURST_ZONE_EN_advanced(U8 data);
/*! \brief Reads the bit group 'advanced' of register 'VO_DVE_BURST_ZONE_EN'. */
U8   GH_VO_DVE_get_BURST_ZONE_EN_advanced(void);
/*! \brief Writes the bit group 'zone3' of register 'VO_DVE_BURST_ZONE_EN'. */
void GH_VO_DVE_set_BURST_ZONE_EN_zone3(U8 data);
/*! \brief Reads the bit group 'zone3' of register 'VO_DVE_BURST_ZONE_EN'. */
U8   GH_VO_DVE_get_BURST_ZONE_EN_zone3(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_invert(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_invert] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_invert(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_invert] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.invert;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_advanced(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.advanced = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_advanced] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_advanced(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_advanced] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.advanced;
}
GH_INLINE void GH_VO_DVE_set_BURST_ZONE_EN_zone3(U8 data)
{
    GH_VO_DVE_BURST_ZONE_EN_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN;
    d.bitc.zone3 = data;
    *(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_BURST_ZONE_EN_zone3] <-- 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_BURST_ZONE_EN_zone3(void)
{
    GH_VO_DVE_BURST_ZONE_EN_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_BURST_ZONE_EN);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_BURST_ZONE_EN_zone3] --> 0x%08x\n",
                        REG_VO_DVE_BURST_ZONE_EN,value);
    #endif
    return tmp_value.bitc.zone3;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N21_L'. */
void GH_VO_DVE_set_MVP_N21_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N21_L'. */
U8   GH_VO_DVE_get_MVP_N21_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N21_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N21_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_L] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_L] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MVP_N21_H'. */
void GH_VO_DVE_set_MVP_N21_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N21_H'. */
U8   GH_VO_DVE_get_MVP_N21_H(void);
/*! \brief Writes the bit group 'invert' of register 'VO_DVE_MVP_N21_H'. */
void GH_VO_DVE_set_MVP_N21_H_invert(U8 data);
/*! \brief Reads the bit group 'invert' of register 'VO_DVE_MVP_N21_H'. */
U8   GH_VO_DVE_get_MVP_N21_H_invert(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MVP_N21_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_H] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_H] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_MVP_N21_H_invert(U8 data)
{
    GH_VO_DVE_MVP_N21_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_MVP_N21_H;
    d.bitc.invert = data;
    *(volatile U8 *)REG_VO_DVE_MVP_N21_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MVP_N21_H_invert] <-- 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MVP_N21_H_invert(void)
{
    GH_VO_DVE_MVP_N21_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_MVP_N21_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MVP_N21_H_invert] --> 0x%08x\n",
                        REG_VO_DVE_MVP_N21_H,value);
    #endif
    return tmp_value.bitc.invert;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_TEST_F'. */
void GH_VO_DVE_set_TEST_F(U8 data);
/*! \brief Reads the register 'VO_DVE_TEST_F'. */
U8   GH_VO_DVE_get_TEST_F(void);
/*! \brief Writes the bit group 'enable' of register 'VO_DVE_TEST_F'. */
void GH_VO_DVE_set_TEST_F_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_DVE_TEST_F'. */
U8   GH_VO_DVE_get_TEST_F_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_TEST_F(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_F = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_F] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_F,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_F(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_F);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_F] --> 0x%08x\n",
                        REG_VO_DVE_TEST_F,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_TEST_F_enable(U8 data)
{
    GH_VO_DVE_TEST_F_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_F;
    d.bitc.enable = data;
    *(volatile U8 *)REG_VO_DVE_TEST_F = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_F_enable] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_F,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_F_enable(void)
{
    GH_VO_DVE_TEST_F_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_F);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_F_enable] --> 0x%08x\n",
                        REG_VO_DVE_TEST_F,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_YO (read/write)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_TEST_YO'. */
void GH_VO_DVE_set_TEST_YO(U8 data);
/*! \brief Reads the register 'VO_DVE_TEST_YO'. */
U8   GH_VO_DVE_get_TEST_YO(void);
/*! \brief Writes the bit group 'ou' of register 'VO_DVE_TEST_YO'. */
void GH_VO_DVE_set_TEST_YO_ou(U8 data);
/*! \brief Reads the bit group 'ou' of register 'VO_DVE_TEST_YO'. */
U8   GH_VO_DVE_get_TEST_YO_ou(void);
/*! \brief Writes the bit group 'yu' of register 'VO_DVE_TEST_YO'. */
void GH_VO_DVE_set_TEST_YO_yu(U8 data);
/*! \brief Reads the bit group 'yu' of register 'VO_DVE_TEST_YO'. */
U8   GH_VO_DVE_get_TEST_YO_yu(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_TEST_YO(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_YO = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_TEST_YO_ou(U8 data)
{
    GH_VO_DVE_TEST_YO_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO;
    d.bitc.ou = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO_ou] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO_ou(void)
{
    GH_VO_DVE_TEST_YO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO_ou] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return tmp_value.bitc.ou;
}
GH_INLINE void GH_VO_DVE_set_TEST_YO_yu(U8 data)
{
    GH_VO_DVE_TEST_YO_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_YO;
    d.bitc.yu = data;
    *(volatile U8 *)REG_VO_DVE_TEST_YO = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_YO_yu] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_YO,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_YO_yu(void)
{
    GH_VO_DVE_TEST_YO_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_YO);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_YO_yu] --> 0x%08x\n",
                        REG_VO_DVE_TEST_YO,value);
    #endif
    return tmp_value.bitc.yu;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_TEST_C'. */
void GH_VO_DVE_set_TEST_C(U8 data);
/*! \brief Reads the register 'VO_DVE_TEST_C'. */
U8   GH_VO_DVE_get_TEST_C(void);
/*! \brief Writes the bit group 'channel' of register 'VO_DVE_TEST_C'. */
void GH_VO_DVE_set_TEST_C_channel(U8 data);
/*! \brief Reads the bit group 'channel' of register 'VO_DVE_TEST_C'. */
U8   GH_VO_DVE_get_TEST_C_channel(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_TEST_C(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_TEST_C = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_C] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_C,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_C(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_C);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_C] --> 0x%08x\n",
                        REG_VO_DVE_TEST_C,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_TEST_C_channel(U8 data)
{
    GH_VO_DVE_TEST_C_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_TEST_C;
    d.bitc.channel = data;
    *(volatile U8 *)REG_VO_DVE_TEST_C = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_TEST_C_channel] <-- 0x%08x\n",
                        REG_VO_DVE_TEST_C,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_TEST_C_channel(void)
{
    GH_VO_DVE_TEST_C_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_TEST_C);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_TEST_C_channel] --> 0x%08x\n",
                        REG_VO_DVE_TEST_C,value);
    #endif
    return tmp_value.bitc.channel;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MACV_TEST (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_MACV_TEST'. */
void GH_VO_DVE_set_MACV_TEST(U8 data);
/*! \brief Reads the register 'VO_DVE_MACV_TEST'. */
U8   GH_VO_DVE_get_MACV_TEST(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_MACV_TEST(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_MACV_TEST = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_MACV_TEST] <-- 0x%08x\n",
                        REG_VO_DVE_MACV_TEST,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_MACV_TEST(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_MACV_TEST);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_MACV_TEST] --> 0x%08x\n",
                        REG_VO_DVE_MACV_TEST,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_H (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HLINE_VRST_H'. */
void GH_VO_DVE_set_HLINE_VRST_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_VRST_H'. */
U8   GH_VO_DVE_get_HLINE_VRST_H(void);
/*! \brief Writes the bit group 'HLR' of register 'VO_DVE_HLINE_VRST_H'. */
void GH_VO_DVE_set_HLINE_VRST_H_HLR(U8 data);
/*! \brief Reads the bit group 'HLR' of register 'VO_DVE_HLINE_VRST_H'. */
U8   GH_VO_DVE_get_HLINE_VRST_H_HLR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_H(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_H] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_H(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_H] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_H_HLR(U8 data)
{
    GH_VO_DVE_HLINE_VRST_H_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H;
    d.bitc.hlr = data;
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_H = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_H_HLR] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_H_HLR(void)
{
    GH_VO_DVE_HLINE_VRST_H_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_H);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_H_HLR] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_H,value);
    #endif
    return tmp_value.bitc.hlr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_L (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_HLINE_VRST_L'. */
void GH_VO_DVE_set_HLINE_VRST_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_VRST_L'. */
U8   GH_VO_DVE_get_HLINE_VRST_L(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_HLINE_VRST_L(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_HLINE_VRST_L = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_HLINE_VRST_L] <-- 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_L,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_HLINE_VRST_L(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_HLINE_VRST_L);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_HLINE_VRST_L] --> 0x%08x\n",
                        REG_VO_DVE_HLINE_VRST_L,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSM_VRST (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_VSM_VRST'. */
void GH_VO_DVE_set_VSM_VRST(U8 data);
/*! \brief Reads the register 'VO_DVE_VSM_VRST'. */
U8   GH_VO_DVE_get_VSM_VRST(void);
/*! \brief Writes the bit group 'VSMR' of register 'VO_DVE_VSM_VRST'. */
void GH_VO_DVE_set_VSM_VRST_VSMR(U8 data);
/*! \brief Reads the bit group 'VSMR' of register 'VO_DVE_VSM_VRST'. */
U8   GH_VO_DVE_get_VSM_VRST_VSMR(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_VSM_VRST(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_VSM_VRST = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSM_VRST] <-- 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_VSM_VRST(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSM_VRST);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSM_VRST] --> 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_VSM_VRST_VSMR(U8 data)
{
    GH_VO_DVE_VSM_VRST_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_VSM_VRST;
    d.bitc.vsmr = data;
    *(volatile U8 *)REG_VO_DVE_VSM_VRST = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_VSM_VRST_VSMR] <-- 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_VSM_VRST_VSMR(void)
{
    GH_VO_DVE_VSM_VRST_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_VSM_VRST);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_VSM_VRST_VSMR] --> 0x%08x\n",
                        REG_VO_DVE_VSM_VRST,value);
    #endif
    return tmp_value.bitc.vsmr;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_START (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_SYNC_START'. */
void GH_VO_DVE_set_SYNC_START(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_START'. */
U8   GH_VO_DVE_get_SYNC_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_SYNC_START'. */
void GH_VO_DVE_set_SYNC_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_SYNC_START'. */
U8   GH_VO_DVE_get_SYNC_START_start(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_SYNC_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_START] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_START,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_START] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_SYNC_START_start(U8 data)
{
    GH_VO_DVE_SYNC_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_START_start(void)
{
    GH_VO_DVE_SYNC_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_START_start] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_END (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_SYNC_END'. */
void GH_VO_DVE_set_SYNC_END(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_END'. */
U8   GH_VO_DVE_get_SYNC_END(void);
/*! \brief Writes the bit group 'end' of register 'VO_DVE_SYNC_END'. */
void GH_VO_DVE_set_SYNC_END_end(U8 data);
/*! \brief Reads the bit group 'end' of register 'VO_DVE_SYNC_END'. */
U8   GH_VO_DVE_get_SYNC_END_end(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_SYNC_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_END] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_END,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_END] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_END,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_SYNC_END_end(U8 data)
{
    GH_VO_DVE_SYNC_END_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_END;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_END = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_END_end] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_END,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_END_end(void)
{
    GH_VO_DVE_SYNC_END_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_END);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_END_end] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_END,value);
    #endif
    return tmp_value.bitc.end;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_SREND (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_SYNC_SREND'. */
void GH_VO_DVE_set_SYNC_SREND(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_SREND'. */
U8   GH_VO_DVE_get_SYNC_SREND(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_SYNC_SREND(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_SREND = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_SREND] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_SREND,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_SREND(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_SREND);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_SREND] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_SREND,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_EQEND (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_SYNC_EQEND'. */
void GH_VO_DVE_set_SYNC_EQEND(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_EQEND'. */
U8   GH_VO_DVE_get_SYNC_EQEND(void);
/*! \brief Writes the bit group 'end' of register 'VO_DVE_SYNC_EQEND'. */
void GH_VO_DVE_set_SYNC_EQEND_end(U8 data);
/*! \brief Reads the bit group 'end' of register 'VO_DVE_SYNC_EQEND'. */
U8   GH_VO_DVE_get_SYNC_EQEND_end(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_SYNC_EQEND(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_EQEND] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_EQEND(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_EQEND] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_SYNC_EQEND_end(U8 data)
{
    GH_VO_DVE_SYNC_EQEND_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_SYNC_EQEND;
    d.bitc.end = data;
    *(volatile U8 *)REG_VO_DVE_SYNC_EQEND = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_SYNC_EQEND_end] <-- 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_SYNC_EQEND_end(void)
{
    GH_VO_DVE_SYNC_EQEND_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_SYNC_EQEND);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_SYNC_EQEND_end] --> 0x%08x\n",
                        REG_VO_DVE_SYNC_EQEND,value);
    #endif
    return tmp_value.bitc.end;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_ACTIVE_START'. */
void GH_VO_DVE_set_ACTIVE_START(U8 data);
/*! \brief Reads the register 'VO_DVE_ACTIVE_START'. */
U8   GH_VO_DVE_get_ACTIVE_START(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_ACTIVE_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_ACTIVE_START] <-- 0x%08x\n",
                        REG_VO_DVE_ACTIVE_START,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_ACTIVE_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_ACTIVE_START] --> 0x%08x\n",
                        REG_VO_DVE_ACTIVE_START,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_ACTIVE_END'. */
void GH_VO_DVE_set_ACTIVE_END(U8 data);
/*! \brief Reads the register 'VO_DVE_ACTIVE_END'. */
U8   GH_VO_DVE_get_ACTIVE_END(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_ACTIVE_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_ACTIVE_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_ACTIVE_END] <-- 0x%08x\n",
                        REG_VO_DVE_ACTIVE_END,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_ACTIVE_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_ACTIVE_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_ACTIVE_END] --> 0x%08x\n",
                        REG_VO_DVE_ACTIVE_END,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_WBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_WBRST_START'. */
void GH_VO_DVE_set_WBRST_START(U8 data);
/*! \brief Reads the register 'VO_DVE_WBRST_START'. */
U8   GH_VO_DVE_get_WBRST_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_WBRST_START'. */
void GH_VO_DVE_set_WBRST_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_WBRST_START'. */
U8   GH_VO_DVE_get_WBRST_START_start(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_WBRST_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_WBRST_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_WBRST_START] <-- 0x%08x\n",
                        REG_VO_DVE_WBRST_START,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_WBRST_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_WBRST_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_WBRST_START] --> 0x%08x\n",
                        REG_VO_DVE_WBRST_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_WBRST_START_start(U8 data)
{
    GH_VO_DVE_WBRST_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_WBRST_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_WBRST_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_WBRST_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_WBRST_START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_WBRST_START_start(void)
{
    GH_VO_DVE_WBRST_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_WBRST_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_WBRST_START_start] --> 0x%08x\n",
                        REG_VO_DVE_WBRST_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_NBRST_START'. */
void GH_VO_DVE_set_NBRST_START(U8 data);
/*! \brief Reads the register 'VO_DVE_NBRST_START'. */
U8   GH_VO_DVE_get_NBRST_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_NBRST_START'. */
void GH_VO_DVE_set_NBRST_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_NBRST_START'. */
U8   GH_VO_DVE_get_NBRST_START_start(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_NBRST_START(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_NBRST_START = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_START] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_START,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_START(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_START);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_START] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_START,value);
    #endif
    return value;
}
GH_INLINE void GH_VO_DVE_set_NBRST_START_start(U8 data)
{
    GH_VO_DVE_NBRST_START_S d;
    d.all = *(volatile U8 *)REG_VO_DVE_NBRST_START;
    d.bitc.start = data;
    *(volatile U8 *)REG_VO_DVE_NBRST_START = d.all;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_START_start] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_START_start(void)
{
    GH_VO_DVE_NBRST_START_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_START);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_START_start] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_START,value);
    #endif
    return tmp_value.bitc.start;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VO_DVE_NBRST_END'. */
void GH_VO_DVE_set_NBRST_END(U8 data);
/*! \brief Reads the register 'VO_DVE_NBRST_END'. */
U8   GH_VO_DVE_get_NBRST_END(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VO_DVE_set_NBRST_END(U8 data)
{
    *(volatile U8 *)REG_VO_DVE_NBRST_END = data;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VO_DVE_set_NBRST_END] <-- 0x%08x\n",
                        REG_VO_DVE_NBRST_END,data,data);
    #endif
}
GH_INLINE U8   GH_VO_DVE_get_NBRST_END(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_NBRST_END);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_NBRST_END] --> 0x%08x\n",
                        REG_VO_DVE_NBRST_END,value);
    #endif
    return value;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLOSED_CAPTION (read)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION(void);
/*! \brief Reads the bit group 'EDSTAT' of register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT(void);
/*! \brief Reads the bit group 'CCSTAT' of register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION(void)
{
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return value;
}
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return tmp_value.bitc.edstat;
}
GH_INLINE U8   GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT(void)
{
    GH_VO_DVE_CLOSED_CAPTION_S tmp_value;
    U8 value = (*(volatile U8 *)REG_VO_DVE_CLOSED_CAPTION);

    tmp_value.all = value;
    #if GH_VO_DVE_ENABLE_DEBUG_PRINT
    GH_VO_DVE_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT] --> 0x%08x\n",
                        REG_VO_DVE_CLOSED_CAPTION,value);
    #endif
    return tmp_value.bitc.ccstat;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DVE_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DVE_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

