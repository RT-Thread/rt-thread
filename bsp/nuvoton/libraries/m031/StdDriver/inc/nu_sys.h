/**************************************************************************//**
 * @file     nu_sys.h
 * @version  V0.10
 * $Revision: 7 $
 * $Date: 19/06/10 2:48p $
 * @brief    M031 Series SYS Driver Header File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __NU_SYS_H__
#define __NU_SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SYS_Driver SYS Driver
  @{
*/

/** @addtogroup SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_RST    ((0x0<<24)|SYS_IPRST0_PDMARST_Pos)      /*!< PDMA  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define EBI_RST     ((0x0<<24)|SYS_IPRST0_EBIRST_Pos)       /*!< EBI   reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define HDIV_RST    ((0x0<<24)|SYS_IPRST0_HDIVRST_Pos)      /*!< HDIV  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define CRC_RST     ((0x0<<24)|SYS_IPRST0_CRCRST_Pos)       /*!< CRC   reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */

#define GPIO_RST    ((0x4<<24)|SYS_IPRST1_GPIORST_Pos)      /*!< GPIO  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define TMR0_RST    ((0x4<<24)|SYS_IPRST1_TMR0RST_Pos)      /*!< TMR0  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define TMR1_RST    ((0x4<<24)|SYS_IPRST1_TMR1RST_Pos)      /*!< TMR1  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define TMR2_RST    ((0x4<<24)|SYS_IPRST1_TMR2RST_Pos)      /*!< TMR2  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define TMR3_RST    ((0x4<<24)|SYS_IPRST1_TMR3RST_Pos)      /*!< TMR3  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define ACMP01_RST  ((0x4<<24)|SYS_IPRST1_ACMP01RST_Pos)    /*!< ACMP  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define I2C0_RST    ((0x4<<24)|SYS_IPRST1_I2C0RST_Pos)      /*!< I2C0  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define I2C1_RST    ((0x4<<24)|SYS_IPRST1_I2C1RST_Pos)      /*!< I2C1  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define QSPI0_RST   ((0x4<<24)|SYS_IPRST1_QSPI0RST_Pos)     /*!< QSPI0 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define SPI0_RST    ((0x4<<24)|SYS_IPRST1_SPI0RST_Pos)      /*!< SPI0  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART0_RST   ((0x4<<24)|SYS_IPRST1_UART0RST_Pos)     /*!< UART0 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART1_RST   ((0x4<<24)|SYS_IPRST1_UART1RST_Pos)     /*!< UART1 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART2_RST   ((0x4<<24)|SYS_IPRST1_UART2RST_Pos)     /*!< UART2 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART3_RST   ((0x4<<24)|SYS_IPRST1_UART3RST_Pos)     /*!< UART3 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART4_RST   ((0x4<<24)|SYS_IPRST1_UART4RST_Pos)     /*!< UART4 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART5_RST   ((0x4<<24)|SYS_IPRST1_UART5RST_Pos)     /*!< UART5 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART6_RST   ((0x4<<24)|SYS_IPRST1_UART6RST_Pos)     /*!< UART6 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define UART7_RST   ((0x4<<24)|SYS_IPRST1_UART7RST_Pos)     /*!< UART7 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define USBD_RST    ((0x4<<24)|SYS_IPRST1_USBDRST_Pos)      /*!< USBD  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define ADC_RST     ((0x4<<24)|SYS_IPRST1_ADCRST_Pos)       /*!< ADC   reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */

#define USCI0_RST   ((0x8<<24)|SYS_IPRST2_USCI0RST_Pos)     /*!< USCI0 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define USCI1_RST   ((0x8<<24)|SYS_IPRST2_USCI1RST_Pos)     /*!< USCI1 reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define PWM0_RST    ((0x8<<24)|SYS_IPRST2_PWM0RST_Pos)      /*!< PWM0  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define PWM1_RST    ((0x8<<24)|SYS_IPRST2_PWM1RST_Pos)      /*!< PWM1  reset is one of the \ref SYS_ResetModule parameter   \hideinitializer */
#define BPWM0_RST   ((0x8<<24)|SYS_IPRST2_BPWM0RST_Pos)     /*!< BPWM0  reset is one of the \ref SYS_ResetModule parameter  \hideinitializer */
#define BPWM1_RST   ((0x8<<24)|SYS_IPRST2_BPWM1RST_Pos)     /*!< BPWM1  reset is one of the \ref SYS_ResetModule parameter  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCTL_BOD_RST_EN           (1UL<<SYS_BODCTL_BODRSTEN_Pos)          /*!< Brown-out Reset Enable     \hideinitializer */
#define SYS_BODCTL_BOD_INTERRUPT_EN     (0UL<<SYS_BODCTL_BODRSTEN_Pos)          /*!< Brown-out Interrupt Enable \hideinitializer */

#define SYS_BODCTL_BODVL_2_5V           (0x1UL<<SYS_BODCTL_BODVL_Pos)           /*!< Setting Brown Out Detector Threshold Voltage as 2.5V   \hideinitializer */
#define SYS_BODCTL_BODVL_2_0V           (0x0UL<<SYS_BODCTL_BODVL_Pos)           /*!< Setting Brown Out Detector Threshold Voltage as 2.0V   \hideinitializer */

#define SYS_BODCTL_LVRDGSEL_0HCLK       (0x0UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time Without de-glitch function.  \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_64HCLK      (0x1UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 64HCLK           \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_128HCLK     (0x2UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 128HCLK          \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_256HCLK     (0x3UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 256HCLK          \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_512HCLK     (0x4UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 512HCLK          \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_1024HCLK    (0x5UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 1024HCLK         \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_2048HCLK    (0x6UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 2048HCLK         \hideinitializer */
#define SYS_BODCTL_LVRDGSEL_4096HCLK    (0x7UL<<SYS_BODCTL_LVRDGSEL_Pos)        /*!< LVR Output De-glitch Time is selected 4096HCLK         \hideinitializer */

#define SYS_BODCTL_BODDGSEL_0HCLK       (0x0UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is sampled by RC10K clock.   \hideinitializer */
#define SYS_BODCTL_BODDGSEL_64HCLK      (0x1UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 64HCLK           \hideinitializer */
#define SYS_BODCTL_BODDGSEL_128HCLK     (0x2UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 128HCLK          \hideinitializer */
#define SYS_BODCTL_BODDGSEL_256HCLK     (0x3UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 256HCLK          \hideinitializer */
#define SYS_BODCTL_BODDGSEL_512HCLK     (0x4UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 512HCLK          \hideinitializer */
#define SYS_BODCTL_BODDGSEL_1024HCLK    (0x5UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 1024HCLK         \hideinitializer */
#define SYS_BODCTL_BODDGSEL_2048HCLK    (0x6UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 2048HCLK         \hideinitializer */
#define SYS_BODCTL_BODDGSEL_4096HCLK    (0x7UL<<SYS_BODCTL_BODDGSEL_Pos)        /*!< BOD Output De-glitch Time is selected 4096HCLK         \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/

/* How to use below #define?

Example: If user want to set PD.3 as UART0_TXD and PD.2 as UART0_RXD in initial function,
         user can issue following command to achieve it.

         SYS->GPD_MFPL = (SYS->GPD_MFPL & ~SYS_GPD_MFPL_PD2MFP_Msk) | SYS_GPD_MFPL_PD2MFP_UART0_RXD;
         SYS->GPD_MFPL = (SYS->GPD_MFPL & ~SYS_GPD_MFPL_PD3MFP_Msk) | SYS_GPD_MFPL_PD3MFP_UART0_TXD;
*/
/* PA.0 MFP */
#define SYS_GPA_MFPL_PA0MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0  (0x03UL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for QSPI0_MOSI0 \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_SPI0_MOSI    (0x04UL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for SPI0_MOSI   \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_UART0_RXD    (0x07UL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for UART0_RXD   \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_UART1_nRTS   (0x08UL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for UART1_nRTS  \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_BPWM0_CH0    (0x0CUL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for BPWM0_CH0   \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_PWM0_CH5     (0x0DUL<<SYS_GPA_MFPL_PA0MFP_Pos) /*!< GPA_MFPL PA0 setting for PWM0_CH5    \hideinitializer */

/* PA.1 MFP */
#define SYS_GPA_MFPL_PA1MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0  (0x03UL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for QSPI0_MISO0 \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_SPI0_MISO    (0x04UL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for SPI0_MISO   \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_UART0_TXD    (0x07UL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for UART0_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_UART1_nCTS   (0x08UL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for UART1_nCTS  \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_USCI1_CLK    (0x0BUL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for USCI1_CLK   \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_BPWM0_CH1    (0x0CUL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for BPWM0_CH1   \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_PWM0_CH4     (0x0DUL<<SYS_GPA_MFPL_PA1MFP_Pos) /*!< GPA_MFPL PA1 setting for PWM0_CH4    \hideinitializer */

/* PA.2 MFP */
#define SYS_GPA_MFPL_PA2MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_QSPI0_CLK    (0x03UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for QSPI0_CLK   \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_SPI0_CLK     (0x04UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for SPI0_CLK    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_UART4_RXD    (0x05UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for UART4_RXD   \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_I2C0_SMBSUS  (0x07UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for I2C0_SMBSUS \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_UART1_RXD    (0x08UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for UART1_RXD   \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_I2C1_SDA     (0x09UL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_USCI1_DAT0   (0x0BUL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for USCI1_DAT0  \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_BPWM0_CH2    (0x0CUL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for BPWM0_CH2   \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_PWM0_CH3     (0x0DUL<<SYS_GPA_MFPL_PA2MFP_Pos) /*!< GPA_MFPL PA2 setting for PWM0_CH3    \hideinitializer */

/* PA.3 MFP */
#define SYS_GPA_MFPL_PA3MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_QSPI0_SS     (0x03UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for QSPI0_SS    \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_SPI0_SS      (0x04UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for SPI0_SS     \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_UART4_TXD    (0x05UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for UART4_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_I2C0_SMBAL   (0x07UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for I2C0_SMBAL  \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_UART1_TXD    (0x08UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for UART1_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_I2C1_SCL     (0x09UL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_USCI1_DAT1   (0x0BUL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for USCI1_DAT1  \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_BPWM0_CH3    (0x0CUL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for BPWM0_CH3   \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_PWM0_CH2     (0x0DUL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for PWM0_CH2    \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_CLKO         (0x0EUL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPB_MFPL PA3 setting for CLKO        \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_PWM1_BRAKE1  (0x0FUL<<SYS_GPA_MFPL_PA3MFP_Pos) /*!< GPA_MFPL PA3 setting for PWM1_BRAKE1 \hideinitializer */

/* PA.4 MFP */
#define SYS_GPA_MFPL_PA4MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for GPIO           \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_QSPI0_MOSI1  (0x03UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for QSPI0_MOSI1    \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for SPI0_I2SMCLK   \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_UART0_nRTS   (0x07UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for UART0_nRTS     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_UART0_RXD    (0x08UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for UART0_RXD      \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_I2C0_SDA     (0x09UL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for I2C0_SDA       \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_UART5_RXD    (0x0BUL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for UART5_RXD      \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_BPWM0_CH4    (0x0CUL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for BPWM0_CH4      \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_PWM0_CH1     (0x0DUL<<SYS_GPA_MFPL_PA4MFP_Pos) /*!< GPA_MFPL PA4 setting for PWM0_CH1       \hideinitializer */

/* PA.5 MFP */
#define SYS_GPA_MFPL_PA5MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_QSPI0_MISO1  (0x03UL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for QSPI0_MISO1 \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_UART0_nCTS   (0x07UL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for UART0_nCTS  \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_UART0_TXD    (0x08UL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for UART0_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_I2C0_SCL     (0x09UL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for I2C0_SCL    \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_UART5_TXD    (0x0BUL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for UART5_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_BPWM0_CH5    (0x0CUL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for BPWM0_CH5   \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_PWM0_CH0     (0x0DUL<<SYS_GPA_MFPL_PA5MFP_Pos) /*!< GPA_MFPL PA5 setting for PWM0_CH0    \hideinitializer */

/* PA.6 MFP */
#define SYS_GPA_MFPL_PA6MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_EBI_AD6      (0x02UL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for EBI_AD6     \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_UART0_RXD    (0x07UL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for UART0_RXD   \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_I2C1_SDA     (0x08UL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_PWM1_CH5     (0x0BUL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for PWM1_CH5    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_BPWM1_CH3    (0x0CUL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for BPWM1_CH3   \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_ACMP1_WLAT   (0x0DUL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for ACMP1_WLAT  \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_TM3          (0x0EUL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for TM3         \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_INT0         (0x0FUL<<SYS_GPA_MFPL_PA6MFP_Pos) /*!< GPA_MFPL PA6 setting for INT0        \hideinitializer */

/* PA.7 MFP */
#define SYS_GPA_MFPL_PA7MFP_GPIO         (0x00UL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_EBI_AD7      (0x02UL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for EBI_AD7     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_UART0_TXD    (0x07UL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for UART0_TXD   \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_I2C1_SCL     (0x08UL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_PWM1_CH4     (0x0BUL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for PWM1_CH4    \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_BPWM1_CH2    (0x0CUL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for BPWM1_CH2   \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_ACMP0_WLAT   (0x0DUL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for ACMP0_WLAT  \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_TM2          (0x0EUL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for TM2         \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_INT1         (0x0FUL<<SYS_GPA_MFPL_PA7MFP_Pos) /*!< GPA_MFPL PA7 setting for INT1        \hideinitializer */

/* PA.8 MFP */
#define SYS_GPA_MFPH_PA8MFP_GPIO         (0x00UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_EBI_ALE      (0x02UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for EBI_ALE     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_USCI0_CTL1   (0x06UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for USCI0_CTL1  \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_UART1_RXD    (0x07UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for UART1_RXD   \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_UART7_RXD    (0x08UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for UART7_RXD   \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_BPWM0_CH3    (0x09UL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for BPWM0_CH3   \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_TM3_EXT      (0x0DUL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for TM3_EXT     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_INT4         (0x0FUL<<SYS_GPA_MFPH_PA8MFP_Pos) /*!< GPA_MFPH PA8 setting for INT4        \hideinitializer */

/* PA.9 MFP */
#define SYS_GPA_MFPH_PA9MFP_GPIO         (0x00UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for GPIO        \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_EBI_MCLK     (0x02UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for EBI_MCLK    \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_USCI0_DAT1   (0x06UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for USCI0_DAT1  \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_UART1_TXD    (0x07UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for UART1_TXD   \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_UART7_TXD    (0x08UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for UART7_TXD   \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_BPWM0_CH2    (0x09UL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for BPWM0_CH2   \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_TM2_EXT      (0x0DUL<<SYS_GPA_MFPH_PA9MFP_Pos) /*!< GPA_MFPH PA9 setting for TM2_EXT     \hideinitializer */

/* PA.10 MFP */
#define SYS_GPA_MFPH_PA10MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_ACMP1_P0    (0x01UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for ACMP1_P0   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_EBI_nWR     (0x02UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for EBI_nWR    \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_USCI0_DAT0  (0x06UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for USCI0_DAT0 \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_UART6_RXD   (0x08UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for UART6_RXD  \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_BPWM0_CH1   (0x09UL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for BPWM0_CH1  \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_TM1_EXT     (0x0DUL<<SYS_GPA_MFPH_PA10MFP_Pos)/*!< GPA_MFPH PA10 setting for TM1_EXT    \hideinitializer */

/* PA.11 MFP */
#define SYS_GPA_MFPH_PA11MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_ACMP0_P0    (0x01UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for ACMP0_P0   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_EBI_nRD     (0x02UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for EBI_nRD    \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_USCI0_CLK   (0x06UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for USCI0_CLK  \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_UART6_TXD   (0x08UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for UART6_TXD  \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_BPWM0_CH0   (0x09UL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for BPWM0_CH0  \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_TM0_EXT     (0x0DUL<<SYS_GPA_MFPH_PA11MFP_Pos)/*!< GPA_MFPH PA11 setting for TM0_EXT    \hideinitializer */

/* PA.12 MFP */
#define SYS_GPA_MFPH_PA12MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA12MFP_Pos)/*!< GPA_MFPH PA12 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_UART4_TXD   (0x03UL<<SYS_GPA_MFPH_PA12MFP_Pos)/*!< GPA_MFPH PA12 setting for UART4_TXD  \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_I2C1_SCL    (0x04UL<<SYS_GPA_MFPH_PA12MFP_Pos)/*!< GPA_MFPH PA12 setting for I2C1_SCL   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_BPWM1_CH2   (0x0BUL<<SYS_GPA_MFPH_PA12MFP_Pos)/*!< GPA_MFPH PA12 setting for BPWM1_CH2  \hideinitializer */

/* PA.13 MFP */
#define SYS_GPA_MFPH_PA13MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA13MFP_Pos)/*!< GPA_MFPH PA13 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_UART4_RXD   (0x03UL<<SYS_GPA_MFPH_PA13MFP_Pos)/*!< GPA_MFPH PA13 setting for UART4_RXD  \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_I2C1_SDA    (0x04UL<<SYS_GPA_MFPH_PA13MFP_Pos)/*!< GPA_MFPH PA13 setting for I2C1_SDA   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_BPWM1_CH3   (0x0BUL<<SYS_GPA_MFPH_PA13MFP_Pos)/*!< GPA_MFPH PA13 setting for BPWM1_CH3  \hideinitializer */

/* PA.14 MFP */
#define SYS_GPA_MFPH_PA14MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA14MFP_Pos)/*!< GPA_MFPH PA14 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_UART0_TXD   (0x03UL<<SYS_GPA_MFPH_PA14MFP_Pos)/*!< GPA_MFPH PA14 setting for UART0_TXD  \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_BPWM1_CH4   (0x0BUL<<SYS_GPA_MFPH_PA14MFP_Pos)/*!< GPA_MFPH PA14 setting for BPWM1_CH4  \hideinitializer */

/* PA.15 MFP */
#define SYS_GPA_MFPH_PA15MFP_GPIO        (0x00UL<<SYS_GPA_MFPH_PA15MFP_Pos)/*!< GPA_MFPH PA15 setting for GPIO       \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_UART0_RXD   (0x03UL<<SYS_GPA_MFPH_PA15MFP_Pos)/*!< GPA_MFPH PA15 setting for UART0_RXD  \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_BPWM1_CH5   (0x0BUL<<SYS_GPA_MFPH_PA15MFP_Pos)/*!< GPA_MFPH PA15 setting for BPWM1_CH5  \hideinitializer */

/* PB.0 MFP */
#define SYS_GPB_MFPL_PB0MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for GPIO           \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_ADC_CH0      (0x01UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for ADC_CH0        \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_ADC0_CH0     (0x01UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for ADC0_CH0       \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_EBI_ADR9     (0x02UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for EBI_ADR9       \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_UART2_RXD    (0x07UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for UART2_RXD      \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_SPI0_I2SMCLK (0x08UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for SPI0_I2SMCLK   \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_I2C1_SDA     (0x09UL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for I2C1_SDA       \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_QSPI0_MOSI1  (0x0AUL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for QSPI0_MOSI1    \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_PWM0_CH5     (0x0BUL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for PWM0_CH5       \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_PWM1_CH5     (0x0CUL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for PWM1_CH5       \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_PWM0_BRAKE1  (0x0DUL<<SYS_GPB_MFPL_PB0MFP_Pos) /*!< GPB_MFPL PB0 setting for PWM0_BRAKE1    \hideinitializer */

/* PB.1 MFP */
#define SYS_GPB_MFPL_PB1MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_ADC_CH1      (0x01UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for ADC_CH1     \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_ADC0_CH1     (0x01UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for ADC0_CH1    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_EBI_ADR8     (0x02UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for EBI_ADR8    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_UART2_TXD    (0x07UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for UART2_TXD   \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_USCI1_CLK    (0x08UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for USCI1_CLK   \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_I2C1_SCL     (0x09UL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_QSPI0_MISO1  (0x0AUL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for QSPI0_MISO1 \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_PWM0_CH4     (0x0BUL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for PWM0_CH4    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_PWM1_CH4     (0x0CUL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for PWM1_CH4    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_PWM0_BRAKE0  (0x0DUL<<SYS_GPB_MFPL_PB1MFP_Pos) /*!< GPB_MFPL PB1 setting for PWM0_BRAKE0 \hideinitializer */

/* PB.2 MFP */
#define SYS_GPB_MFPL_PB2MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_ADC_CH2      (0x01UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for ADC_CH2     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_ADC0_CH2     (0x01UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for ADC0_CH2    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_ACMP0_P1     (0x01UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for ACMP0_P1    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_EBI_ADR3     (0x02UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for EBI_ADR3    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_I2C1_SDA     (0x04UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_UART1_RXD    (0x06UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for UART1_RXD   \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_UART5_nCTS   (0x07UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for UART5_nCTS  \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_USCI1_DAT0   (0x08UL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for USCI1_DAT0  \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_PWM0_CH3     (0x0BUL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for PWM0_CH3    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_TM3          (0x0EUL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for TM3         \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_INT3         (0x0FUL<<SYS_GPB_MFPL_PB2MFP_Pos) /*!< GPB_MFPL PB2 setting for INT3        \hideinitializer */

/* PB.3 MFP */
#define SYS_GPB_MFPL_PB3MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_ADC_CH3      (0x01UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for ADC_CH3     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_ADC0_CH3     (0x01UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for ADC0_CH3    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_ACMP0_N      (0x01UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for ACMP0_N     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_EBI_ADR2     (0x02UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for EBI_ADR2    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_I2C1_SCL     (0x04UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_UART1_TXD    (0x06UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for UART1_TXD   \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_UART5_nRTS   (0x07UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for UART5_nRTS  \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_USCI1_DAT1   (0x08UL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for USCI1_DAT1  \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_PWM0_CH2     (0x0BUL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for PWM0_CH2    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_PWM0_BRAKE0  (0x0DUL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for PWM0_BRAKE0 \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_TM2          (0x0EUL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for TM2         \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_INT2         (0x0FUL<<SYS_GPB_MFPL_PB3MFP_Pos) /*!< GPB_MFPL PB3 setting for INT2        \hideinitializer */

/* PB.4 MFP */
#define SYS_GPB_MFPL_PB4MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_ADC_CH4      (0x01UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for ADC_CH4     \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_ADC0_CH4     (0x01UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for ADC0_CH4    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_ACMP1_P1     (0x01UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for ACMP1_P1    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_EBI_ADR1     (0x02UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for EBI_ADR1    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_I2C0_SDA     (0x06UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for I2C0_SDA    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_UART5_RXD    (0x07UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for UART5_RXD   \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_USCI1_CTL1   (0x08UL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for USCI1_CTL1  \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_PWM0_CH1     (0x0BUL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for PWM0_CH1    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_UART2_RXD    (0x0DUL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for UART2_RXD   \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_TM1          (0x0EUL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for TM1         \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_INT1         (0x0FUL<<SYS_GPB_MFPL_PB4MFP_Pos) /*!< GPB_MFPL PB4 setting for INT1        \hideinitializer */

/* PB.5 MFP */
#define SYS_GPB_MFPL_PB5MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_ADC_CH5      (0x01UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for ADC_CH5     \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_ADC0_CH5     (0x01UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for ADC0_CH5    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_ACMP1_N      (0x01UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for ACMP1_N     \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_EBI_ADR0     (0x02UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for EBI_ADR0    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_I2C0_SCL     (0x06UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for I2C0_SCL    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_UART5_TXD    (0x07UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for UART5_TXD   \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_USCI1_CTL0   (0x08UL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for USCI1_CTL0  \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_PWM0_CH0     (0x0BUL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for PWM0_CH0    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_UART2_TXD    (0x0DUL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for UART2_TXD   \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_TM0          (0x0EUL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for TM0         \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_INT0         (0x0FUL<<SYS_GPB_MFPL_PB5MFP_Pos) /*!< GPB_MFPL PB5 setting for INT0        \hideinitializer */

/* PB.6 MFP */
#define SYS_GPB_MFPL_PB6MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_ADC_CH6      (0x01UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for ADC_CH6     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_ADC0_CH6     (0x01UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for ADC0_CH6    \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_EBI_nWRH     (0x02UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for EBI_nWRH    \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_USCI1_DAT1   (0x04UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for USCI1_DAT1  \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_UART1_RXD    (0x06UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for UART1_RXD   \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_EBI_nCS1     (0x08UL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for EBI_nCS1    \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_BPWM1_CH5    (0x0AUL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for BPWM1_CH5   \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_PWM1_BRAKE1  (0x0BUL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for PWM1_BRAKE1 \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_PWM1_CH5     (0x0CUL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for PWM1_CH5    \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_INT4         (0x0DUL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for INT4        \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_ACMP1_O      (0x0FUL<<SYS_GPB_MFPL_PB6MFP_Pos) /*!< GPB_MFPL PB6 setting for ACMP1_O     \hideinitializer */

/* PB.7 MFP */
#define SYS_GPB_MFPL_PB7MFP_GPIO         (0x00UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_ADC_CH7      (0x01UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for ADC_CH7     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_ADC0_CH7     (0x01UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for ADC0_CH7    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_EBI_nWRL     (0x02UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for EBI_nWRL    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_USCI1_DAT0   (0x04UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for USCI1_DAT0  \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_UART1_TXD    (0x06UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for UART1_TXD   \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_EBI_nCS0     (0x08UL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for EBI_nCS0    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_BPWM1_CH4    (0x0AUL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for BPWM1_CH4   \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_PWM1_BRAKE0  (0x0BUL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for PWM1_BRAKE0 \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_PWM1_CH4     (0x0CUL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for PWM1_CH4    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_INT5         (0x0DUL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for INT5        \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_ACMP0_O      (0x0FUL<<SYS_GPB_MFPL_PB7MFP_Pos) /*!< GPB_MFPL PB7 setting for ACMP0_O     \hideinitializer */

/* PB.8 MFP */
#define SYS_GPB_MFPH_PB8MFP_GPIO         (0x00UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_ADC_CH8      (0x01UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for ADC_CH8     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_ADC0_CH8     (0x01UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for ADC0_CH8    \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_EBI_ADR19    (0x02UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for EBI_ADR19   \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_USCI1_CLK    (0x04UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for USCI1_CLK   \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_UART0_RXD    (0x05UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for UART0_RXD   \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_UART1_nRTS   (0x06UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for UART1_nRTS  \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_UART7_RXD    (0x08UL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for UART7_RXD   \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_BPWM1_CH3    (0x0AUL<<SYS_GPB_MFPH_PB8MFP_Pos) /*!< GPB_MFPH PB8 setting for BPWM1_CH3   \hideinitializer */

/* PB.9 MFP */
#define SYS_GPB_MFPH_PB9MFP_GPIO         (0x00UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for GPIO        \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_ADC_CH9      (0x01UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for ADC_CH9     \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_ADC0_CH9     (0x01UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for ADC0_CH9    \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_EBI_ADR18    (0x02UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for EBI_ADR18   \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_USCI1_CTL1   (0x04UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for USCI1_CTL1  \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_UART0_TXD    (0x05UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for UART0_TXD   \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_UART1_nCTS   (0x06UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for UART1_nCTS  \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_UART7_TXD    (0x08UL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for UART7_TXD   \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_BPWM1_CH2    (0x0AUL<<SYS_GPB_MFPH_PB9MFP_Pos) /*!< GPB_MFPH PB9 setting for BPWM1_CH2   \hideinitializer */

/* PB.10 MFP */
#define SYS_GPB_MFPH_PB10MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for GPIO       \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_ADC_CH10    (0x01UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for ADC_CH10   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_ADC0_CH10   (0x01UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for ADC0_CH10  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_EBI_ADR17   (0x02UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for EBI_ADR17  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_USCI1_CTL0  (0x04UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for USCI1_CTL0 \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_UART0_nRTS  (0x05UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for UART0_nRTS \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_UART4_RXD   (0x06UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for UART4_RXD  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_I2C1_SDA    (0x07UL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for I2C1_SDA   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_BPWM1_CH1   (0x0AUL<<SYS_GPB_MFPH_PB10MFP_Pos)/*!< GPB_MFPH PB10 setting for BPWM1_CH1  \hideinitializer */

/* PB.11 MFP */
#define SYS_GPB_MFPH_PB11MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for GPIO         \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_ADC_CH11    (0x01UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for ADC_CH11     \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_ADC0_CH11   (0x01UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for ADC0_CH11    \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_EBI_ADR16   (0x02UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for EBI_ADR16    \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_UART0_nCTS  (0x05UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for UART0_nCTS   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_UART4_TXD   (0x06UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for UART4_TXD    \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_I2C1_SCL    (0x07UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for I2C1_SCL     \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_SPI0_I2SMCLK (0x09UL<<SYS_GPB_MFPH_PB11MFP_Pos)/*!< GPB_MFPH PB11 setting for SPI0_I2SMCLK \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_BPWM1_CH0   (0x0AUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< GPB_MFPH PB11 setting for BPWM1_CH0    \hideinitializer */

/* PB.12 MFP */
#define SYS_GPB_MFPH_PB12MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for GPIO       \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_ADC_CH12    (0x01UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for ADC_CH12   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_ADC0_CH12   (0x01UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for ADC0_CH12  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_ACMP0_P2    (0x01UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for ACMP0_P2   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_ACMP1_P2    (0x01UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for ACMP1_P2   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_EBI_AD15    (0x02UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for EBI_AD15   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_SPI0_MOSI   (0x04UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for SPI0_MOSI  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_USCI0_CLK   (0x05UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for USCI0_CLK  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_UART0_RXD   (0x06UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for UART0_RXD  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_UART3_nCTS  (0x07UL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for UART3_nCTS \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_PWM1_CH3    (0x0BUL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for PWM1_CH3   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_BPWM0_CH0   (0x0CUL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for BPWM0_CH0  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_TM3_EXT     (0x0DUL<<SYS_GPB_MFPH_PB12MFP_Pos)/*!< GPB_MFPH PB12 setting for TM3_EXT    \hideinitializer */

/* PB.13 MFP */
#define SYS_GPB_MFPH_PB13MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for GPIO       \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_ADC_CH13    (0x01UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for ADC_CH13   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_ADC0_CH13   (0x01UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for ADC0_CH13  \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_ACMP0_P3    (0x01UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for ACMP0_P3   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_ACMP1_P3    (0x01UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for ACMP1_P3   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_EBI_AD14    (0x02UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for EBI_AD14   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_SPI0_MISO   (0x04UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for SPI0_MISO  \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_USCI0_DAT0  (0x05UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for USCI0_DAT0 \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_UART0_TXD   (0x06UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for UART0_TXD  \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_UART3_nRTS  (0x07UL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for UART3_nRTS \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_PWM1_CH2    (0x0BUL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for PWM1_CH2   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_BPWM0_CH1   (0x0CUL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for BPWM0_CH1  \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_TM2_EXT     (0x0DUL<<SYS_GPB_MFPH_PB13MFP_Pos)/*!< GPB_MFPH PB13 setting for TM2_EXT    \hideinitializer */

/* PB.14 MFP */
#define SYS_GPB_MFPH_PB14MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for GPIO       \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_ADC_CH14    (0x01UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for ADC_CH14   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_ADC0_CH14   (0x01UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for ADC0_CH14  \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_EBI_AD13    (0x02UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for EBI_AD13   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_SPI0_CLK    (0x04UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for SPI0_CLK   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_USCI0_DAT1  (0x05UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for USCI0_DAT1 \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_UART0_nRTS  (0x06UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for UART0_nRTS \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_UART3_RXD   (0x07UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for UART3_RXD  \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_BPWM1_CH5   (0x09UL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for BPWM1_CH5  \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_PWM1_CH1    (0x0BUL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for PWM1_CH1   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_BPWM0_CH2   (0x0CUL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for BPWM0_CH2  \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_TM1_EXT     (0x0DUL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for TM1_EXT    \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_CLKO        (0x0EUL<<SYS_GPB_MFPH_PB14MFP_Pos)/*!< GPB_MFPH PB14 setting for CLKO       \hideinitializer */

/* PB.15 MFP */
#define SYS_GPB_MFPH_PB15MFP_GPIO        (0x00UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for GPIO          \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_ADC_CH15    (0x01UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for ADC_CH15      \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_ADC0_CH15   (0x01UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for ADC0_CH15     \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_EBI_AD12    (0x02UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for EBI_AD12      \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_SPI0_SS     (0x04UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for SPI0_SS       \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_USCI0_CTL1  (0x05UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for USCI0_CTL1    \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_UART0_nCTS  (0x06UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for UART0_nCTS    \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_UART3_TXD   (0x07UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for UART3_TXD     \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_BPWM1_CH4   (0x09UL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for BPWM1_CH4     \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_PWM1_CH0    (0x0BUL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for PWM1_CH0      \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_BPWM0_CH3   (0x0CUL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for BPWM0_CH3     \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_TM0_EXT     (0x0DUL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for TM0_EXT       \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_PWM0_BRAKE1 (0x0FUL<<SYS_GPB_MFPH_PB15MFP_Pos)/*!< GPB_MFPH PB15 setting for PWM0_BRAKE1   \hideinitializer */

/* PC.0 MFP */
#define SYS_GPC_MFPL_PC0MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_EBI_AD0      (0x02UL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for EBI_AD0     \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_QSPI0_MOSI0  (0x04UL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for QSPI0_MOSI0 \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_UART2_RXD    (0x08UL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for UART2_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_I2C0_SDA     (0x09UL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for I2C0_SDA    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_BPWM1_CH3    (0x0BUL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for BPWM1_CH3   \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_PWM1_CH5     (0x0CUL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for PWM1_CH5    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_BPWM0_CH4    (0x0DUL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for BPWM0_CH4   \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_ACMP1_O      (0x0EUL<<SYS_GPC_MFPL_PC0MFP_Pos) /*!< GPC_MFPL PC0 setting for ACMP1_O     \hideinitializer */

/* PC.1 MFP */
#define SYS_GPC_MFPL_PC1MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_EBI_AD1      (0x02UL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for EBI_AD1     \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_QSPI0_MISO0  (0x04UL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for QSPI0_MISO0 \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_UART2_TXD    (0x08UL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for UART2_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_I2C0_SCL     (0x09UL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for I2C0_SCL    \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_BPWM1_CH2    (0x0BUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for BPWM1_CH2   \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_PWM1_CH4     (0x0CUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for PWM1_CH4    \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_BPWM0_CH5    (0x0DUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for BPWM0_CH5   \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_ACMP0_O      (0x0EUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for ACMP0_O     \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_ADC_ST       (0x0FUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for ADC_ST      \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_ADC0_ST      (0x0FUL<<SYS_GPC_MFPL_PC1MFP_Pos) /*!< GPC_MFPL PC1 setting for ADC0_ST     \hideinitializer */

/* PC.2 MFP */
#define SYS_GPC_MFPL_PC2MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_EBI_AD2      (0x02UL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for EBI_AD2     \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_QSPI0_CLK    (0x04UL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for QSPI0_CLK   \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_UART2_nCTS   (0x08UL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for UART2_nCTS  \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_I2C0_SMBSUS  (0x09UL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for I2C0_SMBSUS \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_UART3_RXD    (0x0BUL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for UART3_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_PWM1_CH3     (0x0CUL<<SYS_GPC_MFPL_PC2MFP_Pos) /*!< GPC_MFPL PC2 setting for PWM1_CH3    \hideinitializer */

/* PC.3 MFP */
#define SYS_GPC_MFPL_PC3MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_EBI_AD3      (0x02UL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for EBI_AD3     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_QSPI0_SS     (0x04UL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for QSPI0_SS    \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_UART2_nRTS   (0x08UL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for UART2_nRTS  \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_I2C0_SMBAL   (0x09UL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for I2C0_SMBAL  \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_UART3_TXD    (0x0BUL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for UART3_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_PWM1_CH2     (0x0CUL<<SYS_GPC_MFPL_PC3MFP_Pos) /*!< GPC_MFPL PC3 setting for PWM1_CH2    \hideinitializer */

/* PC.4 MFP */
#define SYS_GPC_MFPL_PC4MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_EBI_AD4      (0x02UL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for EBI_AD4     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_QSPI0_MOSI1  (0x04UL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for QSPI0_MOSI1 \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_UART2_RXD    (0x08UL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for UART2_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_I2C1_SDA     (0x09UL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_UART4_RXD    (0x0BUL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for UART4_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_PWM1_CH1     (0x0CUL<<SYS_GPC_MFPL_PC4MFP_Pos) /*!< GPC_MFPL PC4 setting for PWM1_CH1    \hideinitializer */

/* PC.5 MFP */
#define SYS_GPC_MFPL_PC5MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_EBI_AD5      (0x02UL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for EBI_AD5     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_QSPI0_MISO1  (0x04UL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for QSPI0_MISO1 \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_UART2_TXD    (0x08UL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for UART2_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_I2C1_SCL     (0x09UL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_UART4_TXD    (0x0BUL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for UART4_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_PWM1_CH0     (0x0CUL<<SYS_GPC_MFPL_PC5MFP_Pos) /*!< GPC_MFPL PC5 setting for PWM1_CH0    \hideinitializer */

/* PC.6 MFP */
#define SYS_GPC_MFPL_PC6MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_EBI_AD8      (0x02UL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for EBI_AD8     \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_UART4_RXD    (0x05UL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for UART4_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_UART0_nRTS   (0x07UL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for UART0_nRTS  \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_UART6_RXD    (0x09UL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for UART6_RXD   \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_PWM1_CH3     (0x0BUL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for PWM1_CH3    \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_BPWM1_CH1    (0x0CUL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for BPWM1_CH1   \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_TM1          (0x0EUL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for TM1         \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_INT2         (0x0FUL<<SYS_GPC_MFPL_PC6MFP_Pos) /*!< GPC_MFPL PC6 setting for INT2        \hideinitializer */

/* PC.7 MFP */
#define SYS_GPC_MFPL_PC7MFP_GPIO         (0x00UL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for GPIO        \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_EBI_AD9      (0x02UL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for EBI_AD9     \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_UART4_TXD    (0x05UL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for UART4_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_UART0_nCTS   (0x07UL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for UART0_nCTS  \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_UART6_TXD    (0x09UL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for UART6_TXD   \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_PWM1_CH2     (0x0BUL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for PWM1_CH2    \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_BPWM1_CH0    (0x0CUL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for BPWM1_CH0   \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_TM0          (0x0EUL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for TM0         \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_INT3         (0x0FUL<<SYS_GPC_MFPL_PC7MFP_Pos) /*!< GPC_MFPL PC7 setting for INT3        \hideinitializer */

/* PC.8 MFP */
#define SYS_GPC_MFPH_PC8MFP_GPIO         (0x00UL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for GPIO       \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_EBI_ADR16    (0x02UL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for EBI_ADR16  \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_I2C0_SDA     (0x04UL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for I2C0_SDA   \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_UART4_nCTS   (0x05UL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for UART4_nCTS \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_UART1_RXD    (0x08UL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for UART1_RXD  \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_PWM1_CH1     (0x0BUL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for PWM1_CH1   \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_BPWM1_CH4    (0x0CUL<<SYS_GPC_MFPH_PC8MFP_Pos) /*!< GPC_MFPH PC8 setting for BPWM1_CH4  \hideinitializer */

/* PC.9 MFP */
#define SYS_GPC_MFPH_PC9MFP_GPIO         (0x00UL<<SYS_GPC_MFPH_PC9MFP_Pos) /*!< GPC_MFPH PC9 setting for GPIO       \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_EBI_ADR7     (0x02UL<<SYS_GPC_MFPH_PC9MFP_Pos) /*!< GPC_MFPH PC9 setting for EBI_ADR7   \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_UART6_nCTS   (0x05UL<<SYS_GPC_MFPH_PC9MFP_Pos) /*!< GPC_MFPH PC9 setting for UART6_nCTS \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_UART3_RXD    (0x07UL<<SYS_GPC_MFPH_PC9MFP_Pos) /*!< GPC_MFPH PC9 setting for UART3_RXD  \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_PWM1_CH3     (0x0CUL<<SYS_GPC_MFPH_PC9MFP_Pos) /*!< GPC_MFPH PC9 setting for PWM1_CH3   \hideinitializer */

/* PC.10 MFP */
#define SYS_GPC_MFPH_PC10MFP_GPIO        (0x00UL<<SYS_GPC_MFPH_PC10MFP_Pos)/*!< GPC_MFPH PC10 setting for GPIO          \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_EBI_ADR6    (0x02UL<<SYS_GPC_MFPH_PC10MFP_Pos)/*!< GPC_MFPH PC10 setting for EBI_ADR6      \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_UART6_nRTS  (0x05UL<<SYS_GPC_MFPH_PC10MFP_Pos)/*!< GPC_MFPH PC10 setting for UART6_nRTS    \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_UART3_TXD   (0x07UL<<SYS_GPC_MFPH_PC10MFP_Pos)/*!< GPC_MFPH PC10 setting for UART3_TXD     \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_PWM1_CH2    (0x0CUL<<SYS_GPC_MFPH_PC10MFP_Pos)/*!< GPC_MFPH PC10 setting for PWM1_CH2      \hideinitializer */

/* PC.11 MFP */
#define SYS_GPC_MFPH_PC11MFP_GPIO        (0x00UL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for GPIO      \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_EBI_ADR5    (0x02UL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for EBI_ADR5  \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_UART0_RXD   (0x03UL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for UART0_RXD \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_I2C0_SDA    (0x04UL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for I2C0_SDA  \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_UART6_RXD   (0x05UL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for UART6_RXD \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_PWM1_CH1    (0x0CUL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for PWM1_CH1  \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_ACMP1_O     (0x0EUL<<SYS_GPC_MFPH_PC11MFP_Pos)/*!< GPC_MFPH PC11 setting for ACMP1_O   \hideinitializer */

/* PC.12 MFP */
#define SYS_GPC_MFPH_PC12MFP_GPIO        (0x00UL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for GPIO      \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_EBI_ADR4    (0x02UL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for EBI_ADR4  \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_UART0_TXD   (0x03UL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for UART0_TXD \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_I2C0_SCL    (0x04UL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for I2C0_SCL  \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_UART6_TXD   (0x05UL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for UART6_TXD \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_PWM1_CH0    (0x0CUL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for PWM1_CH0  \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_ACMP0_O     (0x0EUL<<SYS_GPC_MFPH_PC12MFP_Pos)/*!< GPC_MFPH PC12 setting for ACMP0_O   \hideinitializer */

/* PC.13 MFP */
#define SYS_GPC_MFPH_PC13MFP_GPIO        (0x00UL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for GPIO          \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_EBI_ADR10   (0x02UL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for EBI_ADR10     \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_USCI0_CTL0  (0x06UL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for USCI0_CTL0    \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_UART2_TXD   (0x07UL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for UART2_TXD     \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_BPWM0_CH4   (0x09UL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for BPWM0_CH4     \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_CLKO        (0x0DUL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for CLKO          \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_ADC_ST      (0x0EUL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for ADC_ST        \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_ADC0_ST     (0x0EUL<<SYS_GPC_MFPH_PC13MFP_Pos)/*!< GPC_MFPH PC13 setting for ADC0_ST       \hideinitializer */

/* PC.14 MFP */
#define SYS_GPC_MFPH_PC14MFP_GPIO        (0x00UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< GPC_MFPH PC14 setting for GPIO         \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_EBI_AD11    (0x02UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< GPC_MFPH PC14 setting for EBI_AD11     \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPC_MFPH_PC14MFP_Pos)/*!< GPC_MFPH PC14 setting for SPI0_I2SMCLK \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_USCI0_CTL0  (0x05UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< GPC_MFPH PC14 setting for USCI0_CTL0   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_QSPI0_CLK   (0x06UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< GPC_MFPH PC14 setting for QSPI0_CLK    \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_TM1         (0x0DUL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< GPC_MFPH PC14 setting for TM1          \hideinitializer */

/* PC.15 MFP */

/* PD.0 MFP */
#define SYS_GPD_MFPL_PD0MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for GPIO        \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_EBI_AD13     (0x02UL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for EBI_AD13    \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_USCI0_CLK    (0x03UL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for USCI0_CLK   \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_SPI0_MOSI    (0x04UL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for SPI0_MOSI   \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_UART3_RXD    (0x05UL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for UART3_RXD   \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_TM2          (0x0EUL<<SYS_GPD_MFPL_PD0MFP_Pos) /*!< GPD_MFPL PD0 setting for TM2         \hideinitializer */

/* PD.1 MFP */
#define SYS_GPD_MFPL_PD1MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD1MFP_Pos) /*!< GPD_MFPL PD1 setting for GPIO        \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_EBI_AD12     (0x02UL<<SYS_GPD_MFPL_PD1MFP_Pos) /*!< GPD_MFPL PD1 setting for EBI_AD12    \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_USCI0_DAT0   (0x03UL<<SYS_GPD_MFPL_PD1MFP_Pos) /*!< GPD_MFPL PD1 setting for USCI0_DAT0  \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_SPI0_MISO    (0x04UL<<SYS_GPD_MFPL_PD1MFP_Pos) /*!< GPD_MFPL PD1 setting for SPI0_MISO   \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_UART3_TXD    (0x05UL<<SYS_GPD_MFPL_PD1MFP_Pos) /*!< GPD_MFPL PD1 setting for UART3_TXD   \hideinitializer */

/* PD.2 MFP */
#define SYS_GPD_MFPL_PD2MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for GPIO        \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_EBI_AD11     (0x02UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for EBI_AD11    \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_USCI0_DAT1   (0x03UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for USCI0_DAT1  \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_SPI0_CLK     (0x04UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for SPI0_CLK    \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_UART3_nCTS   (0x05UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for UART3_nCTS  \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_UART0_RXD    (0x09UL<<SYS_GPD_MFPL_PD2MFP_Pos) /*!< GPD_MFPL PD2 setting for UART0_RXD   \hideinitializer */

/* PD.3 MFP */
#define SYS_GPD_MFPL_PD3MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for GPIO        \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_EBI_AD10     (0x02UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for EBI_AD10    \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_USCI0_CTL1   (0x03UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for USCI0_CTL1  \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_SPI0_SS      (0x04UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for SPI0_SS     \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_UART3_nRTS   (0x05UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for UART3_nRTS  \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_USCI1_CTL0   (0x06UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for USCI1_CTL0  \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_UART0_TXD    (0x09UL<<SYS_GPD_MFPL_PD3MFP_Pos) /*!< GPD_MFPL PD3 setting for UART0_TXD   \hideinitializer */

/* PD.4 MFP */
#define SYS_GPD_MFPL_PD4MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD4MFP_Pos) /*!< GPD_MFPL PD4 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_USCI0_CTL0   (0x03UL<<SYS_GPD_MFPL_PD4MFP_Pos) /*!< GPD_MFPL PD4 setting for USCI0_CTL0 \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_I2C1_SDA     (0x04UL<<SYS_GPD_MFPL_PD4MFP_Pos) /*!< GPD_MFPL PD4 setting for I2C1_SDA   \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_USCI1_CTL1   (0x06UL<<SYS_GPD_MFPL_PD4MFP_Pos) /*!< GPD_MFPL PD4 setting for USCI1_CTL1 \hideinitializer */

/* PD.5 MFP */
#define SYS_GPD_MFPL_PD5MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD5MFP_Pos) /*!< GPD_MFPL PD5 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_I2C1_SCL     (0x04UL<<SYS_GPD_MFPL_PD5MFP_Pos) /*!< GPD_MFPL PD5 setting for I2C1_SCL   \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_USCI1_DAT0   (0x06UL<<SYS_GPD_MFPL_PD5MFP_Pos) /*!< GPD_MFPL PD5 setting for USCI1_DAT0 \hideinitializer */

/* PD.6 MFP */
#define SYS_GPD_MFPL_PD6MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD6MFP_Pos) /*!< GPD_MFPL PD6 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_UART1_RXD    (0x03UL<<SYS_GPD_MFPL_PD6MFP_Pos) /*!< GPD_MFPL PD6 setting for UART1_RXD  \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_I2C0_SDA     (0x04UL<<SYS_GPD_MFPL_PD6MFP_Pos) /*!< GPD_MFPL PD6 setting for I2C0_SDA   \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_USCI1_DAT1   (0x06UL<<SYS_GPD_MFPL_PD6MFP_Pos) /*!< GPD_MFPL PD6 setting for USCI1_DAT1 \hideinitializer */

/* PD.7 MFP */
#define SYS_GPD_MFPL_PD7MFP_GPIO         (0x00UL<<SYS_GPD_MFPL_PD7MFP_Pos) /*!< GPD_MFPL PD7 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_UART1_TXD    (0x03UL<<SYS_GPD_MFPL_PD7MFP_Pos) /*!< GPD_MFPL PD7 setting for UART1_TXD  \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_I2C0_SCL     (0x04UL<<SYS_GPD_MFPL_PD7MFP_Pos) /*!< GPD_MFPL PD7 setting for I2C0_SCL   \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_USCI1_CLK    (0x06UL<<SYS_GPD_MFPL_PD7MFP_Pos) /*!< GPD_MFPL PD7 setting for USCI1_CLK  \hideinitializer */

/* PD.8 MFP */
#define SYS_GPD_MFPH_PD8MFP_GPIO         (0x00UL<<SYS_GPD_MFPH_PD8MFP_Pos) /*!< GPD_MFPH PD8 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPH_PD8MFP_EBI_AD6      (0x02UL<<SYS_GPD_MFPH_PD8MFP_Pos) /*!< GPD_MFPH PD8 setting for EBI_AD6    \hideinitializer */
#define SYS_GPD_MFPH_PD8MFP_UART2_nRTS   (0x04UL<<SYS_GPD_MFPH_PD8MFP_Pos) /*!< GPD_MFPH PD8 setting for UART2_nRTS \hideinitializer */
#define SYS_GPD_MFPH_PD8MFP_UART7_RXD    (0x05UL<<SYS_GPD_MFPH_PD8MFP_Pos) /*!< GPD_MFPH PD8 setting for UART7_RXD  \hideinitializer */

/* PD.9 MFP */
#define SYS_GPD_MFPH_PD9MFP_GPIO         (0x00UL<<SYS_GPD_MFPH_PD9MFP_Pos) /*!< GPD_MFPH PD9 setting for GPIO       \hideinitializer */
#define SYS_GPD_MFPH_PD9MFP_EBI_AD7      (0x02UL<<SYS_GPD_MFPH_PD9MFP_Pos) /*!< GPD_MFPH PD9 setting for EBI_AD7    \hideinitializer */
#define SYS_GPD_MFPH_PD9MFP_UART2_nCTS   (0x04UL<<SYS_GPD_MFPH_PD9MFP_Pos) /*!< GPD_MFPH PD9 setting for UART2_nCTS \hideinitializer */
#define SYS_GPD_MFPH_PD9MFP_UART7_TXD    (0x05UL<<SYS_GPD_MFPH_PD9MFP_Pos) /*!< GPD_MFPH PD9 setting for UART7_TXD  \hideinitializer */

/* PD.10 MFP */
#define SYS_GPD_MFPH_PD10MFP_GPIO        (0x00UL<<SYS_GPD_MFPH_PD10MFP_Pos)/*!< GPD_MFPH PD10 setting for GPIO      \hideinitializer */
#define SYS_GPD_MFPH_PD10MFP_EBI_nCS2    (0x02UL<<SYS_GPD_MFPH_PD10MFP_Pos)/*!< GPD_MFPH PD10 setting for EBI_nCS2  \hideinitializer */
#define SYS_GPD_MFPH_PD10MFP_UART1_RXD   (0x03UL<<SYS_GPD_MFPH_PD10MFP_Pos)/*!< GPD_MFPH PD10 setting for UART1_RXD \hideinitializer */

/* PD.11 MFP */
#define SYS_GPD_MFPH_PD11MFP_GPIO        (0x00UL<<SYS_GPD_MFPH_PD11MFP_Pos)/*!< GPD_MFPH PD11 setting for GPIO      \hideinitializer */
#define SYS_GPD_MFPH_PD11MFP_EBI_nCS1    (0x02UL<<SYS_GPD_MFPH_PD11MFP_Pos)/*!< GPD_MFPH PD11 setting for EBI_nCS1  \hideinitializer */
#define SYS_GPD_MFPH_PD11MFP_UART1_TXD   (0x03UL<<SYS_GPD_MFPH_PD11MFP_Pos)/*!< GPD_MFPH PD11 setting for UART1_TXD \hideinitializer */

/* PD.12 MFP */
#define SYS_GPD_MFPH_PD12MFP_GPIO        (0x00UL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for GPIO      \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_EBI_nCS0    (0x02UL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for EBI_nCS0  \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_UART2_RXD   (0x07UL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for UART2_RXD \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_BPWM0_CH5   (0x09UL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for BPWM0_CH5 \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_CLKO        (0x0DUL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for CLKO      \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_ADC_ST      (0x0EUL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for ADC_ST    \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_ADC0_ST     (0x0EUL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for ADC0_ST   \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_INT5        (0x0FUL<<SYS_GPD_MFPH_PD12MFP_Pos)/*!< GPD_MFPH PD12 setting for INT5      \hideinitializer */

/* PD.13 MFP */
#define SYS_GPD_MFPH_PD13MFP_GPIO         (0x00UL<<SYS_GPD_MFPH_PD13MFP_Pos)/*!< GPD_MFPH PD13 setting for GPIO         \hideinitializer */
#define SYS_GPD_MFPH_PD13MFP_EBI_AD10     (0x02UL<<SYS_GPD_MFPH_PD13MFP_Pos)/*!< GPD_MFPH PD13 setting for EBI_AD10     \hideinitializer */
#define SYS_GPD_MFPH_PD13MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPD_MFPH_PD13MFP_Pos)/*!< GPD_MFPH PD13 setting for SPI0_I2SMCLK \hideinitializer */

/* PD.14 MFP */
#define SYS_GPD_MFPH_PD14MFP_GPIO         (0x00UL<<SYS_GPD_MFPH_PD14MFP_Pos)/*!< GPD_MFPH PD14 setting for GPIO         \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_EBI_nCS0     (0x02UL<<SYS_GPD_MFPH_PD14MFP_Pos)/*!< GPD_MFPH PD14 setting for EBI_nCS0     \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_SPI0_I2SMCLK (0x05UL<<SYS_GPD_MFPH_PD14MFP_Pos)/*!< GPD_MFPH PD14 setting for SPI0_I2SMCLK \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_USCI0_CTL0   (0x08UL<<SYS_GPD_MFPH_PD14MFP_Pos)/*!< GPD_MFPH PD14 setting for USCI0_CTL0   \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_PWM0_CH4     (0x0BUL<<SYS_GPD_MFPH_PD14MFP_Pos)/*!< GPD_MFPH PD14 setting for PWM0_CH4     \hideinitializer */

/* PD.15 MFP */
#define SYS_GPD_MFPH_PD15MFP_GPIO        (0x00UL<<SYS_GPD_MFPH_PD15MFP_Pos)/*!< GPD_MFPH PD15 setting for GPIO      \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_PWM0_CH5    (0x0CUL<<SYS_GPD_MFPH_PD15MFP_Pos)/*!< GPD_MFPH PD15 setting for PWM0_CH5  \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_TM3         (0x0EUL<<SYS_GPD_MFPH_PD15MFP_Pos)/*!< GPD_MFPH PD15 setting for TM3       \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_INT1        (0x0FUL<<SYS_GPD_MFPH_PD15MFP_Pos)/*!< GPD_MFPH PD15 setting for INT1      \hideinitializer */

/* PE.0 MFP */
#define SYS_GPE_MFPL_PE0MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for GPIO           \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_EBI_AD11     (0x02UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for EBI_AD11       \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_QSPI0_MOSI0  (0x03UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for QSPI0_MOSI0    \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_UART3_RXD    (0x07UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for UART3_RXD      \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_I2C1_SDA     (0x08UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for I2C1_SDA       \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_UART4_nRTS   (0x09UL<<SYS_GPE_MFPL_PE0MFP_Pos) /*!< GPE_MFPL PE0 setting for UART4_nRTS     \hideinitializer */

/* PE.1 MFP */
#define SYS_GPE_MFPL_PE1MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for GPIO           \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_EBI_AD10     (0x02UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for EBI_AD10       \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_QSPI0_MISO0  (0x03UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for QSPI0_MISO0    \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_UART3_TXD    (0x07UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for UART3_TXD      \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_I2C1_SCL     (0x08UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for I2C1_SCL       \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_UART4_nCTS   (0x09UL<<SYS_GPE_MFPL_PE1MFP_Pos) /*!< GPE_MFPL PE1 setting for UART4_nCTS     \hideinitializer */

/* PE.2 MFP */
#define SYS_GPE_MFPL_PE2MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_EBI_ALE      (0x02UL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for EBI_ALE    \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_USCI0_CLK    (0x07UL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for USCI0_CLK  \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_UART6_nCTS   (0x08UL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for UART6_nCTS \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_UART7_RXD    (0x09UL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for UART7_RXD  \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_PWM0_CH5     (0x0CUL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for PWM0_CH5   \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_BPWM0_CH0    (0x0DUL<<SYS_GPE_MFPL_PE2MFP_Pos) /*!< GPE_MFPL PE2 setting for BPWM0_CH0  \hideinitializer */

/* PE.3 MFP */
#define SYS_GPE_MFPL_PE3MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_EBI_MCLK     (0x02UL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for EBI_MCLK   \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_USCI0_DAT0   (0x07UL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for USCI0_DAT0 \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_UART6_nRTS   (0x08UL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for UART6_nRTS \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_UART7_TXD    (0x09UL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for UART7_TXD  \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_PWM0_CH4     (0x0CUL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for PWM0_CH4   \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_BPWM0_CH1    (0x0DUL<<SYS_GPE_MFPL_PE3MFP_Pos) /*!< GPE_MFPL PE3 setting for BPWM0_CH1  \hideinitializer */

/* PE.4 MFP */
#define SYS_GPE_MFPL_PE4MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_EBI_nWR      (0x02UL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for EBI_nWR    \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_USCI0_DAT1   (0x07UL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for USCI0_DAT1 \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_UART6_RXD    (0x08UL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for UART6_RXD  \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_UART7_nCTS   (0x09UL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for UART7_nCTS \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_PWM0_CH3     (0x0CUL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for PWM0_CH3   \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_BPWM0_CH2    (0x0DUL<<SYS_GPE_MFPL_PE4MFP_Pos) /*!< GPE_MFPL PE4 setting for BPWM0_CH2  \hideinitializer */

/* PE.5 MFP */
#define SYS_GPE_MFPL_PE5MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_EBI_nRD      (0x02UL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for EBI_nRD    \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_USCI0_CTL1   (0x07UL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for USCI0_CTL1 \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_UART6_TXD    (0x08UL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for UART6_TXD  \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_UART7_nRTS   (0x09UL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for UART7_nRTS \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_PWM0_CH2     (0x0CUL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for PWM0_CH2   \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_BPWM0_CH3    (0x0DUL<<SYS_GPE_MFPL_PE5MFP_Pos) /*!< GPE_MFPL PE5 setting for BPWM0_CH3  \hideinitializer */

/* PE.6 MFP */
#define SYS_GPE_MFPL_PE6MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE6MFP_Pos) /*!< GPE_MFPL PE6 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_USCI0_CTL0   (0x07UL<<SYS_GPE_MFPL_PE6MFP_Pos) /*!< GPE_MFPL PE6 setting for USCI0_CTL0 \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_UART5_RXD    (0x08UL<<SYS_GPE_MFPL_PE6MFP_Pos) /*!< GPE_MFPL PE6 setting for UART5_RXD  \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_PWM0_CH1     (0x0CUL<<SYS_GPE_MFPL_PE6MFP_Pos) /*!< GPE_MFPL PE6 setting for PWM0_CH1   \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_BPWM0_CH4    (0x0DUL<<SYS_GPE_MFPL_PE6MFP_Pos) /*!< GPE_MFPL PE6 setting for BPWM0_CH4  \hideinitializer */

/* PE.7 MFP */
#define SYS_GPE_MFPL_PE7MFP_GPIO         (0x00UL<<SYS_GPE_MFPL_PE7MFP_Pos) /*!< GPE_MFPL PE7 setting for GPIO       \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_UART5_TXD    (0x08UL<<SYS_GPE_MFPL_PE7MFP_Pos) /*!< GPE_MFPL PE7 setting for UART5_TXD  \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_PWM0_CH0     (0x0CUL<<SYS_GPE_MFPL_PE7MFP_Pos) /*!< GPE_MFPL PE7 setting for PWM0_CH0   \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_BPWM0_CH5    (0x0DUL<<SYS_GPE_MFPL_PE7MFP_Pos) /*!< GPE_MFPL PE7 setting for BPWM0_CH5  \hideinitializer */

/* PE.8 MFP */
#define SYS_GPE_MFPH_PE8MFP_GPIO         (0x00UL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for GPIO           \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_EBI_ADR10    (0x02UL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for EBI_ADR10      \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_USCI1_CTL1   (0x06UL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for USCI1_CTL1     \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_UART2_TXD    (0x07UL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for UART2_TXD      \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_PWM0_CH0     (0x0AUL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for PWM0_CH0       \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_PWM0_BRAKE0  (0x0BUL<<SYS_GPE_MFPH_PE8MFP_Pos) /*!< GPE_MFPH PE8 setting for PWM0_BRAKE0    \hideinitializer */

/* PE.9 MFP */
#define SYS_GPE_MFPH_PE9MFP_GPIO         (0x00UL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for GPIO           \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_EBI_ADR11    (0x02UL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for EBI_ADR11      \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_USCI1_CTL0   (0x06UL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for USCI1_CTL0     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_UART2_RXD    (0x07UL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for UART2_RXD      \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_PWM0_CH1     (0x0AUL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for PWM0_CH1       \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_PWM0_BRAKE1  (0x0BUL<<SYS_GPE_MFPH_PE9MFP_Pos) /*!< GPE_MFPH PE9 setting for PWM0_BRAKE1    \hideinitializer */

/* PE.10 MFP */
#define SYS_GPE_MFPH_PE10MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for GPIO          \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_EBI_ADR12   (0x02UL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for EBI_ADR12     \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_USCI1_DAT0  (0x06UL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for USCI1_DAT0    \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_UART3_TXD   (0x07UL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for UART3_TXD     \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_PWM0_CH2    (0x0AUL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for PWM0_CH2      \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_PWM1_BRAKE0 (0x0BUL<<SYS_GPE_MFPH_PE10MFP_Pos)/*!< GPE_MFPH PE10 setting for PWM1_BRAKE0    \hideinitializer */

/* PE.11 MFP */
#define SYS_GPE_MFPH_PE11MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for GPIO          \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_EBI_ADR13   (0x02UL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for EBI_ADR13     \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_USCI1_DAT1  (0x06UL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for USCI1_DAT1    \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_UART3_RXD   (0x07UL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for UART3_RXD     \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_UART1_nCTS  (0x08UL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for UART1_nCTS    \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_PWM0_CH3    (0x0AUL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for PWM0_CH3      \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_PWM1_BRAKE1 (0x0BUL<<SYS_GPE_MFPH_PE11MFP_Pos)/*!< GPE_MFPH PE11 setting for PWM1_BRAKE1   \hideinitializer */

/* PE.12 MFP */
#define SYS_GPE_MFPH_PE12MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE12MFP_Pos)/*!< GPE_MFPH PE12 setting for GPIO          \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_EBI_ADR14   (0x02UL<<SYS_GPE_MFPH_PE12MFP_Pos)/*!< GPE_MFPH PE12 setting for EBI_ADR14     \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_USCI1_CLK   (0x06UL<<SYS_GPE_MFPH_PE12MFP_Pos)/*!< GPE_MFPH PE12 setting for USCI1_CLK     \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_UART1_nRTS  (0x08UL<<SYS_GPE_MFPH_PE12MFP_Pos)/*!< GPE_MFPH PE12 setting for UART1_nRTS    \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_PWM0_CH4    (0x0AUL<<SYS_GPE_MFPH_PE12MFP_Pos)/*!< GPE_MFPH PE12 setting for PWM0_CH4      \hideinitializer */

/* PE.13 MFP */
#define SYS_GPE_MFPH_PE13MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for GPIO          \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_EBI_ADR15   (0x02UL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for EBI_ADR15     \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_I2C0_SCL    (0x04UL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for I2C0_SCL      \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_UART4_nRTS  (0x05UL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for UART4_nRTS    \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_UART1_TXD   (0x08UL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for UART1_TXD     \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_PWM0_CH5    (0x0AUL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for PWM0_CH5      \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_PWM1_CH0    (0x0BUL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for PWM1_CH0      \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_BPWM1_CH5   (0x0CUL<<SYS_GPE_MFPH_PE13MFP_Pos)/*!< GPE_MFPH PE13 setting for BPWM1_CH5     \hideinitializer */

/* PE.14 MFP */
#define SYS_GPE_MFPH_PE14MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE14MFP_Pos)/*!< GPE_MFPH PE14 setting for GPIO      \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_EBI_AD8     (0x02UL<<SYS_GPE_MFPH_PE14MFP_Pos)/*!< GPE_MFPH PE14 setting for EBI_AD8   \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_UART2_TXD   (0x03UL<<SYS_GPE_MFPH_PE14MFP_Pos)/*!< GPE_MFPH PE14 setting for UART2_TXD \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_UART6_TXD   (0x06UL<<SYS_GPE_MFPH_PE14MFP_Pos)/*!< GPE_MFPH PE14 setting for UART6_TXD \hideinitializer */

/* PE.15 MFP */
#define SYS_GPE_MFPH_PE15MFP_GPIO        (0x00UL<<SYS_GPE_MFPH_PE15MFP_Pos)/*!< GPE_MFPH PE15 setting for GPIO      \hideinitializer */
#define SYS_GPE_MFPH_PE15MFP_EBI_AD9     (0x02UL<<SYS_GPE_MFPH_PE15MFP_Pos)/*!< GPE_MFPH PE15 setting for EBI_AD9   \hideinitializer */
#define SYS_GPE_MFPH_PE15MFP_UART2_RXD   (0x03UL<<SYS_GPE_MFPH_PE15MFP_Pos)/*!< GPE_MFPH PE15 setting for UART2_RXD \hideinitializer */
#define SYS_GPE_MFPH_PE15MFP_UART6_RXD   (0x06UL<<SYS_GPE_MFPH_PE15MFP_Pos)/*!< GPE_MFPH PE15 setting for UART6_RXD \hideinitializer */

/* PF.0 MFP */
#define SYS_GPF_MFPL_PF0MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_UART1_TXD    (0x02UL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for UART1_TXD   \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_I2C1_SCL     (0x03UL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for I2C1_SCL    \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_UART0_TXD    (0x04UL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for UART0_TXD   \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_BPWM1_CH0    (0x0CUL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for BPWM1_CH0   \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_BPWM0_CH5    (0x0DUL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for BPWM0_CH5   \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_ICE_DAT      (0x0EUL<<SYS_GPF_MFPL_PF0MFP_Pos) /*!< GPF_MFPL PF0 setting for ICE_DAT     \hideinitializer */

/* PF.1 MFP */
#define SYS_GPF_MFPL_PF1MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_UART1_RXD    (0x02UL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for UART1_RXD   \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_I2C1_SDA     (0x03UL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_UART0_RXD    (0x04UL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for UART0_RXD   \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_BPWM1_CH1    (0x0CUL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for BPWM1_CH1   \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_BPWM0_CH4    (0x0DUL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for BPWM0_CH4   \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_ICE_CLK      (0x0EUL<<SYS_GPF_MFPL_PF1MFP_Pos) /*!< GPF_MFPL PF1 setting for ICE_CLK     \hideinitializer */

/* PF.2 MFP */
#define SYS_GPF_MFPL_PF2MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_EBI_nCS1     (0x02UL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for EBI_nCS1    \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_UART0_RXD    (0x03UL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for UART0_RXD   \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_I2C0_SDA     (0x04UL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for I2C0_SDA    \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_QSPI0_CLK    (0x05UL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for QSPI0_CLK   \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_XT1_OUT      (0x0AUL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for XT1_OUT     \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_BPWM1_CH1    (0x0BUL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for BPWM1_CH1   \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_USCI1_CTL1   (0x0CUL<<SYS_GPF_MFPL_PF2MFP_Pos) /*!< GPF_MFPL PF2 setting for USCI1_CTL1  \hideinitializer */

/* PF.3 MFP */
#define SYS_GPF_MFPL_PF3MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_EBI_nCS0     (0x02UL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for EBI_nCS0    \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_UART0_TXD    (0x03UL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for UART0_TXD   \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_I2C0_SCL     (0x04UL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for I2C0_SCL    \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_XT1_IN       (0x0AUL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for XT1_IN      \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_BPWM1_CH0    (0x0BUL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for BPWM1_CH0   \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_USCI1_CTL0   (0x0CUL<<SYS_GPF_MFPL_PF3MFP_Pos) /*!< GPF_MFPL PF3 setting for USCI1_CTL0  \hideinitializer */

/* PF.4 MFP */
#define SYS_GPF_MFPL_PF4MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_UART2_TXD    (0x02UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for UART2_TXD   \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_QSPI0_MOSI1  (0x03UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for QSPI0_MOSI1 \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_UART2_nRTS   (0x04UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for UART2_nRTS  \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_PWM0_CH1     (0x07UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for PWM0_CH1    \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_BPWM0_CH5    (0x08UL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for BPWM0_CH5   \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_X32_OUT      (0x0AUL<<SYS_GPF_MFPL_PF4MFP_Pos) /*!< GPF_MFPL PF4 setting for X32_OUT     \hideinitializer */

/* PF.5 MFP */
#define SYS_GPF_MFPL_PF5MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_UART2_RXD    (0x02UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for UART2_RXD   \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_QSPI0_MISO1  (0x03UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for QSPI0_MISO1 \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_UART2_nCTS   (0x04UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for UART2_nCTS  \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_PWM0_CH0     (0x07UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for PWM0_CH0    \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_BPWM0_CH4    (0x08UL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for BPWM0_CH4   \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_X32_IN       (0x0AUL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for X32_IN      \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_ADC_ST       (0x0BUL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for ADC_ST      \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_ADC0_ST      (0x0BUL<<SYS_GPF_MFPL_PF5MFP_Pos) /*!< GPF_MFPL PF5 setting for ADC0_ST     \hideinitializer */

/* PF.6 MFP */
#define SYS_GPF_MFPL_PF6MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF6MFP_Pos) /*!< GPF_MFPL PF6 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_EBI_ADR19    (0x02UL<<SYS_GPF_MFPL_PF6MFP_Pos) /*!< GPF_MFPL PF6 setting for EBI_ADR19   \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_SPI0_MOSI    (0x05UL<<SYS_GPF_MFPL_PF6MFP_Pos) /*!< GPF_MFPL PF6 setting for SPI0_MOSI   \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_UART4_RXD    (0x06UL<<SYS_GPF_MFPL_PF6MFP_Pos) /*!< GPF_MFPL PF6 setting for UART4_RXD   \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_EBI_nCS0     (0x07UL<<SYS_GPF_MFPL_PF6MFP_Pos) /*!< GPF_MFPL PF6 setting for EBI_nCS0    \hideinitializer */

/* PF.7 MFP */
#define SYS_GPF_MFPL_PF7MFP_GPIO         (0x00UL<<SYS_GPF_MFPL_PF7MFP_Pos) /*!< GPF_MFPL PF7 setting for GPIO       \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_EBI_ADR18    (0x02UL<<SYS_GPF_MFPL_PF7MFP_Pos) /*!< GPF_MFPL PF7 setting for EBI_ADR18  \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_SPI0_MISO    (0x05UL<<SYS_GPF_MFPL_PF7MFP_Pos) /*!< GPF_MFPL PF7 setting for SPI0_MISO  \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_UART4_TXD    (0x06UL<<SYS_GPF_MFPL_PF7MFP_Pos) /*!< GPF_MFPL PF7 setting for UART4_TXD  \hideinitializer */

/* PF.8 MFP */
#define SYS_GPF_MFPH_PF8MFP_GPIO         (0x00UL<<SYS_GPF_MFPH_PF8MFP_Pos) /*!< GPF_MFPH PF8 setting for GPIO       \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_EBI_ADR17    (0x02UL<<SYS_GPF_MFPH_PF8MFP_Pos) /*!< GPF_MFPH PF8 setting for EBI_ADR17  \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_SPI0_CLK     (0x05UL<<SYS_GPF_MFPH_PF8MFP_Pos) /*!< GPF_MFPH PF8 setting for SPI0_CLK   \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_UART5_nCTS   (0x06UL<<SYS_GPF_MFPH_PF8MFP_Pos) /*!< GPF_MFPH PF8 setting for UART5_nCTS \hideinitializer */

/* PF.9 MFP */
#define SYS_GPF_MFPH_PF9MFP_GPIO         (0x00UL<<SYS_GPF_MFPH_PF9MFP_Pos) /*!< GPF_MFPH PF9 setting for GPIO       \hideinitializer */
#define SYS_GPF_MFPH_PF9MFP_EBI_ADR16    (0x02UL<<SYS_GPF_MFPH_PF9MFP_Pos) /*!< GPF_MFPH PF9 setting for EBI_ADR16  \hideinitializer */
#define SYS_GPF_MFPH_PF9MFP_SPI0_SS      (0x05UL<<SYS_GPF_MFPH_PF9MFP_Pos) /*!< GPF_MFPH PF9 setting for SPI0_SS    \hideinitializer */
#define SYS_GPF_MFPH_PF9MFP_UART5_nRTS   (0x06UL<<SYS_GPF_MFPH_PF9MFP_Pos) /*!< GPF_MFPH PF9 setting for UART5_nRTS \hideinitializer */

/* PF.10 MFP */
#define SYS_GPF_MFPH_PF10MFP_GPIO         (0x00UL<<SYS_GPF_MFPH_PF10MFP_Pos)/*!< GPF_MFPH PF10 setting for GPIO         \hideinitializer */
#define SYS_GPF_MFPH_PF10MFP_EBI_ADR15    (0x02UL<<SYS_GPF_MFPH_PF10MFP_Pos)/*!< GPF_MFPH PF10 setting for EBI_ADR15    \hideinitializer */
#define SYS_GPF_MFPH_PF10MFP_SPI0_I2SMCLK (0x05UL<<SYS_GPF_MFPH_PF10MFP_Pos)/*!< GPF_MFPH PF10 setting for SPI0_I2SMCLK \hideinitializer */
#define SYS_GPF_MFPH_PF10MFP_UART5_RXD    (0x06UL<<SYS_GPF_MFPH_PF10MFP_Pos)/*!< GPF_MFPH PF10 setting for UART5_RXD    \hideinitializer */

/* PF.11 MFP */
#define SYS_GPF_MFPH_PF11MFP_GPIO        (0x00UL<<SYS_GPF_MFPH_PF11MFP_Pos)/*!< GPF_MFPH PF11 setting for GPIO      \hideinitializer */
#define SYS_GPF_MFPH_PF11MFP_EBI_ADR14   (0x02UL<<SYS_GPF_MFPH_PF11MFP_Pos)/*!< GPF_MFPH PF11 setting for EBI_ADR14 \hideinitializer */
#define SYS_GPF_MFPH_PF11MFP_UART5_TXD   (0x06UL<<SYS_GPF_MFPH_PF11MFP_Pos)/*!< GPF_MFPH PF11 setting for UART5_TXD \hideinitializer */
#define SYS_GPF_MFPH_PF11MFP_TM3         (0x0DUL<<SYS_GPF_MFPH_PF11MFP_Pos)/*!< GPF_MFPH PF11 setting for TM3       \hideinitializer */

/* PF.12 MFP */

/* PF.13 MFP */

/* PF.14 MFP \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_GPIO        (0x00UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_PWM1_BRAKE0 (0x09UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for PWM1_BRAKE0 \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_PWM0_BRAKE0 (0x0AUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for PWM0_BRAKE0 \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_PWM0_CH4    (0x0CUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for PWM0_CH4    \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_CLKO        (0x0DUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for CLKO        \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_TM3         (0x0EUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for TM3         \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_INT5        (0x0FUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< GPF_MFPH PF14 setting for INT5        \hideinitializer */

/* PF.15 MFP */
#define SYS_GPF_MFPH_PF15MFP_GPIO        (0x00UL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for GPIO        \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_PWM0_BRAKE0 (0x0BUL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for PWM0_BRAKE0 \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_PWM0_CH1    (0x0CUL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for PWM0_CH1    \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_TM2         (0x0DUL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for TM2         \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_CLKO        (0x0EUL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for CLKO        \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_INT4        (0x0FUL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< GPF_MFPH PF15 setting for INT4        \hideinitializer */

/* PG.0 MFP */

/* PG.1 MFP */

/* PG.2 MFP */
#define SYS_GPG_MFPL_PG2MFP_GPIO         (0x00UL<<SYS_GPG_MFPL_PG2MFP_Pos) /*!< GPG_MFPL PG2 setting for GPIO       \hideinitializer */
#define SYS_GPG_MFPL_PG2MFP_EBI_ADR11    (0x02UL<<SYS_GPG_MFPL_PG2MFP_Pos) /*!< GPG_MFPL PG2 setting for EBI_ADR11  \hideinitializer */
#define SYS_GPG_MFPL_PG2MFP_I2C0_SMBAL   (0x04UL<<SYS_GPG_MFPL_PG2MFP_Pos) /*!< GPG_MFPL PG2 setting for I2C0_SMBAL \hideinitializer */
#define SYS_GPG_MFPL_PG2MFP_I2C1_SCL     (0x05UL<<SYS_GPG_MFPL_PG2MFP_Pos) /*!< GPG_MFPL PG2 setting for I2C1_SCL   \hideinitializer */
#define SYS_GPG_MFPL_PG2MFP_TM0          (0x0DUL<<SYS_GPG_MFPL_PG2MFP_Pos) /*!< GPG_MFPL PG2 setting for TM0        \hideinitializer */

/* PG.3 MFP */
#define SYS_GPG_MFPL_PG3MFP_GPIO         (0x00UL<<SYS_GPG_MFPL_PG3MFP_Pos) /*!< GPG_MFPL PG3 setting for GPIO       \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_EBI_ADR12    (0x02UL<<SYS_GPG_MFPL_PG3MFP_Pos) /*!< GPG_MFPL PG3 setting for EBI_ADR12  \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_I2C0_SMBSUS  (0x04UL<<SYS_GPG_MFPL_PG3MFP_Pos) /*!< GPG_MFPL PG3 setting for I2C0_SMBSUS \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_I2C1_SDA     (0x05UL<<SYS_GPG_MFPL_PG3MFP_Pos) /*!< GPG_MFPL PG3 setting for I2C1_SDA   \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_TM1          (0x0DUL<<SYS_GPG_MFPL_PG3MFP_Pos) /*!< GPG_MFPL PG3 setting for TM1        \hideinitializer */

/* PG.4 MFP */
#define SYS_GPG_MFPL_PG4MFP_GPIO         (0x00UL<<SYS_GPG_MFPL_PG4MFP_Pos) /*!< GPG_MFPL PG4 setting for GPIO       \hideinitializer */
#define SYS_GPG_MFPL_PG4MFP_EBI_ADR13    (0x02UL<<SYS_GPG_MFPL_PG4MFP_Pos) /*!< GPG_MFPL PG4 setting for EBI_ADR13  \hideinitializer */
#define SYS_GPG_MFPL_PG4MFP_TM2          (0x0DUL<<SYS_GPG_MFPL_PG4MFP_Pos) /*!< GPG_MFPL PG4 setting for TM2        \hideinitializer */

/* PG.5 MFP */

/* PG.6 MFP */

/* PG.7 MFP */

/* PG.8 MFP */

/* PG.9 MFP */
#define SYS_GPG_MFPH_PG9MFP_GPIO         (0x00UL<<SYS_GPG_MFPH_PG9MFP_Pos) /*!< GPG_MFPH PG9 setting for GPIO       \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_EBI_AD0      (0x02UL<<SYS_GPG_MFPH_PG9MFP_Pos) /*!< GPG_MFPH PG9 setting for EBI_AD0    \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_BPWM0_CH5    (0x0CUL<<SYS_GPG_MFPH_PG9MFP_Pos) /*!< GPG_MFPH PG9 setting for BPWM0_CH5  \hideinitializer */

/* PG.10 MFP */
#define SYS_GPG_MFPH_PG10MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG10MFP_Pos)/*!< GPG_MFPH PG10 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG10MFP_EBI_AD1     (0x02UL<<SYS_GPG_MFPH_PG10MFP_Pos)/*!< GPG_MFPH PG10 setting for EBI_AD1   \hideinitializer */
#define SYS_GPG_MFPH_PG10MFP_BPWM0_CH4   (0x0CUL<<SYS_GPG_MFPH_PG10MFP_Pos)/*!< GPG_MFPH PG10 setting for BPWM0_CH4 \hideinitializer */

/* PG.11 MFP */
#define SYS_GPG_MFPH_PG11MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG11MFP_Pos)/*!< GPG_MFPH PG11 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG11MFP_EBI_AD2     (0x02UL<<SYS_GPG_MFPH_PG11MFP_Pos)/*!< GPG_MFPH PG11 setting for EBI_AD2   \hideinitializer */
#define SYS_GPG_MFPH_PG11MFP_UART7_TXD   (0x06UL<<SYS_GPG_MFPH_PG11MFP_Pos)/*!< GPG_MFPH PG11 setting for UART7_TXD \hideinitializer */
#define SYS_GPG_MFPH_PG11MFP_BPWM0_CH3   (0x0CUL<<SYS_GPG_MFPH_PG11MFP_Pos)/*!< GPG_MFPH PG11 setting for BPWM0_CH3 \hideinitializer */

/* PG.12 MFP */
#define SYS_GPG_MFPH_PG12MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG12MFP_Pos)/*!< GPG_MFPH PG12 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG12MFP_EBI_AD3     (0x02UL<<SYS_GPG_MFPH_PG12MFP_Pos)/*!< GPG_MFPH PG12 setting for EBI_AD3   \hideinitializer */
#define SYS_GPG_MFPH_PG12MFP_UART7_RXD   (0x06UL<<SYS_GPG_MFPH_PG12MFP_Pos)/*!< GPG_MFPH PG12 setting for UART7_RXD \hideinitializer */
#define SYS_GPG_MFPH_PG12MFP_BPWM0_CH2   (0x0CUL<<SYS_GPG_MFPH_PG12MFP_Pos)/*!< GPG_MFPH PG12 setting for BPWM0_CH2 \hideinitializer */

/* PG.13 MFP */
#define SYS_GPG_MFPH_PG13MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG13MFP_Pos)/*!< GPG_MFPH PG13 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG13MFP_EBI_AD4     (0x02UL<<SYS_GPG_MFPH_PG13MFP_Pos)/*!< GPG_MFPH PG13 setting for EBI_AD4   \hideinitializer */
#define SYS_GPG_MFPH_PG13MFP_UART6_TXD   (0x06UL<<SYS_GPG_MFPH_PG13MFP_Pos)/*!< GPG_MFPH PG13 setting for UART6_TXD \hideinitializer */
#define SYS_GPG_MFPH_PG13MFP_BPWM0_CH1   (0x0CUL<<SYS_GPG_MFPH_PG13MFP_Pos)/*!< GPG_MFPH PG13 setting for BPWM0_CH1 \hideinitializer */

/* PG.14 MFP */
#define SYS_GPG_MFPH_PG14MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG14MFP_Pos)/*!< GPG_MFPH PG14 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG14MFP_EBI_AD5     (0x02UL<<SYS_GPG_MFPH_PG14MFP_Pos)/*!< GPG_MFPH PG14 setting for EBI_AD5   \hideinitializer */
#define SYS_GPG_MFPH_PG14MFP_UART6_RXD   (0x06UL<<SYS_GPG_MFPH_PG14MFP_Pos)/*!< GPG_MFPH PG14 setting for UART6_RXD \hideinitializer */
#define SYS_GPG_MFPH_PG14MFP_BPWM0_CH0   (0x0CUL<<SYS_GPG_MFPH_PG14MFP_Pos)/*!< GPG_MFPH PG14 setting for BPWM0_CH0 \hideinitializer */

/* PG.15 MFP */
#define SYS_GPG_MFPH_PG15MFP_GPIO        (0x00UL<<SYS_GPG_MFPH_PG15MFP_Pos)/*!< GPG_MFPH PG15 setting for GPIO      \hideinitializer */
#define SYS_GPG_MFPH_PG15MFP_CLKO        (0x0EUL<<SYS_GPG_MFPH_PG15MFP_Pos)/*!< GPG_MFPH PG15 setting for CLKO      \hideinitializer */
#define SYS_GPG_MFPH_PG15MFP_ADC_ST      (0x0FUL<<SYS_GPG_MFPH_PG15MFP_Pos)/*!< GPG_MFPH PG15 setting for ADC_ST    \hideinitializer */
#define SYS_GPG_MFPH_PG15MFP_ADC0_ST     (0x0FUL<<SYS_GPG_MFPH_PG15MFP_Pos)/*!< GPG_MFPH PG15 setting for ADC0_ST   \hideinitializer */

/* PH.0 MFP */

/* PH.1 MFP */

/* PH.2 MFP */

/* PH.3 MFP */

/* PH.4 MFP */
#define SYS_GPH_MFPL_PH4MFP_GPIO         (0x00UL<<SYS_GPH_MFPL_PH4MFP_Pos) /*!< GPH_MFPL PH4 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPL_PH4MFP_EBI_ADR3     (0x02UL<<SYS_GPH_MFPL_PH4MFP_Pos) /*!< GPH_MFPL PH4 setting for EBI_ADR3   \hideinitializer */
#define SYS_GPH_MFPL_PH4MFP_UART7_nRTS   (0x04UL<<SYS_GPH_MFPL_PH4MFP_Pos) /*!< GPH_MFPL PH4 setting for UART7_nRTS \hideinitializer */
#define SYS_GPH_MFPL_PH4MFP_UART6_TXD    (0x05UL<<SYS_GPH_MFPL_PH4MFP_Pos) /*!< GPH_MFPL PH4 setting for UART6_TXD  \hideinitializer */

/* PH.5 MFP */
#define SYS_GPH_MFPL_PH5MFP_GPIO         (0x00UL<<SYS_GPH_MFPL_PH5MFP_Pos) /*!< GPH_MFPL PH5 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPL_PH5MFP_EBI_ADR2     (0x02UL<<SYS_GPH_MFPL_PH5MFP_Pos) /*!< GPH_MFPL PH5 setting for EBI_ADR2   \hideinitializer */
#define SYS_GPH_MFPL_PH5MFP_UART7_nCTS   (0x04UL<<SYS_GPH_MFPL_PH5MFP_Pos) /*!< GPH_MFPL PH5 setting for UART7_nCTS \hideinitializer */
#define SYS_GPH_MFPL_PH5MFP_UART6_RXD    (0x05UL<<SYS_GPH_MFPL_PH5MFP_Pos) /*!< GPH_MFPL PH5 setting for UART6_RXD  \hideinitializer */

/* PH.6 MFP */
#define SYS_GPH_MFPL_PH6MFP_GPIO         (0x00UL<<SYS_GPH_MFPL_PH6MFP_Pos) /*!< GPH_MFPL PH6 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPL_PH6MFP_EBI_ADR1     (0x02UL<<SYS_GPH_MFPL_PH6MFP_Pos) /*!< GPH_MFPL PH6 setting for EBI_ADR1   \hideinitializer */
#define SYS_GPH_MFPL_PH6MFP_UART7_TXD    (0x04UL<<SYS_GPH_MFPL_PH6MFP_Pos) /*!< GPH_MFPL PH6 setting for UART7_TXD  \hideinitializer */

/* PH.7 MFP */
#define SYS_GPH_MFPL_PH7MFP_GPIO         (0x00UL<<SYS_GPH_MFPL_PH7MFP_Pos) /*!< GPH_MFPL PH7 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPL_PH7MFP_EBI_ADR0     (0x02UL<<SYS_GPH_MFPL_PH7MFP_Pos) /*!< GPH_MFPL PH7 setting for EBI_ADR0   \hideinitializer */
#define SYS_GPH_MFPL_PH7MFP_UART7_RXD    (0x04UL<<SYS_GPH_MFPL_PH7MFP_Pos) /*!< GPH_MFPL PH7 setting for UART7_RXD  \hideinitializer */

/* PH.8 MFP */
#define SYS_GPH_MFPH_PH8MFP_GPIO         (0x00UL<<SYS_GPH_MFPH_PH8MFP_Pos) /*!< GPH_MFPH PH8 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPH_PH8MFP_EBI_AD12     (0x02UL<<SYS_GPH_MFPH_PH8MFP_Pos) /*!< GPH_MFPH PH8 setting for EBI_AD12   \hideinitializer */
#define SYS_GPH_MFPH_PH8MFP_QSPI0_CLK    (0x03UL<<SYS_GPH_MFPH_PH8MFP_Pos) /*!< GPH_MFPH PH8 setting for QSPI0_CLK  \hideinitializer */
#define SYS_GPH_MFPH_PH8MFP_UART3_nRTS   (0x07UL<<SYS_GPH_MFPH_PH8MFP_Pos) /*!< GPH_MFPH PH8 setting for UART3_nRTS \hideinitializer */
#define SYS_GPH_MFPH_PH8MFP_UART1_TXD    (0x0AUL<<SYS_GPH_MFPH_PH8MFP_Pos) /*!< GPH_MFPH PH8 setting for UART1_TXD  \hideinitializer */

/* PH.9 MFP */
#define SYS_GPH_MFPH_PH9MFP_GPIO         (0x00UL<<SYS_GPH_MFPH_PH9MFP_Pos) /*!< GPH_MFPH PH9 setting for GPIO       \hideinitializer */
#define SYS_GPH_MFPH_PH9MFP_EBI_AD13     (0x02UL<<SYS_GPH_MFPH_PH9MFP_Pos) /*!< GPH_MFPH PH9 setting for EBI_AD13   \hideinitializer */
#define SYS_GPH_MFPH_PH9MFP_QSPI0_SS     (0x03UL<<SYS_GPH_MFPH_PH9MFP_Pos) /*!< GPH_MFPH PH9 setting for QSPI0_SS   \hideinitializer */
#define SYS_GPH_MFPH_PH9MFP_UART3_nCTS   (0x07UL<<SYS_GPH_MFPH_PH9MFP_Pos) /*!< GPH_MFPH PH9 setting for UART3_nCTS \hideinitializer */
#define SYS_GPH_MFPH_PH9MFP_UART1_RXD    (0x0AUL<<SYS_GPH_MFPH_PH9MFP_Pos) /*!< GPH_MFPH PH9 setting for UART1_RXD  \hideinitializer */

/* PH.10 MFP */
#define SYS_GPH_MFPH_PH10MFP_GPIO        (0x00UL<<SYS_GPH_MFPH_PH10MFP_Pos)/*!< GPH_MFPH PH10 setting for GPIO          \hideinitializer */
#define SYS_GPH_MFPH_PH10MFP_EBI_AD14    (0x02UL<<SYS_GPH_MFPH_PH10MFP_Pos)/*!< GPH_MFPH PH10 setting for EBI_AD14      \hideinitializer */
#define SYS_GPH_MFPH_PH10MFP_QSPI0_MISO1 (0x03UL<<SYS_GPH_MFPH_PH10MFP_Pos)/*!< GPH_MFPH PH10 setting for QSPI0_MISO1   \hideinitializer */
#define SYS_GPH_MFPH_PH10MFP_UART4_TXD   (0x07UL<<SYS_GPH_MFPH_PH10MFP_Pos)/*!< GPH_MFPH PH10 setting for UART4_TXD     \hideinitializer */
#define SYS_GPH_MFPH_PH10MFP_UART0_TXD   (0x08UL<<SYS_GPH_MFPH_PH10MFP_Pos)/*!< GPH_MFPH PH10 setting for UART0_TXD     \hideinitializer */

/* PH.11 MFP */
#define SYS_GPH_MFPH_PH11MFP_GPIO        (0x00UL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for GPIO          \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_EBI_AD15    (0x02UL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for EBI_AD15      \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_QSPI0_MOSI1 (0x03UL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for QSPI0_MOSI1   \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_UART4_RXD   (0x07UL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for UART4_RXD     \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_UART0_RXD   (0x08UL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for UART0_RXD     \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_PWM0_CH5    (0x0BUL<<SYS_GPH_MFPH_PH11MFP_Pos)/*!< GPH_MFPH PH11 setting for PWM0_CH5      \hideinitializer */

/* PH.12 MFP */

/* PH.13 MFP */

/* PH.14 MFP */

/* PH.15 MFP */


/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  * \hideinitializer
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Set Brown-out detector function to normal mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to normal mode.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCTL &= ~SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Enable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.
  * \hideinitializer
  */
#define SYS_GET_BOD_INT_FLAG()          (SYS->BODCTL & SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Get Brown-out detector status
  * @param      None
  * @retval     0   System voltage is higher than BOD threshold voltage setting or BOD function is disabled.
  * @retval     >=1 System voltage is lower than BOD threshold voltage setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD function is disabled, this function always return 0.
  * \hideinitializer
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Disable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detect reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Set Brown-out detector function low power mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to low power mode.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_SET_BOD_LPM()               (SYS->BODCTL |= SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Set Brown-out detector voltage level
  * @param[in]  u32Level is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BODVL_2_5V
  *             - \ref SYS_BODCTL_BODVL_2_0V
  * @return     None
  * @details    This macro set Brown-out detector voltage level.
  *             The write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | (u32Level))

/**
  * @brief      Get reset source is from Brown-out detector reset
  * @param      None
  * @retval     0   Previous reset source is not from Brown-out detector reset
  * @retval     >=1 Previous reset source is from Brown-out detector reset
  * @details    This macro get previous reset source is from Brown-out detect reset or not.
  * \hideinitializer
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSTS & SYS_RSTSTS_BODRF_Msk)

/**
  * @brief      Get reset source is from CPU reset
  * @param      None
  * @retval     0   Previous reset source is not from CPU reset
  * @retval     >=1 Previous reset source is from CPU reset
  * @details    This macro get previous reset source is from CPU reset.
  * \hideinitializer
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)

/**
  * @brief      Get reset source is from LVR Reset
  * @param      None
  * @retval     0   Previous reset source is not from Low-Voltage-Reset
  * @retval     >=1 Previous reset source is from Low-Voltage-Reset
  * @details    This macro get previous reset source is from Low-Voltage-Reset.
  * \hideinitializer
  */
#define SYS_IS_LVR_RST()                (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)

/**
  * @brief      Get reset source is from Power-on Reset
  * @param      None
  * @retval     0   Previous reset source is not from Power-on Reset
  * @retval     >=1 Previous reset source is from Power-on Reset
  * @details    This macro get previous reset source is from Power-on Reset.
  * \hideinitializer
  */
#define SYS_IS_POR_RST()                (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)

/**
  * @brief      Get reset source is from reset pin reset
  * @param      None
  * @retval     0   Previous reset source is not from reset pin reset
  * @retval     >=1 Previous reset source is from reset pin reset
  * @details    This macro get previous reset source is from reset pin reset.
  * \hideinitializer
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)

/**
  * @brief      Get reset source is from system reset
  * @param      None
  * @retval     0   Previous reset source is not from system reset
  * @retval     >=1 Previous reset source is from system reset
  * @details    This macro get previous reset source is from system reset.
  * \hideinitializer
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_SYSRF_Msk)

/**
  * @brief      Get reset source is from watchdog timer or window watchdog timer reset
  * @param      None
  * @retval     0   Previous reset source is not from watchdog timer or window watchdog timer reset
  * @retval     >=1 Previous reset source is from watchdog timer or window watchdog timer reset
  * @details    This macro get previous reset source is from watchdog timer or window watchdog timer reset.
  * \hideinitializer
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)

/**
  * @brief      Disable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_POR()                (SYS->PORCTL = 0)

/**
  * @brief      Clear reset source flag
  * @param[in]  u32RstSrc is reset source. Including :
  *             - \ref SYS_RSTSTS_PORF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk
  *             - \ref SYS_RSTSTS_BODRF_Msk
  *             - \ref SYS_RSTSTS_SYSRF_Msk
  *             - \ref SYS_RSTSTS_CPURF_Msk
  *             - \ref SYS_RSTSTS_CPULKRF_Msk
  * @return     None
  * @details    This macro clear reset source flag.
  * \hideinitializer
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) ((SYS->RSTSTS) = (u32RstSrc) )


/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  * \hideinitializer
  */
__STATIC_INLINE void SYS_UnlockReg(void)
{
    do {
        SYS->REGLCTL = 0x59;
        SYS->REGLCTL = 0x16;
        SYS->REGLCTL = 0x88;
    } while (SYS->REGLCTL == 0);
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  * \hideinitializer
  */
__STATIC_INLINE void SYS_LockReg(void)
{
    SYS->REGLCTL = 0;
}


void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
uint32_t SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void SYS_DisableBOD(void);


/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif

#endif /* __NU_SYS_H__ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
