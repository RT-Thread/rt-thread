/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */
#include <rtdevice.h>
#include "board_config.h"

/**
 * The below functions will initialize HC32 board.
 */

#if defined RT_USING_SERIAL
rt_err_t rt_hw_board_uart_init(M4_USART_TypeDef *USARTx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)USARTx)
    {
#if defined(BSP_USING_UART1)
    case (rt_uint32_t)M4_USART1:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART1_RX_PORT, USART1_RX_PIN, GPIO_FUNC_33_USART1_RX, PIN_SUBFUNC_DISABLE);
        GPIO_SetFunc(USART1_TX_PORT, USART1_TX_PIN, GPIO_FUNC_32_USART1_TX, PIN_SUBFUNC_DISABLE);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(RT_USING_PWM)
rt_err_t rt_hw_board_pwm_init(M4_TMRA_TypeDef *TMRAx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)TMRAx)
    {
#if defined(BSP_USING_PWM1)
    case (rt_uint32_t)M4_TMRA_1:
#if defined(BSP_USING_PWM1_CH1)
        GPIO_SetFunc(PWM1_CH1_PORT, PWM1_CH1_PIN, PWM1_CH1_FUNC, PIN_SUBFUNC_DISABLE);
#endif
#if defined(BSP_USING_PWM1_CH2)
        GPIO_SetFunc(PWM1_CH2_PORT, PWM1_CH2_PIN, PWM1_CH2_FUNC, PIN_SUBFUNC_DISABLE);
#endif
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined (RT_USING_SPI)
void hc32_board_spi_init(M4_SPI_TypeDef *M4_SPIx, rt_uint8_t mode)
{
#if defined (BSP_USING_SPI1)
    stc_gpio_init_t stcGpioCfg;

    GPIO_StructInit(&stcGpioCfg);

    /* Port configurate, High driving capacity for output pin.
       CMOS input for input pin */
    if(mode & RT_SPI_3WIRE)
    {
        /* code */
    }
    else
    {
        if(mode & RT_SPI_SLAVE)
        {
            stcGpioCfg.u16PinIType = PIN_ITYPE_CMOS;
        }
        else
        {
            stcGpioCfg.u16PinDrv = PIN_DRV_HIGH;
        }
        GPIO_Init(SPI1_NSS_PORT,  SPI1_NSS_PIN, &stcGpioCfg);
        GPIO_SetFunc(SPI1_NSS_PORT,  SPI1_NSS_PIN,  SPI1_NSS_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    }
    if(mode & RT_SPI_SLAVE)
    {
        stcGpioCfg.u16PinIType = PIN_ITYPE_CMOS;
        GPIO_Init(SPI1_SCK_PORT,  SPI1_SCK_PIN, &stcGpioCfg);
        GPIO_Init(SPI1_MOSI_PORT, SPI1_MOSI_PIN, &stcGpioCfg);
        stcGpioCfg.u16PinDrv = PIN_DRV_HIGH;
        GPIO_Init(SPI1_MISO_PORT, SPI1_MISO_PIN, &stcGpioCfg);
    }
    else
    {
        stcGpioCfg.u16PinDrv = PIN_DRV_HIGH;
        GPIO_Init(SPI1_SCK_PORT,  SPI1_SCK_PIN, &stcGpioCfg);
        GPIO_Init(SPI1_MOSI_PORT, SPI1_MOSI_PIN, &stcGpioCfg);
        stcGpioCfg.u16PinIType = PIN_ITYPE_CMOS;
        GPIO_Init(SPI1_MISO_PORT, SPI1_MISO_PIN, &stcGpioCfg);
    }

    GPIO_SetFunc(SPI1_SCK_PORT,  SPI1_SCK_PIN,  SPI1_SCK_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SPI1_MOSI_PORT, SPI1_MOSI_PIN, SPI1_MOSI_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
    GPIO_SetFunc(SPI1_MISO_PORT, SPI1_MISO_PIN, SPI1_MISO_GPIO_FUNC, PIN_SUBFUNC_DISABLE);
#endif

#if defined (BSP_USING_SPI2)
    /* Config SPI2 relevant port according to SPI1 */
#endif

#if defined (BSP_USING_SPI3)
    /* Config SPI3 relevant port according to SPI1 */
#endif

}
#endif

#if defined(RT_USING_PULSE_ENCODER)
rt_err_t rt_hw_board_pulse_encoder_init(M4_TMRA_TypeDef *TMRAx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)TMRAx)
    {
#if defined(BSP_USING_PULSE_ENCODER9)
    case (rt_uint32_t)M4_TMRA_9:
        GPIO_SetFunc(PULSE_ENCODER9_CLKA_PORT, PULSE_ENCODER9_CLKA_PIN, PULSE_ENCODER9_CLKA_FUNC, PIN_SUBFUNC_DISABLE);
        GPIO_SetFunc(PULSE_ENCODER9_CLKB_PORT, PULSE_ENCODER9_CLKB_PIN, PULSE_ENCODER9_CLKB_FUNC, PIN_SUBFUNC_DISABLE);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif
