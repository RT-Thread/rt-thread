/*
File Name    : system.h
Author       : Yichip
Version      : V1.0
Date         : 2018/05/22
Description  : none.
*/

#ifndef __SYSTEM_H__
#define __SYSTEM_H__


#include <string.h>
#include "yc_uart.h"

//#define SDK_DEBUG	//Debug switch

#define BIT_SET(a,b) ((a) |= (1<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1<<(b)))				//bit Negation
#define BIT_GET(a,b) (((a) & (1<<(b)))>>(b))

/**
 * @brief Print format string to serial port 0.You need to initialize the serial port 0 before you use MyPrintf.
 *
 * @param format : format string
 * @param ...: format parameter
 */
void MyPrintf(char *format, ...);

void _assert_handler(const char *file, int line, const char *func);

void printv(uint8_t *buf, uint32_t len, uint8_t *s);

#define _ASSERT(x)	\
if (!(x))                                                                    \
{                                                                             \
  _assert_handler(__FILE__,__LINE__,__FUNCTION__);\
}


#endif /*__SYSTEM_H__*/

