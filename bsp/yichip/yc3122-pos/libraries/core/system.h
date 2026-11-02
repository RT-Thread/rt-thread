/*
 * Copyright (c) 2006-2020, YICHIP Development Team
 * @file     yc_system.h
 * @brief    source file for setting system
 *
 * Change Logs:
 * Date           Author      Version        Notes
 * 2020-11-05     wushengyan         V1.0.0         the first version
 */
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define SDK_DEBUG	//Debug switch

#include <string.h>
#include "yc_uart.h"
#include "rom_api.h"
#include "board_config.h"

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

void printv(uint8_t *buf, uint32_t len, char *s);

void PrintPort_Set(UART_TypeDef *UARTx);

void Board_Init(void);

void _assert_handler(const char *file, int line, const char *func);

#ifdef SDK_DEBUG
#define _ASSERT(x)	\
if (!(x))                                                                    \
{                                                                             \
    _assert_handler(__FILE__,__LINE__,__FUNCTION__);\
}
#else
#define _ASSERT(x)
#endif

#define YC_DEBUG_LOG(type, message)                                          \
do                                                                            \
{                                                                             \
    if (type)                                                                 \
        MyPrintf message;                                                   \
}                                                                             \
while (0)

#endif /*__SYSTEM_H__*/
