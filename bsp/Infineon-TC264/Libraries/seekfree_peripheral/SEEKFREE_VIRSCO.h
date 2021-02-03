/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2018,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		虚拟示波器协议
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		IAR 8.3 or MDK 5.28
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 * @note		    示波器下载地址：https://pan.baidu.com/s/198CMXTZsbI3HAEqNXDngBw（包含清华直立方案资料）	
 ********************************************************************************************************************/

#ifndef _SEEKFREE_VIRSCO_H
#define _SEEKFREE_VIRSCO_H

#include "common.h"


extern uint8 virtual_scope_data[10];

void data_conversion(int16 data1, int16 data2, int16 data3, int16 data4, uint8 *dat);


#endif 
