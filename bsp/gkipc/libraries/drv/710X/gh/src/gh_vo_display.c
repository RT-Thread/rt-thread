/******************************************************************************
**
** \file      gh_vo_display.c
**
** \brief     VO Display access function.
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
#include "gh_vo_display.h"
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DISPLAY_CONTROL_REAL                         FIO_ADDRESS(VO_DISPLAY,0x60008600) /* read/write */
#define REG_VO_DISPLAY_STATUS_REAL                          FIO_ADDRESS(VO_DISPLAY,0x60008604) /* read/write */
#define REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL               FIO_ADDRESS(VO_DISPLAY,0x60008608) /* read/write */
#define REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL               FIO_ADDRESS(VO_DISPLAY,0x6000860C) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL      FIO_ADDRESS(VO_DISPLAY,0x60008610) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008614) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL      FIO_ADDRESS(VO_DISPLAY,0x60008618) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL             FIO_ADDRESS(VO_DISPLAY,0x6000861C) /* read/write */
#define REG_VO_DISPLAY_BACKGROUND_REAL                      FIO_ADDRESS(VO_DISPLAY,0x60008620) /* write */
#define REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL                  FIO_ADDRESS(VO_DISPLAY,0x60008624) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL           FIO_ADDRESS(VO_DISPLAY,0x60008628) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL           FIO_ADDRESS(VO_DISPLAY,0x6000862C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008630) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL           FIO_ADDRESS(VO_DISPLAY,0x60008634) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008638) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL                FIO_ADDRESS(VO_DISPLAY,0x6000863C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL           FIO_ADDRESS(VO_DISPLAY,0x60008640) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN0_REAL          FIO_ADDRESS(VO_DISPLAY,0x60008644) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN1_REAL          FIO_ADDRESS(VO_DISPLAY,0x60008648) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN2_REAL          FIO_ADDRESS(VO_DISPLAY,0x6000864C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN3_REAL          FIO_ADDRESS(VO_DISPLAY,0x60008650) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008654) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008658) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL             FIO_ADDRESS(VO_DISPLAY,0x6000865C) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008660) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008664) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008668) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL             FIO_ADDRESS(VO_DISPLAY,0x6000866C) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008670) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008674) /* write */
#define REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008678) /* read/write */
#define REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL            FIO_ADDRESS(VO_DISPLAY,0x6000867C) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL            FIO_ADDRESS(VO_DISPLAY,0x60008680) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008684) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL            FIO_ADDRESS(VO_DISPLAY,0x60008688) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL              FIO_ADDRESS(VO_DISPLAY,0x6000868C) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008690) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL                  FIO_ADDRESS(VO_DISPLAY,0x60008694) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_COL_REAL                  FIO_ADDRESS(VO_DISPLAY,0x60008698) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_DATA_REAL                 FIO_ADDRESS(VO_DISPLAY,0x6000869C) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086CC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086D0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086D4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086D8) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086DC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL              FIO_ADDRESS(VO_DISPLAY,0x600086E0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086E4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086E8) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086EC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086F0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086F4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL            FIO_ADDRESS(VO_DISPLAY,0x600086F8) /* write */
#define REG_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL               FIO_ADDRESS(VO_DISPLAY,0x600086FC) /* write */
#define REG_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL            FIO_ADDRESS(VO_DISPLAY,0x60008700) /* write */
#define REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008704) /* read/write */
#define REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008708) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL              FIO_ADDRESS(VO_DISPLAY,0x6000870C) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008710) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008714) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008718) /* read/write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL                FIO_ADDRESS(VO_DISPLAY,0x6000871C) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008720) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008724) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008728) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL                FIO_ADDRESS(VO_DISPLAY,0x6000872C) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008730) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008734) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL                FIO_ADDRESS(VO_DISPLAY,0x60008738) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL                FIO_ADDRESS(VO_DISPLAY,0x6000873C) /* write */
#define REG_VO_DISPLAY_DIGITAL_DITHER_SETTINGS_REAL         FIO_ADDRESS(VO_DISPLAY,0x60008754) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_DITHER_SEED_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008758) /* read/write */
#define REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL                  FIO_ADDRESS(VO_DISPLAY,0x6000875C) /* read/write */
#define REG_VO_DISPLAY_INPUT_STREAM_ENABLES_REAL            FIO_ADDRESS(VO_DISPLAY,0x60008760) /* read/write */
#define REG_VO_DISPLAY_INPUT_SYNC_CONTROL_REAL              FIO_ADDRESS(VO_DISPLAY,0x60008764) /* read/write */
#define REG_VO_DISPLAY_OUTPUT_SYNC_CONTROL_REAL             FIO_ADDRESS(VO_DISPLAY,0x60008768) /* read/write */
#define REG_VO_DISPLAY_STREAM_CONTROL_REAL                  FIO_ADDRESS(VO_DISPLAY,0x6000876C) /* read/write */
#define REG_VO_DISPLAY_FRAME_ENABLE_REAL                    FIO_ADDRESS(VO_DISPLAY,0x60008770) /* read/write */

/*----------------------------------------------------------------------------*/
/* bit group structures                                                       */
/*----------------------------------------------------------------------------*/
typedef union { /* VO_DISPLAY_CONTROL */
    U32 all;
    struct {
        U32 fixed_format                : 5;
        U32 interlace_enable            : 1;
        U32 reverse_mode_enable         : 1;
        U32                             : 18;
        U32 vout_vout_sync_enable       : 1;
        U32 vin_vout_sync_enable        : 1;
        U32 digital_output_enable       : 1;
        U32 analog_output_enable        : 1;
        U32 hdmi_output_enable          : 1;
        U32 dve_reset                   : 1;
        U32 reset                       : 1;
    } bitc;
} GH_VO_DISPLAY_CONTROL_REAL_S;

typedef union { /* VO_DISPLAY_STATUS */
    U32 all;
    struct {
        U32 hdmi_field                  : 1;
        U32 analog_fied                 : 1;
        U32 digital_field               : 1;
        U32                             : 24;
        U32 hdmi_underflow              : 1;
        U32 analog_underflow            : 1;
        U32 digital_underflow           : 1;
        U32 sdtv_configuration_ready    : 1;
        U32 reset                       : 1;
    } bitc;
} GH_VO_DISPLAY_STATUS_REAL_S;

typedef union { /* VO_DISPLAY_FRAME_SIZE_FIELD0 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 2;
        U32 width                       : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S;

typedef union { /* VO_DISPLAY_FRAME_SIZE_FIELD1 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_START_FIELD0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_START_FIELD1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S;

typedef union { /* VO_DISPLAY_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_DISPLAY_BACKGROUND_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_OUTPUT */
    U32 all;
    struct {
        U32 digital_hsync_polarity      : 1;
        U32 digital_vsync_polarity      : 1;
        U32 digital_clock_output_divider: 1;
        U32 digital_clock_divider_enable: 1;
        U32 digital_clock_edge          : 1;
        U32 digital_clock_disable       : 1;
        U32 digital_clock_divider_pattern_width: 7;
        U32 mipi_configuration          : 6;
        U32                             : 2;
        U32 color_sequence_even_lines   : 3;
        U32 color_sequence_odd_lines    : 3;
        U32 mode                        : 5;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_656_VBIT */
    U32 all;
    struct {
        U32 end_row                     : 14;
        U32                             : 2;
        U32 start_row                   : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_656_SAV_START */
    U32 all;
    struct {
        U32 code_location               : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_656_SAV_START_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_6 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_7 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_8 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_OUTPUT_MODE */
    U32 all;
    struct {
        U32 hsync_polarity              : 1;
        U32 vsync_polarity              : 1;
        U32                             : 30;
    } bitc;
} GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_CONTROL */
    U32 all;
    struct {
        U32 zero_level                  : 10;
        U32 one_level                   : 10;
        U32 repeat_count                : 7;
        U32 sd_component                : 1;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_ROW */
    U32 all;
    struct {
        U32 start_field_0               : 14;
        U32                             : 2;
        U32 start_field_1               : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_COL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_DATA */
    U32 all;
    struct {
        U32 output                      : 32;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_DATA_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0              : 13;
        U32                             : 3;
        U32 coefficient_a4              : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_0 */
    U32 all;
    struct {
        U32                             : 16;
        U32 coefficient_a4              : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 19;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_2 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 17;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_3 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_4 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_5 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_SD_SCALE_Y */
    U32 all;
    struct {
        U32 y_coefficient               : 11;
        U32                             : 5;
        U32 enable                      : 1;
        U32                             : 15;
    } bitc;
} GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL_S;

typedef union { /* VO_DISPLAY_ANALOG_SD_SCALE_PBPR */
    U32 all;
    struct {
        U32 pr_coefficient              : 11;
        U32                             : 5;
        U32 pb_coefficient              : 11;
        U32                             : 5;
    } bitc;
} GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_OUTPUT_MODE */
    U32 all;
    struct {
        U32 hsync_polarity              : 1;
        U32 vsync_polarity              : 1;
        U32                             : 27;
        U32 mode                        : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_6 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_7 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_8 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL_S;

typedef union { /* VO_DISPLAY_VOUT_VOUT_SYNC */
    U32 all;
    struct {
        U32 start_row                   : 14;
        U32                             : 2;
        U32 field_select                : 1;
        U32                             : 15;
    } bitc;
} GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
GH_VO_DISPLAY_BACKGROUND_S              m_vo_display_background;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_S     m_vo_display_digital_csc_param_0;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_S     m_vo_display_digital_csc_param_1;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_S     m_vo_display_digital_csc_param_2;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_S     m_vo_display_digital_csc_param_3;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_S     m_vo_display_digital_csc_param_4;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_S     m_vo_display_digital_csc_param_5;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_S     m_vo_display_digital_csc_param_6;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_S     m_vo_display_digital_csc_param_7;
GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_S     m_vo_display_digital_csc_param_8;
GH_VO_DISPLAY_ANALOG_VBI_DATA_S         m_vo_display_analog_vbi_data[12];
GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_S      m_vo_display_analog_csc_param_0;
GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_S      m_vo_display_analog_csc_param_1;
GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_S      m_vo_display_analog_csc_param_2;
GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_S      m_vo_display_analog_csc_param_3;
GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_S      m_vo_display_analog_csc_param_4;
GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_S      m_vo_display_analog_csc_param_5;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_S    m_vo_display_analog_csc_2_param_0;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_S    m_vo_display_analog_csc_2_param_1;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_S    m_vo_display_analog_csc_2_param_2;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_S    m_vo_display_analog_csc_2_param_3;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_S    m_vo_display_analog_csc_2_param_4;
GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_S    m_vo_display_analog_csc_2_param_5;
GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_S       m_vo_display_analog_sd_scale_y;
GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_S    m_vo_display_analog_sd_scale_pbpr;
GH_VO_DISPLAY_HDMI_CSC_PARAM_0_S        m_vo_display_hdmi_csc_param_0;
GH_VO_DISPLAY_HDMI_CSC_PARAM_1_S        m_vo_display_hdmi_csc_param_1;
GH_VO_DISPLAY_HDMI_CSC_PARAM_2_S        m_vo_display_hdmi_csc_param_2;
GH_VO_DISPLAY_HDMI_CSC_PARAM_3_S        m_vo_display_hdmi_csc_param_3;
GH_VO_DISPLAY_HDMI_CSC_PARAM_4_S        m_vo_display_hdmi_csc_param_4;
GH_VO_DISPLAY_HDMI_CSC_PARAM_5_S        m_vo_display_hdmi_csc_param_5;
GH_VO_DISPLAY_HDMI_CSC_PARAM_6_S        m_vo_display_hdmi_csc_param_6;
GH_VO_DISPLAY_HDMI_CSC_PARAM_7_S        m_vo_display_hdmi_csc_param_7;
GH_VO_DISPLAY_HDMI_CSC_PARAM_8_S        m_vo_display_hdmi_csc_param_8;

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_CONTROL (read/write)                                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_CONTROL(U32 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S real;
    GH_VO_DISPLAY_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.fixed_format = dummy.bitc.fixed_format;
    real.bitc.interlace_enable = dummy.bitc.interlace_enable;
    real.bitc.reverse_mode_enable = dummy.bitc.reverse_mode_enable;
    real.bitc.vout_vout_sync_enable = dummy.bitc.vout_vout_sync_enable;
    real.bitc.vin_vout_sync_enable = dummy.bitc.vin_vout_sync_enable;
    real.bitc.digital_output_enable = dummy.bitc.digital_output_enable;
    real.bitc.analog_output_enable = dummy.bitc.analog_output_enable;
    real.bitc.hdmi_output_enable = dummy.bitc.hdmi_output_enable;
    real.bitc.dve_reset = dummy.bitc.dve_reset;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_CONTROL(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S real;
    GH_VO_DISPLAY_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    dummy.bitc.fixed_format = real.bitc.fixed_format;
    dummy.bitc.interlace_enable = real.bitc.interlace_enable;
    dummy.bitc.reverse_mode_enable = real.bitc.reverse_mode_enable;
    dummy.bitc.vout_vout_sync_enable = real.bitc.vout_vout_sync_enable;
    dummy.bitc.vin_vout_sync_enable = real.bitc.vin_vout_sync_enable;
    dummy.bitc.digital_output_enable = real.bitc.digital_output_enable;
    dummy.bitc.analog_output_enable = real.bitc.analog_output_enable;
    dummy.bitc.hdmi_output_enable = real.bitc.hdmi_output_enable;
    dummy.bitc.dve_reset = real.bitc.dve_reset;
    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Fixed_Format(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.fixed_format = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Fixed_Format(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.fixed_format;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Interlace_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.interlace_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Interlace_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.interlace_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Reverse_Mode_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.reverse_mode_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Reverse_Mode_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reverse_mode_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_VOUT_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.vout_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_VOUT_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vout_vout_sync_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_VIN_VOUT_Sync_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.vin_vout_sync_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_VIN_VOUT_Sync_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vin_vout_sync_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Digital_Output_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.digital_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Digital_Output_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_output_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Analog_Output_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.analog_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Analog_Output_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.analog_output_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_HDMI_Output_Enable(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.hdmi_output_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_HDMI_Output_Enable(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmi_output_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_DVE_Reset(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.dve_reset = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_DVE_Reset(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.dve_reset;
}
GH_INLINE void GH_VO_DISPLAY_set_CONTROL_Reset(U8 data)
{
    GH_VO_DISPLAY_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_CONTROL_Reset(void)
{
    GH_VO_DISPLAY_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_STATUS (read/write)                                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_STATUS(U32 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S real;
    GH_VO_DISPLAY_STATUS_S dummy;
    dummy.all = data ;
    real.bitc.hdmi_field = dummy.bitc.hdmi_field;
    real.bitc.analog_fied = dummy.bitc.analog_fied;
    real.bitc.digital_field = dummy.bitc.digital_field;
    real.bitc.hdmi_underflow = dummy.bitc.hdmi_underflow;
    real.bitc.analog_underflow = dummy.bitc.analog_underflow;
    real.bitc.digital_underflow = dummy.bitc.digital_underflow;
    real.bitc.sdtv_configuration_ready = dummy.bitc.sdtv_configuration_ready;
    real.bitc.reset = dummy.bitc.reset;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_STATUS(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S real;
    GH_VO_DISPLAY_STATUS_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    dummy.bitc.hdmi_field = real.bitc.hdmi_field;
    dummy.bitc.analog_fied = real.bitc.analog_fied;
    dummy.bitc.digital_field = real.bitc.digital_field;
    dummy.bitc.hdmi_underflow = real.bitc.hdmi_underflow;
    dummy.bitc.analog_underflow = real.bitc.analog_underflow;
    dummy.bitc.digital_underflow = real.bitc.digital_underflow;
    dummy.bitc.sdtv_configuration_ready = real.bitc.sdtv_configuration_ready;
    dummy.bitc.reset = real.bitc.reset;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_HDMI_Field(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.hdmi_field = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_HDMI_Field(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmi_field;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_Analog_Fied(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.analog_fied = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_Analog_Fied(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.analog_fied;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_Digital_Field(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.digital_field = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_Digital_Field(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_field;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_HDMI_Underflow(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.hdmi_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_HDMI_Underflow(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hdmi_underflow;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_Analog_Underflow(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.analog_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_Analog_Underflow(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.analog_underflow;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_Digital_Underflow(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.digital_underflow = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_Digital_Underflow(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_underflow;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_SDTV_Configuration_Ready(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.sdtv_configuration_ready = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_SDTV_Configuration_Ready(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sdtv_configuration_ready;
}
GH_INLINE void GH_VO_DISPLAY_set_STATUS_Reset(U8 data)
{
    GH_VO_DISPLAY_STATUS_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL;
    d.bitc.reset = data;
    *(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_STATUS_Reset(void)
{
    GH_VO_DISPLAY_STATUS_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STATUS_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.reset;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_SIZE_FIELD0 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0(U32 data)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S real;
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_S dummy;
    dummy.all = data ;
    real.bitc.height = dummy.bitc.height;
    real.bitc.width = dummy.bitc.width;
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0(void)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S real;
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL);

    dummy.bitc.height = real.bitc.height;
    dummy.bitc.width = real.bitc.width;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0_Height(U16 data)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0_Height(void)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.height;
}
GH_INLINE void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0_Width(U16 data)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL;
    d.bitc.width = data;
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0_Width(void)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.width;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_SIZE_FIELD1 (read/write)                         */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD1(U32 data)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL_S real;
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_S dummy;
    dummy.all = data ;
    real.bitc.height = dummy.bitc.height;
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD1(void)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL_S real;
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL);

    dummy.bitc.height = real.bitc.height;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD1_Height(U16 data)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL;
    d.bitc.height = data;
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD1_Height(void)
{
    GH_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_SIZE_FIELD1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.height;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_START_FIELD0 (read/write)                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0(U32 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0_row(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0_row(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0_column(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0_column(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_END_0 (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0(U32 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0_row(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0_row(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0_column(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0_column(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_START_FIELD1 (read/write)                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1(U32 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1_row(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1_row(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1_column(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1_column(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_END_1 (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1(U32 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S real;
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1_row(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1_row(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1_column(U16 data)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1_column(void)
{
    GH_VO_DISPLAY_ACTIVE_REGION_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ACTIVE_REGION_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_BACKGROUND (write)                                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_BACKGROUND(U32 data)
{
    m_vo_display_background.all = data;
    GH_VO_DISPLAY_BACKGROUND_REAL_S real;
    GH_VO_DISPLAY_BACKGROUND_S dummy;
    dummy.all = data ;
    real.bitc.v = dummy.bitc.v;
    real.bitc.u = dummy.bitc.u;
    real.bitc.y = dummy.bitc.y;
    *(volatile U32 *)REG_VO_DISPLAY_BACKGROUND_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_BACKGROUND(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_BACKGROUND] --> 0x%08x\n",
                        m_vo_display_background.all);
    #endif
    return m_vo_display_background.all;
}
GH_INLINE void GH_VO_DISPLAY_set_BACKGROUND_v(U8 data)
{
    m_vo_display_background.bitc.v = data;
    GH_VO_DISPLAY_BACKGROUND_REAL_S real;
    real.bitc.v = m_vo_display_background.bitc.v;
    real.bitc.u = m_vo_display_background.bitc.u;
    real.bitc.y = m_vo_display_background.bitc.y;
    *(volatile U32 *)REG_VO_DISPLAY_BACKGROUND_REAL = real.all;
}
GH_INLINE U8   GH_VO_DISPLAY_getm_BACKGROUND_v(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_BACKGROUND_v] --> 0x%08x\n",
                        m_vo_display_background.bitc.v);
    #endif
    return m_vo_display_background.bitc.v;
}
GH_INLINE void GH_VO_DISPLAY_set_BACKGROUND_u(U8 data)
{
    m_vo_display_background.bitc.u = data;
    GH_VO_DISPLAY_BACKGROUND_REAL_S real;
    real.bitc.v = m_vo_display_background.bitc.v;
    real.bitc.u = m_vo_display_background.bitc.u;
    real.bitc.y = m_vo_display_background.bitc.y;
    *(volatile U32 *)REG_VO_DISPLAY_BACKGROUND_REAL = real.all;
}
GH_INLINE U8   GH_VO_DISPLAY_getm_BACKGROUND_u(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_BACKGROUND_u] --> 0x%08x\n",
                        m_vo_display_background.bitc.u);
    #endif
    return m_vo_display_background.bitc.u;
}
GH_INLINE void GH_VO_DISPLAY_set_BACKGROUND_y(U8 data)
{
    m_vo_display_background.bitc.y = data;
    GH_VO_DISPLAY_BACKGROUND_REAL_S real;
    real.bitc.v = m_vo_display_background.bitc.v;
    real.bitc.u = m_vo_display_background.bitc.u;
    real.bitc.y = m_vo_display_background.bitc.y;
    *(volatile U32 *)REG_VO_DISPLAY_BACKGROUND_REAL = real.all;
}
GH_INLINE U8   GH_VO_DISPLAY_getm_BACKGROUND_y(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_BACKGROUND_y] --> 0x%08x\n",
                        m_vo_display_background.bitc.y);
    #endif
    return m_vo_display_background.bitc.y;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_OUTPUT (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_OUTPUT_S dummy;
    dummy.all = data ;
    real.bitc.digital_hsync_polarity = dummy.bitc.digital_hsync_polarity;
    real.bitc.digital_vsync_polarity = dummy.bitc.digital_vsync_polarity;
    real.bitc.digital_clock_output_divider = dummy.bitc.digital_clock_output_divider;
    real.bitc.digital_clock_divider_enable = dummy.bitc.digital_clock_divider_enable;
    real.bitc.digital_clock_edge = dummy.bitc.digital_clock_edge;
    real.bitc.digital_clock_disable = dummy.bitc.digital_clock_disable;
    real.bitc.digital_clock_divider_pattern_width = dummy.bitc.digital_clock_divider_pattern_width;
    real.bitc.mipi_configuration = dummy.bitc.mipi_configuration;
    real.bitc.color_sequence_even_lines = dummy.bitc.color_sequence_even_lines;
    real.bitc.color_sequence_odd_lines = dummy.bitc.color_sequence_odd_lines;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_OUTPUT(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_OUTPUT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    dummy.bitc.digital_hsync_polarity = real.bitc.digital_hsync_polarity;
    dummy.bitc.digital_vsync_polarity = real.bitc.digital_vsync_polarity;
    dummy.bitc.digital_clock_output_divider = real.bitc.digital_clock_output_divider;
    dummy.bitc.digital_clock_divider_enable = real.bitc.digital_clock_divider_enable;
    dummy.bitc.digital_clock_edge = real.bitc.digital_clock_edge;
    dummy.bitc.digital_clock_disable = real.bitc.digital_clock_disable;
    dummy.bitc.digital_clock_divider_pattern_width = real.bitc.digital_clock_divider_pattern_width;
    dummy.bitc.mipi_configuration = real.bitc.mipi_configuration;
    dummy.bitc.color_sequence_even_lines = real.bitc.color_sequence_even_lines;
    dummy.bitc.color_sequence_odd_lines = real.bitc.color_sequence_odd_lines;
    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_hsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_hsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_vsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_vsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_clock_output_divider = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_clock_output_divider;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_clock_divider_enable = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_clock_divider_enable;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Edge(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_clock_edge = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Edge(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_clock_edge;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Disable(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_clock_disable = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Disable(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_clock_disable;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.digital_clock_divider_pattern_width = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.digital_clock_divider_pattern_width;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_MIPI_Configuration(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.mipi_configuration = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_MIPI_Configuration(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mipi_configuration;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.color_sequence_even_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.color_sequence_even_lines;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.color_sequence_odd_lines = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.color_sequence_odd_lines;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Mode(U8 data)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Mode(void)
{
    GH_VO_DISPLAY_DIGITAL_OUTPUT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_OUTPUT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_HSYNC_CONTROL (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.end_column = dummy.bitc.end_column;
    real.bitc.start_column = dummy.bitc.start_column;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL(void)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL);

    dummy.bitc.end_column = real.bitc.end_column;
    dummy.bitc.start_column = real.bitc.start_column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL_end_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL_end_column(void)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_column;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL_start_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL_start_column(void)
{
    GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_START_0 (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0_row(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0_column(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_END_0 (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0_row(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0_column(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_START_1 (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1_row(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1_column(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_END_1 (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1_row(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1_column(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1_column(void)
{
    GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_656_VBIT (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_656_VBIT(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_656_VBIT_S dummy;
    dummy.all = data ;
    real.bitc.end_row = dummy.bitc.end_row;
    real.bitc.start_row = dummy.bitc.start_row;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_656_VBIT(void)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_656_VBIT_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL);

    dummy.bitc.end_row = real.bitc.end_row;
    dummy.bitc.start_row = real.bitc.start_row;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_656_VBIT_end_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL;
    d.bitc.end_row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_656_VBIT_end_row(void)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_row;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_656_VBIT_start_row(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_656_VBIT_start_row(void)
{
    GH_VO_DISPLAY_DIGITAL_656_VBIT_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_VBIT_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_row;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_656_SAV_START (read/write)                     */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_656_SAV_START(U32 data)
{
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_S dummy;
    dummy.all = data ;
    real.bitc.code_location = dummy.bitc.code_location;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_656_SAV_START(void)
{
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL);

    dummy.bitc.code_location = real.bitc.code_location;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_656_SAV_START_Code_Location(U16 data)
{
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL;
    d.bitc.code_location = data;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_DIGITAL_656_SAV_START_Code_Location(void)
{
    GH_VO_DISPLAY_DIGITAL_656_SAV_START_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_656_SAV_START_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.code_location;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN0 (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN0(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN0_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN0(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN0_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN1 (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN1(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN1_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN1(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN1_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN2 (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN2(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN2_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN2(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN2_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN3 (read/write)                    */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN3(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN3_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN3(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN3_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_0 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0(U32 data)
{
    m_vo_display_digital_csc_param_0.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_0.all);
    #endif
    return m_vo_display_digital_csc_param_0.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246(U16 data)
{
    m_vo_display_digital_csc_param_0.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_0.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_0.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_0.bitc.coefficient_a0246);
    #endif
    return m_vo_display_digital_csc_param_0.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357(U16 data)
{
    m_vo_display_digital_csc_param_0.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_0.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_0.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_0.bitc.coefficient_a1357);
    #endif
    return m_vo_display_digital_csc_param_0.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_1 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1(U32 data)
{
    m_vo_display_digital_csc_param_1.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_1.all);
    #endif
    return m_vo_display_digital_csc_param_1.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246(U16 data)
{
    m_vo_display_digital_csc_param_1.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_1.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_1.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_1.bitc.coefficient_a0246);
    #endif
    return m_vo_display_digital_csc_param_1.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357(U16 data)
{
    m_vo_display_digital_csc_param_1.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_1.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_1.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_1.bitc.coefficient_a1357);
    #endif
    return m_vo_display_digital_csc_param_1.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_2 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2(U32 data)
{
    m_vo_display_digital_csc_param_2.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_2.all);
    #endif
    return m_vo_display_digital_csc_param_2.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246(U16 data)
{
    m_vo_display_digital_csc_param_2.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_2.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_2.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_2.bitc.coefficient_a0246);
    #endif
    return m_vo_display_digital_csc_param_2.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357(U16 data)
{
    m_vo_display_digital_csc_param_2.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_2.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_2.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_2.bitc.coefficient_a1357);
    #endif
    return m_vo_display_digital_csc_param_2.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_3 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3(U32 data)
{
    m_vo_display_digital_csc_param_3.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_3.all);
    #endif
    return m_vo_display_digital_csc_param_3.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246(U16 data)
{
    m_vo_display_digital_csc_param_3.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_3.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_3.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_3.bitc.coefficient_a0246);
    #endif
    return m_vo_display_digital_csc_param_3.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357(U16 data)
{
    m_vo_display_digital_csc_param_3.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_digital_csc_param_3.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_digital_csc_param_3.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_3.bitc.coefficient_a1357);
    #endif
    return m_vo_display_digital_csc_param_3.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_4 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4(U32 data)
{
    m_vo_display_digital_csc_param_4.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a8 = dummy.bitc.coefficient_a8;
    real.bitc.constant_b0 = dummy.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_4.all);
    #endif
    return m_vo_display_digital_csc_param_4.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4_Coefficient_a8(U16 data)
{
    m_vo_display_digital_csc_param_4.bitc.coefficient_a8 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_digital_csc_param_4.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_digital_csc_param_4.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_4.bitc.coefficient_a8);
    #endif
    return m_vo_display_digital_csc_param_4.bitc.coefficient_a8;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4_Constant_b0(U16 data)
{
    m_vo_display_digital_csc_param_4.bitc.constant_b0 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_digital_csc_param_4.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_digital_csc_param_4.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Constant_b0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Constant_b0] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_4.bitc.constant_b0);
    #endif
    return m_vo_display_digital_csc_param_4.bitc.constant_b0;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_5 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5(U32 data)
{
    m_vo_display_digital_csc_param_5.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_S dummy;
    dummy.all = data ;
    real.bitc.constant_b1 = dummy.bitc.constant_b1;
    real.bitc.constant_b2 = dummy.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_5.all);
    #endif
    return m_vo_display_digital_csc_param_5.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5_Constant_b1(U16 data)
{
    m_vo_display_digital_csc_param_5.bitc.constant_b1 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_digital_csc_param_5.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_digital_csc_param_5.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b1] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_5.bitc.constant_b1);
    #endif
    return m_vo_display_digital_csc_param_5.bitc.constant_b1;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5_Constant_b2(U16 data)
{
    m_vo_display_digital_csc_param_5.bitc.constant_b2 = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_digital_csc_param_5.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_digital_csc_param_5.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b2] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_5.bitc.constant_b2);
    #endif
    return m_vo_display_digital_csc_param_5.bitc.constant_b2;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_6 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6(U32 data)
{
    m_vo_display_digital_csc_param_6.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_6.all);
    #endif
    return m_vo_display_digital_csc_param_6.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_digital_csc_param_6.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_6.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_6.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_6.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_digital_csc_param_6.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(U16 data)
{
    m_vo_display_digital_csc_param_6.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_6.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_6.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_6.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_digital_csc_param_6.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_7 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7(U32 data)
{
    m_vo_display_digital_csc_param_7.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_7.all);
    #endif
    return m_vo_display_digital_csc_param_7.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_digital_csc_param_7.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_7.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_7.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_7.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_digital_csc_param_7.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(U16 data)
{
    m_vo_display_digital_csc_param_7.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_7.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_7.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_7.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_digital_csc_param_7.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_8 (write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8(U32 data)
{
    m_vo_display_digital_csc_param_8.all = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL_S real;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_8.all);
    #endif
    return m_vo_display_digital_csc_param_8.all;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_digital_csc_param_8.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_8.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_8.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_8.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_digital_csc_param_8.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(U16 data)
{
    m_vo_display_digital_csc_param_8.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_digital_csc_param_8.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_digital_csc_param_8.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_digital_csc_param_8.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_digital_csc_param_8.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_OUTPUT_MODE (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE(U32 data)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S real;
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_S dummy;
    dummy.all = data ;
    real.bitc.hsync_polarity = dummy.bitc.hsync_polarity;
    real.bitc.vsync_polarity = dummy.bitc.vsync_polarity;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE(void)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S real;
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL);

    dummy.bitc.hsync_polarity = real.bitc.hsync_polarity;
    dummy.bitc.vsync_polarity = real.bitc.vsync_polarity;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE_Hsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL;
    d.bitc.hsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE_Hsync_Polarity(void)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE_Vsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL;
    d.bitc.vsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE_Vsync_Polarity(void)
{
    GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_OUTPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_polarity;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_HSYNC_CONTROL (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL(U32 data)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.end_column = dummy.bitc.end_column;
    real.bitc.start_column = dummy.bitc.start_column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL(void)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL);

    dummy.bitc.end_column = real.bitc.end_column;
    dummy.bitc.start_column = real.bitc.start_column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL_end_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL_end_column(void)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_column;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL_start_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL_start_column(void)
{
    GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_START_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0_row(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0_row(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0_column(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_END_0 (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0_row(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0_row(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0_column(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_START_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1_row(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1_row(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1_column(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_END_1 (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1_row(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1_row(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1_column(void)
{
    GH_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.zero_level = dummy.bitc.zero_level;
    real.bitc.one_level = dummy.bitc.one_level;
    real.bitc.repeat_count = dummy.bitc.repeat_count;
    real.bitc.sd_component = dummy.bitc.sd_component;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL);

    dummy.bitc.zero_level = real.bitc.zero_level;
    dummy.bitc.one_level = real.bitc.one_level;
    dummy.bitc.repeat_count = real.bitc.repeat_count;
    dummy.bitc.sd_component = real.bitc.sd_component;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_Zero_Level(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL;
    d.bitc.zero_level = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_Zero_Level(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.zero_level;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_One_Level(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL;
    d.bitc.one_level = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_One_Level(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.one_level;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_Repeat_Count(U8 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL;
    d.bitc.repeat_count = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_Repeat_Count(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.repeat_count;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_SD_Component(U8 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL;
    d.bitc.sd_component = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_SD_Component(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.sd_component;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_ROW (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_ROW(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_ROW_S dummy;
    dummy.all = data ;
    real.bitc.start_field_0 = dummy.bitc.start_field_0;
    real.bitc.start_field_1 = dummy.bitc.start_field_1;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VBI_ROW(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_ROW_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL);

    dummy.bitc.start_field_0 = real.bitc.start_field_0;
    dummy.bitc.start_field_1 = real.bitc.start_field_1;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_ROW_start_field_0(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL;
    d.bitc.start_field_0 = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_ROW_start_field_0(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_field_0;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_ROW_start_field_1(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL;
    d.bitc.start_field_1 = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_ROW_start_field_1(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_ROW_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_ROW_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_field_1;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_COL (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_COL(U32 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_COL_S dummy;
    dummy.all = data ;
    real.bitc.end_column = dummy.bitc.end_column;
    real.bitc.start_column = dummy.bitc.start_column;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_ANALOG_VBI_COL(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_COL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL);

    dummy.bitc.end_column = real.bitc.end_column;
    dummy.bitc.start_column = real.bitc.start_column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_COL_end_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_COL_end_column(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_column;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_COL_start_column(U16 data)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_ANALOG_VBI_COL_start_column(void)
{
    GH_VO_DISPLAY_ANALOG_VBI_COL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_ANALOG_VBI_COL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_DATA (write)                                */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_DATA(U8 index, U32 data)
{
    m_vo_display_analog_vbi_data[index].all = data;
    GH_VO_DISPLAY_ANALOG_VBI_DATA_REAL_S real;
    GH_VO_DISPLAY_ANALOG_VBI_DATA_S dummy;
    dummy.all = data ;
    real.bitc.output = dummy.bitc.output;
    *(volatile U32 *)(REG_VO_DISPLAY_ANALOG_VBI_DATA_REAL + index * FIO_MOFFSET(VO_DISPLAY,0x00000004)) = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_VBI_DATA(U8 index)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_VBI_DATA] --> 0x%08x\n",
                        m_vo_display_analog_vbi_data[index].all);
    #endif
    return m_vo_display_analog_vbi_data[index].all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_VBI_DATA_Output(U8 index, U32 data)
{
    m_vo_display_analog_vbi_data[index].bitc.output = data;
    GH_VO_DISPLAY_ANALOG_VBI_DATA_REAL_S real;
    real.bitc.output = m_vo_display_analog_vbi_data[index].bitc.output;
    *(volatile U32 *)(REG_VO_DISPLAY_ANALOG_VBI_DATA_REAL + index * FIO_MOFFSET(VO_DISPLAY,0x00000004)) = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_VBI_DATA_Output(U8 index)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_VBI_DATA_Output] --> 0x%08x\n",
                        m_vo_display_analog_vbi_data[index].bitc.output);
    #endif
    return m_vo_display_analog_vbi_data[index].bitc.output;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_0 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0(U32 data)
{
    m_vo_display_analog_csc_param_0.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0 = dummy.bitc.coefficient_a0;
    real.bitc.coefficient_a4 = dummy.bitc.coefficient_a4;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_0.all);
    #endif
    return m_vo_display_analog_csc_param_0.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0_Coefficient_a0(U16 data)
{
    m_vo_display_analog_csc_param_0.bitc.coefficient_a0 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0 = m_vo_display_analog_csc_param_0.bitc.coefficient_a0;
    real.bitc.coefficient_a4 = m_vo_display_analog_csc_param_0.bitc.coefficient_a4;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a0] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_0.bitc.coefficient_a0);
    #endif
    return m_vo_display_analog_csc_param_0.bitc.coefficient_a0;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0_Coefficient_a4(U16 data)
{
    m_vo_display_analog_csc_param_0.bitc.coefficient_a4 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0 = m_vo_display_analog_csc_param_0.bitc.coefficient_a0;
    real.bitc.coefficient_a4 = m_vo_display_analog_csc_param_0.bitc.coefficient_a4;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a4] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_0.bitc.coefficient_a4);
    #endif
    return m_vo_display_analog_csc_param_0.bitc.coefficient_a4;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_1 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1(U32 data)
{
    m_vo_display_analog_csc_param_1.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a8 = dummy.bitc.coefficient_a8;
    real.bitc.constant_b0 = dummy.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_1.all);
    #endif
    return m_vo_display_analog_csc_param_1.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1_Coefficient_a8(U16 data)
{
    m_vo_display_analog_csc_param_1.bitc.coefficient_a8 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_analog_csc_param_1.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_analog_csc_param_1.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_1.bitc.coefficient_a8);
    #endif
    return m_vo_display_analog_csc_param_1.bitc.coefficient_a8;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1_Constant_b0(U16 data)
{
    m_vo_display_analog_csc_param_1.bitc.constant_b0 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_analog_csc_param_1.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_analog_csc_param_1.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Constant_b0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Constant_b0] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_1.bitc.constant_b0);
    #endif
    return m_vo_display_analog_csc_param_1.bitc.constant_b0;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_2 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2(U32 data)
{
    m_vo_display_analog_csc_param_2.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_S dummy;
    dummy.all = data ;
    real.bitc.constant_b1 = dummy.bitc.constant_b1;
    real.bitc.constant_b2 = dummy.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_2.all);
    #endif
    return m_vo_display_analog_csc_param_2.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2_Constant_b1(U16 data)
{
    m_vo_display_analog_csc_param_2.bitc.constant_b1 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_analog_csc_param_2.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_analog_csc_param_2.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b1] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_2.bitc.constant_b1);
    #endif
    return m_vo_display_analog_csc_param_2.bitc.constant_b1;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2_Constant_b2(U16 data)
{
    m_vo_display_analog_csc_param_2.bitc.constant_b2 = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_analog_csc_param_2.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_analog_csc_param_2.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b2] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_2.bitc.constant_b2);
    #endif
    return m_vo_display_analog_csc_param_2.bitc.constant_b2;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_3 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3(U32 data)
{
    m_vo_display_analog_csc_param_3.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_S dummy;
    dummy.all = data ;
    real.bitc.output012_clamp_low = dummy.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = dummy.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_3.all);
    #endif
    return m_vo_display_analog_csc_param_3.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3_Output012_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_param_3.bitc.output012_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_3.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_3.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_3.bitc.output012_clamp_low);
    #endif
    return m_vo_display_analog_csc_param_3.bitc.output012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3_Output012_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_param_3.bitc.output012_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_3.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_3.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_3.bitc.output012_clamp_high);
    #endif
    return m_vo_display_analog_csc_param_3.bitc.output012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_4 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4(U32 data)
{
    m_vo_display_analog_csc_param_4.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_S dummy;
    dummy.all = data ;
    real.bitc.output012_clamp_low = dummy.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = dummy.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_4.all);
    #endif
    return m_vo_display_analog_csc_param_4.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4_Output012_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_param_4.bitc.output012_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_4.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_4.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_4.bitc.output012_clamp_low);
    #endif
    return m_vo_display_analog_csc_param_4.bitc.output012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4_Output012_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_param_4.bitc.output012_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_4.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_4.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_4.bitc.output012_clamp_high);
    #endif
    return m_vo_display_analog_csc_param_4.bitc.output012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_5 (write)                             */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5(U32 data)
{
    m_vo_display_analog_csc_param_5.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_S dummy;
    dummy.all = data ;
    real.bitc.output012_clamp_low = dummy.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = dummy.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_5.all);
    #endif
    return m_vo_display_analog_csc_param_5.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5_Output012_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_param_5.bitc.output012_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_5.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_5.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_5.bitc.output012_clamp_low);
    #endif
    return m_vo_display_analog_csc_param_5.bitc.output012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5_Output012_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_param_5.bitc.output012_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL_S real;
    real.bitc.output012_clamp_low = m_vo_display_analog_csc_param_5.bitc.output012_clamp_low;
    real.bitc.output012_clamp_high = m_vo_display_analog_csc_param_5.bitc.output012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_param_5.bitc.output012_clamp_high);
    #endif
    return m_vo_display_analog_csc_param_5.bitc.output012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_0 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_0(U32 data)
{
    m_vo_display_analog_csc_2_param_0.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a4 = dummy.bitc.coefficient_a4;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_0.all);
    #endif
    return m_vo_display_analog_csc_2_param_0.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_0_Coefficient_a4(U16 data)
{
    m_vo_display_analog_csc_2_param_0.bitc.coefficient_a4 = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL_S real;
    real.bitc.coefficient_a4 = m_vo_display_analog_csc_2_param_0.bitc.coefficient_a4;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0_Coefficient_a4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0_Coefficient_a4] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_0.bitc.coefficient_a4);
    #endif
    return m_vo_display_analog_csc_2_param_0.bitc.coefficient_a4;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_1 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_1(U32 data)
{
    m_vo_display_analog_csc_2_param_1.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a8 = dummy.bitc.coefficient_a8;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_1.all);
    #endif
    return m_vo_display_analog_csc_2_param_1.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_1_Coefficient_a8(U16 data)
{
    m_vo_display_analog_csc_2_param_1.bitc.coefficient_a8 = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_analog_csc_2_param_1.bitc.coefficient_a8;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_1.bitc.coefficient_a8);
    #endif
    return m_vo_display_analog_csc_2_param_1.bitc.coefficient_a8;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_2 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_2(U32 data)
{
    m_vo_display_analog_csc_2_param_2.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_S dummy;
    dummy.all = data ;
    real.bitc.constant_b1 = dummy.bitc.constant_b1;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_2.all);
    #endif
    return m_vo_display_analog_csc_2_param_2.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_2_Constant_b1(U16 data)
{
    m_vo_display_analog_csc_2_param_2.bitc.constant_b1 = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_analog_csc_2_param_2.bitc.constant_b1;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2_Constant_b1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2_Constant_b1] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_2.bitc.constant_b1);
    #endif
    return m_vo_display_analog_csc_2_param_2.bitc.constant_b1;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_3 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3(U32 data)
{
    m_vo_display_analog_csc_2_param_3.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_S dummy;
    dummy.all = data ;
    real.bitc.output1_clamp_low = dummy.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = dummy.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_3.all);
    #endif
    return m_vo_display_analog_csc_2_param_3.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3_Output1_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_low);
    #endif
    return m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3_Output1_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_high);
    #endif
    return m_vo_display_analog_csc_2_param_3.bitc.output1_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_4 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4(U32 data)
{
    m_vo_display_analog_csc_2_param_4.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_S dummy;
    dummy.all = data ;
    real.bitc.output1_clamp_low = dummy.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = dummy.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_4.all);
    #endif
    return m_vo_display_analog_csc_2_param_4.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4_Output1_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_low);
    #endif
    return m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4_Output1_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_high);
    #endif
    return m_vo_display_analog_csc_2_param_4.bitc.output1_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_5 (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5(U32 data)
{
    m_vo_display_analog_csc_2_param_5.all = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL_S real;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_S dummy;
    dummy.all = data ;
    real.bitc.output1_clamp_low = dummy.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = dummy.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_5.all);
    #endif
    return m_vo_display_analog_csc_2_param_5.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5_Output1_Clamp_Low(U16 data)
{
    m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_low = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_low);
    #endif
    return m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5_Output1_Clamp_High(U16 data)
{
    m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_high = data;
    GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL_S real;
    real.bitc.output1_clamp_low = m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_low;
    real.bitc.output1_clamp_high = m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_High] --> 0x%08x\n",
                        m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_high);
    #endif
    return m_vo_display_analog_csc_2_param_5.bitc.output1_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_SD_SCALE_Y (write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y(U32 data)
{
    m_vo_display_analog_sd_scale_y.all = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL_S real;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_S dummy;
    dummy.all = data ;
    real.bitc.y_coefficient = dummy.bitc.y_coefficient;
    real.bitc.enable = dummy.bitc.enable;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_y.all);
    #endif
    return m_vo_display_analog_sd_scale_y.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y_Y_Coefficient(U16 data)
{
    m_vo_display_analog_sd_scale_y.bitc.y_coefficient = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL_S real;
    real.bitc.y_coefficient = m_vo_display_analog_sd_scale_y.bitc.y_coefficient;
    real.bitc.enable = m_vo_display_analog_sd_scale_y.bitc.enable;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Y_Coefficient(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Y_Coefficient] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_y.bitc.y_coefficient);
    #endif
    return m_vo_display_analog_sd_scale_y.bitc.y_coefficient;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y_Enable(U8 data)
{
    m_vo_display_analog_sd_scale_y.bitc.enable = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL_S real;
    real.bitc.y_coefficient = m_vo_display_analog_sd_scale_y.bitc.y_coefficient;
    real.bitc.enable = m_vo_display_analog_sd_scale_y.bitc.enable;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_Y_REAL = real.all;
}
GH_INLINE U8   GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Enable(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Enable] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_y.bitc.enable);
    #endif
    return m_vo_display_analog_sd_scale_y.bitc.enable;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_SD_SCALE_PBPR (write)                           */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR(U32 data)
{
    m_vo_display_analog_sd_scale_pbpr.all = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL_S real;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_S dummy;
    dummy.all = data ;
    real.bitc.pr_coefficient = dummy.bitc.pr_coefficient;
    real.bitc.pb_coefficient = dummy.bitc.pb_coefficient;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_pbpr.all);
    #endif
    return m_vo_display_analog_sd_scale_pbpr.all;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR_Pr_Coefficient(U16 data)
{
    m_vo_display_analog_sd_scale_pbpr.bitc.pr_coefficient = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL_S real;
    real.bitc.pr_coefficient = m_vo_display_analog_sd_scale_pbpr.bitc.pr_coefficient;
    real.bitc.pb_coefficient = m_vo_display_analog_sd_scale_pbpr.bitc.pb_coefficient;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pr_Coefficient(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pr_Coefficient] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_pbpr.bitc.pr_coefficient);
    #endif
    return m_vo_display_analog_sd_scale_pbpr.bitc.pr_coefficient;
}
GH_INLINE void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR_Pb_Coefficient(U16 data)
{
    m_vo_display_analog_sd_scale_pbpr.bitc.pb_coefficient = data;
    GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL_S real;
    real.bitc.pr_coefficient = m_vo_display_analog_sd_scale_pbpr.bitc.pr_coefficient;
    real.bitc.pb_coefficient = m_vo_display_analog_sd_scale_pbpr.bitc.pb_coefficient;
    *(volatile U32 *)REG_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pb_Coefficient(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pb_Coefficient] --> 0x%08x\n",
                        m_vo_display_analog_sd_scale_pbpr.bitc.pb_coefficient);
    #endif
    return m_vo_display_analog_sd_scale_pbpr.bitc.pb_coefficient;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_OUTPUT_MODE (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE(U32 data)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S real;
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_S dummy;
    dummy.all = data ;
    real.bitc.hsync_polarity = dummy.bitc.hsync_polarity;
    real.bitc.vsync_polarity = dummy.bitc.vsync_polarity;
    real.bitc.mode = dummy.bitc.mode;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE(void)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S real;
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL);

    dummy.bitc.hsync_polarity = real.bitc.hsync_polarity;
    dummy.bitc.vsync_polarity = real.bitc.vsync_polarity;
    dummy.bitc.mode = real.bitc.mode;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Hsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL;
    d.bitc.hsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Hsync_Polarity(void)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.hsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Vsync_Polarity(U8 data)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL;
    d.bitc.vsync_polarity = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Vsync_Polarity(void)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.vsync_polarity;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Mode(U8 data)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL;
    d.bitc.mode = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Mode(void)
{
    GH_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_OUTPUT_MODE_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.mode;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_HSYNC_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL(U32 data)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_S dummy;
    dummy.all = data ;
    real.bitc.end_column = dummy.bitc.end_column;
    real.bitc.start_column = dummy.bitc.start_column;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL(void)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S real;
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL);

    dummy.bitc.end_column = real.bitc.end_column;
    dummy.bitc.start_column = real.bitc.start_column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL_end_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL;
    d.bitc.end_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL_end_column(void)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.end_column;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL_start_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL;
    d.bitc.start_column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL_start_column(void)
{
    GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_HSYNC_CONTROL_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_START_0 (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0(U32 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0_row(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0_row(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0_column(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_END_0 (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0(U32 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0_row(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0_row(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0_column(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_0_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_0_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_START_1 (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1(U32 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1_row(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1_row(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1_column(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_START_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_START_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_END_1 (read/write)                          */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1(U32 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_S dummy;
    dummy.all = data ;
    real.bitc.row = dummy.bitc.row;
    real.bitc.column = dummy.bitc.column;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S real;
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL);

    dummy.bitc.row = real.bitc.row;
    dummy.bitc.column = real.bitc.column;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1_row(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL;
    d.bitc.row = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1_row(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.row;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1_column(U16 data)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL;
    d.bitc.column = data;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1_column(void)
{
    GH_VO_DISPLAY_HDMI_VSYNC_END_1_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_HDMI_VSYNC_END_1_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.column;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_0 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0(U32 data)
{
    m_vo_display_hdmi_csc_param_0.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_0_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_0.all);
    #endif
    return m_vo_display_hdmi_csc_param_0.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0_Coefficient_a0246(U16 data)
{
    m_vo_display_hdmi_csc_param_0.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_0.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_0.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_0.bitc.coefficient_a0246);
    #endif
    return m_vo_display_hdmi_csc_param_0.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0_Coefficient_a1357(U16 data)
{
    m_vo_display_hdmi_csc_param_0.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_0.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_0.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_0_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_0.bitc.coefficient_a1357);
    #endif
    return m_vo_display_hdmi_csc_param_0.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_1 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1(U32 data)
{
    m_vo_display_hdmi_csc_param_1.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_1_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_1.all);
    #endif
    return m_vo_display_hdmi_csc_param_1.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1_Coefficient_a0246(U16 data)
{
    m_vo_display_hdmi_csc_param_1.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_1.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_1.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_1.bitc.coefficient_a0246);
    #endif
    return m_vo_display_hdmi_csc_param_1.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1_Coefficient_a1357(U16 data)
{
    m_vo_display_hdmi_csc_param_1.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_1.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_1.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_1_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_1.bitc.coefficient_a1357);
    #endif
    return m_vo_display_hdmi_csc_param_1.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_2 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2(U32 data)
{
    m_vo_display_hdmi_csc_param_2.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_2_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_2.all);
    #endif
    return m_vo_display_hdmi_csc_param_2.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2_Coefficient_a0246(U16 data)
{
    m_vo_display_hdmi_csc_param_2.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_2.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_2.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_2.bitc.coefficient_a0246);
    #endif
    return m_vo_display_hdmi_csc_param_2.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2_Coefficient_a1357(U16 data)
{
    m_vo_display_hdmi_csc_param_2.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_2.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_2.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_2_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_2.bitc.coefficient_a1357);
    #endif
    return m_vo_display_hdmi_csc_param_2.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_3 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3(U32 data)
{
    m_vo_display_hdmi_csc_param_3.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_3_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a0246 = dummy.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = dummy.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_3.all);
    #endif
    return m_vo_display_hdmi_csc_param_3.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3_Coefficient_a0246(U16 data)
{
    m_vo_display_hdmi_csc_param_3.bitc.coefficient_a0246 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_3.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_3.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a0246(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a0246] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_3.bitc.coefficient_a0246);
    #endif
    return m_vo_display_hdmi_csc_param_3.bitc.coefficient_a0246;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3_Coefficient_a1357(U16 data)
{
    m_vo_display_hdmi_csc_param_3.bitc.coefficient_a1357 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL_S real;
    real.bitc.coefficient_a0246 = m_vo_display_hdmi_csc_param_3.bitc.coefficient_a0246;
    real.bitc.coefficient_a1357 = m_vo_display_hdmi_csc_param_3.bitc.coefficient_a1357;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_3_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a1357(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a1357] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_3.bitc.coefficient_a1357);
    #endif
    return m_vo_display_hdmi_csc_param_3.bitc.coefficient_a1357;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_4 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4(U32 data)
{
    m_vo_display_hdmi_csc_param_4.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_4_S dummy;
    dummy.all = data ;
    real.bitc.coefficient_a8 = dummy.bitc.coefficient_a8;
    real.bitc.constant_b0 = dummy.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_4.all);
    #endif
    return m_vo_display_hdmi_csc_param_4.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4_Coefficient_a8(U16 data)
{
    m_vo_display_hdmi_csc_param_4.bitc.coefficient_a8 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_hdmi_csc_param_4.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_hdmi_csc_param_4.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Coefficient_a8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Coefficient_a8] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_4.bitc.coefficient_a8);
    #endif
    return m_vo_display_hdmi_csc_param_4.bitc.coefficient_a8;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4_Constant_b0(U16 data)
{
    m_vo_display_hdmi_csc_param_4.bitc.constant_b0 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL_S real;
    real.bitc.coefficient_a8 = m_vo_display_hdmi_csc_param_4.bitc.coefficient_a8;
    real.bitc.constant_b0 = m_vo_display_hdmi_csc_param_4.bitc.constant_b0;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_4_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Constant_b0(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Constant_b0] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_4.bitc.constant_b0);
    #endif
    return m_vo_display_hdmi_csc_param_4.bitc.constant_b0;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_5 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5(U32 data)
{
    m_vo_display_hdmi_csc_param_5.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_5_S dummy;
    dummy.all = data ;
    real.bitc.constant_b1 = dummy.bitc.constant_b1;
    real.bitc.constant_b2 = dummy.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_5.all);
    #endif
    return m_vo_display_hdmi_csc_param_5.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5_Constant_b1(U16 data)
{
    m_vo_display_hdmi_csc_param_5.bitc.constant_b1 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_hdmi_csc_param_5.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_hdmi_csc_param_5.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b1(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b1] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_5.bitc.constant_b1);
    #endif
    return m_vo_display_hdmi_csc_param_5.bitc.constant_b1;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5_Constant_b2(U16 data)
{
    m_vo_display_hdmi_csc_param_5.bitc.constant_b2 = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL_S real;
    real.bitc.constant_b1 = m_vo_display_hdmi_csc_param_5.bitc.constant_b1;
    real.bitc.constant_b2 = m_vo_display_hdmi_csc_param_5.bitc.constant_b2;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_5_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b2(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b2] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_5.bitc.constant_b2);
    #endif
    return m_vo_display_hdmi_csc_param_5.bitc.constant_b2;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_6 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6(U32 data)
{
    m_vo_display_hdmi_csc_param_6.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_6_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_6.all);
    #endif
    return m_vo_display_hdmi_csc_param_6.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6_Output_012_Clamp_High(U16 data)
{
    m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_6_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_hdmi_csc_param_6.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_7 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7(U32 data)
{
    m_vo_display_hdmi_csc_param_7.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_7_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_7.all);
    #endif
    return m_vo_display_hdmi_csc_param_7.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7_Output_012_Clamp_High(U16 data)
{
    m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_7_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_hdmi_csc_param_7.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_8 (write)                               */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8(U32 data)
{
    m_vo_display_hdmi_csc_param_8.all = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL_S real;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_8_S dummy;
    dummy.all = data ;
    real.bitc.output_012_clamp_low = dummy.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = dummy.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_8.all);
    #endif
    return m_vo_display_hdmi_csc_param_8.all;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8_Output_012_Clamp_Low(U16 data)
{
    m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_low = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_Low(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_Low] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_low);
    #endif
    return m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_low;
}
GH_INLINE void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8_Output_012_Clamp_High(U16 data)
{
    m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_high = data;
    GH_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL_S real;
    real.bitc.output_012_clamp_low = m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_low;
    real.bitc.output_012_clamp_high = m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_high;
    *(volatile U32 *)REG_VO_DISPLAY_HDMI_CSC_PARAM_8_REAL = real.all;
}
GH_INLINE U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_High(void)
{
    #if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
    GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION( "[GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_High] --> 0x%08x\n",
                        m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_high);
    #endif
    return m_vo_display_hdmi_csc_param_8.bitc.output_012_clamp_high;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_DITHER_SETTINGS (read/write)                   */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_DITHER_SETTINGS(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_DITHER_SETTINGS_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_DITHER_SETTINGS(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_DITHER_SETTINGS_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_DITHER_SEED (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_DIGITAL_DITHER_SEED(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_DIGITAL_DITHER_SEED_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_DIGITAL_DITHER_SEED(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_DIGITAL_DITHER_SEED_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_VOUT_VOUT_SYNC (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC(U32 data)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S real;
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_S dummy;
    dummy.all = data ;
    real.bitc.start_row = dummy.bitc.start_row;
    real.bitc.field_select = dummy.bitc.field_select;
    *(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL = real.all;
}
GH_INLINE U32  GH_VO_DISPLAY_get_VOUT_VOUT_SYNC(void)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S real;
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_S dummy;
     dummy.all =  0;
     real.all = (*(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL);

    dummy.bitc.start_row = real.bitc.start_row;
    dummy.bitc.field_select = real.bitc.field_select;
    return dummy.all;
}
GH_INLINE void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC_Start_Row(U16 data)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL;
    d.bitc.start_row = data;
    *(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL = d.all;
}
GH_INLINE U16  GH_VO_DISPLAY_get_VOUT_VOUT_SYNC_Start_Row(void)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.start_row;
}
GH_INLINE void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC_Field_Select(U8 data)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S d;
    d.all = *(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL;
    d.bitc.field_select = data;
    *(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL = d.all;
}
GH_INLINE U8   GH_VO_DISPLAY_get_VOUT_VOUT_SYNC_Field_Select(void)
{
    GH_VO_DISPLAY_VOUT_VOUT_SYNC_REAL_S tmp_value;
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_VOUT_VOUT_SYNC_REAL);

    tmp_value.all = value;
    return tmp_value.bitc.field_select;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_INPUT_STREAM_ENABLES (read/write)                      */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_INPUT_STREAM_ENABLES(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_INPUT_STREAM_ENABLES_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_INPUT_STREAM_ENABLES(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_INPUT_STREAM_ENABLES_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_INPUT_SYNC_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_INPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_INPUT_SYNC_CONTROL_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_INPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_INPUT_SYNC_CONTROL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_OUTPUT_SYNC_CONTROL (read/write)                       */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_OUTPUT_SYNC_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_OUTPUT_SYNC_CONTROL_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_OUTPUT_SYNC_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_OUTPUT_SYNC_CONTROL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_STREAM_CONTROL (read/write)                            */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_STREAM_CONTROL(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_STREAM_CONTROL_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_STREAM_CONTROL(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_STREAM_CONTROL_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_ENABLE (read/write)                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_set_FRAME_ENABLE(U32 data)
{
    *(volatile U32 *)REG_VO_DISPLAY_FRAME_ENABLE_REAL = data;
}
GH_INLINE U32  GH_VO_DISPLAY_get_FRAME_ENABLE(void)
{
    U32 value = (*(volatile U32 *)REG_VO_DISPLAY_FRAME_ENABLE_REAL);

    return value;
}

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
GH_INLINE void GH_VO_DISPLAY_init(void)
{
    int i;

    GH_VO_DISPLAY_set_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_STATUS((U32)0x00000000);
    GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0((U32)0x00000000);
    GH_VO_DISPLAY_set_FRAME_SIZE_FIELD1((U32)0x00000000);
    GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0((U32)0x00000000);
    GH_VO_DISPLAY_set_ACTIVE_REGION_END_0((U32)0x00000000);
    GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1((U32)0x00000000);
    GH_VO_DISPLAY_set_ACTIVE_REGION_END_1((U32)0x00000000);
    GH_VO_DISPLAY_set_BACKGROUND((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_OUTPUT((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_656_VBIT((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_656_SAV_START((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN0((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN1((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN2((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN3((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VBI_ROW((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_VBI_COL((U32)0x00000000);
    for (i=0; i<12; i++)
    {
        GH_VO_DISPLAY_set_ANALOG_VBI_DATA(i, (U32)0x00000000);
    }
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_0((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_1((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_2((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y((U32)0x00000000);
    GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_VSYNC_START_0((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_VSYNC_END_0((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_VSYNC_START_1((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_VSYNC_END_1((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7((U32)0x00000000);
    GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_DITHER_SETTINGS((U32)0x00000000);
    GH_VO_DISPLAY_set_DIGITAL_DITHER_SEED((U32)0x00000000);
    GH_VO_DISPLAY_set_VOUT_VOUT_SYNC((U32)0x00000000);
    GH_VO_DISPLAY_set_INPUT_STREAM_ENABLES((U32)0x00000000);
    GH_VO_DISPLAY_set_INPUT_SYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_OUTPUT_SYNC_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_STREAM_CONTROL((U32)0x00000000);
    GH_VO_DISPLAY_set_FRAME_ENABLE((U32)0x00000000);
    /* read read-clear registers in order to set mirror variables */
}

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

