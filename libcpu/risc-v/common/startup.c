/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>

/*
 * Generic startup preserves the firmware-provided FDT before entering the
 * kernel. The generic DM setup provides the strong implementation; a BSP with
 * custom setup may override this hook when it still uses the common startup.
 */
rt_weak void rt_hw_fdt_install_early(void *fdt)
{
    RT_UNUSED(fdt);
}
