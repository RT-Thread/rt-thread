/**************************************************************************//**
 * @file
 * @brief efm32g_af_annels.h Register and Bit Field definitions
 * @author Energy Micro AS
 * @version 3.0.0
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/
/**************************************************************************//**
 * @defgroup EFM32G_AF_Channels
 * @{
 *****************************************************************************/

/** AF channels connect the different on-chip peripherals with the af-mux */
#define AFCHAN_MAX          79
#define AFCHANLOC_MAX       4
/** Analog AF channels */
#define AFACHAN_MAX         37

/** Peripheral Alternate Function (AF) channels */
#define AF_CMU_CLK0         0
#define AF_CMU_CLK1         1
#define AF_EBI_AD00         2
#define AF_EBI_AD01         3
#define AF_EBI_AD02         4
#define AF_EBI_AD03         5
#define AF_EBI_AD04         6
#define AF_EBI_AD05         7
#define AF_EBI_AD06         8
#define AF_EBI_AD07         9
#define AF_EBI_AD08         10
#define AF_EBI_AD09         11
#define AF_EBI_AD10         12
#define AF_EBI_AD11         13
#define AF_EBI_AD12         14
#define AF_EBI_AD13         15
#define AF_EBI_AD14         16
#define AF_EBI_AD15         17
#define AF_EBI_CS0          18
#define AF_EBI_CS1          19
#define AF_EBI_CS2          20
#define AF_EBI_CS3          21
#define AF_EBI_WEn          22
#define AF_EBI_REn          23
#define AF_EBI_ARDY         24
#define AF_EBI_ALE          25
#define AF_TIMER0_CC0       26
#define AF_TIMER0_CC1       27
#define AF_TIMER0_CC2       28
#define AF_TIMER0_CDTI0     29
#define AF_TIMER0_CDTI1     30
#define AF_TIMER0_CDTI2     31
#define AF_TIMER1_CC0       32
#define AF_TIMER1_CC1       33
#define AF_TIMER1_CC2       34
#define AF_TIMER1_CDTI0     35
#define AF_TIMER1_CDTI1     36
#define AF_TIMER1_CDTI2     37
#define AF_TIMER2_CC0       38
#define AF_TIMER2_CC1       39
#define AF_TIMER2_CC2       40
#define AF_TIMER2_CDTI0     41
#define AF_TIMER2_CDTI1     42
#define AF_TIMER2_CDTI2     43
#define AF_USART0_TX        44
#define AF_USART0_RX        45
#define AF_USART0_CLK       46
#define AF_USART0_CS        47
#define AF_USART1_TX        48
#define AF_USART1_RX        49
#define AF_USART1_CLK       50
#define AF_USART1_CS        51
#define AF_USART2_TX        52
#define AF_USART2_RX        53
#define AF_USART2_CLK       54
#define AF_USART2_CS        55
#define AF_UART0_TX         56
#define AF_UART0_RX         57
#define AF_UART0_CLK        58
#define AF_UART0_CS         59
#define AF_LEUART0_TX       60
#define AF_LEUART0_RX       61
#define AF_LEUART1_TX       62
#define AF_LEUART1_RX       63
#define AF_LETIMER0_OUT0    64
#define AF_LETIMER0_OUT1    65
#define AF_PCNT0_S0IN       66
#define AF_PCNT0_S1IN       67
#define AF_PCNT1_S0IN       68
#define AF_PCNT1_S1IN       69
#define AF_PCNT2_S0IN       70
#define AF_PCNT2_S1IN       71
#define AF_I2C0_SDA         72
#define AF_I2C0_SCL         73
#define AF_ACMP0_OUT        74
#define AF_ACMP1_OUT        75
#define AF_DBG_SWO          76
#define AF_DBG_SWDIO        77
#define AF_DBG_SWCLK        78

/** Analog Alternate Function (AF) channels */
#define AFA_MSC_TM0         0
#define AFA_MSC_TM1         1
#define AFA_MSC_TM2         2
#define AFA_ADC0_CH0        3
#define AFA_ADC0_CH1        4
#define AFA_ADC0_CH2        5
#define AFA_ADC0_CH3        6
#define AFA_ADC0_CH4        7
#define AFA_ADC0_CH5        8
#define AFA_ADC0_CH6        9
#define AFA_ADC0_CH7        10
#define AFA_ADC0_VCM        11
#define AFA_DAC0_OUT0       12
#define AFA_DAC0_OUT1       13
#define AFA_ACMP0_CH0       14
#define AFA_ACMP0_CH1       15
#define AFA_ACMP0_CH2       16
#define AFA_ACMP0_CH3       17
#define AFA_ACMP0_CH4       18
#define AFA_ACMP0_CH5       19
#define AFA_ACMP0_CH6       20
#define AFA_ACMP0_CH7       21
#define AFA_ACMP1_CH0       22
#define AFA_ACMP1_CH1       23
#define AFA_ACMP1_CH2       24
#define AFA_ACMP1_CH3       25
#define AFA_ACMP1_CH4       26
#define AFA_ACMP1_CH5       27
#define AFA_ACMP1_CH6       28
#define AFA_ACMP1_CH7       29
#define AFA_LCD_BCAP_P      30
#define AFA_LCD_BCAP_N      31
#define AFA_LCD_BEXT        32
#define AFA_HFXTAL_P        33
#define AFA_HFXTAL_N        34
#define AFA_LFXTAL_P        35
#define AFA_LFXTAL_N        36

/** Digital Alternate Function (AF) */
#define AF_TIMER_CC0(i)       ((i) == 0 ? AF_TIMER0_CC0 : (i) == 1 ? AF_TIMER1_CC0 : (i) == 2 ? AF_TIMER2_CC0 :  -1)
#define AF_UART_CLK(i)        ((i) == 0 ? AF_UART0_CLK :  -1)
#define AF_I2C_SDA(i)         ((i) == 0 ? AF_I2C0_SDA :  -1)
#define AF_TIMER_CC1(i)       ((i) == 0 ? AF_TIMER0_CC1 : (i) == 1 ? AF_TIMER1_CC1 : (i) == 2 ? AF_TIMER2_CC1 :  -1)
#define AF_USART_CS(i)        ((i) == 0 ? AF_USART0_CS : (i) == 1 ? AF_USART1_CS : (i) == 2 ? AF_USART2_CS :  -1)
#define AF_I2C_SCL(i)         ((i) == 0 ? AF_I2C0_SCL :  -1)
#define AF_TIMER_CC2(i)       ((i) == 0 ? AF_TIMER0_CC2 : (i) == 1 ? AF_TIMER1_CC2 : (i) == 2 ? AF_TIMER2_CC2 :  -1)
#define AF_TIMER_CDTI1(i)     ((i) == 0 ? AF_TIMER0_CDTI1 : (i) == 1 ? AF_TIMER1_CDTI1 : (i) == 2 ? AF_TIMER2_CDTI1 :  -1)
#define AF_TIMER_CDTI0(i)     ((i) == 0 ? AF_TIMER0_CDTI0 : (i) == 1 ? AF_TIMER1_CDTI0 : (i) == 2 ? AF_TIMER2_CDTI0 :  -1)
#define AF_USART_CLK(i)       ((i) == 0 ? AF_USART0_CLK : (i) == 1 ? AF_USART1_CLK : (i) == 2 ? AF_USART2_CLK :  -1)
#define AF_UART_RX(i)         ((i) == 0 ? AF_UART0_RX :  -1)
#define AF_UART_TX(i)         ((i) == 0 ? AF_UART0_TX :  -1)
#define AF_LETIMER_OUT1(i)    ((i) == 0 ? AF_LETIMER0_OUT1 :  -1)
#define AF_LEUART_RX(i)       ((i) == 0 ? AF_LEUART0_RX : (i) == 1 ? AF_LEUART1_RX :  -1)
#define AF_PCNT_S1IN(i)       ((i) == 0 ? AF_PCNT0_S1IN : (i) == 1 ? AF_PCNT1_S1IN : (i) == 2 ? AF_PCNT2_S1IN :  -1)
#define AF_TIMER_CDTI2(i)     ((i) == 0 ? AF_TIMER0_CDTI2 : (i) == 1 ? AF_TIMER1_CDTI2 : (i) == 2 ? AF_TIMER2_CDTI2 :  -1)
#define AF_LEUART_TX(i)       ((i) == 0 ? AF_LEUART0_TX : (i) == 1 ? AF_LEUART1_TX :  -1)
#define AF_USART_TX(i)        ((i) == 0 ? AF_USART0_TX : (i) == 1 ? AF_USART1_TX : (i) == 2 ? AF_USART2_TX :  -1)
#define AF_LETIMER_OUT0(i)    ((i) == 0 ? AF_LETIMER0_OUT0 :  -1)
#define AF_ACMP_OUT(i)        ((i) == 0 ? AF_ACMP0_OUT : (i) == 1 ? AF_ACMP1_OUT :  -1)
#define AF_USART_RX(i)        ((i) == 0 ? AF_USART0_RX : (i) == 1 ? AF_USART1_RX : (i) == 2 ? AF_USART2_RX :  -1)
#define AF_UART_CS(i)         ((i) == 0 ? AF_UART0_CS :  -1)
#define AF_PCNT_S0IN(i)       ((i) == 0 ? AF_PCNT0_S0IN : (i) == 1 ? AF_PCNT1_S0IN : (i) == 2 ? AF_PCNT2_S0IN :  -1)
#define AFA_DAC_OUT1(i)       ((i) == 0 ? AFA_DAC0_OUT1 :  -1)
#define AFA_DAC_OUT0(i)       ((i) == 0 ? AFA_DAC0_OUT0 :  -1)
#define AFA_ADC_CH7(i)        ((i) == 0 ? AFA_ADC0_CH7 :  -1)
#define AFA_ADC_VCM(i)        ((i) == 0 ? AFA_ADC0_VCM :  -1)
#define AFA_ACMP_CH1(i)       ((i) == 0 ? AFA_ACMP0_CH1 : (i) == 1 ? AFA_ACMP1_CH1 :  -1)
#define AFA_ADC_CH0(i)        ((i) == 0 ? AFA_ADC0_CH0 :  -1)
#define AFA_ACMP_CH0(i)       ((i) == 0 ? AFA_ACMP0_CH0 : (i) == 1 ? AFA_ACMP1_CH0 :  -1)
#define AFA_ACMP_CH3(i)       ((i) == 0 ? AFA_ACMP0_CH3 : (i) == 1 ? AFA_ACMP1_CH3 :  -1)
#define AFA_ADC_CH1(i)        ((i) == 0 ? AFA_ADC0_CH1 :  -1)
#define AFA_ACMP_CH2(i)       ((i) == 0 ? AFA_ACMP0_CH2 : (i) == 1 ? AFA_ACMP1_CH2 :  -1)
#define AFA_ADC_CH2(i)        ((i) == 0 ? AFA_ADC0_CH2 :  -1)
#define AFA_ADC_CH3(i)        ((i) == 0 ? AFA_ADC0_CH3 :  -1)
#define AFA_ADC_CH4(i)        ((i) == 0 ? AFA_ADC0_CH4 :  -1)
#define AFA_ADC_CH5(i)        ((i) == 0 ? AFA_ADC0_CH5 :  -1)
#define AFA_ADC_CH6(i)        ((i) == 0 ? AFA_ADC0_CH6 :  -1)
#define AFA_ACMP_CH5(i)       ((i) == 0 ? AFA_ACMP0_CH5 : (i) == 1 ? AFA_ACMP1_CH5 :  -1)
#define AFA_ACMP_CH4(i)       ((i) == 0 ? AFA_ACMP0_CH4 : (i) == 1 ? AFA_ACMP1_CH4 :  -1)
#define AFA_ACMP_CH7(i)       ((i) == 0 ? AFA_ACMP0_CH7 : (i) == 1 ? AFA_ACMP1_CH7 :  -1)
#define AFA_ACMP_CH6(i)       ((i) == 0 ? AFA_ACMP0_CH6 : (i) == 1 ? AFA_ACMP1_CH6 :  -1)

/** @} End of group EFM32G_AF_Channels  */


