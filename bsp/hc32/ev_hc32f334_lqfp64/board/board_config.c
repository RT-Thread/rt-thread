/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#include <rtdevice.h>
#include "board_config.h"

/**
 * The below functions will initialize HC32 board.
 */

#if defined RT_USING_SERIAL
rt_err_t rt_hw_board_uart_init(CM_USART_TypeDef *USARTx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)USARTx)
    {
#if defined(BSP_USING_UART1)
    case (rt_uint32_t)CM_USART1:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART1_RX_PORT, USART1_RX_PIN, USART1_RX_FUNC);
        GPIO_SetFunc(USART1_TX_PORT, USART1_TX_PIN, USART1_TX_FUNC);
        break;
#endif
#if defined(BSP_USING_UART2)
    case (rt_uint32_t)CM_USART2:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART2_RX_PORT, USART2_RX_PIN, USART2_RX_FUNC);
        GPIO_SetFunc(USART2_TX_PORT, USART2_TX_PIN, USART2_TX_FUNC);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(RT_USING_I2C)
rt_err_t rt_hw_board_i2c_init(CM_I2C_TypeDef *I2Cx)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;
    (void)GPIO_StructInit(&stcGpioInit);

    switch ((rt_uint32_t)I2Cx)
    {
#if defined(BSP_USING_I2C1)
    case (rt_uint32_t)CM_I2C:
        /* Configure I2C1 SDA/SCL pin. */
        GPIO_SetFunc(I2C1_SDA_PORT, I2C1_SDA_PIN, I2C1_SDA_FUNC);
        GPIO_SetFunc(I2C1_SCL_PORT, I2C1_SCL_PIN, I2C1_SCL_FUNC);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }
    return result;
}
#endif

#if defined(RT_USING_ADC)
rt_err_t rt_hw_board_adc_init(CM_ADC_TypeDef *ADCx)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    switch ((rt_uint32_t)ADCx)
    {
#if defined(BSP_USING_ADC1)
    case (rt_uint32_t)CM_ADC1:
        (void)GPIO_Init(ADC1_CH_PORT, ADC1_CH_PIN, &stcGpioInit);
        break;
#endif
#if defined(BSP_USING_ADC2)
    case (rt_uint32_t)CM_ADC2:
        (void)GPIO_Init(ADC2_CH_PORT, ADC2_CH_PIN, &stcGpioInit);
        break;
#endif
#if defined(BSP_USING_ADC3)
    case (rt_uint32_t)CM_ADC3:
        (void)GPIO_Init(ADC3_CH_PORT, ADC3_CH_PIN, &stcGpioInit);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(RT_USING_DAC)
rt_err_t rt_hw_board_dac_init(CM_DAC_TypeDef *DACx)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinAttr = PIN_ATTR_ANALOG;
    switch ((rt_uint32_t)DACx)
    {
#if defined(BSP_USING_DAC1)
    case (rt_uint32_t)CM_DAC1:
        (void)GPIO_Init(DAC1_CH1_PORT, DAC1_CH1_PIN, &stcGpioInit);
        (void)GPIO_Init(DAC1_CH2_PORT, DAC1_CH2_PIN, &stcGpioInit);
        break;
#endif
#if defined(BSP_USING_DAC2)
    case (rt_uint32_t)CM_DAC2:
        (void)GPIO_Init(DAC2_CH1_PORT, DAC2_CH1_PIN, &stcGpioInit);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined(RT_USING_CAN)
void CanPhyEnable(void)
{
    stc_gpio_init_t stcGpioInit;

#if defined(BSP_USING_MCAN1)
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinState = PIN_STAT_RST;
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    GPIO_Init(MCAN1_PHY_STBY_PORT, MCAN1_PHY_STBY_PIN, &stcGpioInit);
#endif
#if defined(BSP_USING_MCAN2)
    GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinState = PIN_STAT_RST;
    stcGpioInit.u16PinDir   = PIN_DIR_OUT;
    GPIO_Init(MCAN2_PHY_STBY_PORT, MCAN2_PHY_STBY_PIN, &stcGpioInit);
#endif
}

rt_err_t rt_hw_board_mcan_init(CM_MCAN_TypeDef *MCANx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)MCANx)
    {
#if defined(BSP_USING_MCAN1)
    case (rt_uint32_t)CM_MCAN1:
        GPIO_SetFunc(MCAN1_TX_PORT, MCAN1_TX_PIN, MCAN1_TX_PIN_FUNC);
        GPIO_SetFunc(MCAN1_RX_PORT, MCAN1_RX_PIN, MCAN1_RX_PIN_FUNC);
        break;
#endif
#if defined(BSP_USING_MCAN2)
    case (rt_uint32_t)CM_MCAN2:
        GPIO_SetFunc(MCAN2_TX_PORT, MCAN2_TX_PIN, MCAN2_TX_PIN_FUNC);
        GPIO_SetFunc(MCAN2_RX_PORT, MCAN2_RX_PIN, MCAN2_RX_PIN_FUNC);
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
rt_err_t rt_hw_spi_board_init(CM_SPI_TypeDef *CM_SPIx)
{
    rt_err_t result = RT_EOK;
#if defined(BSP_USING_SPI1)
    stc_gpio_init_t stcGpioInit;
#endif

    switch ((rt_uint32_t)CM_SPIx)
    {
#if defined(BSP_USING_SPI1)
    case (rt_uint32_t)CM_SPI:
        (void)GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
        stcGpioInit.u16PinInputType = PIN_IN_TYPE_CMOS;
        (void)GPIO_Init(SPI1_SCK_PORT,  SPI1_SCK_PIN,  &stcGpioInit);
        (void)GPIO_Init(SPI1_MOSI_PORT, SPI1_MOSI_PIN, &stcGpioInit);
        (void)GPIO_Init(SPI1_MISO_PORT, SPI1_MISO_PIN, &stcGpioInit);
        GPIO_SetFunc(SPI1_SCK_PORT,  SPI1_SCK_PIN,  SPI1_SCK_FUNC);
        GPIO_SetFunc(SPI1_MOSI_PORT, SPI1_MOSI_PIN, SPI1_MOSI_FUNC);
        GPIO_SetFunc(SPI1_MISO_PORT, SPI1_MISO_PIN, SPI1_MISO_FUNC);
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
#if defined(BSP_USING_PWM_TMRA)
rt_err_t rt_hw_board_pwm_tmra_init(CM_TMRA_TypeDef *TMRAx)
{
    rt_err_t result = RT_EOK;
    switch ((rt_uint32_t)TMRAx)
    {
#if defined(BSP_USING_PWM_TMRA_1)
    case (rt_uint32_t)CM_TMRA_1:
#ifdef BSP_USING_PWM_TMRA_1_CH1
        GPIO_SetFunc(PWM_TMRA_1_CH1_PORT, PWM_TMRA_1_CH1_PIN, PWM_TMRA_1_CH1_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH2
        GPIO_SetFunc(PWM_TMRA_1_CH2_PORT, PWM_TMRA_1_CH2_PIN, PWM_TMRA_1_CH2_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH3
        GPIO_SetFunc(PWM_TMRA_1_CH3_PORT, PWM_TMRA_1_CH3_PIN, PWM_TMRA_1_CH3_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_1_CH4
        GPIO_SetFunc(PWM_TMRA_1_CH4_PORT, PWM_TMRA_1_CH4_PIN, PWM_TMRA_1_CH4_PIN_FUNC);
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

#if defined(BSP_USING_PWM_TMR4)
rt_err_t rt_hw_board_pwm_tmr4_init(CM_TMR4_TypeDef *TMR4x)
{
    rt_err_t result = RT_EOK;
    switch ((rt_uint32_t)TMR4x)
    {
#if defined(BSP_USING_PWM_TMR4_1)
    case (rt_uint32_t)CM_TMR4:
#ifdef BSP_USING_PWM_TMR4_1_OUH
        GPIO_SetFunc(PWM_TMR4_1_OUH_PORT, PWM_TMR4_1_OUH_PIN, PWM_TMR4_1_OUH_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OUL
        GPIO_SetFunc(PWM_TMR4_1_OUL_PORT, PWM_TMR4_1_OUL_PIN, PWM_TMR4_1_OUL_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OVH
        GPIO_SetFunc(PWM_TMR4_1_OVH_PORT, PWM_TMR4_1_OVH_PIN, PWM_TMR4_1_OVH_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OVL
        GPIO_SetFunc(PWM_TMR4_1_OVL_PORT, PWM_TMR4_1_OVL_PIN, PWM_TMR4_1_OVL_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OWH
        GPIO_SetFunc(PWM_TMR4_1_OWH_PORT, PWM_TMR4_1_OWH_PIN, PWM_TMR4_1_OWH_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OWL
        GPIO_SetFunc(PWM_TMR4_1_OWL_PORT, PWM_TMR4_1_OWL_PIN, PWM_TMR4_1_OWL_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OXH
        GPIO_SetFunc(PWM_TMR4_1_OXH_PORT, PWM_TMR4_1_OXH_PIN, PWM_TMR4_1_OXH_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR4_1_OXL
        GPIO_SetFunc(PWM_TMR4_1_OXL_PORT, PWM_TMR4_1_OXL_PIN, PWM_TMR4_1_OXL_PIN_FUNC);
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

#if defined(BSP_USING_PWM_TMR6)
rt_err_t rt_hw_board_pwm_tmr6_init(CM_TMR6_TypeDef *TMR6x)
{
    rt_err_t result = RT_EOK;
    switch ((rt_uint32_t)TMR6x)
    {
#if defined(BSP_USING_PWM_TMR6_1)
    case (rt_uint32_t)CM_TMR6_1:
#ifdef BSP_USING_PWM_TMR6_1_A
        GPIO_SetFunc(PWM_TMR6_1_A_PORT, PWM_TMR6_1_A_PIN, PWM_TMR6_1_A_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMR6_1_B
        GPIO_SetFunc(PWM_TMR6_1_B_PORT, PWM_TMR6_1_B_PIN, PWM_TMR6_1_B_PIN_FUNC);
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
#endif

#if defined (BSP_USING_INPUT_CAPTURE)
rt_err_t rt_hw_board_input_capture_init(uint32_t *tmr_instance)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)tmr_instance)
    {
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_1)
    case (rt_uint32_t)CM_TMR6_1:
        GPIO_SetFunc(INPUT_CAPTURE_TMR6_1_PORT, INPUT_CAPTURE_TMR6_1_PIN, INPUT_CAPTURE_TMR6_FUNC);
        break;
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_2)
    case (rt_uint32_t)CM_TMR6_2:
        GPIO_SetFunc(INPUT_CAPTURE_TMR6_2_PORT, INPUT_CAPTURE_TMR6_2_PIN, INPUT_CAPTURE_TMR6_FUNC);
        break;
#endif
#if defined (BSP_USING_INPUT_CAPTURE_TMR6_3)
    case (rt_uint32_t)CM_TMR6_3:
        GPIO_SetFunc(INPUT_CAPTURE_TMR6_3_PORT, INPUT_CAPTURE_TMR6_3_PIN, INPUT_CAPTURE_TMR6_FUNC);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }
    return result;
}
#endif

#ifdef RT_USING_PM
void rt_hw_board_pm_sysclk_cfg(uint8_t run_mode)
{
    switch (run_mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
        CLK_SetSysClockSrc(CLK_SYSCLK_SRC_PLL);
        break;

    case PM_RUN_MODE_LOW_SPEED:
        /* Ensure that system clock less than 8M */
        CLK_SetSysClockSrc(CLK_SYSCLK_SRC_XTAL);

    default:
        break;
    }
}
#endif

#if defined(BSP_USING_TMRA_PULSE_ENCODER)
rt_err_t rt_hw_board_pulse_encoder_tmra_init(void)
{
#if defined(BSP_USING_PULSE_ENCODER_TMRA_1)
    GPIO_SetFunc(PULSE_ENCODER_TMRA_1_A_PORT, PULSE_ENCODER_TMRA_1_A_PIN, PULSE_ENCODER_TMRA_1_A_PIN_FUNC);
    GPIO_SetFunc(PULSE_ENCODER_TMRA_1_B_PORT, PULSE_ENCODER_TMRA_1_B_PIN, PULSE_ENCODER_TMRA_1_B_PIN_FUNC);
#endif
    return RT_EOK;
}
#endif

#if defined(BSP_USING_TMR6_PULSE_ENCODER)
rt_err_t rt_hw_board_pulse_encoder_tmr6_init(void)
{
#if defined(BSP_USING_PULSE_ENCODER_TMR6_1)
    GPIO_SetFunc(PULSE_ENCODER_TMR6_1_A_PORT, PULSE_ENCODER_TMR6_1_A_PIN, PULSE_ENCODER_TMR6_1_A_PIN_FUNC);
    GPIO_SetFunc(PULSE_ENCODER_TMR6_1_B_PORT, PULSE_ENCODER_TMR6_1_B_PIN, PULSE_ENCODER_TMR6_1_B_PIN_FUNC);
#endif
    return RT_EOK;
}
#endif
