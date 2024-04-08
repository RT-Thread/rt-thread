/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtservice.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.pinctrl"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_OFW
static rt_err_t ofw_pin_ctrl_confs_apply(struct rt_ofw_node *np, int index)
{
    rt_err_t err = -RT_EEMPTY;
    rt_phandle phandle;
    const fdt32_t *cell;
    struct rt_ofw_prop *prop;
    char pinctrl_n_name[sizeof("pinctrl-0")];

    rt_sprintf(pinctrl_n_name, "pinctrl-%d", index);
    index = 0;

    rt_ofw_foreach_prop_u32(np, pinctrl_n_name, prop, cell, phandle)
    {
        struct rt_device_pin *pinctrl = RT_NULL;
        struct rt_ofw_node *conf_np, *pinctrl_np;

        conf_np = pinctrl_np = rt_ofw_find_node_by_phandle(phandle);

        if (!conf_np)
        {
            err = -RT_EIO;

            break;
        }
        /*
         * We always assume the phandle in pinctrl-N is the pinctrl-device
         * node's child node. If not, we need a better way to find it:
         *
         *  / {
         *      serial@4600 {
         *          device_type = "serial";
         *          reg = <0x4600 0x100>;
         *          clock-frequency = <0>;
         *          pinctrl-names = "default";
         *          pinctrl-0 = <&uart_pin>;
         *      };
         *
         *      i2c@4700 {
         *          reg = <0x4700 0x100>;
         *          pinctrl-names = "default";
         *          pinctrl-0 = <&i2c_pin_scl, &i2c_pin_sda>;
         *      };
         *
         *      pinctrl: pinctrl {
         *
         *          uart_pin {
         *              multi,pins =
         *                  <0 PD0 1 &uart_rx_pull_up>,
         *                  <0 PD1 1 &uart_tx_pull_up>;
         *          };
         *
         *          i2c_pin_scl {
         *              single,pins = <0 PB1>;
         *              pull = <&i2c_pull_none_smt>;
         *              function = <1>;
         *          };
         *
         *          i2c_pin_sda {
         *              single,pins = <0 PB2>;
         *              pull = <&i2c_pull_none_smt>;
         *              function = <1>;
         *          };
         *      };
         *  }
         */
        rt_ofw_foreach_parent_node(pinctrl_np)
        {
            if (rt_ofw_prop_read_bool(pinctrl_np, "compatible"))
            {
                break;
            }
        }

        if (pinctrl_np)
        {
            pinctrl = rt_ofw_data(pinctrl_np);

            rt_ofw_node_put(pinctrl_np);
        }

        if (!pinctrl || !pinctrl->ops || !pinctrl->ops->pin_ctrl_confs_apply)
        {
            if (index)
            {
                err = -RT_EEMPTY;
            }
            else
            {
                err = -RT_ERROR;
            }

            rt_ofw_node_put(conf_np);

            break;
        }

        err = pinctrl->ops->pin_ctrl_confs_apply(&pinctrl->parent, conf_np);
        rt_ofw_node_put(conf_np);

        if (err)
        {
            break;
        }

        ++index;
    }

    return err;
}

static int ofw_pin_ctrl_confs_lookup(struct rt_ofw_node *np, const char *name)
{
    return rt_ofw_prop_index_of_string(np, "pinctrl-names", name);
}

static rt_err_t ofw_pin_ctrl_confs_apply_by_name(struct rt_ofw_node *np, const char *name)
{
    int index;
    rt_err_t err;

    index = ofw_pin_ctrl_confs_lookup(np, name);

    if (index >= 0)
    {
        err = ofw_pin_ctrl_confs_apply(np, index);
    }
    else
    {
        err = -RT_EEMPTY;
    }

    return err;
}
#endif /* RT_USING_OFW */

rt_ssize_t rt_pin_ctrl_confs_lookup(struct rt_device *device, const char *name)
{
    rt_ssize_t res;

    if (device && name)
    {
        res = -RT_ENOSYS;

    #ifdef RT_USING_OFW
        if (device->ofw_node)
        {
            res = ofw_pin_ctrl_confs_lookup(device->ofw_node, name);
        }
    #endif /* RT_USING_OFW */
    }
    else
    {
        res = -RT_EINVAL;
    }

    return res;
}

rt_err_t rt_pin_ctrl_confs_apply(struct rt_device *device, int index)
{
    rt_err_t err;

    if (device && index >= 0)
    {
        err = -RT_ENOSYS;

    #ifdef RT_USING_OFW
        if (device->ofw_node)
        {
            err = ofw_pin_ctrl_confs_apply(device->ofw_node, index);
        }
    #endif /* RT_USING_OFW */
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

rt_err_t rt_pin_ctrl_confs_apply_by_name(struct rt_device *device, const char *name)
{
    rt_err_t err;

    if (device)
    {
        if (!name)
        {
            name = "default";
        }

        err = -RT_ENOSYS;

    #ifdef RT_USING_OFW
        if (device->ofw_node)
        {
            err = ofw_pin_ctrl_confs_apply_by_name(device->ofw_node, name);
        }
    #endif /* RT_USING_OFW */
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}
