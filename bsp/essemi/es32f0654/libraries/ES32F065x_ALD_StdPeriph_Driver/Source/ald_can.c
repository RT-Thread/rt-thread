/**
  ******************************************************************************
  * @file    ald_can.c
  * @brief   CAN module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the Controller Area Network (CAN) peripheral:
  *           + Initialization  functions
  *           + IO operation functions
  *           + Peripheral Control functions
  *           + Peripheral State and Error functions
  * @version V1.0
  * @date    25 Apr 2017
  * @author  AE Team
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  ********************************************************************************
  * @verbatim
  ==============================================================================
                        ##### How to use this driver #####
  ==============================================================================
    [..]
      (#) Enable the CAN controller interface clock.
      (#) CAN pins configuration
        (++) Enable the clock for the CAN GPIOs;
        (++) Connect and configure the involved CAN pins using the
             following function ald_gpio_init();
      (#) Initialise and configure the CAN using ald_can_init() function.
      (#) Transmit the CAN frame using ald_can_send()/ald_can_send_by_it() function.
      (#) Receive a CAN frame using ald_can_recv()/ald_can_recv_by_it function.

     *** Polling mode IO operation ***
     =================================
     [..]
       (+) Start the CAN peripheral transmission and wait the end of this operation
           using ald_can_send(), at this stage user can specify the value of timeout
           according to his end application.
       (+) Start the CAN peripheral reception and wait the end of this operation
           using ald_can_recv(), at this stage user can specify the value of timeout
           according to his end application

     *** Interrupt mode IO operation ***
     ===================================
     [..]
       (+) Start the CAN peripheral transmission using ald_can_send_by_it()
       (+) Start the CAN peripheral reception using ald_can_recv_by_it()
       (+) Use ald_can_irq_handler() called under the used CAN Interrupt subroutine
       (+) At CAN end of transmission pherh->tx_cplt_cbk() function is executed and user can
            add his own code by customization of function pointer pherh->tx_cplt_cbk()
       (+) In case of CAN Error, pherh->rx_cplt_cbk() function is executed and user can
            add his own code by customization of function pointer pherh->rx_cplt_cbk()

     *** CAN ALD driver macros list ***
     =============================================
     [..]
       Below the list of most used macros in CAN driver.

      (+) CAN_RESET_HANDLE_STATE(): Reset CAN handle state.
      (+) CAN_RX_MSG_PENDING(): Return the number of pending received messages.
      (+) CAN_DBG_FREEZE(): Enable or disables the DBG Freeze for CAN.

     [..]
      (@) You can refer to the CAN driver header file for used the macros

  @endverbatim
  ******************************************************************************
  */

#include "ald_can.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @defgroup CAN CAN
  * @brief CAN module driver
  * @{
  */
#ifdef ALD_CAN

/** @addtogroup CAN_Private_Functions  CAN Private Functions
  * @{
  */
static void can_rx_fifo_release(can_handle_t *hperh, can_rx_fifo_t num);
static ald_status_t __can_send_by_it(can_handle_t *hperh, uint8_t err);
static ald_status_t __can_recv_by_it(can_handle_t *hperh, uint8_t num);
/**
  * @}
  */

/** @defgroup CAN_Public_Functions CAN Public Functions
  * @{
  */

/** @defgroup CAN_Public_Functions_Group1 Initialization  functions
  * @brief    Initialization and Configuration functions
  *
  * @verbatim
  ==============================================================================
              ##### Initialization and Configuration functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Initialize and configure the CAN.
      (+) Configures the CAN reception filter.
      (+) Reset the CAN.

    @endverbatim
  * @{
  */

/**
  * @brief  Initializes the CAN peripheral according to the specified
  *         parameters in the CAN_init_t.
  * @param  hperh: pointer to a can_handle_t structure that contains
  *         the configuration information for the specified CAN.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_init(can_handle_t *hperh)
{
    uint32_t tickstart = 0;

    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_FUNC_STATE(hperh->init.ttcm));
    assert_param(IS_FUNC_STATE(hperh->init.abom));
    assert_param(IS_FUNC_STATE(hperh->init.awk));
    assert_param(IS_FUNC_STATE(hperh->init.abom));
    assert_param(IS_FUNC_STATE(hperh->init.rfom));
    assert_param(IS_FUNC_STATE(hperh->init.txmp));
    assert_param(IS_CAN_MODE(hperh->init.mode));
    assert_param(IS_CAN_SJW(hperh->init.sjw));
    assert_param(IS_CAN_BS1(hperh->init.seg1));
    assert_param(IS_CAN_BS2(hperh->init.seg2));
    assert_param(IS_CAN_PRESCALER(hperh->init.psc));

    if (hperh->state == CAN_STATE_RESET)
        hperh->lock = UNLOCK;

    hperh->state = CAN_STATE_BUSY;
    tickstart    = ald_get_tick();

    CLEAR_BIT(hperh->perh->CON, CAN_CON_SLPREQ_MSK);
    SET_BIT(hperh->perh->CON, CAN_CON_INIREQ_MSK);

    while (!READ_BIT(hperh->perh->STAT, CAN_STAT_INISTAT_MSK))
    {
        if ((ald_get_tick() - tickstart) > CAN_TIMEOUT_VALUE)
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);

            return TIMEOUT;
        }
    }

    MODIFY_REG(hperh->perh->CON, CAN_CON_TTCEN_MSK, hperh->init.ttcm << CAN_CON_TTCEN_POS);
    MODIFY_REG(hperh->perh->CON, CAN_CON_ABOFFEN_MSK, hperh->init.abom << CAN_CON_ABOFFEN_POS);
    MODIFY_REG(hperh->perh->CON, CAN_CON_AWKEN_MSK, hperh->init.awk << CAN_CON_AWKEN_POS);
    MODIFY_REG(hperh->perh->CON, CAN_CON_ARTXDIS_MSK, hperh->init.artx << CAN_CON_ARTXDIS_POS);
    MODIFY_REG(hperh->perh->CON, CAN_CON_RXFOPM_MSK, hperh->init.rfom << CAN_CON_RXFOPM_POS);
    MODIFY_REG(hperh->perh->CON, CAN_CON_TXMP_MSK, hperh->init.txmp << CAN_CON_TXMP_POS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_LOOP_MSK, (hperh->init.mode & 0x1) << CAN_BTIME_LOOP_POS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_SILENT_MSK, ((hperh->init.mode >> 1) & 0x1) << CAN_BTIME_SILENT_POS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_RESJW_MSK, hperh->init.sjw << CAN_BTIME_RESJW_POSS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_SEG1_MSK, hperh->init.seg1 << CAN_BTIME_SEG1_POSS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_SEG2_MSK, hperh->init.seg2 << CAN_BTIME_SEG2_POSS);
    MODIFY_REG(hperh->perh->BTIME, CAN_BTIME_BPSC_MSK, (hperh->init.psc - 1) << CAN_BTIME_BPSC_POSS);

    CLEAR_BIT(hperh->perh->CON, CAN_CON_INIREQ_MSK);
    tickstart = ald_get_tick();

    while (READ_BIT(hperh->perh->STAT, CAN_STAT_INISTAT_MSK))
    {
        if ((ald_get_tick() - tickstart) > CAN_TIMEOUT_VALUE)
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);

            return TIMEOUT;
        }
    }

    hperh->err   = CAN_ERROR_NONE;
    hperh->state = CAN_STATE_READY;

    return OK;
}

/**
  * @brief  Configures the CAN reception filter according to the specified
  *         parameters in the can_filter_t.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  config: pointer to a can_filter_t structure that
  *         contains the filter configuration information.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_filter_config(can_handle_t *hperh, can_filter_t *config)
{
    uint32_t pos;

    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_FILTER_NUMBER(config->number));
    assert_param(IS_CAN_FILTER_MODE(config->mode));
    assert_param(IS_CAN_FILTER_SCALE(config->scale));
    assert_param(IS_CAN_FILTER_FIFO(config->fifo));
    assert_param(IS_FUNC_STATE(config->active));
    assert_param(IS_CAN_BANKNUMBER(config->bank_number));

    pos = 1 << config->number;

    SET_BIT(hperh->perh->FLTCON, CAN_FLTCON_FLTINI_MSK);
    CLEAR_BIT(hperh->perh->FLTGO, pos);

    if (config->scale == CAN_FILTER_SCALE_16)
    {
        CLEAR_BIT(hperh->perh->FLTWS, pos);
        hperh->perh->Filter[config->number].FLT1 =
            ((0xFFFF & config->mask_id_low) << 16) |
            (0xFFFF & config->id_low);

        hperh->perh->Filter[config->number].FLT2 =
            ((0xFFFF & config->mask_id_high) << 16) |
            (0xFFFF & config->id_high);
    }

    if (config->scale == CAN_FILTER_SCALE_32)
    {
        SET_BIT(hperh->perh->FLTWS, pos);
        hperh->perh->Filter[config->number].FLT1 =
            ((0xFFFF & config->id_high) << 16) |
            (0xFFFF & config->id_low);
        hperh->perh->Filter[config->number].FLT2 =
            ((0xFFFF & config->mask_id_high) << 16) |
            (0xFFFF & config->mask_id_low);
    }

    MODIFY_REG(hperh->perh->FLTM, pos, config->mode << config->number);
    MODIFY_REG(hperh->perh->FLTAS, pos, config->fifo << config->number);
    MODIFY_REG(hperh->perh->FLTGO, pos, config->active << config->number);
    CLEAR_BIT(hperh->perh->FLTCON, CAN_FLTCON_FLTINI_MSK);

    return OK;
}

/**
  * @brief  Reset the CAN peripheral.
  * @param  hperh: pointer to a can_handle_t structure.
  * @retval None
  */
void ald_can_reset(can_handle_t *hperh)
{
    assert_param(IS_CAN_ALL(hperh->perh));

    hperh->state = CAN_STATE_RESET;
    __UNLOCK(hperh);

    return;
}

/**
  * @}
  */

/** @defgroup CAN_Public_Functions_Group2 IO operation functions
 *  @brief    I/O operation functions
 *
 *  @verbatim
  ==============================================================================
                      ##### IO operation functions #####
  ==============================================================================
    [..]  This section provides functions allowing to:
      (+) Send a CAN frame message.
      (+) Send a CAN frame message using interrupt.
      (+) Receive a CAN frame message.
      (+) Receive a CAN frame message using interrupt.

  *@endverbatim
  * @{
  */

/**
  * @brief  Send a CAN frame message.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  msg: message which will be sent.
  * @param  timeout: specify Timeout value
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_send(can_handle_t *hperh, can_tx_msg_t *msg, uint32_t timeout)
{
    uint32_t tick;
    can_tx_mailbox_t idx;

    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_IDTYPE(msg->type));
    assert_param(IS_CAN_RTR(msg->rtr));
    assert_param(IS_CAN_DATA_LEN(msg->len));

    __LOCK(hperh);
    SET_BIT(hperh->state, CAN_STATE_TX_MASK);

    if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM0EF_MSK))
        idx = CAN_TX_MAILBOX_0;
    else if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM1EF_MSK))
        idx = CAN_TX_MAILBOX_1;
    else if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM2EF_MSK))
        idx = CAN_TX_MAILBOX_2;
    else
        idx = CAN_TX_MAILBOX_NONE;

    if (idx == CAN_TX_MAILBOX_NONE)
    {
        hperh->state = CAN_STATE_ERROR;
        __UNLOCK(hperh);
        return ERROR;
    }

    CLEAR_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_TXMREQ_MSK);
    MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_IDE_MSK, msg->type << CAN_TXID0_IDE_POS);
    MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_RTR_MSK, msg->rtr << CAN_TXID0_RTR_POS);

    if (msg->type == CAN_ID_STD)
    {
        assert_param(IS_CAN_STDID(msg->std));
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_STDID_MSK, msg->std << CAN_TXID0_STDID_POSS);
        CLEAR_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_EXID_MSK);
    }
    else
    {
        assert_param(IS_CAN_EXTID(msg->ext));
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_STDID_MSK, ((msg->ext >> 18) & 0x7FF) << CAN_TXID0_STDID_POSS);
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_EXID_MSK, (msg->ext & 0x3FFFF) << CAN_TXID0_EXID_POSS);
    }

    MODIFY_REG(hperh->perh->TxMailBox[idx].TXFCON, CAN_TXFCON0_DLEN_MSK, (msg->len & 0xF) << CAN_TXFCON0_DLEN_POSS);
    WRITE_REG(hperh->perh->TxMailBox[idx].TXDL, msg->data[0] | (msg->data[1] << 8) | (msg->data[2] << 16) | (msg->data[3] << 24));
    WRITE_REG(hperh->perh->TxMailBox[idx].TXDH, msg->data[4] | (msg->data[5] << 8) | (msg->data[6] << 16) | (msg->data[7] << 24));
    SET_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_TXMREQ_MSK);
    tick = ald_get_tick();

    while (!(ald_can_get_tx_status(hperh, idx)))
    {
        if ((timeout == 0) || ((ald_get_tick() - tick) > timeout))
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);
            return TIMEOUT;
        }
    }

    CLEAR_BIT(hperh->state, CAN_STATE_TX_MASK);
    __UNLOCK(hperh);
    return OK;
}

/**
  * @brief  Send a CAN frame message using interrupt.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  msg: message which will be sent.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_send_by_it(can_handle_t *hperh, can_tx_msg_t *msg)
{
    uint8_t idx = CAN_TX_MAILBOX_NONE;

    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_IDTYPE(msg->type));
    assert_param(IS_CAN_RTR(msg->rtr));
    assert_param(IS_CAN_DATA_LEN(msg->len));

    if ((hperh->state != CAN_STATE_READY) && (hperh->state != CAN_STATE_BUSY_RX))
        return BUSY;

    if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM0EF_MSK))
        idx = CAN_TX_MAILBOX_0;
    else if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM1EF_MSK))
        idx = CAN_TX_MAILBOX_1;
    else if (READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM2EF_MSK))
        idx = CAN_TX_MAILBOX_2;
    else
        idx = CAN_TX_MAILBOX_NONE;

    if (idx == CAN_TX_MAILBOX_NONE)
        return BUSY;

    CLEAR_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_TXMREQ_MSK);
    MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_IDE_MSK, msg->type << CAN_TXID0_IDE_POS);
    MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_RTR_MSK, msg->rtr << CAN_TXID0_RTR_POS);

    if (msg->type == CAN_ID_STD)
    {
        assert_param(IS_CAN_STDID(msg->std));
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_STDID_MSK, msg->std << CAN_TXID0_STDID_POSS);
        CLEAR_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_EXID_MSK);
    }
    else
    {
        assert_param(IS_CAN_EXTID(msg->ext));
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_STDID_MSK, ((msg->ext >> 18) & 0x7FF) << CAN_TXID0_STDID_POSS);
        MODIFY_REG(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_EXID_MSK, (msg->ext & 0x3FFFF) << CAN_TXID0_EXID_POSS);
    }

    MODIFY_REG(hperh->perh->TxMailBox[idx].TXFCON, CAN_TXFCON0_DLEN_MSK, (msg->len & 0xF) << CAN_TXFCON0_DLEN_POSS);
    WRITE_REG(hperh->perh->TxMailBox[idx].TXDL, msg->data[0] | (msg->data[1] << 8) | (msg->data[2] << 16) | (msg->data[3] << 24));
    WRITE_REG(hperh->perh->TxMailBox[idx].TXDH, msg->data[4] | (msg->data[5] << 8) | (msg->data[6] << 16) | (msg->data[7] << 24));

    SET_BIT(hperh->state, CAN_STATE_TX_MASK);

    ald_can_interrupt_config(hperh, CAN_IT_WARN, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_PERR, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_BOF, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_PRERR, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_ERR, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_TXM, ENABLE);

    SET_BIT(hperh->perh->TxMailBox[idx].TXID, CAN_TXID0_TXMREQ_MSK);
    return OK;
}

/**
  * @brief  Receives a correct CAN frame.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  num: Receive fifo number, CAN_RX_FIFO0 or CAN_RX_FIFO1
  * @param  msg: Storing message.
  * @param  timeout: Specify timeout value
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_recv(can_handle_t *hperh, can_rx_fifo_t num, can_rx_msg_t *msg, uint32_t timeout)
{
    uint32_t tick, stid, exid;

    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_FIFO(num));

    __LOCK(hperh);
    SET_BIT(hperh->state, CAN_STATE_RX_MASK);
    tick = ald_get_tick();

    while (CAN_RX_MSG_PENDING(hperh, num) == 0)
    {
        if ((timeout == 0) || ((ald_get_tick() - tick) > timeout))
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);
            return TIMEOUT;
        }
    }

    stid = READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_STDID_MSK, CAN_RXF0ID_STDID_POSS);
    exid = READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_EXID_MSK, CAN_RXF0ID_EXID_POSS);
    msg->type = (can_id_type_t)READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_IDE_MSK, CAN_RXF0ID_IDE_POS);

    if (msg->type == CAN_ID_STD)
        msg->std = stid;
    else
        msg->ext = (stid << 18) | exid;

    msg->rtr     = (can_remote_req_t)READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_RTR_MSK, CAN_RXF0ID_RTR_POS);
    msg->len     = READ_BITS(hperh->perh->RxFIFO[num].RXFINF, CAN_RXF0INF_DLEN_MSK, CAN_RXF0INF_DLEN_POSS);
    msg->fmi     = READ_BITS(hperh->perh->RxFIFO[num].RXFINF, CAN_RXF0INF_FLTIDX_MSK, CAN_RXF0INF_FLTIDX_POSS);
    msg->data[0] = hperh->perh->RxFIFO[num].RXFDL & 0xFF;
    msg->data[1] = (hperh->perh->RxFIFO[num].RXFDL >> 8) & 0xFF;
    msg->data[2] = (hperh->perh->RxFIFO[num].RXFDL >> 16) & 0xFF;
    msg->data[3] = (hperh->perh->RxFIFO[num].RXFDL >> 24) & 0xFF;
    msg->data[4] = hperh->perh->RxFIFO[num].RXFDH & 0xFF;
    msg->data[5] = (hperh->perh->RxFIFO[num].RXFDH >> 8) & 0xFF;
    msg->data[6] = (hperh->perh->RxFIFO[num].RXFDH >> 16) & 0xFF;
    msg->data[7] = (hperh->perh->RxFIFO[num].RXFDH >> 24) & 0xFF;

    can_rx_fifo_release(hperh, num);
    CLEAR_BIT(hperh->state, CAN_STATE_RX_MASK);
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Receives a correct CAN frame using interrupt.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  num: Specify the FIFO number
  * @param  msg: Storing message.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_recv_by_it(can_handle_t *hperh, can_rx_fifo_t num, can_rx_msg_t *msg)
{
    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_FIFO(num));

    if ((hperh->state != CAN_STATE_READY) && (hperh->state != CAN_STATE_BUSY_TX))
        return BUSY;

    SET_BIT(hperh->state, CAN_STATE_RX_MASK);
    hperh->rx_msg = msg;

    ald_can_interrupt_config(hperh, CAN_IT_WARN, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_PERR, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_BOF, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_PRERR, ENABLE);
    ald_can_interrupt_config(hperh, CAN_IT_ERR, ENABLE);

    if (num == CAN_RX_FIFO0)
        ald_can_interrupt_config(hperh, CAN_IT_FP0, ENABLE);
    else
        ald_can_interrupt_config(hperh, CAN_IT_FP1, ENABLE);

    return OK;
}
/**
  * @}
  */

/** @defgroup CAN_Public_Functions_Group3 Peripheral Control functions
  * @brief    Peripheral Control functions
  *
  * @verbatim
  ==============================================================================
            ##### Peripheral Control functions #####
  ==============================================================================
    [..]
    This section provides functions allowing to:
      (+) Configure CAN sleep.
      (+) Configure CAN wakeup.
      (+) CAN cancel send message.
      (+) Handle CAN interrupt.
      (+) Get CAN transmit status.
      (+) Configure CAN interrupt ENABLE/DISABLE.
      (+) Get CAN interrupt source status.
      (+) Get CAN interrupt flag status.
      (+) Clear CAN interrupt flag.

  * @endverbatim
  * @{
  */

/**
  * @brief  Enters the Sleep(low power) mode.
  * @param  hperh: pointer to a can_handle_t.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_sleep(can_handle_t *hperh)
{
    uint32_t tick;

    assert_param(IS_CAN_ALL(hperh->perh));

    __LOCK(hperh);
    hperh->state = CAN_STATE_BUSY;

    CLEAR_BIT(hperh->perh->CON, CAN_CON_INIREQ_MSK);
    SET_BIT(hperh->perh->CON, CAN_CON_SLPREQ_MSK);
    tick = ald_get_tick();

    while ((!(READ_BIT(hperh->perh->STAT, CAN_STAT_SLPSTAT_MSK))) || READ_BIT(hperh->perh->STAT, CAN_STAT_INISTAT_MSK))
    {
        if ((ald_get_tick() - tick) > CAN_TIMEOUT_VALUE)
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);
            return TIMEOUT;
        }
    }

    hperh->state = CAN_STATE_READY;
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Wakes up the CAN peripheral from sleep mode, after that the CAN peripheral
  *         is in the normal mode.
  * @param  hperh: pointer to a can_handle_t structure.
  * @retval Status, see ald_status_t.
  */
ald_status_t ald_can_wake_up(can_handle_t *hperh)
{
    uint32_t tick;

    assert_param(IS_CAN_ALL(hperh->perh));

    __LOCK(hperh);
    hperh->state = CAN_STATE_BUSY;

    CLEAR_BIT(hperh->perh->CON, CAN_CON_SLPREQ_MSK);
    tick = ald_get_tick();

    while (READ_BIT(hperh->perh->STAT, CAN_STAT_SLPSTAT_MSK))
    {
        if ((ald_get_tick() - tick) > CAN_TIMEOUT_VALUE)
        {
            hperh->state = CAN_STATE_TIMEOUT;
            __UNLOCK(hperh);
            return TIMEOUT;
        }
    }

    hperh->state = CAN_STATE_READY;
    __UNLOCK(hperh);

    return OK;
}

/**
  * @brief  Handles CAN interrupt request
  * @param  hperh: pointer to a can_handle_t structure.
  * @retval None
  */
void ald_can_irq_handler(can_handle_t *hperh)
{
    if (ald_can_get_it_status(hperh, CAN_IT_TXM))
    {
        if ((ald_can_get_tx_status(hperh, CAN_TX_MAILBOX_0))
                || (ald_can_get_tx_status(hperh, CAN_TX_MAILBOX_1))
                || (ald_can_get_tx_status(hperh, CAN_TX_MAILBOX_2)))
            __can_send_by_it(hperh, 0);

        if (hperh->perh->TXSTAT & CAN_TXSTAT_M0TXERR_MSK)
        {
            SET_BIT(hperh->perh->TXSTATC, CAN_TXSTATC_M0REQC_MSK);
            __can_send_by_it(hperh, 1);
        }

        if (hperh->perh->TXSTAT & CAN_TXSTAT_M1TXERR_MSK)
        {
            SET_BIT(hperh->perh->TXSTATC, CAN_TXSTATC_M1REQC_MSK);
            __can_send_by_it(hperh, 1);
        }

        if (hperh->perh->TXSTAT & CAN_TXSTAT_M2TXERR_MSK)
        {
            SET_BIT(hperh->perh->TXSTATC, CAN_TXSTATC_M2REQC_MSK);
            __can_send_by_it(hperh, 1);
        }
    }

    if ((ald_can_get_it_status(hperh, CAN_IT_FP0))
            && (CAN_RX_MSG_PENDING(hperh, CAN_RX_FIFO0) != 0))
        __can_recv_by_it(hperh, CAN_RX_FIFO0);

    if ((ald_can_get_it_status(hperh, CAN_IT_FP1))
            && (CAN_RX_MSG_PENDING(hperh, CAN_RX_FIFO1) != 0))
        __can_recv_by_it(hperh, CAN_RX_FIFO1);

    if ((ald_can_get_flag_status(hperh, CAN_FLAG_WARN))
            && (ald_can_get_it_status(hperh, CAN_IT_WARN))
            && (ald_can_get_it_status(hperh, CAN_IT_ERR)))
        hperh->err |= CAN_ERROR_EWG;

    if ((ald_can_get_flag_status(hperh, CAN_FLAG_PERR))
            && (ald_can_get_it_status(hperh, CAN_IT_PERR))
            && (ald_can_get_it_status(hperh, CAN_IT_ERR)))
        hperh->err |= CAN_ERROR_EPV;

    if ((ald_can_get_flag_status(hperh, CAN_FLAG_BOF))
            && (ald_can_get_it_status(hperh, CAN_IT_BOF))
            && (ald_can_get_it_status(hperh, CAN_IT_ERR)))
        hperh->err |= CAN_ERROR_BOF;

    if (READ_BIT(hperh->perh->ERRSTAT, CAN_ERRSTAT_PRERRF_MSK)
            && (ald_can_get_it_status(hperh, CAN_IT_PRERR))
            && (ald_can_get_it_status(hperh, CAN_IT_ERR)))
    {

        switch (READ_BITS(hperh->perh->ERRSTAT, CAN_ERRSTAT_PRERRF_MSK, CAN_ERRSTAT_PRERRF_POSS))
        {
            case (1):
                hperh->err |= CAN_ERROR_STF;
                break;

            case (2):
                hperh->err |= CAN_ERROR_FOR;
                break;

            case (3):
                hperh->err |= CAN_ERROR_ACK;
                break;

            case (4):
                hperh->err |= CAN_ERROR_BR;
                break;

            case (5):
                hperh->err |= CAN_ERROR_BD;
                break;

            case (6):
                hperh->err |= CAN_ERROR_CRC;
                break;

            default:
                break;
        }

        CLEAR_BIT(hperh->perh->ERRSTAT, CAN_ERRSTAT_PRERRF_MSK);

        if (READ_BIT(hperh->perh->IE, CAN_IE_TXMEIE_MSK))
            ald_can_interrupt_config(hperh, CAN_IT_TXM, DISABLE);

        if (READ_BIT(hperh->perh->IE, CAN_IE_F0PIE_MSK))
            ald_can_interrupt_config(hperh, CAN_IT_FP0, DISABLE);

        if (READ_BIT(hperh->perh->IE, CAN_IE_F1PIE_MSK))
            ald_can_interrupt_config(hperh, CAN_IT_FP1, DISABLE);
    }

    if ((ald_can_get_flag_status(hperh, CAN_FLAG_ERR)) && (hperh->err == CAN_ERROR_NONE))
        hperh->err = CAN_ERROR_UNK;

    if (hperh->err != CAN_ERROR_NONE)
    {
        SET_BIT(hperh->perh->IFC, CAN_IFC_ERRIFC_MSK);
        hperh->state = CAN_STATE_READY;

        if (hperh->error_cbk != NULL)
            hperh->error_cbk(hperh);
    }
}

/**
  * @brief  Check the transmission status of a CAN Frame.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  box: the index of the mailbox that is used for transmission.
  * @retval The new status of transmission(TRUE or FALSE).
  */
type_bool_t ald_can_get_tx_status(can_handle_t *hperh, can_tx_mailbox_t box)
{
    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_TX_MAILBOX(box));

    switch (box)
    {
        case CAN_TX_MAILBOX_0:
            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M0REQC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M0TXC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM0EF_MSK))
                return FALSE;

            return TRUE;

        case CAN_TX_MAILBOX_1:
            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M1REQC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M1TXC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM1EF_MSK))
                return FALSE;

            return TRUE;

        case CAN_TX_MAILBOX_2:
            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M2REQC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M2TXC_MSK))
                return FALSE;

            if (!READ_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_TXM2EF_MSK))
                return FALSE;

            return TRUE;

        default:
            break;
    }

    return FALSE;
}

/**
  * @brief  Cancel transmission.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  box: the index of the mailbox that is used for transmission.
  * @retval None
  */
void ald_can_cancel_send(can_handle_t *hperh, can_tx_mailbox_t box)
{
    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_TX_MAILBOX(box));

    switch (box)
    {
        case CAN_TX_MAILBOX_0:
            SET_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M0STPREQ_MSK);
            break;

        case CAN_TX_MAILBOX_1:
            SET_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M1STPREQ_MSK);
            break;

        case CAN_TX_MAILBOX_2:
            SET_BIT(hperh->perh->TXSTAT, CAN_TXSTAT_M2STPREQ_MSK);
            break;

        default:
            break;
    }

    return;
}

/**
  * @brief  Enable/disable the specified CAN interrupts.
  * @param  hperh: Pointer to a can_handle_t structure.
  * @param  it: Specifies the CAN interrupt sources to be enabled or disabled.
  *         This parameter can be one of the @ref can_it_t.
  * @param  state: New state of the specified CAN interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_can_interrupt_config(can_handle_t *hperh, can_it_t it, type_func_t state)
{
    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_IT(it));
    assert_param(IS_FUNC_STATE(state));

    if (state == ENABLE)
        SET_BIT(hperh->perh->IE, it);
    else
        CLEAR_BIT(hperh->perh->IE, it);

    return;
}

/**
  * @brief  Get the status of CAN interrupt source.
  * @param  hperh: Pointer to a can_handle_t structure.
  * @param  it: Specifies the CAN interrupt source.
  *         This parameter can be one of the @ref can_it_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_can_get_it_status(can_handle_t *hperh, can_it_t it)
{
    assert_param(IS_CAN_ALL(hperh->perh));
    assert_param(IS_CAN_IT(it));

    if (READ_BIT(hperh->perh->IE, it))
        return SET;

    return RESET;
}

/**
  * @brief  Get the status of CAN interrupt flag.
  * @param  hperh: Pointer to a can_handle_t structure.
  * @param  flag: Specifies the CAN interrupt flag.
  *         This parameter can be one of the @ref can_flag_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_can_get_flag_status(can_handle_t *hperh, can_flag_t flag)
{
    uint32_t idx   = (flag >> 20) & 0x7;
    uint32_t _flag = flag & 0xFF8FFFFF;

    assert_param(IS_CAN_GET_FLAG(flag));

    switch (idx)
    {
        case 0:
            if (READ_BIT(hperh->perh->STAT, _flag))
                return SET;

            break;

        case 1:
            if (READ_BIT(hperh->perh->TXSTAT, _flag))
                return SET;

            break;

        case 2:
            if (READ_BIT(hperh->perh->RXF0, _flag))
                return SET;

            break;

        case 3:
            if (READ_BIT(hperh->perh->RXF1, _flag))
                return SET;

            break;

        case 4:
            if (READ_BIT(hperh->perh->ERRSTAT, _flag))
                return SET;

            break;

        default:
            break;
    }

    return RESET;
}

/** @brief  Clear the specified CAN pending flag.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  flag: specifies the flag to check.
  * @retval None.
  */
void ald_can_clear_flag_status(can_handle_t *hperh, can_flag_t flag)
{
    uint32_t idx   = (flag >> 20) & 0x7;
    uint32_t _flag = flag & 0xFF8FFFFF;

    assert_param(IS_CAN_CLEAR_FLAG(flag));

    switch (idx)
    {
        case 0:
            WRITE_REG(hperh->perh->IFC, _flag);
            break;

        case 1:
            WRITE_REG(hperh->perh->TXSTATC, _flag);
            break;

        case 2:
            WRITE_REG(hperh->perh->RXF0C, _flag);
            break;

        case 3:
            WRITE_REG(hperh->perh->RXF1C, _flag);
            break;

        default:
            break;
    }

    return;
}
/**
  * @}
  */

/** @defgroup CAN_Public_Functions_Group4 Peripheral State and Error functions
  * @brief    CAN Peripheral State functions
  *
  * @verbatim
  ==============================================================================
            ##### Peripheral State and Error functions #####
  ==============================================================================
    [..]
    This subsection provides functions allowing to:
      (+) Check the CAN state.
      (+) Check CAN Errors detected during interrupt process

  * @endverbatim
  * @{
  */
/**
  * @brief  return the CAN state
  * @param  hperh: pointer to a can_handle_t structure.
  * @retval Status, see can_state_t.
  */
can_state_t ald_can_get_state(can_handle_t *hperh)
{
    return hperh->state;
}

/**
  * @brief  Return the CAN error code
  * @param  hperh: pointer to a can_handle_t structure.
  * @retval CAN Error Code
  */
can_error_t ald_can_get_error(can_handle_t *hperh)
{
    return hperh->err;
}

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CAN_Private_Functions CAN Private Functions
  * @{
  */

/**
  * @brief  Release rx FIFO
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  num: Receive fifo number, CAN_RX_FIFO0 or CAN_RX_FIFO1
  * @retval None
  */
static void can_rx_fifo_release(can_handle_t *hperh, can_rx_fifo_t num)
{
    if (num == CAN_RX_FIFO0)
        SET_BIT(hperh->perh->RXF0, CAN_RXF0_FREE_MSK);
    else
        SET_BIT(hperh->perh->RXF1, CAN_RXF1_FREE_MSK);
}


/**
  * @brief  transmits a CAN frame message using interrupt.
  * @param  hperh: pointer to a can_handle_t structure.
  * @param  err: Error code, 0 - success, 1 - error.
  * @retval Status, see ald_status_t.
  */
static ald_status_t __can_send_by_it(can_handle_t *hperh, uint8_t err)
{
    ald_can_interrupt_config(hperh, CAN_IT_TXM, DISABLE);

    if (hperh->state == CAN_STATE_BUSY_TX)
    {
        ald_can_interrupt_config(hperh, CAN_IT_WARN, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_PERR, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_BOF, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_PRERR, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_ERR, DISABLE);
    }

    CLEAR_BIT(hperh->state, CAN_STATE_TX_MASK);

    if ((err == 0) && (hperh->tx_cplt_cbk))
        hperh->tx_cplt_cbk(hperh);

    if ((err) && (hperh->error_cbk != NULL))
    {
        hperh->err = CAN_ERROR_UNK;
        hperh->error_cbk(hperh);
    }

    return OK;
}

/**
  * @brief  Receives a correct CAN frame using interrupt.
  * @param  hperh:  Pointer to a can_handle_t structure.
  * @param  num: Specify the FIFO number
  * @retval Status, see ald_status_t.
  */
static ald_status_t __can_recv_by_it(can_handle_t *hperh, uint8_t num)
{
    uint32_t stid, exid;

    stid = READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_STDID_MSK, CAN_RXF0ID_STDID_POSS);
    exid = READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_EXID_MSK, CAN_RXF0ID_EXID_POSS);
    hperh->rx_msg->type = (can_id_type_t)READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_IDE_MSK, CAN_RXF0ID_IDE_POS);

    if (hperh->rx_msg->type == CAN_ID_STD)
        hperh->rx_msg->std = stid;
    else
        hperh->rx_msg->ext = (stid << 18) | exid;

    hperh->rx_msg->rtr     = (can_remote_req_t)READ_BITS(hperh->perh->RxFIFO[num].RXFID, CAN_RXF0ID_RTR_MSK, CAN_RXF0ID_RTR_POS);
    hperh->rx_msg->len     = READ_BITS(hperh->perh->RxFIFO[num].RXFINF, CAN_RXF0INF_DLEN_MSK, CAN_RXF0INF_DLEN_POSS);
    hperh->rx_msg->fmi     = READ_BITS(hperh->perh->RxFIFO[num].RXFINF, CAN_RXF0INF_FLTIDX_MSK, CAN_RXF0INF_FLTIDX_POSS);
    hperh->rx_msg->data[0] = hperh->perh->RxFIFO[num].RXFDL & 0xFF;
    hperh->rx_msg->data[1] = (hperh->perh->RxFIFO[num].RXFDL >> 8) & 0xFF;
    hperh->rx_msg->data[2] = (hperh->perh->RxFIFO[num].RXFDL >> 16) & 0xFF;
    hperh->rx_msg->data[3] = (hperh->perh->RxFIFO[num].RXFDL >> 24) & 0xFF;
    hperh->rx_msg->data[4] = hperh->perh->RxFIFO[num].RXFDH & 0xFF;
    hperh->rx_msg->data[5] = (hperh->perh->RxFIFO[num].RXFDH >> 8) & 0xFF;
    hperh->rx_msg->data[6] = (hperh->perh->RxFIFO[num].RXFDH >> 16) & 0xFF;
    hperh->rx_msg->data[7] = (hperh->perh->RxFIFO[num].RXFDH >> 24) & 0xFF;

    if (num == CAN_RX_FIFO0)
    {
        can_rx_fifo_release(hperh, CAN_RX_FIFO0);
        ald_can_interrupt_config(hperh, CAN_IT_FP0, DISABLE);
    }
    else
    {
        can_rx_fifo_release(hperh, CAN_RX_FIFO1);
        ald_can_interrupt_config(hperh, CAN_IT_FP1, DISABLE);
    }

    if (hperh->state == CAN_STATE_BUSY_RX)
    {
        ald_can_interrupt_config(hperh, CAN_IT_WARN, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_PERR, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_BOF, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_PRERR, DISABLE);
        ald_can_interrupt_config(hperh, CAN_IT_ERR, DISABLE);
    }

    CLEAR_BIT(hperh->state, CAN_STATE_RX_MASK);

    if (hperh->rx_cplt_cbk)
        hperh->rx_cplt_cbk(hperh);

    return OK;
}
/**
 * @}
 */

#endif /* ALD_CAN */

/**
  * @}
  */

/**
  * @}
  */
