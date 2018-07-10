/******************************************************************************
**
** \file      gh_vin.c
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
#include "gh_vin.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VIN_S_CONTROL_REAL                              FIO_ADDRESS(VIN,0x60009000) /* read/write */
#define REG_VIN_S_INPUTCONFIG_REAL                          FIO_ADDRESS(VIN,0x60009004) /* read/write */
#define REG_VIN_S_STATUS_REAL                               FIO_ADDRESS(VIN,0x60009008) /* read/write */
#define REG_VIN_S_VWIDTH_REAL                               FIO_ADDRESS(VIN,0x6000900C) /* read/write */
#define REG_VIN_S_HWIDTH_REAL                               FIO_ADDRESS(VIN,0x60009010) /* read/write */
#define REG_VIN_S_HTOP_REAL                                 FIO_ADDRESS(VIN,0x60009014) /* read/write */
#define REG_VIN_S_HBOTTOM_REAL                              FIO_ADDRESS(VIN,0x60009018) /* read/write */
#define REG_VIN_S_V_REAL                                    FIO_ADDRESS(VIN,0x6000901C) /* read/write */
#define REG_VIN_S_H_REAL                                    FIO_ADDRESS(VIN,0x60009020) /* read/write */
#define REG_VIN_S_MINV_REAL                                 FIO_ADDRESS(VIN,0x60009024) /* read/write */
#define REG_VIN_S_MINH_REAL                                 FIO_ADDRESS(VIN,0x60009028) /* read/write */
#define REG_VIN_S_TRIGGER0START_REAL                        FIO_ADDRESS(VIN,0x6000902C) /* read/write */
#define REG_VIN_S_TRIGGER0END_REAL                          FIO_ADDRESS(VIN,0x60009030) /* read/write */
#define REG_VIN_S_TRIGGER1START_REAL                        FIO_ADDRESS(VIN,0x60009034) /* read/write */
#define REG_VIN_S_TRIGGER1END_REAL                          FIO_ADDRESS(VIN,0x60009038) /* read/write */
#define REG_VIN_S_VOUTSTART0_REAL                           FIO_ADDRESS(VIN,0x6000903C) /* read/write */
#define REG_VIN_S_VOUTSTART1_REAL                           FIO_ADDRESS(VIN,0x60009040) /* read/write */
#define REG_VIN_S_CAPSTARTV_REAL                            FIO_ADDRESS(VIN,0x60009044) /* read/write */
#define REG_VIN_S_CAPSTARTH_REAL                            FIO_ADDRESS(VIN,0x60009048) /* read/write */
#define REG_VIN_S_CAPENDV_REAL                              FIO_ADDRESS(VIN,0x6000904C) /* read/write */
#define REG_VIN_S_CAPENDH_REAL                              FIO_ADDRESS(VIN,0x60009050) /* read/write */
#define REG_VIN_S_BLANKLENGTHH_REAL                         FIO_ADDRESS(VIN,0x60009054) /* read/write */
#define REG_VIN_S_TIMEOUTVLOW_REAL                          FIO_ADDRESS(VIN,0x60009058) /* read/write */
#define REG_VIN_S_TIMEOUTVHIGH_REAL                         FIO_ADDRESS(VIN,0x6000905C) /* read/write */
#define REG_VIN_S_TIMEOUTHLOW_REAL                          FIO_ADDRESS(VIN,0x60009060) /* read/write */
#define REG_VIN_S_TIMEOUTHHIGH_REAL                         FIO_ADDRESS(VIN,0x60009064) /* read/write */
#define REG_VIN_S_DEBUGFIFOCOUNT_REAL                       FIO_ADDRESS(VIN,0x60009080) /* read */
#define REG_VIN_S_DEBUGFIFODATA0_REAL                       FIO_ADDRESS(VIN,0x60009084) /* read */
#define REG_VIN_S_DEBUGFIFODATA1_REAL                       FIO_ADDRESS(VIN,0x60009088) /* read */
#define REG_VIN_S_DEBUGSTALL_REAL                           FIO_ADDRESS(VIN,0x6000908C) /* read */
#define REG_VIN_S_SLVSSATUS_REAL                            FIO_ADDRESS(VIN,0x60009090) /* read */

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
} GH_VIN_S_CONTROL_REAL_S;

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
} GH_VIN_S_INPUTCONFIG_REAL_S;

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
} GH_VIN_S_STATUS_REAL_S;

typedef union { /* VIN_S_Vwidth */
    U32 all;
    struct {
        U32 vsync_width                 : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_VWIDTH_REAL_S;

typedef union { /* VIN_S_Hwidth */
    U32 all;
    struct {
        U32 hsync_width                 : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HWIDTH_REAL_S;

typedef union { /* VIN_S_Htop */
    U32 all;
    struct {
        U32 hsync_top                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HTOP_REAL_S;

typedef union { /* VIN_S_Hbottom */
    U32 all;
    struct {
        U32 hsync_bottom                : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_HBOTTOM_REAL_S;

typedef union { /* VIN_S_V */
    U32 all;
    struct {
        U32 num_lines                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_V_REAL_S;

typedef union { /* VIN_S_H */
    U32 all;
    struct {
        U32 num_cols                    : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_H_REAL_S;

typedef union { /* VIN_S_MinV */
    U32 all;
    struct {
        U32 min_num_lines               : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_MINV_REAL_S;

typedef union { /* VIN_S_MinH */
    U32 all;
    struct {
        U32 min_num_fields              : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_MINH_REAL_S;

typedef union { /* VIN_S_Trigger0Start */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32 pol                         : 1;
        U32 enable                      : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TRIGGER0START_REAL_S;

typedef union { /* VIN_S_Trigger0End */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_TRIGGER0END_REAL_S;

typedef union { /* VIN_S_Trigger1Start */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32 pol                         : 1;
        U32 enable                      : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TRIGGER1START_REAL_S;

typedef union { /* VIN_S_Trigger1End */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_TRIGGER1END_REAL_S;

typedef union { /* VIN_S_VoutStart0 */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 1;
        U32 disable_field_check         : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_VOUTSTART0_REAL_S;

typedef union { /* VIN_S_VoutStart1 */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 1;
        U32 disable_field_check         : 1;
        U32                             : 16;
    } bitc;
} GH_VIN_S_VOUTSTART1_REAL_S;

typedef union { /* VIN_S_CapStartV */
    U32 all;
    struct {
        U32 startline                   : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPSTARTV_REAL_S;

typedef union { /* VIN_S_CapStartH */
    U32 all;
    struct {
        U32 startcol                    : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPSTARTH_REAL_S;

typedef union { /* VIN_S_CapEndV */
    U32 all;
    struct {
        U32 endline                     : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPENDV_REAL_S;

typedef union { /* VIN_S_CapEndH */
    U32 all;
    struct {
        U32 endcol                      : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_CAPENDH_REAL_S;

typedef union { /* VIN_S_BlankLengthH */
    U32 all;
    struct {
        U32 blank_length                : 14;
        U32                             : 18;
    } bitc;
} GH_VIN_S_BLANKLENGTHH_REAL_S;

typedef union { /* VIN_S_TimeoutVLow */
    U32 all;
    struct {
        U32 vsync_timeout_low           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTVLOW_REAL_S;

typedef union { /* VIN_S_TimeoutVHigh */
    U32 all;
    struct {
        U32 vsync_timeout_high          : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTVHIGH_REAL_S;

typedef union { /* VIN_S_TimeoutHLow */
    U32 all;
    struct {
        U32 hsync_timeout_low           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTHLOW_REAL_S;

typedef union { /* VIN_S_TimeoutHHigh */
    U32 all;
    struct {
        U32 hsync_timeout_high          : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_TIMEOUTHHIGH_REAL_S;

typedef union { /* VIN_S_debugFifoCount */
    U32 all;
    struct {
        U32 num_words_in_fifo           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFOCOUNT_REAL_S;

typedef union { /* VIN_S_debugFifoData0 */
    U32 all;
    struct {
        U32 pixel_0_read_data           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFODATA0_REAL_S;

typedef union { /* VIN_S_debugFifoData1 */
    U32 all;
    struct {
        U32 pixel_1_read_data           : 16;
        U32                             : 16;
    } bitc;
} GH_VIN_S_DEBUGFIFODATA1_REAL_S;

typedef union { /* VIN_S_debugStall */
    U32 all;
    struct {
        U32 output_interface_stall      : 1;
        U32                             : 31;
    } bitc;
} GH_VIN_S_DEBUGSTALL_REAL_S;

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
} GH_VIN_S_SLVSSATUS_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* register VIN_S_Control (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Control(U32 data)
{
    GH_VIN_S_CONTROL_REAL_S real;
    GH_VIN_S_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.enable = dummy.bitc.enable;
    real.bitc.win_en = dummy.bitc.win_en;
    real.bitc.data_edge = dummy.bitc.data_edge;
    real.bitc.slave_mode_enable = dummy.bitc.slave_mode_enable;
    real.bitc.master_mode_enable = dummy.bitc.master_mode_enable;
    real.bitc.emb_sync = dummy.bitc.emb_sync;
    real.bitc.emb_sync_mode = dummy.bitc.emb_sync_mode;
    real.bitc.emb_sync_loc = dummy.bitc.emb_sync_loc;
    real.bitc.vs_pol = dummy.bitc.vs_pol;
    real.bitc.hs_pol = dummy.bitc.hs_pol;
    real.bitc.field0_pol = dummy.bitc.field0_pol;
    real.bitc.sony_field_mode = dummy.bitc.sony_field_mode;
    real.bitc.ecc_enable = dummy.bitc.ecc_enable;
    real.bitc.hsync_mask = dummy.bitc.hsync_mask;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Control(void)
{
    GH_VIN_S_CONTROL_REAL_S real;
    GH_VIN_S_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    dummy.bitc.enable = real.bitc.enable;
    dummy.bitc.win_en = real.bitc.win_en;
    dummy.bitc.data_edge = real.bitc.data_edge;
    dummy.bitc.slave_mode_enable = real.bitc.slave_mode_enable;
    dummy.bitc.master_mode_enable = real.bitc.master_mode_enable;
    dummy.bitc.emb_sync = real.bitc.emb_sync;
    dummy.bitc.emb_sync_mode = real.bitc.emb_sync_mode;
    dummy.bitc.emb_sync_loc = real.bitc.emb_sync_loc;
    dummy.bitc.vs_pol = real.bitc.vs_pol;
    dummy.bitc.hs_pol = real.bitc.hs_pol;
    dummy.bitc.field0_pol = real.bitc.field0_pol;
    dummy.bitc.sony_field_mode = real.bitc.sony_field_mode;
    dummy.bitc.ecc_enable = real.bitc.ecc_enable;
    dummy.bitc.hsync_mask = real.bitc.hsync_mask;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Control_enable(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_enable(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}
GH_INLINE void GH_VIN_set_S_Control_win_en(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.win_en = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_win_en(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.win_en;
}
GH_INLINE void GH_VIN_set_S_Control_data_edge(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.data_edge = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_data_edge(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data_edge;
}
GH_INLINE void GH_VIN_set_S_Control_slave_mode_enable(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.slave_mode_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_slave_mode_enable(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slave_mode_enable;
}
GH_INLINE void GH_VIN_set_S_Control_master_mode_enable(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.master_mode_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_master_mode_enable(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.master_mode_enable;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.emb_sync = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.emb_sync;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync_mode(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.emb_sync_mode = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync_mode(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.emb_sync_mode;
}
GH_INLINE void GH_VIN_set_S_Control_emb_sync_loc(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.emb_sync_loc = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_emb_sync_loc(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.emb_sync_loc;
}
GH_INLINE void GH_VIN_set_S_Control_vs_pol(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.vs_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_vs_pol(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vs_pol;
}
GH_INLINE void GH_VIN_set_S_Control_hs_pol(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.hs_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_hs_pol(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hs_pol;
}
GH_INLINE void GH_VIN_set_S_Control_field0_pol(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.field0_pol = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_field0_pol(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.field0_pol;
}
GH_INLINE void GH_VIN_set_S_Control_sony_field_mode(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.sony_field_mode = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_sony_field_mode(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sony_field_mode;
}
GH_INLINE void GH_VIN_set_S_Control_ecc_enable(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.ecc_enable = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_ecc_enable(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ecc_enable;
}
GH_INLINE void GH_VIN_set_S_Control_hsync_mask(U8 data)
{
    GH_VIN_S_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CONTROL_REAL;
    d.bitc.hsync_mask = data;
    *(volatile U32 *)REG_VIN_S_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Control_hsync_mask(void)
{
    GH_VIN_S_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_mask;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_InputConfig (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_InputConfig(U32 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S real;
    GH_VIN_S_INPUTCONFIG_S dummy;
    dummy.all = data ;
    real.bitc.pad_type = dummy.bitc.pad_type;
    real.bitc.data_rate = dummy.bitc.data_rate;
    real.bitc.data_width = dummy.bitc.data_width;
    real.bitc.input_source = dummy.bitc.input_source;
    real.bitc.rgb_yuv = dummy.bitc.rgb_yuv;
    real.bitc.pixel_data_width = dummy.bitc.pixel_data_width;
    real.bitc.yuv_input_order = dummy.bitc.yuv_input_order;
    real.bitc.slvs_num_lanes = dummy.bitc.slvs_num_lanes;
    real.bitc.serial_sensor_interface_mode = dummy.bitc.serial_sensor_interface_mode;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_InputConfig(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S real;
    GH_VIN_S_INPUTCONFIG_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    dummy.bitc.pad_type = real.bitc.pad_type;
    dummy.bitc.data_rate = real.bitc.data_rate;
    dummy.bitc.data_width = real.bitc.data_width;
    dummy.bitc.input_source = real.bitc.input_source;
    dummy.bitc.rgb_yuv = real.bitc.rgb_yuv;
    dummy.bitc.pixel_data_width = real.bitc.pixel_data_width;
    dummy.bitc.yuv_input_order = real.bitc.yuv_input_order;
    dummy.bitc.slvs_num_lanes = real.bitc.slvs_num_lanes;
    dummy.bitc.serial_sensor_interface_mode = real.bitc.serial_sensor_interface_mode;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_InputConfig_pad_type(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.pad_type = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_pad_type(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pad_type;
}
GH_INLINE void GH_VIN_set_S_InputConfig_data_rate(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.data_rate = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_data_rate(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data_rate;
}
GH_INLINE void GH_VIN_set_S_InputConfig_data_width(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.data_width = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_data_width(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.data_width;
}
GH_INLINE void GH_VIN_set_S_InputConfig_input_source(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.input_source = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_input_source(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.input_source;
}
GH_INLINE void GH_VIN_set_S_InputConfig_rgb_yuv(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.rgb_yuv = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_rgb_yuv(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.rgb_yuv;
}
GH_INLINE void GH_VIN_set_S_InputConfig_pixel_data_width(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.pixel_data_width = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_pixel_data_width(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pixel_data_width;
}
GH_INLINE void GH_VIN_set_S_InputConfig_yuv_input_order(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.yuv_input_order = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_yuv_input_order(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.yuv_input_order;
}
GH_INLINE void GH_VIN_set_S_InputConfig_slvs_num_lanes(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.slvs_num_lanes = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_slvs_num_lanes(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slvs_num_lanes;
}
GH_INLINE void GH_VIN_set_S_InputConfig_serial_sensor_interface_mode(U8 data)
{
    GH_VIN_S_INPUTCONFIG_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL;
    d.bitc.serial_sensor_interface_mode = data;
    *(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_InputConfig_serial_sensor_interface_mode(void)
{
    GH_VIN_S_INPUTCONFIG_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_INPUTCONFIG_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.serial_sensor_interface_mode;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Status (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Status(U32 data)
{
    GH_VIN_S_STATUS_REAL_S real;
    GH_VIN_S_STATUS_S dummy;
    dummy.all = data ;
    real.bitc.vsync = dummy.bitc.vsync;
    real.bitc.trig0 = dummy.bitc.trig0;
    real.bitc.trig1 = dummy.bitc.trig1;
    real.bitc.ovfl = dummy.bitc.ovfl;
    real.bitc.shortl = dummy.bitc.shortl;
    real.bitc.shortf = dummy.bitc.shortf;
    real.bitc.field = dummy.bitc.field;
    real.bitc.no_hsync_detected = dummy.bitc.no_hsync_detected;
    real.bitc.no_vsync_detected = dummy.bitc.no_vsync_detected;
    real.bitc.idsp_ahb_vsync = dummy.bitc.idsp_ahb_vsync;
    real.bitc.idsp_ahb_mst_vsync = dummy.bitc.idsp_ahb_mst_vsync;
    real.bitc.idsp_ahb_last_pixel = dummy.bitc.idsp_ahb_last_pixel;
    real.bitc.ecc_uncorrectable = dummy.bitc.ecc_uncorrectable;
    real.bitc.program_error = dummy.bitc.program_error;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Status(void)
{
    GH_VIN_S_STATUS_REAL_S real;
    GH_VIN_S_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    dummy.bitc.vsync = real.bitc.vsync;
    dummy.bitc.trig0 = real.bitc.trig0;
    dummy.bitc.trig1 = real.bitc.trig1;
    dummy.bitc.ovfl = real.bitc.ovfl;
    dummy.bitc.shortl = real.bitc.shortl;
    dummy.bitc.shortf = real.bitc.shortf;
    dummy.bitc.field = real.bitc.field;
    dummy.bitc.no_hsync_detected = real.bitc.no_hsync_detected;
    dummy.bitc.no_vsync_detected = real.bitc.no_vsync_detected;
    dummy.bitc.idsp_ahb_vsync = real.bitc.idsp_ahb_vsync;
    dummy.bitc.idsp_ahb_mst_vsync = real.bitc.idsp_ahb_mst_vsync;
    dummy.bitc.idsp_ahb_last_pixel = real.bitc.idsp_ahb_last_pixel;
    dummy.bitc.ecc_uncorrectable = real.bitc.ecc_uncorrectable;
    dummy.bitc.program_error = real.bitc.program_error;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Status_vsync(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_vsync(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync;
}
GH_INLINE void GH_VIN_set_S_Status_trig0(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.trig0 = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_trig0(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trig0;
}
GH_INLINE void GH_VIN_set_S_Status_trig1(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.trig1 = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_trig1(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.trig1;
}
GH_INLINE void GH_VIN_set_S_Status_ovfl(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.ovfl = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_ovfl(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ovfl;
}
GH_INLINE void GH_VIN_set_S_Status_shortl(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.shortl = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_shortl(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shortl;
}
GH_INLINE void GH_VIN_set_S_Status_shortf(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.shortf = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_shortf(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.shortf;
}
GH_INLINE void GH_VIN_set_S_Status_field(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.field = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_field(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.field;
}
GH_INLINE void GH_VIN_set_S_Status_no_hsync_detected(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.no_hsync_detected = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_no_hsync_detected(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.no_hsync_detected;
}
GH_INLINE void GH_VIN_set_S_Status_no_vsync_detected(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.no_vsync_detected = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_no_vsync_detected(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.no_vsync_detected;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_vsync(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.idsp_ahb_vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_vsync(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.idsp_ahb_vsync;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_mst_vsync(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.idsp_ahb_mst_vsync = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_mst_vsync(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.idsp_ahb_mst_vsync;
}
GH_INLINE void GH_VIN_set_S_Status_idsp_ahb_last_pixel(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.idsp_ahb_last_pixel = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_idsp_ahb_last_pixel(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.idsp_ahb_last_pixel;
}
GH_INLINE void GH_VIN_set_S_Status_ecc_uncorrectable(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.ecc_uncorrectable = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_ecc_uncorrectable(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.ecc_uncorrectable;
}
GH_INLINE void GH_VIN_set_S_Status_program_error(U8 data)
{
    GH_VIN_S_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_STATUS_REAL;
    d.bitc.program_error = data;
    *(volatile U32 *)REG_VIN_S_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Status_program_error(void)
{
    GH_VIN_S_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.program_error;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Vwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Vwidth(U32 data)
{
    GH_VIN_S_VWIDTH_REAL_S real;
    GH_VIN_S_VWIDTH_S dummy;
    dummy.all = data ;
    real.bitc.vsync_width = dummy.bitc.vsync_width;
    *(volatile U32 *)REG_VIN_S_VWIDTH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Vwidth(void)
{
    GH_VIN_S_VWIDTH_REAL_S real;
    GH_VIN_S_VWIDTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_VWIDTH_REAL);

    dummy.bitc.vsync_width = real.bitc.vsync_width;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Vwidth_vsync_width(U16 data)
{
    GH_VIN_S_VWIDTH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VWIDTH_REAL;
    d.bitc.vsync_width = data;
    *(volatile U32 *)REG_VIN_S_VWIDTH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Vwidth_vsync_width(void)
{
    GH_VIN_S_VWIDTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VWIDTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_width;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hwidth (read/write)                                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Hwidth(U32 data)
{
    GH_VIN_S_HWIDTH_REAL_S real;
    GH_VIN_S_HWIDTH_S dummy;
    dummy.all = data ;
    real.bitc.hsync_width = dummy.bitc.hsync_width;
    *(volatile U32 *)REG_VIN_S_HWIDTH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Hwidth(void)
{
    GH_VIN_S_HWIDTH_REAL_S real;
    GH_VIN_S_HWIDTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_HWIDTH_REAL);

    dummy.bitc.hsync_width = real.bitc.hsync_width;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Hwidth_hsync_width(U16 data)
{
    GH_VIN_S_HWIDTH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HWIDTH_REAL;
    d.bitc.hsync_width = data;
    *(volatile U32 *)REG_VIN_S_HWIDTH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Hwidth_hsync_width(void)
{
    GH_VIN_S_HWIDTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HWIDTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_width;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Htop (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Htop(U32 data)
{
    GH_VIN_S_HTOP_REAL_S real;
    GH_VIN_S_HTOP_S dummy;
    dummy.all = data ;
    real.bitc.hsync_top = dummy.bitc.hsync_top;
    *(volatile U32 *)REG_VIN_S_HTOP_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Htop(void)
{
    GH_VIN_S_HTOP_REAL_S real;
    GH_VIN_S_HTOP_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_HTOP_REAL);

    dummy.bitc.hsync_top = real.bitc.hsync_top;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Htop_hsync_top(U16 data)
{
    GH_VIN_S_HTOP_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HTOP_REAL;
    d.bitc.hsync_top = data;
    *(volatile U32 *)REG_VIN_S_HTOP_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Htop_hsync_top(void)
{
    GH_VIN_S_HTOP_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HTOP_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_top;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Hbottom (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Hbottom(U32 data)
{
    GH_VIN_S_HBOTTOM_REAL_S real;
    GH_VIN_S_HBOTTOM_S dummy;
    dummy.all = data ;
    real.bitc.hsync_bottom = dummy.bitc.hsync_bottom;
    *(volatile U32 *)REG_VIN_S_HBOTTOM_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Hbottom(void)
{
    GH_VIN_S_HBOTTOM_REAL_S real;
    GH_VIN_S_HBOTTOM_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_HBOTTOM_REAL);

    dummy.bitc.hsync_bottom = real.bitc.hsync_bottom;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Hbottom_hsync_bottom(U16 data)
{
    GH_VIN_S_HBOTTOM_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_HBOTTOM_REAL;
    d.bitc.hsync_bottom = data;
    *(volatile U32 *)REG_VIN_S_HBOTTOM_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Hbottom_hsync_bottom(void)
{
    GH_VIN_S_HBOTTOM_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_HBOTTOM_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_bottom;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_V (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_V(U32 data)
{
    GH_VIN_S_V_REAL_S real;
    GH_VIN_S_V_S dummy;
    dummy.all = data ;
    real.bitc.num_lines = dummy.bitc.num_lines;
    *(volatile U32 *)REG_VIN_S_V_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_V(void)
{
    GH_VIN_S_V_REAL_S real;
    GH_VIN_S_V_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_V_REAL);

    dummy.bitc.num_lines = real.bitc.num_lines;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_V_num_lines(U16 data)
{
    GH_VIN_S_V_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_V_REAL;
    d.bitc.num_lines = data;
    *(volatile U32 *)REG_VIN_S_V_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_V_num_lines(void)
{
    GH_VIN_S_V_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_V_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.num_lines;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_H (read/write)                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_H(U32 data)
{
    GH_VIN_S_H_REAL_S real;
    GH_VIN_S_H_S dummy;
    dummy.all = data ;
    real.bitc.num_cols = dummy.bitc.num_cols;
    *(volatile U32 *)REG_VIN_S_H_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_H(void)
{
    GH_VIN_S_H_REAL_S real;
    GH_VIN_S_H_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_H_REAL);

    dummy.bitc.num_cols = real.bitc.num_cols;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_H_num_cols(U16 data)
{
    GH_VIN_S_H_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_H_REAL;
    d.bitc.num_cols = data;
    *(volatile U32 *)REG_VIN_S_H_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_H_num_cols(void)
{
    GH_VIN_S_H_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_H_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.num_cols;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinV (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_MinV(U32 data)
{
    GH_VIN_S_MINV_REAL_S real;
    GH_VIN_S_MINV_S dummy;
    dummy.all = data ;
    real.bitc.min_num_lines = dummy.bitc.min_num_lines;
    *(volatile U32 *)REG_VIN_S_MINV_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_MinV(void)
{
    GH_VIN_S_MINV_REAL_S real;
    GH_VIN_S_MINV_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_MINV_REAL);

    dummy.bitc.min_num_lines = real.bitc.min_num_lines;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_MinV_min_num_lines(U16 data)
{
    GH_VIN_S_MINV_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_MINV_REAL;
    d.bitc.min_num_lines = data;
    *(volatile U32 *)REG_VIN_S_MINV_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_MinV_min_num_lines(void)
{
    GH_VIN_S_MINV_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_MINV_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.min_num_lines;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_MinH (read/write)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_MinH(U32 data)
{
    GH_VIN_S_MINH_REAL_S real;
    GH_VIN_S_MINH_S dummy;
    dummy.all = data ;
    real.bitc.min_num_fields = dummy.bitc.min_num_fields;
    *(volatile U32 *)REG_VIN_S_MINH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_MinH(void)
{
    GH_VIN_S_MINH_REAL_S real;
    GH_VIN_S_MINH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_MINH_REAL);

    dummy.bitc.min_num_fields = real.bitc.min_num_fields;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_MinH_min_num_fields(U16 data)
{
    GH_VIN_S_MINH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_MINH_REAL;
    d.bitc.min_num_fields = data;
    *(volatile U32 *)REG_VIN_S_MINH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_MinH_min_num_fields(void)
{
    GH_VIN_S_MINH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_MINH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.min_num_fields;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Trigger0Start(U32 data)
{
    GH_VIN_S_TRIGGER0START_REAL_S real;
    GH_VIN_S_TRIGGER0START_S dummy;
    dummy.all = data ;
    real.bitc.startline = dummy.bitc.startline;
    real.bitc.pol = dummy.bitc.pol;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Trigger0Start(void)
{
    GH_VIN_S_TRIGGER0START_REAL_S real;
    GH_VIN_S_TRIGGER0START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL);

    dummy.bitc.startline = real.bitc.startline;
    dummy.bitc.pol = real.bitc.pol;
    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_startline(U16 data)
{
    GH_VIN_S_TRIGGER0START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Trigger0Start_startline(void)
{
    GH_VIN_S_TRIGGER0START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_pol(U8 data)
{
    GH_VIN_S_TRIGGER0START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL;
    d.bitc.pol = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Trigger0Start_pol(void)
{
    GH_VIN_S_TRIGGER0START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pol;
}
GH_INLINE void GH_VIN_set_S_Trigger0Start_enable(U8 data)
{
    GH_VIN_S_TRIGGER0START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Trigger0Start_enable(void)
{
    GH_VIN_S_TRIGGER0START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger0End (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Trigger0End(U32 data)
{
    GH_VIN_S_TRIGGER0END_REAL_S real;
    GH_VIN_S_TRIGGER0END_S dummy;
    dummy.all = data ;
    real.bitc.endline = dummy.bitc.endline;
    *(volatile U32 *)REG_VIN_S_TRIGGER0END_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Trigger0End(void)
{
    GH_VIN_S_TRIGGER0END_REAL_S real;
    GH_VIN_S_TRIGGER0END_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TRIGGER0END_REAL);

    dummy.bitc.endline = real.bitc.endline;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Trigger0End_endline(U16 data)
{
    GH_VIN_S_TRIGGER0END_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER0END_REAL;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER0END_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Trigger0End_endline(void)
{
    GH_VIN_S_TRIGGER0END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER0END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.endline;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1Start (read/write)                                  */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Trigger1Start(U32 data)
{
    GH_VIN_S_TRIGGER1START_REAL_S real;
    GH_VIN_S_TRIGGER1START_S dummy;
    dummy.all = data ;
    real.bitc.startline = dummy.bitc.startline;
    real.bitc.pol = dummy.bitc.pol;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Trigger1Start(void)
{
    GH_VIN_S_TRIGGER1START_REAL_S real;
    GH_VIN_S_TRIGGER1START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL);

    dummy.bitc.startline = real.bitc.startline;
    dummy.bitc.pol = real.bitc.pol;
    dummy.bitc.enable = real.bitc.enable;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_startline(U16 data)
{
    GH_VIN_S_TRIGGER1START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Trigger1Start_startline(void)
{
    GH_VIN_S_TRIGGER1START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_pol(U8 data)
{
    GH_VIN_S_TRIGGER1START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL;
    d.bitc.pol = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Trigger1Start_pol(void)
{
    GH_VIN_S_TRIGGER1START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pol;
}
GH_INLINE void GH_VIN_set_S_Trigger1Start_enable(U8 data)
{
    GH_VIN_S_TRIGGER1START_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL;
    d.bitc.enable = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_Trigger1Start_enable(void)
{
    GH_VIN_S_TRIGGER1START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_Trigger1End (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_Trigger1End(U32 data)
{
    GH_VIN_S_TRIGGER1END_REAL_S real;
    GH_VIN_S_TRIGGER1END_S dummy;
    dummy.all = data ;
    real.bitc.endline = dummy.bitc.endline;
    *(volatile U32 *)REG_VIN_S_TRIGGER1END_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_Trigger1End(void)
{
    GH_VIN_S_TRIGGER1END_REAL_S real;
    GH_VIN_S_TRIGGER1END_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TRIGGER1END_REAL);

    dummy.bitc.endline = real.bitc.endline;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_Trigger1End_endline(U16 data)
{
    GH_VIN_S_TRIGGER1END_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TRIGGER1END_REAL;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_TRIGGER1END_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_Trigger1End_endline(void)
{
    GH_VIN_S_TRIGGER1END_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TRIGGER1END_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.endline;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart0 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_VoutStart0(U32 data)
{
    GH_VIN_S_VOUTSTART0_REAL_S real;
    GH_VIN_S_VOUTSTART0_S dummy;
    dummy.all = data ;
    real.bitc.startline = dummy.bitc.startline;
    real.bitc.disable_field_check = dummy.bitc.disable_field_check;
    *(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_VoutStart0(void)
{
    GH_VIN_S_VOUTSTART0_REAL_S real;
    GH_VIN_S_VOUTSTART0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL);

    dummy.bitc.startline = real.bitc.startline;
    dummy.bitc.disable_field_check = real.bitc.disable_field_check;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_VoutStart0_startline(U16 data)
{
    GH_VIN_S_VOUTSTART0_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_VoutStart0_startline(void)
{
    GH_VIN_S_VOUTSTART0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_VoutStart0_disable_field_check(U8 data)
{
    GH_VIN_S_VOUTSTART0_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL;
    d.bitc.disable_field_check = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_VoutStart0_disable_field_check(void)
{
    GH_VIN_S_VOUTSTART0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.disable_field_check;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_VoutStart1 (read/write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_VoutStart1(U32 data)
{
    GH_VIN_S_VOUTSTART1_REAL_S real;
    GH_VIN_S_VOUTSTART1_S dummy;
    dummy.all = data ;
    real.bitc.startline = dummy.bitc.startline;
    real.bitc.disable_field_check = dummy.bitc.disable_field_check;
    *(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_VoutStart1(void)
{
    GH_VIN_S_VOUTSTART1_REAL_S real;
    GH_VIN_S_VOUTSTART1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL);

    dummy.bitc.startline = real.bitc.startline;
    dummy.bitc.disable_field_check = real.bitc.disable_field_check;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_VoutStart1_startline(U16 data)
{
    GH_VIN_S_VOUTSTART1_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_VoutStart1_startline(void)
{
    GH_VIN_S_VOUTSTART1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startline;
}
GH_INLINE void GH_VIN_set_S_VoutStart1_disable_field_check(U8 data)
{
    GH_VIN_S_VOUTSTART1_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL;
    d.bitc.disable_field_check = data;
    *(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL = d.all;
}
GH_INLINE U8   GH_VIN_get_S_VoutStart1_disable_field_check(void)
{
    GH_VIN_S_VOUTSTART1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_VOUTSTART1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.disable_field_check;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartV (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_CapStartV(U32 data)
{
    GH_VIN_S_CAPSTARTV_REAL_S real;
    GH_VIN_S_CAPSTARTV_S dummy;
    dummy.all = data ;
    real.bitc.startline = dummy.bitc.startline;
    *(volatile U32 *)REG_VIN_S_CAPSTARTV_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_CapStartV(void)
{
    GH_VIN_S_CAPSTARTV_REAL_S real;
    GH_VIN_S_CAPSTARTV_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_CAPSTARTV_REAL);

    dummy.bitc.startline = real.bitc.startline;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_CapStartV_startline(U16 data)
{
    GH_VIN_S_CAPSTARTV_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPSTARTV_REAL;
    d.bitc.startline = data;
    *(volatile U32 *)REG_VIN_S_CAPSTARTV_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_CapStartV_startline(void)
{
    GH_VIN_S_CAPSTARTV_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTV_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startline;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapStartH (read/write)                                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_CapStartH(U32 data)
{
    GH_VIN_S_CAPSTARTH_REAL_S real;
    GH_VIN_S_CAPSTARTH_S dummy;
    dummy.all = data ;
    real.bitc.startcol = dummy.bitc.startcol;
    *(volatile U32 *)REG_VIN_S_CAPSTARTH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_CapStartH(void)
{
    GH_VIN_S_CAPSTARTH_REAL_S real;
    GH_VIN_S_CAPSTARTH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_CAPSTARTH_REAL);

    dummy.bitc.startcol = real.bitc.startcol;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_CapStartH_startcol(U16 data)
{
    GH_VIN_S_CAPSTARTH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPSTARTH_REAL;
    d.bitc.startcol = data;
    *(volatile U32 *)REG_VIN_S_CAPSTARTH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_CapStartH_startcol(void)
{
    GH_VIN_S_CAPSTARTH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPSTARTH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.startcol;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndV (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_CapEndV(U32 data)
{
    GH_VIN_S_CAPENDV_REAL_S real;
    GH_VIN_S_CAPENDV_S dummy;
    dummy.all = data ;
    real.bitc.endline = dummy.bitc.endline;
    *(volatile U32 *)REG_VIN_S_CAPENDV_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_CapEndV(void)
{
    GH_VIN_S_CAPENDV_REAL_S real;
    GH_VIN_S_CAPENDV_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_CAPENDV_REAL);

    dummy.bitc.endline = real.bitc.endline;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_CapEndV_endline(U16 data)
{
    GH_VIN_S_CAPENDV_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPENDV_REAL;
    d.bitc.endline = data;
    *(volatile U32 *)REG_VIN_S_CAPENDV_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_CapEndV_endline(void)
{
    GH_VIN_S_CAPENDV_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDV_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.endline;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_CapEndH (read/write)                                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_CapEndH(U32 data)
{
    GH_VIN_S_CAPENDH_REAL_S real;
    GH_VIN_S_CAPENDH_S dummy;
    dummy.all = data ;
    real.bitc.endcol = dummy.bitc.endcol;
    *(volatile U32 *)REG_VIN_S_CAPENDH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_CapEndH(void)
{
    GH_VIN_S_CAPENDH_REAL_S real;
    GH_VIN_S_CAPENDH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_CAPENDH_REAL);

    dummy.bitc.endcol = real.bitc.endcol;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_CapEndH_endcol(U16 data)
{
    GH_VIN_S_CAPENDH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_CAPENDH_REAL;
    d.bitc.endcol = data;
    *(volatile U32 *)REG_VIN_S_CAPENDH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_CapEndH_endcol(void)
{
    GH_VIN_S_CAPENDH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_CAPENDH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.endcol;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_BlankLengthH (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_BlankLengthH(U32 data)
{
    GH_VIN_S_BLANKLENGTHH_REAL_S real;
    GH_VIN_S_BLANKLENGTHH_S dummy;
    dummy.all = data ;
    real.bitc.blank_length = dummy.bitc.blank_length;
    *(volatile U32 *)REG_VIN_S_BLANKLENGTHH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_BlankLengthH(void)
{
    GH_VIN_S_BLANKLENGTHH_REAL_S real;
    GH_VIN_S_BLANKLENGTHH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_BLANKLENGTHH_REAL);

    dummy.bitc.blank_length = real.bitc.blank_length;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_BlankLengthH_blank_length(U16 data)
{
    GH_VIN_S_BLANKLENGTHH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_BLANKLENGTHH_REAL;
    d.bitc.blank_length = data;
    *(volatile U32 *)REG_VIN_S_BLANKLENGTHH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_BlankLengthH_blank_length(void)
{
    GH_VIN_S_BLANKLENGTHH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_BLANKLENGTHH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.blank_length;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_TimeoutVLow(U32 data)
{
    GH_VIN_S_TIMEOUTVLOW_REAL_S real;
    GH_VIN_S_TIMEOUTVLOW_S dummy;
    dummy.all = data ;
    real.bitc.vsync_timeout_low = dummy.bitc.vsync_timeout_low;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_TimeoutVLow(void)
{
    GH_VIN_S_TIMEOUTVLOW_REAL_S real;
    GH_VIN_S_TIMEOUTVLOW_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TIMEOUTVLOW_REAL);

    dummy.bitc.vsync_timeout_low = real.bitc.vsync_timeout_low;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_TimeoutVLow_vsync_timeout_low(U16 data)
{
    GH_VIN_S_TIMEOUTVLOW_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW_REAL;
    d.bitc.vsync_timeout_low = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVLOW_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_TimeoutVLow_vsync_timeout_low(void)
{
    GH_VIN_S_TIMEOUTVLOW_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVLOW_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_timeout_low;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutVHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_TimeoutVHigh(U32 data)
{
    GH_VIN_S_TIMEOUTVHIGH_REAL_S real;
    GH_VIN_S_TIMEOUTVHIGH_S dummy;
    dummy.all = data ;
    real.bitc.vsync_timeout_high = dummy.bitc.vsync_timeout_high;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_TimeoutVHigh(void)
{
    GH_VIN_S_TIMEOUTVHIGH_REAL_S real;
    GH_VIN_S_TIMEOUTVHIGH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH_REAL);

    dummy.bitc.vsync_timeout_high = real.bitc.vsync_timeout_high;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_TimeoutVHigh_vsync_timeout_high(U16 data)
{
    GH_VIN_S_TIMEOUTVHIGH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH_REAL;
    d.bitc.vsync_timeout_high = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_TimeoutVHigh_vsync_timeout_high(void)
{
    GH_VIN_S_TIMEOUTVHIGH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTVHIGH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_timeout_high;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHLow (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_TimeoutHLow(U32 data)
{
    GH_VIN_S_TIMEOUTHLOW_REAL_S real;
    GH_VIN_S_TIMEOUTHLOW_S dummy;
    dummy.all = data ;
    real.bitc.hsync_timeout_low = dummy.bitc.hsync_timeout_low;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_TimeoutHLow(void)
{
    GH_VIN_S_TIMEOUTHLOW_REAL_S real;
    GH_VIN_S_TIMEOUTHLOW_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TIMEOUTHLOW_REAL);

    dummy.bitc.hsync_timeout_low = real.bitc.hsync_timeout_low;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_TimeoutHLow_hsync_timeout_low(U16 data)
{
    GH_VIN_S_TIMEOUTHLOW_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW_REAL;
    d.bitc.hsync_timeout_low = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHLOW_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_TimeoutHLow_hsync_timeout_low(void)
{
    GH_VIN_S_TIMEOUTHLOW_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHLOW_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_timeout_low;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_TimeoutHHigh (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_set_S_TimeoutHHigh(U32 data)
{
    GH_VIN_S_TIMEOUTHHIGH_REAL_S real;
    GH_VIN_S_TIMEOUTHHIGH_S dummy;
    dummy.all = data ;
    real.bitc.hsync_timeout_high = dummy.bitc.hsync_timeout_high;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH_REAL = real.all;
}
GH_INLINE U32  GH_VIN_get_S_TimeoutHHigh(void)
{
    GH_VIN_S_TIMEOUTHHIGH_REAL_S real;
    GH_VIN_S_TIMEOUTHHIGH_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH_REAL);

    dummy.bitc.hsync_timeout_high = real.bitc.hsync_timeout_high;
    return dummy.all;
}
GH_INLINE void GH_VIN_set_S_TimeoutHHigh_hsync_timeout_high(U16 data)
{
    GH_VIN_S_TIMEOUTHHIGH_REAL_S d;
    d.all = *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH_REAL;
    d.bitc.hsync_timeout_high = data;
    *(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH_REAL = d.all;
}
GH_INLINE U16  GH_VIN_get_S_TimeoutHHigh_hsync_timeout_high(void)
{
    GH_VIN_S_TIMEOUTHHIGH_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_TIMEOUTHHIGH_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_timeout_high;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoCount (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIN_get_S_debugFifoCount(void)
{
    GH_VIN_S_DEBUGFIFOCOUNT_REAL_S real;
    GH_VIN_S_DEBUGFIFOCOUNT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_DEBUGFIFOCOUNT_REAL);

    dummy.bitc.num_words_in_fifo = real.bitc.num_words_in_fifo;
    return dummy.all;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoCount_num_words_in_fifo(void)
{
    GH_VIN_S_DEBUGFIFOCOUNT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFOCOUNT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.num_words_in_fifo;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData0 (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIN_get_S_debugFifoData0(void)
{
    GH_VIN_S_DEBUGFIFODATA0_REAL_S real;
    GH_VIN_S_DEBUGFIFODATA0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA0_REAL);

    dummy.bitc.pixel_0_read_data = real.bitc.pixel_0_read_data;
    return dummy.all;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoData0_pixel_0_read_data(void)
{
    GH_VIN_S_DEBUGFIFODATA0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pixel_0_read_data;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugFifoData1 (read)                                       */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIN_get_S_debugFifoData1(void)
{
    GH_VIN_S_DEBUGFIFODATA1_REAL_S real;
    GH_VIN_S_DEBUGFIFODATA1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA1_REAL);

    dummy.bitc.pixel_1_read_data = real.bitc.pixel_1_read_data;
    return dummy.all;
}
GH_INLINE U16  GH_VIN_get_S_debugFifoData1_pixel_1_read_data(void)
{
    GH_VIN_S_DEBUGFIFODATA1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGFIFODATA1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.pixel_1_read_data;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_debugStall (read)                                           */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIN_get_S_debugStall(void)
{
    GH_VIN_S_DEBUGSTALL_REAL_S real;
    GH_VIN_S_DEBUGSTALL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_DEBUGSTALL_REAL);

    dummy.bitc.output_interface_stall = real.bitc.output_interface_stall;
    return dummy.all;
}
GH_INLINE U8   GH_VIN_get_S_debugStall_output_interface_stall(void)
{
    GH_VIN_S_DEBUGSTALL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_DEBUGSTALL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.output_interface_stall;
}

/*----------------------------------------------------------------------------*/
/* register VIN_S_slvsSatus (read)                                            */
/*----------------------------------------------------------------------------*/
GH_INLINE U32  GH_VIN_get_S_slvsSatus(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S real;
    GH_VIN_S_SLVSSATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    dummy.bitc.slvs_lock_state = real.bitc.slvs_lock_state;
    dummy.bitc.detected_sync_code_match = real.bitc.detected_sync_code_match;
    dummy.bitc.detected_start_of_frame = real.bitc.detected_start_of_frame;
    dummy.bitc.detected_vsync = real.bitc.detected_vsync;
    dummy.bitc.detected_start_of_line = real.bitc.detected_start_of_line;
    dummy.bitc.valid_pixel_generated = real.bitc.valid_pixel_generated;
    dummy.bitc.end_of_line_generated = real.bitc.end_of_line_generated;
    dummy.bitc.corrected_error = real.bitc.corrected_error;
    return dummy.all;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_slvs_lock_state(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.slvs_lock_state;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_sync_code_match(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.detected_sync_code_match;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_start_of_frame(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.detected_start_of_frame;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_vsync(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.detected_vsync;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_detected_start_of_line(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.detected_start_of_line;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_valid_pixel_generated(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.valid_pixel_generated;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_end_of_line_generated(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_of_line_generated;
}
GH_INLINE U8   GH_VIN_get_S_slvsSatus_corrected_error(void)
{
    GH_VIN_S_SLVSSATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VIN_S_SLVSSATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.corrected_error;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VIN_init(void)
{
    GH_VIN_set_S_Control((U32)0x00000010);
    GH_VIN_set_S_InputConfig((U32)0x00000000);
    GH_VIN_set_S_Status((U32)0x00000000);
    GH_VIN_set_S_Vwidth((U32)0x00000000);
    GH_VIN_set_S_Hwidth((U32)0x00000000);
    GH_VIN_set_S_Htop((U32)0x00000000);
    GH_VIN_set_S_Hbottom((U32)0x00000000);
    GH_VIN_set_S_V((U32)0x00000000);
    GH_VIN_set_S_H((U32)0x00000000);
    GH_VIN_set_S_MinV((U32)0x00000000);
    GH_VIN_set_S_MinH((U32)0x00000000);
    GH_VIN_set_S_Trigger0Start((U32)0x00000000);
    GH_VIN_set_S_Trigger0End((U32)0x00000000);
    GH_VIN_set_S_Trigger1Start((U32)0x00000000);
    GH_VIN_set_S_Trigger1End((U32)0x00000000);
    GH_VIN_set_S_VoutStart0((U32)0x00000000);
    GH_VIN_set_S_VoutStart1((U32)0x00000000);
    GH_VIN_set_S_CapStartV((U32)0x00000000);
    GH_VIN_set_S_CapStartH((U32)0x00000000);
    GH_VIN_set_S_CapEndV((U32)0x00000000);
    GH_VIN_set_S_CapEndH((U32)0x00000000);
    GH_VIN_set_S_BlankLengthH((U32)0x00000000);
    GH_VIN_set_S_TimeoutVLow((U32)0x00000000);
    GH_VIN_set_S_TimeoutVHigh((U32)0x00000000);
    GH_VIN_set_S_TimeoutHLow((U32)0x00000000);
    GH_VIN_set_S_TimeoutHHigh((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

