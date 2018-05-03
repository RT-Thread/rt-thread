/*!
*******************************************************************************
**
** \file      gh_vo_dve.h
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DVE_PHASE_INC_B0                             FIO_ADDRESS(VO_DVE,0x90008080) /* read/write */
#define REG_VO_DVE_PHASE_INC_B1                             FIO_ADDRESS(VO_DVE,0x90008084) /* read/write */
#define REG_VO_DVE_PHASE_INC_B2                             FIO_ADDRESS(VO_DVE,0x90008088) /* read/write */
#define REG_VO_DVE_PHASE_INC_B3                             FIO_ADDRESS(VO_DVE,0x9000808C) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B0                          FIO_ADDRESS(VO_DVE,0x90008090) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B1                          FIO_ADDRESS(VO_DVE,0x90008094) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B2                          FIO_ADDRESS(VO_DVE,0x90008098) /* read/write */
#define REG_VO_DVE_PHASE_OFFSET_B3                          FIO_ADDRESS(VO_DVE,0x9000809C) /* read/write */
#define REG_VO_DVE_CNFG_F                                   FIO_ADDRESS(VO_DVE,0x900080A0) /* read/write */
#define REG_VO_DVE_BLACK_LVL                                FIO_ADDRESS(VO_DVE,0x900080A8) /* read/write */
#define REG_VO_DVE_BLANK_LVL                                FIO_ADDRESS(VO_DVE,0x900080AC) /* read/write */
#define REG_VO_DVE_CLAMP_LVL                                FIO_ADDRESS(VO_DVE,0x900080B0) /* read/write */
#define REG_VO_DVE_SYNC_LVL                                 FIO_ADDRESS(VO_DVE,0x900080B4) /* read/write */
#define REG_VO_DVE_CNFG_Y                                   FIO_ADDRESS(VO_DVE,0x900080B8) /* read/write */
#define REG_VO_DVE_CNFG_O                                   FIO_ADDRESS(VO_DVE,0x900080BC) /* read/write */
#define REG_VO_DVE_NBA                                      FIO_ADDRESS(VO_DVE,0x900080C8) /* read/write */
#define REG_VO_DVE_PBA                                      FIO_ADDRESS(VO_DVE,0x900080CC) /* read/write */
#define REG_VO_DVE_CNFG_C                                   FIO_ADDRESS(VO_DVE,0x900080D0) /* read/write */
#define REG_VO_DVE_INOUT_MODE                               FIO_ADDRESS(VO_DVE,0x900080E0) /* read/write */
#define REG_VO_DVE_INPUT_SEL                                FIO_ADDRESS(VO_DVE,0x900080E4) /* read/write */
#define REG_VO_DVE_VSYNC_OFF                                FIO_ADDRESS(VO_DVE,0x900080E8) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_H                              FIO_ADDRESS(VO_DVE,0x900080EC) /* read/write */
#define REG_VO_DVE_HSYNC_OFF_L                              FIO_ADDRESS(VO_DVE,0x900080F0) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_H                            FIO_ADDRESS(VO_DVE,0x900080F4) /* read/write */
#define REG_VO_DVE_HLINE_LNGTH_L                            FIO_ADDRESS(VO_DVE,0x900080F8) /* read/write */
#define REG_VO_DVE_CC_DATA_H                                FIO_ADDRESS(VO_DVE,0x90008104) /* read/write */
#define REG_VO_DVE_CC_DATA_L                                FIO_ADDRESS(VO_DVE,0x90008108) /* read/write */
#define REG_VO_DVE_CC_EN                                    FIO_ADDRESS(VO_DVE,0x90008114) /* read/write */
#define REG_VO_DVE_MVP_N0                                   FIO_ADDRESS(VO_DVE,0x90008120) /* read/write */
#define REG_VO_DVE_MVP_N1                                   FIO_ADDRESS(VO_DVE,0x90008124) /* read/write */
#define REG_VO_DVE_MVP_N2                                   FIO_ADDRESS(VO_DVE,0x90008128) /* read/write */
#define REG_VO_DVE_MVP_N3                                   FIO_ADDRESS(VO_DVE,0x9000812C) /* read/write */
#define REG_VO_DVE_MVP_N4                                   FIO_ADDRESS(VO_DVE,0x90008130) /* read/write */
#define REG_VO_DVE_MVP_N567                                 FIO_ADDRESS(VO_DVE,0x90008134) /* read/write */
#define REG_VO_DVE_MVP_N8                                   FIO_ADDRESS(VO_DVE,0x90008138) /* read/write */
#define REG_VO_DVE_MVP_N9                                   FIO_ADDRESS(VO_DVE,0x9000813C) /* read/write */
#define REG_VO_DVE_MVP_N10                                  FIO_ADDRESS(VO_DVE,0x90008140) /* read/write */
#define REG_VO_DVE_MVP_N11_H                                FIO_ADDRESS(VO_DVE,0x90008144) /* read/write */
#define REG_VO_DVE_MVP_N11_L                                FIO_ADDRESS(VO_DVE,0x90008148) /* read/write */
#define REG_VO_DVE_MVP_N12_H                                FIO_ADDRESS(VO_DVE,0x9000814C) /* read/write */
#define REG_VO_DVE_MVP_N12_L                                FIO_ADDRESS(VO_DVE,0x90008150) /* read/write */
#define REG_VO_DVE_MVP_N13                                  FIO_ADDRESS(VO_DVE,0x90008154) /* read/write */
#define REG_VO_DVE_MVP_N14                                  FIO_ADDRESS(VO_DVE,0x90008158) /* read/write */
#define REG_VO_DVE_MVP_N15                                  FIO_ADDRESS(VO_DVE,0x9000815C) /* read/write */
#define REG_VO_DVE_BURST_ZONE_12                            FIO_ADDRESS(VO_DVE,0x90008160) /* read/write */
#define REG_VO_DVE_BURST_ZONE_EN                            FIO_ADDRESS(VO_DVE,0x90008164) /* read/write */
#define REG_VO_DVE_MVP_N21_L                                FIO_ADDRESS(VO_DVE,0x90008168) /* read/write */
#define REG_VO_DVE_MVP_N21_H                                FIO_ADDRESS(VO_DVE,0x9000816C) /* read/write */
#define REG_VO_DVE_TEST_F                                   FIO_ADDRESS(VO_DVE,0x90008180) /* read/write */
#define REG_VO_DVE_TEST_YO                                  FIO_ADDRESS(VO_DVE,0x90008184) /* read/write */
#define REG_VO_DVE_TEST_C                                   FIO_ADDRESS(VO_DVE,0x9000818C) /* read/write */
#define REG_VO_DVE_MACV_TEST                                FIO_ADDRESS(VO_DVE,0x90008190) /* read/write */
#define REG_VO_DVE_HLINE_VRST_H                             FIO_ADDRESS(VO_DVE,0x900081B4) /* read/write */
#define REG_VO_DVE_HLINE_VRST_L                             FIO_ADDRESS(VO_DVE,0x900081B8) /* read/write */
#define REG_VO_DVE_VSM_VRST                                 FIO_ADDRESS(VO_DVE,0x900081BC) /* read/write */
#define REG_VO_DVE_SYNC_START                               FIO_ADDRESS(VO_DVE,0x900081D0) /* read/write */
#define REG_VO_DVE_SYNC_END                                 FIO_ADDRESS(VO_DVE,0x900081D4) /* read/write */
#define REG_VO_DVE_SYNC_SREND                               FIO_ADDRESS(VO_DVE,0x900081D8) /* read/write */
#define REG_VO_DVE_SYNC_EQEND                               FIO_ADDRESS(VO_DVE,0x900081DC) /* read/write */
#define REG_VO_DVE_ACTIVE_START                             FIO_ADDRESS(VO_DVE,0x900081E0) /* read/write */
#define REG_VO_DVE_ACTIVE_END                               FIO_ADDRESS(VO_DVE,0x900081E4) /* read/write */
#define REG_VO_DVE_WBRST_START                              FIO_ADDRESS(VO_DVE,0x900081E8) /* read/write */
#define REG_VO_DVE_NBRST_START                              FIO_ADDRESS(VO_DVE,0x900081EC) /* read/write */
#define REG_VO_DVE_NBRST_END                                FIO_ADDRESS(VO_DVE,0x900081F0) /* read/write */
#define REG_VO_DVE_CLOSED_CAPTION                           FIO_ADDRESS(VO_DVE,0x90008200) /* read */

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
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B0'. */
void GH_VO_DVE_set_PHASE_INC_B0(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B0'. */
U8   GH_VO_DVE_get_PHASE_INC_B0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B1 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B1'. */
void GH_VO_DVE_set_PHASE_INC_B1(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B1'. */
U8   GH_VO_DVE_get_PHASE_INC_B1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B2 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B2'. */
void GH_VO_DVE_set_PHASE_INC_B2(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B2'. */
U8   GH_VO_DVE_get_PHASE_INC_B2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_INC_B3 (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_INC_B3'. */
void GH_VO_DVE_set_PHASE_INC_B3(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_INC_B3'. */
U8   GH_VO_DVE_get_PHASE_INC_B3(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B0 (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B0'. */
void GH_VO_DVE_set_PHASE_OFFSET_B0(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B0'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B1 (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B1'. */
void GH_VO_DVE_set_PHASE_OFFSET_B1(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B1'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B2 (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B2'. */
void GH_VO_DVE_set_PHASE_OFFSET_B2(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B2'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PHASE_OFFSET_B3 (read/write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PHASE_OFFSET_B3'. */
void GH_VO_DVE_set_PHASE_OFFSET_B3(U8 data);
/*! \brief Reads the register 'VO_DVE_PHASE_OFFSET_B3'. */
U8   GH_VO_DVE_get_PHASE_OFFSET_B3(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLACK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_BLACK_LVL'. */
void GH_VO_DVE_set_BLACK_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_BLACK_LVL'. */
U8   GH_VO_DVE_get_BLACK_LVL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BLANK_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_BLANK_LVL'. */
void GH_VO_DVE_set_BLANK_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_BLANK_LVL'. */
U8   GH_VO_DVE_get_BLANK_LVL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLAMP_LVL (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_CLAMP_LVL'. */
void GH_VO_DVE_set_CLAMP_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_CLAMP_LVL'. */
U8   GH_VO_DVE_get_CLAMP_LVL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_LVL (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_SYNC_LVL'. */
void GH_VO_DVE_set_SYNC_LVL(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_LVL'. */
U8   GH_VO_DVE_get_SYNC_LVL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_Y (read/write)                                        */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_O (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_CNFG_O'. */
void GH_VO_DVE_set_CNFG_O(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_O'. */
U8   GH_VO_DVE_get_CNFG_O(void);
/*! \brief Writes the bit group 'Y_TSEL_YUV' of register 'VO_DVE_CNFG_O'. */
void GH_VO_DVE_set_CNFG_O_Y_TSEL_YUV(U8 data);
/*! \brief Reads the bit group 'Y_TSEL_YUV' of register 'VO_DVE_CNFG_O'. */
U8   GH_VO_DVE_get_CNFG_O_Y_TSEL_YUV(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_NBA'. */
void GH_VO_DVE_set_NBA(U32 data);
/*! \brief Reads the register 'VO_DVE_NBA'. */
U32  GH_VO_DVE_get_NBA(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_PBA (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_PBA'. */
void GH_VO_DVE_set_PBA(U32 data);
/*! \brief Reads the register 'VO_DVE_PBA'. */
U32  GH_VO_DVE_get_PBA(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CNFG_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_CNFG_C'. */
void GH_VO_DVE_set_CNFG_C(U8 data);
/*! \brief Reads the register 'VO_DVE_CNFG_C'. */
U8   GH_VO_DVE_get_CNFG_C(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INOUT_MODE (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_INPUT_SEL (read/write)                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSYNC_OFF (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_VSYNC_OFF'. */
void GH_VO_DVE_set_VSYNC_OFF(U8 data);
/*! \brief Reads the register 'VO_DVE_VSYNC_OFF'. */
U8   GH_VO_DVE_get_VSYNC_OFF(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_H (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HSYNC_OFF_H'. */
void GH_VO_DVE_set_HSYNC_OFF_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HSYNC_OFF_H'. */
U8   GH_VO_DVE_get_HSYNC_OFF_H(void);
/*! \brief Writes the bit group 'delay' of register 'VO_DVE_HSYNC_OFF_H'. */
void GH_VO_DVE_set_HSYNC_OFF_H_delay(U8 data);
/*! \brief Reads the bit group 'delay' of register 'VO_DVE_HSYNC_OFF_H'. */
U8   GH_VO_DVE_get_HSYNC_OFF_H_delay(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HSYNC_OFF_L (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HSYNC_OFF_L'. */
void GH_VO_DVE_set_HSYNC_OFF_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HSYNC_OFF_L'. */
U8   GH_VO_DVE_get_HSYNC_OFF_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_H (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HLINE_LNGTH_H'. */
void GH_VO_DVE_set_HLINE_LNGTH_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_LNGTH_H'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_H(void);
/*! \brief Writes the bit group 'HLC' of register 'VO_DVE_HLINE_LNGTH_H'. */
void GH_VO_DVE_set_HLINE_LNGTH_H_HLC(U8 data);
/*! \brief Reads the bit group 'HLC' of register 'VO_DVE_HLINE_LNGTH_H'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_H_HLC(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_LNGTH_L (read/write)                                 */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HLINE_LNGTH_L'. */
void GH_VO_DVE_set_HLINE_LNGTH_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_LNGTH_L'. */
U8   GH_VO_DVE_get_HLINE_LNGTH_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_CC_DATA_H'. */
void GH_VO_DVE_set_CC_DATA_H(U8 index, U8 data);
/*! \brief Reads the register 'VO_DVE_CC_DATA_H'. */
U8   GH_VO_DVE_get_CC_DATA_H(U8 index);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_DATA_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_CC_DATA_L'. */
void GH_VO_DVE_set_CC_DATA_L(U8 index, U8 data);
/*! \brief Reads the register 'VO_DVE_CC_DATA_L'. */
U8   GH_VO_DVE_get_CC_DATA_L(U8 index);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CC_EN (read/write)                                         */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N0 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N0'. */
void GH_VO_DVE_set_MVP_N0(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N0'. */
U8   GH_VO_DVE_get_MVP_N0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N1 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N1'. */
void GH_VO_DVE_set_MVP_N1(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N1'. */
U8   GH_VO_DVE_get_MVP_N1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N2 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N2'. */
void GH_VO_DVE_set_MVP_N2(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N2'. */
U8   GH_VO_DVE_get_MVP_N2(void);
/*! \brief Writes the bit group 'spacing' of register 'VO_DVE_MVP_N2'. */
void GH_VO_DVE_set_MVP_N2_spacing(U8 data);
/*! \brief Reads the bit group 'spacing' of register 'VO_DVE_MVP_N2'. */
U8   GH_VO_DVE_get_MVP_N2_spacing(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N3 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N3'. */
void GH_VO_DVE_set_MVP_N3(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N3'. */
U8   GH_VO_DVE_get_MVP_N3(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N4 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N4'. */
void GH_VO_DVE_set_MVP_N4(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N4'. */
U8   GH_VO_DVE_get_MVP_N4(void);
/*! \brief Writes the bit group 'spacing' of register 'VO_DVE_MVP_N4'. */
void GH_VO_DVE_set_MVP_N4_spacing(U8 data);
/*! \brief Reads the bit group 'spacing' of register 'VO_DVE_MVP_N4'. */
U8   GH_VO_DVE_get_MVP_N4_spacing(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N567 (read/write)                                      */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N8 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N8'. */
void GH_VO_DVE_set_MVP_N8(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N8'. */
U8   GH_VO_DVE_get_MVP_N8(void);
/*! \brief Writes the bit group 'PSD' of register 'VO_DVE_MVP_N8'. */
void GH_VO_DVE_set_MVP_N8_PSD(U8 data);
/*! \brief Reads the bit group 'PSD' of register 'VO_DVE_MVP_N8'. */
U8   GH_VO_DVE_get_MVP_N8_PSD(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N9 (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N9'. */
void GH_VO_DVE_set_MVP_N9(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N9'. */
U8   GH_VO_DVE_get_MVP_N9(void);
/*! \brief Writes the bit group 'PSL' of register 'VO_DVE_MVP_N9'. */
void GH_VO_DVE_set_MVP_N9_PSL(U8 data);
/*! \brief Reads the bit group 'PSL' of register 'VO_DVE_MVP_N9'. */
U8   GH_VO_DVE_get_MVP_N9_PSL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N10 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N10'. */
void GH_VO_DVE_set_MVP_N10(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N10'. */
U8   GH_VO_DVE_get_MVP_N10(void);
/*! \brief Writes the bit group 'PSS' of register 'VO_DVE_MVP_N10'. */
void GH_VO_DVE_set_MVP_N10_PSS(U8 data);
/*! \brief Reads the bit group 'PSS' of register 'VO_DVE_MVP_N10'. */
U8   GH_VO_DVE_get_MVP_N10_PSS(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N11_H'. */
void GH_VO_DVE_set_MVP_N11_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N11_H'. */
U8   GH_VO_DVE_get_MVP_N11_H(void);
/*! \brief Writes the bit group 'sync_line' of register 'VO_DVE_MVP_N11_H'. */
void GH_VO_DVE_set_MVP_N11_H_sync_line(U8 data);
/*! \brief Reads the bit group 'sync_line' of register 'VO_DVE_MVP_N11_H'. */
U8   GH_VO_DVE_get_MVP_N11_H_sync_line(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N11_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N11_L'. */
void GH_VO_DVE_set_MVP_N11_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N11_L'. */
U8   GH_VO_DVE_get_MVP_N11_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N12_H'. */
void GH_VO_DVE_set_MVP_N12_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N12_H'. */
U8   GH_VO_DVE_get_MVP_N12_H(void);
/*! \brief Writes the bit group 'sync_line' of register 'VO_DVE_MVP_N12_H'. */
void GH_VO_DVE_set_MVP_N12_H_sync_line(U8 data);
/*! \brief Reads the bit group 'sync_line' of register 'VO_DVE_MVP_N12_H'. */
U8   GH_VO_DVE_get_MVP_N12_H_sync_line(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N12_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N12_L'. */
void GH_VO_DVE_set_MVP_N12_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N12_L'. */
U8   GH_VO_DVE_get_MVP_N12_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N13 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N13'. */
void GH_VO_DVE_set_MVP_N13(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N13'. */
U8   GH_VO_DVE_get_MVP_N13(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N14 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N14'. */
void GH_VO_DVE_set_MVP_N14(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N14'. */
U8   GH_VO_DVE_get_MVP_N14(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N15 (read/write)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N15'. */
void GH_VO_DVE_set_MVP_N15(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N15'. */
U8   GH_VO_DVE_get_MVP_N15(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_12 (read/write)                                 */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_BURST_ZONE_EN (read/write)                                 */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_L (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N21_L'. */
void GH_VO_DVE_set_MVP_N21_L(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N21_L'. */
U8   GH_VO_DVE_get_MVP_N21_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MVP_N21_H (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MVP_N21_H'. */
void GH_VO_DVE_set_MVP_N21_H(U8 data);
/*! \brief Reads the register 'VO_DVE_MVP_N21_H'. */
U8   GH_VO_DVE_get_MVP_N21_H(void);
/*! \brief Writes the bit group 'invert' of register 'VO_DVE_MVP_N21_H'. */
void GH_VO_DVE_set_MVP_N21_H_invert(U8 data);
/*! \brief Reads the bit group 'invert' of register 'VO_DVE_MVP_N21_H'. */
U8   GH_VO_DVE_get_MVP_N21_H_invert(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_F (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_TEST_F'. */
void GH_VO_DVE_set_TEST_F(U8 data);
/*! \brief Reads the register 'VO_DVE_TEST_F'. */
U8   GH_VO_DVE_get_TEST_F(void);
/*! \brief Writes the bit group 'enable' of register 'VO_DVE_TEST_F'. */
void GH_VO_DVE_set_TEST_F_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VO_DVE_TEST_F'. */
U8   GH_VO_DVE_get_TEST_F_enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_YO (read/write)                                       */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VO_DVE_TEST_C (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_TEST_C'. */
void GH_VO_DVE_set_TEST_C(U8 data);
/*! \brief Reads the register 'VO_DVE_TEST_C'. */
U8   GH_VO_DVE_get_TEST_C(void);
/*! \brief Writes the bit group 'channel' of register 'VO_DVE_TEST_C'. */
void GH_VO_DVE_set_TEST_C_channel(U8 data);
/*! \brief Reads the bit group 'channel' of register 'VO_DVE_TEST_C'. */
U8   GH_VO_DVE_get_TEST_C_channel(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_MACV_TEST (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_MACV_TEST'. */
void GH_VO_DVE_set_MACV_TEST(U8 data);
/*! \brief Reads the register 'VO_DVE_MACV_TEST'. */
U8   GH_VO_DVE_get_MACV_TEST(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_H (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HLINE_VRST_H'. */
void GH_VO_DVE_set_HLINE_VRST_H(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_VRST_H'. */
U8   GH_VO_DVE_get_HLINE_VRST_H(void);
/*! \brief Writes the bit group 'HLR' of register 'VO_DVE_HLINE_VRST_H'. */
void GH_VO_DVE_set_HLINE_VRST_H_HLR(U8 data);
/*! \brief Reads the bit group 'HLR' of register 'VO_DVE_HLINE_VRST_H'. */
U8   GH_VO_DVE_get_HLINE_VRST_H_HLR(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_HLINE_VRST_L (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_HLINE_VRST_L'. */
void GH_VO_DVE_set_HLINE_VRST_L(U8 data);
/*! \brief Reads the register 'VO_DVE_HLINE_VRST_L'. */
U8   GH_VO_DVE_get_HLINE_VRST_L(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_VSM_VRST (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_VSM_VRST'. */
void GH_VO_DVE_set_VSM_VRST(U8 data);
/*! \brief Reads the register 'VO_DVE_VSM_VRST'. */
U8   GH_VO_DVE_get_VSM_VRST(void);
/*! \brief Writes the bit group 'VSMR' of register 'VO_DVE_VSM_VRST'. */
void GH_VO_DVE_set_VSM_VRST_VSMR(U8 data);
/*! \brief Reads the bit group 'VSMR' of register 'VO_DVE_VSM_VRST'. */
U8   GH_VO_DVE_get_VSM_VRST_VSMR(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_START (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_SYNC_START'. */
void GH_VO_DVE_set_SYNC_START(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_START'. */
U8   GH_VO_DVE_get_SYNC_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_SYNC_START'. */
void GH_VO_DVE_set_SYNC_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_SYNC_START'. */
U8   GH_VO_DVE_get_SYNC_START_start(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_END (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_SYNC_END'. */
void GH_VO_DVE_set_SYNC_END(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_END'. */
U8   GH_VO_DVE_get_SYNC_END(void);
/*! \brief Writes the bit group 'end' of register 'VO_DVE_SYNC_END'. */
void GH_VO_DVE_set_SYNC_END_end(U8 data);
/*! \brief Reads the bit group 'end' of register 'VO_DVE_SYNC_END'. */
U8   GH_VO_DVE_get_SYNC_END_end(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_SREND (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_SYNC_SREND'. */
void GH_VO_DVE_set_SYNC_SREND(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_SREND'. */
U8   GH_VO_DVE_get_SYNC_SREND(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_SYNC_EQEND (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_SYNC_EQEND'. */
void GH_VO_DVE_set_SYNC_EQEND(U8 data);
/*! \brief Reads the register 'VO_DVE_SYNC_EQEND'. */
U8   GH_VO_DVE_get_SYNC_EQEND(void);
/*! \brief Writes the bit group 'end' of register 'VO_DVE_SYNC_EQEND'. */
void GH_VO_DVE_set_SYNC_EQEND_end(U8 data);
/*! \brief Reads the bit group 'end' of register 'VO_DVE_SYNC_EQEND'. */
U8   GH_VO_DVE_get_SYNC_EQEND_end(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_START (read/write)                                  */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_ACTIVE_START'. */
void GH_VO_DVE_set_ACTIVE_START(U8 data);
/*! \brief Reads the register 'VO_DVE_ACTIVE_START'. */
U8   GH_VO_DVE_get_ACTIVE_START(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_ACTIVE_END (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_ACTIVE_END'. */
void GH_VO_DVE_set_ACTIVE_END(U8 data);
/*! \brief Reads the register 'VO_DVE_ACTIVE_END'. */
U8   GH_VO_DVE_get_ACTIVE_END(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_WBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_WBRST_START'. */
void GH_VO_DVE_set_WBRST_START(U8 data);
/*! \brief Reads the register 'VO_DVE_WBRST_START'. */
U8   GH_VO_DVE_get_WBRST_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_WBRST_START'. */
void GH_VO_DVE_set_WBRST_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_WBRST_START'. */
U8   GH_VO_DVE_get_WBRST_START_start(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_START (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_NBRST_START'. */
void GH_VO_DVE_set_NBRST_START(U8 data);
/*! \brief Reads the register 'VO_DVE_NBRST_START'. */
U8   GH_VO_DVE_get_NBRST_START(void);
/*! \brief Writes the bit group 'start' of register 'VO_DVE_NBRST_START'. */
void GH_VO_DVE_set_NBRST_START_start(U8 data);
/*! \brief Reads the bit group 'start' of register 'VO_DVE_NBRST_START'. */
U8   GH_VO_DVE_get_NBRST_START_start(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_NBRST_END (read/write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DVE_NBRST_END'. */
void GH_VO_DVE_set_NBRST_END(U8 data);
/*! \brief Reads the register 'VO_DVE_NBRST_END'. */
U8   GH_VO_DVE_get_NBRST_END(void);

/*----------------------------------------------------------------------------*/
/* register VO_DVE_CLOSED_CAPTION (read)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION(void);
/*! \brief Reads the bit group 'EDSTAT' of register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION_EDSTAT(void);
/*! \brief Reads the bit group 'CCSTAT' of register 'VO_DVE_CLOSED_CAPTION'. */
U8   GH_VO_DVE_get_CLOSED_CAPTION_CCSTAT(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DVE_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_dve.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DVE_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

