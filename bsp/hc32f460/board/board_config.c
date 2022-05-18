/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
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
        /* Configure USART1 RX/TX pin. */
        PORT_SetFunc(USART1_RX_PORT, USART1_RX_PIN, Func_Usart1_Rx, Disable);
        PORT_SetFunc(USART1_TX_PORT, USART1_TX_PIN, Func_Usart1_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART2)
    case (rt_uint32_t)M4_USART2:
        /* Configure USART2 RX/TX pin. */
        PORT_SetFunc(USART2_RX_PORT, USART2_RX_PIN, Func_Usart2_Rx, Disable);
        PORT_SetFunc(USART2_TX_PORT, USART2_TX_PIN, Func_Usart2_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART3)
    case (rt_uint32_t)M4_USART3:
        /* Configure USART3 RX/TX pin. */
        PORT_SetFunc(USART3_RX_PORT, USART3_RX_PIN, Func_Usart3_Rx, Disable);
        PORT_SetFunc(USART3_TX_PORT, USART3_TX_PIN, Func_Usart3_Tx, Disable);
        break;
#endif
#if defined(BSP_USING_UART4)
    case (rt_uint32_t)M4_USART4:
        /* Configure USART4 RX/TX pin. */
        PORT_SetFunc(USART4_RX_PORT, USART4_RX_PIN, Func_Usart4_Rx, Disable);
        PORT_SetFunc(USART4_TX_PORT, USART4_TX_PIN, Func_Usart4_Tx, Disable);
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
void rt_hw_board_adc_clock_init(void)
{
      stc_clk_xtal_cfg_t stcXtalCfg;
    stc_clk_upll_cfg_t stcUpllCfg;

    MEM_ZERO_STRUCT(stcXtalCfg);
    MEM_ZERO_STRUCT(stcUpllCfg);

    /* Use XTAL as UPLL source. */
    stcXtalCfg.enFastStartup = Enable;
    stcXtalCfg.enMode = ClkXtalModeOsc;
    stcXtalCfg.enDrv = ClkXtalLowDrv;
    CLK_XtalConfig(&stcXtalCfg);
    CLK_XtalCmd(Enable);

    /* Set UPLL out 240MHz. */
    stcUpllCfg.pllmDiv = 2u;
    /* upll = 8M(XTAL) / pllmDiv * plln */
    stcUpllCfg.plln    = 60u;
    stcUpllCfg.PllpDiv = 16u;
    stcUpllCfg.PllqDiv = 16u;
    stcUpllCfg.PllrDiv = 16u;
    CLK_SetPllSource(ClkPllSrcXTAL);
    CLK_UpllConfig(&stcUpllCfg);
    CLK_UpllCmd(Enable);
    CLK_SetPeriClkSource(ClkPeriSrcUpllr);

    /* 1. Enable ADC peripheral clock. */
#if defined(BSP_USING_ADC1)
      PWC_Fcg3PeriphClockCmd(PWC_FCG3_PERIPH_ADC1, Enable);
#endif
#if defined(BSP_USING_ADC2)
    PWC_Fcg3PeriphClockCmd(PWC_FCG3_PERIPH_ADC2, Enable);
#endif
}
rt_err_t rt_hw_board_adc_init(M4_ADC_TypeDef *ADCx)
{
    rt_err_t result = RT_EOK;
    stc_port_init_t stcPortInit;

    MEM_ZERO_STRUCT(stcPortInit);
    stcPortInit.enPinMode = Pin_Mode_Ana;
    stcPortInit.enPullUp  = Disable;

    switch ((rt_uint32_t)ADCx)
    {
#if defined(BSP_USING_ADC1)
    case (rt_uint32_t)M4_ADC1:

        PORT_Init(ADC1_CH0_PORT, ADC1_CH0_PIN, &stcPortInit);
        break;
#endif
#if defined(BSP_USING_ADC2)
    case (rt_uint32_t)CM_ADC2:

        (void)GPIO_Init(ADC2_CH0_PORT, ADC2_CH0_PIN, &stcGpioInit);
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
rt_err_t rt_hw_board_can_init(M4_CAN_TypeDef *CANx)
{
    rt_err_t result = RT_EOK;

    switch ((rt_uint32_t)CANx)
    {
#if defined(BSP_USING_CAN1)
    case (rt_uint32_t)M4_CAN:
        PORT_SetFunc(CAN1_TX_PORT, CAN1_TX_PIN, CAN1_TX_PIN_FUNC, Disable);
        PORT_SetFunc(CAN1_RX_PORT, CAN1_RX_PIN, CAN1_RX_PIN_FUNC, Disable);
        break;
#endif
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}
#endif
