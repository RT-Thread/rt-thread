/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		common
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
 
 
#ifndef _common_h
#define _common_h

#include "PLATFORM_TYPES.H"

//数据类型声明
//typedef unsigned char       uint8;   //  8 bits
//typedef unsigned short int  uint16;  // 16 bits
//typedef unsigned long int   uint32;  // 32 bits
//typedef unsigned long long  uint64;  // 64 bits

typedef char                int8;    //  8 bits 
typedef short int           int16;   // 16 bits 
typedef long  int           int32;   // 32 bits 
typedef long  long          int64;   // 64 bits 

typedef volatile int8       vint8;   //  8 bits 
typedef volatile int16      vint16;  // 16 bits 
typedef volatile int32      vint32;  // 32 bits 
typedef volatile int64      vint64;  // 64 bits 

typedef volatile uint8      vuint8;  //  8 bits 
typedef volatile uint16     vuint16; // 16 bits 
typedef volatile uint32     vuint32; // 32 bits 
typedef volatile uint64     vuint64; // 64 bits 


typedef enum //枚举端口
{
	//在设置IO时请自行根据硬件确认当前芯片是否具有此IO
    P00_0 = 0*32,  P00_1, P00_2,  P00_3,  P00_4,  P00_5,  P00_6,  P00_7,
	P00_8, 		   P00_9, P00_10, P00_11, P00_12, P00_13, P00_14, P00_15,

	P02_0 = 2*32,  P02_1, P02_2,  P02_3,  P02_4,  P02_5,  P02_6,  P02_7,
	P02_8, 		   P02_9, P02_10, P02_11, P02_12, P02_13, P02_14, P02_15,

	P10_0 = 10*32, P10_1, P10_2,  P10_3,  P10_4,  P10_5,  P10_6,  P10_7,
	P10_8, 		   P10_9, P10_10, P10_11, P10_12, P10_13, P10_14, P10_15,

	P11_0 = 11*32, P11_1, P11_2,  P11_3,  P11_4,  P11_5,  P11_6,  P11_7,
	P11_8, 		   P11_9, P11_10, P11_11, P11_12, P11_13, P11_14, P11_15,

	P13_0 = 13*32, P13_1, P13_2,  P13_3,  P13_4,  P13_5,  P13_6,  P13_7,
	P13_8, 		   P13_9, P13_10, P13_11, P13_12, P13_13, P13_14, P13_15,

	P14_0 = 14*32, P14_1, P14_2,  P14_3,  P14_4,  P14_5,  P14_6,  P14_7,
	P14_8, 		   P14_9, P14_10, P14_11, P14_12, P14_13, P14_14, P14_15,

	P15_0 = 15*32, P15_1, P15_2,  P15_3,  P15_4,  P15_5,  P15_6,  P15_7,
	P15_8, 		   P15_9, P15_10, P15_11, P15_12, P15_13, P15_14, P15_15,

	P20_0 = 20*32, P20_1, P20_2,  P20_3,  P20_4,  P20_5,  P20_6,  P20_7,
	P20_8, 		   P20_9, P20_10, P20_11, P20_12, P20_13, P20_14, P20_15,

	P21_0 = 21*32, P21_1, P21_2,  P21_3,  P21_4,  P21_5,  P21_6,  P21_7,
	P21_8, 		   P21_9, P21_10, P21_11, P21_12, P21_13, P21_14, P21_15,

	P22_0 = 22*32, P22_1, P22_2,  P22_3,  P22_4,  P22_5,  P22_6,  P22_7,
	P22_8, 		   P22_9, P22_10, P22_11, P22_12, P22_13, P22_14, P22_15,

	P23_0 = 23*32, P23_1, P23_2,  P23_3,  P23_4,  P23_5,  P23_6,  P23_7,
	P23_8, 		   P23_9, P23_10, P23_11, P23_12, P23_13, P23_14, P23_15,

	P32_0 = 32*32, P32_1, P32_2,  P32_3,  P32_4,  P32_5,  P32_6,  P32_7,
	P32_8, 		   P32_9, P32_10, P32_11, P32_12, P32_13, P32_14, P32_15,

	P33_0 = 33*32, P33_1, P33_2,  P33_3,  P33_4,  P33_5,  P33_6,  P33_7,
	P33_8, 		   P33_9, P33_10, P33_11, P33_12, P33_13, P33_14, P33_15,

}PIN_enum;



typedef enum //枚举端口方向
{
    GPI = 0, //定义管脚输入方向      
    GPO = 1, //定义管脚输出方向
}GPIODIR_enum;

typedef enum //枚举端口电平
{
    GPIO_LOW = 0,	//定义低电平
    GPIO_HIGH = 1,	//定义高电平
}GPIOLEVEL_enum;




#include <math.h>
#include <string.h>


extern uint8 camera_type;	//摄像头型号  1：总钻风   2：凌瞳（暂未支持）3：小钻风


void get_clk(void);

#endif
