/**************************************************************************//**
 * @file     rtc_reg.h
 * @version  V1.00
 * @brief    RTC register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __RTC_REG_H__
#define __RTC_REG_H__

/** @addtogroup REGISTER Control Register

  @{

*/

/*---------------------- Real Time Clock Controller -------------------------*/
/**
    @addtogroup RTC Real Time Clock Controller(RTC)
    Memory Mapped Structure for RTC Controller
  @{
*/

typedef struct
{


    /**
     * @var RTC_T::INIT
     * Offset: 0x00  RTC Initiation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |INIT_ACTIVE|RTC Active Status (Read Only)
     * |        |          |0 = RTC is at reset state.
     * |        |          |1 = RTC is at normal active state.
     * |[31:1]  |INIT      |RTC Initiation (Write Only)
     * |        |          |When RTC block is powered on, RTC is at reset state.
     * |        |          |User has to write a number (0xa5eb1357) to INIT to make RTC leave reset state.
     * |        |          |Once the INIT is written as 0xa5eb1357, the RTC will be in un-reset state permanently.
     * |        |          |The INIT is a write-only field and read value will be always 0.
     * @var RTC_T::FREQADJ
     * Offset: 0x08  RTC Frequency Compensation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[5:0]   |FRACTION  |Fraction Part
     * |        |          |Formula: FRACTION = (fraction part of detected value) X 64.
     * |        |          |Note: Digit in FCR must be expressed as hexadecimal number.
     * |[12:8]  |INTEGER   |Integer Part
     * |        |          |00000 = Integer part of detected value is 32752.
     * |        |          |00001 = Integer part of detected value is 32753.
     * |        |          |00010 = Integer part of detected value is 32754.
     * |        |          |00011 = Integer part of detected value is 32755.
     * |        |          |00100 = Integer part of detected value is 32756.
     * |        |          |00101 = Integer part of detected value is 32757.
     * |        |          |00110 = Integer part of detected value is 32758.
     * |        |          |00111 = Integer part of detected value is 32759.
     * |        |          |01000 = Integer part of detected value is 32760.
     * |        |          |01001 = Integer part of detected value is 32761.
     * |        |          |01010 = Integer part of detected value is 32762.
     * |        |          |01011 = Integer part of detected value is 32763.
     * |        |          |01100 = Integer part of detected value is 32764.
     * |        |          |01101 = Integer part of detected value is 32765.
     * |        |          |01110 = Integer part of detected value is 32766.
     * |        |          |01111 = Integer part of detected value is 32767.
     * |        |          |10000 = Integer part of detected value is 32768.
     * |        |          |10001 = Integer part of detected value is 32769.
     * |        |          |10010 = Integer part of detected value is 32770.
     * |        |          |10011 = Integer part of detected value is 32771.
     * |        |          |10100 = Integer part of detected value is 32772.
     * |        |          |10101 = Integer part of detected value is 32773.
     * |        |          |10110 = Integer part of detected value is 32774.
     * |        |          |10111 = Integer part of detected value is 32775.
     * |        |          |11000 = Integer part of detected value is 32776.
     * |        |          |11001 = Integer part of detected value is 32777.
     * |        |          |11010 = Integer part of detected value is 32778.
     * |        |          |11011 = Integer part of detected value is 32779.
     * |        |          |11100 = Integer part of detected value is 32780.
     * |        |          |11101 = Integer part of detected value is 32781.
     * |        |          |11110 = Integer part of detected value is 32782.
     * |        |          |11111 = Integer part of detected value is 32783.
     * |[31]    |FCRBUSY   |Frequency Compensation Register Write Operation Busy (Read Only)
     * |        |          |0 = The new register write operation is acceptable.
     * |        |          |1 = The last write operation is in progress and new register write operation prohibited.
     * |        |          |Note: This bit is only used when DCOMPEN(RTC_CLKFMT[16]) is enabled.
     * @var RTC_T::TIME
     * Offset: 0x0C  RTC Time Loading Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SEC       |1-Sec Time Digit (0~9)
     * |[6:4]   |TENSEC    |10-Sec Time Digit (0~5)
     * |[11:8]  |MIN       |1-Min Time Digit (0~9)
     * |[14:12] |TENMIN    |10-Min Time Digit (0~5)
     * |[19:16] |HR        |1-Hour Time Digit (0~9)
     * |[21:20] |TENHR     |10-Hour Time Digit (0~2)
     * |        |          |When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication (If RTC_TIME[21] is 1, it indicates PM time message.)
     * @var RTC_T::CAL
     * Offset: 0x10  RTC Calendar Loading Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit (0~9)
     * |[5:4]   |TENDAY    |10-Day Calendar Digit (0~3)
     * |[11:8]  |MON       |1-Month Calendar Digit (0~9)
     * |[12]    |TENMON    |10-Month Calendar Digit (0~1)
     * |[19:16] |YEAR      |1-Year Calendar Digit (0~9)
     * |[23:20] |TENYEAR   |10-Year Calendar Digit (0~9)
     * @var RTC_T::CLKFMT
     * Offset: 0x14  RTC Time Scale Selection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |24HEN     |24-hour / 12-hour Time Scale Selection
     * |        |          |The RTC_TIME and RTC_TALM are in 24-hour time scale or 12-hour time scale.
     * |        |          |0 = 12-hour time scale with AM and PM indication selected.
     * |        |          |1 = 24-hour time scale selected.
     * |[16]    |DCOMPEN   |Dynamic Compensation Enable Bit
     * |        |          |0 = Dynamic Compensation Disabled.
     * |        |          |1 = Dynamic Compensation Enabled.
     * @var RTC_T::WEEKDAY
     * Offset: 0x18  RTC Day of the Week Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |WEEKDAY   |Day of the Week Register
     * |        |          |000 = Sunday.
     * |        |          |001 = Monday.
     * |        |          |010 = Tuesday.
     * |        |          |011 = Wednesday.
     * |        |          |100 = Thursday.
     * |        |          |101 = Friday.
     * |        |          |110 = Saturday.
     * |        |          |111 = Reserved.
     * @var RTC_T::TALM
     * Offset: 0x1C  RTC Time Alarm Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SEC       |1-Sec Time Digit of Alarm Setting (0~9)
     * |[6:4]   |TENSEC    |10-Sec Time Digit of Alarm Setting (0~5)
     * |[11:8]  |MIN       |1-Min Time Digit of Alarm Setting (0~9)
     * |[14:12] |TENMIN    |10-Min Time Digit of Alarm Setting (0~5)
     * |[19:16] |HR        |1-Hour Time Digit of Alarm Setting (0~9)
     * |[21:20] |TENHR     |10-Hour Time Digit of Alarm Setting (0~2)
     * |        |          |When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication (If RTC_TIME[21] is 1, it indicates PM time message.)
     * @var RTC_T::CALM
     * Offset: 0x20  RTC Calendar Alarm Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit of Alarm Setting (0~9)
     * |[5:4]   |TENDAY    |10-Day Calendar Digit of Alarm Setting (0~3)
     * |[11:8]  |MON       |1-Month Calendar Digit of Alarm Setting (0~9)
     * |[12]    |TENMON    |10-Month Calendar Digit of Alarm Setting (0~1)
     * |[19:16] |YEAR      |1-Year Calendar Digit of Alarm Setting (0~9)
     * |[23:20] |TENYEAR   |10-Year Calendar Digit of Alarm Setting (0~9)
     * @var RTC_T::LEAPYEAR
     * Offset: 0x24  RTC Leap Year Indicator Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LEAPYEAR  |Leap Year Indication (Read Only)
     * |        |          |0 = This year is not a leap year.
     * |        |          |1 = This year is leap year.
     * @var RTC_T::INTEN
     * Offset: 0x28  RTC Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ALMIEN    |Alarm Interrupt Enable Bit
     * |        |          |Set ALMIEN to 1 can also enable chip wake-up function when RTC alarm interrupt event is generated.
     * |        |          |0 = RTC Alarm interrupt Disabled.
     * |        |          |1 = RTC Alarm interrupt Enabled.
     * |[1]     |TICKIEN   |Time Tick Interrupt Enable Bit
     * |        |          |Set TICKIEN to 1 can also enable chip wake-up function when RTC tick interrupt event is generated.
     * |        |          |0 = RTC Time Tick interrupt Disabled.
     * |        |          |1 = RTC Time Tick interrupt Enabled.
     * |[8]     |TAMP0IEN  |Tamper 0 Interrupt Enable Bit
     * |        |          |Set TAMP0IEN to 1 can also enable chip wake-up function when tamper 0 interrupt event is generated.
     * |        |          |0 = Tamper 0 interrupt Disabled.
     * |        |          |1 = Tamper 0 interrupt Enabled.
     * |[9]     |TAMP1IEN  |Tamper 1 or Pair 0 Interrupt Enable Bit
     * |        |          |Set TAMP1IEN to 1 can also enable chip wake-up function when tamper 1 interrupt event is generated.
     * |        |          |0 = Tamper 1 or Pair 0 interrupt Disabled.
     * |        |          |1 = Tamper 1 or Pair 0 interrupt Enabled.
     * |[10]    |TAMP2IEN  |Tamper 2 Interrupt Enable Bit
     * |        |          |Set TAMP2IEN to 1 can also enable chip wake-up function when tamper 2 interrupt event is generated.
     * |        |          |0 = Tamper 2 interrupt Disabled.
     * |        |          |1 = Tamper 2 interrupt Enabled.
     * |[11]    |TAMP3IEN  |Tamper 3 or Pair 1 Interrupt Enable Bit
     * |        |          |Set TAMP3IEN to 1 can also enable chip wake-up function when tamper 3 interrupt event is generated.
     * |        |          |0 = Tamper 3 or Pair 1 interrupt Disabled.
     * |        |          |1 = Tamper 3 or Pair 1 interrupt Enabled.
     * |[12]    |TAMP4IEN  |Tamper 4 Interrupt Enable Bit
     * |        |          |Set TAMP4IEN to 1 can also enable chip wake-up function when tamper 4 interrupt event is generated.
     * |        |          |0 = Tamper 4 interrupt Disabled.
     * |        |          |1 = Tamper 4 interrupt Enabled.
     * |[13]    |TAMP5IEN  |Tamper 5 or Pair 2 Interrupt Enable Bit
     * |        |          |Set TAMP5IEN to 1 can also enable chip wake-up function when tamper 5 interrupt event is generated.
     * |        |          |0 = Tamper 5 or Pair 2 interrupt Disabled.
     * |        |          |1 = Tamper 5 or Pair 2 interrupt Enabled.
     * |[24]    |CLKFIEN   |LXT Clock Frequency Monitor Fail Interrupt Enable Bit
     * |        |          |0 = LXT Frequency Fail interrupt Disabled.
     * |        |          |1 = LXT Frequency Fail interrupt Enabled.
     * |[25]    |CLKSTIEN  |LXT Clock Frequency Monitor Stop Interrupt Enable Bit
     * |        |          |0 = LXT Frequency Stop interrupt Disabled.
     * |        |          |1 = LXT Frequency Stop interrupt Enabled.
     * @var RTC_T::INTSTS
     * Offset: 0x2C  RTC Interrupt Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ALMIF     |RTC Alarm Interrupt Flag
     * |        |          |0 = Alarm condition is not matched.
     * |        |          |1 = Alarm condition is matched.
     * |        |          |Note: Write 1 to clear this bit.
     * |[1]     |TICKIF    |RTC Time Tick Interrupt Flag
     * |        |          |0 = Tick condition does not occur.
     * |        |          |1 = Tick condition occur.
     * |        |          |Note: Write 1 to clear this bit.
     * |[8]     |TAMP0IF   |Tamper 0 Interrupt Flag
     * |        |          |This bit is set when TAMP0_PIN detected level non-equal TAMP0LV (RTC_TAMPCTL[9]).
     * |        |          |0 = No Tamper 0 interrupt flag is generated.
     * |        |          |1 = Tamper 0 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[9]     |TAMP1IF   |Tamper 1 or Pair 0 Interrupt Flag
     * |        |          |This bit is set when TAMP1_PIN detected level non-equal TAMP1LV (RTC_TAMPCTL[13]) or TAMP0_PIN and TAMP1_PIN disconnected during DYNPR0EN (RTC_TAMPCTL[15]) is activated.
     * |        |          |0 = No Tamper 1 or Pair 0 interrupt flag is generated.
     * |        |          |1 = Tamper 1 or Pair 0 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[10]    |TAMP2IF   |Tamper 2 Interrupt Flag
     * |        |          |This bit is set when TAMP2_PIN detected level non-equal TAMP2LV (RTC_TAMPCTL[17]).
     * |        |          |0 = No Tamper 2 interrupt flag is generated.
     * |        |          |1 = Tamper 2 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[11]    |TAMP3IF   |Tamper 3 or Pair 1 Interrupt Flag
     * |        |          |This bit is set when TAMP3_PIN detected level non-equal TAMP3LV (RTC_TAMPCTL[21]) or TAMP2_PIN and TAMP3_PIN disconnected during DYNPR1EN (RTC_TAMPCTL[23]) is activated or
     * |        |          |TAMP0_PIN and TAMP3_PIN disconnected during DYNPR1EN (RTC_TAMPCTL[23]) and DYN1ISS (RTC_TAMPCTL[0]) are activated.
     * |        |          |0 = No Tamper 3 or Pair 1 interrupt flag is generated.
     * |        |          |1 = Tamper 3 or Pair 1 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[12]    |TAMP4IF   |Tamper 4 Interrupt Flag
     * |        |          |This bit is set when TAMP4_PIN detected level non-equal TAMP4LV (RTC_TAMPCTL[25]).
     * |        |          |0 = No Tamper 4 interrupt flag is generated.
     * |        |          |1 = Tamper 4 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[13]    |TAMP5IF   |Tamper 5 or Pair 2 Interrupt Flag
     * |        |          |This bit is set when TAMP5_PIN detected level non-equal TAMP5LV (RTC_TAMPCTL[29]) or TAMP4_PIN and TAMP5_PIN disconnected during DYNPR2EN (RTC_TAMPCTL[31]) is activated or
     * |        |          |TAMP0_PIN and TAMP5_PIN disconnected during DYNPR2EN (RTC_TAMPCTL[31]) and DYN2ISS (RTC_TAMPCTL[1]) are activated.
     * |        |          |0 = No Tamper 5 or Pair 2 interrupt flag is generated.
     * |        |          |1 = Tamper 5 or Pair 2 interrupt flag is generated.
     * |        |          |Note1: Write 1 to clear this bit.
     * |        |          |Note2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note3: Need to clear all TAMPxIF, after that, new RTC_TAMPTIME and RTC_TAMPCAL values are loaded while a tamper event occurred.
     * |[24]    |CLKFIF    |LXT Clock Frequency Monitor Fail Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is abnormal.
     * |        |          |Note1: Write 1 to clear the bit to 0.
     * |        |          |Note2: LXT detector will automatic disable when Fail/Stop Flag rise, resume after Fail/Stop Flag clear.
     * |[25]    |CLKSTIF   |LXT Clock Frequency Monitor Stop Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is almost stop.
     * |        |          |Note1: Write 1 to clear the bit to 0.
     * |        |          |Note2: LXT detector will automatic disable when Fail/Stop Flag rise, resume after Fail/Stop Flag clear.
     * @var RTC_T::TICK
     * Offset: 0x30  RTC Time Tick Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TICK      |Time Tick Register
     * |        |          |These bits are used to select RTC time tick period for Periodic Time Tick Interrupt request.
     * |        |          |000 = Time tick is 1 second.
     * |        |          |001 = Time tick is 1/2 second.
     * |        |          |010 = Time tick is 1/4 second.
     * |        |          |011 = Time tick is 1/8 second.
     * |        |          |100 = Time tick is 1/16 second.
     * |        |          |101 = Time tick is 1/32 second.
     * |        |          |110 = Time tick is 1/64 second.
     * |        |          |111 = Time tick is 1/128 second.
     * @var RTC_T::TAMSK
     * Offset: 0x34  RTC Time Alarm Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MSEC      |Mask 1-Sec Time Digit of Alarm Setting (0~9)
     * |[1]     |MTENSEC   |Mask 10-Sec Time Digit of Alarm Setting (0~5)
     * |[2]     |MMIN      |Mask 1-Min Time Digit of Alarm Setting (0~9)
     * |[3]     |MTENMIN   |Mask 10-Min Time Digit of Alarm Setting (0~5)
     * |[4]     |MHR       |Mask 1-Hour Time Digit of Alarm Setting (0~9)
     * |        |          |Note: MHR function is only for 24-hour time scale mode.
     * |[5]     |MTENHR    |Mask 10-Hour Time Digit of Alarm Setting (0~2)
     * |        |          |Note: MTENHR function is only for 24-hour time scale mode.
     * @var RTC_T::CAMSK
     * Offset: 0x38  RTC Calendar Alarm Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MDAY      |Mask 1-Day Calendar Digit of Alarm Setting (0~9)
     * |[1]     |MTENDAY   |Mask 10-Day Calendar Digit of Alarm Setting (0~3)
     * |[2]     |MMON      |Mask 1-Month Calendar Digit of Alarm Setting (0~9)
     * |[3]     |MTENMON   |Mask 10-Month Calendar Digit of Alarm Setting (0~1)
     * |[4]     |MYEAR     |Mask 1-Year Calendar Digit of Alarm Setting (0~9)
     * |[5]     |MTENYEAR  |Mask 10-Year Calendar Digit of Alarm Setting (0~9)
     * @var RTC_T::SPRCTL
     * Offset: 0x3C  RTC Spare Functional Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2]     |SPRRWEN   |Spare Register Enable Bit
     * |        |          |0 = Spare register Disabled.
     * |        |          |1 = Spare register Enabled.
     * |        |          |Note: When spare register is disabled, RTC_SPR0 ~ RTC_SPR19 cannot be accessed.
     * |[5]     |SPRCSTS   |SPR Clear Flag
     * |        |          |This bit indicates if the RTC_SPR0 ~ RTC_SPR19 content is cleared when specify tamper event is detected.
     * |        |          |0 = Spare register content is not cleared.
     * |        |          |1 = Spare register content is cleared.
     * |        |          |Note 1: Writes 1 to clear this bit.
     * |        |          |Note 2: This bit keep 1 when RTC_INTSTS[13:8] or RTC_INTSTS[25:24] are not equal zero.
     * |[16]    |LXTFCLR   |LXT Clock Fail/Stop to Clear Spare Enable Bit
     * |        |          |0 = LXT Fail/Stop to clear Spare register content Disabled.
     * |        |          |1 = LXT Fail/Stop to clear Spare register content Enabled.
     * @var RTC_T::SPR[20]
     * Offset: 0x40 ~ 0x8C  RTC Spare Register 0 ~ 19
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected,
     * |        |          |LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::LXTCTL
     * Offset: 0x100  RTC 32.768 kHz Oscillator Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LIRC32KEN |Enable LIRC32K Source
     * |        |          |0 = LIRC32K Disabled.
     * |        |          |1 = LIRC32K Enabled.
     * |[3:1]   |GAIN      |Oscillator Gain Option
     * |        |          |User can select oscillator gain according to crystal external loading and operating temperature range.
     * |        |          |The larger gain value corresponding to stronger driving capability and higher power consumption.
     * |        |          |000 = L0 mode.
     * |        |          |001 = L1 mode.
     * |        |          |010 = L2 mode.
     * |        |          |011 = L3 mode.
     * |        |          |100 = L4 mode.
     * |        |          |101 = L5 mode.
     * |        |          |110 = L6 mode.
     * |        |          |111 = L7 mode (Default).
     * |[6]     |C32KSEL   |Clock 32K Source Selection
     * |        |          |0 = Clock source from external low speed crystal oscillator (LXT).
     * |        |          |1 = Clock source from internal low speed RC 32K oscillator (LIRC32K).
     * |[7]     |RTCCKSEL  |RTC Clock Source Selection
     * |        |          |0 = Clock source from external low speed crystal oscillator (LXT) or internal low speed RC 32K oscillator (LIRC32K) depended on C32KSEL value.
     * |        |          |1 = Clock source from internal low speed RC oscillator (LIRC).
     * |[8]     |IOCTLSEL  |IO Pin Backup Control Selection
     * |        |          |When low speed 32 kHz oscillator is disabled or TAMPxEN is disabled,
     * |        |          |PF.4 pin (X32KO pin), PF.5 pin (X32KI pin) or PF.6~11 pin (TAMPERx pin) can be used as GPIO function.
     * |        |          |User can program IOCTLSEL to decide PF.4~11 I/O function is controlled by system power domain GPIO module or VBAT power domain RTC_GPIOCTL0/1 control register.
     * |        |          |0 = PF.4~11 pin I/O function is controlled by GPIO module.
     * |        |          |1 = PF.4~11 pin I/O function is controlled by VBAT power domain.
     * |        |          |Note: IOCTLSEL will automatically be set by hardware to 1 when system power is off and any writable RTC registers has been written at RTCCKEN(CLK_APBCLK0[1]) enabled.
     * @var RTC_T::GPIOCTL0
     * Offset: 0x104  RTC GPIO Control 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE0   |IO Operation Mode
     * |        |          |00 = PF.4 is input only mode.
     * |        |          |01 = PF.4 is output push pull mode.
     * |        |          |10 = PF.4 is open drain mode.
     * |        |          |11 = PF.4 is quasi-bidirectional mod.
     * |[2]     |DOUT0     |IO Output Data
     * |        |          |0 = PF.4 output low.
     * |        |          |1 = PF.4 output high.
     * |[3]     |DINOFF0   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.4 digital input path Enabled.
     * |        |          |1 = PF.4 digital input path Disabled (digital input tied to low).
     * |[5:4]   |PUSEL0    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.4 I/O pull-up or pull-down.
     * |        |          |00 = PF.4 pull-up and pull-down Disabled.
     * |        |          |01 = PF.4 pull-up Enabled.
     * |        |          |10 = PF.4 pull-down Enabled.
     * |        |          |11 = PF.4 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE0 is set as input tri-state and open-drain mode.
     * |[9:8]   |OPMODE1   |IO Operation Mode
     * |        |          |00 = PF.5 is input only mode.
     * |        |          |01 = PF.5 is output push pull mode.
     * |        |          |10 = PF.5 is open drain mode.
     * |        |          |11 = PF.5 is quasi-bidirectional mod.
     * |[10]    |DOUT1     |IO Output Data
     * |        |          |0 = PF.5 output low.
     * |        |          |1 = PF.5 output high.
     * |[11     |DINOFF1   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.5 digital input path Enabled.
     * |        |          |1 = PF.5 digital input path Disabled (digital input tied to low).
     * |[13:12] |PUSEL1    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.5 I/O pull-up or pull-down.
     * |        |          |00 = PF.5 pull-up and pull-down Disabled.
     * |        |          |01 = PF.5 pull-up Enabled.
     * |        |          |10 = PF.5 pull-down Enabled.
     * |        |          |11 = PF.5 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE1 is set as input tri-state and open-drain mode.
     * |[17:16] |OPMODE2   |IO Operation Mode
     * |        |          |00 = PF.6 is input only mode.
     * |        |          |01 = PF.6 is output push pull mode.
     * |        |          |10 = PF.6 is open drain mode.
     * |        |          |11 = PF.6 is quasi-bidirectional mod.
     * |[18]    |DOUT2     |IO Output Data
     * |        |          |0 = PF.6 output low.
     * |        |          |1 = PF.6 output high.
     * |[19     |DINOFF2   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.6 digital input path Enabled.
     * |        |          |1 = PF.6 digital input path Disabled (digital input tied to low).
     * |[21:20] |PUSEL2    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.6 I/O pull-up or pull-down.
     * |        |          |00 = PF.6 pull-up and pull-down Disabled.
     * |        |          |01 = PF.6 pull-up Enabled.
     * |        |          |10 = PF.6 pull-down Enabled.
     * |        |          |11 = PF.6 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE2 is set as input tri-state and open-drain mode.
     * |[25:24] |OPMODE3   |IO Operation Mode
     * |        |          |00 = PF.7 is input only mode.
     * |        |          |01 = PF.7 is output push pull mode.
     * |        |          |10 = PF.7 is open drain mode.
     * |        |          |11 = PF.7 is quasi-bidirectional mod.
     * |[26]    |DOUT3     |IO Output Data
     * |        |          |0 = PF.7 output low.
     * |        |          |1 = PF.7 output high.
     * |[27     |DINOFF3   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.7 digital input path Enabled.
     * |        |          |1 = PF.7 digital input path Disabled (digital input tied to low).
     * |[29:28] |PUSEL3    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.7 I/O pull-up or pull-down.
     * |        |          |00 = PF.7 pull-up and pull-down Disabled.
     * |        |          |01 = PF.7 pull-up Enabled.
     * |        |          |10 = PF.7 pull-down Enabled.
     * |        |          |11 = PF.7 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE3 is set as input tri-state and open-drain mode.
     * @var RTC_T::GPIOCTL1
     * Offset: 0x108  RTC GPIO Control 1 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE4   |IO Operation Mode
     * |        |          |00 = PF.8 is input only mode.
     * |        |          |01 = PF.8 is output push pull mode.
     * |        |          |10 = PF.8 is open drain mode.
     * |        |          |11 = PF.8 is quasi-bidirectional mod.
     * |[2]     |DOUT4     |IO Output Data
     * |        |          |0 = PF.8 output low.
     * |        |          |1 = PF.8 output high.
     * |[3]     |DINOFF4   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.8 digital input path Enabled.
     * |        |          |1 = PF.8 digital input path Disabled (digital input tied to low).
     * |[5:4]   |PUSEL4    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.8 I/O pull-up or pull-down.
     * |        |          |00 = PF.8 pull-up and pull-down Disabled.
     * |        |          |01 = PF.8 pull-up Enabled.
     * |        |          |10 = PF.8 pull-down Enabled.
     * |        |          |11 = PF.8 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE4 is set as input tri-state and open-drain mode.
     * |[9:8]   |OPMODE5   |IO Operation Mode
     * |        |          |00 = PF.9 is input only mode.
     * |        |          |01 = PF.9 is output push pull mode.
     * |        |          |10 = PF.9 is open drain mode.
     * |        |          |11 = PF.9 is quasi-bidirectional mod.
     * |[10]    |DOUT5     |IO Output Data
     * |        |          |0 = PF.9 output low.
     * |        |          |1 = PF.9 output high.
     * |[11     |DINOFF5   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.9 digital input path Enabled.
     * |        |          |1 = PF.9 digital input path Disabled (digital input tied to low).
     * |[13:12] |PUSEL5    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.9 I/O pull-up or pull-down.
     * |        |          |00 = PF.9 pull-up and pull-down Disabled.
     * |        |          |01 = PF.9 pull-up Enabled.
     * |        |          |10 = PF.9 pull-down Enabled.
     * |        |          |11 = PF.9 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE5 is set as input tri-state and open-drain mode.
     * |[17:16] |OPMODE6   |IO Operation Mode
     * |        |          |00 = PF.10 is input only mode.
     * |        |          |01 = PF.10 is output push pull mode.
     * |        |          |10 = PF.10 is open drain mode.
     * |        |          |11 = PF.10 is quasi-bidirectional mod.
     * |[18]    |DOUT6     |IO Output Data
     * |        |          |0 = PF.10 output low.
     * |        |          |1 = PF.10 output high.
     * |[19     |DINOFF6   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.10 digital input path Enabled.
     * |        |          |1 = PF.10 digital input path Disabled (digital input tied to low).
     * |[21:20] |PUSEL6    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.10 I/O pull-up or pull-down.
     * |        |          |00 = PF.10 pull-up and pull-down Disabled.
     * |        |          |01 = PF.10 pull-up Enabled.
     * |        |          |10 = PF.10 pull-down Enabled.
     * |        |          |11 = PF.10 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE6 is set as input tri-state and open-drain mode.
     * |[25:24] |OPMODE7   |IO Operation Mode
     * |        |          |00 = PF.11 is input only mode.
     * |        |          |01 = PF.11 is output push pull mode.
     * |        |          |10 = PF.11 is open drain mode.
     * |        |          |11 = PF.11 is quasi-bidirectional mod.
     * |[26]    |DOUT7     |IO Output Data
     * |        |          |0 = PF.11 output low.
     * |        |          |1 = PF.11 output high.
     * |[27     |DINOFF7   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PF.11 digital input path Enabled.
     * |        |          |1 = PF.11 digital input path Disabled (digital input tied to low).
     * |[29:28] |PUSEL7    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PF.11 I/O pull-up or pull-down.
     * |        |          |00 = PF.11 pull-up and pull-down Disabled.
     * |        |          |01 = PF.11 pull-up Enabled.
     * |        |          |10 = PF.11 pull-down Enabled.
     * |        |          |11 = PF.11 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up/pull-down control register is only valid when OPMODE7 is set as input tri-state and open-drain mode.
     * @var RTC_T::DSTCTL
     * Offset: 0x110  RTC Daylight Saving Time Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ADDHR     |Add 1 Hour
     * |        |          |0 = No effect.
     * |        |          |1 = Indicates RTC hour digit has been added one hour for summer time change.
     * |[1]     |SUBHR     |Subtract 1 Hour
     * |        |          |0 = No effect.
     * |        |          |1 = Indicates RTC hour digit has been subtracted one hour for winter time change.
     * |[2]     |DSBAK     |Daylight Saving Back
     * |        |          |0 = Daylight Saving Change is not performed.
     * |        |          |1 = Daylight Saving Change is performed.
     * @var RTC_T::TAMPCTL
     * Offset: 0x120  RTC Tamper Pin Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |DYN1ISS   |Dynamic Pair 1 Input Source Select
     * |        |          |This bit determine Tamper 3 input is from Tamper 2 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 2.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit is effective only when DYNPR1EN (RTC_TAMPCTL[23]) and DYNPR0EN (RTC_TAMPCTL[15]) are set.
     * |[1]     |DYN2ISS   |Dynamic Pair 2 Input Source Select
     * |        |          |This bit determine Tamper 5 input is from Tamper 4 or Tamper 0 in dynamic mode.
     * |        |          |0 = Tamper input is from Tamper 4.
     * |        |          |1 = Tamper input is from Tamper 0.
     * |        |          |Note: This bit is effective only when DYNPR2EN (RTC_TAMPCTL[31]) and DYNPR0EN (RTC_TAMPCTL[15]) are set.
     * |[3]     |DYNSRC    |Dynamic Reference Pattern
     * |        |          |This fields determine the new reference pattern when current pattern run out in dynamic pair mode.
     * |        |          |0 = The new reference pattern is generated by random number generator when the reference pattern run out.
     * |        |          |1 = The new reference pattern is repeated from SEED (RTC_TAMPSEED[31:0]) when the reference pattern run out.
     * |        |          |Note: After this bit is modified, the SEEDRLD (RTC_TAMPCTL[4]) should be set.
     * |[4]     |SEEDRLD   |Reload New Seed for PRNG Engine
     * |        |          |Setting this bit, the tamper configuration will be reload.
     * |        |          |0 = Generating key based on the current seed.
     * |        |          |1 = Reload new seed.
     * |        |          |Note 1: Before this bit is set, the tamper configuration should be set to complete and this bit will be auto clear to 0 after reload new seed completed.
     * |        |          |Note 2: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[7:5]   |DYNRATE   |Dynamic Change Rate
     * |        |          |This item is choice the dynamic tamper output change rate.
     * |        |          |000 = 2^10 * RTC_CLK.
     * |        |          |001 = 2^11 * RTC_CLK.
     * |        |          |010 = 2^12 * RTC_CLK.
     * |        |          |011 = 2^13 * RTC_CLK.
     * |        |          |100 = 2^14 * RTC_CLK.
     * |        |          |101 = 2^15 * RTC_CLK.
     * |        |          |110 = 2^16 * RTC_CLK.
     * |        |          |111 = 2^17 * RTC_CLK.
     * |        |          |Note: After revising this field, set SEEDRLD (RTC_TAMPCTL[4]) can reload change rate immediately.
     * |[8]     |TAMP0EN   |Tamper0 Detect Enable Bit
     * |        |          |0 = Tamper 0 detect Disabled.
     * |        |          |1 = Tamper 0 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[9]     |TAMP0LV   |Tamper 0 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[10]    |TAMP0DBEN |Tamper 0 De-bounce Enable Bit
     * |        |          |0 = Tamper 0 de-bounce Disabled.
     * |        |          |1 = Tamper 0 de-bounce Enabled.
     * |[12]    |TAMP1EN   |Tamper 1 Detect Enable Bit
     * |        |          |0 = Tamper 1 detect Disabled.
     * |        |          |1 = Tamper 1 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[13]    |TAMP1LV   |Tamper 1 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[14]    |TAMP1DBEN |Tamper 1 De-bounce Enable Bit
     * |        |          |0 = Tamper 1 de-bounce Disabled.
     * |        |          |1 = Tamper 1 de-bounce Enabled.
     * |[15]    |DYNPR0EN  |Dynamic Pair 0 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * |[16]    |TAMP2EN   |Tamper 2 Detect Enable Bit
     * |        |          |0 = Tamper 2 detect Disabled.
     * |        |          |1 = Tamper 2 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[17]    |TAMP2LV   |Tamper 2 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[18]    |TAMP2DBEN |Tamper 2 De-bounce Enable Bit
     * |        |          |0 = Tamper 2 de-bounce Disabled.
     * |        |          |1 = Tamper 2 de-bounce Enabled.
     * |[20]    |TAMP3EN   |Tamper 3 Detect Enable Bit
     * |        |          |0 = Tamper 3 detect Disabled.
     * |        |          |1 = Tamper 3 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[21]    |TAMP3LV   |Tamper 3 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[22]    |TAMP3DBEN |Tamper 3 De-bounce Enable Bit
     * |        |          |0 = Tamper 3 de-bounce Disabled.
     * |        |          |1 = Tamper 3 de-bounce Enabled.
     * |[23]    |DYNPR1EN  |Dynamic Pair 1 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * |[24]    |TAMP4EN   |Tamper4 Detect Enable Bit
     * |        |          |0 = Tamper 4 detect Disabled.
     * |        |          |1 = Tamper 4 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[25]    |TAMP4LV   |Tamper 4 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[26]    |TAMP4DBEN |Tamper 4 De-bounce Enable Bit
     * |        |          |0 = Tamper 4 de-bounce Disabled.
     * |        |          |1 = Tamper 4 de-bounce Enabled.
     * |[28]    |TAMP5EN   |Tamper 5 Detect Enable Bit
     * |        |          |0 = Tamper 5 detect Disabled.
     * |        |          |1 = Tamper 5 detect Enabled.
     * |        |          |Note1: The reference is RTC clock. Tamper detector need sync 2 ~ 3 RTC clock.
     * |[29]    |TAMP5LV   |Tamper 5 Level
     * |        |          |This bit depend on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[30]    |TAMP5DBEN |Tamper 5 De-bounce Enable Bit
     * |        |          |0 = Tamper 5 de-bounce Disabled.
     * |        |          |1 = Tamper 5 de-bounce Enabled.
     * |[31]    |DYNPR2EN  |Dynamic Pair 2 Enable Bit
     * |        |          |0 = Static detect.
     * |        |          |1 = Dynamic detect.
     * @var RTC_T::TAMPSEED
     * Offset: 0x128  RTC Tamper Dynamic Seed Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SEED      |Seed Value
     * @var RTC_T::TAMPTIME
     * Offset: 0x130  RTC Tamper Time Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SEC       |1-Sec Time Digit of TAMPER Time (0~9)
     * |[6:4]   |TENSEC    |10-Sec Time Digit of TAMPER Time (0~5)
     * |[11:8]  |MIN       |1-Min Time Digit of TAMPER Time (0~9)
     * |[14:12] |TENMIN    |10-Min Time Digit of TAMPER Time (0~5)
     * |[19:16] |HR        |1-Hour Time Digit of TAMPER Time (0~9)
     * |[21:20] |TENHR     |10-Hour Time Digit of TAMPER Time (0~2)
     * |        |          |Note: 24-hour time scale only.
     * @var RTC_T::TAMPCAL
     * Offset: 0x134  RTC Tamper Calendar Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit of TAMPER Calendar (0~9)
     * |[5:4]   |TENDAY    |10-Day Calendar Digit of TAMPER Calendar (0~3)
     * |[11:8]  |MON       |1-Month Calendar Digit of TAMPER Calendar (0~9)
     * |[12]    |TENMON    |10-Month Calendar Digit of TAMPER Calendar (0~1)
     * |[19:16] |YEAR      |1-Year Calendar Digit of TAMPER Calendar (0~9)
     * |[23:20] |TENYEAR   |10-Year Calendar Digit of TAMPER Calendar (0~9)
     * @var RTC_T::CLKDCTL
     * Offset: 0x140  RTC Clock Fail Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LXTFDEN   |LXT Clock Fail/Stop Detector Enable Bit
     * |        |          |0 = LXT clock Fail/Stop detector Disabled.
     * |        |          |1 = LXT clock Fail/Stop detector Enabled.
     * |        |          |Note: LXT detector will automatic disable when Fail/Stop Flag rise, resume after Fail/Stop Flag clear.
     * |[1]     |LXTFSW    |LXT Clock Fail Detector Switch LIRC32K Enable Bit
     * |        |          |0 = LXT clock Fail switch LIRC32K Disabled.
     * |        |          |1 = LXT clock Fail detector rise, RTC clock source switch from LIRC32K.
     * |        |          |If LXT clock fail detector flag CLKFIF (RTC_INTSTS[24]) is generated, RTC clock source will switch to LIRC32K automatically.
     * |[2]     |LXTSTSW   |LXT Clock Stop Detector Switch LIRC32K Enable Bit
     * |        |          |0 = LXT clock Stop switch LIRC32K Disabled.
     * |        |          |1 = LXT clock Stop detector rise, RTC clock source switch from LIRC32K.
     * |        |          |If LXT clock stop detector flag CLKSTIF (RTC_INTSTS[25]) is generated, RTC clock source will switch to LIRC32K automatically
     * |[16]    |SWLIRCF   |LXT Clock Detector Fail/Stop Switch LIRC32K Flag (Read Only)
     * |        |          |0 = Indicate RTC clock source from LXT.
     * |        |          |1 = Indicate RTC clock source from LIRC32K.
     * |[17]    |LXTSLOWF  |LXT Slower Than LIRC32K Flag (Read Only)
     * |        |          |0 = LXT frequency faster than LIRC32K.
     * |        |          |1 = LXT frequency is slowly.
     * |        |          |Note: LXTSLOWF is vaild during CLKSTIF (RTC_INTSTS[25]) or CLKFIF (RTC_INTSTS[24]) rising.
     * @var RTC_T::CDBR
     * Offset: 0x144  RTC Clock Frequency Detector Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |STOPBD    |LXT Clock Stop Frequency Detector Stop Boundary
     * |        |          |These bits define the stop value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than STOPBD, the LXT frequency detect Stop interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the maximum value of LXT among 256 LIRC32K clock time.
     * |[23:16] |FAILBD    |LXT Clock Frequency Detector Fail Boundary
     * |        |          |These bits define the fail value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than FAILBD, the LXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the maximum value of LXT among 256 LIRC32K clock time.
     */
    __IO uint32_t INIT;                  /*!< [0x0000] RTC Initiation Register                                          */
    __I uint32_t  RESERVE0[1];           /* 0x4 */
    __IO uint32_t FREQADJ;               /*!< [0x0008] RTC Frequency Compensation Register                              */
    __IO uint32_t TIME;                  /*!< [0x000c] RTC Time Loading Register                                        */
    __IO uint32_t CAL;                   /*!< [0x0010] RTC Calendar Loading Register                                    */
    __IO uint32_t CLKFMT;                /*!< [0x0014] RTC Time Scale Selection Register                                */
    __IO uint32_t WEEKDAY;               /*!< [0x0018] RTC Day of the Week Register                                     */
    __IO uint32_t TALM;                  /*!< [0x001c] RTC Time Alarm Register                                          */
    __IO uint32_t CALM;                  /*!< [0x0020] RTC Calendar Alarm Register                                      */
    __I  uint32_t LEAPYEAR;              /*!< [0x0024] RTC Leap Year Indicator Register                                 */
    __IO uint32_t INTEN;                 /*!< [0x0028] RTC Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x002c] RTC Interrupt Status Register                                    */
    __IO uint32_t TICK;                  /*!< [0x0030] RTC Time Tick Register                                           */
    __IO uint32_t TAMSK;                 /*!< [0x0034] RTC Time Alarm Mask Register                                     */
    __IO uint32_t CAMSK;                 /*!< [0x0038] RTC Calendar Alarm Mask Register                                 */
    __IO uint32_t SPRCTL;                /*!< [0x003c] RTC Spare Functional Control Register                            */
    __IO uint32_t SPR[20];               /*!< [0x0040] ~ [0x008C] RTC Spare Register 0 ~ 19                             */
    __I  uint32_t RESERVE1[28];          /* 0x90 ~ 0xfc */
    __IO uint32_t LXTCTL;                /*!< [0x0100] RTC 32.768 kHz Oscillator Control Register                       */
    __IO uint32_t GPIOCTL0;              /*!< [0x0104] RTC GPIO Control 0 Register                                      */
    __IO uint32_t GPIOCTL1;              /*!< [0x0108] RTC GPIO Control 1 Register                                      */
    __I  uint32_t RESERVE2[1];           /* 0x10c */
    __IO uint32_t DSTCTL;                /*!< [0x0110] RTC Daylight Saving Time Control Register                        */
    __I  uint32_t RESERVE3[3];           /* 0x114 ~ 0x11c */
    __IO uint32_t TAMPCTL;               /*!< [0x0120] RTC Tamper Pin Control Register                                  */
    __I  uint32_t RESERVE4[1];           /* 0x124 */
    __IO uint32_t TAMPSEED;              /*!< [0x0128] RTC Tamper Dynamic Seed Register                                 */
    __I  uint32_t RESERVE5[1];           /* 0x12c */
    __I  uint32_t TAMPTIME;              /*!< [0x0130] RTC Tamper Time Register                                         */
    __I  uint32_t TAMPCAL;               /*!< [0x0134] RTC Tamper Calendar Register                                     */
    __I  uint32_t RESERVE6[2];           /* 0x138 ~ 0x13c */
    __IO uint32_t CLKDCTL;               /*!< [0x0140] RTC Clock Fail Detector Control Register                         */
    __IO uint32_t CDBR;                  /*!< [0x0144] RTC Clock Frequency Detector Boundary Register                   */

} RTC_T;

/**
    @addtogroup RTC_CONST RTC Bit Field Definition
    Constant Definitions for RTC Controller
  @{
*/

#define RTC_INIT_ACTIVE_Pos              (0)                                               /*!< RTC_T::INIT: ACTIVE Position           */
#define RTC_INIT_ACTIVE_Msk              (0x1ul << RTC_INIT_ACTIVE_Pos)                    /*!< RTC_T::INIT: ACTIVE Mask               */

#define RTC_INIT_INIT_Pos                (1)                                               /*!< RTC_T::INIT: INIT Position             */
#define RTC_INIT_INIT_Msk                (0x7ffffffful << RTC_INIT_INIT_Pos)               /*!< RTC_T::INIT: INIT Mask                 */

#define RTC_FREQADJ_FRACTION_Pos         (0)                                               /*!< RTC_T::FREQADJ: FRACTION Position      */
#define RTC_FREQADJ_FRACTION_Msk         (0x3ful << RTC_FREQADJ_FRACTION_Pos)              /*!< RTC_T::FREQADJ: FRACTION Mask          */

#define RTC_FREQADJ_INTEGER_Pos          (8)                                               /*!< RTC_T::FREQADJ: INTEGER Position       */
#define RTC_FREQADJ_INTEGER_Msk          (0x1ful << RTC_FREQADJ_INTEGER_Pos)               /*!< RTC_T::FREQADJ: INTEGER Mask           */

#define RTC_FREQADJ_FCRBUSY_Pos          (31)                                              /*!< RTC_T::FREQADJ: FCRBUSY Position       */
#define RTC_FREQADJ_FCRBUSY_Msk          (0x1ul << RTC_FREQADJ_FCRBUSY_Pos)                /*!< RTC_T::FREQADJ: FCRBUSY Mask           */

#define RTC_TIME_SEC_Pos                 (0)                                               /*!< RTC_T::TIME: SEC Position              */
#define RTC_TIME_SEC_Msk                 (0xful << RTC_TIME_SEC_Pos)                       /*!< RTC_T::TIME: SEC Mask                  */

#define RTC_TIME_TENSEC_Pos              (4)                                               /*!< RTC_T::TIME: TENSEC Position           */
#define RTC_TIME_TENSEC_Msk              (0x7ul << RTC_TIME_TENSEC_Pos)                    /*!< RTC_T::TIME: TENSEC Mask               */

#define RTC_TIME_MIN_Pos                 (8)                                               /*!< RTC_T::TIME: MIN Position              */
#define RTC_TIME_MIN_Msk                 (0xful << RTC_TIME_MIN_Pos)                       /*!< RTC_T::TIME: MIN Mask                  */

#define RTC_TIME_TENMIN_Pos              (12)                                              /*!< RTC_T::TIME: TENMIN Position           */
#define RTC_TIME_TENMIN_Msk              (0x7ul << RTC_TIME_TENMIN_Pos)                    /*!< RTC_T::TIME: TENMIN Mask               */

#define RTC_TIME_HR_Pos                  (16)                                              /*!< RTC_T::TIME: HR Position               */
#define RTC_TIME_HR_Msk                  (0xful << RTC_TIME_HR_Pos)                        /*!< RTC_T::TIME: HR Mask                   */

#define RTC_TIME_TENHR_Pos               (20)                                              /*!< RTC_T::TIME: TENHR Position            */
#define RTC_TIME_TENHR_Msk               (0x3ul << RTC_TIME_TENHR_Pos)                     /*!< RTC_T::TIME: TENHR Mask                */

#define RTC_CAL_DAY_Pos                  (0)                                               /*!< RTC_T::CAL: DAY Position               */
#define RTC_CAL_DAY_Msk                  (0xful << RTC_CAL_DAY_Pos)                        /*!< RTC_T::CAL: DAY Mask                   */

#define RTC_CAL_TENDAY_Pos               (4)                                               /*!< RTC_T::CAL: TENDAY Position            */
#define RTC_CAL_TENDAY_Msk               (0x3ul << RTC_CAL_TENDAY_Pos)                     /*!< RTC_T::CAL: TENDAY Mask                */

#define RTC_CAL_MON_Pos                  (8)                                               /*!< RTC_T::CAL: MON Position               */
#define RTC_CAL_MON_Msk                  (0xful << RTC_CAL_MON_Pos)                        /*!< RTC_T::CAL: MON Mask                   */

#define RTC_CAL_TENMON_Pos               (12)                                              /*!< RTC_T::CAL: TENMON Position            */
#define RTC_CAL_TENMON_Msk               (0x1ul << RTC_CAL_TENMON_Pos)                     /*!< RTC_T::CAL: TENMON Mask                */

#define RTC_CAL_YEAR_Pos                 (16)                                              /*!< RTC_T::CAL: YEAR Position              */
#define RTC_CAL_YEAR_Msk                 (0xful << RTC_CAL_YEAR_Pos)                       /*!< RTC_T::CAL: YEAR Mask                  */

#define RTC_CAL_TENYEAR_Pos              (20)                                              /*!< RTC_T::CAL: TENYEAR Position           */
#define RTC_CAL_TENYEAR_Msk              (0xful << RTC_CAL_TENYEAR_Pos)                    /*!< RTC_T::CAL: TENYEAR Mask               */

#define RTC_CLKFMT_24HEN_Pos             (0)                                               /*!< RTC_T::CLKFMT: 24HEN Position          */
#define RTC_CLKFMT_24HEN_Msk             (0x1ul << RTC_CLKFMT_24HEN_Pos)                   /*!< RTC_T::CLKFMT: 24HEN Mask              */

#define RTC_CLKFMT_DCOMPEN_Pos           (16)                                              /*!< RTC_T::CLKFMT: DCOMPEN Position        */
#define RTC_CLKFMT_DCOMPEN_Msk           (0x1ul << RTC_CLKFMT_DCOMPEN_Pos)                 /*!< RTC_T::CLKFMT: DCOMPEN Mask            */

#define RTC_WEEKDAY_WEEKDAY_Pos          (0)                                               /*!< RTC_T::WEEKDAY: WEEKDAY Position       */
#define RTC_WEEKDAY_WEEKDAY_Msk          (0x7ul << RTC_WEEKDAY_WEEKDAY_Pos)                /*!< RTC_T::WEEKDAY: WEEKDAY Mask           */

#define RTC_TALM_SEC_Pos                 (0)                                               /*!< RTC_T::TALM: SEC Position              */
#define RTC_TALM_SEC_Msk                 (0xful << RTC_TALM_SEC_Pos)                       /*!< RTC_T::TALM: SEC Mask                  */

#define RTC_TALM_TENSEC_Pos              (4)                                               /*!< RTC_T::TALM: TENSEC Position           */
#define RTC_TALM_TENSEC_Msk              (0x7ul << RTC_TALM_TENSEC_Pos)                    /*!< RTC_T::TALM: TENSEC Mask               */

#define RTC_TALM_MIN_Pos                 (8)                                               /*!< RTC_T::TALM: MIN Position              */
#define RTC_TALM_MIN_Msk                 (0xful << RTC_TALM_MIN_Pos)                       /*!< RTC_T::TALM: MIN Mask                  */

#define RTC_TALM_TENMIN_Pos              (12)                                              /*!< RTC_T::TALM: TENMIN Position           */
#define RTC_TALM_TENMIN_Msk              (0x7ul << RTC_TALM_TENMIN_Pos)                    /*!< RTC_T::TALM: TENMIN Mask               */

#define RTC_TALM_HR_Pos                  (16)                                              /*!< RTC_T::TALM: HR Position               */
#define RTC_TALM_HR_Msk                  (0xful << RTC_TALM_HR_Pos)                        /*!< RTC_T::TALM: HR Mask                   */

#define RTC_TALM_TENHR_Pos               (20)                                              /*!< RTC_T::TALM: TENHR Position            */
#define RTC_TALM_TENHR_Msk               (0x3ul << RTC_TALM_TENHR_Pos)                     /*!< RTC_T::TALM: TENHR Mask                */

#define RTC_CALM_DAY_Pos                 (0)                                               /*!< RTC_T::CALM: DAY Position              */
#define RTC_CALM_DAY_Msk                 (0xful << RTC_CALM_DAY_Pos)                       /*!< RTC_T::CALM: DAY Mask                  */

#define RTC_CALM_TENDAY_Pos              (4)                                               /*!< RTC_T::CALM: TENDAY Position           */
#define RTC_CALM_TENDAY_Msk              (0x3ul << RTC_CALM_TENDAY_Pos)                    /*!< RTC_T::CALM: TENDAY Mask               */

#define RTC_CALM_MON_Pos                 (8)                                               /*!< RTC_T::CALM: MON Position              */
#define RTC_CALM_MON_Msk                 (0xful << RTC_CALM_MON_Pos)                       /*!< RTC_T::CALM: MON Mask                  */

#define RTC_CALM_TENMON_Pos              (12)                                              /*!< RTC_T::CALM: TENMON Position           */
#define RTC_CALM_TENMON_Msk              (0x1ul << RTC_CALM_TENMON_Pos)                    /*!< RTC_T::CALM: TENMON Mask               */

#define RTC_CALM_YEAR_Pos                (16)                                              /*!< RTC_T::CALM: YEAR Position             */
#define RTC_CALM_YEAR_Msk                (0xful << RTC_CALM_YEAR_Pos)                      /*!< RTC_T::CALM: YEAR Mask                 */

#define RTC_CALM_TENYEAR_Pos             (20)                                              /*!< RTC_T::CALM: TENYEAR Position          */
#define RTC_CALM_TENYEAR_Msk             (0xful << RTC_CALM_TENYEAR_Pos)                   /*!< RTC_T::CALM: TENYEAR Mask              */

#define RTC_LEAPYEAR_LEAPYEAR_Pos        (0)                                               /*!< RTC_T::LEAPYEAR: LEAPYEAR Position     */
#define RTC_LEAPYEAR_LEAPYEAR_Msk        (0x1ul << RTC_LEAPYEAR_LEAPYEAR_Pos)              /*!< RTC_T::LEAPYEAR: LEAPYEAR Mask         */

#define RTC_INTEN_ALMIEN_Pos             (0)                                               /*!< RTC_T::INTEN: ALMIEN Position          */
#define RTC_INTEN_ALMIEN_Msk             (0x1ul << RTC_INTEN_ALMIEN_Pos)                   /*!< RTC_T::INTEN: ALMIEN Mask              */

#define RTC_INTEN_TICKIEN_Pos            (1)                                               /*!< RTC_T::INTEN: TICKIEN Position         */
#define RTC_INTEN_TICKIEN_Msk            (0x1ul << RTC_INTEN_TICKIEN_Pos)                  /*!< RTC_T::INTEN: TICKIEN Mask             */

#define RTC_INTEN_TAMP0IEN_Pos           (8)                                               /*!< RTC_T::INTEN: TAMP0IEN Position        */
#define RTC_INTEN_TAMP0IEN_Msk           (0x1ul << RTC_INTEN_TAMP0IEN_Pos)                 /*!< RTC_T::INTEN: TAMP0IEN Mask            */

#define RTC_INTEN_TAMP1IEN_Pos           (9)                                               /*!< RTC_T::INTEN: TAMP1IEN Position        */
#define RTC_INTEN_TAMP1IEN_Msk           (0x1ul << RTC_INTEN_TAMP1IEN_Pos)                 /*!< RTC_T::INTEN: TAMP1IEN Mask            */

#define RTC_INTEN_TAMP2IEN_Pos           (10)                                              /*!< RTC_T::INTEN: TAMP2IEN Position        */
#define RTC_INTEN_TAMP2IEN_Msk           (0x1ul << RTC_INTEN_TAMP2IEN_Pos)                 /*!< RTC_T::INTEN: TAMP2IEN Mask            */

#define RTC_INTEN_TAMP3IEN_Pos           (11)                                              /*!< RTC_T::INTEN: TAMP3IEN Position        */
#define RTC_INTEN_TAMP3IEN_Msk           (0x1ul << RTC_INTEN_TAMP3IEN_Pos)                 /*!< RTC_T::INTEN: TAMP3IEN Mask            */

#define RTC_INTEN_TAMP4IEN_Pos           (12)                                              /*!< RTC_T::INTEN: TAMP4IEN Position        */
#define RTC_INTEN_TAMP4IEN_Msk           (0x1ul << RTC_INTEN_TAMP4IEN_Pos)                 /*!< RTC_T::INTEN: TAMP4IEN Mask            */

#define RTC_INTEN_TAMP5IEN_Pos           (13)                                              /*!< RTC_T::INTEN: TAMP5IEN Position        */
#define RTC_INTEN_TAMP5IEN_Msk           (0x1ul << RTC_INTEN_TAMP5IEN_Pos)                 /*!< RTC_T::INTEN: TAMP5IEN Mask            */

#define RTC_INTEN_CLKFIEN_Pos            (24)                                              /*!< RTC_T::INTEN: CLKFIEN Position         */
#define RTC_INTEN_CLKFIEN_Msk            (0x1ul << RTC_INTEN_CLKFIEN_Pos)                  /*!< RTC_T::INTEN: CLKFIEN Mask             */

#define RTC_INTEN_CLKSTIEN_Pos           (25)                                              /*!< RTC_T::INTEN: CLKSTIEN Position        */
#define RTC_INTEN_CLKSTIEN_Msk           (0x1ul << RTC_INTEN_CLKSTIEN_Pos)                 /*!< RTC_T::INTEN: CLKSTIEN Mask            */

#define RTC_INTSTS_ALMIF_Pos             (0)                                               /*!< RTC_T::INTSTS: ALMIF Position          */
#define RTC_INTSTS_ALMIF_Msk             (0x1ul << RTC_INTSTS_ALMIF_Pos)                   /*!< RTC_T::INTSTS: ALMIF Mask              */

#define RTC_INTSTS_TICKIF_Pos            (1)                                               /*!< RTC_T::INTSTS: TICKIF Position         */
#define RTC_INTSTS_TICKIF_Msk            (0x1ul << RTC_INTSTS_TICKIF_Pos)                  /*!< RTC_T::INTSTS: TICKIF Mask             */

#define RTC_INTSTS_TAMP0IF_Pos           (8)                                               /*!< RTC_T::INTSTS: TAMP0IF Position        */
#define RTC_INTSTS_TAMP0IF_Msk           (0x1ul << RTC_INTSTS_TAMP0IF_Pos)                 /*!< RTC_T::INTSTS: TAMP0IF Mask            */

#define RTC_INTSTS_TAMP1IF_Pos           (9)                                               /*!< RTC_T::INTSTS: TAMP1IF Position        */
#define RTC_INTSTS_TAMP1IF_Msk           (0x1ul << RTC_INTSTS_TAMP1IF_Pos)                 /*!< RTC_T::INTSTS: TAMP1IF Mask            */

#define RTC_INTSTS_TAMP2IF_Pos           (10)                                              /*!< RTC_T::INTSTS: TAMP2IF Position        */
#define RTC_INTSTS_TAMP2IF_Msk           (0x1ul << RTC_INTSTS_TAMP2IF_Pos)                 /*!< RTC_T::INTSTS: TAMP2IF Mask            */

#define RTC_INTSTS_TAMP3IF_Pos           (11)                                              /*!< RTC_T::INTSTS: TAMP3IF Position        */
#define RTC_INTSTS_TAMP3IF_Msk           (0x1ul << RTC_INTSTS_TAMP3IF_Pos)                 /*!< RTC_T::INTSTS: TAMP3IF Mask            */

#define RTC_INTSTS_TAMP4IF_Pos           (12)                                              /*!< RTC_T::INTSTS: TAMP4IF Position        */
#define RTC_INTSTS_TAMP4IF_Msk           (0x1ul << RTC_INTSTS_TAMP4IF_Pos)                 /*!< RTC_T::INTSTS: TAMP4IF Mask            */

#define RTC_INTSTS_TAMP5IF_Pos           (13)                                              /*!< RTC_T::INTSTS: TAMP5IF Position        */
#define RTC_INTSTS_TAMP5IF_Msk           (0x1ul << RTC_INTSTS_TAMP5IF_Pos)                 /*!< RTC_T::INTSTS: TAMP5IF Mask            */

#define RTC_INTSTS_CLKFIF_Pos            (24)                                              /*!< RTC_T::INTSTS: CLKFIF Position         */
#define RTC_INTSTS_CLKFIF_Msk            (0x1ul << RTC_INTSTS_CLKFIF_Pos)                  /*!< RTC_T::INTSTS: CLKFIF Mask             */

#define RTC_INTSTS_CLKSTIF_Pos           (25)                                              /*!< RTC_T::INTSTS: CLKSTIF Position        */
#define RTC_INTSTS_CLKSTIF_Msk           (0x1ul << RTC_INTSTS_CLKSTIF_Pos)                 /*!< RTC_T::INTSTS: CLKSTIF Mask            */

#define RTC_TICK_TICK_Pos                (0)                                               /*!< RTC_T::TICK: TICK Position             */
#define RTC_TICK_TICK_Msk                (0x7ul << RTC_TICK_TICK_Pos)                      /*!< RTC_T::TICK: TICK Mask                 */

#define RTC_TAMSK_MSEC_Pos               (0)                                               /*!< RTC_T::TAMSK: MSEC Position            */
#define RTC_TAMSK_MSEC_Msk               (0x1ul << RTC_TAMSK_MSEC_Pos)                     /*!< RTC_T::TAMSK: MSEC Mask                */

#define RTC_TAMSK_MTENSEC_Pos            (1)                                               /*!< RTC_T::TAMSK: MTENSEC Position         */
#define RTC_TAMSK_MTENSEC_Msk            (0x1ul << RTC_TAMSK_MTENSEC_Pos)                  /*!< RTC_T::TAMSK: MTENSEC Mask             */

#define RTC_TAMSK_MMIN_Pos               (2)                                               /*!< RTC_T::TAMSK: MMIN Position            */
#define RTC_TAMSK_MMIN_Msk               (0x1ul << RTC_TAMSK_MMIN_Pos)                     /*!< RTC_T::TAMSK: MMIN Mask                */

#define RTC_TAMSK_MTENMIN_Pos            (3)                                               /*!< RTC_T::TAMSK: MTENMIN Position         */
#define RTC_TAMSK_MTENMIN_Msk            (0x1ul << RTC_TAMSK_MTENMIN_Pos)                  /*!< RTC_T::TAMSK: MTENMIN Mask             */

#define RTC_TAMSK_MHR_Pos                (4)                                               /*!< RTC_T::TAMSK: MHR Position             */
#define RTC_TAMSK_MHR_Msk                (0x1ul << RTC_TAMSK_MHR_Pos)                      /*!< RTC_T::TAMSK: MHR Mask                 */

#define RTC_TAMSK_MTENHR_Pos             (5)                                               /*!< RTC_T::TAMSK: MTENHR Position          */
#define RTC_TAMSK_MTENHR_Msk             (0x1ul << RTC_TAMSK_MTENHR_Pos)                   /*!< RTC_T::TAMSK: MTENHR Mask              */

#define RTC_CAMSK_MDAY_Pos               (0)                                               /*!< RTC_T::CAMSK: MDAY Position            */
#define RTC_CAMSK_MDAY_Msk               (0x1ul << RTC_CAMSK_MDAY_Pos)                     /*!< RTC_T::CAMSK: MDAY Mask                */

#define RTC_CAMSK_MTENDAY_Pos            (1)                                               /*!< RTC_T::CAMSK: MTENDAY Position         */
#define RTC_CAMSK_MTENDAY_Msk            (0x1ul << RTC_CAMSK_MTENDAY_Pos)                  /*!< RTC_T::CAMSK: MTENDAY Mask             */

#define RTC_CAMSK_MMON_Pos               (2)                                               /*!< RTC_T::CAMSK: MMON Position            */
#define RTC_CAMSK_MMON_Msk               (0x1ul << RTC_CAMSK_MMON_Pos)                     /*!< RTC_T::CAMSK: MMON Mask                */

#define RTC_CAMSK_MTENMON_Pos            (3)                                               /*!< RTC_T::CAMSK: MTENMON Position         */
#define RTC_CAMSK_MTENMON_Msk            (0x1ul << RTC_CAMSK_MTENMON_Pos)                  /*!< RTC_T::CAMSK: MTENMON Mask             */

#define RTC_CAMSK_MYEAR_Pos              (4)                                               /*!< RTC_T::CAMSK: MYEAR Position           */
#define RTC_CAMSK_MYEAR_Msk              (0x1ul << RTC_CAMSK_MYEAR_Pos)                    /*!< RTC_T::CAMSK: MYEAR Mask               */

#define RTC_CAMSK_MTENYEAR_Pos           (5)                                               /*!< RTC_T::CAMSK: MTENYEAR Position        */
#define RTC_CAMSK_MTENYEAR_Msk           (0x1ul << RTC_CAMSK_MTENYEAR_Pos)                 /*!< RTC_T::CAMSK: MTENYEAR Mask            */

#define RTC_SPRCTL_SPRRWEN_Pos           (2)                                               /*!< RTC_T::SPRCTL: SPRRWEN Position        */
#define RTC_SPRCTL_SPRRWEN_Msk           (0x1ul << RTC_SPRCTL_SPRRWEN_Pos)                 /*!< RTC_T::SPRCTL: SPRRWEN Mask            */

#define RTC_SPRCTL_SPRCSTS_Pos           (5)                                               /*!< RTC_T::SPRCTL: SPRCSTS Position        */
#define RTC_SPRCTL_SPRCSTS_Msk           (0x1ul << RTC_SPRCTL_SPRCSTS_Pos)                 /*!< RTC_T::SPRCTL: SPRCSTS Mask            */

#define RTC_SPRCTL_LXTFCLR_Pos           (16)                                              /*!< RTC_T::SPRCTL: LXTFCLR Position        */
#define RTC_SPRCTL_LXTFCLR_Msk           (0x1ul << RTC_SPRCTL_LXTFCLR_Pos)                 /*!< RTC_T::SPRCTL: LXTFCLR Mask            */

#define RTC_SPR0_SPARE_Pos               (0)                                               /*!< RTC_T::SPR0: SPARE Position            */
#define RTC_SPR0_SPARE_Msk               (0xfffffffful << RTC_SPR0_SPARE_Pos)              /*!< RTC_T::SPR0: SPARE Mask                */

#define RTC_SPR1_SPARE_Pos               (0)                                               /*!< RTC_T::SPR1: SPARE Position            */
#define RTC_SPR1_SPARE_Msk               (0xfffffffful << RTC_SPR1_SPARE_Pos)              /*!< RTC_T::SPR1: SPARE Mask                */

#define RTC_SPR2_SPARE_Pos               (0)                                               /*!< RTC_T::SPR2: SPARE Position            */
#define RTC_SPR2_SPARE_Msk               (0xfffffffful << RTC_SPR2_SPARE_Pos)              /*!< RTC_T::SPR2: SPARE Mask                */

#define RTC_SPR3_SPARE_Pos               (0)                                               /*!< RTC_T::SPR3: SPARE Position            */
#define RTC_SPR3_SPARE_Msk               (0xfffffffful << RTC_SPR3_SPARE_Pos)              /*!< RTC_T::SPR3: SPARE Mask                */

#define RTC_SPR4_SPARE_Pos               (0)                                               /*!< RTC_T::SPR4: SPARE Position            */
#define RTC_SPR4_SPARE_Msk               (0xfffffffful << RTC_SPR4_SPARE_Pos)              /*!< RTC_T::SPR4: SPARE Mask                */

#define RTC_SPR5_SPARE_Pos               (0)                                               /*!< RTC_T::SPR5: SPARE Position            */
#define RTC_SPR5_SPARE_Msk               (0xfffffffful << RTC_SPR5_SPARE_Pos)              /*!< RTC_T::SPR5: SPARE Mask                */

#define RTC_SPR6_SPARE_Pos               (0)                                               /*!< RTC_T::SPR6: SPARE Position            */
#define RTC_SPR6_SPARE_Msk               (0xfffffffful << RTC_SPR6_SPARE_Pos)              /*!< RTC_T::SPR6: SPARE Mask                */

#define RTC_SPR7_SPARE_Pos               (0)                                               /*!< RTC_T::SPR7: SPARE Position            */
#define RTC_SPR7_SPARE_Msk               (0xfffffffful << RTC_SPR7_SPARE_Pos)              /*!< RTC_T::SPR7: SPARE Mask                */

#define RTC_SPR8_SPARE_Pos               (0)                                               /*!< RTC_T::SPR8: SPARE Position            */
#define RTC_SPR8_SPARE_Msk               (0xfffffffful << RTC_SPR8_SPARE_Pos)              /*!< RTC_T::SPR8: SPARE Mask                */

#define RTC_SPR9_SPARE_Pos               (0)                                               /*!< RTC_T::SPR9: SPARE Position            */
#define RTC_SPR9_SPARE_Msk               (0xfffffffful << RTC_SPR9_SPARE_Pos)              /*!< RTC_T::SPR9: SPARE Mask                */

#define RTC_SPR10_SPARE_Pos              (0)                                               /*!< RTC_T::SPR10: SPARE Position           */
#define RTC_SPR10_SPARE_Msk              (0xfffffffful << RTC_SPR10_SPARE_Pos)             /*!< RTC_T::SPR10: SPARE Mask               */

#define RTC_SPR11_SPARE_Pos              (0)                                               /*!< RTC_T::SPR11: SPARE Position           */
#define RTC_SPR11_SPARE_Msk              (0xfffffffful << RTC_SPR11_SPARE_Pos)             /*!< RTC_T::SPR11: SPARE Mask               */

#define RTC_SPR12_SPARE_Pos              (0)                                               /*!< RTC_T::SPR12: SPARE Position           */
#define RTC_SPR12_SPARE_Msk              (0xfffffffful << RTC_SPR12_SPARE_Pos)             /*!< RTC_T::SPR12: SPARE Mask               */

#define RTC_SPR13_SPARE_Pos              (0)                                               /*!< RTC_T::SPR13: SPARE Position           */
#define RTC_SPR13_SPARE_Msk              (0xfffffffful << RTC_SPR13_SPARE_Pos)             /*!< RTC_T::SPR13: SPARE Mask               */

#define RTC_SPR14_SPARE_Pos              (0)                                               /*!< RTC_T::SPR14: SPARE Position           */
#define RTC_SPR14_SPARE_Msk              (0xfffffffful << RTC_SPR14_SPARE_Pos)             /*!< RTC_T::SPR14: SPARE Mask               */

#define RTC_SPR15_SPARE_Pos              (0)                                               /*!< RTC_T::SPR15: SPARE Position           */
#define RTC_SPR15_SPARE_Msk              (0xfffffffful << RTC_SPR15_SPARE_Pos)             /*!< RTC_T::SPR15: SPARE Mask               */

#define RTC_SPR16_SPARE_Pos              (0)                                               /*!< RTC_T::SPR16: SPARE Position           */
#define RTC_SPR16_SPARE_Msk              (0xfffffffful << RTC_SPR16_SPARE_Pos)             /*!< RTC_T::SPR16: SPARE Mask               */

#define RTC_SPR17_SPARE_Pos              (0)                                               /*!< RTC_T::SPR17: SPARE Position           */
#define RTC_SPR17_SPARE_Msk              (0xfffffffful << RTC_SPR17_SPARE_Pos)             /*!< RTC_T::SPR17: SPARE Mask               */

#define RTC_SPR18_SPARE_Pos              (0)                                               /*!< RTC_T::SPR18: SPARE Position           */
#define RTC_SPR18_SPARE_Msk              (0xfffffffful << RTC_SPR18_SPARE_Pos)             /*!< RTC_T::SPR18: SPARE Mask               */

#define RTC_SPR19_SPARE_Pos              (0)                                               /*!< RTC_T::SPR19: SPARE Position           */
#define RTC_SPR19_SPARE_Msk              (0xfffffffful << RTC_SPR19_SPARE_Pos)             /*!< RTC_T::SPR19: SPARE Mask               */

#define RTC_LXTCTL_LIRC32KEN_Pos         (0)                                               /*!< RTC_T::LXTCTL: LIRC32KEN Position      */
#define RTC_LXTCTL_LIRC32KEN_Msk         (0x1ul << RTC_LXTCTL_LIRC32KEN_Pos)               /*!< RTC_T::LXTCTL: LIRC32KEN Mask          */

#define RTC_LXTCTL_GAIN_Pos              (1)                                               /*!< RTC_T::LXTCTL: GAIN Position           */
#define RTC_LXTCTL_GAIN_Msk              (0x7ul << RTC_LXTCTL_GAIN_Pos)                    /*!< RTC_T::LXTCTL: GAIN Mask               */

#define RTC_LXTCTL_C32KSEL_Pos           (6)                                               /*!< RTC_T::LXTCTL: C32KSEL Position        */
#define RTC_LXTCTL_C32KSEL_Msk           (0x1ul << RTC_LXTCTL_C32KSEL_Pos)                 /*!< RTC_T::LXTCTL: C32KSEL Mask            */

#define RTC_LXTCTL_RTCCKSEL_Pos          (7)                                               /*!< RTC_T::LXTCTL: RTCCKSEL Position       */
#define RTC_LXTCTL_RTCCKSEL_Msk          (0x1ul << RTC_LXTCTL_RTCCKSEL_Pos)                /*!< RTC_T::LXTCTL: RTCCKSEL Mask           */

#define RTC_LXTCTL_IOCTLSEL_Pos          (8)                                               /*!< RTC_T::LXTCTL: IOCTLSEL Position       */
#define RTC_LXTCTL_IOCTLSEL_Msk          (0x1ul << RTC_LXTCTL_IOCTLSEL_Pos)                /*!< RTC_T::LXTCTL: IOCTLSEL Mask           */

#define RTC_GPIOCTL0_OPMODE0_Pos         (0)                                               /*!< RTC_T::GPIOCTL0: OPMODE0 Position      */
#define RTC_GPIOCTL0_OPMODE0_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE0_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE0 Mask          */

#define RTC_GPIOCTL0_DOUT0_Pos           (2)                                               /*!< RTC_T::GPIOCTL0: DOUT0 Position        */
#define RTC_GPIOCTL0_DOUT0_Msk           (0x1ul << RTC_GPIOCTL0_DOUT0_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT0 Mask            */

#define RTC_GPIOCTL0_DINOFF0_Pos         (3)                                               /*!< RTC_T::GPIOCTL0: DINOFF0 Position      */
#define RTC_GPIOCTL0_DINOFF0_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF0_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF0 Mask          */

#define RTC_GPIOCTL0_PUSEL0_Pos          (4)                                               /*!< RTC_T::GPIOCTL0: PUSEL0 Position       */
#define RTC_GPIOCTL0_PUSEL0_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL0_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL0 Mask           */

#define RTC_GPIOCTL0_OPMODE1_Pos         (8)                                               /*!< RTC_T::GPIOCTL0: OPMODE1 Position      */
#define RTC_GPIOCTL0_OPMODE1_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE1_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE1 Mask          */

#define RTC_GPIOCTL0_DOUT1_Pos           (10)                                              /*!< RTC_T::GPIOCTL0: DOUT1 Position        */
#define RTC_GPIOCTL0_DOUT1_Msk           (0x1ul << RTC_GPIOCTL0_DOUT1_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT1 Mask            */

#define RTC_GPIOCTL0_DINOFF1_Pos         (11)                                              /*!< RTC_T::GPIOCTL0: DINOFF1 Position      */
#define RTC_GPIOCTL0_DINOFF1_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF1_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF1 Mask          */

#define RTC_GPIOCTL0_PUSEL1_Pos          (12)                                              /*!< RTC_T::GPIOCTL0: PUSEL1 Position       */
#define RTC_GPIOCTL0_PUSEL1_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL1_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL1 Mask           */

#define RTC_GPIOCTL0_OPMODE2_Pos         (16)                                              /*!< RTC_T::GPIOCTL0: OPMODE2 Position      */
#define RTC_GPIOCTL0_OPMODE2_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE2_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE2 Mask          */

#define RTC_GPIOCTL0_DOUT2_Pos           (18)                                              /*!< RTC_T::GPIOCTL0: DOUT2 Position        */
#define RTC_GPIOCTL0_DOUT2_Msk           (0x1ul << RTC_GPIOCTL0_DOUT2_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT2 Mask            */

#define RTC_GPIOCTL0_DINOFF2_Pos         (19)                                              /*!< RTC_T::GPIOCTL0: DINOFF2 Position      */
#define RTC_GPIOCTL0_DINOFF2_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF2_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF2 Mask          */

#define RTC_GPIOCTL0_PUSEL2_Pos          (20)                                              /*!< RTC_T::GPIOCTL0: PUSEL2 Position       */
#define RTC_GPIOCTL0_PUSEL2_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL2_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL2 Mask           */

#define RTC_GPIOCTL0_OPMODE3_Pos         (24)                                              /*!< RTC_T::GPIOCTL0: OPMODE3 Position      */
#define RTC_GPIOCTL0_OPMODE3_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE3_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE3 Mask          */

#define RTC_GPIOCTL0_DOUT3_Pos           (26)                                              /*!< RTC_T::GPIOCTL0: DOUT3 Position        */
#define RTC_GPIOCTL0_DOUT3_Msk           (0x1ul << RTC_GPIOCTL0_DOUT3_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT3 Mask            */

#define RTC_GPIOCTL0_DINOFF3_Pos         (27)                                              /*!< RTC_T::GPIOCTL0: DINOFF3 Position      */
#define RTC_GPIOCTL0_DINOFF3_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF3_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF3 Mask          */

#define RTC_GPIOCTL0_PUSEL3_Pos          (28)                                              /*!< RTC_T::GPIOCTL0: PUSEL3 Position       */
#define RTC_GPIOCTL0_PUSEL3_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL3_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL3 Mask           */

#define RTC_GPIOCTL1_OPMODE4_Pos         (0)                                               /*!< RTC_T::GPIOCTL1: OPMODE4 Position      */
#define RTC_GPIOCTL1_OPMODE4_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE4_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE4 Mask          */

#define RTC_GPIOCTL1_DOUT4_Pos           (2)                                               /*!< RTC_T::GPIOCTL1: DOUT4 Position        */
#define RTC_GPIOCTL1_DOUT4_Msk           (0x1ul << RTC_GPIOCTL1_DOUT4_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT4 Mask            */

#define RTC_GPIOCTL0_DINOFF4_Pos         (3)                                               /*!< RTC_T::GPIOCTL1: DINOFF4 Position      */
#define RTC_GPIOCTL0_DINOFF4_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF4_Pos)               /*!< RTC_T::GPIOCTL1: DINOFF4 Mask          */

#define RTC_GPIOCTL1_PUSEL4_Pos          (4)                                               /*!< RTC_T::GPIOCTL1: PUSEL4 Position       */
#define RTC_GPIOCTL1_PUSEL4_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL4_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL4 Mask           */

#define RTC_GPIOCTL1_OPMODE5_Pos         (8)                                               /*!< RTC_T::GPIOCTL1: OPMODE5 Position      */
#define RTC_GPIOCTL1_OPMODE5_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE5_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE5 Mask          */

#define RTC_GPIOCTL1_DOUT5_Pos           (10)                                              /*!< RTC_T::GPIOCTL1: DOUT5 Position        */
#define RTC_GPIOCTL1_DOUT5_Msk           (0x1ul << RTC_GPIOCTL1_DOUT5_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT5 Mask            */

#define RTC_GPIOCTL0_DINOFF5_Pos         (11)                                              /*!< RTC_T::GPIOCTL1: DINOFF5 Position      */
#define RTC_GPIOCTL0_DINOFF5_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF5_Pos)               /*!< RTC_T::GPIOCTL1: DINOFF5 Mask          */

#define RTC_GPIOCTL1_PUSEL5_Pos          (12)                                              /*!< RTC_T::GPIOCTL1: PUSEL5 Position       */
#define RTC_GPIOCTL1_PUSEL5_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL5_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL5 Mask           */

#define RTC_GPIOCTL1_OPMODE6_Pos         (16)                                              /*!< RTC_T::GPIOCTL1: OPMODE6 Position      */
#define RTC_GPIOCTL1_OPMODE6_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE6_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE6 Mask          */

#define RTC_GPIOCTL1_DOUT6_Pos           (18)                                              /*!< RTC_T::GPIOCTL1: DOUT6 Position        */
#define RTC_GPIOCTL1_DOUT6_Msk           (0x1ul << RTC_GPIOCTL1_DOUT6_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT6 Mask            */

#define RTC_GPIOCTL0_DINOFF6_Pos         (19)                                              /*!< RTC_T::GPIOCTL1: DINOFF6 Position      */
#define RTC_GPIOCTL0_DINOFF6_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF6_Pos)               /*!< RTC_T::GPIOCTL1: DINOFF6 Mask          */

#define RTC_GPIOCTL1_PUSEL6_Pos          (20)                                              /*!< RTC_T::GPIOCTL1: PUSEL6 Position       */
#define RTC_GPIOCTL1_PUSEL6_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL6_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL6 Mask           */

#define RTC_GPIOCTL1_OPMODE7_Pos         (24)                                              /*!< RTC_T::GPIOCTL1: OPMODE7 Position      */
#define RTC_GPIOCTL1_OPMODE7_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE7_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE7 Mask          */

#define RTC_GPIOCTL1_DOUT7_Pos           (26)                                              /*!< RTC_T::GPIOCTL1: DOUT7 Position        */
#define RTC_GPIOCTL1_DOUT7_Msk           (0x1ul << RTC_GPIOCTL1_DOUT7_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT7 Mask            */

#define RTC_GPIOCTL0_DINOFF7_Pos         (27)                                              /*!< RTC_T::GPIOCTL1: DINOFF7 Position      */
#define RTC_GPIOCTL0_DINOFF7_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF7_Pos)               /*!< RTC_T::GPIOCTL1: DINOFF7 Mask          */

#define RTC_GPIOCTL1_PUSEL7_Pos          (28)                                              /*!< RTC_T::GPIOCTL1: PUSEL7 Position       */
#define RTC_GPIOCTL1_PUSEL7_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL7_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL7 Mask           */

#define RTC_DSTCTL_ADDHR_Pos             (0)                                               /*!< RTC_T::DSTCTL: ADDHR Position          */
#define RTC_DSTCTL_ADDHR_Msk             (0x1ul << RTC_DSTCTL_ADDHR_Pos)                   /*!< RTC_T::DSTCTL: ADDHR Mask              */

#define RTC_DSTCTL_SUBHR_Pos             (1)                                               /*!< RTC_T::DSTCTL: SUBHR Position          */
#define RTC_DSTCTL_SUBHR_Msk             (0x1ul << RTC_DSTCTL_SUBHR_Pos)                   /*!< RTC_T::DSTCTL: SUBHR Mask              */

#define RTC_DSTCTL_DSBAK_Pos             (2)                                               /*!< RTC_T::DSTCTL: DSBAK Position          */
#define RTC_DSTCTL_DSBAK_Msk             (0x1ul << RTC_DSTCTL_DSBAK_Pos)                   /*!< RTC_T::DSTCTL: DSBAK Mask              */

#define RTC_TAMPCTL_DYN1ISS_Pos          (0)                                               /*!< RTC_T::TAMPCTL: DYN1ISS Position       */
#define RTC_TAMPCTL_DYN1ISS_Msk          (0x1ul << RTC_TAMPCTL_DYN1ISS_Pos)                /*!< RTC_T::TAMPCTL: DYN1ISS Mask           */

#define RTC_TAMPCTL_DYN2ISS_Pos          (1)                                               /*!< RTC_T::TAMPCTL: DYN2ISS Position       */
#define RTC_TAMPCTL_DYN2ISS_Msk          (0x1ul << RTC_TAMPCTL_DYN2ISS_Pos)                /*!< RTC_T::TAMPCTL: DYN2ISS Mask           */

#define RTC_TAMPCTL_DYNSRC_Pos           (3)                                               /*!< RTC_T::TAMPCTL: DYNSRC Position        */
#define RTC_TAMPCTL_DYNSRC_Msk           (0x1ul << RTC_TAMPCTL_DYNSRC_Pos)                 /*!< RTC_T::TAMPCTL: DYNSRC Mask            */

#define RTC_TAMPCTL_SEEDRLD_Pos          (4)                                               /*!< RTC_T::TAMPCTL: SEEDRLD Position       */
#define RTC_TAMPCTL_SEEDRLD_Msk          (0x1ul << RTC_TAMPCTL_SEEDRLD_Pos)                /*!< RTC_T::TAMPCTL: SEEDRLD Mask           */

#define RTC_TAMPCTL_DYNRATE_Pos          (5)                                               /*!< RTC_T::TAMPCTL: DYNRATE Position       */
#define RTC_TAMPCTL_DYNRATE_Msk          (0x7ul << RTC_TAMPCTL_DYNRATE_Pos)                /*!< RTC_T::TAMPCTL: DYNRATE Mask           */

#define RTC_TAMPCTL_TAMP0EN_Pos          (8)                                               /*!< RTC_T::TAMPCTL: TAMP0EN Position       */
#define RTC_TAMPCTL_TAMP0EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP0EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP0EN Mask           */

#define RTC_TAMPCTL_TAMP0LV_Pos          (9)                                               /*!< RTC_T::TAMPCTL: TAMP0LV Position       */
#define RTC_TAMPCTL_TAMP0LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP0LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP0LV Mask           */

#define RTC_TAMPCTL_TAMP0DBEN_Pos        (10)                                              /*!< RTC_T::TAMPCTL: TAMP0DBEN Position     */
#define RTC_TAMPCTL_TAMP0DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP0DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP0DBEN Mask         */

#define RTC_TAMPCTL_TAMP1EN_Pos          (12)                                              /*!< RTC_T::TAMPCTL: TAMP1EN Position       */
#define RTC_TAMPCTL_TAMP1EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP1EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP1EN Mask           */

#define RTC_TAMPCTL_TAMP1LV_Pos          (13)                                              /*!< RTC_T::TAMPCTL: TAMP1LV Position       */
#define RTC_TAMPCTL_TAMP1LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP1LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP1LV Mask           */

#define RTC_TAMPCTL_TAMP1DBEN_Pos        (14)                                              /*!< RTC_T::TAMPCTL: TAMP1DBEN Position     */
#define RTC_TAMPCTL_TAMP1DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP1DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP1DBEN Mask         */

#define RTC_TAMPCTL_DYNPR0EN_Pos         (15)                                              /*!< RTC_T::TAMPCTL: DYNPR0EN Position      */
#define RTC_TAMPCTL_DYNPR0EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR0EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR0EN Mask          */

#define RTC_TAMPCTL_TAMP2EN_Pos          (16)                                              /*!< RTC_T::TAMPCTL: TAMP2EN Position       */
#define RTC_TAMPCTL_TAMP2EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP2EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP2EN Mask           */

#define RTC_TAMPCTL_TAMP2LV_Pos          (17)                                              /*!< RTC_T::TAMPCTL: TAMP2LV Position       */
#define RTC_TAMPCTL_TAMP2LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP2LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP2LV Mask           */

#define RTC_TAMPCTL_TAMP2DBEN_Pos        (18)                                              /*!< RTC_T::TAMPCTL: TAMP2DBEN Position     */
#define RTC_TAMPCTL_TAMP2DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP2DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP2DBEN Mask         */

#define RTC_TAMPCTL_TAMP3EN_Pos          (20)                                              /*!< RTC_T::TAMPCTL: TAMP3EN Position       */
#define RTC_TAMPCTL_TAMP3EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP3EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP3EN Mask           */

#define RTC_TAMPCTL_TAMP3LV_Pos          (21)                                              /*!< RTC_T::TAMPCTL: TAMP3LV Position       */
#define RTC_TAMPCTL_TAMP3LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP3LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP3LV Mask           */

#define RTC_TAMPCTL_TAMP3DBEN_Pos        (22)                                              /*!< RTC_T::TAMPCTL: TAMP3DBEN Position     */
#define RTC_TAMPCTL_TAMP3DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP3DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP3DBEN Mask         */

#define RTC_TAMPCTL_DYNPR1EN_Pos         (23)                                              /*!< RTC_T::TAMPCTL: DYNPR1EN Position      */
#define RTC_TAMPCTL_DYNPR1EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR1EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR1EN Mask          */

#define RTC_TAMPCTL_TAMP4EN_Pos          (24)                                              /*!< RTC_T::TAMPCTL: TAMP4EN Position       */
#define RTC_TAMPCTL_TAMP4EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP4EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP4EN Mask           */

#define RTC_TAMPCTL_TAMP4LV_Pos          (25)                                              /*!< RTC_T::TAMPCTL: TAMP4LV Position       */
#define RTC_TAMPCTL_TAMP4LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP4LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP4LV Mask           */

#define RTC_TAMPCTL_TAMP4DBEN_Pos        (26)                                              /*!< RTC_T::TAMPCTL: TAMP4DBEN Position     */
#define RTC_TAMPCTL_TAMP4DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP4DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP4DBEN Mask         */

#define RTC_TAMPCTL_TAMP5EN_Pos          (28)                                              /*!< RTC_T::TAMPCTL: TAMP5EN Position       */
#define RTC_TAMPCTL_TAMP5EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP5EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP5EN Mask           */

#define RTC_TAMPCTL_TAMP5LV_Pos          (29)                                              /*!< RTC_T::TAMPCTL: TAMP5LV Position       */
#define RTC_TAMPCTL_TAMP5LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP5LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP5LV Mask           */

#define RTC_TAMPCTL_TAMP5DBEN_Pos        (30)                                              /*!< RTC_T::TAMPCTL: TAMP5DBEN Position     */
#define RTC_TAMPCTL_TAMP5DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP5DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP5DBEN Mask         */

#define RTC_TAMPCTL_DYNPR2EN_Pos         (31)                                              /*!< RTC_T::TAMPCTL: DYNPR2EN Position      */
#define RTC_TAMPCTL_DYNPR2EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR2EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR2EN Mask          */

#define RTC_TAMPSEED_SEED_Pos            (0)                                               /*!< RTC_T::TAMPSEED: SEED Position         */
#define RTC_TAMPSEED_SEED_Msk            (0xfffffffful << RTC_TAMPSEED_SEED_Pos)           /*!< RTC_T::TAMPSEED: SEED Mask             */

#define RTC_TAMPTIME_SEC_Pos             (0)                                               /*!< RTC_T::TAMPTIME: SEC Position          */
#define RTC_TAMPTIME_SEC_Msk             (0xful << RTC_TAMPTIME_SEC_Pos)                   /*!< RTC_T::TAMPTIME: SEC Mask              */

#define RTC_TAMPTIME_TENSEC_Pos          (4)                                               /*!< RTC_T::TAMPTIME: TENSEC Position       */
#define RTC_TAMPTIME_TENSEC_Msk          (0x7ul << RTC_TAMPTIME_TENSEC_Pos)                /*!< RTC_T::TAMPTIME: TENSEC Mask           */

#define RTC_TAMPTIME_MIN_Pos             (8)                                               /*!< RTC_T::TAMPTIME: MIN Position          */
#define RTC_TAMPTIME_MIN_Msk             (0xful << RTC_TAMPTIME_MIN_Pos)                   /*!< RTC_T::TAMPTIME: MIN Mask              */

#define RTC_TAMPTIME_TENMIN_Pos          (12)                                              /*!< RTC_T::TAMPTIME: TENMIN Position       */
#define RTC_TAMPTIME_TENMIN_Msk          (0x7ul << RTC_TAMPTIME_TENMIN_Pos)                /*!< RTC_T::TAMPTIME: TENMIN Mask           */

#define RTC_TAMPTIME_HR_Pos              (16)                                              /*!< RTC_T::TAMPTIME: HR Position           */
#define RTC_TAMPTIME_HR_Msk              (0xful << RTC_TAMPTIME_HR_Pos)                    /*!< RTC_T::TAMPTIME: HR Mask               */

#define RTC_TAMPTIME_TENHR_Pos           (20)                                              /*!< RTC_T::TAMPTIME: TENHR Position        */
#define RTC_TAMPTIME_TENHR_Msk           (0x3ul << RTC_TAMPTIME_TENHR_Pos)                 /*!< RTC_T::TAMPTIME: TENHR Mask            */

#define RTC_TAMPCAL_DAY_Pos              (0)                                               /*!< RTC_T::TAMPCAL: DAY Position           */
#define RTC_TAMPCAL_DAY_Msk              (0xful << RTC_TAMPCAL_DAY_Pos)                    /*!< RTC_T::TAMPCAL: DAY Mask               */

#define RTC_TAMPCAL_TENDAY_Pos           (4)                                               /*!< RTC_T::TAMPCAL: TENDAY Position        */
#define RTC_TAMPCAL_TENDAY_Msk           (0x3ul << RTC_TAMPCAL_TENDAY_Pos)                 /*!< RTC_T::TAMPCAL: TENDAY Mask            */

#define RTC_TAMPCAL_MON_Pos              (8)                                               /*!< RTC_T::TAMPCAL: MON Position           */
#define RTC_TAMPCAL_MON_Msk              (0xful << RTC_TAMPCAL_MON_Pos)                    /*!< RTC_T::TAMPCAL: MON Mask               */

#define RTC_TAMPCAL_TENMON_Pos           (12)                                              /*!< RTC_T::TAMPCAL: TENMON Position        */
#define RTC_TAMPCAL_TENMON_Msk           (0x1ul << RTC_TAMPCAL_TENMON_Pos)                 /*!< RTC_T::TAMPCAL: TENMON Mask            */

#define RTC_TAMPCAL_YEAR_Pos             (16)                                              /*!< RTC_T::TAMPCAL: YEAR Position          */
#define RTC_TAMPCAL_YEAR_Msk             (0xful << RTC_TAMPCAL_YEAR_Pos)                   /*!< RTC_T::TAMPCAL: YEAR Mask              */

#define RTC_TAMPCAL_TENYEAR_Pos          (20)                                              /*!< RTC_T::TAMPCAL: TENYEAR Position       */
#define RTC_TAMPCAL_TENYEAR_Msk          (0xful << RTC_TAMPCAL_TENYEAR_Pos)                /*!< RTC_T::TAMPCAL: TENYEAR Mask           */

#define RTC_CLKDCTL_LXTFDEN_Pos          (0)                                               /*!< RTC_T::CLKDCTL: LXTFDEN Position       */
#define RTC_CLKDCTL_LXTFDEN_Msk          (0x1ul << RTC_CLKDCTL_LXTFDEN_Pos)                /*!< RTC_T::CLKDCTL: LXTFDEN Mask           */

#define RTC_CLKDCTL_LXTFSW_Pos           (1)                                               /*!< RTC_T::CLKDCTL: LXTFSW Position        */
#define RTC_CLKDCTL_LXTFSW_Msk           (0x1ul << RTC_CLKDCTL_LXTFSW_Pos)                 /*!< RTC_T::CLKDCTL: LXTFSW Mask            */

#define RTC_CLKDCTL_LXTSTSW_Pos          (2)                                               /*!< RTC_T::CLKDCTL: LXTSTSW Position       */
#define RTC_CLKDCTL_LXTSTSW_Msk          (0x1ul << RTC_CLKDCTL_LXTSTSW_Pos)                /*!< RTC_T::CLKDCTL: LXTSTSW Mask           */

#define RTC_CLKDCTL_SWLIRCF_Pos          (16)                                              /*!< RTC_T::CLKDCTL: SWLIRCF Position       */
#define RTC_CLKDCTL_SWLIRCF_Msk          (0x1ul << RTC_CLKDCTL_SWLIRCF_Pos)                /*!< RTC_T::CLKDCTL: SWLIRCF Mask           */

#define RTC_CLKDCTL_LXTSLOWF_Pos         (17)                                              /*!< RTC_T::CLKDCTL: LXTSLOWF Position      */
#define RTC_CLKDCTL_LXTSLOWF_Msk         (0x1ul << RTC_CLKDCTL_LXTSLOWF_Pos)               /*!< RTC_T::CLKDCTL: LXTSLOWF Mask          */

#define RTC_CDBR_STOPBD_Pos              (0)                                               /*!< RTC_T::CDBR: STOPBD Position           */
#define RTC_CDBR_STOPBD_Msk              (0xfful << RTC_CDBR_STOPBD_Pos)                   /*!< RTC_T::CDBR: STOPBD Mask               */

#define RTC_CDBR_FAILBD_Pos              (16)                                              /*!< RTC_T::CDBR: FAILBD Position           */
#define RTC_CDBR_FAILBD_Msk              (0xfful << RTC_CDBR_FAILBD_Pos)                   /*!< RTC_T::CDBR: FAILBD Mask               */

/**@}*/ /* RTC_CONST */
/**@}*/ /* end of RTC register group */
/**@}*/ /* end of REGISTER group */

#endif /* __RTC_REG_H__ */
