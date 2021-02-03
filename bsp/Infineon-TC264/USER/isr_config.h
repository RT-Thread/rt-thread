/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr_config
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/

#ifndef _isr_config_h
#define _isr_config_h


//ISR_PRIORITY： TC264具有255个中断优先级可以设置 1-255，0优先级表示不开启中断，255为最高优先级
//特别注意
//中断优先级不能设置一样，所有中断优先级都必须设置为不一样的值
//特别注意



//INT_SERVICE：    宏定义决定中断由谁处理，也称为服务提供者（在TC264中，中断被叫做服务），可设置范围0:CPU0 1:CPU1 3:DMA  不可设置为其他值


//如果INT_SERVICE设置为3的话，ISR_PRIORITY的可设置范围则是0-47。








//------------PIT中断参数相关定义------------
#define CCU6_0_CH0_INT_SERVICE	0	//定义CCU6_0 PIT通道0中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define CCU6_0_CH0_ISR_PRIORITY 30	//定义CCU6_0 PIT通道0中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define CCU6_0_CH1_INT_SERVICE	0
#define CCU6_0_CH1_ISR_PRIORITY 31

#define CCU6_1_CH0_INT_SERVICE	0
#define CCU6_1_CH0_ISR_PRIORITY 32

#define CCU6_1_CH1_INT_SERVICE	0
#define CCU6_1_CH1_ISR_PRIORITY 33



//------------GPIO中断参数相关定义------------
//通道0与通道4是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define ERU_CH0_CH4_INT_SERVICE 0	//定义ERU通道0和通道4中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define ERU_CH0_CH4_INT_PRIO  	40	//定义ERU通道0和通道4中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

//通道1与通道5是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define ERU_CH1_CH5_INT_SERVICE 0	//定义ERU通道1和通道5中断服务类型，同上
#define ERU_CH1_CH5_INT_PRIO  	41	//定义ERU通道1和通道5中断优先级 同上

//通道2与通道6是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define ERU_CH2_CH6_INT_SERVICE 3	//定义ERU通道2和通道6中断服务类型，同上
#define ERU_CH2_CH6_INT_PRIO  	5	//定义ERU通道2和通道6中断优先级 同上

//通道3与通道7是公用一个中断函数 在中断内部通过标志位判断是谁触发的中断
#define ERU_CH3_CH7_INT_SERVICE 0	//定义ERU通道3和通道7中断服务类型，同上
#define ERU_CH3_CH7_INT_PRIO  	43	//定义ERU通道3和通道7中断优先级 同上


//------------DMA中断参数相关定义------------
#define	ERU_DMA_INT_SERVICE  0	//ERU触发DMA中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define ERU_DMA_INT_PRIO  	 60	//ERU触发DMA中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样


//------------串口中断参数相关定义------------
#define	UART0_INT_SERVICE  0	//定义串口0中断服务类型，即中断是由谁响应处理 0:CPU0 1:CPU1 3:DMA  不可设置为其他值
#define UART0_TX_INT_PRIO  10	//定义串口0发送中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样
#define UART0_RX_INT_PRIO  11	//定义串口0接收中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样
#define UART0_ER_INT_PRIO  12	//定义串口0错误中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

#define	UART1_INT_SERVICE  0
#define UART1_TX_INT_PRIO  13
#define UART1_RX_INT_PRIO  14
#define UART1_ER_INT_PRIO  15

#define	UART2_INT_SERVICE  0
#define UART2_TX_INT_PRIO  16
#define UART2_RX_INT_PRIO  17
#define UART2_ER_INT_PRIO  18

#define	UART3_INT_SERVICE  0
#define UART3_TX_INT_PRIO  19
#define UART3_RX_INT_PRIO  20
#define UART3_ER_INT_PRIO  21


#endif
