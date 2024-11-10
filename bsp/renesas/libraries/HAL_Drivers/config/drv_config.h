/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-07-29     KyleChan          first version
 * 2022-12-7      Vandoul           ADD ra4m2
 */

#ifndef __DRV_CONFIG_H__
#define __DRV_CONFIG_H__

#include "board.h"
#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef SOC_SERIES_R7FA6M5
#include "ra6m5/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra6m5/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra6m5/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra6m5/pwm_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra6m5/can_config.h"
#endif
#endif /* SOC_SERIES_R7FA6M5 */

#if defined(SOC_SERIES_R7FA6M3)
#include "ra6m3/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra6m3/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra6m3/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra6m3/pwm_config.h"
#endif

#ifdef BSP_USING_TIM
#include "ra6m3/timer_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra6m3/can_config.h"
#endif
#endif /* SOC_SERIES_R7FA6M3 */

#if defined(SOC_SERIES_R7FA6M4)
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
#endif /* SOC_SERIES_R7FA6M4 */

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
#endif /* SOC_SERIES_R7FA2L1 */

#ifdef SOC_SERIES_R7FA4M2
#include "ra4m2/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra4m2/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra4m2/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra4m2/pwm_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra4m2/can_config.h"
#endif
#endif /* SOC_SERIES_R7FA4M2 */

#ifdef SOC_SERIES_R7FA8M85
#include "ra8/uart_config.h"

#ifdef BSP_USING_PWM
#include "ra8/pwm_config.h"
#endif

#ifdef BSP_USING_ADC
#include "ra8/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra8/dac_config.h"
#endif

#endif /* SOC_SERIES_R7FA8M85 */

#ifdef SOC_SERIES_R9A07G0
#include "rzt/uart_config.h"
#include "rzt/timer_config.h"

#ifdef BSP_USING_PWM
#include "rzt/pwm_config.h"
#endif

#ifdef BSP_USING_ADC
#include "rzt/adc_config.h"
#endif

#endif /* SOC_SERIES_R9A07G0 */

#if defined(SOC_SERIES_R7FA6E2)
#include "ra6e2/uart_config.h"

#ifdef BSP_USING_ADC
#include "ra6e2/adc_config.h"
#endif

#ifdef BSP_USING_DAC
#include "ra6e2/dac_config.h"
#endif

#ifdef BSP_USING_PWM
#include "ra6e2/pwm_config.h"
#endif

#ifdef BSP_USING_TIM
#include "ra6e2/timer_config.h"
#endif

#ifdef BSP_USING_CAN
#include "ra6e2/can_config.h"
#endif
#endif /* SOC_SERIES_R7FA6E2 */

#ifdef __cplusplus
}
#endif

#endif /* __DRV_CONFIG_H__ */
