/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-04-20     tyustli      the first version.
 *
 */
#include <rtthread.h>

#ifdef BSP_USING_LPADC

#if !defined(BSP_USING_LPADC1) && !defined(BSP_USING_LPADC2)
#error "Please define at least one BSP_USING_LPADCx"
#endif

#if (defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#error "Please don't define 'FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL'!"
#endif

#define LOG_TAG             "drv.lpadc"
#include <drv_log.h>
#include "drv_lpadc.h"
#include "fsl_lpadc.h"
#include <rtdevice.h>

lpadc_config_t mLpadcConfigStruct;

#if defined(BSP_USING_LPADC1)
static struct rt_adc_device lpadc1_device;
#endif

#if defined(BSP_USING_LPADC2)
static struct rt_adc_device lpadc2_device;
#endif

#if defined(BSP_LPADC1_USING_DMA)
#include "fsl_edma.h"

volatile bool g_Transfer_Done = false;
AT_NONCACHEABLE_SECTION_ALIGN_INIT(uint32_t adc_result[7], sizeof(uint32_t)) = {0x0,0x0,0x0,0x0,0x0,0x0,0x0};

/* User callback function for EDMA transfer. */
void DMA_Callback(edma_handle_t *handle, void *userData, bool transferDone, uint32_t tcds)
{
    if (transferDone)
    {
        g_Transfer_Done = true;
    }
}
#endif

static rt_err_t imxrt_lp_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    ADC_Type *base;
    /* channel check*/

    if(channel < 4) return -RT_EINVAL;

    base = (ADC_Type *)(device->parent.user_data);
    if( RT_TRUE == enabled )
    {
        LPADC_Enable(base, true);
    } else
    {
        LPADC_Enable(base, false);
    }

    return RT_EOK;
}

static rt_err_t imxrt_lp_adc_convert(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    ADC_Type *base;
    uint32_t data_mask=0xffffffff;
#if defined(BSP_LPADC1_USING_DMA)

#else
    uint8_t i=0;
    uint32_t adc_result[7] = {0x0,0x0,0x0,0x0,0x0,0x0,0x0};  /* conv sequence: A1_4, A1_5(INVALID), A1_6, A1_7, B1_5, B1_6, B1_7 */
    lpadc_conv_result_t mLpadcResultConfigStruct;
#endif

    base = (ADC_Type *)(device->parent.user_data);

    LPADC_DoSoftwareTrigger(base, 1U);
#if defined(BSP_LPADC1_USING_DMA)
	extern edma_handle_t DMA4_CH0_Handle;
    data_mask = 0xffff;
    g_Transfer_Done = false;
    EDMA_StartTransfer(&DMA4_CH0_Handle);
    /* Wait for EDMA transfer finish */
    while (g_Transfer_Done != true)
    {
    }
#else
    for(i=0;i<7;i++)
    {
#if (defined(FSL_FEATURE_LPADC_FIFO_COUNT) && (FSL_FEATURE_LPADC_FIFO_COUNT == 2U))
        while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct, 0U))
#else
        while (!LPADC_GetConvResult(base, &mLpadcResultConfigStruct))
#endif /* FSL_FEATURE_LPADC_FIFO_COUNT */
        {
        }
        adc_result[i] = (mLpadcResultConfigStruct.convValue);
    }
#endif
    switch(channel)
    {
        case 4: *value = adc_result[0] & data_mask;
        break;
        case 5: *value = adc_result[4] & data_mask;
        break;
        case 6: *value = adc_result[2] & data_mask;
        break;
        case 7: *value = adc_result[3] & data_mask;
        break;
        default: *value = 0; return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_uint8_t imxrt_lp_adc_get_resolution(struct rt_adc_device *device)
{
    return 16;
}

static rt_int16_t imxrt_lp_adc_get_vref(struct rt_adc_device *device)
{
    return 1800;
}


static struct rt_adc_ops imxrt_lpadc_ops =
{
    .enabled = imxrt_lp_adc_enabled,
    .convert = imxrt_lp_adc_convert,
    .get_resolution = imxrt_lp_adc_get_resolution,
    .get_vref = imxrt_lp_adc_get_vref,
};

int rt_hw_adc_init(void)
{
    int result = RT_EOK;

#if defined(BSP_USING_LPADC1)
/* on-chip peripherals are initialized in BOARD_InitPeripherals function of board.c */
    result = rt_hw_adc_register(&lpadc1_device, "lpadc1", &imxrt_lpadc_ops, ADC1);
    if (result != RT_EOK)
    {
        LOG_E("register lpadc1 device failed error code = %d\n", result);
    }
#endif
#if defined(BSP_USING_LPADC2)
    LPADC_Init(LPADC1, &mLpadcConfigStruct);
    result = rt_hw_adc_register(&lpadc2_device, "lpadc2", &imxrt_lpadc_ops, LPADC2);
    if (result != RT_EOK)
    {
        LOG_E("register lpadc2 device failed error code = %d\n", result);
    }
#endif
    return result;
}

INIT_DEVICE_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_LPADC */

