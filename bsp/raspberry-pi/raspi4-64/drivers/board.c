/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-04-16     bigmagic       first version
 * 2021-12-28     GuEe-GUI       add smp support
 * 2023-03-28     WangXiaoyao    sync works & memory layout fixups
 *                               code formats
 */

#include <setup.h>
#include <board.h>
#include <rtdevice.h>
#include <mmu.h>
#include <mm_aspace.h>

// extern char __noncacheable_start[];
// extern char __noncacheable_end[];

// static void rt_hw_noncacheable_map(void)
// {
//     rt_ubase_t start = (rt_ubase_t)__noncacheable_start;
//     rt_ubase_t end = (rt_ubase_t)__noncacheable_end;
//     rt_size_t size;

//     if (end <= start)
//     {
//         return;
//     }

//     RT_ASSERT((start & (ARCH_SECTION_SIZE - 1)) == 0);
//     RT_ASSERT((end & (ARCH_SECTION_SIZE - 1)) == 0);
//     size = end - start;

//     rt_hw_mmu_control(&rt_kernel_space, (void *)start, size, MMU_CNTL_NONCACHE);
//     rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)start, size);
//     rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)start, size);
// }

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
    // rt_hw_noncacheable_map();
}

static int ttyAMA0_init(void)
{
    const char *con = rt_ofw_bootargs_select("console=", 0);
    struct rt_device_pin *pinctrl;
    struct rt_ofw_node *pinctrl_np, *conf_np;

    /*
     * Pi4 DT routes PL011 to GPIO32/33 (BT). Header UART needs GPIO14/15.
     */
    if (!con || rt_strncmp(con, "ttyAMA0", 7))
    {
        return 0;
    }

    pinctrl_np = rt_ofw_find_node_by_path("/soc/gpio@7e200000");
    conf_np = rt_ofw_get_child_by_tag(pinctrl_np, "uart0-gpio14");

    if (conf_np && (pinctrl = rt_ofw_data(pinctrl_np)))
    {
        pinctrl->ops->pin_ctrl_confs_apply(&pinctrl->parent, conf_np);
    }

    rt_ofw_node_put(conf_np);
    rt_ofw_node_put(pinctrl_np);

    return 0;
}
INIT_EXPORT(ttyAMA0_init, "1.3");
