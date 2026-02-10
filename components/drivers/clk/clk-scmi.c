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
#include <rtdevice.h>

#define DBG_TAG "clk.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_clk
{
    struct rt_clk_node parent;

    struct rt_scmi_device *sdev;
};

#define raw_to_scmi_clk(raw) rt_container_of(raw, struct scmi_clk, parent)

struct scmi_clk_data
{
    struct rt_clk_cell cell;

    int id;
    rt_bool_t rate_discrete;

    union
    {
        struct
        {
            int rates_nr;
            rt_uint64_t rates[];
        } list;
        struct
        {
            rt_uint64_t min_rate;
            rt_uint64_t max_rate;
            rt_uint64_t step_size;
        } range;
    } info;
};

#define cell_to_scmi_clk_data(cell) rt_container_of(cell, struct scmi_clk_data, cell)

static rt_err_t scmi_clk_op_gate(struct scmi_clk *sclk, int clk_id, rt_bool_t enable)
{
    struct scmi_clk_state_in in =
    {
        .clock_id = rt_cpu_to_le32(clk_id),
        .attributes = rt_cpu_to_le32(enable),
    };
    struct scmi_clk_state_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_CLOCK_CONFIG_SET, &in, &out);

    return rt_scmi_process_msg(sclk->sdev, &msg);
}

static rt_base_t scmi_clk_op_get_rate(struct scmi_clk *sclk, int clk_id)
{
    rt_ubase_t res;
    struct scmi_clk_rate_get_in in =
    {
        .clock_id = rt_cpu_to_le32(clk_id),
    };
    struct scmi_clk_rate_get_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_CLOCK_RATE_GET, &in, &out);

    res = rt_scmi_process_msg(sclk->sdev, &msg);

    if ((rt_base_t)res >= 0)
    {
        res = (rt_ubase_t)(((rt_uint64_t)out.rate_msb << 32) | out.rate_lsb);
    }

    return res;
}

static rt_base_t scmi_clk_op_set_rate(struct scmi_clk *sclk, int clk_id, rt_ubase_t rate)
{
    struct scmi_clk_rate_set_in in =
    {
        .clock_id = rt_cpu_to_le32(clk_id),
        .flags = rt_cpu_to_le32(SCMI_CLK_RATE_ROUND_CLOSEST),
        .rate_lsb = rt_cpu_to_le32((rt_uint32_t)rate),
        .rate_msb = rt_cpu_to_le32((rt_uint32_t)((rt_uint64_t)rate >> 32)),
    };
    struct scmi_clk_rate_set_out out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_CLOCK_RATE_SET, &in, &out);

    return rt_scmi_process_msg(sclk->sdev, &msg);
}

static rt_err_t scmi_clk_enable(struct rt_clk_cell *cell)
{
    struct scmi_clk *sclk = raw_to_scmi_clk(cell->clk_np);
    struct scmi_clk_data *clk_data = cell_to_scmi_clk_data(cell);

    return scmi_clk_op_gate(sclk, clk_data->id, RT_TRUE);
}

static void scmi_clk_disable(struct rt_clk_cell *cell)
{
    struct scmi_clk *sclk = raw_to_scmi_clk(cell->clk_np);
    struct scmi_clk_data *clk_data = cell_to_scmi_clk_data(cell);

    scmi_clk_op_gate(sclk, clk_data->id, RT_FALSE);
}

static rt_ubase_t scmi_clk_recalc_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    struct scmi_clk *sclk = raw_to_scmi_clk(cell->clk_np);
    struct scmi_clk_data *clk_data = cell_to_scmi_clk_data(cell);

    return scmi_clk_op_get_rate(sclk, clk_data->id);
}

static rt_base_t scmi_clk_round_rate(struct rt_clk_cell *cell, rt_ubase_t drate, rt_ubase_t *prate)
{
    rt_uint64_t fmin, fmax, ftmp;
    struct scmi_clk_data *clk_data = cell_to_scmi_clk_data(cell);

    if (clk_data->rate_discrete)
    {
        return rate;
    }

    fmin = clk_data->info.range.min_rate;
    fmax = clk_data->info.range.max_rate;

    if (drate <= fmin)
    {
        return fmin;
    }

    if (drate >= fmax)
    {
        return fmax;
    }

    ftmp = drate - fmin;
    ftmp += clk_data->info.range.step_size - 1;
    rt_do_div(ftmp, clk_data->info.range.step_size);

    return ftmp * clk_data->info.range.step_size + fmin;
}

static rt_err_t scmi_clk_set_rate(struct rt_clk_cell *cell, rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_err_t err;
    rt_ubase_t res_rate;
    struct scmi_clk *sclk = raw_to_scmi_clk(cell->clk_np);
    struct scmi_clk_data *clk_data = cell_to_scmi_clk_data(cell);

    if (!(err = scmi_clk_op_set_rate(sclk, clk_data->id, rate)))
    {
        res_rate = scmi_clk_op_get_rate(sclk, clk_data->id);

        if ((rt_err_t)res_rate < 0)
        {
            err = (rt_err_t)res_rate;
        }
    }

    return err;
}

static const struct rt_clk_ops scmi_clk_ops =
{
    .enable = scmi_clk_enable,
    .disable = scmi_clk_disable,
    .recalc_rate = scmi_clk_recalc_rate,
    .round_rate = scmi_clk_round_rate,
    .set_rate = scmi_clk_set_rate,
};

static rt_err_t scmi_clk_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    rt_size_t cell_count, out_size;
    struct rt_scmi_msg msg;
    struct rt_device *dev = &sdev->parent;
    struct rt_clk_cell **cells_list = RT_NULL, *cell;
    struct scmi_clk_data *clk_data;
    struct scmi_clk_describe_rates_out *out = RT_NULL;
    struct scmi_clk_describe_rates_in in;
    struct scmi_clk_attributes attr;
    struct scmi_clk_name_in name_in;
    struct scmi_clk_name_out name_out;
    struct scmi_clk_describe_attributes_in clk_attr_in;
    struct scmi_clk_describe_attributes_out clk_attr_out;
    struct scmi_clk *sclk = rt_calloc(1, sizeof(*sclk));

    if (!sclk)
    {
        return -RT_ENOMEM;
    }

    sclk->sdev = sdev;

    msg = RT_SCMI_MSG_OUT(SCMI_COM_MSG_ATTRIBUTES, &attr);

    if ((err = rt_scmi_process_msg(sclk->sdev, &msg)))
    {
        goto _fail;
    }

    cell_count = rt_le16_to_cpu(attr.num_clocks);

    if (!(cells_list = rt_calloc(cell_count, sizeof(*cells_list))))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    out_size = rt_offsetof(struct scmi_clk_describe_rates_out, rate[SCMI_MAX_NUM_RATES]);

    if (!(out = rt_malloc(out_size)))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int id = 0; id < cell_count; ++id)
    {
        const char *clk_name;
        rt_uint32_t flags, rates_nr, rate_discrete;

        in.id = rt_cpu_to_le32(id);
        in.rate_index = rt_cpu_to_le32(0);
        msg = RT_SCMI_MSG_RAW(SCMI_CLOCK_DESCRIBE_RATES, &in, sizeof(in), out, out_size);

        if ((err = rt_scmi_process_msg(sclk->sdev, &msg)))
        {
            goto _fail;
        }

        flags = rt_le32_to_cpu(out->num_rates_flags);
        rates_nr = SCMI_NUM_REMAINING(flags);
        rate_discrete = SCMI_RATE_DISCRETE(flags);

        if (rate_discrete)
        {
            clk_data = rt_malloc(rt_offsetof(struct scmi_clk_data,
                    info.list.rates[SCMI_MAX_NUM_RATES]));
        }
        else
        {
            clk_data = rt_malloc(sizeof(*clk_data));
        }

        if (!clk_data)
        {
            err = -RT_ENOMEM;
            break;
        }

        if (rate_discrete)
        {
            for (int i = 0; i < rates_nr; ++i)
            {
                clk_data->info.list.rates[i] = SCMI_RATE_TO_U64(out->rate[i]);
            }

            clk_data->info.list.rates_nr = rates_nr;
        }
        else
        {
            clk_data->info.range.min_rate = SCMI_RATE_TO_U64(out->rate[0]);
            clk_data->info.range.max_rate = SCMI_RATE_TO_U64(out->rate[1]);
            clk_data->info.range.step_size = SCMI_RATE_TO_U64(out->rate[2]);
        }

        clk_data->rate_discrete = rate_discrete;
        clk_data->id = id;

        cell = &clk_data->cell;
        rt_memset(cell, 0, sizeof(*cell));

        clk_attr_in.clock_id = rt_cpu_to_le32(id);
        msg = RT_SCMI_MSG_IN_OUT(SCMI_CLOCK_ATTRIBUTES, &clk_attr_in, &clk_attr_out);

        if ((err = rt_scmi_process_msg(sclk->sdev, &msg)))
        {
            rt_free(clk_data);
            goto _fail;
        }

        if (SUPPORTS_EXTENDED_NAMES(clk_attr_out.attributes))
        {
            name_in.clock_id = rt_cpu_to_le32(id);
            msg = RT_SCMI_MSG_IN_OUT(SCMI_CLOCK_NAME_GET, &name_in, &name_out);

            if ((err = rt_scmi_process_msg(sclk->sdev, &msg)))
            {
                rt_free(clk_data);
                goto _fail;
            }

            clk_name = (const char *)name_out.name;
        }
        else
        {
            clk_name = (const char *)clk_attr_out.name;
        }

        if (!(cell->name = rt_strdup(clk_name)))
        {
            rt_free(clk_data);
            err = -RT_ENOMEM;
            goto _fail;
        }

        cell->ops = &scmi_clk_ops;
        cell->flags = RT_CLK_F_GET_RATE_NOCACHE;

        cells_list[id] = cell;
    }

    sclk->parent.dev = dev;
    sclk->parent.cells = cells_list;
    sclk->parent.cells_nr = cell_count;

    if ((err = rt_clk_register(&sclk->parent)))
    {
        goto _fail;
    }

    for (int id = 0; id < cell_count; ++id)
    {
        struct rt_clk *clk = rt_clk_cell_get_clk(cells_list[id], RT_NULL);

        if (clk)
        {
            rt_ubase_t min_rate, max_rate;

            clk_data = cell_to_scmi_clk_data(cells_list[id]);

            if (clk_data->rate_discrete)
            {
                min_rate = clk_data->info.list.rates[0];
                max_rate = clk_data->info.list.rates[clk_data->info.list.rates_nr - 1];
            }
            else
            {
                min_rate = clk_data->info.range.min_rate;
                max_rate = clk_data->info.range.max_rate;
            }

            rt_clk_set_rate_range(clk, min_rate, max_rate);
        }
    }

    return RT_EOK;

_fail:
    if (out)
    {
        rt_free(out);
    }

    if (cells_list)
    {
        for (int id = 0; id < cell_count; ++id)
        {
            if (!cells_list[id])
            {
                break;
            }

            cell = cells_list[id];
            clk_data = cell_to_scmi_clk_data(cell);

            rt_free(clk_data);
        }

        rt_free(cells_list);
    }

    rt_free(sclk);

    return err;
}

static const struct rt_scmi_device_id scmi_clk_ids[] =
{
    { SCMI_PROTOCOL_ID_CLOCK, "clocks" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_clk_driver =
{
    .name = "clk-scmi",
    .ids = scmi_clk_ids,

    .probe = scmi_clk_probe,
};

static int scmi_clk_drv_register(void)
{
    rt_scmi_driver_register(&scmi_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(scmi_clk_drv_register);
