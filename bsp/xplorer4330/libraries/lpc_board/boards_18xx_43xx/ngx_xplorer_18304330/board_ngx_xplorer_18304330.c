/*
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
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
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include "string.h"

#include "lpc_phy_smsc87x0.c"
#include "retarget.c"

/** @ingroup BOARD_NGX_XPLORER_18304330
 * @{
 */

void Board_UART_Init(LPC_USART_Type *UARTx)
{
	if (UARTx == LPC_USART0) {
		Chip_SCU_PinMux(0x6, 4, MD_PDN, FUNC2);					/* P6.5 : UART0_TXD */
		Chip_SCU_PinMux(0x6, 5, MD_PLN | MD_EZI | MD_ZI, FUNC2);/* P6.4 : UART0_RXD */
	}
	else if (UARTx == LPC_UART1) {
		Chip_SCU_PinMux(0x1, 13, MD_PDN, FUNC2);				/* P1.13 : UART1_TXD */
		Chip_SCU_PinMux(0x1, 14, MD_PLN | MD_EZI | MD_ZI, FUNC2);/* P1.14 : UART1_RX */
	}
}

/* Initialize debug output via UART for board */
void Board_Debug_Init(void)
{
#if defined(DEBUG_UART)
	Board_UART_Init(DEBUG_UART);

	Chip_UART_Init(DEBUG_UART);
	Chip_UART_SetBaud(DEBUG_UART, 115200);
	Chip_UART_ConfigData(DEBUG_UART, UART_DATABIT_8, UART_PARITY_NONE, UART_STOPBIT_1);

	/* Enable UART Transmit */
	Chip_UART_TxCmd(DEBUG_UART, ENABLE);
#endif
}

/* Sends a character on the UART */
void Board_UARTPutChar(char ch)
{
#if defined(DEBUG_UART)
	while (Chip_UART_SendByte(DEBUG_UART, (uint8_t) ch) == ERROR) {}
#endif
}

/* Gets a character from the UART, returns EOF if no character is ready */
int Board_UARTGetChar(void)
{
#if defined(DEBUG_UART)
	uint8_t data;

	if (Chip_UART_ReceiveByte(DEBUG_UART, &data) == SUCCESS) {
		return (int) data;
	}
#endif
	return EOF;
}

/* Outputs a string on the debug UART */
void Board_UARTPutSTR(char *str)
{
#if defined(DEBUG_UART)
	while (*str != '\0') {
		Board_UARTPutChar(*str++);
	}
#endif
}

void Board_LED_Init()
{
	/* P2.12 : LED D2 as output */
	Chip_GPIO_WriteDirBit(1, 12, true);

	/* P2.11 : LED D3 as output */
	Chip_GPIO_WriteDirBit(1, 11, true);

	/* Set initial states to off (true to disable) */
	Chip_GPIO_WritePortBit(1, 12, (bool) true);
	Chip_GPIO_WritePortBit(1, 11, (bool) true);
}

void Board_LED_Set(uint8_t LEDNumber, bool On)
{
	if (LEDNumber == 0) {
		Chip_GPIO_WritePortBit(1, 12, (bool) !On);
	}
	else if (LEDNumber == 1) {
		Chip_GPIO_WritePortBit(1, 11, (bool) !On);
	}
}

bool Board_LED_Test(uint8_t LEDNumber)
{
	if (LEDNumber == 0) {
		return (bool) !Chip_GPIO_ReadPortBit(1, 12);
	}
	else if (LEDNumber == 1) {
		return (bool) !Chip_GPIO_ReadPortBit(1, 11);
	}

	return false;
}

void Board_Buttons_Init(void)	// FIXME not functional ATM
{
	Chip_SCU_PinMux(0x2, 7, MD_PUP | MD_EZI | MD_ZI, FUNC0);		// P2_7 as GPIO0[7]
	Chip_GPIO_WriteDirBit(BUTTONS_BUTTON1_GPIO_PORT_NUM, (1 << BUTTONS_BUTTON1_GPIO_BIT_NUM), false);	// input
}

uint32_t Buttons_GetStatus(void)
{
	uint8_t ret = NO_BUTTON_PRESSED;
	if (Chip_GPIO_ReadPortBit(BUTTONS_BUTTON1_GPIO_PORT_NUM, BUTTONS_BUTTON1_GPIO_BIT_NUM) == 0) {
		ret |= BUTTONS_BUTTON1;
	}
	return ret;
}

void Board_Joystick_Init(void)
{}

uint8_t Joystick_GetStatus(void)
{
	return NO_BUTTON_PRESSED;
}

/*!< System Clock Frequency (Core Clock)*/
uint32_t SystemCoreClock;

/* Update system core clock rate, should be called if the system has
   a clock rate change */
void SystemCoreClockUpdate(void)
{
	/* CPU core speed */
	SystemCoreClock = Chip_Clock_GetRate(CLK_MX_MXCORE);
}

/* Returns the MAC address assigned to this board */
void Board_ENET_GetMacADDR(uint8_t *mcaddr)
{
	uint8_t boardmac[] = {0x00, 0x60, 0x37, 0x12, 0x34, 0x56};

	memcpy(mcaddr, boardmac, 6);
}

/* Set up and initialize all required blocks and functions related to the
   board hardware */
void Board_Init(void)
{
	/* Sets up DEBUG UART */
	DEBUGINIT();

	/* Updates SystemCoreClock global var with current clock speed */
	SystemCoreClockUpdate();

	/* Initializes GPIO */
	Chip_GPIO_Init();

	/* Setup GPIOs for USB demos */
	Chip_SCU_PinMux(0x2, 6, (MD_PUP | MD_EZI), FUNC4);			/* P2_6 USB1_PWR_EN, USB1 VBus function */
	Chip_SCU_PinMux(0x2, 5, (MD_PLN | MD_EZI | MD_ZI), FUNC2);	/* P2_5 USB1_VBUS, MUST CONFIGURE THIS SIGNAL FOR USB1 NORMAL OPERATION */
	Chip_SCU_PinMux(0x1, 7, (MD_PUP | MD_EZI), FUNC4);			/* P1_7 USB0_PWR_EN, USB0 VBus function Xplorer */
	Chip_GPIO_WriteDirBit(5, 6, true);							/* GPIO5[6] = USB1_PWR_EN */
	Chip_GPIO_WritePortBit(5, 6, true);							/* GPIO5[6] output high */
}

void Board_I2C_Init(LPC_I2C_Type *I2Cx)
{
	if (I2Cx == LPC_I2C1) {
		/* Configure pin function for I2C1*/
		Chip_SCU_PinMux(0x2, 3, MD_ZI | MD_EZI, FUNC1);		/* P2.3 : I2C1_SDA */
		Chip_SCU_PinMux(0x2, 4, MD_ZI | MD_EZI, FUNC1);		/* P2.4 : I2C1_SCL */
	}
}

void GPIO0_IRQHandler(void)
{
	static bool On;

	if (Chip_GPIO_IntGetStatus(0, 0, 0)) {
		Chip_GPIO_IntClear(0, 0);
		On = (bool) !On;
		Board_LED_Set(1, On);
	}
}

void Board_GPIO_Int_Init()
{
	Chip_SCU_PinMux(0xF, 9, (MD_PLN | MD_EZI | MD_ZI), FUNC0);	/* PF.9 : POTI button */
	Chip_GPIO_WriteDirBit(7, 23, false);						/* PF.9 -> GPIO7[23] : input */
	Chip_SCU_GPIOIntPinSel(0, 7, 23);
	Chip_GPIO_IntCmd(0, 0, IP_GPIOPININT_FALLING_EDGE);			/* Configure GPIO0[7] to interrupt pin (SW2 switch) */

	NVIC_EnableIRQ(PIN_INT0_IRQn);	/* enable GPIO interrupt 0 */
}

void Board_SDMMC_Init(void)
{
	Chip_SCU_PinMux(0x1, 9, MD_PLN_FAST, FUNC7);	/* P1.9 connected to SDIO_D0 */
	Chip_SCU_PinMux(0x1, 10, MD_PLN_FAST, FUNC7);	/* P1.10 connected to SDIO_D1 */
	Chip_SCU_PinMux(0x1, 11, MD_PLN_FAST, FUNC7);	/* P1.11 connected to SDIO_D2 */
	Chip_SCU_PinMux(0x1, 12, MD_PLN_FAST, FUNC7);	/* P1.12 connected to SDIO_D3 */

	Chip_SCU_PinMux(PINMUX_CLK, 2, MD_PLN | MD_EZI, FUNC4);	/* CLK2 connected to SDIO_CLK */
	Chip_SCU_PinMux(0x1, 6, MD_PLN_FAST, FUNC7);	/* P1.6 connected to SDIO_CMD */
}

void Board_SSP_Init(LPC_SSP_Type *SSPx)
{
	if (SSPx == LPC_SSP1) {
		/* Set up clock and power for SSP1 module */
		/* Configure SSP1 pins*/
		/* SCLK comes out pin CLK0 */
		Chip_SCU_PinMux(PINMUX_CLK, 0, MD_PLN_FAST, FUNC6);		/* CLK0 connected to CLK	func6=SSP1 CLK1  */
		Chip_SCU_PinMux(0x1, 5, MD_PLN_FAST, FUNC5);			/* P1.5 connected to nCS	func5=SSP1 SSEL1 */
		Chip_SCU_PinMux(0x1, 3, MD_PLN | MD_EZI | MD_ZI, FUNC5);/* P1.3 connected to SO		func5=SSP1 MISO1 */
		Chip_SCU_PinMux(0x1, 4, MD_PLN | MD_EZI | MD_ZI, FUNC5);/* P1.4 connected to nSI	func5=SSP1 MOSI1 */
		Chip_Clock_EnableOpts(CLK_MX_SSP1, true, true, 1);
	}
	else {
		return;
	}
}

/* System Register Data Set */
uint16_t UDA_sys_regs_dat[] = {
	UDA1380_REG_EVALCLK_DEFAULT_VALUE,
	UDA1380_REG_I2S_DEFAULT_VALUE,
	UDA1380_REG_PWRCTRL_DEFAULT_VALUE,
	UDA1380_REG_ANAMIX_DEFAULT_VALUE,
	UDA1380_REG_HEADAMP_DEFAULT_VALUE
};

/* System Register Data Set */
uint16_t UDA_interfil_regs_dat[] = {
	UDA1380_REG_MSTRVOL_DEFAULT_VALUE,
	UDA1380_REG_MIXVOL_DEFAULT_VALUE,
	UDA1380_REG_MODEBBT_DEFAULT_VALUE,
	UDA1380_REG_MSTRMUTE_DEFAULT_VALUE,
	UDA1380_REG_MIXSDO_DEFAULT_VALUE
};
/* decimator Register Data Set */
uint16_t UDA_decimator_regs_dat[] = {
	UDA1380_REG_DECVOL_DEFAULT_VALUE,
	UDA1380_REG_PGA_DEFAULT_VALUE,
	UDA1380_REG_ADC_DEFAULT_VALUE,
	UDA1380_REG_AGC_DEFAULT_VALUE
};
static void delay(uint32_t i) {
	while (i--) {}
}

static void UDA_Reg_write(UDA1380_REG reg, unsigned short value, I2C_M_SETUP_Type *I2C_Config) {

	I2C_Config->tx_data[0] = reg;
	I2C_Config->tx_data[1] = value >> 8;
	I2C_Config->tx_data[2] = value & 0xFF;
	Chip_I2C_MasterTransmitData(LPC_I2C0, I2C_Config, I2C_TRANSFER_POLLING);
	delay(10000);
}

static uint16_t UDA_Reg_read(UDA1380_REG reg) {
	uint8_t rx_data[2];
	Chip_I2C_MasterReadReg(LPC_I2C0, I2CDEV_UDA1380_ADDR, reg, rx_data, 2);
	return rx_data[0] << 8 | rx_data[1];
}

static Status UDA1380_init(I2C_M_SETUP_Type *I2C_Config, Board_Audio_Input_Sel_Type audio_in_sel)
{
	uint16_t temp;
	uint8_t  i;
	/* Reset UDA1380 on board NGX Xplorer */
	Chip_SCU_PinMux(0x2, 10, MD_PUP, FUNC0);
	Chip_GPIO_WriteDirBit(0, 14, true);
	Chip_GPIO_WritePortBit(0, 14, true);
	// delay 1us
	delay(100000);
	Chip_GPIO_WritePortBit(0, 14, false);
	delay(100000);
	for (i = 0; i < 5; i++) {
		UDA_Reg_write((UDA1380_REG) (UDA_EVALM_CLK + i), UDA_sys_regs_dat[i], I2C_Config);
		temp = UDA_Reg_read((UDA1380_REG) (UDA_EVALM_CLK + i));
		if (temp != UDA_sys_regs_dat[i]) {
			return ERROR;
		}
	}

	/* interfilter regs init */
	for (i = 0; i < 5; i++) {
		UDA_Reg_write((UDA1380_REG) (UDA_MASTER_VOL_CTRL + i), UDA_interfil_regs_dat[i], I2C_Config);
		temp = UDA_Reg_read((UDA1380_REG) (UDA_MASTER_VOL_CTRL + i));
		if (temp != UDA_interfil_regs_dat[i]) {
			return ERROR;
		}
	}
	/* decimator regs init */
	for (i = 0; i < 4; i++) {
		UDA_Reg_write((UDA1380_REG) (UDA_DEC_VOL_CTRL + i), UDA_decimator_regs_dat[i], I2C_Config);
		temp = UDA_Reg_read((UDA1380_REG) (UDA_DEC_VOL_CTRL + i));
		if (temp != UDA_decimator_regs_dat[i]) {
			return ERROR;
		}
	}

	if (audio_in_sel == MCB_18XX_AUDIO_MIC_SELECT) {
		/* Disable Power On for ADCR, PGAR, PGAL to get mic sound more clearly */
		UDA_Reg_write((UDA1380_REG) (UDA_POWER_CTRL), UDA1380_REG_PWRCTRL_DEFAULT_VALUE & (~(0x0B)), I2C_Config);
		temp = UDA_Reg_read((UDA1380_REG) (UDA_ADC_CTRL));
		if (temp != (UDA1380_REG_ADC_DEFAULT_VALUE | MCB_18XX_AUDIO_MIC_SELECT)) {
			return ERROR;
		}
		UDA_Reg_write((UDA1380_REG) (UDA_ADC_CTRL),
					  UDA1380_REG_ADC_DEFAULT_VALUE | MCB_18XX_AUDIO_MIC_SELECT,
					  I2C_Config);
		temp = UDA_Reg_read((UDA1380_REG) (UDA_ADC_CTRL));
		if (temp != (UDA1380_REG_ADC_DEFAULT_VALUE | MCB_18XX_AUDIO_MIC_SELECT)) {
			return ERROR;
		}
	}
	return SUCCESS;

}

void Board_Audio_Init(LPC_I2S_Type *I2Sx, Board_Audio_Input_Sel_Type audio_in_sel)
{
	uint8_t uda1380_tx_data_buf[3];
	Chip_I2S_Audio_Format_Type I2S_Config;
	I2C_M_SETUP_Type I2C_Config;
	I2C_Config.sl_addr7bit = I2CDEV_UDA1380_ADDR;
	I2C_Config.retransmissions_max = 5;
	I2C_Config.tx_length = 3;
	I2C_Config.tx_data = uda1380_tx_data_buf;
	I2C_Config.rx_length = 0;
	I2C_Config.rx_data = NULL;

	/* Initialize I2C peripheral ------------------------------------*/
	/* Init I2C */
	Chip_I2C_Init(LPC_I2C0);
	Chip_I2C_SetClockRate(LPC_I2C0, 100000);

	I2S_Config.SampleRate = 48000;
	I2S_Config.ChannelNumber = 2;		/* 1 is mono, 2 is stereo */
	I2S_Config.WordWidth =  16;			/* 8, 16 or 32 bits */
	Chip_I2S_Init(LPC_I2S0);
	Chip_I2S_Config(LPC_I2S0, I2S_TX_MODE, &I2S_Config);
	/* Enable Slave I2C operation */
	Chip_I2C_Cmd(LPC_I2C0, I2C_MASTER_MODE, ENABLE);
	/* Init UDA1380 CODEC */
	while (UDA1380_init(&I2C_Config, audio_in_sel) != SUCCESS) {}

}

/* FIXME Should we remove this function? */
void Serial_CreateStream(void *Stream)
{}

/**
 * @}
 */
