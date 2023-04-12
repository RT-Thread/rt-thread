/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author       Notes
* 2021-4-7        Wayne        First version
*
******************************************************************************/

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <rtthread.h>
#include "nu_adc.h"

#if defined(BSP_USING_ADC_TOUCH)
    #include <rtdevice.h>
#endif

typedef enum
{
    eAdc_MF, //0
    eAdc_KPEF, //1
    eAdc_PEDEF, //2
    eAdc_KPUEF, //3
    eAdc_PEUEF, //4
    eAdc_TF = 8, //8
    eAdc_ZF, //9
    eAdc_NACF, //10
    eAdc_VBF, //11
    eAdc_KPCF, //12
    eAdc_SELFTF, //13
    eAdc_INTKP = 16, //16
    eAdc_INTTC, //17
    eAdc_ISR_CNT //18
} E_ADC_ISR_EVENT;

typedef enum
{
    eAdc_WKPEF,
    eAdc_WPEDEF,
    eAdc_WKISR_CNT
} E_ADC_WKISR_EVENT;

typedef struct
{
    ADC_CALLBACK cbfunc;
    uint32_t private_data;
} nu_adc_cb;

typedef nu_adc_cb *nu_adc_cb_t;

#if defined(BSP_USING_ADC_TOUCH)
    void nu_adc_touch_detect(rt_bool_t bStartDetect);
    int32_t nu_adc_touch_read_xyz(uint32_t *bufX, uint32_t *bufY, uint32_t *bufZ0, uint32_t *bufZ1, int32_t dataCnt);
    rt_err_t nu_adc_touch_enable(rt_touch_t psRtTouch);
    rt_err_t nu_adc_touch_disable(void);
#endif

#endif /* __DRV_ADC_H__ */
