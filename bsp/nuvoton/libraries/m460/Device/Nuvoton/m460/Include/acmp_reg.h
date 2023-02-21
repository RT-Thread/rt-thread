/**************************************************************************//**
 * @file     acmp_reg.h
 * @version  V1.00
 * @brief    ACMP register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ACMP_REG_H__
#define __ACMP_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Analog Comparator Controller -------------------------*/
/**
    @addtogroup ACMP Analog Comparator Controller(ACMP)
    Memory Mapped Structure for ACMP Controller
@{ */

typedef struct
{


    /**
     * @var ACMP_T::CTL0
     * Offset: 0x00  Analog Comparator 0 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ACMPEN    |Comparator Enable Bit
     * |        |          |0 = Comparator 0 Disabled.
     * |        |          |1 = Comparator 0 Enabled.
     * |[1]     |ACMPIE    |Comparator Interrupt Enable Bit
     * |        |          |0 = Comparator 0 interrupt Disabled.
     * |        |          |1 = Comparator 0 interrupt Enabled
     * |        |          |If WKEN (ACMP_CTL0[16]) is set to 1, the wake-up interrupt function will be enabled as well.
     * |[2]     |HYSEN     |Comparator Hysteresis Enable Bit
     * |        |          |0 = Comparator 0 hysteresis Disabled.
     * |        |          |1 = Comparator 0 hysteresis Enabled.
     * |        |          |Note: If HYSEN = 0, user can adjust HYS by HYSSEL.
     * |        |          |Note: If HYSEN = 1, HYSSEL is invalid. The Hysterresis is fixed to 30mV.
     * |[3]     |ACMPOINV  |Comparator Output Inverse
     * |        |          |0 = Comparator 0 output inverse Disabled.
     * |        |          |1 = Comparator 0 output inverse Enabled.
     * |[5:4]   |NEGSEL    |Comparator Negative Input Selection
     * |        |          |00 = ACMP0_N pin.
     * |        |          |01 = Internal comparator reference voltage (CRV0).
     * |        |          |10 = Band-gap voltage.
     * |        |          |11 = DAC0 output.
     * |        |          |Note: NEGSEL must select 2u2019b01 in calibration mode.
     * |[7:6]   |POSSEL    |Comparator Positive Input Selection
     * |        |          |00 = Input from ACMP0_P0.
     * |        |          |01 = Input from ACMP0_P1.
     * |        |          |10 = Input from ACMP0_P2.
     * |        |          |11 = Input from ACMP0_P3.
     * |[9:8]   |INTPOL    |Interrupt Condition Polarity Selection
     * |        |          |ACMPIF0 will be set to 1 when comparator output edge condition is detected.
     * |        |          |00 = Rising edge or falling edge.
     * |        |          |01 = Rising edge.
     * |        |          |10 = Falling edge.
     * |        |          |11 = Reserved.
     * |[12]    |OUTSEL    |Comparator Output Select
     * |        |          |0 = Comparator 0 output to ACMP0_O pin is unfiltered comparator output.
     * |        |          |1 = Comparator 0 output to ACMP0_O pin is from filter output.
     * |[15:13] |FILTSEL   |Comparator Output Filter Count Selection
     * |        |          |000 = Filter function is Disabled.
     * |        |          |001 = ACMP0 output is sampled 1 consecutive PCLK.
     * |        |          |010 = ACMP0 output is sampled 2 consecutive PCLKs.
     * |        |          |011 = ACMP0 output is sampled 4 consecutive PCLKs.
     * |        |          |100 = ACMP0 output is sampled 8 consecutive PCLKs.
     * |        |          |101 = ACMP0 output is sampled 16 consecutive PCLKs.
     * |        |          |110 = ACMP0 output is sampled 32 consecutive PCLKs.
     * |        |          |111 = ACMP0 output is sampled 64 consecutive PCLKs.
     * |[16]    |WKEN      |Power-down Wake-up Enable Bit
     * |        |          |0 = Wake-up function Disabled.
     * |        |          |1 = Wake-up function Enabled.
     * |[17]    |WLATEN    |Window Latch Mode Enable Bit
     * |        |          |0 = Window Latch Mode Disabled.
     * |        |          |1 = Window Latch Mode Enabled.
     * |[18]    |WCMPSEL   |Window Compare Mode Selection
     * |        |          |0 = Window Compare Mode Disabled.
     * |        |          |1 = Window Compare Mode is Selected.
     * |[21:20] |FCLKDIV   |Comparator Output Filter Clock Divider
     * |        |          |00 = cComparator output filter clock = PCLK
     * |        |          |01 = cComparator output filter clock = PCLK/2
     * |        |          |10 = cComparator output filter clock = PCLK/4
     * |        |          |11 = Reserved
     * |        |          |Note: uUse FCLKDIV must under the condition fof FILTSEL = 3u2019h7, then set FCLKDIV canto get the effect of filtering 128,256 consecutive PCLKs.
     * |[26:24] |HYSSEL    |Hysteresis Mode Selection
     * |        |          |000 = Hysteresis is 0mV.
     * |        |          |001 = Hysteresis is 10mV.
     * |        |          |010 = Hysteresis is 20mV.
     * |        |          |011 = Hysteresis is 30mV.
     * |        |          |100 = Hysteresis is 40mV
     * |        |          |101 = Hysteresis is 50mV
     * |        |          |Others = rReserved
     * |[29:28] |MODESEL   |Comparator Power Mode Selection
     * |        |          |00 = low power mode comparator AVDD current 1uA
     * |        |          |01 = low power mode comparator AVDD current 2uA
     * |        |          |10 = active mode comparator AVDD current 35uA
     * |        |          |11 = active mode comparator AVDD current 70uA
     * @var ACMP_T::CTL1
     * Offset: 0x04  Analog Comparator 1 Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ACMPEN    |Comparator Enable Bit
     * |        |          |0 = Comparator 1 Disabled.
     * |        |          |1 = Comparator 1 Enabled.
     * |[1]     |ACMPIE    |Comparator Interrupt Enable Bit
     * |        |          |0 = Comparator 1 interrupt Disabled.
     * |        |          |1 = Comparator 1 interrupt Enabled
     * |        |          |If WKEN (ACMP_CTL1[16]) is set to 1, the wake-up interrupt function will be enabled as well.
     * |[2]     |HYSEN     |Comparator Hysteresis Enable Bit
     * |        |          |0 = Comparator 1 hysteresis Disabled.
     * |        |          |1 = Comparator 1 hysteresis Enabled.
     * |        |          |Note: If HYSEN = 0, user can adjust HYS by HYSSEL.
     * |        |          |Note: If HYSEN = 1, HYSSEL is invalid. The Hysterresis is fixed to 30mV.
     * |[3]     |ACMPOINV  |Comparator Output Inverse Control
     * |        |          |0 = Comparator 1 output inverse Disabled.
     * |        |          |1 = Comparator 1 output inverse Enabled.
     * |[5:4]   |NEGSEL    |Comparator Negative Input Selection
     * |        |          |00 = ACMP1_N pin.
     * |        |          |01 = Internal comparator reference voltage (CRV1).
     * |        |          |10 = Band-gap voltage.
     * |        |          |11 = DAC0 output.
     * |        |          |Note: NEGSEL must select 2u2019b01 in calibration mode.
     * |[7:6]   |POSSEL    |Comparator Positive Input Selection
     * |        |          |00 = Input from ACMP1_P0.
     * |        |          |01 = Input from ACMP1_P1.
     * |        |          |10 = Input from ACMP1_P2.
     * |        |          |11 = Input from ACMP1_P3.
     * |[9:8]   |INTPOL    |Interrupt Condition Polarity Selection
     * |        |          |ACMPIF1 will be set to 1 when comparator output edge condition is detected.
     * |        |          |00 = Rising edge or falling edge.
     * |        |          |01 = Rising edge.
     * |        |          |10 = Falling edge.
     * |        |          |11 = Reserved.
     * |[12]    |OUTSEL    |Comparator Output Select
     * |        |          |0 = Comparator 1 output to ACMP1_O pin is unfiltered comparator output.
     * |        |          |1 = Comparator 1 output to ACMP1_O pin is from filter output.
     * |[15:13] |FILTSEL   |Comparator Output Filter Count Selection
     * |        |          |000 = Filter function is Disabled.
     * |        |          |001 = ACMP1 output is sampled 1 consecutive PCLK.
     * |        |          |010 = ACMP1 output is sampled 2 consecutive PCLKs.
     * |        |          |011 = ACMP1 output is sampled 4 consecutive PCLKs.
     * |        |          |100 = ACMP1 output is sampled 8 consecutive PCLKs.
     * |        |          |101 = ACMP1 output is sampled 16 consecutive PCLKs.
     * |        |          |110 = ACMP1 output is sampled 32 consecutive PCLKs.
     * |        |          |111 = ACMP1 output is sampled 64 consecutive PCLKs.
     * |[16]    |WKEN      |Power-down Wakeup Enable Bit
     * |        |          |0 = Wake-up function Disabled.
     * |        |          |1 = Wake-up function Enabled.
     * |[17]    |WLATEN    |Window Latch Mode Enable Bit
     * |        |          |0 = Window Latch Mode Disabled.
     * |        |          |1 = Window Latch Mode Enabled.
     * |[18]    |WCMPSEL   |Window Compare Mode Selection
     * |        |          |0 = Window Compare Mode Disabled.
     * |        |          |1 = Window Compare Mode is Selected.
     * |[21:20] |FCLKDIV   |Comparator Output Filter Clock Divider
     * |        |          |00 = comparator output filter clock = PCLK
     * |        |          |01 = comparator output filter clock = PCLK/2
     * |        |          |10 = comparator output filter clock = PCLK/4
     * |        |          |11 = Reserved
     * |[26:24] |HYSSEL    |Hysteresis Mode Selection
     * |        |          |000 = Hysteresis is 0mV.
     * |        |          |001 = Hysteresis is 10mV.
     * |        |          |010 = Hysteresis is 20mV.
     * |        |          |011 = Hysteresis is 30mV.
     * |        |          |100 = Hysteresis is 40mV
     * |        |          |101 = Hysteresis is 50mV
     * |        |          |Others = rReserved00 = Hysteresis is 0mV.
     * |        |          |01 = Hysteresis is 10mV.
     * |        |          |10 = Hysteresis is 20mV.
     * |        |          |11 = Hysteresis is 30mV.
     * |[29:28] |MODESEL   |Comparator Power Mode Selection
     * |        |          |00 = low power mode comparator AVDD current 1uA
     * |        |          |01 = low power mode comparator AVDD current 2uA
     * |        |          |10 = active mode comparator AVDD current 35uA
     * |        |          |11 = active mode comparator AVDD current 70uA
     * @var ACMP_T::STATUS
     * Offset: 0x08  Analog Comparator Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ACMPIF0   |Comparator 0 Interrupt Flag
     * |        |          |This bit is set by hardware when the edge condition defined by INTPOL (ACMP_CTL0[9:8]) is detected on comparator 0 output
     * |        |          |This will generate an interrupt if ACMPIE (ACMP_CTL0[1]) is set to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[1]     |ACMPIF1   |Comparator 1 Interrupt Flag
     * |        |          |This bit is set by hardware when the edge condition defined by INTPOL (ACMP_CTL1[9:8]) is detected on comparator 1 output
     * |        |          |This will cause an interrupt if ACMPIE (ACMP_CTL1[1]) is set to 1.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[4]     |ACMPO0    |Comparator 0 Output
     * |        |          |Synchronized to the PCLK to allow reading by software
     * |        |          |Cleared when the comparator 0 is disabled, i.e
     * |        |          |ACMPEN (ACMP_CTL0[0]) is cleared to 0.
     * |[5]     |ACMPO1    |Comparator 1 Output
     * |        |          |Synchronized to the PCLK to allow reading by software
     * |        |          |Cleared when the comparator 1 is disabled, i.e
     * |        |          |ACMPEN (ACMP_CTL1[0]) is cleared to 0.
     * |[8]     |WKIF0     |Comparator 0 Power-down Wake-up Interrupt Flag
     * |        |          |This bit will be set to 1 when ACMP0 wake-up interrupt event occurs.
     * |        |          |0 = No power-down wake-up occurred.
     * |        |          |1 = Power-down wake-up occurred.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[9]     |WKIF1     |Comparator 1 Power-down Wake-up Interrupt Flag
     * |        |          |This bit will be set to 1 when ACMP1 wake-up interrupt event occurs.
     * |        |          |0 = No power-down wake-up occurred.
     * |        |          |1 = Power-down wake-up occurred.
     * |        |          |Note: Write 1 to clear this bit to 0.
     * |[12]    |ACMPS0    |Comparator 0 Status
     * |        |          |Synchronized to the PCLK to allow reading by software
     * |        |          |Cleared when the comparator 0 is disabled, i.e
     * |        |          |ACMPEN (ACMP_CTL0[0]) is cleared to 0.
     * |[13]    |ACMPS1    |Comparator 1 Status
     * |        |          |Synchronized to the PCLK to allow reading by software
     * |        |          |Cleared when the comparator 1 is disabled, i.e
     * |        |          |ACMPEN (ACMP_CTL1[0]) is cleared to 0.
     * |[16]    |ACMPWO    |Comparator Window Output
     * |        |          |This bit shows the output status of window compare mode
     * |        |          |0 = The positive input voltage is outside the window.
     * |        |          |1 = The positive input voltage is in the window.
     * @var ACMP_T::VREF
     * Offset: 0x0C  Analog Comparator Reference Voltage Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |CRV0SEL   |Comparator0Comparator 0 Reference Voltage Setting
     * |        |          |CRV0 = CRV0 source voltage * (ACMP_VREF01[5:0] )/ 631/6+CRVCTL/24).
     * |[6]     |CRV0SSEL  |CRV0 Source Voltage Selection
     * |        |          |0 = AVDD is selected as CRV0 source voltage.
     * |        |          |1 = The reference voltage defined by SYS_VREFCTL register is selected as CRV0 source voltage.
     * |[8]     |CRV0EN    |CRV0 Enable Bit
     * |        |          |0 = CRV0 is dDisabled.
     * |        |          |1 = CRV0 is eEnabled.
     * |[21:16] |CRV1SEL   |Comparator1Comparator 1 Reference Voltage Setting
     * |        |          |CRV1 = CRV1 source voltage * (ACMP_VREF01[21:16] )/ 63.
     * |[22]    |CRV1SSEL  |CRV1 Source Voltage Selection
     * |        |          |0 = AVDD is selected as CRV1 source voltage.
     * |        |          |1 = The reference voltage defined by SYS_VREFCTL register is selected as CRV1 source voltage.
     * |[24]    |CRV1EN    |CRV1 Enable Bit
     * |        |          |0 = CRV1 is dDisabled.
     * |        |          |1 = CRV1 Eis enabled.
     * |[31]    |CLAMPEN   |Current Level Control Selection under Speed Up Function
     * |        |          |0 = ACMP run on high SPEED mode with high quiescent current
     * |        |          |1 = ACMP run on low SPEED mode with high quiescent current
     * |        |          |Note: Comparator speed up function only support SPEED[1:0]=2bu201911 & 2bu201910
     * @var ACMP_T::CALCTL
     * Offset: 0x10  Analog Comparator Calibration Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CALTRG0   |Comparator0Comparator 0 Calibration Trigger Bit
     * |        |          |0 = Calibration is stopped.
     * |        |          |1 = Calibration is triggered.
     * |        |          |Note 1: Before this bit is enabled, ACMPEN(ACMP_CTL0[0]) should be set and the internal high speed RC oscillator (HIRC) should be enabled in advance.
     * |        |          |Note 2: Hardware will auto clear this bit when the next calibration is triggered by software.
     * |        |          |Note 3: If user must trigger calibration twice or more times, the second trigger haves to wait at least 300us after the previous calibration is done.
     * |[1]     |CALTRG1   |Comparator1Comparator 1 Calibration Trigger Bit
     * |        |          |0 = Calibration is stopped.
     * |        |          |1 = Calibration is triggered.
     * |        |          |Note 1: Before this bit is enabled, ACMPEN(ACMP_CTL1[0]) should be set and the internal high speed RC oscillator (HIRC) should be enabled in advance.
     * |        |          |Note 2: Hardware will auto clear this bit when the next calibration is triggered by software.
     * |        |          |Note 3: If user must trigger calibration twice or more times, the second trigger haves to wait at least 300us after the previous calibration is done.
     * |[5:4]   |CALCLK0   |Comparator0Comparator 0 Calibration Clock Rate Selection
     * |        |          |00 = 1.5 kHz.
     * |        |          |01 = 6 kHz.
     * |        |          |10 = 24kHz.
     * |        |          |11 = 95 kHz.
     * |[7:6]   |CALCLK1   |Comparator1Comparator 1 Calibration Clock Rate Selection
     * |        |          |00 = 1.5 kHz.
     * |        |          |01 = 6 kHz.
     * |        |          |10 = 24kHz.
     * |        |          |11 = 95 kHz.
     * |[8]     |OFFSETSEL |Comparator Trim Code Selection
     * |        |          |0 = calibration trim code will not minus 1 when calibrated done.
     * |        |          |1 = calibration trim code will not minus 1 when calibrated done.
     * |[17:16] |CALRVS    |Calibration Reference Voltage Selection
     * |        |          |00 = option0 (N-pair calibration: 5V - 80mV, P-pair calibration: 80mV)
     * |        |          |01 = option1
     * |        |          |10 = option2 (N-pair calibration: 5V - 160mV, P-pair calibration: 160mV)
     * |        |          |11 = Reserved
     * |        |          |Note: CRV0 and CRV1 must be the same setting in calibration
     * |        |          |Note: The details refer to Analog ACMP SPEC
     * @var ACMP_T::CALSTS
     * Offset: 0x14  Analog Comparator Calibration Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DONE0     |Comparator 0 Calibration Done Status
     * |        |          |0 = Calibrating.
     * |        |          |1 = Calibration Ddone.
     * |        |          |NOTE: this bit is write 1 clear
     * |[4]     |DONE1     |Comparator 1 Calibration Done Status
     * |        |          |0 = Calibrating.
     * |        |          |1 = Calibration Ddone.
     * |        |          |NOTE: this bit is write 1 clear
     * @var ACMP_T::COFF
     * Offset: 0xFF0  Analog Comparator Calibration Offset Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |NCODE0    |Comparator0Comparator 0 Offset of NMOS
     * |        |          |ACMP0 offset canceling trim code of NMOS
     * |        |          |Note: 1. Once ACMP0 is enabled, reading these bits will gets initial value from ROMMAP46[19:16]
     * |        |          |2. write MODESEL ACMP_CTL0[29:28] will decide NCODE0 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, NCODE0 load from ROMMAP46[3:0]
     * |        |          | MODESEL = 2u2019b01, NCODE0 load from ROMMAP46[19:16]
     * |        |          | MODESEL = 2u2019b10, NCODE0 load from ROMMAP47[3:0]
     * |        |          | MODESEL = 2u2019b11, NCODE0 load from ROMMAP47[19:16]
     * |[7]     |NSEL0     |Comparator0Comparator 0 Offset of NMOS
     * |        |          |0 = trim NMOS negative offset
     * |        |          |1 = trim NMOS positive offset
     * |        |          |Note: 1. Once ACMP0 is enabled, reading this bit default will get initial value from ROMMAP46[20]
     * |        |          | 2. write MODESEL ACMP_CTL0[29:28] will decide NSEL0 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, NSEL0 load from ROMMAP46[4]
     * |        |          | MODESEL = 2u2019b01, NSEL0 load from ROMMAP46[20]
     * |        |          | MODESEL = 2u2019b10, NSEL0 load from ROMMAP47[4]
     * |        |          | MODESEL = 2u2019b11, NSEL0 load from ROMMAP47[20]
     * |        |          |2
     * |        |          |If ACMP0 is enabled and CALTRG0 (ACMP_CALCTL01[0]]) is set, after calibration done DONE0(ACMP_CALSRTS01[0]) will get NSEL0 value
     * |[11:8]  |PCODE0    |Comparator0Comparator 0 Offset of PMOS
     * |        |          |ACMP0 offset canceling trim code of PMOS
     * |        |          |Note: 1. Once ACMP0 is enabled, reading these bits default will get initial value from ROMMAP46[27:24]
     * |        |          |2. write MODESEL ACMP_CTL0[29:28] will decide PCODE0 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, PCODE0 load from ROMMAP46[11:8]
     * |        |          | MODESEL = 2u2019b01, PCODE0 load from ROMMAP46[27:24]
     * |        |          | MODESEL = 2u2019b10, PCODE0 load from ROMMAP47[11:8]
     * |        |          | MODESEL = 2u2019b11, PCODE0 load from ROMMAP47[27:24]
     * |[15]    |PSEL0     |Comparator0Comparator 0 Offset of PMOS
     * |        |          |0 = trim PMOS negative offset
     * |        |          |1 = trim PMOS positive offset
     * |        |          |Note: 1. Once ACMP0 is enabled, reading this bit default will get initial value from ROMMAP46[28].
     * |        |          |2. write MODESEL ACMP_CTL0[29:28] will decide PSEL0 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, PSEL0 load from ROMMAP46[12]
     * |        |          | MODESEL = 2u2019b01, PSEL0 load from ROMMAP48[28]
     * |        |          | MODESEL = 2u2019b10, PSEL0 load from ROMMAP47[12]
     * |        |          | MODESEL = 2u2019b11, PSEL0 load from ROMMAP47[28]
     * |        |          |3
     * |        |          |If ACMP0 is enabled and CALTRG0 (ACMP_CALCTL01[0]]) is set, after calibration done DONE0(ACMP_CALSACMP_CALSTS01R[0]) will get PSEL0 value
     * |[19:16] |NCODE1    |Comparator 1 Offset of NMOS
     * |        |          |ACMP1 offset canceling trim code of PMOS
     * |        |          |Note: 1. Once ACMP1 is enabled, reading these bits default will get initial value from ROMMAP48[19:16]
     * |        |          |2. write MODESEL ACMP_CTL1[29:28] will decide NCODE1 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, NCODE1load from ROMMAP48[3:0]
     * |        |          | MODESEL = 2u2019b01, NCODE1 load from ROMMAP48[19:16]
     * |        |          | MODESEL = 2u2019b10, NCODE1 load from ROMMAP49[3:0]
     * |        |          | MODESEL = 2u2019b11, NCODE1 load from ROMMAP49[19:16]
     * |[23]    |NSEL1     |Comparator 1 Offset of NMOS
     * |        |          |0 = trim NMOS negative offset
     * |        |          |1 = trim NMOS positive offset
     * |        |          |Note: 1. Once ACMP1 is enabled, reading this bit default will get initial value from ROMMAP48[20]
     * |        |          | 2. write MODESEL ACMP_CTL1[29:28] will decide NSEL1 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, NSEL1 load from ROMMAP48[4]
     * |        |          | MODESEL = 2u2019b01, NSEL1 load from ROMMAP48[20]
     * |        |          | MODESEL = 2u2019b10, NSEL1 load from ROMMAP49[4]
     * |        |          | MODESEL = 2u2019b11, NSEL1 load from ROMMAP49[20]
     * |        |          |3
     * |        |          |If ACMP1 is enabled and CALTRG1 (ACMP_CALCTL01[1]]) is set, after calibration done DONE1(ACMP_CALSRTS01[4]) will get NSEL1 value
     * |[27:24] |PCODE1    |Comparator 1 Offset of PMOS
     * |        |          |ACMP1 offset canceling trim code of PMOS
     * |        |          |Note: 1. Once ACMP1 is enabled, reading these bits default will get initial value from ROMMAP48[27:24]
     * |        |          |2. write MODESEL ACMP_CTL1[29:28] will decide PCODE1 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, PCODE1 load from ROMMAP48[11:8]
     * |        |          | MODESEL = 2u2019b01, PCODE1 load from ROMMAP48[27:24]
     * |        |          | MODESEL = 2u2019b10, PCODE1 load from ROMMAP49[11:8]
     * |        |          | MODESEL = 2u2019b11, PCODE1 load from ROMMAP49[27:24]
     * |[31]    |PSEL1     |Comparator 1 Offset of PMOS
     * |        |          |0 = trim PMOS negative offset
     * |        |          |1 = trim PMOS positive offset
     * |        |          |Note: 1. Once ACMP1 is enabled, reading this bit default will get initial value from ROMMAP48[28]
     * |        |          | 2. write MODESEL ACMP_CTL1[29:28] will decide PSEL1 load from which ROMMAP
     * |        |          | MODESEL = 2u2019b00, PSEL1 load from ROMMAP48[12]
     * |        |          | MODESEL = 2u2019b01, PSEL1 load from ROMMAP48[28]
     * |        |          | MODESEL = 2u2019b10, PSEL1 load from ROMMAP49[12]
     * |        |          | MODESEL = 2u2019b11, PSEL1 load from ROMMAP49[28]
     * |        |          |3
     * |        |          |If ACMP1 is enabled and CALTRG1 (ACMP_CALCTL01[1]]) is set, after calibration done DONE1(ACMP_CALSRTS01[4]) will get PSEL1 value
     * @var ACMP_T::TEST
     * Offset: 0xFF8  Analog Comparator Test Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CRV0TEST  |CRV0 Test Mode Enable Bit (Write Protect)
     * |        |          |0 = No effect.
     * |        |          |1 = CRV voltage output to ACMP0_N pin for voltage measure.
     * |        |          |This bit is designed for Nuvoton Lab use only.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note: NEGSEL (ACMP_CTL0[5:4]) or NEGSEL (ACMP_CTL1[5:4]) must select to 2u2019b01 in CRV test mode
     * |[1]     |CRV1TEST  |CRV1 Test Mode Enable Bit (Write Protect)
     * |        |          |0 = No effect.
     * |        |          |1 = CRV voltage output to ACMP0_N pin for voltage measure.
     * |        |          |This bit is designed for Nuvoton Lab use only.
     * |        |          |Note: This bit is write protected. Refer to the SYS_REGLCTL register.
     * |        |          |Note: NEGSEL (ACMP_CTL0[5:4]) or NEGSEL (ACMP_CTL1[5:4]) must select to 2u2019b01 in CRV test mode
     * |[4]     |OUTSEL    |Comparator CRV Output Source Selection
     * |        |          |0 = CRV output from resistor string
     * |        |          |1 = CRV output from bandgap voltage
     * |[8]     |HYSBYPASS |Hysteresis Adjust Function Selection
     * |        |          |0 = Enable adjust function
     * |        |          |1 = Bypass adjust function
     * @var ACMP_T::VERSION
     * Offset: 0xFFC  Analog Comparator RTL Design Version Number
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[15:0]  |MINOR     |Comp RTL Design MINOR Version Number
     * |        |          |Minor version number is dependent on module ECO version control.
     * |[23:16] |SUB       |Comp RTL Design SUB Version Number
     * |        |          |Major version number is correlated to Product Line.
     * |[31:24] |MAJOR     |Comp RTL Design MAJOR Version Number
     * |        |          |Major version number is correlated to Product Line.
     */
    __IO uint32_t CTL[2];                /*!< [0x0000-0x0004] Analog Comparator 0/1 Control Register                             */
    __IO uint32_t STATUS;                /*!< [0x0008] Analog Comparator Status Register                                */
    __IO uint32_t VREF;                  /*!< [0x000c] Analog Comparator Reference Voltage Control Register             */
    __IO uint32_t CALCTL;                /*!< [0x0010] Analog Comparator Calibration Control Register                   */
    __IO uint32_t CALSTS;                /*!< [0x0014] Analog Comparator Calibration Status Register                    */
    __I  uint32_t RESERVE0[1014];
    __IO uint32_t COFF;                  /*!< [0x0ff0] Analog Comparator Calibration Offset Register                    */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t TEST;                  /*!< [0x0ff8] Analog Comparator Test Control Register                          */
    __I  uint32_t VERSION;               /*!< [0x0ffc] Analog Comparator RTL Design Version Number                      */

} ACMP_T;

/**
    @addtogroup ACMP_CONST ACMP Bit Field Definition
    Constant Definitions for ACMP Controller
@{ */

#define ACMP_CTL_ACMPEN_Pos             (0)                                               /*!< ACMP_T::CTL0: ACMPEN Position          */
#define ACMP_CTL_ACMPEN_Msk             (0x1ul << ACMP_CTL_ACMPEN_Pos)                   /*!< ACMP_T::CTL0: ACMPEN Mask              */

#define ACMP_CTL_ACMPIE_Pos             (1)                                              /*!< ACMP_T::CTL0: ACMPIE Position          */
#define ACMP_CTL_ACMPIE_Msk             (0x1ul << ACMP_CTL_ACMPIE_Pos)                   /*!< ACMP_T::CTL0: ACMPIE Mask              */

#define ACMP_CTL_HYSEN_Pos              (2)                                              /*!< ACMP_T::CTL0: HYSEN Position           */
#define ACMP_CTL_HYSEN_Msk              (0x1ul << ACMP_CTL_HYSEN_Pos)                    /*!< ACMP_T::CTL0: HYSEN Mask               */

#define ACMP_CTL_ACMPOINV_Pos           (3)                                              /*!< ACMP_T::CTL0: ACMPOINV Position        */
#define ACMP_CTL_ACMPOINV_Msk           (0x1ul << ACMP_CTL_ACMPOINV_Pos)                 /*!< ACMP_T::CTL0: ACMPOINV Mask            */

#define ACMP_CTL_NEGSEL_Pos             (4)                                              /*!< ACMP_T::CTL0: NEGSEL Position          */
#define ACMP_CTL_NEGSEL_Msk             (0x3ul << ACMP_CTL_NEGSEL_Pos)                   /*!< ACMP_T::CTL0: NEGSEL Mask              */

#define ACMP_CTL_POSSEL_Pos             (6)                                              /*!< ACMP_T::CTL0: POSSEL Position          */
#define ACMP_CTL_POSSEL_Msk             (0x3ul << ACMP_CTL_POSSEL_Pos)                   /*!< ACMP_T::CTL0: POSSEL Mask              */

#define ACMP_CTL_INTPOL_Pos             (8)                                              /*!< ACMP_T::CTL0: INTPOL Position          */
#define ACMP_CTL_INTPOL_Msk             (0x3ul << ACMP_CTL_INTPOL_Pos)                   /*!< ACMP_T::CTL0: INTPOL Mask              */

#define ACMP_CTL_OUTSEL_Pos             (12)                                             /*!< ACMP_T::CTL0: OUTSEL Position          */
#define ACMP_CTL_OUTSEL_Msk             (0x1ul << ACMP_CTL_OUTSEL_Pos)                   /*!< ACMP_T::CTL0: OUTSEL Mask              */

#define ACMP_CTL_FILTSEL_Pos            (13)                                             /*!< ACMP_T::CTL0: FILTSEL Position         */
#define ACMP_CTL_FILTSEL_Msk            (0x7ul << ACMP_CTL_FILTSEL_Pos)                  /*!< ACMP_T::CTL0: FILTSEL Mask             */

#define ACMP_CTL_WKEN_Pos               (16)                                             /*!< ACMP_T::CTL0: WKEN Position            */
#define ACMP_CTL_WKEN_Msk               (0x1ul << ACMP_CTL_WKEN_Pos)                     /*!< ACMP_T::CTL0: WKEN Mask                */

#define ACMP_CTL_WLATEN_Pos             (17)                                             /*!< ACMP_T::CTL0: WLATEN Position          */
#define ACMP_CTL_WLATEN_Msk             (0x1ul << ACMP_CTL_WLATEN_Pos)                   /*!< ACMP_T::CTL0: WLATEN Mask              */

#define ACMP_CTL_WCMPSEL_Pos            (18)                                             /*!< ACMP_T::CTL0: WCMPSEL Position         */
#define ACMP_CTL_WCMPSEL_Msk            (0x1ul << ACMP_CTL_WCMPSEL_Pos)                  /*!< ACMP_T::CTL0: WCMPSEL Mask             */

#define ACMP_CTL_FCLKDIV_Pos            (20)                                             /*!< ACMP_T::CTL0: FCLKDIV Position         */
#define ACMP_CTL_FCLKDIV_Msk            (0x3ul << ACMP_CTL_FCLKDIV_Pos)                  /*!< ACMP_T::CTL0: FCLKDIV Mask             */

#define ACMP_CTL_HYSSEL_Pos             (24)                                             /*!< ACMP_T::CTL0: HYSSEL Position          */
#define ACMP_CTL_HYSSEL_Msk             (0x7ul << ACMP_CTL_HYSSEL_Pos)                   /*!< ACMP_T::CTL0: HYSSEL Mask              */

#define ACMP_CTL_MODESEL_Pos            (28)                                             /*!< ACMP_T::CTL0: MODESEL Position         */
#define ACMP_CTL_MODESEL_Msk            (0x3ul << ACMP_CTL_MODESEL_Pos)                  /*!< ACMP_T::CTL0: MODESEL Mask             */

#define ACMP_STATUS_ACMPIF0_Pos          (0)                                               /*!< ACMP_T::STATUS: ACMPIF0 Position       */
#define ACMP_STATUS_ACMPIF0_Msk          (0x1ul << ACMP_STATUS_ACMPIF0_Pos)                /*!< ACMP_T::STATUS: ACMPIF0 Mask           */

#define ACMP_STATUS_ACMPIF1_Pos          (1)                                               /*!< ACMP_T::STATUS: ACMPIF1 Position       */
#define ACMP_STATUS_ACMPIF1_Msk          (0x1ul << ACMP_STATUS_ACMPIF1_Pos)                /*!< ACMP_T::STATUS: ACMPIF1 Mask           */

#define ACMP_STATUS_ACMPO0_Pos           (4)                                               /*!< ACMP_T::STATUS: ACMPO0 Position        */
#define ACMP_STATUS_ACMPO0_Msk           (0x1ul << ACMP_STATUS_ACMPO0_Pos)                 /*!< ACMP_T::STATUS: ACMPO0 Mask            */

#define ACMP_STATUS_ACMPO1_Pos           (5)                                               /*!< ACMP_T::STATUS: ACMPO1 Position        */
#define ACMP_STATUS_ACMPO1_Msk           (0x1ul << ACMP_STATUS_ACMPO1_Pos)                 /*!< ACMP_T::STATUS: ACMPO1 Mask            */

#define ACMP_STATUS_WKIF0_Pos            (8)                                               /*!< ACMP_T::STATUS: WKIF0 Position         */
#define ACMP_STATUS_WKIF0_Msk            (0x1ul << ACMP_STATUS_WKIF0_Pos)                  /*!< ACMP_T::STATUS: WKIF0 Mask             */

#define ACMP_STATUS_WKIF1_Pos            (9)                                               /*!< ACMP_T::STATUS: WKIF1 Position         */
#define ACMP_STATUS_WKIF1_Msk            (0x1ul << ACMP_STATUS_WKIF1_Pos)                  /*!< ACMP_T::STATUS: WKIF1 Mask             */

#define ACMP_STATUS_ACMPS0_Pos           (12)                                              /*!< ACMP_T::STATUS: ACMPS0 Position        */
#define ACMP_STATUS_ACMPS0_Msk           (0x1ul << ACMP_STATUS_ACMPS0_Pos)                 /*!< ACMP_T::STATUS: ACMPS0 Mask            */

#define ACMP_STATUS_ACMPS1_Pos           (13)                                              /*!< ACMP_T::STATUS: ACMPS1 Position        */
#define ACMP_STATUS_ACMPS1_Msk           (0x1ul << ACMP_STATUS_ACMPS1_Pos)                 /*!< ACMP_T::STATUS: ACMPS1 Mask            */

#define ACMP_STATUS_ACMPWO_Pos           (16)                                              /*!< ACMP_T::STATUS: ACMPWO Position        */
#define ACMP_STATUS_ACMPWO_Msk           (0x1ul << ACMP_STATUS_ACMPWO_Pos)                 /*!< ACMP_T::STATUS: ACMPWO Mask            */

#define ACMP_VREF_CRV0SEL_Pos            (0)                                               /*!< ACMP_T::VREF: CRV0SEL Position         */
#define ACMP_VREF_CRV0SEL_Msk            (0x3ful << ACMP_VREF_CRV0SEL_Pos)                 /*!< ACMP_T::VREF: CRV0SEL Mask             */

#define ACMP_VREF_CRV0SSEL_Pos           (6)                                               /*!< ACMP_T::VREF: CRV0SSEL Position        */
#define ACMP_VREF_CRV0SSEL_Msk           (0x1ul << ACMP_VREF_CRV0SSEL_Pos)                 /*!< ACMP_T::VREF: CRV0SSEL Mask            */

#define ACMP_VREF_CRV0EN_Pos             (8)                                               /*!< ACMP_T::VREF: CRV0EN Position          */
#define ACMP_VREF_CRV0EN_Msk             (0x1ul << ACMP_VREF_CRV0EN_Pos)                   /*!< ACMP_T::VREF: CRV0EN Mask              */

#define ACMP_VREF_CRV1SEL_Pos            (16)                                              /*!< ACMP_T::VREF: CRV1SEL Position         */
#define ACMP_VREF_CRV1SEL_Msk            (0x3ful << ACMP_VREF_CRV1SEL_Pos)                 /*!< ACMP_T::VREF: CRV1SEL Mask             */

#define ACMP_VREF_CRV1SSEL_Pos           (22)                                              /*!< ACMP_T::VREF: CRV1SSEL Position        */
#define ACMP_VREF_CRV1SSEL_Msk           (0x1ul << ACMP_VREF_CRV1SSEL_Pos)                 /*!< ACMP_T::VREF: CRV1SSEL Mask            */

#define ACMP_VREF_CRV1EN_Pos             (24)                                              /*!< ACMP_T::VREF: CRV1EN Position          */
#define ACMP_VREF_CRV1EN_Msk             (0x1ul << ACMP_VREF_CRV1EN_Pos)                   /*!< ACMP_T::VREF: CRV1EN Mask              */

#define ACMP_VREF_CLAMPEN_Pos            (31)                                              /*!< ACMP_T::VREF: CLAMPEN Position         */
#define ACMP_VREF_CLAMPEN_Msk            (0x1ul << ACMP_VREF_CLAMPEN_Pos)                  /*!< ACMP_T::VREF: CLAMPEN Mask             */

#define ACMP_CALCTL_CALTRG0_Pos          (0)                                               /*!< ACMP_T::CALCTL: CALTRG0 Position       */
#define ACMP_CALCTL_CALTRG0_Msk          (0x1ul << ACMP_CALCTL_CALTRG0_Pos)                /*!< ACMP_T::CALCTL: CALTRG0 Mask           */

#define ACMP_CALCTL_CALTRG1_Pos          (1)                                               /*!< ACMP_T::CALCTL: CALTRG1 Position       */
#define ACMP_CALCTL_CALTRG1_Msk          (0x1ul << ACMP_CALCTL_CALTRG1_Pos)                /*!< ACMP_T::CALCTL: CALTRG1 Mask           */

#define ACMP_CALCTL_CALCLK0_Pos          (4)                                               /*!< ACMP_T::CALCTL: CALCLK0 Position       */
#define ACMP_CALCTL_CALCLK0_Msk          (0x3ul << ACMP_CALCTL_CALCLK0_Pos)                /*!< ACMP_T::CALCTL: CALCLK0 Mask           */

#define ACMP_CALCTL_CALCLK1_Pos          (6)                                               /*!< ACMP_T::CALCTL: CALCLK1 Position       */
#define ACMP_CALCTL_CALCLK1_Msk          (0x3ul << ACMP_CALCTL_CALCLK1_Pos)                /*!< ACMP_T::CALCTL: CALCLK1 Mask           */

#define ACMP_CALCTL_OFFSETSEL_Pos        (8)                                               /*!< ACMP_T::CALCTL: OFFSETSEL Position     */
#define ACMP_CALCTL_OFFSETSEL_Msk        (0x1ul << ACMP_CALCTL_OFFSETSEL_Pos)              /*!< ACMP_T::CALCTL: OFFSETSEL Mask         */

#define ACMP_CALCTL_CALRVS_Pos           (16)                                              /*!< ACMP_T::CALCTL: CALRVS Position        */
#define ACMP_CALCTL_CALRVS_Msk           (0x3ul << ACMP_CALCTL_CALRVS_Pos)                 /*!< ACMP_T::CALCTL: CALRVS Mask            */

#define ACMP_CALSTS_DONE0_Pos            (0)                                               /*!< ACMP_T::CALSTS: DONE0 Position         */
#define ACMP_CALSTS_DONE0_Msk            (0x1ul << ACMP_CALSTS_DONE0_Pos)                  /*!< ACMP_T::CALSTS: DONE0 Mask             */

#define ACMP_CALSTS_DONE1_Pos            (4)                                               /*!< ACMP_T::CALSTS: DONE1 Position         */
#define ACMP_CALSTS_DONE1_Msk            (0x1ul << ACMP_CALSTS_DONE1_Pos)                  /*!< ACMP_T::CALSTS: DONE1 Mask             */

#define ACMP_COFF_NCODE0_Pos             (0)                                               /*!< ACMP_T::COFF: NCODE0 Position          */
#define ACMP_COFF_NCODE0_Msk             (0xful << ACMP_COFF_NCODE0_Pos)                   /*!< ACMP_T::COFF: NCODE0 Mask              */

#define ACMP_COFF_NSEL0_Pos              (7)                                               /*!< ACMP_T::COFF: NSEL0 Position           */
#define ACMP_COFF_NSEL0_Msk              (0x1ul << ACMP_COFF_NSEL0_Pos)                    /*!< ACMP_T::COFF: NSEL0 Mask               */

#define ACMP_COFF_PCODE0_Pos             (8)                                               /*!< ACMP_T::COFF: PCODE0 Position          */
#define ACMP_COFF_PCODE0_Msk             (0xful << ACMP_COFF_PCODE0_Pos)                   /*!< ACMP_T::COFF: PCODE0 Mask              */

#define ACMP_COFF_PSEL0_Pos              (15)                                              /*!< ACMP_T::COFF: PSEL0 Position           */
#define ACMP_COFF_PSEL0_Msk              (0x1ul << ACMP_COFF_PSEL0_Pos)                    /*!< ACMP_T::COFF: PSEL0 Mask               */

#define ACMP_COFF_NCODE1_Pos             (16)                                              /*!< ACMP_T::COFF: NCODE1 Position          */
#define ACMP_COFF_NCODE1_Msk             (0xful << ACMP_COFF_NCODE1_Pos)                   /*!< ACMP_T::COFF: NCODE1 Mask              */

#define ACMP_COFF_NSEL1_Pos              (23)                                              /*!< ACMP_T::COFF: NSEL1 Position           */
#define ACMP_COFF_NSEL1_Msk              (0x1ul << ACMP_COFF_NSEL1_Pos)                    /*!< ACMP_T::COFF: NSEL1 Mask               */

#define ACMP_COFF_PCODE1_Pos             (24)                                              /*!< ACMP_T::COFF: PCODE1 Position          */
#define ACMP_COFF_PCODE1_Msk             (0xful << ACMP_COFF_PCODE1_Pos)                   /*!< ACMP_T::COFF: PCODE1 Mask              */

#define ACMP_COFF_PSEL1_Pos              (31)                                              /*!< ACMP_T::COFF: PSEL1 Position           */
#define ACMP_COFF_PSEL1_Msk              (0x1ul << ACMP_COFF_PSEL1_Pos)                    /*!< ACMP_T::COFF: PSEL1 Mask               */

#define ACMP_TEST_CRV0TEST_Pos           (0)                                               /*!< ACMP_T::TEST: CRV0TEST Position        */
#define ACMP_TEST_CRV0TEST_Msk           (0x1ul << ACMP_TEST_CRV0TEST_Pos)                 /*!< ACMP_T::TEST: CRV0TEST Mask            */

#define ACMP_TEST_CRV1TEST_Pos           (1)                                               /*!< ACMP_T::TEST: CRV1TEST Position        */
#define ACMP_TEST_CRV1TEST_Msk           (0x1ul << ACMP_TEST_CRV1TEST_Pos)                 /*!< ACMP_T::TEST: CRV1TEST Mask            */

#define ACMP_TEST_OUTSEL_Pos             (4)                                               /*!< ACMP_T::TEST: OUTSEL Position          */
#define ACMP_TEST_OUTSEL_Msk             (0x1ul << ACMP_TEST_OUTSEL_Pos)                   /*!< ACMP_T::TEST: OUTSEL Mask              */

#define ACMP_TEST_HYSBYPASS_Pos          (8)                                               /*!< ACMP_T::TEST: HYSBYPASS Position       */
#define ACMP_TEST_HYSBYPASS_Msk          (0x1ul << ACMP_TEST_HYSBYPASS_Pos)                /*!< ACMP_T::TEST: HYSBYPASS Mask           */

#define ACMP_VERSION_MINOR_Pos           (0)                                               /*!< ACMP_T::VERSION: MINOR Position        */
#define ACMP_VERSION_MINOR_Msk           (0xfffful << ACMP_VERSION_MINOR_Pos)              /*!< ACMP_T::VERSION: MINOR Mask            */

#define ACMP_VERSION_SUB_Pos             (16)                                              /*!< ACMP_T::VERSION: SUB Position          */
#define ACMP_VERSION_SUB_Msk             (0xfful << ACMP_VERSION_SUB_Pos)                  /*!< ACMP_T::VERSION: SUB Mask              */

#define ACMP_VERSION_MAJOR_Pos           (24)                                              /*!< ACMP_T::VERSION: MAJOR Position        */
#define ACMP_VERSION_MAJOR_Msk           (0xfful << ACMP_VERSION_MAJOR_Pos)                /*!< ACMP_T::VERSION: MAJOR Mask            */

/**@}*/ /* ACMP_CONST */
/**@}*/ /* end of ACMP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __ACMP_REG_H__ */
