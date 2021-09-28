/**************************************************************************//**
 * @file     rtc_reg.h
 * @version  V1.00
 * @brief    RTC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
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
@{ */

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
     * |[31:1]  |INIT      |RTC Initiation
     * |        |          |When RTC block is powered on, RTC is at reset state
     * |        |          |User has to write a number (0x a5eb1357) to INIT to make RTC leaving reset state
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
     * |[30:24] |HZCNT     |Index of sub-second counter(0x00 ~0x7F)
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
     * |        |          |Indicates that RTC_TIME and RTC_TALM are in 24-hour time scale or 12-hour time scale
     * |        |          |0 = 12-hour time scale with AM and PM indication selected.
     * |        |          |1 = 24-hour time scale selected.
     * |[8]     |HZCNTEN   |Sub-second Counter Enable Bit
     * |        |          |0 = HZCNT disabled in RTC_TIME and RTC_TALM.
     * |        |          |1 = HZCNT enabled in RTC_TIME and RTC_TALM .
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
     * |[30:24] |HZCNT     |Index of sub-second counter(0x00 ~0x7F)
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
     * |[0]     |LEAPYEAR  |Leap Year Indication Register (Read Only)
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
     * |        |          |Note: This register can be read back after the RTC register access enable bit RWENF (RTC_RWEN[16]) is active.
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
     * @var RTC_T::LXTCTL
     * Offset: 0x100  RTC 32.768 kHz Oscillator Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7]     |C32KS     |Clock 32K Source Selection:
     * |        |          |0 = Internal 32K clock is from 32K crystal .
     * |        |          |1 = Internal 32K clock is from LIRC32K.
     */
    __IO uint32_t INIT;                  /*!< [0x0000] RTC Initiation Register                                          */
    __I  uint32_t RESERVE0[1];
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
    __I  uint32_t RESERVE1[49];          /* 0x3C ~ 0xFC */
    __IO uint32_t LXTCTL;                /*!< [0x0100] RTC 32.768 kHz Oscillator Control Register                       */

} RTC_T;

/**
    @addtogroup RTC_CONST RTC Bit Field Definition
    Constant Definitions for RTC Controller
@{ */

#define RTC_INIT_ACTIVE_Pos              (0)                                               /*!< RTC_T::INIT: ACTIVE Position           */
#define RTC_INIT_ACTIVE_Msk              (0x1ul << RTC_INIT_ACTIVE_Pos)                    /*!< RTC_T::INIT: ACTIVE Mask               */

#define RTC_INIT_INIT_Pos                (1)                                               /*!< RTC_T::INIT: INIT Position             */
#define RTC_INIT_INIT_Msk                (0x7ffffffful << RTC_INIT_INIT_Pos)               /*!< RTC_T::INIT: INIT Mask                 */

#define RTC_FREQADJ_FRACTION_Pos         (0)                                               /*!< RTC_T::FREQADJ: FRACTION Position      */
#define RTC_FREQADJ_FRACTION_Msk         (0x3ful << RTC_FREQADJ_FRACTION_Pos)              /*!< RTC_T::FREQADJ: FRACTION Mask          */

#define RTC_FREQADJ_INTEGER_Pos          (8)                                               /*!< RTC_T::FREQADJ: INTEGER Position       */
#define RTC_FREQADJ_INTEGER_Msk          (0x1ful << RTC_FREQADJ_INTEGER_Pos)               /*!< RTC_T::FREQADJ: INTEGER Mask           */

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

#define RTC_TIME_HZCNT_Pos               (24)                                              /*!< RTC_T::TIME: HZCNT Position            */
#define RTC_TIME_HZCNT_Msk               (0x7ful << RTC_TIME_HZCNT_Pos)                    /*!< RTC_T::TIME: HZCNT Mask                */

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

#define RTC_CLKFMT_HZCNTEN_Pos           (8)                                               /*!< RTC_T::CLKFMT: HZCNTEN Position        */
#define RTC_CLKFMT_HZCNTEN_Msk           (0x1ul << RTC_CLKFMT_HZCNTEN_Pos)                 /*!< RTC_T::CLKFMT: HZCNTEN Mask            */

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

#define RTC_TALM_HZCNT_Pos               (24)                                              /*!< RTC_T::TALM: HZCNT Position            */
#define RTC_TALM_HZCNT_Msk               (0x7ful << RTC_TALM_HZCNT_Pos)                    /*!< RTC_T::TALM: HZCNT Mask                */

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

#define RTC_INTSTS_ALMIF_Pos             (0)                                               /*!< RTC_T::INTSTS: ALMIF Position          */
#define RTC_INTSTS_ALMIF_Msk             (0x1ul << RTC_INTSTS_ALMIF_Pos)                   /*!< RTC_T::INTSTS: ALMIF Mask              */

#define RTC_INTSTS_TICKIF_Pos            (1)                                               /*!< RTC_T::INTSTS: TICKIF Position         */
#define RTC_INTSTS_TICKIF_Msk            (0x1ul << RTC_INTSTS_TICKIF_Pos)                  /*!< RTC_T::INTSTS: TICKIF Mask             */

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

#define RTC_LXTCTL_C32KS_Pos             (7)                                               /*!< RTC_T::LXTCTL: C32KS Position          */
#define RTC_LXTCTL_C32KS_Msk             (0x1ul << RTC_LXTCTL_C32KS_Pos)                   /*!< RTC_T::LXTCTL: C32KS Mask              */

/**@}*/ /* RTC_CONST */
/**@}*/ /* end of RTC register group */
/**@}*/ /* end of REGISTER group */

#endif /* __RTC_REG_H__ */
