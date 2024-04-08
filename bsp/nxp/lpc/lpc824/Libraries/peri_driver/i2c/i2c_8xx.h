/*
 * @brief LPC15xx I2C driver
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2014
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

#ifndef __I2C_COMMON_8XX_H_
#define __I2C_COMMON_8XX_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup I2C_15XX CHIP: LPC15xx I2C driver
 * @ingroup CHIP_15XX_Drivers
 * @{
 */

/**
 * @brief I2C register block structure
 */
typedef struct {					/* I2C0 Structure         */
	__IO uint32_t CFG;				/*!< I2C Configuration Register common for Master, Slave and Monitor */
	__IO uint32_t STAT;				/*!< I2C Status Register common for Master, Slave and Monitor */
	__IO uint32_t INTENSET;			/*!< I2C Interrupt Enable Set Register common for Master, Slave and Monitor */
	__O  uint32_t INTENCLR;			/*!< I2C Interrupt Enable Clear Register common for Master, Slave and Monitor */
	__IO uint32_t TIMEOUT;			/*!< I2C Timeout value Register */
	__IO uint32_t CLKDIV;			/*!< I2C Clock Divider Register */
	__I  uint32_t INTSTAT;			/*!< I2C Interrupt Status Register */
	__I  uint32_t RESERVED0;        
	__IO uint32_t MSTCTL;			/*!< I2C Master Control Register */
	__IO uint32_t MSTTIME;			/*!< I2C Master Time Register for SCL */
	__IO uint32_t MSTDAT;			/*!< I2C Master Data Register */
	__I  uint32_t RESERVED1[5];     
	__IO uint32_t SLVCTL;			/*!< I2C Slave Control Register */
	__IO uint32_t SLVDAT;			/*!< I2C Slave Data Register */
	__IO uint32_t SLVADR[4];		/*!< I2C Slave Address Registers */
	__IO uint32_t SLVQUAL0;			/*!< I2C Slave Address Qualifier 0 Register */
	__I  uint32_t RESERVED2[9];     
	__I  uint32_t MONRXDAT;			/*!< I2C Monitor Data Register */
} LPC_I2C_T;

/* Reserved bits masks for registers */
#define I2C_CFG_RESERVED            (~0x1f)
#define I2C_STAT_RESERVED           ((1<<5)|(1<<7)|(0xf<<20)|(0x3fu<<26))
#define I2C_INTENSET_RESERVED       ((7<<1)|(1<<5)|(1<<7)|(3<<9)|(7<<12)|(1<<18)|(0xf<<20)|(0x3fu<<26))
#define I2C_INTENCLR_RESERVED       ((7<<1)|(1<<5)|(1<<7)|(3<<9)|(7<<12)|(1<<18)|(0xf<<20)|(0x3fu<<26))
#define I2C_TIMEOUT_RESERVED        0xffff0000
#define I2C_CLKDIV_RESERVED         0xffff0000
#define I2C_INTSTAT_RESERVED        ((7<<1)|(1<<5)|(1<<7)|(3<<9)|(7<<12)|(1<<18)|(0xf<<20)|(0x3fu<<26))
#define I2C_MSTCTL_RESERVED         (~7)
#define I2C_MSTTIME_RESERVED        (~0x7f)
#define I2C_MSTDAT_RESERVED         (~0xff)
#define I2C_SLVCTL_RESERVED         (~3)
#define I2C_SLVDAT_RESERVED         (~0xff)
#define I2C_SLVADR_RESERVED         (~0xff)
#define I2C_SLVQUAL0_RESERVED       (~0xff)

/*
 * @brief I2C Configuration register Bit definition
 */
#define I2C_CFG_MSTEN               (1 << 0)			/*!< Master Enable/Disable Bit */
#define I2C_CFG_SLVEN               (1 << 1)			/*!< Slave Enable/Disable Bit */
#define I2C_CFG_MONEN               (1 << 2)			/*!< Monitor Enable/Disable Bit */
#define I2C_CFG_TIMEOUTEN           (1 << 3)			/*!< Timeout Enable/Disable Bit */
#define I2C_CFG_MONCLKSTR           (1 << 4)			/*!< Monitor Clock Stretching Bit */
#define I2C_CFG_MASK                ((uint32_t) 0x1F)	/*!< Configuration register Mask */

/*
 * @brief I2C Status register Bit definition
 */
#define I2C_STAT_MSTPENDING         (1 << 0)			/*!< Master Pending Status Bit */
#define I2C_STAT_MSTSTATE           (0x7 << 1)			/*!< Master State Code */
#define I2C_STAT_MSTRARBLOSS        (1 << 4)			/*!< Master Arbitration Loss Bit */
#define I2C_STAT_MSTSTSTPERR        (1 << 6)			/*!< Master Start Stop Error Bit */
#define I2C_STAT_SLVPENDING         (1 << 8)			/*!< Slave Pending Status Bit */
#define I2C_STAT_SLVSTATE           (0x3 << 9)			/*!< Slave State Code */
#define I2C_STAT_SLVNOTSTR          (1 << 11)			/*!< Slave not stretching Clock Bit */
#define I2C_STAT_SLVIDX             (0x3 << 12)			/*!< Slave Address Index */
#define I2C_STAT_SLVSEL             (1 << 14)			/*!< Slave Selected Bit */
#define I2C_STAT_SLVDESEL           (1 << 15)			/*!< Slave Deselect Bit */
#define I2C_STAT_MONRDY             (1 << 16)			/*!< Monitor Ready Bit */
#define I2C_STAT_MONOV              (1 << 17)			/*!< Monitor Overflow Flag */
#define I2C_STAT_MONACTIVE          (1 << 18)			/*!< Monitor Active Flag */
#define I2C_STAT_MONIDLE            (1 << 19)			/*!< Monitor Idle Flag */
#define I2C_STAT_EVENTTIMEOUT       (1 << 24)			/*!< Event Timeout Interrupt Flag */
#define I2C_STAT_SCLTIMEOUT         (1 << 25)			/*!< SCL Timeout Interrupt Flag */

#define I2C_STAT_MSTCODE_IDLE       (0)					/*!< Master Idle State Code */
#define I2C_STAT_MSTCODE_RXREADY    (1)					/*!< Master Receive Ready State Code */
#define I2C_STAT_MSTCODE_TXREADY    (2)					/*!< Master Transmit Ready State Code */
#define I2C_STAT_MSTCODE_NACKADR    (3)					/*!< Master NACK by slave on address State Code */
#define I2C_STAT_MSTCODE_NACKDAT    (4)					/*!< Master NACK by slave on data State Code */

#define I2C_STAT_SLVCODE_ADDR       (0)					/*!< Master Idle State Code */
#define I2C_STAT_SLVCODE_RX         (1)					/*!< Received data is available Code */
#define I2C_STAT_SLVCODE_TX         (2)					/*!< Data can be transmitted Code */

/*
 * @brief I2C Interrupt Enable Set register Bit definition
 */
#define I2C_INTENSET_MSTPENDING     (1 << 0)			/*!< Master Pending Interrupt Enable Bit */
#define I2C_INTENSET_MSTRARBLOSS    (1 << 4)			/*!< Master Arbitration Loss Interrupt Enable Bit */
#define I2C_INTENSET_MSTSTSTPERR    (1 << 6)			/*!< Master Start Stop Error Interrupt Enable Bit */
#define I2C_INTENSET_SLVPENDING     (1 << 8)			/*!< Slave Pending Interrupt Enable Bit */
#define I2C_INTENSET_SLVNOTSTR      (1 << 11)			/*!< Slave not stretching Clock Interrupt Enable Bit */
#define I2C_INTENSET_SLVDESEL       (1 << 15)			/*!< Slave Deselect Interrupt Enable Bit */
#define I2C_INTENSET_MONRDY         (1 << 16)			/*!< Monitor Ready Interrupt Enable Bit */
#define I2C_INTENSET_MONOV          (1 << 17)			/*!< Monitor Overflow Interrupt Enable Bit */
#define I2C_INTENSET_MONIDLE        (1 << 19)			/*!< Monitor Idle Interrupt Enable Bit */
#define I2C_INTENSET_EVENTTIMEOUT   (1 << 24)			/*!< Event Timeout Interrupt Enable Bit */
#define I2C_INTENSET_SCLTIMEOUT     (1 << 25)			/*!< SCL Timeout Interrupt Enable Bit */

/*
 * @brief I2C Interrupt Enable Clear register Bit definition
 */
#define I2C_INTENCLR_MSTPENDING     (1 << 0)			/*!< Master Pending Interrupt Clear Bit */
#define I2C_INTENCLR_MSTRARBLOSS    (1 << 4)			/*!< Master Arbitration Loss Interrupt Clear Bit */
#define I2C_INTENCLR_MSTSTSTPERR    (1 << 6)			/*!< Master Start Stop Error Interrupt Clear Bit */
#define I2C_INTENCLR_SLVPENDING     (1 << 8)			/*!< Slave Pending Interrupt Clear Bit */
#define I2C_INTENCLR_SLVNOTSTR      (1 << 11)			/*!< Slave not stretching Clock Interrupt Clear Bit */
#define I2C_INTENCLR_SLVDESEL       (1 << 15)			/*!< Slave Deselect Interrupt Clear Bit */
#define I2C_INTENCLR_MONRDY         (1 << 16)			/*!< Monitor Ready Interrupt Clear Bit */
#define I2C_INTENCLR_MONOV          (1 << 17)			/*!< Monitor Overflow Interrupt Clear Bit */
#define I2C_INTENCLR_MONIDLE        (1 << 19)			/*!< Monitor Idle Interrupt Clear Bit */
#define I2C_INTENCLR_EVENTTIMEOUT   (1 << 24)			/*!< Event Timeout Interrupt Clear Bit */
#define I2C_INTENCLR_SCLTIMEOUT     (1 << 25)			/*!< SCL Timeout Interrupt Clear Bit */

/*
 * @brief I2C TimeOut Value Macro
 */
#define I2C_TIMEOUT_VAL(n)          (((uint32_t) ((n) - 1) & 0xFFF0) | 0x000F)	/*!< Macro for Timeout value register */

/*
 * @brief I2C Interrupt Status register Bit definition
 */
#define I2C_INTSTAT_MSTPENDING      (1 << 0)			/*!< Master Pending Interrupt Status Bit */
#define I2C_INTSTAT_MSTRARBLOSS     (1 << 4)			/*!< Master Arbitration Loss Interrupt Status Bit */
#define I2C_INTSTAT_MSTSTSTPERR     (1 << 6)			/*!< Master Start Stop Error Interrupt Status Bit */
#define I2C_INTSTAT_SLVPENDING      (1 << 8)			/*!< Slave Pending Interrupt Status Bit */
#define I2C_INTSTAT_SLVNOTSTR       (1 << 11)			/*!< Slave not stretching Clock Interrupt Status Bit */
#define I2C_INTSTAT_SLVDESEL        (1 << 15)			/*!< Slave Deselect Interrupt Status Bit */
#define I2C_INTSTAT_MONRDY          (1 << 16)			/*!< Monitor Ready Interrupt Status Bit */
#define I2C_INTSTAT_MONOV           (1 << 17)			/*!< Monitor Overflow Interrupt Status Bit */
#define I2C_INTSTAT_MONIDLE         (1 << 19)			/*!< Monitor Idle Interrupt Status Bit */
#define I2C_INTSTAT_EVENTTIMEOUT    (1 << 24)			/*!< Event Timeout Interrupt Status Bit */
#define I2C_INTSTAT_SCLTIMEOUT      (1 << 25)			/*!< SCL Timeout Interrupt Status Bit */

/*
 * @brief I2C Master Control register Bit definition
 */
#define I2C_MSTCTL_MSTCONTINUE      (1 << 0)			/*!< Master Continue Bit */
#define I2C_MSTCTL_MSTSTART         (1 << 1)			/*!< Master Start Control Bit */
#define I2C_MSTCTL_MSTSTOP          (1 << 2)			/*!< Master Stop Control Bit */
#define I2C_MSTCTL_MSTDMA           (1 << 3)			/*!< Master DMA Enable Bit */

/*
 * @brief I2C Master Time Register Field definition
 */
#define I2C_MSTTIME_MSTSCLLOW       (0x07 << 0)			/*!< Master SCL Low Time field */
#define I2C_MSTTIME_MSTSCLHIGH      (0x07 << 4)			/*!< Master SCL High Time field */

/*
 * @brief I2C Master Data Mask
 */
#define I2C_MSTDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Master data mask */

/*
 * @brief I2C Slave Control register Bit definition
 */
#define I2C_SLVCTL_SLVCONTINUE      (1 << 0)			/*!< Slave Continue Bit */
#define I2C_SLVCTL_SLVNACK          (1 << 1)			/*!< Slave NACK Bit */
#define I2C_SLVCTL_SLVDMA           (1 << 3)			/*!< Slave DMA Enable Bit */

/*
 * @brief I2C Slave Data Mask
 */
#define I2C_SLVDAT_DATAMASK         ((uint32_t) 0x00FF << 0)	/*!< Slave data mask */

/*
 * @brief I2C Slave Address register Bit definition
 */
#define I2C_SLVADR_SADISABLE        (1 << 0)			/*!< Slave Address n Disable Bit */
#define I2C_SLVADR_SLVADR           (0x7F << 1)			/*!< Slave Address field */
#define I2C_SLVADR_MASK             ((uint32_t) 0x00FF)	/*!< Slave Address Mask */

/*
 * @brief I2C Slave Address Qualifier 0 Register Bit definition
 */
#define I2C_SLVQUAL_QUALMODE0       (1 << 0)			/*!< Slave Qualifier Mode Enable Bit */
#define I2C_SLVQUAL_SLVQUAL0        (0x7F << 1)			/*!< Slave Qualifier Address for Address 0 */

/*
 * @brief I2C Monitor Data Register Bit definition
 */
#define I2C_MONRXDAT_DATA           (0xFF << 0)			/*!< Monitor Function Receive Data Field */
#define I2C_MONRXDAT_MONSTART       (1 << 8)			/*!< Monitor Received Start Bit */
#define I2C_MONRXDAT_MONRESTART     (1 << 9)			/*!< Monitor Received Repeated Start Bit */
#define I2C_MONRXDAT_MONNACK        (1 << 10)			/*!< Monitor Received Nack Bit */

/**
 * @brief	Initialize I2C Interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function enables the I2C clock for both the master and
 * slave interfaces of the given I2C peripheral. LPC_I2C1, LPC_I2C2 and
 * LPC_I2C3 are available only on LPC82X devices.
 */
void Chip_I2C_Init(LPC_I2C_T *pI2C);

/**
 * @brief	Shutdown I2C Interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function disables the I2C clock for both the master and
 * slave interfaces of the given I2C peripheral. Only LPC_I2C0 is available
 * on LPC81X devices.
 */
void Chip_I2C_DeInit(LPC_I2C_T *pI2C);

/**
 * @brief	Sets I2C Clock Divider registers
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	clkdiv	: Clock Divider value for I2C, value is between (1 - 65536)
 * @return	Nothing
 * @note	The clock to I2C block is determined by the following formula (I2C_PCLK
 *          is the frequency of the system clock): <br>
 *              I2C Clock Frequency = (I2C_PCLK)/clkdiv;
 */
static INLINE void Chip_I2C_SetClockDiv(LPC_I2C_T *pI2C, uint32_t clkdiv)
{
	if ((clkdiv >= 1) && (clkdiv <= 65536)) {
		pI2C->CLKDIV = clkdiv - 1;
	}
	else {
		pI2C->CLKDIV = 0;
	}
}

/**
 * @brief	Get I2C Clock Divider registers
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Clock Divider value
 * @note	Return the divider value for the I2C block
 *          It is the CLKDIV register value + 1
 */
static INLINE uint32_t Chip_I2C_GetClockDiv(LPC_I2C_T *pI2C)
{
	return (pI2C->CLKDIV & 0xFFFF) + 1;
}

/**
 * @brief	Enable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intEn	: ORed Value of I2C_INTENSET_* values to enable
 * @return	Nothing
 */
static INLINE void Chip_I2C_EnableInt(LPC_I2C_T *pI2C, uint32_t intEn)
{
	pI2C->INTENSET = intEn;
}

/**
 * @brief	Disable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intClr	: ORed Value of I2C_INTENSET_* values to disable
 * @return	Nothing
 */
static INLINE void Chip_I2C_DisableInt(LPC_I2C_T *pI2C, uint32_t intClr)
{
	pI2C->INTENCLR = intClr;
}

/**
 * @brief	Disable I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	intClr	: ORed Value of I2C_INTENSET_* values to disable
 * @return	Nothing
 * @note	It is recommended to use the Chip_I2C_DisableInt() function
 * instead of this function.
 */
static INLINE void Chip_I2C_ClearInt(LPC_I2C_T *pI2C, uint32_t intClr)
{
	Chip_I2C_DisableInt(pI2C, intClr);
}

/**
 * @brief	Returns pending I2C Interrupts
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	All pending interrupts, mask with I2C_INTENSET_* to determine specific interrupts
 */
static INLINE uint32_t Chip_I2C_GetPendingInt(LPC_I2C_T *pI2C)
{
	return pI2C->INTSTAT & ~I2C_INTSTAT_RESERVED;
}

/**
 * @}
 */

 
/** @defgroup I2CM_8XX CHIP: LPC8XX I2C master-only driver
 * @ingroup I2C_8XX
 * This driver only works in master mode. To describe the I2C transactions
 * following symbols are used in driver documentation.
 *
 * Key to symbols
 * ==============
 * S     (1 bit) : Start bit
 * P     (1 bit) : Stop bit
 * Rd/Wr (1 bit) : Read/Write bit. Rd equals 1, Wr equals 0.
 * A, NA (1 bit) : Acknowledge and Not-Acknowledge bit.
 * Addr  (7 bits): I2C 7 bit address. Note that this can be expanded as usual to
 *                 get a 10 bit I2C address.
 * Data  (8 bits): A plain data byte. Sometimes, I write DataLow, DataHigh
 *                 for 16 bit data.
 * [..]: Data sent by I2C device, as opposed to data sent by the host adapter.
 * @{
 */

/** I2CM_8XX_STATUS_TYPES I2C master transfer status types
 * @{
 */

#define I2CM_STATUS_OK              0x00		/*!< Requested Request was executed successfully. */
#define I2CM_STATUS_ERROR           0x01		/*!< Unknown error condition. */
#define I2CM_STATUS_NAK_ADR         0x02		/*!< No acknowledgement received from slave during address phase. */
#define I2CM_STATUS_BUS_ERROR       0x03		/*!< I2C bus error */
#define I2CM_STATUS_NAK_DAT			0x04		/*!< No acknowledgement received from slave during address phase. */
#define I2CM_STATUS_ARBLOST         0x05		/*!< Arbitration lost. */
#define I2CM_STATUS_BUSY            0xFF		/*!< I2C transmistter is busy. */

/**
 * @}
 */

/**
 * @brief Master transfer data structure definitions
 */
typedef struct {
	const uint8_t *txBuff;	/*!< Pointer to array of bytes to be transmitted */
	uint8_t *rxBuff;				/*!< Pointer memory where bytes received from I2C be stored */
	uint16_t txSz;					/*!< Number of bytes in transmit array,
									                if 0 only receive transfer will be carried on */
	uint16_t rxSz;					/*!< Number of bytes to received,
									                if 0 only transmission we be carried on */
	uint16_t status;				/*!< Status of the current I2C transfer */
	uint8_t slaveAddr;			/*!< 7-bit I2C Slave address */
} I2CM_XFER_T;

/**
 * @brief	Set up bus speed for LPC_I2C controller
 * @param	pI2C		: Pointer to selected I2C peripheral
 * @param	busSpeed	: I2C bus clock rate
 * @return	Nothing
 * @note	Per I2C specification the busSpeed should be
 *          @li 100000 for Standard mode
 *          @li 400000 for Fast mode
 *          @li 1000000 for Fast mode plus
 *          IOCON registers corresponding to I2C pads should be updated
 *          according to the bus mode.
 */
void Chip_I2CM_SetBusSpeed(LPC_I2C_T *pI2C, uint32_t busSpeed);

/**
 * @brief	Enable I2C Master interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note
 */
static INLINE void Chip_I2CM_Enable(LPC_I2C_T *pI2C)
{
	pI2C->CFG = (pI2C->CFG & I2C_CFG_MASK) | I2C_CFG_MSTEN;
}

/**
 * @brief	Disable I2C Master interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note
 */
static INLINE void Chip_I2CM_Disable(LPC_I2C_T *pI2C)
{
	pI2C->CFG = (pI2C->CFG & I2C_CFG_MASK) & ~I2C_CFG_MSTEN;
}

/**
 * @brief	Get I2C Status
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	I2C Status register value
 * @note	This function returns the value of the status register.
 */
static INLINE uint32_t Chip_I2CM_GetStatus(LPC_I2C_T *pI2C)
{
	return pI2C->STAT & ~I2C_STAT_RESERVED;
}

/**
 * @brief	Clear I2C status bits (master)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param clrStatus : Status bit to clear, ORed Value of I2C_STAT_MSTRARBLOSS and I2C_STAT_MSTSTSTPERR
 * @return	Nothing
 * @note	This function clears selected status flags.
 */
static INLINE void Chip_I2CM_ClearStatus(LPC_I2C_T *pI2C, uint32_t clrStatus)
{
	/* Clear Master Arbitration Loss and Start, Stop Error */
	pI2C->STAT = clrStatus & (I2C_STAT_MSTRARBLOSS | I2C_STAT_MSTSTSTPERR);
}

/**
 * @brief	Check if I2C Master is pending
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Returns TRUE if the Master is pending else returns FALSE
 * @note
 */
static INLINE bool Chip_I2CM_IsMasterPending(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_MSTPENDING) != 0;
}

/**
 * @brief	Get current state of the I2C Master
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Master State Code, a value in the range of 0 - 4
 * @note	After the Master is pending this state code tells the reason
 *        for Master pending.
 */
static INLINE uint32_t Chip_I2CM_GetMasterState(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_MSTSTATE) >> 1;
}

/**
 * @brief	Transmit START or Repeat-START signal on I2C bus
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function sets the controller to transmit START condition when
 *        the bus becomes free. This should be called only when master is pending.
 *				The function writes a complete value to Master Control register, ORing is not advised.
 */
static INLINE void Chip_I2CM_SendStart(LPC_I2C_T *pI2C)
{
	pI2C->MSTCTL = I2C_MSTCTL_MSTSTART;
}

/**
 * @brief	Transmit STOP signal on I2C bus
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function sets the controller to transmit STOP condition.
 *				This should be called only when master is pending. The function writes a
 *				complete value to Master Control register, ORing is not advised.
 */
static INLINE void Chip_I2CM_SendStop(LPC_I2C_T *pI2C)
{
	pI2C->MSTCTL = I2C_MSTCTL_MSTSTOP;
}

/**
 * @brief	Master Continue transfer operation
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function sets the master controller to continue transmission.
 *				This should be called only when master is pending. The function writes a
 *				complete value to Master Control register, ORing is not advised.
 */
static INLINE void Chip_I2CM_MasterContinue(LPC_I2C_T *pI2C)
{
	pI2C->MSTCTL = I2C_MSTCTL_MSTCONTINUE;
}

/**
 * @brief	Transmit a single data byte through the I2C peripheral (master)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	data	: Byte to transmit
 * @return	Nothing
 * @note	This function attempts to place a byte into the I2C Master
 *			Data Register
 *
 */
static INLINE void Chip_I2CM_WriteByte(LPC_I2C_T *pI2C, uint8_t data)
{
	pI2C->MSTDAT = (uint32_t) data;
}

/**
 * @brief	Read a single byte data from the I2C peripheral (master)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	A single byte of data read
 * @note	This function reads a byte from the I2C receive hold register
 *			regardless of I2C state.
 */
static INLINE uint8_t Chip_I2CM_ReadByte(LPC_I2C_T *pI2C)
{
	return (uint8_t) (pI2C->MSTDAT & I2C_MSTDAT_DATAMASK);
}

/**
 * @brief	Transfer state change handler
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	xfer	: Pointer to a I2CM_XFER_T structure see notes below
 * @return Returns non-zero value on completion of transfer. The @a status
 *         member of @a xfer structure contains the current status of the
 *         transfer at the end of the call.
 * @note
 * The parameter @a xfer should be same as the one passed to Chip_I2CM_Xfer()
 * routine. This function should be called from the I2C interrupt handler
 * only when a master interrupt occurs.
 */
uint32_t Chip_I2CM_XferHandler(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer);

/**
 * @brief	Transmit and Receive data in master mode
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	xfer	: Pointer to a I2CM_XFER_T structure see notes below
 * @return	Nothing
 * @note
 * The parameter @a xfer should have its member @a slaveAddr initialized
 * to the 7-Bit slave address to which the master will do the xfer, Bit0
 * to bit6 should have the address and Bit8 is ignored. During the transfer
 * no code (like event handler) must change the content of the memory
 * pointed to by @a xfer. The member of @a xfer, @a txBuff and @a txSz be
 * initialized to the memory from which the I2C must pick the data to be
 * transfered to slave and the number of bytes to send respectively, similarly
 * @a rxBuff and @a rxSz must have pointer to memory where data received
 * from slave be stored and the number of data to get from slave respectilvely.
 * Following types of transfers are possible:
 * - Write-only transfer: When @a rxSz member of @a xfer is set to 0.
 *
 *          S Addr Wr [A] txBuff0 [A] txBuff1 [A] ... txBuffN [A] P
 *
 *      - If I2CM_XFER_OPTION_IGNORE_NACK is set in @a options memeber
 *
 *          S Addr Wr [A] txBuff0 [A or NA] ... txBuffN [A or NA] P
 *
 * - Read-only transfer: When @a txSz member of @a xfer is set to 0.
 *
 *          S Addr Rd [A] [rxBuff0] A [rxBuff1] A ... [rxBuffN] NA P
 *
 *      - If I2CM_XFER_OPTION_LAST_RX_ACK is set in @a options memeber
 *
 *          S Addr Rd [A] [rxBuff0] A [rxBuff1] A ... [rxBuffN] A P
 *
 * - Read-Write transfer: When @a rxSz and @ txSz members of @a xfer are non-zero.
 *
 *          S Addr Wr [A] txBuff0 [A] txBuff1 [A] ... txBuffN [A]
 *              S Addr Rd [A] [rxBuff0] A [rxBuff1] A ... [rxBuffN] NA P
 *
 */
void Chip_I2CM_Xfer(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer);

/**
 * @brief	Transmit and Receive data in master mode
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	xfer	: Pointer to a I2CM_XFER_T structure see notes below
 * @return Returns non-zero value on succesful completion of transfer.
 * @note
 * This function operates same as Chip_I2CM_Xfer(), but is a blocking call.
 */
uint32_t Chip_I2CM_XferBlocking(LPC_I2C_T *pI2C, I2CM_XFER_T *xfer);

/**
 * @}
 */
 
 
/** @defgroup I2CS_8XX CHIP: LPC8XX I2C slave-only driver
 * @ingroup I2C_8XX
 * This driver only works in slave mode.
 * @{
 */

/** @brief I2C slave service start callback
 * This callback is called from the I2C slave handler when an I2C slave address is
 * received and needs servicing. It's used to indicate the start of a slave transfer
 * that will happen on the slave bus.
 */
typedef void (*I2CSlaveXferStart)(uint8_t addr);

/** @brief I2C slave send data callback
 * This callback is called from the I2C slave handler when an I2C slave address needs
 * data to send. Return 0 to NACK the master and terminate the transfer, or return
 * a non-0 value with the value to send in *data.
 */
typedef uint8_t (*I2CSlaveXferSend)(uint8_t *data);

/** @brief I2C slave receive data callback
 * This callback is called from the I2C slave handler when an I2C slave address has
 * receive data. Return 0 to NACK the master and terminate the transfer, or return
 * a non-0 value to continue the transfer.
 */
typedef uint8_t (*I2CSlaveXferRecv)(uint8_t data);

/** @brief I2C slave service done callback
 * This callback is called from the I2C slave handler when an I2C slave transfer is
 * completed. It's used to indicate the end of a slave transfer.
 */
typedef void (*I2CSlaveXferDone)(void);

/**
 * Slave transfer are performed using 3 callbacks. These 3 callbacks handle most I2C
 * slave transfer cases. When the slave is setup and a slave interrupt is receive
 * and processed with the Chip_I2CS_XferHandler() function in the I2C interrupt handler,
 * one of these 3 callbacks is called. The callbacks can be used for unsized transfers
 * from the master.
 *
 * When an address is received, the SlaveXferAddr() callback is called with the
 * received address. Only addresses enabled in the slave controller will be handled.
 * The slave controller can support up to 4 slave addresses.
 *
 * If the master is going to perform a read operation, the SlaveXferSend() callback
 * is called. Place the data byte to send in *data and return a non-0 value to the
 * caller, or return 0 to NACK the master. (Note the master ACKS/NACKS to slave
 * on reads, so this won't necessarily stop the slave transfer.)<br>
 *
 * If the master performs a write operation, the SlaveXferRecv() callback is called
 * with the received data. Return a non-0 value to the caller, or return 0 to NACK
 * the master.<br>
 *
 * Once the transfer completes, the SlaveXferDone() callback will be called.<br>
 */
typedef struct {
	I2CSlaveXferStart slaveStart;	/*!< Called when an matching I2C slave address is received */
	I2CSlaveXferSend slaveSend;		/*!< Called when a byte is needed to send to master */
	I2CSlaveXferRecv slaveRecv;		/*!< Called when a byte is received from master */
	I2CSlaveXferDone slaveDone;		/*!< Called when a slave transfer is complete */
} I2CS_XFER_T;

/**
 * @brief	Enable I2C slave interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	Do not call this function until the slave interface is fully configured.
 */
STATIC INLINE void Chip_I2CS_Enable(LPC_I2C_T *pI2C)
{
	pI2C->CFG = (pI2C->CFG & I2C_CFG_MASK) | I2C_CFG_SLVEN;
}

/**
 * @brief	Disable I2C slave interface
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 */
STATIC INLINE void Chip_I2CS_Disable(LPC_I2C_T *pI2C)
{
	pI2C->CFG = (pI2C->CFG & I2C_CFG_MASK) & ~I2C_CFG_SLVEN;
}

/**
 * @brief	Get I2C Status
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	I2C Status register value
 * @note	This function returns the value of the status register.
 */
STATIC INLINE uint32_t Chip_I2CS_GetStatus(LPC_I2C_T *pI2C)
{
	return pI2C->STAT & ~I2C_STAT_RESERVED;
}

/**
 * @brief	Clear I2C status bits (slave)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param clrStatus : Status bit to clear, must be I2C_STAT_SLVDESEL
 * @return	Nothing
 * @note	This function clears selected status flags.
 */
STATIC INLINE void Chip_I2CS_ClearStatus(LPC_I2C_T *pI2C, uint32_t clrStatus)
{
	pI2C->STAT = clrStatus & I2C_STAT_SLVDESEL;
}

/**
 * @brief	Check if I2C slave is pending
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Returns TRUE if the slave is pending else returns FALSE
 * @note
 */
STATIC INLINE bool Chip_I2CS_IsSlavePending(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_SLVPENDING) != 0;
}

/**
 * @brief	Check if I2C slave is selected
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Returns TRUE if the slave is is selected, otherwise FALSE
 * @note
 */
STATIC INLINE bool Chip_I2CS_IsSlaveSelected(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_SLVSEL) != 0;
}

/**
 * @brief	Check if I2C slave is deselected
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Returns TRUE if the slave is is deselected, otherwise FALSE
 * @note
 */
STATIC INLINE bool Chip_I2CS_IsSlaveDeSelected(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_SLVDESEL) != 0;
}

/**
 * @brief	Get current state of the I2C slave
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	slave State Code, a value of type I2C_STAT_SLVCODE_*
 * @note	After the slave is pending this state code tells the reason
 *        for slave pending.
 */
STATIC INLINE uint32_t Chip_I2CS_GetSlaveState(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_SLVSTATE) >> 9;
}

/**
 * @brief	Returns the current slave address match index
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	slave match index, 0 - 3
 */
STATIC INLINE uint32_t Chip_I2CS_GetSlaveMatchIndex(LPC_I2C_T *pI2C)
{
	return (pI2C->STAT & I2C_STAT_SLVIDX) >> 12;
}

/**
 * @brief	Slave Continue transfer operation (ACK)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function sets the slave controller to continue transmission.
 *				This should be called only when slave is pending. The function writes a
 *				complete value to slave Control register, ORing is not advised.
 */
STATIC INLINE void Chip_I2CS_SlaveContinue(LPC_I2C_T *pI2C)
{
	pI2C->SLVCTL = I2C_SLVCTL_SLVCONTINUE;
}

/**
 * @brief	Slave NACK operation
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	Nothing
 * @note	This function sets the slave controller to NAK the master.
 */
STATIC INLINE void Chip_I2CS_SlaveNACK(LPC_I2C_T *pI2C)
{
	pI2C->SLVCTL = I2C_SLVCTL_SLVNACK;
}

/**
 * @brief	Transmit a single data byte through the I2C peripheral (slave)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	data	: Byte to transmit
 * @return	Nothing
 * @note	This function attempts to place a byte into the I2C slave
 *			Data Register
 *
 */
STATIC INLINE void Chip_I2CS_WriteByte(LPC_I2C_T *pI2C, uint8_t data)
{
	pI2C->SLVDAT = (uint32_t) data;
}

/**
 * @brief	Read a single byte data from the I2C peripheral (slave)
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @return	A single byte of data read
 * @note	This function reads a byte from the I2C receive hold register
 *			regardless of I2C state.
 */
STATIC INLINE uint8_t Chip_I2CS_ReadByte(LPC_I2C_T *pI2C)
{
	return (uint8_t) (pI2C->SLVDAT & I2C_SLVDAT_DATAMASK);
}

/**
 * @brief	Set a I2C slave address for slave operation
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	slvNum	: Possible slave address number, between 0 - 3
 * @param	slvAddr	: Slave Address for the index (7-bits, bit 7 = 0)
 * @return	Nothing
 * @note	Setting a slave address also enables the slave address. Do
 * not 'pre-shift' the slave address.
 */
STATIC INLINE void Chip_I2CS_SetSlaveAddr(LPC_I2C_T *pI2C, uint8_t slvNum, uint8_t slvAddr)
{
	pI2C->SLVADR[slvNum] = (uint32_t) (slvAddr << 1);
}

/**
 * @brief	Return a I2C programmed slave address
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	slvNum	: Possible slave address number, between 0 - 3
 * @return	Nothing
 */
STATIC INLINE uint8_t Chip_I2CS_GetSlaveAddr(LPC_I2C_T *pI2C, uint8_t slvNum)
{
	return (pI2C->SLVADR[slvNum] >> 1) & 0x7F;
}

/**
 * @brief	Enable a I2C address
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	slvNum	: Possible slave address number, between 0 - 3
 * @return	Nothing
 */
STATIC INLINE void Chip_I2CS_EnableSlaveAddr(LPC_I2C_T *pI2C, uint8_t slvNum)
{
	pI2C->SLVADR[slvNum] = (pI2C->SLVADR[slvNum] & I2C_SLVADR_MASK) & ~I2C_SLVADR_SADISABLE;
}

/**
 * @brief	Disable a I2C address
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	slvNum	: Possible slave address number, between 0 - 3
 * @return	Nothing
 */
STATIC INLINE void Chip_I2CS_DisableSlaveAddr(LPC_I2C_T *pI2C, uint8_t slvNum)
{
	pI2C->SLVADR[slvNum] = (pI2C->SLVADR[slvNum] & I2C_SLVADR_MASK) | I2C_SLVADR_SADISABLE;
}

/**
 * @brief	Setup slave qialifier address
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	extend	: true to extend I2C slave detect address 0 range, or false to match to corresponding bits
 * @param	slvNum	: Slave address qualifier, see SLVQUAL0 register in User Manual
 * @return	Nothing
 * @note	Do not 'pre-shift' the slave address.
 */
STATIC INLINE void Chip_I2CS_SetSlaveQual0(LPC_I2C_T *pI2C, bool extend, uint8_t slvNum)
{
	slvNum = slvNum << 1;
	if (extend) {
		slvNum |= I2C_SLVQUAL_QUALMODE0;
	}

	pI2C->SLVQUAL0 = slvNum;
}

/**
 * @brief	Slave transfer state change handler
 * @param	pI2C	: Pointer to selected I2C peripheral
 * @param	xfers	: Pointer to a I2CS_MULTI_XFER_T structure see notes below
 * @return	Returns non-zero value on completion of transfer
 * @note	See @ref I2CS_XFER_T for more information on this function. When using
 * this function, the I2C_INTENSET_SLVPENDING and I2C_INTENSET_SLVDESEL interrupts
 * should be enabled and setup in the I2C interrupt handler to call this function
 * when they fire.
 */
uint32_t Chip_I2CS_XferHandler(LPC_I2C_T *pI2C, const I2CS_XFER_T *xfers);

/**
 * @}
 */

 
 #ifdef __cplusplus
}
#endif

#endif /* __I2C_COMMON_8XX_H_ */
