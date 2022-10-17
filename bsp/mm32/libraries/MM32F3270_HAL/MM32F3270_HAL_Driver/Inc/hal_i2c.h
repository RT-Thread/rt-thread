/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HAL_I2C_H__
#define __HAL_I2C_H__

#include "hal_common.h"

/*!
 * @addtogroup I2C
 * @{
 */

/*!
 * @addtogroup I2C_INT
 * @{
 */
#define I2C_INT_RX_UNDER        I2C_RAWISR_RXUNDER_MASK   /*!< Assert when attempting to read the RX fifo, even it is empty. */
#define I2C_INT_RX_NOTEMPTY     I2C_RAWISR_RXFULL_MASK    /*!< Assert when the data in RX fifo is available. */
#define I2C_INT_TX_EMPTY        I2C_RAWISR_TXEMPTY_MASK   /*!< When working as master, this bit asserts if the data count is under or equal to the tx threshold. */
#define I2C_INT_TX_ABORT        I2C_RAWISR_TXABRT_MASK    /*!< Assert when transmit abort. */
#define I2C_INT_ACTIVE          I2C_RAWISR_ACTIV_MASK     /*!< Assert when the i2c bus is active, while the clocks are transfered. */
#define I2C_INT_STOP            I2C_RAWISR_STOP_MASK      /*!< Assert when detecting a STOP on the i2c bus, no mater working as master or slave. */
#define I2C_INT_START           I2C_RAWISR_START_MASK     /*!< Assert when detecting a START on the i2c bus, no matter working as master or slave. */
/*!
 * @}
 */

/*!
 * @addtogroup I2C_STATUS
 * @{
 */
#define I2C_STATUS_ACTIVE       I2C_SR_ACTIV_MASK         /*!< I2C bus is active. */
#define I2C_STATUS_TX_EMPTY     I2C_SR_TFE_MASK           /*!< I2C tx fifo is empty. */
#define I2C_STATUS_RX_NOTEMPTY  I2C_SR_RFNE_MASK          /*!< I2C rx fifo is not empty. */
/*!
 * @}
 */

/*!
 * @brief I2C baudrate type.
 */
typedef enum
{
    I2C_BaudRate_50K  = 50000u,   /*!< Specify operate at the speed of 50K. */
    I2C_BaudRate_100K = 100000u,  /*!< Specify operate at the speed of 100K. */
} I2C_BaudRate_Type;

/*!
 * @brief I2C transmission direction type.
 */
typedef enum
{
    I2C_Direction_Tx = 0u,  /*!< Specify I2C transmission direction as tx. */
    I2C_Direction_Rx = 1u,  /*!< Specify I2C transmission direction as rx. */
} I2C_Direction_Type;

/*!
 * @brief Define the callback function called when the I2C master transfer is abort.
 */
typedef void (*I2C_Callback_1_Type)(void *param);

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref I2C_MasterXfer() to transfer the I2C address and data.
 */
typedef struct
{
    uint16_t            TargetAddr;        /*!< Specify I2C target device address. */
    I2C_Direction_Type  Direction;         /*!< specify transmission direction. */
    uint8_t             *TxBuf;            /*!< Specify the tx buffer array. */
    uint32_t            TxIdx;             /*!< Specify the number of data currently sent. */
    uint8_t             TxLen;             /*!< Specify the tx data len. */
    uint8_t             *RxBuf;            /*!< Specify the rx buffer array. */
    uint32_t            RxIdx;             /*!< Specify the number of data currently receive. */
    uint8_t             RxLen;             /*!< Specify the rx data len. */
    uint32_t            WaitTimes;         /*!< Specify the time limit for wait to the flag to be generated. If the required flag is not generated after this time, considered as timeout. */
    I2C_Callback_1_Type DoneCallback;      /*!< Callback function, called when the i2c transmit is done. */
    I2C_Callback_1_Type AbortCallback;     /*!< Callback function, called when the i2c transmit is abort. */
} I2C_MasterXfer_Type;

/*!
 * @brief This type of structure instance is used to keep the settings when calling the @ref I2C_InitMaster() to initialize the I2C master module.
 */
typedef struct
{
    uint32_t            ClockFreqHz;       /*!< Specify bus clock frequency. */
    I2C_BaudRate_Type   BaudRate;          /*!< Specify the I2C communication baud rate. */
} I2C_Master_Init_Type;

/*!
 * @brief Initialize the I2C master module.
 *
 * @param I2Cx I2C instance.
 * @param init  Pointer to the master initialization structure. See to @ref I2C_Master_Init_Type.
 * @return The initialize succeed return true, the misconfiguration of speed or baud rate return false.
 */
bool I2C_InitMaster(I2C_Type * I2Cx, I2C_Master_Init_Type * init);

/*!
 * @brief Enabel the I2C module.
 *
 * @param I2Cx I2C instance.
 * @param enable 'true' to enable the module, 'false' to disable the module.
 * @return None.
 */
void I2C_Enable(I2C_Type *I2Cx, bool enable);

/*!
 * @brief Set the I2C target device address that matches the slave device.
 *
 * @param I2Cx I2C instance.
 * @param addr I2C target device address.
 * @return None.
 */
void I2C_SetTargetAddr(I2C_Type * I2Cx, uint8_t addr);

/*!
 * @brief Get I2C target device address.
 *
 * @param I2Cx I2C instance.
 * @return I2C target device addr.
 */
uint16_t I2C_GetTargetAddr(I2C_Type * I2Cx);

/*!
 * @brief Put the data into transmiter buffer of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @param val Data value to be send through the transmiter.
 * @return None.
 */
void I2C_PutData(I2C_Type * I2Cx, uint8_t val);

/*!
 * @brief Control read-write bit to prepare for data acquisition.
 *
 * @param I2Cx I2C instance.
 * @return None.
 */
void I2C_PrepareToGetData(I2C_Type * I2Cx);

/*!
 * @brief Get the data from receiver buffer of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @return Data received by I2C bus.
 */
uint8_t I2C_GetData(I2C_Type * I2Cx);

/*!
 * @brief  Get the current status flags of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @return Status flags. See to @ref I2C_STATUS.
 */
uint32_t I2C_GetStatus(I2C_Type * I2Cx);

/*!
 * @brief Prepare for the stop, when transfer finish.
 *
 * @param I2Cx I2C instance.
 * @return None.
 */
void I2C_Stop(I2C_Type * I2Cx);

/*!
 * @brief Enable interrupts of I2C module.
 *
 * @param I2Cx I2C instance.
 * @param interrupts Interrupt code masks. See to @ref I2C_INT.
 * @param enable 'true' to enable the indicated interrupts, 'false' to disable the indicated interrupts.
 * @return None.
 */
void I2C_EnableInterrupts(I2C_Type * I2Cx, uint32_t interrupts, bool enable);

/*!
 * @brief Read the current enabled interrupts the I2C module.
 *
 * @param I2Cx I2C instance.
 * @return The mask codes enabled interrupts. See to @ref I2C_INT.
 */
uint32_t I2C_GetEnabledInterrupts(I2C_Type * I2Cx);

/*!
 * @brief Get the I2C interrupt status flags of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @return Interrupt status flags. See to @ref I2C_INT.
 */
uint32_t I2C_GetInterruptStatus(I2C_Type * I2Cx);

/*!
 * @brief Clear the I2C interrupt status flags of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @param interrupts The mask codes of the indicated interrupt flags to be cleared.
 * @return None.
 */
void I2C_ClearInterruptStatus(I2C_Type * I2Cx, uint32_t interrupts);

/*!
 * @brief I2C master interrupt transfer of the I2C module.
 *
 * @param I2Cx I2C instance.
 * @param xfer Pointer to the I2C master transimt structure. See to @ref I2C_MasterXfer_Type.
 * @return None.
 */
void I2C_MasterXfer(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer);

/*!
 * @brief I2C master transfer interrupt handler.
 *
 * @param I2Cx I2C instance.
 * @param xfer Pointer to the I2C master transimt structure. See to @ref I2C_MasterXfer_Type.
 * @param interrupts Interrupt status flags. See to @ref I2C_INT.
 * @return None.
 */
void I2C_MasterXferHandler(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer, uint32_t interrupts);

/*!
 * @brief I2C master write polling.
 *
 * @param I2Cx I2C instance.
 * @param xfer Pointer to the I2C master transimt structure. See to @ref I2C_MasterXfer_Type.
 * @return 'true' to I2C write polling succeed, 'false' to I2C write polling failed.
 */
bool I2C_MasterWriteBlocking(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer);

/*!
 * @brief I2C master read polling.
 *
 * @param I2Cx I2C instance.
 * @param xfer Pointer to the I2C master transimt structure. See to @ref I2C_MasterXfer_Type.
 * @return 'true' to I2C read polling succeed, 'false' to I2C read polling failed.
 */
bool I2C_MasterReadBlocking(I2C_Type * I2Cx, I2C_MasterXfer_Type * xfer);

/*!
 *@}
 */

#endif /* __HAL_I2C_H__ */

