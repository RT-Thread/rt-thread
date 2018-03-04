/*!
*******************************************************************************
**
** \file      gh_vin.h
**
** \brief     Video/Sensor Input.
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
#ifndef _GH_VIN_H
#define _GH_VIN_H

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

#define GH_VIN_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VIN_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VIN_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VIN_ENABLE_DEBUG_PRINT
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
#define REG_VIN_S_CONTROL                                   FIO_ADDRESS(VIN,0x60009000) /* read/write */
#define REG_VIN_S_INPUTCONFIG                               FIO_ADDRESS(VIN,0x60009004) /* read/write */
#define REG_VIN_S_STATUS                                    FIO_ADDRESS(VIN,0x60009008) /* read/write */
#define REG_VIN_S_VWIDTH                                    FIO_ADDRESS(VIN,0x6000900C) /* read/write */
#define REG_VIN_S_HWIDTH                                    FIO_ADDRESS(VIN,0x60009010) /* read/write */
#define REG_VIN_S_HTOP                                      FIO_ADDRESS(VIN,0x60009014) /* read/write */
#define REG_VIN_S_HBOTTOM                                   FIO_ADDRESS(VIN,0x60009018) /* read/write */
#define REG_VIN_S_V                                         FIO_ADDRESS(VIN,0x6000901C) /* read/write */
#define REG_VIN_S_H                                         FIO_ADDRESS(VIN,0x60009020) /* read/write */
#define REG_VIN_S_MINV                                      FIO_ADDRESS(VIN,0x60009024) /* read/write */
#define REG_VIN_S_MINH                                      FIO_ADDRESS(VIN,0x60009028) /* read/write */
#define REG_VIN_S_TRIGGER0START                             FIO_ADDRESS(VIN,0x6000902C) /* read/write */
#define REG_VIN_S_TRIGGER0END                               FIO_ADDRESS(VIN,0x60009030) /* read/write */
#define REG_VIN_S_TRIGGER1START                             FIO_ADDRESS(VIN,0x60009034) /* read/write */
#define REG_VIN_S_TRIGGER1END                               FIO_ADDRESS(VIN,0x60009038) /* read/write */
#define REG_VIN_S_VOUTSTART0                                FIO_ADDRESS(VIN,0x6000903C) /* read/write */
#define REG_VIN_S_VOUTSTART1                                FIO_ADDRESS(VIN,0x60009040) /* read/write */
#define REG_VIN_S_CAPSTARTV                                 FIO_ADDRESS(VIN,0x60009044) /* read/write */
#define REG_VIN_S_CAPSTARTH                                 FIO_ADDRESS(VIN,0x60009048) /* read/write */
#define REG_VIN_S_CAPENDV                                   FIO_ADDRESS(VIN,0x6000904C) /* read/write */
#define REG_VIN_S_CAPENDH                                   FIO_ADDRESS(VIN,0x60009050) /* read/write */
#define REG_VIN_S_BLANKLENGTHH                              FIO_ADDRESS(VIN,0x60009054) /* read/write */
#define REG_VIN_S_TIMEOUTVLOW                               FIO_ADDRESS(VIN,0x60009058) /* read/write */
#define REG_VIN_S_TIMEOUTVHIGH                              FIO_ADDRESS(VIN,0x6000905C) /* read/write */
#define REG_VIN_S_TIMEOUTHLOW                               FIO_ADDRESS(VIN,0x60009060) /* read/write */
#define REG_VIN_S_TIMEOUTHHIGH                              FIO_ADDRESS(VIN,0x60009064) /* read/write */
#define REG_VIN_S_DEBUGFIFOCOUNT                            FIO_ADDRESS(VIN,0x60009080) /* read */
#define REG_VIN_S_DEBUGFIFODATA0                            FIO_ADDRESS(VIN,0x60009084) /* read */
#define REG_VIN_S_DEBUGFIFODATA1                            FIO_ADDRESS(VIN,0x60009088) /* read */
#define REG_VIN_S_DEBUGSTALL                                FIO_ADDRESS(VIN,0x6000908C) /* read */
#define REG_VIN_S_SLVSSATUS                                 FIO_ADDRESS(VIN,0x60009090) /* read */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VIN_S_Control */
    U32 all;
    struct {
        U32                             : 1;
        U32 enable                      : 1;
        U32 win_en                      : 1;
        U32 data_edge                   : 1;
        U32 slave_mode_enable           : 1;
        U32 master_mode_enable          : 1;
        U32 emb_sync                    : 1;
        U32 emb_sync_mode               : 1;
        U32 emb_sync_loc                : 2;
        U32 vs_pol                      : 1;
        U32 hs_pol                      : 1;
        U32 field0_pol                  : 1;
        U32 sony_field_mode             : 1;
        U32 ecc_enable                  : 1;
        U32 hsync_mask                  : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_CONTROL_S;

typedef union { /* VIN_S_InputConfig */
    U32 all;
    struct {
        U32 pad_type                    : 1;
        U32 data_rate                   : 1;
        U32 data_width                  : 1;
        U32 input_source                : 1;
        U32 rgb_yuv                     : 1;
        U32 pixel_data_width            : 2;
        U32 yuv_input_order             : 2;
        U32 slvs_num_lanes              : 2;
        U32 serial_sensor_interface_mode: 1;
        U32                             : 20;
    } bitc;
} GH_VIN_S_INPUTCONFIG_S;

typedef union { /* VIN_S_Status */
    U32 all;
    struct {
        U32 vsync                       : 1;
        U32 trig0                       : 1;
        U32 trig1                       : 1;
        U32 ovfl                        : 1;
        U32 shortl                      : 1;
        U32 shortf                      : 1;
        U32 field                       : 3;
        U32 no_hsync_detected           : 1;
        U32 no_vsync_detected           : 1;
        U32 idsp_ahb_vsync              : 1;
        U32 idsp_ahb_mst_vsync          : 1;
        U32 idsp_ahb_last_pixel         : 1;
        U32 ecc_uncorrectable           : 1;
        U32 program_error               : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_STATUS_S;

typedef union { /* VIN_S_Vwidth */
    U32 all;
    struct {
        U32 vsync_width                 : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_VWIDTH_S;

typedef union { /* VIN_S_Hwidth */
    U32 all;
    struct {
        U32 hsync_width                 : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HWIDTH_S;

typedef union { /* VIN_S_Htop */
    U32 all;
    struct {
        U32 hsync_top                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HTOP_S;

typedef union { /* VIN_S_Hbottom */
    U32 all;
    struct {
        U32 hsync_bottom                : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HBOTTOM_S;

typedef union { /* VIN_S_V */
    U32 all;
    struct {
        U32 num_lines                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_V_S;

typedef union { /* VIN_S_H */
    U32 all;
    struct {
        U32 num_cols                    : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_H_S;

typedef union { /* VIN_S_MinV */
    U32 all;
    struct {
        U32 min_num_lines               : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_MINV_S;

typedef union { /* VIN_S_MinH */
    U32 all;
    struct {
        U32 min_num_fields              : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_MINH_S;

typedef union { /* VIN_S_Trigger0Start */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32 pol                         : 1;
        U32 enable                      : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TRIGGER0START_S;

typedef union { /* VIN_S_Trigger0End */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_TRIGGER0END_S;

typedef union { /* VIN_S_Trigger1Start */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32 pol                         : 1;
        U32 enable                      : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TRIGGER1START_S;

typedef union { /* VIN_S_Trigger1End */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_TRIGGER1END_S;

typedef union { /* VIN_S_VoutStart0 */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 1;
        U32 disable_field_check         : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_VOUTSTART0_S;

typedef union { /* VIN_S_VoutStart1 */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 1;
        U32 disable_field_check         : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_VOUTSTART1_S;

typedef union { /* VIN_S_CapStartV */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPSTARTV_S;

typedef union { /* VIN_S_CapStartH */
    U32 all;
    struct {
        U32 startcol                    : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPSTARTH_S;

typedef union { /* VIN_S_CapEndV */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPENDV_S;

typedef union { /* VIN_S_CapEndH */
    U32 all;
    struct {
        U32 endcol                      : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPENDH_S;

typedef union { /* VIN_S_BlankLengthH */
    U32 all;
    struct {
        U32 blank_length                : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_BLANKLENGTHH_S;

typedef union { /* VIN_S_TimeoutVLow */
    U32 all;
    struct {
        U32 vsync_timeout_low           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTVLOW_S;

typedef union { /* VIN_S_TimeoutVHigh */
    U32 all;
    struct {
        U32 vsync_timeout_high          : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTVHIGH_S;

typedef union { /* VIN_S_TimeoutHLow */
    U32 all;
    struct {
        U32 hsync_timeout_low           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTHLOW_S;

typedef union { /* VIN_S_TimeoutHHigh */
    U32 all;
    struct {
        U32 hsync_timeout_high          : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTHHIGH_S;

typedef union { /* VIN_S_debugFifoCount */
    U32 all;
    struct {
        U32 num_words_in_fifo           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFOCOUNT_S;

typedef union { /* VIN_S_debugFifoData0 */
    U32 all;
    struct {
        U32 pixel_0_read_data           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFODATA0_S;

typedef union { /* VIN_S_debugFifoData1 */
    U32 all;
    struct {
        U32 pixel_1_read_data           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFODATA1_S;

typedef union { /* VIN_S_debugStall */
    U32 all;
    struct {
        U32 output_interface_stall      : 1;
        U32                             : 31;
    } bitc;
} GH_VIN_S_DEBUGSTALL_S;

typedef union { /* VIN_S_slvsSatus */
    U32 all;
    struct {
        U32 slvs_lock_state             : 1;
        U32 detected_sync_code_match    : 1;
        U32 detected_start_of_frame     : 1;
        U32 detected_vsync              : 1;
        U32 detected_start_of_line      : 1;
        U32 valid_pixel_generated       : 1;
        U32 end_of_line_generated       : 1;
        U32 corrected_error             : 1;
        U32                             : 24;
    } bitc;
} GH_VIN_S_SLVSSATUS_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VIN_S_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Control'. */
void GH_VIN_set_S_Control(U32 data);
/*! \brief Reads the register 'VIN_S_Control'. */
U32  GH_VIN_get_S_Control(void);
/*! \brief Writes the bit group 'enable' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_enable(void);
/*! \brief Writes the bit group 'win_en' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_win_en(U8 data);
/*! \brief Reads the bit group 'win_en' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_win_en(void);
/*! \brief Writes the bit group 'data_edge' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_data_edge(U8 data);
/*! \brief Reads the bit group 'data_edge' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_data_edge(void);
/*! \brief Writes the bit group 'slave_mode_enable' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_slave_mode_enable(U8 data);
/*! \brief Reads the bit group 'slave_mode_enable' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_slave_mode_enable(void);
/*! \brief Writes the bit group 'master_mode_enable' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_master_mode_enable(U8 data);
/*! \brief Reads the bit group 'master_mode_enable' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_master_mode_enable(void);
/*! \brief Writes the bit group 'emb_sync' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_emb_sync(U8 data);
/*! \brief Reads the bit group 'emb_sync' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_emb_sync(void);
/*! \brief Writes the bit group 'emb_sync_mode' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_emb_sync_mode(U8 data);
/*! \brief Reads the bit group 'emb_sync_mode' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_emb_sync_mode(void);
/*! \brief Writes the bit group 'emb_sync_loc' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_emb_sync_loc(U8 data);
/*! \brief Reads the bit group 'emb_sync_loc' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_emb_sync_loc(void);
/*! \brief Writes the bit group 'vs_pol' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_vs_pol(U8 data);
/*! \brief Reads the bit group 'vs_pol' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_vs_pol(void);
/*! \brief Writes the bit group 'hs_pol' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_hs_pol(U8 data);
/*! \brief Reads the bit group 'hs_pol' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_hs_pol(void);
/*! \brief Writes the bit group 'field0_pol' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_field0_pol(U8 data);
/*! \brief Reads the bit group 'field0_pol' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_field0_pol(void);
/*! \brief Writes the bit group 'sony_field_mode' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_sony_field_mode(U8 data);
/*! \brief Reads the bit group 'sony_field_mode' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_sony_field_mode(void);
/*! \brief Writes the bit group 'ecc_enable' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_ecc_enable(U8 data);
/*! \brief Reads the bit group 'ecc_enable' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_ecc_enable(void);
/*! \brief Writes the bit group 'hsync_mask' of register 'VIN_S_Control'. */
void GH_VIN_set_S_Control_hsync_mask(U8 data);
/*! \brief Reads the bit group 'hsync_mask' of register 'VIN_S_Control'. */
U8   GH_VIN_get_S_Control_hsync_mask(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Control(U32 data)
{
    *(volatile U32 *)REG_VIN_S_CONTROL = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Control(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Control_enable(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_enable] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_enable(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_enable] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_VIN_set_S_Control_win_en(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.win_en = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_win_en] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_win_en(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_win_en] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.win_en;
}
GH_INLINE void GH_VIN_set_S_Control_data_edge(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.data_edge = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_data_edge] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_data_edge(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_data_edge] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.data_edge;
}
GH_INLINE void GH_VIN_set_S_Control_slave_mode_enable(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.slave_mode_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_slave_mode_enable] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_slave_mode_enable(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_slave_mode_enable] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.slave_mode_enable;
}
GH_INLINE void GH_VIN_set_S_Control_master_mode_enable(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.master_mode_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_master_mode_enable] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_master_mode_enable(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_master_mode_enable] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.master_mode_enable;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.emb_sync = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_emb_sync] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_emb_sync] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.emb_sync;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync_mode(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.emb_sync_mode = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_emb_sync_mode] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync_mode(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_emb_sync_mode] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.emb_sync_mode;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync_loc(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.emb_sync_loc = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_emb_sync_loc] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync_loc(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_emb_sync_loc] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.emb_sync_loc;
}
GH_INLINE void GH_VIN_set_S_Control_vs_pol(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.vs_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_vs_pol] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_vs_pol(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_vs_pol] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.vs_pol;
}
GH_INLINE void GH_VIN_set_S_Control_hs_pol(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.hs_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_hs_pol] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_hs_pol(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_hs_pol] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.hs_pol;
}
GH_INLINE void GH_VIN_set_S_Control_field0_pol(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.field0_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_field0_pol] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_field0_pol(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_field0_pol] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.field0_pol;
}
GH_INLINE void GH_VIN_set_S_Control_sony_field_mode(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.sony_field_mode = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_sony_field_mode] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_sony_field_mode(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_sony_field_mode] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.sony_field_mode;
}
GH_INLINE void GH_VIN_set_S_Control_ecc_enable(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.ecc_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_ecc_enable] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_ecc_enable(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_ecc_enable] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.ecc_enable;
}
GH_INLINE void GH_VIN_set_S_Control_hsync_mask(U8 data)
{
    GH_VIN_S_CONTROL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL;
    d.bitc.hsync_mask = data;
    *(volatile U32 *)REG_VIN_S_CONTROL = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Control_hsync_mask] <-- 0x%08x\n",
                        REG_VIN_S_CONTROL,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Control_hsync_mask(void)
{
    GH_VIN_S_CONTROL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Control_hsync_mask] --> 0x%08x\n",
                        REG_VIN_S_CONTROL,value);
    #endif
    return tmp_value.bitc.hsync_mask;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_InputConfig (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig(U32 data);
/*! \brief Reads the register 'VIN_S_InputConfig'. */
U32  GH_VIN_get_S_InputConfig(void);
/*! \brief Writes the bit group 'pad_type' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_pad_type(U8 data);
/*! \brief Reads the bit group 'pad_type' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_pad_type(void);
/*! \brief Writes the bit group 'data_rate' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_data_rate(U8 data);
/*! \brief Reads the bit group 'data_rate' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_data_rate(void);
/*! \brief Writes the bit group 'data_width' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_data_width(U8 data);
/*! \brief Reads the bit group 'data_width' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_data_width(void);
/*! \brief Writes the bit group 'input_source' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_input_source(U8 data);
/*! \brief Reads the bit group 'input_source' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_input_source(void);
/*! \brief Writes the bit group 'rgb_yuv' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_rgb_yuv(U8 data);
/*! \brief Reads the bit group 'rgb_yuv' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_rgb_yuv(void);
/*! \brief Writes the bit group 'pixel_data_width' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_pixel_data_width(U8 data);
/*! \brief Reads the bit group 'pixel_data_width' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_pixel_data_width(void);
/*! \brief Writes the bit group 'yuv_input_order' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_yuv_input_order(U8 data);
/*! \brief Reads the bit group 'yuv_input_order' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_yuv_input_order(void);
/*! \brief Writes the bit group 'slvs_num_lanes' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_slvs_num_lanes(U8 data);
/*! \brief Reads the bit group 'slvs_num_lanes' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_slvs_num_lanes(void);
/*! \brief Writes the bit group 'serial_sensor_interface_mode' of register 'VIN_S_InputConfig'. */
void GH_VIN_set_S_InputConfig_serial_sensor_interface_mode(U8 data);
/*! \brief Reads the bit group 'serial_sensor_interface_mode' of register 'VIN_S_InputConfig'. */
U8   GH_VIN_get_S_InputConfig_serial_sensor_interface_mode(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_InputConfig(U32 data)
{
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_InputConfig(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_InputConfig_pad_type(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.pad_type = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_pad_type] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_pad_type(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_pad_type] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.pad_type;
}
GH_INLINE void GH_VIN_set_S_InputConfig_data_rate(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.data_rate = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_data_rate] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_data_rate(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_data_rate] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.data_rate;
}
GH_INLINE void GH_VIN_set_S_InputConfig_data_width(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.data_width = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_data_width] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_data_width(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_data_width] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.data_width;
}
GH_INLINE void GH_VIN_set_S_InputConfig_input_source(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.input_source = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_input_source] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_input_source(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_input_source] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.input_source;
}
GH_INLINE void GH_VIN_set_S_InputConfig_rgb_yuv(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.rgb_yuv = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_rgb_yuv] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_rgb_yuv(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_rgb_yuv] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.rgb_yuv;
}
GH_INLINE void GH_VIN_set_S_InputConfig_pixel_data_width(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.pixel_data_width = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_pixel_data_width] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_pixel_data_width(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_pixel_data_width] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.pixel_data_width;
}
GH_INLINE void GH_VIN_set_S_InputConfig_yuv_input_order(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.yuv_input_order = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_yuv_input_order] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_yuv_input_order(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_yuv_input_order] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.yuv_input_order;
}
GH_INLINE void GH_VIN_set_S_InputConfig_slvs_num_lanes(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.slvs_num_lanes = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_slvs_num_lanes] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_slvs_num_lanes(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_slvs_num_lanes] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.slvs_num_lanes;
}
GH_INLINE void GH_VIN_set_S_InputConfig_serial_sensor_interface_mode(U8 data)
{
    GH_VIN_S_INPUTCONFIG_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG;
    d.bitc.serial_sensor_interface_mode = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_InputConfig_serial_sensor_interface_mode] <-- 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_serial_sensor_interface_mode(void)
{
    GH_VIN_S_INPUTCONFIG_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_InputConfig_serial_sensor_interface_mode] --> 0x%08x\n",
                        REG_VIN_S_INPUTCONFIG,value);
    #endif
    return tmp_value.bitc.serial_sensor_interface_mode;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Status (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Status'. */
void GH_VIN_set_S_Status(U32 data);
/*! \brief Reads the register 'VIN_S_Status'. */
U32  GH_VIN_get_S_Status(void);
/*! \brief Writes the bit group 'vsync' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_vsync(U8 data);
/*! \brief Reads the bit group 'vsync' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_vsync(void);
/*! \brief Writes the bit group 'trig0' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_trig0(U8 data);
/*! \brief Reads the bit group 'trig0' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_trig0(void);
/*! \brief Writes the bit group 'trig1' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_trig1(U8 data);
/*! \brief Reads the bit group 'trig1' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_trig1(void);
/*! \brief Writes the bit group 'ovfl' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_ovfl(U8 data);
/*! \brief Reads the bit group 'ovfl' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_ovfl(void);
/*! \brief Writes the bit group 'shortl' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_shortl(U8 data);
/*! \brief Reads the bit group 'shortl' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_shortl(void);
/*! \brief Writes the bit group 'shortf' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_shortf(U8 data);
/*! \brief Reads the bit group 'shortf' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_shortf(void);
/*! \brief Writes the bit group 'field' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_field(U8 data);
/*! \brief Reads the bit group 'field' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_field(void);
/*! \brief Writes the bit group 'no_hsync_detected' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_no_hsync_detected(U8 data);
/*! \brief Reads the bit group 'no_hsync_detected' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_no_hsync_detected(void);
/*! \brief Writes the bit group 'no_vsync_detected' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_no_vsync_detected(U8 data);
/*! \brief Reads the bit group 'no_vsync_detected' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_no_vsync_detected(void);
/*! \brief Writes the bit group 'idsp_ahb_vsync' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_idsp_ahb_vsync(U8 data);
/*! \brief Reads the bit group 'idsp_ahb_vsync' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_idsp_ahb_vsync(void);
/*! \brief Writes the bit group 'idsp_ahb_mst_vsync' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_idsp_ahb_mst_vsync(U8 data);
/*! \brief Reads the bit group 'idsp_ahb_mst_vsync' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_idsp_ahb_mst_vsync(void);
/*! \brief Writes the bit group 'idsp_ahb_last_pixel' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_idsp_ahb_last_pixel(U8 data);
/*! \brief Reads the bit group 'idsp_ahb_last_pixel' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_idsp_ahb_last_pixel(void);
/*! \brief Writes the bit group 'ecc_uncorrectable' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_ecc_uncorrectable(U8 data);
/*! \brief Reads the bit group 'ecc_uncorrectable' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_ecc_uncorrectable(void);
/*! \brief Writes the bit group 'program_error' of register 'VIN_S_Status'. */
void GH_VIN_set_S_Status_program_error(U8 data);
/*! \brief Reads the bit group 'program_error' of register 'VIN_S_Status'. */
U8   GH_VIN_get_S_Status_program_error(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Status(U32 data)
{
    *(volatile U32 *)REG_VIN_S_STATUS = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Status(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Status_vsync(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_vsync] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_vsync(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_vsync] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.vsync;
}
GH_INLINE void GH_VIN_set_S_Status_trig0(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.trig0 = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_trig0] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_trig0(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_trig0] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.trig0;
}
GH_INLINE void GH_VIN_set_S_Status_trig1(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.trig1 = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_trig1] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_trig1(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_trig1] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.trig1;
}
GH_INLINE void GH_VIN_set_S_Status_ovfl(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.ovfl = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_ovfl] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_ovfl(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_ovfl] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.ovfl;
}
GH_INLINE void GH_VIN_set_S_Status_shortl(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.shortl = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_shortl] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_shortl(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_shortl] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.shortl;
}
GH_INLINE void GH_VIN_set_S_Status_shortf(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.shortf = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_shortf] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_shortf(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_shortf] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.shortf;
}
GH_INLINE void GH_VIN_set_S_Status_field(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.field = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_field] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_field(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_field] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.field;
}
GH_INLINE void GH_VIN_set_S_Status_no_hsync_detected(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.no_hsync_detected = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_no_hsync_detected] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_no_hsync_detected(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_no_hsync_detected] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.no_hsync_detected;
}
GH_INLINE void GH_VIN_set_S_Status_no_vsync_detected(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.no_vsync_detected = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_no_vsync_detected] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_no_vsync_detected(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_no_vsync_detected] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.no_vsync_detected;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_vsync(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.idsp_ahb_vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_idsp_ahb_vsync] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_vsync(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_idsp_ahb_vsync] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.idsp_ahb_vsync;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_mst_vsync(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.idsp_ahb_mst_vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_idsp_ahb_mst_vsync] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_mst_vsync(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_idsp_ahb_mst_vsync] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.idsp_ahb_mst_vsync;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_last_pixel(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.idsp_ahb_last_pixel = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_idsp_ahb_last_pixel] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_last_pixel(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_idsp_ahb_last_pixel] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.idsp_ahb_last_pixel;
}
GH_INLINE void GH_VIN_set_S_Status_ecc_uncorrectable(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.ecc_uncorrectable = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_ecc_uncorrectable] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_ecc_uncorrectable(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_ecc_uncorrectable] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.ecc_uncorrectable;
}
GH_INLINE void GH_VIN_set_S_Status_program_error(U8 data)
{
    GH_VIN_S_STATUS_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS;
    d.bitc.program_error = data;
    *(volatile U32 *)REG_VIN_S_STATUS = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Status_program_error] <-- 0x%08x\n",
                        REG_VIN_S_STATUS,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Status_program_error(void)
{
    GH_VIN_S_STATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Status_program_error] --> 0x%08x\n",
                        REG_VIN_S_STATUS,value);
    #endif
    return tmp_value.bitc.program_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Vwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Vwidth'. */
void GH_VIN_set_S_Vwidth(U32 data);
/*! \brief Reads the register 'VIN_S_Vwidth'. */
U32  GH_VIN_get_S_Vwidth(void);
/*! \brief Writes the bit group 'vsync_width' of register 'VIN_S_Vwidth'. */
void GH_VIN_set_S_Vwidth_vsync_width(U16 data);
/*! \brief Reads the bit group 'vsync_width' of register 'VIN_S_Vwidth'. */
U16  GH_VIN_get_S_Vwidth_vsync_width(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Vwidth(U32 data)
{
    *(volatile U32 *)REG_VIN_S_VWIDTH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Vwidth] <-- 0x%08x\n",
                        REG_VIN_S_VWIDTH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Vwidth(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_VWIDTH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Vwidth] --> 0x%08x\n",
                        REG_VIN_S_VWIDTH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Vwidth_vsync_width(U16 data)
{
    GH_VIN_S_VWIDTH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VWIDTH;
    d.bitc.vsync_width = data;
    *(volatile U32 *)REG_VIN_S_VWIDTH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Vwidth_vsync_width] <-- 0x%08x\n",
                        REG_VIN_S_VWIDTH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Vwidth_vsync_width(void)
{
    GH_VIN_S_VWIDTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VWIDTH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Vwidth_vsync_width] --> 0x%08x\n",
                        REG_VIN_S_VWIDTH,value);
    #endif
    return tmp_value.bitc.vsync_width;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Hwidth'. */
void GH_VIN_set_S_Hwidth(U32 data);
/*! \brief Reads the register 'VIN_S_Hwidth'. */
U32  GH_VIN_get_S_Hwidth(void);
/*! \brief Writes the bit group 'hsync_width' of register 'VIN_S_Hwidth'. */
void GH_VIN_set_S_Hwidth_hsync_width(U16 data);
/*! \brief Reads the bit group 'hsync_width' of register 'VIN_S_Hwidth'. */
U16  GH_VIN_get_S_Hwidth_hsync_width(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Hwidth(U32 data)
{
    *(volatile U32 *)REG_VIN_S_HWIDTH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Hwidth] <-- 0x%08x\n",
                        REG_VIN_S_HWIDTH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Hwidth(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_HWIDTH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Hwidth] --> 0x%08x\n",
                        REG_VIN_S_HWIDTH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Hwidth_hsync_width(U16 data)
{
    GH_VIN_S_HWIDTH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HWIDTH;
    d.bitc.hsync_width = data;
    *(volatile U32 *)REG_VIN_S_HWIDTH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Hwidth_hsync_width] <-- 0x%08x\n",
                        REG_VIN_S_HWIDTH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Hwidth_hsync_width(void)
{
    GH_VIN_S_HWIDTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HWIDTH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Hwidth_hsync_width] --> 0x%08x\n",
                        REG_VIN_S_HWIDTH,value);
    #endif
    return tmp_value.bitc.hsync_width;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Htop (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Htop'. */
void GH_VIN_set_S_Htop(U32 data);
/*! \brief Reads the register 'VIN_S_Htop'. */
U32  GH_VIN_get_S_Htop(void);
/*! \brief Writes the bit group 'hsync_top' of register 'VIN_S_Htop'. */
void GH_VIN_set_S_Htop_hsync_top(U16 data);
/*! \brief Reads the bit group 'hsync_top' of register 'VIN_S_Htop'. */
U16  GH_VIN_get_S_Htop_hsync_top(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Htop(U32 data)
{
    *(volatile U32 *)REG_VIN_S_HTOP = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Htop] <-- 0x%08x\n",
                        REG_VIN_S_HTOP,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Htop(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_HTOP);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Htop] --> 0x%08x\n",
                        REG_VIN_S_HTOP,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Htop_hsync_top(U16 data)
{
    GH_VIN_S_HTOP_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HTOP;
    d.bitc.hsync_top = data;
    *(volatile U32 *)REG_VIN_S_HTOP = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Htop_hsync_top] <-- 0x%08x\n",
                        REG_VIN_S_HTOP,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Htop_hsync_top(void)
{
    GH_VIN_S_HTOP_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HTOP);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Htop_hsync_top] --> 0x%08x\n",
                        REG_VIN_S_HTOP,value);
    #endif
    return tmp_value.bitc.hsync_top;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hbottom (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Hbottom'. */
void GH_VIN_set_S_Hbottom(U32 data);
/*! \brief Reads the register 'VIN_S_Hbottom'. */
U32  GH_VIN_get_S_Hbottom(void);
/*! \brief Writes the bit group 'hsync_bottom' of register 'VIN_S_Hbottom'. */
void GH_VIN_set_S_Hbottom_hsync_bottom(U16 data);
/*! \brief Reads the bit group 'hsync_bottom' of register 'VIN_S_Hbottom'. */
U16  GH_VIN_get_S_Hbottom_hsync_bottom(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Hbottom(U32 data)
{
    *(volatile U32 *)REG_VIN_S_HBOTTOM = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Hbottom] <-- 0x%08x\n",
                        REG_VIN_S_HBOTTOM,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Hbottom(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_HBOTTOM);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Hbottom] --> 0x%08x\n",
                        REG_VIN_S_HBOTTOM,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Hbottom_hsync_bottom(U16 data)
{
    GH_VIN_S_HBOTTOM_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HBOTTOM;
    d.bitc.hsync_bottom = data;
    *(volatile U32 *)REG_VIN_S_HBOTTOM = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Hbottom_hsync_bottom] <-- 0x%08x\n",
                        REG_VIN_S_HBOTTOM,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Hbottom_hsync_bottom(void)
{
    GH_VIN_S_HBOTTOM_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HBOTTOM);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Hbottom_hsync_bottom] --> 0x%08x\n",
                        REG_VIN_S_HBOTTOM,value);
    #endif
    return tmp_value.bitc.hsync_bottom;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_V (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_V'. */
void GH_VIN_set_S_V(U32 data);
/*! \brief Reads the register 'VIN_S_V'. */
U32  GH_VIN_get_S_V(void);
/*! \brief Writes the bit group 'num_lines' of register 'VIN_S_V'. */
void GH_VIN_set_S_V_num_lines(U16 data);
/*! \brief Reads the bit group 'num_lines' of register 'VIN_S_V'. */
U16  GH_VIN_get_S_V_num_lines(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_V(U32 data)
{
    *(volatile U32 *)REG_VIN_S_V = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_V] <-- 0x%08x\n",
                        REG_VIN_S_V,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_V(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_V);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_V] --> 0x%08x\n",
                        REG_VIN_S_V,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_V_num_lines(U16 data)
{
    GH_VIN_S_V_S d;
    d.all = *(volatile U32 *)REG_VIN_S_V;
    d.bitc.num_lines = data;
    *(volatile U32 *)REG_VIN_S_V = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_V_num_lines] <-- 0x%08x\n",
                        REG_VIN_S_V,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_V_num_lines(void)
{
    GH_VIN_S_V_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_V);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_V_num_lines] --> 0x%08x\n",
                        REG_VIN_S_V,value);
    #endif
    return tmp_value.bitc.num_lines;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_H (read/write)                                              */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_H'. */
void GH_VIN_set_S_H(U32 data);
/*! \brief Reads the register 'VIN_S_H'. */
U32  GH_VIN_get_S_H(void);
/*! \brief Writes the bit group 'num_cols' of register 'VIN_S_H'. */
void GH_VIN_set_S_H_num_cols(U16 data);
/*! \brief Reads the bit group 'num_cols' of register 'VIN_S_H'. */
U16  GH_VIN_get_S_H_num_cols(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_H(U32 data)
{
    *(volatile U32 *)REG_VIN_S_H = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_H] <-- 0x%08x\n",
                        REG_VIN_S_H,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_H(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_H);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_H] --> 0x%08x\n",
                        REG_VIN_S_H,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_H_num_cols(U16 data)
{
    GH_VIN_S_H_S d;
    d.all = *(volatile U32 *)REG_VIN_S_H;
    d.bitc.num_cols = data;
    *(volatile U32 *)REG_VIN_S_H = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_H_num_cols] <-- 0x%08x\n",
                        REG_VIN_S_H,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_H_num_cols(void)
{
    GH_VIN_S_H_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_H);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_H_num_cols] --> 0x%08x\n",
                        REG_VIN_S_H,value);
    #endif
    return tmp_value.bitc.num_cols;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinV (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_MinV'. */
void GH_VIN_set_S_MinV(U32 data);
/*! \brief Reads the register 'VIN_S_MinV'. */
U32  GH_VIN_get_S_MinV(void);
/*! \brief Writes the bit group 'min_num_lines' of register 'VIN_S_MinV'. */
void GH_VIN_set_S_MinV_min_num_lines(U16 data);
/*! \brief Reads the bit group 'min_num_lines' of register 'VIN_S_MinV'. */
U16  GH_VIN_get_S_MinV_min_num_lines(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_MinV(U32 data)
{
    *(volatile U32 *)REG_VIN_S_MINV = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_MinV] <-- 0x%08x\n",
                        REG_VIN_S_MINV,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_MinV(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_MINV);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_MinV] --> 0x%08x\n",
                        REG_VIN_S_MINV,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_MinV_min_num_lines(U16 data)
{
    GH_VIN_S_MINV_S d;
    d.all = *(volatile U32 *)REG_VIN_S_MINV;
    d.bitc.min_num_lines = data;
    *(volatile U32 *)REG_VIN_S_MINV = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_MinV_min_num_lines] <-- 0x%08x\n",
                        REG_VIN_S_MINV,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_MinV_min_num_lines(void)
{
    GH_VIN_S_MINV_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_MINV);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_MinV_min_num_lines] --> 0x%08x\n",
                        REG_VIN_S_MINV,value);
    #endif
    return tmp_value.bitc.min_num_lines;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinH (read/write)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_MinH'. */
void GH_VIN_set_S_MinH(U32 data);
/*! \brief Reads the register 'VIN_S_MinH'. */
U32  GH_VIN_get_S_MinH(void);
/*! \brief Writes the bit group 'min_num_fields' of register 'VIN_S_MinH'. */
void GH_VIN_set_S_MinH_min_num_fields(U16 data);
/*! \brief Reads the bit group 'min_num_fields' of register 'VIN_S_MinH'. */
U16  GH_VIN_get_S_MinH_min_num_fields(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_MinH(U32 data)
{
    *(volatile U32 *)REG_VIN_S_MINH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_MinH] <-- 0x%08x\n",
                        REG_VIN_S_MINH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_MinH(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_MINH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_MinH] --> 0x%08x\n",
                        REG_VIN_S_MINH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_MinH_min_num_fields(U16 data)
{
    GH_VIN_S_MINH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_MINH;
    d.bitc.min_num_fields = data;
    *(volatile U32 *)REG_VIN_S_MINH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_MinH_min_num_fields] <-- 0x%08x\n",
                        REG_VIN_S_MINH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_MinH_min_num_fields(void)
{
    GH_VIN_S_MINH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_MINH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_MinH_min_num_fields] --> 0x%08x\n",
                        REG_VIN_S_MINH,value);
    #endif
    return tmp_value.bitc.min_num_fields;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Trigger0Start'. */
void GH_VIN_set_S_Trigger0Start(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger0Start'. */
U32  GH_VIN_get_S_Trigger0Start(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_Trigger0Start'. */
void GH_VIN_set_S_Trigger0Start_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_Trigger0Start'. */
U16  GH_VIN_get_S_Trigger0Start_startline(void);
/*! \brief Writes the bit group 'pol' of register 'VIN_S_Trigger0Start'. */
void GH_VIN_set_S_Trigger0Start_pol(U8 data);
/*! \brief Reads the bit group 'pol' of register 'VIN_S_Trigger0Start'. */
U8   GH_VIN_get_S_Trigger0Start_pol(void);
/*! \brief Writes the bit group 'enable' of register 'VIN_S_Trigger0Start'. */
void GH_VIN_set_S_Trigger0Start_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VIN_S_Trigger0Start'. */
U8   GH_VIN_get_S_Trigger0Start_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Trigger0Start(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TRIGGER0START = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0Start] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Trigger0Start(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0Start] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_startline(U16 data)
{
    GH_VIN_S_TRIGGER0START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0Start_startline] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Trigger0Start_startline(void)
{
    GH_VIN_S_TRIGGER0START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0Start_startline] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,value);
    #endif
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_pol(U8 data)
{
    GH_VIN_S_TRIGGER0START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START;
    d.bitc.pol = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0Start_pol] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Trigger0Start_pol(void)
{
    GH_VIN_S_TRIGGER0START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0Start_pol] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,value);
    #endif
    return tmp_value.bitc.pol;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_enable(U8 data)
{
    GH_VIN_S_TRIGGER0START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0Start_enable] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Trigger0Start_enable(void)
{
    GH_VIN_S_TRIGGER0START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0Start_enable] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0START,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0End (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Trigger0End'. */
void GH_VIN_set_S_Trigger0End(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger0End'. */
U32  GH_VIN_get_S_Trigger0End(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_Trigger0End'. */
void GH_VIN_set_S_Trigger0End_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_Trigger0End'. */
U16  GH_VIN_get_S_Trigger0End_endline(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Trigger0End(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TRIGGER0END = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0End] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0END,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Trigger0End(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0END);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0End] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0END,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Trigger0End_endline(U16 data)
{
    GH_VIN_S_TRIGGER0END_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0END;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0END = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger0End_endline] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER0END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Trigger0End_endline(void)
{
    GH_VIN_S_TRIGGER0END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0END);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger0End_endline] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER0END,value);
    #endif
    return tmp_value.bitc.endline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Trigger1Start'. */
void GH_VIN_set_S_Trigger1Start(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger1Start'. */
U32  GH_VIN_get_S_Trigger1Start(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_Trigger1Start'. */
void GH_VIN_set_S_Trigger1Start_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_Trigger1Start'. */
U16  GH_VIN_get_S_Trigger1Start_startline(void);
/*! \brief Writes the bit group 'pol' of register 'VIN_S_Trigger1Start'. */
void GH_VIN_set_S_Trigger1Start_pol(U8 data);
/*! \brief Reads the bit group 'pol' of register 'VIN_S_Trigger1Start'. */
U8   GH_VIN_get_S_Trigger1Start_pol(void);
/*! \brief Writes the bit group 'enable' of register 'VIN_S_Trigger1Start'. */
void GH_VIN_set_S_Trigger1Start_enable(U8 data);
/*! \brief Reads the bit group 'enable' of register 'VIN_S_Trigger1Start'. */
U8   GH_VIN_get_S_Trigger1Start_enable(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Trigger1Start(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TRIGGER1START = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1Start] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Trigger1Start(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1Start] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_startline(U16 data)
{
    GH_VIN_S_TRIGGER1START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1Start_startline] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Trigger1Start_startline(void)
{
    GH_VIN_S_TRIGGER1START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1Start_startline] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,value);
    #endif
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_pol(U8 data)
{
    GH_VIN_S_TRIGGER1START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START;
    d.bitc.pol = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1Start_pol] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Trigger1Start_pol(void)
{
    GH_VIN_S_TRIGGER1START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1Start_pol] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,value);
    #endif
    return tmp_value.bitc.pol;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_enable(U8 data)
{
    GH_VIN_S_TRIGGER1START_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1Start_enable] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_Trigger1Start_enable(void)
{
    GH_VIN_S_TRIGGER1START_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1Start_enable] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1START,value);
    #endif
    return tmp_value.bitc.enable;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1End (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_Trigger1End'. */
void GH_VIN_set_S_Trigger1End(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger1End'. */
U32  GH_VIN_get_S_Trigger1End(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_Trigger1End'. */
void GH_VIN_set_S_Trigger1End_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_Trigger1End'. */
U16  GH_VIN_get_S_Trigger1End_endline(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_Trigger1End(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TRIGGER1END = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1End] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1END,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_Trigger1End(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1END);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1End] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1END,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_Trigger1End_endline(U16 data)
{
    GH_VIN_S_TRIGGER1END_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1END;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1END = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_Trigger1End_endline] <-- 0x%08x\n",
                        REG_VIN_S_TRIGGER1END,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_Trigger1End_endline(void)
{
    GH_VIN_S_TRIGGER1END_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1END);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_Trigger1End_endline] --> 0x%08x\n",
                        REG_VIN_S_TRIGGER1END,value);
    #endif
    return tmp_value.bitc.endline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_VoutStart0'. */
void GH_VIN_set_S_VoutStart0(U32 data);
/*! \brief Reads the register 'VIN_S_VoutStart0'. */
U32  GH_VIN_get_S_VoutStart0(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_VoutStart0'. */
void GH_VIN_set_S_VoutStart0_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_VoutStart0'. */
U16  GH_VIN_get_S_VoutStart0_startline(void);
/*! \brief Writes the bit group 'disable_field_check' of register 'VIN_S_VoutStart0'. */
void GH_VIN_set_S_VoutStart0_disable_field_check(U8 data);
/*! \brief Reads the bit group 'disable_field_check' of register 'VIN_S_VoutStart0'. */
U8   GH_VIN_get_S_VoutStart0_disable_field_check(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_VoutStart0(U32 data)
{
    *(volatile U32 *)REG_VIN_S_VOUTSTART0 = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart0] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_VoutStart0(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART0);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart0] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_VoutStart0_startline(U16 data)
{
    GH_VIN_S_VOUTSTART0_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART0;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART0 = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart0_startline] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_VoutStart0_startline(void)
{
    GH_VIN_S_VOUTSTART0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART0);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart0_startline] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,value);
    #endif
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_VoutStart0_disable_field_check(U8 data)
{
    GH_VIN_S_VOUTSTART0_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART0;
    d.bitc.disable_field_check = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART0 = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart0_disable_field_check] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_VoutStart0_disable_field_check(void)
{
    GH_VIN_S_VOUTSTART0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART0);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart0_disable_field_check] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART0,value);
    #endif
    return tmp_value.bitc.disable_field_check;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_VoutStart1'. */
void GH_VIN_set_S_VoutStart1(U32 data);
/*! \brief Reads the register 'VIN_S_VoutStart1'. */
U32  GH_VIN_get_S_VoutStart1(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_VoutStart1'. */
void GH_VIN_set_S_VoutStart1_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_VoutStart1'. */
U16  GH_VIN_get_S_VoutStart1_startline(void);
/*! \brief Writes the bit group 'disable_field_check' of register 'VIN_S_VoutStart1'. */
void GH_VIN_set_S_VoutStart1_disable_field_check(U8 data);
/*! \brief Reads the bit group 'disable_field_check' of register 'VIN_S_VoutStart1'. */
U8   GH_VIN_get_S_VoutStart1_disable_field_check(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_VoutStart1(U32 data)
{
    *(volatile U32 *)REG_VIN_S_VOUTSTART1 = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart1] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_VoutStart1(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART1);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart1] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_VoutStart1_startline(U16 data)
{
    GH_VIN_S_VOUTSTART1_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART1;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART1 = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart1_startline] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_VoutStart1_startline(void)
{
    GH_VIN_S_VOUTSTART1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART1);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart1_startline] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,value);
    #endif
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_VoutStart1_disable_field_check(U8 data)
{
    GH_VIN_S_VOUTSTART1_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART1;
    d.bitc.disable_field_check = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART1 = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_VoutStart1_disable_field_check] <-- 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,d.all,d.all);
    #endif
}
GH_INLINE U8   GH_VIN_get_S_VoutStart1_disable_field_check(void)
{
    GH_VIN_S_VOUTSTART1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART1);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_VoutStart1_disable_field_check] --> 0x%08x\n",
                        REG_VIN_S_VOUTSTART1,value);
    #endif
    return tmp_value.bitc.disable_field_check;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartV (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_CapStartV'. */
void GH_VIN_set_S_CapStartV(U32 data);
/*! \brief Reads the register 'VIN_S_CapStartV'. */
U32  GH_VIN_get_S_CapStartV(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_CapStartV'. */
void GH_VIN_set_S_CapStartV_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_CapStartV'. */
U16  GH_VIN_get_S_CapStartV_startline(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_CapStartV(U32 data)
{
    *(volatile U32 *)REG_VIN_S_CAPSTARTV = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapStartV] <-- 0x%08x\n",
                        REG_VIN_S_CAPSTARTV,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_CapStartV(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTV);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapStartV] --> 0x%08x\n",
                        REG_VIN_S_CAPSTARTV,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_CapStartV_startline(U16 data)
{
    GH_VIN_S_CAPSTARTV_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPSTARTV;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_CAPSTARTV = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapStartV_startline] <-- 0x%08x\n",
                        REG_VIN_S_CAPSTARTV,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_CapStartV_startline(void)
{
    GH_VIN_S_CAPSTARTV_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTV);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapStartV_startline] --> 0x%08x\n",
                        REG_VIN_S_CAPSTARTV,value);
    #endif
    return tmp_value.bitc.startline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartH (read/write)                                      */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_CapStartH'. */
void GH_VIN_set_S_CapStartH(U32 data);
/*! \brief Reads the register 'VIN_S_CapStartH'. */
U32  GH_VIN_get_S_CapStartH(void);
/*! \brief Writes the bit group 'startcol' of register 'VIN_S_CapStartH'. */
void GH_VIN_set_S_CapStartH_startcol(U16 data);
/*! \brief Reads the bit group 'startcol' of register 'VIN_S_CapStartH'. */
U16  GH_VIN_get_S_CapStartH_startcol(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_CapStartH(U32 data)
{
    *(volatile U32 *)REG_VIN_S_CAPSTARTH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapStartH] <-- 0x%08x\n",
                        REG_VIN_S_CAPSTARTH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_CapStartH(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapStartH] --> 0x%08x\n",
                        REG_VIN_S_CAPSTARTH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_CapStartH_startcol(U16 data)
{
    GH_VIN_S_CAPSTARTH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPSTARTH;
    d.bitc.startcol = data;
    *(volatile U32 *)REG_VIN_S_CAPSTARTH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapStartH_startcol] <-- 0x%08x\n",
                        REG_VIN_S_CAPSTARTH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_CapStartH_startcol(void)
{
    GH_VIN_S_CAPSTARTH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapStartH_startcol] --> 0x%08x\n",
                        REG_VIN_S_CAPSTARTH,value);
    #endif
    return tmp_value.bitc.startcol;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndV (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_CapEndV'. */
void GH_VIN_set_S_CapEndV(U32 data);
/*! \brief Reads the register 'VIN_S_CapEndV'. */
U32  GH_VIN_get_S_CapEndV(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_CapEndV'. */
void GH_VIN_set_S_CapEndV_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_CapEndV'. */
U16  GH_VIN_get_S_CapEndV_endline(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_CapEndV(U32 data)
{
    *(volatile U32 *)REG_VIN_S_CAPENDV = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapEndV] <-- 0x%08x\n",
                        REG_VIN_S_CAPENDV,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_CapEndV(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDV);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapEndV] --> 0x%08x\n",
                        REG_VIN_S_CAPENDV,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_CapEndV_endline(U16 data)
{
    GH_VIN_S_CAPENDV_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPENDV;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_CAPENDV = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapEndV_endline] <-- 0x%08x\n",
                        REG_VIN_S_CAPENDV,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_CapEndV_endline(void)
{
    GH_VIN_S_CAPENDV_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDV);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapEndV_endline] --> 0x%08x\n",
                        REG_VIN_S_CAPENDV,value);
    #endif
    return tmp_value.bitc.endline;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndH (read/write)                                        */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_CapEndH'. */
void GH_VIN_set_S_CapEndH(U32 data);
/*! \brief Reads the register 'VIN_S_CapEndH'. */
U32  GH_VIN_get_S_CapEndH(void);
/*! \brief Writes the bit group 'endcol' of register 'VIN_S_CapEndH'. */
void GH_VIN_set_S_CapEndH_endcol(U16 data);
/*! \brief Reads the bit group 'endcol' of register 'VIN_S_CapEndH'. */
U16  GH_VIN_get_S_CapEndH_endcol(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_CapEndH(U32 data)
{
    *(volatile U32 *)REG_VIN_S_CAPENDH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapEndH] <-- 0x%08x\n",
                        REG_VIN_S_CAPENDH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_CapEndH(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapEndH] --> 0x%08x\n",
                        REG_VIN_S_CAPENDH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_CapEndH_endcol(U16 data)
{
    GH_VIN_S_CAPENDH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPENDH;
    d.bitc.endcol = data;
    *(volatile U32 *)REG_VIN_S_CAPENDH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_CapEndH_endcol] <-- 0x%08x\n",
                        REG_VIN_S_CAPENDH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_CapEndH_endcol(void)
{
    GH_VIN_S_CAPENDH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_CapEndH_endcol] --> 0x%08x\n",
                        REG_VIN_S_CAPENDH,value);
    #endif
    return tmp_value.bitc.endcol;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_BlankLengthH (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_BlankLengthH'. */
void GH_VIN_set_S_BlankLengthH(U32 data);
/*! \brief Reads the register 'VIN_S_BlankLengthH'. */
U32  GH_VIN_get_S_BlankLengthH(void);
/*! \brief Writes the bit group 'blank_length' of register 'VIN_S_BlankLengthH'. */
void GH_VIN_set_S_BlankLengthH_blank_length(U16 data);
/*! \brief Reads the bit group 'blank_length' of register 'VIN_S_BlankLengthH'. */
U16  GH_VIN_get_S_BlankLengthH_blank_length(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_BlankLengthH(U32 data)
{
    *(volatile U32 *)REG_VIN_S_BLANKLENGTHH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_BlankLengthH] <-- 0x%08x\n",
                        REG_VIN_S_BLANKLENGTHH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_BlankLengthH(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_BLANKLENGTHH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_BlankLengthH] --> 0x%08x\n",
                        REG_VIN_S_BLANKLENGTHH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_BlankLengthH_blank_length(U16 data)
{
    GH_VIN_S_BLANKLENGTHH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_BLANKLENGTHH;
    d.bitc.blank_length = data;
    *(volatile U32 *)REG_VIN_S_BLANKLENGTHH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_BlankLengthH_blank_length] <-- 0x%08x\n",
                        REG_VIN_S_BLANKLENGTHH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_BlankLengthH_blank_length(void)
{
    GH_VIN_S_BLANKLENGTHH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_BLANKLENGTHH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_BlankLengthH_blank_length] --> 0x%08x\n",
                        REG_VIN_S_BLANKLENGTHH,value);
    #endif
    return tmp_value.bitc.blank_length;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_TimeoutVLow'. */
void GH_VIN_set_S_TimeoutVLow(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutVLow'. */
U32  GH_VIN_get_S_TimeoutVLow(void);
/*! \brief Writes the bit group 'vsync_timeout_low' of register 'VIN_S_TimeoutVLow'. */
void GH_VIN_set_S_TimeoutVLow_vsync_timeout_low(U16 data);
/*! \brief Reads the bit group 'vsync_timeout_low' of register 'VIN_S_TimeoutVLow'. */
U16  GH_VIN_get_S_TimeoutVLow_vsync_timeout_low(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_TimeoutVLow(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutVLow] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTVLOW,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_TimeoutVLow(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVLOW);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutVLow] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTVLOW,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_TimeoutVLow_vsync_timeout_low(U16 data)
{
    GH_VIN_S_TIMEOUTVLOW_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW;
    d.bitc.vsync_timeout_low = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutVLow_vsync_timeout_low] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTVLOW,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_TimeoutVLow_vsync_timeout_low(void)
{
    GH_VIN_S_TIMEOUTVLOW_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVLOW);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutVLow_vsync_timeout_low] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTVLOW,value);
    #endif
    return tmp_value.bitc.vsync_timeout_low;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_TimeoutVHigh'. */
void GH_VIN_set_S_TimeoutVHigh(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutVHigh'. */
U32  GH_VIN_get_S_TimeoutVHigh(void);
/*! \brief Writes the bit group 'vsync_timeout_high' of register 'VIN_S_TimeoutVHigh'. */
void GH_VIN_set_S_TimeoutVHigh_vsync_timeout_high(U16 data);
/*! \brief Reads the bit group 'vsync_timeout_high' of register 'VIN_S_TimeoutVHigh'. */
U16  GH_VIN_get_S_TimeoutVHigh_vsync_timeout_high(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_TimeoutVHigh(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutVHigh] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTVHIGH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_TimeoutVHigh(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutVHigh] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTVHIGH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_TimeoutVHigh_vsync_timeout_high(U16 data)
{
    GH_VIN_S_TIMEOUTVHIGH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH;
    d.bitc.vsync_timeout_high = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutVHigh_vsync_timeout_high] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTVHIGH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_TimeoutVHigh_vsync_timeout_high(void)
{
    GH_VIN_S_TIMEOUTVHIGH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutVHigh_vsync_timeout_high] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTVHIGH,value);
    #endif
    return tmp_value.bitc.vsync_timeout_high;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_TimeoutHLow'. */
void GH_VIN_set_S_TimeoutHLow(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutHLow'. */
U32  GH_VIN_get_S_TimeoutHLow(void);
/*! \brief Writes the bit group 'hsync_timeout_low' of register 'VIN_S_TimeoutHLow'. */
void GH_VIN_set_S_TimeoutHLow_hsync_timeout_low(U16 data);
/*! \brief Reads the bit group 'hsync_timeout_low' of register 'VIN_S_TimeoutHLow'. */
U16  GH_VIN_get_S_TimeoutHLow_hsync_timeout_low(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_TimeoutHLow(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutHLow] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTHLOW,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_TimeoutHLow(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHLOW);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutHLow] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTHLOW,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_TimeoutHLow_hsync_timeout_low(U16 data)
{
    GH_VIN_S_TIMEOUTHLOW_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW;
    d.bitc.hsync_timeout_low = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutHLow_hsync_timeout_low] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTHLOW,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_TimeoutHLow_hsync_timeout_low(void)
{
    GH_VIN_S_TIMEOUTHLOW_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHLOW);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutHLow_hsync_timeout_low] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTHLOW,value);
    #endif
    return tmp_value.bitc.hsync_timeout_low;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Writes the register 'VIN_S_TimeoutHHigh'. */
void GH_VIN_set_S_TimeoutHHigh(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutHHigh'. */
U32  GH_VIN_get_S_TimeoutHHigh(void);
/*! \brief Writes the bit group 'hsync_timeout_high' of register 'VIN_S_TimeoutHHigh'. */
void GH_VIN_set_S_TimeoutHHigh_hsync_timeout_high(U16 data);
/*! \brief Reads the bit group 'hsync_timeout_high' of register 'VIN_S_TimeoutHHigh'. */
U16  GH_VIN_get_S_TimeoutHHigh_hsync_timeout_high(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE void GH_VIN_set_S_TimeoutHHigh(U32 data)
{
    *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH = data;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutHHigh] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTHHIGH,data,data);
    #endif
}
GH_INLINE U32  GH_VIN_get_S_TimeoutHHigh(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutHHigh] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTHHIGH,value);
    #endif
    return value;
}
GH_INLINE void GH_VIN_set_S_TimeoutHHigh_hsync_timeout_high(U16 data)
{
    GH_VIN_S_TIMEOUTHHIGH_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH;
    d.bitc.hsync_timeout_high = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH = d.all;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "WRREG(0x%08x,0x%08x); \\\\ [GH_VIN_set_S_TimeoutHHigh_hsync_timeout_high] <-- 0x%08x\n",
                        REG_VIN_S_TIMEOUTHHIGH,d.all,d.all);
    #endif
}
GH_INLINE U16  GH_VIN_get_S_TimeoutHHigh_hsync_timeout_high(void)
{
    GH_VIN_S_TIMEOUTHHIGH_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_TimeoutHHigh_hsync_timeout_high] --> 0x%08x\n",
                        REG_VIN_S_TIMEOUTHHIGH,value);
    #endif
    return tmp_value.bitc.hsync_timeout_high;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoCount (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIN_S_debugFifoCount'. */
U32  GH_VIN_get_S_debugFifoCount(void);
/*! \brief Reads the bit group 'num_words_in_fifo' of register 'VIN_S_debugFifoCount'. */
U16  GH_VIN_get_S_debugFifoCount_num_words_in_fifo(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIN_get_S_debugFifoCount(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFOCOUNT);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoCount] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFOCOUNT,value);
    #endif
    return value;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoCount_num_words_in_fifo(void)
{
    GH_VIN_S_DEBUGFIFOCOUNT_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFOCOUNT);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoCount_num_words_in_fifo] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFOCOUNT,value);
    #endif
    return tmp_value.bitc.num_words_in_fifo;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData0 (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIN_S_debugFifoData0'. */
U32  GH_VIN_get_S_debugFifoData0(void);
/*! \brief Reads the bit group 'pixel_0_read_data' of register 'VIN_S_debugFifoData0'. */
U16  GH_VIN_get_S_debugFifoData0_pixel_0_read_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIN_get_S_debugFifoData0(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA0);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoData0] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFODATA0,value);
    #endif
    return value;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoData0_pixel_0_read_data(void)
{
    GH_VIN_S_DEBUGFIFODATA0_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA0);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoData0_pixel_0_read_data] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFODATA0,value);
    #endif
    return tmp_value.bitc.pixel_0_read_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData1 (read)                                       */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIN_S_debugFifoData1'. */
U32  GH_VIN_get_S_debugFifoData1(void);
/*! \brief Reads the bit group 'pixel_1_read_data' of register 'VIN_S_debugFifoData1'. */
U16  GH_VIN_get_S_debugFifoData1_pixel_1_read_data(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIN_get_S_debugFifoData1(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA1);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoData1] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFODATA1,value);
    #endif
    return value;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoData1_pixel_1_read_data(void)
{
    GH_VIN_S_DEBUGFIFODATA1_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA1);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugFifoData1_pixel_1_read_data] --> 0x%08x\n",
                        REG_VIN_S_DEBUGFIFODATA1,value);
    #endif
    return tmp_value.bitc.pixel_1_read_data;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugStall (read)                                           */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIN_S_debugStall'. */
U32  GH_VIN_get_S_debugStall(void);
/*! \brief Reads the bit group 'output_interface_stall' of register 'VIN_S_debugStall'. */
U8   GH_VIN_get_S_debugStall_output_interface_stall(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIN_get_S_debugStall(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGSTALL);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugStall] --> 0x%08x\n",
                        REG_VIN_S_DEBUGSTALL,value);
    #endif
    return value;
}
GH_INLINE U8   GH_VIN_get_S_debugStall_output_interface_stall(void)
{
    GH_VIN_S_DEBUGSTALL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGSTALL);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_debugStall_output_interface_stall] --> 0x%08x\n",
                        REG_VIN_S_DEBUGSTALL,value);
    #endif
    return tmp_value.bitc.output_interface_stall;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* register VIN_S_slvsSatus (read)                                            */
/*----------------------------------------------------------------------------*/
#if GH_INLINE_LEVEL == 0
/*! \brief Reads the register 'VIN_S_slvsSatus'. */
U32  GH_VIN_get_S_slvsSatus(void);
/*! \brief Reads the bit group 'slvs_lock_state' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_slvs_lock_state(void);
/*! \brief Reads the bit group 'detected_sync_code_match' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_detected_sync_code_match(void);
/*! \brief Reads the bit group 'detected_start_of_frame' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_detected_start_of_frame(void);
/*! \brief Reads the bit group 'detected_vsync' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_detected_vsync(void);
/*! \brief Reads the bit group 'detected_start_of_line' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_detected_start_of_line(void);
/*! \brief Reads the bit group 'valid_pixel_generated' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_valid_pixel_generated(void);
/*! \brief Reads the bit group 'end_of_line_generated' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_end_of_line_generated(void);
/*! \brief Reads the bit group 'corrected_error' of register 'VIN_S_slvsSatus'. */
U8   GH_VIN_get_S_slvsSatus_corrected_error(void);
#else /* GH_INLINE_LEVEL == 0 */
GH_INLINE U32  GH_VIN_get_S_slvsSatus(void)
{
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return value;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_slvs_lock_state(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_slvs_lock_state] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.slvs_lock_state;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_sync_code_match(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_detected_sync_code_match] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.detected_sync_code_match;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_start_of_frame(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_detected_start_of_frame] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.detected_start_of_frame;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_vsync(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_detected_vsync] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.detected_vsync;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_start_of_line(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_detected_start_of_line] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.detected_start_of_line;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_valid_pixel_generated(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_valid_pixel_generated] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.valid_pixel_generated;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_end_of_line_generated(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_end_of_line_generated] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.end_of_line_generated;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_corrected_error(void)
{
    GH_VIN_S_SLVSSATUS_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS);

    tmp_value.all = value;
    #if GH_VIN_ENABLE_DEBUG_PRINT
    GH_VIN_DEBUG_PRINT_FUNCTION( "value = RDREG(0x%08x); \\\\ [GH_VIN_get_S_slvsSatus_corrected_error] --> 0x%08x\n",
                        REG_VIN_S_SLVSSATUS,value);
    #endif
    return tmp_value.bitc.corrected_error;
}
#endif /* GH_INLINE_LEVEL == 0 */

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VIN_init(void);

#ifdef __cplusplus
}
#endif

#endif /* _GH_VIN_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

