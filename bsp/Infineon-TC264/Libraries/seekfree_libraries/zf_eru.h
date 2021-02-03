/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		eru
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_eru_h
#define _zf_eru_h

#include "common.h"



typedef enum  // 枚举触发方式
{
    RISING,
    FALLING,
    BOTH,
}TRIGGER_enum;

typedef enum  // 枚举ERU通道
{
	//一个通道只能选择其中一个引脚作为 外部中断的输入
	//例如通道0 可选引脚为P10_7 和 P15_4，
	//在LQFP144封装中没有P10_7
	ERU_CH0_REQ4_P10_7   = 0*3,  ERU_CH0_REQ0_P15_4,						//通道0可选引脚   LQFP没有P10_7引脚
	//在LQFP144封装中没有P10_8
	ERU_CH1_REQ5_P10_8   = 1*3,  ERU_CH1_REQ10_P14_3,						//通道1可选引脚   LQFP没有P10_8引脚
	ERU_CH2_REQ7_P00_4   = 2*3,  ERU_CH2_REQ14_P02_1, ERU_CH2_REQ2_P10_2,	//通道2可选引脚
	ERU_CH3_REQ6_P02_0   = 3*3,  ERU_CH3_REQ3_P10_3,  ERU_CH3_REQ15_P14_1,	//通道3可选引脚

	//通道4与通道0 共用中断函数 在中断内通过判断标志位来识别是哪个通道触发的中断
	ERU_CH4_REQ13_P15_5  = 4*3,  ERU_CH4_REQ8_P33_7,						//通道4可选引脚
	//通道5与通道1 共用中断函数
	ERU_CH5_REQ1_P15_8   = 5*3,												//通道5可选引脚
	//通道6与通道2 共用中断函数
	ERU_CH6_REQ12_P11_10 = 6*3,  ERU_CH6_REQ9_P20_0,						//通道6可选引脚
	//通道7与通道3 共用中断函数
	ERU_CH7_REQ16_P15_1  = 7*3,  ERU_CH7_REQ11_P20_9,						//通道7可选引脚
}ERU_PIN_enum;

//特别注意通道2 与 通道3都被摄像头占用，意味着只有两个外部中断可供用户使用





//中断标志位获取
#define GET_GPIO_FLAG(eru_pin)   	IfxScuEru_getEventFlagStatus((IfxScuEru_InputChannel)(eru_pin/3))
//中断标志位清除
#define CLEAR_GPIO_FLAG(eru_pin) 	IfxScuEru_clearEventFlag((IfxScuEru_InputChannel)(eru_pin/3))





void eru_init(ERU_PIN_enum eru_pin, TRIGGER_enum trigger);
void eru_enable_interrupt(ERU_PIN_enum eru_pin);
void eru_disable_interrupt(ERU_PIN_enum eru_pin);
#endif
