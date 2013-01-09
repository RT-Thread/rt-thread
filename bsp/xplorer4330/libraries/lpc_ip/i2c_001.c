/*
 * @brief	I2C driver functions
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

#include "i2c_001.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/* I2C device configuration structure type */
typedef struct {
	union {
		I2C_M_SETUP_Type    txrx_setup_master;		/* Transmission setup */
		I2C_S_SETUP_Type    txrx_setup_slave;		/* Transmission setup */
	};

	int32_t     dir;	/* Current direction phase, 0 - write, 1 - read */
} I2C_CFG_T;

#define BLOCKING_TIMEOUT (0x000FFFFFUL)
#define RESTRANSMISSION_MAX (0x000000FFUL)

/* I2C driver data for I2C0, I2C1 */
static I2C_CFG_T i2cdat[3];

static bool I2C_MasterComplete[3];
static bool I2C_SlaveComplete[3];

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/* Generate a start condition on I2C bus (in master mode only) */
static uint32_t IP_I2C_Start(IP_I2C_001_Type *LPC_I2C, I2C_TRANSFER_OPT_Type Opt)
{
	uint32_t cnt = 0;
	/* Reset STA, STO, SI */
	LPC_I2C->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STOC | I2C_I2CONCLR_STAC;

	/* Enter to Master Transmitter mode */
	LPC_I2C->CONSET = I2C_I2CONSET_STA;

	if (Opt == I2C_TRANSFER_POLLING) {
		/* Wait for complete */
		while (!(LPC_I2C->CONSET & I2C_I2CONSET_SI)) {
			if (++cnt > BLOCKING_TIMEOUT) {
				return I2C_STAT_CODE_ERROR;
			}
		}
	}

	return LPC_I2C->STAT & I2C_STAT_CODE_BITMASK;
}

/* Generate a stop condition on I2C bus (in master mode only) */
static Status IP_I2C_Stop(IP_I2C_001_Type *LPC_I2C, I2C_TRANSFER_OPT_Type Opt)
{
	uint32_t cnt = 0;
	/* Make sure start bit is not active */
	if (LPC_I2C->CONSET & I2C_I2CONSET_STA) {
		LPC_I2C->CONCLR = I2C_I2CONCLR_STAC;
	}

	LPC_I2C->CONSET = I2C_I2CONSET_STO;

	LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;

	if (Opt == I2C_TRANSFER_POLLING) {
		/* wait for stop is sent */
		while (LPC_I2C->CONSET & I2C_I2CONSET_STO) {
			if (LPC_I2C->CONSET & I2C_I2CONSET_SI) {
				LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
			}
			if (++cnt > BLOCKING_TIMEOUT) {
				return ERROR;
			}
		}
	}

	return SUCCESS;
}

/* I2C send byte subroutine */
static uint32_t IP_I2C_SendByte(IP_I2C_001_Type *LPC_I2C, uint8_t databyte)
{
	uint32_t CodeStatus = LPC_I2C->STAT & I2C_STAT_CODE_BITMASK;

	if ((CodeStatus != I2C_I2STAT_M_TX_START) &&
		(CodeStatus != I2C_I2STAT_M_TX_RESTART) &&
		(CodeStatus != I2C_I2STAT_M_TX_SLAW_ACK)  &&
		(CodeStatus != I2C_I2STAT_M_TX_DAT_ACK)  ) {
		return CodeStatus;
	}

	LPC_I2C->DAT = databyte & I2C_I2DAT_BITMASK;

	LPC_I2C->CONSET = I2C_I2CONSET_AA;

	LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;

	return LPC_I2C->STAT & I2C_STAT_CODE_BITMASK;
}

/* I2C get byte subroutine */
static uint32_t IP_I2C_GetByte(IP_I2C_001_Type *LPC_I2C, uint8_t *retdat, bool ack)
{
	*retdat = (uint8_t) (LPC_I2C->DAT & I2C_I2DAT_BITMASK);

	if (ack == true) {
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
	}
	else {
		LPC_I2C->CONCLR = I2C_I2CONCLR_AAC;
	}

	LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;

	return LPC_I2C->STAT & I2C_STAT_CODE_BITMASK;
}

/* Handle I2C Master states */
static int32_t IP_I2C_MasterHanleStates(IP_I2C_001_Type *LPC_I2C,
										uint32_t CodeStatus,
										I2C_M_SETUP_Type *TransferCfg,
										I2C_TRANSFER_OPT_Type Opt)
{
	uint8_t *txdat;
	uint8_t *rxdat;
	uint8_t tmp;
	int32_t Ret = I2C_OK;

	/* get buffer to send/receive */
	txdat = (uint8_t *) &TransferCfg->tx_data[TransferCfg->tx_count];
	rxdat = (uint8_t *) &TransferCfg->rx_data[TransferCfg->rx_count];

	switch (CodeStatus) {
	case I2C_I2STAT_M_TX_START:
	case I2C_I2STAT_M_TX_RESTART:
		// case I2C_I2STAT_M_RX_START:
		// case I2C_I2STAT_M_RX_RESTART
		/* Send data first */
		if (TransferCfg->tx_count < TransferCfg->tx_length) {
			/* Send slave address + WR direction bit = 0 ----------------------------------- */
			IP_I2C_SendByte(LPC_I2C, (TransferCfg->sl_addr7bit << 1));
			Ret = I2C_BYTE_SENT;
		}
		else if (TransferCfg->rx_count  < TransferCfg->rx_length) {
			/* Send slave address + RD direction bit = 1 ----------------------------------- */
			IP_I2C_SendByte(LPC_I2C, ((TransferCfg->sl_addr7bit << 1) | 0x01));
			Ret = I2C_BYTE_SENT;
		}
		/* Clear STA bit after the slave address is sent */
		LPC_I2C->CONCLR = I2C_I2CONCLR_STAC;
		break;

	case I2C_I2STAT_M_TX_SLAW_ACK:
	case I2C_I2STAT_M_TX_DAT_ACK:

		if (TransferCfg->tx_count < TransferCfg->tx_length) {
			IP_I2C_SendByte(LPC_I2C, *txdat);
			txdat++;
			TransferCfg->tx_count++;
			Ret = I2C_BYTE_SENT;
		}
		else {
			if (TransferCfg->rx_count >= TransferCfg->rx_length) {
				IP_I2C_Stop(LPC_I2C, Opt);
			}
			Ret = I2C_SEND_END;

		}
		break;

	case I2C_I2STAT_M_TX_DAT_NACK:
		if (TransferCfg->rx_count >= TransferCfg->rx_length) {
			IP_I2C_Stop(LPC_I2C, Opt);
		}
		Ret = I2C_SEND_END;
		break;

	case I2C_I2STAT_M_RX_ARB_LOST:
	case I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL:
	case I2C_I2STAT_S_TX_ARB_LOST_M_SLA:
		// case I2C_I2STAT_M_TX_ARB_LOST:
		IP_I2C_Stop(LPC_I2C, Opt);
		Ret = I2C_ERR;
		break;

	case I2C_I2STAT_M_RX_SLAR_ACK:
		if (TransferCfg->rx_length > 1) {
			LPC_I2C->CONSET = I2C_I2CONSET_AA;
		}
		else {
			LPC_I2C->CONCLR = I2C_I2CONCLR_AAC;
		}
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;

		Ret = I2C_BYTE_RECV;
		break;

	case I2C_I2STAT_M_RX_DAT_ACK:
		if (TransferCfg->rx_count < TransferCfg->rx_length) {
			if ((TransferCfg->rx_length > 1) && (TransferCfg->rx_count < (TransferCfg->rx_length - 2))) {
				IP_I2C_GetByte(LPC_I2C, &tmp, true);
				Ret = I2C_BYTE_RECV;

			}
			else {		/* the next byte is the last byte, send NACK instead */
				IP_I2C_GetByte(LPC_I2C, &tmp, false);
				Ret = I2C_BYTE_RECV;
			}
			*rxdat++ = tmp;

			TransferCfg->rx_count++;
		}
		else {
			IP_I2C_Stop(LPC_I2C, Opt);
			Ret = I2C_RECV_END;
		}
		break;

	case I2C_I2STAT_M_RX_DAT_NACK:
		IP_I2C_GetByte(LPC_I2C, &tmp, false);
		if (TransferCfg->rx_count < TransferCfg->rx_length) {
			*rxdat++ = tmp;
			TransferCfg->rx_count++;
		}
		IP_I2C_Stop(LPC_I2C, Opt);
		Ret = I2C_RECV_END;
		break;

	case I2C_I2STAT_M_RX_SLAR_NACK:
	case I2C_I2STAT_M_TX_SLAW_NACK:
	case I2C_I2STAT_BUS_ERROR:
		/* Send STOP condition */
		IP_I2C_Stop(LPC_I2C, Opt);
		Ret = I2C_ERR;
		break;

	/* No status information */
	case I2C_I2STAT_NO_INF:
		if ((TransferCfg->tx_count < TransferCfg->tx_length) ||
			(TransferCfg->rx_count < TransferCfg->rx_length)) {
			IP_I2C_Stop(LPC_I2C, Opt);
			Ret = I2C_ERR;
		}
		else {
			Ret = I2C_RECV_END;
		}
		break;

	default:
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;
	}

	return Ret;
}

/* Handle I2C Master states */
static int32_t IP_I2C_SlaveHanleStates(IP_I2C_001_Type *LPC_I2C, uint32_t CodeStatus, I2C_S_SETUP_Type *TransferCfg)
{
	int32_t Ret = I2C_OK;
	uint8_t *txdat;
	uint8_t *rxdat;

	/* get buffer to send/receive */
	txdat = (uint8_t *) &TransferCfg->tx_data[TransferCfg->tx_count];
	rxdat = (uint8_t *) &TransferCfg->rx_data[TransferCfg->rx_count];

	switch (CodeStatus) {
	/* Reading phase -------------------------------------------------------- */
	/* Own SLA+R has been received, ACK has been returned */
	case I2C_I2STAT_S_RX_SLAW_ACK:

	/* General call address has been received, ACK has been returned */
	case I2C_I2STAT_S_RX_GENCALL_ACK:
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;

	/* Arbitration has been lost in Slave Address + R/W bit as bus Master. General Call has
	    been received and ACK has been returned.*/
	case I2C_I2STAT_S_RX_ARB_LOST_M_GENCALL:
		LPC_I2C->CONSET = I2C_I2CONSET_AA | I2C_I2CONSET_STA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;

	/* Previously addressed with own SLA;
	 * DATA byte has been received;
	 * ACK has been returned */
	case I2C_I2STAT_S_RX_ARB_LOST_M_SLA:
	case I2C_I2STAT_S_RX_PRE_SLA_DAT_ACK:
		/*
		 * All data bytes that over-flow the specified receive
		 * data length, just ignore them.
		 */
		if ((TransferCfg->rx_count < TransferCfg->rx_length) && (TransferCfg->rx_data != NULL)) {
			*rxdat++ = (uint8_t) LPC_I2C->DAT;

			TransferCfg->rx_count++;

			Ret = I2C_BYTE_RECV;
		}
		if (TransferCfg->rx_count == (TransferCfg->rx_length) ) {
			LPC_I2C->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC;
			Ret = I2C_BYTE_RECV;
		}
		else {
			LPC_I2C->CONSET = I2C_I2CONSET_AA;
			LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		}

		break;

	/* DATA has been received, Only the first data byte will be received with ACK.
	 * Additional data will be received with NOT ACK. */
	case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_ACK:
		if ((TransferCfg->rx_count < TransferCfg->rx_length) && (TransferCfg->rx_data != NULL)) {
			*rxdat++ = (uint8_t) LPC_I2C->DAT;

			TransferCfg->rx_count++;

			Ret = I2C_BYTE_RECV;
		}
		LPC_I2C->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC;
		break;

	/* Writing phase -------------------------------------------------------- */
	/* Own SLA+R has been received, ACK has been returned */
	case I2C_I2STAT_S_TX_SLAR_ACK:

	/* Data has been transmitted, ACK has been received */
	case I2C_I2STAT_S_TX_DAT_ACK:
		/*
		 * All data bytes that over-flow the specified receive
		 * data length, just ignore them.
		 */
		if ((TransferCfg->tx_count < TransferCfg->tx_length) && (TransferCfg->tx_data != NULL)) {
			LPC_I2C->DAT = *txdat++;

			TransferCfg->tx_count++;

			Ret = I2C_BYTE_SENT;
		}

		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;

	/* Arbitration lost in Slave Address and R/W bit as bus Master.
	 * Own Slave Address + Read has been received, ACK has been returned. */
	case I2C_I2STAT_S_TX_ARB_LOST_M_SLA:
		if ((TransferCfg->tx_count < TransferCfg->tx_length) && (TransferCfg->tx_data != NULL)) {
			LPC_I2C->DAT = *txdat++;

			TransferCfg->tx_count++;

			Ret = I2C_BYTE_SENT;
		}
		LPC_I2C->CONSET = I2C_I2CONSET_AA | I2C_I2CONSET_STA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;

	case I2C_I2STAT_S_TX_LAST_DAT_ACK:
	/* Data has been transmitted, NACK has been received,
	 * that means there's no more data to send, exit now */
	/*
	 * Note: Don't wait for stop event since in slave transmit mode,
	 * since there no proof lets us know when a stop signal has been received
	 * on slave side.
	 */
	case I2C_I2STAT_S_TX_DAT_NACK:
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		Ret = I2C_SEND_END;
		break;

	/* Previously addressed with own SLA;
	 * DATA byte has been received;
	 * NOT ACK has been returned */
	case I2C_I2STAT_S_RX_PRE_SLA_DAT_NACK:

	/* DATA has been received, NOT ACK has been returned */
	case I2C_I2STAT_S_RX_PRE_GENCALL_DAT_NACK:
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		Ret = I2C_RECV_END;
		break;

	/*
	 * Note that: Return code only let us know a stop condition mixed
	 * with a repeat start condition in the same code value.
	 * So we should provide a time-out. In case this is really a stop
	 * condition, this will return back after time out condition. Otherwise,
	 * next session that is slave receive data will be completed.
	 */

	/* A Stop or a repeat start condition */
	case I2C_I2STAT_S_RX_STA_STO_SLVREC_SLVTRX:
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		Ret = I2C_STA_STO_RECV;
		break;

	/* No status information */
	case I2C_I2STAT_NO_INF:
	/* Other status must be captured */
	default:
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC;
		break;

	}

	return Ret;
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initializes the LPC_I2C peripheral */
void IP_I2C_Init(IP_I2C_001_Type *LPC_I2C)
{
	/* Set I2C operation to default */
	LPC_I2C->CONCLR = (I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC | I2C_I2CONCLR_I2ENC);
}

/* De-initializes the I2C peripheral registers to their default reset values */
void IP_I2C_DeInit(IP_I2C_001_Type *LPC_I2C)
{
	/* Disable I2C control */
	LPC_I2C->CONCLR = I2C_I2CONCLR_I2ENC;
}

/* Set up clock rate for I2Cx */
void IP_I2C_SetClockRate(IP_I2C_001_Type *LPC_I2C, uint32_t SCLValue)
{
	LPC_I2C->SCLH = (uint32_t) (SCLValue / 2);
	LPC_I2C->SCLL = (uint32_t) (SCLValue - LPC_I2C->SCLH);
}

/* Enable or disable I2C peripheral's operation */
void IP_I2C_Cmd(IP_I2C_001_Type *LPC_I2C, I2C_Mode Mode,  FunctionalState NewState)
{
	if (NewState == ENABLE) {
		if (Mode != I2C_SLAVE_MODE) {
			LPC_I2C->CONSET = I2C_I2CONSET_I2EN;
		}
		else {
			LPC_I2C->CONSET = I2C_I2CONSET_I2EN | I2C_I2CONSET_AA;
		}
	}
	else {
		LPC_I2C->CONCLR = I2C_I2CONCLR_I2ENC;
	}
}

/* General Master Interrupt handler for I2C peripheral */
void IP_I2C_Interrupt_MasterHandler(IP_I2C_001_Type *LPC_I2C, I2C_ID_Type I2C_Num)
{
	uint32_t returnCode;
	I2C_M_SETUP_Type *txrx_setup;
	int32_t Ret = I2C_OK;

	txrx_setup = (I2C_M_SETUP_Type *) &i2cdat[I2C_Num].txrx_setup_master;

	while (!(LPC_I2C->CONSET & I2C_I2CONSET_SI)) {}

	returnCode = (uint32_t) (LPC_I2C->STAT & I2C_STAT_CODE_BITMASK);

	/* Save current status */
	txrx_setup->status = returnCode;

	Ret = IP_I2C_MasterHanleStates(LPC_I2C, returnCode, txrx_setup, I2C_TRANSFER_INTERRUPT);

	if (I2C_CheckError(Ret)) {
		if (txrx_setup->retransmissions_count < txrx_setup->retransmissions_max) {
			/* Retry */
			txrx_setup->retransmissions_count++;
			txrx_setup->tx_count = 0;
			txrx_setup->rx_count = 0;
			/* Reset STA, STO, SI */
			IP_I2C_Start(LPC_I2C, I2C_TRANSFER_INTERRUPT);
			return;
		}
		else {
			goto s_int_end;
		}
	}
	else if (Ret & I2C_SEND_END) {
		/* If no need to wait for data from Slave */
		if (txrx_setup->rx_count >= (txrx_setup->rx_length)) {
			goto s_int_end;
		}
		else {	/* Start to wait for data from Slave */
			/* Reset STA, STO, SI */
			IP_I2C_Start(LPC_I2C, I2C_TRANSFER_INTERRUPT);
			return;
		}
	}
	else if (Ret & I2C_RECV_END) {
		goto s_int_end;
	}
	else {
		return;
	}

s_int_end:

	LPC_I2C->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;

	I2C_MasterComplete[I2C_Num] = true;
}

/* General Slave Interrupt handler for I2C peripheral */
void IP_I2C_Interrupt_SlaveHandler(IP_I2C_001_Type *LPC_I2C, I2C_ID_Type I2C_Num)
{
	uint32_t returnCode;
	I2C_S_SETUP_Type *txrx_setup;
	int32_t Ret = I2C_OK;

	txrx_setup = (I2C_S_SETUP_Type *) &i2cdat[I2C_Num].txrx_setup_slave;

	while (!(LPC_I2C->CONSET & I2C_I2CONSET_SI)) {}

	returnCode = (uint32_t) (LPC_I2C->STAT & I2C_STAT_CODE_BITMASK);
	/* Save current status */
	txrx_setup->status = returnCode;

	Ret = IP_I2C_SlaveHanleStates(LPC_I2C, returnCode, txrx_setup);

	if ((I2C_CheckError(Ret)) || (Ret & I2C_STA_STO_RECV) || (Ret & I2C_SEND_END)) {
		goto s_int_end;
	}
	else {
		return;
	}

s_int_end:
	LPC_I2C->CONCLR = I2C_I2CONCLR_AAC | I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;

	I2C_SlaveComplete[I2C_Num] = true;
}

/* Transmit and Receive data in master mode */
Status IP_I2C_MasterTransferData(IP_I2C_001_Type *LPC_I2C,
								 I2C_ID_Type I2C_Num,
								 I2C_M_SETUP_Type *TransferCfg,
								 I2C_TRANSFER_OPT_Type Opt)
{
	uint32_t CodeStatus;
	int32_t Ret = I2C_OK;

	/* Reset I2C setup value to default state */
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;
	TransferCfg->status = 0;

	if (Opt == I2C_TRANSFER_POLLING) {
		/* First Start condition -------------------------------------------------------------- */
		TransferCfg->retransmissions_count = 0;
retry:
		/* Reset I2C setup value to default state */
		TransferCfg->tx_count = 0;
		TransferCfg->rx_count = 0;

		/* Start command */
		CodeStatus = IP_I2C_Start(LPC_I2C, I2C_TRANSFER_POLLING);

		while (1) {	/* send data first and then receive data from Slave */
			Ret = IP_I2C_MasterHanleStates(LPC_I2C, CodeStatus, TransferCfg, I2C_TRANSFER_POLLING);
			if (I2C_CheckError(Ret)) {
				TransferCfg->retransmissions_count++;
				if (TransferCfg->retransmissions_count > TransferCfg->retransmissions_max) {
					/* save status */
					TransferCfg->status = CodeStatus | I2C_SETUP_STATUS_NOACKF;
					goto error;
				}
				else {
					goto retry;
				}
			}
			else if ( (Ret & I2C_BYTE_SENT) ||
					  (Ret & I2C_BYTE_RECV)) {
				/* Wait for sending ends/ Wait for next byte */
				while (!(LPC_I2C->CONSET & I2C_I2CONSET_SI)) {}
			}
			else if (Ret & I2C_SEND_END) {	/* already send all data */
				/* If no need to wait for data from Slave */
				if (TransferCfg->rx_count >= (TransferCfg->rx_length)) {
					break;
				}
				else {
					IP_I2C_Start(LPC_I2C, I2C_TRANSFER_POLLING);
				}
			}
			else if (Ret & I2C_RECV_END) {	/* already receive all data */
				break;
			}
			CodeStatus = LPC_I2C->STAT & I2C_STAT_CODE_BITMASK;
		}
		return SUCCESS;
error:
		return ERROR;
	}
	else if (Opt == I2C_TRANSFER_INTERRUPT) {
		I2C_MasterComplete[I2C_Num] = false;
		/* Setup tx_rx data, callback and interrupt handler */
		i2cdat[I2C_Num].txrx_setup_master = *TransferCfg;

		/* Set direction phase, write first */
		i2cdat[I2C_Num].dir = 0;

		/* First Start condition -------------------------------------------------------------- */
		/* Reset STA, STO, SI */
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STOC | I2C_I2CONCLR_STAC;
		LPC_I2C->CONSET = I2C_I2CONSET_STA;

		return SUCCESS;
	}

	return ERROR;
}

/* Receive and Transmit data in slave mode */
Status IP_I2C_SlaveTransferData(IP_I2C_001_Type *LPC_I2C,
								I2C_ID_Type I2C_Num,
								I2C_S_SETUP_Type *TransferCfg,
								I2C_TRANSFER_OPT_Type Opt)
{
	int32_t   Ret = I2C_OK;
	uint32_t CodeStatus = 0;

	/* Reset I2C setup value to default state */
	TransferCfg->tx_count = 0;
	TransferCfg->rx_count = 0;
	TransferCfg->status = 0;

	/* Polling option */
	if (Opt == I2C_TRANSFER_POLLING) {
		/* Set AA bit to ACK command on I2C bus */
		LPC_I2C->CONSET = I2C_I2CONSET_AA;

		/* Clear SI bit to be ready ... */
		LPC_I2C->CONCLR = (I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC | I2C_I2CONCLR_STOC);

		while (1) {
			/* Check SI flag ready */
			if (LPC_I2C->CONSET & I2C_I2CONSET_SI) {
				CodeStatus = (LPC_I2C->STAT & I2C_STAT_CODE_BITMASK);

				Ret = IP_I2C_SlaveHanleStates(LPC_I2C, CodeStatus, TransferCfg);
				if (I2C_CheckError(Ret)) {
					goto s_error;
				}
				else if ((Ret & I2C_STA_STO_RECV) || (Ret & I2C_SEND_END)) {
					goto s_end_stage;
				}
			}
		}

s_end_stage:
		/* Clear AA bit to disable ACK on I2C bus */
		LPC_I2C->CONCLR = I2C_I2CONCLR_AAC;

		/* Check if there's no error during operation
		 * Update status
		 */
		TransferCfg->status = CodeStatus | I2C_SETUP_STATUS_DONE;
		return SUCCESS;

s_error:
		/* Clear AA bit to disable ACK on I2C bus */
		LPC_I2C->CONCLR = I2C_I2CONCLR_AAC;

		/* Update status */
		TransferCfg->status = CodeStatus;
		return ERROR;
	}

	else if (Opt == I2C_TRANSFER_INTERRUPT) {
		I2C_SlaveComplete[I2C_Num] = false;
		/* Setup tx_rx data, callback and interrupt handler */
		i2cdat[I2C_Num].txrx_setup_slave = *TransferCfg;

		/* Set direction phase, read first */
		i2cdat[I2C_Num].dir = 1;

		/* Enable AA */
		LPC_I2C->CONSET = I2C_I2CONSET_AA;
		LPC_I2C->CONCLR = I2C_I2CONCLR_SIC | I2C_I2CONCLR_STAC;

		return SUCCESS;
	}

	return ERROR;
}

/* Get status of Master Transfer */
bool IP_I2C_Interrupt_MasterTransferComplete(I2C_ID_Type I2C_Num)
{
	bool retval;

	retval = I2C_MasterComplete[I2C_Num];

	I2C_MasterComplete[I2C_Num] = false;

	return retval;
}

/* Get status of Slave Transfer */
bool IP_I2C_Interrupt_SlaveTransferComplete(I2C_ID_Type I2C_Num)
{
	bool retval;

	retval = I2C_SlaveComplete[I2C_Num];

	I2C_SlaveComplete[I2C_Num] = false;

	return retval;
}

/* Set Own slave address in I2C peripheral corresponding to	parameter specified in OwnSlaveAddrConfigStruct */
void IP_I2C_SetOwnSlaveAddr(IP_I2C_001_Type *LPC_I2C, I2C_OWNSLAVEADDR_CFG_Type *OwnSlaveAddrConfigStruct)
{
	uint32_t tmp;

	tmp = (((uint32_t) (OwnSlaveAddrConfigStruct->SlaveAddr_7bit << 1))	\
		   | ((OwnSlaveAddrConfigStruct->GeneralCallState == ENABLE) ? 0x01 : 0x00)) & I2C_I2ADR_BITMASK;
	switch (OwnSlaveAddrConfigStruct->SlaveAddrChannel) {
	case 0:
		LPC_I2C->ADR0 = tmp;
		LPC_I2C->MASK[0] =
			I2C_I2MASK_MASK((uint32_t) (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
		break;

	case 1:
		LPC_I2C->ADR1 = tmp;
		LPC_I2C->MASK[1] = I2C_I2MASK_MASK((uint32_t) (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
		break;

	case 2:
		LPC_I2C->ADR2 = tmp;
		LPC_I2C->MASK[2] = I2C_I2MASK_MASK((uint32_t) (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
		break;

	case 3:
		LPC_I2C->ADR3 = tmp;
		LPC_I2C->MASK[3] = I2C_I2MASK_MASK((uint32_t) (OwnSlaveAddrConfigStruct->SlaveAddrMaskValue));
		break;
	}
}
