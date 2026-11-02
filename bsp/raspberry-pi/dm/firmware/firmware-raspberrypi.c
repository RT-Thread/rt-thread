/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "fw.raspberrypi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpuport.h>
#include <firmware-raspberrypi.h>
#include <drivers/mailbox.h>

#define MBOX_MSG(chan, data28)  (((data28) & ~0xf) | ((chan) & 0xf))
#define MBOX_CHAN(msg)          ((msg) & 0xf)
#define MBOX_DATA28(msg)        ((msg) & ~0xf)
#define MBOX_CHAN_PROPERTY      8

struct rpi_firmware
{
    struct rt_mbox_client parent;

    /* The property channel. */
    struct rt_mbox_chan *chan;
    rt_bool_t done;
    rt_uint32_t enabled;

    struct rt_ref consumers;
    rt_uint32_t get_throttled;

    struct rt_spinlock transaction_lock;
};

static struct rt_device *rpi_firmware_dma_dev(struct rpi_firmware *rpi_fw)
{
    if (rpi_fw && rpi_fw->chan && rpi_fw->chan->ctrl && rpi_fw->chan->ctrl->dev)
    {
        return rpi_fw->chan->ctrl->dev;
    }

    return rpi_fw ? rpi_fw->parent.dev : RT_NULL;
}

static rt_err_t rpi_firmware_transaction(struct rpi_firmware *rpi_fw,
        rt_uint32_t chan, rt_uint32_t data)
{
    rt_ssize_t res;
    rt_uint32_t message = MBOX_MSG(chan, data);

    rt_hw_spin_lock(&rpi_fw->transaction_lock.lock);

    rpi_fw->done = RT_FALSE;
    res = rt_mbox_send(rpi_fw->chan, &message, RT_WAITING_FOREVER);

    rt_hw_rmb();

    if (res == RT_EOK)
    {
        if (!rpi_fw->done)
        {
            res = -RT_ETIMEOUT;
            LOG_W("Firmware transaction timeout");
        }
    }
    else if (res == -RT_ETIMEOUT && rpi_fw->done)
    {
        res = RT_EOK;
    }
    else if (res == -RT_ETIMEOUT)
    {
        LOG_W("Firmware transaction timeout");
    }
    else
    {
        LOG_E("Mailbox send message error = %s", rt_strerror(res));
    }

    rt_hw_spin_unlock(&rpi_fw->transaction_lock.lock);

    return res;
}

/* RPI made the F*CKING hardware so I written the F*CKING code:) */
void *rpi_firmware_property_raw_alloc(struct rpi_firmware *rpi_fw,
        rt_size_t max_header_tag_size, rt_ubase_t *out_bus_addr)
{
    void *buf;
    rt_size_t size = max_header_tag_size + 12;

    buf = rt_dma_alloc_coherent(rpi_firmware_dma_dev(rpi_fw),
            RT_ALIGN(size, ARCH_PAGE_SIZE), out_bus_addr);

    return buf ? buf + 8 : RT_NULL;
}

void rpi_firmware_property_raw_free(struct rpi_firmware *rpi_fw,
        rt_size_t max_header_tag_size, void *buf, rt_ubase_t bus_addr)
{
    rt_size_t size = max_header_tag_size + 12;

    rt_dma_free_coherent(rpi_firmware_dma_dev(rpi_fw),
            RT_ALIGN(size, ARCH_PAGE_SIZE), buf - 8, bus_addr);
}

rt_err_t rpi_firmware_property(struct rpi_firmware *rpi_fw,
        rt_uint32_t tag, void *tag_data, rt_size_t buf_size)
{
    rt_err_t err;
    void *buf;
    rt_ubase_t bus_addr;
    rt_size_t max_size;
    struct rpi_firmware_property_tag_header *header;

    max_size = sizeof(*header) + buf_size;
    buf = rpi_firmware_property_raw_alloc(rpi_fw, max_size, &bus_addr);

    if (!buf)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(buf + sizeof(*header), tag_data, buf_size);
    err = rpi_firmware_property_raw(rpi_fw, tag, bus_addr, buf, max_size);

    if (!err)
    {
        rt_memcpy(tag_data, buf + sizeof(*header), buf_size);
    }

    rpi_firmware_property_raw_free(rpi_fw, max_size, buf, bus_addr);

    return err;
}

rt_err_t rpi_firmware_property_raw(struct rpi_firmware *rpi_fw, rt_uint32_t tag,
        rt_ubase_t bus_addr, struct rpi_firmware_property_tag_header *header, rt_size_t req_size)
{
    header->tag = tag;
    header->buf_size = req_size - sizeof(*header);
    header->req_resp_size = 0;

    return rpi_firmware_property_list_raw(rpi_fw, bus_addr, (void *)header, req_size);
}

rt_err_t rpi_firmware_property_list(struct rpi_firmware *rpi_fw,
        void *data, rt_size_t tag_size)
{
    rt_err_t err;
    rt_ubase_t bus_addr;
    void *buf = rpi_firmware_property_raw_alloc(rpi_fw, tag_size, &bus_addr);

    if (!buf)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(buf, data, tag_size);

    if (!(err = rpi_firmware_property_list_raw(rpi_fw, bus_addr, buf, tag_size)))
    {
        rt_memcpy(data, buf, tag_size);
    }

    rpi_firmware_property_raw_free(rpi_fw, tag_size, buf, bus_addr);

    return err;
}

rt_err_t rpi_firmware_property_list_raw(struct rpi_firmware *rpi_fw,
        rt_ubase_t bus_addr, void *data, rt_size_t tag_size)
{
    rt_err_t err;
    rt_uint32_t *buf = data - 8;
    rt_size_t size = tag_size + 12;

    /* Packets are processed a dword at a time. */
    if (size & 3)
    {
        return -RT_EINVAL;
    }

    buf[0] = size;
    buf[1] = RPI_FIRMWARE_STATUS_REQUEST;
    buf[size / 4 - 1] = RPI_FIRMWARE_PROPERTY_END;
    rt_hw_wmb();

    err = rpi_firmware_transaction(rpi_fw, MBOX_CHAN_PROPERTY, bus_addr);

    rt_hw_rmb();

    if (err == RT_EOK && !(buf[1] & RPI_FIRMWARE_STATUS_SUCCESS))
    {
        /*
         * The tag name here might not be the one causing the
         * error, if there were multiple tags in the request.
         * But single-tag is the most common, so go with it.
         */
        LOG_E("Request 0x%08x returned status 0x%08x", buf[2], buf[1]);
        err = -RT_EINVAL;
    }
    else if (err == RT_EOK && buf[1] == RPI_FIRMWARE_STATUS_ERROR)
    {
        LOG_E("Request 0x%08x returned error status 0x%08x", buf[2], buf[1]);
        err = -RT_EINVAL;
    }

    return err;
}

rt_uint32_t rpi_firmware_clk_get_max_rate(struct rpi_firmware *rpi_fw, rt_uint32_t id)
{
    struct rpi_firmware_clk_rate_request msg = RPI_FIRMWARE_CLK_RATE_REQUEST(id);

    if (rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_MAX_CLOCK_RATE,
            &msg, sizeof(msg)))
    {
        return RT_UINT32_MAX;
    }

    return rt_le32_to_cpu(msg.rate);
}

static const struct rt_ofw_node_id rpi_firmware_ofw_ids[];

struct rt_ofw_node *rpi_firmware_find_node(void)
{
    return rt_ofw_find_node_by_ids(RT_NULL, rpi_firmware_ofw_ids);
}

struct rpi_firmware *rpi_firmware_get(struct rt_ofw_node *fw_np)
{
    struct rpi_firmware *rpi_fw = rt_ofw_data(fw_np);

    if (!rpi_fw)
    {
        rt_platform_ofw_request(fw_np);
        rpi_fw = rt_ofw_data(fw_np);
    }

    if (!rpi_fw)
    {
        return RT_NULL;
    }

    if (!rt_ref_get_unless_zero(&rpi_fw->consumers))
    {
        return RT_NULL;
    }

    return rpi_fw;
}

static void rpi_firmware_release(struct rt_ref *ref)
{
    struct rpi_firmware *rpi_fw = rt_container_of(ref, struct rpi_firmware, consumers);

    rt_mbox_release(rpi_fw->chan);
    rt_free(rpi_fw);
}

void rpi_firmware_put(struct rpi_firmware *rpi_fw)
{
    rt_ref_put(&rpi_fw->consumers, rpi_firmware_release);
}

static rt_err_t rpi_firmware_notify_reboot(struct rt_device *dev, char *cmd)
{
    rt_uint32_t reboot_flags = 0;
    struct rpi_firmware *rpi_fw = dev->user_data;

    if (cmd && rt_strstr(cmd, "tryboot"))
    {
        reboot_flags |= 0x1;
    }

    if (reboot_flags)
    {
        rpi_firmware_property(rpi_fw, RPI_FIRMWARE_SET_REBOOT_FLAGS,
                &reboot_flags, sizeof(reboot_flags));
    }

    rpi_firmware_property(rpi_fw, RPI_FIRMWARE_NOTIFY_REBOOT, RT_NULL, 0);

    return RT_EOK;
}

static void rpi_firmware_rx_callback(struct rt_mbox_client *client, void *data)
{
    struct rpi_firmware *rpi_fw = rt_container_of(client, struct rpi_firmware, parent);

    rpi_fw->done = RT_TRUE;
    rt_hw_wmb();
}

static void rpi_firmware_check_revision_info(struct rpi_firmware *rpi_fw)
{
    struct tm *tm;
    rt_uint32_t revision, variant, hash[5];
    static const char * const variant_strs[] =
    {
        "unknown",
        "start",
        "start_x",
        "start_db",
        "start_cd",
    };
    const char *variant_str = "cmd unsupported";

    if (rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_FIRMWARE_REVISION,
            &revision, sizeof(revision)))
    {
        goto _check_hash;
    }

    tm = localtime((time_t *)&revision);

    if (!rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_FIRMWARE_VARIANT,
            &variant, sizeof(variant)))
    {
        if (variant >= RT_ARRAY_SIZE(variant_strs))
        {
            variant = 0;
        }

        variant_str = variant_strs[variant];
    }

    LOG_I("Attached to firmware from %04d-%02d-%02d %02d:%02d:%02d, variant %s",
            tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
            tm->tm_hour, tm->tm_min, tm->tm_sec, variant_str);
    (void)tm;
    (void)variant_str;

_check_hash:
    if (rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_FIRMWARE_HASH,
            hash, sizeof(hash)))
    {
        return;
    }

    LOG_I("Firmware hash is %08x%08x%08x%08x%08x",
            hash[0], hash[1], hash[2], hash[3], hash[4]);
}

static rt_err_t rpi_firmware_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t packet;
    struct rt_device *dev = &pdev->parent;
    struct rpi_firmware *rpi_fw = rt_calloc(1, sizeof(*rpi_fw));

    if (!rpi_fw)
    {
        return -RT_ENOMEM;
    }

    dev->user_data = rpi_fw;
    rpi_fw->parent.dev = dev;
    rpi_fw->parent.rx_callback = rpi_firmware_rx_callback;

    rpi_fw->chan = rt_mbox_request_by_index(&rpi_fw->parent, 0);

    if (rt_is_err_or_null(rpi_fw->chan))
    {
        err = -RT_EINVAL;
        LOG_E("Request mailbox fail");

        goto _fail;
    }

    if ((err = rt_dm_reboot_mode_register(dev, &rpi_firmware_notify_reboot)))
    {
        goto _fail;
    }

    rt_ref_init(&rpi_fw->consumers);
    rt_spin_lock_init(&rpi_fw->transaction_lock);

    rt_dm_dev_bind_fwdata(dev, RT_NULL, rpi_fw);

    rpi_firmware_check_revision_info(rpi_fw);

    if (!rpi_firmware_property(rpi_fw, RPI_FIRMWARE_GET_THROTTLED,
            &packet, sizeof(packet)))
    {
        struct rt_platform_device *voltage_monitor;

        if (!(voltage_monitor = rt_calloc(1, sizeof(*voltage_monitor))))
        {
            LOG_E("No memory to create voltage monitor");

            err = -RT_ENOMEM;
            goto _fail;
        }

        voltage_monitor->name = "raspberrypi-voltage-monitor";
        voltage_monitor->priv = dev;

        rt_bus_add_device(pdev->parent.bus, &voltage_monitor->parent);
    }

    return RT_EOK;

_fail:
    if (!rt_is_err_or_null(rpi_fw->chan))
    {
        rt_mbox_release(rpi_fw->chan);
    }

    rt_free(rpi_fw);

    return err;
}

static rt_err_t rpi_firmware_shutdown(struct rt_platform_device *pdev)
{
    struct rpi_firmware *rpi_fw = pdev->parent.user_data;

    rpi_firmware_property(rpi_fw, RPI_FIRMWARE_NOTIFY_REBOOT, RT_NULL, 0);

    return RT_EOK;
}

static const struct rt_ofw_node_id rpi_firmware_ofw_ids[] =
{
    { .compatible = "raspberrypi,bcm2835-firmware", },
    { /* sentinel */ }
};

static struct rt_platform_driver rpi_firmware_driver =
{
    .name = "raspberrypi-firmware",
    .ids = rpi_firmware_ofw_ids,

    .probe = rpi_firmware_probe,
    .shutdown = rpi_firmware_shutdown,
};

static int rpi_firmware_drv_register(void)
{
    rt_platform_driver_register(&rpi_firmware_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(rpi_firmware_drv_register);
