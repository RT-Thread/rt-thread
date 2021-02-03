/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		gpio
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_gpio_h
#define _zf_gpio_h

#include "common.h"
#include "IFXPORT.h"




typedef enum    // 枚举上下拉选项
{
    NO_PULL,	//无输入上下拉
    PULLUP,		//输入上拉
	PULLDOWN,	//输入下拉
	PUSHPULL,	//推挽输出
	OPENDRAIN,	//开漏输出
}GPIOMODE_enum;


#define GET_PORT_IN_ADDR(pin)	(uint8 *)(&IfxPort_getAddress((IfxPort_Index)(pin/32))->IN + pin%32/8)



//需要特别注意P20_2是不能用于输出的，仅仅只有输入的功能
//需要特别注意P20_2是不能用于输出的，仅仅只有输入的功能
//需要特别注意P20_2是不能用于输出的，仅仅只有输入的功能




//------------------------------------------------------
//通用GPIO操作
void gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinconf);
void gpio_pin_driver(PIN_enum pin, IfxPort_PadDriver pin_driver);
void gpio_set(PIN_enum pin, uint8 dat);
uint8 gpio_get(PIN_enum pin);
void gpio_dir(PIN_enum pin, GPIODIR_enum dir, GPIOMODE_enum pinconf);
void gpio_toggle(PIN_enum pin);






#endif
