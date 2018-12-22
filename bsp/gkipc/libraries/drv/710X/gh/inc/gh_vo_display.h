/*!
*******************************************************************************
**
** \file      gh_vo_display.h
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
#ifndef _GH_VO_DISPLAY_H
#define _GH_VO_DISPLAY_H

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

#define GH_VO_DISPLAY_ENABLE_DEBUG_PRINT   0
#ifdef __LINUX__
#define GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION printk
#else
#define GH_VO_DISPLAY_DEBUG_PRINT_FUNCTION printf
#endif
#ifndef __LINUX__
#if GH_VO_DISPLAY_ENABLE_DEBUG_PRINT
#include <stdio.h>
#endif
#endif

/*----------------------------------------------------------------------------*/
/* registers                                                                  */
/*----------------------------------------------------------------------------*/
#define REG_VO_DISPLAY_CONTROL                              FIO_ADDRESS(VO_DISPLAY,0x90008600) /* read/write */
#define REG_VO_DISPLAY_STATUS                               FIO_ADDRESS(VO_DISPLAY,0x90008604) /* read/write */
#define REG_VO_DISPLAY_FRAME_SIZE_FIELD0                    FIO_ADDRESS(VO_DISPLAY,0x90008608) /* read/write */
#define REG_VO_DISPLAY_FRAME_SIZE_FIELD1                    FIO_ADDRESS(VO_DISPLAY,0x9000860C) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD0           FIO_ADDRESS(VO_DISPLAY,0x90008610) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_END_0                  FIO_ADDRESS(VO_DISPLAY,0x90008614) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_START_FIELD1           FIO_ADDRESS(VO_DISPLAY,0x90008618) /* read/write */
#define REG_VO_DISPLAY_ACTIVE_REGION_END_1                  FIO_ADDRESS(VO_DISPLAY,0x9000861C) /* read/write */
#define REG_VO_DISPLAY_BACKGROUND                           FIO_ADDRESS(VO_DISPLAY,0x90008620) /* write */
#define REG_VO_DISPLAY_DIGITAL_OUTPUT                       FIO_ADDRESS(VO_DISPLAY,0x90008624) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_HSYNC_CONTROL                FIO_ADDRESS(VO_DISPLAY,0x90008628) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_START_0                FIO_ADDRESS(VO_DISPLAY,0x9000862C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_END_0                  FIO_ADDRESS(VO_DISPLAY,0x90008630) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_START_1                FIO_ADDRESS(VO_DISPLAY,0x90008634) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_VSYNC_END_1                  FIO_ADDRESS(VO_DISPLAY,0x90008638) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_656_VBIT                     FIO_ADDRESS(VO_DISPLAY,0x9000863C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_656_SAV_START                FIO_ADDRESS(VO_DISPLAY,0x90008640) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN0               FIO_ADDRESS(VO_DISPLAY,0x90008644) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN1               FIO_ADDRESS(VO_DISPLAY,0x90008648) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN2               FIO_ADDRESS(VO_DISPLAY,0x9000864C) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CLOCK_PATTERN3               FIO_ADDRESS(VO_DISPLAY,0x90008650) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_0                  FIO_ADDRESS(VO_DISPLAY,0x90008654) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_1                  FIO_ADDRESS(VO_DISPLAY,0x90008658) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_2                  FIO_ADDRESS(VO_DISPLAY,0x9000865C) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_3                  FIO_ADDRESS(VO_DISPLAY,0x90008660) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_4                  FIO_ADDRESS(VO_DISPLAY,0x90008664) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_5                  FIO_ADDRESS(VO_DISPLAY,0x90008668) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_6                  FIO_ADDRESS(VO_DISPLAY,0x9000866C) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_7                  FIO_ADDRESS(VO_DISPLAY,0x90008670) /* write */
#define REG_VO_DISPLAY_DIGITAL_CSC_PARAM_8                  FIO_ADDRESS(VO_DISPLAY,0x90008674) /* write */
#define REG_VO_DISPLAY_ANALOG_OUTPUT_MODE                   FIO_ADDRESS(VO_DISPLAY,0x90008678) /* read/write */
#define REG_VO_DISPLAY_ANALOG_HSYNC_CONTROL                 FIO_ADDRESS(VO_DISPLAY,0x9000867C) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_START_0                 FIO_ADDRESS(VO_DISPLAY,0x90008680) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_END_0                   FIO_ADDRESS(VO_DISPLAY,0x90008684) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_START_1                 FIO_ADDRESS(VO_DISPLAY,0x90008688) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VSYNC_END_1                   FIO_ADDRESS(VO_DISPLAY,0x9000868C) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_CONTROL                   FIO_ADDRESS(VO_DISPLAY,0x90008690) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_ROW                       FIO_ADDRESS(VO_DISPLAY,0x90008694) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_COL                       FIO_ADDRESS(VO_DISPLAY,0x90008698) /* read/write */
#define REG_VO_DISPLAY_ANALOG_VBI_DATA                      FIO_ADDRESS(VO_DISPLAY,0x9000869C) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_0                   FIO_ADDRESS(VO_DISPLAY,0x900086CC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_1                   FIO_ADDRESS(VO_DISPLAY,0x900086D0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_2                   FIO_ADDRESS(VO_DISPLAY,0x900086D4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_3                   FIO_ADDRESS(VO_DISPLAY,0x900086D8) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_4                   FIO_ADDRESS(VO_DISPLAY,0x900086DC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_PARAM_5                   FIO_ADDRESS(VO_DISPLAY,0x900086E0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_0                 FIO_ADDRESS(VO_DISPLAY,0x900086E4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_1                 FIO_ADDRESS(VO_DISPLAY,0x900086E8) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_2                 FIO_ADDRESS(VO_DISPLAY,0x900086EC) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_3                 FIO_ADDRESS(VO_DISPLAY,0x900086F0) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_4                 FIO_ADDRESS(VO_DISPLAY,0x900086F4) /* write */
#define REG_VO_DISPLAY_ANALOG_CSC_2_PARAM_5                 FIO_ADDRESS(VO_DISPLAY,0x900086F8) /* write */
#define REG_VO_DISPLAY_ANALOG_SD_SCALE_Y                    FIO_ADDRESS(VO_DISPLAY,0x900086FC) /* write */
#define REG_VO_DISPLAY_ANALOG_SD_SCALE_PBPR                 FIO_ADDRESS(VO_DISPLAY,0x90008700) /* write */
#define REG_VO_DISPLAY_HDMI_OUTPUT_MODE                     FIO_ADDRESS(VO_DISPLAY,0x90008704) /* read/write */
#define REG_VO_DISPLAY_HDMI_HSYNC_CONTROL                   FIO_ADDRESS(VO_DISPLAY,0x90008708) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_START_0                   FIO_ADDRESS(VO_DISPLAY,0x9000870C) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_END_0                     FIO_ADDRESS(VO_DISPLAY,0x90008710) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_START_1                   FIO_ADDRESS(VO_DISPLAY,0x90008714) /* read/write */
#define REG_VO_DISPLAY_HDMI_VSYNC_END_1                     FIO_ADDRESS(VO_DISPLAY,0x90008718) /* read/write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_0                     FIO_ADDRESS(VO_DISPLAY,0x9000871C) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_1                     FIO_ADDRESS(VO_DISPLAY,0x90008720) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_2                     FIO_ADDRESS(VO_DISPLAY,0x90008724) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_3                     FIO_ADDRESS(VO_DISPLAY,0x90008728) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_4                     FIO_ADDRESS(VO_DISPLAY,0x9000872C) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_5                     FIO_ADDRESS(VO_DISPLAY,0x90008730) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_6                     FIO_ADDRESS(VO_DISPLAY,0x90008734) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_7                     FIO_ADDRESS(VO_DISPLAY,0x90008738) /* write */
#define REG_VO_DISPLAY_HDMI_CSC_PARAM_8                     FIO_ADDRESS(VO_DISPLAY,0x9000873C) /* write */
#define REG_VO_DISPLAY_DIGITAL_DITHER_SETTINGS              FIO_ADDRESS(VO_DISPLAY,0x90008754) /* read/write */
#define REG_VO_DISPLAY_DIGITAL_DITHER_SEED                  FIO_ADDRESS(VO_DISPLAY,0x90008758) /* read/write */
#define REG_VO_DISPLAY_VOUT_VOUT_SYNC                       FIO_ADDRESS(VO_DISPLAY,0x9000875C) /* read/write */
#define REG_VO_DISPLAY_INPUT_STREAM_ENABLES                 FIO_ADDRESS(VO_DISPLAY,0x90008760) /* read/write */
#define REG_VO_DISPLAY_INPUT_SYNC_CONTROL                   FIO_ADDRESS(VO_DISPLAY,0x90008764) /* read/write */
#define REG_VO_DISPLAY_OUTPUT_SYNC_CONTROL                  FIO_ADDRESS(VO_DISPLAY,0x90008768) /* read/write */
#define REG_VO_DISPLAY_STREAM_CONTROL                       FIO_ADDRESS(VO_DISPLAY,0x9000876C) /* read/write */
#define REG_VO_DISPLAY_FRAME_ENABLE                         FIO_ADDRESS(VO_DISPLAY,0x90008770) /* read/write */

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
} GH_VO_DISPLAY_CONTROL_S;

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
} GH_VO_DISPLAY_STATUS_S;

typedef union { /* VO_DISPLAY_FRAME_SIZE_FIELD0 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 2;
        U32 width                       : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_FRAME_SIZE_FIELD0_S;

typedef union { /* VO_DISPLAY_FRAME_SIZE_FIELD1 */
    U32 all;
    struct {
        U32 height                      : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY_FRAME_SIZE_FIELD1_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_START_FIELD0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD0_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_END_0_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_START_FIELD1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_START_FIELD1_S;

typedef union { /* VO_DISPLAY_ACTIVE_REGION_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ACTIVE_REGION_END_1_S;

typedef union { /* VO_DISPLAY_BACKGROUND */
    U32 all;
    struct {
        U32 v                           : 8;
        U32 u                           : 8;
        U32 y                           : 8;
        U32                             : 8;
    } bitc;
} GH_VO_DISPLAY_BACKGROUND_S;

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
} GH_VO_DISPLAY_DIGITAL_OUTPUT_S;

typedef union { /* VO_DISPLAY_DIGITAL_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_HSYNC_CONTROL_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_START_0_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_END_0_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_START_1_S;

typedef union { /* VO_DISPLAY_DIGITAL_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_VSYNC_END_1_S;

typedef union { /* VO_DISPLAY_DIGITAL_656_VBIT */
    U32 all;
    struct {
        U32 end_row                     : 14;
        U32                             : 2;
        U32 start_row                   : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_656_VBIT_S;

typedef union { /* VO_DISPLAY_DIGITAL_656_SAV_START */
    U32 all;
    struct {
        U32 code_location               : 14;
        U32                             : 18;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_656_SAV_START_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_6 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_7 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_S;

typedef union { /* VO_DISPLAY_DIGITAL_CSC_PARAM_8 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_S;

typedef union { /* VO_DISPLAY_ANALOG_OUTPUT_MODE */
    U32 all;
    struct {
        U32 hsync_polarity              : 1;
        U32 vsync_polarity              : 1;
        U32                             : 30;
    } bitc;
} GH_VO_DISPLAY_ANALOG_OUTPUT_MODE_S;

typedef union { /* VO_DISPLAY_ANALOG_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_HSYNC_CONTROL_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_START_0_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_END_0_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_START_1_S;

typedef union { /* VO_DISPLAY_ANALOG_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VSYNC_END_1_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_CONTROL */
    U32 all;
    struct {
        U32 zero_level                  : 10;
        U32 one_level                   : 10;
        U32 repeat_count                : 7;
        U32 sd_component                : 1;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_CONTROL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_ROW */
    U32 all;
    struct {
        U32 start_field_0               : 14;
        U32                             : 2;
        U32 start_field_1               : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_ROW_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_COL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_COL_S;

typedef union { /* VO_DISPLAY_ANALOG_VBI_DATA */
    U32 all;
    struct {
        U32 output                      : 32;
    } bitc;
} GH_VO_DISPLAY_ANALOG_VBI_DATA_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0              : 13;
        U32                             : 3;
        U32 coefficient_a4              : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 output012_clamp_low         : 10;
        U32                             : 6;
        U32 output012_clamp_high        : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_0 */
    U32 all;
    struct {
        U32                             : 16;
        U32 coefficient_a4              : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 19;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_2 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 17;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_3 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_4 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_S;

typedef union { /* VO_DISPLAY_ANALOG_CSC_2_PARAM_5 */
    U32 all;
    struct {
        U32 output1_clamp_low           : 10;
        U32                             : 6;
        U32 output1_clamp_high          : 10;
        U32                             : 6;
    } bitc;
} GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_S;

typedef union { /* VO_DISPLAY_ANALOG_SD_SCALE_Y */
    U32 all;
    struct {
        U32 y_coefficient               : 11;
        U32                             : 5;
        U32 enable                      : 1;
        U32                             : 15;
    } bitc;
} GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_S;

typedef union { /* VO_DISPLAY_ANALOG_SD_SCALE_PBPR */
    U32 all;
    struct {
        U32 pr_coefficient              : 11;
        U32                             : 5;
        U32 pb_coefficient              : 11;
        U32                             : 5;
    } bitc;
} GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_S;

typedef union { /* VO_DISPLAY_HDMI_OUTPUT_MODE */
    U32 all;
    struct {
        U32 hsync_polarity              : 1;
        U32 vsync_polarity              : 1;
        U32                             : 27;
        U32 mode                        : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_OUTPUT_MODE_S;

typedef union { /* VO_DISPLAY_HDMI_HSYNC_CONTROL */
    U32 all;
    struct {
        U32 end_column                  : 14;
        U32                             : 2;
        U32 start_column                : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_HSYNC_CONTROL_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_START_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_START_0_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_END_0 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_END_0_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_START_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_START_1_S;

typedef union { /* VO_DISPLAY_HDMI_VSYNC_END_1 */
    U32 all;
    struct {
        U32 row                         : 14;
        U32                             : 2;
        U32 column                      : 14;
        U32                             : 2;
    } bitc;
} GH_VO_DISPLAY_HDMI_VSYNC_END_1_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_0 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_0_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_1 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_1_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_2 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_2_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_3 */
    U32 all;
    struct {
        U32 coefficient_a0246           : 13;
        U32                             : 3;
        U32 coefficient_a1357           : 13;
        U32                             : 3;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_3_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_4 */
    U32 all;
    struct {
        U32 coefficient_a8              : 13;
        U32                             : 3;
        U32 constant_b0                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_4_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_5 */
    U32 all;
    struct {
        U32 constant_b1                 : 15;
        U32                             : 1;
        U32 constant_b2                 : 15;
        U32                             : 1;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_5_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_6 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_6_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_7 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_7_S;

typedef union { /* VO_DISPLAY_HDMI_CSC_PARAM_8 */
    U32 all;
    struct {
        U32 output_012_clamp_low        : 12;
        U32                             : 4;
        U32 output_012_clamp_high       : 12;
        U32                             : 4;
    } bitc;
} GH_VO_DISPLAY_HDMI_CSC_PARAM_8_S;

typedef union { /* VO_DISPLAY_VOUT_VOUT_SYNC */
    U32 all;
    struct {
        U32 start_row                   : 14;
        U32                             : 2;
        U32 field_select                : 1;
        U32                             : 15;
    } bitc;
} GH_VO_DISPLAY_VOUT_VOUT_SYNC_S;


/*----------------------------------------------------------------------------*/
/* mirror variables                                                           */
/*----------------------------------------------------------------------------*/
extern GH_VO_DISPLAY_BACKGROUND_S              m_vo_display_background;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_0_S     m_vo_display_digital_csc_param_0;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_1_S     m_vo_display_digital_csc_param_1;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_2_S     m_vo_display_digital_csc_param_2;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_3_S     m_vo_display_digital_csc_param_3;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_4_S     m_vo_display_digital_csc_param_4;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_5_S     m_vo_display_digital_csc_param_5;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_6_S     m_vo_display_digital_csc_param_6;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_7_S     m_vo_display_digital_csc_param_7;
extern GH_VO_DISPLAY_DIGITAL_CSC_PARAM_8_S     m_vo_display_digital_csc_param_8;
extern GH_VO_DISPLAY_ANALOG_VBI_DATA_S         m_vo_display_analog_vbi_data[12];
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_0_S      m_vo_display_analog_csc_param_0;
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_1_S      m_vo_display_analog_csc_param_1;
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_2_S      m_vo_display_analog_csc_param_2;
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_3_S      m_vo_display_analog_csc_param_3;
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_4_S      m_vo_display_analog_csc_param_4;
extern GH_VO_DISPLAY_ANALOG_CSC_PARAM_5_S      m_vo_display_analog_csc_param_5;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_0_S    m_vo_display_analog_csc_2_param_0;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_1_S    m_vo_display_analog_csc_2_param_1;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_2_S    m_vo_display_analog_csc_2_param_2;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_3_S    m_vo_display_analog_csc_2_param_3;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_4_S    m_vo_display_analog_csc_2_param_4;
extern GH_VO_DISPLAY_ANALOG_CSC_2_PARAM_5_S    m_vo_display_analog_csc_2_param_5;
extern GH_VO_DISPLAY_ANALOG_SD_SCALE_Y_S       m_vo_display_analog_sd_scale_y;
extern GH_VO_DISPLAY_ANALOG_SD_SCALE_PBPR_S    m_vo_display_analog_sd_scale_pbpr;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_0_S        m_vo_display_hdmi_csc_param_0;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_1_S        m_vo_display_hdmi_csc_param_1;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_2_S        m_vo_display_hdmi_csc_param_2;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_3_S        m_vo_display_hdmi_csc_param_3;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_4_S        m_vo_display_hdmi_csc_param_4;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_5_S        m_vo_display_hdmi_csc_param_5;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_6_S        m_vo_display_hdmi_csc_param_6;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_7_S        m_vo_display_hdmi_csc_param_7;
extern GH_VO_DISPLAY_HDMI_CSC_PARAM_8_S        m_vo_display_hdmi_csc_param_8;

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_CONTROL (read/write)                                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_CONTROL'. */
U32  GH_VO_DISPLAY_get_CONTROL(void);
/*! \brief Writes the bit group 'Fixed_Format' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Fixed_Format(U8 data);
/*! \brief Reads the bit group 'Fixed_Format' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Fixed_Format(void);
/*! \brief Writes the bit group 'Interlace_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Interlace_Enable(U8 data);
/*! \brief Reads the bit group 'Interlace_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Interlace_Enable(void);
/*! \brief Writes the bit group 'Reverse_Mode_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Reverse_Mode_Enable(U8 data);
/*! \brief Reads the bit group 'Reverse_Mode_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Reverse_Mode_Enable(void);
/*! \brief Writes the bit group 'VOUT_VOUT_Sync_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_VOUT_VOUT_Sync_Enable(U8 data);
/*! \brief Reads the bit group 'VOUT_VOUT_Sync_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_VOUT_VOUT_Sync_Enable(void);
/*! \brief Writes the bit group 'VIN_VOUT_Sync_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_VIN_VOUT_Sync_Enable(U8 data);
/*! \brief Reads the bit group 'VIN_VOUT_Sync_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_VIN_VOUT_Sync_Enable(void);
/*! \brief Writes the bit group 'Digital_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Digital_Output_Enable(U8 data);
/*! \brief Reads the bit group 'Digital_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Digital_Output_Enable(void);
/*! \brief Writes the bit group 'Analog_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Analog_Output_Enable(U8 data);
/*! \brief Reads the bit group 'Analog_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Analog_Output_Enable(void);
/*! \brief Writes the bit group 'HDMI_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_HDMI_Output_Enable(U8 data);
/*! \brief Reads the bit group 'HDMI_Output_Enable' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_HDMI_Output_Enable(void);
/*! \brief Writes the bit group 'DVE_Reset' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_DVE_Reset(U8 data);
/*! \brief Reads the bit group 'DVE_Reset' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_DVE_Reset(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_DISPLAY_CONTROL'. */
void GH_VO_DISPLAY_set_CONTROL_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_DISPLAY_CONTROL'. */
U8   GH_VO_DISPLAY_get_CONTROL_Reset(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_STATUS (read/write)                                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_STATUS'. */
U32  GH_VO_DISPLAY_get_STATUS(void);
/*! \brief Writes the bit group 'HDMI_Field' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_HDMI_Field(U8 data);
/*! \brief Reads the bit group 'HDMI_Field' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_HDMI_Field(void);
/*! \brief Writes the bit group 'Analog_Fied' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_Analog_Fied(U8 data);
/*! \brief Reads the bit group 'Analog_Fied' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_Analog_Fied(void);
/*! \brief Writes the bit group 'Digital_Field' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_Digital_Field(U8 data);
/*! \brief Reads the bit group 'Digital_Field' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_Digital_Field(void);
/*! \brief Writes the bit group 'HDMI_Underflow' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_HDMI_Underflow(U8 data);
/*! \brief Reads the bit group 'HDMI_Underflow' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_HDMI_Underflow(void);
/*! \brief Writes the bit group 'Analog_Underflow' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_Analog_Underflow(U8 data);
/*! \brief Reads the bit group 'Analog_Underflow' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_Analog_Underflow(void);
/*! \brief Writes the bit group 'Digital_Underflow' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_Digital_Underflow(U8 data);
/*! \brief Reads the bit group 'Digital_Underflow' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_Digital_Underflow(void);
/*! \brief Writes the bit group 'SDTV_Configuration_Ready' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_SDTV_Configuration_Ready(U8 data);
/*! \brief Reads the bit group 'SDTV_Configuration_Ready' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_SDTV_Configuration_Ready(void);
/*! \brief Writes the bit group 'Reset' of register 'VO_DISPLAY_STATUS'. */
void GH_VO_DISPLAY_set_STATUS_Reset(U8 data);
/*! \brief Reads the bit group 'Reset' of register 'VO_DISPLAY_STATUS'. */
U8   GH_VO_DISPLAY_get_STATUS_Reset(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_SIZE_FIELD0 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
U32  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0(void);
/*! \brief Writes the bit group 'Height' of register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0_Height(U16 data);
/*! \brief Reads the bit group 'Height' of register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0_Height(void);
/*! \brief Writes the bit group 'Width' of register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD0_Width(U16 data);
/*! \brief Reads the bit group 'Width' of register 'VO_DISPLAY_FRAME_SIZE_FIELD0'. */
U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD0_Width(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_SIZE_FIELD1 (read/write)                         */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_FRAME_SIZE_FIELD1'. */
void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_FRAME_SIZE_FIELD1'. */
U32  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD1(void);
/*! \brief Writes the bit group 'Height' of register 'VO_DISPLAY_FRAME_SIZE_FIELD1'. */
void GH_VO_DISPLAY_set_FRAME_SIZE_FIELD1_Height(U16 data);
/*! \brief Reads the bit group 'Height' of register 'VO_DISPLAY_FRAME_SIZE_FIELD1'. */
U16  GH_VO_DISPLAY_get_FRAME_SIZE_FIELD1_Height(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_START_FIELD0 (read/write)                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
U32  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD0'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_END_0 (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
U32  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_END_0'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_START_FIELD1 (read/write)                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
U32  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_START_FIELD1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_START_FIELD1'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_START_FIELD1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ACTIVE_REGION_END_1 (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
U32  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
void GH_VO_DISPLAY_set_ACTIVE_REGION_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ACTIVE_REGION_END_1'. */
U16  GH_VO_DISPLAY_get_ACTIVE_REGION_END_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_BACKGROUND (write)                                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_BACKGROUND'. */
void GH_VO_DISPLAY_set_BACKGROUND(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_BACKGROUND'. */
U32  GH_VO_DISPLAY_getm_BACKGROUND(void);
/*! \brief Writes the bit group 'v' of register 'VO_DISPLAY_BACKGROUND'. */
void GH_VO_DISPLAY_set_BACKGROUND_v(U8 data);
/*! \brief Reads the bit group 'v' from the mirror variable of register 'VO_DISPLAY_BACKGROUND'. */
U8   GH_VO_DISPLAY_getm_BACKGROUND_v(void);
/*! \brief Writes the bit group 'u' of register 'VO_DISPLAY_BACKGROUND'. */
void GH_VO_DISPLAY_set_BACKGROUND_u(U8 data);
/*! \brief Reads the bit group 'u' from the mirror variable of register 'VO_DISPLAY_BACKGROUND'. */
U8   GH_VO_DISPLAY_getm_BACKGROUND_u(void);
/*! \brief Writes the bit group 'y' of register 'VO_DISPLAY_BACKGROUND'. */
void GH_VO_DISPLAY_set_BACKGROUND_y(U8 data);
/*! \brief Reads the bit group 'y' from the mirror variable of register 'VO_DISPLAY_BACKGROUND'. */
U8   GH_VO_DISPLAY_getm_BACKGROUND_y(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_OUTPUT (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U32  GH_VO_DISPLAY_get_DIGITAL_OUTPUT(void);
/*! \brief Writes the bit group 'Digital_Hsync_Polarity' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Hsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Digital_Hsync_Polarity' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Hsync_Polarity(void);
/*! \brief Writes the bit group 'Digital_Vsync_Polarity' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Vsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Digital_Vsync_Polarity' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Vsync_Polarity(void);
/*! \brief Writes the bit group 'Digital_Clock_Output_Divider' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Output_Divider' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Output_Divider(void);
/*! \brief Writes the bit group 'Digital_Clock_Divider_Enable' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Divider_Enable' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Enable(void);
/*! \brief Writes the bit group 'Digital_Clock_Edge' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Edge(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Edge' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Edge(void);
/*! \brief Writes the bit group 'Digital_Clock_Disable' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Disable(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Disable' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Disable(void);
/*! \brief Writes the bit group 'Digital_Clock_Divider_Pattern_Width' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(U8 data);
/*! \brief Reads the bit group 'Digital_Clock_Divider_Pattern_Width' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Digital_Clock_Divider_Pattern_Width(void);
/*! \brief Writes the bit group 'MIPI_Configuration' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_MIPI_Configuration(U8 data);
/*! \brief Reads the bit group 'MIPI_Configuration' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_MIPI_Configuration(void);
/*! \brief Writes the bit group 'Color_Sequence_Even_Lines' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(U8 data);
/*! \brief Reads the bit group 'Color_Sequence_Even_Lines' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Color_Sequence_Even_Lines(void);
/*! \brief Writes the bit group 'Color_Sequence_Odd_Lines' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(U8 data);
/*! \brief Reads the bit group 'Color_Sequence_Odd_Lines' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Color_Sequence_Odd_Lines(void);
/*! \brief Writes the bit group 'Mode' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
void GH_VO_DISPLAY_set_DIGITAL_OUTPUT_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'VO_DISPLAY_DIGITAL_OUTPUT'. */
U8   GH_VO_DISPLAY_get_DIGITAL_OUTPUT_Mode(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_HSYNC_CONTROL (read/write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
U32  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL(void);
/*! \brief Writes the bit group 'end_column' of register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL_end_column(U16 data);
/*! \brief Reads the bit group 'end_column' of register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL_end_column(void);
/*! \brief Writes the bit group 'start_column' of register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_DIGITAL_HSYNC_CONTROL_start_column(U16 data);
/*! \brief Reads the bit group 'start_column' of register 'VO_DISPLAY_DIGITAL_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_DIGITAL_HSYNC_CONTROL_start_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_START_0 (read/write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_END_0 (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_START_1 (read/write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_START_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_START_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_VSYNC_END_1 (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
U32  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_DIGITAL_VSYNC_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_DIGITAL_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_DIGITAL_VSYNC_END_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_656_VBIT (read/write)                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY_set_DIGITAL_656_VBIT(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
U32  GH_VO_DISPLAY_get_DIGITAL_656_VBIT(void);
/*! \brief Writes the bit group 'end_row' of register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY_set_DIGITAL_656_VBIT_end_row(U16 data);
/*! \brief Reads the bit group 'end_row' of register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
U16  GH_VO_DISPLAY_get_DIGITAL_656_VBIT_end_row(void);
/*! \brief Writes the bit group 'start_row' of register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
void GH_VO_DISPLAY_set_DIGITAL_656_VBIT_start_row(U16 data);
/*! \brief Reads the bit group 'start_row' of register 'VO_DISPLAY_DIGITAL_656_VBIT'. */
U16  GH_VO_DISPLAY_get_DIGITAL_656_VBIT_start_row(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_656_SAV_START (read/write)                     */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_656_SAV_START'. */
void GH_VO_DISPLAY_set_DIGITAL_656_SAV_START(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_656_SAV_START'. */
U32  GH_VO_DISPLAY_get_DIGITAL_656_SAV_START(void);
/*! \brief Writes the bit group 'Code_Location' of register 'VO_DISPLAY_DIGITAL_656_SAV_START'. */
void GH_VO_DISPLAY_set_DIGITAL_656_SAV_START_Code_Location(U16 data);
/*! \brief Reads the bit group 'Code_Location' of register 'VO_DISPLAY_DIGITAL_656_SAV_START'. */
U16  GH_VO_DISPLAY_get_DIGITAL_656_SAV_START_Code_Location(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN0 (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN0'. */
void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN0'. */
U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN1 (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN1'. */
void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN1'. */
U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN2 (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN2'. */
void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN2(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN2'. */
U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CLOCK_PATTERN3 (read/write)                    */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN3'. */
void GH_VO_DISPLAY_set_DIGITAL_CLOCK_PATTERN3(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_CLOCK_PATTERN3'. */
U32  GH_VO_DISPLAY_get_DIGITAL_CLOCK_PATTERN3(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_0 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_0_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_0_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_1 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_1_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_1_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_2 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_2_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_2_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_3 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_3_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_3_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_4 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4(void);
/*! \brief Writes the bit group 'Coefficient_a8' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4_Coefficient_a8(U16 data);
/*! \brief Reads the bit group 'Coefficient_a8' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Coefficient_a8(void);
/*! \brief Writes the bit group 'Constant_b0' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_4_Constant_b0(U16 data);
/*! \brief Reads the bit group 'Constant_b0' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_4_Constant_b0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_5 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5(void);
/*! \brief Writes the bit group 'Constant_b1' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5_Constant_b1(U16 data);
/*! \brief Reads the bit group 'Constant_b1' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b1(void);
/*! \brief Writes the bit group 'Constant_b2' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_5_Constant_b2(U16 data);
/*! \brief Reads the bit group 'Constant_b2' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_5_Constant_b2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_6 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_6_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_7 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_7_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_CSC_PARAM_8 (write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
U32  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_DIGITAL_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY_getm_DIGITAL_CSC_PARAM_8_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_OUTPUT_MODE (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
U32  GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE(void);
/*! \brief Writes the bit group 'Hsync_Polarity' of register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE_Hsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Hsync_Polarity' of register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
U8   GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE_Hsync_Polarity(void);
/*! \brief Writes the bit group 'Vsync_Polarity' of register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_ANALOG_OUTPUT_MODE_Vsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Vsync_Polarity' of register 'VO_DISPLAY_ANALOG_OUTPUT_MODE'. */
U8   GH_VO_DISPLAY_get_ANALOG_OUTPUT_MODE_Vsync_Polarity(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_HSYNC_CONTROL (read/write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
U32  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL(void);
/*! \brief Writes the bit group 'end_column' of register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL_end_column(U16 data);
/*! \brief Reads the bit group 'end_column' of register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL_end_column(void);
/*! \brief Writes the bit group 'start_column' of register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_HSYNC_CONTROL_start_column(U16 data);
/*! \brief Reads the bit group 'start_column' of register 'VO_DISPLAY_ANALOG_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_ANALOG_HSYNC_CONTROL_start_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_START_0 (read/write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_END_0 (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_START_1 (read/write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_START_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_START_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VSYNC_END_1 (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
U32  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_ANALOG_VSYNC_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_ANALOG_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_ANALOG_VSYNC_END_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
U32  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL(void);
/*! \brief Writes the bit group 'Zero_Level' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_Zero_Level(U16 data);
/*! \brief Reads the bit group 'Zero_Level' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_Zero_Level(void);
/*! \brief Writes the bit group 'One_Level' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_One_Level(U16 data);
/*! \brief Reads the bit group 'One_Level' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_One_Level(void);
/*! \brief Writes the bit group 'Repeat_Count' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_Repeat_Count(U8 data);
/*! \brief Reads the bit group 'Repeat_Count' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
U8   GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_Repeat_Count(void);
/*! \brief Writes the bit group 'SD_Component' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_CONTROL_SD_Component(U8 data);
/*! \brief Reads the bit group 'SD_Component' of register 'VO_DISPLAY_ANALOG_VBI_CONTROL'. */
U8   GH_VO_DISPLAY_get_ANALOG_VBI_CONTROL_SD_Component(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_ROW (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_ROW(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
U32  GH_VO_DISPLAY_get_ANALOG_VBI_ROW(void);
/*! \brief Writes the bit group 'start_field_0' of register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_ROW_start_field_0(U16 data);
/*! \brief Reads the bit group 'start_field_0' of register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_ROW_start_field_0(void);
/*! \brief Writes the bit group 'start_field_1' of register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_ROW_start_field_1(U16 data);
/*! \brief Reads the bit group 'start_field_1' of register 'VO_DISPLAY_ANALOG_VBI_ROW'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_ROW_start_field_1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_COL (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VBI_COL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_COL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_ANALOG_VBI_COL'. */
U32  GH_VO_DISPLAY_get_ANALOG_VBI_COL(void);
/*! \brief Writes the bit group 'end_column' of register 'VO_DISPLAY_ANALOG_VBI_COL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_COL_end_column(U16 data);
/*! \brief Reads the bit group 'end_column' of register 'VO_DISPLAY_ANALOG_VBI_COL'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_COL_end_column(void);
/*! \brief Writes the bit group 'start_column' of register 'VO_DISPLAY_ANALOG_VBI_COL'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_COL_start_column(U16 data);
/*! \brief Reads the bit group 'start_column' of register 'VO_DISPLAY_ANALOG_VBI_COL'. */
U16  GH_VO_DISPLAY_get_ANALOG_VBI_COL_start_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_VBI_DATA (write)                                */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_VBI_DATA'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_DATA(U8 index, U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_VBI_DATA'. */
U32  GH_VO_DISPLAY_getm_ANALOG_VBI_DATA(U8 index);
/*! \brief Writes the bit group 'Output' of register 'VO_DISPLAY_ANALOG_VBI_DATA'. */
void GH_VO_DISPLAY_set_ANALOG_VBI_DATA_Output(U8 index, U32 data);
/*! \brief Reads the bit group 'Output' from the mirror variable of register 'VO_DISPLAY_ANALOG_VBI_DATA'. */
U32  GH_VO_DISPLAY_getm_ANALOG_VBI_DATA_Output(U8 index);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_0 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0(void);
/*! \brief Writes the bit group 'Coefficient_a0' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0_Coefficient_a0(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a0(void);
/*! \brief Writes the bit group 'Coefficient_a4' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_0_Coefficient_a4(U16 data);
/*! \brief Reads the bit group 'Coefficient_a4' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_0_Coefficient_a4(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_1 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1(void);
/*! \brief Writes the bit group 'Coefficient_a8' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1_Coefficient_a8(U16 data);
/*! \brief Reads the bit group 'Coefficient_a8' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Coefficient_a8(void);
/*! \brief Writes the bit group 'Constant_b0' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_1_Constant_b0(U16 data);
/*! \brief Reads the bit group 'Constant_b0' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_1_Constant_b0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_2 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2(void);
/*! \brief Writes the bit group 'Constant_b1' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2_Constant_b1(U16 data);
/*! \brief Reads the bit group 'Constant_b1' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b1(void);
/*! \brief Writes the bit group 'Constant_b2' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_2_Constant_b2(U16 data);
/*! \brief Reads the bit group 'Constant_b2' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_2_Constant_b2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_3 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3(void);
/*! \brief Writes the bit group 'Output012_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3_Output012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output012_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_3_Output012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_3_Output012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_4 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4(void);
/*! \brief Writes the bit group 'Output012_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4_Output012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output012_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_4_Output012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_4_Output012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_PARAM_5 (write)                             */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5(void);
/*! \brief Writes the bit group 'Output012_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5_Output012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output012_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_PARAM_5_Output012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_PARAM_5_Output012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_0 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_0'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_0(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_0'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0(void);
/*! \brief Writes the bit group 'Coefficient_a4' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_0'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_0_Coefficient_a4(U16 data);
/*! \brief Reads the bit group 'Coefficient_a4' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_0_Coefficient_a4(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_1 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_1'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_1(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_1'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1(void);
/*! \brief Writes the bit group 'Coefficient_a8' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_1'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_1_Coefficient_a8(U16 data);
/*! \brief Reads the bit group 'Coefficient_a8' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_1_Coefficient_a8(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_2 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_2'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_2(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_2'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2(void);
/*! \brief Writes the bit group 'Constant_b1' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_2'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_2_Constant_b1(U16 data);
/*! \brief Reads the bit group 'Constant_b1' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_2_Constant_b1(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_3 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3(void);
/*! \brief Writes the bit group 'Output1_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3_Output1_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_Low(void);
/*! \brief Writes the bit group 'Output1_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_3_Output1_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_3_Output1_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_4 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4(void);
/*! \brief Writes the bit group 'Output1_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4_Output1_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_Low(void);
/*! \brief Writes the bit group 'Output1_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_4_Output1_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_4_Output1_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_CSC_2_PARAM_5 (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
U32  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5(void);
/*! \brief Writes the bit group 'Output1_Clamp_Low' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5_Output1_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_Low(void);
/*! \brief Writes the bit group 'Output1_Clamp_High' of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
void GH_VO_DISPLAY_set_ANALOG_CSC_2_PARAM_5_Output1_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output1_Clamp_High' from the mirror variable of register 'VO_DISPLAY_ANALOG_CSC_2_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_ANALOG_CSC_2_PARAM_5_Output1_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_SD_SCALE_Y (write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
U32  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y(void);
/*! \brief Writes the bit group 'Y_Coefficient' of register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y_Y_Coefficient(U16 data);
/*! \brief Reads the bit group 'Y_Coefficient' from the mirror variable of register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Y_Coefficient(void);
/*! \brief Writes the bit group 'Enable' of register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_Y_Enable(U8 data);
/*! \brief Reads the bit group 'Enable' from the mirror variable of register 'VO_DISPLAY_ANALOG_SD_SCALE_Y'. */
U8   GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_Y_Enable(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_ANALOG_SD_SCALE_PBPR (write)                           */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
U32  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR(void);
/*! \brief Writes the bit group 'Pr_Coefficient' of register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR_Pr_Coefficient(U16 data);
/*! \brief Reads the bit group 'Pr_Coefficient' from the mirror variable of register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pr_Coefficient(void);
/*! \brief Writes the bit group 'Pb_Coefficient' of register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
void GH_VO_DISPLAY_set_ANALOG_SD_SCALE_PBPR_Pb_Coefficient(U16 data);
/*! \brief Reads the bit group 'Pb_Coefficient' from the mirror variable of register 'VO_DISPLAY_ANALOG_SD_SCALE_PBPR'. */
U16  GH_VO_DISPLAY_getm_ANALOG_SD_SCALE_PBPR_Pb_Coefficient(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_OUTPUT_MODE (read/write)                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
U32  GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE(void);
/*! \brief Writes the bit group 'Hsync_Polarity' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Hsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Hsync_Polarity' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Hsync_Polarity(void);
/*! \brief Writes the bit group 'Vsync_Polarity' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Vsync_Polarity(U8 data);
/*! \brief Reads the bit group 'Vsync_Polarity' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Vsync_Polarity(void);
/*! \brief Writes the bit group 'Mode' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
void GH_VO_DISPLAY_set_HDMI_OUTPUT_MODE_Mode(U8 data);
/*! \brief Reads the bit group 'Mode' of register 'VO_DISPLAY_HDMI_OUTPUT_MODE'. */
U8   GH_VO_DISPLAY_get_HDMI_OUTPUT_MODE_Mode(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_HSYNC_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
U32  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL(void);
/*! \brief Writes the bit group 'end_column' of register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL_end_column(U16 data);
/*! \brief Reads the bit group 'end_column' of register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL_end_column(void);
/*! \brief Writes the bit group 'start_column' of register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
void GH_VO_DISPLAY_set_HDMI_HSYNC_CONTROL_start_column(U16 data);
/*! \brief Reads the bit group 'start_column' of register 'VO_DISPLAY_HDMI_HSYNC_CONTROL'. */
U16  GH_VO_DISPLAY_get_HDMI_HSYNC_CONTROL_start_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_START_0 (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
U32  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_START_0'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_END_0 (read/write)                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
U32  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_0_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_END_0'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_0_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_START_1 (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
U32  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_START_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_START_1'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_START_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_VSYNC_END_1 (read/write)                          */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
U32  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1(void);
/*! \brief Writes the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1_row(U16 data);
/*! \brief Reads the bit group 'row' of register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1_row(void);
/*! \brief Writes the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
void GH_VO_DISPLAY_set_HDMI_VSYNC_END_1_column(U16 data);
/*! \brief Reads the bit group 'column' of register 'VO_DISPLAY_HDMI_VSYNC_END_1'. */
U16  GH_VO_DISPLAY_get_HDMI_VSYNC_END_1_column(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_0 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_0_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_0'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_0_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_1 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_1_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_1'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_1_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_2 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_2_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_2'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_2_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_3 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3(void);
/*! \brief Writes the bit group 'Coefficient_a0246' of register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3_Coefficient_a0246(U16 data);
/*! \brief Reads the bit group 'Coefficient_a0246' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a0246(void);
/*! \brief Writes the bit group 'Coefficient_a1357' of register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_3_Coefficient_a1357(U16 data);
/*! \brief Reads the bit group 'Coefficient_a1357' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_3'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_3_Coefficient_a1357(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_4 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4(void);
/*! \brief Writes the bit group 'Coefficient_a8' of register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4_Coefficient_a8(U16 data);
/*! \brief Reads the bit group 'Coefficient_a8' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Coefficient_a8(void);
/*! \brief Writes the bit group 'Constant_b0' of register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_4_Constant_b0(U16 data);
/*! \brief Reads the bit group 'Constant_b0' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_4'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_4_Constant_b0(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_5 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5(void);
/*! \brief Writes the bit group 'Constant_b1' of register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5_Constant_b1(U16 data);
/*! \brief Reads the bit group 'Constant_b1' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b1(void);
/*! \brief Writes the bit group 'Constant_b2' of register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_5_Constant_b2(U16 data);
/*! \brief Reads the bit group 'Constant_b2' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_5'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_5_Constant_b2(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_6 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_6_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_6'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_6_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_7 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_7_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_7'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_7_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_HDMI_CSC_PARAM_8 (write)                               */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8(U32 data);
/*! \brief Reads the mirror variable of the register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
U32  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8(void);
/*! \brief Writes the bit group 'Output_012_Clamp_Low' of register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8_Output_012_Clamp_Low(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_Low' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_Low(void);
/*! \brief Writes the bit group 'Output_012_Clamp_High' of register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
void GH_VO_DISPLAY_set_HDMI_CSC_PARAM_8_Output_012_Clamp_High(U16 data);
/*! \brief Reads the bit group 'Output_012_Clamp_High' from the mirror variable of register 'VO_DISPLAY_HDMI_CSC_PARAM_8'. */
U16  GH_VO_DISPLAY_getm_HDMI_CSC_PARAM_8_Output_012_Clamp_High(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_DITHER_SETTINGS (read/write)                   */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_DITHER_SETTINGS'. */
void GH_VO_DISPLAY_set_DIGITAL_DITHER_SETTINGS(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_DITHER_SETTINGS'. */
U32  GH_VO_DISPLAY_get_DIGITAL_DITHER_SETTINGS(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_DIGITAL_DITHER_SEED (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_DIGITAL_DITHER_SEED'. */
void GH_VO_DISPLAY_set_DIGITAL_DITHER_SEED(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_DIGITAL_DITHER_SEED'. */
U32  GH_VO_DISPLAY_get_DIGITAL_DITHER_SEED(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_VOUT_VOUT_SYNC (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
U32  GH_VO_DISPLAY_get_VOUT_VOUT_SYNC(void);
/*! \brief Writes the bit group 'Start_Row' of register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC_Start_Row(U16 data);
/*! \brief Reads the bit group 'Start_Row' of register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
U16  GH_VO_DISPLAY_get_VOUT_VOUT_SYNC_Start_Row(void);
/*! \brief Writes the bit group 'Field_Select' of register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
void GH_VO_DISPLAY_set_VOUT_VOUT_SYNC_Field_Select(U8 data);
/*! \brief Reads the bit group 'Field_Select' of register 'VO_DISPLAY_VOUT_VOUT_SYNC'. */
U8   GH_VO_DISPLAY_get_VOUT_VOUT_SYNC_Field_Select(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_INPUT_STREAM_ENABLES (read/write)                      */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_INPUT_STREAM_ENABLES'. */
void GH_VO_DISPLAY_set_INPUT_STREAM_ENABLES(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_INPUT_STREAM_ENABLES'. */
U32  GH_VO_DISPLAY_get_INPUT_STREAM_ENABLES(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_INPUT_SYNC_CONTROL (read/write)                        */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_INPUT_SYNC_CONTROL'. */
void GH_VO_DISPLAY_set_INPUT_SYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_INPUT_SYNC_CONTROL'. */
U32  GH_VO_DISPLAY_get_INPUT_SYNC_CONTROL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_OUTPUT_SYNC_CONTROL (read/write)                       */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_OUTPUT_SYNC_CONTROL'. */
void GH_VO_DISPLAY_set_OUTPUT_SYNC_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_OUTPUT_SYNC_CONTROL'. */
U32  GH_VO_DISPLAY_get_OUTPUT_SYNC_CONTROL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_STREAM_CONTROL (read/write)                            */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_STREAM_CONTROL'. */
void GH_VO_DISPLAY_set_STREAM_CONTROL(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_STREAM_CONTROL'. */
U32  GH_VO_DISPLAY_get_STREAM_CONTROL(void);

/*----------------------------------------------------------------------------*/
/* register VO_DISPLAY_FRAME_ENABLE (read/write)                              */
/*----------------------------------------------------------------------------*/
/*! \brief Writes the register 'VO_DISPLAY_FRAME_ENABLE'. */
void GH_VO_DISPLAY_set_FRAME_ENABLE(U32 data);
/*! \brief Reads the register 'VO_DISPLAY_FRAME_ENABLE'. */
U32  GH_VO_DISPLAY_get_FRAME_ENABLE(void);

/*----------------------------------------------------------------------------*/
/* init function                                                              */
/*----------------------------------------------------------------------------*/
/*! \brief Initialises the registers and mirror variables. */
void GH_VO_DISPLAY_init(void);

#ifdef SRC_INLINE
#define SRC_INC 1
#include "gh_vo_display.c"
#undef SRC_INC
#endif

#ifdef __cplusplus
}
#endif

#endif /* _GH_VO_DISPLAY_H */

/*----------------------------------------------------------------------------*/
/* end of file                                                                */
/*----------------------------------------------------------------------------*/

