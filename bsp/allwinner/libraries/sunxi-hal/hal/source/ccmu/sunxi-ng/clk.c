
#include "ccu.h"
#include <stdlib.h>
#include <hal_clk.h>

extern int sunxi_fixed_clk_init(void);
extern int sunxi_ccu_init(void);
extern int sunxi_r_ccu_init(void);
extern int sunxi_rtc_ccu_init(void);

hal_clk_status_t clk_init(void)
{
    sunxi_fixed_clk_init();
    sunxi_rtc_ccu_init();
    sunxi_r_ccu_init();
    sunxi_ccu_init();
    return 0;
}

struct clk *clk_get(hal_clk_type_t type, hal_clk_id_t id)
{
    struct clk_core *core = NULL;
    struct clk *clk = NULL;

    core = clk_core_get(type, id);

    if (!core)
    {
        return NULL;
    }

    clk = core->clk;
    clk->count++;

    return clk;
}

hal_clk_status_t clk_put(struct clk *clk)
{
    if (!clk)
    {
        return 0;
    }

    if (clk->count)
        clk->count--;

    return 0;
}

hal_clk_status_t clk_is_enabled(struct clk *clk)
{
    int ret = 0;

    if (clk)
    {
        ret = clk_core_is_enabled(clk->core);
    }
    return ret ? 0 : -1;
}

hal_clk_status_t clk_prepare_enable(struct clk *clk)
{
    if (!clk)
    {
        return 0;
    }

    return clk_core_enable(clk->core);
}

hal_clk_status_t clk_disable_unprepare(struct clk *clk)
{
    if (clk)
    {
        return clk_core_disable(clk->core);
    }
    return 0;
}

struct clk *clk_get_parent(struct clk *clk)
{
    struct clk_core *parent;
    struct clk *p_clk;
    if (!clk)
    {
        return NULL;
    }

    parent = clk_core_get_parent(clk->core);

    if (!parent)
        return NULL;

    if (parent->clk)
    {
        p_clk = parent->clk;
        p_clk->count++;
    }
    else
    {
        p_clk = (struct clk *)malloc(sizeof(*clk));
        p_clk->core = parent;
        p_clk->name = parent->name;
        p_clk->count = 1;
        parent->clk = p_clk;
    }

    return p_clk;
}

hal_clk_status_t clk_set_parent(struct clk *clk, struct clk *p_clk)
{
    int ret;

    if (!clk || !p_clk)
    {
        return -1;
    }

    ret = clk_core_set_parent(clk->core, p_clk->core);

    if (ret)
    {
        return ret;
    }

    return ret;
}

hal_clk_status_t clk_get_rate(struct clk *clk, u32 *rate)
{
    if (!clk)
    {
        *rate = 0;
    }
    else
    {
        *rate = clk_core_get_rate(clk->core);
    }

    return 0;
}

hal_clk_status_t clk_set_rate(struct clk *clk, u32 rate)
{
    struct clk *p_clk;

    if (!clk)
    {
        return 0;
    }

    p_clk = clk_get_parent(clk);

    return clk_core_set_rate(clk->core, p_clk->core, rate);
}

hal_clk_status_t clk_recalc_rate(struct clk *clk, u32 *rate)
{
    struct clk *p_clk;

    if (!clk)
    {
        return 0;
    }

    p_clk = clk_get_parent(clk);

    *rate = clk_core_recalc_rate(clk->core, p_clk->core);

    return 0;
}

hal_clk_status_t clk_round_rate(struct clk *clk, u32 rate, u32 *round_rate)
{
    if (!clk)
    {
        round_rate = 0;
        return 0;
    }

    *round_rate = clk_core_round_rate(clk->core, rate);

    return 0;
}
