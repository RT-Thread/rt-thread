/**
  ******************************************************************************
  * @file    image_sensor.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __IMAGE_SENSOR_H__
#define __IMAGE_SENSOR_H__

#include "bflb_bsp_driver_glue.h"

/** @addtogroup  Image_Sensor_Driver
 *  @{
 */

/** @addtogroup  IMAGE_SENSOR
 *  @{
 */

/** @defgroup  IMAGE_SENSOR_Public_Types
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Public_Types */

/** @defgroup  IMAGE_SENSOR_Public_Constants
 *  @{
 */

/*@} end of group IMAGE_SENSOR_Public_Constants */

/** @defgroup  IMAGE_SENSOR_Public_Macros
 *  @{
 */
#define IMAGE_SENSOR_BF2013                         0
#define IMAGE_SENSOR_GC0308                         1
#define IMAGE_SENSOR_GC2053                         2
#define IMAGE_SENSOR_USE                            IMAGE_SENSOR_GC2053

#if(IMAGE_SENSOR_USE == IMAGE_SENSOR_GC2053)
#define SENSOR_MAX_EXPO_TIME                        143282
#define SENSOR_MIN_EXPO_TIME                        40000000
#define SENSOR_MAX_GAIN                             9216
#endif

/*@} end of group IMAGE_SENSOR_Public_Macros */

/** @defgroup  IMAGE_SENSOR_Public_Functions
 *  @{
 */
void Image_Sensor_PSRAM_Init(void);
BL_Err_Type Image_Sensor_Init(CAM_ID_Type camId,BL_Fun_Type mjpegEn,CAM_CFG_Type *camCfg,MJPEG_CFG_Type *mjpegCfg);
void Image_Sensor_Dump_Register(void);
BL_Err_Type Image_Sensor_CAM_Get(CAM_ID_Type camId,uint8_t **pic,uint32_t *len);
uint8_t Image_Sensor_CAM_Frame_Count(CAM_ID_Type camId);
void Image_Sensor_CAM_Release(CAM_ID_Type camId);
void Image_Sensor_CAM_Open(CAM_ID_Type camId);
void Image_Sensor_CAM_Close(CAM_ID_Type camId);
void Image_Sensor_CAM_Deinit(CAM_ID_Type camId);
BL_Err_Type Image_Sensor_MJPEG_Get(uint8_t **pic,uint32_t *len);
uint8_t Image_Sensor_MJPEG_Frame_Count(void);
void Image_Sensor_MJPEG_Release(void);
void Image_Sensor_MJPEG_Open(void);
void Image_Sensor_MJPEG_Close(void);
void Image_Sensor_MJPEG_Deinit(void);

/*@} end of group IMAGE_SENSOR_Public_Functions */

/*@} end of group IMAGE_SENSOR */

/*@} end of group Image_Sensor_Driver */

#endif /* __IMAGE_SENSOR_H__ */
