/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
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
#include "ch32f20x_rcc.h"

rt_uint32_t ch32_get_sysclock_frequency(void)
{
    RCC_ClocksTypeDef RCC_Clocks;

    RCC_GetClocksFreq(&RCC_Clocks);

    return RCC_Clocks.SYSCLK_Frequency;
}

void ch32f2_usart_clock_and_io_init(USART_TypeDef *usartx)
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

    if (usartx == UART4)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        /* UART4 TX-->C.10   RX-->C.11 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    if (usartx == UART5)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

        /* UART5 TX-->C.12   RX-->D.2 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }

    if (usartx == UART6)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART6, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        /* UART6 TX-->C.0   RX-->C.1 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    if (usartx == UART7)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        /* UART7 TX-->C.2   RX-->C.3 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    if (usartx == UART8)
    {

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        /* UART8 TX-->C.4   RX-->C.5 */
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }
}

void ch32f2_spi_clock_and_io_init(SPI_TypeDef *spix)
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

    if (spix == SPI3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }
}

rt_uint32_t ch32f2_spi_clock_get(SPI_TypeDef *spix)
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

    if (spix == SPI3)
    {
        return RCC_Clocks.PCLK1_Frequency;
    }

    return RCC_Clocks.PCLK2_Frequency;
}

void ch32f2_i2c_clock_and_io_init(I2C_TypeDef *i2cx)
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

void ch32f2_i2c_config(I2C_TypeDef *i2cx)
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

#ifdef BSP_USING_HWTIMER
void ch32f2_tim_clock_init(TIM_TypeDef *timx)
{
    if (timx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    }

    if (timx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    }

    if (timx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    }

    if (timx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    }

    if (timx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    }

    if (timx == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
    }

    if (timx == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
    }

    if (timx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
    }

    if (timx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    }

    if (timx == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    }
}

rt_uint32_t ch32f2_tim_clock_get(TIM_TypeDef *timx)
{
    RCC_ClocksTypeDef RCC_Clocks;
    rt_uint32_t rcc_cfgr0;
    rt_uint8_t ppre1, ppre2;

    RCC_GetClocksFreq(&RCC_Clocks);

    rcc_cfgr0 = RCC->CFGR0;

    ppre1 = (rcc_cfgr0 >> 8) & 0x7;  // CFGR0[10:8]
    ppre2 = (rcc_cfgr0 >> 11) & 0x7; // CFGR0[13:11]

    if (timx == TIM1 || timx == TIM8 || timx == TIM9 || timx == TIM10)
    {
        return ppre2 >= 4 ? RCC_Clocks.PCLK2_Frequency * 2 : RCC_Clocks.PCLK2_Frequency;
    }

    // TIM2~7
    return ppre1 >= 4 ? RCC_Clocks.PCLK1_Frequency * 2 : RCC_Clocks.PCLK1_Frequency;
}

struct rt_hwtimer_info hwtimer_info1 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info2 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info3 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info4 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info5 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info6 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info7 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info8 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info9 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info hwtimer_info10 =
    {
        .maxfreq = 1000000,
        .minfreq = 2000,
        .maxcnt = 0xFFFF,
        .cntmode = HWTIMER_CNTMODE_UP,

};

struct rt_hwtimer_info *ch32f2_hwtimer_info_config_get(TIM_TypeDef *timx)
{
    struct rt_hwtimer_info *info = RT_NULL;

    if (timx == TIM1)
    {
        info = &hwtimer_info1;
    }
    else if (timx == TIM2)
    {
        info = &hwtimer_info2;
    }
    else if (timx == TIM3)
    {
        info = &hwtimer_info3;
    }
    else if (timx == TIM4)
    {
        info = &hwtimer_info4;
    }
    else if (timx == TIM4)
    {
        info = &hwtimer_info4;
    }
    else if (timx == TIM5)
    {
        info = &hwtimer_info5;
    }
    else if (timx == TIM6)
    {
        info = &hwtimer_info6;
    }
    else if (timx == TIM7)
    {
        info = &hwtimer_info7;
    }
    else if (timx == TIM8)
    {
        info = &hwtimer_info8;
    }
    else if (timx == TIM9)
    {
        info = &hwtimer_info9;
    }
    else if (timx == TIM10)
    {
        info = &hwtimer_info10;
    }

    return info;
}

void ch32f2_pwm_io_init(TIM_TypeDef *timx, rt_uint8_t channel)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    if (timx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
    }

    if (timx == TIM2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
    }

    if (timx == TIM3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
    }

    if (timx == TIM4)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOB, &GPIO_InitStructure);
        }
    }

    if (timx == TIM5)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
    }

    if (timx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
    }

    if (timx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
    }

    if (timx == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        if (channel == TIM_Channel_1)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_2)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_3)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOA, &GPIO_InitStructure);
        }
        if (channel == TIM_Channel_4)
        {
            GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(GPIOC, &GPIO_InitStructure);
        }
    }
}
#endif
