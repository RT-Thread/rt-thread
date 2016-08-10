/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#if !defined(__FSL_I2C_HAL_H__)
#define __FSL_I2C_HAL_H__

#include <assert.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup i2c_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief I2C status return codes.*/
typedef enum _i2c_status {
    kStatus_I2C_Success            = 0x0U,  /*!< I2C operation has no error. */
    kStatus_I2C_Initialized        = 0x1U,  /*!< Current I2C is already initialized by one task.*/
    kStatus_I2C_Fail               = 0x2U,  /*!< I2C operation failed. */
    kStatus_I2C_Busy               = 0x3U,  /*!< The master is already performing a transfer.*/
    kStatus_I2C_Timeout            = 0x4U,  /*!< The transfer timed out.*/
    kStatus_I2C_ReceivedNak        = 0x5U,  /*!< The slave device sent a NAK in response to a byte.*/
    kStatus_I2C_SlaveTxUnderrun    = 0x6U,  /*!< I2C Slave TX Underrun error.*/
    kStatus_I2C_SlaveRxOverrun     = 0x7U,  /*!< I2C Slave RX Overrun error.*/
    kStatus_I2C_AribtrationLost    = 0x8U,  /*!< I2C Arbitration Lost error.*/
    kStatus_I2C_StopSignalFail     = 0x9U,  /*!< I2C STOP signal could not release bus. */
    kStatus_I2C_Idle               = 0xAU, /*!< I2C Slave Bus is Idle. */
    kStatus_I2C_NoReceiveInProgress= 0xBU, /*!< Attempt to abort a receiving when no transfer
                                                was in progress */
    kStatus_I2C_NoSendInProgress   = 0xCU /*!< Attempt to abort a sending when no transfer
                                                was in progress */
} i2c_status_t;

/*! @brief I2C status flags. */
typedef enum _i2c_status_flag {
    kI2CTransferComplete = I2C_S_TCF_SHIFT,
    kI2CAddressAsSlave   = I2C_S_IAAS_SHIFT,
    kI2CBusBusy          = I2C_S_BUSY_SHIFT,
    kI2CArbitrationLost  = I2C_S_ARBL_SHIFT,
    kI2CAddressMatch     = I2C_S_RAM_SHIFT,
    kI2CSlaveTransmit    = I2C_S_SRW_SHIFT,
    kI2CInterruptPending = I2C_S_IICIF_SHIFT,
    kI2CReceivedNak      = I2C_S_RXAK_SHIFT 
} i2c_status_flag_t;

/*! @brief Direction of master and slave transfers.*/
typedef enum _i2c_direction {
    kI2CReceive = 0U,   /*!< Master transmit, slave receive.*/
    kI2CSend    = 1U    /*!< Master receive, slave transmit.*/
} i2c_direction_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Module controls
 * @{
 */

/*!
 * @brief Restores the I2C peripheral to reset state.
 *
 * @param base The I2C peripheral base pointer
 */
void I2C_HAL_Init(I2C_Type * base);

/*!
 * @brief Enables the I2C module operation.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_Enable(I2C_Type * base)
{
    I2C_BWR_C1_IICEN(base, 0x1U);
}

/*!
 * @brief Disables the I2C module operation.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_Disable(I2C_Type * base)
{
    I2C_BWR_C1_IICEN(base, 0x0U);
}

/*@}*/

#if FSL_FEATURE_I2C_HAS_DMA_SUPPORT
/*!
 * @name DMA
 * @{
 */

/*!
 * @brief Enables or disables the DMA support.
 *
 * @param base The I2C peripheral base pointer
 * @param enable Pass true to enable DMA transfer signalling
 */
static inline void I2C_HAL_SetDmaCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C1_DMAEN(base, (uint8_t)enable);
}

/*!
 * @brief Returns whether I2C DMA support is enabled.
 *
 * @param base The I2C peripheral base pointer.
 * @return Whether I2C DMA is enabled or not.
 */
static inline bool I2C_HAL_GetDmaCmd(I2C_Type * base)
{
    return I2C_BRD_C1_DMAEN(base);
}

/*@}*/
#endif /* FSL_FEATURE_I2C_HAS_DMA_SUPPORT */

/*!
 * @name Pin functions
 * @{
 */

#if FSL_FEATURE_I2C_HAS_HIGH_DRIVE_SELECTION 
/*!
 * @brief Controls the drive capability of the I2C pads.
 *
 * @param base The I2C peripheral base pointer
 * @param enable Passing true will enable high drive mode of the I2C pads. False sets normal
 *     drive mode.
 */
static inline void I2C_HAL_SetHighDriveCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C2_HDRS(base, (uint8_t)enable);
}
#endif /* FSL_FEATURE_I2C_HAS_HIGH_DRIVE_SELECTION */

/*!
 * @brief Controls the width of the programmable glitch filter.
 *
 * Controls the width of the glitch, in terms of bus clock cycles, that the filter must absorb.
 * The filter does not allow any glitch whose size is less than or equal to this width setting, 
 * to pass.
 *
 * @param base The I2C peripheral base pointer
 * @param glitchWidth Maximum width in bus clock cycles of the glitches that is filtered.
 *     Pass zero to disable the glitch filter.
 */
static inline void I2C_HAL_SetGlitchWidth(I2C_Type * base, uint8_t glitchWidth)
{
    assert(glitchWidth < FSL_FEATURE_I2C_MAX_GLITCH_FILTER_WIDTH);
    I2C_BWR_FLT_FLT(base, glitchWidth);
}

/*@}*/

/*!
 * @name Low power
 * @{
 */

/*!
 * @brief Controls the I2C wakeup enable.
 *
 * The I2C module can wake the MCU from low power mode with no peripheral bus running when
 * slave address matching occurs. 
 *
 * @param base The I2C peripheral base pointer.
 * @param enable true - Enables the wakeup function in low power mode.<br>
 *     false - Normal operation. No interrupt is  generated when address matching in
 *     low power mode.
 */
static inline void I2C_HAL_SetWakeupCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C1_WUEN(base, (uint8_t)enable);
}

#if FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF
/*!
 * @brief Controls the stop mode hold off.
 *
 * This function lets you enable the hold off entry to low power stop mode when any data transmission
 * or reception is occurring.
 *
 * @param base The I2C peripheral base pointer
 * @param enable false - Stop hold off is disabled. The MCU's entry to stop mode is not gated.<br>
 *     true - Stop hold off is enabled.
 */

static inline void I2C_HAL_SetStopHoldoffCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_FLT_SHEN(base, (uint8_t)enable);
}
#endif /* FSL_FEATURE_I2C_HAS_STOP_HOLD_OFF*/

/*@}*/

/*!
 * @name Baud rate
 * @{
 */

/*!
 * @brief Sets the I2C bus frequency for master transactions.
 *
 * @param base The I2C peripheral base pointer
 * @param sourceClockInHz I2C source input clock in Hertz
 * @param kbps Requested bus frequency in kilohertz. Common values are either 100 or 400.
 * @param absoluteError_Hz If this parameter is not NULL, it is filled in with the
 *     difference in Hertz between the requested bus frequency and the closest frequency
 *     possible given available divider values.
 */
void I2C_HAL_SetBaudRate(I2C_Type * base,
                         uint32_t sourceClockInHz,
                         uint32_t kbps,
                         uint32_t * absoluteError_Hz);

/*!
 * @brief Sets the I2C baud rate multiplier and table entry.
 *
 * Use this function to set the I2C bus frequency register values directly, if they are
 * known in advance.
 *
 * @param base The I2C peripheral base pointer
 * @param mult Value of the MULT bitfield, ranging from 0-2. 
 * @param icr The ICR bitfield value, which is the index into an internal table in the I2C
 *     hardware that selects the baud rate divisor and SCL hold time.
 */
static inline void I2C_HAL_SetFreqDiv(I2C_Type * base, uint8_t mult, uint8_t icr)
{
    I2C_WR_F(base, I2C_F_MULT(mult) | I2C_F_ICR(icr));
}

/*!
 * @brief Slave baud rate control
 *
 * Enables an independent slave mode baud rate at the maximum frequency. This forces clock stretching
 * on the SCL in very fast I2C modes.
 *
 * @param base The I2C peripheral base pointer
 * @param enable true - Slave baud rate is independent of the master baud rate;<br>
 *     false - The slave baud rate follows the master baud rate and clock stretching may occur.
 */
static inline void I2C_HAL_SetSlaveBaudCtrlCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C2_SBRC(base, (uint8_t)enable);
}

/*@}*/

/*!
 * @name Bus operations
 * @{
 */

/*!
 * @brief Sends a START or a Repeated START signal on the I2C bus.
 *
 * This function is used to initiate a new master mode transfer by sending the START signal. It
 * is also used to send a Repeated START signal when a transfer is already in progress.
 *
 * @param base The I2C peripheral base pointer
 */
void I2C_HAL_SendStart(I2C_Type * base);

/*!
 * @brief Sends a STOP signal on the I2C bus.
 *
 * This function changes the direction to receive.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether the sending of STOP single is success or not.
 */
i2c_status_t I2C_HAL_SendStop(I2C_Type * base);

/*!
 * @brief Causes an ACK to be sent on the bus.
 *
 * This function specifies that an ACK signal is sent in response to the next received byte.
 *
 * Note that the behavior of this function is changed when the I2C peripheral is placed in
 * Fast ACK mode. In this case, this function causes an ACK signal to be sent in
 * response to the current byte, rather than the next received byte.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_SendAck(I2C_Type * base)
{
    I2C_BWR_C1_TXAK(base, 0x0U);
}

/*!
 * @brief Causes a NAK to be sent on the bus.
 *
 * This function specifies that a NAK signal is sent in response to the next received byte.
 *
 * Note that the behavior of this function is changed when the I2C peripheral is placed in the
 * Fast ACK mode. In this case, this function causes an NAK signal to be sent in
 * response to the current byte, rather than the next received byte.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_SendNak(I2C_Type * base)
{
    I2C_BWR_C1_TXAK(base, 0x1U);
}

/*!
 * @brief Selects either transmit or receive mode.
 *
 * @param base The I2C peripheral base pointer.
 * @param direction Specifies either transmit mode or receive mode. The valid values are:
 *     - #kI2CTransmit
 *     - #kI2CReceive
 */
static inline void I2C_HAL_SetDirMode(I2C_Type * base, i2c_direction_t direction)
{
    I2C_BWR_C1_TX(base, (uint8_t)direction);
}

/*!
 * @brief Returns the currently selected transmit or receive mode.
 *
 * @param base The I2C peripheral base pointer.
 * @return Current I2C transfer mode.
 * @retval #kI2CTransmit I2C is configured for master or slave transmit mode.
 * @retval #kI2CReceive I2C is configured for master or slave receive mode.
 */
static inline i2c_direction_t I2C_HAL_GetDirMode(I2C_Type * base)
{
    return (i2c_direction_t)I2C_BRD_C1_TX(base);
}

/*@}*/

/*!
 * @name Data transfer
 * @{
 */

/*!
 * @brief Returns the last byte of data read from the bus and initiate another read.
 *
 * In a master receive mode, calling this function initiates receiving  the next byte of data.
 *
 * @param base The I2C peripheral base pointer
 * @return This function returns the last byte received while the I2C module is configured in master
 *     receive or slave receive mode.
 */
static inline uint8_t I2C_HAL_ReadByte(I2C_Type * base)
{
    return I2C_RD_D(base);
}

/*!
 * @brief Writes one byte of data to the I2C bus.
 *
 * When this function is called in the master transmit mode, a data transfer is initiated. In slave
 * mode, the same function is available after an address match occurs.
 *
 * In a master transmit mode, the first byte of data written following the start bit or repeated
 * start bit is used for the address transfer and must consist of the slave address (in bits 7-1)
 * concatenated with the required R/\#W bit (in position bit 0).
 *
 * @param base The I2C peripheral base pointer.
 * @param byte The byte of data to transmit.
 */
static inline void I2C_HAL_WriteByte(I2C_Type * base, uint8_t byte)
{
#if FSL_FEATURE_I2C_HAS_DOUBLE_BUFFERING
    while (!I2C_BRD_S2_EMPTY(base))
    {}
#endif 

    I2C_WR_D(base, byte);
}

/*!
 * @brief Returns the last byte of data read from the bus and initiate another read.
 * It will wait till the transfer is actually completed.
 *
 * @param base The I2C peripheral base pointer
 * @return Returns the last byte received 
 */
uint8_t I2C_HAL_ReadByteBlocking(I2C_Type * base);

/*!
 * @brief Writes one byte of data to the I2C bus and wait till that byte is
 * transfered successfully.
 *
 * @param base The I2C peripheral base pointer.
 * @param byte The byte of data to transmit.
 * @return Whether ACK is received(TRUE) or not(FALSE).
 */
bool I2C_HAL_WriteByteBlocking(I2C_Type * base, uint8_t byte);

/*!
 * @brief Performs a polling receive transaction on the I2C bus.
 *
 * @param base  The I2C peripheral base pointer.
 * @param slaveAddr The slave address to communicate.
 * @param cmdBuff   The pointer to the commands to be transferred.
 * @param cmdSize   The length in bytes of the commands to be transferred.
 * @param rxBuff    The pointer to the data to be transferred.
 * @param rxSize    The length in bytes of the data to be transferred.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_HAL_MasterReceiveDataPolling(I2C_Type * base,
                                              uint16_t slaveAddr,
                                              const uint8_t * cmdBuff,
                                              uint32_t cmdSize,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize);

/*!
 * @brief Performs a polling send transaction on the I2C bus.
 *
 * @param base  The I2C peripheral base pointer.
 * @param slaveAddr The slave address to communicate.
 * @param cmdBuff   The pointer to the commands to be transferred.
 * @param cmdSize   The length in bytes of the commands to be transferred.
 * @param txBuff    The pointer to the data to be transferred.
 * @param txSize    The length in bytes of the data to be transferred.
 * @return Error or success status returned by API.
 */
i2c_status_t I2C_HAL_MasterSendDataPolling(I2C_Type * base,
                                           uint16_t slaveAddr,
                                           const uint8_t * cmdBuff,
                                           uint32_t cmdSize,
                                           const uint8_t * txBuff,
                                           uint32_t txSize);

/*!
* @brief Send out multiple bytes of data using polling method.
*
* @param  base I2C module base pointer.
* @param  txBuff The buffer pointer which saves the data to be sent.
* @param  txSize Size of data to be sent in unit of byte.
* @return Whether the transaction is success or not.
* @retval kStatus_I2C_ReceivedNak if received NACK bit
* @retval Error or success status returned by API.
*/
i2c_status_t I2C_HAL_SlaveSendDataPolling(I2C_Type * base, const uint8_t* txBuff, uint32_t txSize);

/*!
* @brief Receive multiple bytes of data using polling method.
*
* @param  base I2C module base pointer.
* @param  rxBuff The buffer pointer which saves the data to be received.
* @param  rxSize Size of data need to be received in unit of byte.
* @return Error or success status returned by API.
*/
i2c_status_t I2C_HAL_SlaveReceiveDataPolling(I2C_Type * base, uint8_t *rxBuff, uint32_t rxSize);

/*@}*/

/*!
 * @name Slave address
 * @{
 */

/*!
 * @brief Sets the primary 7-bit slave address.
 *
 * @param base The I2C peripheral base pointer
 * @param address The slave address in the upper 7 bits. Bit 0 of this value must be 0.
 */
void I2C_HAL_SetAddress7bit(I2C_Type * base, uint8_t address);

/*!
 * @brief Sets the primary slave address and enables 10-bit address mode.
 *
 * @param base The I2C peripheral base pointer
 * @param address The 10-bit slave address, in bits [10:1] of the value. Bit 0 must be 0.
 */
void I2C_HAL_SetAddress10bit(I2C_Type * base, uint16_t address);

/*!
 * @brief Enables or disables the extension address (10-bit).
 *
 * @param base The I2C peripheral base pointer
 * @param enable true: 10-bit address is enabled.
 *               false: 10-bit address is not enabled.
 */
static inline void I2C_HAL_SetExtensionAddrCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C2_ADEXT(base, (uint8_t)enable);
}

/*!
 * @brief Returns whether the extension address is enabled or not.
 *
 * @param base The I2C peripheral base pointer
 * @return true: 10-bit address is enabled.
 *         false: 10-bit address is not enabled.
 */
static inline bool I2C_HAL_GetExtensionAddrCmd(I2C_Type * base)
{
    return I2C_BRD_C2_ADEXT(base);
}

/*!
 * @brief Controls whether the general call address is recognized.
 *
 * @param base The I2C peripheral base pointer
 * @param enable Whether to enable the general call address.
 */
static inline void I2C_HAL_SetGeneralCallCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C2_GCAEN(base, (uint8_t)enable);
}

/*!
 * @brief Enables or disables the slave address range matching.
 *
 * @param base The I2C peripheral base pointer.
 * @param enable Pass true to enable range address matching. You must also call
 *     I2C_HAL_SetUpperAddress7bit() to set the upper address.
 */
static inline void I2C_HAL_SetRangeMatchCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C2_RMEN(base, (uint8_t)enable);
}

/*!
 * @brief Sets the upper slave address.
 *
 * This slave address is used as a secondary slave address. If range address
 * matching is enabled, this slave address acts as the upper bound on the slave address
 * range.
 *
 * This function sets only a 7-bit slave address. If 10-bit addressing was enabled by calling
 * I2C_HAL_SetAddress10bit(), then the top 3 bits set with that function are also used
 * with the address set with this function to form a 10-bit address.
 *
 * Passing 0 for the @a address parameter  disables  matching the upper slave address.
 *
 * @param base The I2C peripheral base pointer
 * @param address The upper slave address in the upper 7 bits. Bit 0 of this value must be 0.
 *     In addition, this address must be greater than the primary slave address that is set by
 *     calling I2C_HAL_SetAddress7bit().
 */
static inline void I2C_HAL_SetUpperAddress7bit(I2C_Type * base, uint8_t address)
{
    assert((address & 1) == 0);
    assert((address == 0) || (address > I2C_RD_A1(base)));
    I2C_WR_RA(base, address);
}

/*@}*/

/*!
 * @name Status
 * @{
 */

/*!
 * @brief Gets the I2C status flag state.
 *
 * @param base The I2C peripheral base pointer.
 * @param statusFlag The status flag, defined in type i2c_status_flag_t.
 * @return State of the status flag: asserted (true) or not-asserted (false).
 *         - true: related status flag is being set.
 *         - false: related status flag is not set.
 */
static inline bool I2C_HAL_GetStatusFlag(I2C_Type * base, i2c_status_flag_t statusFlag)
{
    return (bool)((I2C_RD_S(base) >> statusFlag) & 0x1U);
}

/*!
 * @brief Returns whether the I2C module is in master mode.
 *
 * @param base The I2C peripheral base pointer.
 * @return Whether current I2C is in master mode or not.
 * @retval true The module is in master mode, which implies it is also performing a transfer.
 * @retval false The module is in slave mode.
 */
static inline bool I2C_HAL_IsMaster(I2C_Type * base)
{
    return (bool)I2C_BRD_C1_MST(base);
}

/*!
 * @brief Clears the arbitration lost flag.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_ClearArbitrationLost(I2C_Type * base)
{
    I2C_WR_S(base, I2C_S_ARBL_MASK);
}

/*@}*/

/*!
 * @name Interrupt
 * @{
 */

/*!
 * @brief Enables or disables I2C interrupt requests.
 *
 * @param base The I2C peripheral base pointer
 * @param enable   Pass true to enable interrupt, false to disable.
 */
static inline void I2C_HAL_SetIntCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_C1_IICIE(base, (uint8_t)enable);
}

/*!
 * @brief Returns whether the I2C interrupts are enabled.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether I2C interrupts are enabled or not.
 */
static inline bool I2C_HAL_GetIntCmd(I2C_Type * base)
{
    return (bool)I2C_BRD_C1_IICIE(base);
}

/*!
 * @brief Returns the current I2C interrupt flag.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether I2C interrupt is pending or not.
 */
static inline bool I2C_HAL_IsIntPending(I2C_Type * base)
{
    return (bool)I2C_BRD_S_IICIF(base);
}

/*!
 * @brief Clears the I2C interrupt if set.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_ClearInt(I2C_Type * base)
{
    I2C_WR_S(base, I2C_S_IICIF_MASK);
}

/*@}*/

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT || FSL_FEATURE_I2C_HAS_STOP_DETECT

/*!
 * @name Bus stop detection flag 
 * @{
 */

/*!
 * @brief Gets the flag indicating a STOP signal was detected on the I2C bus.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether a STOP signal is detected on bus or not.
 */
static inline bool I2C_HAL_GetStopFlag(I2C_Type * base)
{
    return (bool)I2C_BRD_FLT_STOPF(base);
}

/*!
 * @brief Clears the bus STOP signal detected flag.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_ClearStopFlag(I2C_Type * base)
{
    I2C_BWR_FLT_STOPF(base, 0x1U);
}

/*@}*/
#endif /* FSL_FEATURE_I2C_HAS_STOP_DETECT || FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

#if FSL_FEATURE_I2C_HAS_STOP_DETECT

/*!
 * @name Bus stop detection interrupt
 * @{
 */

/*!
 * @brief Enables the I2C bus stop detection interrupt.
 *
 * @param base The I2C peripheral base pointer.
 * @param enable   Pass true to enable interrupt, false to disable.
 */
static inline void I2C_HAL_SetStopIntCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_FLT_STOPIE(base, enable);
}

/*!
 * @brief Returns whether the I2C bus stop detection interrupts are enabled.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether the STOP detection interrupt is enabled or not.
 */
static inline bool I2C_HAL_GetStopIntCmd(I2C_Type * base)
{
    return (bool)I2C_BRD_FLT_STOPIE(base);
}

/*@}*/

#endif /* FSL_FEATURE_I2C_HAS_STOP_DETECT */

#if FSL_FEATURE_I2C_HAS_START_STOP_DETECT

/*!
 * @name Bus start/stop detection interrupt
 * @{
 */

/*!
 * @brief Enables the I2C bus start/stop detection interrupt.
 *
 * @param base The I2C peripheral base pointer
 * @param enable   Pass true to enable interrupt, flase to disable.
 */
static inline void I2C_HAL_SetStartStopIntCmd(I2C_Type * base, bool enable)
{
    I2C_BWR_FLT_SSIE(base, enable);
}

/*!
 * @brief Returns whether the I2C bus start/stop detection interrupts are enabled.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether stop detect interrupt is enabled or not.
 */
static inline bool I2C_HAL_GetStartStopIntCmd(I2C_Type * base)
{
    return (bool)I2C_BRD_FLT_SSIE(base);
}

/*!
 * @brief Gets the flag indicating a START signal was detected on the I2C bus.
 *
 * @param base The I2C peripheral base pointer
 * @return Whether START signal is detected on bus or not.
 */
static inline bool I2C_HAL_GetStartFlag(I2C_Type * base)
{
    return (bool)I2C_BRD_FLT_STARTF(base);
}

/*!
 * @brief Clears the bus START signal detected flag.
 *
 * @param base The I2C peripheral base pointer
 */
static inline void I2C_HAL_ClearStartFlag(I2C_Type * base)
{
    I2C_BWR_FLT_STARTF(base, 0x1U);
}

/*@}*/

#endif /* FSL_FEATURE_I2C_HAS_START_STOP_DETECT */

#if FSL_FEATURE_I2C_HAS_SMBUS
/*! @brief SMBus timeout status flags. */
typedef enum _smb_timeout_status_flag {
    kSMBCLKLowTimeout    = I2C_SMB_SLTF_MASK,
    kSMBCLKHighTimeout   = I2C_SMB_SHTF1_MASK,
    kSMBDATLowTimeout    = I2C_SMB_SHTF2_MASK
} smb_timeout_status_flag_t;
/*! @brief SMBus timeout counter clock. */
typedef enum _smb_timeout_counter_sel {
    kSrcBusClockDividBy64   = 0,
    kSrcBusClock            = 1
} smb_timeout_counter_sel_t;
/*!
 * @brief Fast NACK/ACK enable, if disable, an ACK/NACK will be automatically sent.
 * if enable, writing 0 to TXAK after receiving a data byte generates an ACK, writing 1
 * to TXAK after receiving a data byte generates a NACK
 *
 * @param base The I2C peripheral base pointer
 * @param enable Pass true to enable interrupt, false to disable.
 */

static inline void I2C_HAL_SetManualACKCmd(I2C_Type *base, bool enable)
{
    I2C_BWR_SMB_FACK(base,enable);
}

/*!
 * @brief Enables or disables SMBus alert response address matching.
 * After the host responds to a device that used the alert response address, you must use
 * software to put the device's address on the bus.
 *
 * @param base The I2C peripheral base pointer
 * @param enable Pass true to enable interrupt, false to disable.
 */

static inline void I2C_HAL_SetSMBusARACmd(I2C_Type *base, bool enable)
{
    I2C_BWR_SMB_ALERTEN(base, enable);
}
/*!
 * @brief Selects the clock source of the timeout counter.
 *
 * @param base The I2C peripheral base pointer
 * @param counterSel Counter value of smb_timeout_counter_sel_t.
 */

static inline void I2C_HAL_SelectSMBTimeoutCounter(I2C_Type *base, smb_timeout_counter_sel_t counterSel)
{
    I2C_BWR_SMB_TCKSEL(base, counterSel);
}
/*!
 * @brief Enables/Disables SCL high and SDA low timeout interrupt.
 *
 * @param base The I2C peripheral base pointer
 * @param enable   Pass true to enable interrupt, false to disable.
 */

static inline void I2C_HAL_SetSMBDATLowTimeoutIntCmd(I2C_Type *base, bool enable)
{
    I2C_BWR_SMB_SHTF2IE(base, enable);
}
/*!
 * @brief Get SMBus timeout status.
 *
 * @param base The I2C peripheral base pointer
 * @param status   Status value of smb_timeout_status_flag_t
 * @return Whether the according timeout status is set.
 */

static inline bool I2C_HAL_GetTimeoutStatus(I2C_Type *base, smb_timeout_status_flag_t status)
{
    return (bool) I2C_RD_SMB(base) & status;
}
/*!
 * @brief Clear SMBus timeout status.
 *
 * @param base The I2C peripheral base pointer
 * @param status  Status value of smb_timeout_status_flag_t
 */

void I2C_HAL_ClearTimeoutStatus(I2C_Type *base, smb_timeout_status_flag_t status);
/*!
 * @brief Enables/Disables SMBus device default address.
 *
 * @param base The I2C peripheral base pointer
 * @param enable  Pass true to enable interrupt, false to disable.
 * @param address  Slave address used by the SMBus
 */

void I2C_HAL_SetSMBusAddressCmd(I2C_Type *base, bool enable, uint8_t address);
/*!
 * @brief Config SMBCLK low timeout period.
 *
 * @param base The I2C peripheral base pointer
 * @param timeout  SCL low timeout value
 */

void I2C_HAL_ConfigSMBCLKLowTimeout(I2C_Type *base, uint16_t timeout);
#endif

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* __FSL_I2C_HAL_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/


