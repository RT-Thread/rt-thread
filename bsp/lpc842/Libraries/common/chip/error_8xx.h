/*
 * @brief Error code returned by LPC8xx Boot ROM drivers/library functions
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

#ifndef __ERROR_8XX_H__
#define __ERROR_8XX_H__

/** @defgroup ROMAPI_ERRORCODES_8XX CHIP: LPC8xx ROM API error codes
 * @ingroup ROMAPI_8XX
 * @{
 */

/** Error code returned by Boot ROM drivers/library functions
*
*  Error codes are a 32-bit value with :
*      - The 16 MSB contains the peripheral code number
*      - The 16 LSB contains an error code number associated to that peripheral
*
*/
typedef enum
{
  /**\b 0x00000000*/ LPC_OK = 0,		/**< enum value returned on Successful completion */
  /**\b 0x00000001*/ LPC_ERROR,			/**< enum value returned on general error (I2C) */

  /* ISP related errors */
  ERR_ISP_BASE = 0x00000000,
  /**\b 0x00000001*/ ERR_ISP_INVALID_COMMAND = ERR_ISP_BASE + 1,
  /**\b 0x00000002*/ ERR_ISP_SRC_ADDR_ERROR,			/*!< Source address not on word boundary */
  /**\b 0x00000003*/ ERR_ISP_DST_ADDR_ERROR,			/*!< Destination address not on word or 256 byte boundary */
  /**\b 0x00000004*/ ERR_ISP_SRC_ADDR_NOT_MAPPED,
  /**\b 0x00000005*/ ERR_ISP_DST_ADDR_NOT_MAPPED,
  /**\b 0x00000006*/ ERR_ISP_COUNT_ERROR,				/*!< Byte count is not multiple of 4 or is not a permitted value */
  /**\b 0x00000007*/ ERR_ISP_INVALID_SECTOR,
  /**\b 0x00000008*/ ERR_ISP_SECTOR_NOT_BLANK,
  /**\b 0x00000009*/ ERR_ISP_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
  /**\b 0x0000000A*/ ERR_ISP_COMPARE_ERROR,
  /**\b 0x0000000B*/ ERR_ISP_BUSY,						/*!< Flash programming hardware interface is busy */
  /**\b 0x0000000C*/ ERR_ISP_PARAM_ERROR,				/*!< Insufficient number of parameters */
  /**\b 0x0000000D*/ ERR_ISP_ADDR_ERROR,				/*!< Address not on word boundary */
  /**\b 0x0000000E*/ ERR_ISP_ADDR_NOT_MAPPED,
  /**\b 0x0000000F*/ ERR_ISP_CMD_LOCKED,				/*!< Command is locked */
  /**\b 0x00000010*/ ERR_ISP_INVALID_CODE,				/*!< Unlock code is invalid */
  /**\b 0x00000011*/ ERR_ISP_INVALID_BAUD_RATE,
  /**\b 0x00000012*/ ERR_ISP_INVALID_STOP_BIT,
  /**\b 0x00000013*/ ERR_ISP_CODE_READ_PROTECTION_ENABLED,

  /* I2C related errors */
  ERR_I2C_BASE = 0x00060000,
  /**\b 0x00060001*/ ERR_I2C_NAK = ERR_I2C_BASE + 1,		/*!< NAK */
  /**\b 0x00060002*/ ERR_I2C_BUFFER_OVERFLOW,				/*!< Buffer overflow */
  /**\b 0x00060003*/ ERR_I2C_BYTE_COUNT_ERR,				/*!< Byte count error */
  /**\b 0x00060004*/ ERR_I2C_LOSS_OF_ARBRITRATION,			/*!< Loss of arbitration */
  /**\b 0x00060005*/ ERR_I2C_SLAVE_NOT_ADDRESSED,			/*!< Slave not addressed */
  /**\b 0x00060006*/ ERR_I2C_LOSS_OF_ARBRITRATION_NAK_BIT,	/*!< Loss arbritation NAK */
  /**\b 0x00060007*/ ERR_I2C_GENERAL_FAILURE,				/*!< General failure */
  /**\b 0x00060008*/ ERR_I2C_REGS_SET_TO_DEFAULT,			/*!< Set to default */
  /**\b 0x00060009*/ ERR_I2C_TIMEOUT,						/*!< I2C Timeout */

  /* UART related errors */
  /**\b 0x00080001*/ ERR_NO_ERROR = LPC_OK,					/*!< Receive is busy */
  ERR_UART_BASE = 0x00080000,
  /**\b 0x00080001*/ ERR_UART_RXD_BUSY = ERR_UART_BASE + 1,	/*!< Receive is busy */
  /**\b 0x00080002*/ ERR_UART_TXD_BUSY,						/*!< Transmit is busy */
  /**\b 0x00080003*/ ERR_UART_OVERRUN_FRAME_PARITY_NOISE,	/*!< Overrun, Frame, Parity , Receive Noise error */
  /**\b 0x00080004*/ ERR_UART_UNDERRUN,						/*!< Underrun */
  /**\b 0x00080005*/ ERR_UART_PARAM,						/*!< Parameter error */
} ErrorCode_t;

/**
 * @}
 */

#endif /* __ERROR_8XX_H__ */
