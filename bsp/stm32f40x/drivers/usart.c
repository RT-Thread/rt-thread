/*
 * File      : usart.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-03-29     Bernard      remove interrupt Tx and DMA Rx mode
 * 2012-02-08     aozima       update for F4.
 */

#include "stm32f4xx.h"
#include "usart.h"
#include "board.h"
#include <serial.h>

/*
 * Use UART1 as console output and finsh input
 * interrupt Rx and poll Tx (stream mode)
 *
 * Use UART2 with interrupt Rx and poll Tx
 * Use UART3 with DMA Tx and interrupt Rx -- DMA channel 2
 *
 * USART DMA setting on STM32
 * USART1 Tx --> DMA Channel 4
 * USART1 Rx --> DMA Channel 5
 * USART2 Tx --> DMA Channel 7
 * USART2 Rx --> DMA Channel 6
 * USART3 Tx --> DMA Channel 2
 * USART3 Rx --> DMA Channel 3
 */

#ifdef RT_USING_UART1
struct stm32_serial_int_rx uart1_int_rx;
struct stm32_serial_device uart1 =
{
	USART1,
	&uart1_int_rx,
	RT_NULL
};
struct rt_device uart1_device;
#endif

#ifdef RT_USING_UART2
struct stm32_serial_int_rx uart2_int_rx;
struct stm32_serial_device uart2 =
{
	USART2,
	&uart2_int_rx,
	RT_NULL
};
struct rt_device uart2_device;
#endif

#ifdef RT_USING_UART3
struct stm32_serial_int_rx uart3_int_rx;
struct stm32_serial_dma_tx uart3_dma_tx;
struct stm32_serial_device uart3 =
{
	USART3,
	&uart3_int_rx,
	&uart3_dma_tx
};
struct rt_device uart3_device;
#endif

//#define USART1_DR_Base  0x40013804
//#define USART2_DR_Base  0x40004404
//#define USART3_DR_Base  0x40004804

/* USART1_REMAP = 0 */
#define UART1_GPIO_TX		GPIO_Pin_9
#define UART1_TX_PIN_SOURCE GPIO_PinSource9
#define UART1_GPIO_RX		GPIO_Pin_10
#define UART1_RX_PIN_SOURCE GPIO_PinSource10
#define UART1_GPIO			GPIOA
#define UART1_GPIO_RCC      RCC_AHB1Periph_GPIOA
#define RCC_APBPeriph_UART1	RCC_APB2Periph_USART1
#define UART1_TX_DMA		DMA1_Channel4
#define UART1_RX_DMA		DMA1_Channel5

#define UART2_GPIO_TX	    GPIO_Pin_2
#define UART2_TX_PIN_SOURCE GPIO_PinSource2
#define UART2_GPIO_RX	    GPIO_Pin_3
#define UART2_RX_PIN_SOURCE GPIO_PinSource3
#define UART2_GPIO	    	GPIOA
#define UART2_GPIO_RCC   	RCC_AHB1Periph_GPIOA
#define RCC_APBPeriph_UART2	RCC_APB1Periph_USART2

/* USART3_REMAP[1:0] = 00 */
#define UART3_GPIO_TX		GPIO_Pin_10
#define UART3_TX_PIN_SOURCE GPIO_PinSource10
#define UART3_GPIO_RX		GPIO_Pin_11
#define UART3_RX_PIN_SOURCE GPIO_PinSource11
#define UART3_GPIO			GPIOB
#define UART3_GPIO_RCC   	RCC_AHB1Periph_GPIOB
#define RCC_APBPeriph_UART3	RCC_APB1Periph_USART3
#define UART3_TX_DMA		DMA1_Stream1
#define UART3_RX_DMA		DMA1_Stream3

static void RCC_Configuration(void)
{
#ifdef RT_USING_UART1
	/* Enable USART2 GPIO clocks */
	RCC_AHB1PeriphClockCmd(UART1_GPIO_RCC, ENABLE);
	/* Enable USART2 clock */
	RCC_APB2PeriphClockCmd(RCC_APBPeriph_UART1, ENABLE);
#endif

#ifdef RT_USING_UART2
	/* Enable USART2 GPIO clocks */
	RCC_AHB1PeriphClockCmd(UART2_GPIO_RCC, ENABLE);
	/* Enable USART2 clock */
	RCC_APB1PeriphClockCmd(RCC_APBPeriph_UART2, ENABLE);
#endif

#ifdef RT_USING_UART3
	/* Enable USART3 GPIO clocks */
	RCC_AHB1PeriphClockCmd(UART3_GPIO_RCC, ENABLE);
	/* Enable USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APBPeriph_UART3, ENABLE);

	/* DMA clock enable */
	RCC_APB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
#endif
}

static void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

#ifdef RT_USING_UART1
	/* Configure USART1 Rx/tx PIN */
	GPIO_InitStructure.GPIO_Pin = UART1_GPIO_RX | UART1_GPIO_TX;
	GPIO_Init(UART1_GPIO, &GPIO_InitStructure);

    /* Connect alternate function */
    GPIO_PinAFConfig(UART1_GPIO, UART1_TX_PIN_SOURCE, GPIO_AF_USART1);
    GPIO_PinAFConfig(UART1_GPIO, UART1_RX_PIN_SOURCE, GPIO_AF_USART1);
#endif

#ifdef RT_USING_UART2
	/* Configure USART2 Rx/tx PIN */
	GPIO_InitStructure.GPIO_Pin = UART2_GPIO_TX | UART2_GPIO_RX;
	GPIO_Init(UART2_GPIO, &GPIO_InitStructure);

    /* Connect alternate function */
    GPIO_PinAFConfig(UART2_GPIO, UART2_TX_PIN_SOURCE, GPIO_AF_USART2);
    GPIO_PinAFConfig(UART2_GPIO, UART2_RX_PIN_SOURCE, GPIO_AF_USART2);
#endif

#ifdef RT_USING_UART3
	/* Configure USART3 Rx/tx PIN */
	GPIO_InitStructure.GPIO_Pin = UART3_GPIO_RX | UART3_GPIO_RX;
	GPIO_Init(UART3_GPIO, &GPIO_InitStructure);

    /* Connect alternate function */
    GPIO_PinAFConfig(UART2_GPIO, UART3_TX_PIN_SOURCE, GPIO_AF_USART3);
    GPIO_PinAFConfig(UART2_GPIO, UART3_RX_PIN_SOURCE, GPIO_AF_USART3);
#endif
}

static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

#ifdef RT_USING_UART1
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef RT_USING_UART2
	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#ifdef RT_USING_UART3
	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Enable the DMA1 Channel2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}

static void DMA_Configuration(void)
{
#if defined (RT_USING_UART3)
	DMA_InitTypeDef DMA_InitStructure;

//  /* Configure DMA Stream */
//  DMA_InitStructure.DMA_Channel = DMA_CHANNEL;
//  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SRC_Const_Buffer;
//  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DST_Buffer;
//  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
//  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
//  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
//  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
//  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
//  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
//  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA_STREAM, &DMA_InitStructure);

  /* Configure DMA Stream */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)0;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = (uint32_t)0;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  DMA_DeInit(UART3_TX_DMA);
  DMA_Init(UART3_TX_DMA, &DMA_InitStructure);

//	/* fill init structure */
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//
//	/* DMA1 Channel5 (triggered by USART3 Tx event) Config */
//	DMA_DeInit(UART3_TX_DMA);
//	DMA_InitStructure.DMA_PeripheralBaseAddr = USART3_DR_Base;
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)0;
//	DMA_InitStructure.DMA_BufferSize = 0;
//	DMA_Init(UART3_TX_DMA, &DMA_InitStructure);
	DMA_ITConfig(UART3_TX_DMA, DMA_IT_TC | DMA_IT_TE, ENABLE);
//	DMA_ClearFlag(DMA1_FLAG_TC5);
#endif
}

volatile USART_TypeDef * uart2_debug = USART2;
/*
 * Init all related hardware in here
 * rt_hw_serial_init() will register all supported USART device
 */
void rt_hw_usart_init()
{
	USART_InitTypeDef USART_InitStructure;

	RCC_Configuration();

	GPIO_Configuration();

	NVIC_Configuration();

	DMA_Configuration();

	/* uart init */
#ifdef RT_USING_UART1
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	/* register uart1 */
	rt_hw_serial_register(&uart1_device, "uart1",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart1);

	/* enable interrupt */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
#endif

#ifdef RT_USING_UART2
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);

	/* register uart2 */
	rt_hw_serial_register(&uart2_device, "uart2",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_STREAM,
		&uart2);

	/* Enable USART2 DMA Rx request */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
#endif

#ifdef RT_USING_UART3
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

//	uart3_dma_tx.dma_channel= UART3_TX_DMA;

	/* register uart3 */
	rt_hw_serial_register(&uart3_device, "uart3",
		RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_INT_RX | RT_DEVICE_FLAG_DMA_TX,
		&uart3);

	/* Enable USART3 DMA Tx request */
	USART_DMACmd(USART3, USART_DMAReq_Tx , ENABLE);

	/* enable interrupt */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
#endif
}
