/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-08-10     charlown           first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include "board.h"
#include "ch32f10x_rcc.h"

rt_uint32_t ch32_get_sysclock_frequency(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);

    return RCC_Clocks.SYSCLK_Frequency;
}

void ch32f1_usart_clock_and_io_init(USART_TypeDef *usartx)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    if (usartx == USART1)
    {

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        /* USART1 TX-->A.9   RX-->A.10 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

    if (usartx == USART2)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        /* USART2 TX-->A.2   RX-->A.3 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

    if (usartx == USART3)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        /* USART3 TX-->C.10   RX-->C.11 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
    }
}

void ch32f1_spi_clock_and_io_init(SPI_TypeDef *spix)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    if (spix == SPI1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }

    if (spix == SPI2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
}

rt_uint32_t ch32f1_spi_clock_get(SPI_TypeDef *spix)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);

    if (spix == SPI1)
    {
        return RCC_Clocks.PCLK2_Frequency;
    }

    if (spix == SPI2)
    {
        return RCC_Clocks.PCLK1_Frequency;
    }

    return RCC_Clocks.PCLK2_Frequency; 
}

void ch32f1_i2c_clock_and_io_init(I2C_TypeDef *i2cx)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;

    if (i2cx == I2C1)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);
    }

    if (i2cx == I2C2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
}

void ch32f1_i2c_config(I2C_TypeDef *i2cx)
{

    I2C_InitTypeDef I2C_InitTSturcture;

    if (i2cx == I2C1)
    {
        I2C_InitTSturcture.I2C_ClockSpeed = 100000;
        I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
        I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
        I2C_InitTSturcture.I2C_OwnAddress1 = 0;
        I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
        I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
        I2C_Init(I2C1, &I2C_InitTSturcture);

        I2C_Cmd(I2C1, ENABLE);
        I2C_AcknowledgeConfig(I2C1, ENABLE);
    }

    if (i2cx == I2C2)
    {
        I2C_InitTSturcture.I2C_ClockSpeed = 100000;
        I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
        I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
        I2C_InitTSturcture.I2C_OwnAddress1 = 0;
        I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
        I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
        I2C_Init(I2C2, &I2C_InitTSturcture);

        I2C_Cmd(I2C2, ENABLE);
        I2C_AcknowledgeConfig(I2C2, ENABLE);
    }
}


