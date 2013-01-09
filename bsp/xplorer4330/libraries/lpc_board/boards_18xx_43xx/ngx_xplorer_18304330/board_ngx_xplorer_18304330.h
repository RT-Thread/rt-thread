/*
 * @brief NGX Xplorer 1830/4330 board file
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

#ifndef __BOARD_NGX_XPLORER_18304330_H_
#define __BOARD_NGX_XPLORER_18304330_H_

#include "chip.h"
#include "board_api.h"
#include "lpc_phy.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup BOARD_NGX_XPLORER_18304330 LPC1830 and LPC4330 NGX Xplorer board support functions
 * @ingroup BOARDS_18XX_43XX
 * @{
 */

/** @defgroup BOARD_NGX_XPLORER_18304330_OPTIONS BOARD: LPC1830 and LPC4330 NGX Xplorer board builds options
 * The NGX board has options that configure it's operation at build-time.<br/>
 * CHIP_LPC*
 *  - One of @ref CHIP_LPC18XX or @ref CHIP_LPC43XX must be defined for this board
 * DEBUG:<br/>
 * - When defined, DEBUGOUT and DEBUGSTR functions are routed to the UART defined by DEBUG_UART<br/>
 * - When not defined, DEBUGOUT and DEBUGSTR are null functions<br/><p>
 * DEBUG_UART:<br/>
 *  - This defines the UART used for debug output when DEBUG is defined, example: @ref LPC_USART0<br/><p>
 * CRYSTAL_MAIN_FREQ_IN:<br/>
 *  - This define specifies the crystal input clock into the chip, example: 12000000<br/><p>
 * CRYSTAL_32K_FREQ_IN:<br/>
 *  - This define specifies the RTC crystal input clock into the chip, example: 32768<br/><p>
 * EXTERNAL_CLKIN_FREQ_IN:<br/>
 *  - This define specifies the clock rate input into the EXTCLKIN pin, example: 28000000<br/><p>
 * MAX_CLOCK_FREQ:<br/>
 *  - When defined, this will be used to configure the CPU clock rate, example: 150000000<br/>
 *  - When not defined, the system will use the maximum CPU clokc rate<br/><p>
 * BOARD_HITEX_EVA_18504350:<br/>
 *  - When building for NGX boards, BOARD_NGX_XPLORER_18304330 is defined<br/>
 * <br/><p>
 * For more information on driver options see @ref LPCOPEN_DESIGN_ARPPROACH<br/>
 * @{
 */

/**
 * @}
 */

#define BOARD_NGX_XPLORER_18304330

#define I2CDEV_UDA1380_ADDR     (0x34 >> 1)

#define UDA1380_REG_EVALCLK_DEFAULT_VALUE   (0xF << 8 | 0x3 << 4 | 1 << 1)
#define UDA1380_REG_I2S_DEFAULT_VALUE           0x0000

#define UDA1380_REG_PWRCTRL_DEFAULT_VALUE   (1 << 15 | 1 << 13 | 1 << 10 | 1 << 8 | 1 << 6 | 1 << 4 | 0x0F)
#define UDA1380_REG_ANAMIX_DEFAULT_VALUE    0x0000
#define UDA1380_REG_HEADAMP_DEFAULT_VALUE   ( 1 << 9 | 2)

#define UDA1380_REG_MSTRVOL_DEFAULT_VALUE   0x0000
#define UDA1380_REG_MIXVOL_DEFAULT_VALUE    0x0000
#define UDA1380_REG_MODEBBT_DEFAULT_VALUE   0x0000
#define UDA1380_REG_MSTRMUTE_DEFAULT_VALUE  (2 << 8 | 2)
#define UDA1380_REG_MIXSDO_DEFAULT_VALUE      0x0000

#define UDA1380_REG_DECVOL_DEFAULT_VALUE     0xE4E4			/* Decrease Volume -28dB */
#define UDA1380_REG_PGA_DEFAULT_VALUE         0x0000
#define UDA1380_REG_ADC_DEFAULT_VALUE         0x0001			/* Apply 0bB VGA Gain, enable DC Filter */
#define UDA1380_REG_AGC_DEFAULT_VALUE         0x0000
#define UDA1380_REG_L3_DEFAULT_VALUE          0x0000

/* For USBLIB examples */
#define LEDS_LED1           0x01
#define LEDS_LED2           0x02
#define LEDS_LED3           0x04
#define LEDS_LED4           0x08
#define LEDS_NO_LEDS        0x00
#define BUTTONS_BUTTON1     0x01
#define JOY_UP              0x01
#define JOY_DOWN            0x02
#define JOY_LEFT            0x04
#define JOY_RIGHT           0x08
#define JOY_PRESS           0x10
#define NO_BUTTON_PRESSED   0x00

#define BUTTONS_BUTTON1_GPIO_PORT_NUM   0
#define BUTTONS_BUTTON1_GPIO_BIT_NUM    7
#define LED1_GPIO_PORT_NUM              1
#define LED1_GPIO_BIT_NUM               11
#define LED2_GPIO_PORT_NUM              1
#define LED2_GPIO_BIT_NUM               12

typedef enum {
	MCB_18XX_AUDIO_MIC_SELECT = 1 << 2 | 1 << 3,
	MCB_18XX_AUDIO_LINE_IN_SELECT = 0x00,
} Board_Audio_Input_Sel_Type;

/* UDA1380 Register Address */
typedef enum {
	UDA_EVALM_CLK = 0x00,
	UDA_BUS_CTRL,
	UDA_POWER_CTRL,
	UDA_ANALOG_CTRL,
	UDA_HPAMP_CTRL,
	UDA_MASTER_VOL_CTRL = 0x10,
	UDA_MIXER_VOL_CTRL,
	UDA_MODE_CTRL,
	UDA_MUTE_CTRL,
	UDA_MIXER_FILTER_CTRL,
	UDA_DEC_VOL_CTRL = 0x20,
	UDA_PGA_CTRL,
	UDA_ADC_CTRL,
	UDA_AGC_CTRL,
	UDA_TOTAL_REG
} UDA1380_REG;

/**
 * @brief	Sets up board specific I2C interface
 * @param	I2Cx	: Pointer to I2C interface to initialize
 * @return	Nothing
 */
void Board_I2C_Init(LPC_I2C_Type *I2Cx);

/**
 * @brief	Initializes board specific GPIO Interrupt
 * @return	Nothing
 */
void Board_GPIO_Int_Init(void);

/**
 * @brief	Initialize pin muxing for SSP interface
 * @param	SSPx	: Pointer to SSP interface to initialize
 * @return	Nothing
 */
void Board_SSP_Init(LPC_SSP_Type *SSPx);

/**
 * @brief	Returns the MAC address assigned to this board
 * @param	mcaddr : Pointer to 6-byte character array to populate with MAC address
 * @return	Nothing
 */
void Board_ENET_GetMacADDR(uint8_t *mcaddr);

/**
 * @brief	Initialize pin muxing for a UART
 * @param	UARTx	: Pointer to UART register block for UART pins to init
 * @return	Nothing
 */
void Board_UART_Init(LPC_USART_Type *UARTx);

/**
 * @brief	Initialize pin muxing for SDMMC interface
 * @return	Nothing
 */
void Board_SDMMC_Init(void);

/**
 * @brief	Initialize button(s) interface on board
 * @return	Nothing
 */
void Board_Buttons_Init(void);

/**
 * @brief	Initialize joystick interface on board
 * @return	Nothing
 */
void Board_Joystick_Init(void);

/**
 * @brief	Returns joystick states on board
 * @return	Returns a JOY_* value, ir JOY_PRESS or JOY_UP
 */
uint8_t Joystick_GetStatus(void);

/**
 * @brief	Returns button(s) state on board
 * @return	Returns BUTTONS_BUTTON1 if button1 is pressed
 */
uint32_t Buttons_GetStatus (void);

/**
 * @brief	Initialize I2S interface for the board and UDA1380
 * @param	I2Sx			: Pointer to I2S register interface used on this board
 * @param	audio_in_sel	: Audio input selection
 * @return	Nothing
 */
void Board_Audio_Init(LPC_I2S_Type *I2Sx, Board_Audio_Input_Sel_Type audio_in_sel);

/**
 * @brief	FIXME
 * @param	Stream	: FIXME
 * @return	Nothing
 */
void Serial_CreateStream(void *Stream);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_NGX_XPLORER_18304330_H_ */
