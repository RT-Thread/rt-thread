/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author           Notes
 * 2023-11-15       BetMul      first version
 */
#ifndef __DRV_HWTIMER_H__
#define __DRV_HWTIMER_H__

#include <rtconfig.h>

#ifdef RT_USING_HWTIMER
int rt_hw_hwtimer_init(void);
#endif


#endif /* __DRV_HWTIMER_H__ */
