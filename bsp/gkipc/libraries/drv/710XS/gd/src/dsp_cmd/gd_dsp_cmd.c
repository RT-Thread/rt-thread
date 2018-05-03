/*!
*****************************************************************************
** \file        gd_lib/GK7101/src/dsp_cmd/dsp_reg_priv.c
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
#include <stdio.h>
#include <string.h>

#include "gd_dsp_cmd.h"

//*****************************************************************************
//*****************************************************************************
//** Local Defines
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local structures
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Global Data
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** Local Data
//*****************************************************************************
//*****************************************************************************
static GD_IDSP_CMD_REG_FILTER_DATA_S section_1_VIN[]=
{
    {"REG_VIN_CONTROL",                                                                  0,        0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_INPUT_CONFIG",                                                             1,        0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_INPUT_MODE",                                                               1,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_BIT_RESOLUTION",                                                           1,        5,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_INPUT_ORDER",                                                              1,        7,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_NON_MIPI_INPUT",                                                           1,        13, 1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_VERTICAL_START",                                                           17,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_HORIZONTAL_START",                                                         18,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_VERTICAL_END",                                                             19,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_HORIZONTAL_END",                                                           20,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_CFG_REG1",                                                            26,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_CFG_REG2",                                                            27,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_BDPHY_REG1",                                                          28,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_BDPHY_REG2",                                                          29,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_VIRTUAL_CHANNEL_SELECT",                                              26,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_VIRTUAL_CHANNEL_MASK",                                                26,       2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_ENABLE",                                                              26,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_HS_SETTLE_CTL",                                                       26,       5,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_DATA_TYPE_SELECT",                                                    27,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_DATA_TYPE_MASK",                                                      27,       8,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VIN_MIPI_DATA_SWAP",                                                           27,       14, 1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_1_AML[]=
{
    {"REG_AMP_LINEAR_ENABLE",                                                            0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AMP_LINEAR_BLACK_LEVEL_OFFSET",                                                16,       0,  14, 2,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AMP_LINEAR_EXPONENT_TABLE",                                                    32,       0,  2,  16,   GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AMP_LINEAR_LOOKUP_TABLE",                                                      64,       0,  12, 708,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_1_RLC[]=
{
    {"REG_LOSSY_COMPRESSOR_ENABLE",                                                      0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOSSY_COMPRESSOR_MANTISSA_BITS",                                               0,        2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOSSY_COMPRESSOR_BLOCK_SIZE",                                                  0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_BFN[]=
{
    {"REG_BLACK_LEVEL_OPTIONS",                                                          0,        0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_READ_STATIC_BAD_PIXEL_STREAM",                                     0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_GLOBAL_OFFSET_EE",                                                 1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_GLOBAL_OFFSET_EO",                                                 2,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_GLOBAL_OFFSET_OE",                                                 3,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_GLOBAL_OFFSET_OO",                                                 4,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_ACTIVE_VRT_START",                                                 5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_ACTIVE_VRT_END",                                                   6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_ACTIVE_HOR_START",                                                 7,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_ACTIVE_HOR_END",                                                   8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_ACTIVE_PLUS_DUMMY_COL_COUNT",                                      9,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_DUMMY_ROWS_TOP",                                                   10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_DUMMY_COLS_LEFT",                                                  11,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_DUMMY_COLS_RIGHT",                                                 12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_LOSSY_ENABLE",                                                     13,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_LOSSY_MANTISSA_BITS",                                              13,       2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_LOSSY_BLOCK_SIZE",                                                 13,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_LOSSY_WIDTH",                                                      14,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BLACK_LEVEL_LOSSY_HEIGHT",                                                     15,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_BPC[]=
{
    {"REG_CFA_BAD_PIXEL_CORRECTION_MODE",                                                0,        1,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_ENABLE",                                                    0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ENABLE",                                                      0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_MODE",                                         0,        5,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_ENABLE",                                       0,        5,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BAYER_PATTERN_OF_BAD_PIXEL_CORRECTION_GRGB_MISMATCH",                          1,        0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_CHKR_THRESH",                                               2,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_CHKR_SHIFT",                                                3,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_ALPHA_RR",                                                  4,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_ALPHA_RB",                                                  5,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_ALPHA_BB",                                                  6,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_ALPHA_BR",                                                  7,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LEAKAGE_FILTER_SATURATION_LEVEL",                                          8,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_CENTER_WEIGHT_RED",                                       9,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_CENTER_WEIGHT_GREEN",                                     10,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_CENTER_WEIGHT_BLUE",                                      11,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K0_RED",                                           12,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K1_RED",                                           13,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K0_GREEN",                                         14,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K1_GREEN",                                         15,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K0_BLUE",                                          16,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_K1_BLUE",                                          17,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K0_CLOSE",                                         18,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_DIR_THRESH_GRAD",                                             19,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_CENTER_WEIGHT_RED",                                       20,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_CENTER_WEIGHT_GREEN",                                     21,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_CENTER_WEIGHT_BLUE",                                      22,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K0_RED",                                           23,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K1_RED",                                           24,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K0_GREEN",                                         25,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K1_GREEN",                                         26,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K0_BLUE",                                          27,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_NOISE_FILTER_ISO_THRESH_K1_BLUE",                                          28,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LOSSY_ENABLE",                                                             29,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LOSSY_MANTISSA_BITS",                                                      29,       2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_LOSSY_BLOCK_SIZE",                                                         29,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT",                                 30,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT0",                                30,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT1",                                30,       3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT2",                                30,       6,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT3",                                30,       9,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT4",                                30,       12, 3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_SHIFT5",                                31,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_HOT",                                   32,       0,  8,  384,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_BAD_PIXEL_DYNAMIC_DETECTION_THRESH_DARK",                                  416,      0,  8,  384,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_PSC[]=
{
    {"REG_CFA_PRESCALE_HORIZONTAL_ENABLE",                                               0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_ENABLE",                                                 0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_COEFF_SHIFT",                                          0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_COEFF_SHIFT",                                            0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_OUTPUT_WIDTH",                                         1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_PHASE_INCREMENT",                                      2,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_INITIAL_PHASE_FIRST_COLOR",                            3,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_INITIAL_PHASE_FIRST_COLOR_FRAC",                       4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_INITIAL_PHASE_SECOND_COLOR",                           5,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_INITIAL_PHASE_SECOND_COLOR_FRAC",                      6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_OUTPUT_HEIGHT",                                          7,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_PHASE_INCREMENT",                                        8,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_INITIAL_PHASE_FIRST_COLOR",                              9,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_INITIAL_PHASE_SECOND_COLOR",                             10,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BAYER_PATTERN_OF_PRESCALE_2D_FILTER",                                          11,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_A_RED",                                                      12,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_B_RED",                                                      17,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_C_RED",                                                      20,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_A_GREEN",                                                    26,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_B_GREEN",                                                    31,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_C_GREEN",                                                    34,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_A_BLUE",                                                     40,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_B_BLUE",                                                     45,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_LBUF_C_BLUE",                                                     48,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_LOSSY_COMPRESSOR_ENABLE",                                59,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_LOSSY_COMPRESSOR_MANTISSA_BITS",                         59,       2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_LOSSY_COMPRESSOR_BLOCK_SIZE",                            59,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_HORIZONTAL_COEFF",                                                64,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CFA_PRESCALE_VERTICAL_COEFF",                                                  112,      0,  8,  64,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_AAC[]=
{
    {"REG_AAA_STATS_AWB_CFA_ENABLE",                                                     0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_NUM_COLUMNS",                                           0,        1,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_NUM_ROWS",                                              0,        6,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_COLUMN_START",                                          1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_ROW_START",                                             2,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_WIDTH",                                                 3,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_HEIGHT",                                                4,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_ACTIVE_WIDTH",                                          5,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_ACTIVE_HEIGHT",                                         6,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_MIN_THRESH",                                            7,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_MAX_THRESH",                                            8,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_RGB_SHIFT",                                             9,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AWB_CFA_TILE_MIN_MAX_SHIFT",                                         9,        5,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_ENABLE",                                                      10,       0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_NUM_COLUMNS",                                            10,       1,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_NUM_ROWS",                                               10,       5,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_COLUMN_START",                                           11,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_ROW_START",                                              12,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_WIDTH",                                                  13,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_HEIGHT",                                                 14,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_CFA_TILE_LIN_Y_SHIFT",                                            15,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_ENABLE",                                                      16,       0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_NUM_COLUMNS",                                            16,       1,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_NUM_ROWS",                                               16,       4,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_COLUMN_START",                                           17,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_ROW_START",                                              18,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_WIDTH",                                                  19,       0,  10, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_HEIGHT",                                                 20,       0,  10, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_ACTIVE_WIDTH",                                           21,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_ACTIVE_HEIGHT",                                          22,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_MODE",                                     23,       0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_STAGE1_ENABLE",                            23,       1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_STAGE2_ENABLE",                            23,       2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_STAGE3_ENABLE",                            23,       3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_MODE",                                     23,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_STAGE1_ENABLE",                            23,       5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_STAGE2_ENABLE",                            23,       6,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_STAGE3_ENABLE",                            23,       7,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_GAIN",                                     24,       0,  10, 7,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_SHIFT",                                    31,       0,  4,  4,    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_BIAS_OFFSET",                              32,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER1_THRESH",                                   33,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_GAIN",                                     34,       0,  10, 7,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_SHIFT",                                    41,       0,  4,  4,    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_BIAS_OFFSET",                              42,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_HORIZONTAL_FILTER2_THRESH",                                   43,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_FV1_HORIZONTAL_SHIFT",                                   44,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_FV2_HORIZONTAL_SHIFT",                                   44,       5,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TILE_Y_SHIFT",                                                44,       10, 5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_PSEUDO_Y_MODE",                                                   45,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_PSEUDO_Y_MODE",                                                   45,       2,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_AF_PSEUDO_Y_PIXEL_WEIGHT",                                        45,       4,  2,  4,    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_AF_PSEUDO_Y_SUM_SHIFT",                                           45,       12, 2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BAYER_PATTERN_OF_AAA_CFA",                                                     46,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_HISTOGRAM_CFA_MODE",                                                 51,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_HISTOGRAM_CFA_AE_TILE_MASK",                                         52,       0,  12, 8,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_MULTIPLIER_RED",                                                60,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_MULTIPLIER_BLUE",                                               60,       8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_MULTIPLIER_GREEN_EVEN_ROW",                                     61,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_MULTIPLIER_GREEN_ODD_ROW",                                      61,       8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_SHIFT_RED",                                                     62,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_SHIFT_GREEN_EVEN_ROW",                                          62,       4,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_SHIFT_GREEN_ODD_ROW",                                           62,       8,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_SHIFT_BLUE",                                                    62,       12, 4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_MULTIPLIER_RED",                                             63,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_MULTIPLIER_BLUE",                                            63,       8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_MULTIPLIER_GREEN_EVEN_ROW",                                  64,       0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_MULTIPLIER_GREEN_ODD_ROW",                                   64,       8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_SHIFT_RED",                                                  65,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_SHIFT_GREEN_EVEN_ROW",                                       65,       4,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_SHIFT_GREEN_ODD_ROW",                                        65,       8,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_SHIFT_BLUE",                                                 65,       12, 4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_AF_ENABLE",                                                  66,       0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_AE_ENABLE",                                                  66,       1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_GAIN_WB_HISTOGRAM_Y_ENABLE",                                         66,       2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_TILE_MIN_THRESH",                                                 67,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_TILE_MAX_THRESH",                                                 68,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_CFA_TONE_CURVE_LOOKUP",                                           96,       0,  16, 32,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_DGN[]=
{
    {"REG_BAYER_PATTERN_OF_DIGITAL_GAIN",                                                0,        0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_MULTIPLIER_RED",                                                  1,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_MULTIPLIER_BLUE",                                                 1,        8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_MULTIPLIER_GREEN_EVEN_ROW",                                       2,        0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_MULTIPLIER_GREEN_ODD_ROW",                                        2,        8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SHIFT_RED",                                                       3,        0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SHIFT_GREEN_EVEN_ROW",                                            3,        4,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SHIFT_GREEN_ODD_ROW",                                             3,        8,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SHIFT_BLUE",                                                      3,        12, 4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SATURATION_LEVEL_RED",                                            4,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SATURATION_LEVEL_GREEN_EVEN_ROW",                                 5,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SATURATION_LEVEL_GREEN_ODD_ROW",                                  6,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_SATURATION_LEVEL_BLUE",                                           7,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_ENABLE",                                            8,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_GAIN_SHIFT",                                        8,        1,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_INITIAL_PHASE_HORIZONTAL",                          9,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_INITIAL_PHASE_HORIZONTAL_FRAC",                     10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_INITIAL_PHASE_VERTICAL",                            11,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_INITIAL_PHASE_VERTICAL_FRAC",                       12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_PHASE_INCREMENT_HORIZONTAL",                        13,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_PHASE_INCREMENT_VERTICAL",                          14,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_BLACK_LEVEL_OFFSET_RED",                                          15,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_BLACK_LEVEL_OFFSET_GREEN",                                        16,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_BLACK_LEVEL_OFFSET_BLUE",                                         17,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_GAIN_RED",                                          32,       0,  10, 1089, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_GAIN_GREEN_EVEN_ROW",                               1121,     0,  10, 1089, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_GAIN_GREEN_ODD_ROW",                                2210,     0,  10, 1089, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DIGITAL_GAIN_VIGNETTE_COMP_GAIN_BLUE",                                         3299,     0,  10, 1089, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_LEA[]=
{
    {"REG_LOCAL_EXPOSURE_ENABLE",                                                        0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BAYER_PATTERN_OF_LOCAL_EXPOSURE_ADJUSTMENT",                                   1,        0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LUMA_SUM_SHIFT",                                                2,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LUMA_WEIGHT_RED",                                               3,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LUMA_WEIGHT_GREEN",                                             4,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LUMA_WEIGHT_BLUE",                                              5,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_RADIUS",                                                        6,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_PFPMODE",                                                       7,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_A_RED",                                                    8,        0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_B_RED",                                                    14,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_C_RED",                                                    17,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_A_GREEN",                                                  23,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_B_GREEN",                                                  29,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_C_GREEN",                                                  32,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_A_BLUE",                                                   38,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_B_BLUE",                                                   44,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LBUF_C_BLUE",                                                   47,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_OFFSET",                                                        54,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_LUMA_OFFSET",                                                   55,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_BLACK_LEVEL_OFFSET_RED",                                        56,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_BLACK_LEVEL_OFFSET_GREEN",                                      57,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_BLACK_LEVEL_OFFSET_BLUE",                                       58,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LOCAL_EXPOSURE_GAIN_CURVE",                                                    64,       0,  12, 256,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_DMS[]=
{
    {"REG_DEMOSAIC_ENABLE",                                                              1,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_BAYER_PATTERN_OF_DEMOSAIC",                                                    2,        0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_THRESH_GRAD_CLIPPING",                                                3,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_THRESH_GRAD_NOISE",                                                   4,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_THRESH_ACTIVITY",                                                     5,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_THRESH_ACTIVITY_DIFF",                                                6,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_A_RED",                                                     7,        0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_B_RED",                                                     13,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_C_RED",                                                     16,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_A_GREEN",                                                   22,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_B_GREEN",                                                   28,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFB_LBUF_C_GREEN",                                                   31,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_A_BLUE",                                                    37,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_B_BLUE",                                                    43,       0,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_DEMOSAIC_BUFA_LBUF_C_BLUE",                                                    46,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_CLC[]=
{
    {"REG_COLOR_COR_ENABLE",                                                             0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_OUT_LOOKUP_BYPASS",                                                  0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_NO_INTERPOLATION",                                                   0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_UV_CENTERED",                                                        0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_YUV_MODE",                                                           0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_YUV422",                                                             0,        5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_PREMUL_RED",                                                         (1*2),    0,  17, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_PREMUL_GREEN",                                                       (2*2),    0,  17, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_PREMUL_BLUE",                                                        (3*2),    0,  17, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_OUT_LOOKUP_RED",                                                     (32*2),   0,  10, 256,  GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_OUT_LOOKUP_GREEN",                                                   (32*2),   10, 10, 256,  GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_OUT_LOOKUP_BLUE",                                                    (32*2),   20, 10, 256,  GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_IN_LOOKUP_RED",                                                      (288*2),  0,  12, 176,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_IN_LOOKUP_GREEN",                                                    (480*2),  0,  12, 176,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_IN_LOOKUP_BLUE",                                                     (672*2),  0,  12, 176,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_COLOR_COR_3D",                                                                 (864*2),  0,  10, 4096, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_AAA[]=
{
    {"REG_AAA_STATS_AE_Y_ENABLE",                                                        0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_NUM_COLUMNS",                                              0,        1,  4,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_NUM_ROWS",                                                 0,        5,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_COLUMN_START",                                             1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_ROW_START",                                                2,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_WIDTH",                                                    3,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_HEIGHT",                                                   4,        0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AE_Y_TILE_Y_SHIFT",                                                  5,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_ENABLE",                                                        6,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_NUM_COLUMNS",                                              6,        1,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_NUM_ROWS",                                                 6,        4,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_COLUMN_START",                                             7,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_ROW_START",                                                8,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_WIDTH",                                                    9,        0,  10, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_HEIGHT",                                                   10,       0,  10, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_ACTIVE_WIDTH",                                             11,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_ACTIVE_HEIGHT",                                            12,       0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_MODE",                                       13,       0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_STAGE1_ENABLE",                              13,       1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_STAGE2_ENABLE",                              13,       2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_STAGE3_ENABLE",                              13,       3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_MODE",                                       13,       4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_STAGE1_ENABLE",                              13,       5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_STAGE2_ENABLE",                              13,       6,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_STAGE3_ENABLE",                              13,       7,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_GAIN",                                       14,       0,  10, 7,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_SHIFT",                                      21,       0,  4,  4,    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_BIAS_OFFSET",                                22,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER1_THRESH",                                     23,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_VERTICAL_FILTER1_THRESH",                                       24,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV1_HORIZONTAL_SHIFT",                                     25,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV1_HORIZONTAL_WEIGHT",                                    25,       5,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV1_VERTICAL_SHIFT",                                       26,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV1_VERTICAL_WEIGHT",                                      26,       5,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_GAIN",                                       27,       0,  10, 7,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_SHIFT",                                      34,       0,  4,  4,    GD_IDSP_CMD_SECTION_DATA_BIT_UNIT     , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_BIAS_OFFSET",                                35,       0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_HORIZONTAL_FILTER2_THRESH",                                     36,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_VERTICAL_FILTER2_THRESH",                                       37,       0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV2_HORIZONTAL_SHIFT",                                     38,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV2_HORIZONTAL_WEIGHT",                                    38,       5,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV2_VERTICAL_SHIFT",                                       39,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_FV2_VERTICAL_WEIGHT",                                      39,       5,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_AF_Y_TILE_Y_SHIFT",                                                  40,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_HISTOGRAM_MODE",                                                     41,       0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_STATS_HISTOGRAM_AE_TILE_MASK",                                             42,       0,  12, 8,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_RYC[]=
{
    {"REG_CHROMA_SCALE_GAIN_CURVE",                                                      0,        0,  12, 128,  GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_RGB_TO_YUV_MATRIX",                                                            128,      0,  13, 9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_RGB_TO_YUV_Y_OFFSET",                                                          137,      0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_RGB_TO_YUV_U_OFFSET",                                                          138,      0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_RGB_TO_YUV_V_OFFSET",                                                          139,      0,  9,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_SCALE_WEIGHTS_U",                                                       140,      0,  9,  3,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_SCALE_WEIGHTS_V",                                                       143,      0,  9,  3,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_SCALE_ENABLE",                                                          146,      0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_SCALE_MAKE_LEGAL",                                                      146,      1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_RGB_TO_YUV_MODE",                                                              146,      2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_LSH[]=
{
    {"REG_SHPA_ENABLE",                                                                  0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_LUMA_SHARPENING_CHROMA_MEDIAN_ENABLE",                                         0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_AAA_ENABLE",                                                                   0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_ENABLE",                                                            0,        3,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_ENABLE",                                                            0,        5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING_CNTL",                                                             0,        6,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ADD_IN_LOW_PASS",                                                         0,        8,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_YUV",                                                                     0,        9,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_ENABLE",                                                       0,        11, 3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_THRESH_GRAD0",                                                            (1*2),    0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_THRESH_GRAD1",                                                            (2*2),    0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_SHIFT",                                                              (4*2),    0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_SMOOTH_SHIFT",                                                            (5*2),    0,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_THRESH",                                                             (6*2),    0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_THRESH_MUL",                                                         (6*2),    11, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_WIDE_WEIGHT",                                                             (6*2),    19, 4,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_NARROW_WEIGHT",                                                           (6*2),    23, 4,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_MAX_CHANGE_DOWN",                                                         (7*2),    0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_MAX_CHANGE_UP",                                                           (7*2),    8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ABS",                                                                     (7*2),    16, 1,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CLIP_LOW",                                                                (8*2),    0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CLIP_HIGH",                                                               (8*2),    8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_CLIP_LOW",                                                            (9*2),    0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_CLIP_HIGH",                                                           (9*2),    13, 13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_CLIP_LOW2",                                                           (10*2),   0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_CLIP_HIGH2",                                                          (10*2),   13, 13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_THRESH0",                                                      (11*2),   0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_THRESH1",                                                      (11*2),   11, 11, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_THRESH_MUL",                                                   (12*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_MUL_ISO",                                                           (12*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_THRESH_INVERSE_MANTISSA",                                      (13*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_DIR_INVERSE_MANTISSA",                                              (13*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_ISO_INVERSE_MANTISSA",                                              (13*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_EDGE_THRESH_INVERSE_SHIFT",                                         (14*2),   0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_DIR_INVERSE_SHIFT",                                                 (14*2),   5,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_ISO_INVERSE_SHIFT",                                                 (14*2),   10, 5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_THRESH_DIR0",                                                       (15*2),   0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_THRESH_DIR1",                                                       (15*2),   11, 11, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_THRESH_ISO0",                                                       (16*2),   0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_BLEND_THRESH_ISO1",                                                       (16*2),   11, 11, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_AREA",                             (17*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_AREA",                             (17*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_AREA",                                           (17*2),   6,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_AREA",                                           (17*2),   9,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_AREA",                                                 (17*2),   12, 3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_AREA",                                                 (17*2),   15, 3,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_AREA",                                                 (17*2),   18, 3,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_AREA",                                    (17*2),   21, 3,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_AREA",                                    (17*2),   24, 3,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_AREA",                                    (17*2),   27, 3,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_AREA",                                         (18*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_SEC_INPUT_ENABLE",                                                        (18*2),   3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_SEC_INPUT_SIGNED",                                                        (18*2),   4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_OUTPUT_SIGNED",                                                           (18*2),   5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_SEC_INPUT_SHIFT",                                                         (18*2),   6,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_OUTPUT_SHIFT",                                                            (18*2),   9,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_LOW",                              (19*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_HIGH",                             (19*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_LOW0",                             (20*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_HIGH0",                            (20*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_DELTA_LOW",                        (21*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_DELTA_HIGH",                       (21*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_LOW_VAL",                          (22*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_HIGH_VAL",                         (22*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_ISO_GRADIENT_ALPHA_LVL_CNTL_BASE_VAL",                         (22*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_LOW",                              (23*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_HIGH",                             (23*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_LOW0",                             (24*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_HIGH0",                            (24*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_DELTA_LOW",                        (25*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_DELTA_HIGH",                       (25*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_LOW_VAL",                          (26*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_HIGH_VAL",                         (26*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_EDGE_BLEND_DIR_GRADIENT_ALPHA_LVL_CNTL_BASE_VAL",                         (26*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_LOW",                                            (27*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_HIGH",                                           (27*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_LOW0",                                           (28*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_HIGH0",                                          (28*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_DELTA_LOW",                                      (29*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_DELTA_HIGH",                                     (29*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_LVL_CNTL_CLIP_LOW",                                                       (29*2),   6,  13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_LVL_CNTL_CLIP_HIGH",                                                      (29*2),   19, 13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_LOW_VAL",                                        (30*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_HIGH_VAL",                                       (30*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1_OUT_SCALE_LVL_CNTL_BASE_VAL",                                       (30*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_LOW",                                            (31*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_HIGH",                                           (31*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_LOW0",                                           (32*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_HIGH0",                                          (32*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_DELTA_LOW",                                      (33*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_DELTA_HIGH",                                     (33*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_LVL_CNTL_CLIP_LOW2",                                                      (33*2),   6,  13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_LVL_CNTL_CLIP_HIGH2",                                                     (33*2),   19, 13, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_LOW_VAL",                                        (34*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_HIGH_VAL",                                       (34*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2_OUT_SCALE_LVL_CNTL_BASE_VAL",                                       (34*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_LOW",                                                  (35*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_HIGH",                                                 (35*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_LOW0",                                                 (36*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_HIGH0",                                                (36*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_DELTA_LOW",                                            (37*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_DELTA_HIGH",                                           (37*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_LOW_VAL",                                              (38*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_HIGH_VAL",                                             (38*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MUL_LVL_CNTL_BASE_VAL",                                             (38*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_LOW",                                                  (39*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_HIGH",                                                 (39*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_LOW0",                                                 (40*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_HIGH0",                                                (40*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_DELTA_LOW",                                            (41*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_DELTA_HIGH",                                           (41*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_LOW_VAL",                                              (42*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_HIGH_VAL",                                             (42*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MIN_LVL_CNTL_BASE_VAL",                                             (42*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_LOW",                                                  (43*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_HIGH",                                                 (43*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_LOW0",                                                 (44*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_HIGH0",                                                (44*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_DELTA_LOW",                                            (45*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_DELTA_HIGH",                                           (45*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_LOW_VAL",                                              (46*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_HIGH_VAL",                                             (46*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHA_MAX_LVL_CNTL_BASE_VAL",                                             (46*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_LOW",                                     (47*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_HIGH",                                    (47*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_LOW0",                                    (48*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_HIGH0",                                   (48*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_DELTA_LOW",                               (49*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_DELTA_HIGH",                              (49*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_LOW_VAL",                                 (50*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_HIGH_VAL",                                (50*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MUL_LVL_CNTL_BASE_VAL",                                (50*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_LOW",                                     (51*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_HIGH",                                    (51*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_LOW0",                                    (52*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_HIGH0",                                   (52*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_DELTA_LOW",                               (53*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_DELTA_HIGH",                              (53*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_LOW_VAL",                                 (54*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_HIGH_VAL",                                (54*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MIN_LVL_CNTL_BASE_VAL",                                (54*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_LOW",                                     (55*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_HIGH",                                    (55*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_LOW0",                                    (56*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_HIGH0",                                   (56*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_DELTA_LOW",                               (57*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_DELTA_HIGH",                              (57*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_LOW_VAL",                                 (58*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_HIGH_VAL",                                (58*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_MULTIPLIER_MAX_LVL_CNTL_BASE_VAL",                                (58*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_LOW",                                          (59*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_HIGH",                                         (59*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_LOW0",                                         (60*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_HIGH0",                                        (60*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_DELTA_LOW",                                    (61*2),   0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_DELTA_HIGH",                                   (61*2),   3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_LOW_VAL",                                      (62*2),   0,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_HIGH_VAL",                                     (62*2),   8,  8,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING1_INDEX_MUL_LVL_CNTL_BASE_VAL",                                     (62*2),   16, 8,  1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_1",                                                                   (64*2),   0,  8,  256,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_FIR_2",                                                                   (128*2),  0,  8,  256,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_CORING_TABLE",                                                            (192*2),  0,  20, 64,   GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_SHPA_ALPHAS",                                                                  (256*2),  0,  8,  512,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_CMN[]=
{
    {"REG_CHROMA_MEDIAN_ENABLE",                                                         0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_422_INPUT",                                                      0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_SAT_THRESH0_CB",                                                 1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_SAT_THRESH1_CB",                                                 2,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_SAT_THRESH0_CR",                                                 3,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_SAT_THRESH1_CR",                                                 4,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_ACT_THRESH0_CB",                                                 5,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_ACT_THRESH1_CB",                                                 6,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_ACT_THRESH0_CR",                                                 7,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_ACT_THRESH1_CR",                                                 8,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K0_CB",                                                          9,        0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K0_CR",                                                          12,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K1_CB",                                                          15,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K1_CR",                                                          18,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K2_CB",                                                          21,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K2_CR",                                                          24,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K3_CB",                                                          27,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_MEDIAN_K3_CR",                                                          30,       0,  5,  9,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_CDS[]=
{
    {"REG_CHROMA_DOWNSAMPLING_HORIZONTAL_ENABLE",                                        0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_CHROMA_DOWNSAMPLING_VERTICAL_ENABLE",                                          0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_LRS[]=
{
    {"REG_MAIN_RESAMPLE_LUMA_VERTICAL_ENABLE",                                           0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_COEFF_VERTICAL_SHIFT",                                      0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_HORIZONTAL_ENABLE",                                         0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_COEFF_HORIZONTAL_SHIFT",                                    0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_FORCE_4TAP_VERTICAL_ENABLE",                                0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_HORIZONTAL_LUMA_ENABLE",                               0,        5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_OUTPUT_WIDTH",                                              1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_HORIZONTAL",                                2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                           3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_INITIAL_PHASE_HORIZONTAL",                                  4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_INITIAL_PHASE_HORIZONTAL_FRAC",                             5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_OUTPUT_HEIGHT",                                             6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_VERTICAL",                                  7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_VERTICAL_FRAC",                             8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_INITIAL_PHASE_VERTICAL",                                    9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_INITIAL_PHASE_VERTICAL_FRAC",                               10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_INITIAL_PHASE_SKEW_HORIZONTAL",                             12,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_SKEW_HORIZONTAL",                           13,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_SKEW_HORIZONTAL_MSB",                       14,       0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_SKEW_VERTICAL",                             15,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_PHASE_INCREMENT_SKEW_VERTICAL_MSB",                         16,       0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_GRID_ARRAY_WIDTH",                                     17,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_GRID_ARRAY_HEIGHT",                                    18,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_HORIZONTAL_PASS_HORIZONTAL_GRID_SPACING_EXPONENT",     19,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_HORIZONTAL_PASS_VERTICAL_GRID_SPACING_EXPONENT",       19,       3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_GRID_VECTOR_FORMAT",                                   20,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_COEFF_HORIZONTAL",                                          32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_COEFF_VERTICAL",                                            80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_LUMA_WARP_GRID_HORIZONTAL_COEFF",                                128,      0,  16, 1536, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_CRS[]=
{
    {"REG_MAIN_RESAMPLE_CHROMA_VERTICAL_ENABLE",                                         0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_COEFF_VERTICAL_SHIFT",                                    0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_HORIZONTAL_ENABLE",                                       0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_COEFF_HORIZONTAL_SHIFT",                                  0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_FORCE_4TAP_VERTICAL_ENABLE",                              0,        4,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_HORIZONTAL_CHROMA_ENABLE",                           0,        5,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_CHROMA_FORMAT",                                      0,        6,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_HORIZONTAL_CHROMA_OFFSET_ENABLE",                    0,        8,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_VERTICAL_CHROMA_OFFSET_ENABLE",                      0,        9,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_OUTPUT_WIDTH",                                            1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_HORIZONTAL",                              2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                         3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_INITIAL_PHASE_HORIZONTAL",                                4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_INITIAL_PHASE_HORIZONTAL_FRAC",                           5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_OUTPUT_HEIGHT",                                           6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_VERTICAL",                                7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_VERTICAL_FRAC",                           8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_INITIAL_PHASE_VERTICAL",                                  9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_INITIAL_PHASE_VERTICAL_FRAC",                             10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_INITIAL_PHASE_SKEW_HORIZONTAL",                           12,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_SKEW_HORIZONTAL",                         13,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_SKEW_HORIZONTAL_MSB",                     14,       0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_SKEW_VERTICAL",                           15,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_PHASE_INCREMENT_SKEW_VERTICAL_MSB",                       16,       0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_GRID_ARRAY_WIDTH",                                   17,       0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_GRID_ARRAY_HEIGHT",                                  18,       0,  6,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_HORIZONTAL_PASS_HORIZONTAL_GRID_SPACING_EXPONENT",   19,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_HORIZONTAL_PASS_VERTICAL_GRID_SPACING_EXPONENT",     19,       3,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_WARP_GRID_VECTOR_FORMAT",                                 20,       0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_COEFF_HORIZONTAL",                                        32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_MAIN_RESAMPLE_CHROMA_COEFF_VERTICAL",                                          80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_2_MRS[]=
{
    {"REG_ME1_DOWNSAMPLE_ENABLE",                                                        0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_DOWNSAMPLE_OUTPUT_HEIGHT",                                                 1,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_DOWNSAMPLE_PHASE_INCREMENT_VERTICAL",                                      2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_DOWNSAMPLE_PHASE_INCREMENT_VERTICAL_FRAC",                                 3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_DOWNSAMPLE_INITIAL_PHASE_VERTICAL",                                        4,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_DOWNSAMPLE_INITIAL_PHASE_VERTICAL_FRAC",                                   5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_3_VWP[]=
{
    {"REG_WARP_VERTICAL_LUMA_ENABLE",                                                    0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_ENABLE",                                                  0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_SMEM_MODE",                                                               0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_PASS_HORIZONTAL_GRID_SPACING_EXPONENT",                          0,        2,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_PASS_VERTICAL_GRID_SPACING_EXPONENT",                            0,        5,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_CHROMA_FORMAT",                                                           0,        8,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_POLYPHASE_LUMA_COEFF_SHIFT",                                     0,        9,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_POLYPHASE_CHROMA_COEFF_SHIFT",                                   0,        10, 1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_GRID_VECTOR_FORMAT",                                                      0,        11, 2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_HORIZONTAL_CHROMA_OFFSET_ENABLE",                                         0,        13, 1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_OFFSET_ENABLE",                                           0,        14, 1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_PASS_INPUT_WIDTH",                                               1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_PASS_INPUT_HEIGHT",                                              2,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_PASS_OUTPUT_HEIGHT",                                             3,        0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_LUMA_DMA_SIZE",                                                  4,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_LUMA_POLYPHASE_INITIAL_PHASE",                                   5,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_LUMA_POLYPHASE_INCREMENT",                                       6,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_POLYPHASE_INCREMENT",                                     6,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_LUMA_POLYPHASE_INCREMENT_SKEW_FRAC",                             7,        0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_LUMA_POLYPHASE_INCREMENT_SKEW",                                  8,        0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_DMA_SIZE",                                                9,        0,  5,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_POLYPHASE_INITIAL_PHASE",                                 10,       0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_POLYPHASE_INCREMENT_SKEW_FRAC",                           11,       0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_CHROMA_POLYPHASE_INCREMENT_SKEW",                                12,       0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_WAIT_LINES",                                                              14,       0,  15, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_POLYPHASE_LUMA_COEFF",                                           16,       0,  8,  64,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_VERTICAL_POLYPHASE_CHROMA_COEFF",                                         48,       0,  8,  64,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_WARP_GRID_VERTICAL_COEFF",                                                     80,       0,  16, 1536, GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_4_MVU[]=
{
    {"REG_ME1_UPSAMPLE_ENABLE",                                                          0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_INPUT_WIDTH",                                                     1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_INPUT_HEIGHT",                                                    2,        0,  10, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_OUTPUT_HEIGHT",                                                   3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_TILE_HEIGHT",                                                              4,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_INITIAL_PHASE_VERTICAL",                                          5,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_PHASE_INCREMENT_VERTICAL",                                        6,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_PHASE_INCREMENT_SKEW_VERTICAL",                                   7,        0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_ME1_UPSAMPLE_PHASE_INCREMENT_SKEW_VERTICAL_MSB",                               8,        0,  7,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_5_LPA[]=
{
    {"REG_PREVIEW_A_POLYPHASE_LUMA_VERTICAL_ENABLE",                                     0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_COEFF_VERTICAL_SHIFT",                                0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_HORIZONTAL_ENABLE",                                   0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_COEFF_HORIZONTAL_SHIFT",                              0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_OUTPUT_WIDTH",                                        1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL",                          2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                     3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL",                            4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_FRAC",                       5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN",                       4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                  5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_OUTPUT_HEIGHT",                                       6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL",                            7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL_FRAC",                       8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL",                              9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL_FRAC",                         10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD",                        12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                   13,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_COEFF_HORIZONTAL",                                    32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_LUMA_COEFF_VERTICAL",                                      80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_5_CPA[]=
{
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_VERTICAL_ENABLE",                                   0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_COEFF_VERTICAL_SHIFT",                              0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_HORIZONTAL_ENABLE",                                 0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_COEFF_HORIZONTAL_SHIFT",                            0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_OUTPUT_WIDTH",                                      1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL",                        2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                   3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL",                          4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_FRAC",                     5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN",                     4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_OUTPUT_HEIGHT",                                     6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL",                          7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL_FRAC",                     8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL",                            9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL_FRAC",                       10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD",                      12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                 13,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_COEFF_HORIZONTAL",                                  32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_POLYPHASE_CHROMA_COEFF_VERTICAL",                                    80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_5_LDA[]=
{
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_LUMA_HORIZONTAL_ENABLE",                         0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_LUMA_VERTICAL_ENABLE",                           0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_LUMA_COEFF_HORIZONTAL",                          1,        0,  8,  3,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_LUMA_COEFF_VERTICAL",                            3,        0,  8,  2,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_5_CDA[]=
{
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_CHROMA_HORIZONTAL_ENABLE",                       0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_CHROMA_VERTICAL_ENABLE",                         0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_A_EXTRA_2X_DOWNSAMPLE_CHROMA_COEFF",                                   1,        0,  8,  2,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_6_LPB[]=
{
    {"REG_PREVIEW_B_POLYPHASE_LUMA_VERTICAL_ENABLE",                                     0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_COEFF_VERTICAL_SHIFT",                                0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_HORIZONTAL_ENABLE",                                   0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_COEFF_HORIZONTAL_SHIFT",                              0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_OUTPUT_WIDTH",                                        1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL",                          2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                     3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL",                            4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_FRAC",                       5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN",                       4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                  5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_OUTPUT_HEIGHT",                                       6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL",                            7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL_FRAC",                       8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL",                              9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL_FRAC",                         10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD",                        11,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                   12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_COEFF_HORIZONTAL",                                    32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_LUMA_COEFF_VERTICAL",                                      80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_6_CPB[]=
{
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_VERTICAL_ENABLE",                                   0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_COEFF_VERTICAL_SHIFT",                              0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_HORIZONTAL_ENABLE",                                 0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_COEFF_HORIZONTAL_SHIFT",                            0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_OUTPUT_WIDTH",                                      1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL",                        2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                   3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL",                          4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_FRAC",                     5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN",                     4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_OUTPUT_HEIGHT",                                     6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL",                          7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL_FRAC",                     8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL",                            9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL_FRAC",                       10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD",                      11,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                 12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_COEFF_HORIZONTAL",                                  32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_B_POLYPHASE_CHROMA_COEFF_VERTICAL",                                    80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_7_LPC[]=
{
    {"REG_PREVIEW_C_POLYPHASE_LUMA_VERTICAL_ENABLE",                                     0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_COEFF_VERTICAL_SHIFT",                                0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_HORIZONTAL_ENABLE",                                   0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_COEFF_HORIZONTAL_SHIFT",                              0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_OUTPUT_WIDTH",                                        1,        0,  12, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL",                          2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                     3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL",                            4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_FRAC",                       5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN",                       4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                  5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_OUTPUT_HEIGHT",                                       6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL",                            7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_PHASE_INCREMENT_VERTICAL_FRAC",                       8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL",                              9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_VERTICAL_FRAC",                         10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD",                        11,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                   12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_COEFF_HORIZONTAL",                                    32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_LUMA_COEFF_VERTICAL",                                      80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_7_CPC[]=
{
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_VERTICAL_ENABLE",                                   0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_COEFF_VERTICAL_SHIFT",                              0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_HORIZONTAL_ENABLE",                                 0,        2,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_COEFF_HORIZONTAL_SHIFT",                            0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_OUTPUT_WIDTH",                                      1,        0,  11, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL",                        2,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_PHASE_INCREMENT_HORIZONTAL_FRAC",                   3,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL",                          4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_FRAC",                     5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN",                     4,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_EVEN_FRAC",                5,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_OUTPUT_HEIGHT",                                     6,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL",                          7,        0,  3,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_PHASE_INCREMENT_VERTICAL_FRAC",                     8,        0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL",                            9,        0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_VERTICAL_FRAC",                       10,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD",                      11,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_INITIAL_PHASE_HORIZONTAL_ODD_FRAC",                 12,       0,  13, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_COEFF_HORIZONTAL",                                  32,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_POLYPHASE_CHROMA_COEFF_VERTICAL",                                    80,       0,  8,  63,   GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_7_LDC[]=
{
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_LUMA_HORIZONTAL_ENABLE",                         0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_LUMA_VERTICAL_ENABLE",                           0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_LUMA_COEFF_HORIZONTAL",                          1,        0,  8,  3,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_LUMA_COEFF_VERTICAL",                            3,        0,  8,  2,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_7_CDC[]=
{
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_CHROMA_HORIZONTAL_ENABLE",                       0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_CHROMA_VERTICAL_ENABLE",                         0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_PREVIEW_C_EXTRA_2X_DOWNSAMPLE_CHROMA_COEFF",                                   1,        0,  8,  2,    GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_7_MRC[]=
{
    {"REG_MEC_DOWNSAMPLE_ENABLE",                                                        0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_REG_FILTER_DATA_S section_8_OSD[]=
{
    {"REG_VOUT_OSD_RESCALER_ENABLE",                                                     0,        0,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_COEFF_VERTICAL_SHIFT",                                       0,        1,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_COEFF_HORIZONTAL_SHIFT",                                     0,        3,  1,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_COEFF_INPUT_SELECT",                                         0,        4,  2,  1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_OUTPUT_WIDTH",                                               (1*2),    0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_PHASE_INCREMENT_HORIZONTAL",                                 (2*2),    0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_INITIAL_PHASE_HORIZONTAL",                                   (3*2),    0,  28, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_INITIAL_PHASE_HORIZONTAL_ODD",                               (4*2),    0,  28, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_OUTPUT_HEIGHT",                                              (5*2),    0,  14, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_PHASE_INCREMENT_VERTICAL",                                   (6*2),    0,  16, 1,    GD_IDSP_CMD_SECTION_DATA_WORD_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_INITIAL_PHASE_VERTICAL",                                     (7*2),    0,  28, 1,    GD_IDSP_CMD_SECTION_DATA_DOUBLE_UNIT  , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_COEFF_HORIZONTAL",                                           (8*2),    0,  8,  128,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
    {"REG_VOUT_OSD_RESCALER_COEFF_VERTICAL",                                             (40*2),   0,  8,  128,  GD_IDSP_CMD_SECTION_DATA_BYTE_UNIT    , GD_IDSP_CMD_FILTER_VIDEO_IN  },
};

static GD_IDSP_CMD_SEC_REG_FILTER_S section_reg_filter[]=
{
    {"SEC1", "VIN", 0,         sizeof(section_1_VIN)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_1_VIN},
    {"SEC1", "AML", (128*1),   sizeof(section_1_AML)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_1_AML},
    {"SEC1", "RLC", (128*14),  sizeof(section_1_RLC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_1_RLC},
    {"SEC2", "BFN", (128*15),  sizeof(section_2_BFN)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_BFN},
    {"SEC2", "BPC", (128*16),  sizeof(section_2_BPC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_BPC},
    {"SEC2", "PSC", (128*29),  sizeof(section_2_PSC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_PSC},
    {"SEC2", "AAC", (128*32),  sizeof(section_2_AAC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_AAC},
    {"SEC2", "DGN", (128*34),  sizeof(section_2_DGN)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_DGN},
    {"SEC2", "LEA", (128*103), sizeof(section_2_LEA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_LEA},
    {"SEC2", "DMS", (128*108), sizeof(section_2_DMS)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_DMS},
    {"SEC2", "CLC", (128*109), sizeof(section_2_CLC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_CLC},
    {"SEC2", "AAA", (128*264), sizeof(section_2_AAA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_AAA},
    {"SEC2", "RYC", (128*265), sizeof(section_2_RYC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_RYC},
    {"SEC2", "LSH", (128*268), sizeof(section_2_LSH)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_LSH},
    {"SEC2", "CMN", (128*280), sizeof(section_2_CMN)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_CMN},
    {"SEC2", "CDS", (128*281), sizeof(section_2_CDS)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_CDS},
    {"SEC2", "LRS", (128*282), sizeof(section_2_LRS)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_LRS},
    {"SEC2", "CRS", (128*308), sizeof(section_2_CRS)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_CRS},
    {"SEC2", "MRS", (128*310), sizeof(section_2_MRS)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_2_MRS},
    {"SEC3", "VWP", (128*311), sizeof(section_3_VWP)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_3_VWP},
    {"SEC4", "MVU", (128*337), sizeof(section_4_MVU)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_4_MVU},
    {"SEC5", "LPA", (128*338), sizeof(section_5_LPA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_5_LPA},
    {"SEC5", "CPA", (128*340), sizeof(section_5_CPA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_5_CPA},//RTL
    {"SEC5", "LDA", (128*342), sizeof(section_5_LDA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_5_LDA},//RTL
    {"SEC5", "CDA", (128*343), sizeof(section_5_CDA)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_5_CDA},
    {"SEC6", "LPB", (128*344), sizeof(section_6_LPB)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_6_LPB},
    {"SEC6", "CPB", (128*346), sizeof(section_6_CPB)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_6_CPB},
    {"SEC7", "LPC", (128*348), sizeof(section_7_LPC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_7_LPC},
    {"SEC7", "CPC", (128*350), sizeof(section_7_CPC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_7_CPC},//RTL
    {"SEC7", "LDC", (128*352), sizeof(section_7_LDC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_7_LDC},//RTL
    {"SEC7", "CDC", (128*353), sizeof(section_7_CDC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_7_CDC},
    {"SEC7", "MRC", (128*354), sizeof(section_7_MRC)/sizeof(GD_IDSP_CMD_REG_FILTER_DATA_S), section_7_MRC},
    //{"END",  "END", (128*355), 0, NULL},
};

static GD_IDSP_CMD_REG_FILTER_DEF_S  reg_filter_def[]=
{
    {GD_IDSP_CMD_REG_FILTER_DEF_OFFSET,         "OFFSET"},
    {GD_IDSP_CMD_REG_FILTER_DEF_START_BIT,      "BIT"},
    {GD_IDSP_CMD_REG_FILTER_DEF_NUM_BITS,       "BITS"},
    {GD_IDSP_CMD_REG_FILTER_DEF_NUM_REGISTERS,  "REGISTERS"},
    {GD_IDSP_CMD_REG_FILTER_DEF_DATA_UNIT,      "UNIT"},
    {GD_IDSP_CMD_REG_FILTER_DEF_FILTER,         "FILTER"},
};


//*****************************************************************************
//*****************************************************************************
//** Local Functions Declaration
//*****************************************************************************
//*****************************************************************************



//*****************************************************************************
//*****************************************************************************
//** API Functions
//*****************************************************************************
//*****************************************************************************

U32 GD_DSP_CMD_GET_CODE_CR_PC_T0_ADDR(void)
{
    U32 value = GH_DEBUG_CODE_get_CODE_CR_PC_T0_ADDR();
    return value;
}

//*****************************************************************************
//*****************************************************************************
//** Local Functions
//*****************************************************************************
//*****************************************************************************



