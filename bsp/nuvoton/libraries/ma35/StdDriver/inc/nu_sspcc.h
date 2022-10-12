/****************************************************************************//**
 * @file     nu_sspcc.h
 * @brief    SSPCC driver header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SSPCC_H__
#define __NU_SSPCC_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SSPCC_Driver SSMCC Driver
  @{
*/

/** @addtogroup SSPCC_EXPORTED_CONSTANTS SSMCC Exported Constants
  @{
*/
#define SSPCC_SSET_TZS      0U     /*!< Security set TNS              \hideinitializer */
#define SSPCC_SSET_TZNS     1U     /*!< Security set TZNS             \hideinitializer */
#define SSPCC_SSET_SUBM     3U     /*!< Security set SUBM             \hideinitializer */
#define SSPCC_SSET_Msk      3U     /*!< Security set Mask             \hideinitializer */

#define SSPCC_REG_Pos       8U
#define SSPCC_REG_Msk       (0xFFFF<<SSPCC_REG_Pos)
#define SSPCC_PS_Pos        0U
#define SSPCC_PS_Msk        (0xFFU<<SSPCC_PS_Pos)

#define SSPCC_PDMA0         ((0x0000U<<SSPCC_REG_Pos) | SSPCC_PSSET0_PDMA0_Pos)
#define SSPCC_PDMA1         ((0x0000U<<SSPCC_REG_Pos) | SSPCC_PSSET0_PDMA1_Pos)
#define SSPCC_PDMA2         ((0x0000U<<SSPCC_REG_Pos) | SSPCC_PSSET0_PDMA2_Pos)
#define SSPCC_PDMA3         ((0x0000U<<SSPCC_REG_Pos) | SSPCC_PSSET0_PDMA3_Pos)

#define SSPCC_EBI           ((0x0004U<<SSPCC_REG_Pos) | SSPCC_PSSET1_EBI_Pos)
#define SSPCC_SDH0          ((0x0004U<<SSPCC_REG_Pos) | SSPCC_PSSET1_SDH0_Pos)
#define SSPCC_SDH1          ((0x0004U<<SSPCC_REG_Pos) | SSPCC_PSSET1_SDH1_Pos)
#define SSPCC_NANDC         ((0x0004U<<SSPCC_REG_Pos) | SSPCC_PSSET1_NANDC_Pos)

#define SSPCC_HSUSBD        ((0x0008U<<SSPCC_REG_Pos) | SSPCC_PSSET2_HSUSBD_Pos)

#define SSPCC_CRYPTO        ((0x000CU<<SSPCC_REG_Pos) | SSPCC_PSSET3_CRYPTO_Pos)
#define SSPCC_CANFD0        ((0x000CU<<SSPCC_REG_Pos) | SSPCC_PSSET3_CANFD0_Pos)
#define SSPCC_CANFD1        ((0x000CU<<SSPCC_REG_Pos) | SSPCC_PSSET3_CANFD1_Pos)
#define SSPCC_CANFD2        ((0x000CU<<SSPCC_REG_Pos) | SSPCC_PSSET3_CANFD2_Pos)
#define SSPCC_CANFD3        ((0x000CU<<SSPCC_REG_Pos) | SSPCC_PSSET3_CANFD3_Pos)

#define SSPCC_ADC0          ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_ADC0_Pos)
#define SSPCC_EADC0         ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_EADC0_Pos)
#define SSPCC_WDTWWDT1      ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_WDTWWDT1_Pos)
#define SSPCC_I2S0          ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_I2S0_Pos)
#define SSPCC_I2S1          ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_I2S1_Pos)
#define SSPCC_KPI           ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_KPI_Pos)
#define SSPCC_DDRPHYPUB     ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_DDRPHYPUB_Pos)
#define SSPCC_MCTL          ((0x0010U<<SSPCC_REG_Pos) | SSPCC_PSSET4_MCTL_Pos)

#define SSPCC_TMR01         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR01_Pos)
#define SSPCC_TMR23         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR23_Pos)
#define SSPCC_TMR45         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR45_Pos)
#define SSPCC_TMR67         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR67_Pos)
#define SSPCC_TMR89         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR89_Pos)
#define SSPCC_TMR1011       ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_TMR1011_Pos)
#define SSPCC_EPWM0         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_EPWM0_Pos)
#define SSPCC_EPWM1         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_EPWM1_Pos)
#define SSPCC_EPWM2         ((0x0014U<<SSPCC_REG_Pos) | SSPCC_PSSET5_EPWM2_Pos)

#define SSPCC_SPI0          ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_SPI0_Pos)
#define SSPCC_SPI1          ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_SPI1_Pos)
#define SSPCC_SPI2          ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_SPI2_Pos)
#define SSPCC_SPI3          ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_SPI3_Pos)
#define SSPCC_QSPI0         ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_QSPI0_Pos)
#define SSPCC_QSPI1         ((0x0018U<<SSPCC_REG_Pos) | SSPCC_PSSET6_QSPI1_Pos)

#define SSPCC_UART0         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART0_Pos)
#define SSPCC_UART1         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART1_Pos)
#define SSPCC_UART2         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART2_Pos)
#define SSPCC_UART3         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART3_Pos)
#define SSPCC_UART4         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART4_Pos)
#define SSPCC_UART5         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART5_Pos)
#define SSPCC_UART6         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART6_Pos)
#define SSPCC_UART7         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART7_Pos)
#define SSPCC_UART8         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART8_Pos)
#define SSPCC_UART9         ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART9_Pos)
#define SSPCC_UART10        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART10_Pos)
#define SSPCC_UART11        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART11_Pos)
#define SSPCC_UART12        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART12_Pos)
#define SSPCC_UART13        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART13_Pos)
#define SSPCC_UART14        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART14_Pos)
#define SSPCC_UART15        ((0x001CU<<SSPCC_REG_Pos) | SSPCC_PSSET7_UART15_Pos)

#define SSPCC_I2C0          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C0_Pos)
#define SSPCC_I2C1          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C1_Pos)
#define SSPCC_I2C2          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C2_Pos)
#define SSPCC_I2C3          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C3_Pos)
#define SSPCC_I2C4          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C4_Pos)
#define SSPCC_I2C5          ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_I2C5_Pos)
#define SSPCC_UART16        ((0x0020U<<SSPCC_REG_Pos) | SSPCC_PSSET8_UART16_Pos)

#define SSPCC_SC0           ((0x0024U<<SSPCC_REG_Pos) | SSPCC_PSSET9_SC0_Pos)
#define SSPCC_SC1           ((0x0024U<<SSPCC_REG_Pos) | SSPCC_PSSET9_SC1_Pos)

#define SSPCC_QEI0          ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_QEI0_Pos)
#define SSPCC_QEI1          ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_QEI1_Pos)
#define SSPCC_QEI2          ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_QEI2_Pos)
#define SSPCC_ECAP0         ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_ECAP0_Pos)
#define SSPCC_ECAP1         ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_ECAP1_Pos)
#define SSPCC_ECAP2         ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_ECAP2_Pos)
#define SSPCC_TRNG          ((0x002CU<<SSPCC_REG_Pos) | SSPCC_PSSET11_TRNG_Pos)

#define SSPCC_SR0BOUND      ((0x0040U<<SSPCC_REG_Pos) | SSPCC_SRAMSB_SR0BOUND_Pos)
#define SSPCC_SR1BOUND      ((0x0040U<<SSPCC_REG_Pos) | SSPCC_SRAMSB_SR1BOUND_Pos)

#define SSPCC_EBI_BANK0     ((0x0050U<<SSPCC_REG_Pos) | SSPCC_EBISSET_BANK0_Pos)
#define SSPCC_EBI_BANK1     ((0x0050U<<SSPCC_REG_Pos) | SSPCC_EBISSET_BANK1_Pos)
#define SSPCC_EBI_BANK2     ((0x0050U<<SSPCC_REG_Pos) | SSPCC_EBISSET_BANK2_Pos)

#define SSPCC_PA0           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PA1           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PA2           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PA3           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PA4           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PA5           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PA6           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PA7           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PA8           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PA9           ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PA10          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PA11          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PA12          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PA13          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PA14          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PA15          ((0x0060U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PB0           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PB1           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PB2           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PB3           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PB4           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PB5           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PB6           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PB7           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PB8           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PB9           ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PB10          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PB11          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PB12          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PB13          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PB14          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PB15          ((0x0064U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PC0           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PC1           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PC2           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PC3           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PC4           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PC5           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PC6           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PC7           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PC8           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PC9           ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PC10          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PC11          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PC12          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PC13          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PC14          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PC15          ((0x0068U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PD0           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PD1           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PD2           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PD3           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PD4           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PD5           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PD6           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PD7           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PD8           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PD9           ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PD10          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PD11          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PD12          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PD13          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PD14          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PD15          ((0x006CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PE0           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PE1           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PE2           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PE3           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PE4           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PE5           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PE6           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PE7           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PE8           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PE9           ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PE10          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PE11          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PE12          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PE13          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PE14          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PE15          ((0x0070U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PF0           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PF1           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PF2           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PF3           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PF4           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PF5           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PF6           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PF7           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PF8           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PF9           ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PF10          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PF11          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PF12          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PF13          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PF14          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PF15          ((0x0074U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PG0           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PG1           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PG2           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PG3           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PG4           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PG5           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PG6           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PG7           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PG8           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PG9           ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PG10          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PG11          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PG12          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PG13          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PG14          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PG15          ((0x0078U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PH0           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PH1           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PH2           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PH3           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PH4           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PH5           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PH6           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PH7           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PH8           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PH9           ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PH10          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PH11          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PH12          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PH13          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PH14          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PH15          ((0x007CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PI0           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PI1           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PI2           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PI3           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PI4           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PI5           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PI6           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PI7           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PI8           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PI9           ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PI10          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PI11          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PI12          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PI13          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PI14          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PI15          ((0x0080U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PJ0           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PJ1           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PJ2           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PJ3           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PJ4           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PJ5           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PJ6           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PJ7           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PJ8           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PJ9           ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PJ10          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PJ11          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PJ12          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PJ13          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PJ14          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PJ15          ((0x0084U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PK0           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PK1           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PK2           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PK3           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PK4           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PK5           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PK6           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PK7           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PK8           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PK9           ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PK10          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PK11          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PK12          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PK13          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PK14          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PK15          ((0x0088U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PL0           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PL1           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PL2           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PL3           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PL4           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PL5           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PL6           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PL7           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PL8           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PL9           ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PL10          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PL11          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PL12          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PL13          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PL14          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PL15          ((0x008CU<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PM0           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PM1           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PM2           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PM3           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PM4           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PM5           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PM6           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PM7           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PM8           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PM9           ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PM10          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PM11          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PM12          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PM13          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PM14          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PM15          ((0x0090U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

#define SSPCC_PN0           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN0_Pos)
#define SSPCC_PN1           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN1_Pos)
#define SSPCC_PN2           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN2_Pos)
#define SSPCC_PN3           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN3_Pos)
#define SSPCC_PN4           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN4_Pos)
#define SSPCC_PN5           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN5_Pos)
#define SSPCC_PN6           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN6_Pos)
#define SSPCC_PN7           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN7_Pos)
#define SSPCC_PN8           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN8_Pos)
#define SSPCC_PN9           ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN9_Pos)
#define SSPCC_PN10          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN10_Pos)
#define SSPCC_PN11          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN11_Pos)
#define SSPCC_PN12          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN12_Pos)
#define SSPCC_PN13          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN13_Pos)
#define SSPCC_PN14          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN14_Pos)
#define SSPCC_PN15          ((0x0094U<<SSPCC_REG_Pos) | SSPCC_IOxSSET_PIN15_Pos)

/*@}*/ /* end of group SSPCC_EXPORTED_CONSTANTS */

/** @addtogroup SSPCC_EXPORTED_FUNCTIONS SSMCC Exported Functions
  @{
*/
void SSPCC_SetRealm(uint32_t u32Perip, uint32_t u32Realm);
uint32_t SSPCC_GetRealm(uint32_t u32Perip);

void SSPCC_SetRealm_GPIO(uint32_t u32PortBA, uint32_t u32Pin, uint32_t u32Realm);
uint32_t SSPCC_GetRealm_GPIO(uint32_t u32PortBA, uint32_t u32Pin);

/*@}*/ /* end of group SSPCC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SSPCC_Driver */

/*@}*/ /* end of group Standard_Driver */
#ifdef __cplusplus
}
#endif

#endif


