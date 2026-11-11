/**************************************************************************//**
 * @file
 * @brief efm32gg_af_pins Register and Bit Field definitions
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
 * @defgroup EFM32GG_AF_Pins
 * @{
 *****************************************************************************/

/** AF pin for function f */
#define AF_CMU_CLK0_PIN(f)          ((f) == 0 ? 2 : (f) == 1 ? 12 : (f) == 2 ? 7 :  -1)
#define AF_CMU_CLK1_PIN(f)          ((f) == 0 ? 1 : (f) == 1 ? 8 : (f) == 2 ? 12 :  -1)
#define AF_LESENSE_CH0_PIN(f)       ((f) == 0 ? 0 :  -1)
#define AF_LESENSE_CH1_PIN(f)       ((f) == 0 ? 1 :  -1)
#define AF_LESENSE_CH2_PIN(f)       ((f) == 0 ? 2 :  -1)
#define AF_LESENSE_CH3_PIN(f)       ((f) == 0 ? 3 :  -1)
#define AF_LESENSE_CH4_PIN(f)       ((f) == 0 ? 4 :  -1)
#define AF_LESENSE_CH5_PIN(f)       ((f) == 0 ? 5 :  -1)
#define AF_LESENSE_CH6_PIN(f)       ((f) == 0 ? 6 :  -1)
#define AF_LESENSE_CH7_PIN(f)       ((f) == 0 ? 7 :  -1)
#define AF_LESENSE_CH8_PIN(f)       ((f) == 0 ? 8 :  -1)
#define AF_LESENSE_CH9_PIN(f)       ((f) == 0 ? 9 :  -1)
#define AF_LESENSE_CH10_PIN(f)      ((f) == 0 ? 10 :  -1)
#define AF_LESENSE_CH11_PIN(f)      ((f) == 0 ? 11 :  -1)
#define AF_LESENSE_CH12_PIN(f)      ((f) == 0 ? 12 :  -1)
#define AF_LESENSE_CH13_PIN(f)      ((f) == 0 ? 13 :  -1)
#define AF_LESENSE_CH14_PIN(f)      ((f) == 0 ? 14 :  -1)
#define AF_LESENSE_CH15_PIN(f)      ((f) == 0 ? 15 :  -1)
#define AF_LESENSE_ALTEX0_PIN(f)    ((f) == 0 ? 6 :  -1)
#define AF_LESENSE_ALTEX1_PIN(f)    ((f) == 0 ? 7 :  -1)
#define AF_LESENSE_ALTEX2_PIN(f)    ((f) == 0 ? 3 :  -1)
#define AF_LESENSE_ALTEX3_PIN(f)    ((f) == 0 ? 4 :  -1)
#define AF_LESENSE_ALTEX4_PIN(f)    ((f) == 0 ? 5 :  -1)
#define AF_LESENSE_ALTEX5_PIN(f)    ((f) == 0 ? 11 :  -1)
#define AF_LESENSE_ALTEX6_PIN(f)    ((f) == 0 ? 12 :  -1)
#define AF_LESENSE_ALTEX7_PIN(f)    ((f) == 0 ? 13 :  -1)
#define AF_EBI_AD00_PIN(f)          ((f) == 0 ? 8 : (f) == 1 ? 8 : (f) == 2 ? 8 :  -1)
#define AF_EBI_AD01_PIN(f)          ((f) == 0 ? 9 : (f) == 1 ? 9 : (f) == 2 ? 9 :  -1)
#define AF_EBI_AD02_PIN(f)          ((f) == 0 ? 10 : (f) == 1 ? 10 : (f) == 2 ? 10 :  -1)
#define AF_EBI_AD03_PIN(f)          ((f) == 0 ? 11 : (f) == 1 ? 11 : (f) == 2 ? 11 :  -1)
#define AF_EBI_AD04_PIN(f)          ((f) == 0 ? 12 : (f) == 1 ? 12 : (f) == 2 ? 12 :  -1)
#define AF_EBI_AD05_PIN(f)          ((f) == 0 ? 13 : (f) == 1 ? 13 : (f) == 2 ? 13 :  -1)
#define AF_EBI_AD06_PIN(f)          ((f) == 0 ? 14 : (f) == 1 ? 14 : (f) == 2 ? 14 :  -1)
#define AF_EBI_AD07_PIN(f)          ((f) == 0 ? 15 : (f) == 1 ? 15 : (f) == 2 ? 15 :  -1)
#define AF_EBI_AD08_PIN(f)          ((f) == 0 ? 15 : (f) == 1 ? 15 : (f) == 2 ? 15 :  -1)
#define AF_EBI_AD09_PIN(f)          ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 0 :  -1)
#define AF_EBI_AD10_PIN(f)          ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 1 :  -1)
#define AF_EBI_AD11_PIN(f)          ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 2 :  -1)
#define AF_EBI_AD12_PIN(f)          ((f) == 0 ? 3 : (f) == 1 ? 3 : (f) == 2 ? 3 :  -1)
#define AF_EBI_AD13_PIN(f)          ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 4 :  -1)
#define AF_EBI_AD14_PIN(f)          ((f) == 0 ? 5 : (f) == 1 ? 5 : (f) == 2 ? 5 :  -1)
#define AF_EBI_AD15_PIN(f)          ((f) == 0 ? 6 : (f) == 1 ? 6 : (f) == 2 ? 6 :  -1)
#define AF_EBI_CS0_PIN(f)           ((f) == 0 ? 9 : (f) == 1 ? 9 : (f) == 2 ? 9 :  -1)
#define AF_EBI_CS1_PIN(f)           ((f) == 0 ? 10 : (f) == 1 ? 10 : (f) == 2 ? 10 :  -1)
#define AF_EBI_CS2_PIN(f)           ((f) == 0 ? 11 : (f) == 1 ? 11 : (f) == 2 ? 11 :  -1)
#define AF_EBI_CS3_PIN(f)           ((f) == 0 ? 12 : (f) == 1 ? 12 : (f) == 2 ? 12 :  -1)
#define AF_EBI_ARDY_PIN(f)          ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 2 :  -1)
#define AF_EBI_ALE_PIN(f)           ((f) == 0 ? 3 : (f) == 1 ? 11 : (f) == 2 ? 11 :  -1)
#define AF_EBI_WEn_PIN(f)           ((f) == 0 ? 4 : (f) == 1 ? 8 : (f) == 2 ? 4 :  -1)
#define AF_EBI_REn_PIN(f)           ((f) == 0 ? 5 : (f) == 1 ? 9 : (f) == 2 ? 5 :  -1)
#define AF_EBI_NANDWEn_PIN(f)       ((f) == 0 ? 5 : (f) == 1 ? 5 : (f) == 2 ? 5 :  -1)
#define AF_EBI_NANDREn_PIN(f)       ((f) == 0 ? 3 : (f) == 1 ? 3 : (f) == 2 ? 3 :  -1)
#define AF_EBI_BL0_PIN(f)           ((f) == 0 ? 6 : (f) == 1 ? 6 : (f) == 2 ? 6 :  -1)
#define AF_EBI_BL1_PIN(f)           ((f) == 0 ? 7 : (f) == 1 ? 7 : (f) == 2 ? 7 :  -1)
#define AF_EBI_A00_PIN(f)           ((f) == 0 ? 12 : (f) == 1 ? 12 : (f) == 2 ? 12 :  -1)
#define AF_EBI_A01_PIN(f)           ((f) == 0 ? 13 : (f) == 1 ? 13 : (f) == 2 ? 13 :  -1)
#define AF_EBI_A02_PIN(f)           ((f) == 0 ? 14 : (f) == 1 ? 14 : (f) == 2 ? 14 :  -1)
#define AF_EBI_A03_PIN(f)           ((f) == 0 ? 9 : (f) == 1 ? 9 : (f) == 2 ? 9 :  -1)
#define AF_EBI_A04_PIN(f)           ((f) == 0 ? 10 : (f) == 1 ? 10 : (f) == 2 ? 10 :  -1)
#define AF_EBI_A05_PIN(f)           ((f) == 0 ? 6 : (f) == 1 ? 6 : (f) == 2 ? 6 :  -1)
#define AF_EBI_A06_PIN(f)           ((f) == 0 ? 7 : (f) == 1 ? 7 : (f) == 2 ? 7 :  -1)
#define AF_EBI_A07_PIN(f)           ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 0 :  -1)
#define AF_EBI_A08_PIN(f)           ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 1 :  -1)
#define AF_EBI_A09_PIN(f)           ((f) == 0 ? 2 : (f) == 1 ? 9 : (f) == 2 ? 9 :  -1)
#define AF_EBI_A10_PIN(f)           ((f) == 0 ? 3 : (f) == 1 ? 10 : (f) == 2 ? 10 :  -1)
#define AF_EBI_A11_PIN(f)           ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 4 :  -1)
#define AF_EBI_A12_PIN(f)           ((f) == 0 ? 5 : (f) == 1 ? 5 : (f) == 2 ? 5 :  -1)
#define AF_EBI_A13_PIN(f)           ((f) == 0 ? 6 : (f) == 1 ? 6 : (f) == 2 ? 6 :  -1)
#define AF_EBI_A14_PIN(f)           ((f) == 0 ? 7 : (f) == 1 ? 7 : (f) == 2 ? 7 :  -1)
#define AF_EBI_A15_PIN(f)           ((f) == 0 ? 8 : (f) == 1 ? 8 : (f) == 2 ? 8 :  -1)
#define AF_EBI_A16_PIN(f)           ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 0 :  -1)
#define AF_EBI_A17_PIN(f)           ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 1 :  -1)
#define AF_EBI_A18_PIN(f)           ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 2 :  -1)
#define AF_EBI_A19_PIN(f)           ((f) == 0 ? 3 : (f) == 1 ? 3 : (f) == 2 ? 3 :  -1)
#define AF_EBI_A20_PIN(f)           ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 4 :  -1)
#define AF_EBI_A21_PIN(f)           ((f) == 0 ? 5 : (f) == 1 ? 5 : (f) == 2 ? 5 :  -1)
#define AF_EBI_A22_PIN(f)           ((f) == 0 ? 6 : (f) == 1 ? 6 : (f) == 2 ? 6 :  -1)
#define AF_EBI_A23_PIN(f)           ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 0 :  -1)
#define AF_EBI_A24_PIN(f)           ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 1 :  -1)
#define AF_EBI_A25_PIN(f)           ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 2 :  -1)
#define AF_EBI_A26_PIN(f)           ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 4 :  -1)
#define AF_EBI_A27_PIN(f)           ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 2 :  -1)
#define AF_EBI_CSTFT_PIN(f)         ((f) == 0 ? 7 : (f) == 1 ? 7 : (f) == 2 ? 7 :  -1)
#define AF_EBI_DCLK_PIN(f)          ((f) == 0 ? 8 : (f) == 1 ? 8 : (f) == 2 ? 8 :  -1)
#define AF_EBI_DTEN_PIN(f)          ((f) == 0 ? 9 : (f) == 1 ? 9 : (f) == 2 ? 9 :  -1)
#define AF_EBI_VSNC_PIN(f)          ((f) == 0 ? 10 : (f) == 1 ? 10 : (f) == 2 ? 10 :  -1)
#define AF_EBI_HSNC_PIN(f)          ((f) == 0 ? 11 : (f) == 1 ? 11 : (f) == 2 ? 11 :  -1)
#define AF_PRS_CH0_PIN(f)           ((f) == 0 ? 0 : (f) == 1 ? 3 :  -1)
#define AF_PRS_CH1_PIN(f)           ((f) == 0 ? 1 : (f) == 1 ? 4 :  -1)
#define AF_PRS_CH2_PIN(f)           ((f) == 0 ? 0 : (f) == 1 ? 5 :  -1)
#define AF_PRS_CH3_PIN(f)           ((f) == 0 ? 1 : (f) == 1 ? 8 :  -1)
#define AF_TIMER0_CC0_PIN(f)        ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 6 : (f) == 3 ? 1 : (f) == 4 ? 0 : (f) == 5 ? 0 :  -1)
#define AF_TIMER0_CC1_PIN(f)        ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 7 : (f) == 3 ? 2 : (f) == 4 ? 0 : (f) == 5 ? 1 :  -1)
#define AF_TIMER0_CC2_PIN(f)        ((f) == 0 ? 2 : (f) == 1 ? 2 : (f) == 2 ? 8 : (f) == 3 ? 3 : (f) == 4 ? 1 : (f) == 5 ? 2 :  -1)
#define AF_TIMER0_CDTI0_PIN(f)      ((f) == 0 ? 3 : (f) == 1 ? 13 : (f) == 2 ? 3 : (f) == 3 ? 13 : (f) == 4 ? 2 : (f) == 5 ? 3 :  -1)
#define AF_TIMER0_CDTI1_PIN(f)      ((f) == 0 ? 4 : (f) == 1 ? 14 : (f) == 2 ? 4 : (f) == 3 ? 14 : (f) == 4 ? 3 : (f) == 5 ? 4 :  -1)
#define AF_TIMER0_CDTI2_PIN(f)      ((f) == 0 ? 5 : (f) == 1 ? 15 : (f) == 2 ? 5 : (f) == 3 ? 15 : (f) == 4 ? 4 : (f) == 5 ? 5 :  -1)
#define AF_TIMER1_CC0_PIN(f)        ((f) == 0 ? 13 : (f) == 1 ? 10 : (f) == 2 ? 0 : (f) == 3 ? 7 : (f) == 4 ? 6 :  -1)
#define AF_TIMER1_CC1_PIN(f)        ((f) == 0 ? 14 : (f) == 1 ? 11 : (f) == 2 ? 1 : (f) == 3 ? 8 : (f) == 4 ? 7 :  -1)
#define AF_TIMER1_CC2_PIN(f)        ((f) == 0 ? 15 : (f) == 1 ? 12 : (f) == 2 ? 2 : (f) == 3 ? 11 : (f) == 4 ? 13 :  -1)
#define AF_TIMER1_CDTI0_PIN(f)      (-1)
#define AF_TIMER1_CDTI1_PIN(f)      (-1)
#define AF_TIMER1_CDTI2_PIN(f)      (-1)
#define AF_TIMER2_CC0_PIN(f)        ((f) == 0 ? 8 : (f) == 1 ? 12 : (f) == 2 ? 8 :  -1)
#define AF_TIMER2_CC1_PIN(f)        ((f) == 0 ? 9 : (f) == 1 ? 13 : (f) == 2 ? 9 :  -1)
#define AF_TIMER2_CC2_PIN(f)        ((f) == 0 ? 10 : (f) == 1 ? 14 : (f) == 2 ? 10 :  -1)
#define AF_TIMER2_CDTI0_PIN(f)      (-1)
#define AF_TIMER2_CDTI1_PIN(f)      (-1)
#define AF_TIMER2_CDTI2_PIN(f)      (-1)
#define AF_TIMER3_CC0_PIN(f)        ((f) == 0 ? 14 : (f) == 1 ? 0 :  -1)
#define AF_TIMER3_CC1_PIN(f)        ((f) == 0 ? 15 : (f) == 1 ? 1 :  -1)
#define AF_TIMER3_CC2_PIN(f)        ((f) == 0 ? 15 : (f) == 1 ? 2 :  -1)
#define AF_TIMER3_CDTI0_PIN(f)      (-1)
#define AF_TIMER3_CDTI1_PIN(f)      (-1)
#define AF_TIMER3_CDTI2_PIN(f)      (-1)
#define AF_USART0_TX_PIN(f)         ((f) == 0 ? 10 : (f) == 1 ? 7 : (f) == 2 ? 11 : (f) == 3 ? 13 : (f) == 4 ? 7 : (f) == 5 ? 0 :  -1)
#define AF_USART0_RX_PIN(f)         ((f) == 0 ? 11 : (f) == 1 ? 6 : (f) == 2 ? 10 : (f) == 3 ? 12 : (f) == 4 ? 8 : (f) == 5 ? 1 :  -1)
#define AF_USART0_CLK_PIN(f)        ((f) == 0 ? 12 : (f) == 1 ? 5 : (f) == 2 ? 9 : (f) == 3 ? 15 : (f) == 4 ? 13 : (f) == 5 ? 13 :  -1)
#define AF_USART0_CS_PIN(f)         ((f) == 0 ? 13 : (f) == 1 ? 4 : (f) == 2 ? 8 : (f) == 3 ? 14 : (f) == 4 ? 14 : (f) == 5 ? 14 :  -1)
#define AF_USART1_TX_PIN(f)         ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 7 :  -1)
#define AF_USART1_RX_PIN(f)         ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 6 :  -1)
#define AF_USART1_CLK_PIN(f)        ((f) == 0 ? 7 : (f) == 1 ? 2 : (f) == 2 ? 0 :  -1)
#define AF_USART1_CS_PIN(f)         ((f) == 0 ? 8 : (f) == 1 ? 3 : (f) == 2 ? 1 :  -1)
#define AF_USART2_TX_PIN(f)         ((f) == 0 ? 2 : (f) == 1 ? 3 :  -1)
#define AF_USART2_RX_PIN(f)         ((f) == 0 ? 3 : (f) == 1 ? 4 :  -1)
#define AF_USART2_CLK_PIN(f)        ((f) == 0 ? 4 : (f) == 1 ? 5 :  -1)
#define AF_USART2_CS_PIN(f)         ((f) == 0 ? 5 : (f) == 1 ? 6 :  -1)
#define AF_UART0_TX_PIN(f)          ((f) == 0 ? 6 : (f) == 1 ? 0 : (f) == 2 ? 3 : (f) == 3 ? 14 :  -1)
#define AF_UART0_RX_PIN(f)          ((f) == 0 ? 7 : (f) == 1 ? 1 : (f) == 2 ? 4 : (f) == 3 ? 15 :  -1)
#define AF_UART0_CLK_PIN(f)         (-1)
#define AF_UART0_CS_PIN(f)          (-1)
#define AF_UART1_TX_PIN(f)          ((f) == 0 ? 12 : (f) == 1 ? 10 : (f) == 2 ? 9 : (f) == 3 ? 2 :  -1)
#define AF_UART1_RX_PIN(f)          ((f) == 0 ? 13 : (f) == 1 ? 11 : (f) == 2 ? 10 : (f) == 3 ? 3 :  -1)
#define AF_UART1_CLK_PIN(f)         (-1)
#define AF_UART1_CS_PIN(f)          (-1)
#define AF_LEUART0_TX_PIN(f)        ((f) == 0 ? 4 : (f) == 1 ? 13 : (f) == 2 ? 14 : (f) == 3 ? 0 : (f) == 4 ? 2 :  -1)
#define AF_LEUART0_RX_PIN(f)        ((f) == 0 ? 5 : (f) == 1 ? 14 : (f) == 2 ? 15 : (f) == 3 ? 1 : (f) == 4 ? 0 :  -1)
#define AF_LEUART1_TX_PIN(f)        ((f) == 0 ? 6 : (f) == 1 ? 5 :  -1)
#define AF_LEUART1_RX_PIN(f)        ((f) == 0 ? 7 : (f) == 1 ? 6 :  -1)
#define AF_LETIMER0_OUT0_PIN(f)     ((f) == 0 ? 6 : (f) == 1 ? 11 : (f) == 2 ? 0 : (f) == 3 ? 4 :  -1)
#define AF_LETIMER0_OUT1_PIN(f)     ((f) == 0 ? 7 : (f) == 1 ? 12 : (f) == 2 ? 1 : (f) == 3 ? 5 :  -1)
#define AF_PCNT0_S0IN_PIN(f)        ((f) == 0 ? 13 : (f) == 1 ? 0 : (f) == 2 ? 0 : (f) == 3 ? 6 :  -1)
#define AF_PCNT0_S1IN_PIN(f)        ((f) == 0 ? 14 : (f) == 1 ? 1 : (f) == 2 ? 1 : (f) == 3 ? 7 :  -1)
#define AF_PCNT1_S0IN_PIN(f)        ((f) == 0 ? 4 : (f) == 1 ? 3 :  -1)
#define AF_PCNT1_S1IN_PIN(f)        ((f) == 0 ? 5 : (f) == 1 ? 4 :  -1)
#define AF_PCNT2_S0IN_PIN(f)        ((f) == 0 ? 0 : (f) == 1 ? 8 :  -1)
#define AF_PCNT2_S1IN_PIN(f)        ((f) == 0 ? 1 : (f) == 1 ? 9 :  -1)
#define AF_I2C0_SDA_PIN(f)          ((f) == 0 ? 0 : (f) == 1 ? 6 : (f) == 2 ? 6 : (f) == 3 ? 14 : (f) == 4 ? 0 : (f) == 5 ? 0 : (f) == 6 ? 12 :  -1)
#define AF_I2C0_SCL_PIN(f)          ((f) == 0 ? 1 : (f) == 1 ? 7 : (f) == 2 ? 7 : (f) == 3 ? 15 : (f) == 4 ? 1 : (f) == 5 ? 1 : (f) == 6 ? 13 :  -1)
#define AF_I2C1_SDA_PIN(f)          ((f) == 0 ? 4 : (f) == 1 ? 11 : (f) == 2 ? 0 :  -1)
#define AF_I2C1_SCL_PIN(f)          ((f) == 0 ? 5 : (f) == 1 ? 12 : (f) == 2 ? 1 :  -1)
#define AF_ACMP0_OUT_PIN(f)         ((f) == 0 ? 13 : (f) == 1 ? 2 : (f) == 2 ? 6 :  -1)
#define AF_ACMP1_OUT_PIN(f)         ((f) == 0 ? 2 : (f) == 1 ? 3 : (f) == 2 ? 7 :  -1)
#define AF_USB_VBUSEN_PIN(f)        ((f) == 0 ? 5 :  -1)
#define AF_USB_DMPU_PIN(f)          ((f) == 0 ? 2 :  -1)
#define AF_DBG_SWO_PIN(f)           ((f) == 0 ? 2 : (f) == 1 ? 15 : (f) == 2 ? 1 : (f) == 3 ? 2 :  -1)
#define AF_DBG_SWDIO_PIN(f)         ((f) == 0 ? 1 : (f) == 1 ? 1 : (f) == 2 ? 1 : (f) == 3 ? 1 :  -1)
#define AF_DBG_SWCLK_PIN(f)         ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 0 : (f) == 3 ? 0 :  -1)
#define AF_ETM_TCLK_PIN(f)          ((f) == 0 ? 7 : (f) == 1 ? 8 : (f) == 2 ? 6 : (f) == 3 ? 6 :  -1)
#define AF_ETM_TD0_PIN(f)           ((f) == 0 ? 6 : (f) == 1 ? 9 : (f) == 2 ? 7 : (f) == 3 ? 2 :  -1)
#define AF_ETM_TD1_PIN(f)           ((f) == 0 ? 3 : (f) == 1 ? 13 : (f) == 2 ? 3 : (f) == 3 ? 3 :  -1)
#define AF_ETM_TD2_PIN(f)           ((f) == 0 ? 4 : (f) == 1 ? 15 : (f) == 2 ? 4 : (f) == 3 ? 4 :  -1)
#define AF_ETM_TD3_PIN(f)           ((f) == 0 ? 5 : (f) == 1 ? 3 : (f) == 2 ? 5 : (f) == 3 ? 5 :  -1)

/** @} End of group EFM32GG_AF_Pins */


