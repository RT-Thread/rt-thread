/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-25     liukang      first version
 */

#include <riscv_mal.h>
#include <board.h>

#define DBG_TAG    "mal.riscv"
#ifdef RT_MAL_USING_LOG
#define DBG_LVL    DBG_LOG
#else 
#define DBG_LVL    DBG_INFO
#endif
#include <rtdbg.h>

static rt_err_t _mpu_get_info(rt_thread_t thread, rt_uint32_t type, void *arg)
{
    return RT_EOK;
}

static void _mpu_switch_table(rt_thread_t thread, rt_uint8_t mpu_protect_area_num, 
                                      struct mpu_protect_regions* mpu_protect_areas)
{
    return;
}

static rt_err_t _mpu_init(struct rt_mal_region *tables)
{
    return RT_EOK;
}

static struct rt_mpu_ops _mpu_ops =
{
    .init         = _mpu_init,
    .switch_table = _mpu_switch_table,
    .get_info     = _mpu_get_info
};

static int _mpu_register(void)
{
    rt_err_t result = RT_EOK;

    result = rt_mpu_ops_register(&_mpu_ops);
    if (result != RT_EOK)
    {
        LOG_E("riscv mal ops register failed");
    }

    return result;
}
INIT_BOARD_EXPORT(_mpu_register);
