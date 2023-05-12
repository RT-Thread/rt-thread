/**
  *********************************************************************************
  *
  * @file    ald_i2c.c
  * @brief   I2C module driver.
  *
  * @version V1.0
  * @date    24 Feb. 2023
  * @author  AE Team
  * @note
  *          Change Logs:
  *          Date            Author          Notes
  *          24 Feb. 2023    Lisq            The first version
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
  *
  @verbatim
 ===============================================================================
                       ##### How to use this driver #####
 ===============================================================================
 [..]
   The I2C driver can be used as follows:

   (#) Declare a i2c_handle_t handle structure, for example:
       i2c_handle_t  hperh;

   (#) Configure the Communication Speed, Addressing mode, Own Address1,
       Dual Addressing mode, Own Address2, General call and Nostretch mode in the hperh init structure.

   (#) Initialize the I2C registers by calling the ald_i2c_init().

   (#) For I2C IO and IO MEM operations, three operation modes are available within this driver :

   *** Polling mode IO operation ***
   =================================
   [..]
     (+) Transmit in master mode an amount of data in blocking mode using ald_i2c_master_send()
     (+) Receive in master mode an amount of data in blocking mode using ald_i2c_master_recv()
     (+) Transmit in slave mode an amount of data in blocking mode using ald_i2c_slave_send()
     (+) Receive in slave mode an amount of data in blocking mode using ald_i2c_slave_recv()

   *** Polling mode IO MEM operation ***
   =====================================
   [..]
     (+) Write an amount of data in blocking mode to a specific memory address using ald_i2c_mem_write()
     (+) Read an amount of data in blocking mode from a specific memory address using ald_i2c_mem_read()


   *** Interrupt mode IO operation ***
   ===================================
   [..]
     (+) The I2C interrupts should have the highest priority in the application in order
         to make them uninterruptible.
     (+) Transmit in master mode an amount of data in non-blocking mode using ald_i2c_master_send_by_it()
     (+) At transmission end of transfer, hperh->master_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_tx_cplt_cbk()
     (+) Receive in master mode an amount of data in non-blocking mode using ald_i2c_master_recv_by_it()
     (+) At reception end of transfer, hperh->master_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_rx_cplt_cbk()
     (+) Transmit in slave mode an amount of data in non-blocking mode using ald_i2c_slave_send_by_it()
     (+) At transmission end of transfer, hperh->slave_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_tx_cplt_cbk()
     (+) Receive in slave mode an amount of data in non-blocking mode using ald_i2c_slave_recv_by_it()
     (+) At reception end of transfer, hperh->slave_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** Interrupt mode IO MEM operation ***
   =======================================
   [..]
     (+) The I2C interrupts should have the highest priority in the application in order
         to make them uninterruptible.
     (+) Write an amount of data in non-blocking mode with Interrupt to a specific memory address using
         ald_i2c_mem_write_by_it()
     (+) At Memory end of write transfer, hperh->mem_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_tx_cplt_cbk()
     (+) Read an amount of data in non-blocking mode with Interrupt from a specific memory address using
         ald_i2c_mem_read_by_it()
     (+) At Memory end of read transfer, hperh->mem_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** DMA mode IO operation ***
   ==============================
   [..]
     (+) Transmit in master mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_master_send_by_dma()
     (+) At transmission end of transfer, hperh->master_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_tx_cplt_cbk()
     (+) Receive in master mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_master_recv_by_dma()
     (+) At reception end of transfer, hperh->master_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->master_rx_cplt_cbk()
     (+) Transmit in slave mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_slave_send_by_dma()
     (+) At transmission end of transfer, hperh->slave_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_tx_cplt_cbk()
     (+) Receive in slave mode an amount of data in non-blocking mode (DMA) using
         ald_i2c_slave_recv_by_dma()
     (+) At reception end of transfer, hperh->slave_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->slave_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()

   *** DMA mode IO MEM operation ***
   =================================
   [..]
     (+) Write an amount of data in non-blocking mode with DMA to a specific memory address using
         ald_i2c_mem_write_by_dma()
     (+) At Memory end of write transfer, hperh->mem_tx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_tx_cplt_cbk()
     (+) Read an amount of data in non-blocking mode with DMA from a specific memory address using
         ald_i2c_mem_read_by_dma()
     (+) At Memory end of read transfer, hperh->mem_rx_cplt_cbk() is executed and user can
          add his own code by customization of function pointer hperh->mem_rx_cplt_cbk()
     (+) In case of transfer Error, hperh->error_callback() function is executed and user can
          add his own code by customization of function pointer hperh->error_callback()


    *** I2C ald_status_t driver macros list ***
    ==================================
    [..]
      Below the list of most used macros in I2C ald_status_t driver.

     (+) __I2C_ENABLE: Enable the I2C peripheral
     (+) __I2C_DISABLE: Disable the I2C peripheral
     (+) I2C_GET_FLAG: Check whether the specified I2C flag is set or not
     (+) I2C_ENABLE_IT: Enable the specified I2C interrupt
     (+) I2C_DISABLE_IT: Disable the specified I2C interrupt
      (@) You can refer to the I2C ald_status_t driver header file for more useful macros

    *** I2C Workarounds linked to Silicon Limitation ***
    ====================================================
    [..]
      Below the list of all silicon limitations implemented for library on our product.
      (@) See ErrataSheet to know full silicon limitation list of your product.

      (#) Workarounds Implemented inside I2C library
         (##) Wrong data read into data register (Polling and Interrupt mode)
         (##) Start cannot be generated after a misplaced Stop
         (##) Some software events must be managed before the current byte is being transferred:
              Workaround: Use DMA in general, except when the Master is receiving a single byte.
              For Interupt mode, I2C should have the highest priority in the application.
         (##) Mismatch on the "Setup time for a repeated Start condition" timing parameter:
              Workaround: Reduce the frequency down to 88 kHz or use the I2C Fast-mode if
              supported by the slave.
         (##) Data valid time (tVD;DAT) violated without the OVR flag being set:
              Workaround: If the slave device allows it, use the clock stretching mechanism
              by programming no_stretch = I2C_NOSTRETCH_DISABLE in ald_i2c_init.

 @endverbatim
 *********************************************************************************
 */

#include "ald_i2c.h"

/** @addtogroup ES32VF2264_ALD
 * @{
 */

/** @defgroup I2C I2C
 * @brief I2C module driver
 * @{
 */

/** @addtogroup I2C_Private_Constants I2C Private Constants
 * @{
 */

#define I2C_TIMEOUT_FLAG          (10)
#define I2C_TIMEOUT_ADDR_SLAVE    (10)
#define I2C_TIMEOUT_BUSY_FLAG     (10)
#define I2C_MAX_DELAY             0xFFFFFFFF

/**
 * @}
 */

/** @addtogroup I2C_Private_Functions I2C Private Functions
 * @{
 */

static void i2c_dma_master_send_cplt(void *argv);
static void i2c_dma_master_recv_cplt(void *argv);
static void i2c_dma_slave_send_cplt(void *argv);
static void i2c_dma_slave_recv_cplt(void *argv);
static void i2c_dma_mem_send_cplt(void *argv);
static void i2c_dma_mem_recv_cplt(void *argv);
static ald_status_t i2c_req_mem_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                     uint16_t add_size, uint32_t timeout);

static ald_status_t i2c_master_req_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_master_req_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout);
static ald_status_t i2c_req_mem_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                                      uint16_t add_size, uint32_t timeout);
static ald_status_t i2c_wait_flag_change_to_timeout(ald_i2c_handle_t *hperh, uint32_t flag,
                                                flag_status_t status, uint32_t timeout);
static ald_status_t i2c_wait_master_addr_to_timeout(ald_i2c_handle_t *hperh, uint32_t flag, uint32_t timeout);
static ald_status_t i2c_wait_txe_to_timeout(ald_i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_wait_rxne_to_timeout(ald_i2c_handle_t *hperh, uint32_t timeout);
static ald_status_t i2c_master_send_tc(ald_i2c_handle_t *hperh);
static ald_status_t i2c_master_send_txe(ald_i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_tc(ald_i2c_handle_t *hperh);
static ald_status_t i2c_master_recv_rxne(ald_i2c_handle_t *hperh);
static ald_status_t i2c_slave_send_txe(ald_i2c_handle_t *hperh);
static ald_status_t i2c_slave_recv_rxne(ald_i2c_handle_t *hperh);
static ald_status_t i2c_slave_stopf(ald_i2c_handle_t *hperh);

/**
 * @}
 */

/** @defgroup I2C_Public_Functions I2C Public functions
 * @{
 */

/** @defgroup I2C_Public_Functions_Group1 Initialization and de-initialization functions
 * @brief     Initialization and Configuration functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialiaze the I2Cx peripheral:

      (+) Call the function ald_i2c_init() to configure the selected device with
          the selected configuration:
        (++) Communication Speed
        (++) Addressing mode
        (++) Own Address 1
        (++) Dual Addressing mode
        (++) Own Address 2
        (++) General call mode
        (++) Nostretch mode

      (+) Call the function ald_i2c_reset() to restore the default configuration
          of the selected I2Cx periperal.

@endverbatim
 * @{
 */

/**
 * @brief  I2C Configuration Speed function.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains.
 *                the configuration information for the I2C speed.
 * @param  clk: I2C Peripheral bus clock
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t i2c_speed_init(ald_i2c_handle_t *hperh, uint32_t clk)
{
    int32_t t_scl, t_pre, tmp;
    uint8_t scll, sclh, sdadel, scldel;

    if (clk > 72000000)
        return ALD_ERROR;
    if (hperh->init.module == ALD_I2C_MODULE_SLAVE) {
        hperh->init.clk_speed = 400000UL;
    }

    if (hperh->init.clk_speed <= 100000UL) {
        tmp = clk / 4000000UL;
        tmp = tmp >= 16UL ? 16UL : tmp;
        clk = clk / tmp;
    }
    else if (hperh->init.clk_speed <= 500000UL) {
        if (clk < 8000000UL)
            return ALD_ERROR;

        tmp = clk / 8000000UL;
        clk = clk / tmp;
    }
    else {
        if (clk < 12000000UL)
            return ALD_ERROR;

        tmp = clk / 12000000UL;
        clk = clk / tmp;
    }

    MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_PRESC_MSK, (tmp - 1) << I2C_TIMINGR_PRESC_POSS);

    t_scl = 1000000000UL / hperh->init.clk_speed;
    t_pre = 1000000000UL / clk;

    tmp = (t_scl << 4UL) / (t_pre << 1UL);
    tmp = ((tmp + 8UL) >> 4UL);
    tmp = tmp >= 255UL ? 255UL : tmp;
    scll = tmp;

    if (scll < 4)
        return ALD_ERROR;

    MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLL_MSK, (scll - 1) << I2C_TIMINGR_SCLL_POSS);
    scldel = ((scll << 1) / 3);
    scldel = scldel > 16 ? 16 : scldel;
    sdadel = (scll / 3) < (scll - scldel - 1) ? (scll / 3) : (scll - scldel - 1);
    sdadel = sdadel > 3 ? 3 : sdadel;
    MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLDEL_MSK, (scldel - 1) << I2C_TIMINGR_SCLDEL_POSS);
    MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SDADEL_MSK, sdadel << I2C_TIMINGR_SDADEL_POSS);

    if (scll > 6)
        sclh = scll - 3;
    else if (scll > 4)
        sclh = 3;
    else
        sclh = 2;

    MODIFY_REG(hperh->perh->TIMINGR, I2C_TIMINGR_SCLH_MSK, (sclh - 1UL) << I2C_TIMINGR_SCLH_POSS);
    return ALD_OK;
}
/**
 * @brief  Initializes the I2C according to the specified parameters
 *         in the i2c_init_t and initialize the associated handle.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_init(ald_i2c_handle_t *hperh)
{
    uint32_t freqrange = ald_cmu_get_pclk_clock();

    if (hperh == NULL)
        return ALD_ERROR;

    /* Check the parameters */
    assert_param(IS_I2C_CLOCK_SPEED(hperh->init.clk_speed));
    assert_param(IS_I2C_ADDRESSING_MODE(hperh->init.addr_mode));
    assert_param(IS_I2C_GENERAL_CALL(hperh->init.general_call));
    assert_param(IS_I2C_NO_STRETCH(hperh->init.no_stretch));
    assert_param(IS_I2C_MODULE(hperh->init.module));

    if (hperh->state == ALD_I2C_STATE_RESET)
        hperh->lock = UNLOCK;

    hperh->state = ALD_I2C_STATE_BUSY;

    ALD_I2C_DISABLE(hperh);

    if (ALD_OK != i2c_speed_init(hperh, freqrange))
        return ALD_ERROR;

    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NOSTRETCH_MSK, (hperh->init.no_stretch) << I2C_CON1_NOSTRETCH_POS);
    MODIFY_REG(hperh->perh->CON1, I2C_CON1_GCEN_MSK, (hperh->init.general_call) << I2C_CON1_GCEN_POS);

    if (hperh->init.dual_addr == ALD_I2C_DUALADDR_ENABLE) {
        CLEAR_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
        MODIFY_REG(hperh->perh->ADDR1, I2C_ADDR1_OA1_MSK, (hperh->init.own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
        SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);

        CLEAR_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
        MODIFY_REG(hperh->perh->ADDR2, I2C_ADDR2_OA2_MSK, (hperh->init.own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
        SET_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
    } else {
        if (hperh->init.addr_mode == ALD_I2C_ADDR_10BIT) {
            CLEAR_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
            SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1MODE_MSK);
            MODIFY_REG(hperh->perh->ADDR1, I2C_ADDR1_OA1_MSK, (hperh->init.own_addr1 & 0x3FF) << I2C_ADDR1_OA1_POSS);
            SET_BIT(hperh->perh->ADDR1, I2C_ADDR1_OA1EN_MSK);
        }
        else {
            CLEAR_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
            MODIFY_REG(hperh->perh->ADDR2, I2C_ADDR2_OA2_MSK, (hperh->init.own_addr2 & 0x7F) << I2C_ADDR2_OA2_POSS);
            SET_BIT(hperh->perh->ADDR2, I2C_ADDR2_OA2EN_MSK);
        }
    }

    ALD_I2C_ENABLE(hperh);

    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;

    return ALD_OK;
}

/**
 * @brief  DeInitialize the I2C peripheral.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_reset(ald_i2c_handle_t *hperh)
{
    if (hperh == NULL)
        return ALD_ERROR;

    ALD_I2C_DISABLE(hperh);

    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;

    __UNLOCK(hperh);

    WRITE_REG(hperh->perh->CON1, 0);
    WRITE_REG(hperh->perh->CON2, 0);
    WRITE_REG(hperh->perh->ADDR1, 0);
    WRITE_REG(hperh->perh->ADDR2, 0);
    WRITE_REG(hperh->perh->TIMINGR, 0);
    WRITE_REG(hperh->perh->TIMEOUTR, 0);
    WRITE_REG(hperh->perh->IDR, ALD_I2C_FLAG_MASK);
    WRITE_REG(hperh->perh->ICR, ALD_I2C_FLAG_MASK);

    ALD_I2C_ENABLE(hperh);

    return ALD_OK;
}
/**
 * @}
 */

/** @defgroup I2C_Public_Functions_Group2 Input and Output operation functions
 *  @brief   Data transfers functions
 *
@verbatim
 ===============================================================================
                      ##### IO operation functions #####
 ===============================================================================
    [..]
    This subsection provides a set of functions allowing to manage the I2C data
    transfers.

    (#) There are two modes of transfer:
       (++) Blocking mode : The communication is performed in the polling mode.
            The status of all data processing is returned by the same function
            after finishing transfer.
       (++) No-Blocking mode : The communication is performed using Interrupts
            or DMA. These functions return the status of the transfer startup.
            The end of the data processing will be indicated through the
            dedicated I2C IRQ when using Interrupt mode or the DMA IRQ when
            using DMA mode.

    (#) Blocking mode functions are :
        (++) ald_i2c_master_send()
        (++) ald_i2c_master_recv()
        (++) ald_i2c_slave_send()
        (++) ald_i2c_slave_recv()
        (++) ald_i2c_mem_write()
        (++) ald_i2c_mem_read()

    (#) No-Blocking mode functions with Interrupt are :
        (++) ald_i2c_master_send_by_it()
        (++) ald_i2c_master_recv_by_it()
        (++) ald_i2c_slave_send_by_it()
        (++) ald_i2c_slave_recv_by_it()
        (++) ald_i2c_mem_write_by_it()
        (++) ald_i2c_mem_read_by_it()

    (#) No-Blocking mode functions with DMA are :
        (++) ald_i2c_master_send_by_dma()
        (++) ald_i2c_master_recv_by_dma()
        (++) ald_i2c_slave_send_by_dma()
        (++) ald_i2c_slave_recv_by_dma()
        (++) ald_i2c_mem_write_by_dma()
        (++) ald_i2c_mem_read_by_dma()

    (#) A set of Transfer Complete Callbacks are provided in non Blocking mode:
        (++) hperh->mem_tx_cplt_cbk()
        (++) hperh->mem_rx_cplt_cbk()
        (++) hperh->master_tx_cplt_cbk()
        (++) hperh->master_rx_cplt_cbk()
        (++) hperh->slave_tx_cplt_cbk()
        (++) hperh->slave_rx_cplt_cbk()
        (++) hperh->error_callback()

@endverbatim
 * @{
 */
/**
 * @brief  Transmits in master mode an amount of data in blocking mode.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
 * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_send(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                 uint32_t size, uint32_t timeout)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    i2c_master_req_write(hperh, dev_addr, timeout);

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    while (size > 0)
    {
        hperh->perh->TXDATA  = (*buf++);
        size--;
        hperh->xfer_count++;

        if (i2c_wait_txe_to_timeout(hperh, timeout) != ALD_OK)
            goto ERROR;

        if (((hperh->xfer_count % 0xFFFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK)))
        {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == ALD_OK)
            {
                if (size > 0xFFFF)
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
                }
                else
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
                    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                }
            }
            else
            {
                goto ERROR;
            }
        }
    }

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == SET)
        goto SUCCESS;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == ALD_OK)
    {
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        goto SUCCESS;
    }
    else
    {
        goto ERROR;
    }

ERROR:
    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
 * @brief  Receives in master mode an amount of data in blocking mode.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t
 */
  ald_status_t ald_i2c_master_recv(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                uint32_t size, uint32_t timeout)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    i2c_master_req_read(hperh, dev_addr, timeout);

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    while (size > 0)
    {
        if (i2c_wait_rxne_to_timeout(hperh, timeout) != ALD_OK)
            goto ERROR;

        (*buf++) = hperh->perh->RXDATA;
        size--;
        hperh->xfer_count++;

        if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK)))
        {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == ALD_OK)
            {
                if (size > 0xFFFF)
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
                }
                else
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
                    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                }
            }
            else
            {
                goto ERROR;
            }
        }
    }

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
        goto SUCCESS;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        goto SUCCESS;

ERROR:
    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
 * @brief  Transmits in slave mode an amount of data in blocking mode.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_slave_send(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    ALD_I2C_ENABLE(hperh);

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TXE, RESET, timeout) != ALD_OK)
        goto ERROR;

    hperh->perh->TXDATA = (*buf++);
    --size;
    hperh->xfer_count++;

    if (i2c_wait_master_addr_to_timeout(hperh, ALD_I2C_IT_ADDR, timeout) == ALD_ERROR)
        goto ERROR;

    while (size > 0)
    {
        if (i2c_wait_txe_to_timeout(hperh, timeout) == ALD_ERROR)
            goto ERROR;

        if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TXE, RESET, timeout) != ALD_OK)
            goto ERROR;

        hperh->perh->TXDATA = (*buf++);
        --size;
        hperh->xfer_count++;
    }

    goto SUCCESS;

ERROR:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
 * @brief  Receive in slave mode an amount of data in blocking mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
 * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_slave_recv(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_count = 0;
    hperh->xfer_size  = size;

    if (i2c_wait_master_addr_to_timeout(hperh, ALD_I2C_IT_ADDR, timeout) == ALD_ERROR)
        goto ERROR;

    while (size > 0)
    {
        if (i2c_wait_rxne_to_timeout(hperh, timeout) == ALD_ERROR)
            goto ERROR;

        if (READ_BIT(hperh->perh->CON2, I2C_CON2_HOLDACK_MSK))
            SET_BIT(hperh->perh->CON2, I2C_CON2_ACK_UPD_MSK);

        (*buf++) = hperh->perh->RXDATA;
        --size;
        hperh->xfer_count++;
    }

    goto SUCCESS;

ERROR:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
 * @brief  Transmit in master mode an amount of data in non-blocking mode with Interrupt
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_send_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG);

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TXE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_NACK);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TCR);

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TC | ALD_I2C_IT_TCR);

    return ALD_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_recv_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG) ;

    if (size <= 0xFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_RXNE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TCR);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);

    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_TCR | ALD_I2C_IT_TC);

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    return ALD_OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_send_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TXE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_NACK);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_STOP);

    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_ADDR | ALD_I2C_IT_NACK | ALD_I2C_IT_STOP | ALD_I2C_IT_TXE);

    return ALD_OK;
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_recv_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_RXNE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_STOP);

    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_ADDR | ALD_I2C_IT_STOP);

    return ALD_OK;
}

/**
 * @brief  Sequential Transmit in master mode an amount of data in non-blocking mode with Interrupt
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent
 * @param  option: Options of Transfer
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_seq_send_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size, uint32_t option)
{
    uint32_t pre_state = 0;
    uint32_t it_flag   = 0;

    assert_param(IS_I2C_TRANSFER_OPTIONS(option));

    if (hperh->state == ALD_I2C_STATE_READY) {
        if ((READ_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK) == I2C_CON2_STOP_MSK) || (option == ALD_I2C_FIRST_AND_LAST_FRAME) || (option == ALD_I2C_FIRST_FRAME)) {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK) {
                hperh->state       = ALD_I2C_STATE_READY;
                hperh->mode        = ALD_I2C_MODE_NONE;
                hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

                __UNLOCK(hperh);
                return ALD_BUSY;
            }
        }

        __LOCK(hperh);

        if ((READ_BIT(hperh->perh->CON1, I2C_CON1_PE_MSK) != I2C_CON1_PE_MSK)) {
            ALD_I2C_ENABLE(hperh);
        }

        hperh->state      = ALD_I2C_STATE_BUSY_TX;
        hperh->mode       = ALD_I2C_MODE_MASTER;
        hperh->error_code = ALD_I2C_ERROR_NONE;

        hperh->p_buff     = buf;
        hperh->xfer_size  = size;
        hperh->xfer_count = 0;
        hperh->xfer_opt   = option;
        pre_state         = hperh->pre_state;

        if (size <= 0xFFFF)
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
        }
        else
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        }

        if ((pre_state != ALD_I2C_STATE_MASTER_BUSY_TX) || (IS_I2C_TRANSFER_OTHER_OPTIONS(option))) {
            i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG);

            SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
            SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);
        }

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TXE);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_NACK);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TCR);
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);

        it_flag = ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TCR;

        if ((option == ALD_I2C_FIRST_AND_LAST_FRAME) || (option == ALD_I2C_LAST_FRAME) || (option == ALD_I2C_OTHER_AND_LAST_FRAME)) {
            it_flag |= ALD_I2C_IT_TC;

            if (size <= 0xFFFF) {
                CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                it_flag &= ~ALD_I2C_IT_TCR;
            }
        }

        ALD_I2C_ENABLE_IT(hperh, it_flag);

        __UNLOCK(hperh);
    } else {
        return ALD_BUSY;
    }

    return ALD_OK;
}

/**
  * @brief  Sequential Receive in master mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  option: Options of Transfer
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_seq_recv_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf, uint32_t size, uint32_t option)
{
    uint32_t pre_state = 0;
    uint32_t it_flag   = 0;

    assert_param(IS_I2C_TRANSFER_OPTIONS(option));

    if (hperh->state == ALD_I2C_STATE_READY)
    {
        if ((READ_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK) == I2C_CON2_STOP_MSK) || (option == ALD_I2C_FIRST_AND_LAST_FRAME) || (option == ALD_I2C_FIRST_FRAME)) {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK) {
                hperh->state       = ALD_I2C_STATE_READY;
                hperh->mode        = ALD_I2C_MODE_NONE;
                hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

                __UNLOCK(hperh);
                return ALD_BUSY;
            }
        }

        __LOCK(hperh);

        if ((READ_BIT(hperh->perh->CON1, I2C_CON1_PE_MSK) != I2C_CON1_PE_MSK))
            ALD_I2C_ENABLE(hperh);

        hperh->state      = ALD_I2C_STATE_BUSY_RX;
        hperh->mode       = ALD_I2C_MODE_MASTER;
        hperh->error_code = ALD_I2C_ERROR_NONE;

        hperh->p_buff     = buf;
        hperh->xfer_size  = size;
        hperh->xfer_count = 0;
        pre_state         = hperh->pre_state;

        if (size <= 0xFFFF)
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
        }
        else
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        }

        if ((pre_state != ALD_I2C_STATE_MASTER_BUSY_RX) || (IS_I2C_TRANSFER_OTHER_OPTIONS(option))) {
            i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG);

            SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
            SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);
        }

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_RXNE);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TCR);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);

        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);

        it_flag = ALD_I2C_IT_RXNE | ALD_I2C_IT_TCR;
        if ((option == ALD_I2C_FIRST_AND_LAST_FRAME) || (option == ALD_I2C_LAST_FRAME) || (option == ALD_I2C_OTHER_AND_LAST_FRAME))
            it_flag |= ALD_I2C_IT_TC;

        ALD_I2C_ENABLE_IT(hperh, it_flag);

        __UNLOCK(hperh);
    }
    else
    {
        return ALD_BUSY;
    }

    return ALD_OK;
}

/**
  * @brief  Sequential Transmit in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  option: Options of Transfer
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_seq_send_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t option)
{
    assert_param(IS_I2C_TRANSFER_OPTIONS(option));

    if (((hperh->state & ALD_I2C_STATE_LISTEN) == ALD_I2C_STATE_LISTEN) || (hperh->state == ALD_I2C_STATE_READY))
    {
        if ((buf == NULL) || (size == 0))
            return ALD_ERROR;

        __LOCK(hperh);

        if ((READ_BIT(hperh->perh->CON1, I2C_CON1_PE_MSK) != I2C_CON1_PE_MSK))
            ALD_I2C_ENABLE(hperh);

        hperh->state      = ALD_I2C_STATE_BUSY_TX_LISTEN;
        hperh->mode       = ALD_I2C_MODE_SLAVE;
        hperh->error_code = ALD_I2C_ERROR_NONE;

        hperh->p_buff     = buf;
        hperh->xfer_size  = size;
        hperh->xfer_count = 0;
        hperh->xfer_opt   = option;

        __UNLOCK(hperh);

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TXE);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_NACK);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_STOP);

        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
        ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_ADDR | ALD_I2C_IT_NACK | ALD_I2C_IT_STOP | ALD_I2C_IT_TXE);
    }
    else
    {
        return ALD_BUSY;
    }

    return ALD_OK;
}

/**
  * @brief  Sequential Receive in slave mode an amount of data in non-blocking mode with Interrupt
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  option: Options of Transfer
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_seq_recv_by_it(ald_i2c_handle_t *hperh, uint8_t *buf, uint32_t size, uint32_t option)
{
    assert_param(IS_I2C_TRANSFER_OPTIONS(option));

    if (((hperh->state & ALD_I2C_STATE_LISTEN) == ALD_I2C_STATE_LISTEN) || (hperh->state == ALD_I2C_STATE_READY))
    {
        if ((buf == NULL) || (size == 0))
            return ALD_ERROR;

        __LOCK(hperh);

        if ((READ_BIT(hperh->perh->CON1, I2C_CON1_PE_MSK) != I2C_CON1_PE_MSK))
            ALD_I2C_ENABLE(hperh);

        hperh->state      = ALD_I2C_STATE_BUSY_RX_LISTEN;
        hperh->mode       = ALD_I2C_MODE_SLAVE;
        hperh->error_code = ALD_I2C_ERROR_NONE;

        hperh->p_buff     = buf;
        hperh->xfer_size  = size;
        hperh->xfer_count = 0;
        hperh->xfer_opt   = option;

        __UNLOCK(hperh);

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_RXNE);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_STOP);

        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
        ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_ADDR | ALD_I2C_IT_STOP);
    }
    else
    {
        return ALD_BUSY;
    }

    return ALD_OK;
}

/**
 * @brief  Enable the Address listen mode whit Interrupt
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  addr: Devaddress Target device address
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_abort_it(ald_i2c_handle_t *hperh, uint16_t addr)
{
    UNUSED(addr);
    if ((READ_BIT(hperh->perh->STAT, I2C_STAT_BUSY_MSK) != RESET) && (hperh->mode == ALD_I2C_MODE_MASTER))
    {
        __LOCK(hperh);

        hperh->pre_state = ALD_I2C_STATE_NONE;
        hperh->state     = ALD_I2C_STATE_ABORT;

        SET_BIT(hperh->perh->CON1, I2C_CON2_STOP_MSK);
        hperh->xfer_size = 0;
        hperh->xfer_count = 0;

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_FLAG_MASK);
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);

        __UNLOCK(hperh);
        return ALD_OK;
    }
    else
    {
        return ALD_ERROR;
    }
}

/**
 * @brief  Enable the Address listen mode whit Interrupt
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_enablelisten_it(ald_i2c_handle_t *hperh)
{
    if (hperh->state == ALD_I2C_STATE_READY)
    {
        hperh->state = ALD_I2C_STATE_LISTEN;

        if ((READ_BIT(hperh->perh->CON1, I2C_CON1_PE_MSK) != I2C_CON1_PE_MSK))
            ALD_I2C_ENABLE(hperh);

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
        ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_ADDR);

        return ALD_OK;
    }
    else
    {
        return ALD_BUSY;
    }
}

/**
 * @brief  Disable the Address listen mode whit Interrupt
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_disablelisten_it(ald_i2c_handle_t *hperh)
{
    if (hperh->state == ALD_I2C_STATE_LISTEN)
    {
        hperh->pre_state = ((hperh->state) & ALD_I2C_STATE_MSK) | (hperh->mode);
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode = ALD_I2C_MODE_NONE;

        ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_ADDR);
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);

        return ALD_OK;
    }
    else
    {
        return ALD_BUSY;
    }
}

/**
 * @brief  Transmit in master mode an amount of data in non-blocking mode with DMA
 * @note   The maximum amount of data to be sent is 0xFF.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  buf: Pointer to data buffer
 * @param  size: Amount of data to be sent (maximum is 0xFF)
 * @param  channel: DMA channel as I2C transmit
 * @retval Status, see @ref ald_status_t.
 */
ald_status_t ald_i2c_master_send_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                    uint16_t size, uint8_t channel)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    if (size >= 0xFFFF)
        size = 0xFFFF;

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    if (hperh->hdmatx.perh == NULL)
        hperh->hdmatx.perh = DMA;

    hperh->hdmatx.cplt_tc_cbk = i2c_dma_master_send_cplt;
    hperh->hdmatx.cplt_tc_arg = hperh;

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);

    SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmatx.config);
    hperh->hdmatx.config.size           = size;
    hperh->hdmatx.config.src            = (void *)hperh->p_buff;
    hperh->hdmatx.config.dst            = (void *)&hperh->perh->TXDATA;
    hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.src_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmatx.config.dst_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmatx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmatx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_TXEMPTY;
    hperh->hdmatx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmatx);

    i2c_master_req_write(hperh, dev_addr, I2C_TIMEOUT_FLAG);

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Receive in master mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C receive
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_master_recv_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint8_t *buf,
                                    uint16_t size, uint8_t channel)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    if (size >= 0xFFFF)
        size = 0xFFFF;

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    if (hperh->hdmarx.perh == NULL)
        hperh->hdmarx.perh = DMA;

    hperh->hdmarx.cplt_tc_cbk = i2c_dma_master_recv_cplt;
    hperh->hdmarx.cplt_tc_arg = (void *)hperh;

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);

    SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmarx.config);
    hperh->hdmarx.config.size           = size;
    hperh->hdmarx.config.src            = (void *)&hperh->perh->RXDATA;
    hperh->hdmarx.config.dst            = (void *)buf;
    hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmarx.config.src_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmarx.config.dst_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmarx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmarx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_RNR;
    hperh->hdmarx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmarx);

    i2c_master_req_read(hperh, dev_addr, I2C_TIMEOUT_FLAG);

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    return ALD_OK;
}

/**
  * @brief  Transmit in slave mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C Transmit
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_send_by_dma(ald_i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    if (size >= 0xFFFF)
        size = 0xFFFF;

    if (hperh->hdmatx.perh == NULL)
        hperh->hdmatx.perh = DMA;

    hperh->hdmatx.cplt_tc_cbk = i2c_dma_slave_send_cplt;
    hperh->hdmatx.cplt_tc_arg = hperh;

    SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmatx.config);
    hperh->hdmatx.config.src            = (void *)buf;
    hperh->hdmatx.config.dst            = (void *)&hperh->perh->TXDATA;
    hperh->hdmatx.config.size           = size;
    hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.src_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmatx.config.dst_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmatx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmatx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_TXEMPTY;
    hperh->hdmatx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmatx);

    if (i2c_wait_master_addr_to_timeout(hperh, ALD_I2C_IT_ADDR, I2C_TIMEOUT_ADDR_SLAVE) == ALD_ERROR)
    {
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        return ALD_ERROR;
    }

    return ALD_OK;
}

/**
  * @brief  Receive in slave mode an amount of data in non-blocking mode with DMA
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel as I2C receive
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_slave_recv_by_dma(ald_i2c_handle_t *hperh, uint8_t *buf, uint16_t size, uint8_t channel)
{
    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_SLAVE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    if (size >= 0xFF)
        size = 0xFF;

    if (hperh->hdmarx.perh == NULL)
        hperh->hdmarx.perh = DMA;

    hperh->hdmarx.cplt_tc_cbk = i2c_dma_slave_recv_cplt;
    hperh->hdmarx.cplt_tc_arg = (void *)hperh;

    SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmarx.config);
    hperh->hdmarx.config.src            = (void *)&hperh->perh->RXDATA;
    hperh->hdmarx.config.dst            = (void *)buf;
    hperh->hdmarx.config.size           = size;
    hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmarx.config.src_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmarx.config.dst_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmarx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmarx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_RNR;
    hperh->hdmarx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmarx);

    if (i2c_wait_master_addr_to_timeout(hperh, ALD_I2C_IT_ADDR, I2C_TIMEOUT_ADDR_SLAVE) == ALD_ERROR)
    {
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        return ALD_ERROR;
    }

    return ALD_OK;
}

/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                           ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint32_t nbyte = 0;

    assert_param(IS_I2C_MEMADD_size(add_size));

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MEM;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, timeout) != ALD_OK)
        goto ERROR;

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    while (size > 0)
    {
        hperh->perh->TXDATA = (*buf++);
        --size;
        hperh->xfer_count++;

        if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK)))
        {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TCR, RESET, I2C_TIMEOUT_FLAG) == ALD_OK)
            {
                if (size > 0xFFFF)
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
                }
                else
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
                    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                }
            }
            else
            {
                goto ERROR;
            }
        }

        if (i2c_wait_txe_to_timeout(hperh, timeout) != ALD_OK)
            goto ERROR;
    }

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
        goto SUCCESS;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TC, RESET, timeout))
        goto ERROR;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        goto SUCCESS;

ERROR:
    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  timeout: Timeout duration
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, ald_i2c_addr_size_t add_size,
                          uint8_t *buf, uint32_t size, uint32_t timeout)
{
    uint32_t nbyte = 0;

    assert_param(IS_I2C_MEMADD_size(add_size));

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MEM;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->xfer_count = 0;
    hperh->xfer_size  = size;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, timeout) != ALD_OK)
        return ALD_ERROR;

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    while (size > 0)
    {
        if (i2c_wait_rxne_to_timeout(hperh, timeout) != ALD_OK)
            goto ERROR;

        (*buf++) = hperh->perh->RXDATA;
        size--;
        hperh->xfer_count++;

        if (((hperh->xfer_count % 0xFF) == 0) && (READ_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK)))
        {
            if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TCR, RESET, timeout) == ALD_OK)
            {
                if (size > 0xFFFF)
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
                }
                else
                {
                    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
                    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
                    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
                }
            }
            else
            {
                goto ERROR;
            }
        }
    }

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK))
        goto SUCCESS;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        goto SUCCESS;

ERROR:
    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_ERROR;

SUCCESS:
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    return ALD_OK;
}

/**
  * @brief  Write an amount of data in non-blocking mode with Interrupt to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                              ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size)
{
    uint32_t nbyte = 0;

    assert_param(IS_I2C_MEMADD_size(add_size));

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MEM;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != ALD_OK)
    {
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        return ALD_ERROR;
    }

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TXE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_NACK);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TCR);

    hperh->perh->TXDATA = (*hperh->p_buff++);
    hperh->xfer_count++;

    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_FLAG_MASK);
    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TC | ALD_I2C_IT_TCR);

    return ALD_OK;
}

/**
  * @brief  Read an amount of data in non-blocking mode with Interrupt from a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read_by_it(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr,
                             ald_i2c_addr_size_t add_size, uint8_t *buf, uint32_t size)
{
    uint32_t nbyte = 0;

    assert_param(IS_I2C_MEMADD_size(add_size));

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_TYPE(hperh->perh));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MEM;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != ALD_OK)
    {
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        return ALD_ERROR;
    }

    if (size <= 0xFFFF)
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    }
    else
    {
        MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
        MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    }

    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_RXNE);
    ALD_I2C_CLEAR_IT(hperh, ALD_I2C_IT_TC);
    ALD_I2C_CLEAR_IT(hperh , ALD_I2C_IT_TCR);

    ALD_I2C_ENABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_TC | ALD_I2C_IT_TCR);

    SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    return ALD_OK;
}

/**
  * @brief  Write an amount of data in non-blocking mode with DMA to a specific memory address
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address(Maxsiz 0xFF)
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be sent
  * @param  channel: DMA channel
   * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_write_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, ald_i2c_addr_size_t add_size,
                               uint8_t *buf, uint16_t size, uint8_t channel)
{
    uint32_t nbyte = 0;

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_MEMADD_size(add_size));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_TX;
    hperh->mode       = ALD_I2C_MODE_MASTER;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = 0;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_write(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != ALD_OK)
    {
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        return ALD_ERROR;
    }

    if (hperh->hdmatx.perh == NULL)
        hperh->hdmatx.perh = DMA;

    hperh->hdmatx.cplt_tc_cbk = i2c_dma_mem_send_cplt;
    hperh->hdmatx.cplt_tc_arg = hperh;

    SET_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmatx.config);
    hperh->hdmatx.config.src            = (void *)hperh->p_buff;
    hperh->hdmatx.config.dst            = (void *)&hperh->perh->TXDATA;
    hperh->hdmatx.config.size           = size;
    hperh->hdmatx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmatx.config.src_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmatx.config.dst_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmatx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmatx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_TXEMPTY;
    hperh->hdmatx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmatx);

    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);

    return ALD_OK;
}

/**
  * @brief  Reads an amount of data in non-blocking mode with DMA from a specific memory address.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @param  dev_addr: Target device address
  * @param  mem_addr: Internal memory address
  * @param  add_size: size of internal memory address
  * @param  buf: Pointer to data buffer
  * @param  size: Amount of data to be read
  * @param  channel: DMA channel
  * @retval Status, see @ref ald_status_t.
  */
ald_status_t ald_i2c_mem_read_by_dma(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, ald_i2c_addr_size_t add_size,
                              uint8_t *buf, uint16_t size, uint8_t channel)
{
    uint32_t nbyte = 0;

    if (hperh->state != ALD_I2C_STATE_READY)
        return ALD_BUSY;

    if ((buf == NULL) || (size == 0))
        return ALD_ERROR;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_BUSY, SET, I2C_TIMEOUT_BUSY_FLAG) != ALD_OK)
        return ALD_BUSY;

    assert_param(IS_I2C_MEMADD_size(add_size));
    __LOCK(hperh);

    hperh->state      = ALD_I2C_STATE_BUSY_RX;
    hperh->mode       = ALD_I2C_MODE_MEM;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    hperh->p_buff     = buf;
    hperh->xfer_size  = size;
    hperh->xfer_count = size;

    nbyte = (add_size == ALD_I2C_MEMADD_SIZE_8BIT) ? 1 : 2;
    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, nbyte << I2C_CON2_NBYTES_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    if (i2c_req_mem_read(hperh, dev_addr, mem_addr, add_size, I2C_TIMEOUT_FLAG) != ALD_OK)
    {
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);
    }

    if (hperh->hdmarx.perh == NULL)
        hperh->hdmarx.perh = DMA;

    hperh->hdmarx.cplt_tc_cbk = i2c_dma_mem_recv_cplt;
    hperh->hdmarx.cplt_tc_arg = (void *)hperh;

    SET_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    ald_dma_interrupt_config(channel, ALD_DMA_IT_FLAG_TC, ENABLE);
    ald_dma_config_struct(&hperh->hdmarx.config);
    hperh->hdmarx.config.src            = (void *)&hperh->perh->RXDATA;
    hperh->hdmarx.config.dst            = (void *)buf;
    hperh->hdmarx.config.src_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmarx.config.dst_data_width = ALD_DMA_DATA_SIZE_BYTE;
    hperh->hdmarx.config.size           = size;
    hperh->hdmarx.config.src_inc        = ALD_DMA_DATA_INC_DISABLE;
    hperh->hdmarx.config.dst_inc        = ALD_DMA_DATA_INC_ENABLE;
    hperh->hdmarx.config.msel           = hperh->perh == I2C0 ? ALD_DMA_MSEL_I2C0 : ALD_DMA_MSEL_I2C1;
    hperh->hdmarx.config.msigsel        = ALD_DMA_MSIGSEL_I2C_RNR;
    hperh->hdmarx.config.channel        = channel;
    ald_dma_config_basic(&hperh->hdmarx);

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
    MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);

    SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);
    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    __UNLOCK(hperh);

    return ALD_OK;
}

/**
 * @}
 */

/** @defgroup I2C_Public_Functions_Group3 Peripheral state and Errors functions
 *  @brief   Peripheral state and Errors functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral state and Errors functions #####
 ===============================================================================
    [..]
    This subsection permits to get in run-time the status of the peripheral
    and the data flow.

@endverbatim
 * @{
 */

/**
 * @brief  Return the I2C handle state.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval ald_status_t state
 */
ald_i2c_state_t ald_i2c_get_state(ald_i2c_handle_t *hperh)
{
    return hperh->state;
}

/**
 * @brief  Return the I2C error code.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval I2C Error Code
 */
uint32_t ald_i2c_get_error(ald_i2c_handle_t *hperh)
{
    return hperh->error_code;
}
/**
 * @}
 */

/** @defgroup I2C_Public_Functions_Group4 IRQ Handler and Callbacks
 * @{
 */

/**
  * @brief  This function handles I2C event interrupt request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void ald_i2c_ev_irq_handler(ald_i2c_handle_t *hperh)
{
    uint32_t size = hperh->xfer_size - hperh->xfer_count;

    /**< Transmit empty interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXE) == SET)
    {
        if ((hperh->mode == ALD_I2C_MODE_MASTER) || (hperh->mode == ALD_I2C_MODE_MEM))
            i2c_master_send_txe(hperh);
        else if (hperh->mode == ALD_I2C_MODE_SLAVE)
            i2c_slave_send_txe(hperh);

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXE);
    }

    /**< Receive not empty interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXNE) == SET)
    {
        if ((hperh->mode == ALD_I2C_MODE_MASTER) || (hperh->mode == ALD_I2C_MODE_MEM))
            i2c_master_recv_rxne(hperh);
        else if (hperh->mode == ALD_I2C_MODE_SLAVE)
            i2c_slave_recv_rxne(hperh);

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXNE);
    }

    /**< Transmit completed interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TC) == SET)
    {
        if ((hperh->mode == ALD_I2C_MODE_MASTER) || (hperh->mode == ALD_I2C_MODE_MEM))
        {
            if (ALD_I2C_MASTER_GET_DIR(hperh) == RESET)
                i2c_master_send_tc(hperh);
            else
                i2c_master_recv_tc(hperh);
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TC);
    }

    /**< Transmit and reload completed interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TCR) == SET)
    {
        if (size > 0xFFFF)
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
        }
        else
        {
            MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
            MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
            CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TCR);
    }

    /**< Address matching interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ADDR) == SET)
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ADDR);

    /**< Stop detection interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_STOP) == SET)
    {
        i2c_slave_stopf(hperh);
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_STOP);
    }
}

/**
  * @brief  This function handles I2C error interrupt request.
  * @param  hperh: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval  NONE
  */
void ald_i2c_er_irq_handler(ald_i2c_handle_t *hperh)
{
    /**< Transmit overrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXOV) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXOV);
        hperh->error_code |= ALD_I2C_ERROR_TOV;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    /**< Transmit underrun */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXUD) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXUD);
        hperh->error_code |= ALD_I2C_ERROR_TUD;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< Receive overrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXOV) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXOV);
        hperh->error_code |= ALD_I2C_ERROR_ROV;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< Receive underrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXUD) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXUD);
        hperh->error_code |= ALD_I2C_ERROR_RUD;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< NACK interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_NACK) == SET)
    {
        if (hperh->xfer_count != hperh->xfer_size)
        {
            hperh->state |= ALD_I2C_ERROR_AF;
        }
        else
        {
            ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK);
            ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_NACK);
            return;
        }

        if ((hperh->mode == ALD_I2C_MODE_MASTER) || (hperh->mode == ALD_I2C_MODE_MEM))
            SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK);
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_NACK);

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< Bus error interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_BERR) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_BERR);
        hperh->state |= ALD_I2C_ERROR_BERR;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< Arbitration loss interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ARLO) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ARLO);
        hperh->state |= ALD_I2C_ERROR_ARLO;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< PEC error interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_PECE) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_PECE);

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< Timeout interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TOUT) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TOUT);
        hperh->state |= ALD_I2C_ERROR_TIMEOUT;

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }

    /**< SMBus Alert interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ALERT) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ALERT);

        hperh->state = ALD_I2C_STATE_READY;
        hperh->mode  = ALD_I2C_MODE_NONE;
        __UNLOCK(hperh);

        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
}

/**
  * @brief  This function handles I2C event interrupt request.
  * @param  hperh: Pointer to a i2c_handle_t structure that contains
  *                the configuration information for the specified I2C.
  * @retval None
  */
void ald_i2c_seq_ev_irq_handler(ald_i2c_handle_t *hperh)
{
    uint32_t size = hperh->xfer_size - hperh->xfer_count;
    ald_i2c_state_t current_state = hperh->state;
    uint32_t current_opt      = hperh->xfer_opt;
    uint8_t tmp               = 0;

    /**< Address matching interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ADDR) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ADDR);

        if ((hperh->state & ALD_I2C_STATE_LISTEN) == ALD_I2C_STATE_LISTEN)
        {
            if (hperh->addr_cplt_cbk != NULL)
                hperh->addr_cplt_cbk(hperh);

            if (hperh->state == ALD_I2C_STATE_BUSY_TX_LISTEN)
                hperh->state = ALD_I2C_STATE_BUSY_TX;

            if (hperh->state == ALD_I2C_STATE_BUSY_RX_LISTEN)
                hperh->state = ALD_I2C_STATE_BUSY_RX;
        }
    }

    /**< Transmit empty interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXE) == SET)
    {
        if (hperh->mode == ALD_I2C_MODE_MASTER)
        {
            if ((hperh->xfer_size == 0) && (current_state == ALD_I2C_STATE_BUSY_TX))
            {
                ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TC | ALD_I2C_IT_TCR);
                hperh->state = ALD_I2C_STATE_READY;
                hperh->mode  = ALD_I2C_MODE_NONE;

                if ((current_opt != ALD_I2C_LAST_FRAME) && (current_opt != ALD_I2C_FIRST_AND_LAST_FRAME) && (current_opt != ALD_I2C_OTHER_AND_LAST_FRAME))
                {
                    hperh->pre_state = ALD_I2C_STATE_BUSY_TX;
                    __UNLOCK(hperh);
                }
                else
                {
                    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
                    hperh->pre_state  = (uint32_t)ALD_I2C_STATE_NONE;

                    __UNLOCK(hperh);
                }

                if (hperh->master_tx_cplt_cbk != NULL)
                    hperh->master_tx_cplt_cbk (hperh);
            }

            if (hperh->xfer_count != hperh->xfer_size)
            {
                hperh->perh->TXDATA = (*hperh->p_buff++);
                hperh->xfer_count++;
            }
        }
        else if (hperh->mode == ALD_I2C_MODE_SLAVE)
        {
            if (hperh->xfer_size > hperh->xfer_count)
            {
                while(hperh->perh->STAT & (0x1 << 1));
                hperh->perh->TXDATA = (*hperh->p_buff++);
                hperh->xfer_count++;
            }
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXE);
    }

    /**< Receive not empty interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXNE) == SET)
    {
        if ((hperh->state == ALD_I2C_STATE_BUSY_RX) || (hperh->state == ALD_I2C_STATE_BUSY_RX_LISTEN))
        {
            if (hperh->xfer_size - hperh->xfer_count > 0)
            {
                (*hperh->p_buff++) = hperh->perh->RXDATA;
                hperh->xfer_count++;
            }
            else
            {
                tmp = hperh->perh->RXDATA;
                UNUSED(tmp);
            }
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXNE);
    }

    /**< Transmit completed interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TC) == SET)
    {
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TC | ALD_I2C_IT_TCR);
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

        hperh->pre_state = ALD_I2C_STATE_NONE;
        hperh->mode      = ALD_I2C_MODE_NONE;
        hperh->state     = ALD_I2C_STATE_READY;
        __UNLOCK(hperh);

        if (current_state == ALD_I2C_STATE_MASTER_BUSY_TX)
        {
            ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK);
            if (hperh->master_tx_cplt_cbk != NULL)
                hperh->master_tx_cplt_cbk (hperh);
        }
        else if (current_state == ALD_I2C_STATE_SLAVE_BUSY_TX)
        {
            ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK);
            if (hperh->slave_tx_cplt_cbk != NULL)
                hperh->slave_tx_cplt_cbk (hperh);
        }
        else if (current_state == ALD_I2C_STATE_MASTER_BUSY_RX)
        {
            ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_RXNE);
            if (hperh->master_rx_cplt_cbk != NULL)
                hperh->master_rx_cplt_cbk (hperh);
        }
        else if (current_state == ALD_I2C_STATE_SLAVE_BUSY_RX)
        {
            ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_RXNE);
            if (hperh->slave_rx_cplt_cbk != NULL)
                hperh->slave_rx_cplt_cbk (hperh);
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TC);
    }

    /**< Transmit and reload completed interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TCR) == SET)
    {
        if (size == 0)
        {
            if (current_state == ALD_I2C_STATE_BUSY_TX)
            {
                if (hperh->mode == ALD_I2C_MODE_MASTER)
                    hperh->pre_state = ALD_I2C_STATE_MASTER_BUSY_TX;
                else
                    hperh->pre_state = ALD_I2C_STATE_SLAVE_BUSY_TX;

                hperh->mode  = ALD_I2C_MODE_NONE;
                hperh->state = ALD_I2C_STATE_READY;
                __UNLOCK(hperh);

                ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TCR);

                if (hperh->master_tx_cplt_cbk != NULL)
                    hperh->master_tx_cplt_cbk (hperh);
            }
            else if (current_state == ALD_I2C_STATE_BUSY_RX)
            {
                if (hperh->mode == ALD_I2C_MODE_MASTER)
                    hperh->pre_state = ALD_I2C_STATE_MASTER_BUSY_RX;
                else
                    hperh->pre_state = ALD_I2C_STATE_SLAVE_BUSY_RX;

                hperh->state     = ALD_I2C_STATE_READY;
                hperh->mode      = ALD_I2C_MODE_NONE;
                __UNLOCK(hperh);

                ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_TCR);

                if (hperh->master_rx_cplt_cbk != NULL)
                    hperh->master_rx_cplt_cbk(hperh);
            }
        }
        else
        {
            if (size > 0xFFFF)
            {
                MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, 0xFF << I2C_CON2_NBYTES_POSS);
                MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, 0xFF << I2C_CON1_NBYTES_POSS);
            }
            else
            {
                MODIFY_REG(hperh->perh->CON2, I2C_CON2_NBYTES_MSK, (size & 0xFF) << I2C_CON2_NBYTES_POSS);
                MODIFY_REG(hperh->perh->CON1, I2C_CON1_NBYTES_MSK, (size >> 8) << I2C_CON1_NBYTES_POSS);
                if ((current_opt == ALD_I2C_FIRST_AND_LAST_FRAME) || (current_opt == ALD_I2C_LAST_FRAME) || (current_opt == ALD_I2C_OTHER_AND_LAST_FRAME))
                    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
            }
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TCR);
    }

    /**< Stop detection interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_STOP) == SET)
    {
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_ADDR | ALD_I2C_IT_NACK | ALD_I2C_IT_RXNE | ALD_I2C_IT_TXE | ALD_I2C_IT_STOP);
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_STOP);

        if ((size == 0) && (hperh->error_code == ALD_I2C_ERROR_NONE))
        {
            if (hperh->state == ALD_I2C_STATE_BUSY_TX_LISTEN)
            {
                hperh->pre_state = ALD_I2C_STATE_BUSY_TX_LISTEN;
                hperh->state     = ALD_I2C_STATE_LISTEN;
                hperh->mode      = ALD_I2C_MODE_NONE;

                if (hperh->slave_tx_cplt_cbk != NULL)
                    hperh->slave_tx_cplt_cbk(hperh);
            }
            if (hperh->state == ALD_I2C_STATE_BUSY_RX_LISTEN)
            {
                hperh->pre_state = ALD_I2C_STATE_SLAVE_BUSY_RX;
                hperh->state     = ALD_I2C_STATE_LISTEN;
                hperh->mode      = ALD_I2C_MODE_NONE;

                if (hperh->slave_rx_cplt_cbk != NULL)
                    hperh->slave_rx_cplt_cbk(hperh);
            }
            if (hperh->state == ALD_I2C_STATE_LISTEN)
            {
                hperh->xfer_opt  = ALD_I2C_NO_OPTION_FRAME;
                hperh->pre_state = ALD_I2C_STATE_NONE;
                hperh->state     = ALD_I2C_STATE_READY;
                hperh->mode      = ALD_I2C_MODE_NONE;

                if (hperh->listen_cplt_cbk != NULL)
                    hperh->listen_cplt_cbk(hperh);
            }
        }
    }
}


/**
  * @brief  This function handles I2C error interrupt request.
  * @param  hperh: pointer to a i2c_handle_t structure that contains
  *         the configuration information for I2C module
  * @retval  NONE
  */
void ald_i2c_seq_er_irq_handler(ald_i2c_handle_t *hperh)
{
    /**< Transmit overrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXOV) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXOV);
        hperh->error_code |= ALD_I2C_ERROR_TOV;
    }
    /**< Transmit underrun */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TXUD) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TXUD);
        hperh->error_code |= ALD_I2C_ERROR_TUD;
    }

    /**< Receive overrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXOV) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXOV);
        hperh->error_code |= ALD_I2C_ERROR_ROV;
    }

    /**< Receive underrun interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_RXUD) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_RXUD);
        hperh->error_code |= ALD_I2C_ERROR_RUD;
    }

    /**< NACK interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_NACK) == SET)
    {
        ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK);
        if ((hperh->mode == ALD_I2C_MODE_SLAVE) && (hperh->xfer_count == hperh->xfer_size) && \
            ((hperh->state == ALD_I2C_STATE_BUSY_TX) || (hperh->state == ALD_I2C_STATE_BUSY_TX_LISTEN) || \
            ((hperh->state == ALD_I2C_STATE_LISTEN) && (hperh->pre_state == ALD_I2C_STATE_SLAVE_BUSY_TX)))) {
                if (((hperh->xfer_opt == ALD_I2C_FIRST_AND_LAST_FRAME) || (hperh->xfer_opt == ALD_I2C_LAST_FRAME)) && \
                    (hperh->state == ALD_I2C_STATE_LISTEN)) {
                    hperh->pre_state = ALD_I2C_STATE_NONE;
                    hperh->state     = ALD_I2C_STATE_READY;
                    hperh->mode      = ALD_I2C_MODE_NONE;

                    if (hperh->listen_cplt_cbk != NULL)
                        hperh->listen_cplt_cbk(hperh);

                }
                else if (hperh->state == ALD_I2C_STATE_BUSY_TX)
                {
                    hperh->xfer_opt  = ALD_I2C_NO_OPTION_FRAME;
                    hperh->pre_state = ALD_I2C_STATE_SLAVE_BUSY_TX;
                    hperh->state     = ALD_I2C_STATE_READY;
                    hperh->mode      = ALD_I2C_MODE_NONE;

                    if (hperh->slave_tx_cplt_cbk != NULL)
                        hperh->slave_tx_cplt_cbk(hperh);
                }
        }
        else
        {
            hperh->error_code |= ALD_I2C_ERROR_AF;
            if (hperh->mode == ALD_I2C_MODE_MASTER)
                SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
        }

        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_NACK);
    }

    /**< Bus error interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_BERR) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_BERR);
        hperh->state |= ALD_I2C_ERROR_BERR;
    }

    /**< Arbitration loss interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ARLO) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ARLO);
        hperh->state |= ALD_I2C_ERROR_ARLO;
    }

    /**< PEC error interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_PECE) == SET)
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_PECE);

    /**< Timeout interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_TOUT) == SET)
    {
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TOUT);
        hperh->state |= ALD_I2C_ERROR_TIMEOUT;
    }

    /**< SMBus Alert interrupt */
    if (ald_i2c_get_mask_flag_status(hperh, ALD_I2C_IT_ALERT) == SET)
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_ALERT);

    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode  = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_callback)
        hperh->error_callback(hperh);
}

/**
  * @brief  Enable/disable the specified I2C interrupts.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the i2c interrupt sources to be enabled or disabled.
  * @param  state: New state of the specified I2C interrupts.
  *         This parameter can be:
  *             @arg ENABLE
  *             @arg DISABLE
  * @retval None
  */
void ald_i2c_interrupt_config(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t it, type_func_t state)
{
    assert_param(IS_I2C_TYPE(hperh->perh));
    assert_param(IS_I2C_IT(it));
    assert_param(IS_FUNC_STATE(state));

    if (state == ENABLE)
        hperh->perh->IER = it;
    else
        hperh->perh->IDR = it;

    return;
}

/**
  * @brief  Get the status of I2C interrupt source.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  it: Specifies the I2C interrupt source.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
it_status_t ald_i2c_get_it_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t it)
{
    it_status_t status = RESET;

    assert_param(IS_I2C_TYPE(hperh->perh));
    assert_param(IS_I2C_IT(it));

    if (hperh->perh->IVS & it)
        status = SET;

    return status;
}

/**
  * @brief  Get the status of I2C interrupt flag.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag)
{
    assert_param(IS_I2C_TYPE(hperh->perh));
    assert_param(IS_I2C_IT(flag));

    if (hperh->perh->RIF & flag)
        return SET;

    return RESET;
}


/**
  * @brief  Get the status of interrupt flag and interupt source.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  *         This parameter can be one of the @ref i2c_interrupt_t.
  * @retval Status:
  *           - 0: RESET
  *           - 1: SET
  */
flag_status_t ald_i2c_get_mask_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag)
{
    assert_param(IS_I2C_TYPE(hperh->perh));
    assert_param(IS_I2C_IT(flag));

    if (hperh->perh->IFM & flag)
        return SET;

    return RESET;
}

/**
  * @brief  Clear the I2C interrupt flag.
  * @param  hperh: Pointer to a i2c_handle_t structure.
  * @param  flag: Specifies the I2C interrupt flag.
  * @retval None
  */
void ald_i2c_clear_flag_status(ald_i2c_handle_t *hperh, ald_i2c_interrupt_t flag)
{
    assert_param(IS_I2C_TYPE(hperh->perh));
    assert_param(IS_I2C_IT(flag));

    hperh->perh->ICR = flag;
    return;
}

/**
 * @}
 */

/** @addtogroup I2C_Private_Functions
 * @{
 */

/**
 * @brief  Handle transmit complete flag for Master Transmit mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_send_tc(ald_i2c_handle_t *hperh)
{
    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_TXE | ALD_I2C_IT_NACK | ALD_I2C_IT_TC | ALD_I2C_IT_TCR);

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == RESET)
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

    __UNLOCK(hperh);
    hperh->state = ALD_I2C_STATE_READY;

    if (hperh->mode == ALD_I2C_MODE_MEM)
    {
        if (hperh->mem_tx_cplt_cbk)
            hperh->mem_tx_cplt_cbk(hperh);
    }
    else
    {
        if (hperh->master_tx_cplt_cbk)
            hperh->master_tx_cplt_cbk(hperh);
    }

    return ALD_OK;
}

/**
 * @brief  Handle transmit empty flag for Master Transmit mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_send_txe(ald_i2c_handle_t *hperh)
{
    if (hperh->xfer_count != hperh->xfer_size)
    {
        hperh->perh->TXDATA = (*hperh->p_buff++);
        hperh->xfer_count++;
    }

    return ALD_OK;
}

/**
 * @brief  Handle receive complete for Master Receive mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_recv_tc(ald_i2c_handle_t *hperh)
{
    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_RXNE | ALD_I2C_IT_TCR | ALD_I2C_IT_TC);

    if (READ_BIT(hperh->perh->CON2, I2C_CON2_AUTOEND_MSK) == RESET)
        SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);

    __UNLOCK(hperh);
    hperh->state = ALD_I2C_STATE_READY;

    if (hperh->mode == ALD_I2C_MODE_MEM)
    {
        if (hperh->mem_rx_cplt_cbk)
            hperh->mem_rx_cplt_cbk(hperh);
    }
    else
    {
        if (hperh->master_rx_cplt_cbk)
            hperh->master_rx_cplt_cbk(hperh);
    }

    return ALD_OK;
}

/**
 * @brief  Handle receive not empty for Master Receive mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_recv_rxne(ald_i2c_handle_t *hperh)
{
    if (hperh->xfer_size - hperh->xfer_count > 0)
    {
        (*hperh->p_buff++) = hperh->perh->RXDATA;
        hperh->xfer_count++;
    }
    else
    {
        return ALD_OK;
    }

    return ALD_OK;
}

/**
 * @brief  Handle TXE flag for Slave Transmit mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_slave_send_txe(ald_i2c_handle_t *hperh)
{
    if (hperh->xfer_size > hperh->xfer_count)
    {
        hperh->perh->TXDATA = (*hperh->p_buff++);
        hperh->xfer_count++;
    }

    return ALD_OK;
}

/**
 * @brief  Handle RXNE flag for Slave Receive mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_slave_recv_rxne(ald_i2c_handle_t *hperh)
{
    if (hperh->xfer_size > hperh->xfer_count)
    {
        (*hperh->p_buff++) = hperh->perh->RXDATA;
        hperh->xfer_count++;
    }
    else
    {
        return ALD_OK;
    }

    return ALD_OK;
}

/**
 * @brief  Handle STOPF flag for Slave mode
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_slave_stopf(ald_i2c_handle_t *hperh)
{
    ALD_I2C_DISABLE_IT(hperh, ALD_I2C_IT_ADDR | ALD_I2C_IT_NACK | ALD_I2C_IT_RXNE | ALD_I2C_IT_TXE | ALD_I2C_IT_STOP);

    hperh->mode       = ALD_I2C_MODE_NONE;
    hperh->error_code = ALD_I2C_ERROR_NONE;
    __UNLOCK(hperh);

    if (hperh->state == ALD_I2C_STATE_BUSY_TX)
    {
        hperh->state = ALD_I2C_STATE_READY;
        if ((hperh->slave_tx_cplt_cbk) && (hperh->xfer_count != 0))
            hperh->slave_tx_cplt_cbk(hperh);
    }
    else if (hperh->state == ALD_I2C_STATE_BUSY_RX)
    {
        hperh->state = ALD_I2C_STATE_READY;
        if ((hperh->slave_rx_cplt_cbk) && (hperh->xfer_count != 0))
            hperh->slave_rx_cplt_cbk(hperh);
    }

    return ALD_OK;
}

/**
 * @brief  Master sends target device address followed by internal memory address for write request.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_req_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout)
{
    if (hperh->init.addr_mode == ALD_I2C_ADDR_7BIT)
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
    else
        SET_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_SADD_MSK, dev_addr << I2C_CON2_SADD_POSS);
    CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);

    return ALD_OK;
}

/**
 * @brief  Master sends target device address followed by internal memory address for read request.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_master_req_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint32_t timeout)
{
    if (hperh->init.addr_mode == ALD_I2C_ADDR_7BIT)
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);
    else
        SET_BIT(hperh->perh->CON2, I2C_CON2_ADD10_MSK);

    MODIFY_REG(hperh->perh->CON2, I2C_CON2_SADD_MSK, dev_addr << I2C_CON2_SADD_POSS);
    SET_BIT(hperh->perh->CON2, I2C_CON2_RD_WRN_MSK);

    return ALD_OK;
}

/**
 * @brief  Master sends target device address followed by internal memory address for write request.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  mem_addr: Internal memory address
 * @param  add_size: size of internal memory address
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_req_mem_write(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, uint16_t add_size, uint32_t timeout)
{
    uint32_t tmp = hperh->perh->CON2;
    i2c_master_req_write(hperh, dev_addr, timeout);
    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    if (add_size == ALD_I2C_MEMADD_SIZE_8BIT)
    {
        hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
    }
    else
    {
        hperh->perh->TXDATA = I2C_MEM_ADD_MSB(mem_addr);

        if (i2c_wait_txe_to_timeout(hperh, timeout) != ALD_OK)
            return ALD_ERROR;

        hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
    }

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TCR, RESET, timeout) != ALD_OK)
    {
        CLEAR_BIT(hperh->perh->CON2, I2C_CON2_RELOAD_MSK);
        ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TCR);
        return ALD_ERROR;
    }

    ald_i2c_clear_flag_status(hperh, ALD_I2C_IT_TCR);

    if ((hperh->state == ALD_I2C_STATE_BUSY_RX) && (hperh->mode == ALD_I2C_MODE_MEM))
    {
        tmp = hperh->perh->CON2;
        tmp &= ~(I2C_CON2_RELOAD_MSK | I2C_CON2_NBYTES_MSK);
        hperh->perh->CON2 = tmp;

        tmp = hperh->perh->CON1;
        tmp &= ~I2C_CON1_NBYTES_MSK;
        hperh->perh->CON1 = tmp;
    }

    return ALD_OK;
}

/**
 * @brief  Master sends target device address followed by internal memory address for read request.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  dev_addr: Target device address
 * @param  mem_addr: Internal memory address
 * @param  add_size: size of internal memory address
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_req_mem_read(ald_i2c_handle_t *hperh, uint16_t dev_addr, uint16_t mem_addr, uint16_t add_size, uint32_t timeout)
{
    uint32_t tim_count = 0;

    if (i2c_master_req_write(hperh, dev_addr, timeout) != ALD_OK)
    {
        __UNLOCK(hperh);
        return ALD_ERROR;
    }

    SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);

    if (add_size == ALD_I2C_MEMADD_SIZE_8BIT)
    {
        hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
    }
    else
    {
        hperh->perh->TXDATA = I2C_MEM_ADD_MSB(mem_addr);

        if (i2c_wait_txe_to_timeout(hperh, timeout) != ALD_OK)
        {
            if (hperh->error_code == ALD_I2C_ERROR_AF)
            {
                SET_BIT(hperh->perh->CON2, I2C_CON2_START_MSK);
                return ALD_ERROR;
            }
            else
            {
                return ALD_TIMEOUT;
            }
        }

        hperh->perh->TXDATA = I2C_MEM_ADD_LSB(mem_addr);
    }

    while (!ALD_I2C_GET_FLAG(hperh, ALD_I2C_STAT_TXE))
    {
        tim_count++;

        if (tim_count > 0xFFFF)
            return ALD_TIMEOUT;
    }

    return ALD_OK;
}

/**
* @brief  DMA I2C master transmit process complete callback.
* @param  argv: I2C handle
* @retval None
*/
static void i2c_dma_master_send_cplt(void *argv)
{
    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == ALD_ERROR)
        hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->master_tx_cplt_cbk)
            hperh->master_tx_cplt_cbk(hperh);
    }
}

/**
 * @brief  DMA I2C slave transmit process complete callback.
 * @param  argv: I2C handle
 * @retval None
 */
static void i2c_dma_slave_send_cplt(void *argv)
{
    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->slave_tx_cplt_cbk)
            hperh->slave_tx_cplt_cbk(hperh);
    }
}

/**
 * @brief  DMA I2C master receive process complete callback
 * @param  argv: I2C handle
 * @retval None
 */
static void i2c_dma_master_recv_cplt(void *argv)
{
    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    if (i2c_wait_flag_change_to_timeout(hperh, ALD_I2C_STAT_TC, RESET, I2C_TIMEOUT_FLAG) == ALD_ERROR)
        hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->master_rx_cplt_cbk)
            hperh->master_rx_cplt_cbk(hperh);
    }
}

/**
 * @brief  DMA I2C slave receive process complete callback.
 * @param  argv: I2C handle
 * @retval None
 */
static void i2c_dma_slave_recv_cplt(void *argv)
{
    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->slave_rx_cplt_cbk)
            hperh->slave_rx_cplt_cbk(hperh);
    }
}

/**
 * @brief  DMA I2C Memory Write process complete callback
 * @param  argv: I2C handle
 * @retval None
 */
static void i2c_dma_mem_send_cplt(void *argv)
{
    uint32_t cnt = 0xFFFFFF;

    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    while (cnt--)
    {
        if ((hperh->perh->STAT & ALD_I2C_STAT_TC) != 0)
            break;
    }

    if (cnt == 0)
        hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_TXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state      = ALD_I2C_STATE_READY;
    hperh->mode       = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->mem_tx_cplt_cbk)
            hperh->mem_tx_cplt_cbk(hperh);
    }
}

/**
 * @brief  DMA I2C Memory Read process complete callback
 * @param  argv: I2C handle
 * @retval None
 */
static void i2c_dma_mem_recv_cplt(void *argv)
{
    uint32_t cnt = 0xFFFFF;

    ald_i2c_handle_t* hperh = (ald_i2c_handle_t*)argv;

    while (cnt--)
    {
        if ((hperh->perh->STAT & ALD_I2C_STAT_TC) != 0)
            break;
    }

    if (cnt == 0)
        hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;

    SET_BIT(hperh->perh->CON2, I2C_CON2_STOP_MSK);
    CLEAR_BIT(hperh->perh->CON1, I2C_CON1_RXDMAEN_MSK);

    hperh->xfer_count = 0;
    hperh->state = ALD_I2C_STATE_READY;
    hperh->mode = ALD_I2C_MODE_NONE;
    __UNLOCK(hperh);

    if (hperh->error_code != ALD_I2C_ERROR_NONE)
    {
        if (hperh->error_callback)
            hperh->error_callback(hperh);
    }
    else
    {
        if (hperh->mem_rx_cplt_cbk)
            hperh->mem_rx_cplt_cbk(hperh);
    }
}

/**
 * @brief  This function handles I2C Communication timeout.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  flag: specifies the I2C flag to check.
 * @param  status: The checked flag status (SET or RESET).
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_wait_flag_change_to_timeout(ald_i2c_handle_t *hperh, uint32_t flag, flag_status_t status, uint32_t timeout)
{
    uint32_t tickstart = 0;

    tickstart = ald_get_tick();
    if (status == RESET)
    {
        while (ALD_I2C_GET_FLAG(hperh, flag) == RESET)
        {
            if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout))
            {
                hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;
                return ALD_TIMEOUT;
            }
        }
    }
    else
    {
        while (ALD_I2C_GET_FLAG(hperh, flag) != RESET)
        {
            if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout))
            {
                hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;
                return ALD_TIMEOUT;
            }
        }
    }

    return ALD_OK;
}

/**
 * @brief  This function handles I2C Communication timeout for Master addressing phase.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  flag: specifies the I2C flag to check.
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_wait_master_addr_to_timeout(ald_i2c_handle_t *hperh, uint32_t flag, uint32_t timeout)
{
    uint32_t tickstart = ald_get_tick();

    while (ALD_I2C_GET_IT_FLAG(hperh, flag) == RESET)
    {
        if ((timeout == 0) || ((ald_get_tick() - tickstart ) > timeout))
        {
            hperh->error_code = ALD_I2C_ERROR_TIMEOUT;

            return ALD_ERROR;
        }
    }

    return ALD_OK;
}

/**
 * @brief  This function handles I2C Communication timeout for specific usage of TXE flag.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  timeout: Timeout duration
 * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_wait_txe_to_timeout(ald_i2c_handle_t *hperh, uint32_t timeout)
{
    uint32_t tickstart = ald_get_tick();

    while (ALD_I2C_GET_FLAG(hperh, ALD_I2C_STAT_TXE) == RESET)
    {
        if (ALD_I2C_GET_IT_FLAG(hperh, ALD_I2C_IT_ARLO))
        {
            hperh->error_code |= ALD_I2C_ERROR_ARLO;
            return ALD_ERROR;
        }

        if (ALD_I2C_GET_IT_FLAG(hperh, ALD_I2C_IT_NACK) == SET)
        {
            hperh->error_code |= ALD_I2C_ERROR_AF;
            return ALD_ERROR;
        }

        if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout))
        {
            hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;
            return ALD_ERROR;
        }
    }

    return ALD_OK;
}

/**
 * @brief  This function handles I2C Communication timeout for specific usage of RXNE flag.
 * @param  hperh: Pointer to a i2c_handle_t structure that contains
 *                the configuration information for the specified I2C.
 * @param  timeout: Timeout duration
  * @retval Status, see @ref ald_status_t.
 */
static ald_status_t i2c_wait_rxne_to_timeout(ald_i2c_handle_t *hperh, uint32_t timeout)
{
    uint32_t tickstart = ald_get_tick();

    while (ALD_I2C_GET_FLAG(hperh, ALD_I2C_STAT_RXNE) == RESET)
    {
        if ((timeout == 0) || ((ald_get_tick() - tickstart) > timeout))
        {
            hperh->error_code |= ALD_I2C_ERROR_TIMEOUT;
            return ALD_ERROR;
        }
    }

    return ALD_OK;
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
