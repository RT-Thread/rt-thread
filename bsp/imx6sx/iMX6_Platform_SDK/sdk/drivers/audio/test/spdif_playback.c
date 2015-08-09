/*
 * Copyright (c) 2010-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file spdif_playback.c
 * @brief SPDIF test example
 *
 */

#include <stdio.h>
#include "sdk.h"
#include "audio/audio.h"

extern audio_card_t snd_card_spdif;

int32_t spdif_playback(audio_pcm_p pcm_file)
{
    uint8_t recvCh;
    int32_t result;
    uint32_t bytes_written = 0;
    audio_dev_para_t dev_para;
    audio_card_p snd_card = &snd_card_spdif;

    printf("Please make sure : \n");
    printf(" 1. The EVB board was mounted on the MX6QVPC board. \n");
    printf
        (" 2. A rework should be done to connect \"TP6[SPDIF_OUT]\" with \"PORT2_P98\" on the MX6QVPC board\n");
    printf
        (" 3. The \"SPDIF_OUT\" socket is connected with a SPDIF recording device, such as \"M-AUDIO\".\n");
    if (!is_input_char('y', NULL)) {
        printf("  skip AUDIO test \n");
        return TEST_BYPASSED;
    }

    dev_para.bus_mode = AUDIO_BUS_MODE_SLAVE;
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

    uint32_t cnt;
    while (1) {
        cnt = 2;
        while (cnt--) {
            snd_card->ops->write(snd_card, pcm_file->buf, pcm_file->size, &bytes_written);
        }

        printf(" Do you need to re-play it? (y/n)\n");

        do {
            recvCh = getchar();
        }
        while (recvCh == (uint8_t) 0xFF);

        if ((recvCh == 'Y') || (recvCh == 'y'))
            continue;           /* hear again */
        else
            break;              /* by pass */
    }

    printf(" Please replay the audio file just recorded on your PC. Do you hear audio? (y/n)\n");

    do {
        recvCh = getchar();
    }
    while (recvCh == (uint8_t) 0xFF);

    if ((recvCh == 'y') || (recvCh == 'Y'))
        result = 0;             /* If user types 'Y' or 'y' test passed */
    else
        result = -1;            /* Else test failed */

    return result;

    return true;
}
