/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#include <rtdevice.h>
#include "board_config.h"
#include "tca9539_port.h"

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
#if defined(BSP_USING_UART6)
    case (rt_uint32_t)CM_USART6:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART6_RX_PORT, USART6_RX_PIN, USART6_RX_FUNC);
        GPIO_SetFunc(USART6_TX_PORT, USART6_TX_PIN, USART6_TX_FUNC);
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
    case (rt_uint32_t)CM_I2C1:
        /* Configure I2C1 SDA/SCL pin. */
        GPIO_SetFunc(I2C1_SDA_PORT, I2C1_SDA_PIN, I2C1_SDA_FUNC);
        GPIO_SetFunc(I2C1_SCL_PORT, I2C1_SCL_PIN, I2C1_SCL_FUNC);
        break;
#endif
#if defined(BSP_USING_I2C2) // TODO, ch2 for test only
    case (rt_uint32_t)CM_I2C2:
        /* Configure I2C2 SDA/SCL pin. */
        GPIO_SetFunc(I2C2_SDA_PORT, I2C2_SDA_PIN, I2C2_SDA_FUNC);
        GPIO_SetFunc(I2C2_SCL_PORT, I2C2_SCL_PIN, I2C2_SCL_FUNC);
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
    case (rt_uint32_t)CM_DAC:
        (void)GPIO_Init(DAC1_CH1_PORT, DAC1_CH1_PIN, &stcGpioInit);
        (void)GPIO_Init(DAC1_CH2_PORT, DAC1_CH2_PIN, &stcGpioInit);
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
#if defined(BSP_USING_MCAN1)
    TCA9539_WritePin(CAN1_STB_PORT, CAN1_STB_PIN, TCA9539_PIN_RESET);
    TCA9539_ConfigPin(CAN1_STB_PORT, CAN1_STB_PIN, TCA9539_DIR_OUT);
#endif
#if defined(BSP_USING_MCAN2)
    TCA9539_WritePin(CAN2_STB_PORT, CAN2_STB_PIN, TCA9539_PIN_RESET);
    TCA9539_ConfigPin(CAN2_STB_PORT, CAN2_STB_PIN, TCA9539_DIR_OUT);
#endif
}
rt_err_t rt_hw_board_can_init(CM_MCAN_TypeDef *MCANx)
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
    case (rt_uint32_t)CM_SPI1:
        GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinState = PIN_STAT_SET;
        stcGpioInit.u16PinDir   = PIN_DIR_OUT;
        GPIO_Init(SPI1_WP_PORT, SPI1_WP_PIN, &stcGpioInit);
        GPIO_Init(SPI1_HOLD_PORT, SPI1_HOLD_PIN, &stcGpioInit);

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
#if defined(BSP_USING_PWM_TMRA_2)
    case (rt_uint32_t)CM_TMRA_2:
#ifdef BSP_USING_PWM_TMRA_2_CH1
        GPIO_SetFunc(PWM_TMRA_2_CH1_PORT, PWM_TMRA_2_CH1_PIN, PWM_TMRA_2_CH1_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH2
        GPIO_SetFunc(PWM_TMRA_2_CH2_PORT, PWM_TMRA_2_CH2_PIN, PWM_TMRA_2_CH2_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH3
        GPIO_SetFunc(PWM_TMRA_2_CH3_PORT, PWM_TMRA_2_CH3_PIN, PWM_TMRA_2_CH3_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_2_CH4
        GPIO_SetFunc(PWM_TMRA_2_CH4_PORT, PWM_TMRA_2_CH4_PIN, PWM_TMRA_2_CH4_PIN_FUNC);
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
    case (rt_uint32_t)CM_TMR4_1:
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

#ifdef RT_USING_PM
#define PLL_SRC                                             ((CM_CMU->PLLHCFGR & CMU_PLLHCFGR_PLLSRC) >> CMU_PLLHCFGR_PLLSRC_POS)
void rt_hw_board_pm_sysclk_cfg(uint8_t run_mode)
{
    switch (run_mode)
    {
    case PM_RUN_MODE_HIGH_SPEED:
    case PM_RUN_MODE_NORMAL_SPEED:
        SystemClock_Config();
        break;

    case PM_RUN_MODE_LOW_SPEED:
        CLK_SetSysClockSrc(CLK_SYSCLK_SRC_XTAL);

    default:
        break;
    }
}
#endif

#if defined(BSP_USING_QSPI)
rt_err_t rt_hw_qspi_board_init(void)
{
    stc_gpio_init_t stcGpioInit;

    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
#ifndef BSP_QSPI_USING_SOFT_CS
    (void)GPIO_Init(QSPI_FLASH_CS_PORT,  QSPI_FLASH_CS_PIN,  &stcGpioInit);
    GPIO_SetFunc(QSPI_FLASH_CS_PORT,  QSPI_FLASH_CS_PIN,  QSPI_FLASH_CS_FUNC);
#endif
    (void)GPIO_Init(QSPI_FLASH_SCK_PORT, QSPI_FLASH_SCK_PIN, &stcGpioInit);
    (void)GPIO_Init(QSPI_FLASH_IO0_PORT, QSPI_FLASH_IO0_PIN, &stcGpioInit);
    (void)GPIO_Init(QSPI_FLASH_IO1_PORT, QSPI_FLASH_IO1_PIN, &stcGpioInit);
    (void)GPIO_Init(QSPI_FLASH_IO2_PORT, QSPI_FLASH_IO2_PIN, &stcGpioInit);
    (void)GPIO_Init(QSPI_FLASH_IO3_PORT, QSPI_FLASH_IO3_PIN, &stcGpioInit);
    GPIO_SetFunc(QSPI_FLASH_SCK_PORT, QSPI_FLASH_SCK_PIN, QSPI_FLASH_SCK_FUNC);
    GPIO_SetFunc(QSPI_FLASH_IO0_PORT, QSPI_FLASH_IO0_PIN, QSPI_FLASH_IO0_FUNC);
    GPIO_SetFunc(QSPI_FLASH_IO1_PORT, QSPI_FLASH_IO1_PIN, QSPI_FLASH_IO1_FUNC);
    GPIO_SetFunc(QSPI_FLASH_IO2_PORT, QSPI_FLASH_IO2_PIN, QSPI_FLASH_IO2_FUNC);
    GPIO_SetFunc(QSPI_FLASH_IO3_PORT, QSPI_FLASH_IO3_PIN, QSPI_FLASH_IO3_FUNC);

    return RT_EOK;
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
