#include "stm32f10x.h"
#include "rtthread.h"

static void Delay_Nus(unsigned int dt)
{
    volatile unsigned int a;
    while (--dt)
    {
        for (a=0; a<5000; a++);
    }
}

/*
MISO PA6
MOSI PA7
CLK  PA5
CS   PC4
*/

#define   CS_0()          GPIO_ResetBits(GPIOC,GPIO_Pin_4)
#define   CS_1()          GPIO_SetBits(GPIOC,GPIO_Pin_4)

/*
7  6 - 4  3      2     1-0
s  A2-A0 MODE SER/DFR PD1-PD0
*/
#define TOUCH_MSR_X  0x90   //读X轴坐标指令 addr:1
#define TOUCH_MSR_Y  0xD0   //读Y轴坐标指令 addr:3


extern unsigned char SPI_WriteByte(unsigned char data);

//SPI写数据
static void WriteDataTo7843(unsigned char num)
{
    SPI_WriteByte(num);
}

//SPI 读数据
static unsigned int ReadDataFrom7843(void)
{
    unsigned int temp;
    temp = SPI_WriteByte(0x00)<<4;
    temp |= ( (SPI_WriteByte(0x00)>>4)&0x0F );
    return temp;
}

//触摸处理
void Go_Touch(void)
{
    unsigned int X;
    unsigned int Y;

    CS_0();
    WriteDataTo7843(TOUCH_MSR_X);     //送控制字 10010000 即用差分方式读X坐标 详细请见有关资料
    Delay_Nus(100);
    Y = ReadDataFrom7843();           //读X轴坐标
    WriteDataTo7843(TOUCH_MSR_Y);     //送控制字 11010000 即用差分方式读Y坐标 详细请见有关资料
    Delay_Nus(50);
    X = ReadDataFrom7843();           //读Y轴坐标
    CS_1();

    rt_kprintf("\r\nX: %04d Y: %04d",X,Y);
}

static void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the EXTI0 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void exti_int_config(void)
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* PB1 touch INT */

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);

    /* Configure  EXTI  */
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//Falling下降沿 Rising上升
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    EXTI_ClearITPendingBit(EXTI_Line1);
}

#include <finsh.h>
void touch_test(void)
{
    rt_kprintf("\r\ntouch testing....\r\n");

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);


    NVIC_Configuration();
    exti_int_config();

    /* PC4 touch CS */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB,&GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
        CS_1();
    }
    Delay_Nus( 500 );

    CS_0();
    WriteDataTo7843(0x00);
    CS_1();
}
FINSH_FUNCTION_EXPORT(touch_test, touch_test)

void EXTI1_IRQHandler(void)
{
    EXTI_ClearITPendingBit(EXTI_Line1);
    Go_Touch();
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics */
