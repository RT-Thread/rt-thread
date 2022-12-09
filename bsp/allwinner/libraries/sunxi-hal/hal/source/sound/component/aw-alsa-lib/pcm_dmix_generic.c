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


/* non-concurrent version, only supporting little endians */
#define generic_dmix_supported_format \
    ((1ULL << SND_PCM_FORMAT_S16_LE) | (1ULL << SND_PCM_FORMAT_S32_LE) |\
     (1ULL << SND_PCM_FORMAT_S24_LE) | (1ULL << SND_PCM_FORMAT_S24_3LE) | \
     (1ULL << SND_PCM_FORMAT_U8))

static void generic_mix_areas_16_native(unsigned int size,
                    volatile signed short *dst,
                    signed short *src,
                    volatile signed int *sum,
                    size_t dst_step,
                    size_t src_step,
                    size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = *src;
        if (! *dst) {
            *sum = sample;
            *dst = *src;
        } else {
            sample += *sum;
            *sum = sample;
            if (sample > 0x7fff)
                sample = 0x7fff;
            else if (sample < -0x8000)
                sample = -0x8000;
            *dst = sample;
        }
        if (!--size)
            return;
        src = (signed short *) ((char *)src + src_step);
        dst = (signed short *) ((char *)dst + dst_step);
        sum = (signed int *)   ((char *)sum + sum_step);
    }
}

static void generic_remix_areas_16_native(unsigned int size,
                      volatile signed short *dst,
                      signed short *src,
                      volatile signed int *sum,
                      size_t dst_step,
                      size_t src_step,
                      size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = *src;
        if (! *dst) {
            *sum = -sample;
            *dst = -sample;
        } else {
            *sum = sample = *sum - sample;
            if (sample > 0x7fff)
                sample = 0x7fff;
            else if (sample < -0x8000)
                sample = -0x8000;
            *dst = sample;
        }
        if (!--size)
            return;
        src = (signed short *) ((char *)src + src_step);
        dst = (signed short *) ((char *)dst + dst_step);
        sum = (signed int *)   ((char *)sum + sum_step);
    }
}

static void generic_mix_areas_32_native(unsigned int size,
                    volatile signed int *dst,
                    signed int *src,
                    volatile signed int *sum,
                    size_t dst_step,
                    size_t src_step,
                    size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = *src >> 8;
        if (! *dst) {
            *sum = sample;
            *dst = *src;
        } else {
            sample += *sum;
            *sum = sample;
            if (sample > 0x7fffff)
                sample = 0x7fffffff;
            else if (sample < -0x800000)
                sample = -0x80000000;
            else
                sample *= 256;
            *dst = sample;
        }
        if (!--size)
            return;
        src = (signed int *) ((char *)src + src_step);
        dst = (signed int *) ((char *)dst + dst_step);
        sum = (signed int *) ((char *)sum + sum_step);
    }
}

static void generic_remix_areas_32_native(unsigned int size,
                      volatile signed int *dst,
                      signed int *src,
                      volatile signed int *sum,
                      size_t dst_step,
                      size_t src_step,
                      size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = *src >> 8;
        if (! *dst) {
            *sum = -sample;
            *dst = -*src;
        } else {
            *sum = sample = *sum - sample;
            if (sample > 0x7fffff)
                sample = 0x7fffffff;
            else if (sample < -0x800000)
                sample = -0x80000000;
            else
                sample *= 256;
            *dst = sample;
        }
        if (!--size)
            return;
        src = (signed int *) ((char *)src + src_step);
        dst = (signed int *) ((char *)dst + dst_step);
        sum = (signed int *) ((char *)sum + sum_step);
    }
}

/* always little endian */
static void generic_mix_areas_24(unsigned int size,
                 volatile unsigned char *dst,
                 unsigned char *src,
                 volatile signed int *sum,
                 size_t dst_step,
                 size_t src_step,
                 size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = src[0] | (src[1] << 8) | (((signed char *)src)[2] << 16);
        if (!(dst[0] | dst[1] | dst[2])) {
            *sum = sample;
        } else {
            sample += *sum;
            *sum = sample;
            if (sample > 0x7fffff)
                sample = 0x7fffff;
            else if (sample < -0x800000)
                sample = -0x800000;
        }
        dst[0] = sample;
        dst[1] = sample >> 8;
        dst[2] = sample >> 16;
        if (!--size)
            return;
        dst += dst_step;
        src += src_step;
        sum = (signed int *) ((char *)sum + sum_step);
    }
}

static void generic_remix_areas_24(unsigned int size,
                   volatile unsigned char *dst,
                   unsigned char *src,
                   volatile signed int *sum,
                   size_t dst_step,
                   size_t src_step,
                   size_t sum_step)
{
    register signed int sample;

    for (;;) {
        sample = src[0] | (src[1] << 8) | (((signed char *)src)[2] << 16);
        if (!(dst[0] | dst[1] | dst[2])) {
            sample = -sample;
            *sum = sample;
        } else {
            *sum = sample = *sum - sample;
            if (sample > 0x7fffff)
                sample = 0x7fffff;
            else if (sample < -0x800000)
                sample = -0x800000;
        }
        dst[0] = sample;
        dst[1] = sample >> 8;
        dst[2] = sample >> 16;
        if (!--size)
            return;
        dst += dst_step;
        src += src_step;
        sum = (signed int *) ((char *)sum + sum_step);
    }
}

static void generic_mix_areas_u8(unsigned int size,
                 volatile unsigned char *dst,
                 unsigned char *src,
                 volatile signed int *sum,
                 size_t dst_step,
                 size_t src_step,
                 size_t sum_step)
{
    for (;;) {
        register int sample = *src - 0x80;
        if (*dst == 0x80) {
            *sum = sample;
        } else {
            sample += *sum;
            *sum = sample;
            if (sample > 0x7f)
                sample = 0x7f;
            else if (sample < -0x80)
                sample = -0x80;
        }
        *dst = sample + 0x80;
        if (!--size)
            return;
        dst += dst_step;
        src += src_step;
        sum = (signed int *) ((char *)sum + sum_step);
    }
}

static void generic_remix_areas_u8(unsigned int size,
                   volatile unsigned char *dst,
                   unsigned char *src,
                   volatile signed int *sum,
                   size_t dst_step,
                   size_t src_step,
                   size_t sum_step)
{
    for (;;) {
        register int sample = *src - 0x80;
        if (*dst == 0x80) {
            sample = -sample;
            *sum = sample;
        } else {
            *sum = sample = *sum - sample;
            if (sample > 0x7f)
                sample = 0x7f;
            else if (sample < -0x80)
                sample = -0x80;
        }
        *dst = sample + 0x80;
        if (!--size)
            return;
        dst += dst_step;
        src += src_step;
        sum = (signed int *) ((char *)sum + sum_step);
    }
}


static void generic_mix_select_callbacks(snd_pcm_direct_t *dmix)
{
    /* only support native version, not support swap version */

    dmix->u.dmix.mix_areas_16 = generic_mix_areas_16_native;
    dmix->u.dmix.mix_areas_32 = generic_mix_areas_32_native;
    dmix->u.dmix.remix_areas_16 = generic_remix_areas_16_native;
    dmix->u.dmix.remix_areas_32 = generic_remix_areas_32_native;

    dmix->u.dmix.mix_areas_24 = generic_mix_areas_24;
    dmix->u.dmix.mix_areas_u8 = generic_mix_areas_u8;
    dmix->u.dmix.remix_areas_24 = generic_remix_areas_24;
    dmix->u.dmix.remix_areas_u8 = generic_remix_areas_u8;
}
