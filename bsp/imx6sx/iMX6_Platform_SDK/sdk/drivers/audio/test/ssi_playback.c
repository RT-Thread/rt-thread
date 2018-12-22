/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include "sdk.h"
#include "audio/audio.h"
#include "audio/imx_audmux.h"

/*
 * For smart_device board only.
 */
extern audio_card_t snd_card_ssi_wm8962;
extern void audio_codec_power_on(void);
extern void audio_clock_config(void);

int32_t ssi_playback(audio_pcm_p pcm_file)
{
    uint8_t recvCh;
    int32_t result;
    uint32_t bytes_written = 0;
    audio_dev_para_t dev_para;
    audio_card_p snd_card = &snd_card_ssi_wm8962;

    printf("Please ensure headphones are plugged in to hear.\n");

    if (!is_input_char('y', NULL)) {
        printf("  skip AUDIO test \n");
        return TEST_BYPASSED;
    }
    
    audio_codec_power_on();
    audio_clock_config();

    audmux_route(AUDMUX_PORT_2, AUDMUX_PORT_3, AUDMUX_SSI_MASTER);
    dev_para.bus_mode = AUDIO_BUS_MODE_MASTER;

    dev_para.bus_protocol = AUDIO_BUS_PROTOCOL_I2S;
    dev_para.sample_rate = pcm_file->para->sample_rate;
    dev_para.word_length = pcm_file->para->word_length;
    dev_para.trans_dir = AUDIO_TRANS_DIR_TX;

    if (0 != snd_card->ops->init(snd_card)) {
        printf("Init %s failed.\n", snd_card->name);
        return -1;
    }
    if (0 != snd_card->ops->config(snd_card, &dev_para)) {
        printf("Configure %s failed.\n", snd_card->name);
        return -1;
    }

    while (1) {
        snd_card->ops->write(snd_card, pcm_file->buf, pcm_file->size, &bytes_written);

        printf(" Do you need to re-hear it? (y/n)\n");

        do {
            recvCh = getchar();
        }
        while (recvCh == (uint8_t) 0xFF);

        if ((recvCh == 'Y') || (recvCh == 'y'))
            continue;           /* hear again */
        else
            break;              /* by pass */
    }

    printf(" Do you hear audio from headphone? (y/n)\n");

    do {
        recvCh = getchar();
    }
    while (recvCh == (uint8_t) 0xFF);

    if ((recvCh == 'y') || (recvCh == 'Y'))
        result = 0;             /* If user types 'Y' or 'y' test passed */
    else
        result = -1;            /* Else test failed */

    return result;
}
