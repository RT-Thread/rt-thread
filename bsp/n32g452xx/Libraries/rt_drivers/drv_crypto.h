/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-04-21     wolfJane          first version
 */

#ifndef __DRV_CRYPTO_H_
#define __DRV_CRYPTO_H_

#include <rtthread.h>
#include <rtdevice.h>
#include <n32g45x.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CRC32_PLOY  (0x04C11DB7)
#define CRC16_PLOY  (0x8005)

struct n32_hwcrypto_device
{
    struct rt_hwcrypto_device dev;
    struct rt_mutex mutex;
};

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CRYPTO_H_ */
