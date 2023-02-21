/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-28     luobeihai    first version
 */

#include "board.h"

void apm32_usart_init(void)
{
    GPIO_Config_T GPIO_ConfigStruct;

#ifdef BSP_USING_UART1
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_USART1);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_9;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART2
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART2);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_3;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART3
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB);
    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_USART3);

    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_11;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);
#endif

#ifdef BSP_USING_UART4
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC);

    RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_UART4);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_ConfigStruct.mode = GPIO_MODE_AF_PP;
    GPIO_ConfigStruct.pin = GPIO_PIN_10;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);

    /* Configure USART Rx as input floating */
    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_ConfigStruct.pin = GPIO_PIN_11;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);
#endif
}

void apm32_msp_spi_init(void *Instance)
{
#ifdef BSP_USING_SPI
    GPIO_Config_T gpioConfig;
    SPI_T *spi_x = (SPI_T *)Instance;

    if(spi_x == SPI3)
    {
        /* Enable related Clock */
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_SPI3);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOB | RCM_APB2_PERIPH_AFIO);

        GPIO_ConfigPinRemap(GPIO_REMAP_SWJ_JTAGDISABLE);

        /* Configure FLASH_SPI pins: SCK */
        gpioConfig.pin =  GPIO_PIN_3;
        gpioConfig.mode = GPIO_MODE_AF_PP;
        gpioConfig.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MOSI */
        gpioConfig.pin = GPIO_PIN_5;
        GPIO_Config(GPIOB, &gpioConfig);

        /* Configure FLASH_SPI pins: MISO */
        gpioConfig.pin = GPIO_PIN_4;
        gpioConfig.mode = GPIO_MODE_IN_FLOATING;
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
        RCM_EnableAPB1PeriphClock(RCM_APB1_PERIPH_TMR3);
        RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_AFIO);

        GPIO_ConfigPinRemap(GPIO_FULL_REMAP_TMR3);

        /* TMR3 channel 1 gpio config */
        gpio_config.pin = GPIO_PIN_6;
        gpio_config.mode = GPIO_MODE_AF_PP;
        gpio_config.speed = GPIO_SPEED_50MHz;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 2 gpio config */
        gpio_config.pin = GPIO_PIN_7;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 3 gpio config */
        gpio_config.pin = GPIO_PIN_8;
        GPIO_Config(GPIOC, &gpio_config);

        /* TMR3 channel 4 gpio config */
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
    /* TODO */
}

/*
 * GPIO Configuration for ETH
 */
void ETH_GPIO_Configuration(void)
{
#ifdef BSP_USING_ETH
    GPIO_Config_T GPIO_ConfigStruct;

    /* Enable SYSCFG clock */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_AFIO);

    /* Enable GPIOs clocks */
    RCM_EnableAPB2PeriphClock(RCM_APB2_PERIPH_GPIOA | RCM_APB2_PERIPH_GPIOB
        | RCM_APB2_PERIPH_GPIOC | RCM_APB2_PERIPH_GPIOD);

    /* ETHERNET pins remapp in APM32107-EVAL board: RX_DV and RxD[3:0] */
    GPIO_ConfigPinRemap(GPIO_REMAP_ETH_MAC);

    /* MII/RMII Media interface selection */
    GPIO_ConfigPinRemap(GPIO_REMAP_MACEISEL_RMII);

    /*********************** Ethernet pins configuration ***************************/
    /*
        ETH_MDIO -------------------------> PA2
        ETH_MDC --------------------------> PC1
        ETH_MII_RX_CLK/ETH_RMII_REF_CLK---> PA1
        ETH_MII_RX_DV/ETH_RMII_CRS_DV ----> PD8
        ETH_MII_RXD0/ETH_RMII_RXD0 -------> PD9
        ETH_MII_RXD1/ETH_RMII_RXD1 -------> PD10
        ETH_MII_TX_EN/ETH_RMII_TX_EN -----> PB11
        ETH_MII_TXD0/ETH_RMII_TXD0 -------> PB12
        ETH_MII_TXD1/ETH_RMII_TXD1 -------> PB13
    */
    GPIO_ConfigStruct.pin = GPIO_PIN_1;
    GPIO_ConfigStruct.mode  = GPIO_MODE_IN_FLOATING;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_ConfigStruct.mode = GPIO_MODE_IN_FLOATING;
    GPIO_Config(GPIOD, &GPIO_ConfigStruct);

    /* Configure PA2 */
    GPIO_ConfigStruct.pin = GPIO_PIN_2;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_ConfigStruct.mode  = GPIO_MODE_AF_PP;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    GPIO_ConfigStruct.pin = GPIO_PIN_1;
    GPIO_Config(GPIOC, &GPIO_ConfigStruct);

    /* Configure PB11, PB12, PB13 as alternate function push-pull */
    GPIO_ConfigStruct.pin = GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);

    /* ETH and CAN shared PB8, RMII Mode PB8 Must be output low */
    GPIO_ConfigStruct.pin = GPIO_PIN_8;
    GPIO_ConfigStruct.mode = GPIO_MODE_OUT_PP;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_Config(GPIOB, &GPIO_ConfigStruct);
    GPIO_ResetBit(GPIOB, GPIO_PIN_8);

    /* Configure PA8 output 25MHz clock */
    GPIO_ConfigStruct.pin = GPIO_PIN_8;
    GPIO_ConfigStruct.speed = GPIO_SPEED_50MHz;
    GPIO_ConfigStruct.mode  = GPIO_MODE_AF_PP;
    GPIO_Config(GPIOA, &GPIO_ConfigStruct);

    /* Set PLL3 clock output to 50MHz (25MHz /5 *10 =50MHz) */
    RCM_ConfigPLL3(RCM_PLL3MF_10);

    /* Enable PLL3 */
    RCM_EnablePLL3();

    /* Wait till PLL3 is ready */
    while(RCM_ReadStatusFlag(RCM_FLAG_PLL3RDY) == RESET);

    /* Get PLL3 clock on PA8 pin (MCO) */
    RCM_ConfigMCO(RCM_MCOCLK_PLL3CLK);
#endif
}
