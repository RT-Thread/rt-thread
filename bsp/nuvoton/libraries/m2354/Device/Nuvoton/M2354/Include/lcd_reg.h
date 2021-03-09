/**************************************************************************//**
 * @file     lcd_reg.h
 * @version  V1.00
 * @brief    LCD register definition header file
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __LCD_REG_H__
#define __LCD_REG_H__


/** @addtogroup REGISTER Control Register

  @{

*/


/*---------------------- Liquid-Crystal Display -------------------------*/
/**
    @addtogroup LCD Liquid-Crystal Display(LCD)
    Memory Mapped Structure for LCD Controller
  @{
*/

typedef struct
{


    /**
     * @var LCD_T::CTL
     * Offset: 0x00  LCD Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |EN        |LCD Display Enable Bit
     * |        |          |0 = LCD display function Disabled
     * |        |          |1 = LCD display function Enabled
     * |        |          |Note 1: When software writes 1 to this bit, the LCD Controller needs some synchronizing time to completely enable the LCD display function. Before that, the read value of this bit is still 0.
     * |        |          |Note 2: When software writes 0 to this bit, the LCD Controller needs some synchronizing time to completely disable the LCD display function. Before that, the read value of this bit is still 1.
     * |[31]    |SYNC      |LCD Enable/Disable Synchronizing Indicator (Read Only)
     * |        |          |When software writes 0/1 to EN bit (LCD_CTL[0]), the LCD Controller needs some synchronizing time to completely disable/enable the LCD display function. During this time, this bit keeps at 1.
     * |        |          |0 = LCD display function is completely Disabled/Enabled
     * |        |          |1 = LCD display function is not yet completely Disabled/Enabled
     * |        |          |Note 1: The synchronizing time to enable LCD display function is not constant. It is between one and two cycles of LCD_CLK.
     * |        |          |Note 2: The LCD display function cannot be disabled until the end of a frame. So the maximum synchronizing time to disable LCD display function could be as long as one frame time.
     * @var LCD_T::PCTL
     * Offset: 0x04  LCD Panel Control Registerr
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |BIAS      |LCD Bias Level Selection
     * |        |          |This field is used to select the bias level.
     * |        |          |0 = Reserved
     * |        |          |1 = 1/2 Bias
     * |        |          |2 = 1/3 Bias
     * |        |          |3 = 1/4 Bias
     * |[4:2]   |DUTY      |LCD Duty Ratio Selection
     * |        |          |This field is used to select the duty ratio.
     * |        |          |0 = 1/1 Duty
     * |        |          |1 = 1/2 Duty
     * |        |          |2 = 1/3 Duty
     * |        |          |3 = 1/4 Duty
     * |        |          |4 = 1/5 Duty
     * |        |          |5 = 1/6 Duty
     * |        |          |6 = 1/7 Duty
     * |        |          |7 = 1/8 Duty
     * |[5]     |TYPE      |LCD Waveform Type Selection
     * |        |          |This bit is used to select the waveform type.
     * |        |          |0 = Type A
     * |        |          |1 = Type B
     * |[6]     |INV       |LCD Waveform Inverse
     * |        |          |This bit is used to set the inverse LCD waveform.
     * |        |          |0 = COM/SEG waveform is normal
     * |        |          |1 = COM/SEG waveform is inversed
     * |[17:8]  |FREQDIV   |LCD Operating Frequency Divider
     * |        |          |The field is used to divide LCD_CLK to generate the LCD operating frequency.
     * |        |          |LCD Operating Frequency = (LCD_CLK Frequency) / (FRRQDIV + 1).
     * |        |          |Note 1: FREQDIV can be set from 0 to 1023, therefore, the fastest LCD operating frequency is equal to LCD_CLK frequency,
     * |        |          |and the lowest LCD operating frequency is equal to LCD_CLK frequency divided by 1024.
     * |        |          |Note 2: LCD frame rate is
     * |        |          |(LCD Operating Frequency) x (Duty Ratio) x 1/2 for type A waveform, and
     * |        |          |(LCD Operating Frequency) x (Duty Ratio) for type B waveform.
     * |        |          |Example: Assume LCD operating frequency is 1 kHz, duty ratio is 1/4, then the LCD frame rate is
     * |        |          |1 kHz x (1/4) x (1/2) = 128 Hz for type A waveform, and
     * |        |          |1 kHz x (1/4) = 256 Hz for type B waveform.
     * |[20:18] |CPVSEL    |LCD Operating Voltage (VLCD) Select (For Charge Pump Only)
     * |        |          |This field is used to select the LCD operating voltage.
     * |        |          |0 = 2.6 V
     * |        |          |1 = 2.8 V
     * |        |          |2 = 3.0 V
     * |        |          |3 = 3.2 V
     * |        |          |4 = 3.4 V
     * |        |          |5 = 3.6 V
     * |        |          |Others = (Reserved)
     * |        |          |Note: This field is meaningful only if the VLCD source is the charge pump. Otherwise, this field is ignored.
     * |[27:24] |CPVTUNE   |LCD Operating Voltage (VLCD) Fine Tuning (For Charge Pump Only)
     * |        |          |This field is used to fine tune the LCD operating voltage.
     * |        |          |0 = No tuning
     * |        |          |1 = decrease by 1 unit of voltage
     * |        |          |2 = decrease by 2 unit of voltage
     * |        |          |3 = decrease by 3 unit of voltage
     * |        |          |4 = decrease by 4 unit of voltage
     * |        |          |5 = decrease by 5 unit of voltage
     * |        |          |6 = decrease by 6 unit of voltage
     * |        |          |7 = decrease by 7 unit of voltage
     * |        |          |8 = increase by 8 units of voltage
     * |        |          |9 = increase by 7 units of voltage
     * |        |          |10 = increase by 6 units of voltage
     * |        |          |11 = increase by 5 units of voltage
     * |        |          |12 = increase by 4 units of voltage
     * |        |          |13 = increase by 3 units of voltage
     * |        |          |14 = increase by 2 units of voltage
     * |        |          |15 = increase by 1 unit of voltage
     * |        |          |Note 1: A unit of voltage is about 0.03 V.
     * |        |          |Note 2: This field is meaningful only if the VLCD source is the charge pump. Otherwise, this field is ignored.
     * @var LCD_T::FCTL
     * Offset: 0x08  LCD Frame Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |BLINK     |LCD Blinking Enable Bit
     * |        |          |0 = LCD blinking function Disabled
     * |        |          |1 = LCD blinking function Enabled
     * |[17:8]  |FCV       |Frame Counting Value
     * |        |          |This field indicates the maximum value that the frame counter can reach.
     * |        |          |Note 1: The frame counter automatically increases by 1 at the end of every frame. When the counter reaches FCV, it will recounts from 0 at the end of the next frame.
     * |        |          |At this moment, the hardware sets a dedicated flag to 1, and triggers a dedicated interrupt if it is enabled.
     * |        |          |Note 2: For type B waveform, the frame counter increases at the end of odd frames, not even frames.
     * |[27:24] |NFTIME    |Null Frame Time
     * |        |          |This field is used to configure the length of a null frame.
     * |        |          |One null frame time is (1 / LCD_FREQ) x NFTIME.
     * |        |          |Note: All COM and SEG output voltages are 0 V during a null frame.
     * |[31:28] |NFNUM     |Number of Frames Inserted By One Null Frame
     * |        |          |This field is used to specify the number of continuous normal frames inserted by one null frame.
     * |        |          |The number of continuous normal frames is (NFNUM + 1) frames.
     * @var LCD_T::DCTL
     * Offset: 0x0C  LCD Driving Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[1:0]   |VSRC      |LCD Operating Voltage (VLCD) Source
     * |        |          |0 = VLCD Power
     * |        |          |1 = AVDD Power
     * |        |          |2 = Built-In Charge Pump
     * |        |          |3 = None
     * |        |          |Note: Whenever the LCD controller is disabled, all VLCD sources are automatically cut off.
     * |[2]     |RESMODE   |Resistive Network Driving Mode
     * |        |          |0 = Low-Drive Mode
     * |        |          |1 = High-Drive Mode
     * |[3]     |BUFEN     |Voltage Buffer Enable Bit
     * |        |          |0 = Voltage Buffer Disabled
     * |        |          |1 = Voltage Buffer Enabled
     * |        |          |Note: When RESMODE = 1, the voltage buffers are automatically disabled. The setting of BUFEN bit is ignored.
     * |[4]     |PSVEN     |Power Saving Mode Enable Bit
     * |        |          |0 = Power Saving Mode Disabled
     * |        |          |1 = Power Saving Mode Enabled
     * |        |          |Note: when RESMODE = 0 and BUFEN = 0, the output drivers consumes the least driving current. In this case, the power saving mode is automatically disabled. The setting of PSVEN bit is ignored.
     * |[5]     |PSVREV    |Power Saving Timing Reverse
     * |        |          |When the timing is reversed, the original powe-saving period becomes no-power-saving, and the original no-power-saving period becomes power-saving.
     * |        |          |0 = Timing of power saving is normal
     * |        |          |1 = Timing of power saving is reversed
     * |[11:8]  |PSVT1     |Power Saving "Enable Time" Setting
     * |        |          |The "Enable Time" of the power saving mode is calculated as "Enable Time" = 15.26 us x (PSVT1 + 1),
     * |        |          |where 15.26 us is the half-cycle time of LCD_CLK, whose frequency is about 32 kHz.
     * |        |          |PSVT1 can be set as 0, 1, 2, ..., 15, so the minimum "Enable Time" is about 15.26 us, and the maximum "Enable Time" is about 15.26 x 16 = 244.14 us.
     * |        |          |Note: In the following two cases, the power saving mode is disabled. The setting of PSVT1 bits is ignored.
     * |        |          |1. PSVEN = 0
     * |        |          |2. RESMODE = 0 and BUFEN = 0
     * |[15:12] |PSVT2     |Power Saving "On Time" Setting
     * |        |          |The "On Time" of the power saving mode is calculated as "On Time" = 15.26 us x (PSVT2 + 1),
     * |        |          |where 15.26 us is the half-cycle time of LCD_CLK, whose frequency is about 32 kHz.
     * |        |          |PSVT2 can be set as 0, 1, 2, ..., 15, so the minimum "On Time" is about 15.26 us, and the maximum "On Time" is about 15.26 x 16 = 244.14 us.
     * |        |          |Note: In the following two cases, the power saving mode is disabled. The setting of PSVT2 bits is ignored.
     * |        |          |1. PSVEN = 0
     * |[28:16] |CTOTIME   |Charging Timer Timeout Time
     * |        |          |This field is used to specify the timeout value for the charging timer. When the charging timer reaches this timeout value, a status bit or an interrupt will occur.
     * |        |          |The timeout is calculated by the following formula: Timeout = 30.52 us x (CTOTIME + 1), where 30.52 us is the cycle time of LCD_CLK, whose frequency is about 32 kHz.
     * |        |          |CTOTIME can be set as 0, 1, 2, ..., 8191, so the minimum timeout is 30.52 us, and the maximum timeout is 30.52 x 8192 = 256 ms.
     * @var LCD_T::PKGSEL
     * Offset: 0x10  LCD Package Selection Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |PKG       |Device Package Type Selection
     * |        |          |0 = 128-Pin Package
     * |        |          |1 = 64-Pin Package
     * @var LCD_T::STS
     * Offset: 0x14  LCD Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FCEF      |End of Frame-Counting Flag
     * |        |          |This flag is automatically set by hardware at the end of a frame, and the frame counter value must be equal to FCV (LCD_FCTL[17:8], Frame Counting Value).
     * |        |          |0 = End of Frame-Counting did not occur
     * |        |          |1 = End of Frame-Counting occurred
     * |        |          |Note 1: User can clear this bit by writing 1 to it.
     * |        |          |Note 2: For type B waveform, this flag is set only at the end of an odd frame.
     * |[1]     |FEF       |End of Frame Flag
     * |        |          |This flag is automatically set by hardware at the end of a frame.
     * |        |          |0 = End of Frame did not occur
     * |        |          |1 = End of Frame occurred
     * |        |          |Note 1: User can clear this bit by writing 1 to it.
     * |        |          |Note 2: For type B waveform, this flag is set only at the end of an odd frame.
     * |[2]     |CTOF      |Charging Timeout Flag
     * |        |          |This flag is automatically set by hardware when the charging timer reaches the timeout value.
     * |        |          |0 = Charging Timeout did not occur
     * |        |          |1 = Charging Timeout occurred
     * |        |          |Note: User can clear this bit by writing 1 to it.
     * |[28:16] |CTIME     |Charging Timer Value (Read Only)
     * |        |          |The field contains the value of the charging timer. It records the charging time of the charge pump.
     * |        |          |The charging timer stops counting when the charge pump stops charging or a timeout occurs. At this moment, the hardware dumps the current charging timer value into this field.
     * |        |          |Charging Time = 30.52 us x (CTIME + 1), where 30.52 us is the cycle time of LCD_CLK, whose frequency is about 32 kHz.
     * @var LCD_T::INTEN
     * Offset: 0x18  LCD Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |FCEIEN    |End of Frame-Counting Interrupt Enable Bit
     * |        |          |An interrupt occurs at the end of a frame, and the frame counter value must be equal to FCV (LCD_FCTL[17:8], Frame Counting Value).
     * |        |          |0 = End of Frame-Counting Interrupt Disabled
     * |        |          |1 = End of Frame-Counting Interrupt Enabled
     * |        |          |Note: For type B waveform, the interrupt occurs only at the end of an odd frame.
     * |[1]     |FEIEN     |End of Frame Interrupt Enable Bit
     * |        |          |An interrupt occurs at the end of a frame.
     * |        |          |0 = End of Frame Interrupt Disabled
     * |        |          |1 = End of Frame Interrupt Enabled
     * |        |          |Note: For type B waveform, the interrupt occurs only at the end of an odd frame.
     * |[2]     |CTOIEN    |Charging Timeout Interrupt Enable Bit
     * |        |          |An interrupt occurs when the charging timer reaches the timeout value.
     * |        |          |0 = Charging Timeout Interrupt Disabled
     * |        |          |1 = Charging Timeout Interrupt Enabled
     * @var LCD_T::DATA
     * Offset: 0x20  LCD Segment Display Data Register 0
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x24  LCD Segment Display Data Register 1
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x28  LCD Segment Display Data Register 2
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x2C  LCD Segment Display Data Register 3
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x30  LCD Segment Display Data Register 4
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x34  LCD Segment Display Data Register 5
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x38  LCD Segment Display Data Register 6
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x3C  LCD Segment Display Data Register 7
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x40  LCD Segment Display Data Register 8
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x44  LCD Segment Display Data Register 9
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     * Offset: 0x48  LCD Segment Display Data Register 10
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |DD0       |Display Data of Segments S, where S is (4 x N) + 0, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD0 corresponds to SEG00, SEG04, SEG08, SEG12, SEG16, SEG20, SEG24, SEG28, SEG32, SEG36, and SEG40.
     * |        |          |Note 2: Each bit, DD0[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD0 (= LCD_DATA07[7:0]) = 1001_0110, LCD_DATA07[7:0] corresponds to SEG28 (4 x 7 + 0 = 28),
     * |        |          |the pixel SEG28-COM0 is light (LCD_DATA07[0] = 0),
     * |        |          |the pixel SEG28-COM1 is dark (LCD_DATA07[1] = 1),
     * |        |          |the pixel SEG28-COM2 is dark (LCD_DATA07[2] = 1),
     * |        |          |the pixel SEG28-COM3 is light (LCD_DATA07[3] = 0),
     * |        |          |LCD_DATA07[7:4] are ignored, since COMs from 4 to 7 are not used.
     * |[15:8]  |DD1       |Display Data of Segments S, where S is (4 x N) + 1, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD1 corresponds to SEG01, SEG05, SEG09, SEG13, SEG17, SEG21, SEG25, SEG29, SEG33, SEG37, and SEG41.
     * |        |          |Note 2: Each bit, DD1[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD1 (= LCD_DATA07[15:8]) = 1001_0110, LCD_DATA07[15:8] corresponds to SEG29 (4 x 7 + 1 = 29),
     * |        |          |the pixel SEG29-COM0 is light (LCD_DATA07[8] = 0),
     * |        |          |the pixel SEG29-COM1 is dark (LCD_DATA07[9] = 1),
     * |        |          |the pixel SEG29-COM2 is dark (LCD_DATA07[10] = 1),
     * |        |          |the pixel SEG29-COM3 is light (LCD_DATA07[11] = 0),
     * |        |          |LCD_DATA07[15:12] are ignored, since COMs from 4 to 7 are not used.
     * |[23:16] |DD2       |Display Data of Segments S, where S is (4 x N) + 2, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD2 corresponds to SEG02, SEG06, SEG10, SEG14, SEG18, SEG22, SEG26, SEG30, SEG34, SEG38, and SEG42.
     * |        |          |Note 2: Each bit, DD2[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD2 (= LCD_DATA07[23:16]) = 1001_0110, LCD_DATA07[23:16] corresponds to SEG31 (4 x 7 + 2 = 30),
     * |        |          |the pixel SEG30-COM0 is light (LCD_DATA07[16] = 0),
     * |        |          |the pixel SEG30-COM1 is dark (LCD_DATA07[17] = 1),
     * |        |          |the pixel SEG30-COM2 is dark (LCD_DATA07[18] = 1),
     * |        |          |the pixel SEG30-COM3 is light (LCD_DATA07[19] = 0),
     * |        |          |LCD_DATA07[23:20] are ignored, since COMs from 4 to 7 are not used.
     * |[31:24] |DD3       |Display Data of Segments S, where S is (4 x N) + 3, and N is 0, 1, 2, ..., 10
     * |        |          |Each bit specifies the brightness of each pixel in a segment.
     * |        |          |0 = The pixel is light
     * |        |          |1 = The pixel is dark
     * |        |          |Note 1: DD3 corresponds to SEG03, SEG07, SEG11, SEG15, SEG19, SEG23, SEG27, SEG31, SEG35, SEG39, and SEG43.
     * |        |          |Note 2: Each bit, DD3[n], corresponds to COMn, n= 0 ~ 7.
     * |        |          |[Example] Assume 1/4 Duty, and DD3 (= LCD_DATA07[31:24]) = 1001_0110, LCD_DATA07[31:24] corresponds to SEG31 (4 x 7 + 3 = 31),
     * |        |          |the pixel SEG31-COM0 is light (LCD_DATA07[24] = 0),
     * |        |          |the pixel SEG31-COM1 is dark (LCD_DATA07[25] = 1),
     * |        |          |the pixel SEG31-COM2 is dark (LCD_DATA07[26] = 1),
     * |        |          |the pixel SEG31-COM3 is light (LCD_DATA07[27] = 0),
     * |        |          |LCD_DATA07[31:28] are ignored, since COMs from 4 to 7 are not used.
     */
    __IO uint32_t CTL;                  /*!< [0x0000] LCD Control Register                                      */
    __IO uint32_t PCTL;                 /*!< [0x0004] LCD Panel Control Register                                */
    __IO uint32_t FCTL;                 /*!< [0x0008] LCD Frame Control Register                                */
    __IO uint32_t DCTL;                 /*!< [0x000C] LCD Driving Control Register                              */
    __IO uint32_t PKGSEL;               /*!< [0x0010] LCD Package Selection Register                            */
    __IO uint32_t STS;                  /*!< [0x0014] LCD Status Register                                       */
    __IO uint32_t INTEN;                /*!< [0x0018] LCD Interrupt Enable Register                             */
    __I  uint32_t RESERVED0;            /*!< [0x001C] Reserved 0                                                */
    __IO uint32_t DATA[11];             /*!< [0x0020] ~ [0x0048] LCD Segment Display Data Register 0 ~ 10       */

} LCD_T;

/**
    @addtogroup LCD_CONST LCD Bit Field Definition
    Constant Definitions for LCD Controller
  @{
*/

#define LCD_CTL_EN_Pos                  (0)                                                 /*!< LCD_T::CTL: EN Position                */
#define LCD_CTL_EN_Msk                  (0x1ul << LCD_CTL_EN_Pos)                           /*!< LCD_T::CTL: EN Mask                    */

#define LCD_CTL_SYNC_Pos                (31)                                                /*!< LCD_T::CTL: SYNC Position              */
#define LCD_CTL_SYNC_Msk                (0x1ul << LCD_CTL_SYNC_Pos)                         /*!< LCD_T::CTL: SYNC Mask                  */

#define LCD_PCTL_BIAS_Pos               (0)                                                 /*!< LCD_T::PCTL: BIAS Position             */
#define LCD_PCTL_BIAS_Msk               (0x3ul << LCD_PCTL_BIAS_Pos)                        /*!< LCD_T::PCTL: BIAS Mask                 */

#define LCD_PCTL_DUTY_Pos               (2)                                                 /*!< LCD_T::PCTL: DUTY Position             */
#define LCD_PCTL_DUTY_Msk               (0x7ul << LCD_PCTL_DUTY_Pos)                        /*!< LCD_T::PCTL: DUTY Mask                 */

#define LCD_PCTL_TYPE_Pos               (5)                                                 /*!< LCD_T::PCTL: TYPE Position             */
#define LCD_PCTL_TYPE_Msk               (0x1ul << LCD_PCTL_TYPE_Pos)                        /*!< LCD_T::PCTL: TYPE Mask                 */

#define LCD_PCTL_INV_Pos                (6)                                                 /*!< LCD_T::PCTL: INV Position              */
#define LCD_PCTL_INV_Msk                (0x1ul << LCD_PCTL_INV_Pos)                         /*!< LCD_T::PCTL: INV Mask                  */

#define LCD_PCTL_FREQDIV_Pos            (8)                                                 /*!< LCD_T::PCTL: FREQDIV Position          */
#define LCD_PCTL_FREQDIV_Msk            (0x3fful << LCD_PCTL_FREQDIV_Pos)                   /*!< LCD_T::PCTL: FREQDIV Mask              */

#define LCD_PCTL_CPVSEL_Pos             (18)                                                /*!< LCD_T::PCTL: CPVSEL Position           */
#define LCD_PCTL_CPVSEL_Msk             (0x7ul << LCD_PCTL_CPVSEL_Pos)                      /*!< LCD_T::PCTL: CPVSEL Mask               */

#define LCD_PCTL_CPVTUNE_Pos            (24)                                                /*!< LCD_T::PCTL: CPVTUNE Position          */
#define LCD_PCTL_CPVTUNE_Msk            (0xful << LCD_PCTL_CPVTUNE_Pos)                     /*!< LCD_T::PCTL: CPVTUNE Mask              */

#define LCD_FCTL_BLINK_Pos              (0)                                                 /*!< LCD_T::FCTL: BLINK Position            */
#define LCD_FCTL_BLINK_Msk              (0x1ul << LCD_FCTL_BLINK_Pos)                       /*!< LCD_T::FCTL: BLINK Mask                */

#define LCD_FCTL_FCV_Pos                (8)                                                 /*!< LCD_T::FCTL: FCV Position              */
#define LCD_FCTL_FCV_Msk                (0x3fful << LCD_FCTL_FCV_Pos)                       /*!< LCD_T::FCTL: FCV Mask                  */

#define LCD_FCTL_NFTIME_Pos             (24)                                                /*!< LCD_T::FCTL: NFTIME Position           */
#define LCD_FCTL_NFTIME_Msk             (0xful << LCD_FCTL_NFTIME_Pos)                      /*!< LCD_T::FCTL: NFTIME Mask               */

#define LCD_FCTL_NFNUM_Pos              (28)                                                /*!< LCD_T::FCTL: NFNUM Position            */
#define LCD_FCTL_NFNUM_Msk              (0xful << LCD_FCTL_NFNUM_Pos)                       /*!< LCD_T::FCTL: NFNUM Mask                */

#define LCD_DCTL_VSRC_Pos               (0)                                                 /*!< LCD_T::DCTL: VSRC Position             */
#define LCD_DCTL_VSRC_Msk               (0x3ul << LCD_DCTL_VSRC_Pos)                        /*!< LCD_T::DCTL: VSRC Mask                 */

#define LCD_DCTL_RESMODE_Pos            (2)                                                 /*!< LCD_T::DCTL: RESMODE Position          */
#define LCD_DCTL_RESMODE_Msk            (0x1ul << LCD_DCTL_RESMODE_Pos)                     /*!< LCD_T::DCTL: RESMODE Mask              */

#define LCD_DCTL_BUFEN_Pos              (3)                                                 /*!< LCD_T::DCTL: BUFEN Position            */
#define LCD_DCTL_BUFEN_Msk              (0x1ul << LCD_DCTL_BUFEN_Pos)                       /*!< LCD_T::DCTL: BUFEN Mask                */

#define LCD_DCTL_PSVEN_Pos              (4)                                                 /*!< LCD_T::DCTL: PSVEN Position            */
#define LCD_DCTL_PSVEN_Msk              (0x1ul << LCD_DCTL_PSVEN_Pos)                       /*!< LCD_T::DCTL: PSVEN Mask                */

#define LCD_DCTL_PSVREV_Pos             (5)                                                 /*!< LCD_T::DCTL: PSVREV Position           */
#define LCD_DCTL_PSVREV_Msk             (0x1ul << LCD_DCTL_PSVREV_Pos)                      /*!< LCD_T::DCTL: PSVREV Mask               */

#define LCD_DCTL_PSVT1_Pos              (8)                                                 /*!< LCD_T::DCTL: PSVT1 Position            */
#define LCD_DCTL_PSVT1_Msk              (0xful << LCD_DCTL_PSVT1_Pos)                       /*!< LCD_T::DCTL: PSVT1 Mask                */

#define LCD_DCTL_PSVT2_Pos              (12)                                                /*!< LCD_T::DCTL: PSVT2 Position            */
#define LCD_DCTL_PSVT2_Msk              (0xful << LCD_DCTL_PSVT2_Pos)                       /*!< LCD_T::DCTL: PSVT2 Mask                */

#define LCD_DCTL_CTOTIME_Pos            (16)                                                /*!< LCD_T::DCTL: CTOTIME Position          */
#define LCD_DCTL_CTOTIME_Msk            (0x1ffful << LCD_DCTL_CTOTIME_Pos)                  /*!< LCD_T::DCTL: CTOTIME Mask              */

#define LCD_PKGSEL_PKG_Pos              (0)                                                 /*!< LCD_T::PKGSEL: PKG Position            */
#define LCD_PKGSEL_PKG_Msk              (0x1ul << LCD_PKGSEL_PKG_Pos)                       /*!< LCD_T::PKGSEL: PKG Mask                */

#define LCD_STS_FCEF_Pos                (0)                                                 /*!< LCD_T::STS: FCEF Position              */
#define LCD_STS_FCEF_Msk                (0x1ul << LCD_STS_FCEF_Pos)                         /*!< LCD_T::STS: FCEF Mask                  */

#define LCD_STS_FEF_Pos                 (1)                                                 /*!< LCD_T::STS: FEF Position               */
#define LCD_STS_FEF_Msk                 (0x1ul << LCD_STS_FEF_Pos)                          /*!< LCD_T::STS: FEF Mask                   */

#define LCD_STS_CTOF_Pos                (2)                                                 /*!< LCD_T::STS: CTOF Position              */
#define LCD_STS_CTOF_Msk                (0x1ul << LCD_STS_CTOF_Pos)                         /*!< LCD_T::STS: CTOF Mask                  */

#define LCD_STS_CTIME_Pos               (16)                                                /*!< LCD_T::STS: CTIME Position             */
#define LCD_STS_CTIME_Msk               (0x1ffful << LCD_STS_CTIME_Pos)                     /*!< LCD_T::STS: CTIME Mask                 */

#define LCD_INTEN_FCEIEN_Pos            (0)                                                 /*!< LCD_T::INTEN: FCEIEN Position          */
#define LCD_INTEN_FCEIEN_Msk            (0x1ul << LCD_INTEN_FCEIEN_Pos)                     /*!< LCD_T::INTEN: FCEIEN Mask              */

#define LCD_INTEN_FEIEN_Pos             (1)                                                 /*!< LCD_T::INTEN: FEIEN Position           */
#define LCD_INTEN_FEIEN_Msk             (0x1ul << LCD_INTEN_FEIEN_Pos)                      /*!< LCD_T::INTEN: FEIEN Mask               */

#define LCD_INTEN_CTOIEN_Pos            (2)                                                 /*!< LCD_T::INTEN: CYOIEN Position          */
#define LCD_INTEN_CTOIEN_Msk            (0x1ul << LCD_INTEN_CTOIEN_Pos)                     /*!< LCD_T::INTEN: CTOIEN Mask              */

#define LCD_DATA00_DD0_Pos              (0)                                                 /*!< LCD_T::DATA00: DD0 Position            */
#define LCD_DATA00_DD0_Msk              (0xfful << LCD_DATA00_DD0_Pos)                      /*!< LCD_T::DATA00: DD0 Mask                */

#define LCD_DATA00_DD1_Pos              (8)                                                 /*!< LCD_T::DATA00: DD1 Position            */
#define LCD_DATA00_DD1_Msk              (0xfful << LCD_DATA00_DD1_Pos)                      /*!< LCD_T::DATA00: DD1 Mask                */

#define LCD_DATA00_DD2_Pos              (16)                                                /*!< LCD_T::DATA00: DD2 Position            */
#define LCD_DATA00_DD2_Msk              (0xfful << LCD_DATA00_DD2_Pos)                      /*!< LCD_T::DATA00: DD2 Mask                */

#define LCD_DATA00_DD3_Pos              (24)                                                /*!< LCD_T::DATA00: DD3 Position            */
#define LCD_DATA00_DD3_Msk              (0xfful << LCD_DATA00_DD3_Pos)                      /*!< LCD_T::DATA00: DD3 Mask                */

#define LCD_DATA01_DD0_Pos              (0)                                                 /*!< LCD_T::DATA01: DD0 Position            */
#define LCD_DATA01_DD0_Msk              (0xfful << LCD_DATA01_DD0_Pos)                      /*!< LCD_T::DATA01: DD0 Mask                */

#define LCD_DATA01_DD1_Pos              (8)                                                 /*!< LCD_T::DATA01: DD1 Position            */
#define LCD_DATA01_DD1_Msk              (0xfful << LCD_DATA01_DD1_Pos)                      /*!< LCD_T::DATA01: DD1 Mask                */

#define LCD_DATA01_DD2_Pos              (16)                                                /*!< LCD_T::DATA01: DD2 Position            */
#define LCD_DATA01_DD2_Msk              (0xfful << LCD_DATA01_DD2_Pos)                      /*!< LCD_T::DATA01: DD2 Mask                */

#define LCD_DATA01_DD3_Pos              (24)                                                /*!< LCD_T::DATA01: DD3 Position            */
#define LCD_DATA01_DD3_Msk              (0xfful << LCD_DATA01_DD3_Pos)                      /*!< LCD_T::DATA01: DD3 Mask                */

#define LCD_DATA02_DD0_Pos              (0)                                                 /*!< LCD_T::DATA02: DD0 Position            */
#define LCD_DATA02_DD0_Msk              (0xfful << LCD_DATA02_DD0_Pos)                      /*!< LCD_T::DATA02: DD0 Mask                */

#define LCD_DATA02_DD1_Pos              (8)                                                 /*!< LCD_T::DATA02: DD1 Position            */
#define LCD_DATA02_DD1_Msk              (0xfful << LCD_DATA02_DD1_Pos)                      /*!< LCD_T::DATA02: DD1 Mask                */

#define LCD_DATA02_DD2_Pos              (16)                                                /*!< LCD_T::DATA02: DD2 Position            */
#define LCD_DATA02_DD2_Msk              (0xfful << LCD_DATA02_DD2_Pos)                      /*!< LCD_T::DATA02: DD2 Mask                */

#define LCD_DATA02_DD3_Pos              (24)                                                /*!< LCD_T::DATA02: DD3 Position            */
#define LCD_DATA02_DD3_Msk              (0xfful << LCD_DATA02_DD3_Pos)                      /*!< LCD_T::DATA02: DD3 Mask                */

#define LCD_DATA03_DD0_Pos              (0)                                                 /*!< LCD_T::DATA03: DD0 Position            */
#define LCD_DATA03_DD0_Msk              (0xfful << LCD_DATA03_DD0_Pos)                      /*!< LCD_T::DATA03: DD0 Mask                */

#define LCD_DATA03_DD1_Pos              (8)                                                 /*!< LCD_T::DATA03: DD1 Position            */
#define LCD_DATA03_DD1_Msk              (0xfful << LCD_DATA03_DD1_Pos)                      /*!< LCD_T::DATA03: DD1 Mask                */

#define LCD_DATA03_DD2_Pos              (16)                                                /*!< LCD_T::DATA03: DD2 Position            */
#define LCD_DATA03_DD2_Msk              (0xfful << LCD_DATA03_DD2_Pos)                      /*!< LCD_T::DATA03: DD2 Mask                */

#define LCD_DATA03_DD3_Pos              (24)                                                /*!< LCD_T::DATA03: DD3 Position            */
#define LCD_DATA03_DD3_Msk              (0xfful << LCD_DATA03_DD3_Pos)                      /*!< LCD_T::DATA03: DD3 Mask                */

#define LCD_DATA04_DD0_Pos              (0)                                                 /*!< LCD_T::DATA04: DD0 Position            */
#define LCD_DATA04_DD0_Msk              (0xfful << LCD_DATA04_DD0_Pos)                      /*!< LCD_T::DATA04: DD0 Mask                */

#define LCD_DATA04_DD1_Pos              (8)                                                 /*!< LCD_T::DATA04: DD1 Position            */
#define LCD_DATA04_DD1_Msk              (0xfful << LCD_DATA04_DD1_Pos)                      /*!< LCD_T::DATA04: DD1 Mask                */

#define LCD_DATA04_DD2_Pos              (16)                                                /*!< LCD_T::DATA04: DD2 Position            */
#define LCD_DATA04_DD2_Msk              (0xfful << LCD_DATA04_DD2_Pos)                      /*!< LCD_T::DATA04: DD2 Mask                */

#define LCD_DATA04_DD3_Pos              (24)                                                /*!< LCD_T::DATA04: DD3 Position            */
#define LCD_DATA04_DD3_Msk              (0xfful << LCD_DATA04_DD3_Pos)                      /*!< LCD_T::DATA04: DD3 Mask                */

#define LCD_DATA05_DD0_Pos              (0)                                                 /*!< LCD_T::DATA05: DD0 Position            */
#define LCD_DATA05_DD0_Msk              (0xfful << LCD_DATA05_DD0_Pos)                      /*!< LCD_T::DATA05: DD0 Mask                */

#define LCD_DATA05_DD1_Pos              (8)                                                 /*!< LCD_T::DATA05: DD1 Position            */
#define LCD_DATA05_DD1_Msk              (0xfful << LCD_DATA05_DD1_Pos)                      /*!< LCD_T::DATA05: DD1 Mask                */

#define LCD_DATA05_DD2_Pos              (16)                                                /*!< LCD_T::DATA05: DD2 Position            */
#define LCD_DATA05_DD2_Msk              (0xfful << LCD_DATA05_DD2_Pos)                      /*!< LCD_T::DATA05: DD2 Mask                */

#define LCD_DATA05_DD3_Pos              (24)                                                /*!< LCD_T::DATA05: DD3 Position            */
#define LCD_DATA05_DD3_Msk              (0xfful << LCD_DATA05_DD3_Pos)                      /*!< LCD_T::DATA05: DD3 Mask                */

#define LCD_DATA06_DD0_Pos              (0)                                                 /*!< LCD_T::DATA06: DD0 Position            */
#define LCD_DATA06_DD0_Msk              (0xfful << LCD_DATA06_DD0_Pos)                      /*!< LCD_T::DATA06: DD0 Mask                */

#define LCD_DATA06_DD1_Pos              (8)                                                 /*!< LCD_T::DATA06: DD1 Position            */
#define LCD_DATA06_DD1_Msk              (0xfful << LCD_DATA06_DD1_Pos)                      /*!< LCD_T::DATA06: DD1 Mask                */

#define LCD_DATA06_DD2_Pos              (16)                                                /*!< LCD_T::DATA06: DD2 Position            */
#define LCD_DATA06_DD2_Msk              (0xfful << LCD_DATA06_DD2_Pos)                      /*!< LCD_T::DATA06: DD2 Mask                */

#define LCD_DATA06_DD3_Pos              (24)                                                /*!< LCD_T::DATA06: DD3 Position            */
#define LCD_DATA06_DD3_Msk              (0xfful << LCD_DATA06_DD3_Pos)                      /*!< LCD_T::DATA06: DD3 Mask                */

#define LCD_DATA07_DD0_Pos              (0)                                                 /*!< LCD_T::DATA07: DD0 Position            */
#define LCD_DATA07_DD0_Msk              (0xfful << LCD_DATA07_DD0_Pos)                      /*!< LCD_T::DATA07: DD0 Mask                */

#define LCD_DATA07_DD1_Pos              (8)                                                 /*!< LCD_T::DATA07: DD1 Position            */
#define LCD_DATA07_DD1_Msk              (0xfful << LCD_DATA07_DD1_Pos)                      /*!< LCD_T::DATA07: DD1 Mask                */

#define LCD_DATA07_DD2_Pos              (16)                                                /*!< LCD_T::DATA07: DD2 Position            */
#define LCD_DATA07_DD2_Msk              (0xfful << LCD_DATA07_DD2_Pos)                      /*!< LCD_T::DATA07: DD2 Mask                */

#define LCD_DATA07_DD3_Pos              (24)                                                /*!< LCD_T::DATA07: DD3 Position            */
#define LCD_DATA07_DD3_Msk              (0xfful << LCD_DATA07_DD3_Pos)                      /*!< LCD_T::DATA07: DD3 Mask                */

#define LCD_DATA08_DD0_Pos              (0)                                                 /*!< LCD_T::DATA08: DD0 Position            */
#define LCD_DATA08_DD0_Msk              (0xfful << LCD_DATA08_DD0_Pos)                      /*!< LCD_T::DATA08: DD0 Mask                */

#define LCD_DATA08_DD1_Pos              (8)                                                 /*!< LCD_T::DATA08: DD1 Position            */
#define LCD_DATA08_DD1_Msk              (0xfful << LCD_DATA08_DD1_Pos)                      /*!< LCD_T::DATA08: DD1 Mask                */

#define LCD_DATA08_DD2_Pos              (16)                                                /*!< LCD_T::DATA08: DD2 Position            */
#define LCD_DATA08_DD2_Msk              (0xfful << LCD_DATA08_DD2_Pos)                      /*!< LCD_T::DATA08: DD2 Mask                */

#define LCD_DATA08_DD3_Pos              (24)                                                /*!< LCD_T::DATA08: DD3 Position            */
#define LCD_DATA08_DD3_Msk              (0xfful << LCD_DATA08_DD3_Pos)                      /*!< LCD_T::DATA08: DD3 Mask                */

#define LCD_DATA09_DD0_Pos              (0)                                                 /*!< LCD_T::DATA09: DD0 Position            */
#define LCD_DATA09_DD0_Msk              (0xfful << LCD_DATA09_DD0_Pos)                      /*!< LCD_T::DATA09: DD0 Mask                */

#define LCD_DATA09_DD1_Pos              (8)                                                 /*!< LCD_T::DATA09: DD1 Position            */
#define LCD_DATA09_DD1_Msk              (0xfful << LCD_DATA09_DD1_Pos)                      /*!< LCD_T::DATA09: DD1 Mask                */

#define LCD_DATA09_DD2_Pos              (16)                                                /*!< LCD_T::DATA09: DD2 Position            */
#define LCD_DATA09_DD2_Msk              (0xfful << LCD_DATA09_DD2_Pos)                      /*!< LCD_T::DATA09: DD2 Mask                */

#define LCD_DATA09_DD3_Pos              (24)                                                /*!< LCD_T::DATA09: DD3 Position            */
#define LCD_DATA09_DD3_Msk              (0xfful << LCD_DATA09_DD3_Pos)                      /*!< LCD_T::DATA09: DD3 Mask                */

#define LCD_DATA10_DD0_Pos              (0)                                                 /*!< LCD_T::DATA10: DD0 Position            */
#define LCD_DATA10_DD0_Msk              (0xfful << LCD_DATA10_DD0_Pos)                      /*!< LCD_T::DATA10: DD0 Mask                */

#define LCD_DATA10_DD1_Pos              (8)                                                 /*!< LCD_T::DATA10: DD1 Position            */
#define LCD_DATA10_DD1_Msk              (0xfful << LCD_DATA10_DD1_Pos)                      /*!< LCD_T::DATA10: DD1 Mask                */

#define LCD_DATA10_DD2_Pos              (16)                                                /*!< LCD_T::DATA10: DD2 Position            */
#define LCD_DATA10_DD2_Msk              (0xfful << LCD_DATA10_DD2_Pos)                      /*!< LCD_T::DATA10: DD2 Mask                */

#define LCD_DATA10_DD3_Pos              (24)                                                /*!< LCD_T::DATA10: DD3 Position            */
#define LCD_DATA10_DD3_Msk              (0xfful << LCD_DATA10_DD3_Pos)                      /*!< LCD_T::DATA10: DD3 Mask                */

/**@}*/ /* LCD_CONST */
/**@}*/ /* end of LCD register group */
/**@}*/ /* end of REGISTER group */


#endif /* __LCD_REG_H__ */
