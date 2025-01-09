/*!
    \file    audio_out_itf.c
    \brief   audio OUT (playback) interface functions

    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "audio_core.h"
#include "audio_out_itf.h"

/* local function prototypes ('static') */
static uint8_t init(uint32_t audio_freq, uint32_t volume);
static uint8_t deinit(void);
static uint8_t audio_cmd(uint8_t *pbuf, uint32_t size, uint8_t cmd);

/* local variable defines */
static uint8_t audio_state = AD_STATE_INACTIVE;

audio_fops_struct audio_out_fops = {
    .audio_init   = init,
    .audio_deinit = deinit,
    .audio_cmd    = audio_cmd
};

/*!
    \brief      initialize and configures all required resources
    \param[in]  audio_freq: statrt_up audio frequency
    \param[in]  volume: start_up volume to be set
    \param[out] none
    \retval     AD_OK if all operations succeed, otherwise, AD_FAIL.
*/
static uint8_t init(uint32_t audio_freq, uint32_t volume)
{
    static uint32_t initialized = 0U;

    /* check if the low layer has already been initialized */
    if(0U == initialized) {
        /* initialize GPIO */
        codec_gpio_init();

        /* initialize I2S */
        codec_audio_interface_init(audio_freq);

        /* initialize DMA */
        codec_i2s_dma_init();

        /* prevent reinitializing the interface again */
        initialized = 1U;
    }

    /* update the audio state machine */
    audio_state = AD_STATE_ACTIVE;

    return AD_OK;
}

/*!
    \brief      free all resources used by low layer and stops audio-play function
    \param[in]  none
    \param[out] none
    \retval     AD_OK if all operations succeed, otherwise, AD_FAIL.
*/
static uint8_t deinit(void)
{
    /* update the audio state machine */
    audio_state = AD_STATE_INACTIVE;

    return AD_OK;
}

/*!
    \brief      play, stop, pause or resume current file
    \param[in]  pbuf: address from which file should be played
    \param[in]  size: size of the current buffer/file
    \param[in]  cmd: command to be executed, can be:
      \arg        AD_CMD_PLAY
      \arg        AD_CMD_PAUSE
      \arg        AD_CMD_RESUME
      \arg        AD_CMD_STOP
    \param[out] none
    \retval     AD_OK if all operations succeed, otherwise, AD_FAIL.
*/
static uint8_t audio_cmd(uint8_t *pbuf, uint32_t size, uint8_t cmd)
{
    /* check the current state */
    if((AD_STATE_INACTIVE == audio_state) || (AD_STATE_ERROR == audio_state)) {
        audio_state = AD_STATE_ERROR;

        return AD_FAIL;
    }

    switch(cmd) {
    /* process the play command */
    case AD_CMD_PLAY:
        /* if current state is active or stopped */
        if((AD_STATE_ACTIVE == audio_state) || \
                (AD_STATE_STOPPED == audio_state) || \
                (AD_STATE_PLAYING == audio_state)) {
            audio_play((uint32_t)pbuf, size);
            audio_state = AD_STATE_PLAYING;

            return AD_OK;
        } else if(AD_STATE_PAUSED == audio_state) {
            audio_pause_resume(AD_RESUME, (uint32_t)pbuf, (size / 2U));
            audio_state = AD_STATE_PLAYING;

            return AD_OK;
        } else {
            return AD_FAIL;
        }

    /* process the stop command */
    case AD_CMD_STOP:
        if(AD_STATE_PLAYING != audio_state) {
            /* unsupported command */
            return AD_FAIL;
        } else {
            audio_stop();
            audio_state = AD_STATE_STOPPED;

            return AD_OK;
        }

    /* process the pause command */
    case AD_CMD_PAUSE:
        if(AD_STATE_PLAYING != audio_state) {
            /* unsupported command */
            return AD_FAIL;
        } else {
            audio_pause_resume(AD_PAUSE, (uint32_t)pbuf, (size / 2U));
            audio_state = AD_STATE_PAUSED;

            return AD_OK;
        }

    /* unsupported command */
    default:
        return AD_FAIL;
    }
}
