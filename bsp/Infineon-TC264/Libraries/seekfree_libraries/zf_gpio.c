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
 
 


#include "zf_gpio.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取GPIO基地址
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     void
//  Sample usage:           文件内部使用，用户无需关心
//-------------------------------------------------------------------------------------------------------------------
volatile Ifx_P* get_port(PIN_enum pin)
{
	volatile Ifx_P *port;

	switch(pin&0xffe0)
	{
		case P00_0:	port = &MODULE_P00;	break;
		case P02_0:	port = &MODULE_P02;	break;
		case P10_0:	port = &MODULE_P10;	break;
		case P11_0:	port = &MODULE_P11;	break;
		case P13_0:	port = &MODULE_P13;	break;
		case P14_0:	port = &MODULE_P14;	break;
		case P15_0:	port = &MODULE_P15;	break;
		case P20_0:	port = &MODULE_P20;	break;
		case P21_0:	port = &MODULE_P21;	break;
		case P22_0:	port = &MODULE_P22;	break;
		case P23_0:	port = &MODULE_P23;	break;
		case P32_0:	port = &MODULE_P32;	break;
		case P33_0:	port = &MODULE_P33;	break;
		default:break;
	}
#pragma warning 507
	return port;
#pragma warning default
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO初始化
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      dat         引脚初始化时设置的电平状态，输出时有效 0：低电平 1：高电平
//  @param      pinmode     引脚配置（可设置参数由zf_gpio.h文件内GPIOMODE_enum枚举值确定）
//  @return     void
//  Sample usage:           gpio_init(P00_0, GPO, 1, PUSHPULL);//P00_0初始化为GPIO功能、输出模式、输出高电平、推挽输出
//  @note					需要特别注意P20_2是不能用于输出的，仅仅只有输入的功能
//-------------------------------------------------------------------------------------------------------------------
void gpio_init(PIN_enum pin, GPIODIR_enum dir, uint8 dat, GPIOMODE_enum pinmode)
{
	IfxPort_Mode port_mode;

	if(dir == GPI)
	{
		switch(pinmode)
		{
			case NO_PULL:  	port_mode = IfxPort_Mode_inputNoPullDevice; break;
			case PULLUP:   	port_mode = IfxPort_Mode_inputPullUp; 		break;
			case PULLDOWN: 	port_mode = IfxPort_Mode_inputPullDown; 	break;
			default:		port_mode = IfxPort_Mode_inputPullUp; 		break;
		}
	}
	else
	{
		switch(pinmode)
		{
			case OPENDRAIN:	port_mode = IfxPort_Mode_outputOpenDrainGeneral; break;//开漏输出
			default:		port_mode = IfxPort_Mode_outputPushPullGeneral;	 break;//默认为推挽输
		}
	}

	IfxPort_setPinMode(get_port(pin), pin&0x1f, port_mode);

	IfxPort_setPinPadDriver(get_port(pin), pin&0x1f, IfxPort_PadDriver_cmosAutomotiveSpeed1);

	if(dir == GPO)
	{
		if(dat) IfxPort_setPinHigh(get_port(pin), pin&0x1f);
		else    IfxPort_setPinLow(get_port(pin), pin&0x1f);
	}

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO引脚驱动模式
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      pin_driver 	引脚驱动模式设置
//  @return     void
//  Sample usage:           gpio_pin_driver(P00_0, IfxPort_PadDriver_cmosAutomotiveSpeed1)
//-------------------------------------------------------------------------------------------------------------------
void gpio_pin_driver(PIN_enum pin, IfxPort_PadDriver pin_driver)
{
	IfxPort_setPinPadDriver(get_port(pin), pin&0x1f, pin_driver);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO输出设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dat         0：低电平 1：高电平
//  @return     void
//  Sample usage:           gpio_set(P00_0, 1);//P00_0 输出高电平
//-------------------------------------------------------------------------------------------------------------------
void gpio_set(PIN_enum pin, uint8 dat)
{
    if(dat) IfxPort_setPinHigh(get_port(pin), pin&0x1f);
    else    IfxPort_setPinLow(get_port(pin), pin&0x1f);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO状态获取
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     uint8       0：低电平 1：高电平
//  Sample usage:           uint8 status = gpio_get(P00_0);//获取P00_0引脚电平
//-------------------------------------------------------------------------------------------------------------------
uint8 gpio_get(PIN_enum pin)
{
    return IfxPort_getPinState(get_port(pin), pin&0x1f);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO方向设置
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @param      dir         引脚的方向   输出：GPO   输入：GPI
//  @param      pinmode     引脚配置（可设置参数由zf_gpio.h文件内GPIOMODE_enum枚举值确定）
//  @return     void        
//  Sample usage:           gpio_dir(P00_0, GPO, PUSHPULL);//设置P00_0为推挽输出模式
//-------------------------------------------------------------------------------------------------------------------
void gpio_dir(PIN_enum pin, GPIODIR_enum dir, GPIOMODE_enum pinmode)
{
	IfxPort_Mode port_mode;

	if(dir == GPI)
	{
		switch(pinmode)
		{
			case NO_PULL:  	port_mode = IfxPort_Mode_inputNoPullDevice; break;
			case PULLUP:   	port_mode = IfxPort_Mode_inputPullUp; 		break;
			case PULLDOWN: 	port_mode = IfxPort_Mode_inputPullDown; 	break;
			default:		port_mode = IfxPort_Mode_inputPullUp; 		break;
		}
	}
	else
	{
		switch(pinmode)
		{
			case OPENDRAIN:	port_mode = IfxPort_Mode_outputOpenDrainGeneral; break;//开漏输出
			default:		port_mode = IfxPort_Mode_outputPushPullGeneral;	 break;//默认为推挽输
		}
	}
	
	IfxPort_setPinMode(get_port(pin), pin&0x1f, port_mode);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      GPIO 翻转
//  @param      pin         选择的引脚 (可选择范围由 common.h 内PIN_enum枚举值确定)
//  @return     void        
//  Sample usage:           gpio_toggle(P00_0);//P00_0引脚电平翻转
//-------------------------------------------------------------------------------------------------------------------
void gpio_toggle(PIN_enum pin)
{
	IfxPort_togglePin(get_port(pin), pin&0x1f);
}



