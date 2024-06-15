/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
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
#if defined(BSP_USING_UART2)
    case (rt_uint32_t)CM_USART2:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART2_RX_PORT, USART2_RX_PIN, USART2_RX_FUNC);
        GPIO_SetFunc(USART2_TX_PORT, USART2_TX_PIN, USART2_TX_FUNC);
        break;
#endif
#if defined(BSP_USING_UART4)
    case (rt_uint32_t)CM_USART4:
        /* Configure USART RX/TX pin. */
        GPIO_SetFunc(USART4_RX_PORT, USART4_RX_PIN, USART4_RX_FUNC);
        GPIO_SetFunc(USART4_TX_PORT, USART4_TX_PIN, USART4_TX_FUNC);
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
#if defined(BSP_USING_I2C3)
    case (rt_uint32_t)CM_I2C3:
        /* Configure I2C3 SDA/SCL pin. */
        GPIO_SetFunc(I2C3_SDA_PORT, I2C3_SDA_PIN, I2C3_SDA_FUNC);
        GPIO_SetFunc(I2C3_SCL_PORT, I2C3_SCL_PIN, I2C3_SCL_FUNC);
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
    GPIO_ResetPins(CAN1_STB_PORT, CAN1_STB_PIN);
    GPIO_OutputCmd(CAN1_STB_PORT, CAN1_STB_PIN, ENABLE);
}
rt_err_t rt_hw_board_can_init(CM_CAN_TypeDef *CANx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)CANx)
    {
#if defined(BSP_USING_CAN1)
    case (rt_uint32_t)CM_CAN1:
        GPIO_SetFunc(CAN1_TX_PORT, CAN1_TX_PIN, CAN1_TX_PIN_FUNC);
        GPIO_SetFunc(CAN1_RX_PORT, CAN1_RX_PIN, CAN1_RX_PIN_FUNC);
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
#if defined(BSP_USING_SPI3)
    stc_gpio_init_t stcGpioInit;
#endif

    switch ((rt_uint32_t)CM_SPIx)
    {
#if defined(BSP_USING_SPI3)
    case (rt_uint32_t)CM_SPI3:
        GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinState = PIN_STAT_SET;
        stcGpioInit.u16PinDir   = PIN_DIR_OUT;
        GPIO_Init(SPI3_WP_PORT, SPI3_WP_PIN, &stcGpioInit);
        GPIO_Init(SPI3_HOLD_PORT, SPI3_HOLD_PIN, &stcGpioInit);

        (void)GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
        (void)GPIO_Init(SPI3_SCK_PORT,  SPI3_SCK_PIN,  &stcGpioInit);
        (void)GPIO_Init(SPI3_MOSI_PORT, SPI3_MOSI_PIN, &stcGpioInit);
        (void)GPIO_Init(SPI3_MISO_PORT, SPI3_MISO_PIN, &stcGpioInit);
        GPIO_SetFunc(SPI3_SCK_PORT,  SPI3_SCK_PIN,  SPI3_SCK_FUNC);
        GPIO_SetFunc(SPI3_MOSI_PORT, SPI3_MOSI_PIN, SPI3_MOSI_FUNC);
        GPIO_SetFunc(SPI3_MISO_PORT, SPI3_MISO_PIN, SPI3_MISO_FUNC);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif

#if defined (RT_USING_SDIO)
rt_err_t rt_hw_board_sdio_init(CM_SDIOC_TypeDef *SDIOCx)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    switch ((rt_uint32_t)SDIOCx)
    {
#if defined(BSP_USING_SDIO1)
    case (rt_uint32_t)CM_SDIOC1:
        /************************* Set pin drive capacity *************************/
        (void)GPIO_StructInit(&stcGpioInit);
        stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
        (void)GPIO_Init(SDIOC1_CK_PORT,  SDIOC1_CK_PIN,  &stcGpioInit);
        (void)GPIO_Init(SDIOC1_CMD_PORT, SDIOC1_CMD_PIN, &stcGpioInit);
        (void)GPIO_Init(SDIOC1_D0_PORT,  SDIOC1_D0_PIN,  &stcGpioInit);
        (void)GPIO_Init(SDIOC1_D1_PORT,  SDIOC1_D1_PIN,  &stcGpioInit);
        (void)GPIO_Init(SDIOC1_D2_PORT,  SDIOC1_D2_PIN,  &stcGpioInit);
        (void)GPIO_Init(SDIOC1_D3_PORT,  SDIOC1_D3_PIN,  &stcGpioInit);

        GPIO_SetFunc(SDIOC1_CK_PORT,  SDIOC1_CK_PIN,  SDIOC1_CK_FUNC);
        GPIO_SetFunc(SDIOC1_CMD_PORT, SDIOC1_CMD_PIN, SDIOC1_CMD_FUNC);
        GPIO_SetFunc(SDIOC1_D0_PORT,  SDIOC1_D0_PIN,  SDIOC1_D0_FUNC);
        GPIO_SetFunc(SDIOC1_D1_PORT,  SDIOC1_D1_PIN,  SDIOC1_D1_FUNC);
        GPIO_SetFunc(SDIOC1_D2_PORT,  SDIOC1_D2_PIN,  SDIOC1_D2_FUNC);
        GPIO_SetFunc(SDIOC1_D3_PORT,  SDIOC1_D3_PIN,  SDIOC1_D3_FUNC);
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
#if defined(BSP_USING_PWM_TMRA_4)
    case (rt_uint32_t)CM_TMRA_4:
#ifdef BSP_USING_PWM_TMRA_4_CH1
        GPIO_SetFunc(PWM_TMRA_4_CH1_PORT, PWM_TMRA_4_CH1_PIN, PWM_TMRA_4_CH1_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH2
        GPIO_SetFunc(PWM_TMRA_4_CH2_PORT, PWM_TMRA_4_CH2_PIN, PWM_TMRA_4_CH2_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH3
        GPIO_SetFunc(PWM_TMRA_4_CH3_PORT, PWM_TMRA_4_CH3_PIN, PWM_TMRA_4_CH3_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_4_CH4
        GPIO_SetFunc(PWM_TMRA_4_CH4_PORT, PWM_TMRA_4_CH4_PIN, PWM_TMRA_4_CH4_PIN_FUNC);
#endif
        break;
#endif
#if defined(BSP_USING_PWM_TMRA_5)
    case (rt_uint32_t)CM_TMRA_5:
#ifdef BSP_USING_PWM_TMRA_5_CH1
        GPIO_SetFunc(PWM_TMRA_5_CH1_PORT, PWM_TMRA_5_CH1_PIN, PWM_TMRA_5_CH1_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH2
        GPIO_SetFunc(PWM_TMRA_5_CH2_PORT, PWM_TMRA_5_CH2_PIN, PWM_TMRA_5_CH2_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH3
        GPIO_SetFunc(PWM_TMRA_5_CH3_PORT, PWM_TMRA_5_CH3_PIN, PWM_TMRA_5_CH3_PIN_FUNC);
#endif
#ifdef BSP_USING_PWM_TMRA_5_CH4
        GPIO_SetFunc(PWM_TMRA_5_CH4_PORT, PWM_TMRA_5_CH4_PIN, PWM_TMRA_5_CH4_PIN_FUNC);
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

#if defined(BSP_USING_USBD) || defined(BSP_USING_USBH)
rt_err_t rt_hw_usb_board_init(void)
{
    stc_gpio_init_t stcGpioCfg;
    (void)GPIO_StructInit(&stcGpioCfg);
#if defined(BSP_USING_USBFS)
    stcGpioCfg.u16PinAttr = PIN_ATTR_ANALOG;
    (void)GPIO_Init(USBF_DM_PORT, USBF_DM_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBF_DP_PORT, USBF_DP_PIN, &stcGpioCfg);
#if defined(BSP_USING_USBD)
    GPIO_SetFunc(USBF_VBUS_PORT, USBF_VBUS_PIN, USBF_VBUS_FUNC); /* VBUS */
#endif
#if defined(BSP_USING_USBH)
    GPIO_SetFunc(USBF_DRVVBUS_PORT, USBF_DRVVBUS_PIN, USBF_DRVVBUS_FUNC); /* DRV VBUS */
#endif
#endif
    return RT_EOK;
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
