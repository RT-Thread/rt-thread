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

#include "pcm_local.h"

int snd_pcm_format_signed(snd_pcm_format_t format)
{
    switch (format) {
    case SND_PCM_FORMAT_S8:
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
    case SND_PCM_FORMAT_S24_LE:
    case SND_PCM_FORMAT_S24_BE:
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
        return 1;
    case SND_PCM_FORMAT_U8:
    case SND_PCM_FORMAT_U16_LE:
    case SND_PCM_FORMAT_U16_BE:
    case SND_PCM_FORMAT_U24_LE:
    case SND_PCM_FORMAT_U24_BE:
    case SND_PCM_FORMAT_U32_LE:
    case SND_PCM_FORMAT_U32_BE:
        return 0;
    default:
        return -EINVAL;
    }
}

int snd_pcm_format_unsigned(snd_pcm_format_t format)
{
    int val;

    val = snd_pcm_format_signed(format);
    if (val < 0)
        return val;
    return !val;
}

int snd_pcm_format_linear(snd_pcm_format_t format)
{
    return snd_pcm_format_signed(format) >= 0;
}

int snd_pcm_format_little_endian(snd_pcm_format_t format)
{
    switch (format) {
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_U16_LE:
    case SND_PCM_FORMAT_S24_LE:
    case SND_PCM_FORMAT_U24_LE:
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_U32_LE:
        return 1;
    case SND_PCM_FORMAT_S16_BE:
    case SND_PCM_FORMAT_U16_BE:
    case SND_PCM_FORMAT_S24_BE:
    case SND_PCM_FORMAT_U24_BE:
    case SND_PCM_FORMAT_S32_BE:
    case SND_PCM_FORMAT_U32_BE:
        return 0;
    default:
        return -EINVAL;
    }
}

int snd_pcm_format_big_endian(snd_pcm_format_t format)
{
    int val;

    val = snd_pcm_format_little_endian(format);
    if (val < 0)
        return val;
    return !val;
}

int snd_pcm_format_width(snd_pcm_format_t format)
{
    switch (format) {
    case SND_PCM_FORMAT_S8:
    case SND_PCM_FORMAT_U8:
        return 8;
    case SND_PCM_FORMAT_S16_LE:
    case SND_PCM_FORMAT_S16_BE:
    case SND_PCM_FORMAT_U16_LE:
    case SND_PCM_FORMAT_U16_BE:
        return 16;
    case SND_PCM_FORMAT_S24_LE:
    case SND_PCM_FORMAT_S24_BE:
    case SND_PCM_FORMAT_U24_LE:
    case SND_PCM_FORMAT_U24_BE:
        return 24;
    case SND_PCM_FORMAT_S32_LE:
    case SND_PCM_FORMAT_S32_BE:
    case SND_PCM_FORMAT_U32_LE:
    case SND_PCM_FORMAT_U32_BE:
        return 32;
    default:
        return -EINVAL;
    }
}

static const int linear_formats[4][2][2] = {
    { { SND_PCM_FORMAT_S8, SND_PCM_FORMAT_S8 },
      { SND_PCM_FORMAT_U8, SND_PCM_FORMAT_U8 } },
    { { SND_PCM_FORMAT_S16_LE, SND_PCM_FORMAT_S16_BE },
      { SND_PCM_FORMAT_U16_LE, SND_PCM_FORMAT_U16_BE } },
    { { SND_PCM_FORMAT_S24_LE, SND_PCM_FORMAT_S24_BE },
      { SND_PCM_FORMAT_U24_LE, SND_PCM_FORMAT_U24_BE } },
    { { SND_PCM_FORMAT_S32_LE, SND_PCM_FORMAT_S32_BE },
      { SND_PCM_FORMAT_U32_LE, SND_PCM_FORMAT_U32_BE } }
};

/**
 * \brief Compose a PCM sample linear format
 * \param width Nominal bits per sample
 * \param pwidth Physical bit width of the format
 * \param unsignd Sign: 0 signed, 1 unsigned
 * \param big_endian Endian: 0 little endian, 1 big endian
 * \return The matching format type, or #SND_PCM_FORMAT_UNKNOWN if no match
 */
snd_pcm_format_t snd_pcm_build_linear_format(int width, int pwidth, int unsignd, int big_endian)
{
    if (pwidth == 24) {
#if 0
        switch (width) {
        case 24:
            width = 0;
            break;
        case 20:
            width = 1;
            break;
        case 18:
            width = 2;
            break;
        default:
            return SND_PCM_FORMAT_UNKNOWN;
        }
        return linear24_formats[width][!!unsignd][!!big_endian];
#else
        return SND_PCM_FORMAT_UNKNOWN;
#endif
    } else {
        switch (width) {
        case 8:
            width = 0;
            break;
        case 16:
            width = 1;
            break;
        case 24:
            width = 2;
            break;
        case 32:
            width = 3;
            break;
        default:
            return SND_PCM_FORMAT_UNKNOWN;
        }
        return linear_formats[width][!!unsignd][!!big_endian];
    }
}
