#include "stm32f10x.h"
#include "rtthread.h"
#include "board.h"

#if (LCD_VERSION == 2)
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
#define TOUCH_MSR_Y  0x90   //读X轴坐标指令 addr:1
#define TOUCH_MSR_X  0xD0   //读Y轴坐标指令 addr:3


extern unsigned char SPI_WriteByte(unsigned char data);

//SPI写数据
static void WriteDataTo7843(unsigned char num)
{
    SPI_WriteByte(num);
}

//触摸处理
void Go_Touch(void)
{
    unsigned int X;
    unsigned int Y;

    CS_0();
    WriteDataTo7843(TOUCH_MSR_X | 1);                /* 发送读X坐标命令并关闭中断 */
    X = SPI_WriteByte(0x00)<<4;                      /* 读取第一字节MSB */
    X |= ((SPI_WriteByte(TOUCH_MSR_Y | 1)>>4)&0x0F );/* 读取第二字节 同时发送读Y轴坐标命令行*/
    Y = SPI_WriteByte(0x00)<<4;                      /* 读取第一字节MSB */
    Y |= ((SPI_WriteByte(1<<7)>>4)&0x0F );           /* 读取第二字节并重新打开中断 */
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
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIO_Init(GPIOB,&GPIO_InitStructure);
    }

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
    SPI_InitTypeDef SPI_InitStructure;

    rt_kprintf("\r\ntouch testing....\r\n");

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI1, DISABLE);

    /*------------------------ SPI1 configuration ------------------------*/
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;//SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS  = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;/* 72M/64=1.125M */
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    SPI_I2S_DeInit(SPI1);
    SPI_Init(SPI1, &SPI_InitStructure);

    /* Enable SPI_MASTER */
    SPI_Cmd(SPI1, ENABLE);

    NVIC_Configuration();
    exti_int_config();

    /* PC4 touch CS */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
        CS_1();
    }
    CS_0();
    WriteDataTo7843( 1<<7 ); /* 打开中断 */
    CS_1();
}
FINSH_FUNCTION_EXPORT(touch_test, touch_test)

void EXTI1_IRQHandler(void)
{
    EXTI_ClearITPendingBit(EXTI_Line1);
    Go_Touch();
}
#endif
