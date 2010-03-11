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

static void all_device_reset(void)
{
    /* RESET */
    /* DM9000A     PE5  */
    /* LCD         PF10 */
    /* SPI-FLASH   PA3  */

    /*  CS */
    /* DM9000A FSMC_NE4 PG12 */
    /* LCD     FSMC_NE2 PG9  */
    /* SPI_FLASH        PA4  */
    /* CODEC            PC5  */
    /* TOUCH            PC4  */

    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE
                           | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG,ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    /* SPI_FLASH CS */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_SetBits(GPIOA,GPIO_Pin_4);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    /* CODEC && TOUCH CS */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
    GPIO_SetBits(GPIOC,GPIO_Pin_4 | GPIO_Pin_5);

    /*  DM9000A RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOE,GPIO_Pin_5);

    /* LCD RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOF,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOF,GPIO_Pin_10);

    /* SPI_FLASH RESET */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_3);

    /* FSMC GPIO configure */
    {
        GPIO_InitTypeDef GPIO_InitStructure;
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF
                               | RCC_APB2Periph_GPIOG, ENABLE);
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);

        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

        /*
        FSMC_D0 ~ FSMC_D3
        PD14 FSMC_D0   PD15 FSMC_D1   PD0  FSMC_D2   PD1  FSMC_D3
        */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_Init(GPIOD,&GPIO_InitStructure);

        /*
        FSMC_D4 ~ FSMC_D12
        PE7 ~ PE15  FSMC_D4 ~ FSMC_D12
        */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10
                                      | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_Init(GPIOE,&GPIO_InitStructure);

        /* FSMC_D13 ~ FSMC_D15   PD8 ~ PD10 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
        GPIO_Init(GPIOD,&GPIO_InitStructure);

        /*
        FSMC_A0 ~ FSMC_A5   FSMC_A6 ~ FSMC_A9
        PF0     ~ PF5       PF12    ~ PF15
        */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3
                                      | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
        GPIO_Init(GPIOF,&GPIO_InitStructure);

        /* FSMC_A10 ~ FSMC_A15  PG0 ~ PG5 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
        GPIO_Init(GPIOG,&GPIO_InitStructure);

        /* FSMC_A16 ~ FSMC_A18  PD11 ~ PD13 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
        GPIO_Init(GPIOD,&GPIO_InitStructure);

        /* RD-PD4 WR-PD5 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
        GPIO_Init(GPIOD,&GPIO_InitStructure);

        /* NBL0-PE0 NBL1-PE1 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_Init(GPIOE,&GPIO_InitStructure);

        /* NE1/NCE2 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
        GPIO_Init(GPIOD,&GPIO_InitStructure);
        /* NE2 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_Init(GPIOG,&GPIO_InitStructure);
        /* NE3 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_Init(GPIOG,&GPIO_InitStructure);
        /* NE4 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_Init(GPIOG,&GPIO_InitStructure);
    }
    /* FSMC GPIO configure */

    GPIO_SetBits(GPIOE,GPIO_Pin_5);  /* DM9000A   */
    GPIO_SetBits(GPIOF,GPIO_Pin_10); /* LCD       */
    GPIO_SetBits(GPIOA,GPIO_Pin_3);  /* SPI_FLASH */
}

/**
 * This function will initial STM32 Radio board.
 */
extern void FSMC_SRAM_Init(void);
void rt_hw_board_init()
{
    //NAND_IDTypeDef NAND_ID;

    /* Configure the system clocks */
    SystemInit();

    all_device_reset();

    /* NVIC Configuration */
    NVIC_Configuration();

    /* Configure the SysTick */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );

    /* Console Initialization*/
	rt_hw_usart_init();
	rt_console_set_device("uart1");

    rt_kprintf("\r\n\r\nSystemInit......\r\n");

    /* SRAM init */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    FSMC_SRAM_Init();

    /* memtest */
    {
        unsigned char * p_extram = (unsigned char *)STM32_EXT_SRAM_BEGIN;
        unsigned int temp;

        rt_kprintf("\r\nmem testing....");
        for(temp=0; temp<(STM32_EXT_SRAM_END-STM32_EXT_SRAM_BEGIN); temp++)
        {
            *p_extram++ = (unsigned char)temp;
        }

        p_extram = (unsigned char *)STM32_EXT_SRAM_BEGIN;
        for(temp=0; temp<(STM32_EXT_SRAM_END-STM32_EXT_SRAM_BEGIN); temp++)
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
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;/* 72M/64=1.125M */
        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        SPI_InitStructure.SPI_CRCPolynomial = 7;

        SPI_I2S_DeInit(SPI1);
        SPI_Init(SPI1, &SPI_InitStructure);

        /* Enable SPI_MASTER */
        SPI_Cmd(SPI1, ENABLE);
        SPI_CalculateCRC(SPI1, DISABLE);
    }

}/* rt_hw_board_init */

/*@}*/
