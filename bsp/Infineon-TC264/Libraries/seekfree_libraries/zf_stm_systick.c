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
 
 
#include "IfxStm.h"
#include "IFXSTM_CFG.h"
#include "zf_stm_systick.h"

static uint32 systick_count[2];

//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick延时函数
//  @param      time            需要延时的时间
//  @return     void
//  Sample usage:               无需用户调用，用户请使用h文件中的宏定义
//-------------------------------------------------------------------------------------------------------------------
void systick_delay(STMN_enum stmn, uint32 time)
{
	uint32 stm_clk;
	stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));

	IfxStm_waitTicks(IfxStm_getAddress((IfxStm_Index)stmn), (uint32)((uint64)stm_clk*time/1000000000));
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      systick定时器启动
//  @param      stmn			选择使用的模块
//  @return     void
//  Sample usage:				systick_start(STM0);//记录下当前的时间
//-------------------------------------------------------------------------------------------------------------------
void systick_start(STMN_enum stmn)
{

	systick_count[stmn] = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief     获得当前System tick timer的值
//  @param     stmn				选择使用的模块
//  @return    uint32 			返回从开始到现在的时间(单位10ns)
//  Sample usage:               uint32 tim = systick_getval(STM0);
//-------------------------------------------------------------------------------------------------------------------
uint32 systick_getval(STMN_enum stmn)
{
	uint32 time;
	uint32 stm_clk;

	stm_clk = IfxStm_getFrequency(IfxStm_getAddress((IfxStm_Index)stmn));

	time = IfxStm_getLower(IfxStm_getAddress((IfxStm_Index)stmn)) - systick_count[stmn];
	time = (uint32)((uint64)time * 100000000 / stm_clk);
	return time;
}
