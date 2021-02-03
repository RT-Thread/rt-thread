/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		zf_vadc
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
 
#include "Vadc/Adc/IfxVadc_Adc.h"
#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"


#define ADC_SAMPLE_FREQUENCY	10000000//最大10Mhz

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC初始化
//  @param      adcn            选择ADC模块(ADC_0、ADC_1、ADC_2)
//  @param      ch              选择ADC通道
//  @return     void
//  Sample usage:               adc_init(ADC_0, ADC0_CH0_A0);
//-------------------------------------------------------------------------------------------------------------------
void adc_init(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn)
{
	static uint8 mudule_init_flag = 0;
	IfxVadc_Adc vadc;
	IfxVadc_Adc_Group adcGroup;
    IfxVadc_Adc_Config adcConfig;

	IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

	if(!mudule_init_flag)
	{
		mudule_init_flag = 1;
		IfxVadc_Adc_initModule(&vadc, &adcConfig);

	}
	else
	{
		vadc.vadc = adcConfig.vadc;
	}

	IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &vadc);

    adcGroupConfig.groupId = (IfxVadc_GroupId)vadc_n;//IfxVadc_GroupId_0;
    adcGroupConfig.master  = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;
    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;
    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;
	adcGroupConfig.inputClass[0].resolution = IfxVadc_ChannelResolution_12bit;
	adcGroupConfig.inputClass[0].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;
	adcGroupConfig.inputClass[1].resolution = IfxVadc_ChannelResolution_12bit;
	adcGroupConfig.inputClass[1].sampleTime = 1.0f/ADC_SAMPLE_FREQUENCY;

    IfxVadc_Adc_initGroup(&adcGroup, &adcGroupConfig);

	IfxVadc_Adc_ChannelConfig adcChannelConfig;
	IfxVadc_Adc_Channel       adcChannel;
	IfxVadc_Adc_initChannelConfig(&adcChannelConfig, &adcGroup);

	adcChannelConfig.channelId         = (IfxVadc_ChannelId)(vadc_chn%16);
	adcChannelConfig.resultRegister    = (IfxVadc_ChannelResult)(vadc_chn%16);
	adcChannelConfig.backgroundChannel = TRUE;

	IfxVadc_Adc_initChannel(&adcChannel, &adcChannelConfig);

	unsigned channels = (1 << adcChannelConfig.channelId);
	unsigned mask     = channels;
	IfxVadc_Adc_setBackgroundScan(&vadc, &adcGroup, channels, mask);

	IfxVadc_Adc_startBackgroundScan(&vadc);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC转换一次
//  @param      adcn            选择ADC模块(ADC_0、ADC_1、ADC_2)
//  @param      ch              选择ADC通道
//  @return     void
//  Sample usage:               adc_convert(ADC_0, ADC0_CH0_A0, ADC_12BIT);
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_convert(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res)
{
	Ifx_VADC_RES result;
	uint8 temp;
	do
	{
		result = IfxVadc_getResult(&MODULE_VADC.G[vadc_n], vadc_chn%16);
	} while (!result.B.VF);

	temp = 4 - (vadc_res * 2);
	return((result.U&0x0fff)>>temp);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ADC均值滤波
//  @param      adcn            选择ADC模块(ADC_0、ADC_1、ADC_2)
//  @param      ch              选择ADC通道
//  @param      count           均值滤波次数
//  @return     void
//  Sample usage:               adc_mean_filter(ADC_0, ADC0_CH0_A0, ADC_12BIT, 5);//采集5次 然后返回平均值
//-------------------------------------------------------------------------------------------------------------------
uint16 adc_mean_filter(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res, uint8 count)
{
    uint8 i;
    uint32 sum;

    ZF_ASSERT(count);//断言次数不能为0

    sum = 0;
    for(i=0; i<count; i++)
    {
        sum += adc_convert(vadc_n, vadc_chn, vadc_res);
    }

    sum = sum/count;
    return (uint16)sum;
}
