/**************************************************************************//**
 * @file     SYS.h
 * @brief    SYS Driver Header File
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
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


/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA0_RST           ((0UL<<24) | SYS_IPRST0_PDMA0RST_Pos)       /*!< Reset PDMA0 \hideinitializer */
#define PDMA1_RST           ((0UL<<24) | SYS_IPRST0_PDMA1RST_Pos)       /*!< Reset PDMA1 \hideinitializer */
#define PDMA2_RST           ((0UL<<24) | SYS_IPRST0_PDMA2RST_Pos)       /*!< Reset PDMA2 \hideinitializer */
#define PDMA3_RST           ((0UL<<24) | SYS_IPRST0_PDMA3RST_Pos)       /*!< Reset PDMA3 \hideinitializer */
#define DISPC_RST           ((0UL<<24) | SYS_IPRST0_DISPCRST_Pos)       /*!< Reset DISPC \hideinitializer */
#define CCAP0_RST           ((0UL<<24) | SYS_IPRST0_CCAP0RST_Pos)       /*!< Reset CCAP0 \hideinitializer */
#define CCAP1_RST           ((0UL<<24) | SYS_IPRST0_CCAP1RST_Pos)       /*!< Reset CCAP1 \hideinitializer */
#define GFX_RST             ((0UL<<24) | SYS_IPRST0_GFXRST_Pos)         /*!< Reset GFX \hideinitializer */
#define VDEC_RST            ((0UL<<24) | SYS_IPRST0_VDECRST_Pos)        /*!< Reset VDEC \hideinitializer */
#define WHC0_RST            ((0UL<<24) | SYS_IPRST0_WRHO0RST_Pos)       /*!< Reset WRHO0 \hideinitializer */
#define WHC1_RST            ((0UL<<24) | SYS_IPRST0_WRHO1RST_Pos)       /*!< Reset WRHO1 \hideinitializer */
#define GMAC0_RST           ((0UL<<24) | SYS_IPRST0_GMAC0RST_Pos)       /*!< Reset GMAC0 \hideinitializer */
#define GMAC1_RST           ((0UL<<24) | SYS_IPRST0_GMAC1RST_Pos)       /*!< Reset GMAC1 \hideinitializer */
#define HWSEM0_RST          ((0UL<<24) | SYS_IPRST0_HWSEMRST_Pos)       /*!< Reset HWSEM \hideinitializer */
#define EBI_RST             ((0UL<<24) | SYS_IPRST0_EBIRST_Pos)         /*!< Reset EBI \hideinitializer */
#define HSUSBH0_RST         ((0UL<<24) | SYS_IPRST0_HSUSBH0RST_Pos)     /*!< Reset HSUSBH0 \hideinitializer */
#define HSUSBH1_RST         ((0UL<<24) | SYS_IPRST0_HSUSBH1RST_Pos)     /*!< Reset HSUSBH1 \hideinitializer */
#define HSUSBD_RST          ((0UL<<24) | SYS_IPRST0_HSUSBDRST_Pos)      /*!< Reset HSUSBD \hideinitializer */
#define USBHL_RST           ((0UL<<24) | SYS_IPRST0_USBHLRST_Pos)       /*!< Reset USBHL \hideinitializer */
#define SDH0_RST            ((0UL<<24) | SYS_IPRST0_SDH0RST_Pos)        /*!< Reset SDH0 \hideinitializer */
#define SDH1_RST            ((0UL<<24) | SYS_IPRST0_SDH1RST_Pos)        /*!< Reset SDH1 \hideinitializer */
#define NAND_RST            ((0UL<<24) | SYS_IPRST0_NANDRST_Pos)        /*!< Reset NAND \hideinitializer */
#define GPIO_RST            ((0UL<<24) | SYS_IPRST0_GPIORST_Pos)        /*!< Reset GPIO \hideinitializer */
#define MCTLP_RST           ((0UL<<24) | SYS_IPRST0_MCTLPRST_Pos)       /*!< Reset MCTLP \hideinitializer */
#define MCTLC_RST           ((0UL<<24) | SYS_IPRST0_MCTLCRST_Pos)       /*!< Reset MCTLC \hideinitializer */
#define DDRPUB_RST          ((0UL<<24) | SYS_IPRST0_DDRPUBRST_Pos)      /*!< Reset DDRPUB \hideinitializer */

#define TMR0_RST            ((4UL<<24) | SYS_IPRST1_TMR0RST_Pos)        /*!< Reset TMR0 \hideinitializer */
#define TMR1_RST            ((4UL<<24) | SYS_IPRST1_TMR1RST_Pos)        /*!< Reset TMR1 \hideinitializer */
#define TMR2_RST            ((4UL<<24) | SYS_IPRST1_TMR2RST_Pos)        /*!< Reset TMR2 \hideinitializer */
#define TMR3_RST            ((4UL<<24) | SYS_IPRST1_TMR3RST_Pos)        /*!< Reset TMR3 \hideinitializer */
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
#define CANFD0_RST          ((4UL<<24) | SYS_IPRST1_CANFD0RST_Pos)       /*!< Reset MCAN0 \hideinitializer */
#define CANFD1_RST          ((4UL<<24) | SYS_IPRST1_CANFD1RST_Pos)       /*!< Reset MCAN1 \hideinitializer */
#define EADC0_RST           ((4UL<<24) | SYS_IPRST1_EADC0RST_Pos)       /*!< Reset EADC0 \hideinitializer */
#define I2S0_RST            ((4UL<<24) | SYS_IPRST1_I2S0RST_Pos)        /*!< Reset I2S0 \hideinitializer */

#define SC0_RST             ((8UL<<24) | SYS_IPRST2_SC0RST_Pos)         /*!< Reset SC0 \hideinitializer */
#define SC1_RST             ((8UL<<24) | SYS_IPRST2_SC1RST_Pos)         /*!< Reset SC1 \hideinitializer */
#define QSPI1_RST           ((8UL<<24) | SYS_IPRST2_QSPI1RST_Pos)       /*!< Reset QSPI1 \hideinitializer */
#define SPI3_RST            ((8UL<<24) | SYS_IPRST2_SPI3RST_Pos)        /*!< Reset SPI3 \hideinitializer */
#define EPWM0_RST           ((8UL<<24) | SYS_IPRST2_EPWM0RST_Pos)       /*!< Reset EPWM0 \hideinitializer */
#define EPWM1_RST           ((8UL<<24) | SYS_IPRST2_EPWM1RST_Pos)       /*!< Reset EPWM1 \hideinitializer */
#define QEI0_RST            ((8UL<<24) | SYS_IPRST2_QEI0RST_Pos)        /*!< Reset QEI0 \hideinitializer */
#define QEI1_RST            ((8UL<<24) | SYS_IPRST2_QEI1RST_Pos)        /*!< Reset QEI1 \hideinitializer */
#define ECAP0_RST           ((8UL<<24) | SYS_IPRST2_ECAP0RST_Pos)       /*!< Reset ECAP0 \hideinitializer */
#define ECAP1_RST           ((8UL<<24) | SYS_IPRST2_ECAP1RST_Pos)       /*!< Reset ECAP1 \hideinitializer */
#define CANFD2_RST          ((8UL<<24) | SYS_IPRST2_CANFD2RST_Pos)      /*!< Reset CANFD2 \hideinitializer */
#define ADC0_RST            ((8UL<<24) | SYS_IPRST2_ADC0RST_Pos)        /*!< Reset ADC0 \hideinitializer */

#define TMR4_RST            ((12UL<<24) | SYS_IPRST3_TMR4RST_Pos)       /*!< Reset TMR4 \hideinitializer */
#define TMR5_RST            ((12UL<<24) | SYS_IPRST3_TMR5RST_Pos)       /*!< Reset TMR5 \hideinitializer */
#define TMR6_RST            ((12UL<<24) | SYS_IPRST3_TMR6RST_Pos)       /*!< Reset TMR6 \hideinitializer */
#define TMR7_RST            ((12UL<<24) | SYS_IPRST3_TMR7RST_Pos)       /*!< Reset TMR7 \hideinitializer */
#define TMR8_RST            ((12UL<<24) | SYS_IPRST3_TMR8RST_Pos)       /*!< Reset TMR8 \hideinitializer */
#define TMR9_RST            ((12UL<<24) | SYS_IPRST3_TMR9RST_Pos)       /*!< Reset TMR9 \hideinitializer */
#define TMR10_RST           ((12UL<<24) | SYS_IPRST3_TMR10RST_Pos)      /*!< Reset TMR10 \hideinitializer */
#define TMR11_RST           ((12UL<<24) | SYS_IPRST3_TMR11RST_Pos)      /*!< Reset TMR11 \hideinitializer */
#define UART8_RST           ((12UL<<24) | SYS_IPRST3_UART8RST_Pos)      /*!< Reset UART8 \hideinitializer */
#define UART9_RST           ((12UL<<24) | SYS_IPRST3_UART9RST_Pos)      /*!< Reset UART9 \hideinitializer */
#define UART10_RST          ((12UL<<24) | SYS_IPRST3_UART10RST_Pos)     /*!< Reset UART10 \hideinitializer */
#define UART11_RST          ((12UL<<24) | SYS_IPRST3_UART11RST_Pos)     /*!< Reset UART11 \hideinitializer */
#define UART12_RST          ((12UL<<24) | SYS_IPRST3_UART12RST_Pos)     /*!< Reset UART12 \hideinitializer */
#define UART13_RST          ((12UL<<24) | SYS_IPRST3_UART13RST_Pos)     /*!< Reset UART13 \hideinitializer */
#define UART14_RST          ((12UL<<24) | SYS_IPRST3_UART14RST_Pos)     /*!< Reset UART14 \hideinitializer */
#define UART15_RST          ((12UL<<24) | SYS_IPRST3_UART15RST_Pos)     /*!< Reset UART15 \hideinitializer */
#define UART16_RST          ((12UL<<24) | SYS_IPRST3_UART16RST_Pos)     /*!< Reset UART16 \hideinitializer */
#define I2S1_RST            ((12UL<<24) | SYS_IPRST3_I2S1RST_Pos)       /*!< Reset I2S1 \hideinitializer */
#define I2C4_RST            ((12UL<<24) | SYS_IPRST3_I2C4RST_Pos)       /*!< Reset I2C4 \hideinitializer */
#define I2C5_RST            ((12UL<<24) | SYS_IPRST3_I2C5RST_Pos)       /*!< Reset I2C5 \hideinitializer */
#define EPWM2_RST           ((12UL<<24) | SYS_IPRST3_EPWM2RST_Pos)      /*!< Reset EPWM2 \hideinitializer */
#define ECAP2_RST           ((12UL<<24) | SYS_IPRST3_ECAP2RST_Pos)      /*!< Reset ECAP2 \hideinitializer */
#define QEI2_RST            ((12UL<<24) | SYS_IPRST3_QEI2RST_Pos)       /*!< Reset QEI2 \hideinitializer */
#define CANFD3_RST          ((12UL<<24) | SYS_IPRST3_CANFD3RST_Pos)     /*!< Reset MCAN3 \hideinitializer */
#define KPI_RST             ((12UL<<24) | SYS_IPRST3_KPIRST_Pos)        /*!< Reset KPI \hideinitializer */
#define GIC_RST             ((12UL<<24) | SYS_IPRST3_GICRST_Pos)        /*!< Reset GIC \hideinitializer */
#define SSMCC_RST           ((12UL<<24) | SYS_IPRST3_SSMCCRST_Pos)      /*!< Reset SSMCC \hideinitializer */
#define SSPCC_RST           ((12UL<<24) | SYS_IPRST3_SSPCCRST_Pos)      /*!< Reset SSPCC \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to set PA.0 as SC0_CLK in initial function,
           user can issue following command to achieve it.

           SYS->GPA_MFPL  = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA0MFP_Msk) ) | SYS_GPA_MFPL_PA0_MFP_SC0_CLK  ;

*/
/********************* Bit definition of GPA_MFPL register **********************/
#define SYS_GPA_MFPL_PA0MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA0MFP_UART1_nCTS        (0x02UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< Clear to Send input pin for UART1. */
#define SYS_GPA_MFPL_PA0MFP_UART16_RXD        (0x03UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< Data receiver input pin for UART16. */
#define SYS_GPA_MFPL_PA0MFP_NAND_DATA0        (0x06UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< NAND Flash date bus bit 0. */
#define SYS_GPA_MFPL_PA0MFP_EBI_AD0           (0x07UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< EBI address/data bus bit0. */
#define SYS_GPA_MFPL_PA0MFP_EBI_ADR0          (0x09UL<<SYS_GPA_MFPL_PA0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA1MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA1MFP_UART1_nRTS        (0x02UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< Request to Send output pin for UART1. */
#define SYS_GPA_MFPL_PA1MFP_UART16_TXD        (0x03UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< Data transmitter output pin for UART16. */
#define SYS_GPA_MFPL_PA1MFP_NAND_DATA1        (0x06UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< NAND Flash date bus bit 1. */
#define SYS_GPA_MFPL_PA1MFP_EBI_AD1           (0x07UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPL_PA1MFP_EBI_ADR1          (0x09UL<<SYS_GPA_MFPL_PA1MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA2MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA2MFP_UART1_RXD         (0x02UL<<SYS_GPA_MFPL_PA2MFP_Pos)  /*!< Data receiver input pin for UART1. */
#define SYS_GPA_MFPL_PA2MFP_NAND_DATA2        (0x06UL<<SYS_GPA_MFPL_PA2MFP_Pos)  /*!< NAND Flash date bus bit 2. */
#define SYS_GPA_MFPL_PA2MFP_EBI_AD2           (0x07UL<<SYS_GPA_MFPL_PA2MFP_Pos)  /*!< EBI address/data bus bit2. */
#define SYS_GPA_MFPL_PA2MFP_EBI_ADR2          (0x09UL<<SYS_GPA_MFPL_PA2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA3MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA3MFP_UART1_TXD         (0x02UL<<SYS_GPA_MFPL_PA3MFP_Pos)  /*!< Data transmitter output pin for UART1. */
#define SYS_GPA_MFPL_PA3MFP_NAND_DATA3        (0x06UL<<SYS_GPA_MFPL_PA3MFP_Pos)  /*!< NAND Flash date bus bit 3. */
#define SYS_GPA_MFPL_PA3MFP_EBI_AD3           (0x07UL<<SYS_GPA_MFPL_PA3MFP_Pos)  /*!< EBI address/data bus bit3. */
#define SYS_GPA_MFPL_PA3MFP_EBI_ADR3          (0x09UL<<SYS_GPA_MFPL_PA3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA4MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA4MFP_UART3_nCTS        (0x02UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< Clear to Send input pin for UART3. */
#define SYS_GPA_MFPL_PA4MFP_UART2_RXD         (0x03UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< Data receiver input pin for UART2. */
#define SYS_GPA_MFPL_PA4MFP_NAND_DATA4        (0x06UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< NAND Flash date bus bit 4. */
#define SYS_GPA_MFPL_PA4MFP_EBI_AD4           (0x07UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< EBI address/data bus bit4. */
#define SYS_GPA_MFPL_PA4MFP_EBI_ADR4          (0x09UL<<SYS_GPA_MFPL_PA4MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA5MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA5MFP_UART3_nRTS        (0x02UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< Request to Send output pin for UART3. */
#define SYS_GPA_MFPL_PA5MFP_UART2_TXD         (0x03UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< Data transmitter output pin for UART2. */
#define SYS_GPA_MFPL_PA5MFP_NAND_DATA5        (0x06UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< NAND Flash date bus bit 5. */
#define SYS_GPA_MFPL_PA5MFP_EBI_AD5           (0x07UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< EBI address/data bus bit5. */
#define SYS_GPA_MFPL_PA5MFP_EBI_ADR5          (0x09UL<<SYS_GPA_MFPL_PA5MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA6MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA6MFP_UART3_RXD         (0x02UL<<SYS_GPA_MFPL_PA6MFP_Pos)  /*!< Data receiver input pin for UART3. */
#define SYS_GPA_MFPL_PA6MFP_NAND_DATA6        (0x06UL<<SYS_GPA_MFPL_PA6MFP_Pos)  /*!< NAND Flash date bus bit 6. */
#define SYS_GPA_MFPL_PA6MFP_EBI_AD6           (0x07UL<<SYS_GPA_MFPL_PA6MFP_Pos)  /*!< EBI address/data bus bit6. */
#define SYS_GPA_MFPL_PA6MFP_EBI_ADR6          (0x09UL<<SYS_GPA_MFPL_PA6MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPL_PA7MFP_GPIO              (0x00UL<<SYS_GPA_MFPL_PA7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPL_PA7MFP_UART3_TXD         (0x02UL<<SYS_GPA_MFPL_PA7MFP_Pos)  /*!< Data transmitter output pin for UART3. */
#define SYS_GPA_MFPL_PA7MFP_NAND_DATA7        (0x06UL<<SYS_GPA_MFPL_PA7MFP_Pos)  /*!< NAND Flash date bus bit 7. */
#define SYS_GPA_MFPL_PA7MFP_EBI_AD7           (0x07UL<<SYS_GPA_MFPL_PA7MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPA_MFPL_PA7MFP_EBI_ADR7          (0x09UL<<SYS_GPA_MFPL_PA7MFP_Pos)  /*!< EBI address/data bus bit*. */
/********************* Bit definition of GPA_MFPH register **********************/
#define SYS_GPA_MFPH_PA8MFP_GPIO              (0x00UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA8MFP_UART5_nCTS        (0x02UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< Clear to Send input pin for UART5. */
#define SYS_GPA_MFPH_PA8MFP_UART4_RXD         (0x03UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< Data receiver input pin for UART4. */
#define SYS_GPA_MFPH_PA8MFP_NAND_RDY0         (0x06UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< NAND Flash ready/busy input pin. */
#define SYS_GPA_MFPH_PA8MFP_EBI_AD8           (0x07UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPA_MFPH_PA8MFP_EBI_ADR8          (0x09UL<<SYS_GPA_MFPH_PA8MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA9MFP_GPIO              (0x00UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA9MFP_UART5_nRTS        (0x02UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< Request to Send output pin for UART5. */
#define SYS_GPA_MFPH_PA9MFP_UART4_TXD         (0x03UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< Data transmitter output pin for UART4. */
#define SYS_GPA_MFPH_PA9MFP_NAND_nRE          (0x06UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< NAND Flash read enable output pin. */
#define SYS_GPA_MFPH_PA9MFP_EBI_AD9           (0x07UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< EBI address/data bus bit9. */
#define SYS_GPA_MFPH_PA9MFP_EBI_ADR9          (0x09UL<<SYS_GPA_MFPH_PA9MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA10MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA10MFP_UART5_RXD        (0x02UL<<SYS_GPA_MFPH_PA10MFP_Pos) /*!< Data receiver input pin for UART5. */
#define SYS_GPA_MFPH_PA10MFP_NAND_nWE         (0x06UL<<SYS_GPA_MFPH_PA10MFP_Pos) /*!< NAND Flash write enable output pin. */
#define SYS_GPA_MFPH_PA10MFP_EBI_AD10         (0x07UL<<SYS_GPA_MFPH_PA10MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPH_PA10MFP_EBI_ADR10        (0x09UL<<SYS_GPA_MFPH_PA10MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA11MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA11MFP_UART5_TXD        (0x02UL<<SYS_GPA_MFPH_PA11MFP_Pos) /*!< Data transmitter output pin for UART5. */
#define SYS_GPA_MFPH_PA11MFP_NAND_CLE         (0x06UL<<SYS_GPA_MFPH_PA11MFP_Pos) /*!< NAND Flash command latch enable output pin. */
#define SYS_GPA_MFPH_PA11MFP_EBI_AD11         (0x07UL<<SYS_GPA_MFPH_PA11MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPH_PA11MFP_EBI_ADR11        (0x09UL<<SYS_GPA_MFPH_PA11MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA12MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA12MFP_UART7_nCTS       (0x02UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< Clear to Send input pin for UART7. */
#define SYS_GPA_MFPH_PA12MFP_UART8_RXD        (0x03UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< Data receiver input pin for UART8. */
#define SYS_GPA_MFPH_PA12MFP_NAND_ALE         (0x06UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< NAND Flash address latch enable output pin. */
#define SYS_GPA_MFPH_PA12MFP_EBI_AD12         (0x07UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPH_PA12MFP_EBI_ADR12        (0x09UL<<SYS_GPA_MFPH_PA12MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA13MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA13MFP_UART7_nRTS       (0x02UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< Request to Send output pin for UART7. */
#define SYS_GPA_MFPH_PA13MFP_UART8_TXD        (0x03UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< Data transmitter output pin for UART8. */
#define SYS_GPA_MFPH_PA13MFP_NAND_nCS0        (0x06UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< NAND Flash chip select pin. */
#define SYS_GPA_MFPH_PA13MFP_EBI_AD13         (0x07UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPH_PA13MFP_EBI_ADR13        (0x09UL<<SYS_GPA_MFPH_PA13MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA14MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA14MFP_UART7_RXD        (0x02UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< Data receiver input pin for UART7. */
#define SYS_GPA_MFPH_PA14MFP_CAN3_RXD         (0x03UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPA_MFPH_PA14MFP_USBHL3_DM        (0x04UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPA_MFPH_PA14MFP_NAND_nWP         (0x06UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< NAND Flash write protect input pin. */
#define SYS_GPA_MFPH_PA14MFP_EBI_AD14         (0x07UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPA_MFPH_PA14MFP_EBI_ADR14        (0x09UL<<SYS_GPA_MFPH_PA14MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPA_MFPH_PA15MFP_GPIO             (0x00UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPA_MFPH_PA15MFP_EPWM0_CH2        (0x01UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPA_MFPH_PA15MFP_UART9_nCTS       (0x02UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< Clear to Send input pin for UART*. */
#define SYS_GPA_MFPH_PA15MFP_UART6_RXD        (0x03UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< Data receiver input pin for UART6. */
#define SYS_GPA_MFPH_PA15MFP_I2C4_SDA         (0x04UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< I2C4 data input/output pin. */
#define SYS_GPA_MFPH_PA15MFP_CAN2_RXD         (0x05UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPA_MFPH_PA15MFP_USBHL0_DM        (0x06UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPA_MFPH_PA15MFP_EBI_ALE          (0x07UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< EBI address latch enable output pin. */
#define SYS_GPA_MFPH_PA15MFP_QEI0_A           (0x09UL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< Quadrature encoder phase A input of QEI Unit 0. */
#define SYS_GPA_MFPH_PA15MFP_TM1              (0x0BUL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPA_MFPH_PA15MFP_RGMII0_PPS       (0x0EUL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< RGMII0 Pulse Per Second output pin. */
#define SYS_GPA_MFPH_PA15MFP_RMII0_PPS        (0x0FUL<<SYS_GPA_MFPH_PA15MFP_Pos) /*!< RMII0 Pulse Per Second output pin. */
/********************* Bit definition of GPB_MFPL register **********************/
#define SYS_GPB_MFPL_PB0MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB0MFP_EADC0_CH0         (0x08UL<<SYS_GPB_MFPL_PB0MFP_Pos)  /*!< EADC0 channel0 analog input. */
#define SYS_GPB_MFPL_PB1MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB1MFP_EADC0_CH1         (0x08UL<<SYS_GPB_MFPL_PB1MFP_Pos)  /*!< EADC0 channel1 analog input. */
#define SYS_GPB_MFPL_PB2MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB2MFP_EADC0_CH2         (0x08UL<<SYS_GPB_MFPL_PB2MFP_Pos)  /*!< EADC0 channel2 analog input. */
#define SYS_GPB_MFPL_PB3MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB3MFP_EADC0_CH3         (0x08UL<<SYS_GPB_MFPL_PB3MFP_Pos)  /*!< EADC0 channel3 analog input. */
#define SYS_GPB_MFPL_PB4MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB4MFP_EADC0_CH4         (0x08UL<<SYS_GPB_MFPL_PB4MFP_Pos)  /*!< EADC0 channel4 analog input. */
#define SYS_GPB_MFPL_PB5MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB5MFP_EADC0_CH5         (0x08UL<<SYS_GPB_MFPL_PB5MFP_Pos)  /*!< EADC0 channel5 analog input. */
#define SYS_GPB_MFPL_PB6MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB6MFP_EADC0_CH6         (0x08UL<<SYS_GPB_MFPL_PB6MFP_Pos)  /*!< EADC0 channel6 analog input. */
#define SYS_GPB_MFPL_PB7MFP_GPIO              (0x00UL<<SYS_GPB_MFPL_PB7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPL_PB7MFP_EADC0_CH7         (0x08UL<<SYS_GPB_MFPL_PB7MFP_Pos)  /*!< EADC0 channel7 analog input. */
/********************* Bit definition of GPB_MFPH register **********************/
#define SYS_GPB_MFPH_PB8MFP_GPIO              (0x00UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB8MFP_EPWM2_BRAKE0      (0x01UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< Brake input pin 0 of EPWM2. */
#define SYS_GPB_MFPH_PB8MFP_UART2_nCTS        (0x02UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< Clear to Send input pin for UART2. */
#define SYS_GPB_MFPH_PB8MFP_UART1_RXD         (0x03UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< Data receiver input pin for UART1. */
#define SYS_GPB_MFPH_PB8MFP_I2C2_SDA          (0x04UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< I2C2 data input/output pin. */
#define SYS_GPB_MFPH_PB8MFP_SPI0_SS1          (0x05UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< 1st SPI0 slave select pin. */
#define SYS_GPB_MFPH_PB8MFP_SPI0_I2SMCLK      (0x06UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< SPI0 I2S master clock output pin. */
#define SYS_GPB_MFPH_PB8MFP_ADC0_CH0          (0x08UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< ADC0 channel 0 analog input. */
#define SYS_GPB_MFPH_PB8MFP_EBI_nCS0          (0x09UL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPB_MFPH_PB8MFP_TM4               (0x0BUL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< Timer4 event counter input / toggle output */
#define SYS_GPB_MFPH_PB8MFP_QEI2_INDEX        (0x0EUL<<SYS_GPB_MFPH_PB8MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 2. */
#define SYS_GPB_MFPH_PB9MFP_GPIO              (0x00UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB9MFP_EPWM2_CH4         (0x01UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< EPWM2 channel4 output/capture input. */
#define SYS_GPB_MFPH_PB9MFP_UART2_nRTS        (0x02UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< Request to Send output pin for UART2. */
#define SYS_GPB_MFPH_PB9MFP_UART1_TXD         (0x03UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< Data transmitter output pin for UART1. */
#define SYS_GPB_MFPH_PB9MFP_I2C2_SCL          (0x04UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< I2C2 clock pin. */
#define SYS_GPB_MFPH_PB9MFP_SPI0_CLK          (0x05UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< SPI0 serial clock pin. */
#define SYS_GPB_MFPH_PB9MFP_I2S0_MCLK         (0x06UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< I2S0 master clock output pin. */
#define SYS_GPB_MFPH_PB9MFP_CCAP1_HSYNC       (0x07UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< Camera capture 1 interface hsync input pin. */
#define SYS_GPB_MFPH_PB9MFP_ADC0_CH1          (0x08UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< ADC0 channel 1 analog input. */
#define SYS_GPB_MFPH_PB9MFP_EBI_ALE           (0x09UL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< EBI address latch enable output pin. */
#define SYS_GPB_MFPH_PB9MFP_EBI_AD13          (0x0AUL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPB_MFPH_PB9MFP_TM0_EXT           (0x0BUL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< Timer0 event counter input / toggle output */
#define SYS_GPB_MFPH_PB9MFP_I2S1_MCLK         (0x0CUL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPB_MFPH_PB9MFP_SC0_nCD           (0x0DUL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< SmartCard0 card detect pin. */
#define SYS_GPB_MFPH_PB9MFP_QEI2_A            (0x0EUL<<SYS_GPB_MFPH_PB9MFP_Pos)  /*!< Quadrature encoder phase A input of QEI Unit 2. */
#define SYS_GPB_MFPH_PB10MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB10MFP_EPWM2_CH5        (0x01UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< EPWM2 channel5 output/capture input. */
#define SYS_GPB_MFPH_PB10MFP_UART2_RXD        (0x02UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< Data receiver input pin for UART2. */
#define SYS_GPB_MFPH_PB10MFP_CAN0_RXD         (0x03UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< CAN0 bus receiver input. */
#define SYS_GPB_MFPH_PB10MFP_USBHL2_DM        (0x04UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D-. */
#define SYS_GPB_MFPH_PB10MFP_SPI0_MOSI        (0x05UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< 1st SPI0 MOSI (Master Out, Slave In) pin. */
#define SYS_GPB_MFPH_PB10MFP_EBI_MCLK         (0x06UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< EBI external clock output pin. */
#define SYS_GPB_MFPH_PB10MFP_CCAP1_VSYNC      (0x07UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< Camera capture 1 interface vsync input pin. */
#define SYS_GPB_MFPH_PB10MFP_ADC0_CH2         (0x08UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< ADC0 channel 2 analog input. */
#define SYS_GPB_MFPH_PB10MFP_EBI_ADR15        (0x09UL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPB_MFPH_PB10MFP_EBI_AD14         (0x0AUL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPB_MFPH_PB10MFP_TM5              (0x0BUL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< Timer5 event counter input / toggle output */
#define SYS_GPB_MFPH_PB10MFP_I2C1_SDA         (0x0CUL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< I2C1 data input/output pin. */
#define SYS_GPB_MFPH_PB10MFP_INT1             (0x0DUL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< External interrupt1 input pin. */
#define SYS_GPB_MFPH_PB10MFP_QEI2_B           (0x0EUL<<SYS_GPB_MFPH_PB10MFP_Pos) /*!< Quadrature encoder phase B input of QEI Unit 2. */
#define SYS_GPB_MFPH_PB11MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB11MFP_EPWM2_BRAKE1     (0x01UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< Brake input pin 1 of EPWM2. */
#define SYS_GPB_MFPH_PB11MFP_UART2_TXD        (0x02UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< Data transmitter output pin for UART2. */
#define SYS_GPB_MFPH_PB11MFP_CAN0_TXD         (0x03UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< CAN0 bus transmitter output. */
#define SYS_GPB_MFPH_PB11MFP_USBHL2_DP        (0x04UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D+. */
#define SYS_GPB_MFPH_PB11MFP_SPI0_MISO        (0x05UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< 1st SPI0 MISO (Master In, Slave Out) pin. */
#define SYS_GPB_MFPH_PB11MFP_I2S1_MCLK        (0x06UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< I2S1 master clock output pin. */
#define SYS_GPB_MFPH_PB11MFP_CCAP1_SFIELD     (0x07UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< Camera capture 1 interface SFIELD input pin. */
#define SYS_GPB_MFPH_PB11MFP_ADC0_CH3         (0x08UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< ADC0 channel 3 analog input. */
#define SYS_GPB_MFPH_PB11MFP_EBI_nCS2         (0x09UL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< EBI chip select enable output pin. */
#define SYS_GPB_MFPH_PB11MFP_EBI_ALE          (0x0AUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< EBI address latch enable output pin. */
#define SYS_GPB_MFPH_PB11MFP_TM5_EXT          (0x0BUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< Timer5 event counter input / toggle output */
#define SYS_GPB_MFPH_PB11MFP_I2C1_SCL         (0x0CUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< I2C1 clock pin. */
#define SYS_GPB_MFPH_PB11MFP_INT2             (0x0DUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< External interrupt2 input pin. */
#define SYS_GPB_MFPH_PB11MFP_QEI2_INDEX       (0x0EUL<<SYS_GPB_MFPH_PB11MFP_Pos) /*!< Quadrature encoder index input of QEI Unit 2. */
#define SYS_GPB_MFPH_PB12MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB12MFP_EPWM2_CH0        (0x01UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< EPWM2 channel0 output/capture input. */
#define SYS_GPB_MFPH_PB12MFP_UART4_nCTS       (0x02UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< Clear to Send input pin for UART4. */
#define SYS_GPB_MFPH_PB12MFP_UART3_RXD        (0x03UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< Data receiver input pin for UART3. */
#define SYS_GPB_MFPH_PB12MFP_I2C3_SDA         (0x04UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< I2C3 data input/output pin. */
#define SYS_GPB_MFPH_PB12MFP_CAN2_RXD         (0x05UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPB_MFPH_PB12MFP_I2S1_LRCK        (0x06UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< I2S1 left right channel clock. */
#define SYS_GPB_MFPH_PB12MFP_USBHL1_DM        (0x07UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< USB 1.1 host-lite 1 differential signal D-. */
#define SYS_GPB_MFPH_PB12MFP_ADC0_CH4         (0x08UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< ADC0 channel 4 analog input. */
#define SYS_GPB_MFPH_PB12MFP_EBI_ADR16        (0x09UL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPB_MFPH_PB12MFP_ECAP2_IC0        (0x0EUL<<SYS_GPB_MFPH_PB12MFP_Pos) /*!< Input 0 of enhanced capture unit 2. */
#define SYS_GPB_MFPH_PB13MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB13MFP_EPWM2_CH1        (0x01UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< EPWM2 channel1 output/capture input. */
#define SYS_GPB_MFPH_PB13MFP_UART4_nRTS       (0x02UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< Request to Send output pin for UART4. */
#define SYS_GPB_MFPH_PB13MFP_UART3_TXD        (0x03UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< Data transmitter output pin for UART3. */
#define SYS_GPB_MFPH_PB13MFP_I2C3_SCL         (0x04UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< I2C3 clock pin. */
#define SYS_GPB_MFPH_PB13MFP_CAN2_TXD         (0x05UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< CAN2 bus transmitter output. */
#define SYS_GPB_MFPH_PB13MFP_I2S1_BCLK        (0x06UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< I2S1 bit clock pin. */
#define SYS_GPB_MFPH_PB13MFP_USBHL1_DP        (0x07UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< USB 1.1 host-lite 1 differential signal D+. */
#define SYS_GPB_MFPH_PB13MFP_ADC0_CH5         (0x08UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< ADC0 channel 5 analog input. */
#define SYS_GPB_MFPH_PB13MFP_EBI_ADR17        (0x09UL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPB_MFPH_PB13MFP_ECAP2_IC1        (0x0EUL<<SYS_GPB_MFPH_PB13MFP_Pos) /*!< Input 1 of enhanced capture unit 2. */
#define SYS_GPB_MFPH_PB14MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB14MFP_EPWM2_CH2        (0x01UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< EPWM2 channel2 output/capture input. */
#define SYS_GPB_MFPH_PB14MFP_UART4_RXD        (0x02UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< Data receiver input pin for UART4. */
#define SYS_GPB_MFPH_PB14MFP_CAN1_RXD         (0x03UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< CAN1 bus receiver input. */
#define SYS_GPB_MFPH_PB14MFP_USBHL3_DM        (0x04UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPB_MFPH_PB14MFP_I2C4_SDA         (0x05UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< I2C4 data input/output pin. */
#define SYS_GPB_MFPH_PB14MFP_I2S1_DI          (0x06UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< I2S1 data input. */
#define SYS_GPB_MFPH_PB14MFP_ADC0_CH6         (0x08UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< ADC0 channel 6 analog input. */
#define SYS_GPB_MFPH_PB14MFP_EBI_ADR18        (0x09UL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPB_MFPH_PB14MFP_ECAP2_IC2        (0x0EUL<<SYS_GPB_MFPH_PB14MFP_Pos) /*!< Input 2 of enhanced capture unit 2. */
#define SYS_GPB_MFPH_PB15MFP_GPIO             (0x00UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPB_MFPH_PB15MFP_EPWM2_CH3        (0x01UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< EPWM2 channel3 output/capture input. */
#define SYS_GPB_MFPH_PB15MFP_UART4_TXD        (0x02UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< Data transmitter output pin for UART4. */
#define SYS_GPB_MFPH_PB15MFP_CAN1_TXD         (0x03UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< CAN1 bus transmitter output. */
#define SYS_GPB_MFPH_PB15MFP_USBHL3_DP        (0x04UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPB_MFPH_PB15MFP_I2C4_SCL         (0x05UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< I2C4 clock pin. */
#define SYS_GPB_MFPH_PB15MFP_I2S1_DO          (0x06UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< I2S1 data output. */
#define SYS_GPB_MFPH_PB15MFP_ADC0_CH7         (0x08UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< ADC0 channel 7 analog input. */
#define SYS_GPB_MFPH_PB15MFP_EBI_ADR19        (0x09UL<<SYS_GPB_MFPH_PB15MFP_Pos) /*!< EBI address/data bus bit*. */
/********************* Bit definition of GPC_MFPL register **********************/
#define SYS_GPC_MFPL_PC0MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC0MFP_I2C4_SDA          (0x04UL<<SYS_GPC_MFPL_PC0MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPC_MFPL_PC0MFP_eMMC0_CMD         (0x06UL<<SYS_GPC_MFPL_PC0MFP_Pos)  /*!< eMMC0 command/response. */
#define SYS_GPC_MFPL_PC0MFP_SD0_CMD           (0x06UL<<SYS_GPC_MFPL_PC0MFP_Pos)  /*!< SD/SDIO0 command/response. */
#define SYS_GPC_MFPL_PC1MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC1MFP_I2C4_SCL          (0x04UL<<SYS_GPC_MFPL_PC1MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPC_MFPL_PC1MFP_eMMC0_CLK         (0x06UL<<SYS_GPC_MFPL_PC1MFP_Pos)  /*!< eMMC0 clock. */
#define SYS_GPC_MFPL_PC1MFP_SD0_CLK           (0x06UL<<SYS_GPC_MFPL_PC1MFP_Pos)  /*!< SD/SDIO0 clock. */
#define SYS_GPC_MFPL_PC2MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC2MFP_CAN0_RXD          (0x03UL<<SYS_GPC_MFPL_PC2MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPC_MFPL_PC2MFP_USBHL4_DM         (0x04UL<<SYS_GPC_MFPL_PC2MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPC_MFPL_PC2MFP_eMMC0_DAT0        (0x06UL<<SYS_GPC_MFPL_PC2MFP_Pos)  /*!< eMMC0 data line bit 0. */
#define SYS_GPC_MFPL_PC2MFP_SD0_DAT0          (0x06UL<<SYS_GPC_MFPL_PC2MFP_Pos)  /*!< SD/SDIO0 data line bit 0. */
#define SYS_GPC_MFPL_PC3MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC3MFP_CAN0_TXD          (0x03UL<<SYS_GPC_MFPL_PC3MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPC_MFPL_PC3MFP_USBHL4_DP         (0x04UL<<SYS_GPC_MFPL_PC3MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPC_MFPL_PC3MFP_eMMC0_DAT1        (0x06UL<<SYS_GPC_MFPL_PC3MFP_Pos)  /*!< eMMC0 data line bit 1. */
#define SYS_GPC_MFPL_PC3MFP_SD0_DAT1          (0x06UL<<SYS_GPC_MFPL_PC3MFP_Pos)  /*!< SD/SDIO0 data line bit 1. */
#define SYS_GPC_MFPL_PC4MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC4MFP_I2C5_SDA          (0x04UL<<SYS_GPC_MFPL_PC4MFP_Pos)  /*!< I2C5 data input/output pin. */
#define SYS_GPC_MFPL_PC4MFP_eMMC0_DAT2        (0x06UL<<SYS_GPC_MFPL_PC4MFP_Pos)  /*!< eMMC0 data line bit 2. */
#define SYS_GPC_MFPL_PC4MFP_SD0_DAT2          (0x06UL<<SYS_GPC_MFPL_PC4MFP_Pos)  /*!< SD/SDIO0 data line bit 2. */
#define SYS_GPC_MFPL_PC5MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC5MFP_I2C5_SCL          (0x04UL<<SYS_GPC_MFPL_PC5MFP_Pos)  /*!< I2C5 clock pin. */
#define SYS_GPC_MFPL_PC5MFP_eMMC0_DAT3        (0x06UL<<SYS_GPC_MFPL_PC5MFP_Pos)  /*!< eMMC0 data line bit 3. */
#define SYS_GPC_MFPL_PC5MFP_SD0_DAT3          (0x06UL<<SYS_GPC_MFPL_PC5MFP_Pos)  /*!< SD/SDIO0 data line bit 3. */
#define SYS_GPC_MFPL_PC6MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC6MFP_CAN1_RXD          (0x03UL<<SYS_GPC_MFPL_PC6MFP_Pos)  /*!< CAN1 bus receiver input. */
#define SYS_GPC_MFPL_PC6MFP_USBHL5_DM         (0x04UL<<SYS_GPC_MFPL_PC6MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D-. */
#define SYS_GPC_MFPL_PC6MFP_SD0_nCD           (0x06UL<<SYS_GPC_MFPL_PC6MFP_Pos)  /*!< SD/SDIO0 card detect */
#define SYS_GPC_MFPL_PC7MFP_GPIO              (0x00UL<<SYS_GPC_MFPL_PC7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPL_PC7MFP_CAN1_TXD          (0x03UL<<SYS_GPC_MFPL_PC7MFP_Pos)  /*!< CAN1 bus transmitter output. */
#define SYS_GPC_MFPL_PC7MFP_USBHL5_DP         (0x04UL<<SYS_GPC_MFPL_PC7MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D+. */
#define SYS_GPC_MFPL_PC7MFP_SD0_WP            (0x06UL<<SYS_GPC_MFPL_PC7MFP_Pos)  /*!< SD/SDIO0 write protect input. */
/********************* Bit definition of GPC_MFPH register **********************/
#define SYS_GPC_MFPH_PC8MFP_GPIO              (0x00UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC8MFP_EPWM2_CH0         (0x01UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< EPWM2 channel0 output/capture input. */
#define SYS_GPC_MFPH_PC8MFP_UART10_nCTS       (0x02UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< Clear to Send input pin for UART10. */
#define SYS_GPC_MFPH_PC8MFP_UART9_RXD         (0x03UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< Data receiver input pin for UART*. */
#define SYS_GPC_MFPH_PC8MFP_I2C0_SDA          (0x04UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< I2C0 data input/output pin. */
#define SYS_GPC_MFPH_PC8MFP_SPI1_SS0          (0x05UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< 1st SPI1 slave select pin. */
#define SYS_GPC_MFPH_PC8MFP_eMMC0_DAT4        (0x06UL<<SYS_GPC_MFPH_PC8MFP_Pos)  /*!< eMMC0 data line bit 4. */
#define SYS_GPC_MFPH_PC9MFP_GPIO              (0x00UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC9MFP_EPWM2_CH1         (0x01UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< EPWM2 channel1 output/capture input. */
#define SYS_GPC_MFPH_PC9MFP_UART10_nRTS       (0x02UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< Request to Send output pin for UART10. */
#define SYS_GPC_MFPH_PC9MFP_UART9_TXD         (0x03UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< Data transmitter output pin for UART*. */
#define SYS_GPC_MFPH_PC9MFP_I2C0_SCL          (0x04UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< I2C0 clock pin. */
#define SYS_GPC_MFPH_PC9MFP_SPI1_CLK          (0x05UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< SPI1 serial clock pin. */
#define SYS_GPC_MFPH_PC9MFP_eMMC0_DAT5        (0x06UL<<SYS_GPC_MFPH_PC9MFP_Pos)  /*!< eMMC0 data line bit 5. */
#define SYS_GPC_MFPH_PC10MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC10MFP_EPWM2_CH2        (0x01UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< EPWM2 channel2 output/capture input. */
#define SYS_GPC_MFPH_PC10MFP_UART10_RXD       (0x02UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< Data receiver input pin for UART10. */
#define SYS_GPC_MFPH_PC10MFP_CAN2_RXD         (0x03UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPC_MFPH_PC10MFP_USBHL0_DM        (0x04UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPC_MFPH_PC10MFP_SPI1_MOSI        (0x05UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< 1st SPI1 MOSI (Master Out, Slave In) pin. */
#define SYS_GPC_MFPH_PC10MFP_eMMC0_DAT6       (0x06UL<<SYS_GPC_MFPH_PC10MFP_Pos) /*!< eMMC0 data line bit 6. */
#define SYS_GPC_MFPH_PC11MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC11MFP_EPWM2_CH3        (0x01UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< EPWM2 channel3 output/capture input. */
#define SYS_GPC_MFPH_PC11MFP_UART10_TXD       (0x02UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< Data transmitter output pin for UART10. */
#define SYS_GPC_MFPH_PC11MFP_CAN2_TXD         (0x03UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< CAN2 bus transmitter output. */
#define SYS_GPC_MFPH_PC11MFP_USBHL0_DP        (0x04UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPC_MFPH_PC11MFP_SPI1_MISO        (0x05UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< 1st SPI1 MISO (Master In, Slave Out) pin. */
#define SYS_GPC_MFPH_PC11MFP_eMMC0_DAT7       (0x06UL<<SYS_GPC_MFPH_PC11MFP_Pos) /*!< eMMC0 data line bit 7. */
#define SYS_GPC_MFPH_PC12MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC12MFP_UART12_nCTS      (0x02UL<<SYS_GPC_MFPH_PC12MFP_Pos) /*!< Clear to Send input pin for UART12. */
#define SYS_GPC_MFPH_PC12MFP_UART11_RXD       (0x03UL<<SYS_GPC_MFPH_PC12MFP_Pos) /*!< Data receiver input pin for UART11. */
#define SYS_GPC_MFPH_PC12MFP_LCM_DATA16       (0x06UL<<SYS_GPC_MFPH_PC12MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPC_MFPH_PC13MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC13MFP_UART12_nRTS      (0x02UL<<SYS_GPC_MFPH_PC13MFP_Pos) /*!< Request to Send output pin for UART12. */
#define SYS_GPC_MFPH_PC13MFP_UART11_TXD       (0x03UL<<SYS_GPC_MFPH_PC13MFP_Pos) /*!< Data transmitter output pin for UART11. */
#define SYS_GPC_MFPH_PC13MFP_LCM_DATA17       (0x06UL<<SYS_GPC_MFPH_PC13MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPC_MFPH_PC13MFP_LCM_MPU_DATA17   (0x06UL<<SYS_GPC_MFPH_PC13MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPC_MFPH_PC14MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC14MFP_UART12_RXD       (0x02UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< Data receiver input pin for UART12. */
#define SYS_GPC_MFPH_PC14MFP_LCM_DATA18       (0x06UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPC_MFPH_PC14MFP_LCM_MPU_CSX      (0x06UL<<SYS_GPC_MFPH_PC14MFP_Pos) /*!< TFT LCD Module Chip Selection output pin in MPU-type 80/68 mode. */
#define SYS_GPC_MFPH_PC15MFP_GPIO             (0x00UL<<SYS_GPC_MFPH_PC15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPC_MFPH_PC15MFP_UART12_TXD       (0x02UL<<SYS_GPC_MFPH_PC15MFP_Pos) /*!< Data transmitter output pin for UART12. */
#define SYS_GPC_MFPH_PC15MFP_LCM_DATA19       (0x06UL<<SYS_GPC_MFPH_PC15MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPC_MFPH_PC15MFP_LCM_MPU_TE       (0x07UL<<SYS_GPC_MFPH_PC15MFP_Pos) /*!< TFT LCD Module TE input pin in MPU-type mode. */
#define SYS_GPC_MFPH_PC15MFP_LCM_MPU_VSYNC    (0x08UL<<SYS_GPC_MFPH_PC15MFP_Pos) /*!< TFT LCD Module VSYNC output pin in MPU-type mode. */
/********************* Bit definition of GPD_MFPL register **********************/
#define SYS_GPD_MFPL_PD0MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD0MFP_UART3_nCTS        (0x02UL<<SYS_GPD_MFPL_PD0MFP_Pos)  /*!< Clear to Send input pin for UART3. */
#define SYS_GPD_MFPL_PD0MFP_UART4_RXD         (0x03UL<<SYS_GPD_MFPL_PD0MFP_Pos)  /*!< Data receiver input pin for UART4. */
#define SYS_GPD_MFPL_PD0MFP_QSPI0_SS0         (0x05UL<<SYS_GPD_MFPL_PD0MFP_Pos)  /*!< Quad SPI0 slave select pin. */
#define SYS_GPD_MFPL_PD1MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD1MFP_UART3_nRTS        (0x02UL<<SYS_GPD_MFPL_PD1MFP_Pos)  /*!< Request to Send output pin for UART3. */
#define SYS_GPD_MFPL_PD1MFP_UART4_TXD         (0x03UL<<SYS_GPD_MFPL_PD1MFP_Pos)  /*!< Data transmitter output pin for UART4. */
#define SYS_GPD_MFPL_PD1MFP_QSPI0_CLK         (0x05UL<<SYS_GPD_MFPL_PD1MFP_Pos)  /*!< Quad SPI0 serial clock pin. */
#define SYS_GPD_MFPL_PD2MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD2MFP_UART3_RXD         (0x02UL<<SYS_GPD_MFPL_PD2MFP_Pos)  /*!< Data receiver input pin for UART3. */
#define SYS_GPD_MFPL_PD2MFP_QSPI0_MOSI0       (0x05UL<<SYS_GPD_MFPL_PD2MFP_Pos)  /*!< Quad SPI0 MOSI0 (Master Out, Slave In) pin. */
#define SYS_GPD_MFPL_PD3MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD3MFP_UART3_TXD         (0x02UL<<SYS_GPD_MFPL_PD3MFP_Pos)  /*!< Data transmitter output pin for UART3. */
#define SYS_GPD_MFPL_PD3MFP_QSPI0_MISO0       (0x05UL<<SYS_GPD_MFPL_PD3MFP_Pos)  /*!< Quad SPI0 MISO0 (Master In, Slave Out) pin. */
#define SYS_GPD_MFPL_PD4MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD4MFP_UART1_nCTS        (0x02UL<<SYS_GPD_MFPL_PD4MFP_Pos)  /*!< Clear to Send input pin for UART1. */
#define SYS_GPD_MFPL_PD4MFP_UART2_RXD         (0x03UL<<SYS_GPD_MFPL_PD4MFP_Pos)  /*!< Data receiver input pin for UART2. */
#define SYS_GPD_MFPL_PD4MFP_I2C2_SDA          (0x04UL<<SYS_GPD_MFPL_PD4MFP_Pos)  /*!< I2C2 data input/output pin. */
#define SYS_GPD_MFPL_PD4MFP_QSPI0_MOSI1       (0x05UL<<SYS_GPD_MFPL_PD4MFP_Pos)  /*!< Quad SPI0 MOSI1 (Master Out, Slave In) pin. */
#define SYS_GPD_MFPL_PD5MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD5MFP_UART1_nRTS        (0x02UL<<SYS_GPD_MFPL_PD5MFP_Pos)  /*!< Request to Send output pin for UART1. */
#define SYS_GPD_MFPL_PD5MFP_UART2_TXD         (0x03UL<<SYS_GPD_MFPL_PD5MFP_Pos)  /*!< Data transmitter output pin for UART2. */
#define SYS_GPD_MFPL_PD5MFP_I2C2_SCL          (0x04UL<<SYS_GPD_MFPL_PD5MFP_Pos)  /*!< I2C2 clock pin. */
#define SYS_GPD_MFPL_PD5MFP_QSPI0_MISO1       (0x05UL<<SYS_GPD_MFPL_PD5MFP_Pos)  /*!< Quad SPI0 MISO1 (Master In, Slave Out) pin. */
#define SYS_GPD_MFPL_PD6MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD6MFP_EPWM0_SYNC_IN     (0x01UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< EPWM0 counter synchronous trigger input pin. */
#define SYS_GPD_MFPL_PD6MFP_UART1_RXD         (0x02UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< Data receiver input pin for UART1. */
#define SYS_GPD_MFPL_PD6MFP_USBHL3_DM         (0x04UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPD_MFPL_PD6MFP_QSPI1_MOSI1       (0x05UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< Quad SPI1 MOSI1 (Master Out, Slave In) pin. */
#define SYS_GPD_MFPL_PD6MFP_I2C0_SDA          (0x06UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< I2C0 data input/output pin. */
#define SYS_GPD_MFPL_PD6MFP_I2S0_MCLK         (0x07UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< I2S0 master clock output pin. */
#define SYS_GPD_MFPL_PD6MFP_EPWM0_CH0         (0x08UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< EPWM0 channel0 output/capture input. */
#define SYS_GPD_MFPL_PD6MFP_EBI_AD5           (0x09UL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< EBI address/data bus bit5. */
#define SYS_GPD_MFPL_PD6MFP_SPI3_SS1          (0x0AUL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< 1st SPI3 slave select pin. */
#define SYS_GPD_MFPL_PD6MFP_TRACE_CLK         (0x0BUL<<SYS_GPD_MFPL_PD6MFP_Pos)  /*!< ETM Rx clock input pin. */
#define SYS_GPD_MFPL_PD7MFP_GPIO              (0x00UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPL_PD7MFP_EPWM0_SYNC_OUT    (0x01UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< EPWM0 counter synchronous trigger output pin. */
#define SYS_GPD_MFPL_PD7MFP_UART1_TXD         (0x02UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< Data transmitter output pin for UART1. */
#define SYS_GPD_MFPL_PD7MFP_USBHL3_DP         (0x04UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPD_MFPL_PD7MFP_QSPI1_MISO1       (0x05UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< Quad SPI1 MISO1 (Master In, Slave Out) pin. */
#define SYS_GPD_MFPL_PD7MFP_I2C0_SCL          (0x06UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< I2C0 clock pin. */
#define SYS_GPD_MFPL_PD7MFP_I2S1_MCLK         (0x07UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPD_MFPL_PD7MFP_EPWM0_CH1         (0x08UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< EPWM0 channel1 output/capture input. */
#define SYS_GPD_MFPL_PD7MFP_EBI_AD6           (0x09UL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< EBI address/data bus bit6. */
#define SYS_GPD_MFPL_PD7MFP_SC1_nCD           (0x0AUL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< SmartCard1 card detect pin. */
#define SYS_GPD_MFPL_PD7MFP_EADC0_ST          (0x0BUL<<SYS_GPD_MFPL_PD7MFP_Pos)  /*!< EADC external trigger input. */
/********************* Bit definition of GPD_MFPH register **********************/
#define SYS_GPD_MFPH_PD8MFP_GPIO              (0x00UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD8MFP_EPWM0_BRAKE0      (0x01UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< Brake input pin 0 of EPWM0. */
#define SYS_GPD_MFPH_PD8MFP_UART16_nCTS       (0x02UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< Clear to Send input pin for UART16. */
#define SYS_GPD_MFPH_PD8MFP_UART15_RXD        (0x03UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< Data receiver input pin for UART15. */
#define SYS_GPD_MFPH_PD8MFP_QSPI1_SS0         (0x05UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< Quad SPI1 slave select pin. */
#define SYS_GPD_MFPH_PD8MFP_I2S1_LRCK         (0x07UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< I2S1 left right channel clock. */
#define SYS_GPD_MFPH_PD8MFP_EPWM0_CH2         (0x08UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPD_MFPH_PD8MFP_EBI_AD7           (0x09UL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPD_MFPH_PD8MFP_SC1_CLK           (0x0AUL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< SmartCard1 clock pin. */
#define SYS_GPD_MFPH_PD8MFP_TM0               (0x0BUL<<SYS_GPD_MFPH_PD8MFP_Pos)  /*!< Timer0 event counter input / toggle output */
#define SYS_GPD_MFPH_PD9MFP_GPIO              (0x00UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD9MFP_EPWM0_BRAKE1      (0x01UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< Brake input pin 1 of EPWM0. */
#define SYS_GPD_MFPH_PD9MFP_UART16_nRTS       (0x02UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< Request to Send output pin for UART16. */
#define SYS_GPD_MFPH_PD9MFP_UART15_TXD        (0x03UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< Data transmitter output pin for UART15. */
#define SYS_GPD_MFPH_PD9MFP_QSPI1_CLK         (0x05UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< Quad SPI1 serial clock pin. */
#define SYS_GPD_MFPH_PD9MFP_I2S1_BCLK         (0x07UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< I2S1 bit clock pin. */
#define SYS_GPD_MFPH_PD9MFP_EPWM0_CH3         (0x08UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< EPWM0 channel3 output/capture input. */
#define SYS_GPD_MFPH_PD9MFP_EBI_AD8           (0x09UL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPD_MFPH_PD9MFP_SC1_DAT           (0x0AUL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< SmartCard1 data pin. */
#define SYS_GPD_MFPH_PD9MFP_TM0_EXT           (0x0BUL<<SYS_GPD_MFPH_PD9MFP_Pos)  /*!< Timer0 event counter input / toggle output */
#define SYS_GPD_MFPH_PD10MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD10MFP_EPWM1_BRAKE0     (0x01UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< Brake input pin 0 of EPWM1. */
#define SYS_GPD_MFPH_PD10MFP_UART16_RXD       (0x02UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< Data receiver input pin for UART16. */
#define SYS_GPD_MFPH_PD10MFP_QSPI1_MOSI0      (0x05UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< Quad SPI1 MOSI0 (Master Out, Slave In) pin. */
#define SYS_GPD_MFPH_PD10MFP_I2S1_DI          (0x07UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< I2S1 data input. */
#define SYS_GPD_MFPH_PD10MFP_EPWM0_CH4        (0x08UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< EPWM0 channel4 output/capture input. */
#define SYS_GPD_MFPH_PD10MFP_EBI_AD9          (0x09UL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< EBI address/data bus bit9. */
#define SYS_GPD_MFPH_PD10MFP_SC1_RST          (0x0AUL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< SmartCard1 reset pin. */
#define SYS_GPD_MFPH_PD10MFP_TM2              (0x0BUL<<SYS_GPD_MFPH_PD10MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPD_MFPH_PD11MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD11MFP_EPWM1_BRAKE1     (0x01UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< Brake input pin 1 of EPWM1. */
#define SYS_GPD_MFPH_PD11MFP_UART16_TXD       (0x02UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< Data transmitter output pin for UART16. */
#define SYS_GPD_MFPH_PD11MFP_QSPI1_MISO0      (0x05UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< Quad SPI1 MISO0 (Master In, Slave Out) pin. */
#define SYS_GPD_MFPH_PD11MFP_I2S1_DO          (0x07UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< I2S1 data output. */
#define SYS_GPD_MFPH_PD11MFP_EPWM0_CH5        (0x08UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< EPWM0 channel5 output/capture input. */
#define SYS_GPD_MFPH_PD11MFP_EBI_AD10         (0x09UL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPD_MFPH_PD11MFP_SC1_PWR          (0x0AUL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< SmartCard1 power pin. */
#define SYS_GPD_MFPH_PD11MFP_TM2_EXT          (0x0BUL<<SYS_GPD_MFPH_PD11MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPD_MFPH_PD12MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD12MFP_EPWM0_BRAKE0     (0x01UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< Brake input pin 0 of EPWM0. */
#define SYS_GPD_MFPH_PD12MFP_UART11_TXD       (0x02UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< Data transmitter output pin for UART11. */
#define SYS_GPD_MFPH_PD12MFP_UART10_RXD       (0x03UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< Data receiver input pin for UART10. */
#define SYS_GPD_MFPH_PD12MFP_I2C4_SDA         (0x04UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< I2C4 data input/output pin. */
#define SYS_GPD_MFPH_PD12MFP_TRACE_DATA0      (0x06UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< ETM Rx input bus bit0. */
#define SYS_GPD_MFPH_PD12MFP_EBI_nCS1         (0x07UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< EBI chip select enable output pin. */
#define SYS_GPD_MFPH_PD12MFP_EBI_AD4          (0x08UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< EBI address/data bus bit4. */
#define SYS_GPD_MFPH_PD12MFP_QEI0_INDEX       (0x09UL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< Quadrature encoder index input of QEI Unit 0. */
#define SYS_GPD_MFPH_PD12MFP_TM5              (0x0BUL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< Timer5 event counter input / toggle output */
#define SYS_GPD_MFPH_PD12MFP_I2S1_LRCK        (0x0CUL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< I2S1 left right channel clock. */
#define SYS_GPD_MFPH_PD12MFP_INT1             (0x0DUL<<SYS_GPD_MFPH_PD12MFP_Pos) /*!< External interrupt1 input pin. */
#define SYS_GPD_MFPH_PD13MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD13MFP_EPWM0_BRAKE1     (0x01UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< Brake input pin 1 of EPWM0. */
#define SYS_GPD_MFPH_PD13MFP_UART11_RXD       (0x02UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< Data receiver input pin for UART11. */
#define SYS_GPD_MFPH_PD13MFP_UART10_TXD       (0x03UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< Data transmitter output pin for UART10. */
#define SYS_GPD_MFPH_PD13MFP_I2C4_SCL         (0x04UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< I2C4 clock pin. */
#define SYS_GPD_MFPH_PD13MFP_TRACE_DATA1      (0x06UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< ETM Rx input bus bit1. */
#define SYS_GPD_MFPH_PD13MFP_EBI_nCS2         (0x07UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< EBI chip select enable output pin. */
#define SYS_GPD_MFPH_PD13MFP_EBI_AD5          (0x08UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< EBI address/data bus bit5. */
#define SYS_GPD_MFPH_PD13MFP_ECAP0_IC0        (0x09UL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< Input 0 of enhanced capture unit 0. */
#define SYS_GPD_MFPH_PD13MFP_TM5_EXT          (0x0BUL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< Timer5 event counter input / toggle output */
#define SYS_GPD_MFPH_PD13MFP_I2S1_BCLK        (0x0CUL<<SYS_GPD_MFPH_PD13MFP_Pos) /*!< I2S1 bit clock pin. */
#define SYS_GPD_MFPH_PD14MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD14MFP_EPWM0_SYNC_IN    (0x01UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< EPWM0 counter synchronous trigger input pin. */
#define SYS_GPD_MFPH_PD14MFP_UART11_nCTS      (0x02UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< Clear to Send input pin for UART11. */
#define SYS_GPD_MFPH_PD14MFP_CAN3_RXD         (0x03UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPD_MFPH_PD14MFP_USBHL5_DM        (0x04UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< USB 1.1 host-lite 5 differential signal D-. */
#define SYS_GPD_MFPH_PD14MFP_TRACE_DATA2      (0x06UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< ETM Rx input bus bit2. */
#define SYS_GPD_MFPH_PD14MFP_EBI_MCLK         (0x07UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< EBI external clock output pin. */
#define SYS_GPD_MFPH_PD14MFP_EBI_AD6          (0x08UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< EBI address/data bus bit6. */
#define SYS_GPD_MFPH_PD14MFP_ECAP0_IC1        (0x09UL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< Input 1 of enhanced capture unit 0. */
#define SYS_GPD_MFPH_PD14MFP_TM6              (0x0BUL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< Timer6 event counter input / toggle output */
#define SYS_GPD_MFPH_PD14MFP_I2S1_DI          (0x0CUL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< I2S1 data input. */
#define SYS_GPD_MFPH_PD14MFP_INT3             (0x0DUL<<SYS_GPD_MFPH_PD14MFP_Pos) /*!< External interrupt3 input pin. */
#define SYS_GPD_MFPH_PD15MFP_GPIO             (0x00UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPD_MFPH_PD15MFP_EPWM0_SYNC_OUT   (0x01UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< EPWM0 counter synchronous trigger output pin. */
#define SYS_GPD_MFPH_PD15MFP_UART11_nRTS      (0x02UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< Request to Send output pin for UART11. */
#define SYS_GPD_MFPH_PD15MFP_CAN3_TXD         (0x03UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< CAN3 bus transmitter output. */
#define SYS_GPD_MFPH_PD15MFP_USBHL5_DP        (0x04UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< USB 1.1 host-lite 5 differential signal D+. */
#define SYS_GPD_MFPH_PD15MFP_TRACE_DATA3      (0x06UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< ETM Rx input bus bit3. */
#define SYS_GPD_MFPH_PD15MFP_EBI_ALE          (0x07UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< EBI address latch enable output pin. */
#define SYS_GPD_MFPH_PD15MFP_EBI_AD7          (0x08UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< EBI address/data bus bit7. */
#define SYS_GPD_MFPH_PD15MFP_ECAP0_IC2        (0x09UL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< Input 0 of enhanced capture unit 2. */
#define SYS_GPD_MFPH_PD15MFP_TM6_EXT          (0x0BUL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< Timer6 event counter input / toggle output */
#define SYS_GPD_MFPH_PD15MFP_I2S1_DO          (0x0CUL<<SYS_GPD_MFPH_PD15MFP_Pos) /*!< I2S1 data output. */
/********************* Bit definition of GPE_MFPL register **********************/
#define SYS_GPE_MFPL_PE0MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE0MFP_UART9_nCTS        (0x02UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< Clear to Send input pin for UART*. */
#define SYS_GPE_MFPL_PE0MFP_UART8_RXD         (0x03UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< Data receiver input pin for UART8. */
#define SYS_GPE_MFPL_PE0MFP_CCAP1_DATA0       (0x07UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< Camera capture 1 data input bus bit 0. */
#define SYS_GPE_MFPL_PE0MFP_RGMII0_MDC        (0x08UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< RGMII0 Management Data Clock. */
#define SYS_GPE_MFPL_PE0MFP_RMII0_MDC         (0x09UL<<SYS_GPE_MFPL_PE0MFP_Pos)  /*!< RMII0 PHY Management Clock output pin. */
#define SYS_GPE_MFPL_PE1MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE1MFP_UART9_nRTS        (0x02UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< Request to Send output pin for UART*. */
#define SYS_GPE_MFPL_PE1MFP_UART8_TXD         (0x03UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< Data transmitter output pin for UART8. */
#define SYS_GPE_MFPL_PE1MFP_CCAP1_DATA1       (0x07UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< Camera capture 1 data input bus bit 1. */
#define SYS_GPE_MFPL_PE1MFP_RGMII0_MDIO       (0x08UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< RGMII0 PHY Management Data pin. */
#define SYS_GPE_MFPL_PE1MFP_RMII0_MDIO        (0x09UL<<SYS_GPE_MFPL_PE1MFP_Pos)  /*!< RMII0 PHY Management Data pin. */
#define SYS_GPE_MFPL_PE2MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE2MFP_UART9_RXD         (0x02UL<<SYS_GPE_MFPL_PE2MFP_Pos)  /*!< Data receiver input pin for UART*. */
#define SYS_GPE_MFPL_PE2MFP_CCAP1_DATA2       (0x07UL<<SYS_GPE_MFPL_PE2MFP_Pos)  /*!< Camera capture 1 data input bus bit 2. */
#define SYS_GPE_MFPL_PE2MFP_RGMII0_TXCTL      (0x08UL<<SYS_GPE_MFPL_PE2MFP_Pos)  /*!< RGMII0 Transmit Control output pin. */
#define SYS_GPE_MFPL_PE2MFP_RMII0_TXEN        (0x09UL<<SYS_GPE_MFPL_PE2MFP_Pos)  /*!< RMII0 Transmit Enable output pin. */
#define SYS_GPE_MFPL_PE3MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE3MFP_UART9_TXD         (0x02UL<<SYS_GPE_MFPL_PE3MFP_Pos)  /*!< Data transmitter output pin for UART*. */
#define SYS_GPE_MFPL_PE3MFP_CCAP1_DATA3       (0x07UL<<SYS_GPE_MFPL_PE3MFP_Pos)  /*!< Camera capture 1 data input bus bit 3. */
#define SYS_GPE_MFPL_PE3MFP_RGMII0_TXD0       (0x08UL<<SYS_GPE_MFPL_PE3MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 0. */
#define SYS_GPE_MFPL_PE3MFP_RMII0_TXD0        (0x09UL<<SYS_GPE_MFPL_PE3MFP_Pos)  /*!< RMII0 Transmit Data bus bit 0. */
#define SYS_GPE_MFPL_PE4MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE4MFP_UART4_nCTS        (0x02UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< Clear to Send input pin for UART4. */
#define SYS_GPE_MFPL_PE4MFP_UART3_RXD         (0x03UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< Data receiver input pin for UART3. */
#define SYS_GPE_MFPL_PE4MFP_CCAP1_DATA4       (0x07UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< Camera capture 1 data input bus bit 4. */
#define SYS_GPE_MFPL_PE4MFP_RGMII0_TXD1       (0x08UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 1. */
#define SYS_GPE_MFPL_PE4MFP_RMII0_TXD1        (0x09UL<<SYS_GPE_MFPL_PE4MFP_Pos)  /*!< RMII0 Transmit Data bus bit 1. */
#define SYS_GPE_MFPL_PE5MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE5MFP_UART4_nRTS        (0x02UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< Request to Send output pin for UART4. */
#define SYS_GPE_MFPL_PE5MFP_UART3_TXD         (0x03UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< Data transmitter output pin for UART3. */
#define SYS_GPE_MFPL_PE5MFP_CCAP1_DATA5       (0x07UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< Camera capture 1 data input bus bit 5. */
#define SYS_GPE_MFPL_PE5MFP_RGMII0_RXCLK      (0x08UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< RGMII0 Mode RX Clock input pin. */
#define SYS_GPE_MFPL_PE5MFP_RMII0_REFCLK      (0x09UL<<SYS_GPE_MFPL_PE5MFP_Pos)  /*!< RMII0 Reference Clock input pin. */
#define SYS_GPE_MFPL_PE6MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE6MFP_UART4_RXD         (0x02UL<<SYS_GPE_MFPL_PE6MFP_Pos)  /*!< Data receiver input pin for UART4. */
#define SYS_GPE_MFPL_PE6MFP_CCAP1_DATA6       (0x07UL<<SYS_GPE_MFPL_PE6MFP_Pos)  /*!< Camera capture 1 data input bus bit 6. */
#define SYS_GPE_MFPL_PE6MFP_RGMII0_RXCTL      (0x08UL<<SYS_GPE_MFPL_PE6MFP_Pos)  /*!< RGMII0 Receive Control input pin. */
#define SYS_GPE_MFPL_PE6MFP_RMII0_CRSDV       (0x09UL<<SYS_GPE_MFPL_PE6MFP_Pos)  /*!< RMII0 Carrier Sense/Receive Data input pin. */
#define SYS_GPE_MFPL_PE7MFP_GPIO              (0x00UL<<SYS_GPE_MFPL_PE7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPL_PE7MFP_UART4_TXD         (0x02UL<<SYS_GPE_MFPL_PE7MFP_Pos)  /*!< Data transmitter output pin for UART4. */
#define SYS_GPE_MFPL_PE7MFP_CCAP1_DATA7       (0x07UL<<SYS_GPE_MFPL_PE7MFP_Pos)  /*!< Camera capture 1 data input bus bit 7. */
#define SYS_GPE_MFPL_PE7MFP_RGMII0_RXD0       (0x08UL<<SYS_GPE_MFPL_PE7MFP_Pos)  /*!< RGMII0 Receive Data bus bit 0. */
#define SYS_GPE_MFPL_PE7MFP_RMII0_RXD0        (0x09UL<<SYS_GPE_MFPL_PE7MFP_Pos)  /*!< RMII0 Receive Data bus bit 0. */
/********************* Bit definition of GPE_MFPH register **********************/
#define SYS_GPE_MFPH_PE8MFP_GPIO              (0x00UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE8MFP_UART13_nCTS       (0x02UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< Clear to Send input pin for UART13. */
#define SYS_GPE_MFPH_PE8MFP_UART12_RXD        (0x03UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< Data receiver input pin for UART12. */
#define SYS_GPE_MFPH_PE8MFP_CCAP1_SCLK        (0x07UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< Camera capture 1 interface sensor clock output pin. */
#define SYS_GPE_MFPH_PE8MFP_RGMII0_RXD1       (0x08UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< RGMII0 Receive Data bus bit 1. */
#define SYS_GPE_MFPH_PE8MFP_RMII0_RXD1        (0x09UL<<SYS_GPE_MFPH_PE8MFP_Pos)  /*!< RMII0 Receive Data bus bit 1. */
#define SYS_GPE_MFPH_PE9MFP_GPIO              (0x00UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE9MFP_UART13_nRTS       (0x02UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< Request to Send output pin for UART13. */
#define SYS_GPE_MFPH_PE9MFP_UART12_TXD        (0x03UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< Data transmitter output pin for UART12. */
#define SYS_GPE_MFPH_PE9MFP_CCAP1_PIXCLK      (0x07UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< Camera capture 1 interface pixel clock input pin. */
#define SYS_GPE_MFPH_PE9MFP_RGMII0_RXD2       (0x08UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< RGMII0 Receive Data bus bit 2. */
#define SYS_GPE_MFPH_PE9MFP_RMII0_RXERR       (0x09UL<<SYS_GPE_MFPH_PE9MFP_Pos)  /*!< RMII0 Receive Data Error input pin. */
#define SYS_GPE_MFPH_PE10MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE10MFP_UART15_nCTS      (0x02UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< Clear to Send input pin for UART15. */
#define SYS_GPE_MFPH_PE10MFP_UART14_RXD       (0x03UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< Data receiver input pin for UART14. */
#define SYS_GPE_MFPH_PE10MFP_SPI1_SS0         (0x05UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPE_MFPH_PE10MFP_CCAP1_HSYNC      (0x07UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< Camera capture 1 interface hsync input pin. */
#define SYS_GPE_MFPH_PE10MFP_RGMII0_RXD3      (0x08UL<<SYS_GPE_MFPH_PE10MFP_Pos) /*!< RGMII0 Receive Data bus bit 3. */
#define SYS_GPE_MFPH_PE11MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE11MFP_UART15_nRTS      (0x02UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< Request to Send output pin for UART15. */
#define SYS_GPE_MFPH_PE11MFP_UART14_TXD       (0x03UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< Data transmitter output pin for UART14. */
#define SYS_GPE_MFPH_PE11MFP_SPI1_CLK         (0x05UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< SPI1 serial clock pin. */
#define SYS_GPE_MFPH_PE11MFP_CCAP1_VSYNC      (0x07UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< Camera capture 1 interface vsync input pin. */
#define SYS_GPE_MFPH_PE11MFP_RGMII0_TXCLK     (0x08UL<<SYS_GPE_MFPH_PE11MFP_Pos) /*!< RGMII0 Mode TX Clock output pin. */
#define SYS_GPE_MFPH_PE12MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE12MFP_UART15_RXD       (0x02UL<<SYS_GPE_MFPH_PE12MFP_Pos) /*!< Data receiver input pin for UART15. */
#define SYS_GPE_MFPH_PE12MFP_SPI1_MOSI        (0x05UL<<SYS_GPE_MFPH_PE12MFP_Pos) /*!< 1st SPI1 MOSI (Master Out, Slave In) pin. */
#define SYS_GPE_MFPH_PE12MFP_CCAP1_DATA8      (0x07UL<<SYS_GPE_MFPH_PE12MFP_Pos) /*!< Camera capture 1 data input bus bit 8. */
#define SYS_GPE_MFPH_PE12MFP_RGMII0_TXD2      (0x08UL<<SYS_GPE_MFPH_PE12MFP_Pos) /*!< MII/RMII Transmit Data bus bit 2. */
#define SYS_GPE_MFPH_PE13MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE13MFP_UART15_TXD       (0x02UL<<SYS_GPE_MFPH_PE13MFP_Pos) /*!< Data transmitter output pin for UART15. */
#define SYS_GPE_MFPH_PE13MFP_SPI1_MISO        (0x05UL<<SYS_GPE_MFPH_PE13MFP_Pos) /*!< 1st SPI1 MISO (Master In, Slave Out) pin. */
#define SYS_GPE_MFPH_PE13MFP_CCAP1_DATA9      (0x07UL<<SYS_GPE_MFPH_PE13MFP_Pos) /*!< Camera capture 1 data input bus bit 9. */
#define SYS_GPE_MFPH_PE13MFP_RGMII0_TXD3      (0x08UL<<SYS_GPE_MFPH_PE13MFP_Pos) /*!< MII/RMII Transmit Data bus bit 3. */
#define SYS_GPE_MFPH_PE14MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE14MFP_UART0_TXD        (0x01UL<<SYS_GPE_MFPH_PE14MFP_Pos) /*!< Data transmitter output pin for UART0. */
#define SYS_GPE_MFPH_PE15MFP_GPIO             (0x00UL<<SYS_GPE_MFPH_PE15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPE_MFPH_PE15MFP_UART0_RXD        (0x01UL<<SYS_GPE_MFPH_PE15MFP_Pos) /*!< Data receiver input pin for UART0. */
/********************* Bit definition of GPF_MFPL register **********************/
#define SYS_GPF_MFPL_PF0MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF0MFP_UART2_nCTS        (0x02UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< Clear to Send input pin for UART2. */
#define SYS_GPF_MFPL_PF0MFP_UART1_RXD         (0x03UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< Data receiver input pin for UART1. */
#define SYS_GPF_MFPL_PF0MFP_RGMII0_RXD3       (0x06UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< RGMII0 Receive Data bus bit 3. */
#define SYS_GPF_MFPL_PF0MFP_RGMII1_MDC        (0x08UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< RGMII1 Management Data Clock. */
#define SYS_GPF_MFPL_PF0MFP_RMII1_MDC         (0x09UL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< RMII1 PHY Management Clock output pin. */
#define SYS_GPF_MFPL_PF0MFP_KPI_COL0          (0x0EUL<<SYS_GPF_MFPL_PF0MFP_Pos)  /*!< Keypad Interface Column 0 output pin. */
#define SYS_GPF_MFPL_PF1MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF1MFP_UART2_nRTS        (0x02UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< Request to Send output pin for UART2. */
#define SYS_GPF_MFPL_PF1MFP_UART1_TXD         (0x03UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< Data transmitter output pin for UART1. */
#define SYS_GPF_MFPL_PF1MFP_RGMII0_TXCLK      (0x06UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< RGMII0 Mode TX Clock output pin. */
#define SYS_GPF_MFPL_PF1MFP_RGMII1_MDIO       (0x08UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< RGMII1 PHY Management Data pin. */
#define SYS_GPF_MFPL_PF1MFP_RMII1_MDIO        (0x09UL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< RMII1 PHY Management Data pin. */
#define SYS_GPF_MFPL_PF1MFP_KPI_COL1          (0x0EUL<<SYS_GPF_MFPL_PF1MFP_Pos)  /*!< Keypad Interface Column 1 output pin. */
#define SYS_GPF_MFPL_PF2MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF2MFP_UART2_RXD         (0x02UL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< Data receiver input pin for UART2. */
#define SYS_GPF_MFPL_PF2MFP_RGMII0_TXD2       (0x06UL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 2. */
#define SYS_GPF_MFPL_PF2MFP_RGMII1_TXCTL      (0x08UL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< RGMII1 Transmit Control output pin. */
#define SYS_GPF_MFPL_PF2MFP_RMII1_TXEN        (0x09UL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< RMII1 Transmit Enable output pin. */
#define SYS_GPF_MFPL_PF2MFP_KPI_COL2          (0x0EUL<<SYS_GPF_MFPL_PF2MFP_Pos)  /*!< Keypad Interface Column 2 output pin. */
#define SYS_GPF_MFPL_PF3MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF3MFP_UART2_TXD         (0x02UL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< Data transmitter output pin for UART2. */
#define SYS_GPF_MFPL_PF3MFP_RGMII0_TXD3       (0x06UL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 3. */
#define SYS_GPF_MFPL_PF3MFP_RGMII1_TXD0       (0x08UL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 0. */
#define SYS_GPF_MFPL_PF3MFP_RMII1_TXD0        (0x09UL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< RMII1 Transmit Data bus bit 0. */
#define SYS_GPF_MFPL_PF3MFP_KPI_COL3          (0x0EUL<<SYS_GPF_MFPL_PF3MFP_Pos)  /*!< Keypad Interface Column 3 output pin. */
#define SYS_GPF_MFPL_PF4MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF4MFP_UART11_nCTS       (0x02UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< Clear to Send input pin for UART11. */
#define SYS_GPF_MFPL_PF4MFP_UART10_RXD        (0x03UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< Data receiver input pin for UART10. */
#define SYS_GPF_MFPL_PF4MFP_I2S0_LRCK         (0x04UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< I2S0 left right channel clock. */
#define SYS_GPF_MFPL_PF4MFP_SPI1_SS0          (0x05UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< 1st SPI1 slave select pin. */
#define SYS_GPF_MFPL_PF4MFP_RGMII1_TXD1       (0x08UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< MII/RMII Transmit Data bus bit 1. */
#define SYS_GPF_MFPL_PF4MFP_RMII1_TXD1        (0x09UL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< RMII1 Transmit Data bus bit 1. */
#define SYS_GPF_MFPL_PF4MFP_USBHL0_DM         (0x0CUL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPF_MFPL_PF4MFP_CAN2_RXD          (0x0DUL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< CAN2 bus receiver input. */
#define SYS_GPF_MFPL_PF4MFP_KPI_ROW0          (0x0EUL<<SYS_GPF_MFPL_PF4MFP_Pos)  /*!< Keypad Interface Row 0 input pin. */
#define SYS_GPF_MFPL_PF5MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF5MFP_UART11_nRTS       (0x02UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< Request to Send output pin for UART11. */
#define SYS_GPF_MFPL_PF5MFP_UART10_TXD        (0x03UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< Data transmitter output pin for UART10. */
#define SYS_GPF_MFPL_PF5MFP_I2S0_BCLK         (0x04UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< I2S0 bit clock pin. */
#define SYS_GPF_MFPL_PF5MFP_SPI1_CLK          (0x05UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< SPI1 serial clock pin. */
#define SYS_GPF_MFPL_PF5MFP_RGMII1_RXCLK      (0x08UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< RGMII1 Mode RX Clock input pin. */
#define SYS_GPF_MFPL_PF5MFP_RMII1_REFCLK      (0x09UL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< RMII1 Reference Clock input pin. */
#define SYS_GPF_MFPL_PF5MFP_USBHL0_DP         (0x0CUL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPF_MFPL_PF5MFP_CAN2_TXD          (0x0DUL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< CAN2 bus transmitter output. */
#define SYS_GPF_MFPL_PF5MFP_KPI_ROW1          (0x0EUL<<SYS_GPF_MFPL_PF5MFP_Pos)  /*!< Keypad Interface Row 1 input pin. */
#define SYS_GPF_MFPL_PF6MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF6MFP_UART11_RXD        (0x02UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< Data receiver input pin for UART11. */
#define SYS_GPF_MFPL_PF6MFP_I2S0_DI           (0x04UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< I2S0 data input. */
#define SYS_GPF_MFPL_PF6MFP_SPI1_MOSI         (0x05UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< 1st SPI1 MOSI (Master Out, Slave In) pin. */
#define SYS_GPF_MFPL_PF6MFP_RGMII1_RXCTL      (0x08UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< RGMII1 Receive Control input pin. */
#define SYS_GPF_MFPL_PF6MFP_RMII1_CRSDV       (0x09UL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< RMII1 Carrier Sense/Receive Data input pin. */
#define SYS_GPF_MFPL_PF6MFP_I2C4_SDA          (0x0AUL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPF_MFPL_PF6MFP_SC0_CLK           (0x0DUL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< SmartCard0 clock pin. */
#define SYS_GPF_MFPL_PF6MFP_KPI_ROW2          (0x0EUL<<SYS_GPF_MFPL_PF6MFP_Pos)  /*!< Keypad Interface Row 2 input pin. */
#define SYS_GPF_MFPL_PF7MFP_GPIO              (0x00UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPL_PF7MFP_UART11_TXD        (0x02UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< Data transmitter output pin for UART11. */
#define SYS_GPF_MFPL_PF7MFP_I2S0_DO           (0x04UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< I2S0 data output. */
#define SYS_GPF_MFPL_PF7MFP_SPI1_MISO         (0x05UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< 1st SPI1 MISO (Master In, Slave Out) pin. */
#define SYS_GPF_MFPL_PF7MFP_RGMII1_RXD0       (0x08UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< RGMII1 Receive Data bus bit 0. */
#define SYS_GPF_MFPL_PF7MFP_RMII1_RXD0        (0x09UL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< RMII1 Receive Data bus bit 0. */
#define SYS_GPF_MFPL_PF7MFP_I2C4_SCL          (0x0AUL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPF_MFPL_PF7MFP_SC0_DAT           (0x0DUL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< SmartCard0 data pin. */
#define SYS_GPF_MFPL_PF7MFP_KPI_ROW3          (0x0EUL<<SYS_GPF_MFPL_PF7MFP_Pos)  /*!< Keypad Interface Row 3 input pin. */
/********************* Bit definition of GPF_MFPH register **********************/
#define SYS_GPF_MFPH_PF8MFP_GPIO              (0x00UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF8MFP_UART13_RXD        (0x02UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< Data receiver input pin for UART13. */
#define SYS_GPF_MFPH_PF8MFP_I2C5_SDA          (0x04UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< I2C5 data input/output pin. */
#define SYS_GPF_MFPH_PF8MFP_SPI0_SS0          (0x05UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< 1st SPI0 slave select pin. */
#define SYS_GPF_MFPH_PF8MFP_RGMII1_RXD1       (0x08UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< RGMII1 Receive Data bus bit 1. */
#define SYS_GPF_MFPH_PF8MFP_RMII1_RXD1        (0x09UL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< RMII1 Receive Data bus bit 1. */
#define SYS_GPF_MFPH_PF8MFP_SC0_RST           (0x0DUL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< SmartCard0 reset pin. */
#define SYS_GPF_MFPH_PF8MFP_KPI_COL4          (0x0EUL<<SYS_GPF_MFPH_PF8MFP_Pos)  /*!< Keypad Interface Column 4 output pin. */
#define SYS_GPF_MFPH_PF9MFP_GPIO              (0x00UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF9MFP_UART13_TXD        (0x02UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< Data transmitter output pin for UART13. */
#define SYS_GPF_MFPH_PF9MFP_I2C5_SCL          (0x04UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< I2C5 clock pin. */
#define SYS_GPF_MFPH_PF9MFP_SPI0_SS1          (0x05UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< 1st SPI0 slave select pin. */
#define SYS_GPF_MFPH_PF9MFP_RGMII1_RXD2       (0x08UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< RGMII1 Receive Data bus bit 2. */
#define SYS_GPF_MFPH_PF9MFP_RMII1_RXERR       (0x09UL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< RMII1 Receive Data Error input pin. */
#define SYS_GPF_MFPH_PF9MFP_SC0_PWR           (0x0DUL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< SmartCard0 power pin. */
#define SYS_GPF_MFPH_PF9MFP_KPI_COL5          (0x0EUL<<SYS_GPF_MFPH_PF9MFP_Pos)  /*!< Keypad Interface Column 5 output pin. */
#define SYS_GPF_MFPH_PF10MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF10MFP_UART13_nCTS      (0x02UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< Clear to Send input pin for UART13. */
#define SYS_GPF_MFPH_PF10MFP_I2S0_LRCK        (0x05UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< I2S0 left right channel clock. */
#define SYS_GPF_MFPH_PF10MFP_SPI1_SS0         (0x06UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPF_MFPH_PF10MFP_RGMII1_RXD3      (0x08UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< RGMII1 Receive Data bus bit 3. */
#define SYS_GPF_MFPH_PF10MFP_SC0_CLK          (0x09UL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< SmartCard0 clock pin. */
#define SYS_GPF_MFPH_PF10MFP_KPI_COL6         (0x0EUL<<SYS_GPF_MFPH_PF10MFP_Pos) /*!< Keypad Interface Column 6 output pin. */
#define SYS_GPF_MFPH_PF11MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF11MFP_UART13_nRTS      (0x02UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< Request to Send output pin for UART13. */
#define SYS_GPF_MFPH_PF11MFP_I2S0_BCLK        (0x05UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< I2S0 bit clock pin. */
#define SYS_GPF_MFPH_PF11MFP_SPI1_CLK         (0x06UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< SPI1 serial clock pin. */
#define SYS_GPF_MFPH_PF11MFP_RGMII1_TXCLK     (0x08UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< RGMII1 Mode TX Clock output pin. */
#define SYS_GPF_MFPH_PF11MFP_SC0_DAT          (0x09UL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< SmartCard0 data pin. */
#define SYS_GPF_MFPH_PF11MFP_KPI_COL7         (0x0EUL<<SYS_GPF_MFPH_PF11MFP_Pos) /*!< Keypad Interface Column 7 output pin. */
#define SYS_GPF_MFPH_PF12MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF12MFP_I2S0_DI          (0x05UL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< I2S0 data input. */
#define SYS_GPF_MFPH_PF12MFP_SPI1_MOSI        (0x06UL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< 1st SPI1 MOSI (Master Out, Slave In) pin. */
#define SYS_GPF_MFPH_PF12MFP_RGMII1_TXD2      (0x08UL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< MII/RMII Transmit Data bus bit 2. */
#define SYS_GPF_MFPH_PF12MFP_SC0_RST          (0x09UL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< SmartCard0 reset pin. */
#define SYS_GPF_MFPH_PF12MFP_KPI_ROW4         (0x0EUL<<SYS_GPF_MFPH_PF12MFP_Pos) /*!< Keypad Interface Row 4 input pin. */
#define SYS_GPF_MFPH_PF13MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF13MFP_I2S0_DO          (0x05UL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< I2S0 data output. */
#define SYS_GPF_MFPH_PF13MFP_SPI1_MISO        (0x06UL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< 1st SPI1 MISO (Master In, Slave Out) pin. */
#define SYS_GPF_MFPH_PF13MFP_RGMII1_TXD3      (0x08UL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< MII/RMII Transmit Data bus bit 3. */
#define SYS_GPF_MFPH_PF13MFP_SC0_PWR          (0x09UL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< SmartCard0 power pin. */
#define SYS_GPF_MFPH_PF13MFP_KPI_ROW5         (0x0EUL<<SYS_GPF_MFPH_PF13MFP_Pos) /*!< Keypad Interface Row 5 input pin. */
#define SYS_GPF_MFPH_PF14MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF14MFP_EPWM2_BRAKE0     (0x01UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< Brake input pin 0 of EPWM2. */
#define SYS_GPF_MFPH_PF14MFP_EADC0_ST         (0x02UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< EADC external trigger input. */
#define SYS_GPF_MFPH_PF14MFP_RGMII1_PPS       (0x03UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< RGMII1 Pulse Per Second output pin. */
#define SYS_GPF_MFPH_PF14MFP_RMII1_PPS        (0x04UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< RMII1 Pulse Per Second output pin. */
#define SYS_GPF_MFPH_PF14MFP_SPI0_I2SMCLK     (0x05UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< SPI0 I2S master clock output pin. */
#define SYS_GPF_MFPH_PF14MFP_SPI1_I2SMCLK     (0x06UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< SPI1 I2S master clock output pin. */
#define SYS_GPF_MFPH_PF14MFP_CCAP1_SFIELD     (0x07UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< Camera capture 1 interface SFIELD input pin. */
#define SYS_GPF_MFPH_PF14MFP_RGMII0_PPS       (0x08UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< RGMII0 Pulse Per Second output pin. */
#define SYS_GPF_MFPH_PF14MFP_RMII0_PPS        (0x09UL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< RMII0 Pulse Per Second output pin. */
#define SYS_GPF_MFPH_PF14MFP_TM0              (0x0BUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< Timer0 event counter input / toggle output */
#define SYS_GPF_MFPH_PF14MFP_INT0             (0x0CUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< External interrupt0 input pin. */
#define SYS_GPF_MFPH_PF14MFP_SPI1_SS1         (0x0DUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPF_MFPH_PF14MFP_QEI2_INDEX       (0x0EUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< Quadrature encoder index input of QEI Unit 2. */
#define SYS_GPF_MFPH_PF14MFP_I2S0_MCLK        (0x0FUL<<SYS_GPF_MFPH_PF14MFP_Pos) /*!< I2S0 master clock output pin. */
#define SYS_GPF_MFPH_PF15MFP_GPIO             (0x00UL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPF_MFPH_PF15MFP_HSUSB0_VBUSVLD   (0x01UL<<SYS_GPF_MFPH_PF15MFP_Pos) /*!< HSUSB0 external VBUS regulator status pin. */
/********************* Bit definition of GPG_MFPL register **********************/
#define SYS_GPG_MFPL_PG0MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG0MFP_EPWM0_CH0         (0x01UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< EPWM0 channel0 output/capture input. */
#define SYS_GPG_MFPL_PG0MFP_UART7_TXD         (0x02UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< Data transmitter output pin for UART7. */
#define SYS_GPG_MFPL_PG0MFP_CAN3_TXD          (0x03UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< CAN3 bus transmitter output. */
#define SYS_GPG_MFPL_PG0MFP_SPI0_SS0          (0x05UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< 1st SPI0 slave select pin. */
#define SYS_GPG_MFPL_PG0MFP_EADC0_ST          (0x06UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< EADC external trigger input. */
#define SYS_GPG_MFPL_PG0MFP_EBI_AD15          (0x07UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPG_MFPL_PG0MFP_I2S1_MCLK         (0x09UL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPG_MFPL_PG0MFP_QEI0_INDEX        (0x0AUL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 0. */
#define SYS_GPG_MFPL_PG0MFP_TM1               (0x0BUL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< Timer1 event counter input / toggle output */
#define SYS_GPG_MFPL_PG0MFP_CLKO              (0x0CUL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< Clock Output pin. */
#define SYS_GPG_MFPL_PG0MFP_INT0              (0x0DUL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< External interrupt0 input pin. */
#define SYS_GPG_MFPL_PG0MFP_EBI_ADR15         (0x0FUL<<SYS_GPG_MFPL_PG0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPG_MFPL_PG1MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG1MFP_EPWM0_CH3         (0x01UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< EPWM0 channel3 output/capture input. */
#define SYS_GPG_MFPL_PG1MFP_UART9_nRTS        (0x02UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< Request to Send output pin for UART*. */
#define SYS_GPG_MFPL_PG1MFP_UART6_TXD         (0x03UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< Data transmitter output pin for UART6. */
#define SYS_GPG_MFPL_PG1MFP_I2C4_SCL          (0x04UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPG_MFPL_PG1MFP_CAN2_TXD          (0x05UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< CAN2 bus transmitter output. */
#define SYS_GPG_MFPL_PG1MFP_USBHL0_DP         (0x06UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPG_MFPL_PG1MFP_EBI_nCS0          (0x07UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPL_PG1MFP_QEI0_B            (0x09UL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< Quadrature encoder phase B input of QEI Unit 0. */
#define SYS_GPG_MFPL_PG1MFP_TM1_EXT           (0x0BUL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< Timer1 event counter input / toggle output */
#define SYS_GPG_MFPL_PG1MFP_RGMII1_PPS        (0x0EUL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< RGMII1 Pulse Per Second output pin. */
#define SYS_GPG_MFPL_PG1MFP_RMII1_PPS         (0x0FUL<<SYS_GPG_MFPL_PG1MFP_Pos)  /*!< RMII1 Pulse Per Second output pin. */
#define SYS_GPG_MFPL_PG2MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG2MFP_EPWM0_CH4         (0x01UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< EPWM0 channel4 output/capture input. */
#define SYS_GPG_MFPL_PG2MFP_UART9_RXD         (0x02UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< Data receiver input pin for UART*. */
#define SYS_GPG_MFPL_PG2MFP_CAN0_RXD          (0x03UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPG_MFPL_PG2MFP_SPI0_SS1          (0x05UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< 1st SPI0 slave select pin. */
#define SYS_GPG_MFPL_PG2MFP_TSI_SWD_DAT       (0x06UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< Serial wire debug data pin for TSI. */
#define SYS_GPG_MFPL_PG2MFP_EBI_ADR16         (0x07UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPG_MFPL_PG2MFP_EBI_nCS2          (0x08UL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPL_PG2MFP_QEI0_A            (0x0AUL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< Quadrature encoder phase A input of QEI Unit 0. */
#define SYS_GPG_MFPL_PG2MFP_TM3               (0x0BUL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< Timer3 event counter input / toggle output */
#define SYS_GPG_MFPL_PG2MFP_INT1              (0x0DUL<<SYS_GPG_MFPL_PG2MFP_Pos)  /*!< External interrupt1 input pin. */
#define SYS_GPG_MFPL_PG3MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG3MFP_EPWM0_CH5         (0x01UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< EPWM0 channel5 output/capture input. */
#define SYS_GPG_MFPL_PG3MFP_UART9_TXD         (0x02UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< Data transmitter output pin for UART*. */
#define SYS_GPG_MFPL_PG3MFP_CAN0_TXD          (0x03UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPG_MFPL_PG3MFP_SPI0_I2SMCLK      (0x05UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< SPI0 I2S master clock output pin. */
#define SYS_GPG_MFPL_PG3MFP_TSI_SWD_CLK       (0x06UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< Serial wire debug clock pin for TSI. */
#define SYS_GPG_MFPL_PG3MFP_EBI_ADR17         (0x07UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPG_MFPL_PG3MFP_EBI_nCS1          (0x08UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPL_PG3MFP_EBI_MCLK          (0x09UL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< EBI external clock output pin. */
#define SYS_GPG_MFPL_PG3MFP_QEI0_B            (0x0AUL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< Quadrature encoder phase B input of QEI Unit 0. */
#define SYS_GPG_MFPL_PG3MFP_TM3_EXT           (0x0BUL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< Timer3 event counter input / toggle output */
#define SYS_GPG_MFPL_PG3MFP_I2S1_MCLK         (0x0CUL<<SYS_GPG_MFPL_PG3MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPG_MFPL_PG4MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG4MFP_EPWM1_CH0         (0x01UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< EPWM1 channel0 output/capture input. */
#define SYS_GPG_MFPL_PG4MFP_UART5_nCTS        (0x02UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< Clear to Send input pin for UART5. */
#define SYS_GPG_MFPL_PG4MFP_UART6_RXD         (0x03UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< Data receiver input pin for UART6. */
#define SYS_GPG_MFPL_PG4MFP_SPI3_SS0          (0x05UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< 1st SPI3 slave select pin. */
#define SYS_GPG_MFPL_PG4MFP_QEI1_INDEX        (0x06UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 1. */
#define SYS_GPG_MFPL_PG4MFP_EBI_ADR18         (0x07UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPG_MFPL_PG4MFP_EBI_nCS0          (0x08UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPL_PG4MFP_I2S1_DO           (0x09UL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< I2S1 data output. */
#define SYS_GPG_MFPL_PG4MFP_SC1_CLK           (0x0AUL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< SmartCard1 clock pin. */
#define SYS_GPG_MFPL_PG4MFP_TM4               (0x0BUL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< Timer4 event counter input / toggle output */
#define SYS_GPG_MFPL_PG4MFP_TSI_UART_RXD      (0x0CUL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< UART data receiver input pin for TSI. */
#define SYS_GPG_MFPL_PG4MFP_INT2              (0x0DUL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< External interrupt2 input pin. */
#define SYS_GPG_MFPL_PG4MFP_ECAP1_IC2         (0x0EUL<<SYS_GPG_MFPL_PG4MFP_Pos)  /*!< Input 1 of enhanced capture unit 2. */
#define SYS_GPG_MFPL_PG5MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG5MFP_EPWM1_CH1         (0x01UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< EPWM1 channel1 output/capture input. */
#define SYS_GPG_MFPL_PG5MFP_UART5_nRTS        (0x02UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< Request to Send output pin for UART5. */
#define SYS_GPG_MFPL_PG5MFP_UART6_TXD         (0x03UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< Data transmitter output pin for UART6. */
#define SYS_GPG_MFPL_PG5MFP_SPI3_CLK          (0x05UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< SPI3 serial clock pin. */
#define SYS_GPG_MFPL_PG5MFP_ECAP0_IC0         (0x06UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< Input 0 of enhanced capture unit 0. */
#define SYS_GPG_MFPL_PG5MFP_EBI_ADR19         (0x07UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPG_MFPL_PG5MFP_EBI_ALE           (0x08UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< EBI address latch enable output pin. */
#define SYS_GPG_MFPL_PG5MFP_I2S1_DI           (0x09UL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< I2S1 data input. */
#define SYS_GPG_MFPL_PG5MFP_SC1_DAT           (0x0AUL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< SmartCard1 data pin. */
#define SYS_GPG_MFPL_PG5MFP_TM4_EXT           (0x0BUL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< Timer4 event counter input / toggle output */
#define SYS_GPG_MFPL_PG5MFP_TSI_UART_TXD      (0x0CUL<<SYS_GPG_MFPL_PG5MFP_Pos)  /*!< UART data transmitter output pin for TSI. */
#define SYS_GPG_MFPL_PG6MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG6MFP_EPWM1_CH2         (0x01UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< EPWM1 channel2 output/capture input. */
#define SYS_GPG_MFPL_PG6MFP_UART5_RXD         (0x02UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< Data receiver input pin for UART5. */
#define SYS_GPG_MFPL_PG6MFP_CAN1_RXD          (0x03UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< CAN1 bus receiver input. */
#define SYS_GPG_MFPL_PG6MFP_SPI3_MOSI         (0x05UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< 1st SPI3 MOSI (Master Out, Slave In) pin. */
#define SYS_GPG_MFPL_PG6MFP_ECAP0_IC1         (0x06UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< Input 1 of enhanced capture unit 0. */
#define SYS_GPG_MFPL_PG6MFP_EBI_nRD           (0x07UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< EBI read enable output pin. */
#define SYS_GPG_MFPL_PG6MFP_I2S1_BCLK         (0x09UL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< I2S1 bit clock pin. */
#define SYS_GPG_MFPL_PG6MFP_SC1_RST           (0x0AUL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< SmartCard1 reset pin. */
#define SYS_GPG_MFPL_PG6MFP_TM7               (0x0BUL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< Timer7 event counter input / toggle output */
#define SYS_GPG_MFPL_PG6MFP_INT3              (0x0DUL<<SYS_GPG_MFPL_PG6MFP_Pos)  /*!< External interrupt3 input pin. */
#define SYS_GPG_MFPL_PG7MFP_GPIO              (0x00UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPL_PG7MFP_EPWM1_CH3         (0x01UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< EPWM1 channel3 output/capture input. */
#define SYS_GPG_MFPL_PG7MFP_UART5_TXD         (0x02UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< Data transmitter output pin for UART5. */
#define SYS_GPG_MFPL_PG7MFP_CAN1_TXD          (0x03UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< CAN1 bus transmitter output. */
#define SYS_GPG_MFPL_PG7MFP_SPI3_MISO         (0x05UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< 1st SPI3 MISO (Master In, Slave Out) pin. */
#define SYS_GPG_MFPL_PG7MFP_ECAP0_IC2         (0x06UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< Input 0 of enhanced capture unit 2. */
#define SYS_GPG_MFPL_PG7MFP_EBI_nWR           (0x07UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< EBI write enable output pin. */
#define SYS_GPG_MFPL_PG7MFP_I2S1_LRCK         (0x09UL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< I2S1 left right channel clock. */
#define SYS_GPG_MFPL_PG7MFP_SC1_PWR           (0x0AUL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< SmartCard1 power pin. */
#define SYS_GPG_MFPL_PG7MFP_TM7_EXT           (0x0BUL<<SYS_GPG_MFPL_PG7MFP_Pos)  /*!< Timer7 event counter input / toggle output */
/********************* Bit definition of GPG_MFPH register **********************/
#define SYS_GPG_MFPH_PG8MFP_GPIO              (0x00UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG8MFP_EPWM1_CH4         (0x01UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPG_MFPH_PG8MFP_UART12_RXD        (0x02UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< Data receiver input pin for UART12. */
#define SYS_GPG_MFPH_PG8MFP_CAN3_RXD          (0x03UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< CAN3 bus receiver input. */
#define SYS_GPG_MFPH_PG8MFP_USBHL4_DM         (0x04UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPG_MFPH_PG8MFP_SPI2_SS0          (0x05UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< 1st SPI2 slave select pin. */
#define SYS_GPG_MFPH_PG8MFP_LCM_MPU_RDEN      (0x06UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< TFT LCD Module Read(RD)/Enable(EN) output pin in MPU-type 80/68 mode. */
#define SYS_GPG_MFPH_PG8MFP_LCM_VSYNC         (0x06UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< TFT LCD Module Vertical/Frame sync. output pin in Sync-type mode. */
#define SYS_GPG_MFPH_PG8MFP_I2C3_SDA          (0x07UL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< I2C3 data input/output pin. */
#define SYS_GPG_MFPH_PG8MFP_EBI_AD7           (0x0CUL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPG_MFPH_PG8MFP_EBI_nCS0          (0x0DUL<<SYS_GPG_MFPH_PG8MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPH_PG9MFP_GPIO              (0x00UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG9MFP_EPWM1_CH5         (0x01UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPG_MFPH_PG9MFP_UART12_TXD        (0x02UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< Data transmitter output pin for UART12. */
#define SYS_GPG_MFPH_PG9MFP_CAN3_TXD          (0x03UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< CAN3 bus transmitter output. */
#define SYS_GPG_MFPH_PG9MFP_USBHL4_DP         (0x04UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPG_MFPH_PG9MFP_SPI2_CLK          (0x05UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< SPI2 serial clock pin. */
#define SYS_GPG_MFPH_PG9MFP_LCM_HSYNC         (0x06UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< TFT LCD Module Horizontal/Line sync. output in Sync-type mode. */
#define SYS_GPG_MFPH_PG9MFP_LCM_MPU_WRX       (0x06UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< TFT LCD Module Write(WR)/ReadWrite(RW) output pin in MPU-type 80/68 mode. */
#define SYS_GPG_MFPH_PG9MFP_I2C3_SCL          (0x07UL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< I2C3 clock pin. */
#define SYS_GPG_MFPH_PG9MFP_EBI_AD8           (0x0CUL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPG_MFPH_PG9MFP_EBI_nCS1          (0x0DUL<<SYS_GPG_MFPH_PG9MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPH_PG10MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG10MFP_UART12_nRTS      (0x02UL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< Request to Send output pin for UART12. */
#define SYS_GPG_MFPH_PG10MFP_UART13_TXD       (0x03UL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< Data transmitter output pin for UART13. */
#define SYS_GPG_MFPH_PG10MFP_SPI2_MOSI        (0x05UL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< 1st SPI2 MOSI (Master Out, Slave In) pin. */
#define SYS_GPG_MFPH_PG10MFP_LCM_CLK          (0x06UL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< TFT LCD Module Pixel Clock output pin in Sync-type mode. */
#define SYS_GPG_MFPH_PG10MFP_EBI_AD9          (0x0CUL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< EBI address/data bus bit9. */
#define SYS_GPG_MFPH_PG10MFP_EBI_nWRH         (0x0DUL<<SYS_GPG_MFPH_PG10MFP_Pos) /*!< EBI write enable output pin. */
#define SYS_GPG_MFPH_PG11MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG11MFP_JTAG_TDO         (0x03UL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< JTAG data output pin. */
#define SYS_GPG_MFPH_PG11MFP_I2S0_MCLK        (0x05UL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< I2S0 master clock output pin. */
#define SYS_GPG_MFPH_PG11MFP_EBI_nWRH         (0x07UL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< EBI write enable output pin. */
#define SYS_GPG_MFPH_PG11MFP_EBI_nCS1         (0x08UL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPH_PG11MFP_EBI_AD0          (0x0AUL<<SYS_GPG_MFPH_PG11MFP_Pos) /*!< EBI address/data bus bit0. */
#define SYS_GPG_MFPH_PG12MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG12MFP_JTAG_TCK         (0x03UL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< JTAG clock input pin. */
#define SYS_GPG_MFPH_PG12MFP_SW_CLK           (0x03UL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< Serial wire clock input pin. */
#define SYS_GPG_MFPH_PG12MFP_I2S0_LRCK        (0x05UL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< I2S0 left right channel clock. */
#define SYS_GPG_MFPH_PG12MFP_EBI_nWRL         (0x07UL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< EBI write enable output pin. */
#define SYS_GPG_MFPH_PG12MFP_EBI_AD1          (0x0AUL<<SYS_GPG_MFPH_PG12MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPG_MFPH_PG13MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG13MFP_JTAG_TMS         (0x03UL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< JTAG test mode selection input pin. */
#define SYS_GPG_MFPH_PG13MFP_SW_DIO           (0x03UL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< Serial wire data pin. */
#define SYS_GPG_MFPH_PG13MFP_I2S0_BCLK        (0x05UL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< I2S0 bit clock pin. */
#define SYS_GPG_MFPH_PG13MFP_EBI_MCLK         (0x07UL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< EBI external clock output pin. */
#define SYS_GPG_MFPH_PG13MFP_EBI_AD2          (0x0AUL<<SYS_GPG_MFPH_PG13MFP_Pos) /*!< EBI address/data bus bit2. */
#define SYS_GPG_MFPH_PG14MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG14MFP_JTAG_TDI         (0x03UL<<SYS_GPG_MFPH_PG14MFP_Pos) /*!< JTAG data input pin. */
#define SYS_GPG_MFPH_PG14MFP_I2S0_DI          (0x05UL<<SYS_GPG_MFPH_PG14MFP_Pos) /*!< I2S0 data input. */
#define SYS_GPG_MFPH_PG14MFP_EBI_ALE          (0x07UL<<SYS_GPG_MFPH_PG14MFP_Pos) /*!< EBI address latch enable output pin. */
#define SYS_GPG_MFPH_PG14MFP_EBI_AD3          (0x0AUL<<SYS_GPG_MFPH_PG14MFP_Pos) /*!< EBI address/data bus bit3. */
#define SYS_GPG_MFPH_PG15MFP_GPIO             (0x00UL<<SYS_GPG_MFPH_PG15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPG_MFPH_PG15MFP_JTAG_nTRST       (0x03UL<<SYS_GPG_MFPH_PG15MFP_Pos) /*!< JTAG reset pin. */
#define SYS_GPG_MFPH_PG15MFP_I2S0_DO          (0x05UL<<SYS_GPG_MFPH_PG15MFP_Pos) /*!< I2S0 data output. */
#define SYS_GPG_MFPH_PG15MFP_EBI_nCS0         (0x07UL<<SYS_GPG_MFPH_PG15MFP_Pos) /*!< EBI chip select enable output pin. */
#define SYS_GPG_MFPH_PG15MFP_EBI_AD4          (0x0AUL<<SYS_GPG_MFPH_PG15MFP_Pos) /*!< EBI address/data bus bit4. */
/********************* Bit definition of GPH_MFPL register **********************/
#define SYS_GPH_MFPL_PH0MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH0MFP_UART8_nCTS        (0x02UL<<SYS_GPH_MFPL_PH0MFP_Pos)  /*!< Clear to Send input pin for UART8. */
#define SYS_GPH_MFPL_PH0MFP_UART7_RXD         (0x03UL<<SYS_GPH_MFPL_PH0MFP_Pos)  /*!< Data receiver input pin for UART7. */
#define SYS_GPH_MFPL_PH0MFP_LCM_DATA8         (0x06UL<<SYS_GPH_MFPL_PH0MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 8 in Sync-type mode. */
#define SYS_GPH_MFPL_PH0MFP_LCM_MPU_DATA8     (0x06UL<<SYS_GPH_MFPL_PH0MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 8 in MPU-type mode. */
#define SYS_GPH_MFPL_PH1MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH1MFP_UART8_nRTS        (0x02UL<<SYS_GPH_MFPL_PH1MFP_Pos)  /*!< Request to Send output pin for UART8. */
#define SYS_GPH_MFPL_PH1MFP_UART7_TXD         (0x03UL<<SYS_GPH_MFPL_PH1MFP_Pos)  /*!< Data transmitter output pin for UART7. */
#define SYS_GPH_MFPL_PH1MFP_LCM_DATA9         (0x06UL<<SYS_GPH_MFPL_PH1MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 9 in Sync-type mode. */
#define SYS_GPH_MFPL_PH1MFP_LCM_MPU_DATA9     (0x06UL<<SYS_GPH_MFPL_PH1MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 9 in MPU-type mode. */
#define SYS_GPH_MFPL_PH2MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH2MFP_UART8_RXD         (0x02UL<<SYS_GPH_MFPL_PH2MFP_Pos)  /*!< Data receiver input pin for UART8. */
#define SYS_GPH_MFPL_PH2MFP_LCM_DATA10        (0x06UL<<SYS_GPH_MFPL_PH2MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH2MFP_LCM_MPU_DATA10    (0x06UL<<SYS_GPH_MFPL_PH2MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPH_MFPL_PH3MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH3MFP_UART8_TXD         (0x02UL<<SYS_GPH_MFPL_PH3MFP_Pos)  /*!< Data transmitter output pin for UART8. */
#define SYS_GPH_MFPL_PH3MFP_LCM_DATA11        (0x06UL<<SYS_GPH_MFPL_PH3MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH3MFP_LCM_MPU_DATA11    (0x06UL<<SYS_GPH_MFPL_PH3MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPH_MFPL_PH4MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH4MFP_UART10_nCTS       (0x02UL<<SYS_GPH_MFPL_PH4MFP_Pos)  /*!< Clear to Send input pin for UART10. */
#define SYS_GPH_MFPL_PH4MFP_UART9_RXD         (0x03UL<<SYS_GPH_MFPL_PH4MFP_Pos)  /*!< Data receiver input pin for UART*. */
#define SYS_GPH_MFPL_PH4MFP_LCM_DATA12        (0x06UL<<SYS_GPH_MFPL_PH4MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH4MFP_LCM_MPU_DATA12    (0x06UL<<SYS_GPH_MFPL_PH4MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPH_MFPL_PH5MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH5MFP_UART10_nRTS       (0x02UL<<SYS_GPH_MFPL_PH5MFP_Pos)  /*!< Request to Send output pin for UART10. */
#define SYS_GPH_MFPL_PH5MFP_UART9_TXD         (0x03UL<<SYS_GPH_MFPL_PH5MFP_Pos)  /*!< Data transmitter output pin for UART*. */
#define SYS_GPH_MFPL_PH5MFP_LCM_DATA13        (0x06UL<<SYS_GPH_MFPL_PH5MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH5MFP_LCM_MPU_DATA13    (0x06UL<<SYS_GPH_MFPL_PH5MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPH_MFPL_PH6MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH6MFP_UART10_RXD        (0x02UL<<SYS_GPH_MFPL_PH6MFP_Pos)  /*!< Data receiver input pin for UART10. */
#define SYS_GPH_MFPL_PH6MFP_LCM_DATA14        (0x06UL<<SYS_GPH_MFPL_PH6MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH6MFP_LCM_MPU_DATA14    (0x06UL<<SYS_GPH_MFPL_PH6MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPH_MFPL_PH7MFP_GPIO              (0x00UL<<SYS_GPH_MFPL_PH7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPL_PH7MFP_UART10_TXD        (0x02UL<<SYS_GPH_MFPL_PH7MFP_Pos)  /*!< Data transmitter output pin for UART10. */
#define SYS_GPH_MFPL_PH7MFP_LCM_DATA15        (0x06UL<<SYS_GPH_MFPL_PH7MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPH_MFPL_PH7MFP_LCM_MPU_DATA15    (0x06UL<<SYS_GPH_MFPL_PH7MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
/********************* Bit definition of GPH_MFPH register **********************/
#define SYS_GPH_MFPH_PH8MFP_GPIO              (0x00UL<<SYS_GPH_MFPH_PH8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH8MFP_TAMPER0           (0x06UL<<SYS_GPH_MFPH_PH8MFP_Pos)  /*!< TAMPER detector loop pin0. */
#define SYS_GPH_MFPH_PH9MFP_GPIO              (0x00UL<<SYS_GPH_MFPH_PH9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH9MFP_CLK_32KOUT        (0x04UL<<SYS_GPH_MFPH_PH9MFP_Pos)  /*!< 32kHz clock output pin. */
#define SYS_GPH_MFPH_PH9MFP_TAMPER1           (0x06UL<<SYS_GPH_MFPH_PH9MFP_Pos)  /*!< TAMPER detector loop pin1. */
#define SYS_GPH_MFPH_PH12MFP_GPIO             (0x00UL<<SYS_GPH_MFPH_PH12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH12MFP_UART14_nCTS      (0x02UL<<SYS_GPH_MFPH_PH12MFP_Pos) /*!< Clear to Send input pin for UART14. */
#define SYS_GPH_MFPH_PH12MFP_UART13_RXD       (0x03UL<<SYS_GPH_MFPH_PH12MFP_Pos) /*!< Data receiver input pin for UART13. */
#define SYS_GPH_MFPH_PH12MFP_LCM_DATA20       (0x06UL<<SYS_GPH_MFPH_PH12MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 2 in Sync-type mode. */
#define SYS_GPH_MFPH_PH13MFP_GPIO             (0x00UL<<SYS_GPH_MFPH_PH13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH13MFP_UART14_nRTS      (0x02UL<<SYS_GPH_MFPH_PH13MFP_Pos) /*!< Request to Send output pin for UART14. */
#define SYS_GPH_MFPH_PH13MFP_UART13_TXD       (0x03UL<<SYS_GPH_MFPH_PH13MFP_Pos) /*!< Data transmitter output pin for UART13. */
#define SYS_GPH_MFPH_PH13MFP_LCM_DATA21       (0x06UL<<SYS_GPH_MFPH_PH13MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 2 in Sync-type mode. */
#define SYS_GPH_MFPH_PH14MFP_GPIO             (0x00UL<<SYS_GPH_MFPH_PH14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH14MFP_UART14_RXD       (0x02UL<<SYS_GPH_MFPH_PH14MFP_Pos) /*!< Data receiver input pin for UART14. */
#define SYS_GPH_MFPH_PH14MFP_LCM_DATA22       (0x06UL<<SYS_GPH_MFPH_PH14MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 2 in Sync-type mode. */
#define SYS_GPH_MFPH_PH15MFP_GPIO             (0x00UL<<SYS_GPH_MFPH_PH15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPH_MFPH_PH15MFP_UART14_TXD       (0x02UL<<SYS_GPH_MFPH_PH15MFP_Pos) /*!< Data transmitter output pin for UART14. */
#define SYS_GPH_MFPH_PH15MFP_LCM_DATA23       (0x06UL<<SYS_GPH_MFPH_PH15MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 2 in Sync-type mode. */
/********************* Bit definition of GPI_MFPL register **********************/
#define SYS_GPI_MFPL_PI0MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI0MFP_EPWM0_CH0         (0x01UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< EPWM0 channel0 output/capture input. */
#define SYS_GPI_MFPL_PI0MFP_UART12_nCTS       (0x02UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< Clear to Send input pin for UART12. */
#define SYS_GPI_MFPL_PI0MFP_UART11_RXD        (0x03UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< Data receiver input pin for UART11. */
#define SYS_GPI_MFPL_PI0MFP_I2C2_SDA          (0x04UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< I2C2 data input/output pin. */
#define SYS_GPI_MFPL_PI0MFP_SPI3_SS0          (0x05UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< 1st SPI3 slave select pin. */
#define SYS_GPI_MFPL_PI0MFP_SC0_nCD           (0x07UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< SmartCard0 card detect pin. */
#define SYS_GPI_MFPL_PI0MFP_EBI_ADR0          (0x08UL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI0MFP_TM0               (0x0BUL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< Timer0 event counter input / toggle output */
#define SYS_GPI_MFPL_PI0MFP_ECAP1_IC0         (0x0CUL<<SYS_GPI_MFPL_PI0MFP_Pos)  /*!< Input 0 of enhanced capture unit 1. */
#define SYS_GPI_MFPL_PI1MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI1MFP_EPWM0_CH1         (0x01UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< EPWM0 channel1 output/capture input. */
#define SYS_GPI_MFPL_PI1MFP_UART12_nRTS       (0x02UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< Request to Send output pin for UART12. */
#define SYS_GPI_MFPL_PI1MFP_UART11_TXD        (0x03UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< Data transmitter output pin for UART11. */
#define SYS_GPI_MFPL_PI1MFP_I2C2_SCL          (0x04UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< I2C2 clock pin. */
#define SYS_GPI_MFPL_PI1MFP_SPI3_CLK          (0x05UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< SPI3 serial clock pin. */
#define SYS_GPI_MFPL_PI1MFP_SC0_CLK           (0x07UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< SmartCard0 clock pin. */
#define SYS_GPI_MFPL_PI1MFP_EBI_ADR1          (0x08UL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI1MFP_TM0_EXT           (0x0BUL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< Timer0 event counter input / toggle output */
#define SYS_GPI_MFPL_PI1MFP_ECAP1_IC1         (0x0CUL<<SYS_GPI_MFPL_PI1MFP_Pos)  /*!< Input 1 of enhanced capture unit 1. */
#define SYS_GPI_MFPL_PI2MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI2MFP_EPWM0_CH2         (0x01UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPI_MFPL_PI2MFP_UART12_RXD        (0x02UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< Data receiver input pin for UART12. */
#define SYS_GPI_MFPL_PI2MFP_CAN0_RXD          (0x03UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPI_MFPL_PI2MFP_USBHL2_DM         (0x04UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< USB 1.1 host-lite 2 differential signal D-. */
#define SYS_GPI_MFPL_PI2MFP_SPI3_MOSI         (0x05UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< 1st SPI3 MOSI (Master Out, Slave In) pin. */
#define SYS_GPI_MFPL_PI2MFP_SC0_DAT           (0x07UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< SmartCard0 data pin. */
#define SYS_GPI_MFPL_PI2MFP_EBI_ADR2          (0x08UL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI2MFP_TM1               (0x0BUL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< Timer1 event counter input / toggle output */
#define SYS_GPI_MFPL_PI2MFP_ECAP1_IC2         (0x0CUL<<SYS_GPI_MFPL_PI2MFP_Pos)  /*!< Input 1 of enhanced capture unit 2. */
#define SYS_GPI_MFPL_PI3MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI3MFP_EPWM0_CH3         (0x01UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< EPWM0 channel3 output/capture input. */
#define SYS_GPI_MFPL_PI3MFP_UART12_TXD        (0x02UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< Data transmitter output pin for UART12. */
#define SYS_GPI_MFPL_PI3MFP_CAN0_TXD          (0x03UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPI_MFPL_PI3MFP_USBHL2_DP         (0x04UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< USB 1.1 host-lite 2 differential signal D+. */
#define SYS_GPI_MFPL_PI3MFP_SPI3_MISO         (0x05UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< 1st SPI3 MISO (Master In, Slave Out) pin. */
#define SYS_GPI_MFPL_PI3MFP_SC0_RST           (0x07UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< SmartCard0 reset pin. */
#define SYS_GPI_MFPL_PI3MFP_EBI_ADR3          (0x08UL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI3MFP_TM1_EXT           (0x0BUL<<SYS_GPI_MFPL_PI3MFP_Pos)  /*!< Timer1 event counter input / toggle output */
#define SYS_GPI_MFPL_PI4MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI4MFP_EPWM0_CH4         (0x01UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< EPWM0 channel4 output/capture input. */
#define SYS_GPI_MFPL_PI4MFP_UART14_nCTS       (0x02UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< Clear to Send input pin for UART14. */
#define SYS_GPI_MFPL_PI4MFP_UART13_RXD        (0x03UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< Data receiver input pin for UART13. */
#define SYS_GPI_MFPL_PI4MFP_I2C3_SDA          (0x04UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< I2C3 data input/output pin. */
#define SYS_GPI_MFPL_PI4MFP_SPI2_SS1          (0x05UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< 1st SPI2 slave select pin. */
#define SYS_GPI_MFPL_PI4MFP_I2S1_LRCK         (0x06UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< I2S1 left right channel clock. */
#define SYS_GPI_MFPL_PI4MFP_EBI_ADR4          (0x08UL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI4MFP_INT0              (0x0DUL<<SYS_GPI_MFPL_PI4MFP_Pos)  /*!< External interrupt0 input pin. */
#define SYS_GPI_MFPL_PI5MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI5MFP_EPWM0_CH5         (0x01UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< EPWM0 channel5 output/capture input. */
#define SYS_GPI_MFPL_PI5MFP_UART14_nRTS       (0x02UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< Request to Send output pin for UART14. */
#define SYS_GPI_MFPL_PI5MFP_UART13_TXD        (0x03UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< Data transmitter output pin for UART13. */
#define SYS_GPI_MFPL_PI5MFP_I2C3_SCL          (0x04UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< I2C3 clock pin. */
#define SYS_GPI_MFPL_PI5MFP_I2S1_BCLK         (0x06UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< I2S1 bit clock pin. */
#define SYS_GPI_MFPL_PI5MFP_EBI_ADR5          (0x08UL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI5MFP_INT1              (0x0DUL<<SYS_GPI_MFPL_PI5MFP_Pos)  /*!< External interrupt1 input pin. */
#define SYS_GPI_MFPL_PI6MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI6MFP_EPWM0_BRAKE0      (0x01UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< Brake input pin 0 of EPWM0. */
#define SYS_GPI_MFPL_PI6MFP_UART14_RXD        (0x02UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< Data receiver input pin for UART14. */
#define SYS_GPI_MFPL_PI6MFP_CAN1_RXD          (0x03UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< CAN1 bus receiver input. */
#define SYS_GPI_MFPL_PI6MFP_USBHL3_DM         (0x04UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPI_MFPL_PI6MFP_I2S1_DI           (0x06UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< I2S1 data input. */
#define SYS_GPI_MFPL_PI6MFP_EBI_ADR6          (0x08UL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI6MFP_QEI1_INDEX        (0x0CUL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 1. */
#define SYS_GPI_MFPL_PI6MFP_INT2              (0x0DUL<<SYS_GPI_MFPL_PI6MFP_Pos)  /*!< External interrupt2 input pin. */
#define SYS_GPI_MFPL_PI7MFP_GPIO              (0x00UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPL_PI7MFP_EPWM0_BRAKE1      (0x01UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< Brake input pin 1 of EPWM0. */
#define SYS_GPI_MFPL_PI7MFP_UART14_TXD        (0x02UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< Data transmitter output pin for UART14. */
#define SYS_GPI_MFPL_PI7MFP_CAN1_TXD          (0x03UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< CAN1 bus transmitter output. */
#define SYS_GPI_MFPL_PI7MFP_USBHL3_DP         (0x04UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPI_MFPL_PI7MFP_I2S1_DO           (0x06UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< I2S1 data output. */
#define SYS_GPI_MFPL_PI7MFP_EBI_ADR7          (0x08UL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPI_MFPL_PI7MFP_ECAP0_IC0         (0x0CUL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< Input 0 of enhanced capture unit 0. */
#define SYS_GPI_MFPL_PI7MFP_INT3              (0x0DUL<<SYS_GPI_MFPL_PI7MFP_Pos)  /*!< External interrupt3 input pin. */
/********************* Bit definition of GPI_MFPH register **********************/
#define SYS_GPI_MFPH_PI8MFP_GPIO              (0x00UL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI8MFP_UART4_nCTS        (0x02UL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< Clear to Send input pin for UART4. */
#define SYS_GPI_MFPH_PI8MFP_UART3_RXD         (0x03UL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< Data receiver input pin for UART3. */
#define SYS_GPI_MFPH_PI8MFP_LCM_DATA0         (0x06UL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 0 in Sync-type mode. */
#define SYS_GPI_MFPH_PI8MFP_LCM_MPU_DATA0     (0x06UL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 0 in MPU-type mode. */
#define SYS_GPI_MFPH_PI8MFP_EBI_AD11          (0x0CUL<<SYS_GPI_MFPH_PI8MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPI_MFPH_PI9MFP_GPIO              (0x00UL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI9MFP_UART4_nRTS        (0x02UL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< Request to Send output pin for UART4. */
#define SYS_GPI_MFPH_PI9MFP_UART3_TXD         (0x03UL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< Data transmitter output pin for UART3. */
#define SYS_GPI_MFPH_PI9MFP_LCM_DATA1         (0x06UL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< TFT LCD Module Pixel Data output bit 1 in Sync-type mode. */
#define SYS_GPI_MFPH_PI9MFP_LCM_MPU_DATA1     (0x06UL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< TFT LCD Module Command/Data input/output bit 1 in MPU-type mode. */
#define SYS_GPI_MFPH_PI9MFP_EBI_AD12          (0x0CUL<<SYS_GPI_MFPH_PI9MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPI_MFPH_PI10MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI10MFP_UART4_RXD        (0x02UL<<SYS_GPI_MFPH_PI10MFP_Pos) /*!< Data receiver input pin for UART4. */
#define SYS_GPI_MFPH_PI10MFP_LCM_DATA2        (0x06UL<<SYS_GPI_MFPH_PI10MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 2 in Sync-type mode. */
#define SYS_GPI_MFPH_PI10MFP_LCM_MPU_DATA2    (0x06UL<<SYS_GPI_MFPH_PI10MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 2 in MPU-type mode. */
#define SYS_GPI_MFPH_PI10MFP_EBI_AD13         (0x0CUL<<SYS_GPI_MFPH_PI10MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPI_MFPH_PI11MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI11MFP_UART4_TXD        (0x02UL<<SYS_GPI_MFPH_PI11MFP_Pos) /*!< Data transmitter output pin for UART4. */
#define SYS_GPI_MFPH_PI11MFP_LCM_DATA3        (0x06UL<<SYS_GPI_MFPH_PI11MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 3 in Sync-type mode. */
#define SYS_GPI_MFPH_PI11MFP_LCM_MPU_DATA3    (0x06UL<<SYS_GPI_MFPH_PI11MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 3 in MPU-type mode. */
#define SYS_GPI_MFPH_PI11MFP_EBI_AD14         (0x0CUL<<SYS_GPI_MFPH_PI11MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPI_MFPH_PI12MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI12MFP_UART6_nCTS       (0x02UL<<SYS_GPI_MFPH_PI12MFP_Pos) /*!< Clear to Send input pin for UART6. */
#define SYS_GPI_MFPH_PI12MFP_UART5_RXD        (0x03UL<<SYS_GPI_MFPH_PI12MFP_Pos) /*!< Data receiver input pin for UART5. */
#define SYS_GPI_MFPH_PI12MFP_LCM_DATA4        (0x06UL<<SYS_GPI_MFPH_PI12MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 4 in Sync-type mode. */
#define SYS_GPI_MFPH_PI12MFP_LCM_MPU_DATA4    (0x06UL<<SYS_GPI_MFPH_PI12MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 4 in MPU-type mode. */
#define SYS_GPI_MFPH_PI13MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI13MFP_UART6_nRTS       (0x02UL<<SYS_GPI_MFPH_PI13MFP_Pos) /*!< Request to Send output pin for UART6. */
#define SYS_GPI_MFPH_PI13MFP_UART5_TXD        (0x03UL<<SYS_GPI_MFPH_PI13MFP_Pos) /*!< Data transmitter output pin for UART5. */
#define SYS_GPI_MFPH_PI13MFP_LCM_DATA5        (0x06UL<<SYS_GPI_MFPH_PI13MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 5 in Sync-type mode. */
#define SYS_GPI_MFPH_PI13MFP_LCM_MPU_DATA5    (0x06UL<<SYS_GPI_MFPH_PI13MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 5 in MPU-type mode. */
#define SYS_GPI_MFPH_PI14MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI14MFP_UART6_RXD        (0x02UL<<SYS_GPI_MFPH_PI14MFP_Pos) /*!< Data receiver input pin for UART6. */
#define SYS_GPI_MFPH_PI14MFP_LCM_DATA6        (0x06UL<<SYS_GPI_MFPH_PI14MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 6 in Sync-type mode. */
#define SYS_GPI_MFPH_PI14MFP_LCM_MPU_DATA6    (0x06UL<<SYS_GPI_MFPH_PI14MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 6 in MPU-type mode. */
#define SYS_GPI_MFPH_PI15MFP_GPIO             (0x00UL<<SYS_GPI_MFPH_PI15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPI_MFPH_PI15MFP_UART6_TXD        (0x02UL<<SYS_GPI_MFPH_PI15MFP_Pos) /*!< Data transmitter output pin for UART6. */
#define SYS_GPI_MFPH_PI15MFP_LCM_DATA7        (0x06UL<<SYS_GPI_MFPH_PI15MFP_Pos) /*!< TFT LCD Module Pixel Data output bit 7 in Sync-type mode. */
#define SYS_GPI_MFPH_PI15MFP_LCM_MPU_DATA7    (0x06UL<<SYS_GPI_MFPH_PI15MFP_Pos) /*!< TFT LCD Module Command/Data input/output bit 7 in MPU-type mode. */
/********************* Bit definition of GPJ_MFPL register **********************/
#define SYS_GPJ_MFPL_PJ0MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ0MFP_EPWM1_BRAKE0      (0x01UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< Brake input pin 0 of EPWM1. */
#define SYS_GPJ_MFPL_PJ0MFP_UART8_nCTS        (0x02UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< Clear to Send input pin for UART8. */
#define SYS_GPJ_MFPL_PJ0MFP_UART7_RXD         (0x03UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< Data receiver input pin for UART7. */
#define SYS_GPJ_MFPL_PJ0MFP_I2C2_SDA          (0x04UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< I2C2 data input/output pin. */
#define SYS_GPJ_MFPL_PJ0MFP_SPI2_SS0          (0x05UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< 1st SPI2 slave select pin. */
#define SYS_GPJ_MFPL_PJ0MFP_eMMC1_DAT4        (0x06UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< eMMC1 data line bit 4. */
#define SYS_GPJ_MFPL_PJ0MFP_I2S0_LRCK         (0x07UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< I2S0 left right channel clock. */
#define SYS_GPJ_MFPL_PJ0MFP_SC0_CLK           (0x08UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< SmartCard0 clock pin. */
#define SYS_GPJ_MFPL_PJ0MFP_EBI_AD11          (0x09UL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPJ_MFPL_PJ0MFP_EBI_ADR16         (0x0AUL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPL_PJ0MFP_EBI_nCS0          (0x0BUL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPJ_MFPL_PJ0MFP_EBI_AD7           (0x0CUL<<SYS_GPJ_MFPL_PJ0MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPJ_MFPL_PJ1MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ1MFP_EPWM1_BRAKE1      (0x01UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< Brake input pin 1 of EPWM1. */
#define SYS_GPJ_MFPL_PJ1MFP_UART8_nRTS        (0x02UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< Request to Send output pin for UART8. */
#define SYS_GPJ_MFPL_PJ1MFP_UART7_TXD         (0x03UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< Data transmitter output pin for UART7. */
#define SYS_GPJ_MFPL_PJ1MFP_I2C2_SCL          (0x04UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< I2C2 clock pin. */
#define SYS_GPJ_MFPL_PJ1MFP_SPI2_CLK          (0x05UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< SPI2 serial clock pin. */
#define SYS_GPJ_MFPL_PJ1MFP_eMMC1_DAT5        (0x06UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< eMMC1 data line bit 5. */
#define SYS_GPJ_MFPL_PJ1MFP_I2S0_BCLK         (0x07UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< I2S0 bit clock pin. */
#define SYS_GPJ_MFPL_PJ1MFP_SC0_DAT           (0x08UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< SmartCard0 data pin. */
#define SYS_GPJ_MFPL_PJ1MFP_EBI_AD12          (0x09UL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPJ_MFPL_PJ1MFP_EBI_ADR17         (0x0AUL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPL_PJ1MFP_EBI_nCS1          (0x0BUL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< EBI chip select enable output pin. */
#define SYS_GPJ_MFPL_PJ1MFP_EBI_AD8           (0x0CUL<<SYS_GPJ_MFPL_PJ1MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPJ_MFPL_PJ2MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ2MFP_EPWM1_CH4         (0x01UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPJ_MFPL_PJ2MFP_UART8_RXD         (0x02UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< Data receiver input pin for UART8. */
#define SYS_GPJ_MFPL_PJ2MFP_CAN1_RXD          (0x03UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< CAN1 bus receiver input. */
#define SYS_GPJ_MFPL_PJ2MFP_USBHL5_DM         (0x04UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D-. */
#define SYS_GPJ_MFPL_PJ2MFP_SPI2_MOSI         (0x05UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< 1st SPI2 MOSI (Master Out, Slave In) pin. */
#define SYS_GPJ_MFPL_PJ2MFP_eMMC1_DAT6        (0x06UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< eMMC1 data line bit 6. */
#define SYS_GPJ_MFPL_PJ2MFP_I2S0_DI           (0x07UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< I2S0 data input. */
#define SYS_GPJ_MFPL_PJ2MFP_SC0_RST           (0x08UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< SmartCard0 reset pin. */
#define SYS_GPJ_MFPL_PJ2MFP_EBI_AD13          (0x09UL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPJ_MFPL_PJ2MFP_EBI_ADR18         (0x0AUL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPL_PJ2MFP_EBI_nWRH          (0x0BUL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< EBI write enable output pin. */
#define SYS_GPJ_MFPL_PJ2MFP_EBI_AD9           (0x0CUL<<SYS_GPJ_MFPL_PJ2MFP_Pos)  /*!< EBI address/data bus bit9. */
#define SYS_GPJ_MFPL_PJ3MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ3MFP_EPWM1_CH5         (0x01UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPJ_MFPL_PJ3MFP_UART8_TXD         (0x02UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< Data transmitter output pin for UART8. */
#define SYS_GPJ_MFPL_PJ3MFP_CAN1_TXD          (0x03UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< CAN1 bus transmitter output. */
#define SYS_GPJ_MFPL_PJ3MFP_USBHL5_DP         (0x04UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D+. */
#define SYS_GPJ_MFPL_PJ3MFP_SPI2_MISO         (0x05UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< 1st SPI2 MISO (Master In, Slave Out) pin. */
#define SYS_GPJ_MFPL_PJ3MFP_eMMC1_DAT7        (0x06UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< eMMC1 data line bit 7. */
#define SYS_GPJ_MFPL_PJ3MFP_I2S0_DO           (0x07UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< I2S0 data output. */
#define SYS_GPJ_MFPL_PJ3MFP_SC0_PWR           (0x08UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< SmartCard0 power pin. */
#define SYS_GPJ_MFPL_PJ3MFP_EBI_AD14          (0x09UL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPJ_MFPL_PJ3MFP_EBI_ADR19         (0x0AUL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPL_PJ3MFP_EBI_nWRL          (0x0BUL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< EBI write enable output pin. */
#define SYS_GPJ_MFPL_PJ3MFP_EBI_AD10          (0x0CUL<<SYS_GPJ_MFPL_PJ3MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPJ_MFPL_PJ4MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ4MFP_I2C3_SDA          (0x04UL<<SYS_GPJ_MFPL_PJ4MFP_Pos)  /*!< I2C3 data input/output pin. */
#define SYS_GPJ_MFPL_PJ4MFP_SD1_WP            (0x06UL<<SYS_GPJ_MFPL_PJ4MFP_Pos)  /*!< SD/SDIO1 write protect input. */
#define SYS_GPJ_MFPL_PJ5MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ5MFP_I2C3_SCL          (0x04UL<<SYS_GPJ_MFPL_PJ5MFP_Pos)  /*!< I2C3 clock pin. */
#define SYS_GPJ_MFPL_PJ5MFP_SD1_nCD           (0x06UL<<SYS_GPJ_MFPL_PJ5MFP_Pos)  /*!< SD/SDIO1 card detect */
#define SYS_GPJ_MFPL_PJ6MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ6MFP_CAN3_RXD          (0x03UL<<SYS_GPJ_MFPL_PJ6MFP_Pos)  /*!< CAN3 bus receiver input. */
#define SYS_GPJ_MFPL_PJ6MFP_USBHL0_DM         (0x04UL<<SYS_GPJ_MFPL_PJ6MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPJ_MFPL_PJ6MFP_eMMC1_CMD         (0x06UL<<SYS_GPJ_MFPL_PJ6MFP_Pos)  /*!< eMMC1 command/response. */
#define SYS_GPJ_MFPL_PJ6MFP_SD1_CMD           (0x06UL<<SYS_GPJ_MFPL_PJ6MFP_Pos)  /*!< SD/SDIO1 command/response. */
#define SYS_GPJ_MFPL_PJ7MFP_GPIO              (0x00UL<<SYS_GPJ_MFPL_PJ7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPL_PJ7MFP_CAN3_TXD          (0x03UL<<SYS_GPJ_MFPL_PJ7MFP_Pos)  /*!< CAN3 bus transmitter output. */
#define SYS_GPJ_MFPL_PJ7MFP_USBHL0_DP         (0x04UL<<SYS_GPJ_MFPL_PJ7MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPJ_MFPL_PJ7MFP_eMMC1_CLK         (0x06UL<<SYS_GPJ_MFPL_PJ7MFP_Pos)  /*!< eMMC1 clock. */
#define SYS_GPJ_MFPL_PJ7MFP_SD1_CLK           (0x06UL<<SYS_GPJ_MFPL_PJ7MFP_Pos)  /*!< SD/SDIO1 clock. */
/********************* Bit definition of GPJ_MFPH register **********************/
#define SYS_GPJ_MFPH_PJ8MFP_GPIO              (0x00UL<<SYS_GPJ_MFPH_PJ8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ8MFP_I2C4_SDA          (0x04UL<<SYS_GPJ_MFPH_PJ8MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPJ_MFPH_PJ8MFP_eMMC1_DAT0        (0x06UL<<SYS_GPJ_MFPH_PJ8MFP_Pos)  /*!< eMMC1 data line bit 0. */
#define SYS_GPJ_MFPH_PJ8MFP_SD1_DAT0          (0x06UL<<SYS_GPJ_MFPH_PJ8MFP_Pos)  /*!< SD/SDIO1 data line bit 0. */
#define SYS_GPJ_MFPH_PJ9MFP_GPIO              (0x00UL<<SYS_GPJ_MFPH_PJ9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ9MFP_I2C4_SCL          (0x04UL<<SYS_GPJ_MFPH_PJ9MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPJ_MFPH_PJ9MFP_eMMC1_DAT1        (0x06UL<<SYS_GPJ_MFPH_PJ9MFP_Pos)  /*!< eMMC1 data line bit 1. */
#define SYS_GPJ_MFPH_PJ9MFP_SD1_DAT1          (0x06UL<<SYS_GPJ_MFPH_PJ9MFP_Pos)  /*!< SD/SDIO1 data line bit 1. */
#define SYS_GPJ_MFPH_PJ10MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ10MFP_CAN0_RXD         (0x03UL<<SYS_GPJ_MFPH_PJ10MFP_Pos) /*!< CAN0 bus receiver input. */
#define SYS_GPJ_MFPH_PJ10MFP_USBHL1_DM        (0x04UL<<SYS_GPJ_MFPH_PJ10MFP_Pos) /*!< USB 1.1 host-lite 1 differential signal D-. */
#define SYS_GPJ_MFPH_PJ10MFP_eMMC1_DAT2       (0x06UL<<SYS_GPJ_MFPH_PJ10MFP_Pos) /*!< eMMC1 data line bit 2. */
#define SYS_GPJ_MFPH_PJ10MFP_SD1_DAT2         (0x06UL<<SYS_GPJ_MFPH_PJ10MFP_Pos) /*!< SD/SDIO1 data line bit 2. */
#define SYS_GPJ_MFPH_PJ11MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ11MFP_CAN0_TXD         (0x03UL<<SYS_GPJ_MFPH_PJ11MFP_Pos) /*!< CAN0 bus transmitter output. */
#define SYS_GPJ_MFPH_PJ11MFP_USBHL1_DP        (0x04UL<<SYS_GPJ_MFPH_PJ11MFP_Pos) /*!< USB 1.1 host-lite 1 differential signal D+. */
#define SYS_GPJ_MFPH_PJ11MFP_eMMC1_DAT3       (0x06UL<<SYS_GPJ_MFPH_PJ11MFP_Pos) /*!< eMMC1 data line bit 3. */
#define SYS_GPJ_MFPH_PJ11MFP_SD1_DAT3         (0x06UL<<SYS_GPJ_MFPH_PJ11MFP_Pos) /*!< SD/SDIO1 data line bit 3. */
#define SYS_GPJ_MFPH_PJ12MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ12MFP_EPWM1_CH2        (0x01UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< EPWM1 channel2 output/capture input. */
#define SYS_GPJ_MFPH_PJ12MFP_UART2_nCTS       (0x02UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< Clear to Send input pin for UART2. */
#define SYS_GPJ_MFPH_PJ12MFP_UART1_RXD        (0x03UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< Data receiver input pin for UART1. */
#define SYS_GPJ_MFPH_PJ12MFP_I2C5_SDA         (0x04UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< I2C5 data input/output pin. */
#define SYS_GPJ_MFPH_PJ12MFP_SPI3_SS0         (0x05UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< 1st SPI3 slave select pin. */
#define SYS_GPJ_MFPH_PJ12MFP_SC1_CLK          (0x07UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< SmartCard1 clock pin. */
#define SYS_GPJ_MFPH_PJ12MFP_EBI_ADR12        (0x08UL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPH_PJ12MFP_TM2              (0x0BUL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPJ_MFPH_PJ12MFP_QEI0_INDEX       (0x0CUL<<SYS_GPJ_MFPH_PJ12MFP_Pos) /*!< Quadrature encoder index input of QEI Unit 0. */
#define SYS_GPJ_MFPH_PJ13MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ13MFP_EPWM1_CH3        (0x01UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< EPWM1 channel3 output/capture input. */
#define SYS_GPJ_MFPH_PJ13MFP_UART2_nRTS       (0x02UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< Request to Send output pin for UART2. */
#define SYS_GPJ_MFPH_PJ13MFP_UART1_TXD        (0x03UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< Data transmitter output pin for UART1. */
#define SYS_GPJ_MFPH_PJ13MFP_I2C5_SCL         (0x04UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< I2C5 clock pin. */
#define SYS_GPJ_MFPH_PJ13MFP_SPI3_MOSI        (0x05UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< 1st SPI3 MOSI (Master Out, Slave In) pin. */
#define SYS_GPJ_MFPH_PJ13MFP_SC1_DAT          (0x07UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< SmartCard1 data pin. */
#define SYS_GPJ_MFPH_PJ13MFP_EBI_ADR13        (0x08UL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPH_PJ13MFP_TM2_EXT          (0x0BUL<<SYS_GPJ_MFPH_PJ13MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPJ_MFPH_PJ14MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ14MFP_EPWM1_CH4        (0x01UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPJ_MFPH_PJ14MFP_UART2_RXD        (0x02UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< Data receiver input pin for UART2. */
#define SYS_GPJ_MFPH_PJ14MFP_CAN3_RXD         (0x03UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPJ_MFPH_PJ14MFP_USBHL5_DM        (0x04UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< USB 1.1 host-lite 5 differential signal D-. */
#define SYS_GPJ_MFPH_PJ14MFP_SPI3_MISO        (0x05UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< 1st SPI3 MISO (Master In, Slave Out) pin. */
#define SYS_GPJ_MFPH_PJ14MFP_SC1_RST          (0x07UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< SmartCard1 reset pin. */
#define SYS_GPJ_MFPH_PJ14MFP_EBI_ADR14        (0x08UL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPH_PJ14MFP_TM3              (0x0BUL<<SYS_GPJ_MFPH_PJ14MFP_Pos) /*!< Timer3 event counter input / toggle output */
#define SYS_GPJ_MFPH_PJ15MFP_GPIO             (0x00UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPJ_MFPH_PJ15MFP_EPWM1_CH5        (0x01UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPJ_MFPH_PJ15MFP_UART2_TXD        (0x02UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< Data transmitter output pin for UART2. */
#define SYS_GPJ_MFPH_PJ15MFP_CAN3_TXD         (0x03UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< CAN3 bus transmitter output. */
#define SYS_GPJ_MFPH_PJ15MFP_USBHL5_DP        (0x04UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< USB 1.1 host-lite 5 differential signal D+. */
#define SYS_GPJ_MFPH_PJ15MFP_SPI3_CLK         (0x05UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< SPI3 serial clock pin. */
#define SYS_GPJ_MFPH_PJ15MFP_EADC0_ST         (0x06UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< EADC external trigger input. */
#define SYS_GPJ_MFPH_PJ15MFP_SC1_PWR          (0x07UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< SmartCard1 power pin. */
#define SYS_GPJ_MFPH_PJ15MFP_EBI_ADR15        (0x08UL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPJ_MFPH_PJ15MFP_TM3_EXT          (0x0BUL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< Timer3 event counter input / toggle output */
#define SYS_GPJ_MFPH_PJ15MFP_INT1             (0x0DUL<<SYS_GPJ_MFPH_PJ15MFP_Pos) /*!< External interrupt1 input pin. */
/********************* Bit definition of GPK_MFPL register **********************/
#define SYS_GPK_MFPL_PK0MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK0MFP_EPWM0_SYNC_IN     (0x01UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< EPWM0 counter synchronous trigger input pin. */
#define SYS_GPK_MFPL_PK0MFP_UART16_nCTS       (0x02UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< Clear to Send input pin for UART16. */
#define SYS_GPK_MFPL_PK0MFP_UART15_RXD        (0x03UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< Data receiver input pin for UART15. */
#define SYS_GPK_MFPL_PK0MFP_I2C4_SDA          (0x04UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPK_MFPL_PK0MFP_I2S1_MCLK         (0x06UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPK_MFPL_PK0MFP_EBI_ADR8          (0x08UL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPL_PK0MFP_TM7               (0x0BUL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< Timer7 event counter input / toggle output */
#define SYS_GPK_MFPL_PK0MFP_ECAP0_IC1         (0x0CUL<<SYS_GPK_MFPL_PK0MFP_Pos)  /*!< Input 1 of enhanced capture unit 0. */
#define SYS_GPK_MFPL_PK1MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK1MFP_EPWM0_SYNC_OUT    (0x01UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< EPWM0 counter synchronous trigger output pin. */
#define SYS_GPK_MFPL_PK1MFP_UART16_nRTS       (0x02UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< Request to Send output pin for UART16. */
#define SYS_GPK_MFPL_PK1MFP_UART15_TXD        (0x03UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< Data transmitter output pin for UART15. */
#define SYS_GPK_MFPL_PK1MFP_I2C4_SCL          (0x04UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPK_MFPL_PK1MFP_EADC0_ST          (0x06UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< EADC external trigger input. */
#define SYS_GPK_MFPL_PK1MFP_EBI_ADR9          (0x08UL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPL_PK1MFP_TM7_EXT           (0x0BUL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< Timer7 event counter input / toggle output */
#define SYS_GPK_MFPL_PK1MFP_ECAP0_IC2         (0x0CUL<<SYS_GPK_MFPL_PK1MFP_Pos)  /*!< Input 0 of enhanced capture unit 2. */
#define SYS_GPK_MFPL_PK2MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK2MFP_EPWM1_CH0         (0x01UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< EPWM1 channel0 output/capture input. */
#define SYS_GPK_MFPL_PK2MFP_UART16_RXD        (0x02UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< Data receiver input pin for UART16. */
#define SYS_GPK_MFPL_PK2MFP_CAN2_RXD          (0x03UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< CAN2 bus receiver input. */
#define SYS_GPK_MFPL_PK2MFP_USBHL4_DM         (0x04UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPK_MFPL_PK2MFP_SPI3_I2SMCLK      (0x05UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< SPI3 I2S master clock output pin. */
#define SYS_GPK_MFPL_PK2MFP_SC0_PWR           (0x07UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< SmartCard0 power pin. */
#define SYS_GPK_MFPL_PK2MFP_EBI_ADR10         (0x08UL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPL_PK2MFP_QEI0_A            (0x0CUL<<SYS_GPK_MFPL_PK2MFP_Pos)  /*!< Quadrature encoder phase A input of QEI Unit 0. */
#define SYS_GPK_MFPL_PK3MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK3MFP_EPWM1_CH1         (0x01UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< EPWM1 channel1 output/capture input. */
#define SYS_GPK_MFPL_PK3MFP_UART16_TXD        (0x02UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< Data transmitter output pin for UART16. */
#define SYS_GPK_MFPL_PK3MFP_CAN2_TXD          (0x03UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< CAN2 bus transmitter output. */
#define SYS_GPK_MFPL_PK3MFP_USBHL4_DP         (0x04UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPK_MFPL_PK3MFP_SPI3_SS1          (0x05UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< 1st SPI3 slave select pin. */
#define SYS_GPK_MFPL_PK3MFP_SC1_nCD           (0x07UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< SmartCard1 card detect pin. */
#define SYS_GPK_MFPL_PK3MFP_EBI_ADR11         (0x08UL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPL_PK3MFP_QEI0_B            (0x0CUL<<SYS_GPK_MFPL_PK3MFP_Pos)  /*!< Quadrature encoder phase B input of QEI Unit 0. */
#define SYS_GPK_MFPL_PK4MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK4MFP_UART12_nCTS       (0x02UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< Clear to Send input pin for UART12. */
#define SYS_GPK_MFPL_PK4MFP_UART13_RXD        (0x03UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< Data receiver input pin for UART13. */
#define SYS_GPK_MFPL_PK4MFP_SPI2_MISO         (0x05UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< 1st SPI2 MISO (Master In, Slave Out) pin. */
#define SYS_GPK_MFPL_PK4MFP_LCM_DEN           (0x06UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< TFT LCD Module Data Enable/Display Control Signal output pin in Sync-type mode. */
#define SYS_GPK_MFPL_PK4MFP_LCM_MPU_DCX       (0x06UL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< TFT LCD Module Register Select (RS) output pin in MPU-type mode. */
#define SYS_GPK_MFPL_PK4MFP_EBI_AD10          (0x0CUL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPK_MFPL_PK4MFP_EBI_nWRL          (0x0DUL<<SYS_GPK_MFPL_PK4MFP_Pos)  /*!< EBI write enable output pin. */
#define SYS_GPK_MFPL_PK5MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK5MFP_EPWM1_CH1         (0x01UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< EPWM1 channel1 output/capture input. */
#define SYS_GPK_MFPL_PK5MFP_UART12_nRTS       (0x02UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< Request to Send output pin for UART12. */
#define SYS_GPK_MFPL_PK5MFP_UART13_TXD        (0x03UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< Data transmitter output pin for UART13. */
#define SYS_GPK_MFPL_PK5MFP_I2C4_SCL          (0x04UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPK_MFPL_PK5MFP_SPI2_CLK          (0x05UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< SPI2 serial clock pin. */
#define SYS_GPK_MFPL_PK5MFP_I2S1_DI           (0x07UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< I2S1 data input. */
#define SYS_GPK_MFPL_PK5MFP_SC0_DAT           (0x08UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< SmartCard0 data pin. */
#define SYS_GPK_MFPL_PK5MFP_EADC0_ST          (0x09UL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< EADC external trigger input. */
#define SYS_GPK_MFPL_PK5MFP_TM8_EXT           (0x0BUL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< Timer8 event counter input / toggle output */
#define SYS_GPK_MFPL_PK5MFP_INT1              (0x0DUL<<SYS_GPK_MFPL_PK5MFP_Pos)  /*!< External interrupt1 input pin. */
#define SYS_GPK_MFPL_PK6MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK6MFP_EPWM1_CH2         (0x01UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< EPWM1 channel2 output/capture input. */
#define SYS_GPK_MFPL_PK6MFP_UART12_RXD        (0x02UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< Data receiver input pin for UART12. */
#define SYS_GPK_MFPL_PK6MFP_CAN0_RXD          (0x03UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPK_MFPL_PK6MFP_USBHL4_DM         (0x04UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPK_MFPL_PK6MFP_SPI2_MOSI         (0x05UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< 1st SPI2 MOSI (Master Out, Slave In) pin. */
#define SYS_GPK_MFPL_PK6MFP_I2S1_BCLK         (0x07UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< I2S1 bit clock pin. */
#define SYS_GPK_MFPL_PK6MFP_SC0_RST           (0x08UL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< SmartCard0 reset pin. */
#define SYS_GPK_MFPL_PK6MFP_TM6               (0x0BUL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< Timer6 event counter input / toggle output */
#define SYS_GPK_MFPL_PK6MFP_INT2              (0x0DUL<<SYS_GPK_MFPL_PK6MFP_Pos)  /*!< External interrupt2 input pin. */
#define SYS_GPK_MFPL_PK7MFP_GPIO              (0x00UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPL_PK7MFP_EPWM1_CH3         (0x01UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< EPWM1 channel3 output/capture input. */
#define SYS_GPK_MFPL_PK7MFP_UART12_TXD        (0x02UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< Data transmitter output pin for UART12. */
#define SYS_GPK_MFPL_PK7MFP_CAN0_TXD          (0x03UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPK_MFPL_PK7MFP_USBHL4_DP         (0x04UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPK_MFPL_PK7MFP_SPI2_MISO         (0x05UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< 1st SPI2 MISO (Master In, Slave Out) pin. */
#define SYS_GPK_MFPL_PK7MFP_I2S1_LRCK         (0x07UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< I2S1 left right channel clock. */
#define SYS_GPK_MFPL_PK7MFP_SC0_PWR           (0x08UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< SmartCard0 power pin. */
#define SYS_GPK_MFPL_PK7MFP_CLKO              (0x09UL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< Clock Output pin. */
#define SYS_GPK_MFPL_PK7MFP_TM6_EXT           (0x0BUL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< Timer6 event counter input / toggle output */
#define SYS_GPK_MFPL_PK7MFP_INT3              (0x0DUL<<SYS_GPK_MFPL_PK7MFP_Pos)  /*!< External interrupt3 input pin. */
/********************* Bit definition of GPK_MFPH register **********************/
#define SYS_GPK_MFPH_PK8MFP_GPIO              (0x00UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK8MFP_EPWM1_CH0         (0x01UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< EPWM1 channel0 output/capture input. */
#define SYS_GPK_MFPH_PK8MFP_I2C3_SDA          (0x04UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< I2C3 data input/output pin. */
#define SYS_GPK_MFPH_PK8MFP_SPI3_CLK          (0x05UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< SPI3 serial clock pin. */
#define SYS_GPK_MFPH_PK8MFP_EADC0_ST          (0x07UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< EADC external trigger input. */
#define SYS_GPK_MFPH_PK8MFP_EBI_AD15          (0x08UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPK_MFPH_PK8MFP_EBI_MCLK          (0x09UL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< EBI external clock output pin. */
#define SYS_GPK_MFPH_PK8MFP_EBI_ADR15         (0x0AUL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPH_PK8MFP_TM8               (0x0BUL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< Timer8 event counter input / toggle output */
#define SYS_GPK_MFPH_PK8MFP_QEI1_INDEX        (0x0CUL<<SYS_GPK_MFPH_PK8MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 1. */
#define SYS_GPK_MFPH_PK9MFP_GPIO              (0x00UL<<SYS_GPK_MFPH_PK9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK9MFP_I2C3_SCL          (0x04UL<<SYS_GPK_MFPH_PK9MFP_Pos)  /*!< I2C3 clock pin. */
#define SYS_GPK_MFPH_PK9MFP_CCAP0_SCLK        (0x06UL<<SYS_GPK_MFPH_PK9MFP_Pos)  /*!< Camera capture 0 interface sensor clock output pin. */
#define SYS_GPK_MFPH_PK9MFP_EBI_AD0           (0x08UL<<SYS_GPK_MFPH_PK9MFP_Pos)  /*!< EBI address/data bus bit0. */
#define SYS_GPK_MFPH_PK9MFP_EBI_ADR0          (0x0AUL<<SYS_GPK_MFPH_PK9MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPH_PK10MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK10MFP_CAN1_RXD         (0x03UL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< CAN1 bus receiver input. */
#define SYS_GPK_MFPH_PK10MFP_USBHL3_DM        (0x04UL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPK_MFPH_PK10MFP_CCAP0_PIXCLK     (0x06UL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< Camera capture 0 interface pixel clock input pin. */
#define SYS_GPK_MFPH_PK10MFP_EBI_AD1          (0x08UL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPK_MFPH_PK10MFP_EBI_ADR1         (0x0AUL<<SYS_GPK_MFPH_PK10MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPH_PK11MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK11MFP_CAN1_TXD         (0x03UL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< CAN1 bus transmitter output. */
#define SYS_GPK_MFPH_PK11MFP_USBHL3_DP        (0x04UL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPK_MFPH_PK11MFP_CCAP0_HSYNC      (0x06UL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< Camera capture 0 interface hsync input pin. */
#define SYS_GPK_MFPH_PK11MFP_EBI_AD2          (0x08UL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< EBI address/data bus bit2. */
#define SYS_GPK_MFPH_PK11MFP_EBI_ADR2         (0x0AUL<<SYS_GPK_MFPH_PK11MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPK_MFPH_PK12MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK12MFP_EPWM2_CH0        (0x01UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< EPWM2 channel0 output/capture input. */
#define SYS_GPK_MFPH_PK12MFP_UART1_nCTS       (0x02UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< Clear to Send input pin for UART1. */
#define SYS_GPK_MFPH_PK12MFP_UART13_RXD       (0x03UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< Data receiver input pin for UART13. */
#define SYS_GPK_MFPH_PK12MFP_I2C4_SDA         (0x04UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< I2C4 data input/output pin. */
#define SYS_GPK_MFPH_PK12MFP_I2S0_LRCK        (0x05UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< I2S0 left right channel clock. */
#define SYS_GPK_MFPH_PK12MFP_SPI1_SS0         (0x06UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPK_MFPH_PK12MFP_SC0_CLK          (0x08UL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< SmartCard0 clock pin. */
#define SYS_GPK_MFPH_PK12MFP_TM10             (0x0BUL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPK_MFPH_PK12MFP_INT2             (0x0DUL<<SYS_GPK_MFPH_PK12MFP_Pos) /*!< External interrupt2 input pin. */
#define SYS_GPK_MFPH_PK13MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK13MFP_EPWM2_CH1        (0x01UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< EPWM2 channel1 output/capture input. */
#define SYS_GPK_MFPH_PK13MFP_UART1_nRTS       (0x02UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< Request to Send output pin for UART1. */
#define SYS_GPK_MFPH_PK13MFP_UART13_TXD       (0x03UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< Data transmitter output pin for UART13. */
#define SYS_GPK_MFPH_PK13MFP_I2C4_SCL         (0x04UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< I2C4 clock pin. */
#define SYS_GPK_MFPH_PK13MFP_I2S0_BCLK        (0x05UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< I2S0 bit clock pin. */
#define SYS_GPK_MFPH_PK13MFP_SPI1_CLK         (0x06UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< SPI1 serial clock pin. */
#define SYS_GPK_MFPH_PK13MFP_SC0_DAT          (0x08UL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< SmartCard0 data pin. */
#define SYS_GPK_MFPH_PK13MFP_TM10_EXT         (0x0BUL<<SYS_GPK_MFPH_PK13MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPK_MFPH_PK14MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK14MFP_EPWM2_CH2        (0x01UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< EPWM2 channel2 output/capture input. */
#define SYS_GPK_MFPH_PK14MFP_UART1_RXD        (0x02UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< Data receiver input pin for UART1. */
#define SYS_GPK_MFPH_PK14MFP_CAN3_RXD         (0x03UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPK_MFPH_PK14MFP_USBHL4_DM        (0x04UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPK_MFPH_PK14MFP_I2S0_DI          (0x05UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< I2S0 data input. */
#define SYS_GPK_MFPH_PK14MFP_SPI1_MOSI        (0x06UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< 1st SPI1 MOSI (Master Out, Slave In) pin. */
#define SYS_GPK_MFPH_PK14MFP_SC0_RST          (0x08UL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< SmartCard0 reset pin. */
#define SYS_GPK_MFPH_PK14MFP_I2C5_SDA         (0x0AUL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< I2C5 data input/output pin. */
#define SYS_GPK_MFPH_PK14MFP_TM11             (0x0BUL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPK_MFPH_PK14MFP_INT3             (0x0DUL<<SYS_GPK_MFPH_PK14MFP_Pos) /*!< External interrupt3 input pin. */
#define SYS_GPK_MFPH_PK15MFP_GPIO             (0x00UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPK_MFPH_PK15MFP_EPWM2_CH3        (0x01UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< EPWM2 channel3 output/capture input. */
#define SYS_GPK_MFPH_PK15MFP_UART1_TXD        (0x02UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< Data transmitter output pin for UART1. */
#define SYS_GPK_MFPH_PK15MFP_CAN3_TXD         (0x03UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< CAN3 bus transmitter output. */
#define SYS_GPK_MFPH_PK15MFP_USBHL4_DP        (0x04UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPK_MFPH_PK15MFP_I2S0_DO          (0x05UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< I2S0 data output. */
#define SYS_GPK_MFPH_PK15MFP_SPI1_MISO        (0x06UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< 1st SPI1 MISO (Master In, Slave Out) pin. */
#define SYS_GPK_MFPH_PK15MFP_SC0_PWR          (0x08UL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< SmartCard0 power pin. */
#define SYS_GPK_MFPH_PK15MFP_I2C5_SCL         (0x0AUL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< I2C5 clock pin. */
#define SYS_GPK_MFPH_PK15MFP_TM11_EXT         (0x0BUL<<SYS_GPK_MFPH_PK15MFP_Pos) /*!< Timer1 event counter input / toggle output */
/********************* Bit definition of GPL_MFPL register **********************/
#define SYS_GPL_MFPL_PL0MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL0MFP_EPWM1_CH0         (0x01UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< EPWM1 channel0 output/capture input. */
#define SYS_GPL_MFPL_PL0MFP_UART11_nCTS       (0x02UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< Clear to Send input pin for UART11. */
#define SYS_GPL_MFPL_PL0MFP_UART10_RXD        (0x03UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< Data receiver input pin for UART10. */
#define SYS_GPL_MFPL_PL0MFP_I2C3_SDA          (0x04UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< I2C3 data input/output pin. */
#define SYS_GPL_MFPL_PL0MFP_SPI2_MOSI         (0x05UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< 1st SPI2 MOSI (Master Out, Slave In) pin. */
#define SYS_GPL_MFPL_PL0MFP_QSPI1_MOSI1       (0x06UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< Quad SPI1 MOSI1 (Master Out, Slave In) pin. */
#define SYS_GPL_MFPL_PL0MFP_I2S0_LRCK         (0x07UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< I2S0 left right channel clock. */
#define SYS_GPL_MFPL_PL0MFP_EBI_AD11          (0x08UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPL_PL0MFP_SC1_CLK           (0x09UL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< SmartCard1 clock pin. */
#define SYS_GPL_MFPL_PL0MFP_TM5               (0x0BUL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< Timer5 event counter input / toggle output */
#define SYS_GPL_MFPL_PL0MFP_QEI1_A            (0x0CUL<<SYS_GPL_MFPL_PL0MFP_Pos)  /*!< Quadrature encoder phase A input of QEI Unit 1. */
#define SYS_GPL_MFPL_PL1MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL1MFP_EPWM1_CH1         (0x01UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< EPWM1 channel1 output/capture input. */
#define SYS_GPL_MFPL_PL1MFP_UART11_nRTS       (0x02UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< Request to Send output pin for UART11. */
#define SYS_GPL_MFPL_PL1MFP_UART10_TXD        (0x03UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< Data transmitter output pin for UART10. */
#define SYS_GPL_MFPL_PL1MFP_I2C3_SCL          (0x04UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< I2C3 clock pin. */
#define SYS_GPL_MFPL_PL1MFP_SPI2_MISO         (0x05UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< 1st SPI2 MISO (Master In, Slave Out) pin. */
#define SYS_GPL_MFPL_PL1MFP_QSPI1_MISO1       (0x06UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< Quad SPI1 MISO1 (Master In, Slave Out) pin. */
#define SYS_GPL_MFPL_PL1MFP_I2S0_BCLK         (0x07UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< I2S0 bit clock pin. */
#define SYS_GPL_MFPL_PL1MFP_EBI_AD12          (0x08UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPL_PL1MFP_SC1_DAT           (0x09UL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< SmartCard1 data pin. */
#define SYS_GPL_MFPL_PL1MFP_TM5_EXT           (0x0BUL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< Timer5 event counter input / toggle output */
#define SYS_GPL_MFPL_PL1MFP_QEI1_B            (0x0CUL<<SYS_GPL_MFPL_PL1MFP_Pos)  /*!< Quadrature encoder phase B input of QEI Unit 1. */
#define SYS_GPL_MFPL_PL2MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL2MFP_EPWM1_CH2         (0x01UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< EPWM1 channel2 output/capture input. */
#define SYS_GPL_MFPL_PL2MFP_UART11_RXD        (0x02UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< Data receiver input pin for UART11. */
#define SYS_GPL_MFPL_PL2MFP_CAN3_RXD          (0x03UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< CAN3 bus receiver input. */
#define SYS_GPL_MFPL_PL2MFP_USBHL4_DM         (0x04UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPL_MFPL_PL2MFP_SPI2_SS0          (0x05UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< 1st SPI2 slave select pin. */
#define SYS_GPL_MFPL_PL2MFP_QSPI1_SS1         (0x06UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< Quad SPI1 slave select pin. */
#define SYS_GPL_MFPL_PL2MFP_I2S0_DI           (0x07UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< I2S0 data input. */
#define SYS_GPL_MFPL_PL2MFP_EBI_AD13          (0x08UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPL_PL2MFP_SC1_RST           (0x09UL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< SmartCard1 reset pin. */
#define SYS_GPL_MFPL_PL2MFP_TM7               (0x0BUL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< Timer7 event counter input / toggle output */
#define SYS_GPL_MFPL_PL2MFP_QEI1_INDEX        (0x0CUL<<SYS_GPL_MFPL_PL2MFP_Pos)  /*!< Quadrature encoder index input of QEI Unit 1. */
#define SYS_GPL_MFPL_PL3MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL3MFP_EPWM1_CH3         (0x01UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< EPWM1 channel3 output/capture input. */
#define SYS_GPL_MFPL_PL3MFP_UART11_TXD        (0x02UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< Data transmitter output pin for UART11. */
#define SYS_GPL_MFPL_PL3MFP_CAN3_TXD          (0x03UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< CAN3 bus transmitter output. */
#define SYS_GPL_MFPL_PL3MFP_USBHL4_DP         (0x04UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPL_MFPL_PL3MFP_SPI2_CLK          (0x05UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< SPI2 serial clock pin. */
#define SYS_GPL_MFPL_PL3MFP_QSPI1_CLK         (0x06UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< Quad SPI1 serial clock pin. */
#define SYS_GPL_MFPL_PL3MFP_I2S0_DO           (0x07UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< I2S0 data output. */
#define SYS_GPL_MFPL_PL3MFP_EBI_AD14          (0x08UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPL_PL3MFP_SC1_PWR           (0x09UL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< SmartCard1 power pin. */
#define SYS_GPL_MFPL_PL3MFP_TM7_EXT           (0x0BUL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< Timer7 event counter input / toggle output */
#define SYS_GPL_MFPL_PL3MFP_ECAP0_IC0         (0x0CUL<<SYS_GPL_MFPL_PL3MFP_Pos)  /*!< Input 0 of enhanced capture unit 0. */
#define SYS_GPL_MFPL_PL4MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL4MFP_EPWM1_CH4         (0x01UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPL_MFPL_PL4MFP_UART2_nCTS        (0x02UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< Clear to Send input pin for UART2. */
#define SYS_GPL_MFPL_PL4MFP_UART1_RXD         (0x03UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< Data receiver input pin for UART1. */
#define SYS_GPL_MFPL_PL4MFP_I2C4_SDA          (0x04UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPL_MFPL_PL4MFP_SPI3_MOSI         (0x05UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< 1st SPI3 MOSI (Master Out, Slave In) pin. */
#define SYS_GPL_MFPL_PL4MFP_QSPI1_MOSI0       (0x06UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< Quad SPI1 MOSI0 (Master Out, Slave In) pin. */
#define SYS_GPL_MFPL_PL4MFP_I2S0_MCLK         (0x07UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< I2S0 master clock output pin. */
#define SYS_GPL_MFPL_PL4MFP_EBI_nRD           (0x08UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< EBI read enable output pin. */
#define SYS_GPL_MFPL_PL4MFP_SC1_nCD           (0x09UL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< SmartCard1 card detect pin. */
#define SYS_GPL_MFPL_PL4MFP_TM9               (0x0BUL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< Timer9 event counter input / toggle output */
#define SYS_GPL_MFPL_PL4MFP_ECAP0_IC1         (0x0CUL<<SYS_GPL_MFPL_PL4MFP_Pos)  /*!< Input 1 of enhanced capture unit 0. */
#define SYS_GPL_MFPL_PL5MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL5MFP_EPWM1_CH5         (0x01UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPL_MFPL_PL5MFP_UART2_nRTS        (0x02UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< Request to Send output pin for UART2. */
#define SYS_GPL_MFPL_PL5MFP_UART1_TXD         (0x03UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< Data transmitter output pin for UART1. */
#define SYS_GPL_MFPL_PL5MFP_I2C4_SCL          (0x04UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPL_MFPL_PL5MFP_SPI3_MISO         (0x05UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< 1st SPI3 MISO (Master In, Slave Out) pin. */
#define SYS_GPL_MFPL_PL5MFP_QSPI1_MISO0       (0x06UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< Quad SPI1 MISO0 (Master In, Slave Out) pin. */
#define SYS_GPL_MFPL_PL5MFP_I2S1_MCLK         (0x07UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< I2S1 master clock output pin. */
#define SYS_GPL_MFPL_PL5MFP_EBI_nWR           (0x08UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< EBI write enable output pin. */
#define SYS_GPL_MFPL_PL5MFP_SC0_nCD           (0x09UL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< SmartCard0 card detect pin. */
#define SYS_GPL_MFPL_PL5MFP_TM9_EXT           (0x0BUL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< Timer* event counter input / toggle output */
#define SYS_GPL_MFPL_PL5MFP_ECAP0_IC2         (0x0CUL<<SYS_GPL_MFPL_PL5MFP_Pos)  /*!< Input 0 of enhanced capture unit 2. */
#define SYS_GPL_MFPL_PL6MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL6MFP_EPWM0_CH0         (0x01UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< EPWM0 channel0 output/capture input. */
#define SYS_GPL_MFPL_PL6MFP_UART2_RXD         (0x02UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< Data receiver input pin for UART2. */
#define SYS_GPL_MFPL_PL6MFP_CAN0_RXD          (0x03UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPL_MFPL_PL6MFP_USBHL5_DM         (0x04UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D-. */
#define SYS_GPL_MFPL_PL6MFP_QSPI1_MOSI1       (0x06UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< Quad SPI1 MOSI1 (Master Out, Slave In) pin. */
#define SYS_GPL_MFPL_PL6MFP_TRACE_CLK         (0x07UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< ETM Rx clock input pin. */
#define SYS_GPL_MFPL_PL6MFP_EBI_AD5           (0x08UL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< EBI address/data bus bit5. */
#define SYS_GPL_MFPL_PL6MFP_TM3               (0x0BUL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< Timer3 event counter input / toggle output */
#define SYS_GPL_MFPL_PL6MFP_ECAP1_IC0         (0x0CUL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< Input 0 of enhanced capture unit 1. */
#define SYS_GPL_MFPL_PL6MFP_INT0              (0x0DUL<<SYS_GPL_MFPL_PL6MFP_Pos)  /*!< External interrupt0 input pin. */
#define SYS_GPL_MFPL_PL7MFP_GPIO              (0x00UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPL_PL7MFP_EPWM0_CH1         (0x01UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< EPWM0 channel1 output/capture input. */
#define SYS_GPL_MFPL_PL7MFP_UART2_TXD         (0x02UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< Data transmitter output pin for UART2. */
#define SYS_GPL_MFPL_PL7MFP_CAN0_TXD          (0x03UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPL_MFPL_PL7MFP_USBHL5_DP         (0x04UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< USB 1.1 host-lite 5 differential signal D+. */
#define SYS_GPL_MFPL_PL7MFP_QSPI1_MISO1       (0x06UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< Quad SPI1 MISO1 (Master In, Slave Out) pin. */
#define SYS_GPL_MFPL_PL7MFP_EBI_AD6           (0x08UL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< EBI address/data bus bit6. */
#define SYS_GPL_MFPL_PL7MFP_TM3_EXT           (0x0BUL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< Timer3 event counter input / toggle output */
#define SYS_GPL_MFPL_PL7MFP_ECAP1_IC1         (0x0CUL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< Input 1 of enhanced capture unit 1. */
#define SYS_GPL_MFPL_PL7MFP_INT1              (0x0DUL<<SYS_GPL_MFPL_PL7MFP_Pos)  /*!< External interrupt1 input pin. */
/********************* Bit definition of GPL_MFPH register **********************/
#define SYS_GPL_MFPH_PL8MFP_GPIO              (0x00UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL8MFP_EPWM0_CH2         (0x01UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPL_MFPH_PL8MFP_UART14_nCTS       (0x02UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< Clear to Send input pin for UART14. */
#define SYS_GPL_MFPH_PL8MFP_UART13_RXD        (0x03UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< Data receiver input pin for UART13. */
#define SYS_GPL_MFPH_PL8MFP_I2C5_SDA          (0x04UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< I2C5 data input/output pin. */
#define SYS_GPL_MFPH_PL8MFP_SPI3_SS0          (0x05UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< 1st SPI3 slave select pin. */
#define SYS_GPL_MFPH_PL8MFP_EPWM0_CH4         (0x06UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< EPWM0 channel4 output/capture input. */
#define SYS_GPL_MFPH_PL8MFP_I2S1_LRCK         (0x07UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< I2S1 left right channel clock. */
#define SYS_GPL_MFPH_PL8MFP_EBI_AD7           (0x08UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPL_MFPH_PL8MFP_SC0_CLK           (0x09UL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< SmartCard0 clock pin. */
#define SYS_GPL_MFPH_PL8MFP_TM4               (0x0BUL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< Timer4 event counter input / toggle output */
#define SYS_GPL_MFPH_PL8MFP_ECAP1_IC2         (0x0CUL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< Input 1 of enhanced capture unit 2. */
#define SYS_GPL_MFPH_PL8MFP_INT2              (0x0DUL<<SYS_GPL_MFPH_PL8MFP_Pos)  /*!< External interrupt2 input pin. */
#define SYS_GPL_MFPH_PL9MFP_GPIO              (0x00UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL9MFP_EPWM0_CH3         (0x01UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< EPWM0 channel3 output/capture input. */
#define SYS_GPL_MFPH_PL9MFP_UART14_nRTS       (0x02UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< Request to Send output pin for UART14. */
#define SYS_GPL_MFPH_PL9MFP_UART13_TXD        (0x03UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< Data transmitter output pin for UART13. */
#define SYS_GPL_MFPH_PL9MFP_I2C5_SCL          (0x04UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< I2C5 clock pin. */
#define SYS_GPL_MFPH_PL9MFP_SPI3_CLK          (0x05UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< SPI3 serial clock pin. */
#define SYS_GPL_MFPH_PL9MFP_EPWM1_CH4         (0x06UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPL_MFPH_PL9MFP_I2S1_BCLK         (0x07UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< I2S1 bit clock pin. */
#define SYS_GPL_MFPH_PL9MFP_EBI_AD8           (0x08UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPL_MFPH_PL9MFP_SC0_DAT           (0x09UL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< SmartCard0 data pin. */
#define SYS_GPL_MFPH_PL9MFP_TM4_EXT           (0x0BUL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< Timer4 event counter input / toggle output */
#define SYS_GPL_MFPH_PL9MFP_QEI0_A            (0x0CUL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< Quadrature encoder phase A input of QEI Unit 0. */
#define SYS_GPL_MFPH_PL9MFP_INT3              (0x0DUL<<SYS_GPL_MFPH_PL9MFP_Pos)  /*!< External interrupt3 input pin. */
#define SYS_GPL_MFPH_PL10MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL10MFP_EPWM0_CH4        (0x01UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< EPWM0 channel4 output/capture input. */
#define SYS_GPL_MFPH_PL10MFP_UART14_RXD       (0x02UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< Data receiver input pin for UART14. */
#define SYS_GPL_MFPH_PL10MFP_CAN3_RXD         (0x03UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPL_MFPH_PL10MFP_USBHL2_DM        (0x04UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D-. */
#define SYS_GPL_MFPH_PL10MFP_SPI3_MOSI        (0x05UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< 1st SPI3 MOSI (Master Out, Slave In) pin. */
#define SYS_GPL_MFPH_PL10MFP_EPWM0_CH5        (0x06UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< EPWM0 channel5 output/capture input. */
#define SYS_GPL_MFPH_PL10MFP_I2S1_DI          (0x07UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< I2S1 data input. */
#define SYS_GPL_MFPH_PL10MFP_EBI_AD9          (0x08UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< EBI address/data bus bit9. */
#define SYS_GPL_MFPH_PL10MFP_SC0_RST          (0x09UL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< SmartCard0 reset pin. */
#define SYS_GPL_MFPH_PL10MFP_EBI_nWRH         (0x0BUL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< EBI write enable output pin. */
#define SYS_GPL_MFPH_PL10MFP_QEI0_B           (0x0CUL<<SYS_GPL_MFPH_PL10MFP_Pos) /*!< Quadrature encoder phase B input of QEI Unit 0. */
#define SYS_GPL_MFPH_PL11MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL11MFP_EPWM0_CH5        (0x01UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< EPWM0 channel5 output/capture input. */
#define SYS_GPL_MFPH_PL11MFP_UART14_TXD       (0x02UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< Data transmitter output pin for UART14. */
#define SYS_GPL_MFPH_PL11MFP_CAN3_TXD         (0x03UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< CAN3 bus transmitter output. */
#define SYS_GPL_MFPH_PL11MFP_USBHL2_DP        (0x04UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D+. */
#define SYS_GPL_MFPH_PL11MFP_SPI3_MISO        (0x05UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< 1st SPI3 MISO (Master In, Slave Out) pin. */
#define SYS_GPL_MFPH_PL11MFP_EPWM1_CH5        (0x06UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPL_MFPH_PL11MFP_I2S1_DO          (0x07UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< I2S1 data output. */
#define SYS_GPL_MFPH_PL11MFP_EBI_AD10         (0x08UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPH_PL11MFP_SC0_PWR          (0x09UL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< SmartCard0 power pin. */
#define SYS_GPL_MFPH_PL11MFP_EBI_nWRL         (0x0BUL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< EBI write enable output pin. */
#define SYS_GPL_MFPH_PL11MFP_QEI0_INDEX       (0x0CUL<<SYS_GPL_MFPH_PL11MFP_Pos) /*!< Quadrature encoder index input of QEI Unit 0. */
#define SYS_GPL_MFPH_PL12MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL12MFP_EPWM0_SYNC_IN    (0x01UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< EPWM0 counter synchronous trigger input pin. */
#define SYS_GPL_MFPH_PL12MFP_UART7_nCTS       (0x02UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< Clear to Send input pin for UART7. */
#define SYS_GPL_MFPH_PL12MFP_ECAP1_IC0        (0x03UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< Input 0 of enhanced capture unit 1. */
#define SYS_GPL_MFPH_PL12MFP_UART14_RXD       (0x04UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< Data receiver input pin for UART14. */
#define SYS_GPL_MFPH_PL12MFP_SPI0_SS0         (0x05UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< 1st SPI0 slave select pin. */
#define SYS_GPL_MFPH_PL12MFP_I2S1_LRCK        (0x06UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< I2S1 left right channel clock. */
#define SYS_GPL_MFPH_PL12MFP_SC1_CLK          (0x07UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< SmartCard1 clock pin. */
#define SYS_GPL_MFPH_PL12MFP_EBI_AD0          (0x08UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< EBI address/data bus bit0. */
#define SYS_GPL_MFPH_PL12MFP_HSUSBH_PWREN     (0x09UL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< HSUSB host external VBUS regulator enable pin. */
#define SYS_GPL_MFPH_PL12MFP_I2C2_SDA         (0x0AUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< I2C2 data input/output pin. */
#define SYS_GPL_MFPH_PL12MFP_TM0              (0x0BUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< Timer0 event counter input / toggle output */
#define SYS_GPL_MFPH_PL12MFP_EPWM0_CH2        (0x0CUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPL_MFPH_PL12MFP_EBI_AD11         (0x0DUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPH_PL12MFP_RGMII0_PPS       (0x0EUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< RGMII0 Pulse Per Second output pin. */
#define SYS_GPL_MFPH_PL12MFP_RMII0_PPS        (0x0FUL<<SYS_GPL_MFPH_PL12MFP_Pos) /*!< RMII0 Pulse Per Second output pin. */
#define SYS_GPL_MFPH_PL13MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL13MFP_EPWM0_SYNC_OUT   (0x01UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< EPWM0 counter synchronous trigger output pin. */
#define SYS_GPL_MFPH_PL13MFP_UART7_nRTS       (0x02UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< Request to Send output pin for UART7. */
#define SYS_GPL_MFPH_PL13MFP_ECAP1_IC1        (0x03UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< Input 1 of enhanced capture unit 1. */
#define SYS_GPL_MFPH_PL13MFP_UART14_TXD       (0x04UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< Data transmitter output pin for UART14. */
#define SYS_GPL_MFPH_PL13MFP_SPI0_CLK         (0x05UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< SPI0 serial clock pin. */
#define SYS_GPL_MFPH_PL13MFP_I2S1_BCLK        (0x06UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< I2S1 bit clock pin. */
#define SYS_GPL_MFPH_PL13MFP_SC1_DAT          (0x07UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< SmartCard1 data pin. */
#define SYS_GPL_MFPH_PL13MFP_EBI_AD1          (0x08UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPH_PL13MFP_HSUSBH_OVC       (0x09UL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< HSUSB host bus power over current detector pin. */
#define SYS_GPL_MFPH_PL13MFP_I2C2_SCL         (0x0AUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< I2C2 clock pin. */
#define SYS_GPL_MFPH_PL13MFP_TM0_EXT          (0x0BUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< Timer0 event counter input / toggle output */
#define SYS_GPL_MFPH_PL13MFP_EPWM0_CH3        (0x0CUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< EPWM0 channel3 output/capture input. */
#define SYS_GPL_MFPH_PL13MFP_EBI_AD12         (0x0DUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPH_PL13MFP_RGMII1_PPS       (0x0EUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< RGMII1 Pulse Per Second output pin. */
#define SYS_GPL_MFPH_PL13MFP_RMII1_PPS        (0x0FUL<<SYS_GPL_MFPH_PL13MFP_Pos) /*!< RMII1 Pulse Per Second output pin. */
#define SYS_GPL_MFPH_PL14MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL14MFP_EPWM0_CH2        (0x01UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< EPWM0 channel2 output/capture input. */
#define SYS_GPL_MFPH_PL14MFP_UART7_RXD        (0x02UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< Data receiver input pin for UART7. */
#define SYS_GPL_MFPH_PL14MFP_CAN1_RXD         (0x04UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< CAN1 bus receiver input. */
#define SYS_GPL_MFPH_PL14MFP_SPI0_MOSI        (0x05UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< 1st SPI0 MOSI (Master Out, Slave In) pin. */
#define SYS_GPL_MFPH_PL14MFP_I2S1_DI          (0x06UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< I2S1 data input. */
#define SYS_GPL_MFPH_PL14MFP_SC1_RST          (0x07UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< SmartCard1 reset pin. */
#define SYS_GPL_MFPH_PL14MFP_EBI_AD2          (0x08UL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< EBI address/data bus bit2. */
#define SYS_GPL_MFPH_PL14MFP_TM2              (0x0BUL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPL_MFPH_PL14MFP_INT0             (0x0CUL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< External interrupt0 input pin. */
#define SYS_GPL_MFPH_PL14MFP_EBI_AD13         (0x0DUL<<SYS_GPL_MFPH_PL14MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPL_MFPH_PL15MFP_GPIO             (0x00UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPL_MFPH_PL15MFP_EPWM0_CH1        (0x01UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< EPWM0 channel1 output/capture input. */
#define SYS_GPL_MFPH_PL15MFP_UART7_TXD        (0x02UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< Data transmitter output pin for UART7. */
#define SYS_GPL_MFPH_PL15MFP_TRACE_CLK        (0x03UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< ETM Rx clock input pin. */
#define SYS_GPL_MFPH_PL15MFP_CAN1_TXD         (0x04UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< CAN1 bus transmitter output. */
#define SYS_GPL_MFPH_PL15MFP_SPI0_MISO        (0x05UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< 1st SPI0 MISO (Master In, Slave Out) pin. */
#define SYS_GPL_MFPH_PL15MFP_I2S1_DO          (0x06UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< I2S1 data output. */
#define SYS_GPL_MFPH_PL15MFP_SC1_PWR          (0x07UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< SmartCard1 power pin. */
#define SYS_GPL_MFPH_PL15MFP_EBI_AD3          (0x08UL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< EBI address/data bus bit3. */
#define SYS_GPL_MFPH_PL15MFP_TM2_EXT          (0x0BUL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< Timer2 event counter input / toggle output */
#define SYS_GPL_MFPH_PL15MFP_INT2             (0x0CUL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< External interrupt2 input pin. */
#define SYS_GPL_MFPH_PL15MFP_EBI_AD14         (0x0DUL<<SYS_GPL_MFPH_PL15MFP_Pos) /*!< EBI address/data bus bit1. */
/********************* Bit definition of GPM_MFPL register **********************/
#define SYS_GPM_MFPL_PM0MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM0MFP_I2C4_SDA          (0x04UL<<SYS_GPM_MFPL_PM0MFP_Pos)  /*!< I2C4 data input/output pin. */
#define SYS_GPM_MFPL_PM0MFP_CCAP0_VSYNC       (0x06UL<<SYS_GPM_MFPL_PM0MFP_Pos)  /*!< Camera capture 0 interface vsync input pin. */
#define SYS_GPM_MFPL_PM0MFP_EBI_AD3           (0x08UL<<SYS_GPM_MFPL_PM0MFP_Pos)  /*!< EBI address/data bus bit3. */
#define SYS_GPM_MFPL_PM0MFP_EBI_ADR3          (0x0AUL<<SYS_GPM_MFPL_PM0MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM1MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM1MFP_I2C4_SCL          (0x04UL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< I2C4 clock pin. */
#define SYS_GPM_MFPL_PM1MFP_SPI3_I2SMCLK      (0x05UL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< SPI3 I2S master clock output pin. */
#define SYS_GPM_MFPL_PM1MFP_CCAP0_SFIELD      (0x06UL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< Camera capture 0 interface SFIELD input pin. */
#define SYS_GPM_MFPL_PM1MFP_EBI_AD4           (0x08UL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< EBI address/data bus bit4. */
#define SYS_GPM_MFPL_PM1MFP_EBI_ADR4          (0x0AUL<<SYS_GPM_MFPL_PM1MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM2MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM2MFP_CAN3_RXD          (0x03UL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< CAN3 bus receiver input. */
#define SYS_GPM_MFPL_PM2MFP_USBHL0_DM         (0x04UL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPM_MFPL_PM2MFP_CCAP0_DATA0       (0x06UL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< Camera capture 0 data input bus bit 0. */
#define SYS_GPM_MFPL_PM2MFP_EBI_AD5           (0x08UL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< EBI address/data bus bit5. */
#define SYS_GPM_MFPL_PM2MFP_EBI_ADR5          (0x0AUL<<SYS_GPM_MFPL_PM2MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM3MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM3MFP_CAN3_TXD          (0x03UL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< CAN3 bus transmitter output. */
#define SYS_GPM_MFPL_PM3MFP_USBHL0_DP         (0x04UL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPM_MFPL_PM3MFP_CCAP0_DATA1       (0x06UL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< Camera capture 0 data input bus bit 1. */
#define SYS_GPM_MFPL_PM3MFP_EBI_AD6           (0x08UL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< EBI address/data bus bit6. */
#define SYS_GPM_MFPL_PM3MFP_EBI_ADR6          (0x0AUL<<SYS_GPM_MFPL_PM3MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM4MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM4MFP_I2C5_SDA          (0x04UL<<SYS_GPM_MFPL_PM4MFP_Pos)  /*!< I2C5 data input/output pin. */
#define SYS_GPM_MFPL_PM4MFP_CCAP0_DATA2       (0x06UL<<SYS_GPM_MFPL_PM4MFP_Pos)  /*!< Camera capture 0 data input bus bit 2. */
#define SYS_GPM_MFPL_PM4MFP_EBI_AD7           (0x08UL<<SYS_GPM_MFPL_PM4MFP_Pos)  /*!< EBI address/data bus bit7. */
#define SYS_GPM_MFPL_PM4MFP_EBI_ADR7          (0x0AUL<<SYS_GPM_MFPL_PM4MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM5MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM5MFP_I2C5_SCL          (0x04UL<<SYS_GPM_MFPL_PM5MFP_Pos)  /*!< I2C5 clock pin. */
#define SYS_GPM_MFPL_PM5MFP_CCAP0_DATA3       (0x06UL<<SYS_GPM_MFPL_PM5MFP_Pos)  /*!< Camera capture 0 data input bus bit 3. */
#define SYS_GPM_MFPL_PM5MFP_EBI_AD8           (0x08UL<<SYS_GPM_MFPL_PM5MFP_Pos)  /*!< EBI address/data bus bit8. */
#define SYS_GPM_MFPL_PM5MFP_EBI_ADR8          (0x0AUL<<SYS_GPM_MFPL_PM5MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM6MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM6MFP_CAN0_RXD          (0x03UL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPM_MFPL_PM6MFP_USBHL1_DM         (0x04UL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< USB 1.1 host-lite 1 differential signal D-. */
#define SYS_GPM_MFPL_PM6MFP_CCAP0_DATA4       (0x06UL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< Camera capture 0 data input bus bit 4. */
#define SYS_GPM_MFPL_PM6MFP_EBI_AD9           (0x08UL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< EBI address/data bus bit9. */
#define SYS_GPM_MFPL_PM6MFP_EBI_ADR9          (0x0AUL<<SYS_GPM_MFPL_PM6MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPL_PM7MFP_GPIO              (0x00UL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPL_PM7MFP_CAN0_TXD          (0x03UL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPM_MFPL_PM7MFP_USBHL1_DP         (0x04UL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< USB 1.1 host-lite 1 differential signal D+. */
#define SYS_GPM_MFPL_PM7MFP_CCAP0_DATA5       (0x06UL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< Camera capture 0 data input bus bit 5. */
#define SYS_GPM_MFPL_PM7MFP_EBI_AD10          (0x08UL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPL_PM7MFP_EBI_ADR10         (0x0AUL<<SYS_GPM_MFPL_PM7MFP_Pos)  /*!< EBI address/data bus bit*. */
/********************* Bit definition of GPM_MFPH register **********************/
#define SYS_GPM_MFPH_PM8MFP_GPIO              (0x00UL<<SYS_GPM_MFPH_PM8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM8MFP_I2C0_SDA          (0x04UL<<SYS_GPM_MFPH_PM8MFP_Pos)  /*!< I2C0 data input/output pin. */
#define SYS_GPM_MFPH_PM8MFP_CCAP0_DATA6       (0x06UL<<SYS_GPM_MFPH_PM8MFP_Pos)  /*!< Camera capture 0 data input bus bit 6. */
#define SYS_GPM_MFPH_PM8MFP_EBI_AD11          (0x08UL<<SYS_GPM_MFPH_PM8MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM8MFP_EBI_ADR11         (0x0AUL<<SYS_GPM_MFPH_PM8MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPH_PM9MFP_GPIO              (0x00UL<<SYS_GPM_MFPH_PM9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM9MFP_I2C0_SCL          (0x04UL<<SYS_GPM_MFPH_PM9MFP_Pos)  /*!< I2C0 clock pin. */
#define SYS_GPM_MFPH_PM9MFP_CCAP0_DATA7       (0x06UL<<SYS_GPM_MFPH_PM9MFP_Pos)  /*!< Camera capture 0 data input bus bit 7. */
#define SYS_GPM_MFPH_PM9MFP_EBI_AD12          (0x08UL<<SYS_GPM_MFPH_PM9MFP_Pos)  /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM9MFP_EBI_ADR12         (0x0AUL<<SYS_GPM_MFPH_PM9MFP_Pos)  /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPH_PM10MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM10MFP_EPWM1_CH2        (0x01UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< EPWM1 channel2 output/capture input. */
#define SYS_GPM_MFPH_PM10MFP_CAN2_RXD         (0x03UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPM_MFPH_PM10MFP_USBHL4_DM        (0x04UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< USB 1.1 host-lite 4 differential signal D-. */
#define SYS_GPM_MFPH_PM10MFP_SPI3_SS0         (0x05UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< 1st SPI3 slave select pin. */
#define SYS_GPM_MFPH_PM10MFP_CCAP0_DATA8      (0x06UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< Camera capture 0 data input bus bit 8. */
#define SYS_GPM_MFPH_PM10MFP_SPI2_I2SMCLK     (0x07UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< SPI2 I2S master clock output pin. */
#define SYS_GPM_MFPH_PM10MFP_EBI_AD13         (0x08UL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM10MFP_EBI_ADR13        (0x0AUL<<SYS_GPM_MFPH_PM10MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPH_PM11MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM11MFP_EPWM1_CH3        (0x01UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< EPWM1 channel3 output/capture input. */
#define SYS_GPM_MFPH_PM11MFP_CAN2_TXD         (0x03UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< CAN2 bus transmitter output. */
#define SYS_GPM_MFPH_PM11MFP_USBHL4_DP        (0x04UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< USB 1.1 host-lite 4 differential signal D+. */
#define SYS_GPM_MFPH_PM11MFP_SPI3_SS1         (0x05UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< 1st SPI3 slave select pin. */
#define SYS_GPM_MFPH_PM11MFP_CCAP0_DATA9      (0x06UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< Camera capture 0 data input bus bit 9. */
#define SYS_GPM_MFPH_PM11MFP_SPI2_SS1         (0x07UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< 1st SPI2 slave select pin. */
#define SYS_GPM_MFPH_PM11MFP_EBI_AD14         (0x08UL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM11MFP_EBI_ADR14        (0x0AUL<<SYS_GPM_MFPH_PM11MFP_Pos) /*!< EBI address/data bus bit*. */
#define SYS_GPM_MFPH_PM12MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM12MFP_EPWM1_CH4        (0x01UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< EPWM1 channel4 output/capture input. */
#define SYS_GPM_MFPH_PM12MFP_UART10_nCTS      (0x02UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< Clear to Send input pin for UART10. */
#define SYS_GPM_MFPH_PM12MFP_TRACE_DATA0      (0x03UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< ETM Rx input bus bit0. */
#define SYS_GPM_MFPH_PM12MFP_UART11_RXD       (0x04UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< Data receiver input pin for UART11. */
#define SYS_GPM_MFPH_PM12MFP_I2C2_SDA         (0x05UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< I2C2 data input/output pin. */
#define SYS_GPM_MFPH_PM12MFP_SC1_nCD          (0x07UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< SmartCard1 card detect pin. */
#define SYS_GPM_MFPH_PM12MFP_EBI_AD8          (0x08UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< EBI address/data bus bit8. */
#define SYS_GPM_MFPH_PM12MFP_I2S1_MCLK        (0x09UL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< I2S1 master clock output pin. */
#define SYS_GPM_MFPH_PM12MFP_TM8              (0x0BUL<<SYS_GPM_MFPH_PM12MFP_Pos) /*!< Timer8 event counter input / toggle output */
#define SYS_GPM_MFPH_PM13MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM13MFP_EPWM1_CH5        (0x01UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< EPWM1 channel5 output/capture input. */
#define SYS_GPM_MFPH_PM13MFP_UART10_nRTS      (0x02UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< Request to Send output pin for UART10. */
#define SYS_GPM_MFPH_PM13MFP_TRACE_DATA1      (0x03UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< ETM Rx input bus bit1. */
#define SYS_GPM_MFPH_PM13MFP_UART11_TXD       (0x04UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< Data transmitter output pin for UART11. */
#define SYS_GPM_MFPH_PM13MFP_I2C2_SCL         (0x05UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< I2C2 clock pin. */
#define SYS_GPM_MFPH_PM13MFP_EBI_AD9          (0x08UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< EBI address/data bus bit9. */
#define SYS_GPM_MFPH_PM13MFP_ECAP1_IC0        (0x09UL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< Input 0 of enhanced capture unit 1. */
#define SYS_GPM_MFPH_PM13MFP_TM8_EXT          (0x0BUL<<SYS_GPM_MFPH_PM13MFP_Pos) /*!< Timer8 event counter input / toggle output */
#define SYS_GPM_MFPH_PM14MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM14MFP_EPWM1_BRAKE0     (0x01UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< Brake input pin 0 of EPWM1. */
#define SYS_GPM_MFPH_PM14MFP_UART10_RXD       (0x02UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< Data receiver input pin for UART10. */
#define SYS_GPM_MFPH_PM14MFP_TRACE_DATA2      (0x03UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< ETM Rx input bus bit2. */
#define SYS_GPM_MFPH_PM14MFP_CAN2_RXD         (0x04UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPM_MFPH_PM14MFP_USBHL3_DM        (0x05UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPM_MFPH_PM14MFP_I2C3_SDA         (0x06UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< I2C3 data input/output pin. */
#define SYS_GPM_MFPH_PM14MFP_EBI_AD10         (0x08UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM14MFP_ECAP1_IC1        (0x09UL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< Input 1 of enhanced capture unit 1. */
#define SYS_GPM_MFPH_PM14MFP_TM10             (0x0BUL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPM_MFPH_PM14MFP_INT1             (0x0DUL<<SYS_GPM_MFPH_PM14MFP_Pos) /*!< External interrupt1 input pin. */
#define SYS_GPM_MFPH_PM15MFP_GPIO             (0x00UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPM_MFPH_PM15MFP_EPWM1_BRAKE1     (0x01UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< Brake input pin 1 of EPWM1. */
#define SYS_GPM_MFPH_PM15MFP_UART10_TXD       (0x02UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< Data transmitter output pin for UART10. */
#define SYS_GPM_MFPH_PM15MFP_TRACE_DATA3      (0x03UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< ETM Rx input bus bit3. */
#define SYS_GPM_MFPH_PM15MFP_CAN2_TXD         (0x04UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< CAN2 bus transmitter output. */
#define SYS_GPM_MFPH_PM15MFP_USBHL3_DP        (0x05UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPM_MFPH_PM15MFP_I2C3_SCL         (0x06UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< I2C3 clock pin. */
#define SYS_GPM_MFPH_PM15MFP_EBI_AD11         (0x08UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< EBI address/data bus bit1. */
#define SYS_GPM_MFPH_PM15MFP_ECAP1_IC2        (0x09UL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< Input 1 of enhanced capture unit 2. */
#define SYS_GPM_MFPH_PM15MFP_TM10_EXT         (0x0BUL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< Timer1 event counter input / toggle output */
#define SYS_GPM_MFPH_PM15MFP_INT2             (0x0DUL<<SYS_GPM_MFPH_PM15MFP_Pos) /*!< External interrupt2 input pin. */
/********************* Bit definition of GPN_MFPL register **********************/
#define SYS_GPN_MFPL_PN0MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN0MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN0MFP_I2C2_SDA          (0x04UL<<SYS_GPN_MFPL_PN0MFP_Pos)  /*!< I2C2 data input/output pin. */
#define SYS_GPN_MFPL_PN0MFP_CCAP1_DATA0       (0x06UL<<SYS_GPN_MFPL_PN0MFP_Pos)  /*!< Camera capture 1 data input bus bit 0. */
#define SYS_GPN_MFPL_PN1MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN1MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN1MFP_I2C2_SCL          (0x04UL<<SYS_GPN_MFPL_PN1MFP_Pos)  /*!< I2C2 clock pin. */
#define SYS_GPN_MFPL_PN1MFP_CCAP1_DATA1       (0x06UL<<SYS_GPN_MFPL_PN1MFP_Pos)  /*!< Camera capture 1 data input bus bit 1. */
#define SYS_GPN_MFPL_PN2MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN2MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN2MFP_CAN0_RXD          (0x03UL<<SYS_GPN_MFPL_PN2MFP_Pos)  /*!< CAN0 bus receiver input. */
#define SYS_GPN_MFPL_PN2MFP_USBHL0_DM         (0x04UL<<SYS_GPN_MFPL_PN2MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D-. */
#define SYS_GPN_MFPL_PN2MFP_CCAP1_DATA2       (0x06UL<<SYS_GPN_MFPL_PN2MFP_Pos)  /*!< Camera capture 1 data input bus bit 2. */
#define SYS_GPN_MFPL_PN3MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN3MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN3MFP_CAN0_TXD          (0x03UL<<SYS_GPN_MFPL_PN3MFP_Pos)  /*!< CAN0 bus transmitter output. */
#define SYS_GPN_MFPL_PN3MFP_USBHL0_DP         (0x04UL<<SYS_GPN_MFPL_PN3MFP_Pos)  /*!< USB 1.1 host-lite 0 differential signal D+. */
#define SYS_GPN_MFPL_PN3MFP_CCAP1_DATA3       (0x06UL<<SYS_GPN_MFPL_PN3MFP_Pos)  /*!< Camera capture 1 data input bus bit 3. */
#define SYS_GPN_MFPL_PN4MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN4MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN4MFP_I2C1_SDA          (0x04UL<<SYS_GPN_MFPL_PN4MFP_Pos)  /*!< I2C1 data input/output pin. */
#define SYS_GPN_MFPL_PN4MFP_CCAP1_DATA4       (0x06UL<<SYS_GPN_MFPL_PN4MFP_Pos)  /*!< Camera capture 1 data input bus bit 4. */
#define SYS_GPN_MFPL_PN5MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN5MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN5MFP_I2C1_SCL          (0x04UL<<SYS_GPN_MFPL_PN5MFP_Pos)  /*!< I2C1 clock pin. */
#define SYS_GPN_MFPL_PN5MFP_CCAP1_DATA5       (0x06UL<<SYS_GPN_MFPL_PN5MFP_Pos)  /*!< Camera capture 1 data input bus bit 5. */
#define SYS_GPN_MFPL_PN6MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN6MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN6MFP_CAN1_RXD          (0x03UL<<SYS_GPN_MFPL_PN6MFP_Pos)  /*!< CAN1 bus receiver input. */
#define SYS_GPN_MFPL_PN6MFP_USBHL1_DM         (0x04UL<<SYS_GPN_MFPL_PN6MFP_Pos)  /*!< USB 1.1 host-lite 1 differential signal D-. */
#define SYS_GPN_MFPL_PN6MFP_CCAP1_DATA6       (0x06UL<<SYS_GPN_MFPL_PN6MFP_Pos)  /*!< Camera capture 1 data input bus bit 6. */
#define SYS_GPN_MFPL_PN7MFP_GPIO              (0x00UL<<SYS_GPN_MFPL_PN7MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPL_PN7MFP_CAN1_TXD          (0x03UL<<SYS_GPN_MFPL_PN7MFP_Pos)  /*!< CAN1 bus transmitter output. */
#define SYS_GPN_MFPL_PN7MFP_USBHL1_DP         (0x04UL<<SYS_GPN_MFPL_PN7MFP_Pos)  /*!< USB 1.1 host-lite 1 differential signal D+. */
#define SYS_GPN_MFPL_PN7MFP_CCAP1_DATA7       (0x06UL<<SYS_GPN_MFPL_PN7MFP_Pos)  /*!< Camera capture 1 data input bus bit 7. */
/********************* Bit definition of GPN_MFPH register **********************/
#define SYS_GPN_MFPH_PN8MFP_GPIO              (0x00UL<<SYS_GPN_MFPH_PN8MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN8MFP_EPWM2_CH4         (0x01UL<<SYS_GPN_MFPH_PN8MFP_Pos)  /*!< EPWM2 channel4 output/capture input. */
#define SYS_GPN_MFPH_PN8MFP_I2C0_SDA          (0x04UL<<SYS_GPN_MFPH_PN8MFP_Pos)  /*!< I2C0 data input/output pin. */
#define SYS_GPN_MFPH_PN8MFP_SPI2_I2SMCLK      (0x05UL<<SYS_GPN_MFPH_PN8MFP_Pos)  /*!< SPI2 I2S master clock output pin. */
#define SYS_GPN_MFPH_PN8MFP_CCAP1_DATA8       (0x06UL<<SYS_GPN_MFPH_PN8MFP_Pos)  /*!< Camera capture 1 data input bus bit 8. */
#define SYS_GPN_MFPH_PN9MFP_GPIO              (0x00UL<<SYS_GPN_MFPH_PN9MFP_Pos)  /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN9MFP_EPWM2_CH5         (0x01UL<<SYS_GPN_MFPH_PN9MFP_Pos)  /*!< EPWM2 channel5 output/capture input. */
#define SYS_GPN_MFPH_PN9MFP_I2C0_SCL          (0x04UL<<SYS_GPN_MFPH_PN9MFP_Pos)  /*!< I2C0 clock pin. */
#define SYS_GPN_MFPH_PN9MFP_SPI1_I2SMCLK      (0x05UL<<SYS_GPN_MFPH_PN9MFP_Pos)  /*!< SPI1 I2S master clock output pin. */
#define SYS_GPN_MFPH_PN9MFP_CCAP1_DATA9       (0x06UL<<SYS_GPN_MFPH_PN9MFP_Pos)  /*!< Camera capture 1 data input bus bit 9. */
#define SYS_GPN_MFPH_PN10MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN10MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN10MFP_CAN2_RXD         (0x03UL<<SYS_GPN_MFPH_PN10MFP_Pos) /*!< CAN2 bus receiver input. */
#define SYS_GPN_MFPH_PN10MFP_USBHL2_DM        (0x04UL<<SYS_GPN_MFPH_PN10MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D-. */
#define SYS_GPN_MFPH_PN10MFP_CCAP1_SCLK       (0x06UL<<SYS_GPN_MFPH_PN10MFP_Pos) /*!< Camera capture 1 interface sensor clock output pin. */
#define SYS_GPN_MFPH_PN11MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN11MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN11MFP_CAN2_TXD         (0x03UL<<SYS_GPN_MFPH_PN11MFP_Pos) /*!< CAN2 bus transmitter output. */
#define SYS_GPN_MFPH_PN11MFP_USBHL2_DP        (0x04UL<<SYS_GPN_MFPH_PN11MFP_Pos) /*!< USB 1.1 host-lite 2 differential signal D+. */
#define SYS_GPN_MFPH_PN11MFP_CCAP1_PIXCLK     (0x06UL<<SYS_GPN_MFPH_PN11MFP_Pos) /*!< Camera capture 1 interface pixel clock input pin. */
#define SYS_GPN_MFPH_PN12MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN12MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN12MFP_UART6_nCTS       (0x02UL<<SYS_GPN_MFPH_PN12MFP_Pos) /*!< Clear to Send input pin for UART6. */
#define SYS_GPN_MFPH_PN12MFP_UART12_RXD       (0x03UL<<SYS_GPN_MFPH_PN12MFP_Pos) /*!< Data receiver input pin for UART12. */
#define SYS_GPN_MFPH_PN12MFP_I2C5_SDA         (0x04UL<<SYS_GPN_MFPH_PN12MFP_Pos) /*!< I2C5 data input/output pin. */
#define SYS_GPN_MFPH_PN12MFP_CCAP1_HSYNC      (0x06UL<<SYS_GPN_MFPH_PN12MFP_Pos) /*!< Camera capture 1 interface hsync input pin. */
#define SYS_GPN_MFPH_PN13MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN13MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN13MFP_UART6_nRTS       (0x02UL<<SYS_GPN_MFPH_PN13MFP_Pos) /*!< Request to Send output pin for UART6. */
#define SYS_GPN_MFPH_PN13MFP_UART12_TXD       (0x03UL<<SYS_GPN_MFPH_PN13MFP_Pos) /*!< Data transmitter output pin for UART12. */
#define SYS_GPN_MFPH_PN13MFP_I2C5_SCL         (0x04UL<<SYS_GPN_MFPH_PN13MFP_Pos) /*!< I2C5 clock pin. */
#define SYS_GPN_MFPH_PN13MFP_CCAP1_VSYNC      (0x06UL<<SYS_GPN_MFPH_PN13MFP_Pos) /*!< Camera capture 1 interface vsync input pin. */
#define SYS_GPN_MFPH_PN14MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN14MFP_UART6_RXD        (0x02UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< Data receiver input pin for UART6. */
#define SYS_GPN_MFPH_PN14MFP_CAN3_RXD         (0x03UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< CAN3 bus receiver input. */
#define SYS_GPN_MFPH_PN14MFP_USBHL3_DM        (0x04UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D-. */
#define SYS_GPN_MFPH_PN14MFP_SPI1_SS1         (0x05UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPN_MFPH_PN14MFP_CCAP1_SFIELD     (0x06UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< Camera capture 1 interface SFIELD input pin. */
#define SYS_GPN_MFPH_PN14MFP_SPI1_I2SMCLK     (0x07UL<<SYS_GPN_MFPH_PN14MFP_Pos) /*!< SPI1 I2S master clock output pin. */
#define SYS_GPN_MFPH_PN15MFP_GPIO             (0x00UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< General purpose digital I/O pin. */
#define SYS_GPN_MFPH_PN15MFP_EPWM2_CH4        (0x01UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< EPWM2 channel4 output/capture input. */
#define SYS_GPN_MFPH_PN15MFP_UART6_TXD        (0x02UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< Data transmitter output pin for UART6. */
#define SYS_GPN_MFPH_PN15MFP_CAN3_TXD         (0x03UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< CAN3 bus transmitter output. */
#define SYS_GPN_MFPH_PN15MFP_USBHL3_DP        (0x04UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< USB 1.1 host-lite 3 differential signal D+. */
#define SYS_GPN_MFPH_PN15MFP_I2S0_MCLK        (0x05UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< I2S0 master clock output pin. */
#define SYS_GPN_MFPH_PN15MFP_SPI1_SS1         (0x06UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< 1st SPI1 slave select pin. */
#define SYS_GPN_MFPH_PN15MFP_SPI1_I2SMCLK     (0x07UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< SPI1 I2S master clock output pin. */
#define SYS_GPN_MFPH_PN15MFP_SC0_nCD          (0x08UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< SmartCard0 card detect pin. */
#define SYS_GPN_MFPH_PN15MFP_EADC0_ST         (0x09UL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< EADC external trigger input. */
#define SYS_GPN_MFPH_PN15MFP_CLKO             (0x0AUL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< Clock Output pin. */
#define SYS_GPN_MFPH_PN15MFP_TM6              (0x0BUL<<SYS_GPN_MFPH_PN15MFP_Pos) /*!< Timer6 event counter input / toggle output */

/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */


/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

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
#if defined(USE_MA35D1_SUBM)
    do
    {
        SYS->RLKSUBM = 0x59UL;
        SYS->RLKSUBM = 0x16UL;
        SYS->RLKSUBM = 0x88UL;
    }
    while (SYS->RLKSUBM == 0UL);
#else
    do
    {
        SYS->RLKTZS = 0x59UL;
        SYS->RLKTZS = 0x16UL;
        SYS->RLKTZS = 0x88UL;
    }
    while (SYS->RLKTZS == 0UL);
#endif
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
#if defined(USE_MA35D1_SUBM)
    SYS->RLKSUBM = 0UL;
#else
    SYS->RLKTZS = 0UL;
#endif
}

/**
  * @brief      Query write-protection is locked or not
  * @param      None
  * @return     true or false
  * @details
  */
__STATIC_INLINE uint32_t SYS_IsRegLocked(void)
{
#if defined(USE_MA35D1_SUBM)
    return (SYS->RLKSUBM == 0) ? 1 : 0;
#else
    return (SYS->RLKTZS == 0) ? 1 : 0;
#endif
}

void SYS_ResetModule(uint32_t u32ModuleIndex);

/*@}*/ /* end of group SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SYS_Driver */

/*@}*/ /* end of group Standard_Driver */


#ifdef __cplusplus
}
#endif

#endif  /* __NU_SYS_H__ */

