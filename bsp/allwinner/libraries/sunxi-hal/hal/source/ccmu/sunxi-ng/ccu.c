/* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
 *
 * Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
 *the the People's Republic of China and other countries.
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
#include "ccu.h"
#include <stdlib.h>
#include <hal_clk.h>
#include <sunxi_hal_common.h>

static LIST_HEAD(clk_root_list);

const char *clk_hw_get_name(const struct clk_hw *hw)
{
    if (!hw || !hw->core)
    return NULL;

    return hw->core->name;
}

unsigned long clk_hw_get_flags(const struct clk_hw *hw)
{
    if (!hw || !hw->core)
    return 0;

    return hw->core->flags;
}

struct clk_core *clk_hw_get_core(const struct clk_hw *hw)
{
    if (!hw || !hw->core)
    return NULL;

    return hw->core;
}

struct clk_core *clk_core_get_by_name(const char *name)
{
    struct clk_core *core = NULL;

    list_for_each_entry(core, &clk_root_list, node)
    {
        if (strcmp(name, core->name))
        {
            continue;
        }
        return core;
    }

    return NULL;
}

static struct clk_core *clk_core_get_by_pindex(struct clk_core *core, u8 p_index)
{
    if (p_index > core->num_parents)
    {
        return NULL;
    }

    return clk_core_get_by_name(core->parents[p_index].name);
}

static void clk_core_fill_parent_index(struct clk_core *core, u8 index)
{
    struct clk_parent_map *entry = &core->parents[index];
    struct clk_core *parent = NULL;

    if (entry->hw)
    {
        parent = entry->hw->core;
        /*
         * We have a direct reference but it isn't registered yet?
         * Orphan it and let clk_reparent() update the orphan status
         * when the parent is registered.
         */
    }
    else
    {
        parent = clk_core_get_by_pindex(core, index);
    }

    /* Only cache it if it's not an error */
    if (parent)
    {
        entry->core = parent;
    }
}

static struct clk_core *clk_core_get_parent_by_index(struct clk_core *core,
        u8 index)
{
    if (!core || index >= core->num_parents || !core->parents)
    {
        return NULL;
    }

    if (!core->parents[index].core)
    {
        clk_core_fill_parent_index(core, index);
    }
    return core->parents[index].core;
}

struct clk_hw *
clk_hw_get_parent_by_index(const struct clk_hw *hw, unsigned int index)
{
    struct clk_core *parent;

    parent = clk_core_get_parent_by_index(hw->core, index);

    return !parent ? NULL : parent->hw;
}

unsigned int clk_hw_get_num_parents(const struct clk_hw *hw)
{
    return hw->core->num_parents;
}

struct clk_hw *clk_hw_get_parent(const struct clk_hw *hw)
{
    return hw->core->parent ? hw->core->parent->hw : NULL;
}

static u32 __clk_get_accuracy(struct clk_core *core)
{
    if (!core)
    {
        return 0;
    }
    return core->accuracy;
}

static unsigned long clk_core_get_rate_nolock(struct clk_core *core)
{
    if (!core)
    {
        return 0;
    }

    if (!core->num_parents || core->parent)
    {
        return core->rate;
    }

    /*
     * Clk must have a parent because num_parents > 0 but the parent isn't
     * known yet. Best to return 0 as the rate of this clk until we can
     * properly recalc the rate based on the parent's rate.
     */
    return 0;
}

static int clk_core_determine_round_nolock(struct clk_core *core,
        struct clk_rate_request *req)
{
    long rate;

    if (!core)
    {
        return 0;
    }

    /*
     * At this point, core protection will be disabled if
     * - if the provider is not protected at all
     * - if the calling consumer is the only one which has exclusivity
     *   over the provider
     */
    if (core->ops->determine_rate)
    {
        return core->ops->determine_rate(core->hw, req);
    }
    else if (core->ops->round_rate)
    {
        rate = core->ops->round_rate(core->hw, req->rate,
                                     &req->best_parent_rate);
        if (rate < 0)
        {
            return rate;
        }

        req->rate = rate;
    }
    else
    {
        return -1;
    }

    return 0;
}

static void clk_core_init_rate_req(struct clk_core *const core,
                                   struct clk_rate_request *req)
{
    struct clk_core *parent;

    if (!core || !req)
    {
        return;
    }

    parent = core->parent;
    if (parent)
    {
        req->best_parent_hw = parent->hw;
        req->best_parent_rate = parent->rate;
    }
    else
    {
        req->best_parent_hw = NULL;
        req->best_parent_rate = 0;
    }
}

static u8 clk_core_can_round(struct clk_core *const core)
{
    return core->ops->determine_rate || core->ops->round_rate;
}

static int clk_core_round_rate_nolock(struct clk_core *core,
                                      struct clk_rate_request *req)
{
    if (!core)
    {
        req->rate = 0;
        return 0;
    }

    clk_core_init_rate_req(core, req);

    if (clk_core_can_round(core))
    {
        return clk_core_determine_round_nolock(core, req);
    }
    else if (core->flags & CLK_SET_RATE_PARENT)
    {
        return clk_core_round_rate_nolock(core->parent, req);
    }

    req->rate = core->rate;
    return 0;
}

/**
 * __clk_determine_rate - get the closest rate actually supported by a clock
 * @hw: determine the rate of this clock
 * @req: target rate request
 *
 * Useful for clk_ops such as .set_rate and .determine_rate.
 */
int __clk_determine_rate(struct clk_hw *hw, struct clk_rate_request *req)
{
    if (!hw)
    {
        req->rate = 0;
        return 0;
    }

    return clk_core_round_rate_nolock(hw->core, req);
}

static u8 mux_is_better_rate(unsigned long rate, unsigned long now,
                             unsigned long best, unsigned long flags)
{
    if (flags & CLK_MUX_ROUND_CLOSEST)
    {
        return abs(now - rate) < abs(best - rate);
    }

    return now <= rate && now > best;
}

int clk_mux_determine_rate_flags(struct clk_hw *hw,
                                 struct clk_rate_request *req,
                                 unsigned long flags)
{
    struct clk_core *core = hw->core, *parent, *best_parent = NULL;
    int i, num_parents, ret;
    unsigned long best = 0;
    struct clk_rate_request parent_req = *req;

    /* if NO_REPARENT flag set, pass through to current parent */
    if (core->flags & CLK_SET_RATE_NO_REPARENT)
    {
        parent = core->parent;
        if (core->flags & CLK_SET_RATE_PARENT)
        {
            ret = __clk_determine_rate(parent ? parent->hw : NULL,
                                       &parent_req);
            if (ret)
            {
                return ret;
            }

            best = parent_req.rate;
        }
        else if (parent)
        {
            best = clk_core_get_rate_nolock(parent);
        }
        else
        {
            best = clk_core_get_rate_nolock(core);
        }

        goto out;
    }

    /* find the parent that can provide the fastest rate <= rate */
    num_parents = core->num_parents;
    for (i = 0; i < num_parents; i++)
    {
        parent = clk_core_get_parent_by_index(core, i);
        if (!parent)
        {
            continue;
        }

        if (core->flags & CLK_SET_RATE_PARENT)
        {
            parent_req = *req;
            ret = __clk_determine_rate(parent->hw, &parent_req);
            if (ret)
            {
                continue;
            }
        }
        else
        {
            parent_req.rate = clk_core_get_rate_nolock(parent);
        }

        if (mux_is_better_rate(req->rate, parent_req.rate,
                               best, flags))
        {
            best_parent = parent;
            best = parent_req.rate;
        }
    }

    if (!best_parent)
    {
        return -1;
    }

out:
    if (best_parent)
    {
        req->best_parent_hw = best_parent->hw;
    }
    req->best_parent_rate = best;
    req->rate = best;

    return 0;
}

/*
 * __clk_mux_determine_rate - clk_ops::determine_rate implementation for a mux type clk
 * @hw: mux type clk to determine rate on
 * @req: rate request, also used to return preferred parent and frequencies
 *
 * Helper for finding best parent to provide a given frequency. This can be used
 * directly as a determine_rate callback (e.g. for a mux), or from a more
 * complex clock that may combine a mux with other operations.
 *
 * Returns: 0 on success, -EERROR value on error
 */
int __clk_mux_determine_rate(struct clk_hw *hw,
                             struct clk_rate_request *req)
{
    return clk_mux_determine_rate_flags(hw, req, 0);
}

static void clk_core_get_boundaries(struct clk_core *core,
                                    unsigned long *min_rate,
                                    unsigned long *max_rate)
{
    *min_rate = core->min_rate;
    *max_rate = core->max_rate;
}

unsigned long clk_hw_round_rate(struct clk_hw *hw, unsigned long rate)
{
    int ret;
    struct clk_rate_request req;

    if (!hw)
    {
        return 0;
    }

    clk_core_get_boundaries(hw->core, &req.min_rate, &req.max_rate);
    req.rate = rate;

    ret = clk_core_round_rate_nolock(hw->core, &req);
    if (ret)
    {
        return 0;
    }

    return req.rate;
}

static struct clk_core *__clk_init_parent(struct clk_core *core)
{
    u8 index = 0;

    if (!core->num_parents)
    {
        return NULL;
    }

    if (core->num_parents > 1 && core->ops->get_parent)
    {
        index = core->ops->get_parent(core->hw);
    }

    return clk_core_get_parent_by_index(core, index);
}

static int __clk_core_init(struct clk_core *core)
{
    u32 rate;
    int ret = -1;

    if (!core)
    {
        return ret;
    }

    if (core->ops->init)
    {
        core->ops->init(core->hw);
    }

    core->parent = __clk_init_parent(core);

    if (core->ops->recalc_accuracy)
    {
        core->accuracy = core->ops->recalc_accuracy(core->hw,
                         __clk_get_accuracy(core->parent));
    }
    else if (core->parent)
    {
        core->accuracy = core->parent->accuracy;
    }
    else
    {
        core->accuracy = 0;
    }

    if (core->ops->recalc_rate)
    {
        rate = core->ops->recalc_rate(core->hw, clk_core_get_rate(core->parent));
    }
    else if (core->parent)
    {
        rate = core->parent->rate;
    }
    else
    {
        rate = 0;
    }

    if (core->parent)
    {
        core->p_rate = core->parent->rate;
    }
    else
    {
        core->p_rate = 0;
    }

    core->rate = rate;

    if (core->flags & CLK_IS_CRITICAL)
    {
        ret = clk_core_enable(core);
        if (ret)
        {
            return ret;
        }
    }

    return 0;
}

static int clk_core_populate_parent_map(struct clk_core *core,
                                        const struct clk_init_data *init)
{
    u8 num_parents = init->num_parents;
    const char *const *parent_names = init->parent_names;
    const struct clk_hw **parent_hws = init->parent_hws;
    const struct clk_parent_data *parent_data = init->parent_data;
    int i, ret = 0;
    struct clk_parent_map *parents, *parent;

    if (!num_parents)
    {
        return 0;
    }

    /*
     * Avoid unnecessary string look-ups of clk_core's possible parents by
     * having a cache of names/clk_hw pointers to clk_core pointers.
     */
    parents = (struct clk_parent_map *)malloc(num_parents * sizeof(*parents));
    core->parents = parents;
    if (!parents)
    {
        return -1;
    }

    /* Copy everything over because it might be __initdata */
    for (i = 0, parent = parents; i < num_parents; i++, parent++)
    {
        parent->index = -1;
        parent->core = NULL;
        parent->hw = NULL;
        parent->name = NULL;
        parent->fw_name = NULL;
        if (parent_names)
        {
            if (!parent_names[i])
            {
                hal_log_err("invalid NULL in %s's .parent_names\n", core->name);
            }
            else
            {
                parent->name = parent_names[i];
            }
        }
        else if (parent_data)
        {
            parent->hw = parent_data[i].hw;
            parent->index = parent_data[i].index;
            if (parent_data[i].name)
            {
                parent->name =  parent_data[i].name;
            }
            else
            {
                parent->name = parent_data[i].fw_name;
            }

        }
        else if (parent_hws)
        {
            parent->hw = parent_hws[i];
        }
        else
        {
            ret = -1;
            hal_log_err("Must specify parents if num_parents > 0\n");
        }

        if (ret)
        {
            core->parents = NULL;
            free(parents);
            return ret;
        }
    }

    return 0;
}

#if 0
static void clk_core_free_parent_map(struct clk_core *core)
{
    if (!core->num_parents)
    {
        return;
    }

    free(core->parents);
}
#endif

int clk_hw_register(struct clk_hw *hw)
{
    int ret = -1;
    struct clk_core *core;
    struct clk_init_data *init;

    if (!hw)
    {
        return 0;
    }

    init = hw->init;

    core = (struct clk_core *)malloc(sizeof(*core));
    if (!core)
    {
        hal_log_err("out of memory\n");
        return -1;
    }

    core->name = init->name;
    core->num_parents = init->num_parents;
    core->flags = init->flags;
    core->hw = hw;
    core->ops = hw->init->ops;
    core->min_rate = 0;
    core->max_rate = ULONG_MAX;
    core->enable_count = 0;

    core->clk = (struct clk *)malloc(sizeof(struct clk));
    if (!core->clk)
    {
        hal_log_err("out of memory\n");
    goto fail_clk;
    }
    core->clk->core = core;
    core->clk->name = core->name;
    core->clk->count = 0;

    ret = clk_core_populate_parent_map(core, init);
    if (ret)
    {
        goto fail_parents;
    }

    ret = __clk_core_init(core);

    if (ret)
    {
        free(core);
        return -1;
    }
    hw->core = core;

    list_add_tail(&core->node, &clk_root_list);

    return ret;

fail_parents:
    free(core->clk);
    core->clk = NULL;

fail_clk:
    free(core);
    core = NULL;

    return ret;
}

int clk_hw_unregister(struct clk_hw *hw)
{
    struct clk_core *core;

    if (!hw || !hw->core)
    {
        return 0;
    }

    list_for_each_entry(core, &clk_root_list, node)
    {
        if (core->hw->type != hw->type)
        {
            continue;
        }
        if (core->hw->id != hw->id)
        {
            continue;
        }
        list_del(&core->node);
        free(core->clk);
    free(core);
    return 0;
    }

    return 0;
}

struct clk_core *clk_core_get(hal_clk_type_t type, hal_clk_id_t id)
{
    struct clk_core *core = NULL;

    list_for_each_entry(core, &clk_root_list, node)
    {
        if (core->hw->type != type)
        {
            continue;
        }
        if (core->hw->id != id)
        {
            continue;
        }

        return core;
    }

    return NULL;
}

hal_clk_status_t clk_core_is_enabled(struct clk_core *core)
{
    /*
     * .is_enabled is only mandatory for clocks that gate
     * fall back to software usage counter if .is_enabled is missing
     */
    if (!core->ops->is_enabled)
    {
        return !!core->enable_count;
    }

    return core->ops->is_enabled(core->hw);
}

hal_clk_status_t clk_core_enable(struct clk_core *core)
{
    int ret = 0;

    if (!core)
    {
        return 0;
    }

    if (core->enable_count == 0)
    {
        ret = clk_core_enable(core->parent);

        if (ret)
        {
            return ret;
        }

        if (core->ops->enable)
        {
            ret = core->ops->enable(core->hw);
        }

        if (ret)
        {
            clk_core_disable(core->parent);
            return ret;
        }
    }

    core->enable_count++;
    return 0;
}

hal_clk_status_t clk_core_disable(struct clk_core *core)
{
    if (!core)
    {
        return 0;
    }

    if (core->enable_count == 0)
    {
        return 0;
    }

    if (--core->enable_count > 0)
    {
        return 0;
    }

    if (core->ops->disable)
    {
        core->ops->disable(core->hw);
    }

    clk_core_disable(core->parent);

    return 0;
}

u32 clk_core_round_rate(struct clk_core *core, u32 rate)
{
    struct clk_rate_request req;
    int ret;

    if (!core)
    {
        return 0;
    }

    clk_core_get_boundaries(core, &req.min_rate, &req.max_rate);
    req.rate = rate;

    ret = clk_core_round_rate_nolock(core, &req);

    if (ret)
    {
        return ret;
    }

    return req.rate;
}

u32 clk_core_recalc_rate(struct clk_core *core, struct clk_core *p_core)
{
    u32 p_rate = 0;

    if (!core)
    {
        return 0;
    }

    if (!p_core)
    {
        return core->rate;
    }

    clk_core_recalc_rate(p_core, p_core->parent);

    p_rate = p_core->rate;
    if (core->ops->recalc_rate)
    {
        return core->ops->recalc_rate(core->hw, p_rate);
    }

    return core->rate;
}

u32 clk_core_get_rate(struct clk_core *core)
{
    if (!core)
    {
        return 0;
    }

    core->parent = __clk_init_parent(core);

    return clk_core_recalc_rate(core, core->parent);
}

u32 clk_hw_get_rate(const struct clk_hw *hw)
{
    return clk_core_get_rate(hw->core);
}

hal_clk_status_t clk_core_set_rate(struct clk_core *core, struct clk_core *p_core, unsigned long rate)
{
    u8 ret = -1;

    if (!core || !p_core)
    {
        hal_log_err("core or p_core is NULL\n");
        return ret;
    }

    if (core->ops->set_rate)
    {
        ret = core->ops->set_rate(core->hw, rate, p_core->rate);
    }

    if (ret)
    {
        return ret;
    }

    core->rate = rate;
    return ret;
}

hal_clk_status_t clk_hw_set_rate(struct clk_hw *hw, unsigned long rate)
{
    struct clk_core *core, *p_core;
    core = clk_hw_get_core(hw);
    p_core = clk_core_get_parent(core);

    return clk_core_set_rate(core, p_core, rate);
}


static int __clk_set_parent(struct clk_core *core, struct clk_core *parent,
                            u8 p_index)
{
    int ret = 0;

    /* change clock input source */
    if (parent && core->ops->set_parent)
    {
        ret = core->ops->set_parent(core->hw, p_index);
    }

    return ret;
}

static int clk_fetch_parent_index(struct clk_core *core,
                                  struct clk_core *parent)
{
    int i;

    if (!parent)
    {
        return -1;
    }

    for (i = 0; i < core->num_parents; i++)
    {
        /* Found it first try! */
        if (core->parents[i].core)
        {
            if (core->parents[i].core == parent)
            {
                return i;
            }
        }

        /* Something else is here, so keep looking */
        if (core->parents[i].core)
        {
            continue;
        }

        /* Maybe core hasn't been cached but the hw is all we know? */
        if (core->parents[i].hw)
        {
            if (core->parents[i].hw == parent->hw)
            {
                break;
            }

            /* Didn't match, but we're expecting a clk_hw */
            continue;
        }

        /* Fallback to comparing globally unique names */
        if (core->parents[i].name &&
            !strcmp(parent->name, core->parents[i].name))
        {
            break;
        }
    }

    if (i == core->num_parents)
    {
        return -1;
    }

    core->parents[i].core = parent;
    return i;
}

struct clk_core *clk_core_get_parent(struct clk_core *core)
{
    if (!core)
    {
        return NULL;
    }

    if (!core->parent)
    core->parent = __clk_init_parent(core);

    return core->parent;
}

hal_clk_status_t clk_core_set_parent(struct clk_core *core, struct clk_core *parent)
{
    int ret = 0;
    int p_index = 0;
    uint32_t p_rate = 0;

    if (!core)
    {
        return 0;
    }

    if (core->parent == parent)
    {
        return 0;
    }

    /* verify ops for for multi-parent clks */
    if ((core->num_parents > 1) && (!core->ops->set_parent))
    {
        ret = -1;
        goto out;
    }

    /* try finding the new parent index */
    if (parent)
    {
        p_index = clk_fetch_parent_index(core, parent);
        if (p_index < 0)
        {
            printf("%s: clk %s can not be parent of clk %s\n",
                   __func__, parent->name, core->name);
            ret = p_index;
            goto out;
        }
        p_rate = parent->rate;
    }

    /* do the re-parent */
    ret = __clk_set_parent(core, parent, p_index);

    /* propagate rate an accuracy recalculation accordingly */
    if (!ret)
    {
        core->parent = parent;
        core->p_rate = p_rate;
        core->rate = clk_core_recalc_rate(core, parent);
    }

out:
    return ret;
}

