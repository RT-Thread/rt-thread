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
#ifndef __LIBADC_H__
#define __LIBADC_H__

#include "ES8P508x.h"
#include "type.h"

/* 内部参考电压选择 */
typedef enum {
	ADC_VREF_SEL_2_0 = 0,	/* 内部参考电压2.048v*/
	ADC_VREF_SEL_1_6 = 1,	/* 内部参考电压1.6v*/
	ADC_VREF_SEL_MAX = 1,
}ADC_TYPE_VREF_SEL;

/* ADC时钟源选择 */
typedef enum
{
    ADC_ClkS_PCLK = 0x0 ,   //时钟：PCLK
    ADC_ClkS_PLL = 0x1 ,    //时钟：PLL
    ADC_ClkS_32K = 0x2 ,    //时钟：ADCCLK(32KHZ)
}ADC_TYPE_CLKS;

/* ADC时钟源预分频 */
typedef enum
{
    ADC_ClkDiv_1 = 0x0 ,   //预分频：1:1
    ADC_ClkDiv_2 = 0x1 ,   //预分频：1:2
    ADC_ClkDiv_4 = 0x2 ,   //预分频：1:4
    ADC_ClkDiv_8 = 0x3 ,   //预分频：1:8
    ADC_ClkDiv_16 = 0x4 ,  //预分频：1:16
    ADC_ClkDiv_32 = 0x5 ,  //预分频：1:32
    ADC_ClkDiv_64 = 0x6 ,  //预分频：1:64
    ADC_ClkDiv_256 = 0x7 , //预分频：1:256
}ADC_TYPE_CLKDIV;

/* 正向参考电压选择 */
typedef enum
{
    ADC_VrefP_Vcc = 0x0 ,    //正向参考电压：VDD电压
    ADC_VrefP_Exter = 0x3 ,  //正向参考电压：外部参考电压
}ADC_TYPE_VREFP;

/* 采样模式选择 */
typedef enum
{
    ADC_SMPS_SOFT = 0,      /* 软件控制 */
    ADC_SMPS_HARD = 1,  /* 硬件控制 */
}ADC_TYPE_SMPS;


/* 转换速度选择 */
typedef enum
{
    ADC_ConvSpeed_Low = 0x0 ,  //AD转换速度：低速
    ADC_ConvSpeed_High = 0x1 , //AD转换速度：高速
}ADC_TYPE_HSEN;

/* ADC通道选择 */
typedef enum
{
    ADC_CHS_AIN0 = 0,       /* 通道 0 */
    ADC_CHS_AIN1 = 1,       /* 通道 1 */
    ADC_CHS_AIN2 = 2,       /* 通道 2 */
    ADC_CHS_AIN3 = 3,       /* 通道 3 */
    ADC_CHS_AIN4 = 4,       /* 通道 4 */
    ADC_CHS_AIN5 = 5,       /* 通道 5 */
    ADC_CHS_AIN6 = 6,       /* 通道 6 */
    ADC_CHS_AIN7 = 7,       /* 通道 7 */
    ADC_CHS_AIN8 = 8,       /* 通道 8 */
    ADC_CHS_AIN9 = 9,       /* 通道 9 */
    ADC_CHS_AIN10 = 10,     /* 通道 10 */
    ADC_CHS_AIN11 = 11,     /* 通道 11 */
    ADC_CHS_AIN12 = 12,     /* 通道 12 */
    ADC_CHS_AIN13 = 13,     /* 通道 13 */
    ADC_CHS_AIN14 = 14,     /* 通道 14 */
    ADC_CHS_AIN15 = 15,     /* 通道 15 */
}ADC_TYPE_CHS;

/*ADC core功耗选择位*/
typedef enum
{
    ADC_LP_86ua = 2,     //ADC Core 功耗为86，推荐使用
    ADC_LP_215ua = 0,    //ADC Core 功耗为215uA
    ADC_LP_120ua = 1,    //ADC Core 功耗为120uA
    ADC_LP_70ua = 3,    //ADC Core 功耗为70uA
}ADC_TYPE_BUFLP;

/*ADC 输入buff功耗选择位*/
typedef enum
{
    ADC_BUFF_0ua = 0,     //ADC 输入buff功耗为0uA，推荐使用
    ADC_BUFF_34ua = 1,    //ADC 输入buff功耗为34uA
    ADC_BUFF_95ua = 2,     //ADC 输入buff功耗为95uA
}ADC_TYPE_BUFEN;

/* ADC IF 状态 */
typedef enum 
{
    ADC_IF = 0x01,
    ADC_IF_ACPMIN = 0x02,
    ADC_IF_ACPMAX =0x04,
    ADC_IF_ACPOVER = 0x08,
}ADC_TYPE_IF;

/* ADC IE 状态 */
typedef enum 
{
    ADC_IE = 0x01,
    ADC_IE_ACPMIN = 0x02,
    ADC_IE_ACPMAX =0x04,
    ADC_IE_ACPOVER = 0x08,
}ADC_TYPE_IE;

/* ADC初始化配置结构体定义 */
typedef struct
{
    ADC_TYPE_CLKS  ADC_ClkS;      //ADCCON1:bit3 ADC时钟源选择 
    ADC_TYPE_CLKDIV  ADC_ClkDiv;  //ADCCON1:bit2-0 ADC时钟源预分频 
    ADC_TYPE_VREFP  ADC_VrefP;    //ADCCON1:bit9-8 ADC正向参考电压选择
    ADC_TYPE_SMPS  ADC_SampS;     //ADCCON1:bit12 ADC采样模式选择
    ADC_TYPE_CHS  ADC_ChS;        //ADCCHS:bit0-3 ADC模拟通道选择
		//ADC_TYPE_VREF_SEL VREF_SEL;	  //参考电压选择
		uint8_t ST;							      //硬件采样时间 (当控制模式为硬件时设置) 0~31
    TYPE_FUNCEN ADC_VREFN;        //负向参考电压选择位
    TYPE_FUNCEN ADC_VRBUF_EN;
}ADC_InitStruType;

/* 自动比较低阀值 选择*/
typedef enum
{
    ADC_ACP_MIN_MIN = 0x0,      /* 容许的最小低阀值*/
    ADC_ACP_MIN_MAX = 0xfff,    /* 容许的最大低阀值*/
}ADC_TYPE_ACP_MIN;

/* 自动比较高阀值 选择*/
typedef enum
{
    ADC_ACP_MAX_MIN = 0x0,  /* 容许的最小高阀值*/
    ADC_ACP_MAX_MAX = 0xfff,    /* 容许的最大高阀值*/
}ADC_TYPE_ACP_MAX;

/* 每次自动转换比较溢出时间选择 */
typedef enum
{
    ADC_ACPC_OVFL_TIME_MAX = 0x9c3, /* 容许的最大溢出时间 */
}ADC_TYPE_ACPC_OVFL_TIME;

/* 自动转换比较次数 */
typedef enum
{
    ADC_ACPC_TIMES_1 = 0,   /* 1次 */
    ADC_ACPC_TIMES_2 = 1,   /* 2次 */
    ADC_ACPC_TIMES_4 = 2,   /* 4次 */
    ADC_ACPC_TIMES_8 = 3,   /* 8次 */
    ADC_ACPC_TIMES_MAX = 3,
}ADC_TYPE_ACPC_TIMES;

/* ACP溢出时钟的时钟源 */
typedef enum
{
    ADC_ACPC_CLKS_PCLK = 0,              /* PCLK */
    ADC_ACPC_CLKS_LRC = 1,               /* LRC(32KHz) */
}ADC_TYPE_ACPC_CLKS;

typedef FuncState ADC_TYPE_CHOP_EN1, ADC_TYPE_CHOP_EN;
typedef FuncState ADC_TYPE_VREF_EN,ADC_TYPE_IREF_EN;
typedef FuncState ADC_TYPE_EN,ADC_TYPE_ACP_EN;

/* 自动比较功能初始化结构体*/
typedef struct
{
    ADC_TYPE_ACP_EN ACP_EN;                 /* 自动比较功能使能位*/
    uint16_t ACPC_OVER_TIME;                /* 单次自动比较溢出时间(即使不想设置请设置成0) 0~0x9c3 */
    ADC_TYPE_ACPC_TIMES ACPC_TIMES;         /* 单次自动比较次数(优先级高于溢出时间) */
    uint16_t ACPC_MIN_TARGET;               /* 平均值最低阀值 (设置0xfff关闭) 0~0xfff */
    uint16_t ACPC_MAX_TARGET;               /* 平均值最高阀值 (设置0x0关闭)     0~0xfff */
}ADC_ACP_TypeDef;

/************ADC模块宏定义***********/
/* ADC使能控制 */
#define ADC_Enable()  (ADC->CON0.EN = 0x1)
#define ADC_Disable() (ADC->CON0.EN = 0x0)

/* 自动比较功能使能*/
#define ADC_ACP_Enable() (ADC->CON0.ACP_EN = 1)
#define ADC_ACP_Disable() (ADC->CON0.ACP_EN = 0)

/* ADC开始转换 */
#define ADC_Start() (ADC->CON0.TRIG = 0x1)

/* ADC采样软件控制 */
#define ADC_SampStart() (ADC->CON1.SMPON = 0x1)
#define ADC_SampStop()  (ADC->CON1.SMPON = 0x0)

/* ADC VDD检测控制 */
#define ADC_VDD5_FLAG_Enable() (ADC->CHS.VDD5_FLAG_EN = 0x1)
#define ADC_VDD5_FLAG_Disable()  (ADC->CHS.VDD5_FLAG_EN = 0x0)

/* ADC中断使能控制 */
#define ADC_IE_Enable()  (ADC->IE.IE = 0x1)
#define ADC_IE_Disable() (ADC->IE.IE = 0x0)

#define ADC_ACPMINIE_Enable() (ADC->IE.ACPMINIE = 1)
#define ADC_ACPMINIE_Disable() (ADC->IE.ACPMINIE = 0)

#define ADC_ACPMAXIE_Enable() (ADC->IE.ACPMAXIE = 1)
#define ADC_ACPMAXIE_Disable() (ADC->IE.ACPMAXIE = 0)

#define ADC_ACPOVIE_Enable() (ADC->IE.ACPOVIE = 1)
#define ADC_ACPOVIE_Disable() (ADC->IE.ACPOVIE = 0)

/************ADC模块函数声明***********/
void ADC_Init(ADC_InitStruType * ADC_InitStruct);
void ADC_Set_CH(ADC_TYPE_CHS AdcCH);
uint16_t ADC_GetConvValue(void);
FlagStatus ADC_GetConvStatus(void);
ErrorStatus ADC_ACPConfig(ADC_ACP_TypeDef *ADC_ACP_InitStruct);
ErrorStatus ADC_SoftStart(void);
ErrorStatus ADC_SoftStop(void);
uint16_t ADC_GetACPMeanValue(void);
uint16_t ADC_GetACPMinValue(void);
uint16_t ADC_GetACPMaxValue(void);
FlagStatus ADC_GetFlagStatus(ADC_TYPE_IF IFName);
ITStatus ADC_GetITStatus(ADC_TYPE_IE IEName);
ErrorStatus ADC_ClearIFStatus(ADC_TYPE_IF IFName);
void ADC_Reset(void);

#endif

/*************************END OF FILE**********************/
