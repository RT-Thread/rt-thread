
/*
 * @brief NXP LPCXpresso LPC824 board file
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
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
 
// Must define _BOARD_C_ before ANY include
#define _BOARD_C_

#include "board_lpc.h"
#include "string.h"
#include <stdint.h>
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define BOARD_LED_CNT 8

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/* System oscillator rate and clock rate on the CLKIN pin */
const uint32_t OscRateIn = MAIN_OSC_XTAL_FREQ_HZ;
const uint32_t ExtRateIn = EXT_CLOCK_IN_FREQ_HZ;

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void Board_Key_Init(void)
{
	int i;
	LPC_IOCON_T *pIOCON = LPC_IOCON;
	for (i = 0; i < BOARD_KEY_CNT; i++) {
		Chip_GPIO_PinSetDIR(LPC_GPIO_PORT, 0, cs_keyBits[i], 0);
		pIOCON->PIO0[cs_keyIoConNdce[i]] = 0x80;	// weak pUp
	}
}

/* Initialize the LEDs on the NXP LPC824 LPCXpresso Board */
static void Board_LED_Init(void)
{
	int i;

	for (i = 0; i < BOARD_LED_CNT; i++) {
		Chip_GPIO_PinSetDIR(LPC_GPIO_PORT, 0, ledBits[i], 1);
		Chip_GPIO_PinSetState(LPC_GPIO_PORT, 0, ledBits[i], true);
	}
}

uint32_t Board_Key_GetKeyDown(uint32_t keyNdx)
{
	LPC_GPIO_T *pGP = LPC_GPIO_PORT;
 	return pGP->W[0][cs_keyBits[keyNdx]] == 0 ? 1 : 0;
}

/* Board Debug UART Initialisation function */
STATIC void Board_UART_Init(void)
{
	/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);

	/* Connect the TXD_O and RXD_I signals to port pins(P0.4, P0.0) */
	//Chip_SWM_DisableFixedPin(SWM_FIXED_XTALIN);
	//Chip_SWM_DisableFixedPin(SWM_FIXED_XTALOUT);
	
	Chip_SWM_DisableFixedPin(SWM_FIXED_ACMP_I1);
	Chip_SWM_DisableFixedPin(SWM_FIXED_ADC11);

	/* Enable UART Divider clock, divided by 1 */
	Chip_Clock_SetUARTClockDiv(1);

	/* Divided by 1 */
	if (DEBUG_UART == LPC_USART0) {

		Chip_SWM_MovablePinAssign(SWM_U0_TXD_O, 4);
		Chip_SWM_MovablePinAssign(SWM_U0_RXD_I, 0);
	} else if (DEBUG_UART == LPC_USART1) {
		Chip_SWM_MovablePinAssign(SWM_U1_TXD_O, 4);
		Chip_SWM_MovablePinAssign(SWM_U1_RXD_I, 0);
	} else {
		Chip_SWM_MovablePinAssign(SWM_U2_TXD_O, 4);
		Chip_SWM_MovablePinAssign(SWM_U2_RXD_I, 0);
	}

	/* Disable the clock to the Switch Matrix to save power */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
}

/* Initializes pin muxing for SPI1 interface - note that SystemInit() may
   already setup your pin muxing at system startup */
static void Init_SPI_PinMux(void)
{

	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_MovablePinAssign(SWM_SPI1_SSEL0_IO, 15);
	Chip_SWM_MovablePinAssign(SWM_SPI1_SCK_IO, 24);
	Chip_SWM_MovablePinAssign(SWM_SPI1_MISO_IO, 25);
	Chip_SWM_MovablePinAssign(SWM_SPI1_MOSI_IO, 26);
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);

}

/* Initializes pin muxing for I2C interface */
static void Init_I2C_PinMux(void)
{
	/* Enable the clock to the Switch Matrix */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SDA);
	Chip_SWM_EnableFixedPin(SWM_FIXED_I2C0_SCL);

	/* Enable Fast Mode Plus for I2C pins */
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO10, PIN_I2CMODE_FASTPLUS);
	Chip_IOCON_PinSetI2CMode(LPC_IOCON, IOCON_PIO11, PIN_I2CMODE_FASTPLUS);

	/* Disable the clock to the Switch Matrix to save power */
	Chip_Clock_DisablePeriphClock(SYSCTL_CLOCK_SWM);
}
/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Set the LED to the state of "On" */
void Board_LED_Set(uint8_t LEDNumber, bool On)
{
	if (LEDNumber < BOARD_LED_CNT) {
		Chip_GPIO_PinSetState(LPC_GPIO_PORT, 0, ledBits[LEDNumber], (bool) !On);
	}
}

/* Return the state of LEDNumber */
bool Board_LED_Test(uint8_t LEDNumber)
{
	bool state = false;

	if (LEDNumber < BOARD_LED_CNT) {
		state = (bool) !Chip_GPIO_PinGetState(LPC_GPIO_PORT, 0, ledBits[LEDNumber]);
	}

	return state;
}

/* Toggles the current state of a board LED */
void Board_LED_Toggle(uint8_t LEDNumber)
{
	if (LEDNumber < BOARD_LED_CNT) {
		Chip_GPIO_PinToggleState(LPC_GPIO_PORT, 0, ledBits[LEDNumber]);
	}
}

/*  Classic implementation of itoa -- integer to ASCII */
char *Board_itoa(int value, char *result, int base)
{
    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    if (base < 2 || base > 36) { *result = '\0'; return result; }
    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

/* Sends a character on the UART */
void Board_UARTPutChar(char ch)
{
#if defined(DEBUG_UART)
	Chip_UART_SendBlocking(DEBUG_UART, &ch, 1);
#endif
}

void Board_UARTPutTextChar(char ch)
{
#if defined(DEBUG_UART)
	static char prevChar = 0;
	if (ch == '\n' && prevChar != '\r')
	{
		prevChar = '\r';
		Chip_UART_SendBlocking(DEBUG_UART, &prevChar, 1);
		Chip_UART_SendBlocking(DEBUG_UART, &ch, 1);
	} else {
		Chip_UART_SendBlocking(DEBUG_UART, &ch, 1);
		prevChar = ch;
	}
#endif
}


/* Gets a character from the UART, returns EOF if no character is ready */
int Board_UARTGetChar(void)
{
#if defined(DEBUG_UART)
	uint8_t data;

	if (Chip_UART_ReadBlocking(DEBUG_UART, &data, 1) == 1) {
		Board_UARTPutChar(data);	// echo back the char
		return (int) data;
	}
#endif
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(const char *str)
{
#if defined(DEBUG_UART)
	while (*str != '\0') {
		Board_UARTPutTextChar(*str++);
	}
#endif
}

/* Initialize debug output via UART for board */
void Board_Debug_Init(void)
{
#if defined(DEBUG_UART)
	Board_UART_Init();
	Chip_UART_Init(DEBUG_UART);
	Chip_UART_ConfigData(DEBUG_UART, UART_CFG_DATALEN_8 | UART_CFG_PARITY_NONE | UART_CFG_STOPLEN_1);
	Chip_Clock_SetUSARTNBaseClockRate((115200 * 6 * 16), true);
	Chip_UART_SetBaud(DEBUG_UART, 115200);
	Chip_UART_Enable(DEBUG_UART);
	Chip_UART_TXEnable(DEBUG_UART);
#endif
}

/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	LPC_SWM_T *pSWM = LPC_SWM;
	/* Sets up DEBUG UART */
	#if defined(DEBUG_ENABLE)
	DEBUGINIT();
	//pSWM->PINENABLE0 |= ~(1UL<<SWM_FIXED_SWCLK | 1UL<<SWM_FIXED_SWDIO | 1UL<<SWM_FIXED_RST);
	#ifdef USE_IRC_AS_ROOT_CLOCK
		pSWM->PINENABLE0 |= 1UL<<SWM_FIXED_XTALIN | 1UL<<SWM_FIXED_XTALOUT;
	#endif
	#endif
	/* Initialize GPIO */
	Chip_GPIO_Init(LPC_GPIO_PORT);

	/* Initialize the LEDs */
	Board_LED_Init();
	//Board_Key_Init();
	Init_SPI_PinMux();
	Init_I2C_PinMux();
}
