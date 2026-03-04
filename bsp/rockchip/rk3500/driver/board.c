/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#include <setup.h>
#include <board.h>
#include <psci.h>
#include <drivers/core/power.h>

static void rk3568_machine_shutdown(void)
{
    psci_system_off();
}

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
    rt_dm_machine_shutdown = rk3568_machine_shutdown;
    rt_dm_machine_reset = psci_system_reboot;
}

void reboot(void)
{
    psci_system_reboot();
}
MSH_CMD_EXPORT(reboot, reboot...);
