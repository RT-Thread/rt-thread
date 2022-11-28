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
#include <aw-alsa-lib/pcm.h>
#include <aw-alsa-lib/control.h>
#include <aw-alsa-lib/pcm_plugin.h>
#include "pcm_local.h"

void snd_ctl_open(const char **name)
{
    const snd_pcm_config_t *pcm_config = NULL;
    char ctl_name[32] = "ctl.!";

    strcat(ctl_name, *name);
    pcm_config = snd_pcm_config_get_config(ctl_name);
    if (!pcm_config)
        return ;
    struct {
        const char *type;
        const char *name;
    } snd_pcm_open_ctl_name_table[] = {
        { "hw", ((const snd_pcm_hw_config_t *)(pcm_config->config))->card_name},
    };

    int size = sizeof(snd_pcm_open_ctl_name_table) / sizeof(snd_pcm_open_ctl_name_table[0]);
    int i;
    for (i = 0; i < size; ++i) {
        if (0 == strcmp(pcm_config->type, snd_pcm_open_ctl_name_table[i].type)) {
            *name = snd_pcm_open_ctl_name_table[i].name;
            break;
        }
    }
}

int snd_ctl_num(const char *name)
{
    snd_ctl_open(&name);

    return ksnd_ctl_num(name);
}

int snd_ctl_get_bynum(const char *name, const unsigned int elem_num, snd_ctl_info_t *info)
{
    int ret;

    snd_ctl_open(&name);
    memset(info, 0, sizeof(snd_ctl_info_t));
    ret = ksnd_ctl_get_bynum(name, elem_num, info);

    return ret;
}

int snd_ctl_get(const char *name, const char *elem, snd_ctl_info_t *info)
{
    int ret;

    memset(info, 0, sizeof(snd_ctl_info_t));
    ret = ksnd_ctl_get(name, elem, info);
    awalsa_debug("ret=%d\n", ret);
    return ret;
}

int snd_ctl_set_bynum(const char *name, const unsigned int elem_num, unsigned int val)
{
    int ret;

    ret = ksnd_ctl_set_bynum(name, elem_num, val);
    return ret;
}

int snd_ctl_set(const char *name, const char *elem, unsigned int val)
{
    int ret;

    ret = ksnd_ctl_set(name, elem, val);
    return ret;
}

int snd_ctl_add(const char *name, snd_ctl_info_t *info)
{
    int ret;

    ret = ksnd_ctl_add_elem(name, (void *)info);
    return ret;
}

int snd_ctl_remove(const char *name, const unsigned int elem_num)
{
    int ret;
    ret = ksnd_ctl_remove_elem(name, elem_num);
    return ret;
}
