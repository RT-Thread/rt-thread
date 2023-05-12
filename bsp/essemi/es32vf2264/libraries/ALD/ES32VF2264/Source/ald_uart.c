/**
  *********************************************************************************
  *
  * @file    ald_uart.c
  * @brief   UART module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Universal Asynchronous Receiver Transmitter (UART) peripheral:
  *           + Initialization and Configuration functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  * @version V1.0
  * @date    23 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          23 Feb. 2023    Lisq            The first version
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  **********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The UART driver can be used as follows:

    (#) Declare a uart_handle_t handle structure.

    (#) Initialize the UART low level resources:
        (##) Enable the UARTx interface clock.
        (##) UART pins configuration:
            (+++) Enable the clock for the UART GPIOs.
            (+++) Configure the UART pins (TX as alternate function pull-up, RX as alternate function Input).
        (##) NVIC configuration if you need to use interrupt process (ald_uart_send_by_it()
             and ald_uart_recv_by_it() APIs):
            (+++) Configure the uart interrupt priority.
            (+++) Enable the NVIC UART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (ald_uart_send_by_dma()
             and ald_uart_recv_by_dma() APIs):
            (+++) Select the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the UART DMA Tx/Rx handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity, Hardware
        flow control and Mode(Receiver/Transmitter) in the hperh Init structure.

    (#) Initialize the UART registers by calling the ald_uart_init() API.

     [..]
        Three operation modes are available within this driver:

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using ald_uart_send()
       (+) Receive an amount of data in blocking mode using ald_uart_recv()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using ald_uart_send_by_it()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using ald_uart_recv_by_it()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()

     *** DMA mode IO operation ***
     ==============================
     [..]
       (+) Send an amount of data in non blocking mode (DMA) using ald_uart_send_by_dma()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_uart_recv_by_dma()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()
       (+) Pause the DMA Transfer using ald_uart_dma_pause()
       (+) Resume the DMA Transfer using ald_uart_dma_resume()
       (+) Stop the DMA Transfer using ald_uart_dma_stop()

    @endverbatim
  ******************************************************************************
  */

#include "ald_uart.h"

/** @addtogroup ES32VF2264_ALD
  * @{
  */

/** @defgroup UART UART
  * @brief UART module driver
  * @{
  */

/** @defgroup UART_Private_Functions   UART Private Functions
  *  @brief   UART Private functions
  * @{
  */

/**
  * @brief  DMA uart transmit process complete callback.
  * @param  arg: Pointer to a uart_handle_t structure.
  * @retval None
  */
static void uart_dma_send_cplt(void *arg)
{
    ald_uart_handle_t *hperh = (ald_uart_handle_t *)arg;
    hperh->tx_count = hperh->tx_size;

    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_TX, DISABLE);
    hperh->tx_count = 0;
    ald_uart_interrupt_config(hperh, ALD_UART_IT_TBC, ENABLE);
    CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    return;
}

/**
  * @brief  DMA uart receive process complete callback.
  * @param  arg: Pointer to a uart_handle_t structure.
  * @retval None
  */
static void uart_dma_recv_cplt(void *arg)
{
    uint32_t stat = 0;

    ald_uart_handle_t *hperh = (ald_uart_handle_t *)arg;
    hperh->tx_count = hperh->tx_size;

    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_RX, DISABLE);
    hperh->rx_count = 0;
    CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);
    stat = hperh->perh->STAT;

    /* Handle parity error */
    if ((READ_BIT(stat, ALD_UART_STATUS_PERR)) != RESET)
        hperh->err_code |= ALD_UART_ERROR_PE;

    /* Handle frame error */
    if ((READ_BIT(stat, ALD_UART_STATUS_FERR)) != RESET)
        hperh->err_code |= ALD_UART_ERROR_FE;

    /* Handle rx overflow error */
    if ((READ_BIT(stat, ALD_UART_STATUS_RFOERR)) != RESET) {
        hperh->err_code |= ALD_UART_ERROR_ORE;
    }

    if (hperh->rx_cplt_cbk)
        hperh->rx_cplt_cbk(hperh);

    return;
}

/**
  * @brief  This function handles uart Communication Timeout.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: specifies the uart flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t uart_wait_flag(ald_uart_handle_t *hperh, ald_uart_status_t flag, flag_status_t status, uint32_t timeout)
{
    uint32_t tick;

    if (timeout == 0)
        return ALD_ERROR;

    tick = ald_get_tick();

    /* Waiting for flag */
    while ((ald_uart_get_status(hperh, flag)) != status)
    {
        if (((ald_get_tick()) - tick) > timeout)
            return ALD_TIMEOUT;
    }

    return ALD_OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_send_by_it(ald_uart_handle_t *hperh)
{
    if ((hperh->state & ALD_UART_STATE_TX_MASK) == 0x0)
        return ALD_BUSY;

    hperh->perh->TXBUF = (uint8_t)(*hperh->tx_buf++ & 0x00FF);
    hperh->tx_count++;

    if (hperh->tx_count >= hperh->tx_size)
    {
        ald_uart_interrupt_config(hperh, ALD_UART_IT_TFEMPTY, DISABLE);
        ald_uart_interrupt_config(hperh, ALD_UART_IT_TBC, ENABLE);
    }

    return ALD_OK;
}

/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hperh: pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_end_send_by_it(ald_uart_handle_t *hperh)
{
    uint32_t cnt = 0xFFFFFF;

    ald_uart_interrupt_config(hperh, ALD_UART_IT_TBC, DISABLE);
    CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    while ((hperh->perh->STAT & ALD_UART_STATUS_TSBUSY) && (cnt--));
    ald_uart_clear_flag_status(hperh, ALD_UART_IF_TBC);
    if (hperh->tx_cplt_cbk)
        hperh->tx_cplt_cbk(hperh);

    return ALD_OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __uart_recv_by_it(ald_uart_handle_t *hperh)
{
    if ((hperh->state & ALD_UART_STATE_RX_MASK) == 0x0)
        return ALD_BUSY;

    *hperh->rx_buf++ = (uint8_t)(hperh->perh->RXBUF & 0xFF);
    hperh->rx_count++;

    if (hperh->rx_count >= hperh->rx_size)
    {
        ald_uart_interrupt_config(hperh, ALD_UART_IT_RFNEMPTY, DISABLE);
        CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

        if (hperh->rx_cplt_cbk)
            hperh->rx_cplt_cbk(hperh);
    }

    return ALD_OK;
}
/**
  * @}
  */
/** @defgroup UART_Public_Functions UART Public Functions
  * @{
  */
/** @defgroup UART_Public_Functions_Group1 Initialization and Configuration functions
  * @brief    Initialization and Configuration functions
  *
  * @verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the UARTx
    and configure UARTx param.
      (+) For the UARTx only these parameters can be configured:
        (++) Baud Rate
        (++) Word Length
        (++) Stop Bit
        (++) Parity
        (++) Hardware flow control
      (+) For RS485 mode, user also need configure some parameters by
          ald_uart_rs485_config():
        (++) Enable/disable normal point mode
    (++) Enable/disable auto-direction
    (++) Enable/disable address detection invert
    (++) Enable/disable address for compare

    @endverbatim
  * @{
  */

/**
  * @brief  Reset UART peripheral
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified uart module.
  * @retval None
  */
void ald_uart_reset(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ALL(hperh->perh));

    WRITE_REG(hperh->perh->BRR, 0x0);
    WRITE_REG(hperh->perh->LCON, 0x0);
    WRITE_REG(hperh->perh->MCON, 0x0);
    WRITE_REG(hperh->perh->RS485, 0x0);
    WRITE_REG(hperh->perh->SCARD, 0x0);
    WRITE_REG(hperh->perh->LIN, 0x0);
    WRITE_REG(hperh->perh->RTOR, 0x0);
    WRITE_REG(hperh->perh->IDR, 0xFFF);
    hperh->err_code = ALD_UART_ERROR_NONE;
    hperh->state    = ALD_UART_STATE_RESET;

    __UNLOCK(hperh);

    return;
}

/**
  * @brief  Initializes the UARTx according to the specified
  *         parameters in the uart_handle_t.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @retval None
  */
void ald_uart_init(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_BAUDRATE(hperh->init.baud));
    assert_param(IS_UART_WORD_LENGTH(hperh->init.word_length));
    assert_param(IS_UART_STOPBITS(hperh->init.stop_bits));
    assert_param(IS_UART_PARITY(hperh->init.parity));
    assert_param(IS_UART_MODE(hperh->init.mode));
    assert_param(IS_UART_HARDWARE_FLOW_CONTROL(hperh->init.fctl));

    ald_uart_reset(hperh);

    MODIFY_REG(hperh->perh->LCON, UART_LCON_DLS_MSK, hperh->init.word_length << UART_LCON_DLS_POSS);
    MODIFY_REG(hperh->perh->LCON, UART_LCON_STOP_MSK, hperh->init.stop_bits << UART_LCON_STOP_POS);

    if ((hperh->init.parity) != ALD_UART_PARITY_NONE)
    {
        SET_BIT(hperh->perh->LCON, UART_LCON_PE_MSK);

        if ((hperh->init.parity) == ALD_UART_PARITY_ODD)
            CLEAR_BIT(hperh->perh->LCON, UART_LCON_PS_MSK);

        if ((hperh->init.parity) == ALD_UART_PARITY_EVEN)
            SET_BIT(hperh->perh->LCON, UART_LCON_PS_MSK);
    }

    MODIFY_REG(hperh->perh->MCON, UART_MCON_AFCEN_MSK, hperh->init.fctl << UART_MCON_AFCEN_POS);
    hperh->perh->BRR = (ald_cmu_get_pclk_clock() + (hperh->init.baud >> 1)) / hperh->init.baud;

    if (hperh->init.mode == ALD_UART_MODE_LIN)
        SET_BIT(hperh->perh->LIN, UART_LIN_LINEN_MSK);
    else if (hperh->init.mode == ALD_UART_MODE_IrDA)
        SET_BIT(hperh->perh->MCON, UART_MCON_IREN_MSK);
    else if (hperh->init.mode == ALD_UART_MODE_RS485)
        SET_BIT(hperh->perh->RS485, UART_RS485_AADEN_MSK);
    else if (hperh->init.mode == ALD_UART_MODE_HDSEL)
        SET_BIT(hperh->perh->MCON, UART_MCON_HDEN_MSK);
    else if (hperh->init.mode == ALD_UART_MODE_SCARD)
        SET_BIT(hperh->perh->SCARD, UART_SCARD_SCEN_MSK);
    else
        ;   /* do nothing */

    SET_BIT(hperh->perh->LCON, UART_LCON_RXEN_MSK);
    SET_BIT(hperh->perh->LCON, UART_LCON_TXEN_MSK);

    hperh->state    = ALD_UART_STATE_READY;
    hperh->err_code = ALD_UART_ERROR_NONE;
    return;
}

/**
  * @brief  Configure the RS485 mode according to the specified
  *         parameters in the uart_rs485_config_t.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  config: Specifies the RS485 parameters.
  * @retval None
  */
void ald_uart_rs485_config(ald_uart_handle_t *hperh, ald_uart_rs485_config_t *config)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_FUNC_STATE(config->normal));
    assert_param(IS_FUNC_STATE(config->dir));
    assert_param(IS_FUNC_STATE(config->invert));

    MODIFY_REG(hperh->perh->RS485, UART_RS485_AADNEN_MSK, config->normal << UART_RS485_AADNEN_POS);
    MODIFY_REG(hperh->perh->RS485, UART_RS485_AADACEN_MSK, config->dir << UART_RS485_AADACEN_POS);
    MODIFY_REG(hperh->perh->RS485, UART_RS485_AADINV_MSK, config->invert << UART_RS485_AADINV_POS);
    MODIFY_REG(hperh->perh->RS485, UART_RS485_ADDR_MSK, config->addr << UART_RS485_ADDR_POSS);

    return;
}

/**
  * @brief  Configure the smart card mode according to the specified
  *         parameters in the uart_scard_config_t.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  config: Specifies the scard parameters.
  * @retval None
  */
void ald_uart_scard_config(ald_uart_handle_t *hperh, ald_uart_scard_config_t *config)
{
    assert_param(IS_UART_ENHANCE(hperh->perh));
    assert_param(IS_UART_SCARD_CLK(config->clk_div));

    MODIFY_REG(hperh->perh->SCARD, UART_SCARD_BLEN_MSK, config->block_len << UART_SCARD_BLEN_POSS);
    MODIFY_REG(hperh->perh->SCARD, UART_SCARD_GT_MSK, config->pt << UART_SCARD_GT_POSS);
    MODIFY_REG(hperh->perh->SCARD, UART_SCARD_SCCNT_MSK, config->retry << UART_SCARD_SCCNT_POSS);
    MODIFY_REG(hperh->perh->SCARD, UART_SCARD_PSC_MSK, config->clk_div << UART_SCARD_PSC_POSS);
    MODIFY_REG(hperh->perh->SCARD, UART_SCARD_SCLKEN_MSK, config->clk_out << UART_SCARD_SCLKEN_POS);

    return;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group2 IO operation functions
  * @brief UART Transmit and Receive functions
  * @verbatim
  ==============================================================================
                      # IO operation functions #
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the UART data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The Status of all data processing is returned by the same function
            after finishing transfer.
       (++) Non blocking mode: The communication is performed using Interrupts
            or DMA, these APIs return the Status.
            The end of the data processing will be indicated through the
            dedicated UART IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
            will be executed respectively at the end of the transmit or receive process.
            The hperh->error_cbk() user callback will be executed when
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) ald_uart_send()
        (++) ald_uart_recv()

    (#) Non Blocking mode APIs with Interrupt are:
        (++) ald_uart_send_by_it()
        (++) ald_uart_recv_by_it()
        (++) ald_uart_irq_handler()

    (#) Non Blocking mode functions with DMA are:
        (++) ald_uart_send_by_dma()
        (++) ald_uart_recv_by_dma()
        (++) ald_uart_dma_pause()
        (++) ald_uart_dma_resume()
        (++) ald_uart_dma_stop()

    (#) A set of transfer complete callbacks are provided in non blocking mode:
        (++) hperh->tx_cplt_cbk()
        (++) hperh->rx_cplt_cbk()
        (++) hperh->error_cbk()

    @endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_RX))
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return  ALD_ERROR;

    __LOCK(hperh);
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    hperh->tx_size  = size;
    hperh->tx_count = 0;

    while (size-- > 0)
    {
        if (uart_wait_flag(hperh, ALD_UART_STATUS_TFEMPTY, SET, timeout) != ALD_OK) {
            __UNLOCK(hperh);
            hperh->state = ALD_UART_STATE_READY;
            return ALD_TIMEOUT;
        }

        hperh->perh->TXBUF = (*buf++ & 0xFF);
        hperh->tx_count++;
    }

    if (uart_wait_flag(hperh, ALD_UART_STATUS_TSBUSY, RESET, timeout) != ALD_OK)
    {
        __UNLOCK(hperh);
        hperh->state = ALD_UART_STATE_READY;
        return ALD_TIMEOUT;
    }

    CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Receives an amount of data in blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    uint32_t stat = 0;
    uint32_t err  = 0;
    uint32_t tick = 0;

    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_TX))
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0) || (timeout == 0))
        return ALD_ERROR;

    __LOCK(hperh);
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

    hperh->rx_size  = size;
    hperh->rx_count = 0;

    err = (ALD_UART_STATUS_PERR | ALD_UART_STATUS_FERR | ALD_UART_STATUS_RFOERR);

    while (size-- > 0)
    {
        tick = ald_get_tick();

        /* Waiting for flag */
        while (1)
        {
            stat = hperh->perh->STAT;
            if (READ_BIT(stat, ALD_UART_STATUS_RFNEMPTY) != RESET)
                break;

            if (((ald_get_tick()) - tick) > timeout)
            {
                __UNLOCK(hperh);
                hperh->state = ALD_UART_STATE_READY;
                return ALD_TIMEOUT;
            }
        }

        if ((stat & err) == RESET)
        {
            *buf++ = (uint8_t)(hperh->perh->RXBUF & 0xFF);
            hperh->rx_count++;
        }
        else
        {
            /* Handle parity error */
            if ((READ_BIT(stat, ALD_UART_STATUS_PERR)) != RESET)
                hperh->err_code |= ALD_UART_ERROR_PE;

            /* Handle frame error */
            if ((READ_BIT(stat, ALD_UART_STATUS_FERR)) != RESET)
                hperh->err_code |= ALD_UART_ERROR_FE;

            /* Handle rx overflow error */
            if ((READ_BIT(stat, ALD_UART_STATUS_RFOERR)) != RESET)
                hperh->err_code |= ALD_UART_ERROR_ORE;

            CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);
            __UNLOCK(hperh);

            return ALD_ERROR;
        }
    }

    CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Sends an amount of data in blocking mode.
              Don't care about device lock. This is for RTOS.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send_n_lock(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_RX))
        return ALD_BUSY;
    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    hperh->tx_size  = size;
    hperh->tx_count = 0;

    while (size-- > 0)
    {
        if (uart_wait_flag(hperh, ALD_UART_STATUS_TFEMPTY, SET, timeout) != ALD_OK)
        {
            hperh->state = ALD_UART_STATE_READY;
            return ALD_TIMEOUT;
        }

        hperh->perh->TXBUF = (*buf++ & 0xFF);
        hperh->tx_count++;
    }

    if (uart_wait_flag(hperh, ALD_UART_STATUS_TSBUSY, RESET, timeout) != ALD_OK)
    {
        hperh->state = ALD_UART_STATE_READY;
        return ALD_TIMEOUT;
    }

    CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);
    return ALD_OK;
}

/**
  * @brief  Receives an amount of data in blocking mode.
              Don't care about device lock. This is for RTOS.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_n_lock(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_TX))
        return ALD_BUSY;
    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

    hperh->rx_size  = size;
    hperh->rx_count = 0;

    while (size-- > 0)
    {
        if (uart_wait_flag(hperh, ALD_UART_STATUS_RFNEMPTY, SET, timeout) != ALD_OK)
        {
            hperh->state = ALD_UART_STATE_READY;
            return ALD_TIMEOUT;
        }

        *buf++ = (uint8_t)(hperh->perh->RXBUF & 0xFF);
        hperh->rx_count++;
    }

    CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);
    return ALD_OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_RX))
        return ALD_BUSY;

    if ((buf == NULL ) || (size == 0))
        return ALD_ERROR;

    __LOCK(hperh);

    hperh->tx_buf   = buf;
    hperh->tx_size  = size;
    hperh->tx_count = 0;
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    __UNLOCK(hperh);
    SET_BIT(hperh->perh->ICR, UART_ICR_TFEMPTY_MSK);
    ald_uart_interrupt_config(hperh, ALD_UART_IT_TFEMPTY, ENABLE);

    return ALD_OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_TX))
        return ALD_BUSY;

    if ((buf == NULL ) || (size == 0))
        return ALD_ERROR;

    __LOCK(hperh);
    hperh->rx_buf   = buf;
    hperh->rx_size  = size;
    hperh->rx_count = 0;
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

    __UNLOCK(hperh);
    SET_BIT(hperh->perh->ICR, UART_ICR_RFNEMPTY_MSK);
    ald_uart_interrupt_config(hperh, ALD_UART_IT_RFNEMPTY, ENABLE);

    return ALD_OK;
}

/**
  * @brief  Receives an frame of data in non blocking mode
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Max length of frame.
  * @param  t_out: Timeout duration.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_frame_by_it(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t t_out)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_TX))
        return ALD_BUSY;

    if ((buf == NULL ) || (t_out == 0) || (t_out > 0xFFFFFF) || (size == 0))
        return ALD_ERROR;

    __LOCK(hperh);
    hperh->rx_buf   = buf;
    hperh->rx_size  = size;
    hperh->rx_count = 0;
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

    __UNLOCK(hperh);
    SET_BIT(hperh->perh->ICR, UART_ICR_RFNEMPTY_MSK);
    SET_BIT(hperh->perh->RTOR, UART_RTOR_RTOEN_MSK);
    MODIFY_REG(hperh->perh->RTOR, UART_RTOR_RTO_MSK, t_out << UART_RTOR_RTO_POSS);
    ald_uart_interrupt_config(hperh, ALD_UART_IT_RFNEMPTY, ENABLE);
    ald_uart_interrupt_config(hperh, ALD_UART_IT_RXTO, ENABLE);

    return ALD_OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as UART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_send_by_dma(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_RX))
        return ALD_BUSY;

    if ((buf == NULL ) || (size == 0))
        return ALD_ERROR;

    __LOCK(hperh);

    hperh->tx_buf   = buf;
    hperh->tx_size  = size;
    hperh->tx_count = 0;
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    if (hperh->hdmatx.perh == NULL)
        hperh->hdmatx.perh = DMA;

    /* Set the dma parameters */
    hperh->hdmatx.cplt_tc_cbk = uart_dma_send_cplt;
    hperh->hdmatx.cplt_tc_arg = (void *)hperh;

    ald_dma_config_struct(&hperh->hdmatx.config);
    hperh->hdmatx.config.src     = (void *)buf;
    hperh->hdmatx.config.dst     = (void *)&hperh->perh->TXBUF;
    hperh->hdmatx.config.size    = size;
    hperh->hdmatx.config.src_inc = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmatx.config.dst_inc = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmatx.config.msigsel = ALD_DMA_MSIGSEL_UART_TXEMPTY;
    hperh->hdmatx.config.channel = channel;

    if (hperh->init.mode == ALD_UART_MODE_RS485)
        hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_HALFWORD;

    if (hperh->perh == CUART0)
        hperh->hdmatx.config.msel = ALD_DMA_MSEL_CUART0;
    else if (hperh->perh == CUART1)
        hperh->hdmatx.config.msel = ALD_DMA_MSEL_CUART1;
    else if (hperh->perh == CUART2)
        hperh->hdmatx.config.msel = ALD_DMA_MSEL_CUART2;
    else if (hperh->perh == EUART0)
        hperh->hdmatx.config.msel = ALD_DMA_MSEL_EUART0;
    else if (hperh->perh == EUART1)
        hperh->hdmatx.config.msel = ALD_DMA_MSEL_EUART1;
    else
        ;   /* do nothing */

    ald_dma_config_basic(&hperh->hdmatx);
    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);

    __UNLOCK(hperh);
    ald_uart_clear_flag_status(hperh, ALD_UART_IF_TBC);
    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_TX, ENABLE);

    return ALD_OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  channel: DMA channel as UART receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_recv_by_dma(ald_uart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_TX))
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    __LOCK(hperh);

    hperh->rx_buf   = buf;
    hperh->rx_size  = size;
    hperh->err_code = ALD_UART_ERROR_NONE;
    SET_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

    if (hperh->hdmarx.perh == NULL)
        hperh->hdmarx.perh = DMA;

    /* Set the dma parameters */
    hperh->hdmarx.cplt_tc_cbk = uart_dma_recv_cplt;
    hperh->hdmarx.cplt_tc_arg = (void *)hperh;

    ald_dma_config_struct(&hperh->hdmarx.config);
    hperh->hdmarx.config.src     = (void *)&hperh->perh->RXBUF;
    hperh->hdmarx.config.dst     = (void *)buf;
    hperh->hdmarx.config.size    = size;
    hperh->hdmarx.config.src_inc = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmarx.config.dst_inc = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmarx.config.msigsel = ALD_DMA_MSIGSEL_UART_RNR;
    hperh->hdmarx.config.channel = channel;

    if (hperh->init.mode == ALD_UART_MODE_RS485)
        hperh->hdmarx.config.dst_data_width = ALD_DMA_DATA_SIZE_HALFWORD;

    if (hperh->perh == CUART0)
        hperh->hdmarx.config.msel = ALD_DMA_MSEL_CUART0;
    else if (hperh->perh == CUART1)
        hperh->hdmarx.config.msel = ALD_DMA_MSEL_CUART1;
    else if (hperh->perh == CUART2)
        hperh->hdmarx.config.msel = ALD_DMA_MSEL_CUART2;
    else if (hperh->perh == EUART0)
        hperh->hdmarx.config.msel = ALD_DMA_MSEL_EUART0;
    else if (hperh->perh == EUART1)
        hperh->hdmarx.config.msel = ALD_DMA_MSEL_EUART1;
    else
        ;

    __UNLOCK(hperh);
    ald_dma_config_basic(&hperh->hdmarx);
    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_RX, ENABLE);

    return ALD_OK;
}

/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_pause(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ALL(hperh->perh));

    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_TX, DISABLE);
    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_RX, DISABLE);
    return ALD_OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_resume(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ALL(hperh->perh));

    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_TX, ENABLE);
    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_RX, ENABLE);
    return ALD_OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_uart_dma_stop(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ALL(hperh->perh));

    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_TX, DISABLE);
    ald_uart_dma_req_config(hperh, ALD_UART_DMA_REQ_RX, DISABLE);
    hperh->state = ALD_UART_STATE_READY;
    return ALD_OK;
}

/**
  * @brief  This function handles UART interrupt request.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval None
  */
void ald_uart_irq_handler(ald_uart_handle_t *hperh)
{
    uint32_t stat = 0;

    assert_param(IS_UART_ALL(hperh->perh));

    stat = hperh->perh->STAT;

    /* Handle parity error */
    if (((READ_BIT(stat, ALD_UART_STATUS_PERR)) != RESET) && \
        (ald_uart_get_state(hperh)) == ALD_UART_STATE_RX_MASK)
        hperh->err_code |= ALD_UART_ERROR_PE;

    /* Handle frame error */
    if (((READ_BIT(stat, ALD_UART_STATUS_FERR)) != RESET) && \
        (ald_uart_get_state(hperh)) == ALD_UART_STATE_RX_MASK)
        hperh->err_code |= ALD_UART_ERROR_FE;

    /* Handle rx overflow error */
    if (((READ_BIT(stat, ALD_UART_STATUS_RFOERR)) != RESET) && \
        (ald_uart_get_state(hperh)) == ALD_UART_STATE_RX_MASK)
        hperh->err_code |= ALD_UART_ERROR_ORE;

    /* Handle tx overflow error */
    if (((READ_BIT(stat, ALD_UART_STATUS_TFOERR)) != RESET) && \
        (ald_uart_get_state(hperh)) == ALD_UART_STATE_TX_MASK)
        hperh->err_code |= ALD_UART_ERROR_ORE;

    /* Receive */
    if ((ald_uart_get_mask_flag_status(hperh, ALD_UART_IF_RFNEMPTY)) != RESET)
    {
        __uart_recv_by_it(hperh);
        ald_uart_clear_flag_status(hperh, ALD_UART_IF_RFNEMPTY);
    }

    /* Transmit */
    if ((ald_uart_get_mask_flag_status(hperh, ALD_UART_IF_TFEMPTY)) != RESET)
    {
        __uart_send_by_it(hperh);
        ald_uart_clear_flag_status(hperh, ALD_UART_IF_TFEMPTY);
    }

    /* End Transmit */
    if ((ald_uart_get_mask_flag_status(hperh, ALD_UART_IF_TBC)) != RESET)
    {
        __uart_end_send_by_it(hperh);
        ald_uart_clear_flag_status(hperh, ALD_UART_IF_TBC);
    }

    /* Receive frame timeout*/
    if ((ald_uart_get_mask_flag_status(hperh, ALD_UART_IF_RXTO)) != RESET)
    {
        ald_uart_clear_flag_status(hperh, ALD_UART_IF_RXTO);

        ald_uart_interrupt_config(hperh, ALD_UART_IT_RXTO, DISABLE);
        CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

        if (hperh->rx_cplt_cbk)
            hperh->rx_cplt_cbk(hperh);
    }

    /* Handle error state */
    if (hperh->err_code != ALD_UART_ERROR_NONE)
    {
        hperh->state = ALD_UART_STATE_READY;

        if (hperh->error_cbk)
            hperh->error_cbk(hperh);
    }
}

/**
  * @brief  This function handles UART interrupt request.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval None
  */
void ald_uart_irq_handler_fast(ald_uart_handle_t *hperh)
{
    volatile uint32_t tmp = hperh->perh->IFM;

    /* Transmit */
    if (tmp & 0x10000)
    {
        hperh->perh->ICR   = 0x10000;
        hperh->perh->TXBUF = *hperh->tx_buf++;
        ++hperh->tx_count;

        if (hperh->tx_count >= hperh->tx_size)
        {
            hperh->perh->IDR = 0x10000;
            CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

            if (hperh->tx_cplt_cbk)
                hperh->tx_cplt_cbk(hperh);
        }
    }
    /* End Transmit */
    if (tmp & 0x4000)
    {
        hperh->perh->ICR = 0x4000;
        hperh->perh->IDR = 0x4000;
        CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

        if (hperh->tx_cplt_cbk)
            hperh->tx_cplt_cbk(hperh);
    }

    /* Receive*/
    if (tmp & 0x400)
    {
        hperh->perh->ICR = 0x400;
        *hperh->rx_buf++ = (uint8_t)(hperh->perh->RXBUF & 0xFF);
        ++hperh->rx_count;

        if (hperh->rx_count >= hperh->rx_size)
        {
            hperh->perh->IDR = 0x400;
            CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

            if (hperh->rx_cplt_cbk)
                hperh->rx_cplt_cbk(hperh);
        }
    }
    /* Receive frame */
    if (tmp & 0x10)
    {
        hperh->perh->ICR = 0x10;
        hperh->perh->IDR = 0x10;
        CLEAR_BIT(hperh->state, ALD_UART_STATE_RX_MASK);

        if (hperh->rx_cplt_cbk)
            hperh->rx_cplt_cbk(hperh);
    }

    return;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group3 Peripheral Control functions
  *  @brief   UART control functions
  *
  * @verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control the UART:
    (+) ald_uart_interrupt_config() API can be helpful to configure UART interrupt source.
    (+) ald_uart_dma_req_config() API can be helpful to configure UART DMA request.
    (+) ald_uart_tx_fifo_config() API can be helpful to configure UART TX FIFO paramters.
    (+) ald_uart_rx_fifo_config() API can be helpful to configure UART RX FIFO paramters.
    (+) ald_uart_lin_send_break() API can send a frame of break in LIN mode.
    (+) ald_uart_lin_detect_break_len_config() API can be helpful to configure the length of break frame.
    (+) ald_uart_auto_baud_config() API can be helpful to configure detection data mode.
    (+) ald_uart_get_it_status() API can get the status of interrupt source.
    (+) ald_uart_get_status() API can get the status of UART_SR register.
    (+) ald_uart_get_flag_status() API can get the status of UART flag.
    (+) ald_uart_get_mask_flag_status() API can get status os flag and interrupt source.
    (+) ald_uart_clear_flag_status() API can clear UART flag.

    @endverbatim
  * @{
  */

/**
  * @brief  Enable/disable the specified UART interrupts.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  it: Specifies the UART interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref uart_it_t.
  * @param  state: New state of the specified UART interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_uart_interrupt_config(ald_uart_handle_t *hperh, ald_uart_it_t it, type_func_t state)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_IT(it));
    assert_param(IS_FUNC_STATE(state));

    if (state == ENABLE)
        hperh->perh->IER = it;
    else
        hperh->perh->IDR = it;

    return;
}

/**
  * @brief  Configure UART DMA request.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  req: The type of DMA request.
  * @param  state: New state of the specified DMA request.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_uart_dma_req_config(ald_uart_handle_t *hperh, ald_uart_dma_req_t req, type_func_t state)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_DMA_REQ(req));
    assert_param(IS_FUNC_STATE(state));

    if (req == ALD_UART_DMA_REQ_TX)
    {
        if (state == ENABLE)
            SET_BIT(hperh->perh->MCON, UART_MCON_TXDMAEN_MSK);
        else
            CLEAR_BIT(hperh->perh->MCON, UART_MCON_TXDMAEN_MSK);
    }
    else
    {
        if (state == ENABLE)
            SET_BIT(hperh->perh->MCON, UART_MCON_RXDMAEN_MSK);
        else
            CLEAR_BIT(hperh->perh->MCON, UART_MCON_RXDMAEN_MSK);
    }

    return;
}

/**
  * @brief  Enable/Disable break signal detect interrup.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  status: The new status.
  * @retval None
  */
void uart_lin_break_detect_irq(ald_uart_handle_t *hperh, type_func_t status)
{
    assert_param(IS_UART_ENHANCE(hperh->perh));

    if (status == ENABLE)
        SET_BIT(hperh->perh->IER, UART_IER_LINBK_MSK);
    else
        CLEAR_BIT(hperh->perh->IER, UART_IER_LINBK_MSK);

    return;
}

/**
  * @brief  request to send a frame of break.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval None
  */
void ald_uart_lin_send_break(ald_uart_handle_t *hperh)
{
    assert_param(IS_UART_ENHANCE(hperh->perh));

    SET_BIT(hperh->perh->LIN, UART_LIN_LINBKREQ_MSK);
    hperh->perh->TXBUF = 0x55;

    return;
}

/**
  * @brief  Configure the length of break frame to be detect.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  len: Length of break frame.
  *           @arg LIN_BREAK_LEN_10B
  *           @arg LIN_BREAK_LEN_11B
  * @retval None
  */
void ald_uart_lin_detect_break_len_config(ald_uart_handle_t *hperh, ald_uart_lin_break_len_t len)
{
    assert_param(IS_UART_ENHANCE(hperh->perh));
    assert_param(IS_UART_LIN_BREAK_LEN(len));

    MODIFY_REG(hperh->perh->LIN, UART_LIN_LINBDL_MSK, len << UART_LIN_LINBDL_POS);

    return;
}

/**
  * @brief  Configure the mode of auto-baud-rate detect.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  mode: The mode of auto-baud-rate detect.
  *           @arg UART_ABRMOD_1_TO_0
  *           @arg UART_ABRMOD_1
  *           @arg UART_ABRMOD_0_TO_1
  * @retval None
  */
void ald_uart_auto_baud_config(ald_uart_handle_t *hperh, ald_uart_auto_baud_mode_t mode)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_AUTO_BAUD_MODE(mode));

    MODIFY_REG(hperh->perh->MCON, UART_MCON_ABRMOD_MSK, mode << UART_MCON_ABRMOD_POSS);

    return;
}

/**
  * @brief  Send address in RS485 mode.
  * @param  hperh: Pointer to a uart_handle_t structure that contains
  *         the configuration information for the specified UART module.
  * @param  addr: the address of RS485 device.
  * @param  timeout: Timeout duration
  * @retval The ALD status.
  */
ald_status_t ald_uart_rs485_send_addr(ald_uart_handle_t *hperh, uint16_t addr, uint32_t timeout)
{
    assert_param(IS_UART_ALL(hperh->perh));

    if ((hperh->state != ALD_UART_STATE_READY) && (hperh->state != ALD_UART_STATE_BUSY_RX))
        return ALD_BUSY;

    SET_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    if (uart_wait_flag(hperh, ALD_UART_STATUS_TFEMPTY, SET, timeout) != ALD_OK)
    {
        hperh->state = ALD_UART_STATE_READY;
        return ALD_TIMEOUT;
    }
    WRITE_REG(hperh->perh->TXBUF, (addr | 0x100));

    if (uart_wait_flag(hperh, ALD_UART_STATUS_TFEMPTY, SET, timeout) != ALD_OK)
    {
        hperh->state = ALD_UART_STATE_READY;
        return ALD_TIMEOUT;
    }

    CLEAR_BIT(hperh->state, ALD_UART_STATE_TX_MASK);

    return ALD_OK;
}

/**
  * @brief  Get the status of UART interrupt source.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  it: Specifies the UART interrupt source.
  *         This parameter can be one of the @ref uart_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_uart_get_it_status(ald_uart_handle_t *hperh, ald_uart_it_t it)
{
    it_status_t status = RESET;

    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_IT(it));

    if (hperh->perh->IVS & it)
        status = SET;

    return status;
}

/**
  * @brief  Get the status of UART_SR register.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  status: Specifies the UART status type.
  *         This parameter can be one of the @ref uart_status_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_status(ald_uart_handle_t *hperh, ald_uart_status_t status)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_STATUS(status));

    if (hperh->perh->STAT & status)
        return SET;

    return RESET;
}


/**
  * @brief  Get the status of UART interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_IF(flag));

    if (hperh->perh->RIF & flag)
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_uart_get_mask_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_IF(flag));

    if (hperh->perh->IFM & flag)
        return SET;

    return RESET;
}

/**
  * @brief  Clear the UART interrupt flag.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @param  flag: Specifies the UART interrupt flag.
  *         This parameter can be one of the @ref uart_flag_t.
  * @retval None
  */
void ald_uart_clear_flag_status(ald_uart_handle_t *hperh, ald_uart_flag_t flag)
{
    assert_param(IS_UART_ALL(hperh->perh));
    assert_param(IS_UART_IF(flag));

    hperh->perh->ICR = flag;
    return;
}
/**
  * @}
  */

/** @defgroup UART_Public_Functions_Group4 Peripheral State and Errors functions
  *  @brief   UART State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   UART communication process, return Peripheral Errors occurred during communication
   process
   (+) ald_uart_get_state() API can be helpful to check in run-time the state of the UART peripheral.
   (+) ald_uart_get_error() check in run-time errors that could be occurred during communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the UART state.
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval ALD state
  */
ald_uart_state_t ald_uart_get_state(ald_uart_handle_t *hperh)
{
    return hperh->state;
}

/**
  * @brief  Return the UART error code
  * @param  hperh: Pointer to a uart_handle_t structure.
  * @retval UART Error Code
  */
uint32_t ald_uart_get_error(ald_uart_handle_t *hperh)
{
    return hperh->err_code;
}

/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
/**
  * @}
  */
