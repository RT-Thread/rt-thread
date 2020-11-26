/*
 * @Author: your name
 * @Date: 2020-11-20 11:59:49
 * @LastEditTime: 2020-11-20 15:23:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \stm32f407-handheld - program\applications\app\common.h
 */
/****************************************************************************
 *
 * File Name
 *  common.h
 * Author
 *  wangk
 * Date
 *  2018/01/16
 * Descriptions:
 * 公共定义头文件
 *
 ****************************************************************************/

#ifndef __COMMON_H__
#define __COMMON_H__

#include <rtthread.h>

/**---------------------------------------------------------------------------*
**                             Compiler Flag                                  *
**----------------------------------------------------------------------------*/
#ifdef __cplusplus
extern   "C"
{
#endif

/*----------------------------------------------------------------------------*
**                             Mcaro Definitions                              *
**----------------------------------------------------------------------------*/

#if !defined(MAX)
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#endif

#if !defined(MIN)
#define MIN(a,b)	(((a) < (b)) ? (a) : (b))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

//#ifndef UNUSED
//#define UNUSED(x) ((void)(x))
//#endif

#ifndef STR_LEN
#define STR_LEN(str) (sizeof(str) - 1)
#endif

#ifndef STR_ITEM
#define STR_ITEM(s) (s), STR_LEN(s)
#endif

/* 半字节转换为HEX字符 */
#define TO_HEX_CHAR(b) (((b) <= 0x09) ? ((b) + (uint8_t)'0') : (((b) - 0x0A) + (uint8_t)'A'))

/* 字符是否为有效的HEX字符 */
#define IS_HEX_CHAR(c) ((((c) >= '0') && ((c) <= '9')) \
                        || (((c) >= 'a') && ((c) <= 'f')) \
                        || (((c) >= 'A') && ((c) <= 'F')))

/* Case返回枚举常量(或宏)名称字符串 */
#define MACRO_NAME_CASE(eMacro) case eMacro: return #eMacro

#ifdef TRACE_ON
#define LOG_TRACE(...) rt_kprintf(__VA_ARGS__)
#else
#define LOG_TRACE(...)
#endif

/*----------------------------------------------------------------------------*
**                             Data Structures                                *
**----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*
**                             Function Define                                *
**----------------------------------------------------------------------------*/

/**--------------------------------------------------------------------------*
**                         Compiler Flag                                     *
**---------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif

#endif // __COMMON_H__
