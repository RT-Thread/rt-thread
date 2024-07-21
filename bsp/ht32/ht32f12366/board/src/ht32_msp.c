/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#include "ht32_msp.h"

/* GPIO configuration for UART */
#ifdef BSP_USING_UART
void ht32_usart_gpio_init(void *instance)
{
    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};
    HT_USART_TypeDef *usart_x = (HT_USART_TypeDef *)instance;
#ifdef BSP_USING_USART0
    if(HT_USART0 == usart_x)
    {
        CKCUClock.Bit.HTCFG_USART0_TX_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_USART0_RX_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Turn on UxART Rx internal pull up resistor to prevent unknow state */
        GPIO_PullResistorConfig(HTCFG_USART0_RX_GPIO_PORT,HTCFG_USART0_RX_GPIO_PIN,GPIO_PR_UP);
        /* Config AFIO mode as UxART function */
        AFIO_GPxConfig(HTCFG_USART0_TX_GPIO_ID,HTCFG_USART0_TX_GPIO_PIN,AFIO_FUN_USART_UART);
        AFIO_GPxConfig(HTCFG_USART0_RX_GPIO_ID,HTCFG_USART0_RX_GPIO_PIN,AFIO_FUN_USART_UART);
    }
#endif
#ifdef BSP_USING_USART1
    if(HT_USART1 == usart_x)
    {
        CKCUClock.Bit.HTCFG_USART1_TX_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_USART1_RX_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Turn on UxART Rx internal pull up resistor to prevent unknow state */
        GPIO_PullResistorConfig(HTCFG_USART1_RX_GPIO_PORT,HTCFG_USART1_RX_GPIO_PIN,GPIO_PR_UP);
        /* Config AFIO mode as UxART function */
        AFIO_GPxConfig(HTCFG_USART1_TX_GPIO_ID,HTCFG_USART1_TX_GPIO_PIN,AFIO_FUN_USART_UART);
        AFIO_GPxConfig(HTCFG_USART1_RX_GPIO_ID,HTCFG_USART1_RX_GPIO_PIN,AFIO_FUN_USART_UART);
    }
#endif
#ifdef BSP_USING_UART0
    if(HT_UART0 == usart_x)
    {
        CKCUClock.Bit.HTCFG_UART0_TX_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_UART0_RX_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Turn on UxART Rx internal pull up resistor to prevent unknow state */
        GPIO_PullResistorConfig(HTCFG_UART0_RX_GPIO_PORT,HTCFG_UART0_RX_GPIO_PIN,GPIO_PR_UP);
        /* Config AFIO mode as UxART function */
        AFIO_GPxConfig(HTCFG_UART0_TX_GPIO_ID,HTCFG_UART0_TX_GPIO_PIN,AFIO_FUN_USART_UART);
        AFIO_GPxConfig(HTCFG_UART0_RX_GPIO_ID,HTCFG_UART0_RX_GPIO_PIN,AFIO_FUN_USART_UART);
    }
#endif
#ifdef BSP_USING_UART1
    if(HT_UART1 == usart_x)
    {
        CKCUClock.Bit.HTCFG_UART1_TX_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_UART1_RX_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Turn on UxART Rx internal pull up resistor to prevent unknow state */
        GPIO_PullResistorConfig(HTCFG_UART1_RX_GPIO_PORT,HTCFG_UART1_RX_GPIO_PIN,GPIO_PR_UP);
        /* Config AFIO mode as UxART function */
        AFIO_GPxConfig(HTCFG_UART1_TX_GPIO_ID,HTCFG_UART1_TX_GPIO_PIN,AFIO_FUN_USART_UART);
        AFIO_GPxConfig(HTCFG_UART1_RX_GPIO_ID,HTCFG_UART1_RX_GPIO_PIN,AFIO_FUN_USART_UART);
    }
#endif
}
#endif

/* GPIO configuration for SPI */
#ifdef BSP_USING_SPI
void ht32_spi_gpio_init(void *instance)
{
    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};
    HT_SPI_TypeDef *spi_x = (HT_SPI_TypeDef *)instance;
#ifdef BSP_USING_SPI0
    if(HT_SPI0 == spi_x)
    {
        CKCUClock.Bit.HTCFG_SPI0_SCK_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_SPI0_MISO_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_SPI0_MOSI_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);

        AFIO_GPxConfig(HTCFG_SPI0_SCK_GPIO_ID, HTCFG_SPI0_SCK_GPIO_PIN, AFIO_FUN_SPI);
        AFIO_GPxConfig(HTCFG_SPI0_MISO_GPIO_ID, HTCFG_SPI0_MISO_GPIO_PIN, AFIO_FUN_SPI);
        AFIO_GPxConfig(HTCFG_SPI0_MOSI_GPIO_ID, HTCFG_SPI0_MOSI_GPIO_PIN, AFIO_FUN_SPI);
    }
#endif
#ifdef BSP_USING_SPI1
    if(HT_SPI1 == spi_x)
    {
        CKCUClock.Bit.HTCFG_SPI1_SCK_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_SPI1_MISO_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_SPI1_MOSI_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);

        AFIO_GPxConfig(HTCFG_SPI1_SCK_GPIO_ID, HTCFG_SPI1_SCK_GPIO_PIN, AFIO_FUN_SPI);
        AFIO_GPxConfig(HTCFG_SPI1_MISO_GPIO_ID, HTCFG_SPI1_MISO_GPIO_PIN, AFIO_FUN_SPI);
        AFIO_GPxConfig(HTCFG_SPI1_MOSI_GPIO_ID, HTCFG_SPI1_MOSI_GPIO_PIN, AFIO_FUN_SPI);
    }
#endif
}
#endif

/* GPIO configuration for I2C */
#ifdef BSP_USING_I2C_HW
void ht32_hardware_i2c_gpio_init(void *instance)
{
    CKCU_PeripClockConfig_TypeDef   CKCUClock = {{0}};
    HT_I2C_TypeDef *i2c_x = (HT_I2C_TypeDef *)instance;
#ifdef BSP_USING_I2C0_HW
    if(HT_I2C0 == i2c_x)
    {
        CKCUClock.Bit.HTCFG_I2C0_SCL_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_I2C0_SDA_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Configure GPIO to I2C mode */
        AFIO_GPxConfig(HTCFG_I2C0_SCL_GPIO_ID,HTCFG_I2C0_SCL_GPIO_PIN,AFIO_FUN_I2C);
        AFIO_GPxConfig(HTCFG_I2C0_SDA_GPIO_ID,HTCFG_I2C0_SDA_GPIO_PIN,AFIO_FUN_I2C);
    }
#endif
#ifdef BSP_USING_I2C1_HW
    if(HT_I2C1 == i2c_x)
    {
        CKCUClock.Bit.HTCFG_I2C1_SCL_GPIO_CLK = 1;
        CKCUClock.Bit.HTCFG_I2C1_SDA_GPIO_CLK = 1;
        CKCU_PeripClockConfig(CKCUClock,ENABLE);
        /* Configure GPIO to I2C mode */
        AFIO_GPxConfig(HTCFG_I2C1_SCL_GPIO_ID,HTCFG_I2C1_SCL_GPIO_PIN,AFIO_FUN_I2C);
        AFIO_GPxConfig(HTCFG_I2C1_SDA_GPIO_ID,HTCFG_I2C1_SDA_GPIO_PIN,AFIO_FUN_I2C);
    }
#endif
}
#endif
/* GPIO configuration for ADC */
#ifdef BSP_USING_ADC
void ht32_adc_gpio_init(void *instance,int8_t channel)
{
    CKCU_PeripClockConfig_TypeDef CKCUClock = {{ 0 }};
    HT_ADC_TypeDef *adc_x = (HT_ADC_TypeDef *)instance;
#ifdef BSP_USING_ADC0
    if (HT_ADC0 == adc_x)
    {
        /* Enable peripheral clock */
        CKCUClock.Bit.AFIO = 1;
        CKCUClock.Bit.ADC0 = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);

        /* Configure AFIO mode as ADC function */
        switch(channel)
        {
            case 0:
                AFIO_GPxConfig(HTCFG_ADC0CH0_GPIO_ID, HTCFG_ADC0CH0_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 1:
                AFIO_GPxConfig(HTCFG_ADC0CH1_GPIO_ID, HTCFG_ADC0CH1_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 2:
                AFIO_GPxConfig(HTCFG_ADC0CH2_GPIO_ID, HTCFG_ADC0CH2_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 3:
                AFIO_GPxConfig(HTCFG_ADC0CH3_GPIO_ID, HTCFG_ADC0CH3_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 4:
                AFIO_GPxConfig(HTCFG_ADC0CH4_GPIO_ID, HTCFG_ADC0CH4_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 5:
                AFIO_GPxConfig(HTCFG_ADC0CH5_GPIO_ID, HTCFG_ADC0CH5_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 6:
                AFIO_GPxConfig(HTCFG_ADC0CH6_GPIO_ID, HTCFG_ADC0CH6_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 7:
                AFIO_GPxConfig(HTCFG_ADC0CH7_GPIO_ID, HTCFG_ADC0CH7_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 8:
                AFIO_GPxConfig(HTCFG_ADC0CH8_GPIO_ID, HTCFG_ADC0CH8_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 9:
                AFIO_GPxConfig(HTCFG_ADC0CH9_GPIO_ID, HTCFG_ADC0CH9_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 10:
                AFIO_GPxConfig(HTCFG_ADC0CH10_GPIO_ID, HTCFG_ADC0CH10_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 11:
                AFIO_GPxConfig(HTCFG_ADC0CH11_GPIO_ID, HTCFG_ADC0CH11_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 12:
                AFIO_GPxConfig(HTCFG_ADC0CH12_GPIO_ID, HTCFG_ADC0CH12_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 13:
                AFIO_GPxConfig(HTCFG_ADC0CH13_GPIO_ID, HTCFG_ADC0CH13_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 14:
                AFIO_GPxConfig(HTCFG_ADC0CH14_GPIO_ID, HTCFG_ADC0CH14_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 15:
                AFIO_GPxConfig(HTCFG_ADC0CH15_GPIO_ID, HTCFG_ADC0CH15_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            default:
                break;
        }
    }
#endif
#ifdef BSP_USING_ADC1
    if (HT_ADC1 == adc_x)
    {
        /* Enable peripheral clock */
        CKCUClock.Bit.AFIO = 1;
        CKCUClock.Bit.ADC1 = 1;
        CKCU_PeripClockConfig(CKCUClock, ENABLE);

        /* Configure AFIO mode as ADC function */
        switch(channel)
        {
            case 0:
                AFIO_GPxConfig(HTCFG_ADC1CH0_GPIO_ID, HTCFG_ADC1CH0_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 1:
                AFIO_GPxConfig(HTCFG_ADC1CH1_GPIO_ID, HTCFG_ADC1CH1_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 2:
                AFIO_GPxConfig(HTCFG_ADC1CH2_GPIO_ID, HTCFG_ADC1CH2_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 3:
                AFIO_GPxConfig(HTCFG_ADC1CH3_GPIO_ID, HTCFG_ADC1CH3_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 4:
                AFIO_GPxConfig(HTCFG_ADC1CH4_GPIO_ID, HTCFG_ADC1CH4_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 5:
                AFIO_GPxConfig(HTCFG_ADC1CH5_GPIO_ID, HTCFG_ADC1CH5_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 6:
                AFIO_GPxConfig(HTCFG_ADC1CH6_GPIO_ID, HTCFG_ADC1CH6_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            case 7:
                AFIO_GPxConfig(HTCFG_ADC1CH7_GPIO_ID, HTCFG_ADC1CH7_AFIO_PIN, AFIO_FUN_ADC0);
                break;
            default:
                break;
        }
    }
#endif
}
#endif
