/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		uart
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
 
#ifndef _zf_uart_h
#define _zf_uart_h


#include "common.h"
#include "ifxAsclin_Asc.h"



#define UART0_TX_BUFFER_SIZE 16	//定义串口0发送缓冲区大小
#define UART0_RX_BUFFER_SIZE 16	//定义串口0接收缓冲区大小

#define UART1_TX_BUFFER_SIZE 16
#define UART1_RX_BUFFER_SIZE 16

#define UART2_TX_BUFFER_SIZE 16
#define UART2_RX_BUFFER_SIZE 16

#define UART3_TX_BUFFER_SIZE 16
#define UART3_RX_BUFFER_SIZE 16



//此枚举定义不允许用户修改
typedef enum //枚举串口号
{
    UART_0,
    UART_1,
    UART_2,
    UART_3,
}UARTN_enum;


//此枚举定义不允许用户修改
typedef enum //枚举串口引脚
{
	//串口0 发送引脚可选范围
	UART0_TX_P14_0, UART0_TX_P14_1,  UART0_TX_P15_2,  UART0_TX_P15_3,
	//串口0 接收引脚可选范围
	UART0_RX_P14_1, UART0_RX_P15_3,

	//在LQFP144封装中没有P14_10和P14_8
	//串口1 发送引脚可选范围
	UART1_TX_P02_2, UART1_TX_P11_12, UART1_TX_P14_10, UART1_TX_P15_0, UART1_TX_P15_1,  UART1_TX_P15_4,  UART1_TX_P15_5, UART1_TX_P20_10, UART1_TX_P33_12, UART1_TX_P33_13,
	//串口1 接收引脚可选范围
	UART1_RX_P02_3, UART1_RX_P11_10, UART1_RX_P14_8,  UART1_RX_P15_1, UART1_RX_P15_5,  UART1_RX_P20_9,  UART1_RX_P33_13,

	//串口2 发送引脚可选范围
	UART2_TX_P02_0, UART2_TX_P10_5,  UART2_TX_P14_2,  UART2_TX_P14_3, UART2_TX_P33_8,  UART2_TX_P33_9,
	//串口2 接收引脚可选范围
	UART2_RX_P02_0, UART2_RX_P02_1,  UART2_RX_P10_6,  UART2_RX_P14_3, UART2_RX_P33_8,

	//在LQFP144封装中没有P32_2和P32_3
	//串口3 发送引脚可选范围
	UART3_TX_P00_0, UART3_TX_P00_1,  UART3_TX_P15_6,  UART3_TX_P15_7, UART3_TX_P20_0,  UART3_TX_P20_3,  UART3_TX_P21_7, UART3_TX_P32_2,  UART3_TX_P32_3,
	//串口3 接收引脚可选范围
	UART3_RX_P00_1, UART3_RX_P15_7,  UART3_RX_P20_3,  UART3_RX_P21_6, UART3_RX_P32_2,
}UART_PIN_enum;



//创建串口handle变量
extern IfxAsclin_Asc uart0_handle;
extern IfxAsclin_Asc uart1_handle;
extern IfxAsclin_Asc uart2_handle;
extern IfxAsclin_Asc uart3_handle;

void uart_init(UARTN_enum uartn, uint32 baud, UART_PIN_enum tx_pin, UART_PIN_enum rx_pin);
void uart_putchar(UARTN_enum uartn, uint8 dat);
void uart_putbuff(UARTN_enum uartn, uint8 *buff, uint32 len);
void uart_putstr(UARTN_enum uartn, const int8 *str);
void uart_getchar(UARTN_enum uartn, uint8 *dat);
uint8 uart_query(UARTN_enum uartn, uint8 *dat);

#endif
