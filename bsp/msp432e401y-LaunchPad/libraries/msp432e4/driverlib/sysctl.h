//*****************************************************************************
//
// sysctl.h - Prototypes for the system control driver.
//
// Copyright (c) 2005-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
//   Redistribution and use in source and binary forms, with or without
//   modification, are permitted provided that the following conditions
//   are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//*****************************************************************************

#ifndef __DRIVERLIB_SYSCTL_H__
#define __DRIVERLIB_SYSCTL_H__

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtlPeripheralPresent(), SysCtlPeripheralEnable(),
// SysCtlPeripheralDisable(), and SysCtlPeripheralReset() APIs as the
// ui32Peripheral parameter.  The peripherals in the fourth group (upper nibble
// is 3) can only be used with the SysCtlPeripheralPresent() API.
//
//*****************************************************************************
#define SYSCTL_PERIPH_ADC0      0xf0003800  // ADC 0
#define SYSCTL_PERIPH_ADC1      0xf0003801  // ADC 1
#define SYSCTL_PERIPH_CAN0      0xf0003400  // CAN 0
#define SYSCTL_PERIPH_CAN1      0xf0003401  // CAN 1
#define SYSCTL_PERIPH_COMP0     0xf0003c00  // Analog Comparator Module 0
#define SYSCTL_PERIPH_EMAC0     0xf0009c00  // Ethernet MAC0
#define SYSCTL_PERIPH_EPHY0     0xf0003000  // Ethernet PHY0
#define SYSCTL_PERIPH_EPI0      0xf0001000  // EPI0
#define SYSCTL_PERIPH_GPIOA     0xf0000800  // GPIO A
#define SYSCTL_PERIPH_GPIOB     0xf0000801  // GPIO B
#define SYSCTL_PERIPH_GPIOC     0xf0000802  // GPIO C
#define SYSCTL_PERIPH_GPIOD     0xf0000803  // GPIO D
#define SYSCTL_PERIPH_GPIOE     0xf0000804  // GPIO E
#define SYSCTL_PERIPH_GPIOF     0xf0000805  // GPIO F
#define SYSCTL_PERIPH_GPIOG     0xf0000806  // GPIO G
#define SYSCTL_PERIPH_GPIOH     0xf0000807  // GPIO H
#define SYSCTL_PERIPH_GPIOJ     0xf0000808  // GPIO J
#define SYSCTL_PERIPH_HIBERNATE 0xf0001400  // Hibernation module
#define SYSCTL_PERIPH_CCM0      0xf0007400  // CCM 0
#define SYSCTL_PERIPH_EEPROM0   0xf0005800  // EEPROM 0
#define SYSCTL_PERIPH_GPIOK     0xf0000809  // GPIO K
#define SYSCTL_PERIPH_GPIOL     0xf000080a  // GPIO L
#define SYSCTL_PERIPH_GPIOM     0xf000080b  // GPIO M
#define SYSCTL_PERIPH_GPION     0xf000080c  // GPIO N
#define SYSCTL_PERIPH_GPIOP     0xf000080d  // GPIO P
#define SYSCTL_PERIPH_GPIOQ     0xf000080e  // GPIO Q
#define SYSCTL_PERIPH_GPIOR     0xf000080f  // GPIO R
#define SYSCTL_PERIPH_GPIOS     0xf0000810  // GPIO S
#define SYSCTL_PERIPH_GPIOT     0xf0000811  // GPIO T
#define SYSCTL_PERIPH_I2C0      0xf0002000  // I2C 0
#define SYSCTL_PERIPH_I2C1      0xf0002001  // I2C 1
#define SYSCTL_PERIPH_I2C2      0xf0002002  // I2C 2
#define SYSCTL_PERIPH_I2C3      0xf0002003  // I2C 3
#define SYSCTL_PERIPH_I2C4      0xf0002004  // I2C 4
#define SYSCTL_PERIPH_I2C5      0xf0002005  // I2C 5
#define SYSCTL_PERIPH_I2C6      0xf0002006  // I2C 6
#define SYSCTL_PERIPH_I2C7      0xf0002007  // I2C 7
#define SYSCTL_PERIPH_I2C8      0xf0002008  // I2C 8
#define SYSCTL_PERIPH_I2C9      0xf0002009  // I2C 9
#define SYSCTL_PERIPH_LCD0      0xf0009000  // LCD 0
#define SYSCTL_PERIPH_ONEWIRE0  0xf0009800  // One Wire 0
#define SYSCTL_PERIPH_PWM0      0xf0004000  // PWM 0
#define SYSCTL_PERIPH_PWM1      0xf0004001  // PWM 1
#define SYSCTL_PERIPH_QEI0      0xf0004400  // QEI 0
#define SYSCTL_PERIPH_QEI1      0xf0004401  // QEI 1
#define SYSCTL_PERIPH_SSI0      0xf0001c00  // SSI 0
#define SYSCTL_PERIPH_SSI1      0xf0001c01  // SSI 1
#define SYSCTL_PERIPH_SSI2      0xf0001c02  // SSI 2
#define SYSCTL_PERIPH_SSI3      0xf0001c03  // SSI 3
#define SYSCTL_PERIPH_TIMER0    0xf0000400  // Timer 0
#define SYSCTL_PERIPH_TIMER1    0xf0000401  // Timer 1
#define SYSCTL_PERIPH_TIMER2    0xf0000402  // Timer 2
#define SYSCTL_PERIPH_TIMER3    0xf0000403  // Timer 3
#define SYSCTL_PERIPH_TIMER4    0xf0000404  // Timer 4
#define SYSCTL_PERIPH_TIMER5    0xf0000405  // Timer 5
#define SYSCTL_PERIPH_TIMER6    0xf0000406  // Timer 6
#define SYSCTL_PERIPH_TIMER7    0xf0000407  // Timer 7
#define SYSCTL_PERIPH_UART0     0xf0001800  // UART 0
#define SYSCTL_PERIPH_UART1     0xf0001801  // UART 1
#define SYSCTL_PERIPH_UART2     0xf0001802  // UART 2
#define SYSCTL_PERIPH_UART3     0xf0001803  // UART 3
#define SYSCTL_PERIPH_UART4     0xf0001804  // UART 4
#define SYSCTL_PERIPH_UART5     0xf0001805  // UART 5
#define SYSCTL_PERIPH_UART6     0xf0001806  // UART 6
#define SYSCTL_PERIPH_UART7     0xf0001807  // UART 7
#define SYSCTL_PERIPH_UDMA      0xf0000c00  // uDMA
#define SYSCTL_PERIPH_USB0      0xf0002800  // USB 0
#define SYSCTL_PERIPH_WDOG0     0xf0000000  // Watchdog 0
#define SYSCTL_PERIPH_WDOG1     0xf0000001  // Watchdog 1

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlLDODeepSleepSet()
// API as the ui32Voltage value, or returned by the SysCtlLDODeepSleepGet() API.
//
//*****************************************************************************
#define SYSCTL_LDO_0_90V        0x80000012  // LDO output of 0.90V
#define SYSCTL_LDO_0_95V        0x80000013  // LDO output of 0.95V
#define SYSCTL_LDO_1_00V        0x80000014  // LDO output of 1.00V
#define SYSCTL_LDO_1_05V        0x80000015  // LDO output of 1.05V
#define SYSCTL_LDO_1_10V        0x80000016  // LDO output of 1.10V
#define SYSCTL_LDO_1_15V        0x80000017  // LDO output of 1.15V
#define SYSCTL_LDO_1_20V        0x80000018  // LDO output of 1.20V

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlIntEnable(),
// SysCtlIntDisable(), and SysCtlIntClear() APIs, or returned in the bit mask
// by the SysCtlIntStatus() API.
//
//*****************************************************************************
#define SYSCTL_INT_BOR0         0x00000800  // VDD under BOR0
#define SYSCTL_INT_VDDA_OK      0x00000400  // VDDA Power OK
#define SYSCTL_INT_MOSC_PUP     0x00000100  // MOSC power-up interrupt
#define SYSCTL_INT_USBPLL_LOCK  0x00000080  // USB PLL lock interrupt
#define SYSCTL_INT_PLL_LOCK     0x00000040  // PLL lock interrupt
#define SYSCTL_INT_MOSC_FAIL    0x00000008  // Main oscillator failure int
#define SYSCTL_INT_BOR1         0x00000002  // VDD under BOR1
#define SYSCTL_INT_BOR          0x00000002  // Brown out interrupt

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlResetCauseClear()
// API or returned by the SysCtlResetCauseGet() API.
//
//*****************************************************************************
#define SYSCTL_CAUSE_HSRVREQ    0x00001000  // Hardware System Service Request
#define SYSCTL_CAUSE_HIB        0x00000040  // Hibernate reset
#define SYSCTL_CAUSE_WDOG1      0x00000020  // Watchdog 1 reset
#define SYSCTL_CAUSE_SW         0x00000010  // Software reset
#define SYSCTL_CAUSE_WDOG0      0x00000008  // Watchdog 0 reset
#define SYSCTL_CAUSE_BOR        0x00000004  // Brown-out reset
#define SYSCTL_CAUSE_POR        0x00000002  // Power on reset
#define SYSCTL_CAUSE_EXT        0x00000001  // External reset

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlBrownOutConfigSet()
// API as the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_BOR_RESET        0x00000002  // Reset instead of interrupting
#define SYSCTL_BOR_RESAMPLE     0x00000001  // Resample BOR before asserting

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlClockFreqSet() API as
// the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_CFG_VCO_240      0xF1000000  // VCO is 240 MHz
#define SYSCTL_CFG_VCO_160      0xF0000000  // VCO is 160 MHz
#define SYSCTL_USE_PLL          0x00000000  // System clock is the PLL clock
#define SYSCTL_USE_OSC          0x00003800  // System clock is the osc clock
#define SYSCTL_XTAL_5MHZ        0x00000000  // External crystal is 5MHz
#define SYSCTL_XTAL_6MHZ        0x00000040  // External crystal is 6MHz
#define SYSCTL_XTAL_8MHZ        0x00000080  // External crystal is 8MHz
#define SYSCTL_XTAL_10MHZ       0x000000C0  // External crystal is 10 MHz
#define SYSCTL_XTAL_12MHZ       0x00000100  // External crystal is 12 MHz
#define SYSCTL_XTAL_16MHZ       0x00000140  // External crystal is 16 MHz
#define SYSCTL_XTAL_18MHZ       0x00000180  // External crystal is 18.0 MHz
#define SYSCTL_XTAL_20MHZ       0x000001C0  // External crystal is 20.0 MHz
#define SYSCTL_XTAL_24MHZ       0x00000200  // External crystal is 24.0 MHz
#define SYSCTL_XTAL_25MHZ       0x00000240  // External crystal is 25.0 MHz
#define SYSCTL_OSC_MAIN         0x00000000  // Osc source is main osc
#define SYSCTL_OSC_INT          0x00000010  // Osc source is int. osc
#define SYSCTL_OSC_INT30        0x00000030  // Osc source is int. 30 KHz
#define SYSCTL_OSC_EXT32        0x80000038  // Osc source is ext. 32 KHz
#define SYSCTL_CFG_VCO_480      SYSCTL_CFG_VCO_240  // For backward compatibility
#define SYSCTL_CFG_VCO_320      SYSCTL_CFG_VCO_160  // For backward compatibility
//*****************************************************************************
//
// The following are values that can be passed to the
// SysCtlDeepSleepClockConfigSet() API as the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_DSLP_OSC_MAIN    0x00000000  // Osc source is main osc
#define SYSCTL_DSLP_OSC_INT     0x00000010  // Osc source is int. osc
#define SYSCTL_DSLP_OSC_INT30   0x00000030  // Osc source is int. 30 KHz
#define SYSCTL_DSLP_OSC_EXT32   0x00000070  // Osc source is ext. 32 KHz
#define SYSCTL_DSLP_PIOSC_PD    0x00000002  // Power down PIOSC in deep-sleep
#define SYSCTL_DSLP_MOSC_DPD    0x40000000  // Power down MOSC in deep-sleep

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlPIOSCCalibrate()
// API as the ui32Type parameter.
//
//*****************************************************************************
#define SYSCTL_PIOSC_CAL_AUTO   0x00000200  // Automatic calibration
#define SYSCTL_PIOSC_CAL_FACT   0x00000100  // Factory calibration
#define SYSCTL_PIOSC_CAL_USER   0x80000100  // User-supplied calibration

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlMOSCConfigSet() API
// as the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_MOSC_VALIDATE    0x00000001  // Enable MOSC validation
#define SYSCTL_MOSC_INTERRUPT   0x00000002  // Generate interrupt on MOSC fail
#define SYSCTL_MOSC_NO_XTAL     0x00000004  // No crystal is attached to MOSC
#define SYSCTL_MOSC_PWR_DIS     0x00000008  // Power down the MOSC.
#define SYSCTL_MOSC_LOWFREQ     0x00000000  // MOSC is less than 10MHz
#define SYSCTL_MOSC_HIGHFREQ    0x00000010  // MOSC is greater than 10MHz
#define SYSCTL_MOSC_SESRC       0x00000020  // Singled ended oscillator source.

//*****************************************************************************
//
// The following are values that can be passed to the SysCtlSleepPowerSet() and
// SysCtlDeepSleepPowerSet() APIs as the ui32Config parameter.
//
//*****************************************************************************
#define SYSCTL_LDO_SLEEP        0x00000200  // LDO in sleep mode
// (Deep Sleep Only)
#define SYSCTL_TEMP_LOW_POWER   0x00000100  // Temp sensor in low power mode
// (Deep Sleep Only)
#define SYSCTL_FLASH_NORMAL     0x00000000  // Flash in normal mode
#define SYSCTL_FLASH_LOW_POWER  0x00000020  // Flash in low power mode
#define SYSCTL_SRAM_NORMAL      0x00000000  // SRAM in normal mode
#define SYSCTL_SRAM_STANDBY     0x00000001  // SRAM in standby mode
#define SYSCTL_SRAM_LOW_POWER   0x00000003  // SRAM in low power mode

//*****************************************************************************
//
// Defines for the SysCtlResetBehaviorSet() and SysCtlResetBehaviorGet() APIs.
//
//*****************************************************************************
#define SYSCTL_ONRST_WDOG0_POR  0x00000030
#define SYSCTL_ONRST_WDOG0_SYS  0x00000020
#define SYSCTL_ONRST_WDOG1_POR  0x000000C0
#define SYSCTL_ONRST_WDOG1_SYS  0x00000080
#define SYSCTL_ONRST_BOR_POR    0x0000000C
#define SYSCTL_ONRST_BOR_SYS    0x00000008
#define SYSCTL_ONRST_EXT_POR    0x00000003
#define SYSCTL_ONRST_EXT_SYS    0x00000002

//*****************************************************************************
//
// Values used with the SysCtlVoltageEventConfig() API.
//
//*****************************************************************************
#define SYSCTL_VEVENT_VDDABO_NONE                                             \
                                0x00000000
#define SYSCTL_VEVENT_VDDABO_INT                                              \
                                0x00000100
#define SYSCTL_VEVENT_VDDABO_NMI                                              \
                                0x00000200
#define SYSCTL_VEVENT_VDDABO_RST                                              \
                                0x00000300
#define SYSCTL_VEVENT_VDDBO_NONE                                              \
                                0x00000000
#define SYSCTL_VEVENT_VDDBO_INT 0x00000001
#define SYSCTL_VEVENT_VDDBO_NMI 0x00000002
#define SYSCTL_VEVENT_VDDBO_RST 0x00000003

//*****************************************************************************
//
// Values used with the SysCtlVoltageEventStatus() and
// SysCtlVoltageEventClear() APIs.
//
//*****************************************************************************
#define SYSCTL_VESTAT_VDDBOR    0x00000040
#define SYSCTL_VESTAT_VDDABOR   0x00000010

//*****************************************************************************
//
// Values used with the SysCtlNMIStatus() API.
//
//*****************************************************************************
#define SYSCTL_NMI_MOSCFAIL     0x00010000
#define SYSCTL_NMI_TAMPER       0x00000200
#define SYSCTL_NMI_WDT1         0x00000020
#define SYSCTL_NMI_WDT0         0x00000008
#define SYSCTL_NMI_POWER        0x00000004
#define SYSCTL_NMI_EXTERNAL     0x00000001

//*****************************************************************************
//
// The defines for the SysCtlClockOutConfig() API.
//
//*****************************************************************************
#define SYSCTL_CLKOUT_EN        0x80000000
#define SYSCTL_CLKOUT_DIS       0x00000000
#define SYSCTL_CLKOUT_SYSCLK    0x00000000
#define SYSCTL_CLKOUT_PIOSC     0x00010000
#define SYSCTL_CLKOUT_MOSC      0x00020000

//*****************************************************************************
//
// The following defines are used with the SysCtlAltClkConfig() function.
//
//*****************************************************************************
#define SYSCTL_ALTCLK_PIOSC     0x00000000
#define SYSCTL_ALTCLK_RTCOSC    0x00000003
#define SYSCTL_ALTCLK_LFIOSC    0x00000004

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************
extern uint32_t SysCtlSRAMSizeGet(void);
extern uint32_t SysCtlFlashSizeGet(void);
extern uint32_t SysCtlFlashSectorSizeGet(void);
extern bool SysCtlPeripheralPresent(uint32_t ui32Peripheral);
extern bool SysCtlPeripheralReady(uint32_t ui32Peripheral);
extern void SysCtlPeripheralPowerOn(uint32_t ui32Peripheral);
extern void SysCtlPeripheralPowerOff(uint32_t ui32Peripheral);
extern void SysCtlPeripheralReset(uint32_t ui32Peripheral);
extern void SysCtlPeripheralEnable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralDisable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralSleepEnable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralSleepDisable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralDeepSleepEnable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralDeepSleepDisable(uint32_t ui32Peripheral);
extern void SysCtlPeripheralClockGating(bool bEnable);
extern void SysCtlIntRegister(void (*pfnHandler)(void));
extern void SysCtlIntUnregister(void);
extern void SysCtlIntEnable(uint32_t ui32Ints);
extern void SysCtlIntDisable(uint32_t ui32Ints);
extern void SysCtlIntClear(uint32_t ui32Ints);
extern uint32_t SysCtlIntStatus(bool bMasked);
extern void SysCtlLDODeepSleepSet(uint32_t ui32Voltage);
extern uint32_t SysCtlLDODeepSleepGet(void);
extern void SysCtlSleepPowerSet(uint32_t ui32Config);
extern void SysCtlDeepSleepPowerSet(uint32_t ui32Config);
extern void SysCtlReset(void);
extern void SysCtlSleep(void);
extern void SysCtlDeepSleep(void);
extern uint32_t SysCtlResetCauseGet(void);
extern void SysCtlResetCauseClear(uint32_t ui32Causes);
extern void SysCtlBrownOutConfigSet(uint32_t ui32Config,
                                    uint32_t ui32Delay);
extern void SysCtlDelay(uint32_t ui32Count);
extern void SysCtlMOSCConfigSet(uint32_t ui32Config);
extern uint32_t SysCtlPIOSCCalibrate(uint32_t ui32Type);
extern void SysCtlDeepSleepClockConfigSet(uint32_t ui32Div,
        uint32_t ui32Config);
extern uint32_t SysCtlClockFreqSet(uint32_t ui32Config,
                                   uint32_t ui32SysClock);
extern void SysCtlResetBehaviorSet(uint32_t ui32Behavior);
extern uint32_t SysCtlResetBehaviorGet(void);
extern void SysCtlClockOutConfig(uint32_t ui32Config, uint32_t ui32Div);
extern void SysCtlAltClkConfig(uint32_t ui32Config);
extern uint32_t SysCtlNMIStatus(void);
extern void SysCtlNMIClear(uint32_t ui32Status);
extern void SysCtlVoltageEventConfig(uint32_t ui32Config);
extern uint32_t SysCtlVoltageEventStatus(void);
extern void SysCtlVoltageEventClear(uint32_t ui32Status);
extern bool SysCtlVCOGet(uint32_t ui32Crystal, uint32_t *pui32VCOFrequency);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // __DRIVERLIB_SYSCTL_H__
