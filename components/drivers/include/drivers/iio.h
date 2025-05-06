/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __IIO_H__
#define __IIO_H__

void *rt_iio_channel_get_by_index(struct rt_device *dev, int index, int *out_channel);
void *rt_iio_channel_get_by_name(struct rt_device *dev, const char *name, int *out_channel);

#endif /* __IIO_H__ */
