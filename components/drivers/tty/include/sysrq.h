/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023.08.03     xqyjlj       first version
 */
#ifndef __SYSRQ_H__
#define __SYSRQ_H__
#include <rtthread.h>

struct sysrq_opt
{
    int (*const handler)(const char key);
    const char *const help_str;
    const char *const action_str;
};

rt_err_t sysrq_trigger(char key);
void sysrq_num_register(char key, int (*const fun)(const char));
void sysrq_register(char key, const struct sysrq_opt *opt);

#endif
