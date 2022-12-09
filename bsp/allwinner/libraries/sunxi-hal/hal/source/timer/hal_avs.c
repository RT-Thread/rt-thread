#include <sunxi_hal_common.h>
#include <sunxi_hal_avs.h>
#include <interrupt.h>
#include <stdlib.h>
#include <stdio.h>

static hal_sunxi_avs hal_avs[AVS_NUM];

int hal_avs_continue(hal_avs_id_t id)
{
    u32 val;
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }
    avs = &hal_avs[id];

    val = hal_readl(avs->base + AVS_CNT_CTRL_REG);
    val &= ~(1 << (id + 8));
    hal_writel(val, avs->base + AVS_CNT_CTRL_REG);
    return 0;
}

int hal_avs_pause(hal_avs_id_t id)
{
    u32 val;
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }
    avs = &hal_avs[id];

    val = hal_readl(avs->base + AVS_CNT_CTRL_REG);
    val |= (1 << (id + 8));
    hal_writel(val, avs->base + AVS_CNT_CTRL_REG);
    return 0;
}

int hal_avs_disable(hal_avs_id_t id)
{
    u32 val;
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }
    avs = &hal_avs[id];

    val = hal_readl(avs->base + AVS_CNT_CTRL_REG);
    val &= ~(1 << id);
    hal_writel(val, avs->base + AVS_CNT_CTRL_REG);
    return 0;
}

int hal_avs_enable(hal_avs_id_t id)
{
    u32 val;
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }
    avs = &hal_avs[id];

    val = hal_readl(avs->base + AVS_CNT_CTRL_REG);
    val |= (1 << id);
    hal_writel(val, avs->base + AVS_CNT_CTRL_REG);
    return 0;
}

int hal_avs_get_counter(hal_avs_id_t id, u32 *counter)
{
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];
    *counter = hal_readl(avs->base + AVS_CNT_REG(id));
    return 0;
}

int hal_avs_set_counter(hal_avs_id_t id, u32 counter)
{
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];

    hal_writel(counter, avs->base + AVS_CNT_REG(id));

    return 0;
}

int hal_avs_set_cnt_div(hal_avs_id_t id, u32 div)
{
    u32 val;
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];

    val = hal_readl(avs->base + AVS_CNT_DIV_REG);
    val &= ~(AVS_DIV_MASK << (16 * id));
    div &= AVS_DIV_MASK;
    val |= (div << (16 * id));
    hal_writel(val, avs->base + AVS_CNT_DIV_REG);

    return 0;
}

int hal_avs_init(hal_avs_id_t id)
{
    hal_sunxi_avs *avs;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];
    avs->id = id;
    avs->base = SUNXI_TMR_PBASE;
    avs->enable = 1;
    avs->clk = hal_clock_get(SUNXI_AVS_CLK_TYPE, SUNXI_AVS_CLK);

    AVS_INFO("avs_clk:%d", avs->clk);
    hal_clock_enable(avs->clk);

    return 0;
}

int hal_avs_uninit(hal_avs_id_t id)
{
    hal_sunxi_avs *avs;
    hal_avs_id_t i;

    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];
    avs->enable = 0;

    for (i = 0; i < AVS_NUM; i++)
    {
        if (hal_avs[i].enable)
        {
            break;
        }
    }

    if (i == AVS_NUM)
    {
        hal_clock_disable(avs->clk);
    }

    return 0;
}

int hal_avs_control(hal_avs_id_t id, hal_avs_cmd_t cmd, void *arg)
{
    hal_sunxi_avs *avs;
    u32 *counter, *div;


    if (id >= AVS_NUM)
    {
        AVS_ERR("avs id is too big!!!\n");
        return -1;
    }

    avs = &hal_avs[id];

    switch (cmd)
    {
        case AVS_ENABLE:
            return hal_avs_enable(id);
        case AVS_DISABLE:
            return hal_avs_disable(id);
        case AVS_PAUSE:
            return hal_avs_pause(id);
        case AVS_CONTINUE:
            return hal_avs_continue(id);
        case AVS_SET_COUNTER:
            counter = (u32 *)arg;
            return hal_avs_set_counter(id, *counter);
        case AVS_GET_COUNTER:
            counter = (u32 *)arg;
            return hal_avs_get_counter(id, counter);
        case AVS_SET_DIV:
            div = (u32 *)arg;
            return hal_avs_set_cnt_div(id, *div);
        default:
            return -1;
    }

    return 0;
}
