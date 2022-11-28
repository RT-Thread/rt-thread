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
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <sound/snd_core.h>

int ksnd_ctl_num(const char *name)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k;
    int num = 0;

    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }
    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (!k->name)
            break;
        num++;
        snd_print("card:%s,kcontrol[%u] \"%s\"\n", name, k->id, k->name);
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    return num;
}

int ksnd_ctl_get(const char *name, const char *elem, void *info)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k;
    struct snd_ctl_info *i = info;
    int ret = -1;

    if (!i)
        return -1;
    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }
    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (!strncmp((const char *)k->name, elem, strlen((char *)k->name))) {
            snd_print("card:%s,kcontrol[%u] \"%s\" found...\n", name, k->id, k->name);
            ret = k->get(k, i);
            break;
        }
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    if (ret < 0) {
        snd_info("card %s ctl doesn't have this elem\n", name);
    }
    return ret;
}

int ksnd_ctl_get_bynum(const char *name, const unsigned int elem_num, void *info)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k;
    struct snd_ctl_info *i = info;
    int ret = -1;

    if (!i)
        return -1;
    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }

    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (k->id == elem_num) {
            snd_print("card:%s,kcontrol[%u] \"%s\" found...\n", name, k->id, k->name);
            ret = k->get(k, i);
            break;
        }
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    if (ret < 0) {
        snd_info("card %s ctl doesn't have this elem\n", name);
    }
    return ret;
}

int ksnd_ctl_set(const char *name, const char *elem, unsigned int val)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k;
    int ret = -1;

    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }

    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (!strncmp((const char *)k->name, elem, strlen((char *)k->name))) {
            snd_print("card:%s,kcontrol[%u] \"%s\" found...\n", name, k->id, k->name);
            ret = k->set(k, val);
            break;
        }
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    if (ret < 0)
        snd_err("card %s ctl doesn't have this elem\n", name);
    return ret;
}

int ksnd_ctl_set_bynum(const char *name, const unsigned int elem_num, unsigned int val)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k;
    int ret = -1;

    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }
    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (k->id == elem_num) {
            snd_print("card:%s,kcontrol[%u] \"%s\" found...\n", name, k->id, k->name);
            ret = k->set(k, val);
            break;
        }
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    if (ret < 0)
        snd_err("card %s ctl doesn't have this elem\n", name);
    return ret;
}

int ksnd_ctl_set_multi_args(const char *name, const char *elem, int num, ...)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k, *kcontrol = NULL;
    int j, ret = -1;
    va_list ap;
    unsigned long *value;

    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }

    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (!strncmp((const char *)k->name, elem, strlen((char *)k->name))) {
            kcontrol = k;
            break;
        }
    }
    if (!kcontrol) {
        snd_err("card %s ctl doesn't have this elem\n", name);
        goto err;
    }
    if (kcontrol->count != num) {
        snd_err("actual kcontrol count=%d, but arg num is %d\n",
                    kcontrol->count, num);
        goto err;
    }
    value = snd_malloc(sizeof(unsigned long) * kcontrol->count);

    va_start(ap, num);
    for (j = 0; j < num; j++) {
        value[j] = va_arg(ap, unsigned long);
        snd_print("arg%d is :%d\n", j, value[j]);
    }
    va_end(ap);

    ret = kcontrol->set(kcontrol, (unsigned long)value);
err:
    snd_mutex_unlock(card->ctl->ctl_mutex);
    return ret;
}

int ksnd_ctl_add_elem(const char *name, void *info)
{
    struct snd_card *card = NULL;
    struct snd_ctl_info *i = info;
    int ret;

    if (!i)
        return -1;
    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }

    snd_mutex_lock(card->ctl->ctl_mutex);
    ret = snd_ctl_add_elem(card->ctl, i);
    snd_mutex_unlock(card->ctl->ctl_mutex);
    return ret;
}

int ksnd_ctl_remove_elem(const char *name, const unsigned int elem_num)
{
    struct snd_card *card = NULL;
    struct snd_kcontrol *k = NULL;
    int ret = -1;

    card = snd_card_find_by_name(name);
    if (!card) {
        snd_err("no card %s\n", name);
        return -1;
    }
    if (!card->ctl) {
        snd_err("card %s has no ctl\n", name);
        return -1;
    }

    snd_mutex_lock(card->ctl->ctl_mutex);
    list_for_each_entry(k, &card->ctl->controls, list) {
        if (k->id == elem_num) {
            ret = snd_ctl_remove_elem(card->ctl, k);
            break;
        }
    }
    snd_mutex_unlock(card->ctl->ctl_mutex);
    return ret;
}
