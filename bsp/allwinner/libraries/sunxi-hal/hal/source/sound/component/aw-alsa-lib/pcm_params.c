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

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "pcm_local.h"

#ifdef REFINE_DEBUG
static void dump_hw_params(snd_pcm_hw_params_t *params, const char *type,
               snd_pcm_hw_param_t var, unsigned int val, int err)
{
    awalsa_info("ALSA ERROR hw_params: %s (%s)\n", type, snd_pcm_hw_param_name(var));
    fprintf(stderr, "           value = ");
    switch (var) {
    case SND_PCM_HW_PARAM_ACCESS:
        fprintf(stderr, "%s", snd_pcm_access_name(val));
        break;
    case SND_PCM_HW_PARAM_FORMAT:
        fprintf(stderr, "%s", snd_pcm_format_name(val));
        break;
    default:
        fprintf(stderr, "%u", val);
    }
    fprintf(stderr, " (err: %d)\n", err);
    snd_pcm_hw_params_dump(params);
}
#else
static inline void dump_hw_params(snd_pcm_hw_params_t *params, const char *type,
                  snd_pcm_hw_param_t var, unsigned int val, int err)
{
}
#endif

static void snd_range_print(const snd_interval_t *i)
{
    if (snd_range_empty(i))
        printf("NONE");
    else if (i->range.min == 0 && i->range.openmin == 0 &&
            i->range.max == UINT_MAX && i->range.openmax == 0)
        printf("ALL");
    else if (snd_range_single(i) && i->range.integer)
        printf("%u", snd_range_value(i));
    else
        printf("%c%lu %lu%c",
                i->range.openmin ? '(' : '[',
                (long unsigned int)i->range.min, (long unsigned int)i->range.max,
                i->range.openmax? ')' : ']');
}

void snd_pcm_hw_param_dump(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var)
{
    if (hw_is_mask(var)) {
        const snd_interval_t *interval = hw_param_interval_c(params, var);
        if (snd_mask_empty(interval))
            printf(" NONE");
        else if (snd_mask_full(interval))
            printf(" ALL");
        else {
            unsigned int k;
            for (k = 0; k <= SND_MASK_BITS; ++k) {
                if (snd_mask_test(interval, k)) {
                    const char *s;
                    switch (var) {
                    case SND_PCM_HW_PARAM_ACCESS:
                        s = snd_pcm_access_name(k);
                        break;
                    case SND_PCM_HW_PARAM_FORMAT:
                        s = snd_pcm_format_name(k);
                        break;
                    default:
                        assert(0);
                        s = NULL;
                    }
                    if (s)
                        printf(" %s", s);
                }
            }
        }
        return;
    }
    if (hw_is_range(var)) {
        snd_range_print(hw_param_interval_c(params, var));
        return;
    }
    assert(0);
}

static void boundary_sub(int a, int adir, int b, int bdir, int *c, int *cdir)
{
    adir = adir < 0 ? -1 : (adir > 0 ? 1 : 0);
    bdir = bdir < 0 ? -1 : (bdir > 0 ? 1 : 0);
    *c = a - b;
    *cdir = adir - bdir;
    if (*cdir == -2) {
        assert(*c > INT_MIN);
        (*c)--;
    } else if (*cdir == 2) {
        assert(*c < INT_MAX);
        (*c)++;
    }
}

static int boundary_lt(unsigned int a, int adir, unsigned int b, int bdir)
{
    assert(a > 0 || adir >= 0);
    assert(b > 0 || bdir >= 0);
    if (adir < 0) {
        a--;
        adir = 1;
    } else if (adir > 0)
        adir = 1;
    if (bdir < 0) {
        b--;
        bdir = 1;
    } else if (bdir > 0)
        bdir = 1;
    return a < b || (a == b && adir < bdir);
}

/* Return 1 if min is nearer to best than max */
static int boundary_nearer(int min, int mindir, int best, int bestdir, int max, int maxdir)
{
    int dmin, dmindir;
    int dmax, dmaxdir;
    boundary_sub(best, bestdir, min, mindir, &dmin, &dmindir);
    boundary_sub(max, maxdir, best, bestdir, &dmax, &dmaxdir);
    return boundary_lt(dmin, dmindir, dmax, dmaxdir);
}

int snd_pcm_hw_param_empty(const snd_pcm_hw_params_t *params,
               snd_pcm_hw_param_t var)
{
    if (hw_is_mask(var))
        return snd_mask_empty(hw_param_interval_c(params, var));
    if (hw_is_range(var))
        return snd_range_empty(hw_param_interval_c(params, var));
    assert(0);
    return -EINVAL;
}

int snd_pcm_hw_param_always_eq(const snd_pcm_hw_params_t *params,
                   snd_pcm_hw_param_t var,
                   const snd_pcm_hw_params_t *params1)
{
    if (hw_is_mask(var))
        return snd_mask_always_eq(hw_param_interval_c(params, var),
                      hw_param_interval_c(params1, var));
    if (hw_is_range(var))
        return snd_range_always_eq(hw_param_interval_c(params, var),
                       hw_param_interval_c(params1, var));
    assert(0);
    return -EINVAL;
}

int snd_pcm_hw_param_never_eq(const snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var,
                  const snd_pcm_hw_params_t *params1)
{
    if (hw_is_mask(var))
        return snd_mask_never_eq(hw_param_interval_c(params, var),
                     hw_param_interval_c(params1, var));
    if (hw_is_range(var))
        return snd_range_never_eq(hw_param_interval_c(params, var),
                      hw_param_interval_c(params1, var));
    assert(0);
    return -EINVAL;
}

void _snd_pcm_hw_param_any(snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var)
{
    if (hw_is_mask(var)) {
        snd_mask_any(hw_param_interval(params, var));
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
        return;
    }
    if (hw_is_range(var)) {
        snd_range_any(hw_param_interval(params, var));
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
        return;
    }
    assert(0);
}

void _snd_pcm_hw_params_any(snd_pcm_hw_params_t *params)
{
    unsigned int k;
    memset(params, 0, sizeof(*params));
    for (k = SND_PCM_HW_PARAM_FIRST_INTERVAL; k <= SND_PCM_HW_PARAM_LAST_INTERVAL; k++)
        _snd_pcm_hw_param_any(params, k);
    params->rmask = ~0U;
    params->cmask = 0;
}

int snd_pcm_hw_param_get(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var,
             unsigned int *val, int *dir)
{
    const snd_interval_t *i = hw_param_interval_c(params, var);
    if (hw_is_mask(var)) {
        if (snd_mask_empty(i) || !snd_mask_single(i))
            return -EINVAL;
        if (dir)
            *dir = 0;
        if (val)
            *val = snd_mask_value(i);
        return 0;
    } else if (hw_is_range(var)) {
        if (snd_range_empty(i) || !snd_range_single(i))
            return -EINVAL;
        if (dir)
            *dir = i->range.openmin;
        if (val)
            *val = snd_range_value(i);
        return 0;
    }
    assert(0);
    return -EINVAL;
}

int snd_pcm_hw_param_get_min(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var,
                 unsigned int *val, int *dir)
{
    const snd_interval_t *i = hw_param_interval_c(params, var);
    if (hw_is_mask(var)) {
        assert(!snd_mask_empty(i));
        if (dir)
            *dir = 0;
        if (val)
            *val = snd_mask_min(i);
        return 0;
    } else if (hw_is_range(var)) {
        assert(!snd_range_empty(i));
        if (dir)
            *dir = i->range.openmin;
        if (val)
            *val = snd_range_min(i);
        return 0;
    }
    assert(0);
    return 0;
}

int snd_pcm_hw_param_get_max(const snd_pcm_hw_params_t *params, snd_pcm_hw_param_t var,
                 unsigned int *val, int *dir)
{
    const snd_interval_t *i = hw_param_interval_c(params, var);
    if (hw_is_mask(var)) {
        assert(!snd_mask_empty(i));
        if (dir)
            *dir = 0;
        if (val)
            *val = snd_mask_max(i);
        return 0;
    } else if (hw_is_range(var)) {
        assert(!snd_range_empty(i));
        if (dir)
            *dir = - (int) i->range.openmax;
        if (val)
            *val = snd_range_max(i);
        return 0;
    }
    assert(0);
    return 0;
}

int _snd_pcm_hw_param_set_mask(snd_pcm_hw_params_t *params,
        snd_pcm_hw_param_t var, const snd_interval_t *val)
{
    int changed;
    assert(hw_is_mask(var));
    changed = snd_mask_refine(hw_param_interval(params, var), val);
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_mask(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                  snd_set_mode_t mode,
                  snd_pcm_hw_param_t var, const snd_interval_t *val)
{
    snd_pcm_hw_params_t save;
    int err;
    switch (mode) {
    case SND_CHANGE:
        break;
    case SND_TRY:
        save = *params;
        break;
    case SND_TEST:
        save = *params;
        params = &save;
        break;
    default:
        assert(0);
        return -EINVAL;
    }
    err = _snd_pcm_hw_param_set_mask(params, var, val);
    if (err < 0)
        goto _fail;
    if (mode != SND_TEST && params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            goto _fail;
    }
    return 0;
 _fail:
    if (mode == SND_TRY)
        *params = save;
    return err;
}

int _snd_pcm_hw_param_set_range(snd_pcm_hw_params_t *params,
        snd_pcm_hw_param_t var, const snd_interval_t *val)
{
    int changed;
    assert(hw_is_range(var));
    changed = snd_range_refine(hw_param_interval(params, var), val);
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

static int _snd_pcm_hw_param_set_first(snd_pcm_hw_params_t *params,
                       snd_pcm_hw_param_t var)
{
    int changed;
    if (hw_is_mask(var))
        changed = snd_mask_refine_first(hw_param_interval(params, var));
    else if (hw_is_range(var))
        changed = snd_range_refine_first(hw_param_interval(params, var));
    else {
        assert(0);
        return -EINVAL;
    }
    if (changed > 0) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_first(snd_pcm_t *pcm,
                   snd_pcm_hw_params_t *params,
                   snd_pcm_hw_param_t var,
                   unsigned int *rval, int *dir)
{
    int err;

    err = _snd_pcm_hw_param_set_first(params, var);
    if (err < 0)
        return err;
    if (params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            return err;
    }
    return snd_pcm_hw_param_get(params, var, rval, dir);
}

static int _snd_pcm_hw_param_set_last(snd_pcm_hw_params_t *params,
                      snd_pcm_hw_param_t var)
{
    int changed;
    if (hw_is_mask(var))
        changed = snd_mask_refine_last(hw_param_interval(params, var));
    else if (hw_is_range(var))
        changed = snd_range_refine_last(hw_param_interval(params, var));
    else {
        assert(0);
        return -EINVAL;
    }
    if (changed > 0) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_last(snd_pcm_t *pcm,
                  snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var,
                  unsigned int *rval, int *dir)
{
    int err;

    err = _snd_pcm_hw_param_set_last(params, var);
    if (err < 0)
        return err;
    if (params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            return err;
    }
    return snd_pcm_hw_param_get(params, var, rval, dir);
}

int _snd_pcm_hw_param_set_min(snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var, unsigned int val, int dir)
{
    int changed;
    int openmin = 0;
    if (dir) {
        if (dir > 0) {
            openmin = 1;
        } else if (dir < 0) {
            if (val > 0) {
                openmin = 1;
                val--;
            }
        }
    }
    if (hw_is_mask(var))
        changed = snd_mask_refine_min(hw_param_interval(params, var), val + !!openmin);
    else if (hw_is_range(var))
        changed = snd_range_refine_min(hw_param_interval(params, var), val, openmin);
    else {
        assert(0);
        return -EINVAL;
    }
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_min(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                 snd_set_mode_t mode,
                 snd_pcm_hw_param_t var, unsigned int *val, int *dir)
{
    snd_pcm_hw_params_t save;
    int err;
    switch (mode) {
    case SND_CHANGE:
        break;
    case SND_TRY:
        save = *params;
        break;
    case SND_TEST:
        save = *params;
        params = &save;
        break;
    default:
        assert(0);
        return -EINVAL;
    }
    err = _snd_pcm_hw_param_set_min(params, var, *val, dir ? *dir : 0);
    if (err < 0)
        goto _fail;
    if ((mode != SND_TEST || hw_is_range(var)) && params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            goto _fail;
        if (snd_pcm_hw_param_empty(params, var)) {
            err = -ENOENT;
            goto _fail;
        }
    }
    return snd_pcm_hw_param_get_min(params, var, val, dir);
 _fail:
    if (mode == SND_TRY)
        *params = save;
    if (err < 0 && mode == SND_TRY)
        dump_hw_params(params, "set_min", var, *val, err);
    return err;
}

int _snd_pcm_hw_param_set_max(snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var, unsigned int val, int dir)
{
    int changed;
    int openmax = 0;
    if (dir) {
        if (dir < 0) {
            openmax = 1;
        } else if (dir > 0) {
            openmax = 1;
            val++;
        }
    }
    if (hw_is_mask(var)) {
        if (val == 0 && openmax) {
        snd_mask_none(hw_param_interval(params, var));
            changed = -EINVAL;
        } else
            changed = snd_mask_refine_max(hw_param_interval(params, var),
                              val - !!openmax);
    } else if (hw_is_range(var))
        changed = snd_range_refine_max(hw_param_interval(params, var), val, openmax);
    else {
        assert(0);
        return -EINVAL;
    }
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_max(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                 snd_set_mode_t mode,
                 snd_pcm_hw_param_t var, unsigned int *val, int *dir)
{
    snd_pcm_hw_params_t save;
    int err;
    switch (mode) {
    case SND_CHANGE:
        break;
    case SND_TRY:
        save = *params;
        break;
    case SND_TEST:
        save = *params;
        params = &save;
        break;
    default:
        assert(0);
        return -EINVAL;
    }
    err = _snd_pcm_hw_param_set_max(params, var, *val, dir ? *dir : 0);
    if (err < 0)
        goto _fail;
    if ((mode != SND_TEST || hw_is_range(var)) && params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            goto _fail;
        if (snd_pcm_hw_param_empty(params, var)) {
            err = -ENOENT;
            goto _fail;
        }
    }
    return snd_pcm_hw_param_get_max(params, var, val, dir);
 _fail:
    if (mode == SND_TRY)
        *params = save;
    if (err < 0 && mode == SND_TRY)
        dump_hw_params(params, "set_max", var, *val, err);
    return err;
}

int _snd_pcm_hw_param_set_minmax(snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 unsigned int min, int mindir,
                 unsigned int max, int maxdir)
{
    int changed, c1, c2;
    int openmin = 0, openmax = 0;
    if (mindir) {
        if (mindir > 0) {
            openmin = 1;
        } else if (mindir < 0) {
            if (min > 0) {
                openmin = 1;
                min--;
            }
        }
    }
    if (maxdir) {
        if (maxdir < 0) {
            openmax = 1;
        } else if (maxdir > 0) {
            openmax = 1;
            max++;
        }
    }
    snd_interval_t *i = hw_param_interval(params, var);
    if (hw_is_mask(var)) {
        if (max == 0 && openmax) {
            snd_mask_none(i);
            changed = -EINVAL;
        } else {
            c1 = snd_mask_refine_min(i, min + !!openmin);
            if (c1 < 0)
                changed = c1;
            else {
                c2 = snd_mask_refine_max(i, max - !!openmax);
                if (c2 < 0)
                    changed = c2;
                else
                    changed = (c1 || c2);
            }
        }
    } else if (hw_is_range(var)) {
        c1 = snd_range_refine_min(i, min, openmin);
        if (c1 < 0)
            changed = c1;
        else {
            c2 = snd_range_refine_max(i, max, openmax);
            if (c2 < 0)
                changed = c2;
            else
                changed = (c1 || c2);
        }
    } else {
        assert(0);
        return -EINVAL;
    }
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set_minmax(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                snd_set_mode_t mode,
                snd_pcm_hw_param_t var,
                unsigned int *min, int *mindir,
                unsigned int *max, int *maxdir)
{
    snd_pcm_hw_params_t save;
    int err;
    switch (mode) {
    case SND_CHANGE:
        break;
    case SND_TRY:
        save = *params;
        break;
    case SND_TEST:
        save = *params;
        params = &save;
        break;
    default:
        assert(0);
        return -EINVAL;
    }
    err = _snd_pcm_hw_param_set_minmax(params, var,
                       *min, mindir ? *mindir : 0,
                       *max, maxdir ? *maxdir : 0);
    if (err < 0)
        goto _fail;
    if ((mode != SND_TEST || hw_is_range(var)) && params->rmask) {
        err = snd_pcm_hw_refine(pcm, params);
        if (err < 0)
            goto _fail;
    }
    err = snd_pcm_hw_param_get_min(params, var, min, mindir);
    if (err < 0)
        return err;
    return snd_pcm_hw_param_get_max(params, var, max, maxdir);
 _fail:
    if (mode == SND_TRY)
        *params = save;
    if (err < 0)
        dump_hw_params(params, "set_minmax", var, *min, err);
    return err;
}

int _snd_pcm_hw_param_refine(snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 const snd_pcm_hw_params_t *src)
{
    int changed = 0;
    snd_interval_t *d = hw_param_interval(params, var);
    const snd_interval_t *s = hw_param_interval_c(src, var);
    if (hw_is_mask(var))
        changed = snd_mask_refine(d, s);
    else if (hw_is_range(var))
        changed = snd_range_refine(d, s);
    else
        return 0; /* NOP / reserved */
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int _snd_pcm_hw_params_refine(snd_pcm_hw_params_t *params,
                  unsigned int vars,
                  const snd_pcm_hw_params_t *src)
{
    int changed, err = 0;
    unsigned int k;
    for (k = 0; k <= SND_PCM_HW_PARAM_LAST_INTERVAL; ++k) {
        if (!(vars & (1 << k)))
            continue;
        changed = _snd_pcm_hw_param_refine(params, k, src);
        if (changed < 0)
            err = changed;
    }
#if 0
    params->info &= src->info;
    params->flags = src->flags; /* propagate all flags to slave */
#endif
    return err;
}

int snd_pcm_hw_refine(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    int res;

    assert(pcm && params);
    assert(pcm->ops->hw_refine);
    awalsa_debug("\n");

#ifdef REFINE_DEBUG
    awalsa_info("refine '%s' (begin)\n", pcm->name);
    snd_pcm_hw_params_dump(params);
#endif
    res = pcm->ops->hw_refine(pcm->op_arg, params);
#ifdef REFINE_DEBUG
    awalsa_info("refine '%s' (end: %d)\n", pcm->name, res);
    snd_pcm_hw_params_dump(params);
#endif
    return res;
}

int _snd_pcm_hw_param_set(snd_pcm_hw_params_t *params,
              snd_pcm_hw_param_t var, unsigned int val, int dir)
{
    int changed;
    snd_interval_t *interval = hw_param_interval(params, var);

    awalsa_debug("\n");
    if (hw_is_mask(var)) {
        if (val == 0 && dir < 0) {
            changed = -EINVAL;
            snd_mask_none(interval);
        } else {
            if (dir > 0)
                val++;
            else if (dir < 0)
                val--;
            changed = snd_mask_refine_set(interval, val);
        }
    } else if (hw_is_range(var)) {
        if (val == 0 && dir < 0) {
            changed = -EINVAL;
            snd_range_none(interval);
        } else if (dir == 0) {
            changed = snd_range_refine_set(interval, val);
        } else {
            snd_interval_t t;
            t.range.openmin = 1;
            t.range.openmax = 1;
            t.range.empty = 0;
            t.range.integer = 0;
            if (dir < 0) {
                t.range.min = val - 1;
                t.range.max = val;
            } else {
                t.range.min = val;
                t.range.max = val + 1;
            }
            changed = snd_range_refine(interval, &t);
        }
    } else {
        assert(0);
        return -EINVAL;
    }
    if (changed) {
        params->cmask |= 1 << var;
        params->rmask |= 1 << var;
    }
    return changed;
}

int snd_pcm_hw_param_set(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
             snd_set_mode_t mode,
             snd_pcm_hw_param_t var, unsigned int val, int dir)
{
    snd_pcm_hw_params_t save;
    int ret;
    switch (mode) {
    case SND_CHANGE:
        break;
    case SND_TRY:
        save = *params;
        break;
    case SND_TEST:
        save = *params;
        params = &save;
        break;
    default:
        assert(0);
        return -EINVAL;
    }
    awalsa_debug("\n");
    ret = _snd_pcm_hw_param_set(params, var, val, dir);
    if (ret < 0)
        goto _fail;
    if ((mode != SND_TEST || hw_is_range(var)) && params->rmask) {
        ret = snd_pcm_hw_refine(pcm, params);
        if (ret < 0)
            goto _fail;
    }
    return 0;
 _fail:
    if (mode == SND_TRY)
        *params = save;
    if (ret < 0 && mode == SND_TRY)
        dump_hw_params(params, "set", var, val, ret);
    return ret;
}

int snd_pcm_hw_param_set_near(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                  snd_pcm_hw_param_t var,
                  unsigned int *val, int *dir)
{
    snd_pcm_hw_params_t save;
    int err;
    unsigned int best = *val, saved_min;
    int last = 0;
    unsigned int min, max;
    int mindir, maxdir;
    int valdir = dir ? *dir : 0;
    snd_interval_t *i;

    awalsa_debug("\n");

    /* FIXME */
    if (best > INT_MAX)
        best = INT_MAX;
    min = max = best;
    mindir = maxdir = valdir;
    if (maxdir > 0)
        maxdir = 0;
    else if (maxdir == 0)
        maxdir = -1;
    else {
        maxdir = 1;
        max--;
    }
    save = *params;
    saved_min = min;
    err = snd_pcm_hw_param_set_min(pcm, params, SND_CHANGE, var, &min, &mindir);

    i = hw_param_interval(params, var);
    if (!snd_range_empty(i) && snd_range_single(i)) {
        err = snd_pcm_hw_param_get_min(params, var, val, dir);
        if (err < 0)
            dump_hw_params(params, "set_near", var, *val, err);
        return err;
    }

    if (err >= 0) {
        snd_pcm_hw_params_t params1;
        if (min == saved_min && mindir == valdir)
            goto _end;
        params1 = save;
        err = snd_pcm_hw_param_set_max(pcm, &params1, SND_CHANGE, var, &max, &maxdir);
        if (err < 0)
            goto _end;
        if (boundary_nearer(max, maxdir, best, valdir, min, mindir)) {
            *params = params1;
            last = 1;
        }
    } else {
        *params = save;
        err = snd_pcm_hw_param_set_max(pcm, params, SND_CHANGE, var, &max, &maxdir);
        if (err < 0) {
            dump_hw_params(params, "set_near", var, *val, err);
            return err;
        }
        last = 1;
    }
 _end:
    if (last)
        err = snd_pcm_hw_param_set_last(pcm, params, var, val, dir);
    else
        err = snd_pcm_hw_param_set_first(pcm, params, var, val, dir);
    if (err < 0)
        dump_hw_params(params, "set_near", var, *val, err);
    return err;
}

static int snd_pcm_hw_param_set_near_minmax(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params,
                        snd_pcm_hw_param_t var,
                        unsigned int min, int *mindir,
                        unsigned int max, int *maxdir)
{
    snd_pcm_hw_params_t tmp;
    int err;
    if (!boundary_lt(min, *mindir, max, *maxdir))
        return snd_pcm_hw_param_set_near(pcm, params, var, &min, mindir);
    tmp = *params;
    err = snd_pcm_hw_param_set_near(pcm, &tmp, var, &min, mindir);
    if (err < 0)
        return err;
    if (boundary_lt(min, *mindir, max, *maxdir)) {
        tmp = *params;
        err = snd_pcm_hw_param_set_near(pcm, &tmp, var, &max, maxdir);
    } else {
        max = min;
        *maxdir = *mindir;
    }
    err = snd_pcm_hw_param_set_minmax(pcm, params, SND_CHANGE, var, &min, mindir,
                      &max, maxdir);
    if (err < 0)
        return err;
    return 0;
}

int snd_pcm_hw_param_refine_near(snd_pcm_t *pcm,
                 snd_pcm_hw_params_t *params,
                 snd_pcm_hw_param_t var,
                 const snd_pcm_hw_params_t *src)
{
    unsigned int min, max;
    int mindir, maxdir, err;

    if ((err = snd_pcm_hw_param_get_min(src, var, &min, &mindir)) < 0)
        return err;
    if ((err = snd_pcm_hw_param_get_max(src, var, &max, &maxdir)) < 0)
        return err;
    if ((err = snd_pcm_hw_param_set_near_minmax(pcm, params, var,
                            min, &mindir, max, &maxdir)) < 0)
        return err;
    return 0;
}

int snd_pcm_hw_param_refine_multiple(snd_pcm_t *pcm,
                     snd_pcm_hw_params_t *params,
                     snd_pcm_hw_param_t var,
                     const snd_pcm_hw_params_t *src)
{
    const snd_interval_t *it = hw_param_interval_c(src, var);
    const snd_interval_t *st = hw_param_interval_c(params, var);
    if (snd_range_single(it)) {
        unsigned int best = snd_range_min(it), cur, prev;
        cur = best;
        for (;;) {
            if (st->range.max < cur || (st->range.max == cur && st->range.openmax))
                break;
            if (it->range.min <= cur && ! (it->range.min == cur && st->range.openmin)) {
                if (! snd_pcm_hw_param_set(pcm, params, SND_TRY, var, cur, 0))
                    return 0; /* ok */
            }
            prev = cur;
            cur += best;
            if (cur <= prev)
                break;
        }
    }
    return snd_pcm_hw_param_refine_near(pcm, params, var, src);
}

typedef struct snd_pcm_hw_rule snd_pcm_hw_rule_t;

static const snd_pcm_hw_rule_t refine_rules[] = {
    {
        .var = SND_PCM_HW_PARAM_FORMAT,
        .func = snd_pcm_hw_rule_format,
        .deps = { SND_PCM_HW_PARAM_SAMPLE_BITS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_SAMPLE_BITS,
        .func = snd_pcm_hw_rule_sample_bits,
        .deps = { SND_PCM_HW_PARAM_FORMAT,
            SND_PCM_HW_PARAM_SAMPLE_BITS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_SAMPLE_BITS,
        .func = snd_pcm_hw_rule_div,
        .deps = { SND_PCM_HW_PARAM_FRAME_BITS,
            SND_PCM_HW_PARAM_CHANNELS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_FRAME_BITS,
        .func = snd_pcm_hw_rule_mul,
        .deps = { SND_PCM_HW_PARAM_SAMPLE_BITS,
            SND_PCM_HW_PARAM_CHANNELS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_FRAME_BITS,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_PERIOD_BYTES,
            SND_PCM_HW_PARAM_PERIOD_SIZE, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_FRAME_BITS,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_BUFFER_BYTES,
            SND_PCM_HW_PARAM_BUFFER_SIZE, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_CHANNELS,
        .func = snd_pcm_hw_rule_div,
        .deps = { SND_PCM_HW_PARAM_FRAME_BITS,
            SND_PCM_HW_PARAM_SAMPLE_BITS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_RATE,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_PERIOD_SIZE,
            SND_PCM_HW_PARAM_PERIOD_TIME, -1 },
        .private_data = (void*) 1000000,
    },
    {
        .var = SND_PCM_HW_PARAM_RATE,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_BUFFER_SIZE,
            SND_PCM_HW_PARAM_BUFFER_TIME, -1 },
        .private_data = (void*) 1000000,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIODS,
        .func = snd_pcm_hw_rule_div,
        .deps = { SND_PCM_HW_PARAM_BUFFER_SIZE,
            SND_PCM_HW_PARAM_PERIOD_SIZE, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIOD_SIZE,
        .func = snd_pcm_hw_rule_div,
        .deps = { SND_PCM_HW_PARAM_BUFFER_SIZE,
            SND_PCM_HW_PARAM_PERIODS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIOD_SIZE,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_PERIOD_BYTES,
            SND_PCM_HW_PARAM_FRAME_BITS, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIOD_SIZE,
        .func = snd_pcm_hw_rule_muldivk,
        .deps = { SND_PCM_HW_PARAM_PERIOD_TIME,
            SND_PCM_HW_PARAM_RATE, -1 },
        .private_data = (void*) 1000000,
    },
    {
        .var = SND_PCM_HW_PARAM_BUFFER_SIZE,
        .func = snd_pcm_hw_rule_mul,
        .deps = { SND_PCM_HW_PARAM_PERIOD_SIZE,
            SND_PCM_HW_PARAM_PERIODS, -1 },
        .private_data = 0,
    },
    {
        .var = SND_PCM_HW_PARAM_BUFFER_SIZE,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_BUFFER_BYTES,
            SND_PCM_HW_PARAM_FRAME_BITS, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_BUFFER_SIZE,
        .func = snd_pcm_hw_rule_muldivk,
        .deps = { SND_PCM_HW_PARAM_BUFFER_TIME,
            SND_PCM_HW_PARAM_RATE, -1 },
        .private_data = (void*) 1000000,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIOD_BYTES,
        .func = snd_pcm_hw_rule_muldivk,
        .deps = { SND_PCM_HW_PARAM_PERIOD_SIZE,
            SND_PCM_HW_PARAM_FRAME_BITS, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_BUFFER_BYTES,
        .func = snd_pcm_hw_rule_muldivk,
        .deps = { SND_PCM_HW_PARAM_BUFFER_SIZE,
            SND_PCM_HW_PARAM_FRAME_BITS, -1 },
        .private_data = (void*) 8,
    },
    {
        .var = SND_PCM_HW_PARAM_PERIOD_TIME,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_PERIOD_SIZE,
            SND_PCM_HW_PARAM_RATE, -1 },
        .private_data = (void*) 1000000,
    },
    {
        .var = SND_PCM_HW_PARAM_BUFFER_TIME,
        .func = snd_pcm_hw_rule_mulkdiv,
        .deps = { SND_PCM_HW_PARAM_BUFFER_SIZE,
            SND_PCM_HW_PARAM_RATE, -1 },
        .private_data = (void*) 1000000,
    },
};

#define RULES (sizeof(refine_rules) / sizeof(refine_rules[0]))

static const snd_interval_t refine_intervals[
        SND_PCM_HW_PARAM_LAST_INTERVAL - SND_PCM_HW_PARAM_FIRST_INTERVAL + 1] = {
    [SND_PCM_HW_PARAM_ACCESS - SND_PCM_HW_PARAM_FIRST_INTERVAL] = {
        .mask = 0x1f,
    },
    [SND_PCM_HW_PARAM_FORMAT - SND_PCM_HW_PARAM_FIRST_INTERVAL] = {
        .mask = 0xffff,
    },
    [SND_PCM_HW_PARAM_SAMPLE_BITS - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 1, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_FRAME_BITS - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 1, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_CHANNELS - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 1, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_RATE - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_PERIOD_TIME - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 0, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_PERIOD_SIZE - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 0, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_PERIOD_BYTES - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 0, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_PERIODS - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 0, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_BUFFER_TIME - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 0, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_BUFFER_SIZE - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 1, .empty = 0,
    }},
    [SND_PCM_HW_PARAM_BUFFER_BYTES - SND_PCM_HW_PARAM_FIRST_INTERVAL] = { .range = {
        .min = 1, .max = UINT_MAX,
        .openmin = 0, .openmax = 0, .integer = 1, .empty = 0,
    }},
};

#if 0
#define RULES_DEBUG
#endif

int snd_pcm_hw_refine_soft(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    unsigned int k;
    unsigned int rstamps[RULES];
    unsigned int vstamps[SND_PCM_HW_PARAM_LAST_INTERVAL + 1];
    unsigned int stamp = 2;
    int changed, again;
#ifdef RULES_DEBUG
    awalsa_info("refine_soft '%s' (begin)\n", pcm->name);
    snd_pcm_hw_params_dump(params);
#endif

    for (k = SND_PCM_HW_PARAM_FIRST_MASK; k <= SND_PCM_HW_PARAM_LAST_MASK; k++) {
        if (!(params->rmask & (1 << k)))
            continue;
        changed = snd_mask_refine(hw_param_interval(params, k),
                      &refine_intervals[k - SND_PCM_HW_PARAM_FIRST_INTERVAL]);
        if (changed)
            params->cmask |= 1 << k;
        if (changed < 0)
            goto _err;
    }

    for (k = SND_PCM_HW_PARAM_FIRST_RANGE; k <= SND_PCM_HW_PARAM_LAST_RANGE; k++) {
        if (!(params->rmask & (1 << k)))
            continue;
        changed = snd_range_refine(hw_param_interval(params, k),
                      &refine_intervals[k - SND_PCM_HW_PARAM_FIRST_INTERVAL]);
        if (changed)
            params->cmask |= 1 << k;
        if (changed < 0)
            goto _err;
    }

    for (k = 0; k < RULES; k++)
        rstamps[k] = 0;
    for (k = 0; k <= SND_PCM_HW_PARAM_LAST_INTERVAL; k++)
        vstamps[k] = (params->rmask & (1 << k)) ? 1 : 0;
    do {
        again = 0;
        for (k = 0; k < RULES; k++) {
            const snd_pcm_hw_rule_t *r = &refine_rules[k];
            unsigned int d;
            int doit = 0;
            for (d = 0; r->deps[d] >= 0; d++) {
                if (vstamps[r->deps[d]] > rstamps[k]) {
                    doit = 1;
                    break;
                }
            }
            if (!doit)
                continue;
#ifdef RULES_DEBUG
            printf("Rule %d (%p): ", k, r->func);
            if (r->var >= 0) {
                printf("%s=", snd_pcm_hw_param_name(r->var));
                snd_pcm_hw_param_dump(params, r->var);
                printf(" -> ");
            }
#endif
            changed = r->func(params, (struct snd_pcm_hw_rule *)r);
#ifdef RULES_DEBUG
            if (r->var >= 0)
                snd_pcm_hw_param_dump(params, r->var);
            for (d = 0; r->deps[d] >= 0; d++) {
                printf(" %s=", snd_pcm_hw_param_name(r->deps[d]));
                snd_pcm_hw_param_dump(params, r->deps[d]);
            }
            printf("\n");
#endif
            rstamps[k] = stamp;
            if (changed && r->var >= 0) {
                params->cmask |= 1 << r->var;
                vstamps[r->var] = stamp;
                again = 1;
            }
            if (changed < 0)
                goto _err;
            stamp++;
        }
    } while (again);
#if 0
    if (!params->msbits) {
        i = hw_param_interval(params, SND_PCM_HW_PARAM_SAMPLE_BITS);
        if (snd_interval_single(i))
            params->msbits = snd_interval_value(i);
    }

    if (!params->rate_den) {
        i = hw_param_interval(params, SND_PCM_HW_PARAM_RATE);
        if (snd_interval_single(i)) {
            params->rate_num = snd_interval_value(i);
            params->rate_den = 1;
        }
    }
#endif
    params->rmask = 0;
    return 0;
 _err:
#ifdef RULES_DEBUG
    awalsa_info("refine_soft '%s' (end-%i)\n", pcm->name, changed);
    snd_pcm_hw_params_dump(params);
#endif
    return changed;
}

int snd_pcm_hw_refine_slave(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                int (*cprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*cchange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*schange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*srefine)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *sparams))

{
    snd_pcm_hw_params_t sparams;
    int err;
    unsigned int cmask, changed;

    awalsa_debug("\n");
    err = cprepare(pcm, params);
    if (err < 0)
        return err;
    err = sprepare(pcm, &sparams);
    if (err < 0) {
        awalsa_err("Slave PCM not usable\n");
        return err;
    }
#ifdef RULES_DEBUG
    awalsa_info("hw_refine_slave - enter '%s'\n", pcm->name);
#endif
    do {
        cmask = params->cmask;
        params->cmask = 0;
#ifdef RULES_DEBUG
        awalsa_info("schange '%s' (client)\n", pcm->name);
        snd_pcm_hw_params_dump(params);
        awalsa_info("schange '%s' (slave)\n", pcm->name);
        snd_pcm_hw_params_dump(&sparams);
#endif
        err = schange(pcm, params, &sparams);
        if (err >= 0) {
#ifdef RULES_DEBUG
            awalsa_info("srefine '%s' (client)\n", pcm->name);
            snd_pcm_hw_params_dump(params);
            awalsa_info("srefine '%s' (slave)\n", pcm->name);
            snd_pcm_hw_params_dump(&sparams);
#endif
            err = srefine(pcm, &sparams);
            if (err < 0) {
#ifdef RULES_DEBUG
                awalsa_info("srefine '%s', err < 0 (%i) (client)\n", pcm->name, err);
                snd_pcm_hw_params_dump(params);
                awalsa_info("srefine '%s', err < 0 (%i) (slave)\n", pcm->name, err);
                snd_pcm_hw_params_dump(&sparams);
#endif
                cchange(pcm, params, &sparams);
                return err;
            }
        } else {
#ifdef RULES_DEBUG
            awalsa_info("schange '%s', err < 0 (%i) (client)\n", pcm->name, err);
            snd_pcm_hw_params_dump(params);
            awalsa_info("schange '%s', err < 0 (%i) (slave)\n", pcm->name, err);
            snd_pcm_hw_params_dump(&sparams);
#endif
            cchange(pcm, params, &sparams);
            return err;
        }
#ifdef RULES_DEBUG
        awalsa_info("cchange '%s'\n", pcm->name);
#endif
        err = cchange(pcm, params, &sparams);
        if (err < 0)
            return err;
#ifdef RULES_DEBUG
        awalsa_info("refine_soft '%s'\n", pcm->name);
#endif
        err = snd_pcm_hw_refine_soft(pcm, params);
        changed = params->cmask;
        params->cmask |= cmask;
        if (err < 0)
            return err;
#ifdef RULES_DEBUG
        awalsa_info("refine_soft ok '%s'\n", pcm->name);
#endif
    } while (changed);
#ifdef RULES_DEBUG
    awalsa_info("refine_slave - leave '%s'\n", pcm->name);
#endif
    return 0;
}

int snd_pcm_hw_params_slave(snd_pcm_t *pcm, snd_pcm_hw_params_t *params,
                int (*cchange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sprepare)(snd_pcm_t *pcm,
                        snd_pcm_hw_params_t *params),
                int (*schange)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *params,
                       snd_pcm_hw_params_t *sparams),
                int (*sparams)(snd_pcm_t *pcm,
                       snd_pcm_hw_params_t *sparams))

{
    snd_pcm_hw_params_t slave_params;
    int err;
    err = sprepare(pcm, &slave_params);
    if (err < 0)
        return err;
    err = schange(pcm, params, &slave_params);
    if (err < 0)
        return err;
    err = sparams(pcm, &slave_params);
    if (err < 0)
        cchange(pcm, params, &slave_params);
    return err;
}

#if 0
#define CHOOSE_DEBUG
#endif

/* Choose one configuration from configuration space defined by PARAMS
   The configuration chosen is that obtained fixing in this order:
   first access
   first format
   first subformat
   min channels
   min rate
   min period time
   max buffer size
   min tick time
*/
static int snd_pcm_hw_params_choose(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    int err;
#ifdef CHOOSE_DEBUG
    awalsa_info("CHOOSE called:\n");
    snd_pcm_hw_params_dump(params);
#endif

    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_ACCESS, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_FORMAT, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_CHANNELS, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_RATE, NULL, 0);
    if (err < 0)
        return err;
#if 0
    if (pcm->minperiodtime > 0) {
        unsigned int min, max;
        int dir = 1;
        err = snd_pcm_hw_param_get_min(params, SND_PCM_HW_PARAM_PERIOD_TIME, &min, &dir);
        if (err >= 0)
            err = snd_pcm_hw_param_get_max(params, SND_PCM_HW_PARAM_PERIOD_TIME, &max, &dir);
        if (err >= 0 && (long)min < pcm->minperiodtime &&
                    (long)max > pcm->minperiodtime) {
            min = pcm->minperiodtime; dir = 1;
            snd_pcm_hw_param_set_min(pcm, params, SND_CHANGE, SND_PCM_HW_PARAM_PERIOD_TIME, &min, &dir);
        }
    }
#endif

#if 0
    /* old mode */
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_TIME, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_SIZE, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_last(pcm, params, SND_PCM_HW_PARAM_BUFFER_SIZE, NULL, 0);
    if (err < 0)
        return err;
#else
    /* determine buffer size first */
    err = snd_pcm_hw_param_set_last(pcm, params, SND_PCM_HW_PARAM_BUFFER_SIZE, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_SIZE, NULL, 0);
    if (err < 0)
        return err;
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_PERIOD_TIME, NULL, 0);
    if (err < 0)
        return err;
#endif

#if 0
    err = snd_pcm_hw_param_set_first(pcm, params, SND_PCM_HW_PARAM_TICK_TIME, NULL, 0);
    if (err < 0)
        return err;
#endif
#ifdef CHOOSE_DEBUG
    awalsa_info("choose done\n");
    snd_pcm_hw_params_dump(params);
#endif
    return 0;
}

static int snd_pcm_sw_params_default(snd_pcm_t *pcm, snd_pcm_sw_params_t *params)
{
    params->avail_min = pcm->period_size;
    params->start_threshold = 1;
    params->stop_threshold = pcm->buffer_size;
    params->silence_size = 0;
    params->boundary = pcm->buffer_size;
    if (!pcm->buffer_size) {
        awalsa_info("buffer size is 0...\n");
        return 0;
    }
    while (params->boundary * 2 <= LONG_MAX - pcm->buffer_size)
        params->boundary *= 2;
    return 0;
}

int _snd_pcm_hw_params_internal(snd_pcm_t *pcm, snd_pcm_hw_params_t *params)
{
    int ret;
    snd_pcm_sw_params_t sw;

    awalsa_debug("\n");
    assert(pcm->ops->hw_params);

    ret = snd_pcm_hw_refine(pcm, params);
    if (ret < 0)
        return ret;
    snd_pcm_hw_params_choose(pcm, params);
    if (pcm->setup) {
        ret = snd_pcm_hw_free(pcm);
        if (ret < 0)
            return ret;
    }

    ret = pcm->ops->hw_params(pcm->op_arg, params);
    if (ret < 0)
        return ret;

    pcm->setup = 1;

    snd_pcm_hw_params_get_access(params, &pcm->access);
    snd_pcm_hw_params_get_format(params, &pcm->format);
    snd_pcm_hw_params_get_channels(params, &pcm->channels);
    snd_pcm_hw_params_get_rate(params, &pcm->rate, NULL);
    snd_pcm_hw_params_get_period_time(params, &pcm->period_time, NULL);
    snd_pcm_hw_params_get_period_size(params, &pcm->period_size, NULL);
    snd_pcm_hw_params_get_buffer_size(params, &pcm->buffer_size);
    pcm->sample_bits = snd_pcm_format_physical_width(pcm->format);
    pcm->frame_bits = pcm->sample_bits * pcm->channels;

    awalsa_debug("pcm type=%s\n", snd_pcm_type_name(snd_pcm_type(pcm)));
    awalsa_debug("access:%u\n", pcm->access);
    awalsa_debug("format:%u\n", pcm->format);
    awalsa_debug("channels:%u\n", pcm->channels);
    awalsa_debug("rate:%u\n", pcm->rate);
    awalsa_debug("period_time:%u\n", pcm->period_time);
    awalsa_debug("period_size:%lu\n", pcm->period_size);
    awalsa_debug("buffer_size:%lu\n", pcm->buffer_size);
    awalsa_debug("sample_bits:%u\n", pcm->sample_bits);
    awalsa_debug("frame_bits:%u\n", pcm->frame_bits);

    snd_pcm_sw_params_default(pcm, &sw);
    ret = snd_pcm_sw_params(pcm, &sw);
    if (ret < 0)
        return ret;

    if (pcm->mmap_rw ||
            pcm->access == SND_PCM_ACCESS_MMAP_INTERLEAVED ||
            pcm->access == SND_PCM_ACCESS_MMAP_NONINTERLEAVED ||
            pcm->access == SND_PCM_ACCESS_MMAP_COMPLEX) {
        ret = snd_pcm_mmap(pcm);
    }
    if (ret < 0)
        return ret;
    return 0;
}
