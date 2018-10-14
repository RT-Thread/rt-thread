/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-08-25     ChenYong     First version
 */

#ifndef __AF_INET_H__
#define __AF_INET_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SAL_USING_LWIP
/* lwIP protocol family register */
int lwip_inet_init(void);
#endif

#ifdef SAL_USING_AT
/* AT protocol family register */
int at_inet_init(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AF_INET_H__ */
