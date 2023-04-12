/**************************************************************************//**
*
* @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2022-2-21       Wayne        First version
*
******************************************************************************/

#ifndef __TOUCH_SW_H__
#define __TOUCH_SW_H__

#include <rtthread.h>
#include <rtdevice.h>

typedef enum
{
    evXL,  //X-
    evYU,  //Y-
    evXR,  //X+
    evYD,  //Y+
    evTOUCH_PIN_CNT
} E_TOUCH_PIN;

typedef struct
{
    char            *adc_name;
    rt_device_t      adc;
    int i32ADCChnYU;
    int i32ADCChnXR;
    rt_touch_t       psRtTouch;

    rt_base_t        pin[evTOUCH_PIN_CNT];
    void (*switch_to_analog)(rt_base_t pin);
    void (*switch_to_digital)(rt_base_t pin);
} S_TOUCH_SW;

rt_err_t nu_adc_touch_sw_register(S_TOUCH_SW *psTouchSW);

#endif /* __TOUCH_SW_H__ */
