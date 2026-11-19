/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#ifndef __ROCKCHIP_SAI_H__
#define __ROCKCHIP_SAI_H__

#include "rockchip-i2s-tdm.h"

struct rockchip_sai;

#ifdef RT_AUDIO_ROCKCHIP_SAI
struct rockchip_sai *rockchip_sai_find(struct rt_ofw_node *np);
rt_err_t rockchip_sai_hw_params(struct rockchip_sai *sai,
        const struct rockchip_i2s_config *cfg);
rt_err_t rockchip_sai_start(struct rockchip_sai *sai);
rt_err_t rockchip_sai_stop(struct rockchip_sai *sai);
struct rt_dma_chan *rockchip_sai_dma_tx(struct rockchip_sai *sai);
rt_ubase_t rockchip_sai_txdr_phys(struct rockchip_sai *sai);
#else
rt_inline struct rockchip_sai *rockchip_sai_find(struct rt_ofw_node *np)
{
    return RT_NULL;
}
rt_inline rt_err_t rockchip_sai_hw_params(struct rockchip_sai *sai,
        const struct rockchip_i2s_config *cfg)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rockchip_sai_start(struct rockchip_sai *sai)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rockchip_sai_stop(struct rockchip_sai *sai)
{
    return -RT_ENOSYS;
}
rt_inline struct rt_dma_chan *rockchip_sai_dma_tx(struct rockchip_sai *sai)
{
    return RT_NULL;
}
rt_inline rt_ubase_t rockchip_sai_txdr_phys(struct rockchip_sai *sai)
{
    return 0;
}
#endif

#endif /* __ROCKCHIP_SAI_H__ */
