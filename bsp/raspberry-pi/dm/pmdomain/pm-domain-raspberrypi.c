/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <firmware-raspberrypi.h>
#include <dt-bindings/power/raspberrypi-power.h>

/*
 * Firmware indices for the old power domains interface.
 * Only a few of them were actually implemented.
 */
#define RPI_OLD_POWER_DOMAIN_USB    3
#define RPI_OLD_POWER_DOMAIN_V3D    10

/*
 * Packet definition used by RPI_FIRMWARE_SET_POWER_STATE and
 * RPI_FIRMWARE_SET_DOMAIN_STATE.
 */
struct rpi_power_domain_packet
{
    rt_uint32_t domain;
    rt_uint32_t state;
};

struct rpi_power_domain
{
    struct rt_dm_power_domain parent;

    rt_uint32_t domain;
    rt_bool_t old_interface;
    struct rpi_firmware *rpi_fw;
};

#define raw_to_rpi_power_domain(raw) rt_container_of(raw, struct rpi_power_domain, parent)

struct rpi_power_domains
{
    struct rt_dm_power_domain_proxy parent;

    rt_bool_t has_new_interface;
    struct rpi_firmware *rpi_fw;
    struct rpi_power_domain domains[RPI_POWER_DOMAIN_COUNT];
};

#define raw_to_rpi_power_domains(raw) rt_container_of(raw, struct rpi_power_domains, parent)

static rt_err_t rpi_firmware_set_power(struct rt_dm_power_domain *domain, rt_bool_t on)
{
    struct rpi_power_domain *rpi_domain = raw_to_rpi_power_domain(domain);
    struct rpi_power_domain_packet packet;

    packet.domain = rpi_domain->domain;
    packet.state = on;

    return rpi_firmware_property(rpi_domain->rpi_fw,
            rpi_domain->old_interface ?
                    RPI_FIRMWARE_SET_POWER_STATE : RPI_FIRMWARE_SET_DOMAIN_STATE,
            &packet, sizeof(packet));
}

static rt_err_t rpi_domain_off(struct rt_dm_power_domain *domain)
{
    return rpi_firmware_set_power(domain, RT_FALSE);
}

static rt_err_t rpi_domain_on(struct rt_dm_power_domain *domain)
{
    return rpi_firmware_set_power(domain, RT_TRUE);
}

static struct rt_dm_power_domain *rpi_power_domains_ofw_parse(
        struct rt_dm_power_domain_proxy *proxy, struct rt_ofw_cell_args *args)
{
    struct rpi_power_domains *rpi_domains = raw_to_rpi_power_domains(proxy);

    return &rpi_domains->domains[args->args[0]].parent;
}

static void rpi_common_init_power_domain(struct rpi_power_domains *rpi_domains, int id)
{
    struct rpi_power_domain *dom = &rpi_domains->domains[id];

    dom->rpi_fw = rpi_domains->rpi_fw;

    dom->parent.power_on = rpi_domain_on;
    dom->parent.power_off = rpi_domain_off;

    rt_dm_power_domain_register(&dom->parent);
}

static void rpi_init_power_domain(struct rpi_power_domains *rpi_domains,
        int id, const char *name)
{
    struct rpi_power_domain *dom = &rpi_domains->domains[id];

    if (!rpi_domains->has_new_interface)
    {
        return;
    }

    /* The DT binding index is the firmware's domain index minus one. */
    dom->domain = id + 1;

    rpi_common_init_power_domain(rpi_domains, id);
    (void)name;
}

static void rpi_init_old_power_domain(struct rpi_power_domains *rpi_domains,
        int id, int domain, const char *name)
{
    struct rpi_power_domain *dom = &rpi_domains->domains[id];

    dom->old_interface = RT_TRUE;
    dom->domain = domain;

    rpi_common_init_power_domain(rpi_domains, id);
    (void)name;
}

/*
 * Detect whether the firmware supports the new power domains interface.
 *
 * The firmware does not return an error on an unknown tag and just skips
 * over it, so probe by putting an unexpected value in the return field
 * and checking if it was unchanged.
 */
static rt_bool_t rpi_has_new_domain_support(struct rpi_power_domains *rpi_domains)
{
    struct rpi_power_domain_packet packet;

    packet.domain = RPI_POWER_DOMAIN_ARM;
    packet.state = ~0;

    return !rpi_firmware_property(rpi_domains->rpi_fw,
            RPI_FIRMWARE_GET_DOMAIN_STATE, &packet, sizeof(packet)) &&
            packet.state != ~0;
}

static rt_err_t rpi_power_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rt_ofw_node *fw_np;
    struct rpi_power_domains *rpi_domains = rt_calloc(1, sizeof(*rpi_domains));

    if (!rpi_domains)
    {
        return -RT_ENOMEM;
    }

    fw_np = rt_ofw_parse_phandle(np, "firmware", 0);
    if (!fw_np)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rpi_domains->rpi_fw = rpi_firmware_get(fw_np);
    rt_ofw_node_put(fw_np);

    if (!rpi_domains->rpi_fw)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    rpi_domains->has_new_interface = rpi_has_new_domain_support(rpi_domains);

    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_I2C0, "I2C0");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_I2C1, "I2C1");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_I2C2, "I2C2");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_VIDEO_SCALER, "VIDEO_SCALER");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_VPU1, "VPU1");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_HDMI, "HDMI");

    /*
     * Use the old firmware interface for USB power, so that we
     * can turn it on even if the firmware hasn't been updated.
     */
    rpi_init_old_power_domain(rpi_domains, RPI_POWER_DOMAIN_USB,
            RPI_OLD_POWER_DOMAIN_USB, "USB");

    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_VEC, "VEC");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_JPEG, "JPEG");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_H264, "H264");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_V3D, "V3D");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_ISP, "ISP");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_UNICAM0, "UNICAM0");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_UNICAM1, "UNICAM1");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_CCP2RX, "CCP2RX");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_CSI2, "CSI2");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_CPI, "CPI");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_DSI0, "DSI0");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_DSI1, "DSI1");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_TRANSPOSER, "TRANSPOSER");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_CCP2TX, "CCP2TX");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_CDP, "CDP");
    rpi_init_power_domain(rpi_domains, RPI_POWER_DOMAIN_ARM, "ARM");

    rpi_domains->parent.ofw_parse = rpi_power_domains_ofw_parse;
    rt_dm_power_domain_proxy_ofw_bind(&rpi_domains->parent, pdev->parent.ofw_node);

    return RT_EOK;

_fail:
    rt_free(rpi_domains);

    return err;
}

static const struct rt_ofw_node_id rpi_power_ofw_ids[] =
{
    { .compatible = "raspberrypi,bcm2835-power" },
    { /* sentinel */ }
};

static struct rt_platform_driver rpi_power_driver =
{
    .name = "raspberrypi-power",
    .ids = rpi_power_ofw_ids,

    .probe = rpi_power_probe,
};

static int rpi_power_drv_register(void)
{
    rt_platform_driver_register(&rpi_power_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rpi_power_drv_register);
