/**
  ******************************************************************************
  * @file    ov2640.h
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    02-December-2014
  * @brief   This file contains all the functions prototypes for the ov2640.c
  *          driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OV2640_H
#define __OV2640_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "../Common/camera.h"
   
/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup ov2640
  * @{
  */

/** @defgroup OV2640_Exported_Types
  * @{
  */
     
/**
  * @}
  */ 

/** @defgroup OV2640_Exported_Constants
  * @{
  */
/** 
  * @brief  OV2640 ID  
  */  
#define  OV2640_ID    0x26
/** 
  * @brief  OV2640 Registers  
  */
/* OV2640 Registers definition when DSP bank selected (0xFF = 0x00) */
#define OV2640_DSP_R_BYPASS             0x05
#define OV2640_DSP_Qs                   0x44
#define OV2640_DSP_CTRL                 0x50
#define OV2640_DSP_HSIZE1               0x51
#define OV2640_DSP_VSIZE1               0x52
#define OV2640_DSP_XOFFL                0x53
#define OV2640_DSP_YOFFL                0x54
#define OV2640_DSP_VHYX                 0x55
#define OV2640_DSP_DPRP                 0x56
#define OV2640_DSP_TEST                 0x57
#define OV2640_DSP_ZMOW                 0x5A
#define OV2640_DSP_ZMOH                 0x5B
#define OV2640_DSP_ZMHH                 0x5C
#define OV2640_DSP_BPADDR               0x7C
#define OV2640_DSP_BPDATA               0x7D
#define OV2640_DSP_CTRL2                0x86
#define OV2640_DSP_CTRL3                0x87
#define OV2640_DSP_SIZEL                0x8C
#define OV2640_DSP_HSIZE2               0xC0
#define OV2640_DSP_VSIZE2               0xC1
#define OV2640_DSP_CTRL0                0xC2
#define OV2640_DSP_CTRL1                0xC3
#define OV2640_DSP_R_DVP_SP             0xD3
#define OV2640_DSP_IMAGE_MODE           0xDA
#define OV2640_DSP_RESET                0xE0
#define OV2640_DSP_MS_SP                0xF0
#define OV2640_DSP_SS_ID                0x7F
#define OV2640_DSP_SS_CTRL              0xF8
#define OV2640_DSP_MC_BIST              0xF9
#define OV2640_DSP_MC_AL                0xFA
#define OV2640_DSP_MC_AH                0xFB
#define OV2640_DSP_MC_D                 0xFC
#define OV2640_DSP_P_STATUS             0xFE
#define OV2640_DSP_RA_DLMT              0xFF

/* OV2640 Registers definition when sensor bank selected (0xFF = 0x01) */
#define OV2640_SENSOR_GAIN              0x00
#define OV2640_SENSOR_COM1              0x03
#define OV2640_SENSOR_REG04             0x04
#define OV2640_SENSOR_REG08             0x08
#define OV2640_SENSOR_COM2              0x09
#define OV2640_SENSOR_PIDH              0x0A
#define OV2640_SENSOR_PIDL              0x0B
#define OV2640_SENSOR_COM3              0x0C
#define OV2640_SENSOR_COM4              0x0D
#define OV2640_SENSOR_AEC               0x10
#define OV2640_SENSOR_CLKRC             0x11
#define OV2640_SENSOR_COM7              0x12
#define OV2640_SENSOR_COM8              0x13
#define OV2640_SENSOR_COM9              0x14
#define OV2640_SENSOR_COM10             0x15
#define OV2640_SENSOR_HREFST            0x17
#define OV2640_SENSOR_HREFEND           0x18
#define OV2640_SENSOR_VSTART            0x19
#define OV2640_SENSOR_VEND              0x1A
#define OV2640_SENSOR_MIDH              0x1C
#define OV2640_SENSOR_MIDL              0x1D
#define OV2640_SENSOR_AEW               0x24
#define OV2640_SENSOR_AEB               0x25
#define OV2640_SENSOR_W                 0x26
#define OV2640_SENSOR_REG2A             0x2A
#define OV2640_SENSOR_FRARL             0x2B
#define OV2640_SENSOR_ADDVSL            0x2D
#define OV2640_SENSOR_ADDVHS            0x2E
#define OV2640_SENSOR_YAVG              0x2F
#define OV2640_SENSOR_REG32             0x32
#define OV2640_SENSOR_ARCOM2            0x34
#define OV2640_SENSOR_REG45             0x45
#define OV2640_SENSOR_FLL               0x46
#define OV2640_SENSOR_FLH               0x47
#define OV2640_SENSOR_COM19             0x48
#define OV2640_SENSOR_ZOOMS             0x49
#define OV2640_SENSOR_COM22             0x4B
#define OV2640_SENSOR_COM25             0x4E
#define OV2640_SENSOR_BD50              0x4F
#define OV2640_SENSOR_BD60              0x50
#define OV2640_SENSOR_REG5D             0x5D
#define OV2640_SENSOR_REG5E             0x5E
#define OV2640_SENSOR_REG5F             0x5F
#define OV2640_SENSOR_REG60             0x60
#define OV2640_SENSOR_HISTO_LOW         0x61
#define OV2640_SENSOR_HISTO_HIGH        0x62 

/** 
 * @brief  OV2640 Features Parameters  
 */
#define OV2640_BRIGHTNESS_LEVEL0        0x40   /* Brightness level -2         */
#define OV2640_BRIGHTNESS_LEVEL1        0x30   /* Brightness level -1         */
#define OV2640_BRIGHTNESS_LEVEL2        0x20   /* Brightness level 0          */
#define OV2640_BRIGHTNESS_LEVEL3        0x10   /* Brightness level +1         */
#define OV2640_BRIGHTNESS_LEVEL4        0x00   /* Brightness level +2         */

#define OV2640_BLACK_WHITE_BW           0x18   /* Black and white effect      */
#define OV2640_BLACK_WHITE_NEGATIVE     0x40   /* Negative effect             */
#define OV2640_BLACK_WHITE_BW_NEGATIVE  0x58   /* BW and Negative effect      */
#define OV2640_BLACK_WHITE_NORMAL       0x00   /* Normal effect               */

#define OV2640_CONTRAST_LEVEL0          0x3418 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL1          0x2A1C /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL2          0x2020 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL3          0x1624 /* Contrast level -2           */
#define OV2640_CONTRAST_LEVEL4          0x0C28 /* Contrast level -2           */

#define OV2640_COLOR_EFFECT_ANTIQUE     0xA640 /* Antique effect              */
#define OV2640_COLOR_EFFECT_BLUE        0x40A0 /* Blue effect                 */
#define OV2640_COLOR_EFFECT_GREEN       0x4040 /* Green effect                */
#define OV2640_COLOR_EFFECT_RED         0xC040 /* Red effect                  */   
/**
  * @}
  */
  
/** @defgroup OV2640_Exported_Functions
  * @{
  */ 
void     ov2640_Init(uint16_t DeviceAddr, uint32_t resolution);
void     ov2640_Config(uint16_t DeviceAddr, uint32_t feature, uint32_t value, uint32_t BR_value);
uint16_t ov2640_ReadID(uint16_t DeviceAddr);

void     CAMERA_IO_Init(void);
void     CAMERA_IO_Write(uint8_t addr, uint8_t reg, uint8_t value);
uint8_t  CAMERA_IO_Read(uint8_t addr, uint8_t reg);
void     CAMERA_Delay(uint32_t delay);

/* CAMERA driver structure */
extern CAMERA_DrvTypeDef   ov2640_drv;
/**
  * @}
  */    
#ifdef __cplusplus
}
#endif

#endif /* __OV2640_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
