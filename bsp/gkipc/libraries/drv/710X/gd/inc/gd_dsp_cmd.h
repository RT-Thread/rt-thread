/*!
*****************************************************************************
** \file        gd_lib/GK7101/inc/gd_dsp_cmd.h
**
** \version     $Id$
**
** \brief
**
** \attention   THIS SAMPLE CODE IS PROVIDED AS IS. GOKE MICROELECTRONICS
**              ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR
**              OMMISSIONS
**
** (C) Copyright 2012-2013 by GOKE MICROELECTRONICS CO.,LTD
**
*****************************************************************************
*/
#ifndef _GD_IDSP_CMD_H_
#define _GD_IDSP_CMD_H_


#include <gtypes.h>
#include <gmodids.h>
#include "gd_i2c.h"


//*****************************************************************************
//*****************************************************************************
//** Defines and Macros
//*****************************************************************************
//*****************************************************************************
#define GD_IDSP_SECTION_FILTER(x,y)      ((x<<8)|(y<<4))

/* Configuration commands */
#define GD_INTERRUPT_SETUP                  0x00001001
#define GD_H264_ENCODING_SETUP              0x00001002
#define GD_JPEG_ENCODING_SETUP              0x00001003
#define GD_H264_DECODING_SETUP              0x00001004
#define GD_JPEG_DECODING_SETUP              0x00001005
#define GD_RESET_OPERATION                  0x00001006
#define GD_VIDEO_OUTPUT_RESTART             0x00001007
#define GD_H264_ENC_USE_TIMER               0x00001008
#define GD_CHIP_SELECTION                   0x00001009
#define GD_HD_ECHO_SETUP                    0x0000100A
#define GD_SYSTEM_SETUP_INFO                0x0000100B
#define GD_EIS_SWITCHVOUT_DURING_ENCODE     0x0000100C
#define GD_DSP_DEBUG_LEVEL_SETUP            0x0000100D
#define GD_SYSTEM_PARAMETERS_SETUP          0x0000100E
#define GD_SYSTEM_IDSP_FREQ_SETUP           0x0000100F

#define GD_SENSOR_INPUT_SETUP               0x00002001
#define GD_RGB_GAIN_ADJUSTMENT              0x00002002
#define GD_VIGNETTE_COMPENSATION            0x00002003
#define GD_AAA_STATISTICS_SETUP             0x00002004
#define GD_LUMA_SHARPEN_SETUP               0x00002005
#define GD_RGB_TO_RGB_SETUP                 0x00002006
#define GD_RGB_TO_YUV_SETUP                 0x00002007
#define GD_GAMMA_CURVE_LOOKUP               0x00002008
#define GD_NOISE_FILTER_SETUP               0x00002009
#define GD_BAD_PIXEL_CORRECT_SETUP          0x0000200A
#define GD_VID_FADE_IN_OUT_SETUP            0x0000200B
#define GD_CFA_DOMAIN_LEAKAGE_FILTER        0x0000200C
#define GD_MCTF_MV_STAB_SETUP               0x0000200D
#define GD_SET_SLOW_SHUT_UP_SAMPL_RT        0x0000200E
#define GD_SET_REPEAT_FRM                   0x0000200F
#define GD_MCTF_GMV_SETUP                   0x00002010
#define GD_DIS_SETUP                        0x00002011    //This command is used to setup the DIS algorithm paramete and related debug stuff.

#define GD_SET_VIN_CAPTURE_WIN              0x00002100
#define GD_AMPLIFIER_LINEARIZATION          0x00002101
#define GD_PIXEL_SHUFFLE                    0x00002102
#define GD_BLACK_LEVEL_CORRECTION_CONFIG    0x00002103
#define GD_BLACK_LEVEL_STATE_TABLES         0x00002104
#define GD_BLACK_LEVEL_DETECTION_WINDOW     0x00002105
#define GD_FIXED_PATTERN_NOISE_CORRECTION   0x00002106
#define GD_CFA_NOISE_FILTER_INFO            0x00002107
#define GD_DIGITAL_GAIN_SATURATION_LEVEL    0x00002108
#define GD_LOCAL_EXPOSURE                   0x00002109
#define GD_DEMOASIC_FILTER                  0x0000210A
#define GD_RGB_NOISE_FILTER                 0x0000210B
#define GD_COLOR_CORRECTION                 0x0000210C
#define GD_CHROMA_MEDIAN_FILTER_INFO        0x0000210D
#define GD_CHROMA_SCALE                     0x0000210E
#define GD_LUMA_SHARPENING                  0x0000210F
#define GD_AAA_STATISTICS_SETUP1            0x00002110
#define GD_AAA_STATISTICS_SETUP2            0x00002111
#define GD_AAA_PSEUDO_Y_SETUP               0x00002112
#define GD_AAA_HISTORGRAM_SETUP             0x00002113
#define GD_RAW_COMPRESSION                  0x00002114
#define GD_RAW_DECOMPRESSION                0x00002115
#define GD_ROLLING_SHUTTER_COMPENSATION     0x00002116
#define GD_SET_ZOOM_FACTOR                  0x00002117
#define GD_AAA_STATISTICS_SETUP3            0x00002118
#define GD_VIDEO_PREVIEW_SETUP              0x00002119
#define GD_VIN_RESET                        0x0000211A
#define GD_ANTI_ALIASING                    0x0000211B
#define GD_FPN_CALIBRATION                  0x0000211C
#define GD_BLACK_LEVEL_GLOBAL_OFFSET        0x0000211D
#define GD_RGB_DIRECTIONAL_FILTER           0x0000211E
#define GD_HDR_MIXER                        0x0000211F
#define GD_LUMA_SHARPENING_LINEARIZATION    0x00002120
#define GD_LUMA_SHARPENING_FIR_CONFIG       0x00002121
#define GD_LUMA_SHARPENING_LNL              0x00002122
#define GD_LUMA_SHARPENING_TONE             0x00002123
#define GD_MULTI_STREAM_VIDEO_PREVIEW       0x00002124
#define GD_ENA_SECOND_STREAM_ENCODE         0x00002125
#define GD_SET_ALPHA_CHANNEL                0x00002126
#define GD_MODIFY_FRAME_BUFFER              0x00002127
#define GD_SET_ACT_WIN_CENTER               0x00002128
#define GD_SET_WARP_CONTROL                 0x00002129
#define GD_EARLY_WB_GAIN                    0x0000212A
#define GD_LUMA_SHARPENING_EDGE_CONTROL     0x00002130
#define GD_LUMA_SHARPENING_BLEND_CONTROL    0x00002131
#define GD_LUMA_SHARPENING_LEVEL_CONTROL    0x00002132
#define GD_LUMA_SHARPENING_MISC_CONTROL     0x00002133
#define GD_AAA_EARLY_WB_GAIN                0x00002134

// H264/JPEG encoding mode commands
#define GD_VIDEO_PREPROCESSING              0x00003001
#define GD_FAST_AAA_CAPTURE                 0x00003002
#define GD_H264_ENCODE                      0x00003004
#define GD_H264_ENCODE_FROM_MEMORY          0x00003005
#define GD_H264_BITS_FIFO_UPDATE            0x00003006
#define GD_ENCODING_STOP                    0x00003007
#define GD_MODIFY_CMD_DLY                   0x00003008
#define GD_STILL_CAPTURE                    0x00004001
#define GD_JPEG_ENCODE_RESCALE_FROM_MEMORY  0x00004002
#define GD_JPEG_BITS_FIFO_UPDATE            0x00004003
#define GD_FREE_RAW_YUV_PIC_BUFFER          0x00004004
#define GD_JPEG_RAW_YUV_STOP                0x00004005
#define GD_MJPEG_ENCODE                     0x00004006
#define GD_VID_FADE_IN_OUT                  0x00004007
#define GD_MJPEG_ENCODE_WITH_H264           0x00004008
#define GD_OSD_INSERT                       0x00004009
#define GD_YUV422_CAPTURE                   0x00004010
#define GD_SEND_CAVLC_RESULT                0x00004011
#define GD_STILL_CAPTURE_IN_REC             0x00004012      // Z.ZHOU added for still capture during active recording
#define GD_OSD_BLEND                        0x00004013
#define GD_INTERVAL_CAPTURE                 0x00004014
#define GD_STILL_CAPTURE_ADV                0x00004015

/* H264/JPEG decode mode commnads */
#define GD_H264_DECODE                      0x00005002
#define GD_JPEG_DECODE                      0x00005003
#define GD_RAW_PICTURE_DECODE               0x00005004
#define GD_RESCALE_POSTPROCESSING           0x00005005
#define GD_H264_DECODE_BITS_FIFO_UPDATE     0x00005006
#define GD_H264_PLAYBACK_SPEED              0x00005007
#define GD_H264_TRICKPLAY                   0x00005008
#define GD_DECODE_STOP                      0x00005009
#define GD_MULTI_SCENE_DECODE               0x00005010
#define GD_CAPTURE_VIDEO_PICTURE            0x00005011
#define GD_CAPTURE_STILL_PICTURE            0x00005012
#define GD_JPEG_FREEZE                      0x00005013
#define GD_MULTI_SCENE_SETUP                0x00005014
#define GD_MULTI_SCENE_DECODE_ADV           0x00005015
#define GD_JPEG_DECODE_THUMBNAIL_WARP       0x00005016
#define GD_MULTI_SCENE_DECODE_ADV_2         0x00005017
/* IP CAM commands */
#define GD_IPCAM_VIDEO_PREPROCESSING                0x00006001
#define GD_IPCAM_VIDEO_CAPTURE_PREVIEW_SIZE_SETUP   0x00006002
#define GD_IPCAM_VIDEO_ENCODE_SIZE_SETUP            0x00006003
#define GD_IPCAM_REAL_TIME_ENCODE_PARAM_SETUP       0x00006004
#define GD_IPCAM_VIDEO_FORCED_IDR                   0x00006005
#define GD_IPCAM_VIDEO_SYSTEM_SETUP                 0x00006006
#define GD_IPCAM_OSD_INSERT                         0x00006007
#define GD_IPCAM_SET_PRIVACY_MASK                   0x00006008
#define GD_IPCAM_QP_RATIO                           0x00006009

/* VOUT commands */
#define GD_VOUT_MIXER_SETUP                 0x00007001
#define GD_VOUT_VIDEO_SETUP                 0x00007002
#define GD_VOUT_DEFAULT_IMG_SETUP           0x00007003
#define GD_VOUT_OSD_SETUP                   0x00007004
#define GD_VOUT_OSD_BUFFER_SETUP            0x00007005
#define GD_VOUT_OSD_CLUT_SETUP              0x00007006
#define GD_VOUT_DISPLAY_SETUP               0x00007007
#define GD_VOUT_DVE_SETUP                   0x00007008
#define GD_VOUT_RESET                       0x00007009
#define GD_VOUT_DISPLAY_CSC_SETUP           0x0000700A
#define GD_VOUT_DIGITAL_OUTPUT_MODE_SETUP   0x0000700B

/*
 * These GD_* commands are for experimental use only
 */
#define GD_CFA_NOISE_FILTER                 0x0000f001
#define GD_DIGITAL_GAIN_SATURATION          0x0000f002
#define GD_CHROMA_MEDIAN_FILTER             0x0000f003
#define GD_LUMA_DIRECTIONAL_FILTER          0x0000f004
#define GD_LUMA_SHARPEN                     0x0000f005
#define GD_MAIN_RESAMPLER_BANDWIDTH         0x0000f006
#define GD_CFA_RESAMPLER_BANDWIDTH          0x0000f007

#define GD_DSP_DEBUG_0                      0x0000ff00
#define GD_DSP_DEBUG_1                      0x0000ff01
#define GD_AAA_STATISTICS_DEBUG             0x0000ff02
#define GD_DSP_SPECIAL                      0x0000ff03
#define GD_AAA_STATISTICS_DEBUG1            0x0000ff04
#define GD_AAA_STATISTICS_DEBUG2            0x0000ff05
#define GD_BAD_PIXEL_CROP                   0x0000ff06
#define GD_DSP_DEBUG_2                      0x0000ff07
#define GD_DSP_DEBUG_3                      0x0000ff08
#define GD_UPDATE_IDSP_CONFIG               0x0000ff09
#define GD_REAL_TIME_RATE_MODIFY            0x0000ff0a
#define GD_STOP_FATAL_UCODE                 0x0000ffa0


#define GD_CMD_MSG_CMD_ID(cmd_code)                     (((cmd_code)&0xffffff))
// cmd_code: 0x00001002 GD_H264_ENCODING_SETUP
#define GD_H264_ENCODER_SETUP_GET_CHAN_ID(cmd_code)     (((cmd_code)>>24)&0x1f)
#define GD_H264_ENCODER_SETUP_GET_STREAM_ID(cmd_code)   ((cmd_code)>>30)

#define GD_PRIMARY_STREAM       (0)
#define GD_SECONDARY_STREAM     (1)
#define GD_NUM_PIC_TYPES        (3)
// U8 quality;
#define GD_QLEVEL_MASK          (0x1f)
#define GD_LEVEL_MASK           (0xE0)
#define GD_SIMPLE_GOP           (0)
#define GD_P2B2REF_GOP          (1)
#define GD_P2B3REF_GOP          (2)
#define GD_P2B3_ADV_GOP         (3)
#define GD_HI_GOP_DRAM          (4)
#define GD_HI_GOP_SMEM          (5)
#define GD_NON_REF_P_GOP        (6)
#define GD_HI_P_GOP             (7)
// cmd_code: 0x0000100B GD_SYSTEM_SETUP_INFO
#define GD_CAMCORDER_APP_MODE       0
#define GD_IP_CAMCORDER_APP_MODE    2
// cmd_code: 0x0000100D GD_DSP_DEBUG_LEVEL_SETUP
// U8 debug_level;
#define GD_CODING_ORC_THREAD_0_PRINTF_DISABLE   0x1
#define GD_CODING_ORC_THREAD_1_PRINTF_DISABLE   0x2
#define GD_CODING_ORC_THREAD_2_PRINTF_DISABLE   0x4
#define GD_CODING_ORC_THREAD_3_PRINTF_DISABLE   0x8
// cmd_code: 0x0000100E GD_SYSTEM_PARAMETERS_SETUP
// U32 audio_clk_freq;
#define GD_AUDIO_CLK_12_288_MHZ     12288000
// cmd_code: 0x0000100F GD_SYSTEM_IDSP_FREQ_SETUP
// U32 idsp_freq;
#define GD_IDSP_FREQ_144_MHZ        144000000
// cmd_code: 0x00002004 GD_AAA_STATISTICS_SETUP
#define GD_AAA_FILTER_SELECT_BOTH   0
#define GD_AAA_FILTER_SELECT_CFA    1
#define GD_AAA_FILTER_SELECT_YUV    2
// cmd_code: 0x00002009 GD_NOISE_FILTER_SETUP
// U32 strength;
#define GD_BAD_PIXEL_CORRECTION_ENABLE          0x00000001
#define GD_LEAKAGE_FILTER_ENABLE                0x00000002
#define GD_NOISE_FILTER_ENABLE                  0x00000004
#define GD_LOCAL_EXPOSURE_FILTER_ENABLE         0x00000008
#define GD_DEMOSAIC_FILTER_ENABLE               0x00000010
#define GD_JAGGED_FILTER_ENABLE                 0x00000020
#define GD_RGB_DIRECTIONAL_FILTER_ENABLE        0x00000040
#define GD_SPECKLE_FILTER_ENABLE                0x00000080
#define GD_REINTERPOLATE_FILTER_ENABLE          0x00000100
#define GD_LUMA_SHARPENING_FILTER_ENABLE        0x00000200
#define GD_CHROMA_SCALE_FILTER_ENABLE           0x00000400
#define GD_CHROMA_MEDIAN_FILTER_ENABLE          0x00000800
#define GD_BLACK_LEVEL_ENABLE                   0x00001000
#define GD_FPN_ENABLE                           0x00002000
#define GD_COLOR_CORRECTION_ENABLE              0x00004000
#define GD_IMG_3A_ENABLE                        0x00008000
#define GD_AMPLIFIER_LINEARIZATION_ENABLE       0x00010000
// cmd_code: 0x00002100 GD_SET_VIN_CAPTURE_WIN
// GD_S_CTRL_REG
// U16    data_edge   :1;
#define GD_DATA_VAL_RISING_EDGE     0
#define GD_DATA_VAL_FALLING_EDGE    1
// U16    mastSlav_mod:2;
#define GD_MAS_SLAV_MOD_UND         0x0
#define GD_SLAVE_MOD                0x1
#define GD_MAS_MOD                  0x2
#define GD_MAS_SPECIAL              0x3
// U16    emb_sync    :1;
#define GD_EMB_SYNC_IN_DATA         0x1
// U16    emb_sync_mode:1;
#define GD_EMB_SYNC_656             0x0
#define GD_ALL_ZERO_IN_BLANK        0x1
// U16    emb_sync_loc:2;
#define GD_EMB_SYNC_IN_LOW_PIX      0x0
#define GD_EMB_SYNC_IN_UP_PIX       0x1
#define GD_EMB_SYNC_IN_BOTH         0x2
// U16    vs_pol      :1;
#define GD_VSYNC_POL_ACT_H          0x0
#define GD_VSYNC_POL_ACT_L          0x1
// U16    hs_pol      :1;
#define GD_HSYNC_POL_ACT_H          0x0
#define GD_HSYNC_POL_ACT_L          0x1
// U16    sony_fld_mod:1;
#define GD_FLD_MOD_NORMAL           0
#define GD_FLD_MOD_SONY             1
// GD_S_INPUT_CONFIG_REG
// U16    pad_type
#define GD_LVCMOS           0x0
#define GD_LVDS             0x1
// U16    data_rate
#define GD_SDR              0x0
#define GD_DDR              0x1
// U16 :1;
#define GD_ONE_PIX_WIDE     0
#define GD_TWO_PIX_WIDE     1
// U16    inp_src
#define GD_LVDS_SRC         0x0
#define GD_GPIO_SRC         0x1
// U16    inp_src_ty
#define GD_RGB_IN           0x0
#define GD_YUV_IN           0x1
// U16    yuv_inp_ord
#define GD_CrYCbY_1PIX      0x0
#define GD_CbYCrY_1PIX      0x1
#define GD_YCrYCb_1PIX      0x2
#define GD_YCbYCr_1PIX      0x3
#define GD_YCrYCb_2PIX      0x0
#define GD_YCbYCr_2PIX      0x1
#define GD_CrYCbY_2PIX      0x2
#define GD_CbYCrY_2PIX      0x3
// cmd_code: 0x00002119 GD_VIDEO_PREVIEW_SETUP
// U32 cmd_code;
#define GD_PREVIEW_ID_A     0
#define GD_PREVIEW_ID_B     1
// cmd_code: 0x00002129 GD_SET_WARP_CONTROL
// U32 warp_control;
#define GD_WARP_CONTROL_DISABLE 0
#define GD_WARP_CONTROL_ENABLE  1
// cmd_code: 0x00003001 GD_VIDEO_PREPROCESSING
#define GD_RGB_RAW          0
#define GD_YUV_422_INTLC    1
#define GD_YUV_422_PROG     2
// U8 preview_format_A : 4;
// U8 preview_format_B : 3;
#define GD_PREVIEW_FORMAT_PROGRESS                  0
#define GD_PREVIEW_FORMAT_INTERLACE                 1
#define GD_PREVIEW_FORMAT_DEFAULT_IMAGE_PROGRESS    2
#define GD_PREVIEW_FORMAT_DEFAULT_IMAGE_INTERLACE   3
#define GD_PREVIEW_FORMAT_PROGRESS_TOP_FIELD        4
#define GD_PREVIEW_FORMAT_PROGRESS_BOT_FIELD        5
#define GD_PREVIEW_FORMAT_NO_OUTPUT                 6
// cmd_code: 0x00003007 GD_ENCODING_STOP
// U32 stop_method;
#define GD_H264_STOP_IMMEDIATELY        0
#define GD_H264_STOP_ON_NEXT_IP         1
#define GD_H264_STOP_ON_NEXT_I          2
#define GD_H264_STOP_ON_NEXT_IDR        3
#define GD_EMERG_STOP                   0xff
// cmd_code: 0x00004001 GD_STILL_CAPTURE
#define GD_JPEG_OUTPUT_SELECT_MAIN_JPEG_BITS    0x1
#define GD_JPEG_OUTPUT_SELECT_THUMB_JPEG_BITS   0x4
#define GD_JPEG_OUTPUT_SELECT_MAIN_YUV          0x8
#define GD_JPEG_OUTPUT_SELECT_PREVIEW_YUV       0x10
// U8 still_process_mode;
#define GD_STILL_PROCESS_MODE_NORMAL            0
#define GD_STILL_PROCESS_MODE_HIGH_ISO          1
#define GD_STILL_PROCESS_MODE_LOW_ISO           2
// U8 yuv_proc_mode;
#define GD_YUV_START_NO_CNTRL                   (0)
#define GD_YUV_START_EXP_MODE                   (1)
#define GD_YUV_START_SLW_MODE                   (2)
#define GD_YUV_START_SLW_STATS_MODE             (3)
// cmd_code: 0x00004014 GD_INTERVAL_CAPTURE
// U32 action;
#define GD_CAP_IDLE         (0)
#define GD_CAP_INITIATE     (1)
#define GD_CAP_CAPTURE      (2)
#define GD_CAP_TERMINATE    (3)
// cmd_code: 0x00006008 GD_IPCAM_SET_PRIVACY_MASK
// U8 Y;
// U8 U;
// U8 V;
// use privacy mask to label a region to let MCTF to pass through it
#define GD_PRIVACY_MASK_OFF                     0
#define GD_PRIVACY_MASK_ON                      1
#define GD_PRIVACY_MASK_LABEL_MCTF_PASS_THROUGH 2

// Adding Macros defined in the interface between ARM and VDSP
//following three configuration is predefined inside the coding module.
//and shared between the ARM and DSP.
//Used to describe the layout of the Coding CTX information in the DRAM sent from
//ARM to DSP.
#define GD_CTX_WIDTH                (416)
#define GD_I_CTX_SZ                 (52*GD_CTX_WIDTH)
#define GD_FLD_CTX_OFS              (104*GD_CTX_WIDTH)
#define GD_CABAC_CTX_MEM_SIZE       (GD_CTX_WIDTH*(104*2))

#define GD_JPG_LU_HUFF_DRAM_SIZE    (256)
#define GD_PG_CH_HUFF_DRAM_SIZE     (256)
#define GD_MCTF_CFG_SZ              (22528)

//*****************************************************************************
//*****************************************************************************
//** Enumerated types
//*****************************************************************************
//*****************************************************************************
typedef enum
{
    GD_IDSP_CMD_SEC1_VIN = GD_IDSP_SECTION_FILTER(1, 0),
    GD_IDSP_CMD_SEC1_AML = GD_IDSP_SECTION_FILTER(1, 1),
    GD_IDSP_CMD_SEC1_RLC = GD_IDSP_SECTION_FILTER(1, 2),
    GD_IDSP_CMD_SEC1_SMM = GD_IDSP_SECTION_FILTER(1,14),
    GD_IDSP_CMD_SEC1_SMT = GD_IDSP_SECTION_FILTER(1,15),
    GD_IDSP_CMD_SEC2_BFN = GD_IDSP_SECTION_FILTER(2, 0),
    GD_IDSP_CMD_SEC2_BPC = GD_IDSP_SECTION_FILTER(2, 1),
    GD_IDSP_CMD_SEC2_PSC = GD_IDSP_SECTION_FILTER(2, 2),
    GD_IDSP_CMD_SEC2_AAC = GD_IDSP_SECTION_FILTER(2, 3),
    GD_IDSP_CMD_SEC2_DGN = GD_IDSP_SECTION_FILTER(2, 4),
    GD_IDSP_CMD_SEC2_LEA = GD_IDSP_SECTION_FILTER(2, 5),
    GD_IDSP_CMD_SEC2_DMS = GD_IDSP_SECTION_FILTER(2, 6),
    GD_IDSP_CMD_SEC2_CLC = GD_IDSP_SECTION_FILTER(2, 7),
    GD_IDSP_CMD_SEC2_AAA = GD_IDSP_SECTION_FILTER(2, 8),
    GD_IDSP_CMD_SEC2_RYC = GD_IDSP_SECTION_FILTER(2, 9),
    GD_IDSP_CMD_SEC2_LSH = GD_IDSP_SECTION_FILTER(2,10),
    GD_IDSP_CMD_SEC2_CMN = GD_IDSP_SECTION_FILTER(2,11),
    GD_IDSP_CMD_SEC2_CDS = GD_IDSP_SECTION_FILTER(2,12),
    GD_IDSP_CMD_SEC2_LRS = GD_IDSP_SECTION_FILTER(2,13),
    GD_IDSP_CMD_SEC2_CRS = GD_IDSP_SECTION_FILTER(2,14),
    GD_IDSP_CMD_SEC2_MRS = GD_IDSP_SECTION_FILTER(2,15),
    GD_IDSP_CMD_SEC3_VWP = GD_IDSP_SECTION_FILTER(3, 0),
    GD_IDSP_CMD_SEC4_MVU = GD_IDSP_SECTION_FILTER(4, 0),
    GD_IDSP_CMD_SEC5_LPA = GD_IDSP_SECTION_FILTER(5, 0),
    GD_IDSP_CMD_SEC5_CPA = GD_IDSP_SECTION_FILTER(5, 1),
    GD_IDSP_CMD_SEC5_LDA = GD_IDSP_SECTION_FILTER(5, 2),
    GD_IDSP_CMD_SEC5_CDA = GD_IDSP_SECTION_FILTER(5, 3),
    GD_IDSP_CMD_SEC6_LPB = GD_IDSP_SECTION_FILTER(6, 0),
    GD_IDSP_CMD_SEC6_CPB = GD_IDSP_SECTION_FILTER(6, 1),
    GD_IDSP_CMD_SEC7_LPC = GD_IDSP_SECTION_FILTER(7, 0),
    GD_IDSP_CMD_SEC7_CPC = GD_IDSP_SECTION_FILTER(7, 1),
    GD_IDSP_CMD_SEC7_LDC = GD_IDSP_SECTION_FILTER(7, 2),
    GD_IDSP_CMD_SEC7_CDC = GD_IDSP_SECTION_FILTER(7, 3),
    GD_IDSP_CMD_SEC7_MRC = GD_IDSP_SECTION_FILTER(7, 4),
}GD_IDSP_SECTION_FILTER_E;

typedef enum
{
    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT,
    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT,
    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT,
    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT,
}GD_IDSP_CMD_DATA_UNIT_E;

typedef enum
{
    GD_IDSP_CMD_FILTER_UNKNOW,
    GD_IDSP_CMD_FILTER_VIDEO_IN,
}GD_IDSP_CMD_FILTER_E;

typedef enum
{
    GD_IDSP_CMD_REG_FILTER_DEF_OFFSET,
    GD_IDSP_CMD_REG_FILTER_DEF_START_BIT,
    GD_IDSP_CMD_REG_FILTER_DEF_NUM_BITS,
    GD_IDSP_CMD_REG_FILTER_DEF_NUM_REGISTERS,
    GD_IDSP_CMD_REG_FILTER_DEF_DATA_UNIT,
    GD_IDSP_CMD_REG_FILTER_DEF_FILTER,
}GD_IDSP_CMD_REG_FILTER_DEF_E;

typedef enum
{
    GD_JPEG_THUMB,
    GD_H264_I_ONLY,
    GD_RAW_PIC,
    GD_YUV_PIC,
    GD_JPEG_MAIN,
} GD_DSP_CMD_SCENE_TYPE_E;

typedef enum
{
    GD_NORMAL,
    GD_FLIPPING_BLOCK,
    GD_FLIPPING_PAGE,
    GD_ALBUM_MIRROR,
} GD_DSP_CMD_EFFECT_TYPE_E;

typedef enum
{
    GD_SMALL_SIZE,
    GD_LARGE_SIZE,
} GD_DSP_CMD_THUMBNAIL_TYPE_E;

typedef enum
{
    GD_VOUT_ID_A           = 0,
    GD_VOUT_ID_B           = 1,
} GD_DSP_CMD_VOUT_ID_E;

typedef enum
{
    GD_VOUT_SRC_DEFAULT_IMG = 0,
    GD_VOUT_SRC_BACKGROUND  = 1,
    GD_VOUT_SRC_ENC         = 2,
    GD_VOUT_SRC_DEC         = 3,
    GD_VOUT_SRC_H264_DEC    = 3,
    GD_VOUT_SRC_MPEG2_DEC   = 5,
    GD_VOUT_SRC_MPEG4_DEC   = 6,
    GD_VOUT_SRC_MIXER_A     = 7,
    GD_VOUT_SRC_VCAP        = 8,
} GD_DSP_CMD_VOUT_SRC_E;

typedef enum
{
    GD_VOUT_DATA_SRC_NORMAL = 0,
    GD_VOUT_DATA_SRC_DRAM   = 1,
} GD_DSP_CMD_VOUT_DATA_SRC_E;

typedef enum
{
    GD_OSD_SRC_MAPPED_IN    = 0,
    GD_OSD_SRC_DIRECT_IN    = 1,
} GD_DSP_CMD_OSD_SRC_E;

typedef enum
{
    GD_OSD_MODE_UYV565    = 0,
    GD_OSD_MODE_AYUV4444  = 1,
    GD_OSD_MODE_AYUV1555  = 2,
    GD_OSD_MODE_YUV1555   = 3,
} GD_DSP_CMD_OSD_DIR_MODE_E;

typedef enum
{
    GD_CSC_DIGITAL      = 0,
    GD_CSC_ANALOG       = 1,
    GD_CSC_HDMI         = 2,
} GD_DSP_CMD_CSC_TYPE_E;

/* return value for chip_id_ptr in GD_DSP_INIT_DATA_S */
typedef enum
{
    GD_CHIP_ID_UNKNOWN = -1,
    GD_CHIP_ID_33 = 0,
    GD_CHIP_ID_55 = 1,
    GD_CHIP_ID_66 = 2,
    GD_CHIP_ID_70 = 3,
    GD_CHIP_ID_88 = 4,
    GD_CHIP_ID_99 = 5,
} GD_CHIP_ID_S;

typedef enum
{
    GD_AUDIO_SF_reserved = 0,
    GD_AUDIO_SF_96000,
    GD_AUDIO_SF_48000,
    GD_AUDIO_SF_44100,
    GD_AUDIO_SF_32000,
    GD_AUDIO_SF_24000,
    GD_AUDIO_SF_22050,
    GD_AUDIO_SF_16000,
    GD_AUDIO_SF_12000,
    GD_AUDIO_SF_11025,
    GD_AUDIO_SF_8000,
} GD_AUDIO_IN_FREQ_E;

//*****************************************************************************
//*****************************************************************************
//** Data Structures
//*****************************************************************************
//*****************************************************************************
typedef    struct
{
    U64        cmd[4];
}GD_IDSP_CMD_SECTION_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;

    U64     config_en               :   8;
    U64     res0_2                  :  31;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     res1_1                       ;

    // Dword #2
    U64     out_en                  :   3;
    U64     res2_1                  :   5;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     out_vin_sync_en         :   1;
    U64     out_vin_sync_cnt        :   6;
    U64     res2_2                  :  25;

    // Dword #3
    U64     out_sreg_1              :   8;
    U64     out_pri_1               :   2;
    U64     out_sreg_2              :   8;
    U64     out_pri_2               :   2;
    U64     reserved3_1             :  44;
}GD_IDSP_CMD_SEC_1_S;

typedef struct {
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     config_en               :   8;
    U64     filter_bypass_en        :   8;
    U64     preview_mode            :   4;
    U64     res0_2                  :  19;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   1;
    U64     low_noise_luma          :   1;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_main_sreg            :   8;
    U64     in_main_pri             :   2;
    U64     in_chroma_sreg          :   8;
    U64     in_chroma_pri           :   2;
    U64     in_blk_sreg             :   8;
    U64     in_blk_pri              :   2;
    U64     in_sharpening_sreg      :   8;
    U64     in_sharpening_pri       :   2;
    U64     res1_2                  :   8;

    // Dword #2
    U64     out_en                  :   8;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     out_sec_sync_en         :   1;
    U64     out_sec_sync_cnt        :   6;
    U64     res2_1                  :   1;
    U64     out_3rd_sync_en         :   1;
    U64     out_3rd_sync_cnt        :   6;
    U64     res2_3                  :  16;
    U64     out_ext_src             :   1;

    // Dword #3
    U64     out_main_luma_sreg      :   8;
    U64     out_main_luma_pri       :   2;
    U64     out_main_chroma_sreg    :   8;
    U64     out_main_chroma_pri     :   2;
    U64     out_me_sreg             :   8;
    U64     out_me_pri              :   2;
    U64     out_aaa_cfa_sreg        :   8;
    U64     out_aaa_cfa_pri         :   2;
    U64     out_aaa_rgb_sreg        :   8;
    U64     out_aaa_rgb_pri         :   2;
    U64     out_ext_raw_sreg        :   8;
    U64     out_ext_raw_pri         :   2;
    U64     reserved3_1             :   4;
}GD_IDSP_CMD_SEC_2_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     config_en               :   8;
    U64     res0_2                  :  30;
    U64     lastFrame               :   1;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   2;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_sreg_1               :   8;
    U64     in_pri_1                :   2;
    U64     in_sreg_2               :   8;
    U64     in_pri_2                :   2;
    U64     res1_2                  :  28;

    // Dword #2
    U64     out_en                  :   1;
    U64     res2_1                  :   7;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     res2_2                  :  16;
    U64     out_mode420             :   1;
    U64     res2_3                  :  15;

    // Dword #3
    U64     out_smem_reg_1          :   8;
    U64     out_pri_1               :   2;
    U64     out_smem_reg_2          :   8;
    U64     out_pri_2               :   2;
    U64     reserved3_1             :  44;
}GD_IDSP_CMD_SEC_3_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     res0_2                  :  39;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   2;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_sreg_1               :   8;
    U64     in_pri_1                :   2;
    U64     res1_2                  :  38;

    // Dword #2
    U64     out_en                  :   1;
    U64     res2_1                  :   7;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     res2_2                  :  32;

    // Dword #3
    U64     out_smem_reg_1          :   8;
    U64     out_pri_1               :   2;
    U64     reserved3_1             :  54;
}GD_IDSP_CMD_SEC_4_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     res0_2                  :  39;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   2;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_sreg_1               :   8;
    U64     in_pri_1                :   2;
    U64     in_sreg_2               :   8;
    U64     in_pri_2                :   2;
    U64     res1_2                  :  28;

    // Dword #2
    U64     out_en                  :   1;
    U64     res2_1                  :   7;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     res2_2                  :  32;

    // Dword #3
    U64     out_smem_reg_1          :   8;
    U64     out_pri_1               :   2;
    U64     out_smem_reg_2          :   8;
    U64     out_pri_2               :   2;
    U64     reserved3_1             :  44;
}GD_IDSP_CMD_SEC_5_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     res0_2                  :  39;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   2;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_sreg_1               :   8;
    U64     in_pri_1                :   2;
    U64     in_sreg_2               :   8;
    U64     in_pri_2                :   2;
    U64     res1_2                  :  28;

    // Dword #2
    U64     out_en                  :   1;
    U64     res2_1                  :   7;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     res2_2                  :  32;

    // Dword #3
    U64     out_smem_reg_1          :   8;
    U64     out_pri_1               :   2;
    U64     out_smem_reg_2          :   8;
    U64     out_pri_2               :   2;
    U64     reserved3_1             :  44;
}GD_IDSP_CMD_SEC_6_S;

typedef struct
{
    // Dword #0
    U64     config_chan             :   8;
    U64     res0_1                  :  14;
    U64     config_pri              :   2;
    U64     res0_2                  :  39;
    U64     keep_prev_cfg           :   1;

    // Dword #1
    U64     in_src                  :   2;
    U64     res1_1                  :   2;
    U64     in_Sync_type            :   2;
    U64     in_sync_dec             :   1;
    U64     in_line_sync_cnt_log2   :   3;
    U64     in_sync_cnt_nbr         :   6;
    U64     in_sreg_1               :   8;
    U64     in_pri_1                :   2;
    U64     in_sreg_2               :   8;
    U64     in_pri_2                :   2;
    U64     res1_2                  :  28;

    // Dword #2
    U64     out_en                  :   2;
    U64     res2_1                  :   6;
    U64     out_line_sync_type      :   2;
    U64     out_line_sync_cnt_log2  :   3;
    U64     out_line_sync_cnt       :   6;
    U64     out_str_credits         :   6;
    U64     out_frm_sync_en         :   1;
    U64     out_frm_sync_cnt        :   6;
    U64     res2_2                  :  32;

    // Dword #3
    U64     out_smem_reg_1          :   8;
    U64     out_pri_1               :   2;
    U64     out_smem_reg_2          :   8;
    U64     out_pri_2               :   2;
    U64     out_smem_reg_3          :   8;
    U64     out_pri_3               :   2;
    U64     reserved3_1             :  34;
}GD_IDSP_CMD_SEC_7_S;

typedef union
{
    GD_IDSP_CMD_SECTION_S   sec;
    GD_IDSP_CMD_SEC_1_S     sec1;
    GD_IDSP_CMD_SEC_2_S     sec2;
    GD_IDSP_CMD_SEC_3_S     sec3;
    GD_IDSP_CMD_SEC_4_S     sec4;
    GD_IDSP_CMD_SEC_5_S     sec5;
    GD_IDSP_CMD_SEC_6_S     sec6;
    GD_IDSP_CMD_SEC_7_S     sec7;
}GD_IDSP_SEC_CMD_T;

typedef struct
{
    char                    name[100];
    U32                     dwOffset;           // 2bytes (xx*xx)
    U32                     dwStartBit;         // 2
    U32                     dwBits;             // 2
    U32                     dwRegister;         // xxxx
    GD_IDSP_CMD_DATA_UNIT_E eDataType;          //
    GD_IDSP_CMD_FILTER_E    eFilterType;        //
}GD_IDSP_CMD_REG_FILTER_DATA_S;

typedef struct
{
    GD_IDSP_CMD_REG_FILTER_DEF_E    eDefType;
    char                            name[100];
}GD_IDSP_CMD_REG_FILTER_DEF_S;

typedef struct
{
    char                            section[10];
    char                            filter[10];
    U32                             offset;
    U32                             reg_data_size;
    GD_IDSP_CMD_REG_FILTER_DATA_S*  reg_data;
}GD_IDSP_CMD_SEC_REG_FILTER_S;

typedef struct
{
    U32     Addr;
    U32     data;
}GD_IDSP_CMD_SEC_REG_SET_DATA_S;

typedef struct
{
    char                            section[10];
    char                            filter[10];
    GD_IDSP_SECTION_FILTER_E        control;
    U32                             reg_data_size;
    GD_IDSP_CMD_SEC_REG_SET_DATA_S* reg_data;
}GD_IDSP_CMD_SEC_REG_FILTER_DATS_S;

typedef struct
{
    // reg 0x00: 0x00
    U32 S_Control_reset                 :  1;   // 0: no op  1: reset video in
    U32 S_Control_enable                :  1;   // 0: idle   1: enable video in
    U32 S_Control_win_en                :  1;   // enable capture window. automatic reset at the end of each capture
    U32 S_Control_data_edge             :  1;   // Data clock edge. 0: valid on rising edge of sensor clock
                                                //                  1: valid on falling edge of sensor clock
    U32 S_Control_data_slave            :  1;   // slave mode enable: 0: disabled / 1: enabled
    U32 S_Control_data_master           :  1;   // master mode enable: 0: disabled / 1: enabled
                                                // Bit [5:4] forms the following combination:
                                                // 2b00: undefined
                                                // 2b01: slave mode
                                                // 2b10: master mode
                                                // 2b11: undefined
    U32 S_Control_data_emb_sync         :  1;   // sync code embedded in data. When set in master mode,
                                                // this indicates sensors have embedded sync code while
                                                // receiving seperate sync signals (Sony specific).
    U32 S_Control_data_emb_sync_mode    :  1;   // Embedded sync mode. 0: ITU-656 style(8-bit) 1: ITU-656 style(full data range)
    U32 S_Control_data_emb_sync_loc     :  2;   // Embedded sync code location (2-pixel wide input only).
                                                // 2b00: embedded sync code carried on the lower pixel
                                                // 2b01: embedded sync code carried on the upper pixel
                                                // 2b1x: embedded sync code carried on both pixels [should programed to 2b1x for serial sensor interface modes]
    U32 S_Control_data_vs_pol           :  1;   // vsync polarity. 0: active high (rising edge signals start)  1: active low (falling edge signals start)
    U32 S_Control_data_hs_pol           :  1;   // hsync polarity. 0: active high (rising edge signals start)  1: active low (falling edge signals start)
    U32 S_Control_data_field0_pol       :  1;   // 0: field 0 has ID set to 0 with wen assertion   1:field 0 has ID set to 1 with wen assertion
    U32 S_Control_data_sony_field_mode  :  1;   // 0: normal field mode   1: Sony-specific field mode. The first field of a multi-field readout in Sony CCD/TG is indicated by the state of EXP/ID pin at the first assertion of WEN/FLD
    U32 S_Control_data_ecc_enable       :  1;   // 656 error correction enable {including the sync code words in serial sensor mode]
    U32 S_Control_data_hsync_mask       :  1;   // 0: Toggle hsync during vertical blanking    1: No hsync toggle during vertical blanking
    U32                                 : 16;   // reserved

    // reg 0x01: 0x04
    // input mode[4:0]
    U32 S_InputConfig_pad_type          :  1;   // 0: LVCMOS  1: LVDS
    U32 S_InputConfig_data_rate         :  1;   // 0: SDR    1: DDR
    U32 S_InputConfig_data_width        :  1;   // 0: 1-pixel wide  1: 2-pixel wide [should be programed to 1 (2-pixel wide) for serial sensor interface modes]
    U32 S_InputConfig_input_source      :  1;   // 0: from LVDS (lvds_idsp_sdata)     1: from GPIO (iopad_idsp_sdata). Input source and pad type forms three combinations:-LVDS source, LVDS pad.-LVDS source, LVCMOS pad.-GPIO source. (Pad type makes no difference.)
    U32 S_InputConfig_RGB_YUV           :  1;   // 0: RGB input    1: YUV input
                                                // The following are legal combinations for input mode (x: 0 or 1, -: no effect):
                                                // x000x:SDR,1-pixel wide RGB/YUV data, from lvds_idsp_sdata[13:0]
                                                // x001x:DDR,1-pixel wide RGB/YUV data, from lvds_idsp_sdata[27:0]
                                                // x0100:SDR,2-pixel wide RGB/YUV data, from lvds_idsp_sdata[27:0]
                                                // x0110:DDR,2-pixel wide RGB/YUV data, from lvds_idsp_sdata[55:0]
                                                // 110--:1-pixel wide YUV data, from iopad_idsp_sdata[7:0]
                                                // 111--:2-pixel wide YUV data, from iopad_idsp_sdata[15:0]
    U32 S_InputConfig_Source_pixel_data_width   :  2;   // Source pixel data width. VIN aligns all pixel values to MSB at output.
                                                // For example, 8-bit source means left shift by 6, 14-bit source means no shift,
                                                // etc. YUV data coming from GPIO must be 8-bit wide. (Hardware ignores the configuration.)
                                                // 2b00: 8-bit  2b01: 10-bit    2b10: 12-bit    2b11: 14-bit
    U32 S_InputConfig_YUV_input_order   :  2;   // YUV input order
                                                // For 1-pixel wide YUV data
                                                // 00:Cr,Y0,Cb,Y1,
                                                // 01:Cb,Y0,Cr,Y1,
                                                // 10:Y0,Cr,Y1,Cb,
                                                // 11:Y0,Cb,Y1,Cr,
                                                // For 2-pixel wide YUV data
                                                // 00:{Cr,Y},{Cb,Y},
                                                // 01:{Cb,Y},{Cr,Y},
                                                // 10:{Y,Cr},{Y,Cb},
                                                // 11: {Y, Cb}, {Y, Cr},
    U32 S_InputConfig_Number_of_active_SLVS_lanes   :  2;   // Number of active SLVS lanes
                                                // 2b00: 4 lanes; 2b01: 8 lanes; 2b10: 12 lanes; 2b11: 16 lanes)
    U32 S_InputConfig_Serial_sensor_interface_mode  :  1;   // Serial sensor interface mode (Micron and Sony)
    U32 S_InputConfig_Sony_serial_sensor_interface_mode :  1;   // Sony serial sensor interface mode
    U32 S_InputConfig_VIN_clock_select  :  1;   // VIN clock select - use sensor or bit clock instead of IDSP clock
    U32                                 :  2;   // reserved
    U32                                 : 16;   // reserved

    // reg 0x02: 0x08
    // Status register: Write logic 1 to the status register clears the corresponding bit.
    U32 S_Status_vsync              :  1;   // begin of frame detected
    U32 S_Status_trig0              :  1;   // trigger 0 status. 0: no trigger/ 1: triggered
    U32 S_Status_trig1              :  1;   // trigger 1 status. 0: no trigger/ 1: triggered
    U32 S_Status_ovfl               :  1;   // synchronous FIFO overflow. 0: no overflow/ 1: overflow occurred
    U32 S_Status_shortl             :  1;   // early hsync detected
    U32 S_Status_shortf             :  1;   // early vsync detected
    U32 S_Status_field              :  3;   // current video field (read only).
    U32 S_Status_no_hsync           :  1;   // no hsync detected (time out)
    U32 S_Status_no_vsync           :  1;   // no vsync detected (time out)
    U32 S_Status_idsp_ahb_vsync     :  1;   // frame end signal to ARM
    U32 S_Status_idsp_ahb_mst_vsync :  1;   // master mode frame end signal to ARM
    U32 S_Status_idsp_ahb_last_pxl  :  1;   // capture window end signal to ARM
    U32 S_Status_ecc_uncorrectable  :  1;   // uncorrectable 656 errors
    U32 S_Status_program_error      :  1;   // illegal programming detected. Currently the reported error includes:Master mode, active region exceeds frame region
    U32                             : 16;   // reserved

    // reg 0x03: 0x0C
    // Vertical active region width (master mode only)
    U32 S_Vwidth                    : 14;   // vsync pulse width in unit of lines
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x04: 0x10
    // Horizontal active region width (master mode only).
    U32 S_Hwidth                    : 14;   // hsync pulse width in unit of pixels
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x05: 0x14
    U32 S_Hoffset_top               : 14;   //
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x06: 0x18
    U32 S_Hoffset_bot               : 14;   //
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x07: 0x1C
    // Frame size, vertical (master mode only)
    U32 S_V                         : 14;   // Number of lines per field
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x08: 0x20
    // Frame size, horizontal (in master mode only)
    U32 S_H                         : 14;   // Number of pixels per line
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x09: 0x24
    // Minimum frame size, vertical (slave mode only)
    U32 S_MinV                      : 14;   // number of lines per field
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x0A: 0x28
    // Minimum frame size, horizontal (slave mode only)
    U32 S_MinH                      : 14;   // number of pixels per line
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x0B: 0x2C
    // Trigger 0 control
    U32 S_Trigger0Start_startline   : 14;   // startline. Assert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = startline (counting from 1st line active region)
    U32 S_Trigger0Start_pol         :  1;   // polarity. 0: active low trigger/ 1: active high trigger
    U32 S_Trigger0Start_enable      :  1;   // 0: trigger disabled/ 1: trigger enabled
    U32                             : 16;   // reserved

    // reg 0x0C: 0x30
    // Trigger 0 control
    U32 S_Trigger0End_startline     : 14;   // lastline. Deassert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = lastline (counting from 1st line active region)
    U32                             :  2;   // reserved
                                            U32                             : 16;   // reserved
    // reg 0x0D: 0x34
    // Trigger 1 control
    U32 S_Trigger1Start_startline   : 14;   // startline. Assert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = startline (counting from 1st line active region)
    U32 S_Trigger1Start_pol         :  1;   // polarity. 0: active low trigger/ 1: active high trigger
    U32 S_Trigger1Start_enable      :  1;   // 0: trigger disabled/ 1: trigger enabled
    U32                             : 16;   // reserved

    // reg 0x0E: 0x38
    // Trigger 1 control
    U32 S_Trigger1End_startline     : 14;   // lastline. Deassert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = lastline (counting from 1st line active region)
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x0F: 0x3C
    // VOUT synchronization control
    U32 S_VoutStart0_startline      : 14;   // startline. Synchronization signal is asserted for the duration of the n-th line,
                                            // where n = startline (counting from 1st line active region)
    U32                             :  1;   // reserved
    U32 S_VoutStart0_disable_field_check    :  1;   // 0: synchronization signal is set on even field/ 1: synchronization signal is set on each field
    U32                             : 16;   // reserved

    // reg 0x10: 0x40
    // VOUT synchronization control
    U32 S_VoutStart1_startline      : 14;   // startline. Synchronization signal is asserted for the duration of the n-th line,
                                            // where n = startline (counting from 1st line active region)
    U32                             :  1;   // reserved
    U32 S_VoutStart1_disable_field_check    :  1;   // 0: synchronization signal is set on even field/ 1: synchronization signal is set on each field
    U32                             : 16;   // reserved

    // reg 0x11: 0x44
    // Capture window control, vertical start
    U32 S_CapStartV                 : 14;   // Start vertical location of capture window
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x12: 0x48
    // Capture window control, horizontal start
    U32 S_CapStartH                 : 14;   // Start horizontal location of capture window
                                            // In 8 channel , Sony serial sensor mode, the capture window should start 4
                                            // pixels after the SAV (i.e. exclude the 4 pixels added by the receiver at the
                                            // beginning of every line which are not part of the original active line)
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x13: 0x4C
    // Capture window control, vertical end
    U32 S_CapEndV                   : 14;   // End vertical location of capture window
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x14: 0x50
    // Capture window control, horizontal end
    U32 S_CapEndH                   : 14;   // End horizontal location of capture window
                                            // In 8 channel, Sony serial sensor mode, the capture window should end 4 pixels
                                            // before the EAV sync code to exclude the additional sync code pixels.
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x15: 0x54
    // All-zero embedded sync horizontal blank interval length
    U32 S_BlankLengthH              : 14;   // Blank interval length in sensor clock cycles
    U32                             :  2;   // reserved
    U32                             : 16;   // reserved

    // reg 0x16: 0x58
    // Vsync timeout limit (lower 16 bits) and also EAV column for SLVS mode.
    U32 S_TimeoutVLow               : 16;   // SLVS mode programing notes:Should be integer multiple of 4 and does not count SAV/EAV sync code pixels
    U32                             : 16;   // reserved

    // reg 0x17: 0x5C
    // Vsync timeout limit (upper 16 bits)
    U32 S_TimeoutVHigh              : 16;   //
    U32                             : 16;   // reserved

    // reg 0x18: 0x60
    // Hsync timeout limit (lower 16 bits) and also Horizontal line length (SAV-to-SAV distance) in SLVS mode.
    U32 S_TimeoutHLow               : 16;   // SLVS mode programing notes:Should be integer multiple of 4 and does not count SAV/EAV sync code pixels
    U32                             : 16;   // reserved

    // reg 0x19: 0x64
    // Hsync timeout limit (lower 16 bits)
    U32 S_TimeoutHHigh              : 16;   //
    U32                             : 16;   // reserved

    // reg 0x1A: 0x68
    U32 S_mipi_cfg1                 : 16;   // Add
    U32                             : 16;   // reserved

    // reg 0x1B: 0x6C
    U32 S_mipi_cfg2                 : 16;   // Add
    U32                             : 16;   // reserved

    // reg 0x1C: 0x70
    U32 S_mipi_bdphyctl             : 16;   // Add
    U32                             : 16;   // reserved

    // reg 0x1D: 0x74
    U32 S_mipi_sdphyctl             : 16;   // Add
    U32                             : 16;   // reserved

    // reg 0x1E: 0x78
    U32 s_reserved0;
    // reg 0x1F: 0x7C
    U32 s_reserved1;

    // reg 0x20: 0x80 RO
    U32 S_debugFifoCount            : 16;   // Synchronous FIFO word count (debug only), number of words in synchronous FIFO
    U32                             : 16;   // reserved

    // reg 0x21: 0x84 RO
    U32 S_debugFifoData0            : 16;   // Synchronous FIFO read data (debug only), Pixel 0 read data
    U32                             : 16;   // reserved

    // reg 0x22: 0x88 RO
    U32 S_debugFifoData1            : 16;   // Synchronous FIFO read data (debug only), Pixel 1 read data
    U32                             : 16;   // reserved

    // reg 0x23: 0x8C RO
    U32 S_debugStall                : 16;   // Stall (debug only), Output interface stall
    U32                             : 16;   // reserved

    // reg 0x24: 0x90 RO SLSV status (debug only), Output interface stall
    U32 S_slvStatus_SLSV            :  1;   // receiver reached LOCK state
    U32 S_slvStatus_sync            :  1;   // Detected sync code match on all 4 words.
    U32 S_slvStatus_Start_Of_Frame  :  1;   // Detected Start-Of-Frame
    U32 S_slvStatus_VSYNC           :  1;   // Detected VSYNC
    U32 S_slvStatus_Start_of_line   :  1;   // Detected Start-of-line
    U32 S_slvStatus_valid_pixel     :  1;   // Generated valid pixel output
    U32 S_slvStatus_End_of_line     :  1;   // Generated an End-of-line output
    U32 S_slvStatus_Corrected_error :  1;   // Corrected error in sync code
    U32                             :  8;   // reserved
    U32                             : 16;   // reserved
    // U32 s_reserved0[16];           // reg 0x1A-0x29
    // U32 s_rsc_vertical_enable: 1;  // reg 0x2A
    // U32 s_rsc_horizontal_enable:1;
    // U32 s_rsc_arm_int_enable:1;
    // U32 s_rsc_reg_config_mask:1;
    // U32 s_rsc_use_software_sample: 1;
    // U32 s_reserved1:11;
    // U32 s_rsc_correction_int_delay;// reg 0x2B
    // U32 s_rsc_hor_software_gyro_sample; // reg 0x2C
    // U32 s_rsc_hor_offset;          // reg 0x2D
    // U32 s_rsc_hor_scale;           // reg 0x2E
    // U32 s_rsc_vert_software_gyro_sample; // reg 0x2F
    // U32 s_rsc_vert_offset;          // reg 0x30
    // U32 s_rsc_vert_scale;           // reg 0x31
} GD_IDSP_VIN_REGS_S;

/**
 *  DSP_INIT_DATA contains initialization related parameters
 *  passed from ARM to DSP. The location is used to store a
 *  data structure that contains various buffer pointers and
 *  size information. 128 bytes for DSP_INIT_DATA
 */
typedef struct
{
    U32 *default_binary_data_ptr;
    U32 *cmd_data_ptr;
    U32 cmd_data_size;
    U32 *result_queue_ptr;
    U32 result_queue_size;
    U32 reserved_1[3];
    U32 operation_mode;
    U32 *default_config_ptr;
    U32 default_config_size;
    U32 *DSP_buf_ptr;
    U32 DSP_buf_size;
    U32 *vdsp_info_ptr;
    U32 *pjpeg_buf_ptr;
    U32 pjpeg_buf_size;
    U32 *chip_id_ptr;
    U32 reserved_2;
    U32 reserved_3[14];
} GD_DSP_INIT_DATA_S;

// Structure that indicate the vdsp interrupt status
typedef struct
{
    U32 dsp_cmd_rx; // if DSP had read from cmd buf
    U32 dsp_msg_tx;    // if DSP had written to msg buf

    U32 dsp_histogram_tx:1; //if DSP has send at least one histogram to ARM
    U32 reserv:31;
    U32 padding[5];
} GD_VDSP_INFO_S;

/**
 *  During H264/JPEG encoding mode, ARM will receive vin interrupt.
 *  ARM should copy video input polarity information to video input
 *  register area right after input interrupt is received.
 */
typedef struct
{
    U32 vin_shadow_register;
} GD_VIN_SHADOW_REGISTER_S;

/**
 *  The data structure are read by DSP at each video output frame.
 *  DSP reads the data structure after the DMA completion of the
 *  output data. ARM receives each Vout interrrupt at vsync
 *  rising edge.
 */
typedef struct
{
    U8 format;
    U8 frame_rate;
    U8 Audio_Sampling_Clock_Freq;
    U8 Audio_Output_Clock_Freq;

    U16 active_width;
    U16 active_height;

    U16 video_width;
    U16 video_height;

    U32 OSD0_addr;

    U32 OSD1_addr;

    U16 OSD0_width;
    U16 OSD1_width;

    U16 OSD0_height;
    U16 OSD1_height;

    U16 OSD0_pitch;
    U16 OSD1_pitch;

    U32 default_image_y_addr;

    U32 default_image_u_addr;

    U16 default_image_pitch;
    U16 default_image_height;

    U8 polarity;
    U8 flip_control;
    U8 reset;
    U8 OSD_progressive;
} GD_VOUT_SETUP_DATA_S;

/**
 * Binary data structure for encode mode
 */
typedef struct
{
    U32 magic_number;
    U32 manufacture_id;
    U32 uCode_version;
    U32 dram_addr_idsp_default_cfg;
    U32 dram_addr_luma_huf_tab;
    U32 dram_addr_chroma_huf_tab;
    U32 dram_addr_mctf_cfg_buffer;
    U32 dram_addr_cabac_ctx_tab;
    U32 dram_addr_jpeg_out_bit_buffer;      //BSB start addr
    U32 dram_addr_cabac_out_bit_buffer;     //BSB start addr
    U32 dram_addr_bit_info_buffer;          //Bits INFO BUFFER addr
    U32 jpeg_out_bit_buf_sz;                //BSB size
    U32 h264_out_bit_buf_sz;                //BSB size
    U32 bit_info_buf_sz;                    //Bits INFO BUFFER size
    U32 mctf_cfg_buf_sz;
} GD_DEFAULT_ENC_BINARY_DATA_S;

/**
 * Binary data structure for decode mode
 */
typedef struct
{
    U32 magic_number;
    U32 manufacture_id;
    U32 uCode_version;
    U32 dram_addr_idsp_default_cfg;
    U32 dram_addr_cabac_ctx_tab;
    U32 dram_addr_cabac_out_bit_buffer_daddr;
    U32 dram_addr_cabac_out_bit_buffer_size;
    U32 still_picture_decode_buffer_daddr;
    U32 still_picture_decode_buffer_size;
    U32 h264_frame_buffer_daddr;
    U32 h264_frame_buffer_size;
    U32 still_frame_buffer_daddr;
    U32 still_frame_buffer_size;
    U32 still_frame_buffer_pitch;
    U32 dram_addr_luma_huf_tab;
    U32 dram_addr_chroma_huf_tab;
} GD_DEFAULT_DEC_BINARY_DATA_S;

/**
 * DIS histogram information
 */
typedef struct
{
    U32 seq_nbr                         :  8;
    U32 sem_id                          :  2;
    U32 hist_x_precision_in_quater_pixel:  3;
    U32 hist_y_precision_in_quater_pixel:  3;
    U32 reserved                        : 16;

    U32 hist_x_hist_max_item_nbr    : 16; //For example, the range of the hist x dimension would be: 128: [-64,63]
    U32 hist_y_hist_max_item_nbr    : 16; //As above

    //  This one and the following one are used to specify the block area in the picture for the ME histogram
    U32 hist_start_mb_nbr           : 16;
    U32 hist_total_mb_nbr           : 16;
} GD_DIS_HIST_HEADER_S;

/*********************************************************************/
/* MESSAGE */
/**
 *  The length of a record is fixed at 128 bytes.
 *  DSP firmware continuously writes result record into the queue.
 *  ARM reads the result record out and both advance their buffer
 *  pointer. DSP doesn't handshake with ARM on result queue usage.
 */
typedef struct
{
    U32 time_stamp;
    U32 frame_number;
    U32 params[30];
} GD_DSP_RESULT_QUEUE_S;

/**
 * H264/JPEG encoding message
 */
typedef struct
{
    U8    enable        :  1;
    U8    rsc_enable    :  1;
    U8    proc          :  1;
    U8    reserved      :  5;
    S8    x_angular_velocity;
    S8    y_angular_velocity;
    U8    max_angular_velocity;
} GD_DIS_STATUS_S;

typedef struct
{
    U32 dsp_operation_mode;
    U32 timecode;
    U32 cmd_echo;
    U32 num_cmds;
    U32 aaa_data_fifo_next;
    U32 aaa_data_fifo_size;
    U32 h264_bits_fifo_next;
    U32 h264_bits_fifo_size;
    U32 h264_info_fifo_next;
    U32 h264_info_fifo_size;
    U32 jpeg_bits_fifo_next;
    U32 jpeg_bits_fifo_size;
    U32 jpeg_info_fifo_next;
    U32 jpeg_info_fifo_size;
    U32 raw_pic_addr;
    U32 thumbnail_pic_y_addr;
    U32 thumbnail_pic_uv_addr;
    U32 thumbnail_pic_y_pitch;
    U32 encode_y_pic_addr;
    U32 encode_uv_pic_addr;
    U32 encode_yuv_pitch;
    U32 preview_y_pic_addr;
    U32 preview_uv_pic_addr;
    U32 preview_yuv_pitch;
    U32 total_pic_encoded_h264_mode;
    U32 total_pic_encoded_jpeg_mode;
    U32 total_thumbnail_encoded_jpeg_mode;
    U32 raw_cap_cnt;
    U32 yuv_pic_cnt;
    U32 encode_operation_mode;
    U16 encode_state;
    U16 capture_state;
    U32 pts_val;
#define NO_ERROR    0
#define ILLEGAL_SIGNAL_1    1
    U32 err_code;
    U32 raw_pic_pitch;
    U32 raw_pic_width;
    U32 raw_pic_row;
    U32 yuv_aaa_data_fifo_next;
    U32 yuv_aaa_data_fifo_size;
    U16 re_encode_state[4];
    U32 pjpg_bitBuf_addr;
    U32 pjpg_bitBuf_sz;
    U32 total_screen_thumbnail_encoded_jpeg_mode;
    U32 screen_thumbnail_pic_y_addr;
    U32 screen_thumbnail_pic_uv_addr;
    U32 total_pic_encoded_mjpeg_mode;
    U32 main_me1_addr ;
    U32 main_me1_pitch ;
    U32 preview_c_me1_addr ;
    U32 preview_c_me1_pitch ;
} GD_ENCODE_MSG_S;

/**
 * H264/JPEG decoding message
 */
typedef struct
{
    U32 dsp_operation_mode;
    U32 timecode;
    U32 cmd_echo;
    U32 num_cmds;
    U32 main_yuv_address ;
    U32 preview_c_yuv_address ;
    U32 main_me1_address ;
    U32 preview_c_me1_address ;
    U16 main_yuv_pitch ;
    U16 preview_c_pitch ;
    U16 main_me1_pitch ;
    U16 preview_c_me1_pitch ;
    U32 stream_0_mv_address ;
    U32 stream_1_mv_address ;
    U32 stream_2_mv_address ;
    U32 stream_3_mv_address ;
    U32 stream_0_qp_address ;
    U32 stream_1_qp_address ;
    U32 stream_2_qp_address ;
    U32 stream_3_qp_address ;
} GD_ENCODE_MSG_2_S ;

/**
 * H264/JPEG decoding message
 */

typedef struct
{
    U32 dsp_operation_mode;
    U32 timecode;
    U32 cmd_echo;
    U32 num_cmds;
    U32 latest_clock_counter;
    U32 latest_pts;
    U32 jpeg_frame_count;
    U32 yuv422_y_addr;
    U32 yuv422_uv_addr;
    U32 h264_bits_fifo_next;
    U32 jpeg_bits_fifo_next;
    U32 decode_state;
    U32 error_status;
    U32 total_error_count;
    U32 decoded_pic_number;
    U32 jpeg_thumbnail_size;
    U32 jpeg_rescale_buf_pitch; /* pitch of scaled JPEG after decoding */
    U16 jpeg_rescale_buf_width;
    U16 jpeg_rescale_buf_height;
    U32 jpeg_rescale_buf_address_y; /* Y address of scaled JPEG after decoding */
    U32 jpeg_rescale_buf_address_uv;
    U32 second_rescale_buf_pitch; /* pitch of scaled JPEG after decoding */
    U16 second_rescale_buf_width;
    U16 second_rescale_buf_height;
    U32 second_rescale_buf_address_y; /* Y address of second scaled after decoding */
    U32 second_rescale_buf_address_uv;
    U32 jpeg_y_addr; /*Y address of decoded JPEG */
    U32 jpeg_uv_addr;
    U32 jpeg_pitch; /* DRAM pitch of decoded JPEG */
    U32 jpeg_width; /* width of decoded JPEG */
    U32 jpeg_height;
    U32 jpeg_capture_count;
    U32 jpeg_screennail_size;
    U32 jpeg_thumbnail_buf_dbase; /*multi scene thumbnail buffer base address*/
    U32 jpeg_thumbnail_buf_pitch; /*buffer pitch of each thumbnail buffer */
    U32 jpeg_large_thumbnail_buf_dbase; /*multi scene large thumbnail buffer base address*/
    U32 jpeg_large_thumbnail_buf_pitch; /*buffer pitch of each large thumbnail buffer */
    U16 jpeg_cabac_message_queue_fullness; /* fullness of cabac message queue */
    U16 jpeg_rescale_message_queue_fullness; /* fullness of rescale message queue */

} GD_DECODE_MSG_S;

typedef struct
{
    U16 awb_tile_col_start;
    U16 awb_tile_row_start;
    U16 awb_tile_width;
    U16 awb_tile_height;
    U16 awb_tile_active_width;
    U16 awb_tile_active_height;
    U16 awb_rgb_shift;
    U16 awb_y_shift;
    U16 awb_min_max_shift;
    U16 ae_tile_col_start;
    U16 ae_tile_row_start;
    U16 ae_tile_width;
    U16 ae_tile_height;
    U16 ae_y_shift;
    U16 ae_linear_y_shift;
    U16 af_tile_col_start;
    U16 af_tile_row_start;
    U16 af_tile_width;
    U16 af_tile_height;
    U16 af_tile_active_width;
    U16 af_tile_active_height;
    U16 af_y_shift;
    U16 af_cfa_y_shift;
    U8  awb_tile_num_col;
    U8  awb_tile_num_row;
    U8  ae_tile_num_col;
    U8  ae_tile_num_row;
    U8  af_tile_num_col;
    U8  af_tile_num_row;
    U8 total_slices_x;
    U8 total_slices_y;
    U8 slice_index_x;
    U8 slice_index_y;
    U16 slice_width;
    U16 slice_height;
    U16 slice_start_x;
    U16 slice_start_y;
} GD_AAA_TILE_CONFIG_S;

/*-------------------------------------------------
 *  Configuration mode
 *  1. Interrupt setup          (0x00001001)
 *  2. H264 encoding setup      (0x00001002)
 *  3. JPEG encoding setup      (0x00001003)
 *  4. H264 decoding setup      (0x00001004)
 *  5. JPEG decoding setup      (0x00001005)
 *  6. Reset operation          (0x00001006)
 *  7. Video output restart     (0x00001007)
 *  8. Encode timer operation   (0x00001008)
 *  9. Chip Selection           (0x00001009)
 * 10. HD echo setup            (0x0000100A)
 * 11. System setup info        (0x0000100B)
 * 12. EIS SWITCH VOUT          (0x0000100C)
 * 13. Debug level setup        (0x0000100D)
 * 14. Audio frequency setup    (0x0000100E)
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00001001 GD_INTERRUPT_SETUP
    U32 cmd_code;

    U8 vin_int;
    U8 vout_int;
} GD_DSP_CMD_INTERRUPT_SETUP_S;

typedef struct
{
    // cmd_code: 0x00001002 GD_H264_ENCODING_SETUP
    U32 cmd_code;

    U8 mode;
    U8 M;
    U8 N;
    U8 quality;

    U32 average_bitrate;

    U32 vbr_cntl;

    U32 vbr_setting :  8;
    U32 allow_I_adv :  8;
    U32 cpb_buf_idc :  8;
    U32 en_panic_rc :  2;
    U32 cpb_cmp_idc :  2;  // cpb compliance idc
    U32 fast_rc_idc :  4;

    U32 target_storage_space;

    U32 bits_fifo_base;

    U32 bits_fifo_limit;

    U32 info_fifo_base;

    U32 info_fifo_limit;

    U8 audio_in_freq;
    U8 vin_frame_rate;
    U8 encoder_frame_rate;
    U8 frame_sync;

    U16 initial_fade_in_gain;
    U16 final_fade_out_gain;

    U32 idr_interval;

    U32 cpb_user_size;

    U8 numRef_P;
    U8 numRef_B;
    U8 vin_frame_rate_ext;
    U8 encoder_frame_rate_ext;

    U32 pjpg_bits_fifo_base;

    U32 pjpg_bits_fifo_limit;

    U32 vbr_cbp_rate;

    U32 frame_rate_division_factor      :  8;
    U32 force_intlc_tb_iframe           :  1;
    U32 session_id                      :  4;
    U32 frame_rate_multiplication_factor:  8;
    U32 hflip                           :  1;
    U32 vflip                           :  1;
    U32 rotate                          :  1;
    U32 chroma_format                   :  1;
    U32 reserved                        :  7;

    U32 custom_encoder_frame_rate;
} GD_DSP_CMD_H264_ENCODE_SETUP_S, GD_DSP_CMD_VID_ENCODE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00001003 GD_JPEG_ENCODING_SETUP
    U32 cmd_code;

    U32 chroma_format;
    U32 bits_fifo_base;
    U32 bits_fifo_limit;
    U32 info_fifo_base;
    U32 info_fifo_limit;
    U32 *quant_matrix_addr;
    U32 custom_encoder_frame_rate;

    U32 mctf_mode                       :  8;
    U32 is_mjpeg                        :  1;
    U32 frame_rate_division_factor      :  8;
    U32 session_id                      :  4;
    U32 frame_rate_multiplication_factor:  8;
    U32 hflip                           :  1;
    U32 vflip                           :  1;
    U32 rotate                          :  1;

    U32 targ_bits_pp;

    U32 initial_ql                      :  8;
    U32 tolerance                       :  8;
    U32 max_recode_lp                   :  8;
    U32 total_sample_pts                :  8;

    U32 rate_curve_dram_addr;

    U16 screen_thumbnail_w;
    U16 screen_thumbnail_h;

    U16 screen_thumbnail_active_w;
    U16 screen_thumbnail_active_h;
} GD_DSP_CMD_JPEG_ENCODE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00001004 GD_H264_DECODING_SETUP
    U32 cmd_code;

    U32 bits_fifo_base;
    U32 bits_fifo_limit;
    U32 fade_in_pic_addr;
    U32 fade_in_pic_pitch;
    U32 fade_in_alpha_start;
    U32 fade_in_alpha_step;
    U32 fade_in_total_frames;
    U32 fade_out_pic_addr;
    U32 fade_out_pic_pitch;
    U32 fade_out_alpha_start;
    U32 fade_out_alpha_step;
    U32 fade_out_total_frames;

    U8 cabac_to_recon_delay;
    U8 forced_max_fb_size;
} GD_DSP_CMD_H264_DECODE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00001005 GD_JPEG_DECODING_SETUP
    U32 cmd_code;

    U32 bits_fifo_base;
    U32 bits_fifo_limit;
    U32 cross_fade_alpha_start;
    U32 cross_fade_alpha_step;
    U32 cross_fade_total_frames;

    U8 background_y;
    U8 background_cb;
    U8 background_cr;
    U8 reserved;

    U16 max_vout_width;
    U16 max_vout_height;
} GD_DSP_CMD_JPEG_DECODE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00001006 GD_RESET_OPERATION
    U32 cmd_code;
} GD_DSP_CMD_RESET_OPERATION_S;

typedef struct
{
    // cmd_code: 0x00001007 GD_VIDEO_OUTPUT_RESTART
    U32 cmd_code;

    U8 vout_id;
} GD_DSP_CMD_VIDEO_OUTPUT_RESTART_S;

typedef struct
{
    // cmd_code: 0x00001008 GD_H264_ENC_USE_TIMER
    U32 cmd_code;

    U8 timer_scaler;
    U8 display_opt;
    U8 video_term_opt;  // 0 terminate with frame wait, 1 reset idsp, and terminate right away
    U8 reserved;
} GD_DSP_CMD_VIN_TIMER_MODE_S;

typedef struct
{
    // cmd_code: 0x00001009 GD_CHIP_SELECTION
    U32 cmd_code;

    U8 chip_type;
} GD_DSP_CMD_CHIP_SELECT_S;

typedef struct
{
    // cmd_code: 0x0000100A GD_HD_ECHO_SETUP
    U32 cmd_code;

    U8 enable;
} GD_DSP_CMD_HD_ECHO_SETUP_S;

typedef struct
{
    U32    multiple_stream :  7;   // 0:single stream, 1: multiple stream
    U32    power_mode      :  1;   // 0:high power,    1: low power
} gd_application_mode_s;

typedef struct
{
    // cmd_code: 0x0000100B GD_SYSTEM_SETUP_INFO
    U32 cmd_code;

    U32 preview_A_type              :  8;
    U32 preview_B_type              :  8;
    U32 voutA_osd_blend_enabled     :  1 ;  // if set, Mixing section of VOUTA is used for DRAM to DRAM OSD blending
    U32 voutB_osd_blend_enabled     :  1 ;  // if set, Mixing section of VOUTB is used for DRAM to DRAM OSD blending
    U32 coded_bits_interrupt_enabled:  1 ;  // if set, VOUTA interrupt is generated to ARM for every H.264/MJPEG coded frame written to the bits FIFO
    U32 pip_size_preview_enabled    :  1 ;  // if set, preview A/B/C may be downscaled to PiP resolution (ie: preveiw width < 320)
    U32 low_delay_enabled           :  1 ;  // if set, IDSP will not insert one dummy frame latency after MCTF to compensate for OSD insertion.  Only for M=1 case.
    U32 padding                     : 11;

    gd_application_mode_s  sub_mode_sel;       // 0: Camcorder mode (single-stream encoder) 1: DVR mode (multiple-stream encoder)

    U8  num_yuv_src;                        // number of input YUV sources muxed together.
    U8  resv_1;
    U16 resv_2;

    U32 audio_clk_freq;

    U32 idsp_freq;

    U16 sensor_HB_pixel;
    U16 sensor_VB_pixel;
} GD_DSP_CMD_SYSTEM_SETUP_INFO_S;

typedef struct
{
    // cmd_code: 0x0000100C GD_EIS_SWITCHVOUT_DURING_ENCODE
    U32 cmd_code;

    U8 enable;
} GD_DSP_CMD_EIS_SWITCHVOUT_DURING_ENCOD_S;

typedef struct
{
    // cmd_code: 0x0000100D GD_DSP_DEBUG_LEVEL_SETUP
    U32 cmd_code;

    U8 module;
    U8 debug_level;
    U8 coding_thread_printf_disable_mask;
    U8 padding;
} GD_DSP_CMD_DSP_DEBUG_LEVEL_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000100E GD_SYSTEM_PARAMETERS_SETUP
    U32 cmd_code;

    U32 audio_clk_freq;

    U32 idsp_freq;

    U16 sensor_HB_pixel;
    U16 sensor_VB_pixel;
} GD_DSP_CMD_SYSTEM_PARAMETERS_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000100F GD_SYSTEM_IDSP_FREQ_SETUP
    U32 cmd_code;

    U32 idsp_freq;
} GD_DSP_CMD_SYSTEM_IDSP_FREQ_SETUP_S;

/*-------------------------------------------------
*  1. Sensor Input setup                (0x00002001)
*  2. RGB gain adjustment               (0x00002002)
*  3. Vignette compensation             (0x00002003)
*  4. AAA statistics setup              (0x00002004)
*  5. Luma Sharpen setup                (0x00002005)
*  6. RGB to RGB setup                  (0x00002006) obsolete
*  7. RGB to YUV setup                  (0x00002007)
*  8. Gamma curve lookup table setup    (0x00002008) obsolete
*  9. Noise filter setup                (0x00002009)
* 10. Bad Pixel Correct setup           (0x0000200A)
* 11. Vid Fade In Out setup             (0x0000200B)
* 12. CFA Domain Leakage Filter setup   (0x0000200C)
* 13. MCTF MV Stab setup                (0x0000200D)
* 14. Set slow shutter upsampling rate  (0x0000200E)
* 15. Sensor capture repeat             (0x0000200F)
* 16. MCTF GMV setup                    (0x00002010)
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00002001 GD_SENSOR_INPUT_SETUP
    U32 cmd_code;

    U8 sensor_id;
    U8 field_format;
    U8 sensor_resolution;
    U8 sensor_pattern;

    U8 first_line_field_0;
    U8 first_line_field_1;
    U8 first_line_field_2;
    U8 first_line_field_3;

    U8 first_line_field_4;
    U8 first_line_field_5;
    U8 first_line_field_6;
    U8 first_line_field_7;

    U32 sensor_readout_mode;
} GD_DSP_CMD_SENSOR_INPUT_SETUP_S;

typedef struct
{
    // cmd_code: 0x00002002 GD_RGB_GAIN_ADJUSTMENT
    U32 cmd_code;
    U32 r_gain;
    U32 g_even_gain;
    U32 g_odd_gain;
    U32 b_gain;
    U32 group_index;
} GD_DSP_CMD_RGB_GAIN_ADJUST_S;

typedef struct
{
    // cmd_code: 0x00002003 GD_VIGNETTE_COMPENSATION
    U32 cmd_code;

    U8 enable;
    U8 gain_shift;
    U16 group_index;

    U32 tile_gain_addr;
    U32 tile_gain_addr_green_even;
    U32 tile_gain_addr_green_odd;
    U32 tile_gain_addr_blue;
} GD_DSP_CMD_VIGNETTE_COMPENSATION_S;

typedef struct
{
    // cmd_code: 0x00002004 GD_AAA_STATISTICS_SETUP
    U32 cmd_code;

    U32 on          : 8;
    U32 auto_shift  : 8;
    U32 reserved    :16;

    U32 data_fifo_base;
    U32 data_fifo_limit;
    U32 data_fifo2_base;
    U32 data_fifo2_limit;

    U16 awb_tile_num_col;
    U16 awb_tile_num_row;

    U16 awb_tile_col_start;
    U16 awb_tile_row_start;

    U16 awb_tile_width;
    U16 awb_tile_height;

    U16 awb_tile_active_width;
    U16 awb_tile_active_height;

    U16 awb_pix_min_value;
    U16 awb_pix_max_value;

    U16 ae_tile_num_col;
    U16 ae_tile_num_row;

    U16 ae_tile_col_start;
    U16 ae_tile_row_start;

    U16 ae_tile_width;
    U16 ae_tile_height;

    U16 af_tile_num_col;
    U16 af_tile_num_row;

    U16 af_tile_col_start;
    U16 af_tile_row_start;

    U16 af_tile_width;
    U16 af_tile_height;

    U16 af_tile_active_width;
    U16 af_tile_active_height;

    U16 ae_pix_min_value;
    U16 ae_pix_max_value;
} GD_DSP_CMD_AAA_STATISTICS_SETUP_S;

typedef struct
{
    // cmd_code: 0x00002005 GD_LUMA_SHARPEN_SETUP
    U32 cmd_code;

    U8 strength;
} GD_DSP_CMD_LUMA_SHARPEN_SETUP_S;

typedef struct
{
    // cmd_code: 0x00002006 GD_RGB_TO_RGB_SETUP
    U32 cmd_code;

    S16 matrix_values[9];
} GD_DSP_CMD_RGB_TO_RGB_STUP_S;

typedef struct
{
    // cmd_code: 0x00002007 GD_RGB_TO_YUV_SETUP
    U32 cmd_code;

    U16 matrix_values[9];
    S16 y_offset;

    S16 u_offset;
    S16 v_offset;

    U32 group_index;
} GD_DSP_CMD_RGB_TO_YUV_STUP_S;

typedef struct
{
    // cmd_code: 0x00002008 GD_GAMMA_CURVE_LOOKUP
    U32 cmd_code;

    U32 tone_curve_addr;    // for A2 : tone_curve_addr_red
    U32 tone_curve_addr_green;
    U32 tone_curve_addr_blue;
} GD_DSP_CMD_GAMMA_CURVE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00002009 GD_NOISE_FILTER_SETUP
    U32 cmd_code;

    U32 strength;
} GD_DSP_CMD_NOISE_FILTER_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000200A GD_BAD_PIXEL_CORRECT_SETUP
    U32 cmd_code;

    U32 dynamic_bad_pixel_enable;
    U32 correction_mode;
    U32 hot_pixel_addr;
    U32 dark_pixel_addr;

    U16 shift0_4;
    U16 shift5;

    U32 static_bad_pixel_map_addr;
} GD_DSP_CMD_BAD_PIXEL_CORRECT_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000200B GD_VID_FADE_IN_OUT_SETUP
    U32 cmd_code;

    U16 fade_in_duration;
    U16 fade_out_duration;

    U8  fade_white;
} GD_DSP_CMD_VID_FADE_IN_OUT_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000200C GD_CFA_DOMAIN_LEAKAGE_FILTER
    U32 cmd_code;

    U32 enable;

    U8 alpha_rr;
    U8 alpha_rb;
    U8 alpha_br;
    U8 alpha_bb;

    U16 saturation_level;
} GD_DSP_CMD_CFA_DOMAIN_LEAKAGE_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000200D GD_MCTF_MV_STAB_SETUP
    U32 cmd_code;

    U8 noise_filter_strength;
    U8 image_stabilize_strength;
    U8 still_noise_filter_strength;
    U8 reserved;

    U32 mctf_cfg_dram_addr;
} GD_DSP_CMD_MCTF_MV_STAB_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000200E GD_SET_SLOW_SHUT_UP_SAMPL_RT
    U32 cmd_code;

    U8 slow_shutter_upsampling_rate;
} GD_DSP_CMD_SET_SLOW_SHUTTER_UPSAMPLING_RATE_S;

typedef struct
{
    // cmd_code: 0x0000200F GD_SET_REPEAT_FRM
    U32 cmd_code;

    U32 repeat_cnt;
    U32 mode_sel;
} GD_DSP_CMD_SENSOR_CAP_REPEAT_S;

typedef struct
{
    // cmd_code: 0x00002010 GD_MCTF_GMV_SETUP
    U32 cmd_code;

    U32 enable_external_gmv;
    U32 external_gmv;
} GD_DSP_CMD_MCTF_GMV_SETUP_S;

typedef struct
{
    // cmd_code: 0x00002011 GD_DIS_SETUP
    U32 cmd_code;

    U8 x_pan_thd;
    U8 y_pan_thd;
    U8 x_dis_strength  : 7;
    U8 flg_mc_enabled  : 1;
    U8 y_dis_strength  : 7;
    U8 flg_rsc_enabled : 1;

    U8 x_rsc_strength  : 7;
    U8 flg_dis_enabled : 1;
    U8 y_rsc_strength  : 7;
    U8 blk_select      : 1;
    U16 focal_length;

    U16 sensor_cell_width           : 12;
    U16 x_win_pullback_speed_if_pan : 4;
    U16 sensor_cell_height          : 12;
    U16 y_win_pullback_speed_if_pan : 4;

    U32* dis_hist_dram_addr;
    U32 dis_hist_dram_size;

    U16 me_y_top_blk_start_pos : 12;
    S16 me_x_res               : 4;
    U16 me_y_bot_blk_start_pos : 12;
    S16 me_y_res               : 4;

    U16 me_y_top_blk_height : 12;
    U16 me_x_bin            : 4;
    U16 me_y_bot_blk_height : 12;
    U16 me_y_bin            : 4;

    U32 me_lamda        : 8;
    U32 sensor_row_time : 17;
    U32 mc_beta         : 7;

    S32 x_mov : 16;
    S32 y_mov : 16;

    S32 x_skew : 16;
    S32 y_skew : 16;
} GD_DSP_CMD_DIS_ALGO_PARAMS_S;

/*-------------------------------------------------
 *  0. Set vin capture windows          (0x00002100)
 *  1. Amplifier linearization          (0x00002101)
 *  2. Pixel Shuffle                    (0x00002102)
 *  3. Black level correction           (0x00002103)
 *  4. Black level state tables         (0x00002104)
 *  5. Black level detection window     (0x00002105)
 *  6. Fixed pattern noise correction   (0x00002106)
 *  7. CFA noise filter                 (0x00002107)
 *  8. Digital gain saturation level    (0x00002108)
 *  9. Local exposure                   (0x00002109)
 * 10. Demoasic Filter                  (0x0000210A)
 * 11. RGB noise filter                 (0x0000210B)
 * 12. Color correction                 (0x0000210C)
 * 13. Chroma media filter              (0x0000210D)
 * 14. Chroma scale                     (0x0000210E)
 * 15. Luma sharpening                  (0x0000210F)
 * 16. AAA statistics setup 1           (0x00002110)
 * 17. AAA statistics setup 2           (0x00002111)
 * 18. AAA pseudo Y setup               (0x00002112)
 * 19. AAA histogram setup              (0x00002113)
 * 20. Raw compression                  (0x00002114)
 * 21. Raw decompression                (0x00002115)
 * 22. Rolling shutter compensation     (0x00002116)
 * 23. Set zoom factor                  (0x00002117)
 * 24. AAA_STATISTICS_SETUP3            (0x00002118)
 * 25. Set video preview                (0x00002119)
 * 26. Vin Reset                        (0x0000211A)
 * 27. Anti-Aliasing                    (0x0000211B)
 * 28. FPN Calibration                  (0x0000211C)
 * 29. Black level global offset        (0x0000211D)
-------------------------------------------------*/
typedef union
{
    struct
    {
        U16    sw_reset     :  1;
        U16    enb_vin      :  1;
        U16    win_en       :  1;
        U16    data_edge    :  1;
        U16    mastSlav_mod :  2;
        U16    emb_sync     :  1;
        U16    emb_sync_mode:  1;
        U16    emb_sync_loc :  2;
        U16    vs_pol       :  1;
        U16    hs_pol       :  1;
        U16    field_pol    :  1;
        U16    sony_fld_mod :  1;
        U16    ec_enb       :  1;
        U16    reserved     :  1;
    } s_cntl_bit_fld;
    U16 s_control;
} GD_S_CTRL_REG;

typedef union
{
    struct
    {
        U16    pad_type    :1;
        U16    data_rate   :1;
        U16                :1;
        U16    inp_src     :1;
        U16    inp_src_ty  :1;
        U16    src_pix_data_width:2;
        U16    yuv_inp_ord :2;
        U16    reserved    :4;
        U16    non_mipi_input:1; // New elemented added for a5s here
        U16    reserved2   :2;
    } s_inputCfg_bit_fld;
    U16    s_inputCfg;
} GD_S_INPUT_CONFIG_REG;

typedef struct
{
    U16  s_ctrl_reg;
    U16  s_inpcfg_reg;

    U16  s_status_reg;
    U16  s_v_width_reg;

    U16  s_h_width_reg;
    U16  s_h_offset_top_reg;

    U16  s_h_offset_bot_reg;
    U16  s_v_reg;

    U16  s_h_reg;
    U16  s_min_v_reg;

    U16  s_min_h_reg;
    U16  s_trigger_0_start_reg;

    U16  s_trigger_0_end_reg;
    U16  s_trigger_1_start_reg;

    U16  s_trigger_1_end_reg;
    U16  s_vout_start_0_reg;

    U16  s_vout_start_1_reg;
    U16  s_cap_start_v_reg;

    U16  s_cap_start_h_reg;
    U16  s_cap_end_v_reg;

    U16  s_cap_end_h_reg;
    U16  s_blank_leng_h_reg;

    U32  vsync_timeout;

    U32  hsync_timeout;
} GD_DSP_CMD_VIN_CAP_REG_S;

typedef struct
{
    // cmd_code: 0x00002100 GD_SET_VIN_CAPTURE_WIN
    U32 cmd_code;
    // reg 0x00: 0x04
    U32 S_Control_reset                 :  1;   // 0: no op  1: reset video in
    U32 S_Control_enable                :  1;   // 0: idle   1: enable video in
    U32 S_Control_win_en                :  1;   // enable capture window. automatic reset at the end of each capture
    U32 S_Control_data_edge             :  1;   // Data clock edge. 0: valid on rising edge of sensor clock
                                                //                  1: valid on falling edge of sensor clock
    U32 S_Control_mastSlav_mod          :  2;   // Bit [5:4] forms the following combination:
                                                // 2b00: undefined
                                                // 2b01: slave mode
                                                // 2b10: master mode
                                                // 2b11: undefined
    U32 S_Control_data_emb_sync         :  1;   // sync code embedded in data. When set in master mode,
                                                // this indicates sensors have embedded sync code while
                                                // receiving seperate sync signals (Sony specific).
    U32 S_Control_data_emb_sync_mode    :  1;   // Embedded sync mode. 0: ITU-656 style(8-bit) 1: ITU-656 style(full data range)
    U32 S_Control_data_emb_sync_loc     :  2;   // Embedded sync code location (2-pixel wide input only).
                                                // 2b00: embedded sync code carried on the lower pixel
                                                // 2b01: embedded sync code carried on the upper pixel
                                                // 2b1x: embedded sync code carried on both pixels [should programed to 2b1x for serial sensor interface modes]
    U32 S_Control_data_vs_pol           :  1;   // vsync polarity. 0: active high (rising edge signals start)  1: active low (falling edge signals start)
    U32 S_Control_data_hs_pol           :  1;   // hsync polarity. 0: active high (rising edge signals start)  1: active low (falling edge signals start)
    U32 S_Control_data_field0_pol       :  1;   // 0: field 0 has ID set to 0 with wen assertion   1:field 0 has ID set to 1 with wen assertion
    U32 S_Control_data_sony_field_mode  :  1;   // 0: normal field mode   1: Sony-specific field mode. The first field of a multi-field readout in Sony CCD/TG is indicated by the state of EXP/ID pin at the first assertion of WEN/FLD
    U32 S_Control_data_ecc_enable       :  1;   // 656 error correction enable {including the sync code words in serial sensor mode]
    U32 S_Control_data_hsync_mask       :  1;   // 0: Toggle hsync during vertical blanking    1: No hsync toggle during vertical blanking
    // reg 0x01: 0x06
    // input mode[4:0]
    U32 S_InputConfig_pad_type          :  1;   // 0: LVCMOS  1: LVDS
    U32 S_InputConfig_data_rate         :  1;   // 0: SDR    1: DDR
    U32 S_InputConfig_data_width        :  1;   // 0: 1-pixel wide  1: 2-pixel wide [should be programed to 1 (2-pixel wide) for serial sensor interface modes]
    U32 S_InputConfig_input_source      :  1;   // 0: from LVDS (lvds_idsp_sdata)     1: from GPIO (iopad_idsp_sdata). Input source and pad type forms three combinations:-LVDS source, LVDS pad.-LVDS source, LVCMOS pad.-GPIO source. (Pad type makes no difference.)
    U32 S_InputConfig_RGB_YUV           :  1;   // 0: RGB input    1: YUV input
                                                // The following are legal combinations for input mode (x: 0 or 1, -: no effect):
                                                // x000x:SDR,1-pixel wide RGB/YUV data, from lvds_idsp_sdata[13:0]
                                                // x001x:DDR,1-pixel wide RGB/YUV data, from lvds_idsp_sdata[27:0]
                                                // x0100:SDR,2-pixel wide RGB/YUV data, from lvds_idsp_sdata[27:0]
                                                // x0110:DDR,2-pixel wide RGB/YUV data, from lvds_idsp_sdata[55:0]
                                                // 110--:1-pixel wide YUV data, from iopad_idsp_sdata[7:0]
                                                // 111--:2-pixel wide YUV data, from iopad_idsp_sdata[15:0]
    U32 S_InputConfig_Source_pixel_data_width   :  2;   // Source pixel data width. VIN aligns all pixel values to MSB at output.
                                                // For example, 8-bit source means left shift by 6, 14-bit source means no shift,
                                                // etc. YUV data coming from GPIO must be 8-bit wide. (Hardware ignores the configuration.)
                                                // 2b00: 8-bit  2b01: 10-bit    2b10: 12-bit    2b11: 14-bit
    U32 S_InputConfig_YUV_input_order   :  2;   // YUV input order
                                                // For 1-pixel wide YUV data
                                                // 00:Cr,Y0,Cb,Y1,
                                                // 01:Cb,Y0,Cr,Y1,
                                                // 10:Y0,Cr,Y1,Cb,
                                                // 11:Y0,Cb,Y1,Cr,
                                                // For 2-pixel wide YUV data
                                                // 00:{Cr,Y},{Cb,Y},
                                                // 01:{Cb,Y},{Cr,Y},
                                                // 10:{Y,Cr},{Y,Cb},
                                                // 11: {Y, Cb}, {Y, Cr},
    U32 S_InputConfig_Number_of_active_SLVS_lanes   :  2;   // Number of active SLVS lanes
                                                // 2b00: 4 lanes; 2b01: 8 lanes; 2b10: 12 lanes; 2b11: 16 lanes)
    U32 S_InputConfig_Serial_sensor_interface_mode  :  1;   // Serial sensor interface mode (Micron and Sony)
    U32 S_InputConfig_Sony_serial_sensor_interface_mode :  1;   // Sony serial sensor interface mode
    U32 S_InputConfig_VIN_clock_select  :  1;   // VIN clock select - use sensor or bit clock instead of IDSP clock
    U32                                 :  2;   // reserved

    // reg 0x02: 0x08
    // Status register: Write logic 1 to the status register clears the corresponding bit.
    U32 S_Status_vsync              :  1;   // begin of frame detected
    U32 S_Status_trig0              :  1;   // trigger 0 status. 0: no trigger/ 1: triggered
    U32 S_Status_trig1              :  1;   // trigger 1 status. 0: no trigger/ 1: triggered
    U32 S_Status_ovfl               :  1;   // synchronous FIFO overflow. 0: no overflow/ 1: overflow occurred
    U32 S_Status_shortl             :  1;   // early hsync detected
    U32 S_Status_shortf             :  1;   // early vsync detected
    U32 S_Status_field              :  3;   // current video field (read only).
    U32 S_Status_no_hsync           :  1;   // no hsync detected (time out)
    U32 S_Status_no_vsync           :  1;   // no vsync detected (time out)
    U32 S_Status_idsp_ahb_vsync     :  1;   // frame end signal to ARM
    U32 S_Status_idsp_ahb_mst_vsync :  1;   // master mode frame end signal to ARM
    U32 S_Status_idsp_ahb_last_pxl  :  1;   // capture window end signal to ARM
    U32 S_Status_ecc_uncorrectable  :  1;   // uncorrectable 656 errors
    U32 S_Status_program_error      :  1;   // illegal programming detected. Currently the reported error includes:Master mode, active region exceeds frame region
    // reg 0x03: 0x0A
    // Vertical active region width (master mode only)
    U32 S_Vwidth                    : 14;   // vsync pulse width in unit of lines
    U32                             :  2;   // reserved

    // reg 0x04: 0x0C
    // Horizontal active region width (master mode only).
    U32 S_Hwidth                    : 14;   // hsync pulse width in unit of pixels
    U32                             :  2;   // reserved
    // reg 0x05: 0x0E
    U32 S_Hoffset_top               : 14;   //
    U32                             :  2;   // reserved

    // reg 0x06: 0x10
    U32 S_Hoffset_bot               : 14;   //
    U32                             :  2;   // reserved
    // reg 0x07: 0x12
    // Frame size, vertical (master mode only)
    U32 S_V                         : 14;   // Number of lines per field
    U32                             :  2;   // reserved

    // reg 0x08: 0x14
    // Frame size, horizontal (in master mode only)
    U32 S_H                         : 14;   // Number of pixels per line
    U32                             :  2;   // reserved
    // reg 0x09: 0x16
    // Minimum frame size, vertical (slave mode only)
    U32 S_MinV                      : 14;   // number of lines per field
    U32                             :  2;   // reserved

    // reg 0x0A: 0x18
    // Minimum frame size, horizontal (slave mode only)
    U32 S_MinH                      : 14;   // number of pixels per line
    U32                             :  2;   // reserved
    // reg 0x0B: 0x1A
    // Trigger 0 control
    U32 S_Trigger0Start_startline   : 14;   // startline. Assert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = startline (counting from 1st line active region)
    U32 S_Trigger0Start_pol         :  1;   // polarity. 0: active low trigger/ 1: active high trigger
    U32 S_Trigger0Start_enable      :  1;   // 0: trigger disabled/ 1: trigger enabled

    // reg 0x0C: 0x1C
    // Trigger 0 control
    U32 S_Trigger0End_startline     : 14;   // lastline. Deassert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = lastline (counting from 1st line active region)
    U32                             :  2;   // reserved
    // reg 0x0D: 0x1E
    // Trigger 1 control
    U32 S_Trigger1Start_startline   : 14;   // startline. Assert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = startline (counting from 1st line active region)
    U32 S_Trigger1Start_pol         :  1;   // polarity. 0: active low trigger/ 1: active high trigger
    U32 S_Trigger1Start_enable      :  1;   // 0: trigger disabled/ 1: trigger enabled

    // reg 0x0E: 0x20
    // Trigger 1 control
    U32 S_Trigger1End_startline     : 14;   // lastline. Deassert trigger at the assertion of hsync of the n-thline of the frame,
                                            // where n = lastline (counting from 1st line active region)
    U32                             :  2;   // reserved
    // reg 0x0F: 0x22
    // VOUT synchronization control
    U32 S_VoutStart0_startline      : 14;   // startline. Synchronization signal is asserted for the duration of the n-th line,
                                            // where n = startline (counting from 1st line active region)
    U32                             :  1;   // reserved
    U32 S_VoutStart0_disable_field_check    :  1;   // 0: synchronization signal is set on even field/ 1: synchronization signal is set on each field

    // reg 0x10: 0x24
    // VOUT synchronization control
    U32 S_VoutStart1_startline      : 14;   // startline. Synchronization signal is asserted for the duration of the n-th line,
                                            // where n = startline (counting from 1st line active region)
    U32                             :  1;   // reserved
    U32 S_VoutStart1_disable_field_check    :  1;   // 0: synchronization signal is set on even field/ 1: synchronization signal is set on each field
    // reg 0x11: 0x26
    // Capture window control, vertical start
    U32 S_CapStartV                 : 14;   // Start vertical location of capture window
    U32                             :  2;   // reserved

    // reg 0x12: 0x28
    // Capture window control, horizontal start
    U32 S_CapStartH                 : 14;   // Start horizontal location of capture window
                                            // In 8 channel , Sony serial sensor mode, the capture window should start 4
                                            // pixels after the SAV (i.e. exclude the 4 pixels added by the receiver at the
                                            // beginning of every line which are not part of the original active line)
    U32                             :  2;   // reserved
    // reg 0x13: 0x2A
    // Capture window control, vertical end
    U32 S_CapEndV                   : 14;   // End vertical location of capture window
    U32                             :  2;   // reserved

    // reg 0x14: 0x2C
    // Capture window control, horizontal end
    U32 S_CapEndH                   : 14;   // End horizontal location of capture window
                                            // In 8 channel, Sony serial sensor mode, the capture window should end 4 pixels
                                            // before the EAV sync code to exclude the additional sync code pixels.
    U32                             :  2;   // reserved
    // reg 0x15: 0x2E
    // All-zero embedded sync horizontal blank interval length
    U32 S_BlankLengthH              : 14;   // Blank interval length in sensor clock cycles
    U32                             :  2;   // reserved

    // reg 0x16: 0x30
    // Vsync timeout limit (lower 16 bits) and also EAV column for SLVS mode.
    U32 S_TimeoutVLow               : 16;   // SLVS mode programing notes:Should be integer multiple of 4 and does not count SAV/EAV sync code pixels
    // reg 0x17: 0x32
    // Vsync timeout limit (upper 16 bits)
    U32 S_TimeoutVHigh              : 16;   //

    // reg 0x18: 0x34
    // Hsync timeout limit (lower 16 bits) and also Horizontal line length (SAV-to-SAV distance) in SLVS mode.
    U32 S_TimeoutHLow               : 16;   // SLVS mode programing notes:Should be integer multiple of 4 and does not count SAV/EAV sync code pixels
    // reg 0x19: 0x36
    // Hsync timeout limit (lower 16 bits)
    U32 S_TimeoutHHigh              : 16;   //

    // reg 0x19: 0x38
    U32 S_mipi_cfg1                 : 16;   //
    // reg 0x1A: 0x3A
    U32 S_mipi_cfg2                 : 16;   //

    // reg 0x1B: 0x3C
    U32 S_mipi_bdphyctl             : 16;   //
    // reg 0x1C: 0x3E
    U32 S_mipi_sdphyctl             : 16;   //
} GD_DSP_CMD_VIN_CAP_WIN_S;

typedef struct
{
    // cmd_code: 0x00002101 GD_AMPLIFIER_LINEARIZATION
    U32 cmd_code;

    U32 enable;
    U32 look_up_table_addr;
    U32 exponent_table_addr;
    U32 black_level_offset_table_addr;
} GD_DSP_CMD_AMPLIFIER_LINEAR_S;

typedef struct
{
    // cmd_code: 0x00002102 GD_PIXEL_SHUFFLE
    U32 cmd_code;

    U32 enable;
    U32 reorder_mode;
    U32 input_width;

    U16 start_index[8];

    U16 pitch[8];
} GD_DSP_CMD_PIXEL_SHUFFLE_S;

typedef struct
{
    // cmd_code: 0x00002103 GD_BLACK_LEVEL_CORRECTION_CONFIG
    U32 cmd_code;

    U32 column_enable;
    U32 row_enable;
    U32 black_level_mode;
    U32 bad_pixel_mode_column;
    U32 bad_pixel_mode_row;
    U32 cold_pixel_thresh;
    U32 hot_pixel_thresh;
    U32 center_offset;
    U32 column_replace;
    U32 column_invalid_replace;
    U32 column_invalid_thresh;
    U32 row_invalid_thresh;
    U32 column_average_k_frames;
    U32 row_average_k_frames;
    U32 column_black_gain;
    U32 row_black_gain;
    U32 column_bad_pixel_subtract;
    U32 global_offset_ee;
    U32 global_offset_eo;
    U32 global_offset_oe;
    U32 global_offset_oo;
} GD_DSP_CMD_BLACK_LEVEL_CORRECTTION_S;

typedef struct
{
    // cmd_code: 0x00002104 GD_BLACK_LEVEL_STATE_TABLES
    U32 cmd_code;

    U32 num_columns;
    U32 column_frame_acc_addr;
    U32 column_average_acc_addr;
    U32 num_rows;
    U32 row_fixed_offset_addr;
    U32 row_average_acc_addr;
} GD_DSP_CMD_BLACK_LEVEL_STATE_TABLE_S;

typedef struct
{
    // cmd_code: 0x00002105 GD_BLACK_LEVEL_DETECTION_WINDOW
    U32 cmd_code;

    U8 top_black_present;
    U8 bottom_black_present;
    U8 left_black_present;
    U8 right_black_present;

    U32 top_black_start;
    U32 top_black_end;
    U32 bottom_black_start;
    U32 bottom_black_end;
    U32 left_black_start;
    U32 left_black_end;
    U32 right_black_start;
    U32 right_black_end;
} GD_DSP_CMD_BLACK_LEVEL_DETECT_WIN_S;

typedef struct
{
     // cmd_code: 0x00002106 GD_FIXED_PATTERN_NOISE_CORRECTION
    U32 cmd_code;

    U32 fpn_pixel_mode;
    U32 row_gain_enable;
    U32 column_gain_enable;
    U32 num_of_rows;

    U16 num_of_cols;
    U16 fpn_pitch;

    U32 fpn_pixels_addr;
    U32 fpn_pixels_buf_size;
    U32 intercept_shift;
    U32 intercepts_and_slopes_addr;
    U32 row_gain_addr;
    U32 column_gain_addr;
} GD_DSP_CMD_FIXED_PATTERN_NOISE_CORRECT_S;

typedef struct
{
    // cmd_code: 0x00002107 GD_CFA_NOISE_FILTER_INFO
    U32 cmd_code;

    U32 enable;
    U32 center_weight_red;
    U32 center_weight_green;
    U32 center_weight_blue;
    U32 thresh_k0_red;
    U32 thresh_k0_green;
    U32 thresh_k0_blue;
    U32 thresh_k0_close;
    U32 thresh_k1_red;
    U32 thresh_k1_green;
    U32 thresh_k1_blue;
    U32 direct_center_weight_red;
    U32 direct_center_weight_green;
    U32 direct_center_weight_blue;
    U32 direct_thresh_k0_red;
    U32 direct_thresh_k0_green;
    U32 direct_thresh_k0_blue;
    U32 direct_thresh_k1_red;
    U32 direct_thresh_k1_green;
    U32 direct_thresh_k1_blue;
    U32 direct_grad_thresh;
} GD_DSP_CMD_CFA_NOISE_FILTER_INFO_S;

typedef struct
{
    // cmd_code: 0x00002108 GD_DIGITAL_GAIN_SATURATION_LEVEL
    U32 cmd_code;

    U32 level_red;
    U32 level_green_even;
    U32 level_green_odd;
    U32 level_blue;
    U32 group_index;
} GD_DSP_CMD_DIGITAL_GAIN_LEVEL_S;

typedef struct
{
    // cmd_code: 0x00002109 GD_LOCAL_EXPOSURE
    U32 cmd_code;

    U16 enable;
    U16 group_index;

    U32 radius;

    U8 luma_weight_red;
    U8 luma_weight_green;
    U8 luma_weight_blue;
    U8 luma_weight_sum_shift;

    U32 gain_curve_table_addr;

    U16 black_level_offset_red;
    U16 black_level_offset_green;

    U16 black_level_offset_blue;
    U16 luma_offset;

    U16 global_offset;
} GD_DSP_CMD_LOCAL_EXPOSURE_S;

typedef struct
{
    // cmd_code: 0x0000210A GD_DEMOASIC_FILTER
    U32 cmd_code;

    U16 enable;
    U16 group_index;

    U32 grad_clip_thresh;
    U32 grad_noise_thresh;
    U32 activity_thresh;
    U32 activity_difference_thresh;
} GD_DSP_CMD_DEMOASIC_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000210B GD_RGB_NOISE_FILTER
    U32 cmd_code;

    U32 speckle_filter_enable;
    U32 reinterpol_filter_enable;
    U32 jag_filter_enable;
    U32 jag_thresh_grad_add;
    U32 jag_thresh_grad_mult;
    U32 jag_thresh_add;

    U16 jag_thresh_mult;
    U16 group_index;

    U8 direction_filter_enable;
    U8 thresh_grad_mult;
    U16 thresh_grad_add;

    U8 streng_origin_red;
    U8 streng_origin_green;
    U8 streng_origin_blue;
    U8 streng_interpol_red;

    U8 streng_interpol_green;
    U8 streng_interpol_blue;
    U8 streng_isotrop_origin_red;
    U8 streng_isotrop_origin_green;

    U8 streng_isotrop_origin_blue;
    U8 streng_isotrop_interpol_red;
    U8 streng_isotrop_interpol_green;
    U8 streng_isotrop_interpol_blue;
} GD_DSP_CMD_RGB_NOISE_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000210C GD_COLOR_CORRECTION
    U32 cmd_code;

    U8 enable;
    U8 no_interpolation;
    U8 yuv422_foramt;
    U8 uv_center;

    U32 multi_red;
    U32 multi_green;
    U32 multi_blue;
    U32 in_lookup_table_addr;
    U32 matrix_addr;
    U32 output_lookup_bypass;
    U32 out_lookup_table_addr;
    U32 group_index;
} GD_DSP_CMD_COLOR_CORRECTION_S;

typedef struct
{
    // cmd_code: 0x0000210D GD_CHROMA_MEDIAN_FILTER_INFO
    U32 cmd_code;

    U32 enable;
    U32 group_index;
    U32 k0123_table_addr;

    U16 u_sat_t0;
    U16 u_sat_t1;

    U16 v_sat_t0;
    U16 v_sat_t1;

    U16 u_act_t0;
    U16 u_act_t1;

    U16 v_act_t0;
    U16 v_act_t1;
} GD_DSP_CMD_CHROMA_MEDIAN_FILTER_INFO_S;

typedef struct
{
    // cmd_code: 0x0000210E GD_CHROMA_SCALE
    U32 cmd_code;

    U32 enable;
    U32 make_legal;

    S16 u_weight_0;
    S16 u_weight_1;

    S16 u_weight_2;
    S16 v_weight_0;

    S16 v_weight_1;
    S16 v_weight_2;

    U32 gain_curver_addr;
    U32 group_index;
} GD_DSP_CMD_CHROMA_SCALE_S;

typedef struct
{
    // cmd_code: 0x0000210F GD_LUMA_SHARPENING
    U32 cmd_code;

    U32 enable;
    U32 grad_thresh_0;
    U32 grad_thresh_1;
    U32 smooth_shift;
    U32 edge_shift;
    U32 edge_thresh;
    U32 alpha_table_addr;
    U32 group_index;
    U32 unsharp_mask[6];

    U8  clip_low;
    U8  clip_high;
    U8  max_change_down;
    U8  max_change_up;
} GD_DSP_CMD_LUMA_SHARPENING_S;

typedef struct
{
    // cmd_code: 0x00002110 GD_AAA_STATISTICS_SETUP1
    // cmd_code: 0x00002111 GD_AAA_STATISTICS_SETUP2
    U32 cmd_code;

    U8 af_horizontal_filter_mode    :  4;
    U8 af_filter_select             :  4;
    U8 af_horizontal_filter_stage1_enb;
    U8 af_horizontal_filter_stage2_enb;
    U8 af_horizontal_filter_stage3_enb;

    U16 af_horizontal_filter_gain[7];
    U16 af_horizontal_filter_shift[4];
    U16 af_horizontal_filter_bias_off;

    U16 af_horizontal_filter_thresh;
    U16 af_vertical_filter_thresh;

    U16 af_tile_fv_horizontal_shift;
    U16 af_tile_fv_vertical_shift;

    U16 af_tile_fv_horizontal_weight;
    U16 af_tile_fv_vertical_weight;
} GD_DSP_CMD_AAA_STATISTICS_SETUP12_S;

typedef struct
{
    // cmd_code: 0x00002112 GD_AAA_PSEUDO_Y_SETUP
    U32 cmd_code;

    U32 mode;
    U32 sum_shift;

    U8 pixel_weight[4];

    U8 tone_curve[32];
} GD_DSP_CMD_AAA_PSEUDO_Y_S;

typedef struct
{
    // cmd_code: 0x00002113 GD_AAA_HISTORGRAM_SETUP
    U32 cmd_code;

    U16 mode;
    U16 histogram_select;

    U16 ae_file_mask[8];
} GD_DSP_CMD_AAA_HISTOGRAM_S;

typedef struct
{
    // cmd_code: 0x00002114 GD_RAW_COMPRESSION
    U32 cmd_code;

    U32 enable;
    U32 lossy_mode;
    U32 vic_mode;
} GD_DSP_CMD_RAW_COMPRESSION_S;

typedef struct
{
    // cmd_code: 0x00002115 GD_RAW_DECOMPRESSION
    U32 cmd_code;

    U32 enable;
    U32 lossy_mode;
    U32 vic_mode;
    U32 image_width;
    U32 image_height;
} GD_DSP_CMD_RAW_DECOMPRESSION_S;

typedef struct
{
    // cmd_code: 0x00002116 GD_ROLLING_SHUTTER_COMPENSATION
    U32 cmd_code;

    U32 enable;
    U32 skew_init_phase_horizontal;
    U32 skew_phase_incre_horizontal;
    U32 skew_phase_incre_vertical;
} GD_DSP_CMD_ROLLING_SHUTTER_COMPENSATION_S;

typedef struct
{
    // cmd_code: 0x00002117 GD_SET_ZOOM_FACTOR
    U32 cmd_code;

    U32 zoom_x;
    U32 zoom_y;
    U32 x_center_offset;
    U32 y_center_offset;
} GD_DSP_CMD_ZOOM_FACTOR_S;

typedef struct
{
    // cmd_code: 0x00002118 GD_AAA_STATISTICS_SETUP3
    U32 cmd_code;

    U16 awb_tile_rgb_shift;
    U16 awb_tile_y_shift;
    U16 awb_tile_min_max_shift;
    U16 ae_tile_y_shift;
    U16 ae_tile_linear_y_shift;
    U16 af_tile_cfa_y_shift;
    U16 af_tile_y_shift;
} GD_DSP_CMD_AAA_STATISTICS_SETUP3_S;

typedef struct
{
    // cmd_code: 0x00002119 GD_VIDEO_PREVIEW_SETUP
    U32 cmd_code;
    U8 preview_id;
    U8 preview_format;
    U16 preview_w;

    U16 preview_h;
    U8 preview_frame_rate;
    U8 preview_en;
/*
?* new fields for preview source window parameters of preview A and B
?* x/y offset is relative to the upper left
?* corner of the Main window.
?*/
    U16 preview_src_w;
    U16 preview_src_h;

    U16 preview_src_x_offset;
    U16 preview_src_y_offset;

    U32 preview_freeze_enabled  :  1;
    U32 preview_freeze_offset_x : 10;
    U32 preview_freeze_offset_y : 10;
    U32 resv                    : 11;
} GD_DSP_CMD_VIDEO_PREVIEW_S;

typedef struct
{
    // cmd_code: 0x0000211B GD_ANTI_ALIASING
    U32 cmd_code;

    U32 enable;
    U32 threshold;
    U32 shift;
} GD_DSP_CMD_ANTI_ALIASING_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000211C GD_FPN_CALIBRATION
    U32 cmd_code;

    U32 dram_addr;
    U32 width;
    U32 height;
    U32 num_of_frames;
} GD_DSP_CMD_FPN_CALIBRATION_S;

typedef struct
{
    // cmd_code: 0x0000211D GD_BLACK_LEVEL_GLOBAL_OFFSET
    U32 cmd_code;

    U32 global_offset_ee;
    U32 global_offset_eo;
    U32 global_offset_oe;
    U32 global_offset_oo;

    U16 black_level_offset_red;
    U16 black_level_offset_green;

    U16 black_level_offset_blue;
} GD_DSP_CMD_BLACK_LEVEL_GLOBAL_OFFSET_S;

typedef struct
{
    // cmd_code: 0x0000211E GD_RGB_DIRECTIONAL_FILTER
    U32 cmd_code;

    U8  directional_filter_enable;
    U8  thresh_gradient_mult;
    U16 thresh_gradient_add;

    U16 thresh_blend_dir_0;
    U16 thresh_blend_dir_1;

    U16 thresh_blend_iso_0;
    U16 thresh_blend_iso_1;

    U32 coeff_dir_orig_addr;
    U32 coeff_iso_orig_addr;
    U32 coeff_dir_interpolated_addr;
    U32 coeff_iso_interpolated_addr;
} GD_DSP_CMD_RGB_DIRECTIONAL_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000211F GD_HDR_MIXER
    U32 cmd_code;

    U32 mixer_mode;

    U8  radius;
    U8  luma_weight_red;
    U8  luma_weight_green;
    U8  luma_weight_blue;

    U16 threshold;
    U8  thresh_delta;
    U8  long_exposure_shift;
} GD_DSP_CMD_HDR_MIXER_S;

typedef struct
{
    // cmd_code: 0x00002120 GD_LUMA_SHARPENING_LINEARIZATION
    U32 cmd_code;

    U32 enable;
    U32 linearization_table_addr;
    U32 inverse_linearization_table_addr;
    U32 low_noise_luma_linearization_table_addr;
    U32 group_index;
} GD_DSP_CMD_LUMA_SHARPENING_LINEARIZATION_S;

typedef struct
{
    // cmd_code: 0x00002121 GD_LUMA_SHARPENING_FIR_CONFIG
    U32 cmd_code;

    U8  enable_FIR1;
    U8  enable_FIR2;
    U16 enable_FIR2_bypass_alpha;

    U32 fir0_clip_low;
    U32 fir0_clip_high;
    U32 fir1_clip_low;
    U32 fir1_clip_high;
    U32 fir2_clip_low;
    U32 fir2_clip_high;
    U32 coeff_FIR0_addr;
    U32 coeff_FIR1_addr;
    U32 coeff_FIR2_addr;
    U32 coring_table_addr;
    U32 group_index;
} GD_DSP_CMD_LUMA_SHARPENING_FIR_CONFIG_S;

typedef struct
{
    // cmd_code: 0x00002122 GD_LUMA_SHARPENING_LNL
    U32 cmd_code;

    U8  enable;
    U8  weight_red;
    U8  weight_green;
    U8  weight_blue;

    U32 input_clip_red;
    U32 input_clip_green;
    U32 input_clip_blue;
    U32 low_noise_luma_linearization_table_addr;
    U32 tone_curve_addr;
    U32 group_index;
} GD_DSP_CMD_LUMA_SHARPENING_LNL_S;

typedef struct
{
    // cmd_code: 0x00002123 GD_LUMA_SHARPENING_TONE
    U32 cmd_code;

    U8  enable;
    U8  enable_manual_luma_adjust;
    U8  luma_low;
    U8  luma_high;

    U8  luma_alpha_low;
    U8  luma_alpha_high;
    U8  luma_delta_low;
    U8  luma_delta_high;

    U32 tone_control_config_addr;
    U32 group_index;
} GD_DSP_CMD_LUMA_SHARPENING_TONE_CONTROL_S;

typedef struct
{
    // cmd_code: 0x00002124 GD_MULTI_STREAM_VIDEO_PREVIEW
    U32 cmd_code;

    U16 preview_id;
    U16 num_preview_ins;

    U32 preview_src     :  8;
    U32 dis_dev_x_loc   : 12;
    U32 dis_dev_y_loc   : 12;

    U16 preview_width;
    U16 preview_height;
} GD_DSP_CMD_MULTI_STREAM_PREVIEW_S;

typedef struct
{
    // cmd_code: 0x00002125 GD_ENA_SECOND_STREAM_ENCODE
    U32 cmd_code;

    U32 primary_stream_channel  : 24;
    U32 frame_rate              :  8;

    U16 output_width;
    U16 output_height;

    U16 encode_width;
    U16 encode_height;
} GD_DSP_CMD_ENA_SECOND_STREAM_S;

typedef struct
{
    // cmd_code: 0x00002126 GD_SET_ALPHA_CHANNEL
    U32 cmd_code;

    U32 luma_alpha_addr;
    U32 chroma_alpha_addr;

    U16 luma_alpha_pitch;
    U16 luma_alpha_width;

    U16 luma_alpha_height;
    U16 chroma_alpha_pitch;

    U16 chroma_alpha_width;
    U16 chroma_alpha_height;
} GD_DSP_CMD_SET_ALPHA_CHANNEL_S;

/**
 *
 * Modify Frame Buffer
 * Used to get some DRAM from DSP in some mode
 * and return it back to DSP when finished.
 * User only send this command when the DSP is in IDEL State.
 */
typedef struct
{
    // cmd_code: 0x00002127 GD_MODIFY_FRAME_BUFFER
    U32 cmd_code;

    U32 dramStart; //32 bits DRAM ADDRSS of the Frame Buffer. Must be 32 bits aligned
    U32 dramSize;  //32 bits Size of the DRAM for DSP.
} GD_DSP_CMD_MODIFY_FRAME_BUFFER_S;

typedef struct
{
    // cmd_code: 0x00002128 GD_SET_ACT_WIN_CENTER
    U32 cmd_code;

    S32 x_offset;
    S32 y_offset;
    S32 x_frm_mv;
    S32 y_frm_mv;
} GD_DSP_CMD_SET_ATIVE_WIN_CTR_OFS_S;

typedef struct
{
    // cmd_code: 0x00002129 GD_SET_WARP_CONTROL
    U32 cmd_code;

    U32 warp_control;
    U32 warp_horizontal_table_address;
    U32 warp_vertical_table_address;
    U32 actual_left_top_x;
    U32 actual_left_top_y;
    U32 actual_right_bot_x;
    U32 actual_right_bot_y;
    U32 zoom_x;
    U32 zoom_y;
    U32 x_center_offset;
    U32 y_center_offset;

    U8  grid_array_width;
    U8  grid_array_height;
    U8  horz_grid_spacing_exponent;
    U8  vert_grid_spacing_exponent;

    U8  vert_warp_enable;
    U8  vert_warp_grid_array_width;
    U8  vert_warp_grid_array_height;
    U8  vert_warp_horz_grid_spacing_exponent;

    U8  vert_warp_vert_grid_spacing_exponent;
    U8  binning;
    U16 reserved_2;

    S32 hor_skew_phase_inc;

    /*
        This one is used for ARM to calcuate the
        dummy window for Ucode, these fields should be
        zero for turbo command in case of EIS. could be
        non-zero valid value only when this warp command is send
        in non-turbo command way.
    */
    U16 dummy_window_x_left;
    U16 dummy_window_y_top;

    U16    dummy_window_width;
    U16    dummy_window_height;
    /*
        This field is used for ARM to calculate the
        cfa prescaler zoom factor which will affect
        the warping table value. this should also be zeor
        during the turbo command sending.Only valid on the
        non-turbo command time.
    */
     U16 cfa_output_width;
     U16 cfa_output_height;
} GD_DSP_CMD_SET_WARP_CONTROL_S;

typedef struct
{
    // cmd_code: 0x0000212A GD_EARLY_WB_GAIN
    U32 cmd_code;

    U32 cfa_early_red_multiplier;
    U32 cfa_early_green_multiplier_even;
    U32 cfa_early_green_multiplier_odd;
    U32 cfa_early_blue_multiplier;
    U32 aaa_early_red_multiplier;
    U32 aaa_early_green_multiplier_even;
    U32 aaa_early_green_multiplier_odd;
    U32 aaa_early_blue_multiplier;
} GD_DSP_CMD_EARLY_WB_GAIN_S;

typedef struct
{
    // cmd_code: 0x00002130 GD_LUMA_SHARPENING_EDGE_CONTROL
    U32 cmd_code;

    U32 group_index;

    U16 edge_threshold;
    U8  edge_threshold_multiplier;
    U8  wide_weight;

    U8  narrow_weight;
} GD_DSP_CMD_LUMA_SHARPENING_EDGE_CONTROL_S;

typedef struct
{
    // cmd_code: 0x00002131 GD_LUMA_SHARPENING_BLEND_CONTROL
    U32 cmd_code;

    U32 group_index;

    U16 enable;
    U8  edge_threshold_multiplier;
    U8  iso_threshold_multiplier;

    U16 edge_threshold0;
    U16 edge_threshold1;

    U16 dir_threshold0;
    U16 dir_threshold1;

    U16 iso_threshold0;
    U16 iso_threshold1;
} GD_DSP_CMD_LUMA_SHARPENING_BLEND_CONTROL_S;

typedef struct
{
    // cmd_code: 0x00002132 GD_LUMA_SHARPENING_LEVEL_CONTROL
    U32 cmd_code;

    U32 group_index;

    U32 select;

    U8  low;
    U8  low_0;
    U8  low_delta;
    U8  low_val;

    U8  high;
    U8  high_0;
    U8  high_delta;
    U8  high_val;

    U8  base_val;
    U8  area;
    U16 level_control_clip_low;

    U16 level_control_clip_low2;
    U16 level_control_clip_high;

    U16 level_control_clip_high2;
} GD_DSP_CMD_LUMA_SHARPENING_LEVEL_CONTROL_S;

typedef struct
{
    // cmd_code: 0x00002133 GD_LUMA_SHARPENING_MISC_CONTROL
    U32 cmd_code;

    U32 group_index;

    U8  coring_control;
    U8  add_in_low_pass;
    U8  second_input_enable;
    U8  second_input_signed;

    U8  second_input_shift;
    U8  output_signed;
    U8  output_shift;
    U8  abs;

    U8  yuv;
} GD_DSP_CMD_LUMA_SHARPENING_MISC_CONTROL_S;

typedef struct
{
    // cmd_code: 0x00002134 GD_AAA_EARLY_WB_GAIN
    U32 cmd_code;

    U32 red_multiplier;
    U32 green_multiplier_even;
    U32 green_multiplier_odd;
    U32 blue_multiplier;

    U8  enable_ae_wb_gain;
    U8  enable_af_wb_gain;
    U8  enable_histogram_wb_gain;
    U8  reserved;

    U32 red_wb_multiplier;
    U32 green_wb_multiplier_even;
    U32 green_wb_multiplier_odd;
    U32 blue_wb_multiplier;
} GD_DSP_CMD_AAA_EARLY_WB_GAIN_S;

/*-------------------------------------------------
 *  H264/JPEG encoding mode
 *  1. Video Preprocessing              (0x00003001)
 *  2. Fast AAA capture                 (0x00003002)
 *  3. H264 encode                      (0x00003004)
 *  4. H264 encode from memory          (0x00003005) invalid
 *  5. H264 bits FIFO update            (0x00003006)
 *  6. H264 encoding stop               (0x00003007)
 *  7. Still capture                    (0x00004001)
 *  8. JPEG encode/rescale from memory  (0x00004002)
 *  9. JPEG bits FIFO update            (0x00004003)
 * 10. Free RAW/YUV422 pictures buffers (0x00004004)
 * 11. JPEG/RQW/YUV/422 Stop            (0x00004005)
 * 12. Vid Fade In Out                  (0x00004007)
 * 13. MJPEG encode with h264           (0x00004008)
 * 14. OSD insert in MJPEG and H264     (0x00004009)
 * 15. YUV422 capture                   (0x00004010)
 * 16. Send cavlc result                (0x00004011)
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00003001 GD_VIDEO_PREPROCESSING
    U32 cmd_code;

    U32 input_format    :  8;
    U32 sensor_id       :  8;
    U32 keep_states     :  8;
    U32 vin_frame_rate  :  8;

    U16 vidcap_w;
    U16 vidcap_h;

    U16 main_w;
    U16 main_h;

    U16 encode_w;
    U16 encode_h;

    U16 encode_x;
    U16 encode_y;

    U16 preview_w_A;
    U16 preview_h_A;

    U32 input_center_x;
    U32 input_center_y;
    U32 zoom_factor_x;
    U32 zoom_factor_y;
    U32 aaa_data_fifo_start;
    U32 sensor_readout_mode;

    U8 noise_filter_strength;
    U8 image_stabilize_strength;
    U8 bit_resolution;
    U8 bayer_pattern;

    U8 preview_format_A     :  4;
    U8 preview_format_B     :  3;
    U8 no_pipelineflush     :  1;
    U8 preview_frame_rate_A;
    U16 preview_w_B;

    U16 preview_h_B;
    U8 preview_frame_rate_B;
    U8 preview_A_en         :  4; // 0: dram, 1: smem
    U8 preview_B_en         :  4; // 0: dram, 1: smem

    U16 horizontal_channel_number; // number of channels (streams) displayed on horizontal direction in preview window.
    U16 vertical_channel_number;    //number of channels (streams) displayed on vertical direction in preview window.

    U8 vin_frame_rate_ext;
    U8 vdsp_int_factor;
    U8 main_out_frame_rate;
    U8 main_out_frame_rate_ext;

    U8 vid_skip;                     //used to skip N start frames in VIN capture to avoid bad frames
    U8 EIS_enable               :  1;        //Used to inidcate that EIS will be used.
    U8 DIS_enable               :  1;        //Used to indicate that DIS will be used
    U8 Vert_WARP_enable         :  1;        //Used to indicate that Vertical  WARP will be used
    U8 no_vin_reset_exiting     :  1;        //Used to indicate that we do not need to resetting vin and need to wait
                                    //out the vin before exiting VIDEO mode to TIMER mode
    U8 support_cfa_out_win_2129 :  1;    //Enable teh CFA output window support in ucode.
                                    //This one is only useful for non DIS pipeline
    U8 oversampling_disabled    :  1;        // When set to 1, oversampling is disabled
    U8 hd_sdi_mode              :  1;     // when set to 1, HD-SDI mode
    U8 reserved                 :  1;
    U16 reserved_2;

    U32 cmdReadDly;                // Used to indicate the turbo command time related to normal interrrupts.
                                // First bit indicate its direction,
                                // 1: before the VDSP interrupt, i.e., turbo command deadline is the
                                // absolute value of cmdReadDly's audio clk before the next normal interrupts.
                                // 0: after the VDSP interrutps, i.e., turbo command deadline is the
                                // absolute value of cmdReadDly's audio clk after the next normal interrutps.
    // new fields for preview source window parameters of preview A and B
    // x/y offset is relative to the upper left
    // corner of the Main window.
    U16 preview_src_w_A;
    U16 preview_src_h_A;
    U16 preview_src_x_offset_A;
    U16 preview_src_y_offset_A;
    U16 preview_src_w_B;
    U16 preview_src_h_B;
    U16 preview_src_x_offset_B;
    U16 preview_src_y_offset_B;
} GD_DSP_CMD_VIDEO_PREPROC_S;

typedef struct
{
    // cmd_code: 0x00003002 GD_FAST_AAA_CAPTURE
    U32 cmd_code;

    U16 input_image_width;
    U16 input_image_height;

    U32 start_record_id;
} GD_DSP_CMD_FAST_AAA_CAPTURE_S;

typedef struct
{
    // cmd_code: 0x00003004 GD_H264_ENCODE
    U32 cmd_code;

    U32 bits_fifo_next;
    U32 info_fifo_next;
    U32 start_encode_frame_no;
    U32 encode_duration;

    U8 is_flush;
    U8 enable_slow_shutter;
    U8 res_rate_min;        // between 0 and 100
    S8 alpha;               // between -6 and 6

    S8 beta;                // between -6 and 6
    U8 en_loop_filter;      // 1 enable loop filtering.
    U8 max_upsampling_rate;
    U8 slow_shutter_upsampling_rate;

    // SPS
    U8 frame_cropping_flag;
    U8 high_profile     :  1;
    U8 reserved2        :  7;
    U16 frame_crop_left_offset;

    U16 frame_crop_right_offset;
    U16 frame_crop_top_offset;

    U16 frame_crop_bottom_offset;
    U8 num_ref_frame;
    U8 log2_max_frame_num_minus4;

    U8 log2_max_pic_order_cnt_lsb_minus4;
    U8 sony_avc     :  1;
    U8 reserved     :  7;
    U16 height_mjpeg_h264_simultaneous;

    U16 width_mjpeg_h264_simultaneous;
    U16 vui_enable                              :  1;
    U16 aspect_ratio_info_present_flag          :  1;
    U16 overscan_info_present_flag              :  1;
    U16 overscan_appropriate_flag               :  1;
    U16 video_signal_type_present_flag          :  1;
    U16 video_full_range_flag                   :  1;
    U16 colour_description_present_flag         :  1;
    U16 chroma_loc_info_present_flag            :  1;
    U16 timing_info_present_flag                :  1;
    U16 fixed_frame_rate_flag                   :  1;
    U16 nal_hrd_parameters_present_flag         :  1;
    U16 vcl_hrd_parameters_present_flag         :  1;
    U16 low_delay_hrd_flag                      :  1;
    U16 pic_struct_present_flag                 :  1;
    U16 bitstream_restriction_flag              :  1;
    U16 motion_vectors_over_pic_boundaries_flag :  1;

    // aspect_ratio_info_present_flag
    U16 SAR_width;
    U16 SAR_height;

    // video_signal_type_present_flag
    U8 video_format;
    // colour_description_present_flag
    U8 colour_primaries;
    U8 transfer_characteristics;
    U8 matrix_coefficients;

    // chroma_loc_info_present_flag
    U8 chroma_sample_loc_type_top_field     :  4;
    U8 chroma_sample_loc_type_bottom_field  :  4;
    U8 aspect_ratio_idc;
    U8 reserved3;

    // bitstream_restriction_flag
    U32 max_bytes_per_pic_denom         :  8;
    U32 max_bits_per_mb_denom           :  8;
    U32 log2_max_mv_length_horizontal   :  8;
    U32 log2_max_mv_length_vertical     :  8;

    U16 num_reorder_frames;
    U16 max_dec_frame_buffering;

    U32 I_IDR_sp_rc_handle_mask :  8;
    U32 IDR_QP_adj_str          :  8;
    U32 IDR_class_adj_limit     :  8;
    U32 reserved_1              :  8;

    U32 I_QP_adj_str            :  8;
    U32 I_class_adj_limit       :  8;
    U32 firstGOPstartB          :  8;
    U32 au_type                 :  8;

    //tune the AQP and mode bias
    S8 intra16x16_bias;   // -64~64, clamp the negative value to -64 to avoid underflow
    S8 intra4x4_bias;     // -64~64,  clamp the negative value to -64 to avoid underflow
    S8 inter16x16_bias;   // -64~64, clamp the negative value to -64 to avoid underflow
    S8 inter8x8_bias;     // -64~64, clamp the negative value to -64 to avoid underflow

    S8 direct16x16_bias;  // -64~64, clamp the negative value to -64 to avoid underflow
    S8 direct8x8_bias;    // -64~64, clamp the negative value to -64 to avoid underflow
    S8 me_lambda_qp_offset;
    S8 reserved4;
} GD_DSP_CMD_H264_ENCODE_S, GD_DSP_CMD_VID_ENCODE_S;

typedef struct
{
    // cmd_code: 0x00003005 GD_H264_ENCODE_FROM_MEMORY
    U32 cmd_code;

    U16 vidcap_w;
    U16 vidcap_h;

    U16 vidcap_pitch;
    U16 main_w;

    U16 main_h;
    U16 encode_w;

    U16 encode_h;
    U16 encode_x;

    U16 encode_y;
    U16 preview_w;

    U16 preview_h;

    U32 input_center_x;
    U32 input_center_y;
    U32 zoom_factor_x;
    U32 zoom_factor_y;

    U8 num_images;

    U32 h264_bits_fifo_start;
    U32 h264_info_fifo_start;

    U32 input_image_addr_Y_UV[8];    //u_long
} GD_DSP_CMD_H264_ENCODE_FROM_MEMORY_PARAM_S, GD_DSP_CMD_VID_ENCODE_FROM_MEMORY_PARAM_S;

typedef struct
{
    // cmd_code: 0x00003006 GD_H264_BITS_FIFO_UPDATE
    U32 cmd_code;

    U32 bits_output_fifo_end;
} GD_DSP_CMD_H264_ENCODE_BITS_FIFO_UPDATE_S, GD_DSP_CMD_H264_VID_ENCODE_BITS_FIFO_UPDATE_S;

typedef struct
{
    // cmd_code: 0x00003007 GD_ENCODING_STOP
    U32 cmd_code;

    U32 stop_method;
} GD_DSP_CMD_H264_ENCODE_STOP_S, GD_DSP_CMD_VID_ENCODE_STOP_S;

typedef struct
{
    // cmd_code: 0x00003008 GD_MODIFY_CMD_DLY
    U32 cmd_code;
    U32 api_proc_delay;

} GD_DSP_CMD_PROC_DELAY_S, GD_DSP_CMD_VID_PROC_DELAY_T;

typedef struct
{
    // cmd_code: 0x00004001 GD_STILL_CAPTURE
    U32 cmd_code;

    U8 output_select;
    U8 input_format;
    U8 vsync_skip;
    U8 resume;

    U32 number_frames_to_capture;

    U16 vidcap_w;
    U16 vidcap_h;

    U16 main_w;
    U16 main_h;

    U16 encode_w;
    U16 encode_h;

    U16 encode_x;
    U16 encode_y;

    U16 preview_w;
    U16 preview_h;

    U16 thumbnail_w;
    U16 thumbnail_h;

    U32 input_center_x;
    U32 input_center_y;
    U32 zoom_factor_x;
    U32 zoom_factor_y;
    U32 jpeg_bits_fifo_start;
    U32 jpeg_info_fifo_start;
    U32 sensor_readout_mode;

    U8 sensor_id;
    U8 field_format;
    U8 sensor_resolution;
    U8 sensor_pattern;

    U8 first_line_field_0;
    U8 first_line_field_1;
    U8 first_line_field_2;
    U8 first_line_field_3;

    U8 first_line_field_4;
    U8 first_line_field_5;
    U8 first_line_field_6;
    U8 first_line_field_7;

    U16 preview_w_B;
    U16 preview_h_B;

    U16 raw_cap_cntl;
    // Added by Colin chen for the High ISO mode of Still processing
    U8 still_process_mode;
    U8 yuv_proc_mode;

    U32 still_process_data_dram_addr;
    U32 raw_cap_hw_rsc_ptr;

    U8  disable_quickview_HDMI  :  1;
    U8  disable_quickview_LCD   :  1;
    // Used to indicate that we do not need to resetting vin and need to wait
    // out the vin before exiting RJPEG mode to TIMER mode
    U8  no_vin_reset_exiting    :  1;
    U8  reserved_1              :  5;
    U8  jpg_enc_cntrl;
    U16 thumbnail_active_h;
} GD_DSP_CMD_STILL_CAPTURE_S;

typedef struct
{
    // cmd_code: 0x00004002 GD_JPEG_ENCODE_RESCALE_FROM_MEMORY
    U32 cmd_code;

    U8  output_select;
    U8  input_format;
    U8  bayer_pattern;
    U8  resolution;

    U32 input_address;

    U32 input_chroma_address;

    U16 input_pitch;
    U16 input_chroma_pitch;

    U16 input_h;
    U16 input_w;

    U16 main_w;
    U16 main_h;

    U16 encode_w;
    U16 encode_h;

    U16 encode_x;
    U16 encode_y;

    U16 preview_w_A;
    U16 preview_h_A;

    U16 thumbnail_w;
    U16 thumbnail_h;

    U32 input_center_x;
    U32 input_center_y;
    U32 zoom_factor_x;
    U32 zoom_factor_y;
    U32 jpeg_bits_fifo_start;
    U32 jpeg_info_fifo_start;

    U16 preview_w_B;
    U16 preview_h_B;

    U16 cap_cntl;
/*
    #define    STILL_PROCESS_MODE_NORMAL   0
    #define    STILL_PROCESS_MODE_HIGH_ISO    1
    are defined above.
    Added by Colin chen for the High ISO mode of Still processing
*/
    U8 still_process_mode;
    U8 still_process_mode_padding;

    U32 still_process_data_dram_addr;

    U8 disable_quickview_HDMI   :  1;
    U8 disable_quickview_LCD    :  1;
    U8 no_vin_reset_exiting     :  1;   //Used to indicate that we do not need to resetting vin and need to wait
                                        //out the vin before exiting RJPEG mode to TIMER mode
    U8 reserved_1               :  5;
    U8 reserved;
    U16 thumbnail_active_h;
} GD_DSP_CMD_STILL_PROC_FROM_MEMORY_S;

typedef struct
{
    // cmd_code: 0x00004003 GD_JPEG_BITS_FIFO_UPDATE
    U32 cmd_code;

    U32 bits_fifo_end;
} GD_DSP_CMD_JPEG_BITS_FIFO_UPDATE_S;

typedef struct
{
    // cmd_code: 0x00004004 GD_FREE_RAW_YUV_PIC_BUFFER
    U32 cmd_code;

    U32 number_of_raw_pic_consumed;
    U32 raw_last_addr_consumed;
    U32 number_of_thumbnail_pic_consumed;
    U32 thumbnail_last_addr_consumed;
    U32 number_of_encode_YUV_pic_consumed;
    U32 encode_yuv_last_addr_consumed;
} GD_DSP_CMD_FREE_RAW_YUV_PICTURE_BUFFER_S;

typedef struct
{
    // cmd_code: 0x00004005 GD_JPEG_RAW_YUV_STOP
    U32 cmd_code;

} GD_DSP_CMD_JPEG_STOP_S;

typedef struct
{
    // cmd_code: 0x00004006 GD_MJPEG_ENCODE
    U32 cmd_code;

    U32 bits_fifo_next;
    U32 info_fifo_next;
    U32 start_encode_frame_no;
    U32 encode_duration;

    U8  framerate_control_M;
    U8  framerate_control_N;
    U16 reserve;
} GD_DSP_CMD_MJPEG_CAPTURE_S;

typedef struct
{
    // cmd_code: 0x00004007 GD_VID_FADE_IN_OUT
    U32 cmd_code;

    // 0: fade in start, 1: fade in stop, 2: fade out start, 3: fade out stop
    U8  cmd;
} GD_DSP_CMD_VID_FADE_IN_OUT_S;

typedef struct
{
    // cmd_code: 0x00004008 GD_MJPEG_ENCODE_WITH_H264
    U32 cmd_code;

    U32 enable;
} GD_DSP_CMD_MJPEG_CAPTURE_WITH_264_S;

typedef struct
{
    // cmd_code: 0x00004009 GD_OSD_INSERT
    U32 cmd_code;

    U32 enable;
    U32 y_osd_addr_h264;
    U32 uv_osd_addr_h264;// 420

    U16 osd_width_h264;
    U16 osd_pitch_h264;

    U16 osd_height_h264;
    U16 osd_vertical_position_h264;

    U32 y_osd_addr_mjpeg;
    U32 uv_osd_addr_mjpeg;//422

    U16 osd_width_mjpeg;
    U16 osd_pitch_mjpeg;

    U16 osd_height_mjpeg;
    U16 osd_vertical_position_mjpeg;
} GD_DSP_CMD_OSD_INSERT_S;

typedef struct
{
    // cmd_code: 0x00004010 GD_YUV422_CAPTURE
    U32 cmd_code;

    U32 num2Capture;
} GD_DSP_CMD_YUV422_CAPTURE_S;

typedef struct
{
    // cmd_code: 0x00004011 GD_SEND_CAVLC_RESULT
    U32 cmd_code;

    U32 num_of_cavlc_results:  8;
    U32 pjpg_rd_size        : 24;

    U32 cavlcBits_A[6];
    U32 cavlcBits_B[6];
    U32 cavlcBits_C[6];
    U32 cavlcBits_D[6];
    U32 totCavlcBits[6];
} GD_DSP_CMD_CAVLC_RESULT_S;

typedef struct
{
    // cmd_code: 0x00004012 GD_STILL_CAPTURE_IN_REC
    U32 cmd_code;

    U16 main_jpg_w;
    U16 main_jpg_h;
    U16 encode_w;
    U16 encode_h;
    U16 encode_x;
    U16 encode_y;
    U16 blank_period_duration;      // absolute duration, time unit: 1/60000 second.
    U8 is_use_compaction;           // if compaction is needed
    U8 is_thumbnail_ena;
} GD_DSP_CMD_STILL_CAP_IN_REC_S;

typedef struct
{
    // cmd_code: 0x00004013 GD_OSD_BLEND
    U32 cmd_code;

    U8 chan_id;
    U8 stream_id;
    U8 enable;
    U8 still_osd;

    U32 osd_addr_y;
    U32 osd_addr_uv;
    U32 alpha_addr_y;  // alpha mask must be the same size as osd, (osd_width*osd_height), value 0~0xff
    U32 alpha_addr_uv;

    U16 osd_width;
    U16 osd_pitch;

    U16 osd_height;
    U16 osd_start_x;  // (start_x, start_y)=(0,0) refers to top-left pixel of main image.

    U16 osd_start_y;
    U16 reserved_2;

    U8 blend_area2_enable;
    U8 reserved_3;
    U16 blend_area2_width;

    U16 blend_area2_pitch;
    U16 blend_area2_height;

    U16 blend_area2_start_x;
    U16 blend_area2_start_y;

    U32 blend_area2_y_addr;
    U32 blend_area2_uv_addr;
    U32 blend_area2_alpha_addr;

    U8 blend_area3_enable;
    U8 reserved_4;
    U16 blend_area3_width;

    U16 blend_area3_pitch;
    U16 blend_area3_height;

    U16 blend_area3_start_x;
    U16 blend_area3_start_y;

    U32 blend_area3_y_addr;
    U32 blend_area3_uv_addr;
    U32 blend_area3_alpha_addr;
} GD_DSP_CMD_OSD_BLEND_S;

typedef struct
{
    // cmd_code: 0x00004014 GD_INTERVAL_CAPTURE
    U32 cmd_code;

    U32 action;
    U32 num_of_frame;
} GD_DSP_CMD_INTERVAL_CAP_S;

typedef struct
{
    // cmd_code: 0x00004015 GD_STILL_CAPTURE_ADV
    U32 cmd_code;

} GD_DSP_CMD_STILL_CAPTURE_ADV_S;

/*-------------------------------------------------
*  H264/JPEG decoding mode
*  1. H264 decode                  (0x00005002)
*  2. JPEG decode                  (0x00005003)
*  3. RAW picture decode           (0x00005004)
*  4. Rescale Postprocessing       (0x00005005)
*  5. H264 decode bits FIFO update (0x00005006)
*  6. H264 playback speed          (0x00005007)
*  7. H264 trickplay               (0x00005008)
*  8. Decode stop                  (0x00005009)
*  9. Multi-scene decode           (0x00005010)
* 10. Capture video picture        (0x00005011)
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00005002 GD_H264_DECODE
    U32 cmd_code;

    U32 bits_fifo_start;
    U32 bits_fifo_end;
    U32 num_pics;
    U32 num_frame_decode;
    U32 first_frame_display;
    U32 fade_in_on;
    U32 fade_out_on;
} GD_DSP_CMD_H264_DECODE_S;

typedef struct
{
    // cmd_code: 0x00005003 GD_JPEG_DECODE
    U32 cmd_code;

    U32 bits_fifo_start;
    U32 bits_fifo_end;
    U8 main_rotation;
    U8 ycbcr_position;
    U16 reserved;
    U32 frame_duration;
    U32 num_frame_decode;
    U8 already_decoded;
    U8 sec_rotation;
} GD_DSP_CMD_JPEG_DECODE_S;

typedef struct
{
    // cmd_code: 0x00005004 GD_RAW_PICTURE_DECODE
    U32 cmd_code;

    U32 raw_pic_addr;
    U16 input_width;
    U16 input_height;
    U16 input_pitch;
    U8 rotation;
    U8 bayer_pattern;
    U8 resolution;
    U8 already_decoded;
} GD_DSP_CMD_RAW_PIC_DECODE_S;

typedef struct
{
    // cmd_code: 0x00005005 GD_RESCALE_POSTPROCESSING
    U32 cmd_code;

    U16 input_center_x;
    U16 input_center_y;

    U16 display_win_offset_x;
    U16 display_win_offset_y;

    U16 display_win_width;
    U16 display_win_height;

    U32 zoom_factor_x;

    U32 zoom_factor_y;

    U8 apply_yuv;
    U8 apply_luma;
    U8 apply_noise;
    U8 pip_enable;

    U16 pip_x_offset;
    U16 pip_y_offset;

    U16 pip_x_size;
    U16 pip_y_size;

    U16 sec_display_win_offset_x;
    U16 sec_display_win_offset_y;

    U16 sec_display_win_width;
    U16 sec_display_win_height;

    U32 sec_zoom_factor_x;

    U32 sec_zoom_factor_y;

    U32 reserved            : 31;
    U32 animated_rotation   :  1;

    U32 warp_horizontal_table_address;

    U32 warp_vertical_table_address;

    U8  grid_array_width;
    U8  grid_array_height;
    U8  horz_grid_spacing_exponent;
    U8  vert_grid_spacing_exponent;

    U8  vert_warp_grid_array_width;
    U8  vert_warp_grid_array_height;
    U8  vert_warp_horz_grid_spacing_exponent;
    U8  vert_warp_vert_grid_spacing_exponent;
} GD_DSP_CMD_RESCALE_POSTPROC_S;

typedef struct
{
    // cmd_code: 0x00005006 GD_H264_DECODE_BITS_FIFO_UPDATE
    U32 cmd_code;

    U32 bits_fifo_start;
    U32 bits_fifo_end;
    U32 num_pics;
} GD_DSP_CMD_H264_DECODE_BITS_FIFO_UPDATE_S;

typedef struct
{
    // cmd_code: 0x00005007 GD_H264_PLAYBACK_SPEED
    U32 cmd_code;

    U16 speed;
    U8 scan_mode;
    U8 direction;
} GD_DSP_CMD_H264_PLAYBACK_SPEED_S;

typedef struct
{
    // cmd_code: 0x00005008 GD_H264_TRICKPLAY
    U32 cmd_code;

    U8 mode;
} GD_DSP_CMD_H264_TRICKPLAY_S;

typedef struct
{
    // cmd_code: 0x00005009 GD_DECODE_STOP
    U32 cmd_code;

    U8 stop_flag;
} GD_DSP_CMD_H264_DECODE_STOP_S;

typedef struct
{
    S16 offset_x; //for TV
    S16 offset_y;

    U16 width;
    U16 height;

    S16 sec_offset_x; //for LCD
    S16 sec_offset_y;

    U16 sec_width;
    U16 sec_height;

    U32 source_base;

    U32 source_size     : 24;
    U32 source_type     :  4;
    U32 rotation        :  4; // for main rotation

    U32 thumbnail_id    :  8;
    U32 decode_only     :  4;
    U32 sec_rotation    :  4; // for LCD rotation
    U32 reserved        : 16;
} GD_DSP_CMD_SCENE_STRUCTURE_S;

typedef struct
{
    // cmd_code: 0x00005010 GD_MULTI_SCENE_DECODE
    U32 cmd_code;

    U32 total_scenes    :  8;
    U32 start_scene_num :  8;
    U32 scene_num       :  8;
    U32 end             :  4;
    U32 fast_mode       :  4;

    GD_DSP_CMD_SCENE_STRUCTURE_S scene[4];
} GD_DSP_CMD_MULTI_SCENE_DECODE_S;

typedef struct
{
    U32 cmd_code;
    // cmd_code: 0x00005011 GD_CAPTURE_VIDEO_PICTURE

    U32 coded_pic_base;
    U32 coded_pic_limit;
    U32 thumbnail_pic_base;
    U32 thumbnail_pic_limit;

    U16 thumbnail_width;
    U16 thumbnail_height;

    U16 thumbnail_letterbox_strip_width;
    U16 thumbnail_letterbox_strip_height;

    U8 thumbnail_letterbox_strip_y;
    U8 thumbnail_letterbox_strip_cb;
    U8 thumbnail_letterbox_strip_cr;
    U8 reserved0;

    U32 quant_matrix_addr;

    U16 target_pic_width;
    U16 target_pic_height;

    U32 pic_structure   :  8;
    U32 reserved1       : 24;

    U32 screennail_pic_base;

    U32 screennail_pic_limit;

    U16 screennail_width;
    U16 screennail_height;

    U16 screennail_letterbox_strip_width;
    U16 screennail_letterbox_strip_height;

    U8 screennail_letterbox_strip_y;
    U8 screennail_letterbox_strip_cb;
    U8 screennail_letterbox_strip_cr;
    U8 reserved2;
} GD_DSP_CMD_CAPTURE_VIDEO_PIC_S;

typedef struct
{
    // cmd_code: 0x00005012 GD_CAPTURE_STILL_PICTURE
    U32 cmd_code;

    U32 coded_pic_base; /*DRAM address to hold JPEG to encode */
    U32 coded_pic_limit;
    U32 thumbnail_pic_base; /*DRAM address to store JPEG in thumbnail form */
    U32 thumbnail_pic_limit;

    U16 thumbnail_width;
    U16 thumbnail_height;

    U16 thumbnail_letterbox_strip_width; /*will change order when it's finalized */
    U16 thumbnail_letterbox_strip_height;

    U8 thumbnail_letterbox_strip_y; /*Y value for painting letterbox */
    U8 thumbnail_letterbox_strip_cb; /*Cb value for painting letterbox */
    U8 thumbnail_letterbox_strip_cr; /*Cr value for painting letterbox */
    U8 capture_multi_scene; /* capture the multi scene picture */

    U32 quant_matrix_addr; /*DRAM address to hold quant matrix, refer to capture_video_pic_s*/
    U32 screennail_pic_base; /*DRAM address to store JPEG in screennail form */
    U32 screennail_pic_limit;

    U16 screennail_width;
    U16 screennail_height;

    U16 screennail_letterbox_strip_width; /*will change order when it's finalized */
    U16 screennail_letterbox_strip_height;

    U8 screennail_letterbox_strip_y; /*Y value for painting letterbox */
    U8 screennail_letterbox_strip_cb; /*Cb value for painting letterbox */
    U8 screennail_letterbox_strip_cr; /*Cr value for painting letterbox */
    U8 reserved0;

    U16 input_offset_x; /* offset x to crop the input picture */
    U16 input_offset_y; /* offset y to crop the input picture */

    U16 input_width; /* default=0: capture original size */
    U16 input_height; /* default=0 */

    U16 target_pic_width; /* regular capture width */
    U16 target_pic_height; /* regular capture height */
} GD_DSP_CMD_CAPTURE_STILL_PIC_S;

typedef struct
{
    // cmd_code: 0x00005013 GD_JPEG_FREEZE
    U32 cmd_code;

    U8  freeze_state;
    U8  reserved[3];
} GD_DSP_CMD_JPEG_FREEZE_S;


typedef struct
{
    // cmd_code: 0x00005014 GD_MULTI_SCENE_SETUP
    U32 cmd_code;

    U8  if_save_thumbnail; /* indicate if we need to allocate a regular thumbnail buffer*/
    U8  total_thumbnail;
    U16 saving_thumbnail_width;

    U16 saving_thumbnail_height;
    U8  if_save_large_thumbnail; /* indicate if we need to allocate a large size thumbnail buffer*/
    U8  total_large_thumbnail;

    U16 saving_large_thumbnail_width;
    U16 saving_large_thumbnail_height;

    U8  if_capture_large_size_thumbnail; /* indicate if we need to capture a large size multi scene picture */
    U8  reserved;
    U16 large_thumbnail_pic_width;  /* picture width of large size multi-scene */

    U16 large_thumbnail_pic_height; /* picture height of large size multi-scene */
    U8  visual_effect_type; /* special effect type */
    U8  reserved1;

    U16 extra_total_thumbnail; /*number of thumnails if total > 1000 */
} GD_DSP_CMD_MULTI_SCENE_SETUP_S;

typedef struct
{
    S16 input_offset_x; //for input cropping
    S16 input_offset_y;

    U16 input_width;
    U16 input_height;

    S16 main_output_offset_x; //for TV
    S16 main_output_offset_y;

    U16 main_output_width;
    U16 main_output_height;

    S16 sec_output_offset_x; //for LCD
    S16 sec_output_offset_y;

    U16 sec_output_width;
    U16 sec_output_height;

    U32 source_base;

    U32 source_size     : 24;
    U32 source_type     :  4;
    U32 rotation        :  4;

    U32 thumbnail_id    :  8;
    U32 decode_only     :  4;
    U32 luma_gain       :  8; // for luma scaling
    U32 thumbnail_type  :  2; // indicate different thumbnail size, 0: small size thumbnail 1: large size thumbnail.
    U32 reserved        : 10;
} GD_DSP_CMD_SCENE_STRUCTURE_ADV_S;

typedef struct
{
    // cmd_code: 0x00005015 GD_MULTI_SCENE_DECODE_ADV
    U32 cmd_code;

    U32 total_scenes        :  8;
    U32 start_scene_num     :  8;
    U32 scene_num           :  8;
    U32 end                 :  4;
    U32 buffer_source_only  :  2; // indicate if the scene source is TYPE3=YUV_PIC only
    U32 fast_mode           :  2;

    GD_DSP_CMD_SCENE_STRUCTURE_ADV_S    scene[3];
} GD_DSP_CMD_MULTI_SCENE_DECODE_ADV_S;

typedef struct
{
    // cmd_code: 0x00005016 GD_JPEG_DECODE_THUMBNAIL_WARP
    U32 cmd_code;

    // src and dst thumbnail id
    U8 src_thm_id;
    U8 dst_thm_id;
    U16 origin_height;

    U16 mirror_height;
    U16 reserved;

    // if draw border on src thumbnail buffer
    U8 if_draw_border;
    U8 border_y;
    U8 border_u;
    U8 border_v;

    // mirror
    U8 if_mirror_effect;
    U8 mirror_luma_gain;
    //warp related field
    U8 horz_warp_control;
    U8 vert_warp_control;

    U32 warp_horizontal_table_address;

    U32 warp_vertical_table_address;

    U8 grid_array_width;
    U8 grid_array_height;
    U8 horz_grid_spacing_exponent;
    U8 vert_grid_spacing_exponent;

    U8 vert_warp_grid_array_width;
    U8 vert_warp_grid_array_height;
    U8 vert_warp_horz_grid_spacing_exponent;
    U8 vert_warp_vert_grid_spacing_exponent;
} GD_DSP_CMD_JPEG_DECODE_THUMBNAIL_WARP_S;

typedef struct
{
    S16 input_offset_x; //for input cropping
    S16 input_offset_y;

    U16 input_width;
    U16 input_height;

    S16 main_output_offset_x; //for TV
    S16 main_output_offset_y;

    U16 main_output_width;
    U16 main_output_height;

    S16 sec_output_offset_x; //for LCD
    S16 sec_output_offset_y;

    U16 sec_output_width;
    U16 sec_output_height;

    U32 source_base;

    U32 source_size     : 24;
    U32 source_type     :  4;
    U32 main_rotation   :  4;

    U32 sec_rotation    :  4;
    U32 thumbnail_id    : 11; // to support 2048 thumbnails
    U32 decode_only     :  1;
    U32 luma_gain       :  8; // for luma scaling
    U32 thumbnail_type  :  2; // indicate different thumbnail size, 0: small size thumbnail 1: large size thumbnail.
    U32 reserved        :  6;
} GD_DSP_CMD_SCENE_STRUCTURE_ADV_2_S;

typedef struct
{
    // cmd_code: 0x00005017 GD_MULTI_SCENE_DECODE_ADV_2
    U32 cmd_code;

    U32 total_scenes        :  8;
    U32 start_scene_num     :  8;
    U32 scene_num           :  8;
    U32 end                 :  1;
    U32 update_lcd_only     :  1; //indicate if we only update lcd
    U32 buffer_source_only  :  1; // indicate if the scene source is TYPE3=YUV_PIC only
    U32 fast_mode           :  1;
    U32 reserved            :  4;

    GD_DSP_CMD_SCENE_STRUCTURE_ADV_2_S scene[3];
} GD_DSP_CMD_MULTI_SCENE_DECODE_ADV_2_S;

/*-------------------------------------------------
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00006001 GD_IPCAM_VIDEO_PREPROCESSING
    U32 cmd_code;

    U32 input_format:  8;
    U32 sensor_id   :  8;
    U32 keep_states :  8;
    U32 reserved1   :  8;

    U32 vin_frame_rate;

    U16 vidcap_w;
    U16 vidcap_h;

    U32 input_center_x;
    U32 input_center_y;
    U32 zoom_factor_x;
    U32 zoom_factor_y;
    U32 aaa_data_fifo_start;
    U32 sensor_readout_mode;

    U8 noise_filter_strength;
    U8 image_stabilize_strength;
    U8 bit_resolution;
    U8 bayer_pattern;

    U8 preview_format_A :  4;
    U8 preview_format_B :  3;
    U8 no_pipelineflush :  1;
    U8 preview_frame_rate_A;
    U8 preview_frame_rate_B;
    U8 preview_A_en     :  4; // 0: dram, 1: smem
    U8 preview_B_en     :  4; // 0: dram, 1: smem

    U16 horizontal_channel_number; // number of channels (streams) displayed on horizontal direction in preview window.
    U16 vertical_channel_number;    //number of channels (streams) displayed on vertical direction in preview window.

    U32 vdsp_int_factor     :  8;
    U32 main_out_frame_type :  1;
    U32 reserved2           : 23;
} GD_DSP_CMD_IPCAM_VIDEO_PREPROC_S;


typedef struct
{
    // cmd_code: 0x00006002 GD_IPCAM_VIDEO_CAPTURE_PREVIEW_SIZE_SETUP
    U32 cmd_code;

    U32 capture_source      :  2;
    U32 output_scan_format  :  1;
    U32 deinterlace_mode    :  2;
    U32 disabled            :  1;
    U32 Reserved1           : 26;

    U16 cap_width;
    U16 cap_height;

    U16 input_win_offset_x;
    U16 input_win_offset_y;

    U16 input_win_width;
    U16 input_win_height;
} GD_DSP_CMD_IPCAM_CAPTURE_PREVIEW_SIZE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00006003 GD_IPCAM_VIDEO_ENCODE_SIZE_SETUP
    U32 cmd_code;

    U32 capture_source  :  2;
    U32 Reserved1       : 30;

    U16 enc_x;
    U16 enc_y;

    U16 enc_width;
    U16 enc_height;
} GD_DSP_CMD_IPCAM_VIDEO_ENCODE_SIZE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00006004 GD_IPCAM_REAL_TIME_ENCODE_PARAM_SETUP
    U32 cmd_code;

    U32 enable_flags;

    U32 cbr_modify;

    U32 custom_encoder_frame_rate;

    U8 frame_rate_division_factor;
    U8 qp_min_on_I;
    U8 qp_max_on_I;
    U8 qp_min_on_P;

    U8 qp_max_on_P;
    U8 qp_min_on_B;
    U8 qp_max_on_B;
    U8 aqp;

    U8 frame_rate_multiplication_factor;
    U8 i_qp_reduce;
    U8 skip_flags;
    U8 M;

    U8 N;
    U8 p_qp_reduce;
    U8 intra_refresh_num_mb_row;
    U8 preview_A_frame_rate_divison_factor;

    U32 idr_interval;

    U32 custom_vin_frame_rate;

    U32 roi_daddr;

    S8 roi_delta[GD_NUM_PIC_TYPES][4];  /* 3 num pic types and 4 categories */

    U32 panic_div               :  8;
    U32 is_monochrome           :  1;
    U32 scene_change_detect_on  :  1;
    U32 reserved                : 22;

    U32 pic_size_control;

    U32 quant_matrix_addr;

    U16 P_IntraBiasAdd;
    U16 B_IntraBiasAdd; //tune the AQP and mode bias

    S8 intra16x16_bias;   // -64~64, clamp the negative value to -64 to avoid underflow
    S8 intra4x4_bias;     // -64~64,  clamp the negative value to -64 to avoid underflow
    S8 inter16x16_bias;   // -64~64, clamp the negative value to -64 to avoid underflow
    S8 inter8x8_bias;     // -64~64, clamp the negative value to -64 to avoid underflow

    S8 direct16x16_bias;  // -64~64, clamp the negative value to -64 to avoid underflow
    S8 direct8x8_bias;    // -64~64, clamp the negative value to -64 to avoid underflow
    S8 me_lambda_qp_offset;
    U8 reserved1;

    //S8 aqp_strength;  // 0: Automatic = existing code, 1-81: fixed strength; 1 for no AQP; -1 for inverse AQP

    //tune the deblocking parameters
    S8 alpha;     // between -6 and 6
    S8 beta;      // between -6 and 6
    U16 reserved2;
} GD_DSP_CMD_IPCAM_REAL_TIME_ENCODE_PARAM_SETUP_S;

typedef struct
{
    // cmd_code: 0x00006005 GD_IPCAM_VIDEO_FORCED_IDR
    U32 cmd_code;

    U8    force_idr;
    U8    reserved[3];
} GD_DSP_CMD_FORCE_IDR_S;

typedef struct
{
    // cmd_code: 0x00006006 GD_IPCAM_VIDEO_SYSTEM_SETUP
    U32 cmd_code;

    U16 main_max_width;
    U16 main_max_height;

    U16 preview_A_max_width;
    U16 preview_A_max_height;

    U16 preview_B_max_width;
    U16 preview_B_max_height;

    U16 preview_C_max_width;
    U16 preview_C_max_height;

    U8 stream_0_max_GOP_M;
    U8 stream_1_max_GOP_M;
    U8 stream_2_max_GOP_M;
    U8 stream_3_max_GOP_M;

    U8 stream_0_max_GOP_N;
    U8 stream_1_max_GOP_N;
    U8 stream_2_max_GOP_N;
    U8 stream_3_max_GOP_N;

    U8 stream_0_max_advanced_quality_model;
    U8 stream_1_max_advanced_quality_model;
    U8 stream_2_max_advanced_quality_model;
    U8 stream_3_max_advanced_quality_model;

    U16 stream_0_max_width;
    U16 stream_0_max_height;

    U16 stream_1_max_width;
    U16 stream_1_max_height;

    U16 stream_2_max_width;
    U16 stream_2_max_height;

    U16 stream_3_max_width;
    U16 stream_3_max_height;

    U32 MCTF_possible               :  1;
    U32 max_num_streams             :  3;
    U32 max_num_cap_sources         :  2;
    U32 use_1Gb_DRAM_config         :  1;
    U32 reserved1                   : 25;

    U16 raw_max_width;
    U16 raw_max_height;
} GD_DSP_CMD_IPCAM_VIDEO_SYSTEM_SETUP_S;

typedef struct
{
    // cmd_code: 0x00006007 GD_IPCAM_OSD_INSERT
    U32 cmd_code;

    U32 vout_id         :  1;
    U32 osd_enable      :  1;
    U32 osd_num_regions :  2;
    U32 reserved1       : 28;

    U32 osd_clut_dram_address[3];

    U32 osd_buf_dram_address[3];

    U16 osd_buf_pitch[3];
    U16 osd_win_offset_x[3];

    U16 osd_win_offset_y[3];
    U16 osd_win_w[3];

    U16 osd_win_h[3];
    U16 reserved2;
} GD_DSP_CMD_IPCAM_OSD_INSERT_S;

typedef struct
{
    // cmd_code: 0x00006008 GD_IPCAM_SET_PRIVACY_MASK
    U32 cmd_code;

    U32 enabled_flags_dram_address ;

    // use privacy mask to label a region to let MCTF to pass through it
    U8 Y;
    U8 U;
    U8 V;
} GD_DSP_CMD_IPCAM_SET_PRIVACY_MASK_S;

typedef struct
{
    // cmd_code: 0x00006009 GD_IPCAM_QP_RATIO
    U32 cmd_code;

    U8 iframe_numerator;
    U8 iframe_denominator;
    U8 bframe_numerator;
    U8 bframe_denominator;

    U8 pframe_numerator;
    U8 pframe_denominator;
    U16 reserved;
} GD_DSP_CMD_IPCAM_QP_RATIO_S;

/*-------------------------------------------------
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x00007001 GD_VOUT_MIXER_SETUP
    U32 cmd_code;

    U16 vout_id;
    U8  interlaced;
    U8  frm_rate;

    U16 act_win_width;
    U16 act_win_height;

    U8  back_ground_v;
    U8  back_ground_u;
    U8  back_ground_y;
    U8  reserved;

    U8  highlight_v;
    U8  highlight_u;
    U8  highlight_y;
    U8  highlight_thresh;
} GD_DSP_CMD_VOUT_MIXER_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007002 GD_VOUT_VIDEO_SETUP
    U32 cmd_code;

    U16 vout_id;
    U8  en;
    U8  src;

    U8  flip;
    U8  rotate;
    U8  data_src;
    U8  reserved;

    U16 win_offset_x;
    U16 win_offset_y;

    U16 win_width;
    U16 win_height;

    U32 default_img_y_addr;

    U32 default_img_uv_addr;

    U16 default_img_pitch;
    U8  default_img_repeat_field;
    U8  reserved2;
} GD_DSP_CMD_VOUT_VIDEO_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007003 GD_VOUT_DEFAULT_IMG_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 default_img_y_addr;

    U32 default_img_uv_addr;

    U16 default_img_pitch;
    U8  default_img_repeat_field;
    U8  reserved2;
} GD_DSP_CMD_VOUT_DEFAULT_IMG_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007004 GD_VOUT_OSD_SETUP
    U32 cmd_code;

    U16 vout_id;
    U8  en;
    U8  src;

    U8  flip;
    U8  rescaler_en;
    U8  premultiplied;
    U8  global_blend;

    U16 win_offset_x;
    U16 win_offset_y;

    U16 win_width;
    U16 win_height;

    U16 rescaler_input_width;
    U16 rescaler_input_height;

    U32 osd_buf_dram_addr;

    U16 osd_buf_pitch;
    U8  osd_buf_repeat_field;
    U8  osd_direct_mode;

    U16 osd_transparent_color;
    U8  osd_transparent_color_en;
    U8  reserved;

    U32 osd_buf_info_dram_addr;//24
} GD_DSP_CMD_VOUT_OSD_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007005 GD_VOUT_OSD_BUFFER_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 osd_buf_dram_addr;

    U16 osd_buf_pitch;
    U8  osd_buf_repeat_field;
    U8  reserved2;
} GD_DSP_CMD_VOUT_OSD_BUF_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007006 GD_VOUT_OSD_CLUT_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 clut_dram_addr;
} GD_DSP_CMD_VOUT_OSD_CLUT_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007007 GD_VOUT_DISPLAY_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 disp_config_dram_addr;
} GD_DSP_CMD_VOUT_DISPLAY_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007008 GD_VOUT_DVE_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 dve_config_dram_addr;
} GD_DSP_CMD_VOUT_DVE_SETUP_S;

typedef struct
{
    // cmd_code: 0x00007009 GD_VOUT_RESET
    U32 cmd_code;

    U16 vout_id;
    U8  reset_mixer;
    U8  reset_disp;
} GD_DSP_CMD_VOUT_RESET_S;

typedef struct
{
    // cmd_code: 0x0000700A GD_VOUT_DISPLAY_CSC_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 csc_type; // 0: digital; 1: analog; 2: hdmi

    U32 csc_parms[9];
} GD_DSP_CMD_VOUT_DISPLAY_CSC_SETUP_S;

typedef struct
{
    // cmd_code: 0x0000700B GD_VOUT_DIGITAL_OUTPUT_MODE_SETUP
    U32 cmd_code;

    U16 vout_id;
    U16 reserved;

    U32 output_mode;
} GD_DSP_CMD_VOUT_DIGITAL_OUTPUT_MODE_SETUP_S;

/*-------------------------------------------------
experimental commands
-------------------------------------------------*/
typedef struct
{
    // cmd_code: 0x0000f001 GD_CFA_NOISE_FILTER
    U32 cmd_code;

    U32 enable;
    U32 center_weight_red;
    U32 center_weight_green;
    U32 center_weight_blue;
    U32 thresh_red;
    U32 thresh_green;
    U32 thresh_blue;
} GD_DSP_CMD_CFA_NOISE_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000f002 GD_DIGITAL_GAIN_SATURATION
    U32 cmd_code;

    U32 level;
} GD_DSP_CMD_DIGITAL_GAIN_SATURATION_S;

typedef struct
{
    // cmd_code: 0x0000f003 GD_CHROMA_MEDIAN_FILTER
    U32 cmd_code;

    U32 enable;
} GD_DSP_CMD_CHROMA_MEDIAN_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000f004 GD_LUMA_DIRECTIONAL_FILTER
    U32 cmd_code;

    U32 strength;
} GD_DSP_CMD_LUMA_DIRECTIONAL_FILTER_S;

typedef struct
{
    // cmd_code: 0x0000f005 GD_LUMA_SHARPEN
    U32 cmd_code;

    U32 enable;
    U32 lp_coef[6];
    U32 alpha_max_pos;
    U32 alpha_max_neg;
    U32 thresh_gradient;
} GD_DSP_CMD_LUMA_SHARPEN_S;

typedef struct
{
    // cmd_code: 0x0000f006 GD_MAIN_RESAMPLER_BANDWIDTH
    U32 cmd_code;

    U8 strength_luma;
    U8 strength_chroma;
} GD_DSP_CMD_MAIN_RESAMPLER_S;

typedef struct
{
    // cmd_code: 0x0000f007 GD_CFA_RESAMPLER_BANDWIDTH
    U32 cmd_code;

    U8 strength;
} GD_DSP_CMD_CFA_RESAMPLER_BANDWIDTH_S;

typedef struct
{
    // cmd_code: 0x0000ff00 GD_DSP_DEBUG_0
    // cmd_code: 0x0000ff01 GD_DSP_DEBUG_1
    U32 cmd_code;

    U32 dram_addr;
} GD_DSP_CMD_DSP_DEBUG_S;

typedef struct
{
    // cmd_code: 0x0000ff02 GD_AAA_STATISTICS_DEBUG
    U32 cmd_code;

    U32 on      :  8;
    U32 reserved: 24;

    U32 data_fifo_base;

    U32 data_fifo_limit;

    U16 ae_awb_tile_num_col;
    U16 ae_awb_tile_num_row;

    U16 ae_awb_tile_col_start;
    U16 ae_awb_tile_row_start;

    U16 ae_awb_tile_width;
    U16 ae_awb_tile_height;

    U32 ae_awb_pix_min_value;

    U32 ae_awb_pix_max_value;

    U16 ae_awb_tile_rgb_shift;
    U16 ae_awb_tile_y_shift;

    U16 ae_awb_tile_min_max_shift;
    U16 af_tile_num_col;

    U16 af_tile_num_row;
    U16 af_tile_col_start;

    U16 af_tile_row_start;
    U16 af_tile_width;

    U16 af_tile_height;
    U16 af_tile_active_width;

    U16 af_tile_active_height;
    U16 af_tile_focus_value_shift;

    U16 af_tile_y_shift;
    U8 af_horizontal_filter1_mode;
    U8 af_horizontal_filter1_stage1_enb;

    U8 af_horizontal_filter1_stage2_enb;
    U8 af_horizontal_filter1_stage3_enb;

    U16 af_horizontal_filter1_gain[7];
    U16 af_horizontal_filter1_shift[4];
    U16 af_horizontal_filter1_bias_off;

    U16 af_vertical_filter1_thresh;
    U8 af_horizontal_filter2_mode;
    U8 af_horizontal_filter2_stage1_enb;

    U8 af_horizontal_filter2_stage2_enb;
    U8 af_horizontal_filter2_stage3_enb;
    U16 af_horizontal_filter2_gain[7];

    U16 af_horizontal_filter2_shift[4];

    U16 af_horizontal_filter2_bias_off;
    U16 af_vertical_filter2_thresh;

    U16 af_tile_fv1_horizontal_shift;
    U16 af_tile_fv1_vertical_shift;

    U16 af_tile_fv1_horizontal_weight;
    U16 af_tile_fv1_vertical_weight;

    U16 af_tile_fv2_horizontal_shift;
    U16 af_tile_fv2_vertical_shift;

    U16 af_tile_fv2_horizontal_weight;
    U16 af_tile_fv2_vertical_weight;
} GD_DSP_CMD_AAA_STATISTICS_DEBUG_S;

typedef struct
{
    // cmd_code: 0x0000ff03 GD_DSP_SPECIAL
    U32 cmd_code;

    U32 p0;
    U32 p1;
    U32 p2;
} GD_DSP_CMD_DSP_SPECIAL_S;

typedef struct
{
    // cmd_code: 0x0000ff04 GD_AAA_STATISTICS_DEBUG1
    // cmd_code: 0x0000ff05 GD_AAA_STATISTICS_DEBUG2
    U32 cmd_code;

    U32 on      :  8;
    U32 reserved: 24;

    U32 data_fifo_base;

    U32 data_fifo_limit;

    U16 ae_awb_tile_num_col;
    U16 ae_awb_tile_num_row;

    U16 ae_awb_tile_col_start;
    U16 ae_awb_tile_row_start;

    U16 ae_awb_tile_width;
    U16 ae_awb_tile_height;

    U32 ae_awb_pix_min_value;

    U32 ae_awb_pix_max_value;

    U16 ae_awb_tile_rgb_shift;
    U16 ae_awb_tile_y_shift;

    U16 ae_awb_tile_min_max_shift;
    U16 af_tile_num_col;

    U16 af_tile_num_row;
    U16 af_tile_col_start;

    U16 af_tile_row_start;
    U16 af_tile_width;

    U16 af_tile_height;
    U16 af_tile_active_width;

    U16 af_tile_active_height;
    U16 af_tile_focus_value_shift;

    U16 af_tile_y_shift;
    U8 af_horizontal_filter_mode;
    U8 af_horizontal_filter_stage1_enb;

    U8 af_horizontal_filter_stage2_enb;
    U8 af_horizontal_filter_stage3_enb;
    U16 af_horizontal_filter_gain[7];

    U16 af_horizontal_filter_shift[4];

    U16 af_horizontal_filter_bias_off;
    U16 af_vertical_filter1_thresh;

    U16 af_tile_fv_horizontal_shift;
    U16 af_tile_fv_vertical_shift;

    U16 af_tile_fv_horizontal_weight;
    U16 af_tile_fv_vertical_weight;
} GD_DSP_CMD_AAA_STATISTICS_DEBUG12_S;

typedef struct
{
    // cmd_code: 0x0000ff06 GD_BAD_PIXEL_CROP
    U32 cmd_code;

    U8 enable;
    U16 offset_horiz;
    U16 offset_vert;
} GD_DSP_CMD_BAD_PIXEL_CROP_S;

typedef struct
{
    // cmd_code: 0x0000ff07 GD_DSP_DEBUG_2
    U32 cmd_code;

    U32 dram_addr;
    U32 dram_size;
    U32 mode;
} GD_DSP_CMD_DSP_DEBUG_2_S;

typedef struct
{
    // cmd_code: 0x0000ff08 GD_DSP_DEBUG_3
    U32 cmd_code;

    U32 mode;
    U32 param1;
    U32 param2;
    U32 param3;
    U32 param4;
    U32 param5;
    U32 param6;
    U32 param7;
    U32 param8;
} GD_DSP_CMD_DSP_DEBUG_3_S;

typedef struct
{
    // cmd_code: 0x0000ff09 GD_UPDATE_IDSP_CONFIG
    U32 cmd_code;

    U16 section_id;
    U8 mode;
    U8 table_sel;
    U32 dram_addr;
    U32 data_size;
} GD_DSP_CMD_UPDATE_IDSP_CONFIG_S;

typedef struct
{
    // cmd_code: 0x0000ff0a GD_REAL_TIME_RATE_MODIFY
    U32 cmd_code;

    U32 real_time_rate_modify;
    U32 chan_id;
} GD_DSP_CMD_REAL_TIME_RATE_MODIFY_S;

typedef struct
{
    U32 cmd_code;   //???

    U32 real_time_cbr_modify;
    U32 chan_id;
} GD_DSP_CMD_REAL_TIME_CBR_MODIFY_S;


typedef union
{
    U32 cmddata[32];
    GD_DSP_CMD_INTERRUPT_SETUP_S                    interrupt_setup;
    GD_DSP_CMD_H264_ENCODE_SETUP_S                  h264_encode_setup;
    GD_DSP_CMD_JPEG_ENCODE_SETUP_S                  jpeg_encode_setup;
    GD_DSP_CMD_H264_DECODE_SETUP_S                  h264_decode_setup;
    GD_DSP_CMD_JPEG_DECODE_SETUP_S                  jpeg_decode_setup;
    GD_DSP_CMD_RESET_OPERATION_S                    reset_operation;
    GD_DSP_CMD_VIDEO_OUTPUT_RESTART_S               video_output_restart;
    GD_DSP_CMD_VIN_TIMER_MODE_S                     vin_timer_mode;
    GD_DSP_CMD_CHIP_SELECT_S                        chip_select;
    GD_DSP_CMD_HD_ECHO_SETUP_S                      hd_echo_setup;
    GD_DSP_CMD_SYSTEM_SETUP_INFO_S                  system_setup_info;
    GD_DSP_CMD_EIS_SWITCHVOUT_DURING_ENCOD_S        eis_switchvout_during_encod;
    GD_DSP_CMD_DSP_DEBUG_LEVEL_SETUP_S              dsp_debug_level_setup;
    GD_DSP_CMD_SYSTEM_PARAMETERS_SETUP_S            system_parameters_setup;
    GD_DSP_CMD_SYSTEM_IDSP_FREQ_SETUP_S             system_idsp_freq_setup;
    GD_DSP_CMD_SENSOR_INPUT_SETUP_S                 sensor_input_setup;
    GD_DSP_CMD_RGB_GAIN_ADJUST_S                    rgb_gain_adjust;
    GD_DSP_CMD_VIGNETTE_COMPENSATION_S              vignette_compensation;
    GD_DSP_CMD_AAA_STATISTICS_SETUP_S               aaa_statistics_setup;
    GD_DSP_CMD_LUMA_SHARPEN_SETUP_S                 luma_sharpen_setup;
    GD_DSP_CMD_RGB_TO_RGB_STUP_S                    rgb_to_rgb_stup;
    GD_DSP_CMD_RGB_TO_YUV_STUP_S                    rgb_to_yuv_stup;
    GD_DSP_CMD_GAMMA_CURVE_SETUP_S                  gamma_curve_setup;
    GD_DSP_CMD_NOISE_FILTER_SETUP_S                 noise_filter_setup;
    GD_DSP_CMD_BAD_PIXEL_CORRECT_SETUP_S            bad_pixel_correct_setup;
    GD_DSP_CMD_VID_FADE_IN_OUT_SETUP_S              vid_fade_in_out_setup;
    GD_DSP_CMD_CFA_DOMAIN_LEAKAGE_FILTER_S          cfa_domain_leakage_filter;
    GD_DSP_CMD_MCTF_MV_STAB_SETUP_S                 mctf_mv_stab_setup;
    GD_DSP_CMD_SET_SLOW_SHUTTER_UPSAMPLING_RATE_S   set_slow_shutter_upsampling_rate;
    GD_DSP_CMD_SENSOR_CAP_REPEAT_S                  sensor_cap_repeat;
    GD_DSP_CMD_MCTF_GMV_SETUP_S                     mctf_gmv_setup;
    GD_DSP_CMD_DIS_ALGO_PARAMS_S                    dis_algo_params;
    GD_DSP_CMD_VIN_CAP_WIN_S                        vin_cap_win;
    GD_DSP_CMD_AMPLIFIER_LINEAR_S                   amplifier_linear;
    GD_DSP_CMD_PIXEL_SHUFFLE_S                      pixel_shuffle;
    GD_DSP_CMD_BLACK_LEVEL_CORRECTTION_S            black_level_correcttion;
    GD_DSP_CMD_BLACK_LEVEL_STATE_TABLE_S            black_level_state_table;
    GD_DSP_CMD_BLACK_LEVEL_DETECT_WIN_S             black_level_detect_win;
    GD_DSP_CMD_FIXED_PATTERN_NOISE_CORRECT_S        fixed_pattern_noise_correct;
    GD_DSP_CMD_CFA_NOISE_FILTER_INFO_S              cfa_noise_filter_info;
    GD_DSP_CMD_DIGITAL_GAIN_LEVEL_S                 digital_gain_level;
    GD_DSP_CMD_LOCAL_EXPOSURE_S                     local_exposure;
    GD_DSP_CMD_DEMOASIC_FILTER_S                    demoasic_filter;
    GD_DSP_CMD_RGB_NOISE_FILTER_S                   rgb_noise_filter;
    GD_DSP_CMD_COLOR_CORRECTION_S                   color_correction;
    GD_DSP_CMD_CHROMA_MEDIAN_FILTER_INFO_S          chroma_median_filter_info;
    GD_DSP_CMD_CHROMA_SCALE_S                       chroma_scale;
    GD_DSP_CMD_LUMA_SHARPENING_S                    luma_sharpening;
    GD_DSP_CMD_AAA_STATISTICS_SETUP12_S             aaat_satistics_setup12;
    GD_DSP_CMD_AAA_PSEUDO_Y_S                       aaa_pseudo_y;
    GD_DSP_CMD_AAA_HISTOGRAM_S                      aaa_histogram;
    GD_DSP_CMD_RAW_COMPRESSION_S                    raw_compression;
    GD_DSP_CMD_RAW_DECOMPRESSION_S                  raw_decompression;
    GD_DSP_CMD_ROLLING_SHUTTER_COMPENSATION_S       rolling_shutter_compensation;
    GD_DSP_CMD_ZOOM_FACTOR_S                        zoom_factor;
    GD_DSP_CMD_AAA_STATISTICS_SETUP3_S              aaa_statistics_setup3;
    GD_DSP_CMD_VIDEO_PREVIEW_S                      video_preview;
    GD_DSP_CMD_ANTI_ALIASING_FILTER_S               anti_aliasing_filter;
    GD_DSP_CMD_FPN_CALIBRATION_S                    fpn_calibration;
    GD_DSP_CMD_BLACK_LEVEL_GLOBAL_OFFSET_S          black_level_global_offset;
    GD_DSP_CMD_RGB_DIRECTIONAL_FILTER_S             rgb_directional_filter;
    GD_DSP_CMD_HDR_MIXER_S                          hdr_mixer;
    GD_DSP_CMD_LUMA_SHARPENING_LINEARIZATION_S      luma_sharpening_linearization;
    GD_DSP_CMD_LUMA_SHARPENING_FIR_CONFIG_S         luma_sharpening_fir_config;
    GD_DSP_CMD_LUMA_SHARPENING_LNL_S                luma_sharpening_lnl;
    GD_DSP_CMD_LUMA_SHARPENING_TONE_CONTROL_S       luma_sharpening_tone_control;
    GD_DSP_CMD_MULTI_STREAM_PREVIEW_S               multi_stream_preview;
    GD_DSP_CMD_ENA_SECOND_STREAM_S                  ena_second_stream;
    GD_DSP_CMD_SET_ALPHA_CHANNEL_S                  set_alpha_channel;
    GD_DSP_CMD_MODIFY_FRAME_BUFFER_S                modify_frame_buffer;
    GD_DSP_CMD_SET_ATIVE_WIN_CTR_OFS_S              set_ative_win_ctr_ofs;
    GD_DSP_CMD_SET_WARP_CONTROL_S                   set_warp_control;
    GD_DSP_CMD_EARLY_WB_GAIN_S                      early_wb_gain;
    GD_DSP_CMD_LUMA_SHARPENING_EDGE_CONTROL_S       luma_sharpening_edge_control;
    GD_DSP_CMD_LUMA_SHARPENING_BLEND_CONTROL_S      luma_sharpening_blend_control;
    GD_DSP_CMD_LUMA_SHARPENING_LEVEL_CONTROL_S      luma_sharpening_level_control;
    GD_DSP_CMD_LUMA_SHARPENING_MISC_CONTROL_S       luma_sharpening_misc_control;
    GD_DSP_CMD_AAA_EARLY_WB_GAIN_S                  aaa_early_wb_gain;
    GD_DSP_CMD_VIDEO_PREPROC_S                      video_preproc;
    GD_DSP_CMD_FAST_AAA_CAPTURE_S                   fast_aaa_capture;
    GD_DSP_CMD_H264_ENCODE_S                        h264_encode;
    GD_DSP_CMD_H264_ENCODE_FROM_MEMORY_PARAM_S      h264_encode_from_memory_param;
    GD_DSP_CMD_H264_ENCODE_BITS_FIFO_UPDATE_S       h264_encode_bits_fifo_update;
    GD_DSP_CMD_H264_ENCODE_STOP_S                   h264_encode_stop;
    GD_DSP_CMD_PROC_DELAY_S                         proc_delay;
    GD_DSP_CMD_STILL_CAPTURE_S                      still_capture;
    GD_DSP_CMD_STILL_PROC_FROM_MEMORY_S             still_proc_from_memory;
    GD_DSP_CMD_JPEG_BITS_FIFO_UPDATE_S              jpeg_bits_fifo_update;
    GD_DSP_CMD_FREE_RAW_YUV_PICTURE_BUFFER_S        free_raw_yuv_picture_buffer;
    GD_DSP_CMD_JPEG_STOP_S                          jpeg_stop;
    GD_DSP_CMD_MJPEG_CAPTURE_S                      mjpeg_capture;
    GD_DSP_CMD_VID_FADE_IN_OUT_S                    vid_fade_in_out;
    GD_DSP_CMD_MJPEG_CAPTURE_WITH_264_S             mjpeg_capture_with_264;
    GD_DSP_CMD_OSD_INSERT_S                         osd_insert;
    GD_DSP_CMD_YUV422_CAPTURE_S                     yuv422_capture;
    GD_DSP_CMD_CAVLC_RESULT_S                       cavlc_result;
    GD_DSP_CMD_STILL_CAP_IN_REC_S                   still_cap_in_rec;
    GD_DSP_CMD_OSD_BLEND_S                          osd_blend;
    GD_DSP_CMD_INTERVAL_CAP_S                       interval_cap;
    GD_DSP_CMD_STILL_CAPTURE_ADV_S                  still_capture_adv;
    GD_DSP_CMD_H264_DECODE_S                        h264_decode;
    GD_DSP_CMD_JPEG_DECODE_S                        jpeg_decode;
    GD_DSP_CMD_RAW_PIC_DECODE_S                     raw_pic_decode;
    GD_DSP_CMD_RESCALE_POSTPROC_S                   rescale_postproc;
    GD_DSP_CMD_H264_DECODE_BITS_FIFO_UPDATE_S       h264_decode_bits_fifo_update;
    GD_DSP_CMD_H264_PLAYBACK_SPEED_S                h264_playback_speed;
    GD_DSP_CMD_H264_TRICKPLAY_S                     h264_trickplay;
    GD_DSP_CMD_H264_DECODE_STOP_S                   h264_decode_stop;
    GD_DSP_CMD_MULTI_SCENE_DECODE_S                 multi_scene_decode;
    GD_DSP_CMD_CAPTURE_VIDEO_PIC_S                  capture_video_pic;
    GD_DSP_CMD_CAPTURE_STILL_PIC_S                  capture_still_pic;
    GD_DSP_CMD_JPEG_FREEZE_S                        jpeg_freeze;
    GD_DSP_CMD_MULTI_SCENE_SETUP_S                  multi_scene_setup;
    GD_DSP_CMD_MULTI_SCENE_DECODE_ADV_S             multi_scene_decode_adv;
    GD_DSP_CMD_JPEG_DECODE_THUMBNAIL_WARP_S         jpeg_decode_thumbnail_warp;
    GD_DSP_CMD_MULTI_SCENE_DECODE_ADV_2_S           multi_scene_decode_adv_2;
    GD_DSP_CMD_IPCAM_VIDEO_PREPROC_S                ipcam_video_preproc;
    GD_DSP_CMD_IPCAM_CAPTURE_PREVIEW_SIZE_SETUP_S   ipcam_capture_preview_size_setup;
    GD_DSP_CMD_IPCAM_VIDEO_ENCODE_SIZE_SETUP_S      ipcam_video_encode_size_setup;
    GD_DSP_CMD_IPCAM_REAL_TIME_ENCODE_PARAM_SETUP_S ipcam_real_time_encode_param_setup;
    GD_DSP_CMD_FORCE_IDR_S                          force_idr;
    GD_DSP_CMD_IPCAM_VIDEO_SYSTEM_SETUP_S           ipcam_video_system_setup;
    GD_DSP_CMD_IPCAM_OSD_INSERT_S                   ipcam_osd_insert;
    GD_DSP_CMD_IPCAM_SET_PRIVACY_MASK_S             ipcam_set_privacy_mask;
    GD_DSP_CMD_IPCAM_QP_RATIO_S                     ipcam_qp_ratio;
    GD_DSP_CMD_VOUT_MIXER_SETUP_S                   vout_mixer_setup;
    GD_DSP_CMD_VOUT_VIDEO_SETUP_S                   vout_video_setup;
    GD_DSP_CMD_VOUT_DEFAULT_IMG_SETUP_S             vout_default_img_setup;
    GD_DSP_CMD_VOUT_OSD_SETUP_S                     vout_osd_setup;
    GD_DSP_CMD_VOUT_OSD_BUF_SETUP_S                 vout_osd_buf_setup;
    GD_DSP_CMD_VOUT_OSD_CLUT_SETUP_S                vout_osd_clut_setup;
    GD_DSP_CMD_VOUT_DISPLAY_SETUP_S                 vout_display_setup;
    GD_DSP_CMD_VOUT_DVE_SETUP_S                     vout_dve_setup;
    GD_DSP_CMD_VOUT_RESET_S                         vout_reset;
    GD_DSP_CMD_VOUT_DISPLAY_CSC_SETUP_S             vout_display_csc_setup;
    GD_DSP_CMD_VOUT_DIGITAL_OUTPUT_MODE_SETUP_S     vout_digital_output_mode_setup;
    GD_DSP_CMD_CFA_NOISE_FILTER_S                   cfa_noise_filter;
    GD_DSP_CMD_DIGITAL_GAIN_SATURATION_S            digital_gain_saturation;
    GD_DSP_CMD_CHROMA_MEDIAN_FILTER_S               chroma_median_filter;
    GD_DSP_CMD_LUMA_DIRECTIONAL_FILTER_S            luma_directional_filter;
    GD_DSP_CMD_LUMA_SHARPEN_S                       luma_sharpen;
    GD_DSP_CMD_MAIN_RESAMPLER_S                     main_resampler;
    GD_DSP_CMD_CFA_RESAMPLER_BANDWIDTH_S            cfa_resampler_bandwidth;
    GD_DSP_CMD_DSP_DEBUG_S                          dsp_debug;
    GD_DSP_CMD_AAA_STATISTICS_DEBUG_S               aaa_statistics_debug;
    GD_DSP_CMD_DSP_SPECIAL_S                        dsp_special;
    GD_DSP_CMD_AAA_STATISTICS_DEBUG12_S             aaa_statistics_debug12;
    GD_DSP_CMD_BAD_PIXEL_CROP_S                     bad_pixel_crop;
    GD_DSP_CMD_DSP_DEBUG_2_S                        dsp_debug_2;
    GD_DSP_CMD_DSP_DEBUG_3_S                        dsp_debug_3;
    GD_DSP_CMD_UPDATE_IDSP_CONFIG_S                 update_idsp_config;
    GD_DSP_CMD_REAL_TIME_RATE_MODIFY_S              real_time_rate_modify;
    GD_DSP_CMD_REAL_TIME_CBR_MODIFY_S               real_time_cbr_modify;
}GD_DSP_CMD_S;
//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

U32 GD_DSP_CMD_GET_CODE_CR_PC_T0_ADDR(void);


#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#endif /* _GD_IDSP_CMD_H_ */

