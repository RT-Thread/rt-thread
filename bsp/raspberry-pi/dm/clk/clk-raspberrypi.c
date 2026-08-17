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

#define DBG_TAG "clk.raspberrypi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <drivers/byteorder.h>
#include <firmware-raspberrypi.h>

#define RPI_FIRMWARE_STATE_ENABLE_BIT   RT_BIT(0)
#define RPI_FIRMWARE_STATE_WAIT_BIT     RT_BIT(1)

/*
 * Structure of the message passed to Raspberry Pi's firmware in order to
 * change clock rates. The 'disable_turbo' option is only available to the ARM
 * clock (pllb) which we enable by default as turbo mode will alter multiple
 * clocks at once.
 *
 * Even though we're able to access the clock registers directly we're bound to
 * use the firmware interface as the firmware ultimately takes care of
 * mitigating overheating/undervoltage situations and we would be changing
 * frequencies behind his back.
 *
 * For more information on the firmware interface check:
 * https://github.com/raspberrypi/firmware/wiki/Mailbox-property-interface
 */
rt_packed(struct raspberrypi_firmware_prop
{
    rt_le32_t id;
    rt_le32_t val;
    rt_le32_t disable_turbo;
});

struct rpi_firmware_get_clocks_response
{
    rt_uint32_t parent;
    rt_uint32_t id;
};

struct raspberrypi_clk_data
{
    struct rt_clk_cell cell;

    rt_uint32_t id;
    rt_bool_t export;
    rt_bool_t minimize;
    rt_ubase_t min_rate;
};

#define cell_to_raspberrypi_clk_data(cell) rt_container_of(cell, struct raspberrypi_clk_data, cell)

struct raspberrypi_clk
{
    struct rt_clk_node parent;

    struct rpi_firmware *rpi_fw;
};

#define raw_to_raspberrypi_clk(raw) rt_container_of(raw, struct raspberrypi_clk, parent)

static rt_err_t raspberrypi_clock_property(struct rpi_firmware *firmware,
        struct raspberrypi_clk_data *data, rt_uint32_t tag, rt_uint32_t *val)
{
    rt_err_t err;
    struct raspberrypi_firmware_prop msg =
    {
        .id = rt_cpu_to_le32(data->id),
        .val = rt_cpu_to_le32(*val),
        .disable_turbo = rt_cpu_to_le32(0),
    };

    if ((err = rpi_firmware_property(firmware, tag, &msg, sizeof(msg))))
    {
        return err;
    }

    *val = rt_le32_to_cpu(msg.val);

    return RT_EOK;
}

static rt_bool_t raspberrypi_fw_is_prepared(struct rt_clk_cell *cell)
{
    rt_err_t err;
    rt_uint32_t val = 0;
    struct raspberrypi_clk_data *data = cell_to_raspberrypi_clk_data(cell);
    struct raspberrypi_clk *rpi_clk = raw_to_raspberrypi_clk(cell->clk_np);

    if ((err = raspberrypi_clock_property(rpi_clk->rpi_fw, data,
            RPI_FIRMWARE_GET_CLOCK_STATE, &val)))
    {
        return RT_FALSE;
    }

    return !!(val & RPI_FIRMWARE_STATE_ENABLE_BIT);
}

static rt_ubase_t raspberrypi_fw_get_rate(struct rt_clk_cell *cell, rt_ubase_t parent_rate)
{
    rt_err_t err;
    rt_uint32_t val = 0;
    struct raspberrypi_clk_data *data = cell_to_raspberrypi_clk_data(cell);
    struct raspberrypi_clk *rpi_clk = raw_to_raspberrypi_clk(cell->clk_np);

    if ((err = raspberrypi_clock_property(rpi_clk->rpi_fw, data,
            RPI_FIRMWARE_GET_CLOCK_RATE, &val)))
    {
        return -RT_EIO;
    }

    return val;
}

static rt_err_t raspberrypi_fw_set_rate(struct rt_clk_cell *cell,
        rt_ubase_t rate, rt_ubase_t parent_rate)
{
    rt_err_t err;
    rt_uint32_t in_rate = rate;
    struct raspberrypi_clk_data *data = cell_to_raspberrypi_clk_data(cell);
    struct raspberrypi_clk *rpi_clk = raw_to_raspberrypi_clk(cell->clk_np);

    if ((err = raspberrypi_clock_property(rpi_clk->rpi_fw, data,
            RPI_FIRMWARE_SET_CLOCK_RATE, &in_rate)))
    {
        return err;
    }

    return RT_EOK;
}

static const struct rt_clk_ops raspberrypi_firmware_clk_ops =
{
    .is_prepared = raspberrypi_fw_is_prepared,
    .recalc_rate = raspberrypi_fw_get_rate,
    .set_rate = raspberrypi_fw_set_rate,
};

#define REGISTER_CLK(_struct, _name, ...)       \
static struct raspberrypi_clk_data _struct =    \
{                                               \
    .cell.name = _name,                         \
    .cell.ops = &raspberrypi_firmware_clk_ops,  \
    .cell.flags = RT_CLK_F_GET_RATE_NOCACHE,    \
    __VA_ARGS__                                 \
};

REGISTER_CLK(clk_emmc, "emmc");
REGISTER_CLK(clk_uart, "uart");
REGISTER_CLK(clk_arm, "arm", .export = RT_TRUE);
REGISTER_CLK(clk_core, "core",
    .export = RT_TRUE,

    /*
     * The clock is shared between the HVS and the CSI
     * controllers, on the BCM2711 and will change depending
     * on the pixels composited on the HVS and the capture
     * resolution on Unicam.
     *
     * Since the rate can get quite large, and we need to
     * coordinate between both driver instances, let's
     * always use the minimum the drivers will let us.
     */
    .minimize = RT_TRUE);
REGISTER_CLK(clk_v3d, "v3d", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_h264, "h264");
REGISTER_CLK(clk_isp, "isp", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_sdram, "sdram");
REGISTER_CLK(clk_pixel, "pixel", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_pwm, "pwm");
REGISTER_CLK(clk_hevc, "hevc", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_emmc2, "emmc2");
REGISTER_CLK(clk_m2mc, "m2mc",
    .export = RT_TRUE,
    /*
     * If we boot without any cable connected to any of the
     * HDMI connector, the firmware will skip the HSM
     * initialization and leave it with a rate of 0,
     * resulting in a bus lockup when we're accessing the
     * registers even if it's enabled.
     *
     * Let's put a sensible default so that we don't end up
     * in this situation.
     */
    .min_rate = 120000000,
    /*
     * The clock is shared between the two HDMI controllers
     * on the BCM2711 and will change depending on the
     * resolution output on each. Since the rate can get
     * quite large, and we need to coordinate between both
     * driver instances, let's always use the minimum the
     * drivers will let us.
     */
    .minimize = RT_TRUE);
REGISTER_CLK(clk_pixel_bvb, "pixel-bvb", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_vec, "vec", .export = RT_TRUE, .minimize = RT_TRUE);
REGISTER_CLK(clk_disp, "disp", .export = RT_TRUE, .minimize = RT_TRUE);

static struct rt_clk_cell *raspberrypi_clk_cell[RPI_FIRMWARE_NUM_CLK_ID] =
{
    [RPI_FIRMWARE_EMMC_CLK_ID]      = &clk_emmc.cell,
    [RPI_FIRMWARE_UART_CLK_ID]      = &clk_uart.cell,
    [RPI_FIRMWARE_ARM_CLK_ID]       = &clk_arm.cell,
    [RPI_FIRMWARE_CORE_CLK_ID]      = &clk_core.cell,
    [RPI_FIRMWARE_V3D_CLK_ID]       = &clk_v3d.cell,
    [RPI_FIRMWARE_H264_CLK_ID]      = &clk_h264.cell,
    [RPI_FIRMWARE_ISP_CLK_ID]       = &clk_isp.cell,
    [RPI_FIRMWARE_SDRAM_CLK_ID]     = &clk_sdram.cell,
    [RPI_FIRMWARE_PIXEL_CLK_ID]     = &clk_pixel.cell,
    [RPI_FIRMWARE_PWM_CLK_ID]       = &clk_pwm.cell,
    [RPI_FIRMWARE_HEVC_CLK_ID]      = &clk_hevc.cell,
    [RPI_FIRMWARE_EMMC2_CLK_ID]     = &clk_emmc2.cell,
    [RPI_FIRMWARE_M2MC_CLK_ID]      = &clk_m2mc.cell,
    [RPI_FIRMWARE_PIXEL_BVB_CLK_ID] = &clk_pixel_bvb.cell,
    [RPI_FIRMWARE_VEC_CLK_ID]       = &clk_vec.cell,
    [RPI_FIRMWARE_DISP_CLK_ID]      = &clk_disp.cell,
};

struct rt_clk *raspberrypi_arm_clk_get(void)
{
    if (!clk_arm.cell.clk_np)
    {
        return RT_NULL;
    }

    return rt_clk_cell_get_clk(&clk_arm.cell, RT_NULL);
}

static rt_err_t raspberrypi_clk_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *fw_np;
    struct rpi_firmware_get_clocks_response *clks;
    struct raspberrypi_clk *rpi_clk = rt_calloc(1, sizeof(*rpi_clk));

    if (!rpi_clk)
    {
        return -RT_ENOMEM;
    }

    if (np)
    {
        fw_np = rt_ofw_get_parent(np);

        if (fw_np)
        {
            rpi_clk->rpi_fw = rpi_firmware_get(fw_np);
            rt_ofw_node_put(fw_np);
        }
    }

    if (!rpi_clk->rpi_fw)
    {
        fw_np = rt_ofw_parse_phandle(np, "firmware", 0);

        if (fw_np)
        {
            rpi_clk->rpi_fw = rpi_firmware_get(fw_np);
            rt_ofw_node_put(fw_np);
        }
    }

    if (!rpi_clk->rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    if (!(clks = rt_malloc(sizeof(*clks) * RPI_FIRMWARE_NUM_CLK_ID)))
    {
        goto _fail;
    }

    if ((err = rpi_firmware_property(rpi_clk->rpi_fw, RPI_FIRMWARE_GET_CLOCKS,
            clks, sizeof(*clks) * RPI_FIRMWARE_NUM_CLK_ID)))
    {
        rt_free(clks);
        goto _fail;
    }

    for (int i = 0; i < RPI_FIRMWARE_NUM_CLK_ID; ++i)
    {
        rt_uint32_t min_rate = 0, max_rate = 0;
        struct rt_clk *clk;
        struct rt_clk_cell *cell;
        struct raspberrypi_clk_data *data;
        struct rpi_firmware_get_clocks_response *clk_req = &clks[i];

        if (!clk_req->id)
        {
            break;
        }
        cell = raspberrypi_clk_cell[clk_req->id];
        if (!cell)
        {
            continue;
        }

        cell->clk_np = &rpi_clk->parent;
        data = cell_to_raspberrypi_clk_data(cell);

        data->id = clk_req->id;

        if (raspberrypi_clock_property(rpi_clk->rpi_fw, data,
                RPI_FIRMWARE_GET_MIN_CLOCK_RATE, &min_rate))
        {
            LOG_W("clock %u: get min rate failed", clk_req->id);
        }

        if (raspberrypi_clock_property(rpi_clk->rpi_fw, data,
                RPI_FIRMWARE_GET_MAX_CLOCK_RATE, &max_rate))
        {
            LOG_W("clock %u: get max rate failed", clk_req->id);
        }

        if (!max_rate)
        {
            continue;
        }

        if (clk_req->id == RPI_FIRMWARE_M2MC_CLK_ID)
        {
            min_rate = rt_min_t(rt_uint32_t, min_rate, 120000000);
        }

        clk = rt_clk_cell_get_clk(cell, RT_NULL);

        if (!clk)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        rt_clk_set_rate_range(clk, min_rate, max_rate);

        if (data->min_rate)
        {
            rt_ubase_t rate;

            rt_clk_set_rate_range(clk, data->min_rate, max_rate);

            rate = raspberrypi_fw_get_rate(cell, 0);
            if (rate != (rt_ubase_t)-RT_EIO && rate < data->min_rate)
            {
                raspberrypi_fw_set_rate(cell, data->min_rate, 0);
            }
        }
    }

    rt_free(clks);

    rpi_clk->parent.dev = dev;
    rpi_clk->parent.cells = raspberrypi_clk_cell;
    rpi_clk->parent.cells_nr = RT_ARRAY_SIZE(raspberrypi_clk_cell);

    if ((err = rt_clk_register(&rpi_clk->parent)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    if (rpi_clk->rpi_fw)
    {
        rpi_firmware_put(rpi_clk->rpi_fw);
    }

    rt_free(rpi_clk);

    return err;
}

static const struct rt_ofw_node_id raspberrypi_clk_ofw_ids[] =
{
    { .compatible = "raspberrypi,firmware-clocks" },
    { /* sentinel */ }
};

static struct rt_platform_driver raspberrypi_clk_driver =
{
    .name = "clk-raspberrypi",
    .ids = raspberrypi_clk_ofw_ids,

    .probe = raspberrypi_clk_probe,
};

static int raspberrypi_clk_register(void)
{
    rt_platform_driver_register(&raspberrypi_clk_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(raspberrypi_clk_register);
