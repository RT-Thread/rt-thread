/* Copyright 2018 Canaan Inc.
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
#ifndef _OV5640_H
#define _OV5640_H

#include <stdint.h>

#define OV5640_ID           0X5640
#define OV5640_ADDR         0X78
#define OV5640_CHIPIDH      0X300A
#define OV5640_CHIPIDL      0X300B

#define XSIZE               320
#define YSIZE               240
#define LCD_GRAM_ADDRESS    0x60020000

#define QQVGA_160_120       0
#define QCIF_176_144        1
#define QVGA_320_240        2
#define WQVGA_400_240       3
#define CIF_352_288         4

#define jpeg_buf_size       (30*1024)

uint8_t ov5640_init(void);
void ov5640_flash_lamp(uint8_t sw);
void OV5640_Brightness(uint8_t bright);
void OV5640_Exposure(uint8_t exposure);
void OV5640_Light_Mode(uint8_t mode);
void OV5640_Color_Saturation(uint8_t sat);
void OV5640_Brightness(uint8_t bright);
void OV5640_Contrast(uint8_t contrast);
void OV5640_Sharpness(uint8_t sharp);
void OV5640_Special_Effects(uint8_t eft);
uint8_t OV5640_Focus_Init(void);
uint8_t OV5640_Auto_Focus(void);

#endif

