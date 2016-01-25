/**
  ******************************************************************************
  * @file    wm8994.h
  * @author  MCD Application Team
  * @version V2.0.0
  * @date    24-June-2015
  * @brief   This file contains all the functions prototypes for the 
  *          wm8994.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
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
#ifndef __WM8994_H
#define __WM8994_H

/* Includes ------------------------------------------------------------------*/
#include "../Common/audio.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Component
  * @{
  */ 
  
/** @addtogroup WM8994
  * @{
  */

/** @defgroup WM8994_Exported_Types
  * @{
  */

/**
  * @}
  */

/** @defgroup WM8994_Exported_Constants
  * @{
  */ 

/******************************************************************************/
/***************************  Codec User defines ******************************/
/******************************************************************************/
/* Codec output DEVICE */
#define OUTPUT_DEVICE_SPEAKER                 ((uint16_t)0x0001)
#define OUTPUT_DEVICE_HEADPHONE               ((uint16_t)0x0002)
#define OUTPUT_DEVICE_BOTH                    ((uint16_t)0x0003)
#define OUTPUT_DEVICE_AUTO                    ((uint16_t)0x0004)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_1     ((uint16_t)0x0100)
#define INPUT_DEVICE_DIGITAL_MICROPHONE_2     ((uint16_t)0x0200)
#define INPUT_DEVICE_INPUT_LINE_1             ((uint16_t)0x0300)
#define INPUT_DEVICE_INPUT_LINE_2             ((uint16_t)0x0400)

/* Volume Levels values */
#define DEFAULT_VOLMIN                0x00
#define DEFAULT_VOLMAX                0xFF
#define DEFAULT_VOLSTEP               0x04

#define AUDIO_PAUSE                   0
#define AUDIO_RESUME                  1

/* Codec POWER DOWN modes */
#define CODEC_PDWN_HW                 1
#define CODEC_PDWN_SW                 2

/* MUTE commands */
#define AUDIO_MUTE_ON                 1
#define AUDIO_MUTE_OFF                0

/* AUDIO FREQUENCY */
#define AUDIO_FREQUENCY_192K          ((uint32_t)192000)
#define AUDIO_FREQUENCY_96K           ((uint32_t)96000)
#define AUDIO_FREQUENCY_48K           ((uint32_t)48000)
#define AUDIO_FREQUENCY_44K           ((uint32_t)44100)
#define AUDIO_FREQUENCY_32K           ((uint32_t)32000)
#define AUDIO_FREQUENCY_22K           ((uint32_t)22050)
#define AUDIO_FREQUENCY_16K           ((uint32_t)16000)
#define AUDIO_FREQUENCY_11K           ((uint32_t)11025)
#define AUDIO_FREQUENCY_8K            ((uint32_t)8000)  

#define VOLUME_CONVERT(Volume)        (((Volume) > 100)? 100:((uint8_t)(((Volume) * 63) / 100)))
#define VOLUME_IN_CONVERT(Volume)     (((Volume) >= 100)? 239:((uint8_t)(((Volume) * 240) / 100)))

/******************************************************************************/
/****************************** REGISTER MAPPING ******************************/
/******************************************************************************/
/** 
  * @brief  WM8994 ID  
  */  
#define  WM8994_ID    0x8994

/**
  * @brief Device ID Register: Reading from this register will indicate device 
  *                            family ID 8994h
  */
#define WM8994_CHIPID_ADDR                  0x00

/**
  * @}
  */ 

/** @defgroup WM8994_Exported_Macros
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup WM8994_Exported_Functions
  * @{
  */
    
/*------------------------------------------------------------------------------
                           Audio Codec functions 
------------------------------------------------------------------------------*/
/* High Layer codec functions */
uint32_t wm8994_Init(uint16_t DeviceAddr, uint16_t OutputInputDevice, uint8_t Volume, uint32_t AudioFreq);
void     wm8994_DeInit(void);
uint32_t wm8994_ReadID(uint16_t DeviceAddr);
uint32_t wm8994_Play(uint16_t DeviceAddr, uint16_t* pBuffer, uint16_t Size);
uint32_t wm8994_Pause(uint16_t DeviceAddr);
uint32_t wm8994_Resume(uint16_t DeviceAddr);
uint32_t wm8994_Stop(uint16_t DeviceAddr, uint32_t Cmd);
uint32_t wm8994_SetVolume(uint16_t DeviceAddr, uint8_t Volume);
uint32_t wm8994_SetMute(uint16_t DeviceAddr, uint32_t Cmd);
uint32_t wm8994_SetOutputMode(uint16_t DeviceAddr, uint8_t Output);
uint32_t wm8994_SetFrequency(uint16_t DeviceAddr, uint32_t AudioFreq);
uint32_t wm8994_Reset(uint16_t DeviceAddr);

/* AUDIO IO functions */
void    AUDIO_IO_Init(void);
void    AUDIO_IO_DeInit(void);
void    AUDIO_IO_Write(uint8_t Addr, uint16_t Reg, uint16_t Value);
uint8_t AUDIO_IO_Read(uint8_t Addr, uint16_t Reg);
void    AUDIO_IO_Delay(uint32_t Delay);

/* Audio driver structure */
extern AUDIO_DrvTypeDef   wm8994_drv;

#endif /* __WM8994_H */

/**
  * @}
  */ 

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
