/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
 *文件名：  lib_printf.h
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  串口打印库函数头文件
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#ifndef __LIBPRINTF_H__
#define __LIBPRINTF_H__

#include "lib_uart.h"
#include <stdio.h>
#include "type.h"

int fputc(int ch, FILE *f);
static char *itoa(int value, char *string, int radix);
ErrorStatus UART_printf(uint8_t *Data,...);

#ifdef __clang__ 
ErrorStatus UART_printf(uint8_t *Data, ...);

#elif defined __CC_ARM

#define UART_printf  printf

#endif

#endif

/*************************END OF FILE**********************/
