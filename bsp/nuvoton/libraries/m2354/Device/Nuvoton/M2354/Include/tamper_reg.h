/**************************************************************************//**
 * @file     tamper_reg.h
 * @version  V1.00
 * @brief    Tamper register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __TAMPER_REG_H__
#define __TAMPER_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------------- Tamper Controller ----------------------------*/
/**
    @addtogroup Tamper Controller(TAMPER)
    Memory Mapped Structure for Tamper Controller
  @{
*/

typedef struct
{


    /**
     * @var TAMPER_T::INIT
     * Offset: 0x00  Tamper Function Initiation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TCORERST  |Tamper Core Reset
     * |        |          |0 = Write 0x5500; the Tamper core block reset will be released.
     * |        |          |1 = Write 0x55AA; the Tamper core block will be reset.
     * |[31]    |TLDORDY   |Voltage Regulator Power Ready (Read Only)
     * |        |          |0 = The power status of voltage regulator is not ready.
     * |        |          |1 = The power status of voltage regulator is ready.
     * @var TAMPER_T::FUNEN
     * Offset: 0x04  Tamper Block Function Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LXTDETEN  |LXT Clock Detection Enable Bit
     * |        |          |0 = Write 0x40; the LXT clock detection Disabled.
     * |        |          |1 = Write 0x44; the LXT clock detection Enabled.
     * |[13:8]  |TMPIOSEL  |Tamper I/O Detection Selection Bit
     * |        |          |0 = Write 0x90/0xA0/0xB0/0xC0/0xD0/0xE0 for tamper I/O 0~5; the I/O tamper function is detected through RTC block.
     * |        |          |1 = Write 0x94/0xA4/0xB4/0xC4/0xD4/0xE4 for tamper I/O 0~5; the I/O tamper function is detected through Tamper block.
     * |[23:16] |HIRC48MEN |HIRC48M Enable Bit
     * |        |          |The HIRC48M is disabled when these bits equal 0x5A, otherwise it will be enabled with any other values.
     * |[24]    |VGCHEN0   |Voltage Glitch Channel 0 Enable Bit
     * |        |          |0 = Voltage glitch channel 0 Disabled.
     * |        |          |1 = Voltage glitch channel 0 Enabled.
     * |        |          |Note: To avoid the voltage glitch when the voltage channel is enabled, it is better to detect the voltage glitch about 150us after the channel is enabled.
     * |[25]    |VGCHEN1   |Voltage Glitch Channel 1 Enable Bit
     * |        |          |0 = Voltage glitch channel 1 Disabled.
     * |        |          |1 = Voltage glitch channel 1 Enabled.
     * |        |          |Note: To avoid the voltage glitch when the voltage channel is enabled, it is better to detect the voltage glitch about 150us after the channel is enabled.
     * |[26]    |VGCHEN2   |Voltage Glitch Channel 2 Enable Bit
     * |        |          |0 = Voltage glitch channel 2 Disabled.
     * |        |          |1 = Voltage glitch channel 2 Enabled.
     * |        |          |Note: To avoid the voltage glitch when the voltage channel is enabled, it is better to detect the voltage glitch about 150us after the channel is enabled.
     * |[27]    |VGCHEN3   |Voltage Glitch Channel 3 Enable Bit
     * |        |          |0 = Voltage glitch channel 3 Disabled.
     * |        |          |1 = Voltage glitch channel 3 Enabled.
     * |        |          |Note: To avoid the voltage glitch when the voltage channel is enabled, it is better to detect the voltage glitch about 150us after the channel is enabled.
     * @var TAMPER_T::TRIEN
     * Offset: 0x08  Tamper Trigger Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1]     |KSTRIGEN  |Key Store Trigger Enable Bit
     * |        |          |0 = Tamper event is detected and to trigger Key Store Disabled.
     * |        |          |1 = Tamper event is detected and to trigger Key Store Enabled.
     * |[2]     |WAKEUPEN  |Wakeup Enable Bit
     * |        |          |0 = Tamper wakeup event Disabled.
     * |        |          |1 = Tamper wakeup event Enabled.
     * |[3]     |CRYPTOEN  |Crypto Enable Bit
     * |        |          |0 = Tamper event clear Crypto Disabled.
     * |        |          |1 = Tamper event clear Crypto Enabled.
     * |[4]     |CHIPRSTEN |Chip Reset Enable Bit
     * |        |          |0 = Tamper event trigger chip reset Disabled.
     * |        |          |1 = Tamper event trigger chip reset Enabled.
     * |[5]     |RTCSPCLREN|RTC Spare Register Clear Enable Bit
     * |        |          |0 = Tamper event trigger RTC spare register reset Disabled.
     * |        |          |1 = Tamper event trigger RTC spare register reset Enabled.
     * @var TAMPER_T::INTEN
     * Offset: 0x0C  Tamper Event Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TAMP0IEN  |Tamper 0 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 0 event interrupt Disabled.
     * |        |          |1 = Tamper 0 event interrupt Enabled.
     * |[1]     |TAMP1IEN  |Tamper 1 or Pair 0 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 1 or Pair 0 event interrupt Disabled.
     * |        |          |1 = Tamper 1 or Pair 0 event interrupt Enabled.
     * |[2]     |TAMP2IEN  |Tamper 2 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 2 event interrupt Disabled.
     * |        |          |1 = Tamper 2 event interrupt Enabled.
     * |[3]     |TAMP3IEN  |Tamper 3 or Pair 1 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 3 or Pair 1 event interrupt Disabled.
     * |        |          |1 = Tamper 3 or Pair 1 event interrupt Enabled.
     * |[4]     |TAMP4IEN  |Tamper 4 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 4 event interrupt Disabled.
     * |        |          |1 = Tamper 4 event interrupt Enabled.
     * |[5]     |TAMP5IEN  |Tamper 5 or Pair 2 Event Interrupt Enable Bit
     * |        |          |0 = Tamper 5 or Pair 2 event interrupt Disabled.
     * |        |          |1 = Tamper 5 or Pair 2 event interrupt Enabled.
     * |[6]     |CLKFIEN   |LXT Clock Frequency Monitor Fail Event Interrupt Enable Bit
     * |        |          |0 = LXT frequency fail event interrupt Disabled.
     * |        |          |1 = LXT frequency fail event interrupt Enabled.
     * |[7]     |CLKSTOPIEN|LXT Clock Frequency Monitor Stop Event Interrupt Enable Bit
     * |        |          |0 = LXT frequency stop event interrupt Disabled.
     * |        |          |1 = LXT frequency stop event interrupt Enabled.
     * |[8]     |OVPIEN    |VDD Over Voltage Protect Detection Interrupt Enable Bit
     * |        |          |0 = Detect VDD over voltage protect detection interrupt Disabled.
     * |        |          |1 = Detect VDD over voltage protect detection interrupt Enabled.
     * |        |          |Note: The function enable of the over voltage detection is defined in system manager.
     * |[9]     |VGPIEN    |Voltage Glitch Positive Detection Event Interrupt Enable Bit
     * |        |          |0 = LDO_CAP positive glitch event interrupt Disabled.
     * |        |          |1 = LDO_CAP positive glitch event interrupt Enabled.
     * |[10]    |VGNIEN    |Voltage Glitch Negative Detection Event Interrupt Enable Bit
     * |        |          |0 = LDO_CAP negative glitch event interrupt Disabled.
     * |        |          |1 = LDO_CAP negative glitch event interrupt Enabled.
     * |[11]    |ACTSIEN   |Active Shield Event Interrupt Enable Bit
     * |        |          |0 = Active shield event interrupt Disabled.
     * |        |          |1 = Active shield event interrupt Enabled.
     * |[16]    |RTCLVRIEN |RTC Low Voltage Detection Event Interrupt Enable Bit
     * |        |          |0 = VBAT low voltage detection event interrupt Disabled.
     * |        |          |1 = VBAT low voltage detection event interrupt Enabled.
     * |[17]    |RTCIOIEN  |RTC Tamper I/O Event Interrupt Enable Bit
     * |        |          |0 = RTC tamper I/O detection event interrupt Disabled.
     * |        |          |1 = RTC tamper I/O detection event interrupt Enabled.
     * |[18]    |RTCLKIEN  |RTC Clock Monitor Detection Event Interrupt Enable Bit
     * |        |          |0 = RTC clock monitor event interrupt Disabled.
     * |        |          |1 = RTC clock monitor event interrupt Enabled.
     * |[22]    |BODIEN    |BOD Event Interrupt Enable Bit
     * |        |          |0 = Brown-out event interrupt Disabled.
     * |        |          |1 = Brown-out event interrupt Enabled.
     * @var TAMPER_T::INTSTS
     * Offset: 0x10  Tamper Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |TAMP0IF   |Tamper 0 Event Interrupt Flag
     * |        |          |0 = No Tamper 0 event interrupt flag is generated.
     * |        |          |1 = Tamper 0 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[1]     |TAMP1IF   |Tamper 1 Event Interrupt Flag
     * |        |          |0 = No Tamper 1 event interrupt flag is generated.
     * |        |          |1 = Tamper 1 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[2]     |TAMP2IF   |Tamper 2 Event Interrupt Flag
     * |        |          |0 = No Tamper 2 event interrupt flag is generated.
     * |        |          |1 = Tamper 2 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[3]     |TAMP3IF   |Tamper 3 Event Interrupt Flag
     * |        |          |0 = No Tamper 3 event interrupt flag is generated.
     * |        |          |1 = Tamper 3 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[4]     |TAMP4IF   |Tamper 4 Event Interrupt Flag
     * |        |          |0 = No Tamper 4 event interrupt flag is generated.
     * |        |          |1 = Tamper 4 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[5]     |TAMP5IF   |Tamper 5 Event Interrupt Flag
     * |        |          |0 = No Tamper 5 event interrupt flag is generated.
     * |        |          |1 = Tamper 5 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[6]     |CLKFAILIF |LXT Clock Frequency Monitor Fail Event Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is abnormal.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: LXT detector will be automatically disabled when Fail/Stop flag rises, and resumes after Fail/Stop flag is cleared.
     * |[7]     |CLKSTOPIF |LXT Clock Frequency Monitor Stop Event Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is almost stopped.
     * |        |          |Note 1: Write 1 to clear this bit to 0.
     * |        |          |Note 2: LXT detector will be automatically disabled when Fail/Stop flag rises, and resumes after Fail/Stop flag is cleared.
     * |[8]     |OVPOUTIF  |VDD Over Voltage Event Interrupt Flag
     * |        |          |0 = VDD no over voltage is detected.
     * |        |          |1 = VDD over voltage is detected.
     * |        |          |Note: Write 1 to clear this bit.
     * |[9]     |VGPEVIF   |Voltage Glitch Positive Detection Interrupt Flag
     * |        |          |0 = LDO_CAP positive glitch is not detected.
     * |        |          |1 = LDO_CAP positive glitch is detected.
     * |        |          |Note: It can be written 1 to clear only (No clear by TCORERST)
     * |[10]    |VGNEVIF   |Voltage Glitch Negative Detection Interrupt Flag
     * |        |          |0 = LDO_CAP negative glitch is not detected.
     * |        |          |1 = LDO_CAP negative glitch is detected.
     * |        |          |Note: It can be written 1 to clear only (No clear by TCORERST)
     * |[11]    |ACTSEIF   |Active Shield Event Detection Interrupt Flag
     * |        |          |0 = Active shield event interrupt flag is not detected.
     * |        |          |1 = Active shield event interrupt flag is detected including the voltage of voltage regulator and GND attack.
     * |        |          |Note: Write 1 to clear this bit after all of ACTSTxIF bits have been cleaned.
     * |[13]    |ACTST5IF  |Active Shield Tamper 5 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 5 event interrupt flag is generated.
     * |        |          |1 = Active shield Tamper 5 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[15]    |ACTST25IF |Active Shield Tamper 5 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 5 event interrupt flag is generated.
     * |        |          |1 = 2th Active shield Tamper 5 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[16]    |RTCLVRIF  |RTC Low Voltage Detection Event Interrupt Flag
     * |        |          |0 = VBAT low voltage detection event interrupt flag is not detected.
     * |        |          |1 = VBAT low voltage detection event interrupt flag is detected.
     * |[17]    |RIOTRIGIF |RTC Tamper I/O Event Interrupt Flag
     * |        |          |0 = There is no RTC tamper I/O detection event interrupt flag.
     * |        |          |1 = There is RTC tamper I/O detection event interrupt flag.
     * |[18]    |RCLKTRIGIF|RTC Clock Monitor Detection Event Interrupt Flag
     * |        |          |0 = There is no RTC clock monitor detection event interrupt flag.
     * |        |          |1 = There is RTC clock monitor detection event interrupt flag.
     * |[22]    |BODIF     |BOD Event Interrupt Flag
     * |        |          |0 = Brown-out event interrupt flag is no detected.
     * |        |          |1 = Brown-out interrupt flag is detected.
     * |        |          |Note: It is used to detect the LDO_CAP. Write 1 to clear this bit.
     * |[25]    |ACTST1IF  |Active Shield Tamper 1 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 1 event interrupt flag is generated.
     * |        |          |1 = Active shield Tamper 1 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[27]    |ACTST3IF  |Active Shield Tamper 3 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 3 event interrupt flag is generated.
     * |        |          |1 = Active shield Tamper 3 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[29]    |ACTST21IF |2th Active Shield Tamper 1 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 1 event interrupt flag is generated.
     * |        |          |1 = 2th Active shield Tamper 1 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * |[31]    |ACTST23IF |2th Active Shield Tamper 3 Event Interrupt Flag
     * |        |          |0 = No Active shield Tamper 3 event interrupt flag is generated.
     * |        |          |1 = 2th Active shield Tamper 3 event interrupt flag is generated.
     * |        |          |Note: Write 1 to clear this bit.
     * @var TAMPER_T::LIRCTL
     * Offset: 0x14  Tamper LIRC Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[8:0]   |TLRCTRIM  |Tamper TLIRC32K Trim Value
     * |        |          |TLIRC32K trim value setting
     * |[10:9]  |TRIMMOS   |Tamper TLIRC32K Trim MOS Value
     * |        |          |TLIRC32K trim MOS value setting
     * @var TAMPER_T::TIOCTL
     * Offset: 0x18  Tamper I/O Function Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DYN1ISS   |Dynamic Pair 1 Input Source Select
     * |        |          |This bit determines Tamper 3 input is from Tamper 2 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 2.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit is effective only when DYNPR1EN (TAMPER_TIOCTL[23]) and DYNPR0EN (TAMPER_TIOCTL[15]) are set.
     * |[1]     |DYN2ISS   |Dynamic Pair 2 Input Source Select
     * |        |          |This bit determines Tamper 5 input is from Tamper 4 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 4.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit has effect only when DYNPR2EN (TAMPER_TIOCTL[31]) and DYNPR0EN (TAMPER_TIOCTL[15]) are set.
     * |[3]     |DYNSRC    |Dynamic Reference Pattern
     * |        |          |This field determines the new reference pattern when current pattern run out in dynamic pair mode.
     * |        |          |0 = The new reference pattern is generated by random number generator when the reference pattern run out.
     * |        |          |1 = The new reference pattern is repeated from SEED (TAMPER_SEED[31:0]) when the reference pattern run out.
     * |        |          |Note: After this bit is modified, the SEEDRLD (TAMPER_TIOCTL[4]) should be set.
     * |[4]     |SEEDRLD   |Reload New Seed for PRNG Engine
     * |        |          |Setting this bit, the tamper configuration will be reloaded.
     * |        |          |0 = Generating key based on the current seed.
     * |        |          |1 = Reload new seed.
     * |        |          |Note 1: Before this bit is set, the tamper configuration should be set to complete and this bit will be auto clear to 0 after reload new seed completed.
     * |        |          |Note 2: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[7:5]   |DYNRATE   |Dynamic Change Rate
     * |        |          |This item is choice the dynamic tamper output change rate.
     * |        |          |000 = 26 * RTC_CLK.
     * |        |          |001 = 27 * RTC_CLK.
     * |        |          |010 = 28 * RTC_CLK.
     * |        |          |011 = 29 * RTC_CLK.
     * |        |          |100 = 210 * RTC_CLK.
     * |        |          |101 = 211 * RTC_CLK.
     * |        |          |110 = 212 * RTC_CLK.
     * |        |          |111 = 213 * RTC_CLK.
     * |        |          |Note: After revising this field, setting SEEDRLD (TAMPER_TIOCTL[4]) can reload change rate immediately.
     * |[8]     |TAMP0EN   |Tamper0 Detect Enable Bit
     * |        |          |0 = Tamper 0 detect Disabled.
     * |        |          |1 = Tamper 0 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[9]     |TAMP0LV   |Tamper 0 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[10]    |TAMP0DBEN |Tamper 0 De-bounce Enable Bit
     * |        |          |0 = Tamper 0 de-bounce Disabled.
     * |        |          |1 = Tamper 0 de-bounce Enabled. Tamper detection pin will sync 1 RTC clock.
     * |[12]    |TAMP1EN   |Tamper 1 Detect Enable Bit
     * |        |          |0 = Tamper 1 detect Disabled.
     * |        |          |1 = Tamper 1 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[13]    |TAMP1LV   |Tamper 1 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[14]    |TAMP1DBEN |Tamper 1 De-bounce Enable Bit
     * |        |          |0 = Tamper 1 de-bounce Disabled.
     * |        |          |1 = Tamper 1 de-bounce Enabled, tamper detection pin will sync 1 RTC clock.
     * |[15]    |DYNPR0EN  |Dynamic Pair 0 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * |[16]    |TAMP2EN   |Tamper 2 Detect Enable Bit
     * |        |          |0 = Tamper 2 detect Disabled.
     * |        |          |1 = Tamper 2 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector need sync 2 ~ 3 RTC-clock.
     * |[17]    |TAMP2LV   |Tamper 2 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[18]    |TAMP2DBEN |Tamper 2 De-bounce Enable Bit
     * |        |          |0 = Tamper 2 de-bounce Disabled.
     * |        |          |1 = Tamper 2 de-bounce Enabled. Tamper detection pin will sync 1 RTC clock.
     * |[20]    |TAMP3EN   |Tamper 3 Detect Enable Bit
     * |        |          |0 = Tamper 3 detect Disabled.
     * |        |          |1 = Tamper 3 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[21]    |TAMP3LV   |Tamper 3 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[22]    |TAMP3DBEN |Tamper 3 De-bounce Enable Bit
     * |        |          |0 = Tamper 3 de-bounce Disabled.
     * |        |          |1 = Tamper 3 de-bounce Enabled. Tamper detection pin will sync 1 RTC clock.
     * |[23]    |DYNPR1EN  |Dynamic Pair 1 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * |[24]    |TAMP4EN   |Tamper4 Detect Enable Bit
     * |        |          |0 = Tamper 4 detect Disabled.
     * |        |          |1 = Tamper 4 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[25]    |TAMP4LV   |Tamper 4 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[26]    |TAMP4DBEN |Tamper 4 De-bounce Enable Bit
     * |        |          |0 = Tamper 4 de-bounce Disabled.
     * |        |          |1 = Tamper 4 de-bounce Enabled. Tamper detection pin will sync 1 RTC clock.
     * |[28]    |TAMP5EN   |Tamper 5 Detect Enable Bit
     * |        |          |0 = Tamper 5 detect Disabled.
     * |        |          |1 = Tamper 5 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector needs sync 2 ~ 3 RTC-clock.
     * |[29]    |TAMP5LV   |Tamper 5 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[30]    |TAMP5DBEN |Tamper 5 De-bounce Enable Bit
     * |        |          |0 = Tamper 5 de-bounce Disabled.
     * |        |          |1 = Tamper 5 de-bounce Enabled. Tamper detection pin will sync 1 RTC clock.
     * |[31]    |DYNPR2EN  |Dynamic Pair 2 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * @var TAMPER_T::SEED
     * Offset: 0x1C  Tamper Seed Value Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |Seed value.
     * @var TAMPER_T::SEED2
     * Offset: 0x20  Tamper 2nd Seed Value Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED2     |Seed value. These seed value are used for 2nd active shield I/O.
     * @var TAMPER_T::ACTSTIOCTL1
     * Offset: 0x24  Tamper Active Shield Tamper I/O Function Control Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADYN1ISS  |Active Shied Dynamic Pair 1 Input Source Select
     * |        |          |This bit determines Tamper 3 input is from Tamper 2 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 2.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit is effective only when ADYNPR1EN (TAMPER_ACTSTIOCTL1[23]) and ADYNPR0EN (TAMPER_ACTSTIOCTL1[15]) are set.
     * |[3]     |ADYNSRC   |Active Shied Dynamic Reference Pattern
     * |        |          |This field determines the new reference pattern when current pattern run out in dynamic pair mode.
     * |        |          |0 = The new reference pattern is generated by random number generator when the reference pattern run out.
     * |        |          |1 = The new reference pattern is repeated from SEED (TAMPER_SEED[31:0]) when the reference pattern run out.
     * |        |          |Note: After this bit is modified, the SEEDRLD (TAMPER_TIOCTL[4]) should be set.
     * |[7:5]   |ADYNRATE  |Active Shied Dynamic Change Rate
     * |        |          |Use the bits to choose the dynamic tamper output change rate.
     * |        |          |000 = 210 * TLIRC32K.
     * |        |          |001 = 211 * TLIRC32K.
     * |        |          |010 = 212 * TLIRC32K.
     * |        |          |011 = 213 * TLIRC32K.
     * |        |          |100 = 214 * TLIRC32K.
     * |        |          |101 = 215 * TLIRC32K.
     * |        |          |110 = 216 * TLIRC32K.
     * |        |          |111 = 217 * TLIRC32K.
     * |        |          |Note: After this field is modified, setting SEEDRLD (TAMPER_TIOCTL[4]) can reload the change rate immediately.
     * |[8]     |ATAMP0EN  |Active Shied Tamper0 Detect Enable Bit
     * |        |          |0 = Tamper 0 detect Disabled.
     * |        |          |1 = Tamper 0 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector need sync 2 ~ 3 TLIRC 32K-clock.
     * |[12]    |ATAMP1EN  |Active Shied Tamper 1 Detect Enable Bit
     * |        |          |0 = Tamper 1 detect Disabled.
     * |        |          |1 = Tamper 1 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[15]    |ADYNPR0EN |Active Shied Dynamic Pair 0 Enable Bit
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * |[16]    |ATAMP2EN  |Active Shied Tamper 2 Detect Enable Bit
     * |        |          |0 = Tamper 2 detect Disabled.
     * |        |          |1 = Tamper 2 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[20]    |ATAMP3EN  |Active Shied Tamper 3 Detect Enable Bit
     * |        |          |0 = Tamper 3 detect Disabled.
     * |        |          |1 = Tamper 3 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[23]    |ADYNPR1EN |Active Shied Dynamic Pair 1 Enable Bit
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * |[24]    |ATAMP4EN  |Active Tamper4 Detect Enable Bit
     * |        |          |0 = Tamper 4 detect Disabled.
     * |        |          |1 = Tamper 4 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector need sync 2 ~ 3 TLIRC 32K-clock.
     * |[28]    |ATAMP5EN  |Active Tamper 5 Detect Enable Bit
     * |        |          |0 = Tamper 5 detect Disabled.
     * |        |          |1 = Tamper 5 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector need sync 2 ~ 3 TLIRC 32K-clock.
     * |[31]    |ADYNPR2EN |Active Shied Dynamic Pair 2 Enable Bit
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * @var TAMPER_T::ACTSTIOCTL2
     * Offset: 0x28  Tamper Active Shield Tamper I/O Function Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADYN1ISS2 |Active Shied Dynamic Pair 1 Input Source Select 2
     * |        |          |This bit determines if Tamper 3 input is from Tamper 2 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 2.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit is effective only when ADYNPR1EN2 (TAMPER_ACTSTIOCTL2[23]) and ADYNPR0EN2 (TAMPER_ACTSTIOCTL2[15]) are set.
     * |[3]     |ADYNSRC2  |Active Shied Dynamic Reference Pattern 2
     * |        |          |This field determines the new reference pattern when current pattern run out in dynamic pair mode.
     * |        |          |0 = The new reference pattern is generated by random number generator when the reference pattern run out.
     * |        |          |1 = The new reference pattern is repeated from SEED2 (TAMPER_SEED2[31:0]) when the reference pattern run out.
     * |        |          |Note: After this bit is modified, the SEEDRLD2 (TAMPER_ACTSTIOCTL2[4]) should be set.
     * |[4]     |SEEDRLD2  |Reload New Seed for PRNG Engine 2
     * |        |          |Setting this bit, the tamper configuration will be reloaded.
     * |        |          |0 = Generating key based on the current seed.
     * |        |          |1 = Reload new seed.
     * |        |          |Note 1: Before this bit is set, the tamper configuration should be set to complete and this bit will be auto clear to 0 after reload new seed completed.
     * |        |          |Note 2: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[7:5]   |ADYNRATE2 |Active Shied Dynamic Change Rate 2
     * |        |          |Use the bits to choose the dynamic tamper output change rate.
     * |        |          |000 = 210 * TLIRC32K.
     * |        |          |001 = 211 * TLIRC32K.
     * |        |          |010 = 212 * TLIRC32K.
     * |        |          |011 = 213 * TLIRC32K.
     * |        |          |100 = 214 * TLIRC32K.
     * |        |          |101 = 215 * TLIRC32K.
     * |        |          |110 = 216 * TLIRC32K.
     * |        |          |111 = 217 * TLIRC32K.
     * |        |          |Note: After this field is modified, setting SEEDRLD2 (TAMPER_ACTSTIOCTL2[4]) can reload change rate immediately.
     * |[8]     |ATAMP0EN2 |Active Shied Tamper0 Detect Enable Bit 2
     * |        |          |0 = Tamper 0 detect Disabled.
     * |        |          |1 = Tamper 0 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[12]    |ATAMP1EN2 |Active Shied Tamper 1 Detect Enable Bit 2
     * |        |          |0 = Tamper 1 detect Disabled.
     * |        |          |1 = Tamper 1 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[15]    |ADYNPR0EN2|Active Shied Dynamic Pair 0 Enable Bit 2
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * |[16]    |ATAMP2EN2 |Active Shied Tamper 2 Detect Enable Bit 2
     * |        |          |0 = Tamper 2 detect Disabled.
     * |        |          |1 = Tamper 2 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[20]    |ATAMP3EN2 |Active Shied Tamper 3 Detect Enable Bit 2
     * |        |          |0 = Tamper 3 detect Disabled.
     * |        |          |1 = Tamper 3 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector needs sync 2 ~ 3 TLIRC 32K-clock.
     * |[23]    |ADYNPR1EN2|Active Shied Dynamic Pair 1 Enable Bit 2
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * |[24]    |ATAMP4EN2 |Active Shied Tamper4 Detect Enable Bit 2
     * |        |          |0 = Tamper 4 detect Disabled.
     * |        |          |1 = Tamper 4 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector need sync 2 ~ 3 TLIRC 32K-clock.
     * |[28]    |ATAMP5EN2 |Active Tamper 5 Detect Enable Bit 2
     * |        |          |0 = Tamper 5 detect Disabled.
     * |        |          |1 = Tamper 5 detect Enabled.
     * |        |          |Note: The reference is TLIRC 32K-clock. Tamper detector need sync 2 ~ 3 TLIRC 32K-clock.
     * |[31]    |ADYNPR2EN2|Active Shied Dynamic Pair 2 Enable Bit 2
     * |        |          |0 = Static detect (Not supported).
     * |        |          |1 = Dynamic detect.
     * @var TAMPER_T::CDBR
     * Offset: 0x2C  Tamper Clock Frequency Detector Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |STOPBD    |LXT Clock Frequency Detector Stop Boundary
     * |        |          |The bits define the stop value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than Clock Frequency Detector Stop Boundary, the LXT frequency detect stop interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the maximum value of LXT among 256 Tamper clock time.
     * |[23:16] |FAILBD    |LXT Clock Frequency Detector Fail Boundary
     * |        |          |The bits define the fail value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than Clock Frequency Detector Fail Boundary, the LXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the minimum value of LXT among 256 Tamper clock time.
     * @var TAMPER_T::VG
     * Offset: 0x30  Tamper Voltage Glitch Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PCLKSEL0  |PL0 Positive Clock Trim Range
     * |        |          |The setting value of the positive clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |        |          |Note: PL0 means the power level is 1.26V
     * |        |          |The power level is controlled in system manager
     * |[7:4]   |NCLKSEL0  |PL0 Negative Clock Trim Range
     * |        |          |The setting value of the negative clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[11:8]  |PDATSEL0  |PL0 Positive Data Trim Range
     * |        |          |The setting value of the positive data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[15:12] |NDATSEL0  |PL0 Negative Data Trim Range
     * |        |          |The setting value of the negative data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[19:16] |PCLKSEL1  |PL1 Positive Clock Trim Range
     * |        |          |The setting value of the positive clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |        |          |Note: PL1 means the power level is 1.2V
     * |[23:20] |NCLKSEL1  |PL1 Negative Clock Trim Range
     * |        |          |The setting value of the negative clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[27:24] |PDATSEL1  |PL1 Positive Data Trim Range
     * |        |          |The setting value of the positive data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[31:28] |NDATSEL1  |PL1 Negative Data Trim Range
     * |        |          |The setting value of the negative data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * @var TAMPER_T::VGEV
     * Offset: 0x34  Tamper Voltage Glitch Event Tolerance Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |VGECNTP   |Positive Voltage Glitch Error Tolerance
     * |        |          |The value indicates the tolerance count for positive voltage glitch event.
     * |[15:8]  |VGECNTN   |Negative Voltage Glitch Error Tolerance
     * |        |          |The value indicates the tolerance count for negative voltage glitch event.
     * @var TAMPER_T::LDOTRIM
     * Offset: 0x38  Tamper LDO Trim Value Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |TLDOTRIM  |Voltage Regulator Output Voltage Trim
     * |        |          |The value indicates the trim value of the voltage regulator output voltage.
     * |[9:8]   |TLDOIQSEL |Voltage Regulator Qu Current Selection
     * |        |          |Indicates the Qu current selection of voltage regulator.
     * @var TAMPER_T::LBSTRIM
     * Offset: 0x3C  Tamper LDO BIAS Trim Value Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TLVDSEL   |Under-shoot Detect Level Trim Bits
     * |        |          |The value indicates the trim value of the under-shoot detection level
     * |[4]     |TOVDSEL   |Over-shoot Detect Level Trim Bits
     * |        |          |The value indicates the trim value of the over-shoot detection level
     * |[9:8]   |BSCMPLV   |Under-shoot Detect Comparator Current Trim Bits
     * |        |          |The value indicates the trim value of the under-shoot detection comparator current trim level
     * |[11:10] |BSCMPOV   |Over-shoot Detect Comparator Current Trim Bits
     * |        |          |The value indicates the trim value of the over-shoot detection comparator current trim level
     * |[13:12] |HYSCMPLV  |Under-shoot Detect Comparator Hysteresis Trim Bits
     * |        |          |The value indicates the trim value of the under-shoot detection comparator of hysteresis trim level
     * |[15:14] |HYSCMPOV  |Over-shoot Detect Comparator Hysteresis Trim Bits
     * |        |          |The value indicates the trim value of the over-shoot detection comparator of hysteresis trim level
     * @var TAMPER_T::VG2
     * Offset: 0x40  Tamper Voltage Glitch Control Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |PCLKSEL2  |PL2 Positive Clock Trim Range
     * |        |          |The setting value of the positive clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |        |          |Note: PL2 means the power level is 1.1V
     * |        |          |The power level is controlled in system manager.
     * |[7:4]   |NCLKSEL2  |PL2 Negative Clock Trim Range
     * |        |          |The setting value of the negative clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[11:8]  |PDATSEL2  |PL2 Positive Data Trim Range
     * |        |          |The setting value of the positive data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[15:12] |NDATSEL2  |PL2 Negative Data Trim Range
     * |        |          |The setting value of the negative data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[19:16] |PCLKSEL3  |PL3 Positive Clock Trim Range
     * |        |          |The setting value of the positive clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |        |          |Note: PL3 means the power level is 0.9V
     * |[23:20] |NCLKSEL3  |PL3 Negative Clock Trim Range
     * |        |          |The setting value of the negative clock tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[27:24] |PDATSEL3  |PL3 Positive Data Trim Range
     * |        |          |The setting value of the positive data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     * |[31:28] |NDATSEL3  |PL3 Negative Data Trim Range
     * |        |          |The setting value of the negative data tolerance.
     * |        |          |One step is about 2.5% tolerance. The maximum tolerance is 20%.
     */
    __IO uint32_t INIT;                  /*!< [0x0000] Tamper Function Initiation Register                              */
    __IO uint32_t FUNEN;                 /*!< [0x0004] Tamper Block Function Enable Register                            */
    __IO uint32_t TRIEN;                 /*!< [0x0008] Tamper Trigger Enable Register                                   */
    __IO uint32_t INTEN;                 /*!< [0x000c] Tamper Event Interrupt Enable Register                           */
    __IO uint32_t INTSTS;                /*!< [0x0010] Tamper Interrupt Status Register                                 */
    __IO uint32_t LIRCTL;                /*!< [0x0014] Tamper LIRC Control Register                                     */
    __IO uint32_t TIOCTL;                /*!< [0x0018] Tamper I/O Function Control Register                             */
    __IO uint32_t SEED;                  /*!< [0x001c] Tamper Seed Value Control Register                               */
    __IO uint32_t SEED2;                 /*!< [0x0020] Tamper 2nd Seed Value Control Register                           */
    __IO uint32_t ACTSTIOCTL1;           /*!< [0x0024] Tamper Active Shield Tamper I/O Function Control Register 1      */
    __IO uint32_t ACTSTIOCTL2;           /*!< [0x0028] Tamper Active Shield Tamper I/O Function Control Register 2      */
    __IO uint32_t CDBR;                  /*!< [0x002c] Tamper Clock Frequency Detector Boundary Register                */
    __IO uint32_t VG;                    /*!< [0x0030] Tamper Voltage Glitch Control Register                           */
    __IO uint32_t VGEV;                  /*!< [0x0034] Tamper Voltage Glitch Event Tolerance Control Register           */
    __IO uint32_t LDOTRIM;               /*!< [0x0038] Tamper LDO Trim Value Control Register                           */
    __IO uint32_t LBSTRIM;               /*!< [0x003c] Tamper LDO BIAS Trim Value Control Register                      */
    __IO uint32_t VG2;                   /*!< [0x0040] Tamper Voltage Glitch Control Register 2                         */

} TAMPER_T;

/**
    @addtogroup TAMPER_CONST Tamper Bit Field Definition
    Constant Definitions for Tamper Controller
  @{
*/

#define TAMPER_INIT_TCORERST_Pos         (0)                                               /*!< TAMPER_T::INIT: TCORERST Position      */
#define TAMPER_INIT_TCORERST_Msk         (0x1ul << TAMPER_INIT_TCORERST_Pos)               /*!< TAMPER_T::INIT: TCORERST Mask          */

#define TAMPER_INIT_TLDORDY_Pos          (31)                                              /*!< TAMPER_T::INIT: TLDORDY Position       */
#define TAMPER_INIT_TLDORDY_Msk          (0x1ul << TAMPER_INIT_TLDORDY_Pos)                /*!< TAMPER_T::INIT: TLDORDY Mask           */

#define TAMPER_FUNEN_LXTDETEN_Pos        (0)                                               /*!< TAMPER_T::FUNEN: LXTDETEN Position     */
#define TAMPER_FUNEN_LXTDETEN_Msk        (0x1ul << TAMPER_FUNEN_LXTDETEN_Pos)              /*!< TAMPER_T::FUNEN: LXTDETEN Mask         */

#define TAMPER_FUNEN_TMPIOSEL_Pos        (8)                                               /*!< TAMPER_T::FUNEN: TMPIOSEL Position     */
#define TAMPER_FUNEN_TMPIOSEL_Msk        (0x3ful << TAMPER_FUNEN_TMPIOSEL_Pos)             /*!< TAMPER_T::FUNEN: TMPIOSEL Mask         */

#define TAMPER_FUNEN_HIRC48MEN_Pos       (16)                                              /*!< TAMPER_T::FUNEN: HIRC48MEN Position    */
#define TAMPER_FUNEN_HIRC48MEN_Msk       (0xfful << TAMPER_FUNEN_HIRC48MEN_Pos)            /*!< TAMPER_T::FUNEN: HIRC48MEN Mask        */

#define TAMPER_FUNEN_VGCHEN0_Pos         (24)                                              /*!< TAMPER_T::FUNEN: VGCHEN0 Position      */
#define TAMPER_FUNEN_VGCHEN0_Msk         (0x1ul << TAMPER_FUNEN_VGCHEN0_Pos)               /*!< TAMPER_T::FUNEN: VGCHEN0 Mask          */

#define TAMPER_FUNEN_VGCHEN1_Pos         (25)                                              /*!< TAMPER_T::FUNEN: VGCHEN1 Position      */
#define TAMPER_FUNEN_VGCHEN1_Msk         (0x1ul << TAMPER_FUNEN_VGCHEN1_Pos)               /*!< TAMPER_T::FUNEN: VGCHEN1 Mask          */

#define TAMPER_FUNEN_VGCHEN2_Pos         (26)                                              /*!< TAMPER_T::FUNEN: VGCHEN2 Position      */
#define TAMPER_FUNEN_VGCHEN2_Msk         (0x1ul << TAMPER_FUNEN_VGCHEN2_Pos)               /*!< TAMPER_T::FUNEN: VGCHEN2 Mask          */

#define TAMPER_FUNEN_VGCHEN3_Pos         (27)                                              /*!< TAMPER_T::FUNEN: VGCHEN3 Position      */
#define TAMPER_FUNEN_VGCHEN3_Msk         (0x1ul << TAMPER_FUNEN_VGCHEN3_Pos)               /*!< TAMPER_T::FUNEN: VGCHEN3 Mask          */

#define TAMPER_TRIEN_KSTRIGEN_Pos        (1)                                               /*!< TAMPER_T::TRIEN: KSTRIGEN Position     */
#define TAMPER_TRIEN_KSTRIGEN_Msk        (0x1ul << TAMPER_TRIEN_KSTRIGEN_Pos)              /*!< TAMPER_T::TRIEN: KSTRIGEN Mask         */

#define TAMPER_TRIEN_WAKEUPEN_Pos        (2)                                               /*!< TAMPER_T::TRIEN: WAKEUPEN Position     */
#define TAMPER_TRIEN_WAKEUPEN_Msk        (0x1ul << TAMPER_TRIEN_WAKEUPEN_Pos)              /*!< TAMPER_T::TRIEN: WAKEUPEN Mask         */

#define TAMPER_TRIEN_CRYPTOEN_Pos        (3)                                               /*!< TAMPER_T::TRIEN: CRYPTOEN Position     */
#define TAMPER_TRIEN_CRYPTOEN_Msk        (0x1ul << TAMPER_TRIEN_CRYPTOEN_Pos)              /*!< TAMPER_T::TRIEN: CRYPTOEN Mask         */

#define TAMPER_TRIEN_CHIPRSTEN_Pos       (4)                                               /*!< TAMPER_T::TRIEN: CHIPRSTEN Position    */
#define TAMPER_TRIEN_CHIPRSTEN_Msk       (0x1ul << TAMPER_TRIEN_CHIPRSTEN_Pos)             /*!< TAMPER_T::TRIEN: CHIPRSTEN Mask        */

#define TAMPER_TRIEN_RTCSPCLREN_Pos      (5)                                               /*!< TAMPER_T::TRIEN: RTCSPCLREN Position   */
#define TAMPER_TRIEN_RTCSPCLREN_Msk      (0x1ul << TAMPER_TRIEN_RTCSPCLREN_Pos)            /*!< TAMPER_T::TRIEN: RTCSPCLREN Mask       */

#define TAMPER_INTEN_TAMP0IEN_Pos        (0)                                               /*!< TAMPER_T::INTEN: TAMP0IEN Position     */
#define TAMPER_INTEN_TAMP0IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP0IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP0IEN Mask         */

#define TAMPER_INTEN_TAMP1IEN_Pos        (1)                                               /*!< TAMPER_T::INTEN: TAMP1IEN Position     */
#define TAMPER_INTEN_TAMP1IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP1IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP1IEN Mask         */

#define TAMPER_INTEN_TAMP2IEN_Pos        (2)                                               /*!< TAMPER_T::INTEN: TAMP2IEN Position     */
#define TAMPER_INTEN_TAMP2IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP2IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP2IEN Mask         */

#define TAMPER_INTEN_TAMP3IEN_Pos        (3)                                               /*!< TAMPER_T::INTEN: TAMP3IEN Position     */
#define TAMPER_INTEN_TAMP3IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP3IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP3IEN Mask         */

#define TAMPER_INTEN_TAMP4IEN_Pos        (4)                                               /*!< TAMPER_T::INTEN: TAMP4IEN Position     */
#define TAMPER_INTEN_TAMP4IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP4IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP4IEN Mask         */

#define TAMPER_INTEN_TAMP5IEN_Pos        (5)                                               /*!< TAMPER_T::INTEN: TAMP5IEN Position     */
#define TAMPER_INTEN_TAMP5IEN_Msk        (0x1ul << TAMPER_INTEN_TAMP5IEN_Pos)              /*!< TAMPER_T::INTEN: TAMP5IEN Mask         */

#define TAMPER_INTEN_CLKFIEN_Pos         (6)                                               /*!< TAMPER_T::INTEN: CLKFIEN Position      */
#define TAMPER_INTEN_CLKFIEN_Msk         (0x1ul << TAMPER_INTEN_CLKFIEN_Pos)               /*!< TAMPER_T::INTEN: CLKFIEN Mask          */

#define TAMPER_INTEN_CLKSTOPIEN_Pos      (7)                                               /*!< TAMPER_T::INTEN: CLKSTOPIEN Position   */
#define TAMPER_INTEN_CLKSTOPIEN_Msk      (0x1ul << TAMPER_INTEN_CLKSTOPIEN_Pos)            /*!< TAMPER_T::INTEN: CLKSTOPIEN Mask       */

#define TAMPER_INTEN_OVPIEN_Pos          (8)                                               /*!< TAMPER_T::INTEN: OVPIEN Position       */
#define TAMPER_INTEN_OVPIEN_Msk          (0x1ul << TAMPER_INTEN_OVPIEN_Pos)                /*!< TAMPER_T::INTEN: OVPIEN Mask           */

#define TAMPER_INTEN_VGPIEN_Pos          (9)                                               /*!< TAMPER_T::INTEN: VGPIEN Position       */
#define TAMPER_INTEN_VGPIEN_Msk          (0x1ul << TAMPER_INTEN_VGPIEN_Pos)                /*!< TAMPER_T::INTEN: VGPIEN Mask           */

#define TAMPER_INTEN_VGNIEN_Pos          (10)                                              /*!< TAMPER_T::INTEN: VGNIEN Position       */
#define TAMPER_INTEN_VGNIEN_Msk          (0x1ul << TAMPER_INTEN_VGNIEN_Pos)                /*!< TAMPER_T::INTEN: VGNIEN Mask           */

#define TAMPER_INTEN_ACTSIEN_Pos         (11)                                              /*!< TAMPER_T::INTEN: ACTSIEN Position      */
#define TAMPER_INTEN_ACTSIEN_Msk         (0x1ul << TAMPER_INTEN_ACTSIEN_Pos)               /*!< TAMPER_T::INTEN: ACTSIEN Mask          */

#define TAMPER_INTEN_RTCLVRIEN_Pos       (16)                                              /*!< TAMPER_T::INTEN: RTCLVRIEN Position    */
#define TAMPER_INTEN_RTCLVRIEN_Msk       (0x1ul << TAMPER_INTEN_RTCLVRIEN_Pos)             /*!< TAMPER_T::INTEN: RTCLVRIEN Mask        */

#define TAMPER_INTEN_RTCIOIEN_Pos        (17)                                              /*!< TAMPER_T::INTEN: RTCIOIEN Position     */
#define TAMPER_INTEN_RTCIOIEN_Msk        (0x1ul << TAMPER_INTEN_RTCIOIEN_Pos)              /*!< TAMPER_T::INTEN: RTCIOIEN Mask         */

#define TAMPER_INTEN_RTCLKIEN_Pos        (18)                                              /*!< TAMPER_T::INTEN: RTCLKIEN Position     */
#define TAMPER_INTEN_RTCLKIEN_Msk        (0x1ul << TAMPER_INTEN_RTCLKIEN_Pos)              /*!< TAMPER_T::INTEN: RTCLKIEN Mask         */

#define TAMPER_INTEN_BODIEN_Pos          (22)                                              /*!< TAMPER_T::INTEN: BODIEN Position       */
#define TAMPER_INTEN_BODIEN_Msk          (0x1ul << TAMPER_INTEN_BODIEN_Pos)                /*!< TAMPER_T::INTEN: BODIEN Mask           */

#define TAMPER_INTSTS_TAMP0IF_Pos        (0)                                               /*!< TAMPER_T::INTSTS: TAMP0IF Position     */
#define TAMPER_INTSTS_TAMP0IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP0IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP0IF Mask         */

#define TAMPER_INTSTS_TAMP1IF_Pos        (1)                                               /*!< TAMPER_T::INTSTS: TAMP1IF Position     */
#define TAMPER_INTSTS_TAMP1IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP1IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP1IF Mask         */

#define TAMPER_INTSTS_TAMP2IF_Pos        (2)                                               /*!< TAMPER_T::INTSTS: TAMP2IF Position     */
#define TAMPER_INTSTS_TAMP2IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP2IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP2IF Mask         */

#define TAMPER_INTSTS_TAMP3IF_Pos        (3)                                               /*!< TAMPER_T::INTSTS: TAMP3IF Position     */
#define TAMPER_INTSTS_TAMP3IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP3IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP3IF Mask         */

#define TAMPER_INTSTS_TAMP4IF_Pos        (4)                                               /*!< TAMPER_T::INTSTS: TAMP4IF Position     */
#define TAMPER_INTSTS_TAMP4IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP4IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP4IF Mask         */

#define TAMPER_INTSTS_TAMP5IF_Pos        (5)                                               /*!< TAMPER_T::INTSTS: TAMP5IF Position     */
#define TAMPER_INTSTS_TAMP5IF_Msk        (0x1ul << TAMPER_INTSTS_TAMP5IF_Pos)              /*!< TAMPER_T::INTSTS: TAMP5IF Mask         */

#define TAMPER_INTSTS_CLKFAILIF_Pos      (6)                                               /*!< TAMPER_T::INTSTS: CLKFAILIF Position   */
#define TAMPER_INTSTS_CLKFAILIF_Msk      (0x1ul << TAMPER_INTSTS_CLKFAILIF_Pos)            /*!< TAMPER_T::INTSTS: CLKFAILIF Mask       */

#define TAMPER_INTSTS_CLKSTOPIF_Pos      (7)                                               /*!< TAMPER_T::INTSTS: CLKSTOPIF Position   */
#define TAMPER_INTSTS_CLKSTOPIF_Msk      (0x1ul << TAMPER_INTSTS_CLKSTOPIF_Pos)            /*!< TAMPER_T::INTSTS: CLKSTOPIF Mask       */

#define TAMPER_INTSTS_OVPOUTIF_Pos       (8)                                               /*!< TAMPER_T::INTSTS: OVPOUTIF Position    */
#define TAMPER_INTSTS_OVPOUTIF_Msk       (0x1ul << TAMPER_INTSTS_OVPOUTIF_Pos)             /*!< TAMPER_T::INTSTS: OVPOUTIF Mask        */

#define TAMPER_INTSTS_VGPEVIF_Pos        (9)                                               /*!< TAMPER_T::INTSTS: VGPEVIF Position     */
#define TAMPER_INTSTS_VGPEVIF_Msk        (0x1ul << TAMPER_INTSTS_VGPEVIF_Pos)              /*!< TAMPER_T::INTSTS: VGPEVIF Mask         */

#define TAMPER_INTSTS_VGNEVIF_Pos        (10)                                              /*!< TAMPER_T::INTSTS: VGNEVIF Position     */
#define TAMPER_INTSTS_VGNEVIF_Msk        (0x1ul << TAMPER_INTSTS_VGNEVIF_Pos)              /*!< TAMPER_T::INTSTS: VGNEVIF Mask         */

#define TAMPER_INTSTS_ACTSEIF_Pos        (11)                                              /*!< TAMPER_T::INTSTS: ACTSEIF Position     */
#define TAMPER_INTSTS_ACTSEIF_Msk        (0x1ul << TAMPER_INTSTS_ACTSEIF_Pos)              /*!< TAMPER_T::INTSTS: ACTSEIF Mask         */

#define TAMPER_INTSTS_ACTST5IF_Pos       (13)                                              /*!< TAMPER_T::INTSTS: ACTST5IF Position    */
#define TAMPER_INTSTS_ACTST5IF_Msk       (0x1ul << TAMPER_INTSTS_ACTST5IF_Pos)             /*!< TAMPER_T::INTSTS: ACTST5IF Mask        */

#define TAMPER_INTSTS_ACTST25IF_Pos      (15)                                              /*!< TAMPER_T::INTSTS: ACTST25IF Position   */
#define TAMPER_INTSTS_ACTST25IF_Msk      (0x1ul << TAMPER_INTSTS_ACTST25IF_Pos)            /*!< TAMPER_T::INTSTS: ACTST25IF Mask       */

#define TAMPER_INTSTS_RTCLVRIF_Pos       (16)                                              /*!< TAMPER_T::INTSTS: RTCLVRIF Position    */
#define TAMPER_INTSTS_RTCLVRIF_Msk       (0x1ul << TAMPER_INTSTS_RTCLVRIF_Pos)             /*!< TAMPER_T::INTSTS: RTCLVRIF Mask        */

#define TAMPER_INTSTS_RIOTRIGIF_Pos      (17)                                              /*!< TAMPER_T::INTSTS: RIOTRIGIF Position   */
#define TAMPER_INTSTS_RIOTRIGIF_Msk      (0x1ul << TAMPER_INTSTS_RIOTRIGIF_Pos)            /*!< TAMPER_T::INTSTS: RIOTRIGIF Mask       */

#define TAMPER_INTSTS_RCLKTRIGIF_Pos     (18)                                              /*!< TAMPER_T::INTSTS: RCLKTRIGIF Position  */
#define TAMPER_INTSTS_RCLKTRIGIF_Msk     (0x1ul << TAMPER_INTSTS_RCLKTRIGIF_Pos)           /*!< TAMPER_T::INTSTS: RCLKTRIGIF Mask      */

#define TAMPER_INTSTS_BODIF_Pos          (22)                                              /*!< TAMPER_T::INTSTS: BODIF Position       */
#define TAMPER_INTSTS_BODIF_Msk          (0x1ul << TAMPER_INTSTS_BODIF_Pos)                /*!< TAMPER_T::INTSTS: BODIF Mask           */

#define TAMPER_INTSTS_ACTST1IF_Pos       (25)                                              /*!< TAMPER_T::INTSTS: ACTST1IF Position    */
#define TAMPER_INTSTS_ACTST1IF_Msk       (0x1ul << TAMPER_INTSTS_ACTST1IF_Pos)             /*!< TAMPER_T::INTSTS: ACTST1IF Mask        */

#define TAMPER_INTSTS_ACTST3IF_Pos       (27)                                              /*!< TAMPER_T::INTSTS: ACTST3IF Position    */
#define TAMPER_INTSTS_ACTST3IF_Msk       (0x1ul << TAMPER_INTSTS_ACTST3IF_Pos)             /*!< TAMPER_T::INTSTS: ACTST3IF Mask        */

#define TAMPER_INTSTS_ACTST21IF_Pos      (29)                                              /*!< TAMPER_T::INTSTS: ACTST21IF Position   */
#define TAMPER_INTSTS_ACTST21IF_Msk      (0x1ul << TAMPER_INTSTS_ACTST21IF_Pos)            /*!< TAMPER_T::INTSTS: ACTST21IF Mask       */

#define TAMPER_INTSTS_ACTST23IF_Pos      (31)                                              /*!< TAMPER_T::INTSTS: ACTST23IF Position   */
#define TAMPER_INTSTS_ACTST23IF_Msk      (0x1ul << TAMPER_INTSTS_ACTST23IF_Pos)            /*!< TAMPER_T::INTSTS: ACTST23IF Mask       */

#define TAMPER_LIRCTL_TLRCTRIM_Pos       (0)                                               /*!< TAMPER_T::LIRCTL: TLRCTRIM Position    */
#define TAMPER_LIRCTL_TLRCTRIM_Msk       (0x1fful << TAMPER_LIRCTL_TLRCTRIM_Pos)           /*!< TAMPER_T::LIRCTL: TLRCTRIM Mask        */

#define TAMPER_LIRCTL_TRIMMOS_Pos        (9)                                               /*!< TAMPER_T::LIRCTL: TRIMMOS Position     */
#define TAMPER_LIRCTL_TRIMMOS_Msk        (0x3ul << TAMPER_LIRCTL_TRIMMOS_Pos)              /*!< TAMPER_T::LIRCTL: TRIMMOS Mask         */

#define TAMPER_TIOCTL_DYN1ISS_Pos        (0)                                               /*!< TAMPER_T::TIOCTL: DYN1ISS Position     */
#define TAMPER_TIOCTL_DYN1ISS_Msk        (0x1ul << TAMPER_TIOCTL_DYN1ISS_Pos)              /*!< TAMPER_T::TIOCTL: DYN1ISS Mask         */

#define TAMPER_TIOCTL_DYN2ISS_Pos        (1)                                               /*!< TAMPER_T::TIOCTL: DYN2ISS Position     */
#define TAMPER_TIOCTL_DYN2ISS_Msk        (0x1ul << TAMPER_TIOCTL_DYN2ISS_Pos)              /*!< TAMPER_T::TIOCTL: DYN2ISS Mask         */

#define TAMPER_TIOCTL_DYNSRC_Pos         (3)                                               /*!< TAMPER_T::TIOCTL: DYNSRC Position      */
#define TAMPER_TIOCTL_DYNSRC_Msk         (0x1ul << TAMPER_TIOCTL_DYNSRC_Pos)               /*!< TAMPER_T::TIOCTL: DYNSRC Mask          */

#define TAMPER_TIOCTL_SEEDRLD_Pos        (4)                                               /*!< TAMPER_T::TIOCTL: SEEDRLD Position     */
#define TAMPER_TIOCTL_SEEDRLD_Msk        (0x1ul << TAMPER_TIOCTL_SEEDRLD_Pos)              /*!< TAMPER_T::TIOCTL: SEEDRLD Mask         */

#define TAMPER_TIOCTL_DYNRATE_Pos        (5)                                               /*!< TAMPER_T::TIOCTL: DYNRATE Position     */
#define TAMPER_TIOCTL_DYNRATE_Msk        (0x7ul << TAMPER_TIOCTL_DYNRATE_Pos)              /*!< TAMPER_T::TIOCTL: DYNRATE Mask         */

#define TAMPER_TIOCTL_TAMP0EN_Pos        (8)                                               /*!< TAMPER_T::TIOCTL: TAMP0EN Position     */
#define TAMPER_TIOCTL_TAMP0EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP0EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP0EN Mask         */

#define TAMPER_TIOCTL_TAMP0LV_Pos        (9)                                               /*!< TAMPER_T::TIOCTL: TAMP0LV Position     */
#define TAMPER_TIOCTL_TAMP0LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP0LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP0LV Mask         */

#define TAMPER_TIOCTL_TAMP0DBEN_Pos      (10)                                              /*!< TAMPER_T::TIOCTL: TAMP0DBEN Position   */
#define TAMPER_TIOCTL_TAMP0DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP0DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP0DBEN Mask       */

#define TAMPER_TIOCTL_TAMP1EN_Pos        (12)                                              /*!< TAMPER_T::TIOCTL: TAMP1EN Position     */
#define TAMPER_TIOCTL_TAMP1EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP1EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP1EN Mask         */

#define TAMPER_TIOCTL_TAMP1LV_Pos        (13)                                              /*!< TAMPER_T::TIOCTL: TAMP1LV Position     */
#define TAMPER_TIOCTL_TAMP1LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP1LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP1LV Mask         */

#define TAMPER_TIOCTL_TAMP1DBEN_Pos      (14)                                              /*!< TAMPER_T::TIOCTL: TAMP1DBEN Position   */
#define TAMPER_TIOCTL_TAMP1DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP1DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP1DBEN Mask       */

#define TAMPER_TIOCTL_DYNPR0EN_Pos       (15)                                              /*!< TAMPER_T::TIOCTL: DYNPR0EN Position    */
#define TAMPER_TIOCTL_DYNPR0EN_Msk       (0x1ul << TAMPER_TIOCTL_DYNPR0EN_Pos)             /*!< TAMPER_T::TIOCTL: DYNPR0EN Mask        */

#define TAMPER_TIOCTL_TAMP2EN_Pos        (16)                                              /*!< TAMPER_T::TIOCTL: TAMP2EN Position     */
#define TAMPER_TIOCTL_TAMP2EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP2EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP2EN Mask         */

#define TAMPER_TIOCTL_TAMP2LV_Pos        (17)                                              /*!< TAMPER_T::TIOCTL: TAMP2LV Position     */
#define TAMPER_TIOCTL_TAMP2LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP2LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP2LV Mask         */

#define TAMPER_TIOCTL_TAMP2DBEN_Pos      (18)                                              /*!< TAMPER_T::TIOCTL: TAMP2DBEN Position   */
#define TAMPER_TIOCTL_TAMP2DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP2DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP2DBEN Mask       */

#define TAMPER_TIOCTL_TAMP3EN_Pos        (20)                                              /*!< TAMPER_T::TIOCTL: TAMP3EN Position     */
#define TAMPER_TIOCTL_TAMP3EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP3EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP3EN Mask         */

#define TAMPER_TIOCTL_TAMP3LV_Pos        (21)                                              /*!< TAMPER_T::TIOCTL: TAMP3LV Position     */
#define TAMPER_TIOCTL_TAMP3LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP3LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP3LV Mask         */

#define TAMPER_TIOCTL_TAMP3DBEN_Pos      (22)                                              /*!< TAMPER_T::TIOCTL: TAMP3DBEN Position   */
#define TAMPER_TIOCTL_TAMP3DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP3DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP3DBEN Mask       */

#define TAMPER_TIOCTL_DYNPR1EN_Pos       (23)                                              /*!< TAMPER_T::TIOCTL: DYNPR1EN Position    */
#define TAMPER_TIOCTL_DYNPR1EN_Msk       (0x1ul << TAMPER_TIOCTL_DYNPR1EN_Pos)             /*!< TAMPER_T::TIOCTL: DYNPR1EN Mask        */

#define TAMPER_TIOCTL_TAMP4EN_Pos        (24)                                              /*!< TAMPER_T::TIOCTL: TAMP4EN Position     */
#define TAMPER_TIOCTL_TAMP4EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP4EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP4EN Mask         */

#define TAMPER_TIOCTL_TAMP4LV_Pos        (25)                                              /*!< TAMPER_T::TIOCTL: TAMP4LV Position     */
#define TAMPER_TIOCTL_TAMP4LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP4LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP4LV Mask         */

#define TAMPER_TIOCTL_TAMP4DBEN_Pos      (26)                                              /*!< TAMPER_T::TIOCTL: TAMP4DBEN Position   */
#define TAMPER_TIOCTL_TAMP4DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP4DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP4DBEN Mask       */

#define TAMPER_TIOCTL_TAMP5EN_Pos        (28)                                              /*!< TAMPER_T::TIOCTL: TAMP5EN Position     */
#define TAMPER_TIOCTL_TAMP5EN_Msk        (0x1ul << TAMPER_TIOCTL_TAMP5EN_Pos)              /*!< TAMPER_T::TIOCTL: TAMP5EN Mask         */

#define TAMPER_TIOCTL_TAMP5LV_Pos        (29)                                              /*!< TAMPER_T::TIOCTL: TAMP5LV Position     */
#define TAMPER_TIOCTL_TAMP5LV_Msk        (0x1ul << TAMPER_TIOCTL_TAMP5LV_Pos)              /*!< TAMPER_T::TIOCTL: TAMP5LV Mask         */

#define TAMPER_TIOCTL_TAMP5DBEN_Pos      (30)                                              /*!< TAMPER_T::TIOCTL: TAMP5DBEN Position   */
#define TAMPER_TIOCTL_TAMP5DBEN_Msk      (0x1ul << TAMPER_TIOCTL_TAMP5DBEN_Pos)            /*!< TAMPER_T::TIOCTL: TAMP5DBEN Mask       */

#define TAMPER_TIOCTL_DYNPR2EN_Pos       (31)                                              /*!< TAMPER_T::TIOCTL: DYNPR2EN Position    */
#define TAMPER_TIOCTL_DYNPR2EN_Msk       (0x1ul << TAMPER_TIOCTL_DYNPR2EN_Pos)             /*!< TAMPER_T::TIOCTL: DYNPR2EN Mask        */

#define TAMPER_SEED_SEED_Pos             (0)                                               /*!< TAMPER_T::SEED: SEED Position          */
#define TAMPER_SEED_SEED_Msk             (0xfffffffful << TAMPER_SEED_SEED_Pos)            /*!< TAMPER_T::SEED: SEED Mask              */

#define TAMPER_SEED2_SEED2_Pos           (0)                                               /*!< TAMPER_T::SEED2: SEED2 Position        */
#define TAMPER_SEED2_SEED2_Msk           (0xfffffffful << TAMPER_SEED2_SEED2_Pos)          /*!< TAMPER_T::SEED2: SEED2 Mask            */

#define TAMPER_ACTSTIOCTL1_ADYN1ISS_Pos  (0)                                               /*!< TAMPER_T::ACTSTIOCTL1: ADYN1ISS Position*/
#define TAMPER_ACTSTIOCTL1_ADYN1ISS_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ADYN1ISS_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ADYN1ISS Mask   */

#define TAMPER_ACTSTIOCTL1_ADYNSRC_Pos   (3)                                               /*!< TAMPER_T::ACTSTIOCTL1: ADYNSRC Position*/
#define TAMPER_ACTSTIOCTL1_ADYNSRC_Msk   (0x1ul << TAMPER_ACTSTIOCTL1_ADYNSRC_Pos)         /*!< TAMPER_T::ACTSTIOCTL1: ADYNSRC Mask    */

#define TAMPER_ACTSTIOCTL1_ADYNRATE_Pos  (5)                                               /*!< TAMPER_T::ACTSTIOCTL1: ADYNRATE Position*/
#define TAMPER_ACTSTIOCTL1_ADYNRATE_Msk  (0x7ul << TAMPER_ACTSTIOCTL1_ADYNRATE_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ADYNRATE Mask   */

#define TAMPER_ACTSTIOCTL1_ATAMP0EN_Pos  (8)                                               /*!< TAMPER_T::ACTSTIOCTL1: ATAMP0EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP0EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP0EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP0EN Mask   */

#define TAMPER_ACTSTIOCTL1_ATAMP1EN_Pos  (12)                                              /*!< TAMPER_T::ACTSTIOCTL1: ATAMP1EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP1EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP1EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP1EN Mask   */

#define TAMPER_ACTSTIOCTL1_ADYNPR0EN_Pos (15)                                              /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR0EN Position*/
#define TAMPER_ACTSTIOCTL1_ADYNPR0EN_Msk (0x1ul << TAMPER_ACTSTIOCTL1_ADYNPR0EN_Pos)       /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR0EN Mask  */

#define TAMPER_ACTSTIOCTL1_ATAMP2EN_Pos  (16)                                              /*!< TAMPER_T::ACTSTIOCTL1: ATAMP2EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP2EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP2EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP2EN Mask   */

#define TAMPER_ACTSTIOCTL1_ATAMP3EN_Pos  (20)                                              /*!< TAMPER_T::ACTSTIOCTL1: ATAMP3EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP3EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP3EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP3EN Mask   */

#define TAMPER_ACTSTIOCTL1_ADYNPR1EN_Pos (23)                                              /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR1EN Position*/
#define TAMPER_ACTSTIOCTL1_ADYNPR1EN_Msk (0x1ul << TAMPER_ACTSTIOCTL1_ADYNPR1EN_Pos)       /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR1EN Mask  */

#define TAMPER_ACTSTIOCTL1_ATAMP4EN_Pos  (24)                                              /*!< TAMPER_T::ACTSTIOCTL1: ATAMP4EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP4EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP4EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP4EN Mask   */

#define TAMPER_ACTSTIOCTL1_ATAMP5EN_Pos  (28)                                              /*!< TAMPER_T::ACTSTIOCTL1: ATAMP5EN Position*/
#define TAMPER_ACTSTIOCTL1_ATAMP5EN_Msk  (0x1ul << TAMPER_ACTSTIOCTL1_ATAMP5EN_Pos)        /*!< TAMPER_T::ACTSTIOCTL1: ATAMP5EN Mask   */

#define TAMPER_ACTSTIOCTL1_ADYNPR2EN_Pos (31)                                              /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR2EN Position*/
#define TAMPER_ACTSTIOCTL1_ADYNPR2EN_Msk (0x1ul << TAMPER_ACTSTIOCTL1_ADYNPR2EN_Pos)       /*!< TAMPER_T::ACTSTIOCTL1: ADYNPR2EN Mask  */

#define TAMPER_ACTSTIOCTL2_ADYN1ISS2_Pos (0)                                               /*!< TAMPER_T::ACTSTIOCTL2: ADYN1ISS2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYN1ISS2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ADYN1ISS2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ADYN1ISS2 Mask  */

#define TAMPER_ACTSTIOCTL2_ADYNSRC2_Pos  (3)                                               /*!< TAMPER_T::ACTSTIOCTL2: ADYNSRC2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYNSRC2_Msk  (0x1ul << TAMPER_ACTSTIOCTL2_ADYNSRC2_Pos)        /*!< TAMPER_T::ACTSTIOCTL2: ADYNSRC2 Mask   */

#define TAMPER_ACTSTIOCTL2_SEEDRLD2_Pos  (4)                                               /*!< TAMPER_T::ACTSTIOCTL2: SEEDRLD2 Position*/
#define TAMPER_ACTSTIOCTL2_SEEDRLD2_Msk  (0x1ul << TAMPER_ACTSTIOCTL2_SEEDRLD2_Pos)        /*!< TAMPER_T::ACTSTIOCTL2: SEEDRLD2 Mask   */

#define TAMPER_ACTSTIOCTL2_ADYNRATE2_Pos (5)                                               /*!< TAMPER_T::ACTSTIOCTL2: ADYNRATE2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYNRATE2_Msk (0x7ul << TAMPER_ACTSTIOCTL2_ADYNRATE2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ADYNRATE2 Mask  */

#define TAMPER_ACTSTIOCTL2_ATAMP0EN2_Pos (8)                                               /*!< TAMPER_T::ACTSTIOCTL2: ATAMP0EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP0EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP0EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP0EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ATAMP1EN2_Pos (12)                                              /*!< TAMPER_T::ACTSTIOCTL2: ATAMP1EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP1EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP1EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP1EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ADYNPR0EN2_Pos (15)                                             /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR0EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYNPR0EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ADYNPR0EN2_Pos)     /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR0EN2 Mask */

#define TAMPER_ACTSTIOCTL2_ATAMP2EN2_Pos (16)                                              /*!< TAMPER_T::ACTSTIOCTL2: ATAMP2EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP2EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP2EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP2EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ATAMP3EN2_Pos (20)                                              /*!< TAMPER_T::ACTSTIOCTL2: ATAMP3EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP3EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP3EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP3EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ADYNPR1EN2_Pos (23)                                             /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR1EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYNPR1EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ADYNPR1EN2_Pos)     /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR1EN2 Mask */

#define TAMPER_ACTSTIOCTL2_ATAMP4EN2_Pos (24)                                              /*!< TAMPER_T::ACTSTIOCTL2: ATAMP4EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP4EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP4EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP4EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ATAMP5EN2_Pos (28)                                              /*!< TAMPER_T::ACTSTIOCTL2: ATAMP5EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ATAMP5EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ATAMP5EN2_Pos)       /*!< TAMPER_T::ACTSTIOCTL2: ATAMP5EN2 Mask  */

#define TAMPER_ACTSTIOCTL2_ADYNPR2EN2_Pos (31)                                             /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR2EN2 Position*/
#define TAMPER_ACTSTIOCTL2_ADYNPR2EN2_Msk (0x1ul << TAMPER_ACTSTIOCTL2_ADYNPR2EN2_Pos)     /*!< TAMPER_T::ACTSTIOCTL2: ADYNPR2EN2 Mask */

#define TAMPER_CDBR_STOPBD_Pos           (0)                                               /*!< TAMPER_T::CDBR: STOPBD Position        */
#define TAMPER_CDBR_STOPBD_Msk           (0xfful << TAMPER_CDBR_STOPBD_Pos)                /*!< TAMPER_T::CDBR: STOPBD Mask            */

#define TAMPER_CDBR_FAILBD_Pos           (16)                                              /*!< TAMPER_T::CDBR: FAILBD Position        */
#define TAMPER_CDBR_FAILBD_Msk           (0xfful << TAMPER_CDBR_FAILBD_Pos)                /*!< TAMPER_T::CDBR: FAILBD Mask            */

#define TAMPER_VG_PCLKSEL0_Pos           (0)                                               /*!< TAMPER_T::VG: PCLKSEL0 Position        */
#define TAMPER_VG_PCLKSEL0_Msk           (0xful << TAMPER_VG_PCLKSEL0_Pos)                 /*!< TAMPER_T::VG: PCLKSEL0 Mask            */

#define TAMPER_VG_NCLKSEL0_Pos           (4)                                               /*!< TAMPER_T::VG: NCLKSEL0 Position        */
#define TAMPER_VG_NCLKSEL0_Msk           (0xful << TAMPER_VG_NCLKSEL0_Pos)                 /*!< TAMPER_T::VG: NCLKSEL0 Mask            */

#define TAMPER_VG_PDATSEL0_Pos           (8)                                               /*!< TAMPER_T::VG: PDATSEL0 Position        */
#define TAMPER_VG_PDATSEL0_Msk           (0xful << TAMPER_VG_PDATSEL0_Pos)                 /*!< TAMPER_T::VG: PDATSEL0 Mask            */

#define TAMPER_VG_NDATSEL0_Pos           (12)                                              /*!< TAMPER_T::VG: NDATSEL0 Position        */
#define TAMPER_VG_NDATSEL0_Msk           (0xful << TAMPER_VG_NDATSEL0_Pos)                 /*!< TAMPER_T::VG: NDATSEL0 Mask            */

#define TAMPER_VG_PCLKSEL1_Pos           (16)                                              /*!< TAMPER_T::VG: PCLKSEL1 Position        */
#define TAMPER_VG_PCLKSEL1_Msk           (0xful << TAMPER_VG_PCLKSEL1_Pos)                 /*!< TAMPER_T::VG: PCLKSEL1 Mask            */

#define TAMPER_VG_NCLKSEL1_Pos           (20)                                              /*!< TAMPER_T::VG: NCLKSEL1 Position        */
#define TAMPER_VG_NCLKSEL1_Msk           (0xful << TAMPER_VG_NCLKSEL1_Pos)                 /*!< TAMPER_T::VG: NCLKSEL1 Mask            */

#define TAMPER_VG_PDATSEL1_Pos           (24)                                              /*!< TAMPER_T::VG: PDATSEL1 Position        */
#define TAMPER_VG_PDATSEL1_Msk           (0xful << TAMPER_VG_PDATSEL1_Pos)                 /*!< TAMPER_T::VG: PDATSEL1 Mask            */

#define TAMPER_VG_NDATSEL1_Pos           (28)                                              /*!< TAMPER_T::VG: NDATSEL1 Position        */
#define TAMPER_VG_NDATSEL1_Msk           (0xful << TAMPER_VG_NDATSEL1_Pos)                 /*!< TAMPER_T::VG: NDATSEL1 Mask            */

#define TAMPER_VGEV_VGECNTP_Pos          (0)                                               /*!< TAMPER_T::VGEV: VGECNTP Position       */
#define TAMPER_VGEV_VGECNTP_Msk          (0xfful << TAMPER_VGEV_VGECNTP_Pos)               /*!< TAMPER_T::VGEV: VGECNTP Mask           */

#define TAMPER_VGEV_VGECNTN_Pos          (8)                                               /*!< TAMPER_T::VGEV: VGECNTN Position       */
#define TAMPER_VGEV_VGECNTN_Msk          (0xfful << TAMPER_VGEV_VGECNTN_Pos)               /*!< TAMPER_T::VGEV: VGECNTN Mask           */

#define TAMPER_LDOTRIM_TLDOTRIM_Pos      (0)                                               /*!< TAMPER_T::LDOTRIM: TLDOTRIM Position   */
#define TAMPER_LDOTRIM_TLDOTRIM_Msk      (0xful << TAMPER_LDOTRIM_TLDOTRIM_Pos)            /*!< TAMPER_T::LDOTRIM: TLDOTRIM Mask       */

#define TAMPER_LDOTRIM_TLDOIQSEL_Pos     (8)                                               /*!< TAMPER_T::LDOTRIM: TLDOIQSEL Position  */
#define TAMPER_LDOTRIM_TLDOIQSEL_Msk     (0x3ul << TAMPER_LDOTRIM_TLDOIQSEL_Pos)           /*!< TAMPER_T::LDOTRIM: TLDOIQSEL Mask      */

#define TAMPER_LBSTRIM_TLVDSEL_Pos       (0)                                               /*!< TAMPER_T::LBSTRIM: TLVDSEL Position    */
#define TAMPER_LBSTRIM_TLVDSEL_Msk       (0x7ul << TAMPER_LBSTRIM_TLVDSEL_Pos)             /*!< TAMPER_T::LBSTRIM: TLVDSEL Mask        */

#define TAMPER_LBSTRIM_TOVDSEL_Pos       (4)                                               /*!< TAMPER_T::LBSTRIM: TOVDSEL Position    */
#define TAMPER_LBSTRIM_TOVDSEL_Msk       (0x1ul << TAMPER_LBSTRIM_TOVDSEL_Pos)             /*!< TAMPER_T::LBSTRIM: TOVDSEL Mask        */

#define TAMPER_LBSTRIM_BSCMPLV_Pos       (8)                                               /*!< TAMPER_T::LBSTRIM: BSCMPLV Position    */
#define TAMPER_LBSTRIM_BSCMPLV_Msk       (0x3ul << TAMPER_LBSTRIM_BSCMPLV_Pos)             /*!< TAMPER_T::LBSTRIM: BSCMPLV Mask        */

#define TAMPER_LBSTRIM_BSCMPOV_Pos       (10)                                              /*!< TAMPER_T::LBSTRIM: BSCMPOV Position    */
#define TAMPER_LBSTRIM_BSCMPOV_Msk       (0x3ul << TAMPER_LBSTRIM_BSCMPOV_Pos)             /*!< TAMPER_T::LBSTRIM: BSCMPOV Mask        */

#define TAMPER_LBSTRIM_HYSCMPLV_Pos      (12)                                              /*!< TAMPER_T::LBSTRIM: HYSCMPLV Position   */
#define TAMPER_LBSTRIM_HYSCMPLV_Msk      (0x3ul << TAMPER_LBSTRIM_HYSCMPLV_Pos)            /*!< TAMPER_T::LBSTRIM: HYSCMPLV Mask       */

#define TAMPER_LBSTRIM_HYSCMPOV_Pos      (14)                                              /*!< TAMPER_T::LBSTRIM: HYSCMPOV Position   */
#define TAMPER_LBSTRIM_HYSCMPOV_Msk      (0x3ul << TAMPER_LBSTRIM_HYSCMPOV_Pos)            /*!< TAMPER_T::LBSTRIM: HYSCMPOV Mask       */

#define TAMPER_VG2_PCLKSEL2_Pos          (0)                                               /*!< TAMPER_T::VG2: PCLKSEL2 Position       */
#define TAMPER_VG2_PCLKSEL2_Msk          (0xful << TAMPER_VG2_PCLKSEL2_Pos)                /*!< TAMPER_T::VG2: PCLKSEL2 Mask           */

#define TAMPER_VG2_NCLKSEL2_Pos          (4)                                               /*!< TAMPER_T::VG2: NCLKSEL2 Position       */
#define TAMPER_VG2_NCLKSEL2_Msk          (0xful << TAMPER_VG2_NCLKSEL2_Pos)                /*!< TAMPER_T::VG2: NCLKSEL2 Mask           */

#define TAMPER_VG2_PDATSEL2_Pos          (8)                                               /*!< TAMPER_T::VG2: PDATSEL2 Position       */
#define TAMPER_VG2_PDATSEL2_Msk          (0xful << TAMPER_VG2_PDATSEL2_Pos)                /*!< TAMPER_T::VG2: PDATSEL2 Mask           */

#define TAMPER_VG2_NDATSEL2_Pos          (12)                                              /*!< TAMPER_T::VG2: NDATSEL2 Position       */
#define TAMPER_VG2_NDATSEL2_Msk          (0xful << TAMPER_VG2_NDATSEL2_Pos)                /*!< TAMPER_T::VG2: NDATSEL2 Mask           */

#define TAMPER_VG2_PCLKSEL3_Pos          (16)                                              /*!< TAMPER_T::VG2: PCLKSEL3 Position       */
#define TAMPER_VG2_PCLKSEL3_Msk          (0xful << TAMPER_VG2_PCLKSEL3_Pos)                /*!< TAMPER_T::VG2: PCLKSEL3 Mask           */

#define TAMPER_VG2_NCLKSEL3_Pos          (20)                                              /*!< TAMPER_T::VG2: NCLKSEL3 Position       */
#define TAMPER_VG2_NCLKSEL3_Msk          (0xful << TAMPER_VG2_NCLKSEL3_Pos)                /*!< TAMPER_T::VG2: NCLKSEL3 Mask           */

#define TAMPER_VG2_PDATSEL3_Pos          (24)                                              /*!< TAMPER_T::VG2: PDATSEL3 Position       */
#define TAMPER_VG2_PDATSEL3_Msk          (0xful << TAMPER_VG2_PDATSEL3_Pos)                /*!< TAMPER_T::VG2: PDATSEL3 Mask           */

#define TAMPER_VG2_NDATSEL3_Pos          (28)                                              /*!< TAMPER_T::VG2: NDATSEL3 Position       */
#define TAMPER_VG2_NDATSEL3_Msk          (0xful << TAMPER_VG2_NDATSEL3_Pos)                /*!< TAMPER_T::VG2: NDATSEL3 Mask           */

/**@}*/ /* TAMPER_CONST */
/**@}*/ /* end of TAMPER register group */
/**@}*/ /* end of REGISTER group */

#endif /* __TAMPER_REG_H__ */
