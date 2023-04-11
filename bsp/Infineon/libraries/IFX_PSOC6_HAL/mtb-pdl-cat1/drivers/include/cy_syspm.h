/***************************************************************************//**
* \file cy_syspm.h
* \version 5.91
*
* Provides the function definitions for the power management API.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*******************************************************************************/

/**
* \addtogroup group_syspm
* \{
* \defgroup group_syspm_pdcm            PDCM (Power Dependency Control Matrix)
* \defgroup group_syspm_ppu             PPU (Power Policy Unit)
* \defgroup group_syspm_btss            BTSS Host API(Bluetooth Sub System Host API)
* \} */

/**
* \addtogroup group_syspm
* \{
*
* Use the System Power Management (SysPm) driver to change power modes and
* reduce system power consumption in power sensitive designs.
*
* The functions and other declarations used in this driver are in cy_syspm.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* For multi-CPU devices, this library allows you to individually enter low power
* modes for each CPU.
*
* This document contains the following topics:
*
* * \ref group_syspm_power_modes
* * \ref group_syspm_system_power_modes
*   - \ref group_syspm_switching_into_ulp
*     - \ref group_syspm_ulp_limitations
*   - \ref group_syspm_switching_into_lp
*     - \ref group_syspm_lp_limitations
*   - \ref group_syspm_switching_into_sleep
*   - \ref group_syspm_switching_into_lpactivelpsleep
*   - \ref group_syspm_switching_into_deepsleep
*   - \ref group_syspm_switching_into_deepsleep-ram
*   - \ref group_syspm_switching_into_deepsleep-off
*   - \ref group_syspm_wakingup_from_sleep_deepsleep
*   - \ref group_syspm_switching_into_hibernate
*   - \ref group_syspm_wakingup_from_hibernate
* * \ref group_syspm_system_reg_curr_mode
*   - \ref group_syspm_system_set_min_reg_curr_mode
*   - \ref group_syspm_system_set_normal_reg_curr_mode
* * \ref group_syspm_migration_guide_for_syspm_4_0
* * \ref group_syspm_managing_pmic
* * \ref group_syspm_managing_backup_domain
* * \ref group_syspm_cb
*   - \ref group_syspm_cb_example
*   - \ref group_syspm_cb_config_consideration
*     - \ref group_syspm_cb_parameters
*     - \ref group_syspm_cb_structures
*     - \ref group_syspm_cb_function_implementation
*     - \ref group_syspm_cb_flow
*     - \ref group_syspm_cb_registering
*     - \ref group_syspm_cb_unregistering
* * \ref group_syspm_definitions
*
* \section group_syspm_section_configuration Configuration Considerations
* \subsection group_syspm_power_modes Power Modes
*
* <b>A) CAT1A Architecture</b>:
*
* 1) PSoC 6 MCUs support four system and three CPU power modes.
* These power modes are intended to minimize average power consumption
* in an application.
*
* System power modes:
* * <b>Low Power</b> - All peripheral and CPU power modes
*   are available to be used at maximum device frequency and current
*   consumption.
* * <b>Ultra Low Power</b> - All peripheral and
*   CPU power modes are available, but the frequency and current consumption
*   are limited to a device specific number.
* * <b>Deep Sleep</b> - Device and I/O states is retained. Low-frequency
*   peripherals are available. Both CPUs are in CPU Deep Sleep power mode.
* * <b>Hibernate</b> - The device and I/O states are frozen and the device
*   resets on wakeup.
*
* CPU power modes(standard ARM defined power modes, supported by
*   the ARM CPUs and ISA):
*
* * <b>Active</b>
* * <b>Sleep</b>
* * <b>Deep Sleep</b>
*
* <b>B) CAT1B Architecture</b>:
*
* 1) CAT1B devices supports below Power Modes:
*
* * <b>ACTIVE, SLEEP </b> - standard ARM defined power modes, supported by
*   the ARM CPUs and ISA.
* * <b>LPACTIVE/LPSLEEP</b> - are low power profiles implemented as register
*   configurations within ACTIVE/SLEEP modes.
* * <b>DEEPSLEEP </b> - a lower power mode where high-frequency clocks are
*   disabled.  Most register state is retained and the platform supports saving
*   a configurable amount of SRAM state.
* * <b>DEEPSLEEP-RAM </b> -  a lower mode than DEEPSLEEP that keeps DeepSleep
*   peripherals running, but on wakeup the CPU (and most peripherals) go
*   through a reset.  A configurable amount of system RAM is retained.
* * <b>DEEPSLEEP-OFF </b> -   similar to DEEPSLEEP-RAM but does not retain
*   system RAM.
* * <b>HIBERNATE </b> -   is an even lower power mode than DEEPSLEEP-OFF, but
*   on wakeup the CPU (and almost all peripherals) go through a full reset.
*   DeepSleep peripherals do not operate in HIBERNATE.
* * <b>XRES </b> - occurs when an external reset is applied, either XRES or
*   alternate XRES (AXRES).  It is also considered a power mode with a current
*   target spec.
* * <b>OFF </b> - state simply represents the state of the part with no power
*   applied to it.
*
* CAT1B adopts the <b>ARM Power Control Architecture</b>.Below are
* key changes in the power system:
*
* * CAT1B supports three flavors of DEEPSLEEP: the original one, and two new
* ones called DEEPSLEEP-RAM and DEEPSLEEP-OFF.
* * SRSS implements an ARM Power Policy Unit (PPU) that provides the software
* interface to power mode control for VCCACT_PD.The PPU interacts with a
* Power Control State Machine (PSCM) that interfaces with the core SRSS
* to enter/exit DEEPSLEEP*.
* * SRSS implements a Power Dependency Control Matrix (PDCM) that allows hardware
* and software to specify dependencies between power domains.
*
* <b>C) CAT1C Architecture</b>:
*
* 1) CAT1C MCU's can operate in different power modes that are intended to minimize
* the average power consumption in an application. The power modes supported by
* CATC devices in the order of decreasing power consumption are:
* * <b>ACTIVE </b> - all peripherals are available
* * <b>Low-Power Active (LPACTIVE) profile </b>- Low-power profile of Active mode where
* all peripherals including the CPU are available, but with limited capability
* * <b>SLEEP </b> - all peripherals except the CPU are available
* * <b>Low-Power Sleep (LPSLEEP) profile </b>- Low-power profile of Sleep mode where
* all peripherals except the CPU are available, but with limited capability
* * <b>DEEPSLEEP </b>- only low-frequency peripherals are available
* * <b>HIBERNATE </b>- the device and I/O states are frozen and the device resets on wakeup
* * <b>XRES </b>- the device enters this state when the XRES_L pin is asserted
*
* Active, Sleep, and DeepSleep are standard Arm-defined power modes supported by
* the Arm CPUs and Instruction Set Architecture (ISA).
* LPACTIVE and LPSLEEP are similar to Active and Sleep modes, respectively; however,
* the high-current components are either frequency or current limited or turned off.
* Hibernate mode and XRES state are the lowest power mode/state that the CATC devices
* can be in.
*
* \subsection group_syspm_system_power_modes System Power Modes
* * <b>LP</b> - In this mode, code is executed and all logic and
*   memories are powered. Firmware may disable/reduce clocks for specific
*   peripherals and power down specific analog power domains.
*
* * <b>ULP</b> - This power mode is like LP mode, but
*   with clock restrictions and limited/slower peripherals to achieve lower
*   current consumption. Refer to \ref group_syspm_switching_into_ulp in
*   Configuration considerations.
*
* * <b>LPACTIVE/LPSLEEP</b> - low power profiles implemented as register
*   configurations within ACTIVE/SLEEP modes.Refer to
*   \ref group_syspm_switching_into_lpactivelpsleep in Configuration considerations.
*
* * <b>DEEPSLEEP</b> - Is a lower power mode where high-frequency clocks are
*   disabled. Refer to \ref group_syspm_switching_into_deepsleep in
*   Configuration considerations. Deep-sleep-capable peripherals are available.
*   A normal wakeup from Deep Sleep returns to either system LP or ULP mode,
*   depending on the previous state and programmed behavior for the configured
*   wakeup interrupt. Likewise, a debug wakes up from system Deep Sleep and
*   woken CPU returns to CPU Sleep. Refer
*   to \ref group_syspm_wakingup_from_sleep_deepsleep in Configuration
*   considerations.
*
* * <b>DEEPSLEEP-RAM</b> - a lower mode than DEEPSLEEP that keeps DeepSleep
*   peripherals running, but on wakeup the CPU (and most peripherals) go through
*   a reset. A configurable amount of system RAM is retained.Refer to
*   \ref group_syspm_switching_into_deepsleep-ram in Configuration considerations.
*   Refer to \ref group_syspm_wakingup_from_sleep_deepsleep in Configuration
*   considerations.
*
* * <b>DEEPSLEEP-OFF</b> -  similar to DEEPSLEEP-RAM but does not retain system RAM.
*   Refer to \ref group_syspm_switching_into_deepsleep-off in Configuration considerations.
*   Refer to \ref group_syspm_wakingup_from_sleep_deepsleep in Configuration
*   considerations.
*
* * <b>Hibernate</b> - Is the lowest power mode that is entered from
*   firmware. Refer to \ref group_syspm_switching_into_hibernate in
*   Configuration considerations. On wakeup the CPU(s) and all peripherals
*   go through a full reset. The I/O's state is frozen so that the
*   output driver state is held in system Hibernate. Note that in this mode,
*   the CPU(s) and all peripherals lose their states, so the system and firmware
*   reboot on a wakeup event. Backup memory (if present) can be used to store
*   limited system state for use on the next reboot. Refer to
*   \ref group_syspm_wakingup_from_hibernate in Configuration considerations.
*
* \warning * Above is list of all the System Power modes in general, a device
* support subset of the above System Power modes.Please refer to TRM for more information.
*
* \subsubsection group_syspm_switching_into_lp Switching the System into Low Power
* To set system LP mode you need to set LP voltage for the active core
* regulator:
* * If active core regulator is the LDO, call:
*   \code{.c}
*   Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_LP);
*   \endcode
* * If active core regulator is the Buck, call:
*   \code{.c}
*   Cy_SysPm_BuckSetVoltage1(CY_SYSPM_BUCK_OUT1_VOLTAGE_LP)
*   \endcode
*
* After switching into system LP mode, the operating frequency and current
* consumption may now be increased up to \ref group_syspm_lp_limitations.
* The wait states for flash may be changed to increase device performance by
* calling SysLib function Cy_SysLib_SetWaitStates(true, hfClkFreqMz), where
* hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* \subsubsection group_syspm_lp_limitations LP Limitations
* When the system is in LP mode, the core regulator voltage is set to
* <b>1.1 V (nominal)</b> and the following limitations must be met:
*
*   - The maximum operating frequency for all Clk_HF paths must not exceed
*     <b>150 MHz*</b>, and peripheral and slow clock must
*     not exceed <b>100 MHz *</b>
*
*   - The total current consumption must be less than or equal to
*     <b>250 mA *</b>
*
* \warning * - Numbers shown are approximate and real limit values may be
* different because they are device specific. You should refer to the device
* datasheet for exact values of maximum frequency and current in system LP mode.
*
* \subsubsection group_syspm_switching_into_ulp Switching the System into Ultra Low Power
* Before switching into system ULP mode, ensure that the device meets
* \ref group_syspm_ulp_limitations. Decrease the clock frequencies,
* and slow or disable peripherals. Also ensure that appropriate wait state
* values are set for the flash. Flash wait states can be set by calling
* SysLib function Cy_SysLib_SetWaitStates(true, hfClkFreqMz), where hfClkFreqMz
* is the frequency of HfClk0 in MHz.
*
* After the \ref group_syspm_ulp_limitations are met and appropriate wait
* states are set, you must set ULP voltage for the active core regulator:
* * If active core regulator is the LDO Core Voltage Regulator, call
* Cy_SysPm_LdoSetVoltage(CY_SYSPM_LDO_VOLTAGE_ULP)
* * If active core regulator is the Buck Core Voltage Regulator, then call
* Cy_SysPm_BuckSetVoltage1(CY_SYSPM_BUCK_OUT1_VOLTAGE_ULP)
*
* \subsubsection group_syspm_ulp_limitations ULP Limitations
* When the system is in ULP mode the core regulator voltage is set to <b>0.9 V
* (nominal)</b> and the following limitations must be meet:
*
*   - The maximum operating frequency for all Clk_HF paths must not exceed
*     <b>50 MHz *</b>, whereas the peripheral and slow clock must not exceed
*     <b>25 MHz *</b>.
*
*   - The total current consumption must be less than or equal
*     to <b>20 mA*</b>
*
*   - the flash write operations are prohibited. The flash works in the
*     Read-only operation. If Write operations are required, you must switch to
*     the system LP mode.
*
* \warning * - Numbers shown are approximate and real limit values may be
* different because they are device specific. You should refer to the device
* datasheet for exact values of maximum frequency and current in system
* ULP mode.
*
* \subsubsection group_syspm_switching_into_lpactivelpsleep Switching the System into LPACTIVE/LPSLEEP
* Call Cy_SysPm_SystemLpActiveEnter() to enter LPACTIVE/LPSLEEP mode and
* Cy_SysPm_SystemLpActiveExit() to exit.
*
* \subsubsection group_syspm_switching_into_sleep Switching CPU into Sleep
* For multi-CPU devices, the Cy_SysPm_CpuEnterSleep() switches only the CPU
* that calls the function into the CPU Sleep power mode.
*
* All pending interrupts must be cleared before the CPU is put into a
* Sleep mode, even if they are masked.
*
* The CPU event register can be set in the past, for example, as a result of
* internal system calls. So an old event can cause the CPU to not enter
* Sleep mode upon WFE(). Therefore usually the WFE() is used in an idle loop or
* polling loop as it might or might not cause entering of CPU Sleep mode. If
* the idle loop or polling loop is not used, then it is recommended to use
* WFI() instruction.
*
* \subsubsection group_syspm_switching_into_deepsleep Switching the System or CPU into Deep Sleep
* For multi-CPU devices, the Cy_SysPm_CpuEnterDeepSleep() function switches
* only the CPU that calls the function into the CPU Deep Sleep power mode.
* To set the whole system into Deep Sleep power mode, ensure that all CPUs call
* the Cy_SysPm_CpuEnterDeepSleep() function.
*
* \warning * For CAT1B devices we need to call Cy_SysPm_SetDeepSleepMode() function with
* appropriate type of deepsleep as parameter before calling Cy_SysPm_CpuEnterDeepSleep()
* function.
*
* \subsubsection group_syspm_switching_into_deepsleep-ram Switching the System or CPU into Deep Sleep-RAM
* For multi-CPU devices, the Cy_SysPm_CpuEnterDeepSleep() function switches
* only the CPU that calls the function into the CPU DEEPSLEEP-RAM power mode.
* To set the whole system into Deep Sleep power mode, ensure that all CPUs call
* the Cy_SysPm_CpuEnterDeepSleep() function.
*
* \warning * For CAT1B devices we need to call Cy_SysPm_SetDeepSleepMode() function with
* appropriate type of deepsleep as parameter before calling Cy_SysPm_CpuEnterDeepSleep()
* function.
*
* \subsubsection group_syspm_switching_into_deepsleep-off Switching the System or CPU into Deep Sleep-OFF
* For multi-CPU devices, the Cy_SysPm_CpuEnterDeepSleep() function switches
* only the CPU that calls the function into the CPU DEEPSLEEP-OFF power mode.
* To set the whole system into Deep Sleep power mode, ensure that all CPUs call
* the Cy_SysPm_CpuEnterDeepSleep() function.
*
* Note:- For CAT1B devices we need to call Cy_SysPm_SetDeepSleepMode() function with
* appropriate type of deepsleep as parameter before calling Cy_SysPm_CpuEnterDeepSleep()
* function.
*
* There are situations when the system does not switch into the Deep Sleep
* power mode immediately after the last CPU calls Cy_SysPm_CpuEnterDeepSleep().
* The system will switch into Deep Sleep mode automatically a short time later,
* after the low power circuits are ready to switch into Deep Sleep. Refer to
* the Cy_SysPm_CpuEnterDeepSleep() description for more detail.
*
* All pending interrupts must be cleared before the system is put into a
* Deep Sleep mode, even if they are masked.
*
* The CPU event register can be set in the past, for example, as a result of
* internal system calls. So an old event can cause the CPU to not enter Deep
* Sleep mode upon WFE(). Therefore usually the WFE() is used in an idle loop or
* polling loop as it might or might not cause entering of CPU Deep Sleep mode.
* If the idle loop or polling loop is not used, then it is recommended to use
* WFI() instruction.
*
* For single-CPU devices, SysPm functions that return the status of the
* unsupported CPU always return CY_SYSPM_STATUS_<CPU>_DEEPSLEEP.
*
* \subsubsection group_syspm_wakingup_from_sleep_deepsleep Waking Up from Sleep or Deep Sleep
* For Arm-based devices, an interrupt is required for the CPU to wake up.
* For multi-CPU devices, one CPU can wake up the other CPU by sending the
* event instruction. Use the Cy_SysPm_CpuSendWakeupEvent() function.
*
* \subsubsection group_syspm_switching_into_hibernate Switching System to Hibernate
* If you call Cy_SysPm_SystemEnterHibernate() from either CPU, the system will
* be switched into the Hibernate power mode directly, because there is no
* handshake between CPUs.
*
* \subsubsection group_syspm_wakingup_from_hibernate Waking Up from Hibernate
*
* The system can wake up from Hibernate mode by configuring the following wakeup
* sources:
* - Wakeup pin
* - LP Comparator
* - RTC alarm
* - WDT interrupt
*
* Wakeup is supported from device specific pin(s) with programmable polarity.
* Additionally, unregulated peripherals can wake the system under some
* conditions. For example, a low power comparator can wake the system by
* comparing two external voltages, but does not support comparison to an
* internally-generated voltage. The backup power domain remains functional, and
* if present it can schedule an alarm to wake the system from Hibernate using
* the RTC. Alternatively, the Watchdog Timer (WDT) can be configured to wake-up
* the system by WDT interrupt. Refer to \ref Cy_SysPm_SetHibernateWakeupSource()
* for more detail.
*
* \subsection group_syspm_system_reg_curr_mode System Regulator Current Mode
* In addition to system ULP and LP modes, the five different resource
* power settings can be configured to reduce current consumption:
* -# <b>Linear regulator low power mode</b>. Can be used only if core current
*    is below the LDO regulator LP threshold.
* -# <b>POR/BOD circuit low power mode</b>. Requires compatible power supply
*    stability due to stability increase response time.
* -# <b>Bandgap reference circuits low power mode</b> (turns on Deep Sleep
*    Bandgap). Requires design to accept reduced Vref accuracy. Active ref can
*    be turned off after this feature is enabled.
* -# <b>Reference buffer circuit low power mode</b>. Requires design to accept
*    reduced Vref accuracy.
* -# <b>Current reference circuit low power mode</b>. Require design to accept
*    reduced Iref accuracy.
*
* These five sub features can modify both system LP or ULP modes as they are
* independent from LP/ULP settings.
* When all five sub features are set to their low power modes, the system
* operates in regulator minimum current mode. In regulator minimum current mode,
* the system current consumption is limited to a device-specific value. Refer to
* the device datasheet for the exact current consumption value in regulator
* minimum current mode.
*
* When all five sub features are set to their normal mode, the system operates
* in regulator normal current mode. When regulator normal current mode is set,
* the system may operate at device maximum current.
*
* \subsection group_syspm_system_set_min_reg_curr_mode Setting Minimum System Regulator Current Mode
*
* Before setting the regulator minimum current mode ensure that current limits
* are be met. After current limits are met, call the
* Cy_SysPm_SystemSetMinRegulatorCurrent() function.
*
* \subsection group_syspm_system_set_normal_reg_curr_mode Setting Normal System Regulator Current Mode
*
* To set regulator normal current mode, call the
* Cy_SysPm_SystemSetNormalRegulatorCurrent() function. After the function call,
* the current limits can be increased to a maximum current, depending on what
* system power mode is set: LP or ULP.
*
* \subsection group_syspm_managing_pmic Managing PMIC
*
* The SysPm driver also provides an API to configure the internal power
* management integrated circuit (PMIC) controller for an external PMIC that
* supplies Vddd. Use the API to enable the internal PMIC controller output that
* is routed to pmic_wakeup_out pin, and configure the polarity of the PMIC
* controller input (pmic_wakeup_in) that is used to wake up the PMIC.
*
* The PMIC controller is automatically enabled when:
* * The PMIC is locked by a call to Cy_SysPm_PmicLock()
* * The configured polarity of the PMIC input and the polarity driven to
*   pmic_wakeup_in pin matches.
*
* Because a call to Cy_SysPm_PmicLock() automatically enables the PMIC
* controller, the PMIC can remain disabled only when it is unlocked. See Cy_SysPm_PmicUnlock()
* for more detail.
*
* Use Cy_SysPm_PmicIsLocked() to read the current PMIC lock status.
*
* To enable the PMIC, use these functions in this order:
* \code{.c}
* Cy_SysPm_PmicUnlock();
* Cy_SysPm_PmicEnable();
* Cy_SysPm_PmicLock();
* \endcode
*
* To disable the PMIC controller, unlock the PMIC. Then call
* Cy_SysPm_PmicDisable() with the inverted value of the current active state of
* the pmic_wakeup_in pin.
* For example, assume the current state of the pmic_wakeup_in pin is active low.
* To disable the PMIC controller, call these functions in this order:
* \code{.c}
* Cy_SysPm_PmicUnlock();
* Cy_SysPm_PmicDisable(CY_SYSPM_PMIC_POLARITY_HIGH);
* \endcode
* Note that you do not call Cy_SysPm_PmicLock(), because that automatically
* enables the PMIC.
*
* While disabled, the PMIC controller is automatically enabled when the
* pmic_wakeup_in pin state is changed into a high state.
*
* To disable the PMIC controller output, call these functions in this order:
* Cy_SysPm_PmicUnlock();
* Cy_SysPm_PmicDisableOutput();
*
* Do not call Cy_SysPm_PmicLock() (which automatically enables the PMIC
* controller output).
*
* When disabled, the PMIC controller output is enabled when the PMIC is locked,
* or by calling Cy_SysPm_PmicEnableOutput().
*
* \subsection group_syspm_managing_backup_domain Managing the Backup Domain
* The SysPm driver provide functions to:
*
* * Configure Supercapacitor charging
* * Select power supply source (Vbackup or Vddd) for Vddbackup
* * Measure Vddbackup using the ADC
*
* Refer to the \ref group_syspm_functions_backup functions for more detail.
*
* \subsection group_syspm_cb SysPm Callbacks
* The SysPm driver handles low power callbacks declared in the application.
*
* If there are no callbacks registered, the device executes the power mode
* transition. However, frequently your application firmware must make
* modifications for low power mode. For example, you may need to disable a
* peripheral, or ensure that a message is not being transmitted or received.
*
* To enable this, the SysPm driver implements a callback mechanism. When a lower
* power mode transition is about to take place (either entering or exiting
* \ref group_syspm_system_power_modes), the registered callbacks for that
* transition are called.
*
* The SysPm driver organizes all the callbacks into a linked list. While
* entering a low power mode, SysPm goes through that linked list from first to
* last, executing the callbacks one after another. While exiting low power mode,
* SysPm goes through that linked list again, but in the opposite direction from
* last to first. This ordering supports prioritization of callbacks relative to
* the transition event.
*
* For example, the picture below shows three callback structures organized into
* a linked list: myDeepSleep1, myDeepSleep2, myDeepSleep3 (represented with the
* \ref cy_stc_syspm_callback_t configuration structure). Each structure
* contains, among other fields, the address of the callback function. The code
* snippets below set this up so that myDeepSleep1 is called first when entering
* the low power mode. This also means that myDeepSleep1 will be the last one to
* execute when exiting the low power mode.
*
* The callback structures after registration:
* \image html syspm_register_eq.png
*
* Your application must register each callback, so that SysPm can execute it.
* Upon registration, the linked list is built by the SysPm driver. Notice
* the &myDeepSleep1 address in the myDeepSleep1
* \ref cy_stc_syspm_callback_t structure. This is filled in by the SysPm driver,
* when you register myDeepSleep1. The cy_stc_syspm_callback_t.order element
* defines the order of their execution by the SysPm driver.
* Call \ref Cy_SysPm_RegisterCallback() to register each callback function.
*
* A callback function is typically associated with a particular driver that
* handles the peripheral. So the callback mechanism enables a peripheral to
* prepare for a low power mode (for instance, shutting down the analog part);
* or to perform tasks while exiting a low power mode (like enabling the analog
* part again).
*
* With the callback mechanism you can prevent switching into a low power mode if
* a peripheral is not ready. For example, driver X is in the process of
* receiving a message. In the callback function implementation simply return
* CY_SYSPM_FAIL in a response to CY_SYSPM_CHECK_READY.
*
* If success is returned while executing a callback, the SysPm driver calls the
* next callback and so on to the end of the list. If at some point a callback
* returns CY_SYSPM_FAIL in response to the CY_SYSPM_CHECK_READY step, all the
* callbacks that have already executed are executed in reverse order, with the
* CY_SYSPM_CHECK_FAIL mode parameter. This allows each callback to know that
* entering the low power mode has failed. The callback can then undo whatever it
* did to prepare for low power mode, if required. For example, if the driver X
* callback shut down the analog part, it can re-enable the analog part.
*
* Let's switch to an example explaining the implementation, setup, and
* registration of three callbacks (myDeepSleep1, myDeepSleep2, myDeepSleep2) in
* the application. The \ref group_syspm_cb_config_consideration are provided
* after the \ref group_syspm_cb_example.
*
* \subsection group_syspm_cb_example SysPm Callbacks Example
*
* The following code snippets demonstrate how use the SysPm callbacks mechanism.
* We will build the prototype for an application that registers
* three callback functions:
*    -# myDeepSleep1 - Handles CPU Deep Sleep.
*    -# myDeepSleep2 - Handles CPU Deep Sleep and is associated with peripheral
*       HW1_address (see <a href="..\..\pdl_user_guide.pdf">PDL Design</a>
*       section to learn about the base hardware address).
*    -# myDeepSleep3 - Handles entering and exiting system Deep Sleep and is
*       associated with peripheral HW2_address.
*
* We set things up so that the myDeepSleep1 and myDeepSleep2 callbacks do
* nothing while entering the low power mode (skip on
* CY_SYSPM_SKIP_BEFORE_TRANSITION -
* see \ref group_syspm_cb_function_implementation in
* \ref group_syspm_cb_config_consideration).
* Skipping the actions while entering low power might be useful if you need
* to save time while switching low power modes. This is because the callback
* function with a skipped mode is not even called avoiding the call and return
* overhead.
*
* Let's first declare the callback functions. Each gets the pointer to the
* \ref cy_stc_syspm_callback_params_t structure as the argument.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Func_Declaration
*
* Now we setup the \ref cy_stc_syspm_callback_params_t structures that we will
* pass to the callback functions. Note that for the myDeepSleep2 and
* myDeepSleep3 callbacks we also pass pointers to the peripherals related to
* that callback (see <a href="..\..\pdl_user_guide.pdf">PDL Design</a> section
* to learn about base hardware addresses).
* The configuration considerations related to this structure are described
* in \ref group_syspm_cb_parameters in \ref group_syspm_cb_config_consideration.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Params_Declaration
*
* Now we setup the actual callback configuration structures. Each of these
* contains, among the other fields, the address of the
* \ref cy_stc_syspm_callback_params_t we just set up. We will use the callback
* configuration structures later in the code to register the callbacks in the
* SysPm driver. Again, we set things up so that the myDeepSleep1 and
* myDeepSleep2 callbacks do nothing while entering the low power mode
* (skip on CY_SYSPM_SKIP_BEFORE_TRANSITION) - see
* \ref group_syspm_cb_function_implementation in
* \ref group_syspm_cb_config_consideration.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Structure_Declaration
*
* Note that in each case the last two fields are NULL. These are fields used by
* the SysPm driver to set up the linked list of callback functions.
*
* The callback structures are now defined and allocated in the user's
* memory space:
* \image html syspm_before_registration.png
*
* Now we implement the callback functions. See
* \ref group_syspm_cb_function_implementation in
* \ref group_syspm_cb_config_consideration for the instructions on how the
* callback functions should be implemented.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Func_Implementation
*
* Finally, we register the callbacks so that the SysPm driver knows about them.
* The order in which the callbacks will be called depends upon the order in
* which the callbacks are registered. If there are no callbacks registered,
* the device just executes the power mode transition.
*
* Callbacks that reconfigure global resources, such as clock frequencies, should
* be registered last. They then modify global resources as the final step before
* entering the low power mode, and restore those resources first, as the system
* returns from low power mode.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_RegisterCallback
*
* We are done configuring three callbacks. Now the SysPm driver will execute the
* callbacks appropriately whenever there is a call to a power mode transition
* function: \ref Cy_SysPm_CpuEnterSleep(), \ref Cy_SysPm_CpuEnterDeepSleep(),
* \ref Cy_SysPm_SystemEnterUlp(), \ref Cy_SysPm_SystemEnterLp(), and
* \ref Cy_SysPm_SystemEnterHibernate().
* \note On a wakeup from hibernate the device goes through a reset, so the
* callbacks with CY_SYSPM_AFTER_TRANSITION are not executed. Refer to
* \ref Cy_SysPm_SystemEnterHibernate() for more detail.
*
* Refer to \ref group_syspm_cb_unregistering in
* \ref group_syspm_cb_config_consideration to learn what to do if you need to
* remove the callback from the linked list. You might want to unregister the
* callback for debug purposes.
*
* Refer to \ref group_syspm_cb_flow in \ref group_syspm_cb_config_consideration
* to learn about how the SysPm processes the callbacks.
*
* \subsection group_syspm_cb_config_consideration Callback Configuration Considerations
*
* \subsubsection group_syspm_cb_parameters Callback Function Parameters
*
* The <b>callbackParams</b> parameter of the callback function is a
* \ref cy_stc_syspm_callback_params_t structure. The second parameter
* (<b>mode</b>) is for internal use. In the example code we used a
* dummy value CY_SYSPM_CHECK_READY to eliminate compilation errors associated
* with the enumeration. The driver sets the <b>mode</b> field to the correct
* value when calling the callback functions (the mode is referred to as step in
* the \ref group_syspm_cb_function_implementation). The callback function reads
* the value and executes code based on the mode set by the SysPm driver.
* The <b>base</b> and <b>context</b> fields are optional and can be NULL.
* Some drivers require a base hardware address and context to store information
* about the mode transition. If your callback routine requires access to the
* driver registers or context, provide those values
* (see <a href="..\..\pdl_user_guide.pdf">PDL Design</a> section
* to learn about Base Hardware Address). Be aware of MISRA warnings if these
* parameters are NULL.
*
* \subsubsection group_syspm_cb_structures Callback Function Structure
* For each callback, provide a \ref cy_stc_syspm_callback_t structure. Some
* fields in this structure are maintained by the driver. Use NULL for
* cy_stc_syspm_callback_t.prevItm and cy_stc_syspm_callback_t.nextItm.
* Driver uses these fields to build a linked list of callback functions.
* The value of cy_stc_syspm_callback_t.order element is used to define the order
* how the callbacks are put into linked list, and sequentially, how the
* callbacks are executed. See \ref group_syspm_cb_registering section.
*
* \warning The Cy_SysPm_RegisterCallback() function stores a pointer to the
* cy_stc_syspm_callback_t structure. Do not modify elements of the
* cy_stc_syspm_callback_t structure after the callback is registered.
* You are responsible for ensuring that the structure remains in scope.
* Typically the structure is declared as a global or static variable, or as a
* local variable in the main() function.
*
* \subsubsection group_syspm_cb_function_implementation Callback Function Implementation
*
* Every callback function should handle four possible steps (referred to as
* "mode") defined in \ref cy_en_syspm_callback_mode_t :
*    * CY_SYSPM_CHECK_READY - Check if ready to enter a power mode.
*    * CY_SYSPM_BEFORE_TRANSITION - The actions to be done before entering
*      the low power mode.
*    * CY_SYSPM_AFTER_TRANSITION - The actions to be done after exiting the
*      low power mode.
*    * CY_SYSPM_CHECK_FAIL - Roll back any actions performed in the callback
*      executed previously with CY_SYSPM_CHECK_READY.
*
* A callback function can skip steps (see \ref group_syspm_skip_callback_modes).
* In our example myDeepSleep1 and myDeepSleep2 callbacks do nothing while
* entering the low power mode (skip on CY_SYSPM_BEFORE_TRANSITION). If there is
* anything preventing low power mode entry - return CY_SYSPM_FAIL in response to
* CY_SYSPM_CHECK_READY in your callback implementation. Note that the callback
* should return CY_SYSPM_FAIL only in response to CY_SYSPM_CHECK_READY. The
* callback function should always return CY_SYSPM_PASS for other modes:
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* (see \ref group_syspm_cb_flow).
*
* \subsubsection group_syspm_cb_flow Callbacks Execution Flow
*
* This section explains what happens during a power transition, when callbacks
* are implemented and set up correctly. The following discussion assumes:
* * All required callback functions are defined and implemented
* * All cy_stc_syspm_callback_t structures are filled with required values
* * All callbacks are successfully registered
*
* User calls one of the power mode transition functions: \ref Cy_SysPm_CpuEnterSleep(),
* \ref Cy_SysPm_CpuEnterDeepSleep(), \ref Cy_SysPm_SystemEnterUlp(),
* \ref Cy_SysPm_SystemEnterLp(), or \ref Cy_SysPm_SystemEnterHibernate().
* It calls each callback with the mode set to CY_SYSPM_CHECK_READY. This
* triggers execution of the code for that mode inside of each user callback.
*
* The intent of CY_SYSPM_CHECK_READY is to only signal if the resources is ready
* to transition. Ideally, no transition changes should be made at this time.
* In some cases a small change may be required. For example a communication
* resource callback may set a flag telling firmware not to start any new
* transition.

* If that process is successful for all callbacks, then
* \ref Cy_SysPm_ExecuteCallback() calls each callback with the mode set to
* CY_SYSPM_BEFORE_TRANSITION. This triggers execution of the code for that mode
* inside each user callback. We then enter the low power mode after all callback
* are executed.
*
* When exiting the low power mode, the SysPm driver executes
* \ref Cy_SysPm_ExecuteCallback() again. This time it calls each callback in
* reverse order, with the mode set to CY_SYSPM_AFTER_TRANSITION. This triggers
* execution of the code for that mode inside each user callback. The final
* execution of callbacks depends on the low power mode in which callbacks were
* called:
* * For CPU Sleep or Deep Sleep power modes, the CY_SYSPM_AFTER_TRANSITION mode
*   is called after the CPU wakes from Sleep or Deep Sleep.
* * For system Hibernate, the CY_SYSPM_AFTER_TRANSITION mode is not executed
*   because the device reboots after the wakeup from the Hibernate.
* * For system LP and ULP modes, after the CY_SYSPM_AFTER_TRANSITION mode was
*   called the system remains in the new power mode: LP or ULP.
*
* A callback can return CY_SYSPM_FAIL only while executing the
* CY_SYSPM_CHECK_READY mode. If that happens, then the remaining callbacks are
* not executed. Any callbacks that have already executed are called again, in
* reverse order, with CY_SYSPM_CHECK_FAIL. This allows the system to return to
* the previous state. If a callback returns a fail then any of the functions
* (\ref Cy_SysPm_CpuEnterSleep(), \ref Cy_SysPm_CpuEnterDeepSleep(),
* \ref Cy_SysPm_SystemEnterUlp(), \ref Cy_SysPm_SystemEnterLp(), or
* \ref Cy_SysPm_SystemEnterHibernate()) that attempt to switch the device into
* a low power mode will also return CY_SYSPM_FAIL.
*
* Callbacks that reconfigure global resources, such as clock frequencies,
* should be registered last. They then modify global resources as the final
* step before entering the low power mode, and restore those resources first,
* as the system returns from low power mode.
*
* \subsubsection group_syspm_cb_registering Callback Registering
* While registration the callback is put into the linked list. The
* place where the callback structure is put into the linked list is based on
* cy_stc_syspm_callback_t.order. The callback with the lowest
* cy_stc_syspm_callback_t.order value will be placed at the beginning of linked
* list. The callback with the highest cy_stc_syspm_callback_t.order value will
* be placed at the end of the linked list.
* If there is already a callback structure in the linked list with the same
* cy_stc_syspm_callback_t.order value as you attend to register, then your
* callback will be placed right after such a callback.
*
* Such a registration order defines how the callbacks are executed:
* * Callbacks with the lower cy_stc_syspm_callback_t.order are executed first
* when entering into low power and last when exiting from low power.
* * Callbacks with the higher cy_stc_syspm_callback_t.order are executed last
* when entering into low power and first when exiting from low power.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_RegisterCallback
*
* Callbacks with equal cy_stc_syspm_callback_t.order values are
* registered in the same order as they are registered:
* \image html syspm_register_eq.png

* Callbacks with a different cy_stc_syspm_callback_t.order value will be
* stored based on the cy_stc_syspm_callback_t.order value, with no matter when
* they when registered:
*
* \image html syspm_register_dif.png
*
* This can be useful to ensure that system resources (clock dividers, etc) are
* changed right before entering low power mode and immediately after exiting
* from low power.
*
* \subsubsection group_syspm_cb_unregistering Callback Unregistering
*
* Unregistering the callback might be useful when you need to dynamically manage
* the callbacks.
*
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_UnregisterCallback
* The callback structures after myDeepSleep2 callback is unregistered:
* \image html syspm_unregistration.png
*
* \section group_syspm_definitions Definitions
*
* <table class="doxtable">
*   <tr>
*     <th>Term</th>
*     <th>Definition</th>
*   </tr>
*
*   <tr>
*     <td>LDO</td>
*     <td>Low dropout linear regulator. The functions that manage this
*         block are grouped as \ref group_syspm_functions_ldo under
*         \ref group_syspm_functions_core_regulators</td>
*   </tr>
*
*   <tr>
*     <td>SIMO Buck</td>
*     <td>Single inductor multiple Output Buck regulator, referred as
*         "Buck regulator" throughout the documentation. The functions that
*         manage this block are grouped as \ref group_syspm_functions_buck under
*         \ref group_syspm_functions_core_regulators</td>
*   </tr>
*
*   <tr>
*     <td>SISO Buck</td>
*     <td>Single inductor single output Buck regulator, referred as
*         "Buck regulator" throughout the documentation. The functions that
*         manage this block are grouped as \ref group_syspm_functions_buck under
*         \ref group_syspm_functions_core_regulators</td>
*   </tr>

*   <tr>
*     <td>PMIC</td>
*     <td>Power management integrated circuit. The functions that manage this
*         block are grouped as \ref group_syspm_functions_pmic</td>
*   </tr>
*
*   <tr>
*     <td>LP</td>
*     <td>System low power mode. See the \ref group_syspm_switching_into_lp
*         section for details.</td>
*   </tr>
*
*   <tr>
*     <td>ULP</td>
*     <td>System ultra low power mode. See the
*         \ref group_syspm_switching_into_ulp section for details.</td>
*   </tr>
* </table>
*
* \section group_syspm_section_more_information More Information
* For more information on the SysPm driver,
* refer to the technical reference manual (TRM).
*
* \section group_syspm_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>5.91</td>
*     <td>Updated \ref Cy_SysPm_Init() function.</td>
*     <td>To remove the clearing of reset reason.</td>
*   </tr>
*   <tr>
*     <td>5.90</td>
*     <td>
*           Added new function \ref Cy_SysPm_SetupDeepSleepRAM().
*     </td>
*     <td>Added support for DSRAM Setup for CAT1B devices.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">5.80</td>
*     <td>
*         Support for CAT1C devices.
*     </td>
*     <td>Power Management support for CAT1C devices.</td>
*   <tr>
*     <td>New API's Added/Modified
*         * Cy_SysPm_IsBgRefCtrl()
*         * Cy_SysPm_BgRefCtrl()
*         * Cy_SysPm_LdoSetMode()
*         * Cy_SysPm_LdoGetMode()
*         * Cy_SysPm_LdoIsEnabled()
*         * Cy_SysPm_Cm7IsActive()
*         * Cy_SysPm_Cm7IsSleep()
*         * Cy_SysPm_Cm7IsDeepSleep()
*         * Cy_SysPm_Cm7IsLowPower()
*         * Cy_SysPm_Cm0IsActive()
*         * Cy_SysPm_Cm0IsSleep()
*         * Cy_SysPm_Cm0IsLowPower()
*         * Cy_SysPm_Cm0IsDeepSleep()
*         * Cy_SysPm_IsSystemLp()
*         * Cy_SysPm_PmicEnable()
*         * Cy_SysPm_PmicDisable()
*         * Cy_SysPm_PmicAlwaysEnable()
*         * Cy_SysPm_PmicEnableOutput()
*         * Cy_SysPm_PmicDisableOutput()
*         * Cy_SysPm_PmicLock()
*         * Cy_SysPm_PmicUnlock()
*         * Cy_SysPm_PmicIsEnabled()
*         * Cy_SysPm_PmicIsOutputEnabled()
*         * Cy_SysPm_PmicIsLocked()
*         * Cy_SysPm_OvdEnable()
*         * Cy_SysPm_OvdDisable()
*         * Cy_SysPm_OvdVdddSelect()
*         * Cy_SysPm_OvdVddaSelect()
*         * Cy_SysPm_OvdActionSelect()
*         * Cy_SysPm_BodEnable()
*         * Cy_SysPm_BodDisable()
*         * Cy_SysPm_BodVdddSelect()
*         * Cy_SysPm_BodVddaSelect()
*         * Cy_SysPm_BodActionSelect()
*         * Cy_SysPm_SupplySupervisionStatus()
*         * Cy_SysPm_SystemIsMinRegulatorCurrentSet()
*         * Cy_SysPm_LinearRegDisable()
*         * Cy_SysPm_LinearRegEnable()
*         * Cy_SysPm_LinearRegGetStatus()
*         * Cy_SysPm_DeepSleepRegDisable()
*         * Cy_SysPm_DeepSleepRegEnable()
*         * Cy_SySPm_IsDeepSleepRegEnabled()
*         * Cy_SysPm_ReghcSelectMode()
*         * Cy_SysPm_ReghcGetMode()
*         * Cy_SysPm_ReghcSelectDriveOut()
*         * Cy_SysPm_ReghcGetDriveOut()
*         * Cy_SysPm_ReghcAdjustOutputVoltage()
*         * Cy_SysPm_ReghcDisableIntSupplyWhileExtActive()
*         * Cy_SysPm_ReghcEnableIntSupplyWhileExtActive()
*         * Cy_SysPm_ReghcDisablePmicEnableOutput()
*         * Cy_SysPm_ReghcEnablePmicEnableOutput()
*         * Cy_SysPm_ReghcEnablePmicStatusInput()
*         * Cy_SysPm_ReghcDisablePmicStatusInput()
*         * Cy_SysPm_ReghcSetPmicStatusWaitTime()
*         * Cy_SysPm_ReghcIsConfigured()
*         * Cy_SysPm_ReghcSetConfigured()
*         * Cy_SysPm_ReghcDisable()
*         * Cy_SysPm_ReghcEnable()
*         * Cy_SysPm_ReghcDisablePmicStatusTimeout()
*         * Cy_SysPm_ReghcEnablePmicStatusTimeout()
*         * Cy_SysPm_ReghcIsEnabled()
*         * Cy_SysPm_ReghcIsStatusOk()
*         * Cy_SysPm_ReghcIsSequencerBusy()
*         * Cy_SysPm_ReghcDisableVAdj()
*         * Cy_SysPm_ReghcEnableVAdj()
*         * Cy_SysPm_ReghcDisablePmicInDeepSleep()
*         * Cy_SysPm_ReghcEnablePmicInDeepSleep()
*         * Cy_SysPm_ReghcIsOcdWithinLimits()
*         * Cy_SysPm_ReghcIsCircuitEnabledAndOperating()
*
*     </td>
*     <td>New API's to handle CAT1C devices.</td>
*   <tr>
*     <td>Added \ref group_syspm_functions_ovd, \ref group_syspm_functions_bod, \ref group_syspm_functions_linearreg and \ref group_syspm_functions_reghc API's.</td>
*     <td>New API's to handle Power Management in CAT1C Devices.</td>
*   </tr>
*   <tr>
*     <td>
*           Added following functions for BTSS IP Reset:
*           \ref Cy_BTSS_AssertReset(), \ref Cy_BTSS_IsResetAsserted(),
*     </td>
*     <td>Added API's to support for BTSS IP Reset.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">5.70</td>
*     <td>
*         Support for CAT1B devices.
*     </td>
*     <td>Power Management support for CAT1B devices.</td>
*   <tr>
*     <td>New API's Added
*         * Cy_SysPm_Init()
*         * Cy_SysPm_SystemLpActiveEnter()
*         * Cy_SysPm_SystemLpActiveExit()
*         * Cy_SysPm_IsSystemLpActiveEnabled()
*         * Cy_SysPm_SetDeepSleepMode()
*         * Cy_SysPm_GetDeepSleepMode()
*         * Cy_SysPm_GetBootMode()
*         * Cy_SysPm_TriggerSoftReset()
*         * Cy_SysPm_GetHibernateWakeupCause()
*         * Cy_SysPm_ClearHibernateWakeupCause()
*         * Cy_SysPm_CoreBuckSetVoltage()
*         * Cy_SysPm_CoreBuckGetVoltage()
*         * Cy_SysPm_CoreBuckSetMode()
*         * Cy_SysPm_CoreBuckGetMode()
*         * Cy_SysPm_CoreBuckConfig()
*         * Cy_SysPm_CoreBuckStatus()
*         * Cy_SysPm_LdoExtraRequesterConfig()
*         * Cy_SysPm_SdrConfigure()
*         * Cy_SysPm_SdrSetVoltage()
*         * Cy_SysPm_SdrGetVoltage()
*         * Cy_SysPm_SdrEnable()
*         * Cy_SysPm_IsSdrEnabled()
*         * Cy_SysPm_HvLdoConfigure()
*         * Cy_SysPm_HvLdoSetVoltage()
*         * Cy_SysPm_HvLdoGetVoltage()
*         * Cy_SysPm_HvLdoEnable()
*         * Cy_SysPm_IsHvLdoEnabled()
*         * Cy_SysPm_IoUnfreeze()
*         * Cy_SysPm_DeepSleepIoIsFrozen()
*         * Cy_SysPm_DeepSleepIoUnfreeze()
*         * Cy_SysPm_BackupWordStore()
*         * Cy_SysPm_BackupWordReStore()
*         * Cy_SysPm_CpuEnterRAMOffDeepSleep()
*
*     </td>
*     <td>New API's to handle CAT1B devices.</td>
*   <tr>
*     <td>Added \ref group_syspm_ppu, \ref group_syspm_pdcm and \ref group_syspm_btss API's.</td>
*     <td>New API's to handle Power Management in CAT1B Devices.</td>
*   </tr>
*   </tr>
*   <tr>
*     <td rowspan="2">5.60</td>
*     <td>
*         For PSoC64 device, allow CM0+ to call CY_PRA_FUNCTION_CALL_X_X API in functions
*         accessing FUNCTION_POLICY registers. So that System Configuration structure is
*         updated with new parameters.
*     </td>
*     <td>For PSoC64 device, System configuration can be done from CM0+ application.</td>
*   </tr>
*   <tr>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>5.50</td>
*     <td>
*           Added following functions for SRAM power mode configuration:
*           \ref Cy_SysPm_SetSRAMMacroPwrMode(), \ref Cy_SysPm_SetSRAMPwrMode(),
*           \ref Cy_SysPm_GetSRAMMacroPwrMode(). For PSoC 64 devices these
*           functions can return PRA driver status value.
*     </td>
*     <td>Added support for SRAM power mode configuration.</td>
*   </tr>
*   <tr>
*     <td>5.40</td>
*     <td>Support for CM33.</td>
*     <td>New devices support.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">5.30</td>
*     <td>
*           Updated \ref Cy_SysPm_LdoSetVoltage() and Cy_SysPm_SystemSetMinRegulatorCurrent()
*           to extend the wakeup delay from Deep Sleep for 1.1 V LDO for the case when system
*           regulator is configured to the minimum current mode. Please refer to
*           \ref group_syspm_system_reg_curr_mode for the more details on system regulator modes.
*     </td>
*     <td>Ensure valid VCCD upon wakeup for the system regulator's minimum current mode.</td>
*   </tr>
*   <tr>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>Updated the \ref Cy_SysPm_CpuEnterDeepSleep() function to ensure the Low-power mode
*         entry abort when a system call initiated by Cortex-M4 or Cortex-M0+ is pending.</td>
*     <td>Fixed the issue when the non-blocking flash write initiated by the Cortex-M4 application
*         fails to complete because the Cortex-M0+ CPU is in Deep Sleep mode.</td>
*   </tr>
*   <tr>
*     <td>5.20</td>
*     <td>
*           Updated \ref Cy_SysPm_CpuEnterDeepSleep() function for
*           the CYB06xx7 devices.
*     </td>
*     <td>Added CYB06xx7 device support.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">5.10</td>
*     <td>
*           Updated the following functions for the PSoC 64 devices:
*           \ref Cy_SysPm_CpuEnterDeepSleep(), \ref Cy_SysPm_SystemEnterLp(),
*           \ref Cy_SysPm_SystemEnterUlp, \ref Cy_SysPm_SystemEnterHibernate,
*           \ref Cy_SysPm_SetHibernateWakeupSource,
*           \ref Cy_SysPm_ClearHibernateWakeupSource,
*           \ref Cy_SysPm_SystemSetMinRegulatorCurrent,
*           \ref Cy_SysPm_SystemSetNormalRegulatorCurrent,
*           \ref Cy_SysPm_LdoSetVoltage, \ref Cy_SysPm_LdoSetMode,
*           \ref Cy_SysPm_BuckEnable, \ref Cy_SysPm_BuckSetVoltage1,
*           Following functions are updated as unavailable for PSoC 64 devices:
*           \ref Cy_SysPm_WriteVoltageBitForFlash, \ref Cy_SysPm_SaveRegisters,
*           \ref Cy_SysPm_RestoreRegisters,
*           \ref Cy_SysPm_BuckSetVoltage2, \ref Cy_SysPm_BuckEnableVoltage2,
*           \ref Cy_SysPm_BuckDisableVoltage2,
*           \ref Cy_SysPm_BuckSetVoltage2HwControl, SetReadMarginTrimUlp,
*           SetReadMarginTrimLp, SetWriteAssistTrimUlp, IsVoltageChangePossible.
*     </td>
*     <td>
*           Added PSoC 64 device support.
*     </td>
*   </tr>
*   <tr>
*     <td>
*           For PSoC 64 devices the following functions can return PRA driver
*           status value:
*           \ref Cy_SysPm_CpuEnterDeepSleep(),
*           \ref Cy_SysPm_SystemEnterHibernate(),
*           \ref Cy_SysPm_SystemEnterLp(),
*           \ref Cy_SysPm_SystemEnterUlp(),
*           \ref Cy_SysPm_SystemSetMinRegulatorCurrent(),
*           \ref Cy_SysPm_SystemSetNormalRegulatorCurrent(),
*           \ref Cy_SysPm_LdoSetVoltage(), \ref Cy_SysPm_LdoSetMode(),
*           \ref Cy_SysPm_BuckEnable(), \ref Cy_SysPm_BuckSetVoltage1(),
*     </td>
*     <td>
*           For PSoC 64 devices the SysPm driver uses the PRA driver to change
*           the protected registers. A SysPm driver function that calls a PRA
*           driver function will return the PRA error status code if the called
*           PRA function returns an error. In these cases, refer to PRA return
*           statuses \ref cy_en_pra_status_t.
*     </td>
*   </tr>
*   <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>5.0</td>
*     <td>
*           Updated the internal IsVoltageChangePossible() function
*           (\ref Cy_SysPm_LdoSetVoltage(), \ref Cy_SysPm_BuckEnable(),
*           \ref Cy_SysPm_BuckSetVoltage1(), \ref Cy_SysPm_SystemEnterUlp()
*           and \ref Cy_SysPm_SystemEnterLp() functions are affected).
*           For all the devices except CY8C6xx6 and CY8C6xx7 added the check if
*           modifying the RAM trim register is allowed.
*     </td>
*     <td>
*           Protecting the system from a possible CPU hard-fault cause. If you
*           are using PC > 0 in your project and you want to switch the power
*           modes (LP<->ULP), you need to unprotect the CPUSS_TRIM_RAM_CTL and
*           CPUSS_TRIM_ROM_CTL registers and can use a programmable PPU for that.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="2">4.50</td>
*     <td>Updated the \ref Cy_SysPm_CpuEnterDeepSleep() function.</td>
*     <td>
*           Updated the mechanism for saving/restoring not retained UDB and clock
*           registers in the Cy_SysPm_CpuEnterDeepSleep() function.
*     </td>
*   </tr>
*   <tr>
*     <td>
*           Updated the \ref Cy_SysPm_CpuEnterDeepSleep() function to use values
*           stored into the variable instead of reading them directly from
*           SFLASH memory.
*     </td>
*     <td>
*           SFLASH memory can be unavailable to read the correct value after
*           a Deep sleep state on the CY8C6xx6 and CY8C6xx7 devices.
*     </td>
*   </tr>
*   <tr>
*     <td>4.40</td>
*     <td>
*           Fixed \ref Cy_SysPm_LdoSetVoltage(), \ref Cy_SysPm_BuckEnable(), and
*           \ref Cy_SysPm_BuckSetVoltage1() functions. Corrected the sequence for
*           setting the RAM trim value. This behavior is applicable for all
*           devices, except CY8C6xx6 and CY8C6xx7.
*     </td>
*     <td>
*           For all devices, except CY8C6xx6 and CY8C6xx7, the trim
*           sequence was setting incorrect trim values for RAM.
*           This could cause a CPU hard fault.
*     </td>
*   </tr>
*   <tr>
*     <td>4.30</td>
*     <td>
*           Corrected the \ref Cy_SysPm_CpuEnterDeepSleep() function.
*           Removed early access to flash values after system Deep Sleep, when
*           flash is not ready to be used. Now the \ref Cy_SysPm_CpuEnterDeepSleep()
*           function does not access flash until the flash is ready.
*           This behavior is applicable only on multi-CPU devices CY8C6xx6 and
*           CY8C6xx7.
*     </td>
*     <td>
*           For CY8C6xx6 and CY8C6xx7 early access to flash values after
*           system Deep Sleep could potentially cause hard fault.
*           Now after system Deep Sleep only ram values are used before
*           flash is ready.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="3">4.20</td>
*     <td>Updated the \ref Cy_SysPm_RegisterCallback() function.
*         Added a new element to callback structure -
*         cy_stc_syspm_callback_t.order</td>
*     <td>Enhanced the mechanism of callbacks registration and execution. Now
*         callbacks can be ordered during registration. This means the
*         execution flow now is based on cy_stc_syspm_callback_t.order.
*         For more details, see the \ref group_syspm_cb_registering section. </td>
*   </tr>
*   <tr>
*     <td>Updated \ref group_syspm_cb section.
*         Added \ref group_syspm_cb_registering section</td>
*     <td>Added explanations how to use updated callbacks registration
*         mechanism. </td>
*   </tr>
*   <tr>
*     <td>Added new function  \ref Cy_SysPm_GetFailedCallback()</td>
*     <td>Added new functionality to support callback debugging</td>
*   </tr>
*   <tr>
*     <td>4.10.1</td>
*     <td>
*           Updated the Cy_SysPm_BackupEnableVoltageMeasurement() description
*     </td>
*     <td>
*           Changed the scale number from 40% to 10% to correctly reflect a real value.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="3">4.10</td>
*     <td>Updated the \ref Cy_SysPm_CpuEnterDeepSleep() function.</td>
*     <td>
*         Corrected the mechanism for saving/restoring not retained UDB
*         registers in the Cy_SysPm_CpuEnterDeepSleep() function.
*
*         Now, the \ref Cy_SysPm_CpuEnterDeepSleep() function does not put CM0+ CPU
*         into Deep Sleep and returns \ref CY_SYSPM_SYSCALL_PENDING status, if a
*         syscall operation is pending. This behavior is applicable on multi-CPU
*         devices except CY8C6xx6 and CY8C6xx7.
*     </td>
*   </tr>
*   <tr>
*     <td>Updated the \ref Cy_SysPm_CpuEnterSleep() function.</td>
*     <td>Removed the redundant second call of the WFE() instruction on CM4 CPU.
*         This change is applicable for all devices except CY8C6xx6,
*         CY8C6xx7.
*    </td>
*   </tr>
*   <tr>
*     <td>Added a new \ref CY_SYSPM_SYSCALL_PENDING return status. </td>
*     <td>Expanded driver return statuses for indicating new possible events in
*         the driver.
*     </td>
*   </tr>
*   </tr>
*   <tr>
*     <td rowspan="6">4.0</td>
*     <td>
*          Flattened the organization of the driver source code into the single
*          source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>
*          Changed power modes names. See \ref group_syspm_system_power_modes.
*
*          Renamed the following functions:
*           - Cy_SysPm_Sleep to Cy_SysPm_CpuEnterSleep
*           - Cy_SysPm_DeepSleep to Cy_SysPm_CpuEnterDeepSleep
*           - Cy_SysPm_Hibernate to Cy_SysPm_SystemEnterHibernate
*           - Cy_SysPm_SleepOnExit to Cy_SysPm_CpuSleepOnExit
*           - Cy_SysPm_EnterLowPowerMode to Cy_SysPm_SystemSetMinRegulatorCurrent
*           - Cy_SysPm_ExitLowPowerMode to Cy_SysPm_SystemSetNormalRegulatorCurrent
*           - Cy_SysPm_IsLowPower to Cy_SysPm_IsSystemUlp
*
*          For all renamed functions, added BWC macros to simplify migration.
*     </td>
*     <td>Device power modes simplification</td>
*   </tr>
*   <tr>
*     <td>
*         Added the following functions:
*          - Cy_SysPm_LdoSetMode
*          - Cy_SysPm_LdoGetMode
*          - Cy_SysPm_WriteVoltageBitForFlash
*          - Cy_SysPm_SaveRegisters
*          - Cy_SysPm_RestoreRegisters
*          - Cy_SysPm_CpuSendWakeupEvent
*          - Cy_SysPm_SystemIsMinRegulatorCurrentSet
*          - Cy_SysPm_SystemEnterLp
*          - Cy_SysPm_SystemEnterUlp
*          - Cy_SysPm_IsSystemLp
*     </td>
*     <td>Added new functionality to configure device power modes</td>
*   </tr>
*   <tr>
*     <td>
*          Callback mechanism changes:
*          - Removed the limitation for numbers of registered callbacks. Previously it
*            was possible to register up to 32 callbacks. Now the maximum registered
*            callbacks is not limited by the SysPm driver.
*          - Internal enhancement in callback execution flow.
*          - <b>Changes with BWC issues</b>:
*            -# Removed the <b>mode</b> element from cy_stc_syspm_callback_params_t
*               structure. Now this element is a separate parameter in the
*               callback function.
*            -# Changed the interface of the callback function,
*               added the cy_en_syspm_callback_mode_t mode parameter:
*               - was cy_en_syspm_status_t FuncName (cy_stc_syspm_callback_params_t *callbackParams);
*               - now cy_en_syspm_status_t FuncName (cy_stc_syspm_callback_params_t *callbackParams,
*                 cy_en_syspm_callback_mode_t mode);
*     </td>
*     <td>Callback mechanism enhancements</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>Added \ref group_syspm_migration_guide_for_syspm_4_0.</td>
*     <td>Provided a guidance for migrating to the latest SysPm driver version</td>
*   </tr>
*   <tr>
*     <td rowspan="2">3.0</td>
*     <td>Removed three functions:
*          - Cy_SysPm_Cm4IsLowPower
*          - Cy_SysPm_Cm0IsLowPower
*          - Cy_SysPm_IoFreeze
*
*         Removed the following macros:
*          - CY_SYSPM_STATUS_CM0_LOWPOWER
*          - CY_SYSPM_STATUS_CM4_LOWPOWER
*     </td>
*     <td>
*         Removed the two functions Cy_SysPm_Cm4IsLowPower,
*         Cy_SysPm_Cm0IsLowPower because low power mode is related to the
*         device and not to the CPU.
*         The function Cy_SysPm_IsSystemUlp must be used instead of these two
*         functions.
*
*         Removed Cy_SysPm_IoFreeze because the are no known use cases with IOs
*         freeze in power modes, except Hibernate. In Hibernate power mode, the
*         IOs are frozen automatically.
*     </td>
*   </tr>
*   <tr>
*     <td>
*         Corrected the syspm callback mechanism behavior. Now callbacks with
*         CY_SYSPM_AFTER_TRANSITION mode are executed from the last registered
*         to the first registered. Previously callbacks with
*         CY_SYSPM_AFTER_TRANSITION mode were executed from last executed to
*         the first registered.
*     </td>
*     <td>Corrected the syspm callbacks execution sequence</td>
*   </tr>
*   <tr>
*     <td>2.21</td>
*     <td>Removed saving/restoring the SysClk measurement counters while
*         in Deep Sleep routine
*     </td>
*     <td>Removed possible corruption of SysClk measurement counters if the
*         core wakes up from the Deep Sleep.
*     </td>
*   </tr>
*   <tr>
*     <td>2.20</td>
*     <td> \n
*          * Added support for changing core voltage when the protection context
*            is other that zero. Such support is available only for devices
*            that support modifying registers via syscall.
*
*          * For preproduction PSoC 6 devices the changing core voltage
*            is prohibited when the protection context is other than zero.
*
*          * Updated the following functions. They now have a
*            \ref cy_en_syspm_status_t return value and use a syscall:
*            - Cy_SysPm_LdoSetVoltage
*            - Cy_SysPm_BuckSetVoltage1
*            - Cy_SysPm_BuckEnable
*
*            No backward compatibility issues.
*
*          * Added new CY_SYSPM_CANCELED element in
*            the \ref cy_en_syspm_status_t.
*
*          * Documentation updates.
*
*          * Added warning that
*            Cy_SysPm_PmicDisable(CY_SYSPM_PMIC_POLARITY_LOW) is not
*            supported by hardware.
*     </td>
*     <td>Added support for changing the core voltage in protection context
*         higher than zero (PC > 0).
*
*         Documentation update and clarification
*     </td>
*   </tr>
*   <tr>
*     <td>2.10</td>
*     <td> \n
*          * Changed names for all Backup, Buck-related functions, defines,
*            and enums
*          * Changed next power mode function names:
*            Cy_SysPm_EnterLowPowerMode
*            Cy_SysPm_ExitLpMode
*            Cy_SysPm_SetHibWakeupSource
*            Cy_SysPm_ClearHibWakeupSource
*            Cy_SysPm_GetIoFreezeStatus
*          * Changed following enumeration names:
*            cy_en_syspm_hib_wakeup_source_t
*            cy_en_syspm_simo_buck_voltage1_t
*            cy_en_syspm_simo_buck_voltage2_t
*          * Updated Power Modes documentation section
*          * Added Low Power Callback Managements section
*          * Documentation edits
*     </td>
*     <td> \n
*          * Improvements made based on usability feedback
*          * Documentation update and clarification
*     </td>
*   </tr>
*   <tr>
*     <td>2.0</td>
*     <td>Enhancement and defect fixes:
*         * Added input parameter(s) validation to all public functions
*         * Removed "_SysPm_" prefixes from the internal functions names
*         * Changed the type of elements with limited set of values, from
*           uint32_t to enumeration
*         * Enhanced syspm callback mechanism
*         * Added functions to control:
*           * Power supply for the Vddbackup
*           * Supercapacitor charge
*           * Vddbackup measurement by ADC
*     </td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \subsection group_syspm_migration_guide_for_syspm_4_0 Migration Guide: Moving to SysPm v4.0
*
* This section provides a guideline to migrate from v2.21 to v4.0 of the SysPm
* driver.
*
* \subsubsection group_syspm_migration_into_4_0_intro Introduction
*
* If your application currently uses SysPm v2.21 APIs, you must
* migrate to SysPm v4.0 so that your application continues to operate.
*
* Take a few minutes to review the following information:
* - The APIs related to PSoC 6 \ref group_syspm_power_modes are changed. Old
*   power modes APIs function names are now deprecated and should not be used
*   in new applications.
* - The \ref group_syspm_cb mechanism is changed. The mode element is removed
*   from cy_stc_syspm_callback_params_t structure. Now this element is a
*   separate parameter in the callback function.
*
* \subsubsection group_syspm_migration_into_4_0_names Migrating to new power modes APIs.
* The table below shows the new APIs names that should be used in the
* application instead of old names:
*
* <table class="doxtable">
*   <tr><th>SysPm v2.21 API name</th><th>SysPm v4.0 API name</th><th>Comment</th></tr>
*   <tr>
*     <td>Cy_SysPm_Sleep</td>
*     <td>\ref Cy_SysPm_CpuEnterSleep</td>
*     <td>Renamed, no functional changes</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_DeepSleep</td>
*     <td>\ref Cy_SysPm_CpuEnterDeepSleep</td>
*     <td>Renamed, no functional changes</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_Hibernate</td>
*     <td>\ref Cy_SysPm_SystemEnterHibernate</td>
*     <td>Renamed, no functional changes</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_SleepOnExit</td>
*     <td>\ref Cy_SysPm_CpuSleepOnExit</td>
*     <td>Renamed, no functional changes</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_IsLowPower</td>
*     <td>\ref Cy_SysPm_IsSystemUlp</td>
*     <td>Now this function checks whether the device is in ULP mode</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_EnterLowPowerMode</td>
*     <td>\ref Cy_SysPm_SystemSetMinRegulatorCurrent</td>
*     <td>The low power active mode does not exist anymore.
*         The \ref group_syspm_system_reg_curr_mode is implemented instead </td>
*     </tr>
*   <tr>
*     <td>Cy_SysPm_ExitLowPowerMode</td>
*     <td>\ref Cy_SysPm_SystemSetNormalRegulatorCurrent</td>
*     <td>The low power active mode does not exist anymore.
*         The \ref group_syspm_system_reg_curr_mode is implemented instead</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_Cm4IsLowPower</td>
*     <td>Removed</td>
*     <td>This function is removed because low power mode is related to the system
*         and not to the CPU</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_Cm0IsLowPower</td>
*     <td>Removed</td>
*     <td>This function is removed because low power mode is related to the system
*         and not to the CPU</td>
*   </tr>
*   <tr>
*     <td>Cy_SysPm_IoFreeze</td>
*     <td>Removed</td>
*     <td>This function is removed because there are no known use cases to
*         freeze in power modes other than Hibernate</td>
*   </tr>
* </table>
*
* In addition to renamed power modes APIs, the following defines and enum
* elements names are changed:
* <table class="doxtable">
*   <tr><th>SysPm v2.21 defines</th><th>SysPm v4.0 defines</th><th>Comment</th></tr>
*   <tr>
*     <td>CY_SYSPM_ENTER_LP_MODE</td>
*     <td>CY_SYSPM_ULP</td>
*     <td>The \ref cy_en_syspm_callback_type_t element is renamed to align
*         callback types names to new power modes names</td>
*   </tr>
*   <tr>
*     <td>CY_SYSPM_EXIT_LP_MODE</td>
*     <td>CY_SYSPM_LP</td>
*     <td>The \ref cy_en_syspm_callback_type_t element is renamed to align
*         callback types names to new power modes names</td>
*   <tr>
*     <td>CY_SYSPM_STATUS_SYSTEM_LOWPOWER</td>
*     <td>CY_SYSPM_STATUS_SYSTEM_ULP</td>
*     <td>Status define, renamed to align new power modes names
*         and abbreviations</td>
*   </tr>
* </table>
*
* \subsubsection group_syspm_migration_into_4_0_callbacks Migrating to SysPm v4.0 callbacks
*
* Review this section if your application is using the syspm callback mechanism.
*
* To migrate to SysPm v4.0 callbacks you need to perform the following steps:
* -# Remove mode element from all \ref cy_stc_syspm_callback_params_t
*    structures defined in your application. In SysPm v2.21 this structure is:
*    \code{.c}
*    cy_stc_syspm_callback_params_t deepSleepParam1 =
*    {
*        CY_SYSPM_CHECK_READY,
*        &HW1_address,
*        &context
*    };
*    \endcode
*
*    In SysPm v4.0 this structure should be:
*    \code{.c}
*    cy_stc_syspm_callback_params_t deepSleepParam1 =
*    {
*        &HW1_address,
*        &context
*    };
*    \endcode
* -# Update all defined syspm callback function prototypes to have two
*    parameters instead of one. The SysPm v2.21 callback function prototype is:
*    \code{.c}
*    cy_en_syspm_status_t Func1 (cy_stc_syspm_callback_params_t *callbackParams);
*    \endcode
*    The SysPm v4.0 callback function prototype should be:
*    \code{.c}
*    cy_en_syspm_status_t Func1 (cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
*    \endcode
* -# Change the syspm callback function implementation to not use a mode
*    value as an element of the callbackParams structure, but, as separate
*    function parameter:
*    SysPm v2.21 callback function implementation:
*    \code{.c}
*    cy_en_syspm_status_t Func1(cy_stc_syspm_callback_params_t *callbackParams)
*    {
*        cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;
*
*        switch(callbackParams->mode)
*        {
*            case CY_SYSPM_CHECK_READY:
*            ...
*        }
*
*        return (retVal);
*    }
*    \endcode
*    SysPm v4.0 callback function implementation:
*    \code{.c}
*    cy_en_syspm_status_t Func1(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
*    {
*        cy_en_syspm_status_t retVal = CY_SYSPM_FAIL;
*
*        switch(mode)
*        {
*            case CY_SYSPM_CHECK_READY:
*            ...
*        }
*
*        return (retVal);
*    }
*    \endcode
* After the changes above are done, you have successfully migrated to SysPm v4.0.
*
* Do not forget to review newly added functionality for SysPm v4.0 in the
* \ref group_syspm_changelog.

* \defgroup group_syspm_macros Macros
* \defgroup group_syspm_functions Functions
* \{
    \defgroup group_syspm_functions_general        General
*   \defgroup group_syspm_functions_power          Power Modes
*   \defgroup group_syspm_functions_power_status   Power Status
*   \defgroup group_syspm_functions_iofreeze       I/Os Freeze
*   \defgroup group_syspm_functions_core_regulators    Core Voltage Regulation
*   \{
*     \defgroup group_syspm_functions_ldo      LDO
*     \defgroup group_syspm_functions_buck     Buck
*   \}
*   \defgroup group_syspm_functions_pmic       PMIC
*   \defgroup group_syspm_functions_backup     Backup Domain
*   \defgroup group_syspm_functions_callback   Low Power Callbacks
*   \defgroup group_syspm_functions_linearreg  Linear Regulator
*   \defgroup group_syspm_functions_reghc      REGHC (High Current Regulator)
*   \defgroup group_syspm_functions_ovd        OVD
*   \defgroup group_syspm_functions_bod        BOD
* \}
* \defgroup group_syspm_data_structures Data Structures
* \defgroup group_syspm_data_enumerates Enumerated Types
*/

#if !defined (CY_SYSPM_H)
#define CY_SYSPM_H

#include "cy_device.h"

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)

#include <stdbool.h>
#include <stddef.h>

#include "cy_device.h"
#include "cy_device_headers.h"
#include "cy_syslib.h"

#if ((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE)))
    #include "cy_pra.h"
#endif /* #if ((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE))) */

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*       Register Constants
*******************************************************************************/

/**
* \addtogroup group_syspm_macros
* \{
*/

/** Driver major version */
#define CY_SYSPM_DRV_VERSION_MAJOR       5

/** Driver minor version */
#define CY_SYSPM_DRV_VERSION_MINOR       91

/** SysPm driver identifier */
#define CY_SYSPM_ID                      (CY_PDL_DRV_ID(0x10U))


/*******************************************************************************
*       Internal Defines
*******************************************************************************/

/** \cond INTERNAL */


/* Macro to validate parameters in Cy_SysPm_SetHibernateWakeupSource() and for Cy_SysPm_ClearHibernateWakeupSource() function */
#define CY_SYSPM_IS_WAKE_UP_SOURCE_VALID(wakeupSource)   (0UL == ((wakeupSource) & \
                                                          ((uint32_t) ~(CY_SYSPM_HIB_WAKEUP_SOURSE_MASK))))


#if defined (CY_IP_MXS40SRSS)
/**
* \note
* This macro is available for CAT1A devices.
**/

/* Macro to validate parameters in Cy_SysPm_PmicDisable() function */
#define CY_SYSPM_IS_POLARITY_VALID(polarity)            (((polarity) == CY_SYSPM_PMIC_POLARITY_LOW) || \
                                                         ((polarity) == CY_SYSPM_PMIC_POLARITY_HIGH))

/* Macro to validate parameters in Cy_SysPm_BuckSetVoltage1() function */
#define CY_SYSPM_IS_BUCK_VOLTAGE1_VALID(voltage)        (((voltage) == CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V) || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT1_VOLTAGE_1_1V))

/* Macro to validate parameters in Cy_SysPm_BuckSetVoltage2() function */
#define CY_SYSPM_IS_BUCK_VOLTAGE2_VALID(voltage)        (((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_15V) || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_2V)  || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_25V) || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_3V)  || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_35V) || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_4V)  || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_45V) || \
                                                         ((voltage) == CY_SYSPM_BUCK_OUT2_VOLTAGE_1_5V))

/* Macro to validate parameters in Cy_SysPm_BuckIsOutputEnabled() function */
#define CY_SYSPM_IS_BUCK_OUTPUT_VALID(output)           (((output) == CY_SYSPM_BUCK_VBUCK_1) || \
                                                         ((output) == CY_SYSPM_BUCK_VRF))

/* Macro to validate parameters in Cy_SysPm_LdoSetVoltage() function */
#define CY_SYSPM_IS_LDO_VOLTAGE_VALID(voltage)          (((voltage) == CY_SYSPM_LDO_VOLTAGE_0_9V) || \
                                                         ((voltage) == CY_SYSPM_LDO_VOLTAGE_1_1V))
#endif

/* Macro to validate parameters in Cy_SysPm_ExecuteCallback() function */
#if defined (CY_IP_MXS40SRSS)
#if (CY_IP_MXS40SRSS_VERSION < 3)

/**
* \note
* This macro is available for CAT1A devices.
**/
#define CY_SYSPM_IS_CALLBACK_TYPE_VALID(type)           (((type) == CY_SYSPM_SLEEP) || \
                                                         ((type) == CY_SYSPM_DEEPSLEEP) || \
                                                         ((type) == CY_SYSPM_HIBERNATE) || \
                                                         ((type) == CY_SYSPM_ULP) || \
                                                         ((type) == CY_SYSPM_LP))
#endif /* (CY_IP_MXS40SRSS_VERSION < 3) */

#if (CY_IP_MXS40SRSS_VERSION >= 3)

/* Macro to validate parameters in Cy_SysPm_ExecuteCallback() function */
/**
* \note
* This macro is available for CAT1C devices.
**/
#define CY_SYSPM_IS_CALLBACK_TYPE_VALID(type)           (((type) == CY_SYSPM_SLEEP) || \
                                                         ((type) == CY_SYSPM_DEEPSLEEP) || \
                                                         ((type) == CY_SYSPM_HIBERNATE) || \
                                                         ((type) == CY_SYSPM_LPACTIVE_ENTER) || \
                                                         ((type) == CY_SYSPM_LPACTIVE_EXIT))

/* Macro to validate OVD ACTION */
/**
* \note
* This macro is available for CAT1C devices.
**/

#define CY_OVD_CHECK_ACTION_CFG(ovdActionSelect)        (((ovdActionSelect) == CY_SYSPM_OVD_ACTION_NOTHING) || \
                                                         ((ovdActionSelect) == CY_SYSPM_OVD_ACTION_FAULT) || \
                                                         ((ovdActionSelect) == CY_SYSPM_OVD_ACTION_RESET))

/* Macro to validate BOD ACTION */
/**
* \note
* This macro is available for CAT1C devices.
**/

#define CY_BOD_CHECK_ACTION_CFG(bodActionSelect)        (((bodActionSelect) == CY_SYSPM_BOD_ACTION_NOTHING) || \
                                                         ((bodActionSelect) == CY_SYSPM_BOD_ACTION_FAULT) || \
                                                         ((bodActionSelect) == CY_SYSPM_BOD_ACTION_RESET))

/* Macro to validate SUPPLY ENTITY */
/**
* \note
* This macro is available for CAT1C devices.
**/
#define CY_OVD_CHECK_SUPPLY_ENTITY(supplyEntitySelect)  (((supplyEntitySelect) == CY_SYSPM_ENTITY_BOD_VDDD) || \
                                                         ((supplyEntitySelect) == CY_SYSPM_ENTITY_BOD_VDDA) || \
                                                         ((supplyEntitySelect) == CY_SYSPM_ENTITY_BOD_VCCD) || \
                                                         ((supplyEntitySelect) == CY_SYSPM_ENTITY_OVD_VDDD) || \
                                                         ((supplyEntitySelect) == CY_SYSPM_ENTITY_OVD_VDDA) || \
                                                         ((supplyEntitySelect) == CY_SYSPM_ENTITY_OVD_VCCD))

#endif /* (CY_IP_MXS40SRSS_VERSION >= 3) */
#endif /* defined (CY_IP_MXS40SRSS) */


#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B devices.
**/
#define CY_SYSPM_IS_CALLBACK_TYPE_VALID(type)           (((type) == CY_SYSPM_SLEEP)         || \
                                                         ((type) == CY_SYSPM_LPACTIVE_ENTER)|| \
                                                         ((type) == CY_SYSPM_LPACTIVE_EXIT) || \
                                                         ((type) == CY_SYSPM_DEEPSLEEP)     || \
                                                         ((type) == CY_SYSPM_DEEPSLEEP_RAM) || \
                                                         ((type) == CY_SYSPM_DEEPSLEEP_OFF) || \
                                                         ((type) == CY_SYSPM_HIBERNATE))
/* Macro to validate deep sleep modes in Cy_SysPm_CpuEnterDeepSleep() function */
#define CY_SYSPM_IS_DEEPSLEEP_MODE_VALID(mode)             (((mode) == CY_SYSPM_DEEPSLEEP)     || \
                                                            ((mode) == CY_SYSPM_DEEPSLEEP_RAM) || \
                                                            ((mode) == CY_SYSPM_DEEPSLEEP_OFF))
/* Macro to validate parameters in Cy_SysPm_SetupDeepSleepRAM() function */
#define CY_SYSPM_IS_DSRAM_CHECK_VALID(dsramCheck)          (((dsramCheck) == CY_SYSPM_PRE_DSRAM) || \
                                                            ((dsramCheck) == CY_SYSPM_POST_DSRAM))

/* Macro to validate parameters in Cy_SysPm_CoreBuckSetVoltage() & Cy_SysPm_CoreBuckConfig functions */
#define CY_SYSPM_IS_CORE_BUCK_VOLTAGE_VALID(voltage)    (((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_76V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_78V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_80V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_82V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_84V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_86V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_88V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_90V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_92V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_94V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_96V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_0_98V)  || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_00V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_02V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_04V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_06V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_08V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_10V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_12V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_14V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_16V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_18V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_20V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_22V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_24V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_26V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_28V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_30V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_32V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_34V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_36V) || \
                                                         ((voltage) == CY_SYSPM_CORE_BUCK_VOLTAGE_1_38V))

/* Macro to validate core buck mode in Cy_SysPm_CoreBuckConfig() function */
#define CY_SYSPM_IS_CORE_BUCK_MODE_VALID(mode)           (((mode) == CY_SYSPM_CORE_BUCK_MODE_LP)     || \
                                                          ((mode) == CY_SYSPM_CORE_BUCK_MODE_HP))

/* Macro to Enable/Disable Pause on Core Buck Regulator */
#define CY_SYSPM_CORE_BUCK_PAUSE_ENABLE(enable)          CY_REG32_CLR_SET(SRSS_PWR_CBUCK_CTL2, SRSS_PWR_CBUCK_CTL2_CBUCK_PAUSE, \
                                                          enable)

/* Macro to Enable/Disable Override on Core Buck Regulator */
#define CY_SYSPM_CORE_BUCK_OVERRRIDE_ENABLE(enable)          CY_REG32_CLR_SET(SRSS_PWR_CBUCK_CTL2, SRSS_PWR_CBUCK_CTL2_CBUCK_OVERRIDE, \
                                                          enable)

/* Macro to Enable/Disable Copy Settings of Core Buck Regulator*/
#define CY_SYSPM_CORE_BUCK_COPY_SETTINGS_ENABLE(enable)          CY_REG32_CLR_SET(SRSS_PWR_CBUCK_CTL2, SRSS_PWR_CBUCK_CTL2_CBUCK_COPY_SETTINGS, \
                                                          enable)


/* Macro to validate core buck Inrush Limit in Cy_SysPm_CoreBuckConfig() function */
#define CY_SYSPM_IS_CORE_BUCK_INRUSH_LIMIT_VALID(limit)    (((limit) == CY_SYSPM_CORE_BUCK_INRUSH_LIMIT_10)     || \
                                                            ((limit) == CY_SYSPM_CORE_BUCK_INRUSH_LIMIT_100))

/* Macro to validate parameters in Cy_SysPm_LdoSdrConfigure() function */
#define CY_SYSPM_IS_SDR_VOLTAGE_VALID(voltage)          (((voltage) == CY_SYSPM_SDR_VOLTAGE_0_850V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_0_875V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_0_900V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_0_925V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_0_950V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_0_975V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_000V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_025V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_050V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_075V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_100V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_125V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_150V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_175V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_200V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_225V))

/* Macro to validate parameters in Cy_SysPm_HvLdoConfigure() function */
#define CY_SYSPM_IS_HVLDO_VOLTAGE_VALID(voltage)        (((voltage) == CY_SYSPM_HVLDO_VOLTAGE_1_500V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_1_600V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_1_700V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_1_800V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_1_900V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_000V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_100V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_200V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_300V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_400V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_500V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_600V)  || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_700V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_800V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_2_900V) || \
                                                         ((voltage) == CY_SYSPM_HVLDO_VOLTAGE_3_000V))

/* Macro to validate if the SDR number in Cy_SysPm_LdoSdrConfigure() function */
#define CY_SYSPM_IS_SDR_NUM_VALID(num)    (((num) == CY_SYSPM_SDR_0)     || \
                                           ((num) == CY_SYSPM_SDR_1))

/* Macro to validate parameters in RAM/ROM TRIM functions */
#define CY_SYSPM_IS_SDR_TRIM_VOLTAGE_VALID(voltage)     (((voltage) == CY_SYSPM_SDR_VOLTAGE_0_900V) || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_000V)  || \
                                                         ((voltage) == CY_SYSPM_SDR_VOLTAGE_1_100V))

/**
* \note
* This macro is available for CAT1B devices.
**/
/* Macro to validate number of Macros supported in SRAM0 */

#define CY_SYSPM_IS_SRAM0_MACRO_NUM_VALID(macroNum)      (((macroNum) == CY_SYSPM_SRAM0_MACRO_0)         || \
                                                         ((macroNum) == CY_SYSPM_SRAM0_MACRO_1))

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN) */


/* Macro to validate parameters in Cy_SysPm_ExecuteCallback() function */

#if defined (CY_IP_MXS40SSRSS)
#define CY_SYSPM_IS_CALLBACK_MODE_VALID(mode)           (((mode) == CY_SYSPM_CHECK_READY) || \
                                                         ((mode) == CY_SYSPM_CHECK_FAIL) || \
                                                         ((mode) == CY_SYSPM_BEFORE_TRANSITION) || \
                                                         ((mode) == CY_SYSPM_AFTER_TRANSITION) || \
                                                         ((mode) == CY_SYSPM_AFTER_DS_WFI_TRANSITION))
#else
#define CY_SYSPM_IS_CALLBACK_MODE_VALID(mode)           (((mode) == CY_SYSPM_CHECK_READY) || \
                                                          ((mode) == CY_SYSPM_CHECK_FAIL) || \
                                                          ((mode) == CY_SYSPM_BEFORE_TRANSITION) || \
                                                          ((mode) == CY_SYSPM_AFTER_TRANSITION))
#endif


/* Macro to validate parameters in Cy_SysPm_CpuEnterSleep() and for Cy_SysPm_CpuEnterDeepSleep() function */
#define CY_SYSPM_IS_WAIT_FOR_VALID(waitFor)             (((waitFor) == CY_SYSPM_WAIT_FOR_INTERRUPT) || \
                                                         ((waitFor) == CY_SYSPM_WAIT_FOR_EVENT))

/* Macro to validate parameters in Cy_SysPm_BackupSetSupply() function */
#define CY_SYSPM_IS_VDDBACKUP_VALID(vddBackControl)      (((vddBackControl) == CY_SYSPM_VDDBACKUP_DEFAULT) || \
                                                          ((vddBackControl) == CY_SYSPM_VDDBACKUP_VBACKUP))

/* Macro to validate parameters in Cy_SysPm_BackupSuperCapCharge() function */
#define CY_SYSPM_IS_SC_CHARGE_KEY_VALID(key)            (((key) == CY_SYSPM_SC_CHARGE_ENABLE) || \
                                                         ((key) == CY_SYSPM_SC_CHARGE_DISABLE))

/* Macro to validate parameters in Cy_SysPm_LdoSetMode() function */
#define CY_SYSPM_IS_LDO_MODE_VALID(key)            (((mode) == CY_SYSPM_LDO_MODE_DISABLED) || \
                                                    ((mode) == CY_SYSPM_LDO_MODE_NORMAL) || \
                                                    ((mode) == CY_SYSPM_LDO_MODE_MIN))

/* Macro to validate parameters in Cy_SysPm_WriteVoltageBitForFlash() function */
#define CY_SYSPM_IS_BIT_FOR_FLASH_VALID(value)     (((value) == CY_SYSPM_FLASH_VOLTAGE_BIT_ULP) || \
                                                    ((value) == CY_SYSPM_FLASH_VOLTAGE_BIT_LP))

/** The internal define of the SRAM PWR MACRO register key for write operation */
#define CY_SYSPM_PWR_MACRO_CTL_WRITE_KEY            (0x05FAU)

/** The internal define of the unlock value for the PMIC functions */
#define CY_SYSPM_PMIC_UNLOCK_KEY                    (0x3AU)

/** The internal define of the first wakeup pin bit used in the
* Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN0_POS                (1UL)

/** The internal define of the second wakeup pin bit
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN1_POS                (2UL)

/**
* The internal define of the first LPComparator bit
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS             (4UL)

/**
* The internal define for the second LPComparator bit
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS             (8UL)

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/**
* The internal define of the first LPComparator value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK    (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS))

/**
* The internal define of the second LPComparator value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK    (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS))

/**
* The internal define of the first wake-up pin value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN0_MASK    (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_PIN0_POS))

/**
* The internal define of the second wake-up pin value used
* in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN1_MASK    (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_PIN1_POS))

/** The internal define for the first LPComparator polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS))

/** The internal define for the second LPComparator polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS))

/** The internal define for the first wake-up pin polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_PIN0_POS))

/** The internal define for the second wake-up pin polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIB_WAKE_CTL2_HIB_WAKE_SRC, CY_SYSPM_HIB_WAKEUP_PIN1_POS))

/**
* The internal define of the WDT wakeup source
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_WDT_MASK    SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_WDT_Msk

/**
* The internal define of the WDT wakeup source
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_RTC_MASK    SRSS_PWR_HIB_WAKE_CTL_HIB_WAKE_RTC_Msk

#else

/**
* The internal define of the first LPComparator value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK    (_VAL2FLD(SRSS_PWR_HIBERNATE_MASK_HIBPIN, CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS))

/**
* The internal define of the second LPComparator value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK    (_VAL2FLD(SRSS_PWR_HIBERNATE_MASK_HIBPIN, CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS))

/**
* The internal define of the first wake-up pin value
* used in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN0_MASK    (_VAL2FLD(SRSS_PWR_HIBERNATE_MASK_HIBPIN, CY_SYSPM_HIB_WAKEUP_PIN0_POS))

/**
* The internal define of the second wake-up pin value used
* in the Cy_SysPm_SetHibernateWakeupSource() function
*/
#define CY_SYSPM_HIB_WAKEUP_PIN1_MASK    (_VAL2FLD(SRSS_PWR_HIBERNATE_MASK_HIBPIN, CY_SYSPM_HIB_WAKEUP_PIN1_POS))

/** The internal define for the first LPComparator polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS))

/** The internal define for the second LPComparator polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS))

/** The internal define for the first wake-up pin polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, CY_SYSPM_HIB_WAKEUP_PIN0_POS))

/** The internal define for the second wake-up pin polarity configuration */
#define CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK    \
                                  (_VAL2FLD(SRSS_PWR_HIBERNATE_POLARITY_HIBPIN, CY_SYSPM_HIB_WAKEUP_PIN1_POS))

#endif

/* Internal macro of all possible wakeup sources from hibernate power mode */
#define CY_SYSPM_HIB_WAKEUP_SOURSE_MASK    (CY_SYSPM_HIBERNATE_LPCOMP0_LOW | CY_SYSPM_HIBERNATE_LPCOMP0_HIGH |\
                                            CY_SYSPM_HIBERNATE_LPCOMP1_LOW | CY_SYSPM_HIBERNATE_LPCOMP1_HIGH |\
                                            CY_SYSPM_HIBERNATE_RTC_ALARM   | CY_SYSPM_HIBERNATE_WDT |\
                                            CY_SYSPM_HIBERNATE_PIN0_LOW    | CY_SYSPM_HIBERNATE_PIN0_HIGH |\
                                            CY_SYSPM_HIBERNATE_PIN1_LOW    | CY_SYSPM_HIBERNATE_PIN1_HIGH)

#if defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B & CAT1C devices.
**/
/* The mask for low power modes the power circuits (POR/BOD, Bandgap
*  reference, Reference buffer, Current reference) when active core regulator is
*  LDO
*/
#define CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_LDO_MASK    (SRSS_PWR_CTL2_LINREG_LPMODE_Msk | CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK)

/**
* \note
* This macro is available for CAT1B & CAT1C devices.
**/
/* The mask for low power modes the power circuits (POR/BOD, Bandgap
*  reference, Reference buffer, Current reference) when active core regulator is
*  Buck
*/
#define CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK    (SRSS_PWR_CTL2_PORBOD_LPMODE_Msk |\
                                                          SRSS_PWR_CTL2_REFVBUF_DIS_Msk |\
                                                          SRSS_PWR_CTL2_BGREF_LPMODE_Msk)

/**
* \note
* This macro is available for CAT1B & CAT1C devices.
**/
/* Macro to validate the word index supported in Backup Domain for Store/Restore */
#define CY_SYSPM_IS_WORD_INDEX_VALID(index)    (index < CY_SRSS_BACKUP_NUM_BREG)

/**
* \note
* This macro is available for CAT1B & CAT1C devices.
**/
/* Macro to validate number of words supported in Backup Domain for Store/Restore */
#define CY_SYSPM_IS_WORD_SIZE_VALID(size)    ((size) <= CY_SRSS_BACKUP_NUM_BREG)

#else
/* The mask for low power modes the power circuits (POR/BOD, Bandgap
*  reference, Reference buffer, Current reference) when active core regulator is
*  LDO
*/
#define CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_LDO_MASK    (SRSS_PWR_CTL_LINREG_LPMODE_Msk | CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK)

/* The mask for low power modes the power circuits (POR/BOD, Bandgap
*  reference, Reference buffer, Current reference) when active core regulator is
*  Buck
*/
#define CY_SYSPM_PWR_CIRCUITS_LPMODE_ACTIVE_BUCK_MASK    (SRSS_PWR_CTL_PORBOD_LPMODE_Msk |\
                                                          SRSS_PWR_CTL_ACT_REF_DIS_Msk |\
                                                          SRSS_PWR_CTL_VREFBUF_LPMODE_Msk |\
                                                          SRSS_PWR_CTL_IREF_LPMODE_Msk)
#endif
/** \endcond */

/**
* \defgroup group_syspm_return_status The Power Mode Status Defines
* \{
* Defines for the CPU and system power modes status.
*/

#ifdef CY_IP_M4CPUSS

/** The CM4 is in CPU Active mode */
#define CY_SYSPM_STATUS_CM4_ACTIVE       (0x01U)

/** The CM4 is in CPU Sleep mode */
#define CY_SYSPM_STATUS_CM4_SLEEP        (0x02U)

/** The CM4 is in CPU Deep Sleep mode */
#define CY_SYSPM_STATUS_CM4_DEEPSLEEP    (0x04U)

#endif

#if (__CORTEX_M == 0) || (defined (__CM0P_PRESENT) && (__CM0P_PRESENT == 1))


/** The CM0p is CPU Active mode */
#define CY_SYSPM_STATUS_CM0_ACTIVE       ((uint32_t) 0x01U << 8U)

/** The CM0p is in CPU Sleep mode */
#define CY_SYSPM_STATUS_CM0_SLEEP        ((uint32_t) 0x02U << 8U)

/** The CM0p is in CPU Deep Sleep mode */
#define CY_SYSPM_STATUS_CM0_DEEPSLEEP    ((uint32_t) 0x04U << 8U)

/** The CM0 is in low power mode */
#define CY_SYSPM_STATUS_CM0_LOWPOWER     ((uint32_t) 0x80U << 8U)

#endif


#ifdef CY_IP_M7CPUSS

/** The CM7_0 is Active */
#define CY_SYSPM_STATUS_CM7_0_ACTIVE       ((uint32_t) ((uint32_t)0x01U << 16U))

/** The CM7_0 is in Sleep */
#define CY_SYSPM_STATUS_CM7_0_SLEEP        ((uint32_t) ((uint32_t)0x02U << 16U))

/** The CM7_0 is in DeepSleep */
#define CY_SYSPM_STATUS_CM7_0_DEEPSLEEP    ((uint32_t) ((uint32_t)0x04U << 16U))

/** The CM7_0 is Low Power mode */
#define CY_SYSPM_STATUS_CM7_0_LOWPOWER     ((uint32_t) ((uint32_t)0x80U << 16U))

/** The define of retained power mode of the CM7_0 */
#define CY_SYSPM_CM7_0_PWR_CTL_PWR_MODE_RETAINED     (2U)

/** The CM7_1 is Active */
#define CY_SYSPM_STATUS_CM7_1_ACTIVE       ((uint32_t) ((uint32_t)0x01U << 24U))

/** The CM7_1 is in Sleep */
#define CY_SYSPM_STATUS_CM7_1_SLEEP        ((uint32_t) ((uint32_t)0x02U << 24U))

/** The CM7_1 is in DeepSleep */
#define CY_SYSPM_STATUS_CM7_1_DEEPSLEEP    ((uint32_t) ((uint32_t)0x04U << 24U))

/** The CM7_1 is Low Power mode */
#define CY_SYSPM_STATUS_CM7_1_LOWPOWER     ((uint32_t) ((uint32_t)0x80U << 24U))

/** The define of retained power mode of the CM7_1 */
#define CY_SYSPM_CM7_1_PWR_CTL_PWR_MODE_RETAINED     (2U)

#endif /* CY_IP_M7CPUSS */

/** The system is Low Power mode */
#define CY_SYSPM_STATUS_SYSTEM_LP        (0x80U)

/** The system is in Ultra Low Power mode */
#define CY_SYSPM_STATUS_SYSTEM_ULP       ((uint32_t) 0x08U << 8U)

/** The system is LPACTIVE Power mode */
#define CY_SYSPM_STATUS_SYSTEM_LPACTIVE  (0x08UL << 16U)

/** The wait time for transition of the device from the Active into
* the LPActive (Low Power Active)
*/
#define CY_SYSPM_ACTIVE_TO_LP_WAIT_US           (1u)

/** The wait delay time which occurs before the Active reference is settled.
* This delay is used in transition of the device from Active into the
* LPACTIVE (Low Power Active) mode
*/
#define CY_SYSPM_LP_TO_ACTIVE_WAIT_BEFORE_US    (8u)

/** The wait delay time which occurs after the Active reference is settled.
* This delay is used in transition the device from Active into the
* LPACTIVE (Low Power Active) mode
*/
#define CY_SYSPM_LP_TO_ACTIVE_WAIT_AFTER_US    (1u)

/** The internal define of the tries number in the Cy_SysPm_ExitLpMode()
* function
 */
#define CY_SYSPM_WAIT_DELAY_TRYES                        (100u)

/** \} group_syspm_return_status */

/** \} group_syspm_macros */

/*******************************************************************************
*       Configuration Structures
*******************************************************************************/

/**
* \addtogroup group_syspm_data_enumerates
* \{
*/

/** The SysPm function return value status definitions. */
typedef enum
{
    CY_SYSPM_SUCCESS         = 0x0U,                                         /**< Successful. */
    CY_SYSPM_BAD_PARAM       = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0x01U,    /**< One or more invalid parameters. */
    CY_SYSPM_TIMEOUT         = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0x02U,    /**< A time-out occurred. */
    CY_SYSPM_INVALID_STATE   = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0x03U,    /**< The operation is not setup or is in an
                                                                                  improper state. */
    CY_SYSPM_CANCELED        = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0x04U,    /**< Operation canceled. */
    CY_SYSPM_SYSCALL_PENDING = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0x05U,    /**< Canceled due syscall operation pending. */
    CY_SYSPM_FAIL            = CY_SYSPM_ID | CY_PDL_STATUS_ERROR | 0xFFU     /**< Unknown failure. */
} cy_en_syspm_status_t;

/**
* This enumeration is used to initialize the functions wait action. The wait actions can be -
* an interrupt or an event. Refer to the CMSIS for WFE and WFI instruction explanations.
*/
typedef enum
{
    CY_SYSPM_WAIT_FOR_INTERRUPT,    /**< Wait for an interrupt. */
    CY_SYSPM_WAIT_FOR_EVENT         /**< Wait for an event. */
} cy_en_syspm_waitfor_t;

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/**
* This enumeration is used to distinguish between the pre and post checks required during DS-RAM.
*/
/**
* \note
* This enum is available for CAT1B devices.
**/

typedef enum
{
    CY_SYSPM_PRE_DSRAM,             /**< Pre DSRAM Checks. */
    CY_SYSPM_POST_DSRAM             /**< Post DSRAM Checks. */
} cy_en_syspm_dsram_checks_t;
#endif

/** This enumeration is used to configure wakeup sources for the System Hibernate
*   power mode.
*/
#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/**
* \note
* This macro is available for CAT1B & CAT1C devices.
**/

typedef enum
{
    /** Wake on a low logic level for the LPComp0. */
    CY_SYSPM_HIBERNATE_LPCOMP0_LOW  = 0x1U,

    /** Wake on a high logic level for the LPComp0. */
    CY_SYSPM_HIBERNATE_LPCOMP0_HIGH = (0x1U << 1),

    /** Wake on a low logic level for the LPComp1. */
    CY_SYSPM_HIBERNATE_LPCOMP1_LOW  = (0x1U << 2),

    /** Wake on a high logic level for the LPComp1. */
    CY_SYSPM_HIBERNATE_LPCOMP1_HIGH = (0x1U << 3),

    /** Configure the RTC alarm as wakeup source. */
    CY_SYSPM_HIBERNATE_RTC_ALARM    = (0x1U << 4),

    /** Configure the WDT interrupt as wakeup source. */
    CY_SYSPM_HIBERNATE_WDT          = (0x1U << 5),

    /** Configure a low logic level for the first wakeup-pin. See device datasheet for specific pin. */
    CY_SYSPM_HIBERNATE_PIN0_LOW     = (0x1U << 6),

    /** Configure a high logic level for the first wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN0_HIGH    = (0x1U << 7),

    /** Configure a low logic level for the second wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN1_LOW     = (0x1U << 8),

    /** Configure a high logic level for the second wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN1_HIGH    = (0x1U << 9)
} cy_en_syspm_hibernate_wakeup_source_t;
#else
/**
* \note
* This macro is available for CAT1A devices.
**/
typedef enum
{
    /** Wake on a low logic level for the LPComp0. */
    CY_SYSPM_HIBERNATE_LPCOMP0_LOW  = CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK,

    /** Wake on a high logic level for the LPComp0. */
    CY_SYSPM_HIBERNATE_LPCOMP0_HIGH = CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK | CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK,

    /** Wake on a low logic level for the LPComp1. */
    CY_SYSPM_HIBERNATE_LPCOMP1_LOW  = CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK,

    /** Wake on a high logic level for the LPComp1. */
    CY_SYSPM_HIBERNATE_LPCOMP1_HIGH = CY_SYSPM_HIB_WAKEUP_LPCOMP1_MASK | CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK,

    /** Configure the RTC alarm as wakeup source. */
    CY_SYSPM_HIBERNATE_RTC_ALARM = SRSS_PWR_HIBERNATE_MASK_HIBALARM_Msk,

    /** Configure the WDT interrupt as wakeup source. */
    CY_SYSPM_HIBERNATE_WDT = SRSS_PWR_HIBERNATE_MASK_HIBWDT_Msk,

    /** Configure a low logic level for the first wakeup-pin. See device datasheet for specific pin. */
    CY_SYSPM_HIBERNATE_PIN0_LOW  = CY_SYSPM_HIB_WAKEUP_PIN0_MASK,

    /** Configure a high logic level for the first wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN0_HIGH = CY_SYSPM_HIB_WAKEUP_PIN0_MASK | CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK,

    /** Configure a low logic level for the second wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN1_LOW  = CY_SYSPM_HIB_WAKEUP_PIN1_MASK,

    /** Configure a high logic level for the second wakeup-pin. See device datasheet for specific pin.*/
    CY_SYSPM_HIBERNATE_PIN1_HIGH = CY_SYSPM_HIB_WAKEUP_PIN1_MASK | CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK
} cy_en_syspm_hibernate_wakeup_source_t;
#endif
/** This enumeration is used to select LDO regulator output voltage. */
typedef enum
{
    CY_SYSPM_LDO_VOLTAGE_ULP  = 0U,    /**< System ULP nominal LDO voltage.
                                            See device datasheet for specific voltage. */
    CY_SYSPM_LDO_VOLTAGE_LP   = 1U,    /**< System LP nominal LDO voltage.
                                            See device datasheet for specific voltage. */
    CY_SYSPM_LDO_VOLTAGE_0_9V = 0U,    /**< 0.9 V nominal LDO voltage */
    CY_SYSPM_LDO_VOLTAGE_1_1V = 1U     /**< 1.1 V nominal LDO voltage */
} cy_en_syspm_ldo_voltage_t;

/** This enumeration is used to select the LDO regulator operating mode. */
typedef enum
{
    CY_SYSPM_LDO_MODE_DISABLED = 0U,    /**< Disables the LDO. */
    CY_SYSPM_LDO_MODE_NORMAL   = 1U,    /**< Sets normal current mode. See device datasheet for
                                             specific maximum current limit. */
    CY_SYSPM_LDO_MODE_MIN      = 2U     /**< Sets minimum current mode. See device datasheet for
                                             specific  current limit.  */
} cy_en_syspm_ldo_mode_t;

/**
*  This enumeration is used to select the output voltage for the Buck regulator output 1.
*/
typedef enum
{
    CY_SYSPM_BUCK_OUT1_VOLTAGE_ULP  = 0x02U,    /**< System ULP nominal Buck voltage.
                                                     See device datasheet for specific voltage. */
    CY_SYSPM_BUCK_OUT1_VOLTAGE_LP   = 0x05U,    /**< LP nominal Buck voltage.
                                                     See device datasheet for specific voltage. */
    CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V = 0x02U,    /**< 0.9 V nominal Buck voltage */
    CY_SYSPM_BUCK_OUT1_VOLTAGE_1_1V = 0x05U     /**< 1.1 V nominal Buck voltage */
} cy_en_syspm_buck_voltage1_t;

/** This enumeration is used to select the Buck regulator outputs. */
typedef enum
{
    CY_SYSPM_BUCK_VBUCK_1 = 0x0U,    /**< Buck output 1 Voltage (Vbuck1). Typically used to
                                          supply the PSoC digital core logic. */
    CY_SYSPM_BUCK_VRF                /**< Buck out 2 Voltage (Vbuckrf). Typically used to
                                          supply the BLE radio logic. */
} cy_en_syspm_buck_out_t;

/**
* This enumeration is used to select the output voltage for the Buck regulator
* output 2, which can source the BLE radio.
*/
typedef enum
{
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_15V = 0U,    /**< 1.15 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_2V  = 1U,    /**< 1.20 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_25V = 2U,    /**< 1.25 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_3V  = 3U,    /**< 1.3 V nominal voltage.  */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_35V = 4U,    /**< 1.35 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_4V  = 5U,    /**< 1.4 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_45V = 6U,    /**< 1.45 V nominal voltage. */
    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_5V  = 7U     /**< 1.5 V nominal voltage. */
} cy_en_syspm_buck_voltage2_t;

/**
* This enumeration is used to set the polarity for the PMIC input. The PMIC output is
* automatically enabled when the configured polarity of the PMIC input and the logic level
* driven to the pmic_wakeup_in pin match.
*
* \warning
* Do not use CY_SYSPM_PMIC_POLARITY_LOW as it is not supported by hardware.
*/
typedef enum
{
    CY_SYSPM_PMIC_POLARITY_LOW   = 0U,    /**< Set active low logic level for the PMIC input. */
    CY_SYSPM_PMIC_POLARITY_HIGH  = 1U     /**< Set active high logic level for the PMIC input. */
} cy_en_syspm_pmic_wakeup_polarity_t;

/** This enumeration selects Vbackup or Vddd to supply Vddbackup. */
typedef enum
{
    CY_SYSPM_VDDBACKUP_DEFAULT         = 0U,    /**< Logic automatically selects Vddd if present or
                                                     Vbackup if Vddd is not present to supply Vddbackup */
    CY_SYSPM_VDDBACKUP_VBACKUP         = 2U     /**< Sets only Vbackup to supply Vddbackup */
} cy_en_syspm_vddbackup_control_t;

/** This enumeration enables supercapacitor charging. */
typedef enum
{
    CY_SYSPM_SC_CHARGE_ENABLE     = 0x3CU,    /**< Enables supercapacitor charging */
    CY_SYSPM_SC_CHARGE_DISABLE    = 0x00U     /**< Disables supercapacitor charging */
} cy_en_syspm_sc_charge_key_t;

/** This enumeration configures the flash voltage bit for different system power modes. */
typedef enum
{
    CY_SYSPM_FLASH_VOLTAGE_BIT_LP  = 0U,    /**< Set the flash voltage bit for system LP mode */
    CY_SYSPM_FLASH_VOLTAGE_BIT_ULP = 1U,    /**< Set the flash voltage bit for system ULP mode */
} cy_en_syspm_flash_voltage_bit_t;

/**
* This enumeration is used to select the low power mode for which the
* appropriate registered callback handler will be executed. For example,
* the registered callback of the type CY_SYSPM_SLEEP will be executed while
* switching into the Sleep power mode.
*/
typedef enum
{
    CY_SYSPM_SLEEP      = 0U,    /**< The Sleep enum callback type */
    CY_SYSPM_DEEPSLEEP  = 1U,    /**< The Deep Sleep enum callback type */
    CY_SYSPM_HIBERNATE  = 2U,    /**< The Hibernate enum callback type */
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)
    CY_SYSPM_LP         = 3U,    /**< The Low Power enum callback type, This Macro is available only for CAT1A devices */
    CY_SYSPM_ULP        = 4U,     /**< The Ultra Low Power enum callback type, This Macro is available only for CAT1A devices  */
#endif
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)
    CY_SYSPM_LPACTIVE_ENTER = 3U,    /**< The LPACTIVE (Low Power Active)/LPSLEEP (Low Power Sleep) ENTER enum callback type, This Macro is available only for CAT1B and CAT1D devices  */
    CY_SYSPM_LPACTIVE_EXIT  = 4U,    /**< The LPACTIVE  (Low Power Active)/LPSLEEP (Low Power Sleep) EXIT enum callback type, This Macro is available only for CAT1B and CAT1D devices  */
#endif
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined (CY_DOXYGEN)
    CY_SYSPM_DEEPSLEEP_RAM  = 5U,    /**< The Deep Sleep RAM enum callback type, This Macro is available only for CAT1B devices */
    CY_SYSPM_DEEPSLEEP_OFF  = 6U,    /**< The Deep Sleep OFF enum callback type, This Macro is available only for CAT1B devices */
#endif
} cy_en_syspm_callback_type_t;

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined (CY_DOXYGEN)
/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to list the available deep sleep modes.
*/
typedef enum
{
    CY_SYSPM_MODE_DEEPSLEEP        = CY_SYSPM_DEEPSLEEP,        /**< Deep Sleep Mode. */
    CY_SYSPM_MODE_DEEPSLEEP_RAM    = CY_SYSPM_DEEPSLEEP_RAM,    /**< Deep Sleep RAM Mode. */
    CY_SYSPM_MODE_DEEPSLEEP_OFF    = CY_SYSPM_DEEPSLEEP_OFF,    /**< Deep Sleep OFF Mode. */
    CY_SYSPM_MODE_DEEPSLEEP_NONE   = CY_SYSPM_SLEEP,                     /**< Not Deep Sleep Mode. */
} cy_en_syspm_deep_sleep_mode_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to list the available wakeup modes after deepsleep.
*/
typedef enum
{
    CY_SYSPM_WARM_BOOT_MODE      = 0,    /**< Warm Boot - After DEEPSLEEP-RAM. */
    CY_SYSPM_COLD_BOOT_MODE      = 1,    /**< Cold Boot - After DEEPSLEEP-OFF. */
    CY_SYSPM_POR_BOOT_MODE       = 2,    /**< POR Boot  - After POR Wakeup. */
} cy_en_syspm_boot_mode_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to select the mode for the
* Core Buck regulator.
*/
typedef enum
{
    CY_SYSPM_CORE_BUCK_MODE_LP    = 0x01U,    /**< Low Power Mode. */
    CY_SYSPM_CORE_BUCK_MODE_HP    = 0x11U,    /**< High Power Mode(Low Ripple Mode) */
} cy_en_syspm_core_buck_mode_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to select the Inrush limit for the
* Core Buck regulator.
*/
typedef enum
{
    CY_SYSPM_CORE_BUCK_INRUSH_LIMIT_10    = 0U,    /**< Inrush limit : 10mA. */
    CY_SYSPM_CORE_BUCK_INRUSH_LIMIT_100   = 1U,    /**< Inrush limit : 100mA. */
} cy_en_syspm_core_inrush_limit_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to select the output voltage for the
* Core Buck regulator output.
*/
typedef enum
{
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_76V = 0U,    /**< 0.76 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_78V = 1U,    /**< 0.78 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_80V = 2U,    /**< 0.80 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_82V = 3U,    /**< 0.82 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_84V = 4U,    /**< 0.84 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_86V = 5U,    /**< 0.86 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_88V = 6U,    /**< 0.88 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_90V = 7U,    /**< 0.90 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_92V = 8U,    /**< 0.92 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_94V = 9U,    /**< 0.94 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_96V = 10U,    /**< 0.96 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_0_98V = 11U,    /**< 0.98 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_00V = 12U,    /**< 1.00 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_02V = 13U,    /**< 1.02 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_04V = 14U,    /**< 1.04 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_06V = 15U,    /**< 1.06 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_08V = 16U,    /**< 1.08 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_10V = 17U,    /**< 1.10 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_12V = 18U,    /**< 1.12 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_14V = 19U,    /**< 1.14 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_16V = 20U,    /**< 1.16 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_18V = 21U,    /**< 1.18 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_20V = 22U,    /**< 1.20 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_22V = 23U,    /**< 1.22 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_24V = 24U,    /**< 1.24 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_26V = 25U,    /**< 1.26 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_28V = 26U,    /**< 1.28 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_30V = 27U,    /**< 1.30 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_32V = 28U,    /**< 1.32 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_34V = 29U,    /**< 1.34 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_36V = 30U,    /**< 1.36 V nominal voltage. */
    CY_SYSPM_CORE_BUCK_VOLTAGE_1_38V = 31U,    /**< 1.38 V nominal voltage. */
} cy_en_syspm_core_buck_voltage_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* For SDR's(Step Down Regulators), this enumeration is used to select the SDR0 or SDR1
*/
typedef enum
{
    CY_SYSPM_SDR_0              = 0U,    /**< SDR0 */
    CY_SYSPM_SDR_1              = 1U,    /**< SDR1 */
} cy_en_syspm_sdr_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to select the output voltage for the
* SDR(Step Down Regulator) output.
*/
typedef enum
{
    CY_SYSPM_SDR_VOLTAGE_0_850V = 0U,    /**< 0.850 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_0_875V = 1U,    /**< 0.875 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_0_900V = 2U,    /**< 0.900 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_0_925V = 3U,    /**< 0.925 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_0_950V = 4U,    /**< 0.950 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_0_975V = 5U,    /**< 0.975 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_000V = 6U,    /**< 1.000 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_025V = 7U,    /**< 1.025 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_050V = 8U,    /**< 1.050 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_075V = 9U,    /**< 1.075 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_100V = 10U,   /**< 1.100 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_125V = 11U,   /**< 1.125 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_150V = 12U,   /**< 1.150 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_175V = 13U,   /**< 1.175 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_200V = 14U,   /**< 1.200 V nominal voltage. */
    CY_SYSPM_SDR_VOLTAGE_1_225V = 15U,   /**< 1.225 V nominal voltage. */
} cy_en_syspm_sdr_voltage_t;

/**
* \note
* This enum is available for CAT1B devices.
**/
/**
* This enumeration is used to select the output voltage for the
* HVLDO Regulator.
*/
typedef enum
{
    CY_SYSPM_HVLDO_VOLTAGE_1_500V = 0U,     /**< 1.500 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_1_600V = 1U,     /**< 1.600 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_1_700V = 2U,     /**< 1.700 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_1_800V = 3U,     /**< 1.800 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_1_900V = 4U,     /**< 1.900 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_000V = 5U,     /**< 2.000 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_100V = 6U,     /**< 2.100 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_200V = 7U,     /**< 2.200 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_300V = 8U,     /**< 2.300 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_400V = 9U,     /**< 2.400 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_500V = 10U,    /**< 2.500 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_600V = 11U,    /**< 2.600 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_700V = 12U,    /**< 2.700 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_800V = 13U,    /**< 2.800 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_2_900V = 14U,    /**< 2.900 V nominal voltage. */
    CY_SYSPM_HVLDO_VOLTAGE_3_000V = 15U,    /**< 3.000 V nominal voltage. */
} cy_en_syspm_hvldo_voltage_t;


#endif


#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)
/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects the voltage threshold for OVD on VDDD
*/
typedef enum
{
    CY_SYSPM_OVD_VDDD_5_5V      = 0x0u,       /**< OVD -> VDDD > 5.5 V */
    CY_SYSPM_OVD_VDDD_5_0V      = 0x01u       /**< OVD -> VDDD > 5.0 V  */
} cy_en_syspm_ovd_vddd_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects the voltage threshold for OVD on VDDA
*/
typedef enum
{
    CY_SYSPM_OVD_VDDA_5_5V      = 0x0u,                    /**< OVD -> VDDA > 5.5 V */
    CY_SYSPM_OVD_VDDA_5_0V      = 0x01u                 /**< OVD -> VDDA > 5.0 V  */
} cy_en_syspm_ovd_vdda_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects OVD over VDDD or VDDA or VCCD
*/
typedef enum
{
    CY_SYSPM_OVD_ON_VDDD        = 0x0u,                 /**< OVD -> VDDD */
    CY_SYSPM_OVD_ON_VDDA        = 0x01u,                /**< OVD -> VDDA */
    CY_SYSPM_OVD_ON_VCCD        = 0x02u                 /**< OVD -> VCCD */
} cy_en_syspm_ovd_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
 * OVD action select configuration.
 */
typedef enum
{
    CY_SYSPM_OVD_ACTION_NOTHING = 0x0u,              /**<Select OVD action select: nothing */
    CY_SYSPM_OVD_ACTION_FAULT   = 0x1u,              /**<Select OVD action select: fault */
    CY_SYSPM_OVD_ACTION_RESET   = 0x2u,              /**<Select OVD action select: reset */
} cy_en_syspm_ovd_action_select_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects the voltage threshold for BOD on VDDD
*/
typedef enum
{
    CY_SYSPM_BOD_VDDD_2_7V      = 0x0u,                 /**< BOD -> VDDD < 2.7 V */
    CY_SYSPM_BOD_VDDD_3_0V      = 0x01u               /**< BOD -> VDDD < 3.0 V  */
} cy_en_syspm_bod_vddd_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects the voltage threshold for BOD on VDDA
*/
typedef enum
{
    CY_SYSPM_BOD_VDDA_2_7V      = 0x0u,                    /**< BOD -> VDDA < 2.7 V */
    CY_SYSPM_BOD_VDDA_3_0V      = 0x01u                 /**< BOD -> VDDA < 3.0 V  */
} cy_en_syspm_bod_vdda_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
* Selects BOD over VDDD or VDDA or VCCD
*/
typedef enum
{
    CY_SYSPM_BOD_ON_VDDD        = 0x0u,                 /**< BOD -> VDDD */
    CY_SYSPM_BOD_ON_VDDA        = 0x01u,                /**< BOD -> VDDA */
    CY_SYSPM_BOD_ON_VCCD        = 0x02u                 /**< BOD -> VCCD */
} cy_en_syspm_bod_sel_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
 * BOD action select configuration.
 */
typedef enum
{
    CY_SYSPM_BOD_ACTION_NOTHING = 0x0u,              /**<Select BOD action select: nothing */
    CY_SYSPM_BOD_ACTION_FAULT   = 0x1u,              /**<Select BOD action select: fault */
    CY_SYSPM_BOD_ACTION_RESET   = 0x2u,              /**<Select BOD action select: reset */
} cy_en_syspm_bod_action_select_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/**
 * Supply Supervision Status
 */
typedef enum
{
    CY_SYSPM_ENTITY_BOD_VDDD    = 0x0u,              /**<BOD indicates VDDD is OK */
    CY_SYSPM_ENTITY_BOD_VDDA    = 0x1u,              /**<BOD indicates VDDA is OK */
    CY_SYSPM_ENTITY_BOD_VCCD    = 0x2u,              /**<BOD indicates VCCD is OK */
    CY_SYSPM_ENTITY_OVD_VDDD    = 0x3u,              /**<OVD indicates VDDD is OK */
    CY_SYSPM_ENTITY_OVD_VDDA    = 0x4u,              /**<OVD indicates VDDA is OK */
    CY_SYSPM_ENTITY_OVD_VCCD    = 0x5u,              /**<OVD indicates VCCD is OK */
} cy_en_syspm_supply_entity_select_t;


/**
* \note
* This enum is available for CAT1C devices.
**/
/** This enumeration is used to select the REGHC mode */
typedef enum
{
    CY_SYSPM_REGHC_MODE_TRANSISTOR = 0u, /**< External Transistor Mode */
    CY_SYSPM_REGHC_MODE_PMIC       = 1u, /**< External PMIC Mode */
} cy_en_syspm_reghc_mode_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/** This enumeration is used to set the voltage trims */
typedef enum
{
    CY_SYSPM_REGHC_VADJ_1_020V =  0u,    /**< 1.020 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_025V =  1u,    /**< 1.025 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_030V =  2u,    /**< 1.030 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_035V =  3u,    /**< 1.035 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_040V =  4u,    /**< 1.040 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_045V =  5u,    /**< 1.045 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_050V =  6u,    /**< 1.050 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_055V =  7u,    /**< 1.055 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_060V =  8u,    /**< 1.060 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_065V =  9u,    /**< 1.065 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_070V = 10u,    /**< 1.070 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_075V = 11u,    /**< 1.075 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_080V = 12u,    /**< 1.080 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_085V = 13u,    /**< 1.085 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_090V = 14u,    /**< 1.090 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_095V = 15u,    /**< 1.095V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_100V = 16u,    /**< Default Value, 1.100 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_105V = 17u,    /**< 1.105 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_110V = 18u,    /**< 1.110 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_115V = 19u,    /**< 1.115 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_120V = 20u,    /**< 1.120 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_125V = 21u,    /**< 1.125 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_130V = 22u,    /**< 1.130 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_135V = 23u,    /**< 1.135 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_140V = 24u,    /**< 1.140 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_145V = 25u,    /**< 1.145 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_150V = 26u,    /**< 1.150 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_155V = 27u,    /**< 1.155 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_160V = 28u,    /**< 1.160 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_165V = 29u,    /**< 1.165 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_170V = 30u,    /**< 1.170 V nominal voltage. */
    CY_SYSPM_REGHC_VADJ_1_175V = 31u,    /**< 1.175 V nominal voltage. */
} cy_en_syspm_reghc_vadj_t;

/**
* \note
* This enum is available for CAT1C devices.
**/
/** Drive out configuration */
typedef enum
{
    CY_SYSPM_REGHC_DRIVE_OUT_0P9_VCCD_BY_VADJ  = 0u,    /**< DRV_VOUT=(0.9 * vccd)/vdj Volts */
    CY_SYSPM_REGHC_DRIVE_OUT_0P8_VCCD_BY_VADJ  = 1u,    /**< DRV_VOUT=(0.8 * vccd)/vdj Volts */
    CY_SYSPM_REGHC_DRIVE_OUT_0P6_VCCD_BY_VADJ  = 2u,    /**< DRV_VOUT=(0.6 * vccd)/vdj Volts */
    CY_SYSPM_REGHC_DRIVE_OUT_VCCD              = 3u,    /**< DRV_VOUT=vccd Volts */
} cy_en_syspm_reghc_drive_out_t;

#endif

/**
* For SRAM0, this enumeration represents the Macro Numbers
*/
typedef enum
{
    CY_SYSPM_SRAM0_MACRO_0              = 0U,    /**< SRAM0:Macro-0 */
    CY_SYSPM_SRAM0_MACRO_1              = 1U,    /**< SRAM0:Macro-1 */
} cy_en_syspm_sram0_macro_t;



/** This enumeration specifies the associated callback mode. This enum defines the callback mode. */
typedef enum
{
    CY_SYSPM_CHECK_READY        = 0x01U,    /**< Callbacks with this mode are executed before entering into the
                                                 low power mode. The purpose of his callback function is to check
                                                 if the device is ready to enter the low power mode. */
    CY_SYSPM_CHECK_FAIL         = 0x02U,    /**< Callbacks with this mode are executed after the CY_SYSPM_CHECK_READY
                                                 callbacks execution returns CY_SYSPM_FAIL.
                                                 The callback with the CY_SYSPM_CHECK_FAIL mode should roll back the
                                                 actions performed in the previously executed callback with
                                                 CY_SYSPM_CHECK_READY */
    CY_SYSPM_BEFORE_TRANSITION  = 0x04U,    /**< Callbacks with this mode are executed after the CY_SYSPM_CHECK_READY
                                                 callbacks execution returns CY_SYSPM_SUCCESS.
                                                 Performs the actions to be done before entering into the
                                                 low power mode. */
    CY_SYSPM_AFTER_TRANSITION         = 0x08U,     /**< Performs the actions to be done after exiting the low power mode
                                                 if entered. */
#if defined (CY_IP_MXS40SSRSS)
    /**
     * \note
     * Below enum should be used only during exit of Deepsleep and applicable for only CAT1B devices
     **/
    CY_SYSPM_AFTER_DS_WFI_TRANSITION  = 0x10U,    /**< Performs the actions to be done after exiting the Deepsleep low
                                                     power mode if entered and before the interrupts are enabled. */
#endif
} cy_en_syspm_callback_mode_t;

/**
* This enumeration is used to select a particular SRAM.
*/
typedef enum
{
    CY_SYSPM_SRAM0_MEMORY      = 0U,    /**< SRAM0 Memory Area */
    CY_SYSPM_SRAM1_MEMORY      = 1U,    /**< SRAM1 Memory Area */
    CY_SYSPM_SRAM2_MEMORY      = 2U,    /**< SRAM2 Memory Area */
} cy_en_syspm_sram_index_t;

/**
* This enumeration is used to select a particular SRAM Power Mode.
*/
typedef enum
{
    CY_SYSPM_SRAM_PWR_MODE_OFF      = 0U,   /**< SRAM Power Mode OFF */
    CY_SYSPM_SRAM_PWR_MODE_INVALID  = 1U,   /**< Invalid SRAM Power Mode */
    CY_SYSPM_SRAM_PWR_MODE_RET      = 2U,   /**< SRAM Power Mode RET */
    CY_SYSPM_SRAM_PWR_MODE_ON       = 3U    /**< SRAM Power Mode ON */
} cy_en_syspm_sram_pwr_mode_t;
/** \} group_syspm_data_enumerates */

/**
* \addtogroup group_syspm_macros
* \{
*/
/**
* \defgroup group_syspm_skip_callback_modes Defines to skip the callbacks modes
* \{
* Defines for the SysPm callbacks modes that can be skipped during execution.
* For more information about callbacks modes, refer
* to \ref cy_en_syspm_callback_mode_t.
*/
#define CY_SYSPM_SKIP_CHECK_READY                   (0x01U)   /**< Define to skip check ready mode in the syspm callback */
#define CY_SYSPM_SKIP_CHECK_FAIL                    (0x02U)   /**< Define to skip check fail mode in the syspm callback */
#define CY_SYSPM_SKIP_BEFORE_TRANSITION             (0x04U)   /**< Define to skip before transition mode in the syspm callback */
#define CY_SYSPM_SKIP_AFTER_TRANSITION              (0x08U)   /**< Define to skip after transition mode in the syspm callback */
/** \} group_syspm_skip_callback_modes */
/** \} group_syspm_macros */

/**
* \addtogroup group_syspm_data_structures
* \{
*/

/** The structure contains syspm callback parameters */
typedef struct
{
    void *base;         /**< Base address of a HW instance, matches name of the driver in
                             the API for the base address. Can be undefined if not required. Base address is not
                             required for the SysPm driver as the device has only one set of power modes */
    void *context;      /**< Context for the handler function. This item can be
                             skipped if not required. Can be undefined if not required. */

} cy_stc_syspm_callback_params_t;

/** The type for syspm callbacks */
typedef cy_en_syspm_status_t (*Cy_SysPmCallback) (cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);

/** Structure with syspm callback configuration elements */
typedef struct cy_stc_syspm_callback
{
    Cy_SysPmCallback callback;                         /**< The callback handler function. */
    cy_en_syspm_callback_type_t type;                  /**< The callback type, see \ref cy_en_syspm_callback_type_t. */
    uint32_t skipMode;                                 /**< The mask of modes to be skipped during callback
                                                            execution, see \ref group_syspm_skip_callback_modes. The
                                                            corresponding callback mode won't execute if the
                                                            appropriate define is set. These values can be ORed.
                                                            If all modes are required to be executed this element
                                                            should be equal to zero. Skipping unneeded callback modes speeds up
                                                            power mode transitions by skipping unneeded operations. */

    cy_stc_syspm_callback_params_t *callbackParams;    /**< The address of a cy_stc_syspm_callback_params_t,
                                                            the callback is executed with these parameters. */

    struct cy_stc_syspm_callback *prevItm;             /**< The previous list item. This element should not be
                                                            defined, or defined as NULL. It is for internal
                                                            usage to link this structure to the next registered
                                                            structure. It will be updated during callback
                                                            registration. Do not modify this element at run-time. */

    struct cy_stc_syspm_callback *nextItm;             /**< The next list item. This element should not be
                                                            defined, or defined as NULL. It is for internal usage to
                                                            link this structure to the previous registered structure.
                                                            It will be updated during callback registration. Do not
                                                            modify this element at run-time. */
    uint8_t order;                                     /**< Holds the callback execution order value. Range: 0-255.
                                                            While entering low power mode, callbacks with lower order values
                                                            are executed first. While exiting low power mode,
                                                            the callbacks are executed in the opposite order.
                                                            Callbacks with the same order value are executed in the
                                                            order they are registered in the application. */
} cy_stc_syspm_callback_t;

#if defined (CY_IP_MXS40SRSS)
/**
* \note
* This enum is available for CAT1A devices.
**/
/** This internal structure stores non-retained registers in the system Deep Sleep
*   power mode. On wakeup from system Deep Sleep, these registers are restored.
*/
typedef struct
{

    uint32_t CY_SYSPM_UDB_UDBIF_BANK_CTL_REG;    /**< UDB interface control register */

    uint32_t CY_SYSPM_UDB_BCTL_MDCLK_EN_REG;    /**< UDB bank MDCLK_EN register */
    uint32_t CY_SYSPM_UDB_BCTL_MBCLK_EN_REG;    /**< UDB bank MBCLK_EN register */
    uint32_t CY_SYSPM_UDB_BCTL_BOTSEL_L_REG;    /**< UDB bank BOTSEL_L register */
    uint32_t CY_SYSPM_UDB_BCTL_BOTSEL_U_REG;    /**< UDB bank BOTSEL_U register */
    uint32_t CY_SYSPM_UDB_BCTL_QCLK_EN0_REG;    /**< UDB bank QCLK_EN0 register */
    uint32_t CY_SYSPM_UDB_BCTL_QCLK_EN1_REG;    /**< UDB bank QCLK_EN1 register */
    uint32_t CY_SYSPM_UDB_BCTL_QCLK_EN2_REG;    /**< UDB bank QCLK_EN2 register */
    uint32_t CY_SYSPM_CM0_CLOCK_CTL_REG;        /**< CPUSS CM0+ clock control register */
    uint32_t CY_SYSPM_CM4_CLOCK_CTL_REG;        /**< CPUSS CM4 clock control register */
} cy_stc_syspm_backup_regs_t;
#endif /* CY_IP_MXS40SRSS */

#if (defined(CY_DEVICE_SECURE))
/** PRA structure for Cy_SysPm_BuckSetVoltage2 function parameters */
typedef struct
{
    cy_en_syspm_buck_voltage2_t praVoltage;     /**< The voltage of the Buck regulator output 2 */
    bool praWaitToSettle;                       /**< Enable/disable the delay after setting a higher voltage */
} cy_stc_pra_voltage2_t;

typedef struct
{
    cy_en_syspm_sram_index_t sramNum;           /**< SRAM index */
    uint32_t sramMacroNum;                      /**< SRAM macro number */
    cy_en_syspm_sram_pwr_mode_t sramPwrMode;    /**< Power mode */
} cy_stc_pra_sram_power_mode_config_t;

#endif /* (defined(CY_DEVICE_SECURE)) */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/**
* \note
* This structure is available for CAT1B devices.
**/
/** The structure contains warmboot entry point struct used during DEEPSLEEP-RAM entry*/
typedef struct
{
    uint32_t *stack_pointer;      /**< Stack Pointer */
    uint32_t *entry_pointer;      /**< Entry Function Address */
} cy_stc_syspm_warmboot_entrypoint_t;

/**
* \note
* This structure is available for CAT1B devices.
**/
/** The structure contains syspm core buck configuration parameters */
typedef struct
{
    uint8_t   voltageSel;      /**< Core Buck Voltage Select \ref cy_en_syspm_core_buck_voltage_t */
    uint8_t   mode;            /**< Core Buck Mode :
                                    0x01 - Low Power Mode,
                                    0x11 - High Power Mode(Low Ripple Mode) */
    bool      override;        /**< Core Buck Override : Forces Corebuck to
                                    use the setting in the PWR_CBUCK_CTL register */
    bool      copySettings;    /**< Core Buck Copy Settings :
                                    Copies the current CBUCK composite state to
                                    PWR_CBUCK_CTL register */
    bool      useSettings;     /**< Core Buck use Settings :
                                    Causes the settings in PWR_CBUCK_CTL to be
                                    used in CBUCK settings decision */
    uint8_t   inRushLimitSel;  /**< Core Buck In Rush Limit Selection
                                    0: 10mA  limit
                                    1: 100mA limit */
} cy_stc_syspm_core_buck_params_t;

/**
* \note
* This structure is available for CAT1B devices.
**/
/** The structure contains syspm SDR0/SDR1(Step Down Regulator) LDO configuration parameters */
typedef struct
{
    uint8_t   coreBuckVoltSel;     /**< Core Buck Voltage Select \ref cy_en_syspm_core_buck_voltage_t */
    uint8_t   coreBuckMode;        /**< Core Buck Mode :
                                    0x01 - Low Power Mode,
                                    0x11 - High Power Mode(Low Ripple Mode) */

    /* This field applicable only for SDR0 */
    uint8_t   coreBuckDpSlpVoltSel; /**< Deep Sleep Core Buck Voltage Select \ref cy_en_syspm_core_buck_voltage_t */

    /* This field applicable only for SDR0 */
    uint8_t   coreBuckDpSlpMode;    /**< Deep sleep Core Buck Mode :
                                     0x01 - Low Power Mode,
                                     0x11 - High Power Mode(Low Ripple Mode) */

    uint8_t   sdrVoltSel;           /**< SDR Regulator Voltage Select \ref cy_en_syspm_sdr_voltage_t */

    /* This field applicable only for SDR0 */
    uint8_t   sdr0DpSlpVoltSel;     /**< SDR Regulator Voltage Select \ref cy_en_syspm_sdr_voltage_t */

    /* This field applicable only for SDR0 */
    bool      sdr0Allowbypass;      /**< Allow SDR bypass :
                                     true  - Allow SDR to bypass
                                     false - SDR is not bypassed and will regulate */
    /* This field applicable only for SDR1 */
    bool      sdr1HwControl;        /**< Allow SDR1 HW Control :
                                     true  - sdr1Enable(bit: SDR1_ENABLE) is ignored, HW will control
                                     false - sdr1Enable(bit: SDR1_ENABLE) will control, HW control is ignored */
    /* This field applicable only for SDR1 */
    bool      sdr1Enable;           /**<  SDR1 Enable/Disable:
                                     true  - SDR1 is enabled
                                     false - SDR1 is disabled */
} cy_stc_syspm_sdr_params_t;

/**
* \note
* This structure is available for CAT1B devices.
**/
/** The structure contains syspm HVLDO configuration parameters */
typedef struct
{
    uint8_t   voltageSel;      /**< HVLDO Voltage Select \ref cy_en_syspm_hvldo_voltage_t */
    bool      hwSel;           /**< HVLDO HW Select :
                                    0 - HVLDO0_ENABLE controls SDR1,HW controls are ignored
                                    1 - HLDO0_ENABLE is ignored and HW signal is used instead */
    bool      hvldoEnable;     /**< HVLDO Enable/Disable:
                                    true - HVLDO is enabled
                                    false - HVLDO is disabled */
} cy_stc_syspm_hvldo_params_t;


/**
* \note
* This structure is available for CAT1B devices.
**/
/** The structure contains syspm Extra Requestor configuration parameters */
typedef struct
{
    uint8_t   coreBuckVoltSel; /**< Core Buck Voltage Select \ref cy_en_syspm_core_buck_voltage_t */
    uint8_t   coreBuckMode;    /**< Core Buck Mode :
                                    0x00 - Low Power Mode,
                                    0x10 - Low Ripple(high power) */
    cy_stc_syspm_sdr_params_t *sdr0Config; /**< SDR-0 Parameters \ref cy_stc_syspm_sdr_params_t */
    cy_stc_syspm_sdr_params_t *sdr1Config; /**< SDR-1 Parameters \ref cy_stc_syspm_sdr_params_t */
} cy_stc_syspm_extraReq_params_t;

#endif

/** \} group_syspm_data_structures */

/**
* \addtogroup group_syspm_functions
* \{
*/

/**
* \addtogroup group_syspm_functions_general
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysPm_SetSRAMMacroPwrMode
****************************************************************************//**
*
* Function to set Power Mode for each of the Macro in a particular SRAM.
*
* \param sramNum
* SRAM's index number has to be passed
* ex: CY_SYSPM_SRAM0_MEMORY or CY_SYSPM_SRAM1_MEMORY or CY_SYSPM_SRAM2_MEMORY
* See \ref cy_en_syspm_sram_index_t.
*
* \param sramMacroNum
* Macro number of a particular SRAM.
*
* \note
* If SRAM1 and SRAM2 consists of single power partition, power mode will be
* applied to whole SRAM region, so 0 must be passed for sramMacroNum parameter.
*
* \param sramPwrMode
* Power Mode that needs to be set.
*
* \return
* - CY_SYSPM_SUCCESS - SRAM MACRO power mode is set.
* - CY_SYSPM_BAD_PARAM - Input parameters are out of range.
* See \ref cy_en_syspm_status_t.
*
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode);

/*******************************************************************************
* Function Name: Cy_SysPm_GetSRAMMacroPwrMode
****************************************************************************//**
*
* Function to get Power Mode for each of the Macro in a particular SRAM.
*
* \param sramNum
* SRAM's index number has to be passed
* ex: CY_SYSPM_SRAM0_MEMORY or CY_SYSPM_SRAM1_MEMORY or CY_SYSPM_SRAM2_MEMORY
* See \ref cy_en_syspm_sram_index_t.
*
* \param sramMacroNum
* Macro number of a particular SRAM.
*
* \note
* If SRAM1 and SRAM2 consists of single power partition, power mode will be
* applied to whole SRAM region, so 0 must be passed for sramMacroNum parameter,
* and the power mode obtained will be for whole SRAM.
*
* \return
* Returns SRAM power mode. See \ref cy_en_syspm_sram_pwr_mode_t.
*
*******************************************************************************/
cy_en_syspm_sram_pwr_mode_t Cy_SysPm_GetSRAMMacroPwrMode(cy_en_syspm_sram_index_t sramNum, uint32_t sramMacroNum);

/*******************************************************************************
* Function Name: Cy_SysPm_SetSRAMPwrMode
****************************************************************************//**
*
* Function to set Power Mode for all the Macros for a particular SRAM.
*
* \param sramNum
* SRAM's index number has to be passed
* ex: CY_SYSPM_SRAM0_MEMORY or CY_SYSPM_SRAM1_MEMORY or CY_SYSPM_SRAM2_MEMORY
* See \ref cy_en_syspm_sram_index_t.
*
* \param sramPwrMode
* Power Mode that needs to be set.
*
* \return
* - CY_SYSPM_SUCCESS - SRAM power mode is set.
* - CY_SYSPM_BAD_PARAM - Input parameters are out of range.
* See \ref cy_en_syspm_status_t.
*
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SetSRAMPwrMode(cy_en_syspm_sram_index_t sramNum, cy_en_syspm_sram_pwr_mode_t sramPwrMode);

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_WriteVoltageBitForFlash
****************************************************************************//**
*
* Function that changes the voltage setting for flash.
*
* \note
* Call this function before system enters ULP mode. Call this function after
* the system enters LP mode.
*
* \param value
* Value to be set in the flash voltage control register.
* See \ref cy_en_syspm_flash_voltage_bit_t.
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_WriteVoltageBitForFlash
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_WriteVoltageBitForFlash(cy_en_syspm_flash_voltage_bit_t value);

#if !((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE)))

/*******************************************************************************
* Function Name: Cy_SysPm_SaveRegisters
****************************************************************************//**
*
* \note Behavior of this API is IP dependent. \n
* On CAT1A devices: \n
* Saves non-retained UDB registers and the slow and fast clock dividers before
* system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB
* array.
* Cypress ID #280370, #1451.
* On CAT1B devices: \n
* Saves non-retained UDB registers before system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB
* array.
* Cypress ID #280370.
* \warning
* Only one CPU on dual CPU devices should call this function. If both CPUs call
* this function the UDB state restored may be inconsistent with the expected
* state when restored.
*
* \param regs
* The structure where the registers are saved.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SaveRestoreRegisters
*
*******************************************************************************/
void Cy_SysPm_SaveRegisters(cy_stc_syspm_backup_regs_t *regs);


/*******************************************************************************
* Function Name: Cy_SysPm_RestoreRegisters
****************************************************************************//**
*
* \note Behavior of this API is IP dependent. \n
* On CAT1A devices: \
* Restores non-retained UDB registers and the slow and fast clock dividers
* before system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB
* array.
* Cypress ID #280370, #1451.
* On CAT1B devices: \
* Restores non-retained UDB registers before system entering system Deep Sleep.
* Must be called if programmable logic or function are implemented in the UDB
* array.
* Cypress ID #280370.
* \warning
* Only one CPU on dual CPU devices should call this function. If both CPUs call
* this function the UDB state restored may be inconsistent with the expected
* state when restored.
*
* \param regs
* The structure with data stored (using Cy_SysPm_SaveRegisters()) into the
* required registers after Deep Sleep.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SaveRestoreRegisters
*
*******************************************************************************/
void Cy_SysPm_RestoreRegisters(cy_stc_syspm_backup_regs_t const *regs);

#endif /* !((CY_CPU_CORTEX_M4) && (defined (CY_DEVICE_SECURE))) */
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */

/** \} group_syspm_functions_general */


/**
* \addtogroup group_syspm_functions_power_status
* \{
*/


#if defined (CY_IP_MXS40SRSS)
/*******************************************************************************
* Function Name: Cy_SysPm_ReadStatus
****************************************************************************//**
*
* Reads the power modes status of the system and CPU(s).
*
* \return
* The current power mode. See \ref group_syspm_return_status.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_ReadStatus
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
uint32_t Cy_SysPm_ReadStatus(void);
/** \} group_syspm_functions_power_status */
#endif


/**
* \addtogroup group_syspm_functions_power
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysPm_CpuEnterSleep
****************************************************************************//**
*
* Sets executing CPU to Sleep mode.
*
* Puts the CPU executing this function into CPU Sleep power mode. If callback
* functions were registered they are also executed.
*
* For more detail about switching into CPU Sleep power mode and debug,
* refer to the device technical reference manual (TRM).
*
* If at least one callback function with the CY_SYSPM_SLEEP type was registered,
* the following algorithm is executed:
* Prior to entering CPU Sleep mode, all callback functions of the CY_SYSPM_SLEEP
* type with the CY_SYSPM_CHECK_READY parameter are called. This allows the
* driver to signal whether it is ready to enter the low power mode. If any of
* the callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_READY
* parameter returns CY_SYSPM_FAIL, the remaining callbacks of the
* CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_READY parameter are skipped.
* After the first CY_SYSPM_FAIL, all the CY_SYSPM_SLEEP callbacks that were
* previously executed before getting the CY_SYSPM_CHECK_FAIL are executed with
* the CY_SYSPM_CHECK_FAIL parameter. The CPU Sleep mode is not entered and the
* Cy_SysPm_CpuEnterSleep() function returns CY_SYSPM_FAIL.
*
* If all of the callbacks of the CY_SYSPM_SLEEP type with the
* CY_SYSPM_CHECK_READY parameter return CY_SYSPM_SUCCESS, then all
* callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_CHECK_FAIL parameters
* calls are skipped. All callbacks of the CY_SYSPM_SLEEP type and then
* CY_SYSPM_BEFORE_TRANSITION parameter calls are executed, allowing the
* peripherals to prepare for CPU Sleep. The CPU then enters Sleep mode.
* This is a CPU-centric power mode. This means that the CPU has entered Sleep
* mode and its main clock is removed. Any enabled interrupt can cause a CPU
* wakeup from Sleep mode.
*
* For multi-core devices, CPU wakeup can also be performed using the Send Event
* (SEV) assembly instruction executed from the other active CPU. Such wakeup is
* expected only if the CPU Sleep power mode is done with WFE assembly
* instruction.
*
* After a wakeup from CPU Sleep, all of the registered callbacks of the
* CY_SYSPM_SLEEP type and with the CY_SYSPM_AFTER_TRANSITION parameter are
* executed to return the peripherals to CPU active operation.
* The Cy_SysPm_CpuEnterSleep() function returns CY_SYSPM_SUCCESS.
* No callbacks of the CY_SYSPM_SLEEP type with the CY_SYSPM_BEFORE_TRANSITION
* parameter or callbacks of the CY_SYSPM_SLEEP type and
* CY_SYSPM_AFTER_TRANSITION parameter callbacks are executed if CPU Sleep mode
* is not entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* To support control of callback execution order th following method is
* implemented. Callback function with the CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they
* are registered.

* The return value from executed callback functions with the
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* \ref cy_en_syspm_callback_mode_t, except the CY_SYSPM_CHECK_READY, are ignored
*
* \note The Arm BSD assembly instruction is not required in this function
* because the function implementation ensures the SLEEPDEEP bit of SCS register
* is settled prior executing WFI/WFE instruction.
*
* \param waitFor
* Selects wait for action. See \ref cy_en_syspm_waitfor_t.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
*
* \sideeffect
* For CY8C6xx6, CY8C6xx7 devices this function clears the Event Register of the
* CM4 CPU after wakeup from WFE.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_CpuEnterSleep
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CpuEnterSleep(cy_en_syspm_waitfor_t waitFor);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_Init
****************************************************************************//**
*
* Initializes SysPm Driver
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_Init(void);
#endif

#if defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_IsLpmReady
****************************************************************************//**
*
* Checks if the system is LPM ready.
*
* \return
* - True if the system is LPM Ready.
* - False if the system is not LPM Ready.
*
*******************************************************************************/
bool Cy_SysPm_IsLpmReady(void);

/*******************************************************************************
* Function Name: Cy_SysPm_SystemLpActiveEnter
****************************************************************************//**
*
* Change the system from ACTIVE Profile to LPACTIVE (Low Power Active)/LPSLEEP
* (Low Power Sleep) Profile
*
* \return
* - CY_SYSPM_SUCCESS - Entered the system Low Power mode or
* the device is already in Low Power mode.
* - CY_SYSPM_INVALID_STATE - The system Low Power mode was not set. The
* system Low Power mode was not set because the protection context value is
* higher than zero
*   (PC > 0) or the device revision does not support modifying registers
*   (to enter LP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system Low Power mode is not entered.
*
* \note
* This API is available for CAT1B devices.
*
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemLpActiveEnter(void);

/*******************************************************************************
* Function Name: Cy_SysPm_SystemLpActiveExit
****************************************************************************//**
*
* Changes the system from LPACTIVE (Low Power Active)/LPSLEEP (Low Power Sleep)
* Profile to ACTIVE Profile
*
* \return
* - CY_SYSPM_SUCCESS - Entered the system Low Power mode or
* the device is already in Low Power mode.
* - CY_SYSPM_INVALID_STATE - The system Low Power mode was not set. The
* system Low Power mode was not set because the protection context value is
* higher than zero
*   (PC > 0) or the device revision does not support modifying registers
*   (to enter LP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system Low Power mode is not entered.
*
* \note
* This API is available for CAT1B devices.
*
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemLpActiveExit(void);

/*******************************************************************************
* Function Name: Cy_SysPm_IsSystemLpActiveEnabled
****************************************************************************//**
*
* Checks if the system is in LPACTIVE (Low Power Active)/LPSLEEP (Low Power Sleep)
* Profile
*
* \return
* True if enabled, False if disabled.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
bool Cy_SysPm_IsSystemLpActiveEnabled(void);
#endif

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_SetDeepSleepMode
****************************************************************************//**
*
* Set the deepsleep mode - deepsleep or deepsleep-ram or deepsleep-off
*
* \note
* If mode is set to CY_SYSPM_MODE_DEEPSLEEP_RAM && Application in Flash, user
* needs to take care of below
*
* Two types of images need to be generated
* 1. Flash image
*    - Contains the actual application.
*
* 2. RAM Image(Resides in RAM)
*    - Contains Warmboot Entry Point function.
*    - SMIF initialization is performed only during coldboot, and not in
*      warmboot, so RAM Image will have the code performing SMIF
*      initialization before jumping to Flash Image.
*
* Before entering CY_SYSPM_MODE_DEEPSLEEP_RAM, user need to take care of below
* 1. Entry point
*    - Set entry point to a function located in RAM Image using
*    - Cy_Syslib_SetWarmBootEntryPoint(Syslib Driver)
*
* After waking up from CY_SYSPM_MODE_DEEPSLEEP_RAM, bootrom jumps to
* entry point function located in RAM image code. Entry point function should
* take care of below
*
* 1. Vector table and Peripheral IP's enabling
*    - Set VTOR register with vector table address.
*    - Enable all the peripheral IP's using \ref Cy_SysClk_PeriGroupSetSlaveCtl.
* 2. SMIF Initialization
*    - Perform  SMIF Initialization.
* 3. Jump to API in the Flash.
*
* \param deepSleepMode
* CY_SYSPM_MODE_DEEPSLEEP or CY_SYSPM_MODE_DEEPSLEEP_RAM or CY_SYSPM_MODE_DEEPSLEEP_OFF
*
* \return
* - CY_SYSPM_SUCCESS - Deep sleep mode is set
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SetDeepSleepMode(cy_en_syspm_deep_sleep_mode_t deepSleepMode);

/*******************************************************************************
* Function Name: Cy_SysPm_GetDeepSleepMode
****************************************************************************//**
*
* Get the deepsleep mode - deepsleep or deepsleep-ram or deepsleep-off
*
* \return
* Returns CY_SYSPM_MODE_DEEPSLEEP or CY_SYSPM_MODE_DEEPSLEEP_RAM or CY_SYSPM_MODE_DEEPSLEEP_OFF
* if system performs warm or cold boot else returns CY_SYSPM_MODE_NOT_DEEPSLEEP
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_deep_sleep_mode_t Cy_SysPm_GetDeepSleepMode(void);


/*******************************************************************************
* Function Name: Cy_SysPm_GetBootMode
****************************************************************************//**
*
* Checks from which Deep Sleep mode the system has woke up.
*
* \return
* Returns CY_SYSPM_WARM_BOOT_MODE or CY_SYSPM_WARM_COLD_MODE, if system performs
* warm or cold, else return CY_SYSPM_POR_BOOT_MODE if its a normal(POR) boot.
*
* \note
* This API is available for CAT1B devices.
*
* \note
* Use this API immediately after the boot, before writing any of the PPU
* registers,because this API depends on the programmed state of the PPU
* registers, so call it before the PPU registers get overwritten.
*
*******************************************************************************/
cy_en_syspm_boot_mode_t Cy_SysPm_GetBootMode(void);

/*******************************************************************************
* Function Name: Cy_SysPm_TriggerSoftReset
****************************************************************************//**
*
* Triggers the System Soft reset.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_TriggerSoftReset(void);

#endif

/*******************************************************************************
* Function Name: Cy_SysPm_CpuEnterDeepSleep
****************************************************************************//**
*
* Sets executing CPU to the Deep Sleep mode.
*
* Puts the CPU executing the function into CPU Deep Sleep. For a single CPU
* devices the device will immediately transition to system Deep Sleep. For a
* dual CPU devices the device will transition to system Deep Sleep only after
* both CPUs are in CPU Deep Sleep power mode.
*
* Prior to entering the CPU Deep Sleep mode, all callbacks of the
* CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY parameter registered
* callbacks are called, allowing the driver to signal whether it is ready to
* enter the power mode. If any CY_SYSPM_DEEPSLEEP type with the
* CY_SYSPM_CHECK_READY parameter call returns CY_SYSPM_FAIL, the remaining
* callback CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY parameter are
* skipped. After the first CY_SYSPM_FAIL, all the CY_SYSPM_DEEPSLEEP callbacks
* that were previously executed before getting the CY_SYSPM_CHECK_FAIL are
* executed with the CY_SYSPM_CHECK_FAIL parameter. The CPU Deep Sleep mode is
* not entered and the Cy_SysPm_CpuEnterDeepSleep() function returns
* CY_SYSPM_FAIL.
*
* If all callbacks of the CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_READY
* parameter return CY_SYSPM_SUCCESS, then all callbacks of the
* CY_SYSPM_DEEPSLEEP type with the CY_SYSPM_CHECK_FAIL parameter calls are
* skipped. All callbacks of the CY_SYSPM_DEEPSLEEP type with the
* CY_SYSPM_BEFORE_TRANSITION parameter calls are then executed, allowing the
* peripherals to prepare for CPU Deep Sleep. The Deep Sleep mode is then
* entered. Any enabled interrupt can cause a wakeup from the Deep Sleep mode.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* For multi-CPU devices (except CY8C6xx6 and CY8C6xx7) there is a possible
* situation when a syscall operation (for example during flash read or write)
* is executing. If the CM0+ CPU tries to enter Deep Sleep, it will fail. All
* the CY_SYSPM_DEEPSLEEP callbacks that were previously executed, are executed
* with the CY_SYSPM_CHECK_FAIL parameter. Deep Sleep mode is not entered and
* the Cy_SysPm_CpuEnterDeepSleep() function returns CY_SYSPM_SYSCALL_PENDING.
*
* The return value from executed callback functions with the
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* If the firmware attempts to enter this mode before the system is ready (that
* is, when PWR_CONTROL.LPM_READY = 0), then the CPU(s) will go into the CPU
* Sleep mode instead and automatically enter system Deep Sleep mode when the
* system is ready. On dual CPU devices, if one CPU enters CPU Deep Sleep and the
* other CPU remains active or is in CPU Sleep the first CPU will remain in CPU
* Deep Sleep. A CPU Deep Sleep is functionally identical to CPU Sleep.
*
* The device enters system Deep Sleep mode when all the CPU(s) are in CPU
* Deep Sleep, there are no busy peripherals, the debugger is not active, and the
* Deep Sleep power and reference are ready (PWR_CONTROL.LPM_READY=1).
*
* The peripherals that do not need a clock or that receive a clock from their
* external interface (e.g. I2C/SPI) may continue operating in system Deep Sleep.
* All circuits using current from Vccdpslp supply are limited by its maximum
* current specification of the Deep Sleep regulator.
*
* Wakeup occurs when an interrupt asserts from a Deep Sleep active peripheral.
* For more detail, see the corresponding peripheral's datasheet.
*
* For multi-core devices, CPU wakeup can also be performed using the Send Event
* (SEV) assembly instruction executed from the other active CPU. Such wakeup is
* expected only if the CPU Sleep power mode is done with WFE assembly
* instruction.
*
* \note
* For multi-CPU devices, the second CPU, if it did not participate in
* system wakeup, remains in CPU Deep Sleep mode. Any Deep Sleep capable
* interrupt routed to this CPU can also wake it.
*
* For more detail about switching into the system Deep Sleep power mode and
* debug, refer to the device TRM.
*
* A normal wakeup from the Deep Sleep power mode returns to either ULP or LP
* mode, depending on the previous state and programmed behavior for the
* particular wakeup interrupt. As soon as the system resumes LP or ULP mode the
* CPU(s) return to CPU Active or CPU Deep Sleep mode, depending on their
* configured wakeup settings.
*
* After wakeup from CPU Deep Sleep, all of the registered callbacks with
* CY_SYSPM_DEEPSLEEP type with CY_SYSPM_AFTER_TRANSITION are executed to return
* peripherals to active operation. The Cy_SysPm_CpuEnterDeepSleep() function
* returns CY_SYSPM_SUCCESS. No callbacks are executed with CY_SYSPM_DEEPSLEEP
* type with CY_SYSPM_BEFORE_TRANSITION or CY_SYSPM_AFTER_TRANSITION parameter,
* if Deep Sleep mode was not entered.
*
* To support control of callback execution order th following method is
* implemented. Callback function with the CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they
* are registered.
*
* \param waitFor
* Selects wait for action. See \ref cy_en_syspm_waitfor_t.
*
* \sideeffect
* For CY8C6xx6, CY8C6xx7 devices this function clears the Event Register of the
* CM4 CPU after wakeup from WFE.
*
* \sideeffect
* This function changes the slow and fast clock dividers right before
* entering into system Deep Sleep and restores these dividers after wakeup.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* The FLL/PLL are not restored right before the CPU(s) start executing the
* instructions after system Deep Sleep. This can affect the peripheral that is
* driven by PLL/FLL. Ensure that the PLL/FLL are properly restored (locked)
* after wakeup from System Deep Sleep. Refer to the
* \ref group_sysclk driver documentation for information about how to
* read the PLL/FLL lock statuses.
*
* \note The Arm BSD assembly instruction is not required in this function
* because the function implementation ensures the SLEEPDEEP bit of SCS register
* is settled prior executing the WFI/WFE instruction.
*
* \note
* This parameter is available for CAT1B devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_CpuEnterDeepSleep
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CpuEnterDeepSleep(cy_en_syspm_waitfor_t waitFor);

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterLp
****************************************************************************//**
*
* Sets device into system Low Power mode.
*
* Returns the system to the default LP mode by raising the core voltage.
* In the LP mode, the clock frequencies can be increased to t
he LP mode
* limitations. Refer to the device datasheet for frequency limitations in the
* LP mode. Approximate LP limit values - \ref group_syspm_lp_limitations.
*
* Prior to entering the system LP mode, all the registered CY_SYSPM_LP callbacks
* with CY_SYSPM_CHECK_READY parameter are called. This allows the driver to
* signal that it is not ready to enter the system LP mode. If any CY_SYSPM_LP
* callbacks with the CY_SYSPM_CHECK_READY parameter call return CY_SYSPM_FAIL,
* the remaining CY_SYSPM_LP callbacks with the
* CY_SYSPM_CHECK_READY parameter calls are skipped.
*
* After a CY_SYSPM_FAIL, all of the CY_SYSPM_LP callbacks with
* CY_SYSPM_CHECK_FAIL parameter are executed that correspond to the
* CY_SYSPM_LP callbacks with CY_SYSPM_CHECK_READY parameter that occurred up to
* the point of failure. System LP mode is not entered and the
* Cy_SysPm_SystemEnterLp() function returns CY_SYSPM_FAIL.
*
* If all CY_SYSPM_LP callbacks with the CY_SYSPM_CHECK_READY
* parameter return CY_SYSPM_SUCCESS, then all CY_SYSPM_LP callbacks with
* CY_SYSPM_CHECK_FAIL are skipped and all CY_SYSPM_LP callbacks with the
* CY_SYSPM_BEFORE_TRANSITION parameter are executed. This allows the
* peripherals to prepare for LP mode. The system LP mode is then entered.
*
* After entering the system LP mode, all of the registered
* CY_SYSPM_LP callbacks with the CY_SYSPM_AFTER_TRANSITION parameter
* are executed to complete preparing the peripherals for low power operation.
* The Cy_SysPm_SystemEnterLp() function returns CY_SYSPM_SUCCESS.
* No CY_SYSPM_LP callbacks with the CY_SYSPM_BEFORE_TRANSITION or
* CY_SYSPM_AFTER_TRANSITION parameter are executed if the system LP mode is not
* entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* To support control of callback execution order th following method is
* implemented. Callback function with the CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they
* are registered.
*
* \return
* - CY_SYSPM_SUCCESS - Entered the system LP mode or the device is already in LP mode.
* - CY_SYSPM_INVALID_STATE - The system LP mode was not set. The system LP mode
*   was not set because the protection context value is higher than zero
*   (PC > 0) or the device revision does not support modifying registers
*   (to enter LP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system LP mode is not entered.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemEnterLp
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterLp(void);


/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterUlp
****************************************************************************//**
*
* Sets device into system Ultra Low Power mode.
*
* System ULP mode is similar to system LP mode. The difference is that the
* system is put under \ref group_syspm_ulp_limitations.
*
* Before entering system ULP mode, the user must configure the system so
* the maximum clock frequencies are less than the ULP mode specifications
* presented in the device datasheet. Refer to the device datasheet for
* the maximum clock limitations in the ULP mode with reduced core supply
* regulator voltages.
*
* Prior to entering system ULP mode, all the registered CY_SYSPM_ULP callbacks
* with CY_SYSPM_CHECK_READY parameter are called. This allows the driver to
* signal if it is not ready to enter system ULP mode. If any CY_SYSPM_ULP
* callback with the CY_SYSPM_CHECK_READY parameter call returns CY_SYSPM_FAIL,
* the remaining CY_SYSPM_ULP callbacks with the CY_SYSPM_CHECK_READY parameter
* are skipped.
*
* After a CY_SYSPM_FAIL, all of the CY_SYSPM_ULP callbacks with the
* CY_SYSPM_CHECK_FAIL parameter are executed that correspond to the
* CY_SYSPM_ULP callback with CY_SYSPM_CHECK_READY parameter that occurred up to
* the point of failure. System ULP mode is not entered
* and the Cy_SysPm_SystemEnterUlp() function returns CY_SYSPM_FAIL.
*
* If all CY_SYSPM_ULP callbacks with the CY_SYSPM_CHECK_READY
* parameter return CY_SYSPM_SUCCESS, then all CY_SYSPM_ULP
* callbacks with CY_SYSPM_CHECK_FAIL calls are skipped and all CY_SYSPM_ULP
* callbacks with the CY_SYSPM_BEFORE_TRANSITION parameter are executed. This
* allows preparation for ULP. The system ULP mode is then entered.
*
* After entering system ULP, all of the registered CY_SYSPM_ULP callbacks with
* the CY_SYSPM_AFTER_TRANSITION parameter are executed to complete preparing the
* peripherals for ULP operation. The Cy_SysPm_SystemEnterUlp() function
* returns CY_SYSPM_SUCCESS. No CY_SYSPM_ULP callbacks with the
* CY_SYSPM_BEFORE_TRANSITION or CY_SYSPM_AFTER_TRANSITION parameter are
* executed, if ULP mode is not entered.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* To support control of callback execution order th following method is
* implemented. Callback function with the CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they
* are registered.
*
* \return
* - CY_SYSPM_SUCCESS - Entered the system ULP mode or the device is already in ULP mode.
* - CY_SYSPM_INVALID_STATE - System ULP mode was not set. The ULP mode was not
*   set because the protection context value is higher than zero (PC > 0) or the
*   device revision does not support modifying registers (to enter system
*   ULP mode) via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
* - CY_SYSPM_FAIL - The system ULP mode is not entered.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemEnterUlp
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterUlp(void);
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */

/*******************************************************************************
* Function Name: Cy_SysPm_SystemEnterHibernate
****************************************************************************//**
*
* Sets the device into system Hibernate mode.
*
* Puts the device into the system Hibernate power mode. Prior to entering
* Hibernate mode, all callbacks of the CY_SYSPM_HIBERNATE type are executed.
*
* First, callbacks of the CY_SYSPM_HIBERNATE type are called with the
* CY_SYSPM_CHECK_READY parameter. This allows the callback to signal that the
* driver is not ready to enter the system Hibernate power mode. If any of the
* callback return CY_SYSPM_FAIL, the remaining CY_SYSPM_HIBERNATE callbacks are
* skipped. In this case, all of the callbacks that have already been called are
* called again with the CY_SYSPM_CHECK_FAIL parameter. System Hibernate mode is
* not entered and the Cy_SysPm_SystemEnterHibernate() function returns
* CY_SYSPM_FAIL.
*
* If all CY_SYSPM_HIBERNATE callbacks with the CY_SYSPM_CHECK_READY parameter
* return CY_SYSPM_SUCCESS, then all CY_SYSPM_HIBERNATE callbacks with
* CY_SYSPM_CHECK_FAIL calls are skipped and all CY_SYSPM_HIBERNATE callbacks
* with CY_SYSPM_BEFORE_TRANSITION parameter are executed allowing the
* peripherals to prepare for system Hibernate.
*
* The I/O output state is automatically frozen by hardware system and Hibernate
* mode is then entered. In Hibernate mode, all internal supplies are off and no
* internal state is retained. The only exception is resources powered by the
* Vbackup domain continue to operate, if enabled. For multi-CPU devices, there
* is no handshake with the CPUs and the chip will enter Hibernate power
* mode immediately.
*
* \note The last callback that returns CY_SYSPM_FAIL is not executed with the
* CY_SYSPM_CHECK_FAIL parameter because of the FAIL. The callback generating
* CY_SYSPM_FAIL is expected to not make any changes that require being undone.
*
* The return value from executed callback functions with the
* CY_SYSPM_CHECK_FAIL, CY_SYSPM_BEFORE_TRANSITION, and CY_SYSPM_AFTER_TRANSITION
* modes are ignored.
*
* Wakeup from system Hibernate is triggered by toggling the wakeup pin(s), WDT
* match, or back-up domain RTC alarm expiration, depending on how the they are
* configured. A wakeup causes a normal boot procedure.
* To configure the wakeup pin(s), a digital input pin must be configured, and
* resistively pulled up or down to the inverse state of the wakeup polarity. To
* distinguish a Hibernate mode from a general reset wakeup event, the
* Cy_SysLib_GetResetReason() function can be used. The wakeup pin and low-power
* comparators are active-low by default. The wakeup pin or the LPComparators
* polarity can be changed with the \ref Cy_SysPm_SetHibernateWakeupSource()
* function.
* This function call will not return if system Hibernate mode is entered.
* The CY_SYSPM_HIBERNATE callbacks with the CY_SYSPM_AFTER_TRANSITION parameter
* are never executed.
*
* This function freezes the I/O pins implicitly. Entering system Hibernate mode
* before freezing the I/O pins is not possible. The I/O pins remain frozen after
* waking from Hibernate mode until the firmware unfreezes them with
* a \ref Cy_SysPm_IoUnfreeze() function call.
*
* Boot firmware should reconfigure the I/O pins as required by the application
* prior unfreezing them.
*
* To support control of callback execution order th following method is
* implemented. Callback function with the CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION parameter are executed in the same order they are
* registered. Callback function with the CY_SYSPM_CHECK_FAIL and
* CY_SYSPM_AFTER_TRANSITION parameter are executed in the reverse order they
* are registered.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemEnterHibernate
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemEnterHibernate(void);


/*******************************************************************************
* Function Name: Cy_SysPm_SetHibernateWakeupSource
****************************************************************************//**
*
* This function configures sources to wake up the device from the system
* Hibernate power mode. Sources can be wakeup pins, LPComparators, Watchdog (WDT)
* interrupt, or a Real-Time clock (RTC) alarm (interrupt). Wakeup from system
* Hibernate always results in a device reset and normal boot process.
*
* Wakeup pins:
*
* A wakeup is supported by up to two pins with programmable polarity. These pins
* are typically connected to the GPIO pins or on-chip peripherals under some
* conditions. See device datasheet for specific pin connections.
* Setting the wakeup pin to this level will cause a wakeup from system Hibernate
* mode. The wakeup pins are active-low by default.
*
* LPComparators:
*
* A wakeup is supported by up to two LPComps with programmable polarity.
* Setting the LPComp to this level will cause a wakeup from system Hibernate
* mode. The wakeup LPComps are active-low by default.
*
* \note The low-power comparators should be configured and enabled before
* switching to system Hibernate mode. Refer to the LPComp
* driver description for more detail.
*
* Watchdog Timer:
*
* \note The WDT should be configured and enabled before entering to system
* Hibernate mode.
*
* A wakeup is performed by a WDT interrupt.
*
* Real-time Clock:
*
* A wakeup is performed by the RTC alarm.
* Refer to the Real-Time Clock (RTC) driver description for more detail.
*
* For information about wakeup sources and their assignment in specific
* devices, refer to the appropriate device TRM.
*
* \param wakeupSource
* The source to be configured as a wakeup source from
* the system Hibernate power mode, see \ref cy_en_syspm_hibernate_wakeup_source_t.
* The input parameter values can be ORed. For example, if you want to enable
* LPComp0 (active high) and WDT, call this function:
* Cy_SysPm_SetHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_HIGH | CY_SYSPM_HIBERNATE_WDT).
*
* \warning Do not call this function with different polarity levels for the same
* wakeup source. For example, do not call a function like this:
* Cy_SysPm_SetHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_LOW, CY_SYSPM_HIBERNATE_LPCOMP0_HIGH);
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SetHibernateWakeupSource
*
*******************************************************************************/
void Cy_SysPm_SetHibernateWakeupSource(uint32_t wakeupSource);


/*******************************************************************************
* Function Name: Cy_SysPm_ClearHibernateWakeupSource
****************************************************************************//**
*
* This function disables a wakeup source that was previously configured to
* wake up the device from the system Hibernate mode.
*
* \param wakeupSource
* For the source to be disabled, see \ref cy_en_syspm_hibernate_wakeup_source_t.
* The input parameters values can be ORed. For example, if you want to disable
* LPComp0 (active high) and WDT call this function:
* Cy_SysPm_ClearHibernateWakeupSource(CY_SYSPM_HIBERNATE_LPCOMP0_HIGH | CY_SYSPM_HIBERNATE_WDT).
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_ClearHibernateWakeupSource
*
*******************************************************************************/
void Cy_SysPm_ClearHibernateWakeupSource(uint32_t wakeupSource);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_GetHibernateWakeupCause
****************************************************************************//**
*
* This function gets the wakeup cause for Hibernate mode.
*
* \return
* Wakeup Reason \ref cy_en_syspm_hibernate_wakeup_source_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_hibernate_wakeup_source_t Cy_SysPm_GetHibernateWakeupCause(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ClearHibernateWakeupCause
****************************************************************************//**
*
* This function Clears the wakeup cause register.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_ClearHibernateWakeupCause(void);

#endif



/*******************************************************************************
* Function Name: Cy_SysPm_SystemSetMinRegulatorCurrent
****************************************************************************//**
*
* Sets the system into minimum core regulator current mode. This mode limits
* maximum current available for the system core logic.
*
* Minimum regulator current mode modifies operation of the system in LP or ULP
* modes to further reduce current consumption. If the system current is below
* datasheet current limits for the active core voltage regulator (LDO or Buck),
* this mode may be entered. The user is responsible for ensuring the
* regulator current limit is met in their application.
*
* When in minimum regulator current mode, the following system resources are
* also set to their LP mode:
* - Linear regulator (If LDO is active regulator)
* - POR/BOD circuit
* - Bandgap reference circuit
* - Reference buffer circuit
* - Current reference circuit
*
* The LDO and Buck current limits must be met prior to entering this
* mode. If these are not met, the device may brown out, resulting in an
* exception or reset. These changes also reduce power supply rejection of
* the affected system resources, which can result in increased noise or response
* time. These effects must be evaluated in each application.
*
* \return
* See \ref cy_en_syspm_status_t.
* - CY_SYSPM_SUCCESS - Minimum regulator current mode was set
* - CY_SYSPM_CANCELED - The power circuits were not ready to enter into
*   minimum current mode. You should call the function again.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* Refer to device datasheet for maximum current value in regulator minimum
* current mode.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemSetMinRegulatorCurrent
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemSetMinRegulatorCurrent(void);


/*******************************************************************************
* Function Name: Cy_SysPm_SystemSetNormalRegulatorCurrent
****************************************************************************//**
*
* Sets the system to normal regulator current mode.
*
* Normal regulator current mode modifies operation of the system in LP or ULP
* modes to provide maximum core current consumption. If the LDO core regulator
* is in use, the normal mode output current limits may be used. If the buck
* regulator is in use, its reduced current output limits still apply.
*
* When in normal regulator current mode, the following system resources are set
* to their normal mode:
* - Linear regulator (If LDO is active regulator)
* - POR/BOD circuit
* - Bandgap reference circuit
* - Reference buffer circuit
* - Current reference circuit
*
* \return
* - CY_SYSPM_SUCCESS - Normal regulator current mode was set
* - CY_SYSPM_TIMEOUT - The timeout occurred because device was not
*   ready to enter into the normal regulator current mode
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemSetNormalRegulatorCurrent
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SystemSetNormalRegulatorCurrent(void);


/*******************************************************************************
* Function Name: Cy_SysPm_CpuSleepOnExit
****************************************************************************//**
*
* This function configures the sleep-on-exit feature of the CPU.
*
* This API sets the SLEEPONEXIT bit of the SCR register.
*
* When the sleep-on-exit feature is enabled (the SLEEPONEXIT bit is set),
* the CPU wakes up to service the interrupt and then immediately goes
* back to sleep. Because of this, the unstacking process is not carried out, so
* this feature is useful for interrupt driven application and helps to
* reduce unnecessary stack push and pop operations.
* The CPU does not go to sleep if the interrupt handler returns to
* another interrupt handler (nested interrupt).
* You can use this feature in applications that require the CPU to only run
* when an interrupt occurs.
*
* When the sleep-on-exit feature is disabled (the SLEEPONEXIT bit is cleared),
* the CPU returns back to the main thread after servicing the interrupt
* without going back to sleep.
*
* Refer to the Arm documentation about the sleep-on-exit feature and
* SLEEPONEXIT in the SCR register.
*
* \param enable
* - True if enable sleep-on-exit feature.
* - False if disable sleep-on-exit feature.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_CpuSleepOnExit
*
*******************************************************************************/
void Cy_SysPm_CpuSleepOnExit(bool enable);

/** \} group_syspm_functions_power */


/**
* \addtogroup group_syspm_functions_ldo
* \{
*/

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_LdoSetVoltage
****************************************************************************//**
*
* Set output voltage on the core LDO regulator.
*
* When changing from a higher voltage to a lower voltage as when the device
* enters system ULP mode, ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
* * The appropriate wait states values are set for the flash using
*   The Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b>
*
* The flash access time when the core voltage is 0.9 V (nominal) is
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash.
*
* To change from a higher voltage to a lower voltage 0.9 V (nominal),
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage to a higher voltage 1.1 V (nominal), calling
* the Cy_SysLib_SetWaitStates(false, hfClkFreqMz) function to set the
* wait states is optional, but can be done to improve performance.
* The clock frequency may now be increased up to
* \ref group_syspm_lp_limitations.
*
* \note 1. The output is set to 0.9 V (nominal) - the system is in ULP mode and
* flash works for read-only operation.
* \note 2. The output is set to 1.1 V (nominal) - the system is in LP mode
* and flash works for read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal
* voltage because the actual voltage value depends on conditions
* including the load current.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting the wait
* states.
*
* \param voltage
* The desired output regulator voltage.
* See \ref cy_en_syspm_ldo_voltage_t voltage
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set.
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set
*   because the protection context value is higher than zero (PC > 0) or the
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_LdoSetVoltage(cy_en_syspm_ldo_voltage_t voltage);
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */

/*******************************************************************************
* Function Name: Cy_SysPm_LdoSetMode
****************************************************************************//**
*
* Configures the core LDO regulator operating mode to one of three modes.
* Disabled - turns off the LDO regulator and should be selected only after the
* Buck regulator is operating. Normal mode configures the LDO for operation at
* the maximum output current limit. Minimal current mode optimizes the LDO at a
* reduced output current limit. Specific device current limits can be found in
* the device datasheet.
*
* \param mode
* The desired LDO regulator operating mode.
* See \ref cy_en_syspm_ldo_mode_t mode
*
* \return
* - CY_SYSPM_SUCCESS - Requested regulator current mode was set
* - CY_SYSPM_CANCELED - The power circuits were not ready to enter into
*   minimum current mode. You should try to call the function again
* - CY_SYSPM_TIMEOUT - Timeout occurred because of active reference was not
*   ready to enter into the normal regulator current mode
* - CY_SYSPM_FAIL - incorrect mode value was passed
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \sideeffect
* For PSoC 64 series devices CY_SYSPM_LDO_MODE_DISABLED mode is not supported.
* Use \ref Cy_SysPm_BuckEnable() instead.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_LdoSetMode(cy_en_syspm_ldo_mode_t mode);


/*******************************************************************************
* Function Name: Cy_SysPm_LdoGetMode
****************************************************************************//**
*
* Returns the current core LDO regulator operating mode.
*
* \return
* The LDO regulator operating mode.
* See \ref cy_en_syspm_ldo_mode_t mode
*
*******************************************************************************/
cy_en_syspm_ldo_mode_t Cy_SysPm_LdoGetMode(void);

/** \} group_syspm_functions_ldo */


/**
* \addtogroup group_syspm_functions_linearreg
* \{
*/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

/*******************************************************************************
* Function Name: Cy_SysPm_LinearRegDisable
****************************************************************************//**
*
* Disables internal linear regulator.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_LinearRegDisable(void);

/*******************************************************************************
* Function Name: Cy_SysPm_LinearRegEnable
****************************************************************************//**
*
* Enables internal linear regulator.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_LinearRegEnable(void);


/*******************************************************************************
* Function Name: Cy_SysPm_LinearRegGetStatus
****************************************************************************//**
*
* Check the status of the internal linear regulator.
*
* \return
* true  - status ok
* false - status fail
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_LinearRegGetStatus(void);


/*******************************************************************************
* Function Name: Cy_SysPm_DeepSleepRegDisable
****************************************************************************//**
*
* Disables internal DeepSleep regulator.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_DeepSleepRegDisable(void);


/*******************************************************************************
* Function Name: Cy_SysPm_DeepSleepRegEnable
****************************************************************************//**
*
* Enables internal DeepSleep regulator.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_DeepSleepRegEnable(void);

/*******************************************************************************
* Function Name: Cy_SySPm_IsDeepSleepRegEnabled
****************************************************************************//**
*
* Checks if internal DeepSleep regulator is enabled or not.
*
* \return
* true  - Enabled
* false - Disabled
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SySPm_IsDeepSleepRegEnabled(void);

#endif
/** \} group_syspm_functions_linearreg */

/**
* \addtogroup group_syspm_functions_reghc
* \{
*/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcSelectMode
****************************************************************************//**
*
* Selects one of the supported REGHC modes.
*
* \param
* mode - PMIC or Pass Transistor
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcSelectMode(cy_en_syspm_reghc_mode_t mode);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcGetMode
****************************************************************************//**
*
* Gets the supported REGHC modes.
*
* \return \ref cy_en_syspm_reghc_mode_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_syspm_reghc_mode_t Cy_SysPm_ReghcGetMode(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcSelectDriveOut
****************************************************************************//**
*
* Selects DRV_OUT setting.
*
* \param
* drvOut - \ref cy_en_syspm_reghc_drive_out_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcSelectDriveOut(cy_en_syspm_reghc_drive_out_t drvOut);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcGetDriveOut
****************************************************************************//**
*
* Gets the DRV_OUT setting.
*
* \return \ref cy_en_syspm_reghc_drive_out_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_syspm_reghc_drive_out_t Cy_SysPm_ReghcGetDriveOut(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcAdjustOutputVoltage
****************************************************************************//**
*
* Selects regulator output voltage adjustment.
*
* \param
* trim - \ref cy_en_syspm_reghc_vadj_t
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcAdjustOutputVoltage(cy_en_syspm_reghc_vadj_t trim);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisableIntSupplyWhileExtActive
****************************************************************************//**
*
*  Internal Active Linear Regulator disabled after PMIC enabled.  OCD is disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisableIntSupplyWhileExtActive(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnableIntSupplyWhileExtActive
****************************************************************************//**
*
*   Internal Active Linear Regulator kept enabled.  See datasheet for minimum
*   PMIC vccd input to prevent OCD.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnableIntSupplyWhileExtActive(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisablePmicEnableOutput
****************************************************************************//**
*
* Disables "PMIC enable" output.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisablePmicEnableOutput(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnablePmicEnableOutput
****************************************************************************//**
*
* Enables "PMIC enable" output.
*
* \param
* polarity => true - output high, false - output low.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnablePmicEnableOutput(bool polarity);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnablePmicStatusInput
****************************************************************************//**
*
* Enables receiving status from PMIC.
*
* \param
* polarity => true/false -> receiving high/low means abnormal status.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnablePmicStatusInput(bool polarity);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisablePmicStatusInput
****************************************************************************//**
*
* Disables PMIC status input
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisablePmicStatusInput(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcSetPmicStatusWaitTime
****************************************************************************//**
*
* Wait count in 4us steps after PMIC status ok. This is used by the hardware
* sequencer to allow additional settling time before disabling the internal
* regulator.
* The LSB is 32 IMO periods which results in a nominal LSB step of 4us.
*
* \param
* waitTime = 0 to 1023 -> (waitTime * 4us) Delay
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcSetPmicStatusWaitTime(uint16_t waitTime);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsConfigured
****************************************************************************//**
*
* Indicates that the REGHC has been configured.
* Do not change REGHC settings after this bit is high.
*
* \return
* true - Configured, false - Not configured
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsConfigured(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcSetConfigured
****************************************************************************//**
*
* Set REGHC is configured. This is required to apply setting before enabling REGHC.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcSetConfigured(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisable
****************************************************************************//**
*
* Disables REGHC.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisable(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnable
****************************************************************************//**
*
* Enables REGHC.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnable(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisablePmicStatusTimeout
****************************************************************************//**
*
* Disables timeout when waiting for REGHC_PMIC_STATUS_OK.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisablePmicStatusTimeout(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnablePmicStatusTimeout
****************************************************************************//**
*
* Enables timeout while waiting for REGHC_PMIC_STATUS_OK==1 when switching to PMIC.
* Timeout expiration triggers reset.
*
* \param
* timeout = 1 - 255 -> (timeout * 128us) delay until reset
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnablePmicStatusTimeout(uint8_t timeout);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsEnabled
****************************************************************************//**
*
* Indicates the state of the REGHC enable/disable sequencer.  This bit is only
* valid when REGHC_SEQ_BUSY==0.
*
* \return
* true - Enabled, false - Disabled
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsStatusOk
****************************************************************************//**
*
* Indicates the PMIC status is ok.  This includes polarity adjustment according
* to REGHC_PMIC_STATUS_POLARITY.
*
* \return
* false: PMIC status is not ok or PMIC input is disabled (PMIC_STATUS_INEN == 0)
* true:  PMIC status input is enabled and indicates ok
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsStatusOk(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsSequencerBusy
****************************************************************************//**
*
* Indicates whether the REGHC circuit is busy. Indicates the REGHC enable/disable
* sequencer is busy transitioning to/from REGHC.
*
* \return
* true:  REGHC busy
* false: REGHC not busy
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsSequencerBusy(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisableVAdj
****************************************************************************//**
*
* Device does not generate VADJ, and it must not be part of the PMIC feedback loop.
* This reduces current by turning off the internal resistor divider that generates
* VADJ.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisableVAdj(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnableVAdj
****************************************************************************//**
*
* Device generates VADJ when PMIC is enabled.  This allows the feedback loop to
* compensate for voltage drops in the PCB and package.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnableVAdj(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcDisablePmicInDeepSleep
****************************************************************************//**
*
* Device operates from internal regulators during DEEPSLEEP.  If PMIC is enabled
* at the beginning of the DEEPSLEEP transition, hardware changes to the internal
* regulators and disables the PMIC.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcDisablePmicInDeepSleep(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcEnablePmicInDeepSleep
****************************************************************************//**
*
* DEEPSLEEP transition does not change PMIC enable.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_ReghcEnablePmicInDeepSleep(void);

/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsOcdWithinLimits
****************************************************************************//**
*
* Indicates the over-current detector is operating and the current drawn from
* REGHC is within limits.  OCD is only a choice for transistor mode, and it is
* disabled for PMIC mode.
*
* \return
* false: Current measurement exceeds limit or detector is OFF,
* true:  Current measurement within limit
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsOcdWithinLimits(void);


/*******************************************************************************
* Function Name: Cy_SysPm_ReghcIsCircuitEnabledAndOperating
****************************************************************************//**
*
* Indicates the REGHC circuit is enabled and operating.
*
* \return
* false: REGHC Disabled
* true:  REGHC Enabled and Operating
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_ReghcIsCircuitEnabledAndOperating(void);


#endif

/** \} group_syspm_functions_reghc */


/**
* \addtogroup group_syspm_functions_ovd
* \{
*/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))  || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_OvdEnable
****************************************************************************//**
*
*  Enables OVD over either VDDD or VDDA or VCCD.
*
*  \param ovdSel \ref cy_en_syspm_ovd_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* OVD over VDDD and VCCD are enabled by default and cannot be disabled.
*
*******************************************************************************/
void Cy_SysPm_OvdEnable(cy_en_syspm_ovd_sel_t ovdSel);



/*******************************************************************************
* Function Name: Cy_SysPm_OvdDisable
****************************************************************************//**
*
*  Disables OVD over either VDDD or VDDA or VCCD.
*
*  \param ovdSel \ref cy_en_syspm_ovd_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* OVD over VDDD and VCCD are enabled by default and cannot be disabled.
*
* \note
* Disabling OVD over VDDA will perform the /ref cy_en_syspm_ovd_action_select_t
* action selected for VDDA. If no action is desired when disabling, firmware
* must first write CY_SYSPM_OVD_ACTION_NOTHING in a separate write cycle.
*
*******************************************************************************/
void Cy_SysPm_OvdDisable(cy_en_syspm_ovd_sel_t ovdSel);



/*******************************************************************************
* Function Name: Cy_SysPm_OvdVdddSelect
****************************************************************************//**
*
*  Selects voltage threshold for OVD on VDDD
*
*  \param ovdVdddSel \ref cy_en_syspm_ovd_vddd_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_OvdVdddSelect(cy_en_syspm_ovd_vddd_sel_t ovdVdddSel);


/*******************************************************************************
* Function Name: Cy_SysPm_OvdVddaSelect
****************************************************************************//**
*
*  Selects voltage threshold for OVD on VDDA
*
*  \param ovdVddaSel \ref cy_en_syspm_ovd_vdda_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_OvdVddaSelect(cy_en_syspm_ovd_vdda_sel_t ovdVddaSel);


/*******************************************************************************
* Function Name: Cy_SysPm_OvdActionSelect
****************************************************************************//**
*
*  Sets the action taken when the threshold is crossed in the programmed directions(s)
* for VDDA.
*
*  \param ovdActionSelect \ref cy_en_syspm_ovd_action_select_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* This API is not applicable for selectng actions for VDDD and VCCD as the default
* action is RESET for them.
*
*******************************************************************************/
void Cy_SysPm_OvdActionSelect(cy_en_syspm_ovd_action_select_t ovdActionSelect);

#endif

/** \} group_syspm_functions_ovd */

/**
* \addtogroup group_syspm_functions_bod
* \{
*/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/*******************************************************************************
* Function Name: Cy_SysPm_BodEnable
****************************************************************************//**
*
*  Enables BOD over either VDDD or VDDA or VCCD.
*
*  \param bodSel \ref cy_en_syspm_bod_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* BOD over VDDD and VCCD are enabled by default and cannot be disabled.
*
*******************************************************************************/
void Cy_SysPm_BodEnable(cy_en_syspm_bod_sel_t bodSel);

/*******************************************************************************
* Function Name: Cy_SysPm_BodDisable
****************************************************************************//**
*
*  Disables BOD over either VDDD or VDDA or VCCD.
*
*  \param bodSel \ref cy_en_syspm_bod_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* BOD over VDDD and VCCD are enabled by default and cannot be disabled.
*
* \note
* Disabling BOD over VDDA will perform the /ref cy_en_syspm_bod_action_select_t
* action selected for VDDA. If no action is desired when disabling, firmware
* must first write CY_SYSPM_BOD_ACTION_NOTHING in a separate write cycle.
*
*******************************************************************************/
void Cy_SysPm_BodDisable(cy_en_syspm_bod_sel_t bodSel);


/*******************************************************************************
* Function Name: Cy_SysPm_BodVdddSelect
****************************************************************************//**
*
*  Selects voltage threshold for BOD on VDDD
*
*  \param bodVdddSel \ref cy_en_syspm_bod_vddd_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_BodVdddSelect(cy_en_syspm_bod_vddd_sel_t bodVdddSel);


/*******************************************************************************
* Function Name: Cy_SysPm_BodVddaSelect
****************************************************************************//**
*
*  Selects voltage threshold for BOD on VDDA
*
*  \param bodVddaSel \ref cy_en_syspm_bod_vdda_sel_t.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
 void Cy_SysPm_BodVddaSelect(cy_en_syspm_bod_vdda_sel_t bodVddaSel);


/*******************************************************************************
* Function Name: Cy_SysPm_BodActionSelect
****************************************************************************//**
*
*  Sets the action taken when the threshold is crossed in the programmed directions(s)
* for VDDA.
*
*  \param bodActionSelect \ref cy_en_syspm_bod_action_select_t.
*
* \note
* This API is available for CAT1C devices.
*
* \note
* This API is not applicable for selectng actions for VDDD and VCCD as the default
* action is RESET for them.
*
*******************************************************************************/
void Cy_SysPm_BodActionSelect(cy_en_syspm_bod_action_select_t bodActionSelect);


/*******************************************************************************
* Function Name: Cy_SysPm_SupplySupervisionStatus
****************************************************************************//**
*
* Supply Status.
*
* \param supplyEntitySelect \ref cy_en_syspm_supply_entity_select_t.

* \return
* State of BOD/OVD on VDDD/VDDA/VCCD, whether OK or Not OK
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_SupplySupervisionStatus(cy_en_syspm_supply_entity_select_t supplyEntitySelect);

#endif

/** \} group_syspm_functions_bod */


/**
* \addtogroup group_syspm_functions_buck
* \{
*/

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_BuckEnable
****************************************************************************//**
*
* Switch the core supply regulator to Buck core regulator instead of the LDO
* regulator.
* The Buck core regulator provides output voltage(s) using one external
* inductor and can supply Vccd with higher efficiency than the LDO under some
* conditions, such as high external supply voltage.
*
* Before changing from LDO to Buck, ensure that the circuit board has
* connected Vccbuck1 to Vccd and also populated the
* necessary external components for the Buck regulator, including an
* inductor and a capacitor for each output.
* Refer to the device TRM for more detail.
*
* When changing from a higher voltage to a lower voltage
* (from system LP = LDO 1.1 V (nominal) to system ULP = Buck 0.9 V (nominal)),
* ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
*
* * The appropriate wait states values are set for the flash using
*   the Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b>
*
* The flash access time when the core output voltage is 0.9 V (nominal) is
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash.
*
* To change from a higher voltage (LDO 1.1 V) to a lower voltage (Buck 0.9 V),
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage (LDO 0.9 V (nominal) to a higher voltage
* (Buck 1.1 V (nominal)), call the Cy_SysLib_SetWaitStates(false,
* hfClkFreqMz) function to set the wait states after the voltage change.
* It is optional, but can be done to improve performance. The clock frequency
* may now be increased up to system LP mode limits for the new voltage.
*
* \note 1. If the final Buck output is set to 0.9 V (nominal) - the system is in
*  ULP mode and flash allows read-only operations.
* \note 2. If the final Buck output is set to 1.1 V (nominal) - the system is in
*  LP mode flash allows the read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal
*  voltage because the actual voltage value depends on conditions
*  including the load current.
*
* \warning There is no safe way to go back to the LDO after the
*  Buck regulator supplies a core. The function enabling the Buck regulator
*  switches off the LDO.
*
* \warning Buck converter requires additional external components populated on
* dedicated pins. Refer to device datasheet for details.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting wait
* states.
*
* \param voltage
* The desired output 1 regulator voltage (Vccbuck1).
* See \ref cy_en_syspm_buck_voltage1_t.
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set as requested.
*   (There is no change if the new voltage is the same as the previous voltage.)
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set
*   because the protection context value is higher than zero (PC > 0) or the
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \note
* The function is applicable only for devices with a Buck regulator.
*
* Function uses a critical section to prevent interrupting the regulators
* switch.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckEnable
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_BuckEnable(cy_en_syspm_buck_voltage1_t voltage);


/*******************************************************************************
* Function Name: Cy_SysPm_BuckSetVoltage1
****************************************************************************//**
*
* Sets the output 1 voltage for the Buck regulator that can supply the device
* core. This output can supply the device core instead of the LDO regulator.
*
* When changing from a higher voltage 1.1 V (nominal) to a lower voltage 0.9 V
* (nominal), ensure that:
* * The device maximum operating frequency for all the Clk_HF paths, peripheral,
*   and slow clock are under the \ref group_syspm_ulp_limitations.
* * The total current consumption is under the \ref group_syspm_ulp_limitations.
* * The appropriate wait states values are set for the flash using
*   the Cy_SysLib_SetWaitStates() function as explained below.
*
* <b>Setting wait states values for flash</b>
*
* The flash access time when the core output voltage is 0.9 V (nominal) is
* longer than at 1.1 V (nominal). Therefore, the number of the wait states must
* be adjusted. Use the Cy_SysLib_SetWaitStates() function to set the appropriate
* wait state values for flash.
*
* To change from a higher voltage to a lower voltage 0.9 V (nominal),
* call the Cy_SysLib_SetWaitStates(true, hfClkFreqMz) function before changing
* the voltage, where hfClkFreqMz is the frequency of HfClk0 in MHz.
*
* To change from a lower voltage to a higher voltage 1.1 V (nominal), call
* the Cy_SysLib_SetWaitStates(false, hfClkFreqMz) function to set the
* wait states. It is optional, but can be done to improve the performance.
* The clock frequency may now be increased up to
* \ref group_syspm_lp_limitations for a new voltage.
*
* \note 1. The output is set to 0.9 V (nominal) - the system  is in ULP mode
*  flash allows read-only operations.
* \note 2. The output is set to 1.1 V (nominal) - the system is in LP mode and
*  flash allows the read and write operations.
* \note 3. The actual device Vccd voltage can be different from the nominal
*  voltage because the actual voltage value depends on the conditions
*  including the load current.
*
* \warning Buck converter requires additional external components populated on
* dedicated pins. Refer to device datasheet for details.
*
* For more detail, refer to the \ref group_syspm_switching_into_ulp and
* \ref group_syspm_switching_into_lp sections.
* Refer to the \ref group_syslib driver for more detail about setting the
* wait states.
*
* \param voltage
* The desired output 1 regulator voltage (Vccbuck1).
* See \ref cy_en_syspm_buck_voltage1_t
*
* \return
* - CY_SYSPM_SUCCESS - The voltage is set.
* - CY_SYSPM_INVALID_STATE - The voltage was not set. The voltage cannot be set
*   because the protection context value is higher than zero (PC > 0) or the
*   device revision does not support modifying registers via syscall.
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS. See \ref cy_en_syspm_status_t.
*   For the PSoC 64 devices there are possible situations when function returns
*   the PRA error status code. This is because for PSoC 64 devices the function
*   uses the PRA driver to change the protected registers. Refer to
*   \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
* \sideeffect
* For PSoC 64 series devices Cy_SysPm_BuckSetVoltage1() has the same functional
* behavior as \ref Cy_SysPm_BuckEnable() function.
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_BuckSetVoltage1(cy_en_syspm_buck_voltage1_t voltage);


/*******************************************************************************
* Function Name: Cy_SysPm_BuckSetVoltage2
****************************************************************************//**
*
* This function sets output voltage 2 (Vbuckrf) of the SIMO Buck regulator.
*
* \param voltage
* The voltage of the Buck regulator output 2 (Vbuckrf).
* See \ref cy_en_syspm_buck_voltage2_t.
*
* \param waitToSettle
* - True to enable the 200 us delay after setting a higher voltage.
* - False to disable the 200 us delay after setting a higher voltage.
*
* \warning You must enable the delay (waitToSettle = true)
* while changing from a lower voltage to a higher voltage.
*
* \note The 200 us delay is required only when changing from a
* lower voltage to a higher voltage. When changing from a higher voltage to a
* lower one, the delay is not required.
*
* \warning The function works only on devices with the SIMO Buck regulator.
* Refer to the device datasheet for information on whether the device contains
* SIMO Buck.
*
* \warning Buck converter requires additional external components populated on
* dedicated pins. Refer to device datasheet for details.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckSetVoltage2
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
void Cy_SysPm_BuckSetVoltage2(cy_en_syspm_buck_voltage2_t voltage, bool waitToSettle);


/*******************************************************************************
* Function Name: Cy_SysPm_BuckEnableVoltage2
****************************************************************************//**
*
* Enable the output 2 voltage (Vbuckrf) of the SIMO Buck regulator.
* The output 2 voltage (Vbuckrf) of the Buck regulator is typically used to
* supply the BLE radio.
* This function does following actions, when the Buck regulator does not
* supply the core:
* * Enables the Buck regulator
* * Enables the output 2, but do not enables the output 1.
*
* \note The function does not affect Buck output 1 that typically supplies core.
*
* \warning The function does not select the Buck output 2 voltage and
* does not set/clear the HW-controlled bit for Buck output 2. Call
* Cy_SysPm_BuckSetVoltage2() or Cy_SysPm_BuckSetVoltage2HwControl() to
* configure the Buck output 2.
*
* \warning The function works only on devices with the SIMO Buck regulator.
* Refer to the device datasheet for information on whether the device contains
* the SIMO Buck.
*
* \warning Buck converter requires additional external components populated on
* dedicated pins. Refer to device datasheet for details.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckEnableVoltage2
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
void Cy_SysPm_BuckEnableVoltage2(void);


/*******************************************************************************
* Function Name: Cy_SysPm_BuckIsOutputEnabled
****************************************************************************//**
*
* This function gets the current output status of the Buck outputs.
*
* \param output
* The Buck regulator output. See \ref cy_en_syspm_buck_out_t.
*
* \return
* - True if the requested output is enabled.
* - False if the requested output is disabled.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckIsOutputEnabled
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
bool Cy_SysPm_BuckIsOutputEnabled(cy_en_syspm_buck_out_t output);
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */
/** \} group_syspm_functions_buck */

/**
* \addtogroup group_syspm_functions_callback
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysPm_RegisterCallback
****************************************************************************//**
*
* Registers a new syspm callback.
*
* A callback is a function called after an event in the driver or
* middleware module has occurred. The handler callback API will be executed if
* the specific event occurs. SysPm callbacks are called when changing power
* modes. See \ref cy_stc_syspm_callback_t.
*
* \note The registered callbacks are executed in two orders, based on callback
* mode \ref cy_en_syspm_callback_mode_t. For modes CY_SYSPM_CHECK_READY and
* CY_SYSPM_BEFORE_TRANSITION, the order is same order as callbacks were
* registered.
* For modes CY_SYSPM_AFTER_TRANSITION and CY_SYSPM_CHECK_FAIL, the order is
* reverse as the order callbacks were registered.
*
* \param handler
* The address of the syspm callback structure.
* See \ref cy_stc_syspm_callback_t.
*
* \return
* - True if a callback was registered.
* - False if a callback was not registered.
*
* \note Do not modify the registered structure in run-time.
* \warning After being registered, the SysPm callback structures must be
* allocated during power mode transition.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Func_Declaration
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Params_Declaration
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Structure_Declaration
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Callback_Func_Implementation
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_RegisterCallback
*
*******************************************************************************/
bool Cy_SysPm_RegisterCallback(cy_stc_syspm_callback_t *handler);


/*******************************************************************************
* Function Name: Cy_SysPm_UnregisterCallback
****************************************************************************//**
*
* This function unregisters a callback.
*
* The registered callback can be unregistered and the function returns true.
* Otherwise, false is returned.
*
* \param handler The item that should be unregistered.
* See \ref cy_stc_syspm_callback_t.
*
* \return
* - True if callback was unregistered.
* - False if it was not unregistered or no callbacks are registered.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_UnregisterCallback
*
*******************************************************************************/
bool Cy_SysPm_UnregisterCallback(cy_stc_syspm_callback_t const *handler);


/*******************************************************************************
* Function Name: Cy_SysPm_ExecuteCallback
****************************************************************************//**
*
* The function executes all registered callbacks with provided type and mode.
* \note This low-level function is being used by \ref Cy_SysPm_CpuEnterSleep,
* \ref Cy_SysPm_CpuEnterDeepSleep, \ref Cy_SysPm_SystemEnterHibernate,
* \ref Cy_SysPm_SystemEnterUlp and \ref Cy_SysPm_SystemEnterLp API functions.
* However, it might be also useful as an independent API function in some custom
* applications.
*
* \note The registered callbacks will be executed in order based on
* \ref cy_en_syspm_callback_type_t value. There are two possible callback
* execution orders:
* * From first registered to last registered. This order applies to
*   callbacks with mode CY_SYSPM_CHECK_READY and CY_SYSPM_BEFORE_TRANSITION.
* * Backward flow execution:
*   - From last registered to the first registered. This order applies
*     to callbacks with mode CY_SYSPM_AFTER_TRANSITION.
*   - From last called to the first registered callback. This order applies
*     to callbacks with mode CY_SYSPM_CHECK_FAIL. Note that, the last called
*     callback function  that generated the CY_SYSPM_CHECK_FAIL is skipped when
*     mode CY_SYSPM_CHECK_FAIL. This is because the callback that returns
*     CY_SYSPM_FAIL already knows that it failed and will not take any action
*     that requires correction.
*
* If no callbacks are registered, returns CY_SYSPM_SUCCESS.
*
* \param type
* The callback type. See \ref cy_en_syspm_callback_type_t.
*
* \param mode
* The callback mode. See \ref cy_en_syspm_callback_mode_t.
*
* \return
* - CY_SYSPM_SUCCESS if callback successfully completed or nor callbacks
*   registered.
* - CY_SYSPM_FAIL one of the executed callback(s) returned fail.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_ExecuteCallback
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_ExecuteCallback(cy_en_syspm_callback_type_t type, cy_en_syspm_callback_mode_t mode);


/*******************************************************************************
* Function Name: Cy_SysPm_GetFailedCallback
****************************************************************************//**
*
* Reads the result of the callback execution after the power mode functions
* execution.
*
* This function reads the value of the pointer that stores the result of callback
* execution. It takes power mode as the parameter and returns the address of the
* callback configuration structure in the case of failure or NULL in the case of
* success. This address of the failed callback allows finding the callback that
* blocks entering power mode.
*
* \param type
* Power mode for which a callback execution result is required.
*
* \return
* - The address of the callback configuration structure if the callback handler
* function failed.
* - NULL if the callback skipped or executed successfully.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_GetFailedCallback
*
*******************************************************************************/
cy_stc_syspm_callback_t* Cy_SysPm_GetFailedCallback(cy_en_syspm_callback_type_t type);
/** \} group_syspm_functions_callback */

/**
* \addtogroup group_syspm_functions_power_status
* \{
*/
#if defined (CY_IP_MXS40SRSS)  || defined (CY_DOXYGEN)

#if (CY_IP_MXS40SRSS_VERSION < 3)  || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_Cm4IsActive
****************************************************************************//**
*
* Checks if CM4 is in CPU Active mode.
*
* \return
* - True if CM4 is in CPU Active mode.
* - False if the CM4 is not in CPU Active mode.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm4IsActive
*
*******************************************************************************/
bool Cy_SysPm_Cm4IsActive(void);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm4IsSleep
****************************************************************************//**
*
* Checks if the CM4 is in CPU Sleep mode.
*
* \return
* - True if the CM4 is in CPU Sleep mode.
* - False if the CM4 is not in CPU Sleep mode.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm4IsSleep
*
*******************************************************************************/
bool Cy_SysPm_Cm4IsSleep(void);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm4IsDeepSleep
****************************************************************************//**
*
* Checks if the CM4 is in the CPU Deep Sleep mode.
*
* \return
* - True if CM4 is in CPU Deep Sleep mode.
* - False if the CM4 is not CPU in Deep Sleep mode.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm4IsDeepSleep
*
*******************************************************************************/
bool Cy_SysPm_Cm4IsDeepSleep(void);

/*******************************************************************************
* Function Name: Cy_SysPm_IsSystemUlp
****************************************************************************//**
*
* Checks if the system is in ULP mode.
*
* \return
* - True the system is in ULP mode.
* - False the system is is not ULP mode.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_IsSystemUlp
*
*******************************************************************************/
bool Cy_SysPm_IsSystemUlp(void);

#endif

/*******************************************************************************
* Function Name: Cy_SysPm_Cm0IsActive
****************************************************************************//**
*
* Checks if the CM0+ is in CPU Active mode.
*
* \return
* - True if the CM0+ is in CPU Active mode.
* - False if the CM0+ is not in CPU Active mode.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm0IsActive
*
*******************************************************************************/
bool Cy_SysPm_Cm0IsActive(void);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm0IsSleep
****************************************************************************//**
*
* Checks if the CM0+ is in CPU Sleep mode.
*
* \return
* - True if the CM0+ is in CPU Sleep mode.
* - False if the CM0+ is not in CPU Sleep mode.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm0IsSleep
*
*******************************************************************************/
bool Cy_SysPm_Cm0IsSleep(void);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm0IsDeepSleep
****************************************************************************//**
*
* Checks if the CM0+ is in CPU Deep Sleep mode.
*
* \return
* - True if the CM0+ is in CPU Deep Sleep mode
* - False if the CM0+ is not in CPU Deep Sleep mode
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_Cm0IsDeepSleep
*
*******************************************************************************/
bool Cy_SysPm_Cm0IsDeepSleep(void);

/*******************************************************************************
* Function Name: Cy_SysPm_IsSystemLp
****************************************************************************//**
*
* Checks if the system is in LP mode.
*
* \return
* - True the system is in LP mode.
* - False the system is not in LP mode.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_IsSystemLp
*
*******************************************************************************/
bool Cy_SysPm_IsSystemLp(void);

#if (CY_IP_MXS40SRSS_VERSION >= 3)
/*******************************************************************************
* Function Name: Cy_SysPm_Cm0IsLowPower
****************************************************************************//**
*
* Checks if the CM0+ is in the low power mode.
*
* \return
* true - if the CM0+ is in the low power mode,
* false - if the CM0+ is not in the low power mode.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_Cm0IsLowPower(void);

/*******************************************************************************
* Function Name: Cy_SysPm_IsBgRefCtrl
****************************************************************************//**
*
* Get the power mode status of Bandgap Ref Circuits
*
* \return
* true - Bandgap Ref Circuits power mode is enabled,
* false - Bandgap Ref Circuits power mode is disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_IsBgRefCtrl(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BgRefCtrl
****************************************************************************//**
*
* Enables/Disables powers mode of Bandgap Ref Circuits
*
* \param enable
* true - to enable, false - to disable
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_BgRefCtrl(bool enable);

#endif

#endif

#if defined(CY_IP_M7CPUSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_Cm7IsActive
****************************************************************************//**
*
* Checks if CM7 is in the active mode.
*
* \param core
* Selects the core, 0 for CM7_0, 1 for CM7_1
*
* \note
* This API is available for CAT1C devices.
*
* \return
* true - if CM7 is in the active mode, false - if the CM7 is not in active mode.
*
*******************************************************************************/
bool Cy_SysPm_Cm7IsActive(uint8_t core);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm7IsSleep
****************************************************************************//**
*
* Checks if the CM4 is in the sleep mode.
*
* \param core
* Selects the core, 0 for CM7_0, 1 for CM7_1
*
* \note
* This API is available for CAT1C devices.
*
* \return
* true - if the CM7 is in the sleep mode,
* false - if the CM7 is not in the sleep mode.
*
*******************************************************************************/
bool Cy_SysPm_Cm7IsSleep(uint8_t core);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm7IsDeepSleep
****************************************************************************//**
*
* Checks if the CM7 is in the deep sleep mode.
*
* \param core
* Selects the core, 0 for CM7_0, 1 for CM7_1
*
* \return
* true - if CM7 is in the deep sleep mode, false - if the CM7 is not in
* the deep sleep mode.
*
*******************************************************************************/
bool Cy_SysPm_Cm7IsDeepSleep(uint8_t core);


/*******************************************************************************
* Function Name: Cy_SysPm_Cm4IsLowPower
****************************************************************************//**
*
* Checks if the CM7 is in the low power mode.
*
* \param core
* Selects the core, 0 for CM7_0, 1 for CM7_1
*
* \note
* This API is available for CAT1C devices.
*
* \return
* true - if the CM7 is in the low power mode,
* false - if the CM7 is not in the low power mode.
*
*******************************************************************************/
bool Cy_SysPm_Cm7IsLowPower(uint8_t core);


#endif
/** \} group_syspm_functions_power_status */


/**
* \addtogroup group_syspm_functions_power
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysPm_CpuSendWakeupEvent
****************************************************************************//**
*
* Sends the SEV (Send Event) ARM instruction to the system.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_CpuSendWakeupEvent
*
*******************************************************************************/
void Cy_SysPm_CpuSendWakeupEvent(void);


#if defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_SystemIsMinRegulatorCurrentSet
****************************************************************************//**
*
* Check whether the system regulator is set to minimal current mode.
*
* \return
* - True - system is in regulator minimum current mode.
* - False - system is in normal regulator current mode.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_SystemSetNormalRegulatorCurrent
*
*******************************************************************************/
bool Cy_SysPm_SystemIsMinRegulatorCurrentSet(void);
#endif /* defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN) */
/** \} group_syspm_functions_power */


#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)
/**
* \addtogroup group_syspm_functions_buck
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysPm_BuckIsEnabled
****************************************************************************//**
*
* Get the current status of the Buck regulator.
*
* \return
* - True if the Buck regulator is enabled.
* - False if it is disabled.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
*******************************************************************************/
bool Cy_SysPm_BuckIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysPm_BuckGetVoltage1
****************************************************************************//**
*
* Gets the current nominal output 1 voltage (Vccbuck1) of
* the Buck regulator.
*
* \note The actual device output 1 voltage (Vccbuck1) can be different from
* the nominal voltage because the actual voltage value depends on conditions
* including load current.
*
* \return
* The nominal output voltage 1 (Vccbuck1) of the Buck regulator.
* See \ref cy_en_syspm_buck_voltage1_t.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
* \note
* This API is available for CAT1A devices.
*
*
*******************************************************************************/
cy_en_syspm_buck_voltage1_t Cy_SysPm_BuckGetVoltage1(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BuckGetVoltage2
****************************************************************************//**
*
* Gets the current output 2 nominal voltage (Vbuckrf) of the SIMO
* Buck regulator.
*
* \note The actual device output 2 voltage (Vbuckrf) can be different from the
* nominal voltage because the actual voltage value depends on conditions
* including load current.
*
* \return
* The nominal output voltage of the Buck SIMO regulator output 2
* voltage (Vbuckrf). See \ref cy_en_syspm_buck_voltage2_t.
*
* \note
* Function returns zero for devices without a SIMO Buck regulator.
* Refer to the device datasheet about information on whether device contains
* a SIMO Buck.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckGetVoltage2
*
*******************************************************************************/
cy_en_syspm_buck_voltage2_t Cy_SysPm_BuckGetVoltage2(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BuckDisableVoltage2
****************************************************************************//**
*
* Disables the output 2 voltage (Vbuckrf) of the SIMO Buck regulator. The
* output 2 voltage (Vbuckrf) of the Buck regulator is typically used to supply
* the BLE radio.
*
* \note The function does not have effect, if the Buck regulator is
* switched off.
*
* \note If you are switching the voltage supply source for BLE radio, ensure
* that the new voltage supply for the BLE HW block is settled
* and is stable before calling the Cy_SysPm_BuckDisableVoltage2() function.
*
* This function is applicable for devices with the SIMO Buck regulator.
* Refer to the device datasheet for information about whether the device
* contains a SIMO Buck.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckDisableVoltage2
*
*******************************************************************************/
void Cy_SysPm_BuckDisableVoltage2(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BuckSetVoltage2HwControl
****************************************************************************//**
*
* Sets the hardware control for SIMO Buck output 2 (Vbuckrf).
*
* When hardware control is enabled for the Vbuckrf output, the firmware
* controlled enable register setting is ignored and the hardware signal is used
* instead. If the product has supporting hardware like BLE radio, it can
* directly control the enable signal for Vbuckrf.
*
* \param hwControl
* Enables/disables hardware control for the SIMO Buck output 2.
*
* Function does not have an effect if SIMO Buck regulator is disabled.
*
* The function is applicable for devices with the SIMO Buck regulator.
* Refer to the device datasheet for information about whether the device
* contains a SIMO Buck.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckSetVoltage2HwControl
*
*******************************************************************************/
void Cy_SysPm_BuckSetVoltage2HwControl(bool hwControl);

/*******************************************************************************
* Function Name: Cy_SysPm_BuckIsVoltage2HwControlled
****************************************************************************//**
*
* Returns the hardware control state for Buck output 2 (Vbuckrf).
*
* When hardware control is enabled for the Vbuckrf output, the firmware
* controlled enable register setting is ignored and the hardware signal is used
* instead. If the product has supporting hardware like BLE radio, it can
* directly control the enable signal for Vbuckrf.
*
* \return
* - True if HW control is set.
* - False if FW control is set for the Buck output 2.
*
* The function is applicable for devices with the SIMO Buck regulator.
* Refer to device datasheet about information if device contains
* SIMO Buck.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BuckIsVoltage2HwControlled
*
*******************************************************************************/
bool Cy_SysPm_BuckIsVoltage2HwControlled(void);
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */


#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckSetVoltage
****************************************************************************//**
*
* Set the Core Buck Regulator Voltage
*
* \param voltage
* Pick from \ref cy_en_syspm_core_buck_voltage_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CoreBuckSetVoltage(cy_en_syspm_core_buck_voltage_t voltage);

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckGetVoltage
****************************************************************************//**
*
* Get the Core Buck Regulator Voltage
*
* \return
* Gets enum value of type \ref cy_en_syspm_core_buck_voltage_t
*
* \note
* This API is available for CAT1B devices.
*
* \return
* see \ref cy_en_syspm_status_t.
*
*******************************************************************************/
cy_en_syspm_core_buck_voltage_t Cy_SysPm_CoreBuckGetVoltage(void);

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckSetMode
****************************************************************************//**
*
* Set the Core Buck Regulator mode
*
* \param mode
* Pick from \ref cy_en_syspm_core_buck_mode_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_CoreBuckSetMode(cy_en_syspm_core_buck_mode_t mode);

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckGetMode
****************************************************************************//**
*
* Get the Core Buck Regulator Mode
*
* \return
* Gets enum value of type \ref cy_en_syspm_core_buck_mode_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_core_buck_mode_t Cy_SysPm_CoreBuckGetMode(void);

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckConfig
****************************************************************************//**
*
* Configures the Core Buck Regulator
*
* \note
* Core buck voltage and mode are selected based on a voting system by the
* following 5 requesters
* Deepsleep Requester, SDR0 DS Requester, SDR0 Requester, SDR1 Requester and
* Extra Requester.
* The requesters may all request different voltages and CBUCK modes.
* When multiple requesters are used for a profile, the requests are harmonized
* into a composite request according to rules:
*  - The composite CBUCK voltage request is the maximum voltage from all
*    enabled requesters.
*  - The composite CBUCK mode is the maximum setting among all enabled requesters
*    to get the highest mode.
*
* For information about the CBUCK control, refer to the appropriate device TRM.
*
* \param config
* Structure containing the config parameters, \ref cy_stc_syspm_core_buck_params_t
*
* \note
* This API is available for CAT1B devices.
*
* \return
* see \ref cy_en_syspm_status_t.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CoreBuckConfig(cy_stc_syspm_core_buck_params_t *config);

/*******************************************************************************
* Function Name: Cy_SysPm_CoreBuckStatus
****************************************************************************//**
*
* Get the status of Core Buck Regulator
*
* \return
* Gets enum value of type \ref cy_en_syspm_status_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CoreBuckStatus(void);

/*******************************************************************************
* Function Name: Cy_SysPm_LdoExtraRequesterConfig
****************************************************************************//**
*
* Configures the Extra Requester for Core Buck Regulator
*
* \note
* The extra requester caters to two special cases:
*   - To temporarily force the system to choose a scratch profile with the
*     settings defined by the extra requester.  This allows other requester
*     settings to be changed without changing the internal setting of an active
*     profile.  This can be used to change the target voltage of an enabled
*     stepdown regulator.
*   - To participate in requester harmonization as an extra requester.
*     This can be used to restrict the composite settings higher than the
*     hardware would normally choose according to the harmonization rules.
*
* For information about the CBUCK control, refer to the appropriate device TRM.
*
* \param extraReqConfig
* Pointer to structure containing the extra requester config parameters,
* \ref cy_stc_syspm_extraReq_params_t
*
* \note
* This API is available for CAT1B devices.
*
* \return
* see \ref cy_en_syspm_status_t.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_LdoExtraRequesterConfig(cy_stc_syspm_extraReq_params_t *extraReqConfig);

#endif
/** \} group_syspm_functions_buck */


/**
* \addtogroup group_syspm_functions_ldo
* \{
*/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3))

/*******************************************************************************
* Function Name: Cy_SysPm_LdoGetVoltage
****************************************************************************//**
*
* Gets the current output voltage value of the core LDO regulator.
*
* \note The actual device Vccd voltage can be different from the
* nominal voltage because the actual voltage value depends on conditions
* including the load current.
*
* \return
* The nominal output voltage of the LDO. See \ref cy_en_syspm_ldo_voltage_t.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
cy_en_syspm_ldo_voltage_t Cy_SysPm_LdoGetVoltage(void);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */

/*******************************************************************************
* Function Name: Cy_SysPm_LdoIsEnabled
****************************************************************************//**
*
* Reads the current status of the core LDO regulator.
*
* \return
* - True means the LDO is enabled.
* - False means it is disabled.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_VoltageRegulator
*
*******************************************************************************/
bool Cy_SysPm_LdoIsEnabled(void);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_SdrConfigure
****************************************************************************//**
*
* Configures the SDR(Step Down Regulator)
*
* \note
*  The CBUCK voltage selection must be 60mV higher than the SDR output or the
* regulator output may bypass.
*
* \param sdr
* CY_SYSPM_SDR_0 - for SDR0
* CY_SYSPM_SDR_1 - for SDR1
*
* \param config
* Structure containing the config parameters, \ref cy_stc_syspm_sdr_params_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_SdrConfigure(cy_en_syspm_sdr_t sdr, cy_stc_syspm_sdr_params_t *config);

/*******************************************************************************
* Function Name: Cy_SysPm_SdrSetVoltage
****************************************************************************//**
*
* Set the SDR(Step Down Regulator) Voltage
*
* \note
*  The CBUCK voltage selection must be 60mV higher than the SDR output or the
* regulator output may bypass.
*
* \param sdr
* CY_SYSPM_SDR_0 - for SDR0
* CY_SYSPM_SDR_1 - for SDR1
*
* \param voltage
* Pick from \ref cy_en_syspm_sdr_voltage_t
*

* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_SdrSetVoltage(cy_en_syspm_sdr_t sdr, cy_en_syspm_sdr_voltage_t voltage);


/*******************************************************************************
* Function Name: Cy_SysPm_SdrGetVoltage
****************************************************************************//**
*
* Get the SDR(Step Down Regulator) Voltage
*
* \param sdr
* CY_SYSPM_SDR_0 - for SDR0
* CY_SYSPM_SDR_1 - for SDR1
*
* \return
* Gets Voltage enum value of type \ref cy_en_syspm_sdr_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_sdr_voltage_t Cy_SysPm_SdrGetVoltage(cy_en_syspm_sdr_t sdr);

/*******************************************************************************
* Function Name: Cy_SysPm_SdrEnable
****************************************************************************//**
*
* Enable the SDR(Step Down Regulator)
*
* \note
* Applicable for only SDR1, whereas SDR0 is always enabled.
*
* \param sdr
* CY_SYSPM_SDR_0 - for SDR0
* CY_SYSPM_SDR_1 - for SDR1
*
* \param enable
* true - enable, false - disable
*
* \note
* This function is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_SdrEnable(cy_en_syspm_sdr_t sdr, bool enable);

/*******************************************************************************
* Function Name: Cy_SysPm_IsSdrEnabled
****************************************************************************//**
*
* Checks if SDR(Step Down Regulator) is enabled or not.
*
* \param sdr
* CY_SYSPM_SDR_0 - for SDR0
* CY_SYSPM_SDR_1 - for SDR1
*
* \return
* True if enabled, False if disabled.
*
* \note
* This function is available for CAT1B devices.
*
*******************************************************************************/
bool Cy_SysPm_IsSdrEnabled(cy_en_syspm_sdr_t sdr);

/*******************************************************************************
* Function Name: Cy_SysPm_HvLdoConfigure
****************************************************************************//**
*
* Configures the HVLDO Regulator
*
* \param config
* Structure containing the config parameters, \ref cy_stc_syspm_hvldo_params_t
*
* \note
* This function is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_HvLdoConfigure(cy_stc_syspm_hvldo_params_t *config);

/*******************************************************************************
* Function Name: Cy_SysPm_HvLdoSetVoltage
****************************************************************************//**
*
* Set the HVLDO Regulator Voltage
*
* \param voltage
* Pick from \ref cy_en_syspm_hvldo_voltage_t
*
* \note
* This function is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_HvLdoSetVoltage(cy_en_syspm_hvldo_voltage_t voltage);

/*******************************************************************************
* Function Name: Cy_SysPm_HvLdoGetVoltage
****************************************************************************//**
*
* Get the HVLDO Regulator Voltage
*
* \return
* Gets Voltage enum value of type \ref cy_en_syspm_hvldo_voltage_t
*
* \note
* This function is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_hvldo_voltage_t Cy_SysPm_HvLdoGetVoltage(void);

/*******************************************************************************
* Function Name: Cy_SysPm_HvLdoEnable
****************************************************************************//**
*
* Enable the HVLDO Regulator
*
* \param enable
* true - enable, false - disable
*
* \note
* This parameter is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysPm_HvLdoEnable(bool enable);

/*******************************************************************************
* Function Name: Cy_SysPm_IsHvLdoEnabled
****************************************************************************//**
*
* Checks if HVLDO Regulator is enabled or not.
*
* \return
* True if enabled, False if disabled.
*
* \note
* This parameter is available for CAT1B devices.
*
*******************************************************************************/
bool Cy_SysPm_IsHvLdoEnabled(void);

#endif
/** \} group_syspm_functions_ldo */


/**
* \addtogroup group_syspm_functions_iofreeze
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysPm_IoIsFrozen
****************************************************************************//**
*
* Checks whether IOs are frozen.
*
* \return
* - True if IOs are frozen.
* - False if IOs are unfrozen.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_IoUnfreeze
*
*******************************************************************************/
bool Cy_SysPm_IoIsFrozen(void);

/*******************************************************************************
* Function Name: Cy_SysPm_IoUnfreeze
****************************************************************************//**
*
* This function unfreezes the I/O cells that are automatically frozen when
* Hibernate is entered with the call to \ref Cy_SysPm_SystemEnterHibernate().
*
* I/O cells remain frozen after a wakeup from Hibernate mode until the
* firmware unfreezes them by calling this function.
*
* If the firmware must retain the data value on the pin, then the
* value must be read and re-written to the pin's port data register before
* calling this function. Furthermore, the drive mode must be re-programmed
* before the pins are unfrozen. If this is not done, the pin will change to
* the default state the moment the freeze is removed.
*
* Note that I/O cell configuration can be changed while frozen. The new
* configuration becomes effective only after the pins are unfrozen.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_IoUnfreeze
*
*******************************************************************************/
void Cy_SysPm_IoUnfreeze(void);

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/*******************************************************************************
* Function Name: Cy_SysPm_IoFreeze
****************************************************************************//**
*
* Freezes IOs.
*
* Freezes the IO cells directly to save the IO-cell state on a wakeup from the
* Hibernate. Do not call this function before entering the
* Hibernate mode, because Cy_SysPm_Hibernate() function freezes the IO cells.
*
* \note
* This function is available for CAT1C devices.
*
******************************************************************************/
void Cy_SysPm_IoFreeze(void);
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_DeepSleepIoIsFrozen
****************************************************************************//**
*
* Checks whether IOs are frozen during DEEPSLEEP-RAM/OFF
*
* \return
* - True if IOs are frozen.
* - False if IOs are unfrozen.
*
*******************************************************************************/
bool Cy_SysPm_DeepSleepIoIsFrozen(void);

/*******************************************************************************
* Function Name: Cy_SysPm_DeepSleepIoUnfreeze
****************************************************************************//**
*
* This function unfreezes the I/O cells that are automatically frozen when
* DEEPSLEEP-RAM/OFF is entered.
*
* I/O cells remain frozen after a wakeup from DEEPSLEEP_RAM/OFF mode until the
* firmware unfreezes them by calling this function.
*
* If the firmware must retain the data value on the pin, then the
* value must be read and re-written to the pin's port data register before
* calling this function. Furthermore, the drive mode must be re-programmed
* before the pins are unfrozen. If this is not done, the pin will change to
* the default state the moment the freeze is removed.
*
* Note that I/O cell configuration can be changed while frozen. The new
* configuration becomes effective only after the pins are unfrozen.
*
*******************************************************************************/
void Cy_SysPm_DeepSleepIoUnfreeze(void);

#endif

/** \} group_syspm_functions_iofreeze */



/**
* \addtogroup group_syspm_functions_pmic
* \{
*/

#if defined (CY_IP_MXS40SRSS)

/*******************************************************************************
* Function Name: Cy_SysPm_PmicEnable
****************************************************************************//**
*
* Enable the external PMIC controller that supplies Vddd (if present).
*
* For information about the PMIC controller input and output pins and their
* assignment in specific devices, refer to the appropriate device TRM.
*
* This function is not effective when the PMIC controller is locked. Call
* Cy_SysPm_PmicUnlock() before enabling the PMIC.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicEnable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicEnable(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicDisable
****************************************************************************//**
*
* Disable the external PMIC controller that supplies Vddd (if present).
* This function does not affect the PMIC controller output pin. The PMIC
* controller input pin has programmable polarity to
* enable the external PMIC using different input polarities. The PMIC controller
* is automatically enabled when the input pin polarity and configured polarity
* match. This function is not effective when the active level of PMIC controller
* input pin is equal to the configured PMIC controller polarity.
*
* The function is not effective when the PMIC controller is locked. Call
* Cy_SysPm_PmicUnlock() before enabling the PMIC controller.
*
* \param polarity
* Configures the PMIC controller wakeup input pin to be active low or active
* high. The PMIC will be automatically enabled when the set polarity and the
* active level of PMIC input pin match.
* See \ref cy_en_syspm_pmic_wakeup_polarity_t.
*
* The PMIC controller will be enabled automatically by any of RTC alarm or
* PMIC wakeup events, regardless of the PMIC controller lock state.
*
* \note
* Before disabling the PMIC controller, ensure that PMIC input and PMIC output
* pins are configured correctly to enable expected PMIC operation.
*
* \warning
* The PMIC is enabled automatically when you call Cy_SysPm_PmicLock().
* To keep the external PMIC disabled, the PMIC controller must remain unlocked.
*
* \warning
* Do not call Cy_SysPm_PmicDisable(CY_SYSPM_PMIC_POLARITY_LOW) because this
* is not supported by hardware.
*
* For information about the PMIC controller input and output pins and their
* assignment in the specific devices, refer to the appropriate
* device TRM.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicDisable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicDisable(cy_en_syspm_pmic_wakeup_polarity_t polarity);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicAlwaysEnable
****************************************************************************//**
*
* Enable the external PMIC controller that supplies Vddd (if present) and force
* active. This is a Write once API. It ensures that the PMIC controller cannot
* be disabled or polarity changed until a next device reset.
*
* For information about the PMIC controller input and output pins and their
* assignment in the specific devices, refer to the appropriate device TRM.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicAlwaysEnable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicAlwaysEnable(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicEnableOutput
****************************************************************************//**
*
* Enables the PMIC controller output pin.
*
* The function is not effective when the PMIC controller is locked. Call
* Cy_SysPm_PmicUnlock() before enabling the PMIC controller.
*
* For information about the PMIC controller output pin and its assignment in
* specific devices, refer to the appropriate device TRM.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicEnableOutput
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicEnableOutput(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicDisableOutput
****************************************************************************//**
*
* Disables the PMIC controller output pin.
*
* When the PMIC controller output pin is disabled and is unlocked, the PMIC
* controller output pin can be used for the another purpose.
*
* The function has no effect when the PMIC is locked. Call
* Cy_SysPm_PmicUnlock() before enabling the PMIC.
*
* For information about the PMIC controller output pin and its assignment in
* specific devices, refer to the appropriate device TRM.
*
* \note
* After the PMIC controller output is disabled, the PMIC output pin returns to
* its GPIO configured state.
*
* \warning
* The PMIC controller output is enabled automatically when you call
* Cy_SysPm_PmicLock(). To keep the PMIC controller output disabled, the PMIC
* controller must remain unlocked.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicDisableOutput
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicDisableOutput(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicLock
****************************************************************************//**
*
* Locks the PMIC control controller register so that no changes can be made.
* The changes are related to PMIC enabling/disabling and PMIC output pin
* enabling/disabling.
*
* \warning
* The PMIC controller and/or the PMIC output are enabled automatically when
* you call Cy_SysPm_PmicLock(). To keep the PMIC or PMIC controller output
* disabled, the PMIC controller must remain unlocked.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicLock
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicLock(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicUnlock
****************************************************************************//**
*
* Unlocks the PMIC control register so that changes can be made. The changes are
* related to the PMIC controller enabling/disabling and PMIC output pin
* enabling/disabling.
*
* \warning
* The PMIC controller and/or the PMIC output are enabled automatically when
* you call Cy_SysPm_PmicLock(). To keep the PMIC controller or PMIC output
* disabled, the PMIC must remain unlocked.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicEnable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_PmicUnlock(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicIsEnabled
****************************************************************************//**
*
* This function returns the status of the PMIC controller.
*
* \return
* - True if the PMIC is enabled.
* - False if the PMIC is disabled.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicLock
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_PmicIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicIsOutputEnabled
****************************************************************************//**
*
* This function returns the status of the PMIC controller output.
*
* \return
* - True if the PMIC output is enabled.
* - False if the PMIC output is disabled.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicDisable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_PmicIsOutputEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysPm_PmicIsLocked
****************************************************************************//**
*
* Returns the PMIC controller lock status.
*
* \return
* - True if the PMIC is locked.
* - False if the PMIC is unlocked.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_PmicLock
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
bool Cy_SysPm_PmicIsLocked(void);
#endif /* CY_IP_MXS40SRSS */
/** \} group_syspm_functions_pmic */


/**
* \addtogroup group_syspm_functions_backup
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysPm_BackupSetSupply
****************************************************************************//**
*
* Sets the backup supply (Vddback) operation mode.
*
* \param
* vddBackControl
* Selects backup supply (Vddback) operation mode.
* See \ref cy_en_syspm_vddbackup_control_t.
*
* Refer to device TRM for more detail about backup supply modes.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BackupSetSupply
*
*******************************************************************************/
void Cy_SysPm_BackupSetSupply(cy_en_syspm_vddbackup_control_t vddBackControl);


/*******************************************************************************
* Function Name: Cy_SysPm_BackupGetSupply
****************************************************************************//**
*
* Returns the current backup supply (Vddback) operation mode.
*
* \return
* The current backup supply (Vddback) operation mode,
* see \ref cy_en_syspm_status_t.
*
* Refer to device TRM for more detail about backup supply modes.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BackupGetSupply
*
*******************************************************************************/
cy_en_syspm_vddbackup_control_t Cy_SysPm_BackupGetSupply(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BackupEnableVoltageMeasurement
****************************************************************************//**
*
* This function enables Vbackup supply measurement by the ADC. The function
* connects the Vbackup supply to AMuxBusA. The ADC input can then be connected
* to AMuxBusA. Note that the measured signal is scaled by 10% to allow full
* range measurement by the ADC.
*
* Refer to device TRM for more detail about Vbackup supply measurement.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BackupEnableVoltageMeasurement
*
*******************************************************************************/
void Cy_SysPm_BackupEnableVoltageMeasurement(void);


/*******************************************************************************
* Function Name: Cy_SysPm_BackupDisableVoltageMeasurement
****************************************************************************//**
*
* The function disables Vbackup supply measurement by the ADC by disconnecting
* the Vbackup supply from AMuxBusA.
*
* Refer to device TRM for more detail about Vbackup supply measurement.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BackupDisableVoltageMeasurement
*
*******************************************************************************/
void Cy_SysPm_BackupDisableVoltageMeasurement(void);

/*******************************************************************************
* Function Name: Cy_SysPm_BackupSuperCapCharge
****************************************************************************//**
*
* Configures the supercapacitor charger circuit.
*
* \param key
* Passes the key to enable or disable the supercapacitor charger circuit.
* See \ref cy_en_syspm_sc_charge_key_t.
*
* \warning
* This function is used only for charging the supercapacitor.
* Do not use this function to charge a battery. Refer to device TRM for more
* detail.
*
* \funcusage
* \snippet syspm/snippet/main.c snippet_Cy_SysPm_BackupSuperCapCharge
*
*******************************************************************************/
void Cy_SysPm_BackupSuperCapCharge(cy_en_syspm_sc_charge_key_t key);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysPm_BackupWordStore
****************************************************************************//**
*
* Stores supported number of words(SRSS_BACKUP_NUM_BREG) in Backup Domain
*
* \param wordIndex
* Offset/Index of Backup Register Region(BREG) to where the data needs
* to be stored.
* Starts with 0, ends with (SRSS_BACKUP_NUM_BREG - 1)
*
* \param wordSrcPointer
* Source address from where the words have to be picked and backed up.
*
* \param wordSize
* Number of words to be stored
*
* \note
* This API is available for CAT1B & CAT1C devices.
*
*******************************************************************************/

void Cy_SysPm_BackupWordStore(uint32_t wordIndex, uint32_t *wordSrcPointer, uint32_t wordSize);

/*******************************************************************************
* Function Name: Cy_SysPm_BackupWordReStore
****************************************************************************//**
*
* Restores supported number of words(SRSS_BACKUP_NUM_BREG) in Backup Domain
*
* \param wordIndex
* Offset/Index of Backup Register Region(BREG) from where the data need
* to be Restored.
* Starts with 0, ends with (SRSS_BACKUP_NUM_BREG - 1)
*
* \param wordDstPointer
* Destination address from where the backed up words have to be written.
*
* \param wordSize
* Number of words to be Restored
*
* \note
* This API is available for CAT1B & CAT1C devices.
*
*******************************************************************************/
void Cy_SysPm_BackupWordReStore(uint32_t wordIndex, uint32_t *wordDstPointer, uint32_t wordSize);
#endif

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysPm_SetupDeepSleepRAM
****************************************************************************//**
*
* Implements Pre and Post Deepsleep RAM Setup.
*
* \param dsramCheck
* CY_SYSPM_PRE_DSRAM or CY_SYSPM_POST_DSRAM
*
* \param dsramIntState
* Variable to save the interrupt state before and after Deepsleep RAM.
*
* \return
* - CY_SYSPM_SUCCESS - Deepsleep RAM checks are successful
* - CY_SYSPM_CANCELED - Operation was canceled. Call the function again until
*   the function returns CY_SYSPM_SUCCESS.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_SetupDeepSleepRAM(cy_en_syspm_dsram_checks_t dsramCheck, uint32_t *dsramIntState);

/*******************************************************************************
* Function Name: Cy_SysPm_CpuEnterRAMOffDeepSleep
****************************************************************************//**
*
* Sets executing CPU to the Deep Sleep mode forceful RAM OFF.
*
* \return
* Entered status, see \ref cy_en_syspm_status_t.
*
* \note
* This API is available for CAT1B devices.
*
* \note
* This API is not a standard PDL interface, it is a custom defined Power
* Management State, not to be used by the customers.
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysPm_CpuEnterRAMOffDeepSleep(void);

#endif


/** \} group_syspm_functions_backup */
/** \} group_syspm_functions */

/** \cond INTERNAL */

/*******************************************************************************
* Backward compatibility macro. The following code is DEPRECATED and must
* not be used in new projects
*******************************************************************************/
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3))
/**
* \note
* These macros is available for CAT1A devices.
**/
/* BWC defines for Buck related functions */
typedef cy_en_syspm_buck_voltage1_t          cy_en_syspm_simo_buck_voltage1_t;
typedef cy_en_syspm_buck_voltage2_t          cy_en_syspm_simo_buck_voltage2_t;

#define Cy_SysPm_SimoBuckGetVoltage2         Cy_SysPm_BuckGetVoltage2
#define Cy_SysPm_DisableVoltage2             Cy_SysPm_BuckDisableVoltage2
#define Cy_SysPm_EnableVoltage2              Cy_SysPm_BuckEnableVoltage2
#define Cy_SysPm_SimoBuckSetHwControl        Cy_SysPm_BuckSetVoltage2HwControl
#define Cy_SysPm_SimoBuckGetHwControl        Cy_SysPm_BuckIsVoltage2HwControlled
#define Cy_SysPm_SimoBuckSetVoltage2         Cy_SysPm_BuckSetVoltage2

#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_15V   CY_SYSPM_BUCK_OUT2_VOLTAGE_1_15V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_2V    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_2V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_25V   CY_SYSPM_BUCK_OUT2_VOLTAGE_1_25V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_3V    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_3V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_35V   CY_SYSPM_BUCK_OUT2_VOLTAGE_1_35V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_4V    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_4V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_45V   CY_SYSPM_BUCK_OUT2_VOLTAGE_1_45V
#define CY_SYSPM_SIMO_BUCK_OUT2_VOLTAGE_1_5V    CY_SYSPM_BUCK_OUT2_VOLTAGE_1_5V

#define CY_SYSPM_SIMO_BUCK_OUT1_VOLTAGE_0_9V     CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V
#define CY_SYSPM_SIMO_BUCK_OUT1_VOLTAGE_1_1V     CY_SYSPM_BUCK_OUT1_VOLTAGE_1_1V

#define Cy_SysPm_SwitchToSimoBuck()          (Cy_SysPm_BuckEnable(CY_SYSPM_BUCK_OUT1_VOLTAGE_0_9V))
#define Cy_SysPm_SimoBuckGetVoltage1         Cy_SysPm_BuckGetVoltage1
#define Cy_SysPm_SimoBuckIsEnabled           Cy_SysPm_BuckIsEnabled
#define Cy_SysPm_SimoBuckSetVoltage1         Cy_SysPm_BuckSetVoltage1
#define Cy_SysPm_SimoBuckOutputIsEnabled     Cy_SysPm_BuckIsOutputEnabled
#endif /* CY_IP_MXS40SRSS */

#define CY_SYSPM_LPCOMP0_LOW                 CY_SYSPM_HIBERNATE_LPCOMP0_LOW
#define CY_SYSPM_LPCOMP0_HIGH                CY_SYSPM_HIBERNATE_LPCOMP0_HIGH
#define CY_SYSPM_LPCOMP1_LOW                 CY_SYSPM_HIBERNATE_LPCOMP1_LOW
#define CY_SYSPM_LPCOMP1_HIGH                CY_SYSPM_HIBERNATE_LPCOMP1_HIGH
#define CY_SYSPM_HIBALARM                    CY_SYSPM_HIBERNATE_RTC_ALARM
#define CY_SYSPM_HIBWDT                      CY_SYSPM_HIBERNATE_WDT
#define CY_SYSPM_HIBPIN0_LOW                 CY_SYSPM_HIBERNATE_PIN0_LOW
#define CY_SYSPM_HIBPIN0_HIGH                CY_SYSPM_HIBERNATE_PIN0_HIGH
#define CY_SYSPM_HIBPIN1_LOW                 CY_SYSPM_HIBERNATE_PIN1_LOW
#define CY_SYSPM_HIBPIN1_HIGH                CY_SYSPM_HIBERNATE_PIN1_HIGH

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3))
/**
* \note
* These macros is available for CAT1A devices.
**/
#define CY_SYSPM_ENTER_LP_MODE               CY_SYSPM_ULP
#define CY_SYSPM_EXIT_LP_MODE                CY_SYSPM_LP
#define CY_SYSPM_STATUS_SYSTEM_LOWPOWER      CY_SYSPM_STATUS_SYSTEM_ULP
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/**
* \note
* These macros is available for CAT1C devices.
**/
#define CY_SYSPM_STATUS_SYSTEM_LOWPOWER      CY_SYSPM_STATUS_SYSTEM_LPACTIVE
#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

typedef cy_en_syspm_hibernate_wakeup_source_t  cy_en_syspm_hib_wakeup_source_t;

/* BWC defines related to hibernation functions */
#define Cy_SysPm_SetHibWakeupSource          Cy_SysPm_SetHibernateWakeupSource
#define Cy_SysPm_ClearHibWakeupSource        Cy_SysPm_ClearHibernateWakeupSource
#define Cy_SysPm_GetIoFreezeStatus           Cy_SysPm_IoIsFrozen

/* BWC defines for Backup related functions */
#define Cy_SysPm_SetBackupSupply             Cy_SysPm_BackupSetSupply
#define Cy_SysPm_GetBackupSupply             Cy_SysPm_BackupGetSupply
#define Cy_SysPm_EnableBackupVMeasure        Cy_SysPm_BackupEnableVoltageMeasurement
#define Cy_SysPm_DisableBackupVMeasure       Cy_SysPm_BackupDisableVoltageMeasurement

#if defined (CY_IP_MXS40SRSS)
/**
* \note
* These macros is available for CAT1A devices.
**/
/* BWC defines for PMIC related functions */
#define Cy_SysPm_EnablePmic                  Cy_SysPm_PmicEnable
#define Cy_SysPm_DisablePmic                 Cy_SysPm_PmicDisable
#define Cy_SysPm_AlwaysEnablePmic            Cy_SysPm_PmicAlwaysEnable
#define Cy_SysPm_EnablePmicOutput            Cy_SysPm_PmicEnableOutput
#define Cy_SysPm_DisablePmicOutput           Cy_SysPm_PmicDisableOutput
#define Cy_SysPm_LockPmic                    Cy_SysPm_PmicLock
#define Cy_SysPm_UnlockPmic                  Cy_SysPm_PmicUnlock
#define Cy_SysPm_IsPmicEnabled               Cy_SysPm_PmicIsEnabled
#define Cy_SysPm_IsPmicOutputEnabled         Cy_SysPm_PmicIsOutputEnabled
#define Cy_SysPm_IsPmicLocked                Cy_SysPm_PmicIsLocked
#endif /* CY_IP_MXS40SRSS */

/* BWC defines for functions related to low power transition */
#define Cy_SysPm_Sleep                       Cy_SysPm_CpuEnterSleep
#define Cy_SysPm_DeepSleep                   Cy_SysPm_CpuEnterDeepSleep
#define Cy_SysPm_Hibernate                   Cy_SysPm_SystemEnterHibernate

#define Cy_SysPm_SleepOnExit                 Cy_SysPm_CpuSleepOnExit

/* BWC defines for functions related to low power transition */
#define Cy_SysPm_EnterLpMode                 Cy_SysPm_EnterLowPowerMode
#define Cy_SysPm_ExitLpMode                  Cy_SysPm_ExitLowPowerMode
#define Cy_SysPm_IsLowPower                  Cy_SysPm_IsSystemUlp

#define Cy_SysPm_EnterLowPowerMode           Cy_SysPm_SystemSetMinRegulatorCurrent
#define Cy_SysPm_ExitLowPowerMode            Cy_SysPm_SystemSetNormalRegulatorCurrent

#define CY_SYSPM_WAKEUP_PIN0_BIT             CY_SYSPM_HIB_WAKEUP_PIN0_POS
#define CY_SYSPM_WAKEUP_PIN1_BIT             CY_SYSPM_HIB_WAKEUP_PIN1_POS
#define CY_SYSPM_WAKEUP_LPCOMP0_BIT          CY_SYSPM_HIB_WAKEUP_LPCOMP0_POS
#define CY_SYSPM_WAKEUP_LPCOMP1_BIT          CY_SYSPM_HIB_WAKEUP_LPCOMP1_POS

#define CY_SYSPM_WAKEUP_LPCOMP0                  CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK
#define CY_SYSPM_WAKEUP_LPCOMP1                  CY_SYSPM_HIB_WAKEUP_LPCOMP0_MASK
#define CY_SYSPM_WAKEUP_PIN0                     CY_SYSPM_HIB_WAKEUP_PIN0_MASK
#define CY_SYSPM_WAKEUP_PIN1                     CY_SYSPM_HIB_WAKEUP_PIN1_MASK
#define CY_SYSPM_WAKEUP_LPCOMP0_POLARITY_HIGH    CY_SYSPM_HIB_WAKEUP_LPCOMP0_POLARITY_HIGH_MASK
#define CY_SYSPM_WAKEUP_LPCOMP1_POLARITY_HIGH    CY_SYSPM_HIB_WAKEUP_LPCOMP1_POLARITY_HIGH_MASK
#define CY_SYSPM_WAKEUP_PIN0_POLARITY_HIGH       CY_SYSPM_HIB_WAKEUP_PIN0_POLARITY_HIGH_MASK
#define CY_SYSPM_WAKEUP_PIN1_POLARITY_HIGH       CY_SYSPM_HIB_WAKEUP_PIN1_POLARITY_HIGH_MASK

#define CY_SYSPM_PWR_TOKEN_HIBERNATE             HIBERNATE_TOKEN
#define CY_SYSPM_PWR_WAKEUP_HIB_MASK             HIBERNATE_WAKEUP_MASK
#define CY_SYSPM_PWR_RETAIN_HIBERNATE_STATUS     HIBERNATE_RETAIN_STATUS_MASK
#define CY_SYSPM_PWR_SET_HIBERNATE               SET_HIBERNATE_MODE
#define CY_SYSPM_PWR_HIBERNATE_UNLOCK            HIBERNATE_UNLOCK_VAL

/** \endcond */

#ifdef __cplusplus
}
#endif

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) */

#endif /* CY_SYSPM_H */

/** \} group_syspm */


/* [] END OF FILE */
