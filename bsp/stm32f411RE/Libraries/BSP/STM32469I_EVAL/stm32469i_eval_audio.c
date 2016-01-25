/**
  ******************************************************************************
  * @file    stm32469i_eval_audio.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    29-September-2015
  * @brief   This file provides the Audio driver for the STM32469I-EVAL evaluation board.
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

/*==============================================================================
                                 User NOTES

How To use this driver:
-----------------------
   + This driver supports STM32F4xx devices on STM32469I-EVAL (MB1165) Evaluation boards.
   + Call the function BSP_AUDIO_OUT_Init(
                                    OutputDevice: physical output mode (OUTPUT_DEVICE_HEADPHONE1,
                                                  OUTPUT_DEVICE_HEADPHONE2 or OUTPUT_DEVICE_BOTH)
                                    Volume      : Initial volume to be set (0 is min (mute), 100 is max (100%)
                                    AudioFreq   : Audio frequency in Hz (8000, 16000, 22500, 32000...)
                                                  this parameter is relative to the audio file/stream type.
                                   )
      This function configures all the hardware required for the audio application (codec, I2C, SAI,
      GPIOs, DMA and interrupt if needed). This function returns AUDIO_OK if configuration is OK.
      If the returned value is different from AUDIO_OK or the function is stuck then the communication with
      the codec or the MFX has failed (try to un-plug the power or reset device in this case).
      - OUTPUT_DEVICE_HEADPHONE1 : only headphones 1 will be set as output for the audio stream.
      - OUTPUT_DEVICE_HEADPHONE2 : only headphones 2 will be set as output for the audio stream.
      - OUTPUT_DEVICE_BOTH       : both Headphones are used as outputs for the audio stream
                                 at the same time.
      Note. On STM32469I-EVAL SAI_DMA is configured in CIRCULAR mode. Due to this the application
        does NOT need to call BSP_AUDIO_OUT_ChangeBuffer() to assure straming.
   + Call the function BSP_EVAL_AUDIO_OUT_Play(
                                  pBuffer: pointer to the audio data file address
                                  Size   : size of the buffer to be sent in Bytes
                                 )
      to start playing (for the first time) from the audio file/stream.
   + Call the function BSP_AUDIO_OUT_Pause() to pause playing
   + Call the function BSP_AUDIO_OUT_Resume() to resume playing.
       Note. After calling BSP_AUDIO_OUT_Pause() function for pause, only BSP_AUDIO_OUT_Resume() should be called
          for resume (it is not allowed to call BSP_AUDIO_OUT_Play() in this case).
       Note. This function should be called only when the audio file is played or paused (not stopped).
   + For each mode, you may need to implement the relative callback functions into your code.
      The Callback functions are named AUDIO_OUT_XXX_CallBack() and only their prototypes are declared in
      the stm32469i_eval_audio.h file. (refer to the example for more details on the callbacks implementations)
   + To Stop playing, to modify the volume level, the frequency, the audio frame slot,
      the device output mode the mute or the stop, use the functions: BSP_AUDIO_OUT_SetVolume(),
      AUDIO_OUT_SetFrequency(), BSP_AUDIO_OUT_SetAudioFrameSlot(), BSP_AUDIO_OUT_SetOutputMode(),
      BSP_AUDIO_OUT_SetMute() and BSP_AUDIO_OUT_Stop().
   + The driver API and the callback functions are at the end of the stm32469i_eval_audio.h file.

Driver architecture:
--------------------
   + This driver provide the High Audio Layer: consists of the function API exported in the stm32469i_eval_audio.h file
     (BSP_AUDIO_OUT_Init(), BSP_AUDIO_OUT_Play() ...)
   + This driver provide also the Media Access Layer (MAL): which consists of functions allowing to access the media containing/
     providing the audio file/stream. These functions are also included as local functions into
     the stm32469i_eval_audio_codec.c file (I2Sx_Init(), I2Sx_DeInit(), SAIx_Init() and SAIx_DeInit())

Known Limitations:
------------------
   1- If the TDM Format used to paly in parallel 2 audio Stream (the first Stream is configured in codec SLOT0 and second
      Stream in SLOT1) the Pause/Resume, volume and mute feature will control the both streams.
   2- Parsing of audio file is not implemented (in order to determine audio file properties: Mono/Stereo, Data size,
      File size, Audio Frequency, Audio Data header size ...). The configuration is fixed for the given audio file.
   3- Supports only Stereo audio streaming.
   4- Supports only 16-bits audio data size.
==============================================================================*/

/* Includes ------------------------------------------------------------------*/
#include "stm32469i_eval_audio.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM32469I-EVAL
  * @{
  */

/** @defgroup STM32469I-EVAL_AUDIO STM32469I-EVAL AUDIO
  * @brief This file includes the low layer driver for wm8994 Audio Codec
  *        available on STM32469I-EVAL evaluation board(MB1165).
  * @{
  */

/** @defgroup STM32469I-EVAL_AUDIO_Private_Types STM32469I Eval Audio Private Types
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_Private_Defines STM32469I Eval Audio Private Defines
 *  @brief Headphone1 (CN27 of STM32469I-EVAL board) is connected to the
 *         HEADPHONE output of wm8994 Audio Codec.
 *         Headphone2 (CN26 of STM32469I-EVAL board) is connected to the
 *         SPEAKER output of wm8994 Audio Codec.
  * @{
  */
#define OUTPUT_DEVICE_HEADPHONE1 OUTPUT_DEVICE_HEADPHONE
#define OUTPUT_DEVICE_HEADPHONE2 OUTPUT_DEVICE_SPEAKER /* Headphone2 is connected to Speaker output of the wm8994 codec */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_Private_Macros STM32469I Eval Audio Private macros 
  * @{
  */
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_Private_Variables STM32469I Eval Audio Private Variables
  * @{
  */
  
/*
Note: 
  these global variables are not compliant to naming rules (upper case without "_" ), 
  but we keep this naming for compatibility, in fact these variables (not static)
  could have been used by the application, example the stm32f4xx_it.c:
    void DMA2_Stream6_IRQHandler(void)
     {  HAL_DMA_IRQHandler(haudio_out_sai.hdmatx);  }
*/
AUDIO_DrvTypeDef          *audio_drv;
SAI_HandleTypeDef         haudio_out_sai;
I2S_HandleTypeDef         haudio_in_i2s;
TIM_HandleTypeDef         haudio_tim;

PDMFilter_InitStruct Filter[2];
uint8_t Channel_Demux[128] = {
    0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
    0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
    0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
    0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
    0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
    0x00, 0x01, 0x00, 0x01, 0x02, 0x03, 0x02, 0x03,
    0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
    0x04, 0x05, 0x04, 0x05, 0x06, 0x07, 0x06, 0x07,
    0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
    0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
    0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
    0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
    0x08, 0x09, 0x08, 0x09, 0x0a, 0x0b, 0x0a, 0x0b,
    0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f,
    0x0c, 0x0d, 0x0c, 0x0d, 0x0e, 0x0f, 0x0e, 0x0f
};

uint16_t __IO AudioInVolume = DEFAULT_AUDIO_IN_VOLUME;

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_Private_Function_Prototypes STM32469I Eval Audio Private Prototypes
  * @{
  */
static void SAIx_Init(uint32_t AudioFreq);
static void SAIx_DeInit(void);
static void I2Sx_Init(uint32_t AudioFreq);
static void I2Sx_DeInit(void);
static void TIMx_IC_MspInit(TIM_HandleTypeDef *htim);
static void TIMx_IC_MspDeInit(TIM_HandleTypeDef *htim);
static void TIMx_Init(void);
static void TIMx_DeInit(void);
static void PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbr);
/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_out_Private_Functions STM32469I Eval AudioOut Private Functions
  * @{
  */

/**
  * @brief  Configures the audio peripherals.
  * @param  OutputDevice: OUTPUT_DEVICE_HEADPHONE1, OUTPUT_DEVICE_HEADPHONE2,
  *                       or OUTPUT_DEVICE_BOTH.
  * @param  Volume: Initial volume level (from 0 (Mute) to 100 (Max))
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   The I2S PLL input clock must be done in the user application.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq)
{
  uint8_t ret = AUDIO_ERROR;
  uint32_t deviceid = 0x00;

  SAIx_DeInit();
  
  /* PLL clock is set depending by the AudioFreq (44.1khz vs 48khz groups) */ 
  BSP_AUDIO_OUT_ClockConfig(&haudio_out_sai, AudioFreq, NULL);

  /* SAI data transfer preparation:
  Prepare the Media to be used for the audio transfer from memory to SAI peripheral */
  haudio_out_sai.Instance = AUDIO_SAIx;
  if(HAL_SAI_GetState(&haudio_out_sai) == HAL_SAI_STATE_RESET)
  {
    /* Init the SAI MSP: this __weak function can be redefined by the application*/
    BSP_AUDIO_OUT_MspInit(&haudio_out_sai, NULL);
  }
  SAIx_Init(AudioFreq);

  /* wm8994 codec initialization */
  deviceid = wm8994_drv.ReadID(AUDIO_I2C_ADDRESS);

  if((deviceid) == WM8994_ID)
  {
    /* Initialize the audio driver structure */
    audio_drv = &wm8994_drv;
    ret = AUDIO_OK;
  }
  else
  {
    ret = AUDIO_ERROR;
  }

  if(ret == AUDIO_OK)
  {
    /* Resets the audio codec. */
    audio_drv->Reset(AUDIO_I2C_ADDRESS);
    /* Initialize the codec internal registers */
    audio_drv->Init(AUDIO_I2C_ADDRESS, OutputDevice, Volume, AudioFreq);
  }

  return ret;
}

/**
  * @brief  Starts playing audio stream from a data buffer for a determined size.
  * @param  pBuffer: Pointer to the buffer
  * @param  Size: Number of audio data BYTES.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Play(uint16_t* pBuffer, uint32_t Size)
{
  /* Call the audio Codec Play function */
  if(audio_drv->Play(AUDIO_I2C_ADDRESS, pBuffer, Size) != 0)
  {  
    return AUDIO_ERROR;
  }
  else
  {
    /* Update the Media layer and enable it for play */  
    HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*) pBuffer, DMA_MAX(Size / AUDIODATA_SIZE));
    
    return AUDIO_OK;
  }
}

/**
  * @brief  Sends n-Bytes on the SAI interface.
  * @param  pData: pointer on data address
  * @param  Size: number of data to be written
  */
void BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size)
{
   HAL_SAI_Transmit_DMA(&haudio_out_sai, (uint8_t*) pData, Size);
}

/**
  * @brief   This function Pauses the audio file stream. In case
  *          of using DMA, the DMA Pause feature is used.
  * @warning When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play()
  *          function for resume could lead to unexpected behavior).
  * @retval  AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Pause(void)
{
  /* Call the Audio Codec Pause/Resume function */
  if(audio_drv->Pause(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer pause function */
    HAL_SAI_DMAPause(&haudio_out_sai);

    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  This function  Resumes the audio file stream.
  * @warning When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play()
  *          function for resume could lead to unexpected behavior).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Resume(void)
{
  /* Call the Audio Codec Pause/Resume function */
  if(audio_drv->Resume(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer pause/resume function */
    HAL_SAI_DMAResume(&haudio_out_sai);

    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Stops audio playing and Power down the Audio Codec.
  * @param  Option: could be one of the following parameters
  *           - CODEC_PDWN_SW: for software power off (by writing registers).
  *                            Then no need to reconfigure the Codec after power on.
  *           - CODEC_PDWN_HW: completely shut down the codec (physically).
  *                            Then need to reconfigure the Codec after power on.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option)
{
  /* Call the Media layer stop function */
  HAL_SAI_DMAStop(&haudio_out_sai);

  /* Call Audio Codec Stop function */
  if(audio_drv->Stop(AUDIO_I2C_ADDRESS, Option) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    if(Option == CODEC_PDWN_HW)
    {
      /* Wait at least 100us */
      HAL_Delay(1);
    }
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Controls the current audio volume level.
  * @param  Volume: Volume level to be set in percentage from 0% to 100% (0 for
  *         Mute and 100 for Max volume level).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetVolume(uint8_t Volume)
{
  /* Call the codec volume control function with converted volume value */
  if(audio_drv->SetVolume(AUDIO_I2C_ADDRESS, Volume) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Enables or disables the MUTE mode by software
  * @param  Cmd: Could be AUDIO_MUTE_ON to mute sound or AUDIO_MUTE_OFF to
  *         unmute the codec and restore previous volume level.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetMute(uint32_t Cmd)
{
  /* Call the Codec Mute function */
  if(audio_drv->SetMute(AUDIO_I2C_ADDRESS, Cmd) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Switch dynamically (while audio file is played) the output target
  *         (speaker or headphone).
  * @param  Output: The audio output target: OUTPUT_DEVICE_HEADPHONE1,
  *         OUTPUT_DEVICE_HEADPHONE2 or OUTPUT_DEVICE_BOTH
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output)
{
  /* Call the Codec output device function */
  if(audio_drv->SetOutputMode(AUDIO_I2C_ADDRESS, Output) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Updates the audio frequency.
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   This API should be called after the BSP_AUDIO_OUT_Init() to adjust the
  *         audio frequency.
  */
void BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq)
{ 
  /* PLL clock is set depending by the AudioFreq (44.1khz vs 48khz groups) */ 
  BSP_AUDIO_OUT_ClockConfig(&haudio_out_sai, AudioFreq, NULL);

  /* Disable SAI peripheral to allow access to SAI internal registers */
  __HAL_SAI_DISABLE(&haudio_out_sai);

  /* Update the SAI audio frequency configuration */
  haudio_out_sai.Init.AudioFrequency = AudioFreq;
  HAL_SAI_Init(&haudio_out_sai);

  /* Enable SAI peripheral to generate MCLK */
  __HAL_SAI_ENABLE(&haudio_out_sai);
}

/**
  * @brief  Updates the Audio frame slot configuration.
  * @param  AudioFrameSlot: specifies the audio Frame slot
  *         This parameter can be any value of @ref CODEC_AudioFrame_SLOT_TDMMode
  * @note   This API should be called after the BSP_AUDIO_OUT_Init() to adjust the
  *         audio frame slot.
  */
void BSP_AUDIO_OUT_SetAudioFrameSlot(uint32_t AudioFrameSlot)
{
  /* Disable SAI peripheral to allow access to SAI internal registers */
  __HAL_SAI_DISABLE(&haudio_out_sai);

  /* Update the SAI audio frame slot configuration */
  haudio_out_sai.SlotInit.SlotActive = AudioFrameSlot;
  HAL_SAI_Init(&haudio_out_sai);

  /* Enable SAI peripheral to generate MCLK */
  __HAL_SAI_ENABLE(&haudio_out_sai);
}

/**
  * @brief  Deinit the audio peripherals.
  */
void BSP_AUDIO_OUT_DeInit(void)
{
  SAIx_DeInit();
  /* DeInit the SAI MSP : this __weak function can be rewritten by the applic */
  BSP_AUDIO_OUT_MspDeInit(&haudio_out_sai, NULL);
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hsai: SAI handle
  */
void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
  /* Manage the remaining file size and new address offset: This function
     should be coded by user (its prototype is already declared in stm32469i_eval_audio.h) */
  BSP_AUDIO_OUT_TransferComplete_CallBack();
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hsai: SAI handle
  */
void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
  /* Manage the remaining file size and new address offset: This function
     should be coded by user (its prototype is already declared in stm32469i_eval_audio.h) */
  BSP_AUDIO_OUT_HalfTransfer_CallBack();
}

/**
  * @brief  SAI error callbacks.
  * @param  hsai: SAI handle
  */
void HAL_SAI_ErrorCallback(SAI_HandleTypeDef *hsai)
{
  BSP_AUDIO_OUT_Error_CallBack();
}

/**
  * @brief  Manages the DMA full Transfer complete event.
  */
__weak void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  */
__weak void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
}

/**
  * @brief  Manages the DMA FIFO error event.
  */
__weak void BSP_AUDIO_OUT_Error_CallBack(void)
{
}

/**
  * @brief  Initializes BSP_AUDIO_OUT MSP.
  * @param  hsai: SAI handle
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_OUT_MspInit(SAI_HandleTypeDef *hsai, void *Params)
{
  static DMA_HandleTypeDef hdma_sai_tx;
  GPIO_InitTypeDef  gpio_init_structure;

  /* Enable SAI clock */
  AUDIO_SAIx_CLK_ENABLE();

  /* Enable GPIO clock */
  AUDIO_SAIx_MCLK_ENABLE();
  AUDIO_SAIx_SCK_SD_FS_ENABLE();

  /* CODEC_SAI pins configuration: MCK pin -----------------------------------*/
  gpio_init_structure.Pin =  AUDIO_SAIx_MCK_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = AUDIO_SAIx_MCLK_SCK_SD_FS_AF;
  HAL_GPIO_Init(AUDIO_SAIx_MCLK_GPIO_PORT, &gpio_init_structure);

  /* CODEC_SAI pins configuration: FS, SCK, MCK and SD pins ------------------*/
  gpio_init_structure.Pin = AUDIO_SAIx_FS_PIN | AUDIO_SAIx_SCK_PIN | AUDIO_SAIx_SD_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = AUDIO_SAIx_MCLK_SCK_SD_FS_AF;
  HAL_GPIO_Init(AUDIO_SAIx_SCK_SD_FS_GPIO_PORT, &gpio_init_structure);

  /* Enable the DMA clock */
  AUDIO_SAIx_DMAx_CLK_ENABLE();

  if(hsai->Instance == AUDIO_SAIx)
  {
    /* Configure the hdma_saiTx handle parameters */
    hdma_sai_tx.Init.Channel             = AUDIO_SAIx_DMAx_CHANNEL;
    hdma_sai_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_sai_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_sai_tx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_sai_tx.Init.PeriphDataAlignment = AUDIO_SAIx_DMAx_PERIPH_DATA_SIZE;
    hdma_sai_tx.Init.MemDataAlignment    = AUDIO_SAIx_DMAx_MEM_DATA_SIZE;
    hdma_sai_tx.Init.Mode                = DMA_CIRCULAR;
    hdma_sai_tx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_sai_tx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
    hdma_sai_tx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_sai_tx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_sai_tx.Init.PeriphBurst         = DMA_PBURST_SINGLE;

    hdma_sai_tx.Instance = AUDIO_SAIx_DMAx_STREAM;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hsai, hdmatx, hdma_sai_tx);

    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_sai_tx);

    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_sai_tx);
  }

  /* SAI DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(AUDIO_SAIx_DMAx_IRQ, AUDIO_OUT_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(AUDIO_SAIx_DMAx_IRQ);
}
/**
  * @brief  Deinitializes BSP_AUDIO_OUT MSP.
  * @param  hsai: SAI handle
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_OUT_MspDeInit(SAI_HandleTypeDef *hsai, void *Params)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* SAI DMA IRQ Channel deactivation */
  HAL_NVIC_DisableIRQ(AUDIO_SAIx_DMAx_IRQ);

  if(hsai->Instance == AUDIO_SAIx)
  {
    /* Deinitialize the DMA stream */
    HAL_DMA_DeInit(hsai->hdmatx);
  }

  /* Disable SAI peripheral */
  __HAL_SAI_DISABLE(hsai);  

  /* Deactives CODEC_SAI pins FS, SCK, MCK and SD by putting them in input mode */
  gpio_init_structure.Pin = AUDIO_SAIx_MCK_PIN;
  HAL_GPIO_DeInit(AUDIO_SAIx_MCLK_GPIO_PORT, gpio_init_structure.Pin);

  gpio_init_structure.Pin = AUDIO_SAIx_FS_PIN | AUDIO_SAIx_SCK_PIN | AUDIO_SAIx_SD_PIN;
  HAL_GPIO_DeInit(AUDIO_SAIx_SCK_SD_FS_GPIO_PORT, gpio_init_structure.Pin);

    /* Disable SAI clock */
    AUDIO_SAIx_CLK_DISABLE();

    /* GPIO pins clock and DMA clock can be shut down in the applic 
       by surcgarging this __weak function */ 
}

/**
  * @brief  Clock Config.
  * @param  hsai: might be required to set audio peripheral predivider if any.
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   This API is called by BSP_AUDIO_OUT_Init() and BSP_AUDIO_OUT_SetFrequency()
  *         Being __weak it can be overwritten by the application     
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_OUT_ClockConfig(SAI_HandleTypeDef *hsai, uint32_t AudioFreq, void *Params)
{ 
  RCC_PeriphCLKInitTypeDef rcc_ex_clk_init_struct;

  HAL_RCCEx_GetPeriphCLKConfig(&rcc_ex_clk_init_struct);
  
  /* Set the PLL configuration according to the audio frequency */
  if((AudioFreq == AUDIO_FREQUENCY_11K) || (AudioFreq == AUDIO_FREQUENCY_22K) || (AudioFreq == AUDIO_FREQUENCY_44K))
  {
    /* Configure PLLI2S prescalers */
    /* PLLI2S_VCO: VCO_429M
    I2S_CLK(first level) = PLLI2S_VCO/PLLI2SQ = 429/2 = 214.5 Mhz
    I2S_CLK_x = I2S_CLK(first level)/PLLI2SDIVQ = 214.5/19 = 11.289 Mhz */
    rcc_ex_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_SAI_PLLI2S;
    rcc_ex_clk_init_struct.PLLI2S.PLLI2SN = 429;
    rcc_ex_clk_init_struct.PLLI2S.PLLI2SQ = 2;
    rcc_ex_clk_init_struct.PLLI2SDivQ = 19;
    
    HAL_RCCEx_PeriphCLKConfig(&rcc_ex_clk_init_struct);
    
  }
  else /* AUDIO_FREQUENCY_8K, AUDIO_FREQUENCY_16K, AUDIO_FREQUENCY_48K), AUDIO_FREQUENCY_96K */
  {
    /* SAI clock config 
    PLLSAI_VCO: VCO_344M 
    I2S_CLK(first level) = PLLI2S_VCO/PLLI2SQ = 344/7 = 49.142 Mhz 
    I2S_CLK_x = SAI_CLK(first level)/PLLI2SDIVQ = 49.142/1 = 49.142 Mhz */  
    rcc_ex_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_SAI_PLLI2S;
    rcc_ex_clk_init_struct.PLLI2S.PLLI2SN = 344; 
    rcc_ex_clk_init_struct.PLLI2S.PLLI2SQ = 7; 
    rcc_ex_clk_init_struct.PLLI2SDivQ = 1;       
    
    HAL_RCCEx_PeriphCLKConfig(&rcc_ex_clk_init_struct);
  }
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Initializes the Audio Codec audio interface (SAI).
  * @param  AudioFreq: Audio frequency to be configured for the SAI peripheral.
  * @note   The default SlotActive configuration is set to CODEC_AUDIOFRAME_SLOT_0123
  *         and user can update this configuration using
  */
static void SAIx_Init(uint32_t AudioFreq)
{
  /* Initialize the haudio_out_sai Instance parameter */
  haudio_out_sai.Instance = AUDIO_SAIx;

  /* Disable SAI peripheral to allow access to SAI internal registers */
  __HAL_SAI_DISABLE(&haudio_out_sai);

  /* Configure SAI_Block_x
  LSBFirst: Disabled
  DataSize: 16 */
  haudio_out_sai.Init.AudioFrequency = AudioFreq;
  haudio_out_sai.Init.ClockSource = SAI_CLKSOURCE_PLLI2S;
  haudio_out_sai.Init.AudioMode = SAI_MODEMASTER_TX;
  haudio_out_sai.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
  haudio_out_sai.Init.Protocol = SAI_FREE_PROTOCOL;
  haudio_out_sai.Init.DataSize = SAI_DATASIZE_16;
  haudio_out_sai.Init.FirstBit = SAI_FIRSTBIT_MSB;
  haudio_out_sai.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;
  haudio_out_sai.Init.Synchro = SAI_ASYNCHRONOUS;
  haudio_out_sai.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
  haudio_out_sai.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;

  /* Configure SAI_Block_x Frame
  Frame Length: 64
  Frame active Length: 32
  FS Definition: Start frame + Channel Side identification
  FS Polarity: FS active Low
  FS Offset: FS asserted one bit before the first bit of slot 0 */
  haudio_out_sai.FrameInit.FrameLength = 64;
  haudio_out_sai.FrameInit.ActiveFrameLength = 32;
  haudio_out_sai.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
  haudio_out_sai.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  haudio_out_sai.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;

  /* Configure SAI Block_x Slot
  Slot First Bit Offset: 0
  Slot Size  : 16
  Slot Number: 4
  Slot Active: All slot actives */
  haudio_out_sai.SlotInit.FirstBitOffset = 0;
  haudio_out_sai.SlotInit.SlotSize = SAI_SLOTSIZE_DATASIZE;
  haudio_out_sai.SlotInit.SlotNumber = 4;
  haudio_out_sai.SlotInit.SlotActive = CODEC_AUDIOFRAME_SLOT_0123;

  HAL_SAI_Init(&haudio_out_sai);

  /* Enable SAI peripheral to generate MCLK */
  __HAL_SAI_ENABLE(&haudio_out_sai);
}

/**
  * @brief  Deinitializes the Audio Codec audio interface (SAI).
  */
static void SAIx_DeInit(void)
{
  /* Initialize the hAudioOutSai Instance parameter */
  haudio_out_sai.Instance = AUDIO_SAIx;

  /* Disable SAI peripheral */
  __HAL_SAI_DISABLE(&haudio_out_sai);

  HAL_SAI_DeInit(&haudio_out_sai);
}

/**
  * @}
  */

/** @defgroup STM32469I-EVAL_AUDIO_in_Exported_Functions STM32469I Eval AudioIn Exported functions
  * @{
  */

/**
  * @brief  Initializes wave recording.
  * @note   This function assumes that the I2S input clock (through PLL_R in
  *         Devices RevA/Z and through dedicated PLLI2S_R in Devices RevB/Y)
  *         is already configured and ready to be used.
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral.
  * @param  BitRes: Audio frequency to be configured for the I2S peripheral.
  * @param  ChnlNbr: Audio frequency to be configured for the I2S peripheral.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr)
{
  RCC_PeriphCLKInitTypeDef rcc_ex_clk_init_struct;

  I2Sx_DeInit();
  
  HAL_RCCEx_GetPeriphCLKConfig(&rcc_ex_clk_init_struct);
  rcc_ex_clk_init_struct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
  rcc_ex_clk_init_struct.PLLI2S.PLLI2SN = 384;
  rcc_ex_clk_init_struct.PLLI2S.PLLI2SR = 2;
  HAL_RCCEx_PeriphCLKConfig(&rcc_ex_clk_init_struct);

  /* Configure the PDM library */
  PDMDecoder_Init(AudioFreq, ChnlNbr);
 
  /* Configure the I2S peripheral */
  haudio_in_i2s.Instance = AUDIO_I2Sx;
  if(HAL_I2S_GetState(&haudio_in_i2s) == HAL_I2S_STATE_RESET)
  { 
    /* Initialize the I2S Msp: this __weak function can be rewritten by the application */
    BSP_AUDIO_IN_MspInit(&haudio_in_i2s, NULL);
  }
  I2Sx_Init(AudioFreq);

  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief  Starts audio recording.
  * @param  pbuf: Main buffer pointer for the recorded data storing
  * @param  size: Current size of the recorded buffer
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Record(uint16_t* pbuf, uint32_t size)
{
  uint32_t ret = AUDIO_ERROR;

  /* Start the process receive DMA */
  HAL_I2S_Receive_DMA(&haudio_in_i2s, pbuf, size);

  /* Return AUDIO_OK when all operations are correctly done */
  ret = AUDIO_OK;

  return ret;
}

/**
  * @brief  Stops audio recording.
  * @param  None
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Stop(void)
{
  uint32_t ret = AUDIO_ERROR;

  /* Call the Media layer pause function */
  HAL_I2S_DMAPause(&haudio_in_i2s);

  /* TIMx Peripheral clock disable */
  AUDIO_TIMx_CLK_DISABLE();

  /* Return AUDIO_OK when all operations are correctly done */
  ret = AUDIO_OK;

  return ret;
}

/**
  * @brief  Pauses the audio file stream.
  * @param  None
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Pause(void)
{
  /* Call the Media layer pause function */
  HAL_I2S_DMAPause(&haudio_in_i2s);

  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief  Resumes the audio file stream.
  * @param  None    
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Resume(void)
{
  /* Call the Media layer pause/resume function */
  HAL_I2S_DMAResume(&haudio_in_i2s);

  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief  Controls the audio in volume level.
  * @param  Volume: Volume level to be set in percentage from 0% to 100% (0 for
  *         Mute and 100 for Max volume level).
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_SetVolume(uint8_t Volume)
{
  /* Set the Global variable AudioInVolume  */
  AudioInVolume = Volume;

  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief  Deinit the audio IN peripherals.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_DeInit(void)
{
  I2Sx_DeInit();
    /* DeInit the I2S MSP : this __weak function can be rewritten by the applic */
  BSP_AUDIO_IN_MspDeInit(&haudio_in_i2s, NULL);
  TIMx_DeInit();
}

/**
  * @brief  Converts audio format from PDM to PCM.
  * @param  PDMBuf: Pointer to data PDM buffer
  * @param  PCMBuf: Pointer to data PCM buffer
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_PDMToPCM(uint16_t* PDMBuf, uint16_t* PCMBuf)
{
  uint8_t app_pdm[INTERNAL_BUFF_SIZE*2];
  uint8_t byte1 = 0, byte2 = 0;
  uint32_t index = 0;

  /* PDM Demux */
  for(index = 0; index<INTERNAL_BUFF_SIZE/2; index++)
  {
    byte2 = (PDMBuf[index] >> 8)& 0xFF;
    byte1 = (PDMBuf[index] & 0xFF);
    app_pdm[(index*2)+1] = Channel_Demux[byte1 & CHANNEL_DEMUX_MASK] | Channel_Demux[byte2 & CHANNEL_DEMUX_MASK] << 4;
    app_pdm[(index*2)] = Channel_Demux[(byte1 >> 1) & CHANNEL_DEMUX_MASK] | Channel_Demux[(byte2 >> 1) & CHANNEL_DEMUX_MASK] << 4;
  }

  for(index = 0; index < DEFAULT_AUDIO_IN_CHANNEL_NBR; index++)
  {
    /* PDM to PCM filter */
    PDM_Filter_64_LSB((uint8_t*)&app_pdm[index], (uint16_t*)&(PCMBuf[index]), AudioInVolume , (PDMFilter_InitStruct *)&Filter[index]);
  }

  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

 /**
  * @brief  Rx Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Call the record update function to get the next buffer to fill and its size (size is ignored) */
  BSP_AUDIO_IN_TransferComplete_CallBack();
}

/**
  * @brief  Rx Half Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the remaining file size and new address offset: This function
     should be coded by user (its prototype is already declared in stm32469i_eval_audio.h) */
  BSP_AUDIO_IN_HalfTransfer_CallBack();
}

/**
  * @brief  I2S error callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the error generated on DMA FIFO: This function
     should be coded by user (its prototype is already declared in stm32469i_eval_audio.h) */
  BSP_AUDIO_IN_Error_Callback();
}

/**
  * @brief  User callback when record buffer is filled.
  * @param  None  
  * @retval None
  */
__weak void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{
  /* This function should be implemented by the user application.
     It is called into this driver when the current buffer is filled
     to prepare the next buffer pointer and its size. */
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  None
  * @retval None
  */
__weak void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{
  /* This function should be implemented by the user application.
     It is called into this driver when the current buffer is filled
     to prepare the next buffer pointer and its size. */
}

/**
  * @brief  Audio IN Error callback function.
  * @param  None
  * @retval None
  */
__weak void BSP_AUDIO_IN_Error_Callback(void)
{
  /* This function is called when an Interrupt due to transfer error on or peripheral
     error occurs. */
}

/**
  * @brief  BSP AUDIO IN MSP Init.
  * @param  hi2s: I2S handle
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_IN_MspInit(I2S_HandleTypeDef *hi2s, void *Params)
{
  static DMA_HandleTypeDef hdma_i2s_rx;
  GPIO_InitTypeDef  gpio_init_structure;

  /* Configure the Timer which clocks the MEMS */
  /* Moved inside MSP to allow applic to redefine the TIMx_MspInit */
  TIMx_Init();
  
  /* Enable I2S clock */
  AUDIO_I2Sx_CLK_ENABLE();

  /* Enable SCK and SD GPIO clock */
  AUDIO_I2Sx_SD_GPIO_CLK_ENABLE();
  AUDIO_I2Sx_SCK_GPIO_CLK_ENABLE();
  /* CODEC_I2S pins configuration: SCK and SD pins */
  gpio_init_structure.Pin = AUDIO_I2Sx_SCK_PIN;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_FAST;
  gpio_init_structure.Alternate = AUDIO_I2Sx_SCK_AF;
  HAL_GPIO_Init(AUDIO_I2Sx_SCK_GPIO_PORT, &gpio_init_structure);

  gpio_init_structure.Pin = AUDIO_I2Sx_SD_PIN;
  gpio_init_structure.Alternate = AUDIO_I2Sx_SD_AF;
  HAL_GPIO_Init(AUDIO_I2Sx_SD_GPIO_PORT, &gpio_init_structure);

  /* Enable the DMA clock */
  AUDIO_I2Sx_DMAx_CLK_ENABLE();

  if(hi2s->Instance == AUDIO_I2Sx)
  {
    /* Configure the hdma_i2s_rx handle parameters */   
    hdma_i2s_rx.Init.Channel             = AUDIO_I2Sx_DMAx_CHANNEL;
    hdma_i2s_rx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_i2s_rx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2s_rx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2s_rx.Init.PeriphDataAlignment = AUDIO_I2Sx_DMAx_PERIPH_DATA_SIZE;
    hdma_i2s_rx.Init.MemDataAlignment    = AUDIO_I2Sx_DMAx_MEM_DATA_SIZE;
    hdma_i2s_rx.Init.Mode                = DMA_CIRCULAR;
    hdma_i2s_rx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_i2s_rx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    hdma_i2s_rx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2s_rx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_i2s_rx.Init.PeriphBurst         = DMA_MBURST_SINGLE;

    hdma_i2s_rx.Instance = AUDIO_I2Sx_DMAx_STREAM;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmarx, hdma_i2s_rx);

    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_i2s_rx);

    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_i2s_rx);
  }

  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(AUDIO_I2Sx_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(AUDIO_I2Sx_DMAx_IRQ);
}

/**
  * @brief  DeInitializes BSP_AUDIO_IN MSP.
  * @param  hi2s: I2S handle
  * @param  Params : pointer on additional configuration parameters, can be NULL.
  */
__weak void BSP_AUDIO_IN_MspDeInit(I2S_HandleTypeDef *hi2s, void *Params)
{
  GPIO_InitTypeDef  gpio_init_structure;

  /* I2S DMA IRQ Channel deactivation */
  HAL_NVIC_DisableIRQ(AUDIO_I2Sx_DMAx_IRQ); 
  
  if(hi2s->Instance == AUDIO_I2Sx)
  {
    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(hi2s->hdmarx);
  }

 /* Disable I2S block */
  __HAL_I2S_DISABLE(hi2s);

  /* Disable pins: SCK and SD pins */
  gpio_init_structure.Pin = AUDIO_I2Sx_SCK_PIN;
  HAL_GPIO_DeInit(AUDIO_I2Sx_SCK_GPIO_PORT, gpio_init_structure.Pin);
  gpio_init_structure.Pin = AUDIO_I2Sx_SD_PIN;
  HAL_GPIO_DeInit(AUDIO_I2Sx_SD_GPIO_PORT, gpio_init_structure.Pin); 

  /* Disable I2S clock */
  AUDIO_I2Sx_CLK_DISABLE();

  /* GPIO pins clock and DMA clock can be shut down in the applic 
     by surcgarging this __weak function */ 
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Initializes the PDM library.
  * @param  AudioFreq: Audio sampling frequency
  * @param  ChnlNbr: Number of audio channels (1: mono; 2: stereo)
  * @retval None
  */
static void PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbr)
{
  uint32_t i = 0;

  /* Enable CRC peripheral to unlock the PDM library */
  __HAL_RCC_CRC_CLK_ENABLE();

  for(i = 0; i < ChnlNbr; i++)
  {
    /* Filter LP & HP Init */
    Filter[i].LP_HZ = AudioFreq/2;
    Filter[i].HP_HZ = 10;
    Filter[i].Fs = AudioFreq;
    Filter[i].Out_MicChannels = ChnlNbr;
    Filter[i].In_MicChannels = ChnlNbr;
    PDM_Filter_Init((PDMFilter_InitStruct *)&Filter[i]);
  }
}

/**
  * @brief  Initializes the Audio Codec audio interface (I2S)
  * @note   This function assumes that the I2S input clock (through dedicated PLLI2S_R)
  *         is already configured and ready to be used.
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral.
  * @retval None
  */
static void I2Sx_Init(uint32_t AudioFreq)
{
  /* Initialize the haudio_in_i2s Instance parameter */
  haudio_in_i2s.Instance = AUDIO_I2Sx;

 /* Disable I2S block */
  __HAL_I2S_DISABLE(&haudio_in_i2s);

  /* I2S2 peripheral configuration */
  haudio_in_i2s.Init.AudioFreq = 4 * AudioFreq;
  haudio_in_i2s.Init.ClockSource = I2S_CLOCK_PLL;
  haudio_in_i2s.Init.CPOL = I2S_CPOL_LOW;
  haudio_in_i2s.Init.DataFormat = I2S_DATAFORMAT_16B;
  haudio_in_i2s.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  haudio_in_i2s.Init.Mode = I2S_MODE_MASTER_RX;
  haudio_in_i2s.Init.Standard = I2S_STANDARD_LSB;
  
  /* Init the I2S */
  HAL_I2S_Init(&haudio_in_i2s); 

 /* Disable I2S block */
  __HAL_I2S_ENABLE(&haudio_in_i2s);

}

/**
  * @brief  Deinitializes the Audio Codec audio interface (I2S).
  * @param  None
  * @retval None
  */
static void I2Sx_DeInit(void)
{
  /* Initialize the hAudioInI2s Instance parameter */
  haudio_in_i2s.Instance = AUDIO_I2Sx;

 /* Disable I2S block */
  __HAL_I2S_DISABLE(&haudio_in_i2s);

  /* DeInit the I2S */
  HAL_I2S_DeInit(&haudio_in_i2s); 
}


/**
  * @brief  Initializes the TIM INput Capture MSP.
  * @param  htim: TIM handle
  * @retval None
  */
static void TIMx_IC_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   gpio_init_structure;

  /* Enable peripherals and GPIO Clocks --------------------------------------*/
  /* TIMx Peripheral clock enable */
  AUDIO_TIMx_CLK_ENABLE();

  /* Enable GPIO Channels Clock */
  AUDIO_TIMx_GPIO_CLK_ENABLE();

  /* Configure I/Os ----------------------------------------------------------*/
  /* Common configuration for all channels */
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = AUDIO_TIMx_AF;

  /* Configure TIM input channel */
  gpio_init_structure.Pin = AUDIO_TIMx_IN_GPIO_PIN;
  HAL_GPIO_Init(AUDIO_TIMx_GPIO_PORT, &gpio_init_structure);

  /* Configure TIM output channel */
  gpio_init_structure.Pin = AUDIO_TIMx_OUT_GPIO_PIN;
  HAL_GPIO_Init(AUDIO_TIMx_GPIO_PORT, &gpio_init_structure);

}

/**
  * @brief  Initializes the TIM INput Capture MSP.
  * @param  htim: TIM handle
  * @retval None
  */
static void TIMx_IC_MspDeInit(TIM_HandleTypeDef *htim)
{
    /* Disable TIMx Peripheral clock  */
    AUDIO_TIMx_CLK_DISABLE();

    /* GPIO pins clock and DMA clock can be shut down in the applic 
       by surcgarging this __weak function */ 
}

/**
  * @brief  Configure TIM as a clock divider by 2.
  *         I2S_SCK is externally connected to TIMx input channel
  * @param  None
  * @retval None
  */
static void TIMx_Init(void)
{
  TIM_IC_InitTypeDef     s_ic_config;
  TIM_OC_InitTypeDef     s_oc_config;
  TIM_ClockConfigTypeDef s_clk_source_config;
  TIM_SlaveConfigTypeDef s_slave_config;
  
  /* Configure the TIM peripheral --------------------------------------------*/
  /* Set TIMx instance */
  haudio_tim.Instance = AUDIO_TIMx;
  /* Timer Input Capture Configuration Structure declaration */
   /* Initialize TIMx peripheral as follow:
       + Period = 0xFFFF
       + Prescaler = 0
       + ClockDivision = 0
       + Counter direction = Up
  */
  haudio_tim.Init.Period        = 1;
  haudio_tim.Init.Prescaler     = 0;
  haudio_tim.Init.ClockDivision = 0;
  haudio_tim.Init.CounterMode   = TIM_COUNTERMODE_UP;

  /* Initialize the TIMx peripheral with the structure above */
  TIMx_IC_MspInit(&haudio_tim);
  HAL_TIM_IC_Init(&haudio_tim);

  /* Configure the Input Capture channel -------------------------------------*/
  /* Configure the Input Capture of channel 2 */
  s_ic_config.ICPolarity  = TIM_ICPOLARITY_FALLING;
  s_ic_config.ICSelection = TIM_ICSELECTION_DIRECTTI;
  s_ic_config.ICPrescaler = TIM_ICPSC_DIV1;
  s_ic_config.ICFilter    = 0;
  HAL_TIM_IC_ConfigChannel(&haudio_tim, &s_ic_config, AUDIO_TIMx_IN_CHANNEL);
  
  /* Select external clock mode 1 */
  s_clk_source_config.ClockSource = TIM_CLOCKSOURCE_ETRMODE1;
  s_clk_source_config.ClockPolarity = TIM_CLOCKPOLARITY_NONINVERTED;
  s_clk_source_config.ClockPrescaler = TIM_CLOCKPRESCALER_DIV1;
  s_clk_source_config.ClockFilter = 0;   
  HAL_TIM_ConfigClockSource(&haudio_tim, &s_clk_source_config);
  
  /* Select Input Channel as input trigger */
  s_slave_config.InputTrigger = TIM_TS_TI1FP1;
  s_slave_config.SlaveMode = TIM_SLAVEMODE_EXTERNAL1;
  s_slave_config.TriggerPolarity = TIM_TRIGGERPOLARITY_NONINVERTED;
  s_slave_config.TriggerPrescaler = TIM_CLOCKPRESCALER_DIV1;
  s_slave_config.TriggerFilter = 0;
  HAL_TIM_SlaveConfigSynchronization(&haudio_tim, &s_slave_config);
  
  /* Output Compare PWM Mode configuration: Channel2 */
  s_oc_config.OCMode = TIM_OCMODE_PWM1;
  s_oc_config.OCIdleState = TIM_OCIDLESTATE_SET;
  s_oc_config.Pulse = 1;
  s_oc_config.OCPolarity = TIM_OCPOLARITY_HIGH;
  s_oc_config.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  s_oc_config.OCFastMode = TIM_OCFAST_DISABLE;
  s_oc_config.OCNIdleState = TIM_OCNIDLESTATE_SET;
  
  /* Initialize the TIM3 Channel2 with the structure above */
  HAL_TIM_PWM_ConfigChannel(&haudio_tim, &s_oc_config, AUDIO_TIMx_OUT_CHANNEL);

  /* Start the TIM3 Channel2 */
  HAL_TIM_PWM_Start(&haudio_tim, AUDIO_TIMx_OUT_CHANNEL);

  /* Start the TIM3 Channel1 */
  HAL_TIM_IC_Start(&haudio_tim, AUDIO_TIMx_IN_CHANNEL);
}

/**
  * @brief  Configure TIM as a clock divider by 2.
  *         I2S_SCK is externally connected to TIMx input channel
  * @param  None
  * @retval None
  */
static void TIMx_DeInit(void)
{
  haudio_tim.Instance = AUDIO_TIMx;
  
  /* Stop the TIM3 Channel2 */
  HAL_TIM_PWM_Stop(&haudio_tim, AUDIO_TIMx_OUT_CHANNEL);
  /* Stop the TIM3 Channel1 */
  HAL_TIM_IC_Stop(&haudio_tim, AUDIO_TIMx_IN_CHANNEL);

  HAL_TIM_IC_DeInit(&haudio_tim);
  
  /* Initialize the TIMx peripheral with the structure above */
  TIMx_IC_MspDeInit(&haudio_tim);
}

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
