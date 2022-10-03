/**************************************************************************//**
 * @file     sspcc_reg.h
 * @brief    SSPCC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SSPCC_REG_H__
#define __SSPCC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- System Security Peripheral Configuration Controller -------------------------*/
/**
    @addtogroup SSPCC System Security Peripheral Configuration Controller(SSPCC)
    Memory Mapped Structure for SSPCC Controller
@{ */

typedef struct
{


    /**
     * @var SSPCC_T::PSSET0
     * Offset: 0x00  Peripheral Security Attribution Set Register 0 (0x4000_0000~0x400F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[17:16] |PDMA0     |PDMA0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[19:18] |PDMA1     |PDMA1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[21:20] |PDMA2     |PDMA2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PDMA3     |PDMA3 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET1
     * Offset: 0x04  Peripheral Security Attribution Set Register 1 (0x4010_0000~0x401F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |EBI       |EBI Controller Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |SDH0      |SD Host 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[19:18] |SDH1      |SD Host 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[21:20] |NANDC     |NAND Controller Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * @var SSPCC_T::PSSET2
     * Offset: 0x08  Peripheral Security Attribution Set Register 2 (0x4020_0000~0x402F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |HSUSBD    |HS USB Device Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * @var SSPCC_T::PSSET3
     * Offset: 0x0C  Peripheral Security Attribution Set Register 3 (0x4030_0000~0x403F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |CRYPTO    |Crypto Accelerator Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[25:24] |CANFD0    |CANFD0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |CANFD1    |CANFD1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |CANFD2    |CANFD2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |CANFD3    |CANFD3 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET4
     * Offset: 0x10  Peripheral Security Attribution Set Register 4 (0x4040_0000~0x404F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:4]   |ADC0      |ADC 0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |EADC0     |EADC 0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |WDTWWDT1  |WDTWWDT1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[17:16] |I2S0      |I2S 0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |I2S1      |I2S 1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |KPI       |KPI Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |DDRPHYPUB |DDR PHY Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[27:26] |MCTL      |DRAM Controller Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * @var SSPCC_T::PSSET5
     * Offset: 0x14  Peripheral Security Attribution Set Register 5 (0x4050_0000~0x405F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |TMR01     |TMR01 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[3:2]   |TMR23     |TMR23 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |TMR45     |TMR45 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |TMR67     |TMR67 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |TMR89     |TMR89 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |TMR1011   |TMR1011 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |EPWM0     |EPWM 0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |EPWM1     |EPWM 1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |EPWM2     |EPWM 2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET6
     * Offset: 0x18  Peripheral Security Attribution Set Register 6 (0x4060_0000~0x406F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |SPI0      |SPI0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |SPI1      |SPI1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |SPI2      |SPI2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |SPI3      |SPI3 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |QSPI0     |QSPI0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[19:18] |QSPI1     |QSPI1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET7
     * Offset: 0x1C  Peripheral Security Attribution Set Register 7 (0x4070_0000~0x407F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |UART0     |UART0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[3:2]   |UART1     |UART1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |UART2     |UART2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |UART3     |UART3 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |UART4     |UART4 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |UART5     |UART5 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |UART6     |UART6 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |UART7     |UART7 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |UART8     |UART8 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |UART9     |UART9 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |UART10    |UART10 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |UART11    |UART11 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |UART12    |UART12 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |UART13    |UART13 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |UART14    |UART14 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |UART15    |UART15 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET8
     * Offset: 0x20  Peripheral Security Attribution Set Register 8 (0x4080_0000~0x408F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |I2C0      |I2C0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * |[3:2]   |I2C1      |I2C1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |I2C2      |I2C2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |I2C3      |I2C3 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |I2C4      |I2C4 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |I2C5      |I2C5 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |UART16    |UART16 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET9
     * Offset: 0x24  Peripheral Security Attribution Set Register 9 (0x4090_0000~0x409F_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |SC0       |SC0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |SC1       |SC1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::PSSET10
     * Offset: 0x28  Peripheral Security Attribution Set Register 10 (0x40A0_0000~0x40AF_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var SSPCC_T::PSSET11
     * Offset: 0x2C  Peripheral Security Attribution Set Register 11 (0x40B0_0000~0x40BF_FFFF)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |QEI0      |QEI0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |QEI1      |QEI1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |QEI2      |QEI2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |ECAP0     |ECAP0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |ECAP1     |ECAP1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |ECAP2     |ECAP2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |TRNG      |TRNG Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Reserved.
     * @var SSPCC_T::SRAMSB
     * Offset: 0x40  SRAM Security Boundary Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[4:0]   |SR0BOUND  |Set SRAM0 Security Boundary
     * |        |          |Set the 16 Kbytes-aligned boundary of SRAM0.
     * |        |          |The SRAM part below the boundary is SubM region and the part higher the boundary is ShareMemory region.
     * |        |          |When the boundary is set to higher than the size of SRAM, the whole SRAM is SubM region.
     * |[12:8]  |SR1BOUND  |Set SRAM1 Security Boundary
     * |        |          |Set the 16 Kbytes-aligned boundary of data SRAM.
     * |        |          |The SRAM part below the boundary is TZS region and the part higher the boundary is TZNS region.
     * |        |          |When the boundary is set to higher than the size of SRAM, the whole SRAM is TZS region.
     * @var SSPCC_T::EBISSET
     * Offset: 0x50  EBI Memory Security Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |BANK0     |EBI Memory Bank0 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |BANK1     |EBI Memory Bank1 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |BANK2     |EBI Memory Bank2 Security Attribution Bits
     * |        |          |00 = Reserved.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOASSET
     * Offset: 0x60  GPIO Port A Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOBSSET
     * Offset: 0x64  GPIO Port B Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOCSSET
     * Offset: 0x68  GPIO Port C Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IODSSET
     * Offset: 0x6C  GPIO Port D Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOESSET
     * Offset: 0x70  GPIO Port E Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOFSSET
     * Offset: 0x74  GPIO Port F Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOGSSET
     * Offset: 0x78  GPIO Port G Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOHSSET
     * Offset: 0x7C  GPIO Port H Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOISSET
     * Offset: 0x80  GPIO Port I Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOJSSET
     * Offset: 0x84  GPIO Port J Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOKSSET
     * Offset: 0x88  GPIO Port K Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOLSSET
     * Offset: 0x8C  GPIO Port L Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IOMSSET
     * Offset: 0x90  GPIO Port M Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::IONSSET
     * Offset: 0x94  GPIO Port N Security Attribution Set Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |PIN0      |GPIO Pin 0 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[3:2]   |PIN1      |GPIO Pin 1 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[5:4]   |PIN2      |GPIO Pin 2 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[7:6]   |PIN3      |GPIO Pin 3 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[9:8]   |PIN4      |GPIO Pin 4 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[11:10] |PIN5      |GPIO Pin 5 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[13:12] |PIN6      |GPIO Pin 6 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[15:14] |PIN7      |GPIO Pin 7 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[17:16] |PIN8      |GPIO Pin 8 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[19:18] |PIN9      |GPIO Pin 9 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[21:20] |PIN10     |GPIO Pin 10 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[23:22] |PIN11     |GPIO Pin 11 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[25:24] |PIN12     |GPIO Pin 12 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[27:26] |PIN13     |GPIO Pin 13 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[29:28] |PIN14     |GPIO Pin 14 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * |[31:30] |PIN15     |GPIO Pin 15 Security Attribution Bits
     * |        |          |00 = Set to TZS.
     * |        |          |01 = Set to TZNS.
     * |        |          |10 = Reserved.
     * |        |          |11 = Set to SubM.
     * @var SSPCC_T::SVIEN
     * Offset: 0xF0  Security Violation Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0      |APB0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of APB0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of APB0 Enabled.
     * |[1]     |APB3      |APB3 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of APB3 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of APB3 Enabled.
     * |[2]     |SRAM1     |SRAM1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SRAM1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SRAM1 Enabled.
     * |[3]     |SDH0      |SD Host0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SD host 0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SD host 0 Enabled.
     * |[4]     |SDH1      |SD Host1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of SD host 1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of SD host 1 Enabled.
     * |[5]     |HSUSBD    |HighSpeed USB Device Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of HighSpeed USB Device Disabled.
     * |        |          |1 = Interrupt triggered from security violation of HighSpeed USB Device Enabled.
     * |[6]     |NANDC     |NAND Controller Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of NAND Controller Disabled.
     * |        |          |1 = Interrupt triggered from security violation of NAND Controller Enabled.
     * |[7]     |PDMA0     |PDMA0 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of PDMA0 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of PDMA0 Enabled.
     * |[8]     |PDMA1     |PDMA1 Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of PDMA1 Disabled.
     * |        |          |1 = Interrupt triggered from security violation of PDMA1 Enabled.
     * |[9]     |TRNG      |TRNG Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of TRNG Disabled.
     * |        |          |1 = Interrupt triggered from security violation of TRNG Enabled.
     * |[10]    |CRYPTO    |CRYPTO Security Violation Interrupt Enable Bit
     * |        |          |0 = Interrupt triggered from security violation of CRYPTO Disabled.
     * |        |          |1 = Interrupt triggered from security violation of CRYPTO Enabled.
     * @var SSPCC_T::SVINTSTS
     * Offset: 0xF4  Security Violation Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |APB0      |APB0 Security Violation Interrupt Status
     * |        |          |0 = No APB0 violation interrupt event.
     * |        |          |1 = There is APB0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[1]     |APB3      |APB3 Security Violation Interrupt Status
     * |        |          |0 = No APB3 violation interrupt event.
     * |        |          |1 = There is APB3 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[2]     |SRAM1     |SRAM1 Security Violation Interrupt Status
     * |        |          |0 = No SRAM1 violation interrupt event.
     * |        |          |1 = There is SRAM1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[3]     |SDH0      |SDH0 Security Violation Interrupt Status
     * |        |          |0 = No SDH0 violation interrupt event.
     * |        |          |1 = There is SDH0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[4]     |SDH1      |SDH1 Security Violation Interrupt Status
     * |        |          |0 = No SDH1 violation interrupt event.
     * |        |          |1 = There is SDH1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[5]     |HSUSBD    |High-speed USB Device Security Violation Interrupt Status
     * |        |          |0 = No High-speed USB Device violation interrupt event.
     * |        |          |1 = There is High-speed USB Device violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[6]     |NANDC     |NAND Controller Security Violation Interrupt Status
     * |        |          |0 = No NAND Controller violation interrupt event.
     * |        |          |1 = There is NAND Controller violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[7]     |PDMA0     |PDMA0 Security Violation Interrupt Status
     * |        |          |0 = No PDMA0 violation interrupt event.
     * |        |          |1 = There is PDMA0 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[8]     |PDMA1     |PDMA1 Security Violation Interrupt Status
     * |        |          |0 = No PDMA1 violation interrupt event.
     * |        |          |1 = There is PDMA1 violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[9]     |TRNG      |TRNG Security Violation Interrupt Status
     * |        |          |0 = No TRNG violation interrupt event.
     * |        |          |1 = There is TRNG violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * |[10]    |CRYPTO    |CRYPTO Security Violation Interrupt Status
     * |        |          |0 = No CRYPTO violation interrupt event.
     * |        |          |1 = There is CRYPTO violation interrupt event.
     * |        |          |Note: Write 1 to clear the interrupt flag.
     * @var SSPCC_T::APB0VSRC
     * Offset: 0x100  APB0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::APB3VSRC
     * Offset: 0x104  APB3 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::SRAM1VSRC
     * Offset: 0x108  SRAM1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::SDH0VSRC
     * Offset: 0x10C  SDH0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::SDH1VSRC
     * Offset: 0x110  SDH1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::HSUSBDVSRC
     * Offset: 0x114  HSUSBD Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::NANDCVSRC
     * Offset: 0x118  NANDC Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::PDMA0VSRC
     * Offset: 0x11C  PDMA0 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::PDMA1VSRC
     * Offset: 0x120  PDMA1 Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::TRNGVSRC
     * Offset: 0x124  TRNG Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::CRYPTOVSRC
     * Offset: 0x128  CRYPTO Security Policy Violation Source
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |MASTER    |Master Violating Security Policy
     * |        |          |Indicate which master invokes the security violation.
     * |        |          |0x0 = CA35.
     * |        |          |0x1 = CoreSight AP.
     * |        |          |0x3 =  Crypto Engine
     * |        |          |0x2 = CM4.
     * |        |          |0x4 = PDMA0.
     * |        |          |0x5 = PDMA1.
     * |        |          |0x6 = PDMA2.
     * |        |          |0x7 = PDMA3.
     * |        |          |0x8 = SDH0.
     * |        |          |0x9 = SDH1.
     * |        |          |0xA = USBH2.
     * |        |          |0xB = USBH0/HSUSBH0.
     * |        |          |0xC = USBH1/HSUSBH1.
     * |        |          |0xD = HSUSBD.
     * |        |          |0xE = NAND.
     * |        |          |Others is undefined.
     * @var SSPCC_T::APB0VA
     * Offset: 0x180  APB0 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::APB3VA
     * Offset: 0x184  APB3 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::SRAM1VA
     * Offset: 0x188  SRAM1 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::SDH0VA
     * Offset: 0x18C  SDH0 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::SDH1VA
     * Offset: 0x190  SDH1 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::HSUSBDVA
     * Offset: 0x194  HSUSBD Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::NANDCVA
     * Offset: 0x198  NANDC Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::PDMA0VA
     * Offset: 0x19C  PDMA0 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::PDMA1VA
     * Offset: 0x1A0  PDMA1 Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::TRNGVA
     * Offset: 0x1A4  TRNG Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::CRYPTOVA
     * Offset: 0x1A8  CRYPTO Security Policy Violation Address
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |VIOADDR   |Violation Address
     * |        |          |Indicate the target address of the access, which invokes the security violation.
     * @var SSPCC_T::SINFAEN
     * Offset: 0x200  Shared Information Access Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SSPCCSIAEN|SSPCC Shared Information Access Enable Bit
     * |        |          |0 = SSPCC shared information Disabled.
     * |        |          |1 = SSPCC shared information Enabled.
     * |[1]     |SYSSIAEN  |SYS Shared Information Access Enable Bit
     * |        |          |0 = SYS shared information Disabled.
     * |        |          |1 = SYS shared information Enabled.
     * |        |          |Note: Include clock information.
     * |[2]     |RTCSIAEN  |RTC Shared Information Access Enable Bit
     * |        |          |0 = RTC shared information Disabled.
     * |        |          |1 = RTC shared information Enabled.
     * |[6]     |OTPSIAEN  |OTP Controller Shared Information Access Enable Bit
     * |        |          |0 = OTP controller shared information Disabled.
     * |        |          |1 = OTP controller shared information Enabled.
     * |[7]     |KSSIAEN   |Key Store Shared Information Access Enable Bit
     * |        |          |0 = Key Store shared information Disabled.
     * |        |          |1 = Key Store shared information Enabled.
     * @var SSPCC_T::SCWP
     * Offset: 0x204  Security Configuration Write Protection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ENABLE    |Write Protection Enable Bit
     * |        |          |0 = Write Protection Disabled.
     * |        |          |1 = Write Protection Enabled.
     * |[1]     |LOCK      |Enable Write Protection Lock Bit (Write Once)
     * |        |          |0 = Write protection lock Disabled.
     * |        |          |1 = Write protection Enabled and locked.
     * |        |          |Note: This bit cannot be cleared to 0 after set to 1.
     * |[31:16] |WVCODE    |Write Verify Code
     * |        |          |Read operation:
     * |        |          |Reserved, all zeros.
     * |        |          |Write operation:
     * |        |          |0x475A = The write verify code, 0x475A, is needed to do a valid write to SSPCC_SCWP.
     * |        |          |Others = Invalid write verify code.
     */
    __IO uint32_t PSSET0;                /*!< [0x0000] Peripheral Security Attribution Set Register 0 (0x4000_0000~0x400F_FFFF) */
    __IO uint32_t PSSET1;                /*!< [0x0004] Peripheral Security Attribution Set Register 1 (0x4010_0000~0x401F_FFFF) */
    __IO uint32_t PSSET2;                /*!< [0x0008] Peripheral Security Attribution Set Register 2 (0x4020_0000~0x402F_FFFF) */
    __IO uint32_t PSSET3;                /*!< [0x000c] Peripheral Security Attribution Set Register 3 (0x4030_0000~0x403F_FFFF) */
    __IO uint32_t PSSET4;                /*!< [0x0010] Peripheral Security Attribution Set Register 4 (0x4040_0000~0x404F_FFFF) */
    __IO uint32_t PSSET5;                /*!< [0x0014] Peripheral Security Attribution Set Register 5 (0x4050_0000~0x405F_FFFF) */
    __IO uint32_t PSSET6;                /*!< [0x0018] Peripheral Security Attribution Set Register 6 (0x4060_0000~0x406F_FFFF) */
    __IO uint32_t PSSET7;                /*!< [0x001c] Peripheral Security Attribution Set Register 7 (0x4070_0000~0x407F_FFFF) */
    __IO uint32_t PSSET8;                /*!< [0x0020] Peripheral Security Attribution Set Register 8 (0x4080_0000~0x408F_FFFF) */
    __IO uint32_t PSSET9;                /*!< [0x0024] Peripheral Security Attribution Set Register 9 (0x4090_0000~0x409F_FFFF) */
    __IO uint32_t PSSET10;               /*!< [0x0028] Peripheral Security Attribution Set Register 10 (0x40A0_0000~0x40AF_FFFF) */
    __IO uint32_t PSSET11;               /*!< [0x002c] Peripheral Security Attribution Set Register 11 (0x40B0_0000~0x40BF_FFFF) */
    __I  uint32_t RESERVE0[4];
    __IO uint32_t SRAMSB;                /*!< [0x0040] SRAM Security Boundary Set Register                              */
    __I  uint32_t RESERVE1[3];
    __IO uint32_t EBISSET;               /*!< [0x0050] EBI Memory Security Set Register                                 */
    __I  uint32_t RESERVE2[3];
    __IO uint32_t IOASSET;               /*!< [0x0060] GPIO Port A Security Attribution Set Register                    */
    __IO uint32_t IOBSSET;               /*!< [0x0064] GPIO Port B Security Attribution Set Register                    */
    __IO uint32_t IOCSSET;               /*!< [0x0068] GPIO Port C Security Attribution Set Register                    */
    __IO uint32_t IODSSET;               /*!< [0x006c] GPIO Port D Security Attribution Set Register                    */
    __IO uint32_t IOESSET;               /*!< [0x0070] GPIO Port E Security Attribution Set Register                    */
    __IO uint32_t IOFSSET;               /*!< [0x0074] GPIO Port F Security Attribution Set Register                    */
    __IO uint32_t IOGSSET;               /*!< [0x0078] GPIO Port G Security Attribution Set Register                    */
    __IO uint32_t IOHSSET;               /*!< [0x007c] GPIO Port H Security Attribution Set Register                    */
    __IO uint32_t IOISSET;               /*!< [0x0080] GPIO Port I Security Attribution Set Register                    */
    __IO uint32_t IOJSSET;               /*!< [0x0084] GPIO Port J Security Attribution Set Register                    */
    __IO uint32_t IOKSSET;               /*!< [0x0088] GPIO Port K Security Attribution Set Register                    */
    __IO uint32_t IOLSSET;               /*!< [0x008c] GPIO Port L Security Attribution Set Register                    */
    __IO uint32_t IOMSSET;               /*!< [0x0090] GPIO Port M Security Attribution Set Register                    */
    __IO uint32_t IONSSET;               /*!< [0x0094] GPIO Port N Security Attribution Set Register                    */
    __I  uint32_t RESERVE3[22];
    __IO uint32_t SVIEN;                 /*!< [0x00f0] Security Violation Interrupt Enable Register                     */
    __IO uint32_t SVINTSTS;              /*!< [0x00f4] Security Violation Interrupt Status Register                     */
    __I  uint32_t RESERVE4[2];
    __I  uint32_t APB0VSRC;              /*!< [0x0100] APB0 Security Policy Violation Source                            */
    __I  uint32_t APB3VSRC;              /*!< [0x0104] APB3 Security Policy Violation Source                            */
    __I  uint32_t SRAM1VSRC;             /*!< [0x0108] SRAM1 Security Policy Violation Source                           */
    __I  uint32_t SDH0VSRC;              /*!< [0x010c] SDH0 Security Policy Violation Source                            */
    __I  uint32_t SDH1VSRC;              /*!< [0x0110] SDH1 Security Policy Violation Source                            */
    __I  uint32_t HSUSBDVSRC;            /*!< [0x0114] HSUSBD Security Policy Violation Source                          */
    __I  uint32_t NANDCVSRC;             /*!< [0x0118] NANDC Security Policy Violation Source                           */
    __I  uint32_t PDMA0VSRC;             /*!< [0x011c] PDMA0 Security Policy Violation Source                           */
    __I  uint32_t PDMA1VSRC;             /*!< [0x0120] PDMA1 Security Policy Violation Source                           */
    __I  uint32_t TRNGVSRC;              /*!< [0x0124] TRNG Security Policy Violation Source                            */
    __I  uint32_t CRYPTOVSRC;            /*!< [0x0128] CRYPTO Security Policy Violation Source                          */
    __I  uint32_t RESERVE5[21];
    __I  uint32_t APB0VA;                /*!< [0x0180] APB0 Security Policy Violation Address                           */
    __I  uint32_t APB3VA;                /*!< [0x0184] APB3 Security Policy Violation Address                           */
    __I  uint32_t SRAM1VA;               /*!< [0x0188] SRAM1 Security Policy Violation Address                          */
    __I  uint32_t SDH0VA;                /*!< [0x018c] SDH0 Security Policy Violation Address                           */
    __I  uint32_t SDH1VA;                /*!< [0x0190] SDH1 Security Policy Violation Address                           */
    __I  uint32_t HSUSBDVA;              /*!< [0x0194] HSUSBD Security Policy Violation Address                         */
    __I  uint32_t NANDCVA;               /*!< [0x0198] NANDC Security Policy Violation Address                          */
    __I  uint32_t PDMA0VA;               /*!< [0x019c] PDMA0 Security Policy Violation Address                          */
    __I  uint32_t PDMA1VA;               /*!< [0x01a0] PDMA1 Security Policy Violation Address                          */
    __I  uint32_t TRNGVA;                /*!< [0x01a4] TRNG Security Policy Violation Address                           */
    __I  uint32_t CRYPTOVA;              /*!< [0x01a8] CRYPTO Security Policy Violation Address                         */
    __I  uint32_t RESERVE6[21];
    __IO uint32_t SINFAEN;               /*!< [0x0200] Shared Information Access Enable Register                        */
    __IO uint32_t SCWP;                  /*!< [0x0204] Security Configuration Write Protection Register                 */

} SSPCC_T;

/**
    @addtogroup SSPCC_CONST SSPCC Bit Field Definition
    Constant Definitions for SSPCC Controller
@{ */

#define SSPCC_PSSET0_PDMA0_Pos           (16)                                              /*!< SSPCC_T::PSSET0: PDMA0 Position        */
#define SSPCC_PSSET0_PDMA0_Msk           (0x3ul << SSPCC_PSSET0_PDMA0_Pos)                 /*!< SSPCC_T::PSSET0: PDMA0 Mask            */

#define SSPCC_PSSET0_PDMA1_Pos           (18)                                              /*!< SSPCC_T::PSSET0: PDMA1 Position        */
#define SSPCC_PSSET0_PDMA1_Msk           (0x3ul << SSPCC_PSSET0_PDMA1_Pos)                 /*!< SSPCC_T::PSSET0: PDMA1 Mask            */

#define SSPCC_PSSET0_PDMA2_Pos           (20)                                              /*!< SSPCC_T::PSSET0: PDMA2 Position        */
#define SSPCC_PSSET0_PDMA2_Msk           (0x3ul << SSPCC_PSSET0_PDMA2_Pos)                 /*!< SSPCC_T::PSSET0: PDMA2 Mask            */

#define SSPCC_PSSET0_PDMA3_Pos           (22)                                              /*!< SSPCC_T::PSSET0: PDMA3 Position        */
#define SSPCC_PSSET0_PDMA3_Msk           (0x3ul << SSPCC_PSSET0_PDMA3_Pos)                 /*!< SSPCC_T::PSSET0: PDMA3 Mask            */

#define SSPCC_PSSET1_EBI_Pos             (0)                                               /*!< SSPCC_T::PSSET1: EBI Position          */
#define SSPCC_PSSET1_EBI_Msk             (0x3ul << SSPCC_PSSET1_EBI_Pos)                   /*!< SSPCC_T::PSSET1: EBI Mask              */

#define SSPCC_PSSET1_SDH0_Pos            (16)                                              /*!< SSPCC_T::PSSET1: SDH0 Position         */
#define SSPCC_PSSET1_SDH0_Msk            (0x3ul << SSPCC_PSSET1_SDH0_Pos)                  /*!< SSPCC_T::PSSET1: SDH0 Mask             */

#define SSPCC_PSSET1_SDH1_Pos            (18)                                              /*!< SSPCC_T::PSSET1: SDH1 Position         */
#define SSPCC_PSSET1_SDH1_Msk            (0x3ul << SSPCC_PSSET1_SDH1_Pos)                  /*!< SSPCC_T::PSSET1: SDH1 Mask             */

#define SSPCC_PSSET1_NANDC_Pos           (20)                                              /*!< SSPCC_T::PSSET1: NANDC Position        */
#define SSPCC_PSSET1_NANDC_Msk           (0x3ul << SSPCC_PSSET1_NANDC_Pos)                 /*!< SSPCC_T::PSSET1: NANDC Mask            */

#define SSPCC_PSSET2_HSUSBD_Pos          (0)                                               /*!< SSPCC_T::PSSET2: HSUSBD Position       */
#define SSPCC_PSSET2_HSUSBD_Msk          (0x3ul << SSPCC_PSSET2_HSUSBD_Pos)                /*!< SSPCC_T::PSSET2: HSUSBD Mask           */

#define SSPCC_PSSET3_CRYPTO_Pos          (0)                                               /*!< SSPCC_T::PSSET3: CRYPTO Position       */
#define SSPCC_PSSET3_CRYPTO_Msk          (0x3ul << SSPCC_PSSET3_CRYPTO_Pos)                /*!< SSPCC_T::PSSET3: CRYPTO Mask           */

#define SSPCC_PSSET3_CANFD0_Pos          (24)                                              /*!< SSPCC_T::PSSET3: CANFD0 Position       */
#define SSPCC_PSSET3_CANFD0_Msk          (0x3ul << SSPCC_PSSET3_CANFD0_Pos)                /*!< SSPCC_T::PSSET3: CANFD0 Mask           */

#define SSPCC_PSSET3_CANFD1_Pos          (26)                                              /*!< SSPCC_T::PSSET3: CANFD1 Position       */
#define SSPCC_PSSET3_CANFD1_Msk          (0x3ul << SSPCC_PSSET3_CANFD1_Pos)                /*!< SSPCC_T::PSSET3: CANFD1 Mask           */

#define SSPCC_PSSET3_CANFD2_Pos          (28)                                              /*!< SSPCC_T::PSSET3: CANFD2 Position       */
#define SSPCC_PSSET3_CANFD2_Msk          (0x3ul << SSPCC_PSSET3_CANFD2_Pos)                /*!< SSPCC_T::PSSET3: CANFD2 Mask           */

#define SSPCC_PSSET3_CANFD3_Pos          (30)                                              /*!< SSPCC_T::PSSET3: CANFD3 Position       */
#define SSPCC_PSSET3_CANFD3_Msk          (0x3ul << SSPCC_PSSET3_CANFD3_Pos)                /*!< SSPCC_T::PSSET3: CANFD3 Mask           */

#define SSPCC_PSSET4_ADC0_Pos            (4)                                               /*!< SSPCC_T::PSSET4: ADC0 Position         */
#define SSPCC_PSSET4_ADC0_Msk            (0x3ul << SSPCC_PSSET4_ADC0_Pos)                  /*!< SSPCC_T::PSSET4: ADC0 Mask             */

#define SSPCC_PSSET4_EADC0_Pos           (6)                                               /*!< SSPCC_T::PSSET4: EADC0 Position        */
#define SSPCC_PSSET4_EADC0_Msk           (0x3ul << SSPCC_PSSET4_EADC0_Pos)                 /*!< SSPCC_T::PSSET4: EADC0 Mask            */

#define SSPCC_PSSET4_WDTWWDT1_Pos        (8)                                               /*!< SSPCC_T::PSSET4: WDTWWDT1 Position     */
#define SSPCC_PSSET4_WDTWWDT1_Msk        (0x3ul << SSPCC_PSSET4_WDTWWDT1_Pos)              /*!< SSPCC_T::PSSET4: WDTWWDT1 Mask         */

#define SSPCC_PSSET4_I2S0_Pos            (16)                                              /*!< SSPCC_T::PSSET4: I2S0 Position         */
#define SSPCC_PSSET4_I2S0_Msk            (0x3ul << SSPCC_PSSET4_I2S0_Pos)                  /*!< SSPCC_T::PSSET4: I2S0 Mask             */

#define SSPCC_PSSET4_I2S1_Pos            (18)                                              /*!< SSPCC_T::PSSET4: I2S1 Position         */
#define SSPCC_PSSET4_I2S1_Msk            (0x3ul << SSPCC_PSSET4_I2S1_Pos)                  /*!< SSPCC_T::PSSET4: I2S1 Mask             */

#define SSPCC_PSSET4_KPI_Pos             (20)                                              /*!< SSPCC_T::PSSET4: KPI Position          */
#define SSPCC_PSSET4_KPI_Msk             (0x3ul << SSPCC_PSSET4_KPI_Pos)                   /*!< SSPCC_T::PSSET4: KPI Mask              */

#define SSPCC_PSSET4_DDRPHYPUB_Pos       (24)                                              /*!< SSPCC_T::PSSET4: DDRPHYPUB Position    */
#define SSPCC_PSSET4_DDRPHYPUB_Msk       (0x3ul << SSPCC_PSSET4_DDRPHYPUB_Pos)             /*!< SSPCC_T::PSSET4: DDRPHYPUB Mask        */

#define SSPCC_PSSET4_MCTL_Pos            (26)                                              /*!< SSPCC_T::PSSET4: MCTL Position         */
#define SSPCC_PSSET4_MCTL_Msk            (0x3ul << SSPCC_PSSET4_MCTL_Pos)                  /*!< SSPCC_T::PSSET4: MCTL Mask             */

#define SSPCC_PSSET5_TMR01_Pos           (0)                                               /*!< SSPCC_T::PSSET5: TMR01 Position        */
#define SSPCC_PSSET5_TMR01_Msk           (0x3ul << SSPCC_PSSET5_TMR01_Pos)                 /*!< SSPCC_T::PSSET5: TMR01 Mask            */

#define SSPCC_PSSET5_TMR23_Pos           (2)                                               /*!< SSPCC_T::PSSET5: TMR23 Position        */
#define SSPCC_PSSET5_TMR23_Msk           (0x3ul << SSPCC_PSSET5_TMR23_Pos)                 /*!< SSPCC_T::PSSET5: TMR23 Mask            */

#define SSPCC_PSSET5_TMR45_Pos           (4)                                               /*!< SSPCC_T::PSSET5: TMR45 Position        */
#define SSPCC_PSSET5_TMR45_Msk           (0x3ul << SSPCC_PSSET5_TMR45_Pos)                 /*!< SSPCC_T::PSSET5: TMR45 Mask            */

#define SSPCC_PSSET5_TMR67_Pos           (6)                                               /*!< SSPCC_T::PSSET5: TMR67 Position        */
#define SSPCC_PSSET5_TMR67_Msk           (0x3ul << SSPCC_PSSET5_TMR67_Pos)                 /*!< SSPCC_T::PSSET5: TMR67 Mask            */

#define SSPCC_PSSET5_TMR89_Pos           (8)                                               /*!< SSPCC_T::PSSET5: TMR89 Position        */
#define SSPCC_PSSET5_TMR89_Msk           (0x3ul << SSPCC_PSSET5_TMR89_Pos)                 /*!< SSPCC_T::PSSET5: TMR89 Mask            */

#define SSPCC_PSSET5_TMR1011_Pos         (10)                                              /*!< SSPCC_T::PSSET5: TMR1011 Position      */
#define SSPCC_PSSET5_TMR1011_Msk         (0x3ul << SSPCC_PSSET5_TMR1011_Pos)               /*!< SSPCC_T::PSSET5: TMR1011 Mask          */

#define SSPCC_PSSET5_EPWM0_Pos           (16)                                              /*!< SSPCC_T::PSSET5: EPWM0 Position        */
#define SSPCC_PSSET5_EPWM0_Msk           (0x3ul << SSPCC_PSSET5_EPWM0_Pos)                 /*!< SSPCC_T::PSSET5: EPWM0 Mask            */

#define SSPCC_PSSET5_EPWM1_Pos           (18)                                              /*!< SSPCC_T::PSSET5: EPWM1 Position        */
#define SSPCC_PSSET5_EPWM1_Msk           (0x3ul << SSPCC_PSSET5_EPWM1_Pos)                 /*!< SSPCC_T::PSSET5: EPWM1 Mask            */

#define SSPCC_PSSET5_EPWM2_Pos           (20)                                              /*!< SSPCC_T::PSSET5: EPWM2 Position        */
#define SSPCC_PSSET5_EPWM2_Msk           (0x3ul << SSPCC_PSSET5_EPWM2_Pos)                 /*!< SSPCC_T::PSSET5: EPWM2 Mask            */

#define SSPCC_PSSET6_SPI0_Pos            (0)                                               /*!< SSPCC_T::PSSET6: SPI0 Position         */
#define SSPCC_PSSET6_SPI0_Msk            (0x3ul << SSPCC_PSSET6_SPI0_Pos)                  /*!< SSPCC_T::PSSET6: SPI0 Mask             */

#define SSPCC_PSSET6_SPI1_Pos            (2)                                               /*!< SSPCC_T::PSSET6: SPI1 Position         */
#define SSPCC_PSSET6_SPI1_Msk            (0x3ul << SSPCC_PSSET6_SPI1_Pos)                  /*!< SSPCC_T::PSSET6: SPI1 Mask             */

#define SSPCC_PSSET6_SPI2_Pos            (4)                                               /*!< SSPCC_T::PSSET6: SPI2 Position         */
#define SSPCC_PSSET6_SPI2_Msk            (0x3ul << SSPCC_PSSET6_SPI2_Pos)                  /*!< SSPCC_T::PSSET6: SPI2 Mask             */

#define SSPCC_PSSET6_SPI3_Pos            (6)                                               /*!< SSPCC_T::PSSET6: SPI3 Position         */
#define SSPCC_PSSET6_SPI3_Msk            (0x3ul << SSPCC_PSSET6_SPI3_Pos)                  /*!< SSPCC_T::PSSET6: SPI3 Mask             */

#define SSPCC_PSSET6_QSPI0_Pos           (16)                                              /*!< SSPCC_T::PSSET6: QSPI0 Position        */
#define SSPCC_PSSET6_QSPI0_Msk           (0x3ul << SSPCC_PSSET6_QSPI0_Pos)                 /*!< SSPCC_T::PSSET6: QSPI0 Mask            */

#define SSPCC_PSSET6_QSPI1_Pos           (18)                                              /*!< SSPCC_T::PSSET6: QSPI1 Position        */
#define SSPCC_PSSET6_QSPI1_Msk           (0x3ul << SSPCC_PSSET6_QSPI1_Pos)                 /*!< SSPCC_T::PSSET6: QSPI1 Mask            */

#define SSPCC_PSSET7_UART0_Pos           (0)                                               /*!< SSPCC_T::PSSET7: UART0 Position        */
#define SSPCC_PSSET7_UART0_Msk           (0x3ul << SSPCC_PSSET7_UART0_Pos)                 /*!< SSPCC_T::PSSET7: UART0 Mask            */

#define SSPCC_PSSET7_UART1_Pos           (2)                                               /*!< SSPCC_T::PSSET7: UART1 Position        */
#define SSPCC_PSSET7_UART1_Msk           (0x3ul << SSPCC_PSSET7_UART1_Pos)                 /*!< SSPCC_T::PSSET7: UART1 Mask            */

#define SSPCC_PSSET7_UART2_Pos           (4)                                               /*!< SSPCC_T::PSSET7: UART2 Position        */
#define SSPCC_PSSET7_UART2_Msk           (0x3ul << SSPCC_PSSET7_UART2_Pos)                 /*!< SSPCC_T::PSSET7: UART2 Mask            */

#define SSPCC_PSSET7_UART3_Pos           (6)                                               /*!< SSPCC_T::PSSET7: UART3 Position        */
#define SSPCC_PSSET7_UART3_Msk           (0x3ul << SSPCC_PSSET7_UART3_Pos)                 /*!< SSPCC_T::PSSET7: UART3 Mask            */

#define SSPCC_PSSET7_UART4_Pos           (8)                                               /*!< SSPCC_T::PSSET7: UART4 Position        */
#define SSPCC_PSSET7_UART4_Msk           (0x3ul << SSPCC_PSSET7_UART4_Pos)                 /*!< SSPCC_T::PSSET7: UART4 Mask            */

#define SSPCC_PSSET7_UART5_Pos           (10)                                              /*!< SSPCC_T::PSSET7: UART5 Position        */
#define SSPCC_PSSET7_UART5_Msk           (0x3ul << SSPCC_PSSET7_UART5_Pos)                 /*!< SSPCC_T::PSSET7: UART5 Mask            */

#define SSPCC_PSSET7_UART6_Pos           (12)                                              /*!< SSPCC_T::PSSET7: UART6 Position        */
#define SSPCC_PSSET7_UART6_Msk           (0x3ul << SSPCC_PSSET7_UART6_Pos)                 /*!< SSPCC_T::PSSET7: UART6 Mask            */

#define SSPCC_PSSET7_UART7_Pos           (14)                                              /*!< SSPCC_T::PSSET7: UART7 Position        */
#define SSPCC_PSSET7_UART7_Msk           (0x3ul << SSPCC_PSSET7_UART7_Pos)                 /*!< SSPCC_T::PSSET7: UART7 Mask            */

#define SSPCC_PSSET7_UART8_Pos           (16)                                              /*!< SSPCC_T::PSSET7: UART8 Position        */
#define SSPCC_PSSET7_UART8_Msk           (0x3ul << SSPCC_PSSET7_UART8_Pos)                 /*!< SSPCC_T::PSSET7: UART8 Mask            */

#define SSPCC_PSSET7_UART9_Pos           (18)                                              /*!< SSPCC_T::PSSET7: UART9 Position        */
#define SSPCC_PSSET7_UART9_Msk           (0x3ul << SSPCC_PSSET7_UART9_Pos)                 /*!< SSPCC_T::PSSET7: UART9 Mask            */

#define SSPCC_PSSET7_UART10_Pos          (20)                                              /*!< SSPCC_T::PSSET7: UART10 Position       */
#define SSPCC_PSSET7_UART10_Msk          (0x3ul << SSPCC_PSSET7_UART10_Pos)                /*!< SSPCC_T::PSSET7: UART10 Mask           */

#define SSPCC_PSSET7_UART11_Pos          (22)                                              /*!< SSPCC_T::PSSET7: UART11 Position       */
#define SSPCC_PSSET7_UART11_Msk          (0x3ul << SSPCC_PSSET7_UART11_Pos)                /*!< SSPCC_T::PSSET7: UART11 Mask           */

#define SSPCC_PSSET7_UART12_Pos          (24)                                              /*!< SSPCC_T::PSSET7: UART12 Position       */
#define SSPCC_PSSET7_UART12_Msk          (0x3ul << SSPCC_PSSET7_UART12_Pos)                /*!< SSPCC_T::PSSET7: UART12 Mask           */

#define SSPCC_PSSET7_UART13_Pos          (26)                                              /*!< SSPCC_T::PSSET7: UART13 Position       */
#define SSPCC_PSSET7_UART13_Msk          (0x3ul << SSPCC_PSSET7_UART13_Pos)                /*!< SSPCC_T::PSSET7: UART13 Mask           */

#define SSPCC_PSSET7_UART14_Pos          (28)                                              /*!< SSPCC_T::PSSET7: UART14 Position       */
#define SSPCC_PSSET7_UART14_Msk          (0x3ul << SSPCC_PSSET7_UART14_Pos)                /*!< SSPCC_T::PSSET7: UART14 Mask           */

#define SSPCC_PSSET7_UART15_Pos          (30)                                              /*!< SSPCC_T::PSSET7: UART15 Position       */
#define SSPCC_PSSET7_UART15_Msk          (0x3ul << SSPCC_PSSET7_UART15_Pos)                /*!< SSPCC_T::PSSET7: UART15 Mask           */

#define SSPCC_PSSET8_I2C0_Pos            (0)                                               /*!< SSPCC_T::PSSET8: I2C0 Position         */
#define SSPCC_PSSET8_I2C0_Msk            (0x3ul << SSPCC_PSSET8_I2C0_Pos)                  /*!< SSPCC_T::PSSET8: I2C0 Mask             */

#define SSPCC_PSSET8_I2C1_Pos            (2)                                               /*!< SSPCC_T::PSSET8: I2C1 Position         */
#define SSPCC_PSSET8_I2C1_Msk            (0x3ul << SSPCC_PSSET8_I2C1_Pos)                  /*!< SSPCC_T::PSSET8: I2C1 Mask             */

#define SSPCC_PSSET8_I2C2_Pos            (4)                                               /*!< SSPCC_T::PSSET8: I2C2 Position         */
#define SSPCC_PSSET8_I2C2_Msk            (0x3ul << SSPCC_PSSET8_I2C2_Pos)                  /*!< SSPCC_T::PSSET8: I2C2 Mask             */

#define SSPCC_PSSET8_I2C3_Pos            (6)                                               /*!< SSPCC_T::PSSET8: I2C3 Position         */
#define SSPCC_PSSET8_I2C3_Msk            (0x3ul << SSPCC_PSSET8_I2C3_Pos)                  /*!< SSPCC_T::PSSET8: I2C3 Mask             */

#define SSPCC_PSSET8_I2C4_Pos            (8)                                               /*!< SSPCC_T::PSSET8: I2C4 Position         */
#define SSPCC_PSSET8_I2C4_Msk            (0x3ul << SSPCC_PSSET8_I2C4_Pos)                  /*!< SSPCC_T::PSSET8: I2C4 Mask             */

#define SSPCC_PSSET8_I2C5_Pos            (10)                                              /*!< SSPCC_T::PSSET8: I2C5 Position         */
#define SSPCC_PSSET8_I2C5_Msk            (0x3ul << SSPCC_PSSET8_I2C5_Pos)                  /*!< SSPCC_T::PSSET8: I2C5 Mask             */

#define SSPCC_PSSET8_UART16_Pos          (16)                                              /*!< SSPCC_T::PSSET8: UART16 Position       */
#define SSPCC_PSSET8_UART16_Msk          (0x3ul << SSPCC_PSSET8_UART16_Pos)                /*!< SSPCC_T::PSSET8: UART16 Mask           */

#define SSPCC_PSSET9_SC0_Pos             (0)                                               /*!< SSPCC_T::PSSET9: SC0 Position          */
#define SSPCC_PSSET9_SC0_Msk             (0x3ul << SSPCC_PSSET9_SC0_Pos)                   /*!< SSPCC_T::PSSET9: SC0 Mask              */

#define SSPCC_PSSET9_SC1_Pos             (2)                                               /*!< SSPCC_T::PSSET9: SC1 Position          */
#define SSPCC_PSSET9_SC1_Msk             (0x3ul << SSPCC_PSSET9_SC1_Pos)                   /*!< SSPCC_T::PSSET9: SC1 Mask              */

#define SSPCC_PSSET11_QEI0_Pos           (0)                                               /*!< SSPCC_T::PSSET11: QEI0 Position        */
#define SSPCC_PSSET11_QEI0_Msk           (0x3ul << SSPCC_PSSET11_QEI0_Pos)                 /*!< SSPCC_T::PSSET11: QEI0 Mask            */

#define SSPCC_PSSET11_QEI1_Pos           (2)                                               /*!< SSPCC_T::PSSET11: QEI1 Position        */
#define SSPCC_PSSET11_QEI1_Msk           (0x3ul << SSPCC_PSSET11_QEI1_Pos)                 /*!< SSPCC_T::PSSET11: QEI1 Mask            */

#define SSPCC_PSSET11_QEI2_Pos           (4)                                               /*!< SSPCC_T::PSSET11: QEI2 Position        */
#define SSPCC_PSSET11_QEI2_Msk           (0x3ul << SSPCC_PSSET11_QEI2_Pos)                 /*!< SSPCC_T::PSSET11: QEI2 Mask            */

#define SSPCC_PSSET11_ECAP0_Pos          (8)                                               /*!< SSPCC_T::PSSET11: ECAP0 Position       */
#define SSPCC_PSSET11_ECAP0_Msk          (0x3ul << SSPCC_PSSET11_ECAP0_Pos)                /*!< SSPCC_T::PSSET11: ECAP0 Mask           */

#define SSPCC_PSSET11_ECAP1_Pos          (10)                                              /*!< SSPCC_T::PSSET11: ECAP1 Position       */
#define SSPCC_PSSET11_ECAP1_Msk          (0x3ul << SSPCC_PSSET11_ECAP1_Pos)                /*!< SSPCC_T::PSSET11: ECAP1 Mask           */

#define SSPCC_PSSET11_ECAP2_Pos          (12)                                              /*!< SSPCC_T::PSSET11: ECAP2 Position       */
#define SSPCC_PSSET11_ECAP2_Msk          (0x3ul << SSPCC_PSSET11_ECAP2_Pos)                /*!< SSPCC_T::PSSET11: ECAP2 Mask           */

#define SSPCC_PSSET11_TRNG_Pos           (18)                                              /*!< SSPCC_T::PSSET11: TRNG Position        */
#define SSPCC_PSSET11_TRNG_Msk           (0x3ul << SSPCC_PSSET11_TRNG_Pos)                 /*!< SSPCC_T::PSSET11: TRNG Mask            */

#define SSPCC_SRAMSB_SR0BOUND_Pos        (0)                                               /*!< SSPCC_T::SRAMSB: SR0BOUND Position     */
#define SSPCC_SRAMSB_SR0BOUND_Msk        (0x1ful << SSPCC_SRAMSB_SR0BOUND_Pos)             /*!< SSPCC_T::SRAMSB: SR0BOUND Mask         */

#define SSPCC_SRAMSB_SR1BOUND_Pos        (8)                                               /*!< SSPCC_T::SRAMSB: SR1BOUND Position     */
#define SSPCC_SRAMSB_SR1BOUND_Msk        (0x1ful << SSPCC_SRAMSB_SR1BOUND_Pos)             /*!< SSPCC_T::SRAMSB: SR1BOUND Mask         */

#define SSPCC_EBISSET_BANK0_Pos          (0)                                               /*!< SSPCC_T::EBISSET: BANK0 Position       */
#define SSPCC_EBISSET_BANK0_Msk          (0x3ul << SSPCC_EBISSET_BANK0_Pos)                /*!< SSPCC_T::EBISSET: BANK0 Mask           */

#define SSPCC_EBISSET_BANK1_Pos          (2)                                               /*!< SSPCC_T::EBISSET: BANK1 Position       */
#define SSPCC_EBISSET_BANK1_Msk          (0x3ul << SSPCC_EBISSET_BANK1_Pos)                /*!< SSPCC_T::EBISSET: BANK1 Mask           */

#define SSPCC_EBISSET_BANK2_Pos          (4)                                               /*!< SSPCC_T::EBISSET: BANK2 Position       */
#define SSPCC_EBISSET_BANK2_Msk          (0x3ul << SSPCC_EBISSET_BANK2_Pos)                /*!< SSPCC_T::EBISSET: BANK2 Mask           */

#define SSPCC_IOxSSET_PIN0_Pos           (0)                                               /*!< SSPCC_T::IOxSSET: PIN0 Position        */
#define SSPCC_IOxSSET_PIN0_Msk           (0x3ul << SSPCC_IOxSSET_PIN0_Pos)                 /*!< SSPCC_T::IOxSSET: PIN0 Mask            */

#define SSPCC_IOxSSET_PIN1_Pos           (2)                                               /*!< SSPCC_T::IOxSSET: PIN1 Position        */
#define SSPCC_IOxSSET_PIN1_Msk           (0x3ul << SSPCC_IOxSSET_PIN1_Pos)                 /*!< SSPCC_T::IOxSSET: PIN1 Mask            */

#define SSPCC_IOxSSET_PIN2_Pos           (4)                                               /*!< SSPCC_T::IOxSSET: PIN2 Position        */
#define SSPCC_IOxSSET_PIN2_Msk           (0x3ul << SSPCC_IOxSSET_PIN2_Pos)                 /*!< SSPCC_T::IOxSSET: PIN2 Mask            */

#define SSPCC_IOxSSET_PIN3_Pos           (6)                                               /*!< SSPCC_T::IOxSSET: PIN3 Position        */
#define SSPCC_IOxSSET_PIN3_Msk           (0x3ul << SSPCC_IOxSSET_PIN3_Pos)                 /*!< SSPCC_T::IOxSSET: PIN3 Mask            */

#define SSPCC_IOxSSET_PIN4_Pos           (8)                                               /*!< SSPCC_T::IOxSSET: PIN4 Position        */
#define SSPCC_IOxSSET_PIN4_Msk           (0x3ul << SSPCC_IOxSSET_PIN4_Pos)                 /*!< SSPCC_T::IOxSSET: PIN4 Mask            */

#define SSPCC_IOxSSET_PIN5_Pos           (10)                                              /*!< SSPCC_T::IOxSSET: PIN5 Position        */
#define SSPCC_IOxSSET_PIN5_Msk           (0x3ul << SSPCC_IOxSSET_PIN5_Pos)                 /*!< SSPCC_T::IOxSSET: PIN5 Mask            */

#define SSPCC_IOxSSET_PIN6_Pos           (12)                                              /*!< SSPCC_T::IOxSSET: PIN6 Position        */
#define SSPCC_IOxSSET_PIN6_Msk           (0x3ul << SSPCC_IOxSSET_PIN6_Pos)                 /*!< SSPCC_T::IOxSSET: PIN6 Mask            */

#define SSPCC_IOxSSET_PIN7_Pos           (14)                                              /*!< SSPCC_T::IOxSSET: PIN7 Position        */
#define SSPCC_IOxSSET_PIN7_Msk           (0x3ul << SSPCC_IOxSSET_PIN7_Pos)                 /*!< SSPCC_T::IOxSSET: PIN7 Mask            */

#define SSPCC_IOxSSET_PIN8_Pos           (16)                                              /*!< SSPCC_T::IOxSSET: PIN8 Position        */
#define SSPCC_IOxSSET_PIN8_Msk           (0x3ul << SSPCC_IOxSSET_PIN8_Pos)                 /*!< SSPCC_T::IOxSSET: PIN8 Mask            */

#define SSPCC_IOxSSET_PIN9_Pos           (18)                                              /*!< SSPCC_T::IOxSSET: PIN9 Position        */
#define SSPCC_IOxSSET_PIN9_Msk           (0x3ul << SSPCC_IOxSSET_PIN9_Pos)                 /*!< SSPCC_T::IOxSSET: PIN9 Mask            */

#define SSPCC_IOxSSET_PIN10_Pos          (20)                                              /*!< SSPCC_T::IOxSSET: PIN10 Position       */
#define SSPCC_IOxSSET_PIN10_Msk          (0x3ul << SSPCC_IOxSSET_PIN10_Pos)                /*!< SSPCC_T::IOxSSET: PIN10 Mask           */

#define SSPCC_IOxSSET_PIN11_Pos          (22)                                              /*!< SSPCC_T::IOxSSET: PIN11 Position       */
#define SSPCC_IOxSSET_PIN11_Msk          (0x3ul << SSPCC_IOxSSET_PIN11_Pos)                /*!< SSPCC_T::IOxSSET: PIN11 Mask           */

#define SSPCC_IOxSSET_PIN12_Pos          (24)                                              /*!< SSPCC_T::IOxSSET: PIN12 Position       */
#define SSPCC_IOxSSET_PIN12_Msk          (0x3ul << SSPCC_IOxSSET_PIN12_Pos)                /*!< SSPCC_T::IOxSSET: PIN12 Mask           */

#define SSPCC_IOxSSET_PIN13_Pos          (26)                                              /*!< SSPCC_T::IOxSSET: PIN13 Position       */
#define SSPCC_IOxSSET_PIN13_Msk          (0x3ul << SSPCC_IOxSSET_PIN13_Pos)                /*!< SSPCC_T::IOxSSET: PIN13 Mask           */

#define SSPCC_IOxSSET_PIN14_Pos          (28)                                              /*!< SSPCC_T::IOxSSET: PIN14 Position       */
#define SSPCC_IOxSSET_PIN14_Msk          (0x3ul << SSPCC_IOxSSET_PIN14_Pos)                /*!< SSPCC_T::IOxSSET: PIN14 Mask           */

#define SSPCC_IOxSSET_PIN15_Pos          (30)                                              /*!< SSPCC_T::IOxSSET: PIN15 Position       */
#define SSPCC_IOxSSET_PIN15_Msk          (0x3ul << SSPCC_IOxSSET_PIN15_Pos)                /*!< SSPCC_T::IOxSSET: PIN15 Mask           */

#define SSPCC_SVIEN_APB0_Pos             (0)                                               /*!< SSPCC_T::SVIEN: APB0 Position          */
#define SSPCC_SVIEN_APB0_Msk             (0x1ul << SSPCC_SVIEN_APB0_Pos)                   /*!< SSPCC_T::SVIEN: APB0 Mask              */

#define SSPCC_SVIEN_APB3_Pos             (1)                                               /*!< SSPCC_T::SVIEN: APB3 Position          */
#define SSPCC_SVIEN_APB3_Msk             (0x1ul << SSPCC_SVIEN_APB3_Pos)                   /*!< SSPCC_T::SVIEN: APB3 Mask              */

#define SSPCC_SVIEN_SRAM1_Pos            (2)                                               /*!< SSPCC_T::SVIEN: SRAM1 Position         */
#define SSPCC_SVIEN_SRAM1_Msk            (0x1ul << SSPCC_SVIEN_SRAM1_Pos)                  /*!< SSPCC_T::SVIEN: SRAM1 Mask             */

#define SSPCC_SVIEN_SDH0_Pos             (3)                                               /*!< SSPCC_T::SVIEN: SDH0 Position          */
#define SSPCC_SVIEN_SDH0_Msk             (0x1ul << SSPCC_SVIEN_SDH0_Pos)                   /*!< SSPCC_T::SVIEN: SDH0 Mask              */

#define SSPCC_SVIEN_SDH1_Pos             (4)                                               /*!< SSPCC_T::SVIEN: SDH1 Position          */
#define SSPCC_SVIEN_SDH1_Msk             (0x1ul << SSPCC_SVIEN_SDH1_Pos)                   /*!< SSPCC_T::SVIEN: SDH1 Mask              */

#define SSPCC_SVIEN_HSUSBD_Pos           (5)                                               /*!< SSPCC_T::SVIEN: HSUSBD Position        */
#define SSPCC_SVIEN_HSUSBD_Msk           (0x1ul << SSPCC_SVIEN_HSUSBD_Pos)                 /*!< SSPCC_T::SVIEN: HSUSBD Mask            */

#define SSPCC_SVIEN_NANDC_Pos            (6)                                               /*!< SSPCC_T::SVIEN: NANDC Position         */
#define SSPCC_SVIEN_NANDC_Msk            (0x1ul << SSPCC_SVIEN_NANDC_Pos)                  /*!< SSPCC_T::SVIEN: NANDC Mask             */

#define SSPCC_SVIEN_PDMA0_Pos            (7)                                               /*!< SSPCC_T::SVIEN: PDMA0 Position         */
#define SSPCC_SVIEN_PDMA0_Msk            (0x1ul << SSPCC_SVIEN_PDMA0_Pos)                  /*!< SSPCC_T::SVIEN: PDMA0 Mask             */

#define SSPCC_SVIEN_PDMA1_Pos            (8)                                               /*!< SSPCC_T::SVIEN: PDMA1 Position         */
#define SSPCC_SVIEN_PDMA1_Msk            (0x1ul << SSPCC_SVIEN_PDMA1_Pos)                  /*!< SSPCC_T::SVIEN: PDMA1 Mask             */

#define SSPCC_SVIEN_TRNG_Pos             (9)                                               /*!< SSPCC_T::SVIEN: TRNG Position          */
#define SSPCC_SVIEN_TRNG_Msk             (0x1ul << SSPCC_SVIEN_TRNG_Pos)                   /*!< SSPCC_T::SVIEN: TRNG Mask              */

#define SSPCC_SVIEN_CRYPTO_Pos           (10)                                              /*!< SSPCC_T::SVIEN: CRYPTO Position        */
#define SSPCC_SVIEN_CRYPTO_Msk           (0x1ul << SSPCC_SVIEN_CRYPTO_Pos)                 /*!< SSPCC_T::SVIEN: CRYPTO Mask            */

#define SSPCC_SVINTSTS_APB0_Pos          (0)                                               /*!< SSPCC_T::SVINTSTS: APB0 Position       */
#define SSPCC_SVINTSTS_APB0_Msk          (0x1ul << SSPCC_SVINTSTS_APB0_Pos)                /*!< SSPCC_T::SVINTSTS: APB0 Mask           */

#define SSPCC_SVINTSTS_APB3_Pos          (1)                                               /*!< SSPCC_T::SVINTSTS: APB3 Position       */
#define SSPCC_SVINTSTS_APB3_Msk          (0x1ul << SSPCC_SVINTSTS_APB3_Pos)                /*!< SSPCC_T::SVINTSTS: APB3 Mask           */

#define SSPCC_SVINTSTS_SRAM1_Pos         (2)                                               /*!< SSPCC_T::SVINTSTS: SRAM1 Position      */
#define SSPCC_SVINTSTS_SRAM1_Msk         (0x1ul << SSPCC_SVINTSTS_SRAM1_Pos)               /*!< SSPCC_T::SVINTSTS: SRAM1 Mask          */

#define SSPCC_SVINTSTS_SDH0_Pos          (3)                                               /*!< SSPCC_T::SVINTSTS: SDH0 Position       */
#define SSPCC_SVINTSTS_SDH0_Msk          (0x1ul << SSPCC_SVINTSTS_SDH0_Pos)                /*!< SSPCC_T::SVINTSTS: SDH0 Mask           */

#define SSPCC_SVINTSTS_SDH1_Pos          (4)                                               /*!< SSPCC_T::SVINTSTS: SDH1 Position       */
#define SSPCC_SVINTSTS_SDH1_Msk          (0x1ul << SSPCC_SVINTSTS_SDH1_Pos)                /*!< SSPCC_T::SVINTSTS: SDH1 Mask           */

#define SSPCC_SVINTSTS_HSUSBD_Pos        (5)                                               /*!< SSPCC_T::SVINTSTS: HSUSBD Position     */
#define SSPCC_SVINTSTS_HSUSBD_Msk        (0x1ul << SSPCC_SVINTSTS_HSUSBD_Pos)              /*!< SSPCC_T::SVINTSTS: HSUSBD Mask         */

#define SSPCC_SVINTSTS_NANDC_Pos         (6)                                               /*!< SSPCC_T::SVINTSTS: NANDC Position      */
#define SSPCC_SVINTSTS_NANDC_Msk         (0x1ul << SSPCC_SVINTSTS_NANDC_Pos)               /*!< SSPCC_T::SVINTSTS: NANDC Mask          */

#define SSPCC_SVINTSTS_PDMA0_Pos         (7)                                               /*!< SSPCC_T::SVINTSTS: PDMA0 Position      */
#define SSPCC_SVINTSTS_PDMA0_Msk         (0x1ul << SSPCC_SVINTSTS_PDMA0_Pos)               /*!< SSPCC_T::SVINTSTS: PDMA0 Mask          */

#define SSPCC_SVINTSTS_PDMA1_Pos         (8)                                               /*!< SSPCC_T::SVINTSTS: PDMA1 Position      */
#define SSPCC_SVINTSTS_PDMA1_Msk         (0x1ul << SSPCC_SVINTSTS_PDMA1_Pos)               /*!< SSPCC_T::SVINTSTS: PDMA1 Mask          */

#define SSPCC_SVINTSTS_TRNG_Pos          (9)                                               /*!< SSPCC_T::SVINTSTS: TRNG Position       */
#define SSPCC_SVINTSTS_TRNG_Msk          (0x1ul << SSPCC_SVINTSTS_TRNG_Pos)                /*!< SSPCC_T::SVINTSTS: TRNG Mask           */

#define SSPCC_SVINTSTS_CRYPTO_Pos        (10)                                              /*!< SSPCC_T::SVINTSTS: CRYPTO Position     */
#define SSPCC_SVINTSTS_CRYPTO_Msk        (0x1ul << SSPCC_SVINTSTS_CRYPTO_Pos)              /*!< SSPCC_T::SVINTSTS: CRYPTO Mask         */

#define SSPCC_APB0VSRC_MASTER_Pos        (0)                                               /*!< SSPCC_T::APB0VSRC: MASTER Position     */
#define SSPCC_APB0VSRC_MASTER_Msk        (0xful << SSPCC_APB0VSRC_MASTER_Pos)              /*!< SSPCC_T::APB0VSRC: MASTER Mask         */

#define SSPCC_APB3VSRC_MASTER_Pos        (0)                                               /*!< SSPCC_T::APB3VSRC: MASTER Position     */
#define SSPCC_APB3VSRC_MASTER_Msk        (0xful << SSPCC_APB3VSRC_MASTER_Pos)              /*!< SSPCC_T::APB3VSRC: MASTER Mask         */

#define SSPCC_SRAM1VSRC_MASTER_Pos       (0)                                               /*!< SSPCC_T::SRAM1VSRC: MASTER Position    */
#define SSPCC_SRAM1VSRC_MASTER_Msk       (0xful << SSPCC_SRAM1VSRC_MASTER_Pos)             /*!< SSPCC_T::SRAM1VSRC: MASTER Mask        */

#define SSPCC_SDH0VSRC_MASTER_Pos        (0)                                               /*!< SSPCC_T::SDH0VSRC: MASTER Position     */
#define SSPCC_SDH0VSRC_MASTER_Msk        (0xful << SSPCC_SDH0VSRC_MASTER_Pos)              /*!< SSPCC_T::SDH0VSRC: MASTER Mask         */

#define SSPCC_SDH1VSRC_MASTER_Pos        (0)                                               /*!< SSPCC_T::SDH1VSRC: MASTER Position     */
#define SSPCC_SDH1VSRC_MASTER_Msk        (0xful << SSPCC_SDH1VSRC_MASTER_Pos)              /*!< SSPCC_T::SDH1VSRC: MASTER Mask         */

#define SSPCC_HSUSBDVSRC_MASTER_Pos      (0)                                               /*!< SSPCC_T::HSUSBDVSRC: MASTER Position   */
#define SSPCC_HSUSBDVSRC_MASTER_Msk      (0xful << SSPCC_HSUSBDVSRC_MASTER_Pos)            /*!< SSPCC_T::HSUSBDVSRC: MASTER Mask       */

#define SSPCC_NANDCVSRC_MASTER_Pos       (0)                                               /*!< SSPCC_T::NANDCVSRC: MASTER Position    */
#define SSPCC_NANDCVSRC_MASTER_Msk       (0xful << SSPCC_NANDCVSRC_MASTER_Pos)             /*!< SSPCC_T::NANDCVSRC: MASTER Mask        */

#define SSPCC_PDMA0VSRC_MASTER_Pos       (0)                                               /*!< SSPCC_T::PDMA0VSRC: MASTER Position    */
#define SSPCC_PDMA0VSRC_MASTER_Msk       (0xful << SSPCC_PDMA0VSRC_MASTER_Pos)             /*!< SSPCC_T::PDMA0VSRC: MASTER Mask        */

#define SSPCC_PDMA1VSRC_MASTER_Pos       (0)                                               /*!< SSPCC_T::PDMA1VSRC: MASTER Position    */
#define SSPCC_PDMA1VSRC_MASTER_Msk       (0xful << SSPCC_PDMA1VSRC_MASTER_Pos)             /*!< SSPCC_T::PDMA1VSRC: MASTER Mask        */

#define SSPCC_TRNGVSRC_MASTER_Pos        (0)                                               /*!< SSPCC_T::TRNGVSRC: MASTER Position     */
#define SSPCC_TRNGVSRC_MASTER_Msk        (0xful << SSPCC_TRNGVSRC_MASTER_Pos)              /*!< SSPCC_T::TRNGVSRC: MASTER Mask         */

#define SSPCC_CRYPTOVSRC_MASTER_Pos      (0)                                               /*!< SSPCC_T::CRYPTOVSRC: MASTER Position   */
#define SSPCC_CRYPTOVSRC_MASTER_Msk      (0xful << SSPCC_CRYPTOVSRC_MASTER_Pos)            /*!< SSPCC_T::CRYPTOVSRC: MASTER Mask       */

#define SSPCC_APB0VA_VIOADDR_Pos         (0)                                               /*!< SSPCC_T::APB0VA: VIOADDR Position      */
#define SSPCC_APB0VA_VIOADDR_Msk         (0xfffffffful << SSPCC_APB0VA_VIOADDR_Pos)        /*!< SSPCC_T::APB0VA: VIOADDR Mask          */

#define SSPCC_APB3VA_VIOADDR_Pos         (0)                                               /*!< SSPCC_T::APB3VA: VIOADDR Position      */
#define SSPCC_APB3VA_VIOADDR_Msk         (0xfffffffful << SSPCC_APB3VA_VIOADDR_Pos)        /*!< SSPCC_T::APB3VA: VIOADDR Mask          */

#define SSPCC_SRAM1VA_VIOADDR_Pos        (0)                                               /*!< SSPCC_T::SRAM1VA: VIOADDR Position     */
#define SSPCC_SRAM1VA_VIOADDR_Msk        (0xfffffffful << SSPCC_SRAM1VA_VIOADDR_Pos)       /*!< SSPCC_T::SRAM1VA: VIOADDR Mask         */

#define SSPCC_SDH0VA_VIOADDR_Pos         (0)                                               /*!< SSPCC_T::SDH0VA: VIOADDR Position      */
#define SSPCC_SDH0VA_VIOADDR_Msk         (0xfffffffful << SSPCC_SDH0VA_VIOADDR_Pos)        /*!< SSPCC_T::SDH0VA: VIOADDR Mask          */

#define SSPCC_SDH1VA_VIOADDR_Pos         (0)                                               /*!< SSPCC_T::SDH1VA: VIOADDR Position      */
#define SSPCC_SDH1VA_VIOADDR_Msk         (0xfffffffful << SSPCC_SDH1VA_VIOADDR_Pos)        /*!< SSPCC_T::SDH1VA: VIOADDR Mask          */

#define SSPCC_HSUSBDVA_VIOADDR_Pos       (0)                                               /*!< SSPCC_T::HSUSBDVA: VIOADDR Position    */
#define SSPCC_HSUSBDVA_VIOADDR_Msk       (0xfffffffful << SSPCC_HSUSBDVA_VIOADDR_Pos)      /*!< SSPCC_T::HSUSBDVA: VIOADDR Mask        */

#define SSPCC_NANDCVA_VIOADDR_Pos        (0)                                               /*!< SSPCC_T::NANDCVA: VIOADDR Position     */
#define SSPCC_NANDCVA_VIOADDR_Msk        (0xfffffffful << SSPCC_NANDCVA_VIOADDR_Pos)       /*!< SSPCC_T::NANDCVA: VIOADDR Mask         */

#define SSPCC_PDMA0VA_VIOADDR_Pos        (0)                                               /*!< SSPCC_T::PDMA0VA: VIOADDR Position     */
#define SSPCC_PDMA0VA_VIOADDR_Msk        (0xfffffffful << SSPCC_PDMA0VA_VIOADDR_Pos)       /*!< SSPCC_T::PDMA0VA: VIOADDR Mask         */

#define SSPCC_PDMA1VA_VIOADDR_Pos        (0)                                               /*!< SSPCC_T::PDMA1VA: VIOADDR Position     */
#define SSPCC_PDMA1VA_VIOADDR_Msk        (0xfffffffful << SSPCC_PDMA1VA_VIOADDR_Pos)       /*!< SSPCC_T::PDMA1VA: VIOADDR Mask         */

#define SSPCC_TRNGVA_VIOADDR_Pos         (0)                                               /*!< SSPCC_T::TRNGVA: VIOADDR Position      */
#define SSPCC_TRNGVA_VIOADDR_Msk         (0xfffffffful << SSPCC_TRNGVA_VIOADDR_Pos)        /*!< SSPCC_T::TRNGVA: VIOADDR Mask          */

#define SSPCC_CRYPTOVA_VIOADDR_Pos       (0)                                               /*!< SSPCC_T::CRYPTOVA: VIOADDR Position    */
#define SSPCC_CRYPTOVA_VIOADDR_Msk       (0xfffffffful << SSPCC_CRYPTOVA_VIOADDR_Pos)      /*!< SSPCC_T::CRYPTOVA: VIOADDR Mask        */

#define SSPCC_SINFAEN_SSPCCSIAEN_Pos     (0)                                               /*!< SSPCC_T::SINFAEN: SSPCCSIAEN Position  */
#define SSPCC_SINFAEN_SSPCCSIAEN_Msk     (0x1ul << SSPCC_SINFAEN_SSPCCSIAEN_Pos)           /*!< SSPCC_T::SINFAEN: SSPCCSIAEN Mask      */

#define SSPCC_SINFAEN_SYSSIAEN_Pos       (1)                                               /*!< SSPCC_T::SINFAEN: SYSSIAEN Position    */
#define SSPCC_SINFAEN_SYSSIAEN_Msk       (0x1ul << SSPCC_SINFAEN_SYSSIAEN_Pos)             /*!< SSPCC_T::SINFAEN: SYSSIAEN Mask        */

#define SSPCC_SINFAEN_RTCSIAEN_Pos       (2)                                               /*!< SSPCC_T::SINFAEN: RTCSIAEN Position    */
#define SSPCC_SINFAEN_RTCSIAEN_Msk       (0x1ul << SSPCC_SINFAEN_RTCSIAEN_Pos)             /*!< SSPCC_T::SINFAEN: RTCSIAEN Mask        */

#define SSPCC_SINFAEN_OTPSIAEN_Pos       (6)                                               /*!< SSPCC_T::SINFAEN: OTPSIAEN Position    */
#define SSPCC_SINFAEN_OTPSIAEN_Msk       (0x1ul << SSPCC_SINFAEN_OTPSIAEN_Pos)             /*!< SSPCC_T::SINFAEN: OTPSIAEN Mask        */

#define SSPCC_SINFAEN_KSSIAEN_Pos        (7)                                               /*!< SSPCC_T::SINFAEN: KSSIAEN Position     */
#define SSPCC_SINFAEN_KSSIAEN_Msk        (0x1ul << SSPCC_SINFAEN_KSSIAEN_Pos)              /*!< SSPCC_T::SINFAEN: KSSIAEN Mask         */

#define SSPCC_SCWP_ENABLE_Pos            (0)                                               /*!< SSPCC_T::SCWP: ENABLE Position         */
#define SSPCC_SCWP_ENABLE_Msk            (0x1ul << SSPCC_SCWP_ENABLE_Pos)                  /*!< SSPCC_T::SCWP: ENABLE Mask             */

#define SSPCC_SCWP_LOCK_Pos              (1)                                               /*!< SSPCC_T::SCWP: LOCK Position           */
#define SSPCC_SCWP_LOCK_Msk              (0x1ul << SSPCC_SCWP_LOCK_Pos)                    /*!< SSPCC_T::SCWP: LOCK Mask               */

#define SSPCC_SCWP_WVCODE_Pos            (16)                                              /*!< SSPCC_T::SCWP: WVCODE Position         */
#define SSPCC_SCWP_WVCODE_Msk            (0xfffful << SSPCC_SCWP_WVCODE_Pos)               /*!< SSPCC_T::SCWP: WVCODE Mask             */

/**@}*/ /* SSPCC_CONST */
/**@}*/ /* end of SSPCC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __SSPCC_REG_H__ */
