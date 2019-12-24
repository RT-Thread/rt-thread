/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_printf.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/07/14
 *描  述：  串口打印库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_printf.h"
#include <stdarg.h>

/***************************************************************
  函数名：fputc
  描  述：重定向c库函数printf到UART
  输入值：。。。
  输出值：。。。
  返回值：。。。
 ***************************************************************/
/*使用printf()函数需要调用微库：Use MicroLIB*/
int fputc(int ch, FILE *f)
{
    FlagStatus Status = RESET;
    uint32_t Count=0;

#if defined  __PRINTF_USE_UART3__
    UART_SendByte(UART3, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART3,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#elif defined __PRINTF_USE_UART2__
    UART_SendByte(UART2, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART2,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#elif defined __PRINTF_USE_UART1__
    UART_SendByte(UART1, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART1,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#else
    UART_SendByte(UART0, (unsigned char) ch);
    do
    {
        Status = UART_GetFlagStatus(UART0,UART_FLAG_TXIDLE);
        Count++;
    }while((Status == RESET)&&(Count != 0x1CE2));

    if(Count == 0x1CE2)
        return (EOF);

#endif
    return (ch);
}

#ifdef __clang__     //当使用的是idesigner编译器时，则不调用微库
/***************************************************************
  描  述：将整形数据转换成字符串
  输入值：   -radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 返回值：无
 ***************************************************************/
static char *itoa(int value, char *string, int radix)
{
    int i, d;
    int flag = 0;
    char *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;
}
/***************************************************************
  描  述：格式化输出，类似于C库中的printf，但这里没有用到C库
  输入值：   -UARTx 串口通道，
 *         -Data   要发送到串口的内容的指针
 *         -...    其他参数
 返回值：无
 典型应用： UART_printf("\r\n this is a demo \r\n" );
 *         UART1_printf("\r\n %d \r\n", i );
 *         UART1_printf("\r\n %s \r\n", j );
 ***************************************************************/
/* 未调用C库的时候可以使用此函数代替C库中的printf，但功能无printf全，
   只支持\r  \n  %d   %s */
ErrorStatus UART_printf(uint8_t *Data,...)
{
		UART_TypeDef *UARTx;
    const char *s;
    int d;   
    char buf[16];
    ErrorStatus RET = SUCCESS;
    FlagStatus Status = RESET;
    uint32_t Count=0;
    va_list ap;
	
/**
	**
	**使用宏定义选择使用哪一个串口
	**
***/
#if defined  __PRINTF_USE_UART3__
	
	UARTx = UART3;
	
#elif defined __PRINTF_USE_UART2__
	
	UARTx = UART2;
	
#elif defined __PRINTF_USE_UART1__

	UARTx = UART1;
	
#else

	UARTx = UART0;
	
#endif		
		
    va_start(ap, Data);

    while ( *Data != 0)                           // 判断是否到达字符串结束符
    {
        if ( *Data == 0x5c )                      //'\'
        {
            switch ( *++Data )
            {
                case 'r':                         //回车符
                    Count=0;
                    UART_SendByte(UARTx, 0x0d);
                    do
                    {
                        Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                        Count++;
                    }while((Status == RESET)&&(Count != 0x1CE2));

                    if(Count == 0x1CE2)
                        RET = ERROR;

                    Data ++;
                    break;

                case 'n':                         //换行符
                    Count=0;
                    UART_SendByte(UARTx, 0x0a);    
                    do
                    {
                        Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                        Count++;
                    }while((Status == RESET)&&(Count != 0x1CE2));

                    if(Count == 0x1CE2)
                        RET = ERROR;

                    Data ++;
                    break;

                default:
                    Data ++;
                    break;
            }             
        }
        else if ( *Data == '%')
        {
            switch ( *++Data )
            {                
                case 's':                         //字符串
                    s = va_arg(ap, const char *);
                    for ( ; *s; s++) 
                    {
                        Count=0;
                        UART_SendByte(UARTx,*s);
                        do
                        {
                            Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                            Count++;
                        }while((Status == RESET)&&(Count != 0x1CE2));

                        if(Count == 0x1CE2)
                            RET = ERROR;
                    }
                    Data++;
                    break;

                case 'd':                         //十进制
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf; *s; s++)  
                    {
                        Count=0;
                        UART_SendByte(UARTx,*s);
                        do
                        {
                            Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                            Count++;
                        }while((Status == RESET)&&(Count != 0x1CE2));

                        if(Count == 0x1CE2)
                            RET = ERROR;
                    }
                    Data++;
                    break;
                default:
                    Data++;
                    break;
            }
        } /* end of else if */
        else 
        {
            Count=0;
            UART_SendByte(UARTx, *Data++);
            do
            {
                Status = UART_GetFlagStatus(UARTx,UART_FLAG_TXIDLE);
                Count++;
            }while((Status == RESET)&&(Count != 0x1CE2));

            if(Count == 0x1CE2)
                RET = ERROR;
        }
    }
    return RET;
}

#endif
/*************************END OF FILE**********************/

