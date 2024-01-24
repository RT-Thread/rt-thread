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
#include "tca9539.h"

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
        (void)GPIO_Init(DAC2_CH2_PORT, DAC2_CH2_PIN, &stcGpioInit);
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
    TCA9539_WritePin(CAN_STB_PORT, CAN_STB_PIN, TCA9539_PIN_RESET);
    TCA9539_ConfigPin(CAN_STB_PORT, CAN_STB_PIN, TCA9539_DIR_OUT);
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
#if defined(BSP_USING_CAN2)
    case (rt_uint32_t)CM_CAN2:
        GPIO_SetFunc(CAN2_TX_PORT, CAN2_TX_PIN, CAN2_TX_PIN_FUNC);
        GPIO_SetFunc(CAN2_RX_PORT, CAN2_RX_PIN, CAN2_RX_PIN_FUNC);
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

#if defined(BSP_USING_ETH)
/* PHY hardware reset time */
#define PHY_HW_RST_DELAY                (0x40U)

rt_err_t rt_hw_eth_phy_reset(CM_ETH_TypeDef *CM_ETHx)
{
    TCA9539_ConfigPin(TCA9539_IO_PORT1, EIO_ETH_RST, TCA9539_DIR_OUT);
    TCA9539_WritePin(TCA9539_IO_PORT1,  EIO_ETH_RST, TCA9539_PIN_RESET);
    rt_thread_mdelay(PHY_HW_RST_DELAY);
    TCA9539_WritePin(TCA9539_IO_PORT1,  EIO_ETH_RST, TCA9539_PIN_SET);
    rt_thread_mdelay(PHY_HW_RST_DELAY);
    return RT_EOK;
}

rt_err_t rt_hw_eth_board_init(CM_ETH_TypeDef *CM_ETHx)
{
#if defined(ETH_INTERFACE_USING_RMII)
    GPIO_SetFunc(ETH_SMI_MDIO_PORT,     ETH_SMI_MDIO_PIN,     ETH_SMI_MDIO_FUNC);
    GPIO_SetFunc(ETH_SMI_MDC_PORT,      ETH_SMI_MDC_PIN,      ETH_SMI_MDC_FUNC);
    GPIO_SetFunc(ETH_RMII_TX_EN_PORT,   ETH_RMII_TX_EN_PIN,   ETH_RMII_TX_EN_FUNC);
    GPIO_SetFunc(ETH_RMII_TXD0_PORT,    ETH_RMII_TXD0_PIN,    ETH_RMII_TXD0_FUNC);
    GPIO_SetFunc(ETH_RMII_TXD1_PORT,    ETH_RMII_TXD1_PIN,    ETH_RMII_TXD1_FUNC);
    GPIO_SetFunc(ETH_RMII_REF_CLK_PORT, ETH_RMII_REF_CLK_PIN, ETH_RMII_REF_CLK_FUNC);
    GPIO_SetFunc(ETH_RMII_CRS_DV_PORT,  ETH_RMII_CRS_DV_PIN,  ETH_RMII_CRS_DV_FUNC);
    GPIO_SetFunc(ETH_RMII_RXD0_PORT,    ETH_RMII_RXD0_PIN,    ETH_RMII_RXD0_FUNC);
    GPIO_SetFunc(ETH_RMII_RXD1_PORT,    ETH_RMII_RXD1_PIN,    ETH_RMII_RXD1_FUNC);
#else
    GPIO_SetFunc(ETH_SMI_MDIO_PORT,   ETH_SMI_MDIO_PIN,   ETH_SMI_MDIO_FUNC);
    GPIO_SetFunc(ETH_SMI_MDC_PORT,    ETH_SMI_MDC_PIN,    ETH_SMI_MDC_FUNC);
    GPIO_SetFunc(ETH_MII_TX_CLK_PORT, ETH_MII_TX_CLK_PIN, ETH_MII_TX_CLK_FUNC);
    GPIO_SetFunc(ETH_MII_TX_EN_PORT,  ETH_MII_TX_EN_PIN,  ETH_MII_TX_EN_FUNC);
    GPIO_SetFunc(ETH_MII_TXD0_PORT,   ETH_MII_TXD0_PIN,   ETH_MII_TXD0_FUNC);
    GPIO_SetFunc(ETH_MII_TXD1_PORT,   ETH_MII_TXD1_PIN,   ETH_MII_TXD1_FUNC);
    GPIO_SetFunc(ETH_MII_TXD2_PORT,   ETH_MII_TXD2_PIN,   ETH_MII_TXD2_FUNC);
    GPIO_SetFunc(ETH_MII_TXD3_PORT,   ETH_MII_TXD3_PIN,   ETH_MII_TXD3_FUNC);
    GPIO_SetFunc(ETH_MII_RX_CLK_PORT, ETH_MII_RX_CLK_PIN, ETH_MII_RX_CLK_FUNC);
    GPIO_SetFunc(ETH_MII_RX_DV_PORT,  ETH_MII_RX_DV_PIN,  ETH_MII_RX_DV_FUNC);
    GPIO_SetFunc(ETH_MII_RXD0_PORT,   ETH_MII_RXD0_PIN,   ETH_MII_RXD0_FUNC);
    GPIO_SetFunc(ETH_MII_RXD1_PORT,   ETH_MII_RXD1_PIN,   ETH_MII_RXD1_FUNC);
    GPIO_SetFunc(ETH_MII_RXD2_PORT,   ETH_MII_RXD2_PIN,   ETH_MII_RXD2_FUNC);
    GPIO_SetFunc(ETH_MII_RXD3_PORT,   ETH_MII_RXD3_PIN,   ETH_MII_RXD3_FUNC);
    GPIO_SetFunc(ETH_MII_RX_ER_PORT,  ETH_MII_RX_ER_PIN,  ETH_MII_RX_ER_FUNC);
    GPIO_SetFunc(ETH_MII_CRS_PORT,    ETH_MII_CRS_PIN,    ETH_MII_CRS_FUNC);
    GPIO_SetFunc(ETH_MII_COL_PORT,    ETH_MII_COL_PIN,    ETH_MII_COL_FUNC);
#endif
    return RT_EOK;
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

#if defined (BSP_USING_SDRAM)
rt_err_t rt_hw_board_sdram_init(void)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    /************************* Set pin drive capacity *************************/
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;
    /* DMC_CKE */
    (void)GPIO_Init(SDRAM_CKE_PORT, SDRAM_CKE_PIN, &stcGpioInit);
    /* DMC_CLK */
    (void)GPIO_Init(SDRAM_CLK_PORT, SDRAM_CLK_PIN, &stcGpioInit);
    /* DMC_LDQM && DMC_UDQM */
    (void)GPIO_Init(SDRAM_DQM0_PORT, SDRAM_DQM0_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DQM1_PORT, SDRAM_DQM1_PIN, &stcGpioInit);
    /* DMC_BA[0:1] */
    (void)GPIO_Init(SDRAM_BA0_PORT, SDRAM_BA0_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_BA1_PORT, SDRAM_BA1_PIN, &stcGpioInit);
    /* DMC_CAS && DMC_RAS */
    (void)GPIO_Init(SDRAM_CAS_PORT, SDRAM_CAS_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_RAS_PORT, SDRAM_RAS_PIN, &stcGpioInit);
    /* DMC_WE */
    (void)GPIO_Init(SDRAM_WE_PORT, SDRAM_WE_PIN, &stcGpioInit);
    /* DMC_DATA[0:15] */
    (void)GPIO_Init(SDRAM_DATA0_PORT, SDRAM_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA1_PORT, SDRAM_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA2_PORT, SDRAM_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA3_PORT, SDRAM_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA4_PORT, SDRAM_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA5_PORT, SDRAM_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA6_PORT, SDRAM_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA7_PORT, SDRAM_DATA7_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA8_PORT, SDRAM_DATA8_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA9_PORT, SDRAM_DATA9_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA10_PORT, SDRAM_DATA10_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA11_PORT, SDRAM_DATA11_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA12_PORT, SDRAM_DATA12_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA13_PORT, SDRAM_DATA13_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA14_PORT, SDRAM_DATA14_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_DATA15_PORT, SDRAM_DATA15_PIN, &stcGpioInit);
    /* DMC_ADD[0:11]*/
    (void)GPIO_Init(SDRAM_ADD0_PORT, SDRAM_ADD0_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD1_PORT, SDRAM_ADD1_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD2_PORT, SDRAM_ADD2_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD3_PORT, SDRAM_ADD3_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD4_PORT, SDRAM_ADD4_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD5_PORT, SDRAM_ADD5_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD6_PORT, SDRAM_ADD6_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD7_PORT, SDRAM_ADD7_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD8_PORT, SDRAM_ADD8_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD9_PORT, SDRAM_ADD9_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD10_PORT, SDRAM_ADD10_PIN, &stcGpioInit);
    (void)GPIO_Init(SDRAM_ADD11_PORT, SDRAM_ADD11_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* DMC_CKE */
    GPIO_SetFunc(SDRAM_CKE_PORT, SDRAM_CKE_PIN, SDRAM_CKE_FUNC);
    /* DMC_CLK */
    GPIO_SetFunc(SDRAM_CLK_PORT, SDRAM_CLK_PIN, SDRAM_CLK_FUNC);
    /* DMC_LDQM && DMC_UDQM */
    GPIO_SetFunc(SDRAM_DQM0_PORT, SDRAM_DQM0_PIN, SDRAM_DQM0_FUNC);
    GPIO_SetFunc(SDRAM_DQM1_PORT, SDRAM_DQM1_PIN, SDRAM_DQM1_FUNC);
    /* DMC_BA[0:1] */
    GPIO_SetFunc(SDRAM_BA0_PORT, SDRAM_BA0_PIN, SDRAM_BA0_FUNC);
    GPIO_SetFunc(SDRAM_BA1_PORT, SDRAM_BA1_PIN, SDRAM_BA1_FUNC);
    /* DMC_CS */
    GPIO_SetFunc(SDRAM_CS_PORT, SDRAM_CS_PIN, SDRAM_CS_FUNC);
    /* DMC_CAS && DMC_RAS */
    GPIO_SetFunc(SDRAM_CAS_PORT, SDRAM_CAS_PIN, SDRAM_CAS_FUNC);
    GPIO_SetFunc(SDRAM_RAS_PORT, SDRAM_RAS_PIN, SDRAM_RAS_FUNC);
    /* DMC_WE */
    GPIO_SetFunc(SDRAM_WE_PORT, SDRAM_WE_PIN, SDRAM_WE_FUNC);
    /* DMC_DATA[0:15] */
    GPIO_SetFunc(SDRAM_DATA0_PORT,  SDRAM_DATA0_PIN,  SDRAM_DATA0_FUNC);
    GPIO_SetFunc(SDRAM_DATA1_PORT,  SDRAM_DATA1_PIN,  SDRAM_DATA1_FUNC);
    GPIO_SetFunc(SDRAM_DATA2_PORT,  SDRAM_DATA2_PIN,  SDRAM_DATA2_FUNC);
    GPIO_SetFunc(SDRAM_DATA3_PORT,  SDRAM_DATA3_PIN,  SDRAM_DATA3_FUNC);
    GPIO_SetFunc(SDRAM_DATA4_PORT,  SDRAM_DATA4_PIN,  SDRAM_DATA4_FUNC);
    GPIO_SetFunc(SDRAM_DATA5_PORT,  SDRAM_DATA5_PIN,  SDRAM_DATA5_FUNC);
    GPIO_SetFunc(SDRAM_DATA6_PORT,  SDRAM_DATA6_PIN,  SDRAM_DATA6_FUNC);
    GPIO_SetFunc(SDRAM_DATA7_PORT,  SDRAM_DATA7_PIN,  SDRAM_DATA7_FUNC);
    GPIO_SetFunc(SDRAM_DATA8_PORT,  SDRAM_DATA8_PIN,  SDRAM_DATA8_FUNC);
    GPIO_SetFunc(SDRAM_DATA9_PORT,  SDRAM_DATA9_PIN,  SDRAM_DATA9_FUNC);
    GPIO_SetFunc(SDRAM_DATA10_PORT, SDRAM_DATA10_PIN, SDRAM_DATA10_FUNC);
    GPIO_SetFunc(SDRAM_DATA11_PORT, SDRAM_DATA11_PIN, SDRAM_DATA11_FUNC);
    GPIO_SetFunc(SDRAM_DATA12_PORT, SDRAM_DATA12_PIN, SDRAM_DATA12_FUNC);
    GPIO_SetFunc(SDRAM_DATA13_PORT, SDRAM_DATA13_PIN, SDRAM_DATA13_FUNC);
    GPIO_SetFunc(SDRAM_DATA14_PORT, SDRAM_DATA14_PIN, SDRAM_DATA14_FUNC);
    GPIO_SetFunc(SDRAM_DATA15_PORT, SDRAM_DATA15_PIN, SDRAM_DATA15_FUNC);
    /* DMC_ADD[0:11]*/
    GPIO_SetFunc(SDRAM_ADD0_PORT,  SDRAM_ADD0_PIN,  SDRAM_ADD0_FUNC);
    GPIO_SetFunc(SDRAM_ADD1_PORT,  SDRAM_ADD1_PIN,  SDRAM_ADD1_FUNC);
    GPIO_SetFunc(SDRAM_ADD2_PORT,  SDRAM_ADD2_PIN,  SDRAM_ADD2_FUNC);
    GPIO_SetFunc(SDRAM_ADD3_PORT,  SDRAM_ADD3_PIN,  SDRAM_ADD3_FUNC);
    GPIO_SetFunc(SDRAM_ADD4_PORT,  SDRAM_ADD4_PIN,  SDRAM_ADD4_FUNC);
    GPIO_SetFunc(SDRAM_ADD5_PORT,  SDRAM_ADD5_PIN,  SDRAM_ADD5_FUNC);
    GPIO_SetFunc(SDRAM_ADD6_PORT,  SDRAM_ADD6_PIN,  SDRAM_ADD6_FUNC);
    GPIO_SetFunc(SDRAM_ADD7_PORT,  SDRAM_ADD7_PIN,  SDRAM_ADD7_FUNC);
    GPIO_SetFunc(SDRAM_ADD8_PORT,  SDRAM_ADD8_PIN,  SDRAM_ADD8_FUNC);
    GPIO_SetFunc(SDRAM_ADD9_PORT,  SDRAM_ADD9_PIN,  SDRAM_ADD9_FUNC);
    GPIO_SetFunc(SDRAM_ADD10_PORT, SDRAM_ADD10_PIN, SDRAM_ADD10_FUNC);
    GPIO_SetFunc(SDRAM_ADD11_PORT, SDRAM_ADD11_PIN, SDRAM_ADD11_FUNC);

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
#elif defined(BSP_USING_USBHS)
#if defined(BSP_USING_USBHS_PHY_EMBED)
    /* USBHS work in embedded PHY */
    stcGpioCfg.u16PinAttr = PIN_ATTR_ANALOG;
    (void)GPIO_Init(USBH_DM_PORT, USBH_DM_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_DP_PORT, USBH_DP_PIN, &stcGpioCfg);
#if defined(BSP_USING_USBD)
    GPIO_SetFunc(USBH_VBUS_PORT, USBH_VBUS_PIN, USBH_VBUS_FUNC);
#endif
#if defined(BSP_USING_USBH)
    GPIO_OutputCmd(USBH_DRVVBUS_PORT, USBH_DRVVBUS_PIN, ENABLE);
    GPIO_SetPins(USBH_DRVVBUS_PORT, USBH_DRVVBUS_PIN); /* DRV VBUS with GPIO funciton */
#endif
#else
    /* Reset 3300 */
    TCA9539_WritePin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_PIN_SET);
    TCA9539_ConfigPin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_DIR_OUT);

    (void)GPIO_StructInit(&stcGpioCfg);
    /* High drive capability */
    stcGpioCfg.u16PinDrv = PIN_HIGH_DRV;
    (void)GPIO_Init(USBH_ULPI_D0_PORT, USBH_ULPI_D0_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D1_PORT, USBH_ULPI_D1_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D2_PORT, USBH_ULPI_D2_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D3_PORT, USBH_ULPI_D3_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D4_PORT, USBH_ULPI_D4_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D5_PORT, USBH_ULPI_D5_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D6_PORT, USBH_ULPI_D6_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_D7_PORT, USBH_ULPI_D7_PIN, &stcGpioCfg);
    (void)GPIO_Init(USBH_ULPI_STP_PORT, USBH_ULPI_STP_PIN, &stcGpioCfg);

    GPIO_SetFunc(USBH_ULPI_CLK_PORT, USBH_ULPI_CLK_PIN, USBH_ULPI_CLK_FUNC);
    GPIO_SetFunc(USBH_ULPI_DIR_PORT, USBH_ULPI_DIR_PIN, USBH_ULPI_DIR_FUNC);
    GPIO_SetFunc(USBH_ULPI_NXT_PORT, USBH_ULPI_NXT_PIN, USBH_ULPI_NXT_FUNC);
    GPIO_SetFunc(USBH_ULPI_STP_PORT, USBH_ULPI_STP_PIN, USBH_ULPI_STP_FUNC);
    GPIO_SetFunc(USBH_ULPI_D0_PORT,  USBH_ULPI_D0_PIN,  USBH_ULPI_D0_FUNC);
    GPIO_SetFunc(USBH_ULPI_D1_PORT,  USBH_ULPI_D1_PIN,  USBH_ULPI_D1_FUNC);
    GPIO_SetFunc(USBH_ULPI_D2_PORT,  USBH_ULPI_D2_PIN,  USBH_ULPI_D2_FUNC);
    GPIO_SetFunc(USBH_ULPI_D3_PORT,  USBH_ULPI_D3_PIN,  USBH_ULPI_D3_FUNC);
    GPIO_SetFunc(USBH_ULPI_D4_PORT,  USBH_ULPI_D4_PIN,  USBH_ULPI_D4_FUNC);
    GPIO_SetFunc(USBH_ULPI_D5_PORT,  USBH_ULPI_D5_PIN,  USBH_ULPI_D5_FUNC);
    GPIO_SetFunc(USBH_ULPI_D6_PORT,  USBH_ULPI_D6_PIN,  USBH_ULPI_D6_FUNC);
    GPIO_SetFunc(USBH_ULPI_D7_PORT,  USBH_ULPI_D7_PIN,  USBH_ULPI_D7_FUNC);

    TCA9539_WritePin(TCA9539_IO_PORT1, USB_3300_RESET_PIN, TCA9539_PIN_RESET);
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

#if defined (BSP_USING_NAND)
rt_err_t rt_hw_board_nand_init(void)
{
    rt_err_t result = RT_EOK;
    stc_gpio_init_t stcGpioInit;

    /************************* Set pin drive capacity *************************/
    (void)GPIO_StructInit(&stcGpioInit);
    stcGpioInit.u16PinDrv = PIN_HIGH_DRV;

    /* NFC_CE */
    (void)GPIO_Init(NAND_CE_PORT, NAND_CE_PIN, &stcGpioInit);
    /* NFC_RE */
    (void)GPIO_Init(NAND_RE_PORT, NAND_RE_PIN, &stcGpioInit);
    /* NFC_WE */
    (void)GPIO_Init(NAND_WE_PORT, NAND_WE_PIN, &stcGpioInit);
    /* NFC_CLE */
    (void)GPIO_Init(NAND_CLE_PORT, NAND_CLE_PIN, &stcGpioInit);
    /* NFC_ALE */
    (void)GPIO_Init(NAND_ALE_PORT, NAND_ALE_PIN, &stcGpioInit);
    /* NFC_WP */
    (void)GPIO_Init(NAND_WP_PORT, NAND_WP_PIN, &stcGpioInit);
    GPIO_SetPins(NAND_WP_PORT, NAND_WP_PIN);

    /* NFC_DATA[0:7] */
    (void)GPIO_Init(NAND_DATA0_PORT, NAND_DATA0_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA1_PORT, NAND_DATA1_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA2_PORT, NAND_DATA2_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA3_PORT, NAND_DATA3_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA4_PORT, NAND_DATA4_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA5_PORT, NAND_DATA5_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA6_PORT, NAND_DATA6_PIN, &stcGpioInit);
    (void)GPIO_Init(NAND_DATA7_PORT, NAND_DATA7_PIN, &stcGpioInit);
    /* NFC_RB */
    (void)GPIO_Init(NAND_RB_PORT, NAND_RB_PIN, &stcGpioInit);

    /************************** Set EXMC pin function *************************/
    /* NFC_CE */
    GPIO_SetFunc(NAND_CE_PORT, NAND_CE_PIN, NAND_CE_FUNC);
    /* NFC_RE */
    GPIO_SetFunc(NAND_RE_PORT, NAND_RE_PIN, NAND_RE_FUNC);
    /* NFC_WE */
    GPIO_SetFunc(NAND_WE_PORT, NAND_WE_PIN, NAND_WE_FUNC);
    /* NFC_CLE */
    GPIO_SetFunc(NAND_CLE_PORT, NAND_CLE_PIN, NAND_CLE_FUNC);
    /* NFC_ALE */
    GPIO_SetFunc(NAND_ALE_PORT, NAND_ALE_PIN, NAND_ALE_FUNC);
    /* NFC_WP */
    GPIO_SetFunc(NAND_WP_PORT, NAND_WP_PIN, NAND_WP_FUNC);
    /* NFC_RB */
    GPIO_SetFunc(NAND_RB_PORT, NAND_RB_PIN, NAND_RB_FUNC);
    /* NFC_DATA[0:7] */
    GPIO_SetFunc(NAND_DATA0_PORT, NAND_DATA0_PIN, NAND_DATA0_FUNC);
    GPIO_SetFunc(NAND_DATA1_PORT, NAND_DATA1_PIN, NAND_DATA1_FUNC);
    GPIO_SetFunc(NAND_DATA2_PORT, NAND_DATA2_PIN, NAND_DATA2_FUNC);
    GPIO_SetFunc(NAND_DATA3_PORT, NAND_DATA3_PIN, NAND_DATA3_FUNC);
    GPIO_SetFunc(NAND_DATA4_PORT, NAND_DATA4_PIN, NAND_DATA4_FUNC);
    GPIO_SetFunc(NAND_DATA5_PORT, NAND_DATA5_PIN, NAND_DATA5_FUNC);
    GPIO_SetFunc(NAND_DATA6_PORT, NAND_DATA6_PIN, NAND_DATA6_FUNC);
    GPIO_SetFunc(NAND_DATA7_PORT, NAND_DATA7_PIN, NAND_DATA7_FUNC);

    return result;
}
#endif
