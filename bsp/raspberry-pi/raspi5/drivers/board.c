/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <setup.h>
#include <board.h>
#include <rtdevice.h>
#include <drivers/ofw.h>

void rt_hw_board_init(void)
{
    rt_hw_common_setup();
}

/*
 * Several root-level nodes reference RP1 GPIO in the live DT.
 * Resolving that phandle from an early driver probe calls rt_platform_ofw_request()
 * on the RP1 subtree before PCIe has enumerated the RP1 device.
 *
 * Mark those nodes unavailable at INIT_CORE (before platform_ofw / early probes),
 * then restore them later once platform init has passed the RP1 bring-up window.
 */
static struct rt_ofw_prop *cam0_status_prop = RT_NULL;
static struct rt_ofw_prop *cam1_status_prop = RT_NULL;
static struct rt_ofw_prop *leds_status_prop = RT_NULL;

static void ofw_status_mark(const char *path, struct rt_ofw_prop **status_prop,
        const char *status)
{
    struct rt_ofw_node *np;
    rt_size_t len = rt_strlen(status) + 1;

    if (!(np = rt_ofw_find_node_by_path(path)))
    {
        return;
    }

    if (!(*status_prop = rt_ofw_get_prop(np, "status", RT_NULL)))
    {
        if (rt_ofw_append_prop(np, "status", len, (void *)status))
        {
            rt_kprintf("append prop status failed on %s\n", path);
            RT_ASSERT(0);
        }

        *status_prop = rt_ofw_get_prop(np, "status", RT_NULL);
    }

    if (*status_prop)
    {
        (*status_prop)->value = (char *)status;
        (*status_prop)->length = len;
    }

    rt_ofw_node_put(np);
}

static int early_rp1_consumer_disable(void)
{
    ofw_status_mark("/cam0_reg", &cam0_status_prop, "disabled");
    ofw_status_mark("/cam1_reg", &cam1_status_prop, "disabled");
    ofw_status_mark("/leds", &leds_status_prop, "disabled");

    return RT_EOK;
}
INIT_CORE_EXPORT(early_rp1_consumer_disable);

static struct rt_ofw_prop *fb_status_prop = RT_NULL;

#ifdef RT_GRAPHIC_FB_BCM2708
static int legacy_framebuffer_enable(void)
{
    ofw_status_mark("/soc/fb", &fb_status_prop, "okay");

    return RT_EOK;
}
INIT_CORE_EXPORT(legacy_framebuffer_enable);
#endif /* RT_GRAPHIC_FB_BCM2708 */

static int cam_regulator_enable(void)
{
    ofw_status_mark("/cam0_reg", &cam0_status_prop, "okay");
    ofw_status_mark("/cam1_reg", &cam1_status_prop, "okay");

    return RT_EOK;
}
INIT_PREV_EXPORT(cam_regulator_enable);

/*
 * /leds is kept out of the INIT_PLATFORM scan above.  After INIT_DEVICE, only
 * register it once mfd.rp1 has published the RP1 PIC on the OFW node; otherwise
 * gpio-leds would pull the RP1 subtree in via GPIO phandle (Path B).
 */
static int leds_init(void)
{
    struct rt_ofw_node *np;

    ofw_status_mark("/leds", &leds_status_prop, "okay");

    if (!(np = rt_ofw_find_node_by_path("/leds")))
    {
        return RT_EOK;
    }

    rt_platform_ofw_request(np);
    rt_ofw_node_put(np);

    return RT_EOK;
}
INIT_EXPORT(leds_init, "3.1");
