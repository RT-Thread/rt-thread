/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2009 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "stm32f10x.h"
#include "board.h"

static void rt_hw_console_init(void);

/**
 * @addtogroup STM32
 */

/*@{*/

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

    /*
     * set priority group:
     * 2 bits for pre-emption priority
     * 2 bits for subpriority
     */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
}

extern void rt_hw_interrupt_thread_switch(void);
/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_timer_handler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();

    rt_tick_increase();

    /* leave interrupt */
    rt_interrupt_leave();
}

/* NAND Flash */
#include "fsmc_nand.h"

/**
 * This function will initial STM32 Radio board.
 */
extern void FSMC_SRAM_Init(void);
void rt_hw_board_init()
{
    NAND_IDTypeDef NAND_ID;

    /* Configure the system clocks */
    SystemInit();

    /* DM9000A */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE,&GPIO_InitStructure);
        GPIO_SetBits(GPIOE,GPIO_Pin_5);
    }

#if LCD_VERSION == 2
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
        GPIO_Init(GPIOF,&GPIO_InitStructure);
    }
#endif

    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Config( SystemFrequency_SysClk / RT_TICK_PER_SECOND );

    /* Console Initialization*/
    rt_hw_console_init();
    rt_kprintf("\r\n\r\nSystemInit......\r\n");

    /* FSMC Initialization */
    FSMC_NAND_Init();

    /* NAND read ID command */
    FSMC_NAND_ReadID(&NAND_ID);
    rt_kprintf("Read the NAND ID:%02X%02X%02X%02X",NAND_ID.Maker_ID,NAND_ID.Device_ID,NAND_ID.Third_ID,NAND_ID.Fourth_ID);

    /* SRAM init */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    FSMC_SRAM_Init();

    /* memtest */
    {
        unsigned char * p_extram = (unsigned char *)0x68000000;
        unsigned int temp;

        rt_kprintf("\r\nmem testing....");
        for(temp=0; temp<0x80000; temp++)
        {
            *p_extram++ = (unsigned char)temp;
        }

        p_extram = (unsigned char *)0x68000000;
        for(temp=0; temp<0x80000; temp++)
        {
            if( *p_extram++ != (unsigned char)temp )
            {
                rt_kprintf("\rmemtest fail @ %08X\r\nsystem halt!!!!!",(unsigned int)p_extram);
                while(1);
            }
        }
        rt_kprintf("\rmem test pass!!\r\n");
    }/* memtest */

    {
        /* PC6 for SDCard Rst */
        GPIO_InitTypeDef GPIO_InitStructure;

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC,&GPIO_InitStructure);
        GPIO_SetBits(GPIOC,GPIO_Pin_6);
    }

    /* SPI1 config */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        SPI_InitTypeDef SPI_InitStructure;

        /* Enable SPI1 Periph clock */
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                               | RCC_APB2Periph_AFIO | RCC_APB2Periph_SPI1,
                               ENABLE);

        /* Configure SPI1 pins: PA5-SCK, PA6-MISO and PA7-MOSI */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

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
        SPI_CalculateCRC(SPI1, DISABLE);
    }

}/* rt_hw_board_init */

#if STM32_CONSOLE_USART == 1
#define CONSOLE_RX_PIN	GPIO_Pin_9
#define CONSOLE_TX_PIN	GPIO_Pin_10
#define CONSOLE_GPIO	GPIOA
#define CONSOLE_USART	USART1
#elif STM32_CONSOLE_USART == 2

#if defined(STM32_LD) || defined(STM32_MD)
#define CONSOLE_RX_PIN	GPIO_Pin_6
#define CONSOLE_TX_PIN	GPIO_Pin_5
#define CONSOLE_GPIO	GPIOD
#elif defined(STM32_HD)
#define CONSOLE_RX_PIN	GPIO_Pin_3
#define CONSOLE_TX_PIN	GPIO_Pin_2
#define CONSOLE_GPIO	GPIOA
#endif

#define CONSOLE_USART	USART2
#elif STM32_CONSOLE_USART == 2
#define CONSOLE_RX_PIN	GPIO_Pin_11
#define CONSOLE_TX_PIN	GPIO_Pin_10
#define CONSOLE_GPIO	GPIOB
#define CONSOLE_USART	USART3
#endif

/* init console to support rt_kprintf */
static void rt_hw_console_init(void)
{
    /* Enable USART1 and GPIOA clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1
                           | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC
                           | RCC_APB2Periph_GPIOF, ENABLE);

#if STM32_CONSOLE_USART == 0
#else
    /* GPIO configuration */
    {
        GPIO_InitTypeDef GPIO_InitStructure;

        /* Configure USART1 Tx (PA.09) as alternate function push-pull */
        GPIO_InitStructure.GPIO_Pin = CONSOLE_RX_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(CONSOLE_GPIO, &GPIO_InitStructure);

        /* Configure USART1 Rx (PA.10) as input floating */
        GPIO_InitStructure.GPIO_Pin = CONSOLE_TX_PIN;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_Init(CONSOLE_GPIO, &GPIO_InitStructure);
    }

    /* USART configuration */
    {
        USART_InitTypeDef USART_InitStructure;

        /* USART configured as follow:
            - BaudRate = 115200 baud
            - Word Length = 8 Bits
            - One Stop Bit
            - No parity
            - Hardware flow control disabled (RTS and CTS signals)
            - Receive and transmit enabled
            - USART Clock disabled
            - USART CPOL: Clock is active low
            - USART CPHA: Data is captured on the middle
            - USART LastBit: The clock pulse of the last data bit is not output to
              the SCLK pin
        */
        USART_InitStructure.USART_BaudRate = 115200;
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
        USART_InitStructure.USART_StopBits = USART_StopBits_1;
        USART_InitStructure.USART_Parity = USART_Parity_No;
        USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
        USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
        USART_Init(CONSOLE_USART, &USART_InitStructure);
        /* Enable USART1 */
        USART_Cmd(CONSOLE_USART, ENABLE);
    }
#endif
}

/* write one character to serial, must not trigger interrupt */
static void rt_hw_console_putc(const char c)
{
    /*
    	to be polite with serial console add a line feed
    	to the carriage return character
    */
    if (c=='\n')rt_hw_console_putc('\r');

    while (!(CONSOLE_USART->SR & USART_FLAG_TXE));
    CONSOLE_USART->DR = (c & 0x1FF);
}

/**
 * This function is used by rt_kprintf to display a string on console.
 *
 * @param str the displayed string
 */
void rt_hw_console_output(const char* str)
{
#if STM32_CONSOLE_USART == 0
    /* no console */
#else
    while (*str)
    {
        rt_hw_console_putc (*str++);
    }
#endif
}

/*@}*/
