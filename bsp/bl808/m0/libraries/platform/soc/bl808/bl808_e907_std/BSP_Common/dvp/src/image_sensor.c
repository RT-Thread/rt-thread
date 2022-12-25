/**
  ******************************************************************************
  * @file    image_sensor.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "image_sensor.h"
#include "bflb_platform.h"

/** @addtogroup  Image_Sensor_Driver
 *  @{
 */

/** @addtogroup  IMAGE_SENSOR
 *  @{
 */

/** @defgroup  IMAGE_SENSOR_Private_Macros
 *  @{
 */
#define BFLB_EXTPSRAM_CLK_GPIO                 GLB_GPIO_PIN_27
#define BFLB_EXTPSRAM_CS_GPIO                  GLB_GPIO_PIN_17
#define BFLB_EXTPSRAM_DATA0_GPIO               GLB_GPIO_PIN_28
#define BFLB_EXTPSRAM_DATA1_GPIO               GLB_GPIO_PIN_24
#define BFLB_EXTPSRAM_DATA2_GPIO               GLB_GPIO_PIN_23
#define BFLB_EXTPSRAM_DATA3_GPIO               GLB_GPIO_PIN_26
#if(IMAGE_SENSOR_USE == IMAGE_SENSOR_BF2013)
#define I2C_CAMERA_ADDR   0x6E
#define SENSOR_ID_REG_MSB 0xFC
#define SENSOR_ID_REG_LSB 0xFD
#define SENSOR_ID_VAL_MSB 0x37
#define SENSOR_ID_VAL_LSB 0x03
#elif(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC0308)
#define I2C_CAMERA_ADDR   0x21
#define SENSOR_ID_REG     0x00
#define SENSOR_ID_VAL     0x9B
#elif(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC2053)
#define I2C_CAMERA_ADDR   0x37
#define SENSOR_ID_REG_MSB 0xF0
#define SENSOR_ID_REG_LSB 0xF1
#define SENSOR_ID_VAL_MSB 0x20
#define SENSOR_ID_VAL_LSB 0x53
#endif

/*@} end of group IMAGE_SENSOR_Private_Macros */

/** @defgroup  IMAGE_SENSOR_Private_Types
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Private_Types */

/** @defgroup  IMAGE_SENSOR_Private_Variables
 *  @{
 */
static const uint8_t sensorRegList[][2] =
{
#if(IMAGE_SENSOR_USE == IMAGE_SENSOR_BF2013)
    {0x12,0x80},
    {0x67,0x00},
    {0x68,0x00},
    //{0xb9, 0x80},//use Test pattern
    //{0x69,0x20},
    {0x3a,0x02},
    {0x09,0x01},
    {0x15,0x02},
    {0x12,0x00},
    {0x1e,0x00},
    {0x13,0x00},
    {0x01,0x14},
    {0x02,0x21},
    {0x8c,0x02},
    {0x8d,0x64},
    {0x87,0x18},
    {0x13,0x07},
    //{0x11,0x80},//pclk=mclk
    {0x11,0x30},//pclk=mclk/8
    {0x2b,0x20},
    {0x92,0x40},
    {0x9d,0x99},
    {0x06,0xe0},
    {0x29,0x54},
    {0xeb,0x30},
    {0xbb,0x20},
    {0xf5,0x21},
    {0xe1,0x3c},
    {0x16,0x01},
    {0xe0,0x0b},
    {0x2f,0xf6},
    {0x33,0x20},
    {0x34,0x08},
    {0x35,0x50},
    {0x65,0x4a},
    {0x66,0x50},
    {0x36,0x05},
    {0x37,0xf6},
    {0x38,0x46},
    {0x9b,0xf6},
    {0x9c,0x46},
    {0xbc,0x01},
    {0xbd,0xf6},
    {0xbe,0x46},
    {0x82,0x14},
    {0x83,0x23},
    {0x9a,0x23},
    {0x70,0x6f},
    {0x72,0x3f},
    {0x73,0x3f},
    {0x74,0x27},
    {0x77,0x90},
    {0x79,0x48},
    {0x7a,0x1e},
    {0x7b,0x30},
    {0x84,0x1a},
    {0x85,0x20},
    {0x89,0x02},
    {0x8a,0x64},
    {0x86,0x30},
    {0x96,0xa6},
    {0x97,0x0c},
    {0x98,0x18},
    {0x80,0x55},
    {0x24,0x70},
    {0x25,0x80},
    {0x94,0x0a},
    {0x1f,0x20},
    {0x22,0x20},
    {0x26,0x20},
    {0x56,0x40},
    {0x61,0xd3},
    {0x79,0x48},
    {0x3b,0x60},
    {0x3c,0x20},
    {0x39,0x80},
    {0x3f,0xb0},
    {0x39,0x80},
    {0x40,0x58},
    {0x41,0x54},
    {0x42,0x4e},
    {0x43,0x44},
    {0x44,0x3e},
    {0x45,0x39},
    {0x46,0x35},
    {0x47,0x31},
    {0x48,0x2e},
    {0x49,0x2b},
    {0x4b,0x29},
    {0x4c,0x27},
    {0x4e,0x23},
    {0x4f,0x20},
    {0x50,0x1e},
    {0x51,0x05},
    {0x52,0x10},
    {0x53,0x0b},
    {0x54,0x15},
    {0x57,0x87},
    {0x58,0x72},
    {0x59,0x5f},
    {0x5a,0x7e},
    {0x5b,0x1f},
    {0x5c,0x0e},
    {0x5d,0x95},
    {0x60,0x28},
    {0xb0,0xe0},
    {0xb1,0xc0},
    {0xb2,0xb0},
    {0xb3,0x88},
    {0x6a,0x01},
    {0x23,0x66},
    {0xa0,0x03},
    {0xa1,0x31},
    {0xa2,0x0b},
    {0xa3,0x26},
    {0xa4,0x05},
    {0xa5,0x25},
    {0xa6,0x06},
    {0xa7,0x80},
    {0xa8,0x80},
    {0xa9,0x20},
    {0xaa,0x20},
    {0xab,0x20},
    {0xac,0x3c},
    {0xad,0xf0},
    {0xc8,0x18},
    {0xc9,0x20},
    {0xca,0x17},
    {0xcb,0x1f},
    {0xaf,0x00},
    {0xc5,0x18},
    {0xc6,0x00},
    {0xc7,0x20},
    {0xae,0x80},
    {0xcc,0x40},
    {0xcd,0x58},
    {0xee,0x4c},
    {0x8e,0x07},
    {0x8f,0x79},
    
#elif(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC0308)
    {0xfe , 0x80},
    {0xfe , 0x00},//set page0
    {0xd2 , 0x10},//close AEC
    {0x22 , 0x55},//close AWB
    {0x5a , 0x56},
    {0x5b , 0x40},
    {0x5c , 0x4a},
    {0x22 , 0x57},//Open AWB
#if 0
    //config for 39 FPS
    {0x01 , 0x6a},//HB 106
    //{0x02 , 0x70},//VB 112
    {0x02 , 0x0c},//change VB from 112 to 12
    {0x0f , 0x00},
    {0xe2 , 0x00},//anti-flicker step [11:8]
    {0xe3 , 0x96},//anti-flicker step [7:0]
    {0xe4 , 0x01},//exp level 1  50.00fps or 20ms
    {0xe5 , 0x2c},
    {0xe6 , 0x03},//exp level 2  16.67fps
    {0xe7 , 0x84},
    {0xe8 , 0x04},//exp level 3  12.5fps
    {0xe9 , 0xb0},
    {0xea , 0x09},//exp level 4  6.00fps
    {0xeb , 0xc4},
#elif 1
    //config for 33.33 FPS
    {0x01 , 0x6a},//HB 106
    {0x02 , 0x52},//VB 82
    {0x0f , 0x00},
    {0xe2 , 0x00},//anti-flicker step [11:8]
    {0xe3 , 0x96},//anti-flicker step [7:0]
    {0xe4 , 0x01},//exp level 1  33.33fps or 30ms
    {0xe5 , 0x2c},
    {0xe6 , 0x03},//exp level 2  16.67fps
    {0xe7 , 0x84},
    {0xe8 , 0x04},//exp level 3  12.5fps
    {0xe9 , 0xb0},
    {0xea , 0x09},//exp level 4  6.00fps
    {0xeb , 0xc4},
#else
    //config for 25 FPS
    {0x01 , 0x6a},//HB 106
    //{0x02 , 0x70},//VB 112
    {0x02 , 0xe8},//change VB from 112 to 232
    {0x0f , 0x00},
    {0xe2 , 0x00},//anti-flicker step [11:8]
    {0xe3 , 0x96},//anti-flicker step [7:0]
    {0xe4 , 0x02},//exp level 1  25.00fps or 40ms
    {0xe5 , 0x58},
    {0xe6 , 0x03},//exp level 2  16.67fps
    {0xe7 , 0x84},
    {0xe8 , 0x04},//exp level 3  12.5fps
    {0xe9 , 0xb0},
    {0xea , 0x09},//exp level 4  6.00fps
    {0xeb , 0xc4},
#endif
    {0xec , 0x00},//select max exposure level 1 - highest fps
    {0x05 , 0x00},
    {0x06 , 0x00},
    {0x07 , 0x00},
    {0x08 , 0x00},
    {0x09 , 0x01},
    {0x0a , 0xe8},
    //{0x0a , 0x70},//change win_height from 488 to 368
    {0x0b , 0x02},
    {0x0c , 0x88},//win_width 648
    {0x0d , 0x02},
    {0x0e , 0x02},
    {0x10 , 0x22},
    {0x11 , 0xfd},
    {0x12 , 0x2a},
    {0x13 , 0x00},
    //{0x14 , 0x10},
    {0x14 , 0x13},//enable mirror & flip
    //-------------H_V_Switch(4)---------------//
    /*
    1://normal
    {0x14 , 0x10},
    2://IMAGE_H_MIRROR
    {0x14 , 0x11},
    3://IMAGE_V_MIRROR
    {0x14 , 0x12},
    4://IMAGE_HV_MIRROR
    {0x14 , 0x13},*/
    {0x15 , 0x0a},
    {0x16 , 0x05},
    {0x17 , 0x01},
    {0x18 , 0x44},
    {0x19 , 0x44},
    {0x1a , 0x1e},
    {0x1b , 0x00},
    {0x1c , 0xc1},
    {0x1d , 0x08},
    {0x1e , 0x60},
    {0x1f , 0x17},
    {0x20 , 0xff},
    {0x21 , 0xf8},
    {0x22 , 0x57},
    {0x24 , 0xa0},//Cb Y Cr Y
    //{0x24 , 0xa2},//Y Cb Y Cr
    {0x25 , 0x0f},
    //output sync_mode
    //{0x26 , 0x02},//0x03  20101016 zhj
    {0x26 , 0x03},//sync mode, high high
    {0x2f , 0x01},
    {0x30 , 0xf7},
    {0x31 , 0x50},
    {0x32 , 0x00},
    {0x39 , 0x04},
    {0x3a , 0x18},
    {0x3b , 0x20},
    {0x3c , 0x00},
    {0x3d , 0x00},
    {0x3e , 0x00},
    {0x3f , 0x00},
    {0x50 , 0x10},
    {0x53 , 0x82},
    {0x54 , 0x80},
    {0x55 , 0x80},
    {0x56 , 0x82},
    {0x8b , 0x40},
    {0x8c , 0x40},
    {0x8d , 0x40},
    {0x8e , 0x2e},
    {0x8f , 0x2e},
    {0x90 , 0x2e},
    {0x91 , 0x3c},
    {0x92 , 0x50},
    {0x5d , 0x12},
    {0x5e , 0x1a},
    {0x5f , 0x24},
    {0x60 , 0x07},
    {0x61 , 0x15},
    {0x62 , 0x08},
    {0x64 , 0x03},
    {0x66 , 0xe8},
    {0x67 , 0x86},
    {0x68 , 0xa2},
    {0x69 , 0x18},
    {0x6a , 0x0f},
    {0x6b , 0x00},
    {0x6c , 0x5f},
    {0x6d , 0x8f},
    {0x6e , 0x55},
    {0x6f , 0x38},
    {0x70 , 0x15},
    {0x71 , 0x33},
    {0x72 , 0xdc},
    {0x73 , 0x80},
    {0x74 , 0x02},
    {0x75 , 0x3f},
    {0x76 , 0x02},
    {0x77 , 0x36},
    {0x78 , 0x88},
    {0x79 , 0x81},
    {0x7a , 0x81},
    {0x7b , 0x22},
    {0x7c , 0xff},
    {0x93 , 0x48},
    {0x94 , 0x00},
    {0x95 , 0x05},
    {0x96 , 0xe8},
    {0x97 , 0x40},
    {0x98 , 0xf0},
    {0xb1 , 0x38},
    {0xb2 , 0x38},
    {0xbd , 0x38},
    {0xbe , 0x36},
#if 1
    {0xd0 , 0xc9},
    {0xd1 , 0x10},
    {0xd3 , 0x80},
    {0xd5 , 0xf2},
    {0xd6 , 0x16},
#else
    //default AEC setting
    {0xd0 , 0xca},
    {0xd1 , 0xa1},
    {0xd3 , 0xa0},
    {0xd5 , 0xf2},
    {0xd6 , 0x18},
#endif
    {0xdb , 0x92},
    {0xdc , 0xa5},
    {0xdf , 0x23},
    {0xd9 , 0x00},
    {0xda , 0x00},
    {0xe0 , 0x09},
    {0xed , 0x04},
#if 0
    //default max dgain
    {0xee , 0xa0},
    {0xef , 0x40},
#else
    //increased max dgain
    {0xee , 0xf0},
    {0xef , 0x60},
#endif
    {0x80 , 0x03},
    {0x80 , 0x03},
    {0x9F , 0x10},
    {0xA0 , 0x20},
    {0xA1 , 0x38},
    {0xA2 , 0x4E},
    {0xA3 , 0x63},
    {0xA4 , 0x76},
    {0xA5 , 0x87},
    {0xA6 , 0xA2},
    {0xA7 , 0xB8},
    {0xA8 , 0xCA},
    {0xA9 , 0xD8},
    {0xAA , 0xE3},
    {0xAB , 0xEB},
    {0xAC , 0xF0},
    {0xAD , 0xF8},
    {0xAE , 0xFD},
    {0xAF , 0xFF},
    /*
    GC0308_GAMMA_Select,
    1://smallest gamma curve
    {0x9F , 0x0B},
    {0xA0 , 0x16},
    {0xA1 , 0x29},
    {0xA2 , 0x3C},
    {0xA3 , 0x4F},
    {0xA4 , 0x5F},
    {0xA5 , 0x6F},
    {0xA6 , 0x8A},
    {0xA7 , 0x9F},
    {0xA8 , 0xB4}, 
    {0xA9 , 0xC6},
    {0xAA , 0xD3},
    {0xAB , 0xDD},
    {0xAC , 0xE5},
    {0xAD , 0xF1},
    {0xAE , 0xFA},
    {0xAF , 0xFF},
    2:
    {0x9F , 0x0E},
    {0xA0 , 0x1C},
    {0xA1 , 0x34},
    {0xA2 , 0x48},
    {0xA3 , 0x5A},
    {0xA4 , 0x6B},
    {0xA5 , 0x7B},
    {0xA6 , 0x95},
    {0xA7 , 0xAB},
    {0xA8 , 0xBF},
    {0xA9 , 0xCE},
    {0xAA , 0xD9},
    {0xAB , 0xE4},
    {0xAC , 0xEC},
    {0xAD , 0xF7},
    {0xAE , 0xFD},
    {0xAF , 0xFF},
    3:
    {0x9F , 0x10},
    {0xA0 , 0x20},
    {0xA1 , 0x38},
    {0xA2 , 0x4E},
    {0xA3 , 0x63},
    {0xA4 , 0x76},
    {0xA5 , 0x87},
    {0xA6 , 0xA2},
    {0xA7 , 0xB8},
    {0xA8 , 0xCA},
    {0xA9 , 0xD8},
    {0xAA , 0xE3},
    {0xAB , 0xEB},
    {0xAC , 0xF0},
    {0xAD , 0xF8},
    {0xAE , 0xFD},
    {0xAF , 0xFF},
    4:
    {0x9F , 0x14},
    {0xA0 , 0x28},
    {0xA1 , 0x44},
    {0xA2 , 0x5D},
    {0xA3 , 0x72},
    {0xA4 , 0x86},
    {0xA5 , 0x95},
    {0xA6 , 0xB1},
    {0xA7 , 0xC6},
    {0xA8 , 0xD5},
    {0xA9 , 0xE1},
    {0xAA , 0xEA},
    {0xAB , 0xF1},
    {0xAC , 0xF5},
    {0xAD , 0xFB},
    {0xAE , 0xFE},
    {0xAF , 0xFF},
    5://largest gamma curve
    {0x9F , 0x15},
    {0xA0 , 0x2A},
    {0xA1 , 0x4A},
    {0xA2 , 0x67},
    {0xA3 , 0x79},
    {0xA4 , 0x8C},
    {0xA5 , 0x9A},
    {0xA6 , 0xB3},
    {0xA7 , 0xC5},
    {0xA8 , 0xD5},
    {0xA9 , 0xDF},
    {0xAA , 0xE8},
    {0xAB , 0xEE},
    {0xAC , 0xF3},
    {0xAD , 0xFA},
    {0xAE , 0xFD},
    {0xAF , 0xFF},
    */
    //-----------GAMMA Select End--------------//
    {0xc0 , 0x00},
    {0xc1 , 0x10},
    {0xc2 , 0x1C},
    {0xc3 , 0x30},
    {0xc4 , 0x43},
    {0xc5 , 0x54},
    {0xc6 , 0x65},
    {0xc7 , 0x75},
    {0xc8 , 0x93},
    {0xc9 , 0xB0},
    {0xca , 0xCB},
    {0xcb , 0xE6},
    {0xcc , 0xFF},
    {0xf0 , 0x02},
    {0xf1 , 0x01},
    {0xf2 , 0x01},
    {0xf3 , 0x30},
    {0xf9 , 0x9f},
    {0xfa , 0x78},
    //{0xfa , 0x58},//Change measure window Y1 from 480 to 352
    //-------------------------------------------------
    {0xfe , 0x01},// set page1
    {0x00 , 0xf5},
    {0x02 , 0x1a},
    {0x0a , 0xa0},
    {0x0b , 0x60},
    {0x0c , 0x08},
    {0x0e , 0x4c},
    {0x0f , 0x39},
    {0x11 , 0x3f},
    {0x12 , 0x72},
    {0x13 , 0x13},
    {0x14 , 0x42},
    {0x15 , 0x43},
    {0x16 , 0xc2},
    {0x17 , 0xa8},
    {0x18 , 0x18},
    {0x19 , 0x40},
    {0x1a , 0xd0},
    {0x1b , 0xf5},
    {0x70 , 0x40},
    {0x71 , 0x58},
    {0x72 , 0x30},
    {0x73 , 0x48},
    {0x74 , 0x20},
    {0x75 , 0x60},
    {0x77 , 0x20},
    {0x78 , 0x32},
    {0x30 , 0x03},
    {0x31 , 0x40},
    {0x32 , 0xe0},
    {0x33 , 0xe0},
    {0x34 , 0xe0},
    {0x35 , 0xb0},
    {0x36 , 0xc0},
    {0x37 , 0xc0},
    {0x38 , 0x04},
    {0x39 , 0x09},
    {0x3a , 0x12},
    {0x3b , 0x1C},
    {0x3c , 0x28},
    {0x3d , 0x31},
    {0x3e , 0x44},
    {0x3f , 0x57},
    {0x40 , 0x6C},
    {0x41 , 0x81},
    {0x42 , 0x94},
    {0x43 , 0xA7},
    {0x44 , 0xB8},
    {0x45 , 0xD6},
    {0x46 , 0xEE},
    {0x47 , 0x0d},
    {0xfe , 0x00},//set page0
    //-----------Update the registers 2010/07/06-------------//
    //Registers of Page0
    {0xfe , 0x00},//set page0
    {0x10 , 0x26},
    {0x11 , 0x0d},//fd,modified by mormo 2010/07/06
    {0x1a , 0x2a},//1e,modified by mormo 2010/07/06
    {0x1c , 0x49},//c1,modified by mormo 2010/07/06
    {0x1d , 0x9a},//08,modified by mormo 2010/07/06
    {0x1e , 0x61},//60,modified by mormo 2010/07/06
    {0x3a , 0x20},
    {0x50 , 0x14},//10,modified by mormo 2010/07/06
    {0x53 , 0x80},
    {0x56 , 0x80},
    {0x8b , 0x20},//LSC
    {0x8c , 0x20},
    {0x8d , 0x20},
    {0x8e , 0x14},
    {0x8f , 0x10},
    {0x90 , 0x14},
    {0x94 , 0x02},
    {0x95 , 0x07},
    {0x96 , 0xe0},
    {0xb1 , 0x40},//YCPT
    {0xb2 , 0x40},
    {0xb3 , 0x40},
    {0xb6 , 0xe0},
    //{0xd0 , 0xcb},//AECT    c9,modifed by mormo 2010/07/06
    //{0xd3 , 0x48},//80,modified by mormor 2010/07/06
    {0xf2 , 0x02},
    //{0xf7 , 0x12},
    //{0xf8 , 0x0a},
    //Registers 
    {0xfe , 0x01},// set page1
    {0x02 , 0x20},
    {0x04 , 0x10},
    {0x05 , 0x08},
    {0x06 , 0x20},
    {0x08 , 0x0a},
    {0x0e , 0x44},
    {0x0f , 0x32},
    {0x10 , 0x41},
    {0x11 , 0x37},
    {0x12 , 0x22},
    {0x13 , 0x19},
    {0x14 , 0x44},
    {0x15 , 0x44},
    {0x19 , 0x50},
    {0x1a , 0xd8},
    {0x32 , 0x10},
    {0x35 , 0x00},
    {0x36 , 0x80},
    {0x37 , 0x00},
    //-----------Update the registers end---------//
    {0xfe , 0x00},//set page0
    {0xd2 , 0x90},

#elif(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC2053)
    {0xfe,0x80}, // page select
    {0xfe,0x80},
    {0xfe,0x80},
    {0xfe,0x00},
    {0xf2,0x00}, // [7] OTP_clk_gate [6:4] OTP_mode_temp [1] I2C_open_ena [0]pwd_dn
    {0xf3,0x0f}, // [7] OTP_finish [6] OTP_busy [5] Spad_vb_hiz_mode [4] Spad_buf_mode [3] Sdata_pad_io [2:0] Ssync_pad_io
    {0xf4,0x36}, // [7] reduce_power_mode, [6:4]PLL_ldo_set, [3:0]spi_clk_div
    {0xf5,0xc0}, // [7] soc_mclk_enable, [6] pll_ldo_en, [5:4]cp_clk_del, [3:0]cp_clk_div
    {0xf6,0x44}, // [7:3]wpllclk_div, [2:0]refmp_div
    {0xf7,0x01}, // [7]refdiv2d5_en [6]refdiv1d5_en [5:4]scaler_mode(dvpmode) [3]refmp_enb [2]freq div2 [1]div2en [0]pll_en
    {0xf8,0x63}, // [7:0]pllmp_div
    {0xf9,0x40}, // [7:3]rpllclk_div [2:1]pllmp_prediv [0]analog_pwc
    {0xfc,0x8e}, // [7] regf clk enable [6] sys_rclk_sel [5] sys_wclk_sel [4:3]spi_sel_mode [2] serail_clk enable [1] re_lock_pll [0] not_use_pll
    /*cisctl&analog*/
    {0xfe,0x00},
    {0x87,0x18}, // Debug_mode disable
    {0xee,0x30},
    {0xd0,0xb7},
    {0x03,0x01},
    {0x04,0x19},
    {0x05,0x05}, // Line length = 1320 *2   [3:0] Line length[11:8] X2
    {0x06,0x28}, //                         [7:0] Line length[7:0]  X2
    {0x07,0x00},
    {0x08,0x11},
    {0x09,0x00}, // row start
    {0x0a,0x02},
    {0x0b,0x00}, // col start
    {0x0c,0x02},
    {0x0d,0x04}, // valid line time:Window width 1088
                 // Windows height default is 1936
    {0x0e,0x40},
    {0x12,0xe2},
    {0x13,0x16},
    {0x19,0x0a},
    {0x21,0x1c},
    {0x28,0x0a},
    {0x29,0x24},
    {0x2b,0x04},
    {0x32,0xf8},
    {0x37,0x03},
    {0x39,0x15},
    {0x43,0x07},
    {0x44,0x40},
    {0x46,0x0b},
    {0x4b,0x20},
    {0x4e,0x08},
    {0x55,0x20},
    {0x66,0x05},
    {0x67,0x05},
    {0x77,0x01},
    {0x78,0x00},
    {0x7c,0x93},
    {0x8c,0x12},
    {0x8d,0x92},
    {0x90,0x01},
    {0x9d,0x10},
    {0xce,0x7c},
    {0xd2,0x41},
    {0xd3,0xdc},
    {0xe6,0x50},
    /*gain*/
    {0xb6,0xc0},
    {0xb0,0x70},
    {0xb1,0x01},
    {0xb2,0x14},
    {0xb3,0x30},
    {0xb4,0x00},
    {0xb8,0x01},
    {0xb9,0x2c},
    /*blk*/
    {0x26,0x30},
    {0xfe,0x01},
    {0x40,0x23}, // BLK_mode1. [7] not smooth [6:4] blk_smooth_speed [3]blk_dd_map [2]dark_sel_map [1]dark_current_en [0]offset_en
    {0x55,0x07},
    {0x60,0x40}, // DARK OFFSET
    {0xfe,0x04},
    {0x14,0x78}, // Ndark_ratio_G1
    {0x15,0x78}, // Ndark_ratio_R1
    {0x16,0x78}, // Ndark_ratio_B2
    {0x17,0x78}, // Ndark_ratio_G2
    /*window*/
    {0xfe,0x01},
    {0x92,0x01}, // output win start y
    {0x94,0x02}, // output win start x
    {0x95,0x04}, // output win height 1080
    {0x96,0x38},
    {0x97,0x07}, // outout win width  1920
    {0x98,0x80},
    /*DSP2*/
    {0xfe,0x01},
    {0x01,0x05},
    {0x02,0x89},
    {0x04,0x01},
    {0x07,0xa6},
    {0x08,0xa9},
    {0x09,0xa8},
    {0x0a,0xa7},
    {0x0b,0xff},
    {0x0c,0xff},
    {0x0f,0x00},
    {0x50,0x1c},
    {0x89,0x03},
    {0xfe,0x04},
    {0x28,0x86},
    {0x29,0x86},
    {0x2a,0x86},
    {0x2b,0x68},
    {0x2c,0x68},
    {0x2d,0x68},
    {0x2e,0x68},
    {0x2f,0x68},
    {0x30,0x4f},
    {0x31,0x68},
    {0x32,0x67},
    {0x33,0x66},
    {0x34,0x66},
    {0x35,0x66},
    {0x36,0x66},
    {0x37,0x66},
    {0x38,0x62},
    {0x39,0x62},
    {0x3a,0x62},
    {0x3b,0x62},
    {0x3c,0x62},
    {0x3d,0x62},
    {0x3e,0x62},
    {0x3f,0x62},
    /****DVP & MIPI****/
    {0xfe,0x01},
    // {0x8c,0x01}, // test mode
    //{0x9a,0x06},    /* VSYNC low pulse */
    {0x9a,0x02},      /* VSYNC high pulse */
    {0xfe,0x00},
    {0x7b,0x2b},
    {0x23,0x2d},
    {0xfe,0x03},
    {0x01,0x20}, // DPHY_analog_mode1
    {0x02,0x56}, // DPHY_analog_mode2
    {0x03,0xb2}, // DPHY_analog_mode3
    {0x12,0x80}, // LWC_set[7:0]
    {0x13,0x07}, // LWC_set[15:8]
    
    {0xfe,0x00},
    {0x3e,0x40},

#endif
};

#if 0
SPI_Psram_Cfg_Type apMemory1604 = {
    .readIdCmd = 0x9F,
    .readIdDmyClk = 0,
    .burstToggleCmd = 0xC0,
    .resetEnableCmd = 0x66,
    .resetCmd = 0x99,
    .enterQuadModeCmd = 0x35,
    .exitQuadModeCmd = 0xF5,
    .readRegCmd = 0xB5,
    .readRegDmyClk = 1,
    .writeRegCmd = 0xB1,
    .readCmd = 0x03,
    .readDmyClk = 0,
    .fReadCmd = 0x0B,
    .fReadDmyClk = 1,
    .fReadQuadCmd = 0xEB,
    .fReadQuadDmyClk = 3,
    .writeCmd = 0x02,
    .quadWriteCmd = 0x38,
    .pageSize = 512,
    .ctrlMode = PSRAM_SPI_CTRL_MODE,
    .driveStrength = PSRAM_DRIVE_STRENGTH_50_OHMS,
    .burstLength = PSRAM_BURST_LENGTH_512_BYTES,
};
#endif

/*
SF_Ctrl_Cmds_Cfg cmdsCfg = {
    .cmdsEn=ENABLE,
    .burstToggleEn=ENABLE,
    .wrapModeEn=DISABLE,
    .wrapLen=SF_CTRL_WRAP_LEN_512,
};

SF_Ctrl_Psram_Cfg sfCtrlPsramCfg = {
    .owner=SF_CTRL_OWNER_SAHB,
    .padSel=SF_CTRL_PAD_SEL_DUAL_CS_SF2,
    .bankSel=SF_CTRL_SEL_PSRAM,
    .psramRxClkInvertSrc=ENABLE,
    .psramRxClkInvertSel=ENABLE,
    .psramDelaySrc=ENABLE,
    .psramClkDelay=0,
};
*/

/*@} end of group IMAGE_SENSOR_Private_Variables */

/** @defgroup  IMAGE_SENSOR_Global_Variables
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Global_Variables */

/** @defgroup  IMAGE_SENSOR_Private_Fun_Declaration
 *  @{
 */
static void CAM_GPIO_Init(void);
static void I2C_GPIO_Init(void);
static BL_Err_Type CAM_Write_Byte8(uint8_t data, uint8_t cmd);
static uint8_t CAM_Read_Byte8(uint8_t cmd);
static BL_Err_Type CAM_Read_ID(void);
static BL_Err_Type CAM_Reg_Config(void);

/*@} end of group IMAGE_SENSOR_Private_Fun_Declaration */

/** @defgroup  IMAGE_SENSOR_Private_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  CAMERA GPIO Initialization
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void CAM_GPIO_Init(void)
{
#if 0
    GLB_GPIO_Cfg_Type cfg;

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_0;
    cfg.gpioFun = GPIO0_FUN_PIX_CLK;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_1;
    cfg.gpioFun = GPIO1_FUN_FRAME_VLD;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_2;
    cfg.gpioFun = GPIO2_FUN_LINE_VLD;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_3;
    cfg.gpioFun = GPIO3_FUN_PIX_DAT0;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_4;
    cfg.gpioFun = GPIO4_FUN_PIX_DAT1;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_5;
    cfg.gpioFun = GPIO5_FUN_PIX_DAT2;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_6;
    cfg.gpioFun = GPIO6_FUN_PIX_DAT3;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_12;
    cfg.gpioFun = GPIO12_FUN_PIX_DAT4;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_29;
    cfg.gpioFun = GPIO29_FUN_PIX_DAT5;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_30;
    cfg.gpioFun = GPIO30_FUN_PIX_DAT6;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);

    cfg.drive=0;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_31;
    cfg.gpioFun = GPIO31_FUN_PIX_DAT7;
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);
    
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioPin = GLB_GPIO_PIN_10;
    cfg.gpioFun = GPIO10_FUN_CAM_REF_CLK;
    cfg.gpioMode = GPIO_MODE_OUTPUT;
    cfg.pullType = GPIO_PULL_NONE;
    GLB_GPIO_Init(&cfg);
#endif
}


/****************************************************************************//**
 * @brief  Dump image sensor register while is set
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_Dump_Register(void)
{
    uint32_t i;
    
    for(i=0;i<sizeof(sensorRegList)/sizeof(sensorRegList[0]);i++){
        MSG("reg[%02x]: %02x\n",sensorRegList[i][0],CAM_Read_Byte8(sensorRegList[i][0]));
    }
}


/****************************************************************************//**
 * @brief  I2C GPIO Initialization
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
static void I2C_GPIO_Init(void)
{
#if 0
    uint8_t i;
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[2];
    uint8_t gpiofuns[2];
    uint8_t gpioMode[2];

    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioMode=GPIO_MODE_OUTPUT;

    gpiopins[0]=GLB_GPIO_PIN_16;
    gpiopins[1]=GLB_GPIO_PIN_11;
    gpiofuns[0]=GPIO16_FUN_I2C0_SCL;
    gpiofuns[1]=GPIO11_FUN_I2C0_SDA;
    gpioMode[0]=GPIO_MODE_AF;
    gpioMode[1]=GPIO_MODE_AF;

    for(i=0;i<sizeof(gpiopins)/sizeof(gpiopins[0]);i++){
        cfg.gpioPin=gpiopins[i];
        cfg.gpioFun=gpiofuns[i];
        cfg.gpioMode=gpioMode[i];
        GLB_GPIO_Init(&cfg);
    }
#endif
}


/****************************************************************************//**
 * @brief  PSRAM GPIO Initialization
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#if 0
static void SF_Cfg_Init_Ext_Psram_Gpio(void)
{
    GLB_GPIO_Cfg_Type cfg;
    uint8_t gpiopins[6];
    uint8_t i=0;

    cfg.gpioMode=GPIO_MODE_AF;
    cfg.pullType=GPIO_PULL_UP;
    cfg.drive=1;
    cfg.smtCtrl=1;
    cfg.gpioFun=GPIO_FUN_FLASH_PSRAM;

    gpiopins[0]=BFLB_EXTPSRAM_CLK_GPIO;
    gpiopins[1]=BFLB_EXTPSRAM_CS_GPIO;
    gpiopins[2]=BFLB_EXTPSRAM_DATA0_GPIO;
    gpiopins[3]=BFLB_EXTPSRAM_DATA1_GPIO;
    gpiopins[4]=BFLB_EXTPSRAM_DATA2_GPIO;
    gpiopins[5]=BFLB_EXTPSRAM_DATA3_GPIO;

    for(i=0;i<sizeof(gpiopins);i++){
        cfg.gpioPin=gpiopins[i];
        if(i==0||i==1){
            /*flash clk and cs is output*/
            cfg.gpioMode=GPIO_MODE_OUTPUT;
        }else{
            /*data are bidir*/
            cfg.gpioMode=GPIO_MODE_AF;
        }
        GLB_GPIO_Init(&cfg);
    }
}
#endif

/****************************************************************************//**
 * @brief  I2C CAMERA Write 8 bits
 *
 * @param  cmd: Reg Addr
 * @param  data: Reg Value
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type CAM_Write_Byte8(uint8_t cmd, uint8_t data)
{
    uint8_t temp = data;
    I2C_Transfer_Cfg tranCfg;

    tranCfg.slaveAddr = I2C_CAMERA_ADDR;
    tranCfg.slaveAddr10Bit = DISABLE;
    tranCfg.stopEveryByte = DISABLE;
    tranCfg.subAddrSize = 1;
    tranCfg.subAddr = cmd;
    tranCfg.dataSize = 1;
    tranCfg.data = &temp;
    return I2C_MasterSendBlocking(I2C1_ID, &tranCfg);
}


/****************************************************************************//**
 * @brief  I2C CAMERA Read 8 bits
 *
 * @param  cmd: Reg Addr
 *
 * @return Reg Value
 *
*******************************************************************************/
static uint8_t CAM_Read_Byte8(uint8_t cmd)
{
    uint8_t temp = 0;
    I2C_Transfer_Cfg tranCfg;

    tranCfg.slaveAddr=I2C_CAMERA_ADDR;
    tranCfg.slaveAddr10Bit = DISABLE;
    tranCfg.stopEveryByte=DISABLE;
    tranCfg.subAddrSize=1;
    tranCfg.subAddr=cmd;
    tranCfg.dataSize=1;
    tranCfg.data=&temp;
    I2C_MasterReceiveBlocking(I2C1_ID, &tranCfg);
    
    return temp;
}


/****************************************************************************//**
 * @brief  CAMERA Read ID
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type CAM_Read_ID(void)
{
    uint8_t buf[2] = {0};
#if(IMAGE_SENSOR_USE == IMAGE_SENSOR_BF2013 \
 || IMAGE_SENSOR_USE == IMAGE_SENSOR_GC2053)

    buf[0] = CAM_Read_Byte8(SENSOR_ID_REG_MSB);
    ARCH_Delay_MS(10);

    buf[1] = CAM_Read_Byte8(SENSOR_ID_REG_LSB);

    if(buf[0] == SENSOR_ID_VAL_MSB && buf[1] == SENSOR_ID_VAL_LSB){
        MSG("ID correct\n");
        return SUCCESS;
    }
    else{
        MSG("%02x %02x\n",buf[0],buf[1]);
        return ERROR;
    }
#elif(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC0308)
    buf[0] = CAM_Read_Byte8(SENSOR_ID_REG);

    if(buf[0] == SENSOR_ID_VAL){
        return SUCCESS;
    }
    else{
        return ERROR;
    }
#endif
}


/****************************************************************************//**
 * @brief  CAMERA Reg Config
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
static BL_Err_Type CAM_Reg_Config(void)
{
    int i;

    for (i = 0; i < sizeof(sensorRegList)/sizeof(sensorRegList[0]); i++){
        if(CAM_Write_Byte8(sensorRegList[i][0], sensorRegList[i][1]) != SUCCESS){
            return ERROR;
        }
        ARCH_Delay_MS(1);
    }
    return SUCCESS;
}


/*@} end of group IMAGE_SENSOR_Private_Functions */

/** @defgroup  IMAGE_SENSOR_Public_Functions
 *  @{
 */

/****************************************************************************//**
 * @brief  PSRAM Config Initialization
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_PSRAM_Init(void)
{
#if 0
    uint8_t psramId[8] = {0};
    
    GLB_Set_SF_CLK(1,GLB_SFLASH_CLK_72M,1);
    SF_Cfg_Init_Ext_Psram_Gpio();
    
    Psram_Init(&apMemory1604, &cmdsCfg, &sfCtrlPsramCfg);
    Psram_ReadId(&apMemory1604, psramId);
    MSG("PSRAM ID: %02X %02X %02X %02X %02X %02X %02X %02X.\r\n",
        psramId[0], psramId[1], psramId[2], psramId[3], psramId[4], psramId[5], psramId[6], psramId[7]);

    Psram_Cache_Write_Set(&apMemory1604, SF_CTRL_QIO_MODE, DISABLE, ENABLE, ENABLE);
    L1C_Cache_Enable_Set(0x0f);
#endif
}


/****************************************************************************//**
 * @brief  Image sensor initialization
 *
 * @param  camId: DVP2BUS ID
 * @param  mjpegEn: Enable or disable mjpeg
 * @param  camCfg: CAM configuration structure pointer
 * @param  mjpegCfg: MJPEG configuration structure pointer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Image_Sensor_Init(CAM_ID_Type camId,BL_Fun_Type mjpegEn,CAM_CFG_Type *camCfg,MJPEG_CFG_Type *mjpegCfg)
{
    /* Gpio init */
    CAM_GPIO_Init();
    I2C_GPIO_Init();

    /* Set clock */
    //GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_I2C);
    //GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_CAM);
    //GLB_AHB_Slave1_Clock_Gate(DISABLE,BL_AHB_SLAVE1_MJPEG);
    //GLB_Set_I2C_CLK(1,0);
    //GLB_Set_CAM_CLK(ENABLE,GLB_CAM_CLK_DLL96M,3);
    //GLB_SWAP_EMAC_CAM_Pin(GLB_EMAC_CAM_PIN_CAM);
    
    if(CAM_Read_ID() != SUCCESS){
        return ERROR;
    }
    
    if(CAM_Reg_Config() != SUCCESS){
        return ERROR;
    }
    
    CAM_Disable(camId);
    MJPEG_Disable();
    
    if(mjpegEn){
        CAM_Init(camId,camCfg);
        MJPEG_Init(mjpegCfg);
        MJPEG_Enable();
    }else{
        CAM_Init(camId,camCfg);
    }
    
    //CAM_Enable(camId);
    
    return SUCCESS;
}


/****************************************************************************//**
 * @brief  Get one camera frame
 *
 * @param  camId: DVP2BUS ID
 * @param  pic: Pointer of picture start address
 * @param  len: Length of picture
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Image_Sensor_CAM_Get(CAM_ID_Type camId,uint8_t **pic,uint32_t *len)
{
    CAM_Frame_Info info;
    ARCH_MemSet(&info, 0, sizeof(info));
    
    CAM_Get_Frame_Info(camId,&info);
    
    if(info.validFrames == 0){
        return ERROR;
    }
    
    *pic = (uint8_t*)(uintptr_t)(info.curFrameAddr);
    *len = info.curFrameBytes;
    
    return SUCCESS;
}


/****************************************************************************//**
 * @brief  Get available count of camera frames
 *
 * @param  camId: DVP2BUS ID
 *
 * @return Frames count
 *
*******************************************************************************/
uint8_t Image_Sensor_CAM_Frame_Count(CAM_ID_Type camId)
{
    return CAM_Get_Frame_Count(camId);
}


/****************************************************************************//**
 * @brief  Pop one camera frame
 *
 * @param  camId: DVP2BUS ID
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_CAM_Release(CAM_ID_Type camId)
{
    CAM_Pop_Frame(camId);
}


/****************************************************************************//**
 * @brief  Open camera function
 *
 * @param  camId: DVP2BUS ID
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_CAM_Open(CAM_ID_Type camId)
{
    CAM_Enable(camId);
}


/****************************************************************************//**
 * @brief  Close camera function
 *
 * @param  camId: DVP2BUS ID
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_CAM_Close(CAM_ID_Type camId)
{
    CAM_Disable(camId);
}


/****************************************************************************//**
 * @brief  Deinit camera module
 *
 * @param  camId: DVP2BUS ID
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_CAM_Deinit(CAM_ID_Type camId)
{
    CAM_Deinit(camId);
}


/****************************************************************************//**
 * @brief  Get one mjpeg frame
 *
 * @param  pic: Pointer of picture start address
 * @param  len: Length of picture
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Image_Sensor_MJPEG_Get(uint8_t **pic,uint32_t *len)
{
    MJPEG_Frame_Info info;
    ARCH_MemSet(&info, 0, sizeof(info));
    
    MJPEG_Get_Frame_Info(&info);
    
    if(info.validFrames == 0){
        return ERROR;
    }
    
    *pic = (uint8_t*)(uintptr_t)(info.curFrameAddr);
    *len = info.curFrameBytes;
    
    return SUCCESS;
}


/****************************************************************************//**
 * @brief  Get available count of mjpeg frames
 *
 * @param  None
 *
 * @return Frames count
 *
*******************************************************************************/
uint8_t Image_Sensor_MJPEG_Frame_Count(void)
{
    return MJPEG_Get_Frame_Count();
}


/****************************************************************************//**
 * @brief  Pop one mjpeg frame
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_MJPEG_Release(void)
{
    MJPEG_Pop_Frame();
}


/****************************************************************************//**
 * @brief  Open mjpeg function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_MJPEG_Open(void)
{
    MJPEG_Enable();
}


/****************************************************************************//**
 * @brief  Close mjpeg function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_MJPEG_Close(void)
{
    MJPEG_Disable();
}


/****************************************************************************//**
 * @brief  Deinit mjpeg module
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Image_Sensor_MJPEG_Deinit(void)
{
    MJPEG_Deinit();
}


/*@} end of group IMAGE_SENSOR_Public_Functions */

/*@} end of group IMAGE_SENSOR */

/*@} end of group Image_Sensor_Driver */
