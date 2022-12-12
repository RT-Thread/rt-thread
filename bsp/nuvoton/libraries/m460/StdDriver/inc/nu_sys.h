/**************************************************************************//**
 * @file     SYS.h
 * @version  V3.0
 * @brief    M460 Series SYS Driver Header File
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

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

#define SYS_TIMEOUT_ERR    (-1L)          /*!< SYS operation abort due to timeout error \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA0_RST           ((0UL<<24) | SYS_IPRST0_PDMA0RST_Pos)       /*!< Reset PDMA0 \hideinitializer*/
#define EBI_RST             ((0UL<<24) | SYS_IPRST0_EBIRST_Pos)         /*!< Reset EBI \hideinitializer*/
#define EMAC0_RST           ((0UL<<24) | SYS_IPRST0_EMAC0RST_Pos)       /*!< Reset EMAC0 \hideinitializer */
#define SDH0_RST            ((0UL<<24) | SYS_IPRST0_SDH0RST_Pos)        /*!< Reset SDH0 \hideinitializer */
#define CRC_RST             ((0UL<<24) | SYS_IPRST0_CRCRST_Pos)         /*!< Reset CRC \hideinitializer */
#define CCAP_RST            ((0UL<<24) | SYS_IPRST0_CCAPRST_Pos)        /*!< Reset CCAP \hideinitializer */
#define HSUSBD_RST          ((0UL<<24) | SYS_IPRST0_HSUSBDRST_Pos)      /*!< Reset HSUSBD \hideinitializer */
#define HBI_RST             ((0UL<<24) | SYS_IPRST0_HBIRST_Pos)         /*!< Reset HBI \hideinitializer */
#define CRPT_RST            ((0UL<<24) | SYS_IPRST0_CRPTRST_Pos)        /*!< Reset CRPT \hideinitializer */
#define KS_RST              ((0UL<<24) | SYS_IPRST0_KSRST_Pos)          /*!< Reset KS \hideinitializer */
#define SPIM_RST            ((0UL<<24) | SYS_IPRST0_SPIMRST_Pos)        /*!< Reset SPIM \hideinitializer */
#define HSUSBH_RST          ((0UL<<24) | SYS_IPRST0_HSUSBHRST_Pos)      /*!< Reset HSUSBH \hideinitializer */
#define SDH1_RST            ((0UL<<24) | SYS_IPRST0_SDH1RST_Pos)        /*!< Reset SDH1 \hideinitializer */
#define PDMA1_RST           ((0UL<<24) | SYS_IPRST0_PDMA1RST_Pos)       /*!< Reset PDMA1 \hideinitializer */
#define CANFD0_RST          ((0UL<<24) | SYS_IPRST0_CANFD0RST_Pos)      /*!< Reset CANFD0 \hideinitializer */
#define CANFD1_RST          ((0UL<<24) | SYS_IPRST0_CANFD1RST_Pos)      /*!< Reset CANFD1 \hideinitializer */
#define CANFD2_RST          ((0UL<<24) | SYS_IPRST0_CANFD2RST_Pos)      /*!< Reset CANFD2 \hideinitializer */
#define CANFD3_RST          ((0UL<<24) | SYS_IPRST0_CANFD3RST_Pos)      /*!< Reset CANFD3 \hideinitializer */

#define GPIO_RST            ((4UL<<24) | SYS_IPRST1_GPIORST_Pos)        /*!< Reset GPIO \hideinitializer */
#define TMR0_RST            ((4UL<<24) | SYS_IPRST1_TMR0RST_Pos)        /*!< Reset TMR0 \hideinitializer */
#define TMR1_RST            ((4UL<<24) | SYS_IPRST1_TMR1RST_Pos)        /*!< Reset TMR1 \hideinitializer */
#define TMR2_RST            ((4UL<<24) | SYS_IPRST1_TMR2RST_Pos)        /*!< Reset TMR2 \hideinitializer */
#define TMR3_RST            ((4UL<<24) | SYS_IPRST1_TMR3RST_Pos)        /*!< Reset TMR3 \hideinitializer */
#define ACMP01_RST          ((4UL<<24) | SYS_IPRST1_ACMP01RST_Pos)      /*!< Reset ACMP01 \hideinitializer */
#define I2C0_RST            ((4UL<<24) | SYS_IPRST1_I2C0RST_Pos)        /*!< Reset I2C0 \hideinitializer */
#define I2C1_RST            ((4UL<<24) | SYS_IPRST1_I2C1RST_Pos)        /*!< Reset I2C1 \hideinitializer */
#define I2C2_RST            ((4UL<<24) | SYS_IPRST1_I2C2RST_Pos)        /*!< Reset I2C2 \hideinitializer */
#define I2C3_RST            ((4UL<<24) | SYS_IPRST1_I2C3RST_Pos)        /*!< Reset I2C3 \hideinitializer */
#define QSPI0_RST           ((4UL<<24) | SYS_IPRST1_QSPI0RST_Pos)       /*!< Reset QSPI0 \hideinitializer */
#define SPI0_RST            ((4UL<<24) | SYS_IPRST1_SPI0RST_Pos)        /*!< Reset SPI0 \hideinitializer */
#define SPI1_RST            ((4UL<<24) | SYS_IPRST1_SPI1RST_Pos)        /*!< Reset SPI1 \hideinitializer */
#define SPI2_RST            ((4UL<<24) | SYS_IPRST1_SPI2RST_Pos)        /*!< Reset SPI2 \hideinitializer */
#define UART0_RST           ((4UL<<24) | SYS_IPRST1_UART0RST_Pos)       /*!< Reset UART0 \hideinitializer */
#define UART1_RST           ((4UL<<24) | SYS_IPRST1_UART1RST_Pos)       /*!< Reset UART1 \hideinitializer */
#define UART2_RST           ((4UL<<24) | SYS_IPRST1_UART2RST_Pos)       /*!< Reset UART2 \hideinitializer */
#define UART3_RST           ((4UL<<24) | SYS_IPRST1_UART3RST_Pos)       /*!< Reset UART3 \hideinitializer */
#define UART4_RST           ((4UL<<24) | SYS_IPRST1_UART4RST_Pos)       /*!< Reset UART4 \hideinitializer */
#define UART5_RST           ((4UL<<24) | SYS_IPRST1_UART5RST_Pos)       /*!< Reset UART5 \hideinitializer */
#define UART6_RST           ((4UL<<24) | SYS_IPRST1_UART6RST_Pos)       /*!< Reset UART6 \hideinitializer */
#define UART7_RST           ((4UL<<24) | SYS_IPRST1_UART7RST_Pos)       /*!< Reset UART7 \hideinitializer */
#define OTG_RST             ((4UL<<24) | SYS_IPRST1_OTGRST_Pos)         /*!< Reset OTG \hideinitializer */
#define USBD_RST            ((4UL<<24) | SYS_IPRST1_USBDRST_Pos)        /*!< Reset USBD \hideinitializer */
#define EADC0_RST           ((4UL<<24) | SYS_IPRST1_EADC0RST_Pos)       /*!< Reset EADC0 \hideinitializer */
#define I2S0_RST            ((4UL<<24) | SYS_IPRST1_I2S0RST_Pos)        /*!< Reset I2S0 \hideinitializer */
#define HSOTG_RST           ((4UL<<24) | SYS_IPRST1_HSOTGRST_Pos)       /*!< Reset HSOTG \hideinitializer */
#define TRNG_RST            ((4UL<<24) | SYS_IPRST1_TRNGRST_Pos)        /*!< Reset TRNG \hideinitializer */

#define SC0_RST             ((8UL<<24) | SYS_IPRST2_SC0RST_Pos)         /*!< Reset SC0 \hideinitializer */
#define SC1_RST             ((8UL<<24) | SYS_IPRST2_SC1RST_Pos)         /*!< Reset SC1 \hideinitializer */
#define SC2_RST             ((8UL<<24) | SYS_IPRST2_SC2RST_Pos)         /*!< Reset SC2 \hideinitializer */
#define I2C4_RST            ((8UL<<24) | SYS_IPRST2_I2C4RST_Pos)        /*!< Reset I2C4 \hideinitializer */
#define QSPI1_RST           ((8UL<<24) | SYS_IPRST2_QSPI1RST_Pos)       /*!< Reset QSPI1 \hideinitializer */
#define SPI3_RST            ((8UL<<24) | SYS_IPRST2_SPI3RST_Pos)        /*!< Reset SPI3 \hideinitializer */
#define SPI4_RST            ((8UL<<24) | SYS_IPRST2_SPI4RST_Pos)        /*!< Reset SPI4 \hideinitializer */
#define USCI0_RST           ((8UL<<24) | SYS_IPRST2_USCI0RST_Pos)       /*!< Reset USCI0 \hideinitializer */
#define PSIO_RST            ((8UL<<24) | SYS_IPRST2_PSIORST_Pos)        /*!< Reset PSIO \hideinitializer */
#define DAC_RST             ((8UL<<24) | SYS_IPRST2_DACRST_Pos)         /*!< Reset DAC \hideinitializer */
#define EPWM0_RST           ((8UL<<24) | SYS_IPRST2_EPWM0RST_Pos)       /*!< Reset EPWM0 \hideinitializer */
#define EPWM1_RST           ((8UL<<24) | SYS_IPRST2_EPWM1RST_Pos)       /*!< Reset EPWM1 \hideinitializer */
#define BPWM0_RST           ((8UL<<24) | SYS_IPRST2_BPWM0RST_Pos)       /*!< Reset BPWM0 \hideinitializer */
#define BPWM1_RST           ((8UL<<24) | SYS_IPRST2_BPWM1RST_Pos)       /*!< Reset BPWM1 \hideinitializer */
#define EQEI0_RST           ((8UL<<24) | SYS_IPRST2_EQEI0RST_Pos)       /*!< Reset EQEI0 \hideinitializer */
#define EQEI1_RST           ((8UL<<24) | SYS_IPRST2_EQEI1RST_Pos)       /*!< Reset EQEI1 \hideinitializer */
#define EQEI2_RST           ((8UL<<24) | SYS_IPRST2_EQEI2RST_Pos)       /*!< Reset EQEI2 \hideinitializer */
#define EQEI3_RST           ((8UL<<24) | SYS_IPRST2_EQEI3RST_Pos)       /*!< Reset EQEI3 \hideinitializer */
#define ECAP0_RST           ((8UL<<24) | SYS_IPRST2_ECAP0RST_Pos)       /*!< Reset ECAP0 \hideinitializer */
#define ECAP1_RST           ((8UL<<24) | SYS_IPRST2_ECAP1RST_Pos)       /*!< Reset ECAP1 \hideinitializer */
#define ECAP2_RST           ((8UL<<24) | SYS_IPRST2_ECAP2RST_Pos)       /*!< Reset ECAP2 \hideinitializer */
#define ECAP3_RST           ((8UL<<24) | SYS_IPRST2_ECAP3RST_Pos)       /*!< Reset ECAP3 \hideinitializer */
#define I2S1_RST            ((8UL<<24) | SYS_IPRST2_I2S1RST_Pos)        /*!< Reset I2S1 \hideinitializer */
#define EADC1_RST           ((8UL<<24) | SYS_IPRST2_EADC1RST_Pos)       /*!< Reset EADC1 \hideinitializer */

#define KPI_RST             ((0x18UL<<24) | SYS_IPRST3_KPIRST_Pos)      /*!< Reset KPI \hideinitializer */
#define EADC2_RST           ((0x18UL<<24) | SYS_IPRST3_EADC2RST_Pos)    /*!< Reset EADC2 \hideinitializer */
#define ACMP23_RST          ((0x18UL<<24) | SYS_IPRST3_ACMP23RST_Pos)   /*!< Reset ACMP23 \hideinitializer */
#define SPI5_RST            ((0x18UL<<24) | SYS_IPRST3_SPI5RST_Pos)     /*!< Reset SPI5 \hideinitializer */
#define SPI6_RST            ((0x18UL<<24) | SYS_IPRST3_SPI6RST_Pos)     /*!< Reset SPI6 \hideinitializer */
#define SPI7_RST            ((0x18UL<<24) | SYS_IPRST3_SPI7RST_Pos)     /*!< Reset SPI7 \hideinitializer */
#define SPI8_RST            ((0x18UL<<24) | SYS_IPRST3_SPI8RST_Pos)     /*!< Reset SPI8 \hideinitializer */
#define SPI9_RST            ((0x18UL<<24) | SYS_IPRST3_SPI9RST_Pos)     /*!< Reset SPI9 \hideinitializer */
#define SPI10_RST           ((0x18UL<<24) | SYS_IPRST3_SPI10RST_Pos)    /*!< Reset SPI10 \hideinitializer */
#define UART8_RST           ((0x18UL<<24) | SYS_IPRST3_UART8RST_Pos)    /*!< Reset UART8 \hideinitializer */
#define UART9_RST           ((0x18UL<<24) | SYS_IPRST3_UART9RST_Pos)    /*!< Reset UART9 \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCTL_BOD_RST_EN           (1UL << SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Reset Enable \hideinitializer */
#define SYS_BODCTL_BOD_INTERRUPT_EN     (0UL << SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Interrupt Enable \hideinitializer */
#define SYS_BODCTL_BODVL_3_0V           (7UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 3.0V \hideinitializer */
#define SYS_BODCTL_BODVL_2_8V           (6UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.8V \hideinitializer */
#define SYS_BODCTL_BODVL_2_6V           (5UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.6V \hideinitializer */
#define SYS_BODCTL_BODVL_2_4V           (4UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.4V \hideinitializer */
#define SYS_BODCTL_BODVL_2_2V           (3UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.2V \hideinitializer */
#define SYS_BODCTL_BODVL_2_0V           (2UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.0V \hideinitializer */
#define SYS_BODCTL_BODVL_1_8V           (1UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 1.8V \hideinitializer */
#define SYS_BODCTL_BODVL_1_6V           (0UL << SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 1.6V \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  VREFCTL constant definitions. (Write-Protection Register)                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_VREFCTL_VREF_PIN        (0x0UL << SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = Vref pin \hideinitializer */
#define SYS_VREFCTL_VREF_1_6V       (0x3UL << SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 1.6V \hideinitializer */
#define SYS_VREFCTL_VREF_2_0V       (0x7UL << SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 2.0V \hideinitializer */
#define SYS_VREFCTL_VREF_2_5V       (0xBUL << SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 2.5V \hideinitializer */
#define SYS_VREFCTL_VREF_3_0V       (0xFUL << SYS_VREFCTL_VREFCTL_Pos)    /*!< Vref = 3.0V \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  USBPHY constant definitions. (Write-Protection Register)                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_USBPHY_USBROLE_STD_USBD     (0x0UL << SYS_USBPHY_USBROLE_Pos)   /*!<  Standard USB device \hideinitializer */
#define SYS_USBPHY_USBROLE_STD_USBH     (0x1UL << SYS_USBPHY_USBROLE_Pos)   /*!<  Standard USB host \hideinitializer */
#define SYS_USBPHY_USBROLE_ID_DEPH      (0x2UL << SYS_USBPHY_USBROLE_Pos)   /*!<  ID dependent device \hideinitializer */
#define SYS_USBPHY_USBROLE_ON_THE_GO    (0x3UL << SYS_USBPHY_USBROLE_Pos)   /*!<  On-The-Go device \hideinitializer */
#define SYS_USBPHY_HSUSBROLE_STD_USBD   (0x0UL << SYS_USBPHY_HSUSBROLE_Pos)   /*!<  Standard HSUSB device \hideinitializer */
#define SYS_USBPHY_HSUSBROLE_STD_USBH   (0x1UL << SYS_USBPHY_HSUSBROLE_Pos)   /*!<  Standard HSUSB host \hideinitializer */
#define SYS_USBPHY_HSUSBROLE_ID_DEPH    (0x2UL << SYS_USBPHY_HSUSBROLE_Pos)   /*!<  ID dependent device \hideinitializer */
#define SYS_USBPHY_HSUSBROLE_ON_THE_GO  (0x3UL << SYS_USBPHY_HSUSBROLE_Pos)   /*!<  On-The-Go device \hideinitializer */


/*---------------------------------------------------------------------------------------------------------*/
/*  PLCTL constant definitions. (Write-Protection Register)                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_PLCTL_PLSEL_PL0     (0x0UL<<SYS_PLCTL_PLSEL_Pos)   /*!< Set power level to power level 0. Supports system clock up to 200MHz. \hideinitializer */
#define SYS_PLCTL_PLSEL_PL1     (0x1UL<<SYS_PLCTL_PLSEL_Pos)   /*!< Set power level to power level 1. Supports system clock up to 180MHz. \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  PLSTS constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_PLSTS_PLSTATUS_PL0  (0x0UL<<SYS_PLSTS_PLSTATUS_Pos) /*!< Power level is power level 0. Supports system clock up to 200MHz. \hideinitializer */
#define SYS_PLSTS_PLSTATUS_PL1  (0x1UL<<SYS_PLSTS_PLSTATUS_Pos) /*!< Power level is power level 1. Supports system clock up to 180MHz. \hideinitializer */



/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to set PA.0 as SC0_CLK in initial function,
           user can issue following command to achieve it.

           SYS->GPA_MFP0  = (SYS->GPA_MFP0 & (~SYS_GPA_MFP0_PA0MFP_Msk) ) | SYS_GPA_MFP0_PA0_MFP_SC0_CLK;
*/


/* PA.0 MFP */
#define SYS_GPA_MFP0_PA0MFP_GPIO         (0x00UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for GPIO        */
#define SYS_GPA_MFP0_PA0MFP_SPIM_MOSI    (0x02UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for SPIM_MOSI   */
#define SYS_GPA_MFP0_PA0MFP_QSPI0_MOSI0  (0x03UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for QSPI0_MOSI0 */
#define SYS_GPA_MFP0_PA0MFP_SPI0_MOSI    (0x04UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for SPI0_MOSI   */
#define SYS_GPA_MFP0_PA0MFP_SD1_DAT0     (0x05UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for SD1_DAT0    */
#define SYS_GPA_MFP0_PA0MFP_SC0_CLK      (0x06UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for SC0_CLK     */
#define SYS_GPA_MFP0_PA0MFP_UART0_RXD    (0x07UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for UART0_RXD   */
#define SYS_GPA_MFP0_PA0MFP_UART1_nRTS   (0x08UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for UART1_nRTS  */
#define SYS_GPA_MFP0_PA0MFP_I2C2_SDA     (0x09UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for I2C2_SDA    */
#define SYS_GPA_MFP0_PA0MFP_CCAP_DATA6   (0x0aUL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for CCAP_DATA6  */
#define SYS_GPA_MFP0_PA0MFP_BPWM0_CH0    (0x0cUL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for BPWM0_CH0   */
#define SYS_GPA_MFP0_PA0MFP_EPWM0_CH5    (0x0dUL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for EPWM0_CH5   */
#define SYS_GPA_MFP0_PA0MFP_EQEI3_B      (0x0eUL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for EQEI3_B     */
#define SYS_GPA_MFP0_PA0MFP_DAC0_ST      (0x0fUL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for DAC0_ST     */
#define SYS_GPA_MFP0_PA0MFP_PSIO0_CH7    (0x11UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for PSIO0_CH7   */
#define SYS_GPA_MFP0_PA0MFP_BMC19        (0x14UL<<SYS_GPA_MFP0_PA0MFP_Pos) /*!< GPA_MFP0 PA0 setting for BMC19       */

/* PA.1 MFP */
#define SYS_GPA_MFP0_PA1MFP_GPIO         (0x00UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for GPIO        */
#define SYS_GPA_MFP0_PA1MFP_SPIM_MISO    (0x02UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for SPIM_MISO   */
#define SYS_GPA_MFP0_PA1MFP_QSPI0_MISO0  (0x03UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for QSPI0_MISO0 */
#define SYS_GPA_MFP0_PA1MFP_SPI0_MISO    (0x04UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for SPI0_MISO   */
#define SYS_GPA_MFP0_PA1MFP_SD1_DAT1     (0x05UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for SD1_DAT1    */
#define SYS_GPA_MFP0_PA1MFP_SC0_DAT      (0x06UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for SC0_DAT     */
#define SYS_GPA_MFP0_PA1MFP_UART0_TXD    (0x07UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for UART0_TXD   */
#define SYS_GPA_MFP0_PA1MFP_UART1_nCTS   (0x08UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for UART1_nCTS  */
#define SYS_GPA_MFP0_PA1MFP_I2C2_SCL     (0x09UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for I2C2_SCL    */
#define SYS_GPA_MFP0_PA1MFP_CCAP_DATA7   (0x0aUL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for CCAP_DATA7  */
#define SYS_GPA_MFP0_PA1MFP_BPWM0_CH1    (0x0cUL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for BPWM0_CH1   */
#define SYS_GPA_MFP0_PA1MFP_EPWM0_CH4    (0x0dUL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for EPWM0_CH4   */
#define SYS_GPA_MFP0_PA1MFP_EQEI3_A      (0x0eUL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for EQEI3_A     */
#define SYS_GPA_MFP0_PA1MFP_DAC1_ST      (0x0fUL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for DAC1_ST     */
#define SYS_GPA_MFP0_PA1MFP_PSIO0_CH6    (0x11UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for PSIO0_CH6   */
#define SYS_GPA_MFP0_PA1MFP_BMC18        (0x14UL<<SYS_GPA_MFP0_PA1MFP_Pos) /*!< GPA_MFP0 PA1 setting for BMC18       */

/* PA.2 MFP */
#define SYS_GPA_MFP0_PA2MFP_GPIO         (0x00UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for GPIO        */
#define SYS_GPA_MFP0_PA2MFP_SPIM_CLK     (0x02UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for SPIM_CLK    */
#define SYS_GPA_MFP0_PA2MFP_QSPI0_CLK    (0x03UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for QSPI0_CLK   */
#define SYS_GPA_MFP0_PA2MFP_SPI0_CLK     (0x04UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for SPI0_CLK    */
#define SYS_GPA_MFP0_PA2MFP_SD1_DAT2     (0x05UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for SD1_DAT2    */
#define SYS_GPA_MFP0_PA2MFP_SC0_RST      (0x06UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for SC0_RST     */
#define SYS_GPA_MFP0_PA2MFP_UART4_RXD    (0x07UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for UART4_RXD   */
#define SYS_GPA_MFP0_PA2MFP_UART1_RXD    (0x08UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for UART1_RXD   */
#define SYS_GPA_MFP0_PA2MFP_I2C1_SDA     (0x09UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for I2C1_SDA    */
#define SYS_GPA_MFP0_PA2MFP_I2C0_SMBSUS  (0x0aUL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for I2C0_SMBSUS */
#define SYS_GPA_MFP0_PA2MFP_BPWM0_CH2    (0x0cUL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for BPWM0_CH2   */
#define SYS_GPA_MFP0_PA2MFP_EPWM0_CH3    (0x0dUL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for EPWM0_CH3   */
#define SYS_GPA_MFP0_PA2MFP_EQEI3_INDEX  (0x0eUL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for EQEI3_INDEX */
#define SYS_GPA_MFP0_PA2MFP_PSIO0_CH5    (0x11UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for PSIO0_CH5   */
#define SYS_GPA_MFP0_PA2MFP_BMC17        (0x14UL<<SYS_GPA_MFP0_PA2MFP_Pos) /*!< GPA_MFP0 PA2 setting for BMC17       */

/* PA.3 MFP */
#define SYS_GPA_MFP0_PA3MFP_GPIO         (0x00UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for GPIO        */
#define SYS_GPA_MFP0_PA3MFP_SPIM_SS      (0x02UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for SPIM_SS     */
#define SYS_GPA_MFP0_PA3MFP_QSPI0_SS     (0x03UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for QSPI0_SS    */
#define SYS_GPA_MFP0_PA3MFP_SPI0_SS      (0x04UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for SPI0_SS     */
#define SYS_GPA_MFP0_PA3MFP_SD1_DAT3     (0x05UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for SD1_DAT3    */
#define SYS_GPA_MFP0_PA3MFP_SC0_PWR      (0x06UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for SC0_PWR     */
#define SYS_GPA_MFP0_PA3MFP_UART4_TXD    (0x07UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for UART4_TXD   */
#define SYS_GPA_MFP0_PA3MFP_UART1_TXD    (0x08UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for UART1_TXD   */
#define SYS_GPA_MFP0_PA3MFP_I2C1_SCL     (0x09UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for I2C1_SCL    */
#define SYS_GPA_MFP0_PA3MFP_I2C0_SMBAL   (0x0aUL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for I2C0_SMBAL  */
#define SYS_GPA_MFP0_PA3MFP_BPWM0_CH3    (0x0cUL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for BPWM0_CH3   */
#define SYS_GPA_MFP0_PA3MFP_EPWM0_CH2    (0x0dUL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for EPWM0_CH2   */
#define SYS_GPA_MFP0_PA3MFP_EQEI0_B      (0x0eUL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for EQEI0_B     */
#define SYS_GPA_MFP0_PA3MFP_EPWM1_BRAKE1 (0x0fUL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for EPWM1_BRAKE1*/
#define SYS_GPA_MFP0_PA3MFP_PSIO0_CH4    (0x11UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for PSIO0_CH4   */
#define SYS_GPA_MFP0_PA3MFP_BMC16        (0x14UL<<SYS_GPA_MFP0_PA3MFP_Pos) /*!< GPA_MFP0 PA3 setting for BMC16       */

/* PA.4 MFP */
#define SYS_GPA_MFP1_PA4MFP_GPIO         (0x00UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for GPIO        */
#define SYS_GPA_MFP1_PA4MFP_SPIM_D3      (0x02UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for SPIM_D3     */
#define SYS_GPA_MFP1_PA4MFP_QSPI0_MOSI1  (0x03UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for QSPI0_MOSI1 */
#define SYS_GPA_MFP1_PA4MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for SPI0_I2SMCLK*/
#define SYS_GPA_MFP1_PA4MFP_SD1_CLK      (0x05UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for SD1_CLK     */
#define SYS_GPA_MFP1_PA4MFP_SC0_nCD      (0x06UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for SC0_nCD     */
#define SYS_GPA_MFP1_PA4MFP_UART0_nRTS   (0x07UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for UART0_nRTS  */
#define SYS_GPA_MFP1_PA4MFP_UART5_RXD    (0x08UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for UART5_RXD   */
#define SYS_GPA_MFP1_PA4MFP_I2C0_SDA     (0x09UL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for I2C0_SDA    */
#define SYS_GPA_MFP1_PA4MFP_CAN0_RXD     (0x0aUL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for CAN0_RXD    */
#define SYS_GPA_MFP1_PA4MFP_UART0_RXD    (0x0bUL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for UART0_RXD   */
#define SYS_GPA_MFP1_PA4MFP_BPWM0_CH4    (0x0cUL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for BPWM0_CH4   */
#define SYS_GPA_MFP1_PA4MFP_EPWM0_CH1    (0x0dUL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for EPWM0_CH1   */
#define SYS_GPA_MFP1_PA4MFP_EQEI0_A      (0x0eUL<<SYS_GPA_MFP1_PA4MFP_Pos) /*!< GPA_MFP1 PA4 setting for EQEI0_A     */

/* PA.5 MFP */
#define SYS_GPA_MFP1_PA5MFP_GPIO         (0x00UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for GPIO        */
#define SYS_GPA_MFP1_PA5MFP_SPIM_D2      (0x02UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for SPIM_D2     */
#define SYS_GPA_MFP1_PA5MFP_QSPI0_MISO1  (0x03UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for QSPI0_MISO1 */
#define SYS_GPA_MFP1_PA5MFP_SPI1_I2SMCLK (0x04UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for SPI1_I2SMCLK*/
#define SYS_GPA_MFP1_PA5MFP_SD1_CMD      (0x05UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for SD1_CMD     */
#define SYS_GPA_MFP1_PA5MFP_SC2_nCD      (0x06UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for SC2_nCD     */
#define SYS_GPA_MFP1_PA5MFP_UART0_nCTS   (0x07UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for UART0_nCTS  */
#define SYS_GPA_MFP1_PA5MFP_UART5_TXD    (0x08UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for UART5_TXD   */
#define SYS_GPA_MFP1_PA5MFP_I2C0_SCL     (0x09UL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for I2C0_SCL    */
#define SYS_GPA_MFP1_PA5MFP_CAN0_TXD     (0x0aUL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for CAN0_TXD    */
#define SYS_GPA_MFP1_PA5MFP_UART0_TXD    (0x0bUL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for UART0_TXD   */
#define SYS_GPA_MFP1_PA5MFP_BPWM0_CH5    (0x0cUL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for BPWM0_CH5   */
#define SYS_GPA_MFP1_PA5MFP_EPWM0_CH0    (0x0dUL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for EPWM0_CH0   */
#define SYS_GPA_MFP1_PA5MFP_EQEI0_INDEX  (0x0eUL<<SYS_GPA_MFP1_PA5MFP_Pos) /*!< GPA_MFP1 PA5 setting for EQEI0_INDEX */

/* PA.6 MFP */
#define SYS_GPA_MFP1_PA6MFP_GPIO         (0x00UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for GPIO        */
#define SYS_GPA_MFP1_PA6MFP_EBI_AD6      (0x02UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for EBI_AD6     */
#define SYS_GPA_MFP1_PA6MFP_EMAC0_RMII_RXERR (0x03UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for EMAC0_RMII_RXERR*/
#define SYS_GPA_MFP1_PA6MFP_SPI1_SS      (0x04UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for SPI1_SS     */
#define SYS_GPA_MFP1_PA6MFP_SD1_nCD      (0x05UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for SD1_nCD     */
#define SYS_GPA_MFP1_PA6MFP_SC2_CLK      (0x06UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for SC2_CLK     */
#define SYS_GPA_MFP1_PA6MFP_UART0_RXD    (0x07UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for UART0_RXD   */
#define SYS_GPA_MFP1_PA6MFP_I2C1_SDA     (0x08UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for I2C1_SDA    */
#define SYS_GPA_MFP1_PA6MFP_QSPI1_MOSI1  (0x09UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for QSPI1_MOSI1 */
#define SYS_GPA_MFP1_PA6MFP_EPWM1_CH5    (0x0bUL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for EPWM1_CH5   */
#define SYS_GPA_MFP1_PA6MFP_BPWM1_CH3    (0x0cUL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for BPWM1_CH3   */
#define SYS_GPA_MFP1_PA6MFP_ACMP1_WLAT   (0x0dUL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for ACMP1_WLAT  */
#define SYS_GPA_MFP1_PA6MFP_TM3          (0x0eUL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for TM3         */
#define SYS_GPA_MFP1_PA6MFP_INT0         (0x0fUL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for INT0        */
#define SYS_GPA_MFP1_PA6MFP_SPI5_CLK     (0x11UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for SPI5_CLK    */
#define SYS_GPA_MFP1_PA6MFP_KPI_COL0     (0x12UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for KPI_COL0    */
#define SYS_GPA_MFP1_PA6MFP_SPI6_CLK     (0x13UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for SPI6_CLK    */
#define SYS_GPA_MFP1_PA6MFP_BMC15        (0x14UL<<SYS_GPA_MFP1_PA6MFP_Pos) /*!< GPA_MFP1 PA6 setting for BMC15       */

/* PA.7 MFP */
#define SYS_GPA_MFP1_PA7MFP_GPIO         (0x00UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for GPIO        */
#define SYS_GPA_MFP1_PA7MFP_EBI_AD7      (0x02UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for EBI_AD7     */
#define SYS_GPA_MFP1_PA7MFP_EMAC0_RMII_CRSDV (0x03UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for EMAC0_RMII_CRSDV*/
#define SYS_GPA_MFP1_PA7MFP_SPI1_CLK     (0x04UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for SPI1_CLK    */
#define SYS_GPA_MFP1_PA7MFP_SC2_DAT      (0x06UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for SC2_DAT     */
#define SYS_GPA_MFP1_PA7MFP_UART0_TXD    (0x07UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for UART0_TXD   */
#define SYS_GPA_MFP1_PA7MFP_I2C1_SCL     (0x08UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for I2C1_SCL    */
#define SYS_GPA_MFP1_PA7MFP_QSPI1_MISO1  (0x09UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for QSPI1_MISO1 */
#define SYS_GPA_MFP1_PA7MFP_EPWM1_CH4    (0x0bUL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for EPWM1_CH4   */
#define SYS_GPA_MFP1_PA7MFP_BPWM1_CH2    (0x0cUL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for BPWM1_CH2   */
#define SYS_GPA_MFP1_PA7MFP_ACMP0_WLAT   (0x0dUL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for ACMP0_WLAT  */
#define SYS_GPA_MFP1_PA7MFP_TM2          (0x0eUL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for TM2         */
#define SYS_GPA_MFP1_PA7MFP_INT1         (0x0fUL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for INT1        */
#define SYS_GPA_MFP1_PA7MFP_SPI5_SS      (0x11UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for SPI5_SS     */
#define SYS_GPA_MFP1_PA7MFP_KPI_COL1     (0x12UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for KPI_COL1    */
#define SYS_GPA_MFP1_PA7MFP_SPI6_SS      (0x13UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for SPI6_SS     */
#define SYS_GPA_MFP1_PA7MFP_BMC14        (0x14UL<<SYS_GPA_MFP1_PA7MFP_Pos) /*!< GPA_MFP1 PA7 setting for BMC14       */

/* PA.8 MFP */
#define SYS_GPA_MFP2_PA8MFP_GPIO         (0x00UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for GPIO        */
#define SYS_GPA_MFP2_PA8MFP_EADC1_CH4    (0x01UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for EADC1_CH4   */
#define SYS_GPA_MFP2_PA8MFP_EADC2_CH4    (0x01UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for EADC2_CH4   */
#define SYS_GPA_MFP2_PA8MFP_EBI_ALE      (0x02UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for EBI_ALE     */
#define SYS_GPA_MFP2_PA8MFP_SC2_CLK      (0x03UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for SC2_CLK     */
#define SYS_GPA_MFP2_PA8MFP_SPI2_MOSI    (0x04UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for SPI2_MOSI   */
#define SYS_GPA_MFP2_PA8MFP_SD1_DAT0     (0x05UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for SD1_DAT0    */
#define SYS_GPA_MFP2_PA8MFP_USCI0_CTL1   (0x06UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for USCI0_CTL1  */
#define SYS_GPA_MFP2_PA8MFP_UART1_RXD    (0x07UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for UART1_RXD   */
#define SYS_GPA_MFP2_PA8MFP_UART7_RXD    (0x08UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for UART7_RXD   */
#define SYS_GPA_MFP2_PA8MFP_BPWM0_CH3    (0x09UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for BPWM0_CH3   */
#define SYS_GPA_MFP2_PA8MFP_EQEI1_B      (0x0aUL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for EQEI1_B     */
#define SYS_GPA_MFP2_PA8MFP_ECAP0_IC2    (0x0bUL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for ECAP0_IC2   */
#define SYS_GPA_MFP2_PA8MFP_I2S1_DO      (0x0cUL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for I2S1_DO     */
#define SYS_GPA_MFP2_PA8MFP_TM3_EXT      (0x0dUL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for TM3_EXT     */
#define SYS_GPA_MFP2_PA8MFP_INT4         (0x0fUL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for INT4        */
#define SYS_GPA_MFP2_PA8MFP_BMC9         (0x14UL<<SYS_GPA_MFP2_PA8MFP_Pos) /*!< GPA_MFP2 PA8 setting for BMC9        */

/* PA.9 MFP */
#define SYS_GPA_MFP2_PA9MFP_GPIO         (0x00UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for GPIO        */
#define SYS_GPA_MFP2_PA9MFP_EADC1_CH5    (0x01UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for EADC1_CH5   */
#define SYS_GPA_MFP2_PA9MFP_EADC2_CH5    (0x01UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for EADC2_CH5   */
#define SYS_GPA_MFP2_PA9MFP_EBI_MCLK     (0x02UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for EBI_MCLK    */
#define SYS_GPA_MFP2_PA9MFP_SC2_DAT      (0x03UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for SC2_DAT     */
#define SYS_GPA_MFP2_PA9MFP_SPI2_MISO    (0x04UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for SPI2_MISO   */
#define SYS_GPA_MFP2_PA9MFP_SD1_DAT1     (0x05UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for SD1_DAT1    */
#define SYS_GPA_MFP2_PA9MFP_USCI0_DAT1   (0x06UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for USCI0_DAT1  */
#define SYS_GPA_MFP2_PA9MFP_UART1_TXD    (0x07UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for UART1_TXD   */
#define SYS_GPA_MFP2_PA9MFP_UART7_TXD    (0x08UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for UART7_TXD   */
#define SYS_GPA_MFP2_PA9MFP_BPWM0_CH2    (0x09UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for BPWM0_CH2   */
#define SYS_GPA_MFP2_PA9MFP_EQEI1_A      (0x0aUL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for EQEI1_A     */
#define SYS_GPA_MFP2_PA9MFP_ECAP0_IC1    (0x0bUL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for ECAP0_IC1   */
#define SYS_GPA_MFP2_PA9MFP_I2S1_DI      (0x0cUL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for I2S1_DI     */
#define SYS_GPA_MFP2_PA9MFP_TM2_EXT      (0x0dUL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for TM2_EXT     */
#define SYS_GPA_MFP2_PA9MFP_SWDH_DAT     (0x0fUL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for SWDH_DAT    */
#define SYS_GPA_MFP2_PA9MFP_BMC8         (0x14UL<<SYS_GPA_MFP2_PA9MFP_Pos) /*!< GPA_MFP2 PA9 setting for BMC8        */

/* PA.10 MFP */
#define SYS_GPA_MFP2_PA10MFP_GPIO        (0x00UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for GPIO       */
#define SYS_GPA_MFP2_PA10MFP_EADC1_CH6   (0x01UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for EADC1_CH6  */
#define SYS_GPA_MFP2_PA10MFP_EADC2_CH6   (0x01UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for EADC2_CH6  */
#define SYS_GPA_MFP2_PA10MFP_ACMP1_P0    (0x01UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for ACMP1_P0   */
#define SYS_GPA_MFP2_PA10MFP_EBI_nWR     (0x02UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for EBI_nWR    */
#define SYS_GPA_MFP2_PA10MFP_SC2_RST     (0x03UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for SC2_RST    */
#define SYS_GPA_MFP2_PA10MFP_SPI2_CLK    (0x04UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for SPI2_CLK   */
#define SYS_GPA_MFP2_PA10MFP_SD1_DAT2    (0x05UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for SD1_DAT2   */
#define SYS_GPA_MFP2_PA10MFP_USCI0_DAT0  (0x06UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for USCI0_DAT0 */
#define SYS_GPA_MFP2_PA10MFP_I2C2_SDA    (0x07UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for I2C2_SDA   */
#define SYS_GPA_MFP2_PA10MFP_UART6_RXD   (0x08UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for UART6_RXD  */
#define SYS_GPA_MFP2_PA10MFP_BPWM0_CH1   (0x09UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for BPWM0_CH1  */
#define SYS_GPA_MFP2_PA10MFP_EQEI1_INDEX (0x0aUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for EQEI1_INDEX */
#define SYS_GPA_MFP2_PA10MFP_ECAP0_IC0   (0x0bUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for ECAP0_IC0  */
#define SYS_GPA_MFP2_PA10MFP_I2S1_MCLK   (0x0cUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for I2S1_MCLK  */
#define SYS_GPA_MFP2_PA10MFP_TM1_EXT     (0x0dUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for TM1_EXT    */
#define SYS_GPA_MFP2_PA10MFP_DAC0_ST     (0x0eUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for DAC0_ST    */
#define SYS_GPA_MFP2_PA10MFP_SWDH_CLK    (0x0fUL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for SWDH_CLK   */
#define SYS_GPA_MFP2_PA10MFP_KPI_ROW5    (0x12UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for KPI_ROW5   */
#define SYS_GPA_MFP2_PA10MFP_BMC7        (0x14UL<<SYS_GPA_MFP2_PA10MFP_Pos)/*!< GPA_MFP2 PA10 setting for BMC7       */

/* PA.11 MFP */
#define SYS_GPA_MFP2_PA11MFP_GPIO        (0x00UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for GPIO       */
#define SYS_GPA_MFP2_PA11MFP_EADC1_CH7   (0x01UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for EADC1_CH7  */
#define SYS_GPA_MFP2_PA11MFP_EADC2_CH7   (0x01UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for EADC2_CH7  */
#define SYS_GPA_MFP2_PA11MFP_ACMP0_P0    (0x01UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for ACMP0_P0   */
#define SYS_GPA_MFP2_PA11MFP_EBI_nRD     (0x02UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for EBI_nRD    */
#define SYS_GPA_MFP2_PA11MFP_SC2_PWR     (0x03UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for SC2_PWR    */
#define SYS_GPA_MFP2_PA11MFP_SPI2_SS     (0x04UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for SPI2_SS    */
#define SYS_GPA_MFP2_PA11MFP_SD1_DAT3    (0x05UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for SD1_DAT3   */
#define SYS_GPA_MFP2_PA11MFP_USCI0_CLK   (0x06UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for USCI0_CLK  */
#define SYS_GPA_MFP2_PA11MFP_I2C2_SCL    (0x07UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for I2C2_SCL   */
#define SYS_GPA_MFP2_PA11MFP_UART6_TXD   (0x08UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for UART6_TXD  */
#define SYS_GPA_MFP2_PA11MFP_BPWM0_CH0   (0x09UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for BPWM0_CH0  */
#define SYS_GPA_MFP2_PA11MFP_EPWM0_SYNC_OUT (0x0aUL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for EPWM0_SYNC_OUT*/
#define SYS_GPA_MFP2_PA11MFP_I2S1_BCLK   (0x0cUL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for I2S1_BCLK  */
#define SYS_GPA_MFP2_PA11MFP_TM0_EXT     (0x0dUL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for TM0_EXT    */
#define SYS_GPA_MFP2_PA11MFP_DAC1_ST     (0x0eUL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for DAC1_ST    */
#define SYS_GPA_MFP2_PA11MFP_KPI_ROW4    (0x12UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for KPI_ROW4   */
#define SYS_GPA_MFP2_PA11MFP_BMC6        (0x14UL<<SYS_GPA_MFP2_PA11MFP_Pos)/*!< GPA_MFP2 PA11 setting for BMC6       */

/* PA.12 MFP */
#define SYS_GPA_MFP3_PA12MFP_GPIO        (0x00UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for GPIO       */
#define SYS_GPA_MFP3_PA12MFP_I2S0_BCLK   (0x02UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for I2S0_BCLK  */
#define SYS_GPA_MFP3_PA12MFP_UART4_TXD   (0x03UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for UART4_TXD  */
#define SYS_GPA_MFP3_PA12MFP_I2C1_SCL    (0x04UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for I2C1_SCL   */
#define SYS_GPA_MFP3_PA12MFP_SPI2_SS     (0x05UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for SPI2_SS    */
#define SYS_GPA_MFP3_PA12MFP_CAN0_TXD    (0x06UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for CAN0_TXD   */
#define SYS_GPA_MFP3_PA12MFP_SC2_PWR     (0x07UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for SC2_PWR    */
#define SYS_GPA_MFP3_PA12MFP_SD1_nCD     (0x08UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for SD1_nCD    */
#define SYS_GPA_MFP3_PA12MFP_SPI0_SS     (0x09UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for SPI0_SS    */
#define SYS_GPA_MFP3_PA12MFP_QSPI1_MISO0 (0x0aUL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for QSPI1_MISO0*/
#define SYS_GPA_MFP3_PA12MFP_BPWM1_CH2   (0x0bUL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for BPWM1_CH2  */
#define SYS_GPA_MFP3_PA12MFP_EQEI1_INDEX (0x0cUL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for EQEI1_INDEX */
#define SYS_GPA_MFP3_PA12MFP_ECAP3_IC0   (0x0dUL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for ECAP3_IC0  */
#define SYS_GPA_MFP3_PA12MFP_USB_VBUS    (0x0eUL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for USB_VBUS   */
#define SYS_GPA_MFP3_PA12MFP_PSIO0_CH4   (0x11UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for PSIO0_CH4  */
#define SYS_GPA_MFP3_PA12MFP_SPI10_SS    (0x13UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for SPI10_SS   */
#define SYS_GPA_MFP3_PA12MFP_BMC12       (0x14UL<<SYS_GPA_MFP3_PA12MFP_Pos)/*!< GPA_MFP3 PA12 setting for BMC12      */

/* PA.13 MFP */
#define SYS_GPA_MFP3_PA13MFP_GPIO        (0x00UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for GPIO       */
#define SYS_GPA_MFP3_PA13MFP_I2S0_MCLK   (0x02UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for I2S0_MCLK  */
#define SYS_GPA_MFP3_PA13MFP_UART4_RXD   (0x03UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for UART4_RXD  */
#define SYS_GPA_MFP3_PA13MFP_I2C1_SDA    (0x04UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for I2C1_SDA   */
#define SYS_GPA_MFP3_PA13MFP_SPI2_CLK    (0x05UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for SPI2_CLK   */
#define SYS_GPA_MFP3_PA13MFP_CAN0_RXD    (0x06UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for CAN0_RXD   */
#define SYS_GPA_MFP3_PA13MFP_SC2_RST     (0x07UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for SC2_RST    */
#define SYS_GPA_MFP3_PA13MFP_SPI0_CLK    (0x09UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for SPI0_CLK   */
#define SYS_GPA_MFP3_PA13MFP_QSPI1_MOSI0 (0x0aUL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for QSPI1_MOSI0*/
#define SYS_GPA_MFP3_PA13MFP_BPWM1_CH3   (0x0bUL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for BPWM1_CH3  */
#define SYS_GPA_MFP3_PA13MFP_EQEI1_A     (0x0cUL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for EQEI1_A    */
#define SYS_GPA_MFP3_PA13MFP_ECAP3_IC1   (0x0dUL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for ECAP3_IC1  */
#define SYS_GPA_MFP3_PA13MFP_USB_D_N     (0x0eUL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for USB_D-     */
#define SYS_GPA_MFP3_PA13MFP_PSIO0_CH5   (0x11UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for PSIO0_CH5  */
#define SYS_GPA_MFP3_PA13MFP_SPI10_CLK   (0x13UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for SPI10_CLK  */
#define SYS_GPA_MFP3_PA13MFP_BMC13       (0x14UL<<SYS_GPA_MFP3_PA13MFP_Pos)/*!< GPA_MFP3 PA13 setting for BMC13      */

/* PA.14 MFP */
#define SYS_GPA_MFP3_PA14MFP_GPIO        (0x00UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for GPIO       */
#define SYS_GPA_MFP3_PA14MFP_I2S0_DI     (0x02UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for I2S0_DI    */
#define SYS_GPA_MFP3_PA14MFP_UART0_TXD   (0x03UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for UART0_TXD  */
#define SYS_GPA_MFP3_PA14MFP_EBI_AD5     (0x04UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for EBI_AD5    */
#define SYS_GPA_MFP3_PA14MFP_SPI2_MISO   (0x05UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for SPI2_MISO  */
#define SYS_GPA_MFP3_PA14MFP_I2C2_SCL    (0x06UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for I2C2_SCL   */
#define SYS_GPA_MFP3_PA14MFP_SC2_DAT     (0x07UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for SC2_DAT    */
#define SYS_GPA_MFP3_PA14MFP_SPI0_MISO   (0x09UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for SPI0_MISO  */
#define SYS_GPA_MFP3_PA14MFP_BPWM1_CH4   (0x0bUL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for BPWM1_CH4  */
#define SYS_GPA_MFP3_PA14MFP_EQEI1_B     (0x0cUL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for EQEI1_B    */
#define SYS_GPA_MFP3_PA14MFP_ECAP3_IC2   (0x0dUL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for ECAP3_IC2  */
#define SYS_GPA_MFP3_PA14MFP_USB_D_P     (0x0eUL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for USB_D+     */
#define SYS_GPA_MFP3_PA14MFP_I2C0_SCL    (0x10UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for I2C0_SCL   */
#define SYS_GPA_MFP3_PA14MFP_PSIO0_CH6   (0x11UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for PSIO0_CH6  */
#define SYS_GPA_MFP3_PA14MFP_SPI10_MISO  (0x13UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for SPI10_MISO */
#define SYS_GPA_MFP3_PA14MFP_BMC14       (0x14UL<<SYS_GPA_MFP3_PA14MFP_Pos)/*!< GPA_MFP3 PA14 setting for BMC14      */

/* PA.15 MFP */
#define SYS_GPA_MFP3_PA15MFP_GPIO        (0x00UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for GPIO       */
#define SYS_GPA_MFP3_PA15MFP_I2S0_DO     (0x02UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for I2S0_DO    */
#define SYS_GPA_MFP3_PA15MFP_UART0_RXD   (0x03UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for UART0_RXD  */
#define SYS_GPA_MFP3_PA15MFP_SPIM_MOSI   (0x04UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for SPIM_MOSI  */
#define SYS_GPA_MFP3_PA15MFP_SPI2_MOSI   (0x05UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for SPI2_MOSI  */
#define SYS_GPA_MFP3_PA15MFP_I2C2_SDA    (0x06UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for I2C2_SDA   */
#define SYS_GPA_MFP3_PA15MFP_SC2_CLK     (0x07UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for SC2_CLK    */
#define SYS_GPA_MFP3_PA15MFP_SPI0_MOSI   (0x09UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for SPI0_MOSI  */
#define SYS_GPA_MFP3_PA15MFP_BPWM1_CH5   (0x0bUL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for BPWM1_CH5  */
#define SYS_GPA_MFP3_PA15MFP_EPWM0_SYNC_IN (0x0cUL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for EPWM0_SYNC_IN*/
#define SYS_GPA_MFP3_PA15MFP_EQEI3_INDEX (0x0dUL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for EQEI3_INDEX */
#define SYS_GPA_MFP3_PA15MFP_USB_OTG_ID  (0x0eUL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for USB_OTG_ID */
#define SYS_GPA_MFP3_PA15MFP_I2C0_SDA    (0x10UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for I2C0_SDA   */
#define SYS_GPA_MFP3_PA15MFP_PSIO0_CH7   (0x11UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for PSIO0_CH7  */
#define SYS_GPA_MFP3_PA15MFP_SPI10_MOSI  (0x13UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for SPI10_MOSI */
#define SYS_GPA_MFP3_PA15MFP_BMC15       (0x14UL<<SYS_GPA_MFP3_PA15MFP_Pos)/*!< GPA_MFP3 PA15 setting for BMC15      */

/* PB.0 MFP */
#define SYS_GPB_MFP0_PB0MFP_GPIO         (0x00UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for GPIO        */
#define SYS_GPB_MFP0_PB0MFP_EADC0_CH0    (0x01UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EADC0_CH0   */
#define SYS_GPB_MFP0_PB0MFP_EADC1_CH8    (0x01UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EADC1_CH8   */
#define SYS_GPB_MFP0_PB0MFP_EADC2_CH8    (0x01UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EADC2_CH8   */
#define SYS_GPB_MFP0_PB0MFP_ACMP3_N      (0x01UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for ACMP3_N     */
#define SYS_GPB_MFP0_PB0MFP_EBI_ADR9     (0x02UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EBI_ADR9    */
#define SYS_GPB_MFP0_PB0MFP_SD0_CMD      (0x03UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for SD0_CMD     */
#define SYS_GPB_MFP0_PB0MFP_SPI2_I2SMCLK (0x04UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for SPI2_I2SMCLK*/
#define SYS_GPB_MFP0_PB0MFP_USCI0_CTL0   (0x06UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for USCI0_CTL0  */
#define SYS_GPB_MFP0_PB0MFP_UART2_RXD    (0x07UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for UART2_RXD   */
#define SYS_GPB_MFP0_PB0MFP_SPI0_I2SMCLK (0x08UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for SPI0_I2SMCLK*/
#define SYS_GPB_MFP0_PB0MFP_I2C1_SDA     (0x09UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for I2C1_SDA    */
#define SYS_GPB_MFP0_PB0MFP_I2S1_LRCK    (0x0aUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for I2S1_LRCK   */
#define SYS_GPB_MFP0_PB0MFP_EPWM0_CH5    (0x0bUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EPWM0_CH5   */
#define SYS_GPB_MFP0_PB0MFP_EPWM1_CH5    (0x0cUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EPWM1_CH5   */
#define SYS_GPB_MFP0_PB0MFP_EPWM0_BRAKE1 (0x0dUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for EPWM0_BRAKE1*/
#define SYS_GPB_MFP0_PB0MFP_ACMP3_O      (0x0eUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for ACMP3_O     */
#define SYS_GPB_MFP0_PB0MFP_QSPI0_MOSI1  (0x0fUL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for QSPI0_MOSI1 */
#define SYS_GPB_MFP0_PB0MFP_KPI_ROW3     (0x12UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for KPI_ROW3    */
#define SYS_GPB_MFP0_PB0MFP_SPI4_MOSI    (0x13UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for SPI4_MOSI   */
#define SYS_GPB_MFP0_PB0MFP_BMC5         (0x14UL<<SYS_GPB_MFP0_PB0MFP_Pos) /*!< GPB_MFP0 PB0 setting for BMC5        */

/* PB.1 MFP */
#define SYS_GPB_MFP0_PB1MFP_GPIO         (0x00UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for GPIO        */
#define SYS_GPB_MFP0_PB1MFP_EADC0_CH1    (0x01UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EADC0_CH1   */
#define SYS_GPB_MFP0_PB1MFP_EADC1_CH9    (0x01UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EADC1_CH9   */
#define SYS_GPB_MFP0_PB1MFP_EADC2_CH9    (0x01UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EADC2_CH9   */
#define SYS_GPB_MFP0_PB1MFP_ACMP3_P0     (0x01UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for ACMP3_P0    */
#define SYS_GPB_MFP0_PB1MFP_EBI_ADR8     (0x02UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EBI_ADR8    */
#define SYS_GPB_MFP0_PB1MFP_SD0_CLK      (0x03UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for SD0_CLK     */
#define SYS_GPB_MFP0_PB1MFP_EMAC0_RMII_RXERR (0x04UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EMAC0_RMII_RXERR*/
#define SYS_GPB_MFP0_PB1MFP_SPI1_I2SMCLK (0x05UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for SPI1_I2SMCLK*/
#define SYS_GPB_MFP0_PB1MFP_SPI3_I2SMCLK (0x06UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for SPI3_I2SMCLK*/
#define SYS_GPB_MFP0_PB1MFP_UART2_TXD    (0x07UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for UART2_TXD   */
#define SYS_GPB_MFP0_PB1MFP_I2C1_SCL     (0x09UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for I2C1_SCL    */
#define SYS_GPB_MFP0_PB1MFP_I2S0_LRCK    (0x0aUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for I2S0_LRCK   */
#define SYS_GPB_MFP0_PB1MFP_EPWM0_CH4    (0x0bUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EPWM0_CH4   */
#define SYS_GPB_MFP0_PB1MFP_EPWM1_CH4    (0x0cUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EPWM1_CH4   */
#define SYS_GPB_MFP0_PB1MFP_EPWM0_BRAKE0 (0x0dUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for EPWM0_BRAKE0*/
#define SYS_GPB_MFP0_PB1MFP_ACMP2_O      (0x0eUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for ACMP2_O     */
#define SYS_GPB_MFP0_PB1MFP_QSPI0_MISO1  (0x0fUL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for QSPI0_MISO1 */
#define SYS_GPB_MFP0_PB1MFP_KPI_ROW2     (0x12UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for KPI_ROW2    */
#define SYS_GPB_MFP0_PB1MFP_SPI4_MISO    (0x13UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for SPI4_MISO   */
#define SYS_GPB_MFP0_PB1MFP_BMC4         (0x14UL<<SYS_GPB_MFP0_PB1MFP_Pos) /*!< GPB_MFP0 PB1 setting for BMC4        */

/* PB.2 MFP */
#define SYS_GPB_MFP0_PB2MFP_GPIO         (0x00UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for GPIO        */
#define SYS_GPB_MFP0_PB2MFP_EADC0_CH2    (0x01UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for EADC0_CH2   */
#define SYS_GPB_MFP0_PB2MFP_EADC1_CH10   (0x01UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for EADC1_CH10  */
#define SYS_GPB_MFP0_PB2MFP_ACMP0_P1     (0x01UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for ACMP0_P1    */
#define SYS_GPB_MFP0_PB2MFP_EBI_ADR3     (0x02UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for EBI_ADR3    */
#define SYS_GPB_MFP0_PB2MFP_SD0_DAT0     (0x03UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for SD0_DAT0    */
#define SYS_GPB_MFP0_PB2MFP_EMAC0_RMII_CRSDV (0x04UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for EMAC0_RMII_CRSDV*/
#define SYS_GPB_MFP0_PB2MFP_SPI1_SS      (0x05UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for SPI1_SS     */
#define SYS_GPB_MFP0_PB2MFP_UART1_RXD    (0x06UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for UART1_RXD   */
#define SYS_GPB_MFP0_PB2MFP_UART5_nCTS   (0x07UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for UART5_nCTS  */
#define SYS_GPB_MFP0_PB2MFP_SC0_PWR      (0x09UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for SC0_PWR     */
#define SYS_GPB_MFP0_PB2MFP_I2S0_DO      (0x0aUL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for I2S0_DO     */
#define SYS_GPB_MFP0_PB2MFP_EPWM0_CH3    (0x0bUL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for EPWM0_CH3   */
#define SYS_GPB_MFP0_PB2MFP_I2C1_SDA     (0x0cUL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for I2C1_SDA    */
#define SYS_GPB_MFP0_PB2MFP_TM3          (0x0eUL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for TM3         */
#define SYS_GPB_MFP0_PB2MFP_INT3         (0x0fUL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for INT3        */
#define SYS_GPB_MFP0_PB2MFP_PSIO0_CH7    (0x11UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for PSIO0_CH7   */
#define SYS_GPB_MFP0_PB2MFP_KPI_ROW1     (0x12UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for KPI_ROW1    */
#define SYS_GPB_MFP0_PB2MFP_SPI4_CLK     (0x13UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for SPI4_CLK    */
#define SYS_GPB_MFP0_PB2MFP_BMC3         (0x14UL<<SYS_GPB_MFP0_PB2MFP_Pos) /*!< GPB_MFP0 PB2 setting for BMC3        */

/* PB.3 MFP */
#define SYS_GPB_MFP0_PB3MFP_GPIO         (0x00UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for GPIO        */
#define SYS_GPB_MFP0_PB3MFP_EADC0_CH3    (0x01UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for EADC0_CH3   */
#define SYS_GPB_MFP0_PB3MFP_EADC1_CH11   (0x01UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for EADC1_CH11  */
#define SYS_GPB_MFP0_PB3MFP_ACMP0_N      (0x01UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for ACMP0_N     */
#define SYS_GPB_MFP0_PB3MFP_EBI_ADR2     (0x02UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for EBI_ADR2    */
#define SYS_GPB_MFP0_PB3MFP_SD0_DAT1     (0x03UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for SD0_DAT1    */
#define SYS_GPB_MFP0_PB3MFP_EMAC0_RMII_RXD1 (0x04UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for EMAC0_RMII_RXD1*/
#define SYS_GPB_MFP0_PB3MFP_SPI1_CLK     (0x05UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for SPI1_CLK    */
#define SYS_GPB_MFP0_PB3MFP_UART1_TXD    (0x06UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for UART1_TXD   */
#define SYS_GPB_MFP0_PB3MFP_UART5_nRTS   (0x07UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for UART5_nRTS  */
#define SYS_GPB_MFP0_PB3MFP_SC0_RST      (0x09UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for SC0_RST     */
#define SYS_GPB_MFP0_PB3MFP_I2S0_DI      (0x0aUL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for I2S0_DI     */
#define SYS_GPB_MFP0_PB3MFP_EPWM0_CH2    (0x0bUL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for EPWM0_CH2   */
#define SYS_GPB_MFP0_PB3MFP_I2C1_SCL     (0x0cUL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for I2C1_SCL    */
#define SYS_GPB_MFP0_PB3MFP_TM2          (0x0eUL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for TM2         */
#define SYS_GPB_MFP0_PB3MFP_INT2         (0x0fUL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for INT2        */
#define SYS_GPB_MFP0_PB3MFP_PSIO0_CH6    (0x11UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for PSIO0_CH6   */
#define SYS_GPB_MFP0_PB3MFP_KPI_ROW0     (0x12UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for KPI_ROW0    */
#define SYS_GPB_MFP0_PB3MFP_SPI4_SS      (0x13UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for SPI4_SS     */
#define SYS_GPB_MFP0_PB3MFP_BMC2         (0x14UL<<SYS_GPB_MFP0_PB3MFP_Pos) /*!< GPB_MFP0 PB3 setting for BMC2        */

/* PB.4 MFP */
#define SYS_GPB_MFP1_PB4MFP_GPIO         (0x00UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for GPIO        */
#define SYS_GPB_MFP1_PB4MFP_EADC0_CH4    (0x01UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for EADC0_CH4   */
#define SYS_GPB_MFP1_PB4MFP_ACMP1_P1     (0x01UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for ACMP1_P1    */
#define SYS_GPB_MFP1_PB4MFP_EBI_ADR1     (0x02UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for EBI_ADR1    */
#define SYS_GPB_MFP1_PB4MFP_SD0_DAT2     (0x03UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for SD0_DAT2    */
#define SYS_GPB_MFP1_PB4MFP_EMAC0_RMII_RXD0 (0x04UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for EMAC0_RMII_RXD0*/
#define SYS_GPB_MFP1_PB4MFP_SPI1_MOSI    (0x05UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for SPI1_MOSI   */
#define SYS_GPB_MFP1_PB4MFP_I2C0_SDA     (0x06UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for I2C0_SDA    */
#define SYS_GPB_MFP1_PB4MFP_UART5_RXD    (0x07UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for UART5_RXD   */
#define SYS_GPB_MFP1_PB4MFP_SC0_DAT      (0x09UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for SC0_DAT     */
#define SYS_GPB_MFP1_PB4MFP_I2S0_MCLK    (0x0aUL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for I2S0_MCLK   */
#define SYS_GPB_MFP1_PB4MFP_EPWM0_CH1    (0x0bUL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for EPWM0_CH1   */
#define SYS_GPB_MFP1_PB4MFP_UART2_RXD    (0x0cUL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for UART2_RXD   */
#define SYS_GPB_MFP1_PB4MFP_TM1          (0x0eUL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for TM1         */
#define SYS_GPB_MFP1_PB4MFP_INT1         (0x0fUL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for INT1        */
#define SYS_GPB_MFP1_PB4MFP_PSIO0_CH5    (0x11UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for PSIO0_CH5   */
#define SYS_GPB_MFP1_PB4MFP_KPI_COL7     (0x12UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for KPI_COL7    */
#define SYS_GPB_MFP1_PB4MFP_BMC1         (0x14UL<<SYS_GPB_MFP1_PB4MFP_Pos) /*!< GPB_MFP1 PB4 setting for BMC1        */

/* PB.5 MFP */
#define SYS_GPB_MFP1_PB5MFP_GPIO         (0x00UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for GPIO        */
#define SYS_GPB_MFP1_PB5MFP_EADC0_CH5    (0x01UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for EADC0_CH5   */
#define SYS_GPB_MFP1_PB5MFP_ACMP1_N      (0x01UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for ACMP1_N     */
#define SYS_GPB_MFP1_PB5MFP_EBI_ADR0     (0x02UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for EBI_ADR0    */
#define SYS_GPB_MFP1_PB5MFP_SD0_DAT3     (0x03UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for SD0_DAT3    */
#define SYS_GPB_MFP1_PB5MFP_EMAC0_RMII_REFCLK (0x04UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for EMAC0_RMII_REFCLK*/
#define SYS_GPB_MFP1_PB5MFP_SPI1_MISO    (0x05UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for SPI1_MISO   */
#define SYS_GPB_MFP1_PB5MFP_I2C0_SCL     (0x06UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for I2C0_SCL    */
#define SYS_GPB_MFP1_PB5MFP_UART5_TXD    (0x07UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for UART5_TXD   */
#define SYS_GPB_MFP1_PB5MFP_SC0_CLK      (0x09UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for SC0_CLK     */
#define SYS_GPB_MFP1_PB5MFP_I2S0_BCLK    (0x0aUL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for I2S0_BCLK   */
#define SYS_GPB_MFP1_PB5MFP_EPWM0_CH0    (0x0bUL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for EPWM0_CH0   */
#define SYS_GPB_MFP1_PB5MFP_UART2_TXD    (0x0cUL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for UART2_TXD   */
#define SYS_GPB_MFP1_PB5MFP_TM0          (0x0eUL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for TM0         */
#define SYS_GPB_MFP1_PB5MFP_INT0         (0x0fUL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for INT0        */
#define SYS_GPB_MFP1_PB5MFP_PSIO0_CH4    (0x11UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for PSIO0_CH4   */
#define SYS_GPB_MFP1_PB5MFP_KPI_COL6     (0x12UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for KPI_COL6    */
#define SYS_GPB_MFP1_PB5MFP_BMC0         (0x14UL<<SYS_GPB_MFP1_PB5MFP_Pos) /*!< GPB_MFP1 PB5 setting for BMC0        */

/* PB.6 MFP */
#define SYS_GPB_MFP1_PB6MFP_GPIO         (0x00UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for GPIO        */
#define SYS_GPB_MFP1_PB6MFP_EADC0_CH6    (0x01UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EADC0_CH6   */
#define SYS_GPB_MFP1_PB6MFP_EADC2_CH14   (0x01UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EADC2_CH14  */
#define SYS_GPB_MFP1_PB6MFP_ACMP2_N      (0x01UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for ACMP2_N     */
#define SYS_GPB_MFP1_PB6MFP_EBI_nWRH     (0x02UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EBI_nWRH    */
#define SYS_GPB_MFP1_PB6MFP_EMAC0_PPS    (0x03UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EMAC0_PPS   */
#define SYS_GPB_MFP1_PB6MFP_CAN1_RXD     (0x05UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for CAN1_RXD    */
#define SYS_GPB_MFP1_PB6MFP_UART1_RXD    (0x06UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for UART1_RXD   */
#define SYS_GPB_MFP1_PB6MFP_SD1_CLK      (0x07UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for SD1_CLK     */
#define SYS_GPB_MFP1_PB6MFP_EBI_nCS1     (0x08UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EBI_nCS1    */
#define SYS_GPB_MFP1_PB6MFP_BPWM1_CH5    (0x0aUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for BPWM1_CH5   */
#define SYS_GPB_MFP1_PB6MFP_EPWM1_BRAKE1 (0x0bUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EPWM1_BRAKE1*/
#define SYS_GPB_MFP1_PB6MFP_EPWM1_CH5    (0x0cUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for EPWM1_CH5   */
#define SYS_GPB_MFP1_PB6MFP_INT4         (0x0dUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for INT4        */
#define SYS_GPB_MFP1_PB6MFP_USB_VBUS_EN  (0x0eUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for USB_VBUS_EN */
#define SYS_GPB_MFP1_PB6MFP_ACMP1_O      (0x0fUL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for ACMP1_O     */
#define SYS_GPB_MFP1_PB6MFP_SPI3_MOSI    (0x10UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for SPI3_MOSI   */
#define SYS_GPB_MFP1_PB6MFP_KPI_COL5     (0x12UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for KPI_COL5    */
#define SYS_GPB_MFP1_PB6MFP_SPI1_SS      (0x13UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for SPI1_SS     */
#define SYS_GPB_MFP1_PB6MFP_BMC31        (0x14UL<<SYS_GPB_MFP1_PB6MFP_Pos) /*!< GPB_MFP1 PB6 setting for BMC31       */

/* PB.7 MFP */
#define SYS_GPB_MFP1_PB7MFP_GPIO         (0x00UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for GPIO        */
#define SYS_GPB_MFP1_PB7MFP_EADC0_CH7    (0x01UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EADC0_CH7   */
#define SYS_GPB_MFP1_PB7MFP_EADC2_CH15   (0x01UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EADC2_CH15  */
#define SYS_GPB_MFP1_PB7MFP_ACMP2_P0     (0x01UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for ACMP2_P0    */
#define SYS_GPB_MFP1_PB7MFP_EBI_nWRL     (0x02UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EBI_nWRL    */
#define SYS_GPB_MFP1_PB7MFP_EMAC0_RMII_TXEN (0x03UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EMAC0_RMII_TXEN*/
#define SYS_GPB_MFP1_PB7MFP_CAN1_TXD     (0x05UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for CAN1_TXD    */
#define SYS_GPB_MFP1_PB7MFP_UART1_TXD    (0x06UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for UART1_TXD   */
#define SYS_GPB_MFP1_PB7MFP_SD1_CMD      (0x07UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for SD1_CMD     */
#define SYS_GPB_MFP1_PB7MFP_EBI_nCS0     (0x08UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EBI_nCS0    */
#define SYS_GPB_MFP1_PB7MFP_BPWM1_CH4    (0x0aUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for BPWM1_CH4   */
#define SYS_GPB_MFP1_PB7MFP_EPWM1_BRAKE0 (0x0bUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EPWM1_BRAKE0*/
#define SYS_GPB_MFP1_PB7MFP_EPWM1_CH4    (0x0cUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for EPWM1_CH4   */
#define SYS_GPB_MFP1_PB7MFP_INT5         (0x0dUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for INT5        */
#define SYS_GPB_MFP1_PB7MFP_USB_VBUS_ST  (0x0eUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for USB_VBUS_ST */
#define SYS_GPB_MFP1_PB7MFP_ACMP0_O      (0x0fUL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for ACMP0_O     */
#define SYS_GPB_MFP1_PB7MFP_SPI3_MISO    (0x10UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for SPI3_MISO   */
#define SYS_GPB_MFP1_PB7MFP_KPI_COL4     (0x12UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for KPI_COL4    */
#define SYS_GPB_MFP1_PB7MFP_SPI1_CLK     (0x13UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for SPI1_CLK    */
#define SYS_GPB_MFP1_PB7MFP_BMC30        (0x14UL<<SYS_GPB_MFP1_PB7MFP_Pos) /*!< GPB_MFP1 PB7 setting for BMC30       */

/* PB.8 MFP */
#define SYS_GPB_MFP2_PB8MFP_GPIO         (0x00UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for GPIO        */
#define SYS_GPB_MFP2_PB8MFP_EADC0_CH8    (0x01UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for EADC0_CH8   */
#define SYS_GPB_MFP2_PB8MFP_ACMP2_P1     (0x01UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for ACMP2_P1    */
#define SYS_GPB_MFP2_PB8MFP_EBI_ADR19    (0x02UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for EBI_ADR19   */
#define SYS_GPB_MFP2_PB8MFP_EMAC0_RMII_TXD1 (0x03UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for EMAC0_RMII_TXD1*/
#define SYS_GPB_MFP2_PB8MFP_UART0_RXD    (0x05UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for UART0_RXD   */
#define SYS_GPB_MFP2_PB8MFP_UART1_nRTS   (0x06UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for UART1_nRTS  */
#define SYS_GPB_MFP2_PB8MFP_I2C1_SMBSUS  (0x07UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for I2C1_SMBSUS */
#define SYS_GPB_MFP2_PB8MFP_UART7_RXD    (0x08UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for UART7_RXD   */
#define SYS_GPB_MFP2_PB8MFP_I2C0_SDA     (0x09UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for I2C0_SDA    */
#define SYS_GPB_MFP2_PB8MFP_BPWM1_CH3    (0x0aUL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for BPWM1_CH3   */
#define SYS_GPB_MFP2_PB8MFP_SPI3_MOSI    (0x0bUL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for SPI3_MOSI   */
#define SYS_GPB_MFP2_PB8MFP_CAN2_RXD     (0x0cUL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for CAN2_RXD    */
#define SYS_GPB_MFP2_PB8MFP_INT6         (0x0dUL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for INT6        */
#define SYS_GPB_MFP2_PB8MFP_EADC2_ST     (0x0eUL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for EADC2_ST    */
#define SYS_GPB_MFP2_PB8MFP_BMC23        (0x14UL<<SYS_GPB_MFP2_PB8MFP_Pos) /*!< GPB_MFP2 PB8 setting for BMC23       */

/* PB.9 MFP */
#define SYS_GPB_MFP2_PB9MFP_GPIO         (0x00UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for GPIO        */
#define SYS_GPB_MFP2_PB9MFP_EADC0_CH9    (0x01UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for EADC0_CH9   */
#define SYS_GPB_MFP2_PB9MFP_ACMP2_P2     (0x01UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for ACMP2_P2    */
#define SYS_GPB_MFP2_PB9MFP_EBI_ADR18    (0x02UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for EBI_ADR18   */
#define SYS_GPB_MFP2_PB9MFP_EMAC0_RMII_TXD0 (0x03UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for EMAC0_RMII_TXD0*/
#define SYS_GPB_MFP2_PB9MFP_UART0_TXD    (0x05UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for UART0_TXD   */
#define SYS_GPB_MFP2_PB9MFP_UART1_nCTS   (0x06UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for UART1_nCTS  */
#define SYS_GPB_MFP2_PB9MFP_I2C1_SMBAL   (0x07UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for I2C1_SMBAL  */
#define SYS_GPB_MFP2_PB9MFP_UART7_TXD    (0x08UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for UART7_TXD   */
#define SYS_GPB_MFP2_PB9MFP_I2C0_SCL     (0x09UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for I2C0_SCL    */
#define SYS_GPB_MFP2_PB9MFP_BPWM1_CH2    (0x0aUL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for BPWM1_CH2   */
#define SYS_GPB_MFP2_PB9MFP_SPI3_MISO    (0x0bUL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for SPI3_MISO   */
#define SYS_GPB_MFP2_PB9MFP_CAN2_TXD     (0x0cUL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for CAN2_TXD    */
#define SYS_GPB_MFP2_PB9MFP_INT7         (0x0dUL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for INT7        */
#define SYS_GPB_MFP2_PB9MFP_CCAP_HSYNC   (0x0eUL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for CCAP_HSYNC  */
#define SYS_GPB_MFP2_PB9MFP_BMC22        (0x14UL<<SYS_GPB_MFP2_PB9MFP_Pos) /*!< GPB_MFP2 PB9 setting for BMC22       */

/* PB.10 MFP */
#define SYS_GPB_MFP2_PB10MFP_GPIO        (0x00UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for GPIO       */
#define SYS_GPB_MFP2_PB10MFP_EADC0_CH10  (0x01UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for EADC0_CH10 */
#define SYS_GPB_MFP2_PB10MFP_ACMP2_P3    (0x01UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for ACMP2_P3   */
#define SYS_GPB_MFP2_PB10MFP_EBI_ADR17   (0x02UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for EBI_ADR17  */
#define SYS_GPB_MFP2_PB10MFP_EMAC0_RMII_MDIO (0x03UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for EMAC0_RMII_MDIO*/
#define SYS_GPB_MFP2_PB10MFP_UART0_nRTS  (0x05UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for UART0_nRTS */
#define SYS_GPB_MFP2_PB10MFP_UART4_RXD   (0x06UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for UART4_RXD  */
#define SYS_GPB_MFP2_PB10MFP_I2C1_SDA    (0x07UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for I2C1_SDA   */
#define SYS_GPB_MFP2_PB10MFP_CAN0_RXD    (0x08UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for CAN0_RXD   */
#define SYS_GPB_MFP2_PB10MFP_BPWM1_CH1   (0x0aUL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for BPWM1_CH1  */
#define SYS_GPB_MFP2_PB10MFP_SPI3_SS     (0x0bUL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for SPI3_SS    */
#define SYS_GPB_MFP2_PB10MFP_CCAP_VSYNC  (0x0cUL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for CCAP_VSYNC */
#define SYS_GPB_MFP2_PB10MFP_HSUSB_VBUS_EN (0x0eUL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for HSUSB_VBUS_EN*/
#define SYS_GPB_MFP2_PB10MFP_BMC21       (0x14UL<<SYS_GPB_MFP2_PB10MFP_Pos)/*!< GPB_MFP2 PB10 setting for BMC21      */

/* PB.11 MFP */
#define SYS_GPB_MFP2_PB11MFP_GPIO        (0x00UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for GPIO       */
#define SYS_GPB_MFP2_PB11MFP_EADC0_CH11  (0x01UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for EADC0_CH11 */
#define SYS_GPB_MFP2_PB11MFP_EBI_ADR16   (0x02UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for EBI_ADR16  */
#define SYS_GPB_MFP2_PB11MFP_EMAC0_RMII_MDC (0x03UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for EMAC0_RMII_MDC*/
#define SYS_GPB_MFP2_PB11MFP_UART0_nCTS  (0x05UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for UART0_nCTS */
#define SYS_GPB_MFP2_PB11MFP_UART4_TXD   (0x06UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for UART4_TXD  */
#define SYS_GPB_MFP2_PB11MFP_I2C1_SCL    (0x07UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for I2C1_SCL   */
#define SYS_GPB_MFP2_PB11MFP_CAN0_TXD    (0x08UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for CAN0_TXD   */
#define SYS_GPB_MFP2_PB11MFP_SPI0_I2SMCLK (0x09UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for SPI0_I2SMCLK*/
#define SYS_GPB_MFP2_PB11MFP_BPWM1_CH0   (0x0aUL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for BPWM1_CH0  */
#define SYS_GPB_MFP2_PB11MFP_SPI3_CLK    (0x0bUL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for SPI3_CLK   */
#define SYS_GPB_MFP2_PB11MFP_CCAP_SFIELD (0x0cUL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for CCAP_SFIELD*/
#define SYS_GPB_MFP2_PB11MFP_HSUSB_VBUS_ST (0x0eUL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for HSUSB_VBUS_ST*/
#define SYS_GPB_MFP2_PB11MFP_BMC20       (0x14UL<<SYS_GPB_MFP2_PB11MFP_Pos)/*!< GPB_MFP2 PB11 setting for BMC20      */

/* PB.12 MFP */
#define SYS_GPB_MFP3_PB12MFP_GPIO        (0x00UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for GPIO       */
#define SYS_GPB_MFP3_PB12MFP_EADC0_CH12  (0x01UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for EADC0_CH12 */
#define SYS_GPB_MFP3_PB12MFP_EADC1_CH12  (0x01UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for EADC1_CH12 */
#define SYS_GPB_MFP3_PB12MFP_DAC0_OUT    (0x01UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for DAC0_OUT   */
#define SYS_GPB_MFP3_PB12MFP_ACMP0_P2    (0x01UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for ACMP0_P2   */
#define SYS_GPB_MFP3_PB12MFP_ACMP1_P2    (0x01UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for ACMP1_P2   */
#define SYS_GPB_MFP3_PB12MFP_EBI_AD15    (0x02UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for EBI_AD15   */
#define SYS_GPB_MFP3_PB12MFP_SC1_CLK     (0x03UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for SC1_CLK    */
#define SYS_GPB_MFP3_PB12MFP_SPI0_MOSI   (0x04UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for SPI0_MOSI  */
#define SYS_GPB_MFP3_PB12MFP_USCI0_CLK   (0x05UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for USCI0_CLK  */
#define SYS_GPB_MFP3_PB12MFP_UART0_RXD   (0x06UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for UART0_RXD  */
#define SYS_GPB_MFP3_PB12MFP_UART3_nCTS  (0x07UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for UART3_nCTS */
#define SYS_GPB_MFP3_PB12MFP_I2C2_SDA    (0x08UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for I2C2_SDA   */
#define SYS_GPB_MFP3_PB12MFP_SD0_nCD     (0x09UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for SD0_nCD    */
#define SYS_GPB_MFP3_PB12MFP_CCAP_SCLK   (0x0aUL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for CCAP_SCLK  */
#define SYS_GPB_MFP3_PB12MFP_EPWM1_CH3   (0x0bUL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for EPWM1_CH3  */
#define SYS_GPB_MFP3_PB12MFP_ETMC_TRACE_DATA3 (0x0cUL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for ETMC_TRACE_DATA3*/
#define SYS_GPB_MFP3_PB12MFP_TM3_EXT     (0x0dUL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for TM3_EXT    */
#define SYS_GPB_MFP3_PB12MFP_CAN3_RXD    (0x0eUL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for CAN3_RXD   */
#define SYS_GPB_MFP3_PB12MFP_SPI3_SS     (0x10UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for SPI3_SS    */
#define SYS_GPB_MFP3_PB12MFP_PSIO0_CH3   (0x11UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for PSIO0_CH3  */
#define SYS_GPB_MFP3_PB12MFP_KPI_COL3    (0x12UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for KPI_COL3   */
#define SYS_GPB_MFP3_PB12MFP_BMC29       (0x14UL<<SYS_GPB_MFP3_PB12MFP_Pos)/*!< GPB_MFP3 PB12 setting for BMC29      */

/* PB.13 MFP */
#define SYS_GPB_MFP3_PB13MFP_GPIO        (0x00UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for GPIO       */
#define SYS_GPB_MFP3_PB13MFP_EADC0_CH13  (0x01UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for EADC0_CH13 */
#define SYS_GPB_MFP3_PB13MFP_EADC1_CH13  (0x01UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for EADC1_CH13 */
#define SYS_GPB_MFP3_PB13MFP_DAC1_OUT    (0x01UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for DAC1_OUT   */
#define SYS_GPB_MFP3_PB13MFP_ACMP0_P3    (0x01UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for ACMP0_P3   */
#define SYS_GPB_MFP3_PB13MFP_ACMP1_P3    (0x01UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for ACMP1_P3   */
#define SYS_GPB_MFP3_PB13MFP_EBI_AD14    (0x02UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for EBI_AD14   */
#define SYS_GPB_MFP3_PB13MFP_SC1_DAT     (0x03UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for SC1_DAT    */
#define SYS_GPB_MFP3_PB13MFP_SPI0_MISO   (0x04UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for SPI0_MISO  */
#define SYS_GPB_MFP3_PB13MFP_USCI0_DAT0  (0x05UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for USCI0_DAT0 */
#define SYS_GPB_MFP3_PB13MFP_UART0_TXD   (0x06UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for UART0_TXD  */
#define SYS_GPB_MFP3_PB13MFP_UART3_nRTS  (0x07UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for UART3_nRTS */
#define SYS_GPB_MFP3_PB13MFP_I2C2_SCL    (0x08UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for I2C2_SCL   */
#define SYS_GPB_MFP3_PB13MFP_CCAP_PIXCLK (0x0aUL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for CCAP_PIXCLK*/
#define SYS_GPB_MFP3_PB13MFP_EPWM1_CH2   (0x0bUL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for EPWM1_CH2  */
#define SYS_GPB_MFP3_PB13MFP_ETMC_TRACE_DATA2 (0x0cUL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for ETMC_TRACE_DATA2*/
#define SYS_GPB_MFP3_PB13MFP_TM2_EXT     (0x0dUL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for TM2_EXT    */
#define SYS_GPB_MFP3_PB13MFP_CAN3_TXD    (0x0eUL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for CAN3_TXD   */
#define SYS_GPB_MFP3_PB13MFP_SPI3_CLK    (0x10UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for SPI3_CLK   */
#define SYS_GPB_MFP3_PB13MFP_PSIO0_CH2   (0x11UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for PSIO0_CH2  */
#define SYS_GPB_MFP3_PB13MFP_KPI_COL2    (0x12UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for KPI_COL2   */
#define SYS_GPB_MFP3_PB13MFP_SPI9_MISO   (0x13UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for SPI9_MISO  */
#define SYS_GPB_MFP3_PB13MFP_BMC28       (0x14UL<<SYS_GPB_MFP3_PB13MFP_Pos)/*!< GPB_MFP3 PB13 setting for BMC28      */

/* PB.14 MFP */
#define SYS_GPB_MFP3_PB14MFP_GPIO        (0x00UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for GPIO       */
#define SYS_GPB_MFP3_PB14MFP_EADC0_CH14  (0x01UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for EADC0_CH14 */
#define SYS_GPB_MFP3_PB14MFP_EADC1_CH14  (0x01UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for EADC1_CH14 */
#define SYS_GPB_MFP3_PB14MFP_EBI_AD13    (0x02UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for EBI_AD13   */
#define SYS_GPB_MFP3_PB14MFP_SC1_RST     (0x03UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for SC1_RST    */
#define SYS_GPB_MFP3_PB14MFP_SPI0_CLK    (0x04UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for SPI0_CLK   */
#define SYS_GPB_MFP3_PB14MFP_USCI0_DAT1  (0x05UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for USCI0_DAT1 */
#define SYS_GPB_MFP3_PB14MFP_UART0_nRTS  (0x06UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for UART0_nRTS */
#define SYS_GPB_MFP3_PB14MFP_UART3_RXD   (0x07UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for UART3_RXD  */
#define SYS_GPB_MFP3_PB14MFP_I2C2_SMBSUS (0x08UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for I2C2_SMBSUS*/
#define SYS_GPB_MFP3_PB14MFP_CCAP_DATA0  (0x09UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for CCAP_DATA0 */
#define SYS_GPB_MFP3_PB14MFP_EPWM1_CH1   (0x0bUL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for EPWM1_CH1  */
#define SYS_GPB_MFP3_PB14MFP_ETMC_TRACE_DATA1 (0x0cUL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for ETMC_TRACE_DATA1*/
#define SYS_GPB_MFP3_PB14MFP_TM1_EXT     (0x0dUL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for TM1_EXT    */
#define SYS_GPB_MFP3_PB14MFP_CLKO        (0x0eUL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for CLKO       */
#define SYS_GPB_MFP3_PB14MFP_USB_VBUS_ST (0x0fUL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for USB_VBUS_ST*/
#define SYS_GPB_MFP3_PB14MFP_PSIO0_CH1   (0x11UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for PSIO0_CH1  */
#define SYS_GPB_MFP3_PB14MFP_KPI_COL1    (0x12UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for KPI_COL1   */
#define SYS_GPB_MFP3_PB14MFP_SPI9_SS     (0x13UL<<SYS_GPB_MFP3_PB14MFP_Pos)/*!< GPB_MFP3 PB14 setting for SPI9_SS    */

/* PB.15 MFP */
#define SYS_GPB_MFP3_PB15MFP_GPIO        (0x00UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for GPIO       */
#define SYS_GPB_MFP3_PB15MFP_EADC0_CH15  (0x01UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for EADC0_CH15 */
#define SYS_GPB_MFP3_PB15MFP_EADC1_CH15  (0x01UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for EADC1_CH15 */
#define SYS_GPB_MFP3_PB15MFP_EBI_AD12    (0x02UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for EBI_AD12   */
#define SYS_GPB_MFP3_PB15MFP_SC1_PWR     (0x03UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for SC1_PWR    */
#define SYS_GPB_MFP3_PB15MFP_SPI0_SS     (0x04UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for SPI0_SS    */
#define SYS_GPB_MFP3_PB15MFP_USCI0_CTL1  (0x05UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for USCI0_CTL1 */
#define SYS_GPB_MFP3_PB15MFP_UART0_nCTS  (0x06UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for UART0_nCTS */
#define SYS_GPB_MFP3_PB15MFP_UART3_TXD   (0x07UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for UART3_TXD  */
#define SYS_GPB_MFP3_PB15MFP_I2C2_SMBAL  (0x08UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for I2C2_SMBAL */
#define SYS_GPB_MFP3_PB15MFP_CCAP_DATA1  (0x09UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for CCAP_DATA1 */
#define SYS_GPB_MFP3_PB15MFP_EPWM0_BRAKE1 (0x0aUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for EPWM0_BRAKE1*/
#define SYS_GPB_MFP3_PB15MFP_EPWM1_CH0   (0x0bUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for EPWM1_CH0  */
#define SYS_GPB_MFP3_PB15MFP_ETMC_TRACE_DATA0 (0x0cUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for ETMC_TRACE_DATA0*/
#define SYS_GPB_MFP3_PB15MFP_TM0_EXT     (0x0dUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for TM0_EXT    */
#define SYS_GPB_MFP3_PB15MFP_USB_VBUS_EN (0x0eUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for USB_VBUS_EN*/
#define SYS_GPB_MFP3_PB15MFP_HSUSB_VBUS_EN (0x0fUL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for HSUSB_VBUS_EN*/
#define SYS_GPB_MFP3_PB15MFP_PSIO0_CH0   (0x11UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for PSIO0_CH0  */
#define SYS_GPB_MFP3_PB15MFP_KPI_COL0    (0x12UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for KPI_COL0   */
#define SYS_GPB_MFP3_PB15MFP_SPI9_CLK    (0x13UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for SPI9_CLK   */
#define SYS_GPB_MFP3_PB15MFP_BMC27       (0x14UL<<SYS_GPB_MFP3_PB15MFP_Pos)/*!< GPB_MFP3 PB15 setting for BMC27      */

/* PC.0 MFP */
#define SYS_GPC_MFP0_PC0MFP_GPIO         (0x00UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for GPIO        */
#define SYS_GPC_MFP0_PC0MFP_EBI_AD0      (0x02UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for EBI_AD0     */
#define SYS_GPC_MFP0_PC0MFP_SPIM_MOSI    (0x03UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for SPIM_MOSI   */
#define SYS_GPC_MFP0_PC0MFP_QSPI0_MOSI0  (0x04UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for QSPI0_MOSI0 */
#define SYS_GPC_MFP0_PC0MFP_SC1_CLK      (0x05UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for SC1_CLK     */
#define SYS_GPC_MFP0_PC0MFP_I2S0_LRCK    (0x06UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for I2S0_LRCK   */
#define SYS_GPC_MFP0_PC0MFP_SPI1_SS      (0x07UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for SPI1_SS     */
#define SYS_GPC_MFP0_PC0MFP_UART2_RXD    (0x08UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for UART2_RXD   */
#define SYS_GPC_MFP0_PC0MFP_I2C0_SDA     (0x09UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for I2C0_SDA    */
#define SYS_GPC_MFP0_PC0MFP_CAN2_RXD     (0x0aUL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for CAN2_RXD    */
#define SYS_GPC_MFP0_PC0MFP_EPWM1_CH5    (0x0cUL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for EPWM1_CH5   */
#define SYS_GPC_MFP0_PC0MFP_CCAP_DATA0   (0x0dUL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for CCAP_DATA0  */
#define SYS_GPC_MFP0_PC0MFP_ACMP1_O      (0x0eUL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for ACMP1_O     */
#define SYS_GPC_MFP0_PC0MFP_EADC1_ST     (0x0fUL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for EADC1_ST    */
#define SYS_GPC_MFP0_PC0MFP_HBI_D2       (0x10UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for HBI_D2      */
#define SYS_GPC_MFP0_PC0MFP_QSPI1_CLK    (0x11UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for QSPI1_CLK   */
#define SYS_GPC_MFP0_PC0MFP_KPI_ROW5     (0x12UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for KPI_ROW5    */
#define SYS_GPC_MFP0_PC0MFP_SPI7_MOSI    (0x13UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for SPI7_MOSI   */
#define SYS_GPC_MFP0_PC0MFP_BMC25        (0x14UL<<SYS_GPC_MFP0_PC0MFP_Pos) /*!< GPC_MFP0 PC0 setting for BMC25       */

/* PC.1 MFP */
#define SYS_GPC_MFP0_PC1MFP_GPIO         (0x00UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for GPIO        */
#define SYS_GPC_MFP0_PC1MFP_EBI_AD1      (0x02UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for EBI_AD1     */
#define SYS_GPC_MFP0_PC1MFP_SPIM_MISO    (0x03UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for SPIM_MISO   */
#define SYS_GPC_MFP0_PC1MFP_QSPI0_MISO0  (0x04UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for QSPI0_MISO0 */
#define SYS_GPC_MFP0_PC1MFP_SC1_DAT      (0x05UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for SC1_DAT     */
#define SYS_GPC_MFP0_PC1MFP_I2S0_DO      (0x06UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for I2S0_DO     */
#define SYS_GPC_MFP0_PC1MFP_SPI1_CLK     (0x07UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for SPI1_CLK    */
#define SYS_GPC_MFP0_PC1MFP_UART2_TXD    (0x08UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for UART2_TXD   */
#define SYS_GPC_MFP0_PC1MFP_I2C0_SCL     (0x09UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for I2C0_SCL    */
#define SYS_GPC_MFP0_PC1MFP_CAN2_TXD     (0x0aUL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for CAN2_TXD    */
#define SYS_GPC_MFP0_PC1MFP_EPWM1_CH4    (0x0cUL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for EPWM1_CH4   */
#define SYS_GPC_MFP0_PC1MFP_CCAP_DATA1   (0x0dUL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for CCAP_DATA1  */
#define SYS_GPC_MFP0_PC1MFP_ACMP0_O      (0x0eUL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for ACMP0_O     */
#define SYS_GPC_MFP0_PC1MFP_EADC0_ST     (0x0fUL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for EADC0_ST    */
#define SYS_GPC_MFP0_PC1MFP_HBI_RWDS     (0x10UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for HBI_RWDS    */
#define SYS_GPC_MFP0_PC1MFP_QSPI1_SS     (0x11UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for QSPI1_SS    */
#define SYS_GPC_MFP0_PC1MFP_KPI_ROW4     (0x12UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for KPI_ROW4    */
#define SYS_GPC_MFP0_PC1MFP_SPI7_MISO    (0x13UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for SPI7_MISO   */
#define SYS_GPC_MFP0_PC1MFP_BMC24        (0x14UL<<SYS_GPC_MFP0_PC1MFP_Pos) /*!< GPC_MFP0 PC1 setting for BMC24       */

/* PC.2 MFP */
#define SYS_GPC_MFP0_PC2MFP_GPIO         (0x00UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for GPIO        */
#define SYS_GPC_MFP0_PC2MFP_EBI_AD2      (0x02UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for EBI_AD2     */
#define SYS_GPC_MFP0_PC2MFP_SPIM_CLK     (0x03UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for SPIM_CLK    */
#define SYS_GPC_MFP0_PC2MFP_QSPI0_CLK    (0x04UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for QSPI0_CLK   */
#define SYS_GPC_MFP0_PC2MFP_SC1_RST      (0x05UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for SC1_RST     */
#define SYS_GPC_MFP0_PC2MFP_I2S0_DI      (0x06UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for I2S0_DI     */
#define SYS_GPC_MFP0_PC2MFP_SPI1_MOSI    (0x07UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for SPI1_MOSI   */
#define SYS_GPC_MFP0_PC2MFP_UART2_nCTS   (0x08UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for UART2_nCTS  */
#define SYS_GPC_MFP0_PC2MFP_I2C0_SMBSUS  (0x09UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for I2C0_SMBSUS */
#define SYS_GPC_MFP0_PC2MFP_CAN1_RXD     (0x0aUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for CAN1_RXD    */
#define SYS_GPC_MFP0_PC2MFP_UART3_RXD    (0x0bUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for UART3_RXD   */
#define SYS_GPC_MFP0_PC2MFP_EPWM1_CH3    (0x0cUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for EPWM1_CH3   */
#define SYS_GPC_MFP0_PC2MFP_CCAP_DATA2   (0x0dUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for CCAP_DATA2  */
#define SYS_GPC_MFP0_PC2MFP_QSPI1_MOSI0  (0x0eUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for QSPI1_MOSI0 */
#define SYS_GPC_MFP0_PC2MFP_I2C3_SDA     (0x0fUL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for I2C3_SDA    */
#define SYS_GPC_MFP0_PC2MFP_HBI_nRESET   (0x10UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for HBI_nRESET  */
#define SYS_GPC_MFP0_PC2MFP_PSIO0_CH3    (0x11UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for PSIO0_CH3   */
#define SYS_GPC_MFP0_PC2MFP_KPI_ROW3     (0x12UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for KPI_ROW3    */
#define SYS_GPC_MFP0_PC2MFP_SPI7_CLK     (0x13UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for SPI7_CLK    */
#define SYS_GPC_MFP0_PC2MFP_BMC23        (0x14UL<<SYS_GPC_MFP0_PC2MFP_Pos) /*!< GPC_MFP0 PC2 setting for BMC23       */

/* PC.3 MFP */
#define SYS_GPC_MFP0_PC3MFP_GPIO         (0x00UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for GPIO        */
#define SYS_GPC_MFP0_PC3MFP_EBI_AD3      (0x02UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for EBI_AD3     */
#define SYS_GPC_MFP0_PC3MFP_SPIM_SS      (0x03UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for SPIM_SS     */
#define SYS_GPC_MFP0_PC3MFP_QSPI0_SS     (0x04UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for QSPI0_SS    */
#define SYS_GPC_MFP0_PC3MFP_SC1_PWR      (0x05UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for SC1_PWR     */
#define SYS_GPC_MFP0_PC3MFP_I2S0_MCLK    (0x06UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for I2S0_MCLK   */
#define SYS_GPC_MFP0_PC3MFP_SPI1_MISO    (0x07UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for SPI1_MISO   */
#define SYS_GPC_MFP0_PC3MFP_UART2_nRTS   (0x08UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for UART2_nRTS  */
#define SYS_GPC_MFP0_PC3MFP_I2C0_SMBAL   (0x09UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for I2C0_SMBAL  */
#define SYS_GPC_MFP0_PC3MFP_CAN1_TXD     (0x0aUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for CAN1_TXD    */
#define SYS_GPC_MFP0_PC3MFP_UART3_TXD    (0x0bUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for UART3_TXD   */
#define SYS_GPC_MFP0_PC3MFP_EPWM1_CH2    (0x0cUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for EPWM1_CH2   */
#define SYS_GPC_MFP0_PC3MFP_CCAP_DATA3   (0x0dUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for CCAP_DATA3  */
#define SYS_GPC_MFP0_PC3MFP_QSPI1_MISO0  (0x0eUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for QSPI1_MISO0 */
#define SYS_GPC_MFP0_PC3MFP_I2C3_SCL     (0x0fUL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for I2C3_SCL    */
#define SYS_GPC_MFP0_PC3MFP_HBI_nCS      (0x10UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for HBI_nCS     */
#define SYS_GPC_MFP0_PC3MFP_PSIO0_CH2    (0x11UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for PSIO0_CH2   */
#define SYS_GPC_MFP0_PC3MFP_KPI_ROW2     (0x12UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for KPI_ROW2    */
#define SYS_GPC_MFP0_PC3MFP_SPI7_SS      (0x13UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for SPI7_SS     */
#define SYS_GPC_MFP0_PC3MFP_BMC22        (0x14UL<<SYS_GPC_MFP0_PC3MFP_Pos) /*!< GPC_MFP0 PC3 setting for BMC22       */

/* PC.4 MFP */
#define SYS_GPC_MFP1_PC4MFP_GPIO         (0x00UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for GPIO        */
#define SYS_GPC_MFP1_PC4MFP_EBI_AD4      (0x02UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for EBI_AD4     */
#define SYS_GPC_MFP1_PC4MFP_SPIM_D3      (0x03UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for SPIM_D3     */
#define SYS_GPC_MFP1_PC4MFP_QSPI0_MOSI1  (0x04UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for QSPI0_MOSI1 */
#define SYS_GPC_MFP1_PC4MFP_SC1_nCD      (0x05UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for SC1_nCD     */
#define SYS_GPC_MFP1_PC4MFP_I2S0_BCLK    (0x06UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for I2S0_BCLK   */
#define SYS_GPC_MFP1_PC4MFP_SPI1_I2SMCLK (0x07UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for SPI1_I2SMCLK*/
#define SYS_GPC_MFP1_PC4MFP_UART2_RXD    (0x08UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for UART2_RXD   */
#define SYS_GPC_MFP1_PC4MFP_I2C1_SDA     (0x09UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for I2C1_SDA    */
#define SYS_GPC_MFP1_PC4MFP_CAN0_RXD     (0x0aUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for CAN0_RXD    */
#define SYS_GPC_MFP1_PC4MFP_UART4_RXD    (0x0bUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for UART4_RXD   */
#define SYS_GPC_MFP1_PC4MFP_EPWM1_CH1    (0x0cUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for EPWM1_CH1   */
#define SYS_GPC_MFP1_PC4MFP_CCAP_DATA4   (0x0dUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for CCAP_DATA4  */
#define SYS_GPC_MFP1_PC4MFP_QSPI1_CLK    (0x0eUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for QSPI1_CLK   */
#define SYS_GPC_MFP1_PC4MFP_I2C3_SMBSUS  (0x0fUL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for I2C3_SMBSUS */
#define SYS_GPC_MFP1_PC4MFP_HBI_CK       (0x10UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for HBI_CK      */
#define SYS_GPC_MFP1_PC4MFP_PSIO0_CH1    (0x11UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for PSIO0_CH1   */
#define SYS_GPC_MFP1_PC4MFP_KPI_ROW1     (0x12UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for KPI_ROW1    */
#define SYS_GPC_MFP1_PC4MFP_BMC21        (0x14UL<<SYS_GPC_MFP1_PC4MFP_Pos) /*!< GPC_MFP1 PC4 setting for BMC21       */

/* PC.5 MFP */
#define SYS_GPC_MFP1_PC5MFP_GPIO         (0x00UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for GPIO        */
#define SYS_GPC_MFP1_PC5MFP_EBI_AD5      (0x02UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for EBI_AD5     */
#define SYS_GPC_MFP1_PC5MFP_SPIM_D2      (0x03UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for SPIM_D2     */
#define SYS_GPC_MFP1_PC5MFP_QSPI0_MISO1  (0x04UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for QSPI0_MISO1 */
#define SYS_GPC_MFP1_PC5MFP_UART2_TXD    (0x08UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for UART2_TXD   */
#define SYS_GPC_MFP1_PC5MFP_I2C1_SCL     (0x09UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for I2C1_SCL    */
#define SYS_GPC_MFP1_PC5MFP_CAN0_TXD     (0x0aUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for CAN0_TXD    */
#define SYS_GPC_MFP1_PC5MFP_UART4_TXD    (0x0bUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for UART4_TXD   */
#define SYS_GPC_MFP1_PC5MFP_EPWM1_CH0    (0x0cUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for EPWM1_CH0   */
#define SYS_GPC_MFP1_PC5MFP_CCAP_DATA5   (0x0dUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for CCAP_DATA5  */
#define SYS_GPC_MFP1_PC5MFP_QSPI1_SS     (0x0eUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for QSPI1_SS    */
#define SYS_GPC_MFP1_PC5MFP_I2C3_SMBAL   (0x0fUL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for I2C3_SMBAL  */
#define SYS_GPC_MFP1_PC5MFP_HBI_nCK      (0x10UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for HBI_nCK     */
#define SYS_GPC_MFP1_PC5MFP_PSIO0_CH0    (0x11UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for PSIO0_CH0   */
#define SYS_GPC_MFP1_PC5MFP_KPI_ROW0     (0x12UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for KPI_ROW0    */
#define SYS_GPC_MFP1_PC5MFP_BMC20        (0x14UL<<SYS_GPC_MFP1_PC5MFP_Pos) /*!< GPC_MFP1 PC5 setting for BMC20       */

/* PC.6 MFP */
#define SYS_GPC_MFP1_PC6MFP_GPIO         (0x00UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for GPIO        */
#define SYS_GPC_MFP1_PC6MFP_EBI_AD8      (0x02UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for EBI_AD8     */
#define SYS_GPC_MFP1_PC6MFP_EMAC0_RMII_RXD1 (0x03UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for EMAC0_RMII_RXD1*/
#define SYS_GPC_MFP1_PC6MFP_SPI1_MOSI    (0x04UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for SPI1_MOSI   */
#define SYS_GPC_MFP1_PC6MFP_UART4_RXD    (0x05UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for UART4_RXD   */
#define SYS_GPC_MFP1_PC6MFP_SC2_RST      (0x06UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for SC2_RST     */
#define SYS_GPC_MFP1_PC6MFP_UART0_nRTS   (0x07UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for UART0_nRTS  */
#define SYS_GPC_MFP1_PC6MFP_I2C1_SMBSUS  (0x08UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for I2C1_SMBSUS */
#define SYS_GPC_MFP1_PC6MFP_UART6_RXD    (0x09UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for UART6_RXD   */
#define SYS_GPC_MFP1_PC6MFP_ACMP3_WLAT   (0x0aUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for ACMP3_WLAT  */
#define SYS_GPC_MFP1_PC6MFP_EPWM1_CH3    (0x0bUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for EPWM1_CH3   */
#define SYS_GPC_MFP1_PC6MFP_BPWM1_CH1    (0x0cUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for BPWM1_CH1   */
#define SYS_GPC_MFP1_PC6MFP_CAN3_RXD     (0x0dUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for CAN3_RXD    */
#define SYS_GPC_MFP1_PC6MFP_TM1          (0x0eUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for TM1         */
#define SYS_GPC_MFP1_PC6MFP_INT2         (0x0fUL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for INT2        */
#define SYS_GPC_MFP1_PC6MFP_KPI_COL2     (0x12UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for KPI_COL2    */
#define SYS_GPC_MFP1_PC6MFP_SPI6_MOSI    (0x13UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for SPI6_MOSI   */
#define SYS_GPC_MFP1_PC6MFP_BMC25        (0x14UL<<SYS_GPC_MFP1_PC6MFP_Pos) /*!< GPC_MFP1 PC6 setting for BMC25       */

/* PC.7 MFP */
#define SYS_GPC_MFP1_PC7MFP_GPIO         (0x00UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for GPIO        */
#define SYS_GPC_MFP1_PC7MFP_EBI_AD9      (0x02UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for EBI_AD9     */
#define SYS_GPC_MFP1_PC7MFP_EMAC0_RMII_RXD0 (0x03UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for EMAC0_RMII_RXD0*/
#define SYS_GPC_MFP1_PC7MFP_SPI1_MISO    (0x04UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for SPI1_MISO   */
#define SYS_GPC_MFP1_PC7MFP_UART4_TXD    (0x05UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for UART4_TXD   */
#define SYS_GPC_MFP1_PC7MFP_SC2_PWR      (0x06UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for SC2_PWR     */
#define SYS_GPC_MFP1_PC7MFP_UART0_nCTS   (0x07UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for UART0_nCTS  */
#define SYS_GPC_MFP1_PC7MFP_I2C1_SMBAL   (0x08UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for I2C1_SMBAL  */
#define SYS_GPC_MFP1_PC7MFP_UART6_TXD    (0x09UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for UART6_TXD   */
#define SYS_GPC_MFP1_PC7MFP_ACMP2_WLAT   (0x0aUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for ACMP2_WLAT  */
#define SYS_GPC_MFP1_PC7MFP_EPWM1_CH2    (0x0bUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for EPWM1_CH2   */
#define SYS_GPC_MFP1_PC7MFP_BPWM1_CH0    (0x0cUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for BPWM1_CH0   */
#define SYS_GPC_MFP1_PC7MFP_CAN3_TXD     (0x0dUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for CAN3_TXD    */
#define SYS_GPC_MFP1_PC7MFP_TM0          (0x0eUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for TM0         */
#define SYS_GPC_MFP1_PC7MFP_INT3         (0x0fUL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for INT3        */
#define SYS_GPC_MFP1_PC7MFP_KPI_COL3     (0x12UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for KPI_COL3    */
#define SYS_GPC_MFP1_PC7MFP_SPI6_MISO    (0x13UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for SPI6_MISO   */
#define SYS_GPC_MFP1_PC7MFP_BMC24        (0x14UL<<SYS_GPC_MFP1_PC7MFP_Pos) /*!< GPC_MFP1 PC7 setting for BMC24       */

/* PC.8 MFP */
#define SYS_GPC_MFP2_PC8MFP_GPIO         (0x00UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for GPIO        */
#define SYS_GPC_MFP2_PC8MFP_EBI_ADR16    (0x02UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for EBI_ADR16   */
#define SYS_GPC_MFP2_PC8MFP_EMAC0_RMII_REFCLK (0x03UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for EMAC0_RMII_REFCLK*/
#define SYS_GPC_MFP2_PC8MFP_I2C0_SDA     (0x04UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for I2C0_SDA    */
#define SYS_GPC_MFP2_PC8MFP_UART4_nCTS   (0x05UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for UART4_nCTS  */
#define SYS_GPC_MFP2_PC8MFP_UART1_RXD    (0x08UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for UART1_RXD   */
#define SYS_GPC_MFP2_PC8MFP_EPWM1_CH1    (0x0bUL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for EPWM1_CH1   */
#define SYS_GPC_MFP2_PC8MFP_BPWM1_CH4    (0x0cUL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for BPWM1_CH4   */
#define SYS_GPC_MFP2_PC8MFP_KPI_COL4     (0x12UL<<SYS_GPC_MFP2_PC8MFP_Pos) /*!< GPC_MFP2 PC8 setting for KPI_COL4    */

/* PC.9 MFP */
#define SYS_GPC_MFP2_PC9MFP_GPIO         (0x00UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for GPIO        */
#define SYS_GPC_MFP2_PC9MFP_EADC2_CH10   (0x01UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for EADC2_CH10  */
#define SYS_GPC_MFP2_PC9MFP_ACMP3_P1     (0x01UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for ACMP3_P1    */
#define SYS_GPC_MFP2_PC9MFP_EBI_ADR7     (0x02UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for EBI_ADR7    */
#define SYS_GPC_MFP2_PC9MFP_UART6_nCTS   (0x05UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for UART6_nCTS  */
#define SYS_GPC_MFP2_PC9MFP_SPI3_SS      (0x06UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for SPI3_SS     */
#define SYS_GPC_MFP2_PC9MFP_UART3_RXD    (0x07UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for UART3_RXD   */
#define SYS_GPC_MFP2_PC9MFP_CAN1_RXD     (0x09UL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for CAN1_RXD    */
#define SYS_GPC_MFP2_PC9MFP_I2C4_SMBSUS  (0x0aUL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for I2C4_SMBSUS */
#define SYS_GPC_MFP2_PC9MFP_EPWM1_CH3    (0x0cUL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for EPWM1_CH3   */
#define SYS_GPC_MFP2_PC9MFP_EADC1_ST     (0x0eUL<<SYS_GPC_MFP2_PC9MFP_Pos) /*!< GPC_MFP2 PC9 setting for EADC1_ST    */

/* PC.10 MFP */
#define SYS_GPC_MFP2_PC10MFP_GPIO        (0x00UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for GPIO       */
#define SYS_GPC_MFP2_PC10MFP_EADC2_CH11  (0x01UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for EADC2_CH11 */
#define SYS_GPC_MFP2_PC10MFP_ACMP3_P2    (0x01UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for ACMP3_P2   */
#define SYS_GPC_MFP2_PC10MFP_EBI_ADR6    (0x02UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for EBI_ADR6   */
#define SYS_GPC_MFP2_PC10MFP_UART6_nRTS  (0x05UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for UART6_nRTS */
#define SYS_GPC_MFP2_PC10MFP_SPI3_CLK    (0x06UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for SPI3_CLK   */
#define SYS_GPC_MFP2_PC10MFP_UART3_TXD   (0x07UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for UART3_TXD  */
#define SYS_GPC_MFP2_PC10MFP_CAN1_TXD    (0x09UL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for CAN1_TXD   */
#define SYS_GPC_MFP2_PC10MFP_I2C4_SMBAL  (0x0aUL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for I2C4_SMBAL */
#define SYS_GPC_MFP2_PC10MFP_ECAP1_IC0   (0x0bUL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for ECAP1_IC0  */
#define SYS_GPC_MFP2_PC10MFP_EPWM1_CH2   (0x0cUL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for EPWM1_CH2  */
#define SYS_GPC_MFP2_PC10MFP_EADC1_ST    (0x0eUL<<SYS_GPC_MFP2_PC10MFP_Pos)/*!< GPC_MFP2 PC10 setting for EADC1_ST   */

/* PC.11 MFP */
#define SYS_GPC_MFP2_PC11MFP_GPIO        (0x00UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for GPIO       */
#define SYS_GPC_MFP2_PC11MFP_EADC2_CH12  (0x01UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for EADC2_CH12 */
#define SYS_GPC_MFP2_PC11MFP_ACMP3_P3    (0x01UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for ACMP3_P3   */
#define SYS_GPC_MFP2_PC11MFP_EBI_ADR5    (0x02UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for EBI_ADR5   */
#define SYS_GPC_MFP2_PC11MFP_UART0_RXD   (0x03UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for UART0_RXD  */
#define SYS_GPC_MFP2_PC11MFP_I2C0_SDA    (0x04UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for I2C0_SDA   */
#define SYS_GPC_MFP2_PC11MFP_UART6_RXD   (0x05UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for UART6_RXD  */
#define SYS_GPC_MFP2_PC11MFP_SPI3_MOSI   (0x06UL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for SPI3_MOSI  */
#define SYS_GPC_MFP2_PC11MFP_I2C4_SDA    (0x0aUL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for I2C4_SDA   */
#define SYS_GPC_MFP2_PC11MFP_ECAP1_IC1   (0x0bUL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for ECAP1_IC1  */
#define SYS_GPC_MFP2_PC11MFP_EPWM1_CH1   (0x0cUL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for EPWM1_CH1  */
#define SYS_GPC_MFP2_PC11MFP_ACMP1_O     (0x0eUL<<SYS_GPC_MFP2_PC11MFP_Pos)/*!< GPC_MFP2 PC11 setting for ACMP1_O    */

/* PC.12 MFP */
#define SYS_GPC_MFP3_PC12MFP_GPIO        (0x00UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for GPIO       */
#define SYS_GPC_MFP3_PC12MFP_EADC2_CH13  (0x01UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for EADC2_CH13 */
#define SYS_GPC_MFP3_PC12MFP_EBI_ADR4    (0x02UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for EBI_ADR4   */
#define SYS_GPC_MFP3_PC12MFP_UART0_TXD   (0x03UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for UART0_TXD  */
#define SYS_GPC_MFP3_PC12MFP_I2C0_SCL    (0x04UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for I2C0_SCL   */
#define SYS_GPC_MFP3_PC12MFP_UART6_TXD   (0x05UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for UART6_TXD  */
#define SYS_GPC_MFP3_PC12MFP_SPI3_MISO   (0x06UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for SPI3_MISO  */
#define SYS_GPC_MFP3_PC12MFP_SC0_nCD     (0x09UL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for SC0_nCD    */
#define SYS_GPC_MFP3_PC12MFP_I2C4_SCL    (0x0aUL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for I2C4_SCL   */
#define SYS_GPC_MFP3_PC12MFP_ECAP1_IC2   (0x0bUL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for ECAP1_IC2  */
#define SYS_GPC_MFP3_PC12MFP_EPWM1_CH0   (0x0cUL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for EPWM1_CH0  */
#define SYS_GPC_MFP3_PC12MFP_ACMP0_O     (0x0eUL<<SYS_GPC_MFP3_PC12MFP_Pos)/*!< GPC_MFP3 PC12 setting for ACMP0_O    */

/* PC.13 MFP */
#define SYS_GPC_MFP3_PC13MFP_GPIO        (0x00UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for GPIO       */
#define SYS_GPC_MFP3_PC13MFP_EADC1_CH3   (0x01UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for EADC1_CH3  */
#define SYS_GPC_MFP3_PC13MFP_EADC2_CH3   (0x01UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for EADC2_CH3  */
#define SYS_GPC_MFP3_PC13MFP_EBI_ADR10   (0x02UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for EBI_ADR10  */
#define SYS_GPC_MFP3_PC13MFP_SC2_nCD     (0x03UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for SC2_nCD    */
#define SYS_GPC_MFP3_PC13MFP_SPI2_I2SMCLK (0x04UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for SPI2_I2SMCLK*/
#define SYS_GPC_MFP3_PC13MFP_CAN1_TXD    (0x05UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for CAN1_TXD   */
#define SYS_GPC_MFP3_PC13MFP_USCI0_CTL0  (0x06UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for USCI0_CTL0 */
#define SYS_GPC_MFP3_PC13MFP_UART2_TXD   (0x07UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for UART2_TXD  */
#define SYS_GPC_MFP3_PC13MFP_UART8_nCTS  (0x08UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for UART8_nCTS */
#define SYS_GPC_MFP3_PC13MFP_BPWM0_CH4   (0x09UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for BPWM0_CH4  */
#define SYS_GPC_MFP3_PC13MFP_CLKO        (0x0dUL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for CLKO       */
#define SYS_GPC_MFP3_PC13MFP_EADC0_ST    (0x0eUL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for EADC0_ST   */
#define SYS_GPC_MFP3_PC13MFP_SPI9_SS     (0x13UL<<SYS_GPC_MFP3_PC13MFP_Pos)/*!< GPC_MFP3 PC13 setting for SPI9_SS    */

/* PC.14 MFP */
#define SYS_GPC_MFP3_PC14MFP_GPIO        (0x00UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for GPIO       */
#define SYS_GPC_MFP3_PC14MFP_EBI_AD11    (0x02UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for EBI_AD11   */
#define SYS_GPC_MFP3_PC14MFP_SC1_nCD     (0x03UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for SC1_nCD    */
#define SYS_GPC_MFP3_PC14MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for SPI0_I2SMCLK*/
#define SYS_GPC_MFP3_PC14MFP_USCI0_CTL0  (0x05UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for USCI0_CTL0 */
#define SYS_GPC_MFP3_PC14MFP_QSPI0_CLK   (0x06UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for QSPI0_CLK  */
#define SYS_GPC_MFP3_PC14MFP_TRACE_SWO   (0x0aUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for TRACE_SWO  */
#define SYS_GPC_MFP3_PC14MFP_EPWM0_SYNC_IN (0x0bUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for EPWM0_SYNC_IN*/
#define SYS_GPC_MFP3_PC14MFP_ETMC_TRACE_CLK (0x0cUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for ETMC_TRACE_CLK*/
#define SYS_GPC_MFP3_PC14MFP_TM1         (0x0dUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for TM1        */
#define SYS_GPC_MFP3_PC14MFP_USB_VBUS_ST (0x0eUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for USB_VBUS_ST*/
#define SYS_GPC_MFP3_PC14MFP_HSUSB_VBUS_ST (0x0fUL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for HSUSB_VBUS_ST*/
#define SYS_GPC_MFP3_PC14MFP_SPI9_MOSI   (0x13UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for SPI9_MOSI  */
#define SYS_GPC_MFP3_PC14MFP_BMC26       (0x14UL<<SYS_GPC_MFP3_PC14MFP_Pos)/*!< GPC_MFP3 PC14 setting for BMC26      */

/* PD.0 MFP */
#define SYS_GPD_MFP0_PD0MFP_GPIO         (0x00UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for GPIO        */
#define SYS_GPD_MFP0_PD0MFP_EBI_AD13     (0x02UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for EBI_AD13    */
#define SYS_GPD_MFP0_PD0MFP_USCI0_CLK    (0x03UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for USCI0_CLK   */
#define SYS_GPD_MFP0_PD0MFP_SPI0_MOSI    (0x04UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for SPI0_MOSI   */
#define SYS_GPD_MFP0_PD0MFP_UART3_RXD    (0x05UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for UART3_RXD   */
#define SYS_GPD_MFP0_PD0MFP_I2C2_SDA     (0x06UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for I2C2_SDA    */
#define SYS_GPD_MFP0_PD0MFP_SC2_CLK      (0x07UL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for SC2_CLK     */
#define SYS_GPD_MFP0_PD0MFP_I2S1_DO      (0x0aUL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for I2S1_DO     */
#define SYS_GPD_MFP0_PD0MFP_EQEI2_A      (0x0cUL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for EQEI2_A     */
#define SYS_GPD_MFP0_PD0MFP_ECAP2_IC1    (0x0dUL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for ECAP2_IC1   */
#define SYS_GPD_MFP0_PD0MFP_TM2          (0x0eUL<<SYS_GPD_MFP0_PD0MFP_Pos) /*!< GPD_MFP0 PD0 setting for TM2         */

/* PD.1 MFP */
#define SYS_GPD_MFP0_PD1MFP_GPIO         (0x00UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for GPIO        */
#define SYS_GPD_MFP0_PD1MFP_EBI_AD12     (0x02UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for EBI_AD12    */
#define SYS_GPD_MFP0_PD1MFP_USCI0_DAT0   (0x03UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for USCI0_DAT0  */
#define SYS_GPD_MFP0_PD1MFP_SPI0_MISO    (0x04UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for SPI0_MISO   */
#define SYS_GPD_MFP0_PD1MFP_UART3_TXD    (0x05UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for UART3_TXD   */
#define SYS_GPD_MFP0_PD1MFP_I2C2_SCL     (0x06UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for I2C2_SCL    */
#define SYS_GPD_MFP0_PD1MFP_SC2_DAT      (0x07UL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for SC2_DAT     */
#define SYS_GPD_MFP0_PD1MFP_I2S1_DI      (0x0aUL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for I2S1_DI     */
#define SYS_GPD_MFP0_PD1MFP_EQEI2_INDEX  (0x0cUL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for EQEI2_INDEX */
#define SYS_GPD_MFP0_PD1MFP_ECAP2_IC0    (0x0dUL<<SYS_GPD_MFP0_PD1MFP_Pos) /*!< GPD_MFP0 PD1 setting for ECAP2_IC0   */

/* PD.2 MFP */
#define SYS_GPD_MFP0_PD2MFP_GPIO         (0x00UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for GPIO        */
#define SYS_GPD_MFP0_PD2MFP_EBI_AD11     (0x02UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for EBI_AD11    */
#define SYS_GPD_MFP0_PD2MFP_USCI0_DAT1   (0x03UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for USCI0_DAT1  */
#define SYS_GPD_MFP0_PD2MFP_SPI0_CLK     (0x04UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for SPI0_CLK    */
#define SYS_GPD_MFP0_PD2MFP_UART3_nCTS   (0x05UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for UART3_nCTS  */
#define SYS_GPD_MFP0_PD2MFP_SC2_RST      (0x07UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for SC2_RST     */
#define SYS_GPD_MFP0_PD2MFP_UART0_RXD    (0x09UL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for UART0_RXD   */
#define SYS_GPD_MFP0_PD2MFP_I2S1_MCLK    (0x0aUL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for I2S1_MCLK   */
#define SYS_GPD_MFP0_PD2MFP_EQEI3_B      (0x0dUL<<SYS_GPD_MFP0_PD2MFP_Pos) /*!< GPD_MFP0 PD2 setting for EQEI3_B     */

/* PD.3 MFP */
#define SYS_GPD_MFP0_PD3MFP_GPIO         (0x00UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for GPIO        */
#define SYS_GPD_MFP0_PD3MFP_EBI_AD10     (0x02UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for EBI_AD10    */
#define SYS_GPD_MFP0_PD3MFP_USCI0_CTL1   (0x03UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for USCI0_CTL1  */
#define SYS_GPD_MFP0_PD3MFP_SPI0_SS      (0x04UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for SPI0_SS     */
#define SYS_GPD_MFP0_PD3MFP_UART3_nRTS   (0x05UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for UART3_nRTS  */
#define SYS_GPD_MFP0_PD3MFP_SC2_PWR      (0x07UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for SC2_PWR     */
#define SYS_GPD_MFP0_PD3MFP_SC1_nCD      (0x08UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for SC1_nCD     */
#define SYS_GPD_MFP0_PD3MFP_UART0_TXD    (0x09UL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for UART0_TXD   */
#define SYS_GPD_MFP0_PD3MFP_I2S1_BCLK    (0x0aUL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for I2S1_BCLK   */
#define SYS_GPD_MFP0_PD3MFP_EQEI3_A      (0x0dUL<<SYS_GPD_MFP0_PD3MFP_Pos) /*!< GPD_MFP0 PD3 setting for EQEI3_A     */

/* PD.4 MFP */
#define SYS_GPD_MFP1_PD4MFP_GPIO         (0x00UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for GPIO        */
#define SYS_GPD_MFP1_PD4MFP_USCI0_CTL0   (0x03UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for USCI0_CTL0  */
#define SYS_GPD_MFP1_PD4MFP_I2C1_SDA     (0x04UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for I2C1_SDA    */
#define SYS_GPD_MFP1_PD4MFP_SPI1_SS      (0x05UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for SPI1_SS     */
#define SYS_GPD_MFP1_PD4MFP_SC1_CLK      (0x08UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for SC1_CLK     */
#define SYS_GPD_MFP1_PD4MFP_USB_VBUS_ST  (0x0eUL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for USB_VBUS_ST */
#define SYS_GPD_MFP1_PD4MFP_PSIO0_CH7    (0x11UL<<SYS_GPD_MFP1_PD4MFP_Pos) /*!< GPD_MFP1 PD4 setting for PSIO0_CH7   */

/* PD.5 MFP */
#define SYS_GPD_MFP1_PD5MFP_GPIO         (0x00UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for GPIO        */
#define SYS_GPD_MFP1_PD5MFP_I2C1_SCL     (0x04UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for I2C1_SCL    */
#define SYS_GPD_MFP1_PD5MFP_SPI1_CLK     (0x05UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for SPI1_CLK    */
#define SYS_GPD_MFP1_PD5MFP_SC1_DAT      (0x08UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for SC1_DAT     */
#define SYS_GPD_MFP1_PD5MFP_ACMP1_O      (0x0eUL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for ACMP1_O     */
#define SYS_GPD_MFP1_PD5MFP_EADC1_ST     (0x0fUL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for EADC1_ST    */
#define SYS_GPD_MFP1_PD5MFP_HBI_D7       (0x10UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for HBI_D7      */
#define SYS_GPD_MFP1_PD5MFP_PSIO0_CH6    (0x11UL<<SYS_GPD_MFP1_PD5MFP_Pos) /*!< GPD_MFP1 PD5 setting for PSIO0_CH6   */

/* PD.6 MFP */
#define SYS_GPD_MFP1_PD6MFP_GPIO         (0x00UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for GPIO        */
#define SYS_GPD_MFP1_PD6MFP_EBI_AD5      (0x02UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for EBI_AD5     */
#define SYS_GPD_MFP1_PD6MFP_UART1_RXD    (0x03UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for UART1_RXD   */
#define SYS_GPD_MFP1_PD6MFP_I2C0_SDA     (0x04UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for I2C0_SDA    */
#define SYS_GPD_MFP1_PD6MFP_SPI1_MOSI    (0x05UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for SPI1_MOSI   */
#define SYS_GPD_MFP1_PD6MFP_QSPI1_MOSI0  (0x06UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for QSPI1_MOSI0 */
#define SYS_GPD_MFP1_PD6MFP_SC1_RST      (0x08UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for SC1_RST     */
#define SYS_GPD_MFP1_PD6MFP_ACMP0_O      (0x0eUL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for ACMP0_O     */
#define SYS_GPD_MFP1_PD6MFP_EADC0_ST     (0x0fUL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for EADC0_ST    */
#define SYS_GPD_MFP1_PD6MFP_HBI_D6       (0x10UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for HBI_D6      */
#define SYS_GPD_MFP1_PD6MFP_PSIO0_CH5    (0x11UL<<SYS_GPD_MFP1_PD6MFP_Pos) /*!< GPD_MFP1 PD6 setting for PSIO0_CH5   */

/* PD.7 MFP */
#define SYS_GPD_MFP1_PD7MFP_GPIO         (0x00UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for GPIO        */
#define SYS_GPD_MFP1_PD7MFP_EBI_AD4      (0x02UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for EBI_AD4     */
#define SYS_GPD_MFP1_PD7MFP_UART1_TXD    (0x03UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for UART1_TXD   */
#define SYS_GPD_MFP1_PD7MFP_I2C0_SCL     (0x04UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for I2C0_SCL    */
#define SYS_GPD_MFP1_PD7MFP_SPI1_MISO    (0x05UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for SPI1_MISO   */
#define SYS_GPD_MFP1_PD7MFP_QSPI1_MISO0  (0x06UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for QSPI1_MISO0 */
#define SYS_GPD_MFP1_PD7MFP_CCAP_HSYNC   (0x07UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for CCAP_HSYNC  */
#define SYS_GPD_MFP1_PD7MFP_SC1_PWR      (0x08UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for SC1_PWR     */
#define SYS_GPD_MFP1_PD7MFP_HBI_D5       (0x10UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for HBI_D5      */
#define SYS_GPD_MFP1_PD7MFP_PSIO0_CH4    (0x11UL<<SYS_GPD_MFP1_PD7MFP_Pos) /*!< GPD_MFP1 PD7 setting for PSIO0_CH4   */

/* PD.8 MFP */
#define SYS_GPD_MFP2_PD8MFP_GPIO         (0x00UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for GPIO        */
#define SYS_GPD_MFP2_PD8MFP_EBI_AD6      (0x02UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for EBI_AD6     */
#define SYS_GPD_MFP2_PD8MFP_I2C2_SDA     (0x03UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for I2C2_SDA    */
#define SYS_GPD_MFP2_PD8MFP_UART2_nRTS   (0x04UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for UART2_nRTS  */
#define SYS_GPD_MFP2_PD8MFP_UART7_RXD    (0x05UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for UART7_RXD   */
#define SYS_GPD_MFP2_PD8MFP_CAN2_RXD     (0x06UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for CAN2_RXD    */
#define SYS_GPD_MFP2_PD8MFP_PSIO0_CH3    (0x11UL<<SYS_GPD_MFP2_PD8MFP_Pos) /*!< GPD_MFP2 PD8 setting for PSIO0_CH3   */

/* PD.9 MFP */
#define SYS_GPD_MFP2_PD9MFP_GPIO         (0x00UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for GPIO        */
#define SYS_GPD_MFP2_PD9MFP_EBI_AD7      (0x02UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for EBI_AD7     */
#define SYS_GPD_MFP2_PD9MFP_I2C2_SCL     (0x03UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for I2C2_SCL    */
#define SYS_GPD_MFP2_PD9MFP_UART2_nCTS   (0x04UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for UART2_nCTS  */
#define SYS_GPD_MFP2_PD9MFP_UART7_TXD    (0x05UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for UART7_TXD   */
#define SYS_GPD_MFP2_PD9MFP_CAN2_TXD     (0x06UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for CAN2_TXD    */
#define SYS_GPD_MFP2_PD9MFP_PSIO0_CH2    (0x11UL<<SYS_GPD_MFP2_PD9MFP_Pos) /*!< GPD_MFP2 PD9 setting for PSIO0_CH2   */

/* PD.10 MFP */
#define SYS_GPD_MFP2_PD10MFP_GPIO        (0x00UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for GPIO       */
#define SYS_GPD_MFP2_PD10MFP_EADC1_CH0   (0x01UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for EADC1_CH0  */
#define SYS_GPD_MFP2_PD10MFP_EADC2_CH0   (0x01UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for EADC2_CH0  */
#define SYS_GPD_MFP2_PD10MFP_EBI_nCS2    (0x02UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for EBI_nCS2   */
#define SYS_GPD_MFP2_PD10MFP_UART1_RXD   (0x03UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for UART1_RXD  */
#define SYS_GPD_MFP2_PD10MFP_CAN0_RXD    (0x04UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for CAN0_RXD   */
#define SYS_GPD_MFP2_PD10MFP_UART8_RXD   (0x08UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for UART8_RXD  */
#define SYS_GPD_MFP2_PD10MFP_EQEI0_B     (0x0aUL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for EQEI0_B    */
#define SYS_GPD_MFP2_PD10MFP_ECAP3_IC2   (0x0bUL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for ECAP3_IC2  */
#define SYS_GPD_MFP2_PD10MFP_INT7        (0x0fUL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for INT7       */
#define SYS_GPD_MFP2_PD10MFP_SPI9_MOSI   (0x13UL<<SYS_GPD_MFP2_PD10MFP_Pos)/*!< GPD_MFP2 PD10 setting for SPI9_MOSI  */

/* PD.11 MFP */
#define SYS_GPD_MFP2_PD11MFP_GPIO        (0x00UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for GPIO       */
#define SYS_GPD_MFP2_PD11MFP_EADC1_CH1   (0x01UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for EADC1_CH1  */
#define SYS_GPD_MFP2_PD11MFP_EADC2_CH1   (0x01UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for EADC2_CH1  */
#define SYS_GPD_MFP2_PD11MFP_EBI_nCS1    (0x02UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for EBI_nCS1   */
#define SYS_GPD_MFP2_PD11MFP_UART1_TXD   (0x03UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for UART1_TXD  */
#define SYS_GPD_MFP2_PD11MFP_CAN0_TXD    (0x04UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for CAN0_TXD   */
#define SYS_GPD_MFP2_PD11MFP_UART8_TXD   (0x08UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for UART8_TXD  */
#define SYS_GPD_MFP2_PD11MFP_EQEI0_A     (0x0aUL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for EQEI0_A    */
#define SYS_GPD_MFP2_PD11MFP_ECAP3_IC1   (0x0bUL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for ECAP3_IC1  */
#define SYS_GPD_MFP2_PD11MFP_INT6        (0x0fUL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for INT6       */
#define SYS_GPD_MFP2_PD11MFP_SPI9_MISO   (0x13UL<<SYS_GPD_MFP2_PD11MFP_Pos)/*!< GPD_MFP2 PD11 setting for SPI9_MISO  */

/* PD.12 MFP */
#define SYS_GPD_MFP3_PD12MFP_GPIO        (0x00UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for GPIO       */
#define SYS_GPD_MFP3_PD12MFP_EADC1_CH2   (0x01UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for EADC1_CH2  */
#define SYS_GPD_MFP3_PD12MFP_EADC2_CH2   (0x01UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for EADC2_CH2  */
#define SYS_GPD_MFP3_PD12MFP_EBI_nCS0    (0x02UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for EBI_nCS0   */
#define SYS_GPD_MFP3_PD12MFP_CAN1_RXD    (0x05UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for CAN1_RXD   */
#define SYS_GPD_MFP3_PD12MFP_UART2_RXD   (0x07UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for UART2_RXD  */
#define SYS_GPD_MFP3_PD12MFP_UART8_nRTS  (0x08UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for UART8_nRTS */
#define SYS_GPD_MFP3_PD12MFP_BPWM0_CH5   (0x09UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for BPWM0_CH5  */
#define SYS_GPD_MFP3_PD12MFP_EQEI0_INDEX (0x0aUL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for EQEI0_INDEX */
#define SYS_GPD_MFP3_PD12MFP_ECAP3_IC0   (0x0bUL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for ECAP3_IC0  */
#define SYS_GPD_MFP3_PD12MFP_CLKO        (0x0dUL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for CLKO       */
#define SYS_GPD_MFP3_PD12MFP_EADC0_ST    (0x0eUL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for EADC0_ST   */
#define SYS_GPD_MFP3_PD12MFP_INT5        (0x0fUL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for INT5       */
#define SYS_GPD_MFP3_PD12MFP_SPI9_CLK    (0x13UL<<SYS_GPD_MFP3_PD12MFP_Pos)/*!< GPD_MFP3 PD12 setting for SPI9_CLK   */

/* PD.13 MFP */
#define SYS_GPD_MFP3_PD13MFP_GPIO        (0x00UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for GPIO       */
#define SYS_GPD_MFP3_PD13MFP_EBI_AD10    (0x02UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for EBI_AD10   */
#define SYS_GPD_MFP3_PD13MFP_SD0_nCD     (0x03UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for SD0_nCD    */
#define SYS_GPD_MFP3_PD13MFP_SPI0_I2SMCLK (0x04UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for SPI0_I2SMCLK*/
#define SYS_GPD_MFP3_PD13MFP_SPI1_I2SMCLK (0x05UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for SPI1_I2SMCLK*/
#define SYS_GPD_MFP3_PD13MFP_QSPI1_MOSI0 (0x06UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for QSPI1_MOSI0*/
#define SYS_GPD_MFP3_PD13MFP_SC2_nCD     (0x07UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for SC2_nCD    */
#define SYS_GPD_MFP3_PD13MFP_SD1_CLK     (0x08UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for SD1_CLK    */
#define SYS_GPD_MFP3_PD13MFP_UART6_RXD   (0x09UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for UART6_RXD  */
#define SYS_GPD_MFP3_PD13MFP_I2S1_LRCK   (0x0aUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for I2S1_LRCK  */
#define SYS_GPD_MFP3_PD13MFP_BPWM0_CH0   (0x0bUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for BPWM0_CH0  */
#define SYS_GPD_MFP3_PD13MFP_EQEI2_B     (0x0cUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for EQEI2_B    */
#define SYS_GPD_MFP3_PD13MFP_ECAP2_IC2   (0x0dUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for ECAP2_IC2  */
#define SYS_GPD_MFP3_PD13MFP_CLKO        (0x0eUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for CLKO       */
#define SYS_GPD_MFP3_PD13MFP_EADC0_ST    (0x0fUL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for EADC0_ST   */
#define SYS_GPD_MFP3_PD13MFP_QSPI1_MOSI1 (0x13UL<<SYS_GPD_MFP3_PD13MFP_Pos)/*!< GPD_MFP3 PD13 setting for QSPI1_MOSI1*/

/* PD.14 MFP */
#define SYS_GPD_MFP3_PD14MFP_GPIO        (0x00UL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for GPIO       */
#define SYS_GPD_MFP3_PD14MFP_EBI_nCS0    (0x02UL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for EBI_nCS0   */
#define SYS_GPD_MFP3_PD14MFP_SPI3_I2SMCLK (0x03UL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for SPI3_I2SMCLK*/
#define SYS_GPD_MFP3_PD14MFP_SC1_nCD     (0x04UL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for SC1_nCD    */
#define SYS_GPD_MFP3_PD14MFP_SPI0_I2SMCLK (0x05UL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for SPI0_I2SMCLK*/
#define SYS_GPD_MFP3_PD14MFP_I2S1_BCLK   (0x0aUL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for I2S1_BCLK  */
#define SYS_GPD_MFP3_PD14MFP_EPWM0_CH4   (0x0bUL<<SYS_GPD_MFP3_PD14MFP_Pos)/*!< GPD_MFP3 PD14 setting for EPWM0_CH4  */

/* PE.0 MFP */
#define SYS_GPE_MFP0_PE0MFP_GPIO         (0x00UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for GPIO        */
#define SYS_GPE_MFP0_PE0MFP_EBI_AD11     (0x02UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for EBI_AD11    */
#define SYS_GPE_MFP0_PE0MFP_QSPI0_MOSI0  (0x03UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for QSPI0_MOSI0 */
#define SYS_GPE_MFP0_PE0MFP_SC2_CLK      (0x04UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for SC2_CLK     */
#define SYS_GPE_MFP0_PE0MFP_I2S0_MCLK    (0x05UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for I2S0_MCLK   */
#define SYS_GPE_MFP0_PE0MFP_SPI1_MOSI    (0x06UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for SPI1_MOSI   */
#define SYS_GPE_MFP0_PE0MFP_UART3_RXD    (0x07UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for UART3_RXD   */
#define SYS_GPE_MFP0_PE0MFP_I2C1_SDA     (0x08UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for I2C1_SDA    */
#define SYS_GPE_MFP0_PE0MFP_UART4_nRTS   (0x09UL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for UART4_nRTS  */
#define SYS_GPE_MFP0_PE0MFP_UART8_RXD    (0x0aUL<<SYS_GPE_MFP0_PE0MFP_Pos) /*!< GPE_MFP0 PE0 setting for UART8_RXD   */

/* PE.1 MFP */
#define SYS_GPE_MFP0_PE1MFP_GPIO         (0x00UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for GPIO        */
#define SYS_GPE_MFP0_PE1MFP_EBI_AD10     (0x02UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for EBI_AD10    */
#define SYS_GPE_MFP0_PE1MFP_QSPI0_MISO0  (0x03UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for QSPI0_MISO0 */
#define SYS_GPE_MFP0_PE1MFP_SC2_DAT      (0x04UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for SC2_DAT     */
#define SYS_GPE_MFP0_PE1MFP_I2S0_BCLK    (0x05UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for I2S0_BCLK   */
#define SYS_GPE_MFP0_PE1MFP_SPI1_MISO    (0x06UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for SPI1_MISO   */
#define SYS_GPE_MFP0_PE1MFP_UART3_TXD    (0x07UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for UART3_TXD   */
#define SYS_GPE_MFP0_PE1MFP_I2C1_SCL     (0x08UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for I2C1_SCL    */
#define SYS_GPE_MFP0_PE1MFP_UART4_nCTS   (0x09UL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for UART4_nCTS  */
#define SYS_GPE_MFP0_PE1MFP_UART8_TXD    (0x0aUL<<SYS_GPE_MFP0_PE1MFP_Pos) /*!< GPE_MFP0 PE1 setting for UART8_TXD   */

/* PE.2 MFP */
#define SYS_GPE_MFP0_PE2MFP_GPIO         (0x00UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for GPIO        */
#define SYS_GPE_MFP0_PE2MFP_EBI_ALE      (0x02UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for EBI_ALE     */
#define SYS_GPE_MFP0_PE2MFP_SD0_DAT0     (0x03UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for SD0_DAT0    */
#define SYS_GPE_MFP0_PE2MFP_SPIM_MOSI    (0x04UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for SPIM_MOSI   */
#define SYS_GPE_MFP0_PE2MFP_SPI3_MOSI    (0x05UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for SPI3_MOSI   */
#define SYS_GPE_MFP0_PE2MFP_SC0_CLK      (0x06UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for SC0_CLK     */
#define SYS_GPE_MFP0_PE2MFP_USCI0_CLK    (0x07UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for USCI0_CLK   */
#define SYS_GPE_MFP0_PE2MFP_UART6_nCTS   (0x08UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for UART6_nCTS  */
#define SYS_GPE_MFP0_PE2MFP_UART7_RXD    (0x09UL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for UART7_RXD   */
#define SYS_GPE_MFP0_PE2MFP_UART8_nRTS   (0x0aUL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for UART8_nRTS  */
#define SYS_GPE_MFP0_PE2MFP_EQEI0_B      (0x0bUL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for EQEI0_B     */
#define SYS_GPE_MFP0_PE2MFP_EPWM0_CH5    (0x0cUL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for EPWM0_CH5   */
#define SYS_GPE_MFP0_PE2MFP_BPWM0_CH0    (0x0dUL<<SYS_GPE_MFP0_PE2MFP_Pos) /*!< GPE_MFP0 PE2 setting for BPWM0_CH0   */

/* PE.3 MFP */
#define SYS_GPE_MFP0_PE3MFP_GPIO         (0x00UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for GPIO        */
#define SYS_GPE_MFP0_PE3MFP_EBI_MCLK     (0x02UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for EBI_MCLK    */
#define SYS_GPE_MFP0_PE3MFP_SD0_DAT1     (0x03UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for SD0_DAT1    */
#define SYS_GPE_MFP0_PE3MFP_SPIM_MISO    (0x04UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for SPIM_MISO   */
#define SYS_GPE_MFP0_PE3MFP_SPI3_MISO    (0x05UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for SPI3_MISO   */
#define SYS_GPE_MFP0_PE3MFP_SC0_DAT      (0x06UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for SC0_DAT     */
#define SYS_GPE_MFP0_PE3MFP_USCI0_DAT0   (0x07UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for USCI0_DAT0  */
#define SYS_GPE_MFP0_PE3MFP_UART6_nRTS   (0x08UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for UART6_nRTS  */
#define SYS_GPE_MFP0_PE3MFP_UART7_TXD    (0x09UL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for UART7_TXD   */
#define SYS_GPE_MFP0_PE3MFP_UART8_nCTS   (0x0aUL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for UART8_nCTS  */
#define SYS_GPE_MFP0_PE3MFP_EQEI0_A      (0x0bUL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for EQEI0_A     */
#define SYS_GPE_MFP0_PE3MFP_EPWM0_CH4    (0x0cUL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for EPWM0_CH4   */
#define SYS_GPE_MFP0_PE3MFP_BPWM0_CH1    (0x0dUL<<SYS_GPE_MFP0_PE3MFP_Pos) /*!< GPE_MFP0 PE3 setting for BPWM0_CH1   */

/* PE.4 MFP */
#define SYS_GPE_MFP1_PE4MFP_GPIO         (0x00UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for GPIO        */
#define SYS_GPE_MFP1_PE4MFP_EBI_nWR      (0x02UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for EBI_nWR     */
#define SYS_GPE_MFP1_PE4MFP_SD0_DAT2     (0x03UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for SD0_DAT2    */
#define SYS_GPE_MFP1_PE4MFP_SPIM_CLK     (0x04UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for SPIM_CLK    */
#define SYS_GPE_MFP1_PE4MFP_SPI3_CLK     (0x05UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for SPI3_CLK    */
#define SYS_GPE_MFP1_PE4MFP_SC0_RST      (0x06UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for SC0_RST     */
#define SYS_GPE_MFP1_PE4MFP_USCI0_DAT1   (0x07UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for USCI0_DAT1  */
#define SYS_GPE_MFP1_PE4MFP_UART6_RXD    (0x08UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for UART6_RXD   */
#define SYS_GPE_MFP1_PE4MFP_UART7_nCTS   (0x09UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for UART7_nCTS  */
#define SYS_GPE_MFP1_PE4MFP_UART9_RXD    (0x0aUL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for UART9_RXD   */
#define SYS_GPE_MFP1_PE4MFP_EQEI0_INDEX  (0x0bUL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for EQEI0_INDEX */
#define SYS_GPE_MFP1_PE4MFP_EPWM0_CH3    (0x0cUL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for EPWM0_CH3   */
#define SYS_GPE_MFP1_PE4MFP_BPWM0_CH2    (0x0dUL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for BPWM0_CH2   */
#define SYS_GPE_MFP1_PE4MFP_PSIO0_CH3    (0x11UL<<SYS_GPE_MFP1_PE4MFP_Pos) /*!< GPE_MFP1 PE4 setting for PSIO0_CH3   */

/* PE.5 MFP */
#define SYS_GPE_MFP1_PE5MFP_GPIO         (0x00UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for GPIO        */
#define SYS_GPE_MFP1_PE5MFP_EBI_nRD      (0x02UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for EBI_nRD     */
#define SYS_GPE_MFP1_PE5MFP_SD0_DAT3     (0x03UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for SD0_DAT3    */
#define SYS_GPE_MFP1_PE5MFP_SPIM_SS      (0x04UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for SPIM_SS     */
#define SYS_GPE_MFP1_PE5MFP_SPI3_SS      (0x05UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for SPI3_SS     */
#define SYS_GPE_MFP1_PE5MFP_SC0_PWR      (0x06UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for SC0_PWR     */
#define SYS_GPE_MFP1_PE5MFP_USCI0_CTL1   (0x07UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for USCI0_CTL1  */
#define SYS_GPE_MFP1_PE5MFP_UART6_TXD    (0x08UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for UART6_TXD   */
#define SYS_GPE_MFP1_PE5MFP_UART7_nRTS   (0x09UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for UART7_nRTS  */
#define SYS_GPE_MFP1_PE5MFP_UART9_TXD    (0x0aUL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for UART9_TXD   */
#define SYS_GPE_MFP1_PE5MFP_EQEI1_B      (0x0bUL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for EQEI1_B     */
#define SYS_GPE_MFP1_PE5MFP_EPWM0_CH2    (0x0cUL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for EPWM0_CH2   */
#define SYS_GPE_MFP1_PE5MFP_BPWM0_CH3    (0x0dUL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for BPWM0_CH3   */
#define SYS_GPE_MFP1_PE5MFP_PSIO0_CH2    (0x11UL<<SYS_GPE_MFP1_PE5MFP_Pos) /*!< GPE_MFP1 PE5 setting for PSIO0_CH2   */

/* PE.6 MFP */
#define SYS_GPE_MFP1_PE6MFP_GPIO         (0x00UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for GPIO        */
#define SYS_GPE_MFP1_PE6MFP_SD0_CLK      (0x03UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for SD0_CLK     */
#define SYS_GPE_MFP1_PE6MFP_SPIM_D3      (0x04UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for SPIM_D3     */
#define SYS_GPE_MFP1_PE6MFP_SPI3_I2SMCLK (0x05UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for SPI3_I2SMCLK*/
#define SYS_GPE_MFP1_PE6MFP_SC0_nCD      (0x06UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for SC0_nCD     */
#define SYS_GPE_MFP1_PE6MFP_USCI0_CTL0   (0x07UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for USCI0_CTL0  */
#define SYS_GPE_MFP1_PE6MFP_UART5_RXD    (0x08UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for UART5_RXD   */
#define SYS_GPE_MFP1_PE6MFP_CAN1_RXD     (0x09UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for CAN1_RXD    */
#define SYS_GPE_MFP1_PE6MFP_UART9_nRTS   (0x0aUL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for UART9_nRTS  */
#define SYS_GPE_MFP1_PE6MFP_EQEI1_A      (0x0bUL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for EQEI1_A     */
#define SYS_GPE_MFP1_PE6MFP_EPWM0_CH1    (0x0cUL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for EPWM0_CH1   */
#define SYS_GPE_MFP1_PE6MFP_BPWM0_CH4    (0x0dUL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for BPWM0_CH4   */
#define SYS_GPE_MFP1_PE6MFP_ACMP3_O      (0x0eUL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for ACMP3_O     */
#define SYS_GPE_MFP1_PE6MFP_PSIO0_CH1    (0x11UL<<SYS_GPE_MFP1_PE6MFP_Pos) /*!< GPE_MFP1 PE6 setting for PSIO0_CH1   */

/* PE.7 MFP */
#define SYS_GPE_MFP1_PE7MFP_GPIO         (0x00UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for GPIO        */
#define SYS_GPE_MFP1_PE7MFP_SD0_CMD      (0x03UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for SD0_CMD     */
#define SYS_GPE_MFP1_PE7MFP_SPIM_D2      (0x04UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for SPIM_D2     */
#define SYS_GPE_MFP1_PE7MFP_UART5_TXD    (0x08UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for UART5_TXD   */
#define SYS_GPE_MFP1_PE7MFP_CAN1_TXD     (0x09UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for CAN1_TXD    */
#define SYS_GPE_MFP1_PE7MFP_UART9_nCTS   (0x0aUL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for UART9_nCTS  */
#define SYS_GPE_MFP1_PE7MFP_EQEI1_INDEX  (0x0bUL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for EQEI1_INDEX */
#define SYS_GPE_MFP1_PE7MFP_EPWM0_CH0    (0x0cUL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for EPWM0_CH0   */
#define SYS_GPE_MFP1_PE7MFP_BPWM0_CH5    (0x0dUL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for BPWM0_CH5   */
#define SYS_GPE_MFP1_PE7MFP_ACMP2_O      (0x0eUL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for ACMP2_O     */
#define SYS_GPE_MFP1_PE7MFP_PSIO0_CH0    (0x11UL<<SYS_GPE_MFP1_PE7MFP_Pos) /*!< GPE_MFP1 PE7 setting for PSIO0_CH0   */

/* PE.8 MFP */
#define SYS_GPE_MFP2_PE8MFP_GPIO         (0x00UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for GPIO        */
#define SYS_GPE_MFP2_PE8MFP_EBI_ADR10    (0x02UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for EBI_ADR10   */
#define SYS_GPE_MFP2_PE8MFP_EMAC0_RMII_MDC (0x03UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for EMAC0_RMII_MDC*/
#define SYS_GPE_MFP2_PE8MFP_I2S0_BCLK    (0x04UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for I2S0_BCLK   */
#define SYS_GPE_MFP2_PE8MFP_SPI2_CLK     (0x05UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for SPI2_CLK    */
#define SYS_GPE_MFP2_PE8MFP_UART2_TXD    (0x07UL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for UART2_TXD   */
#define SYS_GPE_MFP2_PE8MFP_EPWM0_CH0    (0x0aUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for EPWM0_CH0   */
#define SYS_GPE_MFP2_PE8MFP_EPWM0_BRAKE0 (0x0bUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for EPWM0_BRAKE0*/
#define SYS_GPE_MFP2_PE8MFP_ECAP0_IC0    (0x0cUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for ECAP0_IC0   */
#define SYS_GPE_MFP2_PE8MFP_EQEI2_INDEX  (0x0dUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for EQEI2_INDEX */
#define SYS_GPE_MFP2_PE8MFP_TRACE_DATA3  (0x0eUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for TRACE_DATA3 */
#define SYS_GPE_MFP2_PE8MFP_ECAP3_IC0    (0x0fUL<<SYS_GPE_MFP2_PE8MFP_Pos) /*!< GPE_MFP2 PE8 setting for ECAP3_IC0   */

/* PE.9 MFP */
#define SYS_GPE_MFP2_PE9MFP_GPIO         (0x00UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for GPIO        */
#define SYS_GPE_MFP2_PE9MFP_EBI_ADR11    (0x02UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for EBI_ADR11   */
#define SYS_GPE_MFP2_PE9MFP_EMAC0_RMII_MDIO (0x03UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for EMAC0_RMII_MDIO*/
#define SYS_GPE_MFP2_PE9MFP_I2S0_MCLK    (0x04UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for I2S0_MCLK   */
#define SYS_GPE_MFP2_PE9MFP_SPI2_MISO    (0x05UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for SPI2_MISO   */
#define SYS_GPE_MFP2_PE9MFP_UART2_RXD    (0x07UL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for UART2_RXD   */
#define SYS_GPE_MFP2_PE9MFP_EPWM0_CH1    (0x0aUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for EPWM0_CH1   */
#define SYS_GPE_MFP2_PE9MFP_EPWM0_BRAKE1 (0x0bUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for EPWM0_BRAKE1*/
#define SYS_GPE_MFP2_PE9MFP_ECAP0_IC1    (0x0cUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for ECAP0_IC1   */
#define SYS_GPE_MFP2_PE9MFP_EQEI2_A      (0x0dUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for EQEI2_A     */
#define SYS_GPE_MFP2_PE9MFP_TRACE_DATA2  (0x0eUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for TRACE_DATA2 */
#define SYS_GPE_MFP2_PE9MFP_ECAP3_IC1    (0x0fUL<<SYS_GPE_MFP2_PE9MFP_Pos) /*!< GPE_MFP2 PE9 setting for ECAP3_IC1   */

/* PE.10 MFP */
#define SYS_GPE_MFP2_PE10MFP_GPIO        (0x00UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for GPIO       */
#define SYS_GPE_MFP2_PE10MFP_EBI_ADR12   (0x02UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for EBI_ADR12  */
#define SYS_GPE_MFP2_PE10MFP_EMAC0_RMII_TXD0 (0x03UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for EMAC0_RMII_TXD0*/
#define SYS_GPE_MFP2_PE10MFP_I2S0_DI     (0x04UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for I2S0_DI    */
#define SYS_GPE_MFP2_PE10MFP_SPI2_MOSI   (0x05UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for SPI2_MOSI  */
#define SYS_GPE_MFP2_PE10MFP_UART3_TXD   (0x07UL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for UART3_TXD  */
#define SYS_GPE_MFP2_PE10MFP_EPWM0_CH2   (0x0aUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for EPWM0_CH2  */
#define SYS_GPE_MFP2_PE10MFP_EPWM1_BRAKE0 (0x0bUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for EPWM1_BRAKE0*/
#define SYS_GPE_MFP2_PE10MFP_ECAP0_IC2   (0x0cUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for ECAP0_IC2  */
#define SYS_GPE_MFP2_PE10MFP_EQEI2_B     (0x0dUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for EQEI2_B    */
#define SYS_GPE_MFP2_PE10MFP_TRACE_DATA1 (0x0eUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for TRACE_DATA1*/
#define SYS_GPE_MFP2_PE10MFP_ECAP3_IC2   (0x0fUL<<SYS_GPE_MFP2_PE10MFP_Pos)/*!< GPE_MFP2 PE10 setting for ECAP3_IC2  */

/* PE.11 MFP */
#define SYS_GPE_MFP2_PE11MFP_GPIO        (0x00UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for GPIO       */
#define SYS_GPE_MFP2_PE11MFP_EBI_ADR13   (0x02UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for EBI_ADR13  */
#define SYS_GPE_MFP2_PE11MFP_EMAC0_RMII_TXD1 (0x03UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for EMAC0_RMII_TXD1*/
#define SYS_GPE_MFP2_PE11MFP_I2S0_DO     (0x04UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for I2S0_DO    */
#define SYS_GPE_MFP2_PE11MFP_SPI2_SS     (0x05UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for SPI2_SS    */
#define SYS_GPE_MFP2_PE11MFP_UART3_RXD   (0x07UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for UART3_RXD  */
#define SYS_GPE_MFP2_PE11MFP_UART1_nCTS  (0x08UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for UART1_nCTS */
#define SYS_GPE_MFP2_PE11MFP_EPWM0_CH3   (0x0aUL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for EPWM0_CH3  */
#define SYS_GPE_MFP2_PE11MFP_EPWM1_BRAKE1 (0x0bUL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for EPWM1_BRAKE1*/
#define SYS_GPE_MFP2_PE11MFP_ECAP1_IC2   (0x0dUL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for ECAP1_IC2  */
#define SYS_GPE_MFP2_PE11MFP_TRACE_DATA0 (0x0eUL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for TRACE_DATA0*/
#define SYS_GPE_MFP2_PE11MFP_KPI_COL7    (0x12UL<<SYS_GPE_MFP2_PE11MFP_Pos)/*!< GPE_MFP2 PE11 setting for KPI_COL7   */

/* PE.12 MFP */
#define SYS_GPE_MFP3_PE12MFP_GPIO        (0x00UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for GPIO       */
#define SYS_GPE_MFP3_PE12MFP_EBI_ADR14   (0x02UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for EBI_ADR14  */
#define SYS_GPE_MFP3_PE12MFP_EMAC0_RMII_TXEN (0x03UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for EMAC0_RMII_TXEN*/
#define SYS_GPE_MFP3_PE12MFP_I2S0_LRCK   (0x04UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for I2S0_LRCK  */
#define SYS_GPE_MFP3_PE12MFP_SPI2_I2SMCLK (0x05UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for SPI2_I2SMCLK*/
#define SYS_GPE_MFP3_PE12MFP_UART1_nRTS  (0x08UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for UART1_nRTS */
#define SYS_GPE_MFP3_PE12MFP_EPWM0_CH4   (0x0aUL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for EPWM0_CH4  */
#define SYS_GPE_MFP3_PE12MFP_ECAP1_IC1   (0x0dUL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for ECAP1_IC1  */
#define SYS_GPE_MFP3_PE12MFP_TRACE_CLK   (0x0eUL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for TRACE_CLK  */
#define SYS_GPE_MFP3_PE12MFP_KPI_COL6    (0x12UL<<SYS_GPE_MFP3_PE12MFP_Pos)/*!< GPE_MFP3 PE12 setting for KPI_COL6   */

/* PE.13 MFP */
#define SYS_GPE_MFP3_PE13MFP_GPIO        (0x00UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for GPIO       */
#define SYS_GPE_MFP3_PE13MFP_EBI_ADR15   (0x02UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for EBI_ADR15  */
#define SYS_GPE_MFP3_PE13MFP_EMAC0_PPS   (0x03UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for EMAC0_PPS  */
#define SYS_GPE_MFP3_PE13MFP_I2C0_SCL    (0x04UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for I2C0_SCL   */
#define SYS_GPE_MFP3_PE13MFP_UART4_nRTS  (0x05UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for UART4_nRTS */
#define SYS_GPE_MFP3_PE13MFP_UART1_TXD   (0x08UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for UART1_TXD  */
#define SYS_GPE_MFP3_PE13MFP_EPWM0_CH5   (0x0aUL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for EPWM0_CH5  */
#define SYS_GPE_MFP3_PE13MFP_EPWM1_CH0   (0x0bUL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for EPWM1_CH0  */
#define SYS_GPE_MFP3_PE13MFP_BPWM1_CH5   (0x0cUL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for BPWM1_CH5  */
#define SYS_GPE_MFP3_PE13MFP_ECAP1_IC0   (0x0dUL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for ECAP1_IC0  */
#define SYS_GPE_MFP3_PE13MFP_TRACE_SWO   (0x0eUL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for TRACE_SWO  */
#define SYS_GPE_MFP3_PE13MFP_KPI_COL5    (0x12UL<<SYS_GPE_MFP3_PE13MFP_Pos)/*!< GPE_MFP3 PE13 setting for KPI_COL5   */

/* PE.14 MFP */
#define SYS_GPE_MFP3_PE14MFP_GPIO        (0x00UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for GPIO       */
#define SYS_GPE_MFP3_PE14MFP_EBI_AD8     (0x02UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for EBI_AD8    */
#define SYS_GPE_MFP3_PE14MFP_UART2_TXD   (0x03UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for UART2_TXD  */
#define SYS_GPE_MFP3_PE14MFP_CAN0_TXD    (0x04UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for CAN0_TXD   */
#define SYS_GPE_MFP3_PE14MFP_SD1_nCD     (0x05UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for SD1_nCD    */
#define SYS_GPE_MFP3_PE14MFP_UART6_TXD   (0x06UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for UART6_TXD  */
#define SYS_GPE_MFP3_PE14MFP_PSIO0_CH0   (0x11UL<<SYS_GPE_MFP3_PE14MFP_Pos)/*!< GPE_MFP3 PE14 setting for PSIO0_CH0  */

/* PE.15 MFP */
#define SYS_GPE_MFP3_PE15MFP_GPIO        (0x00UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for GPIO       */
#define SYS_GPE_MFP3_PE15MFP_EBI_AD9     (0x02UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for EBI_AD9    */
#define SYS_GPE_MFP3_PE15MFP_UART2_RXD   (0x03UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for UART2_RXD  */
#define SYS_GPE_MFP3_PE15MFP_CAN0_RXD    (0x04UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for CAN0_RXD   */
#define SYS_GPE_MFP3_PE15MFP_UART6_RXD   (0x06UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for UART6_RXD  */
#define SYS_GPE_MFP3_PE15MFP_PSIO0_CH1   (0x11UL<<SYS_GPE_MFP3_PE15MFP_Pos)/*!< GPE_MFP3 PE15 setting for PSIO0_CH1  */

/* PF.0 MFP */
#define SYS_GPF_MFP0_PF0MFP_GPIO         (0x00UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for GPIO        */
#define SYS_GPF_MFP0_PF0MFP_UART1_TXD    (0x02UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for UART1_TXD   */
#define SYS_GPF_MFP0_PF0MFP_I2C1_SCL     (0x03UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for I2C1_SCL    */
#define SYS_GPF_MFP0_PF0MFP_UART0_TXD    (0x04UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for UART0_TXD   */
#define SYS_GPF_MFP0_PF0MFP_SC1_DAT      (0x05UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for SC1_DAT     */
#define SYS_GPF_MFP0_PF0MFP_I2S0_DO      (0x06UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for I2S0_DO     */
#define SYS_GPF_MFP0_PF0MFP_UART2_TXD    (0x08UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for UART2_TXD   */
#define SYS_GPF_MFP0_PF0MFP_I2C0_SCL     (0x09UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for I2C0_SCL    */
#define SYS_GPF_MFP0_PF0MFP_CAN2_TXD     (0x0aUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for CAN2_TXD    */
#define SYS_GPF_MFP0_PF0MFP_EPWM1_CH4    (0x0bUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for EPWM1_CH4   */
#define SYS_GPF_MFP0_PF0MFP_BPWM1_CH0    (0x0cUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for BPWM1_CH0   */
#define SYS_GPF_MFP0_PF0MFP_ACMP0_O      (0x0dUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for ACMP0_O     */
#define SYS_GPF_MFP0_PF0MFP_ICE_DAT      (0x0eUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for ICE_DAT     */
#define SYS_GPF_MFP0_PF0MFP_EADC0_ST     (0x0fUL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for EADC0_ST    */
#define SYS_GPF_MFP0_PF0MFP_QSPI1_MISO0  (0x13UL<<SYS_GPF_MFP0_PF0MFP_Pos) /*!< GPF_MFP0 PF0 setting for QSPI1_MISO0 */

/* PF.1 MFP */
#define SYS_GPF_MFP0_PF1MFP_GPIO         (0x00UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for GPIO        */
#define SYS_GPF_MFP0_PF1MFP_UART1_RXD    (0x02UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for UART1_RXD   */
#define SYS_GPF_MFP0_PF1MFP_I2C1_SDA     (0x03UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for I2C1_SDA    */
#define SYS_GPF_MFP0_PF1MFP_UART0_RXD    (0x04UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for UART0_RXD   */
#define SYS_GPF_MFP0_PF1MFP_SC1_CLK      (0x05UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for SC1_CLK     */
#define SYS_GPF_MFP0_PF1MFP_I2S0_LRCK    (0x06UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for I2S0_LRCK   */
#define SYS_GPF_MFP0_PF1MFP_UART2_RXD    (0x08UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for UART2_RXD   */
#define SYS_GPF_MFP0_PF1MFP_I2C0_SDA     (0x09UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for I2C0_SDA    */
#define SYS_GPF_MFP0_PF1MFP_CAN2_RXD     (0x0aUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for CAN2_RXD    */
#define SYS_GPF_MFP0_PF1MFP_EPWM1_CH5    (0x0bUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for EPWM1_CH5   */
#define SYS_GPF_MFP0_PF1MFP_BPWM1_CH1    (0x0cUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for BPWM1_CH1   */
#define SYS_GPF_MFP0_PF1MFP_ACMP1_O      (0x0dUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for ACMP1_O     */
#define SYS_GPF_MFP0_PF1MFP_ICE_CLK      (0x0eUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for ICE_CLK     */
#define SYS_GPF_MFP0_PF1MFP_EADC1_ST     (0x0fUL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for EADC1_ST    */
#define SYS_GPF_MFP0_PF1MFP_QSPI1_MOSI0  (0x13UL<<SYS_GPF_MFP0_PF1MFP_Pos) /*!< GPF_MFP0 PF1 setting for QSPI1_MOSI0 */

/* PF.2 MFP */
#define SYS_GPF_MFP0_PF2MFP_GPIO         (0x00UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for GPIO        */
#define SYS_GPF_MFP0_PF2MFP_EBI_nCS1     (0x02UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for EBI_nCS1    */
#define SYS_GPF_MFP0_PF2MFP_UART0_RXD    (0x03UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for UART0_RXD   */
#define SYS_GPF_MFP0_PF2MFP_I2C0_SDA     (0x04UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for I2C0_SDA    */
#define SYS_GPF_MFP0_PF2MFP_QSPI0_CLK    (0x05UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for QSPI0_CLK   */
#define SYS_GPF_MFP0_PF2MFP_UART9_RXD    (0x07UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for UART9_RXD   */
#define SYS_GPF_MFP0_PF2MFP_XT1_OUT      (0x0aUL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for XT1_OUT     */
#define SYS_GPF_MFP0_PF2MFP_BPWM1_CH1    (0x0bUL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for BPWM1_CH1   */
#define SYS_GPF_MFP0_PF2MFP_I2C4_SMBSUS  (0x0cUL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for I2C4_SMBSUS */
#define SYS_GPF_MFP0_PF2MFP_ACMP3_O      (0x0dUL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for ACMP3_O     */
#define SYS_GPF_MFP0_PF2MFP_BMC13        (0x14UL<<SYS_GPF_MFP0_PF2MFP_Pos) /*!< GPF_MFP0 PF2 setting for BMC13       */

/* PF.3 MFP */
#define SYS_GPF_MFP0_PF3MFP_GPIO         (0x00UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for GPIO        */
#define SYS_GPF_MFP0_PF3MFP_EBI_nCS0     (0x02UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for EBI_nCS0    */
#define SYS_GPF_MFP0_PF3MFP_UART0_TXD    (0x03UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for UART0_TXD   */
#define SYS_GPF_MFP0_PF3MFP_I2C0_SCL     (0x04UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for I2C0_SCL    */
#define SYS_GPF_MFP0_PF3MFP_UART9_TXD    (0x07UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for UART9_TXD   */
#define SYS_GPF_MFP0_PF3MFP_XT1_IN       (0x0aUL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for XT1_IN      */
#define SYS_GPF_MFP0_PF3MFP_BPWM1_CH0    (0x0bUL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for BPWM1_CH0   */
#define SYS_GPF_MFP0_PF3MFP_I2C4_SMBAL   (0x0cUL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for I2C4_SMBAL  */
#define SYS_GPF_MFP0_PF3MFP_ACMP2_O      (0x0dUL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for ACMP2_O     */
#define SYS_GPF_MFP0_PF3MFP_EADC2_ST     (0x0fUL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for EADC2_ST    */
#define SYS_GPF_MFP0_PF3MFP_BMC12        (0x14UL<<SYS_GPF_MFP0_PF3MFP_Pos) /*!< GPF_MFP0 PF3 setting for BMC12       */

/* PF.4 MFP */
#define SYS_GPF_MFP1_PF4MFP_GPIO         (0x00UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for GPIO        */
#define SYS_GPF_MFP1_PF4MFP_UART2_TXD    (0x02UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for UART2_TXD   */
#define SYS_GPF_MFP1_PF4MFP_EBI_AD0      (0x03UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for EBI_AD0     */
#define SYS_GPF_MFP1_PF4MFP_UART2_nRTS   (0x04UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for UART2_nRTS  */
#define SYS_GPF_MFP1_PF4MFP_EPWM0_CH1    (0x07UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for EPWM0_CH1   */
#define SYS_GPF_MFP1_PF4MFP_BPWM0_CH5    (0x08UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for BPWM0_CH5   */
#define SYS_GPF_MFP1_PF4MFP_X32_OUT      (0x0aUL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for X32_OUT     */
#define SYS_GPF_MFP1_PF4MFP_EADC1_ST     (0x0bUL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for EADC1_ST    */
#define SYS_GPF_MFP1_PF4MFP_I2C4_SDA     (0x0cUL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for I2C4_SDA    */
#define SYS_GPF_MFP1_PF4MFP_EQEI2_B      (0x0dUL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for EQEI2_B     */
#define SYS_GPF_MFP1_PF4MFP_SPI5_MISO    (0x13UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for SPI5_MISO   */
#define SYS_GPF_MFP1_PF4MFP_BMC11        (0x14UL<<SYS_GPF_MFP1_PF4MFP_Pos) /*!< GPF_MFP1 PF4 setting for BMC11       */

/* PF.5 MFP */
#define SYS_GPF_MFP1_PF5MFP_GPIO         (0x00UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for GPIO        */
#define SYS_GPF_MFP1_PF5MFP_UART2_RXD    (0x02UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for UART2_RXD   */
#define SYS_GPF_MFP1_PF5MFP_EBI_AD1      (0x03UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for EBI_AD1     */
#define SYS_GPF_MFP1_PF5MFP_UART2_nCTS   (0x04UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for UART2_nCTS  */
#define SYS_GPF_MFP1_PF5MFP_EPWM0_CH0    (0x07UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for EPWM0_CH0   */
#define SYS_GPF_MFP1_PF5MFP_BPWM0_CH4    (0x08UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for BPWM0_CH4   */
#define SYS_GPF_MFP1_PF5MFP_EPWM0_SYNC_OUT (0x09UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for EPWM0_SYNC_OUT*/
#define SYS_GPF_MFP1_PF5MFP_X32_IN       (0x0aUL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for X32_IN      */
#define SYS_GPF_MFP1_PF5MFP_EADC0_ST     (0x0bUL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for EADC0_ST    */
#define SYS_GPF_MFP1_PF5MFP_I2C4_SCL     (0x0cUL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for I2C4_SCL    */
#define SYS_GPF_MFP1_PF5MFP_EQEI2_A      (0x0dUL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for EQEI2_A     */
#define SYS_GPF_MFP1_PF5MFP_SPI5_MOSI    (0x13UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for SPI5_MOSI   */
#define SYS_GPF_MFP1_PF5MFP_BMC10        (0x14UL<<SYS_GPF_MFP1_PF5MFP_Pos) /*!< GPF_MFP1 PF5 setting for BMC10       */

/* PF.6 MFP */
#define SYS_GPF_MFP1_PF6MFP_GPIO         (0x00UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for GPIO        */
#define SYS_GPF_MFP1_PF6MFP_EBI_ADR19    (0x02UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for EBI_ADR19   */
#define SYS_GPF_MFP1_PF6MFP_SC0_CLK      (0x03UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for SC0_CLK     */
#define SYS_GPF_MFP1_PF6MFP_I2S0_LRCK    (0x04UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for I2S0_LRCK   */
#define SYS_GPF_MFP1_PF6MFP_SPI0_MOSI    (0x05UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for SPI0_MOSI   */
#define SYS_GPF_MFP1_PF6MFP_UART4_RXD    (0x06UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for UART4_RXD   */
#define SYS_GPF_MFP1_PF6MFP_EBI_nCS0     (0x07UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for EBI_nCS0    */
#define SYS_GPF_MFP1_PF6MFP_CAN2_RXD     (0x08UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for CAN2_RXD    */
#define SYS_GPF_MFP1_PF6MFP_SPI3_I2SMCLK (0x09UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for SPI3_I2SMCLK*/
#define SYS_GPF_MFP1_PF6MFP_TAMPER0      (0x0aUL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for TAMPER0     */
#define SYS_GPF_MFP1_PF6MFP_EQEI2_INDEX  (0x0dUL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for EQEI2_INDEX */
#define SYS_GPF_MFP1_PF6MFP_TRACE_SWO    (0x0eUL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for TRACE_SWO   */
#define SYS_GPF_MFP1_PF6MFP_SPI5_CLK     (0x13UL<<SYS_GPF_MFP1_PF6MFP_Pos) /*!< GPF_MFP1 PF6 setting for SPI5_CLK    */

/* PF.7 MFP */
#define SYS_GPF_MFP1_PF7MFP_GPIO         (0x00UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for GPIO        */
#define SYS_GPF_MFP1_PF7MFP_EBI_ADR18    (0x02UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for EBI_ADR18   */
#define SYS_GPF_MFP1_PF7MFP_SC0_DAT      (0x03UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for SC0_DAT     */
#define SYS_GPF_MFP1_PF7MFP_I2S0_DO      (0x04UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for I2S0_DO     */
#define SYS_GPF_MFP1_PF7MFP_SPI0_MISO    (0x05UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for SPI0_MISO   */
#define SYS_GPF_MFP1_PF7MFP_UART4_TXD    (0x06UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for UART4_TXD   */
#define SYS_GPF_MFP1_PF7MFP_CCAP_DATA0   (0x07UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for CCAP_DATA0  */
#define SYS_GPF_MFP1_PF7MFP_CAN2_TXD     (0x08UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for CAN2_TXD    */
#define SYS_GPF_MFP1_PF7MFP_TAMPER1      (0x0aUL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for TAMPER1     */
#define SYS_GPF_MFP1_PF7MFP_SPI5_SS      (0x13UL<<SYS_GPF_MFP1_PF7MFP_Pos) /*!< GPF_MFP1 PF7 setting for SPI5_SS     */

/* PF.8 MFP */
#define SYS_GPF_MFP2_PF8MFP_GPIO         (0x00UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for GPIO        */
#define SYS_GPF_MFP2_PF8MFP_EBI_ADR17    (0x02UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for EBI_ADR17   */
#define SYS_GPF_MFP2_PF8MFP_SC0_RST      (0x03UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for SC0_RST     */
#define SYS_GPF_MFP2_PF8MFP_I2S0_DI      (0x04UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for I2S0_DI     */
#define SYS_GPF_MFP2_PF8MFP_SPI0_CLK     (0x05UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for SPI0_CLK    */
#define SYS_GPF_MFP2_PF8MFP_UART5_nCTS   (0x06UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for UART5_nCTS  */
#define SYS_GPF_MFP2_PF8MFP_CCAP_DATA1   (0x07UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for CCAP_DATA1  */
#define SYS_GPF_MFP2_PF8MFP_CAN1_RXD     (0x08UL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for CAN1_RXD    */
#define SYS_GPF_MFP2_PF8MFP_TAMPER2      (0x0aUL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for TAMPER2     */
#define SYS_GPF_MFP2_PF8MFP_UART9_RXD    (0x0bUL<<SYS_GPF_MFP2_PF8MFP_Pos) /*!< GPF_MFP2 PF8 setting for UART9_RXD   */

/* PF.9 MFP */
#define SYS_GPF_MFP2_PF9MFP_GPIO         (0x00UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for GPIO        */
#define SYS_GPF_MFP2_PF9MFP_EBI_ADR16    (0x02UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for EBI_ADR16   */
#define SYS_GPF_MFP2_PF9MFP_SC0_PWR      (0x03UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for SC0_PWR     */
#define SYS_GPF_MFP2_PF9MFP_I2S0_MCLK    (0x04UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for I2S0_MCLK   */
#define SYS_GPF_MFP2_PF9MFP_SPI0_SS      (0x05UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for SPI0_SS     */
#define SYS_GPF_MFP2_PF9MFP_UART5_nRTS   (0x06UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for UART5_nRTS  */
#define SYS_GPF_MFP2_PF9MFP_CCAP_DATA2   (0x07UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for CCAP_DATA2  */
#define SYS_GPF_MFP2_PF9MFP_CAN1_TXD     (0x08UL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for CAN1_TXD    */
#define SYS_GPF_MFP2_PF9MFP_TAMPER3      (0x0aUL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for TAMPER3     */
#define SYS_GPF_MFP2_PF9MFP_UART9_TXD    (0x0bUL<<SYS_GPF_MFP2_PF9MFP_Pos) /*!< GPF_MFP2 PF9 setting for UART9_TXD   */

/* PF.10 MFP */
#define SYS_GPF_MFP2_PF10MFP_GPIO        (0x00UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for GPIO       */
#define SYS_GPF_MFP2_PF10MFP_EBI_ADR15   (0x02UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for EBI_ADR15  */
#define SYS_GPF_MFP2_PF10MFP_SC0_nCD     (0x03UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for SC0_nCD    */
#define SYS_GPF_MFP2_PF10MFP_I2S0_BCLK   (0x04UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for I2S0_BCLK  */
#define SYS_GPF_MFP2_PF10MFP_SPI0_I2SMCLK (0x05UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for SPI0_I2SMCLK*/
#define SYS_GPF_MFP2_PF10MFP_UART5_RXD   (0x06UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for UART5_RXD  */
#define SYS_GPF_MFP2_PF10MFP_CCAP_DATA3  (0x07UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for CCAP_DATA3 */
#define SYS_GPF_MFP2_PF10MFP_CAN3_RXD    (0x08UL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for CAN3_RXD   */
#define SYS_GPF_MFP2_PF10MFP_TAMPER4     (0x0aUL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for TAMPER4    */
#define SYS_GPF_MFP2_PF10MFP_UART9_nRTS  (0x0bUL<<SYS_GPF_MFP2_PF10MFP_Pos)/*!< GPF_MFP2 PF10 setting for UART9_nRTS */

/* PF.11 MFP */
#define SYS_GPF_MFP2_PF11MFP_GPIO        (0x00UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for GPIO       */
#define SYS_GPF_MFP2_PF11MFP_EBI_ADR14   (0x02UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for EBI_ADR14  */
#define SYS_GPF_MFP2_PF11MFP_SPI2_MOSI   (0x03UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for SPI2_MOSI  */
#define SYS_GPF_MFP2_PF11MFP_UART5_TXD   (0x06UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for UART5_TXD  */
#define SYS_GPF_MFP2_PF11MFP_CCAP_DATA4  (0x07UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for CCAP_DATA4 */
#define SYS_GPF_MFP2_PF11MFP_CAN3_TXD    (0x08UL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for CAN3_TXD   */
#define SYS_GPF_MFP2_PF11MFP_TAMPER5     (0x0aUL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for TAMPER5    */
#define SYS_GPF_MFP2_PF11MFP_UART9_nCTS  (0x0bUL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for UART9_nCTS */
#define SYS_GPF_MFP2_PF11MFP_TM3         (0x0dUL<<SYS_GPF_MFP2_PF11MFP_Pos)/*!< GPF_MFP2 PF11 setting for TM3        */

/* PG.0 MFP */
#define SYS_GPG_MFP0_PG0MFP_GPIO         (0x00UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for GPIO        */
#define SYS_GPG_MFP0_PG0MFP_EBI_ADR8     (0x02UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for EBI_ADR8    */
#define SYS_GPG_MFP0_PG0MFP_I2C0_SCL     (0x04UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for I2C0_SCL    */
#define SYS_GPG_MFP0_PG0MFP_I2C1_SMBAL   (0x05UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for I2C1_SMBAL  */
#define SYS_GPG_MFP0_PG0MFP_UART2_RXD    (0x06UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for UART2_RXD   */
#define SYS_GPG_MFP0_PG0MFP_CAN1_TXD     (0x07UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for CAN1_TXD    */
#define SYS_GPG_MFP0_PG0MFP_UART1_TXD    (0x08UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for UART1_TXD   */
#define SYS_GPG_MFP0_PG0MFP_I2C3_SCL     (0x09UL<<SYS_GPG_MFP0_PG0MFP_Pos) /*!< GPG_MFP0 PG0 setting for I2C3_SCL    */

/* PG.1 MFP */
#define SYS_GPG_MFP0_PG1MFP_GPIO         (0x00UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for GPIO        */
#define SYS_GPG_MFP0_PG1MFP_EBI_ADR9     (0x02UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for EBI_ADR9    */
#define SYS_GPG_MFP0_PG1MFP_SPI2_I2SMCLK (0x03UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for SPI2_I2SMCLK*/
#define SYS_GPG_MFP0_PG1MFP_I2C0_SDA     (0x04UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for I2C0_SDA    */
#define SYS_GPG_MFP0_PG1MFP_I2C1_SMBSUS  (0x05UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for I2C1_SMBSUS */
#define SYS_GPG_MFP0_PG1MFP_UART2_TXD    (0x06UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for UART2_TXD   */
#define SYS_GPG_MFP0_PG1MFP_CAN1_RXD     (0x07UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for CAN1_RXD    */
#define SYS_GPG_MFP0_PG1MFP_UART1_RXD    (0x08UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for UART1_RXD   */
#define SYS_GPG_MFP0_PG1MFP_I2C3_SDA     (0x09UL<<SYS_GPG_MFP0_PG1MFP_Pos) /*!< GPG_MFP0 PG1 setting for I2C3_SDA    */

/* PG.2 MFP */
#define SYS_GPG_MFP0_PG2MFP_GPIO         (0x00UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for GPIO        */
#define SYS_GPG_MFP0_PG2MFP_EBI_ADR11    (0x02UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for EBI_ADR11   */
#define SYS_GPG_MFP0_PG2MFP_SPI2_SS      (0x03UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for SPI2_SS     */
#define SYS_GPG_MFP0_PG2MFP_I2C0_SMBAL   (0x04UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for I2C0_SMBAL  */
#define SYS_GPG_MFP0_PG2MFP_I2C1_SCL     (0x05UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for I2C1_SCL    */
#define SYS_GPG_MFP0_PG2MFP_CCAP_DATA7   (0x07UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for CCAP_DATA7  */
#define SYS_GPG_MFP0_PG2MFP_I2C3_SMBAL   (0x09UL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for I2C3_SMBAL  */
#define SYS_GPG_MFP0_PG2MFP_TM0          (0x0dUL<<SYS_GPG_MFP0_PG2MFP_Pos) /*!< GPG_MFP0 PG2 setting for TM0         */

/* PG.3 MFP */
#define SYS_GPG_MFP0_PG3MFP_GPIO         (0x00UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for GPIO        */
#define SYS_GPG_MFP0_PG3MFP_EBI_ADR12    (0x02UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for EBI_ADR12   */
#define SYS_GPG_MFP0_PG3MFP_SPI2_CLK     (0x03UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for SPI2_CLK    */
#define SYS_GPG_MFP0_PG3MFP_I2C0_SMBSUS  (0x04UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for I2C0_SMBSUS */
#define SYS_GPG_MFP0_PG3MFP_I2C1_SDA     (0x05UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for I2C1_SDA    */
#define SYS_GPG_MFP0_PG3MFP_CCAP_DATA6   (0x07UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for CCAP_DATA6  */
#define SYS_GPG_MFP0_PG3MFP_I2C3_SMBSUS  (0x09UL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for I2C3_SMBSUS */
#define SYS_GPG_MFP0_PG3MFP_TM1          (0x0dUL<<SYS_GPG_MFP0_PG3MFP_Pos) /*!< GPG_MFP0 PG3 setting for TM1         */

/* PG.4 MFP */
#define SYS_GPG_MFP1_PG4MFP_GPIO         (0x00UL<<SYS_GPG_MFP1_PG4MFP_Pos) /*!< GPG_MFP1 PG4 setting for GPIO        */
#define SYS_GPG_MFP1_PG4MFP_EBI_ADR13    (0x02UL<<SYS_GPG_MFP1_PG4MFP_Pos) /*!< GPG_MFP1 PG4 setting for EBI_ADR13   */
#define SYS_GPG_MFP1_PG4MFP_SPI2_MISO    (0x03UL<<SYS_GPG_MFP1_PG4MFP_Pos) /*!< GPG_MFP1 PG4 setting for SPI2_MISO   */
#define SYS_GPG_MFP1_PG4MFP_CCAP_DATA5   (0x07UL<<SYS_GPG_MFP1_PG4MFP_Pos) /*!< GPG_MFP1 PG4 setting for CCAP_DATA5  */
#define SYS_GPG_MFP1_PG4MFP_TM2          (0x0dUL<<SYS_GPG_MFP1_PG4MFP_Pos) /*!< GPG_MFP1 PG4 setting for TM2         */

/* PG.5 MFP */
#define SYS_GPG_MFP1_PG5MFP_GPIO         (0x00UL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for GPIO        */
#define SYS_GPG_MFP1_PG5MFP_EBI_nCS1     (0x02UL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for EBI_nCS1    */
#define SYS_GPG_MFP1_PG5MFP_SPI3_SS      (0x03UL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for SPI3_SS     */
#define SYS_GPG_MFP1_PG5MFP_SC1_PWR      (0x04UL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for SC1_PWR     */
#define SYS_GPG_MFP1_PG5MFP_I2C3_SMBAL   (0x08UL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for I2C3_SMBAL  */
#define SYS_GPG_MFP1_PG5MFP_I2S1_MCLK    (0x0aUL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for I2S1_MCLK   */
#define SYS_GPG_MFP1_PG5MFP_EPWM0_CH3    (0x0bUL<<SYS_GPG_MFP1_PG5MFP_Pos) /*!< GPG_MFP1 PG5 setting for EPWM0_CH3   */

/* PG.6 MFP */
#define SYS_GPG_MFP1_PG6MFP_GPIO         (0x00UL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for GPIO        */
#define SYS_GPG_MFP1_PG6MFP_EBI_nCS2     (0x02UL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for EBI_nCS2    */
#define SYS_GPG_MFP1_PG6MFP_SPI3_CLK     (0x03UL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for SPI3_CLK    */
#define SYS_GPG_MFP1_PG6MFP_SC1_RST      (0x04UL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for SC1_RST     */
#define SYS_GPG_MFP1_PG6MFP_I2C3_SMBSUS  (0x08UL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for I2C3_SMBSUS */
#define SYS_GPG_MFP1_PG6MFP_I2S1_DI      (0x0aUL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for I2S1_DI     */
#define SYS_GPG_MFP1_PG6MFP_EPWM0_CH2    (0x0bUL<<SYS_GPG_MFP1_PG6MFP_Pos) /*!< GPG_MFP1 PG6 setting for EPWM0_CH2   */

/* PG.7 MFP */
#define SYS_GPG_MFP1_PG7MFP_GPIO         (0x00UL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for GPIO        */
#define SYS_GPG_MFP1_PG7MFP_EBI_nWRL     (0x02UL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for EBI_nWRL    */
#define SYS_GPG_MFP1_PG7MFP_SPI3_MISO    (0x03UL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for SPI3_MISO   */
#define SYS_GPG_MFP1_PG7MFP_SC1_DAT      (0x04UL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for SC1_DAT     */
#define SYS_GPG_MFP1_PG7MFP_I2C3_SCL     (0x08UL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for I2C3_SCL    */
#define SYS_GPG_MFP1_PG7MFP_I2S1_DO      (0x0aUL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for I2S1_DO     */
#define SYS_GPG_MFP1_PG7MFP_EPWM0_CH1    (0x0bUL<<SYS_GPG_MFP1_PG7MFP_Pos) /*!< GPG_MFP1 PG7 setting for EPWM0_CH1   */

/* PG.8 MFP */
#define SYS_GPG_MFP2_PG8MFP_GPIO         (0x00UL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for GPIO        */
#define SYS_GPG_MFP2_PG8MFP_EBI_nWRH     (0x02UL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for EBI_nWRH    */
#define SYS_GPG_MFP2_PG8MFP_SPI3_MOSI    (0x03UL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for SPI3_MOSI   */
#define SYS_GPG_MFP2_PG8MFP_SC1_CLK      (0x04UL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for SC1_CLK     */
#define SYS_GPG_MFP2_PG8MFP_I2C3_SDA     (0x08UL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for I2C3_SDA    */
#define SYS_GPG_MFP2_PG8MFP_I2S1_LRCK    (0x0aUL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for I2S1_LRCK   */
#define SYS_GPG_MFP2_PG8MFP_EPWM0_CH0    (0x0bUL<<SYS_GPG_MFP2_PG8MFP_Pos) /*!< GPG_MFP2 PG8 setting for EPWM0_CH0   */

/* PG.9 MFP */
#define SYS_GPG_MFP2_PG9MFP_GPIO         (0x00UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for GPIO        */
#define SYS_GPG_MFP2_PG9MFP_EBI_AD0      (0x02UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for EBI_AD0     */
#define SYS_GPG_MFP2_PG9MFP_SD1_DAT3     (0x03UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for SD1_DAT3    */
#define SYS_GPG_MFP2_PG9MFP_SPIM_D2      (0x04UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for SPIM_D2     */
#define SYS_GPG_MFP2_PG9MFP_QSPI1_MISO1  (0x05UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for QSPI1_MISO1 */
#define SYS_GPG_MFP2_PG9MFP_CCAP_PIXCLK  (0x07UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for CCAP_PIXCLK */
#define SYS_GPG_MFP2_PG9MFP_I2C4_SCL     (0x08UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for I2C4_SCL    */
#define SYS_GPG_MFP2_PG9MFP_ECAP2_IC0    (0x09UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for ECAP2_IC0   */
#define SYS_GPG_MFP2_PG9MFP_BPWM0_CH5    (0x0cUL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for BPWM0_CH5   */
#define SYS_GPG_MFP2_PG9MFP_HBI_D4       (0x10UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for HBI_D4      */
#define SYS_GPG_MFP2_PG9MFP_SPI8_SS      (0x13UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for SPI8_SS     */
#define SYS_GPG_MFP2_PG9MFP_BMC16        (0x14UL<<SYS_GPG_MFP2_PG9MFP_Pos) /*!< GPG_MFP2 PG9 setting for BMC16       */

/* PG.10 MFP */
#define SYS_GPG_MFP2_PG10MFP_GPIO        (0x00UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for GPIO       */
#define SYS_GPG_MFP2_PG10MFP_EBI_AD1     (0x02UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for EBI_AD1    */
#define SYS_GPG_MFP2_PG10MFP_SD1_DAT2    (0x03UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for SD1_DAT2   */
#define SYS_GPG_MFP2_PG10MFP_SPIM_D3     (0x04UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for SPIM_D3    */
#define SYS_GPG_MFP2_PG10MFP_QSPI1_MOSI1 (0x05UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for QSPI1_MOSI1*/
#define SYS_GPG_MFP2_PG10MFP_CCAP_SCLK   (0x07UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for CCAP_SCLK  */
#define SYS_GPG_MFP2_PG10MFP_I2C4_SDA    (0x08UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for I2C4_SDA   */
#define SYS_GPG_MFP2_PG10MFP_ECAP2_IC1   (0x09UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for ECAP2_IC1  */
#define SYS_GPG_MFP2_PG10MFP_BPWM0_CH4   (0x0cUL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for BPWM0_CH4  */
#define SYS_GPG_MFP2_PG10MFP_HBI_D3      (0x10UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for HBI_D3     */
#define SYS_GPG_MFP2_PG10MFP_SPI8_CLK    (0x13UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for SPI8_CLK   */
#define SYS_GPG_MFP2_PG10MFP_BMC17       (0x14UL<<SYS_GPG_MFP2_PG10MFP_Pos)/*!< GPG_MFP2 PG10 setting for BMC17      */

/* PG.11 MFP */
#define SYS_GPG_MFP2_PG11MFP_GPIO        (0x00UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for GPIO       */
#define SYS_GPG_MFP2_PG11MFP_EBI_AD2     (0x02UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for EBI_AD2    */
#define SYS_GPG_MFP2_PG11MFP_SD1_DAT1    (0x03UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for SD1_DAT1   */
#define SYS_GPG_MFP2_PG11MFP_SPIM_SS     (0x04UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for SPIM_SS    */
#define SYS_GPG_MFP2_PG11MFP_QSPI1_SS    (0x05UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for QSPI1_SS   */
#define SYS_GPG_MFP2_PG11MFP_UART7_TXD   (0x06UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for UART7_TXD  */
#define SYS_GPG_MFP2_PG11MFP_CCAP_SFIELD (0x07UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for CCAP_SFIELD*/
#define SYS_GPG_MFP2_PG11MFP_I2C4_SMBAL  (0x08UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for I2C4_SMBAL */
#define SYS_GPG_MFP2_PG11MFP_ECAP2_IC2   (0x09UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for ECAP2_IC2  */
#define SYS_GPG_MFP2_PG11MFP_BPWM0_CH3   (0x0cUL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for BPWM0_CH3  */
#define SYS_GPG_MFP2_PG11MFP_HBI_D0      (0x10UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for HBI_D0     */
#define SYS_GPG_MFP2_PG11MFP_SPI8_MOSI   (0x13UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for SPI8_MOSI  */
#define SYS_GPG_MFP2_PG11MFP_BMC18       (0x14UL<<SYS_GPG_MFP2_PG11MFP_Pos)/*!< GPG_MFP2 PG11 setting for BMC18      */

/* PG.12 MFP */
#define SYS_GPG_MFP3_PG12MFP_GPIO        (0x00UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for GPIO       */
#define SYS_GPG_MFP3_PG12MFP_EBI_AD3     (0x02UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for EBI_AD3    */
#define SYS_GPG_MFP3_PG12MFP_SD1_DAT0    (0x03UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for SD1_DAT0   */
#define SYS_GPG_MFP3_PG12MFP_SPIM_CLK    (0x04UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for SPIM_CLK   */
#define SYS_GPG_MFP3_PG12MFP_QSPI1_CLK   (0x05UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for QSPI1_CLK  */
#define SYS_GPG_MFP3_PG12MFP_UART7_RXD   (0x06UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for UART7_RXD  */
#define SYS_GPG_MFP3_PG12MFP_CCAP_VSYNC  (0x07UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for CCAP_VSYNC */
#define SYS_GPG_MFP3_PG12MFP_I2C4_SMBSUS (0x08UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for I2C4_SMBSUS*/
#define SYS_GPG_MFP3_PG12MFP_BPWM0_CH2   (0x0cUL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for BPWM0_CH2  */
#define SYS_GPG_MFP3_PG12MFP_HBI_D1      (0x10UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for HBI_D1     */
#define SYS_GPG_MFP3_PG12MFP_SPI8_MISO   (0x13UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for SPI8_MISO  */
#define SYS_GPG_MFP3_PG12MFP_BMC19       (0x14UL<<SYS_GPG_MFP3_PG12MFP_Pos)/*!< GPG_MFP3 PG12 setting for BMC19      */

/* PG.13 MFP */
#define SYS_GPG_MFP3_PG13MFP_GPIO        (0x00UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for GPIO       */
#define SYS_GPG_MFP3_PG13MFP_EBI_AD4     (0x02UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for EBI_AD4    */
#define SYS_GPG_MFP3_PG13MFP_SD1_CMD     (0x03UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for SD1_CMD    */
#define SYS_GPG_MFP3_PG13MFP_SPIM_MISO   (0x04UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for SPIM_MISO  */
#define SYS_GPG_MFP3_PG13MFP_QSPI1_MISO0 (0x05UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for QSPI1_MISO0*/
#define SYS_GPG_MFP3_PG13MFP_UART6_TXD   (0x06UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for UART6_TXD  */
#define SYS_GPG_MFP3_PG13MFP_CCAP_HSYNC  (0x07UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for CCAP_HSYNC */
#define SYS_GPG_MFP3_PG13MFP_BPWM0_CH1   (0x0cUL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for BPWM0_CH1  */
#define SYS_GPG_MFP3_PG13MFP_HBI_D5      (0x10UL<<SYS_GPG_MFP3_PG13MFP_Pos)/*!< GPG_MFP3 PG13 setting for HBI_D5     */

/* PG.14 MFP */
#define SYS_GPG_MFP3_PG14MFP_GPIO        (0x00UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for GPIO       */
#define SYS_GPG_MFP3_PG14MFP_EBI_AD5     (0x02UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for EBI_AD5    */
#define SYS_GPG_MFP3_PG14MFP_SD1_CLK     (0x03UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for SD1_CLK    */
#define SYS_GPG_MFP3_PG14MFP_SPIM_MOSI   (0x04UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for SPIM_MOSI  */
#define SYS_GPG_MFP3_PG14MFP_QSPI1_MOSI0 (0x05UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for QSPI1_MOSI0*/
#define SYS_GPG_MFP3_PG14MFP_UART6_RXD   (0x06UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for UART6_RXD  */
#define SYS_GPG_MFP3_PG14MFP_BPWM0_CH0   (0x0cUL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for BPWM0_CH0  */
#define SYS_GPG_MFP3_PG14MFP_HBI_D6      (0x10UL<<SYS_GPG_MFP3_PG14MFP_Pos)/*!< GPG_MFP3 PG14 setting for HBI_D6     */

/* PG.15 MFP */
#define SYS_GPG_MFP3_PG15MFP_GPIO        (0x00UL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for GPIO       */
#define SYS_GPG_MFP3_PG15MFP_SD1_nCD     (0x03UL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for SD1_nCD    */
#define SYS_GPG_MFP3_PG15MFP_CLKO        (0x0eUL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for CLKO       */
#define SYS_GPG_MFP3_PG15MFP_EADC0_ST    (0x0fUL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for EADC0_ST   */
#define SYS_GPG_MFP3_PG15MFP_HBI_D7      (0x10UL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for HBI_D7     */
#define SYS_GPG_MFP3_PG15MFP_QSPI1_MISO1 (0x13UL<<SYS_GPG_MFP3_PG15MFP_Pos)/*!< GPG_MFP3 PG15 setting for QSPI1_MISO1*/

/* PH.0 MFP */
#define SYS_GPH_MFP0_PH0MFP_GPIO         (0x00UL<<SYS_GPH_MFP0_PH0MFP_Pos) /*!< GPH_MFP0 PH0 setting for GPIO        */
#define SYS_GPH_MFP0_PH0MFP_EBI_ADR7     (0x02UL<<SYS_GPH_MFP0_PH0MFP_Pos) /*!< GPH_MFP0 PH0 setting for EBI_ADR7    */
#define SYS_GPH_MFP0_PH0MFP_UART5_TXD    (0x04UL<<SYS_GPH_MFP0_PH0MFP_Pos) /*!< GPH_MFP0 PH0 setting for UART5_TXD   */
#define SYS_GPH_MFP0_PH0MFP_TM0_EXT      (0x0dUL<<SYS_GPH_MFP0_PH0MFP_Pos) /*!< GPH_MFP0 PH0 setting for TM0_EXT     */

/* PH.1 MFP */
#define SYS_GPH_MFP0_PH1MFP_GPIO         (0x00UL<<SYS_GPH_MFP0_PH1MFP_Pos) /*!< GPH_MFP0 PH1 setting for GPIO        */
#define SYS_GPH_MFP0_PH1MFP_EBI_ADR6     (0x02UL<<SYS_GPH_MFP0_PH1MFP_Pos) /*!< GPH_MFP0 PH1 setting for EBI_ADR6    */
#define SYS_GPH_MFP0_PH1MFP_UART5_RXD    (0x04UL<<SYS_GPH_MFP0_PH1MFP_Pos) /*!< GPH_MFP0 PH1 setting for UART5_RXD   */
#define SYS_GPH_MFP0_PH1MFP_TM1_EXT      (0x0dUL<<SYS_GPH_MFP0_PH1MFP_Pos) /*!< GPH_MFP0 PH1 setting for TM1_EXT     */

/* PH.2 MFP */
#define SYS_GPH_MFP0_PH2MFP_GPIO         (0x00UL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for GPIO        */
#define SYS_GPH_MFP0_PH2MFP_EBI_ADR5     (0x02UL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for EBI_ADR5    */
#define SYS_GPH_MFP0_PH2MFP_UART5_nRTS   (0x04UL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for UART5_nRTS  */
#define SYS_GPH_MFP0_PH2MFP_UART4_TXD    (0x05UL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for UART4_TXD   */
#define SYS_GPH_MFP0_PH2MFP_I2C0_SCL     (0x06UL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for I2C0_SCL    */
#define SYS_GPH_MFP0_PH2MFP_TM2_EXT      (0x0dUL<<SYS_GPH_MFP0_PH2MFP_Pos) /*!< GPH_MFP0 PH2 setting for TM2_EXT     */

/* PH.3 MFP */
#define SYS_GPH_MFP0_PH3MFP_GPIO         (0x00UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for GPIO        */
#define SYS_GPH_MFP0_PH3MFP_EBI_ADR4     (0x02UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for EBI_ADR4    */
#define SYS_GPH_MFP0_PH3MFP_SPI1_I2SMCLK (0x03UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for SPI1_I2SMCLK*/
#define SYS_GPH_MFP0_PH3MFP_UART5_nCTS   (0x04UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for UART5_nCTS  */
#define SYS_GPH_MFP0_PH3MFP_UART4_RXD    (0x05UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for UART4_RXD   */
#define SYS_GPH_MFP0_PH3MFP_I2C0_SDA     (0x06UL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for I2C0_SDA    */
#define SYS_GPH_MFP0_PH3MFP_TM3_EXT      (0x0dUL<<SYS_GPH_MFP0_PH3MFP_Pos) /*!< GPH_MFP0 PH3 setting for TM3_EXT     */

/* PH.4 MFP */
#define SYS_GPH_MFP1_PH4MFP_GPIO         (0x00UL<<SYS_GPH_MFP1_PH4MFP_Pos) /*!< GPH_MFP1 PH4 setting for GPIO        */
#define SYS_GPH_MFP1_PH4MFP_EBI_ADR3     (0x02UL<<SYS_GPH_MFP1_PH4MFP_Pos) /*!< GPH_MFP1 PH4 setting for EBI_ADR3    */
#define SYS_GPH_MFP1_PH4MFP_SPI1_MISO    (0x03UL<<SYS_GPH_MFP1_PH4MFP_Pos) /*!< GPH_MFP1 PH4 setting for SPI1_MISO   */
#define SYS_GPH_MFP1_PH4MFP_UART7_nRTS   (0x04UL<<SYS_GPH_MFP1_PH4MFP_Pos) /*!< GPH_MFP1 PH4 setting for UART7_nRTS  */
#define SYS_GPH_MFP1_PH4MFP_UART6_TXD    (0x05UL<<SYS_GPH_MFP1_PH4MFP_Pos) /*!< GPH_MFP1 PH4 setting for UART6_TXD   */

/* PH.5 MFP */
#define SYS_GPH_MFP1_PH5MFP_GPIO         (0x00UL<<SYS_GPH_MFP1_PH5MFP_Pos) /*!< GPH_MFP1 PH5 setting for GPIO        */
#define SYS_GPH_MFP1_PH5MFP_EBI_ADR2     (0x02UL<<SYS_GPH_MFP1_PH5MFP_Pos) /*!< GPH_MFP1 PH5 setting for EBI_ADR2    */
#define SYS_GPH_MFP1_PH5MFP_SPI1_MOSI    (0x03UL<<SYS_GPH_MFP1_PH5MFP_Pos) /*!< GPH_MFP1 PH5 setting for SPI1_MOSI   */
#define SYS_GPH_MFP1_PH5MFP_UART7_nCTS   (0x04UL<<SYS_GPH_MFP1_PH5MFP_Pos) /*!< GPH_MFP1 PH5 setting for UART7_nCTS  */
#define SYS_GPH_MFP1_PH5MFP_UART6_RXD    (0x05UL<<SYS_GPH_MFP1_PH5MFP_Pos) /*!< GPH_MFP1 PH5 setting for UART6_RXD   */

/* PH.6 MFP */
#define SYS_GPH_MFP1_PH6MFP_GPIO         (0x00UL<<SYS_GPH_MFP1_PH6MFP_Pos) /*!< GPH_MFP1 PH6 setting for GPIO        */
#define SYS_GPH_MFP1_PH6MFP_EBI_ADR1     (0x02UL<<SYS_GPH_MFP1_PH6MFP_Pos) /*!< GPH_MFP1 PH6 setting for EBI_ADR1    */
#define SYS_GPH_MFP1_PH6MFP_SPI1_CLK     (0x03UL<<SYS_GPH_MFP1_PH6MFP_Pos) /*!< GPH_MFP1 PH6 setting for SPI1_CLK    */
#define SYS_GPH_MFP1_PH6MFP_UART7_TXD    (0x04UL<<SYS_GPH_MFP1_PH6MFP_Pos) /*!< GPH_MFP1 PH6 setting for UART7_TXD   */
#define SYS_GPH_MFP1_PH6MFP_UART9_nCTS   (0x07UL<<SYS_GPH_MFP1_PH6MFP_Pos) /*!< GPH_MFP1 PH6 setting for UART9_nCTS  */

/* PH.7 MFP */
#define SYS_GPH_MFP1_PH7MFP_GPIO         (0x00UL<<SYS_GPH_MFP1_PH7MFP_Pos) /*!< GPH_MFP1 PH7 setting for GPIO        */
#define SYS_GPH_MFP1_PH7MFP_EBI_ADR0     (0x02UL<<SYS_GPH_MFP1_PH7MFP_Pos) /*!< GPH_MFP1 PH7 setting for EBI_ADR0    */
#define SYS_GPH_MFP1_PH7MFP_SPI1_SS      (0x03UL<<SYS_GPH_MFP1_PH7MFP_Pos) /*!< GPH_MFP1 PH7 setting for SPI1_SS     */
#define SYS_GPH_MFP1_PH7MFP_UART7_RXD    (0x04UL<<SYS_GPH_MFP1_PH7MFP_Pos) /*!< GPH_MFP1 PH7 setting for UART7_RXD   */
#define SYS_GPH_MFP1_PH7MFP_UART9_nRTS   (0x07UL<<SYS_GPH_MFP1_PH7MFP_Pos) /*!< GPH_MFP1 PH7 setting for UART9_nRTS  */

/* PH.8 MFP */
#define SYS_GPH_MFP2_PH8MFP_GPIO         (0x00UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for GPIO        */
#define SYS_GPH_MFP2_PH8MFP_EBI_AD12     (0x02UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for EBI_AD12    */
#define SYS_GPH_MFP2_PH8MFP_QSPI0_CLK    (0x03UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for QSPI0_CLK   */
#define SYS_GPH_MFP2_PH8MFP_SC2_PWR      (0x04UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for SC2_PWR     */
#define SYS_GPH_MFP2_PH8MFP_I2S0_DI      (0x05UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for I2S0_DI     */
#define SYS_GPH_MFP2_PH8MFP_SPI1_CLK     (0x06UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for SPI1_CLK    */
#define SYS_GPH_MFP2_PH8MFP_UART3_nRTS   (0x07UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for UART3_nRTS  */
#define SYS_GPH_MFP2_PH8MFP_I2C1_SMBAL   (0x08UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for I2C1_SMBAL  */
#define SYS_GPH_MFP2_PH8MFP_I2C2_SCL     (0x09UL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for I2C2_SCL    */
#define SYS_GPH_MFP2_PH8MFP_UART1_TXD    (0x0aUL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for UART1_TXD   */
#define SYS_GPH_MFP2_PH8MFP_UART9_nCTS   (0x0dUL<<SYS_GPH_MFP2_PH8MFP_Pos) /*!< GPH_MFP2 PH8 setting for UART9_nCTS  */

/* PH.9 MFP */
#define SYS_GPH_MFP2_PH9MFP_GPIO         (0x00UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for GPIO        */
#define SYS_GPH_MFP2_PH9MFP_EBI_AD13     (0x02UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for EBI_AD13    */
#define SYS_GPH_MFP2_PH9MFP_QSPI0_SS     (0x03UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for QSPI0_SS    */
#define SYS_GPH_MFP2_PH9MFP_SC2_RST      (0x04UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for SC2_RST     */
#define SYS_GPH_MFP2_PH9MFP_I2S0_DO      (0x05UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for I2S0_DO     */
#define SYS_GPH_MFP2_PH9MFP_SPI1_SS      (0x06UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for SPI1_SS     */
#define SYS_GPH_MFP2_PH9MFP_UART3_nCTS   (0x07UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for UART3_nCTS  */
#define SYS_GPH_MFP2_PH9MFP_I2C1_SMBSUS  (0x08UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for I2C1_SMBSUS */
#define SYS_GPH_MFP2_PH9MFP_I2C2_SDA     (0x09UL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for I2C2_SDA    */
#define SYS_GPH_MFP2_PH9MFP_UART1_RXD    (0x0aUL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for UART1_RXD   */
#define SYS_GPH_MFP2_PH9MFP_UART9_nRTS   (0x0dUL<<SYS_GPH_MFP2_PH9MFP_Pos) /*!< GPH_MFP2 PH9 setting for UART9_nRTS  */

/* PH.10 MFP */
#define SYS_GPH_MFP2_PH10MFP_GPIO        (0x00UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for GPIO       */
#define SYS_GPH_MFP2_PH10MFP_EBI_AD14    (0x02UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for EBI_AD14   */
#define SYS_GPH_MFP2_PH10MFP_QSPI0_MISO1 (0x03UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for QSPI0_MISO1*/
#define SYS_GPH_MFP2_PH10MFP_SC2_nCD     (0x04UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for SC2_nCD    */
#define SYS_GPH_MFP2_PH10MFP_I2S0_LRCK   (0x05UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for I2S0_LRCK  */
#define SYS_GPH_MFP2_PH10MFP_SPI1_I2SMCLK (0x06UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for SPI1_I2SMCLK*/
#define SYS_GPH_MFP2_PH10MFP_UART4_TXD   (0x07UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for UART4_TXD  */
#define SYS_GPH_MFP2_PH10MFP_UART0_TXD   (0x08UL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for UART0_TXD  */
#define SYS_GPH_MFP2_PH10MFP_UART9_TXD   (0x0dUL<<SYS_GPH_MFP2_PH10MFP_Pos)/*!< GPH_MFP2 PH10 setting for UART9_TXD  */

/* PH.11 MFP */
#define SYS_GPH_MFP2_PH11MFP_GPIO        (0x00UL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for GPIO       */
#define SYS_GPH_MFP2_PH11MFP_EBI_AD15    (0x02UL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for EBI_AD15   */
#define SYS_GPH_MFP2_PH11MFP_QSPI0_MOSI1 (0x03UL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for QSPI0_MOSI1*/
#define SYS_GPH_MFP2_PH11MFP_UART4_RXD   (0x07UL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for UART4_RXD  */
#define SYS_GPH_MFP2_PH11MFP_UART0_RXD   (0x08UL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for UART0_RXD  */
#define SYS_GPH_MFP2_PH11MFP_EPWM0_CH5   (0x0bUL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for EPWM0_CH5  */
#define SYS_GPH_MFP2_PH11MFP_UART9_RXD   (0x0dUL<<SYS_GPH_MFP2_PH11MFP_Pos)/*!< GPH_MFP2 PH11 setting for UART9_RXD  */

/* PH.12 MFP */
#define SYS_GPH_MFP3_PH12MFP_GPIO        (0x00UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for GPIO       */
#define SYS_GPH_MFP3_PH12MFP_EBI_AD0     (0x02UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for EBI_AD0    */
#define SYS_GPH_MFP3_PH12MFP_UART9_TXD   (0x03UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for UART9_TXD  */
#define SYS_GPH_MFP3_PH12MFP_QSPI1_MISO1 (0x06UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for QSPI1_MISO1*/
#define SYS_GPH_MFP3_PH12MFP_CCAP_PIXCLK (0x07UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for CCAP_PIXCLK*/
#define SYS_GPH_MFP3_PH12MFP_CAN3_TXD    (0x0aUL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for CAN3_TXD   */
#define SYS_GPH_MFP3_PH12MFP_HBI_nCK     (0x10UL<<SYS_GPH_MFP3_PH12MFP_Pos)/*!< GPH_MFP3 PH12 setting for HBI_nCK    */

/* PH.13 MFP */
#define SYS_GPH_MFP3_PH13MFP_GPIO        (0x00UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for GPIO       */
#define SYS_GPH_MFP3_PH13MFP_EBI_AD1     (0x02UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for EBI_AD1    */
#define SYS_GPH_MFP3_PH13MFP_UART9_RXD   (0x03UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for UART9_RXD  */
#define SYS_GPH_MFP3_PH13MFP_QSPI1_MOSI1 (0x06UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for QSPI1_MOSI1*/
#define SYS_GPH_MFP3_PH13MFP_CCAP_SCLK   (0x07UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for CCAP_SCLK  */
#define SYS_GPH_MFP3_PH13MFP_CAN3_RXD    (0x0aUL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for CAN3_RXD   */
#define SYS_GPH_MFP3_PH13MFP_HBI_CK      (0x10UL<<SYS_GPH_MFP3_PH13MFP_Pos)/*!< GPH_MFP3 PH13 setting for HBI_CK     */

/* PH.14 MFP */
#define SYS_GPH_MFP3_PH14MFP_GPIO        (0x00UL<<SYS_GPH_MFP3_PH14MFP_Pos)/*!< GPH_MFP3 PH14 setting for GPIO       */
#define SYS_GPH_MFP3_PH14MFP_EBI_AD2     (0x02UL<<SYS_GPH_MFP3_PH14MFP_Pos)/*!< GPH_MFP3 PH14 setting for EBI_AD2    */
#define SYS_GPH_MFP3_PH14MFP_QSPI1_SS    (0x06UL<<SYS_GPH_MFP3_PH14MFP_Pos)/*!< GPH_MFP3 PH14 setting for QSPI1_SS   */
#define SYS_GPH_MFP3_PH14MFP_CCAP_SFIELD (0x07UL<<SYS_GPH_MFP3_PH14MFP_Pos)/*!< GPH_MFP3 PH14 setting for CCAP_SFIELD*/
#define SYS_GPH_MFP3_PH14MFP_HBI_RWDS    (0x10UL<<SYS_GPH_MFP3_PH14MFP_Pos)/*!< GPH_MFP3 PH14 setting for HBI_RWDS   */

/* PH.15 MFP */
#define SYS_GPH_MFP3_PH15MFP_GPIO        (0x00UL<<SYS_GPH_MFP3_PH15MFP_Pos)/*!< GPH_MFP3 PH15 setting for GPIO       */
#define SYS_GPH_MFP3_PH15MFP_EBI_AD3     (0x02UL<<SYS_GPH_MFP3_PH15MFP_Pos)/*!< GPH_MFP3 PH15 setting for EBI_AD3    */
#define SYS_GPH_MFP3_PH15MFP_QSPI1_CLK   (0x06UL<<SYS_GPH_MFP3_PH15MFP_Pos)/*!< GPH_MFP3 PH15 setting for QSPI1_CLK  */
#define SYS_GPH_MFP3_PH15MFP_CCAP_VSYNC  (0x07UL<<SYS_GPH_MFP3_PH15MFP_Pos)/*!< GPH_MFP3 PH15 setting for CCAP_VSYNC */
#define SYS_GPH_MFP3_PH15MFP_HBI_D4      (0x10UL<<SYS_GPH_MFP3_PH15MFP_Pos)/*!< GPH_MFP3 PH15 setting for HBI_D4     */

/* PI.6 MFP */
#define SYS_GPI_MFP1_PI6MFP_GPIO         (0x00UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for GPIO        */
#define SYS_GPI_MFP1_PI6MFP_SC1_nCD      (0x05UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for SC1_nCD     */
#define SYS_GPI_MFP1_PI6MFP_I2S0_BCLK    (0x06UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for I2S0_BCLK   */
#define SYS_GPI_MFP1_PI6MFP_SPI1_I2SMCLK (0x07UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for SPI1_I2SMCLK*/
#define SYS_GPI_MFP1_PI6MFP_UART2_TXD    (0x08UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for UART2_TXD   */
#define SYS_GPI_MFP1_PI6MFP_I2C1_SCL     (0x09UL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for I2C1_SCL    */
#define SYS_GPI_MFP1_PI6MFP_CAN3_TXD     (0x0dUL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for CAN3_TXD    */
#define SYS_GPI_MFP1_PI6MFP_USB_VBUS_ST  (0x0fUL<<SYS_GPI_MFP1_PI6MFP_Pos) /*!< GPI_MFP1 PI6 setting for USB_VBUS_ST */

/* PI.7 MFP */
#define SYS_GPI_MFP1_PI7MFP_GPIO         (0x00UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for GPIO        */
#define SYS_GPI_MFP1_PI7MFP_SC1_PWR      (0x05UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for SC1_PWR     */
#define SYS_GPI_MFP1_PI7MFP_I2S0_MCLK    (0x06UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for I2S0_MCLK   */
#define SYS_GPI_MFP1_PI7MFP_SPI1_MISO    (0x07UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for SPI1_MISO   */
#define SYS_GPI_MFP1_PI7MFP_UART2_RXD    (0x08UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for UART2_RXD   */
#define SYS_GPI_MFP1_PI7MFP_I2C1_SDA     (0x09UL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for I2C1_SDA    */
#define SYS_GPI_MFP1_PI7MFP_CAN3_RXD     (0x0dUL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for CAN3_RXD    */
#define SYS_GPI_MFP1_PI7MFP_USB_VBUS_EN  (0x0fUL<<SYS_GPI_MFP1_PI7MFP_Pos) /*!< GPI_MFP1 PI7 setting for USB_VBUS_EN */

/* PI.8 MFP */
#define SYS_GPI_MFP2_PI8MFP_GPIO         (0x00UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for GPIO        */
#define SYS_GPI_MFP2_PI8MFP_SC1_RST      (0x05UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for SC1_RST     */
#define SYS_GPI_MFP2_PI8MFP_I2S0_DI      (0x06UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for I2S0_DI     */
#define SYS_GPI_MFP2_PI8MFP_SPI1_MOSI    (0x07UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for SPI1_MOSI   */
#define SYS_GPI_MFP2_PI8MFP_UART2_nRTS   (0x08UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for UART2_nRTS  */
#define SYS_GPI_MFP2_PI8MFP_I2C0_SMBAL   (0x09UL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for I2C0_SMBAL  */
#define SYS_GPI_MFP2_PI8MFP_CAN2_TXD     (0x0dUL<<SYS_GPI_MFP2_PI8MFP_Pos) /*!< GPI_MFP2 PI8 setting for CAN2_TXD    */

/* PI.9 MFP */
#define SYS_GPI_MFP2_PI9MFP_GPIO         (0x00UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for GPIO        */
#define SYS_GPI_MFP2_PI9MFP_SC1_DAT      (0x05UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for SC1_DAT     */
#define SYS_GPI_MFP2_PI9MFP_I2S0_DO      (0x06UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for I2S0_DO     */
#define SYS_GPI_MFP2_PI9MFP_SPI1_CLK     (0x07UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for SPI1_CLK    */
#define SYS_GPI_MFP2_PI9MFP_UART2_nCTS   (0x08UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for UART2_nCTS  */
#define SYS_GPI_MFP2_PI9MFP_I2C0_SMBSUS  (0x09UL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for I2C0_SMBSUS */
#define SYS_GPI_MFP2_PI9MFP_CAN2_RXD     (0x0dUL<<SYS_GPI_MFP2_PI9MFP_Pos) /*!< GPI_MFP2 PI9 setting for CAN2_RXD    */

/* PI.10 MFP */
#define SYS_GPI_MFP2_PI10MFP_GPIO        (0x00UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for GPIO       */
#define SYS_GPI_MFP2_PI10MFP_SC1_CLK     (0x05UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for SC1_CLK    */
#define SYS_GPI_MFP2_PI10MFP_I2S0_LRCK   (0x06UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for I2S0_LRCK  */
#define SYS_GPI_MFP2_PI10MFP_SPI1_SS     (0x07UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for SPI1_SS    */
#define SYS_GPI_MFP2_PI10MFP_UART2_TXD   (0x08UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for UART2_TXD  */
#define SYS_GPI_MFP2_PI10MFP_I2C0_SCL    (0x09UL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for I2C0_SCL   */
#define SYS_GPI_MFP2_PI10MFP_CAN3_TXD    (0x0dUL<<SYS_GPI_MFP2_PI10MFP_Pos)/*!< GPI_MFP2 PI10 setting for CAN3_TXD   */

/* PI.11 MFP */
#define SYS_GPI_MFP2_PI11MFP_GPIO        (0x00UL<<SYS_GPI_MFP2_PI11MFP_Pos)/*!< GPI_MFP2 PI11 setting for GPIO       */
#define SYS_GPI_MFP2_PI11MFP_UART2_RXD   (0x08UL<<SYS_GPI_MFP2_PI11MFP_Pos)/*!< GPI_MFP2 PI11 setting for UART2_RXD  */
#define SYS_GPI_MFP2_PI11MFP_I2C0_SDA    (0x09UL<<SYS_GPI_MFP2_PI11MFP_Pos)/*!< GPI_MFP2 PI11 setting for I2C0_SDA   */
#define SYS_GPI_MFP2_PI11MFP_CAN3_RXD    (0x0dUL<<SYS_GPI_MFP2_PI11MFP_Pos)/*!< GPI_MFP2 PI11 setting for CAN3_RXD   */

/* PI.12 MFP */
#define SYS_GPI_MFP3_PI12MFP_GPIO        (0x00UL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for GPIO       */
#define SYS_GPI_MFP3_PI12MFP_SPIM_SS     (0x03UL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for SPIM_SS    */
#define SYS_GPI_MFP3_PI12MFP_QSPI0_MISO1 (0x04UL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for QSPI0_MISO1*/
#define SYS_GPI_MFP3_PI12MFP_CAN0_TXD    (0x0aUL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for CAN0_TXD   */
#define SYS_GPI_MFP3_PI12MFP_UART4_TXD   (0x0bUL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for UART4_TXD  */
#define SYS_GPI_MFP3_PI12MFP_EPWM1_CH0   (0x0cUL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for EPWM1_CH0  */
#define SYS_GPI_MFP3_PI12MFP_I2C3_SMBAL  (0x0fUL<<SYS_GPI_MFP3_PI12MFP_Pos)/*!< GPI_MFP3 PI12 setting for I2C3_SMBAL */

/* PI.13 MFP */
#define SYS_GPI_MFP3_PI13MFP_GPIO        (0x00UL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for GPIO       */
#define SYS_GPI_MFP3_PI13MFP_SPIM_MISO   (0x03UL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for SPIM_MISO  */
#define SYS_GPI_MFP3_PI13MFP_QSPI0_MOSI1 (0x04UL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for QSPI0_MOSI1*/
#define SYS_GPI_MFP3_PI13MFP_CAN0_RXD    (0x0aUL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for CAN0_RXD   */
#define SYS_GPI_MFP3_PI13MFP_UART4_RXD   (0x0bUL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for UART4_RXD  */
#define SYS_GPI_MFP3_PI13MFP_EPWM1_CH1   (0x0cUL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for EPWM1_CH1  */
#define SYS_GPI_MFP3_PI13MFP_I2C3_SMBSUS (0x0fUL<<SYS_GPI_MFP3_PI13MFP_Pos)/*!< GPI_MFP3 PI13 setting for I2C3_SMBSUS*/

/* PI.14 MFP */
#define SYS_GPI_MFP3_PI14MFP_GPIO        (0x00UL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for GPIO       */
#define SYS_GPI_MFP3_PI14MFP_SPIM_D2     (0x03UL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for SPIM_D2    */
#define SYS_GPI_MFP3_PI14MFP_QSPI0_SS    (0x04UL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for QSPI0_SS   */
#define SYS_GPI_MFP3_PI14MFP_UART8_nCTS  (0x07UL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for UART8_nCTS */
#define SYS_GPI_MFP3_PI14MFP_CAN1_TXD    (0x0aUL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for CAN1_TXD   */
#define SYS_GPI_MFP3_PI14MFP_UART3_TXD   (0x0bUL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for UART3_TXD  */
#define SYS_GPI_MFP3_PI14MFP_EPWM1_CH2   (0x0cUL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for EPWM1_CH2  */
#define SYS_GPI_MFP3_PI14MFP_I2C3_SCL    (0x0fUL<<SYS_GPI_MFP3_PI14MFP_Pos)/*!< GPI_MFP3 PI14 setting for I2C3_SCL   */

/* PI.15 MFP */
#define SYS_GPI_MFP3_PI15MFP_GPIO        (0x00UL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for GPIO       */
#define SYS_GPI_MFP3_PI15MFP_SPIM_D3     (0x03UL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for SPIM_D3    */
#define SYS_GPI_MFP3_PI15MFP_QSPI0_CLK   (0x04UL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for QSPI0_CLK  */
#define SYS_GPI_MFP3_PI15MFP_UART8_nRTS  (0x07UL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for UART8_nRTS */
#define SYS_GPI_MFP3_PI15MFP_CAN1_RXD    (0x0aUL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for CAN1_RXD   */
#define SYS_GPI_MFP3_PI15MFP_UART3_RXD   (0x0bUL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for UART3_RXD  */
#define SYS_GPI_MFP3_PI15MFP_EPWM1_CH3   (0x0cUL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for EPWM1_CH3  */
#define SYS_GPI_MFP3_PI15MFP_I2C3_SDA    (0x0fUL<<SYS_GPI_MFP3_PI15MFP_Pos)/*!< GPI_MFP3 PI15 setting for I2C3_SDA   */

/* PJ.0 MFP */
#define SYS_GPJ_MFP0_PJ0MFP_GPIO         (0x00UL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for GPIO        */
#define SYS_GPJ_MFP0_PJ0MFP_SPIM_CLK     (0x03UL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for SPIM_CLK    */
#define SYS_GPJ_MFP0_PJ0MFP_QSPI0_MISO0  (0x04UL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for QSPI0_MISO0 */
#define SYS_GPJ_MFP0_PJ0MFP_UART8_TXD    (0x07UL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for UART8_TXD   */
#define SYS_GPJ_MFP0_PJ0MFP_CAN2_TXD     (0x0aUL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for CAN2_TXD    */
#define SYS_GPJ_MFP0_PJ0MFP_EPWM1_CH4    (0x0cUL<<SYS_GPJ_MFP0_PJ0MFP_Pos) /*!< GPJ_MFP0 PJ0 setting for EPWM1_CH4   */

/* PJ.1 MFP */
#define SYS_GPJ_MFP0_PJ1MFP_GPIO         (0x00UL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for GPIO        */
#define SYS_GPJ_MFP0_PJ1MFP_SPIM_MOSI    (0x03UL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for SPIM_MOSI   */
#define SYS_GPJ_MFP0_PJ1MFP_QSPI0_MOSI0  (0x04UL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for QSPI0_MOSI0 */
#define SYS_GPJ_MFP0_PJ1MFP_UART8_RXD    (0x07UL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for UART8_RXD   */
#define SYS_GPJ_MFP0_PJ1MFP_CAN2_RXD     (0x0aUL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for CAN2_RXD    */
#define SYS_GPJ_MFP0_PJ1MFP_EPWM1_CH5    (0x0cUL<<SYS_GPJ_MFP0_PJ1MFP_Pos) /*!< GPJ_MFP0 PJ1 setting for EPWM1_CH5   */

/* PJ.2 MFP */
#define SYS_GPJ_MFP0_PJ2MFP_GPIO         (0x00UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for GPIO        */
#define SYS_GPJ_MFP0_PJ2MFP_EBI_AD5      (0x02UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for EBI_AD5     */
#define SYS_GPJ_MFP0_PJ2MFP_UART8_nCTS   (0x03UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for UART8_nCTS  */
#define SYS_GPJ_MFP0_PJ2MFP_QSPI1_SS     (0x06UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for QSPI1_SS    */
#define SYS_GPJ_MFP0_PJ2MFP_CCAP_DATA5   (0x07UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for CCAP_DATA5  */
#define SYS_GPJ_MFP0_PJ2MFP_CAN0_TXD     (0x0aUL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for CAN0_TXD    */
#define SYS_GPJ_MFP0_PJ2MFP_HBI_nRESET   (0x10UL<<SYS_GPJ_MFP0_PJ2MFP_Pos) /*!< GPJ_MFP0 PJ2 setting for HBI_nRESET  */

/* PJ.3 MFP */
#define SYS_GPJ_MFP0_PJ3MFP_GPIO         (0x00UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for GPIO        */
#define SYS_GPJ_MFP0_PJ3MFP_EBI_AD4      (0x02UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for EBI_AD4     */
#define SYS_GPJ_MFP0_PJ3MFP_UART8_nRTS   (0x03UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for UART8_nRTS  */
#define SYS_GPJ_MFP0_PJ3MFP_QSPI1_CLK    (0x06UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for QSPI1_CLK   */
#define SYS_GPJ_MFP0_PJ3MFP_CCAP_DATA4   (0x07UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for CCAP_DATA4  */
#define SYS_GPJ_MFP0_PJ3MFP_CAN0_RXD     (0x0aUL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for CAN0_RXD    */
#define SYS_GPJ_MFP0_PJ3MFP_HBI_D3       (0x10UL<<SYS_GPJ_MFP0_PJ3MFP_Pos) /*!< GPJ_MFP0 PJ3 setting for HBI_D3      */

/* PJ.4 MFP */
#define SYS_GPJ_MFP1_PJ4MFP_GPIO         (0x00UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for GPIO        */
#define SYS_GPJ_MFP1_PJ4MFP_EBI_AD3      (0x02UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for EBI_AD3     */
#define SYS_GPJ_MFP1_PJ4MFP_UART8_TXD    (0x03UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for UART8_TXD   */
#define SYS_GPJ_MFP1_PJ4MFP_QSPI1_MISO0  (0x06UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for QSPI1_MISO0 */
#define SYS_GPJ_MFP1_PJ4MFP_CCAP_DATA3   (0x07UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for CCAP_DATA3  */
#define SYS_GPJ_MFP1_PJ4MFP_CAN1_TXD     (0x0aUL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for CAN1_TXD    */
#define SYS_GPJ_MFP1_PJ4MFP_HBI_D2       (0x10UL<<SYS_GPJ_MFP1_PJ4MFP_Pos) /*!< GPJ_MFP1 PJ4 setting for HBI_D2      */

/* PJ.5 MFP */
#define SYS_GPJ_MFP1_PJ5MFP_GPIO         (0x00UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for GPIO        */
#define SYS_GPJ_MFP1_PJ5MFP_EBI_AD2      (0x02UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for EBI_AD2     */
#define SYS_GPJ_MFP1_PJ5MFP_UART8_RXD    (0x03UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for UART8_RXD   */
#define SYS_GPJ_MFP1_PJ5MFP_QSPI1_MOSI0  (0x06UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for QSPI1_MOSI0 */
#define SYS_GPJ_MFP1_PJ5MFP_CCAP_DATA2   (0x07UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for CCAP_DATA2  */
#define SYS_GPJ_MFP1_PJ5MFP_CAN1_RXD     (0x0aUL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for CAN1_RXD    */
#define SYS_GPJ_MFP1_PJ5MFP_HBI_D1       (0x10UL<<SYS_GPJ_MFP1_PJ5MFP_Pos) /*!< GPJ_MFP1 PJ5 setting for HBI_D1      */

/* PJ.6 MFP */
#define SYS_GPJ_MFP1_PJ6MFP_GPIO         (0x00UL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for GPIO        */
#define SYS_GPJ_MFP1_PJ6MFP_EBI_AD1      (0x02UL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for EBI_AD1     */
#define SYS_GPJ_MFP1_PJ6MFP_UART9_nCTS   (0x03UL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for UART9_nCTS  */
#define SYS_GPJ_MFP1_PJ6MFP_CCAP_DATA1   (0x07UL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for CCAP_DATA1  */
#define SYS_GPJ_MFP1_PJ6MFP_CAN2_TXD     (0x0aUL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for CAN2_TXD    */
#define SYS_GPJ_MFP1_PJ6MFP_HBI_D0       (0x10UL<<SYS_GPJ_MFP1_PJ6MFP_Pos) /*!< GPJ_MFP1 PJ6 setting for HBI_D0      */

/* PJ.7 MFP */
#define SYS_GPJ_MFP1_PJ7MFP_GPIO         (0x00UL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for GPIO        */
#define SYS_GPJ_MFP1_PJ7MFP_EBI_AD0      (0x02UL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for EBI_AD0     */
#define SYS_GPJ_MFP1_PJ7MFP_UART9_nRTS   (0x03UL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for UART9_nRTS  */
#define SYS_GPJ_MFP1_PJ7MFP_CCAP_DATA0   (0x07UL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for CCAP_DATA0  */
#define SYS_GPJ_MFP1_PJ7MFP_CAN2_RXD     (0x0aUL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for CAN2_RXD    */
#define SYS_GPJ_MFP1_PJ7MFP_HBI_nCS      (0x10UL<<SYS_GPJ_MFP1_PJ7MFP_Pos) /*!< GPJ_MFP1 PJ7 setting for HBI_nCS     */

/* PJ.8 MFP */
#define SYS_GPJ_MFP2_PJ8MFP_GPIO         (0x00UL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for GPIO        */
#define SYS_GPJ_MFP2_PJ8MFP_EBI_nRD      (0x02UL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for EBI_nRD     */
#define SYS_GPJ_MFP2_PJ8MFP_SD1_DAT3     (0x03UL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for SD1_DAT3    */
#define SYS_GPJ_MFP2_PJ8MFP_SPIM_SS      (0x04UL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for SPIM_SS     */
#define SYS_GPJ_MFP2_PJ8MFP_UART7_TXD    (0x06UL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for UART7_TXD   */
#define SYS_GPJ_MFP2_PJ8MFP_CAN2_TXD     (0x0bUL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for CAN2_TXD    */
#define SYS_GPJ_MFP2_PJ8MFP_BPWM0_CH5    (0x0cUL<<SYS_GPJ_MFP2_PJ8MFP_Pos) /*!< GPJ_MFP2 PJ8 setting for BPWM0_CH5   */

/* PJ.9 MFP */
#define SYS_GPJ_MFP2_PJ9MFP_GPIO         (0x00UL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for GPIO        */
#define SYS_GPJ_MFP2_PJ9MFP_EBI_nWR      (0x02UL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for EBI_nWR     */
#define SYS_GPJ_MFP2_PJ9MFP_SD1_DAT2     (0x03UL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for SD1_DAT2    */
#define SYS_GPJ_MFP2_PJ9MFP_SPIM_MISO    (0x04UL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for SPIM_MISO   */
#define SYS_GPJ_MFP2_PJ9MFP_UART7_RXD    (0x06UL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for UART7_RXD   */
#define SYS_GPJ_MFP2_PJ9MFP_CAN2_RXD     (0x0bUL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for CAN2_RXD    */
#define SYS_GPJ_MFP2_PJ9MFP_BPWM0_CH4    (0x0cUL<<SYS_GPJ_MFP2_PJ9MFP_Pos) /*!< GPJ_MFP2 PJ9 setting for BPWM0_CH4   */

/* PJ.10 MFP */
#define SYS_GPJ_MFP2_PJ10MFP_GPIO        (0x00UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for GPIO       */
#define SYS_GPJ_MFP2_PJ10MFP_EBI_MCLK    (0x02UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for EBI_MCLK   */
#define SYS_GPJ_MFP2_PJ10MFP_SD1_DAT1    (0x03UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for SD1_DAT1   */
#define SYS_GPJ_MFP2_PJ10MFP_SPIM_D2     (0x04UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for SPIM_D2    */
#define SYS_GPJ_MFP2_PJ10MFP_UART6_TXD   (0x06UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for UART6_TXD  */
#define SYS_GPJ_MFP2_PJ10MFP_I2C4_SCL    (0x08UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for I2C4_SCL   */
#define SYS_GPJ_MFP2_PJ10MFP_ECAP2_IC0   (0x09UL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for ECAP2_IC0  */
#define SYS_GPJ_MFP2_PJ10MFP_CAN0_TXD    (0x0bUL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for CAN0_TXD   */
#define SYS_GPJ_MFP2_PJ10MFP_BPWM0_CH3   (0x0cUL<<SYS_GPJ_MFP2_PJ10MFP_Pos)/*!< GPJ_MFP2 PJ10 setting for BPWM0_CH3  */

/* PJ.11 MFP */
#define SYS_GPJ_MFP2_PJ11MFP_GPIO        (0x00UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for GPIO       */
#define SYS_GPJ_MFP2_PJ11MFP_EBI_ALE     (0x02UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for EBI_ALE    */
#define SYS_GPJ_MFP2_PJ11MFP_SD1_DAT0    (0x03UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for SD1_DAT0   */
#define SYS_GPJ_MFP2_PJ11MFP_SPIM_D3     (0x04UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for SPIM_D3    */
#define SYS_GPJ_MFP2_PJ11MFP_UART6_RXD   (0x06UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for UART6_RXD  */
#define SYS_GPJ_MFP2_PJ11MFP_I2C4_SDA    (0x08UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for I2C4_SDA   */
#define SYS_GPJ_MFP2_PJ11MFP_ECAP2_IC1   (0x09UL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for ECAP2_IC1  */
#define SYS_GPJ_MFP2_PJ11MFP_CAN0_RXD    (0x0bUL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for CAN0_RXD   */
#define SYS_GPJ_MFP2_PJ11MFP_BPWM0_CH2   (0x0cUL<<SYS_GPJ_MFP2_PJ11MFP_Pos)/*!< GPJ_MFP2 PJ11 setting for BPWM0_CH2  */

/* PJ.12 MFP */
#define SYS_GPJ_MFP3_PJ12MFP_GPIO        (0x00UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for GPIO       */
#define SYS_GPJ_MFP3_PJ12MFP_EBI_nCS0    (0x02UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for EBI_nCS0   */
#define SYS_GPJ_MFP3_PJ12MFP_SD1_CMD     (0x03UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for SD1_CMD    */
#define SYS_GPJ_MFP3_PJ12MFP_SPIM_CLK    (0x04UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for SPIM_CLK   */
#define SYS_GPJ_MFP3_PJ12MFP_I2C4_SMBAL  (0x08UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for I2C4_SMBAL */
#define SYS_GPJ_MFP3_PJ12MFP_ECAP2_IC2   (0x09UL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for ECAP2_IC2  */
#define SYS_GPJ_MFP3_PJ12MFP_CAN1_TXD    (0x0bUL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for CAN1_TXD   */
#define SYS_GPJ_MFP3_PJ12MFP_BPWM0_CH1   (0x0cUL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for BPWM0_CH1  */
#define SYS_GPJ_MFP3_PJ12MFP_HSUSB_VBUS_ST (0x0fUL<<SYS_GPJ_MFP3_PJ12MFP_Pos)/*!< GPJ_MFP3 PJ12 setting for HSUSB_VBUS_ST*/

/* PJ.13 MFP */
#define SYS_GPJ_MFP3_PJ13MFP_GPIO        (0x00UL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for GPIO       */
#define SYS_GPJ_MFP3_PJ13MFP_SD1_CLK     (0x03UL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for SD1_CLK    */
#define SYS_GPJ_MFP3_PJ13MFP_SPIM_MOSI   (0x04UL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for SPIM_MOSI  */
#define SYS_GPJ_MFP3_PJ13MFP_I2C4_SMBSUS (0x08UL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for I2C4_SMBSUS*/
#define SYS_GPJ_MFP3_PJ13MFP_CAN1_RXD    (0x0bUL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for CAN1_RXD   */
#define SYS_GPJ_MFP3_PJ13MFP_BPWM0_CH0   (0x0cUL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for BPWM0_CH0  */
#define SYS_GPJ_MFP3_PJ13MFP_HSUSB_VBUS_EN (0x0fUL<<SYS_GPJ_MFP3_PJ13MFP_Pos)/*!< GPJ_MFP3 PJ13 setting for HSUSB_VBUS_EN*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function setting constant definitions abbreviation.                                              */
/*---------------------------------------------------------------------------------------------------------*/

#define ACMP0_N_PB3              SYS_GPB_MFP0_PB3MFP_ACMP0_N          /*!< GPB_MFP0 PB3 setting for ACMP0_N*/
#define ACMP0_O_PB7              SYS_GPB_MFP1_PB7MFP_ACMP0_O          /*!< GPB_MFP1 PB7 setting for ACMP0_O*/
#define ACMP0_O_PC1              SYS_GPC_MFP0_PC1MFP_ACMP0_O          /*!< GPC_MFP0 PC1 setting for ACMP0_O*/
#define ACMP0_O_PC12             SYS_GPC_MFP3_PC12MFP_ACMP0_O         /*!< GPC_MFP3 PC12 setting for ACMP0_O*/
#define ACMP0_O_PD6              SYS_GPD_MFP1_PD6MFP_ACMP0_O          /*!< GPD_MFP1 PD6 setting for ACMP0_O*/
#define ACMP0_O_PF0              SYS_GPF_MFP0_PF0MFP_ACMP0_O          /*!< GPF_MFP0 PF0 setting for ACMP0_O*/
#define ACMP0_P0_PA11            SYS_GPA_MFP2_PA11MFP_ACMP0_P0        /*!< GPA_MFP2 PA11 setting for ACMP0_P0*/
#define ACMP0_P1_PB2             SYS_GPB_MFP0_PB2MFP_ACMP0_P1         /*!< GPB_MFP0 PB2 setting for ACMP0_P1*/
#define ACMP0_P2_PB12            SYS_GPB_MFP3_PB12MFP_ACMP0_P2        /*!< GPB_MFP3 PB12 setting for ACMP0_P2*/
#define ACMP0_P3_PB13            SYS_GPB_MFP3_PB13MFP_ACMP0_P3        /*!< GPB_MFP3 PB13 setting for ACMP0_P3*/
#define ACMP0_WLAT_PA7           SYS_GPA_MFP1_PA7MFP_ACMP0_WLAT       /*!< GPA_MFP1 PA7 setting for ACMP0_WLAT*/
#define ACMP1_N_PB5              SYS_GPB_MFP1_PB5MFP_ACMP1_N          /*!< GPB_MFP1 PB5 setting for ACMP1_N*/
#define ACMP1_O_PC0              SYS_GPC_MFP0_PC0MFP_ACMP1_O          /*!< GPC_MFP0 PC0 setting for ACMP1_O*/
#define ACMP1_O_PD5              SYS_GPD_MFP1_PD5MFP_ACMP1_O          /*!< GPD_MFP1 PD5 setting for ACMP1_O*/
#define ACMP1_O_PB6              SYS_GPB_MFP1_PB6MFP_ACMP1_O          /*!< GPB_MFP1 PB6 setting for ACMP1_O*/
#define ACMP1_O_PC11             SYS_GPC_MFP2_PC11MFP_ACMP1_O         /*!< GPC_MFP2 PC11 setting for ACMP1_O*/
#define ACMP1_O_PF1              SYS_GPF_MFP0_PF1MFP_ACMP1_O          /*!< GPF_MFP0 PF1 setting for ACMP1_O*/
#define ACMP1_P0_PA10            SYS_GPA_MFP2_PA10MFP_ACMP1_P0        /*!< GPA_MFP2 PA10 setting for ACMP1_P0*/
#define ACMP1_P1_PB4             SYS_GPB_MFP1_PB4MFP_ACMP1_P1         /*!< GPB_MFP1 PB4 setting for ACMP1_P1*/
#define ACMP1_P2_PB12            SYS_GPB_MFP3_PB12MFP_ACMP1_P2        /*!< GPB_MFP3 PB12 setting for ACMP1_P2*/
#define ACMP1_P3_PB13            SYS_GPB_MFP3_PB13MFP_ACMP1_P3        /*!< GPB_MFP3 PB13 setting for ACMP1_P3*/
#define ACMP1_WLAT_PA6           SYS_GPA_MFP1_PA6MFP_ACMP1_WLAT       /*!< GPA_MFP1 PA6 setting for ACMP1_WLAT*/
#define ACMP2_N_PB6              SYS_GPB_MFP1_PB6MFP_ACMP2_N          /*!< GPB_MFP1 PB6 setting for ACMP2_N*/
#define ACMP2_O_PB1              SYS_GPB_MFP0_PB1MFP_ACMP2_O          /*!< GPB_MFP0 PB1 setting for ACMP2_O*/
#define ACMP2_O_PE7              SYS_GPE_MFP1_PE7MFP_ACMP2_O          /*!< GPE_MFP1 PE7 setting for ACMP2_O*/
#define ACMP2_O_PF3              SYS_GPF_MFP0_PF3MFP_ACMP2_O          /*!< GPF_MFP0 PF3 setting for ACMP2_O*/
#define ACMP2_P0_PB7             SYS_GPB_MFP1_PB7MFP_ACMP2_P0         /*!< GPB_MFP1 PB7 setting for ACMP2_P0*/
#define ACMP2_P1_PB8             SYS_GPB_MFP2_PB8MFP_ACMP2_P1         /*!< GPB_MFP2 PB8 setting for ACMP2_P1*/
#define ACMP2_P2_PB9             SYS_GPB_MFP2_PB9MFP_ACMP2_P2         /*!< GPB_MFP2 PB9 setting for ACMP2_P2*/
#define ACMP2_P3_PB10            SYS_GPB_MFP2_PB10MFP_ACMP2_P3        /*!< GPB_MFP2 PB10 setting for ACMP2_P3*/
#define ACMP2_WLAT_PC7           SYS_GPC_MFP1_PC7MFP_ACMP2_WLAT       /*!< GPC_MFP1 PC7 setting for ACMP2_WLAT*/
#define ACMP3_N_PB0              SYS_GPB_MFP0_PB0MFP_ACMP3_N          /*!< GPB_MFP0 PB0 setting for ACMP3_N*/
#define ACMP3_O_PB0              SYS_GPB_MFP0_PB0MFP_ACMP3_O          /*!< GPB_MFP0 PB0 setting for ACMP3_O*/
#define ACMP3_O_PF2              SYS_GPF_MFP0_PF2MFP_ACMP3_O          /*!< GPF_MFP0 PF2 setting for ACMP3_O*/
#define ACMP3_O_PE6              SYS_GPE_MFP1_PE6MFP_ACMP3_O          /*!< GPE_MFP1 PE6 setting for ACMP3_O*/
#define ACMP3_P0_PB1             SYS_GPB_MFP0_PB1MFP_ACMP3_P0         /*!< GPB_MFP0 PB1 setting for ACMP3_P0*/
#define ACMP3_P1_PC9             SYS_GPC_MFP2_PC9MFP_ACMP3_P1         /*!< GPC_MFP2 PC9 setting for ACMP3_P1*/
#define ACMP3_P2_PC10            SYS_GPC_MFP2_PC10MFP_ACMP3_P2        /*!< GPC_MFP2 PC10 setting for ACMP3_P2*/
#define ACMP3_P3_PC11            SYS_GPC_MFP2_PC11MFP_ACMP3_P3        /*!< GPC_MFP2 PC11 setting for ACMP3_P3*/
#define ACMP3_WLAT_PC6           SYS_GPC_MFP1_PC6MFP_ACMP3_WLAT       /*!< GPC_MFP1 PC6 setting for ACMP3_WLAT*/
#define BMC0_PB5                 SYS_GPB_MFP1_PB5MFP_BMC0             /*!< GPB_MFP1 PB5 setting for BMC0*/
#define BMC1_PB4                 SYS_GPB_MFP1_PB4MFP_BMC1             /*!< GPB_MFP1 PB4 setting for BMC1*/
#define BMC10_PF5                SYS_GPF_MFP1_PF5MFP_BMC10            /*!< GPF_MFP1 PF5 setting for BMC10*/
#define BMC11_PF4                SYS_GPF_MFP1_PF4MFP_BMC11            /*!< GPF_MFP1 PF4 setting for BMC11*/
#define BMC12_PA12               SYS_GPA_MFP3_PA12MFP_BMC12           /*!< GPA_MFP3 PA12 setting for BMC12*/
#define BMC12_PF3                SYS_GPF_MFP0_PF3MFP_BMC12            /*!< GPF_MFP0 PF3 setting for BMC12*/
#define BMC13_PF2                SYS_GPF_MFP0_PF2MFP_BMC13            /*!< GPF_MFP0 PF2 setting for BMC13*/
#define BMC13_PA13               SYS_GPA_MFP3_PA13MFP_BMC13           /*!< GPA_MFP3 PA13 setting for BMC13*/
#define BMC14_PA7                SYS_GPA_MFP1_PA7MFP_BMC14            /*!< GPA_MFP1 PA7 setting for BMC14*/
#define BMC14_PA14               SYS_GPA_MFP3_PA14MFP_BMC14           /*!< GPA_MFP3 PA14 setting for BMC14*/
#define BMC15_PA6                SYS_GPA_MFP1_PA6MFP_BMC15            /*!< GPA_MFP1 PA6 setting for BMC15*/
#define BMC15_PA15               SYS_GPA_MFP3_PA15MFP_BMC15           /*!< GPA_MFP3 PA15 setting for BMC15*/
#define BMC16_PA3                SYS_GPA_MFP0_PA3MFP_BMC16            /*!< GPA_MFP0 PA3 setting for BMC16*/
#define BMC16_PG9                SYS_GPG_MFP2_PG9MFP_BMC16            /*!< GPG_MFP2 PG9 setting for BMC16*/
#define BMC17_PA2                SYS_GPA_MFP0_PA2MFP_BMC17            /*!< GPA_MFP0 PA2 setting for BMC17*/
#define BMC17_PG10               SYS_GPG_MFP2_PG10MFP_BMC17           /*!< GPG_MFP2 PG10 setting for BMC17*/
#define BMC18_PA1                SYS_GPA_MFP0_PA1MFP_BMC18            /*!< GPA_MFP0 PA1 setting for BMC18*/
#define BMC18_PG11               SYS_GPG_MFP2_PG11MFP_BMC18           /*!< GPG_MFP2 PG11 setting for BMC18*/
#define BMC19_PA0                SYS_GPA_MFP0_PA0MFP_BMC19            /*!< GPA_MFP0 PA0 setting for BMC19*/
#define BMC19_PG12               SYS_GPG_MFP3_PG12MFP_BMC19           /*!< GPG_MFP3 PG12 setting for BMC19*/
#define BMC2_PB3                 SYS_GPB_MFP0_PB3MFP_BMC2             /*!< GPB_MFP0 PB3 setting for BMC2*/
#define BMC20_PB11               SYS_GPB_MFP2_PB11MFP_BMC20           /*!< GPB_MFP2 PB11 setting for BMC20*/
#define BMC20_PC5                SYS_GPC_MFP1_PC5MFP_BMC20            /*!< GPC_MFP1 PC5 setting for BMC20*/
#define BMC21_PC4                SYS_GPC_MFP1_PC4MFP_BMC21            /*!< GPC_MFP1 PC4 setting for BMC21*/
#define BMC21_PB10               SYS_GPB_MFP2_PB10MFP_BMC21           /*!< GPB_MFP2 PB10 setting for BMC21*/
#define BMC22_PB9                SYS_GPB_MFP2_PB9MFP_BMC22            /*!< GPB_MFP2 PB9 setting for BMC22*/
#define BMC22_PC3                SYS_GPC_MFP0_PC3MFP_BMC22            /*!< GPC_MFP0 PC3 setting for BMC22*/
#define BMC23_PC2                SYS_GPC_MFP0_PC2MFP_BMC23            /*!< GPC_MFP0 PC2 setting for BMC23*/
#define BMC23_PB8                SYS_GPB_MFP2_PB8MFP_BMC23            /*!< GPB_MFP2 PB8 setting for BMC23*/
#define BMC24_PC1                SYS_GPC_MFP0_PC1MFP_BMC24            /*!< GPC_MFP0 PC1 setting for BMC24*/
#define BMC24_PC7                SYS_GPC_MFP1_PC7MFP_BMC24            /*!< GPC_MFP1 PC7 setting for BMC24*/
#define BMC25_PC6                SYS_GPC_MFP1_PC6MFP_BMC25            /*!< GPC_MFP1 PC6 setting for BMC25*/
#define BMC25_PC0                SYS_GPC_MFP0_PC0MFP_BMC25            /*!< GPC_MFP0 PC0 setting for BMC25*/
#define BMC26_PC14               SYS_GPC_MFP3_PC14MFP_BMC26           /*!< GPC_MFP3 PC14 setting for BMC26*/
#define BMC27_PB15               SYS_GPB_MFP3_PB15MFP_BMC27           /*!< GPB_MFP3 PB15 setting for BMC27*/
#define BMC28_PB13               SYS_GPB_MFP3_PB13MFP_BMC28           /*!< GPB_MFP3 PB13 setting for BMC28*/
#define BMC29_PB12               SYS_GPB_MFP3_PB12MFP_BMC29           /*!< GPB_MFP3 PB12 setting for BMC29*/
#define BMC3_PB2                 SYS_GPB_MFP0_PB2MFP_BMC3             /*!< GPB_MFP0 PB2 setting for BMC3*/
#define BMC30_PB7                SYS_GPB_MFP1_PB7MFP_BMC30            /*!< GPB_MFP1 PB7 setting for BMC30*/
#define BMC31_PB6                SYS_GPB_MFP1_PB6MFP_BMC31            /*!< GPB_MFP1 PB6 setting for BMC31*/
#define BMC4_PB1                 SYS_GPB_MFP0_PB1MFP_BMC4             /*!< GPB_MFP0 PB1 setting for BMC4*/
#define BMC5_PB0                 SYS_GPB_MFP0_PB0MFP_BMC5             /*!< GPB_MFP0 PB0 setting for BMC5*/
#define BMC6_PA11                SYS_GPA_MFP2_PA11MFP_BMC6            /*!< GPA_MFP2 PA11 setting for BMC6*/
#define BMC7_PA10                SYS_GPA_MFP2_PA10MFP_BMC7            /*!< GPA_MFP2 PA10 setting for BMC7*/
#define BMC8_PA9                 SYS_GPA_MFP2_PA9MFP_BMC8             /*!< GPA_MFP2 PA9 setting for BMC8*/
#define BMC9_PA8                 SYS_GPA_MFP2_PA8MFP_BMC9             /*!< GPA_MFP2 PA8 setting for BMC9*/
#define BPWM0_CH0_PD13           SYS_GPD_MFP3_PD13MFP_BPWM0_CH0       /*!< GPD_MFP3 PD13 setting for BPWM0_CH0*/
#define BPWM0_CH0_PE2            SYS_GPE_MFP0_PE2MFP_BPWM0_CH0        /*!< GPE_MFP0 PE2 setting for BPWM0_CH0*/
#define BPWM0_CH0_PA0            SYS_GPA_MFP0_PA0MFP_BPWM0_CH0        /*!< GPA_MFP0 PA0 setting for BPWM0_CH0*/
#define BPWM0_CH0_PA11           SYS_GPA_MFP2_PA11MFP_BPWM0_CH0       /*!< GPA_MFP2 PA11 setting for BPWM0_CH0*/
#define BPWM0_CH0_PG14           SYS_GPG_MFP3_PG14MFP_BPWM0_CH0       /*!< GPG_MFP3 PG14 setting for BPWM0_CH0*/
#define BPWM0_CH0_PJ13           SYS_GPJ_MFP3_PJ13MFP_BPWM0_CH0       /*!< GPJ_MFP3 PJ13 setting for BPWM0_CH0*/
#define BPWM0_CH1_PE3            SYS_GPE_MFP0_PE3MFP_BPWM0_CH1        /*!< GPE_MFP0 PE3 setting for BPWM0_CH1*/
#define BPWM0_CH1_PG13           SYS_GPG_MFP3_PG13MFP_BPWM0_CH1       /*!< GPG_MFP3 PG13 setting for BPWM0_CH1*/
#define BPWM0_CH1_PA1            SYS_GPA_MFP0_PA1MFP_BPWM0_CH1        /*!< GPA_MFP0 PA1 setting for BPWM0_CH1*/
#define BPWM0_CH1_PJ12           SYS_GPJ_MFP3_PJ12MFP_BPWM0_CH1       /*!< GPJ_MFP3 PJ12 setting for BPWM0_CH1*/
#define BPWM0_CH1_PA10           SYS_GPA_MFP2_PA10MFP_BPWM0_CH1       /*!< GPA_MFP2 PA10 setting for BPWM0_CH1*/
#define BPWM0_CH2_PA9            SYS_GPA_MFP2_PA9MFP_BPWM0_CH2        /*!< GPA_MFP2 PA9 setting for BPWM0_CH2*/
#define BPWM0_CH2_PA2            SYS_GPA_MFP0_PA2MFP_BPWM0_CH2        /*!< GPA_MFP0 PA2 setting for BPWM0_CH2*/
#define BPWM0_CH2_PJ11           SYS_GPJ_MFP2_PJ11MFP_BPWM0_CH2       /*!< GPJ_MFP2 PJ11 setting for BPWM0_CH2*/
#define BPWM0_CH2_PE4            SYS_GPE_MFP1_PE4MFP_BPWM0_CH2        /*!< GPE_MFP1 PE4 setting for BPWM0_CH2*/
#define BPWM0_CH2_PG12           SYS_GPG_MFP3_PG12MFP_BPWM0_CH2       /*!< GPG_MFP3 PG12 setting for BPWM0_CH2*/
#define BPWM0_CH3_PE5            SYS_GPE_MFP1_PE5MFP_BPWM0_CH3        /*!< GPE_MFP1 PE5 setting for BPWM0_CH3*/
#define BPWM0_CH3_PJ10           SYS_GPJ_MFP2_PJ10MFP_BPWM0_CH3       /*!< GPJ_MFP2 PJ10 setting for BPWM0_CH3*/
#define BPWM0_CH3_PG11           SYS_GPG_MFP2_PG11MFP_BPWM0_CH3       /*!< GPG_MFP2 PG11 setting for BPWM0_CH3*/
#define BPWM0_CH3_PA8            SYS_GPA_MFP2_PA8MFP_BPWM0_CH3        /*!< GPA_MFP2 PA8 setting for BPWM0_CH3*/
#define BPWM0_CH3_PA3            SYS_GPA_MFP0_PA3MFP_BPWM0_CH3        /*!< GPA_MFP0 PA3 setting for BPWM0_CH3*/
#define BPWM0_CH4_PF5            SYS_GPF_MFP1_PF5MFP_BPWM0_CH4        /*!< GPF_MFP1 PF5 setting for BPWM0_CH4*/
#define BPWM0_CH4_PJ9            SYS_GPJ_MFP2_PJ9MFP_BPWM0_CH4        /*!< GPJ_MFP2 PJ9 setting for BPWM0_CH4*/
#define BPWM0_CH4_PG10           SYS_GPG_MFP2_PG10MFP_BPWM0_CH4       /*!< GPG_MFP2 PG10 setting for BPWM0_CH4*/
#define BPWM0_CH4_PC13           SYS_GPC_MFP3_PC13MFP_BPWM0_CH4       /*!< GPC_MFP3 PC13 setting for BPWM0_CH4*/
#define BPWM0_CH4_PA4            SYS_GPA_MFP1_PA4MFP_BPWM0_CH4        /*!< GPA_MFP1 PA4 setting for BPWM0_CH4*/
#define BPWM0_CH4_PE6            SYS_GPE_MFP1_PE6MFP_BPWM0_CH4        /*!< GPE_MFP1 PE6 setting for BPWM0_CH4*/
#define BPWM0_CH5_PJ8            SYS_GPJ_MFP2_PJ8MFP_BPWM0_CH5        /*!< GPJ_MFP2 PJ8 setting for BPWM0_CH5*/
#define BPWM0_CH5_PD12           SYS_GPD_MFP3_PD12MFP_BPWM0_CH5       /*!< GPD_MFP3 PD12 setting for BPWM0_CH5*/
#define BPWM0_CH5_PA5            SYS_GPA_MFP1_PA5MFP_BPWM0_CH5        /*!< GPA_MFP1 PA5 setting for BPWM0_CH5*/
#define BPWM0_CH5_PF4            SYS_GPF_MFP1_PF4MFP_BPWM0_CH5        /*!< GPF_MFP1 PF4 setting for BPWM0_CH5*/
#define BPWM0_CH5_PE7            SYS_GPE_MFP1_PE7MFP_BPWM0_CH5        /*!< GPE_MFP1 PE7 setting for BPWM0_CH5*/
#define BPWM0_CH5_PG9            SYS_GPG_MFP2_PG9MFP_BPWM0_CH5        /*!< GPG_MFP2 PG9 setting for BPWM0_CH5*/
#define BPWM1_CH0_PF3            SYS_GPF_MFP0_PF3MFP_BPWM1_CH0        /*!< GPF_MFP0 PF3 setting for BPWM1_CH0*/
#define BPWM1_CH0_PB11           SYS_GPB_MFP2_PB11MFP_BPWM1_CH0       /*!< GPB_MFP2 PB11 setting for BPWM1_CH0*/
#define BPWM1_CH0_PC7            SYS_GPC_MFP1_PC7MFP_BPWM1_CH0        /*!< GPC_MFP1 PC7 setting for BPWM1_CH0*/
#define BPWM1_CH0_PF0            SYS_GPF_MFP0_PF0MFP_BPWM1_CH0        /*!< GPF_MFP0 PF0 setting for BPWM1_CH0*/
#define BPWM1_CH1_PF1            SYS_GPF_MFP0_PF1MFP_BPWM1_CH1        /*!< GPF_MFP0 PF1 setting for BPWM1_CH1*/
#define BPWM1_CH1_PB10           SYS_GPB_MFP2_PB10MFP_BPWM1_CH1       /*!< GPB_MFP2 PB10 setting for BPWM1_CH1*/
#define BPWM1_CH1_PF2            SYS_GPF_MFP0_PF2MFP_BPWM1_CH1        /*!< GPF_MFP0 PF2 setting for BPWM1_CH1*/
#define BPWM1_CH1_PC6            SYS_GPC_MFP1_PC6MFP_BPWM1_CH1        /*!< GPC_MFP1 PC6 setting for BPWM1_CH1*/
#define BPWM1_CH2_PB9            SYS_GPB_MFP2_PB9MFP_BPWM1_CH2        /*!< GPB_MFP2 PB9 setting for BPWM1_CH2*/
#define BPWM1_CH2_PA7            SYS_GPA_MFP1_PA7MFP_BPWM1_CH2        /*!< GPA_MFP1 PA7 setting for BPWM1_CH2*/
#define BPWM1_CH2_PA12           SYS_GPA_MFP3_PA12MFP_BPWM1_CH2       /*!< GPA_MFP3 PA12 setting for BPWM1_CH2*/
#define BPWM1_CH3_PA6            SYS_GPA_MFP1_PA6MFP_BPWM1_CH3        /*!< GPA_MFP1 PA6 setting for BPWM1_CH3*/
#define BPWM1_CH3_PB8            SYS_GPB_MFP2_PB8MFP_BPWM1_CH3        /*!< GPB_MFP2 PB8 setting for BPWM1_CH3*/
#define BPWM1_CH3_PA13           SYS_GPA_MFP3_PA13MFP_BPWM1_CH3       /*!< GPA_MFP3 PA13 setting for BPWM1_CH3*/
#define BPWM1_CH4_PB7            SYS_GPB_MFP1_PB7MFP_BPWM1_CH4        /*!< GPB_MFP1 PB7 setting for BPWM1_CH4*/
#define BPWM1_CH4_PC8            SYS_GPC_MFP2_PC8MFP_BPWM1_CH4        /*!< GPC_MFP2 PC8 setting for BPWM1_CH4*/
#define BPWM1_CH4_PA14           SYS_GPA_MFP3_PA14MFP_BPWM1_CH4       /*!< GPA_MFP3 PA14 setting for BPWM1_CH4*/
#define BPWM1_CH5_PB6            SYS_GPB_MFP1_PB6MFP_BPWM1_CH5        /*!< GPB_MFP1 PB6 setting for BPWM1_CH5*/
#define BPWM1_CH5_PE13           SYS_GPE_MFP3_PE13MFP_BPWM1_CH5       /*!< GPE_MFP3 PE13 setting for BPWM1_CH5*/
#define BPWM1_CH5_PA15           SYS_GPA_MFP3_PA15MFP_BPWM1_CH5       /*!< GPA_MFP3 PA15 setting for BPWM1_CH5*/
#define CAN0_RXD_PI13            SYS_GPI_MFP3_PI13MFP_CAN0_RXD        /*!< GPI_MFP3 PI13 setting for CAN0_RXD*/
#define CAN0_RXD_PJ3             SYS_GPJ_MFP0_PJ3MFP_CAN0_RXD         /*!< GPJ_MFP0 PJ3 setting for CAN0_RXD*/
#define CAN0_RXD_PA4             SYS_GPA_MFP1_PA4MFP_CAN0_RXD         /*!< GPA_MFP1 PA4 setting for CAN0_RXD*/
#define CAN0_RXD_PE15            SYS_GPE_MFP3_PE15MFP_CAN0_RXD        /*!< GPE_MFP3 PE15 setting for CAN0_RXD*/
#define CAN0_RXD_PA13            SYS_GPA_MFP3_PA13MFP_CAN0_RXD        /*!< GPA_MFP3 PA13 setting for CAN0_RXD*/
#define CAN0_RXD_PJ11            SYS_GPJ_MFP2_PJ11MFP_CAN0_RXD        /*!< GPJ_MFP2 PJ11 setting for CAN0_RXD*/
#define CAN0_RXD_PC4             SYS_GPC_MFP1_PC4MFP_CAN0_RXD         /*!< GPC_MFP1 PC4 setting for CAN0_RXD*/
#define CAN0_RXD_PB10            SYS_GPB_MFP2_PB10MFP_CAN0_RXD        /*!< GPB_MFP2 PB10 setting for CAN0_RXD*/
#define CAN0_RXD_PD10            SYS_GPD_MFP2_PD10MFP_CAN0_RXD        /*!< GPD_MFP2 PD10 setting for CAN0_RXD*/
#define CAN0_TXD_PC5             SYS_GPC_MFP1_PC5MFP_CAN0_TXD         /*!< GPC_MFP1 PC5 setting for CAN0_TXD*/
#define CAN0_TXD_PB11            SYS_GPB_MFP2_PB11MFP_CAN0_TXD        /*!< GPB_MFP2 PB11 setting for CAN0_TXD*/
#define CAN0_TXD_PA5             SYS_GPA_MFP1_PA5MFP_CAN0_TXD         /*!< GPA_MFP1 PA5 setting for CAN0_TXD*/
#define CAN0_TXD_PJ10            SYS_GPJ_MFP2_PJ10MFP_CAN0_TXD        /*!< GPJ_MFP2 PJ10 setting for CAN0_TXD*/
#define CAN0_TXD_PD11            SYS_GPD_MFP2_PD11MFP_CAN0_TXD        /*!< GPD_MFP2 PD11 setting for CAN0_TXD*/
#define CAN0_TXD_PA12            SYS_GPA_MFP3_PA12MFP_CAN0_TXD        /*!< GPA_MFP3 PA12 setting for CAN0_TXD*/
#define CAN0_TXD_PI12            SYS_GPI_MFP3_PI12MFP_CAN0_TXD        /*!< GPI_MFP3 PI12 setting for CAN0_TXD*/
#define CAN0_TXD_PE14            SYS_GPE_MFP3_PE14MFP_CAN0_TXD        /*!< GPE_MFP3 PE14 setting for CAN0_TXD*/
#define CAN0_TXD_PJ2             SYS_GPJ_MFP0_PJ2MFP_CAN0_TXD         /*!< GPJ_MFP0 PJ2 setting for CAN0_TXD*/
#define CAN1_RXD_PJ5             SYS_GPJ_MFP1_PJ5MFP_CAN1_RXD         /*!< GPJ_MFP1 PJ5 setting for CAN1_RXD*/
#define CAN1_RXD_PC9             SYS_GPC_MFP2_PC9MFP_CAN1_RXD         /*!< GPC_MFP2 PC9 setting for CAN1_RXD*/
#define CAN1_RXD_PD12            SYS_GPD_MFP3_PD12MFP_CAN1_RXD        /*!< GPD_MFP3 PD12 setting for CAN1_RXD*/
#define CAN1_RXD_PF8             SYS_GPF_MFP2_PF8MFP_CAN1_RXD         /*!< GPF_MFP2 PF8 setting for CAN1_RXD*/
#define CAN1_RXD_PG1             SYS_GPG_MFP0_PG1MFP_CAN1_RXD         /*!< GPG_MFP0 PG1 setting for CAN1_RXD*/
#define CAN1_RXD_PB6             SYS_GPB_MFP1_PB6MFP_CAN1_RXD         /*!< GPB_MFP1 PB6 setting for CAN1_RXD*/
#define CAN1_RXD_PI15            SYS_GPI_MFP3_PI15MFP_CAN1_RXD        /*!< GPI_MFP3 PI15 setting for CAN1_RXD*/
#define CAN1_RXD_PC2             SYS_GPC_MFP0_PC2MFP_CAN1_RXD         /*!< GPC_MFP0 PC2 setting for CAN1_RXD*/
#define CAN1_RXD_PJ13            SYS_GPJ_MFP3_PJ13MFP_CAN1_RXD        /*!< GPJ_MFP3 PJ13 setting for CAN1_RXD*/
#define CAN1_RXD_PE6             SYS_GPE_MFP1_PE6MFP_CAN1_RXD         /*!< GPE_MFP1 PE6 setting for CAN1_RXD*/
#define CAN1_TXD_PG0             SYS_GPG_MFP0_PG0MFP_CAN1_TXD         /*!< GPG_MFP0 PG0 setting for CAN1_TXD*/
#define CAN1_TXD_PB7             SYS_GPB_MFP1_PB7MFP_CAN1_TXD         /*!< GPB_MFP1 PB7 setting for CAN1_TXD*/
#define CAN1_TXD_PC3             SYS_GPC_MFP0_PC3MFP_CAN1_TXD         /*!< GPC_MFP0 PC3 setting for CAN1_TXD*/
#define CAN1_TXD_PI14            SYS_GPI_MFP3_PI14MFP_CAN1_TXD        /*!< GPI_MFP3 PI14 setting for CAN1_TXD*/
#define CAN1_TXD_PC10            SYS_GPC_MFP2_PC10MFP_CAN1_TXD        /*!< GPC_MFP2 PC10 setting for CAN1_TXD*/
#define CAN1_TXD_PE7             SYS_GPE_MFP1_PE7MFP_CAN1_TXD         /*!< GPE_MFP1 PE7 setting for CAN1_TXD*/
#define CAN1_TXD_PJ12            SYS_GPJ_MFP3_PJ12MFP_CAN1_TXD        /*!< GPJ_MFP3 PJ12 setting for CAN1_TXD*/
#define CAN1_TXD_PC13            SYS_GPC_MFP3_PC13MFP_CAN1_TXD        /*!< GPC_MFP3 PC13 setting for CAN1_TXD*/
#define CAN1_TXD_PJ4             SYS_GPJ_MFP1_PJ4MFP_CAN1_TXD         /*!< GPJ_MFP1 PJ4 setting for CAN1_TXD*/
#define CAN1_TXD_PF9             SYS_GPF_MFP2_PF9MFP_CAN1_TXD         /*!< GPF_MFP2 PF9 setting for CAN1_TXD*/
#define CAN2_RXD_PF1             SYS_GPF_MFP0_PF1MFP_CAN2_RXD         /*!< GPF_MFP0 PF1 setting for CAN2_RXD*/
#define CAN2_RXD_PJ1             SYS_GPJ_MFP0_PJ1MFP_CAN2_RXD         /*!< GPJ_MFP0 PJ1 setting for CAN2_RXD*/
#define CAN2_RXD_PF6             SYS_GPF_MFP1_PF6MFP_CAN2_RXD         /*!< GPF_MFP1 PF6 setting for CAN2_RXD*/
#define CAN2_RXD_PI9             SYS_GPI_MFP2_PI9MFP_CAN2_RXD         /*!< GPI_MFP2 PI9 setting for CAN2_RXD*/
#define CAN2_RXD_PD8             SYS_GPD_MFP2_PD8MFP_CAN2_RXD         /*!< GPD_MFP2 PD8 setting for CAN2_RXD*/
#define CAN2_RXD_PB8             SYS_GPB_MFP2_PB8MFP_CAN2_RXD         /*!< GPB_MFP2 PB8 setting for CAN2_RXD*/
#define CAN2_RXD_PJ7             SYS_GPJ_MFP1_PJ7MFP_CAN2_RXD         /*!< GPJ_MFP1 PJ7 setting for CAN2_RXD*/
#define CAN2_RXD_PC0             SYS_GPC_MFP0_PC0MFP_CAN2_RXD         /*!< GPC_MFP0 PC0 setting for CAN2_RXD*/
#define CAN2_RXD_PJ9             SYS_GPJ_MFP2_PJ9MFP_CAN2_RXD         /*!< GPJ_MFP2 PJ9 setting for CAN2_RXD*/
#define CAN2_TXD_PB9             SYS_GPB_MFP2_PB9MFP_CAN2_TXD         /*!< GPB_MFP2 PB9 setting for CAN2_TXD*/
#define CAN2_TXD_PC1             SYS_GPC_MFP0_PC1MFP_CAN2_TXD         /*!< GPC_MFP0 PC1 setting for CAN2_TXD*/
#define CAN2_TXD_PD9             SYS_GPD_MFP2_PD9MFP_CAN2_TXD         /*!< GPD_MFP2 PD9 setting for CAN2_TXD*/
#define CAN2_TXD_PF0             SYS_GPF_MFP0_PF0MFP_CAN2_TXD         /*!< GPF_MFP0 PF0 setting for CAN2_TXD*/
#define CAN2_TXD_PJ6             SYS_GPJ_MFP1_PJ6MFP_CAN2_TXD         /*!< GPJ_MFP1 PJ6 setting for CAN2_TXD*/
#define CAN2_TXD_PF7             SYS_GPF_MFP1_PF7MFP_CAN2_TXD         /*!< GPF_MFP1 PF7 setting for CAN2_TXD*/
#define CAN2_TXD_PJ8             SYS_GPJ_MFP2_PJ8MFP_CAN2_TXD         /*!< GPJ_MFP2 PJ8 setting for CAN2_TXD*/
#define CAN2_TXD_PJ0             SYS_GPJ_MFP0_PJ0MFP_CAN2_TXD         /*!< GPJ_MFP0 PJ0 setting for CAN2_TXD*/
#define CAN2_TXD_PI8             SYS_GPI_MFP2_PI8MFP_CAN2_TXD         /*!< GPI_MFP2 PI8 setting for CAN2_TXD*/
#define CAN3_RXD_PC6             SYS_GPC_MFP1_PC6MFP_CAN3_RXD         /*!< GPC_MFP1 PC6 setting for CAN3_RXD*/
#define CAN3_RXD_PH13            SYS_GPH_MFP3_PH13MFP_CAN3_RXD        /*!< GPH_MFP3 PH13 setting for CAN3_RXD*/
#define CAN3_RXD_PI7             SYS_GPI_MFP1_PI7MFP_CAN3_RXD         /*!< GPI_MFP1 PI7 setting for CAN3_RXD*/
#define CAN3_RXD_PF10            SYS_GPF_MFP2_PF10MFP_CAN3_RXD        /*!< GPF_MFP2 PF10 setting for CAN3_RXD*/
#define CAN3_RXD_PB12            SYS_GPB_MFP3_PB12MFP_CAN3_RXD        /*!< GPB_MFP3 PB12 setting for CAN3_RXD*/
#define CAN3_RXD_PI11            SYS_GPI_MFP2_PI11MFP_CAN3_RXD        /*!< GPI_MFP2 PI11 setting for CAN3_RXD*/
#define CAN3_TXD_PI6             SYS_GPI_MFP1_PI6MFP_CAN3_TXD         /*!< GPI_MFP1 PI6 setting for CAN3_TXD*/
#define CAN3_TXD_PC7             SYS_GPC_MFP1_PC7MFP_CAN3_TXD         /*!< GPC_MFP1 PC7 setting for CAN3_TXD*/
#define CAN3_TXD_PB13            SYS_GPB_MFP3_PB13MFP_CAN3_TXD        /*!< GPB_MFP3 PB13 setting for CAN3_TXD*/
#define CAN3_TXD_PH12            SYS_GPH_MFP3_PH12MFP_CAN3_TXD        /*!< GPH_MFP3 PH12 setting for CAN3_TXD*/
#define CAN3_TXD_PI10            SYS_GPI_MFP2_PI10MFP_CAN3_TXD        /*!< GPI_MFP2 PI10 setting for CAN3_TXD*/
#define CAN3_TXD_PF11            SYS_GPF_MFP2_PF11MFP_CAN3_TXD        /*!< GPF_MFP2 PF11 setting for CAN3_TXD*/
#define CCAP_DATA0_PB14          SYS_GPB_MFP3_PB14MFP_CCAP_DATA0      /*!< GPB_MFP3 PB14 setting for CCAP_DATA0*/
#define CCAP_DATA0_PC0           SYS_GPC_MFP0_PC0MFP_CCAP_DATA0       /*!< GPC_MFP0 PC0 setting for CCAP_DATA0*/
#define CCAP_DATA0_PJ7           SYS_GPJ_MFP1_PJ7MFP_CCAP_DATA0       /*!< GPJ_MFP1 PJ7 setting for CCAP_DATA0*/
#define CCAP_DATA0_PF7           SYS_GPF_MFP1_PF7MFP_CCAP_DATA0       /*!< GPF_MFP1 PF7 setting for CCAP_DATA0*/
#define CCAP_DATA1_PJ6           SYS_GPJ_MFP1_PJ6MFP_CCAP_DATA1       /*!< GPJ_MFP1 PJ6 setting for CCAP_DATA1*/
#define CCAP_DATA1_PB15          SYS_GPB_MFP3_PB15MFP_CCAP_DATA1      /*!< GPB_MFP3 PB15 setting for CCAP_DATA1*/
#define CCAP_DATA1_PC1           SYS_GPC_MFP0_PC1MFP_CCAP_DATA1       /*!< GPC_MFP0 PC1 setting for CCAP_DATA1*/
#define CCAP_DATA1_PF8           SYS_GPF_MFP2_PF8MFP_CCAP_DATA1       /*!< GPF_MFP2 PF8 setting for CCAP_DATA1*/
#define CCAP_DATA2_PJ5           SYS_GPJ_MFP1_PJ5MFP_CCAP_DATA2       /*!< GPJ_MFP1 PJ5 setting for CCAP_DATA2*/
#define CCAP_DATA2_PC2           SYS_GPC_MFP0_PC2MFP_CCAP_DATA2       /*!< GPC_MFP0 PC2 setting for CCAP_DATA2*/
#define CCAP_DATA2_PF9           SYS_GPF_MFP2_PF9MFP_CCAP_DATA2       /*!< GPF_MFP2 PF9 setting for CCAP_DATA2*/
#define CCAP_DATA3_PF10          SYS_GPF_MFP2_PF10MFP_CCAP_DATA3      /*!< GPF_MFP2 PF10 setting for CCAP_DATA3*/
#define CCAP_DATA3_PJ4           SYS_GPJ_MFP1_PJ4MFP_CCAP_DATA3       /*!< GPJ_MFP1 PJ4 setting for CCAP_DATA3*/
#define CCAP_DATA3_PC3           SYS_GPC_MFP0_PC3MFP_CCAP_DATA3       /*!< GPC_MFP0 PC3 setting for CCAP_DATA3*/
#define CCAP_DATA4_PC4           SYS_GPC_MFP1_PC4MFP_CCAP_DATA4       /*!< GPC_MFP1 PC4 setting for CCAP_DATA4*/
#define CCAP_DATA4_PF11          SYS_GPF_MFP2_PF11MFP_CCAP_DATA4      /*!< GPF_MFP2 PF11 setting for CCAP_DATA4*/
#define CCAP_DATA4_PJ3           SYS_GPJ_MFP0_PJ3MFP_CCAP_DATA4       /*!< GPJ_MFP0 PJ3 setting for CCAP_DATA4*/
#define CCAP_DATA5_PJ2           SYS_GPJ_MFP0_PJ2MFP_CCAP_DATA5       /*!< GPJ_MFP0 PJ2 setting for CCAP_DATA5*/
#define CCAP_DATA5_PC5           SYS_GPC_MFP1_PC5MFP_CCAP_DATA5       /*!< GPC_MFP1 PC5 setting for CCAP_DATA5*/
#define CCAP_DATA5_PG4           SYS_GPG_MFP1_PG4MFP_CCAP_DATA5       /*!< GPG_MFP1 PG4 setting for CCAP_DATA5*/
#define CCAP_DATA6_PG3           SYS_GPG_MFP0_PG3MFP_CCAP_DATA6       /*!< GPG_MFP0 PG3 setting for CCAP_DATA6*/
#define CCAP_DATA6_PA0           SYS_GPA_MFP0_PA0MFP_CCAP_DATA6       /*!< GPA_MFP0 PA0 setting for CCAP_DATA6*/
#define CCAP_DATA7_PA1           SYS_GPA_MFP0_PA1MFP_CCAP_DATA7       /*!< GPA_MFP0 PA1 setting for CCAP_DATA7*/
#define CCAP_DATA7_PG2           SYS_GPG_MFP0_PG2MFP_CCAP_DATA7       /*!< GPG_MFP0 PG2 setting for CCAP_DATA7*/
#define CCAP_HSYNC_PD7           SYS_GPD_MFP1_PD7MFP_CCAP_HSYNC       /*!< GPD_MFP1 PD7 setting for CCAP_HSYNC*/
#define CCAP_HSYNC_PG13          SYS_GPG_MFP3_PG13MFP_CCAP_HSYNC      /*!< GPG_MFP3 PG13 setting for CCAP_HSYNC*/
#define CCAP_HSYNC_PB9           SYS_GPB_MFP2_PB9MFP_CCAP_HSYNC       /*!< GPB_MFP2 PB9 setting for CCAP_HSYNC*/
#define CCAP_PIXCLK_PH12         SYS_GPH_MFP3_PH12MFP_CCAP_PIXCLK     /*!< GPH_MFP3 PH12 setting for CCAP_PIXCLK*/
#define CCAP_PIXCLK_PG9          SYS_GPG_MFP2_PG9MFP_CCAP_PIXCLK      /*!< GPG_MFP2 PG9 setting for CCAP_PIXCLK*/
#define CCAP_PIXCLK_PB13         SYS_GPB_MFP3_PB13MFP_CCAP_PIXCLK     /*!< GPB_MFP3 PB13 setting for CCAP_PIXCLK*/
#define CCAP_SCLK_PG10           SYS_GPG_MFP2_PG10MFP_CCAP_SCLK       /*!< GPG_MFP2 PG10 setting for CCAP_SCLK*/
#define CCAP_SCLK_PH13           SYS_GPH_MFP3_PH13MFP_CCAP_SCLK       /*!< GPH_MFP3 PH13 setting for CCAP_SCLK*/
#define CCAP_SCLK_PB12           SYS_GPB_MFP3_PB12MFP_CCAP_SCLK       /*!< GPB_MFP3 PB12 setting for CCAP_SCLK*/
#define CCAP_SFIELD_PG11         SYS_GPG_MFP2_PG11MFP_CCAP_SFIELD     /*!< GPG_MFP2 PG11 setting for CCAP_SFIELD*/
#define CCAP_SFIELD_PB11         SYS_GPB_MFP2_PB11MFP_CCAP_SFIELD     /*!< GPB_MFP2 PB11 setting for CCAP_SFIELD*/
#define CCAP_SFIELD_PH14         SYS_GPH_MFP3_PH14MFP_CCAP_SFIELD     /*!< GPH_MFP3 PH14 setting for CCAP_SFIELD*/
#define CCAP_VSYNC_PG12          SYS_GPG_MFP3_PG12MFP_CCAP_VSYNC      /*!< GPG_MFP3 PG12 setting for CCAP_VSYNC*/
#define CCAP_VSYNC_PB10          SYS_GPB_MFP2_PB10MFP_CCAP_VSYNC      /*!< GPB_MFP2 PB10 setting for CCAP_VSYNC*/
#define CCAP_VSYNC_PH15          SYS_GPH_MFP3_PH15MFP_CCAP_VSYNC      /*!< GPH_MFP3 PH15 setting for CCAP_VSYNC*/
#define CLKO_PC13                SYS_GPC_MFP3_PC13MFP_CLKO            /*!< GPC_MFP3 PC13 setting for CLKO*/
#define CLKO_PD13                SYS_GPD_MFP3_PD13MFP_CLKO            /*!< GPD_MFP3 PD13 setting for CLKO*/
#define CLKO_PG15                SYS_GPG_MFP3_PG15MFP_CLKO            /*!< GPG_MFP3 PG15 setting for CLKO*/
#define CLKO_PB14                SYS_GPB_MFP3_PB14MFP_CLKO            /*!< GPB_MFP3 PB14 setting for CLKO*/
#define CLKO_PD12                SYS_GPD_MFP3_PD12MFP_CLKO            /*!< GPD_MFP3 PD12 setting for CLKO*/
#define DAC0_OUT_PB12            SYS_GPB_MFP3_PB12MFP_DAC0_OUT        /*!< GPB_MFP3 PB12 setting for DAC0_OUT*/
#define DAC0_ST_PA0              SYS_GPA_MFP0_PA0MFP_DAC0_ST          /*!< GPA_MFP0 PA0 setting for DAC0_ST*/
#define DAC0_ST_PA10             SYS_GPA_MFP2_PA10MFP_DAC0_ST         /*!< GPA_MFP2 PA10 setting for DAC0_ST*/
#define DAC1_OUT_PB13            SYS_GPB_MFP3_PB13MFP_DAC1_OUT        /*!< GPB_MFP3 PB13 setting for DAC1_OUT*/
#define DAC1_ST_PA11             SYS_GPA_MFP2_PA11MFP_DAC1_ST         /*!< GPA_MFP2 PA11 setting for DAC1_ST*/
#define DAC1_ST_PA1              SYS_GPA_MFP0_PA1MFP_DAC1_ST          /*!< GPA_MFP0 PA1 setting for DAC1_ST*/
#define EADC0_CH0_PB0            SYS_GPB_MFP0_PB0MFP_EADC0_CH0        /*!< GPB_MFP0 PB0 setting for EADC0_CH0*/
#define EADC0_CH1_PB1            SYS_GPB_MFP0_PB1MFP_EADC0_CH1        /*!< GPB_MFP0 PB1 setting for EADC0_CH1*/
#define EADC0_CH10_PB10          SYS_GPB_MFP2_PB10MFP_EADC0_CH10      /*!< GPB_MFP2 PB10 setting for EADC0_CH10*/
#define EADC0_CH11_PB11          SYS_GPB_MFP2_PB11MFP_EADC0_CH11      /*!< GPB_MFP2 PB11 setting for EADC0_CH11*/
#define EADC0_CH12_PB12          SYS_GPB_MFP3_PB12MFP_EADC0_CH12      /*!< GPB_MFP3 PB12 setting for EADC0_CH12*/
#define EADC0_CH13_PB13          SYS_GPB_MFP3_PB13MFP_EADC0_CH13      /*!< GPB_MFP3 PB13 setting for EADC0_CH13*/
#define EADC0_CH14_PB14          SYS_GPB_MFP3_PB14MFP_EADC0_CH14      /*!< GPB_MFP3 PB14 setting for EADC0_CH14*/
#define EADC0_CH15_PB15          SYS_GPB_MFP3_PB15MFP_EADC0_CH15      /*!< GPB_MFP3 PB15 setting for EADC0_CH15*/
#define EADC0_CH2_PB2            SYS_GPB_MFP0_PB2MFP_EADC0_CH2        /*!< GPB_MFP0 PB2 setting for EADC0_CH2*/
#define EADC0_CH3_PB3            SYS_GPB_MFP0_PB3MFP_EADC0_CH3        /*!< GPB_MFP0 PB3 setting for EADC0_CH3*/
#define EADC0_CH4_PB4            SYS_GPB_MFP1_PB4MFP_EADC0_CH4        /*!< GPB_MFP1 PB4 setting for EADC0_CH4*/
#define EADC0_CH5_PB5            SYS_GPB_MFP1_PB5MFP_EADC0_CH5        /*!< GPB_MFP1 PB5 setting for EADC0_CH5*/
#define EADC0_CH6_PB6            SYS_GPB_MFP1_PB6MFP_EADC0_CH6        /*!< GPB_MFP1 PB6 setting for EADC0_CH6*/
#define EADC0_CH7_PB7            SYS_GPB_MFP1_PB7MFP_EADC0_CH7        /*!< GPB_MFP1 PB7 setting for EADC0_CH7*/
#define EADC0_CH8_PB8            SYS_GPB_MFP2_PB8MFP_EADC0_CH8        /*!< GPB_MFP2 PB8 setting for EADC0_CH8*/
#define EADC0_CH9_PB9            SYS_GPB_MFP2_PB9MFP_EADC0_CH9        /*!< GPB_MFP2 PB9 setting for EADC0_CH9*/
#define EADC0_ST_PF0             SYS_GPF_MFP0_PF0MFP_EADC0_ST         /*!< GPF_MFP0 PF0 setting for EADC0_ST*/
#define EADC0_ST_PD12            SYS_GPD_MFP3_PD12MFP_EADC0_ST        /*!< GPD_MFP3 PD12 setting for EADC0_ST*/
#define EADC0_ST_PD6             SYS_GPD_MFP1_PD6MFP_EADC0_ST         /*!< GPD_MFP1 PD6 setting for EADC0_ST*/
#define EADC0_ST_PC1             SYS_GPC_MFP0_PC1MFP_EADC0_ST         /*!< GPC_MFP0 PC1 setting for EADC0_ST*/
#define EADC0_ST_PF5             SYS_GPF_MFP1_PF5MFP_EADC0_ST         /*!< GPF_MFP1 PF5 setting for EADC0_ST*/
#define EADC0_ST_PG15            SYS_GPG_MFP3_PG15MFP_EADC0_ST        /*!< GPG_MFP3 PG15 setting for EADC0_ST*/
#define EADC0_ST_PD13            SYS_GPD_MFP3_PD13MFP_EADC0_ST        /*!< GPD_MFP3 PD13 setting for EADC0_ST*/
#define EADC0_ST_PC13            SYS_GPC_MFP3_PC13MFP_EADC0_ST        /*!< GPC_MFP3 PC13 setting for EADC0_ST*/
#define EADC1_CH0_PD10           SYS_GPD_MFP2_PD10MFP_EADC1_CH0       /*!< GPD_MFP2 PD10 setting for EADC1_CH0*/
#define EADC1_CH1_PD11           SYS_GPD_MFP2_PD11MFP_EADC1_CH1       /*!< GPD_MFP2 PD11 setting for EADC1_CH1*/
#define EADC1_CH10_PB2           SYS_GPB_MFP0_PB2MFP_EADC1_CH10       /*!< GPB_MFP0 PB2 setting for EADC1_CH10*/
#define EADC1_CH11_PB3           SYS_GPB_MFP0_PB3MFP_EADC1_CH11       /*!< GPB_MFP0 PB3 setting for EADC1_CH11*/
#define EADC1_CH12_PB12          SYS_GPB_MFP3_PB12MFP_EADC1_CH12      /*!< GPB_MFP3 PB12 setting for EADC1_CH12*/
#define EADC1_CH13_PB13          SYS_GPB_MFP3_PB13MFP_EADC1_CH13      /*!< GPB_MFP3 PB13 setting for EADC1_CH13*/
#define EADC1_CH14_PB14          SYS_GPB_MFP3_PB14MFP_EADC1_CH14      /*!< GPB_MFP3 PB14 setting for EADC1_CH14*/
#define EADC1_CH15_PB15          SYS_GPB_MFP3_PB15MFP_EADC1_CH15      /*!< GPB_MFP3 PB15 setting for EADC1_CH15*/
#define EADC1_CH2_PD12           SYS_GPD_MFP3_PD12MFP_EADC1_CH2       /*!< GPD_MFP3 PD12 setting for EADC1_CH2*/
#define EADC1_CH3_PC13           SYS_GPC_MFP3_PC13MFP_EADC1_CH3       /*!< GPC_MFP3 PC13 setting for EADC1_CH3*/
#define EADC1_CH4_PA8            SYS_GPA_MFP2_PA8MFP_EADC1_CH4        /*!< GPA_MFP2 PA8 setting for EADC1_CH4*/
#define EADC1_CH5_PA9            SYS_GPA_MFP2_PA9MFP_EADC1_CH5        /*!< GPA_MFP2 PA9 setting for EADC1_CH5*/
#define EADC1_CH6_PA10           SYS_GPA_MFP2_PA10MFP_EADC1_CH6       /*!< GPA_MFP2 PA10 setting for EADC1_CH6*/
#define EADC1_CH7_PA11           SYS_GPA_MFP2_PA11MFP_EADC1_CH7       /*!< GPA_MFP2 PA11 setting for EADC1_CH7*/
#define EADC1_CH8_PB0            SYS_GPB_MFP0_PB0MFP_EADC1_CH8        /*!< GPB_MFP0 PB0 setting for EADC1_CH8*/
#define EADC1_CH9_PB1            SYS_GPB_MFP0_PB1MFP_EADC1_CH9        /*!< GPB_MFP0 PB1 setting for EADC1_CH9*/
#define EADC1_ST_PC10            SYS_GPC_MFP2_PC10MFP_EADC1_ST        /*!< GPC_MFP2 PC10 setting for EADC1_ST*/
#define EADC1_ST_PD5             SYS_GPD_MFP1_PD5MFP_EADC1_ST         /*!< GPD_MFP1 PD5 setting for EADC1_ST*/
#define EADC1_ST_PC0             SYS_GPC_MFP0_PC0MFP_EADC1_ST         /*!< GPC_MFP0 PC0 setting for EADC1_ST*/
#define EADC1_ST_PF1             SYS_GPF_MFP0_PF1MFP_EADC1_ST         /*!< GPF_MFP0 PF1 setting for EADC1_ST*/
#define EADC1_ST_PF4             SYS_GPF_MFP1_PF4MFP_EADC1_ST         /*!< GPF_MFP1 PF4 setting for EADC1_ST*/
#define EADC1_ST_PC9             SYS_GPC_MFP2_PC9MFP_EADC1_ST         /*!< GPC_MFP2 PC9 setting for EADC1_ST*/
#define EADC2_CH0_PD10           SYS_GPD_MFP2_PD10MFP_EADC2_CH0       /*!< GPD_MFP2 PD10 setting for EADC2_CH0*/
#define EADC2_CH1_PD11           SYS_GPD_MFP2_PD11MFP_EADC2_CH1       /*!< GPD_MFP2 PD11 setting for EADC2_CH1*/
#define EADC2_CH10_PC9           SYS_GPC_MFP2_PC9MFP_EADC2_CH10       /*!< GPC_MFP2 PC9 setting for EADC2_CH10*/
#define EADC2_CH11_PC10          SYS_GPC_MFP2_PC10MFP_EADC2_CH11      /*!< GPC_MFP2 PC10 setting for EADC2_CH11*/
#define EADC2_CH12_PC11          SYS_GPC_MFP2_PC11MFP_EADC2_CH12      /*!< GPC_MFP2 PC11 setting for EADC2_CH12*/
#define EADC2_CH13_PC12          SYS_GPC_MFP3_PC12MFP_EADC2_CH13      /*!< GPC_MFP3 PC12 setting for EADC2_CH13*/
#define EADC2_CH14_PB6           SYS_GPB_MFP1_PB6MFP_EADC2_CH14       /*!< GPB_MFP1 PB6 setting for EADC2_CH14*/
#define EADC2_CH15_PB7           SYS_GPB_MFP1_PB7MFP_EADC2_CH15       /*!< GPB_MFP1 PB7 setting for EADC2_CH15*/
#define EADC2_CH2_PD12           SYS_GPD_MFP3_PD12MFP_EADC2_CH2       /*!< GPD_MFP3 PD12 setting for EADC2_CH2*/
#define EADC2_CH3_PC13           SYS_GPC_MFP3_PC13MFP_EADC2_CH3       /*!< GPC_MFP3 PC13 setting for EADC2_CH3*/
#define EADC2_CH4_PA8            SYS_GPA_MFP2_PA8MFP_EADC2_CH4        /*!< GPA_MFP2 PA8 setting for EADC2_CH4*/
#define EADC2_CH5_PA9            SYS_GPA_MFP2_PA9MFP_EADC2_CH5        /*!< GPA_MFP2 PA9 setting for EADC2_CH5*/
#define EADC2_CH6_PA10           SYS_GPA_MFP2_PA10MFP_EADC2_CH6       /*!< GPA_MFP2 PA10 setting for EADC2_CH6*/
#define EADC2_CH7_PA11           SYS_GPA_MFP2_PA11MFP_EADC2_CH7       /*!< GPA_MFP2 PA11 setting for EADC2_CH7*/
#define EADC2_CH8_PB0            SYS_GPB_MFP0_PB0MFP_EADC2_CH8        /*!< GPB_MFP0 PB0 setting for EADC2_CH8*/
#define EADC2_CH9_PB1            SYS_GPB_MFP0_PB1MFP_EADC2_CH9        /*!< GPB_MFP0 PB1 setting for EADC2_CH9*/
#define EADC2_ST_PF3             SYS_GPF_MFP0_PF3MFP_EADC2_ST         /*!< GPF_MFP0 PF3 setting for EADC2_ST*/
#define EADC2_ST_PB8             SYS_GPB_MFP2_PB8MFP_EADC2_ST         /*!< GPB_MFP2 PB8 setting for EADC2_ST*/
#define EBI_AD0_PJ7              SYS_GPJ_MFP1_PJ7MFP_EBI_AD0          /*!< GPJ_MFP1 PJ7 setting for EBI_AD0*/
#define EBI_AD0_PF4              SYS_GPF_MFP1_PF4MFP_EBI_AD0          /*!< GPF_MFP1 PF4 setting for EBI_AD0*/
#define EBI_AD0_PG9              SYS_GPG_MFP2_PG9MFP_EBI_AD0          /*!< GPG_MFP2 PG9 setting for EBI_AD0*/
#define EBI_AD0_PC0              SYS_GPC_MFP0_PC0MFP_EBI_AD0          /*!< GPC_MFP0 PC0 setting for EBI_AD0*/
#define EBI_AD0_PH12             SYS_GPH_MFP3_PH12MFP_EBI_AD0         /*!< GPH_MFP3 PH12 setting for EBI_AD0*/
#define EBI_AD1_PC1              SYS_GPC_MFP0_PC1MFP_EBI_AD1          /*!< GPC_MFP0 PC1 setting for EBI_AD1*/
#define EBI_AD1_PH13             SYS_GPH_MFP3_PH13MFP_EBI_AD1         /*!< GPH_MFP3 PH13 setting for EBI_AD1*/
#define EBI_AD1_PJ6              SYS_GPJ_MFP1_PJ6MFP_EBI_AD1          /*!< GPJ_MFP1 PJ6 setting for EBI_AD1*/
#define EBI_AD1_PG10             SYS_GPG_MFP2_PG10MFP_EBI_AD1         /*!< GPG_MFP2 PG10 setting for EBI_AD1*/
#define EBI_AD1_PF5              SYS_GPF_MFP1_PF5MFP_EBI_AD1          /*!< GPF_MFP1 PF5 setting for EBI_AD1*/
#define EBI_AD10_PD3             SYS_GPD_MFP0_PD3MFP_EBI_AD10         /*!< GPD_MFP0 PD3 setting for EBI_AD10*/
#define EBI_AD10_PE1             SYS_GPE_MFP0_PE1MFP_EBI_AD10         /*!< GPE_MFP0 PE1 setting for EBI_AD10*/
#define EBI_AD10_PD13            SYS_GPD_MFP3_PD13MFP_EBI_AD10        /*!< GPD_MFP3 PD13 setting for EBI_AD10*/
#define EBI_AD11_PE0             SYS_GPE_MFP0_PE0MFP_EBI_AD11         /*!< GPE_MFP0 PE0 setting for EBI_AD11*/
#define EBI_AD11_PC14            SYS_GPC_MFP3_PC14MFP_EBI_AD11        /*!< GPC_MFP3 PC14 setting for EBI_AD11*/
#define EBI_AD11_PD2             SYS_GPD_MFP0_PD2MFP_EBI_AD11         /*!< GPD_MFP0 PD2 setting for EBI_AD11*/
#define EBI_AD12_PD1             SYS_GPD_MFP0_PD1MFP_EBI_AD12         /*!< GPD_MFP0 PD1 setting for EBI_AD12*/
#define EBI_AD12_PH8             SYS_GPH_MFP2_PH8MFP_EBI_AD12         /*!< GPH_MFP2 PH8 setting for EBI_AD12*/
#define EBI_AD12_PB15            SYS_GPB_MFP3_PB15MFP_EBI_AD12        /*!< GPB_MFP3 PB15 setting for EBI_AD12*/
#define EBI_AD13_PD0             SYS_GPD_MFP0_PD0MFP_EBI_AD13         /*!< GPD_MFP0 PD0 setting for EBI_AD13*/
#define EBI_AD13_PH9             SYS_GPH_MFP2_PH9MFP_EBI_AD13         /*!< GPH_MFP2 PH9 setting for EBI_AD13*/
#define EBI_AD13_PB14            SYS_GPB_MFP3_PB14MFP_EBI_AD13        /*!< GPB_MFP3 PB14 setting for EBI_AD13*/
#define EBI_AD14_PB13            SYS_GPB_MFP3_PB13MFP_EBI_AD14        /*!< GPB_MFP3 PB13 setting for EBI_AD14*/
#define EBI_AD14_PH10            SYS_GPH_MFP2_PH10MFP_EBI_AD14        /*!< GPH_MFP2 PH10 setting for EBI_AD14*/
#define EBI_AD15_PB12            SYS_GPB_MFP3_PB12MFP_EBI_AD15        /*!< GPB_MFP3 PB12 setting for EBI_AD15*/
#define EBI_AD15_PH11            SYS_GPH_MFP2_PH11MFP_EBI_AD15        /*!< GPH_MFP2 PH11 setting for EBI_AD15*/
#define EBI_AD2_PH14             SYS_GPH_MFP3_PH14MFP_EBI_AD2         /*!< GPH_MFP3 PH14 setting for EBI_AD2*/
#define EBI_AD2_PG11             SYS_GPG_MFP2_PG11MFP_EBI_AD2         /*!< GPG_MFP2 PG11 setting for EBI_AD2*/
#define EBI_AD2_PC2              SYS_GPC_MFP0_PC2MFP_EBI_AD2          /*!< GPC_MFP0 PC2 setting for EBI_AD2*/
#define EBI_AD2_PJ5              SYS_GPJ_MFP1_PJ5MFP_EBI_AD2          /*!< GPJ_MFP1 PJ5 setting for EBI_AD2*/
#define EBI_AD3_PJ4              SYS_GPJ_MFP1_PJ4MFP_EBI_AD3          /*!< GPJ_MFP1 PJ4 setting for EBI_AD3*/
#define EBI_AD3_PH15             SYS_GPH_MFP3_PH15MFP_EBI_AD3         /*!< GPH_MFP3 PH15 setting for EBI_AD3*/
#define EBI_AD3_PG12             SYS_GPG_MFP3_PG12MFP_EBI_AD3         /*!< GPG_MFP3 PG12 setting for EBI_AD3*/
#define EBI_AD3_PC3              SYS_GPC_MFP0_PC3MFP_EBI_AD3          /*!< GPC_MFP0 PC3 setting for EBI_AD3*/
#define EBI_AD4_PG13             SYS_GPG_MFP3_PG13MFP_EBI_AD4         /*!< GPG_MFP3 PG13 setting for EBI_AD4*/
#define EBI_AD4_PJ3              SYS_GPJ_MFP0_PJ3MFP_EBI_AD4          /*!< GPJ_MFP0 PJ3 setting for EBI_AD4*/
#define EBI_AD4_PD7              SYS_GPD_MFP1_PD7MFP_EBI_AD4          /*!< GPD_MFP1 PD7 setting for EBI_AD4*/
#define EBI_AD4_PC4              SYS_GPC_MFP1_PC4MFP_EBI_AD4          /*!< GPC_MFP1 PC4 setting for EBI_AD4*/
#define EBI_AD5_PJ2              SYS_GPJ_MFP0_PJ2MFP_EBI_AD5          /*!< GPJ_MFP0 PJ2 setting for EBI_AD5*/
#define EBI_AD5_PA14             SYS_GPA_MFP3_PA14MFP_EBI_AD5         /*!< GPA_MFP3 PA14 setting for EBI_AD5*/
#define EBI_AD5_PD6              SYS_GPD_MFP1_PD6MFP_EBI_AD5          /*!< GPD_MFP1 PD6 setting for EBI_AD5*/
#define EBI_AD5_PG14             SYS_GPG_MFP3_PG14MFP_EBI_AD5         /*!< GPG_MFP3 PG14 setting for EBI_AD5*/
#define EBI_AD5_PC5              SYS_GPC_MFP1_PC5MFP_EBI_AD5          /*!< GPC_MFP1 PC5 setting for EBI_AD5*/
#define EBI_AD6_PD8              SYS_GPD_MFP2_PD8MFP_EBI_AD6          /*!< GPD_MFP2 PD8 setting for EBI_AD6*/
#define EBI_AD6_PA6              SYS_GPA_MFP1_PA6MFP_EBI_AD6          /*!< GPA_MFP1 PA6 setting for EBI_AD6*/
#define EBI_AD7_PA7              SYS_GPA_MFP1_PA7MFP_EBI_AD7          /*!< GPA_MFP1 PA7 setting for EBI_AD7*/
#define EBI_AD7_PD9              SYS_GPD_MFP2_PD9MFP_EBI_AD7          /*!< GPD_MFP2 PD9 setting for EBI_AD7*/
#define EBI_AD8_PC6              SYS_GPC_MFP1_PC6MFP_EBI_AD8          /*!< GPC_MFP1 PC6 setting for EBI_AD8*/
#define EBI_AD8_PE14             SYS_GPE_MFP3_PE14MFP_EBI_AD8         /*!< GPE_MFP3 PE14 setting for EBI_AD8*/
#define EBI_AD9_PE15             SYS_GPE_MFP3_PE15MFP_EBI_AD9         /*!< GPE_MFP3 PE15 setting for EBI_AD9*/
#define EBI_AD9_PC7              SYS_GPC_MFP1_PC7MFP_EBI_AD9          /*!< GPC_MFP1 PC7 setting for EBI_AD9*/
#define EBI_ADR0_PB5             SYS_GPB_MFP1_PB5MFP_EBI_ADR0         /*!< GPB_MFP1 PB5 setting for EBI_ADR0*/
#define EBI_ADR0_PH7             SYS_GPH_MFP1_PH7MFP_EBI_ADR0         /*!< GPH_MFP1 PH7 setting for EBI_ADR0*/
#define EBI_ADR1_PH6             SYS_GPH_MFP1_PH6MFP_EBI_ADR1         /*!< GPH_MFP1 PH6 setting for EBI_ADR1*/
#define EBI_ADR1_PB4             SYS_GPB_MFP1_PB4MFP_EBI_ADR1         /*!< GPB_MFP1 PB4 setting for EBI_ADR1*/
#define EBI_ADR10_PE8            SYS_GPE_MFP2_PE8MFP_EBI_ADR10        /*!< GPE_MFP2 PE8 setting for EBI_ADR10*/
#define EBI_ADR10_PC13           SYS_GPC_MFP3_PC13MFP_EBI_ADR10       /*!< GPC_MFP3 PC13 setting for EBI_ADR10*/
#define EBI_ADR11_PE9            SYS_GPE_MFP2_PE9MFP_EBI_ADR11        /*!< GPE_MFP2 PE9 setting for EBI_ADR11*/
#define EBI_ADR11_PG2            SYS_GPG_MFP0_PG2MFP_EBI_ADR11        /*!< GPG_MFP0 PG2 setting for EBI_ADR11*/
#define EBI_ADR12_PG3            SYS_GPG_MFP0_PG3MFP_EBI_ADR12        /*!< GPG_MFP0 PG3 setting for EBI_ADR12*/
#define EBI_ADR12_PE10           SYS_GPE_MFP2_PE10MFP_EBI_ADR12       /*!< GPE_MFP2 PE10 setting for EBI_ADR12*/
#define EBI_ADR13_PE11           SYS_GPE_MFP2_PE11MFP_EBI_ADR13       /*!< GPE_MFP2 PE11 setting for EBI_ADR13*/
#define EBI_ADR13_PG4            SYS_GPG_MFP1_PG4MFP_EBI_ADR13        /*!< GPG_MFP1 PG4 setting for EBI_ADR13*/
#define EBI_ADR14_PF11           SYS_GPF_MFP2_PF11MFP_EBI_ADR14       /*!< GPF_MFP2 PF11 setting for EBI_ADR14*/
#define EBI_ADR14_PE12           SYS_GPE_MFP3_PE12MFP_EBI_ADR14       /*!< GPE_MFP3 PE12 setting for EBI_ADR14*/
#define EBI_ADR15_PE13           SYS_GPE_MFP3_PE13MFP_EBI_ADR15       /*!< GPE_MFP3 PE13 setting for EBI_ADR15*/
#define EBI_ADR15_PF10           SYS_GPF_MFP2_PF10MFP_EBI_ADR15       /*!< GPF_MFP2 PF10 setting for EBI_ADR15*/
#define EBI_ADR16_PB11           SYS_GPB_MFP2_PB11MFP_EBI_ADR16       /*!< GPB_MFP2 PB11 setting for EBI_ADR16*/
#define EBI_ADR16_PC8            SYS_GPC_MFP2_PC8MFP_EBI_ADR16        /*!< GPC_MFP2 PC8 setting for EBI_ADR16*/
#define EBI_ADR16_PF9            SYS_GPF_MFP2_PF9MFP_EBI_ADR16        /*!< GPF_MFP2 PF9 setting for EBI_ADR16*/
#define EBI_ADR17_PB10           SYS_GPB_MFP2_PB10MFP_EBI_ADR17       /*!< GPB_MFP2 PB10 setting for EBI_ADR17*/
#define EBI_ADR17_PF8            SYS_GPF_MFP2_PF8MFP_EBI_ADR17        /*!< GPF_MFP2 PF8 setting for EBI_ADR17*/
#define EBI_ADR18_PF7            SYS_GPF_MFP1_PF7MFP_EBI_ADR18        /*!< GPF_MFP1 PF7 setting for EBI_ADR18*/
#define EBI_ADR18_PB9            SYS_GPB_MFP2_PB9MFP_EBI_ADR18        /*!< GPB_MFP2 PB9 setting for EBI_ADR18*/
#define EBI_ADR19_PF6            SYS_GPF_MFP1_PF6MFP_EBI_ADR19        /*!< GPF_MFP1 PF6 setting for EBI_ADR19*/
#define EBI_ADR19_PB8            SYS_GPB_MFP2_PB8MFP_EBI_ADR19        /*!< GPB_MFP2 PB8 setting for EBI_ADR19*/
#define EBI_ADR2_PB3             SYS_GPB_MFP0_PB3MFP_EBI_ADR2         /*!< GPB_MFP0 PB3 setting for EBI_ADR2*/
#define EBI_ADR2_PH5             SYS_GPH_MFP1_PH5MFP_EBI_ADR2         /*!< GPH_MFP1 PH5 setting for EBI_ADR2*/
#define EBI_ADR3_PH4             SYS_GPH_MFP1_PH4MFP_EBI_ADR3         /*!< GPH_MFP1 PH4 setting for EBI_ADR3*/
#define EBI_ADR3_PB2             SYS_GPB_MFP0_PB2MFP_EBI_ADR3         /*!< GPB_MFP0 PB2 setting for EBI_ADR3*/
#define EBI_ADR4_PC12            SYS_GPC_MFP3_PC12MFP_EBI_ADR4        /*!< GPC_MFP3 PC12 setting for EBI_ADR4*/
#define EBI_ADR4_PH3             SYS_GPH_MFP0_PH3MFP_EBI_ADR4         /*!< GPH_MFP0 PH3 setting for EBI_ADR4*/
#define EBI_ADR5_PH2             SYS_GPH_MFP0_PH2MFP_EBI_ADR5         /*!< GPH_MFP0 PH2 setting for EBI_ADR5*/
#define EBI_ADR5_PC11            SYS_GPC_MFP2_PC11MFP_EBI_ADR5        /*!< GPC_MFP2 PC11 setting for EBI_ADR5*/
#define EBI_ADR6_PC10            SYS_GPC_MFP2_PC10MFP_EBI_ADR6        /*!< GPC_MFP2 PC10 setting for EBI_ADR6*/
#define EBI_ADR6_PH1             SYS_GPH_MFP0_PH1MFP_EBI_ADR6         /*!< GPH_MFP0 PH1 setting for EBI_ADR6*/
#define EBI_ADR7_PH0             SYS_GPH_MFP0_PH0MFP_EBI_ADR7         /*!< GPH_MFP0 PH0 setting for EBI_ADR7*/
#define EBI_ADR7_PC9             SYS_GPC_MFP2_PC9MFP_EBI_ADR7         /*!< GPC_MFP2 PC9 setting for EBI_ADR7*/
#define EBI_ADR8_PG0             SYS_GPG_MFP0_PG0MFP_EBI_ADR8         /*!< GPG_MFP0 PG0 setting for EBI_ADR8*/
#define EBI_ADR8_PB1             SYS_GPB_MFP0_PB1MFP_EBI_ADR8         /*!< GPB_MFP0 PB1 setting for EBI_ADR8*/
#define EBI_ADR9_PB0             SYS_GPB_MFP0_PB0MFP_EBI_ADR9         /*!< GPB_MFP0 PB0 setting for EBI_ADR9*/
#define EBI_ADR9_PG1             SYS_GPG_MFP0_PG1MFP_EBI_ADR9         /*!< GPG_MFP0 PG1 setting for EBI_ADR9*/
#define EBI_ALE_PA8              SYS_GPA_MFP2_PA8MFP_EBI_ALE          /*!< GPA_MFP2 PA8 setting for EBI_ALE*/
#define EBI_ALE_PE2              SYS_GPE_MFP0_PE2MFP_EBI_ALE          /*!< GPE_MFP0 PE2 setting for EBI_ALE*/
#define EBI_ALE_PJ11             SYS_GPJ_MFP2_PJ11MFP_EBI_ALE         /*!< GPJ_MFP2 PJ11 setting for EBI_ALE*/
#define EBI_MCLK_PE3             SYS_GPE_MFP0_PE3MFP_EBI_MCLK         /*!< GPE_MFP0 PE3 setting for EBI_MCLK*/
#define EBI_MCLK_PA9             SYS_GPA_MFP2_PA9MFP_EBI_MCLK         /*!< GPA_MFP2 PA9 setting for EBI_MCLK*/
#define EBI_MCLK_PJ10            SYS_GPJ_MFP2_PJ10MFP_EBI_MCLK        /*!< GPJ_MFP2 PJ10 setting for EBI_MCLK*/
#define EBI_nCS0_PF3             SYS_GPF_MFP0_PF3MFP_EBI_nCS0         /*!< GPF_MFP0 PF3 setting for EBI_nCS0*/
#define EBI_nCS0_PJ12            SYS_GPJ_MFP3_PJ12MFP_EBI_nCS0        /*!< GPJ_MFP3 PJ12 setting for EBI_nCS0*/
#define EBI_nCS0_PD14            SYS_GPD_MFP3_PD14MFP_EBI_nCS0        /*!< GPD_MFP3 PD14 setting for EBI_nCS0*/
#define EBI_nCS0_PB7             SYS_GPB_MFP1_PB7MFP_EBI_nCS0         /*!< GPB_MFP1 PB7 setting for EBI_nCS0*/
#define EBI_nCS0_PF6             SYS_GPF_MFP1_PF6MFP_EBI_nCS0         /*!< GPF_MFP1 PF6 setting for EBI_nCS0*/
#define EBI_nCS0_PD12            SYS_GPD_MFP3_PD12MFP_EBI_nCS0        /*!< GPD_MFP3 PD12 setting for EBI_nCS0*/
#define EBI_nCS1_PB6             SYS_GPB_MFP1_PB6MFP_EBI_nCS1         /*!< GPB_MFP1 PB6 setting for EBI_nCS1*/
#define EBI_nCS1_PG5             SYS_GPG_MFP1_PG5MFP_EBI_nCS1         /*!< GPG_MFP1 PG5 setting for EBI_nCS1*/
#define EBI_nCS1_PD11            SYS_GPD_MFP2_PD11MFP_EBI_nCS1        /*!< GPD_MFP2 PD11 setting for EBI_nCS1*/
#define EBI_nCS1_PF2             SYS_GPF_MFP0_PF2MFP_EBI_nCS1         /*!< GPF_MFP0 PF2 setting for EBI_nCS1*/
#define EBI_nCS2_PD10            SYS_GPD_MFP2_PD10MFP_EBI_nCS2        /*!< GPD_MFP2 PD10 setting for EBI_nCS2*/
#define EBI_nCS2_PG6             SYS_GPG_MFP1_PG6MFP_EBI_nCS2         /*!< GPG_MFP1 PG6 setting for EBI_nCS2*/
#define EBI_nRD_PA11             SYS_GPA_MFP2_PA11MFP_EBI_nRD         /*!< GPA_MFP2 PA11 setting for EBI_nRD*/
#define EBI_nRD_PE5              SYS_GPE_MFP1_PE5MFP_EBI_nRD          /*!< GPE_MFP1 PE5 setting for EBI_nRD*/
#define EBI_nRD_PJ8              SYS_GPJ_MFP2_PJ8MFP_EBI_nRD          /*!< GPJ_MFP2 PJ8 setting for EBI_nRD*/
#define EBI_nWR_PA10             SYS_GPA_MFP2_PA10MFP_EBI_nWR         /*!< GPA_MFP2 PA10 setting for EBI_nWR*/
#define EBI_nWR_PJ9              SYS_GPJ_MFP2_PJ9MFP_EBI_nWR          /*!< GPJ_MFP2 PJ9 setting for EBI_nWR*/
#define EBI_nWR_PE4              SYS_GPE_MFP1_PE4MFP_EBI_nWR          /*!< GPE_MFP1 PE4 setting for EBI_nWR*/
#define EBI_nWRH_PB6             SYS_GPB_MFP1_PB6MFP_EBI_nWRH         /*!< GPB_MFP1 PB6 setting for EBI_nWRH*/
#define EBI_nWRH_PG8             SYS_GPG_MFP2_PG8MFP_EBI_nWRH         /*!< GPG_MFP2 PG8 setting for EBI_nWRH*/
#define EBI_nWRL_PG7             SYS_GPG_MFP1_PG7MFP_EBI_nWRL         /*!< GPG_MFP1 PG7 setting for EBI_nWRL*/
#define EBI_nWRL_PB7             SYS_GPB_MFP1_PB7MFP_EBI_nWRL         /*!< GPB_MFP1 PB7 setting for EBI_nWRL*/
#define ECAP0_IC0_PE8            SYS_GPE_MFP2_PE8MFP_ECAP0_IC0        /*!< GPE_MFP2 PE8 setting for ECAP0_IC0*/
#define ECAP0_IC0_PA10           SYS_GPA_MFP2_PA10MFP_ECAP0_IC0       /*!< GPA_MFP2 PA10 setting for ECAP0_IC0*/
#define ECAP0_IC1_PA9            SYS_GPA_MFP2_PA9MFP_ECAP0_IC1        /*!< GPA_MFP2 PA9 setting for ECAP0_IC1*/
#define ECAP0_IC1_PE9            SYS_GPE_MFP2_PE9MFP_ECAP0_IC1        /*!< GPE_MFP2 PE9 setting for ECAP0_IC1*/
#define ECAP0_IC2_PE10           SYS_GPE_MFP2_PE10MFP_ECAP0_IC2       /*!< GPE_MFP2 PE10 setting for ECAP0_IC2*/
#define ECAP0_IC2_PA8            SYS_GPA_MFP2_PA8MFP_ECAP0_IC2        /*!< GPA_MFP2 PA8 setting for ECAP0_IC2*/
#define ECAP1_IC0_PE13           SYS_GPE_MFP3_PE13MFP_ECAP1_IC0       /*!< GPE_MFP3 PE13 setting for ECAP1_IC0*/
#define ECAP1_IC0_PC10           SYS_GPC_MFP2_PC10MFP_ECAP1_IC0       /*!< GPC_MFP2 PC10 setting for ECAP1_IC0*/
#define ECAP1_IC1_PC11           SYS_GPC_MFP2_PC11MFP_ECAP1_IC1       /*!< GPC_MFP2 PC11 setting for ECAP1_IC1*/
#define ECAP1_IC1_PE12           SYS_GPE_MFP3_PE12MFP_ECAP1_IC1       /*!< GPE_MFP3 PE12 setting for ECAP1_IC1*/
#define ECAP1_IC2_PC12           SYS_GPC_MFP3_PC12MFP_ECAP1_IC2       /*!< GPC_MFP3 PC12 setting for ECAP1_IC2*/
#define ECAP1_IC2_PE11           SYS_GPE_MFP2_PE11MFP_ECAP1_IC2       /*!< GPE_MFP2 PE11 setting for ECAP1_IC2*/
#define ECAP2_IC0_PG9            SYS_GPG_MFP2_PG9MFP_ECAP2_IC0        /*!< GPG_MFP2 PG9 setting for ECAP2_IC0*/
#define ECAP2_IC0_PJ10           SYS_GPJ_MFP2_PJ10MFP_ECAP2_IC0       /*!< GPJ_MFP2 PJ10 setting for ECAP2_IC0*/
#define ECAP2_IC0_PD1            SYS_GPD_MFP0_PD1MFP_ECAP2_IC0        /*!< GPD_MFP0 PD1 setting for ECAP2_IC0*/
#define ECAP2_IC1_PD0            SYS_GPD_MFP0_PD0MFP_ECAP2_IC1        /*!< GPD_MFP0 PD0 setting for ECAP2_IC1*/
#define ECAP2_IC1_PJ11           SYS_GPJ_MFP2_PJ11MFP_ECAP2_IC1       /*!< GPJ_MFP2 PJ11 setting for ECAP2_IC1*/
#define ECAP2_IC1_PG10           SYS_GPG_MFP2_PG10MFP_ECAP2_IC1       /*!< GPG_MFP2 PG10 setting for ECAP2_IC1*/
#define ECAP2_IC2_PG11           SYS_GPG_MFP2_PG11MFP_ECAP2_IC2       /*!< GPG_MFP2 PG11 setting for ECAP2_IC2*/
#define ECAP2_IC2_PJ12           SYS_GPJ_MFP3_PJ12MFP_ECAP2_IC2       /*!< GPJ_MFP3 PJ12 setting for ECAP2_IC2*/
#define ECAP2_IC2_PD13           SYS_GPD_MFP3_PD13MFP_ECAP2_IC2       /*!< GPD_MFP3 PD13 setting for ECAP2_IC2*/
#define ECAP3_IC0_PA12           SYS_GPA_MFP3_PA12MFP_ECAP3_IC0       /*!< GPA_MFP3 PA12 setting for ECAP3_IC0*/
#define ECAP3_IC0_PD12           SYS_GPD_MFP3_PD12MFP_ECAP3_IC0       /*!< GPD_MFP3 PD12 setting for ECAP3_IC0*/
#define ECAP3_IC0_PE8            SYS_GPE_MFP2_PE8MFP_ECAP3_IC0        /*!< GPE_MFP2 PE8 setting for ECAP3_IC0*/
#define ECAP3_IC1_PA13           SYS_GPA_MFP3_PA13MFP_ECAP3_IC1       /*!< GPA_MFP3 PA13 setting for ECAP3_IC1*/
#define ECAP3_IC1_PE9            SYS_GPE_MFP2_PE9MFP_ECAP3_IC1        /*!< GPE_MFP2 PE9 setting for ECAP3_IC1*/
#define ECAP3_IC1_PD11           SYS_GPD_MFP2_PD11MFP_ECAP3_IC1       /*!< GPD_MFP2 PD11 setting for ECAP3_IC1*/
#define ECAP3_IC2_PE10           SYS_GPE_MFP2_PE10MFP_ECAP3_IC2       /*!< GPE_MFP2 PE10 setting for ECAP3_IC2*/
#define ECAP3_IC2_PD10           SYS_GPD_MFP2_PD10MFP_ECAP3_IC2       /*!< GPD_MFP2 PD10 setting for ECAP3_IC2*/
#define ECAP3_IC2_PA14           SYS_GPA_MFP3_PA14MFP_ECAP3_IC2       /*!< GPA_MFP3 PA14 setting for ECAP3_IC2*/
#define EMAC0_PPS_PE13           SYS_GPE_MFP3_PE13MFP_EMAC0_PPS       /*!< GPE_MFP3 PE13 setting for EMAC0_PPS*/
#define EMAC0_PPS_PB6            SYS_GPB_MFP1_PB6MFP_EMAC0_PPS        /*!< GPB_MFP1 PB6 setting for EMAC0_PPS*/
#define EMAC0_RMII_CRSDV_PA7     SYS_GPA_MFP1_PA7MFP_EMAC0_RMII_CRSDV  /*!< GPA_MFP1 PA7 setting for EMAC0_RMII_CRSDV*/
#define EMAC0_RMII_CRSDV_PB2     SYS_GPB_MFP0_PB2MFP_EMAC0_RMII_CRSDV  /*!< GPB_MFP0 PB2 setting for EMAC0_RMII_CRSDV*/
#define EMAC0_RMII_MDC_PE8       SYS_GPE_MFP2_PE8MFP_EMAC0_RMII_MDC    /*!< GPE_MFP2 PE8 setting for EMAC0_RMII_MDC*/
#define EMAC0_RMII_MDC_PB11      SYS_GPB_MFP2_PB11MFP_EMAC0_RMII_MDC   /*!< GPB_MFP2 PB11 setting for EMAC0_RMII_MDC*/
#define EMAC0_RMII_MDIO_PB10     SYS_GPB_MFP2_PB10MFP_EMAC0_RMII_MDIO  /*!< GPB_MFP2 PB10 setting for EMAC0_RMII_MDIO*/
#define EMAC0_RMII_MDIO_PE9      SYS_GPE_MFP2_PE9MFP_EMAC0_RMII_MDIO   /*!< GPE_MFP2 PE9 setting for EMAC0_RMII_MDIO*/
#define EMAC0_RMII_REFCLK_PB5    SYS_GPB_MFP1_PB5MFP_EMAC0_RMII_REFCLK /*!< GPB_MFP1 PB5 setting for EMAC0_RMII_REFCLK*/
#define EMAC0_RMII_REFCLK_PC8    SYS_GPC_MFP2_PC8MFP_EMAC0_RMII_REFCLK /*!< GPC_MFP2 PC8 setting for EMAC0_RMII_REFCLK*/
#define EMAC0_RMII_RXD0_PC7      SYS_GPC_MFP1_PC7MFP_EMAC0_RMII_RXD0   /*!< GPC_MFP1 PC7 setting for EMAC0_RMII_RXD0*/
#define EMAC0_RMII_RXD0_PB4      SYS_GPB_MFP1_PB4MFP_EMAC0_RMII_RXD0   /*!< GPB_MFP1 PB4 setting for EMAC0_RMII_RXD0*/
#define EMAC0_RMII_RXD1_PB3      SYS_GPB_MFP0_PB3MFP_EMAC0_RMII_RXD1   /*!< GPB_MFP0 PB3 setting for EMAC0_RMII_RXD1*/
#define EMAC0_RMII_RXD1_PC6      SYS_GPC_MFP1_PC6MFP_EMAC0_RMII_RXD1   /*!< GPC_MFP1 PC6 setting for EMAC0_RMII_RXD1*/
#define EMAC0_RMII_RXERR_PA6     SYS_GPA_MFP1_PA6MFP_EMAC0_RMII_RXERR  /*!< GPA_MFP1 PA6 setting for EMAC0_RMII_RXERR*/
#define EMAC0_RMII_RXERR_PB1     SYS_GPB_MFP0_PB1MFP_EMAC0_RMII_RXERR  /*!< GPB_MFP0 PB1 setting for EMAC0_RMII_RXERR*/
#define EMAC0_RMII_TXD0_PE10     SYS_GPE_MFP2_PE10MFP_EMAC0_RMII_TXD0  /*!< GPE_MFP2 PE10 setting for EMAC0_RMII_TXD0*/
#define EMAC0_RMII_TXD0_PB9      SYS_GPB_MFP2_PB9MFP_EMAC0_RMII_TXD0   /*!< GPB_MFP2 PB9 setting for EMAC0_RMII_TXD0*/
#define EMAC0_RMII_TXD1_PB8      SYS_GPB_MFP2_PB8MFP_EMAC0_RMII_TXD1   /*!< GPB_MFP2 PB8 setting for EMAC0_RMII_TXD1*/
#define EMAC0_RMII_TXD1_PE11     SYS_GPE_MFP2_PE11MFP_EMAC0_RMII_TXD1  /*!< GPE_MFP2 PE11 setting for EMAC0_RMII_TXD1*/
#define EMAC0_RMII_TXEN_PB7      SYS_GPB_MFP1_PB7MFP_EMAC0_RMII_TXEN   /*!< GPB_MFP1 PB7 setting for EMAC0_RMII_TXEN*/
#define EMAC0_RMII_TXEN_PE12     SYS_GPE_MFP3_PE12MFP_EMAC0_RMII_TXEN  /*!< GPE_MFP3 PE12 setting for EMAC0_RMII_TXEN*/
#define EPWM0_BRAKE0_PE8         SYS_GPE_MFP2_PE8MFP_EPWM0_BRAKE0     /*!< GPE_MFP2 PE8 setting for EPWM0_BRAKE0*/
#define EPWM0_BRAKE0_PB1         SYS_GPB_MFP0_PB1MFP_EPWM0_BRAKE0     /*!< GPB_MFP0 PB1 setting for EPWM0_BRAKE0*/
#define EPWM0_BRAKE1_PE9         SYS_GPE_MFP2_PE9MFP_EPWM0_BRAKE1     /*!< GPE_MFP2 PE9 setting for EPWM0_BRAKE1*/
#define EPWM0_BRAKE1_PB15        SYS_GPB_MFP3_PB15MFP_EPWM0_BRAKE1    /*!< GPB_MFP3 PB15 setting for EPWM0_BRAKE1*/
#define EPWM0_BRAKE1_PB0         SYS_GPB_MFP0_PB0MFP_EPWM0_BRAKE1     /*!< GPB_MFP0 PB0 setting for EPWM0_BRAKE1*/
#define EPWM0_CH0_PA5            SYS_GPA_MFP1_PA5MFP_EPWM0_CH0        /*!< GPA_MFP1 PA5 setting for EPWM0_CH0*/
#define EPWM0_CH0_PG8            SYS_GPG_MFP2_PG8MFP_EPWM0_CH0        /*!< GPG_MFP2 PG8 setting for EPWM0_CH0*/
#define EPWM0_CH0_PF5            SYS_GPF_MFP1_PF5MFP_EPWM0_CH0        /*!< GPF_MFP1 PF5 setting for EPWM0_CH0*/
#define EPWM0_CH0_PE7            SYS_GPE_MFP1_PE7MFP_EPWM0_CH0        /*!< GPE_MFP1 PE7 setting for EPWM0_CH0*/
#define EPWM0_CH0_PB5            SYS_GPB_MFP1_PB5MFP_EPWM0_CH0        /*!< GPB_MFP1 PB5 setting for EPWM0_CH0*/
#define EPWM0_CH0_PE8            SYS_GPE_MFP2_PE8MFP_EPWM0_CH0        /*!< GPE_MFP2 PE8 setting for EPWM0_CH0*/
#define EPWM0_CH1_PE9            SYS_GPE_MFP2_PE9MFP_EPWM0_CH1        /*!< GPE_MFP2 PE9 setting for EPWM0_CH1*/
#define EPWM0_CH1_PE6            SYS_GPE_MFP1_PE6MFP_EPWM0_CH1        /*!< GPE_MFP1 PE6 setting for EPWM0_CH1*/
#define EPWM0_CH1_PF4            SYS_GPF_MFP1_PF4MFP_EPWM0_CH1        /*!< GPF_MFP1 PF4 setting for EPWM0_CH1*/
#define EPWM0_CH1_PB4            SYS_GPB_MFP1_PB4MFP_EPWM0_CH1        /*!< GPB_MFP1 PB4 setting for EPWM0_CH1*/
#define EPWM0_CH1_PA4            SYS_GPA_MFP1_PA4MFP_EPWM0_CH1        /*!< GPA_MFP1 PA4 setting for EPWM0_CH1*/
#define EPWM0_CH1_PG7            SYS_GPG_MFP1_PG7MFP_EPWM0_CH1        /*!< GPG_MFP1 PG7 setting for EPWM0_CH1*/
#define EPWM0_CH2_PE5            SYS_GPE_MFP1_PE5MFP_EPWM0_CH2        /*!< GPE_MFP1 PE5 setting for EPWM0_CH2*/
#define EPWM0_CH2_PG6            SYS_GPG_MFP1_PG6MFP_EPWM0_CH2        /*!< GPG_MFP1 PG6 setting for EPWM0_CH2*/
#define EPWM0_CH2_PA3            SYS_GPA_MFP0_PA3MFP_EPWM0_CH2        /*!< GPA_MFP0 PA3 setting for EPWM0_CH2*/
#define EPWM0_CH2_PB3            SYS_GPB_MFP0_PB3MFP_EPWM0_CH2        /*!< GPB_MFP0 PB3 setting for EPWM0_CH2*/
#define EPWM0_CH2_PE10           SYS_GPE_MFP2_PE10MFP_EPWM0_CH2       /*!< GPE_MFP2 PE10 setting for EPWM0_CH2*/
#define EPWM0_CH3_PB2            SYS_GPB_MFP0_PB2MFP_EPWM0_CH3        /*!< GPB_MFP0 PB2 setting for EPWM0_CH3*/
#define EPWM0_CH3_PE4            SYS_GPE_MFP1_PE4MFP_EPWM0_CH3        /*!< GPE_MFP1 PE4 setting for EPWM0_CH3*/
#define EPWM0_CH3_PA2            SYS_GPA_MFP0_PA2MFP_EPWM0_CH3        /*!< GPA_MFP0 PA2 setting for EPWM0_CH3*/
#define EPWM0_CH3_PE11           SYS_GPE_MFP2_PE11MFP_EPWM0_CH3       /*!< GPE_MFP2 PE11 setting for EPWM0_CH3*/
#define EPWM0_CH3_PG5            SYS_GPG_MFP1_PG5MFP_EPWM0_CH3        /*!< GPG_MFP1 PG5 setting for EPWM0_CH3*/
#define EPWM0_CH4_PD14           SYS_GPD_MFP3_PD14MFP_EPWM0_CH4       /*!< GPD_MFP3 PD14 setting for EPWM0_CH4*/
#define EPWM0_CH4_PB1            SYS_GPB_MFP0_PB1MFP_EPWM0_CH4        /*!< GPB_MFP0 PB1 setting for EPWM0_CH4*/
#define EPWM0_CH4_PE12           SYS_GPE_MFP3_PE12MFP_EPWM0_CH4       /*!< GPE_MFP3 PE12 setting for EPWM0_CH4*/
#define EPWM0_CH4_PA1            SYS_GPA_MFP0_PA1MFP_EPWM0_CH4        /*!< GPA_MFP0 PA1 setting for EPWM0_CH4*/
#define EPWM0_CH4_PE3            SYS_GPE_MFP0_PE3MFP_EPWM0_CH4        /*!< GPE_MFP0 PE3 setting for EPWM0_CH4*/
#define EPWM0_CH5_PE13           SYS_GPE_MFP3_PE13MFP_EPWM0_CH5       /*!< GPE_MFP3 PE13 setting for EPWM0_CH5*/
#define EPWM0_CH5_PA0            SYS_GPA_MFP0_PA0MFP_EPWM0_CH5        /*!< GPA_MFP0 PA0 setting for EPWM0_CH5*/
#define EPWM0_CH5_PB0            SYS_GPB_MFP0_PB0MFP_EPWM0_CH5        /*!< GPB_MFP0 PB0 setting for EPWM0_CH5*/
#define EPWM0_CH5_PE2            SYS_GPE_MFP0_PE2MFP_EPWM0_CH5        /*!< GPE_MFP0 PE2 setting for EPWM0_CH5*/
#define EPWM0_CH5_PH11           SYS_GPH_MFP2_PH11MFP_EPWM0_CH5       /*!< GPH_MFP2 PH11 setting for EPWM0_CH5*/
#define EPWM0_SYNC_IN_PA15       SYS_GPA_MFP3_PA15MFP_EPWM0_SYNC_IN   /*!< GPA_MFP3 PA15 setting for EPWM0_SYNC_IN*/
#define EPWM0_SYNC_IN_PC14       SYS_GPC_MFP3_PC14MFP_EPWM0_SYNC_IN   /*!< GPC_MFP3 PC14 setting for EPWM0_SYNC_IN*/
#define EPWM0_SYNC_OUT_PA11      SYS_GPA_MFP2_PA11MFP_EPWM0_SYNC_OUT  /*!< GPA_MFP2 PA11 setting for EPWM0_SYNC_OUT*/
#define EPWM0_SYNC_OUT_PF5       SYS_GPF_MFP1_PF5MFP_EPWM0_SYNC_OUT   /*!< GPF_MFP1 PF5 setting for EPWM0_SYNC_OUT*/
#define EPWM1_BRAKE0_PB7         SYS_GPB_MFP1_PB7MFP_EPWM1_BRAKE0     /*!< GPB_MFP1 PB7 setting for EPWM1_BRAKE0*/
#define EPWM1_BRAKE0_PE10        SYS_GPE_MFP2_PE10MFP_EPWM1_BRAKE0    /*!< GPE_MFP2 PE10 setting for EPWM1_BRAKE0*/
#define EPWM1_BRAKE1_PA3         SYS_GPA_MFP0_PA3MFP_EPWM1_BRAKE1     /*!< GPA_MFP0 PA3 setting for EPWM1_BRAKE1*/
#define EPWM1_BRAKE1_PE11        SYS_GPE_MFP2_PE11MFP_EPWM1_BRAKE1    /*!< GPE_MFP2 PE11 setting for EPWM1_BRAKE1*/
#define EPWM1_BRAKE1_PB6         SYS_GPB_MFP1_PB6MFP_EPWM1_BRAKE1     /*!< GPB_MFP1 PB6 setting for EPWM1_BRAKE1*/
#define EPWM1_CH0_PC5            SYS_GPC_MFP1_PC5MFP_EPWM1_CH0        /*!< GPC_MFP1 PC5 setting for EPWM1_CH0*/
#define EPWM1_CH0_PI12           SYS_GPI_MFP3_PI12MFP_EPWM1_CH0       /*!< GPI_MFP3 PI12 setting for EPWM1_CH0*/
#define EPWM1_CH0_PB15           SYS_GPB_MFP3_PB15MFP_EPWM1_CH0       /*!< GPB_MFP3 PB15 setting for EPWM1_CH0*/
#define EPWM1_CH0_PE13           SYS_GPE_MFP3_PE13MFP_EPWM1_CH0       /*!< GPE_MFP3 PE13 setting for EPWM1_CH0*/
#define EPWM1_CH0_PC12           SYS_GPC_MFP3_PC12MFP_EPWM1_CH0       /*!< GPC_MFP3 PC12 setting for EPWM1_CH0*/
#define EPWM1_CH1_PB14           SYS_GPB_MFP3_PB14MFP_EPWM1_CH1       /*!< GPB_MFP3 PB14 setting for EPWM1_CH1*/
#define EPWM1_CH1_PC8            SYS_GPC_MFP2_PC8MFP_EPWM1_CH1        /*!< GPC_MFP2 PC8 setting for EPWM1_CH1*/
#define EPWM1_CH1_PI13           SYS_GPI_MFP3_PI13MFP_EPWM1_CH1       /*!< GPI_MFP3 PI13 setting for EPWM1_CH1*/
#define EPWM1_CH1_PC4            SYS_GPC_MFP1_PC4MFP_EPWM1_CH1        /*!< GPC_MFP1 PC4 setting for EPWM1_CH1*/
#define EPWM1_CH1_PC11           SYS_GPC_MFP2_PC11MFP_EPWM1_CH1       /*!< GPC_MFP2 PC11 setting for EPWM1_CH1*/
#define EPWM1_CH2_PC10           SYS_GPC_MFP2_PC10MFP_EPWM1_CH2       /*!< GPC_MFP2 PC10 setting for EPWM1_CH2*/
#define EPWM1_CH2_PB13           SYS_GPB_MFP3_PB13MFP_EPWM1_CH2       /*!< GPB_MFP3 PB13 setting for EPWM1_CH2*/
#define EPWM1_CH2_PC7            SYS_GPC_MFP1_PC7MFP_EPWM1_CH2        /*!< GPC_MFP1 PC7 setting for EPWM1_CH2*/
#define EPWM1_CH2_PI14           SYS_GPI_MFP3_PI14MFP_EPWM1_CH2       /*!< GPI_MFP3 PI14 setting for EPWM1_CH2*/
#define EPWM1_CH2_PC3            SYS_GPC_MFP0_PC3MFP_EPWM1_CH2        /*!< GPC_MFP0 PC3 setting for EPWM1_CH2*/
#define EPWM1_CH3_PC9            SYS_GPC_MFP2_PC9MFP_EPWM1_CH3        /*!< GPC_MFP2 PC9 setting for EPWM1_CH3*/
#define EPWM1_CH3_PC2            SYS_GPC_MFP0_PC2MFP_EPWM1_CH3        /*!< GPC_MFP0 PC2 setting for EPWM1_CH3*/
#define EPWM1_CH3_PC6            SYS_GPC_MFP1_PC6MFP_EPWM1_CH3        /*!< GPC_MFP1 PC6 setting for EPWM1_CH3*/
#define EPWM1_CH3_PB12           SYS_GPB_MFP3_PB12MFP_EPWM1_CH3       /*!< GPB_MFP3 PB12 setting for EPWM1_CH3*/
#define EPWM1_CH3_PI15           SYS_GPI_MFP3_PI15MFP_EPWM1_CH3       /*!< GPI_MFP3 PI15 setting for EPWM1_CH3*/
#define EPWM1_CH4_PB7            SYS_GPB_MFP1_PB7MFP_EPWM1_CH4        /*!< GPB_MFP1 PB7 setting for EPWM1_CH4*/
#define EPWM1_CH4_PB1            SYS_GPB_MFP0_PB1MFP_EPWM1_CH4        /*!< GPB_MFP0 PB1 setting for EPWM1_CH4*/
#define EPWM1_CH4_PJ0            SYS_GPJ_MFP0_PJ0MFP_EPWM1_CH4        /*!< GPJ_MFP0 PJ0 setting for EPWM1_CH4*/
#define EPWM1_CH4_PF0            SYS_GPF_MFP0_PF0MFP_EPWM1_CH4        /*!< GPF_MFP0 PF0 setting for EPWM1_CH4*/
#define EPWM1_CH4_PA7            SYS_GPA_MFP1_PA7MFP_EPWM1_CH4        /*!< GPA_MFP1 PA7 setting for EPWM1_CH4*/
#define EPWM1_CH4_PC1            SYS_GPC_MFP0_PC1MFP_EPWM1_CH4        /*!< GPC_MFP0 PC1 setting for EPWM1_CH4*/
#define EPWM1_CH5_PF1            SYS_GPF_MFP0_PF1MFP_EPWM1_CH5        /*!< GPF_MFP0 PF1 setting for EPWM1_CH5*/
#define EPWM1_CH5_PB0            SYS_GPB_MFP0_PB0MFP_EPWM1_CH5        /*!< GPB_MFP0 PB0 setting for EPWM1_CH5*/
#define EPWM1_CH5_PA6            SYS_GPA_MFP1_PA6MFP_EPWM1_CH5        /*!< GPA_MFP1 PA6 setting for EPWM1_CH5*/
#define EPWM1_CH5_PJ1            SYS_GPJ_MFP0_PJ1MFP_EPWM1_CH5        /*!< GPJ_MFP0 PJ1 setting for EPWM1_CH5*/
#define EPWM1_CH5_PC0            SYS_GPC_MFP0_PC0MFP_EPWM1_CH5        /*!< GPC_MFP0 PC0 setting for EPWM1_CH5*/
#define EPWM1_CH5_PB6            SYS_GPB_MFP1_PB6MFP_EPWM1_CH5        /*!< GPB_MFP1 PB6 setting for EPWM1_CH5*/
#define ETMC_TRACE_CLK_PC14      SYS_GPC_MFP3_PC14MFP_ETMC_TRACE_CLK   /*!< GPC_MFP3 PC14 setting for ETMC_TRACE_CLK*/
#define ETMC_TRACE_DATA0_PB15    SYS_GPB_MFP3_PB15MFP_ETMC_TRACE_DATA0 /*!< GPB_MFP3 PB15 setting for ETMC_TRACE_DATA0*/
#define ETMC_TRACE_DATA1_PB14    SYS_GPB_MFP3_PB14MFP_ETMC_TRACE_DATA1 /*!< GPB_MFP3 PB14 setting for ETMC_TRACE_DATA1*/
#define ETMC_TRACE_DATA2_PB13    SYS_GPB_MFP3_PB13MFP_ETMC_TRACE_DATA2 /*!< GPB_MFP3 PB13 setting for ETMC_TRACE_DATA2*/
#define ETMC_TRACE_DATA3_PB12    SYS_GPB_MFP3_PB12MFP_ETMC_TRACE_DATA3 /*!< GPB_MFP3 PB12 setting for ETMC_TRACE_DATA3*/
#define HBI_CK_PC4               SYS_GPC_MFP1_PC4MFP_HBI_CK           /*!< GPC_MFP1 PC4 setting for HBI_CK*/
#define HBI_CK_PH13              SYS_GPH_MFP3_PH13MFP_HBI_CK          /*!< GPH_MFP3 PH13 setting for HBI_CK*/
#define HBI_D0_PJ6               SYS_GPJ_MFP1_PJ6MFP_HBI_D0           /*!< GPJ_MFP1 PJ6 setting for HBI_D0*/
#define HBI_D0_PG11              SYS_GPG_MFP2_PG11MFP_HBI_D0          /*!< GPG_MFP2 PG11 setting for HBI_D0*/
#define HBI_D1_PG12              SYS_GPG_MFP3_PG12MFP_HBI_D1          /*!< GPG_MFP3 PG12 setting for HBI_D1*/
#define HBI_D1_PJ5               SYS_GPJ_MFP1_PJ5MFP_HBI_D1           /*!< GPJ_MFP1 PJ5 setting for HBI_D1*/
#define HBI_D2_PJ4               SYS_GPJ_MFP1_PJ4MFP_HBI_D2           /*!< GPJ_MFP1 PJ4 setting for HBI_D2*/
#define HBI_D2_PC0               SYS_GPC_MFP0_PC0MFP_HBI_D2           /*!< GPC_MFP0 PC0 setting for HBI_D2*/
#define HBI_D3_PG10              SYS_GPG_MFP2_PG10MFP_HBI_D3          /*!< GPG_MFP2 PG10 setting for HBI_D3*/
#define HBI_D3_PJ3               SYS_GPJ_MFP0_PJ3MFP_HBI_D3           /*!< GPJ_MFP0 PJ3 setting for HBI_D3*/
#define HBI_D4_PG9               SYS_GPG_MFP2_PG9MFP_HBI_D4           /*!< GPG_MFP2 PG9 setting for HBI_D4*/
#define HBI_D4_PH15              SYS_GPH_MFP3_PH15MFP_HBI_D4          /*!< GPH_MFP3 PH15 setting for HBI_D4*/
#define HBI_D5_PG13              SYS_GPG_MFP3_PG13MFP_HBI_D5          /*!< GPG_MFP3 PG13 setting for HBI_D5*/
#define HBI_D5_PD7               SYS_GPD_MFP1_PD7MFP_HBI_D5           /*!< GPD_MFP1 PD7 setting for HBI_D5*/
#define HBI_D6_PG14              SYS_GPG_MFP3_PG14MFP_HBI_D6          /*!< GPG_MFP3 PG14 setting for HBI_D6*/
#define HBI_D6_PD6               SYS_GPD_MFP1_PD6MFP_HBI_D6           /*!< GPD_MFP1 PD6 setting for HBI_D6*/
#define HBI_D7_PG15              SYS_GPG_MFP3_PG15MFP_HBI_D7          /*!< GPG_MFP3 PG15 setting for HBI_D7*/
#define HBI_D7_PD5               SYS_GPD_MFP1_PD5MFP_HBI_D7           /*!< GPD_MFP1 PD5 setting for HBI_D7*/
#define HBI_RWDS_PC1             SYS_GPC_MFP0_PC1MFP_HBI_RWDS         /*!< GPC_MFP0 PC1 setting for HBI_RWDS*/
#define HBI_RWDS_PH14            SYS_GPH_MFP3_PH14MFP_HBI_RWDS        /*!< GPH_MFP3 PH14 setting for HBI_RWDS*/
#define HBI_nCK_PH12             SYS_GPH_MFP3_PH12MFP_HBI_nCK         /*!< GPH_MFP3 PH12 setting for HBI_nCK*/
#define HBI_nCK_PC5              SYS_GPC_MFP1_PC5MFP_HBI_nCK          /*!< GPC_MFP1 PC5 setting for HBI_nCK*/
#define HBI_nCS_PC3              SYS_GPC_MFP0_PC3MFP_HBI_nCS          /*!< GPC_MFP0 PC3 setting for HBI_nCS*/
#define HBI_nCS_PJ7              SYS_GPJ_MFP1_PJ7MFP_HBI_nCS          /*!< GPJ_MFP1 PJ7 setting for HBI_nCS*/
#define HBI_nRESET_PJ2           SYS_GPJ_MFP0_PJ2MFP_HBI_nRESET       /*!< GPJ_MFP0 PJ2 setting for HBI_nRESET*/
#define HBI_nRESET_PC2           SYS_GPC_MFP0_PC2MFP_HBI_nRESET       /*!< GPC_MFP0 PC2 setting for HBI_nRESET*/
#define HSUSB_VBUS_EN_PB10       SYS_GPB_MFP2_PB10MFP_HSUSB_VBUS_EN   /*!< GPB_MFP2 PB10 setting for HSUSB_VBUS_EN*/
#define HSUSB_VBUS_EN_PB15       SYS_GPB_MFP3_PB15MFP_HSUSB_VBUS_EN   /*!< GPB_MFP3 PB15 setting for HSUSB_VBUS_EN*/
#define HSUSB_VBUS_EN_PJ13       SYS_GPJ_MFP3_PJ13MFP_HSUSB_VBUS_EN   /*!< GPJ_MFP3 PJ13 setting for HSUSB_VBUS_EN*/
#define HSUSB_VBUS_ST_PB11       SYS_GPB_MFP2_PB11MFP_HSUSB_VBUS_ST   /*!< GPB_MFP2 PB11 setting for HSUSB_VBUS_ST*/
#define HSUSB_VBUS_ST_PC14       SYS_GPC_MFP3_PC14MFP_HSUSB_VBUS_ST   /*!< GPC_MFP3 PC14 setting for HSUSB_VBUS_ST*/
#define HSUSB_VBUS_ST_PJ12       SYS_GPJ_MFP3_PJ12MFP_HSUSB_VBUS_ST   /*!< GPJ_MFP3 PJ12 setting for HSUSB_VBUS_ST*/
#define I2C0_SCL_PB9             SYS_GPB_MFP2_PB9MFP_I2C0_SCL         /*!< GPB_MFP2 PB9 setting for I2C0_SCL*/
#define I2C0_SCL_PF0             SYS_GPF_MFP0_PF0MFP_I2C0_SCL         /*!< GPF_MFP0 PF0 setting for I2C0_SCL*/
#define I2C0_SCL_PD7             SYS_GPD_MFP1_PD7MFP_I2C0_SCL         /*!< GPD_MFP1 PD7 setting for I2C0_SCL*/
#define I2C0_SCL_PA5             SYS_GPA_MFP1_PA5MFP_I2C0_SCL         /*!< GPA_MFP1 PA5 setting for I2C0_SCL*/
#define I2C0_SCL_PH2             SYS_GPH_MFP0_PH2MFP_I2C0_SCL         /*!< GPH_MFP0 PH2 setting for I2C0_SCL*/
#define I2C0_SCL_PG0             SYS_GPG_MFP0_PG0MFP_I2C0_SCL         /*!< GPG_MFP0 PG0 setting for I2C0_SCL*/
#define I2C0_SCL_PC12            SYS_GPC_MFP3_PC12MFP_I2C0_SCL        /*!< GPC_MFP3 PC12 setting for I2C0_SCL*/
#define I2C0_SCL_PC1             SYS_GPC_MFP0_PC1MFP_I2C0_SCL         /*!< GPC_MFP0 PC1 setting for I2C0_SCL*/
#define I2C0_SCL_PB5             SYS_GPB_MFP1_PB5MFP_I2C0_SCL         /*!< GPB_MFP1 PB5 setting for I2C0_SCL*/
#define I2C0_SCL_PE13            SYS_GPE_MFP3_PE13MFP_I2C0_SCL        /*!< GPE_MFP3 PE13 setting for I2C0_SCL*/
#define I2C0_SCL_PF3             SYS_GPF_MFP0_PF3MFP_I2C0_SCL         /*!< GPF_MFP0 PF3 setting for I2C0_SCL*/
#define I2C0_SCL_PI10            SYS_GPI_MFP2_PI10MFP_I2C0_SCL        /*!< GPI_MFP2 PI10 setting for I2C0_SCL*/
#define I2C0_SCL_PA14            SYS_GPA_MFP3_PA14MFP_I2C0_SCL        /*!< GPA_MFP3 PA14 setting for I2C0_SCL*/
#define I2C0_SDA_PI11            SYS_GPI_MFP2_PI11MFP_I2C0_SDA        /*!< GPI_MFP2 PI11 setting for I2C0_SDA*/
#define I2C0_SDA_PF2             SYS_GPF_MFP0_PF2MFP_I2C0_SDA         /*!< GPF_MFP0 PF2 setting for I2C0_SDA*/
#define I2C0_SDA_PB4             SYS_GPB_MFP1_PB4MFP_I2C0_SDA         /*!< GPB_MFP1 PB4 setting for I2C0_SDA*/
#define I2C0_SDA_PF1             SYS_GPF_MFP0_PF1MFP_I2C0_SDA         /*!< GPF_MFP0 PF1 setting for I2C0_SDA*/
#define I2C0_SDA_PH3             SYS_GPH_MFP0_PH3MFP_I2C0_SDA         /*!< GPH_MFP0 PH3 setting for I2C0_SDA*/
#define I2C0_SDA_PG1             SYS_GPG_MFP0_PG1MFP_I2C0_SDA         /*!< GPG_MFP0 PG1 setting for I2C0_SDA*/
#define I2C0_SDA_PA4             SYS_GPA_MFP1_PA4MFP_I2C0_SDA         /*!< GPA_MFP1 PA4 setting for I2C0_SDA*/
#define I2C0_SDA_PC11            SYS_GPC_MFP2_PC11MFP_I2C0_SDA        /*!< GPC_MFP2 PC11 setting for I2C0_SDA*/
#define I2C0_SDA_PD6             SYS_GPD_MFP1_PD6MFP_I2C0_SDA         /*!< GPD_MFP1 PD6 setting for I2C0_SDA*/
#define I2C0_SDA_PC0             SYS_GPC_MFP0_PC0MFP_I2C0_SDA         /*!< GPC_MFP0 PC0 setting for I2C0_SDA*/
#define I2C0_SDA_PC8             SYS_GPC_MFP2_PC8MFP_I2C0_SDA         /*!< GPC_MFP2 PC8 setting for I2C0_SDA*/
#define I2C0_SDA_PB8             SYS_GPB_MFP2_PB8MFP_I2C0_SDA         /*!< GPB_MFP2 PB8 setting for I2C0_SDA*/
#define I2C0_SDA_PA15            SYS_GPA_MFP3_PA15MFP_I2C0_SDA        /*!< GPA_MFP3 PA15 setting for I2C0_SDA*/
#define I2C0_SMBAL_PC3           SYS_GPC_MFP0_PC3MFP_I2C0_SMBAL       /*!< GPC_MFP0 PC3 setting for I2C0_SMBAL*/
#define I2C0_SMBAL_PG2           SYS_GPG_MFP0_PG2MFP_I2C0_SMBAL       /*!< GPG_MFP0 PG2 setting for I2C0_SMBAL*/
#define I2C0_SMBAL_PA3           SYS_GPA_MFP0_PA3MFP_I2C0_SMBAL       /*!< GPA_MFP0 PA3 setting for I2C0_SMBAL*/
#define I2C0_SMBAL_PI8           SYS_GPI_MFP2_PI8MFP_I2C0_SMBAL       /*!< GPI_MFP2 PI8 setting for I2C0_SMBAL*/
#define I2C0_SMBSUS_PI9          SYS_GPI_MFP2_PI9MFP_I2C0_SMBSUS      /*!< GPI_MFP2 PI9 setting for I2C0_SMBSUS*/
#define I2C0_SMBSUS_PA2          SYS_GPA_MFP0_PA2MFP_I2C0_SMBSUS      /*!< GPA_MFP0 PA2 setting for I2C0_SMBSUS*/
#define I2C0_SMBSUS_PG3          SYS_GPG_MFP0_PG3MFP_I2C0_SMBSUS      /*!< GPG_MFP0 PG3 setting for I2C0_SMBSUS*/
#define I2C0_SMBSUS_PC2          SYS_GPC_MFP0_PC2MFP_I2C0_SMBSUS      /*!< GPC_MFP0 PC2 setting for I2C0_SMBSUS*/
#define I2C1_SCL_PF0             SYS_GPF_MFP0_PF0MFP_I2C1_SCL         /*!< GPF_MFP0 PF0 setting for I2C1_SCL*/
#define I2C1_SCL_PD5             SYS_GPD_MFP1_PD5MFP_I2C1_SCL         /*!< GPD_MFP1 PD5 setting for I2C1_SCL*/
#define I2C1_SCL_PB1             SYS_GPB_MFP0_PB1MFP_I2C1_SCL         /*!< GPB_MFP0 PB1 setting for I2C1_SCL*/
#define I2C1_SCL_PI6             SYS_GPI_MFP1_PI6MFP_I2C1_SCL         /*!< GPI_MFP1 PI6 setting for I2C1_SCL*/
#define I2C1_SCL_PB3             SYS_GPB_MFP0_PB3MFP_I2C1_SCL         /*!< GPB_MFP0 PB3 setting for I2C1_SCL*/
#define I2C1_SCL_PA12            SYS_GPA_MFP3_PA12MFP_I2C1_SCL        /*!< GPA_MFP3 PA12 setting for I2C1_SCL*/
#define I2C1_SCL_PE1             SYS_GPE_MFP0_PE1MFP_I2C1_SCL         /*!< GPE_MFP0 PE1 setting for I2C1_SCL*/
#define I2C1_SCL_PB11            SYS_GPB_MFP2_PB11MFP_I2C1_SCL        /*!< GPB_MFP2 PB11 setting for I2C1_SCL*/
#define I2C1_SCL_PG2             SYS_GPG_MFP0_PG2MFP_I2C1_SCL         /*!< GPG_MFP0 PG2 setting for I2C1_SCL*/
#define I2C1_SCL_PA7             SYS_GPA_MFP1_PA7MFP_I2C1_SCL         /*!< GPA_MFP1 PA7 setting for I2C1_SCL*/
#define I2C1_SCL_PC5             SYS_GPC_MFP1_PC5MFP_I2C1_SCL         /*!< GPC_MFP1 PC5 setting for I2C1_SCL*/
#define I2C1_SCL_PA3             SYS_GPA_MFP0_PA3MFP_I2C1_SCL         /*!< GPA_MFP0 PA3 setting for I2C1_SCL*/
#define I2C1_SDA_PB0             SYS_GPB_MFP0_PB0MFP_I2C1_SDA         /*!< GPB_MFP0 PB0 setting for I2C1_SDA*/
#define I2C1_SDA_PA2             SYS_GPA_MFP0_PA2MFP_I2C1_SDA         /*!< GPA_MFP0 PA2 setting for I2C1_SDA*/
#define I2C1_SDA_PB2             SYS_GPB_MFP0_PB2MFP_I2C1_SDA         /*!< GPB_MFP0 PB2 setting for I2C1_SDA*/
#define I2C1_SDA_PC4             SYS_GPC_MFP1_PC4MFP_I2C1_SDA         /*!< GPC_MFP1 PC4 setting for I2C1_SDA*/
#define I2C1_SDA_PI7             SYS_GPI_MFP1_PI7MFP_I2C1_SDA         /*!< GPI_MFP1 PI7 setting for I2C1_SDA*/
#define I2C1_SDA_PF1             SYS_GPF_MFP0_PF1MFP_I2C1_SDA         /*!< GPF_MFP0 PF1 setting for I2C1_SDA*/
#define I2C1_SDA_PD4             SYS_GPD_MFP1_PD4MFP_I2C1_SDA         /*!< GPD_MFP1 PD4 setting for I2C1_SDA*/
#define I2C1_SDA_PA13            SYS_GPA_MFP3_PA13MFP_I2C1_SDA        /*!< GPA_MFP3 PA13 setting for I2C1_SDA*/
#define I2C1_SDA_PB10            SYS_GPB_MFP2_PB10MFP_I2C1_SDA        /*!< GPB_MFP2 PB10 setting for I2C1_SDA*/
#define I2C1_SDA_PA6             SYS_GPA_MFP1_PA6MFP_I2C1_SDA         /*!< GPA_MFP1 PA6 setting for I2C1_SDA*/
#define I2C1_SDA_PG3             SYS_GPG_MFP0_PG3MFP_I2C1_SDA         /*!< GPG_MFP0 PG3 setting for I2C1_SDA*/
#define I2C1_SDA_PE0             SYS_GPE_MFP0_PE0MFP_I2C1_SDA         /*!< GPE_MFP0 PE0 setting for I2C1_SDA*/
#define I2C1_SMBAL_PG0           SYS_GPG_MFP0_PG0MFP_I2C1_SMBAL       /*!< GPG_MFP0 PG0 setting for I2C1_SMBAL*/
#define I2C1_SMBAL_PC7           SYS_GPC_MFP1_PC7MFP_I2C1_SMBAL       /*!< GPC_MFP1 PC7 setting for I2C1_SMBAL*/
#define I2C1_SMBAL_PB9           SYS_GPB_MFP2_PB9MFP_I2C1_SMBAL       /*!< GPB_MFP2 PB9 setting for I2C1_SMBAL*/
#define I2C1_SMBAL_PH8           SYS_GPH_MFP2_PH8MFP_I2C1_SMBAL       /*!< GPH_MFP2 PH8 setting for I2C1_SMBAL*/
#define I2C1_SMBSUS_PH9          SYS_GPH_MFP2_PH9MFP_I2C1_SMBSUS      /*!< GPH_MFP2 PH9 setting for I2C1_SMBSUS*/
#define I2C1_SMBSUS_PC6          SYS_GPC_MFP1_PC6MFP_I2C1_SMBSUS      /*!< GPC_MFP1 PC6 setting for I2C1_SMBSUS*/
#define I2C1_SMBSUS_PG1          SYS_GPG_MFP0_PG1MFP_I2C1_SMBSUS      /*!< GPG_MFP0 PG1 setting for I2C1_SMBSUS*/
#define I2C1_SMBSUS_PB8          SYS_GPB_MFP2_PB8MFP_I2C1_SMBSUS      /*!< GPB_MFP2 PB8 setting for I2C1_SMBSUS*/
#define I2C2_SCL_PA1             SYS_GPA_MFP0_PA1MFP_I2C2_SCL         /*!< GPA_MFP0 PA1 setting for I2C2_SCL*/
#define I2C2_SCL_PH8             SYS_GPH_MFP2_PH8MFP_I2C2_SCL         /*!< GPH_MFP2 PH8 setting for I2C2_SCL*/
#define I2C2_SCL_PB13            SYS_GPB_MFP3_PB13MFP_I2C2_SCL        /*!< GPB_MFP3 PB13 setting for I2C2_SCL*/
#define I2C2_SCL_PA11            SYS_GPA_MFP2_PA11MFP_I2C2_SCL        /*!< GPA_MFP2 PA11 setting for I2C2_SCL*/
#define I2C2_SCL_PA14            SYS_GPA_MFP3_PA14MFP_I2C2_SCL        /*!< GPA_MFP3 PA14 setting for I2C2_SCL*/
#define I2C2_SCL_PD1             SYS_GPD_MFP0_PD1MFP_I2C2_SCL         /*!< GPD_MFP0 PD1 setting for I2C2_SCL*/
#define I2C2_SCL_PD9             SYS_GPD_MFP2_PD9MFP_I2C2_SCL         /*!< GPD_MFP2 PD9 setting for I2C2_SCL*/
#define I2C2_SDA_PB12            SYS_GPB_MFP3_PB12MFP_I2C2_SDA        /*!< GPB_MFP3 PB12 setting for I2C2_SDA*/
#define I2C2_SDA_PD8             SYS_GPD_MFP2_PD8MFP_I2C2_SDA         /*!< GPD_MFP2 PD8 setting for I2C2_SDA*/
#define I2C2_SDA_PA0             SYS_GPA_MFP0_PA0MFP_I2C2_SDA         /*!< GPA_MFP0 PA0 setting for I2C2_SDA*/
#define I2C2_SDA_PH9             SYS_GPH_MFP2_PH9MFP_I2C2_SDA         /*!< GPH_MFP2 PH9 setting for I2C2_SDA*/
#define I2C2_SDA_PA15            SYS_GPA_MFP3_PA15MFP_I2C2_SDA        /*!< GPA_MFP3 PA15 setting for I2C2_SDA*/
#define I2C2_SDA_PA10            SYS_GPA_MFP2_PA10MFP_I2C2_SDA        /*!< GPA_MFP2 PA10 setting for I2C2_SDA*/
#define I2C2_SDA_PD0             SYS_GPD_MFP0_PD0MFP_I2C2_SDA         /*!< GPD_MFP0 PD0 setting for I2C2_SDA*/
#define I2C2_SMBAL_PB15          SYS_GPB_MFP3_PB15MFP_I2C2_SMBAL      /*!< GPB_MFP3 PB15 setting for I2C2_SMBAL*/
#define I2C2_SMBSUS_PB14         SYS_GPB_MFP3_PB14MFP_I2C2_SMBSUS     /*!< GPB_MFP3 PB14 setting for I2C2_SMBSUS*/
#define I2C3_SCL_PG7             SYS_GPG_MFP1_PG7MFP_I2C3_SCL         /*!< GPG_MFP1 PG7 setting for I2C3_SCL*/
#define I2C3_SCL_PG0             SYS_GPG_MFP0_PG0MFP_I2C3_SCL         /*!< GPG_MFP0 PG0 setting for I2C3_SCL*/
#define I2C3_SCL_PC3             SYS_GPC_MFP0_PC3MFP_I2C3_SCL         /*!< GPC_MFP0 PC3 setting for I2C3_SCL*/
#define I2C3_SCL_PI14            SYS_GPI_MFP3_PI14MFP_I2C3_SCL        /*!< GPI_MFP3 PI14 setting for I2C3_SCL*/
#define I2C3_SDA_PG8             SYS_GPG_MFP2_PG8MFP_I2C3_SDA         /*!< GPG_MFP2 PG8 setting for I2C3_SDA*/
#define I2C3_SDA_PI15            SYS_GPI_MFP3_PI15MFP_I2C3_SDA        /*!< GPI_MFP3 PI15 setting for I2C3_SDA*/
#define I2C3_SDA_PC2             SYS_GPC_MFP0_PC2MFP_I2C3_SDA         /*!< GPC_MFP0 PC2 setting for I2C3_SDA*/
#define I2C3_SDA_PG1             SYS_GPG_MFP0_PG1MFP_I2C3_SDA         /*!< GPG_MFP0 PG1 setting for I2C3_SDA*/
#define I2C3_SMBAL_PG2           SYS_GPG_MFP0_PG2MFP_I2C3_SMBAL       /*!< GPG_MFP0 PG2 setting for I2C3_SMBAL*/
#define I2C3_SMBAL_PI12          SYS_GPI_MFP3_PI12MFP_I2C3_SMBAL      /*!< GPI_MFP3 PI12 setting for I2C3_SMBAL*/
#define I2C3_SMBAL_PC5           SYS_GPC_MFP1_PC5MFP_I2C3_SMBAL       /*!< GPC_MFP1 PC5 setting for I2C3_SMBAL*/
#define I2C3_SMBAL_PG5           SYS_GPG_MFP1_PG5MFP_I2C3_SMBAL       /*!< GPG_MFP1 PG5 setting for I2C3_SMBAL*/
#define I2C3_SMBSUS_PG6          SYS_GPG_MFP1_PG6MFP_I2C3_SMBSUS      /*!< GPG_MFP1 PG6 setting for I2C3_SMBSUS*/
#define I2C3_SMBSUS_PC4          SYS_GPC_MFP1_PC4MFP_I2C3_SMBSUS      /*!< GPC_MFP1 PC4 setting for I2C3_SMBSUS*/
#define I2C3_SMBSUS_PG3          SYS_GPG_MFP0_PG3MFP_I2C3_SMBSUS      /*!< GPG_MFP0 PG3 setting for I2C3_SMBSUS*/
#define I2C3_SMBSUS_PI13         SYS_GPI_MFP3_PI13MFP_I2C3_SMBSUS     /*!< GPI_MFP3 PI13 setting for I2C3_SMBSUS*/
#define I2C4_SCL_PJ10            SYS_GPJ_MFP2_PJ10MFP_I2C4_SCL        /*!< GPJ_MFP2 PJ10 setting for I2C4_SCL*/
#define I2C4_SCL_PG9             SYS_GPG_MFP2_PG9MFP_I2C4_SCL         /*!< GPG_MFP2 PG9 setting for I2C4_SCL*/
#define I2C4_SCL_PC12            SYS_GPC_MFP3_PC12MFP_I2C4_SCL        /*!< GPC_MFP3 PC12 setting for I2C4_SCL*/
#define I2C4_SCL_PF5             SYS_GPF_MFP1_PF5MFP_I2C4_SCL         /*!< GPF_MFP1 PF5 setting for I2C4_SCL*/
#define I2C4_SDA_PJ11            SYS_GPJ_MFP2_PJ11MFP_I2C4_SDA        /*!< GPJ_MFP2 PJ11 setting for I2C4_SDA*/
#define I2C4_SDA_PG10            SYS_GPG_MFP2_PG10MFP_I2C4_SDA        /*!< GPG_MFP2 PG10 setting for I2C4_SDA*/
#define I2C4_SDA_PC11            SYS_GPC_MFP2_PC11MFP_I2C4_SDA        /*!< GPC_MFP2 PC11 setting for I2C4_SDA*/
#define I2C4_SDA_PF4             SYS_GPF_MFP1_PF4MFP_I2C4_SDA         /*!< GPF_MFP1 PF4 setting for I2C4_SDA*/
#define I2C4_SMBAL_PJ12          SYS_GPJ_MFP3_PJ12MFP_I2C4_SMBAL      /*!< GPJ_MFP3 PJ12 setting for I2C4_SMBAL*/
#define I2C4_SMBAL_PG11          SYS_GPG_MFP2_PG11MFP_I2C4_SMBAL      /*!< GPG_MFP2 PG11 setting for I2C4_SMBAL*/
#define I2C4_SMBAL_PF3           SYS_GPF_MFP0_PF3MFP_I2C4_SMBAL       /*!< GPF_MFP0 PF3 setting for I2C4_SMBAL*/
#define I2C4_SMBAL_PC10          SYS_GPC_MFP2_PC10MFP_I2C4_SMBAL      /*!< GPC_MFP2 PC10 setting for I2C4_SMBAL*/
#define I2C4_SMBSUS_PJ13         SYS_GPJ_MFP3_PJ13MFP_I2C4_SMBSUS     /*!< GPJ_MFP3 PJ13 setting for I2C4_SMBSUS*/
#define I2C4_SMBSUS_PG12         SYS_GPG_MFP3_PG12MFP_I2C4_SMBSUS     /*!< GPG_MFP3 PG12 setting for I2C4_SMBSUS*/
#define I2C4_SMBSUS_PC9          SYS_GPC_MFP2_PC9MFP_I2C4_SMBSUS      /*!< GPC_MFP2 PC9 setting for I2C4_SMBSUS*/
#define I2C4_SMBSUS_PF2          SYS_GPF_MFP0_PF2MFP_I2C4_SMBSUS      /*!< GPF_MFP0 PF2 setting for I2C4_SMBSUS*/
#define I2S0_BCLK_PE8            SYS_GPE_MFP2_PE8MFP_I2S0_BCLK        /*!< GPE_MFP2 PE8 setting for I2S0_BCLK*/
#define I2S0_BCLK_PF10           SYS_GPF_MFP2_PF10MFP_I2S0_BCLK       /*!< GPF_MFP2 PF10 setting for I2S0_BCLK*/
#define I2S0_BCLK_PE1            SYS_GPE_MFP0_PE1MFP_I2S0_BCLK        /*!< GPE_MFP0 PE1 setting for I2S0_BCLK*/
#define I2S0_BCLK_PA12           SYS_GPA_MFP3_PA12MFP_I2S0_BCLK       /*!< GPA_MFP3 PA12 setting for I2S0_BCLK*/
#define I2S0_BCLK_PB5            SYS_GPB_MFP1_PB5MFP_I2S0_BCLK        /*!< GPB_MFP1 PB5 setting for I2S0_BCLK*/
#define I2S0_BCLK_PI6            SYS_GPI_MFP1_PI6MFP_I2S0_BCLK        /*!< GPI_MFP1 PI6 setting for I2S0_BCLK*/
#define I2S0_BCLK_PC4            SYS_GPC_MFP1_PC4MFP_I2S0_BCLK        /*!< GPC_MFP1 PC4 setting for I2S0_BCLK*/
#define I2S0_DI_PB3              SYS_GPB_MFP0_PB3MFP_I2S0_DI          /*!< GPB_MFP0 PB3 setting for I2S0_DI*/
#define I2S0_DI_PC2              SYS_GPC_MFP0_PC2MFP_I2S0_DI          /*!< GPC_MFP0 PC2 setting for I2S0_DI*/
#define I2S0_DI_PI8              SYS_GPI_MFP2_PI8MFP_I2S0_DI          /*!< GPI_MFP2 PI8 setting for I2S0_DI*/
#define I2S0_DI_PA14             SYS_GPA_MFP3_PA14MFP_I2S0_DI         /*!< GPA_MFP3 PA14 setting for I2S0_DI*/
#define I2S0_DI_PF8              SYS_GPF_MFP2_PF8MFP_I2S0_DI          /*!< GPF_MFP2 PF8 setting for I2S0_DI*/
#define I2S0_DI_PH8              SYS_GPH_MFP2_PH8MFP_I2S0_DI          /*!< GPH_MFP2 PH8 setting for I2S0_DI*/
#define I2S0_DI_PE10             SYS_GPE_MFP2_PE10MFP_I2S0_DI         /*!< GPE_MFP2 PE10 setting for I2S0_DI*/
#define I2S0_DO_PH9              SYS_GPH_MFP2_PH9MFP_I2S0_DO          /*!< GPH_MFP2 PH9 setting for I2S0_DO*/
#define I2S0_DO_PC1              SYS_GPC_MFP0_PC1MFP_I2S0_DO          /*!< GPC_MFP0 PC1 setting for I2S0_DO*/
#define I2S0_DO_PA15             SYS_GPA_MFP3_PA15MFP_I2S0_DO         /*!< GPA_MFP3 PA15 setting for I2S0_DO*/
#define I2S0_DO_PB2              SYS_GPB_MFP0_PB2MFP_I2S0_DO          /*!< GPB_MFP0 PB2 setting for I2S0_DO*/
#define I2S0_DO_PF7              SYS_GPF_MFP1_PF7MFP_I2S0_DO          /*!< GPF_MFP1 PF7 setting for I2S0_DO*/
#define I2S0_DO_PF0              SYS_GPF_MFP0_PF0MFP_I2S0_DO          /*!< GPF_MFP0 PF0 setting for I2S0_DO*/
#define I2S0_DO_PE11             SYS_GPE_MFP2_PE11MFP_I2S0_DO         /*!< GPE_MFP2 PE11 setting for I2S0_DO*/
#define I2S0_DO_PI9              SYS_GPI_MFP2_PI9MFP_I2S0_DO          /*!< GPI_MFP2 PI9 setting for I2S0_DO*/
#define I2S0_LRCK_PF6            SYS_GPF_MFP1_PF6MFP_I2S0_LRCK        /*!< GPF_MFP1 PF6 setting for I2S0_LRCK*/
#define I2S0_LRCK_PE12           SYS_GPE_MFP3_PE12MFP_I2S0_LRCK       /*!< GPE_MFP3 PE12 setting for I2S0_LRCK*/
#define I2S0_LRCK_PH10           SYS_GPH_MFP2_PH10MFP_I2S0_LRCK       /*!< GPH_MFP2 PH10 setting for I2S0_LRCK*/
#define I2S0_LRCK_PB1            SYS_GPB_MFP0_PB1MFP_I2S0_LRCK        /*!< GPB_MFP0 PB1 setting for I2S0_LRCK*/
#define I2S0_LRCK_PF1            SYS_GPF_MFP0_PF1MFP_I2S0_LRCK        /*!< GPF_MFP0 PF1 setting for I2S0_LRCK*/
#define I2S0_LRCK_PC0            SYS_GPC_MFP0_PC0MFP_I2S0_LRCK        /*!< GPC_MFP0 PC0 setting for I2S0_LRCK*/
#define I2S0_LRCK_PI10           SYS_GPI_MFP2_PI10MFP_I2S0_LRCK       /*!< GPI_MFP2 PI10 setting for I2S0_LRCK*/
#define I2S0_MCLK_PE0            SYS_GPE_MFP0_PE0MFP_I2S0_MCLK        /*!< GPE_MFP0 PE0 setting for I2S0_MCLK*/
#define I2S0_MCLK_PB4            SYS_GPB_MFP1_PB4MFP_I2S0_MCLK        /*!< GPB_MFP1 PB4 setting for I2S0_MCLK*/
#define I2S0_MCLK_PF9            SYS_GPF_MFP2_PF9MFP_I2S0_MCLK        /*!< GPF_MFP2 PF9 setting for I2S0_MCLK*/
#define I2S0_MCLK_PE9            SYS_GPE_MFP2_PE9MFP_I2S0_MCLK        /*!< GPE_MFP2 PE9 setting for I2S0_MCLK*/
#define I2S0_MCLK_PI7            SYS_GPI_MFP1_PI7MFP_I2S0_MCLK        /*!< GPI_MFP1 PI7 setting for I2S0_MCLK*/
#define I2S0_MCLK_PA13           SYS_GPA_MFP3_PA13MFP_I2S0_MCLK       /*!< GPA_MFP3 PA13 setting for I2S0_MCLK*/
#define I2S0_MCLK_PC3            SYS_GPC_MFP0_PC3MFP_I2S0_MCLK        /*!< GPC_MFP0 PC3 setting for I2S0_MCLK*/
#define I2S1_BCLK_PD14           SYS_GPD_MFP3_PD14MFP_I2S1_BCLK       /*!< GPD_MFP3 PD14 setting for I2S1_BCLK*/
#define I2S1_BCLK_PA11           SYS_GPA_MFP2_PA11MFP_I2S1_BCLK       /*!< GPA_MFP2 PA11 setting for I2S1_BCLK*/
#define I2S1_BCLK_PD3            SYS_GPD_MFP0_PD3MFP_I2S1_BCLK        /*!< GPD_MFP0 PD3 setting for I2S1_BCLK*/
#define I2S1_DI_PD1              SYS_GPD_MFP0_PD1MFP_I2S1_DI          /*!< GPD_MFP0 PD1 setting for I2S1_DI*/
#define I2S1_DI_PA9              SYS_GPA_MFP2_PA9MFP_I2S1_DI          /*!< GPA_MFP2 PA9 setting for I2S1_DI*/
#define I2S1_DI_PG6              SYS_GPG_MFP1_PG6MFP_I2S1_DI          /*!< GPG_MFP1 PG6 setting for I2S1_DI*/
#define I2S1_DO_PD0              SYS_GPD_MFP0_PD0MFP_I2S1_DO          /*!< GPD_MFP0 PD0 setting for I2S1_DO*/
#define I2S1_DO_PA8              SYS_GPA_MFP2_PA8MFP_I2S1_DO          /*!< GPA_MFP2 PA8 setting for I2S1_DO*/
#define I2S1_DO_PG7              SYS_GPG_MFP1_PG7MFP_I2S1_DO          /*!< GPG_MFP1 PG7 setting for I2S1_DO*/
#define I2S1_LRCK_PB0            SYS_GPB_MFP0_PB0MFP_I2S1_LRCK        /*!< GPB_MFP0 PB0 setting for I2S1_LRCK*/
#define I2S1_LRCK_PD13           SYS_GPD_MFP3_PD13MFP_I2S1_LRCK       /*!< GPD_MFP3 PD13 setting for I2S1_LRCK*/
#define I2S1_LRCK_PG8            SYS_GPG_MFP2_PG8MFP_I2S1_LRCK        /*!< GPG_MFP2 PG8 setting for I2S1_LRCK*/
#define I2S1_MCLK_PD2            SYS_GPD_MFP0_PD2MFP_I2S1_MCLK        /*!< GPD_MFP0 PD2 setting for I2S1_MCLK*/
#define I2S1_MCLK_PA10           SYS_GPA_MFP2_PA10MFP_I2S1_MCLK       /*!< GPA_MFP2 PA10 setting for I2S1_MCLK*/
#define I2S1_MCLK_PG5            SYS_GPG_MFP1_PG5MFP_I2S1_MCLK        /*!< GPG_MFP1 PG5 setting for I2S1_MCLK*/
#define ICE_CLK_PF1              SYS_GPF_MFP0_PF1MFP_ICE_CLK          /*!< GPF_MFP0 PF1 setting for ICE_CLK*/
#define ICE_DAT_PF0              SYS_GPF_MFP0_PF0MFP_ICE_DAT          /*!< GPF_MFP0 PF0 setting for ICE_DAT*/
#define INT0_PA6                 SYS_GPA_MFP1_PA6MFP_INT0             /*!< GPA_MFP1 PA6 setting for INT0*/
#define INT0_PB5                 SYS_GPB_MFP1_PB5MFP_INT0             /*!< GPB_MFP1 PB5 setting for INT0*/
#define INT1_PA7                 SYS_GPA_MFP1_PA7MFP_INT1             /*!< GPA_MFP1 PA7 setting for INT1*/
#define INT1_PB4                 SYS_GPB_MFP1_PB4MFP_INT1             /*!< GPB_MFP1 PB4 setting for INT1*/
#define INT2_PB3                 SYS_GPB_MFP0_PB3MFP_INT2             /*!< GPB_MFP0 PB3 setting for INT2*/
#define INT2_PC6                 SYS_GPC_MFP1_PC6MFP_INT2             /*!< GPC_MFP1 PC6 setting for INT2*/
#define INT3_PC7                 SYS_GPC_MFP1_PC7MFP_INT3             /*!< GPC_MFP1 PC7 setting for INT3*/
#define INT3_PB2                 SYS_GPB_MFP0_PB2MFP_INT3             /*!< GPB_MFP0 PB2 setting for INT3*/
#define INT4_PA8                 SYS_GPA_MFP2_PA8MFP_INT4             /*!< GPA_MFP2 PA8 setting for INT4*/
#define INT4_PB6                 SYS_GPB_MFP1_PB6MFP_INT4             /*!< GPB_MFP1 PB6 setting for INT4*/
#define INT5_PD12                SYS_GPD_MFP3_PD12MFP_INT5            /*!< GPD_MFP3 PD12 setting for INT5*/
#define INT5_PB7                 SYS_GPB_MFP1_PB7MFP_INT5             /*!< GPB_MFP1 PB7 setting for INT5*/
#define INT6_PB8                 SYS_GPB_MFP2_PB8MFP_INT6             /*!< GPB_MFP2 PB8 setting for INT6*/
#define INT6_PD11                SYS_GPD_MFP2_PD11MFP_INT6            /*!< GPD_MFP2 PD11 setting for INT6*/
#define INT7_PB9                 SYS_GPB_MFP2_PB9MFP_INT7             /*!< GPB_MFP2 PB9 setting for INT7*/
#define INT7_PD10                SYS_GPD_MFP2_PD10MFP_INT7            /*!< GPD_MFP2 PD10 setting for INT7*/
#define TRACE_SWO_PF6            SYS_GPF_MFP1_PF6MFP_TRACE_SWO        /*!< GPF_MFP1 PF6 setting for TRACE_SWO*/
#define TRACE_SWO_PC14           SYS_GPC_MFP3_PC14MFP_TRACE_SWO       /*!< GPC_MFP3 PC14 setting for TRACE_SWO*/
#define TRACE_SWO_PE13           SYS_GPE_MFP3_PE13MFP_TRACE_SWO       /*!< GPE_MFP3 PE13 setting for TRACE_SWO*/
#define KPI_COL0_PA6             SYS_GPA_MFP1_PA6MFP_KPI_COL0         /*!< GPA_MFP1 PA6 setting for KPI_COL0*/
#define KPI_COL0_PB15            SYS_GPB_MFP3_PB15MFP_KPI_COL0        /*!< GPB_MFP3 PB15 setting for KPI_COL0*/
#define KPI_COL1_PA7             SYS_GPA_MFP1_PA7MFP_KPI_COL1         /*!< GPA_MFP1 PA7 setting for KPI_COL1*/
#define KPI_COL1_PB14            SYS_GPB_MFP3_PB14MFP_KPI_COL1        /*!< GPB_MFP3 PB14 setting for KPI_COL1*/
#define KPI_COL2_PC6             SYS_GPC_MFP1_PC6MFP_KPI_COL2         /*!< GPC_MFP1 PC6 setting for KPI_COL2*/
#define KPI_COL2_PB13            SYS_GPB_MFP3_PB13MFP_KPI_COL2        /*!< GPB_MFP3 PB13 setting for KPI_COL2*/
#define KPI_COL3_PC7             SYS_GPC_MFP1_PC7MFP_KPI_COL3         /*!< GPC_MFP1 PC7 setting for KPI_COL3*/
#define KPI_COL3_PB12            SYS_GPB_MFP3_PB12MFP_KPI_COL3        /*!< GPB_MFP3 PB12 setting for KPI_COL3*/
#define KPI_COL4_PB7             SYS_GPB_MFP1_PB7MFP_KPI_COL4         /*!< GPB_MFP1 PB7 setting for KPI_COL4*/
#define KPI_COL4_PC8             SYS_GPC_MFP2_PC8MFP_KPI_COL4         /*!< GPC_MFP2 PC8 setting for KPI_COL4*/
#define KPI_COL5_PB6             SYS_GPB_MFP1_PB6MFP_KPI_COL5         /*!< GPB_MFP1 PB6 setting for KPI_COL5*/
#define KPI_COL5_PE13            SYS_GPE_MFP3_PE13MFP_KPI_COL5        /*!< GPE_MFP3 PE13 setting for KPI_COL5*/
#define KPI_COL6_PE12            SYS_GPE_MFP3_PE12MFP_KPI_COL6        /*!< GPE_MFP3 PE12 setting for KPI_COL6*/
#define KPI_COL6_PB5             SYS_GPB_MFP1_PB5MFP_KPI_COL6         /*!< GPB_MFP1 PB5 setting for KPI_COL6*/
#define KPI_COL7_PE11            SYS_GPE_MFP2_PE11MFP_KPI_COL7        /*!< GPE_MFP2 PE11 setting for KPI_COL7*/
#define KPI_COL7_PB4             SYS_GPB_MFP1_PB4MFP_KPI_COL7         /*!< GPB_MFP1 PB4 setting for KPI_COL7*/
#define KPI_ROW0_PC5             SYS_GPC_MFP1_PC5MFP_KPI_ROW0         /*!< GPC_MFP1 PC5 setting for KPI_ROW0*/
#define KPI_ROW0_PB3             SYS_GPB_MFP0_PB3MFP_KPI_ROW0         /*!< GPB_MFP0 PB3 setting for KPI_ROW0*/
#define KPI_ROW1_PC4             SYS_GPC_MFP1_PC4MFP_KPI_ROW1         /*!< GPC_MFP1 PC4 setting for KPI_ROW1*/
#define KPI_ROW1_PB2             SYS_GPB_MFP0_PB2MFP_KPI_ROW1         /*!< GPB_MFP0 PB2 setting for KPI_ROW1*/
#define KPI_ROW2_PB1             SYS_GPB_MFP0_PB1MFP_KPI_ROW2         /*!< GPB_MFP0 PB1 setting for KPI_ROW2*/
#define KPI_ROW2_PC3             SYS_GPC_MFP0_PC3MFP_KPI_ROW2         /*!< GPC_MFP0 PC3 setting for KPI_ROW2*/
#define KPI_ROW3_PC2             SYS_GPC_MFP0_PC2MFP_KPI_ROW3         /*!< GPC_MFP0 PC2 setting for KPI_ROW3*/
#define KPI_ROW3_PB0             SYS_GPB_MFP0_PB0MFP_KPI_ROW3         /*!< GPB_MFP0 PB0 setting for KPI_ROW3*/
#define KPI_ROW4_PA11            SYS_GPA_MFP2_PA11MFP_KPI_ROW4        /*!< GPA_MFP2 PA11 setting for KPI_ROW4*/
#define KPI_ROW4_PC1             SYS_GPC_MFP0_PC1MFP_KPI_ROW4         /*!< GPC_MFP0 PC1 setting for KPI_ROW4*/
#define KPI_ROW5_PA10            SYS_GPA_MFP2_PA10MFP_KPI_ROW5        /*!< GPA_MFP2 PA10 setting for KPI_ROW5*/
#define KPI_ROW5_PC0             SYS_GPC_MFP0_PC0MFP_KPI_ROW5         /*!< GPC_MFP0 PC0 setting for KPI_ROW5*/
#define PSIO0_CH0_PC5            SYS_GPC_MFP1_PC5MFP_PSIO0_CH0        /*!< GPC_MFP1 PC5 setting for PSIO0_CH0*/
#define PSIO0_CH0_PB15           SYS_GPB_MFP3_PB15MFP_PSIO0_CH0       /*!< GPB_MFP3 PB15 setting for PSIO0_CH0*/
#define PSIO0_CH0_PE7            SYS_GPE_MFP1_PE7MFP_PSIO0_CH0        /*!< GPE_MFP1 PE7 setting for PSIO0_CH0*/
#define PSIO0_CH0_PE14           SYS_GPE_MFP3_PE14MFP_PSIO0_CH0       /*!< GPE_MFP3 PE14 setting for PSIO0_CH0*/
#define PSIO0_CH1_PC4            SYS_GPC_MFP1_PC4MFP_PSIO0_CH1        /*!< GPC_MFP1 PC4 setting for PSIO0_CH1*/
#define PSIO0_CH1_PE15           SYS_GPE_MFP3_PE15MFP_PSIO0_CH1       /*!< GPE_MFP3 PE15 setting for PSIO0_CH1*/
#define PSIO0_CH1_PE6            SYS_GPE_MFP1_PE6MFP_PSIO0_CH1        /*!< GPE_MFP1 PE6 setting for PSIO0_CH1*/
#define PSIO0_CH1_PB14           SYS_GPB_MFP3_PB14MFP_PSIO0_CH1       /*!< GPB_MFP3 PB14 setting for PSIO0_CH1*/
#define PSIO0_CH2_PC3            SYS_GPC_MFP0_PC3MFP_PSIO0_CH2        /*!< GPC_MFP0 PC3 setting for PSIO0_CH2*/
#define PSIO0_CH2_PD9            SYS_GPD_MFP2_PD9MFP_PSIO0_CH2        /*!< GPD_MFP2 PD9 setting for PSIO0_CH2*/
#define PSIO0_CH2_PE5            SYS_GPE_MFP1_PE5MFP_PSIO0_CH2        /*!< GPE_MFP1 PE5 setting for PSIO0_CH2*/
#define PSIO0_CH2_PB13           SYS_GPB_MFP3_PB13MFP_PSIO0_CH2       /*!< GPB_MFP3 PB13 setting for PSIO0_CH2*/
#define PSIO0_CH3_PD8            SYS_GPD_MFP2_PD8MFP_PSIO0_CH3        /*!< GPD_MFP2 PD8 setting for PSIO0_CH3*/
#define PSIO0_CH3_PC2            SYS_GPC_MFP0_PC2MFP_PSIO0_CH3        /*!< GPC_MFP0 PC2 setting for PSIO0_CH3*/
#define PSIO0_CH3_PE4            SYS_GPE_MFP1_PE4MFP_PSIO0_CH3        /*!< GPE_MFP1 PE4 setting for PSIO0_CH3*/
#define PSIO0_CH3_PB12           SYS_GPB_MFP3_PB12MFP_PSIO0_CH3       /*!< GPB_MFP3 PB12 setting for PSIO0_CH3*/
#define PSIO0_CH4_PD7            SYS_GPD_MFP1_PD7MFP_PSIO0_CH4        /*!< GPD_MFP1 PD7 setting for PSIO0_CH4*/
#define PSIO0_CH4_PA12           SYS_GPA_MFP3_PA12MFP_PSIO0_CH4       /*!< GPA_MFP3 PA12 setting for PSIO0_CH4*/
#define PSIO0_CH4_PB5            SYS_GPB_MFP1_PB5MFP_PSIO0_CH4        /*!< GPB_MFP1 PB5 setting for PSIO0_CH4*/
#define PSIO0_CH4_PA3            SYS_GPA_MFP0_PA3MFP_PSIO0_CH4        /*!< GPA_MFP0 PA3 setting for PSIO0_CH4*/
#define PSIO0_CH5_PA13           SYS_GPA_MFP3_PA13MFP_PSIO0_CH5       /*!< GPA_MFP3 PA13 setting for PSIO0_CH5*/
#define PSIO0_CH5_PB4            SYS_GPB_MFP1_PB4MFP_PSIO0_CH5        /*!< GPB_MFP1 PB4 setting for PSIO0_CH5*/
#define PSIO0_CH5_PA2            SYS_GPA_MFP0_PA2MFP_PSIO0_CH5        /*!< GPA_MFP0 PA2 setting for PSIO0_CH5*/
#define PSIO0_CH5_PD6            SYS_GPD_MFP1_PD6MFP_PSIO0_CH5        /*!< GPD_MFP1 PD6 setting for PSIO0_CH5*/
#define PSIO0_CH6_PB3            SYS_GPB_MFP0_PB3MFP_PSIO0_CH6        /*!< GPB_MFP0 PB3 setting for PSIO0_CH6*/
#define PSIO0_CH6_PD5            SYS_GPD_MFP1_PD5MFP_PSIO0_CH6        /*!< GPD_MFP1 PD5 setting for PSIO0_CH6*/
#define PSIO0_CH6_PA1            SYS_GPA_MFP0_PA1MFP_PSIO0_CH6        /*!< GPA_MFP0 PA1 setting for PSIO0_CH6*/
#define PSIO0_CH6_PA14           SYS_GPA_MFP3_PA14MFP_PSIO0_CH6       /*!< GPA_MFP3 PA14 setting for PSIO0_CH6*/
#define PSIO0_CH7_PD4            SYS_GPD_MFP1_PD4MFP_PSIO0_CH7        /*!< GPD_MFP1 PD4 setting for PSIO0_CH7*/
#define PSIO0_CH7_PA15           SYS_GPA_MFP3_PA15MFP_PSIO0_CH7       /*!< GPA_MFP3 PA15 setting for PSIO0_CH7*/
#define PSIO0_CH7_PB2            SYS_GPB_MFP0_PB2MFP_PSIO0_CH7        /*!< GPB_MFP0 PB2 setting for PSIO0_CH7*/
#define PSIO0_CH7_PA0            SYS_GPA_MFP0_PA0MFP_PSIO0_CH7        /*!< GPA_MFP0 PA0 setting for PSIO0_CH7*/
#define EQEI0_A_PE3              SYS_GPE_MFP0_PE3MFP_EQEI0_A          /*!< GPE_MFP0 PE3 setting for EQEI0_A*/
#define EQEI0_A_PA4              SYS_GPA_MFP1_PA4MFP_EQEI0_A          /*!< GPA_MFP1 PA4 setting for EQEI0_A*/
#define EQEI0_A_PD11             SYS_GPD_MFP2_PD11MFP_EQEI0_A         /*!< GPD_MFP2 PD11 setting for EQEI0_A*/
#define EQEI0_B_PA3              SYS_GPA_MFP0_PA3MFP_EQEI0_B          /*!< GPA_MFP0 PA3 setting for EQEI0_B*/
#define EQEI0_B_PD10             SYS_GPD_MFP2_PD10MFP_EQEI0_B         /*!< GPD_MFP2 PD10 setting for EQEI0_B*/
#define EQEI0_B_PE2              SYS_GPE_MFP0_PE2MFP_EQEI0_B          /*!< GPE_MFP0 PE2 setting for EQEI0_B*/
#define EQEI0_INDEX_PE4          SYS_GPE_MFP1_PE4MFP_EQEI0_INDEX      /*!< GPE_MFP1 PE4 setting for EQEI0_INDEX*/
#define EQEI0_INDEX_PA5          SYS_GPA_MFP1_PA5MFP_EQEI0_INDEX      /*!< GPA_MFP1 PA5 setting for EQEI0_INDEX*/
#define EQEI0_INDEX_PD12         SYS_GPD_MFP3_PD12MFP_EQEI0_INDEX     /*!< GPD_MFP3 PD12 setting for EQEI0_INDEX*/
#define EQEI1_A_PA9              SYS_GPA_MFP2_PA9MFP_EQEI1_A          /*!< GPA_MFP2 PA9 setting for EQEI1_A*/
#define EQEI1_A_PA13             SYS_GPA_MFP3_PA13MFP_EQEI1_A         /*!< GPA_MFP3 PA13 setting for EQEI1_A*/
#define EQEI1_A_PE6              SYS_GPE_MFP1_PE6MFP_EQEI1_A          /*!< GPE_MFP1 PE6 setting for EQEI1_A*/
#define EQEI1_B_PE5              SYS_GPE_MFP1_PE5MFP_EQEI1_B          /*!< GPE_MFP1 PE5 setting for EQEI1_B*/
#define EQEI1_B_PA8              SYS_GPA_MFP2_PA8MFP_EQEI1_B          /*!< GPA_MFP2 PA8 setting for EQEI1_B*/
#define EQEI1_B_PA14             SYS_GPA_MFP3_PA14MFP_EQEI1_B         /*!< GPA_MFP3 PA14 setting for EQEI1_B*/
#define EQEI1_INDEX_PA10         SYS_GPA_MFP2_PA10MFP_EQEI1_INDEX     /*!< GPA_MFP2 PA10 setting for EQEI1_INDEX*/
#define EQEI1_INDEX_PE7          SYS_GPE_MFP1_PE7MFP_EQEI1_INDEX      /*!< GPE_MFP1 PE7 setting for EQEI1_INDEX*/
#define EQEI1_INDEX_PA12         SYS_GPA_MFP3_PA12MFP_EQEI1_INDEX     /*!< GPA_MFP3 PA12 setting for EQEI1_INDEX*/
#define EQEI2_A_PE9              SYS_GPE_MFP2_PE9MFP_EQEI2_A          /*!< GPE_MFP2 PE9 setting for EQEI2_A*/
#define EQEI2_A_PF5              SYS_GPF_MFP1_PF5MFP_EQEI2_A          /*!< GPF_MFP1 PF5 setting for EQEI2_A*/
#define EQEI2_A_PD0              SYS_GPD_MFP0_PD0MFP_EQEI2_A          /*!< GPD_MFP0 PD0 setting for EQEI2_A*/
#define EQEI2_B_PF4              SYS_GPF_MFP1_PF4MFP_EQEI2_B          /*!< GPF_MFP1 PF4 setting for EQEI2_B*/
#define EQEI2_B_PE10             SYS_GPE_MFP2_PE10MFP_EQEI2_B         /*!< GPE_MFP2 PE10 setting for EQEI2_B*/
#define EQEI2_B_PD13             SYS_GPD_MFP3_PD13MFP_EQEI2_B         /*!< GPD_MFP3 PD13 setting for EQEI2_B*/
#define EQEI2_INDEX_PE8          SYS_GPE_MFP2_PE8MFP_EQEI2_INDEX      /*!< GPE_MFP2 PE8 setting for EQEI2_INDEX*/
#define EQEI2_INDEX_PD1          SYS_GPD_MFP0_PD1MFP_EQEI2_INDEX      /*!< GPD_MFP0 PD1 setting for EQEI2_INDEX*/
#define EQEI2_INDEX_PF6          SYS_GPF_MFP1_PF6MFP_EQEI2_INDEX      /*!< GPF_MFP1 PF6 setting for EQEI2_INDEX*/
#define EQEI3_A_PD3              SYS_GPD_MFP0_PD3MFP_EQEI3_A          /*!< GPD_MFP0 PD3 setting for EQEI3_A*/
#define EQEI3_A_PA1              SYS_GPA_MFP0_PA1MFP_EQEI3_A          /*!< GPA_MFP0 PA1 setting for EQEI3_A*/
#define EQEI3_B_PA0              SYS_GPA_MFP0_PA0MFP_EQEI3_B          /*!< GPA_MFP0 PA0 setting for EQEI3_B*/
#define EQEI3_B_PD2              SYS_GPD_MFP0_PD2MFP_EQEI3_B          /*!< GPD_MFP0 PD2 setting for EQEI3_B*/
#define EQEI3_INDEX_PA2          SYS_GPA_MFP0_PA2MFP_EQEI3_INDEX      /*!< GPA_MFP0 PA2 setting for EQEI3_INDEX*/
#define EQEI3_INDEX_PA15         SYS_GPA_MFP3_PA15MFP_EQEI3_INDEX     /*!< GPA_MFP3 PA15 setting for EQEI3_INDEX*/
#define QSPI0_CLK_PH8            SYS_GPH_MFP2_PH8MFP_QSPI0_CLK        /*!< GPH_MFP2 PH8 setting for QSPI0_CLK*/
#define QSPI0_CLK_PA2            SYS_GPA_MFP0_PA2MFP_QSPI0_CLK        /*!< GPA_MFP0 PA2 setting for QSPI0_CLK*/
#define QSPI0_CLK_PI15           SYS_GPI_MFP3_PI15MFP_QSPI0_CLK       /*!< GPI_MFP3 PI15 setting for QSPI0_CLK*/
#define QSPI0_CLK_PC2            SYS_GPC_MFP0_PC2MFP_QSPI0_CLK        /*!< GPC_MFP0 PC2 setting for QSPI0_CLK*/
#define QSPI0_CLK_PF2            SYS_GPF_MFP0_PF2MFP_QSPI0_CLK        /*!< GPF_MFP0 PF2 setting for QSPI0_CLK*/
#define QSPI0_CLK_PC14           SYS_GPC_MFP3_PC14MFP_QSPI0_CLK       /*!< GPC_MFP3 PC14 setting for QSPI0_CLK*/
#define QSPI0_MISO0_PC1          SYS_GPC_MFP0_PC1MFP_QSPI0_MISO0      /*!< GPC_MFP0 PC1 setting for QSPI0_MISO0*/
#define QSPI0_MISO0_PJ0          SYS_GPJ_MFP0_PJ0MFP_QSPI0_MISO0      /*!< GPJ_MFP0 PJ0 setting for QSPI0_MISO0*/
#define QSPI0_MISO0_PE1          SYS_GPE_MFP0_PE1MFP_QSPI0_MISO0      /*!< GPE_MFP0 PE1 setting for QSPI0_MISO0*/
#define QSPI0_MISO0_PA1          SYS_GPA_MFP0_PA1MFP_QSPI0_MISO0      /*!< GPA_MFP0 PA1 setting for QSPI0_MISO0*/
#define QSPI0_MISO1_PB1          SYS_GPB_MFP0_PB1MFP_QSPI0_MISO1      /*!< GPB_MFP0 PB1 setting for QSPI0_MISO1*/
#define QSPI0_MISO1_PI12         SYS_GPI_MFP3_PI12MFP_QSPI0_MISO1     /*!< GPI_MFP3 PI12 setting for QSPI0_MISO1*/
#define QSPI0_MISO1_PC5          SYS_GPC_MFP1_PC5MFP_QSPI0_MISO1      /*!< GPC_MFP1 PC5 setting for QSPI0_MISO1*/
#define QSPI0_MISO1_PH10         SYS_GPH_MFP2_PH10MFP_QSPI0_MISO1     /*!< GPH_MFP2 PH10 setting for QSPI0_MISO1*/
#define QSPI0_MISO1_PA5          SYS_GPA_MFP1_PA5MFP_QSPI0_MISO1      /*!< GPA_MFP1 PA5 setting for QSPI0_MISO1*/
#define QSPI0_MOSI0_PE0          SYS_GPE_MFP0_PE0MFP_QSPI0_MOSI0      /*!< GPE_MFP0 PE0 setting for QSPI0_MOSI0*/
#define QSPI0_MOSI0_PC0          SYS_GPC_MFP0_PC0MFP_QSPI0_MOSI0      /*!< GPC_MFP0 PC0 setting for QSPI0_MOSI0*/
#define QSPI0_MOSI0_PA0          SYS_GPA_MFP0_PA0MFP_QSPI0_MOSI0      /*!< GPA_MFP0 PA0 setting for QSPI0_MOSI0*/
#define QSPI0_MOSI0_PJ1          SYS_GPJ_MFP0_PJ1MFP_QSPI0_MOSI0      /*!< GPJ_MFP0 PJ1 setting for QSPI0_MOSI0*/
#define QSPI0_MOSI1_PA4          SYS_GPA_MFP1_PA4MFP_QSPI0_MOSI1      /*!< GPA_MFP1 PA4 setting for QSPI0_MOSI1*/
#define QSPI0_MOSI1_PC4          SYS_GPC_MFP1_PC4MFP_QSPI0_MOSI1      /*!< GPC_MFP1 PC4 setting for QSPI0_MOSI1*/
#define QSPI0_MOSI1_PH11         SYS_GPH_MFP2_PH11MFP_QSPI0_MOSI1     /*!< GPH_MFP2 PH11 setting for QSPI0_MOSI1*/
#define QSPI0_MOSI1_PI13         SYS_GPI_MFP3_PI13MFP_QSPI0_MOSI1     /*!< GPI_MFP3 PI13 setting for QSPI0_MOSI1*/
#define QSPI0_MOSI1_PB0          SYS_GPB_MFP0_PB0MFP_QSPI0_MOSI1      /*!< GPB_MFP0 PB0 setting for QSPI0_MOSI1*/
#define QSPI0_SS_PI14            SYS_GPI_MFP3_PI14MFP_QSPI0_SS        /*!< GPI_MFP3 PI14 setting for QSPI0_SS*/
#define QSPI0_SS_PA3             SYS_GPA_MFP0_PA3MFP_QSPI0_SS         /*!< GPA_MFP0 PA3 setting for QSPI0_SS*/
#define QSPI0_SS_PC3             SYS_GPC_MFP0_PC3MFP_QSPI0_SS         /*!< GPC_MFP0 PC3 setting for QSPI0_SS*/
#define QSPI0_SS_PH9             SYS_GPH_MFP2_PH9MFP_QSPI0_SS         /*!< GPH_MFP2 PH9 setting for QSPI0_SS*/
#define QSPI1_CLK_PH15           SYS_GPH_MFP3_PH15MFP_QSPI1_CLK       /*!< GPH_MFP3 PH15 setting for QSPI1_CLK*/
#define QSPI1_CLK_PC4            SYS_GPC_MFP1_PC4MFP_QSPI1_CLK        /*!< GPC_MFP1 PC4 setting for QSPI1_CLK*/
#define QSPI1_CLK_PJ3            SYS_GPJ_MFP0_PJ3MFP_QSPI1_CLK        /*!< GPJ_MFP0 PJ3 setting for QSPI1_CLK*/
#define QSPI1_CLK_PG12           SYS_GPG_MFP3_PG12MFP_QSPI1_CLK       /*!< GPG_MFP3 PG12 setting for QSPI1_CLK*/
#define QSPI1_CLK_PC0            SYS_GPC_MFP0_PC0MFP_QSPI1_CLK        /*!< GPC_MFP0 PC0 setting for QSPI1_CLK*/
#define QSPI1_MISO0_PD7          SYS_GPD_MFP1_PD7MFP_QSPI1_MISO0      /*!< GPD_MFP1 PD7 setting for QSPI1_MISO0*/
#define QSPI1_MISO0_PA12         SYS_GPA_MFP3_PA12MFP_QSPI1_MISO0     /*!< GPA_MFP3 PA12 setting for QSPI1_MISO0*/
#define QSPI1_MISO0_PC3          SYS_GPC_MFP0_PC3MFP_QSPI1_MISO0      /*!< GPC_MFP0 PC3 setting for QSPI1_MISO0*/
#define QSPI1_MISO0_PJ4          SYS_GPJ_MFP1_PJ4MFP_QSPI1_MISO0      /*!< GPJ_MFP1 PJ4 setting for QSPI1_MISO0*/
#define QSPI1_MISO0_PG13         SYS_GPG_MFP3_PG13MFP_QSPI1_MISO0     /*!< GPG_MFP3 PG13 setting for QSPI1_MISO0*/
#define QSPI1_MISO0_PF0          SYS_GPF_MFP0_PF0MFP_QSPI1_MISO0      /*!< GPF_MFP0 PF0 setting for QSPI1_MISO0*/
#define QSPI1_MISO1_PG9          SYS_GPG_MFP2_PG9MFP_QSPI1_MISO1      /*!< GPG_MFP2 PG9 setting for QSPI1_MISO1*/
#define QSPI1_MISO1_PA7          SYS_GPA_MFP1_PA7MFP_QSPI1_MISO1      /*!< GPA_MFP1 PA7 setting for QSPI1_MISO1*/
#define QSPI1_MISO1_PH12         SYS_GPH_MFP3_PH12MFP_QSPI1_MISO1     /*!< GPH_MFP3 PH12 setting for QSPI1_MISO1*/
#define QSPI1_MISO1_PG15         SYS_GPG_MFP3_PG15MFP_QSPI1_MISO1     /*!< GPG_MFP3 PG15 setting for QSPI1_MISO1*/
#define QSPI1_MOSI0_PA13         SYS_GPA_MFP3_PA13MFP_QSPI1_MOSI0     /*!< GPA_MFP3 PA13 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PD13         SYS_GPD_MFP3_PD13MFP_QSPI1_MOSI0     /*!< GPD_MFP3 PD13 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PG14         SYS_GPG_MFP3_PG14MFP_QSPI1_MOSI0     /*!< GPG_MFP3 PG14 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PC2          SYS_GPC_MFP0_PC2MFP_QSPI1_MOSI0      /*!< GPC_MFP0 PC2 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PJ5          SYS_GPJ_MFP1_PJ5MFP_QSPI1_MOSI0      /*!< GPJ_MFP1 PJ5 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PD6          SYS_GPD_MFP1_PD6MFP_QSPI1_MOSI0      /*!< GPD_MFP1 PD6 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI0_PF1          SYS_GPF_MFP0_PF1MFP_QSPI1_MOSI0      /*!< GPF_MFP0 PF1 setting for QSPI1_MOSI0*/
#define QSPI1_MOSI1_PG10         SYS_GPG_MFP2_PG10MFP_QSPI1_MOSI1     /*!< GPG_MFP2 PG10 setting for QSPI1_MOSI1*/
#define QSPI1_MOSI1_PA6          SYS_GPA_MFP1_PA6MFP_QSPI1_MOSI1      /*!< GPA_MFP1 PA6 setting for QSPI1_MOSI1*/
#define QSPI1_MOSI1_PH13         SYS_GPH_MFP3_PH13MFP_QSPI1_MOSI1     /*!< GPH_MFP3 PH13 setting for QSPI1_MOSI1*/
#define QSPI1_MOSI1_PD13         SYS_GPD_MFP3_PD13MFP_QSPI1_MOSI1     /*!< GPD_MFP3 PD13 setting for QSPI1_MOSI1*/
#define QSPI1_SS_PG11            SYS_GPG_MFP2_PG11MFP_QSPI1_SS        /*!< GPG_MFP2 PG11 setting for QSPI1_SS*/
#define QSPI1_SS_PH14            SYS_GPH_MFP3_PH14MFP_QSPI1_SS        /*!< GPH_MFP3 PH14 setting for QSPI1_SS*/
#define QSPI1_SS_PC5             SYS_GPC_MFP1_PC5MFP_QSPI1_SS         /*!< GPC_MFP1 PC5 setting for QSPI1_SS*/
#define QSPI1_SS_PJ2             SYS_GPJ_MFP0_PJ2MFP_QSPI1_SS         /*!< GPJ_MFP0 PJ2 setting for QSPI1_SS*/
#define QSPI1_SS_PC1             SYS_GPC_MFP0_PC1MFP_QSPI1_SS         /*!< GPC_MFP0 PC1 setting for QSPI1_SS*/
#define SC0_CLK_PA0              SYS_GPA_MFP0_PA0MFP_SC0_CLK          /*!< GPA_MFP0 PA0 setting for SC0_CLK*/
#define SC0_CLK_PF6              SYS_GPF_MFP1_PF6MFP_SC0_CLK          /*!< GPF_MFP1 PF6 setting for SC0_CLK*/
#define SC0_CLK_PE2              SYS_GPE_MFP0_PE2MFP_SC0_CLK          /*!< GPE_MFP0 PE2 setting for SC0_CLK*/
#define SC0_CLK_PB5              SYS_GPB_MFP1_PB5MFP_SC0_CLK          /*!< GPB_MFP1 PB5 setting for SC0_CLK*/
#define SC0_DAT_PE3              SYS_GPE_MFP0_PE3MFP_SC0_DAT          /*!< GPE_MFP0 PE3 setting for SC0_DAT*/
#define SC0_DAT_PB4              SYS_GPB_MFP1_PB4MFP_SC0_DAT          /*!< GPB_MFP1 PB4 setting for SC0_DAT*/
#define SC0_DAT_PA1              SYS_GPA_MFP0_PA1MFP_SC0_DAT          /*!< GPA_MFP0 PA1 setting for SC0_DAT*/
#define SC0_DAT_PF7              SYS_GPF_MFP1_PF7MFP_SC0_DAT          /*!< GPF_MFP1 PF7 setting for SC0_DAT*/
#define SC0_PWR_PE5              SYS_GPE_MFP1_PE5MFP_SC0_PWR          /*!< GPE_MFP1 PE5 setting for SC0_PWR*/
#define SC0_PWR_PA3              SYS_GPA_MFP0_PA3MFP_SC0_PWR          /*!< GPA_MFP0 PA3 setting for SC0_PWR*/
#define SC0_PWR_PB2              SYS_GPB_MFP0_PB2MFP_SC0_PWR          /*!< GPB_MFP0 PB2 setting for SC0_PWR*/
#define SC0_PWR_PF9              SYS_GPF_MFP2_PF9MFP_SC0_PWR          /*!< GPF_MFP2 PF9 setting for SC0_PWR*/
#define SC0_RST_PE4              SYS_GPE_MFP1_PE4MFP_SC0_RST          /*!< GPE_MFP1 PE4 setting for SC0_RST*/
#define SC0_RST_PA2              SYS_GPA_MFP0_PA2MFP_SC0_RST          /*!< GPA_MFP0 PA2 setting for SC0_RST*/
#define SC0_RST_PF8              SYS_GPF_MFP2_PF8MFP_SC0_RST          /*!< GPF_MFP2 PF8 setting for SC0_RST*/
#define SC0_RST_PB3              SYS_GPB_MFP0_PB3MFP_SC0_RST          /*!< GPB_MFP0 PB3 setting for SC0_RST*/
#define SC0_nCD_PC12             SYS_GPC_MFP3_PC12MFP_SC0_nCD         /*!< GPC_MFP3 PC12 setting for SC0_nCD*/
#define SC0_nCD_PE6              SYS_GPE_MFP1_PE6MFP_SC0_nCD          /*!< GPE_MFP1 PE6 setting for SC0_nCD*/
#define SC0_nCD_PA4              SYS_GPA_MFP1_PA4MFP_SC0_nCD          /*!< GPA_MFP1 PA4 setting for SC0_nCD*/
#define SC0_nCD_PF10             SYS_GPF_MFP2_PF10MFP_SC0_nCD         /*!< GPF_MFP2 PF10 setting for SC0_nCD*/
#define SC1_CLK_PF1              SYS_GPF_MFP0_PF1MFP_SC1_CLK          /*!< GPF_MFP0 PF1 setting for SC1_CLK*/
#define SC1_CLK_PD4              SYS_GPD_MFP1_PD4MFP_SC1_CLK          /*!< GPD_MFP1 PD4 setting for SC1_CLK*/
#define SC1_CLK_PI10             SYS_GPI_MFP2_PI10MFP_SC1_CLK         /*!< GPI_MFP2 PI10 setting for SC1_CLK*/
#define SC1_CLK_PB12             SYS_GPB_MFP3_PB12MFP_SC1_CLK         /*!< GPB_MFP3 PB12 setting for SC1_CLK*/
#define SC1_CLK_PG8              SYS_GPG_MFP2_PG8MFP_SC1_CLK          /*!< GPG_MFP2 PG8 setting for SC1_CLK*/
#define SC1_CLK_PC0              SYS_GPC_MFP0_PC0MFP_SC1_CLK          /*!< GPC_MFP0 PC0 setting for SC1_CLK*/
#define SC1_DAT_PC1              SYS_GPC_MFP0_PC1MFP_SC1_DAT          /*!< GPC_MFP0 PC1 setting for SC1_DAT*/
#define SC1_DAT_PD5              SYS_GPD_MFP1_PD5MFP_SC1_DAT          /*!< GPD_MFP1 PD5 setting for SC1_DAT*/
#define SC1_DAT_PF0              SYS_GPF_MFP0_PF0MFP_SC1_DAT          /*!< GPF_MFP0 PF0 setting for SC1_DAT*/
#define SC1_DAT_PG7              SYS_GPG_MFP1_PG7MFP_SC1_DAT          /*!< GPG_MFP1 PG7 setting for SC1_DAT*/
#define SC1_DAT_PI9              SYS_GPI_MFP2_PI9MFP_SC1_DAT          /*!< GPI_MFP2 PI9 setting for SC1_DAT*/
#define SC1_DAT_PB13             SYS_GPB_MFP3_PB13MFP_SC1_DAT         /*!< GPB_MFP3 PB13 setting for SC1_DAT*/
#define SC1_PWR_PD7              SYS_GPD_MFP1_PD7MFP_SC1_PWR          /*!< GPD_MFP1 PD7 setting for SC1_PWR*/
#define SC1_PWR_PC3              SYS_GPC_MFP0_PC3MFP_SC1_PWR          /*!< GPC_MFP0 PC3 setting for SC1_PWR*/
#define SC1_PWR_PI7              SYS_GPI_MFP1_PI7MFP_SC1_PWR          /*!< GPI_MFP1 PI7 setting for SC1_PWR*/
#define SC1_PWR_PG5              SYS_GPG_MFP1_PG5MFP_SC1_PWR          /*!< GPG_MFP1 PG5 setting for SC1_PWR*/
#define SC1_PWR_PB15             SYS_GPB_MFP3_PB15MFP_SC1_PWR         /*!< GPB_MFP3 PB15 setting for SC1_PWR*/
#define SC1_RST_PI8              SYS_GPI_MFP2_PI8MFP_SC1_RST          /*!< GPI_MFP2 PI8 setting for SC1_RST*/
#define SC1_RST_PG6              SYS_GPG_MFP1_PG6MFP_SC1_RST          /*!< GPG_MFP1 PG6 setting for SC1_RST*/
#define SC1_RST_PB14             SYS_GPB_MFP3_PB14MFP_SC1_RST         /*!< GPB_MFP3 PB14 setting for SC1_RST*/
#define SC1_RST_PC2              SYS_GPC_MFP0_PC2MFP_SC1_RST          /*!< GPC_MFP0 PC2 setting for SC1_RST*/
#define SC1_RST_PD6              SYS_GPD_MFP1_PD6MFP_SC1_RST          /*!< GPD_MFP1 PD6 setting for SC1_RST*/
#define SC1_nCD_PD14             SYS_GPD_MFP3_PD14MFP_SC1_nCD         /*!< GPD_MFP3 PD14 setting for SC1_nCD*/
#define SC1_nCD_PC4              SYS_GPC_MFP1_PC4MFP_SC1_nCD          /*!< GPC_MFP1 PC4 setting for SC1_nCD*/
#define SC1_nCD_PI6              SYS_GPI_MFP1_PI6MFP_SC1_nCD          /*!< GPI_MFP1 PI6 setting for SC1_nCD*/
#define SC1_nCD_PD3              SYS_GPD_MFP0_PD3MFP_SC1_nCD          /*!< GPD_MFP0 PD3 setting for SC1_nCD*/
#define SC1_nCD_PC14             SYS_GPC_MFP3_PC14MFP_SC1_nCD         /*!< GPC_MFP3 PC14 setting for SC1_nCD*/
#define SC2_CLK_PA15             SYS_GPA_MFP3_PA15MFP_SC2_CLK         /*!< GPA_MFP3 PA15 setting for SC2_CLK*/
#define SC2_CLK_PD0              SYS_GPD_MFP0_PD0MFP_SC2_CLK          /*!< GPD_MFP0 PD0 setting for SC2_CLK*/
#define SC2_CLK_PA6              SYS_GPA_MFP1_PA6MFP_SC2_CLK          /*!< GPA_MFP1 PA6 setting for SC2_CLK*/
#define SC2_CLK_PE0              SYS_GPE_MFP0_PE0MFP_SC2_CLK          /*!< GPE_MFP0 PE0 setting for SC2_CLK*/
#define SC2_CLK_PA8              SYS_GPA_MFP2_PA8MFP_SC2_CLK          /*!< GPA_MFP2 PA8 setting for SC2_CLK*/
#define SC2_DAT_PD1              SYS_GPD_MFP0_PD1MFP_SC2_DAT          /*!< GPD_MFP0 PD1 setting for SC2_DAT*/
#define SC2_DAT_PA9              SYS_GPA_MFP2_PA9MFP_SC2_DAT          /*!< GPA_MFP2 PA9 setting for SC2_DAT*/
#define SC2_DAT_PE1              SYS_GPE_MFP0_PE1MFP_SC2_DAT          /*!< GPE_MFP0 PE1 setting for SC2_DAT*/
#define SC2_DAT_PA14             SYS_GPA_MFP3_PA14MFP_SC2_DAT         /*!< GPA_MFP3 PA14 setting for SC2_DAT*/
#define SC2_DAT_PA7              SYS_GPA_MFP1_PA7MFP_SC2_DAT          /*!< GPA_MFP1 PA7 setting for SC2_DAT*/
#define SC2_PWR_PC7              SYS_GPC_MFP1_PC7MFP_SC2_PWR          /*!< GPC_MFP1 PC7 setting for SC2_PWR*/
#define SC2_PWR_PA11             SYS_GPA_MFP2_PA11MFP_SC2_PWR         /*!< GPA_MFP2 PA11 setting for SC2_PWR*/
#define SC2_PWR_PA12             SYS_GPA_MFP3_PA12MFP_SC2_PWR         /*!< GPA_MFP3 PA12 setting for SC2_PWR*/
#define SC2_PWR_PD3              SYS_GPD_MFP0_PD3MFP_SC2_PWR          /*!< GPD_MFP0 PD3 setting for SC2_PWR*/
#define SC2_PWR_PH8              SYS_GPH_MFP2_PH8MFP_SC2_PWR          /*!< GPH_MFP2 PH8 setting for SC2_PWR*/
#define SC2_RST_PC6              SYS_GPC_MFP1_PC6MFP_SC2_RST          /*!< GPC_MFP1 PC6 setting for SC2_RST*/
#define SC2_RST_PD2              SYS_GPD_MFP0_PD2MFP_SC2_RST          /*!< GPD_MFP0 PD2 setting for SC2_RST*/
#define SC2_RST_PA13             SYS_GPA_MFP3_PA13MFP_SC2_RST         /*!< GPA_MFP3 PA13 setting for SC2_RST*/
#define SC2_RST_PA10             SYS_GPA_MFP2_PA10MFP_SC2_RST         /*!< GPA_MFP2 PA10 setting for SC2_RST*/
#define SC2_RST_PH9              SYS_GPH_MFP2_PH9MFP_SC2_RST          /*!< GPH_MFP2 PH9 setting for SC2_RST*/
#define SC2_nCD_PD13             SYS_GPD_MFP3_PD13MFP_SC2_nCD         /*!< GPD_MFP3 PD13 setting for SC2_nCD*/
#define SC2_nCD_PA5              SYS_GPA_MFP1_PA5MFP_SC2_nCD          /*!< GPA_MFP1 PA5 setting for SC2_nCD*/
#define SC2_nCD_PC13             SYS_GPC_MFP3_PC13MFP_SC2_nCD         /*!< GPC_MFP3 PC13 setting for SC2_nCD*/
#define SC2_nCD_PH10             SYS_GPH_MFP2_PH10MFP_SC2_nCD         /*!< GPH_MFP2 PH10 setting for SC2_nCD*/
#define SD0_CLK_PB1              SYS_GPB_MFP0_PB1MFP_SD0_CLK          /*!< GPB_MFP0 PB1 setting for SD0_CLK*/
#define SD0_CLK_PE6              SYS_GPE_MFP1_PE6MFP_SD0_CLK          /*!< GPE_MFP1 PE6 setting for SD0_CLK*/
#define SD0_CMD_PE7              SYS_GPE_MFP1_PE7MFP_SD0_CMD          /*!< GPE_MFP1 PE7 setting for SD0_CMD*/
#define SD0_CMD_PB0              SYS_GPB_MFP0_PB0MFP_SD0_CMD          /*!< GPB_MFP0 PB0 setting for SD0_CMD*/
#define SD0_DAT0_PE2             SYS_GPE_MFP0_PE2MFP_SD0_DAT0         /*!< GPE_MFP0 PE2 setting for SD0_DAT0*/
#define SD0_DAT0_PB2             SYS_GPB_MFP0_PB2MFP_SD0_DAT0         /*!< GPB_MFP0 PB2 setting for SD0_DAT0*/
#define SD0_DAT1_PB3             SYS_GPB_MFP0_PB3MFP_SD0_DAT1         /*!< GPB_MFP0 PB3 setting for SD0_DAT1*/
#define SD0_DAT1_PE3             SYS_GPE_MFP0_PE3MFP_SD0_DAT1         /*!< GPE_MFP0 PE3 setting for SD0_DAT1*/
#define SD0_DAT2_PE4             SYS_GPE_MFP1_PE4MFP_SD0_DAT2         /*!< GPE_MFP1 PE4 setting for SD0_DAT2*/
#define SD0_DAT2_PB4             SYS_GPB_MFP1_PB4MFP_SD0_DAT2         /*!< GPB_MFP1 PB4 setting for SD0_DAT2*/
#define SD0_DAT3_PE5             SYS_GPE_MFP1_PE5MFP_SD0_DAT3         /*!< GPE_MFP1 PE5 setting for SD0_DAT3*/
#define SD0_DAT3_PB5             SYS_GPB_MFP1_PB5MFP_SD0_DAT3         /*!< GPB_MFP1 PB5 setting for SD0_DAT3*/
#define SD0_nCD_PB12             SYS_GPB_MFP3_PB12MFP_SD0_nCD         /*!< GPB_MFP3 PB12 setting for SD0_nCD*/
#define SD0_nCD_PD13             SYS_GPD_MFP3_PD13MFP_SD0_nCD         /*!< GPD_MFP3 PD13 setting for SD0_nCD*/
#define SD1_CLK_PJ13             SYS_GPJ_MFP3_PJ13MFP_SD1_CLK         /*!< GPJ_MFP3 PJ13 setting for SD1_CLK*/
#define SD1_CLK_PG14             SYS_GPG_MFP3_PG14MFP_SD1_CLK         /*!< GPG_MFP3 PG14 setting for SD1_CLK*/
#define SD1_CLK_PD13             SYS_GPD_MFP3_PD13MFP_SD1_CLK         /*!< GPD_MFP3 PD13 setting for SD1_CLK*/
#define SD1_CLK_PA4              SYS_GPA_MFP1_PA4MFP_SD1_CLK          /*!< GPA_MFP1 PA4 setting for SD1_CLK*/
#define SD1_CLK_PB6              SYS_GPB_MFP1_PB6MFP_SD1_CLK          /*!< GPB_MFP1 PB6 setting for SD1_CLK*/
#define SD1_CMD_PA5              SYS_GPA_MFP1_PA5MFP_SD1_CMD          /*!< GPA_MFP1 PA5 setting for SD1_CMD*/
#define SD1_CMD_PJ12             SYS_GPJ_MFP3_PJ12MFP_SD1_CMD         /*!< GPJ_MFP3 PJ12 setting for SD1_CMD*/
#define SD1_CMD_PB7              SYS_GPB_MFP1_PB7MFP_SD1_CMD          /*!< GPB_MFP1 PB7 setting for SD1_CMD*/
#define SD1_CMD_PG13             SYS_GPG_MFP3_PG13MFP_SD1_CMD         /*!< GPG_MFP3 PG13 setting for SD1_CMD*/
#define SD1_DAT0_PA8             SYS_GPA_MFP2_PA8MFP_SD1_DAT0         /*!< GPA_MFP2 PA8 setting for SD1_DAT0*/
#define SD1_DAT0_PA0             SYS_GPA_MFP0_PA0MFP_SD1_DAT0         /*!< GPA_MFP0 PA0 setting for SD1_DAT0*/
#define SD1_DAT0_PG12            SYS_GPG_MFP3_PG12MFP_SD1_DAT0        /*!< GPG_MFP3 PG12 setting for SD1_DAT0*/
#define SD1_DAT0_PJ11            SYS_GPJ_MFP2_PJ11MFP_SD1_DAT0        /*!< GPJ_MFP2 PJ11 setting for SD1_DAT0*/
#define SD1_DAT1_PG11            SYS_GPG_MFP2_PG11MFP_SD1_DAT1        /*!< GPG_MFP2 PG11 setting for SD1_DAT1*/
#define SD1_DAT1_PJ10            SYS_GPJ_MFP2_PJ10MFP_SD1_DAT1        /*!< GPJ_MFP2 PJ10 setting for SD1_DAT1*/
#define SD1_DAT1_PA9             SYS_GPA_MFP2_PA9MFP_SD1_DAT1         /*!< GPA_MFP2 PA9 setting for SD1_DAT1*/
#define SD1_DAT1_PA1             SYS_GPA_MFP0_PA1MFP_SD1_DAT1         /*!< GPA_MFP0 PA1 setting for SD1_DAT1*/
#define SD1_DAT2_PA2             SYS_GPA_MFP0_PA2MFP_SD1_DAT2         /*!< GPA_MFP0 PA2 setting for SD1_DAT2*/
#define SD1_DAT2_PJ9             SYS_GPJ_MFP2_PJ9MFP_SD1_DAT2         /*!< GPJ_MFP2 PJ9 setting for SD1_DAT2*/
#define SD1_DAT2_PG10            SYS_GPG_MFP2_PG10MFP_SD1_DAT2        /*!< GPG_MFP2 PG10 setting for SD1_DAT2*/
#define SD1_DAT2_PA10            SYS_GPA_MFP2_PA10MFP_SD1_DAT2        /*!< GPA_MFP2 PA10 setting for SD1_DAT2*/
#define SD1_DAT3_PA3             SYS_GPA_MFP0_PA3MFP_SD1_DAT3         /*!< GPA_MFP0 PA3 setting for SD1_DAT3*/
#define SD1_DAT3_PJ8             SYS_GPJ_MFP2_PJ8MFP_SD1_DAT3         /*!< GPJ_MFP2 PJ8 setting for SD1_DAT3*/
#define SD1_DAT3_PA11            SYS_GPA_MFP2_PA11MFP_SD1_DAT3        /*!< GPA_MFP2 PA11 setting for SD1_DAT3*/
#define SD1_DAT3_PG9             SYS_GPG_MFP2_PG9MFP_SD1_DAT3         /*!< GPG_MFP2 PG9 setting for SD1_DAT3*/
#define SD1_nCD_PA6              SYS_GPA_MFP1_PA6MFP_SD1_nCD          /*!< GPA_MFP1 PA6 setting for SD1_nCD*/
#define SD1_nCD_PG15             SYS_GPG_MFP3_PG15MFP_SD1_nCD         /*!< GPG_MFP3 PG15 setting for SD1_nCD*/
#define SD1_nCD_PA12             SYS_GPA_MFP3_PA12MFP_SD1_nCD         /*!< GPA_MFP3 PA12 setting for SD1_nCD*/
#define SD1_nCD_PE14             SYS_GPE_MFP3_PE14MFP_SD1_nCD         /*!< GPE_MFP3 PE14 setting for SD1_nCD*/
#define SPI0_CLK_PD2             SYS_GPD_MFP0_PD2MFP_SPI0_CLK         /*!< GPD_MFP0 PD2 setting for SPI0_CLK*/
#define SPI0_CLK_PF8             SYS_GPF_MFP2_PF8MFP_SPI0_CLK         /*!< GPF_MFP2 PF8 setting for SPI0_CLK*/
#define SPI0_CLK_PA2             SYS_GPA_MFP0_PA2MFP_SPI0_CLK         /*!< GPA_MFP0 PA2 setting for SPI0_CLK*/
#define SPI0_CLK_PB14            SYS_GPB_MFP3_PB14MFP_SPI0_CLK        /*!< GPB_MFP3 PB14 setting for SPI0_CLK*/
#define SPI0_CLK_PA13            SYS_GPA_MFP3_PA13MFP_SPI0_CLK        /*!< GPA_MFP3 PA13 setting for SPI0_CLK*/
#define SPI0_I2SMCLK_PF10        SYS_GPF_MFP2_PF10MFP_SPI0_I2SMCLK    /*!< GPF_MFP2 PF10 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PD13        SYS_GPD_MFP3_PD13MFP_SPI0_I2SMCLK    /*!< GPD_MFP3 PD13 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PB0         SYS_GPB_MFP0_PB0MFP_SPI0_I2SMCLK     /*!< GPB_MFP0 PB0 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PD14        SYS_GPD_MFP3_PD14MFP_SPI0_I2SMCLK    /*!< GPD_MFP3 PD14 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PA4         SYS_GPA_MFP1_PA4MFP_SPI0_I2SMCLK     /*!< GPA_MFP1 PA4 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PC14        SYS_GPC_MFP3_PC14MFP_SPI0_I2SMCLK    /*!< GPC_MFP3 PC14 setting for SPI0_I2SMCLK*/
#define SPI0_I2SMCLK_PB11        SYS_GPB_MFP2_PB11MFP_SPI0_I2SMCLK    /*!< GPB_MFP2 PB11 setting for SPI0_I2SMCLK*/
#define SPI0_MISO_PD1            SYS_GPD_MFP0_PD1MFP_SPI0_MISO        /*!< GPD_MFP0 PD1 setting for SPI0_MISO*/
#define SPI0_MISO_PB13           SYS_GPB_MFP3_PB13MFP_SPI0_MISO       /*!< GPB_MFP3 PB13 setting for SPI0_MISO*/
#define SPI0_MISO_PF7            SYS_GPF_MFP1_PF7MFP_SPI0_MISO        /*!< GPF_MFP1 PF7 setting for SPI0_MISO*/
#define SPI0_MISO_PA1            SYS_GPA_MFP0_PA1MFP_SPI0_MISO        /*!< GPA_MFP0 PA1 setting for SPI0_MISO*/
#define SPI0_MISO_PA14           SYS_GPA_MFP3_PA14MFP_SPI0_MISO       /*!< GPA_MFP3 PA14 setting for SPI0_MISO*/
#define SPI0_MOSI_PD0            SYS_GPD_MFP0_PD0MFP_SPI0_MOSI        /*!< GPD_MFP0 PD0 setting for SPI0_MOSI*/
#define SPI0_MOSI_PB12           SYS_GPB_MFP3_PB12MFP_SPI0_MOSI       /*!< GPB_MFP3 PB12 setting for SPI0_MOSI*/
#define SPI0_MOSI_PF6            SYS_GPF_MFP1_PF6MFP_SPI0_MOSI        /*!< GPF_MFP1 PF6 setting for SPI0_MOSI*/
#define SPI0_MOSI_PA0            SYS_GPA_MFP0_PA0MFP_SPI0_MOSI        /*!< GPA_MFP0 PA0 setting for SPI0_MOSI*/
#define SPI0_MOSI_PA15           SYS_GPA_MFP3_PA15MFP_SPI0_MOSI       /*!< GPA_MFP3 PA15 setting for SPI0_MOSI*/
#define SPI0_SS_PD3              SYS_GPD_MFP0_PD3MFP_SPI0_SS          /*!< GPD_MFP0 PD3 setting for SPI0_SS*/
#define SPI0_SS_PF9              SYS_GPF_MFP2_PF9MFP_SPI0_SS          /*!< GPF_MFP2 PF9 setting for SPI0_SS*/
#define SPI0_SS_PB15             SYS_GPB_MFP3_PB15MFP_SPI0_SS         /*!< GPB_MFP3 PB15 setting for SPI0_SS*/
#define SPI0_SS_PA3              SYS_GPA_MFP0_PA3MFP_SPI0_SS          /*!< GPA_MFP0 PA3 setting for SPI0_SS*/
#define SPI0_SS_PA12             SYS_GPA_MFP3_PA12MFP_SPI0_SS         /*!< GPA_MFP3 PA12 setting for SPI0_SS*/
#define SPI1_CLK_PI9             SYS_GPI_MFP2_PI9MFP_SPI1_CLK         /*!< GPI_MFP2 PI9 setting for SPI1_CLK*/
#define SPI1_CLK_PH8             SYS_GPH_MFP2_PH8MFP_SPI1_CLK         /*!< GPH_MFP2 PH8 setting for SPI1_CLK*/
#define SPI1_CLK_PB3             SYS_GPB_MFP0_PB3MFP_SPI1_CLK         /*!< GPB_MFP0 PB3 setting for SPI1_CLK*/
#define SPI1_CLK_PD5             SYS_GPD_MFP1_PD5MFP_SPI1_CLK         /*!< GPD_MFP1 PD5 setting for SPI1_CLK*/
#define SPI1_CLK_PA7             SYS_GPA_MFP1_PA7MFP_SPI1_CLK         /*!< GPA_MFP1 PA7 setting for SPI1_CLK*/
#define SPI1_CLK_PC1             SYS_GPC_MFP0_PC1MFP_SPI1_CLK         /*!< GPC_MFP0 PC1 setting for SPI1_CLK*/
#define SPI1_CLK_PH6             SYS_GPH_MFP1_PH6MFP_SPI1_CLK         /*!< GPH_MFP1 PH6 setting for SPI1_CLK*/
#define SPI1_CLK_PB7             SYS_GPB_MFP1_PB7MFP_SPI1_CLK         /*!< GPB_MFP1 PB7 setting for SPI1_CLK*/
#define SPI1_I2SMCLK_PC4         SYS_GPC_MFP1_PC4MFP_SPI1_I2SMCLK     /*!< GPC_MFP1 PC4 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PI6         SYS_GPI_MFP1_PI6MFP_SPI1_I2SMCLK     /*!< GPI_MFP1 PI6 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PH10        SYS_GPH_MFP2_PH10MFP_SPI1_I2SMCLK    /*!< GPH_MFP2 PH10 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PA5         SYS_GPA_MFP1_PA5MFP_SPI1_I2SMCLK     /*!< GPA_MFP1 PA5 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PH3         SYS_GPH_MFP0_PH3MFP_SPI1_I2SMCLK     /*!< GPH_MFP0 PH3 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PD13        SYS_GPD_MFP3_PD13MFP_SPI1_I2SMCLK    /*!< GPD_MFP3 PD13 setting for SPI1_I2SMCLK*/
#define SPI1_I2SMCLK_PB1         SYS_GPB_MFP0_PB1MFP_SPI1_I2SMCLK     /*!< GPB_MFP0 PB1 setting for SPI1_I2SMCLK*/
#define SPI1_MISO_PE1            SYS_GPE_MFP0_PE1MFP_SPI1_MISO        /*!< GPE_MFP0 PE1 setting for SPI1_MISO*/
#define SPI1_MISO_PC3            SYS_GPC_MFP0_PC3MFP_SPI1_MISO        /*!< GPC_MFP0 PC3 setting for SPI1_MISO*/
#define SPI1_MISO_PH4            SYS_GPH_MFP1_PH4MFP_SPI1_MISO        /*!< GPH_MFP1 PH4 setting for SPI1_MISO*/
#define SPI1_MISO_PC7            SYS_GPC_MFP1_PC7MFP_SPI1_MISO        /*!< GPC_MFP1 PC7 setting for SPI1_MISO*/
#define SPI1_MISO_PB5            SYS_GPB_MFP1_PB5MFP_SPI1_MISO        /*!< GPB_MFP1 PB5 setting for SPI1_MISO*/
#define SPI1_MISO_PI7            SYS_GPI_MFP1_PI7MFP_SPI1_MISO        /*!< GPI_MFP1 PI7 setting for SPI1_MISO*/
#define SPI1_MISO_PD7            SYS_GPD_MFP1_PD7MFP_SPI1_MISO        /*!< GPD_MFP1 PD7 setting for SPI1_MISO*/
#define SPI1_MOSI_PD6            SYS_GPD_MFP1_PD6MFP_SPI1_MOSI        /*!< GPD_MFP1 PD6 setting for SPI1_MOSI*/
#define SPI1_MOSI_PH5            SYS_GPH_MFP1_PH5MFP_SPI1_MOSI        /*!< GPH_MFP1 PH5 setting for SPI1_MOSI*/
#define SPI1_MOSI_PI8            SYS_GPI_MFP2_PI8MFP_SPI1_MOSI        /*!< GPI_MFP2 PI8 setting for SPI1_MOSI*/
#define SPI1_MOSI_PE0            SYS_GPE_MFP0_PE0MFP_SPI1_MOSI        /*!< GPE_MFP0 PE0 setting for SPI1_MOSI*/
#define SPI1_MOSI_PC2            SYS_GPC_MFP0_PC2MFP_SPI1_MOSI        /*!< GPC_MFP0 PC2 setting for SPI1_MOSI*/
#define SPI1_MOSI_PC6            SYS_GPC_MFP1_PC6MFP_SPI1_MOSI        /*!< GPC_MFP1 PC6 setting for SPI1_MOSI*/
#define SPI1_MOSI_PB4            SYS_GPB_MFP1_PB4MFP_SPI1_MOSI        /*!< GPB_MFP1 PB4 setting for SPI1_MOSI*/
#define SPI1_SS_PA6              SYS_GPA_MFP1_PA6MFP_SPI1_SS          /*!< GPA_MFP1 PA6 setting for SPI1_SS*/
#define SPI1_SS_PH9              SYS_GPH_MFP2_PH9MFP_SPI1_SS          /*!< GPH_MFP2 PH9 setting for SPI1_SS*/
#define SPI1_SS_PC0              SYS_GPC_MFP0_PC0MFP_SPI1_SS          /*!< GPC_MFP0 PC0 setting for SPI1_SS*/
#define SPI1_SS_PB2              SYS_GPB_MFP0_PB2MFP_SPI1_SS          /*!< GPB_MFP0 PB2 setting for SPI1_SS*/
#define SPI1_SS_PI10             SYS_GPI_MFP2_PI10MFP_SPI1_SS         /*!< GPI_MFP2 PI10 setting for SPI1_SS*/
#define SPI1_SS_PD4              SYS_GPD_MFP1_PD4MFP_SPI1_SS          /*!< GPD_MFP1 PD4 setting for SPI1_SS*/
#define SPI1_SS_PH7              SYS_GPH_MFP1_PH7MFP_SPI1_SS          /*!< GPH_MFP1 PH7 setting for SPI1_SS*/
#define SPI2_CLK_PE8             SYS_GPE_MFP2_PE8MFP_SPI2_CLK         /*!< GPE_MFP2 PE8 setting for SPI2_CLK*/
#define SPI2_CLK_PA10            SYS_GPA_MFP2_PA10MFP_SPI2_CLK        /*!< GPA_MFP2 PA10 setting for SPI2_CLK*/
#define SPI2_CLK_PA13            SYS_GPA_MFP3_PA13MFP_SPI2_CLK        /*!< GPA_MFP3 PA13 setting for SPI2_CLK*/
#define SPI2_CLK_PG3             SYS_GPG_MFP0_PG3MFP_SPI2_CLK         /*!< GPG_MFP0 PG3 setting for SPI2_CLK*/
#define SPI2_I2SMCLK_PG1         SYS_GPG_MFP0_PG1MFP_SPI2_I2SMCLK     /*!< GPG_MFP0 PG1 setting for SPI2_I2SMCLK*/
#define SPI2_I2SMCLK_PC13        SYS_GPC_MFP3_PC13MFP_SPI2_I2SMCLK    /*!< GPC_MFP3 PC13 setting for SPI2_I2SMCLK*/
#define SPI2_I2SMCLK_PB0         SYS_GPB_MFP0_PB0MFP_SPI2_I2SMCLK     /*!< GPB_MFP0 PB0 setting for SPI2_I2SMCLK*/
#define SPI2_I2SMCLK_PE12        SYS_GPE_MFP3_PE12MFP_SPI2_I2SMCLK    /*!< GPE_MFP3 PE12 setting for SPI2_I2SMCLK*/
#define SPI2_MISO_PG4            SYS_GPG_MFP1_PG4MFP_SPI2_MISO        /*!< GPG_MFP1 PG4 setting for SPI2_MISO*/
#define SPI2_MISO_PE9            SYS_GPE_MFP2_PE9MFP_SPI2_MISO        /*!< GPE_MFP2 PE9 setting for SPI2_MISO*/
#define SPI2_MISO_PA9            SYS_GPA_MFP2_PA9MFP_SPI2_MISO        /*!< GPA_MFP2 PA9 setting for SPI2_MISO*/
#define SPI2_MISO_PA14           SYS_GPA_MFP3_PA14MFP_SPI2_MISO       /*!< GPA_MFP3 PA14 setting for SPI2_MISO*/
#define SPI2_MOSI_PA8            SYS_GPA_MFP2_PA8MFP_SPI2_MOSI        /*!< GPA_MFP2 PA8 setting for SPI2_MOSI*/
#define SPI2_MOSI_PA15           SYS_GPA_MFP3_PA15MFP_SPI2_MOSI       /*!< GPA_MFP3 PA15 setting for SPI2_MOSI*/
#define SPI2_MOSI_PF11           SYS_GPF_MFP2_PF11MFP_SPI2_MOSI       /*!< GPF_MFP2 PF11 setting for SPI2_MOSI*/
#define SPI2_MOSI_PE10           SYS_GPE_MFP2_PE10MFP_SPI2_MOSI       /*!< GPE_MFP2 PE10 setting for SPI2_MOSI*/
#define SPI2_SS_PG2              SYS_GPG_MFP0_PG2MFP_SPI2_SS          /*!< GPG_MFP0 PG2 setting for SPI2_SS*/
#define SPI2_SS_PA11             SYS_GPA_MFP2_PA11MFP_SPI2_SS         /*!< GPA_MFP2 PA11 setting for SPI2_SS*/
#define SPI2_SS_PA12             SYS_GPA_MFP3_PA12MFP_SPI2_SS         /*!< GPA_MFP3 PA12 setting for SPI2_SS*/
#define SPI2_SS_PE11             SYS_GPE_MFP2_PE11MFP_SPI2_SS         /*!< GPE_MFP2 PE11 setting for SPI2_SS*/
#define SPI3_CLK_PC10            SYS_GPC_MFP2_PC10MFP_SPI3_CLK        /*!< GPC_MFP2 PC10 setting for SPI3_CLK*/
#define SPI3_CLK_PB11            SYS_GPB_MFP2_PB11MFP_SPI3_CLK        /*!< GPB_MFP2 PB11 setting for SPI3_CLK*/
#define SPI3_CLK_PE4             SYS_GPE_MFP1_PE4MFP_SPI3_CLK         /*!< GPE_MFP1 PE4 setting for SPI3_CLK*/
#define SPI3_CLK_PG6             SYS_GPG_MFP1_PG6MFP_SPI3_CLK         /*!< GPG_MFP1 PG6 setting for SPI3_CLK*/
#define SPI3_CLK_PB13            SYS_GPB_MFP3_PB13MFP_SPI3_CLK        /*!< GPB_MFP3 PB13 setting for SPI3_CLK*/
#define SPI3_I2SMCLK_PF6         SYS_GPF_MFP1_PF6MFP_SPI3_I2SMCLK     /*!< GPF_MFP1 PF6 setting for SPI3_I2SMCLK*/
#define SPI3_I2SMCLK_PB1         SYS_GPB_MFP0_PB1MFP_SPI3_I2SMCLK     /*!< GPB_MFP0 PB1 setting for SPI3_I2SMCLK*/
#define SPI3_I2SMCLK_PD14        SYS_GPD_MFP3_PD14MFP_SPI3_I2SMCLK    /*!< GPD_MFP3 PD14 setting for SPI3_I2SMCLK*/
#define SPI3_I2SMCLK_PE6         SYS_GPE_MFP1_PE6MFP_SPI3_I2SMCLK     /*!< GPE_MFP1 PE6 setting for SPI3_I2SMCLK*/
#define SPI3_MISO_PG7            SYS_GPG_MFP1_PG7MFP_SPI3_MISO        /*!< GPG_MFP1 PG7 setting for SPI3_MISO*/
#define SPI3_MISO_PB9            SYS_GPB_MFP2_PB9MFP_SPI3_MISO        /*!< GPB_MFP2 PB9 setting for SPI3_MISO*/
#define SPI3_MISO_PC12           SYS_GPC_MFP3_PC12MFP_SPI3_MISO       /*!< GPC_MFP3 PC12 setting for SPI3_MISO*/
#define SPI3_MISO_PE3            SYS_GPE_MFP0_PE3MFP_SPI3_MISO        /*!< GPE_MFP0 PE3 setting for SPI3_MISO*/
#define SPI3_MISO_PB7            SYS_GPB_MFP1_PB7MFP_SPI3_MISO        /*!< GPB_MFP1 PB7 setting for SPI3_MISO*/
#define SPI3_MOSI_PB8            SYS_GPB_MFP2_PB8MFP_SPI3_MOSI        /*!< GPB_MFP2 PB8 setting for SPI3_MOSI*/
#define SPI3_MOSI_PG8            SYS_GPG_MFP2_PG8MFP_SPI3_MOSI        /*!< GPG_MFP2 PG8 setting for SPI3_MOSI*/
#define SPI3_MOSI_PC11           SYS_GPC_MFP2_PC11MFP_SPI3_MOSI       /*!< GPC_MFP2 PC11 setting for SPI3_MOSI*/
#define SPI3_MOSI_PE2            SYS_GPE_MFP0_PE2MFP_SPI3_MOSI        /*!< GPE_MFP0 PE2 setting for SPI3_MOSI*/
#define SPI3_MOSI_PB6            SYS_GPB_MFP1_PB6MFP_SPI3_MOSI        /*!< GPB_MFP1 PB6 setting for SPI3_MOSI*/
#define SPI3_SS_PE5              SYS_GPE_MFP1_PE5MFP_SPI3_SS          /*!< GPE_MFP1 PE5 setting for SPI3_SS*/
#define SPI3_SS_PB10             SYS_GPB_MFP2_PB10MFP_SPI3_SS         /*!< GPB_MFP2 PB10 setting for SPI3_SS*/
#define SPI3_SS_PC9              SYS_GPC_MFP2_PC9MFP_SPI3_SS          /*!< GPC_MFP2 PC9 setting for SPI3_SS*/
#define SPI3_SS_PG5              SYS_GPG_MFP1_PG5MFP_SPI3_SS          /*!< GPG_MFP1 PG5 setting for SPI3_SS*/
#define SPI3_SS_PB12             SYS_GPB_MFP3_PB12MFP_SPI3_SS         /*!< GPB_MFP3 PB12 setting for SPI3_SS*/
#define SPI4_CLK_PB2             SYS_GPB_MFP0_PB2MFP_SPI4_CLK         /*!< GPB_MFP0 PB2 setting for SPI4_CLK*/
#define SPI4_MISO_PB1            SYS_GPB_MFP0_PB1MFP_SPI4_MISO        /*!< GPB_MFP0 PB1 setting for SPI4_MISO*/
#define SPI4_MOSI_PB0            SYS_GPB_MFP0_PB0MFP_SPI4_MOSI        /*!< GPB_MFP0 PB0 setting for SPI4_MOSI*/
#define SPI4_SS_PB3              SYS_GPB_MFP0_PB3MFP_SPI4_SS          /*!< GPB_MFP0 PB3 setting for SPI4_SS*/
#define SPI5_CLK_PF6             SYS_GPF_MFP1_PF6MFP_SPI5_CLK         /*!< GPF_MFP1 PF6 setting for SPI5_CLK*/
#define SPI5_CLK_PA6             SYS_GPA_MFP1_PA6MFP_SPI5_CLK         /*!< GPA_MFP1 PA6 setting for SPI5_CLK*/
#define SPI5_MISO_PF4            SYS_GPF_MFP1_PF4MFP_SPI5_MISO        /*!< GPF_MFP1 PF4 setting for SPI5_MISO*/
#define SPI5_MOSI_PF5            SYS_GPF_MFP1_PF5MFP_SPI5_MOSI        /*!< GPF_MFP1 PF5 setting for SPI5_MOSI*/
#define SPI5_SS_PA7              SYS_GPA_MFP1_PA7MFP_SPI5_SS          /*!< GPA_MFP1 PA7 setting for SPI5_SS*/
#define SPI5_SS_PF7              SYS_GPF_MFP1_PF7MFP_SPI5_SS          /*!< GPF_MFP1 PF7 setting for SPI5_SS*/
#define SPI6_CLK_PA6             SYS_GPA_MFP1_PA6MFP_SPI6_CLK         /*!< GPA_MFP1 PA6 setting for SPI6_CLK*/
#define SPI6_MISO_PC7            SYS_GPC_MFP1_PC7MFP_SPI6_MISO        /*!< GPC_MFP1 PC7 setting for SPI6_MISO*/
#define SPI6_MOSI_PC6            SYS_GPC_MFP1_PC6MFP_SPI6_MOSI        /*!< GPC_MFP1 PC6 setting for SPI6_MOSI*/
#define SPI6_SS_PA7              SYS_GPA_MFP1_PA7MFP_SPI6_SS          /*!< GPA_MFP1 PA7 setting for SPI6_SS*/
#define SPI7_CLK_PC2             SYS_GPC_MFP0_PC2MFP_SPI7_CLK         /*!< GPC_MFP0 PC2 setting for SPI7_CLK*/
#define SPI7_MISO_PC1            SYS_GPC_MFP0_PC1MFP_SPI7_MISO        /*!< GPC_MFP0 PC1 setting for SPI7_MISO*/
#define SPI7_MOSI_PC0            SYS_GPC_MFP0_PC0MFP_SPI7_MOSI        /*!< GPC_MFP0 PC0 setting for SPI7_MOSI*/
#define SPI7_SS_PC3              SYS_GPC_MFP0_PC3MFP_SPI7_SS          /*!< GPC_MFP0 PC3 setting for SPI7_SS*/
#define SPI8_CLK_PG10            SYS_GPG_MFP2_PG10MFP_SPI8_CLK        /*!< GPG_MFP2 PG10 setting for SPI8_CLK*/
#define SPI8_MISO_PG12           SYS_GPG_MFP3_PG12MFP_SPI8_MISO       /*!< GPG_MFP3 PG12 setting for SPI8_MISO*/
#define SPI8_MOSI_PG11           SYS_GPG_MFP2_PG11MFP_SPI8_MOSI       /*!< GPG_MFP2 PG11 setting for SPI8_MOSI*/
#define SPI8_SS_PG9              SYS_GPG_MFP2_PG9MFP_SPI8_SS          /*!< GPG_MFP2 PG9 setting for SPI8_SS*/
#define SPI9_CLK_PB15            SYS_GPB_MFP3_PB15MFP_SPI9_CLK        /*!< GPB_MFP3 PB15 setting for SPI9_CLK*/
#define SPI9_CLK_PD12            SYS_GPD_MFP3_PD12MFP_SPI9_CLK        /*!< GPD_MFP3 PD12 setting for SPI9_CLK*/
#define SPI9_MISO_PB13           SYS_GPB_MFP3_PB13MFP_SPI9_MISO       /*!< GPB_MFP3 PB13 setting for SPI9_MISO*/
#define SPI9_MISO_PD11           SYS_GPD_MFP2_PD11MFP_SPI9_MISO       /*!< GPD_MFP2 PD11 setting for SPI9_MISO*/
#define SPI9_MOSI_PD10           SYS_GPD_MFP2_PD10MFP_SPI9_MOSI       /*!< GPD_MFP2 PD10 setting for SPI9_MOSI*/
#define SPI9_MOSI_PC14           SYS_GPC_MFP3_PC14MFP_SPI9_MOSI       /*!< GPC_MFP3 PC14 setting for SPI9_MOSI*/
#define SPI9_SS_PC13             SYS_GPC_MFP3_PC13MFP_SPI9_SS         /*!< GPC_MFP3 PC13 setting for SPI9_SS*/
#define SPI9_SS_PB14             SYS_GPB_MFP3_PB14MFP_SPI9_SS         /*!< GPB_MFP3 PB14 setting for SPI9_SS*/
#define SPI10_CLK_PA13           SYS_GPA_MFP3_PA13MFP_SPI10_CLK       /*!< GPA_MFP3 PA13 setting for SPI10_CLK*/
#define SPI10_MISO_PA14          SYS_GPA_MFP3_PA14MFP_SPI10_MISO      /*!< GPA_MFP3 PA14 setting for SPI10_MISO*/
#define SPI10_MOSI_PA15          SYS_GPA_MFP3_PA15MFP_SPI10_MOSI      /*!< GPA_MFP3 PA15 setting for SPI10_MOSI*/
#define SPI10_SS_PA12            SYS_GPA_MFP3_PA12MFP_SPI10_SS        /*!< GPA_MFP3 PA12 setting for SPI10_SS*/
#define SPIM_CLK_PE4             SYS_GPE_MFP1_PE4MFP_SPIM_CLK         /*!< GPE_MFP1 PE4 setting for SPIM_CLK*/
#define SPIM_CLK_PJ12            SYS_GPJ_MFP3_PJ12MFP_SPIM_CLK        /*!< GPJ_MFP3 PJ12 setting for SPIM_CLK*/
#define SPIM_CLK_PG12            SYS_GPG_MFP3_PG12MFP_SPIM_CLK        /*!< GPG_MFP3 PG12 setting for SPIM_CLK*/
#define SPIM_CLK_PA2             SYS_GPA_MFP0_PA2MFP_SPIM_CLK         /*!< GPA_MFP0 PA2 setting for SPIM_CLK*/
#define SPIM_CLK_PC2             SYS_GPC_MFP0_PC2MFP_SPIM_CLK         /*!< GPC_MFP0 PC2 setting for SPIM_CLK*/
#define SPIM_CLK_PJ0             SYS_GPJ_MFP0_PJ0MFP_SPIM_CLK         /*!< GPJ_MFP0 PJ0 setting for SPIM_CLK*/
#define SPIM_D2_PJ10             SYS_GPJ_MFP2_PJ10MFP_SPIM_D2         /*!< GPJ_MFP2 PJ10 setting for SPIM_D2*/
#define SPIM_D2_PE7              SYS_GPE_MFP1_PE7MFP_SPIM_D2          /*!< GPE_MFP1 PE7 setting for SPIM_D2*/
#define SPIM_D2_PI14             SYS_GPI_MFP3_PI14MFP_SPIM_D2         /*!< GPI_MFP3 PI14 setting for SPIM_D2*/
#define SPIM_D2_PG9              SYS_GPG_MFP2_PG9MFP_SPIM_D2          /*!< GPG_MFP2 PG9 setting for SPIM_D2*/
#define SPIM_D2_PC5              SYS_GPC_MFP1_PC5MFP_SPIM_D2          /*!< GPC_MFP1 PC5 setting for SPIM_D2*/
#define SPIM_D2_PA5              SYS_GPA_MFP1_PA5MFP_SPIM_D2          /*!< GPA_MFP1 PA5 setting for SPIM_D2*/
#define SPIM_D3_PJ11             SYS_GPJ_MFP2_PJ11MFP_SPIM_D3         /*!< GPJ_MFP2 PJ11 setting for SPIM_D3*/
#define SPIM_D3_PE6              SYS_GPE_MFP1_PE6MFP_SPIM_D3          /*!< GPE_MFP1 PE6 setting for SPIM_D3*/
#define SPIM_D3_PC4              SYS_GPC_MFP1_PC4MFP_SPIM_D3          /*!< GPC_MFP1 PC4 setting for SPIM_D3*/
#define SPIM_D3_PG10             SYS_GPG_MFP2_PG10MFP_SPIM_D3         /*!< GPG_MFP2 PG10 setting for SPIM_D3*/
#define SPIM_D3_PI15             SYS_GPI_MFP3_PI15MFP_SPIM_D3         /*!< GPI_MFP3 PI15 setting for SPIM_D3*/
#define SPIM_D3_PA4              SYS_GPA_MFP1_PA4MFP_SPIM_D3          /*!< GPA_MFP1 PA4 setting for SPIM_D3*/
#define SPIM_MISO_PJ9            SYS_GPJ_MFP2_PJ9MFP_SPIM_MISO        /*!< GPJ_MFP2 PJ9 setting for SPIM_MISO*/
#define SPIM_MISO_PG13           SYS_GPG_MFP3_PG13MFP_SPIM_MISO       /*!< GPG_MFP3 PG13 setting for SPIM_MISO*/
#define SPIM_MISO_PE3            SYS_GPE_MFP0_PE3MFP_SPIM_MISO        /*!< GPE_MFP0 PE3 setting for SPIM_MISO*/
#define SPIM_MISO_PC1            SYS_GPC_MFP0_PC1MFP_SPIM_MISO        /*!< GPC_MFP0 PC1 setting for SPIM_MISO*/
#define SPIM_MISO_PA1            SYS_GPA_MFP0_PA1MFP_SPIM_MISO        /*!< GPA_MFP0 PA1 setting for SPIM_MISO*/
#define SPIM_MISO_PI13           SYS_GPI_MFP3_PI13MFP_SPIM_MISO       /*!< GPI_MFP3 PI13 setting for SPIM_MISO*/
#define SPIM_MOSI_PA0            SYS_GPA_MFP0_PA0MFP_SPIM_MOSI        /*!< GPA_MFP0 PA0 setting for SPIM_MOSI*/
#define SPIM_MOSI_PG14           SYS_GPG_MFP3_PG14MFP_SPIM_MOSI       /*!< GPG_MFP3 PG14 setting for SPIM_MOSI*/
#define SPIM_MOSI_PJ13           SYS_GPJ_MFP3_PJ13MFP_SPIM_MOSI       /*!< GPJ_MFP3 PJ13 setting for SPIM_MOSI*/
#define SPIM_MOSI_PC0            SYS_GPC_MFP0_PC0MFP_SPIM_MOSI        /*!< GPC_MFP0 PC0 setting for SPIM_MOSI*/
#define SPIM_MOSI_PA15           SYS_GPA_MFP3_PA15MFP_SPIM_MOSI       /*!< GPA_MFP3 PA15 setting for SPIM_MOSI*/
#define SPIM_MOSI_PJ1            SYS_GPJ_MFP0_PJ1MFP_SPIM_MOSI        /*!< GPJ_MFP0 PJ1 setting for SPIM_MOSI*/
#define SPIM_MOSI_PE2            SYS_GPE_MFP0_PE2MFP_SPIM_MOSI        /*!< GPE_MFP0 PE2 setting for SPIM_MOSI*/
#define SPIM_SS_PJ8              SYS_GPJ_MFP2_PJ8MFP_SPIM_SS          /*!< GPJ_MFP2 PJ8 setting for SPIM_SS*/
#define SPIM_SS_PG11             SYS_GPG_MFP2_PG11MFP_SPIM_SS         /*!< GPG_MFP2 PG11 setting for SPIM_SS*/
#define SPIM_SS_PC3              SYS_GPC_MFP0_PC3MFP_SPIM_SS          /*!< GPC_MFP0 PC3 setting for SPIM_SS*/
#define SPIM_SS_PI12             SYS_GPI_MFP3_PI12MFP_SPIM_SS         /*!< GPI_MFP3 PI12 setting for SPIM_SS*/
#define SPIM_SS_PA3              SYS_GPA_MFP0_PA3MFP_SPIM_SS          /*!< GPA_MFP0 PA3 setting for SPIM_SS*/
#define SPIM_SS_PE5              SYS_GPE_MFP1_PE5MFP_SPIM_SS          /*!< GPE_MFP1 PE5 setting for SPIM_SS*/
#define SWDH_CLK_PA10            SYS_GPA_MFP2_PA10MFP_SWDH_CLK        /*!< GPA_MFP2 PA10 setting for SWDH_CLK*/
#define SWDH_DAT_PA9             SYS_GPA_MFP2_PA9MFP_SWDH_DAT         /*!< GPA_MFP2 PA9 setting for SWDH_DAT*/
#define TAMPER0_PF6              SYS_GPF_MFP1_PF6MFP_TAMPER0          /*!< GPF_MFP1 PF6 setting for TAMPER0*/
#define TAMPER1_PF7              SYS_GPF_MFP1_PF7MFP_TAMPER1          /*!< GPF_MFP1 PF7 setting for TAMPER1*/
#define TAMPER2_PF8              SYS_GPF_MFP2_PF8MFP_TAMPER2          /*!< GPF_MFP2 PF8 setting for TAMPER2*/
#define TAMPER3_PF9              SYS_GPF_MFP2_PF9MFP_TAMPER3          /*!< GPF_MFP2 PF9 setting for TAMPER3*/
#define TAMPER4_PF10             SYS_GPF_MFP2_PF10MFP_TAMPER4         /*!< GPF_MFP2 PF10 setting for TAMPER4*/
#define TAMPER5_PF11             SYS_GPF_MFP2_PF11MFP_TAMPER5         /*!< GPF_MFP2 PF11 setting for TAMPER5*/
#define TM0_PC7                  SYS_GPC_MFP1_PC7MFP_TM0              /*!< GPC_MFP1 PC7 setting for TM0*/
#define TM0_PB5                  SYS_GPB_MFP1_PB5MFP_TM0              /*!< GPB_MFP1 PB5 setting for TM0*/
#define TM0_PG2                  SYS_GPG_MFP0_PG2MFP_TM0              /*!< GPG_MFP0 PG2 setting for TM0*/
#define TM0_EXT_PA11             SYS_GPA_MFP2_PA11MFP_TM0_EXT         /*!< GPA_MFP2 PA11 setting for TM0_EXT*/
#define TM0_EXT_PH0              SYS_GPH_MFP0_PH0MFP_TM0_EXT          /*!< GPH_MFP0 PH0 setting for TM0_EXT*/
#define TM0_EXT_PB15             SYS_GPB_MFP3_PB15MFP_TM0_EXT         /*!< GPB_MFP3 PB15 setting for TM0_EXT*/
#define TM1_PC6                  SYS_GPC_MFP1_PC6MFP_TM1              /*!< GPC_MFP1 PC6 setting for TM1*/
#define TM1_PB4                  SYS_GPB_MFP1_PB4MFP_TM1              /*!< GPB_MFP1 PB4 setting for TM1*/
#define TM1_PC14                 SYS_GPC_MFP3_PC14MFP_TM1             /*!< GPC_MFP3 PC14 setting for TM1*/
#define TM1_PG3                  SYS_GPG_MFP0_PG3MFP_TM1              /*!< GPG_MFP0 PG3 setting for TM1*/
#define TM1_EXT_PA10             SYS_GPA_MFP2_PA10MFP_TM1_EXT         /*!< GPA_MFP2 PA10 setting for TM1_EXT*/
#define TM1_EXT_PB14             SYS_GPB_MFP3_PB14MFP_TM1_EXT         /*!< GPB_MFP3 PB14 setting for TM1_EXT*/
#define TM1_EXT_PH1              SYS_GPH_MFP0_PH1MFP_TM1_EXT          /*!< GPH_MFP0 PH1 setting for TM1_EXT*/
#define TM2_PB3                  SYS_GPB_MFP0_PB3MFP_TM2              /*!< GPB_MFP0 PB3 setting for TM2*/
#define TM2_PG4                  SYS_GPG_MFP1_PG4MFP_TM2              /*!< GPG_MFP1 PG4 setting for TM2*/
#define TM2_PD0                  SYS_GPD_MFP0_PD0MFP_TM2              /*!< GPD_MFP0 PD0 setting for TM2*/
#define TM2_PA7                  SYS_GPA_MFP1_PA7MFP_TM2              /*!< GPA_MFP1 PA7 setting for TM2*/
#define TM2_EXT_PB13             SYS_GPB_MFP3_PB13MFP_TM2_EXT         /*!< GPB_MFP3 PB13 setting for TM2_EXT*/
#define TM2_EXT_PH2              SYS_GPH_MFP0_PH2MFP_TM2_EXT          /*!< GPH_MFP0 PH2 setting for TM2_EXT*/
#define TM2_EXT_PA9              SYS_GPA_MFP2_PA9MFP_TM2_EXT          /*!< GPA_MFP2 PA9 setting for TM2_EXT*/
#define TM3_PF11                 SYS_GPF_MFP2_PF11MFP_TM3             /*!< GPF_MFP2 PF11 setting for TM3*/
#define TM3_PA6                  SYS_GPA_MFP1_PA6MFP_TM3              /*!< GPA_MFP1 PA6 setting for TM3*/
#define TM3_PB2                  SYS_GPB_MFP0_PB2MFP_TM3              /*!< GPB_MFP0 PB2 setting for TM3*/
#define TM3_EXT_PA8              SYS_GPA_MFP2_PA8MFP_TM3_EXT          /*!< GPA_MFP2 PA8 setting for TM3_EXT*/
#define TM3_EXT_PH3              SYS_GPH_MFP0_PH3MFP_TM3_EXT          /*!< GPH_MFP0 PH3 setting for TM3_EXT*/
#define TM3_EXT_PB12             SYS_GPB_MFP3_PB12MFP_TM3_EXT         /*!< GPB_MFP3 PB12 setting for TM3_EXT*/
#define TRACE_CLK_PE12           SYS_GPE_MFP3_PE12MFP_TRACE_CLK       /*!< GPE_MFP3 PE12 setting for TRACE_CLK*/
#define TRACE_DATA0_PE11         SYS_GPE_MFP2_PE11MFP_TRACE_DATA0     /*!< GPE_MFP2 PE11 setting for TRACE_DATA0*/
#define TRACE_DATA1_PE10         SYS_GPE_MFP2_PE10MFP_TRACE_DATA1     /*!< GPE_MFP2 PE10 setting for TRACE_DATA1*/
#define TRACE_DATA2_PE9          SYS_GPE_MFP2_PE9MFP_TRACE_DATA2      /*!< GPE_MFP2 PE9 setting for TRACE_DATA2*/
#define TRACE_DATA3_PE8          SYS_GPE_MFP2_PE8MFP_TRACE_DATA3      /*!< GPE_MFP2 PE8 setting for TRACE_DATA3*/
#define UART0_RXD_PA0            SYS_GPA_MFP0_PA0MFP_UART0_RXD        /*!< GPA_MFP0 PA0 setting for UART0_RXD*/
#define UART0_RXD_PC11           SYS_GPC_MFP2_PC11MFP_UART0_RXD       /*!< GPC_MFP2 PC11 setting for UART0_RXD*/
#define UART0_RXD_PH11           SYS_GPH_MFP2_PH11MFP_UART0_RXD       /*!< GPH_MFP2 PH11 setting for UART0_RXD*/
#define UART0_RXD_PA4            SYS_GPA_MFP1_PA4MFP_UART0_RXD        /*!< GPA_MFP1 PA4 setting for UART0_RXD*/
#define UART0_RXD_PA6            SYS_GPA_MFP1_PA6MFP_UART0_RXD        /*!< GPA_MFP1 PA6 setting for UART0_RXD*/
#define UART0_RXD_PD2            SYS_GPD_MFP0_PD2MFP_UART0_RXD        /*!< GPD_MFP0 PD2 setting for UART0_RXD*/
#define UART0_RXD_PB8            SYS_GPB_MFP2_PB8MFP_UART0_RXD        /*!< GPB_MFP2 PB8 setting for UART0_RXD*/
#define UART0_RXD_PF1            SYS_GPF_MFP0_PF1MFP_UART0_RXD        /*!< GPF_MFP0 PF1 setting for UART0_RXD*/
#define UART0_RXD_PA15           SYS_GPA_MFP3_PA15MFP_UART0_RXD       /*!< GPA_MFP3 PA15 setting for UART0_RXD*/
#define UART0_RXD_PF2            SYS_GPF_MFP0_PF2MFP_UART0_RXD        /*!< GPF_MFP0 PF2 setting for UART0_RXD*/
#define UART0_RXD_PB12           SYS_GPB_MFP3_PB12MFP_UART0_RXD       /*!< GPB_MFP3 PB12 setting for UART0_RXD*/
#define UART0_TXD_PD3            SYS_GPD_MFP0_PD3MFP_UART0_TXD        /*!< GPD_MFP0 PD3 setting for UART0_TXD*/
#define UART0_TXD_PA5            SYS_GPA_MFP1_PA5MFP_UART0_TXD        /*!< GPA_MFP1 PA5 setting for UART0_TXD*/
#define UART0_TXD_PF0            SYS_GPF_MFP0_PF0MFP_UART0_TXD        /*!< GPF_MFP0 PF0 setting for UART0_TXD*/
#define UART0_TXD_PB9            SYS_GPB_MFP2_PB9MFP_UART0_TXD        /*!< GPB_MFP2 PB9 setting for UART0_TXD*/
#define UART0_TXD_PF3            SYS_GPF_MFP0_PF3MFP_UART0_TXD        /*!< GPF_MFP0 PF3 setting for UART0_TXD*/
#define UART0_TXD_PA1            SYS_GPA_MFP0_PA1MFP_UART0_TXD        /*!< GPA_MFP0 PA1 setting for UART0_TXD*/
#define UART0_TXD_PA7            SYS_GPA_MFP1_PA7MFP_UART0_TXD        /*!< GPA_MFP1 PA7 setting for UART0_TXD*/
#define UART0_TXD_PA14           SYS_GPA_MFP3_PA14MFP_UART0_TXD       /*!< GPA_MFP3 PA14 setting for UART0_TXD*/
#define UART0_TXD_PC12           SYS_GPC_MFP3_PC12MFP_UART0_TXD       /*!< GPC_MFP3 PC12 setting for UART0_TXD*/
#define UART0_TXD_PB13           SYS_GPB_MFP3_PB13MFP_UART0_TXD       /*!< GPB_MFP3 PB13 setting for UART0_TXD*/
#define UART0_TXD_PH10           SYS_GPH_MFP2_PH10MFP_UART0_TXD       /*!< GPH_MFP2 PH10 setting for UART0_TXD*/
#define UART0_nCTS_PC7           SYS_GPC_MFP1_PC7MFP_UART0_nCTS       /*!< GPC_MFP1 PC7 setting for UART0_nCTS*/
#define UART0_nCTS_PB15          SYS_GPB_MFP3_PB15MFP_UART0_nCTS      /*!< GPB_MFP3 PB15 setting for UART0_nCTS*/
#define UART0_nCTS_PA5           SYS_GPA_MFP1_PA5MFP_UART0_nCTS       /*!< GPA_MFP1 PA5 setting for UART0_nCTS*/
#define UART0_nCTS_PB11          SYS_GPB_MFP2_PB11MFP_UART0_nCTS      /*!< GPB_MFP2 PB11 setting for UART0_nCTS*/
#define UART0_nRTS_PA4           SYS_GPA_MFP1_PA4MFP_UART0_nRTS       /*!< GPA_MFP1 PA4 setting for UART0_nRTS*/
#define UART0_nRTS_PB14          SYS_GPB_MFP3_PB14MFP_UART0_nRTS      /*!< GPB_MFP3 PB14 setting for UART0_nRTS*/
#define UART0_nRTS_PB10          SYS_GPB_MFP2_PB10MFP_UART0_nRTS      /*!< GPB_MFP2 PB10 setting for UART0_nRTS*/
#define UART0_nRTS_PC6           SYS_GPC_MFP1_PC6MFP_UART0_nRTS       /*!< GPC_MFP1 PC6 setting for UART0_nRTS*/
#define UART1_RXD_PH9            SYS_GPH_MFP2_PH9MFP_UART1_RXD        /*!< GPH_MFP2 PH9 setting for UART1_RXD*/
#define UART1_RXD_PD6            SYS_GPD_MFP1_PD6MFP_UART1_RXD        /*!< GPD_MFP1 PD6 setting for UART1_RXD*/
#define UART1_RXD_PF1            SYS_GPF_MFP0_PF1MFP_UART1_RXD        /*!< GPF_MFP0 PF1 setting for UART1_RXD*/
#define UART1_RXD_PA2            SYS_GPA_MFP0_PA2MFP_UART1_RXD        /*!< GPA_MFP0 PA2 setting for UART1_RXD*/
#define UART1_RXD_PC8            SYS_GPC_MFP2_PC8MFP_UART1_RXD        /*!< GPC_MFP2 PC8 setting for UART1_RXD*/
#define UART1_RXD_PB2            SYS_GPB_MFP0_PB2MFP_UART1_RXD        /*!< GPB_MFP0 PB2 setting for UART1_RXD*/
#define UART1_RXD_PD10           SYS_GPD_MFP2_PD10MFP_UART1_RXD       /*!< GPD_MFP2 PD10 setting for UART1_RXD*/
#define UART1_RXD_PG1            SYS_GPG_MFP0_PG1MFP_UART1_RXD        /*!< GPG_MFP0 PG1 setting for UART1_RXD*/
#define UART1_RXD_PB6            SYS_GPB_MFP1_PB6MFP_UART1_RXD        /*!< GPB_MFP1 PB6 setting for UART1_RXD*/
#define UART1_RXD_PA8            SYS_GPA_MFP2_PA8MFP_UART1_RXD        /*!< GPA_MFP2 PA8 setting for UART1_RXD*/
#define UART1_TXD_PA3            SYS_GPA_MFP0_PA3MFP_UART1_TXD        /*!< GPA_MFP0 PA3 setting for UART1_TXD*/
#define UART1_TXD_PD11           SYS_GPD_MFP2_PD11MFP_UART1_TXD       /*!< GPD_MFP2 PD11 setting for UART1_TXD*/
#define UART1_TXD_PH8            SYS_GPH_MFP2_PH8MFP_UART1_TXD        /*!< GPH_MFP2 PH8 setting for UART1_TXD*/
#define UART1_TXD_PB3            SYS_GPB_MFP0_PB3MFP_UART1_TXD        /*!< GPB_MFP0 PB3 setting for UART1_TXD*/
#define UART1_TXD_PB7            SYS_GPB_MFP1_PB7MFP_UART1_TXD        /*!< GPB_MFP1 PB7 setting for UART1_TXD*/
#define UART1_TXD_PA9            SYS_GPA_MFP2_PA9MFP_UART1_TXD        /*!< GPA_MFP2 PA9 setting for UART1_TXD*/
#define UART1_TXD_PF0            SYS_GPF_MFP0_PF0MFP_UART1_TXD        /*!< GPF_MFP0 PF0 setting for UART1_TXD*/
#define UART1_TXD_PE13           SYS_GPE_MFP3_PE13MFP_UART1_TXD       /*!< GPE_MFP3 PE13 setting for UART1_TXD*/
#define UART1_TXD_PD7            SYS_GPD_MFP1_PD7MFP_UART1_TXD        /*!< GPD_MFP1 PD7 setting for UART1_TXD*/
#define UART1_TXD_PG0            SYS_GPG_MFP0_PG0MFP_UART1_TXD        /*!< GPG_MFP0 PG0 setting for UART1_TXD*/
#define UART1_nCTS_PE11          SYS_GPE_MFP2_PE11MFP_UART1_nCTS      /*!< GPE_MFP2 PE11 setting for UART1_nCTS*/
#define UART1_nCTS_PB9           SYS_GPB_MFP2_PB9MFP_UART1_nCTS       /*!< GPB_MFP2 PB9 setting for UART1_nCTS*/
#define UART1_nCTS_PA1           SYS_GPA_MFP0_PA1MFP_UART1_nCTS       /*!< GPA_MFP0 PA1 setting for UART1_nCTS*/
#define UART1_nRTS_PE12          SYS_GPE_MFP3_PE12MFP_UART1_nRTS      /*!< GPE_MFP3 PE12 setting for UART1_nRTS*/
#define UART1_nRTS_PA0           SYS_GPA_MFP0_PA0MFP_UART1_nRTS       /*!< GPA_MFP0 PA0 setting for UART1_nRTS*/
#define UART1_nRTS_PB8           SYS_GPB_MFP2_PB8MFP_UART1_nRTS       /*!< GPB_MFP2 PB8 setting for UART1_nRTS*/
#define UART2_RXD_PC0            SYS_GPC_MFP0_PC0MFP_UART2_RXD        /*!< GPC_MFP0 PC0 setting for UART2_RXD*/
#define UART2_RXD_PE9            SYS_GPE_MFP2_PE9MFP_UART2_RXD        /*!< GPE_MFP2 PE9 setting for UART2_RXD*/
#define UART2_RXD_PB0            SYS_GPB_MFP0_PB0MFP_UART2_RXD        /*!< GPB_MFP0 PB0 setting for UART2_RXD*/
#define UART2_RXD_PF1            SYS_GPF_MFP0_PF1MFP_UART2_RXD        /*!< GPF_MFP0 PF1 setting for UART2_RXD*/
#define UART2_RXD_PI7            SYS_GPI_MFP1_PI7MFP_UART2_RXD        /*!< GPI_MFP1 PI7 setting for UART2_RXD*/
#define UART2_RXD_PD12           SYS_GPD_MFP3_PD12MFP_UART2_RXD       /*!< GPD_MFP3 PD12 setting for UART2_RXD*/
#define UART2_RXD_PE15           SYS_GPE_MFP3_PE15MFP_UART2_RXD       /*!< GPE_MFP3 PE15 setting for UART2_RXD*/
#define UART2_RXD_PC4            SYS_GPC_MFP1_PC4MFP_UART2_RXD        /*!< GPC_MFP1 PC4 setting for UART2_RXD*/
#define UART2_RXD_PF5            SYS_GPF_MFP1_PF5MFP_UART2_RXD        /*!< GPF_MFP1 PF5 setting for UART2_RXD*/
#define UART2_RXD_PG0            SYS_GPG_MFP0_PG0MFP_UART2_RXD        /*!< GPG_MFP0 PG0 setting for UART2_RXD*/
#define UART2_RXD_PB4            SYS_GPB_MFP1_PB4MFP_UART2_RXD        /*!< GPB_MFP1 PB4 setting for UART2_RXD*/
#define UART2_RXD_PI11           SYS_GPI_MFP2_PI11MFP_UART2_RXD       /*!< GPI_MFP2 PI11 setting for UART2_RXD*/
#define UART2_TXD_PE8            SYS_GPE_MFP2_PE8MFP_UART2_TXD        /*!< GPE_MFP2 PE8 setting for UART2_TXD*/
#define UART2_TXD_PC5            SYS_GPC_MFP1_PC5MFP_UART2_TXD        /*!< GPC_MFP1 PC5 setting for UART2_TXD*/
#define UART2_TXD_PB5            SYS_GPB_MFP1_PB5MFP_UART2_TXD        /*!< GPB_MFP1 PB5 setting for UART2_TXD*/
#define UART2_TXD_PF0            SYS_GPF_MFP0_PF0MFP_UART2_TXD        /*!< GPF_MFP0 PF0 setting for UART2_TXD*/
#define UART2_TXD_PG1            SYS_GPG_MFP0_PG1MFP_UART2_TXD        /*!< GPG_MFP0 PG1 setting for UART2_TXD*/
#define UART2_TXD_PC13           SYS_GPC_MFP3_PC13MFP_UART2_TXD       /*!< GPC_MFP3 PC13 setting for UART2_TXD*/
#define UART2_TXD_PE14           SYS_GPE_MFP3_PE14MFP_UART2_TXD       /*!< GPE_MFP3 PE14 setting for UART2_TXD*/
#define UART2_TXD_PF4            SYS_GPF_MFP1_PF4MFP_UART2_TXD        /*!< GPF_MFP1 PF4 setting for UART2_TXD*/
#define UART2_TXD_PI10           SYS_GPI_MFP2_PI10MFP_UART2_TXD       /*!< GPI_MFP2 PI10 setting for UART2_TXD*/
#define UART2_TXD_PI6            SYS_GPI_MFP1_PI6MFP_UART2_TXD        /*!< GPI_MFP1 PI6 setting for UART2_TXD*/
#define UART2_TXD_PB1            SYS_GPB_MFP0_PB1MFP_UART2_TXD        /*!< GPB_MFP0 PB1 setting for UART2_TXD*/
#define UART2_TXD_PC1            SYS_GPC_MFP0_PC1MFP_UART2_TXD        /*!< GPC_MFP0 PC1 setting for UART2_TXD*/
#define UART2_nCTS_PD9           SYS_GPD_MFP2_PD9MFP_UART2_nCTS       /*!< GPD_MFP2 PD9 setting for UART2_nCTS*/
#define UART2_nCTS_PC2           SYS_GPC_MFP0_PC2MFP_UART2_nCTS       /*!< GPC_MFP0 PC2 setting for UART2_nCTS*/
#define UART2_nCTS_PI9           SYS_GPI_MFP2_PI9MFP_UART2_nCTS       /*!< GPI_MFP2 PI9 setting for UART2_nCTS*/
#define UART2_nCTS_PF5           SYS_GPF_MFP1_PF5MFP_UART2_nCTS       /*!< GPF_MFP1 PF5 setting for UART2_nCTS*/
#define UART2_nRTS_PI8           SYS_GPI_MFP2_PI8MFP_UART2_nRTS       /*!< GPI_MFP2 PI8 setting for UART2_nRTS*/
#define UART2_nRTS_PF4           SYS_GPF_MFP1_PF4MFP_UART2_nRTS       /*!< GPF_MFP1 PF4 setting for UART2_nRTS*/
#define UART2_nRTS_PD8           SYS_GPD_MFP2_PD8MFP_UART2_nRTS       /*!< GPD_MFP2 PD8 setting for UART2_nRTS*/
#define UART2_nRTS_PC3           SYS_GPC_MFP0_PC3MFP_UART2_nRTS       /*!< GPC_MFP0 PC3 setting for UART2_nRTS*/
#define UART3_RXD_PI15           SYS_GPI_MFP3_PI15MFP_UART3_RXD       /*!< GPI_MFP3 PI15 setting for UART3_RXD*/
#define UART3_RXD_PE0            SYS_GPE_MFP0_PE0MFP_UART3_RXD        /*!< GPE_MFP0 PE0 setting for UART3_RXD*/
#define UART3_RXD_PE11           SYS_GPE_MFP2_PE11MFP_UART3_RXD       /*!< GPE_MFP2 PE11 setting for UART3_RXD*/
#define UART3_RXD_PB14           SYS_GPB_MFP3_PB14MFP_UART3_RXD       /*!< GPB_MFP3 PB14 setting for UART3_RXD*/
#define UART3_RXD_PC9            SYS_GPC_MFP2_PC9MFP_UART3_RXD        /*!< GPC_MFP2 PC9 setting for UART3_RXD*/
#define UART3_RXD_PD0            SYS_GPD_MFP0_PD0MFP_UART3_RXD        /*!< GPD_MFP0 PD0 setting for UART3_RXD*/
#define UART3_RXD_PC2            SYS_GPC_MFP0_PC2MFP_UART3_RXD        /*!< GPC_MFP0 PC2 setting for UART3_RXD*/
#define UART3_TXD_PB15           SYS_GPB_MFP3_PB15MFP_UART3_TXD       /*!< GPB_MFP3 PB15 setting for UART3_TXD*/
#define UART3_TXD_PI14           SYS_GPI_MFP3_PI14MFP_UART3_TXD       /*!< GPI_MFP3 PI14 setting for UART3_TXD*/
#define UART3_TXD_PD1            SYS_GPD_MFP0_PD1MFP_UART3_TXD        /*!< GPD_MFP0 PD1 setting for UART3_TXD*/
#define UART3_TXD_PE10           SYS_GPE_MFP2_PE10MFP_UART3_TXD       /*!< GPE_MFP2 PE10 setting for UART3_TXD*/
#define UART3_TXD_PE1            SYS_GPE_MFP0_PE1MFP_UART3_TXD        /*!< GPE_MFP0 PE1 setting for UART3_TXD*/
#define UART3_TXD_PC3            SYS_GPC_MFP0_PC3MFP_UART3_TXD        /*!< GPC_MFP0 PC3 setting for UART3_TXD*/
#define UART3_TXD_PC10           SYS_GPC_MFP2_PC10MFP_UART3_TXD       /*!< GPC_MFP2 PC10 setting for UART3_TXD*/
#define UART3_nCTS_PB12          SYS_GPB_MFP3_PB12MFP_UART3_nCTS      /*!< GPB_MFP3 PB12 setting for UART3_nCTS*/
#define UART3_nCTS_PH9           SYS_GPH_MFP2_PH9MFP_UART3_nCTS       /*!< GPH_MFP2 PH9 setting for UART3_nCTS*/
#define UART3_nCTS_PD2           SYS_GPD_MFP0_PD2MFP_UART3_nCTS       /*!< GPD_MFP0 PD2 setting for UART3_nCTS*/
#define UART3_nRTS_PB13          SYS_GPB_MFP3_PB13MFP_UART3_nRTS      /*!< GPB_MFP3 PB13 setting for UART3_nRTS*/
#define UART3_nRTS_PH8           SYS_GPH_MFP2_PH8MFP_UART3_nRTS       /*!< GPH_MFP2 PH8 setting for UART3_nRTS*/
#define UART3_nRTS_PD3           SYS_GPD_MFP0_PD3MFP_UART3_nRTS       /*!< GPD_MFP0 PD3 setting for UART3_nRTS*/
#define UART4_RXD_PB10           SYS_GPB_MFP2_PB10MFP_UART4_RXD       /*!< GPB_MFP2 PB10 setting for UART4_RXD*/
#define UART4_RXD_PI13           SYS_GPI_MFP3_PI13MFP_UART4_RXD       /*!< GPI_MFP3 PI13 setting for UART4_RXD*/
#define UART4_RXD_PH3            SYS_GPH_MFP0_PH3MFP_UART4_RXD        /*!< GPH_MFP0 PH3 setting for UART4_RXD*/
#define UART4_RXD_PA13           SYS_GPA_MFP3_PA13MFP_UART4_RXD       /*!< GPA_MFP3 PA13 setting for UART4_RXD*/
#define UART4_RXD_PH11           SYS_GPH_MFP2_PH11MFP_UART4_RXD       /*!< GPH_MFP2 PH11 setting for UART4_RXD*/
#define UART4_RXD_PA2            SYS_GPA_MFP0_PA2MFP_UART4_RXD        /*!< GPA_MFP0 PA2 setting for UART4_RXD*/
#define UART4_RXD_PC6            SYS_GPC_MFP1_PC6MFP_UART4_RXD        /*!< GPC_MFP1 PC6 setting for UART4_RXD*/
#define UART4_RXD_PF6            SYS_GPF_MFP1_PF6MFP_UART4_RXD        /*!< GPF_MFP1 PF6 setting for UART4_RXD*/
#define UART4_RXD_PC4            SYS_GPC_MFP1_PC4MFP_UART4_RXD        /*!< GPC_MFP1 PC4 setting for UART4_RXD*/
#define UART4_TXD_PA12           SYS_GPA_MFP3_PA12MFP_UART4_TXD       /*!< GPA_MFP3 PA12 setting for UART4_TXD*/
#define UART4_TXD_PB11           SYS_GPB_MFP2_PB11MFP_UART4_TXD       /*!< GPB_MFP2 PB11 setting for UART4_TXD*/
#define UART4_TXD_PF7            SYS_GPF_MFP1_PF7MFP_UART4_TXD        /*!< GPF_MFP1 PF7 setting for UART4_TXD*/
#define UART4_TXD_PH2            SYS_GPH_MFP0_PH2MFP_UART4_TXD        /*!< GPH_MFP0 PH2 setting for UART4_TXD*/
#define UART4_TXD_PI12           SYS_GPI_MFP3_PI12MFP_UART4_TXD       /*!< GPI_MFP3 PI12 setting for UART4_TXD*/
#define UART4_TXD_PC5            SYS_GPC_MFP1_PC5MFP_UART4_TXD        /*!< GPC_MFP1 PC5 setting for UART4_TXD*/
#define UART4_TXD_PC7            SYS_GPC_MFP1_PC7MFP_UART4_TXD        /*!< GPC_MFP1 PC7 setting for UART4_TXD*/
#define UART4_TXD_PA3            SYS_GPA_MFP0_PA3MFP_UART4_TXD        /*!< GPA_MFP0 PA3 setting for UART4_TXD*/
#define UART4_TXD_PH10           SYS_GPH_MFP2_PH10MFP_UART4_TXD       /*!< GPH_MFP2 PH10 setting for UART4_TXD*/
#define UART4_nCTS_PC8           SYS_GPC_MFP2_PC8MFP_UART4_nCTS       /*!< GPC_MFP2 PC8 setting for UART4_nCTS*/
#define UART4_nCTS_PE1           SYS_GPE_MFP0_PE1MFP_UART4_nCTS       /*!< GPE_MFP0 PE1 setting for UART4_nCTS*/
#define UART4_nRTS_PE0           SYS_GPE_MFP0_PE0MFP_UART4_nRTS       /*!< GPE_MFP0 PE0 setting for UART4_nRTS*/
#define UART4_nRTS_PE13          SYS_GPE_MFP3_PE13MFP_UART4_nRTS      /*!< GPE_MFP3 PE13 setting for UART4_nRTS*/
#define UART5_RXD_PF10           SYS_GPF_MFP2_PF10MFP_UART5_RXD       /*!< GPF_MFP2 PF10 setting for UART5_RXD*/
#define UART5_RXD_PB4            SYS_GPB_MFP1_PB4MFP_UART5_RXD        /*!< GPB_MFP1 PB4 setting for UART5_RXD*/
#define UART5_RXD_PH1            SYS_GPH_MFP0_PH1MFP_UART5_RXD        /*!< GPH_MFP0 PH1 setting for UART5_RXD*/
#define UART5_RXD_PE6            SYS_GPE_MFP1_PE6MFP_UART5_RXD        /*!< GPE_MFP1 PE6 setting for UART5_RXD*/
#define UART5_RXD_PA4            SYS_GPA_MFP1_PA4MFP_UART5_RXD        /*!< GPA_MFP1 PA4 setting for UART5_RXD*/
#define UART5_TXD_PB5            SYS_GPB_MFP1_PB5MFP_UART5_TXD        /*!< GPB_MFP1 PB5 setting for UART5_TXD*/
#define UART5_TXD_PF11           SYS_GPF_MFP2_PF11MFP_UART5_TXD       /*!< GPF_MFP2 PF11 setting for UART5_TXD*/
#define UART5_TXD_PE7            SYS_GPE_MFP1_PE7MFP_UART5_TXD        /*!< GPE_MFP1 PE7 setting for UART5_TXD*/
#define UART5_TXD_PA5            SYS_GPA_MFP1_PA5MFP_UART5_TXD        /*!< GPA_MFP1 PA5 setting for UART5_TXD*/
#define UART5_TXD_PH0            SYS_GPH_MFP0_PH0MFP_UART5_TXD        /*!< GPH_MFP0 PH0 setting for UART5_TXD*/
#define UART5_nCTS_PF8           SYS_GPF_MFP2_PF8MFP_UART5_nCTS       /*!< GPF_MFP2 PF8 setting for UART5_nCTS*/
#define UART5_nCTS_PH3           SYS_GPH_MFP0_PH3MFP_UART5_nCTS       /*!< GPH_MFP0 PH3 setting for UART5_nCTS*/
#define UART5_nCTS_PB2           SYS_GPB_MFP0_PB2MFP_UART5_nCTS       /*!< GPB_MFP0 PB2 setting for UART5_nCTS*/
#define UART5_nRTS_PF9           SYS_GPF_MFP2_PF9MFP_UART5_nRTS       /*!< GPF_MFP2 PF9 setting for UART5_nRTS*/
#define UART5_nRTS_PH2           SYS_GPH_MFP0_PH2MFP_UART5_nRTS       /*!< GPH_MFP0 PH2 setting for UART5_nRTS*/
#define UART5_nRTS_PB3           SYS_GPB_MFP0_PB3MFP_UART5_nRTS       /*!< GPB_MFP0 PB3 setting for UART5_nRTS*/
#define UART6_RXD_PE15           SYS_GPE_MFP3_PE15MFP_UART6_RXD       /*!< GPE_MFP3 PE15 setting for UART6_RXD*/
#define UART6_RXD_PC6            SYS_GPC_MFP1_PC6MFP_UART6_RXD        /*!< GPC_MFP1 PC6 setting for UART6_RXD*/
#define UART6_RXD_PH5            SYS_GPH_MFP1_PH5MFP_UART6_RXD        /*!< GPH_MFP1 PH5 setting for UART6_RXD*/
#define UART6_RXD_PG14           SYS_GPG_MFP3_PG14MFP_UART6_RXD       /*!< GPG_MFP3 PG14 setting for UART6_RXD*/
#define UART6_RXD_PA10           SYS_GPA_MFP2_PA10MFP_UART6_RXD       /*!< GPA_MFP2 PA10 setting for UART6_RXD*/
#define UART6_RXD_PD13           SYS_GPD_MFP3_PD13MFP_UART6_RXD       /*!< GPD_MFP3 PD13 setting for UART6_RXD*/
#define UART6_RXD_PC11           SYS_GPC_MFP2_PC11MFP_UART6_RXD       /*!< GPC_MFP2 PC11 setting for UART6_RXD*/
#define UART6_RXD_PE4            SYS_GPE_MFP1_PE4MFP_UART6_RXD        /*!< GPE_MFP1 PE4 setting for UART6_RXD*/
#define UART6_RXD_PJ11           SYS_GPJ_MFP2_PJ11MFP_UART6_RXD       /*!< GPJ_MFP2 PJ11 setting for UART6_RXD*/
#define UART6_TXD_PG13           SYS_GPG_MFP3_PG13MFP_UART6_TXD       /*!< GPG_MFP3 PG13 setting for UART6_TXD*/
#define UART6_TXD_PE14           SYS_GPE_MFP3_PE14MFP_UART6_TXD       /*!< GPE_MFP3 PE14 setting for UART6_TXD*/
#define UART6_TXD_PC12           SYS_GPC_MFP3_PC12MFP_UART6_TXD       /*!< GPC_MFP3 PC12 setting for UART6_TXD*/
#define UART6_TXD_PC7            SYS_GPC_MFP1_PC7MFP_UART6_TXD        /*!< GPC_MFP1 PC7 setting for UART6_TXD*/
#define UART6_TXD_PH4            SYS_GPH_MFP1_PH4MFP_UART6_TXD        /*!< GPH_MFP1 PH4 setting for UART6_TXD*/
#define UART6_TXD_PJ10           SYS_GPJ_MFP2_PJ10MFP_UART6_TXD       /*!< GPJ_MFP2 PJ10 setting for UART6_TXD*/
#define UART6_TXD_PA11           SYS_GPA_MFP2_PA11MFP_UART6_TXD       /*!< GPA_MFP2 PA11 setting for UART6_TXD*/
#define UART6_TXD_PE5            SYS_GPE_MFP1_PE5MFP_UART6_TXD        /*!< GPE_MFP1 PE5 setting for UART6_TXD*/
#define UART6_nCTS_PC9           SYS_GPC_MFP2_PC9MFP_UART6_nCTS       /*!< GPC_MFP2 PC9 setting for UART6_nCTS*/
#define UART6_nCTS_PE2           SYS_GPE_MFP0_PE2MFP_UART6_nCTS       /*!< GPE_MFP0 PE2 setting for UART6_nCTS*/
#define UART6_nRTS_PC10          SYS_GPC_MFP2_PC10MFP_UART6_nRTS      /*!< GPC_MFP2 PC10 setting for UART6_nRTS*/
#define UART6_nRTS_PE3           SYS_GPE_MFP0_PE3MFP_UART6_nRTS       /*!< GPE_MFP0 PE3 setting for UART6_nRTS*/
#define UART7_RXD_PD8            SYS_GPD_MFP2_PD8MFP_UART7_RXD        /*!< GPD_MFP2 PD8 setting for UART7_RXD*/
#define UART7_RXD_PG12           SYS_GPG_MFP3_PG12MFP_UART7_RXD       /*!< GPG_MFP3 PG12 setting for UART7_RXD*/
#define UART7_RXD_PJ9            SYS_GPJ_MFP2_PJ9MFP_UART7_RXD        /*!< GPJ_MFP2 PJ9 setting for UART7_RXD*/
#define UART7_RXD_PH7            SYS_GPH_MFP1_PH7MFP_UART7_RXD        /*!< GPH_MFP1 PH7 setting for UART7_RXD*/
#define UART7_RXD_PB8            SYS_GPB_MFP2_PB8MFP_UART7_RXD        /*!< GPB_MFP2 PB8 setting for UART7_RXD*/
#define UART7_RXD_PE2            SYS_GPE_MFP0_PE2MFP_UART7_RXD        /*!< GPE_MFP0 PE2 setting for UART7_RXD*/
#define UART7_RXD_PA8            SYS_GPA_MFP2_PA8MFP_UART7_RXD        /*!< GPA_MFP2 PA8 setting for UART7_RXD*/
#define UART7_TXD_PE3            SYS_GPE_MFP0_PE3MFP_UART7_TXD        /*!< GPE_MFP0 PE3 setting for UART7_TXD*/
#define UART7_TXD_PG11           SYS_GPG_MFP2_PG11MFP_UART7_TXD       /*!< GPG_MFP2 PG11 setting for UART7_TXD*/
#define UART7_TXD_PA9            SYS_GPA_MFP2_PA9MFP_UART7_TXD        /*!< GPA_MFP2 PA9 setting for UART7_TXD*/
#define UART7_TXD_PJ8            SYS_GPJ_MFP2_PJ8MFP_UART7_TXD        /*!< GPJ_MFP2 PJ8 setting for UART7_TXD*/
#define UART7_TXD_PB9            SYS_GPB_MFP2_PB9MFP_UART7_TXD        /*!< GPB_MFP2 PB9 setting for UART7_TXD*/
#define UART7_TXD_PD9            SYS_GPD_MFP2_PD9MFP_UART7_TXD        /*!< GPD_MFP2 PD9 setting for UART7_TXD*/
#define UART7_TXD_PH6            SYS_GPH_MFP1_PH6MFP_UART7_TXD        /*!< GPH_MFP1 PH6 setting for UART7_TXD*/
#define UART7_nCTS_PE4           SYS_GPE_MFP1_PE4MFP_UART7_nCTS       /*!< GPE_MFP1 PE4 setting for UART7_nCTS*/
#define UART7_nCTS_PH5           SYS_GPH_MFP1_PH5MFP_UART7_nCTS       /*!< GPH_MFP1 PH5 setting for UART7_nCTS*/
#define UART7_nRTS_PE5           SYS_GPE_MFP1_PE5MFP_UART7_nRTS       /*!< GPE_MFP1 PE5 setting for UART7_nRTS*/
#define UART7_nRTS_PH4           SYS_GPH_MFP1_PH4MFP_UART7_nRTS       /*!< GPH_MFP1 PH4 setting for UART7_nRTS*/
#define UART8_RXD_PJ1            SYS_GPJ_MFP0_PJ1MFP_UART8_RXD        /*!< GPJ_MFP0 PJ1 setting for UART8_RXD*/
#define UART8_RXD_PJ5            SYS_GPJ_MFP1_PJ5MFP_UART8_RXD        /*!< GPJ_MFP1 PJ5 setting for UART8_RXD*/
#define UART8_RXD_PE0            SYS_GPE_MFP0_PE0MFP_UART8_RXD        /*!< GPE_MFP0 PE0 setting for UART8_RXD*/
#define UART8_RXD_PD10           SYS_GPD_MFP2_PD10MFP_UART8_RXD       /*!< GPD_MFP2 PD10 setting for UART8_RXD*/
#define UART8_TXD_PE1            SYS_GPE_MFP0_PE1MFP_UART8_TXD        /*!< GPE_MFP0 PE1 setting for UART8_TXD*/
#define UART8_TXD_PD11           SYS_GPD_MFP2_PD11MFP_UART8_TXD       /*!< GPD_MFP2 PD11 setting for UART8_TXD*/
#define UART8_TXD_PJ0            SYS_GPJ_MFP0_PJ0MFP_UART8_TXD        /*!< GPJ_MFP0 PJ0 setting for UART8_TXD*/
#define UART8_TXD_PJ4            SYS_GPJ_MFP1_PJ4MFP_UART8_TXD        /*!< GPJ_MFP1 PJ4 setting for UART8_TXD*/
#define UART8_nCTS_PJ2           SYS_GPJ_MFP0_PJ2MFP_UART8_nCTS       /*!< GPJ_MFP0 PJ2 setting for UART8_nCTS*/
#define UART8_nCTS_PC13          SYS_GPC_MFP3_PC13MFP_UART8_nCTS      /*!< GPC_MFP3 PC13 setting for UART8_nCTS*/
#define UART8_nCTS_PE3           SYS_GPE_MFP0_PE3MFP_UART8_nCTS       /*!< GPE_MFP0 PE3 setting for UART8_nCTS*/
#define UART8_nCTS_PI14          SYS_GPI_MFP3_PI14MFP_UART8_nCTS      /*!< GPI_MFP3 PI14 setting for UART8_nCTS*/
#define UART8_nRTS_PI15          SYS_GPI_MFP3_PI15MFP_UART8_nRTS      /*!< GPI_MFP3 PI15 setting for UART8_nRTS*/
#define UART8_nRTS_PJ3           SYS_GPJ_MFP0_PJ3MFP_UART8_nRTS       /*!< GPJ_MFP0 PJ3 setting for UART8_nRTS*/
#define UART8_nRTS_PD12          SYS_GPD_MFP3_PD12MFP_UART8_nRTS      /*!< GPD_MFP3 PD12 setting for UART8_nRTS*/
#define UART8_nRTS_PE2           SYS_GPE_MFP0_PE2MFP_UART8_nRTS       /*!< GPE_MFP0 PE2 setting for UART8_nRTS*/
#define UART9_RXD_PF2            SYS_GPF_MFP0_PF2MFP_UART9_RXD        /*!< GPF_MFP0 PF2 setting for UART9_RXD*/
#define UART9_RXD_PH11           SYS_GPH_MFP2_PH11MFP_UART9_RXD       /*!< GPH_MFP2 PH11 setting for UART9_RXD*/
#define UART9_RXD_PF8            SYS_GPF_MFP2_PF8MFP_UART9_RXD        /*!< GPF_MFP2 PF8 setting for UART9_RXD*/
#define UART9_RXD_PE4            SYS_GPE_MFP1_PE4MFP_UART9_RXD        /*!< GPE_MFP1 PE4 setting for UART9_RXD*/
#define UART9_RXD_PH13           SYS_GPH_MFP3_PH13MFP_UART9_RXD       /*!< GPH_MFP3 PH13 setting for UART9_RXD*/
#define UART9_TXD_PE5            SYS_GPE_MFP1_PE5MFP_UART9_TXD        /*!< GPE_MFP1 PE5 setting for UART9_TXD*/
#define UART9_TXD_PF9            SYS_GPF_MFP2_PF9MFP_UART9_TXD        /*!< GPF_MFP2 PF9 setting for UART9_TXD*/
#define UART9_TXD_PF3            SYS_GPF_MFP0_PF3MFP_UART9_TXD        /*!< GPF_MFP0 PF3 setting for UART9_TXD*/
#define UART9_TXD_PH12           SYS_GPH_MFP3_PH12MFP_UART9_TXD       /*!< GPH_MFP3 PH12 setting for UART9_TXD*/
#define UART9_TXD_PH10           SYS_GPH_MFP2_PH10MFP_UART9_TXD       /*!< GPH_MFP2 PH10 setting for UART9_TXD*/
#define UART9_nCTS_PJ6           SYS_GPJ_MFP1_PJ6MFP_UART9_nCTS       /*!< GPJ_MFP1 PJ6 setting for UART9_nCTS*/
#define UART9_nCTS_PF11          SYS_GPF_MFP2_PF11MFP_UART9_nCTS      /*!< GPF_MFP2 PF11 setting for UART9_nCTS*/
#define UART9_nCTS_PH6           SYS_GPH_MFP1_PH6MFP_UART9_nCTS       /*!< GPH_MFP1 PH6 setting for UART9_nCTS*/
#define UART9_nCTS_PH8           SYS_GPH_MFP2_PH8MFP_UART9_nCTS       /*!< GPH_MFP2 PH8 setting for UART9_nCTS*/
#define UART9_nCTS_PE7           SYS_GPE_MFP1_PE7MFP_UART9_nCTS       /*!< GPE_MFP1 PE7 setting for UART9_nCTS*/
#define UART9_nRTS_PH7           SYS_GPH_MFP1_PH7MFP_UART9_nRTS       /*!< GPH_MFP1 PH7 setting for UART9_nRTS*/
#define UART9_nRTS_PF10          SYS_GPF_MFP2_PF10MFP_UART9_nRTS      /*!< GPF_MFP2 PF10 setting for UART9_nRTS*/
#define UART9_nRTS_PH9           SYS_GPH_MFP2_PH9MFP_UART9_nRTS       /*!< GPH_MFP2 PH9 setting for UART9_nRTS*/
#define UART9_nRTS_PE6           SYS_GPE_MFP1_PE6MFP_UART9_nRTS       /*!< GPE_MFP1 PE6 setting for UART9_nRTS*/
#define UART9_nRTS_PJ7           SYS_GPJ_MFP1_PJ7MFP_UART9_nRTS       /*!< GPJ_MFP1 PJ7 setting for UART9_nRTS*/
#define USB_D_P_PA14              SYS_GPA_MFP3_PA14MFP_USB_D_P          /*!< GPA_MFP3 PA14 setting for USB_D+*/
#define USB_D_N_PA13              SYS_GPA_MFP3_PA13MFP_USB_D_N          /*!< GPA_MFP3 PA13 setting for USB_D-*/
#define USB_OTG_ID_PA15          SYS_GPA_MFP3_PA15MFP_USB_OTG_ID      /*!< GPA_MFP3 PA15 setting for USB_OTG_ID*/
#define USB_VBUS_PA12            SYS_GPA_MFP3_PA12MFP_USB_VBUS        /*!< GPA_MFP3 PA12 setting for USB_VBUS*/
#define USB_VBUS_EN_PB6          SYS_GPB_MFP1_PB6MFP_USB_VBUS_EN      /*!< GPB_MFP1 PB6 setting for USB_VBUS_EN*/
#define USB_VBUS_EN_PI7          SYS_GPI_MFP1_PI7MFP_USB_VBUS_EN      /*!< GPI_MFP1 PI7 setting for USB_VBUS_EN*/
#define USB_VBUS_EN_PB15         SYS_GPB_MFP3_PB15MFP_USB_VBUS_EN     /*!< GPB_MFP3 PB15 setting for USB_VBUS_EN*/
#define USB_VBUS_ST_PB14         SYS_GPB_MFP3_PB14MFP_USB_VBUS_ST     /*!< GPB_MFP3 PB14 setting for USB_VBUS_ST*/
#define USB_VBUS_ST_PC14         SYS_GPC_MFP3_PC14MFP_USB_VBUS_ST     /*!< GPC_MFP3 PC14 setting for USB_VBUS_ST*/
#define USB_VBUS_ST_PD4          SYS_GPD_MFP1_PD4MFP_USB_VBUS_ST      /*!< GPD_MFP1 PD4 setting for USB_VBUS_ST*/
#define USB_VBUS_ST_PB7          SYS_GPB_MFP1_PB7MFP_USB_VBUS_ST      /*!< GPB_MFP1 PB7 setting for USB_VBUS_ST*/
#define USB_VBUS_ST_PI6          SYS_GPI_MFP1_PI6MFP_USB_VBUS_ST      /*!< GPI_MFP1 PI6 setting for USB_VBUS_ST*/
#define USCI0_CLK_PD0            SYS_GPD_MFP0_PD0MFP_USCI0_CLK        /*!< GPD_MFP0 PD0 setting for USCI0_CLK*/
#define USCI0_CLK_PE2            SYS_GPE_MFP0_PE2MFP_USCI0_CLK        /*!< GPE_MFP0 PE2 setting for USCI0_CLK*/
#define USCI0_CLK_PA11           SYS_GPA_MFP2_PA11MFP_USCI0_CLK       /*!< GPA_MFP2 PA11 setting for USCI0_CLK*/
#define USCI0_CLK_PB12           SYS_GPB_MFP3_PB12MFP_USCI0_CLK       /*!< GPB_MFP3 PB12 setting for USCI0_CLK*/
#define USCI0_CTL0_PC14          SYS_GPC_MFP3_PC14MFP_USCI0_CTL0      /*!< GPC_MFP3 PC14 setting for USCI0_CTL0*/
#define USCI0_CTL0_PE6           SYS_GPE_MFP1_PE6MFP_USCI0_CTL0       /*!< GPE_MFP1 PE6 setting for USCI0_CTL0*/
#define USCI0_CTL0_PB0           SYS_GPB_MFP0_PB0MFP_USCI0_CTL0       /*!< GPB_MFP0 PB0 setting for USCI0_CTL0*/
#define USCI0_CTL0_PD4           SYS_GPD_MFP1_PD4MFP_USCI0_CTL0       /*!< GPD_MFP1 PD4 setting for USCI0_CTL0*/
#define USCI0_CTL0_PC13          SYS_GPC_MFP3_PC13MFP_USCI0_CTL0      /*!< GPC_MFP3 PC13 setting for USCI0_CTL0*/
#define USCI0_CTL1_PA8           SYS_GPA_MFP2_PA8MFP_USCI0_CTL1       /*!< GPA_MFP2 PA8 setting for USCI0_CTL1*/
#define USCI0_CTL1_PD3           SYS_GPD_MFP0_PD3MFP_USCI0_CTL1       /*!< GPD_MFP0 PD3 setting for USCI0_CTL1*/
#define USCI0_CTL1_PE5           SYS_GPE_MFP1_PE5MFP_USCI0_CTL1       /*!< GPE_MFP1 PE5 setting for USCI0_CTL1*/
#define USCI0_CTL1_PB15          SYS_GPB_MFP3_PB15MFP_USCI0_CTL1      /*!< GPB_MFP3 PB15 setting for USCI0_CTL1*/
#define USCI0_DAT0_PA10          SYS_GPA_MFP2_PA10MFP_USCI0_DAT0      /*!< GPA_MFP2 PA10 setting for USCI0_DAT0*/
#define USCI0_DAT0_PB13          SYS_GPB_MFP3_PB13MFP_USCI0_DAT0      /*!< GPB_MFP3 PB13 setting for USCI0_DAT0*/
#define USCI0_DAT0_PE3           SYS_GPE_MFP0_PE3MFP_USCI0_DAT0       /*!< GPE_MFP0 PE3 setting for USCI0_DAT0*/
#define USCI0_DAT0_PD1           SYS_GPD_MFP0_PD1MFP_USCI0_DAT0       /*!< GPD_MFP0 PD1 setting for USCI0_DAT0*/
#define USCI0_DAT1_PD2           SYS_GPD_MFP0_PD2MFP_USCI0_DAT1       /*!< GPD_MFP0 PD2 setting for USCI0_DAT1*/
#define USCI0_DAT1_PE4           SYS_GPE_MFP1_PE4MFP_USCI0_DAT1       /*!< GPE_MFP1 PE4 setting for USCI0_DAT1*/
#define USCI0_DAT1_PA9           SYS_GPA_MFP2_PA9MFP_USCI0_DAT1       /*!< GPA_MFP2 PA9 setting for USCI0_DAT1*/
#define USCI0_DAT1_PB14          SYS_GPB_MFP3_PB14MFP_USCI0_DAT1      /*!< GPB_MFP3 PB14 setting for USCI0_DAT1*/
#define X32_IN_PF5               SYS_GPF_MFP1_PF5MFP_X32_IN           /*!< GPF_MFP1 PF5 setting for X32_IN*/
#define X32_OUT_PF4              SYS_GPF_MFP1_PF4MFP_X32_OUT          /*!< GPF_MFP1 PF4 setting for X32_OUT*/
#define XT1_IN_PF3               SYS_GPF_MFP0_PF3MFP_XT1_IN           /*!< GPF_MFP0 PF3 setting for XT1_IN*/
#define XT1_OUT_PF2              SYS_GPF_MFP0_PF2MFP_XT1_OUT          /*!< GPF_MFP0 PF2 setting for XT1_OUT*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function setting mask constant definitions abbreviation.                                         */
/*---------------------------------------------------------------------------------------------------------*/

#define ACMP0_N_PB3_Msk         SYS_GPB_MFP0_PB3MFP_Msk        /*<! ACMP0_N         PB3      MFP Mask */
#define ACMP0_O_PB7_Msk         SYS_GPB_MFP1_PB7MFP_Msk        /*<! ACMP0_O         PB7      MFP Mask */
#define ACMP0_O_PC1_Msk         SYS_GPC_MFP0_PC1MFP_Msk        /*<! ACMP0_O         PC1      MFP Mask */
#define ACMP0_O_PC12_Msk        SYS_GPC_MFP3_PC12MFP_Msk       /*<! ACMP0_O         PC12     MFP Mask */
#define ACMP0_O_PD6_Msk         SYS_GPD_MFP1_PD6MFP_Msk        /*<! ACMP0_O         PD6      MFP Mask */
#define ACMP0_O_PF0_Msk         SYS_GPF_MFP0_PF0MFP_Msk        /*<! ACMP0_O         PF0      MFP Mask */
#define ACMP0_P0_PA11_Msk       SYS_GPA_MFP2_PA11MFP_Msk       /*<! ACMP0_P0        PA11     MFP Mask */
#define ACMP0_P1_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! ACMP0_P1        PB2      MFP Mask */
#define ACMP0_P2_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! ACMP0_P2        PB12     MFP Mask */
#define ACMP0_P3_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! ACMP0_P3        PB13     MFP Mask */
#define ACMP0_WLAT_PA7_Msk      SYS_GPA_MFP1_PA7MFP_Msk        /*<! ACMP0_WLAT      PA7      MFP Mask */
#define ACMP1_N_PB5_Msk         SYS_GPB_MFP1_PB5MFP_Msk        /*<! ACMP1_N         PB5      MFP Mask */
#define ACMP1_O_PC0_Msk         SYS_GPC_MFP0_PC0MFP_Msk        /*<! ACMP1_O         PC0      MFP Mask */
#define ACMP1_O_PD5_Msk         SYS_GPD_MFP1_PD5MFP_Msk        /*<! ACMP1_O         PD5      MFP Mask */
#define ACMP1_O_PB6_Msk         SYS_GPB_MFP1_PB6MFP_Msk        /*<! ACMP1_O         PB6      MFP Mask */
#define ACMP1_O_PC11_Msk        SYS_GPC_MFP2_PC11MFP_Msk       /*<! ACMP1_O         PC11     MFP Mask */
#define ACMP1_O_PF1_Msk         SYS_GPF_MFP0_PF1MFP_Msk        /*<! ACMP1_O         PF1      MFP Mask */
#define ACMP1_P0_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! ACMP1_P0        PA10     MFP Mask */
#define ACMP1_P1_PB4_Msk        SYS_GPB_MFP1_PB4MFP_Msk        /*<! ACMP1_P1        PB4      MFP Mask */
#define ACMP1_P2_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! ACMP1_P2        PB12     MFP Mask */
#define ACMP1_P3_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! ACMP1_P3        PB13     MFP Mask */
#define ACMP1_WLAT_PA6_Msk      SYS_GPA_MFP1_PA6MFP_Msk        /*<! ACMP1_WLAT      PA6      MFP Mask */
#define ACMP2_N_PB6_Msk         SYS_GPB_MFP1_PB6MFP_Msk        /*<! ACMP2_N         PB6      MFP Mask */
#define ACMP2_O_PB1_Msk         SYS_GPB_MFP0_PB1MFP_Msk        /*<! ACMP2_O         PB1      MFP Mask */
#define ACMP2_O_PE7_Msk         SYS_GPE_MFP1_PE7MFP_Msk        /*<! ACMP2_O         PE7      MFP Mask */
#define ACMP2_O_PF3_Msk         SYS_GPF_MFP0_PF3MFP_Msk        /*<! ACMP2_O         PF3      MFP Mask */
#define ACMP2_P0_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! ACMP2_P0        PB7      MFP Mask */
#define ACMP2_P1_PB8_Msk        SYS_GPB_MFP2_PB8MFP_Msk        /*<! ACMP2_P1        PB8      MFP Mask */
#define ACMP2_P2_PB9_Msk        SYS_GPB_MFP2_PB9MFP_Msk        /*<! ACMP2_P2        PB9      MFP Mask */
#define ACMP2_P3_PB10_Msk       SYS_GPB_MFP2_PB10MFP_Msk       /*<! ACMP2_P3        PB10     MFP Mask */
#define ACMP2_WLAT_PC7_Msk      SYS_GPC_MFP1_PC7MFP_Msk        /*<! ACMP2_WLAT      PC7      MFP Mask */
#define ACMP3_N_PB0_Msk         SYS_GPB_MFP0_PB0MFP_Msk        /*<! ACMP3_N         PB0      MFP Mask */
#define ACMP3_O_PB0_Msk         SYS_GPB_MFP0_PB0MFP_Msk        /*<! ACMP3_O         PB0      MFP Mask */
#define ACMP3_O_PF2_Msk         SYS_GPF_MFP0_PF2MFP_Msk        /*<! ACMP3_O         PF2      MFP Mask */
#define ACMP3_O_PE6_Msk         SYS_GPE_MFP1_PE6MFP_Msk        /*<! ACMP3_O         PE6      MFP Mask */
#define ACMP3_P0_PB1_Msk        SYS_GPB_MFP0_PB1MFP_Msk        /*<! ACMP3_P0        PB1      MFP Mask */
#define ACMP3_P1_PC9_Msk        SYS_GPC_MFP2_PC9MFP_Msk        /*<! ACMP3_P1        PC9      MFP Mask */
#define ACMP3_P2_PC10_Msk       SYS_GPC_MFP2_PC10MFP_Msk       /*<! ACMP3_P2        PC10     MFP Mask */
#define ACMP3_P3_PC11_Msk       SYS_GPC_MFP2_PC11MFP_Msk       /*<! ACMP3_P3        PC11     MFP Mask */
#define ACMP3_WLAT_PC6_Msk      SYS_GPC_MFP1_PC6MFP_Msk        /*<! ACMP3_WLAT      PC6      MFP Mask */
#define BMC0_PB5_Msk            SYS_GPB_MFP1_PB5MFP_Msk        /*!< BMC0            PB5      MFP Mask */
#define BMC1_PB4_Msk            SYS_GPB_MFP1_PB4MFP_Msk        /*!< BMC1            PB4      MFP Mask */
#define BMC10_PF5_Msk           SYS_GPF_MFP1_PF5MFP_Msk        /*!< BMC10           PF5      MFP Mask */
#define BMC11_PF4_Msk           SYS_GPF_MFP1_PF4MFP_Msk        /*!< BMC11           PF4      MFP Mask */
#define BMC12_PA12_Msk          SYS_GPA_MFP3_PA12MFP_Msk       /*!< BMC12           PA12     MFP Mask */
#define BMC12_PF3_Msk           SYS_GPF_MFP0_PF3MFP_Msk        /*!< BMC12           PF3      MFP Mask */
#define BMC13_PF2_Msk           SYS_GPF_MFP0_PF2MFP_Msk        /*!< BMC13           PF2      MFP Mask */
#define BMC13_PA13_Msk          SYS_GPA_MFP3_PA13MFP_Msk       /*!< BMC13           PA13     MFP Mask */
#define BMC14_PA7_Msk           SYS_GPA_MFP1_PA7MFP_Msk        /*!< BMC14           PA7      MFP Mask */
#define BMC14_PA14_Msk          SYS_GPA_MFP3_PA14MFP_Msk       /*!< BMC14           PA14     MFP Mask */
#define BMC15_PA6_Msk           SYS_GPA_MFP1_PA6MFP_Msk        /*!< BMC15           PA6      MFP Mask */
#define BMC15_PA15_Msk          SYS_GPA_MFP3_PA15MFP_Msk       /*!< BMC15           PA15     MFP Mask */
#define BMC16_PA3_Msk           SYS_GPA_MFP0_PA3MFP_Msk        /*!< BMC16           PA3      MFP Mask */
#define BMC16_PG9_Msk           SYS_GPG_MFP2_PG9MFP_Msk        /*!< BMC16           PG9      MFP Mask */
#define BMC17_PA2_Msk           SYS_GPA_MFP0_PA2MFP_Msk        /*!< BMC17           PA2      MFP Mask */
#define BMC17_PG10_Msk          SYS_GPG_MFP2_PG10MFP_Msk       /*!< BMC17           PG10     MFP Mask */
#define BMC18_PA1_Msk           SYS_GPA_MFP0_PA1MFP_Msk        /*!< BMC18           PA1      MFP Mask */
#define BMC18_PG11_Msk          SYS_GPG_MFP2_PG11MFP_Msk       /*!< BMC18           PG11     MFP Mask */
#define BMC19_PA0_Msk           SYS_GPA_MFP0_PA0MFP_Msk        /*!< BMC19           PA0      MFP Mask */
#define BMC19_PG12_Msk          SYS_GPG_MFP3_PG12MFP_Msk       /*!< BMC19           PG12     MFP Mask */
#define BMC2_PB3_Msk            SYS_GPB_MFP0_PB3MFP_Msk        /*!< BMC2            PB3      MFP Mask */
#define BMC20_PB11_Msk          SYS_GPB_MFP2_PB11MFP_Msk       /*!< BMC20           PB11     MFP Mask */
#define BMC20_PC5_Msk           SYS_GPC_MFP1_PC5MFP_Msk        /*!< BMC20           PC5      MFP Mask */
#define BMC21_PC4_Msk           SYS_GPC_MFP1_PC4MFP_Msk        /*!< BMC21           PC4      MFP Mask */
#define BMC21_PB10_Msk          SYS_GPB_MFP2_PB10MFP_Msk       /*!< BMC21           PB10     MFP Mask */
#define BMC22_PB9_Msk           SYS_GPB_MFP2_PB9MFP_Msk        /*!< BMC22           PB9      MFP Mask */
#define BMC22_PC3_Msk           SYS_GPC_MFP0_PC3MFP_Msk        /*!< BMC22           PC3      MFP Mask */
#define BMC23_PC2_Msk           SYS_GPC_MFP0_PC2MFP_Msk        /*!< BMC23           PC2      MFP Mask */
#define BMC23_PB8_Msk           SYS_GPB_MFP2_PB8MFP_Msk        /*!< BMC23           PB8      MFP Mask */
#define BMC24_PC1_Msk           SYS_GPC_MFP0_PC1MFP_Msk        /*!< BMC24           PC1      MFP Mask */
#define BMC24_PC7_Msk           SYS_GPC_MFP1_PC7MFP_Msk        /*!< BMC24           PC7      MFP Mask */
#define BMC25_PC6_Msk           SYS_GPC_MFP1_PC6MFP_Msk        /*!< BMC25           PC6      MFP Mask */
#define BMC25_PC0_Msk           SYS_GPC_MFP0_PC0MFP_Msk        /*!< BMC25           PC0      MFP Mask */
#define BMC26_PC14_Msk          SYS_GPC_MFP3_PC14MFP_Msk       /*!< BMC26           PC14     MFP Mask */
#define BMC27_PB15_Msk          SYS_GPB_MFP3_PB15MFP_Msk       /*!< BMC27           PB15     MFP Mask */
#define BMC28_PB13_Msk          SYS_GPB_MFP3_PB13MFP_Msk       /*!< BMC28           PB13     MFP Mask */
#define BMC29_PB12_Msk          SYS_GPB_MFP3_PB12MFP_Msk       /*!< BMC29           PB12     MFP Mask */
#define BMC3_PB2_Msk            SYS_GPB_MFP0_PB2MFP_Msk        /*!< BMC3            PB2      MFP Mask */
#define BMC30_PB7_Msk           SYS_GPB_MFP1_PB7MFP_Msk        /*!< BMC30           PB7      MFP Mask */
#define BMC31_PB6_Msk           SYS_GPB_MFP1_PB6MFP_Msk        /*!< BMC31           PB6      MFP Mask */
#define BMC4_PB1_Msk            SYS_GPB_MFP0_PB1MFP_Msk        /*!< BMC4            PB1      MFP Mask */
#define BMC5_PB0_Msk            SYS_GPB_MFP0_PB0MFP_Msk        /*!< BMC5            PB0      MFP Mask */
#define BMC6_PA11_Msk           SYS_GPA_MFP2_PA11MFP_Msk       /*!< BMC6            PA11     MFP Mask */
#define BMC7_PA10_Msk           SYS_GPA_MFP2_PA10MFP_Msk       /*!< BMC7            PA10     MFP Mask */
#define BMC8_PA9_Msk            SYS_GPA_MFP2_PA9MFP_Msk        /*!< BMC8            PA9      MFP Mask */
#define BMC9_PA8_Msk            SYS_GPA_MFP2_PA8MFP_Msk        /*!< BMC9            PA8      MFP Mask */
#define BPWM0_CH0_PD13_Msk      SYS_GPD_MFP3_PD13MFP_Msk       /*<! BPWM0_CH0       PD13     MFP Mask */
#define BPWM0_CH0_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! BPWM0_CH0       PE2      MFP Mask */
#define BPWM0_CH0_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! BPWM0_CH0       PA0      MFP Mask */
#define BPWM0_CH0_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! BPWM0_CH0       PA11     MFP Mask */
#define BPWM0_CH0_PG14_Msk      SYS_GPG_MFP3_PG14MFP_Msk       /*<! BPWM0_CH0       PG14     MFP Mask */
#define BPWM0_CH0_PJ13_Msk      SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! BPWM0_CH0       PJ13     MFP Mask */
#define BPWM0_CH1_PE3_Msk       SYS_GPE_MFP0_PE3MFP_Msk        /*<! BPWM0_CH1       PE3      MFP Mask */
#define BPWM0_CH1_PG13_Msk      SYS_GPG_MFP3_PG13MFP_Msk       /*<! BPWM0_CH1       PG13     MFP Mask */
#define BPWM0_CH1_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! BPWM0_CH1       PA1      MFP Mask */
#define BPWM0_CH1_PJ12_Msk      SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! BPWM0_CH1       PJ12     MFP Mask */
#define BPWM0_CH1_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! BPWM0_CH1       PA10     MFP Mask */
#define BPWM0_CH2_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! BPWM0_CH2       PA9      MFP Mask */
#define BPWM0_CH2_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! BPWM0_CH2       PA2      MFP Mask */
#define BPWM0_CH2_PJ11_Msk      SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! BPWM0_CH2       PJ11     MFP Mask */
#define BPWM0_CH2_PE4_Msk       SYS_GPE_MFP1_PE4MFP_Msk        /*<! BPWM0_CH2       PE4      MFP Mask */
#define BPWM0_CH2_PG12_Msk      SYS_GPG_MFP3_PG12MFP_Msk       /*<! BPWM0_CH2       PG12     MFP Mask */
#define BPWM0_CH3_PE5_Msk       SYS_GPE_MFP1_PE5MFP_Msk        /*<! BPWM0_CH3       PE5      MFP Mask */
#define BPWM0_CH3_PJ10_Msk      SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! BPWM0_CH3       PJ10     MFP Mask */
#define BPWM0_CH3_PG11_Msk      SYS_GPG_MFP2_PG11MFP_Msk       /*<! BPWM0_CH3       PG11     MFP Mask */
#define BPWM0_CH3_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! BPWM0_CH3       PA8      MFP Mask */
#define BPWM0_CH3_PA3_Msk       SYS_GPA_MFP0_PA3MFP_Msk        /*<! BPWM0_CH3       PA3      MFP Mask */
#define BPWM0_CH4_PF5_Msk       SYS_GPF_MFP1_PF5MFP_Msk        /*<! BPWM0_CH4       PF5      MFP Mask */
#define BPWM0_CH4_PJ9_Msk       SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! BPWM0_CH4       PJ9      MFP Mask */
#define BPWM0_CH4_PG10_Msk      SYS_GPG_MFP2_PG10MFP_Msk       /*<! BPWM0_CH4       PG10     MFP Mask */
#define BPWM0_CH4_PC13_Msk      SYS_GPC_MFP3_PC13MFP_Msk       /*<! BPWM0_CH4       PC13     MFP Mask */
#define BPWM0_CH4_PA4_Msk       SYS_GPA_MFP1_PA4MFP_Msk        /*<! BPWM0_CH4       PA4      MFP Mask */
#define BPWM0_CH4_PE6_Msk       SYS_GPE_MFP1_PE6MFP_Msk        /*<! BPWM0_CH4       PE6      MFP Mask */
#define BPWM0_CH5_PJ8_Msk       SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! BPWM0_CH5       PJ8      MFP Mask */
#define BPWM0_CH5_PD12_Msk      SYS_GPD_MFP3_PD12MFP_Msk       /*<! BPWM0_CH5       PD12     MFP Mask */
#define BPWM0_CH5_PA5_Msk       SYS_GPA_MFP1_PA5MFP_Msk        /*<! BPWM0_CH5       PA5      MFP Mask */
#define BPWM0_CH5_PF4_Msk       SYS_GPF_MFP1_PF4MFP_Msk        /*<! BPWM0_CH5       PF4      MFP Mask */
#define BPWM0_CH5_PE7_Msk       SYS_GPE_MFP1_PE7MFP_Msk        /*<! BPWM0_CH5       PE7      MFP Mask */
#define BPWM0_CH5_PG9_Msk       SYS_GPG_MFP2_PG9MFP_Msk        /*<! BPWM0_CH5       PG9      MFP Mask */
#define BPWM1_CH0_PF3_Msk       SYS_GPF_MFP0_PF3MFP_Msk        /*<! BPWM1_CH0       PF3      MFP Mask */
#define BPWM1_CH0_PB11_Msk      SYS_GPB_MFP2_PB11MFP_Msk       /*<! BPWM1_CH0       PB11     MFP Mask */
#define BPWM1_CH0_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! BPWM1_CH0       PC7      MFP Mask */
#define BPWM1_CH0_PF0_Msk       SYS_GPF_MFP0_PF0MFP_Msk        /*<! BPWM1_CH0       PF0      MFP Mask */
#define BPWM1_CH1_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! BPWM1_CH1       PF1      MFP Mask */
#define BPWM1_CH1_PB10_Msk      SYS_GPB_MFP2_PB10MFP_Msk       /*<! BPWM1_CH1       PB10     MFP Mask */
#define BPWM1_CH1_PF2_Msk       SYS_GPF_MFP0_PF2MFP_Msk        /*<! BPWM1_CH1       PF2      MFP Mask */
#define BPWM1_CH1_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! BPWM1_CH1       PC6      MFP Mask */
#define BPWM1_CH2_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! BPWM1_CH2       PB9      MFP Mask */
#define BPWM1_CH2_PA7_Msk       SYS_GPA_MFP1_PA7MFP_Msk        /*<! BPWM1_CH2       PA7      MFP Mask */
#define BPWM1_CH2_PA12_Msk      SYS_GPA_MFP3_PA12MFP_Msk       /*<! BPWM1_CH2       PA12     MFP Mask */
#define BPWM1_CH3_PA6_Msk       SYS_GPA_MFP1_PA6MFP_Msk        /*<! BPWM1_CH3       PA6      MFP Mask */
#define BPWM1_CH3_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! BPWM1_CH3       PB8      MFP Mask */
#define BPWM1_CH3_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! BPWM1_CH3       PA13     MFP Mask */
#define BPWM1_CH4_PB7_Msk       SYS_GPB_MFP1_PB7MFP_Msk        /*<! BPWM1_CH4       PB7      MFP Mask */
#define BPWM1_CH4_PC8_Msk       SYS_GPC_MFP2_PC8MFP_Msk        /*<! BPWM1_CH4       PC8      MFP Mask */
#define BPWM1_CH4_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! BPWM1_CH4       PA14     MFP Mask */
#define BPWM1_CH5_PB6_Msk       SYS_GPB_MFP1_PB6MFP_Msk        /*<! BPWM1_CH5       PB6      MFP Mask */
#define BPWM1_CH5_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! BPWM1_CH5       PE13     MFP Mask */
#define BPWM1_CH5_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! BPWM1_CH5       PA15     MFP Mask */
#define CAN0_RXD_PI13_Msk       SYS_GPI_MFP3_PI13MFP_Msk       /*<! CAN0_RXD        PI13     MFP Mask */
#define CAN0_RXD_PJ3_Msk        SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! CAN0_RXD        PJ3      MFP Mask */
#define CAN0_RXD_PA4_Msk        SYS_GPA_MFP1_PA4MFP_Msk        /*<! CAN0_RXD        PA4      MFP Mask */
#define CAN0_RXD_PE15_Msk       SYS_GPE_MFP3_PE15MFP_Msk       /*<! CAN0_RXD        PE15     MFP Mask */
#define CAN0_RXD_PA13_Msk       SYS_GPA_MFP3_PA13MFP_Msk       /*<! CAN0_RXD        PA13     MFP Mask */
#define CAN0_RXD_PJ11_Msk       SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! CAN0_RXD        PJ11     MFP Mask */
#define CAN0_RXD_PC4_Msk        SYS_GPC_MFP1_PC4MFP_Msk        /*<! CAN0_RXD        PC4      MFP Mask */
#define CAN0_RXD_PB10_Msk       SYS_GPB_MFP2_PB10MFP_Msk       /*<! CAN0_RXD        PB10     MFP Mask */
#define CAN0_RXD_PD10_Msk       SYS_GPD_MFP2_PD10MFP_Msk       /*<! CAN0_RXD        PD10     MFP Mask */
#define CAN0_TXD_PC5_Msk        SYS_GPC_MFP1_PC5MFP_Msk        /*<! CAN0_TXD        PC5      MFP Mask */
#define CAN0_TXD_PB11_Msk       SYS_GPB_MFP2_PB11MFP_Msk       /*<! CAN0_TXD        PB11     MFP Mask */
#define CAN0_TXD_PA5_Msk        SYS_GPA_MFP1_PA5MFP_Msk        /*<! CAN0_TXD        PA5      MFP Mask */
#define CAN0_TXD_PJ10_Msk       SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! CAN0_TXD        PJ10     MFP Mask */
#define CAN0_TXD_PD11_Msk       SYS_GPD_MFP2_PD11MFP_Msk       /*<! CAN0_TXD        PD11     MFP Mask */
#define CAN0_TXD_PA12_Msk       SYS_GPA_MFP3_PA12MFP_Msk       /*<! CAN0_TXD        PA12     MFP Mask */
#define CAN0_TXD_PI12_Msk       SYS_GPI_MFP3_PI12MFP_Msk       /*<! CAN0_TXD        PI12     MFP Mask */
#define CAN0_TXD_PE14_Msk       SYS_GPE_MFP3_PE14MFP_Msk       /*<! CAN0_TXD        PE14     MFP Mask */
#define CAN0_TXD_PJ2_Msk        SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! CAN0_TXD        PJ2      MFP Mask */
#define CAN1_RXD_PJ5_Msk        SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! CAN1_RXD        PJ5      MFP Mask */
#define CAN1_RXD_PC9_Msk        SYS_GPC_MFP2_PC9MFP_Msk        /*<! CAN1_RXD        PC9      MFP Mask */
#define CAN1_RXD_PD12_Msk       SYS_GPD_MFP3_PD12MFP_Msk       /*<! CAN1_RXD        PD12     MFP Mask */
#define CAN1_RXD_PF8_Msk        SYS_GPF_MFP2_PF8MFP_Msk        /*<! CAN1_RXD        PF8      MFP Mask */
#define CAN1_RXD_PG1_Msk        SYS_GPG_MFP0_PG1MFP_Msk        /*<! CAN1_RXD        PG1      MFP Mask */
#define CAN1_RXD_PB6_Msk        SYS_GPB_MFP1_PB6MFP_Msk        /*<! CAN1_RXD        PB6      MFP Mask */
#define CAN1_RXD_PI15_Msk       SYS_GPI_MFP3_PI15MFP_Msk       /*<! CAN1_RXD        PI15     MFP Mask */
#define CAN1_RXD_PC2_Msk        SYS_GPC_MFP0_PC2MFP_Msk        /*<! CAN1_RXD        PC2      MFP Mask */
#define CAN1_RXD_PJ13_Msk       SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! CAN1_RXD        PJ13     MFP Mask */
#define CAN1_RXD_PE6_Msk        SYS_GPE_MFP1_PE6MFP_Msk        /*<! CAN1_RXD        PE6      MFP Mask */
#define CAN1_TXD_PG0_Msk        SYS_GPG_MFP0_PG0MFP_Msk        /*<! CAN1_TXD        PG0      MFP Mask */
#define CAN1_TXD_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! CAN1_TXD        PB7      MFP Mask */
#define CAN1_TXD_PC3_Msk        SYS_GPC_MFP0_PC3MFP_Msk        /*<! CAN1_TXD        PC3      MFP Mask */
#define CAN1_TXD_PI14_Msk       SYS_GPI_MFP3_PI14MFP_Msk       /*<! CAN1_TXD        PI14     MFP Mask */
#define CAN1_TXD_PC10_Msk       SYS_GPC_MFP2_PC10MFP_Msk       /*<! CAN1_TXD        PC10     MFP Mask */
#define CAN1_TXD_PE7_Msk        SYS_GPE_MFP1_PE7MFP_Msk        /*<! CAN1_TXD        PE7      MFP Mask */
#define CAN1_TXD_PJ12_Msk       SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! CAN1_TXD        PJ12     MFP Mask */
#define CAN1_TXD_PC13_Msk       SYS_GPC_MFP3_PC13MFP_Msk       /*<! CAN1_TXD        PC13     MFP Mask */
#define CAN1_TXD_PJ4_Msk        SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! CAN1_TXD        PJ4      MFP Mask */
#define CAN1_TXD_PF9_Msk        SYS_GPF_MFP2_PF9MFP_Msk        /*<! CAN1_TXD        PF9      MFP Mask */
#define CAN2_RXD_PF1_Msk        SYS_GPF_MFP0_PF1MFP_Msk        /*<! CAN2_RXD        PF1      MFP Mask */
#define CAN2_RXD_PJ1_Msk        SYS_GPJ_MFP0_PJ1MFP_Msk        /*<! CAN2_RXD        PJ1      MFP Mask */
#define CAN2_RXD_PF6_Msk        SYS_GPF_MFP1_PF6MFP_Msk        /*<! CAN2_RXD        PF6      MFP Mask */
#define CAN2_RXD_PI9_Msk        SYS_GPI_MFP2_PI9MFP_Msk        /*<! CAN2_RXD        PI9      MFP Mask */
#define CAN2_RXD_PD8_Msk        SYS_GPD_MFP2_PD8MFP_Msk        /*<! CAN2_RXD        PD8      MFP Mask */
#define CAN2_RXD_PB8_Msk        SYS_GPB_MFP2_PB8MFP_Msk        /*<! CAN2_RXD        PB8      MFP Mask */
#define CAN2_RXD_PJ7_Msk        SYS_GPJ_MFP1_PJ7MFP_Msk        /*<! CAN2_RXD        PJ7      MFP Mask */
#define CAN2_RXD_PC0_Msk        SYS_GPC_MFP0_PC0MFP_Msk        /*<! CAN2_RXD        PC0      MFP Mask */
#define CAN2_RXD_PJ9_Msk        SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! CAN2_RXD        PJ9      MFP Mask */
#define CAN2_TXD_PB9_Msk        SYS_GPB_MFP2_PB9MFP_Msk        /*<! CAN2_TXD        PB9      MFP Mask */
#define CAN2_TXD_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! CAN2_TXD        PC1      MFP Mask */
#define CAN2_TXD_PD9_Msk        SYS_GPD_MFP2_PD9MFP_Msk        /*<! CAN2_TXD        PD9      MFP Mask */
#define CAN2_TXD_PF0_Msk        SYS_GPF_MFP0_PF0MFP_Msk        /*<! CAN2_TXD        PF0      MFP Mask */
#define CAN2_TXD_PJ6_Msk        SYS_GPJ_MFP1_PJ6MFP_Msk        /*<! CAN2_TXD        PJ6      MFP Mask */
#define CAN2_TXD_PF7_Msk        SYS_GPF_MFP1_PF7MFP_Msk        /*<! CAN2_TXD        PF7      MFP Mask */
#define CAN2_TXD_PJ8_Msk        SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! CAN2_TXD        PJ8      MFP Mask */
#define CAN2_TXD_PJ0_Msk        SYS_GPJ_MFP0_PJ0MFP_Msk        /*<! CAN2_TXD        PJ0      MFP Mask */
#define CAN2_TXD_PI8_Msk        SYS_GPI_MFP2_PI8MFP_Msk        /*<! CAN2_TXD        PI8      MFP Mask */
#define CAN3_RXD_PC6_Msk        SYS_GPC_MFP1_PC6MFP_Msk        /*<! CAN3_RXD        PC6      MFP Mask */
#define CAN3_RXD_PH13_Msk       SYS_GPH_MFP3_PH13MFP_Msk       /*<! CAN3_RXD        PH13     MFP Mask */
#define CAN3_RXD_PI7_Msk        SYS_GPI_MFP1_PI7MFP_Msk        /*<! CAN3_RXD        PI7      MFP Mask */
#define CAN3_RXD_PF10_Msk       SYS_GPF_MFP2_PF10MFP_Msk       /*<! CAN3_RXD        PF10     MFP Mask */
#define CAN3_RXD_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! CAN3_RXD        PB12     MFP Mask */
#define CAN3_RXD_PI11_Msk       SYS_GPI_MFP2_PI11MFP_Msk       /*<! CAN3_RXD        PI11     MFP Mask */
#define CAN3_TXD_PI6_Msk        SYS_GPI_MFP1_PI6MFP_Msk        /*<! CAN3_TXD        PI6      MFP Mask */
#define CAN3_TXD_PC7_Msk        SYS_GPC_MFP1_PC7MFP_Msk        /*<! CAN3_TXD        PC7      MFP Mask */
#define CAN3_TXD_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! CAN3_TXD        PB13     MFP Mask */
#define CAN3_TXD_PH12_Msk       SYS_GPH_MFP3_PH12MFP_Msk       /*<! CAN3_TXD        PH12     MFP Mask */
#define CAN3_TXD_PI10_Msk       SYS_GPI_MFP2_PI10MFP_Msk       /*<! CAN3_TXD        PI10     MFP Mask */
#define CAN3_TXD_PF11_Msk       SYS_GPF_MFP2_PF11MFP_Msk       /*<! CAN3_TXD        PF11     MFP Mask */
#define CCAP_DATA0_PB14_Msk     SYS_GPB_MFP3_PB14MFP_Msk       /*<! CCAP_DATA0      PB14     MFP Mask */
#define CCAP_DATA0_PC0_Msk      SYS_GPC_MFP0_PC0MFP_Msk        /*<! CCAP_DATA0      PC0      MFP Mask */
#define CCAP_DATA0_PJ7_Msk      SYS_GPJ_MFP1_PJ7MFP_Msk        /*<! CCAP_DATA0      PJ7      MFP Mask */
#define CCAP_DATA0_PF7_Msk      SYS_GPF_MFP1_PF7MFP_Msk        /*<! CCAP_DATA0      PF7      MFP Mask */
#define CCAP_DATA1_PJ6_Msk      SYS_GPJ_MFP1_PJ6MFP_Msk        /*<! CCAP_DATA1      PJ6      MFP Mask */
#define CCAP_DATA1_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! CCAP_DATA1      PB15     MFP Mask */
#define CCAP_DATA1_PC1_Msk      SYS_GPC_MFP0_PC1MFP_Msk        /*<! CCAP_DATA1      PC1      MFP Mask */
#define CCAP_DATA1_PF8_Msk      SYS_GPF_MFP2_PF8MFP_Msk        /*<! CCAP_DATA1      PF8      MFP Mask */
#define CCAP_DATA2_PJ5_Msk      SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! CCAP_DATA2      PJ5      MFP Mask */
#define CCAP_DATA2_PC2_Msk      SYS_GPC_MFP0_PC2MFP_Msk        /*<! CCAP_DATA2      PC2      MFP Mask */
#define CCAP_DATA2_PF9_Msk      SYS_GPF_MFP2_PF9MFP_Msk        /*<! CCAP_DATA2      PF9      MFP Mask */
#define CCAP_DATA3_PF10_Msk     SYS_GPF_MFP2_PF10MFP_Msk       /*<! CCAP_DATA3      PF10     MFP Mask */
#define CCAP_DATA3_PJ4_Msk      SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! CCAP_DATA3      PJ4      MFP Mask */
#define CCAP_DATA3_PC3_Msk      SYS_GPC_MFP0_PC3MFP_Msk        /*<! CCAP_DATA3      PC3      MFP Mask */
#define CCAP_DATA4_PC4_Msk      SYS_GPC_MFP1_PC4MFP_Msk        /*<! CCAP_DATA4      PC4      MFP Mask */
#define CCAP_DATA4_PF11_Msk     SYS_GPF_MFP2_PF11MFP_Msk       /*<! CCAP_DATA4      PF11     MFP Mask */
#define CCAP_DATA4_PJ3_Msk      SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! CCAP_DATA4      PJ3      MFP Mask */
#define CCAP_DATA5_PJ2_Msk      SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! CCAP_DATA5      PJ2      MFP Mask */
#define CCAP_DATA5_PC5_Msk      SYS_GPC_MFP1_PC5MFP_Msk        /*<! CCAP_DATA5      PC5      MFP Mask */
#define CCAP_DATA5_PG4_Msk      SYS_GPG_MFP1_PG4MFP_Msk        /*<! CCAP_DATA5      PG4      MFP Mask */
#define CCAP_DATA6_PG3_Msk      SYS_GPG_MFP0_PG3MFP_Msk        /*<! CCAP_DATA6      PG3      MFP Mask */
#define CCAP_DATA6_PA0_Msk      SYS_GPA_MFP0_PA0MFP_Msk        /*<! CCAP_DATA6      PA0      MFP Mask */
#define CCAP_DATA7_PA1_Msk      SYS_GPA_MFP0_PA1MFP_Msk        /*<! CCAP_DATA7      PA1      MFP Mask */
#define CCAP_DATA7_PG2_Msk      SYS_GPG_MFP0_PG2MFP_Msk        /*<! CCAP_DATA7      PG2      MFP Mask */
#define CCAP_HSYNC_PD7_Msk      SYS_GPD_MFP1_PD7MFP_Msk        /*<! CCAP_HSYNC      PD7      MFP Mask */
#define CCAP_HSYNC_PG13_Msk     SYS_GPG_MFP3_PG13MFP_Msk       /*<! CCAP_HSYNC      PG13     MFP Mask */
#define CCAP_HSYNC_PB9_Msk      SYS_GPB_MFP2_PB9MFP_Msk        /*<! CCAP_HSYNC      PB9      MFP Mask */
#define CCAP_PIXCLK_PH12_Msk    SYS_GPH_MFP3_PH12MFP_Msk       /*<! CCAP_PIXCLK     PH12     MFP Mask */
#define CCAP_PIXCLK_PG9_Msk     SYS_GPG_MFP2_PG9MFP_Msk        /*<! CCAP_PIXCLK     PG9      MFP Mask */
#define CCAP_PIXCLK_PB13_Msk    SYS_GPB_MFP3_PB13MFP_Msk       /*<! CCAP_PIXCLK     PB13     MFP Mask */
#define CCAP_SCLK_PG10_Msk      SYS_GPG_MFP2_PG10MFP_Msk       /*<! CCAP_SCLK       PG10     MFP Mask */
#define CCAP_SCLK_PH13_Msk      SYS_GPH_MFP3_PH13MFP_Msk       /*<! CCAP_SCLK       PH13     MFP Mask */
#define CCAP_SCLK_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! CCAP_SCLK       PB12     MFP Mask */
#define CCAP_SFIELD_PG11_Msk    SYS_GPG_MFP2_PG11MFP_Msk       /*<! CCAP_SFIELD     PG11     MFP Mask */
#define CCAP_SFIELD_PB11_Msk    SYS_GPB_MFP2_PB11MFP_Msk       /*<! CCAP_SFIELD     PB11     MFP Mask */
#define CCAP_SFIELD_PH14_Msk    SYS_GPH_MFP3_PH14MFP_Msk       /*<! CCAP_SFIELD     PH14     MFP Mask */
#define CCAP_VSYNC_PG12_Msk     SYS_GPG_MFP3_PG12MFP_Msk       /*<! CCAP_VSYNC      PG12     MFP Mask */
#define CCAP_VSYNC_PB10_Msk     SYS_GPB_MFP2_PB10MFP_Msk       /*<! CCAP_VSYNC      PB10     MFP Mask */
#define CCAP_VSYNC_PH15_Msk     SYS_GPH_MFP3_PH15MFP_Msk       /*<! CCAP_VSYNC      PH15     MFP Mask */
#define CLKO_PC13_Msk           SYS_GPC_MFP3_PC13MFP_Msk       /*<! CLKO            PC13     MFP Mask */
#define CLKO_PD13_Msk           SYS_GPD_MFP3_PD13MFP_Msk       /*<! CLKO            PD13     MFP Mask */
#define CLKO_PG15_Msk           SYS_GPG_MFP3_PG15MFP_Msk       /*<! CLKO            PG15     MFP Mask */
#define CLKO_PB14_Msk           SYS_GPB_MFP3_PB14MFP_Msk       /*<! CLKO            PB14     MFP Mask */
#define CLKO_PD12_Msk           SYS_GPD_MFP3_PD12MFP_Msk       /*<! CLKO            PD12     MFP Mask */
#define DAC0_OUT_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! DAC0_OUT        PB12     MFP Mask */
#define DAC0_ST_PA0_Msk         SYS_GPA_MFP0_PA0MFP_Msk        /*<! DAC0_ST         PA0      MFP Mask */
#define DAC0_ST_PA10_Msk        SYS_GPA_MFP2_PA10MFP_Msk       /*<! DAC0_ST         PA10     MFP Mask */
#define DAC1_OUT_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! DAC1_OUT        PB13     MFP Mask */
#define DAC1_ST_PA11_Msk        SYS_GPA_MFP2_PA11MFP_Msk       /*<! DAC1_ST         PA11     MFP Mask */
#define DAC1_ST_PA1_Msk         SYS_GPA_MFP0_PA1MFP_Msk        /*<! DAC1_ST         PA1      MFP Mask */
#define EADC0_CH0_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! EADC0_CH0       PB0      MFP Mask */
#define EADC0_CH1_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! EADC0_CH1       PB1      MFP Mask */
#define EADC0_CH10_PB10_Msk     SYS_GPB_MFP2_PB10MFP_Msk       /*<! EADC0_CH10      PB10     MFP Mask */
#define EADC0_CH11_PB11_Msk     SYS_GPB_MFP2_PB11MFP_Msk       /*<! EADC0_CH11      PB11     MFP Mask */
#define EADC0_CH12_PB12_Msk     SYS_GPB_MFP3_PB12MFP_Msk       /*<! EADC0_CH12      PB12     MFP Mask */
#define EADC0_CH13_PB13_Msk     SYS_GPB_MFP3_PB13MFP_Msk       /*<! EADC0_CH13      PB13     MFP Mask */
#define EADC0_CH14_PB14_Msk     SYS_GPB_MFP3_PB14MFP_Msk       /*<! EADC0_CH14      PB14     MFP Mask */
#define EADC0_CH15_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! EADC0_CH15      PB15     MFP Mask */
#define EADC0_CH2_PB2_Msk       SYS_GPB_MFP0_PB2MFP_Msk        /*<! EADC0_CH2       PB2      MFP Mask */
#define EADC0_CH3_PB3_Msk       SYS_GPB_MFP0_PB3MFP_Msk        /*<! EADC0_CH3       PB3      MFP Mask */
#define EADC0_CH4_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! EADC0_CH4       PB4      MFP Mask */
#define EADC0_CH5_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! EADC0_CH5       PB5      MFP Mask */
#define EADC0_CH6_PB6_Msk       SYS_GPB_MFP1_PB6MFP_Msk        /*<! EADC0_CH6       PB6      MFP Mask */
#define EADC0_CH7_PB7_Msk       SYS_GPB_MFP1_PB7MFP_Msk        /*<! EADC0_CH7       PB7      MFP Mask */
#define EADC0_CH8_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! EADC0_CH8       PB8      MFP Mask */
#define EADC0_CH9_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! EADC0_CH9       PB9      MFP Mask */
#define EADC0_ST_PF0_Msk        SYS_GPF_MFP0_PF0MFP_Msk        /*<! EADC0_ST        PF0      MFP Mask */
#define EADC0_ST_PD12_Msk       SYS_GPD_MFP3_PD12MFP_Msk       /*<! EADC0_ST        PD12     MFP Mask */
#define EADC0_ST_PD6_Msk        SYS_GPD_MFP1_PD6MFP_Msk        /*<! EADC0_ST        PD6      MFP Mask */
#define EADC0_ST_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! EADC0_ST        PC1      MFP Mask */
#define EADC0_ST_PF5_Msk        SYS_GPF_MFP1_PF5MFP_Msk        /*<! EADC0_ST        PF5      MFP Mask */
#define EADC0_ST_PG15_Msk       SYS_GPG_MFP3_PG15MFP_Msk       /*<! EADC0_ST        PG15     MFP Mask */
#define EADC0_ST_PD13_Msk       SYS_GPD_MFP3_PD13MFP_Msk       /*<! EADC0_ST        PD13     MFP Mask */
#define EADC0_ST_PC13_Msk       SYS_GPC_MFP3_PC13MFP_Msk       /*<! EADC0_ST        PC13     MFP Mask */
#define EADC1_CH0_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! EADC1_CH0       PD10     MFP Mask */
#define EADC1_CH1_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! EADC1_CH1       PD11     MFP Mask */
#define EADC1_CH10_PB2_Msk      SYS_GPB_MFP0_PB2MFP_Msk        /*<! EADC1_CH10      PB2      MFP Mask */
#define EADC1_CH11_PB3_Msk      SYS_GPB_MFP0_PB3MFP_Msk        /*<! EADC1_CH11      PB3      MFP Mask */
#define EADC1_CH12_PB12_Msk     SYS_GPB_MFP3_PB12MFP_Msk       /*<! EADC1_CH12      PB12     MFP Mask */
#define EADC1_CH13_PB13_Msk     SYS_GPB_MFP3_PB13MFP_Msk       /*<! EADC1_CH13      PB13     MFP Mask */
#define EADC1_CH14_PB14_Msk     SYS_GPB_MFP3_PB14MFP_Msk       /*<! EADC1_CH14      PB14     MFP Mask */
#define EADC1_CH15_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! EADC1_CH15      PB15     MFP Mask */
#define EADC1_CH2_PD12_Msk      SYS_GPD_MFP3_PD12MFP_Msk       /*<! EADC1_CH2       PD12     MFP Mask */
#define EADC1_CH3_PC13_Msk      SYS_GPC_MFP3_PC13MFP_Msk       /*<! EADC1_CH3       PC13     MFP Mask */
#define EADC1_CH4_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! EADC1_CH4       PA8      MFP Mask */
#define EADC1_CH5_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! EADC1_CH5       PA9      MFP Mask */
#define EADC1_CH6_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! EADC1_CH6       PA10     MFP Mask */
#define EADC1_CH7_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! EADC1_CH7       PA11     MFP Mask */
#define EADC1_CH8_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! EADC1_CH8       PB0      MFP Mask */
#define EADC1_CH9_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! EADC1_CH9       PB1      MFP Mask */
#define EADC1_ST_PC10_Msk       SYS_GPC_MFP2_PC10MFP_Msk       /*<! EADC1_ST        PC10     MFP Mask */
#define EADC1_ST_PD5_Msk        SYS_GPD_MFP1_PD5MFP_Msk        /*<! EADC1_ST        PD5      MFP Mask */
#define EADC1_ST_PC0_Msk        SYS_GPC_MFP0_PC0MFP_Msk        /*<! EADC1_ST        PC0      MFP Mask */
#define EADC1_ST_PF1_Msk        SYS_GPF_MFP0_PF1MFP_Msk        /*<! EADC1_ST        PF1      MFP Mask */
#define EADC1_ST_PF4_Msk        SYS_GPF_MFP1_PF4MFP_Msk        /*<! EADC1_ST        PF4      MFP Mask */
#define EADC1_ST_PC9_Msk        SYS_GPC_MFP2_PC9MFP_Msk        /*<! EADC1_ST        PC9      MFP Mask */
#define EADC2_CH0_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! EADC2_CH0       PD10     MFP Mask */
#define EADC2_CH1_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! EADC2_CH1       PD11     MFP Mask */
#define EADC2_CH10_PC9_Msk      SYS_GPC_MFP2_PC9MFP_Msk        /*<! EADC2_CH10      PC9      MFP Mask */
#define EADC2_CH11_PC10_Msk     SYS_GPC_MFP2_PC10MFP_Msk       /*<! EADC2_CH11      PC10     MFP Mask */
#define EADC2_CH12_PC11_Msk     SYS_GPC_MFP2_PC11MFP_Msk       /*<! EADC2_CH12      PC11     MFP Mask */
#define EADC2_CH13_PC12_Msk     SYS_GPC_MFP3_PC12MFP_Msk       /*<! EADC2_CH13      PC12     MFP Mask */
#define EADC2_CH14_PB6_Msk      SYS_GPB_MFP1_PB6MFP_Msk        /*<! EADC2_CH14      PB6      MFP Mask */
#define EADC2_CH15_PB7_Msk      SYS_GPB_MFP1_PB7MFP_Msk        /*<! EADC2_CH15      PB7      MFP Mask */
#define EADC2_CH2_PD12_Msk      SYS_GPD_MFP3_PD12MFP_Msk       /*<! EADC2_CH2       PD12     MFP Mask */
#define EADC2_CH3_PC13_Msk      SYS_GPC_MFP3_PC13MFP_Msk       /*<! EADC2_CH3       PC13     MFP Mask */
#define EADC2_CH4_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! EADC2_CH4       PA8      MFP Mask */
#define EADC2_CH5_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! EADC2_CH5       PA9      MFP Mask */
#define EADC2_CH6_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! EADC2_CH6       PA10     MFP Mask */
#define EADC2_CH7_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! EADC2_CH7       PA11     MFP Mask */
#define EADC2_CH8_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! EADC2_CH8       PB0      MFP Mask */
#define EADC2_CH9_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! EADC2_CH9       PB1      MFP Mask */
#define EADC2_ST_PF3_Msk        SYS_GPF_MFP0_PF3MFP_Msk        /*<! EADC2_ST        PF3      MFP Mask */
#define EADC2_ST_PB8_Msk        SYS_GPB_MFP2_PB8MFP_Msk        /*<! EADC2_ST        PB8      MFP Mask */
#define EBI_AD0_PJ7_Msk         SYS_GPJ_MFP1_PJ7MFP_Msk        /*<! EBI_AD0         PJ7      MFP Mask */
#define EBI_AD0_PF4_Msk         SYS_GPF_MFP1_PF4MFP_Msk        /*<! EBI_AD0         PF4      MFP Mask */
#define EBI_AD0_PG9_Msk         SYS_GPG_MFP2_PG9MFP_Msk        /*<! EBI_AD0         PG9      MFP Mask */
#define EBI_AD0_PC0_Msk         SYS_GPC_MFP0_PC0MFP_Msk        /*<! EBI_AD0         PC0      MFP Mask */
#define EBI_AD0_PH12_Msk        SYS_GPH_MFP3_PH12MFP_Msk       /*<! EBI_AD0         PH12     MFP Mask */
#define EBI_AD1_PC1_Msk         SYS_GPC_MFP0_PC1MFP_Msk        /*<! EBI_AD1         PC1      MFP Mask */
#define EBI_AD1_PH13_Msk        SYS_GPH_MFP3_PH13MFP_Msk       /*<! EBI_AD1         PH13     MFP Mask */
#define EBI_AD1_PJ6_Msk         SYS_GPJ_MFP1_PJ6MFP_Msk        /*<! EBI_AD1         PJ6      MFP Mask */
#define EBI_AD1_PG10_Msk        SYS_GPG_MFP2_PG10MFP_Msk       /*<! EBI_AD1         PG10     MFP Mask */
#define EBI_AD1_PF5_Msk         SYS_GPF_MFP1_PF5MFP_Msk        /*<! EBI_AD1         PF5      MFP Mask */
#define EBI_AD10_PD3_Msk        SYS_GPD_MFP0_PD3MFP_Msk        /*<! EBI_AD10        PD3      MFP Mask */
#define EBI_AD10_PE1_Msk        SYS_GPE_MFP0_PE1MFP_Msk        /*<! EBI_AD10        PE1      MFP Mask */
#define EBI_AD10_PD13_Msk       SYS_GPD_MFP3_PD13MFP_Msk       /*<! EBI_AD10        PD13     MFP Mask */
#define EBI_AD11_PE0_Msk        SYS_GPE_MFP0_PE0MFP_Msk        /*<! EBI_AD11        PE0      MFP Mask */
#define EBI_AD11_PC14_Msk       SYS_GPC_MFP3_PC14MFP_Msk       /*<! EBI_AD11        PC14     MFP Mask */
#define EBI_AD11_PD2_Msk        SYS_GPD_MFP0_PD2MFP_Msk        /*<! EBI_AD11        PD2      MFP Mask */
#define EBI_AD12_PD1_Msk        SYS_GPD_MFP0_PD1MFP_Msk        /*<! EBI_AD12        PD1      MFP Mask */
#define EBI_AD12_PH8_Msk        SYS_GPH_MFP2_PH8MFP_Msk        /*<! EBI_AD12        PH8      MFP Mask */
#define EBI_AD12_PB15_Msk       SYS_GPB_MFP3_PB15MFP_Msk       /*<! EBI_AD12        PB15     MFP Mask */
#define EBI_AD13_PD0_Msk        SYS_GPD_MFP0_PD0MFP_Msk        /*<! EBI_AD13        PD0      MFP Mask */
#define EBI_AD13_PH9_Msk        SYS_GPH_MFP2_PH9MFP_Msk        /*<! EBI_AD13        PH9      MFP Mask */
#define EBI_AD13_PB14_Msk       SYS_GPB_MFP3_PB14MFP_Msk       /*<! EBI_AD13        PB14     MFP Mask */
#define EBI_AD14_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! EBI_AD14        PB13     MFP Mask */
#define EBI_AD14_PH10_Msk       SYS_GPH_MFP2_PH10MFP_Msk       /*<! EBI_AD14        PH10     MFP Mask */
#define EBI_AD15_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! EBI_AD15        PB12     MFP Mask */
#define EBI_AD15_PH11_Msk       SYS_GPH_MFP2_PH11MFP_Msk       /*<! EBI_AD15        PH11     MFP Mask */
#define EBI_AD2_PH14_Msk        SYS_GPH_MFP3_PH14MFP_Msk       /*<! EBI_AD2         PH14     MFP Mask */
#define EBI_AD2_PG11_Msk        SYS_GPG_MFP2_PG11MFP_Msk       /*<! EBI_AD2         PG11     MFP Mask */
#define EBI_AD2_PC2_Msk         SYS_GPC_MFP0_PC2MFP_Msk        /*<! EBI_AD2         PC2      MFP Mask */
#define EBI_AD2_PJ5_Msk         SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! EBI_AD2         PJ5      MFP Mask */
#define EBI_AD3_PJ4_Msk         SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! EBI_AD3         PJ4      MFP Mask */
#define EBI_AD3_PH15_Msk        SYS_GPH_MFP3_PH15MFP_Msk       /*<! EBI_AD3         PH15     MFP Mask */
#define EBI_AD3_PG12_Msk        SYS_GPG_MFP3_PG12MFP_Msk       /*<! EBI_AD3         PG12     MFP Mask */
#define EBI_AD3_PC3_Msk         SYS_GPC_MFP0_PC3MFP_Msk        /*<! EBI_AD3         PC3      MFP Mask */
#define EBI_AD4_PG13_Msk        SYS_GPG_MFP3_PG13MFP_Msk       /*<! EBI_AD4         PG13     MFP Mask */
#define EBI_AD4_PJ3_Msk         SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! EBI_AD4         PJ3      MFP Mask */
#define EBI_AD4_PD7_Msk         SYS_GPD_MFP1_PD7MFP_Msk        /*<! EBI_AD4         PD7      MFP Mask */
#define EBI_AD4_PC4_Msk         SYS_GPC_MFP1_PC4MFP_Msk        /*<! EBI_AD4         PC4      MFP Mask */
#define EBI_AD5_PJ2_Msk         SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! EBI_AD5         PJ2      MFP Mask */
#define EBI_AD5_PA14_Msk        SYS_GPA_MFP3_PA14MFP_Msk       /*<! EBI_AD5         PA14     MFP Mask */
#define EBI_AD5_PD6_Msk         SYS_GPD_MFP1_PD6MFP_Msk        /*<! EBI_AD5         PD6      MFP Mask */
#define EBI_AD5_PG14_Msk        SYS_GPG_MFP3_PG14MFP_Msk       /*<! EBI_AD5         PG14     MFP Mask */
#define EBI_AD5_PC5_Msk         SYS_GPC_MFP1_PC5MFP_Msk        /*<! EBI_AD5         PC5      MFP Mask */
#define EBI_AD6_PD8_Msk         SYS_GPD_MFP2_PD8MFP_Msk        /*<! EBI_AD6         PD8      MFP Mask */
#define EBI_AD6_PA6_Msk         SYS_GPA_MFP1_PA6MFP_Msk        /*<! EBI_AD6         PA6      MFP Mask */
#define EBI_AD7_PA7_Msk         SYS_GPA_MFP1_PA7MFP_Msk        /*<! EBI_AD7         PA7      MFP Mask */
#define EBI_AD7_PD9_Msk         SYS_GPD_MFP2_PD9MFP_Msk        /*<! EBI_AD7         PD9      MFP Mask */
#define EBI_AD8_PC6_Msk         SYS_GPC_MFP1_PC6MFP_Msk        /*<! EBI_AD8         PC6      MFP Mask */
#define EBI_AD8_PE14_Msk        SYS_GPE_MFP3_PE14MFP_Msk       /*<! EBI_AD8         PE14     MFP Mask */
#define EBI_AD9_PE15_Msk        SYS_GPE_MFP3_PE15MFP_Msk       /*<! EBI_AD9         PE15     MFP Mask */
#define EBI_AD9_PC7_Msk         SYS_GPC_MFP1_PC7MFP_Msk        /*<! EBI_AD9         PC7      MFP Mask */
#define EBI_ADR0_PB5_Msk        SYS_GPB_MFP1_PB5MFP_Msk        /*<! EBI_ADR0        PB5      MFP Mask */
#define EBI_ADR0_PH7_Msk        SYS_GPH_MFP1_PH7MFP_Msk        /*<! EBI_ADR0        PH7      MFP Mask */
#define EBI_ADR1_PH6_Msk        SYS_GPH_MFP1_PH6MFP_Msk        /*<! EBI_ADR1        PH6      MFP Mask */
#define EBI_ADR1_PB4_Msk        SYS_GPB_MFP1_PB4MFP_Msk        /*<! EBI_ADR1        PB4      MFP Mask */
#define EBI_ADR10_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! EBI_ADR10       PE8      MFP Mask */
#define EBI_ADR10_PC13_Msk      SYS_GPC_MFP3_PC13MFP_Msk       /*<! EBI_ADR10       PC13     MFP Mask */
#define EBI_ADR11_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! EBI_ADR11       PE9      MFP Mask */
#define EBI_ADR11_PG2_Msk       SYS_GPG_MFP0_PG2MFP_Msk        /*<! EBI_ADR11       PG2      MFP Mask */
#define EBI_ADR12_PG3_Msk       SYS_GPG_MFP0_PG3MFP_Msk        /*<! EBI_ADR12       PG3      MFP Mask */
#define EBI_ADR12_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! EBI_ADR12       PE10     MFP Mask */
#define EBI_ADR13_PE11_Msk      SYS_GPE_MFP2_PE11MFP_Msk       /*<! EBI_ADR13       PE11     MFP Mask */
#define EBI_ADR13_PG4_Msk       SYS_GPG_MFP1_PG4MFP_Msk        /*<! EBI_ADR13       PG4      MFP Mask */
#define EBI_ADR14_PF11_Msk      SYS_GPF_MFP2_PF11MFP_Msk       /*<! EBI_ADR14       PF11     MFP Mask */
#define EBI_ADR14_PE12_Msk      SYS_GPE_MFP3_PE12MFP_Msk       /*<! EBI_ADR14       PE12     MFP Mask */
#define EBI_ADR15_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! EBI_ADR15       PE13     MFP Mask */
#define EBI_ADR15_PF10_Msk      SYS_GPF_MFP2_PF10MFP_Msk       /*<! EBI_ADR15       PF10     MFP Mask */
#define EBI_ADR16_PB11_Msk      SYS_GPB_MFP2_PB11MFP_Msk       /*<! EBI_ADR16       PB11     MFP Mask */
#define EBI_ADR16_PC8_Msk       SYS_GPC_MFP2_PC8MFP_Msk        /*<! EBI_ADR16       PC8      MFP Mask */
#define EBI_ADR16_PF9_Msk       SYS_GPF_MFP2_PF9MFP_Msk        /*<! EBI_ADR16       PF9      MFP Mask */
#define EBI_ADR17_PB10_Msk      SYS_GPB_MFP2_PB10MFP_Msk       /*<! EBI_ADR17       PB10     MFP Mask */
#define EBI_ADR17_PF8_Msk       SYS_GPF_MFP2_PF8MFP_Msk        /*<! EBI_ADR17       PF8      MFP Mask */
#define EBI_ADR18_PF7_Msk       SYS_GPF_MFP1_PF7MFP_Msk        /*<! EBI_ADR18       PF7      MFP Mask */
#define EBI_ADR18_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! EBI_ADR18       PB9      MFP Mask */
#define EBI_ADR19_PF6_Msk       SYS_GPF_MFP1_PF6MFP_Msk        /*<! EBI_ADR19       PF6      MFP Mask */
#define EBI_ADR19_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! EBI_ADR19       PB8      MFP Mask */
#define EBI_ADR2_PB3_Msk        SYS_GPB_MFP0_PB3MFP_Msk        /*<! EBI_ADR2        PB3      MFP Mask */
#define EBI_ADR2_PH5_Msk        SYS_GPH_MFP1_PH5MFP_Msk        /*<! EBI_ADR2        PH5      MFP Mask */
#define EBI_ADR3_PH4_Msk        SYS_GPH_MFP1_PH4MFP_Msk        /*<! EBI_ADR3        PH4      MFP Mask */
#define EBI_ADR3_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! EBI_ADR3        PB2      MFP Mask */
#define EBI_ADR4_PC12_Msk       SYS_GPC_MFP3_PC12MFP_Msk       /*<! EBI_ADR4        PC12     MFP Mask */
#define EBI_ADR4_PH3_Msk        SYS_GPH_MFP0_PH3MFP_Msk        /*<! EBI_ADR4        PH3      MFP Mask */
#define EBI_ADR5_PH2_Msk        SYS_GPH_MFP0_PH2MFP_Msk        /*<! EBI_ADR5        PH2      MFP Mask */
#define EBI_ADR5_PC11_Msk       SYS_GPC_MFP2_PC11MFP_Msk       /*<! EBI_ADR5        PC11     MFP Mask */
#define EBI_ADR6_PC10_Msk       SYS_GPC_MFP2_PC10MFP_Msk       /*<! EBI_ADR6        PC10     MFP Mask */
#define EBI_ADR6_PH1_Msk        SYS_GPH_MFP0_PH1MFP_Msk        /*<! EBI_ADR6        PH1      MFP Mask */
#define EBI_ADR7_PH0_Msk        SYS_GPH_MFP0_PH0MFP_Msk        /*<! EBI_ADR7        PH0      MFP Mask */
#define EBI_ADR7_PC9_Msk        SYS_GPC_MFP2_PC9MFP_Msk        /*<! EBI_ADR7        PC9      MFP Mask */
#define EBI_ADR8_PG0_Msk        SYS_GPG_MFP0_PG0MFP_Msk        /*<! EBI_ADR8        PG0      MFP Mask */
#define EBI_ADR8_PB1_Msk        SYS_GPB_MFP0_PB1MFP_Msk        /*<! EBI_ADR8        PB1      MFP Mask */
#define EBI_ADR9_PB0_Msk        SYS_GPB_MFP0_PB0MFP_Msk        /*<! EBI_ADR9        PB0      MFP Mask */
#define EBI_ADR9_PG1_Msk        SYS_GPG_MFP0_PG1MFP_Msk        /*<! EBI_ADR9        PG1      MFP Mask */
#define EBI_ALE_PA8_Msk         SYS_GPA_MFP2_PA8MFP_Msk        /*<! EBI_ALE         PA8      MFP Mask */
#define EBI_ALE_PE2_Msk         SYS_GPE_MFP0_PE2MFP_Msk        /*<! EBI_ALE         PE2      MFP Mask */
#define EBI_ALE_PJ11_Msk        SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! EBI_ALE         PJ11     MFP Mask */
#define EBI_MCLK_PE3_Msk        SYS_GPE_MFP0_PE3MFP_Msk        /*<! EBI_MCLK        PE3      MFP Mask */
#define EBI_MCLK_PA9_Msk        SYS_GPA_MFP2_PA9MFP_Msk        /*<! EBI_MCLK        PA9      MFP Mask */
#define EBI_MCLK_PJ10_Msk       SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! EBI_MCLK        PJ10     MFP Mask */
#define EBI_nCS0_PF3_Msk        SYS_GPF_MFP0_PF3MFP_Msk        /*<! EBI_nCS0        PF3      MFP Mask */
#define EBI_nCS0_PJ12_Msk       SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! EBI_nCS0        PJ12     MFP Mask */
#define EBI_nCS0_PD14_Msk       SYS_GPD_MFP3_PD14MFP_Msk       /*<! EBI_nCS0        PD14     MFP Mask */
#define EBI_nCS0_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! EBI_nCS0        PB7      MFP Mask */
#define EBI_nCS0_PF6_Msk        SYS_GPF_MFP1_PF6MFP_Msk        /*<! EBI_nCS0        PF6      MFP Mask */
#define EBI_nCS0_PD12_Msk       SYS_GPD_MFP3_PD12MFP_Msk       /*<! EBI_nCS0        PD12     MFP Mask */
#define EBI_nCS1_PB6_Msk        SYS_GPB_MFP1_PB6MFP_Msk        /*<! EBI_nCS1        PB6      MFP Mask */
#define EBI_nCS1_PG5_Msk        SYS_GPG_MFP1_PG5MFP_Msk        /*<! EBI_nCS1        PG5      MFP Mask */
#define EBI_nCS1_PD11_Msk       SYS_GPD_MFP2_PD11MFP_Msk       /*<! EBI_nCS1        PD11     MFP Mask */
#define EBI_nCS1_PF2_Msk        SYS_GPF_MFP0_PF2MFP_Msk        /*<! EBI_nCS1        PF2      MFP Mask */
#define EBI_nCS2_PD10_Msk       SYS_GPD_MFP2_PD10MFP_Msk       /*<! EBI_nCS2        PD10     MFP Mask */
#define EBI_nCS2_PG6_Msk        SYS_GPG_MFP1_PG6MFP_Msk        /*<! EBI_nCS2        PG6      MFP Mask */
#define EBI_nRD_PA11_Msk        SYS_GPA_MFP2_PA11MFP_Msk       /*<! EBI_nRD         PA11     MFP Mask */
#define EBI_nRD_PE5_Msk         SYS_GPE_MFP1_PE5MFP_Msk        /*<! EBI_nRD         PE5      MFP Mask */
#define EBI_nRD_PJ8_Msk         SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! EBI_nRD         PJ8      MFP Mask */
#define EBI_nWR_PA10_Msk        SYS_GPA_MFP2_PA10MFP_Msk       /*<! EBI_nWR         PA10     MFP Mask */
#define EBI_nWR_PJ9_Msk         SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! EBI_nWR         PJ9      MFP Mask */
#define EBI_nWR_PE4_Msk         SYS_GPE_MFP1_PE4MFP_Msk        /*<! EBI_nWR         PE4      MFP Mask */
#define EBI_nWRH_PB6_Msk        SYS_GPB_MFP1_PB6MFP_Msk        /*<! EBI_nWRH        PB6      MFP Mask */
#define EBI_nWRH_PG8_Msk        SYS_GPG_MFP2_PG8MFP_Msk        /*<! EBI_nWRH        PG8      MFP Mask */
#define EBI_nWRL_PG7_Msk        SYS_GPG_MFP1_PG7MFP_Msk        /*<! EBI_nWRL        PG7      MFP Mask */
#define EBI_nWRL_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! EBI_nWRL        PB7      MFP Mask */
#define ECAP0_IC0_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! ECAP0_IC0       PE8      MFP Mask */
#define ECAP0_IC0_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! ECAP0_IC0       PA10     MFP Mask */
#define ECAP0_IC1_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! ECAP0_IC1       PA9      MFP Mask */
#define ECAP0_IC1_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! ECAP0_IC1       PE9      MFP Mask */
#define ECAP0_IC2_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! ECAP0_IC2       PE10     MFP Mask */
#define ECAP0_IC2_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! ECAP0_IC2       PA8      MFP Mask */
#define ECAP1_IC0_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! ECAP1_IC0       PE13     MFP Mask */
#define ECAP1_IC0_PC10_Msk      SYS_GPC_MFP2_PC10MFP_Msk       /*<! ECAP1_IC0       PC10     MFP Mask */
#define ECAP1_IC1_PC11_Msk      SYS_GPC_MFP2_PC11MFP_Msk       /*<! ECAP1_IC1       PC11     MFP Mask */
#define ECAP1_IC1_PE12_Msk      SYS_GPE_MFP3_PE12MFP_Msk       /*<! ECAP1_IC1       PE12     MFP Mask */
#define ECAP1_IC2_PC12_Msk      SYS_GPC_MFP3_PC12MFP_Msk       /*<! ECAP1_IC2       PC12     MFP Mask */
#define ECAP1_IC2_PE11_Msk      SYS_GPE_MFP2_PE11MFP_Msk       /*<! ECAP1_IC2       PE11     MFP Mask */
#define ECAP2_IC0_PG9_Msk       SYS_GPG_MFP2_PG9MFP_Msk        /*<! ECAP2_IC0       PG9      MFP Mask */
#define ECAP2_IC0_PJ10_Msk      SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! ECAP2_IC0       PJ10     MFP Mask */
#define ECAP2_IC0_PD1_Msk       SYS_GPD_MFP0_PD1MFP_Msk        /*<! ECAP2_IC0       PD1      MFP Mask */
#define ECAP2_IC1_PD0_Msk       SYS_GPD_MFP0_PD0MFP_Msk        /*<! ECAP2_IC1       PD0      MFP Mask */
#define ECAP2_IC1_PJ11_Msk      SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! ECAP2_IC1       PJ11     MFP Mask */
#define ECAP2_IC1_PG10_Msk      SYS_GPG_MFP2_PG10MFP_Msk       /*<! ECAP2_IC1       PG10     MFP Mask */
#define ECAP2_IC2_PG11_Msk      SYS_GPG_MFP2_PG11MFP_Msk       /*<! ECAP2_IC2       PG11     MFP Mask */
#define ECAP2_IC2_PJ12_Msk      SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! ECAP2_IC2       PJ12     MFP Mask */
#define ECAP2_IC2_PD13_Msk      SYS_GPD_MFP3_PD13MFP_Msk       /*<! ECAP2_IC2       PD13     MFP Mask */
#define ECAP3_IC0_PA12_Msk      SYS_GPA_MFP3_PA12MFP_Msk       /*<! ECAP3_IC0       PA12     MFP Mask */
#define ECAP3_IC0_PD12_Msk      SYS_GPD_MFP3_PD12MFP_Msk       /*<! ECAP3_IC0       PD12     MFP Mask */
#define ECAP3_IC0_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! ECAP3_IC0       PE8      MFP Mask */
#define ECAP3_IC1_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! ECAP3_IC1       PA13     MFP Mask */
#define ECAP3_IC1_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! ECAP3_IC1       PE9      MFP Mask */
#define ECAP3_IC1_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! ECAP3_IC1       PD11     MFP Mask */
#define ECAP3_IC2_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! ECAP3_IC2       PE10     MFP Mask */
#define ECAP3_IC2_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! ECAP3_IC2       PD10     MFP Mask */
#define ECAP3_IC2_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! ECAP3_IC2       PA14     MFP Mask */
#define EMAC0_PPS_PE13_Msk        SYS_GPE_MFP3_PE13MFP_Msk     /*<! EMAC0_PPS        PE13    MFP Mask */
#define EMAC0_PPS_PB6_Msk         SYS_GPB_MFP1_PB6MFP_Msk      /*<! EMAC0_PPS        PB6     MFP Mask */
#define EMAC0_RMII_CRSDV_PA7_Msk  SYS_GPA_MFP1_PA7MFP_Msk      /*<! EMAC0_RMII_CRSDV PA7     MFP Mask */
#define EMAC0_RMII_CRSDV_PB2_Msk  SYS_GPB_MFP0_PB2MFP_Msk      /*<! EMAC0_RMII_CRSDV PB2     MFP Mask */
#define EMAC0_RMII_MDC_PE8_Msk    SYS_GPE_MFP2_PE8MFP_Msk      /*<! EMAC0_RMII_MDC   PE8     MFP Mask */
#define EMAC0_RMII_MDC_PB11_Msk   SYS_GPB_MFP2_PB11MFP_Msk     /*<! EMAC0_RMII_MDC   PB11    MFP Mask */
#define EMAC0_RMII_MDIO_PB10_Msk  SYS_GPB_MFP2_PB10MFP_Msk     /*<! EMAC0_RMII_MDIO  PB10    MFP Mask */
#define EMAC0_RMII_MDIO_PE9_Msk   SYS_GPE_MFP2_PE9MFP_Msk      /*<! EMAC0_RMII_MDIO  PE9     MFP Mask */
#define EMAC0_RMII_REFCLK_PB5_Msk SYS_GPB_MFP1_PB5MFP_Msk      /*<! EMAC0_RMII_REFCLKPB5     MFP Mask */
#define EMAC0_RMII_REFCLK_PC8_Msk SYS_GPC_MFP2_PC8MFP_Msk      /*<! EMAC0_RMII_REFCLKPC8     MFP Mask */
#define EMAC0_RMII_RXD0_PC7_Msk   SYS_GPC_MFP1_PC7MFP_Msk      /*<! EMAC0_RMII_RXD0  PC7     MFP Mask */
#define EMAC0_RMII_RXD0_PB4_Msk   SYS_GPB_MFP1_PB4MFP_Msk      /*<! EMAC0_RMII_RXD0  PB4     MFP Mask */
#define EMAC0_RMII_RXD1_PB3_Msk   SYS_GPB_MFP0_PB3MFP_Msk      /*<! EMAC0_RMII_RXD1  PB3     MFP Mask */
#define EMAC0_RMII_RXD1_PC6_Msk   SYS_GPC_MFP1_PC6MFP_Msk      /*<! EMAC0_RMII_RXD1  PC6     MFP Mask */
#define EMAC0_RMII_RXERR_PA6_Msk  SYS_GPA_MFP1_PA6MFP_Msk      /*<! EMAC0_RMII_RXERR PA6     MFP Mask */
#define EMAC0_RMII_RXERR_PB1_Msk  SYS_GPB_MFP0_PB1MFP_Msk      /*<! EMAC0_RMII_RXERR PB1     MFP Mask */
#define EMAC0_RMII_TXD0_PE10_Msk  SYS_GPE_MFP2_PE10MFP_Msk     /*<! EMAC0_RMII_TXD0  PE10    MFP Mask */
#define EMAC0_RMII_TXD0_PB9_Msk   SYS_GPB_MFP2_PB9MFP_Msk      /*<! EMAC0_RMII_TXD0  PB9     MFP Mask */
#define EMAC0_RMII_TXD1_PB8_Msk   SYS_GPB_MFP2_PB8MFP_Msk      /*<! EMAC0_RMII_TXD1  PB8     MFP Mask */
#define EMAC0_RMII_TXD1_PE11_Msk  SYS_GPE_MFP2_PE11MFP_Msk     /*<! EMAC0_RMII_TXD1  PE11    MFP Mask */
#define EMAC0_RMII_TXEN_PB7_Msk   SYS_GPB_MFP1_PB7MFP_Msk      /*<! EMAC0_RMII_TXEN  PB7     MFP Mask */
#define EMAC0_RMII_TXEN_PE12_Msk  SYS_GPE_MFP3_PE12MFP_Msk     /*<! EMAC0_RMII_TXEN  PE12    MFP Mask */
#define EPWM0_BRAKE0_PE8_Msk    SYS_GPE_MFP2_PE8MFP_Msk        /*<! EPWM0_BRAKE0    PE8      MFP Mask */
#define EPWM0_BRAKE0_PB1_Msk    SYS_GPB_MFP0_PB1MFP_Msk        /*<! EPWM0_BRAKE0    PB1      MFP Mask */
#define EPWM0_BRAKE1_PE9_Msk    SYS_GPE_MFP2_PE9MFP_Msk        /*<! EPWM0_BRAKE1    PE9      MFP Mask */
#define EPWM0_BRAKE1_PB15_Msk   SYS_GPB_MFP3_PB15MFP_Msk       /*<! EPWM0_BRAKE1    PB15     MFP Mask */
#define EPWM0_BRAKE1_PB0_Msk    SYS_GPB_MFP0_PB0MFP_Msk        /*<! EPWM0_BRAKE1    PB0      MFP Mask */
#define EPWM0_CH0_PA5_Msk       SYS_GPA_MFP1_PA5MFP_Msk        /*<! EPWM0_CH0       PA5      MFP Mask */
#define EPWM0_CH0_PG8_Msk       SYS_GPG_MFP2_PG8MFP_Msk        /*<! EPWM0_CH0       PG8      MFP Mask */
#define EPWM0_CH0_PF5_Msk       SYS_GPF_MFP1_PF5MFP_Msk        /*<! EPWM0_CH0       PF5      MFP Mask */
#define EPWM0_CH0_PE7_Msk       SYS_GPE_MFP1_PE7MFP_Msk        /*<! EPWM0_CH0       PE7      MFP Mask */
#define EPWM0_CH0_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! EPWM0_CH0       PB5      MFP Mask */
#define EPWM0_CH0_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! EPWM0_CH0       PE8      MFP Mask */
#define EPWM0_CH1_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! EPWM0_CH1       PE9      MFP Mask */
#define EPWM0_CH1_PE6_Msk       SYS_GPE_MFP1_PE6MFP_Msk        /*<! EPWM0_CH1       PE6      MFP Mask */
#define EPWM0_CH1_PF4_Msk       SYS_GPF_MFP1_PF4MFP_Msk        /*<! EPWM0_CH1       PF4      MFP Mask */
#define EPWM0_CH1_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! EPWM0_CH1       PB4      MFP Mask */
#define EPWM0_CH1_PA4_Msk       SYS_GPA_MFP1_PA4MFP_Msk        /*<! EPWM0_CH1       PA4      MFP Mask */
#define EPWM0_CH1_PG7_Msk       SYS_GPG_MFP1_PG7MFP_Msk        /*<! EPWM0_CH1       PG7      MFP Mask */
#define EPWM0_CH2_PE5_Msk       SYS_GPE_MFP1_PE5MFP_Msk        /*<! EPWM0_CH2       PE5      MFP Mask */
#define EPWM0_CH2_PG6_Msk       SYS_GPG_MFP1_PG6MFP_Msk        /*<! EPWM0_CH2       PG6      MFP Mask */
#define EPWM0_CH2_PA3_Msk       SYS_GPA_MFP0_PA3MFP_Msk        /*<! EPWM0_CH2       PA3      MFP Mask */
#define EPWM0_CH2_PB3_Msk       SYS_GPB_MFP0_PB3MFP_Msk        /*<! EPWM0_CH2       PB3      MFP Mask */
#define EPWM0_CH2_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! EPWM0_CH2       PE10     MFP Mask */
#define EPWM0_CH3_PB2_Msk       SYS_GPB_MFP0_PB2MFP_Msk        /*<! EPWM0_CH3       PB2      MFP Mask */
#define EPWM0_CH3_PE4_Msk       SYS_GPE_MFP1_PE4MFP_Msk        /*<! EPWM0_CH3       PE4      MFP Mask */
#define EPWM0_CH3_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! EPWM0_CH3       PA2      MFP Mask */
#define EPWM0_CH3_PE11_Msk      SYS_GPE_MFP2_PE11MFP_Msk       /*<! EPWM0_CH3       PE11     MFP Mask */
#define EPWM0_CH3_PG5_Msk       SYS_GPG_MFP1_PG5MFP_Msk        /*<! EPWM0_CH3       PG5      MFP Mask */
#define EPWM0_CH4_PD14_Msk      SYS_GPD_MFP3_PD14MFP_Msk       /*<! EPWM0_CH4       PD14     MFP Mask */
#define EPWM0_CH4_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! EPWM0_CH4       PB1      MFP Mask */
#define EPWM0_CH4_PE12_Msk      SYS_GPE_MFP3_PE12MFP_Msk       /*<! EPWM0_CH4       PE12     MFP Mask */
#define EPWM0_CH4_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! EPWM0_CH4       PA1      MFP Mask */
#define EPWM0_CH4_PE3_Msk       SYS_GPE_MFP0_PE3MFP_Msk        /*<! EPWM0_CH4       PE3      MFP Mask */
#define EPWM0_CH5_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! EPWM0_CH5       PE13     MFP Mask */
#define EPWM0_CH5_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! EPWM0_CH5       PA0      MFP Mask */
#define EPWM0_CH5_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! EPWM0_CH5       PB0      MFP Mask */
#define EPWM0_CH5_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! EPWM0_CH5       PE2      MFP Mask */
#define EPWM0_CH5_PH11_Msk      SYS_GPH_MFP2_PH11MFP_Msk       /*<! EPWM0_CH5       PH11     MFP Mask */
#define EPWM0_SYNC_IN_PA15_Msk  SYS_GPA_MFP3_PA15MFP_Msk       /*<! EPWM0_SYNC_IN   PA15     MFP Mask */
#define EPWM0_SYNC_IN_PC14_Msk  SYS_GPC_MFP3_PC14MFP_Msk       /*<! EPWM0_SYNC_IN   PC14     MFP Mask */
#define EPWM0_SYNC_OUT_PA11_Msk SYS_GPA_MFP2_PA11MFP_Msk       /*<! EPWM0_SYNC_OUT  PA11     MFP Mask */
#define EPWM0_SYNC_OUT_PF5_Msk  SYS_GPF_MFP1_PF5MFP_Msk        /*<! EPWM0_SYNC_OUT  PF5      MFP Mask */
#define EPWM1_BRAKE0_PB7_Msk    SYS_GPB_MFP1_PB7MFP_Msk        /*<! EPWM1_BRAKE0    PB7      MFP Mask */
#define EPWM1_BRAKE0_PE10_Msk   SYS_GPE_MFP2_PE10MFP_Msk       /*<! EPWM1_BRAKE0    PE10     MFP Mask */
#define EPWM1_BRAKE1_PA3_Msk    SYS_GPA_MFP0_PA3MFP_Msk        /*<! EPWM1_BRAKE1    PA3      MFP Mask */
#define EPWM1_BRAKE1_PE11_Msk   SYS_GPE_MFP2_PE11MFP_Msk       /*<! EPWM1_BRAKE1    PE11     MFP Mask */
#define EPWM1_BRAKE1_PB6_Msk    SYS_GPB_MFP1_PB6MFP_Msk        /*<! EPWM1_BRAKE1    PB6      MFP Mask */
#define EPWM1_CH0_PC5_Msk       SYS_GPC_MFP1_PC5MFP_Msk        /*<! EPWM1_CH0       PC5      MFP Mask */
#define EPWM1_CH0_PI12_Msk      SYS_GPI_MFP3_PI12MFP_Msk       /*<! EPWM1_CH0       PI12     MFP Mask */
#define EPWM1_CH0_PB15_Msk      SYS_GPB_MFP3_PB15MFP_Msk       /*<! EPWM1_CH0       PB15     MFP Mask */
#define EPWM1_CH0_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! EPWM1_CH0       PE13     MFP Mask */
#define EPWM1_CH0_PC12_Msk      SYS_GPC_MFP3_PC12MFP_Msk       /*<! EPWM1_CH0       PC12     MFP Mask */
#define EPWM1_CH1_PB14_Msk      SYS_GPB_MFP3_PB14MFP_Msk       /*<! EPWM1_CH1       PB14     MFP Mask */
#define EPWM1_CH1_PC8_Msk       SYS_GPC_MFP2_PC8MFP_Msk        /*<! EPWM1_CH1       PC8      MFP Mask */
#define EPWM1_CH1_PI13_Msk      SYS_GPI_MFP3_PI13MFP_Msk       /*<! EPWM1_CH1       PI13     MFP Mask */
#define EPWM1_CH1_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! EPWM1_CH1       PC4      MFP Mask */
#define EPWM1_CH1_PC11_Msk      SYS_GPC_MFP2_PC11MFP_Msk       /*<! EPWM1_CH1       PC11     MFP Mask */
#define EPWM1_CH2_PC10_Msk      SYS_GPC_MFP2_PC10MFP_Msk       /*<! EPWM1_CH2       PC10     MFP Mask */
#define EPWM1_CH2_PB13_Msk      SYS_GPB_MFP3_PB13MFP_Msk       /*<! EPWM1_CH2       PB13     MFP Mask */
#define EPWM1_CH2_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! EPWM1_CH2       PC7      MFP Mask */
#define EPWM1_CH2_PI14_Msk      SYS_GPI_MFP3_PI14MFP_Msk       /*<! EPWM1_CH2       PI14     MFP Mask */
#define EPWM1_CH2_PC3_Msk       SYS_GPC_MFP0_PC3MFP_Msk        /*<! EPWM1_CH2       PC3      MFP Mask */
#define EPWM1_CH3_PC9_Msk       SYS_GPC_MFP2_PC9MFP_Msk        /*<! EPWM1_CH3       PC9      MFP Mask */
#define EPWM1_CH3_PC2_Msk       SYS_GPC_MFP0_PC2MFP_Msk        /*<! EPWM1_CH3       PC2      MFP Mask */
#define EPWM1_CH3_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! EPWM1_CH3       PC6      MFP Mask */
#define EPWM1_CH3_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! EPWM1_CH3       PB12     MFP Mask */
#define EPWM1_CH3_PI15_Msk      SYS_GPI_MFP3_PI15MFP_Msk       /*<! EPWM1_CH3       PI15     MFP Mask */
#define EPWM1_CH4_PB7_Msk       SYS_GPB_MFP1_PB7MFP_Msk        /*<! EPWM1_CH4       PB7      MFP Mask */
#define EPWM1_CH4_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! EPWM1_CH4       PB1      MFP Mask */
#define EPWM1_CH4_PJ0_Msk       SYS_GPJ_MFP0_PJ0MFP_Msk        /*<! EPWM1_CH4       PJ0      MFP Mask */
#define EPWM1_CH4_PF0_Msk       SYS_GPF_MFP0_PF0MFP_Msk        /*<! EPWM1_CH4       PF0      MFP Mask */
#define EPWM1_CH4_PA7_Msk       SYS_GPA_MFP1_PA7MFP_Msk        /*<! EPWM1_CH4       PA7      MFP Mask */
#define EPWM1_CH4_PC1_Msk       SYS_GPC_MFP0_PC1MFP_Msk        /*<! EPWM1_CH4       PC1      MFP Mask */
#define EPWM1_CH5_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! EPWM1_CH5       PF1      MFP Mask */
#define EPWM1_CH5_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! EPWM1_CH5       PB0      MFP Mask */
#define EPWM1_CH5_PA6_Msk       SYS_GPA_MFP1_PA6MFP_Msk        /*<! EPWM1_CH5       PA6      MFP Mask */
#define EPWM1_CH5_PJ1_Msk       SYS_GPJ_MFP0_PJ1MFP_Msk        /*<! EPWM1_CH5       PJ1      MFP Mask */
#define EPWM1_CH5_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! EPWM1_CH5       PC0      MFP Mask */
#define EPWM1_CH5_PB6_Msk       SYS_GPB_MFP1_PB6MFP_Msk        /*<! EPWM1_CH5       PB6      MFP Mask */
#define ETMC_TRACE_CLK_PC14_Msk  SYS_GPC_MFP3_PC14MFP_Msk      /*<! ETMC_TRACE_CLK   PC14    MFP Mask */
#define ETMC_TRACE_DATA0_PB15_Msk SYS_GPB_MFP3_PB15MFP_Msk     /*<! ETMC_TRACE_DATA0 PB15    MFP Mask */
#define ETMC_TRACE_DATA1_PB14_Msk SYS_GPB_MFP3_PB14MFP_Msk     /*<! ETMC_TRACE_DATA1 PB14    MFP Mask */
#define ETMC_TRACE_DATA2_PB13_Msk SYS_GPB_MFP3_PB13MFP_Msk     /*<! ETMC_TRACE_DATA2 PB13    MFP Mask */
#define ETMC_TRACE_DATA3_PB12_Msk SYS_GPB_MFP3_PB12MFP_Msk     /*<! ETMC_TRACE_DATA3 PB12    MFP Mask */
#define HBI_CK_PC4_Msk          SYS_GPC_MFP1_PC4MFP_Msk        /*<! HBI_CK          PC4      MFP Mask */
#define HBI_CK_PH13_Msk         SYS_GPH_MFP3_PH13MFP_Msk       /*<! HBI_CK          PH13     MFP Mask */
#define HBI_D0_PJ6_Msk          SYS_GPJ_MFP1_PJ6MFP_Msk        /*<! HBI_D0          PJ6      MFP Mask */
#define HBI_D0_PG11_Msk         SYS_GPG_MFP2_PG11MFP_Msk       /*<! HBI_D0          PG11     MFP Mask */
#define HBI_D1_PG12_Msk         SYS_GPG_MFP3_PG12MFP_Msk       /*<! HBI_D1          PG12     MFP Mask */
#define HBI_D1_PJ5_Msk          SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! HBI_D1          PJ5      MFP Mask */
#define HBI_D2_PJ4_Msk          SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! HBI_D2          PJ4      MFP Mask */
#define HBI_D2_PC0_Msk          SYS_GPC_MFP0_PC0MFP_Msk        /*<! HBI_D2          PC0      MFP Mask */
#define HBI_D3_PG10_Msk         SYS_GPG_MFP2_PG10MFP_Msk       /*<! HBI_D3          PG10     MFP Mask */
#define HBI_D3_PJ3_Msk          SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! HBI_D3          PJ3      MFP Mask */
#define HBI_D4_PG9_Msk          SYS_GPG_MFP2_PG9MFP_Msk        /*<! HBI_D4          PG9      MFP Mask */
#define HBI_D4_PH15_Msk         SYS_GPH_MFP3_PH15MFP_Msk       /*<! HBI_D4          PH15     MFP Mask */
#define HBI_D5_PG13_Msk         SYS_GPG_MFP3_PG13MFP_Msk       /*<! HBI_D5          PG13     MFP Mask */
#define HBI_D5_PD7_Msk          SYS_GPD_MFP1_PD7MFP_Msk        /*<! HBI_D5          PD7      MFP Mask */
#define HBI_D6_PG14_Msk         SYS_GPG_MFP3_PG14MFP_Msk       /*<! HBI_D6          PG14     MFP Mask */
#define HBI_D6_PD6_Msk          SYS_GPD_MFP1_PD6MFP_Msk        /*<! HBI_D6          PD6      MFP Mask */
#define HBI_D7_PG15_Msk         SYS_GPG_MFP3_PG15MFP_Msk       /*<! HBI_D7          PG15     MFP Mask */
#define HBI_D7_PD5_Msk          SYS_GPD_MFP1_PD5MFP_Msk        /*<! HBI_D7          PD5      MFP Mask */
#define HBI_RWDS_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! HBI_RWDS        PC1      MFP Mask */
#define HBI_RWDS_PH14_Msk       SYS_GPH_MFP3_PH14MFP_Msk       /*<! HBI_RWDS        PH14     MFP Mask */
#define HBI_nCK_PH12_Msk        SYS_GPH_MFP3_PH12MFP_Msk       /*<! HBI_nCK         PH12     MFP Mask */
#define HBI_nCK_PC5_Msk         SYS_GPC_MFP1_PC5MFP_Msk        /*<! HBI_nCK         PC5      MFP Mask */
#define HBI_nCS_PC3_Msk         SYS_GPC_MFP0_PC3MFP_Msk        /*<! HBI_nCS         PC3      MFP Mask */
#define HBI_nCS_PJ7_Msk         SYS_GPJ_MFP1_PJ7MFP_Msk        /*<! HBI_nCS         PJ7      MFP Mask */
#define HBI_nRESET_PJ2_Msk      SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! HBI_nRESET      PJ2      MFP Mask */
#define HBI_nRESET_PC2_Msk      SYS_GPC_MFP0_PC2MFP_Msk        /*<! HBI_nRESET      PC2      MFP Mask */
#define HSUSB_VBUS_EN_PB10_Msk  SYS_GPB_MFP2_PB10MFP_Msk       /*<! HSUSB_VBUS_EN   PB10     MFP Mask */
#define HSUSB_VBUS_EN_PB15_Msk  SYS_GPB_MFP3_PB15MFP_Msk       /*<! HSUSB_VBUS_EN   PB15     MFP Mask */
#define HSUSB_VBUS_EN_PJ13_Msk  SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! HSUSB_VBUS_EN   PJ13     MFP Mask */
#define HSUSB_VBUS_ST_PB11_Msk  SYS_GPB_MFP2_PB11MFP_Msk       /*<! HSUSB_VBUS_ST   PB11     MFP Mask */
#define HSUSB_VBUS_ST_PC14_Msk  SYS_GPC_MFP3_PC14MFP_Msk       /*<! HSUSB_VBUS_ST   PC14     MFP Mask */
#define HSUSB_VBUS_ST_PJ12_Msk  SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! HSUSB_VBUS_ST   PJ12     MFP Mask */
#define I2C0_SCL_PB9_Msk        SYS_GPB_MFP2_PB9MFP_Msk        /*<! I2C0_SCL        PB9      MFP Mask */
#define I2C0_SCL_PF0_Msk        SYS_GPF_MFP0_PF0MFP_Msk        /*<! I2C0_SCL        PF0      MFP Mask */
#define I2C0_SCL_PD7_Msk        SYS_GPD_MFP1_PD7MFP_Msk        /*<! I2C0_SCL        PD7      MFP Mask */
#define I2C0_SCL_PA5_Msk        SYS_GPA_MFP1_PA5MFP_Msk        /*<! I2C0_SCL        PA5      MFP Mask */
#define I2C0_SCL_PH2_Msk        SYS_GPH_MFP0_PH2MFP_Msk        /*<! I2C0_SCL        PH2      MFP Mask */
#define I2C0_SCL_PG0_Msk        SYS_GPG_MFP0_PG0MFP_Msk        /*<! I2C0_SCL        PG0      MFP Mask */
#define I2C0_SCL_PC12_Msk       SYS_GPC_MFP3_PC12MFP_Msk       /*<! I2C0_SCL        PC12     MFP Mask */
#define I2C0_SCL_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! I2C0_SCL        PC1      MFP Mask */
#define I2C0_SCL_PB5_Msk        SYS_GPB_MFP1_PB5MFP_Msk        /*<! I2C0_SCL        PB5      MFP Mask */
#define I2C0_SCL_PE13_Msk       SYS_GPE_MFP3_PE13MFP_Msk       /*<! I2C0_SCL        PE13     MFP Mask */
#define I2C0_SCL_PF3_Msk        SYS_GPF_MFP0_PF3MFP_Msk        /*<! I2C0_SCL        PF3      MFP Mask */
#define I2C0_SCL_PI10_Msk       SYS_GPI_MFP2_PI10MFP_Msk       /*<! I2C0_SCL        PI10     MFP Mask */
#define I2C0_SCL_PA14_Msk       SYS_GPA_MFP3_PA14MFP_Msk       /*<! I2C0_SCL        PA14     MFP Mask */
#define I2C0_SDA_PI11_Msk       SYS_GPI_MFP2_PI11MFP_Msk       /*<! I2C0_SDA        PI11     MFP Mask */
#define I2C0_SDA_PF2_Msk        SYS_GPF_MFP0_PF2MFP_Msk        /*<! I2C0_SDA        PF2      MFP Mask */
#define I2C0_SDA_PB4_Msk        SYS_GPB_MFP1_PB4MFP_Msk        /*<! I2C0_SDA        PB4      MFP Mask */
#define I2C0_SDA_PF1_Msk        SYS_GPF_MFP0_PF1MFP_Msk        /*<! I2C0_SDA        PF1      MFP Mask */
#define I2C0_SDA_PH3_Msk        SYS_GPH_MFP0_PH3MFP_Msk        /*<! I2C0_SDA        PH3      MFP Mask */
#define I2C0_SDA_PG1_Msk        SYS_GPG_MFP0_PG1MFP_Msk        /*<! I2C0_SDA        PG1      MFP Mask */
#define I2C0_SDA_PA4_Msk        SYS_GPA_MFP1_PA4MFP_Msk        /*<! I2C0_SDA        PA4      MFP Mask */
#define I2C0_SDA_PC11_Msk       SYS_GPC_MFP2_PC11MFP_Msk       /*<! I2C0_SDA        PC11     MFP Mask */
#define I2C0_SDA_PD6_Msk        SYS_GPD_MFP1_PD6MFP_Msk        /*<! I2C0_SDA        PD6      MFP Mask */
#define I2C0_SDA_PC0_Msk        SYS_GPC_MFP0_PC0MFP_Msk        /*<! I2C0_SDA        PC0      MFP Mask */
#define I2C0_SDA_PC8_Msk        SYS_GPC_MFP2_PC8MFP_Msk        /*<! I2C0_SDA        PC8      MFP Mask */
#define I2C0_SDA_PB8_Msk        SYS_GPB_MFP2_PB8MFP_Msk        /*<! I2C0_SDA        PB8      MFP Mask */
#define I2C0_SDA_PA15_Msk       SYS_GPA_MFP3_PA15MFP_Msk       /*<! I2C0_SDA        PA15     MFP Mask */
#define I2C0_SMBAL_PC3_Msk      SYS_GPC_MFP0_PC3MFP_Msk        /*<! I2C0_SMBAL      PC3      MFP Mask */
#define I2C0_SMBAL_PG2_Msk      SYS_GPG_MFP0_PG2MFP_Msk        /*<! I2C0_SMBAL      PG2      MFP Mask */
#define I2C0_SMBAL_PA3_Msk      SYS_GPA_MFP0_PA3MFP_Msk        /*<! I2C0_SMBAL      PA3      MFP Mask */
#define I2C0_SMBAL_PI8_Msk      SYS_GPI_MFP2_PI8MFP_Msk        /*<! I2C0_SMBAL      PI8      MFP Mask */
#define I2C0_SMBSUS_PI9_Msk     SYS_GPI_MFP2_PI9MFP_Msk        /*<! I2C0_SMBSUS     PI9      MFP Mask */
#define I2C0_SMBSUS_PA2_Msk     SYS_GPA_MFP0_PA2MFP_Msk        /*<! I2C0_SMBSUS     PA2      MFP Mask */
#define I2C0_SMBSUS_PG3_Msk     SYS_GPG_MFP0_PG3MFP_Msk        /*<! I2C0_SMBSUS     PG3      MFP Mask */
#define I2C0_SMBSUS_PC2_Msk     SYS_GPC_MFP0_PC2MFP_Msk        /*<! I2C0_SMBSUS     PC2      MFP Mask */
#define I2C1_SCL_PF0_Msk        SYS_GPF_MFP0_PF0MFP_Msk        /*<! I2C1_SCL        PF0      MFP Mask */
#define I2C1_SCL_PD5_Msk        SYS_GPD_MFP1_PD5MFP_Msk        /*<! I2C1_SCL        PD5      MFP Mask */
#define I2C1_SCL_PB1_Msk        SYS_GPB_MFP0_PB1MFP_Msk        /*<! I2C1_SCL        PB1      MFP Mask */
#define I2C1_SCL_PI6_Msk        SYS_GPI_MFP1_PI6MFP_Msk        /*<! I2C1_SCL        PI6      MFP Mask */
#define I2C1_SCL_PB3_Msk        SYS_GPB_MFP0_PB3MFP_Msk        /*<! I2C1_SCL        PB3      MFP Mask */
#define I2C1_SCL_PA12_Msk       SYS_GPA_MFP3_PA12MFP_Msk       /*<! I2C1_SCL        PA12     MFP Mask */
#define I2C1_SCL_PE1_Msk        SYS_GPE_MFP0_PE1MFP_Msk        /*<! I2C1_SCL        PE1      MFP Mask */
#define I2C1_SCL_PB11_Msk       SYS_GPB_MFP2_PB11MFP_Msk       /*<! I2C1_SCL        PB11     MFP Mask */
#define I2C1_SCL_PG2_Msk        SYS_GPG_MFP0_PG2MFP_Msk        /*<! I2C1_SCL        PG2      MFP Mask */
#define I2C1_SCL_PA7_Msk        SYS_GPA_MFP1_PA7MFP_Msk        /*<! I2C1_SCL        PA7      MFP Mask */
#define I2C1_SCL_PC5_Msk        SYS_GPC_MFP1_PC5MFP_Msk        /*<! I2C1_SCL        PC5      MFP Mask */
#define I2C1_SCL_PA3_Msk        SYS_GPA_MFP0_PA3MFP_Msk        /*<! I2C1_SCL        PA3      MFP Mask */
#define I2C1_SDA_PB0_Msk        SYS_GPB_MFP0_PB0MFP_Msk        /*<! I2C1_SDA        PB0      MFP Mask */
#define I2C1_SDA_PA2_Msk        SYS_GPA_MFP0_PA2MFP_Msk        /*<! I2C1_SDA        PA2      MFP Mask */
#define I2C1_SDA_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! I2C1_SDA        PB2      MFP Mask */
#define I2C1_SDA_PC4_Msk        SYS_GPC_MFP1_PC4MFP_Msk        /*<! I2C1_SDA        PC4      MFP Mask */
#define I2C1_SDA_PI7_Msk        SYS_GPI_MFP1_PI7MFP_Msk        /*<! I2C1_SDA        PI7      MFP Mask */
#define I2C1_SDA_PF1_Msk        SYS_GPF_MFP0_PF1MFP_Msk        /*<! I2C1_SDA        PF1      MFP Mask */
#define I2C1_SDA_PD4_Msk        SYS_GPD_MFP1_PD4MFP_Msk        /*<! I2C1_SDA        PD4      MFP Mask */
#define I2C1_SDA_PA13_Msk       SYS_GPA_MFP3_PA13MFP_Msk       /*<! I2C1_SDA        PA13     MFP Mask */
#define I2C1_SDA_PB10_Msk       SYS_GPB_MFP2_PB10MFP_Msk       /*<! I2C1_SDA        PB10     MFP Mask */
#define I2C1_SDA_PA6_Msk        SYS_GPA_MFP1_PA6MFP_Msk        /*<! I2C1_SDA        PA6      MFP Mask */
#define I2C1_SDA_PG3_Msk        SYS_GPG_MFP0_PG3MFP_Msk        /*<! I2C1_SDA        PG3      MFP Mask */
#define I2C1_SDA_PE0_Msk        SYS_GPE_MFP0_PE0MFP_Msk        /*<! I2C1_SDA        PE0      MFP Mask */
#define I2C1_SMBAL_PG0_Msk      SYS_GPG_MFP0_PG0MFP_Msk        /*<! I2C1_SMBAL      PG0      MFP Mask */
#define I2C1_SMBAL_PC7_Msk      SYS_GPC_MFP1_PC7MFP_Msk        /*<! I2C1_SMBAL      PC7      MFP Mask */
#define I2C1_SMBAL_PB9_Msk      SYS_GPB_MFP2_PB9MFP_Msk        /*<! I2C1_SMBAL      PB9      MFP Mask */
#define I2C1_SMBAL_PH8_Msk      SYS_GPH_MFP2_PH8MFP_Msk        /*<! I2C1_SMBAL      PH8      MFP Mask */
#define I2C1_SMBSUS_PH9_Msk     SYS_GPH_MFP2_PH9MFP_Msk        /*<! I2C1_SMBSUS     PH9      MFP Mask */
#define I2C1_SMBSUS_PC6_Msk     SYS_GPC_MFP1_PC6MFP_Msk        /*<! I2C1_SMBSUS     PC6      MFP Mask */
#define I2C1_SMBSUS_PG1_Msk     SYS_GPG_MFP0_PG1MFP_Msk        /*<! I2C1_SMBSUS     PG1      MFP Mask */
#define I2C1_SMBSUS_PB8_Msk     SYS_GPB_MFP2_PB8MFP_Msk        /*<! I2C1_SMBSUS     PB8      MFP Mask */
#define I2C2_SCL_PA1_Msk        SYS_GPA_MFP0_PA1MFP_Msk        /*<! I2C2_SCL        PA1      MFP Mask */
#define I2C2_SCL_PH8_Msk        SYS_GPH_MFP2_PH8MFP_Msk        /*<! I2C2_SCL        PH8      MFP Mask */
#define I2C2_SCL_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! I2C2_SCL        PB13     MFP Mask */
#define I2C2_SCL_PA11_Msk       SYS_GPA_MFP2_PA11MFP_Msk       /*<! I2C2_SCL        PA11     MFP Mask */
#define I2C2_SCL_PA14_Msk       SYS_GPA_MFP3_PA14MFP_Msk       /*<! I2C2_SCL        PA14     MFP Mask */
#define I2C2_SCL_PD1_Msk        SYS_GPD_MFP0_PD1MFP_Msk        /*<! I2C2_SCL        PD1      MFP Mask */
#define I2C2_SCL_PD9_Msk        SYS_GPD_MFP2_PD9MFP_Msk        /*<! I2C2_SCL        PD9      MFP Mask */
#define I2C2_SDA_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! I2C2_SDA        PB12     MFP Mask */
#define I2C2_SDA_PD8_Msk        SYS_GPD_MFP2_PD8MFP_Msk        /*<! I2C2_SDA        PD8      MFP Mask */
#define I2C2_SDA_PA0_Msk        SYS_GPA_MFP0_PA0MFP_Msk        /*<! I2C2_SDA        PA0      MFP Mask */
#define I2C2_SDA_PH9_Msk        SYS_GPH_MFP2_PH9MFP_Msk        /*<! I2C2_SDA        PH9      MFP Mask */
#define I2C2_SDA_PA15_Msk       SYS_GPA_MFP3_PA15MFP_Msk       /*<! I2C2_SDA        PA15     MFP Mask */
#define I2C2_SDA_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! I2C2_SDA        PA10     MFP Mask */
#define I2C2_SDA_PD0_Msk        SYS_GPD_MFP0_PD0MFP_Msk        /*<! I2C2_SDA        PD0      MFP Mask */
#define I2C2_SMBAL_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! I2C2_SMBAL      PB15     MFP Mask */
#define I2C2_SMBSUS_PB14_Msk    SYS_GPB_MFP3_PB14MFP_Msk       /*<! I2C2_SMBSUS     PB14     MFP Mask */
#define I2C3_SCL_PG7_Msk        SYS_GPG_MFP1_PG7MFP_Msk        /*<! I2C3_SCL        PG7      MFP Mask */
#define I2C3_SCL_PG0_Msk        SYS_GPG_MFP0_PG0MFP_Msk        /*<! I2C3_SCL        PG0      MFP Mask */
#define I2C3_SCL_PC3_Msk        SYS_GPC_MFP0_PC3MFP_Msk        /*<! I2C3_SCL        PC3      MFP Mask */
#define I2C3_SCL_PI14_Msk       SYS_GPI_MFP3_PI14MFP_Msk       /*<! I2C3_SCL        PI14     MFP Mask */
#define I2C3_SDA_PG8_Msk        SYS_GPG_MFP2_PG8MFP_Msk        /*<! I2C3_SDA        PG8      MFP Mask */
#define I2C3_SDA_PI15_Msk       SYS_GPI_MFP3_PI15MFP_Msk       /*<! I2C3_SDA        PI15     MFP Mask */
#define I2C3_SDA_PC2_Msk        SYS_GPC_MFP0_PC2MFP_Msk        /*<! I2C3_SDA        PC2      MFP Mask */
#define I2C3_SDA_PG1_Msk        SYS_GPG_MFP0_PG1MFP_Msk        /*<! I2C3_SDA        PG1      MFP Mask */
#define I2C3_SMBAL_PG2_Msk      SYS_GPG_MFP0_PG2MFP_Msk        /*<! I2C3_SMBAL      PG2      MFP Mask */
#define I2C3_SMBAL_PI12_Msk     SYS_GPI_MFP3_PI12MFP_Msk       /*<! I2C3_SMBAL      PI12     MFP Mask */
#define I2C3_SMBAL_PC5_Msk      SYS_GPC_MFP1_PC5MFP_Msk        /*<! I2C3_SMBAL      PC5      MFP Mask */
#define I2C3_SMBAL_PG5_Msk      SYS_GPG_MFP1_PG5MFP_Msk        /*<! I2C3_SMBAL      PG5      MFP Mask */
#define I2C3_SMBSUS_PG6_Msk     SYS_GPG_MFP1_PG6MFP_Msk        /*<! I2C3_SMBSUS     PG6      MFP Mask */
#define I2C3_SMBSUS_PC4_Msk     SYS_GPC_MFP1_PC4MFP_Msk        /*<! I2C3_SMBSUS     PC4      MFP Mask */
#define I2C3_SMBSUS_PG3_Msk     SYS_GPG_MFP0_PG3MFP_Msk        /*<! I2C3_SMBSUS     PG3      MFP Mask */
#define I2C3_SMBSUS_PI13_Msk    SYS_GPI_MFP3_PI13MFP_Msk       /*<! I2C3_SMBSUS     PI13     MFP Mask */
#define I2C4_SCL_PJ10_Msk       SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! I2C4_SCL        PJ10     MFP Mask */
#define I2C4_SCL_PG9_Msk        SYS_GPG_MFP2_PG9MFP_Msk        /*<! I2C4_SCL        PG9      MFP Mask */
#define I2C4_SCL_PC12_Msk       SYS_GPC_MFP3_PC12MFP_Msk       /*<! I2C4_SCL        PC12     MFP Mask */
#define I2C4_SCL_PF5_Msk        SYS_GPF_MFP1_PF5MFP_Msk        /*<! I2C4_SCL        PF5      MFP Mask */
#define I2C4_SDA_PJ11_Msk       SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! I2C4_SDA        PJ11     MFP Mask */
#define I2C4_SDA_PG10_Msk       SYS_GPG_MFP2_PG10MFP_Msk       /*<! I2C4_SDA        PG10     MFP Mask */
#define I2C4_SDA_PC11_Msk       SYS_GPC_MFP2_PC11MFP_Msk       /*<! I2C4_SDA        PC11     MFP Mask */
#define I2C4_SDA_PF4_Msk        SYS_GPF_MFP1_PF4MFP_Msk        /*<! I2C4_SDA        PF4      MFP Mask */
#define I2C4_SMBAL_PJ12_Msk     SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! I2C4_SMBAL      PJ12     MFP Mask */
#define I2C4_SMBAL_PG11_Msk     SYS_GPG_MFP2_PG11MFP_Msk       /*<! I2C4_SMBAL      PG11     MFP Mask */
#define I2C4_SMBAL_PF3_Msk      SYS_GPF_MFP0_PF3MFP_Msk        /*<! I2C4_SMBAL      PF3      MFP Mask */
#define I2C4_SMBAL_PC10_Msk     SYS_GPC_MFP2_PC10MFP_Msk       /*<! I2C4_SMBAL      PC10     MFP Mask */
#define I2C4_SMBSUS_PJ13_Msk    SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! I2C4_SMBSUS     PJ13     MFP Mask */
#define I2C4_SMBSUS_PG12_Msk    SYS_GPG_MFP3_PG12MFP_Msk       /*<! I2C4_SMBSUS     PG12     MFP Mask */
#define I2C4_SMBSUS_PC9_Msk     SYS_GPC_MFP2_PC9MFP_Msk        /*<! I2C4_SMBSUS     PC9      MFP Mask */
#define I2C4_SMBSUS_PF2_Msk     SYS_GPF_MFP0_PF2MFP_Msk        /*<! I2C4_SMBSUS     PF2      MFP Mask */
#define I2S0_BCLK_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! I2S0_BCLK       PE8      MFP Mask */
#define I2S0_BCLK_PF10_Msk      SYS_GPF_MFP2_PF10MFP_Msk       /*<! I2S0_BCLK       PF10     MFP Mask */
#define I2S0_BCLK_PE1_Msk       SYS_GPE_MFP0_PE1MFP_Msk        /*<! I2S0_BCLK       PE1      MFP Mask */
#define I2S0_BCLK_PA12_Msk      SYS_GPA_MFP3_PA12MFP_Msk       /*<! I2S0_BCLK       PA12     MFP Mask */
#define I2S0_BCLK_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! I2S0_BCLK       PB5      MFP Mask */
#define I2S0_BCLK_PI6_Msk       SYS_GPI_MFP1_PI6MFP_Msk        /*<! I2S0_BCLK       PI6      MFP Mask */
#define I2S0_BCLK_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! I2S0_BCLK       PC4      MFP Mask */
#define I2S0_DI_PB3_Msk         SYS_GPB_MFP0_PB3MFP_Msk        /*<! I2S0_DI         PB3      MFP Mask */
#define I2S0_DI_PC2_Msk         SYS_GPC_MFP0_PC2MFP_Msk        /*<! I2S0_DI         PC2      MFP Mask */
#define I2S0_DI_PI8_Msk         SYS_GPI_MFP2_PI8MFP_Msk        /*<! I2S0_DI         PI8      MFP Mask */
#define I2S0_DI_PA14_Msk        SYS_GPA_MFP3_PA14MFP_Msk       /*<! I2S0_DI         PA14     MFP Mask */
#define I2S0_DI_PF8_Msk         SYS_GPF_MFP2_PF8MFP_Msk        /*<! I2S0_DI         PF8      MFP Mask */
#define I2S0_DI_PH8_Msk         SYS_GPH_MFP2_PH8MFP_Msk        /*<! I2S0_DI         PH8      MFP Mask */
#define I2S0_DI_PE10_Msk        SYS_GPE_MFP2_PE10MFP_Msk       /*<! I2S0_DI         PE10     MFP Mask */
#define I2S0_DO_PH9_Msk         SYS_GPH_MFP2_PH9MFP_Msk        /*<! I2S0_DO         PH9      MFP Mask */
#define I2S0_DO_PC1_Msk         SYS_GPC_MFP0_PC1MFP_Msk        /*<! I2S0_DO         PC1      MFP Mask */
#define I2S0_DO_PA15_Msk        SYS_GPA_MFP3_PA15MFP_Msk       /*<! I2S0_DO         PA15     MFP Mask */
#define I2S0_DO_PB2_Msk         SYS_GPB_MFP0_PB2MFP_Msk        /*<! I2S0_DO         PB2      MFP Mask */
#define I2S0_DO_PF7_Msk         SYS_GPF_MFP1_PF7MFP_Msk        /*<! I2S0_DO         PF7      MFP Mask */
#define I2S0_DO_PF0_Msk         SYS_GPF_MFP0_PF0MFP_Msk        /*<! I2S0_DO         PF0      MFP Mask */
#define I2S0_DO_PE11_Msk        SYS_GPE_MFP2_PE11MFP_Msk       /*<! I2S0_DO         PE11     MFP Mask */
#define I2S0_DO_PI9_Msk         SYS_GPI_MFP2_PI9MFP_Msk        /*<! I2S0_DO         PI9      MFP Mask */
#define I2S0_LRCK_PF6_Msk       SYS_GPF_MFP1_PF6MFP_Msk        /*<! I2S0_LRCK       PF6      MFP Mask */
#define I2S0_LRCK_PE12_Msk      SYS_GPE_MFP3_PE12MFP_Msk       /*<! I2S0_LRCK       PE12     MFP Mask */
#define I2S0_LRCK_PH10_Msk      SYS_GPH_MFP2_PH10MFP_Msk       /*<! I2S0_LRCK       PH10     MFP Mask */
#define I2S0_LRCK_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! I2S0_LRCK       PB1      MFP Mask */
#define I2S0_LRCK_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! I2S0_LRCK       PF1      MFP Mask */
#define I2S0_LRCK_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! I2S0_LRCK       PC0      MFP Mask */
#define I2S0_LRCK_PI10_Msk      SYS_GPI_MFP2_PI10MFP_Msk       /*<! I2S0_LRCK       PI10     MFP Mask */
#define I2S0_MCLK_PE0_Msk       SYS_GPE_MFP0_PE0MFP_Msk        /*<! I2S0_MCLK       PE0      MFP Mask */
#define I2S0_MCLK_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! I2S0_MCLK       PB4      MFP Mask */
#define I2S0_MCLK_PF9_Msk       SYS_GPF_MFP2_PF9MFP_Msk        /*<! I2S0_MCLK       PF9      MFP Mask */
#define I2S0_MCLK_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! I2S0_MCLK       PE9      MFP Mask */
#define I2S0_MCLK_PI7_Msk       SYS_GPI_MFP1_PI7MFP_Msk        /*<! I2S0_MCLK       PI7      MFP Mask */
#define I2S0_MCLK_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! I2S0_MCLK       PA13     MFP Mask */
#define I2S0_MCLK_PC3_Msk       SYS_GPC_MFP0_PC3MFP_Msk        /*<! I2S0_MCLK       PC3      MFP Mask */
#define I2S1_BCLK_PD14_Msk      SYS_GPD_MFP3_PD14MFP_Msk       /*<! I2S1_BCLK       PD14     MFP Mask */
#define I2S1_BCLK_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! I2S1_BCLK       PA11     MFP Mask */
#define I2S1_BCLK_PD3_Msk       SYS_GPD_MFP0_PD3MFP_Msk        /*<! I2S1_BCLK       PD3      MFP Mask */
#define I2S1_DI_PD1_Msk         SYS_GPD_MFP0_PD1MFP_Msk        /*<! I2S1_DI         PD1      MFP Mask */
#define I2S1_DI_PA9_Msk         SYS_GPA_MFP2_PA9MFP_Msk        /*<! I2S1_DI         PA9      MFP Mask */
#define I2S1_DI_PG6_Msk         SYS_GPG_MFP1_PG6MFP_Msk        /*<! I2S1_DI         PG6      MFP Mask */
#define I2S1_DO_PD0_Msk         SYS_GPD_MFP0_PD0MFP_Msk        /*<! I2S1_DO         PD0      MFP Mask */
#define I2S1_DO_PA8_Msk         SYS_GPA_MFP2_PA8MFP_Msk        /*<! I2S1_DO         PA8      MFP Mask */
#define I2S1_DO_PG7_Msk         SYS_GPG_MFP1_PG7MFP_Msk        /*<! I2S1_DO         PG7      MFP Mask */
#define I2S1_LRCK_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! I2S1_LRCK       PB0      MFP Mask */
#define I2S1_LRCK_PD13_Msk      SYS_GPD_MFP3_PD13MFP_Msk       /*<! I2S1_LRCK       PD13     MFP Mask */
#define I2S1_LRCK_PG8_Msk       SYS_GPG_MFP2_PG8MFP_Msk        /*<! I2S1_LRCK       PG8      MFP Mask */
#define I2S1_MCLK_PD2_Msk       SYS_GPD_MFP0_PD2MFP_Msk        /*<! I2S1_MCLK       PD2      MFP Mask */
#define I2S1_MCLK_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! I2S1_MCLK       PA10     MFP Mask */
#define I2S1_MCLK_PG5_Msk       SYS_GPG_MFP1_PG5MFP_Msk        /*<! I2S1_MCLK       PG5      MFP Mask */
#define ICE_CLK_PF1_Msk         SYS_GPF_MFP0_PF1MFP_Msk        /*<! ICE_CLK         PF1      MFP Mask */
#define ICE_DAT_PF0_Msk         SYS_GPF_MFP0_PF0MFP_Msk        /*<! ICE_DAT         PF0      MFP Mask */
#define INT0_PA6_Msk            SYS_GPA_MFP1_PA6MFP_Msk        /*<! INT0            PA6      MFP Mask */
#define INT0_PB5_Msk            SYS_GPB_MFP1_PB5MFP_Msk        /*<! INT0            PB5      MFP Mask */
#define INT1_PA7_Msk            SYS_GPA_MFP1_PA7MFP_Msk        /*<! INT1            PA7      MFP Mask */
#define INT1_PB4_Msk            SYS_GPB_MFP1_PB4MFP_Msk        /*<! INT1            PB4      MFP Mask */
#define INT2_PB3_Msk            SYS_GPB_MFP0_PB3MFP_Msk        /*<! INT2            PB3      MFP Mask */
#define INT2_PC6_Msk            SYS_GPC_MFP1_PC6MFP_Msk        /*<! INT2            PC6      MFP Mask */
#define INT3_PC7_Msk            SYS_GPC_MFP1_PC7MFP_Msk        /*<! INT3            PC7      MFP Mask */
#define INT3_PB2_Msk            SYS_GPB_MFP0_PB2MFP_Msk        /*<! INT3            PB2      MFP Mask */
#define INT4_PA8_Msk            SYS_GPA_MFP2_PA8MFP_Msk        /*<! INT4            PA8      MFP Mask */
#define INT4_PB6_Msk            SYS_GPB_MFP1_PB6MFP_Msk        /*<! INT4            PB6      MFP Mask */
#define INT5_PD12_Msk           SYS_GPD_MFP3_PD12MFP_Msk       /*<! INT5            PD12     MFP Mask */
#define INT5_PB7_Msk            SYS_GPB_MFP1_PB7MFP_Msk        /*<! INT5            PB7      MFP Mask */
#define INT6_PB8_Msk            SYS_GPB_MFP2_PB8MFP_Msk        /*<! INT6            PB8      MFP Mask */
#define INT6_PD11_Msk           SYS_GPD_MFP2_PD11MFP_Msk       /*<! INT6            PD11     MFP Mask */
#define INT7_PB9_Msk            SYS_GPB_MFP2_PB9MFP_Msk        /*<! INT7            PB9      MFP Mask */
#define INT7_PD10_Msk           SYS_GPD_MFP2_PD10MFP_Msk       /*<! INT7            PD10     MFP Mask */
#define TRACE_SWO_PF6_Msk       SYS_GPF_MFP1_PF6MFP_Msk        /*<! TRACE_SWO       PF6      MFP Mask */
#define TRACE_SWO_PC14_Msk      SYS_GPC_MFP3_PC14MFP_Msk       /*<! TRACE_SWO       PC14     MFP Mask */
#define TRACE_SWO_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! TRACE_SWO       PE13     MFP Mask */
#define KPI_COL0_PA6_Msk        SYS_GPA_MFP1_PA6MFP_Msk        /*<! KPI_COL0        PA6      MFP Mask */
#define KPI_COL0_PB15_Msk       SYS_GPB_MFP3_PB15MFP_Msk       /*<! KPI_COL0        PB15     MFP Mask */
#define KPI_COL1_PA7_Msk        SYS_GPA_MFP1_PA7MFP_Msk        /*<! KPI_COL1        PA7      MFP Mask */
#define KPI_COL1_PB14_Msk       SYS_GPB_MFP3_PB14MFP_Msk       /*<! KPI_COL1        PB14     MFP Mask */
#define KPI_COL2_PC6_Msk        SYS_GPC_MFP1_PC6MFP_Msk        /*<! KPI_COL2        PC6      MFP Mask */
#define KPI_COL2_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*<! KPI_COL2        PB13     MFP Mask */
#define KPI_COL3_PC7_Msk        SYS_GPC_MFP1_PC7MFP_Msk        /*<! KPI_COL3        PC7      MFP Mask */
#define KPI_COL3_PB12_Msk       SYS_GPB_MFP3_PB12MFP_Msk       /*<! KPI_COL3        PB12     MFP Mask */
#define KPI_COL4_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! KPI_COL4        PB7      MFP Mask */
#define KPI_COL4_PC8_Msk        SYS_GPC_MFP2_PC8MFP_Msk        /*<! KPI_COL4        PC8      MFP Mask */
#define KPI_COL5_PB6_Msk        SYS_GPB_MFP1_PB6MFP_Msk        /*<! KPI_COL5        PB6      MFP Mask */
#define KPI_COL5_PE13_Msk       SYS_GPE_MFP3_PE13MFP_Msk       /*<! KPI_COL5        PE13     MFP Mask */
#define KPI_COL6_PE12_Msk       SYS_GPE_MFP3_PE12MFP_Msk       /*<! KPI_COL6        PE12     MFP Mask */
#define KPI_COL6_PB5_Msk        SYS_GPB_MFP1_PB5MFP_Msk        /*<! KPI_COL6        PB5      MFP Mask */
#define KPI_COL7_PE11_Msk       SYS_GPE_MFP2_PE11MFP_Msk       /*<! KPI_COL7        PE11     MFP Mask */
#define KPI_COL7_PB4_Msk        SYS_GPB_MFP1_PB4MFP_Msk        /*<! KPI_COL7        PB4      MFP Mask */
#define KPI_ROW0_PC5_Msk        SYS_GPC_MFP1_PC5MFP_Msk        /*<! KPI_ROW0        PC5      MFP Mask */
#define KPI_ROW0_PB3_Msk        SYS_GPB_MFP0_PB3MFP_Msk        /*<! KPI_ROW0        PB3      MFP Mask */
#define KPI_ROW1_PC4_Msk        SYS_GPC_MFP1_PC4MFP_Msk        /*<! KPI_ROW1        PC4      MFP Mask */
#define KPI_ROW1_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! KPI_ROW1        PB2      MFP Mask */
#define KPI_ROW2_PB1_Msk        SYS_GPB_MFP0_PB1MFP_Msk        /*<! KPI_ROW2        PB1      MFP Mask */
#define KPI_ROW2_PC3_Msk        SYS_GPC_MFP0_PC3MFP_Msk        /*<! KPI_ROW2        PC3      MFP Mask */
#define KPI_ROW3_PC2_Msk        SYS_GPC_MFP0_PC2MFP_Msk        /*<! KPI_ROW3        PC2      MFP Mask */
#define KPI_ROW3_PB0_Msk        SYS_GPB_MFP0_PB0MFP_Msk        /*<! KPI_ROW3        PB0      MFP Mask */
#define KPI_ROW4_PA11_Msk       SYS_GPA_MFP2_PA11MFP_Msk       /*<! KPI_ROW4        PA11     MFP Mask */
#define KPI_ROW4_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! KPI_ROW4        PC1      MFP Mask */
#define KPI_ROW5_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! KPI_ROW5        PA10     MFP Mask */
#define KPI_ROW5_PC0_Msk        SYS_GPC_MFP0_PC0MFP_Msk        /*<! KPI_ROW5        PC0      MFP Mask */
#define PSIO0_CH0_PC5_Msk       SYS_GPC_MFP1_PC5MFP_Msk        /*<! PSIO0_CH0       PC5      MFP Mask */
#define PSIO0_CH0_PB15_Msk      SYS_GPB_MFP3_PB15MFP_Msk       /*<! PSIO0_CH0       PB15     MFP Mask */
#define PSIO0_CH0_PE7_Msk       SYS_GPE_MFP1_PE7MFP_Msk        /*<! PSIO0_CH0       PE7      MFP Mask */
#define PSIO0_CH0_PE14_Msk      SYS_GPE_MFP3_PE14MFP_Msk       /*<! PSIO0_CH0       PE14     MFP Mask */
#define PSIO0_CH1_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! PSIO0_CH1       PC4      MFP Mask */
#define PSIO0_CH1_PE15_Msk      SYS_GPE_MFP3_PE15MFP_Msk       /*<! PSIO0_CH1       PE15     MFP Mask */
#define PSIO0_CH1_PE6_Msk       SYS_GPE_MFP1_PE6MFP_Msk        /*<! PSIO0_CH1       PE6      MFP Mask */
#define PSIO0_CH1_PB14_Msk      SYS_GPB_MFP3_PB14MFP_Msk       /*<! PSIO0_CH1       PB14     MFP Mask */
#define PSIO0_CH2_PC3_Msk       SYS_GPC_MFP0_PC3MFP_Msk        /*<! PSIO0_CH2       PC3      MFP Mask */
#define PSIO0_CH2_PD9_Msk       SYS_GPD_MFP2_PD9MFP_Msk        /*<! PSIO0_CH2       PD9      MFP Mask */
#define PSIO0_CH2_PE5_Msk       SYS_GPE_MFP1_PE5MFP_Msk        /*<! PSIO0_CH2       PE5      MFP Mask */
#define PSIO0_CH2_PB13_Msk      SYS_GPB_MFP3_PB13MFP_Msk       /*<! PSIO0_CH2       PB13     MFP Mask */
#define PSIO0_CH3_PD8_Msk       SYS_GPD_MFP2_PD8MFP_Msk        /*<! PSIO0_CH3       PD8      MFP Mask */
#define PSIO0_CH3_PC2_Msk       SYS_GPC_MFP0_PC2MFP_Msk        /*<! PSIO0_CH3       PC2      MFP Mask */
#define PSIO0_CH3_PE4_Msk       SYS_GPE_MFP1_PE4MFP_Msk        /*<! PSIO0_CH3       PE4      MFP Mask */
#define PSIO0_CH3_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! PSIO0_CH3       PB12     MFP Mask */
#define PSIO0_CH4_PD7_Msk       SYS_GPD_MFP1_PD7MFP_Msk        /*<! PSIO0_CH4       PD7      MFP Mask */
#define PSIO0_CH4_PA12_Msk      SYS_GPA_MFP3_PA12MFP_Msk       /*<! PSIO0_CH4       PA12     MFP Mask */
#define PSIO0_CH4_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! PSIO0_CH4       PB5      MFP Mask */
#define PSIO0_CH4_PA3_Msk       SYS_GPA_MFP0_PA3MFP_Msk        /*<! PSIO0_CH4       PA3      MFP Mask */
#define PSIO0_CH5_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! PSIO0_CH5       PA13     MFP Mask */
#define PSIO0_CH5_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! PSIO0_CH5       PB4      MFP Mask */
#define PSIO0_CH5_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! PSIO0_CH5       PA2      MFP Mask */
#define PSIO0_CH5_PD6_Msk       SYS_GPD_MFP1_PD6MFP_Msk        /*<! PSIO0_CH5       PD6      MFP Mask */
#define PSIO0_CH6_PB3_Msk       SYS_GPB_MFP0_PB3MFP_Msk        /*<! PSIO0_CH6       PB3      MFP Mask */
#define PSIO0_CH6_PD5_Msk       SYS_GPD_MFP1_PD5MFP_Msk        /*<! PSIO0_CH6       PD5      MFP Mask */
#define PSIO0_CH6_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! PSIO0_CH6       PA1      MFP Mask */
#define PSIO0_CH6_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! PSIO0_CH6       PA14     MFP Mask */
#define PSIO0_CH7_PD4_Msk       SYS_GPD_MFP1_PD4MFP_Msk        /*<! PSIO0_CH7       PD4      MFP Mask */
#define PSIO0_CH7_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! PSIO0_CH7       PA15     MFP Mask */
#define PSIO0_CH7_PB2_Msk       SYS_GPB_MFP0_PB2MFP_Msk        /*<! PSIO0_CH7       PB2      MFP Mask */
#define PSIO0_CH7_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! PSIO0_CH7       PA0      MFP Mask */
#define EQEI0_A_PE3_Msk         SYS_GPE_MFP0_PE3MFP_Msk        /*<! EQEI0_A         PE3      MFP Mask */
#define EQEI0_A_PA4_Msk         SYS_GPA_MFP1_PA4MFP_Msk        /*<! EQEI0_A         PA4      MFP Mask */
#define EQEI0_A_PD11_Msk        SYS_GPD_MFP2_PD11MFP_Msk       /*<! EQEI0_A         PD11     MFP Mask */
#define EQEI0_B_PA3_Msk         SYS_GPA_MFP0_PA3MFP_Msk        /*<! EQEI0_B         PA3      MFP Mask */
#define EQEI0_B_PD10_Msk        SYS_GPD_MFP2_PD10MFP_Msk       /*<! EQEI0_B         PD10     MFP Mask */
#define EQEI0_B_PE2_Msk         SYS_GPE_MFP0_PE2MFP_Msk        /*<! EQEI0_B         PE2      MFP Mask */
#define EQEI0_INDEX_PE4_Msk     SYS_GPE_MFP1_PE4MFP_Msk        /*<! EQEI0_INDEX     PE4      MFP Mask */
#define EQEI0_INDEX_PA5_Msk     SYS_GPA_MFP1_PA5MFP_Msk        /*<! EQEI0_INDEX     PA5      MFP Mask */
#define EQEI0_INDEX_PD12_Msk    SYS_GPD_MFP3_PD12MFP_Msk       /*<! EQEI0_INDEX     PD12     MFP Mask */
#define EQEI1_A_PA9_Msk         SYS_GPA_MFP2_PA9MFP_Msk        /*<! EQEI1_A         PA9      MFP Mask */
#define EQEI1_A_PA13_Msk        SYS_GPA_MFP3_PA13MFP_Msk       /*<! EQEI1_A         PA13     MFP Mask */
#define EQEI1_A_PE6_Msk         SYS_GPE_MFP1_PE6MFP_Msk        /*<! EQEI1_A         PE6      MFP Mask */
#define EQEI1_B_PE5_Msk         SYS_GPE_MFP1_PE5MFP_Msk        /*<! EQEI1_B         PE5      MFP Mask */
#define EQEI1_B_PA8_Msk         SYS_GPA_MFP2_PA8MFP_Msk        /*<! EQEI1_B         PA8      MFP Mask */
#define EQEI1_B_PA14_Msk        SYS_GPA_MFP3_PA14MFP_Msk       /*<! EQEI1_B         PA14     MFP Mask */
#define EQEI1_INDEX_PA10_Msk    SYS_GPA_MFP2_PA10MFP_Msk       /*<! EQEI1_INDEX     PA10     MFP Mask */
#define EQEI1_INDEX_PE7_Msk     SYS_GPE_MFP1_PE7MFP_Msk        /*<! EQEI1_INDEX     PE7      MFP Mask */
#define EQEI1_INDEX_PA12_Msk    SYS_GPA_MFP3_PA12MFP_Msk       /*<! EQEI1_INDEX     PA12     MFP Mask */
#define EQEI2_A_PE9_Msk         SYS_GPE_MFP2_PE9MFP_Msk        /*<! EQEI2_A         PE9      MFP Mask */
#define EQEI2_A_PF5_Msk         SYS_GPF_MFP1_PF5MFP_Msk        /*<! EQEI2_A         PF5      MFP Mask */
#define EQEI2_A_PD0_Msk         SYS_GPD_MFP0_PD0MFP_Msk        /*<! EQEI2_A         PD0      MFP Mask */
#define EQEI2_B_PF4_Msk         SYS_GPF_MFP1_PF4MFP_Msk        /*<! EQEI2_B         PF4      MFP Mask */
#define EQEI2_B_PE10_Msk        SYS_GPE_MFP2_PE10MFP_Msk       /*<! EQEI2_B         PE10     MFP Mask */
#define EQEI2_B_PD13_Msk        SYS_GPD_MFP3_PD13MFP_Msk       /*<! EQEI2_B         PD13     MFP Mask */
#define EQEI2_INDEX_PE8_Msk     SYS_GPE_MFP2_PE8MFP_Msk        /*<! EQEI2_INDEX     PE8      MFP Mask */
#define EQEI2_INDEX_PD1_Msk     SYS_GPD_MFP0_PD1MFP_Msk        /*<! EQEI2_INDEX     PD1      MFP Mask */
#define EQEI2_INDEX_PF6_Msk     SYS_GPF_MFP1_PF6MFP_Msk        /*<! EQEI2_INDEX     PF6      MFP Mask */
#define EQEI3_A_PD3_Msk         SYS_GPD_MFP0_PD3MFP_Msk        /*<! EQEI3_A         PD3      MFP Mask */
#define EQEI3_A_PA1_Msk         SYS_GPA_MFP0_PA1MFP_Msk        /*<! EQEI3_A         PA1      MFP Mask */
#define EQEI3_B_PA0_Msk         SYS_GPA_MFP0_PA0MFP_Msk        /*<! EQEI3_B         PA0      MFP Mask */
#define EQEI3_B_PD2_Msk         SYS_GPD_MFP0_PD2MFP_Msk        /*<! EQEI3_B         PD2      MFP Mask */
#define EQEI3_INDEX_PA2_Msk     SYS_GPA_MFP0_PA2MFP_Msk        /*<! EQEI3_INDEX     PA2      MFP Mask */
#define EQEI3_INDEX_PA15_Msk    SYS_GPA_MFP3_PA15MFP_Msk       /*<! EQEI3_INDEX     PA15     MFP Mask */
#define QSPI0_CLK_PH8_Msk       SYS_GPH_MFP2_PH8MFP_Msk        /*<! QSPI0_CLK       PH8      MFP Mask */
#define QSPI0_CLK_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! QSPI0_CLK       PA2      MFP Mask */
#define QSPI0_CLK_PI15_Msk      SYS_GPI_MFP3_PI15MFP_Msk       /*<! QSPI0_CLK       PI15     MFP Mask */
#define QSPI0_CLK_PC2_Msk       SYS_GPC_MFP0_PC2MFP_Msk        /*<! QSPI0_CLK       PC2      MFP Mask */
#define QSPI0_CLK_PF2_Msk       SYS_GPF_MFP0_PF2MFP_Msk        /*<! QSPI0_CLK       PF2      MFP Mask */
#define QSPI0_CLK_PC14_Msk      SYS_GPC_MFP3_PC14MFP_Msk       /*<! QSPI0_CLK       PC14     MFP Mask */
#define QSPI0_MISO0_PC1_Msk     SYS_GPC_MFP0_PC1MFP_Msk        /*<! QSPI0_MISO0     PC1      MFP Mask */
#define QSPI0_MISO0_PJ0_Msk     SYS_GPJ_MFP0_PJ0MFP_Msk        /*<! QSPI0_MISO0     PJ0      MFP Mask */
#define QSPI0_MISO0_PE1_Msk     SYS_GPE_MFP0_PE1MFP_Msk        /*<! QSPI0_MISO0     PE1      MFP Mask */
#define QSPI0_MISO0_PA1_Msk     SYS_GPA_MFP0_PA1MFP_Msk        /*<! QSPI0_MISO0     PA1      MFP Mask */
#define QSPI0_MISO1_PB1_Msk     SYS_GPB_MFP0_PB1MFP_Msk        /*<! QSPI0_MISO1     PB1      MFP Mask */
#define QSPI0_MISO1_PI12_Msk    SYS_GPI_MFP3_PI12MFP_Msk       /*<! QSPI0_MISO1     PI12     MFP Mask */
#define QSPI0_MISO1_PC5_Msk     SYS_GPC_MFP1_PC5MFP_Msk        /*<! QSPI0_MISO1     PC5      MFP Mask */
#define QSPI0_MISO1_PH10_Msk    SYS_GPH_MFP2_PH10MFP_Msk       /*<! QSPI0_MISO1     PH10     MFP Mask */
#define QSPI0_MISO1_PA5_Msk     SYS_GPA_MFP1_PA5MFP_Msk        /*<! QSPI0_MISO1     PA5      MFP Mask */
#define QSPI0_MOSI0_PE0_Msk     SYS_GPE_MFP0_PE0MFP_Msk        /*<! QSPI0_MOSI0     PE0      MFP Mask */
#define QSPI0_MOSI0_PC0_Msk     SYS_GPC_MFP0_PC0MFP_Msk        /*<! QSPI0_MOSI0     PC0      MFP Mask */
#define QSPI0_MOSI0_PA0_Msk     SYS_GPA_MFP0_PA0MFP_Msk        /*<! QSPI0_MOSI0     PA0      MFP Mask */
#define QSPI0_MOSI0_PJ1_Msk     SYS_GPJ_MFP0_PJ1MFP_Msk        /*<! QSPI0_MOSI0     PJ1      MFP Mask */
#define QSPI0_MOSI1_PA4_Msk     SYS_GPA_MFP1_PA4MFP_Msk        /*<! QSPI0_MOSI1     PA4      MFP Mask */
#define QSPI0_MOSI1_PC4_Msk     SYS_GPC_MFP1_PC4MFP_Msk        /*<! QSPI0_MOSI1     PC4      MFP Mask */
#define QSPI0_MOSI1_PH11_Msk    SYS_GPH_MFP2_PH11MFP_Msk       /*<! QSPI0_MOSI1     PH11     MFP Mask */
#define QSPI0_MOSI1_PI13_Msk    SYS_GPI_MFP3_PI13MFP_Msk       /*<! QSPI0_MOSI1     PI13     MFP Mask */
#define QSPI0_MOSI1_PB0_Msk     SYS_GPB_MFP0_PB0MFP_Msk        /*<! QSPI0_MOSI1     PB0      MFP Mask */
#define QSPI0_SS_PI14_Msk       SYS_GPI_MFP3_PI14MFP_Msk       /*<! QSPI0_SS        PI14     MFP Mask */
#define QSPI0_SS_PA3_Msk        SYS_GPA_MFP0_PA3MFP_Msk        /*<! QSPI0_SS        PA3      MFP Mask */
#define QSPI0_SS_PC3_Msk        SYS_GPC_MFP0_PC3MFP_Msk        /*<! QSPI0_SS        PC3      MFP Mask */
#define QSPI0_SS_PH9_Msk        SYS_GPH_MFP2_PH9MFP_Msk        /*<! QSPI0_SS        PH9      MFP Mask */
#define QSPI1_CLK_PH15_Msk      SYS_GPH_MFP3_PH15MFP_Msk       /*<! QSPI1_CLK       PH15     MFP Mask */
#define QSPI1_CLK_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! QSPI1_CLK       PC4      MFP Mask */
#define QSPI1_CLK_PJ3_Msk       SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! QSPI1_CLK       PJ3      MFP Mask */
#define QSPI1_CLK_PG12_Msk      SYS_GPG_MFP3_PG12MFP_Msk       /*<! QSPI1_CLK       PG12     MFP Mask */
#define QSPI1_CLK_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! QSPI1_CLK       PC0      MFP Mask */
#define QSPI1_MISO0_PD7_Msk     SYS_GPD_MFP1_PD7MFP_Msk        /*<! QSPI1_MISO0     PD7      MFP Mask */
#define QSPI1_MISO0_PA12_Msk    SYS_GPA_MFP3_PA12MFP_Msk       /*<! QSPI1_MISO0     PA12     MFP Mask */
#define QSPI1_MISO0_PC3_Msk     SYS_GPC_MFP0_PC3MFP_Msk        /*<! QSPI1_MISO0     PC3      MFP Mask */
#define QSPI1_MISO0_PJ4_Msk     SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! QSPI1_MISO0     PJ4      MFP Mask */
#define QSPI1_MISO0_PG13_Msk    SYS_GPG_MFP3_PG13MFP_Msk       /*<! QSPI1_MISO0     PG13     MFP Mask */
#define QSPI1_MISO0_PF0_Msk     SYS_GPF_MFP0_PF0MFP_Msk        /*<! QSPI1_MISO0     PF0      MFP Mask */
#define QSPI1_MISO1_PG9_Msk     SYS_GPG_MFP2_PG9MFP_Msk        /*<! QSPI1_MISO1     PG9      MFP Mask */
#define QSPI1_MISO1_PA7_Msk     SYS_GPA_MFP1_PA7MFP_Msk        /*<! QSPI1_MISO1     PA7      MFP Mask */
#define QSPI1_MISO1_PG15_Msk    SYS_GPG_MFP3_PG15MFP_Msk       /*<! QSPI1_MISO1     PG15     MFP Mask */
#define QSPI1_MISO1_PH12_Msk    SYS_GPH_MFP3_PH12MFP_Msk       /*<! QSPI1_MISO1     PH12     MFP Mask */
#define QSPI1_MOSI0_PA13_Msk    SYS_GPA_MFP3_PA13MFP_Msk       /*<! QSPI1_MOSI0     PA13     MFP Mask */
#define QSPI1_MOSI0_PD13_Msk    SYS_GPD_MFP3_PD13MFP_Msk       /*<! QSPI1_MOSI0     PD13     MFP Mask */
#define QSPI1_MOSI0_PG14_Msk    SYS_GPG_MFP3_PG14MFP_Msk       /*<! QSPI1_MOSI0     PG14     MFP Mask */
#define QSPI1_MOSI0_PC2_Msk     SYS_GPC_MFP0_PC2MFP_Msk        /*<! QSPI1_MOSI0     PC2      MFP Mask */
#define QSPI1_MOSI0_PJ5_Msk     SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! QSPI1_MOSI0     PJ5      MFP Mask */
#define QSPI1_MOSI0_PD6_Msk     SYS_GPD_MFP1_PD6MFP_Msk        /*<! QSPI1_MOSI0     PD6      MFP Mask */
#define QSPI1_MOSI0_PD13_Msk    SYS_GPD_MFP3_PD13MFP_Msk       /*<! QSPI1_MOSI0     PD13     MFP Mask */
#define QSPI1_MOSI0_PF1_Msk     SYS_GPF_MFP0_PF1MFP_Msk        /*<! QSPI1_MOSI0     PF1      MFP Mask */
#define QSPI1_MOSI1_PG10_Msk    SYS_GPG_MFP2_PG10MFP_Msk       /*<! QSPI1_MOSI1     PG10     MFP Mask */
#define QSPI1_MOSI1_PA6_Msk     SYS_GPA_MFP1_PA6MFP_Msk        /*<! QSPI1_MOSI1     PA6      MFP Mask */
#define QSPI1_MOSI1_PH13_Msk    SYS_GPH_MFP3_PH13MFP_Msk       /*<! QSPI1_MOSI1     PH13     MFP Mask */
#define QSPI1_SS_PG11_Msk       SYS_GPG_MFP2_PG11MFP_Msk       /*<! QSPI1_SS        PG11     MFP Mask */
#define QSPI1_SS_PH14_Msk       SYS_GPH_MFP3_PH14MFP_Msk       /*<! QSPI1_SS        PH14     MFP Mask */
#define QSPI1_SS_PC5_Msk        SYS_GPC_MFP1_PC5MFP_Msk        /*<! QSPI1_SS        PC5      MFP Mask */
#define QSPI1_SS_PJ2_Msk        SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! QSPI1_SS        PJ2      MFP Mask */
#define QSPI1_SS_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! QSPI1_SS        PC1      MFP Mask */
#define SC0_CLK_PA0_Msk         SYS_GPA_MFP0_PA0MFP_Msk        /*<! SC0_CLK         PA0      MFP Mask */
#define SC0_CLK_PF6_Msk         SYS_GPF_MFP1_PF6MFP_Msk        /*<! SC0_CLK         PF6      MFP Mask */
#define SC0_CLK_PE2_Msk         SYS_GPE_MFP0_PE2MFP_Msk        /*<! SC0_CLK         PE2      MFP Mask */
#define SC0_CLK_PB5_Msk         SYS_GPB_MFP1_PB5MFP_Msk        /*<! SC0_CLK         PB5      MFP Mask */
#define SC0_DAT_PE3_Msk         SYS_GPE_MFP0_PE3MFP_Msk        /*<! SC0_DAT         PE3      MFP Mask */
#define SC0_DAT_PB4_Msk         SYS_GPB_MFP1_PB4MFP_Msk        /*<! SC0_DAT         PB4      MFP Mask */
#define SC0_DAT_PA1_Msk         SYS_GPA_MFP0_PA1MFP_Msk        /*<! SC0_DAT         PA1      MFP Mask */
#define SC0_DAT_PF7_Msk         SYS_GPF_MFP1_PF7MFP_Msk        /*<! SC0_DAT         PF7      MFP Mask */
#define SC0_PWR_PE5_Msk         SYS_GPE_MFP1_PE5MFP_Msk        /*<! SC0_PWR         PE5      MFP Mask */
#define SC0_PWR_PA3_Msk         SYS_GPA_MFP0_PA3MFP_Msk        /*<! SC0_PWR         PA3      MFP Mask */
#define SC0_PWR_PB2_Msk         SYS_GPB_MFP0_PB2MFP_Msk        /*<! SC0_PWR         PB2      MFP Mask */
#define SC0_PWR_PF9_Msk         SYS_GPF_MFP2_PF9MFP_Msk        /*<! SC0_PWR         PF9      MFP Mask */
#define SC0_RST_PE4_Msk         SYS_GPE_MFP1_PE4MFP_Msk        /*<! SC0_RST         PE4      MFP Mask */
#define SC0_RST_PA2_Msk         SYS_GPA_MFP0_PA2MFP_Msk        /*<! SC0_RST         PA2      MFP Mask */
#define SC0_RST_PF8_Msk         SYS_GPF_MFP2_PF8MFP_Msk        /*<! SC0_RST         PF8      MFP Mask */
#define SC0_RST_PB3_Msk         SYS_GPB_MFP0_PB3MFP_Msk        /*<! SC0_RST         PB3      MFP Mask */
#define SC0_nCD_PC12_Msk        SYS_GPC_MFP3_PC12MFP_Msk       /*<! SC0_nCD         PC12     MFP Mask */
#define SC0_nCD_PE6_Msk         SYS_GPE_MFP1_PE6MFP_Msk        /*<! SC0_nCD         PE6      MFP Mask */
#define SC0_nCD_PA4_Msk         SYS_GPA_MFP1_PA4MFP_Msk        /*<! SC0_nCD         PA4      MFP Mask */
#define SC0_nCD_PF10_Msk        SYS_GPF_MFP2_PF10MFP_Msk       /*<! SC0_nCD         PF10     MFP Mask */
#define SC1_CLK_PF1_Msk         SYS_GPF_MFP0_PF1MFP_Msk        /*<! SC1_CLK         PF1      MFP Mask */
#define SC1_CLK_PD4_Msk         SYS_GPD_MFP1_PD4MFP_Msk        /*<! SC1_CLK         PD4      MFP Mask */
#define SC1_CLK_PI10_Msk        SYS_GPI_MFP2_PI10MFP_Msk       /*<! SC1_CLK         PI10     MFP Mask */
#define SC1_CLK_PB12_Msk        SYS_GPB_MFP3_PB12MFP_Msk       /*<! SC1_CLK         PB12     MFP Mask */
#define SC1_CLK_PG8_Msk         SYS_GPG_MFP2_PG8MFP_Msk        /*<! SC1_CLK         PG8      MFP Mask */
#define SC1_CLK_PC0_Msk         SYS_GPC_MFP0_PC0MFP_Msk        /*<! SC1_CLK         PC0      MFP Mask */
#define SC1_DAT_PC1_Msk         SYS_GPC_MFP0_PC1MFP_Msk        /*<! SC1_DAT         PC1      MFP Mask */
#define SC1_DAT_PD5_Msk         SYS_GPD_MFP1_PD5MFP_Msk        /*<! SC1_DAT         PD5      MFP Mask */
#define SC1_DAT_PF0_Msk         SYS_GPF_MFP0_PF0MFP_Msk        /*<! SC1_DAT         PF0      MFP Mask */
#define SC1_DAT_PG7_Msk         SYS_GPG_MFP1_PG7MFP_Msk        /*<! SC1_DAT         PG7      MFP Mask */
#define SC1_DAT_PI9_Msk         SYS_GPI_MFP2_PI9MFP_Msk        /*<! SC1_DAT         PI9      MFP Mask */
#define SC1_DAT_PB13_Msk        SYS_GPB_MFP3_PB13MFP_Msk       /*<! SC1_DAT         PB13     MFP Mask */
#define SC1_PWR_PD7_Msk         SYS_GPD_MFP1_PD7MFP_Msk        /*<! SC1_PWR         PD7      MFP Mask */
#define SC1_PWR_PC3_Msk         SYS_GPC_MFP0_PC3MFP_Msk        /*<! SC1_PWR         PC3      MFP Mask */
#define SC1_PWR_PI7_Msk         SYS_GPI_MFP1_PI7MFP_Msk        /*<! SC1_PWR         PI7      MFP Mask */
#define SC1_PWR_PG5_Msk         SYS_GPG_MFP1_PG5MFP_Msk        /*<! SC1_PWR         PG5      MFP Mask */
#define SC1_PWR_PB15_Msk        SYS_GPB_MFP3_PB15MFP_Msk       /*<! SC1_PWR         PB15     MFP Mask */
#define SC1_RST_PI8_Msk         SYS_GPI_MFP2_PI8MFP_Msk        /*<! SC1_RST         PI8      MFP Mask */
#define SC1_RST_PG6_Msk         SYS_GPG_MFP1_PG6MFP_Msk        /*<! SC1_RST         PG6      MFP Mask */
#define SC1_RST_PB14_Msk        SYS_GPB_MFP3_PB14MFP_Msk       /*<! SC1_RST         PB14     MFP Mask */
#define SC1_RST_PC2_Msk         SYS_GPC_MFP0_PC2MFP_Msk        /*<! SC1_RST         PC2      MFP Mask */
#define SC1_RST_PD6_Msk         SYS_GPD_MFP1_PD6MFP_Msk        /*<! SC1_RST         PD6      MFP Mask */
#define SC1_nCD_PD14_Msk        SYS_GPD_MFP3_PD14MFP_Msk       /*<! SC1_nCD         PD14     MFP Mask */
#define SC1_nCD_PC4_Msk         SYS_GPC_MFP1_PC4MFP_Msk        /*<! SC1_nCD         PC4      MFP Mask */
#define SC1_nCD_PI6_Msk         SYS_GPI_MFP1_PI6MFP_Msk        /*<! SC1_nCD         PI6      MFP Mask */
#define SC1_nCD_PD3_Msk         SYS_GPD_MFP0_PD3MFP_Msk        /*<! SC1_nCD         PD3      MFP Mask */
#define SC1_nCD_PC14_Msk        SYS_GPC_MFP3_PC14MFP_Msk       /*<! SC1_nCD         PC14     MFP Mask */
#define SC2_CLK_PA15_Msk        SYS_GPA_MFP3_PA15MFP_Msk       /*<! SC2_CLK         PA15     MFP Mask */
#define SC2_CLK_PD0_Msk         SYS_GPD_MFP0_PD0MFP_Msk        /*<! SC2_CLK         PD0      MFP Mask */
#define SC2_CLK_PA6_Msk         SYS_GPA_MFP1_PA6MFP_Msk        /*<! SC2_CLK         PA6      MFP Mask */
#define SC2_CLK_PE0_Msk         SYS_GPE_MFP0_PE0MFP_Msk        /*<! SC2_CLK         PE0      MFP Mask */
#define SC2_CLK_PA8_Msk         SYS_GPA_MFP2_PA8MFP_Msk        /*<! SC2_CLK         PA8      MFP Mask */
#define SC2_DAT_PD1_Msk         SYS_GPD_MFP0_PD1MFP_Msk        /*<! SC2_DAT         PD1      MFP Mask */
#define SC2_DAT_PA9_Msk         SYS_GPA_MFP2_PA9MFP_Msk        /*<! SC2_DAT         PA9      MFP Mask */
#define SC2_DAT_PE1_Msk         SYS_GPE_MFP0_PE1MFP_Msk        /*<! SC2_DAT         PE1      MFP Mask */
#define SC2_DAT_PA14_Msk        SYS_GPA_MFP3_PA14MFP_Msk       /*<! SC2_DAT         PA14     MFP Mask */
#define SC2_DAT_PA7_Msk         SYS_GPA_MFP1_PA7MFP_Msk        /*<! SC2_DAT         PA7      MFP Mask */
#define SC2_PWR_PC7_Msk         SYS_GPC_MFP1_PC7MFP_Msk        /*<! SC2_PWR         PC7      MFP Mask */
#define SC2_PWR_PA11_Msk        SYS_GPA_MFP2_PA11MFP_Msk       /*<! SC2_PWR         PA11     MFP Mask */
#define SC2_PWR_PA12_Msk        SYS_GPA_MFP3_PA12MFP_Msk       /*<! SC2_PWR         PA12     MFP Mask */
#define SC2_PWR_PD3_Msk         SYS_GPD_MFP0_PD3MFP_Msk        /*<! SC2_PWR         PD3      MFP Mask */
#define SC2_PWR_PH8_Msk         SYS_GPH_MFP2_PH8MFP_Msk        /*<! SC2_PWR         PH8      MFP Mask */
#define SC2_RST_PC6_Msk         SYS_GPC_MFP1_PC6MFP_Msk        /*<! SC2_RST         PC6      MFP Mask */
#define SC2_RST_PD2_Msk         SYS_GPD_MFP0_PD2MFP_Msk        /*<! SC2_RST         PD2      MFP Mask */
#define SC2_RST_PA13_Msk        SYS_GPA_MFP3_PA13MFP_Msk       /*<! SC2_RST         PA13     MFP Mask */
#define SC2_RST_PA10_Msk        SYS_GPA_MFP2_PA10MFP_Msk       /*<! SC2_RST         PA10     MFP Mask */
#define SC2_RST_PH9_Msk         SYS_GPH_MFP2_PH9MFP_Msk        /*<! SC2_RST         PH9      MFP Mask */
#define SC2_nCD_PD13_Msk        SYS_GPD_MFP3_PD13MFP_Msk       /*<! SC2_nCD         PD13     MFP Mask */
#define SC2_nCD_PA5_Msk         SYS_GPA_MFP1_PA5MFP_Msk        /*<! SC2_nCD         PA5      MFP Mask */
#define SC2_nCD_PC13_Msk        SYS_GPC_MFP3_PC13MFP_Msk       /*<! SC2_nCD         PC13     MFP Mask */
#define SC2_nCD_PH10_Msk        SYS_GPH_MFP2_PH10MFP_Msk       /*<! SC2_nCD         PH10     MFP Mask */
#define SD0_CLK_PB1_Msk         SYS_GPB_MFP0_PB1MFP_Msk        /*<! SD0_CLK         PB1      MFP Mask */
#define SD0_CLK_PE6_Msk         SYS_GPE_MFP1_PE6MFP_Msk        /*<! SD0_CLK         PE6      MFP Mask */
#define SD0_CMD_PE7_Msk         SYS_GPE_MFP1_PE7MFP_Msk        /*<! SD0_CMD         PE7      MFP Mask */
#define SD0_CMD_PB0_Msk         SYS_GPB_MFP0_PB0MFP_Msk        /*<! SD0_CMD         PB0      MFP Mask */
#define SD0_DAT0_PE2_Msk        SYS_GPE_MFP0_PE2MFP_Msk        /*<! SD0_DAT0        PE2      MFP Mask */
#define SD0_DAT0_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! SD0_DAT0        PB2      MFP Mask */
#define SD0_DAT1_PB3_Msk        SYS_GPB_MFP0_PB3MFP_Msk        /*<! SD0_DAT1        PB3      MFP Mask */
#define SD0_DAT1_PE3_Msk        SYS_GPE_MFP0_PE3MFP_Msk        /*<! SD0_DAT1        PE3      MFP Mask */
#define SD0_DAT2_PE4_Msk        SYS_GPE_MFP1_PE4MFP_Msk        /*<! SD0_DAT2        PE4      MFP Mask */
#define SD0_DAT2_PB4_Msk        SYS_GPB_MFP1_PB4MFP_Msk        /*<! SD0_DAT2        PB4      MFP Mask */
#define SD0_DAT3_PE5_Msk        SYS_GPE_MFP1_PE5MFP_Msk        /*<! SD0_DAT3        PE5      MFP Mask */
#define SD0_DAT3_PB5_Msk        SYS_GPB_MFP1_PB5MFP_Msk        /*<! SD0_DAT3        PB5      MFP Mask */
#define SD0_nCD_PB12_Msk        SYS_GPB_MFP3_PB12MFP_Msk       /*<! SD0_nCD         PB12     MFP Mask */
#define SD0_nCD_PD13_Msk        SYS_GPD_MFP3_PD13MFP_Msk       /*<! SD0_nCD         PD13     MFP Mask */
#define SD1_CLK_PJ13_Msk        SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! SD1_CLK         PJ13     MFP Mask */
#define SD1_CLK_PG14_Msk        SYS_GPG_MFP3_PG14MFP_Msk       /*<! SD1_CLK         PG14     MFP Mask */
#define SD1_CLK_PD13_Msk        SYS_GPD_MFP3_PD13MFP_Msk       /*<! SD1_CLK         PD13     MFP Mask */
#define SD1_CLK_PA4_Msk         SYS_GPA_MFP1_PA4MFP_Msk        /*<! SD1_CLK         PA4      MFP Mask */
#define SD1_CLK_PB6_Msk         SYS_GPB_MFP1_PB6MFP_Msk        /*<! SD1_CLK         PB6      MFP Mask */
#define SD1_CMD_PA5_Msk         SYS_GPA_MFP1_PA5MFP_Msk        /*<! SD1_CMD         PA5      MFP Mask */
#define SD1_CMD_PJ12_Msk        SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! SD1_CMD         PJ12     MFP Mask */
#define SD1_CMD_PB7_Msk         SYS_GPB_MFP1_PB7MFP_Msk        /*<! SD1_CMD         PB7      MFP Mask */
#define SD1_CMD_PG13_Msk        SYS_GPG_MFP3_PG13MFP_Msk       /*<! SD1_CMD         PG13     MFP Mask */
#define SD1_DAT0_PA8_Msk        SYS_GPA_MFP2_PA8MFP_Msk        /*<! SD1_DAT0        PA8      MFP Mask */
#define SD1_DAT0_PA0_Msk        SYS_GPA_MFP0_PA0MFP_Msk        /*<! SD1_DAT0        PA0      MFP Mask */
#define SD1_DAT0_PG12_Msk       SYS_GPG_MFP3_PG12MFP_Msk       /*<! SD1_DAT0        PG12     MFP Mask */
#define SD1_DAT0_PJ11_Msk       SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! SD1_DAT0        PJ11     MFP Mask */
#define SD1_DAT1_PG11_Msk       SYS_GPG_MFP2_PG11MFP_Msk       /*<! SD1_DAT1        PG11     MFP Mask */
#define SD1_DAT1_PJ10_Msk       SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! SD1_DAT1        PJ10     MFP Mask */
#define SD1_DAT1_PA9_Msk        SYS_GPA_MFP2_PA9MFP_Msk        /*<! SD1_DAT1        PA9      MFP Mask */
#define SD1_DAT1_PA1_Msk        SYS_GPA_MFP0_PA1MFP_Msk        /*<! SD1_DAT1        PA1      MFP Mask */
#define SD1_DAT2_PA2_Msk        SYS_GPA_MFP0_PA2MFP_Msk        /*<! SD1_DAT2        PA2      MFP Mask */
#define SD1_DAT2_PJ9_Msk        SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! SD1_DAT2        PJ9      MFP Mask */
#define SD1_DAT2_PG10_Msk       SYS_GPG_MFP2_PG10MFP_Msk       /*<! SD1_DAT2        PG10     MFP Mask */
#define SD1_DAT2_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! SD1_DAT2        PA10     MFP Mask */
#define SD1_DAT3_PA3_Msk        SYS_GPA_MFP0_PA3MFP_Msk        /*<! SD1_DAT3        PA3      MFP Mask */
#define SD1_DAT3_PJ8_Msk        SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! SD1_DAT3        PJ8      MFP Mask */
#define SD1_DAT3_PA11_Msk       SYS_GPA_MFP2_PA11MFP_Msk       /*<! SD1_DAT3        PA11     MFP Mask */
#define SD1_DAT3_PG9_Msk        SYS_GPG_MFP2_PG9MFP_Msk        /*<! SD1_DAT3        PG9      MFP Mask */
#define SD1_nCD_PA6_Msk         SYS_GPA_MFP1_PA6MFP_Msk        /*<! SD1_nCD         PA6      MFP Mask */
#define SD1_nCD_PG15_Msk        SYS_GPG_MFP3_PG15MFP_Msk       /*<! SD1_nCD         PG15     MFP Mask */
#define SD1_nCD_PA12_Msk        SYS_GPA_MFP3_PA12MFP_Msk       /*<! SD1_nCD         PA12     MFP Mask */
#define SD1_nCD_PE14_Msk        SYS_GPE_MFP3_PE14MFP_Msk       /*<! SD1_nCD         PE14     MFP Mask */
#define SPI0_CLK_PD2_Msk        SYS_GPD_MFP0_PD2MFP_Msk        /*<! SPI0_CLK        PD2      MFP Mask */
#define SPI0_CLK_PF8_Msk        SYS_GPF_MFP2_PF8MFP_Msk        /*<! SPI0_CLK        PF8      MFP Mask */
#define SPI0_CLK_PA2_Msk        SYS_GPA_MFP0_PA2MFP_Msk        /*<! SPI0_CLK        PA2      MFP Mask */
#define SPI0_CLK_PB14_Msk       SYS_GPB_MFP3_PB14MFP_Msk       /*<! SPI0_CLK        PB14     MFP Mask */
#define SPI10_CLK_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! SPI10_CLK       PA13     MFP Mask */
#define SPI0_I2SMCLK_PF10_Msk   SYS_GPF_MFP2_PF10MFP_Msk       /*<! SPI0_I2SMCLK    PF10     MFP Mask */
#define SPI0_I2SMCLK_PD13_Msk   SYS_GPD_MFP3_PD13MFP_Msk       /*<! SPI0_I2SMCLK    PD13     MFP Mask */
#define SPI0_I2SMCLK_PB0_Msk    SYS_GPB_MFP0_PB0MFP_Msk        /*<! SPI0_I2SMCLK    PB0      MFP Mask */
#define SPI0_I2SMCLK_PD14_Msk   SYS_GPD_MFP3_PD14MFP_Msk       /*<! SPI0_I2SMCLK    PD14     MFP Mask */
#define SPI0_I2SMCLK_PA4_Msk    SYS_GPA_MFP1_PA4MFP_Msk        /*<! SPI0_I2SMCLK    PA4      MFP Mask */
#define SPI0_I2SMCLK_PC14_Msk   SYS_GPC_MFP3_PC14MFP_Msk       /*<! SPI0_I2SMCLK    PC14     MFP Mask */
#define SPI0_I2SMCLK_PB11_Msk   SYS_GPB_MFP2_PB11MFP_Msk       /*<! SPI0_I2SMCLK    PB11     MFP Mask */
#define SPI0_MISO_PD1_Msk       SYS_GPD_MFP0_PD1MFP_Msk        /*<! SPI0_MISO       PD1      MFP Mask */
#define SPI0_MISO_PB13_Msk      SYS_GPB_MFP3_PB13MFP_Msk       /*<! SPI0_MISO       PB13     MFP Mask */
#define SPI0_MISO_PF7_Msk       SYS_GPF_MFP1_PF7MFP_Msk        /*<! SPI0_MISO       PF7      MFP Mask */
#define SPI0_MISO_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! SPI0_MISO       PA1      MFP Mask */
#define SPI0_MISO_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! SPI0_MISO       PA14     MFP Mask */
#define SPI0_MOSI_PD0_Msk       SYS_GPD_MFP0_PD0MFP_Msk        /*<! SPI0_MOSI       PD0      MFP Mask */
#define SPI0_MOSI_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! SPI0_MOSI       PB12     MFP Mask */
#define SPI0_MOSI_PF6_Msk       SYS_GPF_MFP1_PF6MFP_Msk        /*<! SPI0_MOSI       PF6      MFP Mask */
#define SPI0_MOSI_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! SPI0_MOSI       PA0      MFP Mask */
#define SPI0_MOSI_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! SPI0_MOSI       PA15     MFP Mask */
#define SPI0_SS_PD3_Msk         SYS_GPD_MFP0_PD3MFP_Msk        /*<! SPI0_SS         PD3      MFP Mask */
#define SPI0_SS_PF9_Msk         SYS_GPF_MFP2_PF9MFP_Msk        /*<! SPI0_SS         PF9      MFP Mask */
#define SPI0_SS_PB15_Msk        SYS_GPB_MFP3_PB15MFP_Msk       /*<! SPI0_SS         PB15     MFP Mask */
#define SPI0_SS_PA3_Msk         SYS_GPA_MFP0_PA3MFP_Msk        /*<! SPI0_SS         PA3      MFP Mask */
#define SPI0_SS_PA12_Msk        SYS_GPA_MFP3_PA12MFP_Msk       /*<! SPI0_SS         PA12     MFP Mask */
#define SPI1_CLK_PI9_Msk        SYS_GPI_MFP2_PI9MFP_Msk        /*<! SPI1_CLK        PI9      MFP Mask */
#define SPI1_CLK_PH8_Msk        SYS_GPH_MFP2_PH8MFP_Msk        /*<! SPI1_CLK        PH8      MFP Mask */
#define SPI1_CLK_PB3_Msk        SYS_GPB_MFP0_PB3MFP_Msk        /*<! SPI1_CLK        PB3      MFP Mask */
#define SPI1_CLK_PD5_Msk        SYS_GPD_MFP1_PD5MFP_Msk        /*<! SPI1_CLK        PD5      MFP Mask */
#define SPI1_CLK_PA7_Msk        SYS_GPA_MFP1_PA7MFP_Msk        /*<! SPI1_CLK        PA7      MFP Mask */
#define SPI1_CLK_PC1_Msk        SYS_GPC_MFP0_PC1MFP_Msk        /*<! SPI1_CLK        PC1      MFP Mask */
#define SPI1_CLK_PH6_Msk        SYS_GPH_MFP1_PH6MFP_Msk        /*<! SPI1_CLK        PH6      MFP Mask */
#define SPI1_CLK_PB7_Msk        SYS_GPB_MFP1_PB7MFP_Msk        /*<! SPI1_CLK        PB7      MFP Mask */
#define SPI1_I2SMCLK_PC4_Msk    SYS_GPC_MFP1_PC4MFP_Msk        /*<! SPI1_I2SMCLK    PC4      MFP Mask */
#define SPI1_I2SMCLK_PI6_Msk    SYS_GPI_MFP1_PI6MFP_Msk        /*<! SPI1_I2SMCLK    PI6      MFP Mask */
#define SPI1_I2SMCLK_PH10_Msk   SYS_GPH_MFP2_PH10MFP_Msk       /*<! SPI1_I2SMCLK    PH10     MFP Mask */
#define SPI1_I2SMCLK_PA5_Msk    SYS_GPA_MFP1_PA5MFP_Msk        /*<! SPI1_I2SMCLK    PA5      MFP Mask */
#define SPI1_I2SMCLK_PH3_Msk    SYS_GPH_MFP0_PH3MFP_Msk        /*<! SPI1_I2SMCLK    PH3      MFP Mask */
#define SPI1_I2SMCLK_PD13_Msk   SYS_GPD_MFP3_PD13MFP_Msk       /*<! SPI1_I2SMCLK    PD13     MFP Mask */
#define SPI1_I2SMCLK_PB1_Msk    SYS_GPB_MFP0_PB1MFP_Msk        /*<! SPI1_I2SMCLK    PB1      MFP Mask */
#define SPI1_MISO_PE1_Msk       SYS_GPE_MFP0_PE1MFP_Msk        /*<! SPI1_MISO       PE1      MFP Mask */
#define SPI1_MISO_PC3_Msk       SYS_GPC_MFP0_PC3MFP_Msk        /*<! SPI1_MISO       PC3      MFP Mask */
#define SPI1_MISO_PH4_Msk       SYS_GPH_MFP1_PH4MFP_Msk        /*<! SPI1_MISO       PH4      MFP Mask */
#define SPI1_MISO_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! SPI1_MISO       PC7      MFP Mask */
#define SPI1_MISO_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! SPI1_MISO       PB5      MFP Mask */
#define SPI1_MISO_PI7_Msk       SYS_GPI_MFP1_PI7MFP_Msk        /*<! SPI1_MISO       PI7      MFP Mask */
#define SPI1_MISO_PD7_Msk       SYS_GPD_MFP1_PD7MFP_Msk        /*<! SPI1_MISO       PD7      MFP Mask */
#define SPI1_MOSI_PD6_Msk       SYS_GPD_MFP1_PD6MFP_Msk        /*<! SPI1_MOSI       PD6      MFP Mask */
#define SPI1_MOSI_PH5_Msk       SYS_GPH_MFP1_PH5MFP_Msk        /*<! SPI1_MOSI       PH5      MFP Mask */
#define SPI1_MOSI_PI8_Msk       SYS_GPI_MFP2_PI8MFP_Msk        /*<! SPI1_MOSI       PI8      MFP Mask */
#define SPI1_MOSI_PE0_Msk       SYS_GPE_MFP0_PE0MFP_Msk        /*<! SPI1_MOSI       PE0      MFP Mask */
#define SPI1_MOSI_PC2_Msk       SYS_GPC_MFP0_PC2MFP_Msk        /*<! SPI1_MOSI       PC2      MFP Mask */
#define SPI1_MOSI_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! SPI1_MOSI       PC6      MFP Mask */
#define SPI1_MOSI_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! SPI1_MOSI       PB4      MFP Mask */
#define SPI1_SS_PA6_Msk         SYS_GPA_MFP1_PA6MFP_Msk        /*<! SPI1_SS         PA6      MFP Mask */
#define SPI1_SS_PH9_Msk         SYS_GPH_MFP2_PH9MFP_Msk        /*<! SPI1_SS         PH9      MFP Mask */
#define SPI1_SS_PC0_Msk         SYS_GPC_MFP0_PC0MFP_Msk        /*<! SPI1_SS         PC0      MFP Mask */
#define SPI1_SS_PB2_Msk         SYS_GPB_MFP0_PB2MFP_Msk        /*<! SPI1_SS         PB2      MFP Mask */
#define SPI1_SS_PI10_Msk        SYS_GPI_MFP2_PI10MFP_Msk       /*<! SPI1_SS         PI10     MFP Mask */
#define SPI1_SS_PD4_Msk         SYS_GPD_MFP1_PD4MFP_Msk        /*<! SPI1_SS         PD4      MFP Mask */
#define SPI1_SS_PH7_Msk         SYS_GPH_MFP1_PH7MFP_Msk        /*<! SPI1_SS         PH7      MFP Mask */
#define SPI2_CLK_PE8_Msk        SYS_GPE_MFP2_PE8MFP_Msk        /*<! SPI2_CLK        PE8      MFP Mask */
#define SPI2_CLK_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! SPI2_CLK        PA10     MFP Mask */
#define SPI2_CLK_PA13_Msk       SYS_GPA_MFP3_PA13MFP_Msk       /*<! SPI2_CLK        PA13     MFP Mask */
#define SPI2_CLK_PG3_Msk        SYS_GPG_MFP0_PG3MFP_Msk        /*<! SPI2_CLK        PG3      MFP Mask */
#define SPI2_I2SMCLK_PG1_Msk    SYS_GPG_MFP0_PG1MFP_Msk        /*<! SPI2_I2SMCLK    PG1      MFP Mask */
#define SPI2_I2SMCLK_PC13_Msk   SYS_GPC_MFP3_PC13MFP_Msk       /*<! SPI2_I2SMCLK    PC13     MFP Mask */
#define SPI2_I2SMCLK_PB0_Msk    SYS_GPB_MFP0_PB0MFP_Msk        /*<! SPI2_I2SMCLK    PB0      MFP Mask */
#define SPI2_I2SMCLK_PE12_Msk   SYS_GPE_MFP3_PE12MFP_Msk       /*<! SPI2_I2SMCLK    PE12     MFP Mask */
#define SPI2_MISO_PG4_Msk       SYS_GPG_MFP1_PG4MFP_Msk        /*<! SPI2_MISO       PG4      MFP Mask */
#define SPI2_MISO_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! SPI2_MISO       PE9      MFP Mask */
#define SPI2_MISO_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! SPI2_MISO       PA9      MFP Mask */
#define SPI2_MISO_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! SPI2_MISO       PA14     MFP Mask */
#define SPI2_MOSI_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! SPI2_MOSI       PA8      MFP Mask */
#define SPI2_MOSI_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! SPI2_MOSI       PA15     MFP Mask */
#define SPI2_MOSI_PF11_Msk      SYS_GPF_MFP2_PF11MFP_Msk       /*<! SPI2_MOSI       PF11     MFP Mask */
#define SPI2_MOSI_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! SPI2_MOSI       PE10     MFP Mask */
#define SPI2_SS_PG2_Msk         SYS_GPG_MFP0_PG2MFP_Msk        /*<! SPI2_SS         PG2      MFP Mask */
#define SPI2_SS_PA11_Msk        SYS_GPA_MFP2_PA11MFP_Msk       /*<! SPI2_SS         PA11     MFP Mask */
#define SPI2_SS_PA12_Msk        SYS_GPA_MFP3_PA12MFP_Msk       /*<! SPI2_SS         PA12     MFP Mask */
#define SPI2_SS_PE11_Msk        SYS_GPE_MFP2_PE11MFP_Msk       /*<! SPI2_SS         PE11     MFP Mask */
#define SPI3_CLK_PC10_Msk       SYS_GPC_MFP2_PC10MFP_Msk       /*<! SPI3_CLK        PC10     MFP Mask */
#define SPI3_CLK_PB11_Msk       SYS_GPB_MFP2_PB11MFP_Msk       /*<! SPI3_CLK        PB11     MFP Mask */
#define SPI3_CLK_PE4_Msk        SYS_GPE_MFP1_PE4MFP_Msk        /*<! SPI3_CLK        PE4      MFP Mask */
#define SPI3_CLK_PG6_Msk        SYS_GPG_MFP1_PG6MFP_Msk        /*<! SPI3_CLK        PG6      MFP Mask */
#define SPI3_CLK_PB13_Msk       SYS_GPB_MFP3_PB13MFP_Msk       /*!< SPI3_CLK        PB13     MFP Mask */
#define SPI3_I2SMCLK_PF6_Msk    SYS_GPF_MFP1_PF6MFP_Msk        /*<! SPI3_I2SMCLK    PF6      MFP Mask */
#define SPI3_I2SMCLK_PB1_Msk    SYS_GPB_MFP0_PB1MFP_Msk        /*<! SPI3_I2SMCLK    PB1      MFP Mask */
#define SPI3_I2SMCLK_PD14_Msk   SYS_GPD_MFP3_PD14MFP_Msk       /*<! SPI3_I2SMCLK    PD14     MFP Mask */
#define SPI3_I2SMCLK_PE6_Msk    SYS_GPE_MFP1_PE6MFP_Msk        /*<! SPI3_I2SMCLK    PE6      MFP Mask */
#define SPI3_MISO_PG7_Msk       SYS_GPG_MFP1_PG7MFP_Msk        /*<! SPI3_MISO       PG7      MFP Mask */
#define SPI3_MISO_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! SPI3_MISO       PB9      MFP Mask */
#define SPI3_MISO_PC12_Msk      SYS_GPC_MFP3_PC12MFP_Msk       /*<! SPI3_MISO       PC12     MFP Mask */
#define SPI3_MISO_PE3_Msk       SYS_GPE_MFP0_PE3MFP_Msk        /*<! SPI3_MISO       PE3      MFP Mask */
#define SPI3_MISO_PB7_Msk       SYS_GPB_MFP1_PB7MFP_Msk        /*!< SPI3_MISO       PB7      MFP Mask */
#define SPI3_MOSI_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! SPI3_MOSI       PB8      MFP Mask */
#define SPI3_MOSI_PG8_Msk       SYS_GPG_MFP2_PG8MFP_Msk        /*<! SPI3_MOSI       PG8      MFP Mask */
#define SPI3_MOSI_PC11_Msk      SYS_GPC_MFP2_PC11MFP_Msk       /*<! SPI3_MOSI       PC11     MFP Mask */
#define SPI3_MOSI_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! SPI3_MOSI       PE2      MFP Mask */
#define SPI3_MOSI_PB6_Msk       SYS_GPB_MFP1_PB6MFP_Msk        /*!< SPI3_MOSI       PB6      MFP Mask */
#define SPI3_SS_PE5_Msk         SYS_GPE_MFP1_PE5MFP_Msk        /*<! SPI3_SS         PE5      MFP Mask */
#define SPI3_SS_PB10_Msk        SYS_GPB_MFP2_PB10MFP_Msk       /*<! SPI3_SS         PB10     MFP Mask */
#define SPI3_SS_PC9_Msk         SYS_GPC_MFP2_PC9MFP_Msk        /*<! SPI3_SS         PC9      MFP Mask */
#define SPI3_SS_PG5_Msk         SYS_GPG_MFP1_PG5MFP_Msk        /*<! SPI3_SS         PG5      MFP Mask */
#define SPI3_SS_PB12_Msk        SYS_GPB_MFP3_PB12MFP_Msk       /*!< SPI3_SS         PB12     MFP Mask */
#define SPI4_CLK_PB2_Msk        SYS_GPB_MFP0_PB2MFP_Msk        /*<! SPI4_CLK        PB2      MFP Mask */
#define SPI4_MISO_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! SPI4_MISO       PB1      MFP Mask */
#define SPI4_MOSI_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! SPI4_MOSI       PB0      MFP Mask */
#define SPI4_SS_PB3_Msk         SYS_GPB_MFP0_PB3MFP_Msk        /*<! SPI4_SS         PB3      MFP Mask */
#define SPI5_CLK_PF6_Msk        SYS_GPF_MFP1_PF6MFP_Msk        /*<! SPI5_CLK        PF6      MFP Mask */
#define SPI5_CLK_PA6_Msk        SYS_GPA_MFP1_PA6MFP_Msk        /*<! SPI5_CLK        PA6      MFP Mask */
#define SPI5_MISO_PF4_Msk       SYS_GPF_MFP1_PF4MFP_Msk        /*<! SPI5_MISO       PF4      MFP Mask */
#define SPI5_MOSI_PF5_Msk       SYS_GPF_MFP1_PF5MFP_Msk        /*<! SPI5_MOSI       PF5      MFP Mask */
#define SPI5_SS_PA7_Msk         SYS_GPA_MFP1_PA7MFP_Msk        /*<! SPI5_SS         PA7      MFP Mask */
#define SPI5_SS_PF7_Msk         SYS_GPF_MFP1_PF7MFP_Msk        /*<! SPI5_SS         PF7      MFP Mask */
#define SPI6_CLK_PA6_Msk        SYS_GPA_MFP1_PA6MFP_Msk        /*<! SPI6_CLK        PA6      MFP Mask */
#define SPI6_MISO_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! SPI6_MISO       PC7      MFP Mask */
#define SPI6_MOSI_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! SPI6_MOSI       PC6      MFP Mask */
#define SPI6_SS_PA7_Msk         SYS_GPA_MFP1_PA7MFP_Msk        /*<! SPI6_SS         PA7      MFP Mask */
#define SPI7_CLK_PC2_Msk        SYS_GPC_MFP0_PC2MFP_Msk        /*<! SPI7_CLK        PC2      MFP Mask */
#define SPI7_MISO_PC1_Msk       SYS_GPC_MFP0_PC1MFP_Msk        /*<! SPI7_MISO       PC1      MFP Mask */
#define SPI7_MOSI_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! SPI7_MOSI       PC0      MFP Mask */
#define SPI7_SS_PC3_Msk         SYS_GPC_MFP0_PC3MFP_Msk        /*<! SPI7_SS         PC3      MFP Mask */
#define SPI8_CLK_PG10_Msk       SYS_GPG_MFP2_PG10MFP_Msk       /*<! SPI8_CLK        PG10     MFP Mask */
#define SPI8_MISO_PG12_Msk      SYS_GPG_MFP3_PG12MFP_Msk       /*<! SPI8_MISO       PG12     MFP Mask */
#define SPI8_MOSI_PG11_Msk      SYS_GPG_MFP2_PG11MFP_Msk       /*<! SPI8_MOSI       PG11     MFP Mask */
#define SPI8_SS_PG9_Msk         SYS_GPG_MFP2_PG9MFP_Msk        /*<! SPI8_SS         PG9      MFP Mask */
#define SPI9_CLK_PB15_Msk       SYS_GPB_MFP3_PB15MFP_Msk       /*<! SPI9_CLK        PB15     MFP Mask */
#define SPI9_CLK_PD12_Msk       SYS_GPD_MFP3_PD12MFP_Msk       /*<! SPI9_CLK        PD12     MFP Mask */
#define SPI9_MISO_PB13_Msk      SYS_GPB_MFP3_PB13MFP_Msk       /*<! SPI9_MISO       PB13     MFP Mask */
#define SPI9_MISO_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! SPI9_MISO       PD11     MFP Mask */
#define SPI9_MOSI_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! SPI9_MOSI       PD10     MFP Mask */
#define SPI9_MOSI_PC14_Msk      SYS_GPC_MFP3_PC14MFP_Msk       /*<! SPI9_MOSI       PC14     MFP Mask */
#define SPI9_SS_PC13_Msk        SYS_GPC_MFP3_PC13MFP_Msk       /*<! SPI9_SS         PC13     MFP Mask */
#define SPI9_SS_PB14_Msk        SYS_GPB_MFP3_PB14MFP_Msk       /*<! SPI9_SS         PB14     MFP Mask */
#define SPI10_CLK_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! SPI10_CLK       PA13     MFP Mask */
#define SPI10_MISO_PA14_Msk     SYS_GPA_MFP3_PA14MFP_Msk       /*<! SPI10_MISO      PA14     MFP Mask */
#define SPI10_MOSI_PA15_Msk     SYS_GPA_MFP3_PA15MFP_Msk       /*<! SPI10_MOSI      PA15     MFP Mask */
#define SPI10_SS_PA12_Msk       SYS_GPA_MFP3_PA12MFP_Msk       /*<! SPI10_SS        PA12     MFP Mask */
#define SPIM_CLK_PE4_Msk        SYS_GPE_MFP1_PE4MFP_Msk        /*<! SPIM_CLK        PE4      MFP Mask */
#define SPIM_CLK_PJ12_Msk       SYS_GPJ_MFP3_PJ12MFP_Msk       /*<! SPIM_CLK        PJ12     MFP Mask */
#define SPIM_CLK_PG12_Msk       SYS_GPG_MFP3_PG12MFP_Msk       /*<! SPIM_CLK        PG12     MFP Mask */
#define SPIM_CLK_PA2_Msk        SYS_GPA_MFP0_PA2MFP_Msk        /*<! SPIM_CLK        PA2      MFP Mask */
#define SPIM_CLK_PC2_Msk        SYS_GPC_MFP0_PC2MFP_Msk        /*<! SPIM_CLK        PC2      MFP Mask */
#define SPIM_CLK_PJ0_Msk        SYS_GPJ_MFP0_PJ0MFP_Msk        /*<! SPIM_CLK        PJ0      MFP Mask */
#define SPIM_D2_PJ10_Msk        SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! SPIM_D2         PJ10     MFP Mask */
#define SPIM_D2_PE7_Msk         SYS_GPE_MFP1_PE7MFP_Msk        /*<! SPIM_D2         PE7      MFP Mask */
#define SPIM_D2_PI14_Msk        SYS_GPI_MFP3_PI14MFP_Msk       /*<! SPIM_D2         PI14     MFP Mask */
#define SPIM_D2_PG9_Msk         SYS_GPG_MFP2_PG9MFP_Msk        /*<! SPIM_D2         PG9      MFP Mask */
#define SPIM_D2_PC5_Msk         SYS_GPC_MFP1_PC5MFP_Msk        /*<! SPIM_D2         PC5      MFP Mask */
#define SPIM_D2_PA5_Msk         SYS_GPA_MFP1_PA5MFP_Msk        /*<! SPIM_D2         PA5      MFP Mask */
#define SPIM_D3_PJ11_Msk        SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! SPIM_D3         PJ11     MFP Mask */
#define SPIM_D3_PE6_Msk         SYS_GPE_MFP1_PE6MFP_Msk        /*<! SPIM_D3         PE6      MFP Mask */
#define SPIM_D3_PC4_Msk         SYS_GPC_MFP1_PC4MFP_Msk        /*<! SPIM_D3         PC4      MFP Mask */
#define SPIM_D3_PG10_Msk        SYS_GPG_MFP2_PG10MFP_Msk       /*<! SPIM_D3         PG10     MFP Mask */
#define SPIM_D3_PI15_Msk        SYS_GPI_MFP3_PI15MFP_Msk       /*<! SPIM_D3         PI15     MFP Mask */
#define SPIM_D3_PA4_Msk         SYS_GPA_MFP1_PA4MFP_Msk        /*<! SPIM_D3         PA4      MFP Mask */
#define SPIM_MISO_PJ9_Msk       SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! SPIM_MISO       PJ9      MFP Mask */
#define SPIM_MISO_PG13_Msk      SYS_GPG_MFP3_PG13MFP_Msk       /*<! SPIM_MISO       PG13     MFP Mask */
#define SPIM_MISO_PE3_Msk       SYS_GPE_MFP0_PE3MFP_Msk        /*<! SPIM_MISO       PE3      MFP Mask */
#define SPIM_MISO_PC1_Msk       SYS_GPC_MFP0_PC1MFP_Msk        /*<! SPIM_MISO       PC1      MFP Mask */
#define SPIM_MISO_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! SPIM_MISO       PA1      MFP Mask */
#define SPIM_MISO_PI13_Msk      SYS_GPI_MFP3_PI13MFP_Msk       /*<! SPIM_MISO       PI13     MFP Mask */
#define SPIM_MOSI_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! SPIM_MOSI       PA0      MFP Mask */
#define SPIM_MOSI_PG14_Msk      SYS_GPG_MFP3_PG14MFP_Msk       /*<! SPIM_MOSI       PG14     MFP Mask */
#define SPIM_MOSI_PJ13_Msk      SYS_GPJ_MFP3_PJ13MFP_Msk       /*<! SPIM_MOSI       PJ13     MFP Mask */
#define SPIM_MOSI_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! SPIM_MOSI       PC0      MFP Mask */
#define SPIM_MOSI_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! SPIM_MOSI       PA15     MFP Mask */
#define SPIM_MOSI_PJ1_Msk       SYS_GPJ_MFP0_PJ1MFP_Msk        /*<! SPIM_MOSI       PJ1      MFP Mask */
#define SPIM_MOSI_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! SPIM_MOSI       PE2      MFP Mask */
#define SPIM_SS_PJ8_Msk         SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! SPIM_SS         PJ8      MFP Mask */
#define SPIM_SS_PG11_Msk        SYS_GPG_MFP2_PG11MFP_Msk       /*<! SPIM_SS         PG11     MFP Mask */
#define SPIM_SS_PC3_Msk         SYS_GPC_MFP0_PC3MFP_Msk        /*<! SPIM_SS         PC3      MFP Mask */
#define SPIM_SS_PI12_Msk        SYS_GPI_MFP3_PI12MFP_Msk       /*<! SPIM_SS         PI12     MFP Mask */
#define SPIM_SS_PA3_Msk         SYS_GPA_MFP0_PA3MFP_Msk        /*<! SPIM_SS         PA3      MFP Mask */
#define SPIM_SS_PE5_Msk         SYS_GPE_MFP1_PE5MFP_Msk        /*<! SPIM_SS         PE5      MFP Mask */
#define SWDH_CLK_PA10_Msk       SYS_GPA_MFP2_PA10MFP_Msk       /*<! SWDH_CLK        PA10     MFP Mask */
#define SWDH_DAT_PA9_Msk        SYS_GPA_MFP2_PA9MFP_Msk        /*<! SWDH_DAT        PA9      MFP Mask */
#define TAMPER0_PF6_Msk         SYS_GPF_MFP1_PF6MFP_Msk        /*<! TAMPER0         PF6      MFP Mask */
#define TAMPER1_PF7_Msk         SYS_GPF_MFP1_PF7MFP_Msk        /*<! TAMPER1         PF7      MFP Mask */
#define TAMPER2_PF8_Msk         SYS_GPF_MFP2_PF8MFP_Msk        /*<! TAMPER2         PF8      MFP Mask */
#define TAMPER3_PF9_Msk         SYS_GPF_MFP2_PF9MFP_Msk        /*<! TAMPER3         PF9      MFP Mask */
#define TAMPER4_PF10_Msk        SYS_GPF_MFP2_PF10MFP_Msk       /*<! TAMPER4         PF10     MFP Mask */
#define TAMPER5_PF11_Msk        SYS_GPF_MFP2_PF11MFP_Msk       /*<! TAMPER5         PF11     MFP Mask */
#define TM0_PC7_Msk             SYS_GPC_MFP1_PC7MFP_Msk        /*<! TM0             PC7      MFP Mask */
#define TM0_PB5_Msk             SYS_GPB_MFP1_PB5MFP_Msk        /*<! TM0             PB5      MFP Mask */
#define TM0_PG2_Msk             SYS_GPG_MFP0_PG2MFP_Msk        /*<! TM0             PG2      MFP Mask */
#define TM0_EXT_PA11_Msk        SYS_GPA_MFP2_PA11MFP_Msk       /*<! TM0_EXT         PA11     MFP Mask */
#define TM0_EXT_PH0_Msk         SYS_GPH_MFP0_PH0MFP_Msk        /*<! TM0_EXT         PH0      MFP Mask */
#define TM0_EXT_PB15_Msk        SYS_GPB_MFP3_PB15MFP_Msk       /*<! TM0_EXT         PB15     MFP Mask */
#define TM1_PC6_Msk             SYS_GPC_MFP1_PC6MFP_Msk        /*<! TM1             PC6      MFP Mask */
#define TM1_PB4_Msk             SYS_GPB_MFP1_PB4MFP_Msk        /*<! TM1             PB4      MFP Mask */
#define TM1_PC14_Msk            SYS_GPC_MFP3_PC14MFP_Msk       /*<! TM1             PC14     MFP Mask */
#define TM1_PG3_Msk             SYS_GPG_MFP0_PG3MFP_Msk        /*<! TM1             PG3      MFP Mask */
#define TM1_EXT_PA10_Msk        SYS_GPA_MFP2_PA10MFP_Msk       /*<! TM1_EXT         PA10     MFP Mask */
#define TM1_EXT_PB14_Msk        SYS_GPB_MFP3_PB14MFP_Msk       /*<! TM1_EXT         PB14     MFP Mask */
#define TM1_EXT_PH1_Msk         SYS_GPH_MFP0_PH1MFP_Msk        /*<! TM1_EXT         PH1      MFP Mask */
#define TM2_PB3_Msk             SYS_GPB_MFP0_PB3MFP_Msk        /*<! TM2             PB3      MFP Mask */
#define TM2_PG4_Msk             SYS_GPG_MFP1_PG4MFP_Msk        /*<! TM2             PG4      MFP Mask */
#define TM2_PD0_Msk             SYS_GPD_MFP0_PD0MFP_Msk        /*<! TM2             PD0      MFP Mask */
#define TM2_PA7_Msk             SYS_GPA_MFP1_PA7MFP_Msk        /*<! TM2             PA7      MFP Mask */
#define TM2_EXT_PB13_Msk        SYS_GPB_MFP3_PB13MFP_Msk       /*<! TM2_EXT         PB13     MFP Mask */
#define TM2_EXT_PH2_Msk         SYS_GPH_MFP0_PH2MFP_Msk        /*<! TM2_EXT         PH2      MFP Mask */
#define TM2_EXT_PA9_Msk         SYS_GPA_MFP2_PA9MFP_Msk        /*<! TM2_EXT         PA9      MFP Mask */
#define TM3_PF11_Msk            SYS_GPF_MFP2_PF11MFP_Msk       /*<! TM3             PF11     MFP Mask */
#define TM3_PA6_Msk             SYS_GPA_MFP1_PA6MFP_Msk        /*<! TM3             PA6      MFP Mask */
#define TM3_PB2_Msk             SYS_GPB_MFP0_PB2MFP_Msk        /*<! TM3             PB2      MFP Mask */
#define TM3_EXT_PA8_Msk         SYS_GPA_MFP2_PA8MFP_Msk        /*<! TM3_EXT         PA8      MFP Mask */
#define TM3_EXT_PH3_Msk         SYS_GPH_MFP0_PH3MFP_Msk        /*<! TM3_EXT         PH3      MFP Mask */
#define TM3_EXT_PB12_Msk        SYS_GPB_MFP3_PB12MFP_Msk       /*<! TM3_EXT         PB12     MFP Mask */
#define TRACE_CLK_PE12_Msk      SYS_GPE_MFP3_PE12MFP_Msk       /*<! TRACE_CLK       PE12     MFP Mask */
#define TRACE_DATA0_PE11_Msk    SYS_GPE_MFP2_PE11MFP_Msk       /*<! TRACE_DATA0     PE11     MFP Mask */
#define TRACE_DATA1_PE10_Msk    SYS_GPE_MFP2_PE10MFP_Msk       /*<! TRACE_DATA1     PE10     MFP Mask */
#define TRACE_DATA2_PE9_Msk     SYS_GPE_MFP2_PE9MFP_Msk        /*<! TRACE_DATA2     PE9      MFP Mask */
#define TRACE_DATA3_PE8_Msk     SYS_GPE_MFP2_PE8MFP_Msk        /*<! TRACE_DATA3     PE8      MFP Mask */
#define UART0_RXD_PA0_Msk       SYS_GPA_MFP0_PA0MFP_Msk        /*<! UART0_RXD       PA0      MFP Mask */
#define UART0_RXD_PC11_Msk      SYS_GPC_MFP2_PC11MFP_Msk       /*<! UART0_RXD       PC11     MFP Mask */
#define UART0_RXD_PH11_Msk      SYS_GPH_MFP2_PH11MFP_Msk       /*<! UART0_RXD       PH11     MFP Mask */
#define UART0_RXD_PA4_Msk       SYS_GPA_MFP1_PA4MFP_Msk        /*<! UART0_RXD       PA4      MFP Mask */
#define UART0_RXD_PA6_Msk       SYS_GPA_MFP1_PA6MFP_Msk        /*<! UART0_RXD       PA6      MFP Mask */
#define UART0_RXD_PD2_Msk       SYS_GPD_MFP0_PD2MFP_Msk        /*<! UART0_RXD       PD2      MFP Mask */
#define UART0_RXD_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! UART0_RXD       PB8      MFP Mask */
#define UART0_RXD_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! UART0_RXD       PF1      MFP Mask */
#define UART0_RXD_PA15_Msk      SYS_GPA_MFP3_PA15MFP_Msk       /*<! UART0_RXD       PA15     MFP Mask */
#define UART0_RXD_PF2_Msk       SYS_GPF_MFP0_PF2MFP_Msk        /*<! UART0_RXD       PF2      MFP Mask */
#define UART0_RXD_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! UART0_RXD       PB12     MFP Mask */
#define UART0_TXD_PD3_Msk       SYS_GPD_MFP0_PD3MFP_Msk        /*<! UART0_TXD       PD3      MFP Mask */
#define UART0_TXD_PA5_Msk       SYS_GPA_MFP1_PA5MFP_Msk        /*<! UART0_TXD       PA5      MFP Mask */
#define UART0_TXD_PF0_Msk       SYS_GPF_MFP0_PF0MFP_Msk        /*<! UART0_TXD       PF0      MFP Mask */
#define UART0_TXD_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! UART0_TXD       PB9      MFP Mask */
#define UART0_TXD_PF3_Msk       SYS_GPF_MFP0_PF3MFP_Msk        /*<! UART0_TXD       PF3      MFP Mask */
#define UART0_TXD_PA1_Msk       SYS_GPA_MFP0_PA1MFP_Msk        /*<! UART0_TXD       PA1      MFP Mask */
#define UART0_TXD_PA7_Msk       SYS_GPA_MFP1_PA7MFP_Msk        /*<! UART0_TXD       PA7      MFP Mask */
#define UART0_TXD_PA14_Msk      SYS_GPA_MFP3_PA14MFP_Msk       /*<! UART0_TXD       PA14     MFP Mask */
#define UART0_TXD_PC12_Msk      SYS_GPC_MFP3_PC12MFP_Msk       /*<! UART0_TXD       PC12     MFP Mask */
#define UART0_TXD_PB13_Msk      SYS_GPB_MFP3_PB13MFP_Msk       /*<! UART0_TXD       PB13     MFP Mask */
#define UART0_TXD_PH10_Msk      SYS_GPH_MFP2_PH10MFP_Msk       /*<! UART0_TXD       PH10     MFP Mask */
#define UART0_nCTS_PC7_Msk      SYS_GPC_MFP1_PC7MFP_Msk        /*<! UART0_nCTS      PC7      MFP Mask */
#define UART0_nCTS_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! UART0_nCTS      PB15     MFP Mask */
#define UART0_nCTS_PA5_Msk      SYS_GPA_MFP1_PA5MFP_Msk        /*<! UART0_nCTS      PA5      MFP Mask */
#define UART0_nCTS_PB11_Msk     SYS_GPB_MFP2_PB11MFP_Msk       /*<! UART0_nCTS      PB11     MFP Mask */
#define UART0_nRTS_PA4_Msk      SYS_GPA_MFP1_PA4MFP_Msk        /*<! UART0_nRTS      PA4      MFP Mask */
#define UART0_nRTS_PB14_Msk     SYS_GPB_MFP3_PB14MFP_Msk       /*<! UART0_nRTS      PB14     MFP Mask */
#define UART0_nRTS_PB10_Msk     SYS_GPB_MFP2_PB10MFP_Msk       /*<! UART0_nRTS      PB10     MFP Mask */
#define UART0_nRTS_PC6_Msk      SYS_GPC_MFP1_PC6MFP_Msk        /*<! UART0_nRTS      PC6      MFP Mask */
#define UART1_RXD_PH9_Msk       SYS_GPH_MFP2_PH9MFP_Msk        /*<! UART1_RXD       PH9      MFP Mask */
#define UART1_RXD_PD6_Msk       SYS_GPD_MFP1_PD6MFP_Msk        /*<! UART1_RXD       PD6      MFP Mask */
#define UART1_RXD_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! UART1_RXD       PF1      MFP Mask */
#define UART1_RXD_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! UART1_RXD       PA2      MFP Mask */
#define UART1_RXD_PC8_Msk       SYS_GPC_MFP2_PC8MFP_Msk        /*<! UART1_RXD       PC8      MFP Mask */
#define UART1_RXD_PB2_Msk       SYS_GPB_MFP0_PB2MFP_Msk        /*<! UART1_RXD       PB2      MFP Mask */
#define UART1_RXD_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! UART1_RXD       PD10     MFP Mask */
#define UART1_RXD_PG1_Msk       SYS_GPG_MFP0_PG1MFP_Msk        /*<! UART1_RXD       PG1      MFP Mask */
#define UART1_RXD_PB6_Msk       SYS_GPB_MFP1_PB6MFP_Msk        /*<! UART1_RXD       PB6      MFP Mask */
#define UART1_RXD_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! UART1_RXD       PA8      MFP Mask */
#define UART1_TXD_PA3_Msk       SYS_GPA_MFP0_PA3MFP_Msk        /*<! UART1_TXD       PA3      MFP Mask */
#define UART1_TXD_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! UART1_TXD       PD11     MFP Mask */
#define UART1_TXD_PH8_Msk       SYS_GPH_MFP2_PH8MFP_Msk        /*<! UART1_TXD       PH8      MFP Mask */
#define UART1_TXD_PB3_Msk       SYS_GPB_MFP0_PB3MFP_Msk        /*<! UART1_TXD       PB3      MFP Mask */
#define UART1_TXD_PB7_Msk       SYS_GPB_MFP1_PB7MFP_Msk        /*<! UART1_TXD       PB7      MFP Mask */
#define UART1_TXD_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! UART1_TXD       PA9      MFP Mask */
#define UART1_TXD_PF0_Msk       SYS_GPF_MFP0_PF0MFP_Msk        /*<! UART1_TXD       PF0      MFP Mask */
#define UART1_TXD_PE13_Msk      SYS_GPE_MFP3_PE13MFP_Msk       /*<! UART1_TXD       PE13     MFP Mask */
#define UART1_TXD_PD7_Msk       SYS_GPD_MFP1_PD7MFP_Msk        /*<! UART1_TXD       PD7      MFP Mask */
#define UART1_TXD_PG0_Msk       SYS_GPG_MFP0_PG0MFP_Msk        /*<! UART1_TXD       PG0      MFP Mask */
#define UART1_nCTS_PE11_Msk     SYS_GPE_MFP2_PE11MFP_Msk       /*<! UART1_nCTS      PE11     MFP Mask */
#define UART1_nCTS_PB9_Msk      SYS_GPB_MFP2_PB9MFP_Msk        /*<! UART1_nCTS      PB9      MFP Mask */
#define UART1_nCTS_PA1_Msk      SYS_GPA_MFP0_PA1MFP_Msk        /*<! UART1_nCTS      PA1      MFP Mask */
#define UART1_nRTS_PE12_Msk     SYS_GPE_MFP3_PE12MFP_Msk       /*<! UART1_nRTS      PE12     MFP Mask */
#define UART1_nRTS_PA0_Msk      SYS_GPA_MFP0_PA0MFP_Msk        /*<! UART1_nRTS      PA0      MFP Mask */
#define UART1_nRTS_PB8_Msk      SYS_GPB_MFP2_PB8MFP_Msk        /*<! UART1_nRTS      PB8      MFP Mask */
#define UART2_RXD_PC0_Msk       SYS_GPC_MFP0_PC0MFP_Msk        /*<! UART2_RXD       PC0      MFP Mask */
#define UART2_RXD_PE9_Msk       SYS_GPE_MFP2_PE9MFP_Msk        /*<! UART2_RXD       PE9      MFP Mask */
#define UART2_RXD_PB0_Msk       SYS_GPB_MFP0_PB0MFP_Msk        /*<! UART2_RXD       PB0      MFP Mask */
#define UART2_RXD_PF1_Msk       SYS_GPF_MFP0_PF1MFP_Msk        /*<! UART2_RXD       PF1      MFP Mask */
#define UART2_RXD_PI7_Msk       SYS_GPI_MFP1_PI7MFP_Msk        /*<! UART2_RXD       PI7      MFP Mask */
#define UART2_RXD_PD12_Msk      SYS_GPD_MFP3_PD12MFP_Msk       /*<! UART2_RXD       PD12     MFP Mask */
#define UART2_RXD_PE15_Msk      SYS_GPE_MFP3_PE15MFP_Msk       /*<! UART2_RXD       PE15     MFP Mask */
#define UART2_RXD_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! UART2_RXD       PC4      MFP Mask */
#define UART2_RXD_PF5_Msk       SYS_GPF_MFP1_PF5MFP_Msk        /*<! UART2_RXD       PF5      MFP Mask */
#define UART2_RXD_PG0_Msk       SYS_GPG_MFP0_PG0MFP_Msk        /*<! UART2_RXD       PG0      MFP Mask */
#define UART2_RXD_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! UART2_RXD       PB4      MFP Mask */
#define UART2_RXD_PI11_Msk      SYS_GPI_MFP2_PI11MFP_Msk       /*<! UART2_RXD       PI11     MFP Mask */
#define UART2_TXD_PE8_Msk       SYS_GPE_MFP2_PE8MFP_Msk        /*<! UART2_TXD       PE8      MFP Mask */
#define UART2_TXD_PC5_Msk       SYS_GPC_MFP1_PC5MFP_Msk        /*<! UART2_TXD       PC5      MFP Mask */
#define UART2_TXD_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! UART2_TXD       PB5      MFP Mask */
#define UART2_TXD_PF0_Msk       SYS_GPF_MFP0_PF0MFP_Msk        /*<! UART2_TXD       PF0      MFP Mask */
#define UART2_TXD_PG1_Msk       SYS_GPG_MFP0_PG1MFP_Msk        /*<! UART2_TXD       PG1      MFP Mask */
#define UART2_TXD_PC13_Msk      SYS_GPC_MFP3_PC13MFP_Msk       /*<! UART2_TXD       PC13     MFP Mask */
#define UART2_TXD_PE14_Msk      SYS_GPE_MFP3_PE14MFP_Msk       /*<! UART2_TXD       PE14     MFP Mask */
#define UART2_TXD_PF4_Msk       SYS_GPF_MFP1_PF4MFP_Msk        /*<! UART2_TXD       PF4      MFP Mask */
#define UART2_TXD_PI10_Msk      SYS_GPI_MFP2_PI10MFP_Msk       /*<! UART2_TXD       PI10     MFP Mask */
#define UART2_TXD_PI6_Msk       SYS_GPI_MFP1_PI6MFP_Msk        /*<! UART2_TXD       PI6      MFP Mask */
#define UART2_TXD_PB1_Msk       SYS_GPB_MFP0_PB1MFP_Msk        /*<! UART2_TXD       PB1      MFP Mask */
#define UART2_TXD_PC1_Msk       SYS_GPC_MFP0_PC1MFP_Msk        /*<! UART2_TXD       PC1      MFP Mask */
#define UART2_nCTS_PD9_Msk      SYS_GPD_MFP2_PD9MFP_Msk        /*<! UART2_nCTS      PD9      MFP Mask */
#define UART2_nCTS_PC2_Msk      SYS_GPC_MFP0_PC2MFP_Msk        /*<! UART2_nCTS      PC2      MFP Mask */
#define UART2_nCTS_PI9_Msk      SYS_GPI_MFP2_PI9MFP_Msk        /*<! UART2_nCTS      PI9      MFP Mask */
#define UART2_nCTS_PF5_Msk      SYS_GPF_MFP1_PF5MFP_Msk        /*<! UART2_nCTS      PF5      MFP Mask */
#define UART2_nRTS_PI8_Msk      SYS_GPI_MFP2_PI8MFP_Msk        /*<! UART2_nRTS      PI8      MFP Mask */
#define UART2_nRTS_PF4_Msk      SYS_GPF_MFP1_PF4MFP_Msk        /*<! UART2_nRTS      PF4      MFP Mask */
#define UART2_nRTS_PD8_Msk      SYS_GPD_MFP2_PD8MFP_Msk        /*<! UART2_nRTS      PD8      MFP Mask */
#define UART2_nRTS_PC3_Msk      SYS_GPC_MFP0_PC3MFP_Msk        /*<! UART2_nRTS      PC3      MFP Mask */
#define UART3_RXD_PI15_Msk      SYS_GPI_MFP3_PI15MFP_Msk       /*<! UART3_RXD       PI15     MFP Mask */
#define UART3_RXD_PE0_Msk       SYS_GPE_MFP0_PE0MFP_Msk        /*<! UART3_RXD       PE0      MFP Mask */
#define UART3_RXD_PE11_Msk      SYS_GPE_MFP2_PE11MFP_Msk       /*<! UART3_RXD       PE11     MFP Mask */
#define UART3_RXD_PB14_Msk      SYS_GPB_MFP3_PB14MFP_Msk       /*<! UART3_RXD       PB14     MFP Mask */
#define UART3_RXD_PC9_Msk       SYS_GPC_MFP2_PC9MFP_Msk        /*<! UART3_RXD       PC9      MFP Mask */
#define UART3_RXD_PD0_Msk       SYS_GPD_MFP0_PD0MFP_Msk        /*<! UART3_RXD       PD0      MFP Mask */
#define UART3_RXD_PC2_Msk       SYS_GPC_MFP0_PC2MFP_Msk        /*<! UART3_RXD       PC2      MFP Mask */
#define UART3_TXD_PB15_Msk      SYS_GPB_MFP3_PB15MFP_Msk       /*<! UART3_TXD       PB15     MFP Mask */
#define UART3_TXD_PI14_Msk      SYS_GPI_MFP3_PI14MFP_Msk       /*<! UART3_TXD       PI14     MFP Mask */
#define UART3_TXD_PD1_Msk       SYS_GPD_MFP0_PD1MFP_Msk        /*<! UART3_TXD       PD1      MFP Mask */
#define UART3_TXD_PE10_Msk      SYS_GPE_MFP2_PE10MFP_Msk       /*<! UART3_TXD       PE10     MFP Mask */
#define UART3_TXD_PE1_Msk       SYS_GPE_MFP0_PE1MFP_Msk        /*<! UART3_TXD       PE1      MFP Mask */
#define UART3_TXD_PC3_Msk       SYS_GPC_MFP0_PC3MFP_Msk        /*<! UART3_TXD       PC3      MFP Mask */
#define UART3_TXD_PC10_Msk      SYS_GPC_MFP2_PC10MFP_Msk       /*<! UART3_TXD       PC10     MFP Mask */
#define UART3_nCTS_PB12_Msk     SYS_GPB_MFP3_PB12MFP_Msk       /*<! UART3_nCTS      PB12     MFP Mask */
#define UART3_nCTS_PH9_Msk      SYS_GPH_MFP2_PH9MFP_Msk        /*<! UART3_nCTS      PH9      MFP Mask */
#define UART3_nCTS_PD2_Msk      SYS_GPD_MFP0_PD2MFP_Msk        /*<! UART3_nCTS      PD2      MFP Mask */
#define UART3_nRTS_PB13_Msk     SYS_GPB_MFP3_PB13MFP_Msk       /*<! UART3_nRTS      PB13     MFP Mask */
#define UART3_nRTS_PH8_Msk      SYS_GPH_MFP2_PH8MFP_Msk        /*<! UART3_nRTS      PH8      MFP Mask */
#define UART3_nRTS_PD3_Msk      SYS_GPD_MFP0_PD3MFP_Msk        /*<! UART3_nRTS      PD3      MFP Mask */
#define UART4_RXD_PB10_Msk      SYS_GPB_MFP2_PB10MFP_Msk       /*<! UART4_RXD       PB10     MFP Mask */
#define UART4_RXD_PI13_Msk      SYS_GPI_MFP3_PI13MFP_Msk       /*<! UART4_RXD       PI13     MFP Mask */
#define UART4_RXD_PH3_Msk       SYS_GPH_MFP0_PH3MFP_Msk        /*<! UART4_RXD       PH3      MFP Mask */
#define UART4_RXD_PA13_Msk      SYS_GPA_MFP3_PA13MFP_Msk       /*<! UART4_RXD       PA13     MFP Mask */
#define UART4_RXD_PH11_Msk      SYS_GPH_MFP2_PH11MFP_Msk       /*<! UART4_RXD       PH11     MFP Mask */
#define UART4_RXD_PA2_Msk       SYS_GPA_MFP0_PA2MFP_Msk        /*<! UART4_RXD       PA2      MFP Mask */
#define UART4_RXD_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! UART4_RXD       PC6      MFP Mask */
#define UART4_RXD_PF6_Msk       SYS_GPF_MFP1_PF6MFP_Msk        /*<! UART4_RXD       PF6      MFP Mask */
#define UART4_RXD_PC4_Msk       SYS_GPC_MFP1_PC4MFP_Msk        /*<! UART4_RXD       PC4      MFP Mask */
#define UART4_TXD_PA12_Msk      SYS_GPA_MFP3_PA12MFP_Msk       /*<! UART4_TXD       PA12     MFP Mask */
#define UART4_TXD_PB11_Msk      SYS_GPB_MFP2_PB11MFP_Msk       /*<! UART4_TXD       PB11     MFP Mask */
#define UART4_TXD_PF7_Msk       SYS_GPF_MFP1_PF7MFP_Msk        /*<! UART4_TXD       PF7      MFP Mask */
#define UART4_TXD_PH2_Msk       SYS_GPH_MFP0_PH2MFP_Msk        /*<! UART4_TXD       PH2      MFP Mask */
#define UART4_TXD_PI12_Msk      SYS_GPI_MFP3_PI12MFP_Msk       /*<! UART4_TXD       PI12     MFP Mask */
#define UART4_TXD_PC5_Msk       SYS_GPC_MFP1_PC5MFP_Msk        /*<! UART4_TXD       PC5      MFP Mask */
#define UART4_TXD_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! UART4_TXD       PC7      MFP Mask */
#define UART4_TXD_PA3_Msk       SYS_GPA_MFP0_PA3MFP_Msk        /*<! UART4_TXD       PA3      MFP Mask */
#define UART4_TXD_PH10_Msk      SYS_GPH_MFP2_PH10MFP_Msk       /*<! UART4_TXD       PH10     MFP Mask */
#define UART4_nCTS_PC8_Msk      SYS_GPC_MFP2_PC8MFP_Msk        /*<! UART4_nCTS      PC8      MFP Mask */
#define UART4_nCTS_PE1_Msk      SYS_GPE_MFP0_PE1MFP_Msk        /*<! UART4_nCTS      PE1      MFP Mask */
#define UART4_nRTS_PE0_Msk      SYS_GPE_MFP0_PE0MFP_Msk        /*<! UART4_nRTS      PE0      MFP Mask */
#define UART4_nRTS_PE13_Msk     SYS_GPE_MFP3_PE13MFP_Msk       /*<! UART4_nRTS      PE13     MFP Mask */
#define UART5_RXD_PF10_Msk      SYS_GPF_MFP2_PF10MFP_Msk       /*<! UART5_RXD       PF10     MFP Mask */
#define UART5_RXD_PB4_Msk       SYS_GPB_MFP1_PB4MFP_Msk        /*<! UART5_RXD       PB4      MFP Mask */
#define UART5_RXD_PH1_Msk       SYS_GPH_MFP0_PH1MFP_Msk        /*<! UART5_RXD       PH1      MFP Mask */
#define UART5_RXD_PE6_Msk       SYS_GPE_MFP1_PE6MFP_Msk        /*<! UART5_RXD       PE6      MFP Mask */
#define UART5_RXD_PA4_Msk       SYS_GPA_MFP1_PA4MFP_Msk        /*<! UART5_RXD       PA4      MFP Mask */
#define UART5_TXD_PB5_Msk       SYS_GPB_MFP1_PB5MFP_Msk        /*<! UART5_TXD       PB5      MFP Mask */
#define UART5_TXD_PF11_Msk      SYS_GPF_MFP2_PF11MFP_Msk       /*<! UART5_TXD       PF11     MFP Mask */
#define UART5_TXD_PE7_Msk       SYS_GPE_MFP1_PE7MFP_Msk        /*<! UART5_TXD       PE7      MFP Mask */
#define UART5_TXD_PA5_Msk       SYS_GPA_MFP1_PA5MFP_Msk        /*<! UART5_TXD       PA5      MFP Mask */
#define UART5_TXD_PH0_Msk       SYS_GPH_MFP0_PH0MFP_Msk        /*<! UART5_TXD       PH0      MFP Mask */
#define UART5_nCTS_PF8_Msk      SYS_GPF_MFP2_PF8MFP_Msk        /*<! UART5_nCTS      PF8      MFP Mask */
#define UART5_nCTS_PH3_Msk      SYS_GPH_MFP0_PH3MFP_Msk        /*<! UART5_nCTS      PH3      MFP Mask */
#define UART5_nCTS_PB2_Msk      SYS_GPB_MFP0_PB2MFP_Msk        /*<! UART5_nCTS      PB2      MFP Mask */
#define UART5_nRTS_PF9_Msk      SYS_GPF_MFP2_PF9MFP_Msk        /*<! UART5_nRTS      PF9      MFP Mask */
#define UART5_nRTS_PH2_Msk      SYS_GPH_MFP0_PH2MFP_Msk        /*<! UART5_nRTS      PH2      MFP Mask */
#define UART5_nRTS_PB3_Msk      SYS_GPB_MFP0_PB3MFP_Msk        /*<! UART5_nRTS      PB3      MFP Mask */
#define UART6_RXD_PE15_Msk      SYS_GPE_MFP3_PE15MFP_Msk       /*<! UART6_RXD       PE15     MFP Mask */
#define UART6_RXD_PC6_Msk       SYS_GPC_MFP1_PC6MFP_Msk        /*<! UART6_RXD       PC6      MFP Mask */
#define UART6_RXD_PH5_Msk       SYS_GPH_MFP1_PH5MFP_Msk        /*<! UART6_RXD       PH5      MFP Mask */
#define UART6_RXD_PG14_Msk      SYS_GPG_MFP3_PG14MFP_Msk       /*<! UART6_RXD       PG14     MFP Mask */
#define UART6_RXD_PA10_Msk      SYS_GPA_MFP2_PA10MFP_Msk       /*<! UART6_RXD       PA10     MFP Mask */
#define UART6_RXD_PD13_Msk      SYS_GPD_MFP3_PD13MFP_Msk       /*<! UART6_RXD       PD13     MFP Mask */
#define UART6_RXD_PC11_Msk      SYS_GPC_MFP2_PC11MFP_Msk       /*<! UART6_RXD       PC11     MFP Mask */
#define UART6_RXD_PE4_Msk       SYS_GPE_MFP1_PE4MFP_Msk        /*<! UART6_RXD       PE4      MFP Mask */
#define UART6_RXD_PJ11_Msk      SYS_GPJ_MFP2_PJ11MFP_Msk       /*<! UART6_RXD       PJ11     MFP Mask */
#define UART6_TXD_PG13_Msk      SYS_GPG_MFP3_PG13MFP_Msk       /*<! UART6_TXD       PG13     MFP Mask */
#define UART6_TXD_PE14_Msk      SYS_GPE_MFP3_PE14MFP_Msk       /*<! UART6_TXD       PE14     MFP Mask */
#define UART6_TXD_PC12_Msk      SYS_GPC_MFP3_PC12MFP_Msk       /*<! UART6_TXD       PC12     MFP Mask */
#define UART6_TXD_PC7_Msk       SYS_GPC_MFP1_PC7MFP_Msk        /*<! UART6_TXD       PC7      MFP Mask */
#define UART6_TXD_PH4_Msk       SYS_GPH_MFP1_PH4MFP_Msk        /*<! UART6_TXD       PH4      MFP Mask */
#define UART6_TXD_PJ10_Msk      SYS_GPJ_MFP2_PJ10MFP_Msk       /*<! UART6_TXD       PJ10     MFP Mask */
#define UART6_TXD_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! UART6_TXD       PA11     MFP Mask */
#define UART6_TXD_PE5_Msk       SYS_GPE_MFP1_PE5MFP_Msk        /*<! UART6_TXD       PE5      MFP Mask */
#define UART6_nCTS_PC9_Msk      SYS_GPC_MFP2_PC9MFP_Msk        /*<! UART6_nCTS      PC9      MFP Mask */
#define UART6_nCTS_PE2_Msk      SYS_GPE_MFP0_PE2MFP_Msk        /*<! UART6_nCTS      PE2      MFP Mask */
#define UART6_nRTS_PC10_Msk     SYS_GPC_MFP2_PC10MFP_Msk       /*<! UART6_nRTS      PC10     MFP Mask */
#define UART6_nRTS_PE3_Msk      SYS_GPE_MFP0_PE3MFP_Msk        /*<! UART6_nRTS      PE3      MFP Mask */
#define UART7_RXD_PD8_Msk       SYS_GPD_MFP2_PD8MFP_Msk        /*<! UART7_RXD       PD8      MFP Mask */
#define UART7_RXD_PG12_Msk      SYS_GPG_MFP3_PG12MFP_Msk       /*<! UART7_RXD       PG12     MFP Mask */
#define UART7_RXD_PJ9_Msk       SYS_GPJ_MFP2_PJ9MFP_Msk        /*<! UART7_RXD       PJ9      MFP Mask */
#define UART7_RXD_PH7_Msk       SYS_GPH_MFP1_PH7MFP_Msk        /*<! UART7_RXD       PH7      MFP Mask */
#define UART7_RXD_PB8_Msk       SYS_GPB_MFP2_PB8MFP_Msk        /*<! UART7_RXD       PB8      MFP Mask */
#define UART7_RXD_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! UART7_RXD       PE2      MFP Mask */
#define UART7_RXD_PA8_Msk       SYS_GPA_MFP2_PA8MFP_Msk        /*<! UART7_RXD       PA8      MFP Mask */
#define UART7_TXD_PE3_Msk       SYS_GPE_MFP0_PE3MFP_Msk        /*<! UART7_TXD       PE3      MFP Mask */
#define UART7_TXD_PG11_Msk      SYS_GPG_MFP2_PG11MFP_Msk       /*<! UART7_TXD       PG11     MFP Mask */
#define UART7_TXD_PA9_Msk       SYS_GPA_MFP2_PA9MFP_Msk        /*<! UART7_TXD       PA9      MFP Mask */
#define UART7_TXD_PJ8_Msk       SYS_GPJ_MFP2_PJ8MFP_Msk        /*<! UART7_TXD       PJ8      MFP Mask */
#define UART7_TXD_PB9_Msk       SYS_GPB_MFP2_PB9MFP_Msk        /*<! UART7_TXD       PB9      MFP Mask */
#define UART7_TXD_PD9_Msk       SYS_GPD_MFP2_PD9MFP_Msk        /*<! UART7_TXD       PD9      MFP Mask */
#define UART7_TXD_PH6_Msk       SYS_GPH_MFP1_PH6MFP_Msk        /*<! UART7_TXD       PH6      MFP Mask */
#define UART7_nCTS_PE4_Msk      SYS_GPE_MFP1_PE4MFP_Msk        /*<! UART7_nCTS      PE4      MFP Mask */
#define UART7_nCTS_PH5_Msk      SYS_GPH_MFP1_PH5MFP_Msk        /*<! UART7_nCTS      PH5      MFP Mask */
#define UART7_nRTS_PE5_Msk      SYS_GPE_MFP1_PE5MFP_Msk        /*<! UART7_nRTS      PE5      MFP Mask */
#define UART7_nRTS_PH4_Msk      SYS_GPH_MFP1_PH4MFP_Msk        /*<! UART7_nRTS      PH4      MFP Mask */
#define UART8_RXD_PJ1_Msk       SYS_GPJ_MFP0_PJ1MFP_Msk        /*<! UART8_RXD       PJ1      MFP Mask */
#define UART8_RXD_PJ5_Msk       SYS_GPJ_MFP1_PJ5MFP_Msk        /*<! UART8_RXD       PJ5      MFP Mask */
#define UART8_RXD_PE0_Msk       SYS_GPE_MFP0_PE0MFP_Msk        /*<! UART8_RXD       PE0      MFP Mask */
#define UART8_RXD_PD10_Msk      SYS_GPD_MFP2_PD10MFP_Msk       /*<! UART8_RXD       PD10     MFP Mask */
#define UART8_TXD_PE1_Msk       SYS_GPE_MFP0_PE1MFP_Msk        /*<! UART8_TXD       PE1      MFP Mask */
#define UART8_TXD_PD11_Msk      SYS_GPD_MFP2_PD11MFP_Msk       /*<! UART8_TXD       PD11     MFP Mask */
#define UART8_TXD_PJ0_Msk       SYS_GPJ_MFP0_PJ0MFP_Msk        /*<! UART8_TXD       PJ0      MFP Mask */
#define UART8_TXD_PJ4_Msk       SYS_GPJ_MFP1_PJ4MFP_Msk        /*<! UART8_TXD       PJ4      MFP Mask */
#define UART8_nCTS_PJ2_Msk      SYS_GPJ_MFP0_PJ2MFP_Msk        /*<! UART8_nCTS      PJ2      MFP Mask */
#define UART8_nCTS_PC13_Msk     SYS_GPC_MFP3_PC13MFP_Msk       /*<! UART8_nCTS      PC13     MFP Mask */
#define UART8_nCTS_PE3_Msk      SYS_GPE_MFP0_PE3MFP_Msk        /*<! UART8_nCTS      PE3      MFP Mask */
#define UART8_nCTS_PI14_Msk     SYS_GPI_MFP3_PI14MFP_Msk       /*<! UART8_nCTS      PI14     MFP Mask */
#define UART8_nRTS_PI15_Msk     SYS_GPI_MFP3_PI15MFP_Msk       /*<! UART8_nRTS      PI15     MFP Mask */
#define UART8_nRTS_PJ3_Msk      SYS_GPJ_MFP0_PJ3MFP_Msk        /*<! UART8_nRTS      PJ3      MFP Mask */
#define UART8_nRTS_PD12_Msk     SYS_GPD_MFP3_PD12MFP_Msk       /*<! UART8_nRTS      PD12     MFP Mask */
#define UART8_nRTS_PE2_Msk      SYS_GPE_MFP0_PE2MFP_Msk        /*<! UART8_nRTS      PE2      MFP Mask */
#define UART9_RXD_PF2_Msk       SYS_GPF_MFP0_PF2MFP_Msk        /*<! UART9_RXD       PF2      MFP Mask */
#define UART9_RXD_PH11_Msk      SYS_GPH_MFP2_PH11MFP_Msk       /*<! UART9_RXD       PH11     MFP Mask */
#define UART9_RXD_PF8_Msk       SYS_GPF_MFP2_PF8MFP_Msk        /*<! UART9_RXD       PF8      MFP Mask */
#define UART9_RXD_PE4_Msk       SYS_GPE_MFP1_PE4MFP_Msk        /*<! UART9_RXD       PE4      MFP Mask */
#define UART9_RXD_PH13_Msk      SYS_GPH_MFP3_PH13MFP_Msk       /*<! UART9_RXD       PH13     MFP Mask */
#define UART9_TXD_PE5_Msk       SYS_GPE_MFP1_PE5MFP_Msk        /*<! UART9_TXD       PE5      MFP Mask */
#define UART9_TXD_PF9_Msk       SYS_GPF_MFP2_PF9MFP_Msk        /*<! UART9_TXD       PF9      MFP Mask */
#define UART9_TXD_PF3_Msk       SYS_GPF_MFP0_PF3MFP_Msk        /*<! UART9_TXD       PF3      MFP Mask */
#define UART9_TXD_PH12_Msk      SYS_GPH_MFP3_PH12MFP_Msk       /*<! UART9_TXD       PH12     MFP Mask */
#define UART9_TXD_PH10_Msk      SYS_GPH_MFP2_PH10MFP_Msk       /*<! UART9_TXD       PH10     MFP Mask */
#define UART9_nCTS_PJ6_Msk      SYS_GPJ_MFP1_PJ6MFP_Msk        /*<! UART9_nCTS      PJ6      MFP Mask */
#define UART9_nCTS_PF11_Msk     SYS_GPF_MFP2_PF11MFP_Msk       /*<! UART9_nCTS      PF11     MFP Mask */
#define UART9_nCTS_PH6_Msk      SYS_GPH_MFP1_PH6MFP_Msk        /*<! UART9_nCTS      PH6      MFP Mask */
#define UART9_nCTS_PH8_Msk      SYS_GPH_MFP2_PH8MFP_Msk        /*<! UART9_nCTS      PH8      MFP Mask */
#define UART9_nCTS_PE7_Msk      SYS_GPE_MFP1_PE7MFP_Msk        /*<! UART9_nCTS      PE7      MFP Mask */
#define UART9_nRTS_PH7_Msk      SYS_GPH_MFP1_PH7MFP_Msk        /*<! UART9_nRTS      PH7      MFP Mask */
#define UART9_nRTS_PF10_Msk     SYS_GPF_MFP2_PF10MFP_Msk       /*<! UART9_nRTS      PF10     MFP Mask */
#define UART9_nRTS_PH9_Msk      SYS_GPH_MFP2_PH9MFP_Msk        /*<! UART9_nRTS      PH9      MFP Mask */
#define UART9_nRTS_PE6_Msk      SYS_GPE_MFP1_PE6MFP_Msk        /*<! UART9_nRTS      PE6      MFP Mask */
#define UART9_nRTS_PJ7_Msk      SYS_GPJ_MFP1_PJ7MFP_Msk        /*<! UART9_nRTS      PJ7      MFP Mask */
#define USB_D_P_PA14_Msk         SYS_GPA_MFP3_PA14MFP_Msk       /*<! USB_D+          PA14     MFP Mask */
#define USB_D_N_PA13_Msk         SYS_GPA_MFP3_PA13MFP_Msk       /*<! USB_D-          PA13     MFP Mask */
#define USB_OTG_ID_PA15_Msk     SYS_GPA_MFP3_PA15MFP_Msk       /*<! USB_OTG_ID      PA15     MFP Mask */
#define USB_VBUS_PA12_Msk       SYS_GPA_MFP3_PA12MFP_Msk       /*<! USB_VBUS        PA12     MFP Mask */
#define USB_VBUS_EN_PB6_Msk     SYS_GPB_MFP1_PB6MFP_Msk        /*<! USB_VBUS_EN     PB6      MFP Mask */
#define USB_VBUS_EN_PI7_Msk     SYS_GPI_MFP1_PI7MFP_Msk        /*<! USB_VBUS_EN     PI7      MFP Mask */
#define USB_VBUS_EN_PB15_Msk    SYS_GPB_MFP3_PB15MFP_Msk       /*<! USB_VBUS_EN     PB15     MFP Mask */
#define USB_VBUS_ST_PB14_Msk    SYS_GPB_MFP3_PB14MFP_Msk       /*<! USB_VBUS_ST     PB14     MFP Mask */
#define USB_VBUS_ST_PC14_Msk    SYS_GPC_MFP3_PC14MFP_Msk       /*<! USB_VBUS_ST     PC14     MFP Mask */
#define USB_VBUS_ST_PD4_Msk     SYS_GPD_MFP1_PD4MFP_Msk        /*<! USB_VBUS_ST     PD4      MFP Mask */
#define USB_VBUS_ST_PB7_Msk     SYS_GPB_MFP1_PB7MFP_Msk        /*<! USB_VBUS_ST     PB7      MFP Mask */
#define USB_VBUS_ST_PI6_Msk     SYS_GPI_MFP1_PI6MFP_Msk        /*<! USB_VBUS_ST     PI6      MFP Mask */
#define USCI0_CLK_PD0_Msk       SYS_GPD_MFP0_PD0MFP_Msk        /*<! USCI0_CLK       PD0      MFP Mask */
#define USCI0_CLK_PE2_Msk       SYS_GPE_MFP0_PE2MFP_Msk        /*<! USCI0_CLK       PE2      MFP Mask */
#define USCI0_CLK_PA11_Msk      SYS_GPA_MFP2_PA11MFP_Msk       /*<! USCI0_CLK       PA11     MFP Mask */
#define USCI0_CLK_PB12_Msk      SYS_GPB_MFP3_PB12MFP_Msk       /*<! USCI0_CLK       PB12     MFP Mask */
#define USCI0_CTL0_PC14_Msk     SYS_GPC_MFP3_PC14MFP_Msk       /*<! USCI0_CTL0      PC14     MFP Mask */
#define USCI0_CTL0_PE6_Msk      SYS_GPE_MFP1_PE6MFP_Msk        /*<! USCI0_CTL0      PE6      MFP Mask */
#define USCI0_CTL0_PB0_Msk      SYS_GPB_MFP0_PB0MFP_Msk        /*<! USCI0_CTL0      PB0      MFP Mask */
#define USCI0_CTL0_PD4_Msk      SYS_GPD_MFP1_PD4MFP_Msk        /*<! USCI0_CTL0      PD4      MFP Mask */
#define USCI0_CTL0_PC13_Msk     SYS_GPC_MFP3_PC13MFP_Msk       /*<! USCI0_CTL0      PC13     MFP Mask */
#define USCI0_CTL1_PA8_Msk      SYS_GPA_MFP2_PA8MFP_Msk        /*<! USCI0_CTL1      PA8      MFP Mask */
#define USCI0_CTL1_PD3_Msk      SYS_GPD_MFP0_PD3MFP_Msk        /*<! USCI0_CTL1      PD3      MFP Mask */
#define USCI0_CTL1_PE5_Msk      SYS_GPE_MFP1_PE5MFP_Msk        /*<! USCI0_CTL1      PE5      MFP Mask */
#define USCI0_CTL1_PB15_Msk     SYS_GPB_MFP3_PB15MFP_Msk       /*<! USCI0_CTL1      PB15     MFP Mask */
#define USCI0_DAT0_PA10_Msk     SYS_GPA_MFP2_PA10MFP_Msk       /*<! USCI0_DAT0      PA10     MFP Mask */
#define USCI0_DAT0_PB13_Msk     SYS_GPB_MFP3_PB13MFP_Msk       /*<! USCI0_DAT0      PB13     MFP Mask */
#define USCI0_DAT0_PE3_Msk      SYS_GPE_MFP0_PE3MFP_Msk        /*<! USCI0_DAT0      PE3      MFP Mask */
#define USCI0_DAT0_PD1_Msk      SYS_GPD_MFP0_PD1MFP_Msk        /*<! USCI0_DAT0      PD1      MFP Mask */
#define USCI0_DAT1_PD2_Msk      SYS_GPD_MFP0_PD2MFP_Msk        /*<! USCI0_DAT1      PD2      MFP Mask */
#define USCI0_DAT1_PE4_Msk      SYS_GPE_MFP1_PE4MFP_Msk        /*<! USCI0_DAT1      PE4      MFP Mask */
#define USCI0_DAT1_PA9_Msk      SYS_GPA_MFP2_PA9MFP_Msk        /*<! USCI0_DAT1      PA9      MFP Mask */
#define USCI0_DAT1_PB14_Msk     SYS_GPB_MFP3_PB14MFP_Msk       /*<! USCI0_DAT1      PB14     MFP Mask */
#define X32_IN_PF5_Msk          SYS_GPF_MFP1_PF5MFP_Msk        /*<! X32_IN          PF5      MFP Mask */
#define X32_OUT_PF4_Msk         SYS_GPF_MFP1_PF4MFP_Msk        /*<! X32_OUT         PF4      MFP Mask */
#define XT1_IN_PF3_Msk          SYS_GPF_MFP0_PF3MFP_Msk        /*<! XT1_IN          PF3      MFP Mask */
#define XT1_OUT_PF2_Msk         SYS_GPF_MFP0_PF2MFP_Msk        /*<! XT1_OUT         PF2      MFP Mask */


/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */

extern int32_t g_SYS_i32ErrCode;

/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function macro definitions.                                                                      */
/*---------------------------------------------------------------------------------------------------------*/

#define SET_ACMP0_N_PB3()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP0_N_PB3_Msk)) | ACMP0_N_PB3              /*!< Set PB3 function to ACMP0_N          */
#define SET_ACMP0_O_PB7()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP0_O_PB7_Msk)) | ACMP0_O_PB7              /*!< Set PB7 function to ACMP0_O          */
#define SET_ACMP0_O_PC1()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~ACMP0_O_PC1_Msk)) | ACMP0_O_PC1              /*!< Set PC1 function to ACMP0_O          */
#define SET_ACMP0_O_PC12()       SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~ACMP0_O_PC12_Msk)) | ACMP0_O_PC12            /*!< Set PC12 function to ACMP0_O         */
#define SET_ACMP0_O_PD6()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~ACMP0_O_PD6_Msk)) | ACMP0_O_PD6              /*!< Set PD6 function to ACMP0_O          */
#define SET_ACMP0_O_PF0()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ACMP0_O_PF0_Msk)) | ACMP0_O_PF0              /*!< Set PF0 function to ACMP0_O          */
#define SET_ACMP0_P0_PA11()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~ACMP0_P0_PA11_Msk)) | ACMP0_P0_PA11          /*!< Set PA11 function to ACMP0_P0        */
#define SET_ACMP0_P1_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP0_P1_PB2_Msk)) | ACMP0_P1_PB2            /*!< Set PB2 function to ACMP0_P1         */
#define SET_ACMP0_P2_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ACMP0_P2_PB12_Msk)) | ACMP0_P2_PB12          /*!< Set PB12 function to ACMP0_P2        */
#define SET_ACMP0_P3_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ACMP0_P3_PB13_Msk)) | ACMP0_P3_PB13          /*!< Set PB13 function to ACMP0_P3        */
#define SET_ACMP0_WLAT_PA7()     SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~ACMP0_WLAT_PA7_Msk)) | ACMP0_WLAT_PA7        /*!< Set PA7 function to ACMP0_WLAT       */
#define SET_ACMP1_N_PB5()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP1_N_PB5_Msk)) | ACMP1_N_PB5              /*!< Set PB5 function to ACMP1_N          */
#define SET_ACMP1_O_PC0()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~ACMP1_O_PC0_Msk)) | ACMP1_O_PC0              /*!< Set PC0 function to ACMP1_O          */
#define SET_ACMP1_O_PD5()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~ACMP1_O_PD5_Msk)) | ACMP1_O_PD5              /*!< Set PD5 function to ACMP1_O          */
#define SET_ACMP1_O_PB6()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP1_O_PB6_Msk)) | ACMP1_O_PB6              /*!< Set PB6 function to ACMP1_O          */
#define SET_ACMP1_O_PC11()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ACMP1_O_PC11_Msk)) | ACMP1_O_PC11            /*!< Set PC11 function to ACMP1_O         */
#define SET_ACMP1_O_PF1()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ACMP1_O_PF1_Msk)) | ACMP1_O_PF1              /*!< Set PF1 function to ACMP1_O          */
#define SET_ACMP1_P0_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~ACMP1_P0_PA10_Msk)) | ACMP1_P0_PA10          /*!< Set PA10 function to ACMP1_P0        */
#define SET_ACMP1_P1_PB4()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP1_P1_PB4_Msk)) | ACMP1_P1_PB4            /*!< Set PB4 function to ACMP1_P1         */
#define SET_ACMP1_P2_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ACMP1_P2_PB12_Msk)) | ACMP1_P2_PB12          /*!< Set PB12 function to ACMP1_P2        */
#define SET_ACMP1_P3_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ACMP1_P3_PB13_Msk)) | ACMP1_P3_PB13          /*!< Set PB13 function to ACMP1_P3        */
#define SET_ACMP1_WLAT_PA6()     SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~ACMP1_WLAT_PA6_Msk)) | ACMP1_WLAT_PA6        /*!< Set PA6 function to ACMP1_WLAT       */
#define SET_ACMP2_N_PB6()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP2_N_PB6_Msk)) | ACMP2_N_PB6              /*!< Set PB6 function to ACMP2_N          */
#define SET_ACMP2_O_PB1()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP2_O_PB1_Msk)) | ACMP2_O_PB1              /*!< Set PB1 function to ACMP2_O          */
#define SET_ACMP2_O_PE7()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~ACMP2_O_PE7_Msk)) | ACMP2_O_PE7              /*!< Set PE7 function to ACMP2_O          */
#define SET_ACMP2_O_PF3()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ACMP2_O_PF3_Msk)) | ACMP2_O_PF3              /*!< Set PF3 function to ACMP2_O          */
#define SET_ACMP2_P0_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~ACMP2_P0_PB7_Msk)) | ACMP2_P0_PB7            /*!< Set PB7 function to ACMP2_P0         */
#define SET_ACMP2_P1_PB8()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~ACMP2_P1_PB8_Msk)) | ACMP2_P1_PB8            /*!< Set PB8 function to ACMP2_P1         */
#define SET_ACMP2_P2_PB9()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~ACMP2_P2_PB9_Msk)) | ACMP2_P2_PB9            /*!< Set PB9 function to ACMP2_P2         */
#define SET_ACMP2_P3_PB10()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~ACMP2_P3_PB10_Msk)) | ACMP2_P3_PB10          /*!< Set PB10 function to ACMP2_P3        */
#define SET_ACMP2_WLAT_PC7()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~ACMP2_WLAT_PC7_Msk)) | ACMP2_WLAT_PC7        /*!< Set PC7 function to ACMP2_WLAT       */
#define SET_ACMP3_N_PB0()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP3_N_PB0_Msk)) | ACMP3_N_PB0              /*!< Set PB0 function to ACMP3_N          */
#define SET_ACMP3_O_PB0()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP3_O_PB0_Msk)) | ACMP3_O_PB0              /*!< Set PB0 function to ACMP3_O          */
#define SET_ACMP3_O_PF2()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ACMP3_O_PF2_Msk)) | ACMP3_O_PF2              /*!< Set PF2 function to ACMP3_O          */
#define SET_ACMP3_O_PE6()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~ACMP3_O_PE6_Msk)) | ACMP3_O_PE6              /*!< Set PE6 function to ACMP3_O          */
#define SET_ACMP3_P0_PB1()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~ACMP3_P0_PB1_Msk)) | ACMP3_P0_PB1            /*!< Set PB1 function to ACMP3_P0         */
#define SET_ACMP3_P1_PC9()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ACMP3_P1_PC9_Msk)) | ACMP3_P1_PC9            /*!< Set PC9 function to ACMP3_P1         */
#define SET_ACMP3_P2_PC10()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ACMP3_P2_PC10_Msk)) | ACMP3_P2_PC10          /*!< Set PC10 function to ACMP3_P2        */
#define SET_ACMP3_P3_PC11()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ACMP3_P3_PC11_Msk)) | ACMP3_P3_PC11          /*!< Set PC11 function to ACMP3_P3        */
#define SET_ACMP3_WLAT_PC6()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~ACMP3_WLAT_PC6_Msk)) | ACMP3_WLAT_PC6        /*!< Set PC6 function to ACMP3_WLAT       */
#define SET_BMC0_PB5()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BMC0_PB5_Msk)) | BMC0_PB5                    /*!< Set PB5 function to BMC0             */
#define SET_BMC1_PB4()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BMC1_PB4_Msk)) | BMC1_PB4                    /*!< Set PB4 function to BMC1             */
#define SET_BMC10_PF5()          SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~BMC10_PF5_Msk)) | BMC10_PF5                  /*!< Set PF5 function to BMC10            */
#define SET_BMC11_PF4()          SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~BMC11_PF4_Msk)) | BMC11_PF4                  /*!< Set PF4 function to BMC11            */
#define SET_BMC12_PA12()         SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BMC12_PA12_Msk)) | BMC12_PA12                /*!< Set PA12 function to BMC12           */
#define SET_BMC12_PF3()          SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BMC12_PF3_Msk)) | BMC12_PF3                  /*!< Set PF3 function to BMC12            */
#define SET_BMC13_PF2()          SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BMC13_PF2_Msk)) | BMC13_PF2                  /*!< Set PF2 function to BMC13            */
#define SET_BMC13_PA13()         SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BMC13_PA13_Msk)) | BMC13_PA13                /*!< Set PA13 function to BMC13           */
#define SET_BMC14_PA7()          SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BMC14_PA7_Msk)) | BMC14_PA7                  /*!< Set PA7 function to BMC14            */
#define SET_BMC14_PA14()         SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BMC14_PA14_Msk)) | BMC14_PA14                /*!< Set PA14 function to BMC14           */
#define SET_BMC15_PA6()          SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BMC15_PA6_Msk)) | BMC15_PA6                  /*!< Set PA6 function to BMC15            */
#define SET_BMC15_PA15()         SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BMC15_PA15_Msk)) | BMC15_PA15                /*!< Set PA15 function to BMC15           */
#define SET_BMC16_PA3()          SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BMC16_PA3_Msk)) | BMC16_PA3                  /*!< Set PA3 function to BMC16            */
#define SET_BMC16_PG9()          SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BMC16_PG9_Msk)) | BMC16_PG9                  /*!< Set PG9 function to BMC16            */
#define SET_BMC17_PA2()          SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BMC17_PA2_Msk)) | BMC17_PA2                  /*!< Set PA2 function to BMC17            */
#define SET_BMC17_PG10()         SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BMC17_PG10_Msk)) | BMC17_PG10                /*!< Set PG10 function to BMC17           */
#define SET_BMC18_PA1()          SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BMC18_PA1_Msk)) | BMC18_PA1                  /*!< Set PA1 function to BMC18            */
#define SET_BMC18_PG11()         SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BMC18_PG11_Msk)) | BMC18_PG11                /*!< Set PG11 function to BMC18           */
#define SET_BMC19_PA0()          SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BMC19_PA0_Msk)) | BMC19_PA0                  /*!< Set PA0 function to BMC19            */
#define SET_BMC19_PG12()         SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~BMC19_PG12_Msk)) | BMC19_PG12                /*!< Set PG12 function to BMC19           */
#define SET_BMC2_PB3()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~BMC2_PB3_Msk)) | BMC2_PB3                    /*!< Set PB3 function to BMC2             */
#define SET_BMC20_PB11()         SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BMC20_PB11_Msk)) | BMC20_PB11                /*!< Set PB11 function to BMC20           */
#define SET_BMC20_PC5()          SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BMC20_PC5_Msk)) | BMC20_PC5                  /*!< Set PC5 function to BMC20            */
#define SET_BMC21_PC4()          SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BMC21_PC4_Msk)) | BMC21_PC4                  /*!< Set PC4 function to BMC21            */
#define SET_BMC21_PB10()         SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BMC21_PB10_Msk)) | BMC21_PB10                /*!< Set PB10 function to BMC21           */
#define SET_BMC22_PB9()          SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BMC22_PB9_Msk)) | BMC22_PB9                  /*!< Set PB9 function to BMC22            */
#define SET_BMC22_PC3()          SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~BMC22_PC3_Msk)) | BMC22_PC3                  /*!< Set PC3 function to BMC22            */
#define SET_BMC23_PC2()          SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~BMC23_PC2_Msk)) | BMC23_PC2                  /*!< Set PC2 function to BMC23            */
#define SET_BMC23_PB8()          SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BMC23_PB8_Msk)) | BMC23_PB8                  /*!< Set PB8 function to BMC23            */
#define SET_BMC24_PC1()          SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~BMC24_PC1_Msk)) | BMC24_PC1                  /*!< Set PC1 function to BMC24            */
#define SET_BMC24_PC7()          SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BMC24_PC7_Msk)) | BMC24_PC7                  /*!< Set PC7 function to BMC24            */
#define SET_BMC25_PC6()          SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BMC25_PC6_Msk)) | BMC25_PC6                  /*!< Set PC6 function to BMC25            */
#define SET_BMC25_PC0()          SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~BMC25_PC0_Msk)) | BMC25_PC0                  /*!< Set PC0 function to BMC25            */
#define SET_BMC26_PC14()         SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~BMC26_PC14_Msk)) | BMC26_PC14                /*!< Set PC14 function to BMC26           */
#define SET_BMC27_PB15()         SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~BMC27_PB15_Msk)) | BMC27_PB15                /*!< Set PB15 function to BMC27           */
#define SET_BMC28_PB13()         SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~BMC28_PB13_Msk)) | BMC28_PB13                /*!< Set PB13 function to BMC28           */
#define SET_BMC29_PB12()         SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~BMC29_PB12_Msk)) | BMC29_PB12                /*!< Set PB12 function to BMC29           */
#define SET_BMC3_PB2()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~BMC3_PB2_Msk)) | BMC3_PB2                    /*!< Set PB2 function to BMC3             */
#define SET_BMC30_PB7()          SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BMC30_PB7_Msk)) | BMC30_PB7                  /*!< Set PB7 function to BMC30            */
#define SET_BMC31_PB6()          SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BMC31_PB6_Msk)) | BMC31_PB6                  /*!< Set PB6 function to BMC31            */
#define SET_BMC4_PB1()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~BMC4_PB1_Msk)) | BMC4_PB1                    /*!< Set PB1 function to BMC4             */
#define SET_BMC5_PB0()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~BMC5_PB0_Msk)) | BMC5_PB0                    /*!< Set PB0 function to BMC5             */
#define SET_BMC6_PA11()          SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BMC6_PA11_Msk)) | BMC6_PA11                  /*!< Set PA11 function to BMC6            */
#define SET_BMC7_PA10()          SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BMC7_PA10_Msk)) | BMC7_PA10                  /*!< Set PA10 function to BMC7            */
#define SET_BMC8_PA9()           SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BMC8_PA9_Msk)) | BMC8_PA9                    /*!< Set PA9 function to BMC8             */
#define SET_BMC9_PA8()           SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BMC9_PA8_Msk)) | BMC9_PA8                    /*!< Set PA8 function to BMC9             */
#define SET_BPWM0_CH0_PD13()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~BPWM0_CH0_PD13_Msk)) | BPWM0_CH0_PD13        /*!< Set PD13 function to BPWM0_CH0       */
#define SET_BPWM0_CH0_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~BPWM0_CH0_PE2_Msk)) | BPWM0_CH0_PE2          /*!< Set PE2 function to BPWM0_CH0        */
#define SET_BPWM0_CH0_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BPWM0_CH0_PA0_Msk)) | BPWM0_CH0_PA0          /*!< Set PA0 function to BPWM0_CH0        */
#define SET_BPWM0_CH0_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BPWM0_CH0_PA11_Msk)) | BPWM0_CH0_PA11        /*!< Set PA11 function to BPWM0_CH0       */
#define SET_BPWM0_CH0_PG14()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~BPWM0_CH0_PG14_Msk)) | BPWM0_CH0_PG14        /*!< Set PG14 function to BPWM0_CH0       */
#define SET_BPWM0_CH0_PJ13()     SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~BPWM0_CH0_PJ13_Msk)) | BPWM0_CH0_PJ13        /*!< Set PJ13 function to BPWM0_CH0       */
#define SET_BPWM0_CH1_PE3()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~BPWM0_CH1_PE3_Msk)) | BPWM0_CH1_PE3          /*!< Set PE3 function to BPWM0_CH1        */
#define SET_BPWM0_CH1_PG13()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~BPWM0_CH1_PG13_Msk)) | BPWM0_CH1_PG13        /*!< Set PG13 function to BPWM0_CH1       */
#define SET_BPWM0_CH1_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BPWM0_CH1_PA1_Msk)) | BPWM0_CH1_PA1          /*!< Set PA1 function to BPWM0_CH1        */
#define SET_BPWM0_CH1_PJ12()     SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~BPWM0_CH1_PJ12_Msk)) | BPWM0_CH1_PJ12        /*!< Set PJ12 function to BPWM0_CH1       */
#define SET_BPWM0_CH1_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BPWM0_CH1_PA10_Msk)) | BPWM0_CH1_PA10        /*!< Set PA10 function to BPWM0_CH1       */
#define SET_BPWM0_CH2_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BPWM0_CH2_PA9_Msk)) | BPWM0_CH2_PA9          /*!< Set PA9 function to BPWM0_CH2        */
#define SET_BPWM0_CH2_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BPWM0_CH2_PA2_Msk)) | BPWM0_CH2_PA2          /*!< Set PA2 function to BPWM0_CH2        */
#define SET_BPWM0_CH2_PJ11()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~BPWM0_CH2_PJ11_Msk)) | BPWM0_CH2_PJ11        /*!< Set PJ11 function to BPWM0_CH2       */
#define SET_BPWM0_CH2_PE4()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~BPWM0_CH2_PE4_Msk)) | BPWM0_CH2_PE4          /*!< Set PE4 function to BPWM0_CH2        */
#define SET_BPWM0_CH2_PG12()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~BPWM0_CH2_PG12_Msk)) | BPWM0_CH2_PG12        /*!< Set PG12 function to BPWM0_CH2       */
#define SET_BPWM0_CH3_PE5()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~BPWM0_CH3_PE5_Msk)) | BPWM0_CH3_PE5          /*!< Set PE5 function to BPWM0_CH3        */
#define SET_BPWM0_CH3_PJ10()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~BPWM0_CH3_PJ10_Msk)) | BPWM0_CH3_PJ10        /*!< Set PJ10 function to BPWM0_CH3       */
#define SET_BPWM0_CH3_PG11()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BPWM0_CH3_PG11_Msk)) | BPWM0_CH3_PG11        /*!< Set PG11 function to BPWM0_CH3       */
#define SET_BPWM0_CH3_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~BPWM0_CH3_PA8_Msk)) | BPWM0_CH3_PA8          /*!< Set PA8 function to BPWM0_CH3        */
#define SET_BPWM0_CH3_PA3()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~BPWM0_CH3_PA3_Msk)) | BPWM0_CH3_PA3          /*!< Set PA3 function to BPWM0_CH3        */
#define SET_BPWM0_CH4_PF5()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~BPWM0_CH4_PF5_Msk)) | BPWM0_CH4_PF5          /*!< Set PF5 function to BPWM0_CH4        */
#define SET_BPWM0_CH4_PJ9()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~BPWM0_CH4_PJ9_Msk)) | BPWM0_CH4_PJ9          /*!< Set PJ9 function to BPWM0_CH4        */
#define SET_BPWM0_CH4_PG10()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BPWM0_CH4_PG10_Msk)) | BPWM0_CH4_PG10        /*!< Set PG10 function to BPWM0_CH4       */
#define SET_BPWM0_CH4_PC13()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~BPWM0_CH4_PC13_Msk)) | BPWM0_CH4_PC13        /*!< Set PC13 function to BPWM0_CH4       */
#define SET_BPWM0_CH4_PA4()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BPWM0_CH4_PA4_Msk)) | BPWM0_CH4_PA4          /*!< Set PA4 function to BPWM0_CH4        */
#define SET_BPWM0_CH4_PE6()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~BPWM0_CH4_PE6_Msk)) | BPWM0_CH4_PE6          /*!< Set PE6 function to BPWM0_CH4        */
#define SET_BPWM0_CH5_PJ8()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~BPWM0_CH5_PJ8_Msk)) | BPWM0_CH5_PJ8          /*!< Set PJ8 function to BPWM0_CH5        */
#define SET_BPWM0_CH5_PD12()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~BPWM0_CH5_PD12_Msk)) | BPWM0_CH5_PD12        /*!< Set PD12 function to BPWM0_CH5       */
#define SET_BPWM0_CH5_PA5()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BPWM0_CH5_PA5_Msk)) | BPWM0_CH5_PA5          /*!< Set PA5 function to BPWM0_CH5        */
#define SET_BPWM0_CH5_PF4()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~BPWM0_CH5_PF4_Msk)) | BPWM0_CH5_PF4          /*!< Set PF4 function to BPWM0_CH5        */
#define SET_BPWM0_CH5_PE7()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~BPWM0_CH5_PE7_Msk)) | BPWM0_CH5_PE7          /*!< Set PE7 function to BPWM0_CH5        */
#define SET_BPWM0_CH5_PG9()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~BPWM0_CH5_PG9_Msk)) | BPWM0_CH5_PG9          /*!< Set PG9 function to BPWM0_CH5        */
#define SET_BPWM1_CH0_PF3()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BPWM1_CH0_PF3_Msk)) | BPWM1_CH0_PF3          /*!< Set PF3 function to BPWM1_CH0        */
#define SET_BPWM1_CH0_PB11()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BPWM1_CH0_PB11_Msk)) | BPWM1_CH0_PB11        /*!< Set PB11 function to BPWM1_CH0       */
#define SET_BPWM1_CH0_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BPWM1_CH0_PC7_Msk)) | BPWM1_CH0_PC7          /*!< Set PC7 function to BPWM1_CH0        */
#define SET_BPWM1_CH0_PF0()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BPWM1_CH0_PF0_Msk)) | BPWM1_CH0_PF0          /*!< Set PF0 function to BPWM1_CH0        */
#define SET_BPWM1_CH1_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BPWM1_CH1_PF1_Msk)) | BPWM1_CH1_PF1          /*!< Set PF1 function to BPWM1_CH1        */
#define SET_BPWM1_CH1_PB10()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BPWM1_CH1_PB10_Msk)) | BPWM1_CH1_PB10        /*!< Set PB10 function to BPWM1_CH1       */
#define SET_BPWM1_CH1_PF2()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~BPWM1_CH1_PF2_Msk)) | BPWM1_CH1_PF2          /*!< Set PF2 function to BPWM1_CH1        */
#define SET_BPWM1_CH1_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~BPWM1_CH1_PC6_Msk)) | BPWM1_CH1_PC6          /*!< Set PC6 function to BPWM1_CH1        */
#define SET_BPWM1_CH2_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BPWM1_CH2_PB9_Msk)) | BPWM1_CH2_PB9          /*!< Set PB9 function to BPWM1_CH2        */
#define SET_BPWM1_CH2_PA7()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BPWM1_CH2_PA7_Msk)) | BPWM1_CH2_PA7          /*!< Set PA7 function to BPWM1_CH2        */
#define SET_BPWM1_CH2_PA12()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BPWM1_CH2_PA12_Msk)) | BPWM1_CH2_PA12        /*!< Set PA12 function to BPWM1_CH2       */
#define SET_BPWM1_CH3_PA6()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~BPWM1_CH3_PA6_Msk)) | BPWM1_CH3_PA6          /*!< Set PA6 function to BPWM1_CH3        */
#define SET_BPWM1_CH3_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~BPWM1_CH3_PB8_Msk)) | BPWM1_CH3_PB8          /*!< Set PB8 function to BPWM1_CH3        */
#define SET_BPWM1_CH3_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BPWM1_CH3_PA13_Msk)) | BPWM1_CH3_PA13        /*!< Set PA13 function to BPWM1_CH3       */
#define SET_BPWM1_CH4_PB7()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BPWM1_CH4_PB7_Msk)) | BPWM1_CH4_PB7          /*!< Set PB7 function to BPWM1_CH4        */
#define SET_BPWM1_CH4_PC8()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~BPWM1_CH4_PC8_Msk)) | BPWM1_CH4_PC8          /*!< Set PC8 function to BPWM1_CH4        */
#define SET_BPWM1_CH4_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BPWM1_CH4_PA14_Msk)) | BPWM1_CH4_PA14        /*!< Set PA14 function to BPWM1_CH4       */
#define SET_BPWM1_CH5_PB6()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~BPWM1_CH5_PB6_Msk)) | BPWM1_CH5_PB6          /*!< Set PB6 function to BPWM1_CH5        */
#define SET_BPWM1_CH5_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~BPWM1_CH5_PE13_Msk)) | BPWM1_CH5_PE13        /*!< Set PE13 function to BPWM1_CH5       */
#define SET_BPWM1_CH5_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~BPWM1_CH5_PA15_Msk)) | BPWM1_CH5_PA15        /*!< Set PA15 function to BPWM1_CH5       */
#define SET_CAN0_RXD_PI13()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~CAN0_RXD_PI13_Msk)) | CAN0_RXD_PI13          /*!< Set PI13 function to CAN0_RXD        */
#define SET_CAN0_RXD_PJ3()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CAN0_RXD_PJ3_Msk)) | CAN0_RXD_PJ3            /*!< Set PJ3 function to CAN0_RXD         */
#define SET_CAN0_RXD_PA4()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~CAN0_RXD_PA4_Msk)) | CAN0_RXD_PA4            /*!< Set PA4 function to CAN0_RXD         */
#define SET_CAN0_RXD_PE15()      SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~CAN0_RXD_PE15_Msk)) | CAN0_RXD_PE15          /*!< Set PE15 function to CAN0_RXD        */
#define SET_CAN0_RXD_PA13()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~CAN0_RXD_PA13_Msk)) | CAN0_RXD_PA13          /*!< Set PA13 function to CAN0_RXD        */
#define SET_CAN0_RXD_PJ11()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~CAN0_RXD_PJ11_Msk)) | CAN0_RXD_PJ11          /*!< Set PJ11 function to CAN0_RXD        */
#define SET_CAN0_RXD_PC4()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CAN0_RXD_PC4_Msk)) | CAN0_RXD_PC4            /*!< Set PC4 function to CAN0_RXD         */
#define SET_CAN0_RXD_PB10()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CAN0_RXD_PB10_Msk)) | CAN0_RXD_PB10          /*!< Set PB10 function to CAN0_RXD        */
#define SET_CAN0_RXD_PD10()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~CAN0_RXD_PD10_Msk)) | CAN0_RXD_PD10          /*!< Set PD10 function to CAN0_RXD        */
#define SET_CAN0_TXD_PC5()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CAN0_TXD_PC5_Msk)) | CAN0_TXD_PC5            /*!< Set PC5 function to CAN0_TXD         */
#define SET_CAN0_TXD_PB11()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CAN0_TXD_PB11_Msk)) | CAN0_TXD_PB11          /*!< Set PB11 function to CAN0_TXD        */
#define SET_CAN0_TXD_PA5()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~CAN0_TXD_PA5_Msk)) | CAN0_TXD_PA5            /*!< Set PA5 function to CAN0_TXD         */
#define SET_CAN0_TXD_PJ10()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~CAN0_TXD_PJ10_Msk)) | CAN0_TXD_PJ10          /*!< Set PJ10 function to CAN0_TXD        */
#define SET_CAN0_TXD_PD11()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~CAN0_TXD_PD11_Msk)) | CAN0_TXD_PD11          /*!< Set PD11 function to CAN0_TXD        */
#define SET_CAN0_TXD_PA12()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~CAN0_TXD_PA12_Msk)) | CAN0_TXD_PA12          /*!< Set PA12 function to CAN0_TXD        */
#define SET_CAN0_TXD_PI12()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~CAN0_TXD_PI12_Msk)) | CAN0_TXD_PI12          /*!< Set PI12 function to CAN0_TXD        */
#define SET_CAN0_TXD_PE14()      SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~CAN0_TXD_PE14_Msk)) | CAN0_TXD_PE14          /*!< Set PE14 function to CAN0_TXD        */
#define SET_CAN0_TXD_PJ2()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CAN0_TXD_PJ2_Msk)) | CAN0_TXD_PJ2            /*!< Set PJ2 function to CAN0_TXD         */
#define SET_CAN1_RXD_PJ5()       SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CAN1_RXD_PJ5_Msk)) | CAN1_RXD_PJ5            /*!< Set PJ5 function to CAN1_RXD         */
#define SET_CAN1_RXD_PC9()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~CAN1_RXD_PC9_Msk)) | CAN1_RXD_PC9            /*!< Set PC9 function to CAN1_RXD         */
#define SET_CAN1_RXD_PD12()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~CAN1_RXD_PD12_Msk)) | CAN1_RXD_PD12          /*!< Set PD12 function to CAN1_RXD        */
#define SET_CAN1_RXD_PF8()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CAN1_RXD_PF8_Msk)) | CAN1_RXD_PF8            /*!< Set PF8 function to CAN1_RXD         */
#define SET_CAN1_RXD_PG1()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~CAN1_RXD_PG1_Msk)) | CAN1_RXD_PG1            /*!< Set PG1 function to CAN1_RXD         */
#define SET_CAN1_RXD_PB6()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~CAN1_RXD_PB6_Msk)) | CAN1_RXD_PB6            /*!< Set PB6 function to CAN1_RXD         */
#define SET_CAN1_RXD_PI15()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~CAN1_RXD_PI15_Msk)) | CAN1_RXD_PI15          /*!< Set PI15 function to CAN1_RXD        */
#define SET_CAN1_RXD_PC2()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CAN1_RXD_PC2_Msk)) | CAN1_RXD_PC2            /*!< Set PC2 function to CAN1_RXD         */
#define SET_CAN1_RXD_PJ13()      SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~CAN1_RXD_PJ13_Msk)) | CAN1_RXD_PJ13          /*!< Set PJ13 function to CAN1_RXD        */
#define SET_CAN1_RXD_PE6()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~CAN1_RXD_PE6_Msk)) | CAN1_RXD_PE6            /*!< Set PE6 function to CAN1_RXD         */
#define SET_CAN1_TXD_PG0()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~CAN1_TXD_PG0_Msk)) | CAN1_TXD_PG0            /*!< Set PG0 function to CAN1_TXD         */
#define SET_CAN1_TXD_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~CAN1_TXD_PB7_Msk)) | CAN1_TXD_PB7            /*!< Set PB7 function to CAN1_TXD         */
#define SET_CAN1_TXD_PC3()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CAN1_TXD_PC3_Msk)) | CAN1_TXD_PC3            /*!< Set PC3 function to CAN1_TXD         */
#define SET_CAN1_TXD_PI14()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~CAN1_TXD_PI14_Msk)) | CAN1_TXD_PI14          /*!< Set PI14 function to CAN1_TXD        */
#define SET_CAN1_TXD_PC10()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~CAN1_TXD_PC10_Msk)) | CAN1_TXD_PC10          /*!< Set PC10 function to CAN1_TXD        */
#define SET_CAN1_TXD_PE7()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~CAN1_TXD_PE7_Msk)) | CAN1_TXD_PE7            /*!< Set PE7 function to CAN1_TXD         */
#define SET_CAN1_TXD_PJ12()      SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~CAN1_TXD_PJ12_Msk)) | CAN1_TXD_PJ12          /*!< Set PJ12 function to CAN1_TXD        */
#define SET_CAN1_TXD_PC13()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~CAN1_TXD_PC13_Msk)) | CAN1_TXD_PC13          /*!< Set PC13 function to CAN1_TXD        */
#define SET_CAN1_TXD_PJ4()       SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CAN1_TXD_PJ4_Msk)) | CAN1_TXD_PJ4            /*!< Set PJ4 function to CAN1_TXD         */
#define SET_CAN1_TXD_PF9()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CAN1_TXD_PF9_Msk)) | CAN1_TXD_PF9            /*!< Set PF9 function to CAN1_TXD         */
#define SET_CAN2_RXD_PF1()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~CAN2_RXD_PF1_Msk)) | CAN2_RXD_PF1            /*!< Set PF1 function to CAN2_RXD         */
#define SET_CAN2_RXD_PJ1()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CAN2_RXD_PJ1_Msk)) | CAN2_RXD_PJ1            /*!< Set PJ1 function to CAN2_RXD         */
#define SET_CAN2_RXD_PF6()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~CAN2_RXD_PF6_Msk)) | CAN2_RXD_PF6            /*!< Set PF6 function to CAN2_RXD         */
#define SET_CAN2_RXD_PI9()       SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~CAN2_RXD_PI9_Msk)) | CAN2_RXD_PI9            /*!< Set PI9 function to CAN2_RXD         */
#define SET_CAN2_RXD_PD8()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~CAN2_RXD_PD8_Msk)) | CAN2_RXD_PD8            /*!< Set PD8 function to CAN2_RXD         */
#define SET_CAN2_RXD_PB8()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CAN2_RXD_PB8_Msk)) | CAN2_RXD_PB8            /*!< Set PB8 function to CAN2_RXD         */
#define SET_CAN2_RXD_PJ7()       SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CAN2_RXD_PJ7_Msk)) | CAN2_RXD_PJ7            /*!< Set PJ7 function to CAN2_RXD         */
#define SET_CAN2_RXD_PC0()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CAN2_RXD_PC0_Msk)) | CAN2_RXD_PC0            /*!< Set PC0 function to CAN2_RXD         */
#define SET_CAN2_RXD_PJ9()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~CAN2_RXD_PJ9_Msk)) | CAN2_RXD_PJ9            /*!< Set PJ9 function to CAN2_RXD         */
#define SET_CAN2_TXD_PB9()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CAN2_TXD_PB9_Msk)) | CAN2_TXD_PB9            /*!< Set PB9 function to CAN2_TXD         */
#define SET_CAN2_TXD_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CAN2_TXD_PC1_Msk)) | CAN2_TXD_PC1            /*!< Set PC1 function to CAN2_TXD         */
#define SET_CAN2_TXD_PD9()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~CAN2_TXD_PD9_Msk)) | CAN2_TXD_PD9            /*!< Set PD9 function to CAN2_TXD         */
#define SET_CAN2_TXD_PF0()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~CAN2_TXD_PF0_Msk)) | CAN2_TXD_PF0            /*!< Set PF0 function to CAN2_TXD         */
#define SET_CAN2_TXD_PJ6()       SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CAN2_TXD_PJ6_Msk)) | CAN2_TXD_PJ6            /*!< Set PJ6 function to CAN2_TXD         */
#define SET_CAN2_TXD_PF7()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~CAN2_TXD_PF7_Msk)) | CAN2_TXD_PF7            /*!< Set PF7 function to CAN2_TXD         */
#define SET_CAN2_TXD_PJ8()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~CAN2_TXD_PJ8_Msk)) | CAN2_TXD_PJ8            /*!< Set PJ8 function to CAN2_TXD         */
#define SET_CAN2_TXD_PJ0()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CAN2_TXD_PJ0_Msk)) | CAN2_TXD_PJ0            /*!< Set PJ0 function to CAN2_TXD         */
#define SET_CAN2_TXD_PI8()       SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~CAN2_TXD_PI8_Msk)) | CAN2_TXD_PI8            /*!< Set PI8 function to CAN2_TXD         */
#define SET_CAN3_RXD_PC6()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CAN3_RXD_PC6_Msk)) | CAN3_RXD_PC6            /*!< Set PC6 function to CAN3_RXD         */
#define SET_CAN3_RXD_PH13()      SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CAN3_RXD_PH13_Msk)) | CAN3_RXD_PH13          /*!< Set PH13 function to CAN3_RXD        */
#define SET_CAN3_RXD_PI7()       SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~CAN3_RXD_PI7_Msk)) | CAN3_RXD_PI7            /*!< Set PI7 function to CAN3_RXD         */
#define SET_CAN3_RXD_PF10()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CAN3_RXD_PF10_Msk)) | CAN3_RXD_PF10          /*!< Set PF10 function to CAN3_RXD        */
#define SET_CAN3_RXD_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CAN3_RXD_PB12_Msk)) | CAN3_RXD_PB12          /*!< Set PB12 function to CAN3_RXD        */
#define SET_CAN3_RXD_PI11()      SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~CAN3_RXD_PI11_Msk)) | CAN3_RXD_PI11          /*!< Set PI11 function to CAN3_RXD        */
#define SET_CAN3_TXD_PI6()       SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~CAN3_TXD_PI6_Msk)) | CAN3_TXD_PI6            /*!< Set PI6 function to CAN3_TXD         */
#define SET_CAN3_TXD_PC7()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CAN3_TXD_PC7_Msk)) | CAN3_TXD_PC7            /*!< Set PC7 function to CAN3_TXD         */
#define SET_CAN3_TXD_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CAN3_TXD_PB13_Msk)) | CAN3_TXD_PB13          /*!< Set PB13 function to CAN3_TXD        */
#define SET_CAN3_TXD_PH12()      SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CAN3_TXD_PH12_Msk)) | CAN3_TXD_PH12          /*!< Set PH12 function to CAN3_TXD        */
#define SET_CAN3_TXD_PI10()      SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~CAN3_TXD_PI10_Msk)) | CAN3_TXD_PI10          /*!< Set PI10 function to CAN3_TXD        */
#define SET_CAN3_TXD_PF11()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CAN3_TXD_PF11_Msk)) | CAN3_TXD_PF11          /*!< Set PF11 function to CAN3_TXD        */
#define SET_CCAP_DATA0_PB14()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CCAP_DATA0_PB14_Msk)) | CCAP_DATA0_PB14      /*!< Set PB14 function to CCAP_DATA0      */
#define SET_CCAP_DATA0_PC0()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CCAP_DATA0_PC0_Msk)) | CCAP_DATA0_PC0        /*!< Set PC0 function to CCAP_DATA0       */
#define SET_CCAP_DATA0_PJ7()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CCAP_DATA0_PJ7_Msk)) | CCAP_DATA0_PJ7        /*!< Set PJ7 function to CCAP_DATA0       */
#define SET_CCAP_DATA0_PF7()     SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~CCAP_DATA0_PF7_Msk)) | CCAP_DATA0_PF7        /*!< Set PF7 function to CCAP_DATA0       */
#define SET_CCAP_DATA1_PJ6()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CCAP_DATA1_PJ6_Msk)) | CCAP_DATA1_PJ6        /*!< Set PJ6 function to CCAP_DATA1       */
#define SET_CCAP_DATA1_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CCAP_DATA1_PB15_Msk)) | CCAP_DATA1_PB15      /*!< Set PB15 function to CCAP_DATA1      */
#define SET_CCAP_DATA1_PC1()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CCAP_DATA1_PC1_Msk)) | CCAP_DATA1_PC1        /*!< Set PC1 function to CCAP_DATA1       */
#define SET_CCAP_DATA1_PF8()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CCAP_DATA1_PF8_Msk)) | CCAP_DATA1_PF8        /*!< Set PF8 function to CCAP_DATA1       */
#define SET_CCAP_DATA2_PJ5()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CCAP_DATA2_PJ5_Msk)) | CCAP_DATA2_PJ5        /*!< Set PJ5 function to CCAP_DATA2       */
#define SET_CCAP_DATA2_PC2()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CCAP_DATA2_PC2_Msk)) | CCAP_DATA2_PC2        /*!< Set PC2 function to CCAP_DATA2       */
#define SET_CCAP_DATA2_PF9()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CCAP_DATA2_PF9_Msk)) | CCAP_DATA2_PF9        /*!< Set PF9 function to CCAP_DATA2       */
#define SET_CCAP_DATA3_PF10()    SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CCAP_DATA3_PF10_Msk)) | CCAP_DATA3_PF10      /*!< Set PF10 function to CCAP_DATA3      */
#define SET_CCAP_DATA3_PJ4()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~CCAP_DATA3_PJ4_Msk)) | CCAP_DATA3_PJ4        /*!< Set PJ4 function to CCAP_DATA3       */
#define SET_CCAP_DATA3_PC3()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~CCAP_DATA3_PC3_Msk)) | CCAP_DATA3_PC3        /*!< Set PC3 function to CCAP_DATA3       */
#define SET_CCAP_DATA4_PC4()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CCAP_DATA4_PC4_Msk)) | CCAP_DATA4_PC4        /*!< Set PC4 function to CCAP_DATA4       */
#define SET_CCAP_DATA4_PF11()    SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~CCAP_DATA4_PF11_Msk)) | CCAP_DATA4_PF11      /*!< Set PF11 function to CCAP_DATA4      */
#define SET_CCAP_DATA4_PJ3()     SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CCAP_DATA4_PJ3_Msk)) | CCAP_DATA4_PJ3        /*!< Set PJ3 function to CCAP_DATA4       */
#define SET_CCAP_DATA5_PJ2()     SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~CCAP_DATA5_PJ2_Msk)) | CCAP_DATA5_PJ2        /*!< Set PJ2 function to CCAP_DATA5       */
#define SET_CCAP_DATA5_PC5()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~CCAP_DATA5_PC5_Msk)) | CCAP_DATA5_PC5        /*!< Set PC5 function to CCAP_DATA5       */
#define SET_CCAP_DATA5_PG4()     SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~CCAP_DATA5_PG4_Msk)) | CCAP_DATA5_PG4        /*!< Set PG4 function to CCAP_DATA5       */
#define SET_CCAP_DATA6_PG3()     SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~CCAP_DATA6_PG3_Msk)) | CCAP_DATA6_PG3        /*!< Set PG3 function to CCAP_DATA6       */
#define SET_CCAP_DATA6_PA0()     SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~CCAP_DATA6_PA0_Msk)) | CCAP_DATA6_PA0        /*!< Set PA0 function to CCAP_DATA6       */
#define SET_CCAP_DATA7_PA1()     SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~CCAP_DATA7_PA1_Msk)) | CCAP_DATA7_PA1        /*!< Set PA1 function to CCAP_DATA7       */
#define SET_CCAP_DATA7_PG2()     SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~CCAP_DATA7_PG2_Msk)) | CCAP_DATA7_PG2        /*!< Set PG2 function to CCAP_DATA7       */
#define SET_CCAP_HSYNC_PD7()     SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~CCAP_HSYNC_PD7_Msk)) | CCAP_HSYNC_PD7        /*!< Set PD7 function to CCAP_HSYNC       */
#define SET_CCAP_HSYNC_PG13()    SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~CCAP_HSYNC_PG13_Msk)) | CCAP_HSYNC_PG13      /*!< Set PG13 function to CCAP_HSYNC      */
#define SET_CCAP_HSYNC_PB9()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CCAP_HSYNC_PB9_Msk)) | CCAP_HSYNC_PB9        /*!< Set PB9 function to CCAP_HSYNC       */
#define SET_CCAP_PIXCLK_PH12()   SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CCAP_PIXCLK_PH12_Msk)) | CCAP_PIXCLK_PH12    /*!< Set PH12 function to CCAP_PIXCLK     */
#define SET_CCAP_PIXCLK_PG9()    SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~CCAP_PIXCLK_PG9_Msk)) | CCAP_PIXCLK_PG9      /*!< Set PG9 function to CCAP_PIXCLK      */
#define SET_CCAP_PIXCLK_PB13()   SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CCAP_PIXCLK_PB13_Msk)) | CCAP_PIXCLK_PB13    /*!< Set PB13 function to CCAP_PIXCLK     */
#define SET_CCAP_SCLK_PG10()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~CCAP_SCLK_PG10_Msk)) | CCAP_SCLK_PG10        /*!< Set PG10 function to CCAP_SCLK       */
#define SET_CCAP_SCLK_PH13()     SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CCAP_SCLK_PH13_Msk)) | CCAP_SCLK_PH13        /*!< Set PH13 function to CCAP_SCLK       */
#define SET_CCAP_SCLK_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CCAP_SCLK_PB12_Msk)) | CCAP_SCLK_PB12        /*!< Set PB12 function to CCAP_SCLK       */
#define SET_CCAP_SFIELD_PG11()   SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~CCAP_SFIELD_PG11_Msk)) | CCAP_SFIELD_PG11    /*!< Set PG11 function to CCAP_SFIELD     */
#define SET_CCAP_SFIELD_PB11()   SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CCAP_SFIELD_PB11_Msk)) | CCAP_SFIELD_PB11    /*!< Set PB11 function to CCAP_SFIELD     */
#define SET_CCAP_SFIELD_PH14()   SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CCAP_SFIELD_PH14_Msk)) | CCAP_SFIELD_PH14    /*!< Set PH14 function to CCAP_SFIELD     */
#define SET_CCAP_VSYNC_PG12()    SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~CCAP_VSYNC_PG12_Msk)) | CCAP_VSYNC_PG12      /*!< Set PG12 function to CCAP_VSYNC      */
#define SET_CCAP_VSYNC_PB10()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~CCAP_VSYNC_PB10_Msk)) | CCAP_VSYNC_PB10      /*!< Set PB10 function to CCAP_VSYNC      */
#define SET_CCAP_VSYNC_PH15()    SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~CCAP_VSYNC_PH15_Msk)) | CCAP_VSYNC_PH15      /*!< Set PH15 function to CCAP_VSYNC      */
#define SET_CLKO_PC13()          SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~CLKO_PC13_Msk)) | CLKO_PC13                  /*!< Set PC13 function to CLKO            */
#define SET_CLKO_PD13()          SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~CLKO_PD13_Msk)) | CLKO_PD13                  /*!< Set PD13 function to CLKO            */
#define SET_CLKO_PG15()          SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~CLKO_PG15_Msk)) | CLKO_PG15                  /*!< Set PG15 function to CLKO            */
#define SET_CLKO_PB14()          SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~CLKO_PB14_Msk)) | CLKO_PB14                  /*!< Set PB14 function to CLKO            */
#define SET_CLKO_PD12()          SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~CLKO_PD12_Msk)) | CLKO_PD12                  /*!< Set PD12 function to CLKO            */
#define SET_DAC0_OUT_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~DAC0_OUT_PB12_Msk)) | DAC0_OUT_PB12          /*!< Set PB12 function to DAC0_OUT        */
#define SET_DAC0_ST_PA0()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~DAC0_ST_PA0_Msk)) | DAC0_ST_PA0              /*!< Set PA0 function to DAC0_ST          */
#define SET_DAC0_ST_PA10()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~DAC0_ST_PA10_Msk)) | DAC0_ST_PA10            /*!< Set PA10 function to DAC0_ST         */
#define SET_DAC1_OUT_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~DAC1_OUT_PB13_Msk)) | DAC1_OUT_PB13          /*!< Set PB13 function to DAC1_OUT        */
#define SET_DAC1_ST_PA11()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~DAC1_ST_PA11_Msk)) | DAC1_ST_PA11            /*!< Set PA11 function to DAC1_ST         */
#define SET_DAC1_ST_PA1()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~DAC1_ST_PA1_Msk)) | DAC1_ST_PA1              /*!< Set PA1 function to DAC1_ST          */
#define SET_EADC0_CH0_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC0_CH0_PB0_Msk)) | EADC0_CH0_PB0          /*!< Set PB0 function to EADC0_CH0        */
#define SET_EADC0_CH1_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC0_CH1_PB1_Msk)) | EADC0_CH1_PB1          /*!< Set PB1 function to EADC0_CH1        */
#define SET_EADC0_CH10_PB10()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EADC0_CH10_PB10_Msk)) | EADC0_CH10_PB10      /*!< Set PB10 function to EADC0_CH10      */
#define SET_EADC0_CH11_PB11()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EADC0_CH11_PB11_Msk)) | EADC0_CH11_PB11      /*!< Set PB11 function to EADC0_CH11      */
#define SET_EADC0_CH12_PB12()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC0_CH12_PB12_Msk)) | EADC0_CH12_PB12      /*!< Set PB12 function to EADC0_CH12      */
#define SET_EADC0_CH13_PB13()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC0_CH13_PB13_Msk)) | EADC0_CH13_PB13      /*!< Set PB13 function to EADC0_CH13      */
#define SET_EADC0_CH14_PB14()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC0_CH14_PB14_Msk)) | EADC0_CH14_PB14      /*!< Set PB14 function to EADC0_CH14      */
#define SET_EADC0_CH15_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC0_CH15_PB15_Msk)) | EADC0_CH15_PB15      /*!< Set PB15 function to EADC0_CH15      */
#define SET_EADC0_CH2_PB2()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC0_CH2_PB2_Msk)) | EADC0_CH2_PB2          /*!< Set PB2 function to EADC0_CH2        */
#define SET_EADC0_CH3_PB3()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC0_CH3_PB3_Msk)) | EADC0_CH3_PB3          /*!< Set PB3 function to EADC0_CH3        */
#define SET_EADC0_CH4_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC0_CH4_PB4_Msk)) | EADC0_CH4_PB4          /*!< Set PB4 function to EADC0_CH4        */
#define SET_EADC0_CH5_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC0_CH5_PB5_Msk)) | EADC0_CH5_PB5          /*!< Set PB5 function to EADC0_CH5        */
#define SET_EADC0_CH6_PB6()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC0_CH6_PB6_Msk)) | EADC0_CH6_PB6          /*!< Set PB6 function to EADC0_CH6        */
#define SET_EADC0_CH7_PB7()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC0_CH7_PB7_Msk)) | EADC0_CH7_PB7          /*!< Set PB7 function to EADC0_CH7        */
#define SET_EADC0_CH8_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EADC0_CH8_PB8_Msk)) | EADC0_CH8_PB8          /*!< Set PB8 function to EADC0_CH8        */
#define SET_EADC0_CH9_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EADC0_CH9_PB9_Msk)) | EADC0_CH9_PB9          /*!< Set PB9 function to EADC0_CH9        */
#define SET_EADC0_ST_PF0()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EADC0_ST_PF0_Msk)) | EADC0_ST_PF0            /*!< Set PF0 function to EADC0_ST         */
#define SET_EADC0_ST_PD12()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EADC0_ST_PD12_Msk)) | EADC0_ST_PD12          /*!< Set PD12 function to EADC0_ST        */
#define SET_EADC0_ST_PD6()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~EADC0_ST_PD6_Msk)) | EADC0_ST_PD6            /*!< Set PD6 function to EADC0_ST         */
#define SET_EADC0_ST_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EADC0_ST_PC1_Msk)) | EADC0_ST_PC1            /*!< Set PC1 function to EADC0_ST         */
#define SET_EADC0_ST_PF5()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EADC0_ST_PF5_Msk)) | EADC0_ST_PF5            /*!< Set PF5 function to EADC0_ST         */
#define SET_EADC0_ST_PG15()      SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~EADC0_ST_PG15_Msk)) | EADC0_ST_PG15          /*!< Set PG15 function to EADC0_ST        */
#define SET_EADC0_ST_PD13()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EADC0_ST_PD13_Msk)) | EADC0_ST_PD13          /*!< Set PD13 function to EADC0_ST        */
#define SET_EADC0_ST_PC13()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EADC0_ST_PC13_Msk)) | EADC0_ST_PC13          /*!< Set PC13 function to EADC0_ST        */
#define SET_EADC1_CH0_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EADC1_CH0_PD10_Msk)) | EADC1_CH0_PD10        /*!< Set PD10 function to EADC1_CH0       */
#define SET_EADC1_CH1_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EADC1_CH1_PD11_Msk)) | EADC1_CH1_PD11        /*!< Set PD11 function to EADC1_CH1       */
#define SET_EADC1_CH10_PB2()     SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC1_CH10_PB2_Msk)) | EADC1_CH10_PB2        /*!< Set PB2 function to EADC1_CH10       */
#define SET_EADC1_CH11_PB3()     SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC1_CH11_PB3_Msk)) | EADC1_CH11_PB3        /*!< Set PB3 function to EADC1_CH11       */
#define SET_EADC1_CH12_PB12()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC1_CH12_PB12_Msk)) | EADC1_CH12_PB12      /*!< Set PB12 function to EADC1_CH12      */
#define SET_EADC1_CH13_PB13()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC1_CH13_PB13_Msk)) | EADC1_CH13_PB13      /*!< Set PB13 function to EADC1_CH13      */
#define SET_EADC1_CH14_PB14()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC1_CH14_PB14_Msk)) | EADC1_CH14_PB14      /*!< Set PB14 function to EADC1_CH14      */
#define SET_EADC1_CH15_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EADC1_CH15_PB15_Msk)) | EADC1_CH15_PB15      /*!< Set PB15 function to EADC1_CH15      */
#define SET_EADC1_CH2_PD12()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EADC1_CH2_PD12_Msk)) | EADC1_CH2_PD12        /*!< Set PD12 function to EADC1_CH2       */
#define SET_EADC1_CH3_PC13()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EADC1_CH3_PC13_Msk)) | EADC1_CH3_PC13        /*!< Set PC13 function to EADC1_CH3       */
#define SET_EADC1_CH4_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC1_CH4_PA8_Msk)) | EADC1_CH4_PA8          /*!< Set PA8 function to EADC1_CH4        */
#define SET_EADC1_CH5_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC1_CH5_PA9_Msk)) | EADC1_CH5_PA9          /*!< Set PA9 function to EADC1_CH5        */
#define SET_EADC1_CH6_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC1_CH6_PA10_Msk)) | EADC1_CH6_PA10        /*!< Set PA10 function to EADC1_CH6       */
#define SET_EADC1_CH7_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC1_CH7_PA11_Msk)) | EADC1_CH7_PA11        /*!< Set PA11 function to EADC1_CH7       */
#define SET_EADC1_CH8_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC1_CH8_PB0_Msk)) | EADC1_CH8_PB0          /*!< Set PB0 function to EADC1_CH8        */
#define SET_EADC1_CH9_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC1_CH9_PB1_Msk)) | EADC1_CH9_PB1          /*!< Set PB1 function to EADC1_CH9        */
#define SET_EADC1_ST_PC10()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EADC1_ST_PC10_Msk)) | EADC1_ST_PC10          /*!< Set PC10 function to EADC1_ST        */
#define SET_EADC1_ST_PD5()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~EADC1_ST_PD5_Msk)) | EADC1_ST_PD5            /*!< Set PD5 function to EADC1_ST         */
#define SET_EADC1_ST_PC0()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EADC1_ST_PC0_Msk)) | EADC1_ST_PC0            /*!< Set PC0 function to EADC1_ST         */
#define SET_EADC1_ST_PF1()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EADC1_ST_PF1_Msk)) | EADC1_ST_PF1            /*!< Set PF1 function to EADC1_ST         */
#define SET_EADC1_ST_PF4()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EADC1_ST_PF4_Msk)) | EADC1_ST_PF4            /*!< Set PF4 function to EADC1_ST         */
#define SET_EADC1_ST_PC9()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EADC1_ST_PC9_Msk)) | EADC1_ST_PC9            /*!< Set PC9 function to EADC1_ST         */
#define SET_EADC2_CH0_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EADC2_CH0_PD10_Msk)) | EADC2_CH0_PD10        /*!< Set PD10 function to EADC2_CH0       */
#define SET_EADC2_CH1_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EADC2_CH1_PD11_Msk)) | EADC2_CH1_PD11        /*!< Set PD11 function to EADC2_CH1       */
#define SET_EADC2_CH10_PC9()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EADC2_CH10_PC9_Msk)) | EADC2_CH10_PC9        /*!< Set PC9 function to EADC2_CH10       */
#define SET_EADC2_CH11_PC10()    SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EADC2_CH11_PC10_Msk)) | EADC2_CH11_PC10      /*!< Set PC10 function to EADC2_CH11      */
#define SET_EADC2_CH12_PC11()    SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EADC2_CH12_PC11_Msk)) | EADC2_CH12_PC11      /*!< Set PC11 function to EADC2_CH12      */
#define SET_EADC2_CH13_PC12()    SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EADC2_CH13_PC12_Msk)) | EADC2_CH13_PC12      /*!< Set PC12 function to EADC2_CH13      */
#define SET_EADC2_CH14_PB6()     SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC2_CH14_PB6_Msk)) | EADC2_CH14_PB6        /*!< Set PB6 function to EADC2_CH14       */
#define SET_EADC2_CH15_PB7()     SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EADC2_CH15_PB7_Msk)) | EADC2_CH15_PB7        /*!< Set PB7 function to EADC2_CH15       */
#define SET_EADC2_CH2_PD12()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EADC2_CH2_PD12_Msk)) | EADC2_CH2_PD12        /*!< Set PD12 function to EADC2_CH2       */
#define SET_EADC2_CH3_PC13()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EADC2_CH3_PC13_Msk)) | EADC2_CH3_PC13        /*!< Set PC13 function to EADC2_CH3       */
#define SET_EADC2_CH4_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC2_CH4_PA8_Msk)) | EADC2_CH4_PA8          /*!< Set PA8 function to EADC2_CH4        */
#define SET_EADC2_CH5_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC2_CH5_PA9_Msk)) | EADC2_CH5_PA9          /*!< Set PA9 function to EADC2_CH5        */
#define SET_EADC2_CH6_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC2_CH6_PA10_Msk)) | EADC2_CH6_PA10        /*!< Set PA10 function to EADC2_CH6       */
#define SET_EADC2_CH7_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EADC2_CH7_PA11_Msk)) | EADC2_CH7_PA11        /*!< Set PA11 function to EADC2_CH7       */
#define SET_EADC2_CH8_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC2_CH8_PB0_Msk)) | EADC2_CH8_PB0          /*!< Set PB0 function to EADC2_CH8        */
#define SET_EADC2_CH9_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EADC2_CH9_PB1_Msk)) | EADC2_CH9_PB1          /*!< Set PB1 function to EADC2_CH9        */
#define SET_EADC2_ST_PF3()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EADC2_ST_PF3_Msk)) | EADC2_ST_PF3            /*!< Set PF3 function to EADC2_ST         */
#define SET_EADC2_ST_PB8()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EADC2_ST_PB8_Msk)) | EADC2_ST_PB8            /*!< Set PB8 function to EADC2_ST         */
#define SET_EBI_AD0_PJ7()        SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~EBI_AD0_PJ7_Msk)) | EBI_AD0_PJ7              /*!< Set PJ7 function to EBI_AD0          */
#define SET_EBI_AD0_PF4()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EBI_AD0_PF4_Msk)) | EBI_AD0_PF4              /*!< Set PF4 function to EBI_AD0          */
#define SET_EBI_AD0_PG9()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~EBI_AD0_PG9_Msk)) | EBI_AD0_PG9              /*!< Set PG9 function to EBI_AD0          */
#define SET_EBI_AD0_PC0()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EBI_AD0_PC0_Msk)) | EBI_AD0_PC0              /*!< Set PC0 function to EBI_AD0          */
#define SET_EBI_AD0_PH12()       SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~EBI_AD0_PH12_Msk)) | EBI_AD0_PH12            /*!< Set PH12 function to EBI_AD0         */
#define SET_EBI_AD1_PC1()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EBI_AD1_PC1_Msk)) | EBI_AD1_PC1              /*!< Set PC1 function to EBI_AD1          */
#define SET_EBI_AD1_PH13()       SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~EBI_AD1_PH13_Msk)) | EBI_AD1_PH13            /*!< Set PH13 function to EBI_AD1         */
#define SET_EBI_AD1_PJ6()        SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~EBI_AD1_PJ6_Msk)) | EBI_AD1_PJ6              /*!< Set PJ6 function to EBI_AD1          */
#define SET_EBI_AD1_PG10()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~EBI_AD1_PG10_Msk)) | EBI_AD1_PG10            /*!< Set PG10 function to EBI_AD1         */
#define SET_EBI_AD1_PF5()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EBI_AD1_PF5_Msk)) | EBI_AD1_PF5              /*!< Set PF5 function to EBI_AD1          */
#define SET_EBI_AD10_PD3()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EBI_AD10_PD3_Msk)) | EBI_AD10_PD3            /*!< Set PD3 function to EBI_AD10         */
#define SET_EBI_AD10_PE1()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EBI_AD10_PE1_Msk)) | EBI_AD10_PE1            /*!< Set PE1 function to EBI_AD10         */
#define SET_EBI_AD10_PD13()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EBI_AD10_PD13_Msk)) | EBI_AD10_PD13          /*!< Set PD13 function to EBI_AD10        */
#define SET_EBI_AD11_PE0()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EBI_AD11_PE0_Msk)) | EBI_AD11_PE0            /*!< Set PE0 function to EBI_AD11         */
#define SET_EBI_AD11_PC14()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EBI_AD11_PC14_Msk)) | EBI_AD11_PC14          /*!< Set PC14 function to EBI_AD11        */
#define SET_EBI_AD11_PD2()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EBI_AD11_PD2_Msk)) | EBI_AD11_PD2            /*!< Set PD2 function to EBI_AD11         */
#define SET_EBI_AD12_PD1()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EBI_AD12_PD1_Msk)) | EBI_AD12_PD1            /*!< Set PD1 function to EBI_AD12         */
#define SET_EBI_AD12_PH8()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~EBI_AD12_PH8_Msk)) | EBI_AD12_PH8            /*!< Set PH8 function to EBI_AD12         */
#define SET_EBI_AD12_PB15()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EBI_AD12_PB15_Msk)) | EBI_AD12_PB15          /*!< Set PB15 function to EBI_AD12        */
#define SET_EBI_AD13_PD0()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EBI_AD13_PD0_Msk)) | EBI_AD13_PD0            /*!< Set PD0 function to EBI_AD13         */
#define SET_EBI_AD13_PH9()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~EBI_AD13_PH9_Msk)) | EBI_AD13_PH9            /*!< Set PH9 function to EBI_AD13         */
#define SET_EBI_AD13_PB14()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EBI_AD13_PB14_Msk)) | EBI_AD13_PB14          /*!< Set PB14 function to EBI_AD13        */
#define SET_EBI_AD14_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EBI_AD14_PB13_Msk)) | EBI_AD14_PB13          /*!< Set PB13 function to EBI_AD14        */
#define SET_EBI_AD14_PH10()      SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~EBI_AD14_PH10_Msk)) | EBI_AD14_PH10          /*!< Set PH10 function to EBI_AD14        */
#define SET_EBI_AD15_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EBI_AD15_PB12_Msk)) | EBI_AD15_PB12          /*!< Set PB12 function to EBI_AD15        */
#define SET_EBI_AD15_PH11()      SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~EBI_AD15_PH11_Msk)) | EBI_AD15_PH11          /*!< Set PH11 function to EBI_AD15        */
#define SET_EBI_AD2_PH14()       SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~EBI_AD2_PH14_Msk)) | EBI_AD2_PH14            /*!< Set PH14 function to EBI_AD2         */
#define SET_EBI_AD2_PG11()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~EBI_AD2_PG11_Msk)) | EBI_AD2_PG11            /*!< Set PG11 function to EBI_AD2         */
#define SET_EBI_AD2_PC2()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EBI_AD2_PC2_Msk)) | EBI_AD2_PC2              /*!< Set PC2 function to EBI_AD2          */
#define SET_EBI_AD2_PJ5()        SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~EBI_AD2_PJ5_Msk)) | EBI_AD2_PJ5              /*!< Set PJ5 function to EBI_AD2          */
#define SET_EBI_AD3_PJ4()        SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~EBI_AD3_PJ4_Msk)) | EBI_AD3_PJ4              /*!< Set PJ4 function to EBI_AD3          */
#define SET_EBI_AD3_PH15()       SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~EBI_AD3_PH15_Msk)) | EBI_AD3_PH15            /*!< Set PH15 function to EBI_AD3         */
#define SET_EBI_AD3_PG12()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~EBI_AD3_PG12_Msk)) | EBI_AD3_PG12            /*!< Set PG12 function to EBI_AD3         */
#define SET_EBI_AD3_PC3()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EBI_AD3_PC3_Msk)) | EBI_AD3_PC3              /*!< Set PC3 function to EBI_AD3          */
#define SET_EBI_AD4_PG13()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~EBI_AD4_PG13_Msk)) | EBI_AD4_PG13            /*!< Set PG13 function to EBI_AD4         */
#define SET_EBI_AD4_PJ3()        SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~EBI_AD4_PJ3_Msk)) | EBI_AD4_PJ3              /*!< Set PJ3 function to EBI_AD4          */
#define SET_EBI_AD4_PD7()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~EBI_AD4_PD7_Msk)) | EBI_AD4_PD7              /*!< Set PD7 function to EBI_AD4          */
#define SET_EBI_AD4_PC4()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EBI_AD4_PC4_Msk)) | EBI_AD4_PC4              /*!< Set PC4 function to EBI_AD4          */
#define SET_EBI_AD5_PJ2()        SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~EBI_AD5_PJ2_Msk)) | EBI_AD5_PJ2              /*!< Set PJ2 function to EBI_AD5          */
#define SET_EBI_AD5_PA14()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EBI_AD5_PA14_Msk)) | EBI_AD5_PA14            /*!< Set PA14 function to EBI_AD5         */
#define SET_EBI_AD5_PD6()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~EBI_AD5_PD6_Msk)) | EBI_AD5_PD6              /*!< Set PD6 function to EBI_AD5          */
#define SET_EBI_AD5_PG14()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~EBI_AD5_PG14_Msk)) | EBI_AD5_PG14            /*!< Set PG14 function to EBI_AD5         */
#define SET_EBI_AD5_PC5()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EBI_AD5_PC5_Msk)) | EBI_AD5_PC5              /*!< Set PC5 function to EBI_AD5          */
#define SET_EBI_AD6_PD8()        SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EBI_AD6_PD8_Msk)) | EBI_AD6_PD8              /*!< Set PD8 function to EBI_AD6          */
#define SET_EBI_AD6_PA6()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EBI_AD6_PA6_Msk)) | EBI_AD6_PA6              /*!< Set PA6 function to EBI_AD6          */
#define SET_EBI_AD7_PA7()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EBI_AD7_PA7_Msk)) | EBI_AD7_PA7              /*!< Set PA7 function to EBI_AD7          */
#define SET_EBI_AD7_PD9()        SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EBI_AD7_PD9_Msk)) | EBI_AD7_PD9              /*!< Set PD9 function to EBI_AD7          */
#define SET_EBI_AD8_PC6()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EBI_AD8_PC6_Msk)) | EBI_AD8_PC6              /*!< Set PC6 function to EBI_AD8          */
#define SET_EBI_AD8_PE14()       SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EBI_AD8_PE14_Msk)) | EBI_AD8_PE14            /*!< Set PE14 function to EBI_AD8         */
#define SET_EBI_AD9_PE15()       SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EBI_AD9_PE15_Msk)) | EBI_AD9_PE15            /*!< Set PE15 function to EBI_AD9         */
#define SET_EBI_AD9_PC7()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EBI_AD9_PC7_Msk)) | EBI_AD9_PC7              /*!< Set PC7 function to EBI_AD9          */
#define SET_EBI_ADR0_PB5()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_ADR0_PB5_Msk)) | EBI_ADR0_PB5            /*!< Set PB5 function to EBI_ADR0         */
#define SET_EBI_ADR0_PH7()       SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~EBI_ADR0_PH7_Msk)) | EBI_ADR0_PH7            /*!< Set PH7 function to EBI_ADR0         */
#define SET_EBI_ADR1_PH6()       SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~EBI_ADR1_PH6_Msk)) | EBI_ADR1_PH6            /*!< Set PH6 function to EBI_ADR1         */
#define SET_EBI_ADR1_PB4()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_ADR1_PB4_Msk)) | EBI_ADR1_PB4            /*!< Set PB4 function to EBI_ADR1         */
#define SET_EBI_ADR10_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EBI_ADR10_PE8_Msk)) | EBI_ADR10_PE8          /*!< Set PE8 function to EBI_ADR10        */
#define SET_EBI_ADR10_PC13()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EBI_ADR10_PC13_Msk)) | EBI_ADR10_PC13        /*!< Set PC13 function to EBI_ADR10       */
#define SET_EBI_ADR11_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EBI_ADR11_PE9_Msk)) | EBI_ADR11_PE9          /*!< Set PE9 function to EBI_ADR11        */
#define SET_EBI_ADR11_PG2()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~EBI_ADR11_PG2_Msk)) | EBI_ADR11_PG2          /*!< Set PG2 function to EBI_ADR11        */
#define SET_EBI_ADR12_PG3()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~EBI_ADR12_PG3_Msk)) | EBI_ADR12_PG3          /*!< Set PG3 function to EBI_ADR12        */
#define SET_EBI_ADR12_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EBI_ADR12_PE10_Msk)) | EBI_ADR12_PE10        /*!< Set PE10 function to EBI_ADR12       */
#define SET_EBI_ADR13_PE11()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EBI_ADR13_PE11_Msk)) | EBI_ADR13_PE11        /*!< Set PE11 function to EBI_ADR13       */
#define SET_EBI_ADR13_PG4()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EBI_ADR13_PG4_Msk)) | EBI_ADR13_PG4          /*!< Set PG4 function to EBI_ADR13        */
#define SET_EBI_ADR14_PF11()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~EBI_ADR14_PF11_Msk)) | EBI_ADR14_PF11        /*!< Set PF11 function to EBI_ADR14       */
#define SET_EBI_ADR14_PE12()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EBI_ADR14_PE12_Msk)) | EBI_ADR14_PE12        /*!< Set PE12 function to EBI_ADR14       */
#define SET_EBI_ADR15_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EBI_ADR15_PE13_Msk)) | EBI_ADR15_PE13        /*!< Set PE13 function to EBI_ADR15       */
#define SET_EBI_ADR15_PF10()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~EBI_ADR15_PF10_Msk)) | EBI_ADR15_PF10        /*!< Set PF10 function to EBI_ADR15       */
#define SET_EBI_ADR16_PB11()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EBI_ADR16_PB11_Msk)) | EBI_ADR16_PB11        /*!< Set PB11 function to EBI_ADR16       */
#define SET_EBI_ADR16_PC8()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EBI_ADR16_PC8_Msk)) | EBI_ADR16_PC8          /*!< Set PC8 function to EBI_ADR16        */
#define SET_EBI_ADR16_PF9()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~EBI_ADR16_PF9_Msk)) | EBI_ADR16_PF9          /*!< Set PF9 function to EBI_ADR16        */
#define SET_EBI_ADR17_PB10()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EBI_ADR17_PB10_Msk)) | EBI_ADR17_PB10        /*!< Set PB10 function to EBI_ADR17       */
#define SET_EBI_ADR17_PF8()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~EBI_ADR17_PF8_Msk)) | EBI_ADR17_PF8          /*!< Set PF8 function to EBI_ADR17        */
#define SET_EBI_ADR18_PF7()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EBI_ADR18_PF7_Msk)) | EBI_ADR18_PF7          /*!< Set PF7 function to EBI_ADR18        */
#define SET_EBI_ADR18_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EBI_ADR18_PB9_Msk)) | EBI_ADR18_PB9          /*!< Set PB9 function to EBI_ADR18        */
#define SET_EBI_ADR19_PF6()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EBI_ADR19_PF6_Msk)) | EBI_ADR19_PF6          /*!< Set PF6 function to EBI_ADR19        */
#define SET_EBI_ADR19_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EBI_ADR19_PB8_Msk)) | EBI_ADR19_PB8          /*!< Set PB8 function to EBI_ADR19        */
#define SET_EBI_ADR2_PB3()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EBI_ADR2_PB3_Msk)) | EBI_ADR2_PB3            /*!< Set PB3 function to EBI_ADR2         */
#define SET_EBI_ADR2_PH5()       SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~EBI_ADR2_PH5_Msk)) | EBI_ADR2_PH5            /*!< Set PH5 function to EBI_ADR2         */
#define SET_EBI_ADR3_PH4()       SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~EBI_ADR3_PH4_Msk)) | EBI_ADR3_PH4            /*!< Set PH4 function to EBI_ADR3         */
#define SET_EBI_ADR3_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EBI_ADR3_PB2_Msk)) | EBI_ADR3_PB2            /*!< Set PB2 function to EBI_ADR3         */
#define SET_EBI_ADR4_PC12()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EBI_ADR4_PC12_Msk)) | EBI_ADR4_PC12          /*!< Set PC12 function to EBI_ADR4        */
#define SET_EBI_ADR4_PH3()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~EBI_ADR4_PH3_Msk)) | EBI_ADR4_PH3            /*!< Set PH3 function to EBI_ADR4         */
#define SET_EBI_ADR5_PH2()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~EBI_ADR5_PH2_Msk)) | EBI_ADR5_PH2            /*!< Set PH2 function to EBI_ADR5         */
#define SET_EBI_ADR5_PC11()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EBI_ADR5_PC11_Msk)) | EBI_ADR5_PC11          /*!< Set PC11 function to EBI_ADR5        */
#define SET_EBI_ADR6_PC10()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EBI_ADR6_PC10_Msk)) | EBI_ADR6_PC10          /*!< Set PC10 function to EBI_ADR6        */
#define SET_EBI_ADR6_PH1()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~EBI_ADR6_PH1_Msk)) | EBI_ADR6_PH1            /*!< Set PH1 function to EBI_ADR6         */
#define SET_EBI_ADR7_PH0()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~EBI_ADR7_PH0_Msk)) | EBI_ADR7_PH0            /*!< Set PH0 function to EBI_ADR7         */
#define SET_EBI_ADR7_PC9()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EBI_ADR7_PC9_Msk)) | EBI_ADR7_PC9            /*!< Set PC9 function to EBI_ADR7         */
#define SET_EBI_ADR8_PG0()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~EBI_ADR8_PG0_Msk)) | EBI_ADR8_PG0            /*!< Set PG0 function to EBI_ADR8         */
#define SET_EBI_ADR8_PB1()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EBI_ADR8_PB1_Msk)) | EBI_ADR8_PB1            /*!< Set PB1 function to EBI_ADR8         */
#define SET_EBI_ADR9_PB0()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EBI_ADR9_PB0_Msk)) | EBI_ADR9_PB0            /*!< Set PB0 function to EBI_ADR9         */
#define SET_EBI_ADR9_PG1()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~EBI_ADR9_PG1_Msk)) | EBI_ADR9_PG1            /*!< Set PG1 function to EBI_ADR9         */
#define SET_EBI_ALE_PA8()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EBI_ALE_PA8_Msk)) | EBI_ALE_PA8              /*!< Set PA8 function to EBI_ALE          */
#define SET_EBI_ALE_PE2()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EBI_ALE_PE2_Msk)) | EBI_ALE_PE2              /*!< Set PE2 function to EBI_ALE          */
#define SET_EBI_ALE_PJ11()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~EBI_ALE_PJ11_Msk)) | EBI_ALE_PJ11            /*!< Set PJ11 function to EBI_ALE         */
#define SET_EBI_MCLK_PE3()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EBI_MCLK_PE3_Msk)) | EBI_MCLK_PE3            /*!< Set PE3 function to EBI_MCLK         */
#define SET_EBI_MCLK_PA9()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EBI_MCLK_PA9_Msk)) | EBI_MCLK_PA9            /*!< Set PA9 function to EBI_MCLK         */
#define SET_EBI_MCLK_PJ10()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~EBI_MCLK_PJ10_Msk)) | EBI_MCLK_PJ10          /*!< Set PJ10 function to EBI_MCLK        */
#define SET_EBI_nCS0_PF3()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EBI_nCS0_PF3_Msk)) | EBI_nCS0_PF3            /*!< Set PF3 function to EBI_nCS0         */
#define SET_EBI_nCS0_PJ12()      SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~EBI_nCS0_PJ12_Msk)) | EBI_nCS0_PJ12          /*!< Set PJ12 function to EBI_nCS0        */
#define SET_EBI_nCS0_PD14()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EBI_nCS0_PD14_Msk)) | EBI_nCS0_PD14          /*!< Set PD14 function to EBI_nCS0        */
#define SET_EBI_nCS0_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_nCS0_PB7_Msk)) | EBI_nCS0_PB7            /*!< Set PB7 function to EBI_nCS0         */
#define SET_EBI_nCS0_PF6()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EBI_nCS0_PF6_Msk)) | EBI_nCS0_PF6            /*!< Set PF6 function to EBI_nCS0         */
#define SET_EBI_nCS0_PD12()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EBI_nCS0_PD12_Msk)) | EBI_nCS0_PD12          /*!< Set PD12 function to EBI_nCS0        */
#define SET_EBI_nCS1_PB6()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_nCS1_PB6_Msk)) | EBI_nCS1_PB6            /*!< Set PB6 function to EBI_nCS1         */
#define SET_EBI_nCS1_PG5()       SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EBI_nCS1_PG5_Msk)) | EBI_nCS1_PG5            /*!< Set PG5 function to EBI_nCS1         */
#define SET_EBI_nCS1_PD11()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EBI_nCS1_PD11_Msk)) | EBI_nCS1_PD11          /*!< Set PD11 function to EBI_nCS1        */
#define SET_EBI_nCS1_PF2()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EBI_nCS1_PF2_Msk)) | EBI_nCS1_PF2            /*!< Set PF2 function to EBI_nCS1         */
#define SET_EBI_nCS2_PD10()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EBI_nCS2_PD10_Msk)) | EBI_nCS2_PD10          /*!< Set PD10 function to EBI_nCS2        */
#define SET_EBI_nCS2_PG6()       SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EBI_nCS2_PG6_Msk)) | EBI_nCS2_PG6            /*!< Set PG6 function to EBI_nCS2         */
#define SET_EBI_nRD_PA11()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EBI_nRD_PA11_Msk)) | EBI_nRD_PA11            /*!< Set PA11 function to EBI_nRD         */
#define SET_EBI_nRD_PE5()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EBI_nRD_PE5_Msk)) | EBI_nRD_PE5              /*!< Set PE5 function to EBI_nRD          */
#define SET_EBI_nRD_PJ8()        SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~EBI_nRD_PJ8_Msk)) | EBI_nRD_PJ8              /*!< Set PJ8 function to EBI_nRD          */
#define SET_EBI_nWR_PA10()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EBI_nWR_PA10_Msk)) | EBI_nWR_PA10            /*!< Set PA10 function to EBI_nWR         */
#define SET_EBI_nWR_PJ9()        SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~EBI_nWR_PJ9_Msk)) | EBI_nWR_PJ9              /*!< Set PJ9 function to EBI_nWR          */
#define SET_EBI_nWR_PE4()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EBI_nWR_PE4_Msk)) | EBI_nWR_PE4              /*!< Set PE4 function to EBI_nWR          */
#define SET_EBI_nWRH_PB6()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_nWRH_PB6_Msk)) | EBI_nWRH_PB6            /*!< Set PB6 function to EBI_nWRH         */
#define SET_EBI_nWRH_PG8()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~EBI_nWRH_PG8_Msk)) | EBI_nWRH_PG8            /*!< Set PG8 function to EBI_nWRH         */
#define SET_EBI_nWRL_PG7()       SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EBI_nWRL_PG7_Msk)) | EBI_nWRL_PG7            /*!< Set PG7 function to EBI_nWRL         */
#define SET_EBI_nWRL_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EBI_nWRL_PB7_Msk)) | EBI_nWRL_PB7            /*!< Set PB7 function to EBI_nWRL         */
#define SET_ECAP0_IC0_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP0_IC0_PE8_Msk)) | ECAP0_IC0_PE8          /*!< Set PE8 function to ECAP0_IC0        */
#define SET_ECAP0_IC0_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~ECAP0_IC0_PA10_Msk)) | ECAP0_IC0_PA10        /*!< Set PA10 function to ECAP0_IC0       */
#define SET_ECAP0_IC1_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~ECAP0_IC1_PA9_Msk)) | ECAP0_IC1_PA9          /*!< Set PA9 function to ECAP0_IC1        */
#define SET_ECAP0_IC1_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP0_IC1_PE9_Msk)) | ECAP0_IC1_PE9          /*!< Set PE9 function to ECAP0_IC1        */
#define SET_ECAP0_IC2_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP0_IC2_PE10_Msk)) | ECAP0_IC2_PE10        /*!< Set PE10 function to ECAP0_IC2       */
#define SET_ECAP0_IC2_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~ECAP0_IC2_PA8_Msk)) | ECAP0_IC2_PA8          /*!< Set PA8 function to ECAP0_IC2        */
#define SET_ECAP1_IC0_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~ECAP1_IC0_PE13_Msk)) | ECAP1_IC0_PE13        /*!< Set PE13 function to ECAP1_IC0       */
#define SET_ECAP1_IC0_PC10()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ECAP1_IC0_PC10_Msk)) | ECAP1_IC0_PC10        /*!< Set PC10 function to ECAP1_IC0       */
#define SET_ECAP1_IC1_PC11()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~ECAP1_IC1_PC11_Msk)) | ECAP1_IC1_PC11        /*!< Set PC11 function to ECAP1_IC1       */
#define SET_ECAP1_IC1_PE12()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~ECAP1_IC1_PE12_Msk)) | ECAP1_IC1_PE12        /*!< Set PE12 function to ECAP1_IC1       */
#define SET_ECAP1_IC2_PC12()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~ECAP1_IC2_PC12_Msk)) | ECAP1_IC2_PC12        /*!< Set PC12 function to ECAP1_IC2       */
#define SET_ECAP1_IC2_PE11()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP1_IC2_PE11_Msk)) | ECAP1_IC2_PE11        /*!< Set PE11 function to ECAP1_IC2       */
#define SET_ECAP2_IC0_PG9()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~ECAP2_IC0_PG9_Msk)) | ECAP2_IC0_PG9          /*!< Set PG9 function to ECAP2_IC0        */
#define SET_ECAP2_IC0_PJ10()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~ECAP2_IC0_PJ10_Msk)) | ECAP2_IC0_PJ10        /*!< Set PJ10 function to ECAP2_IC0       */
#define SET_ECAP2_IC0_PD1()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~ECAP2_IC0_PD1_Msk)) | ECAP2_IC0_PD1          /*!< Set PD1 function to ECAP2_IC0        */
#define SET_ECAP2_IC1_PD0()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~ECAP2_IC1_PD0_Msk)) | ECAP2_IC1_PD0          /*!< Set PD0 function to ECAP2_IC1        */
#define SET_ECAP2_IC1_PJ11()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~ECAP2_IC1_PJ11_Msk)) | ECAP2_IC1_PJ11        /*!< Set PJ11 function to ECAP2_IC1       */
#define SET_ECAP2_IC1_PG10()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~ECAP2_IC1_PG10_Msk)) | ECAP2_IC1_PG10        /*!< Set PG10 function to ECAP2_IC1       */
#define SET_ECAP2_IC2_PG11()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~ECAP2_IC2_PG11_Msk)) | ECAP2_IC2_PG11        /*!< Set PG11 function to ECAP2_IC2       */
#define SET_ECAP2_IC2_PJ12()     SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~ECAP2_IC2_PJ12_Msk)) | ECAP2_IC2_PJ12        /*!< Set PJ12 function to ECAP2_IC2       */
#define SET_ECAP2_IC2_PD13()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~ECAP2_IC2_PD13_Msk)) | ECAP2_IC2_PD13        /*!< Set PD13 function to ECAP2_IC2       */
#define SET_ECAP3_IC0_PA12()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~ECAP3_IC0_PA12_Msk)) | ECAP3_IC0_PA12        /*!< Set PA12 function to ECAP3_IC0       */
#define SET_ECAP3_IC0_PD12()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~ECAP3_IC0_PD12_Msk)) | ECAP3_IC0_PD12        /*!< Set PD12 function to ECAP3_IC0       */
#define SET_ECAP3_IC0_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP3_IC0_PE8_Msk)) | ECAP3_IC0_PE8          /*!< Set PE8 function to ECAP3_IC0        */
#define SET_ECAP3_IC1_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~ECAP3_IC1_PA13_Msk)) | ECAP3_IC1_PA13        /*!< Set PA13 function to ECAP3_IC1       */
#define SET_ECAP3_IC1_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP3_IC1_PE9_Msk)) | ECAP3_IC1_PE9          /*!< Set PE9 function to ECAP3_IC1        */
#define SET_ECAP3_IC1_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~ECAP3_IC1_PD11_Msk)) | ECAP3_IC1_PD11        /*!< Set PD11 function to ECAP3_IC1       */
#define SET_ECAP3_IC2_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~ECAP3_IC2_PE10_Msk)) | ECAP3_IC2_PE10        /*!< Set PE10 function to ECAP3_IC2       */
#define SET_ECAP3_IC2_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~ECAP3_IC2_PD10_Msk)) | ECAP3_IC2_PD10        /*!< Set PD10 function to ECAP3_IC2       */
#define SET_ECAP3_IC2_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~ECAP3_IC2_PA14_Msk)) | ECAP3_IC2_PA14        /*!< Set PA14 function to ECAP3_IC2       */
#define SET_EMAC0_PPS_PE13()        SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EMAC0_PPS_PE13_Msk)) | EMAC0_PPS_PE13               /*!< Set PE13 function to EMAC0_PPS        */
#define SET_EMAC0_PPS_PB6()         SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EMAC0_PPS_PB6_Msk)) | EMAC0_PPS_PB6                 /*!< Set PB6 function to EMAC0_PPS         */
#define SET_EMAC0_RMII_CRSDV_PA7()  SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EMAC0_RMII_CRSDV_PA7_Msk)) | EMAC0_RMII_CRSDV_PA7   /*!< Set PA7 function to EMAC0_RMII_CRSDV  */
#define SET_EMAC0_RMII_CRSDV_PB2()  SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EMAC0_RMII_CRSDV_PB2_Msk)) | EMAC0_RMII_CRSDV_PB2   /*!< Set PB2 function to EMAC0_RMII_CRSDV  */
#define SET_EMAC0_RMII_MDC_PE8()    SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EMAC0_RMII_MDC_PE8_Msk)) | EMAC0_RMII_MDC_PE8       /*!< Set PE8 function to EMAC0_RMII_MDC    */
#define SET_EMAC0_RMII_MDC_PB11()   SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EMAC0_RMII_MDC_PB11_Msk)) | EMAC0_RMII_MDC_PB11     /*!< Set PB11 function to EMAC0_RMII_MDC   */
#define SET_EMAC0_RMII_MDIO_PB10()  SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EMAC0_RMII_MDIO_PB10_Msk)) | EMAC0_RMII_MDIO_PB10   /*!< Set PB10 function to EMAC0_RMII_MDIO  */
#define SET_EMAC0_RMII_MDIO_PE9()   SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EMAC0_RMII_MDIO_PE9_Msk)) | EMAC0_RMII_MDIO_PE9     /*!< Set PE9 function to EMAC0_RMII_MDIO   */
#define SET_EMAC0_RMII_REFCLK_PB5() SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EMAC0_RMII_REFCLK_PB5_Msk)) | EMAC0_RMII_REFCLK_PB5 /*!< Set PB5 function to EMAC0_RMII_REFCLK */
#define SET_EMAC0_RMII_REFCLK_PC8() SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EMAC0_RMII_REFCLK_PC8_Msk)) | EMAC0_RMII_REFCLK_PC8 /*!< Set PC8 function to EMAC0_RMII_REFCLK */
#define SET_EMAC0_RMII_RXD0_PC7()   SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EMAC0_RMII_RXD0_PC7_Msk)) | EMAC0_RMII_RXD0_PC7     /*!< Set PC7 function to EMAC0_RMII_RXD0   */
#define SET_EMAC0_RMII_RXD0_PB4()   SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EMAC0_RMII_RXD0_PB4_Msk)) | EMAC0_RMII_RXD0_PB4     /*!< Set PB4 function to EMAC0_RMII_RXD0   */
#define SET_EMAC0_RMII_RXD1_PB3()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EMAC0_RMII_RXD1_PB3_Msk)) | EMAC0_RMII_RXD1_PB3     /*!< Set PB3 function to EMAC0_RMII_RXD1   */
#define SET_EMAC0_RMII_RXD1_PC6()   SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EMAC0_RMII_RXD1_PC6_Msk)) | EMAC0_RMII_RXD1_PC6     /*!< Set PC6 function to EMAC0_RMII_RXD1   */
#define SET_EMAC0_RMII_RXERR_PA6()  SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EMAC0_RMII_RXERR_PA6_Msk)) | EMAC0_RMII_RXERR_PA6   /*!< Set PA6 function to EMAC0_RMII_RXERR  */
#define SET_EMAC0_RMII_RXERR_PB1()  SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EMAC0_RMII_RXERR_PB1_Msk)) | EMAC0_RMII_RXERR_PB1   /*!< Set PB1 function to EMAC0_RMII_RXERR  */
#define SET_EMAC0_RMII_TXD0_PE10()  SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EMAC0_RMII_TXD0_PE10_Msk)) | EMAC0_RMII_TXD0_PE10   /*!< Set PE10 function to EMAC0_RMII_TXD0  */
#define SET_EMAC0_RMII_TXD0_PB9()   SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EMAC0_RMII_TXD0_PB9_Msk)) | EMAC0_RMII_TXD0_PB9     /*!< Set PB9 function to EMAC0_RMII_TXD0   */
#define SET_EMAC0_RMII_TXD1_PB8()   SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~EMAC0_RMII_TXD1_PB8_Msk)) | EMAC0_RMII_TXD1_PB8     /*!< Set PB8 function to EMAC0_RMII_TXD1   */
#define SET_EMAC0_RMII_TXD1_PE11()  SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EMAC0_RMII_TXD1_PE11_Msk)) | EMAC0_RMII_TXD1_PE11   /*!< Set PE11 function to EMAC0_RMII_TXD1  */
#define SET_EMAC0_RMII_TXEN_PB7()   SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EMAC0_RMII_TXEN_PB7_Msk)) | EMAC0_RMII_TXEN_PB7     /*!< Set PB7 function to EMAC0_RMII_TXEN   */
#define SET_EMAC0_RMII_TXEN_PE12()  SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EMAC0_RMII_TXEN_PE12_Msk)) | EMAC0_RMII_TXEN_PE12   /*!< Set PE12 function to EMAC0_RMII_TXEN  */
#define SET_EPWM0_BRAKE0_PE8()   SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_BRAKE0_PE8_Msk)) | EPWM0_BRAKE0_PE8    /*!< Set PE8 function to EPWM0_BRAKE0     */
#define SET_EPWM0_BRAKE0_PB1()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_BRAKE0_PB1_Msk)) | EPWM0_BRAKE0_PB1    /*!< Set PB1 function to EPWM0_BRAKE0     */
#define SET_EPWM0_BRAKE1_PE9()   SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_BRAKE1_PE9_Msk)) | EPWM0_BRAKE1_PE9    /*!< Set PE9 function to EPWM0_BRAKE1     */
#define SET_EPWM0_BRAKE1_PB15()  SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EPWM0_BRAKE1_PB15_Msk)) | EPWM0_BRAKE1_PB15  /*!< Set PB15 function to EPWM0_BRAKE1    */
#define SET_EPWM0_BRAKE1_PB0()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_BRAKE1_PB0_Msk)) | EPWM0_BRAKE1_PB0    /*!< Set PB0 function to EPWM0_BRAKE1     */
#define SET_EPWM0_CH0_PA5()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EPWM0_CH0_PA5_Msk)) | EPWM0_CH0_PA5          /*!< Set PA5 function to EPWM0_CH0        */
#define SET_EPWM0_CH0_PG8()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~EPWM0_CH0_PG8_Msk)) | EPWM0_CH0_PG8          /*!< Set PG8 function to EPWM0_CH0        */
#define SET_EPWM0_CH0_PF5()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EPWM0_CH0_PF5_Msk)) | EPWM0_CH0_PF5          /*!< Set PF5 function to EPWM0_CH0        */
#define SET_EPWM0_CH0_PE7()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EPWM0_CH0_PE7_Msk)) | EPWM0_CH0_PE7          /*!< Set PE7 function to EPWM0_CH0        */
#define SET_EPWM0_CH0_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM0_CH0_PB5_Msk)) | EPWM0_CH0_PB5          /*!< Set PB5 function to EPWM0_CH0        */
#define SET_EPWM0_CH0_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_CH0_PE8_Msk)) | EPWM0_CH0_PE8          /*!< Set PE8 function to EPWM0_CH0        */
#define SET_EPWM0_CH1_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_CH1_PE9_Msk)) | EPWM0_CH1_PE9          /*!< Set PE9 function to EPWM0_CH1        */
#define SET_EPWM0_CH1_PE6()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EPWM0_CH1_PE6_Msk)) | EPWM0_CH1_PE6          /*!< Set PE6 function to EPWM0_CH1        */
#define SET_EPWM0_CH1_PF4()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EPWM0_CH1_PF4_Msk)) | EPWM0_CH1_PF4          /*!< Set PF4 function to EPWM0_CH1        */
#define SET_EPWM0_CH1_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM0_CH1_PB4_Msk)) | EPWM0_CH1_PB4          /*!< Set PB4 function to EPWM0_CH1        */
#define SET_EPWM0_CH1_PA4()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EPWM0_CH1_PA4_Msk)) | EPWM0_CH1_PA4          /*!< Set PA4 function to EPWM0_CH1        */
#define SET_EPWM0_CH1_PG7()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EPWM0_CH1_PG7_Msk)) | EPWM0_CH1_PG7          /*!< Set PG7 function to EPWM0_CH1        */
#define SET_EPWM0_CH2_PE5()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EPWM0_CH2_PE5_Msk)) | EPWM0_CH2_PE5          /*!< Set PE5 function to EPWM0_CH2        */
#define SET_EPWM0_CH2_PG6()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EPWM0_CH2_PG6_Msk)) | EPWM0_CH2_PG6          /*!< Set PG6 function to EPWM0_CH2        */
#define SET_EPWM0_CH2_PA3()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EPWM0_CH2_PA3_Msk)) | EPWM0_CH2_PA3          /*!< Set PA3 function to EPWM0_CH2        */
#define SET_EPWM0_CH2_PB3()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_CH2_PB3_Msk)) | EPWM0_CH2_PB3          /*!< Set PB3 function to EPWM0_CH2        */
#define SET_EPWM0_CH2_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_CH2_PE10_Msk)) | EPWM0_CH2_PE10        /*!< Set PE10 function to EPWM0_CH2       */
#define SET_EPWM0_CH3_PB2()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_CH3_PB2_Msk)) | EPWM0_CH3_PB2          /*!< Set PB2 function to EPWM0_CH3        */
#define SET_EPWM0_CH3_PE4()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EPWM0_CH3_PE4_Msk)) | EPWM0_CH3_PE4          /*!< Set PE4 function to EPWM0_CH3        */
#define SET_EPWM0_CH3_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EPWM0_CH3_PA2_Msk)) | EPWM0_CH3_PA2          /*!< Set PA2 function to EPWM0_CH3        */
#define SET_EPWM0_CH3_PE11()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM0_CH3_PE11_Msk)) | EPWM0_CH3_PE11        /*!< Set PE11 function to EPWM0_CH3       */
#define SET_EPWM0_CH3_PG5()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~EPWM0_CH3_PG5_Msk)) | EPWM0_CH3_PG5          /*!< Set PG5 function to EPWM0_CH3        */
#define SET_EPWM0_CH4_PD14()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EPWM0_CH4_PD14_Msk)) | EPWM0_CH4_PD14        /*!< Set PD14 function to EPWM0_CH4       */
#define SET_EPWM0_CH4_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_CH4_PB1_Msk)) | EPWM0_CH4_PB1          /*!< Set PB1 function to EPWM0_CH4        */
#define SET_EPWM0_CH4_PE12()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EPWM0_CH4_PE12_Msk)) | EPWM0_CH4_PE12        /*!< Set PE12 function to EPWM0_CH4       */
#define SET_EPWM0_CH4_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EPWM0_CH4_PA1_Msk)) | EPWM0_CH4_PA1          /*!< Set PA1 function to EPWM0_CH4        */
#define SET_EPWM0_CH4_PE3()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EPWM0_CH4_PE3_Msk)) | EPWM0_CH4_PE3          /*!< Set PE3 function to EPWM0_CH4        */
#define SET_EPWM0_CH5_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EPWM0_CH5_PE13_Msk)) | EPWM0_CH5_PE13        /*!< Set PE13 function to EPWM0_CH5       */
#define SET_EPWM0_CH5_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EPWM0_CH5_PA0_Msk)) | EPWM0_CH5_PA0          /*!< Set PA0 function to EPWM0_CH5        */
#define SET_EPWM0_CH5_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM0_CH5_PB0_Msk)) | EPWM0_CH5_PB0          /*!< Set PB0 function to EPWM0_CH5        */
#define SET_EPWM0_CH5_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EPWM0_CH5_PE2_Msk)) | EPWM0_CH5_PE2          /*!< Set PE2 function to EPWM0_CH5        */
#define SET_EPWM0_CH5_PH11()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~EPWM0_CH5_PH11_Msk)) | EPWM0_CH5_PH11        /*!< Set PH11 function to EPWM0_CH5       */
#define SET_EPWM0_SYNC_IN_PA15() SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EPWM0_SYNC_IN_PA15_Msk)) | EPWM0_SYNC_IN_PA15/*!< Set PA15 function to EPWM0_SYNC_IN   */
#define SET_EPWM0_SYNC_IN_PC14() SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EPWM0_SYNC_IN_PC14_Msk)) | EPWM0_SYNC_IN_PC14/*!< Set PC14 function to EPWM0_SYNC_IN   */
#define SET_EPWM0_SYNC_OUT_PA11() SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EPWM0_SYNC_OUT_PA11_Msk)) | EPWM0_SYNC_OUT_PA11/*!< Set PA11 function to EPWM0_SYNC_OUT  */
#define SET_EPWM0_SYNC_OUT_PF5() SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EPWM0_SYNC_OUT_PF5_Msk)) | EPWM0_SYNC_OUT_PF5/*!< Set PF5 function to EPWM0_SYNC_OUT   */
#define SET_EPWM1_BRAKE0_PB7()   SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM1_BRAKE0_PB7_Msk)) | EPWM1_BRAKE0_PB7    /*!< Set PB7 function to EPWM1_BRAKE0     */
#define SET_EPWM1_BRAKE0_PE10()  SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM1_BRAKE0_PE10_Msk)) | EPWM1_BRAKE0_PE10  /*!< Set PE10 function to EPWM1_BRAKE0    */
#define SET_EPWM1_BRAKE1_PA3()   SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EPWM1_BRAKE1_PA3_Msk)) | EPWM1_BRAKE1_PA3    /*!< Set PA3 function to EPWM1_BRAKE1     */
#define SET_EPWM1_BRAKE1_PE11()  SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EPWM1_BRAKE1_PE11_Msk)) | EPWM1_BRAKE1_PE11  /*!< Set PE11 function to EPWM1_BRAKE1    */
#define SET_EPWM1_BRAKE1_PB6()   SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM1_BRAKE1_PB6_Msk)) | EPWM1_BRAKE1_PB6    /*!< Set PB6 function to EPWM1_BRAKE1     */
#define SET_EPWM1_CH0_PC5()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EPWM1_CH0_PC5_Msk)) | EPWM1_CH0_PC5          /*!< Set PC5 function to EPWM1_CH0        */
#define SET_EPWM1_CH0_PI12()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~EPWM1_CH0_PI12_Msk)) | EPWM1_CH0_PI12        /*!< Set PI12 function to EPWM1_CH0       */
#define SET_EPWM1_CH0_PB15()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EPWM1_CH0_PB15_Msk)) | EPWM1_CH0_PB15        /*!< Set PB15 function to EPWM1_CH0       */
#define SET_EPWM1_CH0_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~EPWM1_CH0_PE13_Msk)) | EPWM1_CH0_PE13        /*!< Set PE13 function to EPWM1_CH0       */
#define SET_EPWM1_CH0_PC12()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~EPWM1_CH0_PC12_Msk)) | EPWM1_CH0_PC12        /*!< Set PC12 function to EPWM1_CH0       */
#define SET_EPWM1_CH1_PB14()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EPWM1_CH1_PB14_Msk)) | EPWM1_CH1_PB14        /*!< Set PB14 function to EPWM1_CH1       */
#define SET_EPWM1_CH1_PC8()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EPWM1_CH1_PC8_Msk)) | EPWM1_CH1_PC8          /*!< Set PC8 function to EPWM1_CH1        */
#define SET_EPWM1_CH1_PI13()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~EPWM1_CH1_PI13_Msk)) | EPWM1_CH1_PI13        /*!< Set PI13 function to EPWM1_CH1       */
#define SET_EPWM1_CH1_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EPWM1_CH1_PC4_Msk)) | EPWM1_CH1_PC4          /*!< Set PC4 function to EPWM1_CH1        */
#define SET_EPWM1_CH1_PC11()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EPWM1_CH1_PC11_Msk)) | EPWM1_CH1_PC11        /*!< Set PC11 function to EPWM1_CH1       */
#define SET_EPWM1_CH2_PC10()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EPWM1_CH2_PC10_Msk)) | EPWM1_CH2_PC10        /*!< Set PC10 function to EPWM1_CH2       */
#define SET_EPWM1_CH2_PB13()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EPWM1_CH2_PB13_Msk)) | EPWM1_CH2_PB13        /*!< Set PB13 function to EPWM1_CH2       */
#define SET_EPWM1_CH2_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EPWM1_CH2_PC7_Msk)) | EPWM1_CH2_PC7          /*!< Set PC7 function to EPWM1_CH2        */
#define SET_EPWM1_CH2_PI14()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~EPWM1_CH2_PI14_Msk)) | EPWM1_CH2_PI14        /*!< Set PI14 function to EPWM1_CH2       */
#define SET_EPWM1_CH2_PC3()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EPWM1_CH2_PC3_Msk)) | EPWM1_CH2_PC3          /*!< Set PC3 function to EPWM1_CH2        */
#define SET_EPWM1_CH3_PC9()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~EPWM1_CH3_PC9_Msk)) | EPWM1_CH3_PC9          /*!< Set PC9 function to EPWM1_CH3        */
#define SET_EPWM1_CH3_PC2()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EPWM1_CH3_PC2_Msk)) | EPWM1_CH3_PC2          /*!< Set PC2 function to EPWM1_CH3        */
#define SET_EPWM1_CH3_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~EPWM1_CH3_PC6_Msk)) | EPWM1_CH3_PC6          /*!< Set PC6 function to EPWM1_CH3        */
#define SET_EPWM1_CH3_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~EPWM1_CH3_PB12_Msk)) | EPWM1_CH3_PB12        /*!< Set PB12 function to EPWM1_CH3       */
#define SET_EPWM1_CH3_PI15()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~EPWM1_CH3_PI15_Msk)) | EPWM1_CH3_PI15        /*!< Set PI15 function to EPWM1_CH3       */
#define SET_EPWM1_CH4_PB7()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM1_CH4_PB7_Msk)) | EPWM1_CH4_PB7          /*!< Set PB7 function to EPWM1_CH4        */
#define SET_EPWM1_CH4_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM1_CH4_PB1_Msk)) | EPWM1_CH4_PB1          /*!< Set PB1 function to EPWM1_CH4        */
#define SET_EPWM1_CH4_PJ0()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~EPWM1_CH4_PJ0_Msk)) | EPWM1_CH4_PJ0          /*!< Set PJ0 function to EPWM1_CH4        */
#define SET_EPWM1_CH4_PF0()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EPWM1_CH4_PF0_Msk)) | EPWM1_CH4_PF0          /*!< Set PF0 function to EPWM1_CH4        */
#define SET_EPWM1_CH4_PA7()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EPWM1_CH4_PA7_Msk)) | EPWM1_CH4_PA7          /*!< Set PA7 function to EPWM1_CH4        */
#define SET_EPWM1_CH4_PC1()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EPWM1_CH4_PC1_Msk)) | EPWM1_CH4_PC1          /*!< Set PC1 function to EPWM1_CH4        */
#define SET_EPWM1_CH5_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~EPWM1_CH5_PF1_Msk)) | EPWM1_CH5_PF1          /*!< Set PF1 function to EPWM1_CH5        */
#define SET_EPWM1_CH5_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~EPWM1_CH5_PB0_Msk)) | EPWM1_CH5_PB0          /*!< Set PB0 function to EPWM1_CH5        */
#define SET_EPWM1_CH5_PA6()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EPWM1_CH5_PA6_Msk)) | EPWM1_CH5_PA6          /*!< Set PA6 function to EPWM1_CH5        */
#define SET_EPWM1_CH5_PJ1()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~EPWM1_CH5_PJ1_Msk)) | EPWM1_CH5_PJ1          /*!< Set PJ1 function to EPWM1_CH5        */
#define SET_EPWM1_CH5_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~EPWM1_CH5_PC0_Msk)) | EPWM1_CH5_PC0          /*!< Set PC0 function to EPWM1_CH5        */
#define SET_EPWM1_CH5_PB6()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~EPWM1_CH5_PB6_Msk)) | EPWM1_CH5_PB6          /*!< Set PB6 function to EPWM1_CH5        */
#define SET_ETMC_TRACE_CLK_PC14()   SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~ETMC_TRACE_CLK_PC14_Msk)) | ETMC_TRACE_CLK_PC14     /*!< Set PC14 function to ETMC_TRACE_CLK   */
#define SET_ETMC_TRACE_DATA0_PB15() SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ETMC_TRACE_DATA0_PB15_Msk)) | ETMC_TRACE_DATA0_PB15 /*!< Set PB15 function to ETMC_TRACE_DATA0 */
#define SET_ETMC_TRACE_DATA1_PB14() SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ETMC_TRACE_DATA1_PB14_Msk)) | ETMC_TRACE_DATA1_PB14 /*!< Set PB14 function to ETMC_TRACE_DATA1 */
#define SET_ETMC_TRACE_DATA2_PB13() SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ETMC_TRACE_DATA2_PB13_Msk)) | ETMC_TRACE_DATA2_PB13 /*!< Set PB13 function to ETMC_TRACE_DATA2 */
#define SET_ETMC_TRACE_DATA3_PB12() SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~ETMC_TRACE_DATA3_PB12_Msk)) | ETMC_TRACE_DATA3_PB12 /*!< Set PB12 function to ETMC_TRACE_DATA3 */
#define SET_HBI_CK_PC4()         SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~HBI_CK_PC4_Msk)) | HBI_CK_PC4                /*!< Set PC4 function to HBI_CK           */
#define SET_HBI_CK_PH13()        SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~HBI_CK_PH13_Msk)) | HBI_CK_PH13              /*!< Set PH13 function to HBI_CK          */
#define SET_HBI_D0_PJ6()         SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~HBI_D0_PJ6_Msk)) | HBI_D0_PJ6                /*!< Set PJ6 function to HBI_D0           */
#define SET_HBI_D0_PG11()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~HBI_D0_PG11_Msk)) | HBI_D0_PG11              /*!< Set PG11 function to HBI_D0          */
#define SET_HBI_D1_PG12()        SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~HBI_D1_PG12_Msk)) | HBI_D1_PG12              /*!< Set PG12 function to HBI_D1          */
#define SET_HBI_D1_PJ5()         SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~HBI_D1_PJ5_Msk)) | HBI_D1_PJ5                /*!< Set PJ5 function to HBI_D1           */
#define SET_HBI_D2_PJ4()         SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~HBI_D2_PJ4_Msk)) | HBI_D2_PJ4                /*!< Set PJ4 function to HBI_D2           */
#define SET_HBI_D2_PC0()         SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~HBI_D2_PC0_Msk)) | HBI_D2_PC0                /*!< Set PC0 function to HBI_D2           */
#define SET_HBI_D3_PG10()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~HBI_D3_PG10_Msk)) | HBI_D3_PG10              /*!< Set PG10 function to HBI_D3          */
#define SET_HBI_D3_PJ3()         SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~HBI_D3_PJ3_Msk)) | HBI_D3_PJ3                /*!< Set PJ3 function to HBI_D3           */
#define SET_HBI_D4_PG9()         SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~HBI_D4_PG9_Msk)) | HBI_D4_PG9                /*!< Set PG9 function to HBI_D4           */
#define SET_HBI_D4_PH15()        SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~HBI_D4_PH15_Msk)) | HBI_D4_PH15              /*!< Set PH15 function to HBI_D4          */
#define SET_HBI_D5_PG13()        SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~HBI_D5_PG13_Msk)) | HBI_D5_PG13              /*!< Set PG13 function to HBI_D5          */
#define SET_HBI_D5_PD7()         SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~HBI_D5_PD7_Msk)) | HBI_D5_PD7                /*!< Set PD7 function to HBI_D5           */
#define SET_HBI_D6_PG14()        SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~HBI_D6_PG14_Msk)) | HBI_D6_PG14              /*!< Set PG14 function to HBI_D6          */
#define SET_HBI_D6_PD6()         SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~HBI_D6_PD6_Msk)) | HBI_D6_PD6                /*!< Set PD6 function to HBI_D6           */
#define SET_HBI_D7_PG15()        SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~HBI_D7_PG15_Msk)) | HBI_D7_PG15              /*!< Set PG15 function to HBI_D7          */
#define SET_HBI_D7_PD5()         SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~HBI_D7_PD5_Msk)) | HBI_D7_PD5                /*!< Set PD5 function to HBI_D7           */
#define SET_HBI_RWDS_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~HBI_RWDS_PC1_Msk)) | HBI_RWDS_PC1            /*!< Set PC1 function to HBI_RWDS         */
#define SET_HBI_RWDS_PH14()      SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~HBI_RWDS_PH14_Msk)) | HBI_RWDS_PH14          /*!< Set PH14 function to HBI_RWDS        */
#define SET_HBI_nCK_PH12()       SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~HBI_nCK_PH12_Msk)) | HBI_nCK_PH12            /*!< Set PH12 function to HBI_nCK         */
#define SET_HBI_nCK_PC5()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~HBI_nCK_PC5_Msk)) | HBI_nCK_PC5              /*!< Set PC5 function to HBI_nCK          */
#define SET_HBI_nCS_PC3()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~HBI_nCS_PC3_Msk)) | HBI_nCS_PC3              /*!< Set PC3 function to HBI_nCS          */
#define SET_HBI_nCS_PJ7()        SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~HBI_nCS_PJ7_Msk)) | HBI_nCS_PJ7              /*!< Set PJ7 function to HBI_nCS          */
#define SET_HBI_nRESET_PJ2()     SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~HBI_nRESET_PJ2_Msk)) | HBI_nRESET_PJ2        /*!< Set PJ7 function to HBI_nRESET       */
#define SET_HBI_nRESET_PC2()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~HBI_nRESET_PC2_Msk)) | HBI_nRESET_PC2        /*!< Set PC2 function to HBI_nRESET       */
#define SET_HSUSB_VBUS_EN_PB10() SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~HSUSB_VBUS_EN_PB10_Msk)) | HSUSB_VBUS_EN_PB10/*!< Set PB10 function to HSUSB_VBUS_EN   */
#define SET_HSUSB_VBUS_EN_PB15() SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~HSUSB_VBUS_EN_PB15_Msk)) | HSUSB_VBUS_EN_PB15/*!< Set PB15 function to HSUSB_VBUS_EN   */
#define SET_HSUSB_VBUS_EN_PJ13() SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~HSUSB_VBUS_EN_PJ13_Msk)) | HSUSB_VBUS_EN_PJ13/*!< Set PJ13 function to HSUSB_VBUS_EN   */
#define SET_HSUSB_VBUS_ST_PB11() SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~HSUSB_VBUS_ST_PB11_Msk)) | HSUSB_VBUS_ST_PB11/*!< Set PB11 function to HSUSB_VBUS_ST   */
#define SET_HSUSB_VBUS_ST_PC14() SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~HSUSB_VBUS_ST_PC14_Msk)) | HSUSB_VBUS_ST_PC14/*!< Set PC14 function to HSUSB_VBUS_ST   */
#define SET_HSUSB_VBUS_ST_PJ12() SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~HSUSB_VBUS_ST_PJ12_Msk)) | HSUSB_VBUS_ST_PJ12/*!< Set PJ12 function to HSUSB_VBUS_ST   */
#define SET_I2C0_SCL_PB9()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C0_SCL_PB9_Msk)) | I2C0_SCL_PB9            /*!< Set PB9 function to I2C0_SCL         */
#define SET_I2C0_SCL_PF0()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C0_SCL_PF0_Msk)) | I2C0_SCL_PF0            /*!< Set PF0 function to I2C0_SCL         */
#define SET_I2C0_SCL_PD7()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~I2C0_SCL_PD7_Msk)) | I2C0_SCL_PD7            /*!< Set PD7 function to I2C0_SCL         */
#define SET_I2C0_SCL_PA5()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~I2C0_SCL_PA5_Msk)) | I2C0_SCL_PA5            /*!< Set PA5 function to I2C0_SCL         */
#define SET_I2C0_SCL_PH2()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~I2C0_SCL_PH2_Msk)) | I2C0_SCL_PH2            /*!< Set PH2 function to I2C0_SCL         */
#define SET_I2C0_SCL_PG0()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C0_SCL_PG0_Msk)) | I2C0_SCL_PG0            /*!< Set PG0 function to I2C0_SCL         */
#define SET_I2C0_SCL_PC12()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~I2C0_SCL_PC12_Msk)) | I2C0_SCL_PC12          /*!< Set PC12 function to I2C0_SCL        */
#define SET_I2C0_SCL_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C0_SCL_PC1_Msk)) | I2C0_SCL_PC1            /*!< Set PC1 function to I2C0_SCL         */
#define SET_I2C0_SCL_PB5()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~I2C0_SCL_PB5_Msk)) | I2C0_SCL_PB5            /*!< Set PB5 function to I2C0_SCL         */
#define SET_I2C0_SCL_PE13()      SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~I2C0_SCL_PE13_Msk)) | I2C0_SCL_PE13          /*!< Set PE13 function to I2C0_SCL        */
#define SET_I2C0_SCL_PF3()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C0_SCL_PF3_Msk)) | I2C0_SCL_PF3            /*!< Set PF3 function to I2C0_SCL         */
#define SET_I2C0_SCL_PI10()      SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2C0_SCL_PI10_Msk)) | I2C0_SCL_PI10          /*!< Set PI10 function to I2C0_SCL        */
#define SET_I2C0_SCL_PA14()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C0_SCL_PA14_Msk)) | I2C0_SCL_PA14          /*!< Set PA14 function to I2C0_SCL        */
#define SET_I2C0_SDA_PI11()      SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2C0_SDA_PI11_Msk)) | I2C0_SDA_PI11          /*!< Set PI11 function to I2C0_SDA        */
#define SET_I2C0_SDA_PF2()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C0_SDA_PF2_Msk)) | I2C0_SDA_PF2            /*!< Set PF2 function to I2C0_SDA         */
#define SET_I2C0_SDA_PB4()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~I2C0_SDA_PB4_Msk)) | I2C0_SDA_PB4            /*!< Set PB4 function to I2C0_SDA         */
#define SET_I2C0_SDA_PF1()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C0_SDA_PF1_Msk)) | I2C0_SDA_PF1            /*!< Set PF1 function to I2C0_SDA         */
#define SET_I2C0_SDA_PH3()       SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~I2C0_SDA_PH3_Msk)) | I2C0_SDA_PH3            /*!< Set PH3 function to I2C0_SDA         */
#define SET_I2C0_SDA_PG1()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C0_SDA_PG1_Msk)) | I2C0_SDA_PG1            /*!< Set PG1 function to I2C0_SDA         */
#define SET_I2C0_SDA_PA4()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~I2C0_SDA_PA4_Msk)) | I2C0_SDA_PA4            /*!< Set PA4 function to I2C0_SDA         */
#define SET_I2C0_SDA_PC11()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~I2C0_SDA_PC11_Msk)) | I2C0_SDA_PC11          /*!< Set PC11 function to I2C0_SDA        */
#define SET_I2C0_SDA_PD6()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~I2C0_SDA_PD6_Msk)) | I2C0_SDA_PD6            /*!< Set PD6 function to I2C0_SDA         */
#define SET_I2C0_SDA_PC0()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C0_SDA_PC0_Msk)) | I2C0_SDA_PC0            /*!< Set PC0 function to I2C0_SDA         */
#define SET_I2C0_SDA_PC8()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~I2C0_SDA_PC8_Msk)) | I2C0_SDA_PC8            /*!< Set PC8 function to I2C0_SDA         */
#define SET_I2C0_SDA_PB8()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C0_SDA_PB8_Msk)) | I2C0_SDA_PB8            /*!< Set PB8 function to I2C0_SDA         */
#define SET_I2C0_SDA_PA15()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C0_SDA_PA15_Msk)) | I2C0_SDA_PA15          /*!< Set PA15 function to I2C0_SDA        */
#define SET_I2C0_SMBAL_PC3()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C0_SMBAL_PC3_Msk)) | I2C0_SMBAL_PC3        /*!< Set PC3 function to I2C0_SMBAL       */
#define SET_I2C0_SMBAL_PG2()     SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C0_SMBAL_PG2_Msk)) | I2C0_SMBAL_PG2        /*!< Set PG2 function to I2C0_SMBAL       */
#define SET_I2C0_SMBAL_PA3()     SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C0_SMBAL_PA3_Msk)) | I2C0_SMBAL_PA3        /*!< Set PA3 function to I2C0_SMBAL       */
#define SET_I2C0_SMBAL_PI8()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2C0_SMBAL_PI8_Msk)) | I2C0_SMBAL_PI8        /*!< Set PI8 function to I2C0_SMBAL       */
#define SET_I2C0_SMBSUS_PI9()    SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2C0_SMBSUS_PI9_Msk)) | I2C0_SMBSUS_PI9      /*!< Set PI9 function to I2C0_SMBSUS      */
#define SET_I2C0_SMBSUS_PA2()    SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C0_SMBSUS_PA2_Msk)) | I2C0_SMBSUS_PA2      /*!< Set PA2 function to I2C0_SMBSUS      */
#define SET_I2C0_SMBSUS_PG3()    SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C0_SMBSUS_PG3_Msk)) | I2C0_SMBSUS_PG3      /*!< Set PG3 function to I2C0_SMBSUS      */
#define SET_I2C0_SMBSUS_PC2()    SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C0_SMBSUS_PC2_Msk)) | I2C0_SMBSUS_PC2      /*!< Set PC2 function to I2C0_SMBSUS      */
#define SET_I2C1_SCL_PF0()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C1_SCL_PF0_Msk)) | I2C1_SCL_PF0            /*!< Set PF0 function to I2C1_SCL         */
#define SET_I2C1_SCL_PD5()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~I2C1_SCL_PD5_Msk)) | I2C1_SCL_PD5            /*!< Set PD5 function to I2C1_SCL         */
#define SET_I2C1_SCL_PB1()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2C1_SCL_PB1_Msk)) | I2C1_SCL_PB1            /*!< Set PB1 function to I2C1_SCL         */
#define SET_I2C1_SCL_PI6()       SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~I2C1_SCL_PI6_Msk)) | I2C1_SCL_PI6            /*!< Set PI6 function to I2C1_SCL         */
#define SET_I2C1_SCL_PB3()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2C1_SCL_PB3_Msk)) | I2C1_SCL_PB3            /*!< Set PB3 function to I2C1_SCL         */
#define SET_I2C1_SCL_PA12()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C1_SCL_PA12_Msk)) | I2C1_SCL_PA12          /*!< Set PA12 function to I2C1_SCL        */
#define SET_I2C1_SCL_PE1()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~I2C1_SCL_PE1_Msk)) | I2C1_SCL_PE1            /*!< Set PE1 function to I2C1_SCL         */
#define SET_I2C1_SCL_PB11()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C1_SCL_PB11_Msk)) | I2C1_SCL_PB11          /*!< Set PB11 function to I2C1_SCL        */
#define SET_I2C1_SCL_PG2()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C1_SCL_PG2_Msk)) | I2C1_SCL_PG2            /*!< Set PG2 function to I2C1_SCL         */
#define SET_I2C1_SCL_PA7()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~I2C1_SCL_PA7_Msk)) | I2C1_SCL_PA7            /*!< Set PA7 function to I2C1_SCL         */
#define SET_I2C1_SCL_PC5()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C1_SCL_PC5_Msk)) | I2C1_SCL_PC5            /*!< Set PC5 function to I2C1_SCL         */
#define SET_I2C1_SCL_PA3()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C1_SCL_PA3_Msk)) | I2C1_SCL_PA3            /*!< Set PA3 function to I2C1_SCL         */
#define SET_I2C1_SDA_PB0()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2C1_SDA_PB0_Msk)) | I2C1_SDA_PB0            /*!< Set PB0 function to I2C1_SDA         */
#define SET_I2C1_SDA_PA2()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C1_SDA_PA2_Msk)) | I2C1_SDA_PA2            /*!< Set PA2 function to I2C1_SDA         */
#define SET_I2C1_SDA_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2C1_SDA_PB2_Msk)) | I2C1_SDA_PB2            /*!< Set PB2 function to I2C1_SDA         */
#define SET_I2C1_SDA_PC4()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C1_SDA_PC4_Msk)) | I2C1_SDA_PC4            /*!< Set PC4 function to I2C1_SDA         */
#define SET_I2C1_SDA_PI7()       SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~I2C1_SDA_PI7_Msk)) | I2C1_SDA_PI7            /*!< Set PI7 function to I2C1_SDA         */
#define SET_I2C1_SDA_PF1()       SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C1_SDA_PF1_Msk)) | I2C1_SDA_PF1            /*!< Set PF1 function to I2C1_SDA         */
#define SET_I2C1_SDA_PD4()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~I2C1_SDA_PD4_Msk)) | I2C1_SDA_PD4            /*!< Set PD4 function to I2C1_SDA         */
#define SET_I2C1_SDA_PA13()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C1_SDA_PA13_Msk)) | I2C1_SDA_PA13          /*!< Set PA13 function to I2C1_SDA        */
#define SET_I2C1_SDA_PB10()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C1_SDA_PB10_Msk)) | I2C1_SDA_PB10          /*!< Set PB10 function to I2C1_SDA        */
#define SET_I2C1_SDA_PA6()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~I2C1_SDA_PA6_Msk)) | I2C1_SDA_PA6            /*!< Set PA6 function to I2C1_SDA         */
#define SET_I2C1_SDA_PG3()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C1_SDA_PG3_Msk)) | I2C1_SDA_PG3            /*!< Set PG3 function to I2C1_SDA         */
#define SET_I2C1_SDA_PE0()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~I2C1_SDA_PE0_Msk)) | I2C1_SDA_PE0            /*!< Set PE0 function to I2C1_SDA         */
#define SET_I2C1_SMBAL_PG0()     SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C1_SMBAL_PG0_Msk)) | I2C1_SMBAL_PG0        /*!< Set PG0 function to I2C1_SMBAL       */
#define SET_I2C1_SMBAL_PC7()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C1_SMBAL_PC7_Msk)) | I2C1_SMBAL_PC7        /*!< Set PC7 function to I2C1_SMBAL       */
#define SET_I2C1_SMBAL_PB9()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C1_SMBAL_PB9_Msk)) | I2C1_SMBAL_PB9        /*!< Set PB9 function to I2C1_SMBAL       */
#define SET_I2C1_SMBAL_PH8()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2C1_SMBAL_PH8_Msk)) | I2C1_SMBAL_PH8        /*!< Set PH8 function to I2C1_SMBAL       */
#define SET_I2C1_SMBSUS_PH9()    SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2C1_SMBSUS_PH9_Msk)) | I2C1_SMBSUS_PH9      /*!< Set PH9 function to I2C1_SMBSUS      */
#define SET_I2C1_SMBSUS_PC6()    SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C1_SMBSUS_PC6_Msk)) | I2C1_SMBSUS_PC6      /*!< Set PC6 function to I2C1_SMBSUS      */
#define SET_I2C1_SMBSUS_PG1()    SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C1_SMBSUS_PG1_Msk)) | I2C1_SMBSUS_PG1      /*!< Set PG1 function to I2C1_SMBSUS      */
#define SET_I2C1_SMBSUS_PB8()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~I2C1_SMBSUS_PB8_Msk)) | I2C1_SMBSUS_PB8      /*!< Set PB8 function to I2C1_SMBSUS      */
#define SET_I2C2_SCL_PA1()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C2_SCL_PA1_Msk)) | I2C2_SCL_PA1            /*!< Set PA1 function to I2C2_SCL         */
#define SET_I2C2_SCL_PH8()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2C2_SCL_PH8_Msk)) | I2C2_SCL_PH8            /*!< Set PH8 function to I2C2_SCL         */
#define SET_I2C2_SCL_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~I2C2_SCL_PB13_Msk)) | I2C2_SCL_PB13          /*!< Set PB13 function to I2C2_SCL        */
#define SET_I2C2_SCL_PA11()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2C2_SCL_PA11_Msk)) | I2C2_SCL_PA11          /*!< Set PA11 function to I2C2_SCL        */
#define SET_I2C2_SCL_PA14()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C2_SCL_PA14_Msk)) | I2C2_SCL_PA14          /*!< Set PA14 function to I2C2_SCL        */
#define SET_I2C2_SCL_PD1()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2C2_SCL_PD1_Msk)) | I2C2_SCL_PD1            /*!< Set PD1 function to I2C2_SCL         */
#define SET_I2C2_SCL_PD9()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~I2C2_SCL_PD9_Msk)) | I2C2_SCL_PD9            /*!< Set PD9 function to I2C2_SCL         */
#define SET_I2C2_SDA_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~I2C2_SDA_PB12_Msk)) | I2C2_SDA_PB12          /*!< Set PB12 function to I2C2_SDA        */
#define SET_I2C2_SDA_PD8()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~I2C2_SDA_PD8_Msk)) | I2C2_SDA_PD8            /*!< Set PD8 function to I2C2_SDA         */
#define SET_I2C2_SDA_PA0()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~I2C2_SDA_PA0_Msk)) | I2C2_SDA_PA0            /*!< Set PA0 function to I2C2_SDA         */
#define SET_I2C2_SDA_PH9()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2C2_SDA_PH9_Msk)) | I2C2_SDA_PH9            /*!< Set PH9 function to I2C2_SDA         */
#define SET_I2C2_SDA_PA15()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2C2_SDA_PA15_Msk)) | I2C2_SDA_PA15          /*!< Set PA15 function to I2C2_SDA        */
#define SET_I2C2_SDA_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2C2_SDA_PA10_Msk)) | I2C2_SDA_PA10          /*!< Set PA10 function to I2C2_SDA        */
#define SET_I2C2_SDA_PD0()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2C2_SDA_PD0_Msk)) | I2C2_SDA_PD0            /*!< Set PD0 function to I2C2_SDA         */
#define SET_I2C2_SMBAL_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~I2C2_SMBAL_PB15_Msk)) | I2C2_SMBAL_PB15      /*!< Set PB15 function to I2C2_SMBAL      */
#define SET_I2C2_SMBSUS_PB14()   SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~I2C2_SMBSUS_PB14_Msk)) | I2C2_SMBSUS_PB14    /*!< Set PB14 function to I2C2_SMBSUS     */
#define SET_I2C3_SCL_PG7()       SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2C3_SCL_PG7_Msk)) | I2C3_SCL_PG7            /*!< Set PG7 function to I2C3_SCL         */
#define SET_I2C3_SCL_PG0()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C3_SCL_PG0_Msk)) | I2C3_SCL_PG0            /*!< Set PG0 function to I2C3_SCL         */
#define SET_I2C3_SCL_PC3()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C3_SCL_PC3_Msk)) | I2C3_SCL_PC3            /*!< Set PC3 function to I2C3_SCL         */
#define SET_I2C3_SCL_PI14()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~I2C3_SCL_PI14_Msk)) | I2C3_SCL_PI14          /*!< Set PI14 function to I2C3_SCL        */
#define SET_I2C3_SDA_PG8()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~I2C3_SDA_PG8_Msk)) | I2C3_SDA_PG8            /*!< Set PG8 function to I2C3_SDA         */
#define SET_I2C3_SDA_PI15()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~I2C3_SDA_PI15_Msk)) | I2C3_SDA_PI15          /*!< Set PI15 function to I2C3_SDA        */
#define SET_I2C3_SDA_PC2()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2C3_SDA_PC2_Msk)) | I2C3_SDA_PC2            /*!< Set PC2 function to I2C3_SDA         */
#define SET_I2C3_SDA_PG1()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C3_SDA_PG1_Msk)) | I2C3_SDA_PG1            /*!< Set PG1 function to I2C3_SDA         */
#define SET_I2C3_SMBAL_PG2()     SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C3_SMBAL_PG2_Msk)) | I2C3_SMBAL_PG2        /*!< Set PG2 function to I2C3_SMBAL       */
#define SET_I2C3_SMBAL_PI12()    SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~I2C3_SMBAL_PI12_Msk)) | I2C3_SMBAL_PI12      /*!< Set PI12 function to I2C3_SMBAL      */
#define SET_I2C3_SMBAL_PC5()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C3_SMBAL_PC5_Msk)) | I2C3_SMBAL_PC5        /*!< Set PC5 function to I2C3_SMBAL       */
#define SET_I2C3_SMBAL_PG5()     SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2C3_SMBAL_PG5_Msk)) | I2C3_SMBAL_PG5        /*!< Set PG5 function to I2C3_SMBAL       */
#define SET_I2C3_SMBSUS_PG6()    SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2C3_SMBSUS_PG6_Msk)) | I2C3_SMBSUS_PG6      /*!< Set PG6 function to I2C3_SMBSUS      */
#define SET_I2C3_SMBSUS_PC4()    SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2C3_SMBSUS_PC4_Msk)) | I2C3_SMBSUS_PC4      /*!< Set PC4 function to I2C3_SMBSUS      */
#define SET_I2C3_SMBSUS_PG3()    SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~I2C3_SMBSUS_PG3_Msk)) | I2C3_SMBSUS_PG3      /*!< Set PG3 function to I2C3_SMBSUS      */
#define SET_I2C3_SMBSUS_PI13()   SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~I2C3_SMBSUS_PI13_Msk)) | I2C3_SMBSUS_PI13    /*!< Set PI13 function to I2C3_SMBSUS     */
#define SET_I2C4_SCL_PJ10()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~I2C4_SCL_PJ10_Msk)) | I2C4_SCL_PJ10          /*!< Set PJ10 function to I2C4_SCL        */
#define SET_I2C4_SCL_PG9()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~I2C4_SCL_PG9_Msk)) | I2C4_SCL_PG9            /*!< Set PG9 function to I2C4_SCL         */
#define SET_I2C4_SCL_PC12()      SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~I2C4_SCL_PC12_Msk)) | I2C4_SCL_PC12          /*!< Set PC12 function to I2C4_SCL        */
#define SET_I2C4_SCL_PF5()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~I2C4_SCL_PF5_Msk)) | I2C4_SCL_PF5            /*!< Set PF5 function to I2C4_SCL         */
#define SET_I2C4_SDA_PJ11()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~I2C4_SDA_PJ11_Msk)) | I2C4_SDA_PJ11          /*!< Set PJ11 function to I2C4_SDA        */
#define SET_I2C4_SDA_PG10()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~I2C4_SDA_PG10_Msk)) | I2C4_SDA_PG10          /*!< Set PG10 function to I2C4_SDA        */
#define SET_I2C4_SDA_PC11()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~I2C4_SDA_PC11_Msk)) | I2C4_SDA_PC11          /*!< Set PC11 function to I2C4_SDA        */
#define SET_I2C4_SDA_PF4()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~I2C4_SDA_PF4_Msk)) | I2C4_SDA_PF4            /*!< Set PF4 function to I2C4_SDA         */
#define SET_I2C4_SMBAL_PJ12()    SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~I2C4_SMBAL_PJ12_Msk)) | I2C4_SMBAL_PJ12      /*!< Set PJ12 function to I2C4_SMBAL      */
#define SET_I2C4_SMBAL_PG11()    SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~I2C4_SMBAL_PG11_Msk)) | I2C4_SMBAL_PG11      /*!< Set PG11 function to I2C4_SMBAL      */
#define SET_I2C4_SMBAL_PF3()     SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C4_SMBAL_PF3_Msk)) | I2C4_SMBAL_PF3        /*!< Set PF3 function to I2C4_SMBAL       */
#define SET_I2C4_SMBAL_PC10()    SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~I2C4_SMBAL_PC10_Msk)) | I2C4_SMBAL_PC10      /*!< Set PC10 function to I2C4_SMBAL      */
#define SET_I2C4_SMBSUS_PJ13()   SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~I2C4_SMBSUS_PJ13_Msk)) | I2C4_SMBSUS_PJ13    /*!< Set PJ13 function to I2C4_SMBSUS     */
#define SET_I2C4_SMBSUS_PG12()   SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~I2C4_SMBSUS_PG12_Msk)) | I2C4_SMBSUS_PG12    /*!< Set PG12 function to I2C4_SMBSUS     */
#define SET_I2C4_SMBSUS_PC9()    SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~I2C4_SMBSUS_PC9_Msk)) | I2C4_SMBSUS_PC9      /*!< Set PC9 function to I2C4_SMBSUS      */
#define SET_I2C4_SMBSUS_PF2()    SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2C4_SMBSUS_PF2_Msk)) | I2C4_SMBSUS_PF2      /*!< Set PF2 function to I2C4_SMBSUS      */
#define SET_I2S0_BCLK_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~I2S0_BCLK_PE8_Msk)) | I2S0_BCLK_PE8          /*!< Set PE8 function to I2S0_BCLK        */
#define SET_I2S0_BCLK_PF10()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~I2S0_BCLK_PF10_Msk)) | I2S0_BCLK_PF10        /*!< Set PF10 function to I2S0_BCLK       */
#define SET_I2S0_BCLK_PE1()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~I2S0_BCLK_PE1_Msk)) | I2S0_BCLK_PE1          /*!< Set PE1 function to I2S0_BCLK        */
#define SET_I2S0_BCLK_PA12()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2S0_BCLK_PA12_Msk)) | I2S0_BCLK_PA12        /*!< Set PA12 function to I2S0_BCLK       */
#define SET_I2S0_BCLK_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~I2S0_BCLK_PB5_Msk)) | I2S0_BCLK_PB5          /*!< Set PB5 function to I2S0_BCLK        */
#define SET_I2S0_BCLK_PI6()      SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~I2S0_BCLK_PI6_Msk)) | I2S0_BCLK_PI6          /*!< Set PI6 function to I2S0_BCLK        */
#define SET_I2S0_BCLK_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~I2S0_BCLK_PC4_Msk)) | I2S0_BCLK_PC4          /*!< Set PC4 function to I2S0_BCLK        */
#define SET_I2S0_DI_PB3()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2S0_DI_PB3_Msk)) | I2S0_DI_PB3              /*!< Set PB3 function to I2S0_DI          */
#define SET_I2S0_DI_PC2()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2S0_DI_PC2_Msk)) | I2S0_DI_PC2              /*!< Set PC2 function to I2S0_DI          */
#define SET_I2S0_DI_PI8()        SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2S0_DI_PI8_Msk)) | I2S0_DI_PI8              /*!< Set PI8 function to I2S0_DI          */
#define SET_I2S0_DI_PA14()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2S0_DI_PA14_Msk)) | I2S0_DI_PA14            /*!< Set PA14 function to I2S0_DI         */
#define SET_I2S0_DI_PF8()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~I2S0_DI_PF8_Msk)) | I2S0_DI_PF8              /*!< Set PF8 function to I2S0_DI          */
#define SET_I2S0_DI_PH8()        SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2S0_DI_PH8_Msk)) | I2S0_DI_PH8              /*!< Set PH8 function to I2S0_DI          */
#define SET_I2S0_DI_PE10()       SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~I2S0_DI_PE10_Msk)) | I2S0_DI_PE10            /*!< Set PE10 function to I2S0_DI         */
#define SET_I2S0_DO_PH9()        SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2S0_DO_PH9_Msk)) | I2S0_DO_PH9              /*!< Set PH9 function to I2S0_DO          */
#define SET_I2S0_DO_PC1()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2S0_DO_PC1_Msk)) | I2S0_DO_PC1              /*!< Set PC1 function to I2S0_DO          */
#define SET_I2S0_DO_PA15()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2S0_DO_PA15_Msk)) | I2S0_DO_PA15            /*!< Set PA15 function to I2S0_DO         */
#define SET_I2S0_DO_PB2()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2S0_DO_PB2_Msk)) | I2S0_DO_PB2              /*!< Set PB2 function to I2S0_DO          */
#define SET_I2S0_DO_PF7()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~I2S0_DO_PF7_Msk)) | I2S0_DO_PF7              /*!< Set PF7 function to I2S0_DO          */
#define SET_I2S0_DO_PF0()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2S0_DO_PF0_Msk)) | I2S0_DO_PF0              /*!< Set PF0 function to I2S0_DO          */
#define SET_I2S0_DO_PE11()       SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~I2S0_DO_PE11_Msk)) | I2S0_DO_PE11            /*!< Set PE11 function to I2S0_DO         */
#define SET_I2S0_DO_PI9()        SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2S0_DO_PI9_Msk)) | I2S0_DO_PI9              /*!< Set PI9 function to I2S0_DO          */
#define SET_I2S0_LRCK_PF6()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~I2S0_LRCK_PF6_Msk)) | I2S0_LRCK_PF6          /*!< Set PF6 function to I2S0_LRCK        */
#define SET_I2S0_LRCK_PE12()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~I2S0_LRCK_PE12_Msk)) | I2S0_LRCK_PE12        /*!< Set PE12 function to I2S0_LRCK       */
#define SET_I2S0_LRCK_PH10()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~I2S0_LRCK_PH10_Msk)) | I2S0_LRCK_PH10        /*!< Set PH10 function to I2S0_LRCK       */
#define SET_I2S0_LRCK_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2S0_LRCK_PB1_Msk)) | I2S0_LRCK_PB1          /*!< Set PB1 function to I2S0_LRCK        */
#define SET_I2S0_LRCK_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~I2S0_LRCK_PF1_Msk)) | I2S0_LRCK_PF1          /*!< Set PF1 function to I2S0_LRCK        */
#define SET_I2S0_LRCK_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2S0_LRCK_PC0_Msk)) | I2S0_LRCK_PC0          /*!< Set PC0 function to I2S0_LRCK        */
#define SET_I2S0_LRCK_PI10()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~I2S0_LRCK_PI10_Msk)) | I2S0_LRCK_PI10        /*!< Set PI10 function to I2S0_LRCK       */
#define SET_I2S0_MCLK_PE0()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~I2S0_MCLK_PE0_Msk)) | I2S0_MCLK_PE0          /*!< Set PE0 function to I2S0_MCLK        */
#define SET_I2S0_MCLK_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~I2S0_MCLK_PB4_Msk)) | I2S0_MCLK_PB4          /*!< Set PB4 function to I2S0_MCLK        */
#define SET_I2S0_MCLK_PF9()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~I2S0_MCLK_PF9_Msk)) | I2S0_MCLK_PF9          /*!< Set PF9 function to I2S0_MCLK        */
#define SET_I2S0_MCLK_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~I2S0_MCLK_PE9_Msk)) | I2S0_MCLK_PE9          /*!< Set PE9 function to I2S0_MCLK        */
#define SET_I2S0_MCLK_PI7()      SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~I2S0_MCLK_PI7_Msk)) | I2S0_MCLK_PI7          /*!< Set PI7 function to I2S0_MCLK        */
#define SET_I2S0_MCLK_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~I2S0_MCLK_PA13_Msk)) | I2S0_MCLK_PA13        /*!< Set PA13 function to I2S0_MCLK       */
#define SET_I2S0_MCLK_PC3()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~I2S0_MCLK_PC3_Msk)) | I2S0_MCLK_PC3          /*!< Set PC3 function to I2S0_MCLK        */
#define SET_I2S1_BCLK_PD14()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~I2S1_BCLK_PD14_Msk)) | I2S1_BCLK_PD14        /*!< Set PD14 function to I2S1_BCLK       */
#define SET_I2S1_BCLK_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2S1_BCLK_PA11_Msk)) | I2S1_BCLK_PA11        /*!< Set PA11 function to I2S1_BCLK       */
#define SET_I2S1_BCLK_PD3()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2S1_BCLK_PD3_Msk)) | I2S1_BCLK_PD3          /*!< Set PD3 function to I2S1_BCLK        */
#define SET_I2S1_DI_PD1()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2S1_DI_PD1_Msk)) | I2S1_DI_PD1              /*!< Set PD1 function to I2S1_DI          */
#define SET_I2S1_DI_PA9()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2S1_DI_PA9_Msk)) | I2S1_DI_PA9              /*!< Set PA9 function to I2S1_DI          */
#define SET_I2S1_DI_PG6()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2S1_DI_PG6_Msk)) | I2S1_DI_PG6              /*!< Set PG6 function to I2S1_DI          */
#define SET_I2S1_DO_PD0()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2S1_DO_PD0_Msk)) | I2S1_DO_PD0              /*!< Set PD0 function to I2S1_DO          */
#define SET_I2S1_DO_PA8()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2S1_DO_PA8_Msk)) | I2S1_DO_PA8              /*!< Set PA8 function to I2S1_DO          */
#define SET_I2S1_DO_PG7()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2S1_DO_PG7_Msk)) | I2S1_DO_PG7              /*!< Set PG7 function to I2S1_DO          */
#define SET_I2S1_LRCK_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~I2S1_LRCK_PB0_Msk)) | I2S1_LRCK_PB0          /*!< Set PB0 function to I2S1_LRCK        */
#define SET_I2S1_LRCK_PD13()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~I2S1_LRCK_PD13_Msk)) | I2S1_LRCK_PD13        /*!< Set PD13 function to I2S1_LRCK       */
#define SET_I2S1_LRCK_PG8()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~I2S1_LRCK_PG8_Msk)) | I2S1_LRCK_PG8          /*!< Set PG8 function to I2S1_LRCK        */
#define SET_I2S1_MCLK_PD2()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~I2S1_MCLK_PD2_Msk)) | I2S1_MCLK_PD2          /*!< Set PD2 function to I2S1_MCLK        */
#define SET_I2S1_MCLK_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~I2S1_MCLK_PA10_Msk)) | I2S1_MCLK_PA10        /*!< Set PA10 function to I2S1_MCLK       */
#define SET_I2S1_MCLK_PG5()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~I2S1_MCLK_PG5_Msk)) | I2S1_MCLK_PG5          /*!< Set PG5 function to I2S1_MCLK        */
#define SET_ICE_CLK_PF1()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ICE_CLK_PF1_Msk)) | ICE_CLK_PF1              /*!< Set PF1 function to ICE_CLK          */
#define SET_ICE_DAT_PF0()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~ICE_DAT_PF0_Msk)) | ICE_DAT_PF0              /*!< Set PF0 function to ICE_DAT          */
#define SET_INT0_PA6()           SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~INT0_PA6_Msk)) | INT0_PA6                    /*!< Set PA6 function to INT0             */
#define SET_INT0_PB5()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~INT0_PB5_Msk)) | INT0_PB5                    /*!< Set PB5 function to INT0             */
#define SET_INT1_PA7()           SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~INT1_PA7_Msk)) | INT1_PA7                    /*!< Set PA7 function to INT1             */
#define SET_INT1_PB4()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~INT1_PB4_Msk)) | INT1_PB4                    /*!< Set PB4 function to INT1             */
#define SET_INT2_PB3()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~INT2_PB3_Msk)) | INT2_PB3                    /*!< Set PB3 function to INT2             */
#define SET_INT2_PC6()           SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~INT2_PC6_Msk)) | INT2_PC6                    /*!< Set PC6 function to INT2             */
#define SET_INT3_PC7()           SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~INT3_PC7_Msk)) | INT3_PC7                    /*!< Set PC7 function to INT3             */
#define SET_INT3_PB2()           SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~INT3_PB2_Msk)) | INT3_PB2                    /*!< Set PB2 function to INT3             */
#define SET_INT4_PA8()           SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~INT4_PA8_Msk)) | INT4_PA8                    /*!< Set PA8 function to INT4             */
#define SET_INT4_PB6()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~INT4_PB6_Msk)) | INT4_PB6                    /*!< Set PB6 function to INT4             */
#define SET_INT5_PD12()          SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~INT5_PD12_Msk)) | INT5_PD12                  /*!< Set PD12 function to INT5            */
#define SET_INT5_PB7()           SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~INT5_PB7_Msk)) | INT5_PB7                    /*!< Set PB7 function to INT5             */
#define SET_INT6_PB8()           SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~INT6_PB8_Msk)) | INT6_PB8                    /*!< Set PB8 function to INT6             */
#define SET_INT6_PD11()          SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~INT6_PD11_Msk)) | INT6_PD11                  /*!< Set PD11 function to INT6            */
#define SET_INT7_PB9()           SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~INT7_PB9_Msk)) | INT7_PB9                    /*!< Set PB9 function to INT7             */
#define SET_INT7_PD10()          SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~INT7_PD10_Msk)) | INT7_PD10                  /*!< Set PD10 function to INT7            */
#define SET_TRACE_SWO_PF6()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~TRACE_SWO_PF6_Msk)) | TRACE_SWO_PF6          /*!< Set PF6 function to TRACE_SWO        */
#define SET_TRACE_SWO_PC14()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~TRACE_SWO_PC14_Msk)) | TRACE_SWO_PC14        /*!< Set PC14 function to TRACE_SWO       */
#define SET_TRACE_SWO_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~TRACE_SWO_PE13_Msk)) | TRACE_SWO_PE13        /*!< Set PE13 function to TRACE_SWO       */
#define SET_KPI_COL0_PA6()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~KPI_COL0_PA6_Msk)) | KPI_COL0_PA6            /*!< Set PA6 function to KPI_COL0         */
#define SET_KPI_COL0_PB15()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~KPI_COL0_PB15_Msk)) | KPI_COL0_PB15          /*!< Set PB15 function to KPI_COL0        */
#define SET_KPI_COL1_PA7()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~KPI_COL1_PA7_Msk)) | KPI_COL1_PA7            /*!< Set PA7 function to KPI_COL1         */
#define SET_KPI_COL1_PB14()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~KPI_COL1_PB14_Msk)) | KPI_COL1_PB14          /*!< Set PB14 function to KPI_COL1        */
#define SET_KPI_COL2_PC6()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~KPI_COL2_PC6_Msk)) | KPI_COL2_PC6            /*!< Set PC6 function to KPI_COL2         */
#define SET_KPI_COL2_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~KPI_COL2_PB13_Msk)) | KPI_COL2_PB13          /*!< Set PB13 function to KPI_COL2        */
#define SET_KPI_COL3_PC7()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~KPI_COL3_PC7_Msk)) | KPI_COL3_PC7            /*!< Set PC7 function to KPI_COL3         */
#define SET_KPI_COL3_PB12()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~KPI_COL3_PB12_Msk)) | KPI_COL3_PB12          /*!< Set PB12 function to KPI_COL3        */
#define SET_KPI_COL4_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~KPI_COL4_PB7_Msk)) | KPI_COL4_PB7            /*!< Set PB7 function to KPI_COL4         */
#define SET_KPI_COL4_PC8()       SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~KPI_COL4_PC8_Msk)) | KPI_COL4_PC8            /*!< Set PC8 function to KPI_COL4         */
#define SET_KPI_COL5_PB6()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~KPI_COL5_PB6_Msk)) | KPI_COL5_PB6            /*!< Set PB6 function to KPI_COL5         */
#define SET_KPI_COL5_PE13()      SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~KPI_COL5_PE13_Msk)) | KPI_COL5_PE13          /*!< Set PE13 function to KPI_COL5        */
#define SET_KPI_COL6_PE12()      SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~KPI_COL6_PE12_Msk)) | KPI_COL6_PE12          /*!< Set PE12 function to KPI_COL6        */
#define SET_KPI_COL6_PB5()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~KPI_COL6_PB5_Msk)) | KPI_COL6_PB5            /*!< Set PB5 function to KPI_COL6         */
#define SET_KPI_COL7_PE11()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~KPI_COL7_PE11_Msk)) | KPI_COL7_PE11          /*!< Set PE11 function to KPI_COL7        */
#define SET_KPI_COL7_PB4()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~KPI_COL7_PB4_Msk)) | KPI_COL7_PB4            /*!< Set PB4 function to KPI_COL7         */
#define SET_KPI_ROW0_PC5()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~KPI_ROW0_PC5_Msk)) | KPI_ROW0_PC5            /*!< Set PC5 function to KPI_ROW0         */
#define SET_KPI_ROW0_PB3()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~KPI_ROW0_PB3_Msk)) | KPI_ROW0_PB3            /*!< Set PB3 function to KPI_ROW0         */
#define SET_KPI_ROW1_PC4()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~KPI_ROW1_PC4_Msk)) | KPI_ROW1_PC4            /*!< Set PC4 function to KPI_ROW1         */
#define SET_KPI_ROW1_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~KPI_ROW1_PB2_Msk)) | KPI_ROW1_PB2            /*!< Set PB2 function to KPI_ROW1         */
#define SET_KPI_ROW2_PB1()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~KPI_ROW2_PB1_Msk)) | KPI_ROW2_PB1            /*!< Set PB1 function to KPI_ROW2         */
#define SET_KPI_ROW2_PC3()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~KPI_ROW2_PC3_Msk)) | KPI_ROW2_PC3            /*!< Set PC3 function to KPI_ROW2         */
#define SET_KPI_ROW3_PC2()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~KPI_ROW3_PC2_Msk)) | KPI_ROW3_PC2            /*!< Set PC2 function to KPI_ROW3         */
#define SET_KPI_ROW3_PB0()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~KPI_ROW3_PB0_Msk)) | KPI_ROW3_PB0            /*!< Set PB0 function to KPI_ROW3         */
#define SET_KPI_ROW4_PA11()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~KPI_ROW4_PA11_Msk)) | KPI_ROW4_PA11          /*!< Set PA11 function to KPI_ROW4        */
#define SET_KPI_ROW4_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~KPI_ROW4_PC1_Msk)) | KPI_ROW4_PC1            /*!< Set PC1 function to KPI_ROW4         */
#define SET_KPI_ROW5_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~KPI_ROW5_PA10_Msk)) | KPI_ROW5_PA10          /*!< Set PA10 function to KPI_ROW5        */
#define SET_KPI_ROW5_PC0()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~KPI_ROW5_PC0_Msk)) | KPI_ROW5_PC0            /*!< Set PC0 function to KPI_ROW5         */
#define SET_PSIO0_CH0_PC5()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~PSIO0_CH0_PC5_Msk)) | PSIO0_CH0_PC5          /*!< Set PC5 function to PSIO0_CH0        */
#define SET_PSIO0_CH0_PB15()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~PSIO0_CH0_PB15_Msk)) | PSIO0_CH0_PB15        /*!< Set PB15 function to PSIO0_CH0       */
#define SET_PSIO0_CH0_PE7()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~PSIO0_CH0_PE7_Msk)) | PSIO0_CH0_PE7          /*!< Set PE7 function to PSIO0_CH0        */
#define SET_PSIO0_CH0_PE14()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~PSIO0_CH0_PE14_Msk)) | PSIO0_CH0_PE14        /*!< Set PE14 function to PSIO0_CH0       */
#define SET_PSIO0_CH1_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~PSIO0_CH1_PC4_Msk)) | PSIO0_CH1_PC4          /*!< Set PC4 function to PSIO0_CH1        */
#define SET_PSIO0_CH1_PE15()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~PSIO0_CH1_PE15_Msk)) | PSIO0_CH1_PE15        /*!< Set PE15 function to PSIO0_CH1       */
#define SET_PSIO0_CH1_PE6()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~PSIO0_CH1_PE6_Msk)) | PSIO0_CH1_PE6          /*!< Set PE6 function to PSIO0_CH1        */
#define SET_PSIO0_CH1_PB14()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~PSIO0_CH1_PB14_Msk)) | PSIO0_CH1_PB14        /*!< Set PB14 function to PSIO0_CH1       */
#define SET_PSIO0_CH2_PC3()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~PSIO0_CH2_PC3_Msk)) | PSIO0_CH2_PC3          /*!< Set PC3 function to PSIO0_CH2        */
#define SET_PSIO0_CH2_PD9()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~PSIO0_CH2_PD9_Msk)) | PSIO0_CH2_PD9          /*!< Set PD9 function to PSIO0_CH2        */
#define SET_PSIO0_CH2_PE5()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~PSIO0_CH2_PE5_Msk)) | PSIO0_CH2_PE5          /*!< Set PE5 function to PSIO0_CH2        */
#define SET_PSIO0_CH2_PB13()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~PSIO0_CH2_PB13_Msk)) | PSIO0_CH2_PB13        /*!< Set PB13 function to PSIO0_CH2       */
#define SET_PSIO0_CH3_PD8()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~PSIO0_CH3_PD8_Msk)) | PSIO0_CH3_PD8          /*!< Set PD8 function to PSIO0_CH3        */
#define SET_PSIO0_CH3_PC2()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~PSIO0_CH3_PC2_Msk)) | PSIO0_CH3_PC2          /*!< Set PC2 function to PSIO0_CH3        */
#define SET_PSIO0_CH3_PE4()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~PSIO0_CH3_PE4_Msk)) | PSIO0_CH3_PE4          /*!< Set PE4 function to PSIO0_CH3        */
#define SET_PSIO0_CH3_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~PSIO0_CH3_PB12_Msk)) | PSIO0_CH3_PB12        /*!< Set PB12 function to PSIO0_CH3       */
#define SET_PSIO0_CH4_PD7()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~PSIO0_CH4_PD7_Msk)) | PSIO0_CH4_PD7          /*!< Set PD7 function to PSIO0_CH4        */
#define SET_PSIO0_CH4_PA12()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~PSIO0_CH4_PA12_Msk)) | PSIO0_CH4_PA12        /*!< Set PA12 function to PSIO0_CH4       */
#define SET_PSIO0_CH4_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~PSIO0_CH4_PB5_Msk)) | PSIO0_CH4_PB5          /*!< Set PB5 function to PSIO0_CH4        */
#define SET_PSIO0_CH4_PA3()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~PSIO0_CH4_PA3_Msk)) | PSIO0_CH4_PA3          /*!< Set PA3 function to PSIO0_CH4        */
#define SET_PSIO0_CH5_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~PSIO0_CH5_PA13_Msk)) | PSIO0_CH5_PA13        /*!< Set PA13 function to PSIO0_CH5       */
#define SET_PSIO0_CH5_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~PSIO0_CH5_PB4_Msk)) | PSIO0_CH5_PB4          /*!< Set PB4 function to PSIO0_CH5        */
#define SET_PSIO0_CH5_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~PSIO0_CH5_PA2_Msk)) | PSIO0_CH5_PA2          /*!< Set PA2 function to PSIO0_CH5        */
#define SET_PSIO0_CH5_PD6()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~PSIO0_CH5_PD6_Msk)) | PSIO0_CH5_PD6          /*!< Set PD6 function to PSIO0_CH5        */
#define SET_PSIO0_CH6_PB3()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~PSIO0_CH6_PB3_Msk)) | PSIO0_CH6_PB3          /*!< Set PB3 function to PSIO0_CH6        */
#define SET_PSIO0_CH6_PD5()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~PSIO0_CH6_PD5_Msk)) | PSIO0_CH6_PD5          /*!< Set PD5 function to PSIO0_CH6        */
#define SET_PSIO0_CH6_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~PSIO0_CH6_PA1_Msk)) | PSIO0_CH6_PA1          /*!< Set PA1 function to PSIO0_CH6        */
#define SET_PSIO0_CH6_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~PSIO0_CH6_PA14_Msk)) | PSIO0_CH6_PA14        /*!< Set PA14 function to PSIO0_CH6       */
#define SET_PSIO0_CH7_PD4()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~PSIO0_CH7_PD4_Msk)) | PSIO0_CH7_PD4          /*!< Set PD4 function to PSIO0_CH7        */
#define SET_PSIO0_CH7_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~PSIO0_CH7_PA15_Msk)) | PSIO0_CH7_PA15        /*!< Set PA15 function to PSIO0_CH7       */
#define SET_PSIO0_CH7_PB2()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~PSIO0_CH7_PB2_Msk)) | PSIO0_CH7_PB2          /*!< Set PB2 function to PSIO0_CH7        */
#define SET_PSIO0_CH7_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~PSIO0_CH7_PA0_Msk)) | PSIO0_CH7_PA0          /*!< Set PA0 function to PSIO0_CH7        */
#define SET_EQEI0_A_PE3()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EQEI0_A_PE3_Msk)) | EQEI0_A_PE3                /*!< Set PE3 function to EQEI0_A           */
#define SET_EQEI0_A_PA4()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EQEI0_A_PA4_Msk)) | EQEI0_A_PA4                /*!< Set PA4 function to EQEI0_A           */
#define SET_EQEI0_A_PD11()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EQEI0_A_PD11_Msk)) | EQEI0_A_PD11              /*!< Set PD11 function to EQEI0_A          */
#define SET_EQEI0_B_PA3()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EQEI0_B_PA3_Msk)) | EQEI0_B_PA3                /*!< Set PA3 function to EQEI0_B           */
#define SET_EQEI0_B_PD10()       SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~EQEI0_B_PD10_Msk)) | EQEI0_B_PD10              /*!< Set PD10 function to EQEI0_B          */
#define SET_EQEI0_B_PE2()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~EQEI0_B_PE2_Msk)) | EQEI0_B_PE2                /*!< Set PE2 function to EQEI0_B           */
#define SET_EQEI0_INDEX_PE4()    SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EQEI0_INDEX_PE4_Msk)) | EQEI0_INDEX_PE4        /*!< Set PE4 function to EQEI0_INDEX       */
#define SET_EQEI0_INDEX_PA5()    SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~EQEI0_INDEX_PA5_Msk)) | EQEI0_INDEX_PA5        /*!< Set PA5 function to EQEI0_INDEX       */
#define SET_EQEI0_INDEX_PD12()   SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EQEI0_INDEX_PD12_Msk)) | EQEI0_INDEX_PD12      /*!< Set PD12 function to EQEI0_INDEX      */
#define SET_EQEI1_A_PA9()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EQEI1_A_PA9_Msk)) | EQEI1_A_PA9                /*!< Set PA9 function to EQEI1_A           */
#define SET_EQEI1_A_PA13()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EQEI1_A_PA13_Msk)) | EQEI1_A_PA13              /*!< Set PA13 function to EQEI1_A          */
#define SET_EQEI1_A_PE6()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EQEI1_A_PE6_Msk)) | EQEI1_A_PE6                /*!< Set PE6 function to EQEI1_A           */
#define SET_EQEI1_B_PE5()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EQEI1_B_PE5_Msk)) | EQEI1_B_PE5                /*!< Set PE5 function to EQEI1_B           */
#define SET_EQEI1_B_PA8()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EQEI1_B_PA8_Msk)) | EQEI1_B_PA8                /*!< Set PA8 function to EQEI1_B           */
#define SET_EQEI1_B_PA14()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EQEI1_B_PA14_Msk)) | EQEI1_B_PA14              /*!< Set PA14 function to EQEI1_B          */
#define SET_EQEI1_INDEX_PA10()   SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~EQEI1_INDEX_PA10_Msk)) | EQEI1_INDEX_PA10      /*!< Set PA10 function to EQEI1_INDEX      */
#define SET_EQEI1_INDEX_PE7()    SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~EQEI1_INDEX_PE7_Msk)) | EQEI1_INDEX_PE7        /*!< Set PE7 function to EQEI1_INDEX       */
#define SET_EQEI1_INDEX_PA12()   SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EQEI1_INDEX_PA12_Msk)) | EQEI1_INDEX_PA12      /*!< Set PA12 function to EQEI1_INDEX      */
#define SET_EQEI2_A_PE9()        SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EQEI2_A_PE9_Msk)) | EQEI2_A_PE9                /*!< Set PE9 function to EQEI2_A           */
#define SET_EQEI2_A_PF5()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EQEI2_A_PF5_Msk)) | EQEI2_A_PF5                /*!< Set PF5 function to EQEI2_A           */
#define SET_EQEI2_A_PD0()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EQEI2_A_PD0_Msk)) | EQEI2_A_PD0                /*!< Set PD0 function to EQEI2_A           */
#define SET_EQEI2_B_PF4()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EQEI2_B_PF4_Msk)) | EQEI2_B_PF4                /*!< Set PF4 function to EQEI2_B           */
#define SET_EQEI2_B_PE10()       SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EQEI2_B_PE10_Msk)) | EQEI2_B_PE10              /*!< Set PE10 function to EQEI2_B          */
#define SET_EQEI2_B_PD13()       SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~EQEI2_B_PD13_Msk)) | EQEI2_B_PD13              /*!< Set PD13 function to EQEI2_B          */
#define SET_EQEI2_INDEX_PE8()    SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~EQEI2_INDEX_PE8_Msk)) | EQEI2_INDEX_PE8        /*!< Set PE8 function to EQEI2_INDEX       */
#define SET_EQEI2_INDEX_PD1()    SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EQEI2_INDEX_PD1_Msk)) | EQEI2_INDEX_PD1        /*!< Set PD1 function to EQEI2_INDEX       */
#define SET_EQEI2_INDEX_PF6()    SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~EQEI2_INDEX_PF6_Msk)) | EQEI2_INDEX_PF6        /*!< Set PF6 function to EQEI2_INDEX       */
#define SET_EQEI3_A_PD3()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EQEI3_A_PD3_Msk)) | EQEI3_A_PD3                /*!< Set PD3 function to EQEI3_A           */
#define SET_EQEI3_A_PA1()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EQEI3_A_PA1_Msk)) | EQEI3_A_PA1                /*!< Set PA1 function to EQEI3_A           */
#define SET_EQEI3_B_PA0()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EQEI3_B_PA0_Msk)) | EQEI3_B_PA0                /*!< Set PA0 function to EQEI3_B           */
#define SET_EQEI3_B_PD2()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~EQEI3_B_PD2_Msk)) | EQEI3_B_PD2                /*!< Set PD2 function to EQEI3_B           */
#define SET_EQEI3_INDEX_PA2()    SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~EQEI3_INDEX_PA2_Msk)) | EQEI3_INDEX_PA2        /*!< Set PA2 function to EQEI3_INDEX       */
#define SET_EQEI3_INDEX_PA15()   SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~EQEI3_INDEX_PA15_Msk)) | EQEI3_INDEX_PA15      /*!< Set PA15 function to EQEI3_INDEX      */
#define SET_QSPI0_CLK_PH8()      SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~QSPI0_CLK_PH8_Msk)) | QSPI0_CLK_PH8          /*!< Set PH8 function to QSPI0_CLK        */
#define SET_QSPI0_CLK_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~QSPI0_CLK_PA2_Msk)) | QSPI0_CLK_PA2          /*!< Set PA2 function to QSPI0_CLK        */
#define SET_QSPI0_CLK_PI15()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~QSPI0_CLK_PI15_Msk)) | QSPI0_CLK_PI15        /*!< Set PI15 function to QSPI0_CLK       */
#define SET_QSPI0_CLK_PC2()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI0_CLK_PC2_Msk)) | QSPI0_CLK_PC2          /*!< Set PC2 function to QSPI0_CLK        */
#define SET_QSPI0_CLK_PF2()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~QSPI0_CLK_PF2_Msk)) | QSPI0_CLK_PF2          /*!< Set PF2 function to QSPI0_CLK        */
#define SET_QSPI0_CLK_PC14()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~QSPI0_CLK_PC14_Msk)) | QSPI0_CLK_PC14        /*!< Set PC14 function to QSPI0_CLK       */
#define SET_QSPI0_MISO0_PC1()    SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI0_MISO0_PC1_Msk)) | QSPI0_MISO0_PC1      /*!< Set PC1 function to QSPI0_MISO0      */
#define SET_QSPI0_MISO0_PJ0()    SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~QSPI0_MISO0_PJ0_Msk)) | QSPI0_MISO0_PJ0      /*!< Set PJ0 function to QSPI0_MISO0      */
#define SET_QSPI0_MISO0_PE1()    SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~QSPI0_MISO0_PE1_Msk)) | QSPI0_MISO0_PE1      /*!< Set PE1 function to QSPI0_MISO0      */
#define SET_QSPI0_MISO0_PA1()    SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~QSPI0_MISO0_PA1_Msk)) | QSPI0_MISO0_PA1      /*!< Set PA1 function to QSPI0_MISO0      */
#define SET_QSPI0_MISO1_PB1()    SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~QSPI0_MISO1_PB1_Msk)) | QSPI0_MISO1_PB1      /*!< Set PB1 function to QSPI0_MISO1      */
#define SET_QSPI0_MISO1_PI12()   SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~QSPI0_MISO1_PI12_Msk)) | QSPI0_MISO1_PI12    /*!< Set PI12 function to QSPI0_MISO1     */
#define SET_QSPI0_MISO1_PC5()    SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~QSPI0_MISO1_PC5_Msk)) | QSPI0_MISO1_PC5      /*!< Set PC5 function to QSPI0_MISO1      */
#define SET_QSPI0_MISO1_PH10()   SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~QSPI0_MISO1_PH10_Msk)) | QSPI0_MISO1_PH10    /*!< Set PH10 function to QSPI0_MISO1     */
#define SET_QSPI0_MISO1_PA5()    SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~QSPI0_MISO1_PA5_Msk)) | QSPI0_MISO1_PA5      /*!< Set PA5 function to QSPI0_MISO1      */
#define SET_QSPI0_MOSI0_PE0()    SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~QSPI0_MOSI0_PE0_Msk)) | QSPI0_MOSI0_PE0      /*!< Set PE0 function to QSPI0_MOSI0      */
#define SET_QSPI0_MOSI0_PC0()    SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI0_MOSI0_PC0_Msk)) | QSPI0_MOSI0_PC0      /*!< Set PC0 function to QSPI0_MOSI0      */
#define SET_QSPI0_MOSI0_PA0()    SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~QSPI0_MOSI0_PA0_Msk)) | QSPI0_MOSI0_PA0      /*!< Set PA0 function to QSPI0_MOSI0      */
#define SET_QSPI0_MOSI0_PJ1()    SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~QSPI0_MOSI0_PJ1_Msk)) | QSPI0_MOSI0_PJ1      /*!< Set PJ1 function to QSPI0_MOSI0      */
#define SET_QSPI0_MOSI1_PA4()    SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~QSPI0_MOSI1_PA4_Msk)) | QSPI0_MOSI1_PA4      /*!< Set PA4 function to QSPI0_MOSI1      */
#define SET_QSPI0_MOSI1_PC4()    SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~QSPI0_MOSI1_PC4_Msk)) | QSPI0_MOSI1_PC4      /*!< Set PC4 function to QSPI0_MOSI1      */
#define SET_QSPI0_MOSI1_PH11()   SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~QSPI0_MOSI1_PH11_Msk)) | QSPI0_MOSI1_PH11    /*!< Set PH11 function to QSPI0_MOSI1     */
#define SET_QSPI0_MOSI1_PI13()   SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~QSPI0_MOSI1_PI13_Msk)) | QSPI0_MOSI1_PI13    /*!< Set PI13 function to QSPI0_MOSI1     */
#define SET_QSPI0_MOSI1_PB0()    SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~QSPI0_MOSI1_PB0_Msk)) | QSPI0_MOSI1_PB0      /*!< Set PB0 function to QSPI0_MOSI1      */
#define SET_QSPI0_SS_PI14()      SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~QSPI0_SS_PI14_Msk)) | QSPI0_SS_PI14          /*!< Set PI14 function to QSPI0_SS        */
#define SET_QSPI0_SS_PA3()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~QSPI0_SS_PA3_Msk)) | QSPI0_SS_PA3            /*!< Set PA3 function to QSPI0_SS         */
#define SET_QSPI0_SS_PC3()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI0_SS_PC3_Msk)) | QSPI0_SS_PC3            /*!< Set PC3 function to QSPI0_SS         */
#define SET_QSPI0_SS_PH9()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~QSPI0_SS_PH9_Msk)) | QSPI0_SS_PH9            /*!< Set PH9 function to QSPI0_SS         */
#define SET_QSPI1_CLK_PH15()     SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~QSPI1_CLK_PH15_Msk)) | QSPI1_CLK_PH15        /*!< Set PH15 function to QSPI1_CLK       */
#define SET_QSPI1_CLK_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~QSPI1_CLK_PC4_Msk)) | QSPI1_CLK_PC4          /*!< Set PC4 function to QSPI1_CLK        */
#define SET_QSPI1_CLK_PJ3()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~QSPI1_CLK_PJ3_Msk)) | QSPI1_CLK_PJ3          /*!< Set PJ3 function to QSPI1_CLK        */
#define SET_QSPI1_CLK_PG12()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~QSPI1_CLK_PG12_Msk)) | QSPI1_CLK_PG12        /*!< Set PG12 function to QSPI1_CLK       */
#define SET_QSPI1_CLK_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI1_CLK_PC0_Msk)) | QSPI1_CLK_PC0          /*!< Set PC0 function to QSPI1_CLK        */
#define SET_QSPI1_MISO0_PD7()    SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~QSPI1_MISO0_PD7_Msk)) | QSPI1_MISO0_PD7      /*!< Set PD7 function to QSPI1_MISO0      */
#define SET_QSPI1_MISO0_PA12()   SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~QSPI1_MISO0_PA12_Msk)) | QSPI1_MISO0_PA12    /*!< Set PA12 function to QSPI1_MISO0     */
#define SET_QSPI1_MISO0_PC3()    SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI1_MISO0_PC3_Msk)) | QSPI1_MISO0_PC3      /*!< Set PC3 function to QSPI1_MISO0      */
#define SET_QSPI1_MISO0_PJ4()    SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~QSPI1_MISO0_PJ4_Msk)) | QSPI1_MISO0_PJ4      /*!< Set PJ4 function to QSPI1_MISO0      */
#define SET_QSPI1_MISO0_PG13()   SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~QSPI1_MISO0_PG13_Msk)) | QSPI1_MISO0_PG13    /*!< Set PG13 function to QSPI1_MISO0     */
#define SET_QSPI1_MISO0_PF0()    SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~QSPI1_MISO0_PF0_Msk)) | QSPI1_MISO0_PF0      /*!< Set PF0 function to QSPI1_MISO0      */
#define SET_QSPI1_MISO1_PG9()    SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~QSPI1_MISO1_PG9_Msk)) | QSPI1_MISO1_PG9      /*!< Set PG9 function to QSPI1_MISO1      */
#define SET_QSPI1_MISO1_PA7()    SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~QSPI1_MISO1_PA7_Msk)) | QSPI1_MISO1_PA7      /*!< Set PA7 function to QSPI1_MISO1      */
#define SET_QSPI1_MISO1_PH12()   SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~QSPI1_MISO1_PH12_Msk)) | QSPI1_MISO1_PH12    /*!< Set PH12 function to QSPI1_MISO1     */
#define SET_QSPI1_MISO1_PG15()   SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~QSPI1_MISO1_PG15_Msk)) | QSPI1_MISO1_PG15    /*!< Set PG15 function to QSPI1_MISO1     */
#define SET_QSPI1_MOSI0_PA13()   SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~QSPI1_MOSI0_PA13_Msk)) | QSPI1_MOSI0_PA13    /*!< Set PA13 function to QSPI1_MOSI0     */
#define SET_QSPI1_MOSI0_PD13()   SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~QSPI1_MOSI0_PD13_Msk)) | QSPI1_MOSI0_PD13    /*!< Set PD13 function to QSPI1_MOSI0     */
#define SET_QSPI1_MOSI0_PG14()   SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~QSPI1_MOSI0_PG14_Msk)) | QSPI1_MOSI0_PG14    /*!< Set PG14 function to QSPI1_MOSI0     */
#define SET_QSPI1_MOSI0_PC2()    SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI1_MOSI0_PC2_Msk)) | QSPI1_MOSI0_PC2      /*!< Set PC2 function to QSPI1_MOSI0      */
#define SET_QSPI1_MOSI0_PJ5()    SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~QSPI1_MOSI0_PJ5_Msk)) | QSPI1_MOSI0_PJ5      /*!< Set PJ5 function to QSPI1_MOSI0      */
#define SET_QSPI1_MOSI0_PD6()    SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~QSPI1_MOSI0_PD6_Msk)) | QSPI1_MOSI0_PD6      /*!< Set PD6 function to QSPI1_MOSI0      */
#define SET_QSPI1_MOSI0_PF1()    SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~QSPI1_MOSI0_PF1_Msk)) | QSPI1_MOSI0_PF1      /*!< Set PF1 function to QSPI1_MOSI0      */
#define SET_QSPI1_MOSI1_PG10()   SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~QSPI1_MOSI1_PG10_Msk)) | QSPI1_MOSI1_PG10    /*!< Set PG10 function to QSPI1_MOSI1     */
#define SET_QSPI1_MOSI1_PA6()    SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~QSPI1_MOSI1_PA6_Msk)) | QSPI1_MOSI1_PA6      /*!< Set PA6 function to QSPI1_MOSI1      */
#define SET_QSPI1_MOSI1_PH13()   SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~QSPI1_MOSI1_PH13_Msk)) | QSPI1_MOSI1_PH13    /*!< Set PH13 function to QSPI1_MOSI1     */
#define SET_QSPI1_MOSI1_PD13()   SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~QSPI1_MOSI1_PD13_Msk)) | QSPI1_MOSI1_PD13    /*!< Set PD13 function to QSPI1_MOSI1     */
#define SET_QSPI1_SS_PG11()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~QSPI1_SS_PG11_Msk)) | QSPI1_SS_PG11          /*!< Set PG11 function to QSPI1_SS        */
#define SET_QSPI1_SS_PH14()      SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~QSPI1_SS_PH14_Msk)) | QSPI1_SS_PH14          /*!< Set PH14 function to QSPI1_SS        */
#define SET_QSPI1_SS_PC5()       SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~QSPI1_SS_PC5_Msk)) | QSPI1_SS_PC5            /*!< Set PC5 function to QSPI1_SS         */
#define SET_QSPI1_SS_PJ2()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~QSPI1_SS_PJ2_Msk)) | QSPI1_SS_PJ2            /*!< Set PJ2 function to QSPI1_SS         */
#define SET_QSPI1_SS_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~QSPI1_SS_PC1_Msk)) | QSPI1_SS_PC1            /*!< Set PC1 function to QSPI1_SS         */
#define SET_SC0_CLK_PA0()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SC0_CLK_PA0_Msk)) | SC0_CLK_PA0              /*!< Set PA0 function to SC0_CLK          */
#define SET_SC0_CLK_PF6()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SC0_CLK_PF6_Msk)) | SC0_CLK_PF6              /*!< Set PF6 function to SC0_CLK          */
#define SET_SC0_CLK_PE2()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SC0_CLK_PE2_Msk)) | SC0_CLK_PE2              /*!< Set PE2 function to SC0_CLK          */
#define SET_SC0_CLK_PB5()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SC0_CLK_PB5_Msk)) | SC0_CLK_PB5              /*!< Set PB5 function to SC0_CLK          */
#define SET_SC0_DAT_PE3()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SC0_DAT_PE3_Msk)) | SC0_DAT_PE3              /*!< Set PE3 function to SC0_DAT          */
#define SET_SC0_DAT_PB4()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SC0_DAT_PB4_Msk)) | SC0_DAT_PB4              /*!< Set PB4 function to SC0_DAT          */
#define SET_SC0_DAT_PA1()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SC0_DAT_PA1_Msk)) | SC0_DAT_PA1              /*!< Set PA1 function to SC0_DAT          */
#define SET_SC0_DAT_PF7()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SC0_DAT_PF7_Msk)) | SC0_DAT_PF7              /*!< Set PF7 function to SC0_DAT          */
#define SET_SC0_PWR_PE5()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SC0_PWR_PE5_Msk)) | SC0_PWR_PE5              /*!< Set PE5 function to SC0_PWR          */
#define SET_SC0_PWR_PA3()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SC0_PWR_PA3_Msk)) | SC0_PWR_PA3              /*!< Set PA3 function to SC0_PWR          */
#define SET_SC0_PWR_PB2()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SC0_PWR_PB2_Msk)) | SC0_PWR_PB2              /*!< Set PB2 function to SC0_PWR          */
#define SET_SC0_PWR_PF9()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SC0_PWR_PF9_Msk)) | SC0_PWR_PF9              /*!< Set PF9 function to SC0_PWR          */
#define SET_SC0_RST_PE4()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SC0_RST_PE4_Msk)) | SC0_RST_PE4              /*!< Set PE4 function to SC0_RST          */
#define SET_SC0_RST_PA2()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SC0_RST_PA2_Msk)) | SC0_RST_PA2              /*!< Set PA2 function to SC0_RST          */
#define SET_SC0_RST_PF8()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SC0_RST_PF8_Msk)) | SC0_RST_PF8              /*!< Set PF8 function to SC0_RST          */
#define SET_SC0_RST_PB3()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SC0_RST_PB3_Msk)) | SC0_RST_PB3              /*!< Set PB3 function to SC0_RST          */
#define SET_SC0_nCD_PC12()       SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SC0_nCD_PC12_Msk)) | SC0_nCD_PC12            /*!< Set PC12 function to SC0_nCD         */
#define SET_SC0_nCD_PE6()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SC0_nCD_PE6_Msk)) | SC0_nCD_PE6              /*!< Set PE6 function to SC0_nCD          */
#define SET_SC0_nCD_PA4()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SC0_nCD_PA4_Msk)) | SC0_nCD_PA4              /*!< Set PA4 function to SC0_nCD          */
#define SET_SC0_nCD_PF10()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SC0_nCD_PF10_Msk)) | SC0_nCD_PF10            /*!< Set PF10 function to SC0_nCD         */
#define SET_SC1_CLK_PF1()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~SC1_CLK_PF1_Msk)) | SC1_CLK_PF1              /*!< Set PF1 function to SC1_CLK          */
#define SET_SC1_CLK_PD4()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SC1_CLK_PD4_Msk)) | SC1_CLK_PD4              /*!< Set PD4 function to SC1_CLK          */
#define SET_SC1_CLK_PI10()       SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SC1_CLK_PI10_Msk)) | SC1_CLK_PI10            /*!< Set PI10 function to SC1_CLK         */
#define SET_SC1_CLK_PB12()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SC1_CLK_PB12_Msk)) | SC1_CLK_PB12            /*!< Set PB12 function to SC1_CLK         */
#define SET_SC1_CLK_PG8()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SC1_CLK_PG8_Msk)) | SC1_CLK_PG8              /*!< Set PG8 function to SC1_CLK          */
#define SET_SC1_CLK_PC0()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SC1_CLK_PC0_Msk)) | SC1_CLK_PC0              /*!< Set PC0 function to SC1_CLK          */
#define SET_SC1_DAT_PC1()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SC1_DAT_PC1_Msk)) | SC1_DAT_PC1              /*!< Set PC1 function to SC1_DAT          */
#define SET_SC1_DAT_PD5()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SC1_DAT_PD5_Msk)) | SC1_DAT_PD5              /*!< Set PD5 function to SC1_DAT          */
#define SET_SC1_DAT_PF0()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~SC1_DAT_PF0_Msk)) | SC1_DAT_PF0              /*!< Set PF0 function to SC1_DAT          */
#define SET_SC1_DAT_PG7()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SC1_DAT_PG7_Msk)) | SC1_DAT_PG7              /*!< Set PG7 function to SC1_DAT          */
#define SET_SC1_DAT_PI9()        SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SC1_DAT_PI9_Msk)) | SC1_DAT_PI9              /*!< Set PI9 function to SC1_DAT          */
#define SET_SC1_DAT_PB13()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SC1_DAT_PB13_Msk)) | SC1_DAT_PB13            /*!< Set PB13 function to SC1_DAT         */
#define SET_SC1_PWR_PD7()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SC1_PWR_PD7_Msk)) | SC1_PWR_PD7              /*!< Set PD7 function to SC1_PWR          */
#define SET_SC1_PWR_PC3()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SC1_PWR_PC3_Msk)) | SC1_PWR_PC3              /*!< Set PC3 function to SC1_PWR          */
#define SET_SC1_PWR_PI7()        SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~SC1_PWR_PI7_Msk)) | SC1_PWR_PI7              /*!< Set PI7 function to SC1_PWR          */
#define SET_SC1_PWR_PG5()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SC1_PWR_PG5_Msk)) | SC1_PWR_PG5              /*!< Set PG5 function to SC1_PWR          */
#define SET_SC1_PWR_PB15()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SC1_PWR_PB15_Msk)) | SC1_PWR_PB15            /*!< Set PB15 function to SC1_PWR         */
#define SET_SC1_RST_PI8()        SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SC1_RST_PI8_Msk)) | SC1_RST_PI8              /*!< Set PI8 function to SC1_RST          */
#define SET_SC1_RST_PG6()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SC1_RST_PG6_Msk)) | SC1_RST_PG6              /*!< Set PG6 function to SC1_RST          */
#define SET_SC1_RST_PB14()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SC1_RST_PB14_Msk)) | SC1_RST_PB14            /*!< Set PB14 function to SC1_RST         */
#define SET_SC1_RST_PC2()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SC1_RST_PC2_Msk)) | SC1_RST_PC2              /*!< Set PC2 function to SC1_RST          */
#define SET_SC1_RST_PD6()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SC1_RST_PD6_Msk)) | SC1_RST_PD6              /*!< Set PD6 function to SC1_RST          */
#define SET_SC1_nCD_PD14()       SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SC1_nCD_PD14_Msk)) | SC1_nCD_PD14            /*!< Set PD14 function to SC1_nCD         */
#define SET_SC1_nCD_PC4()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SC1_nCD_PC4_Msk)) | SC1_nCD_PC4              /*!< Set PC4 function to SC1_nCD          */
#define SET_SC1_nCD_PI6()        SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~SC1_nCD_PI6_Msk)) | SC1_nCD_PI6              /*!< Set PI6 function to SC1_nCD          */
#define SET_SC1_nCD_PD3()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SC1_nCD_PD3_Msk)) | SC1_nCD_PD3              /*!< Set PD3 function to SC1_nCD          */
#define SET_SC1_nCD_PC14()       SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SC1_nCD_PC14_Msk)) | SC1_nCD_PC14            /*!< Set PC14 function to SC1_nCD         */
#define SET_SC2_CLK_PA15()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SC2_CLK_PA15_Msk)) | SC2_CLK_PA15            /*!< Set PA15 function to SC2_CLK         */
#define SET_SC2_CLK_PD0()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SC2_CLK_PD0_Msk)) | SC2_CLK_PD0              /*!< Set PD0 function to SC2_CLK          */
#define SET_SC2_CLK_PA6()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SC2_CLK_PA6_Msk)) | SC2_CLK_PA6              /*!< Set PA6 function to SC2_CLK          */
#define SET_SC2_CLK_PE0()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SC2_CLK_PE0_Msk)) | SC2_CLK_PE0              /*!< Set PE0 function to SC2_CLK          */
#define SET_SC2_CLK_PA8()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SC2_CLK_PA8_Msk)) | SC2_CLK_PA8              /*!< Set PA8 function to SC2_CLK          */
#define SET_SC2_DAT_PD1()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SC2_DAT_PD1_Msk)) | SC2_DAT_PD1              /*!< Set PD1 function to SC2_DAT          */
#define SET_SC2_DAT_PA9()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SC2_DAT_PA9_Msk)) | SC2_DAT_PA9              /*!< Set PA9 function to SC2_DAT          */
#define SET_SC2_DAT_PE1()        SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SC2_DAT_PE1_Msk)) | SC2_DAT_PE1              /*!< Set PE1 function to SC2_DAT          */
#define SET_SC2_DAT_PA14()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SC2_DAT_PA14_Msk)) | SC2_DAT_PA14            /*!< Set PA14 function to SC2_DAT         */
#define SET_SC2_DAT_PA7()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SC2_DAT_PA7_Msk)) | SC2_DAT_PA7              /*!< Set PA7 function to SC2_DAT          */
#define SET_SC2_PWR_PC7()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SC2_PWR_PC7_Msk)) | SC2_PWR_PC7              /*!< Set PC7 function to SC2_PWR          */
#define SET_SC2_PWR_PA11()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SC2_PWR_PA11_Msk)) | SC2_PWR_PA11            /*!< Set PA11 function to SC2_PWR         */
#define SET_SC2_PWR_PA12()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SC2_PWR_PA12_Msk)) | SC2_PWR_PA12            /*!< Set PA12 function to SC2_PWR         */
#define SET_SC2_PWR_PD3()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SC2_PWR_PD3_Msk)) | SC2_PWR_PD3              /*!< Set PD3 function to SC2_PWR          */
#define SET_SC2_PWR_PH8()        SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SC2_PWR_PH8_Msk)) | SC2_PWR_PH8              /*!< Set PH8 function to SC2_PWR          */
#define SET_SC2_RST_PC6()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SC2_RST_PC6_Msk)) | SC2_RST_PC6              /*!< Set PC6 function to SC2_RST          */
#define SET_SC2_RST_PD2()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SC2_RST_PD2_Msk)) | SC2_RST_PD2              /*!< Set PD2 function to SC2_RST          */
#define SET_SC2_RST_PA13()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SC2_RST_PA13_Msk)) | SC2_RST_PA13            /*!< Set PA13 function to SC2_RST         */
#define SET_SC2_RST_PA10()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SC2_RST_PA10_Msk)) | SC2_RST_PA10            /*!< Set PA10 function to SC2_RST         */
#define SET_SC2_RST_PH9()        SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SC2_RST_PH9_Msk)) | SC2_RST_PH9              /*!< Set PH9 function to SC2_RST          */
#define SET_SC2_nCD_PD13()       SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SC2_nCD_PD13_Msk)) | SC2_nCD_PD13            /*!< Set PD13 function to SC2_nCD         */
#define SET_SC2_nCD_PA5()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SC2_nCD_PA5_Msk)) | SC2_nCD_PA5              /*!< Set PA5 function to SC2_nCD          */
#define SET_SC2_nCD_PC13()       SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SC2_nCD_PC13_Msk)) | SC2_nCD_PC13            /*!< Set PC13 function to SC2_nCD         */
#define SET_SC2_nCD_PH10()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SC2_nCD_PH10_Msk)) | SC2_nCD_PH10            /*!< Set PH10 function to SC2_nCD         */
#define SET_SD0_CLK_PB1()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SD0_CLK_PB1_Msk)) | SD0_CLK_PB1              /*!< Set PB1 function to SD0_CLK          */
#define SET_SD0_CLK_PE6()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SD0_CLK_PE6_Msk)) | SD0_CLK_PE6              /*!< Set PE6 function to SD0_CLK          */
#define SET_SD0_CMD_PE7()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SD0_CMD_PE7_Msk)) | SD0_CMD_PE7              /*!< Set PE7 function to SD0_CMD          */
#define SET_SD0_CMD_PB0()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SD0_CMD_PB0_Msk)) | SD0_CMD_PB0              /*!< Set PB0 function to SD0_CMD          */
#define SET_SD0_DAT0_PE2()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SD0_DAT0_PE2_Msk)) | SD0_DAT0_PE2            /*!< Set PE2 function to SD0_DAT0         */
#define SET_SD0_DAT0_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SD0_DAT0_PB2_Msk)) | SD0_DAT0_PB2            /*!< Set PB2 function to SD0_DAT0         */
#define SET_SD0_DAT1_PB3()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SD0_DAT1_PB3_Msk)) | SD0_DAT1_PB3            /*!< Set PB3 function to SD0_DAT1         */
#define SET_SD0_DAT1_PE3()       SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SD0_DAT1_PE3_Msk)) | SD0_DAT1_PE3            /*!< Set PE3 function to SD0_DAT1         */
#define SET_SD0_DAT2_PE4()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SD0_DAT2_PE4_Msk)) | SD0_DAT2_PE4            /*!< Set PE4 function to SD0_DAT2         */
#define SET_SD0_DAT2_PB4()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SD0_DAT2_PB4_Msk)) | SD0_DAT2_PB4            /*!< Set PB4 function to SD0_DAT2         */
#define SET_SD0_DAT3_PE5()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SD0_DAT3_PE5_Msk)) | SD0_DAT3_PE5            /*!< Set PE5 function to SD0_DAT3         */
#define SET_SD0_DAT3_PB5()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SD0_DAT3_PB5_Msk)) | SD0_DAT3_PB5            /*!< Set PB5 function to SD0_DAT3         */
#define SET_SD0_nCD_PB12()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SD0_nCD_PB12_Msk)) | SD0_nCD_PB12            /*!< Set PB12 function to SD0_nCD         */
#define SET_SD0_nCD_PD13()       SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SD0_nCD_PD13_Msk)) | SD0_nCD_PD13            /*!< Set PD13 function to SD0_nCD         */
#define SET_SD1_CLK_PJ13()       SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~SD1_CLK_PJ13_Msk)) | SD1_CLK_PJ13            /*!< Set PJ13 function to SD1_CLK         */
#define SET_SD1_CLK_PG14()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SD1_CLK_PG14_Msk)) | SD1_CLK_PG14            /*!< Set PG14 function to SD1_CLK         */
#define SET_SD1_CLK_PD13()       SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SD1_CLK_PD13_Msk)) | SD1_CLK_PD13            /*!< Set PD13 function to SD1_CLK         */
#define SET_SD1_CLK_PA4()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SD1_CLK_PA4_Msk)) | SD1_CLK_PA4              /*!< Set PA4 function to SD1_CLK          */
#define SET_SD1_CLK_PB6()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SD1_CLK_PB6_Msk)) | SD1_CLK_PB6              /*!< Set PB6 function to SD1_CLK          */
#define SET_SD1_CMD_PA5()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SD1_CMD_PA5_Msk)) | SD1_CMD_PA5              /*!< Set PA5 function to SD1_CMD          */
#define SET_SD1_CMD_PJ12()       SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~SD1_CMD_PJ12_Msk)) | SD1_CMD_PJ12            /*!< Set PJ12 function to SD1_CMD         */
#define SET_SD1_CMD_PB7()        SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SD1_CMD_PB7_Msk)) | SD1_CMD_PB7              /*!< Set PB7 function to SD1_CMD          */
#define SET_SD1_CMD_PG13()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SD1_CMD_PG13_Msk)) | SD1_CMD_PG13            /*!< Set PG13 function to SD1_CMD         */
#define SET_SD1_DAT0_PA8()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SD1_DAT0_PA8_Msk)) | SD1_DAT0_PA8            /*!< Set PA8 function to SD1_DAT0         */
#define SET_SD1_DAT0_PA0()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SD1_DAT0_PA0_Msk)) | SD1_DAT0_PA0            /*!< Set PA0 function to SD1_DAT0         */
#define SET_SD1_DAT0_PG12()      SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SD1_DAT0_PG12_Msk)) | SD1_DAT0_PG12          /*!< Set PG12 function to SD1_DAT0        */
#define SET_SD1_DAT0_PJ11()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SD1_DAT0_PJ11_Msk)) | SD1_DAT0_PJ11          /*!< Set PJ11 function to SD1_DAT0        */
#define SET_SD1_DAT1_PG11()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SD1_DAT1_PG11_Msk)) | SD1_DAT1_PG11          /*!< Set PG11 function to SD1_DAT1        */
#define SET_SD1_DAT1_PJ10()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SD1_DAT1_PJ10_Msk)) | SD1_DAT1_PJ10          /*!< Set PJ10 function to SD1_DAT1        */
#define SET_SD1_DAT1_PA9()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SD1_DAT1_PA9_Msk)) | SD1_DAT1_PA9            /*!< Set PA9 function to SD1_DAT1         */
#define SET_SD1_DAT1_PA1()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SD1_DAT1_PA1_Msk)) | SD1_DAT1_PA1            /*!< Set PA1 function to SD1_DAT1         */
#define SET_SD1_DAT2_PA2()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SD1_DAT2_PA2_Msk)) | SD1_DAT2_PA2            /*!< Set PA2 function to SD1_DAT2         */
#define SET_SD1_DAT2_PJ9()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SD1_DAT2_PJ9_Msk)) | SD1_DAT2_PJ9            /*!< Set PJ9 function to SD1_DAT2         */
#define SET_SD1_DAT2_PG10()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SD1_DAT2_PG10_Msk)) | SD1_DAT2_PG10          /*!< Set PG10 function to SD1_DAT2        */
#define SET_SD1_DAT2_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SD1_DAT2_PA10_Msk)) | SD1_DAT2_PA10          /*!< Set PA10 function to SD1_DAT2        */
#define SET_SD1_DAT3_PA3()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SD1_DAT3_PA3_Msk)) | SD1_DAT3_PA3            /*!< Set PA3 function to SD1_DAT3         */
#define SET_SD1_DAT3_PJ8()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SD1_DAT3_PJ8_Msk)) | SD1_DAT3_PJ8            /*!< Set PJ8 function to SD1_DAT3         */
#define SET_SD1_DAT3_PA11()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SD1_DAT3_PA11_Msk)) | SD1_DAT3_PA11          /*!< Set PA11 function to SD1_DAT3        */
#define SET_SD1_DAT3_PG9()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SD1_DAT3_PG9_Msk)) | SD1_DAT3_PG9            /*!< Set PG9 function to SD1_DAT3         */
#define SET_SD1_nCD_PA6()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SD1_nCD_PA6_Msk)) | SD1_nCD_PA6              /*!< Set PA6 function to SD1_nCD          */
#define SET_SD1_nCD_PG15()       SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SD1_nCD_PG15_Msk)) | SD1_nCD_PG15            /*!< Set PG15 function to SD1_nCD         */
#define SET_SD1_nCD_PA12()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SD1_nCD_PA12_Msk)) | SD1_nCD_PA12            /*!< Set PA12 function to SD1_nCD         */
#define SET_SD1_nCD_PE14()       SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~SD1_nCD_PE14_Msk)) | SD1_nCD_PE14            /*!< Set PE14 function to SD1_nCD         */
#define SET_SPI0_CLK_PD2()       SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SPI0_CLK_PD2_Msk)) | SPI0_CLK_PD2            /*!< Set PD2 function to SPI0_CLK         */
#define SET_SPI0_CLK_PF8()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SPI0_CLK_PF8_Msk)) | SPI0_CLK_PF8            /*!< Set PF8 function to SPI0_CLK         */
#define SET_SPI0_CLK_PA2()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPI0_CLK_PA2_Msk)) | SPI0_CLK_PA2            /*!< Set PA2 function to SPI0_CLK         */
#define SET_SPI0_CLK_PB14()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI0_CLK_PB14_Msk)) | SPI0_CLK_PB14          /*!< Set PB14 function to SPI0_CLK        */
#define SET_SPI0_CLK_PA13()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI0_CLK_PA13_Msk)) | SPI0_CLK_PA13          /*!< Set PA13 function to SPI0_CLK        */
#define SET_SPI0_I2SMCLK_PF10()  SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SPI0_I2SMCLK_PF10_Msk)) | SPI0_I2SMCLK_PF10  /*!< Set PF10 function to SPI0_I2SMCLK    */
#define SET_SPI0_I2SMCLK_PD13()  SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SPI0_I2SMCLK_PD13_Msk)) | SPI0_I2SMCLK_PD13  /*!< Set PD13 function to SPI0_I2SMCLK    */
#define SET_SPI0_I2SMCLK_PB0()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI0_I2SMCLK_PB0_Msk)) | SPI0_I2SMCLK_PB0    /*!< Set PB0 function to SPI0_I2SMCLK     */
#define SET_SPI0_I2SMCLK_PD14()  SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SPI0_I2SMCLK_PD14_Msk)) | SPI0_I2SMCLK_PD14  /*!< Set PD14 function to SPI0_I2SMCLK    */
#define SET_SPI0_I2SMCLK_PA4()   SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI0_I2SMCLK_PA4_Msk)) | SPI0_I2SMCLK_PA4    /*!< Set PA4 function to SPI0_I2SMCLK     */
#define SET_SPI0_I2SMCLK_PC14()  SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SPI0_I2SMCLK_PC14_Msk)) | SPI0_I2SMCLK_PC14  /*!< Set PC14 function to SPI0_I2SMCLK    */
#define SET_SPI0_I2SMCLK_PB11()  SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~SPI0_I2SMCLK_PB11_Msk)) | SPI0_I2SMCLK_PB11  /*!< Set PB11 function to SPI0_I2SMCLK    */
#define SET_SPI0_MISO_PD1()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SPI0_MISO_PD1_Msk)) | SPI0_MISO_PD1          /*!< Set PD1 function to SPI0_MISO        */
#define SET_SPI0_MISO_PB13()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI0_MISO_PB13_Msk)) | SPI0_MISO_PB13        /*!< Set PB13 function to SPI0_MISO       */
#define SET_SPI0_MISO_PF7()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI0_MISO_PF7_Msk)) | SPI0_MISO_PF7          /*!< Set PF7 function to SPI0_MISO        */
#define SET_SPI0_MISO_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPI0_MISO_PA1_Msk)) | SPI0_MISO_PA1          /*!< Set PA1 function to SPI0_MISO        */
#define SET_SPI0_MISO_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI0_MISO_PA14_Msk)) | SPI0_MISO_PA14        /*!< Set PA14 function to SPI0_MISO       */
#define SET_SPI0_MOSI_PD0()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SPI0_MOSI_PD0_Msk)) | SPI0_MOSI_PD0          /*!< Set PD0 function to SPI0_MOSI        */
#define SET_SPI0_MOSI_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI0_MOSI_PB12_Msk)) | SPI0_MOSI_PB12        /*!< Set PB12 function to SPI0_MOSI       */
#define SET_SPI0_MOSI_PF6()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI0_MOSI_PF6_Msk)) | SPI0_MOSI_PF6          /*!< Set PF6 function to SPI0_MOSI        */
#define SET_SPI0_MOSI_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPI0_MOSI_PA0_Msk)) | SPI0_MOSI_PA0          /*!< Set PA0 function to SPI0_MOSI        */
#define SET_SPI0_MOSI_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI0_MOSI_PA15_Msk)) | SPI0_MOSI_PA15        /*!< Set PA15 function to SPI0_MOSI       */
#define SET_SPI0_SS_PD3()        SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~SPI0_SS_PD3_Msk)) | SPI0_SS_PD3              /*!< Set PD3 function to SPI0_SS          */
#define SET_SPI0_SS_PF9()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SPI0_SS_PF9_Msk)) | SPI0_SS_PF9              /*!< Set PF9 function to SPI0_SS          */
#define SET_SPI0_SS_PB15()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI0_SS_PB15_Msk)) | SPI0_SS_PB15            /*!< Set PB15 function to SPI0_SS         */
#define SET_SPI0_SS_PA3()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPI0_SS_PA3_Msk)) | SPI0_SS_PA3              /*!< Set PA3 function to SPI0_SS          */
#define SET_SPI0_SS_PA12()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI0_SS_PA12_Msk)) | SPI0_SS_PA12            /*!< Set PA12 function to SPI0_SS         */
#define SET_SPI1_CLK_PI9()       SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SPI1_CLK_PI9_Msk)) | SPI1_CLK_PI9            /*!< Set PI9 function to SPI1_CLK         */
#define SET_SPI1_CLK_PH8()       SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SPI1_CLK_PH8_Msk)) | SPI1_CLK_PH8            /*!< Set PH8 function to SPI1_CLK         */
#define SET_SPI1_CLK_PB3()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI1_CLK_PB3_Msk)) | SPI1_CLK_PB3            /*!< Set PB3 function to SPI1_CLK         */
#define SET_SPI1_CLK_PD5()       SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SPI1_CLK_PD5_Msk)) | SPI1_CLK_PD5            /*!< Set PD5 function to SPI1_CLK         */
#define SET_SPI1_CLK_PA7()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI1_CLK_PA7_Msk)) | SPI1_CLK_PA7            /*!< Set PA7 function to SPI1_CLK         */
#define SET_SPI1_CLK_PC1()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI1_CLK_PC1_Msk)) | SPI1_CLK_PC1            /*!< Set PC1 function to SPI1_CLK         */
#define SET_SPI1_CLK_PH6()       SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~SPI1_CLK_PH6_Msk)) | SPI1_CLK_PH6            /*!< Set PH6 function to SPI1_CLK         */
#define SET_SPI1_CLK_PB7()       SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SPI1_CLK_PB7_Msk)) | SPI1_CLK_PB7            /*!< Set PB7 function to SPI1_CLK         */
#define SET_SPI1_I2SMCLK_PC4()   SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPI1_I2SMCLK_PC4_Msk)) | SPI1_I2SMCLK_PC4    /*!< Set PC4 function to SPI1_I2SMCLK     */
#define SET_SPI1_I2SMCLK_PI6()   SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~SPI1_I2SMCLK_PI6_Msk)) | SPI1_I2SMCLK_PI6    /*!< Set PI6 function to SPI1_I2SMCLK     */
#define SET_SPI1_I2SMCLK_PH10()  SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SPI1_I2SMCLK_PH10_Msk)) | SPI1_I2SMCLK_PH10  /*!< Set PH10 function to SPI1_I2SMCLK    */
#define SET_SPI1_I2SMCLK_PA5()   SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI1_I2SMCLK_PA5_Msk)) | SPI1_I2SMCLK_PA5    /*!< Set PA5 function to SPI1_I2SMCLK     */
#define SET_SPI1_I2SMCLK_PH3()   SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~SPI1_I2SMCLK_PH3_Msk)) | SPI1_I2SMCLK_PH3    /*!< Set PH3 function to SPI1_I2SMCLK     */
#define SET_SPI1_I2SMCLK_PD13()  SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SPI1_I2SMCLK_PD13_Msk)) | SPI1_I2SMCLK_PD13  /*!< Set PD13 function to SPI1_I2SMCLK    */
#define SET_SPI1_I2SMCLK_PB1()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI1_I2SMCLK_PB1_Msk)) | SPI1_I2SMCLK_PB1    /*!< Set PB1 function to SPI1_I2SMCLK     */
#define SET_SPI1_MISO_PE1()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPI1_MISO_PE1_Msk)) | SPI1_MISO_PE1          /*!< Set PE1 function to SPI1_MISO        */
#define SET_SPI1_MISO_PC3()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI1_MISO_PC3_Msk)) | SPI1_MISO_PC3          /*!< Set PC3 function to SPI1_MISO        */
#define SET_SPI1_MISO_PH4()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~SPI1_MISO_PH4_Msk)) | SPI1_MISO_PH4          /*!< Set PH4 function to SPI1_MISO        */
#define SET_SPI1_MISO_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPI1_MISO_PC7_Msk)) | SPI1_MISO_PC7          /*!< Set PC7 function to SPI1_MISO        */
#define SET_SPI1_MISO_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SPI1_MISO_PB5_Msk)) | SPI1_MISO_PB5          /*!< Set PB5 function to SPI1_MISO        */
#define SET_SPI1_MISO_PI7()      SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~SPI1_MISO_PI7_Msk)) | SPI1_MISO_PI7          /*!< Set PI7 function to SPI1_MISO        */
#define SET_SPI1_MISO_PD7()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SPI1_MISO_PD7_Msk)) | SPI1_MISO_PD7          /*!< Set PD7 function to SPI1_MISO        */
#define SET_SPI1_MOSI_PD6()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SPI1_MOSI_PD6_Msk)) | SPI1_MOSI_PD6          /*!< Set PD6 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PH5()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~SPI1_MOSI_PH5_Msk)) | SPI1_MOSI_PH5          /*!< Set PH5 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PI8()      SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SPI1_MOSI_PI8_Msk)) | SPI1_MOSI_PI8          /*!< Set PI8 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PE0()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPI1_MOSI_PE0_Msk)) | SPI1_MOSI_PE0          /*!< Set PE0 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PC2()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI1_MOSI_PC2_Msk)) | SPI1_MOSI_PC2          /*!< Set PC2 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPI1_MOSI_PC6_Msk)) | SPI1_MOSI_PC6          /*!< Set PC6 function to SPI1_MOSI        */
#define SET_SPI1_MOSI_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SPI1_MOSI_PB4_Msk)) | SPI1_MOSI_PB4          /*!< Set PB4 function to SPI1_MOSI        */
#define SET_SPI1_SS_PA6()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI1_SS_PA6_Msk)) | SPI1_SS_PA6              /*!< Set PA6 function to SPI1_SS          */
#define SET_SPI1_SS_PH9()        SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~SPI1_SS_PH9_Msk)) | SPI1_SS_PH9              /*!< Set PH9 function to SPI1_SS          */
#define SET_SPI1_SS_PC0()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI1_SS_PC0_Msk)) | SPI1_SS_PC0              /*!< Set PC0 function to SPI1_SS          */
#define SET_SPI1_SS_PB2()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI1_SS_PB2_Msk)) | SPI1_SS_PB2              /*!< Set PB2 function to SPI1_SS          */
#define SET_SPI1_SS_PI10()       SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~SPI1_SS_PI10_Msk)) | SPI1_SS_PI10            /*!< Set PI10 function to SPI1_SS         */
#define SET_SPI1_SS_PD4()        SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~SPI1_SS_PD4_Msk)) | SPI1_SS_PD4              /*!< Set PD4 function to SPI1_SS          */
#define SET_SPI1_SS_PH7()        SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~SPI1_SS_PH7_Msk)) | SPI1_SS_PH7              /*!< Set PH7 function to SPI1_SS          */
#define SET_SPI2_CLK_PE8()       SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~SPI2_CLK_PE8_Msk)) | SPI2_CLK_PE8            /*!< Set PE8 function to SPI2_CLK         */
#define SET_SPI2_CLK_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SPI2_CLK_PA10_Msk)) | SPI2_CLK_PA10          /*!< Set PA10 function to SPI2_CLK        */
#define SET_SPI2_CLK_PA13()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI2_CLK_PA13_Msk)) | SPI2_CLK_PA13          /*!< Set PA13 function to SPI2_CLK        */
#define SET_SPI2_CLK_PG3()       SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~SPI2_CLK_PG3_Msk)) | SPI2_CLK_PG3            /*!< Set PG3 function to SPI2_CLK         */
#define SET_SPI2_I2SMCLK_PG1()   SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~SPI2_I2SMCLK_PG1_Msk)) | SPI2_I2SMCLK_PG1    /*!< Set PG1 function to SPI2_I2SMCLK     */
#define SET_SPI2_I2SMCLK_PC13()  SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SPI2_I2SMCLK_PC13_Msk)) | SPI2_I2SMCLK_PC13  /*!< Set PC13 function to SPI2_I2SMCLK    */
#define SET_SPI2_I2SMCLK_PB0()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI2_I2SMCLK_PB0_Msk)) | SPI2_I2SMCLK_PB0    /*!< Set PB0 function to SPI2_I2SMCLK     */
#define SET_SPI2_I2SMCLK_PE12()  SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~SPI2_I2SMCLK_PE12_Msk)) | SPI2_I2SMCLK_PE12  /*!< Set PE12 function to SPI2_I2SMCLK    */
#define SET_SPI2_MISO_PG4()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SPI2_MISO_PG4_Msk)) | SPI2_MISO_PG4          /*!< Set PG4 function to SPI2_MISO        */
#define SET_SPI2_MISO_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~SPI2_MISO_PE9_Msk)) | SPI2_MISO_PE9          /*!< Set PE9 function to SPI2_MISO        */
#define SET_SPI2_MISO_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SPI2_MISO_PA9_Msk)) | SPI2_MISO_PA9          /*!< Set PA9 function to SPI2_MISO        */
#define SET_SPI2_MISO_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI2_MISO_PA14_Msk)) | SPI2_MISO_PA14        /*!< Set PA14 function to SPI2_MISO       */
#define SET_SPI2_MOSI_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SPI2_MOSI_PA8_Msk)) | SPI2_MOSI_PA8          /*!< Set PA8 function to SPI2_MOSI        */
#define SET_SPI2_MOSI_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI2_MOSI_PA15_Msk)) | SPI2_MOSI_PA15        /*!< Set PA15 function to SPI2_MOSI       */
#define SET_SPI2_MOSI_PF11()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~SPI2_MOSI_PF11_Msk)) | SPI2_MOSI_PF11        /*!< Set PF11 function to SPI2_MOSI       */
#define SET_SPI2_MOSI_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~SPI2_MOSI_PE10_Msk)) | SPI2_MOSI_PE10        /*!< Set PE10 function to SPI2_MOSI       */
#define SET_SPI2_SS_PG2()        SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~SPI2_SS_PG2_Msk)) | SPI2_SS_PG2              /*!< Set PG2 function to SPI2_SS          */
#define SET_SPI2_SS_PA11()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SPI2_SS_PA11_Msk)) | SPI2_SS_PA11            /*!< Set PA11 function to SPI2_SS         */
#define SET_SPI2_SS_PA12()       SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI2_SS_PA12_Msk)) | SPI2_SS_PA12            /*!< Set PA12 function to SPI2_SS         */
#define SET_SPI2_SS_PE11()       SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~SPI2_SS_PE11_Msk)) | SPI2_SS_PE11            /*!< Set PE11 function to SPI2_SS         */
#define SET_SPI3_CLK_PC10()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~SPI3_CLK_PC10_Msk)) | SPI3_CLK_PC10          /*!< Set PC10 function to SPI3_CLK        */
#define SET_SPI3_CLK_PB11()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~SPI3_CLK_PB11_Msk)) | SPI3_CLK_PB11          /*!< Set PB11 function to SPI3_CLK        */
#define SET_SPI3_CLK_PE4()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPI3_CLK_PE4_Msk)) | SPI3_CLK_PE4            /*!< Set PE4 function to SPI3_CLK         */
#define SET_SPI3_CLK_PG6()       SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SPI3_CLK_PG6_Msk)) | SPI3_CLK_PG6            /*!< Set PG6 function to SPI3_CLK         */
#define SET_SPI3_CLK_PB13()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI3_CLK_PB13_Msk)) | SPI3_CLK_PB13          /*!< Set PB13 function to SPI3_CLK        */
#define SET_SPI3_I2SMCLK_PF6()   SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI3_I2SMCLK_PF6_Msk)) | SPI3_I2SMCLK_PF6    /*!< Set PF6 function to SPI3_I2SMCLK     */
#define SET_SPI3_I2SMCLK_PB1()   SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI3_I2SMCLK_PB1_Msk)) | SPI3_I2SMCLK_PB1    /*!< Set PB1 function to SPI3_I2SMCLK     */
#define SET_SPI3_I2SMCLK_PD14()  SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SPI3_I2SMCLK_PD14_Msk)) | SPI3_I2SMCLK_PD14  /*!< Set PD14 function to SPI3_I2SMCLK    */
#define SET_SPI3_I2SMCLK_PE6()   SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPI3_I2SMCLK_PE6_Msk)) | SPI3_I2SMCLK_PE6    /*!< Set PE6 function to SPI3_I2SMCLK     */
#define SET_SPI3_MISO_PG7()      SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SPI3_MISO_PG7_Msk)) | SPI3_MISO_PG7          /*!< Set PG7 function to SPI3_MISO        */
#define SET_SPI3_MISO_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~SPI3_MISO_PB9_Msk)) | SPI3_MISO_PB9          /*!< Set PB9 function to SPI3_MISO        */
#define SET_SPI3_MISO_PC12()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SPI3_MISO_PC12_Msk)) | SPI3_MISO_PC12        /*!< Set PC12 function to SPI3_MISO       */
#define SET_SPI3_MISO_PE3()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPI3_MISO_PE3_Msk)) | SPI3_MISO_PE3          /*!< Set PE3 function to SPI3_MISO        */
#define SET_SPI3_MISO_PB7()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SPI3_MISO_PB7_Msk)) | SPI3_MISO_PB7          /*!< Set PB7 function to SPI3_MISO        */
#define SET_SPI3_MOSI_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~SPI3_MOSI_PB8_Msk)) | SPI3_MOSI_PB8          /*!< Set PB8 function to SPI3_MOSI        */
#define SET_SPI3_MOSI_PG8()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPI3_MOSI_PG8_Msk)) | SPI3_MOSI_PG8          /*!< Set PG8 function to SPI3_MOSI        */
#define SET_SPI3_MOSI_PC11()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~SPI3_MOSI_PC11_Msk)) | SPI3_MOSI_PC11        /*!< Set PC11 function to SPI3_MOSI       */
#define SET_SPI3_MOSI_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPI3_MOSI_PE2_Msk)) | SPI3_MOSI_PE2          /*!< Set PE2 function to SPI3_MOSI        */
#define SET_SPI3_MOSI_PB6()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~SPI3_MOSI_PB6_Msk)) | SPI3_MOSI_PB6          /*!< Set PB6 function to SPI3_MOSI        */
#define SET_SPI3_SS_PE5()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPI3_SS_PE5_Msk)) | SPI3_SS_PE5              /*!< Set PE5 function to SPI3_SS          */
#define SET_SPI3_SS_PB10()       SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~SPI3_SS_PB10_Msk)) | SPI3_SS_PB10            /*!< Set PB10 function to SPI3_SS         */
#define SET_SPI3_SS_PC9()        SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~SPI3_SS_PC9_Msk)) | SPI3_SS_PC9              /*!< Set PC9 function to SPI3_SS          */
#define SET_SPI3_SS_PG5()        SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~SPI3_SS_PG5_Msk)) | SPI3_SS_PG5              /*!< Set PG5 function to SPI3_SS          */
#define SET_SPI3_SS_PB12()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI3_SS_PB12_Msk)) | SPI3_SS_PB12            /*!< Set PB12 function to SPI3_SS         */
#define SET_SPI4_CLK_PB2()       SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI4_CLK_PB2_Msk)) | SPI4_CLK_PB2            /*!< Set PB2 function to SPI4_CLK         */
#define SET_SPI4_MISO_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI4_MISO_PB1_Msk)) | SPI4_MISO_PB1          /*!< Set PB1 function to SPI4_MISO        */
#define SET_SPI4_MOSI_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI4_MOSI_PB0_Msk)) | SPI4_MOSI_PB0          /*!< Set PB0 function to SPI4_MOSI        */
#define SET_SPI4_SS_PB3()        SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~SPI4_SS_PB3_Msk)) | SPI4_SS_PB3              /*!< Set PB3 function to SPI4_SS          */
#define SET_SPI5_CLK_PF6()       SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI5_CLK_PF6_Msk)) | SPI5_CLK_PF6            /*!< Set PF6 function to SPI5_CLK         */
#define SET_SPI5_CLK_PA6()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI5_CLK_PA6_Msk)) | SPI5_CLK_PA6            /*!< Set PA6 function to SPI5_CLK         */
#define SET_SPI5_MISO_PF4()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI5_MISO_PF4_Msk)) | SPI5_MISO_PF4          /*!< Set PF4 function to SPI5_MISO        */
#define SET_SPI5_MOSI_PF5()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI5_MOSI_PF5_Msk)) | SPI5_MOSI_PF5          /*!< Set PF5 function to SPI5_MOSI        */
#define SET_SPI5_SS_PA7()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI5_SS_PA7_Msk)) | SPI5_SS_PA7              /*!< Set PA7 function to SPI5_SS          */
#define SET_SPI5_SS_PF7()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~SPI5_SS_PF7_Msk)) | SPI5_SS_PF7              /*!< Set PF7 function to SPI5_SS          */
#define SET_SPI6_CLK_PA6()       SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI6_CLK_PA6_Msk)) | SPI6_CLK_PA6            /*!< Set PA6 function to SPI6_CLK         */
#define SET_SPI6_MISO_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPI6_MISO_PC7_Msk)) | SPI6_MISO_PC7          /*!< Set PC7 function to SPI6_MISO        */
#define SET_SPI6_MOSI_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPI6_MOSI_PC6_Msk)) | SPI6_MOSI_PC6          /*!< Set PC6 function to SPI6_MOSI        */
#define SET_SPI6_SS_PA7()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPI6_SS_PA7_Msk)) | SPI6_SS_PA7              /*!< Set PA7 function to SPI6_SS          */
#define SET_SPI7_CLK_PC2()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI7_CLK_PC2_Msk)) | SPI7_CLK_PC2            /*!< Set PC2 function to SPI7_CLK         */
#define SET_SPI7_MISO_PC1()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI7_MISO_PC1_Msk)) | SPI7_MISO_PC1          /*!< Set PC1 function to SPI7_MISO        */
#define SET_SPI7_MOSI_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI7_MOSI_PC0_Msk)) | SPI7_MOSI_PC0          /*!< Set PC0 function to SPI7_MOSI        */
#define SET_SPI7_SS_PC3()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPI7_SS_PC3_Msk)) | SPI7_SS_PC3              /*!< Set PC3 function to SPI7_SS          */
#define SET_SPI8_CLK_PG10()      SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPI8_CLK_PG10_Msk)) | SPI8_CLK_PG10          /*!< Set PG10 function to SPI8_CLK        */
#define SET_SPI8_MISO_PG12()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SPI8_MISO_PG12_Msk)) | SPI8_MISO_PG12        /*!< Set PG12 function to SPI8_MISO       */
#define SET_SPI8_MOSI_PG11()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPI8_MOSI_PG11_Msk)) | SPI8_MOSI_PG11        /*!< Set PG11 function to SPI8_MOSI       */
#define SET_SPI8_SS_PG9()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPI8_SS_PG9_Msk)) | SPI8_SS_PG9              /*!< Set PG9 function to SPI8_SS          */
#define SET_SPI9_CLK_PB15()      SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI9_CLK_PB15_Msk)) | SPI9_CLK_PB15          /*!< Set PB15 function to SPI9_CLK        */
#define SET_SPI9_CLK_PD12()      SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~SPI9_CLK_PD12_Msk)) | SPI9_CLK_PD12          /*!< Set PD12 function to SPI9_CLK        */
#define SET_SPI9_MISO_PB13()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI9_MISO_PB13_Msk)) | SPI9_MISO_PB13        /*!< Set PB13 function to SPI9_MISO       */
#define SET_SPI9_MISO_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~SPI9_MISO_PD11_Msk)) | SPI9_MISO_PD11        /*!< Set PD11 function to SPI9_MISO       */
#define SET_SPI9_MOSI_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~SPI9_MOSI_PD10_Msk)) | SPI9_MOSI_PD10        /*!< Set PD10 function to SPI9_MOSI       */
#define SET_SPI9_MOSI_PC14()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SPI9_MOSI_PC14_Msk)) | SPI9_MOSI_PC14        /*!< Set PC14 function to SPI9_MOSI       */
#define SET_SPI9_SS_PC13()       SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~SPI9_SS_PC13_Msk)) | SPI9_SS_PC13            /*!< Set PC13 function to SPI9_SS         */
#define SET_SPI9_SS_PB14()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~SPI9_SS_PB14_Msk)) | SPI9_SS_PB14            /*!< Set PB14 function to SPI9_SS         */
#define SET_SPI10_CLK_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI10_CLK_PA13_Msk)) | SPI10_CLK_PA13        /*!< Set PA13 function to SPI10_CLK       */
#define SET_SPI10_MISO_PA14()    SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI10_MISO_PA14_Msk)) | SPI10_MISO_PA14      /*!< Set PA14 function to SPI10_MISO      */
#define SET_SPI10_MOSI_PA15()    SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI10_MOSI_PA15_Msk)) | SPI10_MOSI_PA15      /*!< Set PA15 function to SPI10_MOSI      */
#define SET_SPI10_SS_PA12()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPI10_SS_PA12_Msk)) | SPI10_SS_PA12          /*!< Set PA12 function to SPI10_SS        */
#define SET_SPIM_CLK_PE4()       SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPIM_CLK_PE4_Msk)) | SPIM_CLK_PE4            /*!< Set PE4 function to SPIM_CLK         */
#define SET_SPIM_CLK_PJ12()      SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~SPIM_CLK_PJ12_Msk)) | SPIM_CLK_PJ12          /*!< Set PJ12 function to SPIM_CLK        */
#define SET_SPIM_CLK_PG12()      SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SPIM_CLK_PG12_Msk)) | SPIM_CLK_PG12          /*!< Set PG12 function to SPIM_CLK        */
#define SET_SPIM_CLK_PA2()       SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPIM_CLK_PA2_Msk)) | SPIM_CLK_PA2            /*!< Set PA2 function to SPIM_CLK         */
#define SET_SPIM_CLK_PC2()       SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPIM_CLK_PC2_Msk)) | SPIM_CLK_PC2            /*!< Set PC2 function to SPIM_CLK         */
#define SET_SPIM_CLK_PJ0()       SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~SPIM_CLK_PJ0_Msk)) | SPIM_CLK_PJ0            /*!< Set PJ0 function to SPIM_CLK         */
#define SET_SPIM_D2_PJ10()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SPIM_D2_PJ10_Msk)) | SPIM_D2_PJ10            /*!< Set PJ10 function to SPIM_D2         */
#define SET_SPIM_D2_PE7()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPIM_D2_PE7_Msk)) | SPIM_D2_PE7              /*!< Set PE7 function to SPIM_D2          */
#define SET_SPIM_D2_PI14()       SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~SPIM_D2_PI14_Msk)) | SPIM_D2_PI14            /*!< Set PI14 function to SPIM_D2         */
#define SET_SPIM_D2_PG9()        SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPIM_D2_PG9_Msk)) | SPIM_D2_PG9              /*!< Set PG9 function to SPIM_D2          */
#define SET_SPIM_D2_PC5()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPIM_D2_PC5_Msk)) | SPIM_D2_PC5              /*!< Set PC5 function to SPIM_D2          */
#define SET_SPIM_D2_PA5()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPIM_D2_PA5_Msk)) | SPIM_D2_PA5              /*!< Set PA5 function to SPIM_D2          */
#define SET_SPIM_D3_PJ11()       SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SPIM_D3_PJ11_Msk)) | SPIM_D3_PJ11            /*!< Set PJ11 function to SPIM_D3         */
#define SET_SPIM_D3_PE6()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPIM_D3_PE6_Msk)) | SPIM_D3_PE6              /*!< Set PE6 function to SPIM_D3          */
#define SET_SPIM_D3_PC4()        SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~SPIM_D3_PC4_Msk)) | SPIM_D3_PC4              /*!< Set PC4 function to SPIM_D3          */
#define SET_SPIM_D3_PG10()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPIM_D3_PG10_Msk)) | SPIM_D3_PG10            /*!< Set PG10 function to SPIM_D3         */
#define SET_SPIM_D3_PI15()       SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~SPIM_D3_PI15_Msk)) | SPIM_D3_PI15            /*!< Set PI15 function to SPIM_D3         */
#define SET_SPIM_D3_PA4()        SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~SPIM_D3_PA4_Msk)) | SPIM_D3_PA4              /*!< Set PA4 function to SPIM_D3          */
#define SET_SPIM_MISO_PJ9()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SPIM_MISO_PJ9_Msk)) | SPIM_MISO_PJ9          /*!< Set PJ9 function to SPIM_MISO        */
#define SET_SPIM_MISO_PG13()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SPIM_MISO_PG13_Msk)) | SPIM_MISO_PG13        /*!< Set PG13 function to SPIM_MISO       */
#define SET_SPIM_MISO_PE3()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPIM_MISO_PE3_Msk)) | SPIM_MISO_PE3          /*!< Set PE3 function to SPIM_MISO        */
#define SET_SPIM_MISO_PC1()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPIM_MISO_PC1_Msk)) | SPIM_MISO_PC1          /*!< Set PC1 function to SPIM_MISO        */
#define SET_SPIM_MISO_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPIM_MISO_PA1_Msk)) | SPIM_MISO_PA1          /*!< Set PA1 function to SPIM_MISO        */
#define SET_SPIM_MISO_PI13()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~SPIM_MISO_PI13_Msk)) | SPIM_MISO_PI13        /*!< Set PI13 function to SPIM_MISO       */
#define SET_SPIM_MOSI_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPIM_MOSI_PA0_Msk)) | SPIM_MOSI_PA0          /*!< Set PA0 function to SPIM_MOSI        */
#define SET_SPIM_MOSI_PG14()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~SPIM_MOSI_PG14_Msk)) | SPIM_MOSI_PG14        /*!< Set PG14 function to SPIM_MOSI       */
#define SET_SPIM_MOSI_PJ13()     SYS->GPJ_MFP3 = (SYS->GPJ_MFP3 & (~SPIM_MOSI_PJ13_Msk)) | SPIM_MOSI_PJ13        /*!< Set PJ13 function to SPIM_MOSI       */
#define SET_SPIM_MOSI_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPIM_MOSI_PC0_Msk)) | SPIM_MOSI_PC0          /*!< Set PC0 function to SPIM_MOSI        */
#define SET_SPIM_MOSI_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~SPIM_MOSI_PA15_Msk)) | SPIM_MOSI_PA15        /*!< Set PA15 function to SPIM_MOSI       */
#define SET_SPIM_MOSI_PJ1()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~SPIM_MOSI_PJ1_Msk)) | SPIM_MOSI_PJ1          /*!< Set PJ1 function to SPIM_MOSI        */
#define SET_SPIM_MOSI_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~SPIM_MOSI_PE2_Msk)) | SPIM_MOSI_PE2          /*!< Set PE2 function to SPIM_MOSI        */
#define SET_SPIM_SS_PJ8()        SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~SPIM_SS_PJ8_Msk)) | SPIM_SS_PJ8              /*!< Set PJ8 function to SPIM_SS          */
#define SET_SPIM_SS_PG11()       SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~SPIM_SS_PG11_Msk)) | SPIM_SS_PG11            /*!< Set PG11 function to SPIM_SS         */
#define SET_SPIM_SS_PC3()        SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~SPIM_SS_PC3_Msk)) | SPIM_SS_PC3              /*!< Set PC3 function to SPIM_SS          */
#define SET_SPIM_SS_PI12()       SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~SPIM_SS_PI12_Msk)) | SPIM_SS_PI12            /*!< Set PI12 function to SPIM_SS         */
#define SET_SPIM_SS_PA3()        SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~SPIM_SS_PA3_Msk)) | SPIM_SS_PA3              /*!< Set PA3 function to SPIM_SS          */
#define SET_SPIM_SS_PE5()        SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~SPIM_SS_PE5_Msk)) | SPIM_SS_PE5              /*!< Set PE5 function to SPIM_SS          */
#define SET_SWDH_CLK_PA10()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SWDH_CLK_PA10_Msk)) | SWDH_CLK_PA10          /*!< Set PA10 function to SWDH_CLK        */
#define SET_SWDH_DAT_PA9()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~SWDH_DAT_PA9_Msk)) | SWDH_DAT_PA9            /*!< Set PA9 function to SWDH_DAT         */
#define SET_TAMPER0_PF6()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~TAMPER0_PF6_Msk)) | TAMPER0_PF6              /*!< Set PF6 function to TAMPER0          */
#define SET_TAMPER1_PF7()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~TAMPER1_PF7_Msk)) | TAMPER1_PF7              /*!< Set PF7 function to TAMPER1          */
#define SET_TAMPER2_PF8()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~TAMPER2_PF8_Msk)) | TAMPER2_PF8              /*!< Set PF8 function to TAMPER2          */
#define SET_TAMPER3_PF9()        SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~TAMPER3_PF9_Msk)) | TAMPER3_PF9              /*!< Set PF9 function to TAMPER3          */
#define SET_TAMPER4_PF10()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~TAMPER4_PF10_Msk)) | TAMPER4_PF10            /*!< Set PF10 function to TAMPER4         */
#define SET_TAMPER5_PF11()       SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~TAMPER5_PF11_Msk)) | TAMPER5_PF11            /*!< Set PF11 function to TAMPER5         */
#define SET_TM0_PC7()            SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~TM0_PC7_Msk)) | TM0_PC7                      /*!< Set PC7 function to TM0              */
#define SET_TM0_PB5()            SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~TM0_PB5_Msk)) | TM0_PB5                      /*!< Set PB5 function to TM0              */
#define SET_TM0_PG2()            SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~TM0_PG2_Msk)) | TM0_PG2                      /*!< Set PG2 function to TM0              */
#define SET_TM0_EXT_PA11()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~TM0_EXT_PA11_Msk)) | TM0_EXT_PA11            /*!< Set PA11 function to TM0_EXT         */
#define SET_TM0_EXT_PH0()        SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~TM0_EXT_PH0_Msk)) | TM0_EXT_PH0              /*!< Set PH0 function to TM0_EXT          */
#define SET_TM0_EXT_PB15()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~TM0_EXT_PB15_Msk)) | TM0_EXT_PB15            /*!< Set PB15 function to TM0_EXT         */
#define SET_TM1_PC6()            SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~TM1_PC6_Msk)) | TM1_PC6                      /*!< Set PC6 function to TM1              */
#define SET_TM1_PB4()            SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~TM1_PB4_Msk)) | TM1_PB4                      /*!< Set PB4 function to TM1              */
#define SET_TM1_PC14()           SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~TM1_PC14_Msk)) | TM1_PC14                    /*!< Set PC14 function to TM1             */
#define SET_TM1_PG3()            SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~TM1_PG3_Msk)) | TM1_PG3                      /*!< Set PG3 function to TM1              */
#define SET_TM1_EXT_PA10()       SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~TM1_EXT_PA10_Msk)) | TM1_EXT_PA10            /*!< Set PA10 function to TM1_EXT         */
#define SET_TM1_EXT_PB14()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~TM1_EXT_PB14_Msk)) | TM1_EXT_PB14            /*!< Set PB14 function to TM1_EXT         */
#define SET_TM1_EXT_PH1()        SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~TM1_EXT_PH1_Msk)) | TM1_EXT_PH1              /*!< Set PH1 function to TM1_EXT          */
#define SET_TM2_PB3()            SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~TM2_PB3_Msk)) | TM2_PB3                      /*!< Set PB3 function to TM2              */
#define SET_TM2_PG4()            SYS->GPG_MFP1 = (SYS->GPG_MFP1 & (~TM2_PG4_Msk)) | TM2_PG4                      /*!< Set PG4 function to TM2              */
#define SET_TM2_PD0()            SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~TM2_PD0_Msk)) | TM2_PD0                      /*!< Set PD0 function to TM2              */
#define SET_TM2_PA7()            SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~TM2_PA7_Msk)) | TM2_PA7                      /*!< Set PA7 function to TM2              */
#define SET_TM2_EXT_PB13()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~TM2_EXT_PB13_Msk)) | TM2_EXT_PB13            /*!< Set PB13 function to TM2_EXT         */
#define SET_TM2_EXT_PH2()        SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~TM2_EXT_PH2_Msk)) | TM2_EXT_PH2              /*!< Set PH2 function to TM2_EXT          */
#define SET_TM2_EXT_PA9()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~TM2_EXT_PA9_Msk)) | TM2_EXT_PA9              /*!< Set PA9 function to TM2_EXT          */
#define SET_TM3_PF11()           SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~TM3_PF11_Msk)) | TM3_PF11                    /*!< Set PF11 function to TM3             */
#define SET_TM3_PA6()            SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~TM3_PA6_Msk)) | TM3_PA6                      /*!< Set PA6 function to TM3              */
#define SET_TM3_PB2()            SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~TM3_PB2_Msk)) | TM3_PB2                      /*!< Set PB2 function to TM3              */
#define SET_TM3_EXT_PA8()        SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~TM3_EXT_PA8_Msk)) | TM3_EXT_PA8              /*!< Set PA8 function to TM3_EXT          */
#define SET_TM3_EXT_PH3()        SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~TM3_EXT_PH3_Msk)) | TM3_EXT_PH3              /*!< Set PH3 function to TM3_EXT          */
#define SET_TM3_EXT_PB12()       SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~TM3_EXT_PB12_Msk)) | TM3_EXT_PB12            /*!< Set PB12 function to TM3_EXT         */
#define SET_TRACE_CLK_PE12()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~TRACE_CLK_PE12_Msk)) | TRACE_CLK_PE12        /*!< Set PE12 function to TRACE_CLK       */
#define SET_TRACE_DATA0_PE11()   SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~TRACE_DATA0_PE11_Msk)) | TRACE_DATA0_PE11    /*!< Set PE11 function to TRACE_DATA0     */
#define SET_TRACE_DATA1_PE10()   SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~TRACE_DATA1_PE10_Msk)) | TRACE_DATA1_PE10    /*!< Set PE10 function to TRACE_DATA1     */
#define SET_TRACE_DATA2_PE9()    SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~TRACE_DATA2_PE9_Msk)) | TRACE_DATA2_PE9      /*!< Set PE9 function to TRACE_DATA2      */
#define SET_TRACE_DATA3_PE8()    SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~TRACE_DATA3_PE8_Msk)) | TRACE_DATA3_PE8      /*!< Set PE8 function to TRACE_DATA3      */
#define SET_UART0_RXD_PA0()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART0_RXD_PA0_Msk)) | UART0_RXD_PA0          /*!< Set PA0 function to UART0_RXD        */
#define SET_UART0_RXD_PC11()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART0_RXD_PC11_Msk)) | UART0_RXD_PC11        /*!< Set PC11 function to UART0_RXD       */
#define SET_UART0_RXD_PH11()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART0_RXD_PH11_Msk)) | UART0_RXD_PH11        /*!< Set PH11 function to UART0_RXD       */
#define SET_UART0_RXD_PA4()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_RXD_PA4_Msk)) | UART0_RXD_PA4          /*!< Set PA4 function to UART0_RXD        */
#define SET_UART0_RXD_PA6()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_RXD_PA6_Msk)) | UART0_RXD_PA6          /*!< Set PA6 function to UART0_RXD        */
#define SET_UART0_RXD_PD2()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART0_RXD_PD2_Msk)) | UART0_RXD_PD2          /*!< Set PD2 function to UART0_RXD        */
#define SET_UART0_RXD_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART0_RXD_PB8_Msk)) | UART0_RXD_PB8          /*!< Set PB8 function to UART0_RXD        */
#define SET_UART0_RXD_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART0_RXD_PF1_Msk)) | UART0_RXD_PF1          /*!< Set PF1 function to UART0_RXD        */
#define SET_UART0_RXD_PA15()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~UART0_RXD_PA15_Msk)) | UART0_RXD_PA15        /*!< Set PA15 function to UART0_RXD       */
#define SET_UART0_RXD_PF2()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART0_RXD_PF2_Msk)) | UART0_RXD_PF2          /*!< Set PF2 function to UART0_RXD        */
#define SET_UART0_RXD_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART0_RXD_PB12_Msk)) | UART0_RXD_PB12        /*!< Set PB12 function to UART0_RXD       */
#define SET_UART0_TXD_PD3()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART0_TXD_PD3_Msk)) | UART0_TXD_PD3          /*!< Set PD3 function to UART0_TXD        */
#define SET_UART0_TXD_PA5()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_TXD_PA5_Msk)) | UART0_TXD_PA5          /*!< Set PA5 function to UART0_TXD        */
#define SET_UART0_TXD_PF0()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART0_TXD_PF0_Msk)) | UART0_TXD_PF0          /*!< Set PF0 function to UART0_TXD        */
#define SET_UART0_TXD_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART0_TXD_PB9_Msk)) | UART0_TXD_PB9          /*!< Set PB9 function to UART0_TXD        */
#define SET_UART0_TXD_PF3()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART0_TXD_PF3_Msk)) | UART0_TXD_PF3          /*!< Set PF3 function to UART0_TXD        */
#define SET_UART0_TXD_PA1()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART0_TXD_PA1_Msk)) | UART0_TXD_PA1          /*!< Set PA1 function to UART0_TXD        */
#define SET_UART0_TXD_PA7()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_TXD_PA7_Msk)) | UART0_TXD_PA7          /*!< Set PA7 function to UART0_TXD        */
#define SET_UART0_TXD_PA14()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~UART0_TXD_PA14_Msk)) | UART0_TXD_PA14        /*!< Set PA14 function to UART0_TXD       */
#define SET_UART0_TXD_PC12()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~UART0_TXD_PC12_Msk)) | UART0_TXD_PC12        /*!< Set PC12 function to UART0_TXD       */
#define SET_UART0_TXD_PB13()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART0_TXD_PB13_Msk)) | UART0_TXD_PB13        /*!< Set PB13 function to UART0_TXD       */
#define SET_UART0_TXD_PH10()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART0_TXD_PH10_Msk)) | UART0_TXD_PH10        /*!< Set PH10 function to UART0_TXD       */
#define SET_UART0_nCTS_PC7()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART0_nCTS_PC7_Msk)) | UART0_nCTS_PC7        /*!< Set PC7 function to UART0_nCTS       */
#define SET_UART0_nCTS_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART0_nCTS_PB15_Msk)) | UART0_nCTS_PB15      /*!< Set PB15 function to UART0_nCTS      */
#define SET_UART0_nCTS_PA5()     SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_nCTS_PA5_Msk)) | UART0_nCTS_PA5        /*!< Set PA5 function to UART0_nCTS       */
#define SET_UART0_nCTS_PB11()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART0_nCTS_PB11_Msk)) | UART0_nCTS_PB11      /*!< Set PB11 function to UART0_nCTS      */
#define SET_UART0_nRTS_PA4()     SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART0_nRTS_PA4_Msk)) | UART0_nRTS_PA4        /*!< Set PA4 function to UART0_nRTS       */
#define SET_UART0_nRTS_PB14()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART0_nRTS_PB14_Msk)) | UART0_nRTS_PB14      /*!< Set PB14 function to UART0_nRTS      */
#define SET_UART0_nRTS_PB10()    SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART0_nRTS_PB10_Msk)) | UART0_nRTS_PB10      /*!< Set PB10 function to UART0_nRTS      */
#define SET_UART0_nRTS_PC6()     SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART0_nRTS_PC6_Msk)) | UART0_nRTS_PC6        /*!< Set PC6 function to UART0_nRTS       */
#define SET_UART1_RXD_PH9()      SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART1_RXD_PH9_Msk)) | UART1_RXD_PH9          /*!< Set PH9 function to UART1_RXD        */
#define SET_UART1_RXD_PD6()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~UART1_RXD_PD6_Msk)) | UART1_RXD_PD6          /*!< Set PD6 function to UART1_RXD        */
#define SET_UART1_RXD_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART1_RXD_PF1_Msk)) | UART1_RXD_PF1          /*!< Set PF1 function to UART1_RXD        */
#define SET_UART1_RXD_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART1_RXD_PA2_Msk)) | UART1_RXD_PA2          /*!< Set PA2 function to UART1_RXD        */
#define SET_UART1_RXD_PC8()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART1_RXD_PC8_Msk)) | UART1_RXD_PC8          /*!< Set PC8 function to UART1_RXD        */
#define SET_UART1_RXD_PB2()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART1_RXD_PB2_Msk)) | UART1_RXD_PB2          /*!< Set PB2 function to UART1_RXD        */
#define SET_UART1_RXD_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART1_RXD_PD10_Msk)) | UART1_RXD_PD10        /*!< Set PD10 function to UART1_RXD       */
#define SET_UART1_RXD_PG1()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~UART1_RXD_PG1_Msk)) | UART1_RXD_PG1          /*!< Set PG1 function to UART1_RXD        */
#define SET_UART1_RXD_PB6()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART1_RXD_PB6_Msk)) | UART1_RXD_PB6          /*!< Set PB6 function to UART1_RXD        */
#define SET_UART1_RXD_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART1_RXD_PA8_Msk)) | UART1_RXD_PA8          /*!< Set PA8 function to UART1_RXD        */
#define SET_UART1_TXD_PA3()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART1_TXD_PA3_Msk)) | UART1_TXD_PA3          /*!< Set PA3 function to UART1_TXD        */
#define SET_UART1_TXD_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART1_TXD_PD11_Msk)) | UART1_TXD_PD11        /*!< Set PD11 function to UART1_TXD       */
#define SET_UART1_TXD_PH8()      SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART1_TXD_PH8_Msk)) | UART1_TXD_PH8          /*!< Set PH8 function to UART1_TXD        */
#define SET_UART1_TXD_PB3()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART1_TXD_PB3_Msk)) | UART1_TXD_PB3          /*!< Set PB3 function to UART1_TXD        */
#define SET_UART1_TXD_PB7()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART1_TXD_PB7_Msk)) | UART1_TXD_PB7          /*!< Set PB7 function to UART1_TXD        */
#define SET_UART1_TXD_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART1_TXD_PA9_Msk)) | UART1_TXD_PA9          /*!< Set PA9 function to UART1_TXD        */
#define SET_UART1_TXD_PF0()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART1_TXD_PF0_Msk)) | UART1_TXD_PF0          /*!< Set PF0 function to UART1_TXD        */
#define SET_UART1_TXD_PE13()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART1_TXD_PE13_Msk)) | UART1_TXD_PE13        /*!< Set PE13 function to UART1_TXD       */
#define SET_UART1_TXD_PD7()      SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~UART1_TXD_PD7_Msk)) | UART1_TXD_PD7          /*!< Set PD7 function to UART1_TXD        */
#define SET_UART1_TXD_PG0()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~UART1_TXD_PG0_Msk)) | UART1_TXD_PG0          /*!< Set PG0 function to UART1_TXD        */
#define SET_UART1_nCTS_PE11()    SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~UART1_nCTS_PE11_Msk)) | UART1_nCTS_PE11      /*!< Set PE11 function to UART1_nCTS      */
#define SET_UART1_nCTS_PB9()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART1_nCTS_PB9_Msk)) | UART1_nCTS_PB9        /*!< Set PB9 function to UART1_nCTS       */
#define SET_UART1_nCTS_PA1()     SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART1_nCTS_PA1_Msk)) | UART1_nCTS_PA1        /*!< Set PA1 function to UART1_nCTS       */
#define SET_UART1_nRTS_PE12()    SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART1_nRTS_PE12_Msk)) | UART1_nRTS_PE12      /*!< Set PE12 function to UART1_nRTS      */
#define SET_UART1_nRTS_PA0()     SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART1_nRTS_PA0_Msk)) | UART1_nRTS_PA0        /*!< Set PA0 function to UART1_nRTS       */
#define SET_UART1_nRTS_PB8()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART1_nRTS_PB8_Msk)) | UART1_nRTS_PB8        /*!< Set PB8 function to UART1_nRTS       */
#define SET_UART2_RXD_PC0()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART2_RXD_PC0_Msk)) | UART2_RXD_PC0          /*!< Set PC0 function to UART2_RXD        */
#define SET_UART2_RXD_PE9()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~UART2_RXD_PE9_Msk)) | UART2_RXD_PE9          /*!< Set PE9 function to UART2_RXD        */
#define SET_UART2_RXD_PB0()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART2_RXD_PB0_Msk)) | UART2_RXD_PB0          /*!< Set PB0 function to UART2_RXD        */
#define SET_UART2_RXD_PF1()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART2_RXD_PF1_Msk)) | UART2_RXD_PF1          /*!< Set PF1 function to UART2_RXD        */
#define SET_UART2_RXD_PI7()      SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~UART2_RXD_PI7_Msk)) | UART2_RXD_PI7          /*!< Set PI7 function to UART2_RXD        */
#define SET_UART2_RXD_PD12()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~UART2_RXD_PD12_Msk)) | UART2_RXD_PD12        /*!< Set PD12 function to UART2_RXD       */
#define SET_UART2_RXD_PE15()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART2_RXD_PE15_Msk)) | UART2_RXD_PE15        /*!< Set PE15 function to UART2_RXD       */
#define SET_UART2_RXD_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART2_RXD_PC4_Msk)) | UART2_RXD_PC4          /*!< Set PC4 function to UART2_RXD        */
#define SET_UART2_RXD_PF5()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART2_RXD_PF5_Msk)) | UART2_RXD_PF5          /*!< Set PF5 function to UART2_RXD        */
#define SET_UART2_RXD_PG0()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~UART2_RXD_PG0_Msk)) | UART2_RXD_PG0          /*!< Set PG0 function to UART2_RXD        */
#define SET_UART2_RXD_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART2_RXD_PB4_Msk)) | UART2_RXD_PB4          /*!< Set PB4 function to UART2_RXD        */
#define SET_UART2_RXD_PI11()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~UART2_RXD_PI11_Msk)) | UART2_RXD_PI11        /*!< Set PI11 function to UART2_RXD       */
#define SET_UART2_TXD_PE8()      SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~UART2_TXD_PE8_Msk)) | UART2_TXD_PE8          /*!< Set PE8 function to UART2_TXD        */
#define SET_UART2_TXD_PC5()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART2_TXD_PC5_Msk)) | UART2_TXD_PC5          /*!< Set PC5 function to UART2_TXD        */
#define SET_UART2_TXD_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART2_TXD_PB5_Msk)) | UART2_TXD_PB5          /*!< Set PB5 function to UART2_TXD        */
#define SET_UART2_TXD_PF0()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART2_TXD_PF0_Msk)) | UART2_TXD_PF0          /*!< Set PF0 function to UART2_TXD        */
#define SET_UART2_TXD_PG1()      SYS->GPG_MFP0 = (SYS->GPG_MFP0 & (~UART2_TXD_PG1_Msk)) | UART2_TXD_PG1          /*!< Set PG1 function to UART2_TXD        */
#define SET_UART2_TXD_PC13()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~UART2_TXD_PC13_Msk)) | UART2_TXD_PC13        /*!< Set PC13 function to UART2_TXD       */
#define SET_UART2_TXD_PE14()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART2_TXD_PE14_Msk)) | UART2_TXD_PE14        /*!< Set PE14 function to UART2_TXD       */
#define SET_UART2_TXD_PF4()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART2_TXD_PF4_Msk)) | UART2_TXD_PF4          /*!< Set PF4 function to UART2_TXD        */
#define SET_UART2_TXD_PI10()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~UART2_TXD_PI10_Msk)) | UART2_TXD_PI10        /*!< Set PI10 function to UART2_TXD       */
#define SET_UART2_TXD_PI6()      SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~UART2_TXD_PI6_Msk)) | UART2_TXD_PI6          /*!< Set PI6 function to UART2_TXD        */
#define SET_UART2_TXD_PB1()      SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART2_TXD_PB1_Msk)) | UART2_TXD_PB1          /*!< Set PB1 function to UART2_TXD        */
#define SET_UART2_TXD_PC1()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART2_TXD_PC1_Msk)) | UART2_TXD_PC1          /*!< Set PC1 function to UART2_TXD        */
#define SET_UART2_nCTS_PD9()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART2_nCTS_PD9_Msk)) | UART2_nCTS_PD9        /*!< Set PD9 function to UART2_nCTS       */
#define SET_UART2_nCTS_PC2()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART2_nCTS_PC2_Msk)) | UART2_nCTS_PC2        /*!< Set PC2 function to UART2_nCTS       */
#define SET_UART2_nCTS_PI9()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~UART2_nCTS_PI9_Msk)) | UART2_nCTS_PI9        /*!< Set PI9 function to UART2_nCTS       */
#define SET_UART2_nCTS_PF5()     SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART2_nCTS_PF5_Msk)) | UART2_nCTS_PF5        /*!< Set PF5 function to UART2_nCTS       */
#define SET_UART2_nRTS_PI8()     SYS->GPI_MFP2 = (SYS->GPI_MFP2 & (~UART2_nRTS_PI8_Msk)) | UART2_nRTS_PI8        /*!< Set PI8 function to UART2_nRTS       */
#define SET_UART2_nRTS_PF4()     SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART2_nRTS_PF4_Msk)) | UART2_nRTS_PF4        /*!< Set PF4 function to UART2_nRTS       */
#define SET_UART2_nRTS_PD8()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART2_nRTS_PD8_Msk)) | UART2_nRTS_PD8        /*!< Set PD8 function to UART2_nRTS       */
#define SET_UART2_nRTS_PC3()     SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART2_nRTS_PC3_Msk)) | UART2_nRTS_PC3        /*!< Set PC3 function to UART2_nRTS       */
#define SET_UART3_RXD_PI15()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART3_RXD_PI15_Msk)) | UART3_RXD_PI15        /*!< Set PI15 function to UART3_RXD       */
#define SET_UART3_RXD_PE0()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART3_RXD_PE0_Msk)) | UART3_RXD_PE0          /*!< Set PE0 function to UART3_RXD        */
#define SET_UART3_RXD_PE11()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~UART3_RXD_PE11_Msk)) | UART3_RXD_PE11        /*!< Set PE11 function to UART3_RXD       */
#define SET_UART3_RXD_PB14()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART3_RXD_PB14_Msk)) | UART3_RXD_PB14        /*!< Set PB14 function to UART3_RXD       */
#define SET_UART3_RXD_PC9()      SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART3_RXD_PC9_Msk)) | UART3_RXD_PC9          /*!< Set PC9 function to UART3_RXD        */
#define SET_UART3_RXD_PD0()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART3_RXD_PD0_Msk)) | UART3_RXD_PD0          /*!< Set PD0 function to UART3_RXD        */
#define SET_UART3_RXD_PC2()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART3_RXD_PC2_Msk)) | UART3_RXD_PC2          /*!< Set PC2 function to UART3_RXD        */
#define SET_UART3_TXD_PB15()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART3_TXD_PB15_Msk)) | UART3_TXD_PB15        /*!< Set PB15 function to UART3_TXD       */
#define SET_UART3_TXD_PI14()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART3_TXD_PI14_Msk)) | UART3_TXD_PI14        /*!< Set PI14 function to UART3_TXD       */
#define SET_UART3_TXD_PD1()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART3_TXD_PD1_Msk)) | UART3_TXD_PD1          /*!< Set PD1 function to UART3_TXD        */
#define SET_UART3_TXD_PE10()     SYS->GPE_MFP2 = (SYS->GPE_MFP2 & (~UART3_TXD_PE10_Msk)) | UART3_TXD_PE10        /*!< Set PE10 function to UART3_TXD       */
#define SET_UART3_TXD_PE1()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART3_TXD_PE1_Msk)) | UART3_TXD_PE1          /*!< Set PE1 function to UART3_TXD        */
#define SET_UART3_TXD_PC3()      SYS->GPC_MFP0 = (SYS->GPC_MFP0 & (~UART3_TXD_PC3_Msk)) | UART3_TXD_PC3          /*!< Set PC3 function to UART3_TXD        */
#define SET_UART3_TXD_PC10()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART3_TXD_PC10_Msk)) | UART3_TXD_PC10        /*!< Set PC10 function to UART3_TXD       */
#define SET_UART3_nCTS_PB12()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART3_nCTS_PB12_Msk)) | UART3_nCTS_PB12      /*!< Set PB12 function to UART3_nCTS      */
#define SET_UART3_nCTS_PH9()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART3_nCTS_PH9_Msk)) | UART3_nCTS_PH9        /*!< Set PH9 function to UART3_nCTS       */
#define SET_UART3_nCTS_PD2()     SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART3_nCTS_PD2_Msk)) | UART3_nCTS_PD2        /*!< Set PD2 function to UART3_nCTS       */
#define SET_UART3_nRTS_PB13()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~UART3_nRTS_PB13_Msk)) | UART3_nRTS_PB13      /*!< Set PB13 function to UART3_nRTS      */
#define SET_UART3_nRTS_PH8()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART3_nRTS_PH8_Msk)) | UART3_nRTS_PH8        /*!< Set PH8 function to UART3_nRTS       */
#define SET_UART3_nRTS_PD3()     SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~UART3_nRTS_PD3_Msk)) | UART3_nRTS_PD3        /*!< Set PD3 function to UART3_nRTS       */
#define SET_UART4_RXD_PB10()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART4_RXD_PB10_Msk)) | UART4_RXD_PB10        /*!< Set PB10 function to UART4_RXD       */
#define SET_UART4_RXD_PI13()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART4_RXD_PI13_Msk)) | UART4_RXD_PI13        /*!< Set PI13 function to UART4_RXD       */
#define SET_UART4_RXD_PH3()      SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART4_RXD_PH3_Msk)) | UART4_RXD_PH3          /*!< Set PH3 function to UART4_RXD        */
#define SET_UART4_RXD_PA13()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~UART4_RXD_PA13_Msk)) | UART4_RXD_PA13        /*!< Set PA13 function to UART4_RXD       */
#define SET_UART4_RXD_PH11()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART4_RXD_PH11_Msk)) | UART4_RXD_PH11        /*!< Set PH11 function to UART4_RXD       */
#define SET_UART4_RXD_PA2()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART4_RXD_PA2_Msk)) | UART4_RXD_PA2          /*!< Set PA2 function to UART4_RXD        */
#define SET_UART4_RXD_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART4_RXD_PC6_Msk)) | UART4_RXD_PC6          /*!< Set PC6 function to UART4_RXD        */
#define SET_UART4_RXD_PF6()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART4_RXD_PF6_Msk)) | UART4_RXD_PF6          /*!< Set PF6 function to UART4_RXD        */
#define SET_UART4_RXD_PC4()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART4_RXD_PC4_Msk)) | UART4_RXD_PC4          /*!< Set PC4 function to UART4_RXD        */
#define SET_UART4_TXD_PA12()     SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~UART4_TXD_PA12_Msk)) | UART4_TXD_PA12        /*!< Set PA12 function to UART4_TXD       */
#define SET_UART4_TXD_PB11()     SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART4_TXD_PB11_Msk)) | UART4_TXD_PB11        /*!< Set PB11 function to UART4_TXD       */
#define SET_UART4_TXD_PF7()      SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~UART4_TXD_PF7_Msk)) | UART4_TXD_PF7          /*!< Set PF7 function to UART4_TXD        */
#define SET_UART4_TXD_PH2()      SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART4_TXD_PH2_Msk)) | UART4_TXD_PH2          /*!< Set PH2 function to UART4_TXD        */
#define SET_UART4_TXD_PI12()     SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART4_TXD_PI12_Msk)) | UART4_TXD_PI12        /*!< Set PI12 function to UART4_TXD       */
#define SET_UART4_TXD_PC5()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART4_TXD_PC5_Msk)) | UART4_TXD_PC5          /*!< Set PC5 function to UART4_TXD        */
#define SET_UART4_TXD_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART4_TXD_PC7_Msk)) | UART4_TXD_PC7          /*!< Set PC7 function to UART4_TXD        */
#define SET_UART4_TXD_PA3()      SYS->GPA_MFP0 = (SYS->GPA_MFP0 & (~UART4_TXD_PA3_Msk)) | UART4_TXD_PA3          /*!< Set PA3 function to UART4_TXD        */
#define SET_UART4_TXD_PH10()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART4_TXD_PH10_Msk)) | UART4_TXD_PH10        /*!< Set PH10 function to UART4_TXD       */
#define SET_UART4_nCTS_PC8()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART4_nCTS_PC8_Msk)) | UART4_nCTS_PC8        /*!< Set PC8 function to UART4_nCTS       */
#define SET_UART4_nCTS_PE1()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART4_nCTS_PE1_Msk)) | UART4_nCTS_PE1        /*!< Set PE1 function to UART4_nCTS       */
#define SET_UART4_nRTS_PE0()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART4_nRTS_PE0_Msk)) | UART4_nRTS_PE0        /*!< Set PE0 function to UART4_nRTS       */
#define SET_UART4_nRTS_PE13()    SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART4_nRTS_PE13_Msk)) | UART4_nRTS_PE13      /*!< Set PE13 function to UART4_nRTS      */
#define SET_UART5_RXD_PF10()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART5_RXD_PF10_Msk)) | UART5_RXD_PF10        /*!< Set PF10 function to UART5_RXD       */
#define SET_UART5_RXD_PB4()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART5_RXD_PB4_Msk)) | UART5_RXD_PB4          /*!< Set PB4 function to UART5_RXD        */
#define SET_UART5_RXD_PH1()      SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART5_RXD_PH1_Msk)) | UART5_RXD_PH1          /*!< Set PH1 function to UART5_RXD        */
#define SET_UART5_RXD_PE6()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART5_RXD_PE6_Msk)) | UART5_RXD_PE6          /*!< Set PE6 function to UART5_RXD        */
#define SET_UART5_RXD_PA4()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART5_RXD_PA4_Msk)) | UART5_RXD_PA4          /*!< Set PA4 function to UART5_RXD        */
#define SET_UART5_TXD_PB5()      SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~UART5_TXD_PB5_Msk)) | UART5_TXD_PB5          /*!< Set PB5 function to UART5_TXD        */
#define SET_UART5_TXD_PF11()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART5_TXD_PF11_Msk)) | UART5_TXD_PF11        /*!< Set PF11 function to UART5_TXD       */
#define SET_UART5_TXD_PE7()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART5_TXD_PE7_Msk)) | UART5_TXD_PE7          /*!< Set PE7 function to UART5_TXD        */
#define SET_UART5_TXD_PA5()      SYS->GPA_MFP1 = (SYS->GPA_MFP1 & (~UART5_TXD_PA5_Msk)) | UART5_TXD_PA5          /*!< Set PA5 function to UART5_TXD        */
#define SET_UART5_TXD_PH0()      SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART5_TXD_PH0_Msk)) | UART5_TXD_PH0          /*!< Set PH0 function to UART5_TXD        */
#define SET_UART5_nCTS_PF8()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART5_nCTS_PF8_Msk)) | UART5_nCTS_PF8        /*!< Set PF8 function to UART5_nCTS       */
#define SET_UART5_nCTS_PH3()     SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART5_nCTS_PH3_Msk)) | UART5_nCTS_PH3        /*!< Set PH3 function to UART5_nCTS       */
#define SET_UART5_nCTS_PB2()     SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART5_nCTS_PB2_Msk)) | UART5_nCTS_PB2        /*!< Set PB2 function to UART5_nCTS       */
#define SET_UART5_nRTS_PF9()     SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART5_nRTS_PF9_Msk)) | UART5_nRTS_PF9        /*!< Set PF9 function to UART5_nRTS       */
#define SET_UART5_nRTS_PH2()     SYS->GPH_MFP0 = (SYS->GPH_MFP0 & (~UART5_nRTS_PH2_Msk)) | UART5_nRTS_PH2        /*!< Set PH2 function to UART5_nRTS       */
#define SET_UART5_nRTS_PB3()     SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~UART5_nRTS_PB3_Msk)) | UART5_nRTS_PB3        /*!< Set PB3 function to UART5_nRTS       */
#define SET_UART6_RXD_PE15()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART6_RXD_PE15_Msk)) | UART6_RXD_PE15        /*!< Set PE15 function to UART6_RXD       */
#define SET_UART6_RXD_PC6()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART6_RXD_PC6_Msk)) | UART6_RXD_PC6          /*!< Set PC6 function to UART6_RXD        */
#define SET_UART6_RXD_PH5()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART6_RXD_PH5_Msk)) | UART6_RXD_PH5          /*!< Set PH5 function to UART6_RXD        */
#define SET_UART6_RXD_PG14()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~UART6_RXD_PG14_Msk)) | UART6_RXD_PG14        /*!< Set PG14 function to UART6_RXD       */
#define SET_UART6_RXD_PA10()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART6_RXD_PA10_Msk)) | UART6_RXD_PA10        /*!< Set PA10 function to UART6_RXD       */
#define SET_UART6_RXD_PD13()     SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~UART6_RXD_PD13_Msk)) | UART6_RXD_PD13        /*!< Set PD13 function to UART6_RXD       */
#define SET_UART6_RXD_PC11()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART6_RXD_PC11_Msk)) | UART6_RXD_PC11        /*!< Set PC11 function to UART6_RXD       */
#define SET_UART6_RXD_PE4()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART6_RXD_PE4_Msk)) | UART6_RXD_PE4          /*!< Set PE4 function to UART6_RXD        */
#define SET_UART6_RXD_PJ11()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~UART6_RXD_PJ11_Msk)) | UART6_RXD_PJ11        /*!< Set PJ11 function to UART6_RXD       */
#define SET_UART6_TXD_PG13()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~UART6_TXD_PG13_Msk)) | UART6_TXD_PG13        /*!< Set PG13 function to UART6_TXD       */
#define SET_UART6_TXD_PE14()     SYS->GPE_MFP3 = (SYS->GPE_MFP3 & (~UART6_TXD_PE14_Msk)) | UART6_TXD_PE14        /*!< Set PE14 function to UART6_TXD       */
#define SET_UART6_TXD_PC12()     SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~UART6_TXD_PC12_Msk)) | UART6_TXD_PC12        /*!< Set PC12 function to UART6_TXD       */
#define SET_UART6_TXD_PC7()      SYS->GPC_MFP1 = (SYS->GPC_MFP1 & (~UART6_TXD_PC7_Msk)) | UART6_TXD_PC7          /*!< Set PC7 function to UART6_TXD        */
#define SET_UART6_TXD_PH4()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART6_TXD_PH4_Msk)) | UART6_TXD_PH4          /*!< Set PH4 function to UART6_TXD        */
#define SET_UART6_TXD_PJ10()     SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~UART6_TXD_PJ10_Msk)) | UART6_TXD_PJ10        /*!< Set PJ10 function to UART6_TXD       */
#define SET_UART6_TXD_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART6_TXD_PA11_Msk)) | UART6_TXD_PA11        /*!< Set PA11 function to UART6_TXD       */
#define SET_UART6_TXD_PE5()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART6_TXD_PE5_Msk)) | UART6_TXD_PE5          /*!< Set PE5 function to UART6_TXD        */
#define SET_UART6_nCTS_PC9()     SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART6_nCTS_PC9_Msk)) | UART6_nCTS_PC9        /*!< Set PC9 function to UART6_nCTS       */
#define SET_UART6_nCTS_PE2()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART6_nCTS_PE2_Msk)) | UART6_nCTS_PE2        /*!< Set PE2 function to UART6_nCTS       */
#define SET_UART6_nRTS_PC10()    SYS->GPC_MFP2 = (SYS->GPC_MFP2 & (~UART6_nRTS_PC10_Msk)) | UART6_nRTS_PC10      /*!< Set PC10 function to UART6_nRTS      */
#define SET_UART6_nRTS_PE3()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART6_nRTS_PE3_Msk)) | UART6_nRTS_PE3        /*!< Set PE3 function to UART6_nRTS       */
#define SET_UART7_RXD_PD8()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART7_RXD_PD8_Msk)) | UART7_RXD_PD8          /*!< Set PD8 function to UART7_RXD        */
#define SET_UART7_RXD_PG12()     SYS->GPG_MFP3 = (SYS->GPG_MFP3 & (~UART7_RXD_PG12_Msk)) | UART7_RXD_PG12        /*!< Set PG12 function to UART7_RXD       */
#define SET_UART7_RXD_PJ9()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~UART7_RXD_PJ9_Msk)) | UART7_RXD_PJ9          /*!< Set PJ9 function to UART7_RXD        */
#define SET_UART7_RXD_PH7()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART7_RXD_PH7_Msk)) | UART7_RXD_PH7          /*!< Set PH7 function to UART7_RXD        */
#define SET_UART7_RXD_PB8()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART7_RXD_PB8_Msk)) | UART7_RXD_PB8          /*!< Set PB8 function to UART7_RXD        */
#define SET_UART7_RXD_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART7_RXD_PE2_Msk)) | UART7_RXD_PE2          /*!< Set PE2 function to UART7_RXD        */
#define SET_UART7_RXD_PA8()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART7_RXD_PA8_Msk)) | UART7_RXD_PA8          /*!< Set PA8 function to UART7_RXD        */
#define SET_UART7_TXD_PE3()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART7_TXD_PE3_Msk)) | UART7_TXD_PE3          /*!< Set PE3 function to UART7_TXD        */
#define SET_UART7_TXD_PG11()     SYS->GPG_MFP2 = (SYS->GPG_MFP2 & (~UART7_TXD_PG11_Msk)) | UART7_TXD_PG11        /*!< Set PG11 function to UART7_TXD       */
#define SET_UART7_TXD_PA9()      SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~UART7_TXD_PA9_Msk)) | UART7_TXD_PA9          /*!< Set PA9 function to UART7_TXD        */
#define SET_UART7_TXD_PJ8()      SYS->GPJ_MFP2 = (SYS->GPJ_MFP2 & (~UART7_TXD_PJ8_Msk)) | UART7_TXD_PJ8          /*!< Set PJ8 function to UART7_TXD        */
#define SET_UART7_TXD_PB9()      SYS->GPB_MFP2 = (SYS->GPB_MFP2 & (~UART7_TXD_PB9_Msk)) | UART7_TXD_PB9          /*!< Set PB9 function to UART7_TXD        */
#define SET_UART7_TXD_PD9()      SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART7_TXD_PD9_Msk)) | UART7_TXD_PD9          /*!< Set PD9 function to UART7_TXD        */
#define SET_UART7_TXD_PH6()      SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART7_TXD_PH6_Msk)) | UART7_TXD_PH6          /*!< Set PH6 function to UART7_TXD        */
#define SET_UART7_nCTS_PE4()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART7_nCTS_PE4_Msk)) | UART7_nCTS_PE4        /*!< Set PE4 function to UART7_nCTS       */
#define SET_UART7_nCTS_PH5()     SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART7_nCTS_PH5_Msk)) | UART7_nCTS_PH5        /*!< Set PH5 function to UART7_nCTS       */
#define SET_UART7_nRTS_PE5()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART7_nRTS_PE5_Msk)) | UART7_nRTS_PE5        /*!< Set PE5 function to UART7_nRTS       */
#define SET_UART7_nRTS_PH4()     SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART7_nRTS_PH4_Msk)) | UART7_nRTS_PH4        /*!< Set PH4 function to UART7_nRTS       */
#define SET_UART8_RXD_PJ1()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~UART8_RXD_PJ1_Msk)) | UART8_RXD_PJ1          /*!< Set PJ1 function to UART8_RXD        */
#define SET_UART8_RXD_PJ5()      SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~UART8_RXD_PJ5_Msk)) | UART8_RXD_PJ5          /*!< Set PJ5 function to UART8_RXD        */
#define SET_UART8_RXD_PE0()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART8_RXD_PE0_Msk)) | UART8_RXD_PE0          /*!< Set PE0 function to UART8_RXD        */
#define SET_UART8_RXD_PD10()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART8_RXD_PD10_Msk)) | UART8_RXD_PD10        /*!< Set PD10 function to UART8_RXD       */
#define SET_UART8_TXD_PE1()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART8_TXD_PE1_Msk)) | UART8_TXD_PE1          /*!< Set PE1 function to UART8_TXD        */
#define SET_UART8_TXD_PD11()     SYS->GPD_MFP2 = (SYS->GPD_MFP2 & (~UART8_TXD_PD11_Msk)) | UART8_TXD_PD11        /*!< Set PD11 function to UART8_TXD       */
#define SET_UART8_TXD_PJ0()      SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~UART8_TXD_PJ0_Msk)) | UART8_TXD_PJ0          /*!< Set PJ0 function to UART8_TXD        */
#define SET_UART8_TXD_PJ4()      SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~UART8_TXD_PJ4_Msk)) | UART8_TXD_PJ4          /*!< Set PJ4 function to UART8_TXD        */
#define SET_UART8_nCTS_PJ2()     SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~UART8_nCTS_PJ2_Msk)) | UART8_nCTS_PJ2        /*!< Set PJ2 function to UART8_nCTS       */
#define SET_UART8_nCTS_PC13()    SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~UART8_nCTS_PC13_Msk)) | UART8_nCTS_PC13      /*!< Set PC13 function to UART8_nCTS      */
#define SET_UART8_nCTS_PE3()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART8_nCTS_PE3_Msk)) | UART8_nCTS_PE3        /*!< Set PE3 function to UART8_nCTS       */
#define SET_UART8_nCTS_PI14()    SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART8_nCTS_PI14_Msk)) | UART8_nCTS_PI14      /*!< Set PI14 function to UART8_nCTS      */
#define SET_UART8_nRTS_PI15()    SYS->GPI_MFP3 = (SYS->GPI_MFP3 & (~UART8_nRTS_PI15_Msk)) | UART8_nRTS_PI15      /*!< Set PI15 function to UART8_nRTS      */
#define SET_UART8_nRTS_PJ3()     SYS->GPJ_MFP0 = (SYS->GPJ_MFP0 & (~UART8_nRTS_PJ3_Msk)) | UART8_nRTS_PJ3        /*!< Set PJ3 function to UART8_nRTS       */
#define SET_UART8_nRTS_PD12()    SYS->GPD_MFP3 = (SYS->GPD_MFP3 & (~UART8_nRTS_PD12_Msk)) | UART8_nRTS_PD12      /*!< Set PD12 function to UART8_nRTS      */
#define SET_UART8_nRTS_PE2()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~UART8_nRTS_PE2_Msk)) | UART8_nRTS_PE2        /*!< Set PE2 function to UART8_nRTS       */
#define SET_UART9_RXD_PF2()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART9_RXD_PF2_Msk)) | UART9_RXD_PF2          /*!< Set PF2 function to UART9_RXD        */
#define SET_UART9_RXD_PH11()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART9_RXD_PH11_Msk)) | UART9_RXD_PH11        /*!< Set PH11 function to UART9_RXD       */
#define SET_UART9_RXD_PF8()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART9_RXD_PF8_Msk)) | UART9_RXD_PF8          /*!< Set PF8 function to UART9_RXD        */
#define SET_UART9_RXD_PE4()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART9_RXD_PE4_Msk)) | UART9_RXD_PE4          /*!< Set PE4 function to UART9_RXD        */
#define SET_UART9_RXD_PH13()     SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~UART9_RXD_PH13_Msk)) | UART9_RXD_PH13        /*!< Set PH13 function to UART9_RXD       */
#define SET_UART9_TXD_PE5()      SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART9_TXD_PE5_Msk)) | UART9_TXD_PE5          /*!< Set PE5 function to UART9_TXD        */
#define SET_UART9_TXD_PF9()      SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART9_TXD_PF9_Msk)) | UART9_TXD_PF9          /*!< Set PF9 function to UART9_TXD        */
#define SET_UART9_TXD_PF3()      SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~UART9_TXD_PF3_Msk)) | UART9_TXD_PF3          /*!< Set PF3 function to UART9_TXD        */
#define SET_UART9_TXD_PH12()     SYS->GPH_MFP3 = (SYS->GPH_MFP3 & (~UART9_TXD_PH12_Msk)) | UART9_TXD_PH12        /*!< Set PH12 function to UART9_TXD       */
#define SET_UART9_TXD_PH10()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART9_TXD_PH10_Msk)) | UART9_TXD_PH10        /*!< Set PH10 function to UART9_TXD       */
#define SET_UART9_nCTS_PJ6()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~UART9_nCTS_PJ6_Msk)) | UART9_nCTS_PJ6        /*!< Set PJ6 function to UART9_nCTS       */
#define SET_UART9_nCTS_PF11()    SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART9_nCTS_PF11_Msk)) | UART9_nCTS_PF11      /*!< Set PF11 function to UART9_nCTS      */
#define SET_UART9_nCTS_PH6()     SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART9_nCTS_PH6_Msk)) | UART9_nCTS_PH6        /*!< Set PH6 function to UART9_nCTS       */
#define SET_UART9_nCTS_PH8()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART9_nCTS_PH8_Msk)) | UART9_nCTS_PH8        /*!< Set PH8 function to UART9_nCTS       */
#define SET_UART9_nCTS_PE7()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART9_nCTS_PE7_Msk)) | UART9_nCTS_PE7        /*!< Set PE7 function to UART9_nCTS       */
#define SET_UART9_nRTS_PH7()     SYS->GPH_MFP1 = (SYS->GPH_MFP1 & (~UART9_nRTS_PH7_Msk)) | UART9_nRTS_PH7        /*!< Set PH7 function to UART9_nRTS       */
#define SET_UART9_nRTS_PF10()    SYS->GPF_MFP2 = (SYS->GPF_MFP2 & (~UART9_nRTS_PF10_Msk)) | UART9_nRTS_PF10      /*!< Set PF10 function to UART9_nRTS      */
#define SET_UART9_nRTS_PH9()     SYS->GPH_MFP2 = (SYS->GPH_MFP2 & (~UART9_nRTS_PH9_Msk)) | UART9_nRTS_PH9        /*!< Set PH9 function to UART9_nRTS       */
#define SET_UART9_nRTS_PE6()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~UART9_nRTS_PE6_Msk)) | UART9_nRTS_PE6        /*!< Set PE6 function to UART9_nRTS       */
#define SET_UART9_nRTS_PJ7()     SYS->GPJ_MFP1 = (SYS->GPJ_MFP1 & (~UART9_nRTS_PJ7_Msk)) | UART9_nRTS_PJ7        /*!< Set PJ7 function to UART9_nRTS       */
#define SET_USB_D_P_PA14()        SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~USB_D_P_PA14_Msk)) | USB_D_P_PA14              /*!< Set PA14 function to USB_D+          */
#define SET_USB_D_N_PA13()        SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~USB_D_N_PA13_Msk)) | USB_D_N_PA13              /*!< Set PA13 function to USB_D-          */
#define SET_USB_OTG_ID_PA15()    SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~USB_OTG_ID_PA15_Msk)) | USB_OTG_ID_PA15      /*!< Set PA15 function to USB_OTG_ID      */
#define SET_USB_VBUS_PA12()      SYS->GPA_MFP3 = (SYS->GPA_MFP3 & (~USB_VBUS_PA12_Msk)) | USB_VBUS_PA12          /*!< Set PA12 function to USB_VBUS        */
#define SET_USB_VBUS_EN_PB6()    SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~USB_VBUS_EN_PB6_Msk)) | USB_VBUS_EN_PB6      /*!< Set PB6 function to USB_VBUS_EN      */
#define SET_USB_VBUS_EN_PI7()    SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~USB_VBUS_EN_PI7_Msk)) | USB_VBUS_EN_PI7      /*!< Set PI7 function to USB_VBUS_EN      */
#define SET_USB_VBUS_EN_PB15()   SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USB_VBUS_EN_PB15_Msk)) | USB_VBUS_EN_PB15    /*!< Set PB15 function to USB_VBUS_EN     */
#define SET_USB_VBUS_ST_PB14()   SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USB_VBUS_ST_PB14_Msk)) | USB_VBUS_ST_PB14    /*!< Set PB14 function to USB_VBUS_ST     */
#define SET_USB_VBUS_ST_PC14()   SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~USB_VBUS_ST_PC14_Msk)) | USB_VBUS_ST_PC14    /*!< Set PC14 function to USB_VBUS_ST     */
#define SET_USB_VBUS_ST_PD4()    SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~USB_VBUS_ST_PD4_Msk)) | USB_VBUS_ST_PD4      /*!< Set PD4 function to USB_VBUS_ST      */
#define SET_USB_VBUS_ST_PB7()    SYS->GPB_MFP1 = (SYS->GPB_MFP1 & (~USB_VBUS_ST_PB7_Msk)) | USB_VBUS_ST_PB7      /*!< Set PB7 function to USB_VBUS_ST      */
#define SET_USB_VBUS_ST_PI6()    SYS->GPI_MFP1 = (SYS->GPI_MFP1 & (~USB_VBUS_ST_PI6_Msk)) | USB_VBUS_ST_PI6      /*!< Set PI6 function to USB_VBUS_ST      */
#define SET_USCI0_CLK_PD0()      SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~USCI0_CLK_PD0_Msk)) | USCI0_CLK_PD0          /*!< Set PD0 function to USCI0_CLK        */
#define SET_USCI0_CLK_PE2()      SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~USCI0_CLK_PE2_Msk)) | USCI0_CLK_PE2          /*!< Set PE2 function to USCI0_CLK        */
#define SET_USCI0_CLK_PA11()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~USCI0_CLK_PA11_Msk)) | USCI0_CLK_PA11        /*!< Set PA11 function to USCI0_CLK       */
#define SET_USCI0_CLK_PB12()     SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USCI0_CLK_PB12_Msk)) | USCI0_CLK_PB12        /*!< Set PB12 function to USCI0_CLK       */
#define SET_USCI0_CTL0_PC14()    SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~USCI0_CTL0_PC14_Msk)) | USCI0_CTL0_PC14      /*!< Set PC14 function to USCI0_CTL0      */
#define SET_USCI0_CTL0_PE6()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~USCI0_CTL0_PE6_Msk)) | USCI0_CTL0_PE6        /*!< Set PE6 function to USCI0_CTL0       */
#define SET_USCI0_CTL0_PB0()     SYS->GPB_MFP0 = (SYS->GPB_MFP0 & (~USCI0_CTL0_PB0_Msk)) | USCI0_CTL0_PB0        /*!< Set PB0 function to USCI0_CTL0       */
#define SET_USCI0_CTL0_PD4()     SYS->GPD_MFP1 = (SYS->GPD_MFP1 & (~USCI0_CTL0_PD4_Msk)) | USCI0_CTL0_PD4        /*!< Set PD4 function to USCI0_CTL0       */
#define SET_USCI0_CTL0_PC13()    SYS->GPC_MFP3 = (SYS->GPC_MFP3 & (~USCI0_CTL0_PC13_Msk)) | USCI0_CTL0_PC13      /*!< Set PC13 function to USCI0_CTL0      */
#define SET_USCI0_CTL1_PA8()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~USCI0_CTL1_PA8_Msk)) | USCI0_CTL1_PA8        /*!< Set PA8 function to USCI0_CTL1       */
#define SET_USCI0_CTL1_PD3()     SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~USCI0_CTL1_PD3_Msk)) | USCI0_CTL1_PD3        /*!< Set PD3 function to USCI0_CTL1       */
#define SET_USCI0_CTL1_PE5()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~USCI0_CTL1_PE5_Msk)) | USCI0_CTL1_PE5        /*!< Set PE5 function to USCI0_CTL1       */
#define SET_USCI0_CTL1_PB15()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USCI0_CTL1_PB15_Msk)) | USCI0_CTL1_PB15      /*!< Set PB15 function to USCI0_CTL1      */
#define SET_USCI0_DAT0_PA10()    SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~USCI0_DAT0_PA10_Msk)) | USCI0_DAT0_PA10      /*!< Set PA10 function to USCI0_DAT0      */
#define SET_USCI0_DAT0_PB13()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USCI0_DAT0_PB13_Msk)) | USCI0_DAT0_PB13      /*!< Set PB13 function to USCI0_DAT0      */
#define SET_USCI0_DAT0_PE3()     SYS->GPE_MFP0 = (SYS->GPE_MFP0 & (~USCI0_DAT0_PE3_Msk)) | USCI0_DAT0_PE3        /*!< Set PE3 function to USCI0_DAT0       */
#define SET_USCI0_DAT0_PD1()     SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~USCI0_DAT0_PD1_Msk)) | USCI0_DAT0_PD1        /*!< Set PD1 function to USCI0_DAT0       */
#define SET_USCI0_DAT1_PD2()     SYS->GPD_MFP0 = (SYS->GPD_MFP0 & (~USCI0_DAT1_PD2_Msk)) | USCI0_DAT1_PD2        /*!< Set PD2 function to USCI0_DAT1       */
#define SET_USCI0_DAT1_PE4()     SYS->GPE_MFP1 = (SYS->GPE_MFP1 & (~USCI0_DAT1_PE4_Msk)) | USCI0_DAT1_PE4        /*!< Set PE4 function to USCI0_DAT1       */
#define SET_USCI0_DAT1_PA9()     SYS->GPA_MFP2 = (SYS->GPA_MFP2 & (~USCI0_DAT1_PA9_Msk)) | USCI0_DAT1_PA9        /*!< Set PA9 function to USCI0_DAT1       */
#define SET_USCI0_DAT1_PB14()    SYS->GPB_MFP3 = (SYS->GPB_MFP3 & (~USCI0_DAT1_PB14_Msk)) | USCI0_DAT1_PB14      /*!< Set PB14 function to USCI0_DAT1      */
#define SET_X32_IN_PF5()         SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~X32_IN_PF5_Msk)) | X32_IN_PF5                /*!< Set PF5 function to X32_IN           */
#define SET_X32_OUT_PF4()        SYS->GPF_MFP1 = (SYS->GPF_MFP1 & (~X32_OUT_PF4_Msk)) | X32_OUT_PF4              /*!< Set PF4 function to X32_OUT          */
#define SET_XT1_IN_PF3()         SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~XT1_IN_PF3_Msk)) | XT1_IN_PF3                /*!< Set PF3 function to XT1_IN           */
#define SET_XT1_OUT_PF2()        SYS->GPF_MFP0 = (SYS->GPF_MFP0 & (~XT1_OUT_PF2_Msk)) | XT1_OUT_PF2              /*!< Set PF2 function to XT1_OUT          */


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
  * @brief      Enable Brown-out detector interrupt function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector interrupt function.
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
  *             - \ref SYS_BODCTL_BODVL_3_0V
  *             - \ref SYS_BODCTL_BODVL_2_8V
  *             - \ref SYS_BODCTL_BODVL_2_6V
  *             - \ref SYS_BODCTL_BODVL_2_4V
  *             - \ref SYS_BODCTL_BODVL_2_2V
  *             - \ref SYS_BODCTL_BODVL_2_0V
  *             - \ref SYS_BODCTL_BODVL_1_8V
  *             - \ref SYS_BODCTL_BODVL_1_6V
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
  * @brief      Get reset source is from system (MCU) reset
  * @param      None
  * @retval     0   Previous reset source is not from system (MCU) reset
  * @retval     >=1 Previous reset source is from system (MCU) reset
  * @details    This macro get previous reset source is from system (MCU) reset.
  * \hideinitializer
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_MCURF_Msk)

/**
  * @brief      Get reset source is from window watch dog reset
  * @param      None
  * @retval     0   Previous reset source is not from window watch dog reset
  * @retval     >=1 Previous reset source is from window watch dog reset
  * @details    This macro get previous reset source is from window watch dog reset.
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
#define SYS_DISABLE_POR()               (SYS->PORDISAN = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  * \hideinitializer
  */
#define SYS_ENABLE_POR()               (SYS->PORDISAN = 0)

/**
  * @brief      Clear reset source flag
  * @param[in]  u32RstSrc is reset source. Including :
  *             - \ref SYS_RSTSTS_PORF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk
  *             - \ref SYS_RSTSTS_BODRF_Msk
  *             - \ref SYS_RSTSTS_MCURF_Msk
  *             - \ref SYS_RSTSTS_HRESETRF_Msk
  *             - \ref SYS_RSTSTS_CPURF_Msk
  *             - \ref SYS_RSTSTS_CPULKRF_Msk
  * @return     None
  * @details    This macro clear reset source flag.
  * \hideinitializer
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) ((SYS->RSTSTS) = (u32RstSrc) )


/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
/* Declare these inline functions here to avoid MISRA C 2004 rule 8.1 error */
__STATIC_INLINE void SYS_UnlockReg(void);
__STATIC_INLINE void SYS_LockReg(void);

/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
__STATIC_INLINE void SYS_UnlockReg(void)
{
    uint32_t u32TimeOutCount = SystemCoreClock; /* 1 second time-out */

    do
    {
        SYS->REGLCTL = 0x59UL;
        SYS->REGLCTL = 0x16UL;
        SYS->REGLCTL = 0x88UL;

        if (--u32TimeOutCount == 0) break;
    }
    while (SYS->REGLCTL == 0UL);
}

/**
  * @brief      Enable register write-protection function
  * @param      None
  * @return     None
  * @details    This function is used to enable register write-protection function.
  *             To lock the protected register to forbid write access.
  */
__STATIC_INLINE void SYS_LockReg(void)
{
    SYS->REGLCTL = 0UL;
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
void SYS_SetPowerLevel(uint32_t u32PowerLevel);
void SYS_SetVRef(uint32_t u32VRefCTL);

/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif

#endif  /* __NU_SYS_H__ */
