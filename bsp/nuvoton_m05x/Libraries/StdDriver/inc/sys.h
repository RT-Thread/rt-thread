/**************************************************************************//**
 * @file     SYS.h
 * @version  V2.1
 * $Revision: 10 $
 * $Date: 14/02/05 1:17p $
 * @brief    M051 Series Global Control and Clock Control Driver Header File
 *
 * @note
 * Copyright (C) 2011 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef __SYS_H__
#define __SYS_H__


#include "M051Series.h"


#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup M051_Device_Driver M051 Device Driver
  @{
*/

/** @addtogroup M051_SYS_Driver SYS Driver
  @{
*/

/** @addtogroup M051_SYS_EXPORTED_CONSTANTS SYS Exported Constants
  @{
*/

/*---------------------------------------------------------------------------------------------------------*/
/*  Module Reset Control Resister constant definitions.                                                    */
/*---------------------------------------------------------------------------------------------------------*/
#define CHIP_RST    ((0x0<<24) | SYS_IPRSTC1_CPU_RST_Pos    ) /*!< CPU reset is one of the SYS_ResetModule parameter */
#define CPU_RST     ((0x0<<24) | SYS_IPRSTC1_CHIP_RST_Pos   ) /*!< CHIP reset is one of the SYS_ResetModule parameter */
#define EBI_RST     ((0x0<<24) | SYS_IPRSTC1_EBI_RST_Pos    ) /*!< EBI reset is one of the SYS_ResetModule parameter */
#define HDIV_RST    ((0x0<<24) | SYS_IPRSTC1_HDIV_RST_Pos   ) /*!< HDIV reset is one of the SYS_ResetModule parameter */
#define GPIO_RST    ((0x4<<24) | SYS_IPRSTC2_GPIO_RST_Pos   ) /*!< GPIO reset is one of the SYS_ResetModule parameter */
#define TMR0_RST    ((0x4<<24) | SYS_IPRSTC2_TMR0_RST_Pos   ) /*!< TMR0 reset is one of the SYS_ResetModule parameter */
#define TMR1_RST    ((0x4<<24) | SYS_IPRSTC2_TMR1_RST_Pos   ) /*!< TMR1 reset is one of the SYS_ResetModule parameter */
#define TMR2_RST    ((0x4<<24) | SYS_IPRSTC2_TMR2_RST_Pos   ) /*!< TMR2 reset is one of the SYS_ResetModule parameter */
#define TMR3_RST    ((0x4<<24) | SYS_IPRSTC2_TMR3_RST_Pos   ) /*!< TMR3 reset is one of the SYS_ResetModule parameter */
#define I2C0_RST    ((0x4<<24) | SYS_IPRSTC2_I2C0_RST_Pos   ) /*!< I2C0 reset is one of the SYS_ResetModule parameter */
#define I2C1_RST    ((0x4<<24) | SYS_IPRSTC2_I2C1_RST_Pos   ) /*!< I2C1 reset is one of the SYS_ResetModule parameter */
#define SPI0_RST    ((0x4<<24) | SYS_IPRSTC2_SPI0_RST_Pos   ) /*!< SPI0 reset is one of the SYS_ResetModule parameter */
#define SPI1_RST    ((0x4<<24) | SYS_IPRSTC2_SPI1_RST_Pos   ) /*!< SPI1 reset is one of the SYS_ResetModule parameter */
#define UART0_RST   ((0x4<<24) | SYS_IPRSTC2_UART0_RST_Pos  ) /*!< UART0 reset is one of the SYS_ResetModule parameter */
#define UART1_RST   ((0x4<<24) | SYS_IPRSTC2_UART1_RST_Pos  ) /*!< UART1 reset is one of the SYS_ResetModule parameter */
#define PWM03_RST   ((0x4<<24) | SYS_IPRSTC2_PWM03_RST_Pos  ) /*!< PWM03 reset is one of the SYS_ResetModule parameter */
#define PWM47_RST   ((0x4<<24) | SYS_IPRSTC2_PWM47_RST_Pos  ) /*!< PWM47 reset is one of the SYS_ResetModule parameter */
#define ACMP01_RST  ((0x4<<24) | SYS_IPRSTC2_ACMP01_RST_Pos ) /*!< ACMP01 reset is one of the SYS_ResetModule parameter */
#define ACMP23_RST  ((0x4<<24) | SYS_IPRSTC2_ACMP23_RST_Pos ) /*!< ACMP23 reset is one of the SYS_ResetModule parameter */
#define ADC_RST     ((0x4<<24) | SYS_IPRSTC2_ADC_RST_Pos    ) /*!< ADC reset is one of the SYS_ResetModule parameter */


/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector Threshold Voltage Selection constant definitions.                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_BODCR_BOD_RST_EN            (1UL<<SYS_BODCR_BOD_RSTEN_Pos)    /*!< Brown-out Reset Enable */
#define SYS_BODCR_BOD_INTERRUPT_EN      (0UL<<SYS_BODCR_BOD_RSTEN_Pos)    /*!< Brown-out Interrupt Enable */
#define SYS_BODCR_BOD_VL_4_4V           (3UL<<SYS_BODCR_BOD_VL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 4.4V */
#define SYS_BODCR_BOD_VL_3_7V           (2UL<<SYS_BODCR_BOD_VL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 3.7V */
#define SYS_BODCR_BOD_VL_2_7V           (1UL<<SYS_BODCR_BOD_VL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.7V */
#define SYS_BODCR_BOD_VL_2_2V           (0UL<<SYS_BODCR_BOD_VL_Pos)       /*!< Setting Brown Out Detector Threshold Voltage as 2.2V */


/*---------------------------------------------------------------------------------------------------------*/
/*  Multi-Function constant definitions.                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
#define SYS_MFP_TYPE_Msk(bit)       (1UL << ((bit) +16))
#define SYS_MFP_ALT_Msk(bit)        (1UL << ((bit) + 8))
#define SYS_MFP_MFP_Msk(bit)        (1UL << ((bit)    ))

#define SYS_MFP_P00_GPIO        0x00000000UL /*!< P0_MFP pin 0 setting for GPIO */
#define SYS_MFP_P00_AD0         0x00000001UL /*!< P0_MFP pin 0 setting for AD0  */
#define SYS_MFP_P00_CTS1        0x00000100UL /*!< P0_MFP pin 0 setting for CTS1 */
#define SYS_MFP_P00_TXD1        0x00000101UL /*!< P0_MFP pin 0 setting for TXD1 */
#define SYS_MFP_P00_ACMP3_P     0x01000000UL /*!< P0_MFP pin 0 setting for ACMP3_P */
#define SYS_MFP_P00_Msk         0x01000101UL /*!< P0_MFP pin 0 mask             */

#define SYS_MFP_P01_GPIO        0x00000000UL /*!< P0_MFP pin 1 setting for GPIO */
#define SYS_MFP_P01_AD1         0x00000002UL /*!< P0_MFP pin 1 setting for AD1  */
#define SYS_MFP_P01_RTS1        0x00000200UL /*!< P0_MFP pin 1 setting for RTS1 */
#define SYS_MFP_P01_RXD1        0x00000202UL /*!< P0_MFP pin 1 setting for RXD1 */
#define SYS_MFP_P01_ACMP3_N     0x02000000UL /*!< P0_MFP pin 1 setting for ACMP3_N */
#define SYS_MFP_P01_Msk         0x02000202UL /*!< P0_MFP pin 1 mask             */

#define SYS_MFP_P02_GPIO    0x00000000UL /*!< P0_MFP pin 2 setting for GPIO */
#define SYS_MFP_P02_AD2     0x00000004UL /*!< P0_MFP pin 2 setting for AD2  */
#define SYS_MFP_P02_CTS0    0x00000400UL /*!< P0_MFP pin 2 setting for CTS0 */
#define SYS_MFP_P02_TXD0    0x00000404UL /*!< P0_MFP pin 2 setting for TXD0 */
#define SYS_MFP_P02_Msk     0x00000404UL /*!< P0_MFP pin 2 mask             */

#define SYS_MFP_P03_GPIO    0x00000000UL /*!< P0_MFP pin 3 setting for GPIO */
#define SYS_MFP_P03_AD3     0x00000008UL /*!< P0_MFP pin 3 setting for AD3  */
#define SYS_MFP_P03_RTS0    0x00000800UL /*!< P0_MFP pin 3 setting for RTS0 */
#define SYS_MFP_P03_RXD0    0x00000808UL /*!< P0_MFP pin 3 setting for RXD0 */
#define SYS_MFP_P03_Msk     0x00000808UL /*!< P0_MFP pin 3 mask             */

#define SYS_MFP_P04_GPIO    0x00000000UL /*!< P0_MFP pin 4 setting for GPIO   */
#define SYS_MFP_P04_AD4     0x00000010UL /*!< P0_MFP pin 4 setting for AD4    */
#define SYS_MFP_P04_SPISS1  0x00001000UL /*!< P0_MFP pin 4 setting for SPISS1 */
#define SYS_MFP_P04_Msk     0x00001010UL /*!< P0_MFP pin 4 mask               */

#define SYS_MFP_P05_GPIO    0x00000000UL /*!< P0_MFP pin 5 setting for GPIO   */
#define SYS_MFP_P05_AD5     0x00000020UL /*!< P0_MFP pin 5 setting for AD5    */
#define SYS_MFP_P05_MOSI_1  0x00002000UL /*!< P0_MFP pin 5 setting for MOSI_1 */
#define SYS_MFP_P05_Msk     0x00002020UL /*!< P0_MFP pin 5 mask               */

#define SYS_MFP_P06_GPIO    0x00000000UL /*!< P0_MFP pin 6 setting for GPIO   */
#define SYS_MFP_P06_AD6     0x00000040UL /*!< P0_MFP pin 6 setting for AD6    */
#define SYS_MFP_P06_MISO_1  0x00004000UL /*!< P0_MFP pin 6 setting for MISO_1 */
#define SYS_MFP_P06_Msk     0x00004040UL /*!< P0_MFP pin 6 mask               */

#define SYS_MFP_P07_GPIO    0x00000000UL /*!< P0_MFP pin 7 setting for GPIO    */
#define SYS_MFP_P07_AD7     0x00000080UL /*!< P0_MFP pin 7 setting for AD7     */
#define SYS_MFP_P07_SPICLK1 0x00008000UL /*!< P0_MFP pin 7 setting for SPICLK1 */
#define SYS_MFP_P07_Msk     0x00008080UL /*!< P0_MFP pin 7 mask                */

#define SYS_MFP_P10_GPIO    0x00000000UL /*!< P1_MFP pin 0 setting for GPIO */
#define SYS_MFP_P10_AIN0    0x00000001UL /*!< P1_MFP pin 0 setting for AIN0 */
#define SYS_MFP_P10_T2      0x00000100UL /*!< P1_MFP pin 0 setting for T2   */
#define SYS_MFP_P10_nWRL    0x00000101UL /*!< P1_MFP pin 0 setting for nWRL */
#define SYS_MFP_P10_Msk     0x00000101UL /*!< P1_MFP pin 0 mask             */

#define SYS_MFP_P11_GPIO    0x00000000UL /*!< P1_MFP pin 1 setting for GPIO */
#define SYS_MFP_P11_AIN1    0x00000002UL /*!< P1_MFP pin 1 setting for AIN1 */
#define SYS_MFP_P11_T3      0x00000200UL /*!< P1_MFP pin 1 setting for T3   */
#define SYS_MFP_P11_nWRH    0x00000202UL /*!< P1_MFP pin 1 setting for nWRH */
#define SYS_MFP_P11_Msk     0x00000202UL /*!< P1_MFP pin 1 mask             */

#define SYS_MFP_P12_GPIO    0x00000000UL /*!< P1_MFP pin 2 setting for GPIO */
#define SYS_MFP_P12_AIN2    0x00000004UL /*!< P1_MFP pin 2 setting for AIN2 */
#define SYS_MFP_P12_RXD1    0x00000400UL /*!< P1_MFP pin 2 setting for RXD1 */
#define SYS_MFP_P12_Msk     0x00000404UL /*!< P1_MFP pin 2 mask             */

#define SYS_MFP_P13_GPIO    0x00000000UL /*!< P1_MFP pin 3 setting for GPIO */
#define SYS_MFP_P13_AIN3    0x00000008UL /*!< P1_MFP pin 3 setting for AIN3 */
#define SYS_MFP_P13_TXD1    0x00000800UL /*!< P1_MFP pin 3 setting for TXD1 */
#define SYS_MFP_P13_Msk     0x00000808UL /*!< P1_MFP pin 3 mask             */

#define SYS_MFP_P14_GPIO    0x00000000UL /*!< P1_MFP pin 4 setting for GPIO   */
#define SYS_MFP_P14_AIN4    0x00000010UL /*!< P1_MFP pin 4 setting for AIN4   */
#define SYS_MFP_P14_SPISS0  0x00001000UL /*!< P1_MFP pin 4 setting for SPISS0 */
#define SYS_MFP_P14_CPN0    0x00001010UL /*!< P1_MFP pin 4 setting for CPN0   */
#define SYS_MFP_P14_ACMP0_N 0x00001010UL /*!< P1_MFP pin 4 setting for ACMP0_N */
#define SYS_MFP_P14_Msk     0x00001010UL /*!< P1_MFP pin 4 mask               */

#define SYS_MFP_P15_GPIO    0x00000000UL /*!< P1_MFP pin 5 setting for GPIO   */
#define SYS_MFP_P15_AIN5    0x00000020UL /*!< P1_MFP pin 5 setting for AIN5   */
#define SYS_MFP_P15_MOSI_0  0x00002000UL /*!< P1_MFP pin 5 setting for MOSI_0 */
#define SYS_MFP_P15_CPP0    0x00002020UL /*!< P1_MFP pin 5 setting for CPP0   */
#define SYS_MFP_P15_ACMP0_P 0x00002020UL /*!< P1_MFP pin 5 setting for ACMP0_P */
#define SYS_MFP_P15_Msk     0x00002020UL /*!< P1_MFP pin 5 mask               */

#define SYS_MFP_P16_GPIO    0x00000000UL /*!< P1_MFP pin 6 setting for GPIO   */
#define SYS_MFP_P16_AIN6    0x00000040UL /*!< P1_MFP pin 6 setting for AIN6   */
#define SYS_MFP_P16_MISO_0  0x00004000UL /*!< P1_MFP pin 6 setting for MISO_0 */
#define SYS_MFP_P16_ACMP2_N 0x00004040UL /*!< P1_MFP pin 6 setting for ACMP2_N */
#define SYS_MFP_P16_Msk     0x00004040UL /*!< P1_MFP pin 6 mask               */

#define SYS_MFP_P17_GPIO    0x00000000UL /*!< P1_MFP pin 7 setting for GPIO    */
#define SYS_MFP_P17_AIN7    0x00000080UL /*!< P1_MFP pin 7 setting for AIN7    */
#define SYS_MFP_P17_SPICLK0 0x00008000UL /*!< P1_MFP pin 7 setting for SPICLK0 */
#define SYS_MFP_P17_ACMP2_P 0x00008080UL /*!< P1_MFP pin 7 setting for ACMP2_P */
#define SYS_MFP_P17_Msk     0x00008080UL /*!< P1_MFP pin 7 mask                */

#define SYS_MFP_P20_GPIO    0x00000000UL /*!< P2_MFP pin 0 setting for GPIO */
#define SYS_MFP_P20_AD8     0x00000001UL /*!< P2_MFP pin 0 setting for AD8  */
#define SYS_MFP_P20_PWM0    0x00000100UL /*!< P2_MFP pin 0 setting for PWM0 */
#define SYS_MFP_P20_Msk     0x00000101UL /*!< P2_MFP pin 0 mask             */

#define SYS_MFP_P21_GPIO    0x00000000UL /*!< P2_MFP pin 1 setting for GPIO */
#define SYS_MFP_P21_AD9     0x00000002UL /*!< P2_MFP pin 1 setting for AD9  */
#define SYS_MFP_P21_PWM1    0x00000200UL /*!< P2_MFP pin 1 setting for PWM1 */
#define SYS_MFP_P21_Msk     0x00000202UL /*!< P2_MFP pin 1 mask             */

#define SYS_MFP_P22_GPIO    0x00000000UL /*!< P2_MFP pin 2 setting for GPIO */
#define SYS_MFP_P22_AD10    0x00000004UL /*!< P2_MFP pin 2 setting for AD10 */
#define SYS_MFP_P22_PWM2    0x00000400UL /*!< P2_MFP pin 2 setting for PWM2 */
#define SYS_MFP_P22_Msk     0x00000404UL /*!< P2_MFP pin 2 mask             */

#define SYS_MFP_P23_GPIO    0x00000000UL /*!< P2_MFP pin 3 setting for GPIO */
#define SYS_MFP_P23_AD11    0x00000008UL /*!< P2_MFP pin 3 setting for AD11 */
#define SYS_MFP_P23_PWM3    0x00000800UL /*!< P2_MFP pin 3 setting for PWM3 */
#define SYS_MFP_P23_Msk     0x00000808UL /*!< P2_MFP pin 3 mask             */

#define SYS_MFP_P24_GPIO    0x00000000UL /*!< P2_MFP pin 4 setting for GPIO */
#define SYS_MFP_P24_AD12    0x00000010UL /*!< P2_MFP pin 4 setting for AD12 */
#define SYS_MFP_P24_PWM4    0x00001000UL /*!< P2_MFP pin 4 setting for PWM4 */
#define SYS_MFP_P24_SCL1    0x00001010UL /*!< P2_MFP pin 4 setting for SCL1 */
#define SYS_MFP_P24_Msk     0x00001010UL /*!< P2_MFP pin 4 mask             */

#define SYS_MFP_P25_GPIO    0x00000000UL /*!< P2_MFP pin 5 setting for GPIO */
#define SYS_MFP_P25_AD13    0x00000020UL /*!< P2_MFP pin 5 setting for AD13 */
#define SYS_MFP_P25_PWM5    0x00002000UL /*!< P2_MFP pin 5 setting for PWM5 */
#define SYS_MFP_P25_SDA1    0x00002020UL /*!< P2_MFP pin 5 setting for SDA1 */
#define SYS_MFP_P25_Msk     0x00002020UL /*!< P2_MFP pin 5 mask             */

#define SYS_MFP_P26_GPIO    0x00000000UL /*!< P2_MFP pin 6 setting for GPIO */
#define SYS_MFP_P26_AD14    0x00000040UL /*!< P2_MFP pin 6 setting for AD14 */
#define SYS_MFP_P26_PWM6    0x00004000UL /*!< P2_MFP pin 6 setting for PWM6 */
#define SYS_MFP_P26_CPO1    0x00004040UL /*!< P2_MFP pin 6 setting for CPO1 */
#define SYS_MFP_P26_ACMP1_O 0x00004040UL /*!< P2_MFP pin 6 setting for ACMP1_O */
#define SYS_MFP_P26_Msk     0x00004040UL /*!< P2_MFP pin 6 mask             */

#define SYS_MFP_P27_GPIO    0x00000000UL /*!< P2_MFP pin 7 setting for GPIO */
#define SYS_MFP_P27_AD15    0x00000080UL /*!< P2_MFP pin 7 setting for AD15 */
#define SYS_MFP_P27_PWM7    0x00008000UL /*!< P2_MFP pin 7 setting for PWM7 */
#define SYS_MFP_P27_Msk     0x00008080UL /*!< P2_MFP pin 7 mask             */

#define SYS_MFP_P30_GPIO    0x00000000UL /*!< P3_MFP pin 0 setting for GPIO */
#define SYS_MFP_P30_RXD0    0x00000001UL /*!< P3_MFP pin 0 setting for RXD0 */
#define SYS_MFP_P30_CPN1    0x00000100UL /*!< P3_MFP pin 0 setting for CPN1 */
#define SYS_MFP_P30_ACMP1_N 0x00000100UL /*!< P3_MFP pin 0 setting for ACMP1_N */
#define SYS_MFP_P30_Msk     0x00000101UL /*!< P3_MFP pin 0 mask             */

#define SYS_MFP_P31_GPIO    0x00000000UL /*!< P3_MFP pin 1 setting for GPIO */
#define SYS_MFP_P31_TXD0    0x00000002UL /*!< P3_MFP pin 1 setting for TXD0 */
#define SYS_MFP_P31_CPP1    0x00000200UL /*!< P3_MFP pin 1 setting for CPP1 */
#define SYS_MFP_P31_ACMP1_P 0x00000200UL /*!< P3_MFP pin 1 setting for ACMP1_P */
#define SYS_MFP_P31_Msk     0x00000202UL /*!< P3_MFP pin 1 mask             */

#define SYS_MFP_P32_GPIO    0x00000000UL /*!< P3_MFP pin 2 setting for GPIO  */
#define SYS_MFP_P32_INT0    0x00000004UL /*!< P3_MFP pin 2 setting for /INT0 */
#define SYS_MFP_P32_T0EX    0x00000400UL /*!< P3_MFP pin 2 setting for T0EX  */
#define SYS_MFP_P32_Msk     0x00000404UL /*!< P3_MFP pin 2 mask              */

#define SYS_MFP_P33_GPIO    0x00000000UL /*!< P3_MFP pin 3 setting for GPIO  */
#define SYS_MFP_P33_INT1    0x00000008UL /*!< P3_MFP pin 3 setting for /INT1 */
#define SYS_MFP_P33_MCLK    0x00000800UL /*!< P3_MFP pin 3 setting for MCLK  */
#define SYS_MFP_P33_T1EX    0x00000808UL /*!< P3_MFP pin 3 setting for T1EX  */
#define SYS_MFP_P33_Msk     0x00000808UL /*!< P3_MFP pin 3 mask              */

#define SYS_MFP_P34_GPIO    0x00000000UL /*!< P3_MFP pin 4 setting for GPIO */
#define SYS_MFP_P34_T0      0x00000010UL /*!< P3_MFP pin 4 setting for T0   */
#define SYS_MFP_P34_SDA0    0x00001000UL /*!< P3_MFP pin 4 setting for SDA0 */
#define SYS_MFP_P34_Msk     0x00001010UL /*!< P3_MFP pin 4 mask             */

#define SYS_MFP_P35_GPIO    0x00000000UL /*!< P3_MFP pin 5 setting for GPIO */
#define SYS_MFP_P35_T1      0x00000020UL /*!< P3_MFP pin 5 setting for T1   */
#define SYS_MFP_P35_SCL0    0x00002000UL /*!< P3_MFP pin 5 setting for SCL0 */
#define SYS_MFP_P35_CKO     0x00002020UL /*!< P3_MFP pin 5 setting for CKO  */
#define SYS_MFP_P35_Msk     0x00002020UL /*!< P3_MFP pin 5 mask             */

#define SYS_MFP_P36_GPIO    0x00000000UL /*!< P3_MFP pin 6 setting for GPIO */
#define SYS_MFP_P36_nWR     0x00000040UL /*!< P3_MFP pin 6 setting for nWR  */
#define SYS_MFP_P36_CKO     0x00004000UL /*!< P3_MFP pin 6 setting for CKO  */
#define SYS_MFP_P36_CPO0    0x00004040UL /*!< P3_MFP pin 6 setting for CPO0 */
#define SYS_MFP_P36_ACMP0_O 0x00004040UL /*!< P3_MFP pin 6 setting for ACMP0_O */
#define SYS_MFP_P36_Msk     0x00004040UL /*!< P3_MFP pin 6 mask             */

#define SYS_MFP_P37_GPIO    0x00000000UL /*!< P3_MFP pin 7 setting for GPIO */
#define SYS_MFP_P37_nRD     0x00000080UL /*!< P3_MFP pin 7 setting for nWR  */
#define SYS_MFP_P37_Msk     0x00008080UL /*!< P3_MFP pin 7 mask             */

#define SYS_MFP_P40_GPIO    0x00000000UL /*!< P4_MFP pin 0 setting for GPIO */
#define SYS_MFP_P40_PWM0    0x00000001UL /*!< P4_MFP pin 0 setting for PWM0 */
#define SYS_MFP_P40_T2EX    0x00000100UL /*!< P4_MFP pin 0 setting for T2EX */
#define SYS_MFP_P40_Msk     0x00000101UL /*!< P4_MFP pin 0 mask             */

#define SYS_MFP_P41_GPIO    0x00000000UL /*!< P4_MFP pin 1 setting for GPIO */
#define SYS_MFP_P41_PWM1    0x00000002UL /*!< P4_MFP pin 1 setting for PWM1 */
#define SYS_MFP_P41_T3EX    0x00000200UL /*!< P4_MFP pin 1 setting for T3EX */
#define SYS_MFP_P41_Msk     0x00000202UL /*!< P4_MFP pin 1 mask             */

#define SYS_MFP_P42_GPIO    0x00000000UL /*!< P4_MFP pin 2 setting for GPIO */
#define SYS_MFP_P42_PWM2    0x00000004UL /*!< P4_MFP pin 2 setting for PWM2 */
#define SYS_MFP_P42_Msk     0x00000404UL /*!< P4_MFP pin 2 mask             */

#define SYS_MFP_P43_GPIO    0x00000000UL /*!< P4_MFP pin 3 setting for GPIO */
#define SYS_MFP_P43_PWM3    0x00000008UL /*!< P4_MFP pin 3 setting for PWM3 */
#define SYS_MFP_P43_Msk     0x00000808UL /*!< P4_MFP pin 3 mask             */

#define SYS_MFP_P44_GPIO    0x00000000UL /*!< P4_MFP pin 4 setting for GPIO */
#define SYS_MFP_P44_nCS     0x00000010UL /*!< P4_MFP pin 4 setting for nCS  */
#define SYS_MFP_P44_SCL1    0x00001000UL /*!< P4_MFP pin 4 setting for SCL1  */
#define SYS_MFP_P44_Msk     0x00001010UL /*!< P4_MFP pin 4 mask             */

#define SYS_MFP_P45_GPIO    0x00000000UL /*!< P4_MFP pin 5 setting for GPIO */
#define SYS_MFP_P45_ALE     0x00000020UL /*!< P4_MFP pin 5 setting for ALE  */
#define SYS_MFP_P45_SDA1    0x00002000UL /*!< P4_MFP pin 5 setting for SDA1  */
#define SYS_MFP_P45_Msk     0x00002020UL /*!< P4_MFP pin 5 mask             */

#define SYS_MFP_P46_GPIO    0x00000000UL /*!< P4_MFP pin 6 setting for GPIO    */
#define SYS_MFP_P46_ICE_CLK 0x00000040UL /*!< P4_MFP pin 6 setting for ICE_CLK */
#define SYS_MFP_P46_Msk     0x00004040UL /*!< P4_MFP pin 6 mask                */

#define SYS_MFP_P47_GPIO    0x00000000UL /*!< P4_MFP pin 7 setting for GPIO    */
#define SYS_MFP_P47_ICE_DAT 0x00000080UL /*!< P4_MFP pin 7 setting for ICE_DAT */
#define SYS_MFP_P47_Msk     0x00008080UL /*!< P4_MFP pin 7 mask                */



/*@}*/ /* end of group M051_SYS_EXPORTED_CONSTANTS */

/** @addtogroup M051_SYS_EXPORTED_FUNCTIONS SYS Exported Functions
  @{
*/


/**
  * @brief  This macro clear Brown-out interrupt flag.
  * @return None
  */
#define SYS_CLEAR_BOD_INT_FLAG()        (SYS->BODCR |= SYS_BODCR_BOD_INTF_Msk)

/**
  * @brief  This macro set Brown-out detect to normal mode.
  * @return None
  */
#define SYS_CLEAR_BOD_LPM()             (SYS->BODCR &= ~SYS_BODCR_BOD_LPM_Msk)

/**
  * @brief  This macro disable Brown-out detect function.
  * @return None
  */
#define SYS_DISABLE_BOD()               (SYS->BODCR &= ~SYS_BODCR_BOD_EN_Msk)

/**
  * @brief  This macro enable Brown-out detect function.
  * @return None
  */
#define SYS_ENABLE_BOD()                (SYS->BODCR |= SYS_BODCR_BOD_EN_Msk)

/**
  * @brief  This macro get Brown-out detect interrupt flag.
  * @return 0: Brown-out detect interrupt flag is not set.
  *         1: Brown-out detect interrupt flag is set.
  */
#define SYS_GET_BOD_INT_FLAG()          ((SYS->BODCR & SYS_BODCR_BOD_INTF_Msk)>>SYS_BODCR_BOD_INTF_Pos)

/**
  * @brief      This macro get Brown-out detector output status.
  * @return     0: System voltage is higher than BOD_VL setting or BOD_EN is 0.
  *             1: System voltage is lower than BOD_VL setting.
  * @details    If the BOD_EN is 0, this function always return 0.
  */
#define SYS_GET_BOD_OUTPUT()            ((SYS->BODCR & SYS_BODCR_BOD_OUT_Msk)>>SYS_BODCR_BOD_OUT_Msk)

/**
  * @brief  This macro enable Brown-out detect interrupt function.
  * @return None
  */
#define SYS_DISABLE_BOD_RST()           (SYS->BODCR &= ~SYS_BODCR_BOD_RSTEN_Msk)

/**
  * @brief  This macro enable Brown-out detect reset function.
  * @return None
  */
#define SYS_ENABLE_BOD_RST()            (SYS->BODCR |= SYS_BODCR_BOD_RSTEN_Msk)

/**
  * @brief  This macro set Brown-out detect to low power mode.
  * @return None
  */
#define SYS_SET_BOD_LPM()               (SYS->BODCR |= SYS_BODCR_BOD_LPM_Msk)

/**
  * @brief  This macro set Brown-out detect voltage level.
  * @param  u32Level is Brown-out voltage level. Including :
  *         - \ref SYS_BODCR_BOD_VL_4_4V
  *         - \ref SYS_BODCR_BOD_VL_3_7V
  *         - \ref SYS_BODCR_BOD_VL_2_7V
  *         - \ref SYS_BODCR_BOD_VL_2_2V
  * @return None
  */
#define SYS_SET_BOD_LEVEL(u32Level)     (SYS->BODCR = (SYS->BODCR & ~SYS_BODCR_BOD_VL_Msk) | u32Level)

/**
  * @brief  This macro get previous reset source is from Brown-out detect reset.
  * @return 0: Previous reset source is not from Brown-out detect reset
  *         1: Previous reset source is from Brown-out detect reset
  */
#define SYS_IS_BOD_RST()                (SYS->RSTSRC & SYS_RSTSRC_RSTS_BOD_Msk)

/**
  * @brief  This macro get previous reset source is from Low-Voltage-Reset.
  * @return 0: Previous reset source is not from CPU reset
  *         1: Previous reset source is from CPU reset
  */
#define SYS_IS_CPU_RST()                (SYS->RSTSRC & SYS_RSTSRC_RSTS_CPU_Msk)

/**
  * @brief  This macro get previous reset source is from Power-on Reset.
  * @return 0: Previous reset source is not from Low-Voltage-Reset
  *         1: Previous reset source is from Low-Voltage-Reset
  */
#define SYS_IS_POR_RST()                (SYS->RSTSRC & SYS_RSTSRC_RSTS_POR_Msk)

/**
  * @brief  This macro get previous reset source is from reset pin reset.
  * @return 0: Previous reset source is not from Power-on Reset
  *         1: Previous reset source is from Power-on Reset
  */
#define SYS_IS_RSTPIN_RST()             (SYS->RSTSRC & SYS_RSTSRC_RSTS_RESET_Msk)

/**
  * @brief  This macro get previous reset source is from system reset.
  * @return 0: Previous reset source is not from reset pin reset
  *         1: Previous reset source is from reset pin reset
  */
#define SYS_IS_SYSTEM_RST()             (SYS->RSTSRC & SYS_RSTSRC_RSTS_MCU_Msk)

/**
  * @brief  This macro get previous reset source is from window watch dog reset.
  * @return 0: Previous reset source is not from reset system reset
  *         1: Previous reset source is from reset system reset
  */
#define SYS_IS_WDT_RST()                (SYS->RSTSRC & SYS_RSTSRC_RSTS_WDT_Msk)

/**
  * @brief  This macro disable Low-Voltage-Reset function.
  * @return None
  */
#define SYS_DISABLE_LVR()               (SYS->BODCR &= ~SYS_BODCR_LVR_EN_Msk)

/**
  * @brief  This macro enable Low-Voltage-Reset function.
  * @return None
  */
#define SYS_ENABLE_LVR()                (SYS->BODCR |= SYS_BODCR_LVR_EN_Msk)

/**
  * @brief  This macro disable Power-on Reset function.
  * @return None
  */
#define SYS_DISABLE_POR()               (SYS->PORCR = 0x5AA5)

/**
  * @brief  This macro enable Power-on Reset function.
  * @return None
  */
#define SYS_ENABLE_POR()                (SYS->PORCR = 0)

/**
  * @brief  This macro clear reset source flag.
  * @param  u32RstSrc is reset source.
  * @return None
  */
#define SYS_CLEAR_RST_SOURCE(u32RstSrc) (SYS->RSTSRC | u32RstSrc )

/**
  * @brief   This function enable register write-protection function
  * @return  None
  * @details To lock the protected register to forbid write access
  */
static __INLINE void SYS_LockReg(void)
{
    SYS->REGWRPROT = 0;
}

/**
  * @brief   This function disable register write-protection function
  * @return  None
  * @details To unlock the protected register to allow write access
  */
static __INLINE void SYS_UnlockReg(void)
{
    while(SYS->REGWRPROT != SYS_REGWRPROT_REGPROTDIS_Msk)
    {
        SYS->REGWRPROT = 0x59;
        SYS->REGWRPROT = 0x16;
        SYS->REGWRPROT = 0x88;
    }
}




void SYS_ClearResetSrc(uint32_t u32Src);
uint32_t SYS_GetBODStatus(void);
uint32_t SYS_GetResetSrc(void);
uint32_t SYS_IsRegLocked(void);
uint32_t  SYS_ReadPDID(void);
void SYS_ResetChip(void);
void SYS_ResetCPU(void);
void SYS_ResetModule(uint32_t u32ModuleIndex);
void SYS_EnableBOD(int32_t i32Mode, uint32_t u32BODLevel);
void SYS_DisableBOD(void);


/*@}*/ /* end of group M051_SYS_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M051_SYS_Driver */

/*@}*/ /* end of group M051_Device_Driver */


#ifdef __cplusplus
}
#endif

#endif //__SYS_H__
