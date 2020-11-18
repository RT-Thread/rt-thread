/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_timer.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  ADC模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_adc.h"

/***************************************************************
  函数名：ADC_Init
  描  述：初始化ADC模块
  输入值：初始化配置结构体地址
  输出值：无
  返回值：无
 ***************************************************************/
void ADC_Init(ADC_InitStruType * ADC_InitStruct)
{
		ADC->VREFCON.VREF_EN = ENABLE;    //内部VREFP使能
	  ADC->VREFCON.IREF_EN = ENABLE;    //IREF使能位
	  ADC->CON1.VCMBUF_EN = ENABLE;     //ADC共模电压VCM BUF使能
	  ADC ->CON1.VCMBUF_HS = ENABLE;    //ADC共模电压VCM BUF高速模式使能
	  ADC->CON1.HSEN = ENABLE;          //ADC转换速度：高速 
	  ADC->CHS.VDD5_FLAG_EN = DISABLE;        //屏蔽VDD检测控制
	
    ADC->CON1.CLKS = ADC_InitStruct->ADC_ClkS;     //ADCCON1:bit3 ADC时钟源选择
    ADC->CON1.CLKDIV = ADC_InitStruct->ADC_ClkDiv; //ADCCON1:bit2-0 ADC时钟源预分频
    ADC->CON1.VREFP = ADC_InitStruct->ADC_VrefP;   //ADCCON1:bit9-8 ADC正向参考电压选择
    ADC->CON1.SMPS = ADC_InitStruct->ADC_SampS;    //ADCCON1:bit12 ADC采样模式选择
    ADC->CHS.CHS = ADC_InitStruct->ADC_ChS;        //ADCCHS:bit0-3 ADC模拟通道选择
		ADC->CON1.ST = ADC_InitStruct->ST;             //ADCCON1:bit20-16 ADC采样时间选择 ST*2+1个Tadclk 
	  //ADC->VREFCON.VREF_SEL=ADC_InitStruct->VREF_SEL;//内部参考电压选择
	
    ADC->CON1.VREFN = ADC_InitStruct->ADC_VREFN;                    //负向参考电压使能位
    ADC->CON1.VRBUF_EN = ADC_InitStruct->ADC_VRBUF_EN;              //VREF BUF使能位
}


/***************************************************************
  函数名：ADC_Set_CH
  描  述：选择ADC模拟通道
  输入值：通道
  输出值：无
  返回值：无
 ***************************************************************/
void ADC_Set_CH(ADC_TYPE_CHS AdcCH)
{
    ADC->CHS.CHS = AdcCH;
}

/***************************************************************
  函数名：ADC_GetConvValue
  描  述：获取ADC转换结果
  输入值：无
  输出值：无
  返回值：转换值
 ***************************************************************/
uint16_t ADC_GetConvValue(void)
{   
    return ((uint16_t)ADC->DR.DR);
}

/***************************************************************
  函数名：ADC_GetConvStatus
  描  述：获取ADC转换状态
  输入值：无
  输出值：无
  返回值：RESET(完成)/SET(正在转换)
 ***************************************************************/
FlagStatus ADC_GetConvStatus(void)
{
    FlagStatus bitstatus = RESET;

    /* 检测转换状态寄存器 */
    if ((ADC->CON0.TRIG != (uint32_t)RESET))
        bitstatus = SET;                    //正在转换
    else
        bitstatus = RESET;                  //转换完成

    return  bitstatus;
}

/***************************************************************
  函数名：ADC_ACPConfig
  描  述：ADC 自动比较功能初始化
  输入值：ADC_ACP_InitStruct 自动比较功能初始化结构体
  输出值：无
  返回值：SUCCESS 成功
  ERROR 失败
 ***************************************************************/
ErrorStatus ADC_ACPConfig(ADC_ACP_TypeDef *ADC_ACP_InitStruct)
{
    if(ADC_ACP_InitStruct->ACPC_OVER_TIME > ADC_ACPC_OVFL_TIME_MAX
       ||ADC_ACP_InitStruct->ACPC_TIMES > ADC_ACPC_TIMES_MAX
       ||ADC_ACP_InitStruct->ACPC_MIN_TARGET > ADC_ACP_MIN_MAX
       ||ADC_ACP_InitStruct->ACPC_MAX_TARGET > ADC_ACP_MAX_MAX)
    {
        return ERROR;
    }

    if(ADC_ACP_InitStruct->ACP_EN == ENABLE)
    {
        if(ADC->CON1.CLKS == ADC_ClkS_PCLK)
        {
            ADC->ACPC.CLKS = ADC_ACPC_CLKS_PCLK;
        }
        else
        {
            ADC->ACPC.CLKS = ADC_ACPC_CLKS_LRC;
        }

        ADC->ACPC.OVFL_TIME = ADC_ACP_InitStruct ->ACPC_OVER_TIME;
        ADC->ACPC.TIMES = ADC_ACP_InitStruct->ACPC_TIMES;
        ADC->IE.ACPOVIE = ENABLE;

        /* 假设用户将高阀值设置成0(最小值)，我们可以认为其想关闭该功能 */
        if(ADC_ACP_InitStruct ->ACPC_MAX_TARGET ==0x0)
        {
            ADC->IE.ACPMAXIE = DISABLE;
        }
        else
        {
            ADC->ACPCMP.CMP_MAX =ADC_ACP_InitStruct ->ACPC_MAX_TARGET;
            ADC->IE.ACPMAXIE = ENABLE;
        }

        /* 假设用户将低阀值设置成0xfff(最大值)，我们可以认为其想关闭该功能 */
        if(ADC_ACP_InitStruct ->ACPC_MIN_TARGET == 0xfff)
        {
            ADC->IE.ACPMINIE = DISABLE;
        }
        else
        {
            ADC->ACPCMP.CMP_MIN =ADC_ACP_InitStruct ->ACPC_MIN_TARGET;
            ADC->IE.ACPMINIE = ENABLE;
        }

        ADC->CON0.ACP_EN = ENABLE;

    }
    else
    {
        ADC->CON0.ACP_EN = DISABLE;
    }

    return SUCCESS;
}

/***************************************************************
  函数名：ADC_SampStart
  描  述：ADC 采样软件控制-启动函数
  输入值：无
  输出值：无
  返回值：SUCCESS 成功
  ERROR 失败
 ***************************************************************/
ErrorStatus ADC_SoftStart(void)
{
    if(ADC->CON1.SMPS == ADC_SMPS_HARD)
        return ERROR;

    ADC ->CON1.SMPON = SET;
    return SUCCESS;
}

/***************************************************************
  函数名：ADC_SampStop
  描  述：ADC 采样软件控制-停止函数
  输入值：无
  输出值：无
  返回值：SUCCESS 成功
  ERROR 失败
 ***************************************************************/
ErrorStatus ADC_SoftStop(void)
{
    if(ADC->CON1.SMPS == ADC_SMPS_HARD)
        return ERROR;

    ADC->CON1.SMPON = RESET;
    return SUCCESS;
}

/***************************************************************
  函数名：ADC_GetACPMeanValue
  描  述：ADC 获得单次自动比较平均值
  输入值：无
  输出值：无
  返回值：采样数据
 ***************************************************************/
uint16_t ADC_GetACPMeanValue(void)
{
    return ((uint16_t)ADC->ACPMEAN.MEAN_DATA);
}

/***************************************************************
  函数名：ADC_GetACPMINValue
  描  述：ADC 获得单次自动比较平均值
  输入值：无
  输出值：无
  返回值：采样数据
 ***************************************************************/
uint16_t ADC_GetACPMinValue(void)
{
    return ((uint16_t)ADC->ACPCMP.CMP_MIN);
}

/***************************************************************
  函数名：ADC_GetACPMAXValue
  描  述：ADC 获得单次自动比较平均值
  输入值：无
  输出值：无
  返回值：采样数据
 ***************************************************************/
uint16_t ADC_GetACPMaxValue(void)
{
    return ((uint16_t)ADC->ACPCMP.CMP_MAX);
}

/***************************************************************
  函数名：ADC_GetFlagStatus
  描  述：读取ADC标志位状态
  输入值：IFName：ADC中断标志
  输出值：无
  返回值：SET/RESET
 ***************************************************************/
FlagStatus ADC_GetFlagStatus(ADC_TYPE_IF IFName)
{
    FlagStatus bitstatus = RESET;

    /* 检查中断标志位 */
    if (((ADC->IF.Word & IFName) != (uint32_t)RESET))
        bitstatus = SET;                    //转换完成
    else
        bitstatus = RESET;                  //无中断

    return  bitstatus;
}

/***************************************************************
  函数名：ADC_GetITStatus
  描  述：读取ADC中断状态，未使能相应中断时不会返回SET
  输入值：无
  输出值：无
  返回值：SET（中断）/RESET（无中断）
 ***************************************************************/
ITStatus ADC_GetITStatus(ADC_TYPE_IE IEName)
{
    ITStatus bitstatus = RESET;

    /* 检查中断标志位 */
    if (((ADC->IE.Word & IEName) != (uint32_t)RESET))
        bitstatus = SET;                    //转换完成，进中断
    else
        bitstatus = RESET;                  //无中断

    return  bitstatus;
}

/***************************************************************
  函数名：ADC_ClearIFStatus
  描  述：ADC 清除特定类型中断
  输入值：IFName 中断类型选择
  ADC_IF            ADC中断
  ADC_IF_ACPMIN 自动转换低阀值超出中断
  ADC_IF_ACPMAX 自动转换高阀值超出中断
  ADC_IF_ACPOVER    自动转换溢出中断
  输出值：无
  返回值：SUCCESS 成功
  ERROR 失败
 ***************************************************************/
ErrorStatus ADC_ClearIFStatus(ADC_TYPE_IF IFName)
{
    ADC->IF.Word = (uint32_t)IFName;

    return SUCCESS;
}
/***************************************************************
  函数名：ADC_Reset
  描  述：ADC复位
  输入值：无
  输出值：无
  返回值：无
 ***************************************************************/
void ADC_Reset(void)
{
    ADC->CON0.Word = 0x00000030;
    ADC->CON1.Word = 0x00041000;
    ADC->CHS.Word = 0x00000100;
    ADC->IE.Word = 0x00000000;
    ADC->IF.Word = 0x00000000;
    ADC->ACPC.Word = 0x00000000;
    ADC->ACPCMP.Word = 0x0FFF0000;
    ADC->VREFCON.Word = 0x00000000;
}

/*************************END OF FILE**********************/


