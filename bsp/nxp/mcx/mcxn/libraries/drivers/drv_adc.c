/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-05-16     shelton      first version
 */

#include "drv_adc.h"
#include "fsl_lpadc.h"
#include "fsl_spc.h"
#include "fsl_common.h"

#if defined(BSP_USING_ADC0) || defined(BSP_USING_ADC1)

#define DEFAULT_HW_AVG          (kLPADC_HardwareAverageCount4)
#define DEFAULT_SAMPLE_TIME     (kLPADC_SampleTimeADCK7)


/* by default: cmd = chl+1 */
static uint8_t adc_chl2cmd[] =  {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
static uint8_t adc_cmd2trig[] = {0, 1, 2 ,3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};

struct mcx_adc
{
    struct rt_adc_device        mcx_adc_device;
    ADC_Type                   *adc_base;
    clock_attach_id_t           clock_attach_id;
    clock_div_name_t            clock_div_name;
    uint8_t                     clock_div;
    uint8_t                     referenceVoltageSource; /* 00, VREFH reference pin, 01, ANA_7(VREFI/VREFO) pin, 10, VDDA supply pin */
    char *name;
};

static struct mcx_adc mcx_adc_obj[] =
{
#ifdef BSP_USING_ADC0
    {
        .adc_base = ADC0,
        .clock_attach_id = kCLK_IN_to_ADC0,
        .clock_div_name = kCLOCK_DivAdc0Clk,
        .clock_div = 2,
        .referenceVoltageSource = 0,
        .name = "adc0",
    },
#endif

};

static rt_err_t at32_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    struct mcx_adc *adc = (struct mcx_adc *)device->parent.user_data;

    lpadc_conv_command_config_t cmd_cfg;
    LPADC_GetDefaultConvCommandConfig(&cmd_cfg);

    cmd_cfg.channelNumber = channel;
    cmd_cfg.conversionResolutionMode = kLPADC_ConversionResolutionHigh;
    cmd_cfg.hardwareAverageMode = DEFAULT_HW_AVG;
    cmd_cfg.loopCount = 0;
    cmd_cfg.sampleTimeMode = DEFAULT_SAMPLE_TIME;
/*
    kLPADC_SampleChannelSingleEndSideA = 0U,
    kLPADC_SampleChannelSingleEndSideB = 1U,
    kLPADC_SampleChannelDiffBothSide = 2U,
    kLPADC_SampleChannelDualSingleEndBothSide =
*/
    cmd_cfg.sampleChannelMode = kLPADC_SampleChannelSingleEndSideA;
    LPADC_SetConvCommandConfig(adc->adc_base, adc_chl2cmd[channel], &cmd_cfg);

    lpadc_conv_trigger_config_t trig_config;
    LPADC_GetDefaultConvTriggerConfig(&trig_config);
    trig_config.targetCommandId       = adc_chl2cmd[channel];
    trig_config.enableHardwareTrigger = false;
    LPADC_SetConvTriggerConfig(adc->adc_base, adc_cmd2trig[trig_config.targetCommandId], &trig_config); /* Configurate the trigger0. */

    return RT_EOK;
}

static rt_err_t at32_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    struct mcx_adc *adc = (struct mcx_adc *)device->parent.user_data;

    lpadc_conv_result_t mLpadcResultConfigStruct;

    LPADC_DoSoftwareTrigger(adc->adc_base, 1<<(adc_cmd2trig[adc_chl2cmd[channel]])); /* 1U is trigger0 mask. */
    while (!LPADC_GetConvResult(adc->adc_base, &mLpadcResultConfigStruct, 0))
    {
    }


    *value = mLpadcResultConfigStruct.convValue;
    return RT_EOK;
}

static const struct rt_adc_ops mcx_adc_ops =
{
    .enabled = at32_adc_enabled,
    .convert = at32_get_adc_value,
};

static int rt_hw_adc_init(void)
{
    int result = RT_EOK;
    int i = 0;

    /* Enable VREF */
    SPC0->ACTIVE_CFG1 |= 0xFFFFFFFF;
    SPC_SetActiveModeBandgapModeConfig(SPC0, kSPC_BandgapEnabledBufferEnabled);

    for (i = 0; i < sizeof(mcx_adc_obj) / sizeof(mcx_adc_obj[0]); i++)
    {
        CLOCK_SetClkDiv(mcx_adc_obj[i].clock_div_name, mcx_adc_obj[i].clock_div);
        CLOCK_AttachClk(mcx_adc_obj[i].clock_attach_id);

        lpadc_config_t adc_config;
        LPADC_GetDefaultConfig(&adc_config);
        adc_config.enableAnalogPreliminary = true;
        adc_config.referenceVoltageSource = mcx_adc_obj[i].referenceVoltageSource;
        adc_config.conversionAverageMode = kLPADC_ConversionAverage128; /* this is for calibartion avg mode */
        adc_config.powerLevelMode = kLPADC_PowerLevelAlt4;
        adc_config.enableConvPause       = false;
        adc_config.convPauseDelay        = 0;

        LPADC_Init(mcx_adc_obj[i].adc_base, &adc_config);
        LPADC_DoOffsetCalibration(mcx_adc_obj[i].adc_base);
        LPADC_DoAutoCalibration(mcx_adc_obj[i].adc_base);

        rt_hw_adc_register(&mcx_adc_obj[i].mcx_adc_device, mcx_adc_obj[i].name, &mcx_adc_ops, &mcx_adc_obj[i]);
    }

    return result;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);

#endif /* BSP_USING_ADC */
