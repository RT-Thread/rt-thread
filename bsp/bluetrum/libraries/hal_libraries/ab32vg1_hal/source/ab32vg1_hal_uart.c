/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vg1_hal.h"

#ifdef HAL_UART_MODULE_ENABLED

enum
{
    UARTxCON = 0x00,
    UARTxCPND,
    UARTxBAUD,
    UARTxDATA,
};

/**
 * @brief Set the UART baud rate.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param baud Baud rate.
 */
void hal_uart_setbaud(hal_sfr_t uartx, uint32_t baud)
{
    uint32_t baud_cfg;

    uartx[UARTxCON] |= UART_CLK_SRC1;
    baud_cfg = (26000000/2)/baud;
    uartx[UARTxBAUD] = (baud_cfg << 16) | baud_cfg;
}

/**
 * @brief Set the UART misc paramter.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param param uart config paramter pointer.
 */
void hal_uart_setparam(hal_sfr_t uartx, struct uart_init *param)
{
    switch (param->word_len)
    {
    case UART_WORDLENGTH_8B:
        uartx[UARTxCON] &= ~UART_BIT9_ENABLE;
        break;
    case UART_WORDLENGTH_9B:
        uartx[UARTxCON] |= UART_BIT9_ENABLE;
        break;
    default:
        break;
    }

    switch (param->stop_bits)
    {
    case UART_STOPBITS_1:
        uartx[UARTxCON] &= ~UART_SB2_ENABLE;
        break;
    case UART_STOPBITS_2:
        uartx[UARTxCON] |= UART_SB2_ENABLE;
        break;
    default:
        break;
    }

    if (param->mode & UART_MODE_1LINE)
    {
        uartx[UARTxCON] |= UART_1LINE_ENABLE;
    }
    else
    {
        uartx[UARTxCON] &= ~UART_1LINE_ENABLE;
    }
}
/**
 * @brief Initialize the UART mode.
 *
 * @param huart UART handle.
 * @return hal_error_t
 */
hal_error_t hal_uart_init(struct uart_handle *huart)
{
    if (huart == HAL_NULL) {
        return -HAL_ERROR;
    }

    hal_uart_mspinit(huart);
    uart_config_all(huart);

    return HAL_EOK;
}

/**
 * @brief DeInitialize the UART peripheral.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 */
void hal_uart_deinit(hal_sfr_t uartx)
{
    uartx[UARTxCON] = 0;
}

/**
 * @brief Initialize the UART MSP.
 *
 * @param huart UART handle.
 */
WEAK void HAL_UART_MspInit(struct uart_handle *huart)
{}

/**
 * @brief Control the UART peripheral.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param cntl
 *      @arg UART_MODULE_ENABLE
 *      @arg UART_BIT9_ENABLE
 *      @arg UART_RXIT_ENABLE
 *      @arg UART_TXIT_ENABLE
 *      @arg UART_SB2_ENABLE
 *      @arg UART_CLK_SRC1
 *      @arg UART_1LINE_ENABLE
 *      @arg UART_RX_ENABLE
 * @param param
 *      @arg HAL_DISABLE
 *      @arg HAL_ENABLE
 */
void hal_uart_control(hal_sfr_t uartx, uint32_t cntl, uint32_t param)
{
    if (param == HAL_ENABLE) {
        uartx[UARTxCON] |= (cntl);
    } else {
        uartx[UARTxCON] &= ~(cntl);
    }
}

/**
 * @brief Send a character
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param data The characters that need to be sent
 */
void hal_uart_write(hal_sfr_t uartx, uint8_t data)
{
    uartx[UARTxDATA] = data;
}

/**
 * @brief Receive a character.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @return uint8_t Received character.
 */
uint8_t hal_uart_read(hal_sfr_t uartx)
{
    return (uartx[UARTxDATA] & 0xff);
}

/**
 * @brief Get the UART flag.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param flag
 *      @arg UART_FLAG_RXPND
 *      @arg UART_FLAG_TXPND
 * @return uint32_t
 */
uint32_t hal_uart_getflag(hal_sfr_t uartx, uint32_t flag)
{
    uint32_t ret = uartx[UARTxCON] & flag;
    return ret;
}

/**
 * @brief Clear the UART flag.
 *
 * @param uartx This parameter can be UARTxN where x can be (0.2).
 * @param flag
 *      @arg UART_FLAG_RXPND
 *      @arg UART_FLAG_TXPND
 */
void hal_uart_clrflag(hal_sfr_t uartx, uint32_t flag)
{
    uartx[UARTxCPND] |= flag;
}

/**
 * @brief Configure the UART peripheral.
 *
 * @param huart UART handle.
 */
void uart_config_all(struct uart_handle *huart)
{
    hal_uart_control(huart->instance, UART_MODULE_ENABLE, HAL_DISABLE);

    CLKCON1 |= BIT(14);
    if (huart->instance == UART0_BASE) {
        hal_rcu_periph_clk_enable(RCU_UART0);
    } else if (huart->instance == UART1_BASE) {
        hal_rcu_periph_clk_enable(RCU_UART1);
    } else if (huart->instance == UART2_BASE) {
        hal_rcu_periph_clk_enable(RCU_UART2);
    } else {
        return; /* Not support! */
    }

    hal_uart_deinit(huart->instance);
    hal_uart_setbaud(huart->instance, huart->init.baud);
    hal_uart_setparam(huart->instance, &huart->init);

    if (huart->init.mode != UART_MODE_TX) {
        hal_uart_control(huart->instance, UART_RX_ENABLE, HAL_ENABLE);
    }
    hal_uart_control(huart->instance, UART_MODULE_ENABLE, HAL_ENABLE);
}

#endif
