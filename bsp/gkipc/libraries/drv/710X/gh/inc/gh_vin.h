/*!
*******************************************************************************
**
** \file      gh_vin.h
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

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VIN_S_CONTROL                                   FIO_ADDRESS(VIN,0x90009000) /* read/write */
#define REG_VIN_S_INPUTCONFIG                               FIO_ADDRESS(VIN,0x90009004) /* read/write */
#define REG_VIN_S_STATUS                                    FIO_ADDRESS(VIN,0x90009008) /* read/write */
#define REG_VIN_S_VWIDTH                                    FIO_ADDRESS(VIN,0x9000900C) /* read/write */
#define REG_VIN_S_HWIDTH                                    FIO_ADDRESS(VIN,0x90009010) /* read/write */
#define REG_VIN_S_HTOP                                      FIO_ADDRESS(VIN,0x90009014) /* read/write */
#define REG_VIN_S_HBOTTOM                                   FIO_ADDRESS(VIN,0x90009018) /* read/write */
#define REG_VIN_S_V                                         FIO_ADDRESS(VIN,0x9000901C) /* read/write */
#define REG_VIN_S_H                                         FIO_ADDRESS(VIN,0x90009020) /* read/write */
#define REG_VIN_S_MINV                                      FIO_ADDRESS(VIN,0x90009024) /* read/write */
#define REG_VIN_S_MINH                                      FIO_ADDRESS(VIN,0x90009028) /* read/write */
#define REG_VIN_S_TRIGGER0START                             FIO_ADDRESS(VIN,0x9000902C) /* read/write */
#define REG_VIN_S_TRIGGER0END                               FIO_ADDRESS(VIN,0x90009030) /* read/write */
#define REG_VIN_S_TRIGGER1START                             FIO_ADDRESS(VIN,0x90009034) /* read/write */
#define REG_VIN_S_TRIGGER1END                               FIO_ADDRESS(VIN,0x90009038) /* read/write */
#define REG_VIN_S_VOUTSTART0                                FIO_ADDRESS(VIN,0x9000903C) /* read/write */
#define REG_VIN_S_VOUTSTART1                                FIO_ADDRESS(VIN,0x90009040) /* read/write */
#define REG_VIN_S_CAPSTARTV                                 FIO_ADDRESS(VIN,0x90009044) /* read/write */
#define REG_VIN_S_CAPSTARTH                                 FIO_ADDRESS(VIN,0x90009048) /* read/write */
#define REG_VIN_S_CAPENDV                                   FIO_ADDRESS(VIN,0x9000904C) /* read/write */
#define REG_VIN_S_CAPENDH                                   FIO_ADDRESS(VIN,0x90009050) /* read/write */
#define REG_VIN_S_BLANKLENGTHH                              FIO_ADDRESS(VIN,0x90009054) /* read/write */
#define REG_VIN_S_TIMEOUTVLOW                               FIO_ADDRESS(VIN,0x90009058) /* read/write */
#define REG_VIN_S_TIMEOUTVHIGH                              FIO_ADDRESS(VIN,0x9000905C) /* read/write */
#define REG_VIN_S_TIMEOUTHLOW                               FIO_ADDRESS(VIN,0x90009060) /* read/write */
#define REG_VIN_S_TIMEOUTHHIGH                              FIO_ADDRESS(VIN,0x90009064) /* read/write */
#define REG_VIN_S_DEBUGFIFOCOUNT                            FIO_ADDRESS(VIN,0x90009080) /* read */
#define REG_VIN_S_DEBUGFIFODATA0                            FIO_ADDRESS(VIN,0x90009084) /* read */
#define REG_VIN_S_DEBUGFIFODATA1                            FIO_ADDRESS(VIN,0x90009088) /* read */
#define REG_VIN_S_DEBUGSTALL                                FIO_ADDRESS(VIN,0x9000908C) /* read */
#define REG_VIN_S_SLVSSATUS                                 FIO_ADDRESS(VIN,0x90009090) /* read */

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

/*----------------------------------------------------------------------------*/
/* register VIN_S_InputConfig (read/write)                                    */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_Status (read/write)                                         */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_Vwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Vwidth'. */
void GH_VIN_set_S_Vwidth(U32 data);
/*! \brief Reads the register 'VIN_S_Vwidth'. */
U32  GH_VIN_get_S_Vwidth(void);
/*! \brief Writes the bit group 'vsync_width' of register 'VIN_S_Vwidth'. */
void GH_VIN_set_S_Vwidth_vsync_width(U16 data);
/*! \brief Reads the bit group 'vsync_width' of register 'VIN_S_Vwidth'. */
U16  GH_VIN_get_S_Vwidth_vsync_width(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Hwidth'. */
void GH_VIN_set_S_Hwidth(U32 data);
/*! \brief Reads the register 'VIN_S_Hwidth'. */
U32  GH_VIN_get_S_Hwidth(void);
/*! \brief Writes the bit group 'hsync_width' of register 'VIN_S_Hwidth'. */
void GH_VIN_set_S_Hwidth_hsync_width(U16 data);
/*! \brief Reads the bit group 'hsync_width' of register 'VIN_S_Hwidth'. */
U16  GH_VIN_get_S_Hwidth_hsync_width(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_Htop (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Htop'. */
void GH_VIN_set_S_Htop(U32 data);
/*! \brief Reads the register 'VIN_S_Htop'. */
U32  GH_VIN_get_S_Htop(void);
/*! \brief Writes the bit group 'hsync_top' of register 'VIN_S_Htop'. */
void GH_VIN_set_S_Htop_hsync_top(U16 data);
/*! \brief Reads the bit group 'hsync_top' of register 'VIN_S_Htop'. */
U16  GH_VIN_get_S_Htop_hsync_top(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hbottom (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Hbottom'. */
void GH_VIN_set_S_Hbottom(U32 data);
/*! \brief Reads the register 'VIN_S_Hbottom'. */
U32  GH_VIN_get_S_Hbottom(void);
/*! \brief Writes the bit group 'hsync_bottom' of register 'VIN_S_Hbottom'. */
void GH_VIN_set_S_Hbottom_hsync_bottom(U16 data);
/*! \brief Reads the bit group 'hsync_bottom' of register 'VIN_S_Hbottom'. */
U16  GH_VIN_get_S_Hbottom_hsync_bottom(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_V (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_V'. */
void GH_VIN_set_S_V(U32 data);
/*! \brief Reads the register 'VIN_S_V'. */
U32  GH_VIN_get_S_V(void);
/*! \brief Writes the bit group 'num_lines' of register 'VIN_S_V'. */
void GH_VIN_set_S_V_num_lines(U16 data);
/*! \brief Reads the bit group 'num_lines' of register 'VIN_S_V'. */
U16  GH_VIN_get_S_V_num_lines(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_H (read/write)                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_H'. */
void GH_VIN_set_S_H(U32 data);
/*! \brief Reads the register 'VIN_S_H'. */
U32  GH_VIN_get_S_H(void);
/*! \brief Writes the bit group 'num_cols' of register 'VIN_S_H'. */
void GH_VIN_set_S_H_num_cols(U16 data);
/*! \brief Reads the bit group 'num_cols' of register 'VIN_S_H'. */
U16  GH_VIN_get_S_H_num_cols(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinV (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_MinV'. */
void GH_VIN_set_S_MinV(U32 data);
/*! \brief Reads the register 'VIN_S_MinV'. */
U32  GH_VIN_get_S_MinV(void);
/*! \brief Writes the bit group 'min_num_lines' of register 'VIN_S_MinV'. */
void GH_VIN_set_S_MinV_min_num_lines(U16 data);
/*! \brief Reads the bit group 'min_num_lines' of register 'VIN_S_MinV'. */
U16  GH_VIN_get_S_MinV_min_num_lines(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinH (read/write)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_MinH'. */
void GH_VIN_set_S_MinH(U32 data);
/*! \brief Reads the register 'VIN_S_MinH'. */
U32  GH_VIN_get_S_MinH(void);
/*! \brief Writes the bit group 'min_num_fields' of register 'VIN_S_MinH'. */
void GH_VIN_set_S_MinH_min_num_fields(U16 data);
/*! \brief Reads the bit group 'min_num_fields' of register 'VIN_S_MinH'. */
U16  GH_VIN_get_S_MinH_min_num_fields(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0End (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Trigger0End'. */
void GH_VIN_set_S_Trigger0End(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger0End'. */
U32  GH_VIN_get_S_Trigger0End(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_Trigger0End'. */
void GH_VIN_set_S_Trigger0End_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_Trigger0End'. */
U16  GH_VIN_get_S_Trigger0End_endline(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1End (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_Trigger1End'. */
void GH_VIN_set_S_Trigger1End(U32 data);
/*! \brief Reads the register 'VIN_S_Trigger1End'. */
U32  GH_VIN_get_S_Trigger1End(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_Trigger1End'. */
void GH_VIN_set_S_Trigger1End_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_Trigger1End'. */
U16  GH_VIN_get_S_Trigger1End_endline(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartV (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_CapStartV'. */
void GH_VIN_set_S_CapStartV(U32 data);
/*! \brief Reads the register 'VIN_S_CapStartV'. */
U32  GH_VIN_get_S_CapStartV(void);
/*! \brief Writes the bit group 'startline' of register 'VIN_S_CapStartV'. */
void GH_VIN_set_S_CapStartV_startline(U16 data);
/*! \brief Reads the bit group 'startline' of register 'VIN_S_CapStartV'. */
U16  GH_VIN_get_S_CapStartV_startline(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartH (read/write)                                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_CapStartH'. */
void GH_VIN_set_S_CapStartH(U32 data);
/*! \brief Reads the register 'VIN_S_CapStartH'. */
U32  GH_VIN_get_S_CapStartH(void);
/*! \brief Writes the bit group 'startcol' of register 'VIN_S_CapStartH'. */
void GH_VIN_set_S_CapStartH_startcol(U16 data);
/*! \brief Reads the bit group 'startcol' of register 'VIN_S_CapStartH'. */
U16  GH_VIN_get_S_CapStartH_startcol(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndV (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_CapEndV'. */
void GH_VIN_set_S_CapEndV(U32 data);
/*! \brief Reads the register 'VIN_S_CapEndV'. */
U32  GH_VIN_get_S_CapEndV(void);
/*! \brief Writes the bit group 'endline' of register 'VIN_S_CapEndV'. */
void GH_VIN_set_S_CapEndV_endline(U16 data);
/*! \brief Reads the bit group 'endline' of register 'VIN_S_CapEndV'. */
U16  GH_VIN_get_S_CapEndV_endline(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndH (read/write)                                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_CapEndH'. */
void GH_VIN_set_S_CapEndH(U32 data);
/*! \brief Reads the register 'VIN_S_CapEndH'. */
U32  GH_VIN_get_S_CapEndH(void);
/*! \brief Writes the bit group 'endcol' of register 'VIN_S_CapEndH'. */
void GH_VIN_set_S_CapEndH_endcol(U16 data);
/*! \brief Reads the bit group 'endcol' of register 'VIN_S_CapEndH'. */
U16  GH_VIN_get_S_CapEndH_endcol(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_BlankLengthH (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_BlankLengthH'. */
void GH_VIN_set_S_BlankLengthH(U32 data);
/*! \brief Reads the register 'VIN_S_BlankLengthH'. */
U32  GH_VIN_get_S_BlankLengthH(void);
/*! \brief Writes the bit group 'blank_length' of register 'VIN_S_BlankLengthH'. */
void GH_VIN_set_S_BlankLengthH_blank_length(U16 data);
/*! \brief Reads the bit group 'blank_length' of register 'VIN_S_BlankLengthH'. */
U16  GH_VIN_get_S_BlankLengthH_blank_length(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_TimeoutVLow'. */
void GH_VIN_set_S_TimeoutVLow(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutVLow'. */
U32  GH_VIN_get_S_TimeoutVLow(void);
/*! \brief Writes the bit group 'vsync_timeout_low' of register 'VIN_S_TimeoutVLow'. */
void GH_VIN_set_S_TimeoutVLow_vsync_timeout_low(U16 data);
/*! \brief Reads the bit group 'vsync_timeout_low' of register 'VIN_S_TimeoutVLow'. */
U16  GH_VIN_get_S_TimeoutVLow_vsync_timeout_low(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_TimeoutVHigh'. */
void GH_VIN_set_S_TimeoutVHigh(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutVHigh'. */
U32  GH_VIN_get_S_TimeoutVHigh(void);
/*! \brief Writes the bit group 'vsync_timeout_high' of register 'VIN_S_TimeoutVHigh'. */
void GH_VIN_set_S_TimeoutVHigh_vsync_timeout_high(U16 data);
/*! \brief Reads the bit group 'vsync_timeout_high' of register 'VIN_S_TimeoutVHigh'. */
U16  GH_VIN_get_S_TimeoutVHigh_vsync_timeout_high(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_TimeoutHLow'. */
void GH_VIN_set_S_TimeoutHLow(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutHLow'. */
U32  GH_VIN_get_S_TimeoutHLow(void);
/*! \brief Writes the bit group 'hsync_timeout_low' of register 'VIN_S_TimeoutHLow'. */
void GH_VIN_set_S_TimeoutHLow_hsync_timeout_low(U16 data);
/*! \brief Reads the bit group 'hsync_timeout_low' of register 'VIN_S_TimeoutHLow'. */
U16  GH_VIN_get_S_TimeoutHLow_hsync_timeout_low(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VIN_S_TimeoutHHigh'. */
void GH_VIN_set_S_TimeoutHHigh(U32 data);
/*! \brief Reads the register 'VIN_S_TimeoutHHigh'. */
U32  GH_VIN_get_S_TimeoutHHigh(void);
/*! \brief Writes the bit group 'hsync_timeout_high' of register 'VIN_S_TimeoutHHigh'. */
void GH_VIN_set_S_TimeoutHHigh_hsync_timeout_high(U16 data);
/*! \brief Reads the bit group 'hsync_timeout_high' of register 'VIN_S_TimeoutHHigh'. */
U16  GH_VIN_get_S_TimeoutHHigh_hsync_timeout_high(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoCount (read)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIN_S_debugFifoCount'. */
U32  GH_VIN_get_S_debugFifoCount(void);
/*! \brief Reads the bit group 'num_words_in_fifo' of register 'VIN_S_debugFifoCount'. */
U16  GH_VIN_get_S_debugFifoCount_num_words_in_fifo(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData0 (read)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIN_S_debugFifoData0'. */
U32  GH_VIN_get_S_debugFifoData0(void);
/*! \brief Reads the bit group 'pixel_0_read_data' of register 'VIN_S_debugFifoData0'. */
U16  GH_VIN_get_S_debugFifoData0_pixel_0_read_data(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData1 (read)                                       */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIN_S_debugFifoData1'. */
U32  GH_VIN_get_S_debugFifoData1(void);
/*! \brief Reads the bit group 'pixel_1_read_data' of register 'VIN_S_debugFifoData1'. */
U16  GH_VIN_get_S_debugFifoData1_pixel_1_read_data(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugStall (read)                                           */
/*----------------------------------------------------------------------------*/
/*! \brief Reads the register 'VIN_S_debugStall'. */
U32  GH_VIN_get_S_debugStall(void);
/*! \brief Reads the bit group 'output_interface_stall' of register 'VIN_S_debugStall'. */
U8   GH_VIN_get_S_debugStall_output_interface_stall(void);

/*----------------------------------------------------------------------------*/
/* register VIN_S_slvsSatus (read)                                            */
/*----------------------------------------------------------------------------*/
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

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VIN_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vin.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VIN_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

