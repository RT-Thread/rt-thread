 /*************************************************************************//**
 * @file dmd_ssd2119.h
 * @brief Register definitions for LCD controller SSD2119
 * @author Energy Micro AS
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2012 Energy Micro AS, http://www.energymicro.com</b>
 ******************************************************************************
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 4. The source and compiled code may only be used on Energy Micro "EFM32"
 *    microcontrollers and "EFR4" radios.
 *
 * DISCLAIMER OF WARRANTY/LIMITATION OF REMEDIES: Energy Micro AS has no
 * obligation to support this Software. Energy Micro AS is providing the
 * Software "AS IS", with no express or implied warranties of any kind,
 * including, but not limited to, any implied warranties of merchantability
 * or fitness for any particular purpose or warranties against infringement
 * of any proprietary rights of a third party.
 *
 * Energy Micro AS will not be liable for any consequential, incidental, or
 * special damages, or any other relief, or for any claim by any third party,
 * arising from your use of this Software.
 *
 *****************************************************************************/

#ifndef __DMD_SSD2119_REGISTERS_H_
#define __DMD_SSD2119_REGISTERS_H_

#define DMD_SSD2119_DEVICE_CODE_READ                        0x00
#define DMD_SSD2119_OSCILLATION_START                       0x00
#define DMD_SSD2119_OSCILLATION_START_OSCEN                 0x0001

#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL                   0x01
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_RL                0x4000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_REV               0x2000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_GD                0x1000
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_BGR               0x0800
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_SM                0x0400
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_TB                0x0200
#define DMD_SSD2119_DRIVER_OUTPUT_CONTROL_MUX_SHIFT         0

#define DMD_SSD2119_LCD_AC_CONTROL                          0x02
#define DMD_SSD2119_LCD_AC_CONTROL_FLC                      0x1000
#define DMD_SSD2119_LCD_AC_CONTROL_ENWS                     0x0800
#define DMD_SSD2119_LCD_AC_CONTROL_BC                       0x0400
#define DMD_SSD2119_LCD_AC_CONTROL_EOR                      0x0200
#define DMD_SSD2119_LCD_AC_CONTROL_WSMD                     0x0100
#define DMD_SSD2119_LCD_AC_CONTROL_NW_SHIFT                 0

#define DMD_SSD2119_POWER_CONTROL_1                         0x03
#define DMD_SSD2119_POWER_CONTROL_1_DCT_SHIFT               12
#define DMD_SSD2119_POWER_CONTROL_1_BT_SHIFT                9
#define DMD_SSD2119_POWER_CONTROL_1_DC_SHIFT                4
#define DMD_SSD2119_POWER_CONTROL_1_AP_SHIFT                1

#define DMD_SSD2119_DISPLAY_CONTROL                         0x07
#define DMD_SSD2119_DISPLAY_CONTROL_PT1                     0x1000
#define DMD_SSD2119_DISPLAY_CONTROL_PT0                     0x0800
#define DMD_SSD2119_DISPLAY_CONTROL_VLE2                    0x0400
#define DMD_SSD2119_DISPLAY_CONTROL_VLE1                    0x0200
#define DMD_SSD2119_DISPLAY_CONTROL_SPT                     0x0100
#define DMD_SSD2119_DISPLAY_CONTROL_GON                     0x0020
#define DMD_SSD2119_DISPLAY_CONTROL_DTE                     0x0010
#define DMD_SSD2119_DISPLAY_CONTROL_CM                      0x0008
#define DMD_SSD2119_DISPLAY_CONTROL_D1                      0x0002
#define DMD_SSD2119_DISPLAY_CONTROL_D0                      0x0001

#define DMD_SSD2119_FRAME_CYCLE_CONTROL                     0x0B
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_NO_SHIFT            14
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SDT_SHIFT           12
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_EQ_SHIFT            8
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_SHIFT           6
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_1               0x0
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_2               0x1
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_4               0x2
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_DIV_8               0x3
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SDIV                0x0020
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_SRTN                0x0010
#define DMD_SSD2119_FRAME_CYCLE_CONTROL_RTN_SHIFT           0

#define DMD_SSD2119_POWER_CONTROL_2                         0x0C
#define DMD_SSD2119_POWER_CONTROL_2_VRC_SHIFT               0

#define DMD_SSD2119_POWER_CONTROL_3                         0x0D
#define DMD_SSD2119_POWER_CONTROL_3_VRH_SHIFT               0

#define DMD_SSD2119_POWER_CONTROL_4                         0x0E
#define DMD_SSD2119_POWER_CONTROL_4_VCOMG                   0x2000
#define DMD_SSD2119_POWER_CONTROL_4_VDV_SHIFT               8

#define DMD_SSD2119_GATE_SCAN_START_POSITION                0x0F

#define DMD_SSD2119_SLEEP_MODE_1                            0x10
#define DMD_SSD2119_SLEEP_MODE_1_SLP                        0x0001

#define DMD_SSD2119_ENTRY_MODE                              0x11
#define DMD_SSD2119_ENTRY_MODE_VSMODE                       0x8000
#define DMD_SSD2119_ENTRY_MODE_DFM_SHIFT                    13
#define DMD_SSD2119_ENTRY_MODE_DFM_65K                      0x3
#define DMD_SSD2119_ENTRY_MODE_DFM_262K                     0x2
#define DMD_SSD2119_ENTRY_MODE_DENMODE                      0x0800
#define DMD_SSD2119_ENTRY_MODE_WMODE                        0x0400
#define DMD_SSD2119_ENTRY_MODE_NOSYNC                       0x0200
#define DMD_SSD2119_ENTRY_MODE_DMODE                        0x0100
#define DMD_SSD2119_ENTRY_MODE_TY_SHIFT                     6
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_A                    0x0
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_B                    0x1
#define DMD_SSD2119_ENTRY_MODE_TY_TYPE_C                    0x2
#define DMD_SSD2119_ENTRY_MODE_ID1                          0x0020
#define DMD_SSD2119_ENTRY_MODE_ID0                          0x0010
#define DMD_SSD2119_ENTRY_MODE_AM                           0x0008

#define DMD_SSD2119_SLEEP_MODE_2                            0x12
#define DMD_SSD2119_SLEEP_MODE_2_DSLP                       0x2000
#define DMD_SSD2119_SLEEP_MODE_2_HVCI                       0x4000

#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL               0x15
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVDOT        0x0008
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVDEN        0x0004
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVHS         0x0002
#define DMD_SSD2119_GENERIC_INTERFACE_CONTROL_INVVS         0x0001

#define DMD_SSD2119_POWER_CONTROL_5                         0x1E
#define DMD_SSD2119_POWER_CONTROL_5_NOTP                    0x0080
#define DMD_SSD2119_POWER_CONTROL_5_VCM_SHIFT               0

#define DMD_SSD2119_ACCESS_DATA                             0x22

#define DMD_SSD2119_FRAME_FREQUENCY_CONTROL                 0x25
#define DMD_SSD2119_FRAME_FREQUENCY_CONTROL_OSC_SHIFT       12

#define DMD_SSD2119_VCOM_OTP_1                              0x28
#define DMD_SSD2119_VCOM_OTP_2                              0x29

#define DMD_SSD2119_GAMMA_1                                 0x30
#define DMD_SSD2119_GAMMA_1_PKP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_1_PKP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_2                                 0x31
#define DMD_SSD2119_GAMMA_2_PKP3_SHIFT                      8
#define DMD_SSD2119_GAMMA_2_PKP2_SHIFT                      0

#define DMD_SSD2119_GAMMA_3                                 0x32
#define DMD_SSD2119_GAMMA_3_PKP5_SHIFT                      8
#define DMD_SSD2119_GAMMA_3_PKP4_SHIFT                      0

#define DMD_SSD2119_GAMMA_4                                 0x33
#define DMD_SSD2119_GAMMA_4_PRP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_4_PRP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_5                                 0x34
#define DMD_SSD2119_GAMMA_5_PKN1_SHIFT                      8
#define DMD_SSD2119_GAMMA_5_PKN0_SHIFT                      0

#define DMD_SSD2119_GAMMA_6                                 0x35
#define DMD_SSD2119_GAMMA_6_PKN3_SHIFT                      8
#define DMD_SSD2119_GAMMA_6_PKN2_SHIFT                      0

#define DMD_SSD2119_GAMMA_7                                 0x36
#define DMD_SSD2119_GAMMA_7_PKN5_SHIFT                      8
#define DMD_SSD2119_GAMMA_7_PKN4_SHIFT                      0

#define DMD_SSD2119_GAMMA_8                                 0x37
#define DMD_SSD2119_GAMMA_8_PRN1_SHIFT                      8
#define DMD_SSD2119_GAMMA_8_PRN0_SHIFT                      0

#define DMD_SSD2119_GAMMA_9                                 0x3A
#define DMD_SSD2119_GAMMA_9_VRP1_SHIFT                      8
#define DMD_SSD2119_GAMMA_9_VRP0_SHIFT                      0

#define DMD_SSD2119_GAMMA_10                                0x3B
#define DMD_SSD2119_GAMMA_10_VRN1_SHIFT                     8
#define DMD_SSD2119_GAMMA_10_VRN0_SHIFT                     0

#define DMD_SSD2119_VERTICAL_SCROLL_CONTROL_1               0x41
#define DMD_SSD2119_VERTICAL_SCROLL_CONTROL_2               0x42

#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS                0x44
#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS_END_SHIFT      8
#define DMD_SSD2119_VERTICAL_RAM_ADDRESS_POS_START_SHIFT    0

#define DMD_SSD2119_HORIZONTAL_RAM_ADDRESS_START_POS        0x45
#define DMD_SSD2119_HORIZONTAL_RAM_ADDRESS_END_POS          0x46

#define DMD_SSD2119_FIRST_WINDOW_START                      0x48
#define DMD_SSD2119_FIRST_WINDOW_END                        0x49

#define DMD_SSD2119_SECOND_WINDOW_START                     0x4A
#define DMD_SSD2119_SECOND_WINDOW_END                       0x4B

#define DMD_SSD2119_SET_X_ADDRESS_COUNTER                   0x4E
#define DMD_SSD2119_SET_Y_ADDRESS_COUNTER                   0x4F

#endif
