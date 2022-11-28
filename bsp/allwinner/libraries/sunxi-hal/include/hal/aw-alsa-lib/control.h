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
#ifndef __AW_ALSA_CONTROL_H
#define __AW_ALSA_CONTROL_H
#ifdef __cplusplus
extern "C" {
#endif

#include <sound/ksound.h>

typedef int snd_ctl_elem_type_t;
#define SND_CTL_ELEM_TYPE_INTEGER ((snd_ctl_elem_type_t)0)
#define SND_CTL_ELEM_TYPE_ENUMERATED ((snd_ctl_elem_type_t)1)
#define SND_CTL_ELEM_TYPE_LAST SND_CTL_ELEM_TYPE_ENUMERATED

/* can't modify this struct */
typedef struct {
    unsigned int id;
        snd_ctl_elem_type_t type;
    const unsigned char *name;
    unsigned long value;
    int min,max;
    int count;
    /* for enum */
    unsigned int items;
    const char * const *texts;

    const unsigned long *private_data;
} snd_ctl_info_t;

int snd_ctl_num(const char *name);
int snd_ctl_get(const char *name, const char *elem, snd_ctl_info_t *info);
int snd_ctl_get_bynum(const char *name, const unsigned int elem_num, snd_ctl_info_t *info);
int snd_ctl_set(const char *name, const char *elem, unsigned int val);
int snd_ctl_set_bynum(const char *name, const unsigned int elem_num, unsigned int val);
int snd_ctl_add(const char *name, snd_ctl_info_t *info);
int snd_ctl_remove(const char *name, const unsigned int elem_num);
#define snd_ctl_set_multi_args  ksnd_ctl_set_multi_args

#ifdef __cplusplus
}
#endif

#endif /* __AW_ALSA_CONTROL_H */
