/*
 * Copyright (C) 2018 ETH Zurich and University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Copyright (C) 2018 GreenWaves Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __HIMAX_H__
#define __HIMAX_H__

/*
 *  HIMAX camera macros
 */
// Register address
// Read only registers
#define         MODEL_ID_H          0x0000
#define         MODEL_ID_L          0x0001
#define         FRAME_COUNT         0x0005
#define         PIXEL_ORDER         0x0006
// R&W registers
// Sensor mode control
#define         MODE_SELECT         0x0100
#define         IMG_ORIENTATION     0x0101
#define         SW_RESET            0x0103
#define         GRP_PARAM_HOLD      0x0104
// Sensor exposure gain control
#define         INTEGRATION_H       0x0202
#define         INTEGRATION_L       0x0203
#define         ANALOG_GAIN         0x0205
#define         DIGITAL_GAIN_H      0x020E
#define         DIGITAL_GAIN_L      0x020F
// Frame timing control
#define         FRAME_LEN_LINES_H   0x0340
#define         FRAME_LEN_LINES_L   0x0341
#define         LINE_LEN_PCK_H      0x0342
#define         LINE_LEN_PCK_L      0x0343
// Binning mode control
#define         READOUT_X           0x0383
#define         READOUT_Y           0x0387
#define         BINNING_MODE        0x0390
// Test pattern control
#define         TEST_PATTERN_MODE   0x0601
// Black level control
#define         BLC_CFG             0x1000
#define         BLC_TGT             0x1003
#define         BLI_EN              0x1006
#define         BLC2_TGT            0x1007
//  Sensor reserved
#define         DPC_CTRL            0x1008
#define         SINGLE_THR_HOT      0x100B
#define         SINGLE_THR_COLD     0x100C
// VSYNC,HSYNC and pixel shift register
#define         VSYNC_HSYNC_PIXEL_SHIFT_EN  0x1012
// Automatic exposure gain control
#define         AE_CTRL             0x2100
#define         AE_TARGET_MEAN      0x2101
#define         AE_MIN_MEAN         0x2102
#define         CONVERGE_IN_TH      0x2103
#define         CONVERGE_OUT_TH     0x2104
#define         MAX_INTG_H          0x2105
#define         MAX_INTG_L          0x2106
#define         MIN_INTG            0x2107
#define         MAX_AGAIN_FULL      0x2108
#define         MAX_AGAIN_BIN2      0x2109
#define         MIN_AGAIN           0x210A
#define         MAX_DGAIN           0x210B
#define         MIN_DGAIN           0x210C
#define         DAMPING_FACTOR      0x210D
#define         FS_CTRL             0x210E
#define         FS_60HZ_H           0x210F
#define         FS_60HZ_L           0x2110
#define         FS_50HZ_H           0x2111
#define         FS_50HZ_L           0x2112
#define         FS_HYST_TH          0x2113
// Motion detection control
#define         MD_CTRL             0x2150
#define         I2C_CLEAR           0x2153
#define         WMEAN_DIFF_TH_H     0x2155
#define         WMEAN_DIFF_TH_M     0x2156
#define         WMEAN_DIFF_TH_L     0x2157
#define         MD_THH              0x2158
#define         MD_THM1             0x2159
#define         MD_THM2             0x215A
#define         MD_THL              0x215B
//  Sensor timing control
#define         QVGA_WIN_EN         0x3010
#define         SIX_BIT_MODE_EN     0x3011
#define         PMU_AUTOSLEEP_FRAMECNT  0x3020
#define         ADVANCE_VSYNC       0x3022
#define         ADVANCE_HSYNC       0x3023
#define         EARLY_GAIN          0x3035
//  IO and clock control
#define         BIT_CONTROL         0x3059
#define         OSC_CLK_DIV         0x3060
#define         ANA_Register_11     0x3061
#define         IO_DRIVE_STR        0x3062
#define         IO_DRIVE_STR2       0x3063
#define         ANA_Register_14     0x3064
#define         OUTPUT_PIN_STATUS_CONTROL   0x3065
#define         ANA_Register_17     0x3067
#define         PCLK_POLARITY       0x3068

/*
 * Useful value of Himax registers
 */
#define         HIMAX_RESET         0x01
#define         Pclk_rising_edge    0x00
#define         Pclk_falling_edge   0x01

#define         BYPASS_BIGEND       5

enum{
    HIMAX_Standby = 0x0,
    HIMAX_Streaming = 0x1,        // I2C triggered streaming enable
    HIMAX_Streaming2 = 0x3,       // Output N frames
    HIMAX_Streaming3 = 0x5        // Hardware Trigger
};

#endif
