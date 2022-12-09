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
#include <sound/snd_core.h>
#include <sound/snd_pcm.h>
#include <sound/snd_misc.h>

#define HW_PARAM(v) [SND_PCM_HW_PARAM_##v] = #v
static const char * const snd_pcm_hw_param_names[] = {
    HW_PARAM(ACCESS),
    HW_PARAM(FORMAT),
    HW_PARAM(SAMPLE_BITS),
    HW_PARAM(FRAME_BITS),
    HW_PARAM(CHANNELS),
    HW_PARAM(RATE),
    HW_PARAM(PERIOD_TIME),
    HW_PARAM(PERIOD_SIZE),
    HW_PARAM(PERIOD_BYTES),
    HW_PARAM(PERIODS),
    HW_PARAM(BUFFER_TIME),
    HW_PARAM(BUFFER_SIZE),
    HW_PARAM(BUFFER_BYTES),
};

const char *snd_pcm_hw_param_name(snd_pcm_hw_param_t param)
{
    return snd_pcm_hw_param_names[param];
}

int snd_range_refine(snd_interval_t *i, const snd_interval_t *v)
{
    int changed = 0;
    if (snd_range_empty(i))
        return -EINVAL;

    if (i->range.min < v->range.min) {
        i->range.min = v->range.min;
        i->range.openmin = v->range.openmin;
        changed = 1;
    } else if (i->range.min == v->range.min && !i->range.openmin && v->range.openmin) {
        i->range.openmin = 1;
        changed = 1;
    }

    if (i->range.max > v->range.max) {
        i->range.max = v->range.max;
        i->range.openmax = v->range.openmax;
        changed = 1;
    } else if (i->range.max == v->range.max && !i->range.openmax && v->range.openmax) {
        i->range.openmax = 1;
        changed = 1;
    }

    if (!i->range.integer && v->range.integer) {
        i->range.integer = 1;
        changed = 1;
    }
    if (i->range.integer) {
        if (i->range.openmin) {
            i->range.min++;
            i->range.openmin = 0;
        }
        if (i->range.openmax) {
            i->range.max--;
            i->range.openmax = 0;
        }
    } else if (!i->range.openmin && !i->range.openmax && i->range.min == i->range.max) {
        i->range.integer = 1;
    }

    if (snd_range_checkempty(i)) {
        snd_range_none(i);
        return -EINVAL;
    }
    return changed;
}

int snd_range_refine_first(snd_interval_t *i)
{
    if (snd_range_empty(i))
        return -EINVAL;
    if (snd_range_single(i))
        return 0;
    i->range.max = i->range.min;
    i->range.openmax = i->range.openmin;
    if (i->range.openmax)
        i->range.max++;
    return 1;
}

int snd_range_refine_last(snd_interval_t *i)
{
    if (snd_range_empty(i))
        return -EINVAL;
    if (snd_range_single(i))
        return 0;
    i->range.min = i->range.max;
    i->range.openmin = i->range.openmax;
    if (i->range.openmin)
        i->range.min--;
    return 1;
}

int snd_range_refine_min(snd_interval_t *i, unsigned int min, int openmin)
{
    int changed = 0;
    if (snd_range_empty(i))
        return -ENOENT;
    if (i->range.min < min) {
        i->range.min = min;
        i->range.openmin = openmin;
        changed = 1;
    } else if (i->range.min == min && !i->range.openmin && openmin) {
        i->range.openmin = 1;
        changed = 1;
    }
    if (i->range.integer) {
        if (i->range.openmin) {
            i->range.min++;
            i->range.openmin = 0;
        }
    }
    if (snd_range_checkempty(i)) {
        snd_range_none(i);
        return -EINVAL;
    }
    return changed;
}

int snd_range_refine_max(snd_interval_t *i, unsigned int max, int openmax)
{
    int changed = 0;
    if (snd_range_empty(i))
        return -ENOENT;
    if (i->range.max > max) {
        i->range.max = max;
        i->range.openmax = openmax;
        changed = 1;
    } else if (i->range.max == max && !i->range.openmax && openmax) {
        i->range.openmax = 1;
        changed = 1;
    }
    if (i->range.integer) {
        if (i->range.openmax) {
            i->range.max--;
            i->range.openmax = 0;
        }
    }
    if (snd_range_checkempty(i)) {
        snd_range_none(i);
        return -EINVAL;
    }
    return changed;
}

int snd_range_refine_set(snd_interval_t *i, unsigned int val)
{
    snd_interval_t t;
    t.range.empty = 0;
    t.range.min = t.range.max = val;
    t.range.openmin = t.range.openmax = 0;
    t.range.integer = 1;
    return snd_range_refine(i, &t);
}

void snd_range_add(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c)
{
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = add(a->range.min, b->range.min);
    c->range.openmin = (a->range.openmin || b->range.openmin);
    c->range.max = add(a->range.max,  b->range.max);
    c->range.openmax = (a->range.openmax || b->range.openmax);
    c->range.integer = (a->range.integer && b->range.integer);
}

void snd_interval_sub(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c)
{
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = sub(a->range.min, b->range.max);
    c->range.openmin = (a->range.openmin || b->range.openmax);
    c->range.max = add(a->range.max,  b->range.min);
    c->range.openmax = (a->range.openmax || b->range.openmin);
    c->range.integer = (a->range.integer && b->range.integer);
}

void snd_range_mul(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c)
{
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = mul(a->range.min, b->range.min);
    c->range.openmin = (a->range.openmin || b->range.openmin);
    c->range.max = mul(a->range.max, b->range.max);
    c->range.openmax = (a->range.openmax || b->range.openmax);
    c->range.integer = (a->range.integer && b->range.integer);
}

/**
 * snd_range_div - refine the range value with division
 * @a: dividend
 * @b: divisor
 * @c: quotient
 *
 * c = a / b
 *
 * Returns non-zero if the value is changed, zero if not changed.
 */
void snd_range_div(const snd_interval_t *a, const snd_interval_t *b, snd_interval_t *c)
{
    unsigned int r;
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = div32(a->range.min, b->range.max, &r);
    c->range.openmin = (r || a->range.openmin || b->range.openmax);
    if (b->range.min > 0) {
        c->range.max = div32(a->range.max, b->range.min, &r);
        if (r) {
            c->range.max++;
            c->range.openmax = 1;
        } else {
            c->range.openmax = (a->range.openmax || b->range.openmin);
        }
    } else {
        c->range.max = UINT_MAX;
        c->range.openmax = 0;
    }
    c->range.integer = 0;
}

/* a * b / c */
void snd_range_muldiv(const snd_interval_t *a, const snd_interval_t *b,
        const snd_interval_t *c, snd_interval_t *d)
{
    unsigned int r;
    if (a->range.empty || b->range.empty || c->range.empty) {
        snd_range_none(d);
        return;
    }
    d->range.empty = 0;
    d->range.min = muldiv32(a->range.min, b->range.min, c->range.max, &r);
    d->range.openmin = (r || a->range.openmin || b->range.openmin || c->range.openmax);
    d->range.max = muldiv32(a->range.max, b->range.max, c->range.min, &r);
    if (r) {
        d->range.max++;
        d->range.openmax = 1;
    } else
        d->range.openmax = (a->range.openmax || b->range.openmax || c->range.openmin);
    d->range.integer = 0;
}

/**
 * snd_range_muldivk - refine the range value
 * @a: dividend 1
 * @b: dividend 2
 * @k: divisor (as integer)
 * @c: result
  *
 * c = a * b / k
 *
 * Returns non-zero if the value is changed, zero if not changed.
 */
void snd_range_muldivk(const snd_interval_t *a, const snd_interval_t *b,
        unsigned int k, snd_interval_t *c)
{
    unsigned int r;
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = muldiv32(a->range.min, b->range.min, k, &r);
    c->range.openmin = (r || a->range.openmin || b->range.openmin);
    c->range.max = muldiv32(a->range.max, b->range.max, k, &r);
    if (r) {
        c->range.max++;
        c->range.openmax = 1;
    } else {
        c->range.openmax = (a->range.openmax || b->range.openmax);
    }
    c->range.integer = 0;
}

/**
 * snd_range_mulkdiv - refine the range value
 * @a: dividend 1
 * @k: dividend 2 (as integer)
 * @b: divisor
 * @c: result
 *
 * c = a * k / b
 *
 * Returns non-zero if the value is changed, zero if not changed.
 */
void snd_range_mulkdiv(const snd_interval_t *a, unsigned int k,
        const snd_interval_t *b, snd_interval_t *c)
{
    unsigned int r;
    if (a->range.empty || b->range.empty) {
        snd_range_none(c);
        return;
    }
    c->range.empty = 0;
    c->range.min = muldiv32(a->range.min, k, b->range.max, &r);
    c->range.openmin = (r || a->range.openmin || b->range.openmax);
    if (b->range.min > 0) {
        c->range.max = muldiv32(a->range.max, k, b->range.min, &r);
        if (r) {
            c->range.max++;
            c->range.openmax = 1;
        } else {
            c->range.openmax = (a->range.openmax || b->range.openmin);
        }
    } else {
        c->range.max = UINT_MAX;
        c->range.openmax = 0;
    }
    c->range.integer = 0;
}

/**
 * snd_range_list - refine the range value from the list
 * @i: the interval value to refine
 * @count: the number of elements in the list
 * @list: the value list
 * @mask: the bit-mask to evaluate
 *
 * Refines the interval value from the list.
 * When mask is non-zero, only the elements corresponding to bit 1 are
 * evaluated.
 *
 * Return: Positive if the value is changed, zero if it's not changed, or a
 * negative error code.
 */
int snd_range_list(snd_interval_t *i, unsigned int count,
        const unsigned int *list, unsigned int mask)
{
    unsigned int k;
    snd_interval_t list_range;

    if (!count) {
        i->range.empty = 1;
        return -EINVAL;
    }
    snd_range_any(&list_range);
    list_range.range.min = UINT_MAX;
    list_range.range.max = 0;
    for (k = 0; k < count; k++) {
        if (mask && !(mask & (1 << k)))
            continue;
        if (!snd_range_test(i, list[k]))
            continue;
        list_range.range.min = min(list_range.range.min, list[k]);
        list_range.range.max = max(list_range.range.max, list[k]);
    }
    return snd_range_refine(i, &list_range);
}

int snd_pcm_hw_rule_mul(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    snd_range_mul(hw_param_interval(params, rule->deps[0]),
            hw_param_interval(params, rule->deps[1]), &t);
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}

int snd_pcm_hw_rule_div(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    snd_range_div(hw_param_interval(params, rule->deps[0]),
            hw_param_interval(params, rule->deps[1]), &t);
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}

int snd_pcm_hw_rule_muldivk(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    snd_range_muldivk(hw_param_interval(params, rule->deps[0]),
            hw_param_interval(params, rule->deps[1]),
            (unsigned long) rule->private_data, &t);
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}

int snd_pcm_hw_rule_mulkdiv(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    snd_range_mulkdiv(hw_param_interval_c(params, rule->deps[0]),
            (unsigned long) rule->private_data,
            hw_param_interval_c(params, rule->deps[1]), &t);
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}

int snd_pcm_hw_rule_format(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    unsigned int k;
    snd_interval_t *dep_i = hw_param_interval(params, rule->deps[0]);
    snd_interval_t tmp_i;
    snd_interval_t *interval = hw_param_interval(params, SND_PCM_HW_PARAM_FORMAT);
    snd_mask_any(&tmp_i);
    for (k = 0; k <= SND_PCM_FORMAT_LAST; ++k) {
        int bits;
        if (! snd_mask_test(interval, k))
            continue;
        bits = snd_pcm_format_physical_width(k);
        if (bits <= 0)
            continue; /* ignore invalid formats */
        if ((unsigned)bits < dep_i->range.min || (unsigned)bits > dep_i->range.max)
            snd_mask_reset(&tmp_i, k);
    }
    return snd_mask_refine(interval, &tmp_i);
}

int snd_pcm_hw_rule_sample_bits(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    unsigned int k;
    t.range.min = UINT_MAX;
    t.range.max = 0;
    t.range.openmin = 0;
    t.range.openmax = 0;
    for (k = 0; k <= SND_PCM_FORMAT_LAST; ++k) {
        int bits;
        if (! snd_mask_test(hw_param_interval(params, SND_PCM_HW_PARAM_FORMAT), k))
            continue;
        bits = snd_pcm_format_physical_width(k);
        if (bits <= 0)
            continue; /* ignore invalid formats */
        if (t.range.min > (unsigned)bits)
            t.range.min = bits;
        if (t.range.max < (unsigned)bits)
            t.range.max = bits;
    }
    t.range.integer = 1;
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}

int snd_pcm_hw_rule_rate(struct snd_pcm_hw_params *params, struct snd_pcm_hw_rule *rule)
{
    struct snd_pcm_hardware *hw = rule->private_data;
    return snd_range_list(hw_param_interval(params, rule->var),
            snd_pcm_known_rates.count,
            snd_pcm_known_rates.list, hw->rates);
}

int snd_pcm_hw_rule_buffer_bytes_max(struct snd_pcm_hw_params *params,
        struct snd_pcm_hw_rule *rule)
{
    snd_interval_t t;
    struct snd_pcm_substream *substream = rule->private_data;
    t.range.min = 0;
    t.range.max = substream->runtime->hw.buffer_bytes_max;
    t.range.openmin = 0;
    t.range.openmax = 0;
    t.range.integer = 1;
    return snd_range_refine(hw_param_interval(params, rule->var), &t);
}
