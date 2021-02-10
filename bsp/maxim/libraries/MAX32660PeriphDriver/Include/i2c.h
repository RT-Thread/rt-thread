/**
 * @file    i2c.h
 * @brief   Inter-integrated circuit (I2C) communications interface driver.
 */

/* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2019-06-28 09:42:42 -0500 (Fri, 28 Jun 2019) $
 * $Revision: 44330 $
 *
 *************************************************************************** */

#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>
#include "i2c_regs.h"
#include "mxc_sys.h"

/**
 * @defgroup i2c I2C
 * @ingroup periphlibs
 * @{
 */

/***** Definitions *****/

/// @brief I2C Speed Modes
typedef enum {
    I2C_STD_MODE        = 100000,       //!< 100KHz Bus Speed 
    I2C_FAST_MODE       = 400000,       //!< 400KHz Bus Speed 
    I2C_FASTPLUS_MODE   = 1000000,      //!< 1MHz   Bus Speed
    I2C_HS_MODE         = 3400000       //!< 3.4MHz Bus Speed 
} i2c_speed_t;

//State for Master
typedef enum {
    I2C_STATE_READING = 0,
    I2C_STATE_WRITING = 1
} i2c_state_t;

// @brief Enable/Disable TXFIFO Autoflush mode
typedef enum {
    I2C_AUTOFLUSH_ENABLE   = 0,
    I2C_AUTOFLUSH_DISABLE  = 1 
} i2c_autoflush_disable_t;

// @brief I2C Transaction request.
typedef struct i2c_req i2c_req_t;
struct i2c_req {

    uint8_t addr;                  /**< @parblock I2C 7-bit Address left aligned, bit 7 to bit 1.
                                     *     Only supports 7-bit addressing. LSb of the given address
                                     *     will be used as the read/write bit, the @p addr <b>will 
                                     *     not be shifted</b>. Used for <em>both master</em> and 
                                     *     @em slave transactions. @endparblock
                                     */
    const uint8_t *tx_data;          ///< Data for mater write/slave read.
    uint8_t *rx_data;                ///< Data for master read/slave write.
    unsigned tx_len;                 ///< Length of tx data.
    unsigned rx_len;                 ///< Length of rx.
    unsigned tx_num;                 ///< Number of tx bytes sent.
    unsigned rx_num;                 ///< Number of rx bytes sent.
    i2c_state_t state;               ///< Read or Write.

    /**
     * @details     0 to send a stop bit at the end of the transaction, 
                    otherwise send a restart. Only used in master trasnactions.
     */
    int restart;                   /**< @parblock Restart or stop bit indicator. 
                                     *    @arg 0 to send a stop bit at the end of the transaction
                                     *    @arg Non-zero to send a restart at end of the transaction
                                     *    @note Only used for Master transactions.
                                     *    @endparblock
                                     */ 
    i2c_autoflush_disable_t sw_autoflush_disable;       ///< Enable/Disable autoflush.

    /**
     * @brief   Callback for asynchronous request.
     * @param   i2c_req_t*  Pointer to the transaction request.
     * @param   int         Error code.
     */
    void (*callback)(i2c_req_t*, int);
};

/***** Function Prototypes *****/

/**
 * @brief   Initialize and enable I2C.
 * @param      i2c     Pointer to I2C peripheral registers.
 * @param      i2cspeed desired speed (I2C mode)
 * @param      sys_cfg System configuration object
 * @returns \c #E_NO_ERROR if everything is successful, 
 *             @ref MXC_Error_Codes if an error occurred.
 */
int I2C_Init(mxc_i2c_regs_t * i2c, i2c_speed_t i2cspeed, const sys_cfg_i2c_t* sys_cfg);

/**
 * @brief   Shutdown I2C module.
 * @param   i2c    Pointer to the I2C registers.
 * @returns #E_NO_ERROR I2C shutdown successfully, @ref MXC_Error_Codes "error" if
 *             unsuccessful.
 */
int I2C_Shutdown(mxc_i2c_regs_t *i2c);

/**
 * @brief   Master write data. Will block until transaction is complete.
 * @param   i2c         Pointer to I2C regs.
 * @param   addr        @parblock I2C 7-bit Address left aligned, bit 7 to bit 1.
 *                          Only supports 7-bit addressing. LSb of the given address
 *                          will be used as the read/write bit, the \p addr <b>will 
 *                          not be shifted</b>. Used for <em>both master</em> and 
 *                          @em slave transactions.    @endparblock                                 
 * @param   data        Data to be written.
 * @param   len         Number of bytes to Write.
 * @param   restart     0 to send a stop bit at the end of the transaction, 
                        otherwise send a restart.
 * @returns Bytes transacted if everything is successful, 
 *              @ref MXC_Error_Codes if an error occurred.
 */
int I2C_MasterWrite(mxc_i2c_regs_t *i2c, uint8_t addr, const uint8_t* data, int len, int restart);

/**
 * @brief   Master read data. Will block until transaction is complete.
 * @param   i2c         Pointer to I2C regs.
 * @param   addr        @parblock I2C 7-bit Address left aligned, bit 7 to bit 1.
 *                          Only supports 7-bit addressing. LSb of the given address
 *                          will be used as the read/write bit, the @p addr <b>will 
 *                          not be shifted</b>. Used for <em>both master</em> and 
 *                          @em slave transactions.  @endparblock
 * @param   data        Data to be written.
 * @param   len         Number of bytes to Write.
 * @param   restart     0 to send a stop bit at the end of the transaction, 
                        otherwise send a restart.
 * @returns Bytes transacted if everything is successful, @ref MXC_Error_Codes if an error occurred.
 */
int I2C_MasterRead(mxc_i2c_regs_t *i2c, uint8_t addr, uint8_t* data, int len, int restart);

/**
 * @brief   Slave read data. Will block until transaction is complete.
 * @param   i2c         Pointer to I2C regs.
 * @param   addr        @parblock I2C 7-bit Address left aligned, bit 7 to bit 1.
 *                          Only supports 7-bit addressing. LSb of the given address
 *                          will be used as the read/write bit, the @p addr <b>will 
 *                          not be shifted</b>. Used for <em>both master</em> and 
 *                          @em slave transactions.  @endparblock
 * @param   read_data   Buffer that the master will read from.
 * @param   read_len    Number of bytes the master can read.
 * @param   write_data  Buffer that the master will write to.
 * @param   write_len   Number of bytes the master can write.
 * @param   tx_num      Number of bytes transmitted by the slave.
 * @param   rx_num      Number of bytes received by the slave.
 * @param   sw_autoflush_disable      TX Autoflush enabled by default.Set this bit to disable autoflush manually.
 * @returns #E_NO_ERROR if everything is successful, @ref MXC_Error_Codes if an error occurred.
 */
int I2C_Slave(mxc_i2c_regs_t *i2c, uint8_t addr, const uint8_t* read_data, 
              int read_len, uint8_t* write_data, int write_len, int* tx_num, 
              int* rx_num, i2c_autoflush_disable_t sw_autoflush_disable);

/**
 * @brief   Master Read and Write Asynchronous.
 * @param   i2c         Pointer to I2C regs.
 * @param   req         Request for an I2C transaction.
 * @returns #E_NO_ERROR if everything is successful, @ref MXC_Error_Codes if an error occurred.
 */
int I2C_MasterAsync(mxc_i2c_regs_t *i2c, i2c_req_t *req);

/**
 * @brief   Slave Read and Write Asynchronous.
 * @param   i2c         Pointer to I2C regs.
 * @param   req         Request for an I2C transaction.
 * @returns #E_NO_ERROR if everything is successful, @ref MXC_Error_Codes if an error occurred.
 */
int I2C_SlaveAsync(mxc_i2c_regs_t *i2c, i2c_req_t *req);
/**
 * @brief   I2C interrupt handler.
 * @details This function should be called by the application from the interrupt
 *          handler if I2C interrupts are enabled. Alternately, this function
 *          can be periodically called by the application if I2C interrupts are
 *          disabled.
 * @param   i2c         Base address of the I2C module.
 */
void I2C_Handler(mxc_i2c_regs_t *i2c);

/**
 * @brief   Drain all of the data in the RXFIFO.
 * @param   i2c     Pointer to I2C regs.
 */
void I2C_DrainRX(mxc_i2c_regs_t *i2c);

/**
 * @brief   Drain all of the data in the TXFIFO.
 * @param   i2c     Pointer to I2C regs.
 */
void I2C_DrainTX(mxc_i2c_regs_t *i2c);

/**
 * @brief   Abort Async request based on the request you want to abort.
 * @param   req     Pointer to I2C Transaction.
 */
int I2C_AbortAsync(i2c_req_t *req);

/**
 * @brief      Enable and Set Timeout 
 *
 * @param      i2c   pointer to I2C regs
 * @param[in]  us    micro seconds to delay
 *
 * @return     E_NO_ERROR or E_BAD_PARAM if delay is to long.
 */
int I2C_SetTimeout(mxc_i2c_regs_t *i2c, int us);

/**
 * @brief      clear and disable timeout
 *
 * @param      i2c   pointer to I2C regs
 */
void I2C_ClearTimeout(mxc_i2c_regs_t *i2c);

/**@} end of group i2c */
#endif /* _I2C_H_ */
