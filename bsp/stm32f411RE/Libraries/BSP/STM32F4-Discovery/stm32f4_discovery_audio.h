/**
  ******************************************************************************
  * @file    stm32f4_discovery_audio.h
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file contains the common defines and functions prototypes for
  *          stm32f4_discovery_audio.c driver.
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
#ifndef __STM32F4_DISCOVERY_AUDIO_H
#define __STM32F4_DISCOVERY_AUDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
/* Include audio component Driver */
#include "../Components/cs43l22/cs43l22.h"

#include "stm32f4_discovery.h"
#include "../../../Middlewares/ST/STM32_Audio/Addons/PDM/pdm_filter.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32F4_DISCOVERY
  * @{
  */
    
/** @defgroup STM32F4_DISCOVERY_AUDIO
  * @{
  */    


/** @defgroup STM32F4_DISCOVERY_AUDIO_Exported_Types
  * @{
  */
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_AUDIO_OUT_Exported_Constants
  * @{
  */ 

/*------------------------------------------------------------------------------
                          AUDIO OUT CONFIGURATION
------------------------------------------------------------------------------*/

/* I2S peripheral configuration defines */
#define I2S3                            SPI3
#define I2S3_CLK_ENABLE()               __SPI3_CLK_ENABLE()
#define I2S3_SCK_SD_WS_AF               GPIO_AF6_SPI3
#define I2S3_SCK_SD_CLK_ENABLE()        __GPIOC_CLK_ENABLE()
#define I2S3_MCK_CLK_ENABLE()           __GPIOC_CLK_ENABLE()
#define I2S3_WS_CLK_ENABLE()            __GPIOA_CLK_ENABLE()
#define I2S3_WS_PIN                     GPIO_PIN_4
#define I2S3_SCK_PIN                    GPIO_PIN_10
#define I2S3_SD_PIN                     GPIO_PIN_12
#define I2S3_MCK_PIN                    GPIO_PIN_7
#define I2S3_SCK_SD_GPIO_PORT           GPIOC
#define I2S3_WS_GPIO_PORT               GPIOA
#define I2S3_MCK_GPIO_PORT              GPIOC

/* I2S DMA Stream definitions */
#define I2S3_DMAx_CLK_ENABLE()          __DMA1_CLK_ENABLE()
#define I2S3_DMAx_STREAM                DMA1_Stream7
#define I2S3_DMAx_CHANNEL               DMA_CHANNEL_0
#define I2S3_DMAx_IRQ                   DMA1_Stream7_IRQn
#define I2S3_DMAx_PERIPH_DATA_SIZE      DMA_PDATAALIGN_HALFWORD
#define I2S3_DMAx_MEM_DATA_SIZE         DMA_MDATAALIGN_HALFWORD
#define DMA_MAX_SZE                     0xFFFF

#define I2S3_IRQHandler                 DMA1_Stream7_IRQHandler

/* Select the interrupt preemption priority and subpriority for the DMA interrupt */
#define AUDIO_OUT_IRQ_PREPRIO           5   /* Select the preemption priority level(0 is the highest) */

/*------------------------------------------------------------------------------
                          AUDIO IN CONFIGURATION
------------------------------------------------------------------------------*/
/* SPI Configuration defines */
#define I2S2                            SPI2
#define I2S2_CLK_ENABLE()               __SPI2_CLK_ENABLE()
#define I2S2_SCK_PIN                    GPIO_PIN_10
#define I2S2_SCK_GPIO_PORT              GPIOB
#define I2S2_SCK_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define I2S2_SCK_AF                     GPIO_AF5_SPI2

#define I2S2_MOSI_PIN                   GPIO_PIN_3
#define I2S2_MOSI_GPIO_PORT             GPIOC
#define I2S2_MOSI_GPIO_CLK_ENABLE()     __GPIOC_CLK_ENABLE()
#define I2S2_MOSI_AF                    GPIO_AF5_SPI2

/* I2S DMA Stream Rx definitions */
#define I2S2_DMAx_CLK_ENABLE()          __DMA1_CLK_ENABLE()
#define I2S2_DMAx_STREAM                DMA1_Stream3
#define I2S2_DMAx_CHANNEL               DMA_CHANNEL_0
#define I2S2_DMAx_IRQ                   DMA1_Stream3_IRQn
#define I2S2_DMAx_PERIPH_DATA_SIZE      DMA_PDATAALIGN_HALFWORD
#define I2S2_DMAx_MEM_DATA_SIZE         DMA_MDATAALIGN_HALFWORD
   
#define I2S2_IRQHandler                 DMA1_Stream3_IRQHandler

/* Select the interrupt preemption priority and subpriority for the IT/DMA interrupt */
#define AUDIO_IN_IRQ_PREPRIO            6   /* Select the preemption priority level(0 is the highest) */

/*------------------------------------------------------------------------------
             CONFIGURATION: Audio Driver Configuration parameters
------------------------------------------------------------------------------*/

#define AUDIODATA_SIZE                  2   /* 16-bits audio data size */

/* Audio status definition */     
#define AUDIO_OK                        0
#define AUDIO_ERROR                     1
#define AUDIO_TIMEOUT                   2

/* AudioFreq * DataSize (2 bytes) * NumChannels (Stereo: 2) */
#define DEFAULT_AUDIO_IN_FREQ                 I2S_AUDIOFREQ_16K
#define DEFAULT_AUDIO_IN_BIT_RESOLUTION       16
#define DEFAULT_AUDIO_IN_CHANNEL_NBR          1 /* Mono = 1, Stereo = 2 */
#define DEFAULT_AUDIO_IN_VOLUME               64

/* PDM buffer input size */
#define INTERNAL_BUFF_SIZE                    128*DEFAULT_AUDIO_IN_FREQ/16000*DEFAULT_AUDIO_IN_CHANNEL_NBR
/* PCM buffer output size */
#define PCM_OUT_SIZE                          DEFAULT_AUDIO_IN_FREQ/1000
#define CHANNEL_DEMUX_MASK                    0x55
   
/*------------------------------------------------------------------------------
                    OPTIONAL Configuration defines parameters
------------------------------------------------------------------------------*/

/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_AUDIO_Exported_Variables 
  * @{
  */ 
extern __IO uint16_t AudioInVolume;
/**
  * @}
  */ 

/** @defgroup STM32F4_DISCOVERY_AUDIO_Exported_Macros AUDIO_Exported_Macros
  * @{
  */
#define DMA_MAX(_X_)                (((_X_) <= DMA_MAX_SZE)? (_X_):DMA_MAX_SZE)
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_AUDIO_OUT_Exported_Functions 
  * @{
  */ 
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size);
void    BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size);
uint8_t BSP_AUDIO_OUT_Pause(void);
uint8_t BSP_AUDIO_OUT_Resume(void);
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option);
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume);
void    BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq);
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd);
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output);

/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function is called when the requested data has been completely transferred. */
void    BSP_AUDIO_OUT_TransferComplete_CallBack(void);

/* This function is called when half of the requested buffer has been transferred. */
void    BSP_AUDIO_OUT_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_OUT_Error_CallBack(void);
/**
  * @}
  */

/** @defgroup STM32F4_DISCOVERY_AUDIO_IN_Exported_Functions
  * @{
  */ 
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr);
uint8_t BSP_AUDIO_IN_Record(uint16_t *pData, uint32_t Size);
uint8_t BSP_AUDIO_IN_Stop(void);
uint8_t BSP_AUDIO_IN_Pause(void);
uint8_t BSP_AUDIO_IN_Resume(void);
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume);
uint8_t BSP_AUDIO_IN_PDMToPCM(uint16_t *PDMBuf, uint16_t *PCMBuf);
/* User Callbacks: user has to implement these functions in his code if they are needed. */
/* This function should be implemented by the user application.
   It is called into this driver when the current buffer is filled to prepare the next
   buffer pointer and its size. */
void    BSP_AUDIO_IN_TransferComplete_CallBack(void);
void    BSP_AUDIO_IN_HalfTransfer_CallBack(void);

/* This function is called when an Interrupt due to transfer error on or peripheral
   error occurs. */
void    BSP_AUDIO_IN_Error_Callback(void);

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
   
#endif /* __STM32F4_DISCOVERY_AUDIO_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
