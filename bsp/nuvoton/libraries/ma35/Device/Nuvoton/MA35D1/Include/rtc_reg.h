/**************************************************************************//**
 * @file     rtc_reg.h
 * @brief    RTC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __RTC_REG_H__
#define __RTC_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
  @{
*/



/*---------------------- Real Time Clock Controller -------------------------*/
/**
    @addtogroup RTC Real Time Clock Controller(RTC)
    Memory Mapped Structure for RTC Controller
@{ */

typedef struct
{


    /**
     * @var RTC_T::INIT
     * Offset: 0x00  RTC Initiation Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ACTIVE    |RTC Active Status (Read Only)
     * |        |          |0 = RTC is at reset state.
     * |        |          |1 = RTC is at normal active state.
     * |[31:1]  |INIT      |RTC Initiation (Write Only)
     * |        |          |When RTC block is powered on, RTC is at reset state
     * |        |          |User has to write a number (0xa5eb1357) to INIT to make RTC leave reset state
     * |        |          |Once the INIT is written as 0xa5eb1357, the RTC will be in un-reset state permanently.
     * |        |          |Note: The INIT is a write-only field and read value will be always 0.
     * @var RTC_T::SINFASTS
     * Offset: 0x04  RTC Shared Information Accessable Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |SINFASTS  |RTC Shared Information Accessable Status (Read Only)
     * |        |          |0 = Indicate that the RTCSIAEN(SSPCC_SINFAEN[2]) Disabled.
     * |        |          |1 = Indicate that the RTCSIAEN(SSPCC_SINFAEN[2]) Enabled.
     * |        |          |Note: For RTC control registers access attribute please refer to section 1.1.5.2
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
     * |[3:0]   |SEC       |1-Sec Time Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[6:4]   |TENSEC    |10-Sec Time Digit
     * |        |          |Note: The reasonable value range is 0~5
     * |[11:8]  |MIN       |1-Min Time Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[14:12] |TENMIN    |10-Min Time Digit
     * |        |          |Note: The reasonable value range is 0~5
     * |[19:16] |HR        |1-Hour Time Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[21:20] |TENHR     |10-Hour Time Digit
     * |        |          |When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication (If RTC_TIME[21] is 1, it indicates PM time message.)
     * |        |          |Note: The reasonable value range is 0~2
     * @var RTC_T::CAL
     * Offset: 0x10  RTC Calendar Loading Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[5:4]   |TENDAY    |10-Day Calendar Digit
     * |        |          |Note: The reasonable value range is 0~3
     * |[11:8]  |MON       |1-Month Calendar Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[12]    |TENMON    |10-Month Calendar Digit
     * |        |          |Note: The reasonable value range is 0~1
     * |[19:16] |YEAR      |1-Year Calendar Digit
     * |        |          |Note: The reasonable value range is 0~9
     * |[23:20] |TENYEAR   |10-Year Calendar Digit
     * |        |          |Note: The reasonable value range is 0~9
     * @var RTC_T::CLKFMT
     * Offset: 0x14  RTC Time Scale Selection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |24HEN     |24-hour / 12-hour Time Scale Selection
     * |        |          |Indicates that RTC_TIME and RTC_TALM are in 24-hour time scale or 12-hour time scale
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
     * |[3:0]   |SEC       |1-Sec Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[6:4]   |TENSEC    |10-Sec Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~5
     * |[11:8]  |MIN       |1-Min Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[14:12] |TENMIN    |10-Min Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~5
     * |[19:16] |HR        |1-Hour Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[21:20] |TENHR     |10-Hour Time Digit of Alarm Setting
     * |        |          |When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication (If RTC_TIME[21] is 1, it indicates PM time message.)
     * |        |          |Note: The reasonable value range is 0~2
     * @var RTC_T::CALM
     * Offset: 0x20  RTC Calendar Alarm Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[5:4]   |TENDAY    |10-Day Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~3
     * |[11:8]  |MON       |1-Month Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[12]    |TENMON    |10-Month Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~1
     * |[19:16] |YEAR      |1-Year Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[23:20] |TENYEAR   |10-Year Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
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
     * |[2]     |PSWIEN    |Power Switch Interrupt Enable Bit
     * |        |          |0 = RTC Power Switch interrupt Disabled.
     * |        |          |1 = RTC Power Switch interrupt Enabled.
     * |[3]     |KPRSIEN   |Key Pressed for 1 Second Interrupt Enable Bit
     * |        |          |0 = Key Pressed for 1 Second interrupt Disabled.
     * |        |          |1 = Key Pressed for 1 Second interrupt Enabled.
     * |[8]     |TAMP0IEN  |Tamper 0 Interrupt Enable Bit
     * |        |          |Set TAMP0IEN to 1 can also enable chip wake-up function when tamper 0 interrupt event is generated.
     * |        |          |0 = Tamper 0 interrupt Disabled.
     * |        |          |1 = Tamper 0 interrupt Enabled.
     * |[9]     |TAMP1IEN  |Tamper 1 or Pair 0 Interrupt Enable Bit
     * |        |          |Set TAMP1IEN to 1 can also enable chip wake-up function when tamper 1 interrupt event is generated.
     * |        |          |0 = Tamper 1 or Pair 0 interrupt Disabled.
     * |        |          |1 = Tamper 1 or Pair 0 interrupt Enabled.
     * |[16]    |TAMPIENSubM|Tamper Interrupt for SubM Enable Bit
     * |        |          |0 = Tamper interrupt for SubM Disabled.
     * |        |          |1 = Tamper interrupt for SubM Enabled.
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
     * |        |          |0 = Tick condition did not occur.
     * |        |          |1 = Tick condition occurred.
     * |        |          |Note: Write 1 to clear this bit.
     * |[2]     |PSWST     |Power Switch Interrupt Status
     * |        |          |This bit high indicates the RTC_nRWAKE transition from high to low (user pressed the key) when RTC_RPWR is high (stage machine is in Power_On state).
     * |        |          |When state machine is not in Power_On state, RTC_nRWAKE transition from high to low will not set this bit high.
     * |        |          |Note: Write 1 to clear this bit.
     * |[3]     |KPRSST    |Key Pressed for 1 Second Interrupt Status
     * |        |          |This bit high indicates the RTC_nRWAKE kept in low (user pressed the key) for 1 second when RTC_RPWR is high (stage machine is in Power_On state).
     * |        |          |Note: Write 1 to clear this bit.
     * |[8]     |TAMP0IF   |Tamper 0 Interrupt Flag
     * |        |          |This bit is set when TAMP0_PIN detected level non-equal TAMP0LV (RTC_TAMPCTL[9]).
     * |        |          |0 = No Tamper 0 interrupt flag is generated.
     * |        |          |1 = Tamper 0 interrupt flag is generated.
     * |        |          |Note 1: Write 1 to clear this bit.
     * |        |          |Note 2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note 3: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
     * |[9]     |TAMP1IF   |Tamper 1 or Pair 0 Interrupt Flag
     * |        |          |This bit is set when TAMP1_PIN detected level non-equal TAMP1LV (RTC_TAMPCTL[13]) or TAMP0_PIN and TAMP1_PIN disconnected during DYNPR0EN (RTC_TAMPCTL[15]) is activated.
     * |        |          |0 = No Tamper 1 or Pair 0 interrupt flag is generated.
     * |        |          |1 = Tamper 1 or Pair 0 interrupt flag is generated.
     * |        |          |Note 1: Write 1 to clear this bit.
     * |        |          |Note 2: This interrupt flag will be generated again when Tamper setting condition is not restoration.
     * |        |          |Note 3: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
     * |[24]    |CLKFIF    |LXT Clock Frequency Monitor Fail Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is abnormal.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
     * |[25]    |CLKSTIF   |LXT Clock Frequency Monitor Stop Interrupt Flag
     * |        |          |0 = LXT frequency is normal.
     * |        |          |1 = LXT frequency is almost stop.
     * |        |          |Note 1: Write 1 to clear the bit to 0.
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
     * |[0]     |MSEC      |Mask 1-Sec Time Digit of Alarm Setting
     * |[1]     |MTENSEC   |Mask 10-Sec Time Digit of Alarm Setting
     * |[2]     |MMIN      |Mask 1-Min Time Digit of Alarm Setting
     * |[3]     |MTENMIN   |Mask 10-Min Time Digit of Alarm Setting
     * |[4]     |MHR       |Mask 1-Hour Time Digit of Alarm Setting
     * |[5]     |MTENHR    |Mask 10-Hour Time Digit of Alarm Setting
     * @var RTC_T::CAMSK
     * Offset: 0x38  RTC Calendar Alarm Mask Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MDAY      |Mask 1-Day Calendar Digit of Alarm Setting
     * |[1]     |MTENDAY   |Mask 10-Day Calendar Digit of Alarm Setting
     * |[2]     |MMON      |Mask 1-Month Calendar Digit of Alarm Setting
     * |[3]     |MTENMON   |Mask 10-Month Calendar Digit of Alarm Setting
     * |[4]     |MYEAR     |Mask 1-Year Calendar Digit of Alarm Setting
     * |[5]     |MTENYEAR  |Mask 10-Year Calendar Digit of Alarm Setting
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
     * |        |          |This bit indicates if the RTC_SPR0 ~RTC_SPR19 content is cleared when specify tamper event is detected.
     * |        |          |0 = Spare register content is not cleared.
     * |        |          |1 = Spare register content is cleared.
     * |        |          |Note 1: Write 1 to clear this bit.
     * |        |          |Note 2: This bit keeps 1 when RTC_INTSTS[13:8] is not equal to 0.
     * |[16]    |LXTFCLR   |LXT Clock Fail/Stop to Clear Spare Enable Bit
     * |        |          |0 = LXT Fail/Stop to clear Spare register content is Disabled..
     * |        |          |1 = LXT Fail/Stop to clear Spare register content is Enabled.
     * @var RTC_T::SPR0
     * Offset: 0x40  RTC Spare Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR1
     * Offset: 0x44  RTC Spare Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR2
     * Offset: 0x48  RTC Spare Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR3
     * Offset: 0x4C  RTC Spare Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR4
     * Offset: 0x50  RTC Spare Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR5
     * Offset: 0x54  RTC Spare Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR6
     * Offset: 0x58  RTC Spare Register 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR7
     * Offset: 0x5C  RTC Spare Register 7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR8
     * Offset: 0x60  RTC Spare Register 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR9
     * Offset: 0x64  RTC Spare Register 9
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR10
     * Offset: 0x68  RTC Spare Register 10
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR11
     * Offset: 0x6C  RTC Spare Register 11
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR12
     * Offset: 0x70  RTC Spare Register 12
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR13
     * Offset: 0x74  RTC Spare Register 13
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR14
     * Offset: 0x78  RTC Spare Register 14
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::SPR15
     * Offset: 0x7C  RTC Spare Register 15
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:0]  |SPARE     |Spare Register
     * |        |          |This field is used to store back-up information defined by user.
     * |        |          |This field will be cleared by hardware automatically in the following conditions, a tamper pin event is detected, LXT clock fail/stop event occurs if LXTFCLR(RTC_SPRCTL[16]) is 1, or after Flash mass operation.
     * @var RTC_T::TALM_M
     * Offset: 0x9C  RTC Time Alarm Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |SECM      |1-Sec Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[6:4]   |TENSECM   |10-Sec Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~5
     * |[11:8]  |MINM      |1-Min Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[14:12] |TENMINM   |10-Min Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~5
     * |[19:16] |HRM       |1-Hour Time Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[21:20] |TENHRM    |10-Hour Time Digit of Alarm Setting
     * |        |          |When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication (If RTC_TIME[21] is 1, it indicates PM time message.)
     * |        |          |Note: The reasonable value range is 0~2
     * @var RTC_T::CALM_M
     * Offset: 0xA0  RTC Calendar Alarm Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAYM      |1-Day Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[5:4]   |TENDAYM   |10-Day Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~3
     * |[11:8]  |MONM      |1-Month Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[12]    |TENMONM   |10-Month Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~1
     * |[19:16] |YEARM     |1-Year Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * |[23:20] |TENYEARM  |10-Year Calendar Digit of Alarm Setting
     * |        |          |Note: The reasonable value range is 0~9
     * @var RTC_T::INTEN_M
     * Offset: 0xA8  RTC Interrupt Enable Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ALMIENM   |Alarm Interrupt Enable Bit
     * |        |          |Setting ALMIEN to 1 can also enable chip wake-up function when RTC alarm interrupt event is generated.
     * |        |          |0 = RTC Alarm interrupt Disabled.
     * |        |          |1 = RTC Alarm interrupt Enabled.
     * |[1]     |TICKIENM  |Time Tick Interrupt Enable Bit
     * |        |          |Setting TICKIEN to 1 can also enable chip wake-up function when RTC tick interrupt event is generated.
     * |        |          |0 = RTC Time Tick interrupt Disabled.
     * |        |          |1 = RTC Time Tick interrupt Enabled.
     * @var RTC_T::INTSTS_M
     * Offset: 0xAC  RTC Interrupt Status Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |ALMIFM    |RTC Alarm Interrupt Flag
     * |        |          |0 = Alarm condition is not matched.
     * |        |          |1 = Alarm condition is matched.
     * |        |          |Note: Write 1 to clear this bit.
     * |[1]     |TICKIFM   |RTC Time Tick Interrupt Flag
     * |        |          |0 = Tick condition did not occur.
     * |        |          |1 = Tick condition occurred.
     * |        |          |Note: Write 1 to clear this bit.
     * @var RTC_T::TICK_M
     * Offset: 0xB0  RTC Time Tick Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[2:0]   |TICKM     |Time Tick Register
     * |        |          |These bits are used to select RTC time tick period for Periodic Time Tick Interrupt request.
     * |        |          |000 = Time tick is 1 second.
     * |        |          |001 = Time tick is 1/2 second.
     * |        |          |010 = Time tick is 1/4 second.
     * |        |          |011 = Time tick is 1/8 second.
     * |        |          |100 = Time tick is 1/16 second.
     * |        |          |101 = Time tick is 1/32 second.
     * |        |          |110 = Time tick is 1/64 second.
     * |        |          |111 = Time tick is 1/128 second.
     * @var RTC_T::TAMSK_M
     * Offset: 0xB4  RTC Time Alarm Mask Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MSECM     |Mask 1-Sec Time Digit of Alarm Setting
     * |[1]     |MTENSECM  |Mask 10-Sec Time Digit of Alarm Setting
     * |[2]     |MMINM     |Mask 1-Min Time Digit of Alarm Setting
     * |[3]     |MTENMINM  |Mask 10-Min Time Digit of Alarm Setting
     * |[4]     |MHRM      |Mask 1-Hour Time Digit of Alarm Setting
     * |[5]     |MTENHRM   |Mask 10-Hour Time Digit of Alarm Setting
     * @var RTC_T::CAMSK_M
     * Offset: 0xB8  RTC Calendar Alarm Mask Register for SubM (SubM)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |MDAYM     |Mask 1-Day Calendar Digit of Alarm Setting
     * |[1]     |MTENDAYM  |Mask 10-Day Calendar Digit of Alarm Setting
     * |[2]     |MMONM     |Mask 1-Month Calendar Digit of Alarm Setting
     * |[3]     |MTENMONM  |Mask 10-Month Calendar Digit of Alarm Setting
     * |[4]     |MYEARM    |Mask 1-Year Calendar Digit of Alarm Setting
     * |[5]     |MTENYEARM |Mask 10-Year Calendar Digit of Alarm Setting
     * @var RTC_T::LXTCTL
     * Offset: 0x100  RTC 32.768 kHz Oscillator Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[6]     |C32KSEL   |Clock 32K Source Selection
     * |        |          |0 = Clock source from external low speed crystal oscillator (LXT).
     * |        |          |1 = Clock source from internal low speed RC 32K oscillator (LIRC32K).
     * |[8]     |IOCTLSEL  |IO Pin Backup Control Selection
     * |        |          |When TAMPxEN or 32KOUTEN is disabled, PH.8 pin and PH.9 pin(TAMPERx pin) can be used as GPIO function
     * |        |          |User can program IOCTLSEL to decide PH.8~9 I/O function is controlled by system power domain GPIO module or VBAT power domain RTC_GPIOCTL0 control register.
     * |        |          |0 = PH.8~9 pin I/O function is controlled by GPIO module.
     * |        |          |1 = PH.8~9 pin I/O function is controlled by VBAT power domain.
     * |        |          |Note: IOCTLSEL will automatically be set by hardware to 1 when system power is off and any writable RTC registers has been written at RTCCKEN(CLK_APBCLK0[29]) enabled.
     * |[16]    |32KOUTEN  |Clock 32 kHz Output Enable Bit
     * |        |          |When TAMP1EN is disabled, PH.9 pin(TAMPERx pin) can be used as clock 32 kHz output.
     * |        |          |0 = Clock 32 kHz output to PH.9 pin Disabled.
     * |        |          |1 = Clock 32 kHz output to PH.9 pin Enabled.
     * @var RTC_T::GPIOCTL0
     * Offset: 0x104  RTC GPIO Control 0 Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |OPMODE0   |IO Operation Mode
     * |        |          |00 = PH.8 is input only mode.
     * |        |          |01 = PH.8 is output push pull mode.
     * |        |          |10 = PH.8 is open drain mode.
     * |        |          |11 = PH.8 is quasi-bidirectional mode.
     * |[2]     |DOUT0     |IO Output Data
     * |        |          |0 = PH.8 output low.
     * |        |          |1 = PH.8 output high.
     * |[3]     |DINOFF0   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PH.8 digital input path Enabled.
     * |        |          |1 = PH.8 digital input path Disabled (digital input tied to low).
     * |[5:4]   |PUSEL0    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PH.8 I/O pull-up or pull-down.
     * |        |          |00 = PH.8 pull-up and pull-down Disabled.
     * |        |          |01 = PH.8 pull-up Enabled.
     * |        |          |10 = PH.8 pull-down Enabled.
     * |        |          |11 = PH.8 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up / pull-down control register only valid when OPMODE0 set as input tri-state and open-drain mode.
     * |[6]     |SMTEN0    |Input Schmitt Trigger Enable Bit
     * |        |          |0 = PH.8 input schmitt trigger function Disabled.
     * |        |          |1 = PH.8 input schmitt trigger function Enabled.
     * |[9:8]   |OPMODE1   |IO Operation Mode
     * |        |          |00 = PH.9 is input only mode.
     * |        |          |01 = PH.9 is output push pull mode.
     * |        |          |10 = PH.9 is open drain mode.
     * |        |          |11 = PH.9 is quasi-bidirectional mode.
     * |[10]    |DOUT1     |IO Output Data
     * |        |          |0 = PH.9 output low.
     * |        |          |1 = PH.9 output high.
     * |[11]    |DINOFF1   |IO Pin Digital Input Path Disable Bit
     * |        |          |0 = PH.9 digital input path Enabled.
     * |        |          |1 = PH.9 digital input path Disabled (digital input tied to low).
     * |[13:12] |PUSEL1    |IO Pull-up and Pull-down Enable Bits
     * |        |          |Determine PH.9 I/O pull-up or pull-down.
     * |        |          |00 = PH.9 pull-up and pull-down Disabled.
     * |        |          |01 = PH.9 pull-up Enabled.
     * |        |          |10 = PH.9 pull-down Enabled.
     * |        |          |11 = PH.9 pull-up and pull-down Disabled.
     * |        |          |Note: Basically, the pull-up control and pull-down control has following behavior limitation.
     * |        |          |The independent pull-up / pull-down control register only valid when OPMODE1 set as input tri-state and open-drain mode.
     * |[14]    |SMTEN1    |Input Schmitt Trigger Enable Bit
     * |        |          |0 = PH.9 input schmitt trigger function Disabled.
     * |        |          |1 = PH.9 input schmitt trigger function Enabled.
     * @var RTC_T::TAMPCTL
     * Offset: 0x120  RTC Tamper Pin Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3]     |DYNSRC    |Dynamic Reference Pattern
     * |        |          |This fields determine the new reference pattern when the current pattern runs out in dynamic pair mode.
     * |        |          |0 = The new reference pattern is generated by random number generator when the reference pattern run out.
     * |        |          |1 = The new reference pattern is repeated from SEED (RTC_TAMPSEED[31:0]) when the reference pattern run out.
     * |        |          |Note: After this bit is modified, the SEEDRLD (RTC_TAMPCTL[4]) should be set.
     * |[4]     |SEEDRLD   |Reload New Seed for PRNG Engine
     * |        |          |Setting this bit, the tamper configuration will be reloaded.
     * |        |          |0 = Generating key based on the current seed.
     * |        |          |1 = Reload new seed.
     * |        |          |Note 1: Before this bit is set, the tamper configuration should be set to complete and this bit will be auto clear to 0 after reload new seed completed.
     * |        |          |Note 2: The reference is RTC-clock. Tamper detector need sync 2 ~ 3 RTC-clock.
     * |[7:5]   |DYNRATE   |Dynamic Change Rate
     * |        |          |This item is choice the dynamic tamper output change rate.
     * |        |          |000 = 210 * RTC_CLK.
     * |        |          |001 = 211 * RTC_CLK.
     * |        |          |010 = 212 * RTC_CLK.
     * |        |          |011 = 213 * RTC_CLK.
     * |        |          |100 = 214 * RTC_CLK.
     * |        |          |101 = 215 * RTC_CLK.
     * |        |          |110 = 216 * RTC_CLK.
     * |        |          |111 = 217 * RTC_CLK.
     * |        |          |Note: After revising this field, set SEEDRLD (RTC_TAMPCTL[4]) can reload change rate immediately.
     * |[8]     |TAMP0EN   |Tamper0 Detect Enable Bit
     * |        |          |0 = Tamper 0 detect Disabled.
     * |        |          |1 = Tamper 0 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector need sync 2 ~ 3 RTC-clock.
     * |[9]     |TAMP0LV   |Tamper 0 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[10]    |TAMP0DEN  |Tamper 0 De-bounce Enable Bit
     * |        |          |0 = Tamper 0 de-bounce Disabled.
     * |        |          |1 = Tamper 0 de-bounce Enabled, tamper detection pin will sync 1 RTC clock.
     * |[12]    |TAMP1EN   |Tamper 1 Detect Enable Bit
     * |        |          |0 = Tamper 1 detect Disabled.
     * |        |          |1 = Tamper 1 detect Enabled.
     * |        |          |Note: The reference is RTC-clock. Tamper detector need sync 2 ~ 3 RTC-clock.
     * |[13]    |TAMP1LV   |Tamper 1 Level
     * |        |          |This bit depends on level attribute of tamper pin for static tamper detection.
     * |        |          |0 = Detect voltage level is low.
     * |        |          |1 = Detect voltage level is high.
     * |[14]    |TAMP1DEN  |Tamper 1 De-bounce Enable Bit
     * |        |          |0 = Tamper 1 de-bounce Disabled.
     * |        |          |1 = Tamper 1 de-bounce Enabled, tamper detection pin will sync 1 RTC clock.
     * |[15]    |DYNPR0EN  |Dynamic Pair 0 Enable Bit
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
     * |[3:0]   |SEC       |1-Sec Time Digit of TAMPER Time
     * |        |          |Note: The reasonable value range is 0~9
     * |[6:4]   |TENSEC    |10-Sec Time Digit of TAMPER Time
     * |        |          |Note: The reasonable value range is 0~5
     * |[11:8]  |MIN       |1-Min Time Digit of TAMPER Time
     * |        |          |Note: The reasonable value range is 0~9
     * |[14:12] |TENMIN    |10-Min Time Digit of TAMPER Time
     * |        |          |Note: The reasonable value range is 0~5
     * |[19:16] |HR        |1-Hour Time Digit of TAMPER Time
     * |        |          |Note: The reasonable value range is 0~9
     * |[21:20] |TENHR     |10-Hour Time Digit of TAMPER Time
     * |        |          |Note 1: The reasonable value range is 0~2
     * |        |          |Note 2: 24-hour time scale only.
     * @var RTC_T::TAMPCAL
     * Offset: 0x134  RTC Tamper Calendar Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |DAY       |1-Day Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~9
     * |[5:4]   |TENDAY    |10-Day Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~3
     * |[11:8]  |MON       |1-Month Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~9
     * |[12]    |TENMON    |10-Month Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~1
     * |[19:16] |YEAR      |1-Year Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~9
     * |[23:20] |TENYEAR   |10-Year Calendar Digit of TAMPER Calendar
     * |        |          |Note: The reasonable value range is 0~9
     * @var RTC_T::CLKDCTL
     * Offset: 0x140  Clock Fail Detector Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |LXTFDEN   |LXT Clock Fail/Stop Detector Enable Bit
     * |        |          |0 = LXT clock Fail/Stop detector Disabled.
     * |        |          |1 = LXT clock Fail/Stop detector Enabled.
     * |[1]     |LXTFSW    |LXT Clock Fail Detector Switch LIRC32K Enable Bit
     * |        |          |0 = LXT clock Fail switch LIRC32K Disabled.
     * |        |          |1 = LXT clock Fail detector rise, RTC clock source switched from LIRC32K.
     * |[2]     |LXTSTSW   |LXT Clock Stop Detector Switch LIRC32K Enable Bit
     * |        |          |0 = LXT clock Stop switch LIRC32K Disabled.
     * |        |          |1 = LXT clock Stop detector rise, RTC clock source switched from LIRC32K.
     * |[16]    |SWLIRCF   |LXT Clock Detector Fail/Stop Switch LIRC32K Flag (Read Only)
     * |        |          |0 = Indicate RTC clock source from LXT.
     * |        |          |1 = Indicate RTC clock source from LIRC32K.
     * |[17]    |LXTSLOWF  |LXT Slower Than LIRC32K Flag (Read Only)
     * |        |          |0 = LXT frequency faster than LIRC32K.
     * |        |          |1 = LXT frequency is slowly.
     * |        |          |Note: LXTSLOWF is vaild during CLKSTIF (RTC_INTSTS[25]) or CLKFIF (RTC_INTSTS[24]) rising.
     * @var RTC_T::CDBR
     * Offset: 0x144  Clock Frequency Detector Boundary Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |STOPBD    |LXT Clock Stop Frequency Detector Stop Boundary
     * |        |          |The bits define the stop value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than STOPBD, the LXT frequency detect Stop interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the maximun value of LXT among 256 LIRC32K clock time.
     * |[23:16] |FAILBD    |LXT Clock Frequency Detector Fail Boundary
     * |        |          |The bits define the fail value of frequency monitor window.
     * |        |          |When LXT frequency monitor counter lower than FAILBD, the LXT frequency detect fail interrupt flag will set to 1.
     * |        |          |Note: The boundary is defined as the minimun value of LXT among 256 LIRC32K clock time.
     * @var RTC_T::PWRCTL
     * Offset: 0x180  RTC Power Control Register (TZS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * @var RTC_T::PWRSTS
     * Offset: 0x184  RTC Power Control Status Register (TZS)
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[22:8]  |PWRONCNT  |Power On Counter Current Value (Read Only)
     * |        |          |This field shows the current value of power on counter.
     * |        |          |This field is read only and write to this field will not take any effect.
     * |[26:24] |PWROFFCNT |Power Off Counter Current Value (Read Only)
     * |        |          |This field shows the current value of power off counter.
     * |        |          |This field is read only and write to this field will not take any effect.
     */
    __IO uint32_t INIT;                  /*!< [0x0000] RTC Initiation Register                                          */
    __I  uint32_t SINFASTS;              /*!< [0x0004] RTC Shared Information Accessable Status Register                */
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
    __IO uint32_t SPR0;                  /*!< [0x0040] RTC Spare Register 0                                             */
    __IO uint32_t SPR1;                  /*!< [0x0044] RTC Spare Register 1                                             */
    __IO uint32_t SPR2;                  /*!< [0x0048] RTC Spare Register 2                                             */
    __IO uint32_t SPR3;                  /*!< [0x004c] RTC Spare Register 3                                             */
    __IO uint32_t SPR4;                  /*!< [0x0050] RTC Spare Register 4                                             */
    __IO uint32_t SPR5;                  /*!< [0x0054] RTC Spare Register 5                                             */
    __IO uint32_t SPR6;                  /*!< [0x0058] RTC Spare Register 6                                             */
    __IO uint32_t SPR7;                  /*!< [0x005c] RTC Spare Register 7                                             */
    __IO uint32_t SPR8;                  /*!< [0x0060] RTC Spare Register 8                                             */
    __IO uint32_t SPR9;                  /*!< [0x0064] RTC Spare Register 9                                             */
    __IO uint32_t SPR10;                 /*!< [0x0068] RTC Spare Register 10                                            */
    __IO uint32_t SPR11;                 /*!< [0x006c] RTC Spare Register 11                                            */
    __IO uint32_t SPR12;                 /*!< [0x0070] RTC Spare Register 12                                            */
    __IO uint32_t SPR13;                 /*!< [0x0074] RTC Spare Register 13                                            */
    __IO uint32_t SPR14;                 /*!< [0x0078] RTC Spare Register 14                                            */
    __IO uint32_t SPR15;                 /*!< [0x007c] RTC Spare Register 15                                            */
    __I  uint32_t RESERVE0[7];
    __IO uint32_t TALM_M;                /*!< [0x009c] RTC Time Alarm Register for SubM (SubM)                          */
    __IO uint32_t CALM_M;                /*!< [0x00a0] RTC Calendar Alarm Register for SubM (SubM)                      */
    __I  uint32_t RESERVE1[1];
    __IO uint32_t INTEN_M;               /*!< [0x00a8] RTC Interrupt Enable Register for SubM (SubM)                    */
    __IO uint32_t INTSTS_M;              /*!< [0x00ac] RTC Interrupt Status Register for SubM (SubM)                    */
    __IO uint32_t TICK_M;                /*!< [0x00b0] RTC Time Tick Register for SubM (SubM)                           */
    __IO uint32_t TAMSK_M;               /*!< [0x00b4] RTC Time Alarm Mask Register for SubM (SubM)                     */
    __IO uint32_t CAMSK_M;               /*!< [0x00b8] RTC Calendar Alarm Mask Register for SubM (SubM)                 */
    __I  uint32_t RESERVE2[17];
    __IO uint32_t LXTCTL;                /*!< [0x0100] RTC 32.768 kHz Oscillator Control Register                       */
    __IO uint32_t GPIOCTL0;              /*!< [0x0104] RTC GPIO Control 0 Register                                      */
    __I  uint32_t RESERVE3[6];
    __IO uint32_t TAMPCTL;               /*!< [0x0120] RTC Tamper Pin Control Register                                  */
    __I  uint32_t RESERVE4[1];
    __IO uint32_t TAMPSEED;              /*!< [0x0128] RTC Tamper Dynamic Seed Register                                 */
    __I  uint32_t RESERVE5[1];
    __I  uint32_t TAMPTIME;              /*!< [0x0130] RTC Tamper Time Register                                         */
    __I  uint32_t TAMPCAL;               /*!< [0x0134] RTC Tamper Calendar Register                                     */
    __I  uint32_t RESERVE6[2];
    __IO uint32_t CLKDCTL;               /*!< [0x0140] Clock Fail Detector Control Register                             */
    __IO uint32_t CDBR;                  /*!< [0x0144] Clock Frequency Detector Boundary Register                       */
    __I  uint32_t RESERVE7[14];
    __IO uint32_t PWRCTL;                /*!< [0x0180] RTC Power Control Register (TZS)                                 */
    __I  uint32_t PWRSTS;                /*!< [0x0184] RTC Power Control Status Register (TZS)                          */

} RTC_T;

/**
    @addtogroup RTC_CONST RTC Bit Field Definition
    Constant Definitions for RTC Controller
@{ */

#define RTC_INIT_ACTIVE_Pos              (0)                                               /*!< RTC_T::INIT: ACTIVE Position           */
#define RTC_INIT_ACTIVE_Msk              (0x1ul << RTC_INIT_ACTIVE_Pos)                    /*!< RTC_T::INIT: ACTIVE Mask               */

#define RTC_INIT_INIT_Pos                (1)                                               /*!< RTC_T::INIT: INIT Position             */
#define RTC_INIT_INIT_Msk                (0x7ffffffful << RTC_INIT_INIT_Pos)               /*!< RTC_T::INIT: INIT Mask                 */

#define RTC_SINFASTS_SINFASTS_Pos        (0)                                               /*!< RTC_T::SINFASTS: SINFASTS Position     */
#define RTC_SINFASTS_SINFASTS_Msk        (0x1ul << RTC_SINFASTS_SINFASTS_Pos)              /*!< RTC_T::SINFASTS: SINFASTS Mask         */

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

#define RTC_INTEN_PSWIEN_Pos             (2)                                               /*!< RTC_T::INTEN: PSWIEN Position          */
#define RTC_INTEN_PSWIEN_Msk             (0x1ul << RTC_INTEN_PSWIEN_Pos)                   /*!< RTC_T::INTEN: PSWIEN Mask              */

#define RTC_INTEN_KPRSIEN_Pos            (3)                                               /*!< RTC_T::INTEN: KPRSIEN Position         */
#define RTC_INTEN_KPRSIEN_Msk            (0x1ul << RTC_INTEN_KPRSIEN_Pos)                  /*!< RTC_T::INTEN: KPRSIEN Mask             */

#define RTC_INTEN_TAMP0IEN_Pos           (8)                                               /*!< RTC_T::INTEN: TAMP0IEN Position        */
#define RTC_INTEN_TAMP0IEN_Msk           (0x1ul << RTC_INTEN_TAMP0IEN_Pos)                 /*!< RTC_T::INTEN: TAMP0IEN Mask            */

#define RTC_INTEN_TAMP1IEN_Pos           (9)                                               /*!< RTC_T::INTEN: TAMP1IEN Position        */
#define RTC_INTEN_TAMP1IEN_Msk           (0x1ul << RTC_INTEN_TAMP1IEN_Pos)                 /*!< RTC_T::INTEN: TAMP1IEN Mask            */

#define RTC_INTEN_TAMPIENSubM_Pos        (16)                                              /*!< RTC_T::INTEN: TAMPIENSubM Position     */
#define RTC_INTEN_TAMPIENSubM_Msk        (0x1ul << RTC_INTEN_TAMPIENSubM_Pos)              /*!< RTC_T::INTEN: TAMPIENSubM Mask         */

#define RTC_INTEN_CLKFIEN_Pos            (24)                                              /*!< RTC_T::INTEN: CLKFIEN Position         */
#define RTC_INTEN_CLKFIEN_Msk            (0x1ul << RTC_INTEN_CLKFIEN_Pos)                  /*!< RTC_T::INTEN: CLKFIEN Mask             */

#define RTC_INTEN_CLKSTIEN_Pos           (25)                                              /*!< RTC_T::INTEN: CLKSTIEN Position        */
#define RTC_INTEN_CLKSTIEN_Msk           (0x1ul << RTC_INTEN_CLKSTIEN_Pos)                 /*!< RTC_T::INTEN: CLKSTIEN Mask            */

#define RTC_INTSTS_ALMIF_Pos             (0)                                               /*!< RTC_T::INTSTS: ALMIF Position          */
#define RTC_INTSTS_ALMIF_Msk             (0x1ul << RTC_INTSTS_ALMIF_Pos)                   /*!< RTC_T::INTSTS: ALMIF Mask              */

#define RTC_INTSTS_TICKIF_Pos            (1)                                               /*!< RTC_T::INTSTS: TICKIF Position         */
#define RTC_INTSTS_TICKIF_Msk            (0x1ul << RTC_INTSTS_TICKIF_Pos)                  /*!< RTC_T::INTSTS: TICKIF Mask             */

#define RTC_INTSTS_PSWST_Pos             (2)                                               /*!< RTC_T::INTSTS: PSWST Position          */
#define RTC_INTSTS_PSWST_Msk             (0x1ul << RTC_INTSTS_PSWST_Pos)                   /*!< RTC_T::INTSTS: PSWST Mask              */

#define RTC_INTSTS_KPRSST_Pos            (3)                                               /*!< RTC_T::INTSTS: KPRSST Position         */
#define RTC_INTSTS_KPRSST_Msk            (0x1ul << RTC_INTSTS_KPRSST_Pos)                  /*!< RTC_T::INTSTS: KPRSST Mask             */

#define RTC_INTSTS_TAMP0IF_Pos           (8)                                               /*!< RTC_T::INTSTS: TAMP0IF Position        */
#define RTC_INTSTS_TAMP0IF_Msk           (0x1ul << RTC_INTSTS_TAMP0IF_Pos)                 /*!< RTC_T::INTSTS: TAMP0IF Mask            */

#define RTC_INTSTS_TAMP1IF_Pos           (9)                                               /*!< RTC_T::INTSTS: TAMP1IF Position        */
#define RTC_INTSTS_TAMP1IF_Msk           (0x1ul << RTC_INTSTS_TAMP1IF_Pos)                 /*!< RTC_T::INTSTS: TAMP1IF Mask            */

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

#define RTC_TALM_M_SECM_Pos              (0)                                               /*!< RTC_T::TALM_M: SECM Position           */
#define RTC_TALM_M_SECM_Msk              (0xful << RTC_TALM_M_SECM_Pos)                    /*!< RTC_T::TALM_M: SECM Mask               */

#define RTC_TALM_M_TENSECM_Pos           (4)                                               /*!< RTC_T::TALM_M: TENSECM Position        */
#define RTC_TALM_M_TENSECM_Msk           (0x7ul << RTC_TALM_M_TENSECM_Pos)                 /*!< RTC_T::TALM_M: TENSECM Mask            */

#define RTC_TALM_M_MINM_Pos              (8)                                               /*!< RTC_T::TALM_M: MINM Position           */
#define RTC_TALM_M_MINM_Msk              (0xful << RTC_TALM_M_MINM_Pos)                    /*!< RTC_T::TALM_M: MINM Mask               */

#define RTC_TALM_M_TENMINM_Pos           (12)                                              /*!< RTC_T::TALM_M: TENMINM Position        */
#define RTC_TALM_M_TENMINM_Msk           (0x7ul << RTC_TALM_M_TENMINM_Pos)                 /*!< RTC_T::TALM_M: TENMINM Mask            */

#define RTC_TALM_M_HRM_Pos               (16)                                              /*!< RTC_T::TALM_M: HRM Position            */
#define RTC_TALM_M_HRM_Msk               (0xful << RTC_TALM_M_HRM_Pos)                     /*!< RTC_T::TALM_M: HRM Mask                */

#define RTC_TALM_M_TENHRM_Pos            (20)                                              /*!< RTC_T::TALM_M: TENHRM Position         */
#define RTC_TALM_M_TENHRM_Msk            (0x3ul << RTC_TALM_M_TENHRM_Pos)                  /*!< RTC_T::TALM_M: TENHRM Mask             */

#define RTC_CALM_M_DAYM_Pos              (0)                                               /*!< RTC_T::CALM_M: DAYM Position           */
#define RTC_CALM_M_DAYM_Msk              (0xful << RTC_CALM_M_DAYM_Pos)                    /*!< RTC_T::CALM_M: DAYM Mask               */

#define RTC_CALM_M_TENDAYM_Pos           (4)                                               /*!< RTC_T::CALM_M: TENDAYM Position        */
#define RTC_CALM_M_TENDAYM_Msk           (0x3ul << RTC_CALM_M_TENDAYM_Pos)                 /*!< RTC_T::CALM_M: TENDAYM Mask            */

#define RTC_CALM_M_MONM_Pos              (8)                                               /*!< RTC_T::CALM_M: MONM Position           */
#define RTC_CALM_M_MONM_Msk              (0xful << RTC_CALM_M_MONM_Pos)                    /*!< RTC_T::CALM_M: MONM Mask               */

#define RTC_CALM_M_TENMONM_Pos           (12)                                              /*!< RTC_T::CALM_M: TENMONM Position        */
#define RTC_CALM_M_TENMONM_Msk           (0x1ul << RTC_CALM_M_TENMONM_Pos)                 /*!< RTC_T::CALM_M: TENMONM Mask            */

#define RTC_CALM_M_YEARM_Pos             (16)                                              /*!< RTC_T::CALM_M: YEARM Position          */
#define RTC_CALM_M_YEARM_Msk             (0xful << RTC_CALM_M_YEARM_Pos)                   /*!< RTC_T::CALM_M: YEARM Mask              */

#define RTC_CALM_M_TENYEARM_Pos          (20)                                              /*!< RTC_T::CALM_M: TENYEARM Position       */
#define RTC_CALM_M_TENYEARM_Msk          (0xful << RTC_CALM_M_TENYEARM_Pos)                /*!< RTC_T::CALM_M: TENYEARM Mask           */

#define RTC_INTEN_M_ALMIENM_Pos          (0)                                               /*!< RTC_T::INTEN_M: ALMIENM Position       */
#define RTC_INTEN_M_ALMIENM_Msk          (0x1ul << RTC_INTEN_M_ALMIENM_Pos)                /*!< RTC_T::INTEN_M: ALMIENM Mask           */

#define RTC_INTEN_M_TICKIENM_Pos         (1)                                               /*!< RTC_T::INTEN_M: TICKIENM Position      */
#define RTC_INTEN_M_TICKIENM_Msk         (0x1ul << RTC_INTEN_M_TICKIENM_Pos)               /*!< RTC_T::INTEN_M: TICKIENM Mask          */

#define RTC_INTSTS_M_ALMIFM_Pos          (0)                                               /*!< RTC_T::INTSTS_M: ALMIFM Position       */
#define RTC_INTSTS_M_ALMIFM_Msk          (0x1ul << RTC_INTSTS_M_ALMIFM_Pos)                /*!< RTC_T::INTSTS_M: ALMIFM Mask           */

#define RTC_INTSTS_M_TICKIFM_Pos         (1)                                               /*!< RTC_T::INTSTS_M: TICKIFM Position      */
#define RTC_INTSTS_M_TICKIFM_Msk         (0x1ul << RTC_INTSTS_M_TICKIFM_Pos)               /*!< RTC_T::INTSTS_M: TICKIFM Mask          */

#define RTC_TICK_M_TICKM_Pos             (0)                                               /*!< RTC_T::TICK_M: TICKM Position          */
#define RTC_TICK_M_TICKM_Msk             (0x7ul << RTC_TICK_M_TICKM_Pos)                   /*!< RTC_T::TICK_M: TICKM Mask              */

#define RTC_TAMSK_M_MSECM_Pos            (0)                                               /*!< RTC_T::TAMSK_M: MSECM Position         */
#define RTC_TAMSK_M_MSECM_Msk            (0x1ul << RTC_TAMSK_M_MSECM_Pos)                  /*!< RTC_T::TAMSK_M: MSECM Mask             */

#define RTC_TAMSK_M_MTENSECM_Pos         (1)                                               /*!< RTC_T::TAMSK_M: MTENSECM Position      */
#define RTC_TAMSK_M_MTENSECM_Msk         (0x1ul << RTC_TAMSK_M_MTENSECM_Pos)               /*!< RTC_T::TAMSK_M: MTENSECM Mask          */

#define RTC_TAMSK_M_MMINM_Pos            (2)                                               /*!< RTC_T::TAMSK_M: MMINM Position         */
#define RTC_TAMSK_M_MMINM_Msk            (0x1ul << RTC_TAMSK_M_MMINM_Pos)                  /*!< RTC_T::TAMSK_M: MMINM Mask             */

#define RTC_TAMSK_M_MTENMINM_Pos         (3)                                               /*!< RTC_T::TAMSK_M: MTENMINM Position      */
#define RTC_TAMSK_M_MTENMINM_Msk         (0x1ul << RTC_TAMSK_M_MTENMINM_Pos)               /*!< RTC_T::TAMSK_M: MTENMINM Mask          */

#define RTC_TAMSK_M_MHRM_Pos             (4)                                               /*!< RTC_T::TAMSK_M: MHRM Position          */
#define RTC_TAMSK_M_MHRM_Msk             (0x1ul << RTC_TAMSK_M_MHRM_Pos)                   /*!< RTC_T::TAMSK_M: MHRM Mask              */

#define RTC_TAMSK_M_MTENHRM_Pos          (5)                                               /*!< RTC_T::TAMSK_M: MTENHRM Position       */
#define RTC_TAMSK_M_MTENHRM_Msk          (0x1ul << RTC_TAMSK_M_MTENHRM_Pos)                /*!< RTC_T::TAMSK_M: MTENHRM Mask           */

#define RTC_CAMSK_M_MDAYM_Pos            (0)                                               /*!< RTC_T::CAMSK_M: MDAYM Position         */
#define RTC_CAMSK_M_MDAYM_Msk            (0x1ul << RTC_CAMSK_M_MDAYM_Pos)                  /*!< RTC_T::CAMSK_M: MDAYM Mask             */

#define RTC_CAMSK_M_MTENDAYM_Pos         (1)                                               /*!< RTC_T::CAMSK_M: MTENDAYM Position      */
#define RTC_CAMSK_M_MTENDAYM_Msk         (0x1ul << RTC_CAMSK_M_MTENDAYM_Pos)               /*!< RTC_T::CAMSK_M: MTENDAYM Mask          */

#define RTC_CAMSK_M_MMONM_Pos            (2)                                               /*!< RTC_T::CAMSK_M: MMONM Position         */
#define RTC_CAMSK_M_MMONM_Msk            (0x1ul << RTC_CAMSK_M_MMONM_Pos)                  /*!< RTC_T::CAMSK_M: MMONM Mask             */

#define RTC_CAMSK_M_MTENMONM_Pos         (3)                                               /*!< RTC_T::CAMSK_M: MTENMONM Position      */
#define RTC_CAMSK_M_MTENMONM_Msk         (0x1ul << RTC_CAMSK_M_MTENMONM_Pos)               /*!< RTC_T::CAMSK_M: MTENMONM Mask          */

#define RTC_CAMSK_M_MYEARM_Pos           (4)                                               /*!< RTC_T::CAMSK_M: MYEARM Position        */
#define RTC_CAMSK_M_MYEARM_Msk           (0x1ul << RTC_CAMSK_M_MYEARM_Pos)                 /*!< RTC_T::CAMSK_M: MYEARM Mask            */

#define RTC_CAMSK_M_MTENYEARM_Pos        (5)                                               /*!< RTC_T::CAMSK_M: MTENYEARM Position     */
#define RTC_CAMSK_M_MTENYEARM_Msk        (0x1ul << RTC_CAMSK_M_MTENYEARM_Pos)              /*!< RTC_T::CAMSK_M: MTENYEARM Mask         */

#define RTC_LXTCTL_C32KSEL_Pos           (6)                                               /*!< RTC_T::LXTCTL: C32KSEL Position        */
#define RTC_LXTCTL_C32KSEL_Msk           (0x1ul << RTC_LXTCTL_C32KSEL_Pos)                 /*!< RTC_T::LXTCTL: C32KSEL Mask            */

#define RTC_LXTCTL_IOCTLSEL_Pos          (8)                                               /*!< RTC_T::LXTCTL: IOCTLSEL Position       */
#define RTC_LXTCTL_IOCTLSEL_Msk          (0x1ul << RTC_LXTCTL_IOCTLSEL_Pos)                /*!< RTC_T::LXTCTL: IOCTLSEL Mask           */

#define RTC_LXTCTL_32KOUTEN_Pos          (16)                                              /*!< RTC_T::LXTCTL: 32KOUTEN Position       */
#define RTC_LXTCTL_32KOUTEN_Msk          (0x1ul << RTC_LXTCTL_32KOUTEN_Pos)                /*!< RTC_T::LXTCTL: 32KOUTEN Mask           */

#define RTC_GPIOCTL0_OPMODE0_Pos         (0)                                               /*!< RTC_T::GPIOCTL0: OPMODE0 Position      */
#define RTC_GPIOCTL0_OPMODE0_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE0_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE0 Mask          */

#define RTC_GPIOCTL0_DOUT0_Pos           (2)                                               /*!< RTC_T::GPIOCTL0: DOUT0 Position        */
#define RTC_GPIOCTL0_DOUT0_Msk           (0x1ul << RTC_GPIOCTL0_DOUT0_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT0 Mask            */

#define RTC_GPIOCTL0_DINOFF0_Pos         (3)                                               /*!< RTC_T::GPIOCTL0: DINOFF0 Position      */
#define RTC_GPIOCTL0_DINOFF0_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF0_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF0 Mask          */

#define RTC_GPIOCTL0_PUSEL0_Pos          (4)                                               /*!< RTC_T::GPIOCTL0: PUSEL0 Position       */
#define RTC_GPIOCTL0_PUSEL0_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL0_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL0 Mask           */

#define RTC_GPIOCTL0_SMTEN0_Pos          (6)                                               /*!< RTC_T::GPIOCTL0: SMTEN0 Position       */
#define RTC_GPIOCTL0_SMTEN0_Msk          (0x1ul << RTC_GPIOCTL0_SMTEN0_Pos)                /*!< RTC_T::GPIOCTL0: SMTEN0 Mask           */

#define RTC_GPIOCTL0_OPMODE1_Pos         (8)                                               /*!< RTC_T::GPIOCTL0: OPMODE1 Position      */
#define RTC_GPIOCTL0_OPMODE1_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE1_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE1 Mask          */

#define RTC_GPIOCTL0_DOUT1_Pos           (10)                                              /*!< RTC_T::GPIOCTL0: DOUT1 Position        */
#define RTC_GPIOCTL0_DOUT1_Msk           (0x1ul << RTC_GPIOCTL0_DOUT1_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT1 Mask            */

#define RTC_GPIOCTL0_DINOFF1_Pos         (11)                                              /*!< RTC_T::GPIOCTL0: DINOFF1 Position      */
#define RTC_GPIOCTL0_DINOFF1_Msk         (0x1ul << RTC_GPIOCTL0_DINOFF1_Pos)               /*!< RTC_T::GPIOCTL0: DINOFF1 Mask          */

#define RTC_GPIOCTL0_PUSEL1_Pos          (12)                                              /*!< RTC_T::GPIOCTL0: PUSEL1 Position       */
#define RTC_GPIOCTL0_PUSEL1_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL1_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL1 Mask           */

#define RTC_GPIOCTL0_SMTEN1_Pos          (14)                                              /*!< RTC_T::GPIOCTL0: SMTEN1 Position       */
#define RTC_GPIOCTL0_SMTEN1_Msk          (0x1ul << RTC_GPIOCTL0_SMTEN1_Pos)                /*!< RTC_T::GPIOCTL0: SMTEN1 Mask           */

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

#define RTC_TAMPCTL_TAMP0DEN_Pos         (10)                                              /*!< RTC_T::TAMPCTL: TAMP0DEN Position      */
#define RTC_TAMPCTL_TAMP0DEN_Msk         (0x1ul << RTC_TAMPCTL_TAMP0DEN_Pos)               /*!< RTC_T::TAMPCTL: TAMP0DEN Mask          */

#define RTC_TAMPCTL_TAMP1EN_Pos          (12)                                              /*!< RTC_T::TAMPCTL: TAMP1EN Position       */
#define RTC_TAMPCTL_TAMP1EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP1EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP1EN Mask           */

#define RTC_TAMPCTL_TAMP1LV_Pos          (13)                                              /*!< RTC_T::TAMPCTL: TAMP1LV Position       */
#define RTC_TAMPCTL_TAMP1LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP1LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP1LV Mask           */

#define RTC_TAMPCTL_TAMP1DEN_Pos         (14)                                              /*!< RTC_T::TAMPCTL: TAMP1DEN Position      */
#define RTC_TAMPCTL_TAMP1DEN_Msk         (0x1ul << RTC_TAMPCTL_TAMP1DEN_Pos)               /*!< RTC_T::TAMPCTL: TAMP1DEN Mask          */

#define RTC_TAMPCTL_DYNPR0EN_Pos         (15)                                              /*!< RTC_T::TAMPCTL: DYNPR0EN Position      */
#define RTC_TAMPCTL_DYNPR0EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR0EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR0EN Mask          */

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

#define RTC_PWRSTS_PWRONCNT_Pos          (8)                                               /*!< RTC_T::PWRSTS: PWRONCNT Position       */
#define RTC_PWRSTS_PWRONCNT_Msk          (0x7ffful << RTC_PWRSTS_PWRONCNT_Pos)             /*!< RTC_T::PWRSTS: PWRONCNT Mask           */

#define RTC_PWRSTS_PWROFFCNT_Pos         (24)                                              /*!< RTC_T::PWRSTS: PWROFFCNT Position      */
#define RTC_PWRSTS_PWROFFCNT_Msk         (0x7ul << RTC_PWRSTS_PWROFFCNT_Pos)               /*!< RTC_T::PWRSTS: PWROFFCNT Mask          */

/**@}*/ /* RTC_CONST */
/**@}*/ /* end of RTC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __RTC_REG_H__ */
