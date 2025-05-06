/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.scsi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/*
 * Since SCSI is used for storage (almost),
 * we do not want to implement SCSI as a system DM bus.
 */
struct scsi_driver
{
    rt_err_t (*probe)(struct rt_scsi_device *sdev);
    rt_err_t (*remove)(struct rt_scsi_device *sdev);
};

extern rt_err_t scsi_sd_probe(struct rt_scsi_device *sdev);
extern rt_err_t scsi_sd_remove(struct rt_scsi_device *sdev);

extern rt_err_t scsi_cdrom_probe(struct rt_scsi_device *sdev);
extern rt_err_t scsi_cdrom_remove(struct rt_scsi_device *sdev);

static struct scsi_driver driver_table[SCSI_DEVICE_TYPE_MAX] =
{
#ifdef RT_SCSI_SD
    [SCSI_DEVICE_TYPE_DIRECT] =
    {
        .probe = scsi_sd_probe,
        .remove = scsi_sd_remove,
    },
#endif /* RT_SCSI_SD */
#ifdef RT_SCSI_CDROM
    [SCSI_DEVICE_TYPE_CDROM] =
    {
        .probe = scsi_cdrom_probe,
        .remove = scsi_cdrom_remove,
    },
#endif /* RT_SCSI_CDROM */
};

static rt_err_t scsi_device_setup(struct rt_scsi_device *sdev)
{
    rt_err_t err;
    rt_tick_t timeout;

    if (sdev->host->ops->reset)
    {
        if ((err = sdev->host->ops->reset(sdev)))
        {
            return err;
        }
    }

    if (!driver_table[sdev->devtype].probe)
    {
        LOG_E("Device type %x is not supported", sdev->devtype);

        return -RT_ENOSYS;
    }

    timeout = rt_tick_from_millisecond(5000);
    timeout += rt_tick_get();

    while ((err = rt_scsi_test_unit_ready(sdev)))
    {
        if (rt_tick_get() >= timeout)
        {
            return -RT_ETIMEOUT;
        }
    }

    return driver_table[sdev->devtype].probe(sdev);
}

rt_err_t rt_scsi_host_register(struct rt_scsi_host *scsi)
{
    struct rt_scsi_device tmp_sdev, *sdev;

    if (!scsi || !scsi->dev || !scsi->ops)
    {
        return -RT_EINVAL;
    }

    if (!scsi->max_id || !scsi->max_lun)
    {
        return -RT_EINVAL;
    }

    rt_list_init(&scsi->lun_nodes);

    rt_memset(&tmp_sdev, 0, sizeof(tmp_sdev));
    tmp_sdev.host = scsi;

    for (rt_size_t id = 0; id < scsi->max_id; ++id)
    {
        for (rt_size_t lun = 0; lun < scsi->max_lun; ++lun)
        {
            tmp_sdev.id = id;
            tmp_sdev.lun = lun;

            if (rt_scsi_inquiry(&tmp_sdev, RT_NULL))
            {
                continue;
            }

            if (tmp_sdev.devtype >= SCSI_DEVICE_TYPE_MAX)
            {
                /*
                 * This might seem odd, but we're only aiming to
                 * support simple SCSI.
                 * If devices appear on the bus out of order,
                 * we won't perform additional scans.
                 */
                scsi->max_id = id;
                scsi->max_lun = lun;

                LOG_D("Scan is end of ID: %u LUN: %u", id, lun);
                break;
            }

            if (!(sdev = rt_malloc(sizeof(*sdev))))
            {
                if (!rt_list_isempty(&scsi->lun_nodes))
                {
                    LOG_E("No memory to create device ID: %u, LUN: %u", id, lun);

                    return RT_EOK;
                }

                return -RT_ENOMEM;
            }

            rt_memcpy(sdev, &tmp_sdev, sizeof(*sdev));
            rt_list_init(&sdev->list);

            if (scsi_device_setup(sdev))
            {
                rt_free(sdev);
                continue;
            }

            rt_list_insert_before(&scsi->lun_nodes, &sdev->list);
        }
    }

    return rt_list_isempty(&scsi->lun_nodes) ? -RT_EEMPTY : RT_EOK;
}

rt_err_t rt_scsi_host_unregister(struct rt_scsi_host *scsi)
{
    struct rt_scsi_device *sdev, *next_sdev;

    if (!scsi)
    {
        return -RT_EINVAL;
    }

    rt_list_for_each_entry_safe(sdev, next_sdev, &scsi->lun_nodes, list)
    {
        rt_list_remove(&sdev->list);

        if (sdev->host->ops->reset)
        {
            sdev->host->ops->reset(sdev);
        }

        if (!driver_table[sdev->devtype].remove)
        {
            driver_table[sdev->devtype].remove(sdev);
        }

        rt_free(sdev);
    }

    return RT_EOK;
}

rt_inline rt_err_t scsi_transfer(struct rt_scsi_device *sdev, struct rt_scsi_cmd *cmd)
{
    return sdev->host->ops->transfer(sdev, cmd);
}

rt_err_t rt_scsi_request_sense(struct rt_scsi_device *sdev,
        struct rt_scsi_request_sense_data *out_data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.request_sense.opcode = RT_SCSI_CMD_REQUEST_SENSE;
    cmd.op.request_sense.config = 0;
    cmd.op.request_sense.alloc_length = 0x12;
    cmd.op.request_sense.control = 0;
    cmd.op_size = sizeof(cmd.op.request_sense);
    cmd.data.ptr = &cmd.data.request_sense;
    cmd.data.size = sizeof(cmd.data.request_sense);

    err = scsi_transfer(sdev, &cmd);

    if (!err && out_data)
    {
        rt_memcpy(out_data, &cmd.data.request_sense, sizeof(*out_data));
    }

    return err;
}

rt_err_t rt_scsi_test_unit_ready(struct rt_scsi_device *sdev)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.test_unit_ready.opcode = RT_SCSI_CMD_TEST_UNIT_READY;
    cmd.op.test_unit_ready.control = 0;
    cmd.op_size = sizeof(cmd.op.test_unit_ready);

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_inquiry(struct rt_scsi_device *sdev,
        struct rt_scsi_inquiry_data *out_data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.inquiry.opcode = RT_SCSI_CMD_INQUIRY;
    cmd.op.inquiry.config = 0;
    cmd.op.inquiry.page = 0;
    cmd.op.inquiry.alloc_length = 0x24;
    cmd.op.inquiry.control = 0;
    cmd.op_size = sizeof(cmd.op.inquiry);
    cmd.data.ptr = &cmd.data.inquiry;
    cmd.data.size = sizeof(cmd.data.inquiry);

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    if (!err)
    {
        sdev->devtype = cmd.data.inquiry.devtype & RT_SCSI_DEVTYPE_MASK;
        sdev->removable = cmd.data.inquiry.rmb >> RT_SCSI_REMOVABLE_BIT;

        if (out_data)
        {
            rt_memcpy(out_data, &cmd.data.inquiry, sizeof(*out_data));
        }
    }

    return err;
}

rt_err_t rt_scsi_read_capacity10(struct rt_scsi_device *sdev,
        struct rt_scsi_read_capacity10_data *out_data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.read_capacity10.opcode = RT_SCSI_CMD_READ_CAPACITY10;
    cmd.op.read_capacity10.config = 0;
    cmd.op.read_capacity10.logical_block_addr = 0;
    cmd.op.read_capacity10.pmi = 0;
    cmd.op.read_capacity10.control = 0;
    cmd.op_size = sizeof(cmd.op.read_capacity10);
    cmd.data.ptr = &cmd.data.read_capacity10;
    cmd.data.size = sizeof(cmd.data.read_capacity10);

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    if (!err)
    {
        sdev->last_block = rt_be32_to_cpu(cmd.data.read_capacity10.last_block);
        sdev->block_size = rt_be32_to_cpu(cmd.data.read_capacity10.block_size);

        if (out_data)
        {
            rt_memcpy(out_data, &cmd.data.read_capacity10, sizeof(*out_data));
        }
    }

    return err;
}

rt_err_t rt_scsi_read_capacity16(struct rt_scsi_device *sdev,
        struct rt_scsi_read_capacity16_data *out_data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.read_capacity16.opcode = RT_SCSI_CMD_READ_CAPACITY16;
    cmd.op.read_capacity16.config = 0x10;
    cmd.op.read_capacity16.logical_block_addr = 0;
    cmd.op.read_capacity16.alloc_len = rt_cpu_to_be32(sizeof(cmd.data.read_capacity16));
    cmd.op.read_capacity16.pmi = 0;
    cmd.op.read_capacity16.control = 0;
    cmd.op_size = sizeof(cmd.op.read_capacity16);
    cmd.data.ptr = &cmd.data.read_capacity16;
    cmd.data.size = sizeof(cmd.data.read_capacity16);

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    if (!err)
    {
        sdev->last_block = rt_be64_to_cpu(cmd.data.read_capacity16.last_block);
        sdev->block_size = rt_be32_to_cpu(cmd.data.read_capacity16.block_size);

        if (out_data)
        {
            rt_memcpy(out_data, &cmd.data.read_capacity16, sizeof(*out_data));
        }
    }

    return err;
}

rt_err_t rt_scsi_read10(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.read10.opcode = RT_SCSI_CMD_READ10;
    cmd.op.read10.config = 0;
    cmd.op.read10.lba = rt_cpu_to_be32(lba);
    cmd.op.read10.size = rt_cpu_to_be16(size);
    cmd.op_size = sizeof(cmd.op.read10);
    cmd.data.ptr = buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_read12(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.read12.opcode = RT_SCSI_CMD_READ12;
    cmd.op.read12.config = 0;
    cmd.op.read12.lba = rt_cpu_to_be32(lba);
    cmd.op.read12.size = rt_cpu_to_be32(size);
    cmd.op.read12.control = 0;
    cmd.op_size = sizeof(cmd.op.read12);
    cmd.data.ptr = buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_read16(struct rt_scsi_device *sdev,
        rt_off_t lba, void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.read16.opcode = RT_SCSI_CMD_READ16;
    cmd.op.read16.config = 0;
    cmd.op.read16.lba = rt_cpu_to_be64(lba);
    cmd.op.read16.size = rt_cpu_to_be32(size);
    cmd.op.read16.control = 0;
    cmd.op_size = sizeof(cmd.op.read16);
    cmd.data.ptr = buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_write10(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.write10.opcode = RT_SCSI_CMD_WRITE10;
    cmd.op.write10.config = 0;
    cmd.op.write10.lba = rt_cpu_to_be32(lba);
    cmd.op.write10.size = rt_cpu_to_be16(size);
    cmd.op_size = sizeof(cmd.op.write10);
    cmd.data.ptr = (void *)buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_write12(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.write12.opcode = RT_SCSI_CMD_WRITE12;
    cmd.op.write12.config = 0;
    cmd.op.write12.lba = rt_cpu_to_be32(lba);
    cmd.op.write12.size = rt_cpu_to_be32(size);
    cmd.op.write12.control = 0;
    cmd.op_size = sizeof(cmd.op.write12);
    cmd.data.ptr = (void *)buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_write16(struct rt_scsi_device *sdev,
        rt_off_t lba, const void *buffer, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.write16.opcode = RT_SCSI_CMD_WRITE16;
    cmd.op.write16.config = 0;
    cmd.op.write16.lba = rt_cpu_to_be64(lba);
    cmd.op.write16.size = rt_cpu_to_be32(size);
    cmd.op.write16.control = 0;
    cmd.op_size = sizeof(cmd.op.write16);
    cmd.data.ptr = (void *)buffer;
    cmd.data.size = size * sdev->block_size;

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_synchronize_cache10(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.synchronize_cache10.opcode = RT_SCSI_CMD_SYNCHRONIZE_CACHE10;
    cmd.op.synchronize_cache10.config = 0;
    cmd.op.synchronize_cache10.lba = rt_cpu_to_be32(lba);
    cmd.op.synchronize_cache10.size = rt_cpu_to_be16(size);
    cmd.op.synchronize_cache10.control = 0;
    cmd.op_size = sizeof(cmd.op.synchronize_cache10);

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_synchronize_cache16(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.synchronize_cache16.opcode = RT_SCSI_CMD_SYNCHRONIZE_CACHE16;
    cmd.op.synchronize_cache16.config = 0;
    cmd.op.synchronize_cache16.lba = rt_cpu_to_be64(lba);
    cmd.op.synchronize_cache16.size = rt_cpu_to_be32(size);
    cmd.op.synchronize_cache16.control = 0;
    cmd.op_size = sizeof(cmd.op.synchronize_cache16);

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_write_same10(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.write_same10.opcode = RT_SCSI_CMD_WRITE_SAME10;
    cmd.op.write_same10.config = RT_BIT(RT_SCSI_UNMAP_SHIFT);
    cmd.op.write_same10.lba = rt_cpu_to_be32(lba);
    cmd.op.write_same10.size = rt_cpu_to_be16(size);
    cmd.op.write_same10.control = 0;
    cmd.op_size = sizeof(cmd.op.write_same10);

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_write_same16(struct rt_scsi_device *sdev,
        rt_off_t lba, rt_size_t size)
{
    struct rt_scsi_cmd cmd;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.write_same16.opcode = RT_SCSI_CMD_WRITE_SAME16;
    cmd.op.write_same16.config = RT_BIT(RT_SCSI_UNMAP_SHIFT);
    cmd.op.write_same16.lba = rt_cpu_to_be64(lba);
    cmd.op.write_same16.size = rt_cpu_to_be32(size);
    cmd.op.write_same16.control = 0;
    cmd.op_size = sizeof(cmd.op.write_same16);

    return scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);
}

rt_err_t rt_scsi_mode_select6(struct rt_scsi_device *sdev,
        rt_uint8_t pf, rt_uint8_t sp, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data)
{
    rt_err_t err;
    rt_uint8_t *real_buffer;
    struct rt_scsi_cmd cmd;

    real_buffer = rt_malloc(4 + size);

    if (!real_buffer)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(real_buffer + 4, buffer, size);
    size += 4;
    real_buffer[0] = 0;
    real_buffer[1] = data->medium_type;
    real_buffer[2] = data->device_specific;
    real_buffer[3] = data->block_descriptor_length;

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.mode_select6.opcode = RT_SCSI_CMD_MODE_SELECT;
    cmd.op.mode_select6.config = pf ? RT_BIT(RT_SCSI_PF_SHIFT) : 0;
    cmd.op.mode_select6.config |= sp ? RT_BIT(RT_SCSI_SP_SHIFT) : 0;
    cmd.op.mode_select6.param_list_len = (rt_uint8_t)size;
    cmd.op.mode_select6.control = 0;
    cmd.op_size = sizeof(cmd.op.mode_select6);
    cmd.data.ptr = real_buffer;
    cmd.data.size = size;

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    rt_free(real_buffer);

    return err;
}

rt_err_t rt_scsi_mode_select10(struct rt_scsi_device *sdev,
        rt_uint8_t pf, rt_uint8_t sp, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data)
{
    rt_err_t err;
    rt_uint8_t *real_buffer;
    struct rt_scsi_cmd cmd;

    real_buffer = rt_malloc(8 + size);

    if (!real_buffer)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(real_buffer + 8, buffer, size);
    size += 8;
    real_buffer[0] = 0;
    real_buffer[1] = 0;
    real_buffer[2] = data->medium_type;
    real_buffer[3] = data->device_specific;
    real_buffer[4] = data->longlba ? 0x01 : 0;
    real_buffer[5] = 0;
    real_buffer[6] = rt_cpu_to_be16(data->block_descriptor_length);

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.mode_select10.opcode = RT_SCSI_CMD_MODE_SELECT10;
    cmd.op.mode_select10.config = pf ? RT_BIT(RT_SCSI_PF_SHIFT) : 0;
    cmd.op.mode_select10.config |= sp ? RT_BIT(RT_SCSI_SP_SHIFT) : 0;
    cmd.op.mode_select10.param_list_len = rt_cpu_to_be16(size);
    cmd.op.mode_select10.control = 0;
    cmd.op_size = sizeof(cmd.op.mode_select10);
    cmd.data.ptr = real_buffer;
    cmd.data.size = size;

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    rt_free(real_buffer);

    return err;
}

static void scsi_mode_sense_fill(struct rt_scsi_mode_select_data *data,
        rt_uint8_t modepage, rt_uint8_t *buffer, rt_bool_t use10)
{
    if (buffer[0] == 0x86 && buffer[1] == 0x0b && (modepage == 6 || modepage == 8))
    {
        data->header_length = 0;
        data->length = 13;
        data->medium_type = 0;
        data->device_specific = 0;
        data->longlba = 0;
        data->block_descriptor_length = 0;
    }
    else if (use10)
    {
        data->length = rt_be16_to_cpu(buffer[0]) + 2;
        data->medium_type = buffer[2];
        data->device_specific = buffer[3];
        data->longlba = buffer[4] & 0x01;
        data->block_descriptor_length = rt_be16_to_cpu(buffer[6]);
    }
    else
    {
        data->length = buffer[0] + 1;
        data->medium_type = buffer[1];
        data->device_specific = buffer[2];
        data->block_descriptor_length = buffer[3];
    }
}

rt_err_t rt_scsi_mode_sense6(struct rt_scsi_device *sdev,
        rt_uint8_t dbd, rt_uint8_t modepage, rt_uint8_t subpage, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(buffer, 0, size);

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.mode_sense6.opcode = RT_SCSI_CMD_MODE_SENSE;
    cmd.op.mode_sense6.config = dbd & 0x18;
    cmd.op.mode_sense6.page_control_code = modepage;
    cmd.op.mode_sense6.subpage_code = subpage;
    cmd.op.mode_sense6.allocation_len = (rt_uint8_t)size;
    cmd.op.mode_sense6.control = 0;
    cmd.op_size = sizeof(cmd.op.mode_sense6);
    cmd.data.ptr = buffer;
    cmd.data.size = size;

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    if (!err)
    {
        data->header_length = 4;
        scsi_mode_sense_fill(data, modepage, buffer, RT_FALSE);
    }

    return err;
}

rt_err_t rt_scsi_mode_sense10(struct rt_scsi_device *sdev,
        rt_uint8_t dbd, rt_uint8_t modepage, rt_uint8_t subpage, void *buffer, rt_size_t size,
        struct rt_scsi_mode_select_data *data)
{
    rt_err_t err;
    struct rt_scsi_cmd cmd;

    rt_memset(buffer, 0, size);

    rt_memset(&cmd, 0, sizeof(cmd));
    cmd.op.mode_sense6.opcode = RT_SCSI_CMD_MODE_SENSE10;
    cmd.op.mode_sense6.config = dbd & 0x18;
    cmd.op.mode_sense6.page_control_code = modepage;
    cmd.op.mode_sense6.subpage_code = subpage;
    cmd.op.mode_sense6.allocation_len = rt_cpu_to_be16(size);
    cmd.op.mode_sense6.control = 0;
    cmd.op_size = sizeof(cmd.op.mode_sense6);
    cmd.data.ptr = buffer;
    cmd.data.size = size;

    err = scsi_transfer(sdev, &cmd) ? : rt_scsi_request_sense(sdev, RT_NULL);

    if (!err)
    {
        data->header_length = 8;
        scsi_mode_sense_fill(data, modepage, buffer, RT_FALSE);
    }

    return err;
}
