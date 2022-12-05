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
#ifndef __AW_ALSA_COMMON_H
#define __AW_ALSA_COMMON_H
#ifdef __cplusplus
extern "C" {
#endif

#include <sound/ksound.h>
#include <aw-alsa-lib/pcm.h>

/* Other */
static inline int snd_card_index(const char *name)
{
    return ksnd_card_index(name);
}

static inline const char *snd_card_name(int index)
{
    return ksnd_card_name(index);
}

static inline int snd_card_num(void)
{
    return ksnd_card_num();
}

static inline int snd_card_info(int card_num)
{
    return ksnd_card_info(card_num);
}

static inline int snd_card_pcm_info(int card_num, int device_num, int stream)
{
    return ksnd_pcm_stream_info(card_num, device_num, stream);
}

static inline void asound_list(void)
{
        int i, ret = 0;

    ret = snd_card_num();
    if (ret < 0) {
        printf("no registered card...\n");
        return;
    }
    printf("============= Sound Card list =============\n");
    printf("%8s%20s\n", "card_num", "card_name");
    for (i = 0; i < ret; i++) {
        if (i != snd_card_index(snd_card_name(i))) {
            printf("card_num%d not equal index convert"
                "from name:%s\n", i, snd_card_name(i));
            return;
        }
        printf("%8d%20s\n", i, snd_card_name(i));
    }
    printf("\n");
}

#endif
