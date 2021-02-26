
/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-29     WangQiang    the first version
 *
 */

#ifndef DRV_MDIO_H__
#define DRV_MDIO_H__

#include <rtdevice.h>

#include "fsl_enet.h"


rt_mdio_t *rt_hw_mdio_register(void *hw_obj, char *name);

rt_mdio_t *rt_hw_mdio_get(void);

#endif /*DRV_MDIO_H__*/
