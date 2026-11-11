/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-03-27     Evlers       first version
 */

#include <rtdevice.h>

#ifdef RT_USING_FINSH

#include <limits.h>
#include <stdlib.h>

static void regulator_msh_usage(void)
{
    rt_kprintf("Usage:\n");
    rt_kprintf("  regulator list\n");
    rt_kprintf("  regulator info <name>\n");
    rt_kprintf("  regulator <name> on|off|status\n");
    rt_kprintf("  regulator <name> getv\n");
    rt_kprintf("  regulator <name> setv <min_uV> [max_uV]\n");
    rt_kprintf("  regulator <name> getc\n");
    rt_kprintf("  regulator <name> setc <min_uA> [max_uA]\n");
}

static rt_bool_t regulator_node_is_enabled(struct rt_regulator_node *node)
{
    if (!node)
    {
        return RT_FALSE;
    }

    if (node->ops->is_enabled)
    {
        return node->ops->is_enabled(node);
    }

    return rt_atomic_load(&node->enabled_count) > 0;
}

static rt_err_t regulator_msh_parse_value(const char *str, int *out)
{
    char *endptr;
    long value;

    if (!str || !out)
    {
        return -RT_EINVAL;
    }

    value = strtol(str, &endptr, 10);
    if (endptr == str || *endptr != '\0')
    {
        return -RT_EINVAL;
    }

    if (value <= 0 || value > INT_MAX)
    {
        return -RT_EINVAL;
    }

    *out = (int)value;
    return RT_EOK;
}

static rt_err_t regulator_msh_get_reg(const char *name, struct rt_regulator **out)
{
    struct rt_regulator *reg;

    if (!name || !out)
    {
        return -RT_EINVAL;
    }

    reg = rt_regulator_get(RT_NULL, name);
    if (!reg)
    {
        rt_kprintf("regulator '%s' not found\n", name);
        return -RT_ERROR;
    }

    if (rt_is_err(reg))
    {
        rt_err_t err = rt_ptr_err(reg);

        rt_kprintf("regulator '%s' get failed: %d\n", name, err);
        return err;
    }

    *out = reg;
    return RT_EOK;
}

static struct rt_regulator_node *regulator_find_node_by_name(const char *name)
{
    struct rt_regulator_node **nodes;
    struct rt_regulator_node *result = RT_NULL;
    rt_size_t count = 0;
    rt_size_t i;

    if (!name)
    {
        return RT_NULL;
    }

    nodes = rt_regulator_nodes_snapshot(&count);
    if (!nodes)
    {
        return RT_NULL;
    }

    for (i = 0; i < count; ++i)
    {
        if (nodes[i]->supply_name && !rt_strcmp(nodes[i]->supply_name, name))
        {
            result = nodes[i];
            break;
        }
    }

    rt_regulator_nodes_snapshot_free(nodes, count);
    return result;
}

static rt_err_t regulator_msh_info(const char *name)
{
    struct rt_regulator *reg;
    struct rt_regulator_node *node;
    const struct rt_regulator_param *param;
    rt_err_t err;
    int value;

    node = regulator_find_node_by_name(name);
    if (!node)
    {
        rt_kprintf("regulator '%s' not found\n", name ? name : "(null)");
        return -RT_ERROR;
    }

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    param = node->param;

    rt_kprintf("Regulator info:\n");
    rt_kprintf("  name        : %s\n", node->supply_name ? node->supply_name : "(null)");
    rt_kprintf("  state       : %s\n", regulator_node_is_enabled(node) ? "on" : "off");
    rt_kprintf("  enabled_cnt : %d\n", rt_atomic_load(&node->enabled_count));

    if (param)
    {
        rt_kprintf("  boot_on     : %d\n", param->boot_on);
        rt_kprintf("  always_on   : %d\n", param->always_on);
        if (param->min_uvolt || param->max_uvolt)
        {
            rt_kprintf("  volt_range  : [%d, %d] uV\n", param->min_uvolt, param->max_uvolt);
        }
        if (param->min_uamp || param->max_uamp)
        {
            rt_kprintf("  curr_range  : [%d, %d] uA\n", param->min_uamp, param->max_uamp);
        }
        if (param->enable_delay)
        {
            rt_kprintf("  enable_delay: %d us\n", param->enable_delay);
        }
        if (param->off_on_delay)
        {
            rt_kprintf("  off_on_delay: %d us\n", param->off_on_delay);
        }
    }

    value = rt_regulator_get_voltage(reg);
    if (value >= 0)
    {
        rt_kprintf("  voltage_now : %d uV\n", value);
    }

    value = rt_regulator_get_current(reg);
    if (value >= 0)
    {
        rt_kprintf("  current_now : %d uA\n", value);
    }

    value = rt_regulator_get_mode(reg);
    if (value >= 0)
    {
        rt_kprintf("  mode        : 0x%X\n", value);
    }

    rt_regulator_put(reg);

    return RT_EOK;
}

static void regulator_msh_list(void)
{
    struct rt_regulator_node **nodes;
    rt_size_t count = 0;
    rt_size_t idx;

    nodes = rt_regulator_nodes_snapshot(&count);

    rt_kprintf("Regulator list:\n");

    if (!nodes || !count)
    {
        rt_kprintf("  (none)\n");
        return;
    }

    for (idx = 0; idx < count; idx++)
    {
        rt_kprintf("%2d) %-20s state=%-3s boot_on=%d always_on=%d\n",
                (int)(idx + 1),
                nodes[idx]->supply_name ? nodes[idx]->supply_name : "(null)",
                regulator_node_is_enabled(nodes[idx]) ? "on" : "off",
                nodes[idx]->param ? nodes[idx]->param->boot_on : 0,
                nodes[idx]->param ? nodes[idx]->param->always_on : 0);
    }

    rt_kprintf("Total: %d\n", (int)count);
    rt_regulator_nodes_snapshot_free(nodes, count);
}

static rt_err_t regulator_msh_switch(const char *name, rt_bool_t enable)
{
    struct rt_regulator *reg;
    struct rt_regulator_node *node;
    rt_err_t err;
    int enabled_cnt = -1;

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    node = regulator_find_node_by_name(name);

    if (enable)
    {
        err = rt_regulator_enable(reg);
    }
    else
    {
        err = rt_regulator_disable(reg);
    }

    if (err)
    {
        rt_kprintf("%s '%s' failed: %d\n", enable ? "enable" : "disable", name, err);
    }
    else
    {
        if (node)
        {
            enabled_cnt = (int)rt_atomic_load(&node->enabled_count);
        }

        if (enabled_cnt >= 0)
        {
            rt_kprintf("regulator '%s' %s (enabled_cnt=%d)\n", name,
                    enable ? "enabled" : "disabled", enabled_cnt);
        }
        else
        {
            rt_kprintf("regulator '%s' %s\n", name, enable ? "enabled" : "disabled");
        }
    }

    rt_regulator_put(reg);
    return err;
}

static rt_err_t regulator_msh_status(const char *name)
{
    struct rt_regulator *reg;
    rt_err_t err;

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    rt_kprintf("regulator '%s' is %s\n", name, rt_regulator_is_enabled(reg) ? "on" : "off");
    rt_regulator_put(reg);

    return RT_EOK;
}

static rt_err_t regulator_msh_get_voltage_cmd(const char *name)
{
    struct rt_regulator *reg;
    rt_err_t err;
    int value;

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    value = rt_regulator_get_voltage(reg);
    if (value < 0)
    {
        rt_kprintf("get voltage of '%s' failed: %d\n", name, value);
        err = value;
    }
    else
    {
        rt_kprintf("regulator '%s' voltage: %d uV\n", name, value);
    }

    rt_regulator_put(reg);
    return err;
}

static rt_err_t regulator_msh_set_voltage_cmd(const char *name, const char *min_str, const char *max_str)
{
    struct rt_regulator *reg;
    int min_uvolt;
    int max_uvolt;
    rt_err_t err;

    if ((err = regulator_msh_parse_value(min_str, &min_uvolt)))
    {
        rt_kprintf("invalid min_uV: %s\n", min_str ? min_str : "(null)");
        return err;
    }

    if (max_str)
    {
        if ((err = regulator_msh_parse_value(max_str, &max_uvolt)))
        {
            rt_kprintf("invalid max_uV: %s\n", max_str);
            return err;
        }
    }
    else
    {
        max_uvolt = min_uvolt;
    }

    if (max_uvolt < min_uvolt)
    {
        rt_kprintf("max_uV must be >= min_uV\n");
        return -RT_EINVAL;
    }

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    err = rt_regulator_set_voltage(reg, min_uvolt, max_uvolt);
    if (err)
    {
        rt_kprintf("set voltage of '%s' failed: %d\n", name, err);
    }
    else
    {
        rt_kprintf("regulator '%s' voltage set to [%d, %d] uV\n", name, min_uvolt, max_uvolt);
    }

    rt_regulator_put(reg);
    return err;
}

static rt_err_t regulator_msh_get_current_cmd(const char *name)
{
    struct rt_regulator *reg;
    rt_err_t err;
    int value;

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    value = rt_regulator_get_current(reg);
    if (value < 0)
    {
        rt_kprintf("get current of '%s' failed: %d\n", name, value);
        err = value;
    }
    else
    {
        rt_kprintf("regulator '%s' current: %d uA\n", name, value);
    }

    rt_regulator_put(reg);
    return err;
}

static rt_err_t regulator_msh_set_current_cmd(const char *name, const char *min_str, const char *max_str)
{
    struct rt_regulator *reg;
    int min_uamp;
    int max_uamp;
    rt_err_t err;

    if ((err = regulator_msh_parse_value(min_str, &min_uamp)))
    {
        rt_kprintf("invalid min_uA: %s\n", min_str ? min_str : "(null)");
        return err;
    }

    if (max_str)
    {
        if ((err = regulator_msh_parse_value(max_str, &max_uamp)))
        {
            rt_kprintf("invalid max_uA: %s\n", max_str);
            return err;
        }
    }
    else
    {
        max_uamp = min_uamp;
    }

    if (max_uamp < min_uamp)
    {
        rt_kprintf("max_uA must be >= min_uA\n");
        return -RT_EINVAL;
    }

    err = regulator_msh_get_reg(name, &reg);
    if (err)
    {
        return err;
    }

    if (!rt_regulator_is_supported_current(reg, min_uamp, max_uamp))
    {
        rt_kprintf("regulator '%s' does not support current setting in [%d, %d] uA\n",
                   name, min_uamp, max_uamp);
        rt_regulator_put(reg);
        return -RT_ENOSYS;
    }

    err = rt_regulator_set_current(reg, min_uamp, max_uamp);
    if (err)
    {
        rt_kprintf("set current of '%s' failed: %d\n", name, err);
    }
    else
    {
        rt_kprintf("regulator '%s' current set to [%d, %d] uA\n", name, min_uamp, max_uamp);
    }

    rt_regulator_put(reg);
    return err;
}

static int regulator_msh(int argc, char **argv)
{
    if (argc < 2)
    {
        regulator_msh_usage();
        return RT_EOK;
    }

    if (!rt_strcmp(argv[1], "list"))
    {
        regulator_msh_list();
        return RT_EOK;
    }

    if (!rt_strcmp(argv[1], "info"))
    {
        if (argc < 3)
        {
            regulator_msh_usage();
            return -RT_EINVAL;
        }

        return regulator_msh_info(argv[2]);
    }

    if (argc < 3)
    {
        regulator_msh_usage();
        return -RT_EINVAL;
    }

    if (!rt_strcmp(argv[2], "on"))
    {
        return regulator_msh_switch(argv[1], RT_TRUE);
    }

    if (!rt_strcmp(argv[2], "off"))
    {
        return regulator_msh_switch(argv[1], RT_FALSE);
    }

    if (!rt_strcmp(argv[2], "status"))
    {
        return regulator_msh_status(argv[1]);
    }

    if (!rt_strcmp(argv[2], "getv"))
    {
        return regulator_msh_get_voltage_cmd(argv[1]);
    }

    if (!rt_strcmp(argv[2], "setv"))
    {
        if (argc < 4)
        {
            regulator_msh_usage();
            return -RT_EINVAL;
        }

        return regulator_msh_set_voltage_cmd(argv[1], argv[3], argc >= 5 ? argv[4] : RT_NULL);
    }

    if (!rt_strcmp(argv[2], "getc"))
    {
        return regulator_msh_get_current_cmd(argv[1]);
    }

    if (!rt_strcmp(argv[2], "setc"))
    {
        if (argc < 4)
        {
            regulator_msh_usage();
            return -RT_EINVAL;
        }

        return regulator_msh_set_current_cmd(argv[1], argv[3], argc >= 5 ? argv[4] : RT_NULL);
    }

    regulator_msh_usage();
    return -RT_EINVAL;
}
MSH_CMD_EXPORT_ALIAS(regulator_msh, regulator, regulator command);

#endif /* RT_USING_FINSH */
