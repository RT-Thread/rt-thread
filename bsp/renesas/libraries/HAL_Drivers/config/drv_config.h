/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include "board.h"
#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef SOC_SERIES_R7FA6M4
#include "ra6m4/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra6m4/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra6m4/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra6m4/pwm_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra6m4/can_config.h"
#endif
#endif/* SOC_SERIES_R7FA6M4 */

#ifdef SOC_SERIES_R7FA2L1
#include "ra2l1/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra2l1/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra2l1/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra2l1/pwm_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra2l1/can_config.h"
#endif
#endif/* SOC_SERIES_R7FA2L1 */




#ifdef __cplusplus
}
#endif

#endif/* __DRV_CONFIG_H__ */
