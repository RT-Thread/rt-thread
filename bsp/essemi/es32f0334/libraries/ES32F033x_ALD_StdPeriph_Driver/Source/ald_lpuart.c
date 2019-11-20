/**
  *********************************************************************************
  *
  * @file    ald_lpuart.c
  * @brief   Low Power UART module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Low Power Universal Asynchronous Receiver
  *          Transmitter (LPUART) peripheral:
  *           + Initialization and Configuration functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Errors functions
  *
  * @version V1.0
  * @date    30 May 2017
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
  [..]
    The LPUART driver can be used as follows:

    (#) Declare a lpuart_handle_t handle structure.

    (#) Initialize the LPUART resources:
        (##) Enable the LPUART interface clock.
        (##) LPUART pins configuration:
            (+++) Enable the clock for the LPUART GPIOs.
            (+++) Configure the LPUART pins (TX as alternate function pull-up, RX as alternate function Input).
        (##) NVIC configuration if you need to use interrupt process (ald_lpuart_send_by_it()
             and ald_lpuart_recv_by_it() APIs):
            (+++) Configure the LPUART interrupt priority.
            (+++) Enable the NVIC LPUART IRQ handle.
        (##) DMA Configuration if you need to use DMA process (ald_lpuart_send_by_dma()
             and ald_lpuart_recv_by_dma() APIs):
            (+++) Declare a DMA handle structure for the Tx/Rx channel.
            (+++) Enable the DMAx interface clock.
            (+++) Configure the declared DMA handle structure with the required
                  Tx/Rx parameters.
            (+++) Configure the DMA Tx/Rx channel.
            (+++) Associate the initialized DMA handle to the LPUART DMA Tx/Rx handle.

    (#) Program the Baud Rate, Word Length, Stop Bit, Parity, Hardware
        flow control and Mode(Receiver/Transmitter) in the hperh Init structure.

    (#) Initialize the LPUART registers by calling the ald_lpuart_init() API.

     [..]
        Three operation modes are available within this driver:

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Send an amount of data in blocking mode using ald_lpuart_send()
       (+) Receive an amount of data in blocking mode using ald_lpuart_recv()

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Send an amount of data in non blocking mode using ald_lpuart_send_by_it()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode using ald_lpuart_recv_by_it()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()

     *** DMA mode IO operation ***
     ==============================
     [..]
       (+) Send an amount of data in non blocking mode (DMA) using ald_lpuart_send_by_dma()
       (+) At transmission end of transfer hperh->tx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->tx_cplt_cbk()
       (+) Receive an amount of data in non blocking mode (DMA) using ald_lpuart_recv_by_dma()
       (+) At reception end of transfer hperh->rx_cplt_cbk() is executed and user can
           add his own code by customization of function pointer hperh->rx_cplt_cbk()
       (+) In case of transfer Error, hperh->error_cbk() function is executed and user can
           add his own code by customization of function pointer hperh->error_cbk()
       (+) Pause the DMA Transfer using ald_lpuart_dma_pause()
       (+) Resume the DMA Transfer using ald_lpuart_dma_resume()
       (+) Stop the DMA Transfer using ald_lpuart_dma_stop()

    @endverbatim
  ******************************************************************************
  */

#include "ald_lpuart.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup LPUART LPUART
  * @brief Low Power UART module driver
  * @{
  */
#ifdef ALD_LPUART

/** @defgroup LPUART_Private_Functions   LPUART Private Functions
  *  @brief   LPUART Private functions
  * @{
  */

#ifdef ALD_DMA
/**
  * @brief  DMA LPUART transmit process complete callback.
  * @param  arg: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
static void lpuart_dma_send_cplt(void *arg)
{
    lpuart_handle_t *hperh = (lpuart_handle_t *)arg;

    hperh->tx_count = 0;
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, DISABLE);
    ald_lpuart_interrupt_config(hperh, LPUART_IT_TC, ENABLE);
}

/**
  * @brief  DMA LPUART receive process complete callback.
  * @param  arg: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
static void lpuart_dma_recv_cplt(void *arg)
{
    lpuart_handle_t *hperh = (lpuart_handle_t *)arg;

    hperh->rx_count = 0;
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, DISABLE);
    CLEAR_BIT(hperh->state, LPUART_STATE_RX_MASK);

    if (hperh->rx_cplt_cbk)
        hperh->rx_cplt_cbk(hperh);
}

/**
  * @brief  DMA LPUART communication error callback.
  * @param  arg: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
static void lpuart_dma_error(void *arg)
{
    lpuart_handle_t *hperh = (lpuart_handle_t *)arg;

    hperh->rx_count  = 0;
    hperh->tx_count  = 0;
    hperh->state     = LPUART_STATE_READY;
    hperh->err_code |= LPUART_ERROR_DMA;

    if (hperh->error_cbk)
        hperh->error_cbk(hperh);
}
#endif

/**
  * @brief  This function handles uart Communication Timeout.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  flag: specifies the uart flag to check.
  * @param  status: The new Flag status (SET or RESET).
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t lpuart_wait_flag(lpuart_handle_t *hperh, lpuart_status_t flag, flag_status_t status, uint32_t timeout)
{
    uint32_t tick;

    if (timeout == 0)
        return OK;

    tick = ald_get_tick();

    /* Waiting for flag */
    while ((ald_lpuart_get_status(hperh, flag)) != status)
    {
        if (((ald_get_tick()) - tick) > timeout)
            return TIMEOUT;
    }

    return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __lpuart_send_by_it(lpuart_handle_t *hperh)
{
    if ((hperh->state & LPUART_STATE_TX_MASK) == 0x0)
        return BUSY;

    WRITE_REG(hperh->perh->TXDR, *hperh->tx_buf++);

    if (--hperh->tx_count == 0)
    {
        ald_lpuart_interrupt_config(hperh, LPUART_IT_TBEMP, DISABLE);
        ald_lpuart_interrupt_config(hperh, LPUART_IT_TC, ENABLE);
    }

    return OK;
}


/**
  * @brief  Wraps up transmission in non blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __lpuart_end_send_by_it(lpuart_handle_t *hperh)
{
    ald_lpuart_interrupt_config(hperh, LPUART_IT_TC, DISABLE);
    CLEAR_BIT(hperh->state, LPUART_STATE_TX_MASK);

    if (hperh->tx_cplt_cbk)
        hperh->tx_cplt_cbk(hperh);

    return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
static ald_status_t __lpuart_recv_by_it(lpuart_handle_t *hperh)
{
    uint8_t tmp;
    uint16_t i;

    if ((hperh->state & LPUART_STATE_RX_MASK) == 0x0)
        return BUSY;

    do
    {
        i   = 10000;
        tmp = hperh->perh->STAT & LPUART_STAT_RXPTR_MSK;
        *hperh->rx_buf++ = (uint8_t)(hperh->perh->RXDR & 0xFF);
        --hperh->rx_count;

        while (((hperh->perh->STAT & LPUART_STAT_RXPTR_MSK) != tmp - 1) && (i--));
    }
    while (hperh->perh->STAT & LPUART_STAT_RXPTR_MSK);

    if (hperh->rx_count == 0)
    {
        ald_lpuart_interrupt_config(hperh, LPUART_IT_RBR, DISABLE);
        CLEAR_BIT(hperh->state, LPUART_STATE_RX_MASK);

        if (hperh->state == LPUART_STATE_READY)
        {
            ald_lpuart_interrupt_config(hperh, LPUART_IT_PERR, DISABLE);
            ald_lpuart_interrupt_config(hperh, LPUART_IT_FERR, DISABLE);
        }

        if (hperh->rx_cplt_cbk)
            hperh->rx_cplt_cbk(hperh);
    }

    return OK;
}
/**
  * @}
  */

/** @defgroup LPUART_Public_Functions LPUART Public Functions
  * @{
  */

/** @defgroup LPUART_Public_Functions_Group1 Initialization and Configuration functions
  *  @brief    Initialization and Configuration functions
  *
@verbatim
===============================================================================
            ##### Initialization and Configuration functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to initialize the LPUART
    and configure LPUART param.
      (+) For the LPUART only these parameters can be configured:
        (++) Baud Rate
        (++) Word Length
        (++) Stop Bit
        (++) Parity
        (++) Hardware flow control
      (+) For RS485 mode, user also need configure some parameters by
      ald_lpuart_rs485_config():
        (++) Enable/disable normal point mode
	(++) Enable/disable auto-address detect
	(++) Enable/disable auto-direction
	(++) Enable/disable address detect
	(++) Enable/disable address for compare

    @endverbatim
  * @{
  */

/**
  * @brief  Reset LPUART peripheral
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
void ald_lpuart_reset(lpuart_handle_t *hperh)
{
    WRITE_REG(hperh->perh->CON0, 0x3000);
    WRITE_REG(hperh->perh->CON1, 0x4);
    WRITE_REG(hperh->perh->CLKDIV, 0x0);
    WRITE_REG(hperh->perh->FIFOCON, 0x0);
    WRITE_REG(hperh->perh->IER, 0x0);
    hperh->err_code = LPUART_ERROR_NONE;
    hperh->state    = LPUART_STATE_RESET;

    __UNLOCK(hperh);
    return;
}

/**
  * @brief  Initializes the LPUART according to the specified
  *         parameters in the lpuart_handle_t.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
void ald_lpuart_init(lpuart_handle_t *hperh)
{
    uint32_t tmp;

    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_BAUDRATE(hperh->init.baud));
    assert_param(IS_LPUART_WORD_LENGTH(hperh->init.word_length));
    assert_param(IS_LPUART_STOPBITS(hperh->init.stop_bits));
    assert_param(IS_LPUART_PARITY(hperh->init.parity));
    assert_param(IS_LPUART_MODE(hperh->init.mode));
    assert_param(IS_LPUART_HARDWARE_FLOW_CONTROL(hperh->init.fctl));

    if ((hperh->init.clock != CMU_LP_PERH_CLOCK_SEL_LOSC)
            && (hperh->init.clock != CMU_LP_PERH_CLOCK_SEL_LRC))
        hperh->init.clock = CMU_LP_PERH_CLOCK_SEL_LRC;

    ald_cmu_lpuart0_clock_select(hperh->init.clock);
    ald_lpuart_reset(hperh);
    LPUART_UPDATE_DISABLE(hperh);

    tmp = READ_REG(hperh->perh->CON0);
    MODIFY_REG(tmp, LPUART_CON0_DATLENTH_MSK, hperh->init.word_length << LPUART_CON0_DATLENTH_POSS);
    MODIFY_REG(tmp, LPUART_CON0_STPLENTH_MSK, hperh->init.stop_bits << LPUART_CON0_STPLENTH_POS);

    if (hperh->init.parity == LPUART_PARITY_NONE)
        CLEAR_BIT(tmp, LPUART_CON0_PARCHKE_MSK);
    else
        SET_BIT(tmp, LPUART_CON0_PARCHKE_MSK);

    if (hperh->init.parity == LPUART_PARITY_EVEN)
        SET_BIT(tmp, LPUART_CON0_EVENPARSEL_MSK);
    else
        CLEAR_BIT(tmp, LPUART_CON0_EVENPARSEL_MSK);

    MODIFY_REG(tmp, LPUART_CON0_ATRTSE_MSK, (hperh->init.fctl & 1) << LPUART_CON0_ATRTSE_POS);
    MODIFY_REG(tmp, LPUART_CON0_ATCTSE_MSK, ((hperh->init.fctl >> 1) & 1) << LPUART_CON0_ATCTSE_POS);
    WRITE_REG(hperh->perh->CON0, tmp);
    WRITE_REG(hperh->perh->CLKDIV, (32768 << 8) / hperh->init.baud);

    if (hperh->init.mode == LPUART_MODE_IrDA)
        CLEAR_BIT(hperh->perh->CON1, LPUART_CON1_IRRXINV_MSK);

    MODIFY_REG(hperh->perh->CON0, LPUART_CON0_MODESEL_MSK, hperh->init.mode << LPUART_CON0_MODESEL_POSS);
    LPUART_UPDATE_ENABLE(hperh);

    while (hperh->perh->SYNCSTAT & 0xF)
        ;

    hperh->state = LPUART_STATE_READY;
    return;
}

/**
  * @brief  Configure the RS485 mode according to the specified
  *         parameters in the lpuart_rs485_config_Typedef.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  config: Specifies the RS485 parameters.
  * @retval None
  */
void ald_lpuart_rs485_config(lpuart_handle_t *hperh, lpuart_rs485_config_t *config)
{
    uint32_t tmp;

    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_FUNC_STATE(config->RS485_NMM));
    assert_param(IS_FUNC_STATE(config->RS485_AAD));
    assert_param(IS_FUNC_STATE(config->RS485_AUD));
    assert_param(IS_FUNC_STATE(config->RS485_ADD_DET));

    tmp = READ_REG(hperh->perh->CON1);
    MODIFY_REG(tmp, LPUART_CON1_NMPMOD_MSK, config->RS485_NMM << LPUART_CON1_NMPMOD_POS);
    MODIFY_REG(tmp, LPUART_CON1_ATADETE_MSK, config->RS485_AAD << LPUART_CON1_ATADETE_POS);
    MODIFY_REG(tmp, LPUART_CON1_ATDIRM_MSK, config->RS485_AUD << LPUART_CON1_ATDIRM_POS);
    MODIFY_REG(tmp, LPUART_CON1_ADETE_MSK, config->RS485_ADD_DET << LPUART_CON1_ADETE_POS);
    MODIFY_REG(tmp, LPUART_CON1_ADDCMP_MSK, config->RS485_ADDCMP << LPUART_CON1_ADDCMP_POSS);
    WRITE_REG(hperh->perh->CON1, tmp);

    return;
}

/**
  * @}
  */

/** @defgroup LPUART_Public_Functions_Group2 IO operation functions
  * @brief    LPUART Transmit and Receive functions
  * @verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to manage the LPUART data transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The status of all data processing is returned by the same function
            after finishing transfer.
       (++) Non blocking mode: The communication is performed using Interrupts
            or DMA, these APIs return the status.
            The end of the data processing will be indicated through the
            dedicated LPUART IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.
            The hperh->tx_cplt_cbk(), hperh->rx_cplt_cbk() user callbacks
            will be executed respectively at the end of the transmit or receive process.
            The hperh->error_cbk() user callback will be executed when
            a communication error is detected.

    (#) Blocking mode APIs are:
        (++) ald_lpuart_send()
        (++) ald_lpuart_recv()

    (#) Non Blocking mode APIs with Interrupt are:
        (++) ald_lpuart_send_by_it()
        (++) ald_lpuart_recv_by_it()
        (++) ald_lpuart_irq_handler()

    (#) Non Blocking mode functions with DMA are:
        (++) ald_lpuart_send_by_dma()
        (++) ald_lpuart_recv_by_dma()
        (++) ald_lpuart_dma_pause()
        (++) ald_lpuart_dma_resume()
        (++) ald_lpuart_dma_stop()

    (#) A set of Transfer Complete Callbacks are provided in non blocking mode:
        (++) hperh->tx_cplt_cbk()
        (++) hperh->rx_cplt_cbk()
        (++) hperh->error_cbk()

    @endverbatim
  * @{
  */

/**
  * @brief  Sends an amount of data in blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_send(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_RX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return  ERROR;

    __LOCK(hperh);
    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_TX_MASK);

    hperh->tx_size  = size;
    hperh->tx_count = size;

    while (hperh->tx_count-- > 0)
    {
        if (lpuart_wait_flag(hperh, LPUART_STAT_TXEMP, SET, timeout) != OK)
        {
            __UNLOCK(hperh);
            hperh->state = LPUART_STATE_READY;
            return TIMEOUT;
        }

        WRITE_REG(hperh->perh->TXDR, *buf++);

        if (lpuart_wait_flag(hperh, LPUART_STAT_TXEMP, RESET, timeout) != OK)
        {
            __UNLOCK(hperh);
            hperh->state = LPUART_STATE_READY;
            return TIMEOUT;
        }
    }

    if (lpuart_wait_flag(hperh, LPUART_STAT_TXIDLE, SET, timeout) != OK)
    {
        __UNLOCK(hperh);
        hperh->state = LPUART_STATE_READY;
        return TIMEOUT;
    }

    CLEAR_BIT(hperh->state, LPUART_STATE_TX_MASK);
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Receives an amount of data in blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_recv(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint32_t timeout)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_TX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return  ERROR;

    __LOCK(hperh);

    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_RX_MASK);

    hperh->rx_size  = size;
    hperh->rx_count = size;

    /* Check the remain data to be received */
    while (hperh->rx_count-- > 0)
    {
        if (lpuart_wait_flag(hperh, LPUART_STAT_RXEMP, RESET, timeout) != OK)
        {
            __UNLOCK(hperh);
            hperh->state = LPUART_STATE_READY;
            return TIMEOUT;
        }

        *buf++ = (uint8_t)(hperh->perh->RXDR & 0xFF);
    }

    CLEAR_BIT(hperh->state, LPUART_STATE_RX_MASK);
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_send_by_it(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_RX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return ERROR;

    __LOCK(hperh);

    hperh->tx_buf   = buf;
    hperh->tx_size  = size;
    hperh->tx_count = size;
    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_TX_MASK);

    __UNLOCK(hperh);
    ald_lpuart_interrupt_config(hperh, LPUART_IT_TBEMP, ENABLE);

    return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_recv_by_it(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_TX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return ERROR;

    __LOCK(hperh);

    hperh->rx_buf   = buf;
    hperh->rx_size  = size;
    hperh->rx_count = size;
    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_RX_MASK);

    __UNLOCK(hperh);

    ald_lpuart_interrupt_config(hperh, LPUART_IT_PERR, ENABLE);
    ald_lpuart_interrupt_config(hperh, LPUART_IT_FERR, ENABLE);
    ald_lpuart_interrupt_config(hperh, LPUART_IT_RBR, ENABLE);

    return OK;
}

#ifdef ALD_DMA
/**
  * @brief  Sends an amount of data in non blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as LPUART transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_send_by_dma(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_RX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return ERROR;

    __LOCK(hperh);

    hperh->tx_buf   = buf;
    hperh->tx_size  = size;
    hperh->tx_count = size;
    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_TX_MASK);

    if (hperh->hdmatx.perh == NULL)
        hperh->hdmatx.perh = DMA0;

    /* Set the dma parameters */
    hperh->hdmatx.cplt_cbk = lpuart_dma_send_cplt;
    hperh->hdmatx.cplt_arg = (void *)hperh;
    hperh->hdmatx.err_cbk  = lpuart_dma_error;
    hperh->hdmatx.err_arg  = (void *)hperh;

    ald_dma_config_struct(&hperh->hdmatx.config);
    hperh->hdmatx.config.src     = (void *)buf;
    hperh->hdmatx.config.dst     = (void *)&hperh->perh->TXDR;
    hperh->hdmatx.config.size    = size;
    hperh->hdmatx.config.src_inc = DMA_DATA_INC_BYTE;
    hperh->hdmatx.config.dst_inc = DMA_DATA_INC_NONE;
    hperh->hdmatx.config.msel    = DMA_MSEL_LPUART0;
    hperh->hdmatx.config.msigsel = DMA_MSIGSEL_LPUART_TXEMPTY;
    hperh->hdmatx.config.channel = channel;

    if (hperh->init.mode == LPUART_MODE_RS485)
    {
        hperh->hdmatx.config.src_inc    = DMA_DATA_INC_HALFWORD;
        hperh->hdmatx.config.data_width = DMA_DATA_SIZE_HALFWORD;
    }

    ald_dma_config_basic(&hperh->hdmatx);
    ald_lpuart_clear_flag_status(hperh, LPUART_IF_TC);
    __UNLOCK(hperh);
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, ENABLE);

    return OK;
}

/**
  * @brief  Receives an amount of data in non blocking mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be received
  * @param  channel: DMA channel as LPUART receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_recv_by_dma(lpuart_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_TX))
        return BUSY;

    if ((buf == NULL) || (size == 0))
        return ERROR;

    __LOCK(hperh);

    hperh->rx_buf   = buf;
    hperh->rx_size  = size;
    hperh->err_code = LPUART_ERROR_NONE;
    SET_BIT(hperh->state, LPUART_STATE_RX_MASK);

    if (hperh->hdmarx.perh == NULL)
        hperh->hdmarx.perh = DMA0;

    /* Set the dma parameters */
    hperh->hdmarx.cplt_cbk = lpuart_dma_recv_cplt;
    hperh->hdmarx.cplt_arg = (void *)hperh;
    hperh->hdmarx.err_cbk  = lpuart_dma_error;
    hperh->hdmarx.err_arg  = (void *)hperh;

    ald_dma_config_struct(&hperh->hdmarx.config);
    hperh->hdmarx.config.src     = (void *)&hperh->perh->RXDR;
    hperh->hdmarx.config.dst     = (void *)buf;
    hperh->hdmarx.config.size    = size;
    hperh->hdmarx.config.src_inc = DMA_DATA_INC_NONE;
    hperh->hdmarx.config.dst_inc = DMA_DATA_INC_BYTE;
    hperh->hdmarx.config.msel    = DMA_MSEL_LPUART0;
    hperh->hdmarx.config.msigsel = DMA_MSIGSEL_LPUART_RNR;
    hperh->hdmarx.config.channel = channel;

    if (hperh->init.mode == LPUART_MODE_RS485)
    {
        hperh->hdmarx.config.dst_inc    = DMA_DATA_INC_HALFWORD;
        hperh->hdmarx.config.data_width = DMA_DATA_SIZE_HALFWORD;
    }

    ald_dma_config_basic(&hperh->hdmarx);
    __UNLOCK(hperh);
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, ENABLE);

    return OK;
}

/**
  * @brief  Pauses the DMA Transfer.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_dma_pause(lpuart_handle_t *hperh)
{
    __LOCK(hperh);

    if (hperh->state == LPUART_STATE_BUSY_TX)
    {
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, DISABLE);
    }
    else if (hperh->state == LPUART_STATE_BUSY_RX)
    {
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, DISABLE);
    }
    else if (hperh->state == LPUART_STATE_BUSY_TX_RX)
    {
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, DISABLE);
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, DISABLE);
    }
    else
    {
        __UNLOCK(hperh);
        return ERROR;
    }

    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Resumes the DMA Transfer.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_dma_resume(lpuart_handle_t *hperh)
{
    __LOCK(hperh);

    if (hperh->state == LPUART_STATE_BUSY_TX)
    {
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, ENABLE);
    }
    else if (hperh->state == LPUART_STATE_BUSY_RX)
    {
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_RXOV);
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, ENABLE);
    }
    else if (hperh->state == LPUART_STATE_BUSY_TX_RX)
    {
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_RXOV);
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, ENABLE);
        ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, ENABLE);
    }
    else
    {
        __UNLOCK(hperh);
        return ERROR;
    }

    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Stops the DMA Transfer.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_lpuart_dma_stop(lpuart_handle_t *hperh)
{
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_TX, DISABLE);
    ald_lpuart_dma_req_config(hperh, LPUART_DMA_REQ_RX, DISABLE);

    hperh->state = LPUART_STATE_READY;
    return OK;
}
#endif

/**
  * @brief  This function handles LPUART interrupt request.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval None
  */
void ald_lpuart_irq_handler(lpuart_handle_t *hperh)
{
    uint32_t flag;
    uint32_t source;

    /* Handle CTS wakeup */
    flag = ald_lpuart_get_flag_status(hperh, LPUART_IF_CTSWK);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_CTSWK);

    if ((flag != RESET) && (source != RESET))
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_CTSWK);

    /* Handle DATA wakeup */
    flag = ald_lpuart_get_flag_status(hperh, LPUART_IF_DATWK);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_DATWK);

    if ((flag != RESET) && (source != RESET))
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_DATWK);

    /* Handle parity error */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_PERR);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_PERR);

    if ((flag != RESET) && (source != RESET))
        hperh->err_code |= LPUART_ERROR_PE;

    /* Handle frame error */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_FERR);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_FERR);

    if ((flag != RESET) && (source != RESET))
        hperh->err_code |= LPUART_ERROR_FE;

    /* Handle overflow error */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_RXOV);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_RXOV);

    if ((flag != RESET) && (source != RESET))
        hperh->err_code |= LPUART_ERROR_ORE;

    /* Receive */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_RBR);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_RBR);

    if ((flag != RESET) && (source != RESET))
        __lpuart_recv_by_it(hperh);

    /* Transmite */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_TBEMP);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_TBEMP);

    if ((flag != RESET) && (source != RESET))
        __lpuart_send_by_it(hperh);

    /* End Transmite */
    flag   = ald_lpuart_get_flag_status(hperh, LPUART_IF_TC);
    source = ald_lpuart_get_it_status(hperh, LPUART_IT_TC);

    if ((flag != RESET) && (source != RESET))
        __lpuart_end_send_by_it(hperh);

    /* Handle error state */
    if (hperh->err_code != LPUART_ERROR_NONE)
    {
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_PERR);
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_FERR);
        ald_lpuart_clear_flag_status(hperh, LPUART_IF_RXOV);
        hperh->state = LPUART_STATE_READY;

        if (hperh->error_cbk)
            hperh->error_cbk(hperh);
    }
}
/**
  * @}
  */

/** @defgroup LPUART_Public_Functions_Group3 Peripheral Control functions
  *  @brief   Low Power UART control functions
  *
  * @verbatim
  ==============================================================================
                      ##### Peripheral Control functions #####
  ==============================================================================
  [..]
    This subsection provides a set of functions allowing to control the LPUART:
    (+) ald_lpuart_interrupt_config() API can be helpful to configure LPUART interrupt source.
    (+) ald_lpuart_tx_interval_config() API can be helpful to configure TX interval.
    (+) ald_lpuart_dma_req_config() API can be helpful to configure LPUART DMA request.
    (+) ald_lpuart_rx_fifo_it_config() API can be helpful to configure LPUART RX FIFO interrupt.
    (+) ald_lpuart_rx_fifo_rts_config() API can be helpful to configure RTS threshold value.
    (+) ald_lpuart_get_flag_status() API can get the status of LPUART flag.
    (+) ald_lpuart_clear_flag_status() API can clear LPUART flag.
    (+) ald_lpuart_get_it_status() API can get the status of interrupt source.

    @endverbatim
  * @{
  */

/**
  * @brief  Enable/disable the specified LPUART interrupts.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  it: Specifies the LPUART interrupt sources to be enabled or
  *         disabled. This parameter can be one of the @ref lpuart_it_t.
  * @param  status: New state of the specified LPUART interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_lpuart_interrupt_config(lpuart_handle_t *hperh, lpuart_it_t it, type_func_t status)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_IT(it));
    assert_param(IS_FUNC_STATE(status));

    if (status == ENABLE)
        SET_BIT(hperh->perh->IER, it);
    else
        CLEAR_BIT(hperh->perh->IER, it);

    return;
}

/**
  * @brief  Configure transmite interval.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  val: The value of interval.
  * @retval None
  */
void ald_lpuart_tx_interval_config(lpuart_handle_t *hperh, uint8_t val)
{
    assert_param(IS_LPUART(hperh->perh));

    MODIFY_REG(hperh->perh->CON0, LPUART_CON0_INTERVAL_MSK, val << LPUART_CON0_INTERVAL_POSS);
    return;
}

/**
  * @brief  Configure LPUART DMA request.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  req: The DMA type:
  *             @arg LPUART_DMA_REQ_TX
  *             @arg LPUART_DMA_REQ_RX
  * @param  status: New state of the specified DMA request.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_lpuart_dma_req_config(lpuart_handle_t *hperh, lpuart_dma_req_t req, type_func_t status)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_DMAREQ(req));
    assert_param(IS_FUNC_STATE(status));

    if (req == LPUART_DMA_REQ_TX)
    {
        if (status == ENABLE)
            SET_BIT(hperh->perh->CON0, LPUART_CON0_TXDMAE_MSK);
        else
            CLEAR_BIT(hperh->perh->CON0, LPUART_CON0_TXDMAE_MSK);
    }
    else
    {
        if (status == ENABLE)
            SET_BIT(hperh->perh->CON0, LPUART_CON0_RXDMAE_MSK);
        else
            CLEAR_BIT(hperh->perh->CON0, LPUART_CON0_RXDMAE_MSK);
    }

    return;
}

/**
  * @brief  Configure receive FIFO interrupt threshold value.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  config: The value of RX FIFO interrupt threshold value.
  * @retval None
  */
void ald_lpuart_rx_fifo_it_config(lpuart_handle_t *hperh, lpuart_rxfifo_t config)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_RXFIFO(config));

    MODIFY_REG(hperh->perh->FIFOCON, LPUART_FIFOCON_RXTRGLVL_MSK, config << LPUART_FIFOCON_RXTRGLVL_POSS);
    return;
}

/**
  * @brief  Configure receive FIFO RTS threshold value.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  config: The value of RX FIFO RTS threshold value.
  * @retval None
  */
void ald_lpuart_rx_fifo_rts_config(lpuart_handle_t *hperh, lpuart_rxfifo_t config)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_RXFIFO(config));

    MODIFY_REG(hperh->perh->FIFOCON, LPUART_FIFOCON_RTSTRGLVL_MSK, config << LPUART_FIFOCON_RTSTRGLVL_POSS);
    return;
}

/**
  * @brief  Send address in RS485 mode.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  addr: the address of RS485 device.
  * @param  timeout: Timeout duration
  * @retval The hal status.
  */
ald_status_t ald_lpuart_rs485_send_addr(lpuart_handle_t *hperh, uint16_t addr, uint32_t timeout)
{
    assert_param(IS_LPUART(hperh->perh));

    if ((hperh->state != LPUART_STATE_READY) && (hperh->state != LPUART_STATE_BUSY_RX))
        return BUSY;

    SET_BIT(hperh->state, LPUART_STATE_TX_MASK);

    if (lpuart_wait_flag(hperh, LPUART_STAT_TXEMP, SET, timeout) != OK)
    {
        hperh->state = LPUART_STATE_READY;
        return TIMEOUT;
    }

    WRITE_REG(hperh->perh->TXDR, addr | 0x100);

    if (lpuart_wait_flag(hperh, LPUART_STAT_TXEMP, RESET, timeout) != OK)
    {
        hperh->state = LPUART_STATE_READY;
        return TIMEOUT;
    }

    if (lpuart_wait_flag(hperh, LPUART_STAT_TXIDLE, SET, timeout) != OK)
    {
        hperh->state = LPUART_STATE_READY;
        return TIMEOUT;
    }

    CLEAR_BIT(hperh->state, LPUART_STATE_TX_MASK);
    return OK;
}

/**
  * @brief  Get the status of LPUART status.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  flag: Specifies the LPUART status flag.
  *         This parameter can be one of the @ref lpuart_status_t.
  * @retval Status:
  *           - RESET
  *           - SET
  */
flag_status_t ald_lpuart_get_status(lpuart_handle_t *hperh, lpuart_status_t flag)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_STAT(flag));

    if (READ_BIT(hperh->perh->STAT, flag))
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of LPUART interrupt flag.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  flag: Specifies the LPUART interrupt flag.
  *         This parameter can be one of the @ref lpuart_flag_t.
  * @retval Status:
  *           - RESET
  *           - SET
  */
flag_status_t ald_lpuart_get_flag_status(lpuart_handle_t *hperh, lpuart_flag_t flag)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_IF(flag));

    if (READ_BIT(hperh->perh->IFLAG, flag))
        return SET;

    return RESET;
}

/**
  * @brief  Clear the LPUART interrupt flag.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  flag: Specifies the LPUART interrupt flag.
  *         This parameter can be one of the @ref lpuart_flag_t.
  * @retval None
  */
void ald_lpuart_clear_flag_status(lpuart_handle_t *hperh, lpuart_flag_t flag)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_IF(flag));

    WRITE_REG(hperh->perh->IFC, flag);
    return;
}

/**
  * @brief  Get the status of LPUART interrupt source.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @param  it: Specifies the LPUART interrupt source.
  *         This parameter can be one of the @ref lpuart_it_t.
  * @retval Status:
  *           - RESET
  *           - SET
  */
it_status_t ald_lpuart_get_it_status(lpuart_handle_t *hperh, lpuart_it_t it)
{
    assert_param(IS_LPUART(hperh->perh));
    assert_param(IS_LPUART_IT(it));

    if (READ_BIT(hperh->perh->IER, it))
        return SET;

    return RESET;
}
/**
  * @}
  */

/** @defgroup LPUART_Public_Functions_Group4 Peripheral State and Errors functions
  *  @brief   LPUART State and Errors functions
  *
@verbatim
  ==============================================================================
                 ##### Peripheral State and Errors functions #####
  ==============================================================================
 [..]
   This subsection provides a set of functions allowing to return the State of
   LPUART communication process, return Peripheral Errors occurred during communication
   process
   (+) ald_lpuart_get_state() API can be helpful to check in run-time the state of the LPUART peripheral.
   (+) ald_lpuart_get_error() check in run-time errors that could be occurred during communication.

@endverbatim
  * @{
  */

/**
  * @brief  Returns the LPUART state.
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART module.
  * @retval HAL state
  */
lpuart_state_t ald_lpuart_get_state(lpuart_handle_t *hperh)
{
    return hperh->state;
}

/**
  * @brief  Return the LPUART error code
  * @param  hperh: Pointer to a lpuart_handle_t structure that contains
  *         the configuration information for the specified LPUART.
  * @retval LPUART Error Code
  */
uint32_t ald_lpuart_get_error(lpuart_handle_t *hperh)
{
    return hperh->err_code;
}

/**
  * @}
  */

/**
  * @}
  */
#endif /* ALD_LPUART */

/**
  * @}
  */

/**
  * @}
  */
