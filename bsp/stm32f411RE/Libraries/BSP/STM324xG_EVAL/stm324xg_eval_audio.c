/**
  ******************************************************************************
  * @file    stm324xg_eval_audio.c
  * @author  MCD Application Team
  * @version V2.1.0
  * @date    14-August-2015
  * @brief   This file provides the Audio driver for the STM324xG-EVAL evaluation
  *          board.  
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
   + This driver supports STM32F4xx devices on STM324xG-EVAL Evaluation board.
   + Call the function BSP_AUDIO_OUT_Init(
                                    OutputDevice: physical output mode (OUTPUT_DEVICE_SPEAKER, 
                                                 OUTPUT_DEVICE_HEADPHONE, OUTPUT_DEVICE_AUTO or 
                                                 OUTPUT_DEVICE_BOTH)
                                    Volume: initial volume to be set (0 is min (mute), 100 is max (100%)
                                    AudioFreq: Audio frequency in Hz (8000, 16000, 22500, 32000 ...)
                                     this parameter is relative to the audio file/stream type.
                                    )
      This function configures all the hardware required for the audio application (codec, I2C, I2S, 
      GPIOs, DMA and interrupt if needed). This function returns 0 if configuration is OK.
      If the returned value is different from 0 or the function is stuck then the communication with
      the codec or the IOExpander has failed (try to un-plug the power or reset device in this case).
      - OUTPUT_DEVICE_SPEAKER: only speaker will be set as output for the audio stream.
      - OUTPUT_DEVICE_HEADPHONE: only headphones will be set as output for the audio stream.
      - OUTPUT_DEVICE_AUTO: Selection of output device is made through external switch (implemented 
         into the audio jack on the evaluation board). When the Headphone is connected it is used
         as output. When the headphone is disconnected from the audio jack, the output is
         automatically switched to Speaker.
      - OUTPUT_DEVICE_BOTH: both Speaker and Headphone are used as outputs for the audio stream
         at the same time.
   + Call the function BSP_AUDIO_OUT_Play(
                                  pBuffer: pointer to the audio data file address
                                  Size: size of the buffer to be sent in Bytes
                                 )
      to start playing (for the first time) from the audio file/stream.
   + Call the function BSP_AUDIO_OUT_Pause() to pause playing 
   + Call the function BSP_AUDIO_OUT_Resume() to resume playing.
       Note. After calling BSP_AUDIO_OUT_Pause() function for pause, only BSP_AUDIO_OUT_Resume() should be called
          for resume (it is not allowed to call BSP_AUDIO_OUT_Play() in this case).
       Note. This function should be called only when the audio file is played or paused (not stopped).
   + For each mode, you may need to implement the relative callback functions into your code.
      The Callback functions are named AUDIO_OUT_XXX_CallBack() and only their prototypes are declared in 
      the stm324xg_eval_audio.h file. (refer to the example for more details on the callbacks implementations)
   + To Stop playing, to modify the volume level or to mute, use the functions
       BSP_AUDIO_OUT_Stop(), BSP_AUDIO_OUT_SetVolume(), AUDIO_OUT_SetFrequency() BSP_AUDIO_OUT_SetOutputMode and BSP_AUDIO_OUT_SetMute().
   + The driver API and the callback functions are at the end of the stm324xg_eval_audio.h file.

Driver architecture:
 -------------------
   + This driver provide the High Audio Layer: consists of the function API exported in the stm324xg_eval_audio.h file
     (BSP_AUDIO_OUT_Init(), BSP_AUDIO_OUT_Play() ...)
   + This driver provide also the Media Access Layer (MAL): which consists of functions allowing to access the media containing/
     providing the audio file/stream. These functions are also included as local functions into
     the stm324xg_eval_audio_codec.c file (I2Sx_MspInit() and I2Sx_Init())

 Known Limitations:
-------------------
   1- When using the Speaker, if the audio file quality is not high enough, the speaker output
      may produce high and uncomfortable noise level. To avoid this issue, to use speaker
      output properly, try to increase audio file sampling rate (typically higher than 48KHz).
      This operation will lead to larger file size.
   2- Communication with the audio codec (through I2C) may be corrupted if it is interrupted by some
      user interrupt routines (in this case, interrupts could be disabled just before the start of 
      communication then re-enabled when it is over). Note that this communication is only done at
      the configuration phase (BSP_AUDIO_OUT_Init() or BSP_AUDIO_OUT_Stop()) and when Volume control modification is 
      performed (BSP_AUDIO_OUT_SetVolume() or AUDIO_OUT_Mute() or BSP_AUDIO_OUT_SetOutputMode()).
      When the audio data is played, no communication is required with the audio codec.
   3- Parsing of audio file is not implemented (in order to determine audio file properties: Mono/Stereo, Data size, 
      File size, Audio Frequency, Audio Data header size ...). The configuration is fixed for the given audio file.
   4- Supports only Stereo audio streaming. To play mono audio streams, each data should be sent twice 
      on the I2S or should be duplicated on the source buffer. Or convert the stream in stereo before playing.
   5- Supports only 16-bits audio data size.
==============================================================================*/

/* Includes ------------------------------------------------------------------*/
#include "stm324xg_eval_audio.h"
#include "stm324xg_eval_io.h" /* IOExpander driver is included in order to allow 
                                 CS43L22 codec reset pin managment on the evaluation board */
/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM324xG_EVAL
  * @{
  */ 
  
/** @defgroup STM324xG_EVAL_AUDIO
  * @brief This file includes the low layer audio driver available on STM324xG-EVAL
  *        evaluation board.
  * @{
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Private_Types
  * @{
  */ 
/**
  * @}
  */ 
  
/** @defgroup STM324xG_EVAL_AUDIO_Private_Defines
  * @{
  */
/* These PLL parameters are valide when the f(VCO clock) = 1Mhz */
const uint32_t I2SFreq[8] = {8000, 11025, 16000, 22050, 32000, 44100, 48000, 96000};
const uint32_t I2SPLLN[8] = {256, 429, 213, 429, 426, 271, 258, 344};
const uint32_t I2SPLLR[8] = {5, 4, 4, 4, 4, 6, 3, 1};
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM324xG_EVAL_AUDIO_Private_Variables
  * @{
  */
AUDIO_DrvTypeDef   *audio_drv;
I2S_HandleTypeDef  haudio_i2s;
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Private_Function_Prototypes
  * @{
  */
static void CODEC_Reset(void);
static void I2Sx_MspInit(void);
static void I2Sx_Init(uint32_t AudioFreq);
/**
  * @}
  */ 

/** @defgroup STM324xG_EVAL_AUDIO_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures the audio peripherals.
  * @param  OutputDevice: OUTPUT_DEVICE_SPEAKER, OUTPUT_DEVICE_HEADPHONE,
  *                       OUTPUT_DEVICE_BOTH or OUTPUT_DEVICE_AUTO .
  * @param  Volume: Initial volume level (from 0 (Mute) to 100 (Max))
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @note   This function configure also that the I2S PLL input clock.    
  * @retval 0 if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq)
{ 
  uint8_t ret = AUDIO_ERROR;
  uint32_t deviceid = 0x00;
  RCC_PeriphCLKInitTypeDef RCC_ExCLKInitStruct;
  uint8_t index = 0, freqindex = 0xFF;
  
  for(index = 0; index < 8; index++)
  {
    if(I2SFreq[index] == AudioFreq)
    {
      freqindex = index;
    }
  }
  HAL_RCCEx_GetPeriphCLKConfig(&RCC_ExCLKInitStruct); 
  if(freqindex != 0xFF)
  {
    /* I2S clock config 
    PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input) × (PLLI2SN/PLLM)
    I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR */
    RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = I2SPLLN[freqindex];
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = I2SPLLR[freqindex];
    HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct);     
  } 
  else /* Default PLL I2S configuration */
  {
    /* I2S clock config 
    PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input) × (PLLI2SN/PLLM)
    I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR */
    RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = 258;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = 3;
    HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct); 
  }
  
  /* Reset the Codec Registers */
  CODEC_Reset();
  
  deviceid = cs43l22_drv.ReadID(AUDIO_I2C_ADDRESS);
  
  if((deviceid & CS43L22_ID_MASK) == CS43L22_ID)
  {  
    /* Initialize the audio driver structure */
    audio_drv = &cs43l22_drv; 
    ret = AUDIO_OK;
  }
  else
  {
    ret = AUDIO_ERROR;
  }
  
  if(ret == AUDIO_OK)
  {
    audio_drv->Init(AUDIO_I2C_ADDRESS, OutputDevice, Volume, AudioFreq);
    /* I2S data transfer preparation:
    Prepare the Media to be used for the audio transfer from memory to I2S peripheral */
    /* Configure the I2S peripheral */
    I2Sx_Init(AudioFreq);
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
    HAL_I2S_Transmit_DMA(&haudio_i2s, pBuffer, DMA_MAX(Size/AUDIODATA_SIZE));
    return AUDIO_OK;
  }
}

/**
  * @brief  Sends n-Bytes on the I2S interface.
  * @param  pData: Pointer to data address 
  * @param  Size: Number of data to be written.
  * @retval None
  */
void BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size)
{
  HAL_I2S_Transmit_DMA(&haudio_i2s, pData, Size); 
}

/**
  * @brief   Pauses the audio file stream. 
  *          In case of using DMA, the DMA Pause feature is used.
  * @WARNING When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @param   None
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
    HAL_I2S_DMAPause(&haudio_i2s);
    
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief   Resumes the audio file stream.  
  * @WARNING When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @param   None
  * @retval  AUDIO_OK if correct communication, else wrong communication
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
    HAL_I2S_DMAResume(&haudio_i2s);
    
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
  HAL_I2S_DMAStop(&haudio_i2s);
  
  /* Call Audio Codec Stop function */
  if(audio_drv->Stop(AUDIO_I2C_ADDRESS, Option) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    if(Option == CODEC_PDWN_HW)
    { 
      /* Wait at least 1ms */
      HAL_Delay(1);
      
      /* Reset the pin */
      BSP_IO_WritePin(AUDIO_RESET_PIN, RESET);
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
  * @param  Cmd: could be AUDIO_MUTE_ON to mute sound or AUDIO_MUTE_OFF to 
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
  * @note   This function modifies a global variable of the audio codec driver: OutputDev.
  * @param  Output: specifies the audio output target: OUTPUT_DEVICE_SPEAKER,
  *         OUTPUT_DEVICE_HEADPHONE, OUTPUT_DEVICE_BOTH or OUTPUT_DEVICE_AUTO 
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_SetOutputMode(uint8_t Output)
{
  /* Call the Codec output Device function */
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
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
void BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq)
{
  RCC_PeriphCLKInitTypeDef RCC_ExCLKInitStruct;
  uint8_t index = 0, freqindex = 0xFF;
  
  for(index = 0; index < 8; index++)
  {
    if(I2SFreq[index] == AudioFreq)
    {
      freqindex = index;
    }
  }
  HAL_RCCEx_GetPeriphCLKConfig(&RCC_ExCLKInitStruct);
  if(freqindex != 0xFF)
  {
    /* I2S clock config 
    PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input) × (PLLI2SN/PLLM)
    I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR */
    RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = I2SPLLN[freqindex];
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = I2SPLLR[freqindex];
    HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct);     
  } 
  else /* Default PLL I2S configuration */
  {
    /* I2S clock config 
    PLLI2S_VCO = f(VCO clock) = f(PLLI2S clock input) × (PLLI2SN/PLLM)
    I2SCLK = f(PLLI2S clock output) = f(VCO clock) / PLLI2SR */
    RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = 258;
    RCC_ExCLKInitStruct.PLLI2S.PLLI2SR = 3;
    HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct); 
  }
  /* Update the I2S audio frequency configuration */
  I2Sx_Init(AudioFreq);
}

/**
  * @brief Tx Transfer completed callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the remaining file size and new address offset: This function 
     should be coded by user (its prototype is already declared in stm324xg_eval_audio.h) */  
  BSP_AUDIO_OUT_TransferComplete_CallBack();       
}

/**
  * @brief Tx Transfer Half completed callbacks
  * @param hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the remaining file size and new address offset: This function 
     should be coded by user (its prototype is already declared in stm324xg_eval_audio.h) */  
  BSP_AUDIO_OUT_HalfTransfer_CallBack();   
}

/**
  * @brief  I2S error callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s) 
{
  BSP_AUDIO_OUT_Error_CallBack();
}

/**
  * @brief  Manages the DMA full Transfer complete event.
  * @param  None
  * @retval None
  */
__weak void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  None
  * @retval None
  */
__weak void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{ 
}

/**
  * @brief  Manages the DMA FIFO error event.
  * @param  None
  * @retval None
  */
__weak void BSP_AUDIO_OUT_Error_CallBack(void)
{
}

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Initializes I2C MSP.
  * @param  None
  * @retval None
  */
static void I2Sx_MspInit(void)
{ 
  static DMA_HandleTypeDef hdma_i2sTx;
  GPIO_InitTypeDef  GPIO_InitStruct;  
  I2S_HandleTypeDef *hi2s = &haudio_i2s;
  
  /* Enable I2S clock */
  AUDIO_I2Sx_CLK_ENABLE();
  
  /* Enable SCK, SD and WS GPIO clock */
  AUDIO_I2Sx_SCK_SD_WS_CLK_ENABLE();
  
  /* CODEC_I2S pins configuration: WS, SCK and SD pins */
  GPIO_InitStruct.Pin = AUDIO_I2Sx_SCK_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate = AUDIO_I2Sx_SCK_SD_WS_AF;
  HAL_GPIO_Init(AUDIO_I2Sx_SCK_SD_WS_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = AUDIO_I2Sx_SD_PIN;
  HAL_GPIO_Init(AUDIO_I2Sx_SCK_SD_WS_GPIO_PORT, &GPIO_InitStruct); 
  
  GPIO_InitStruct.Pin = AUDIO_I2Sx_WS_PIN;
  HAL_GPIO_Init(AUDIO_I2Sx_SCK_SD_WS_GPIO_PORT, &GPIO_InitStruct); 
  
  /* Enable MCK GPIO clock */
  AUDIO_I2Sx_MCK_CLK_ENABLE();
  
  /* CODEC_I2S pins configuration: MCK pin */
  GPIO_InitStruct.Pin = AUDIO_I2Sx_MCK_PIN;
  HAL_GPIO_Init(AUDIO_I2Sx_MCK_GPIO_PORT, &GPIO_InitStruct); 
  
  /* Enable the DMA clock */
  AUDIO_I2Sx_DMAx_CLK_ENABLE();
    
  if(hi2s->Instance == AUDIO_I2Sx)
  {
    /* Configure the hdma_i2sTx handle parameters */   
    hdma_i2sTx.Init.Channel             = AUDIO_I2Sx_DMAx_CHANNEL;
    hdma_i2sTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_i2sTx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2sTx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2sTx.Init.PeriphDataAlignment = AUDIO_I2Sx_DMAx_PERIPH_DATA_SIZE;
    hdma_i2sTx.Init.MemDataAlignment    = AUDIO_I2Sx_DMAx_MEM_DATA_SIZE;
    hdma_i2sTx.Init.Mode                = DMA_NORMAL;
    hdma_i2sTx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_i2sTx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;         
    hdma_i2sTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2sTx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_i2sTx.Init.PeriphBurst         = DMA_PBURST_SINGLE; 
    
    hdma_i2sTx.Instance = AUDIO_I2Sx_DMAx_STREAM;
    
    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmatx, hdma_i2sTx);
    
    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_i2sTx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_i2sTx);      
  }
  
  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(AUDIO_I2Sx_DMAx_IRQ, AUDIO_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(AUDIO_I2Sx_DMAx_IRQ); 
}

/**
  * @brief  Initializes the Audio Codec audio interface (I2S).
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral. 
  * @retval None
  */
static void I2Sx_Init(uint32_t AudioFreq)
{
  /* Initialize the haudio_i2s Instance parameter */
  haudio_i2s.Instance = AUDIO_I2Sx;

 /* Disable I2S block */
  __HAL_I2S_DISABLE(&haudio_i2s);  

  haudio_i2s.Init.Mode = I2S_MODE_MASTER_TX;
  haudio_i2s.Init.Standard = I2S_STANDARD;
  haudio_i2s.Init.DataFormat = I2S_DATAFORMAT_16B;
  haudio_i2s.Init.AudioFreq = AudioFreq;
  haudio_i2s.Init.CPOL = I2S_CPOL_LOW;
  haudio_i2s.Init.MCLKOutput = I2S_MCLKOUTPUT_ENABLE;

  if(HAL_I2S_GetState(&haudio_i2s) == HAL_I2S_STATE_RESET)
  { 
    I2Sx_MspInit();
  }
  /* Init the I2S */
  HAL_I2S_Init(&haudio_i2s); 
}

/**
  * @brief  Resets the audio codec. It restores the default configuration of the 
  *         codec (this function shall be called before initializing the codec).
  * @note   This function calls an external driver function: The IO Expander driver.
  * @param  None
  * @retval None
  */
static void CODEC_Reset(void)
{
  /* Configure the IO Expander (to use the Codec Reset pin mapped on the IOExpander) */
  BSP_IO_Init();
  
  BSP_IO_ConfigPin(AUDIO_RESET_PIN, IO_MODE_OUTPUT);
  
  /* Power Down the codec */
  BSP_IO_WritePin(AUDIO_RESET_PIN, RESET);

  /* Wait for a delay to insure registers erasing */
  HAL_Delay(CODEC_RESET_DELAY); 
  
  /* Power on the codec */
  BSP_IO_WritePin(AUDIO_RESET_PIN, SET);
   
  /* Wait for a delay to insure registers erasing */
  HAL_Delay(CODEC_RESET_DELAY); 
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
