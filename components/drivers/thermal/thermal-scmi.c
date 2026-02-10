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

#define DBG_TAG "thermal.scmi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

struct scmi_thermal
{
    struct rt_thermal_zone_device parent;

    rt_uint32_t sensor_id;
    rt_uint32_t scale;
    struct rt_scmi_device *sdev;
};

#define raw_to_scmi_thermal(raw) rt_container_of(raw, struct scmi_thermal, parent)

static rt_err_t scmi_thermal_zone_get_temp(struct rt_thermal_zone_device *zdev,
        int *out_temp)
{
    int scale;
    rt_err_t err;
    rt_uint64_t value, factor = 1;
    struct scmi_thermal *st = raw_to_scmi_thermal(zdev);
    struct scmi_sensor_reading_in reading_in =
    {
        .id = rt_cpu_to_le32(st->sensor_id),
        .flags = rt_cpu_to_le32(0),
    };
    struct scmi_sensor_reading_out reading_out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_IN_OUT(SCMI_SENSOR_READING_GET, &reading_in, &reading_out);

    if ((err = rt_scmi_process_msg(st->sdev, &msg)))
    {
        return err;
    }

    value = rt_le32_to_cpu(reading_out.value_high);
    value <<= 32;
    value |= rt_le32_to_cpu(reading_out.value_low);

    scale = st->scale + 3;

    if (scale == 0)
    {
        goto _end;
    }

    if (scale > 19 || scale < -19)
    {
        return -RT_EIO;
    }

    for (int i = 0; i < rt_abs(scale); i++)
    {
        factor *= 10;
    }

    if (scale > 0)
    {
        value *= factor;
    }
    else
    {
        value = rt_div_u64(value, factor);
    }

_end:
    *out_temp = (int)value;

    return err;
}

const static struct rt_thermal_zone_ops scmi_thermal_zone_ops =
{
    .get_temp = scmi_thermal_zone_get_temp,
};

static rt_err_t scmi_thermal_probe(struct rt_scmi_device *sdev)
{
    rt_err_t err;
    struct scmi_sensor_attributes attr = {};
    struct scmi_sensor_description_get_out *desc_out;
    struct rt_scmi_msg msg = RT_SCMI_MSG_OUT(SCMI_COM_MSG_ATTRIBUTES, &attr);

    if ((err = rt_scmi_process_msg(sdev, &msg)))
    {
        return err;
    }

    desc_out = rt_malloc(sizeof(*desc_out) + sizeof(desc_out->desc[0]));

    if (!desc_out)
    {
        return -RT_ENOMEM;
    }

    for (int i = 0, ts_nr = 0; i < attr.num_sensors; ++i)
    {
        struct scmi_thermal *st;
        struct rt_thermal_zone_device *tz;
        struct scmi_sensor_description_get_in desc_in;

        desc_in.desc_index = i;
        msg = RT_SCMI_MSG_IN_OUT(SCMI_SENSOR_DESCRIPTION_GET, &desc_in, desc_out);

        if ((err = rt_scmi_process_msg(sdev, &msg)))
        {
            goto _end;
        }

        if (SCMI_SENSOR_TYPE(rt_le32_to_cpu(desc_out->desc[0].attributes_high)) !=
                SCMI_SENSOR_TYPE_TEMPERATURE_C)
        {
            continue;
        }

        if (!(st = rt_calloc(1, sizeof(*st))))
        {
            err = -RT_ENOMEM;
            goto _end;
        }

        st->sdev = sdev;
        st->sensor_id = rt_le32_to_cpu(desc_out->desc[0].id);
        st->scale = SCMI_SENSOR_SCALE(desc_out->desc[0].attributes_high);

        tz = &st->parent;
        tz->zone_id = ts_nr;
        tz->ops = &scmi_thermal_zone_ops;
        tz->parent.ofw_node = sdev->parent.ofw_node;

        rt_dm_dev_set_name(&tz->parent, "scmi-%s", desc_out->desc[0].name);

        rt_thermal_zone_device_register(tz);

        ++ts_nr;
    }

_end:
    rt_free(desc_out);

    return err;
}

static const struct rt_scmi_device_id scmi_thermal_ids[] =
{
    { SCMI_PROTOCOL_ID_SENSOR, "thermal" },
    { /* sentinel */ },
};

static struct rt_scmi_driver scmi_thermal_driver =
{
    .name = "thermal-scmi",
    .ids = scmi_thermal_ids,

    .probe = scmi_thermal_probe,
};
RT_SCMI_DRIVER_EXPORT(scmi_thermal_driver);
