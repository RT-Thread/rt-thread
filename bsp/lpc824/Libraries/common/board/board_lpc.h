/*
 * @brief NXP LPCXpresso LPC824 board file
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

#ifndef __BOARD_H_
#define __BOARD_H_

#include "chip.h"
/* board_api.h is included at the bottom of this file after DEBUG setup */

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BOARD_NXP_LPCXPRESSO_824 NXP LPC824 LPCXpresso board support software API functions
 * @ingroup LPCOPEN_8XX_BOARD_LPCXPRESSO_824
 * The board support software API functions provide some simple abstracted
 * functions used across multiple LPCOpen board examples. See @ref BOARD_COMMON_API
 * for the functions defined by this board support layer.<br>
 * @{
 */

/** @defgroup LPCOPEN_8XX_BOARD_LPCXPRESSO_824_OPTIONS BOARD: LPC824 LPCXpresso board build options
 * This board has options that configure its operation at build-time.<br>
 * @{
 */

/** Define the frequency in Hz, of the main oscillator (from Xtal) 
 * Note that it only takes effect if main oscillator is selected as clock source
 */
#define MAIN_OSC_XTAL_FREQ_HZ		12000000
/** Define the frequency in Hz, of the external clock input.
 * Note that it only takes effect if external clock is selected as clock source
 */
#define EXT_CLOCK_IN_FREQ_HZ		0

//#define USE_IRC_AS_ROOT_CLOCK /*注释掉使用外部晶体 打开定义则是使用内部IRC*/

#define BOARD_LED_CNT 8
#define BOARD_KEY_CNT 3

typedef enum _enum_boardKeys
{
	BOARD_KEY_0 = 0,
	BOARD_KEY_1 = 1,
	BOARD_KEY_2 = 2,
}enum_boardKeys;

// define LED bits (bit <--> pin on port 0) only if in board.c file
#ifdef  _BOARD_C_
static const uint8_t ledBits[BOARD_LED_CNT] = {7, 13, 16, 17, 19, 27, 28, 18};
static const uint8_t cs_keyBits[BOARD_KEY_CNT] = {12, 4 , 1};
static const uint8_t cs_keyIoConNdce[BOARD_KEY_CNT] = {IOCON_PIO12, IOCON_PIO4, IOCON_PIO1};
#endif
 
/** Define DEBUG_ENABLE to enable IO via the DEBUGSTR, DEBUGOUT, and
    DEBUGIN macros. If not defined, DEBUG* functions will be optimized
	out of the code at build time.
 */
#define DEBUG_ENABLE

/** Define DEBUG_SEMIHOSTING along with DEBUG_ENABLE to enable IO support
    via semihosting. You may need to use a C library that supports
	semihosting with this option.
 */
//#define DEBUG_SEMIHOSTING

/** Board UART used for debug output and input using the DEBUG* macros. This
    is also the port used for Board_UARTPutChar, Board_UARTGetChar, and
	Board_UARTPutSTR functions. Although you can setup multiple UARTs here,
	the board code only supoprts UART0 in the Board_UART_Init() fucntion,
	so be sure to change it there too if not using UART0.
 */
#define DEBUG_UART LPC_USART1

/**
 * @}
 */

/* Board name */
#define BOARD_NXP_LPCXPRESSO_824


#include "board_api.h"

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H_ */
