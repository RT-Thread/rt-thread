/**************************************************************************//**
 * @file
 * @brief efm32g_af_ports Register and Bit Field definitions
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
 * @defgroup EFM32G_AF_Ports
 * @{
 *****************************************************************************/

/** AF port for function f */
#define AF_CMU_CLK0_PORT(f)         ((f) == 0 ? 0 : (f) == 1 ? 2 :  -1)
#define AF_CMU_CLK1_PORT(f)         ((f) == 0 ? 0 : (f) == 1 ? 3 :  -1)
#define AF_EBI_AD00_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD01_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD02_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD03_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD04_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD05_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD06_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD07_PORT(f)         ((f) == 0 ? 4 :  -1)
#define AF_EBI_AD08_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD09_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD10_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD11_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD12_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD13_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD14_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_AD15_PORT(f)         ((f) == 0 ? 0 :  -1)
#define AF_EBI_CS0_PORT(f)          ((f) == 0 ? 3 :  -1)
#define AF_EBI_CS1_PORT(f)          ((f) == 0 ? 3 :  -1)
#define AF_EBI_CS2_PORT(f)          ((f) == 0 ? 3 :  -1)
#define AF_EBI_CS3_PORT(f)          ((f) == 0 ? 3 :  -1)
#define AF_EBI_WEn_PORT(f)          ((f) == 0 ? 5 :  -1)
#define AF_EBI_REn_PORT(f)          ((f) == 0 ? 5 :  -1)
#define AF_EBI_ARDY_PORT(f)         ((f) == 0 ? 5 :  -1)
#define AF_EBI_ALE_PORT(f)          ((f) == 0 ? 5 :  -1)
#define AF_TIMER0_CC0_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 5 : (f) == 3 ? 3 :  -1)
#define AF_TIMER0_CC1_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 5 : (f) == 3 ? 3 :  -1)
#define AF_TIMER0_CC2_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 5 : (f) == 3 ? 3 :  -1)
#define AF_TIMER0_CDTI0_PORT(f)     ((f) == 0 ? 0 : (f) == 1 ? 2 : (f) == 2 ? 5 : (f) == 3 ? 2 :  -1)
#define AF_TIMER0_CDTI1_PORT(f)     ((f) == 0 ? 0 : (f) == 1 ? 2 : (f) == 2 ? 5 : (f) == 3 ? 2 :  -1)
#define AF_TIMER0_CDTI2_PORT(f)     ((f) == 0 ? 0 : (f) == 1 ? 2 : (f) == 2 ? 5 : (f) == 3 ? 2 :  -1)
#define AF_TIMER1_CC0_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 4 : (f) == 2 ? 1 :  -1)
#define AF_TIMER1_CC1_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 4 : (f) == 2 ? 1 :  -1)
#define AF_TIMER1_CC2_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 4 : (f) == 2 ? 1 :  -1)
#define AF_TIMER1_CDTI0_PORT(f)     (-1)
#define AF_TIMER1_CDTI1_PORT(f)     (-1)
#define AF_TIMER1_CDTI2_PORT(f)     (-1)
#define AF_TIMER2_CC0_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 2 :  -1)
#define AF_TIMER2_CC1_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 2 :  -1)
#define AF_TIMER2_CC2_PORT(f)       ((f) == 0 ? 0 : (f) == 1 ? 0 : (f) == 2 ? 2 :  -1)
#define AF_TIMER2_CDTI0_PORT(f)     (-1)
#define AF_TIMER2_CDTI1_PORT(f)     (-1)
#define AF_TIMER2_CDTI2_PORT(f)     (-1)
#define AF_USART0_TX_PORT(f)        ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_USART0_RX_PORT(f)        ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_USART0_CLK_PORT(f)       ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_USART0_CS_PORT(f)        ((f) == 0 ? 4 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_USART1_TX_PORT(f)        ((f) == 0 ? 2 : (f) == 1 ? 3 :  -1)
#define AF_USART1_RX_PORT(f)        ((f) == 0 ? 2 : (f) == 1 ? 3 :  -1)
#define AF_USART1_CLK_PORT(f)       ((f) == 0 ? 1 : (f) == 1 ? 3 :  -1)
#define AF_USART1_CS_PORT(f)        ((f) == 0 ? 1 : (f) == 1 ? 3 :  -1)
#define AF_USART2_TX_PORT(f)        ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_USART2_RX_PORT(f)        ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_USART2_CLK_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_USART2_CS_PORT(f)        ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_UART0_TX_PORT(f)         ((f) == 0 ? 5 : (f) == 1 ? 4 : (f) == 2 ? 0 : (f) == 3 ? 2 :  -1)
#define AF_UART0_RX_PORT(f)         ((f) == 0 ? 5 : (f) == 1 ? 4 : (f) == 2 ? 0 : (f) == 3 ? 2 :  -1)
#define AF_UART0_CLK_PORT(f)        (-1)
#define AF_UART0_CS_PORT(f)         (-1)
#define AF_LEUART0_TX_PORT(f)       ((f) == 0 ? 3 : (f) == 1 ? 1 : (f) == 2 ? 4 :  -1)
#define AF_LEUART0_RX_PORT(f)       ((f) == 0 ? 3 : (f) == 1 ? 1 : (f) == 2 ? 4 :  -1)
#define AF_LEUART1_TX_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 0 :  -1)
#define AF_LEUART1_RX_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 0 :  -1)
#define AF_LETIMER0_OUT0_PORT(f)    ((f) == 0 ? 3 : (f) == 1 ? 1 : (f) == 2 ? 5 : (f) == 3 ? 2 :  -1)
#define AF_LETIMER0_OUT1_PORT(f)    ((f) == 0 ? 3 : (f) == 1 ? 1 : (f) == 2 ? 5 : (f) == 3 ? 2 :  -1)
#define AF_PCNT0_S0IN_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_PCNT0_S1IN_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 4 : (f) == 2 ? 2 :  -1)
#define AF_PCNT1_S0IN_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_PCNT1_S1IN_PORT(f)       ((f) == 0 ? 2 : (f) == 1 ? 1 :  -1)
#define AF_PCNT2_S0IN_PORT(f)       ((f) == 0 ? 3 : (f) == 1 ? 4 :  -1)
#define AF_PCNT2_S1IN_PORT(f)       ((f) == 0 ? 3 : (f) == 1 ? 4 :  -1)
#define AF_I2C0_SDA_PORT(f)         ((f) == 0 ? 0 : (f) == 1 ? 3 : (f) == 2 ? 2 : (f) == 3 ? 3 :  -1)
#define AF_I2C0_SCL_PORT(f)         ((f) == 0 ? 0 : (f) == 1 ? 3 : (f) == 2 ? 2 : (f) == 3 ? 3 :  -1)
#define AF_ACMP0_OUT_PORT(f)        ((f) == 0 ? 4 : (f) == 1 ? 4 :  -1)
#define AF_ACMP1_OUT_PORT(f)        ((f) == 0 ? 5 : (f) == 1 ? 4 :  -1)
#define AF_DBG_SWO_PORT(f)          ((f) == 0 ? 5 : (f) == 1 ? 2 :  -1)
#define AF_DBG_SWDIO_PORT(f)        ((f) == 0 ? 5 : (f) == 1 ? 5 :  -1)
#define AF_DBG_SWCLK_PORT(f)        ((f) == 0 ? 5 : (f) == 1 ? 5 :  -1)

/** @} End of group EFM32G_AF_Ports */


