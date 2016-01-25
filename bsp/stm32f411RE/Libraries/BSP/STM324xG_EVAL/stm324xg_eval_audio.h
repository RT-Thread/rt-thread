/**
  ******************************************************************************
  * @file    stm324xg_eval_audio.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm324xg_eval_audio.c driver.
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
#ifndef __STM324xG_EVAL_AUDIO_H
#define __STM324xG_EVAL_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "../Components/cs43l22/cs43l22.h"
#include "stm324xg_eval.h"

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM324xG_EVAL
  * @{
  */
    
/** @defgroup STM324xG_EVAL_AUDIO
  * @{
  */

/** @defgroup STM324xG_EVAL_AUDIO_Exported_Types
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Exported_Constants
  * @{
  */
/* Audio Reset Pin definition */
#define AUDIO_RESET_PIN                     IO_PIN_2
    
/* I2S peripheral configuration defines */
#define AUDIO_I2Sx                          SPI2
#define AUDIO_I2Sx_CLK_ENABLE()             __SPI2_CLK_ENABLE()
#define AUDIO_I2Sx_SCK_SD_WS_AF             GPIO_AF5_SPI2
#define AUDIO_I2Sx_SCK_SD_WS_CLK_ENABLE()   __GPIOI_CLK_ENABLE()
#define AUDIO_I2Sx_MCK_CLK_ENABLE()         __GPIOC_CLK_ENABLE()
#define AUDIO_I2Sx_WS_PIN                   GPIO_PIN_0
#define AUDIO_I2Sx_SCK_PIN                  GPIO_PIN_1
#define AUDIO_I2Sx_SD_PIN                   GPIO_PIN_3
#define AUDIO_I2Sx_MCK_PIN                  GPIO_PIN_6
#define AUDIO_I2Sx_SCK_SD_WS_GPIO_PORT      GPIOI
#define AUDIO_I2Sx_MCK_GPIO_PORT            GPIOC

/* I2S DMA Stream definitions */
#define AUDIO_I2Sx_DMAx_CLK_ENABLE()        __DMA1_CLK_ENABLE()
#define AUDIO_I2Sx_DMAx_STREAM              DMA1_Stream4
#define AUDIO_I2Sx_DMAx_CHANNEL             DMA_CHANNEL_0
#define AUDIO_I2Sx_DMAx_IRQ                 DMA1_Stream4_IRQn
#define AUDIO_I2Sx_DMAx_PERIPH_DATA_SIZE    DMA_PDATAALIGN_HALFWORD
#define AUDIO_I2Sx_DMAx_MEM_DATA_SIZE       DMA_MDATAALIGN_HALFWORD
#define DMA_MAX_SZE                         0xFFFF
   
#define AUDIO_I2Sx_DMAx_IRQHandler          DMA1_Stream4_IRQHandler

/*------------------------------------------------------------------------------
             CONFIGURATION: Audio Driver Configuration parameters
------------------------------------------------------------------------------*/
/* Select the interrupt preemption priority for the DMA interrupt */
#define AUDIO_IRQ_PREPRIO           5   /* Select the preemption priority level(0 is the highest) */

#define AUDIODATA_SIZE              2   /* 16-bits audio data size */

/* Audio status definition */     
#define AUDIO_OK         0x00
#define AUDIO_ERROR      0x01
#define AUDIO_TIMEOUT    0x02

/*------------------------------------------------------------------------------
                    OPTIONAL Configuration defines parameters
------------------------------------------------------------------------------*/
/* Delay for the Codec to be correctly reset */
#define CODEC_RESET_DELAY               5

/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Exported_Macros
  * @{
  */
#define DMA_MAX(x)           (((x) <= DMA_MAX_SZE)? (x):DMA_MAX_SZE)
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Exported_Functions
  * @{
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_Play(uint16_t *pBuffer, uint32_t Size);
void    BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size);
uint8_t BSP_AUDIO_OUT_Pause(void);
uint8_t BSP_AUDIO_OUT_Resume(void);
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option);
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume);
void    BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd);
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred.*/
void    BSP_AUDIO_OUT_TransferComplete_CallBack(void);

/* This function is called when half of the requested buffer has been transferred. */
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_OUT_Error_CallBack(void);

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

#endif /* __STM324xG_EVAL_AUDIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
