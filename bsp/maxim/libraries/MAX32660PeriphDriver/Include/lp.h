/**
 * @file    lp.h
 * @brief   Low power function prototypes and data types.
 */


/* ****************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2018-09-26 08:48:30 -0500 (Wed, 26 Sep 2018) $
 * $Revision: 38105 $
 *
 *************************************************************************** */
 
// Define to prevent redundant inclusion 
#ifndef _LP_H_
#define _LP_H_

/***** Includes *****/
#include "gpio.h"
#include "pwrseq_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @brief System reset0 enumeration. Used in SYS_PeriphReset0 function */
typedef enum {
    LP_OVR_0_9       = MXC_S_PWRSEQ_LP_CTRL_OVR_0_9V,         /**< Reset DMA */
    LP_OVR_1_0       = MXC_S_PWRSEQ_LP_CTRL_OVR_1_0V,         /**< Reset DMA */
    LP_OVR_1_1       = MXC_S_PWRSEQ_LP_CTRL_OVR_1_1V,         /**< Reset DMA */
} lp_ovr_t;

/**
 * @brief 	   Clears the low power wakeup flags
 */	
void LP_ClearWakeStatus(void);

/**
 * @brief      Enables power to RAM addresses 0x20010000-0x20017FFF.
 */
void LP_EnableSRAM3(void);

/**
 * @brief      Enables power to RAM addresses 0x20008000-0x2000FFFF.
 */
void LP_EnableSRAM2(void);

/**
 * @brief      Enables power to RAM addresses 0x20004000-0x20007FFF.
 */
void LP_EnableSRAM1(void);

/**
 * @brief      Enables power to RAM addresses 0x20000000-0x20003FFF.
 */
void LP_EnableSRAM0(void);

/**
 * @brief      Disables power to RAM addresses 0x20010000-0x20017FFF. The contents of the RAM are destroyed.
 */
void LP_DisableSRAM3(void);

/**
 * @brief      Disables power to RAM addresses 0x20008000-0x2000FFFF. The contents of the RAM are destroyed.
 */
void LP_DisableSRAM2(void);

/**
 * @brief      Disables power to RAM addresses 0x20004000-0x20007FFF. The contents of the RAM are destroyed.
 */
void LP_DisableSRAM1(void);

/**
 * @brief      Disables power to RAM addresses 0x20000000-0x20003FFF. The contents of the RAM are destroyed.
 */
void LP_DisableSRAM0(void);

/**
 * @brief      Places the instruction cache in light sleep mode. Data will be unavailable for read/write operations but will be retained.
 */
void LP_EnableICacheLightSleep(void);

/**
 * @brief      Places addresses 0x20010000 to 0x20017FFF of the RAM in light sleep mode. Data will be unavailable for read/write operations but will be retained.
 */
void LP_EnableSysRAM3LightSleep(void);

/**
 * @brief      Places addresses 0x20008000 to 0x2000FFFF of the RAM in light sleep mode. Data will be unavailable for read/write operations but will be retained.
 */
void LP_EnableSysRAM2LightSleep(void);

/**
 * @brief      Places addresses 0x20004000 to 0x20007FFF of the RAM in light sleep mode. Data will be unavailable for read/write operations but will be retained.
 */
void LP_EnableSysRAM1LightSleep(void);

/**
 * @brief      Places addresses 0x20000000 to 0x20003FFF of the RAM in light sleep mode. Data will be unavailable for read/write operations but will be retained.
 */
void LP_EnableSysRAM0LightSleep(void);

/**
 * @brief      Places the instruction cache in active mode.
 */
void LP_DisableICacheLightSleep(void);

/**
 * @brief      Places addresses 0x20010000 to 0x20017FFF of the RAM in active mode.
 */
void LP_DisableSysRAM3LightSleep(void);

/**
 * @brief      Places addresses 0x20008000 to 0x2000FFFF of the RAM in active mode.
 */
void LP_DisableSysRAM2LightSleep(void);

/**
 * @brief      Places addresses 0x20004000 to 0x20007FFF of the RAM in active mode.
 */
void LP_DisableSysRAM1LightSleep(void);

/**
 * @brief      Places addresses 0x20000000 to 0x20003FFF of the RAM in active mode.
 */
void LP_DisableSysRAM0LightSleep(void);

/**
 * @brief      Enables the selected GPIO port and its selected pins to wake up the device from any low power mode.  
 *             Call this function multiple times to enable pins on multiple ports.  This function does not configure
 *             the GPIO pins nor does it setup their interrupt functionality.
 * @param      wu_pins      The port and pins to configure as wakeup sources.  Only the gpio and mask fields of the
 *                          structure are used.  The func and pad fields are ignored.
 */
void LP_EnableGPIOWakeup(const gpio_cfg_t *wu_pins);

/**
 * @brief      Disables the selected GPIO port and its selected pins as a wake up source.  
 *             Call this function multiple times to disable pins on multiple ports.
 * @param      wu_pins      The port and pins to disable as wakeup sources.  Only the gpio and mask fields of the
 *                          structure are used.  The func and pad fields are ignored.
 */
void LP_DisableGPIOWakeup(const gpio_cfg_t *wu_pins);

/**
 * @brief      Enables the RTC alarm to wake up the device from any low power mode.  
 */
void LP_EnableRTCAlarmWakeup(void);

/**
 * @brief      Disables the RTC alarm from waking up the device.  
 */
void LP_DisableRTCAlarmWakeup(void);

/**
 * @brief      Places the device into SLEEP mode.  This function returns once any interrupt occurs. 
 * @note 	   LP_ClearWakeStatus should be called before this function, to avoid immediately waking up again
 */
void LP_EnterSleepMode(void);

/**
 * @brief      Places the device into DEEPSLEEP mode.  This function returns once an RTC or external interrupt occur. 
 * @note      LP_ClearWakeStatus should be called before this function, to avoid immediately waking up again
*/
void LP_EnterDeepSleepMode(void);

/**
 * @brief      Places the device into BACKUP mode.  CPU state is not maintained in this mode, so this function never returns.  
 *             Instead, the device will restart once an RTC or external interrupt occur. 
 * @note       LP_ClearWakeStatus should be called before this function, to avoid immediately waking up again
 */
void LP_EnterBackupMode(void);

/**
 * @brief      Places the device into Shutdown mode.  CPU state is not maintained in this mode, so this function never returns.  
 *             Instead, the device will restart once an RTC, USB wakeup, or external interrupt occur. 
 */
void LP_EnterShutDownMode(void);

/**
 * @brief      Set operating voltage and change the clock to match the new voltage. 
 * @param	   system reset configuration struct
 */
void LP_SetOperatingVoltage(lp_ovr_t ovr);

/**
 * @brief      Enables Data Retention to RAM addresses 0x20000000-0x20003FFF.
 */
void LP_EnableSRamRet0(void);

/**
 * @brief      Disables Data Retention to RAM addresses 0x20000000-0x20003FFF. 
 */
void LP_DisableSRamRet0(void);

/**
 * @brief      Enables Data Retention to RAM addresses 0x20004000-0x20007FFF.
 */
void LP_EnableSRamRet1(void);

/**
 * @brief      Disables Data Retention to RAM addresses 0x20004000-0x20007FFF.
 */
void LP_DisableSRamRet1(void);

/**
 * @brief      Enables Data Retention to RAM addresses 0x20008000-0x2000FFFF.
 */
void LP_EnableSRamRet2(void);

/**
 * @brief      Disables Data Retention to RAM addresses 0x20008000-0x2000FFFF.
 */
void LP_DisableSRamRet2(void);

/**
 * @brief      Enables Data Retention to RAM addresses 0x20010000-0x20017FFF.
 */
void LP_EnableSRamRet3(void);

/**
 * @brief      Disables Data Retention to RAM addresses 0x20010000-0x20017FFF.
 */
void LP_DisableSRamRet3(void);

/**
 * @brief      Enables Bypassing the hardware detection of an external supply on V CORE enables a faster wakeup time.
 */
void LP_EnableBlockDetect(void);

/**
 * @brief      Disables Bypassing the hardware detection of an external supply on V CORE enables a faster wakeup time
 */
void LP_DisableBlockDetect(void);

/**
 * @brief      RAM Retention Regulator Enable for BACKUP Mode
 */
void LP_EnableRamRetReg(void);

/**
 * @brief      RAM Retention Regulator Disabels for BACKUP Mode
 */
void LP_DisableRamRetReg(void);

/**
 * @brief      Enables Fast wake up from deepsleep 
 */
void LP_EnableFastWk(void);

/**
 * @brief      Disables Fast wake up from deepsleep
 */
void LP_DisableFastWk(void);

/**
 * @brief      Turns on band gap during deepsleep and backup mode. 
 */
void LP_EnableBandGap(void);

/**
 * @brief      Turns off band gap during deepsleep and backup mode.
 */
void LP_DisableBandGap(void);

/**
 * @brief     Enables signal for power on reset when the device is int DEEPSLEEP or BACKUP mode
 */
void LP_EnableVCorePORSignal(void);

/**
 * @brief     Disables signal for power on reset when the device is int DEEPSLEEP or BACKUP mode 
 */
void LP_DisableVCorePORSignal(void);

/**
 * @brief     Enables signal for power on reset when the device is int DEEPSLEEP or BACKUP mode
 */
void LP_EnableLDO(void);

/**
 * @brief     Disables signal for power on reset when the device is int DEEPSLEEP or BACKUP mode 
 */
void LP_DisableLDO(void);

/**
 * @brief     Enables V CORE Supply Voltage Monitor 
 */
void LP_EnableVCoreSVM(void);

/**
 * @brief     Disables V CORE Supply Voltage Monitor 
 */
void LP_DisableVCoreSVM(void);


/**
 * @brief     Enables VDDIO Power-On-Reset Monitor 
 */
void LP_EnableVDDIOPorMonitor(void);

/**
 * @brief     Disables VDDIO Power-On-Reset Monitor  
 */
void LP_DisableVDDIOPorMonitor(void);


#ifdef __cplusplus
}
#endif

#endif /* _LP_H_ */
