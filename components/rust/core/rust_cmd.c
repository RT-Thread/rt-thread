/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-09-20     foxglove    First version
 * 2025-10-10     foxglove     Clear Rust component MSH command registration
 *
 * Description: Rust component MSH command registration
 *              Provides access interface to Rust modular APIs
 */

#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <rtdbg.h>

extern int rust_init(void);
/* ============== Rust function declarations ============== */

/* Component initialization */
static int rust_component_init(void)
{
    int ret = rust_init();
    if (ret == 0)
    {
        printf("Hello RT-Thread Rust!\n");
    }
    return ret;
}
#ifdef RUST_INIT_COMPONENT
INIT_APP_EXPORT(rust_component_init);
#endif
