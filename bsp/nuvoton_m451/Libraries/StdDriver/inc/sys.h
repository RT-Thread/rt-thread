/**************************************************************************//**
 * @file     SYS.h
 * @version  V3.0
 * $Revision  1 $
 * $Date: 15/08/11 10:26a $
 * @brief    M451 Series SYS Header File
 *
 * @note
 * Copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#ifndef __SYS_H__
#define __SYS_H__

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
#define PDMA_RST    ((0x0<<24) | SYS_IPRST0_PDMARST_Pos )   /*!< Reset PDMA */
#define EBI_RST     ((0x0<<24) | SYS_IPRST0_EBIRST_Pos )    /*!< Reset EBI */
#define USBH_RST    ((0x0<<24) | SYS_IPRST0_USBHRST_Pos )   /*!< Reset USBH */
#define CRC_RST     ((0x0<<24) | SYS_IPRST0_CRCRST_Pos )    /*!< Reset CRC */

#define GPIO_RST    ((0x4<<24) | SYS_IPRST1_GPIORST_Pos )   /*!< Reset GPIO */
#define TMR0_RST    ((0x4<<24) | SYS_IPRST1_TMR0RST_Pos )   /*!< Reset TMR0 */
#define TMR1_RST    ((0x4<<24) | SYS_IPRST1_TMR1RST_Pos )   /*!< Reset TMR1 */
#define TMR2_RST    ((0x4<<24) | SYS_IPRST1_TMR2RST_Pos )   /*!< Reset TMR2 */
#define TMR3_RST    ((0x4<<24) | SYS_IPRST1_TMR3RST_Pos )   /*!< Reset TMR3 */
#define ACMP01_RST  ((0x4<<24) | SYS_IPRST1_ACMP01RST_Pos ) /*!< Reset ACMP01 */
#define I2C0_RST    ((0x4<<24) | SYS_IPRST1_I2C0RST_Pos )   /*!< Reset I2C0 */
#define I2C1_RST    ((0x4<<24) | SYS_IPRST1_I2C1RST_Pos )   /*!< Reset I2C1 */
#define SPI0_RST    ((0x4<<24) | SYS_IPRST1_SPI0RST_Pos )   /*!< Reset SPI0 */
#define SPI1_RST    ((0x4<<24) | SYS_IPRST1_SPI1RST_Pos )   /*!< Reset SPI1 */
#define SPI2_RST    ((0x4<<24) | SYS_IPRST1_SPI2RST_Pos )   /*!< Reset SPI2 */
#define UART0_RST   ((0x4<<24) | SYS_IPRST1_UART0RST_Pos )  /*!< Reset UART0 */
#define UART1_RST   ((0x4<<24) | SYS_IPRST1_UART1RST_Pos )  /*!< Reset UART1 */
#define UART2_RST   ((0x4<<24) | SYS_IPRST1_UART2RST_Pos )  /*!< Reset UART2 */
#define UART3_RST   ((0x4<<24) | SYS_IPRST1_UART3RST_Pos )  /*!< Reset UART3 */
#define CAN0_RST    ((0x4<<24) | SYS_IPRST1_CAN0RST_Pos )   /*!< Reset CAN0 */
#define OTG_RST     ((0x4<<24) | SYS_IPRST1_OTGRST_Pos )    /*!< Reset OTG */
#define USBD_RST    ((0x4<<24) | SYS_IPRST1_USBDRST_Pos )   /*!< Reset USBD */
#define EADC_RST    ((0x4<<24) | SYS_IPRST1_EADCRST_Pos )   /*!< Reset EADC */

#define SC0_RST     ((0x8<<24) | SYS_IPRST2_SC0RST_Pos )    /*!< Reset SC0 */
#define DAC_RST     ((0x8<<24) | SYS_IPRST2_DACRST_Pos )    /*!< Reset DAC */
#define PWM0_RST    ((0x8<<24) | SYS_IPRST2_PWM0RST_Pos )   /*!< Reset PWM0 */
#define PWM1_RST    ((0x8<<24) | SYS_IPRST2_PWM1RST_Pos )   /*!< Reset PWM1 */
#define TK_RST      ((0x8<<24) | SYS_IPRST2_TKRST_Pos )     /*!< Reset TK */


/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCTL_BOD_RST_EN           (1UL<<SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Reset Enable */
#define SYS_BODCTL_BOD_INTERRUPT_EN     (0UL<<SYS_BODCTL_BODRSTEN_Pos)    /*!< Brown-out Interrupt Enable */
#define SYS_BODCTL_BODVL_4_5V           (3UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 4.5V */
#define SYS_BODCTL_BODVL_3_7V           (2UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 3.7V */
#define SYS_BODCTL_BODVL_2_7V           (1UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.7V */
#define SYS_BODCTL_BODVL_2_2V           (0UL<<SYS_BODCTL_BODVL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.2V */


/*---------------------------------------------------------------------------------------------------------*/
/*  VREFCTL constant definitions. (Write-Protection Register)                                              */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_VREFCTL_VREF_2_56V      (0x3UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT = 2.56V */
#define SYS_VREFCTL_VREF_2_048V     (0x7UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT = 2.048V */
#define SYS_VREFCTL_VREF_3_072V     (0xBUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT = 3.072V */
#define SYS_VREFCTL_VREF_4_096V     (0xFUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT = 4.096V */


/*---------------------------------------------------------------------------------------------------------*/
/*  USBPHY constant definitions. (Write-Protection Register)                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_USBPHY_USBROLE_OTG_V33_EN (0x1UL<<SYS_USBPHY_LDO33EN_Pos)   /*!<  USB LDO33 Enabled  */
#define SYS_USBPHY_USBROLE_STD_USBD   (0x0UL<<SYS_USBPHY_USBROLE_Pos)   /*!<  Standard USB device */
#define SYS_USBPHY_USBROLE_STD_USBH   (0x1UL<<SYS_USBPHY_USBROLE_Pos)   /*!<  Standard USB host */
#define SYS_USBPHY_USBROLE_ID_DEPH    (0x2UL<<SYS_USBPHY_USBROLE_Pos)   /*!<  ID dependent device */
#define SYS_USBPHY_USBROLE_ON_THE_GO  (0x3UL<<SYS_USBPHY_USBROLE_Pos)   /*!<  On-The-Go device */


/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to set PA.0 as SC0_CLK in initial function,
           user can issue following command to achieve it.

           SYS->GPA_MFPL  = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA0MFP_Msk) ) | SYS_GPA_MFPL_PA0_MFP_SC0_CLK  ;

*/
//PA0 MFP
#define SYS_GPA_MFPL_PA0MFP_GPIO               (0ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for GPIO*/
#define SYS_GPA_MFPL_PA0MFP_UART1_nCTS         (1ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for UART1_nCTS*/
#define SYS_GPA_MFPL_PA0MFP_UART1_TXD          (3ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for UART1_TXD*/
#define SYS_GPA_MFPL_PA0MFP_CAN0_RXD           (4ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for CAN0_RXD*/
#define SYS_GPA_MFPL_PA0MFP_SC0_CLK            (5ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for SC0_CLK*/
#define SYS_GPA_MFPL_PA0MFP_PWM1_CH5           (6ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for PWM1_CH5*/
#define SYS_GPA_MFPL_PA0MFP_EBI_AD0            (7ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for EBI_AD0*/
#define SYS_GPA_MFPL_PA0MFP_INT0               (8ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for INT0*/
#define SYS_GPA_MFPL_PA0MFP_SPI1_I2SMCLK       (9ul << SYS_GPA_MFPL_PA0MFP_Pos)        /*!< GPA_MFPL PA0 setting for SPI1_I2SMCLK*/

//PA1 MFP
#define SYS_GPA_MFPL_PA1MFP_GPIO               (0ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for GPIO*/
#define SYS_GPA_MFPL_PA1MFP_UART1_nRTS         (1ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for UART1_nRTS*/
#define SYS_GPA_MFPL_PA1MFP_UART1_RXD          (3ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for UART1_RXD*/
#define SYS_GPA_MFPL_PA1MFP_CAN0_TXD           (4ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for CAN0_TXD*/
#define SYS_GPA_MFPL_PA1MFP_SC0_DAT            (5ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for SC0_DAT*/
#define SYS_GPA_MFPL_PA1MFP_PWM1_CH4           (6ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for PWM1_CH4*/
#define SYS_GPA_MFPL_PA1MFP_EBI_AD1            (7ul << SYS_GPA_MFPL_PA1MFP_Pos)        /*!< GPA_MFPL PA1 setting for EBI_AD1*/
#define SYS_GPA_MFPL_PA1MFP_STADC              (10ul << SYS_GPA_MFPL_PA1MFP_Pos)       /*!< GPA_MFPL PA1 setting for STADC*/

//PA2 MFP
#define SYS_GPA_MFPL_PA2MFP_GPIO               (0ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for GPIO*/
#define SYS_GPA_MFPL_PA2MFP_USB_VBUS_EN        (1ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for USB_VBUS_EN*/
#define SYS_GPA_MFPL_PA2MFP_UART0_TXD          (2ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for UART0_TXD*/
#define SYS_GPA_MFPL_PA2MFP_UART0_nCTS         (3ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for UART0_nCTS*/
#define SYS_GPA_MFPL_PA2MFP_I2C0_SDA           (4ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for I2C0_SDA*/
#define SYS_GPA_MFPL_PA2MFP_SC0_RST            (5ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for SC0_RST*/
#define SYS_GPA_MFPL_PA2MFP_PWM1_CH3           (6ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for PWM1_CH3*/
#define SYS_GPA_MFPL_PA2MFP_EBI_AD2            (7ul << SYS_GPA_MFPL_PA2MFP_Pos)        /*!< GPA_MFPL PA2 setting for EBI_AD2*/

//PA3 MFP
#define SYS_GPA_MFPL_PA3MFP_GPIO               (0ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for GPIO*/
#define SYS_GPA_MFPL_PA3MFP_USB_VBUS_ST       (1ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for USB_VBUS_ST*/
#define SYS_GPA_MFPL_PA3MFP_UART0_RXD          (2ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for UART0_RXD*/
#define SYS_GPA_MFPL_PA3MFP_UART0_nRTS         (3ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for UART0_nRTS*/
#define SYS_GPA_MFPL_PA3MFP_I2C0_SCL           (4ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for I2C0_SCL*/
#define SYS_GPA_MFPL_PA3MFP_SC0_PWR            (5ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for SC0_PWR*/
#define SYS_GPA_MFPL_PA3MFP_PWM1_CH2           (6ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for PWM1_CH2*/
#define SYS_GPA_MFPL_PA3MFP_EBI_AD3            (7ul << SYS_GPA_MFPL_PA3MFP_Pos)        /*!< GPA_MFPL PA3 setting for EBI_AD3*/

//PA4 MFP
#define SYS_GPA_MFPL_PA4MFP_GPIO               (0ul << SYS_GPA_MFPL_PA4MFP_Pos)        /*!< GPA_MFPL PA4 setting for GPIO*/
#define SYS_GPA_MFPL_PA4MFP_SPI1_SS            (2ul << SYS_GPA_MFPL_PA4MFP_Pos)        /*!< GPA_MFPL PA4 setting for SPI1_SS*/
#define SYS_GPA_MFPL_PA4MFP_EBI_AD4            (7ul << SYS_GPA_MFPL_PA4MFP_Pos)        /*!< GPA_MFPL PA4 setting for EBI_AD4*/

//PA5 MFP
#define SYS_GPA_MFPL_PA5MFP_GPIO               (0ul << SYS_GPA_MFPL_PA5MFP_Pos)        /*!< GPA_MFPL PA5 setting for GPIO*/
#define SYS_GPA_MFPL_PA5MFP_SPI1_MOSI          (2ul << SYS_GPA_MFPL_PA5MFP_Pos)        /*!< GPA_MFPL PA5 setting for SPI1_MOSI*/
#define SYS_GPA_MFPL_PA5MFP_T2_EXT             (3ul << SYS_GPA_MFPL_PA5MFP_Pos)        /*!< GPA_MFPL PA5 setting for T2_EXT*/
#define SYS_GPA_MFPL_PA5MFP_EBI_AD5            (7ul << SYS_GPA_MFPL_PA5MFP_Pos)        /*!< GPA_MFPL PA5 setting for EBI_AD5*/

//PA6 MFP
#define SYS_GPA_MFPL_PA6MFP_GPIO               (0ul << SYS_GPA_MFPL_PA6MFP_Pos)        /*!< GPA_MFPL PA6 setting for GPIO*/
#define SYS_GPA_MFPL_PA6MFP_SPI1_MISO          (2ul << SYS_GPA_MFPL_PA6MFP_Pos)        /*!< GPA_MFPL PA6 setting for SPI1_MISO*/
#define SYS_GPA_MFPL_PA6MFP_T1_EXT             (3ul << SYS_GPA_MFPL_PA6MFP_Pos)        /*!< GPA_MFPL PA6 setting for T1_EXT*/
#define SYS_GPA_MFPL_PA6MFP_EBI_AD6            (7ul << SYS_GPA_MFPL_PA6MFP_Pos)        /*!< GPA_MFPL PA6 setting for EBI_AD6*/

//PA7 MFP
#define SYS_GPA_MFPL_PA7MFP_GPIO               (0ul << SYS_GPA_MFPL_PA7MFP_Pos)        /*!< GPA_MFPL PA7 setting for GPIO*/
#define SYS_GPA_MFPL_PA7MFP_SPI1_CLK           (2ul << SYS_GPA_MFPL_PA7MFP_Pos)        /*!< GPA_MFPL PA7 setting for SPI1_CLK*/
#define SYS_GPA_MFPL_PA7MFP_T0_EXT             (3ul << SYS_GPA_MFPL_PA7MFP_Pos)        /*!< GPA_MFPL PA7 setting for T0_EXT*/
#define SYS_GPA_MFPL_PA7MFP_EBI_AD7            (7ul << SYS_GPA_MFPL_PA7MFP_Pos)        /*!< GPA_MFPL PA7 setting for EBI_AD7*/

//PA8 MFP
#define SYS_GPA_MFPH_PA8MFP_GPIO               (0ul << SYS_GPA_MFPH_PA8MFP_Pos)        /*!< GPA_MFPH PA8 setting for GPIO*/
#define SYS_GPA_MFPH_PA8MFP_UART3_TXD          (3ul << SYS_GPA_MFPH_PA8MFP_Pos)        /*!< GPA_MFPH PA8 setting for UART3_TXD*/

//PA9 MFP
#define SYS_GPA_MFPH_PA9MFP_GPIO               (0ul << SYS_GPA_MFPH_PA9MFP_Pos)        /*!< GPA_MFPH PA9 setting for GPIO*/
#define SYS_GPA_MFPH_PA9MFP_UART3_RXD          (3ul << SYS_GPA_MFPH_PA9MFP_Pos)        /*!< GPA_MFPH PA9 setting for UART3_RXD*/

//PA10 MFP
#define SYS_GPA_MFPH_PA10MFP_GPIO              (0ul << SYS_GPA_MFPH_PA10MFP_Pos)        /*!< GPA_MFPH PA10 setting for GPIO*/
#define SYS_GPA_MFPH_PA10MFP_UART3_nCTS        (3ul << SYS_GPA_MFPH_PA10MFP_Pos)        /*!< GPA_MFPH PA10 setting for UART3_nCTS*/

//PA11 MFP
#define SYS_GPA_MFPH_PA11MFP_GPIO              (0ul << SYS_GPA_MFPH_PA11MFP_Pos)        /*!< GPA_MFPH PA11 setting for GPIO*/
#define SYS_GPA_MFPH_PA11MFP_UART3_nRTS        (3ul << SYS_GPA_MFPH_PA11MFP_Pos)        /*!< GPA_MFPH PA11 setting for UART3_nRTS*/

//PA12 MFP
#define SYS_GPA_MFPH_PA12MFP_GPIO              (0ul << SYS_GPA_MFPH_PA12MFP_Pos)        /*!< GPA_MFPH PA12 setting for GPIO*/
#define SYS_GPA_MFPH_PA12MFP_SPI1_I2SMCLK      (2ul << SYS_GPA_MFPH_PA12MFP_Pos)        /*!< GPA_MFPH PA12 setting for SPI1_I2SMCLK*/
#define SYS_GPA_MFPH_PA12MFP_CAN0_TXD          (4ul << SYS_GPA_MFPH_PA12MFP_Pos)        /*!< GPA_MFPH PA12 setting for CAN0_TXD*/

//PA13 MFP
#define SYS_GPA_MFPH_PA13MFP_GPIO              (0ul << SYS_GPA_MFPH_PA13MFP_Pos)        /*!< GPA_MFPH PA13 setting for GPIO*/
#define SYS_GPA_MFPH_PA13MFP_CAN0_RXD          (4ul << SYS_GPA_MFPH_PA13MFP_Pos)        /*!< GPA_MFPH PA13 setting for CAN0_RXD*/

//PA14 MFP
#define SYS_GPA_MFPH_PA14MFP_GPIO              (0ul << SYS_GPA_MFPH_PA14MFP_Pos)        /*!< GPA_MFPH PA14 setting for GPIO*/
#define SYS_GPA_MFPH_PA14MFP_UART2_nCTS        (3ul << SYS_GPA_MFPH_PA14MFP_Pos)        /*!< GPA_MFPH PA14 setting for UART2_nCTS*/
#define SYS_GPA_MFPH_PA14MFP_I2C0_SMBAL        (4ul << SYS_GPA_MFPH_PA14MFP_Pos)        /*!< GPA_MFPH PA14 setting for I2C0_SMBAL*/

//PA15 MFP
#define SYS_GPA_MFPH_PA15MFP_GPIO              (0ul << SYS_GPA_MFPH_PA15MFP_Pos)        /*!< GPA_MFPH PA15 setting for GPIO*/
#define SYS_GPA_MFPH_PA15MFP_UART2_nRTS        (3ul << SYS_GPA_MFPH_PA15MFP_Pos)        /*!< GPA_MFPH PA15 setting for UART2_nRTS*/
#define SYS_GPA_MFPH_PA15MFP_I2C0_SMBSUS       (4ul << SYS_GPA_MFPH_PA15MFP_Pos)        /*!< GPA_MFPH PA15 setting for I2C0_SMBSUS*/

//PB0 MFP
#define SYS_GPB_MFPL_PB0MFP_GPIO               (0ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for GPIO*/
#define SYS_GPB_MFPL_PB0MFP_EADC_CH0           (1ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for EADC_CH0*/
#define SYS_GPB_MFPL_PB0MFP_SPI0_MOSI1         (2ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for SPI0_MOSI1*/
#define SYS_GPB_MFPL_PB0MFP_UART2_RXD          (3ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for UART2_RXD*/
#define SYS_GPB_MFPL_PB0MFP_T2                 (4ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for T2*/
#define SYS_GPB_MFPL_PB0MFP_DAC                (5ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for DAC*/
#define SYS_GPB_MFPL_PB0MFP_EBI_nWRL           (7ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for EBI_nWRL*/
#define SYS_GPB_MFPL_PB0MFP_INT1               (8ul << SYS_GPB_MFPL_PB0MFP_Pos)        /*!< GPB_MFPL PB0 setting for INT1*/

//PB1 MFP
#define SYS_GPB_MFPL_PB1MFP_GPIO               (0ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for GPIO*/
#define SYS_GPB_MFPL_PB1MFP_EADC_CH1           (1ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for EADC_CH1*/
#define SYS_GPB_MFPL_PB1MFP_SPI0_MISO1         (2ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for SPI0_MISO1*/
#define SYS_GPB_MFPL_PB1MFP_UART2_TXD          (3ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for UART2_TXD*/
#define SYS_GPB_MFPL_PB1MFP_T3                 (4ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for T3*/
#define SYS_GPB_MFPL_PB1MFP_SC0_RST            (5ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for SC0_RST*/
#define SYS_GPB_MFPL_PB1MFP_PWM0_SYNC_OUT      (6ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for PWM0_SYNC_OUT*/
#define SYS_GPB_MFPL_PB1MFP_EBI_nWRH           (7ul << SYS_GPB_MFPL_PB1MFP_Pos)        /*!< GPB_MFPL PB1 setting for EBI_nWRH*/

//PB2 MFP
#define SYS_GPB_MFPL_PB2MFP_GPIO               (0ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for GPIO*/
#define SYS_GPB_MFPL_PB2MFP_EADC_CH2           (1ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for EADC_CH2*/
#define SYS_GPB_MFPL_PB2MFP_SPI0_CLK           (2ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for SPI0_CLK*/
#define SYS_GPB_MFPL_PB2MFP_SPI1_CLK           (3ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for SPI1_CLK*/
#define SYS_GPB_MFPL_PB2MFP_UART1_RXD          (4ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for UART1_RXD*/
#define SYS_GPB_MFPL_PB2MFP_SC0_CD             (5ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for SC0_CD*/
#define SYS_GPB_MFPL_PB2MFP_UART3_RXD          (9ul << SYS_GPB_MFPL_PB2MFP_Pos)        /*!< GPB_MFPL PB2 setting for UART3_RXD*/
#define SYS_GPB_MFPL_PB2MFP_T2_EXT             (11ul << SYS_GPB_MFPL_PB2MFP_Pos)       /*!< GPB_MFPL PB2 setting for T2_EXT*/

//PB3
#define SYS_GPB_MFPL_PB3MFP_GPIO               (0ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for GPIO*/
#define SYS_GPB_MFPL_PB3MFP_EADC_CH3           (1ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for EADC_CH3*/
#define SYS_GPB_MFPL_PB3MFP_SPI0_MISO0         (2ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for SPI0_MISO0*/
#define SYS_GPB_MFPL_PB3MFP_SPI1_MISO          (3ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for SPI1_MISO*/
#define SYS_GPB_MFPL_PB3MFP_UART1_TXD          (4ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for UART1_TXD*/
#define SYS_GPB_MFPL_PB3MFP_UART3_TXD          (9ul << SYS_GPB_MFPL_PB3MFP_Pos)        /*!< GPB_MFPL PB3 setting for UART3_TXD*/
#define SYS_GPB_MFPL_PB3MFP_T0_EXT             (11ul << SYS_GPB_MFPL_PB3MFP_Pos)       /*!< GPB_MFPL PB3 setting for T0_EXT*/

//PB4
#define SYS_GPB_MFPL_PB4MFP_GPIO               (0ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for GPIO*/
#define SYS_GPB_MFPL_PB4MFP_EADC_CH4           (1ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for EADC_CH4*/
#define SYS_GPB_MFPL_PB4MFP_SPI0_SS            (2ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for SPI0_SS*/
#define SYS_GPB_MFPL_PB4MFP_SPI1_SS            (3ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for SPI1_SS*/
#define SYS_GPB_MFPL_PB4MFP_UART1_nCTS         (4ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for UART1_nCTS*/
#define SYS_GPB_MFPL_PB4MFP_ACMP0_N            (5ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for ACMP0_N*/
#define SYS_GPB_MFPL_PB4MFP_EBI_AD7            (7ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for EBI_AD7*/
#define SYS_GPB_MFPL_PB4MFP_UART2_TXD          (9ul << SYS_GPB_MFPL_PB4MFP_Pos)        /*!< GPB_MFPL PB4 setting for UART2_TXD*/
#define SYS_GPB_MFPL_PB4MFP_T1_EXT             (11ul << SYS_GPB_MFPL_PB4MFP_Pos)       /*!< GPB_MFPL PB4 setting for T1_EXT*/

//PB5
#define SYS_GPB_MFPL_PB5MFP_GPIO               (0ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for GPIO*/
#define SYS_GPB_MFPL_PB5MFP_EADC_CH13          (1ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for EADC_CH13*/
#define SYS_GPB_MFPL_PB5MFP_SPI0_MOSI0         (2ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for SPI0_MOSI0*/
#define SYS_GPB_MFPL_PB5MFP_SPI1_MOSI          (3ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for SPI1_MOSI*/
#define SYS_GPB_MFPL_PB5MFP_TK3                (4ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for TK3*/
#define SYS_GPB_MFPL_PB5MFP_ACMP0_P2           (5ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for ACMP0_P2*/
#define SYS_GPB_MFPL_PB5MFP_EBI_AD6            (7ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for EBI_AD6*/
#define SYS_GPB_MFPL_PB5MFP_UART2_RXD          (9ul << SYS_GPB_MFPL_PB5MFP_Pos)        /*!< GPB_MFPL PB5 setting for UART2_RXD*/

//PB6
#define SYS_GPB_MFPL_PB6MFP_GPIO               (0ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for GPIO*/
#define SYS_GPB_MFPL_PB6MFP_EADC_CH14          (1ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for EADC_CH14*/
#define SYS_GPB_MFPL_PB6MFP_SPI0_MISO0         (2ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for SPI0_MISO0*/
#define SYS_GPB_MFPL_PB6MFP_SPI1_MISO          (3ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for SPI1_MISO*/
#define SYS_GPB_MFPL_PB6MFP_TK4                (4ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for TK4*/
#define SYS_GPB_MFPL_PB6MFP_ACMP0_P1           (5ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for ACMP0_P1*/
#define SYS_GPB_MFPL_PB6MFP_EBI_AD5            (7ul << SYS_GPB_MFPL_PB6MFP_Pos)        /*!< GPB_MFPL PB6 setting for EBI_AD5*/

//PB7
#define SYS_GPB_MFPL_PB7MFP_GPIO               (0ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for GPIO*/
#define SYS_GPB_MFPL_PB7MFP_EADC_CH15          (1ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for EADC_CH15*/
#define SYS_GPB_MFPL_PB7MFP_SPI0_CLK           (2ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for SPI0_CLK*/
#define SYS_GPB_MFPL_PB7MFP_SPI1_CLK           (3ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for SPI1_CLK*/
#define SYS_GPB_MFPL_PB7MFP_TK5                (4ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for TK5*/
#define SYS_GPB_MFPL_PB7MFP_ACMP0_P0           (5ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for ACMP0_P0*/
#define SYS_GPB_MFPL_PB7MFP_EBI_AD4            (7ul << SYS_GPB_MFPL_PB7MFP_Pos)        /*!< GPB_MFPL PB7 setting for EBI_AD4*/
#define SYS_GPB_MFPL_PB7MFP_STADC              (10ul << SYS_GPB_MFPL_PB7MFP_Pos)       /*!< GPB_MFPL PB7 setting for STADC*/

//PB8
#define SYS_GPB_MFPH_PB8MFP_GPIO               (0ul << SYS_GPB_MFPH_PB8MFP_Pos)        /*!< GPB_MFPH PB8 setting for GPIO*/
#define SYS_GPB_MFPH_PB8MFP_EADC_CH5           (1ul << SYS_GPB_MFPH_PB8MFP_Pos)        /*!< GPB_MFPH PB8 setting for EADC_CH5*/
#define SYS_GPB_MFPH_PB8MFP_UART1_nRTS         (4ul << SYS_GPB_MFPH_PB8MFP_Pos)        /*!< GPB_MFPH PB8 setting for UART1_nRTS*/
#define SYS_GPB_MFPH_PB8MFP_PWM0_CH2           (6ul << SYS_GPB_MFPH_PB8MFP_Pos)        /*!< GPB_MFPH PB8 setting for PWM0_CH2*/

//PB9
#define SYS_GPB_MFPH_PB9MFP_GPIO               (0ul << SYS_GPB_MFPH_PB9MFP_Pos)        /*!< GPB_MFPH PB9 setting for GPIO*/
#define SYS_GPB_MFPH_PB9MFP_EADC_CH6           (1ul << SYS_GPB_MFPH_PB9MFP_Pos)        /*!< GPB_MFPH PB9 setting for EADC_CH6*/

//PB10
#define SYS_GPB_MFPH_PB10MFP_GPIO              (0ul << SYS_GPB_MFPH_PB10MFP_Pos)        /*!< GPB_MFPH_ PB10 setting for GPIO*/
#define SYS_GPB_MFPH_PB10MFP_EADC_CH7          (1ul << SYS_GPB_MFPH_PB10MFP_Pos)        /*!< GPB_MFPH_ PB10 setting for EADC_CH7*/

//PB11
#define SYS_GPB_MFPH_PB11MFP_GPIO              (0ul << SYS_GPB_MFPH_PB11MFP_Pos)        /*!< GPB_MFPH_ PB11 setting for GPIO*/
#define SYS_GPB_MFPH_PB11MFP_EADC_CH8          (1ul << SYS_GPB_MFPH_PB11MFP_Pos)        /*!< GPB_MFPH_ PB11 setting for EADC_CH8*/
#define SYS_GPB_MFPH_PB11MFP_TK0               (4ul << SYS_GPB_MFPH_PB11MFP_Pos)        /*!< GPB_MFPH_ PB11 setting for TK0*/

//PB12
#define SYS_GPB_MFPH_PB12MFP_GPIO              (0ul << SYS_GPB_MFPH_PB12MFP_Pos)        /*!< GPB_MFPH_ PB12 setting for GPIO*/
#define SYS_GPB_MFPH_PB12MFP_EADC_CH9          (1ul << SYS_GPB_MFPH_PB12MFP_Pos)        /*!< GPB_MFPH_ PB12 setting for EADC_CH9*/
#define SYS_GPB_MFPH_PB12MFP_TK1               (4ul << SYS_GPB_MFPH_PB12MFP_Pos)        /*!< GPB_MFPH_ PB12 setting for TK1*/

//PB13
#define SYS_GPB_MFPH_PB13MFP_GPIO              (0ul << SYS_GPB_MFPH_PB13MFP_Pos)        /*!< GPB_MFPH PB13 setting for GPIO*/
#define SYS_GPB_MFPH_PB13MFP_EADC_CH10         (1ul << SYS_GPB_MFPH_PB13MFP_Pos)        /*!< GPB_MFPH PB13 setting for EADC_CH10*/

//PB14
#define SYS_GPB_MFPH_PB14MFP_GPIO              (0ul << SYS_GPB_MFPH_PB14MFP_Pos)        /*!< GPB_MFPH PB14 setting for GPIO*/
#define SYS_GPB_MFPH_PB14MFP_EADC_CH11         (1ul << SYS_GPB_MFPH_PB14MFP_Pos)        /*!< GPB_MFPH PB14 setting for EADC_CH11*/

//PB15
#define SYS_GPB_MFPH_PB15MFP_GPIO              (0ul << SYS_GPB_MFPH_PB15MFP_Pos)        /*!< GPB_MFPH PB15 setting for GPIO*/
#define SYS_GPB_MFPH_PB15MFP_EADC_CH12         (1ul << SYS_GPB_MFPH_PB15MFP_Pos)        /*!< GPB_MFPH PB15 setting for EADC_CH12*/
#define SYS_GPB_MFPH_PB15MFP_TK2               (4ul << SYS_GPB_MFPH_PB15MFP_Pos)        /*!< GPB_MFPH PB15 setting for TK2*/
#define SYS_GPB_MFPH_PB15MFP_ACMP0_P3          (5ul << SYS_GPB_MFPH_PB15MFP_Pos)        /*!< GPB_MFPH PB15 setting for ACMP0_P3*/
#define SYS_GPB_MFPH_PB15MFP_EBI_nCS1          (7ul << SYS_GPB_MFPH_PB15MFP_Pos)        /*!< GPB_MFPH PB15 setting for EBI_nCS1*/

//PC0
#define SYS_GPC_MFPL_PC0MFP_GPIO               (0ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for GPIO*/
#define SYS_GPC_MFPL_PC0MFP_SPI2_CLK           (2ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for SPI2_CLK*/
#define SYS_GPC_MFPL_PC0MFP_UART2_nCTS         (3ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for UART2_nCTS*/
#define SYS_GPC_MFPL_PC0MFP_CAN0_TXD           (4ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for CAN0_TXD*/
#define SYS_GPC_MFPL_PC0MFP_PWM0_CH0           (6ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for PWM0_CH0*/
#define SYS_GPC_MFPL_PC0MFP_EBI_AD8            (7ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for EBI_AD8*/
#define SYS_GPC_MFPL_PC0MFP_INT2               (8ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for INT2*/
#define SYS_GPC_MFPL_PC0MFP_UART3_TXD          (9ul << SYS_GPC_MFPL_PC0MFP_Pos)        /*!< GPC_MFPL PC0 setting for UART3_TXD*/
#define SYS_GPC_MFPL_PC0MFP_T3_EXT             (11ul << SYS_GPC_MFPL_PC0MFP_Pos)       /*!< GPC_MFPL PC0 setting for T3_EXT*/

//PC1
#define SYS_GPC_MFPL_PC1MFP_GPIO               (0ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for GPIO*/
#define SYS_GPC_MFPL_PC1MFP_CLKO               (1ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for CLKO*/
#define SYS_GPC_MFPL_PC1MFP_STDAC              (2ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for STDAC*/
#define SYS_GPC_MFPL_PC1MFP_UART2_nRTS         (3ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for UART2_nRTS*/
#define SYS_GPC_MFPL_PC1MFP_CAN0_RXD           (4ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for CAN0_RXD*/
#define SYS_GPC_MFPL_PC1MFP_PWM0_CH1           (6ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for PWM0_CH1*/
#define SYS_GPC_MFPL_PC1MFP_EBI_AD9            (7ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for EBI_AD9*/
#define SYS_GPC_MFPL_PC1MFP_UART3_RXD          (9ul << SYS_GPC_MFPL_PC1MFP_Pos)        /*!< GPC_MFPL PC1 setting for UART3_RXD*/

//PC2
#define SYS_GPC_MFPL_PC2MFP_GPIO               (0ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for GPIO*/
#define SYS_GPC_MFPL_PC2MFP_SPI2_SS            (2ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for SPI2_SS*/
#define SYS_GPC_MFPL_PC2MFP_UART2_TXD          (3ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for UART2_TXD*/
#define SYS_GPC_MFPL_PC2MFP_ACMP1_O            (5ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for ACMP1_O*/
#define SYS_GPC_MFPL_PC2MFP_PWM0_CH2           (6ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for PWM0_CH2*/
#define SYS_GPC_MFPL_PC2MFP_EBI_AD10           (7ul << SYS_GPC_MFPL_PC2MFP_Pos)        /*!< GPC_MFPL PC2 setting for EBI_AD10*/

//PC3
#define SYS_GPC_MFPL_PC3MFP_GPIO               (0ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for GPIO*/
#define SYS_GPC_MFPL_PC3MFP_SPI2_MOSI          (2ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for SPI2_MOSI*/
#define SYS_GPC_MFPL_PC3MFP_UART2_RXD          (3ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for UART2_RXD*/
#define SYS_GPC_MFPL_PC3MFP_USB_VBUS_ST        (4ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for USB_VBUS_ST*/
#define SYS_GPC_MFPL_PC3MFP_PWM0_CH3           (6ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for PWM0_CH3*/
#define SYS_GPC_MFPL_PC3MFP_EBI_AD11           (7ul << SYS_GPC_MFPL_PC3MFP_Pos)        /*!< GPC_MFPL PC3 setting for EBI_AD11*/

//PC4
#define SYS_GPC_MFPL_PC4MFP_GPIO               (0ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for GPIO*/
#define SYS_GPC_MFPL_PC4MFP_SPI2_MISO          (2ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for SPI2_MISO*/
#define SYS_GPC_MFPL_PC4MFP_I2C1_SCL           (3ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for I2C1_SCL*/
#define SYS_GPC_MFPL_PC4MFP_USB_VBUS_EN        (4ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for USB_VBUS_EN*/
#define SYS_GPC_MFPL_PC4MFP_PWM0_CH4           (6ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for PWM0_CH4*/
#define SYS_GPC_MFPL_PC4MFP_EBI_AD12           (7ul << SYS_GPC_MFPL_PC4MFP_Pos)        /*!< GPC_MFPL PC4 setting for EBI_AD12*/

//PC5
#define SYS_GPC_MFPL_PC5MFP_GPIO               (0ul << SYS_GPC_MFPL_PC5MFP_Pos)        /*!< GPC_MFPL PC5 setting for GPIO*/
#define SYS_GPC_MFPL_PC5MFP_SPI2_I2SMCLK       (2ul << SYS_GPC_MFPL_PC5MFP_Pos)        /*!< GPC_MFPL PC5 setting for SPI2_I2SMCLK*/
#define SYS_GPC_MFPL_PC5MFP_PWM0_CH5           (6ul << SYS_GPC_MFPL_PC5MFP_Pos)        /*!< GPC_MFPL PC5 setting for PWM0_CH5*/
#define SYS_GPC_MFPL_PC5MFP_EBI_AD13           (7ul << SYS_GPC_MFPL_PC5MFP_Pos)        /*!< GPC_MFPL PC5 setting for EBI_AD13*/

//PC6
#define SYS_GPC_MFPL_PC6MFP_GPIO               (0ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for GPIO*/
#define SYS_GPC_MFPL_PC6MFP_I2C1_SMBAL         (3ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for I2C1_SMBAL*/
#define SYS_GPC_MFPL_PC6MFP_ACMP1_O            (5ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for ACMP1_O*/
#define SYS_GPC_MFPL_PC6MFP_PWM1_CH0           (6ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for PWM1_CH0*/
#define SYS_GPC_MFPL_PC6MFP_EBI_AD14           (7ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for EBI_AD14*/
#define SYS_GPC_MFPL_PC6MFP_UART0_TXD          (9ul << SYS_GPC_MFPL_PC6MFP_Pos)        /*!< GPC_MFPL PC6 setting for UART0_TXD*/

//PC7
#define SYS_GPC_MFPL_PC7MFP_GPIO               (0ul << SYS_GPC_MFPL_PC7MFP_Pos)        /*!< GPC_MFPL PC7 setting for GPIO*/
#define SYS_GPC_MFPL_PC7MFP_I2C1_SMBSUS        (3ul << SYS_GPC_MFPL_PC7MFP_Pos)        /*!< GPC_MFPL PC7 setting for I2C1_SMBSUS*/
#define SYS_GPC_MFPL_PC7MFP_PWM1_CH1           (6ul << SYS_GPC_MFPL_PC7MFP_Pos)        /*!< GPC_MFPL PC7 setting for PWM1_CH1*/
#define SYS_GPC_MFPL_PC7MFP_EBI_AD15           (7ul << SYS_GPC_MFPL_PC7MFP_Pos)        /*!< GPC_MFPL PC7 setting for EBI_AD15*/
#define SYS_GPC_MFPL_PC7MFP_UART0_RXD          (9ul << SYS_GPC_MFPL_PC7MFP_Pos)        /*!< GPC_MFPL PC7 setting for UART0_RXD*/

//PC8
#define SYS_GPC_MFPH_PC8MFP_GPIO               (0ul << SYS_GPC_MFPH_PC8MFP_Pos)        /*!< GPC_MFPH_ PC8 setting for GPIO*/
#define SYS_GPC_MFPH_PC8MFP_TK7                (4ul << SYS_GPC_MFPH_PC8MFP_Pos)        /*!< GPC_MFPH_ PC8 setting for TK7*/

//PC9
#define SYS_GPC_MFPH_PC9MFP_GPIO               (0ul << SYS_GPC_MFPH_PC9MFP_Pos)        /*!< GPC_MFPH PC9 setting for GPIO*/
#define SYS_GPC_MFPH_PC9MFP_SPI2_I2SMCLK       (2ul << SYS_GPC_MFPH_PC9MFP_Pos)        /*!< GPC_MFPH PC9 setting for SPI2_I2SMCLK*/
#define SYS_GPC_MFPH_PC9MFP_PWM1_CH0           (6ul << SYS_GPC_MFPH_PC9MFP_Pos)        /*!< GPC_MFPH PC9 setting for PWM1_CH0*/

//PC10
#define SYS_GPC_MFPH_PC10MFP_GPIO              (0ul << SYS_GPC_MFPH_PC10MFP_Pos)        /*!< GPC_MFPH PC10 setting for GPIO*/
#define SYS_GPC_MFPH_PC10MFP_SPI2_MOSI         (2ul << SYS_GPC_MFPH_PC10MFP_Pos)        /*!< GPC_MFPH PC10 setting for SPI2_MOSI*/
#define SYS_GPC_MFPH_PC10MFP_PWM1_CH1          (6ul << SYS_GPC_MFPH_PC10MFP_Pos)        /*!< GPC_MFPH PC10 setting for PWM1_CH1*/

//PC11
#define SYS_GPC_MFPH_PC11MFP_GPIO              (0ul << SYS_GPC_MFPH_PC11MFP_Pos)        /*!< GPC_MFPH PC11 setting for GPIO*/
#define SYS_GPC_MFPH_PC11MFP_SPI2_MISO         (2ul << SYS_GPC_MFPH_PC11MFP_Pos)        /*!< GPC_MFPH PC11 setting for SPI2_MISO*/
#define SYS_GPC_MFPH_PC11MFP_PWM1_CH2          (6ul << SYS_GPC_MFPH_PC11MFP_Pos)        /*!< GPC_MFPH PC11 setting for PWM1_CH2*/

//PC12
#define SYS_GPC_MFPH_PC12MFP_GPIO              (0ul << SYS_GPC_MFPH_PC12MFP_Pos)        /*!< GPC_MFPH PC12 setting for GPIO*/
#define SYS_GPC_MFPH_PC12MFP_SPI2_CLK          (2ul << SYS_GPC_MFPH_PC12MFP_Pos)        /*!< GPC_MFPH PC12 setting for SPI2_CLK*/
#define SYS_GPC_MFPH_PC12MFP_PWM1_CH3          (6ul << SYS_GPC_MFPH_PC12MFP_Pos)        /*!< GPC_MFPH PC12 setting for PWM1_CH3*/

//PC13
#define SYS_GPC_MFPH_PC13MFP_GPIO              (0ul << SYS_GPC_MFPH_PC13MFP_Pos)        /*!< GPC_MFPH PC13 setting for GPIO*/
#define SYS_GPC_MFPH_PC13MFP_SPI2_SS           (2ul << SYS_GPC_MFPH_PC13MFP_Pos)        /*!< GPC_MFPH PC13 setting for SPI2_SS*/
#define SYS_GPC_MFPH_PC13MFP_PWM1_CH4          (6ul << SYS_GPC_MFPH_PC13MFP_Pos)        /*!< GPC_MFPH PC13 setting for PWM1_CH4*/

//PC14
#define SYS_GPC_MFPH_PC14MFP_GPIO              (0ul << SYS_GPC_MFPH_PC14MFP_Pos)        /*!< GPC_MFPH PC14 setting for GPIO*/
#define SYS_GPC_MFPH_PC14MFP_PWM1_CH5          (6ul << SYS_GPC_MFPH_PC14MFP_Pos)        /*!< GPC_MFPH PC14 setting for PWM1_CH5*/

//PC15
#define SYS_GPC_MFPH_PC15MFP_GPIO              (0ul << SYS_GPC_MFPH_PC15MFP_Pos)        /*!< GPC_MFPH PC15 setting for GPIO*/
#define SYS_GPC_MFPH_PC15MFP_PWM1_CH0          (6ul << SYS_GPC_MFPH_PC15MFP_Pos)        /*!< GPC_MFPH PC15 setting for PWM1_CH0*/

//PD0
#define SYS_GPD_MFPL_PD0MFP_GPIO            (0ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for GPIO*/
#define SYS_GPD_MFPL_PD0MFP_EADC_CH6        (1ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for EADC_CH6*/
#define SYS_GPD_MFPL_PD0MFP_SPI1_I2SMCLK    (2ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for SPI1_I2SMCLK*/
#define SYS_GPD_MFPL_PD0MFP_UART0_RXD       (3ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for UART0_RXD*/
#define SYS_GPD_MFPL_PD0MFP_TK6             (4ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for TK6*/
#define SYS_GPD_MFPL_PD0MFP_ACMP1_N         (5ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for ACMP1_N*/
#define SYS_GPD_MFPL_PD0MFP_INT3            (8ul << SYS_GPD_MFPL_PD0MFP_Pos)        /*!< GPD_MFPL PD0 setting for INT3*/
#define SYS_GPD_MFPL_PD0MFP_T3              (11ul << SYS_GPD_MFPL_PD0MFP_Pos)       /*!< GPD_MFPL PD0 setting for T3*/

//PD1
#define SYS_GPD_MFPL_PD1MFP_GPIO            (0ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for GPIO*/
#define SYS_GPD_MFPL_PD1MFP_EADC_CH11       (1ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for EADC_CH11*/
#define SYS_GPD_MFPL_PD1MFP_PWM0_SYNC_IN    (2ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for PWM0_SYNC_IN*/
#define SYS_GPD_MFPL_PD1MFP_UART0_TXD       (3ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for UART0_TXD*/
#define SYS_GPD_MFPL_PD1MFP_TK10            (4ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for TK10*/
#define SYS_GPD_MFPL_PD1MFP_ACMP1_P2        (5ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for ACMP1_P2*/
#define SYS_GPD_MFPL_PD1MFP_T0              (6ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for T0*/
#define SYS_GPD_MFPL_PD1MFP_EBI_nRD         (7ul << SYS_GPD_MFPL_PD1MFP_Pos)        /*!< GPD_MFPL PD1 setting for EBI_nRD*/

//PD2
#define SYS_GPD_MFPL_PD2MFP_GPIO            (0ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for GPIO*/
#define SYS_GPD_MFPL_PD2MFP_STADC           (1ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for STADC*/
#define SYS_GPD_MFPL_PD2MFP_T0_EXT          (3ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for T0_EXT*/
#define SYS_GPD_MFPL_PD2MFP_TK11            (4ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for TK11*/
#define SYS_GPD_MFPL_PD2MFP_ACMP1_P1        (5ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for ACMP1_P1*/
#define SYS_GPD_MFPL_PD2MFP_PWM0_BRAKE0     (6ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for PWM0_BRAKE0*/
#define SYS_GPD_MFPL_PD2MFP_EBI_nWR         (7ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for EBI_nWR*/
#define SYS_GPD_MFPL_PD2MFP_INT0            (8ul << SYS_GPD_MFPL_PD2MFP_Pos)        /*!< GPD_MFPL PD2 setting for INT0*/

//PD3
#define SYS_GPD_MFPL_PD3MFP_GPIO            (0ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for GPIO*/
#define SYS_GPD_MFPL_PD3MFP_T2              (1ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for T2*/
#define SYS_GPD_MFPL_PD3MFP_T1_EXT          (3ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for T1_EXT*/
#define SYS_GPD_MFPL_PD3MFP_TK12            (4ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for TK12*/
#define SYS_GPD_MFPL_PD3MFP_ACMP1_P0        (5ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for ACMP1_P0*/
#define SYS_GPD_MFPL_PD3MFP_PWM0_BRAKE1     (6ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for PWM0_BRAKE1*/
#define SYS_GPD_MFPL_PD3MFP_EBI_MCLK        (7ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for EBI_MCLK*/
#define SYS_GPD_MFPL_PD3MFP_INT1            (8ul << SYS_GPD_MFPL_PD3MFP_Pos)        /*!< GPD_MFPL PD3 setting for INT1*/

//PD4
#define SYS_GPD_MFPL_PD4MFP_GPIO            (0ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for GPIO*/
#define SYS_GPD_MFPL_PD4MFP_SPI1_CLK        (2ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for SPI1_CLK*/
#define SYS_GPD_MFPL_PD4MFP_I2C0_SDA        (3ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for I2C0_SDA*/
#define SYS_GPD_MFPL_PD4MFP_TK13            (4ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for TK13*/
#define SYS_GPD_MFPL_PD4MFP_PWM0_BRAKE0     (5ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for PWM0_BRAKE0*/
#define SYS_GPD_MFPL_PD4MFP_T0              (6ul << SYS_GPD_MFPL_PD4MFP_Pos)        /*!< GPD_MFPL PD4 setting for T0*/

//PD5
#define SYS_GPD_MFPL_PD5MFP_GPIO            (0ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for GPIO*/
#define SYS_GPD_MFPL_PD5MFP_CLKO            (1ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for CLKO*/
#define SYS_GPD_MFPL_PD5MFP_SPI1_MISO       (2ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for SPI1_MISO*/
#define SYS_GPD_MFPL_PD5MFP_I2C0_SCL        (3ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for I2C0_SCL*/
#define SYS_GPD_MFPL_PD5MFP_TK14            (4ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for TK14*/
#define SYS_GPD_MFPL_PD5MFP_PWM0_BRAKE1     (5ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for PWM0_BRAKE1*/
#define SYS_GPD_MFPL_PD5MFP_T1              (6ul << SYS_GPD_MFPL_PD5MFP_Pos)        /*!< GPD_MFPL PD5 setting for T1*/

//PD6
#define SYS_GPD_MFPL_PD6MFP_GPIO            (0ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for GPIO*/
#define SYS_GPD_MFPL_PD6MFP_CLKO            (1ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for CLKO*/
#define SYS_GPD_MFPL_PD6MFP_SPI1_SS         (2ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for SPI1_SS*/
#define SYS_GPD_MFPL_PD6MFP_UART0_RXD       (3ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for UART0_RXD*/
#define SYS_GPD_MFPL_PD6MFP_TK16            (4ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for TK16*/
#define SYS_GPD_MFPL_PD6MFP_ACMP0_O         (5ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for ACMP0_O*/
#define SYS_GPD_MFPL_PD6MFP_PWM0_CH5        (6ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for PWM0_CH5*/
#define SYS_GPD_MFPL_PD6MFP_EBI_nWR         (7ul << SYS_GPD_MFPL_PD6MFP_Pos)        /*!< GPD_MFPL PD6 setting for EBI_nWR*/

//PD7
#define SYS_GPD_MFPL_PD7MFP_GPIO           (0ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for GPIO*/
#define SYS_GPD_MFPL_PD7MFP_PWM0_SYNC_IN   (3ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for PWM0_SYNC_IN*/
#define SYS_GPD_MFPL_PD7MFP_T1             (4ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for T1*/
#define SYS_GPD_MFPL_PD7MFP_ACMP0_O        (5ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for ACMP0_O*/
#define SYS_GPD_MFPL_PD7MFP_PWM0_CH5       (6ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for PWM0_CH5*/
#define SYS_GPD_MFPL_PD7MFP_EBI_nRD        (7ul << SYS_GPD_MFPL_PD7MFP_Pos)        /*!< GPD_MFPL PD7 setting for EBI_nRD*/

//PD8
#define SYS_GPD_MFPH_PD8MFP_GPIO               (0ul << SYS_GPD_MFPH_PD8MFP_Pos)        /*!< GPD_MFPH PD8 setting for GPIO*/
#define SYS_GPD_MFPH_PD8MFP_EADC_CH7           (1ul << SYS_GPD_MFPH_PD8MFP_Pos)        /*!< GPD_MFPH PD8 setting for EADC_CH7*/
#define SYS_GPD_MFPH_PD8MFP_TK8                (4ul << SYS_GPD_MFPH_PD8MFP_Pos)        /*!< GPD_MFPH PD8 setting for TK8*/
#define SYS_GPD_MFPH_PD8MFP_EBI_nCS0           (7ul << SYS_GPD_MFPH_PD8MFP_Pos)        /*!< GPD_MFPH PD8 setting for EBI_nCS0*/

//PD9
#define SYS_GPD_MFPH_PD9MFP_GPIO               (0ul << SYS_GPD_MFPH_PD9MFP_Pos)        /*!< GPD_MFPH PD9 setting for GPIO*/
#define SYS_GPD_MFPH_PD9MFP_EADC_CH10          (1ul << SYS_GPD_MFPH_PD9MFP_Pos)        /*!< GPD_MFPH PD9 setting for EADC_CH10*/
#define SYS_GPD_MFPH_PD9MFP_TK9                (4ul << SYS_GPD_MFPH_PD9MFP_Pos)        /*!< GPD_MFPH PD9 setting for TK9*/
#define SYS_GPD_MFPH_PD9MFP_ACMP1_P3           (5ul << SYS_GPD_MFPH_PD9MFP_Pos)        /*!< GPD_MFPH PD9 setting for ACMP1_P3*/
#define SYS_GPD_MFPH_PD9MFP_EBI_ALE            (7ul << SYS_GPD_MFPH_PD9MFP_Pos)        /*!< GPD_MFPH PD9 setting for EBI_ALE*/

//PD10
#define SYS_GPD_MFPH_PD10MFP_GPIO              (0ul << SYS_GPD_MFPH_PD10MFP_Pos)        /*!< GPD_MFPH PD10 setting for GPIO*/
#define SYS_GPD_MFPH_PD10MFP_T2                (4ul << SYS_GPD_MFPH_PD10MFP_Pos)        /*!< GPD_MFPH PD10 setting for T2*/

//PD11
#define SYS_GPD_MFPH_PD11MFP_GPIO              (0ul << SYS_GPD_MFPH_PD11MFP_Pos)        /*!< GPD_MFPH PD11 setting for GPIO*/
#define SYS_GPD_MFPH_PD11MFP_T3                (4ul << SYS_GPD_MFPH_PD11MFP_Pos)        /*!< GPD_MFPH PD11 setting for T3*/

//PD12
#define SYS_GPD_MFPH_PD12MFP_GPIO              (0ul << SYS_GPD_MFPH_PD12MFP_Pos)        /*!< GPD_MFPH PD12 setting for GPIO*/
#define SYS_GPD_MFPH_PD12MFP_SPI2_SS           (2ul << SYS_GPD_MFPH_PD12MFP_Pos)        /*!< GPD_MFPH PD12 setting for SPI2_SS*/
#define SYS_GPD_MFPH_PD12MFP_UART3_TXD         (3ul << SYS_GPD_MFPH_PD12MFP_Pos)        /*!< GPD_MFPH PD12 setting for UART3_TXD*/
#define SYS_GPD_MFPH_PD12MFP_PWM1_CH0          (6ul << SYS_GPD_MFPH_PD12MFP_Pos)        /*!< GPD_MFPH PD12 setting for PWM1_CH0*/
#define SYS_GPD_MFPH_PD12MFP_EBI_ADR16         (7ul << SYS_GPD_MFPH_PD12MFP_Pos)        /*!< GPD_MFPH PD12 setting for EBI_ADR16*/

//PD13
#define SYS_GPD_MFPH_PD13MFP_GPIO              (0ul << SYS_GPD_MFPH_PD13MFP_Pos)        /*!< GPD_MFPH PD13 setting for GPIO*/
#define SYS_GPD_MFPH_PD13MFP_SPI2_MOSI         (2ul << SYS_GPD_MFPH_PD13MFP_Pos)        /*!< GPD_MFPH PD13 setting for SPI2_MOSI*/
#define SYS_GPD_MFPH_PD13MFP_UART3_RXD         (3ul << SYS_GPD_MFPH_PD13MFP_Pos)        /*!< GPD_MFPH PD13 setting for UART3_RXD*/
#define SYS_GPD_MFPH_PD13MFP_PWM1_CH1          (6ul << SYS_GPD_MFPH_PD13MFP_Pos)        /*!< GPD_MFPH PD13 setting for PWM1_CH1*/
#define SYS_GPD_MFPH_PD13MFP_EBI_ADR17         (7ul << SYS_GPD_MFPH_PD13MFP_Pos)        /*!< GPD_MFPH PD13 setting for EBI_ADR17*/

//PD14
#define SYS_GPD_MFPH_PD14MFP_GPIO              (0ul << SYS_GPD_MFPH_PD14MFP_Pos)        /*!< GPD_MFPH_ PD14 setting for GPIO*/
#define SYS_GPD_MFPH_PD14MFP_SPI2_MISO         (2ul << SYS_GPD_MFPH_PD14MFP_Pos)        /*!< GPD_MFPH_ PD14 setting for SPI2_MISO*/
#define SYS_GPD_MFPH_PD14MFP_UART3_nCTS        (3ul << SYS_GPD_MFPH_PD14MFP_Pos)        /*!< GPD_MFPH_ PD14 setting for UART3_nCTS*/
#define SYS_GPD_MFPH_PD14MFP_PWM1_CH2          (6ul << SYS_GPD_MFPH_PD14MFP_Pos)        /*!< GPD_MFPH_ PD14 setting for PWM1_CH2*/
#define SYS_GPD_MFPH_PD14MFP_EBI_ADR18         (7ul << SYS_GPD_MFPH_PD14MFP_Pos)        /*!< GPD_MFPH_ PD14 setting for EBI_ADR18*/

//PD15
#define SYS_GPD_MFPH_PD15MFP_GPIO              (0ul << SYS_GPD_MFPH_PD15MFP_Pos)        /*!< GPD_MFPH_ PD15 setting for GPIO*/
#define SYS_GPD_MFPH_PD15MFP_SPI2_CLK          (2ul << SYS_GPD_MFPH_PD15MFP_Pos)        /*!< GPD_MFPH_ PD15 setting for SPI2_CLK*/
#define SYS_GPD_MFPH_PD15MFP_UART3_nRTS        (3ul << SYS_GPD_MFPH_PD15MFP_Pos)        /*!< GPD_MFPH_ PD15 setting for UART3_nRTS*/
#define SYS_GPD_MFPH_PD15MFP_PWM1_CH3          (6ul << SYS_GPD_MFPH_PD15MFP_Pos)        /*!< GPD_MFPH_ PD15 setting for PWM1_CH3*/
#define SYS_GPD_MFPH_PD15MFP_EBI_ADR19         (7ul << SYS_GPD_MFPH_PD15MFP_Pos)        /*!< GPD_MFPH_ PD15 setting for EBI_ADR19*/

//PE0
#define SYS_GPE_MFPL_PE0MFP_GPIO               (0ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for GPIO*/
#define SYS_GPE_MFPL_PE0MFP_SPI2_CLK           (2ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for SPI2_CLK*/
#define SYS_GPE_MFPL_PE0MFP_I2C1_SDA           (3ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for I2C1_SDA*/
#define SYS_GPE_MFPL_PE0MFP_T2_EXT             (4ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for T2_EXT*/
#define SYS_GPE_MFPL_PE0MFP_SC0_CD             (5ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for SC0_CD*/
#define SYS_GPE_MFPL_PE0MFP_PWM0_CH0           (6ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for PWM0_CH0*/
#define SYS_GPE_MFPL_PE0MFP_EBI_nCS1           (7ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for EBI_nCS1*/
#define SYS_GPE_MFPL_PE0MFP_INT4               (8ul << SYS_GPE_MFPL_PE0MFP_Pos)        /*!< GPE_MFPL PE0 setting for INT4*/

//PE1
#define SYS_GPE_MFPL_PE1MFP_GPIO               (0ul << SYS_GPE_MFPL_PE1MFP_Pos)        /*!< GPE_MFPL PE1 setting for GPIO*/
#define SYS_GPE_MFPL_PE1MFP_T3_EXT             (3ul << SYS_GPE_MFPL_PE1MFP_Pos)        /*!< GPE_MFPL PE1 setting for T3_EXT*/
#define SYS_GPE_MFPL_PE1MFP_SC0_CD             (5ul << SYS_GPE_MFPL_PE1MFP_Pos)        /*!< GPE_MFPL PE1 setting for SC0_CD*/
#define SYS_GPE_MFPL_PE1MFP_PWM0_CH1           (6ul << SYS_GPE_MFPL_PE1MFP_Pos)        /*!< GPE_MFPL PE1 setting for PWM0_CH1*/

//PE2
#define SYS_GPE_MFPL_PE2MFP_GPIO               (0ul << SYS_GPE_MFPL_PE2MFP_Pos)        /*!< GPE_MFPL PE2 setting for GPIO*/
#define SYS_GPE_MFPL_PE2MFP_PWM1_CH1           (6ul << SYS_GPE_MFPL_PE2MFP_Pos)        /*!< GPE_MFPL PE2 setting for PWM1_CH1*/

//PE3
#define SYS_GPE_MFPL_PE3MFP_GPIO               (0ul << SYS_GPE_MFPL_PE3MFP_Pos)        /*!< GPE_MFPL PE3 setting for GPIO*/
#define SYS_GPE_MFPL_PE3MFP_SPI1_MOSI          (2ul << SYS_GPE_MFPL_PE3MFP_Pos)        /*!< GPE_MFPL PE3 setting for SPI1_MOSI*/
#define SYS_GPE_MFPL_PE3MFP_TK15               (4ul << SYS_GPE_MFPL_PE3MFP_Pos)        /*!< GPE_MFPL PE3 setting for TK15*/
#define SYS_GPE_MFPL_PE3MFP_PWM0_CH3           (6ul << SYS_GPE_MFPL_PE3MFP_Pos)        /*!< GPE_MFPL PE3 setting for PWM0_CH3*/

//PE4
#define SYS_GPE_MFPL_PE4MFP_GPIO               (0ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for GPIO*/
#define SYS_GPE_MFPL_PE4MFP_I2C1_SCL           (3ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for I2C1_SCL*/
#define SYS_GPE_MFPL_PE4MFP_SC0_PWR            (5ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for SC0_PWR*/
#define SYS_GPE_MFPL_PE4MFP_PWM1_BRAKE0        (6ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for PWM1_BRAKE0*/
#define SYS_GPE_MFPL_PE4MFP_EBI_nCS0           (7ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for EBI_nCS0*/
#define SYS_GPE_MFPL_PE4MFP_INT0               (8ul << SYS_GPE_MFPL_PE4MFP_Pos)        /*!< GPE_MFPL PE4 setting for INT0*/

//PE5
#define SYS_GPE_MFPL_PE5MFP_GPIO               (0ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for GPIO*/
#define SYS_GPE_MFPL_PE5MFP_I2C1_SDA           (3ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for I2C1_SDA*/
#define SYS_GPE_MFPL_PE5MFP_SC0_RST            (5ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for SC0_RST*/
#define SYS_GPE_MFPL_PE5MFP_PWM1_BRAKE1        (6ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for PWM1_BRAKE1*/
#define SYS_GPE_MFPL_PE5MFP_EBI_ALE            (7ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for EBI_ALE*/
#define SYS_GPE_MFPL_PE5MFP_INT1               (8ul << SYS_GPE_MFPL_PE5MFP_Pos)        /*!< GPE_MFPL PE5 setting for INT1*/

//PE6
#define SYS_GPE_MFPL_PE6MFP_GPIO               (0ul << SYS_GPE_MFPL_PE6MFP_Pos)        /*!< GPE_MFPL PE6 setting for GPIO*/
#define SYS_GPE_MFPL_PE6MFP_T3_EXT             (3ul << SYS_GPE_MFPL_PE6MFP_Pos)        /*!< GPE_MFPL PE6 setting for T3_EXT*/

//PE7
#define SYS_GPE_MFPL_PE7MFP_GPIO               (0ul << SYS_GPE_MFPL_PE7MFP_Pos)        /*!< GPE_MFPL PE7 setting for GPIO*/

//PE8
#define SYS_GPE_MFPH_PE8MFP_GPIO               (0ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for GPIO*/
#define SYS_GPE_MFPH_PE8MFP_UART1_TXD          (1ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for UART1_TXD*/
#define SYS_GPE_MFPH_PE8MFP_SPI0_MISO1         (2ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for SPI0_MISO1*/
#define SYS_GPE_MFPH_PE8MFP_I2C1_SCL           (4ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for I2C1_SCL*/
#define SYS_GPE_MFPH_PE8MFP_SC0_PWR            (5ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for SC0_PWR*/
#define SYS_GPE_MFPH_PE8MFP_CLKO               (9ul << SYS_GPE_MFPH_PE8MFP_Pos)        /*!< GPE_MFPH PE8 setting for CLKO*/
#define SYS_GPE_MFPH_PE8MFP_PWM0_BRAKE0        (10ul << SYS_GPE_MFPH_PE8MFP_Pos)       /*!< GPE_MFPH PE8 setting for PWM0_BRAKE0*/
#define SYS_GPE_MFPH_PE8MFP_T1                 (11ul << SYS_GPE_MFPH_PE8MFP_Pos)       /*!< GPE_MFPH PE8 setting for T1*/

//PE9
#define SYS_GPE_MFPH_PE9MFP_GPIO               (0ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for GPIO*/
#define SYS_GPE_MFPH_PE9MFP_UART1_RXD          (1ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for UART1_RXD*/
#define SYS_GPE_MFPH_PE9MFP_SPI0_MOSI1         (2ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for SPI0_MOSI1*/
#define SYS_GPE_MFPH_PE9MFP_I2C1_SDA           (4ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for I2C1_SDA*/
#define SYS_GPE_MFPH_PE9MFP_SC0_RST            (5ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for SC0_RST*/
#define SYS_GPE_MFPH_PE9MFP_SPI1_I2SMCLK       (9ul << SYS_GPE_MFPH_PE9MFP_Pos)        /*!< GPE_MFPH PE9 setting for SPI1_I2SMCLK*/
#define SYS_GPE_MFPH_PE9MFP_PWM1_BRAKE1        (10ul << SYS_GPE_MFPH_PE9MFP_Pos)       /*!< GPE_MFPH PE9 setting for PWM1_BRAKE1*/
#define SYS_GPE_MFPH_PE9MFP_T2                 (11ul << SYS_GPE_MFPH_PE9MFP_Pos)       /*!< GPE_MFPH PE9 setting for T2*/

//PE10
#define SYS_GPE_MFPH_PE10MFP_GPIO              (0ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for GPIO*/
#define SYS_GPE_MFPH_PE10MFP_SPI1_MISO         (1ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for SPI1_MISO*/
#define SYS_GPE_MFPH_PE10MFP_SPI0_MISO0        (2ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for SPI0_MISO0*/
#define SYS_GPE_MFPH_PE10MFP_UART1_nCTS        (3ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for UART1_nCTS*/
#define SYS_GPE_MFPH_PE10MFP_I2C0_SMBAL        (4ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for I2C0_SMBAL*/
#define SYS_GPE_MFPH_PE10MFP_SC0_DAT           (5ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for SC0_DAT*/
#define SYS_GPE_MFPH_PE10MFP_UART3_TXD         (9ul << SYS_GPE_MFPH_PE10MFP_Pos)        /*!< GPE_MFPH PE10 setting for UART3_TXD*/
#define SYS_GPE_MFPH_PE10MFP_I2C1_SCL          (11ul << SYS_GPE_MFPH_PE10MFP_Pos)       /*!< GPE_MFPH PE10 setting for I2C1_SCL*/

//PE11
#define SYS_GPE_MFPH_PE11MFP_GPIO              (0ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for GPIO*/
#define SYS_GPE_MFPH_PE11MFP_SPI1_MOSI         (1ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for SPI1_MOSI*/
#define SYS_GPE_MFPH_PE11MFP_SPI0_MOSI0        (2ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for SPI0_MOSI0*/
#define SYS_GPE_MFPH_PE11MFP_UART1_nRTS        (3ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for UART1_nRTS*/
#define SYS_GPE_MFPH_PE11MFP_I2C0_SMBSUS       (4ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for I2C0_SMBSUS*/
#define SYS_GPE_MFPH_PE11MFP_SC0_CLK           (5ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for SC0_CLK*/
#define SYS_GPE_MFPH_PE11MFP_UART3_RXD         (9ul << SYS_GPE_MFPH_PE11MFP_Pos)        /*!< GPE_MFPH PE11 setting for UART3_RXD*/
#define SYS_GPE_MFPH_PE11MFP_I2C1_SDA          (11ul << SYS_GPE_MFPH_PE11MFP_Pos)       /*!< GPE_MFPH PE11 setting for I2C1_SDA*/

//PE12
#define SYS_GPE_MFPH_PE12MFP_GPIO              (0ul << SYS_GPE_MFPH_PE12MFP_Pos)        /*!< GPE_MFPH PE12 setting for GPIO*/
#define SYS_GPE_MFPH_PE12MFP_SPI1_SS           (1ul << SYS_GPE_MFPH_PE12MFP_Pos)        /*!< GPE_MFPH PE12 setting for SPI1_SS*/
#define SYS_GPE_MFPH_PE12MFP_SPI0_SS           (2ul << SYS_GPE_MFPH_PE12MFP_Pos)        /*!< GPE_MFPH PE12 setting for SPI0_SS*/
#define SYS_GPE_MFPH_PE12MFP_UART1_TXD         (3ul << SYS_GPE_MFPH_PE12MFP_Pos)        /*!< GPE_MFPH PE12 setting for UART1_TXD*/
#define SYS_GPE_MFPH_PE12MFP_I2C0_SCL          (4ul << SYS_GPE_MFPH_PE12MFP_Pos)        /*!< GPE_MFPH PE12 setting for I2C0_SCL*/

//PE13
#define SYS_GPE_MFPH_PE13MFP_GPIO              (0ul << SYS_GPE_MFPH_PE13MFP_Pos)        /*!< GPE_MFPH PE13 setting for GPIO*/
#define SYS_GPE_MFPH_PE13MFP_SPI1_CLK          (1ul << SYS_GPE_MFPH_PE13MFP_Pos)        /*!< GPE_MFPH PE13 setting for SPI1_CLK*/
#define SYS_GPE_MFPH_PE13MFP_SPI0_CLK          (2ul << SYS_GPE_MFPH_PE13MFP_Pos)        /*!< GPE_MFPH PE13 setting for SPI0_CLK*/
#define SYS_GPE_MFPH_PE13MFP_UART1_RXD         (3ul << SYS_GPE_MFPH_PE13MFP_Pos)        /*!< GPE_MFPH PE13 setting for UART1_RXD*/
#define SYS_GPE_MFPH_PE13MFP_I2C0_SDA          (4ul << SYS_GPE_MFPH_PE13MFP_Pos)        /*!< GPE_MFPH PE13 setting for I2C0_SDA*/

//PE14
#define SYS_GPE_MFPH_PE14MFP_GPIO              (0ul << SYS_GPE_MFPH_PE14MFP_Pos)        /*!< GPE_MFPH PE14 setting for GPIO*/

//PF0
#define SYS_GPF_MFPL_PF0MFP_GPIO               (0ul << SYS_GPF_MFPL_PF0MFP_Pos)        /*!< GPF_MFPL PF0 setting for GPIO*/
#define SYS_GPF_MFPL_PF0MFP_X32_OUT            (1ul << SYS_GPF_MFPL_PF0MFP_Pos)        /*!< GPF_MFPL PF0 setting for X32_OUT*/
#define SYS_GPF_MFPL_PF0MFP_INT5               (8ul << SYS_GPF_MFPL_PF0MFP_Pos)        /*!< GPF_MFPL PF0 setting for INT5*/

//PF1
#define SYS_GPF_MFPL_PF1MFP_GPIO               (0ul << SYS_GPF_MFPL_PF1MFP_Pos)        /*!< GPF_MFPL PF1 setting for GPIO*/
#define SYS_GPF_MFPL_PF1MFP_X32_IN             (1ul << SYS_GPF_MFPL_PF1MFP_Pos)        /*!< GPF_MFPL PF1 setting for X32_IN*/

//PF2
#define SYS_GPF_MFPL_PF2MFP_GPIO               (0ul << SYS_GPF_MFPL_PF2MFP_Pos)        /*!< GPF_MFPL PF2 setting for GPIO*/
#define SYS_GPF_MFPL_PF2MFP_TAMPER             (1ul << SYS_GPF_MFPL_PF2MFP_Pos)        /*!< GPF_MFPL PF2 setting for TAMPER*/

//PF3
#define SYS_GPF_MFPL_PF3MFP_GPIO               (0ul << SYS_GPF_MFPL_PF3MFP_Pos)        /*!< GPF_MFPL PF3 setting for GPIO*/
#define SYS_GPF_MFPL_PF3MFP_XT1_OUT            (1ul << SYS_GPF_MFPL_PF3MFP_Pos)        /*!< GPF_MFPL PF3 setting for XT1_OUT*/
#define SYS_GPF_MFPL_PF3MFP_I2C1_SCL           (3ul << SYS_GPF_MFPL_PF3MFP_Pos)        /*!< GPF_MFPL PF3 setting for I2C1_SCL*/

//PF4
#define SYS_GPF_MFPL_PF4MFP_GPIO               (0ul << SYS_GPF_MFPL_PF4MFP_Pos)        /*!< GPF_MFPL PF4 setting for GPIO*/
#define SYS_GPF_MFPL_PF4MFP_XT1_IN             (1ul << SYS_GPF_MFPL_PF4MFP_Pos)        /*!< GPF_MFPL PF4 setting for XT1_IN*/
#define SYS_GPF_MFPL_PF4MFP_I2C1_SDA           (3ul << SYS_GPF_MFPL_PF4MFP_Pos)        /*!< GPF_MFPL PF4 setting for I2C1_SDA*/

//PF5
#define SYS_GPF_MFPL_PF5MFP_GPIO               (0ul << SYS_GPF_MFPL_PF5MFP_Pos)        /*!< GPF_MFPL PF5 setting for GPIO*/
#define SYS_GPF_MFPL_PF5MFP_ICE_CLK            (1ul << SYS_GPF_MFPL_PF5MFP_Pos)        /*!< GPF_MFPL PF5 setting for ICE_CLK*/

//PF6
#define SYS_GPF_MFPL_PF6MFP_GPIO               (0ul << SYS_GPF_MFPL_PF6MFP_Pos)        /*!< GPF_MFPL PF6 setting for GPIO*/
#define SYS_GPF_MFPL_PF6MFP_ICE_DAT            (1ul << SYS_GPF_MFPL_PF6MFP_Pos)        /*!< GPF_MFPL PF6 setting for ICE_DAT*/

//PF7
#define SYS_GPF_MFPL_PF7MFP_GPIO               (0ul << SYS_GPF_MFPL_PF7MFP_Pos)        /*!< GPF_MFPL PF7 setting for GPIO*/


/*@}*/ /* end of group SYS_EXPORTED_CONSTANTS */


/** @addtogroup SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Set Brown-out detector function to normal mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to normal mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCTL &= ~SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro disable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Enable Brown-out detector function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)

/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.
  */
#define SYS_GET_BOD_INT_FLAG()          (SYS->BODCTL & SYS_BODCTL_BODIF_Msk)

/**
  * @brief      Get Brown-out detector status
  * @param      None
  * @retval     0   System voltage is higher than BOD threshold voltage setting or BOD function is disabled.
  * @retval     >=1 System voltage is lower than BOD threshold voltage setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD function is disabled, this function always return 0.
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Enable Brown-out detector interrupt function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detector interrupt function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None
  * @return     None
  * @details    This macro enable Brown-out detect reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Set Brown-out detector function low power mode
  * @param      None
  * @return     None
  * @details    This macro set Brown-out detector to low power mode.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_SET_BOD_LPM()               (SYS->BODCTL |= SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Set Brown-out detector voltage level
  * @param[in]  u32Level is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BODVL_4_5V
  *             - \ref SYS_BODCTL_BODVL_3_7V
  *             - \ref SYS_BODCTL_BODVL_2_7V
  *             - \ref SYS_BODCTL_BODVL_2_2V
  * @return     None
  * @details    This macro set Brown-out detector voltage level.
  *             The write-protection function should be disabled before using this macro.
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | (u32Level))

/**
  * @brief      Get reset source is from Brown-out detector reset
  * @param      None
  * @retval     0   Previous reset source is not from Brown-out detector reset
  * @retval     >=1 Previous reset source is from Brown-out detector reset
  * @details    This macro get previous reset source is from Brown-out detect reset or not.
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSTS & SYS_RSTSTS_BODRF_Msk)

/**
  * @brief      Get reset source is from CPU reset
  * @param      None
  * @retval     0   Previous reset source is not from CPU reset
  * @retval     >=1 Previous reset source is from CPU reset
  * @details    This macro get previous reset source is from CPU reset.
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSTS & SYS_RSTSTS_CPURF_Msk)

/**
  * @brief      Get reset source is from LVR Reset
  * @param      None     
  * @retval     0   Previous reset source is not from Low-Voltage-Reset
  * @retval     >=1 Previous reset source is from Low-Voltage-Reset
  * @details    This macro get previous reset source is from Low-Voltage-Reset.   
  */
#define SYS_IS_LVR_RST()                (SYS->RSTSTS & SYS_RSTSTS_LVRF_Msk)

/**
  * @brief      Get reset source is from Power-on Reset
  * @param      None
  * @retval     0   Previous reset source is not from Power-on Reset
  * @retval     >=1 Previous reset source is from Power-on Reset
  * @details    This macro get previous reset source is from Power-on Reset.
  */
#define SYS_IS_POR_RST()                (SYS->RSTSTS & SYS_RSTSTS_PORF_Msk)

/**
  * @brief      Get reset source is from reset pin reset
  * @param      None
  * @retval     0   Previous reset source is not from reset pin reset
  * @retval     >=1 Previous reset source is from reset pin reset
  * @details    This macro get previous reset source is from reset pin reset.
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSTS & SYS_RSTSTS_PINRF_Msk)

/**
  * @brief      Get reset source is from system reset
  * @param      None
  * @retval     0   Previous reset source is not from system reset
  * @retval     >=1 Previous reset source is from system reset
  * @details    This macro get previous reset source is from system reset.
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSTS & SYS_RSTSTS_SYSRF_Msk)

/**
  * @brief      Get reset source is from window watch dog reset
  * @param      None
  * @retval     0   Previous reset source is not from window watch dog reset
  * @retval     >=1 Previous reset source is from window watch dog reset
  * @details    This macro get previous reset source is from window watch dog reset.
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSTS & SYS_RSTSTS_WDTRF_Msk)

/**
  * @brief      Disable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro disable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None
  * @return     None
  * @details    This macro enable Power-on Reset function.
  *             The register write-protection function should be disabled before using this macro.
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
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) ((SYS->RSTSTS) = (u32RstSrc) )


/*---------------------------------------------------------------------------------------------------------*/
/* static inline functions                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/


/**
  * @brief      Disable register write-protection function
  * @param      None
  * @return     None
  * @details    This function disable register write-protection function.
  *             To unlock the protected register to allow write access.
  */
__STATIC_INLINE void SYS_UnlockReg(void)
{
    do
    {
        SYS->REGLCTL = 0x59;
        SYS->REGLCTL = 0x16;
        SYS->REGLCTL = 0x88;
    }
    while(SYS->REGLCTL == 0);
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

#endif  //__SYS_H__
