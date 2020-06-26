/**
  *********************************************************************************
  *
  * @file    ald_pis.h
  * @brief   Header file of PIS driver.
  *
  * @version V1.0
  * @date    27 Nov 2019
  * @author  AE Team
  * @note
  *
  * Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
  *
  *********************************************************************************
  */

#ifndef __ALD_PIS_H__
#define __ALD_PIS_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "utils.h"


/** @addtogroup ES32FXXX_ALD
  * @{
  */

/** @addtogroup PIS
  * @{
  */

/** @defgroup PIS_Public_Types PIS Public Types
  * @{
  */

/**
  * @brief Producer entry
  * @note
  *	ES32F36xx
  *	AD16C4T0	TIMER0
  *	AD16C4T1	TIMER1
  *	GP32C4T0	TIMER2
  *	GP32C4T1	TIMER3
  *	BS16T0		TIMER4
  *	BS16T1		TIMER5
  *	GP16C4T0	TIMER6
  *	GP16C4T1	TIMER7
  *	
  *	ES32F393x/ES32F336x/ES32F392x
  *	GP16C4T0	TIMER0
  *	GP16C4T1	TIMER1
  *	GP32C4T0	TIMER2
  *	GP32C4T1	TIMER3
  *	BS16T0		TIMER4
  *	BS16T1		TIMER5
  *	GP16C4T2	TIMER6
  *	GP16C4T3	TIMER7
  */
typedef enum {
	PIS_NON                 = 0x0,	/**< No async */
	PIS_GPIO_PIN0           = 0x10,	/**< Pin0, level,support async */
	PIS_GPIO_PIN1           = 0x11,	/**< Pin1, level,support async */
	PIS_GPIO_PIN2           = 0x12,	/**< Pin2, level,support async */
	PIS_GPIO_PIN3           = 0x13,	/**< Pin3, level,support async */
	PIS_GPIO_PIN4           = 0x14,	/**< Pin4, level,support async */
	PIS_GPIO_PIN5           = 0x15,	/**< Pin5, level,support async */
	PIS_GPIO_PIN6           = 0x16,	/**< Pin6, level,support async */
	PIS_GPIO_PIN7           = 0x17,	/**< Pin7, level,support async */
	PIS_GPIO_PIN8           = 0x18,	/**< Pin8, level,support async */
	PIS_GPIO_PIN9           = 0x19,	/**< Pin9, level,support async */
	PIS_GPIO_PIN10          = 0x1a,	/**< Pin10, level,support async */
	PIS_GPIO_PIN11          = 0x1b,	/**< Pin11, level,support async */
	PIS_GPIO_PIN12          = 0x1c,	/**< Pin12, level,support async */
	PIS_GPIO_PIN13          = 0x1d,	/**< Pin13, level,support async */
	PIS_GPIO_PIN14          = 0x1e,	/**< Pin14, level,support async */
	PIS_GPIO_PIN15          = 0x1f,	/**< Pin15, level,support async */
	PIS_ACMP_OUT0           = 0x30,	/**< Acmp0 output, level,support async */
	PIS_ACMP_OUT1           = 0x31,	/**< Acmp1 output, level,support async */
	PIS_DAC0_CH0            = 0x40,	/**< Dac0 channel 0, pclk2 pulse,support async */
	PIS_DAC0_CH1            = 0x41,	/**< Dac0 channel 1, pclk2 pulse,support async */
	PIS_ADC0_INJECT         = 0x60,	/**< Adc0 inject, pclk2 pulse,support async */
	PIS_ADC0_REGULAT        = 0x61,	/**< Adc0 regulat, pclk2 pulse,support async */
	PIS_ADC0_RESERVE        = 0x62,	/**< Adc0 reserve */
	PIS_LVD                 = 0x70,	/**< Lvd, level,support async */
	PIS_UART0_RESERVE0      = 0x80,	/**< Uart0 reserve bit 0 */
	PIS_UART0_RESERVE1      = 0x81,	/**< Uart0 reserve bit 1*/
	PIS_UART0_IRDAOUT       = 0x82,	/**< Uart0 irdaout, level,support async */
	PIS_UART0_RTSOUT        = 0x83,	/**< Uart0 rtsout, level,support async */
	PIS_UART0_TXOUT         = 0x84,	/**< Uart0 txout, level,support async */
	PIS_UART0_SYN_SEND      = 0x85,	/**< Uart0 syn send, pulse,support async */
	PIS_UART0_SYN_RECV      = 0x86,	/**< Uart0 syn recv, pulse,support async */
	PIS_UART1_RESERVE0      = 0x90,	/**< Uart1 reserve bit 0 */
	PIS_UART1_RESERVE1      = 0x91,	/**< Uart1 reserve bit 1*/
	PIS_UART1_IRDA          = 0x92,	/**< Uart1 irdaout, level,support async */
	PIS_UART1_RTS           = 0x93,	/**< Uart1 rtsout, level,support async */
	PIS_UART1_TXOUT         = 0x94,	/**< Uart1 txout, level,support async */
	PIS_UART1_SYN_SEND      = 0x95,	/**< Uart1 syn send, pulse,support async */
	PIS_UART1_SYN_RECV      = 0x96,	/**< Uart1 syn recv, pulse,support async */
	PIS_UART2_RESERVE0      = 0xa0,	/**< Uart2 reserve bit 0 */
	PIS_UART2_RESERVE1      = 0xa1,	/**< Uart2 reserve bit 1*/
	PIS_UART2_IRDA          = 0xa2,	/**< Uart2 irdaout, level,support async */
	PIS_UART2_RTS           = 0xa3,	/**< Uart2 rtsout, level,support async */
	PIS_UART2_TXOUT         = 0xa4,	/**< Uart2 txout, level,support async */
	PIS_UART2_SYN_SEND      = 0xa5,	/**< Uart2 syn send, pulse,support async */
	PIS_UART2_SYN_RECV      = 0xa6,	/**< Uart2 syn recv, pulse,support async */
	PIS_UART3_RESERVE0      = 0xb1,	/**< Uart3 reserve bit 0 */
	PIS_UART3_RESERVE1      = 0xb2,	/**< Uart3 reserve bit 1*/
	PIS_UART3_IRDA          = 0xb3,	/**< Uart3 irdaout, level,support async */
	PIS_UART3_RTS           = 0xb4,	/**< Uart3 rtsout, level,support async */
	PIS_UART3_TXOUT         = 0xb5,	/**< Uart3 txout, level,support async */
	PIS_UART3_SYN_SEND      = 0xb6,	/**< Uart3 syn send, pulse,support async */
	PIS_UART3_SYN_RECV      = 0xb7,	/**< Uart3 syn recv, pulse,support async */
	PIS_UART4_RECV          = 0xc0,	/**< uart4 recv, plck1 pulse */
	PIS_UART4_SEND          = 0xc1,	/**< uart4 send, plck1 pulse */
	PIS_UART4_TXOUT         = 0xc2,	/**< uart4 txout, plck1 level */
	PIS_UART5_RECV          = 0xd0,	/**< uart5 recv, plck1 pulse */
	PIS_UART5_SEND          = 0xd1,	/**< uart5 send, plck1 pulse */
	PIS_UART5_TXOUT         = 0xd2,	/**< uart5 txout, plck1 level */
	PIS_SPI0_RECV           = 0xe0,	/**< Spi0 recv, plck1 pulse */
	PIS_SPI0_SEND           = 0xe1,	/**< Spi0 send, plck1 pulse */
	PIS_SPI0_NE             = 0xe2,	/**< Spi0 ne, plck1 level */
	PIS_SPI1_RECV           = 0xf0,	/**< Spi1 recv, plck1 pulse */
	PIS_SPI1_SEND           = 0xf1,	/**< Spi1 send, plck1 pulse */
	PIS_SPI1_NE             = 0xf2,	/**< Spi1 ne, plck1 level */
	PIS_I2C0_RECV           = 0x100,	/**< I2c0 recv, plck1 level */
	PIS_I2C0_SEND           = 0x101,	/**< I2c0 send, plck1 level */
	PIS_I2C1_RECV           = 0x110,	/**< I2c1 recv, plck1 level */
	PIS_I2C1_SEND           = 0x111,	/**< I2c1 send, plck1 level */
	PIS_TIMER0_UPDATA       = 0x120,	/**< Timer0 updata, plck1 pulse */
	PIS_TIMER0_TRIG         = 0x121,	/**< Timer0 trig, plck1 pulse */
	PIS_TIMER0_INPUT_1      = 0x122,	/**< Timer0 chan1 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_1     = 0x123,	/**< Timer0 chan1 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_2      = 0x124,	/**< Timer0 chan2 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_2     = 0x125,	/**< Timer0 chan2 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_3      = 0x126,	/**< Timer0 chan3 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_3     = 0x127,	/**< Timer0 chan3 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_4      = 0x128,	/**< Timer0 chan4 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_4     = 0x129,	/**< Timer0 chan4 output compare, plck1 pulse */
	PIS_TIMER1_UPDATA       = 0x130,	/**< Timer1 updata, plck1 pulse */
	PIS_TIMER1_TRIG         = 0x131,	/**< Timer1 trig, plck1 pulse */
	PIS_TIMER1_INPUT_1      = 0x132,	/**< Timer1 chan1 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_1     = 0x133,	/**< Timer1 chan1 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_2      = 0x134,	/**< Timer1 chan2 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_2     = 0x135,	/**< Timer1 chan2 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_3      = 0x136,	/**< Timer1 chan3 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_3     = 0x137,	/**< Timer1 chan3 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_4      = 0x138,	/**< Timer1 chan4 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_4     = 0x139,	/**< Timer1 chan4 output compare, plck1 pulse */
	PIS_TIMER2_UPDATA       = 0x140,	/**< Timer2 updata, plck1 pulse */
	PIS_TIMER2_TRIG         = 0x141,	/**< Timer2 trig, plck1 pulse */
	PIS_TIMER2_INPUT_1      = 0x142,	/**< Timer2 chan1 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_1     = 0x143,	/**< Timer2 chan1 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_2      = 0x144,	/**< Timer2 chan2 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_2     = 0x145,	/**< Timer2 chan2 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_3      = 0x146,	/**< Timer2 chan3 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_3     = 0x147,	/**< Timer2 chan3 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_4      = 0x148,	/**< Timer2 chan4 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_4     = 0x149,	/**< Timer2 chan4 output compare, plck1 pulse */
	PIS_TIMER3_UPDATA       = 0x150,	/**< Timer3 updata, plck1 pulse */
	PIS_TIMER3_TRIG         = 0x151,	/**< Timer3 trig, plck1 pulse */
	PIS_TIMER3_INPUT_1      = 0x152,	/**< Timer3 chan1 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_1     = 0x153,	/**< Timer3 chan1 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_2      = 0x154,	/**< Timer3 chan2 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_2     = 0x155,	/**< Timer3 chan2 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_3      = 0x156,	/**< Timer3 chan3 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_3     = 0x157,	/**< Timer3 chan3 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_4      = 0x158,	/**< Timer3 chan4 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_4     = 0x159,	/**< Timer3 chan4 output compare, plck1 pulse */
	PIS_RTC_CLOCK           = 0x160,	/**< Rtc clock, pulse,support async */
	PIS_RTC_ALARM           = 0x161,	/**< Rtc alarm, pulse,support async */
	PIS_LPTIMER0_SYN_UPDATA = 0x170,	/**< Lptimer0 syn updata, pulse,support async */
	PIS_LPTIMER0_ASY_UPDATA = 0x171,	/**< Lptimer0 asy updata, pulse,support async */
	PIS_LPUART0_ASY_RECV    = 0x180,	/**< Lpuart0 asy recv, pulse,support async */
	PIS_LPUART0_ASY_SEND    = 0x181,	/**< Lpuart0 asy send, pulse,support async */
	PIS_LPUART0_SYN_RECV    = 0x182,	/**< Lpuart0 syn recv, pulse,support async */
	PIS_LPUART0_SYN_SEND    = 0x183,	/**< Lpuart0 syn recv, pulse,support async */
	PIS_DMA                 = 0x190,	/**< Dma, pulse,support async */
	PIS_ADC1_INJECT         = 0x1a0,	/**< Adc1 inject, pclk2 pulse,support async */
	PIS_ADC1_REGULAT        = 0x1a1,	/**< Adc1 regulat, pclk2 pulse,support async */
	PIS_ADC1_RESERVE        = 0x1a2,	/**< Adc1 reserve */
} pis_src_t;

/**
  * @brief Consumer entry
  */
typedef enum {
	PIS_CH12_TIMER0_ITR0  = 0x003C, /** Tim0 internal input chan0 */
	PIS_CH13_TIMER0_ITR1  = 0x003D, /** Tim0 internal input chan1 */
	PIS_CH14_TIMER0_ITR2  = 0x003E, /** Tim0 internal input chan2 */
	PIS_CH15_TIMER0_ITR3  = 0x003F, /** Tim0 internal input chan3 */
	PIS_CH12_TIMER1_ITR0  = 0x003C, /** Tim1 internal input chan0 */
	PIS_CH13_TIMER1_ITR1  = 0x003D, /** Tim1 internal input chan1 */
	PIS_CH14_TIMER1_ITR2  = 0x003E, /** Tim1 internal input chan2 */
	PIS_CH15_TIMER1_ITR3  = 0x003F, /** Tim1 internal input chan3 */
	PIS_CH12_TIMER2_ITR0  = 0x003C, /** Tim2 internal input chan0 */
	PIS_CH13_TIMER2_ITR1  = 0x003D, /** Tim2 internal input chan1 */
	PIS_CH14_TIMER2_ITR2  = 0x003E, /** Tim2 internal input chan2 */
	PIS_CH15_TIMER2_ITR3  = 0x003F, /** Tim2 internal input chan3 */
	PIS_CH12_TIMER3_ITR0  = 0x003C, /** Tim3 internal input chan0 */
	PIS_CH13_TIMER3_ITR1  = 0x003D, /** Tim3 internal input chan1 */
	PIS_CH14_TIMER3_ITR2  = 0x003E, /** Tim3 internal input chan2 */
	PIS_CH15_TIMER3_ITR3  = 0x003F, /** Tim3 internal input chan3 */
	PIS_CH6_ADC0_REGULAT  = 0x0036, /** ADC0 regulat transform */
	PIS_CH7_ADC0_INJECT   = 0x0037, /** ADC0 inject transform */
	PIS_CH0_LPTIM0_EXT0   = 0x0030, /** Lptim0 external trigger 0 */
	PIS_CH1_LPTIM0_EXT1   = 0x0031, /** Lptim0 external trigger 1 */
	PIS_CH2_LPTIM0_EXT2   = 0x0032, /** Lptim0 external trigger 2 */
	PIS_CH3_LPTIM0_EXT3   = 0x0033, /** Lptim0 external trigger 3 */
	PIS_CH4_LPTIM0_EXT4   = 0x0034, /** Lptim0 external trigger 4 */
	PIS_CH5_LPTIM0_EXT5   = 0x0035, /** Lptim0 external trigger 5 */
	PIS_CH6_LPTIM0_EXT6   = 0x0036, /** Lptim0 external trigger 6 */
	PIS_CH7_LPTIM0_EXT7   = 0x0037, /** Lptim0 external trigger 7 */
	PIS_CH7_DMA_REQUEST   = 0x0037, /** DMA request 7 */
	PIS_CH15_LPUART0_RXD  = 0x081F, /**< Lpuart Rx data */
	PIS_CH14_UART5_RXD    = 0x071E, /**< Uart5 Rx data */
	PIS_CH13_UART4_RXD    = 0x061D, /**< Uart4 Rx data */
	PIS_CH12_UART3_RXD    = 0x031C, /**< Uart3 Rx data */
	PIS_CH11_UART2_RXD    = 0x021B, /**< Uart2 Rx data */
	PIS_CH10_UART1_RXD    = 0x011A, /**< Uart1 Rx data */
	PIS_CH9_UART0_RXD     = 0x0019, /**< Uart0 Rx data  */
	PIS_CH8_TIMER3_CH4IN  = 0x1B08, /**< Tim3 input chan4 */
	PIS_CH8_TIMER2_CH4IN  = 0x1308, /**< Tim2 input chan4 */
	PIS_CH8_SPI1_CLK      = 0x0F18, /**< Spi1 clk */
	PIS_CH7_TIMER3_CH3IN  = 0x1A07, /**< Tim3 input chan3 */
	PIS_CH7_TIMER2_CH3IN  = 0x1207, /**< Tim2 input chan3 */
	PIS_CH7_SPI1_RX       = 0x0E17, /**< Spi1 rx */
	PIS_CH6_TIMER3_CH2IN  = 0x1906, /**< Tim3 input chan2 */
	PIS_CH6_TIMER2_CH2IN  = 0x1106, /**< Tim2 input chan2 */
	PIS_CH6_SPI0_CLK      = 0x0D16, /**< SPI0 CLK */
	PIS_CH5_TIMER3_CH1IN  = 0x1805, /**< Tim3 input chan1 */
	PIS_CH5_TIMER2_CH1IN  = 0x1005, /**< Tim2 input chan1 */
	PIS_CH5_SPI0_RX       = 0x0C15, /**< SPI0 RX */
	PIS_CH4_TIMER1_CH4IN  = 0x0B04, /**< Tim1 input chan4 */
	PIS_CH4_TIMER0_CH4IN  = 0x0304, /**< Tim0 input chan4 */
	PIS_CH3_TIMER1_CH3IN  = 0x0A03, /**< Tim1 input chan3 */
	PIS_CH3_TIMER0_CH3IN  = 0x0203, /**< Tim0 input chan3 */
	PIS_CH2_TIMER1_CH2IN  = 0x0902, /**< Tim1 input chan2 */
	PIS_CH2_TIMER0_CH2IN  = 0x0102, /**< Tim0 input chan2 */
	PIS_CH1_TIMER1_CH1IN  = 0x0801, /**< Tim1 input chan1 */
	PIS_CH0_TIMER0_CH1IN  = 0x0000, /**< Tim0 input chan1 */
	PIS_CH0_TIMER0_BRKIN  = 0x0400, /**< Tim0 break in */
	PIS_CH0_TIMER1_BRKIN  = 0x0C00, /**< Tim1 break in */
	PIS_TRIG_RESERVE      = 0xFFFF, /**< Other Consumer */
} pis_trig_t;

/**
  * @brief Clock select
  */
typedef enum {
	PIS_CLK_PCLK1    = 0,	/**< APB1 peripherals clock */
	PIS_CLK_PCLK2    = 1,	/**< APB2 peripherals clock */
	PIS_CLK_SYS      = 2,	/**< AHB peripherals clock */
	PIS_CLK_RESERVE  = 3,	/**< reserve clock */
} pis_clock_t;

/**
  * @brief Level select
  */
typedef enum {
	PIS_EDGE_NONE    = 0,	/**< None edge */
	PIS_EDGE_UP      = 1,	/**< Up edge */
	PIS_EDGE_DOWN    = 2,	/**< Down edge */
	PIS_EDGE_UP_DOWN = 3,	/**< Up and down edge */
} pis_edge_t;

/**
  * @brief Output style
  */
typedef enum {
	PIS_OUT_LEVEL = 0,	/**< Level */
	PIS_OUT_PULSE = 1,	/**< Pulse */
} pis_output_t;
/**
  * @brief Sync select
  */
typedef enum {
	PIS_SYN_DIRECT		= 0,	/**< Direct */
	PIS_SYN_LEVEL_ASY_APB1	= 1,	/**< Producer level signal and Consumer in APB1 */
	PIS_SYN_LEVEL_ASY_APB2	= 2,	/**< Producer level signal and Consumer in APB2 */
	PIS_SYN_LEVEL_ASY_AHB	= 3,	/**< Producer level signal and Consumer in AHB */
	PIS_SYN_PULSE_ASY_APB1	= 4,	/**< Producer Pulse signal and Consumer in APB1 */
	PIS_SYN_PULSE_ASY_APB2	= 5,	/**< Producer Pulse signal and Consumer in APB2 */
	PIS_SYN_PULSE_ASY_AHB	= 6,	/**< Producer Pulse signal and Consumer in AHB */
} pis_syncsel_t;

/**
  * @brief Pis channel
  */
typedef enum {
	PIS_CH_0 = 0,	/**< Channel 0 */
	PIS_CH_1 = 1,	/**< Channel 1 */
	PIS_CH_2 = 2,	/**< Channel 2 */
	PIS_CH_3 = 3,	/**< Channel 3 */
	PIS_CH_4 = 4,	/**< Channel 4 */
	PIS_CH_5 = 5,	/**< Channel 5 */
	PIS_CH_6 = 6,	/**< Channel 6 */
	PIS_CH_7 = 7,	/**< Channel 7 */
	PIS_CH_8 = 8,	/**< Channel 8 */
	PIS_CH_9 = 9,	/**< Channel 9 */
	PIS_CH_10 = 10,	/**< Channel 10 */
	PIS_CH_11 = 11,	/**< Channel 11 */
	PIS_CH_12 = 12,	/**< Channel 12 */
	PIS_CH_13 = 13,	/**< Channel 13 */
	PIS_CH_14 = 14,	/**< Channel 14 */
	PIS_CH_15 = 15,	/**< Channel 15 */
} pis_ch_t;

/**
  * @brief Pis output channel
  */
typedef enum {
	PIS_OUT_CH_0 = 0,	/**< Channel 0 */
	PIS_OUT_CH_1 = 1,	/**< Channel 1 */
	PIS_OUT_CH_2 = 2,	/**< Channel 2 */
	PIS_OUT_CH_3 = 3,	/**< Channel 3 */
} pis_out_ch_t;

/**
  * @brief Indirect value,no care of it.
  */
typedef enum {
	PIS_CON_0    = 0,	/**< Con 0 */
	PIS_CON_1    = 1,	/**< Con 1 */
	PIS_CON_NONE = 2,	/**< None */
} pis_con_t;

/**
  * @brief Indirect value,no care of it.
  */
typedef union {
	struct {
		uint8_t ch    :4;	/**< Channel */
		uint8_t con   :4;	/**< Contorl */
		uint8_t shift :8;	/**< Shift */
	};
	uint16_t HalfWord;
} pis_divide_t;

/**
  * @brief PIS state structures definition
  */
typedef enum {
	PIS_STATE_RESET   = 0x00,	/**< Peripheral is not initialized */
	PIS_STATE_READY   = 0x01,	/**< Peripheral Initialized and ready for use */
	PIS_STATE_BUSY    = 0x02,	/**< An internal process is ongoing */
	PIS_STATE_TIMEOUT = 0x03,	/**< Timeout state */
	PIS_STATE_ERROR   = 0x04,	/**< Error */
} pis_state_t;

/**
  * @brief PIS modulate target
  */
typedef enum {
	PIS_UART0_TX   = 0,	/**< Modulate uart0 tx */
	PIS_UART1_TX   = 1,	/**< Modulate uart1 tx */
	PIS_UART2_TX   = 2,	/**< Modulate uart2 tx */
	PIS_UART3_TX   = 3,	/**< Modulate uart3 tx */
	PIS_LPUART0_TX = 4,	/**< Modulate lpuart0 tx */
} pis_modu_targ_t;

/**
  * @brief PIS modulate level
  */
typedef enum {
	PIS_LOW_LEVEL  = 0,	/**< Modulate low level */
	PIS_HIGH_LEVEL = 1,	/**< Modulate high level */
} pis_modu_level_t;

/**
  * @brief PIS modulate source
  */
typedef enum {
	PIS_SRC_NONE   = 0,	/**< Stop modulate */
	PIS_SRC_TIMER0 = 1,	/**< Modulate source is TIMER0 */
	PIS_SRC_TIMER1 = 2,	/**< Modulate source is TIMER1 */
	PIS_SRC_TIMER2 = 3,	/**< Modulate source is TIMER2 */
	PIS_SRC_TIMER3 = 4,	/**< Modulate source is TIMER3 */
	PIS_SRC_TIMER6 = 5,	/**< Modulate source is TIMER6 */
	PIS_SRC_TIMER7 = 6,	/**< Modulate source is TIMER7 */
	PIS_SRC_LPTIM0 = 7,	/**< Modulate source is LPTIM0 */
	PIS_SRC_BUZ    = 8,	/**< Modulate source is buz */
} pis_modu_src_t;

/**
  * @brief PIS modulate channel
  */
typedef enum {
	PIS_TIMER_CH1 = 0,	/**< Src is TIMERx and choose channel 1 */
	PIS_TIMER_CH2 = 1,	/**< Src is TIMERx and choose channel 2 */
	PIS_TIMER_CH3 = 2,	/**< Src is TIMERx and choose channel 3 */
	PIS_TIMER_CH4 = 3,	/**< Src is TIMERx and choose channel 4 */
} pis_modu_channel_t;

/**
  * @brief PIS input channel chose
  */
typedef enum {
	PIS_NONE_INPUT = 0,	/**< Consumer input none */
	PIS_PORT_INPUT = 1,	/**< Consumer input choose external port */
	PIS_CHAN_INPUT = 2	/**< Consumer input choose pis channel */
} pis_input_sel_t;

/**
  * @brief PIS init structure definition
  */
typedef struct {
	pis_src_t producer_src;			/**< Producer entry */
	pis_output_t producer_signal;		/**< Producer signal mode */
	pis_clock_t producer_clk;		/**< Producer module clock */
	pis_edge_t producer_edge;		/**< Producer module pin output edge */
	pis_trig_t consumer_trig;		/**< Consumer entry */
	pis_clock_t consumer_clk;		/**< Consumer clock */
	pis_input_sel_t input_chan;		/**< Consumer input channel */
} pis_init_t;

/**
  * @brief PIS modulate config structure definition
  */
typedef struct {
	pis_modu_targ_t target;		/**< Modulate target */
	pis_modu_level_t level;		/**< Modulate level */
	pis_modu_src_t src;		/**< Modulate src */
	pis_modu_channel_t channel;	/**< Modulate channel */
} pis_modulate_config_t;

/**
  * @brief  PIS Handle Structure definition
  */
typedef struct pis_handle_s {
	PIS_TypeDef *perh;		/**< Register base address */
	pis_init_t init;		/**< PIS required parameters */
	pis_ch_t consumer_ch;		/**< Indirect value, no care of it */
	pis_con_t consumer_con;		/**< Indirect value, no care of it */
	uint8_t consumer_pos;	        /**< Indirect value, no care of it */
	uint32_t check_info;		/**< When destroy a handle ,user need check whether is right that ready to destroy */
	lock_state_t lock;		/**< Locking object */
	pis_state_t state;		/**< PIS operation state */
} pis_handle_t;
/**
  * @}
  */


/** @defgroup PIS_Private_Macros PIS Private Macros
  * @{
  */
#define IS_PIS(x) 		(((x) == PIS))
#define IS_PIS_SRC(x) 		(((x) == PIS_NON)		|| \
				 ((x) == PIS_GPIO_PIN0)		|| \
				 ((x) == PIS_GPIO_PIN1)		|| \
				 ((x) == PIS_GPIO_PIN2)		|| \
				 ((x) == PIS_GPIO_PIN3)		|| \
				 ((x) == PIS_GPIO_PIN4)		|| \
				 ((x) == PIS_GPIO_PIN5)		|| \
				 ((x) == PIS_GPIO_PIN6)		|| \
				 ((x) == PIS_GPIO_PIN7)		|| \
				 ((x) == PIS_GPIO_PIN8)		|| \
				 ((x) == PIS_GPIO_PIN9)		|| \
				 ((x) == PIS_GPIO_PIN10)	|| \
				 ((x) == PIS_GPIO_PIN11)	|| \
				 ((x) == PIS_GPIO_PIN12)	|| \
				 ((x) == PIS_GPIO_PIN13)	|| \
				 ((x) == PIS_GPIO_PIN14)	|| \
				 ((x) == PIS_GPIO_PIN15)	|| \
				 ((x) == PIS_ACMP_OUT0)		|| \
				 ((x) == PIS_ACMP_OUT1)		|| \
				 ((x) == PIS_DAC0_CH0)		|| \
				 ((x) == PIS_DAC0_CH1)		|| \
				 ((x) == PIS_ADC0_INJECT)	|| \
				 ((x) == PIS_ADC0_REGULAT)	|| \
				 ((x) == PIS_ADC0_RESERVE)	|| \
				 ((x) == PIS_LVD)		|| \
				 ((x) == PIS_UART0_RESERVE0)	|| \
				 ((x) == PIS_UART0_RESERVE1)	|| \
				 ((x) == PIS_UART0_IRDAOUT)	|| \
				 ((x) == PIS_UART0_RTSOUT)	|| \
				 ((x) == PIS_UART0_TXOUT)	|| \
				 ((x) == PIS_UART0_SYN_SEND)	|| \
				 ((x) == PIS_UART0_SYN_RECV)	|| \
				 ((x) == PIS_UART1_RESERVE0)	|| \
				 ((x) == PIS_UART1_RESERVE1)	|| \
				 ((x) == PIS_UART1_IRDA)	|| \
				 ((x) == PIS_UART1_RTS)		|| \
				 ((x) == PIS_UART1_TXOUT)	|| \
				 ((x) == PIS_UART1_SYN_SEND)	|| \
				 ((x) == PIS_UART1_SYN_RECV)	|| \
				 ((x) == PIS_UART2_RESERVE0)	|| \
				 ((x) == PIS_UART2_RESERVE1)	|| \
				 ((x) == PIS_UART2_IRDA)	|| \
				 ((x) == PIS_UART2_RTS)		|| \
				 ((x) == PIS_UART2_TXOUT)	|| \
				 ((x) == PIS_UART2_SYN_SEND)	|| \
				 ((x) == PIS_UART2_SYN_RECV)	|| \
				 ((x) == PIS_UART3_RESERVE0)	|| \
				 ((x) == PIS_UART3_RESERVE1)	|| \
				 ((x) == PIS_UART3_IRDA)	|| \
				 ((x) == PIS_UART3_RTS)		|| \
				 ((x) == PIS_UART3_TXOUT)	|| \
				 ((x) == PIS_UART3_SYN_SEND)	|| \
				 ((x) == PIS_UART3_SYN_RECV)	|| \
				 ((x) == PIS_UART4_RECV)	|| \
				 ((x) == PIS_UART4_SEND)	|| \
				 ((x) == PIS_UART4_TXOUT)	|| \
				 ((x) == PIS_UART5_RECV)	|| \
				 ((x) == PIS_UART5_SEND)	|| \
				 ((x) == PIS_UART5_TXOUT)	|| \
				 ((x) == PIS_SPI0_RECV)		|| \
				 ((x) == PIS_SPI0_SEND)		|| \
				 ((x) == PIS_SPI0_NE)		|| \
				 ((x) == PIS_SPI1_RECV)		|| \
				 ((x) == PIS_SPI1_SEND)		|| \
				 ((x) == PIS_SPI1_NE)		|| \
				 ((x) == PIS_I2C0_RECV)		|| \
				 ((x) == PIS_I2C0_SEND)		|| \
				 ((x) == PIS_I2C1_RECV)		|| \
				 ((x) == PIS_I2C1_SEND)		|| \
				 ((x) == PIS_TIMER0_UPDATA)	|| \
				 ((x) == PIS_TIMER0_TRIG)	|| \
				 ((x) == PIS_TIMER0_INPUT_1)	|| \
				 ((x) == PIS_TIMER0_OUTPUT_1)	|| \
				 ((x) == PIS_TIMER0_INPUT_2)	|| \
				 ((x) == PIS_TIMER0_OUTPUT_2)	|| \
				 ((x) == PIS_TIMER0_INPUT_3)	|| \
				 ((x) == PIS_TIMER0_OUTPUT_3)	|| \
				 ((x) == PIS_TIMER0_INPUT_4)	|| \
				 ((x) == PIS_TIMER0_OUTPUT_4)	|| \
				 ((x) == PIS_TIMER1_UPDATA)	|| \
				 ((x) == PIS_TIMER1_TRIG)	|| \
				 ((x) == PIS_TIMER1_INPUT_1)	|| \
				 ((x) == PIS_TIMER1_OUTPUT_1)	|| \
				 ((x) == PIS_TIMER1_INPUT_2)	|| \
				 ((x) == PIS_TIMER1_OUTPUT_2)	|| \
				 ((x) == PIS_TIMER1_INPUT_3)	|| \
				 ((x) == PIS_TIMER1_OUTPUT_3)	|| \
				 ((x) == PIS_TIMER1_INPUT_4)	|| \
				 ((x) == PIS_TIMER1_OUTPUT_4)	|| \
				 ((x) == PIS_TIMER2_UPDATA)	|| \
				 ((x) == PIS_TIMER2_TRIG)	|| \
				 ((x) == PIS_TIMER2_INPUT_1)	|| \
				 ((x) == PIS_TIMER2_OUTPUT_1)	|| \
				 ((x) == PIS_TIMER2_INPUT_2)	|| \
				 ((x) == PIS_TIMER2_OUTPUT_2)	|| \
				 ((x) == PIS_TIMER2_INPUT_3)	|| \
				 ((x) == PIS_TIMER2_OUTPUT_3))
#define IS_PIS_TRIG(x) 		(((x) == PIS_CH12_TIMER0_ITR0)  || \
				 ((x) == PIS_CH13_TIMER0_ITR1)  || \
				 ((x) == PIS_CH14_TIMER0_ITR2)  || \
				 ((x) == PIS_CH15_TIMER0_ITR3)  || \
				 ((x) == PIS_CH12_TIMER1_ITR0)  || \
				 ((x) == PIS_CH13_TIMER1_ITR1)  || \
				 ((x) == PIS_CH14_TIMER1_ITR2)  || \
				 ((x) == PIS_CH15_TIMER1_ITR3)  || \
				 ((x) == PIS_CH12_TIMER2_ITR0)  || \
				 ((x) == PIS_CH13_TIMER2_ITR1)  || \
				 ((x) == PIS_CH14_TIMER2_ITR2)  || \
				 ((x) == PIS_CH15_TIMER2_ITR3)  || \
				 ((x) == PIS_CH12_TIMER3_ITR0)  || \
				 ((x) == PIS_CH13_TIMER3_ITR1)  || \
				 ((x) == PIS_CH14_TIMER3_ITR2)  || \
				 ((x) == PIS_CH15_TIMER3_ITR3)  || \
				 ((x) == PIS_CH6_ADC0_REGULAT)  || \
				 ((x) == PIS_CH7_ADC0_INJECT)   || \
				 ((x) == PIS_CH0_LPTIM0_EXT0) || \
				 ((x) == PIS_CH1_LPTIM0_EXT1) || \
				 ((x) == PIS_CH2_LPTIM0_EXT2) || \
				 ((x) == PIS_CH3_LPTIM0_EXT3) || \
				 ((x) == PIS_CH4_LPTIM0_EXT4) || \
				 ((x) == PIS_CH5_LPTIM0_EXT5) || \
				 ((x) == PIS_CH6_LPTIM0_EXT6) || \
				 ((x) == PIS_CH7_LPTIM0_EXT7) || \
				 ((x) == PIS_CH7_DMA_REQUEST)   || \
				 ((x) == PIS_CH15_LPUART0_RXD)  || \
				 ((x) == PIS_CH14_UART5_RXD)    || \
				 ((x) == PIS_CH13_UART4_RXD)    || \
				 ((x) == PIS_CH12_UART3_RXD)    || \
				 ((x) == PIS_CH11_UART2_RXD)    || \
				 ((x) == PIS_CH10_UART1_RXD)    || \
				 ((x) == PIS_CH9_UART0_RXD)     || \
				 ((x) == PIS_CH8_TIMER3_CH4IN)  || \
				 ((x) == PIS_CH8_TIMER2_CH4IN)  || \
				 ((x) == PIS_CH8_SPI1_CLK)      || \
				 ((x) == PIS_CH7_TIMER3_CH3IN)  || \
				 ((x) == PIS_CH7_TIMER2_CH3IN)  || \
				 ((x) == PIS_CH7_SPI1_RX)       || \
				 ((x) == PIS_CH6_TIMER3_CH2IN)  || \
				 ((x) == PIS_CH6_TIMER2_CH2IN)  || \
				 ((x) == PIS_CH6_SPI0_CLK)      || \
				 ((x) == PIS_CH5_TIMER3_CH1IN)  || \
				 ((x) == PIS_CH5_TIMER2_CH1IN)  || \
				 ((x) == PIS_CH5_SPI0_RX)       || \
				 ((x) == PIS_CH4_TIMER1_CH4IN)  || \
				 ((x) == PIS_CH4_TIMER0_CH4IN)  || \
				 ((x) == PIS_CH3_TIMER1_CH3IN)  || \
				 ((x) == PIS_CH3_TIMER0_CH3IN)  || \
				 ((x) == PIS_CH2_TIMER1_CH2IN)  || \
				 ((x) == PIS_CH2_TIMER0_CH2IN)  || \
				 ((x) == PIS_CH1_TIMER1_CH1IN)  || \
				 ((x) == PIS_CH0_TIMER0_CH1IN)  || \
				 ((x) == PIS_CH0_TIMER0_BRKIN)  || \
				 ((x) == PIS_CH0_TIMER1_BRKIN)  || \
				 ((x) == PIS_TRIG_RESERVE)      || \
				 ((x) == PIS_CH8_SPI1_CLK))
#define IS_PIS_CLOCK(x) 	(((x) == PIS_CLK_PCLK1)  || \
				 ((x) == PIS_CLK_PCLK2)  || \
				 ((x) == PIS_CLK_SYS))
#define IS_PIS_SIGNAL_MODE(x) 	(((x) == PIS_OUT_LEVEL)  || \
				 ((x) == PIS_OUT_PULSE))
#define IS_PIS_EDGE(x) 		(((x) == PIS_EDGE_NONE) || \
				 ((x) == PIS_EDGE_UP)   || \
				 ((x) == PIS_EDGE_DOWN) || \
				 ((x) == PIS_EDGE_UP_DOWN))
#define IS_PIS_OUTPUT(x) 	(((x) == PIS_OUT_LEVEL) || \
				 ((x) == PIS_OUT_PULSE))
#define IS_PIS_OUPUT_CH(x)	(((x) == PIS_OUT_CH_0) || \
				 ((x) == PIS_OUT_CH_1) || \
				 ((x) == PIS_OUT_CH_2) || \
				 ((x) == PIS_OUT_CH_3))
#define IS_PIS_MODU_TARGET(x)	(((x) == PIS_UART0_TX) || \
				 ((x) == PIS_UART1_TX) || \
				 ((x) == PIS_UART2_TX) || \
				 ((x) == PIS_UART3_TX) || \
				 ((x) == PIS_LPUART0_TX))
#define IS_PIS_MODU_LEVEL(x)	(((x) == PIS_LOW_LEVEL) || \
				 ((x) == PIS_HIGH_LEVEL))
#define IS_PIS_MODU_SRC(x)	(((x) == PIS_SRC_NONE)     || \
				 ((x) == PIS_SRC_TIMER0)   || \
				 ((x) == PIS_SRC_TIMER1)   || \
				 ((x) == PIS_SRC_TIMER2)   || \
				 ((x) == PIS_SRC_TIMER3)   || \
				 ((x) == PIS_SRC_TIMER6)   || \
				 ((x) == PIS_SRC_TIMER7)   || \
				 ((x) == PIS_SRC_LPTIM0)   || \
				 ((x) == PIS_SRC_BUZ))
#define IS_PIS_MODU_CHANNEL(x)	(((x) == PIS_TIMER_CH1) || \
				 ((x) == PIS_TIMER_CH2) || \
				 ((x) == PIS_TIMER_CH3) || \
				 ((x) == PIS_TIMER_CH4))
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions
  * @{
  */

/** @addtogroup PIS_Public_Functions_Group1
  * @{
  */
ald_status_t ald_pis_create(pis_handle_t *hperh);
ald_status_t ald_pis_destroy(pis_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group2
  * @{
  */
ald_status_t ald_pis_output_start(pis_handle_t *hperh, pis_out_ch_t ch);
ald_status_t ald_pis_output_stop(pis_handle_t *hperh, pis_out_ch_t ch);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group3
  * @{
  */
pis_state_t ald_pis_get_state(pis_handle_t *hperh);
/**
  * @}
  */

/** @addtogroup PIS_Public_Functions_Group4
  * @{
  */
ald_status_t ald_pis_modu_config(pis_handle_t *hperh, pis_modulate_config_t *config);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __ALD_PIS_H__ */
