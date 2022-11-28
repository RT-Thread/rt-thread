/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <stdio.h>
#include <string.h>
#include "wav_parser.h"

#define WAV_DEBUG
#ifdef WAV_DEBUG
void dump_wav_header(wav_header_t *header)
{
#if 1
    char *ptr = (char *)&header->riffType;
    printf("riffType:     %c%c%c%c\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    ptr = (char *)&header->waveType;
    printf("waveType:     %c%c%c%c\n", ptr[0], ptr[1], ptr[2], ptr[3]);
    printf("channels:     %u\n", header->numChannels);
    printf("rate:         %u\n", header->sampleRate);
    printf("bits:         %u\n", header->bitsPerSample);
    printf("align:        %u\n", header->blockAlign);
    printf("data size:    %u\n", header->dataSize);
#else
    int i;
    unsigned char *ptr = (unsigned char *)header;
    for (i = 0; i < sizeof(wav_header_t); i++) {
        if (i%16 == 0)
            printf("\n");
        printf("0x%02x ", ptr[i]);
    }
    printf("\n");
#endif
}
#else
void dump_wav_header(wav_header_t *header)
{

}
#endif


int check_wav_header(wav_header_t *header, wav_hw_params_t *hwparams)
{
    if (!header)
        return -1;

    dump_wav_header(header);

    if (header->riffType != WAV_RIFF)
        return -1;
    if (header->waveType != WAV_WAVE)
        return -1;

    hwparams->rate = header->sampleRate;
    hwparams->channels = header->numChannels;
    /* ignore bit endian */
    switch (header->bitsPerSample) {
    case 8:
        hwparams->format = SND_PCM_FORMAT_U8;
        break;
    case 16:
        hwparams->format = SND_PCM_FORMAT_S16_LE;
        break;
    case 24:
        switch (header->blockAlign/header->numChannels) {
            case 4:
                hwparams->format = SND_PCM_FORMAT_S24_LE;
                break;
            case 3:
                /*hwparams->format = SND_PCM_FORMAT_S24_3LE;*/
            default:
                printf("unknown format..\n");
                return -1;
        }
        break;
    case 32:
        hwparams->format = SND_PCM_FORMAT_S32_LE;
        break;
    default:
        break;
    }

    return 0;
}

void resize_wav(wav_header_t *header, unsigned int size)
{
    header->dataSize = LE_INT(size);
    header->riffSize = LE_INT(size + 36);
    dump_wav_header(header);
}

void create_wav(wav_header_t *header, unsigned int format, unsigned int rate, unsigned int channels)
{
    unsigned int bits = 0, align = 0;

    memset(header, 0 , sizeof(wav_header_t));
    switch (format) {
    case SND_PCM_FORMAT_S16_LE:
        bits = 16;
        align = 2;
        break;
    case SND_PCM_FORMAT_S24_LE:
        bits = 24;
        align = 4;
        break;
    case SND_PCM_FORMAT_S32_LE:
        bits = 32;
        align = 4;
        break;
    }
    header->riffType = WAV_RIFF;
    header->riffSize = LE_INT(36);
    header->waveType = WAV_WAVE;
    header->formatType = WAV_FMT;
    header->formatSize = LE_INT(16);
    /* PCM */
    header->compressionCode = LE_INT(0x0001);
    header->numChannels = channels;
    header->sampleRate = rate;
    header->bytesPerSecond =
        rate * snd_pcm_format_physical_width(format) / 8;
    header->blockAlign = align * channels;
    header->bitsPerSample = bits;
    header->dataType = WAV_DATA;
    header->dataSize = 0;
}
