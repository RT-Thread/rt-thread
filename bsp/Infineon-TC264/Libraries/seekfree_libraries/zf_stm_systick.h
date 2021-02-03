/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		stm_systick
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_stm_systick_h
#define _zf_stm_systick_h

#include "common.h"



typedef enum  // 枚举STM模块号
{
    STM0,
	STM1,
}STMN_enum;


void systick_delay(STMN_enum stmn, uint32 time);
void systick_start(STMN_enum stmn);
uint32 systick_getval(STMN_enum stmn);

//------------------------------------以下宏定义用于延时------------------------------------
#define systick_delay_ms(stmn, time)	systick_delay(stmn, time*1000000)   //设置延时时间  单位ms
#define systick_delay_us(stmn, time)	systick_delay(stmn, time*1000)      //设置延时时间  单位us
#define systick_delay_ns(stmn, time)	systick_delay(stmn, time)   		//设置延时时间  单位ns

//------------------------------------以下宏定义用于获取当前时间------------------------------------
#define systick_getval_ms(stmn)         systick_getval(stmn)/100000         //获取当前计时时间  单位ms
#define systick_getval_us(stmn)         systick_getval(stmn)/100            //获取当前计时时间  单位us
#define systick_getval_ns(stmn)         systick_getval(stmn)*10    			//获取当前计时时间  单位ns


#endif
