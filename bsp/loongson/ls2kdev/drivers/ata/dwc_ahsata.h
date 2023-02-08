/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     porting to ls2k
 */


#ifndef __DWC_AHSATA_H__
#define __DWC_AHSATA_H__

#define DWCAHSATA_BASE (0x9000000000000000 | 0x400e0000)

int dwc_ahsata_bus_reset(struct rt_device *dev);
int dwc_ahsata_probe(struct rt_device *dev);
int dwc_ahsata_scan(struct rt_device *dev);
int dwc_ahsata_port_status(struct rt_device *dev, int port);
rt_ssize_t dwc_ahsata_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size);
rt_ssize_t dwc_ahsata_write(rt_device_t dev, rt_off_t pos, const void *buffer, rt_size_t size);
rt_err_t dwc_ahsata_control(rt_device_t dev, int cmd, void *args);

#endif
