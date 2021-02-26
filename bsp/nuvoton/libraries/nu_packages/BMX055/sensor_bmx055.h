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

#ifndef __SENSOR_BMX055_H__
#define __SENSOR_BMX055_H__

#include "sensor.h"
#include "bma2x2.h"
#include "bmm050.h"
#include "bmg160.h"

int rt_hw_bmx055_init(const char *name, struct rt_sensor_config *cfg);

#endif /* __SENSOR_BMX055_H__ */
