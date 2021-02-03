/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		ccu6_pit
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_ccu6_pit_h
#define _zf_ccu6_pit_h


#include "common.h"





//此枚举定义不允许用户修改
typedef enum //枚举模块号
{
    CCU6_0,
	CCU6_1,
}CCU6N_enum;

typedef enum //枚举通道号
{
    PIT_CH0,
	PIT_CH1,
}CCU6_CHN_enum;



#define PIT_CLEAR_FLAG(ccu6n,pit_ch) IfxCcu6_clearInterruptStatusFlag(IfxCcu6_getAddress((IfxCcu6_Index)ccu6n), (IfxCcu6_InterruptSource)(7+(pit_ch*2)))


void pit_init(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch, uint32 time);
void pit_close(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
void pit_start(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
void pit_disable_interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);
void pit_enable_interrupt(CCU6N_enum ccu6n, CCU6_CHN_enum pit_ch);


//------------------------------------以下代码用于PIT中断------------------------------------
#define pit_interrupt_ms(ccu6n, pit_ch, time)  pit_init(ccu6n, pit_ch, time*1000)	//(单位为 毫秒)
#define pit_interrupt_us(ccu6n, pit_ch, time)  pit_init(ccu6n, pit_ch, time)    	//(单位为 微秒)




#endif
