#include "kbd.h"
#include "stm32f10x_lib.h"

#define GPIO_Pin_KB1	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
#define GPIO_Pin_KB2	GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_9
#define GPIO_KB1		GPIOA
#define GPIO_KB2		GPIOB

#define RCC_APB2Periph_GPIO_KB1		RCC_APB2Periph_GPIOA
#define RCC_APB2Periph_GPIO_KB2		RCC_APB2Periph_GPIOB

#define EXTI_LINE_KB1              	EXTI_Line0 | EXTI_Line1 | EXTI_Line2 | EXTI_Line3
#define GPIO_PORT_SOURCE_KB1		GPIO_PortSourceGPIOA
#define EXTI_LINE_KB2              	EXTI_Line0 | EXTI_Line1 | EXTI_Line9
#define GPIO_PORT_SOURCE_KB2		GPIO_PortSourceGPIOB

void rt_hw_kbd_init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

	/* Configure Key Button 1 GPIO Pin as input floating (Key Button EXTI Line) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_KB1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_KB1, &GPIO_InitStructure);
	
	/* Configure Key Button 2 GPIO Pin as input floating (Key Button EXTI Line) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_KB2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIO_KB2, &GPIO_InitStructure);
	
	/* Enable Key Button GPIO Port clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_KB1 | RCC_APB2Periph_GPIO_KB2 |
		RCC_APB2Periph_AFIO, ENABLE);

	/* Configure one bit for preemption priority */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	/* Enable the EXTI9_5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* Connect Key Button EXTI Line to Key Button GPIO Pin */
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB1, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB1, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB1, GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB1, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB2, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB2, GPIO_PinSource1);
	GPIO_EXTILineConfig(GPIO_PORT_SOURCE_KB2, GPIO_PinSource9);

	/* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
	EXTI_InitStructure.EXTI_Line = EXTI_LINE_KB1 | EXTI_LINE_KB2;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

void rt_hw_kbd_scan()
{
	/* KBD1 */
	
	/* KBD2 */
}
