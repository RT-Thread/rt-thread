/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-19     lizhirui     first version
 */

#ifndef __ATA_DEBUG_H__
#define __ATA_DEBUG_H__
//#define ATA_DEBUG
#include <rtthread.h>
#ifdef ATA_DEBUG
#define debug rt_kprintf
#else
#define debug(...)
#endif
#endif
