/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 * 2026-08-28     FUNMSAN          add N32H47_48x and N32H49x support
 */

#include <board.h>
#include <rtthread.h>

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3) || \
    (defined(SOC_SERIES_N32H47x_48x) && defined(BSP_USING_ADC4))

#if defined(SOC_SERIES_N32H7xx)
#include "n32h7xx_adc.h"
#include "n32h7xx_rcc.h"
#elif defined(SOC_SERIES_N32H47x_48x)
#include "n32h47x_48x_adc.h"
#include "n32h47x_48x_rcc.h"
#elif defined(SOC_SERIES_N32H49x)
#include "n32h49x_adc.h"
#include "n32h49x_rcc.h"
#endif

#include "drv_config.h"

//#define DRV_DEBUG
#define LOG_TAG "drv.adc"
#include <drv_log.h>

#define N32_ADC_POLL_TIMEOUT 1000000U


typedef struct
{
    ADC_Module *ADCx;
    uint32_t AHB_periph;
    void (*EnablePeriphClk)(uint32_t periph, FunctionalState cmd);

    ADC_CTRL3_CKMOD ADC_ClkMode;
    uint32_t Pll_CLK_source;
    uint32_t RCC_ADCPrescaler;
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    uint32_t ADC1M_ClkSource;
    uint32_t ADC1M_ClkPrescaler;
#endif

    uint32_t Rank;
    uint32_t ADC_SampleTime;

    ADC_InitType Init;
} ADC_InitInfo_t;

static ADC_InitInfo_t adc_config[] = {
#ifdef BSP_USING_ADC1
    ADC1_CONFIG,
#endif

#ifdef BSP_USING_ADC2
    ADC2_CONFIG,
#endif

#ifdef BSP_USING_ADC3
    ADC3_CONFIG,
#endif

#if defined(SOC_SERIES_N32H47x_48x) && defined(BSP_USING_ADC4)
    ADC4_CONFIG,
#endif
};


struct n32_adc
{
    ADC_InitInfo_t ADC_Info;
    struct rt_adc_device n32_adc_device;
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    rt_bool_t calibrated;
    rt_bool_t enabled;
#endif
};


static struct n32_adc n32_adc_obj[sizeof(adc_config) / sizeof(adc_config[0])];


static rt_err_t n32_adc_get_channel(rt_int8_t rt_channel, uint32_t *n32_channel)
{
    switch (rt_channel)
    {
    case 0:
        *n32_channel = ADC_CH_0;
        break;
    case 1:
        *n32_channel = ADC_CH_1;
        break;
    case 2:
        *n32_channel = ADC_CH_2;
        break;
    case 3:
        *n32_channel = ADC_CH_3;
        break;
    case 4:
        *n32_channel = ADC_CH_4;
        break;
    case 5:
        *n32_channel = ADC_CH_5;
        break;
    case 6:
        *n32_channel = ADC_CH_6;
        break;
    case 7:
        *n32_channel = ADC_CH_7;
        break;
    case 8:
        *n32_channel = ADC_CH_8;
        break;
    case 9:
        *n32_channel = ADC_CH_9;
        break;
    case 10:
        *n32_channel = ADC_CH_10;
        break;
    case 11:
        *n32_channel = ADC_CH_11;
        break;
    case 12:
        *n32_channel = ADC_CH_12;
        break;
    case 13:
        *n32_channel = ADC_CH_13;
        break;
    case 14:
        *n32_channel = ADC_CH_14;
        break;
    case 15:
        *n32_channel = ADC_CH_15;
        break;
    case 16:
        *n32_channel = ADC_CH_16;
        break;
    case 17:
        *n32_channel = ADC_CH_17;
        break;
    case 18:
        *n32_channel = ADC_CH_18;
        break;
#ifdef ADC_CH_19
    case 19:
        *n32_channel = ADC_CH_19;
        break;
#endif

#if defined(SOC_SERIES_N32H7xx)
#ifdef ADC3_Channel_19_VREFINT
    case RT_ADC_INTERN_CH_VREF:
        *n32_channel = ADC3_Channel_19_VREFINT;
        break;
#endif /* ADC3_Channel_19_VREFINT */

#ifdef ADC3_Channel_17_Battery_DIV4
    case RT_ADC_INTERN_CH_VBAT:
        *n32_channel = ADC3_Channel_17_Battery_DIV4;
        break;
#endif /* ADC3_Channel_17_Battery_DIV4 */

#ifdef ADC3_Channel_18_Temperture_Sensor
    case RT_ADC_INTERN_CH_TEMPER:
        *n32_channel = ADC3_Channel_18_Temperture_Sensor;
        break;
#endif /* ADC3_Channel_18_Temperture_Sensor */
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    case RT_ADC_INTERN_CH_VREF:
        *n32_channel = ADC1_Channel_18_VREFINT;
        break;

    case RT_ADC_INTERN_CH_VBAT:
        *n32_channel = ADC1_Channel_17_Battery_DIV2;
        break;

    case RT_ADC_INTERN_CH_TEMPER:
        *n32_channel = ADC1_Channel_16_Temperture_Sensor;
        break;
#endif

    default:
        return -RT_EINVAL;
    }

    return RT_EOK;
}


static rt_err_t n32_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
#if defined(SOC_SERIES_N32H7xx)
    volatile uint32_t index = 0;
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    rt_uint32_t timeout;
    struct n32_adc *adc_obj;
#endif
    uint32_t ADC_Channel;
    ADC_InitInfo_t *n32_adc_info;

    RT_ASSERT(device != RT_NULL);
    n32_adc_info = device->parent.user_data;
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    adc_obj = rt_container_of(device, struct n32_adc, n32_adc_device);
#endif

    if (enabled)
    {
        if (n32_adc_get_channel(channel, &ADC_Channel) != RT_EOK)
        {
            LOG_E("ADC channel illegal: %d", channel);
            return -RT_EINVAL;
        }

#if defined(SOC_SERIES_N32H7xx)

        /* */
        if ((channel == RT_ADC_INTERN_CH_VREF) || (channel == RT_ADC_INTERN_CH_VBAT) || (channel == RT_ADC_INTERN_CH_TEMPER))
        {
            if (n32_adc_info->ADCx != ADC3)
            {
                LOG_E("%s not supported", device->parent.parent.name);
                return -RT_EINVAL;
            }

            if (channel == RT_ADC_INTERN_CH_VREF)
            {
                /* Enable ADC Vrefint channel */
                ADC_EnableVrefint(ENABLE);
            }
            else if (channel == RT_ADC_INTERN_CH_TEMPER)
            {
                /* Enable ADC temperature sensor */
                ADC_EnableTempSensor(ENABLE);
            }
            else
            {
                /* Enable ADC battery voltage monitor */
                ADC_EnableBatteryVoltageMonitor(ENABLE);
            }
        }

        /* Enable ADC */
        ADC_Enable(n32_adc_info->ADCx, ENABLE);
        /* Check ADC Ready */
        while (ADC_GetFlagStatus(n32_adc_info->ADCx, ADC_FLAG_RDY) == RESET)
        {
        }

        /* Start ADC calibration */
        ADC_CalibrationOperation(n32_adc_info->ADCx);
        /* Check the end of ADCx calibration */
        while (ADC_GetCalibrationStatus(n32_adc_info->ADCx))
        {
        }

        /* Configures ADC regular channel */
        ADC_ConfigRegularChannel(n32_adc_info->ADCx, ADC_Channel, n32_adc_info->Rank, n32_adc_info->ADC_SampleTime);

        for (index = 0U; index < 100U; index++)
        {
            __NOP();
        }

        /* Enable ADC Regular channel conversion */
        ADC_StartRegularConv(n32_adc_info->ADCx);

        while ((n32_adc_info->ADCx->CTRL3 & ADC_CTRL3_RSTART) != ADC_CTRL3_RSTART)
        {
        }

        /* Start ADC Software Conversion */
        ADC_EnableSoftwareStartConv(n32_adc_info->ADCx, ENABLE);
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
        if (channel == RT_ADC_INTERN_CH_TEMPER)
        {
            if (n32_adc_info->ADCx != ADC1)
            {
                LOG_E("%s not supported", device->parent.parent.name);
                return -RT_EINVAL;
            }
            ADC_EnableTempSensorVrefint(ENABLE);
        }
        else if (channel == RT_ADC_INTERN_CH_VREF)
        {
#if defined(SOC_SERIES_N32H47x_48x)
            if ((n32_adc_info->ADCx != ADC1) && (n32_adc_info->ADCx != ADC2))
#elif defined(SOC_SERIES_N32H49x)
            if ((n32_adc_info->ADCx != ADC1) && (n32_adc_info->ADCx != ADC2) &&
                (n32_adc_info->ADCx != ADC3))
#endif
            {
                LOG_E("%s not supported", device->parent.parent.name);
                return -RT_EINVAL;
            }
            ADC_EnableTempSensorVrefint(ENABLE);
        }
        else if (channel == RT_ADC_INTERN_CH_VBAT)
        {
            if (n32_adc_info->ADCx != ADC1)
            {
                LOG_E("%s not supported", device->parent.parent.name);
                return -RT_EINVAL;
            }
            ADC_EnableBatteryVoltageMonitor(n32_adc_info->ADCx, ENABLE);
        }

        if (adc_obj->enabled == RT_FALSE)
        {
            /* RDY/PDRDY are sticky write-one-to-clear flags. Clear the status
             * from the previous power cycle before waiting for a new RDY. */
            ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_RDY);
            ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_PDRDY);

            ADC_Enable(n32_adc_info->ADCx, ENABLE);
            timeout = N32_ADC_POLL_TIMEOUT;
            while (ADC_GetFlagStatus(n32_adc_info->ADCx, ADC_FLAG_RDY) == RESET)
            {
                if (timeout-- == 0U)
                {
                    ADC_Enable(n32_adc_info->ADCx, DISABLE);
                    LOG_E("%s ready timeout", device->parent.parent.name);
                    return -RT_ETIMEOUT;
                }
            }

            /* The calibration factor is retained while the ADC is disabled. Re-running
             * calibration on every RT_ADC_CMD_ENABLE can leave a new calibration in
             * progress because the vendor status API also checks the old factor. */
            if (adc_obj->calibrated == RT_FALSE)
            {
                ADC_CalibrationOperation(n32_adc_info->ADCx, ADC_CALIBRATION_SINGLE_MODE);
                timeout = N32_ADC_POLL_TIMEOUT;
                while (ADC_GetCalibrationStatus(n32_adc_info->ADCx, ADC_CALIBRATION_SINGLE_MODE) != RESET)
                {
                    if (timeout-- == 0U)
                    {
                        ADC_Enable(n32_adc_info->ADCx, DISABLE);
                        LOG_E("%s calibration timeout", device->parent.parent.name);
                        return -RT_ETIMEOUT;
                    }
                }
                adc_obj->calibrated = RT_TRUE;
            }

            adc_obj->enabled = RT_TRUE;
        }

        ADC_ConfigRegularChannel(n32_adc_info->ADCx, ADC_Channel, n32_adc_info->Rank, n32_adc_info->ADC_SampleTime);
#endif
    }
    else
    {
#if defined(SOC_SERIES_N32H7xx)
        if (channel == RT_ADC_INTERN_CH_VREF)
        {
            /* Disable ADC Vrefint channel */
            ADC_EnableVrefint(DISABLE);
        }
        else if (channel == RT_ADC_INTERN_CH_VBAT)
        {
            /* Disable ADC battery voltage monitor */
            ADC_EnableBatteryVoltageMonitor(DISABLE);
        }
        else
        {
            /* Disable ADC temperature sensor */
            ADC_EnableTempSensor(DISABLE);
        }

        /* Disable ADC */
        ADC_Enable(n32_adc_info->ADCx, DISABLE);
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
        if ((channel == RT_ADC_INTERN_CH_VREF) || (channel == RT_ADC_INTERN_CH_TEMPER))
        {
            ADC_EnableTempSensorVrefint(DISABLE);
        }
        else if (channel == RT_ADC_INTERN_CH_VBAT)
        {
            ADC_EnableBatteryVoltageMonitor(n32_adc_info->ADCx, DISABLE);
        }

        if (adc_obj->enabled == RT_TRUE)
        {
            ADC_Enable(n32_adc_info->ADCx, DISABLE);
            adc_obj->enabled = RT_FALSE;

            /* ADC_Enable(DISABLE) clears ON directly. PDRDY is not asserted in
             * every power mode, so it must not be a mandatory completion event. */
            ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_RDY);
            ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_PDRDY);
        }
#endif
    }

    return RT_EOK;
}


static rt_err_t n32_adc_get_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    uint16_t Convert_Value = 0;
    ADC_InitInfo_t *n32_adc_info;
#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    rt_uint32_t timeout;
#endif

    RT_ASSERT(device != RT_NULL);
    RT_ASSERT(value != RT_NULL);

    n32_adc_info = device->parent.user_data;

#if defined(SOC_SERIES_N32H7xx)
    /* Wait for the ADC to convert */
    while (ADC_GetFlagStatus(n32_adc_info->ADCx, ADC_FLAG_ENDC) != SET)
    {
    }

    /* Clear ADC Flag */
    ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_ENDC);
    ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_STR);

    /* Get ADC value */
    Convert_Value = ADC_GetDat(n32_adc_info->ADCx);

    if (channel == RT_ADC_INTERN_CH_VBAT)
    {
        Convert_Value *= 4U;
    }
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    /* Start one software conversion for the selected regular channel */
    ADC_EnableSoftwareStartConv(n32_adc_info->ADCx, ENABLE);

    timeout = N32_ADC_POLL_TIMEOUT;
    while (ADC_GetFlagStatus(n32_adc_info->ADCx, ADC_FLAG_ENDC) != SET)
    {
        if (timeout-- == 0U)
        {
            LOG_E("%s conversion timeout", device->parent.parent.name);
            return -RT_ETIMEOUT;
        }
    }

    ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_ENDC);
    ADC_ClearFlag(n32_adc_info->ADCx, ADC_FLAG_STR);
    Convert_Value = ADC_GetDat(n32_adc_info->ADCx);

    if (channel == RT_ADC_INTERN_CH_VBAT)
    {
        Convert_Value *= 2U;
    }
#endif

    *value = Convert_Value;

    return RT_EOK;
}


static rt_uint8_t n32_adc_get_resolution(struct rt_adc_device *device)
{
    rt_uint8_t Resolution = 0;
    ADC_InitInfo_t *n32_adc_info = device->parent.user_data;

    RT_ASSERT(device != RT_NULL);

    switch (n32_adc_info->Init.Resolution)
    {
#if defined(SOC_SERIES_N32H7xx)
    case ADC_DATA_RES_12BIT:
    {
        Resolution = 12;
        break;
    }

    case ADC_DATA_RES_10BIT:
    {
        Resolution = 10;
        break;
    }
#elif defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
    case ADC_DATA_RES_12BIT:
    {
        Resolution = 12;
        break;
    }

    case ADC_DATA_RES_10BIT:
    {
        Resolution = 10;
        break;
    }

    case ADC_DATA_RES_8BIT:
    {
        Resolution = 8;
        break;
    }

    case ADC_DATA_RES_6BIT:
    {
        Resolution = 6;
        break;
    }
#endif
    default:
        break;
    }

    return Resolution;
}


static rt_int16_t n32_adc_get_vref(struct rt_adc_device *device)
{
    return 3300;
}


static const struct rt_adc_ops n32_adc_ops = {
    .enabled = n32_adc_enabled,
    .convert = n32_adc_get_value,
    .get_resolution = n32_adc_get_resolution,
    .get_vref = n32_adc_get_vref,
};


static int n32_adc_init(void)
{
    int result = RT_EOK;
    /* save adc name */
    char name_buf[5] = { 'a', 'd', 'c', '0', 0 };
    int i = 0;

    for (i = 0; i < sizeof(adc_config) / sizeof(adc_config[0]); i++)
    {
        /* ADC init */
        name_buf[3] = '0';
        n32_adc_obj[i].ADC_Info = adc_config[i];
#if defined(ADC1)
        if (n32_adc_obj[i].ADC_Info.ADCx == ADC1)
        {
            name_buf[3] = '1';
        }
#endif
#if defined(ADC2)
        if (n32_adc_obj[i].ADC_Info.ADCx == ADC2)
        {
            name_buf[3] = '2';
        }
#endif
#if defined(ADC3)
        if (n32_adc_obj[i].ADC_Info.ADCx == ADC3)
        {
            name_buf[3] = '3';
        }
#endif
#if defined(ADC4)
        if (n32_adc_obj[i].ADC_Info.ADCx == ADC4)
        {
            name_buf[3] = '4';
        }
#endif

#if defined(SOC_SERIES_N32H47x_48x) || defined(SOC_SERIES_N32H49x)
        n32_adc_obj[i].ADC_Info.EnablePeriphClk(n32_adc_obj[i].ADC_Info.AHB_periph, ENABLE);
        ADC_ConfigClk(n32_adc_obj[i].ADC_Info.ADC_ClkMode, n32_adc_obj[i].ADC_Info.RCC_ADCPrescaler);
        RCC_ConfigAdc1mClk(n32_adc_obj[i].ADC_Info.ADC1M_ClkSource,
                           n32_adc_obj[i].ADC_Info.ADC1M_ClkPrescaler);
#endif

        ADC_Init(n32_adc_obj[i].ADC_Info.ADCx, &n32_adc_obj[i].ADC_Info.Init);

        /* register ADC device */
        if (rt_hw_adc_register(&n32_adc_obj[i].n32_adc_device, name_buf, &n32_adc_ops, &n32_adc_obj[i].ADC_Info) == RT_EOK)
        {
            LOG_D("%s init success", name_buf);
        }
        else
        {
            LOG_E("%s register failed", name_buf);
            result = -RT_ERROR;
        }
    }

    return result;
}
INIT_BOARD_EXPORT(n32_adc_init);

#endif /* BSP_USING_ADC */
