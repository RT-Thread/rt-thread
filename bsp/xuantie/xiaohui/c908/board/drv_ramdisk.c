/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "drv.ramdisk"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define RAMDISK_SECTOR_SIZE 512
#define RAMDISK_SIZE        (8 * 1024 * 1024)
#define RAMDISK_SECTOR_NR   (RAMDISK_SIZE / RAMDISK_SECTOR_SIZE)

static struct rt_device _ramdisk_dev;
static rt_uint8_t *_ramdisk_data;

static rt_ssize_t _ramdisk_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    if (pos + size > RAMDISK_SECTOR_NR)
    {
        return 0;
    }
    rt_memcpy(buffer, _ramdisk_data + pos * RAMDISK_SECTOR_SIZE, size * RAMDISK_SECTOR_SIZE);
    return size;
}

static rt_ssize_t _ramdisk_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size)
{
    if (pos + size > RAMDISK_SECTOR_NR)
    {
        return 0;
    }
    rt_memcpy(_ramdisk_data + pos * RAMDISK_SECTOR_SIZE, buffer, size * RAMDISK_SECTOR_SIZE);
    return size;
}

static rt_err_t _ramdisk_control(rt_device_t dev, int cmd, void *args)
{
    if (cmd == RT_DEVICE_CTRL_BLK_GETGEOME)
    {
        struct rt_device_blk_geometry *geometry = (struct rt_device_blk_geometry *)args;

        if (geometry == RT_NULL)
        {
            return -RT_ERROR;
        }
        geometry->bytes_per_sector = RAMDISK_SECTOR_SIZE;
        geometry->block_size = RAMDISK_SECTOR_SIZE;
        geometry->sector_count = RAMDISK_SECTOR_NR;
    }
    return RT_EOK;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops ramdisk_ops = {
    RT_NULL,
    RT_NULL,
    RT_NULL,
    _ramdisk_read,
    _ramdisk_write,
    _ramdisk_control,
};
#endif

int rt_hw_ramdisk_init(void)
{
    rt_device_t dev = &_ramdisk_dev;

    _ramdisk_data = rt_malloc(RAMDISK_SIZE);
    if (_ramdisk_data == RT_NULL)
    {
        LOG_E("no memory for the ramdisk");
        return -RT_ENOMEM;
    }
    rt_memset(_ramdisk_data, 0, RAMDISK_SIZE);

    dev->type = RT_Device_Class_Block;
#ifdef RT_USING_DEVICE_OPS
    dev->ops = &ramdisk_ops;
#else
    dev->read = _ramdisk_read;
    dev->write = _ramdisk_write;
    dev->control = _ramdisk_control;
#endif

    return rt_device_register(dev, "ramdisk0", RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE);
}
INIT_DEVICE_EXPORT(rt_hw_ramdisk_init);
