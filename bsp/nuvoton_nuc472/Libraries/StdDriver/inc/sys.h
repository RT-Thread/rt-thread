/**************************************************************************//**
 * @file     SYS.h
 * @version  V1.0
 * $Revision  1 $
 * $Date: 15/10/21 1:35p $
 * @brief    NUC472/NUC442 SYS Header File
 *
 * @note
 * Copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#ifndef __SYS_H__
#define __SYS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup NUC472_442_Device_Driver NUC472/NUC442 Device Driver
  @{
*/

/** @addtogroup NUC472_442_SYS_Driver SYS Driver
  @{
*/

/** @addtogroup NUC472_442_SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define PDMA_RST  ((0x0<<24)|SYS_IPRST0_PDMARST_Pos)    /*!<Reset PDMA  \hideinitializer */
#define EBI_RST   ((0x0<<24)|SYS_IPRST0_EBIRST_Pos)     /*!<Reset EBI  \hideinitializer  */
#define USBH_RST  ((0x0<<24)|SYS_IPRST0_USBHRST_Pos)    /*!<Reset USBH  \hideinitializer  */
#define EMAC_RST  ((0x0<<24)|SYS_IPRST0_EMACRST_Pos)    /*!<Reset EMAC  \hideinitializer */
#define SDH_RST   ((0x0<<24)|SYS_IPRST0_SDHRST_Pos)     /*!<Reset SDIO  \hideinitializer */
#define CRC_RST   ((0x0<<24)|SYS_IPRST0_CRCRST_Pos)     /*!<Reset CRC  \hideinitializer  */
#define CAP_RST   ((0x0<<24)|SYS_IPRST0_CAPRST_Pos)     /*!<Reset CAP  \hideinitializer  */
#define CRYPTO_RST ((0x0<<24)|SYS_IPRST0_CRYPTORST_Pos)  /*!<Reset CRYPTO  \hideinitializer */
#define GPIO_RST  ((0x4<<24)|SYS_IPRST1_GPIORST_Pos)    /*!<Reset GPIO  \hideinitializer  */
#define TMR0_RST  ((0x4<<24)|SYS_IPRST1_TMR0RST_Pos)    /*!<Reset TMR0  \hideinitializer */
#define TMR1_RST  ((0x4<<24)|SYS_IPRST1_TMR1RST_Pos)    /*!<Reset TMR1 \hideinitializer */
#define TMR2_RST  ((0x4<<24)|SYS_IPRST1_TMR2RST_Pos)    /*!<Reset TMR2 \hideinitializer */
#define TMR3_RST  ((0x4<<24)|SYS_IPRST1_TMR3RST_Pos)    /*!<Reset TMR3 \hideinitializer */
#define ACMP_RST  ((0x4<<24)|SYS_IPRST1_ACMPRST_Pos)    /*!<Reset ACMP \hideinitializer */
#define I2C0_RST  ((0x4<<24)|SYS_IPRST1_I2C0RST_Pos)    /*!<Reset I2C0 \hideinitializer */
#define I2C1_RST  ((0x4<<24)|SYS_IPRST1_I2C1RST_Pos)    /*!<Reset I2C1 \hideinitializer */
#define I2C2_RST  ((0x4<<24)|SYS_IPRST1_I2C2RST_Pos)    /*!<Reset I2C2 \hideinitializer */
#define I2C3_RST  ((0x4<<24)|SYS_IPRST1_I2C3RST_Pos)    /*!<Reset I2C3 \hideinitializer */
#define SPI0_RST  ((0x4<<24)|SYS_IPRST1_SPI0RST_Pos)    /*!<Reset SPI0 \hideinitializer */
#define SPI1_RST  ((0x4<<24)|SYS_IPRST1_SPI1RST_Pos)    /*!<Reset SPI1 \hideinitializer */
#define SPI2_RST  ((0x4<<24)|SYS_IPRST1_SPI2RST_Pos)    /*!<Reset SPI2 \hideinitializer */
#define SPI3_RST  ((0x4<<24)|SYS_IPRST1_SPI3RST_Pos)    /*!<Reset SPI3 \hideinitializer */
#define UART0_RST ((0x4<<24)|SYS_IPRST1_UART0RST_Pos)   /*!<Reset UART0 \hideinitializer */
#define UART1_RST ((0x4<<24)|SYS_IPRST1_UART1RST_Pos)   /*!<Reset UART1 \hideinitializer */
#define UART2_RST ((0x4<<24)|SYS_IPRST1_UART2RST_Pos)   /*!<Reset UART2 \hideinitializer */
#define UART3_RST ((0x4<<24)|SYS_IPRST1_UART3RST_Pos)   /*!<Reset UART3 \hideinitializer */
#define UART4_RST ((0x4<<24)|SYS_IPRST1_UART4RST_Pos)   /*!<Reset UART4 \hideinitializer */
#define UART5_RST ((0x4<<24)|SYS_IPRST1_UART5RST_Pos)   /*!<Reset UART5 \hideinitializer */
#define CAN0_RST  ((0x4<<24)|SYS_IPRST1_CAN0RST_Pos)    /*!<Reset CAN0 \hideinitializer */
#define CAN1_RST  ((0x4<<24)|SYS_IPRST1_CAN1RST_Pos)    /*!<Reset CAN1 \hideinitializer */
#define OTG_RST   ((0x4<<24)|SYS_IPRST1_OTGRST_Pos)     /*!<Reset OTG \hideinitializer */
#define USBD_RST  ((0x4<<24)|SYS_IPRST1_USBDRST_Pos)    /*!<Reset USBD \hideinitializer */
#define ADC_RST   ((0x4<<24)|SYS_IPRST1_ADCRST_Pos)     /*!<Reset ADC \hideinitializer */
#define I2S0_RST  ((0x4<<24)|SYS_IPRST1_I2S0RST_Pos)    /*!<Reset I2S0 \hideinitializer */
#define I2S1_RST  ((0x4<<24)|SYS_IPRST1_I2S1RST_Pos)    /*!<Reset I2S1 \hideinitializer */
#define PS2_RST   ((0x4<<24)|SYS_IPRST1_PS2RST_Pos)     /*!<Reset PS2 \hideinitializer */
#define SC0_RST   ((0x8<<24)|SYS_IPRST2_SC0RST_Pos)     /*!<Reset SC0 \hideinitializer */
#define SC1_RST   ((0x8<<24)|SYS_IPRST2_SC1RST_Pos)     /*!<Reset SC1 \hideinitializer */
#define SC2_RST   ((0x8<<24)|SYS_IPRST2_SC2RST_Pos)     /*!<Reset SC2 \hideinitializer */
#define SC3_RST   ((0x8<<24)|SYS_IPRST2_SC3RST_Pos)     /*!<Reset SC3 \hideinitializer */
#define SC4_RST   ((0x8<<24)|SYS_IPRST2_SC4RST_Pos)     /*!<Reset SC4 \hideinitializer */
#define SC5_RST   ((0x8<<24)|SYS_IPRST2_SC5RST_Pos)     /*!<Reset SC5 \hideinitializer */
#define I2C4_RST  ((0x8<<24)|SYS_IPRST2_I2C4RST_Pos)    /*!<Reset I2C4 \hideinitializer */
#define PWM0_RST  ((0x8<<24)|SYS_IPRST2_PWM0RST_Pos)    /*!<Reset PWM0 \hideinitializer */
#define PWM1_RST  ((0x8<<24)|SYS_IPRST2_PWM1RST_Pos)    /*!<Reset PWM1 \hideinitializer */
#define QEI0_RST  ((0x8<<24)|SYS_IPRST2_QEI0RST_Pos)    /*!<Reset QEI0 \hideinitializer */
#define QEI1_RST  ((0x8<<24)|SYS_IPRST2_QEI1RST_Pos)    /*!<Reset QEI1 \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  BODCTL constant definitions.                                                                            */
/*---------------------------------------------------------------------------------------------------------*/
#define  SYS_BODCTL_BODVL_2_2V        (0x0UL<<SYS_BODCTL_BODVL_Pos)        /*!<Threshold voltage of BOD is selected 2.2V \hideinitializer */
#define  SYS_BODCTL_BODVL_2_7V        (0x1UL<<SYS_BODCTL_BODVL_Pos)        /*!<Threshold voltage of BOD is selected 2.7V \hideinitializer */
#define  SYS_BODCTL_BODVL_3_8V        (0x2UL<<SYS_BODCTL_BODVL_Pos)        /*!<Threshold voltage of BOD is selected 3.82V \hideinitializer */
#define  SYS_BODCTL_BODVL_4_5V        (0x3UL<<SYS_BODCTL_BODVL_Pos)        /*!<Threshold voltage of BOD is selected 4.5V \hideinitializer */
#define  SYS_BODCTL_BODRSTEN          (0x1UL<<SYS_BODCTL_BODRSTEN_Pos)     /*!<Enable reset function of BOD. \hideinitializer */
#define  SYS_BODCTL_BODINTEN          (0x0UL<<SYS_BODCTL_BODRSTEN_Pos)     /*!<Enable interrupt function of BOD. \hideinitializer */
#define  SYS_BODCTL_BODLPM            (0x1UL<<SYS_BODCTL_BODLPM_Pos)       /*!<BOD work in low power mode. \hideinitializer */
#define  SYS_BODCTL_BODOUT            (0x1UL<<SYS_BODCTL_BODOUT_Pos)       /*!<Output of BOD IP. \hideinitializer */
#define  SYS_BODCTL_LVREN             (0x1UL<<SYS_BODCTL_LVREN_Pos)        /*!<Enable LVR function. \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  VREFCTL constant definitions. (Write-Protection Register)                                               */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_VREFCTL_VREF_2_65V         (0x03UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!<  VOUT= 2.56V  \hideinitializer */
#define SYS_VREFCTL_VREF_2_048V        (0x07UL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT= 2.048V  \hideinitializer */
#define SYS_VREFCTL_VREF_3_072V        (0x0BUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT= 3.072V  \hideinitializer */
#define SYS_VREFCTL_VREF_4_096V        (0x0FUL<<SYS_VREFCTL_VREFCTL_Pos)    /*!< VOUT= 4.096V  \hideinitializer */
#define SYS_VREFCTL_VREF_AVDD          (0x10UL<<SYS_VREFCTL_VREFCTL_Pos)   /*!< VOUT= AVDD  \hideinitializer */
#define SYS_VREFCTL_ADCMODESEL_EADC    (0x1UL<<SYS_VREFCTL_ADCMODESEL_Pos) /*!< EADC mode  \hideinitializer */
#define SYS_VREFCTL_ADCMODESEL_ADC     (0x0UL<<SYS_VREFCTL_ADCMODESEL_Pos) /*!< ADC mode  \hideinitializer */
#define SYS_VREFCTL_PWMSYNCMODE_EN     (0x1UL<<SYS_VREFCTL_PWMSYNCMODE_Pos)/*!<PWM SYNC MODE ENABLED, PWM engine clock is same as HCLK  \hideinitializer */

/*---------------------------------------------------------------------------------------------------------*/
/*  USBROLE constant definitions. (Write-Protection Register)                                                */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_USBPHY_USBROLE_OTG_V33_EN (0x1UL<<SYS_USBPHY_LDO33EN_Pos)   /*!<   USB LDO33 Enabled  \hideinitializer */
#define SYS_USBPHY_USBROLE_STD_USBD   (0x0UL<<SYS_USBPHY_USBROLE_Pos)   /*!<    Standard USB device  \hideinitializer */
#define SYS_USBPHY_USBROLE_STD_USBH   (0x1UL<<SYS_USBPHY_USBROLE_Pos)   /*!<   Standard USB host  \hideinitializer */
#define SYS_USBPHY_USBROLE_ID_DEPH    (0x2UL<<SYS_USBPHY_USBROLE_Pos)   /*!<   ID dependent device  \hideinitializer */
#define SYS_USBPHY_USBROLE_ON_THE_GO  (0x3UL<<SYS_USBPHY_USBROLE_Pos)   /*!<   On-The-Go device  \hideinitializer */



/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
/* How to use below #define?
Example 1: If user want to set PA.0 as SC0_CD in initial function,
           user can issue following command to achieve it.

           SYS->GPA_MFPL  = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA0MFP_Msk) ) | SYS_GPA_MFPL_PA0MFP_SC0_CD  ;

*/
//GPA_MFPL_PA0MFP
#define SYS_GPA_MFPL_PA0MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_TAMPER0     (0x1UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for TAMPER0    \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_SC0_CD      (0x2UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for SC0_CD   \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_CAN1_RXD    (0x3UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for CAN1_RXD  \hideinitializer */
#define SYS_GPA_MFPL_PA0MFP_INT0        (0x8UL<<SYS_GPA_MFPL_PA0MFP_Pos)           /*!< GPA_MFPL PA0 setting for INT0  \hideinitializer */

//GPA_MFPL_PA1MFP
#define SYS_GPA_MFPL_PA1MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for GPIO    \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_TAMPER1     (0x1UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for TAMPER1   \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_SC5_CD      (0x2UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for SC5_CD  \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_CAN1_TXD    (0x3UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for CAN1_TXD  \hideinitializer */
#define SYS_GPA_MFPL_PA1MFP_EBI_A22     (0x7UL<<SYS_GPA_MFPL_PA1MFP_Pos)            /*!< GPA_MFPL PA1 setting for EBI_A22 \hideinitializer */

//GPA_MFPL_PA2MFP
#define SYS_GPA_MFPL_PA2MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_SC2_DAT     (0x1UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for SC2_DAT    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_SPI3_MISO0  (0x2UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for SPI3_MISO0     \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_I2S0_MCLK   (0x3UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for I2S0_MCLK    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_BRAKE11     (0x4UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for BRAKE11    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_CAP_SFIELD  (0x5UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for CAP_SFIELD    \hideinitializer */
#define SYS_GPA_MFPL_PA2MFP_EBI_A12     (0x7UL<<SYS_GPA_MFPL_PA2MFP_Pos)           /*!< GPA_MFPL PA2 setting for EBI_A12    \hideinitializer */

//GPA_MFPL_PA3MFP
#define SYS_GPA_MFPL_PA3MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_SC2_CLK     (0x1UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for SC2_CLK      \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_SPI3_MOSI0  (0x2UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for SPI3_MOSI0      \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_I2S0_DO     (0x3UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for I2S0_D0     \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_BRAKE10     (0x4UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for BRAKE10    \hideinitializer */
#define SYS_GPA_MFPL_PA3MFP_EBI_A13     (0x7UL<<SYS_GPA_MFPL_PA3MFP_Pos)           /*!< GPA_MFPL PA3 setting for EBI_A13    \hideinitializer */

//GPA_MFPL_PA4MFP
#define SYS_GPA_MFPL_PA4MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA4MFP_Pos)           /*!< GPA_MFPL PA4 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_SC2_PWR     (0x1UL<<SYS_GPA_MFPL_PA4MFP_Pos)            /*!< GPA_MFPL PA4 setting for SC2_PWR     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_SPI3_CLK    (0x2UL<<SYS_GPA_MFPL_PA4MFP_Pos)            /*!< GPA_MFPL PA4 setting for SPI3_CLK    \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_I2S0_DI     (0x3UL<<SYS_GPA_MFPL_PA4MFP_Pos)            /*!< GPA_MFPL PA4 setting for I2S0_DI     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_QEI1_Z      (0x5UL<<SYS_GPA_MFPL_PA4MFP_Pos)            /*!< GPA_MFPL PA4 setting for QEI1_Z      \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_EBI_A14     (0x7UL<<SYS_GPA_MFPL_PA4MFP_Pos)            /*!< GPA_MFPL PA4 setting for EBI_A14     \hideinitializer */
#define SYS_GPA_MFPL_PA4MFP_ECAP1_IC2   (0x8UL<<SYS_GPA_MFPL_PA4MFP_Pos)             /*!< GPA_MFPL PA4 setting for ECAP1_IC2   \hideinitializer */

//GPA_MFPL_PA5MFP
#define SYS_GPA_MFPL_PA5MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA5MFP_Pos)           /*!< GPA_MFPL PA5 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_SC2_RST     (0x1UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for SC2_RST     \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_SPI3_SS0    (0x2UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for SPI3_SS0    \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_I2S0_BCLK   (0x3UL<<SYS_GPA_MFPL_PA5MFP_Pos)          /*!< GPA_MFPL PA5 setting for I2S0_BCLK    \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_PWM0_CH0    (0x4UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for PWM0 CH0     \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_QEI1_B      (0x5UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for QEI1_B    \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_EBI_A15     (0x7UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for EBI_A15    \hideinitializer */
#define SYS_GPA_MFPL_PA5MFP_ECAP1_IC1   (0x8UL<<SYS_GPA_MFPL_PA5MFP_Pos)            /*!< GPA_MFPL PA5 setting for ECAP1_IC1    \hideinitializer */

//GPA_MFPL_PA6MFP
#define SYS_GPA_MFPL_PA6MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_SC2_CD      (0x1UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for SC2_CD     \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_I2S0_LRCK   (0x3UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for I2S0_LRCK    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_PWM0_CH1    (0x4UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for PWM1 CH1    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_QEI1_A      (0x5UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for QEI1_A     \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_CAN1_TXD    (0x6UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for CAN1_TXD    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_EBI_A16     (0x7UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for EBI_A16    \hideinitializer */
#define SYS_GPA_MFPL_PA6MFP_ECAP1_IC0   (0x8UL<<SYS_GPA_MFPL_PA6MFP_Pos)           /*!< GPA_MFPL PA6 setting for ECAP1_IC0    \hideinitializer */

//GPA_MFPL_PA7MFP
#define SYS_GPA_MFPL_PA7MFP_GPIO        (0x0UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_SC0_CLK     (0x2UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for SC0_CLK    \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_SPI3_SS0    (0x3UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for SPI3_SS0     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_PWM1_CH3    (0x4UL<<SYS_GPA_MFPL_PA7MFP_Pos)          /*!< GPA_MFPL PA7 setting for PWM1 CH3     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_EPWM0_CH5   (0x5UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for EPWM0 CH5     \hideinitializer */
#define SYS_GPA_MFPL_PA7MFP_EBI_A17     (0x7UL<<SYS_GPA_MFPL_PA7MFP_Pos)           /*!< GPA_MFPL PA7 setting for EBI_A17     \hideinitializer */

//GPA_MFPL_PA8MFP
#define SYS_GPA_MFPH_PA8MFP_GPIO        (0x0UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_SC0_RST     (0x2UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for SC0_RST    \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_SPI3_CLK    (0x3UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for SPI3_CLK     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_PWM1_CH2    (0x4UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for PWM1 CH2    \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_EPWM0_CH4   (0x5UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for EPWM0_CH4     \hideinitializer */
#define SYS_GPA_MFPH_PA8MFP_EBI_A18     (0x7UL<<SYS_GPA_MFPH_PA8MFP_Pos)           /*!< GPA_MFPH PA8 setting for EBI_A18    \hideinitializer */

//GPA_MFPH_PA9MFP
#define SYS_GPA_MFPH_PA9MFP_GPIO        (0x0UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for GPIO     \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_SC0_PWR     (0x2UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for SC0_PWR    \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_SPI3_MISO0  (0x3UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for SPI3_MISO0     \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_PWM1_CH1    (0x4UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for PWM1 CH1    \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_EPWM0_CH3   (0x5UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for EPWM0 CH3     \hideinitializer */
#define SYS_GPA_MFPH_PA9MFP_EBI_A19     (0x7UL<<SYS_GPA_MFPH_PA9MFP_Pos)           /*!< GPA_MFPH PA9 setting for EBI_A19    \hideinitializer */

//GPA_MFPH_PA10MFP
#define SYS_GPA_MFPH_PA10MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_SC0_DAT    (0x2UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for SC0_DAT  \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_SPI3_MOSI0 (0x3UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for SPI3_MOSI0   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_PWM1_CH0   (0x4UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for PWM1_CH0  \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_EPWM0_CH2  (0x5UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for EPWM0_CH2   \hideinitializer */
#define SYS_GPA_MFPH_PA10MFP_EBI_A20    (0x7UL<<SYS_GPA_MFPH_PA10MFP_Pos)           /*!< GPA_MFPH PA10 setting for EBI_A20  \hideinitializer */

//GPA_MFPH_PA11MFP
#define SYS_GPA_MFPH_PA11MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_UART0_RTS    (0x1UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for UART0_RTS   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_SPI3_MISO1 (0x3UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for SPI3_MISO1   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_PWM0_CH5   (0x4UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for PWM0_CH5   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_EPWM0_CH1  (0x5UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for EPWM0_CH1   \hideinitializer */
#define SYS_GPA_MFPH_PA11MFP_EBI_AD0    (0x7UL<<SYS_GPA_MFPH_PA11MFP_Pos)           /*!< GPA_MFPH PA11 setting for EBI_AD0   \hideinitializer */

//GPA_MFPH_PA12MFP
#define SYS_GPA_MFPH_PA12MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_UART0_CTS    (0x1UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for UART0_CTS   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_SPI3_MOSI1 (0x3UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for SPI3_MOSI1   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_PWM0_CH4   (0x4UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for PWM0_CH4   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_EPWM0_CH0  (0x5UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for EPWM0_CH0   \hideinitializer */
#define SYS_GPA_MFPH_PA12MFP_EBI_AD1    (0x7UL<<SYS_GPA_MFPH_PA12MFP_Pos)           /*!< GPA_MFPH PA12 setting for EBI_AD1   \hideinitializer */

//GPA_MFPH_PA13MFP
#define SYS_GPA_MFPH_PA13MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_UART0_RXD    (0x1UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for UART0_RXD   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_SC3_DAT    (0x3UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for SC3_DAT   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_PWM1_CH4   (0x4UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for PWM1_CH4   \hideinitializer */
#define SYS_GPA_MFPH_PA13MFP_EBI_AD2    (0x7UL<<SYS_GPA_MFPH_PA13MFP_Pos)           /*!< GPA_MFPH PA13 setting for EBI_AD2   \hideinitializer */

//GPA_MFPH_PA14MFP
#define SYS_GPA_MFPH_PA14MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_UART0_TXD    (0x1UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for UART0_TXD   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_SC3_CLK    (0x3UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for SC3_CLK   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_PWM1_CH5   (0x4UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for PWM1_CH5   \hideinitializer */
#define SYS_GPA_MFPH_PA14MFP_EBI_AD3    (0x7UL<<SYS_GPA_MFPH_PA14MFP_Pos)           /*!< GPA_MFPH PA14 setting for EBI_AD3   \hideinitializer */
//GPA_MFPH_PA15MFP
#define SYS_GPA_MFPH_PA15MFP_GPIO       (0x0UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for GPIO   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_SC3_PWR    (0x1UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for SC3_PWR   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_UART2_RTS    (0x2UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for UART2_RTS   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_I2C0_SCL   (0x4UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for I2C0_SCL   \hideinitializer */
#define SYS_GPA_MFPH_PA15MFP_EBI_A21    (0x7UL<<SYS_GPA_MFPH_PA15MFP_Pos)           /*!< GPA_MFPH PA15 setting for EBI_A21   \hideinitializer */


//GPB_MFPL_PB0MFP
#define SYS_GPB_MFPL_PB0MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_USB0_OTG5V_ST  (0x1UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for USB0_OTG5V_ST    \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_I2C4_SCL       (0x2UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for I2C4_SCL     \hideinitializer */
#define SYS_GPB_MFPL_PB0MFP_INT1           (0x8UL<<SYS_GPB_MFPL_PB0MFP_Pos)           /*!< GPB_MFPL PB0 setting for INT1     \hideinitializer */

//GPB_MFPL_PB1MFP
#define SYS_GPB_MFPL_PB1MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_USB0_OTG5V_EN  (0x1UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for USB0_OTG5V_EN    \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_I2C4_SDA       (0x2UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for I2C4_SDA     \hideinitializer */
#define SYS_GPB_MFPL_PB1MFP_TM1_CNT_OUT    (0x3UL<<SYS_GPB_MFPL_PB1MFP_Pos)           /*!< GPB_MFPL PB1 setting for TM1_CNT_OUT    \hideinitializer */

//GPB_MFPL_PB2MFP
#define SYS_GPB_MFPL_PB2MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_UART1_RXD      (0x1UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for UART1_RXD    \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_SPI2_SS0       (0x2UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for SPI2_SS0     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_USB1_D_N       (0x3UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for USB1_D_N     \hideinitializer */
#define SYS_GPB_MFPL_PB2MFP_EBI_AD4        (0x7UL<<SYS_GPB_MFPL_PB2MFP_Pos)           /*!< GPB_MFPL PB2 setting for EBI_AD4    \hideinitializer */

//GPB_MFPL_PB3MFP
#define SYS_GPB_MFPL_PB3MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_UART1_TXD        (0x1UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for UART1_TXD    \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_SPI2_CLK       (0x2UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for SPI2_CLK     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_USB1_D_P       (0x3UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for USB1_D_P     \hideinitializer */
#define SYS_GPB_MFPL_PB3MFP_EBI_AD5        (0x7UL<<SYS_GPB_MFPL_PB3MFP_Pos)           /*!< GPB_MFPL PB3 setting for EBI_AD5    \hideinitializer */

//GPB_MFPL_PB4MFP
#define SYS_GPB_MFPL_PB4MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_UART1_RTS      (0x1UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for UART1_RTS    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_SPI2_MISO0     (0x2UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for SPI2_MISO0     \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_UART4_RXD      (0x3UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for UART4_RXD    \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_TM0_CNT_OUT    (0x4UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for TM0_CNT_OUT      \hideinitializer */
#define SYS_GPB_MFPL_PB4MFP_EBI_AD6        (0x7UL<<SYS_GPB_MFPL_PB4MFP_Pos)           /*!< GPB_MFPL PB4 setting for EBI_AD6    \hideinitializer */

//GPB_MFPL_PB5MFP
#define SYS_GPB_MFPL_PB5MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_UART1_CTS      (0x1UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for UART1_CTS    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_SPI2_MOSI0     (0x2UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for SPI2_MOSI0     \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_UART4_TXD      (0x3UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for UART4_TXD    \hideinitializer */
#define SYS_GPB_MFPL_PB5MFP_EBI_AD7        (0x7UL<<SYS_GPB_MFPL_PB5MFP_Pos)           /*!< GPB_MFPL PB5 setting for EBI_AD7    \hideinitializer */

//GPB_MFPL_PB6MFP
#define SYS_GPB_MFPL_PB6MFP_GPIO           (0x0UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_I2C2_SCL       (0x1UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for I2C2_SCL     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_BRAKE01        (0x2UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for BRAKE01      \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_UART4_RTS      (0x3UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for UART4_RTS    \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_PWM1_CH4       (0x4UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for PWM1_CH4     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_EPWM1_CH0      (0x5UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for EPWM1_CH0     \hideinitializer */
#define SYS_GPB_MFPL_PB6MFP_EBI_AD8        (0x7UL<<SYS_GPB_MFPL_PB6MFP_Pos)           /*!< GPB_MFPL PB6 setting for EBI_AD8    \hideinitializer */

//GPB_MFPL_PB7MFP
#define SYS_GPB_MFPL_PB7MFP_GPIO            (0x0UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_I2C2_SDA        (0x1UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for I2C2_SDA     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_BRAKE00         (0x2UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for BRAKE00    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_UART4_CTS       (0x3UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for UART4_CTS    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_PWM1_CH5        (0x4UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for PWM1_CH5    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_EPWM1_CH1       (0x5UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for EPWM1_CH1     \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_ETM_TRACE_DATA3 (0x6UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for ETM_TRACE_DATA3    \hideinitializer */
#define SYS_GPB_MFPL_PB7MFP_EBI_AD9         (0x7UL<<SYS_GPB_MFPL_PB7MFP_Pos)           /*!< GPB_MFPL PB7 setting for EBI_AD9    \hideinitializer */

//GPB_MFPL_PB8MFP
#define SYS_GPB_MFPH_PB8MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for GPIO     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_UART5_CTS       (0x1UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for UART5_CTS     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_EPWM1_CH2       (0x5UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for EPWM1_CH2    \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_ETM_TRACE_DATA2 (0x6UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for ETM_TRACE_DATA2     \hideinitializer */
#define SYS_GPB_MFPH_PB8MFP_EBI_AD10        (0x7UL<<SYS_GPB_MFPH_PB8MFP_Pos)           /*!< GPB_MFPH PB8 setting for EBI_AD10    \hideinitializer */

//GPB_MFPH_PB9MFP
#define SYS_GPB_MFPH_PB9MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for GPIO    \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_UART5_RTS       (0x1UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for UART5_RTS    \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_EPWM1_CH3       (0x5UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for EPWM1_CH3     \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_ETM_TRACE_DATA1 (0x6UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for ETM_TRACE_DATA1      \hideinitializer */
#define SYS_GPB_MFPH_PB9MFP_EBI_AD11        (0x7UL<<SYS_GPB_MFPH_PB9MFP_Pos)           /*!< GPB_MFPH PB9 setting for EBI_AD11     \hideinitializer */

//GPB_MFPH_PB10MFP
#define SYS_GPB_MFPH_PB10MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_UART5_TXD       (0x1UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for UART5_TXD  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_EPWM1_CH4       (0x5UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for EPWM1_CH4   \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_ETM_TRACE_DATA0 (0x6UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for ETM_TRACE_DATA0  \hideinitializer */
#define SYS_GPB_MFPH_PB10MFP_EBI_AD12        (0x7UL<<SYS_GPB_MFPH_PB10MFP_Pos)           /*!< GPB_MFPH PB10 setting for EBI_AD12   \hideinitializer */

//GPB_MFPH_PB11MFP
#define SYS_GPB_MFPH_PB11MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_UART5_RXD       (0x1UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for UART5_RXD   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_EPWM1_CH5       (0x5UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for EPWM1_CH5   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_ETM_TRACE_CLK   (0x6UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for ETM_TRACE_CLK   \hideinitializer */
#define SYS_GPB_MFPH_PB11MFP_EBI_AD13        (0x7UL<<SYS_GPB_MFPH_PB11MFP_Pos)           /*!< GPB_MFPH PB11 setting for EBI_AD13   \hideinitializer */

//GPB_MFPH_PB12MFP
#define SYS_GPB_MFPH_PB12MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_UART4_RTS       (0x1UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for UART4_RTS   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_SPI2_MISO1      (0x2UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for _SPI2_MISO1  \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_CAN0_RXD        (0x3UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for CAN0_RXD   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_EMAC_MII_MDC    (0x6UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for EMAC_MII_MDC   \hideinitializer */
#define SYS_GPB_MFPH_PB12MFP_EBI_AD14        (0x7UL<<SYS_GPB_MFPH_PB12MFP_Pos)           /*!< GPB_MFPH PB12 setting for EBI_AD4  \hideinitializer */

//GPB_MFPH_PB13MFP
#define SYS_GPB_MFPH_PB13MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_UART4_CTS       (0x1UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for UART4_CTS   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_SPI2_MOSI1      (0x2UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for SPI2_MOSI1   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_CAN0_TXD        (0x3UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for CAN0_TXD   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_EMAC_MII_MDIO   (0x6UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for EMAC_MII_MDIO   \hideinitializer */
#define SYS_GPB_MFPH_PB13MFP_EBI_AD15        (0x7UL<<SYS_GPB_MFPH_PB13MFP_Pos)           /*!< GPB_MFPH PB13 setting for EBI_AD15   \hideinitializer */

//GPB_MFPH_PB14MFP
#define SYS_GPB_MFPH_PB14MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_I2S1_MCLK       (0x1UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for I2S1_MCLK   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_SC1_RST         (0x2UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for SC1_RST   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_BRAKE01         (0x4UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for BRAKE01   \hideinitializer */
#define SYS_GPB_MFPH_PB14MFP_EMAC_MII_MDC    (0x6UL<<SYS_GPB_MFPH_PB14MFP_Pos)           /*!< GPB_MFPH PB14 setting for EMAC_MII_MDC   \hideinitializer */

//GPB_MFPH_PB15MFP
#define SYS_GPB_MFPH_PB15MFP_GPIO            (0x0UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for GPIO   \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_I2S1_DO         (0x1UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for I2S1_DO  \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_SC1_DAT         (0x2UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for SC1_DAT  \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_BRAKE00         (0x4UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for BRAKE00   \hideinitializer */
#define SYS_GPB_MFPH_PB15MFP_EMAC_MII_MDIO   (0x6UL<<SYS_GPB_MFPH_PB15MFP_Pos)           /*!< GPA_MFPH PB15 setting for EMAC_MII_MDIO  \hideinitializer */


//GPC_MFPL_PC0MFP
#define SYS_GPC_MFPL_PC0MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_I2S1_DI          (0x1UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for I2S1_D1    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_SC1_DAT          (0x2UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for SC1_DAT    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_UART4_RXD        (0x3UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for UART4_RXD    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_EMAC_REFCLK      (0x6UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for EMAC_REFCLK    \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_EBI_MCLK         (0x7UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for EBI_MCLK     \hideinitializer */
#define SYS_GPC_MFPL_PC0MFP_INT2             (0x8UL<<SYS_GPC_MFPL_PC0MFP_Pos)           /*!< GPC_MFPL PC0 setting for INT2     \hideinitializer */


//GPC_MFPL_PC1MFP
#define SYS_GPC_MFPL_PC1MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_I2S1_BCLK        (0x1UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for I2S1_BCLK    \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_SC1_CLK          (0x2UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for SC1_CLK    \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_UART4_TXD        (0x3UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for UART4_TXD      \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_TM3_CNT_OUT      (0x5UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for TM3_CNT_OUT    \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_EMAC_MII_RXERR   (0x6UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for EMAC_MII_RXERR     \hideinitializer */
#define SYS_GPC_MFPL_PC1MFP_EBI_AD13         (0x7UL<<SYS_GPC_MFPL_PC1MFP_Pos)           /*!< GPC_MFPL PC1 setting for EBI_AD13     \hideinitializer */

//GPC_MFPL_PC2MFP
#define SYS_GPC_MFPL_PC2MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_I2S1_LRCK        (0x1UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for I2S1_LRCK    \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_SC1_PWR          (0x2UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for SC1_PWR    \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_UART4_RTS        (0x3UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for UART4_RTS    \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_SPI0_SS0         (0x4UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for SPI0_SS0     \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_EMAC_MII_RXDV    (0x6UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for EMAC_MII_RXDV    \hideinitializer */
#define SYS_GPC_MFPL_PC2MFP_EBI_AD12         (0x7UL<<SYS_GPC_MFPL_PC2MFP_Pos)           /*!< GPC_MFPL PC2 setting for EBI_AD12     \hideinitializer */

//GPC_MFPL_PC3MFP
#define SYS_GPC_MFPL_PC3MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_I2S1_MCLK        (0x1UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for I2S1_MCLK    \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_SC1_CD           (0x2UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for SC1_CD     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_UART4_CTS        (0x3UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for UART4_CTS    \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_SPI0_MISO1       (0x4UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for SPI0_MISO1     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_QEI0_Z           (0x5UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for QEI0_Z     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_EMAC_MII_RXD1    (0x6UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for EMAC_MII_RXD1    \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_EBI_AD11         (0x7UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for EBI_AD11     \hideinitializer */
#define SYS_GPC_MFPL_PC3MFP_ECAP0_IC2        (0x8UL<<SYS_GPC_MFPL_PC3MFP_Pos)           /*!< GPC_MFPL PC3 setting for ECAP0_IC2    \hideinitializer */

//GPC_MFPL_PC4MFP
#define SYS_GPC_MFPL_PC4MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_I2S1_DO          (0x1UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for I2S1_DO    \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_SC1_RST          (0x2UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for SC1_RST    \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_SPI0_MOSI1       (0x4UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for SPI0_MOSI1     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_QEI0_B           (0x5UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for QEI0_B     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_EMAC_MII_RXD0    (0x6UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for EMAC_MII_RXD0    \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_EBI_AD10         (0x7UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for EBI_AD10     \hideinitializer */
#define SYS_GPC_MFPL_PC4MFP_ECAP0_IC1        (0x8UL<<SYS_GPC_MFPL_PC4MFP_Pos)           /*!< GPC_MFPL PC4 setting for ECAP0_IC1    \hideinitializer */

//GPC_MFPL_PC5MFP
#define SYS_GPC_MFPL_PC5MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_CLK_O            (0x1UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for CLK_O    \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_QEI0_A           (0x5UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for QEI0_A     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_EMAC_MII_RXCLK   (0x6UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for EMAC_MII_RXCLK     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_EBI_MCLK         (0x7UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for EBI_MCLK     \hideinitializer */
#define SYS_GPC_MFPL_PC5MFP_ECAP0_IC0        (0x8UL<<SYS_GPC_MFPL_PC5MFP_Pos)           /*!< GPC_MFPL PC5 setting for ECAP0_IC0    \hideinitializer */

//GPC_MFPL_PC6MFP
#define SYS_GPC_MFPL_PC6MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_TM2_EXT          (0x1UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for TM2_EXT    \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_SPI0_MISO0       (0x4UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for SPI0_MISO0     \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_TM2_CNT_OUT      (0x5UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for TM2_CNT_OUT    \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_EMAC_MII_TXD0    (0x6UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for EMAC_MII_TXD0    \hideinitializer */
#define SYS_GPC_MFPL_PC6MFP_EBI_AD9          (0x7UL<<SYS_GPC_MFPL_PC6MFP_Pos)           /*!< GPC_MFPL PC6 setting for EBI_AD9    \hideinitializer */

//GPC_MFPL_PC7MFP
#define SYS_GPC_MFPL_PC7MFP_GPIO             (0x0UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_TM1_EXT          (0x1UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for TM1_EXT    \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_SPI0_MOSI0       (0x4UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for SPI0_MOSI0     \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_EMAC_MII_TXD1    (0x6UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for EMAC_MII_TXD1    \hideinitializer */
#define SYS_GPC_MFPL_PC7MFP_EBI_AD8          (0x7UL<<SYS_GPC_MFPL_PC7MFP_Pos)           /*!< GPC_MFPL PC7 setting for EBI_AD8    \hideinitializer */

//GPC_MFPL_PC8MFP
#define SYS_GPC_MFPH_PC8MFP_GPIO             (0x0UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_TM0_EXT          (0x1UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for TM0_EXT    \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_SPI0_CLK         (0x4UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for SPI0_CLK     \hideinitializer */
#define SYS_GPC_MFPH_PC8MFP_EMAC_MII_TXEN    (0x6UL<<SYS_GPC_MFPH_PC8MFP_Pos)           /*!< GPC_MFPH PC8 setting for EMAC_MII_TXEN    \hideinitializer */

//GPC_MFPH_PC9MFP
#define SYS_GPC_MFPH_PC9MFP_GPIO             (0x0UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for GPIO     \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_STADC            (0x1UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for STADC    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_UART2_CTS        (0x2UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for UART2_CTS    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_SC3_RST          (0x3UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for SC3_RST    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_I2C0_SDA         (0x4UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for I2C0_SDA     \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_CAP_DATA1        (0x5UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for CAP_DATA1    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_I2C3_SCL         (0x6UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for I2C3_SCL     \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_EBI_A22          (0x7UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for EBI_A22    \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_SD1_DAT0         (0x8UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for SD1_DAT0     \hideinitializer */
#define SYS_GPC_MFPH_PC9MFP_EBI_A6           (0x9UL<<SYS_GPC_MFPH_PC9MFP_Pos)           /*!< GPC_MFPH PC9 setting for EBI_A6     \hideinitializer */
//GPC_MFPH_PC10MFP
#define SYS_GPC_MFPH_PC10MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_SC3_CD          (0x1UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for SC3_CD   \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_UART2_RXD       (0x2UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for UART2_RXD  \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_PWM0_CH2        (0x4UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for PWM0_CH2  \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_EBI_A23         (0x6UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for EBI_A23  \hideinitializer */
#define SYS_GPC_MFPH_PC10MFP_EBI_AD2         (0x7UL<<SYS_GPC_MFPH_PC10MFP_Pos)           /*!< GPC_MFPH PC10 setting for EBI_AD2  \hideinitializer */

//GPC_MFPH_PC11MFP
#define SYS_GPC_MFPH_PC11MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_UART2_TXD       (0x2UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for UART2_TXD   \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_PWM0_CH3        (0x4UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for PWM0_CH3   \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_EBI_A24         (0x6UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for EBI_A24   \hideinitializer */
#define SYS_GPC_MFPH_PC11MFP_EBI_AD3         (0x7UL<<SYS_GPC_MFPH_PC11MFP_Pos)           /*!< GPC_MFPH PC11 setting for EBI_AD3   \hideinitializer */

//GPC_MFPH_PC12MFP
#define SYS_GPC_MFPH_PC12MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_SPI1_SS0        (0x1UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for SPI1_SS0   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_SC4_CD          (0x2UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for SC4_CD   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_SD1_CDn         (0x4UL<<SYS_GPC_MFPH_PC12MFP_Pos)          /*!< GPC_MFPH PC12 setting for SD1_CDn  \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_CAP_DATA7       (0x5UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for CAP_DATA7   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_ETM_TRACE_DATA3 (0x6UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for ETM_TRACE_DATA3   \hideinitializer */
#define SYS_GPC_MFPH_PC12MFP_EBI_A0          (0x7UL<<SYS_GPC_MFPH_PC12MFP_Pos)           /*!< GPC_MFPH PC12 setting for MFP_EBI_A0   \hideinitializer */

//GPC_MFPH_PC13MFP
#define SYS_GPC_MFPH_PC13MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_SPI1_MOSI1      (0x1UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for SPI1_MOSI1   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_SC4_RST         (0x2UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for SC4_RST   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_SD1_CMD         (0x4UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for SD1_CMD   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_CAP_DATA6       (0x5UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for CAP_DATA6   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_ETM_TRACE_DATA2 (0x6UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for ETM_TRACE_DATA2   \hideinitializer */
#define SYS_GPC_MFPH_PC13MFP_EBI_A1          (0x7UL<<SYS_GPC_MFPH_PC13MFP_Pos)           /*!< GPC_MFPH PC13 setting for EBI_A1   \hideinitializer */

//GPC_MFPH_PC14MFP
#define SYS_GPC_MFPH_PC14MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_SPI1_MISO1      (0x1UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for SPI1_MISO1   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_SC4_PWR         (0x2UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for SC4_PWR   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_TM3_EXT         (0x3UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for TM3_EXT   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_SD1_CLK         (0x4UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for SD1_CLK   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_CAP_DATA5       (0x5UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for CAP_DATA5   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_ETM_TRACE_DATA1 (0x6UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for ETM_TRACE_DATA1   \hideinitializer */
#define SYS_GPC_MFPH_PC14MFP_EBI_A2          (0x7UL<<SYS_GPC_MFPH_PC14MFP_Pos)           /*!< GPC_MFPH PC14 setting for EBI_A2   \hideinitializer */

//GPC_MFPH_PC15MFP
#define SYS_GPC_MFPH_PC15MFP_GPIO            (0x0UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for GPIO   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_SPI1_MOSI0      (0x1UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for SPI1_MOSI0   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_SC4_DAT         (0x2UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for SC4_DAT   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_SD1_DAT3        (0x4UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for SD1_DAT3   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_CAP_DATA4       (0x5UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for CAP_DATA4   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_ETM_TRACE_DATA0 (0x6UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for ETM_TRACE_DATA0   \hideinitializer */
#define SYS_GPC_MFPH_PC15MFP_EBI_A3          (0x7UL<<SYS_GPC_MFPH_PC15MFP_Pos)           /*!< GPC_MFPH PC15 setting for EBI_A3   \hideinitializer */

//GPD_MFPL_PD0MFP
#define SYS_GPD_MFPL_PD0MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_SPI1_MISO0       (0x1UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for SPI1_MISO0     \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_SC4_CLK          (0x2UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for SC4_CLK    \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_SD1_DAT2         (0x4UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for SD1_DAT2     \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_CAP_DATA3        (0x5UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for CAP_DATA3    \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_ETM_TRACE_CLK    (0x6UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for ETM_TRACE_CLK    \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_EBI_A4           (0x7UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for EBI_A4     \hideinitializer */
#define SYS_GPD_MFPL_PD0MFP_INT3             (0x8UL<<SYS_GPD_MFPL_PD0MFP_Pos)           /*!< GPD_MFPL PD0 setting for INT3     \hideinitializer */

//GPD_MFPL_PD1MFP
#define SYS_GPD_MFPL_PD1MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_SPI1_CLK         (0x1UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for SPI1_CLK     \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_TM0_CNT_OUT      (0x3UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for TM0_CNT_OUT      \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_SD1_DAT1         (0x4UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for SD1_DAT1     \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_CAP_DATA2        (0x5UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for CAP_DATA2    \hideinitializer */
#define SYS_GPD_MFPL_PD1MFP_EBI_A5           (0x7UL<<SYS_GPD_MFPL_PD1MFP_Pos)           /*!< GPD_MFPL PD1 setting for EBI_A5     \hideinitializer */

//GPD_MFPL_PD2MFP
#define SYS_GPD_MFPL_PD2MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_STADC            (0x1UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for STADC    \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_I2C3_SCL         (0x2UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for I2C3_SCL     \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_SD1_DAT0         (0x4UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for SD1_DAT0     \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_CAP_DATA1        (0x5UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for CAP_DATA1    \hideinitializer */
#define SYS_GPD_MFPL_PD2MFP_EBI_A6           (0x7UL<<SYS_GPD_MFPL_PD2MFP_Pos)           /*!< GPD_MFPL PD2 setting for EBI_A6     \hideinitializer */

//GPD_MFPL_PD3MFP
#define SYS_GPD_MFPL_PD3MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_SC5_CLK          (0x1UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for SC5_CLK    \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_I2C3_SDA         (0x2UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for I2C3_SDA     \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_ACMP2_O          (0x3UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for ACMP2_O    \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_SD0_CDn          (0x4UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for SD0_CDn    \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_CAP_DATA0        (0x5UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for CAP_DATA0    \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_JTAG_TDO         (0x6UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for JTAG_TDO     \hideinitializer */
#define SYS_GPD_MFPL_PD3MFP_EBI_A7           (0x7UL<<SYS_GPD_MFPL_PD3MFP_Pos)           /*!< GPD_MFPL PD3 setting for EBI_A7     \hideinitializer */

//GPD_MFPL_PD4MFP
#define SYS_GPD_MFPL_PD4MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_SC5_CD           (0x1UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for SC5_CD     \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_UART3_RXD        (0x2UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for UART3_RXD    \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_ACMP1_O          (0x3UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for ACMP1_O    \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_CAP_SCLK         (0x5UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for CAP_SCLK     \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_JTAG_TDI         (0x6UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for JTAG_TDI     \hideinitializer */
#define SYS_GPD_MFPL_PD4MFP_EBI_A8           (0x7UL<<SYS_GPD_MFPL_PD4MFP_Pos)           /*!< GPD_MFPL PD4 setting for EBI_A8     \hideinitializer */

//GPD_MFPL_PD5MFP
#define SYS_GPD_MFPL_PD5MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_SC5_RST          (0x1UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for SC5_RST      \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_UART3_TXD        (0x2UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for UART3_TXD    \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_CAP_VSYNC        (0x5UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for CAP_VSYNC    \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_JTAG_nTRST       (0x6UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for JTAG_nTRST     \hideinitializer */
#define SYS_GPD_MFPL_PD5MFP_EBI_A9           (0x7UL<<SYS_GPD_MFPL_PD5MFP_Pos)           /*!< GPD_MFPL PD5 setting for EBI_A9     \hideinitializer */

//GPD_MFPL_PD6MFP
#define SYS_GPD_MFPL_PD6MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_SC5_PWR          (0x1UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for SC5_PWR    \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_UART3_RTS        (0x2UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for UART3_RTS    \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_SD0_CMD          (0x4UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for SD0_CMD      \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_CAP_HSYNC        (0x5UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for CAP_HSYNC      \hideinitializer */
#define SYS_GPD_MFPL_PD6MFP_EBI_A10          (0x7UL<<SYS_GPD_MFPL_PD6MFP_Pos)           /*!< GPD_MFPL PD6 setting for EBI_A10    \hideinitializer */

//GPD_MFPL_PD7MFP
#define SYS_GPD_MFPL_PD7MFP_GPIO             (0x0UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_SC5_DAT          (0x1UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for SC5_DAT    \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_UART3_CTS        (0x2UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for UART3_CTS      \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_SD0_CLK          (0x4UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for SD0_CLK    \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_CAP_PIXCLK       (0x5UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for CAP_PIXCLK     \hideinitializer */
#define SYS_GPD_MFPL_PD7MFP_EBI_A11          (0x7UL<<SYS_GPD_MFPL_PD7MFP_Pos)           /*!< GPD_MFPL PD7 setting for EBI_A11    \hideinitializer */

//GPD_MFPL_PD8MFP
#define SYS_GPD_MFPH_PD8MFP_GPIO             (0x0UL<<SYS_GPD_MFPH_PD8MFP_Pos)           /*!< GPD_MFPH PD8 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPH_PD8MFP_SPI3_MISO1       (0x1UL<<SYS_GPD_MFPH_PD8MFP_Pos)           /*!< GPD_MFPH PD8 setting for SPI3_MISO1     \hideinitializer */
#define SYS_GPD_MFPH_PD8MFP_I2C0_SCL         (0x2UL<<SYS_GPD_MFPH_PD8MFP_Pos)           /*!< GPD_MFPH PD8 setting for I2C0_SCL     \hideinitializer */

//GPD_MFPH_PD9MFP
#define SYS_GPD_MFPH_PD9MFP_GPIO             (0x0UL<<SYS_GPD_MFPH_PD9MFP_Pos)           /*!< GPD_MFPH PD9 setting for GPIO     \hideinitializer */
#define SYS_GPD_MFPH_PD9MFP_SPI3_MOSI1       (0x1UL<<SYS_GPD_MFPH_PD9MFP_Pos)           /*!< GPD_MFPH PD9 setting for SPI3_MOSI1     \hideinitializer */
#define SYS_GPD_MFPH_PD9MFP_I2C0_SDA         (0x2UL<<SYS_GPD_MFPH_PD9MFP_Pos)           /*!< GPD_MFPH PD9 setting for I2C0_SDA     \hideinitializer */

//GPD_MFPH_PD10MFP
#define SYS_GPD_MFPH_PD10MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD10MFP_Pos)           /*!< GPD_MFPH PD10 setting for GPIO   \hideinitializer */
#define SYS_GPD_MFPH_PD10MFP_SC3_DAT         (0x1UL<<SYS_GPD_MFPH_PD10MFP_Pos)           /*!< GPD_MFPH PD10 setting for SC3_DAT    \hideinitializer */
#define SYS_GPD_MFPH_PD10MFP_I2C4_SCL        (0x2UL<<SYS_GPD_MFPH_PD10MFP_Pos)           /*!< GPD_MFPH PD10 setting for I2C4_SCL     \hideinitializer */

//GPD_MFPH_PD11MFP
#define SYS_GPD_MFPH_PD11MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD11MFP_Pos)           /*!< GPD_MFPH PD11 setting for GPIO   \hideinitializer */
#define SYS_GPD_MFPH_PD11MFP_SC3_RST         (0x1UL<<SYS_GPD_MFPH_PD11MFP_Pos)           /*!< GPD_MFPH PD11 setting for SC3_RST   \hideinitializer */
#define SYS_GPD_MFPH_PD11MFP_TM3_CNT_OUT     (0x3UL<<SYS_GPD_MFPH_PD11MFP_Pos)           /*!< GPD_MFPH PD11 setting for TM3_CNT_OUT   \hideinitializer */

//GPD_MFPH_PD12MFP
#define SYS_GPD_MFPH_PD12MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD12MFP_Pos)           /*!< GPD_MFPH PD12 setting for GPIO   \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_SC3_CLK         (0x1UL<<SYS_GPD_MFPH_PD12MFP_Pos)           /*!< GPD_MFPH PD12 setting for SC3_CLK   \hideinitializer */
#define SYS_GPD_MFPH_PD12MFP_I2C4_SDA        (0x2UL<<SYS_GPD_MFPH_PD12MFP_Pos)           /*!< GPD_MFPH PD12 setting for I2C4_SDA   \hideinitializer */

//GPD_MFPH_PD13MFP
#define SYS_GPD_MFPH_PD13MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD13MFP_Pos)           /*!< GPD_MFPH PD13 setting for GPIO   \hideinitializer */
#define SYS_GPD_MFPH_PD13MFP_SPI1_SS0        (0x1UL<<SYS_GPD_MFPH_PD13MFP_Pos)           /*!< GPD_MFPH PD13 setting for SPI1_SS0   \hideinitializer */
#define SYS_GPD_MFPH_PD13MFP_UART5_CTS       (0x2UL<<SYS_GPD_MFPH_PD13MFP_Pos)           /*!< GPD_MFPH PD13 setting for UART5_CTS   \hideinitializer */
#define SYS_GPD_MFPH_PD13MFP_ECAP0_IC2       (0x3UL<<SYS_GPD_MFPH_PD13MFP_Pos)           /*!< GPD_MFPH PD13 setting for ECAP0_IC2   \hideinitializer */

//GPD_MFPH_PD14MFP
#define SYS_GPD_MFPH_PD14MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD14MFP_Pos)           /*!< GPD_MFPH PD14 setting for GPIO   \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_SPI1_CLK        (0x1UL<<SYS_GPD_MFPH_PD14MFP_Pos)           /*!< GPD_MFPH PD14 setting for SPI1_CLK   \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_UART5_RTS       (0x2UL<<SYS_GPD_MFPH_PD14MFP_Pos)           /*!< GPD_MFPH PD14 setting for UART5_RTS   \hideinitializer */
#define SYS_GPD_MFPH_PD14MFP_ECAP0_IC1       (0x3UL<<SYS_GPD_MFPH_PD14MFP_Pos)           /*!< GPD_MFPH PD14 setting for ECAP0_IC1   \hideinitializer */

//GPD_MFPH_PD15MFP
#define SYS_GPD_MFPH_PD15MFP_GPIO            (0x0UL<<SYS_GPD_MFPH_PD15MFP_Pos)           /*!< GPD_MFPH PD15 setting for GPIO  \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_SPI1_MISO0      (0x1UL<<SYS_GPD_MFPH_PD15MFP_Pos)           /*!< GPD_MFPH PD15 setting for SPI1_MISO0    \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_UART5_TXD       (0x2UL<<SYS_GPD_MFPH_PD15MFP_Pos)           /*!< GPD_MFPH PD15 setting for UART5_TXD  \hideinitializer */
#define SYS_GPD_MFPH_PD15MFP_ECAP0_IC0       (0x3UL<<SYS_GPD_MFPH_PD15MFP_Pos)           /*!< GPD_MFPH PD15 setting for ECAP0_IC0  \hideinitializer */

//GPE_MFPL_PE0MFP
#define SYS_GPE_MFPL_PE0MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE0MFP_Pos)           /*!< GPE_MFPL PE0 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_ADC0_0           (0x1UL<<SYS_GPE_MFPL_PE0MFP_Pos)           /*!< GPE_MFPL PE0 setting for ADC0_0     \hideinitializer */
#define SYS_GPE_MFPL_PE0MFP_INT4             (0x8UL<<SYS_GPE_MFPL_PE0MFP_Pos)           /*!< GPE_MFPL PE0 setting for INT4     \hideinitializer */

//GPE_MFPL_PE1MFP
#define SYS_GPE_MFPL_PE1MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE1MFP_Pos)           /*!< GPE_MFPL PE1 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_ADC0_1           (0x1UL<<SYS_GPE_MFPL_PE1MFP_Pos)           /*!< GPE_MFPL PE1 setting for ADC0_1     \hideinitializer */
#define SYS_GPE_MFPL_PE1MFP_TM2_CNT_OUT      (0x3UL<<SYS_GPE_MFPL_PE1MFP_Pos)           /*!< GPE_MFPL PE1 setting for TM2_CNT_OUT      \hideinitializer */

//GPE_MFPL_PE2MFP
#define SYS_GPE_MFPL_PE2MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE2MFP_Pos)           /*!< GPE_MFPL PE2 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_ADC0_2           (0x1UL<<SYS_GPE_MFPL_PE2MFP_Pos)           /*!< GPE_MFPL PE2 setting for ADC0_2     \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_ACMP0_O          (0x2UL<<SYS_GPE_MFPL_PE2MFP_Pos)           /*!< GPE_MFPL PE2 setting for ACMP0_O      \hideinitializer */
#define SYS_GPE_MFPL_PE2MFP_SPI0_MISO0       (0x3UL<<SYS_GPE_MFPL_PE2MFP_Pos)           /*!< GPE_MFPL PE2 setting for SPI0_MISO0     \hideinitializer */

//GPE_MFPL_PE3MFP
#define SYS_GPE_MFPL_PE3MFP_GPIO             (0x0UL<<SYS_GPE_MFPL_PE3MFP_Pos)           /*!< GPE_MFPL PE3 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_ADC0_3           (0x1UL<<SYS_GPE_MFPL_PE3MFP_Pos)           /*!< GPE_MFPL PE3 setting for ADC0_3     \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_ACMP0_P3         (0x2UL<<SYS_GPE_MFPL_PE3MFP_Pos)           /*!< GPE_MFPL PE3 setting for ACMP0_P3     \hideinitializer */
#define SYS_GPE_MFPL_PE3MFP_SPI0_MOSI0       (0x3UL<<SYS_GPE_MFPL_PE3MFP_Pos)           /*!< GPE_MFPL PE3 setting for SPI0_MOSI0     \hideinitializer */

//GPE_MFPL_PE4MFP
#define SYS_GPE_MFPL_PE4MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE4MFP_Pos)           /*!< GPE_MFPL PE4 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_ADC0_4          (0x1UL<<SYS_GPE_MFPL_PE4MFP_Pos)           /*!< GPE_MFPL PE4 setting for ADC0_4     \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_ACMP0_P2        (0x2UL<<SYS_GPE_MFPL_PE4MFP_Pos)           /*!< GPE_MFPL PE4 setting for ACMP0_P2     \hideinitializer */
#define SYS_GPE_MFPL_PE4MFP_SPI0_SS0        (0x3UL<<SYS_GPE_MFPL_PE4MFP_Pos)           /*!< GPE_MFPL PE4 setting for SPI0_SS0     \hideinitializer */

//GPE_MFPL_PE5MFP
#define SYS_GPE_MFPL_PE5MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE5MFP_Pos)           /*!< GPE_MFPL PE5 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_ADC0_5          (0x1UL<<SYS_GPE_MFPL_PE5MFP_Pos)           /*!< GPE_MFPL PE5 setting for ADC0_5     \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_ACMP0_P1        (0x2UL<<SYS_GPE_MFPL_PE5MFP_Pos)           /*!< GPE_MFPL PE5 setting for ACMP0_P1     \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_SPI0_CLK        (0x3UL<<SYS_GPE_MFPL_PE5MFP_Pos)           /*!< GPE_MFPL PE5 setting for SPI0_CLK     \hideinitializer */
#define SYS_GPE_MFPL_PE5MFP_SD0_CDn         (0x4UL<<SYS_GPE_MFPL_PE5MFP_Pos)           /*!< GPE_MFPL PE5 setting for SD0_CDn      \hideinitializer */

//GPE_MFPL_PE6MFP
#define SYS_GPE_MFPL_PE6MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE6MFP_Pos)           /*!< GPE_MFPL PE6 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_ADC0_6          (0x1UL<<SYS_GPE_MFPL_PE6MFP_Pos)            /*!< GPE_MFPL PE6 setting for ADC0_6    \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_ACMP0_P0        (0x2UL<<SYS_GPE_MFPL_PE6MFP_Pos)            /*!< GPE_MFPL PE6 setting for ACMP0_P0    \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_SPI0_MISO0      (0x3UL<<SYS_GPE_MFPL_PE6MFP_Pos)            /*!< GPE_MFPL PE6 setting for SPI0_MISO0    \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_SD0_CMD         (0x4UL<<SYS_GPE_MFPL_PE6MFP_Pos)            /*!< GPE_MFPL PE6 setting for SD0_CMD     \hideinitializer */
#define SYS_GPE_MFPL_PE6MFP_EBI_nWR         (0x7UL<<SYS_GPE_MFPL_PE6MFP_Pos)            /*!< GPE_MFPL PE6 setting for EBI_nWR     \hideinitializer */

//GPE_MFPL_PE7MFP
#define SYS_GPE_MFPL_PE7MFP_GPIO            (0x0UL<<SYS_GPE_MFPL_PE7MFP_Pos)            /*!< GPE_MFPL PE7 setting for GPIO    \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_ADC0_7          (0x1UL<<SYS_GPE_MFPL_PE7MFP_Pos)           /*!< GPE_MFPL PE7 setting for ADC0_7     \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_ACMP0_N         (0x2UL<<SYS_GPE_MFPL_PE7MFP_Pos)           /*!< GPE_MFPL PE7 setting for ACMP0_N      \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_SPI0_MOSI0      (0x3UL<<SYS_GPE_MFPL_PE7MFP_Pos)           /*!< GPE_MFPL PE7 setting for SPI0_MOSI0     \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_SD0_CLK         (0x4UL<<SYS_GPE_MFPL_PE7MFP_Pos)           /*!< GPE_MFPL PE7 setting for SD0_CLK      \hideinitializer */
#define SYS_GPE_MFPL_PE7MFP_EBI_nRD         (0x7UL<<SYS_GPE_MFPL_PE7MFP_Pos)           /*!< GPE_MFPL PE7 setting for _EBI_nRD     \hideinitializer */

//GPE_MFPL_PE8MFP
#define SYS_GPE_MFPH_PE8MFP_GPIO            (0x0UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_ADC0_8          (0x1UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for ADC0_8     \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_ADC1_0          (0x1UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for ADC1_0     \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_ACMP1_N         (0x2UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for ACMP1_N    \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_TM1_CNT_OUT     (0x3UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for TM1_CNT_OUT    \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_SD0_DAT3        (0x4UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for SD0_DAT3     \hideinitializer */
#define SYS_GPE_MFPH_PE8MFP_EBI_ALE         (0x7UL<<SYS_GPE_MFPH_PE8MFP_Pos)           /*!< GPE_MFPH PE8 setting for EBI_ALE    \hideinitializer */

//GPE_MFPH_PE9MFP
#define SYS_GPE_MFPH_PE9MFP_GPIO            (0x0UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for GPIO     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_ADC0_9          (0x1UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for ADC0_9     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_ADC1_1          (0x1UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for ADC1_1     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_ACMP1_P0        (0x2UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for ACMP1_P0     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_SD0_DAT2        (0x4UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for SD0_DAT2     \hideinitializer */
#define SYS_GPE_MFPH_PE9MFP_EBI_nWRH        (0x7UL<<SYS_GPE_MFPH_PE9MFP_Pos)           /*!< GPE_MFPH PE9 setting for EBI_nWRH     \hideinitializer */

//GPE_MFPH_PE10MFP
#define SYS_GPE_MFPH_PE10MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_ADC0_10        (0x1UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for ADC0_10     \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_ADC1_2         (0x1UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for ADC1_2   \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_ACMP1_P1       (0x2UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for ACMP1_P1   \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_SPI0_MISO1     (0x3UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for SPI0_MISO1   \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_SD0_DAT1       (0x4UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for SD0_DAT1     \hideinitializer */
#define SYS_GPE_MFPH_PE10MFP_EBI_nWRL       (0x7UL<<SYS_GPE_MFPH_PE10MFP_Pos)           /*!< GPE_MFPH PE10 setting for EBI_nWRL   \hideinitializer */

//GPE_MFPH_PE11MFP
#define SYS_GPE_MFPH_PE11MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_ADC0_11        (0x1UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for ADC0_11     \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_ADC1_3         (0x1UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for ADC1_3   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_ACMP1_P2       (0x2UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for ACMP1_P2   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_SPI0_MOSI1     (0x3UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for SPI0_MOSI1   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_SD0_DAT0       (0x4UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for SD0_DAT0   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_ACMP2_P3       (0x5UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for ACMP2_P3   \hideinitializer */
#define SYS_GPE_MFPH_PE11MFP_EBI_nCS0       (0x7UL<<SYS_GPE_MFPH_PE11MFP_Pos)           /*!< GPE_MFPH PE11 setting for EBI_nCS0   \hideinitializer */

//GPE_MFPH_PE12MFP
#define SYS_GPE_MFPH_PE12MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE12MFP_Pos)           /*!< GPE_MFPH PE12 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_ADC1_4         (0x1UL<<SYS_GPE_MFPH_PE12MFP_Pos)           /*!< GPE_MFPH PE12 setting for ADC1_4   \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_ACMP1_P3       (0x2UL<<SYS_GPE_MFPH_PE12MFP_Pos)           /*!< GPE_MFPH PE12 setting for ACMP1_P3   \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_ACMP2_P2       (0x3UL<<SYS_GPE_MFPH_PE12MFP_Pos)           /*!< GPE_MFPH PE12 setting for ACMP2_P2   \hideinitializer */
#define SYS_GPE_MFPH_PE12MFP_EBI_nCS1       (0x7UL<<SYS_GPE_MFPH_PE12MFP_Pos)           /*!< GPE_MFPH PE12 setting for EBI_nCS1   \hideinitializer */
//GPE_MFPH_PE13MFP
#define SYS_GPE_MFPH_PE13MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE13MFP_Pos)           /*!< GPE_MFPH PE13 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_ADC1_5         (0x1UL<<SYS_GPE_MFPH_PE13MFP_Pos)           /*!< GPE_MFPH PE13 setting for ADC1_5   \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_ACMP2_P1       (0x3UL<<SYS_GPE_MFPH_PE13MFP_Pos)           /*!< GPE_MFPH PE13 setting for ACMP2_P1   \hideinitializer */
#define SYS_GPE_MFPH_PE13MFP_EBI_nCS2       (0x7UL<<SYS_GPE_MFPH_PE13MFP_Pos)           /*!< GPE_MFPH PE13 setting for EBI_nCS2   \hideinitializer */

//GPE_MFPH_PE14MFP
#define SYS_GPE_MFPH_PE14MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE14MFP_Pos)           /*!< GPE_MFPH PE14 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_ADC1_6         (0x1UL<<SYS_GPE_MFPH_PE14MFP_Pos)           /*!< GPE_MFPH PE14 setting for ADC1_6   \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_ACMP2_P0       (0x3UL<<SYS_GPE_MFPH_PE14MFP_Pos)           /*!< GPE_MFPH PE14 setting for ACMP2_P0   \hideinitializer */
#define SYS_GPE_MFPH_PE14MFP_EBI_nCS3       (0x7UL<<SYS_GPE_MFPH_PE14MFP_Pos)           /*!< GPE_MFPH PE14 setting for EBI_nCS3   \hideinitializer */

//GPE_MFPH_PE15MFP
#define SYS_GPE_MFPH_PE15MFP_GPIO           (0x0UL<<SYS_GPE_MFPH_PE15MFP_Pos)           /*!< GPE_MFPH PE15 setting for GPIO   \hideinitializer */
#define SYS_GPE_MFPH_PE15MFP_ADC1_7         (0x1UL<<SYS_GPE_MFPH_PE15MFP_Pos)            /*!< GPE_MFPH PE15 setting for ADC1_7    \hideinitializer */
#define SYS_GPE_MFPH_PE15MFP_ACMP2_N        (0x3UL<<SYS_GPE_MFPH_PE15MFP_Pos)            /*!< GPE_MFPH PE15 setting for ACMP2_N  \hideinitializer */

//GPF_MFPL_PF0MFP
#define SYS_GPF_MFPL_PF0MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF0MFP_Pos)            /*!< GPF_MFPL PF0 setting for GPIO    \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_SPI1_MOSI0      (0x1UL<<SYS_GPF_MFPL_PF0MFP_Pos)           /*!< GPF_MFPL PF0 setting for SPI1_MOSI0     \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_UART5_RXD       (0x2UL<<SYS_GPF_MFPL_PF0MFP_Pos)           /*!< GPF_MFPL PF0 setting for UART5_RXD      \hideinitializer */
#define SYS_GPF_MFPL_PF0MFP_INT5            (0x8UL<<SYS_GPF_MFPL_PF0MFP_Pos)           /*!< GPF_MFPL PF0 setting for INT5     \hideinitializer */

//GPF_MFPL_PF1MFP
#define SYS_GPF_MFPL_PF1MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF1MFP_Pos)           /*!< GPF_MFPL PF1 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF1MFP_SPI2_MOSI1      (0x1UL<<SYS_GPF_MFPL_PF1MFP_Pos)           /*!< GPF_MFPL PF1 setting for SPI2_MOSI1     \hideinitializer */

//GPF_MFPL_PF2MFP
#define SYS_GPF_MFPL_PF2MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF2MFP_Pos)           /*!< GPF_MFPL PF2 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_SPI3_SS0        (0x1UL<<SYS_GPF_MFPL_PF2MFP_Pos)           /*!< GPF_MFPL PF2 setting for SPI3_SS0     \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_SD0_DAT3        (0x4UL<<SYS_GPF_MFPL_PF2MFP_Pos)           /*!< GPF_MFPL PF2 setting for SD0_DAT3     \hideinitializer */
#define SYS_GPF_MFPL_PF2MFP_EMAC_MII_RXD3   (0x6UL<<SYS_GPF_MFPL_PF2MFP_Pos)           /*!< GPF_MFPL PF2 setting for EMAC_MII_RXD3    \hideinitializer */

//GPF_MFPL_PF3MFP
#define SYS_GPF_MFPL_PF3MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF3MFP_Pos)           /*!< GPF_MFPL PF3 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_SPI3_CLK        (0x1UL<<SYS_GPF_MFPL_PF3MFP_Pos)           /*!< GPF_MFPL PF3 setting for SPI3_CLK     \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_SD0_DAT2        (0x4UL<<SYS_GPF_MFPL_PF3MFP_Pos)           /*!< GPF_MFPL PF3 setting for SD0_DAT2     \hideinitializer */
#define SYS_GPF_MFPL_PF3MFP_EMAC_MII_RXD2   (0x6UL<<SYS_GPF_MFPL_PF3MFP_Pos)          /*!< GPF_MFPL PF3 setting for EMAC_MII_RXD2     \hideinitializer */

//GPF_MFPL_PF4MFP
#define SYS_GPF_MFPL_PF4MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF4MFP_Pos)           /*!< GPF_MFPL PF4 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_SPI3_MISO0      (0x1UL<<SYS_GPF_MFPL_PF4MFP_Pos)           /*!< GPF_MFPL PF4 setting for SPI3_MISO0     \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_SD0_DAT1        (0x4UL<<SYS_GPF_MFPL_PF4MFP_Pos)           /*!< GPF_MFPL PF4 setting for SD0_DAT1     \hideinitializer */
#define SYS_GPF_MFPL_PF4MFP_EMAC_MII_COL0   (0x6UL<<SYS_GPF_MFPL_PF4MFP_Pos)           /*!< GPF_MFPL PF4 setting for EMAC_MII_COL0    \hideinitializer */

//GPF_MFPL_PF5MFP
#define SYS_GPF_MFPL_PF5MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF5MFP_Pos)           /*!< GPF_MFPL PF5 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_SPI3_MOSI0      (0x1UL<<SYS_GPF_MFPL_PF5MFP_Pos)           /*!< GPF_MFPL PF5 setting for SPI3_MOSI0     \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_SD0_DAT0        (0x4UL<<SYS_GPF_MFPL_PF5MFP_Pos)           /*!< GPF_MFPL PF5 setting for SD0_DAT0     \hideinitializer */
#define SYS_GPF_MFPL_PF5MFP_EMAC_MII_CRS    (0x6UL<<SYS_GPF_MFPL_PF5MFP_Pos)           /*!< GPF_MFPL PF5 setting for EMAC_MII_CRS     \hideinitializer */

//GPF_MFPL_PF6MFP
#define SYS_GPF_MFPL_PF6MFP_GPIO            (0x0UL<<SYS_GPF_MFPL_PF6MFP_Pos)           /*!< GPF_MFPL PF6 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_UART2_RXD       (0x1UL<<SYS_GPF_MFPL_PF6MFP_Pos)           /*!< GPF_MFPL PF6 setting for UART2_RXD    \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_SD0_CDn         (0x4UL<<SYS_GPF_MFPL_PF6MFP_Pos)           /*!< GPF_MFPL PF6 setting for SD0_CDn    \hideinitializer */
#define SYS_GPF_MFPL_PF6MFP_EMAC_MII_TXCLK  (0x6UL<<SYS_GPF_MFPL_PF6MFP_Pos)           /*!< GPF_MFPL PF6 setting for EMAC_MII_TXCLK     \hideinitializer */

//GPF_MFPL_PF7MFP
#define SYS_GPF_MFPL_PF7MFP_GPIO          (0x0UL<<SYS_GPF_MFPL_PF7MFP_Pos)           /*!< GPF_MFPL PF7 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_UART2_TXD     (0x1UL<<SYS_GPF_MFPL_PF7MFP_Pos)           /*!< GPF_MFPL PF7 setting for UART2_TXD    \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_SD0_CMD       (0x4UL<<SYS_GPF_MFPL_PF7MFP_Pos)           /*!< GPF_MFPL PF7 setting for SD0_CMD    \hideinitializer */
#define SYS_GPF_MFPL_PF7MFP_EMAC_MII_TXD3 (0x6UL<<SYS_GPF_MFPL_PF7MFP_Pos)           /*!< GPF_MFPL PF7 setting for EMAC_MII_TXD3    \hideinitializer */

//GPF_MFPL_PF8MFP
#define SYS_GPF_MFPH_PF8MFP_GPIO          (0x0UL<<SYS_GPF_MFPH_PF8MFP_Pos)           /*!< GPF_MFPH PF8 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_UART2_RTS     (0x1UL<<SYS_GPF_MFPH_PF8MFP_Pos)           /*!< GPF_MFPH PF8 setting for UART2_RTS    \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_SD0_CLK       (0x4UL<<SYS_GPF_MFPH_PF8MFP_Pos)           /*!< GPF_MFPH PF8 setting for SD0_CLK    \hideinitializer */
#define SYS_GPF_MFPH_PF8MFP_EMAC_MII_TXD2 (0x6UL<<SYS_GPF_MFPH_PF8MFP_Pos)           /*!< GPF_MFPH PF8 setting for EMAC_MII_TXD2    \hideinitializer */

//GPF_MFPH_PF9MFP
#define SYS_GPF_MFPH_PF9MFP_GPIO          (0x0UL<<SYS_GPF_MFPH_PF9MFP_Pos)           /*!< GPF_MFPH PF9 setting for GPIO     \hideinitializer */
#define SYS_GPF_MFPH_PF9MFP_OPA0_IN_P     (0x1UL<<SYS_GPF_MFPH_PF9MFP_Pos)           /*!< GPF_MFPH PF9 setting for OPA0_IN_P      \hideinitializer */
#define SYS_GPF_MFPH_PF9MFP_PWM0_CH0      (0x4UL<<SYS_GPF_MFPH_PF9MFP_Pos)           /*!< GPF_MFPH PF9 setting for PWM0_CH0      \hideinitializer */

//GPF_MFPH_PF10MFP
#define SYS_GPF_MFPH_PF10MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF10MFP_Pos)           /*!< GPF_MFPH PF10 setting for GPIO   \hideinitializer */
#define SYS_GPF_MFPH_PF10MFP_OPA0_IN_N    (0x1UL<<SYS_GPF_MFPH_PF10MFP_Pos)           /*!< GPF_MFPH PF10 setting for OPA0_IN_N    \hideinitializer */
#define SYS_GPF_MFPH_PF10MFP_PWM0_CH1     (0x4UL<<SYS_GPF_MFPH_PF10MFP_Pos)           /*!< GPF_MFPH PF10 setting for PWM0_CH1  \hideinitializer */

//GPF_MFPH_PF11MFP
#define SYS_GPF_MFPH_PF11MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF11MFP_Pos)           /*!< GPF_MFPH PF11 setting for GPIO   \hideinitializer */
#define SYS_GPF_MFPH_PF11MFP_OPA0_O       (0x1UL<<SYS_GPF_MFPH_PF11MFP_Pos)           /*!< GPF_MFPH PF11 setting for OPA0_O   \hideinitializer */
#define SYS_GPF_MFPH_PF11MFP_UART1_RTS    (0x2UL<<SYS_GPF_MFPH_PF11MFP_Pos)           /*!< GPF_MFPH PF11 setting for UART1_RTS   \hideinitializer */

//GPF_MFPH_PF12MFP
#define SYS_GPF_MFPH_PF12MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF12MFP_Pos)           /*!< GPF_MFPH PF12 setting for GPIO   \hideinitializer */
#define SYS_GPF_MFPH_PF12MFP_OPA1_IN_P    (0x1UL<<SYS_GPF_MFPH_PF12MFP_Pos)           /*!< GPF_MFPH PF12 setting for OPA1_IN_P   \hideinitializer */
#define SYS_GPF_MFPH_PF12MFP_UART1_CTS    (0x2UL<<SYS_GPF_MFPH_PF12MFP_Pos)           /*!< GPF_MFPH PF12 setting for UART1_CTS   \hideinitializer */
//GPF_MFPH_PF13MFP
#define SYS_GPF_MFPH_PF13MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF13MFP_Pos)           /*!< GPF_MFPH PF13 setting for GPIO   \hideinitializer */
#define SYS_GPF_MFPH_PF13MFP_OPA1_IN_N    (0x1UL<<SYS_GPF_MFPH_PF13MFP_Pos)            /*!< GPF_MFPH PF13 setting for OPA1_IN_N  \hideinitializer */
#define SYS_GPF_MFPH_PF13MFP_UART1_TXD    (0x2UL<<SYS_GPF_MFPH_PF13MFP_Pos)            /*!< GPF_MFPH PF13 setting for UART1_TXD    \hideinitializer */

//GPF_MFPH_PF14MFP
#define SYS_GPF_MFPH_PF14MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF14MFP_Pos)            /*!< GPF_MFPH PF14 setting for GPIO  \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_OPA1_O       (0x1UL<<SYS_GPF_MFPH_PF14MFP_Pos)           /*!< GPF_MFPH PF14 setting for OPA1_O   \hideinitializer */
#define SYS_GPF_MFPH_PF14MFP_UART1_RXD    (0x2UL<<SYS_GPF_MFPH_PF14MFP_Pos)           /*!< GPF_MFPH PF14 setting for UART1_RXD   \hideinitializer */

//GPF_MFPH_PF15MFP
#define SYS_GPF_MFPH_PF15MFP_GPIO         (0x0UL<<SYS_GPF_MFPH_PF15MFP_Pos)          /*!< GPF_MFPH PF15 setting for GPIO  \hideinitializer */
#define SYS_GPF_MFPH_PF15MFP_UART0_RTS    (0x1UL<<SYS_GPF_MFPH_PF15MFP_Pos)            /*!< GPF_MFPH PF15 setting for UART0_RTS  \hideinitializer */


//GPG_MFPL_PG0MFP
#define SYS_GPG_MFPL_PG0MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG0MFP_Pos)            /*!< GPG_MFPL PG0 setting for GPIO    \hideinitializer */
#define SYS_GPG_MFPL_PG0MFP_UART0_CTS     (0x1UL<<SYS_GPG_MFPL_PG0MFP_Pos)           /*!< GPG_MFPL PG0 setting for UART0_CTS    \hideinitializer */
#define SYS_GPG_MFPL_PG0MFP_INT6          (0x8UL<<SYS_GPG_MFPL_PG0MFP_Pos)           /*!< GPG_MFPL PG0 setting for INT6     \hideinitializer */

//GPG_MFPL_PG1MFP
#define SYS_GPG_MFPL_PG1MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG1MFP_Pos)           /*!< GPG_MFPL PG1 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG1MFP_UART0_RXD     (0x1UL<<SYS_GPG_MFPL_PG1MFP_Pos)           /*!< GPG_MFPL PG1 setting for UART0_RXD    \hideinitializer */

//GPG_MFPL_PG2MFP
#define SYS_GPG_MFPL_PG2MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG2MFP_Pos)           /*!< GPG_MFPL PG2 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG2MFP_UART0_TXD     (0x1UL<<SYS_GPG_MFPL_PG2MFP_Pos)           /*!< GPG_MFPL PG2 setting for UART0_TXD      \hideinitializer */

//GPG_MFPL_PG3MFP
#define SYS_GPG_MFPL_PG3MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG3MFP_Pos)           /*!< GPG_MFPL PG3 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_PS2_CLK       (0x1UL<<SYS_GPG_MFPL_PG3MFP_Pos)            /*!< GPG_MFPL PG3 setting for PS2_CLK     \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_I2S1_DO       (0x2UL<<SYS_GPG_MFPL_PG3MFP_Pos)            /*!< GPG_MFPL PG3 setting for I2S1_DO     \hideinitializer */
#define SYS_GPG_MFPL_PG3MFP_SC1_RST       (0x3UL<<SYS_GPG_MFPL_PG3MFP_Pos)            /*!< GPG_MFPL PG3 setting for SC1_RST     \hideinitializer */
//GPG_MFPL_PG4MFP
#define SYS_GPG_MFPL_PG4MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG4MFP_Pos)            /*!< GPG_MFPL PG4 setting for GPIO    \hideinitializer */
#define SYS_GPG_MFPL_PG4MFP_PS2_DAT       (0x1UL<<SYS_GPG_MFPL_PG4MFP_Pos)           /*!< GPG_MFPL PG4 setting for PS2_DAT      \hideinitializer */
#define SYS_GPG_MFPL_PG4MFP_I2S1_DI       (0x2UL<<SYS_GPG_MFPL_PG4MFP_Pos)           /*!< GPG_MFPL PG4 setting for I2S1_DI      \hideinitializer */
#define SYS_GPG_MFPL_PG4MFP_SC1_PWR       (0x3UL<<SYS_GPG_MFPL_PG4MFP_Pos)           /*!< GPG_MFPL PG4 setting for SC1_PWR      \hideinitializer */

//GPG_MFPL_PG5MFP
#define SYS_GPG_MFPL_PG5MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG5MFP_Pos)           /*!< GPG_MFPL PG5 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG5MFP_I2S1_BCLK     (0x2UL<<SYS_GPG_MFPL_PG5MFP_Pos)           /*!< GPG_MFPL PG5 setting for I2S1_BCLK      \hideinitializer */
#define SYS_GPG_MFPL_PG5MFP_SC1_DAT       (0x3UL<<SYS_GPG_MFPL_PG5MFP_Pos)           /*!< GPG_MFPL PG5 setting for SC1_DAT    \hideinitializer */
//GPG_MFPL_PG6MFP
#define SYS_GPG_MFPL_PG6MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG6MFP_Pos)           /*!< GPG_MFPL PG6 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG6MFP_I2S1_LRCK     (0x2UL<<SYS_GPG_MFPL_PG6MFP_Pos)           /*!< GPG_MFPL PG6 setting for I2S1_LRCK    \hideinitializer */
#define SYS_GPG_MFPL_PG6MFP_SC1_CLK       (0x3UL<<SYS_GPG_MFPL_PG6MFP_Pos)           /*!< GPG_MFPL PG6 setting for SC1_CLK    \hideinitializer */

//GPG_MFPL_PG7MFP
#define SYS_GPG_MFPL_PG7MFP_GPIO          (0x0UL<<SYS_GPG_MFPL_PG7MFP_Pos)           /*!< GPG_MFPL PG7 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPL_PG7MFP_SPI2_MISO0    (0x1UL<<SYS_GPG_MFPL_PG7MFP_Pos)           /*!< GPG_MFPL PG7 setting for SPI2_MISO0     \hideinitializer */
#define SYS_GPG_MFPL_PG7MFP_I2S1_MCLK     (0x2UL<<SYS_GPG_MFPL_PG7MFP_Pos)           /*!< GPG_MFPL PG7 setting for I2S1_MCLK    \hideinitializer */
#define SYS_GPG_MFPL_PG7MFP_SC1_CD        (0x3UL<<SYS_GPG_MFPL_PG7MFP_Pos)           /*!< GPG_MFPL PG7 setting for SC1_CD     \hideinitializer */
#define SYS_GPG_MFPL_PG7MFP_SC3_RST       (0x4UL<<SYS_GPG_MFPL_PG7MFP_Pos)           /*!< GPG_MFPL PG7 setting for SC3_RST      \hideinitializer */

//GPG_MFPL_PG8MFP
#define SYS_GPG_MFPH_PG8MFP_GPIO          (0x0UL<<SYS_GPG_MFPH_PG8MFP_Pos)           /*!< GPG_MFPH PG8 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPH_PG8MFP_SPI2_MOSI0    (0x1UL<<SYS_GPG_MFPH_PG8MFP_Pos)           /*!< GPG_MFPH PG8 setting for SPI2_MOSI0     \hideinitializer */
#define SYS_GPG_MFPH_PG8MFP_I2S1_DO       (0x2UL<<SYS_GPG_MFPH_PG8MFP_Pos)           /*!< GPG_MFPH PG8 setting for I2S1_DO    \hideinitializer */
#define SYS_GPG_MFPH_PG8MFP_UART4_RTS     (0x3UL<<SYS_GPG_MFPH_PG8MFP_Pos)           /*!< GPG_MFPH PG8 setting for UART4_RTS    \hideinitializer */
#define SYS_GPG_MFPH_PG8MFP_SC3_DAT       (0x4UL<<SYS_GPG_MFPH_PG8MFP_Pos)           /*!< GPG_MFPH PG8 setting for SC3_DAT    \hideinitializer */

//GPG_MFPH_PG9MFP
#define SYS_GPG_MFPH_PG9MFP_GPIO          (0x0UL<<SYS_GPG_MFPH_PG9MFP_Pos)           /*!< GPG_MFPH PG9 setting for GPIO     \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_SPI2_CLK      (0x1UL<<SYS_GPG_MFPH_PG9MFP_Pos)           /*!< GPG_MFPH PG9 setting for SPI2_CLK     \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_I2S1_DI       (0x2UL<<SYS_GPG_MFPH_PG9MFP_Pos)           /*!< GPG_MFPH PG9 setting for I2S1_DI    \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_UART4_CTS     (0x3UL<<SYS_GPG_MFPH_PG9MFP_Pos)           /*!< GPG_MFPH PG9 setting for UART4_CTS    \hideinitializer */
#define SYS_GPG_MFPH_PG9MFP_SC3_CLK       (0x4UL<<SYS_GPG_MFPH_PG9MFP_Pos)           /*!< GPG_MFPH PG9 setting for SC3_CLK      \hideinitializer */

//GPG_MFPH_PG10MFP
#define SYS_GPG_MFPH_PG10MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG10MFP_Pos)           /*!< GPG_MFPH PG10 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG10MFP_ICE_CLK      (0x1UL<<SYS_GPG_MFPH_PG10MFP_Pos)           /*!< GPG_MFPH PG10 setting for ICE_CLK    \hideinitializer */
#define SYS_GPG_MFPH_PG10MFP_JTAG_TCLK    (0x6UL<<SYS_GPG_MFPH_PG10MFP_Pos)           /*!< GPG_MFPH PG10 setting for JTAG_TCLK  \hideinitializer */

//GPG_MFPH_PG11MFP
#define SYS_GPG_MFPH_PG11MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG11MFP_Pos)           /*!< GPG_MFPH PG11 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG11MFP_ICE_DAT      (0x1UL<<SYS_GPG_MFPH_PG11MFP_Pos)           /*!< GPG_MFPH PG11 setting for ICE_DAT   \hideinitializer */
#define SYS_GPG_MFPH_PG11MFP_JTAG_TMS     (0x6UL<<SYS_GPG_MFPH_PG11MFP_Pos)           /*!< GPG_MFPH PG11 setting for JTAG_TMS   \hideinitializer */

//GPG_MFPH_PG12MFP
#define SYS_GPG_MFPH_PG12MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG12MFP_Pos)           /*!< GPG_MFPH PG12 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG12MFP_XT1_OUT      (0x1UL<<SYS_GPG_MFPH_PG12MFP_Pos)           /*!< GPG_MFPH PG12 setting for XT1_OUT   \hideinitializer */

//GPG_MFPH_PG13MFP
#define SYS_GPG_MFPH_PG13MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG13MFP_Pos)           /*!< GPG_MFPH PG13 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG13MFP_XT1_IN       (0x1UL<<SYS_GPG_MFPH_PG13MFP_Pos)           /*!< GPG_MFPH PG13 setting for XT1_IN   \hideinitializer */

//GPG_MFPH_PG14MFP
#define SYS_GPG_MFPH_PG14MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG14MFP_Pos)           /*!< GPG_MFPH PG14 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG14MFP_X32K_OUT     (0x1UL<<SYS_GPG_MFPH_PG14MFP_Pos)           /*!< GPG_MFPH PG14 setting for X32K_OUT   \hideinitializer */
#define SYS_GPG_MFPH_PG14MFP_I2C1_SDA     (0x3UL<<SYS_GPG_MFPH_PG14MFP_Pos)           /*!< GPG_MFPH PG14 setting for I2C1_SDA   \hideinitializer */

//GPG_MFPH_PG15MFP
#define SYS_GPG_MFPH_PG15MFP_GPIO         (0x0UL<<SYS_GPG_MFPH_PG15MFP_Pos)           /*!< GPG_MFPH PG15 setting for GPIO   \hideinitializer */
#define SYS_GPG_MFPH_PG15MFP_X32K_IN      (0x1UL<<SYS_GPG_MFPH_PG15MFP_Pos)           /*!< GPG_MFPH PG15 setting for X32K_IN   \hideinitializer */
#define SYS_GPG_MFPH_PG15MFP_I2C1_SCL     (0x3UL<<SYS_GPG_MFPH_PG15MFP_Pos)           /*!< GPG_MFPH PG15 setting for I2C1_SCL   \hideinitializer */


//GPH_MFPL_PH0MFP
#define SYS_GPH_MFPL_PH0MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH0MFP_Pos)           /*!< GPH_MFPL PH0 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH0MFP_I2C1_SCL      (0x1UL<<SYS_GPH_MFPL_PH0MFP_Pos)           /*!< GPH_MFPL PH0 setting for I2C1_SCL     \hideinitializer */
#define SYS_GPH_MFPL_PH0MFP_UART4_RXD     (0x2UL<<SYS_GPH_MFPL_PH0MFP_Pos)           /*!< GPH_MFPL PH0 setting for UART4_RXD    \hideinitializer */
#define SYS_GPH_MFPL_PH0MFP_CAN1_RXD      (0x3UL<<SYS_GPH_MFPL_PH0MFP_Pos)           /*!< GPH_MFPL PH0 setting for CAN1_RXD     \hideinitializer */
#define SYS_GPH_MFPL_PH0MFP_INT7          (0x8UL<<SYS_GPH_MFPL_PH0MFP_Pos)           /*!< GPH_MFPL PH0 setting for INT7     \hideinitializer */

//GPH_MFPL_PH1MFP
#define SYS_GPH_MFPL_PH1MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH1MFP_Pos)           /*!< GPH_MFPL PH1 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH1MFP_UART4_TXD     (0x1UL<<SYS_GPH_MFPL_PH1MFP_Pos)            /*!< GPH_MFPL PH1 setting for UART4_TXD     \hideinitializer */
#define SYS_GPH_MFPL_PH1MFP_I2C1_SDA      (0x2UL<<SYS_GPH_MFPL_PH1MFP_Pos)            /*!< GPH_MFPL PH1 setting for I2C1_SDA    \hideinitializer */
#define SYS_GPH_MFPL_PH1MFP_CAN1_TXD      (0x3UL<<SYS_GPH_MFPL_PH1MFP_Pos)            /*!< GPH_MFPL PH1 setting for CAN1_TXD    \hideinitializer */

//GPH_MFPL_PH2MFP
#define SYS_GPH_MFPL_PH2MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH2MFP_Pos)            /*!< GPH_MFPL PH2 setting for GPIO    \hideinitializer */
#define SYS_GPH_MFPL_PH2MFP_UART2_CTS     (0x1UL<<SYS_GPH_MFPL_PH2MFP_Pos)           /*!< GPH_MFPL PH2 setting for UART2_CTS    \hideinitializer */

//GPH_MFPL_PH3MFP
#define SYS_GPH_MFPL_PH3MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH3MFP_Pos)           /*!< GPH_MFPL PH3 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH3MFP_I2C3_SCL      (0x1UL<<SYS_GPH_MFPL_PH3MFP_Pos)           /*!< GPH_MFPL PH3 setting for I2C3_SCL     \hideinitializer */

//GPH_MFPL_PH4MFP
#define SYS_GPH_MFPL_PH4MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH4MFP_Pos)           /*!< GPH_MFPL PH4 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH4MFP_I2C3_SDA      (0x1UL<<SYS_GPH_MFPL_PH4MFP_Pos)           /*!< GPH_MFPL PH4 setting for I2C3_SDA     \hideinitializer */

//GPH_MFPL_PH5MFP
#define SYS_GPH_MFPL_PH5MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH5MFP_Pos)           /*!< GPH_MFPL PH5 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH5MFP_SPI2_SS0      (0x1UL<<SYS_GPH_MFPL_PH5MFP_Pos)           /*!< GPH_MFPL PH5 setting for SPI2_SS0     \hideinitializer */

//GPH_MFPL_PH6MFP
#define SYS_GPH_MFPL_PH6MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH6MFP_Pos)           /*!< GPH_MFPL PH6 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPL_PH6MFP_SPI2_CLK      (0x1UL<<SYS_GPH_MFPL_PH6MFP_Pos)            /*!< GPH_MFPL PH6 setting for SPI2_CLK    \hideinitializer */

//GPH_MFPL_PH7MFP
#define SYS_GPH_MFPL_PH7MFP_GPIO          (0x0UL<<SYS_GPH_MFPL_PH7MFP_Pos)            /*!< GPH_MFPL PH7 setting for GPIO    \hideinitializer */
#define SYS_GPH_MFPL_PH7MFP_SPI2_MISO0    (0x1UL<<SYS_GPH_MFPL_PH7MFP_Pos)            /*!< GPH_MFPL PH7 setting for SPI2_MISO0    \hideinitializer */

//GPH_MFPL_PH8MFP
#define SYS_GPH_MFPH_PH8MFP_GPIO          (0x0UL<<SYS_GPH_MFPH_PH8MFP_Pos)            /*!< GPH_MFPH PH8 setting for GPIO    \hideinitializer */
#define SYS_GPH_MFPH_PH8MFP_SPI2_MOSI0    (0x1UL<<SYS_GPH_MFPH_PH8MFP_Pos)           /*!< GPH_MFPH PH8 setting for SPI2_MOSI0     \hideinitializer */

//GPH_MFPH_PH9MFP
#define SYS_GPH_MFPH_PH9MFP_GPIO          (0x0UL<<SYS_GPH_MFPH_PH9MFP_Pos)           /*!< GPH_MFPH PH9 setting for GPIO     \hideinitializer */
#define SYS_GPH_MFPH_PH9MFP_SPI2_MISO1    (0x1UL<<SYS_GPH_MFPH_PH9MFP_Pos)           /*!< GPH_MFPH PH9 setting for SPI2_MISO1     \hideinitializer */

//GPH_MFPH_PH10MFP
#define SYS_GPH_MFPH_PH10MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH10MFP_Pos)           /*!< GPH_MFPH PH10 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH10MFP_SPI2_MOSI1   (0x1UL<<SYS_GPH_MFPH_PH10MFP_Pos)           /*!< GPH_MFPH PH10 setting for SPI2_MOSI1   \hideinitializer */

//GPH_MFPH_PH11MFP
#define SYS_GPH_MFPH_PH11MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH11MFP_Pos)           /*!< GPH_MFPH PH11 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH11MFP_UART3_RXD    (0x1UL<<SYS_GPH_MFPH_PH11MFP_Pos)           /*!< GPH_MFPH PH11 setting for UART3_RXD   \hideinitializer */

//GPH_MFPH_PH12MFP
#define SYS_GPH_MFPH_PH12MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH12MFP_Pos)           /*!< GPH_MFPH PH12 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH12MFP_UART3_TXD    (0x1UL<<SYS_GPH_MFPH_PH12MFP_Pos)           /*!< GPH_MFPH PH12 setting for UART3_TXD   \hideinitializer */

//GPH_MFPH_PH13MFP
#define SYS_GPH_MFPH_PH13MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH13MFP_Pos)           /*!< GPH_MFPH PH13 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH13MFP_UART3_RTS    (0x1UL<<SYS_GPH_MFPH_PH13MFP_Pos)           /*!< GPH_MFPH PH13 setting for UART3_RTS   \hideinitializer */

//GPH_MFPH_PH14MFP
#define SYS_GPH_MFPH_PH14MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH14MFP_Pos)           /*!< GPH_MFPH PH14 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH14MFP_UART3_CTS    (0x1UL<<SYS_GPH_MFPH_PH14MFP_Pos)           /*!< GPH_MFPH PH14 setting for UART3_CTS   \hideinitializer */

//GPH_MFPH_PH15MFP
#define SYS_GPH_MFPH_PH15MFP_GPIO         (0x0UL<<SYS_GPH_MFPH_PH15MFP_Pos)           /*!< GPH_MFPH PH15 setting for GPIO   \hideinitializer */
#define SYS_GPH_MFPH_PH15MFP_SC5_CLK      (0x2UL<<SYS_GPH_MFPH_PH15MFP_Pos)           /*!< GPH_MFPH PH15 setting for SC5_CLK   \hideinitializer */

//GPI_MFPL_PI0MFP
#define SYS_GPI_MFPL_PI0MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI0MFP_Pos)           /*!< GPI_MFPL PI0 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPL_PI0MFP_SC5_RST       (0x2UL<<SYS_GPI_MFPL_PI0MFP_Pos)            /*!< GPI_MFPL PI0 setting for SC5_RST     \hideinitializer */

//GPI_MFPL_PI1MFP
#define SYS_GPI_MFPL_PI1MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI1MFP_Pos)            /*!< GPI_MFPL PI1 setting for GPIO    \hideinitializer */
#define SYS_GPI_MFPL_PI1MFP_SC5_PWR       (0x2UL<<SYS_GPI_MFPL_PI1MFP_Pos)            /*!< GPI_MFPL PI1 setting for SC5_PWR     \hideinitializer */

//GPI_MFPL_PI2MFP
#define SYS_GPI_MFPL_PI2MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI2MFP_Pos)            /*!< GPI_MFPL PI2 setting for GPIO    \hideinitializer */
#define SYS_GPI_MFPL_PI2MFP_SC5_DAT       (0x2UL<<SYS_GPI_MFPL_PI2MFP_Pos)           /*!< GPI_MFPL PI2 setting for SC5_DAT      \hideinitializer */

//GPI_MFPL_PI3MFP
#define SYS_GPI_MFPL_PI3MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI3MFP_Pos)           /*!< GPI_MFPL PI3 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPL_PI3MFP_SPI3_SS0      (0x1UL<<SYS_GPI_MFPL_PI3MFP_Pos)            /*!< GPI_MFPL PI3 setting for SPI3_SS0      \hideinitializer */

//GPI_MFPL_PI4MFP
#define SYS_GPI_MFPL_PI4MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI4MFP_Pos)            /*!< GPI_MFPL PI4 setting for GPIO    \hideinitializer */
#define SYS_GPI_MFPL_PI4MFP_SPI3_CLK      (0x1UL<<SYS_GPI_MFPL_PI4MFP_Pos)           /*!< GPI_MFPL PI4 setting for SPI3_CLK     \hideinitializer */

//GPI_MFPL_PI5MFP
#define SYS_GPI_MFPL_PI5MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI5MFP_Pos)           /*!< GPI_MFPL PI5 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPL_PI5MFP_SPI3_MISO0    (0x1UL<<SYS_GPI_MFPL_PI5MFP_Pos)           /*!< GPI_MFPL PI5 setting for SPI3_MISO0     \hideinitializer */

//GPI_MFPL_PI6MFP
#define SYS_GPI_MFPL_PI6MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI6MFP_Pos)           /*!< GPI_MFPL PI6 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPL_PI6MFP_SPI3_MOSI0    (0x1UL<<SYS_GPI_MFPL_PI6MFP_Pos)           /*!< GPI_MFPL PI6 setting for SPI3_MOSI0     \hideinitializer */

//GPI_MFPL_PI7MFP
#define SYS_GPI_MFPL_PI7MFP_GPIO          (0x0UL<<SYS_GPI_MFPL_PI7MFP_Pos)           /*!< GPI_MFPL PI7 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPL_PI7MFP_I2C2_SCL      (0x1UL<<SYS_GPI_MFPL_PI7MFP_Pos)           /*!< GPI_MFPL PI7 setting for I2C2_SCL     \hideinitializer */
#define SYS_GPI_MFPL_PI7MFP_SPI3_MISO1    (0x2UL<<SYS_GPI_MFPL_PI7MFP_Pos)           /*!< GPI_MFPL PI7 setting for SPI3_MISO1     \hideinitializer */

//GPI_MFPL_PI8MFP
#define SYS_GPI_MFPH_PI8MFP_GPIO          (0x0UL<<SYS_GPI_MFPH_PI8MFP_Pos)           /*!< GPI_MFPH PI8 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPH_PI8MFP_I2C2_SDA      (0x1UL<<SYS_GPI_MFPH_PI8MFP_Pos)           /*!< GPI_MFPH PI8 setting for I2C2_SDA     \hideinitializer */
#define SYS_GPI_MFPH_PI8MFP_SPI3_MOSI1    (0x2UL<<SYS_GPI_MFPH_PI8MFP_Pos)           /*!< GPI_MFPH PI8 setting for SPI3_MOSI1     \hideinitializer */

//GPI_MFPH_PI9MFP
#define SYS_GPI_MFPH_PI9MFP_GPIO          (0x0UL<<SYS_GPI_MFPH_PI9MFP_Pos)           /*!< GPI_MFPH PI9 setting for GPIO     \hideinitializer */
#define SYS_GPI_MFPH_PI9MFP_I2C4_SCL      (0x4UL<<SYS_GPI_MFPH_PI9MFP_Pos)           /*!< GPI_MFPH PI9 setting for I2C4_SCL     \hideinitializer */

//GPI_MFPH_PI10MFP
#define SYS_GPI_MFPH_PI10MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI10MFP_Pos)           /*!< GPI_MFPH PI10 setting for GPIO   \hideinitializer */

//GPI_MFPH_PI11MFP
#define SYS_GPI_MFPH_PI11MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI11MFP_Pos)           /*!< GPI_MFPH PI11 setting for GPIO   \hideinitializer */
#define SYS_GPI_MFPH_PI11MFP_SPI2_SS0     (0x1UL<<SYS_GPI_MFPH_PI11MFP_Pos)            /*!< GPI_MFPH PI11 setting for SPI2_SS0  \hideinitializer */
#define SYS_GPI_MFPH_PI11MFP_I2S1_BCLK    (0x2UL<<SYS_GPI_MFPH_PI11MFP_Pos)            /*!< GPI_MFPH PI11 setting for I2S1_BCLK  \hideinitializer */
#define SYS_GPI_MFPH_PI11MFP_I2C4_SCL     (0x3UL<<SYS_GPI_MFPH_PI11MFP_Pos)            /*!< GPI_MFPH PI11 setting for I2C4_SCL  \hideinitializer */
#define SYS_GPI_MFPH_PI11MFP_SC3_PWR      (0x4UL<<SYS_GPI_MFPH_PI11MFP_Pos)            /*!< GPI_MFPH PI11 setting for SC3_PWR  \hideinitializer */

//GPI_MFPH_PI12MFP
#define SYS_GPI_MFPH_PI12MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI12MFP_Pos)            /*!< GPI_MFPH PI12 setting for GPIO  \hideinitializer */
#define SYS_GPI_MFPH_PI12MFP_SPI2_MISO1   (0x1UL<<SYS_GPI_MFPH_PI12MFP_Pos)            /*!< GPI_MFPH PI12 setting for SPI2_MISO1    \hideinitializer */
#define SYS_GPI_MFPH_PI12MFP_I2S1_LRCK    (0x2UL<<SYS_GPI_MFPH_PI12MFP_Pos)            /*!< GPI_MFPH PI12 setting for I2S1_LRCK     \hideinitializer */
#define SYS_GPI_MFPH_PI12MFP_I2C4_SDA     (0x3UL<<SYS_GPI_MFPH_PI12MFP_Pos)            /*!< GPI_MFPH PI12 setting for I2C4_SDA  \hideinitializer */
#define SYS_GPI_MFPH_PI12MFP_SC3_CD       (0x4UL<<SYS_GPI_MFPH_PI12MFP_Pos)            /*!< GPI_MFPH PI12 setting for SC3_CD    \hideinitializer */

//GPI_MFPH_PI13MFP
#define SYS_GPI_MFPH_PI13MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI13MFP_Pos)            /*!< GPI_MFPH PI13 setting for GPIO  \hideinitializer */

//GPI_MFPH_PI14MFP
#define SYS_GPI_MFPH_PI14MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI14MFP_Pos)            /*!< GPI_MFPH PI14 setting for GPIO  \hideinitializer */

//GPI_MFPH_PI15MFP
#define SYS_GPI_MFPH_PI15MFP_GPIO         (0x0UL<<SYS_GPI_MFPH_PI15MFP_Pos)            /*!< GPI_MFPH PI15 setting for GPIO  \hideinitializer */

/*@}*/ /* end of group NUC472_442_SYS_EXPORTED_CONSTANTS */

/** @addtogroup NUC472_442_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/

/**
  * @brief      Clear Brown-out detector interrupt flag
  * @param      None  
  * @return     None
  * @details    This macro clear Brown-out detector interrupt flag.
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCTL |= SYS_BODCTL_BODINTF_Msk)

/**
  * @brief      Set Brown-out detector function to normal mode
  * @param      None  
  * @return     None
  * @details    This macro set Brown-out detector to normal mode.
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCTL &= ~SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Disable Brown-out detector function
  * @param      None  
  * @return     None
  * @details    This macro disable Brown-out detector function.  
  */
#define SYS_DISABLE_BOD()               (SYS->BODCTL &= ~SYS_BODCTL_BODEN_Msk)     

/**
  * @brief      Enable Brown-out detector function
  * @param      None  
  * @return     None
  * @details    This macro enable Brown-out detector function.  
  */
#define SYS_ENABLE_BOD()                (SYS->BODCTL |= SYS_BODCTL_BODEN_Msk)
/**
  * @brief      Get Brown-out detector interrupt flag
  * @param      None    
  * @retval     0   Brown-out detect interrupt flag is not set.
  * @retval     >=1 Brown-out detect interrupt flag is set.
  * @details    This macro get Brown-out detector interrupt flag.    
  */
#define SYS_GET_BOD_INT_FLAG()          (SYS->BODCTL & SYS_BODCTL_BODINTF_Msk)    

/**
  * @brief      Get Brown-out detector status
  * @param      None 
  * @retval     0   System voltage is higher than BOD_VL setting or BOD_EN is 0.
  * @retval     >=1 System voltage is lower than BOD_VL setting.
  * @details    This macro get Brown-out detector output status.
  *             If the BOD_EN is 0, this function always return 0.
  */
#define SYS_GET_BOD_OUTPUT()            (SYS->BODCTL & SYS_BODCTL_BODOUT_Msk)

/**
  * @brief      Disable Brown-out detector interrupt function
  * @param      None   
  * @return     None
  * @details    This macro enable Brown-out detector interrupt function.
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCTL &= ~SYS_BODCTL_BODRSTEN_Msk)

/**
  * @brief      Enable Brown-out detector reset function
  * @param      None     
  * @return     None
  * @details    This macro enable Brown-out detect reset function.  
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCTL |= SYS_BODCTL_BODRSTEN_Msk)


/**
  * @brief      Set Brown-out detector function low power mode 
  * @param      None     
  * @return     None
  * @details    This macro set Brown-out detector to low power mode.  
  */
#define SYS_SET_BOD_LPM()               (SYS->BODCTL |= SYS_BODCTL_BODLPM_Msk)

/**
  * @brief      Set Brown-out detector voltage level
  * @param[in]  u32Level is Brown-out voltage level. Including :
  *             - \ref SYS_BODCTL_BODVL_4_5V
  *             - \ref SYS_BODCTL_BODVL_3_8V
  *             - \ref SYS_BODCTL_BODVL_2_7V
  *             - \ref SYS_BODCTL_BODVL_2_2V
  * @return     None
  * @details    This macro set Brown-out detector voltage level.  
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCTL = (SYS->BODCTL & ~SYS_BODCTL_BODVL_Msk) | u32Level) 

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
  * @retval     0   Previous reset source is not from LVR Reset
  * @retval     >=1 Previous reset source is from LVR Reset
  * @details    This macro get previous reset source is from Power-on Reset.   
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
  */
#define SYS_DISABLE_LVR()               (SYS->BODCTL &= ~SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Enable Low-Voltage-Reset function
  * @param      None  
  * @return     None
  * @details    This macro enable Low-Voltage-Reset function.  
  */
#define SYS_ENABLE_LVR()                (SYS->BODCTL |= SYS_BODCTL_LVREN_Msk)

/**
  * @brief      Disable Power-on Reset function
  * @param      None  
  * @return     None
  * @details    This macro disable Power-on Reset function.  
  */
#define SYS_DISABLE_POR()               (SYS->PORCTL = 0x5AA5)

/**
  * @brief      Enable Power-on Reset function
  * @param      None  
  * @return     None
  * @details    This macro enable Power-on Reset function.  
  */
#define SYS_ENABLE_POR()                (SYS->PORCTL = 0)


/**
  * @brief      Clear reset source flag
  * @param[in]  u32RstSrc is reset source. Including:
  *             - \ref SYS_RSTSTS_PORF_Msk
  *             - \ref SYS_RSTSTS_PINRF_Msk  
  *             - \ref SYS_RSTSTS_WDTRF_Msk
  *             - \ref SYS_RSTSTS_LVRF_Msk 
  *             - \ref SYS_RSTSTS_BODRF_Msk 
  *             - \ref SYS_RSTSTS_SYSRF_Msk   
	*             - \ref SYS_RSTSTS_CPURF_Msk
  * @return     None
  * @details    This macro clear reset source flag.   
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) (SYS->RSTSTS = u32RstSrc )

void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
void SYS_LockReg(void);
void SYS_UnlockReg(void);
uint32_t  SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void SYS_DisableBOD(void);

/*@}*/ /* end of group NUC472_442_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group NUC472_442_SYS_Driver */

/*@}*/ /* end of group NUC472_442_Device_Driver */

#ifdef __cplusplus
}
#endif

#endif //__SYS_H__

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
