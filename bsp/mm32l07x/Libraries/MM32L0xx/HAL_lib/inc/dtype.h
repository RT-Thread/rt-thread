/****************************************Copyright (c)****************************************************
** 

**--------------File Info---------------------------------------------------------------------------------
** File name:			dtype.h
** modified Date:  		22/08/2017
** Last Version:		V2.0.0
** Descriptions:		定义工程要用到的数据类型，包括函数库和应用代码都应该使用本文件里定义的数据类型
**	
*********************************************************************************************************/
#ifndef _DTYPE_H_
#define _DTYPE_H_     //这样处理是为了避免同一个文件重复包含该头文件

/*********************************************************************************************************
/定义数据的读写特性，常用于外围寄存器的存储限制
*********************************************************************************************************/
#define     __I     volatile const    //只读 
#define     __O     volatile          //只写
#define     __IO    volatile          //读写

/*********************************************************************************************************
常用数据类型定义
*********************************************************************************************************/
typedef unsigned char  int8u;         //无符号8位整型变量 
typedef signed   char  int8s;		  //有符号8位整型变量 
typedef unsigned short int16u;        //无符号16位整型变量
typedef signed   short int16s;        //有符号16位整型变量
typedef unsigned int   int32u;        //无符号32位整型变量
typedef signed   int   int32s;        //有符号32位整型变量 
typedef float          fp32;          //单精度浮点数（32位长度）
typedef double         fp64;          //双精度浮点数（64位长度）

/*********************************************************************************************************
标准函数库用到的数据类型定义
*********************************************************************************************************/
//typedef   signed          char int8_t;
//typedef   signed short     int int16_t;
//typedef   signed           int int32_t;
//
//typedef unsigned          char uint8_t;
//typedef unsigned short     int uint16_t;
//typedef unsigned           int uint32_t;
//
//typedef int32_t   s32;
//typedef int16_t   s16;
//typedef int8_t    s8;
//typedef uint32_t  u32;
//typedef uint16_t  u16;
//typedef uint8_t   u8;
/*
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrorStatus;	
typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))
*/
#endif  //_DTYPE_H_
