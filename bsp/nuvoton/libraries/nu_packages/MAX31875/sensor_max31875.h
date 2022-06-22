/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2020-1-16       Wayne        First version
*
******************************************************************************/

#ifndef __SENSOR_MAX31875_H__
#define __SENSOR_MAX31875_H__

#include "sensor.h"
#include "max31875_c.h"

int rt_hw_max31875_init(const char *name, struct rt_sensor_config *cfg);

#endif /* __SENSOR_MAX31875_H__ */
