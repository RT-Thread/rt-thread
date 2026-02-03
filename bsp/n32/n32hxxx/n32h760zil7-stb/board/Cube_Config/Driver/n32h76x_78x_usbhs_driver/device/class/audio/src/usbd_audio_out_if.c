/**
*     Copyright (c) 2025, Nations Technologies Inc.
* 
*     All rights reserved.
*
*     This software is the exclusive property of Nations Technologies Inc. (Hereinafter 
* referred to as NATIONS). This software, and the product of NATIONS described herein 
* (Hereinafter referred to as the Product) are owned by NATIONS under the laws and treaties
* of the People's Republic of China and other applicable jurisdictions worldwide.
*
*     NATIONS does not grant any license under its patents, copyrights, trademarks, or other 
* intellectual property rights. Names and brands of third party may be mentioned or referred 
* thereto (if any) for identification purposes only.
*
*     NATIONS reserves the right to make changes, corrections, enhancements, modifications, and 
* improvements to this software at any time without notice. Please contact NATIONS and obtain 
* the latest version of this software before placing orders.

*     Although NATIONS has attempted to provide accurate and reliable information, NATIONS assumes 
* no responsibility for the accuracy and reliability of this software.
* 
*     It is the responsibility of the user of this software to properly design, program, and test 
* the functionality and safety of any application made of this information and any resulting product. 
* In no event shall NATIONS be liable for any direct, indirect, incidental, special,exemplary, or 
* consequential damages arising in any way out of the use of this software or the Product.
*
*     NATIONS Products are neither intended nor warranted for usage in systems or equipment, any
* malfunction or failure of which may cause loss of human life, bodily injury or severe property 
* damage. Such applications are deemed, "Insecure Usage".
*
*     All Insecure Usage shall be made at user's risk. User shall indemnify NATIONS and hold NATIONS 
* harmless from and against all claims, costs, damages, and other liabilities, arising from or related 
* to any customer's Insecure Usage.

*     Any express or implied warranty with regard to this software or the Product, including,but not 
* limited to, the warranties of merchantability, fitness for a particular purpose and non-infringement
* are disclaimed to the fullest extent permitted by law.

*     Unless otherwise explicitly permitted by NATIONS, anyone may not duplicate, modify, transcribe
* or otherwise distribute this software for any purposes, in whole or in part.
*
*     NATIONS products and technologies shall not be used for or incorporated into any products or systems
* whose manufacture, use, or sale is prohibited under any applicable domestic or foreign laws or regulations. 
* User shall comply with any applicable export control laws and regulations promulgated and administered by 
* the governments of any countries asserting jurisdiction over the parties or transactions.
**/

/**
 * @file usbd_audio_out_if.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2025, Nations Technologies Inc. All rights reserved.
 */#include "usbd_audio_core.h"
#include "usbd_audio_out_if.h"
#include "bsp_wm8978.h"

static uint8_t  Init         (uint32_t  AudioFreq, uint32_t Volume, uint32_t options);
static uint8_t  DeInit       (uint32_t options);
static uint8_t  AudioCmd     (uint8_t* pbuf, uint32_t size, uint8_t cmd);
static uint8_t  VolumeCtrl    (uint8_t vol);
static uint8_t  MuteCtrl      (uint8_t cmd);
static uint8_t  PeriodicTC   (uint8_t cmd);
static uint8_t  GetState     (void);

AUDIO_FOPS_TypeDef  AUDIO_OUT_fops = 
{
    Init,
    DeInit,
    AudioCmd,
    VolumeCtrl,
    MuteCtrl,
    PeriodicTC,
    GetState
};

static uint8_t AudioState = AUDIO_STATE_INACTIVE;

/**
*\*\name    Init.
*\*\fun     Initialize and configures all required resources for audio play function.
*\*\param   AudioFreq: Startup audio frequency. 
*\*\param   Volume: Startup volume to be set.
*\*\param   options: specific options passed to low layer function.
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t Init(uint32_t AudioFreq, uint32_t Volume, uint32_t options)
{
    static uint32_t Initialized = 0;

    /* Check if the low layer has already been initialized */
    if (Initialized == 0)
    {
        /* Call low layer function */
        if (WM8978_Speaker_Init(Volume, AudioFreq) != 0)
        {
            AudioState = AUDIO_STATE_ERROR;
            return AUDIO_FAIL;
        }
        /* Set the Initialization flag to prevent reinitializing the interface again */
        Initialized = 1;
    }
  
    /* Update the Audio state machine */
    AudioState = AUDIO_STATE_ACTIVE;

    return AUDIO_OK;
}

/**
*\*\name    DeInit.
*\*\fun     Free all resources used by low layer and stops audio-play function.
*\*\param   options: specific options passed to low layer function.
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t DeInit (uint32_t options)
{
    /* Update the Audio state machine */
    AudioState = AUDIO_STATE_INACTIVE;

    return AUDIO_OK;
}

uint8_t txbuff[0xC0] = {0};
/**
*\*\name    AudioCmd.
*\*\fun     Play, Stop, Pause or Resume current file.
*\*\param   pbuf: address from which file should be played.
*\*\param   size: size of the current buffer/file.
*\*\param   cmd: command to be executed, can be AUDIO_CMD_PLAY , AUDIO_CMD_PAUSE, AUDIO_CMD_RESUME or AUDIO_CMD_STOP.
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t AudioCmd(uint8_t* pbuf, uint32_t size, uint8_t cmd)
{
    /* Check the current state */
    if ((AudioState == AUDIO_STATE_INACTIVE) || (AudioState == AUDIO_STATE_ERROR))
    {
        AudioState = AUDIO_STATE_ERROR;
        return AUDIO_FAIL;
    }

    switch (cmd)
    {
        /* Process the PLAY command ----------------------------*/
        case AUDIO_CMD_PLAY:
            /* If current state is Active or Stopped */
            if ((AudioState == AUDIO_STATE_ACTIVE) || (AudioState == AUDIO_STATE_STOPPED) || (AudioState == AUDIO_STATE_PLAYING))
            {
                I2S_TX_DMA_Add_SIZE_Set(pbuf, (size/2));
                
                AudioState = AUDIO_STATE_PLAYING;
                return AUDIO_OK;
            }
            /* If current state is Paused */
            else if (AudioState == AUDIO_STATE_PAUSED)
            {
                I2S_Play_Start();
                AudioState = AUDIO_STATE_PLAYING;
                return AUDIO_OK;
            } 
            else /* Not allowed command */
            {
                return AUDIO_FAIL;
            }
    
        /* Process the STOP command ----------------------------*/
        case AUDIO_CMD_STOP:
            if (AudioState != AUDIO_STATE_PLAYING)
            {
                /* Unsupported command */
                return AUDIO_FAIL;
            }
            else
            {
                I2S_Play_Stop();
                AudioState = AUDIO_STATE_STOPPED;
                return AUDIO_OK;
            }

        /* Process the PAUSE command */
        case AUDIO_CMD_PAUSE:
            if (AudioState != AUDIO_STATE_PLAYING)
            {
                /* Unsupported command */
                return AUDIO_FAIL;
            }
            else
            {
                I2S_Play_Stop();
                AudioState = AUDIO_STATE_PAUSED;
                return AUDIO_OK;
            } 
    
        /* Unsupported command ---------------------------------*/
        default:
            return AUDIO_FAIL;
    }
}

/**
*\*\name    VolumeCtrl.
*\*\fun     Set the volume level in %
*\*\param   vol: volume level to be set in % (from 0% to 100%)
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t VolumeCtrl(uint8_t vol)
{
    /* Call low layer volume setting function */  
    WM8978_SetOUT1Volume(vol);

    return AUDIO_OK;
}

/**
*\*\name    MuteCtrl.
*\*\fun     Mute or Unmute the audio current output
*\*\param   cmd: can be 0 to unmute, or 1 to mute.
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t MuteCtrl(uint8_t cmd)
{
    /* Call low layer mute setting function */  
    WM8978_OutMute(cmd);
    return AUDIO_OK;
}

/**
*\*\name    PeriodicTC.
*\*\fun     PeriodicTC.
*\*\param   none
*\*\return  AUDIO_OK if all operations succeed, AUDIO_FAIL else.
**/
static uint8_t PeriodicTC(uint8_t cmd)
{
    return AUDIO_OK;
}

/**
*\*\name    GetState.
*\*\fun     Return the current state of the audio machine
*\*\param   none
*\*\return  Current State.
**/
static uint8_t  GetState(void)
{
    return AudioState;
}
