/*
 * @brief LPC18xx/43xx ethernet driver
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

#ifndef __ENET_18XX_43XX_H_
#define __ENET_18XX_43XX_H_

#include "chip.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup ENET_18XX_43XX CHIP: LPC18xx/43xx Ethernet driver
 * @ingroup CHIP_18XX_43XX_Drivers
 * @{
 */

/** @defgroup ENET_18XX_43XX_OPTIONS CHIP: LPC18xx/43xx Ethernet driver build options
 * @ingroup ENET_18XX_43XX CHIP_18XX_43XX_DRIVER_OPTIONS
 * The ethernet driver has options that configure it's operation at build-time.<br/>
 * USE_RMII:
 * - When defined, the driver will be built for RMII operation.
 * - When not defined, the driver will be built for MII operation.
 * <br/><p>
 * For more information on driver options see @ref LPCOPEN_DESIGN_ARPPROACH<br/>
 * @{
 */

/**
 * @}
 */

/**
 * @brief	Initialize ethernet interface
 * @return	Nothing
 * Performs basic initialization of the ethernet interface in a default
 * state. This is enough to place the interface in a usable state, but
 * may require more setup outside this function.
 */
void Chip_ENET_Init(void);

/**
 * @brief	De-initialize the ethernet interface
 * @return	Nothing
 */
void Chip_ENET_DeInit(void);

/**
 * @brief	Resets the ethernet interface
 * @return	Nothing
 * Resets the ethernet interface. This should be called prior to
 * Chip_ENET_Init with a small delay after this call.
 */
STATIC INLINE void Chip_ENET_Reset(void)
{
	IP_ENET_Reset(LPC_ETHERNET);
}

/**
 * @brief	Sets the address of the interface
 * @param	macAddr	: Pointer to the 6 bytes used for the MAC address
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_SetADDR(const uint8_t *macAddr)
{
	IP_ENET_SetADDR(LPC_ETHERNET, macAddr);
}

/**
 * @brief	Sets up the PHY link clock divider and PHY address
 * @param	div		: Divider value, may vary per chip
 * @param	addr	: PHY address, used with MII read and write
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_Setup_MII(uint32_t div, uint8_t addr)
{
	IP_ENET_SetupMII(LPC_ETHERNET, div, addr);
}

/**
 * @brief	Starts a PHY write via the MII
 * @param	reg		: PHY register to write
 * @param	data	: Data to write to PHY register
 * @return	Nothing
 * Start a PHY write operation. Does not block, requires calling
 * IP_ENET_IsMIIBusy to determine when write is complete.
 */
STATIC INLINE void Chip_ENET_Start_MII_Write(uint8_t reg, uint16_t data)
{
	IP_ENET_StartMIIWrite(LPC_ETHERNET, reg, data);
}

/**
 * @brief	Starts a PHY read via the MII
 * @param	reg	: PHY register to read
 * @return	Nothing
 * Start a PHY read operation. Does not block, requires calling
 * IP_ENET_IsMIIBusy to determine when read is complete and calling
 * IP_ENET_ReadMIIData to get the data.
 */
STATIC INLINE void Chip_ENET_Start_MII_Read(uint8_t reg)
{
	IP_ENET_StartMIIRead(LPC_ETHERNET, reg);
}

/**
 * @brief	Returns MII link (PHY) busy status
 * @return	Returns true if busy, otherwise false
 */
STATIC INLINE bool Chip_ENET_Is_MII_Busy(void)
{
	return IP_ENET_IsMIIBusy(LPC_ETHERNET);
}

/**
 * @brief	Returns the value read from the PHY
 * @return	Read value from PHY
 */
STATIC INLINE uint16_t Chip_ENET_Read_MII_Data(void)
{
	return IP_ENET_ReadMIIData(LPC_ETHERNET);
}

/**
 * @brief	Enables or disables ethernet transmit
 * @param	Enable	: true to enable transmit, false to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_TX_Enable(bool Enable)
{
	IP_ENET_TXEnable(LPC_ETHERNET, Enable);
}

/**
 * @brief	Enables or disables ethernet packet reception
 * @param	Enable	: true to enable receive, false to disable
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_RX_Enable(bool Enable)
{
	IP_ENET_RXEnable(LPC_ETHERNET, Enable);
}

/**
 * @brief	Sets full or half duplex for the interface
 * @param	full	: true to selected full duplex, false for half
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_Set_Duplex(bool full)
{
	IP_ENET_SetDuplex(LPC_ETHERNET, full);
}

/**
 * @brief	Sets speed for the interface
 * @param	speed100	: true to select 100Mbps mode, false for 10Mbps
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_Set_Speed(bool speed100)
{
	IP_ENET_SetSpeed(LPC_ETHERNET, speed100);
}

/**
 * @brief	Configures the initial ethernet descriptors
 * @param	pTXDescs	: Pointer to TX descriptor list
 * @param	pRXDescs	: Pointer to RX descriptor list
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_InitDescriptors(
	IP_ENET_001_ENHTXDESC_Type *pTXDescs, IP_ENET_001_ENHRXDESC_Type *pRXDescs)
{
	IP_ENET_InitDescriptors(LPC_ETHERNET, pTXDescs, pRXDescs);
}

/**
 * @brief	Starts receive polling of RX descriptors
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_RXStart(void)
{
	IP_ENET_RXStart(LPC_ETHERNET);
}

/**
 * @brief	Starts transmit polling of TX descriptors
 * @return	Nothing
 */
STATIC INLINE void Chip_ENET_TXStart(void)
{
	IP_ENET_TXStart(LPC_ETHERNET);
}

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __ENET_18XX_43XX_H_ */
