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

#include "i2c_18xx_43xx.h"
#include "scu_18xx_43xx.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define MAX_TX_BUFFER_SIZE 10	/* Maximum transmit buffer size in Chip_I2C_MasterWriteReg() function */

static uint32_t i2cClockrate[2];
static I2C_M_SETUP_Type TransferMCfg;
static uint8_t p_regAddr;
static uint8_t tx_buffer[MAX_TX_BUFFER_SIZE];

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Determine clock for uart BASED ON SELECTED uart */
static CCU_CLK_T Chip_I2C_DetermineClk(LPC_I2C_Type *I2Cx) {

	CCU_CLK_T i2cclk;

	/* Pick clock for uart BASED ON SELECTED uart */
	if (I2Cx == LPC_I2C0) {
		i2cclk = CLK_APB1_I2C0;
	}
	else {
		i2cclk = CLK_APB3_I2C1;
	}

	return i2cclk;
}

/* Get UART bus number BASED ON SELECTED uart */
static I2C_ID_Type Chip_I2C_Get_BusNum(LPC_I2C_Type *I2Cx)
{
	if (I2Cx == LPC_I2C1) {
		return I2C1;
	}

	return I2C0;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the LPC_I2C peripheral with specified parameter */
void Chip_I2C_Init(LPC_I2C_Type *I2Cx)
{
	/* Enable I2C Clocking */
	//	Chip_Clock_EnableOpts(Chip_I2C_DetermineClk(I2Cx), false, false, 1);
	Chip_Clock_Enable(Chip_I2C_DetermineClk(I2Cx));

	IP_I2C_Init(I2Cx);
}

/* De-initializes the I2C peripheral registers to their default reset values */
void Chip_I2C_DeInit(LPC_I2C_Type *I2Cx)
{
	IP_I2C_DeInit(I2Cx);

	/* Disable UART clocking */
	Chip_Clock_Disable(Chip_I2C_DetermineClk(I2Cx));
}

/* Set up clock rate for LPC_I2C peripheral */
void Chip_I2C_SetClockRate(LPC_I2C_Type *I2Cx, uint32_t clockrate)
{
	if (I2Cx == LPC_I2C0) {
		i2cClockrate[0] = clockrate;
		/* Select weather standard, fast, fast plus mode*/
		if (clockrate >= 1000000) {	/* Fast mode plus: 1MHz, high speed 3.4MHz */
			Chip_SCU_I2C0PinConfig(I2C0_FAST_MODE_PLUS);
		}
		else {					/* standard 100KHz, fast 400KHz */
			Chip_SCU_I2C0PinConfig(I2C0_STANDARD_FAST_MODE);
		}
	}
	else if (I2Cx == LPC_I2C1) {
		i2cClockrate[1] = clockrate;
		/* Check if I2C1 run fast mode*/
		if (clockrate > 400000) {
			return;
		}
	}
	else {return; }

	/* Set clock rate */
	if (clockrate < 1000) {	/* make sure SCLH,SCLL not exceed its 16bit value */
		return;
	}

	IP_I2C_SetClockRate(I2Cx, (Chip_Clock_GetRate(Chip_I2C_DetermineClk(I2Cx)) / clockrate));
}

/* Get current clock rate for LPC_I2C peripheral */
uint32_t Chip_I2C_GetClockRate(LPC_I2C_Type *I2Cx)
{
	if (I2Cx == LPC_I2C0) {
		return i2cClockrate[0];
	}
	else if (I2Cx == LPC_I2C1) {
		return i2cClockrate[1];
	}
	return 0;
}

/* Transmit and Receive data in master mode */
Status Chip_I2C_MasterTransferData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->retransmissions_max = 3;
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;
	TransferCfg->retransmissions_count = 0;

	return IP_I2C_MasterTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* Transmit an array of bytes in Master mode */
Status Chip_I2C_MasterTransmitData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->rx_data = NULL;
	TransferCfg->rx_length = 0;
	TransferCfg->retransmissions_max = 3;
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;
	TransferCfg->retransmissions_count = 0;

	return IP_I2C_MasterTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* Receive an array of bytes in Master mode */
Status Chip_I2C_MasterReceiveData(LPC_I2C_Type *I2Cx, I2C_M_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->tx_data = NULL;
	TransferCfg->tx_length = 0;
	TransferCfg->retransmissions_max = 3;
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;
	TransferCfg->retransmissions_count = 0;

	return IP_I2C_MasterTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* Transmit one byte and continue to send an array of bytes
 * after a repeated start condition is generated in Master mode
 */
uint32_t Chip_I2C_MasterWriteReg(LPC_I2C_Type *I2Cx,
								 uint32_t SlaveAddr,
								 uint8_t regAddr,
								 uint8_t *buffer,
								 uint8_t buffer_len)
{
	uint8_t i = 0;
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	tx_buffer[0] = regAddr;

	for (i = 0; i < buffer_len; i++)
		tx_buffer[i + 1] = *(buffer + i);

	TransferMCfg.sl_addr7bit = SlaveAddr;
	TransferMCfg.tx_data = tx_buffer;
	TransferMCfg.tx_length = buffer_len + 1;
	TransferMCfg.rx_data = NULL;
	TransferMCfg.rx_length = 0;
	TransferMCfg.retransmissions_max = 3;
	TransferMCfg.tx_count = 0;
	TransferMCfg.rx_count = 0;
	TransferMCfg.retransmissions_count = 0;
	IP_I2C_MasterTransferData(I2Cx, I2C_Num, &TransferMCfg, I2C_TRANSFER_POLLING);

	return TransferMCfg.tx_count;
}

/* Transmit one byte and receive an array of bytes after a repeated start condition is generated in Master mode.
 * This function is useful for communicating with the I2C slave registers
 */
uint32_t Chip_I2C_MasterReadReg(LPC_I2C_Type *I2Cx,
								uint32_t SlaveAddr,
								uint8_t regAddr,
								uint8_t *buffer,
								uint8_t buffer_len)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	p_regAddr = regAddr;

	TransferMCfg.sl_addr7bit = SlaveAddr;
	TransferMCfg.tx_data = &p_regAddr;
	TransferMCfg.tx_length = 1;
	TransferMCfg.rx_data = buffer;
	TransferMCfg.rx_length = buffer_len;
	TransferMCfg.retransmissions_max = 3;
	TransferMCfg.tx_count = 0;
	TransferMCfg.rx_count = 0;
	TransferMCfg.retransmissions_count = 0;
	IP_I2C_MasterTransferData(I2Cx, I2C_Num, &TransferMCfg, I2C_TRANSFER_POLLING);

	return TransferMCfg.rx_count;
}

/* General Master Interrupt handler for I2C peripheral */
void Chip_I2C_Interrupt_MasterHandler(LPC_I2C_Type *I2Cx)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	IP_I2C_Interrupt_MasterHandler(I2Cx, I2C_Num);
}

/* Get status of Master Transfer */
bool Chip_I2C_Interrupt_MasterTransferComplete(LPC_I2C_Type *I2Cx)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	return IP_I2C_Interrupt_MasterTransferComplete(I2C_Num);
}

/* Receive and Transmit data in slave mode */
Status Chip_I2C_SlaveTransferData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;

	return IP_I2C_SlaveTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* Transmit an array of bytes in Slave mode */
Status Chip_I2C_SlaveTransmitData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->tx_count = 0;
	TransferCfg->rx_data = NULL;
	TransferCfg->rx_length = 0;
	TransferCfg->rx_count = 0;

	return IP_I2C_SlaveTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* Receive an array of bytes in Slave mode */
Status Chip_I2C_SlaveReceiveData(LPC_I2C_Type *I2Cx, I2C_S_SETUP_Type *TransferCfg, I2C_TRANSFER_OPT_Type Opt)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	TransferCfg->tx_data = NULL;
	TransferCfg->tx_length = 0;
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;

	return IP_I2C_SlaveTransferData(I2Cx, I2C_Num, TransferCfg, Opt);
}

/* General Slave Interrupt handler for I2C peripheral */
void Chip_I2C_Interrupt_SlaveHandler(LPC_I2C_Type *I2Cx)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	IP_I2C_Interrupt_SlaveHandler(I2Cx, I2C_Num);
}

/* Get status of Slave Transfer */
bool Chip_I2C_Interrupt_SlaveTransferComplete(LPC_I2C_Type *I2Cx)
{
	I2C_ID_Type I2C_Num = Chip_I2C_Get_BusNum(I2Cx);

	return IP_I2C_Interrupt_SlaveTransferComplete(I2C_Num);
}
