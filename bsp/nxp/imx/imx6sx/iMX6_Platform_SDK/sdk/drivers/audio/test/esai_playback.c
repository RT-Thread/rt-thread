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
 * @file esai_playback.c
 * @brief ESAI test example
 *
 */

#include <stdio.h>
#include "sdk.h"
#include "audio/audio.h"

#ifdef ESAI_AC97_SUPPORT
#include "core/cortex_a9.h"
#include "core/mmu.h"
#endif

extern audio_card_t snd_card_esai;

int32_t esai_playback(audio_pcm_p pcm_file)
{
    uint8_t recvCh;
    int32_t result;
    uint32_t bytes_written = 0;
    audio_card_p snd_card = &snd_card_esai;
    audio_dev_para_t dev_para;

    recvCh = recvCh;
#ifdef ESAI_AC97_SUPPORT
    dev_para.bus_protocol = AUDIO_BUS_PROTOCOL_AC97;
#endif
    dev_para.bus_mode = AUDIO_BUS_MODE_MASTER;
    dev_para.trans_dir = AUDIO_TRANS_DIR_TX;
    /* ESAI driver supports 48KHz only because of CS42888 issue */
    dev_para.sample_rate = SAMPLERATE_48KHz;
    dev_para.word_length = pcm_file->para->word_length;
#ifndef ESAI_AC97_SUPPORT
    dev_para.channel_number = pcm_file->para->channel_number;
#endif

    printf("Please ensure:\n");
    printf
        (" 1. i.MX6DQ_EVB board and the Automotive Card are both mounted to the ARMADILLO 2 board.\n");
    printf
        (" 2. The converting cable's two plugs were plugged into the Automotive Card's AOUT1 and AOUT2 sockets.\n");
    printf(" 3. The headphone is plugged into the converting cable's socket.\n");
    if (!is_input_char('y', NULL)) {
        printf("  skip AUDIO test \n");
        return TEST_BYPASSED;
    }

    if (0 != snd_card->ops->init(snd_card)) {
        printf("Init %s failed.\n", snd_card->name);
        return -1;
    }
    if (0 != snd_card->ops->config(snd_card, &dev_para)) {
        printf("Configure %s failed.\n", snd_card->name);
        return -1;
    }
#ifdef ESAI_AC97_SUPPORT
    /* enable L1 cache for mx6dq and mx6sdl */
    arm_icache_enable();
    arm_dcache_invalidate();
    mmu_enable();
    arm_dcache_enable();
    /*
     * Keep driving special patterns on the esai bus to easy the probing.
     * For testing only.
     */
    printf("Since no mx6x reference board supports AC97, this program\n");
    printf("keeps driving special patterns on the esai bus to easy the probing.\n");
    unsigned short ac97_pattern[] =
        { 0x8000, 0x0000, 0xa000, 0x0000, 0xa800, 0x0000, 0xaa00, 0x0000, 0xaa80, 0x0000, 0xaaa0,
0x0000, 0xaaa8,
        0x8000, 0x0000, 0xa000, 0x0000, 0xa800, 0x0000, 0xaa00, 0x0000, 0xaa80, 0x0000, 0xaaa0,
            0x0000, 0xaaa8,
        0x8000, 0x0000, 0xa000, 0x0000, 0xa800, 0x0000, 0xaa00, 0x0000, 0xaa80, 0x0000, 0xaaa0,
            0x0000, 0xaaa8,
        0x8000, 0x0000, 0xa000, 0x0000, 0xa800, 0x0000, 0xaa00, 0x0000, 0xaa80, 0x0000, 0xaaa0,
            0x0000, 0xaaa8
    };
    pcm_file->buf = (unsigned char *)ac97_pattern;
    pcm_file->size = sizeof(ac97_pattern);
#endif
    /*
     * CS42888 driver supports 48/44.1KHz only, although it was 
     * expected to support all sample rates.  When lower sample rate used,
     * no audio output.
     * It is supposed that the pcm was 16KHz, and we should convert it to 48KHz,
     */
     uint8_t *buf_sr_48K = malloc(pcm_file->size * 3);
     if(NULL == buf_sr_48K){
	printf("Failed to malloc pcm buf for up-samplerate.\n");
	return -1;
     } 
     uint16_t *sample_dst = (uint16_t *)buf_sr_48K;
     uint16_t *sample_src = (uint16_t *)pcm_file->buf;
     uint16_t r_val, l_val;
     for(int i = 0; i < pcm_file->size/(pcm_file->para->word_length/8); i+=2){
	r_val = *sample_src++;
	l_val = *sample_src++;
	for(int j=0; j <3; j++){
		*sample_dst++ = r_val;	// R channel  
		*sample_dst++ = l_val;    // L channel
	}
     }

     pcm_file->buf = buf_sr_48K;
     pcm_file->size *= 3; 

    while (1) {
        snd_card->ops->write(snd_card, pcm_file->buf, pcm_file->size, &bytes_written);
#ifndef ESAI_AC97_SUPPORT
        printf(" Do you need to re-hear it? (y/n)\n");

        do {
            recvCh = getchar();
        }
        while (recvCh == (uint8_t) 0xFF);

        if ((recvCh == 'Y') || (recvCh == 'y'))
            continue;           /* hear again */
        else
            break;              /* by pass */
#endif
    }

    free(buf_sr_48K);

#ifndef ESAI_AC97_SUPPORT
    printf(" Do you hear audio from headphone? (y/n)\n");

    do {
        recvCh = getchar();
    }
    while (recvCh == (uint8_t) 0xFF);

    if ((recvCh == 'y') || (recvCh == 'Y'))
        result = 0;             /* If user types 'Y' or 'y' test passed */
    else
        result = -1;            /* Else test failed */
#endif

    return result;
}
