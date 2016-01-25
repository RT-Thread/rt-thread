/**
  ******************************************************************************
  * @file    stm32f401_discovery_audio.c
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    14-August-2015
  * @brief   This file provides the Audio driver for the STM32F401-Discovery 
  *          board.  
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

/*==============================================================================
                                             User NOTES
1. How To use this driver:
--------------------------
   - This driver supports STM32F401xx devices on STM32F401-Discovery Kit:
        a) to play an audio file (all functions names start by BSP_AUDIO_OUT_xxx)
        b) to record an audio file through MP45DT02, ST MEMS (all functions names start by AUDIO_IN_xxx)

a) PLAY A FILE:
==============
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
      the codec (try to un-plug the power or reset device in this case).
      - OUTPUT_DEVICE_SPEAKER: only speaker will be set as output for the audio stream.
      - OUTPUT_DEVICE_HEADPHONE: only headphones will be set as output for the audio stream.
      - OUTPUT_DEVICE_AUTO: Selection of output device is made through external switch (implemented 
         into the audio jack on the discovery board). When the Headphone is connected it is used
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
      The Callback functions are named BSP_AUDIO_OUT_XXXCallBack() and only their prototypes are declared in 
      the stm32f401_discovery_audio.h file. (refer to the example for more details on the callbacks implementations)
   + To Stop playing, to modify the volume level, the frequency or to mute, use the functions
       BSP_AUDIO_OUT_Stop(), BSP_AUDIO_OUT_SetVolume(), AUDIO_OUT_SetFrequency() BSP_AUDIO_OUT_SetOutputMode and BSP_AUDIO_OUT_SetMute().
   + The driver API and the callback functions are at the end of the stm32f401_discovery_audio.h file.
   
Driver architecture:
--------------------
   + This driver provide the High Audio Layer: consists of the function API exported in the stm32f401_discovery_audio.h file
       (BSP_AUDIO_OUT_Init(), BSP_AUDIO_OUT_Play() ...)
   + This driver provide also the Media Access Layer (MAL): which consists of functions allowing to access the media containing/
       providing the audio file/stream. These functions are also included as local functions into
       the stm32f401_discovery_audio.c file (I2S3_Init()...)

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
      performed (BSP_AUDIO_OUT_SetVolume() or BSP_AUDIO_OUT_SetMute()or BSP_AUDIO_OUT_SetOutputMode()). 
      When the audio data is played, no communication is required with the audio codec.
   3- Parsing of audio file is not implemented (in order to determine audio file properties: Mono/Stereo, Data size, 
      File size, Audio Frequency, Audio Data header size ...). The configuration is fixed for the given audio file.
   4- Supports only Stereo audio streaming. To play mono audio streams, each data should be sent twice 
      on the I2S or should be duplicated on the source buffer. Or convert the stream in stereo before playing.
   5- Supports only 16-bits audio data size.

b) RECORD A FILE:
================
   + Call the function BSP_AUDIO_IN_Init(
                                    AudioFreq: Audio frequency in Hz (8000, 16000, 22500, 32000 ...)
                                    )
      This function configures all the hardware required for the audio application (I2S, 
      GPIOs, DMA and interrupt if needed). This function returns 0 if configuration is OK.

   + Call the function BSP_AUDIO_IN_Record(
                            pbuf Main buffer pointer for the recorded data storing  
                            size Current size of the recorded buffer
                            )
      to start recording from the microphone.

   + User needs to implement user callbacks to retrieve data saved in the record buffer
      (AUDIO_IN_RxHalfCpltCallback/BSP_AUDIO_IN_ReceiveComplete_CallBack)

   + Call the function AUDIO_IN_STOP() to stop recording 

==============================================================================*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f401_discovery_audio.h"

/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup STM32F401_DISCOVERY
  * @{
  */

/** @addtogroup STM32F401_DISCOVERY_AUDIO
  * @brief This file includes the low layer audio driver available on STM32F401-Discovery
  *        discovery board.
  * @{
  */ 

/** @defgroup STM32F401_DISCOVERY_AUDIO_Private_Types
  * @{
  */ 
/**
  * @}
  */ 
  
/** @defgroup STM32F401_DISCOVERY_AUDIO_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 

/** @defgroup STM32F401_DISCOVERY_AUDIO_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  
/** @defgroup STM32F401_DISCOVERY_AUDIO_Private_Variables
  * @{
  */
/*##### PLAY #####*/
static AUDIO_DrvTypeDef           *pAudioDrv;
I2S_HandleTypeDef                 hAudioOutI2s;

/*### RECORDER ###*/
I2S_HandleTypeDef                 hAudioInI2s;

PDMFilter_InitStruct Filter[DEFAULT_AUDIO_IN_CHANNEL_NBR];
uint16_t __IO AudioInVolume = DEFAULT_AUDIO_IN_VOLUME;
    
/**
  * @}
  */ 

/** @defgroup STM32F401_DISCOVERY_AUDIO_Private_Function_Prototypes
  * @{
  */ 
static void  I2S3_MspInit(void);
static void  I2S3_Init(uint32_t AudioFreq);

static void  I2S2_MspInit(void);
static void  I2S2_Init(uint32_t AudioFreq);
static void  PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbr);
/**
  * @}
  */ 

/** @defgroup STM32F401_DISCOVERY_AUDIO_OUT_Private_Functions
  * @{
  */ 

/**
  * @brief  Configure the audio peripherals.
  * @param  OutputDevice: OUTPUT_DEVICE_SPEAKER, OUTPUT_DEVICE_HEADPHONE,
  *                       OUTPUT_DEVICE_BOTH or OUTPUT_DEVICE_AUTO .
  * @param  Volume: Initial volume level (from 0 (Mute) to 100 (Max))
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Init(uint16_t OutputDevice, uint8_t Volume, uint32_t AudioFreq)
{    
  uint8_t ret = AUDIO_ERROR;
  uint32_t deviceid = 0x00;
  RCC_PeriphCLKInitTypeDef rccclkinit;
  
  /* Enable PLLI2S clock */
  HAL_RCCEx_GetPeriphCLKConfig(&rccclkinit);
  /* PLLI2S_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
  if((AudioFreq & 0x7) == 0)
  {
    /* Audio frequency multiple of 8 (8/16/32/48/96/192)*/
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 192 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 192/6 = 32 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 192;
    rccclkinit.PLLI2S.PLLI2SR = 6;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  else
  {
    /* Other Frequency (11.025/22.500/44.100) */
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 290 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 290/2 = 145 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 290;
    rccclkinit.PLLI2S.PLLI2SR = 2;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  
  deviceid = cs43l22_drv.ReadID(AUDIO_I2C_ADDRESS);

  if((deviceid & CS43L22_ID_MASK) == CS43L22_ID)
  {  
    /* Initialize the audio driver structure */
    pAudioDrv = &cs43l22_drv; 
    ret = AUDIO_OK;
  }
  else
  {
    ret = AUDIO_ERROR;
  }
  
  if(ret == AUDIO_OK)
  {
    pAudioDrv->Init(AUDIO_I2C_ADDRESS, OutputDevice, Volume, AudioFreq);
    /* I2S data transfer preparation:
       Prepare the Media to be used for the audio transfer from memory to I2S peripheral */
    /* Configure the I2S peripheral */
    I2S3_Init(AudioFreq);
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
  if(pAudioDrv->Play(AUDIO_I2C_ADDRESS, pBuffer, Size) != 0)
  {
    return AUDIO_ERROR;
  }
  else 
  {
    /* Update the Media layer and enable it for play */  
    HAL_I2S_Transmit_DMA(&hAudioOutI2s, pBuffer, DMA_MAX(Size/AUDIODATA_SIZE)); 
    
    return AUDIO_OK;
  }
}
  
/**
  * @brief  Sends n-Bytes on the I2S interface.
  * @param  pData: Pointer to data address 
  * @param  Size: Number of data to be written
  * @retval None
  */
void BSP_AUDIO_OUT_ChangeBuffer(uint16_t *pData, uint16_t Size)
{
  HAL_I2S_Transmit_DMA(&hAudioOutI2s, pData, Size); 
}

/**
  * @brief   This function Pauses the audio file stream. In case
  *          of using DMA, the DMA Pause feature is used.
  * @WARNING When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @retval  AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Pause(void)
{    
  /* Call the Audio Codec Pause/Resume function */
  if(pAudioDrv->Pause(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer pause function */
    HAL_I2S_DMAPause(&hAudioOutI2s);
    
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief   This function  Resumes the audio file stream.  
  * @WARNING When calling BSP_AUDIO_OUT_Pause() function for pause, only
  *          BSP_AUDIO_OUT_Resume() function should be called for resume (use of BSP_AUDIO_OUT_Play() 
  *          function for resume could lead to unexpected behavior).
  * @retval  AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Resume(void)
{    
  /* Call the Audio Codec Pause/Resume function */
  if(pAudioDrv->Resume(AUDIO_I2C_ADDRESS) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    /* Call the Media layer resume function */
    HAL_I2S_DMAResume(&hAudioOutI2s);
    
    /* Return AUDIO_OK when all operations are correctly done */
    return AUDIO_OK;
  }
}

/**
  * @brief  Stops audio playing and Power down the Audio Codec. 
  * @param  Option: could be one of the following parameters 
  *           - CODEC_PDWN_HW: completely shut down the codec (physically). 
  *                            Then need to reconfigure the Codec after power on.  
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_OUT_Stop(uint32_t Option)
{
  /* Call DMA Stop to disable DMA stream before stopping codec */
  HAL_I2S_DMAStop(&hAudioOutI2s);
  
  /* Call Audio Codec Stop function */
  if(pAudioDrv->Stop(AUDIO_I2C_ADDRESS, Option) != 0)
  {
    return AUDIO_ERROR;
  }
  else
  {
    if(Option == CODEC_PDWN_HW)
    { 
      /* Wait at least 100us */
      HAL_Delay(1);
      
      /* Reset the pin */
      HAL_GPIO_WritePin(AUDIO_RESET_GPIO, AUDIO_RESET_PIN, GPIO_PIN_RESET);
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
  if(pAudioDrv->SetVolume(AUDIO_I2C_ADDRESS, Volume) != 0)
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
  if(pAudioDrv->SetMute(AUDIO_I2C_ADDRESS, Cmd) != 0)
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
  if(pAudioDrv->SetOutputMode(AUDIO_I2C_ADDRESS, Output) != 0)
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
  * @brief  Update the audio frequency.
  * @param  AudioFreq: Audio frequency used to play the audio stream.
  * @retval None
  * @note This API should be called after the BSP_AUDIO_OUT_Init() to adjust the
  * audio frequency. 
  */
void BSP_AUDIO_OUT_SetFrequency(uint32_t AudioFreq)
{ 
  RCC_PeriphCLKInitTypeDef rccclkinit;
  
  /* Enable PLLI2S clock */
  HAL_RCCEx_GetPeriphCLKConfig(&rccclkinit);
  /* PLLI2S_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
  if ((AudioFreq & 0x7) == 0)
  {
    /* Audio frequency multiple of 8 (8/16/32/48/96/192)*/
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 192 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 192/6 = 32 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 192;
    rccclkinit.PLLI2S.PLLI2SR = 6;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  else
  {
    /* Other Frequency (11.025/22.500/44.100) */
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 290 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 290/2 = 145 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 290;
    rccclkinit.PLLI2S.PLLI2SR = 2;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  
  /* Update the I2S audio frequency configuration */
  I2S3_Init(AudioFreq);
}

/**
  * @brief  Tx Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == I2S3)
  {
    /* Call the user function which will manage directly transfer complete */  
    BSP_AUDIO_OUT_TransferComplete_CallBack();       
  }
}

/**
  * @brief  Tx Half Transfer completed callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_TxHalfCpltCallback(I2S_HandleTypeDef *hi2s)
{
  if(hi2s->Instance == I2S3)
  {
  /* Manage the remaining file size and new address offset: This function 
     should be coded by user (its prototype is already declared in stm32f401_discovery_audio.h) */
    BSP_AUDIO_OUT_HalfTransfer_CallBack();
  }
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
  * @brief  AUDIO OUT I2S MSP Init.
  * @param  None
  * @retval None
  */
static void I2S3_MspInit(void)
{
  static DMA_HandleTypeDef hdma_i2sTx;
  GPIO_InitTypeDef  GPIO_InitStruct;
  I2S_HandleTypeDef *hi2s = &hAudioOutI2s;

  /* Enable I2S3 clock */
  I2S3_CLK_ENABLE();

  /*** Configure the GPIOs ***/  
  /* Enable I2S GPIO clocks */
  I2S3_SCK_SD_CLK_ENABLE();
  I2S3_WS_CLK_ENABLE();

  /* I2S3 pins configuration: WS, SCK and SD pins ----------------------------*/
  GPIO_InitStruct.Pin         = I2S3_SCK_PIN | I2S3_SD_PIN; 
  GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull        = GPIO_NOPULL;
  GPIO_InitStruct.Speed       = GPIO_SPEED_FAST;
  GPIO_InitStruct.Alternate   = I2S3_SCK_SD_WS_AF;
  HAL_GPIO_Init(I2S3_SCK_SD_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin         = I2S3_WS_PIN ;
  HAL_GPIO_Init(I2S3_WS_GPIO_PORT, &GPIO_InitStruct); 

  /* I2S3 pins configuration: MCK pin */
  I2S3_MCK_CLK_ENABLE();
  GPIO_InitStruct.Pin         = I2S3_MCK_PIN; 
  HAL_GPIO_Init(I2S3_MCK_GPIO_PORT, &GPIO_InitStruct);   

  /* Enable the I2S DMA clock */
  I2S3_DMAx_CLK_ENABLE(); 
  
  if(hi2s->Instance == I2S3)
  {
    /* Configure the hdma_i2sTx handle parameters */   
    hdma_i2sTx.Init.Channel             = I2S3_DMAx_CHANNEL;  
    hdma_i2sTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    hdma_i2sTx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2sTx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2sTx.Init.PeriphDataAlignment = I2S3_DMAx_PERIPH_DATA_SIZE;
    hdma_i2sTx.Init.MemDataAlignment    = I2S3_DMAx_MEM_DATA_SIZE;
    hdma_i2sTx.Init.Mode                = DMA_NORMAL;
    hdma_i2sTx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_i2sTx.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;         
    hdma_i2sTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2sTx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_i2sTx.Init.PeriphBurst         = DMA_PBURST_SINGLE; 

    hdma_i2sTx.Instance                 = I2S3_DMAx_STREAM;

    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmatx, hdma_i2sTx);
    
    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_i2sTx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_i2sTx);
  }
  
  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(I2S3_DMAx_IRQ, AUDIO_OUT_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(I2S3_DMAx_IRQ); 
}

/**
  * @brief  Initializes the Audio Codec audio interface (I2S)
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral. 
  * @retval None
  */
static void I2S3_Init(uint32_t AudioFreq)
{
  /* Initialize the hAudioOutI2s Instance parameter */
  hAudioOutI2s.Instance         = I2S3;
  
  /* Disable I2S block */
  __HAL_I2S_DISABLE(&hAudioOutI2s);
  
  /* I2S3 peripheral configuration */
  hAudioOutI2s.Init.AudioFreq   = AudioFreq;
  hAudioOutI2s.Init.ClockSource = I2S_CLOCK_PLL;
  hAudioOutI2s.Init.CPOL        = I2S_CPOL_LOW;
  hAudioOutI2s.Init.DataFormat  = I2S_DATAFORMAT_16B;
  hAudioOutI2s.Init.MCLKOutput  = I2S_MCLKOUTPUT_ENABLE;
  hAudioOutI2s.Init.Mode        = I2S_MODE_MASTER_TX;
  hAudioOutI2s.Init.Standard    = I2S_STANDARD;

  /* Initialize the I2S peripheral with the structure above */
  if(HAL_I2S_GetState(&hAudioOutI2s) == HAL_I2S_STATE_RESET)
  { 
    I2S3_MspInit();
  }
  
  HAL_I2S_Init(&hAudioOutI2s);
}
  
/**
  * @}
  */ 
  
/** @defgroup STM32F401_DISCOVERY_AUDIO_IN_Private_Functions
  * @{
  */ 
  
/**
  * @brief  Initializes wave recording.
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral. 
  * @param  BitRes: Audio frequency to be configured for the I2S peripheral.
  * @param  ChnlNbr: Audio frequency to be configured for the I2S peripheral.
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_Init(uint32_t AudioFreq, uint32_t BitRes, uint32_t ChnlNbr)
{
  RCC_PeriphCLKInitTypeDef rccclkinit;
  
  /* Enable PLLI2S clock */
  HAL_RCCEx_GetPeriphCLKConfig(&rccclkinit);
  /* PLLI2S_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
  if ((AudioFreq & 0x7) == 0)
  {
    /* Audio frequency multiple of 8 (8/16/32/48/96/192)*/
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 192 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 192/6 = 32 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 192;
    rccclkinit.PLLI2S.PLLI2SR = 6;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  else
  {
    /* Other Frequency (11.025/22.500/44.100) */
    /* PLLI2S_VCO Output = PLLI2S_VCO Input * PLLI2SN = 290 Mhz */
    /* I2SCLK = PLLI2S_VCO Output/PLLI2SR = 290/2 = 145 Mhz */
    rccclkinit.PeriphClockSelection = RCC_PERIPHCLK_I2S;
    rccclkinit.PLLI2S.PLLI2SN = 290;
    rccclkinit.PLLI2S.PLLI2SR = 2;
    HAL_RCCEx_PeriphCLKConfig(&rccclkinit);
  }
  
  /* Configure the PDM library */
  PDMDecoder_Init(AudioFreq, ChnlNbr);
  
  /* Configure the I2S2 */
  I2S2_Init(AudioFreq);
  
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
  HAL_I2S_Receive_DMA(&hAudioInI2s, pbuf, size);
  
  /* Return AUDIO_OK when all operations are correctly done */
  ret = AUDIO_OK;
  
  return ret;
}

/**
  * @brief  Stops audio recording.
  * @param  None
  * @retval None
  */
uint8_t BSP_AUDIO_IN_Stop(void)
{
  uint32_t ret = AUDIO_ERROR;
  
  /* Call the Media layer pause function */
  HAL_I2S_DMAStop(&hAudioInI2s);  
  
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
  HAL_I2S_DMAPause(&hAudioInI2s);
  
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
  HAL_I2S_DMAResume(&hAudioInI2s);
  
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
  /* Set the Global variable AudioInVolume */
  AudioInVolume = Volume; 
  
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK;
}

/**
  * @brief  Converts audio format from PDM to PCM. 
  * @param  PDMBuf: Pointer to data PDM buffer
  * @param  PCMBuf: Pointer to data PCM buffer
  * @retval AUDIO_OK if correct communication, else wrong communication
  */
uint8_t BSP_AUDIO_IN_PDMToPCM(uint16_t *PDMBuf, uint16_t *PCMBuf)
{
  uint16_t AppPDM[INTERNAL_BUFF_SIZE/2];
  uint32_t index = 0; 
  
  /* PDM Demux */
  for(index = 0; index<INTERNAL_BUFF_SIZE/2; index++)
  {
    AppPDM[index] = HTONS(PDMBuf[index]);
  }
  
  for(index = 0; index < DEFAULT_AUDIO_IN_CHANNEL_NBR; index++)
  {
    /* PDM to PCM filter */
    PDM_Filter_64_LSB((uint8_t*)&AppPDM[index], (uint16_t*)&(PCMBuf[index]), AudioInVolume , (PDMFilter_InitStruct *)&Filter[index]);
  }
  
  /* Duplicate samples since a single microphone in mounted on STM32F4-Discovery */
  for(index = 0; index < PCM_OUT_SIZE; index++)
  {
    PCMBuf[(index<<1)+1] = PCMBuf[index<<1];
  }
	
  /* Return AUDIO_OK when all operations are correctly done */
  return AUDIO_OK; 
}

/**
  * @brief  Rx Transfer completed callbacks
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
     should be coded by user (its prototype is already declared in stm32f401_discovery_audio.h) */
  BSP_AUDIO_IN_HalfTransfer_CallBack();
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

/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Initialize the PDM library.
  * @param  AudioFreq: Audio sampling frequency
  * @param  ChnlNbr: Number of audio channels (1: mono; 2: stereo)
  * @retval None
  */
static void PDMDecoder_Init(uint32_t AudioFreq, uint32_t ChnlNbr)
{ 
  uint32_t i = 0;
  
  /* Enable CRC peripheral to unlock the PDM library */
  __CRC_CLK_ENABLE();
  
  for(i = 0; i < ChnlNbr; i++)
  {
    /* Filter LP & HP Init */
    Filter[i].LP_HZ = AudioFreq / 2;
    Filter[i].HP_HZ = 10;
    Filter[i].Fs = AudioFreq;
		/* On STM32F401-Discovery a single microphone is mounted, samples are duplicated
       to make stereo audio streams */
    Filter[i].Out_MicChannels = 2;
    Filter[i].In_MicChannels = ChnlNbr; 
    PDM_Filter_Init((PDMFilter_InitStruct *)&Filter[i]);
  }  
}

/**
  * @brief  AUDIO IN I2S MSP Init.
  * @param  None
  * @retval None
  */
static void I2S2_MspInit(void)
{
  static DMA_HandleTypeDef hdma_i2sRx;
  GPIO_InitTypeDef  GPIO_InitStruct;
  I2S_HandleTypeDef *hi2s = &hAudioInI2s;

  /* Enable the I2S2 peripheral clock */
  I2S2_CLK_ENABLE();

  /* Enable I2S GPIO clocks */
  I2S2_SCK_GPIO_CLK_ENABLE();
  I2S2_MOSI_GPIO_CLK_ENABLE();
  
  /* I2S2 pins configuration: SCK and MOSI pins ------------------------------*/
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;

  GPIO_InitStruct.Pin = I2S2_SCK_PIN; 
  GPIO_InitStruct.Alternate  = I2S2_SCK_AF;
  HAL_GPIO_Init(I2S2_SCK_GPIO_PORT, &GPIO_InitStruct);
  
  GPIO_InitStruct.Pin = I2S2_MOSI_PIN ;
  GPIO_InitStruct.Alternate  = I2S2_MOSI_AF;
  HAL_GPIO_Init(I2S2_MOSI_GPIO_PORT, &GPIO_InitStruct); 

  /* Enable the DMA clock */
  I2S2_DMAx_CLK_ENABLE();
    
  if(hi2s->Instance == I2S2)
  {
    /* Configure the hdma_i2sRx handle parameters */   
    hdma_i2sRx.Init.Channel             = I2S2_DMAx_CHANNEL;
    hdma_i2sRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
    hdma_i2sRx.Init.PeriphInc           = DMA_PINC_DISABLE;
    hdma_i2sRx.Init.MemInc              = DMA_MINC_ENABLE;
    hdma_i2sRx.Init.PeriphDataAlignment = I2S2_DMAx_PERIPH_DATA_SIZE;
    hdma_i2sRx.Init.MemDataAlignment    = I2S2_DMAx_MEM_DATA_SIZE;
    hdma_i2sRx.Init.Mode                = DMA_CIRCULAR;
    hdma_i2sRx.Init.Priority            = DMA_PRIORITY_HIGH;
    hdma_i2sRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
    hdma_i2sRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    hdma_i2sRx.Init.MemBurst            = DMA_MBURST_SINGLE;
    hdma_i2sRx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
    
    hdma_i2sRx.Instance = I2S2_DMAx_STREAM;
    
    /* Associate the DMA handle */
    __HAL_LINKDMA(hi2s, hdmarx, hdma_i2sRx);
    
    /* Deinitialize the Stream for new transfer */
    HAL_DMA_DeInit(&hdma_i2sRx);
    
    /* Configure the DMA Stream */
    HAL_DMA_Init(&hdma_i2sRx);      
  }
  
  /* I2S DMA IRQ Channel configuration */
  HAL_NVIC_SetPriority(I2S2_DMAx_IRQ, AUDIO_IN_IRQ_PREPRIO, 0);
  HAL_NVIC_EnableIRQ(I2S2_DMAx_IRQ); 
}

/**
  * @brief  Initializes the Audio Codec audio interface (I2S)
  * @note   This function assumes that the I2S input clock (through PLL_R in 
  *         Devices RevA/Z and through dedicated PLLI2S_R in Devices RevB/Y)
  *         is already configured and ready to be used.    
  * @param  AudioFreq: Audio frequency to be configured for the I2S peripheral. 
  * @retval None
  */
static void I2S2_Init(uint32_t AudioFreq)
{
  /* Initialize the hAudioInI2s Instance parameter */
  hAudioInI2s.Instance          = I2S2;
  
  /* Disable I2S block */
  __HAL_I2S_DISABLE(&hAudioInI2s);
  
  /* I2S2 peripheral configuration */
  hAudioInI2s.Init.AudioFreq    = 2 * AudioFreq;
  hAudioInI2s.Init.ClockSource  = I2S_CLOCK_PLL;
  hAudioInI2s.Init.CPOL         = I2S_CPOL_HIGH;
  hAudioInI2s.Init.DataFormat   = I2S_DATAFORMAT_16B;
  hAudioInI2s.Init.MCLKOutput   = I2S_MCLKOUTPUT_DISABLE;
  hAudioInI2s.Init.Mode         = I2S_MODE_MASTER_RX;
  hAudioInI2s.Init.Standard     = I2S_STANDARD_LSB;
  
  /* Initialize the I2S peripheral with the structure above */
  if(HAL_I2S_GetState(&hAudioInI2s) == HAL_I2S_STATE_RESET)
  { 
    I2S2_MspInit();
  }
  
  HAL_I2S_Init(&hAudioInI2s);
}
/**
  * @}
  */

/** @defgroup STM32F401_DISCOVERY_AUDIO_IN_OUT_Private_Functions 
  * @{
  */ 
  
/**
  * @brief  I2S error callbacks.
  * @param  hi2s: I2S handle
  * @retval None
  */
void HAL_I2S_ErrorCallback(I2S_HandleTypeDef *hi2s)
{
  /* Manage the error generated on DMA FIFO: This function 
     should be coded by user (its prototype is already declared in stm32f401_discovery_audio.h) */ 
  if(hi2s->Instance == I2S3)
  {
    BSP_AUDIO_OUT_Error_CallBack();
  }
  if(hi2s->Instance == I2S2)
  {
    BSP_AUDIO_IN_Error_Callback();
  }
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
