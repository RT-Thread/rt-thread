/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-10     luobeihai    first version
 */

#include "board.h"

void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_9, GPIO_AF_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_UP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_10, GPIO_AF_USART1);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF;
    GPIO_ConfigStruct.pin = GPIO_PIN_3;
    GPIO_ConfigStruct.pupd = GPIO_PUPD_UP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_3, GPIO_AF_USART2);
#endif
}

void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI
    GPIO_Config_T gpioConfig;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI1)
    {
        /* Enable related Clock */
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SPI1);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

        /* Config SPI1 PinAF */
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_3, GPIO_AF_SPI1);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_4, GPIO_AF_SPI1);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_5, GPIO_AF_SPI1);

        /* Config SPI GPIO, SCK=PB3, MISO=PB4, MOSI=PB5 */
        GPIO_ConfigStructInit(&gpioConfig);
        gpioConfig.pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5;
        gpioConfig.speed = GPIO_SPEED_100MHz;
        gpioConfig.mode = GPIO_MODE_AF;
        gpioConfig.otype = GPIO_OTYPE_PP;
        gpioConfig.pupd = GPIO_PUPD_NOPULL;
        GPIO_Config(GPIOB, &gpioConfig);
    }
#endif
}

void apm32_msp_timer_init(void *Instance)
{
#ifdef BSP_USING_PWM
    GPIO_Config_T gpio_config;
    TMR_T *tmr_x = (TMR_T *)Instance;

    if (tmr_x == TMR3)
    {
        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC);
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);

        /* TMR3 channel 1 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_6, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF;
        gpio_config.otype = GPIO_OTYPE_PP;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_7, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_8, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio init */
        GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_9, GPIO_AF_TMR3);
        gpio_config.pin = GPIO_PIN_9;
        GPIO_Config(GPIOC, &gpio_config);
    }
#endif
}

/*
 * phy reset
 */
void phy_reset(void)
{
#ifdef BSP_USING_ETH
    /* PHY RESET PIN: PD11 */
    GPIO_Config_T GPIO_ConfigStruct;

    GPIO_ConfigStruct.mode  = GPIO_MODE_OUT;
    GPIO_ConfigStruct.speed = GPIO_SPEED_2MHz;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.pupd  = GPIO_PUPD_NOPULL;

    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOD);

    GPIO_ConfigStruct.pin = GPIO_PIN_11;
    GPIO_Config(GPIOD, &GPIO_ConfigStruct);

    GPIO_ResetBit(GPIOD, GPIO_PIN_11);
    rt_thread_delay(2);
    GPIO_SetBit(GPIOD, GPIO_PIN_11);
    rt_thread_delay(2);
#endif
}

/*
 * GPIO Configuration for ETH
 */
void apm32_msp_eth_init(void *instance)
{
#ifdef BSP_USING_ETH
    GPIO_Config_T GPIO_ConfigStruct;

    /* Enable SYSCFG clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SYSCFG);

    /* Enable GPIOs clocks */
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOA | RCM_AHB1_PERIPH_GPIOC | RCM_AHB1_PERIPH_GPIOG);

    /* MII/RMII Media interface selection */
    SYSCFG_ConfigMediaInterface(SYSCFG_INTERFACE_RMII);

    /*********************** Ethernet pins configuration ***************************/
    /*
        ETH_MDIO -------------------------> PA2
        ETH_MDC --------------------------> PC1
        ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
        ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PA7
        ETH_MII_RXD0/ETH_RMII_RXD0 -------> PC4
        ETH_MII_RXD1/ETH_RMII_RXD1 -------> PC5
        ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PG11
        ETH_MII_TXD0/ETH_RMII_TXD0 -------> PG13
        ETH_MII_TXD1/ETH_RMII_TXD1 -------> PG14
    */
    /* Configure PC1, PC4 and PC5 */
    GPIO_ConfigStruct.pin = GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5;
    GPIO_ConfigStruct.speed = GPIO_SPEED_100MHz;
    GPIO_ConfigStruct.mode  = GPIO_MODE_AF;
    GPIO_ConfigStruct.otype = GPIO_OTYPE_PP;
    GPIO_ConfigStruct.pupd  = GPIO_PUPD_NOPULL;

    GPIO_Config(GPIOC, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_1, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_4, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOC, GPIO_PIN_SOURCE_5, GPIO_AF_ETH);

    /* Configure PG11, PG13 and PG14 */
    GPIO_ConfigStruct.pin =  GPIO_PIN_11 | GPIO_PIN_13 | GPIO_PIN_14;
    GPIO_Config(GPIOG, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_11, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_13, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOG, GPIO_PIN_SOURCE_14, GPIO_AF_ETH);

    /* Configure PA1, PA2 and PA7 */
    GPIO_ConfigStruct.pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_1, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_2, GPIO_AF_ETH);
    GPIO_ConfigPinAF(GPIOA, GPIO_PIN_SOURCE_7, GPIO_AF_ETH);
#endif
}

void apm32_msp_sdio_init(void *Instance)
{
#ifdef BSP_USING_SDIO
    GPIO_Config_T  GPIO_InitStructure;

    /* Enable the GPIO Clock */
    RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOC | RCM_AHB1_PERIPH_GPIOD);

    /* Enable the SDIO Clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_SDIO);

    /* Enable the SDIO peripheral reset */
    RCM_EnableAPB2PeriphReset(RCM_APB2_PERIPH_SDIO);

    /* Configure the GPIO pin */
    GPIO_InitStructure.pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
    GPIO_InitStructure.mode = GPIO_MODE_AF;
    GPIO_InitStructure.speed = GPIO_SPEED_50MHz;
    GPIO_InitStructure.otype = GPIO_OTYPE_PP;
    GPIO_InitStructure.pupd = GPIO_PUPD_UP;
    GPIO_Config(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.pin = GPIO_PIN_2;
    GPIO_Config(GPIOD, &GPIO_InitStructure);

    GPIO_ConfigPinAF(GPIOC,GPIO_PIN_SOURCE_8, GPIO_AF_SDIO);
    GPIO_ConfigPinAF(GPIOC,GPIO_PIN_SOURCE_9, GPIO_AF_SDIO);
    GPIO_ConfigPinAF(GPIOC,GPIO_PIN_SOURCE_10, GPIO_AF_SDIO);
    GPIO_ConfigPinAF(GPIOC,GPIO_PIN_SOURCE_11, GPIO_AF_SDIO);
    GPIO_ConfigPinAF(GPIOC,GPIO_PIN_SOURCE_12, GPIO_AF_SDIO);
    GPIO_ConfigPinAF(GPIOD,GPIO_PIN_SOURCE_2, GPIO_AF_SDIO);

    /* Disable the SDIO peripheral reset */
    RCM_DisableAPB2PeriphReset(RCM_APB2_PERIPH_SDIO);
#endif
}

void apm32_msp_can_init(void *Instance)
{
#if defined(BSP_USING_CAN1) || defined(BSP_USING_CAN2)
    GPIO_Config_T  GPIO_InitStructure;
    CAN_T *CANx = (CAN_T *)Instance;

    if (CAN1 == CANx)
    {
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);

        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);

        /* PB8: CAN1_RX, PB9: CAN1_TX */
        GPIO_InitStructure.pin = GPIO_PIN_8 | GPIO_PIN_9;
        GPIO_InitStructure.mode = GPIO_MODE_AF;
        GPIO_InitStructure.otype = GPIO_OTYPE_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_100MHz;
        GPIO_InitStructure.pupd = GPIO_PUPD_UP;
        GPIO_Config(GPIOB, &GPIO_InitStructure);

        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_8, GPIO_AF_CAN1);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_9, GPIO_AF_CAN1);
    }
    else if (CAN2 == CANx)
    {
        /* When using the CAN2 peripheral, the CAN1 clock must be turned on */
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN1);
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_CAN2);

        RCM_EnableAHB1PeriphClock(RCM_AHB1_PERIPH_GPIOB);

        /* PB12: CAN2_RX, PB13: CAN2_TX */
        GPIO_InitStructure.pin = GPIO_PIN_12 | GPIO_PIN_13;
        GPIO_InitStructure.mode = GPIO_MODE_AF;
        GPIO_InitStructure.otype = GPIO_OTYPE_PP;
        GPIO_InitStructure.speed = GPIO_SPEED_100MHz;
        GPIO_InitStructure.pupd = GPIO_PUPD_UP;
        GPIO_Config(GPIOB, &GPIO_InitStructure);

        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_12, GPIO_AF_CAN2);
        GPIO_ConfigPinAF(GPIOB, GPIO_PIN_SOURCE_13, GPIO_AF_CAN2);
    }
#endif
}
