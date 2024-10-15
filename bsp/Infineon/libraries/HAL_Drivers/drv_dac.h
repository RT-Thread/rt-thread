/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                 Notes
 * 2022-07-28     rtthread qiu       first version
 */
#ifndef __DRV__DAC_H__
#define __DRV__DAC_H__
#include "rtconfig.h"
#include "cycfg.h"
#include <rtthread.h>
#include "cy_csdidac.h"
#include "cycfg_peripherals.h"

static const cy_stc_csdidac_pin_t CSDIDAC_csdidac_a_pin =
{
    .ioPcPtr = GPIO_PRT10,
    .pin = 0u,
};
static const cy_stc_csdidac_pin_t CSDIDAC_csdidac_b_pin =
{
    .ioPcPtr = GPIO_PRT10,
    .pin = 0u,
};

const cy_stc_csdidac_config_t CSDIDAC_csdidac_config =
{
    .base = CSD0,
    .csdCxtPtr = &cy_csd_0_context,
    .configA = CY_CSDIDAC_GPIO,
    .configB = CY_CSDIDAC_GPIO,
    .ptrPinA = (const cy_stc_csdidac_pin_t *)&CSDIDAC_csdidac_a_pin,
    .ptrPinB = (const cy_stc_csdidac_pin_t *)&CSDIDAC_csdidac_b_pin,
    .cpuClk = 100000000u,
    .csdInitTime = 25u,
};

#ifdef BSP_USING_DAC1
#ifndef DAC1_CONFIG
#define DAC1_CONFIG     \
    {                   \
        .name = "dac1", \
    }
#endif /* DAC1_CONFIG */
#endif /*BSP_USING_DAC2*/

#ifdef BSP_USING_DAC2
#ifndef DAC2_CONFIG
#define DAC2_CONFIG     \
    {                   \
        .name = "dac2", \
    }
#endif /* DAC2_CONFIG */
#endif /*BSP_USING_DAC2*/

#endif /*__DRV__DAC_H__*/
