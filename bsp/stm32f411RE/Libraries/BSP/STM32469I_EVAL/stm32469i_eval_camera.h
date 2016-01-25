/**
  ******************************************************************************
  * @file    stm32469i_eval_camera.h
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32469i_eval_camera.c driver.
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
#ifndef __STM32469I_EVAL_CAMERA_H
#define __STM32469I_EVAL_CAMERA_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Include Camera component Driver */
#include "../Components/s5k5cag/s5k5cag.h"

/* Include IO Driver */
#include "stm32469i_eval_io.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @addtogroup STM32469I-EVAL_CAMERA
  * @{
  */

/** @defgroup STM32469I-EVAL_CAMERA_Exported_Types STM32469I EVAL Camera Exported Types
  * @{
  */

/**
  * @brief  Camera State structures definition
  */
typedef enum
{
  CAMERA_OK            = 0x00,
  CAMERA_ERROR         = 0x01,
  CAMERA_TIMEOUT       = 0x02,
  CAMERA_NOT_DETECTED  = 0x03,
  CAMERA_NOT_SUPPORTED = 0x04

} Camera_StatusTypeDef;

/**
  * @brief  Camera Image rotation definition
  *         in frame buffer for LCD Display.
  */
typedef enum
{
  CAMERA_NO_ROTATION       = 0x00,
  CAMERA_ROTATION_90       = 0x01,
  CAMERA_ROTATION_INVALID  = 0x02

} Camera_RotationTypeDef;

#define RESOLUTION_R160x120      CAMERA_R160x120      /* QQVGA Resolution     */
#define RESOLUTION_R320x240      CAMERA_R320x240      /* QVGA Resolution      */
#define RESOLUTION_R480x272      CAMERA_R480x272      /* 480x272 Resolution   */
#define RESOLUTION_R640x480      CAMERA_R640x480      /* VGA Resolution       */

#define CAMERA_VGA_RES_X          640
#define CAMERA_VGA_RES_Y          480
#define CAMERA_480x272_RES_X      480
#define CAMERA_480x272_RES_Y      272
#define CAMERA_QVGA_RES_X         320
#define CAMERA_QVGA_RES_Y         240
#define CAMERA_QQVGA_RES_X        160
#define CAMERA_QQVGA_RES_Y        120

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_CAMERA_Exported_Constants STM32469I-EVAL CAMERA Exported Constants
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_CAMERA_Exported_Functions STM32469I-EVAL CAMERA Exported Functions
  * @{
  */

uint8_t  BSP_CAMERA_SetRotation(uint32_t rotation);
uint32_t BSP_CAMERA_GetRotation(void);

uint8_t BSP_CAMERA_Init(uint32_t Resolution);
uint8_t BSP_CAMERA_DeInit(void);
void    BSP_CAMERA_ContinuousStart(uint8_t *buff);
void    BSP_CAMERA_SnapshotStart(uint8_t *buff);
void    BSP_CAMERA_Suspend(void);
void    BSP_CAMERA_Resume(void);
uint8_t BSP_CAMERA_Stop(void);
void    BSP_CAMERA_HwReset(void);
void    BSP_CAMERA_PwrDown(void);
void    BSP_CAMERA_LineEventCallback(void);
void    BSP_CAMERA_VsyncEventCallback(void);
void    BSP_CAMERA_FrameEventCallback(void);
void    BSP_CAMERA_ErrorCallback(void);

/* Camera features functions prototype */
void    BSP_CAMERA_ContrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level);
void    BSP_CAMERA_BlackWhiteConfig(uint32_t Mode);
void    BSP_CAMERA_ColorEffectConfig(uint32_t Effect);

/* To be called in DCMI_IRQHandler function */
void    BSP_CAMERA_IRQHandler(void);

/* To be called in DMA2_Stream1_IRQHandler function */
void    BSP_CAMERA_DMA_IRQHandler(void);
/* These functions can be modified in case the current settings (e.g. DMA stream)
   need to be changed for specific application needs */
void BSP_CAMERA_MspInit(DCMI_HandleTypeDef *hdcmi, void *Params);
void BSP_CAMERA_MspDeInit(DCMI_HandleTypeDef *hdcmi, void *Params);

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

#ifdef __cplusplus
}
#endif

#endif /* __STM32469I_EVAL_CAMERA_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
