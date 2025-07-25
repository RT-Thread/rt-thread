/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author    Notes
 * 2025-05-28     RTT       the first version
 */
#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include "board.h"
#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(SOC_CY8C624ALQI_S2D42) || defined(SOC_CY8C6347BZI_BLD53) || defined(SOC_CY8C6247BZI_D54) || defined(SOC_CY8C6244LQI_S4D92)

#ifdef BSP_USING_ADC
#include "cy8c62/adc_config.h"
#endif

#endif /* SOC_CY8C624ALQI_S2D42 */

#if defined(SOC_XMC7100D_F144K4160AA)

#ifdef BSP_USING_ADC
#include "xmc7100/adc_config.h"
#endif

#endif /* SOC_XMC7100D_F144K4160AA */

#if defined(SOC_XMC7200D_E272K8384AA)

#ifdef BSP_USING_ADC
#include "xmc7200/adc_config.h"
#endif

#endif /* SOC_XMC7200D_E272K8384AA */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CONFIG_H__ */
