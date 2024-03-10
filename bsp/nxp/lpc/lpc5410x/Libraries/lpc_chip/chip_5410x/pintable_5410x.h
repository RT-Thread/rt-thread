/*
 * @brief LPC5410x enhanced boot block
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

#ifndef __PINTABLE_5410X_H_
#define __PINTABLE_5410X_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup PINTAB_5410X CHIP: LPC5410X Enhanced boot block support
 * @ingroup CHIP_5410X_DRIVERS
 * @{
 */

/**
 * @brief LPC5410X Pin table structure used for enhanced boot block support
 */
struct PINTABLE {
	/* pin table marker: Should be 0xFEEDA5A5 */
	uint32_t marker;
	/* img_type:
	    0    = Normal image check IRQ line to halt boot
	    1    = Wait for AP to send SH_CMD_BOOT command
	    2    = Boot image with no AP checks
	    3    = No CRC or AP checks needed. Used during development */
	uint8_t img_type;
	/* ifSel: Interface selection for host
	    (0,=AUTODETECT, 1=I2C0, 2=I2C1, 3=I2C2, 4=SPI0, 5=SPI1) */
	uint8_t ifSel;
	/* hostIrqPortPin:	Host IRQ port (bits 7:5) and pins (bits 4:0) */
	uint8_t hostIrqPortPin;
	/* hostMisoPortPin:	SPI MISO port (bits 7:5) and pins (bits 4:0) */
	uint8_t hostMisoPortPin;
	/* hostMosiPortPin:	SPI MOSI port (bits 7:5) and pins (bits 4:0) */
	uint8_t hostMosiPortPin;
	/* hostSselPortPin:	SPI SEL port (bits 7:5) and pins (bits 4:0) */
	uint8_t hostSselPortPin;
	/* hostSckPortPin:	SPI SCK port (bits 7:5) and pins (bits 4:0) */
	uint8_t hostSckPortPin;
	/* xorVal: XOR value of the 7 bytes above */
	uint8_t xorVal;
	/* CRC32 length and value fields */
	uint32_t crc32_len;
	uint32_t crc32_val;
	/* Application image version number */
	uint32_t version;
};

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __PINTAB_5410X_H_ */
