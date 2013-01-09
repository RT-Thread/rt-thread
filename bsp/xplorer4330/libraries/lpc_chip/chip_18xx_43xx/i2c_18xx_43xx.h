/*
 * @brief LPC18xx/43xx I2C driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#ifndef I2C_18XX_43XX_H_
#define I2C_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup I2C_18XX_43XX CHIP: LPC18xx/43xx I2C Driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/**
 * @brief	Initializes the LPC_I2C peripheral with specified parameter.
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Nothing
 */
void Chip_I2C_Init(LPC_I2C_Type *I2Cx);

/**
 * @brief	De-initializes the I2C peripheral registers to their default reset values
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Nothing
 */
void Chip_I2C_DeInit(LPC_I2C_Type *I2Cx);

/**
 * @brief	Set up clock rate for LPC_I2C peripheral.
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	clockrate	: Target clock rate value to initialized I2C peripheral (Hz)
 * @return	Nothing
 */
void Chip_I2C_SetClockRate(LPC_I2C_Type *I2Cx, uint32_t clockrate);

/**
 * @brief	Get current clock rate for LPC_I2C peripheral.
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	the current I2Cx clock rate
 */
uint32_t Chip_I2C_GetClockRate(LPC_I2C_Type *I2Cx);

/**
 * @brief	Transmit and Receive data in master mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_M_SETUP_Type structure that contains specified
 *                      information about the configuration for master transfer.
 * @param	Opt			: a I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode
 * @return	SUCCESS or ERROR
 */
Status Chip_I2C_MasterTransferData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	Transmit an array of bytes in Master mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_M_SETUP_Type structure that contains specified
 *                      information about the	configuration for master transfer
 * @param	Opt			: a I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode
 * @return  SUCCESS or ERROR
 */
Status Chip_I2C_MasterTransmitData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	Receive an array of bytes in Master mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_M_SETUP_Type structure that contains specified
 *                      information about the configuration for master transfer.
 * @param	Opt			: a I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode.
 * @return	SUCCESS or ERROR
 */
Status Chip_I2C_MasterReceiveData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	Write byte(s) to slave register
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	SlaveAddr	: Slave address in 7-bit mode
 * @param	regAddr		: Slave register address
 * @param	buffer		: pointer to data array needed to send
 * @param	buffer_len	: data length (number of bytes)
 * @return	Number of bytes sent
 * Transmit one byte and an array of bytes after a repeated start condition is generated in Master mode.
 * This function is useful for communicating with the I2C slave registers.
 */
uint32_t Chip_I2C_MasterWriteReg(LPC_I2C_Type *I2Cx,
								 uint32_t SlaveAddr,
								 uint8_t regAddr,
								 uint8_t *buffer,
								 uint8_t buffer_len);

/**
 * @brief	Read slave register content
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	SlaveAddr	: Slave address in 7-bit mode
 * @param	regAddr		: Slave register address
 * @param	buffer		: pointer to data array needed to receive
 * @param	buffer_len	: data length (number of bytes)
 * @return	Number of bytes received
 * Transmit one byte and continue to receive an array of bytes after a repeated start condition is
 * generated in Master mode. This function is useful for communicating with the I2C slave registers.
 */
uint32_t Chip_I2C_MasterReadReg(LPC_I2C_Type *I2Cx,
								uint32_t SlaveAddr,
								uint8_t regAddr,
								uint8_t *buffer,
								uint8_t buffer_len);

/**
 * @brief	General Master Interrupt handler for I2C peripheral
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Nothing
 */
void Chip_I2C_Interrupt_MasterHandler (LPC_I2C_Type *I2Cx);

/**
 * @brief	Get status of Master Transfer
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Master transfer status: TRUE (transfer completed) or FALSE (not completed yet)
 */
bool Chip_I2C_Interrupt_MasterTransferComplete(LPC_I2C_Type *I2Cx);

/**
 * @brief	Receive and Transmit data in slave mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_S_SETUP_Type structure that contains specified
 *                      information about the configuration for master transfer.
 * @param	Opt			: I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode.
 * @return	SUCCESS or ERROR
 */
Status Chip_I2C_SlaveTransferData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	Transmit an array of bytes in Slave mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_S_SETUP_Type structure that contains specified
 *                      information about the configuration for slave transfer.
 * @param	Opt			: a I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode.
 * @return	SUCCESS or ERROR
 */
Status Chip_I2C_SlaveTransmitData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	Receive an array of bytes in Slave mode
 * @param	I2Cx		: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	TransferCfg	: Pointer to a I2C_S_SETUP_Type structure that contains specified
 *                      information about the configuration for slave transfer.
 * @param	Opt			: a I2C_TRANSFER_OPT_Type type that selected for interrupt or polling mode.
 * @return	SUCCESS or ERROR
 */
Status Chip_I2C_SlaveReceiveData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt);

/**
 * @brief	General Slave Interrupt handler for I2C peripheral
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Nothing
 */
void Chip_I2C_Interrupt_SlaveHandler (LPC_I2C_Type *I2Cx);

/**
 * @brief	Get status of Slave Transfer
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @return	Slave transfer status: TRUE (transfer completed) or FALSE (not completed yet)
 */
bool Chip_I2C_Interrupt_SlaveTransferComplete(LPC_I2C_Type *I2Cx);

/**
 * @brief	Set Own slave address in I2C peripheral corresponding to parameter specified in OwnSlaveAddrConfigStruct.
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	OwnSlaveAddrConfigStruct : Pointer to a I2C_OWNSLAVEADDR_CFG_Type structure that contains the
 *                      configuration information for the specified I2C slave address.
 * @return	Nothing
 */
STATIC INLINE void Chip_I2C_SetOwnSlaveAddr(LPC_I2C_Type *I2Cx, I2C_OWNSLAVEADDR_CFG_Type *OwnSlaveAddrConfigStruct)
{
	IP_I2C_SetOwnSlaveAddr(I2Cx, OwnSlaveAddrConfigStruct);
}

/**
 * @brief	Enable or disable I2C peripheral's operation
 * @param	I2Cx	: I2C peripheral selected, should be LPC_I2C0 or LPC_I2C1
 * @param	Mode	: I2C mode, should be I2C_MASTER_MODE, I2C_SLAVE_MODE or I2C_GENERAL_MODE
 * @param	NewState: New State of LPC_I2C peripheral's operation, should be ENABLE or DISABLE
 * @return	Nothing
 */
STATIC INLINE void Chip_I2C_Cmd(LPC_I2C_Type *I2Cx, I2C_Mode Mode, FunctionalState NewState)
{
	IP_I2C_Cmd(I2Cx, Mode, NewState);
}

/**
 * @}
 */

 #ifdef __cplusplus
}
#endif

#endif /* I2C_18XX_43XX_H_ */
