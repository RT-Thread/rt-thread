#include <rtthread.h>
#include "stm32f10x.h"

#define LEDR_PORT          GPIOA
#define LEDR_PIN           GPIO_Pin_11
#define LEDR_RCC           RCC_APB2Periph_GPIOA

#define LEDG_PORT          GPIOA
#define LEDG_PIN           GPIO_Pin_12
#define LEDG_RCC           RCC_APB2Periph_GPIOA

char thread001_stack[512];
struct rt_thread thread001;
void rt_init_thread_entry001(void *parameter)
{
    unsigned int count=0;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LEDG_RCC,ENABLE);

    GPIO_InitStructure.GPIO_Pin  = LEDG_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LEDG_PORT,&GPIO_InitStructure);

    while(1)
    {
    rt_kprintf("thread001:%d\r\n",count++);
    GPIO_ResetBits(LEDG_PORT,LEDG_PIN);
    rt_thread_delay(64);
    rt_kprintf("thread001:%d\r\n",count++);
    GPIO_SetBits(LEDG_PORT,LEDG_PIN);
    rt_thread_delay(64);
    }
}

char thread002_stack[512];
struct rt_thread thread002;
void rt_init_thread_entry002(void *parameter)
{
    unsigned int count=0;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(LEDR_RCC,ENABLE);

    GPIO_InitStructure.GPIO_Pin  = LEDR_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LEDR_PORT,&GPIO_InitStructure);

    while(1)
    {
    rt_kprintf("thread001:%d\r\n",count++);
    GPIO_ResetBits(LEDR_PORT,LEDR_PIN);
    rt_thread_delay(32);
    rt_kprintf("thread001:%d\r\n",count++);
    GPIO_SetBits(LEDR_PORT,LEDR_PIN);
    rt_thread_delay(32);
    }
}

int rt_application_init()
{
	rt_thread_init(&thread001,"led",rt_init_thread_entry001,RT_NULL,&thread001_stack[0], sizeof(thread001_stack),20,10);
	rt_thread_init(&thread002,"led2",rt_init_thread_entry002,RT_NULL,&thread002_stack[0], sizeof(thread002_stack),20,10);
	rt_thread_startup(&thread001);
	rt_thread_startup(&thread002);

    return 0;
}
