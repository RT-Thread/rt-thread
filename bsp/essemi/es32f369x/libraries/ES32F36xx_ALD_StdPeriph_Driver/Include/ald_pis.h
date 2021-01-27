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
  * @verbatim
      In PIS module, for the convenience of code maintenance,
      TIMERx is used to indicate the sequence of the timer peripheral.
      Different product series TIMERx represent different meanings:
      1. For ES32F36xx series:
      TIMER0 ----> AD16C4T0
      TIMER1 ----> AD16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
     
      2. For ES32F393x/ES32F336x/ES32F392x series:
      TIMER0 ----> GP16C4T0
      TIMER1 ----> GP16C4T1
      TIMER2 ----> GP32C4T0
      TIMER3 ----> GP32C4T1
    @endverbatim
  * @{
  */

/**
  * @brief Producer entry
  */
typedef enum {
	PIS_NON                 = 0x0U,		/**< No async */
	PIS_GPIO_PIN0           = 0x10U,	/**< Pin0, level,support async */
	PIS_GPIO_PIN1           = 0x11U,	/**< Pin1, level,support async */
	PIS_GPIO_PIN2           = 0x12U,	/**< Pin2, level,support async */
	PIS_GPIO_PIN3           = 0x13U,	/**< Pin3, level,support async */
	PIS_GPIO_PIN4           = 0x14U,	/**< Pin4, level,support async */
	PIS_GPIO_PIN5           = 0x15U,	/**< Pin5, level,support async */
	PIS_GPIO_PIN6           = 0x16U,	/**< Pin6, level,support async */
	PIS_GPIO_PIN7           = 0x17U,	/**< Pin7, level,support async */
	PIS_GPIO_PIN8           = 0x18U,	/**< Pin8, level,support async */
	PIS_GPIO_PIN9           = 0x19U,	/**< Pin9, level,support async */
	PIS_GPIO_PIN10          = 0x1aU,	/**< Pin10, level,support async */
	PIS_GPIO_PIN11          = 0x1bU,	/**< Pin11, level,support async */
	PIS_GPIO_PIN12          = 0x1cU,	/**< Pin12, level,support async */
	PIS_GPIO_PIN13          = 0x1dU,	/**< Pin13, level,support async */
	PIS_GPIO_PIN14          = 0x1eU,	/**< Pin14, level,support async */
	PIS_GPIO_PIN15          = 0x1fU,	/**< Pin15, level,support async */
	PIS_ACMP_OUT0           = 0x30U,	/**< Acmp0 output, level,support async */
	PIS_ACMP_OUT1           = 0x31U,	/**< Acmp1 output, level,support async */
	PIS_DAC0_CH0            = 0x40U,	/**< Dac0 channel 0, pclk2 pulse,support async */
	PIS_DAC0_CH1            = 0x41U,	/**< Dac0 channel 1, pclk2 pulse,support async */
	PIS_ADC0_INSERT         = 0x60U,	/**< Adc0 insert, pclk2 pulse,support async */
	PIS_ADC0_NORMAL         = 0x61U,	/**< Adc0 normal, pclk2 pulse,support async */
	PIS_ADC0_RESERVE        = 0x62U,	/**< Adc0 reserve */
	PIS_LVD                 = 0x70U,	/**< Lvd, level,support async */
	PIS_UART0_RESERVE0      = 0x80U,	/**< Uart0 reserve bit 0 */
	PIS_UART0_RESERVE1      = 0x81U,	/**< Uart0 reserve bit 1*/
	PIS_UART0_IRDAOUT       = 0x82U,	/**< Uart0 irdaout, level,support async */
	PIS_UART0_RTSOUT        = 0x83U,	/**< Uart0 rtsout, level,support async */
	PIS_UART0_TXOUT         = 0x84U,	/**< Uart0 txout, level,support async */
	PIS_UART0_SYN_SEND      = 0x85U,	/**< Uart0 syn send, pulse,support async */
	PIS_UART0_SYN_RECV      = 0x86U,	/**< Uart0 syn recv, pulse,support async */
	PIS_UART1_RESERVE0      = 0x90U,	/**< Uart1 reserve bit 0 */
	PIS_UART1_RESERVE1      = 0x91U,	/**< Uart1 reserve bit 1*/
	PIS_UART1_IRDA          = 0x92U,	/**< Uart1 irdaout, level,support async */
	PIS_UART1_RTS           = 0x93U,	/**< Uart1 rtsout, level,support async */
	PIS_UART1_TXOUT         = 0x94U,	/**< Uart1 txout, level,support async */
	PIS_UART1_SYN_SEND      = 0x95U,	/**< Uart1 syn send, pulse,support async */
	PIS_UART1_SYN_RECV      = 0x96U,	/**< Uart1 syn recv, pulse,support async */
	PIS_UART2_RESERVE0      = 0xa0U,	/**< Uart2 reserve bit 0 */
	PIS_UART2_RESERVE1      = 0xa1U,	/**< Uart2 reserve bit 1*/
	PIS_UART2_IRDA          = 0xa2U,	/**< Uart2 irdaout, level,support async */
	PIS_UART2_RTS           = 0xa3U,	/**< Uart2 rtsout, level,support async */
	PIS_UART2_TXOUT         = 0xa4U,	/**< Uart2 txout, level,support async */
	PIS_UART2_SYN_SEND      = 0xa5U,	/**< Uart2 syn send, pulse,support async */
	PIS_UART2_SYN_RECV      = 0xa6U,	/**< Uart2 syn recv, pulse,support async */
	PIS_UART3_RESERVE0      = 0xb1U,	/**< Uart3 reserve bit 0 */
	PIS_UART3_RESERVE1      = 0xb2U,	/**< Uart3 reserve bit 1*/
	PIS_UART3_IRDA          = 0xb3U,	/**< Uart3 irdaout, level,support async */
	PIS_UART3_RTS           = 0xb4U,	/**< Uart3 rtsout, level,support async */
	PIS_UART3_TXOUT         = 0xb5U,	/**< Uart3 txout, level,support async */
	PIS_UART3_SYN_SEND      = 0xb6U,	/**< Uart3 syn send, pulse,support async */
	PIS_UART3_SYN_RECV      = 0xb7U,	/**< Uart3 syn recv, pulse,support async */
	PIS_UART4_RECV          = 0xc0U,	/**< uart4 recv, plck1 pulse */
	PIS_UART4_SEND          = 0xc1U,	/**< uart4 send, plck1 pulse */
	PIS_UART4_TXOUT         = 0xc2U,	/**< uart4 txout, plck1 level */
	PIS_UART5_RECV          = 0xd0U,	/**< uart5 recv, plck1 pulse */
	PIS_UART5_SEND          = 0xd1U,	/**< uart5 send, plck1 pulse */
	PIS_UART5_TXOUT         = 0xd2U,	/**< uart5 txout, plck1 level */
	PIS_SPI0_RECV           = 0xe0U,	/**< Spi0 recv, plck1 pulse */
	PIS_SPI0_SEND           = 0xe1U,	/**< Spi0 send, plck1 pulse */
	PIS_SPI0_NE             = 0xe2U,	/**< Spi0 ne, plck1 level */
	PIS_SPI1_RECV           = 0xf0U,	/**< Spi1 recv, plck1 pulse */
	PIS_SPI1_SEND           = 0xf1U,	/**< Spi1 send, plck1 pulse */
	PIS_SPI1_NE             = 0xf2U,	/**< Spi1 ne, plck1 level */
	PIS_I2C0_RECV           = 0x100U,	/**< I2c0 recv, plck1 level */
	PIS_I2C0_SEND           = 0x101U,	/**< I2c0 send, plck1 level */
	PIS_I2C1_RECV           = 0x110U,	/**< I2c1 recv, plck1 level */
	PIS_I2C1_SEND           = 0x111U,	/**< I2c1 send, plck1 level */
	PIS_TIMER0_UPDATA       = 0x120U,	/**< Timer0 updata, plck1 pulse */
	PIS_TIMER0_TRIG         = 0x121U,	/**< Timer0 trig, plck1 pulse */
	PIS_TIMER0_INPUT_1      = 0x122U,	/**< Timer0 chan1 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_1     = 0x123U,	/**< Timer0 chan1 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_2      = 0x124U,	/**< Timer0 chan2 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_2     = 0x125U,	/**< Timer0 chan2 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_3      = 0x126U,	/**< Timer0 chan3 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_3     = 0x127U,	/**< Timer0 chan3 output compare, plck1 pulse */
	PIS_TIMER0_INPUT_4      = 0x128U,	/**< Timer0 chan4 input catch, plck1 pulse */
	PIS_TIMER0_OUTPUT_4     = 0x129U,	/**< Timer0 chan4 output compare, plck1 pulse */
	PIS_TIMER1_UPDATA       = 0x130U,	/**< Timer1 updata, plck1 pulse */
	PIS_TIMER1_TRIG         = 0x131U,	/**< Timer1 trig, plck1 pulse */
	PIS_TIMER1_INPUT_1      = 0x132U,	/**< Timer1 chan1 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_1     = 0x133U,	/**< Timer1 chan1 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_2      = 0x134U,	/**< Timer1 chan2 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_2     = 0x135U,	/**< Timer1 chan2 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_3      = 0x136U,	/**< Timer1 chan3 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_3     = 0x137U,	/**< Timer1 chan3 output compare, plck1 pulse */
	PIS_TIMER1_INPUT_4      = 0x138U,	/**< Timer1 chan4 input catch, plck1 pulse */
	PIS_TIMER1_OUTPUT_4     = 0x139U,	/**< Timer1 chan4 output compare, plck1 pulse */
	PIS_TIMER2_UPDATA       = 0x140U,	/**< Timer2 updata, plck1 pulse */
	PIS_TIMER2_TRIG         = 0x141U,	/**< Timer2 trig, plck1 pulse */
	PIS_TIMER2_INPUT_1      = 0x142U,	/**< Timer2 chan1 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_1     = 0x143U,	/**< Timer2 chan1 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_2      = 0x144U,	/**< Timer2 chan2 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_2     = 0x145U,	/**< Timer2 chan2 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_3      = 0x146U,	/**< Timer2 chan3 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_3     = 0x147U,	/**< Timer2 chan3 output compare, plck1 pulse */
	PIS_TIMER2_INPUT_4      = 0x148U,	/**< Timer2 chan4 input catch, plck1 pulse */
	PIS_TIMER2_OUTPUT_4     = 0x149U,	/**< Timer2 chan4 output compare, plck1 pulse */
	PIS_TIMER3_UPDATA       = 0x150U,	/**< Timer3 updata, plck1 pulse */
	PIS_TIMER3_TRIG         = 0x151U,	/**< Timer3 trig, plck1 pulse */
	PIS_TIMER3_INPUT_1      = 0x152U,	/**< Timer3 chan1 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_1     = 0x153U,	/**< Timer3 chan1 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_2      = 0x154U,	/**< Timer3 chan2 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_2     = 0x155U,	/**< Timer3 chan2 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_3      = 0x156U,	/**< Timer3 chan3 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_3     = 0x157U,	/**< Timer3 chan3 output compare, plck1 pulse */
	PIS_TIMER3_INPUT_4      = 0x158U,	/**< Timer3 chan4 input catch, plck1 pulse */
	PIS_TIMER3_OUTPUT_4     = 0x159U,	/**< Timer3 chan4 output compare, plck1 pulse */
	PIS_RTC_CLOCK           = 0x160U,	/**< Rtc clock, pulse,support async */
	PIS_RTC_ALARM           = 0x161U,	/**< Rtc alarm, pulse,support async */
	PIS_LPTIMER0_SYN_UPDATA = 0x170U,	/**< Lptimer0 syn updata, pulse,support async */
	PIS_LPTIMER0_ASY_UPDATA = 0x171U,	/**< Lptimer0 asy updata, pulse,support async */
	PIS_LPUART0_ASY_RECV    = 0x180U,	/**< Lpuart0 asy recv, pulse,support async */
	PIS_LPUART0_ASY_SEND    = 0x181U,	/**< Lpuart0 asy send, pulse,support async */
	PIS_LPUART0_SYN_RECV    = 0x182U,	/**< Lpuart0 syn recv, pulse,support async */
	PIS_LPUART0_SYN_SEND    = 0x183U,	/**< Lpuart0 syn recv, pulse,support async */
	PIS_DMA                 = 0x190U,	/**< Dma, pulse,support async */
	PIS_ADC1_INSERT         = 0x1a0U,	/**< Adc1 insert, pclk2 pulse,support async */
	PIS_ADC1_NORMAL         = 0x1a1U,	/**< Adc1 normal, pclk2 pulse,support async */
	PIS_ADC1_RESERVE        = 0x1a2U,	/**< Adc1 reserve */
} pis_src_t;

/**
  * @brief Consumer entry
  */
typedef enum {
	PIS_CH12_TIMER0_ITR0  = 0x003CU,	/** Tim0 internal input chan0 */
	PIS_CH13_TIMER0_ITR1  = 0x003DU,	/** Tim0 internal input chan1 */
	PIS_CH14_TIMER0_ITR2  = 0x003EU,	/** Tim0 internal input chan2 */
	PIS_CH15_TIMER0_ITR3  = 0x003FU,	/** Tim0 internal input chan3 */
	PIS_CH12_TIMER1_ITR0  = 0x003CU,	/** Tim1 internal input chan0 */
	PIS_CH13_TIMER1_ITR1  = 0x003DU,	/** Tim1 internal input chan1 */
	PIS_CH14_TIMER1_ITR2  = 0x003EU,	/** Tim1 internal input chan2 */
	PIS_CH15_TIMER1_ITR3  = 0x003FU,	/** Tim1 internal input chan3 */
	PIS_CH12_TIMER2_ITR0  = 0x003CU,	/** Tim2 internal input chan0 */
	PIS_CH13_TIMER2_ITR1  = 0x003DU,	/** Tim2 internal input chan1 */
	PIS_CH14_TIMER2_ITR2  = 0x003EU,	/** Tim2 internal input chan2 */
	PIS_CH15_TIMER2_ITR3  = 0x003FU,	/** Tim2 internal input chan3 */
	PIS_CH12_TIMER3_ITR0  = 0x003CU,	/** Tim3 internal input chan0 */
	PIS_CH13_TIMER3_ITR1  = 0x003DU,	/** Tim3 internal input chan1 */
	PIS_CH14_TIMER3_ITR2  = 0x003EU,	/** Tim3 internal input chan2 */
	PIS_CH15_TIMER3_ITR3  = 0x003FU,	/** Tim3 internal input chan3 */
	PIS_CH6_ADC0_NORMAL   = 0x0036U,	/** ADC0 normal transform */
	PIS_CH7_ADC0_INSERT   = 0x0037U,	/** ADC0 insert transform */
	PIS_CH0_ADC1_NORMAL   = 0x0030U,	/** ADC1 normal transform */
	PIS_CH1_ADC1_INSERT   = 0x0031U,	/** ADC1 insert transform */
	PIS_CH0_LPTIM0_EXT0   = 0x0030U,	/** Lptim0 external trigger 0 */
	PIS_CH1_LPTIM0_EXT1   = 0x0031U,	/** Lptim0 external trigger 1 */
	PIS_CH2_LPTIM0_EXT2   = 0x0032U,	/** Lptim0 external trigger 2 */
	PIS_CH3_LPTIM0_EXT3   = 0x0033U,	/** Lptim0 external trigger 3 */
	PIS_CH4_LPTIM0_EXT4   = 0x0034U,	/** Lptim0 external trigger 4 */
	PIS_CH5_LPTIM0_EXT5   = 0x0035U,	/** Lptim0 external trigger 5 */
	PIS_CH6_LPTIM0_EXT6   = 0x0036U,	/** Lptim0 external trigger 6 */
	PIS_CH7_LPTIM0_EXT7   = 0x0037U,	/** Lptim0 external trigger 7 */
	PIS_CH7_DMA_REQUEST   = 0x0037U,	/** DMA request 7 */
	PIS_CH15_LPUART0_RXD  = 0x081FU,	/**< Lpuart Rx data */
	PIS_CH14_UART5_RXD    = 0x071EU,	/**< Uart5 Rx data */
	PIS_CH13_UART4_RXD    = 0x061DU,	/**< Uart4 Rx data */
	PIS_CH12_UART3_RXD    = 0x031CU,	/**< Uart3 Rx data */
	PIS_CH11_UART2_RXD    = 0x021BU,	/**< Uart2 Rx data */
	PIS_CH10_UART1_RXD    = 0x011AU,	/**< Uart1 Rx data */
	PIS_CH9_UART0_RXD     = 0x0019U,	/**< Uart0 Rx data  */
	PIS_CH8_TIMER3_CH4IN  = 0x1B08U,	/**< Tim3 input chan4 */
	PIS_CH8_TIMER2_CH4IN  = 0x1308U,	/**< Tim2 input chan4 */
	PIS_CH8_SPI1_CLK      = 0x0F18U,	/**< Spi1 clk */
	PIS_CH7_TIMER3_CH3IN  = 0x1A07U,	/**< Tim3 input chan3 */
	PIS_CH7_TIMER2_CH3IN  = 0x1207U,	/**< Tim2 input chan3 */
	PIS_CH7_SPI1_RX       = 0x0E17U,	/**< Spi1 rx */
	PIS_CH6_TIMER3_CH2IN  = 0x1906U,	/**< Tim3 input chan2 */
	PIS_CH6_TIMER2_CH2IN  = 0x1106U,	/**< Tim2 input chan2 */
	PIS_CH6_SPI0_CLK      = 0x0D16U,	/**< SPI0 CLK */
	PIS_CH5_TIMER3_CH1IN  = 0x1805U,	/**< Tim3 input chan1 */
	PIS_CH5_TIMER2_CH1IN  = 0x1005U,	/**< Tim2 input chan1 */
	PIS_CH5_SPI0_RX       = 0x0C15U,	/**< SPI0 RX */
	PIS_CH4_TIMER1_CH4IN  = 0x0B04U,	/**< Tim1 input chan4 */
	PIS_CH4_TIMER0_CH4IN  = 0x0304U,	/**< Tim0 input chan4 */
	PIS_CH3_TIMER1_CH3IN  = 0x0A03U,	/**< Tim1 input chan3 */
	PIS_CH3_TIMER0_CH3IN  = 0x0203U,	/**< Tim0 input chan3 */
	PIS_CH2_TIMER1_CH2IN  = 0x0902U,	/**< Tim1 input chan2 */
	PIS_CH2_TIMER0_CH2IN  = 0x0102U,	/**< Tim0 input chan2 */
	PIS_CH1_TIMER1_CH1IN  = 0x0801U,	/**< Tim1 input chan1 */
	PIS_CH0_TIMER0_CH1IN  = 0x0000U,	/**< Tim0 input chan1 */
	PIS_CH0_TIMER0_BRKIN  = 0x0400U,	/**< Tim0 break in */
	PIS_CH0_TIMER1_BRKIN  = 0x0C00U,	/**< Tim1 break in */
	PIS_TRIG_RESERVE      = 0xFFFFU,	/**< Other Consumer */
} pis_trig_t;

/**
  * @brief Clock select
  */
typedef enum {
	PIS_CLK_PCLK1    = 0U,	/**< APB1 peripherals clock */
	PIS_CLK_PCLK2    = 1U,	/**< APB2 peripherals clock */
	PIS_CLK_SYS      = 2U,	/**< AHB peripherals clock */
	PIS_CLK_RESERVE  = 3U,	/**< reserve clock */
} pis_clock_t;

/**
  * @brief Level select
  */
typedef enum {
	PIS_EDGE_NONE    = 0U,	/**< None edge */
	PIS_EDGE_UP      = 1U,	/**< Up edge */
	PIS_EDGE_DOWN    = 2U,	/**< Down edge */
	PIS_EDGE_UP_DOWN = 3U,	/**< Up and down edge */
} pis_edge_t;

/**
  * @brief Output style
  */
typedef enum {
	PIS_OUT_LEVEL = 0U,	/**< Level */
	PIS_OUT_PULSE = 1U,	/**< Pulse */
} pis_output_t;
/**
  * @brief Sync select
  */
typedef enum {
	PIS_SYN_DIRECT		= 0U,	/**< Direct */
	PIS_SYN_LEVEL_ASY_APB1	= 1U,	/**< Producer level signal and Consumer in APB1 */
	PIS_SYN_LEVEL_ASY_APB2	= 2U,	/**< Producer level signal and Consumer in APB2 */
	PIS_SYN_LEVEL_ASY_AHB	= 3U,	/**< Producer level signal and Consumer in AHB */
	PIS_SYN_PULSE_ASY_APB1	= 4U,	/**< Producer Pulse signal and Consumer in APB1 */
	PIS_SYN_PULSE_ASY_APB2	= 5U,	/**< Producer Pulse signal and Consumer in APB2 */
	PIS_SYN_PULSE_ASY_AHB	= 6U,	/**< Producer Pulse signal and Consumer in AHB */
} pis_syncsel_t;

/**
  * @brief Pis channel
  */
typedef enum {
	PIS_CH_0 = 0U,	/**< Channel 0 */
	PIS_CH_1 = 1U,	/**< Channel 1 */
	PIS_CH_2 = 2U,	/**< Channel 2 */
	PIS_CH_3 = 3U,	/**< Channel 3 */
	PIS_CH_4 = 4U,	/**< Channel 4 */
	PIS_CH_5 = 5U,	/**< Channel 5 */
	PIS_CH_6 = 6U,	/**< Channel 6 */
	PIS_CH_7 = 7U,	/**< Channel 7 */
	PIS_CH_8 = 8U,	/**< Channel 8 */
	PIS_CH_9 = 9U,	/**< Channel 9 */
	PIS_CH_10 = 10U,/**< Channel 10 */
	PIS_CH_11 = 11U,/**< Channel 11 */
	PIS_CH_12 = 12U,/**< Channel 12 */
	PIS_CH_13 = 13U,/**< Channel 13 */
	PIS_CH_14 = 14U,/**< Channel 14 */
	PIS_CH_15 = 15U,/**< Channel 15 */
} pis_ch_t;

/**
  * @brief Pis output channel
  */
typedef enum {
	PIS_OUT_CH_0 = 0U,	/**< Channel 0 */
	PIS_OUT_CH_1 = 1U,	/**< Channel 1 */
	PIS_OUT_CH_2 = 2U,	/**< Channel 2 */
	PIS_OUT_CH_3 = 3U,	/**< Channel 3 */
} pis_out_ch_t;

/**
  * @brief Indirect value,no care of it.
  */
typedef enum {
	PIS_CON_0    = 0U,	/**< Con 0 */
	PIS_CON_1    = 1U,	/**< Con 1 */
	PIS_CON_NONE = 2U,	/**< None */
} pis_con_t;

/**
  * @brief PIS state structures definition
  */
typedef enum {
	PIS_STATE_RESET   = 0x00U,	/**< Peripheral is not initialized */
	PIS_STATE_READY   = 0x01U,	/**< Peripheral Initialized and ready for use */
	PIS_STATE_BUSY    = 0x02U,	/**< An internal process is ongoing */
	PIS_STATE_TIMEOUT = 0x03U,	/**< Timeout state */
	PIS_STATE_ERROR   = 0x04U,	/**< Error */
} pis_state_t;

/**
  * @brief PIS modulate target
  */
typedef enum {
	PIS_UART0_TX   = 0U,	/**< Modulate uart0 tx */
	PIS_UART1_TX   = 1U,	/**< Modulate uart1 tx */
	PIS_UART2_TX   = 2U,	/**< Modulate uart2 tx */
	PIS_UART3_TX   = 3U,	/**< Modulate uart3 tx */
	PIS_LPUART0_TX = 4U,	/**< Modulate lpuart0 tx */
} pis_modu_targ_t;

/**
  * @brief PIS modulate level
  */
typedef enum {
	PIS_LOW_LEVEL  = 0U,	/**< Modulate low level */
	PIS_HIGH_LEVEL = 1U,	/**< Modulate high level */
} pis_modu_level_t;

/**
  * @brief PIS modulate source
  */
typedef enum {
	PIS_SRC_NONE   = 0U,	/**< Stop modulate */
	PIS_SRC_TIMER0 = 1U,	/**< Modulate source is TIMER0 */
	PIS_SRC_TIMER1 = 2U,	/**< Modulate source is TIMER1 */
	PIS_SRC_TIMER2 = 3U,	/**< Modulate source is TIMER2 */
	PIS_SRC_TIMER3 = 4U,	/**< Modulate source is TIMER3 */
	PIS_SRC_TIMER6 = 5U,	/**< Modulate source is TIMER6 */
	PIS_SRC_TIMER7 = 6U,	/**< Modulate source is TIMER7 */
	PIS_SRC_LPTIM0 = 7U,	/**< Modulate source is LPTIM0 */
	PIS_SRC_BUZ    = 8U,	/**< Modulate source is buz */
} pis_modu_src_t;

/**
  * @brief PIS modulate channel
  */
typedef enum {
	PIS_TIMER_CH1 = 0U,	/**< Src is TIMERx and choose channel 1 */
	PIS_TIMER_CH2 = 1U,	/**< Src is TIMERx and choose channel 2 */
	PIS_TIMER_CH3 = 2U,	/**< Src is TIMERx and choose channel 3 */
	PIS_TIMER_CH4 = 3U,	/**< Src is TIMERx and choose channel 4 */
} pis_modu_channel_t;

/**
  * @brief PIS input channel chose
  */
typedef enum {
	PIS_NONE_INPUT = 0U,	/**< Consumer input none */
	PIS_PORT_INPUT = 1U,	/**< Consumer input choose external port */
	PIS_CHAN_INPUT = 2U,	/**< Consumer input choose pis channel */
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
				 ((x) == PIS_ADC0_INSERT)	|| \
				 ((x) == PIS_ADC0_NORMAL)	|| \
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
				 ((x) == PIS_TIMER2_OUTPUT_3)   || \
				 ((x) == PIS_TIMER2_INPUT_4)    || \
				 ((x) == PIS_TIMER2_OUTPUT_4)   || \
				 ((x) == PIS_TIMER3_UPDATA)     || \
				 ((x) == PIS_TIMER3_TRIG)       || \
				 ((x) == PIS_TIMER3_INPUT_1)    || \
				 ((x) == PIS_TIMER3_OUTPUT_1)   || \
				 ((x) == PIS_TIMER3_INPUT_2)    || \
				 ((x) == PIS_TIMER3_OUTPUT_2)   || \
				 ((x) == PIS_TIMER3_INPUT_3)    || \
				 ((x) == PIS_TIMER3_OUTPUT_3)   || \
				 ((x) == PIS_TIMER3_INPUT_4)    || \
				 ((x) == PIS_TIMER3_OUTPUT_4)   || \
				 ((x) == PIS_RTC_CLOCK)         || \
				 ((x) == PIS_RTC_ALARM)         || \
				 ((x) == PIS_LPTIMER0_SYN_UPDATA) || \
				 ((x) == PIS_LPTIMER0_ASY_UPDATA) || \
				 ((x) == PIS_LPUART0_ASY_RECV)    || \
				 ((x) == PIS_LPUART0_ASY_SEND)    || \
				 ((x) == PIS_LPUART0_SYN_RECV)    || \
				 ((x) == PIS_LPUART0_SYN_SEND)    || \
				 ((x) == PIS_DMA)                 || \
				 ((x) == PIS_ADC1_INSERT)         || \
				 ((x) == PIS_ADC1_NORMAL)         || \
				 ((x) == PIS_ADC1_RESERVE))
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
				 ((x) == PIS_CH6_ADC0_NORMAL )  || \
				 ((x) == PIS_CH7_ADC0_INSERT)   || \
				 ((x) == PIS_CH0_ADC1_NORMAL)   || \
				 ((x) == PIS_CH1_ADC1_INSERT)   || \
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
