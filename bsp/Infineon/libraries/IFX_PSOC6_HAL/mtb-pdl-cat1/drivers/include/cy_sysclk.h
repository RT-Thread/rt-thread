/***************************************************************************//**
* \file cy_sysclk.h
* \version 3.50
*
* Provides an API declaration of the sysclk driver.
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
*******************************************************************************/

/**
* \addtogroup group_sysclk
* \{
* The System Clock (SysClk) driver contains the API for configuring system and
* peripheral clocks.
*
* The functions and other declarations used in this driver are in cy_sysclk.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* Firmware uses the API to configure, enable, or disable a clock.
*
* The clock system includes a variety of resources that can vary per device, including:
* - Internal clock sources such as internal oscillators
* - External clock sources such as crystal oscillators or a signal on an I/O pin
* - Generated clocks such as an FLL, a PLL, and peripheral clocks
*
* Consult the Technical Reference Manual for your device for details of the
* clock system.
*
* The PDL defines clock system capabilities in:\n
* devices/COMPONENT_CAT1\<subcategory\>/include/\<series\>_config.h. (E.g.
* devices/COMPONENT_CAT1A/include/psoc6_01_config.h).
*
* As an illustration of the clocking system, the following diagram shows the
* PSoC 63 series clock tree. The actual tree may vary depending on the device series.
* Consult the Technical Reference Manual for your device for details.
* ![](sysclk_tree.png)
*
* The sysclk driver supports multiple peripheral clocks, as well as the fast
* clock, slow clock, backup domain clock, timer clock, and pump clock. The API
* for any given clock contains the functions to manage that clock. Functions
* for clock measurement and trimming are also provided.
*
* \section group_sysclk_configuration Configuration Considerations
* The availability of clock functions depend on the availability of the chip
* resources that support those functions. Consult the device TRM before
* attempting to use these functions.
* For PSoC 64  devices the clocks configurations are restricted and limited.
* Refer to the PRA driver, and the TRM and datasheet for details.
*
* \warning
* On the diagram above, the yellow muxes are glitch-safe. All glitch-safe
* mux transitions take four cycles of the source clock.
* It is not allowed to turn off the source clock during that time.
*
* PSoC 6 power modes limit the maximum clock frequency.
* Refer to the SysPm driver and the TRM for details.
*
* \section group_sysclk_more_information More Information
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_sysclk_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>3.50</td>
*     <td>
*         Bug fixes and few new APIs addition.<br>Newly added APIs:
*         \n Cy_SysClk_PllGetFrequency() for CAT1A,CAT1C and CAT1D devices,
*         \n Cy_SysClk_Pll200MGetFrequency() for CAT1C devices,
*         \n Cy_SysClk_Pll400MGetFrequency() for CAT1C devices,
*         \n Cy_SysClk_ImoEnable() for CAT1D devices,
*         \n Cy_SysClk_ImoDisable() for CAT1D devices,
*         \n Cy_SysClk_ImoIsEnabled() for CAT1D devices,
*         \n Cy_SysClk_ImoDeepsleepEnable() for CAT1D devices,
*         \n Cy_SysClk_ImoIsDeepsleepEnabled() for CAT1D devices,
*         \n Cy_SysClk_ImoDeepsleepDisable() for CAT1D devices,
*         \n Cy_SysClk_ClkFastSrcGetDivider() for CAT1C devices,
*         \n Cy_SysClk_ClkFastSrcSetDivider() for CAT1C devices,
*         \n Cy_SysClk_ClkFastSrcGetFrequency() for CAT1C devices,
*     </td>
*     <td>Bug fixes and new devices support.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">3.40</td>
*     <td>
*         Added CAT1C and CAT1D devices support.
*     </td>
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>New API's for PLL400M and PLL200M.</td>
*     <td>To handle the new PLL's for CAT1C devices.</td>
*   </tr>
*   <tr>
*     <td>New API's Added
*         * Cy_SysClk_Pll200MConfigure()
*         * Cy_SysClk_Pll200MManualConfigure()
*         * Cy_SysClk_Pll200MGetConfiguration()
*         * Cy_SysClk_Pll200MEnable()
*         * Cy_SysClk_Pll200MIsEnabled()
*         * Cy_SysClk_Pll200MLocked()
*         * Cy_SysClk_Pll200MLostLock()
*         * Cy_SysClk_Pll200MDisable()
*         * Cy_SysClk_Pll400MConfigure()
*         * Cy_SysClk_Pll400MManualConfigure()
*         * Cy_SysClk_Pll400MGetConfiguration()
*         * Cy_SysClk_Pll400MEnable()
*         * Cy_SysClk_Pll400MIsEnabled()
*         * Cy_SysClk_Pll400MLocked()
*         * Cy_SysClk_Pll400MLostLock()
*         * Cy_SysClk_Pll200MDisable()
*         * Cy_SysClk_IhoDeepsleepEnable()
*         * Cy_SysClk_IhoIsDeepsleepEnabled()
*         * Cy_SysClk_IhoDeepsleepDisable()
*         * Cy_SysClk_IloSrcEnable()
*         * Cy_SysClk_IloSrcIsEnabled()
*         * Cy_SysClk_IloSrcDisable()
*         * Cy_SysClk_IloSrcHibernateOn()
*         * Cy_SysClk_PiloBackupEnable()
*         * Cy_SysClk_PiloBackupDisable()
*         * Cy_SysClk_PiloTcscEnable()
*         * Cy_SysClk_PiloTcscDisable()
*         * Cy_SysClk_AltHfEnable()
*         * Cy_SysClk_IsAltHfEnabled()
*         * Cy_SysClk_IloSetTrim()
*         * Cy_SysClk_IloGetTrim()
*         * Cy_SysClk_ClkMfSetSource()
*         * Cy_SysClk_ClkMfGetSource()
*         * Cy_SysClk_ClkHfDirectSel()
*         * Cy_SysClk_IsClkHfDirectSelEnabled()
*         * Cy_SysClk_PeriGroupGetSlaveCtl()
*         * Cy_SysClk_IsPeriGroupSlaveCtlSet()
*         * Cy_SysClk_PeriPclkGetFrequency()
*         * Cy_SysClk_PeriPclkGetDividerEnabled()
*         * Cy_Sysclk_PeriPclkGetClkHfNum()
*         * Cy_SysClk_ClkMemSetDivider()
*         * Cy_SysClk_ClkMemGetDivider()
*         * Cy_SysClk_ClkMemGetFrequency()
*
*     </td>
*     <td>New API's to handle CAT1B, CAT1C and CAT1D devices.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">3.30</td>
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
*     <td>Return type doxygen updated for PSoC64 devices.</td>
*     <td>Doxygen update for PSoC64 devices.</td>
*   </tr>
*   <tr>
*     <td>3.20</td>
*     <td>Added new API's \ref Cy_SysClk_FllGetFrequency and \ref Cy_SysClk_PllGetFrequency.</td>
*     <td>Fetch the FLL and PLL frequency.</td>
*   </tr>
*   <tr>
*     <td>3.10</td>
*     <td>Support for CM33.</td>
*     <td>New devices support.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">3.0</td>
*     <td>The behavior of \ref Cy_SysClk_EcoEnable and \ref Cy_SysClk_PllEnable is changed -
*         these functions disable the resource in case of enabling failure (timeout).</td>
*     <td>Usability enhancement.</td>
*   </tr>
*   <tr>
*     <td>The implementation of \ref Cy_SysClk_ClkPathGetSource,
*                               \ref Cy_SysClk_FllConfigure,
*                               \ref Cy_SysClk_FllGetConfiguration,
*                               \ref Cy_SysClk_PllConfigure
*                           and \ref Cy_SysClk_ClkMeasurementCountersGetFreq
*         is updated in accordance to the MISRA 2012 requirements. No behavioral changes.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>2.20.1</td>
*     <td>Updated source code comments.</td>
*     <td>Documentation update.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">2.20</td>
*     <td>Added the assertion mechanism to the following functions:
*         * Cy_SysClk_EcoDisable()
*         * Cy_SysClk_IloEnable()
*         * Cy_SysClk_IloHibernateOn()
*         * Cy_SysClk_PiloEnable()
*         * Cy_SysClk_PiloDisable()
*         * Cy_SysClk_WcoDisable()
*         * Cy_SysClk_WcoBypass()
*         * Cy_SysClk_ClkFastSetDivider()
*         * Cy_SysClk_ClkPeriSetDivider()
*         * Cy_SysClk_ClkLfSetSource()
*         * Cy_SysClk_ClkTimerSetSource()
*         * Cy_SysClk_ClkTimerSetDivider()
*         * Cy_SysClk_ClkTimerEnable()
*         * Cy_SysClk_ClkTimerDisable()
*         * Cy_SysClk_ClkPumpSetSource()
*         * Cy_SysClk_ClkPumpSetDivider()
*         * Cy_SysClk_ClkPumpEnable()
*         * Cy_SysClk_ClkPumpDisable()
*         * Cy_SysClk_ClkBakSetSource()
*
*         Now, the functions described above halt in assertion when a PRA
*         request returns not successful operation. This change is
*         applicable only for the PSoC 64 family devices.
*     </td>
*     <td>Enhancements for the debugging process.</td>
*   </tr>
*   <tr>
*     <td>Added \ref Cy_SysClk_PiloInitialTrim and \ref Cy_SysClk_PiloUpdateTrimStep functions.
*         Extended the \ref Cy_SysClk_PiloTrim function to use the step-size value calculated for PILO
*         based on the \ref Cy_SysClk_PiloInitialTrim and \ref Cy_SysClk_PiloUpdateTrimStep
*         functions call. </td>
*     </td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td>
*          * Added the warning that during a glitch-safe mux, the transition is not allowed
*            to disable the previous clock source. See more info
*            in the \ref group_sysclk_configuration.
*          * Removed Known Issues table.
*     </td>
*     <td>Documentation updates.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">2.10</td>
*     <td>Updated SysClk functions for PSoC 64 devices. Now the SysClk functions can return
*         PRA driver status value.</td>
*     <td>The SysClk driver uses the PRA driver to change the protected registers.
*         A SysClk driver function that calls a PRA driver function will return the PRA
*         error status code if the called PRA function returns an error. In these cases,
*         refer to PRA return statuses. Refer to functions description for details.</td>
*   </tr>
*   <tr>
*     <td>Updated the code of \ref Cy_SysClk_ClkPathGetFrequency function.</td>
*     <td>Make the code more error-resistant to user errors for some corner cases.</td>
*   </tr>
*   <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>2.0</td>
*     <td>Updated the ECO trimming values calculation algorithm in the \ref Cy_SysClk_EcoConfigure implementation. \n
*         This change may invalidate the already used crystals, in cases: \n
*         * The crystal frequency is less than 16 MHz. \n
*         * The maximum amplitude (internal calculation value) is less than 0.65 V. \n
*
*         For detail, refer the \ref Cy_SysClk_EcoConfigure documentation and the ECO Trimming section of the device TRM.</td>
*     <td>Enhanced the ECO performance for high-noise conditions that result from simultaneous switching of GPIOs and/or high switching activity on the chip.</td>
*   </tr>
*   <tr>
*     <td>1.60</td>
*     <td>Added the following functions: \ref Cy_SysClk_ExtClkGetFrequency, \ref Cy_SysClk_EcoGetFrequency,\n
*         \ref Cy_SysClk_ClkPathMuxGetFrequency, \ref Cy_SysClk_ClkPathGetFrequency, \ref Cy_SysClk_IloIsEnabled.\n
*         \ref Cy_SysClk_PiloIsEnabled, \ref Cy_SysClk_AltHfGetFrequency, \ref Cy_SysClk_ClkHfIsEnabled,\n
*         \ref Cy_SysClk_ClkTimerIsEnabled, \ref Cy_SysClk_ClkTimerGetFrequency, \ref Cy_SysClk_ClkPumpIsEnabled and\n
*         \ref Cy_SysClk_ClkPumpGetFrequency.</td>
*     <td>API enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>\ref Cy_SysClk_ClkHfGetFrequency is updated to reuse the \ref cy_BleEcoClockFreqHz global system variable.</td>
*     <td>API enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.40.2</td>
*     <td>Update documentation based on collateral review feedback.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.40.1</td>
*     <td>Fix compiler warning.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td rowspan="4">1.40</td>
*     <td>Updated the following functions implementation: \ref Cy_SysClk_PllConfigure and \ref Cy_SysClk_PllEnable.</td>
*     <td>
*       Fixed the \ref Cy_SysClk_PllConfigure API function behaviour when it is called with a bypass mode, \n
*       Fixed the \ref Cy_SysClk_PllEnable API function behaviour when it is called with a zero timeout.
*     </td>
*   </tr>
*   <tr>
*     <td>Added the following functions: \ref Cy_SysClk_MfoEnable, \ref Cy_SysClk_MfoIsEnabled,\n
*         \ref Cy_SysClk_MfoDisable, \ref Cy_SysClk_ClkMfEnable, \ref Cy_SysClk_ClkMfIsEnabled,\n
*         \ref Cy_SysClk_ClkMfDisable, \ref Cy_SysClk_ClkMfGetDivider, \ref Cy_SysClk_ClkMfSetDivider,\n.
*         \ref Cy_SysClk_ClkMfGetFrequency</td>
*     <td>New device support.</td>
*   </tr>
*   <tr>
*     <td>Added the following new API functions \ref Cy_SysClk_FllIsEnabled, \ref Cy_SysClk_PllIsEnabled,\n
*         \ref Cy_SysClk_ExtClkSetFrequency, \ref Cy_SysClk_ClkHfGetFrequency, \ref Cy_SysClk_ClkFastGetFrequency,\n
*         \ref Cy_SysClk_ClkPeriGetFrequency and \ref Cy_SysClk_ClkSlowGetFrequency</td>
*     <td>Enhancement based on usability feedback</td>
*   </tr>
*   <tr>
*     <td>Deprecated the following macros: CY_SYSCLK_DIV_ROUND and CY_SYSCLK_DIV_ROUNDUP</td>
*     <td>Macros were moved into \ref group_syslib</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.30</td>
*     <td>Updated the following functions implementation: \ref Cy_SysClk_EcoConfigure and \ref Cy_SysClk_FllConfigure.</td>
*     <td>Math library dependency is removed, the floating-point math is replaced with integer math.</td>
*   </tr>
*   <tr>
*     <td>Updated the following functions implementation: \ref Cy_SysClk_EcoEnable, \ref Cy_SysClk_EcoGetStatus, \ref Cy_SysClk_FllGetConfiguration \n
*         and \ref Cy_SysClk_DeepSleepCallback. \n
*         The \ref Cy_SysClk_DeepSleepCallback now implements all four SysPm callback modes \ref cy_en_syspm_callback_mode_t. \n
*         The actions that were done in \ref CY_SYSPM_CHECK_READY case are moved to \ref CY_SYSPM_BEFORE_TRANSITION. \n
*         So the \ref cy_stc_syspm_callback_t::skipMode must be set to 0UL.</td>
*     <td>Defect fixing.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">1.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Updated \ref Cy_SysClk_FllLocked function description</td>
*     <td>The SRSS_ver1 HW details clarification</td>
*   </tr>
*   <tr>
*     <td>Removed the following functions:
*         - Cy_SysClk_FllLostLock
*         - Cy_SysClk_WcoConfigureCsv
*         - Cy_SysClk_ClkHfConfigureCsv
*     </td>
*     <td>No hardware support for the removed functions.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.11</td>
*     <td>Updated the following functions. Now they use a semaphore when
*         try to read the status or configure the SysClk measurement counters:
*         * Cy_SysClk_StartClkMeasurementCounters()
*         * Cy_SysClk_ClkMeasurementCountersGetFreq()
*
*         Now Cy_SysClk_ClkMeasurementCountersGetFreq() returns zero value,
*         if during measurement device was in the Deep Sleep or partially
*         blocking flash operation occurred </td>
*     <td>Added arbiter mechanism for correct usage of the SysClk measurement
*         counters</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Renamed Power Management section to Low Power Callback section</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td rowspan="5">1.10</td>
*     <td>Updated FLL parameter calculation</td>
*     <td>Support low frequency sources</td>
*   </tr>
*   <tr>
*     <td>Added Cy_SysClk_PiloSetTrim() and Cy_SysclkPiloGetTrim() functions</td>
*     <td>Support PILO manual trims</td>
*   </tr>
*   <tr>
*     <td>Made Cy_SysClk_FllLostLock() function dependent on SRSS v1</td>
*     <td>Feature is not supported in SRSS v1</td>
*   </tr>
*   <tr>
*     <td>Updated Cy_SysClk_DeepSleepCallback() to save/restore both FLL and PLL settings</td>
*     <td>The function should return when the lock is established or a timeout has occurred</td>
*   </tr>
*   <tr>
*     <td>General documentation updates</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sysclk_macros           Macros
* \{
* \}
* \defgroup group_sysclk_enums           General Enumerated Types
* \{
*   \defgroup group_sysclk_returns         Function return values
* \}
* \defgroup group_sysclk_ext             External Clock Source (EXTCLK)
* \{
*   The External Clock Source (EXTCLK) is a clock source routed into SOC
*   through a GPIO pin. The EXTCLK is a source clock that can be used to
*   source one or more clock paths (Refer to \ref group_sysclk_path_src).
*   These clock paths can then source the processors and peripherals in
*   the device.
*
*   The EXTCLK relies on the presence of an external clock signal applied
*   to the GPIO pin. The pin must be configured to operate in Digital
*   High-Z drive mode with input buffer on and HSIOM connection
*   set to HSIOM_SEL_ACT_4.
*
*   \defgroup group_sysclk_ext_funcs       Functions
* \}
* \defgroup group_sysclk_eco             External Crystal Oscillator (ECO)
* \{
*   The External Crystal Oscillator (ECO) is a clock source that consists
*   of an oscillator circuit that drives an external crystal through its
*   dedicated ECO pins. The ECO is a source clock that can be used to
*   source one or more clock paths (Refer to \ref group_sysclk_path_src).
*   These clock paths can then source the processors and peripherals in
*   the device.
*
*   The ECO relies on the presence of an external crystal. The pins
*   connected to this crystal must be configured to operate in analog
*   drive mode with HSIOM connection set to GPIO control (HSIOM_SEL_GPIO).
*
*   \defgroup group_sysclk_eco_funcs       Functions
*   \defgroup group_sysclk_eco_enums     Enumerated Types
* \}
* \defgroup group_sysclk_path_src           Clock Path Source
* \{
*   Clock paths are a series of multiplexers that allow a source clock
*   to drive multiple clocking resources down the chain. These paths are
*   used for active domain clocks that are not operational during chip
*   Deep Sleep, hibernate and off modes. Illustrated below is a diagram
*   of the clock paths for the PSoC 63 series, showing the first three
*   clock paths. The source clocks for these paths are highlighted in
*   the red box.
*
*   - IMO: 8 MHz Internal Main Oscillator (Default)
*   - EXTCLK: External clock (signal brought in through dedicated pins)
*   - ECO: External Crystal Oscillator (requires external crystal on dedicated pins)
*   - ALTHF: Select on-chip signals (e.g. \ref group_ble_clk)
*   - Digital Signal (DSI): Digital signal from a UDB source
*
*   Some clock paths such as path 0 and path 1 have additional resources
*   that can be utilized to provide a higher frequency clock. For example,
*   path 0 source clock can be used as the reference clock for the FLL and
*   path 1 source clock can be used as the reference clock for the PLL.
*
*   ![](sysclk_path_source.png)
*
*   \note The PDL driver cannot configure a clock path to use Digital Signal
*   Interconnect (DSI) outputs as sources. This must be done through DSI
*   configuration tool such as PSoC Creator.
*
*   \defgroup group_sysclk_path_src_funcs     Functions
*   \defgroup group_sysclk_path_src_enums     Enumerated Types
* \}
* \defgroup group_sysclk_fll             Frequency Locked Loop (FLL)
* \{
*   The FLL is a clock generation circuit that can be used to produce a
*   higher frequency clock from a reference clock. The output clock exhibits
*   some characteristics of the reference clock such as the accuracy of the
*   source. However other attributes such as the clock phase are not preserved.
*   The FLL is similar in purpose to a (Phase locked loop) PLL but they are
*   not equivalent.
*
*   - They may have different frequency ranges.
*   - The FLL starts up (locks) faster and consumes less current than the PLL.
*   - The FLL accepts a source clock with lower frequency than PLL, such as the WCO (32 KHz).
*   - The FLL does not lock phase. The hardware consist of a counter with a
*     current-controlled oscillator (CCO). The counter counts the number of output
*     clock edges in a reference clock period and adjusts the CCO until the
*     expected ratio is achieved (locked). After initial lock, the CCO is
*     adjusted dynamically to keep the ratio within tolerance. The lock tolerance
*     is user-adjustable.
*   ![](sysclk_fll.png)
*
*   The SysClk driver supports two models for configuring the FLL. The first
*   model is to call the Cy_SysClk_FllConfigure() function, which calculates the
*   necessary parameters for the FLL at run-time. This may be necessary for dynamic
*   run-time changes to the FLL. However this method is slow as it needs to perform
*   the calculation before configuring the FLL. The other model is to call
*   Cy_SysClk_FllManualConfigure() function with pre-calculated parameter values.
*   This method is faster but requires prior knowledge of the necessary parameters.
*   Consult the device TRM for the FLL calculation equations.
*
*   \defgroup group_sysclk_fll_funcs       Functions
*   \defgroup group_sysclk_fll_structs     Data Structures
*   \defgroup group_sysclk_fll_enums       Enumerated Types
* \}
* \defgroup group_sysclk_pll             Phase Locked Loop (PLL)
* \{
*   The PLL is a clock generation circuit that can be used to produce a
*   higher frequency clock from a reference clock. The output clock exhibits
*   characteristics of the reference clock such as the accuracy of the source
*   and its phase. The PLL is similar in purpose to a (Frequency locked loop) FLL
*   but they are not equivalent.
*
*   - They may have different frequency ranges.
*   - The PLL starts up more slowly and consumes more current than the FLL.
*   - The PLL requires a higher frequency source clock than PLL.
*   ![](sysclk_pll.png)
*
*   The SysClk driver supports two models for configuring the PLL. The first
*   model is to call the Cy_SysClk_PllConfigure() function, which calculates the
*   necessary parameters for the PLL at run-time. This may be necessary for dynamic
*   run-time changes to the PLL. However this method is slow as it needs to perform
*   the calculation before configuring the PLL. The other model is to call
*   Cy_SysClk_PllManualConfigure() function with pre-calculated parameter values.
*   This method is faster but requires prior knowledge of the necessary parameters.
*   Consult the device TRM for the PLL calculation equations.
*
*   \defgroup group_sysclk_pll_funcs       Functions
*   \defgroup group_sysclk_pll_structs     Data Structures
* \}
* \defgroup group_sysclk_ilo             Internal Low-Speed Oscillator (ILO)
* \{
*   The ILO operates with no external components and outputs a stable clock at
*   32.768 kHz nominal. The ILO is relatively low power and low accuracy. It is
*   available in all power modes and can be used as a source for the Backup domain clock.
*   ![](sysclk_backup.png)
*
*   To ensure the ILO remains active in Hibernate mode, and across power-on-reset
*   (POR) or brown out detect (BOD), firmware must call Cy_SysClk_IloHibernateOn().
*
*   Additionally, the ILO clock can be trimmed to +/- 1.5% of nominal frequency using
*   a higher precision clock source. Use the \ref group_sysclk_calclk API to measure
*   the current ILO frequency before trimming.
*
*   \note The ILO is always the source clock for the \ref group_wdt. Therefore:
*   - The WDT must be unlocked when making an ILO function call in the PDL
*   - It is recommended to always have the ILO enabled
*
*   \defgroup group_sysclk_ilo_funcs       Functions
* \}
* \defgroup group_sysclk_pilo            Precision Internal Low-Speed Oscillator (PILO)
* \{
*   PILO provides a higher accuracy 32.768 kHz clock than the \ref group_sysclk_ilo "ILO".
*   When periodically calibrated using a high-accuracy clock such as the
*   \ref group_sysclk_eco "ECO", the PILO can achieve 250 ppm accuracy of nominal frequency.
*   The PILO is capable of operating in device Active, Sleep and Deep-Sleep power modes.
*   It is not available in Hibernate mode.
*
*   The PILO can be used as a source for the \ref group_sysclk_clk_lf. However,
*   because PILO is disabled in Hibernate mode, RTC timers cannot operate in this mode
*   when clocked using the PILO. Instead, either the \ref group_sysclk_ilo "ILO" or
*   \ref group_sysclk_wco "WCO" should be used when hibernate operation is required.
*
*   ![](sysclk_backup.png)
*
*   Periodic calibration to a high-accuracy clock (such as ECO) is required to
*   maintain accuracy. The application should use the functions described in the
*   \ref group_sysclk_calclk API to measure the current PILO frequency before trimming.
*
*   \defgroup group_sysclk_pilo_funcs      Functions
* \}
* \defgroup group_sysclk_calclk          Clock Measurement
* \{
*   These functions measure the frequency of a specified clock relative to a
*   reference clock. They are typically called in the following order:
*
*   1. Specify the measured clock, the count, and the reference clock
*   2. Start the counters
*   3. Wait for the measurement counter to finish counting
*   4. Retrieve the measured frequency
*
*   \note These functions may also be used as part of a clock trimming
*   process. Refer to the \ref group_sysclk_trim "Clock Trim" API.
*
*   \defgroup group_sysclk_calclk_funcs    Functions
*   \defgroup group_sysclk_calclk_enums    Enumerated Types
*   \defgroup group_sysclk_calclk_structs  Data Structures
* \}
* \defgroup group_sysclk_trim            Clock Trim (ILO, PILO)
* \{
*   These functions perform a single trim operation on the ILO or PILO. Each
*   function's parameter is the actual frequency of the clock. To measure the
*   frequency, use the functions described in the \ref group_sysclk_calclk API.
*
*   To trim the clock as close as possible to the target frequency, multiple
*   calls to the trim function may be needed. A typical usage example is to:
*   1. Call the clock measurement functions to get the actual frequency of the clock
*   2. Call the trim function, passing in the measured frequency
*   3. Repeat the above until the trim function reports that the clock is trimmed to within limits.
*
*   \defgroup group_sysclk_trim_funcs      Functions
* \}
* \defgroup group_sysclk_pm              Low Power Callback
* \{
*   Entering and exiting low power modes require compatible clock configurations
*   to be set before entering low power and restored upon wake-up and exit. The
*   SysClk driver provides a Cy_SysClk_DeepSleepCallback() function to support
*   Deep Sleep mode entry.
*
*   This function can be called either by itself before initiating low-power mode
*   entry or it can be used in conjunction with the SysPm driver as a registered
*   callback. To do so, register this function as a callback before calling
*   Cy_SysPm_DeepSleep(). Specify \ref CY_SYSPM_DEEPSLEEP as the callback type,
*   and call Cy_SysPm_RegisterCallback().
*
*   \note If the FLL or PLL source is the ECO, this function must be called.
*
*   \defgroup group_sysclk_pm_funcs        Functions
* \}
* \defgroup group_sysclk_wco             Watch Crystal Oscillator (WCO)
* \{
*   The WCO is a highly accurate 32.768 kHz clock source capable of operating
*   in all power modes (excluding the Off mode). It is the primary clock source for
*   the backup domain clock, which is used by the real-time clock (RTC). The
*   WCO can also be used as a source for the low-frequency clock to support other
*   low power mode peripherals.
*
*   ![](sysclk_backup.png)
*
*   The WCO requires the configuration of the dedicated WCO pins (SRSS_WCO_IN_PIN,
*   SRSS_WCO_OUT_PIN). These must be configured as Analog Hi-Z drive modes and the
*   HSIOM selection set to GPIO. The WCO can also be used in bypass mode, where
*   an external 32.768 kHz square wave is brought in directly through the
*   SRSS_WCO_OUT_PIN pin.
*
*   \defgroup group_sysclk_wco_funcs       Functions
*   \defgroup group_sysclk_wco_enums       Enumerated Types
* \}
* \defgroup group_sysclk_clk_hf          High-Frequency Clocks
* \{
*   Multiple high frequency clocks (CLK_HF) are available in the device. For example,
*   PSoC 63 series has five high-frequency root clocks. Each CLK_HF has a particular
*   connection and chip-specific destination on the device.
*
*   |Name     |Description                                             |
*   |:--------|:-------------------------------------------------------|
*   |CLK_HF[0]| Root clock for CPUs, PERI, and AHB infrastructure      |
*   |CLK_HF[1]| Root clock for the PDM/PCM and I2S audio subsystem     |
*   |CLK_HF[2]| Root clock for the Serial Memory Interface subsystem   |
*   |CLK_HF[3]| Root clock for USB communications                      |
*   |CLK_HF[4]| Clock output on clk_ext pin (when used as an output)   |
*
*   ![](sysclk_hf.png)
*
*   Note this is a particular example. The actual tree may vary depending on the device series.
*   Consult the Technical Reference Manual for your device for details.
*
*   High frequency clocks are sourced by path clocks, which should be configured
*   first. An exception to this rule is CLK_HF[0], which cannot be disabled.
*   This divided clock drives the core processors and the peripherals in the system.
*   In order to update its clock source, CLK_HF[0] source must be selected without
*   disabling the clock.
*
*   ![](sysclk_hf_dist.png)
*
*   \defgroup group_sysclk_clk_hf_funcs    Functions
*   \defgroup group_sysclk_clk_hf_enums    Enumerated Types
* \}
* \defgroup group_sysclk_clk_fast        Fast Clock
* \{
*   The fast clock drives the "fast" processor (e.g. Cortex-M4 processor in PSoC 6).
*   This clock is sourced by CLK_HF[0] (\ref group_sysclk_clk_hf "HF Clocks").
*   A divider value of 1~256 can be used to further divide the CLK_HF[0] to a
*   desired clock speed for the processor.
*
*   ![](sysclk_fast.png)
*
*   \defgroup group_sysclk_clk_fast_funcs  Functions
* \}
* \defgroup group_sysclk_clk_peri        Peripheral Clock
* \{
*   The peripheral clock is a divided clock of CLK_HF0 (\ref group_sysclk_clk_hf "HF Clocks").
*   It is the source clock for the \ref group_sysclk_clk_slow, and most active domain
*   peripheral clocks (\ref group_sysclk_clk_peripheral). A divider value of 1~256
*   can be used to further divide the CLK_HF[0] to a desired clock speed for the peripherals.
*
*   ![](sysclk_peri.png)
*
*   \defgroup group_sysclk_clk_peri_funcs  Functions
* \}
* \defgroup group_sysclk_clk_peripheral  Peripherals Clock Dividers
* \{
*   There are multiple peripheral clock dividers that, in effect, create
*   multiple separate peripheral clocks. The available dividers vary per device
*   series. As an example, for the PSoC 63 series there are 29 dividers:
*
*   - eight 8-bit dividers
*   - sixteen 16-bit dividers
*   - four fractional 16.5-bit dividers (16 integer bits, 5 fractional bits)
*   - one fractional 24.5-bit divider (24 integer bits, 5 fractional bits)
*
*
*   The 8-bit and 16-bit dividers are integer dividers. A divider value of 1
*   means the output frequency matches the input frequency (that is, there is
*   no change). Otherwise the frequency is divided by the value of the divider.
*   For example, if the input frequency is 50 MHz, and the divider is value 10,
*   the output frequency is 5 MHz.
*
*   The five fractional bits supports further precision in 1/32nd increments. For
*   example, a divider with an integer value of 3 and a fractional value of
*   4 (4/32) results in a divider of 3.125. Fractional dividers are useful when
*   a high-precision clock is required, for example, for a UART/SPI serial
*   interface.
*
*   ![](sysclk_peri_divs.png)
*
*   Each peripheral can connect to any one of the programmable dividers. A
*   particular peripheral clock divider can drive multiple peripherals.
*
*   The SysClk driver also supports phase aligning two peripheral clock dividers using
*   Cy_SysClk_PeriphEnablePhaseAlignDivider(). Alignment works for both integer
*   and fractional dividers. The divider to which a second divider is aligned
*   must already be enabled.
*
*   \defgroup group_sysclk_clk_peripheral_funcs Functions
*   \defgroup group_sysclk_clk_peripheral_enums Enumerated Types
* \}
* \defgroup group_sysclk_clk_slow        Slow Clock
* \{
*   The slow clock is the source clock for the "slow" processor (e.g. Cortex-M0+ in PSoC 6).
*   This clock is a divided version of the \ref group_sysclk_clk_peri, which in turn is
*   a divided version of CLK_HF[0] (\ref group_sysclk_clk_hf "HF Clocks"). A divider
*   value of 1~256 can be used to further divide the Peri clock to a desired clock speed
*   for the processor.
*
*   ![](sysclk_slow.png)
*
*   \defgroup group_sysclk_clk_slow_funcs  Functions
* \}
 * \defgroup group_sysclk_alt_hf Alternative High-Frequency Clock
* \{
*   In  the BLE-enabled PSoC6 devices, the \ref group_ble_clk clock is
*   connected to the system Alternative High-Frequency Clock input.
*
*   \defgroup group_sysclk_alt_hf_funcs    Functions
* \}
* \defgroup group_sysclk_clk_lf          Low-Frequency Clock
* \{
*   The low-frequency clock is the source clock for the \ref group_mcwdt
*   and can be the source clock for \ref group_sysclk_clk_bak, which drives the
*   \ref group_rtc.
*
*   The low-frequency clock has three possible source clocks:
*   \ref group_sysclk_ilo "ILO", \ref group_sysclk_pilo "PILO", and
*   \ref group_sysclk_wco "WCO".
*
*   ![](sysclk_lf.png)
*
*   \defgroup group_sysclk_clk_lf_funcs    Functions
*   \defgroup group_sysclk_clk_lf_enums    Enumerated Types
* \}
* \defgroup group_sysclk_clk_timer       Timer Clock
* \{
*   The timer clock can be a source for the alternative clock driving
*   the \ref group_arm_system_timer. It can also be used as a reference clock
*   for a counter in the \ref group_energy_profiler "Energy Profiler".
*
*   The timer clock is a divided clock of either the IMO or CLK_HF[0]
*   (\ref group_sysclk_clk_hf "HF Clocks").
*
*   \defgroup group_sysclk_clk_timer_funcs Functions
*   \defgroup group_sysclk_clk_timer_enums Enumerated Types
* \}
* \defgroup group_sysclk_clk_pump        Pump Clock
* \{
*   The pump clock is a clock source used to provide analog precision in low voltage
*   applications. Depending on the usage scenario, it may be required to drive the
*   internal voltage pump for the Continuous Time Block mini (CTBm) in the analog
*   subsystem. The pump clock is a divided clock of one of the clock paths
*   (\ref group_sysclk_path_src).
*
*   \defgroup group_sysclk_clk_pump_funcs  Functions
*   \defgroup group_sysclk_clk_pump_enums  Enumerated Types
* \}
* \defgroup group_sysclk_clk_bak         Backup Domain Clock
* \{
*   The backup domain clock drives the \ref group_rtc.
*   This clock has two possible source clocks: \ref group_sysclk_wco "WCO"
*   or the \ref group_sysclk_clk_lf. In turn the low frequency clock is sourced by
*   \ref group_sysclk_ilo "ILO", \ref group_sysclk_pilo "PILO", or
*   \ref group_sysclk_wco "WCO". Typically the ILO is not suitable as an RTC source,
*   because of its low accuracy. However the ILO does operate in hibernate mode and
*   may be used as an alternative to the WCO with a tradeoff in precision.
*
*   \defgroup group_sysclk_clk_bak_funcs   Functions
*   \defgroup group_sysclk_clk_bak_enums   Enumerated Types
* \}
* \defgroup group_sysclk_mf         Medium Frequency Domain Clock
* \{
*   The Medium Frequency Domain Clock is present only in SRSS_ver1_3.
*   Consists of MFO - the Medium Frequency Oscillator,
*   and CLK_MF - the Medium Frequency Clock divider.
*   This clock chain is designed to source the LCD block
*   in Deep Sleep mode, see \ref cy_en_seglcd_lsclk_t.
*
*   \defgroup group_sysclk_mf_funcs   Functions
*   \defgroup group_sysclk_clk_mf_enums    Enumerated Types
* \}
* \defgroup group_sysclk_iho         Internal High Frequency(IHO) Clock
* \{
*   The IHO Clock is Internal High-speed Oscillator, which is present in CAT1B(48MHz)
*   and CAT1D(50MHz) devices.
*
*   \defgroup group_sysclk_iho_funcs   Functions
*   \defgroup group_sysclk_clk_iho_enums    Enumerated Types
* \}
* \defgroup group_sysclk_imo         Internal Main Oscillator(IMO) Clock
* \{
*   The IMO Clock is Internal Main Oscillator, which is present in CAT1A/CAT1B/CAT1C and
*   CAT1D devices, where as it is it is 8MHz in CAT1A/CAT1B/CAT1C, and CAT1D supports
*   two instances of IMO i.e. 2MHz frequency (deep sleep capable) and separate
*   instance with 4Mhz for LPPASS.
*
*   \defgroup group_sysclk_imo_funcs   Functions
*   \defgroup group_sysclk_clk_imo_enums    Enumerated Types
* \}
* \defgroup group_sysclk_clk_mem         Mem Clock
* \{
*   Clock for the Memories

*   \defgroup group_sysclk_clk_mem_funcs   Functions
* \}

*/

#if !defined (CY_SYSCLK_H)
#define CY_SYSCLK_H

#include "cy_device.h"

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
#include <stdbool.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined(CY_DEVICE_SECURE)
    #include "cy_pra.h"
#endif /* defined(CY_DEVICE_SECURE) */


#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/**
* \addtogroup group_sysclk_macros
* \{
*/
/** Driver major version */
#define  CY_SYSCLK_DRV_VERSION_MAJOR   3
/** Driver minor version */
#define  CY_SYSCLK_DRV_VERSION_MINOR   50
/** Sysclk driver identifier */
#define CY_SYSCLK_ID   CY_PDL_DRV_ID(0x12U)

/** ILO clock frequency */
#define CY_SYSCLK_ILO_FREQ  (32768UL)   /* Hz */
/** WCO clock frequency */
#define CY_SYSCLK_WCO_FREQ  (32768UL)   /* Hz */
/** PILO clock frequency */
#define CY_SYSCLK_PILO_FREQ (32768UL)   /* Hz */

/** IMO clock frequency */
#define CY_SYSCLK_IMO_FREQ  (8000000UL) /* Hz */

/** MFO clock frequency */
#define CY_SYSCLK_MFO_FREQ  (2000000UL) /* Hz */

/** CY_SYSCLK_PILO_TRIM_STEP is the default PILO TRIM Step value */
#define CY_SYSCLK_PILO_TRIM_STEP  (5UL) /* Default PILO TRIM Step size */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS)
/**
* \note
* This macro is available for CAT1B devices.
**/
/** IHO clock frequency */
#define CY_SYSCLK_IHO_FREQ  (48000000UL) /* Hz */

#elif defined (CY_IP_MXS22SRSS)
/**
* \note
* This macro is available for CAT1D devices.
**/
/** IHO clock frequency */
#define CY_SYSCLK_IHO_FREQ  (50000000UL) /* Hz */
#endif /* CY_IP_MXS40SSRSS,CY_IP_MXS28SRSS*/


#if defined (CY_IP_MXS40SRSS)
/**
* \note
* This macro is available for CAT1A devices.
**/
/** ECO clock frequency */
#define CY_SYSCLK_ECO_FREQ  (4000000UL) /* Hz */
#endif /* CY_IP_MXS40SRSS */


#if defined (CY_IP_MXS40SSRSS)|| defined (CY_IP_MXS22SRSS)
/** FLL BYPASS configure Delay , As per SAS
* "When changing BYPASS_SEL, do not turn off the reference clock
* or CCO clock for ten cycles (whichever is slower)"
* Slower if IMO, so delay = (10 * 1/(IMO freq in Mhz))  = 1.25 micro seconds,
* approximated to 2 micro second
 **/
#define CY_SYSCLK_BYPASS_CONFIGURE_DELAY  (2UL) /* micro seconds */

/** FLL Disable Timeout value
**/
#define CY_SYSCLK_FLL_DISABLE_TIMEOUT     (100UL) /* micro seconds */

#else

/** FLL BYPASS configure Delay , As per SAS
* "When changing BYPASS_SEL, do not turn off the reference clock
* or CCO clock for seven cycles (whichever is slower)"
* Slower if IMO, so delay = (7 * 1/(IMO freq in Mhz))  = 0.875 micro seconds,
* approximated to 1 micro second
**/
#define CY_SYSCLK_BYPASS_CONFIGURE_DELAY  (1UL) /* micro seconds */

/** FLL Disable Timeout value
**/
#define CY_SYSCLK_FLL_DISABLE_TIMEOUT     (100UL) /* micro seconds */

#endif /* defined (CY_IP_MXS40SSRSS)|| defined (CY_IP_MXS22SRSS) */


/** \} group_sysclk_macros */


/**
* \addtogroup group_sysclk_returns
* \{
*/
/** Defines general-purpose function return values */
typedef enum
{
    CY_SYSCLK_SUCCESS           = 0x00UL, /**< Command completed with no errors */
    CY_SYSCLK_BAD_PARAM         = (CY_SYSCLK_ID | CY_PDL_STATUS_ERROR | 0x01UL), /**< Invalid function input parameter */
    CY_SYSCLK_TIMEOUT           = (CY_SYSCLK_ID | CY_PDL_STATUS_ERROR | 0x02UL), /**< Timeout occurred */
    CY_SYSCLK_INVALID_STATE     = (CY_SYSCLK_ID | CY_PDL_STATUS_ERROR | 0x03UL), /**< Clock is in an invalid state */
    CY_SYSCLK_UNSUPPORTED_STATE = (CY_SYSCLK_ID | CY_PDL_STATUS_ERROR | 0x04UL) /**< Feature Unsupported */
} cy_en_sysclk_status_t;
/** \} group_sysclk_returns */


/* ========================================================================== */
/* ===========================    EXT SECTION    ============================ */
/* ========================================================================== */

/** \cond INTERNAL */
#if ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE)))
    /* Internal storage for external clock frequency user setting */
    extern uint32_t cySysClkExtFreq;
#endif /* ((CY_CPU_CORTEX_M4) && (defined(CY_DEVICE_SECURE))) */
/** \endcond */

/**
* \addtogroup group_sysclk_ext_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ExtClkSetFrequency
****************************************************************************//**
*
* Sets the signal frequency of the External Clock Source (EXTCLK) into the
* internal storage to be used in \ref Cy_SysClk_ClkHfGetFrequency.
*
* \param freq The frequency of the External Clock Source.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ExtClkSetFrequency
*
*******************************************************************************/
void Cy_SysClk_ExtClkSetFrequency(uint32_t freq);


/*******************************************************************************
* Function Name: Cy_SysClk_ExtClkGetFrequency
****************************************************************************//**
*
* Returns the frequency of the External Clock Source (EXTCLK) from the
* internal storage.
*
* \return The frequency of the External Clock Source.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ExtClkSetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_ExtClkGetFrequency(void);
/** \} group_sysclk_ext_funcs */

/* ========================================================================== */
/* ===========================    ECO SECTION    ============================ */
/* ========================================================================== */

/**
* \addtogroup group_sysclk_macros
* \{
*/

/**
* \defgroup group_sysclk_ecostatus ECO status
* \{
* Constants used for expressing ECO status.
*/
#define CY_SYSCLK_ECOSTAT_AMPLITUDE  0UL /**< \brief ECO does not have sufficient amplitude */
#define CY_SYSCLK_ECOSTAT_INACCURATE 1UL /**< \brief ECO may not be meeting accuracy and duty cycle specs */
#define CY_SYSCLK_ECOSTAT_STABLE     2UL /**< \brief ECO has fully stabilized */

#if defined (CY_IP_MXS28SRSS)
/**
* \note
* This macro is available for CAT1B devices.
**/
#define CY_SYSCLK_ECOSTAT_BLE_DISABLED 0UL /**< \brief ECO for BLE is disabled */
/**
* \note
* This macro is available for CAT1B devices.
**/
#define CY_SYSCLK_ECOSTAT_BLE_ENABLED  1UL /**< \brief ECO for BLE is enabled */
#endif /* CY_IP_MXS28SRSS */

/** \} group_sysclk_ecostatus */

# if (defined (CY_DEVICE_SECURE))
/**
* \note
* This structure is available for CAT1A devices.
**/
/** PRA structure for Cy_SysClk_EcoConfigure function parameters */
typedef struct
{
    uint32_t praClkEcofreq;                           /**< freq */
    uint32_t praCsum;                           /**< cSum */
    uint32_t praEsr;                             /**< esr */
    uint32_t praDriveLevel;                     /**< drivelevel */
} cy_stc_pra_clk_eco_configure_t;
#endif /* (defined (CY_DEVICE_SECURE)) */

/** \} group_sysclk_macros */

#if defined (CY_IP_MXS40SRSS)  || defined (CY_IP_MXS22SRSS)
/** \cond */
/**
* \note
* This macro is available for CAT1A and CAT1D devices.
**/
#define SRSS_CLK_ECO_STATUS_Msk (SRSS_CLK_ECO_STATUS_ECO_OK_Msk | SRSS_CLK_ECO_STATUS_ECO_READY_Msk)
/** \endcond */
#endif /* defined (CY_IP_MXS40SRSS)  || defined (CY_IP_MXS22SRSS) */

#if defined (CY_IP_MXS28SRSS)
/** \cond */
/**
* \note
* It is available for CAT1B devices.
**/
#define SRSS_CLK_ECO_STATUS_Msk (SRSS_CLK_ECO_STATUS_ECO_CORE_READY_Msk | SRSS_CLK_ECO_STATUS_ECO_CORE_AMP_OK_Msk)

/** \endcond */
#endif /* CY_IP_MXS28SRSS */



#if defined (CY_IP_MXS28SRSS)
/**
* \addtogroup group_sysclk_eco_enums
* \{
*/
/**
*   ECO enable options for BLE
*/
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_SYSCLK_ECO_BLESS_CONTROL0    =  0U, /**< 0, 1: hardware controlled by BLESS. */
    CY_SYSCLK_ECO_BLESS_CONTROL1    =  1U, /**< 0, 1: hardware controlled by BLESS. */
    CY_SYSCLK_ECO_FORCE_ENABLE      =  2U, /**< Force ECO enabled for use by BLE */
    CY_SYSCLK_ECO_FORCE_DISABLE     =  3U, /**< Force ECO disabled for use by BLE */
} cy_en_eco_for_ble_t;
/** \} group_sysclk_eco_enums */
#endif /* CY_IP_MXS28SRSS */

/**
* \addtogroup group_sysclk_eco_funcs
* \{
*/
 #if defined (CY_IP_MXS40SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_EcoConfigure
****************************************************************************//**
*
* Configures the external crystal oscillator (ECO) trim bits based on crystal
* characteristics. This function should be called only when the ECO is disabled.
*
* \param freq Operating frequency of the crystal in Hz.
* Valid range: 16000000...35000000 (16..35 MHz).
*
* \param cSum The summary capacitance of
* C0 (the crystal itself shunt capacitance) and
* Cload (the parallel load capacitance), in pF.
* So cSum = C0 + Cload.
* Valid range: 1...100.
* \note
* For CAT1B Devices:
* cSum stands for crystal load capacitance in pF.
*
* \param esr Effective series resistance of the crystal in Ohms.
* Valid range: 1...1000.
*
* \param driveLevel Crystal drive level in uW.
* Valid range: 1...2000.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ECO configuration completed successfully \n
* CY_SYSCLK_BAD_PARAM - One or more invalid parameters \n
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* \note Behavior of this API is IP dependent. \n
* On CAT1A device: \n
*
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
* The following calculations are implemented in the 32-bit integer math:
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_EcoEnable call.
*
* \verbatim
*   freqKhz = freq / 1000
*   maxAmpl = sqrt(drivelevel / 2 / esr) / 3.14 / freqKhz / cSum
*   ampSect = INT(5 * 4 * 3.14^2 * freqKhz^2 * cSum^2 * 4 * esr / 1000000000 / 1000000 / 9)
*   As a result of the above calculations, max amplitude must be >= 0.65V, and the
*   number of amplifier sections must be <= 3, otherwise this function returns with
*   a parameter error.
*
*   atrim = 15
*   agc_en = 1
*   wdtrim = 7
*   gtrim = ampSect > 1 ? ampSect : ampSect == 1 ? 0 : 1
*   rtrim = 0
*   ftrim = 3
* \endverbatim
*
* \note
* On CAT1C Device: \n
*
* \verbatim

*   No TRIM registers configuration required for CAT1B devices, For legacy API is emptied
*   The following calculations are implemented, generally in floating point:
*   freqMHz = freq / 1000000
*   max amplitude Vpp = 1000 * sqrt(drivelevel / 2 / esr) / 3.14 / freqMHz / cLoad
*   gm_min mA/V = 5 * 4 * 3.14 * 3.14 * freqMhz^2 * cLoad^2 * 4 * esr / 1000000000
*   Number of amplifier sections = INT(gm_min / 4.5)
*
*   As a result of the above calculations, max amplitude must be >= 0.5, and the
*   number of amplifier sections must be <= 3, otherwise this function returns with
*   a parameter error.
*
*   atrim = if (max amplitude < 0.5) then error
*           else 2 * the following:
*                    max amplitude < 0.6: 0
*                    max amplitude < 0.7: 1
*                    max amplitude < 0.8: 2
*                    max amplitude < 0.9: 3
*                    max amplitude < 1.15: 5
*                    max amplitude < 1.275: 6
*                    max amplitude >= 1.275: 7
*   wdtrim = if (max amplitude < 0.5) then error
*            else 2 * the following:
*                     max amplitude < 1.2: INT(5 * max amplitude) - 2
*                     max amplitude >= 1.2: 3
*   gtrim = if (number of amplifier sections > 3) then error
*           else the following:
*                number of amplifier sections > 1: number of amplifier sections
*                number of amplifier sections = 1: 0
*                number of amplifier sections < 1: 1
*   rtrim = if (gtrim = error) then error
*           else the following:
*                freqMHz > 26.8: 0
*                freqMHz > 23.33: 1
*                freqMHz > 16.5: 2
*                freqMHz <= 16.5: 3
*   ftrim = if (atrim = error) then error
*           else INT(atrim / 2)
* \endverbatim
*
* \note
* This API is available for CAT1A,CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_EcoConfigure
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_EcoConfigure(uint32_t freq, uint32_t cSum, uint32_t esr, uint32_t driveLevel);

/*******************************************************************************
* Function Name: Cy_SysClk_EcoEnable
****************************************************************************//**
*
* Enables the external crystal oscillator (ECO). This function should be called
* after \ref Cy_SysClk_EcoConfigure.
*
* \param timeoutus Amount of time in microseconds to wait for the ECO to stabilize.
* To avoid waiting for stabilization, set this parameter to 0.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ECO locked \n
* CY_SYSCLK_TIMEOUT - ECO timed out and did not lock \n
* CY_SYSCLK_INVALID_STATE - ECO already enabled \n
* CY_SYSCLK_UNSUPPORTED_STATE - ECO is not present
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_EcoEnable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_EcoEnable(uint32_t timeoutus);

/*******************************************************************************
* Function Name: Cy_SysClk_EcoGetFrequency
****************************************************************************//**
*
* Returns the frequency of the external crystal oscillator (ECO).
*
* \return The frequency of the ECO.
*
* \note If the ECO is not enabled or stable - a zero is returned.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_EcoEnable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_EcoGetFrequency(void);


/*******************************************************************************
* Function Name: Cy_SysClk_EcoDisable
****************************************************************************//**
*
* Disables the external crystal oscillator (ECO). This function should not be
* called if the ECO is sourcing clkHf[0].
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_EcoDisable
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_EcoDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_EcoGetStatus
****************************************************************************//**
*
* Reports the current status of the external crystal oscillator (ECO).
*
* \return
* CY_SYSCLK_ECOSTAT_AMPLITUDE = ECO does not have sufficient amplitude \n
* CY_SYSCLK_ECOSTAT_INACCURATE = ECO has sufficient amplitude but may not be meeting accuracy and duty cycle specifications \n
* CY_SYSCLK_ECOSTAT_STABLE = ECO has fully stabilized
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_EcoGetStatus
*
*******************************************************************************/
uint32_t Cy_SysClk_EcoGetStatus(void);
#endif /* defined (CY_IP_MXS40SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS) */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_EcoPrescaleConfigure
****************************************************************************//**
*
* Configures the external crystal oscillator (ECO) using ECO Prescaler
* Configuration Register and derives clk_eco_prescaler
*
* \param enable ECO Prescaler enable/disable.
*
* \param int_div 10-bit integer value.
*
* \param frac_div 8-bit fraction value.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ECO configuration completed successfully \n
* CY_SYSCLK_BAD_PARAM - One or more invalid parameters \n
* CY_SYSCLK_INVALID_STATE - ECO already enabled \n
* CY_SYSCLK_UNSUPPORTED_STATE - ECO is not present
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_EcoPrescaleConfigure(uint32_t enable, uint32_t int_div, uint32_t frac_div);

/*******************************************************************************
* Function Name: Cy_SysClk_EcoPrescaleIsEnabled
****************************************************************************//**
*
* Reports whether or not ECO Prescale is enabled.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_EcoPrescaleIsEnabled(void);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS) */

#if defined (CY_IP_MXS28SRSS)
/*******************************************************************************
* Function Name: Cy_SysClk_EcoBleEnable
****************************************************************************//**
*
* Enables the external crystal oscillator (ECO) for BlueTooth Usage. This function should be called
* after \ref Cy_SysClk_EcoConfigure.
*
* \param control To be selected from \ref cy_en_eco_for_ble_t
*
* \param timeoutus timeoutus
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ECO locked \n
* CY_SYSCLK_TIMEOUT - ECO timed out and did not lock \n
* CY_SYSCLK_INVALID_STATE - ECO already enabled \n
* CY_SYSCLK_UNSUPPORTED_STATE - ECO is not present
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_EcoBleControl(cy_en_eco_for_ble_t control, uint32_t timeoutus);

/*******************************************************************************
* Function Name: Cy_SysClk_EcoBleGetStatus
****************************************************************************//**
*
* Reports the current status w.r.to BLE of the external crystal oscillator (ECO).
*
* \return
* CY_SYSCLK_ECOSTAT_BLE_ENABLED = ECO for BLE is enabled \n
* CY_SYSCLK_ECOSTAT_BLE_DISABLED = ECO for BLE is not enabled
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_EcoBleGetStatus(void);
#endif /* defined (CY_IP_MXS28SRSS) */

/** \} group_sysclk_eco_funcs */


/* ========================================================================== */
/* ====================    INPUT MULTIPLEXER SECTION    ===================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_path_src_enums
* \{
*/
/**
*   Input multiplexer clock sources
*/


typedef enum
{
#if defined (CY_IP_MXS22SRSS)
    CY_SYSCLK_CLKPATH_IN_IHO    =     0U, /**< Select the IMO as the output of the path mux */
#else
    CY_SYSCLK_CLKPATH_IN_IMO    =     0U, /**< Select the IMO as the output of the path mux */
#endif /* defined (CY_IP_MXS22SRSS) */
    CY_SYSCLK_CLKPATH_IN_EXT    =     1U, /**< Select the EXT as the output of the path mux */
    CY_SYSCLK_CLKPATH_IN_ECO    =     2U, /**< Select the ECO as the output of the path mux */
    CY_SYSCLK_CLKPATH_IN_ALTHF  =     3U, /**< Select the ALTHF as the output of the path mux */

    CY_SYSCLK_CLKPATH_IN_DSIMUX =     4U, /**< Select the DSI MUX output as the output of the path mux */

#if defined (CY_IP_MXS22SRSS)
    CY_SYSCLK_CLKPATH_IN_IMO    =     5U, /**< Select the IMO as the output of the path mux */
#else
    CY_SYSCLK_CLKPATH_IN_LPECO  =     5U, /**< Select the LPECO as the output of the path mux */
    CY_SYSCLK_CLKPATH_IN_IHO    =     6U, /**< Select the IHO as the output of the path mux */
#endif /* defined (CY_IP_MXS22SRSS) */
    CY_SYSCLK_CLKPATH_IN_DSI    = 0x100U, /**< Select a DSI signal (0 - 15) as the output of the DSI mux and path mux.
                                           *   Make sure the DSI clock sources are available on used device.
                                           */
    CY_SYSCLK_CLKPATH_IN_ILO    = 0x110U, /**< Select the ILO (16) as the output of the DSI mux and path mux */

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)
    CY_SYSCLK_CLKPATH_IN_ILO0   = CY_SYSCLK_CLKPATH_IN_ILO,
#endif /* defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3) */

    CY_SYSCLK_CLKPATH_IN_WCO    = 0x111U, /**< Select the WCO (17) as the output of the DSI mux and path mux */
    CY_SYSCLK_CLKPATH_IN_ALTLF  = 0x112U, /**< Select the ALTLF (18) as the output of the DSI mux and path mux.
                                           *   Make sure the ALTLF clock sources in available on used device.
                                           */
    CY_SYSCLK_CLKPATH_IN_PILO   = 0x113U, /**< Select the PILO (19) as the output of the DSI mux and path mux.
                                           *   Make sure the PILO clock sources in available on used device.
                                           */
    CY_SYSCLK_CLKPATH_IN_ILO1   = 0x114U  /**< Select the ILO1(20) as the output of the path mux */
} cy_en_clkpath_in_sources_t;


#if (defined(CY_DEVICE_SECURE))
/**
* \note
* This structure is available for CAT1A devices.
**/
/** PRA structure for Cy_SysClk_ClkPathSetSource function parameters */
typedef struct
{
    uint32_t                          clk_path;      /**< clkpath  */
    cy_en_clkpath_in_sources_t         source;        /**< Source */
} cy_stc_pra_clkpathsetsource_t;
#endif /* (defined(CY_DEVICE_SECURE)) */

/** \} group_sysclk_path_src_enums */

/**
* \addtogroup group_sysclk_path_src_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ClkPathSetSource
****************************************************************************//**
*
* Configures the source for the specified clock path.
*
* \param clkPath Selects which clock path to configure; 0 is the first clock
* path, which is the FLL.
*
* \param source \ref cy_en_clkpath_in_sources_t
*
* \return \ref cy_en_sysclk_status_t
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* If calling this function changes an FLL or PLL input frequency, disable the FLL
* or PLL before calling this function. After calling this function, call the FLL
* or PLL configure function, for example \ref Cy_SysClk_FllConfigure().
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* it affects the CLK_HF0 frequency and the frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* it affects the CLK_HF0 frequency and the frequency is decreasing.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPathSetSource
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \note  It takes four cycles of the originally selected clock to switch away
* from it.  Do not disable the original clock during this time.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkPathSetSource(uint32_t clkPath, cy_en_clkpath_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPathGetSource
****************************************************************************//**
*
* Reports which source is selected for the path mux.
*
* \param clkPath Selects which clock path to report; 0 is the first clock path,
* which is the FLL.
*
* \return \ref cy_en_clkpath_in_sources_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPathGetSource
*
*******************************************************************************/
cy_en_clkpath_in_sources_t Cy_SysClk_ClkPathGetSource(uint32_t clkPath);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPathMuxGetFrequency
****************************************************************************//**
*
* Returns the output frequency of the clock path mux.
*
* \return The output frequency of the path mux.
*
* \note If the return value equals zero, that means either:
* - the selected path mux source signal frequency is unknown (e.g. dsi_out, etc.) or
* - the selected path mux source is not configured/enabled/stable (e.g. ECO, EXTCLK, etc.).
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPathSetSource
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkPathMuxGetFrequency(uint32_t clkPath);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPathGetFrequency
****************************************************************************//**
*
* Returns the output frequency of the clock path mux.
*
* \return The output frequency of the path mux.
*
* \note If the return value equals zero, that means either:
* - the selected path mux source signal frequency is unknown (e.g. dsi_out, etc.) or
* - the selected path mux source is not configured/enabled/stable (e.g. ECO, EXTCLK, etc.).
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllEnable
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkPathGetFrequency(uint32_t clkPath);
/** \} group_sysclk_path_src_funcs */


/* ========================================================================== */
/* ===========================    FLL SECTION    ============================ */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_fll_enums
* \{
*/
/** FLL and PLL output mode.
* See registers CLK_FLL_CONFIG3 and CLK_PLL_CONFIG0, bits BYPASS_SEL.
*/
typedef enum
{
    CY_SYSCLK_FLLPLL_OUTPUT_AUTO   = 0U, /**< Output FLL/PLL input source when not locked, and FLL/PLL output when locked */
    CY_SYSCLK_FLLPLL_OUTPUT_AUTO1  = 1U, /**< Same as AUTO */
    CY_SYSCLK_FLLPLL_OUTPUT_INPUT  = 2U, /**< Output FLL/PLL input source regardless of lock status */
    CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT = 3U  /**< Output FLL/PLL output regardless of lock status. This can be dangerous if used to clock clkHf, because FLL/PLL output may be unstable */
} cy_en_fll_pll_output_mode_t;


/** FLL current-controlled oscillator (CCO) frequency ranges.
* See register CLK_FLL_CONFIG4, bits CCO_RANGE.
*/
typedef enum
{
    CY_SYSCLK_FLL_CCO_RANGE0, /**< Target frequency is in range  48 -  64 MHz */
    CY_SYSCLK_FLL_CCO_RANGE1, /**< Target frequency is in range  64 -  85 MHz */
    CY_SYSCLK_FLL_CCO_RANGE2, /**< Target frequency is in range  85 - 113 MHz */
    CY_SYSCLK_FLL_CCO_RANGE3, /**< Target frequency is in range 113 - 150 MHz */
    CY_SYSCLK_FLL_CCO_RANGE4  /**< Target frequency is in range 150 - 200 MHz */
} cy_en_fll_cco_ranges_t;
/** \} group_sysclk_fll_enums */


/**
* \addtogroup group_sysclk_fll_structs
* \{
*/
/** Structure containing information for manual configuration of FLL.
*/
typedef struct
{
    uint32_t                    fllMult;         /**< CLK_FLL_CONFIG  register, FLL_MULT bits */
    uint16_t                    refDiv;          /**< CLK_FLL_CONFIG2 register, FLL_REF_DIV bits */
    cy_en_fll_cco_ranges_t      ccoRange;        /**< CLK_FLL_CONFIG4 register, CCO_RANGE bits */
    bool                        enableOutputDiv; /**< CLK_FLL_CONFIG  register, FLL_OUTPUT_DIV bit */
    uint16_t                    lockTolerance;   /**< CLK_FLL_CONFIG2 register, LOCK_TOL bits */
    uint8_t                     igain;           /**< CLK_FLL_CONFIG3 register, FLL_LF_IGAIN bits */
    uint8_t                     pgain;           /**< CLK_FLL_CONFIG3 register, FLL_LF_PGAIN bits */
    uint16_t                    settlingCount;   /**< CLK_FLL_CONFIG3 register, SETTLING_COUNT bits */
    cy_en_fll_pll_output_mode_t outputMode;      /**< CLK_FLL_CONFIG3 register, BYPASS_SEL bits */
    uint16_t                    cco_Freq;        /**< CLK_FLL_CONFIG4 register, CCO_FREQ bits */
} cy_stc_fll_manual_config_t;

/** \} group_sysclk_fll_structs */

/**
* \addtogroup group_sysclk_fll_funcs
* \{
*//*******************************************************************************
* Function Name: Cy_SysClk_FllConfigure
****************************************************************************//**
*
* Configures the FLL, for best accuracy optimization.
*
* \param inputFreq frequency of input source, in Hz
*
* \param outputFreq Desired FLL output frequency, in Hz. Allowable range is
* 24 MHz to 100 MHz. In all cases, FLL_OUTPUT_DIV must be set; the output divide
* by 2 option is required.
*
* \param outputMode \ref cy_en_fll_pll_output_mode_t
* If output mode is bypass, then the output frequency equals the input source
* frequency regardless of the frequency parameter values.
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - FLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - FLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - desired output frequency is out of valid range \n
* CY_SYSCLK_UNSUPPORTED_STATE - FLL is not present
*
* \note
* Call this function after changing the FLL input frequency, for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the FLL is enabled. If it is called, then this function
* returns with an CY_SYSCLK_INVALID_STATE return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the FLL is the source of CLK_HF0 and the FLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the FLL is the source of CLK_HF0 and the FLL frequency is decreasing.
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_FllEnable call. Any call to \ref Cy_SysClk_FllGetConfiguration
* before calling \ref Cy_SysClk_FllEnable returns old configuration values.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllConfigure
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_FllConfigure(uint32_t inputFreq, uint32_t outputFreq, cy_en_fll_pll_output_mode_t outputMode);


/*******************************************************************************
* Function Name: Cy_SysClk_FllManualConfigure
****************************************************************************//**
*
* Manually configures the FLL based on user inputs.
*
* \param config \ref cy_stc_fll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - FLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - FLL not configured because it is enabled
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call this function after changing the FLL input frequency, for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the FLL is enabled. If it is called, then this function
* returns immediately with an CY_SYSCLK_INVALID_STATE return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the FLL is the source of CLK_HF0 and the FLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the FLL is the source of CLK_HF0 and the FLL frequency is decreasing.
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_FllEnable call. Any call to \ref Cy_SysClk_FllGetConfiguration
* before calling \ref Cy_SysClk_FllEnable returns old configuration values.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllManualConfigure
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_FllManualConfigure(const cy_stc_fll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_FllGetConfiguration
****************************************************************************//**
*
* Reports the FLL configuration settings.
*
* \param config \ref cy_stc_fll_manual_config_t
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_FllEnable call. Any call to \ref Cy_SysClk_FllGetConfiguration
* before calling \ref Cy_SysClk_FllEnable returns old configuration values.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllGetConfiguration
*
*******************************************************************************/
void Cy_SysClk_FllGetConfiguration(cy_stc_fll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_FllEnable
****************************************************************************//**
*
* Enables the FLL. The FLL should be configured before calling this function.
*
* \param timeoutus Amount of time in micro seconds to wait for FLL to lock.
* If lock doesn't occur, the FLL is stopped. To avoid waiting for lock, set this to 0
* and manually check for lock using \ref Cy_SysClk_FllLocked.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - FLL successfully enabled \n
* CY_SYSCLK_TIMEOUT - Timeout waiting for FLL lock
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* While waiting for the FLL to lock, the FLL bypass mode is set to \ref CY_SYSCLK_FLLPLL_OUTPUT_INPUT.
* After the FLL is locked, the FLL bypass mdoe is then set to \ref CY_SYSCLK_FLLPLL_OUTPUT_OUTPUT.
*
* \note
* Call \ref SystemCoreClockUpdate after calling this function
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the FLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllEnable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_FllEnable(uint32_t timeoutus);


/*******************************************************************************
* Function Name: Cy_SysClk_FllIsEnabled
****************************************************************************//**
*
* Reports whether or not the FLL is enabled.
*
* \return
* false = disabled \n
* true = enabled
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllDisable
*
*******************************************************************************/
bool Cy_SysClk_FllIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_FllLocked
****************************************************************************//**
*
* Reports whether the FLL is locked first time during FLL starting.
* Intended to be used with \ref Cy_SysClk_FllEnable with zero timeout.
*
* \return
* false = not locked \n
* true = locked
*
* \note
* The unlock occurrence may appear during FLL normal operation, so this function
* is not recommended to check the FLL normal operation stability.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllLocked
*
*******************************************************************************/
bool Cy_SysClk_FllLocked(void);


/*******************************************************************************
* Function Name: Cy_SysClk_FllDisable
****************************************************************************//**
*
* Disables the FLL and the CCO.
*
* \return \ref cy_en_sysclk_status_t
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the FLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllDisable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_FllDisable(void);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

/*******************************************************************************
* Function Name: Cy_SysClk_FllOutputDividerEnable
****************************************************************************//**
*
* Enables/Disables the FLL output divider
*
* \param enable
*
*******************************************************************************/
void Cy_SysClk_FllOutputDividerEnable(bool enable);

#endif

/*******************************************************************************
* Function Name: Cy_SysClk_FllGetFrequency
****************************************************************************//**
*
* Returns the output frequency of the FLL.
*
* \return The output frequency of FLL.
*
* \note If the return value equals zero, that means FLL is disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_FllGetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_FllGetFrequency(void);

/** \} group_sysclk_fll_funcs */


/* ========================================================================== */
/* ===========================    PLL SECTION    ============================ */
/* ========================================================================== */
#if defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS22SRSS)

/**
* \addtogroup group_sysclk_pll_structs
* \{
*/
/** Structure containing information for configuration of a PLL.
*/
typedef struct
{
    uint32_t                    inputFreq;  /**< frequency of PLL source, in Hz */
    uint32_t                    outputFreq; /**< frequency of PLL output, in Hz */
    bool                        lfMode;     /**< CLK_PLL_CONFIG register, PLL_LF_MODE bit */
    cy_en_fll_pll_output_mode_t outputMode; /**< CLK_PLL_CONFIG register, BYPASS_SEL bits */
} cy_stc_pll_config_t;


/** Structure containing information for manual configuration of a PLL.
*/
typedef struct
{
    uint8_t                     feedbackDiv;  /**< CLK_PLL_CONFIG register, FEEDBACK_DIV (P) bits */
    uint8_t                     referenceDiv; /**< CLK_PLL_CONFIG register, REFERENCE_DIV (Q) bits */
    uint8_t                     outputDiv;    /**< CLK_PLL_CONFIG register, OUTPUT_DIV bits */
    bool                        lfMode;       /**< CLK_PLL_CONFIG register, PLL_LF_MODE bit */
    cy_en_fll_pll_output_mode_t outputMode;   /**< CLK_PLL_CONFIG register, BYPASS_SEL bits */
#if (CY_SRSS_PLL400M_PRESENT) || defined(CY_DOXYGEN)
    uint32_t                    fracDiv;      /**< CLK_PLL_CONFIG2 register, FRAC_DIV bits, only for CAT1C devices */
    bool                        fracDitherEn; /**< CLK_PLL_CONFIG2 register, FRAC_DITHER_EN bits, only for CAT1C devices */
    bool                        fracEn;       /**< CLK_PLL_CONFIG2 register, FRAC_EN bits, only for CAT1C devices */
    uint32_t                    sscgDepth;    /**< CLK_PLL_CONFIG3 register, SSCG_DEPTH bits, only for CAT1C devices */
    uint8_t                     sscgRate;     /**< CLK_PLL_CONFIG3 register, SSCG_RATE bits, only for CAT1C devices */
    bool                        sscgEn;       /**< CLK_PLL_CONFIG3 register, SSCG_EN bits, only for CAT1C devices */
#endif
} cy_stc_pll_manual_config_t;
/** \} group_sysclk_pll_structs */

#if (defined(CY_DEVICE_SECURE))

/** PRA structure for Cy_SysClk_PllManualConfigure function parameters */
typedef struct
{
    uint32_t                        clkPath;       /**< clkPath */
    cy_stc_pll_manual_config_t      *praConfig;    /**< config */
} cy_stc_pra_clk_pll_manconfigure_t;
#endif /* (defined(CY_DEVICE_SECURE)) */

/**
* \addtogroup group_sysclk_pll_funcs
* \{
*//*******************************************************************************
* Function Name: Cy_SysClk_PllConfigure
****************************************************************************//**
*
* Configures a given PLL.
* The configuration formula used is:
*   Fout = pll_clk * (P / Q / div_out), where:
*     Fout is the desired output frequency
*     pll_clk is the frequency of the input source
*     P is the feedback divider. Its value is in bitfield FEEDBACK_DIV.
*     Q is the reference divider. Its value is in bitfield REFERENCE_DIV.
*     div_out is the reference divider. Its value is in bitfield OUTPUT_DIV.
*
* \param clkPath Selects which PLL to configure. 1 is the first PLL; 0 is invalid.
*
* \param config \ref cy_stc_pll_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - Invalid clock path number, or input or desired output frequency is out of valid range \n
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call this function after changing the PLL input frequency, for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_PllEnable call. Any call to \ref Cy_SysClk_PllGetConfiguration
* before calling \ref Cy_SysClk_PllEnable returns old configuration values.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllConfigure
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PllConfigure(uint32_t clkPath, const cy_stc_pll_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_PllManualConfigure
****************************************************************************//**
*
* Manually configures a PLL based on user inputs.
*
* \param clkPath Selects which PLL to configure. 1 is the first PLL; 0 is invalid.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call this function after changing the PLL input frequency; for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_PllEnable call. Any call to \ref Cy_SysClk_PllGetConfiguration
* before calling \ref Cy_SysClk_PllEnable returns old configuration values.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllManualConfigure
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PllManualConfigure(uint32_t clkPath, const cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_PllGetConfiguration
****************************************************************************//**
*
* Reports configuration settings for a PLL.
*
* \param clkPath Selects which PLL to report. 1 is the first PLL; 0 is invalid.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL data successfully reported \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* On PSoC 64 devices the configuration on the PRA driver will be reflected
* after \ref Cy_SysClk_PllEnable call. Any call to \ref Cy_SysClk_PllGetConfiguration
* before calling \ref Cy_SysClk_PllEnable returns old configuration values.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllGetConfiguration
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PllGetConfiguration(uint32_t clkPath, cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_PllEnable
****************************************************************************//**
*
* Enables the PLL. The PLL should be configured before calling this function.
*
* \param clkPath Selects which PLL to enable. 1 is the first PLL; 0 is invalid.
*
* \param timeoutus amount of time in microseconds to wait for the PLL to lock.
* If the lock doesn't occur, PLL is stopped. To avoid waiting for lock, set this to 0
* and manually check for lock using \ref Cy_SysClk_PllLocked.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully enabled \n
* CY_SYSCLK_TIMEOUT - Timeout waiting for PLL lock \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllEnable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PllEnable(uint32_t clkPath, uint32_t timeoutus);


/*******************************************************************************
* Function Name: Cy_SysClk_PllIsEnabled
****************************************************************************//**
*
* Reports whether or not the selected PLL is enabled.
*
* \param clkPath Selects which PLL to check. 1 is the first PLL; 0 is invalid.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllDisable
*
*******************************************************************************/
bool Cy_SysClk_PllIsEnabled(uint32_t clkPath);


/*******************************************************************************
* Function Name: Cy_SysClk_PllLocked
****************************************************************************//**
*
* Reports whether or not the selected PLL is locked.
*
* \param clkPath Selects which PLL to check. 1 is the first PLL; 0 is invalid.
*
* \return
* false = not locked \n
* true = locked
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllLocked
*
*******************************************************************************/
bool Cy_SysClk_PllLocked(uint32_t clkPath);


/*******************************************************************************
* Function Name: Cy_SysClk_PllLostLock
****************************************************************************//**
*
* Reports whether or not the selected PLL lost its lock since the last time this
* function was called. Clears the lost lock indicator.
*
* \param clkPath Selects which PLL to check. 1 is the first PLL; 0 is invalid.
*
* \return
* false = did not lose lock \n
* true = lost lock
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllLostLock
*
*******************************************************************************/
bool Cy_SysClk_PllLostLock(uint32_t clkPath);


/*******************************************************************************
* Function Name: Cy_SysClk_PllDisable
****************************************************************************//**
*
* Disables the selected PLL.
*
* \param clkPath Selects which PLL to disable. 1 is the first PLL; 0 is invalid.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully disabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \sideeffect
* This function sets PLL bypass mode to CY_SYSCLK_FLLPLL_OUTPUT_INPUT.
* If AUTO mode should be used, call \ref Cy_SysClk_PllConfigure or
* \ref Cy_SysClk_PllManualConfigure before calling \ref Cy_SysClk_PllEnable.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllDisable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PllDisable(uint32_t clkPath);

/*******************************************************************************
* Function Name: Cy_SysClk_PllGetFrequency
****************************************************************************//**
*
* Returns the output frequency of the PLL.
*
* \param clkPath Selects which PLL to check. 1 is the first PLL; 0 is invalid
*
* \return The output frequency of the path PLL.
*
* \note If the return value equals zero, that means PLL is disabled.
*
* \note
* This API is available for CAT1A, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PllGetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_PllGetFrequency(uint32_t clkPath);

#if defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)

/********************************************************************************
* Function Name: Cy_SysClk_Pll200MConfigure
****************************************************************************//**
*
* Configures 200M PLL.
* The configuration formula used is:
*   Fout = pll_clk * (P / Q / div_out), where:
*     Fout is the desired output frequency
*     pll_clk is the frequency of the input source
*     P is the feedback divider. Its value is in bitfield FEEDBACK_DIV.
*     Q is the reference divider. Its value is in bitfield REFERENCE_DIV.
*     div_out is the reference divider. Its value is in bitfield OUTPUT_DIV.
*
* \param pllNum Selects which PLL to configure
*
* \param config \ref cy_stc_pll_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - Invalid clock path number, or input or desired output frequency is out of valid range \n
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call this function after changing the PLL input frequency, for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll200MConfigure(uint32_t pllNum, const cy_stc_pll_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MManualConfigure
****************************************************************************//**
*
* Manually configures a 200M PLL based on user inputs.
*
* \param pllNum Selects which PLL to configure.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
* For the PSoC 64 devices there are possible situations when function returns
* the PRA error status code. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call this function after changing the PLL input frequency; for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll200MManualConfigure(uint32_t pllNum, const cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MGetConfiguration
****************************************************************************//**
*
* Reports configuration settings for 200M PLL.
*
* \param pllNum Selects which PLL to report.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL data successfully reported \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll200MGetConfiguration(uint32_t pllNum, cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MEnable
****************************************************************************//**
*
* Enables the 200M PLL. The PLL should be configured before calling this function.
*
* \param pllNum Selects which PLL to enable.
*
* \param timeoutus amount of time in microseconds to wait for the PLL to lock.
* If the lock doesn't occur, PLL is stopped. To avoid waiting for lock, set this to 0
* and manually check for lock using \ref Cy_SysClk_PllLocked.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully enabled \n
* CY_SYSCLK_TIMEOUT - Timeout waiting for PLL lock \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll200MEnable(uint32_t pllNum, uint32_t timeoutus);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MIsEnabled
****************************************************************************//**
*
* Reports whether or not the selected 200M PLL is enabled.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll200MIsEnabled(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MLocked
****************************************************************************//**
*
* Reports whether or not the selected 200M PLL is locked.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = not locked \n
* true = locked
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll200MLocked(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MLostLock
****************************************************************************//**
*
* Reports whether or not the selected 200M PLL lost its lock since the last time this
* function was called. Clears the lost lock indicator.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = did not lose lock \n
* true = lost lock
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll200MLostLock(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MDisable
****************************************************************************//**
*
* Disables the selected 200M PLL.
*
* \param pllNum Selects which PLL to disable.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully disabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \sideeffect
* This function sets PLL bypass mode to CY_SYSCLK_FLLPLL_OUTPUT_INPUT.
* If AUTO mode should be used, call \ref Cy_SysClk_PllConfigure or
* \ref Cy_SysClk_PllManualConfigure before calling \ref Cy_SysClk_PllEnable.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll200MDisable(uint32_t pllNum);

/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MGetFrequency
****************************************************************************//**
*
* Gets the frequency of PLL200M
*
* \param pllNum Selects which PLL to check.
*
* \return
* PLL200M Frequency
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_Pll200MGetFrequency(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MConfigure
****************************************************************************//**
*
* Configures 400M PLL.
* The configuration formula used is:
*   Fout = pll_clk * (P / Q / div_out), where:
*     Fout is the desired output frequency
*     pll_clk is the frequency of the input source
*     P is the feedback divider. Its value is in bitfield FEEDBACK_DIV.
*     Q is the reference divider. Its value is in bitfield REFERENCE_DIV.
*     div_out is the reference divider. Its value is in bitfield OUTPUT_DIV.
*
* \param pllNum Selects which PLL to configure
*
* \param config \ref cy_stc_pll_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - Invalid clock path number, or input or desired output frequency is out of valid range \n
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call this function after changing the PLL input frequency, for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll400MConfigure(uint32_t pllNum, const cy_stc_pll_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MManualConfigure
****************************************************************************//**
*
* Manually configures a 400M PLL based on user inputs.
*
* \param pllNum Selects which PLL to configure.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully configured \n
* CY_SYSCLK_INVALID_STATE - PLL not configured because it is enabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call this function after changing the PLL input frequency; for example if
* \ref Cy_SysClk_ClkPathSetSource() is called.
*
* \note
* Do not call this function when the PLL is enabled. If it is called, then this function
* returns immediately with an error return value and no register updates.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the PLL frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll400MManualConfigure(uint32_t pllNum, const cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MGetConfiguration
****************************************************************************//**
*
* Reports configuration settings for 400M PLL.
*
* \param pllNum Selects which PLL to report.
*
* \param config \ref cy_stc_pll_manual_config_t
*
* \return  Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL data successfully reported \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll400MGetConfiguration(uint32_t pllNum, cy_stc_pll_manual_config_t *config);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MEnable
****************************************************************************//**
*
* Enables the 400M PLL. The PLL should be configured before calling this function.
*
* \param pllNum Selects which PLL to enable.
*
* \param timeoutus amount of time in microseconds to wait for the PLL to lock.
* If the lock doesn't occur, PLL is stopped. To avoid waiting for lock, set this to 0
* and manually check for lock using \ref Cy_SysClk_PllLocked.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully enabled \n
* CY_SYSCLK_TIMEOUT - Timeout waiting for PLL lock \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll400MEnable(uint32_t pllNum, uint32_t timeoutus);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MIsEnabled
****************************************************************************//**
*
* Reports whether or not the selected 400M PLL is enabled.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll400MIsEnabled(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MLocked
****************************************************************************//**
*
* Reports whether or not the selected 400M PLL is locked.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = not locked \n
* true = locked
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll400MLocked(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll200MLostLock
****************************************************************************//**
*
* Reports whether or not the selected 200M PLL lost its lock since the last time this
* function was called. Clears the lost lock indicator.
*
* \param pllNum Selects which PLL to check.
*
* \return
* false = did not lose lock \n
* true = lost lock
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_Pll400MLostLock(uint32_t pllNum);


/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MDisable
****************************************************************************//**
*
* Disables the selected 400M PLL.
*
* \param pllNum Selects which PLL to disable.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - PLL successfully disabled \n
* CY_SYSCLK_BAD_PARAM - invalid clock path number
* CY_SYSCLK_INVALID_STATE - ECO already enabled
* CY_SYSCLK_UNSUPPORTED_STATE - PLL is not present
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* the PLL is the source of CLK_HF0 and the CLK_HF0 frequency is decreasing.
*
* \sideeffect
* This function sets PLL bypass mode to CY_SYSCLK_FLLPLL_OUTPUT_INPUT.
* If AUTO mode should be used, call \ref Cy_SysClk_PllConfigure or
* \ref Cy_SysClk_PllManualConfigure before calling \ref Cy_SysClk_PllEnable.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_Pll400MDisable(uint32_t pllNum);

/*******************************************************************************
* Function Name: Cy_SysClk_Pll400MGetFrequency
****************************************************************************//**
*
* Gets the frequency of PLL400M
*
* \param pllNum Selects which PLL to check.
*
* \return
* PLL400M Frequency
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_Pll400MGetFrequency(uint32_t pllNum);

#endif

/** \} group_sysclk_pll_funcs */

#endif


#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)
/* ========================================================================== */
/* ===========================    IHO SECTION    ============================ */
/* ========================================================================== */

/**
* \addtogroup group_sysclk_iho_funcs
* \{
*/

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_IhoEnable
****************************************************************************//**
*
* Enables the IHO.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* This API is available for devices having MXS40SSRSS(CAT1B) and
* CY_IP_MXS22SRSS IP(CAT1D).
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
*******************************************************************************/
void Cy_SysClk_IhoEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_IhoIsEnabled
****************************************************************************//**
*
* Reports whether or not the selected IHO is enabled.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for devices having MXS40SSRSS(CAT1B) and
* CY_IP_MXS22SRSS IP(CAT1D).
*
*******************************************************************************/
bool Cy_SysClk_IhoIsEnabled(void);

/*******************************************************************************
* Function Name: Cy_SysClk_IhoDisable
****************************************************************************//**
*
* Disables IHO.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* This API is available for devices having MXS40SSRSS(CAT1B) and
* CY_IP_MXS22SRSS IP(CAT1D).
*
*******************************************************************************/
void Cy_SysClk_IhoDisable(void);

#endif

#if defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysClk_IhoDeepsleepEnable
****************************************************************************//**
*
* Enables the IHO during deepsleep mode
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
void Cy_SysClk_IhoDeepsleepEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_IhoIsDeepsleepEnabled
****************************************************************************//**
*
* Reports whether or not the selected IHO is enabled during deepsleep mode.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
bool Cy_SysClk_IhoIsDeepsleepEnabled(void);

/*******************************************************************************
* Function Name: Cy_SysClk_IhoDeepsleepDisable
****************************************************************************//**
*
* Disables IHO during deepsleep mode.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
void Cy_SysClk_IhoDeepsleepDisable(void);

/*******************************************************************************
* Function Name: Cy_SysClk_IhoDeepsleepDisable
****************************************************************************//**
*
* Set the trim value for IHO.
*
* \param trimVal Trim value to be set for IHO.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
void Cy_SysClk_IhoSetTrim(uint32_t trimVal);

/*******************************************************************************
* Function Name: Cy_SysClk_IhoDeepsleepDisable
****************************************************************************//**
*
* Get the trim value configured for IHO.
*
* \return
* Configured IHO Trim value.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
uint32_t Cy_SysClk_IhoGetTrim(void);


#endif/* CY_IP_MXS22SRSS*/

/** \} group_sysclk_iho_funcs */
#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)*/

/* ========================================================================== */
/* ===========================    IMO SECTION    ============================ */
/* ========================================================================== */

#if defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/**
* IMO frequency select sources.
*/

typedef enum
{
    CY_SYSCLK_IMO_IN_4MHz                = 0U, /**< 4MHz selected for IMO */
    CY_SYSCLK_IMO_IN_2MHz                = 1U, /**< 2MHz selected for IMO */
} cy_en_imo_in_sources_t;

/** \cond */
#define  CY_SYSCLK_IMO_IS_FREQ_VALID(freqSelect) (((freqSelect) == CY_SYSCLK_IMO_IN_4MHz) || \
                                                  ((freqSelect) == CY_SYSCLK_IMO_IN_2MHz))
/** \endcond */


/**
* \addtogroup group_sysclk_imo_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ImoEnable
****************************************************************************//**
*
* Enables the IMO.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS IP(CAT1D).
*
*******************************************************************************/
void Cy_SysClk_ImoEnable(void);

/*******************************************************************************
* Function Name: Cy_SysClk_ImoIsEnabled
****************************************************************************//**
*
* Reports whether or not the selected IMO is enabled.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for devices having MXS40SSRSS(CAT1B) and
* CY_IP_MXS22SRSS IP(CAT1D).
*
*******************************************************************************/
bool Cy_SysClk_ImoIsEnabled(void);

/*******************************************************************************
* Function Name: Cy_SysClk_ImoDisable
****************************************************************************//**
*
* Disables IMO.
*
*
* \note
* This API is available for devices having MXS40SSRSS(CAT1B) and
* CY_IP_MXS22SRSS IP(CAT1D).
*
*******************************************************************************/
void Cy_SysClk_ImoDisable(void);

/*******************************************************************************
* Function Name: Cy_SysClk_ImoDeepsleepEnable
****************************************************************************//**
*
* Enables the IMO during deepsleep mode
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
void Cy_SysClk_ImoDeepsleepEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ImoIsDeepsleepEnabled
****************************************************************************//**
*
* Reports whether or not the selected IMO is enabled during deepsleep mode.
*
* \return
* false = disabled \n
* true = enabled
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
bool Cy_SysClk_ImoIsDeepsleepEnabled(void);

/*******************************************************************************
* Function Name: Cy_SysClk_ImoDeepsleepDisable
****************************************************************************//**
*
* Disables IMO during deepsleep mode.
*
* \note
* This API is available for devices having CY_IP_MXS22SRSS(CAT1D) IP.
*
*******************************************************************************/
void Cy_SysClk_ImoDeepsleepDisable(void);

/** \} group_sysclk_imo_funcs */

#endif


/* ========================================================================== */
/* ===========================    ILO SECTION    ============================ */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_ilo_funcs
* \{
*/

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_IloEnable
****************************************************************************//**
*
* Enables the ILO.
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloEnable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
void Cy_SysClk_IloEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_IloIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of the ILO.
*
* \return Boolean status of ILO: true - Enabled, false - Disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloDisable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
bool Cy_SysClk_IloIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_IloDisable
****************************************************************************//**
*
* Disables the ILO. ILO can't be disabled if WDT is enabled.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ILO successfully disabled \n
* CY_SYSCLK_INVALID_STATE - Cannot disable the ILO if the WDT is enabled.
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
* Do not call this function if the WDT is enabled, because the WDT is clocked by
* the ILO.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloDisable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_IloDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_IloHibernateOn
****************************************************************************//**
*
* Controls whether the ILO stays on during a hibernate, or through an XRES or
* brown-out detect (BOD) event.
*
* \param on
* true = ILO stays on during hibernate or across XRES/BOD. \n
* false = ILO turns off for hibernate or XRES/BOD.
*
* \note Writes to the register/bit are ignored if the watchdog (WDT) is locked.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloHibernateOn
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
void Cy_SysClk_IloHibernateOn(bool on);
#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)  */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_IloSrcEnable
****************************************************************************//**
*
* Enables the ILO.
*
* \param iloNum - ILO index , 0 : ILO0, 1: ILO1
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloSrcEnable
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_IloSrcEnable(uint32_t iloNum);


/*******************************************************************************
* Function Name: Cy_SysClk_IloSrcIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of the ILO.
*
* \param iloNum - ILO index , ILO0 or ILO1
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloSrcIsEnabled
*
* \return Boolean status of ILO: true - Enabled, false - Disabled.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_IloSrcIsEnabled(uint32_t iloNum);


/*******************************************************************************
* Function Name: Cy_SysClk_IloSrcDisable
****************************************************************************//**
*
* Disables the ILO. ILO can't be disabled if WDT is enabled.
*
* \param iloNum - ILO index , 0 : ILO0, 1: ILO1
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloSrcDisable
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ILO successfully disabled \n
* CY_SYSCLK_INVALID_STATE - Cannot disable the ILO if the WDT is enabled.
* CY_SYSCLK_INVALID_STATE - ECO already enabled
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
* Do not call this function if the WDT is enabled, because the WDT is clocked by
* the ILO.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_IloSrcDisable(uint32_t iloNum);


/*******************************************************************************
* Function Name: Cy_SysClk_IloSrcHibernateOn
****************************************************************************//**
*
* Controls whether the ILO0 stays on during a hibernate, or through an XRES or
* brown-out detect (BOD) event, this feature is not available for ILO1.
*
* \param iloNum - ILO index , 0 : ILO0, 1: ILO1(Feature not available, ignored)
*
* \param on
* true = ILO stays on during hibernate or across XRES/BOD. \n
* false = ILO turns off for hibernate or XRES/BOD.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloSrcHibernateOn
*
* \note Writes to the register/bit are ignored if the watchdog (WDT) is locked.
*
* \note
* This API is available for CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_IloSrcHibernateOn(uint32_t iloNum, bool on);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

/** \} group_sysclk_ilo_funcs */


/* ========================================================================== */
/* ===========================    PILO SECTION    =========================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_pilo_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_PiloEnable
****************************************************************************//**
*
* Enables the PILO.
*
* \note This function blocks for 1 millisecond between enabling the PILO and
* releasing the PILO reset. This is applicable only for CAT1A Devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloEnable
*
*******************************************************************************/
void Cy_SysClk_PiloEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_PiloIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of the PILO.
*
* \return Boolean status of PILO: true - Enabled, false - Disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloDisable
*
*******************************************************************************/
bool Cy_SysClk_PiloIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_PiloDisable
****************************************************************************//**
*
* Disables the PILO.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloDisable
*
*******************************************************************************/
void Cy_SysClk_PiloDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_PiloSetTrim
****************************************************************************//**
*
* Sets the PILO trim bits, which adjusts the PILO frequency. This is typically
* done after measuring the PILO frequency; see \ref Cy_SysClk_StartClkMeasurementCounters().
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloSetTrim
*
*******************************************************************************/
void Cy_SysClk_PiloSetTrim(uint32_t trimVal);


/*******************************************************************************
* Function Name: Cy_SysClk_PiloGetTrim
****************************************************************************//**
*
* Reports the current PILO trim bits value.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloSetTrim
*
*******************************************************************************/
uint32_t Cy_SysClk_PiloGetTrim(void);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_PiloBackupEnable
****************************************************************************//**
*
* Enables the PILO as always on if Backup Domain is present.
*
* \note
* This API is available for CAT1B & CAT1D devices.
*
*******************************************************************************/
void Cy_SysClk_PiloBackupEnable(void);

/*******************************************************************************
* Function Name: Cy_SysClk_PiloBackupDisable
****************************************************************************//**
*
* Disables the PILO as always on if Backup Domain is present.
*
* \note
* This API is available for CAT1B & CAT1D devices.
*
*******************************************************************************/
void Cy_SysClk_PiloBackupDisable(void);
#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN) */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysClk_PiloTcscEnable
****************************************************************************//**
*
* Enables the PILO TCSC(Second order temperature curvature correction) Feature.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysClk_PiloTcscEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_PiloTcscDisable
****************************************************************************//**
*
* Disables the PILO TCSC(Second order temperature curvature correction) Feature.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysClk_PiloTcscDisable(void);

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN) */

/** \} group_sysclk_pilo_funcs */


/* ========================================================================== */
/* ==========================    ALTHF SECTION    =========================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_alt_hf_funcs
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysClk_AltHfGetFrequency
****************************************************************************//**
*
* Reports the frequency of the Alternative High-Frequency Clock
*
* \funcusage
* \snippet bleclk/snippet/main.c BLE ECO clock API: Cy_BLE_EcoConfigure()
*
*******************************************************************************/
uint32_t Cy_SysClk_AltHfGetFrequency(void);

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_AltHfEnable
****************************************************************************//**
*
* Enables the ATLHF.
*
* \note
* This API is available for CAT1B devices.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - ALTHF successfully disabled \n
* CY_SYSCLK_TIMEOUT - ALTHF enabling failed due to timeout
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_AltHfEnable(uint32_t timeoutus);

/*******************************************************************************
* Function Name: Cy_SysClk_IsAltHfEnabled
****************************************************************************//**
*
* Reports if ALTHF is enabled or not
*
* \return Status of ALTHF \n
* true = Enabled \n
* false = Not Enabled
*
*******************************************************************************/
bool Cy_SysClk_IsAltHfEnabled(void);

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS) */

/** \} group_sysclk_alt_hf_funcs */


/* ========================================================================== */
/* ==========================    ALTLF SECTION    =========================== */
/* ========================================================================== */
/** \cond For future usage */
uint32_t Cy_SysClk_AltLfGetFrequency(void);
bool Cy_SysClk_AltLfIsEnabled(void);
/** \endcond  */


/* ========================================================================== */
/* ====================    CLOCK MEASUREMENT SECTION    ===================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_calclk_enums
* \{
*/
/** Defines all possible clock sources */
typedef enum
{
    CY_SYSCLK_MEAS_CLK_NC =                0U,
    CY_SYSCLK_MEAS_CLK_ILO =               1U,
    CY_SYSCLK_MEAS_CLK_WCO =               2U,
    CY_SYSCLK_MEAS_CLK_BAK =               3U,
    CY_SYSCLK_MEAS_CLK_ALTLF =             4U,
    CY_SYSCLK_MEAS_CLK_LFCLK =             5U,
    CY_SYSCLK_MEAS_CLK_IMO =               6U,
    CY_SYSCLK_MEAS_CLK_SLPCTRL =           7U,
    CY_SYSCLK_MEAS_CLK_PILO =              8U,
    CY_SYSCLK_MEAS_CLK_ILO1 =              9U,
    CY_SYSCLK_MEAS_CLK_ECO_PRESCALER =     10U,
    CY_SYSCLK_MEAS_CLK_LPECO =             11U,
    CY_SYSCLK_MEAS_CLK_LPECO_PRESCALER =   12U,
    CY_SYSCLK_MEAS_CLK_MFO =               13U,
    CY_SYSCLK_MEAS_CLK_FAST_CLKS =         0x100U,
    CY_SYSCLK_MEAS_CLK_ECO =               0x101U,
    CY_SYSCLK_MEAS_CLK_EXT =               0x102U,
    CY_SYSCLK_MEAS_CLK_ALTHF =             0x103U,
    CY_SYSCLK_MEAS_CLK_TIMERCLK =          0x104U,
    CY_SYSCLK_MEAS_CLK_IHO =               0x108U,
    CY_SYSCLK_MEAS_CLK_PWR =               0x109U,
    CY_SYSCLK_MEAS_CLK_PATH_CLKS =         0x500U,
    CY_SYSCLK_MEAS_CLK_PATH0 =             0x500U,
    CY_SYSCLK_MEAS_CLK_PATH1 =             0x501U,
    CY_SYSCLK_MEAS_CLK_PATH2 =             0x502U,
    CY_SYSCLK_MEAS_CLK_PATH3 =             0x503U,
    CY_SYSCLK_MEAS_CLK_PATH4 =             0x504U,
    CY_SYSCLK_MEAS_CLK_PATH5 =             0x505U,
    CY_SYSCLK_MEAS_CLK_PATH6 =             0x506U,
    CY_SYSCLK_MEAS_CLK_PATH7 =             0x507U,
    CY_SYSCLK_MEAS_CLK_PATH8 =             0x508U,
    CY_SYSCLK_MEAS_CLK_PATH9 =             0x509U,
    CY_SYSCLK_MEAS_CLK_PATH10 =            0x50AU,
    CY_SYSCLK_MEAS_CLK_PATH11 =            0x50BU,
    CY_SYSCLK_MEAS_CLK_PATH12 =            0x50CU,
    CY_SYSCLK_MEAS_CLK_PATH13 =            0x50DU,
    CY_SYSCLK_MEAS_CLK_PATH14 =            0x50EU,
    CY_SYSCLK_MEAS_CLK_PATH15 =            0x50FU,
    CY_SYSCLK_MEAS_CLK_CLKHFS =            0x600U,
    CY_SYSCLK_MEAS_CLK_CLKHF0 =            0x600U,
    CY_SYSCLK_MEAS_CLK_CLKHF1 =            0x601U,
    CY_SYSCLK_MEAS_CLK_CLKHF2 =            0x602U,
    CY_SYSCLK_MEAS_CLK_CLKHF3 =            0x603U,
    CY_SYSCLK_MEAS_CLK_CLKHF4 =            0x604U,
    CY_SYSCLK_MEAS_CLK_CLKHF5 =            0x605U,
    CY_SYSCLK_MEAS_CLK_CLKHF6 =            0x606U,
    CY_SYSCLK_MEAS_CLK_CLKHF7 =            0x607U,
    CY_SYSCLK_MEAS_CLK_CLKHF8 =            0x608U,
    CY_SYSCLK_MEAS_CLK_CLKHF9 =            0x609U,
    CY_SYSCLK_MEAS_CLK_CLKHF10 =           0x60AU,
    CY_SYSCLK_MEAS_CLK_CLKHF11 =           0x60BU,
    CY_SYSCLK_MEAS_CLK_CLKHF12 =           0x60CU,
    CY_SYSCLK_MEAS_CLK_CLKHF13 =           0x60DU,
    CY_SYSCLK_MEAS_CLK_CLKHF14 =           0x60EU,
    CY_SYSCLK_MEAS_CLK_CLKHF15 =           0x60FU,
    CY_SYSCLK_MEAS_CLK_LAST_CLK =          0x610U
} cy_en_meas_clks_t;
/** \} group_sysclk_calclk_enums */

/**
* \addtogroup group_sysclk_calclk_structs
* \{
*/
#if (defined(CY_DEVICE_SECURE))
/** PRA structure for Cy_SysClk_StartClkMeasurementCounters function parameters */
typedef struct
{
    cy_en_meas_clks_t clock1;        /**< clock1 */
    uint32_t          count1;        /**< count  */
    cy_en_meas_clks_t clock2;        /**< clock2 */
} cy_stc_pra_start_clk_measurement_t;

#endif /* (defined(CY_DEVICE_SECURE)) */
/** \} group_sysclk_calclk_structs */

/**
* \addtogroup group_sysclk_calclk_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_StartClkMeasurementCounters
****************************************************************************//**
*
* Assigns clocks to the clock measurement counters, and starts counting. The counters
* let you measure a clock frequency using another clock as a reference. There are two
* counters.
*
* - One counter (counter1), which is clocked by clock1, is loaded with an initial
*   value and counts down to zero.
* - The second counter (counter2), which is clocked by clock2, counts up until
*   the first counter reaches zero.
*
* Either clock1 or clock2 can be a reference clock; the other clock becomes the
* measured clock. The reference clock frequency is always known. \n
* After calling this function, call \ref Cy_SysClk_ClkMeasurementCountersDone()
* to determine when counting is done; that is, counter1 has counted down to zero.
* Then call \ref Cy_SysClk_ClkMeasurementCountersGetFreq() to calculate the frequency
* of the measured clock.
*
* \param clock1 The clock for counter1
*
* \param count1 The initial value for counter1, from which counter1 counts down to zero.
*
* \param clock2 The clock for counter2
*
* \return Error / status code: \n
* CY_SYSCLK_INVALID_STATE if already doing a measurement \n
* CY_SYSCLK_BAD_PARAM if invalid clock input parameter \n
* else CY_SYSCLK_SUCCESS
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note The counters are both 24-bit, so the maximum value of count1 is 0xFFFFFF.
* If clock2 frequency is greater than clock1, make sure that count1 is low enough
* that counter2 does not overflow before counter1 reaches zero.
* \note The time to complete a measurement is count1 / clock1 frequency.
* \note The clocks for both counters must have a nonzero frequency, or
* \ref Cy_SysClk_ClkMeasurementCountersGetFreq() incorrectly reports the result of the
* previous  measurement.
* \note Do not enter a device low power mode (Sleep, Deep Sleep) while doing a measurement;
* the measured clock frequency may not be accurate.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_StartClkMeasurementCounters
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_StartClkMeasurementCounters(cy_en_meas_clks_t clock1, uint32_t count1, cy_en_meas_clks_t clock2);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMeasurementCountersGetFreq
****************************************************************************//**
*
* Calculates the frequency of the indicated measured clock (clock1 or clock2).
* - If clock1 is the measured clock, its frequency is: clock1 frequency = (count1 / count2) * clock2 frequency
* - If clock2 is the measured clock, its frequency is: clock2 frequency = (count2 / count1) * clock1 frequency
*
* Call this function only after counting is done; see \ref Cy_SysClk_ClkMeasurementCountersDone().
*
* \param measuredClock False (0) if the measured clock is clock1; true (1)
* if the measured clock is clock2.
*
* \param refClkFreq The reference clock frequency (clock1 or clock2).
*
* \return The frequency of the measured clock, in Hz.
* \warning The function returns zero, if during measurement device was in the
* Deep Sleep or partially blocking flash operation occurred. It means that
* current measurement is not valid and you should call the
* Cy_SysClk_StartClkMeasurementCounters() function once again.
*
* \funcusage
* Refer to the Cy_SysClk_StartClkMeasurementCounters() function usage.
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkMeasurementCountersGetFreq(bool measuredClock, uint32_t refClkFreq);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMeasurementCountersDone
****************************************************************************//**
*
* Checks if clock measurement counting is done, that is, counter1 has counted down
* to zero. Call \ref Cy_SysClk_StartClkMeasurementCounters() before calling this function.
*
* \return Status of calibration counters: \n
* true = done \n
* false = not done
*
* \funcusage
* Refer to the Cy_SysClk_StartClkMeasurementCounters() function usage.
*
*******************************************************************************/
bool Cy_SysClk_ClkMeasurementCountersDone(void);
/** \} group_sysclk_calclk_funcs */


/* ========================================================================== */
/* ==========================    TRIM SECTION    ============================ */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_trim_funcs
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysClk_IloTrim
****************************************************************************//**
*
* Trims the ILO to be as close to 32,768 Hz as possible.
*
* \param iloFreq current ILO frequency. Call \ref Cy_SysClk_StartClkMeasurementCounters
* and other measurement functions to obtain the current frequency of the ILO.
*
* \return Change in trim value - 0 if done; that is, no change in trim value.
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_IloTrim
*
*******************************************************************************/
int32_t Cy_SysClk_IloTrim(uint32_t iloFreq);

#if  defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_IloSetTrim
****************************************************************************//**
*
* Set ILO Trim Value
*
* \param trimVal Trim value to be set for ILO.
*
* \note
* The function is applicable only for a CAT1B Devices.
*
*******************************************************************************/
void Cy_SysClk_IloSetTrim(uint32_t trimVal);


/*******************************************************************************
* Function Name: Cy_SysClk_IloGetTrim
****************************************************************************//**
*
* Gets the ILO Trim Value.
*
* \return ILO Trim Value.
*
* \note
* The function is applicable only for a CAT1B Devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_IloGetTrim(void);

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_DOXYGEN) */

/*******************************************************************************
* Function Name: Cy_SysClk_PiloTrim
****************************************************************************//**
*
* Trims the PILO to be as close to 32,768 Hz as possible.
*
* \param piloFreq current PILO frequency. Call \ref Cy_SysClk_StartClkMeasurementCounters
* and other measurement functions to obtain the current frequency of the PILO.
*
* \return Change in trim value; 0 if done, that is, no change in trim value.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloTrim
*
*******************************************************************************/
int32_t Cy_SysClk_PiloTrim(uint32_t piloFreq);

/*******************************************************************************
* Function Name: Cy_SysClk_PiloInitialTrim
****************************************************************************//**
*
* Initial trims the PILO to be as close to 32,768 Hz as possible.
* This function takes ECO ALTHF as reference clock and calculate Fine PILO
* frequency trimming, by using binary search algorithm.
*
* This function requires configured BLE ECO ALTHF clock.
* Use ModusToolbox Device Configurator to configure BLE ECO ALTHF clock.
*
* \note
* This function must be call after every power-up.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloInitialTrimAndUpdateTrimStep
*
*******************************************************************************/
void Cy_SysClk_PiloInitialTrim(void);

/*******************************************************************************
* Function Name: Cy_SysClk_PiloUpdateTrimStep
****************************************************************************//**
*
* Calculates and updates the PILO trim step size (stepSize variable).
* The stepSize value is used by \ref Cy_SysClk_PiloTrim function during periodical
* PILO calibration.
*
* This function requires configured BLE ECO ALTHF clock.
* Use ModusToolbox Device Configurator to configure BLE ECO ALTHF clock.
*
* \note
* This function must be call after every power-up after call of
* \ref Cy_SysClk_PiloInitialTrim function.
*
* \note
* To achieve best trimming results it is recommended to configure BLE ECO ALTHF
* reference clock to 16 MHz.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PiloInitialTrimAndUpdateTrimStep
*
*******************************************************************************/
void Cy_SysClk_PiloUpdateTrimStep(void);
/** \} group_sysclk_trim_funcs */


/* ========================================================================== */
/* ======================    POWER MANAGEMENT SECTION    ==================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_pm_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_DeepSleepCallback
****************************************************************************//**
*
* Callback function to be used when entering system Deep Sleep mode.
* This function is applicable if:
* - The FLL is enabled
* - The PLL is enabled and is driven by ECO
*
* This function performs the following:
*
* 1. Before entering Deep Sleep, the clock configuration is saved in SRAM.
*    If the FLL/PLL source is the ECO, then the FLL/PLL is bypassed and the
*    source is changed to IMO. \n
*    If the FLL is enabled - it is just bypassed.
* 2. Upon wakeup from Deep Sleep, the function waits for ECO stabilization,
*    then restores the configuration and waits for the FLL/PLL to regain their
*    frequency locks. \n
*    If ECO is not used and FLL is enabled - it waits for FLL lock and unbypasses it.
*
* The function prevents entry into Deep Sleep mode if the measurement counters
* are currently counting; see \ref Cy_SysClk_StartClkMeasurementCounters.
*
* This function can be called during execution of \ref Cy_SysPm_CpuEnterDeepSleep.
* To do so, register this function as a callback before calling
* \ref Cy_SysPm_CpuEnterDeepSleep - specify \ref CY_SYSPM_DEEPSLEEP as the callback
* type and call \ref Cy_SysPm_RegisterCallback.
*
* \note
* This function is recommended to be the last callback that is registered.
* Doing so minimizes the time spent on low power mode entry and exit. \n
* This function implements all four SysPm callback modes \ref cy_en_syspm_callback_mode_t.
* So the \ref cy_stc_syspm_callback_t::skipMode must be set to 0UL. \n
* This function does not support such cases as, for example, FLL is enabled
* but bypassed by user code before entering Deep Sleep. \n
* You can use this callback implementation as an example to design custom low-power
* callbacks for certain user application.
*
* \param callbackParams
* structure with the syspm callback parameters,
* see \ref cy_stc_syspm_callback_params_t.
*
* \param mode
* Callback mode, see \ref cy_en_syspm_callback_mode_t
*
* \return Error / status code; see \ref cy_en_syspm_status_t. Pass if not doing
* a clock measurement, otherwise Fail. Timeout if timeout waiting for ECO, FLL
* or PLL to get stable / regain its frequency lock.
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_DeepSleepCallback
*
*******************************************************************************/
cy_en_syspm_status_t Cy_SysClk_DeepSleepCallback(cy_stc_syspm_callback_params_t * callbackParams, cy_en_syspm_callback_mode_t mode);
/** \} group_sysclk_pm_funcs */


/* ========================================================================== */
/* ===========================    WCO SECTION    ============================ */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_wco_enums
* \{
*/
/** WCO bypass modes */
typedef enum
{
    CY_SYSCLK_WCO_NOT_BYPASSED = 0U, /**< WCO is not bypassed crystal is used */
    CY_SYSCLK_WCO_BYPASSED = 1U      /**< WCO is bypassed external clock must be supplied  on XTAL pin */
} cy_en_wco_bypass_modes_t;

#if defined (CY_IP_MXS28SRSS)
/** WCO GM Config */
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_SYSCLK_WCO_GM_0P5    = 0U, /**< WCO GM - 0.5x */
    CY_SYSCLK_WCO_GM_1P0    = 1U, /**< WCO GM - 1.0x */
    CY_SYSCLK_WCO_GM_1P5    = 2U, /**< WCO GM - 1.5x */
    CY_SYSCLK_WCO_GM_2P0    = 3U, /**< WCO GM - 2.0x */
    CY_SYSCLK_WCO_GM_2P5    = 4U, /**< WCO GM - 2.5x */
    CY_SYSCLK_WCO_GM_3P0    = 5U, /**< WCO GM - 3.0x */
    CY_SYSCLK_WCO_GM_3P5    = 6U, /**< WCO GM - 3.5x */
    CY_SYSCLK_WCO_GM_4P0    = 7U, /**< WCO GM - 4.0x */
} cy_en_wco_gain_ctrl_modes_t;
#endif /* CY_IP_MXS28SRSS */

#if defined (CY_IP_MXS40SRSS)
/** \cond BWC */
/**
* \note
* This enum is available for CAT1A devices.
**/
typedef enum
{
    CY_SYSCLK_WCO_CSV_SUPERVISOR_ILO,
    CY_SYSCLK_WCO_CSV_SUPERVISOR_ALTLF,
    CY_SYSCLK_WCO_CSV_SUPERVISOR_PILO
} cy_en_wco_csv_supervisor_clock_t;

#endif /* CY_IP_MXS40SRSS */


/**
* Clock supervisor clock loss window. There must be one clock of the supervised
* clock within this many clocks of the supervising clock.
* See registers CLK_CSV_HF_CTL and CLK_CSV_WCO_CTL, bitfield CSV_LOSS_WINDOW.
*/
typedef enum
{
    CY_SYSCLK_CSV_LOSS_4_CYCLES =   0U, /**< 1 clock must be seen within 4 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_8_CYCLES =   1U, /**< 1 clock must be seen within 8 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_16_CYCLES =  2U, /**< 1 clock must be seen within 16 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_32_CYCLES =  3U, /**< 1 clock must be seen within 32 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_64_CYCLES =  4U, /**< 1 clock must be seen within 64 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_128_CYCLES = 5U, /**< 1 clock must be seen within 128 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_256_CYCLES = 6U, /**< 1 clock must be seen within 256 cycles of the supervising clock */
    CY_SYSCLK_CSV_LOSS_512_CYCLES = 7U  /**< 1 clock must be seen within 512 cycles of the supervising clock */
} cy_en_csv_loss_window_t;

/**
* Clock supervisor error actions. See register CLK_CSV_HF_CTL[CSV_FREQ_ACTION and CSV_LOSS_ACTION].
*/
typedef enum
{
    CY_SYSCLK_CSV_ERROR_IGNORE =      0U, /**< Ignore the error reported by the clock supervisor */
    CY_SYSCLK_CSV_ERROR_FAULT =       1U, /**< Trigger a fault when an error is reported by the clock supervisor */
    CY_SYSCLK_CSV_ERROR_RESET =       2U, /**< Trigger a reset when an error is reported by the clock supervisor */
    CY_SYSCLK_CSV_ERROR_FAULT_RESET = 3U  /**< Trigger a fault then reset when an error is reported by the supervisor */
} cy_en_csv_error_actions_t;

#if defined (CY_IP_MXS28SRSS)
/** WCO CSV supervisor clock selections */
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_SYSCLK_WCO_CSV_SUPERVISOR_ILO,   /**< WCO CSV supervisor clock source is the ILO */
    CY_SYSCLK_WCO_CSV_SUPERVISOR_ALTLF, /**< WCO CSV supervisor clock source is the alternate low-frequency clock (ALTLF) */
    CY_SYSCLK_WCO_CSV_SUPERVISOR_PILO   /**< WCO CSV supervisor clock source is the PILO */
} cy_en_wco_csv_supervisor_clock_t;

/** \endcond */

/** \} group_sysclk_wco_enums */

/** \cond BWC */

/**
* \addtogroup group_sysclk_wco_structs
* \{
*/
/**
* This structure is used to configure the clock supervisor for the WCO.
*/
/**
* \note
* This structure is available for CAT1B devices.
**/
typedef struct
{
    cy_en_wco_csv_supervisor_clock_t supervisorClock; /**< supervisor clock selection */
    bool enableLossDetection;                         /**< 1= enabled, 0= disabled. Note that if loss detection is enabled, writes to other register bits are ignored */
    cy_en_csv_loss_window_t lossWindow;               /**< \ref cy_en_csv_loss_window_t */
    cy_en_csv_error_actions_t lossAction;             /**< \ref cy_en_csv_error_actions_t */
} cy_stc_wco_csv_config_t;

#endif /* CY_IP_MXS28SRSS */

/** \} group_sysclk_wco_structs */

#if defined (CY_IP_MXS40SRSS)
/**
* \note
* This structure is available for CAT1A devices.
**/
typedef struct
{
    cy_en_wco_csv_supervisor_clock_t supervisorClock;
    bool enableLossDetection;
    cy_en_csv_loss_window_t lossWindow;
    cy_en_csv_error_actions_t lossAction;
} cy_stc_wco_csv_config_t;
/** \endcond */
#endif /* CY_IP_MXS40SRSS */

/**
* \addtogroup group_sysclk_wco_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_WcoEnable
****************************************************************************//**
*
* Enables the WCO.
*
* \param timeoutus amount of time in microseconds to wait for the WCO to be ready.
* If WCO is not ready, WCO is stopped. To avoid waiting for WCO ready set this to 0,
* and manually check if WCO is okay using \ref Cy_SysClk_WcoOkay.
*
* \return Error / status code: \n
* CY_SYSCLK_SUCCESS - WCO successfully enabled \n
* CY_SYSCLK_TIMEOUT - Timeout waiting for WCO to stabilize
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_WcoEnable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_WcoEnable(uint32_t timeoutus);


/*******************************************************************************
* Function Name: Cy_SysClk_WcoOkay
****************************************************************************//**
*
* Reports the status of the WCO_OK bit.
*
* \return
* true = okay \n
* false = not okay
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_WcoOkay
*
*******************************************************************************/
bool Cy_SysClk_WcoOkay(void);


/*******************************************************************************
* Function Name: Cy_SysClk_WcoDisable
****************************************************************************//**
*
* Disables the WCO.
*
* \note
* We need to set writable option using Cy_RTC_WriteEnable
* before disabling WCO, and clear writable option after disabling WCO.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_WcoDisable
*
*******************************************************************************/
void Cy_SysClk_WcoDisable(void);


#if defined (CY_IP_MXS28SRSS)
/*******************************************************************************
* Function Name: Cy_SysClk_WcoGainControl
****************************************************************************//**
*
* Sets the GM(Loop Gain Control) for WCO.
*
* \param gmMode \ref cy_en_wco_gain_ctrl_modes_t
*
* \funcusage
* TBD
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysClk_WcoGainControl(cy_en_wco_gain_ctrl_modes_t gmMode);

#endif /* CY_IP_MXS28SRSS */

/*******************************************************************************
* Function Name: Cy_SysClk_WcoBypass
****************************************************************************//**
*
* Sets whether the WCO is bypassed or not. If it is bypassed, then a 32-kHz clock
* must be provided on the wco_out pin.
*
* \param bypass \ref cy_en_wco_bypass_modes_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_WcoBypass
*
*******************************************************************************/
void Cy_SysClk_WcoBypass(cy_en_wco_bypass_modes_t bypass);
/** \} group_sysclk_wco_funcs */


/* ========================================================================== */
/* ============================    MF SECTION    ============================ */
/* ========================================================================== */


/**
* \addtogroup group_sysclk_clk_mf_enums
* \{
*/
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined(CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/**
* \note
* This Enumeration is available for CAT1B devices.
**/
/**
* Medium frequency (clkMf) input sources. See CLK_MF_SELECT register, MFCLK_SEL bits.
* Used with functions \ref Cy_SysClk_ClkMfSetSource, and \ref Cy_SysClk_ClkMfGetSource.
*/
typedef enum
{
    CY_SYSCLK_CLKMF_IN_MFO               = 0U, /**< clkMf is sourced by the internal low speed oscillator (ILO) */
    CY_SYSCLK_CLKMF_IN_ILO               = 1U, /**< clkMf is sourced by the internal low speed oscillator (ILO) */
    CY_SYSCLK_CLKMF_IN_WCO               = 2U, /**< clkMf is sourced by the watch crystal oscillator (WCO) */
    CY_SYSCLK_CLKMF_IN_ALTLF             = 3U, /**< clkMf is sourced by the Alternate Low Frequency Clock (ALTLF) */
    CY_SYSCLK_CLKMF_IN_PILO              = 4U, /**< clkMf is sourced by the precision low speed oscillator (PILO) */
    CY_SYSCLK_CLKMF_IN_ILO1              = 5U, /**< clkMf is sourced by the precision low speed oscillator (ILO1) */
    CY_SYSCLK_CLKMF_IN_ECO_PRESCALER     = 6U, /**< clkMf is sourced by the External Clock Oscillator (ECO Prescaler) */
    CY_SYSCLK_CLKMF_IN_LPECO             = 7U, /**< clkMf is sourced by the External Clock Oscillator (LPECO) */
} cy_en_clkmf_in_sources_t;

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined (CY_DOXYGEN) */

/** \} group_sysclk_clk_mf_enums */

/**
* \addtogroup group_sysclk_mf_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_MfoEnable
****************************************************************************//**
*
* Enables the MFO.
*
* \param deepSleepEnable enables MFO operation is Deep Sleep low power mode.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
void Cy_SysClk_MfoEnable(bool deepSleepEnable);


/*******************************************************************************
* Function Name: Cy_SysClk_MfoIsEnabled
****************************************************************************//**
*
* Reports whether MFO is enabled or not.
*
* \return
* false - disabled \n
* true  - enabled
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfDisable
*
*******************************************************************************/
bool Cy_SysClk_MfoIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_MfoDisable
****************************************************************************//**
*
* Disables the MFO.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfDisable
*
*******************************************************************************/
void Cy_SysClk_MfoDisable(void);


/** \cond internal */
#define CY_SYSCLK_MF_DIVIDER_MIN                  (1U)
#define CY_SYSCLK_MF_DIVIDER_MAX                  (256U)
#define CY_SYSCLK_IS_MF_DIVIDER_VALID(locDiv)     ((CY_SYSCLK_MF_DIVIDER_MIN <= (locDiv)) && ((locDiv) <= CY_SYSCLK_MF_DIVIDER_MAX))
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined(CY_IP_MXS22SRSS)
/**
 * \note
 * This macro is available for CAT1B and CAT1D devices.
 **/
#define CY_SYSCLK_IF_MF_SOURCE_VALID(mfClkSrc)    (((mfClkSrc) == CY_SYSCLK_CLKMF_IN_MFO)     || \
                                                    ((mfClkSrc) == CY_SYSCLK_CLKMF_IN_ILO) || \
                                                    ((mfClkSrc) == CY_SYSCLK_CLKMF_IN_WCO) || \
                                                    ((mfClkSrc) == CY_SYSCLK_CLKMF_IN_ALTLF) || \
                                                    ((mfClkSrc) == CY_SYSCLK_CLKMF_IN_PILO))

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || defined(CY_IP_MXS22SRSS)*/

/** \endcond */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined(CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfEnable
****************************************************************************//**
*
* Enables the CLK_MF.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
void Cy_SysClk_ClkMfEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfIsEnabled
****************************************************************************//**
*
* Reports whether CLK_MF is enabled or not.
*
* \return
* false - disabled \n
* true  - enabled
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
bool Cy_SysClk_ClkMfIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfDisable
****************************************************************************//**
*
* Disables the CLK_MF.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfDisable
*
*******************************************************************************/
void Cy_SysClk_ClkMfDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfSetDivider
****************************************************************************//**
*
* Sets the clock divider for CLK_MF.
*
* \pre If the CLK_MF is already enabled - it should be disabled
* prior to use this function by \ref Cy_SysClk_ClkMfDisable.
*
* \param divider divider value between 1 and 256.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
void Cy_SysClk_ClkMfSetDivider(uint32_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfGetDivider
****************************************************************************//**
*
* Returns the clock divider of CLK_MF.
*
* \return divider value in range 1..256.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkMfGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfGetFrequency
****************************************************************************//**
*
* Reports the output clock signal frequency of CLK_MF.
*
* \return The frequency, in Hz.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkMfEnable
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkMfGetFrequency(void);

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN) */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) ||  defined(CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfSetSource
****************************************************************************//**
*
* Sets the source for the Medium frequency clock(clkMf).
*
* \param source \ref cy_en_clkmf_in_sources_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
void Cy_SysClk_ClkMfSetSource(cy_en_clkmf_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMfGetSource
****************************************************************************//**
*
* Reports the source for the Medium frequency clock (clkMf).
*
* \return \ref cy_en_clkmf_in_sources_t
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
cy_en_clkmf_in_sources_t Cy_SysClk_ClkMfGetSource(void);

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS28SRSS) */

/** \} group_sysclk_mf_funcs */

/* ========================================================================== */
/* =========================    clkHf[n] SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_hf_enums
* \{
*/
/**
* Selects which clkHf input, or root mux, to configure.
* See CLK_ROOT_SELECT registers, bits ROOT_MUX.
* Used with functions \ref Cy_SysClk_ClkHfSetSource and \ref Cy_SysClk_ClkHfGetSource.
*/
typedef enum
{
    CY_SYSCLK_CLKHF_IN_CLKPATH0  = 0U,  /**< clkHf input is Clock Path 0 */
    CY_SYSCLK_CLKHF_IN_CLKPATH1  = 1U,  /**< clkHf input is Clock Path 1 */
    CY_SYSCLK_CLKHF_IN_CLKPATH2  = 2U,  /**< clkHf input is Clock Path 2 */
    CY_SYSCLK_CLKHF_IN_CLKPATH3  = 3U,  /**< clkHf input is Clock Path 3 */
    CY_SYSCLK_CLKHF_IN_CLKPATH4  = 4U,  /**< clkHf input is Clock Path 4 */
    CY_SYSCLK_CLKHF_IN_CLKPATH5  = 5U,  /**< clkHf input is Clock Path 5 */
    CY_SYSCLK_CLKHF_IN_CLKPATH6  = 6U,  /**< clkHf input is Clock Path 6 */
    CY_SYSCLK_CLKHF_IN_CLKPATH7  = 7U,  /**< clkHf input is Clock Path 7 */
    CY_SYSCLK_CLKHF_IN_CLKPATH8  = 8U,  /**< clkHf input is Clock Path 8 */
    CY_SYSCLK_CLKHF_IN_CLKPATH9  = 9U,  /**< clkHf input is Clock Path 9 */
    CY_SYSCLK_CLKHF_IN_CLKPATH10 = 10U, /**< clkHf input is Clock Path 10 */
    CY_SYSCLK_CLKHF_IN_CLKPATH11 = 11U, /**< clkHf input is Clock Path 11 */
    CY_SYSCLK_CLKHF_IN_CLKPATH12 = 12U, /**< clkHf input is Clock Path 12 */
    CY_SYSCLK_CLKHF_IN_CLKPATH13 = 13U, /**< clkHf input is Clock Path 13 */
    CY_SYSCLK_CLKHF_IN_CLKPATH14 = 14U, /**< clkHf input is Clock Path 14 */
    CY_SYSCLK_CLKHF_IN_CLKPATH15 = 15U, /**< clkHf input is Clock Path 15 */
} cy_en_clkhf_in_sources_t;

#if defined (CY_IP_MXS28SRSS)
/**
* clkHf clock supervisor input sources. See register CLK_CSV_HF_CTL[CSV_MUX].
*/
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_IMO   = 0U,  /**< Supervising clock is the IMO */
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_EXT   = 1U,  /**< Supervising clock is the external clock */
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_ALTHF = 2U   /**< Supervising clock is clk_althf */
} cy_en_clkhf_csv_supervisor_clock_t;
#endif /* CY_IP_MXS28SRSS */

/** \} group_sysclk_clk_hf_enums */

/**
* \addtogroup group_sysclk_clk_hf_enums
* \{
*/
/**
* clkHf divider values. See CLK_ROOT_SELECT registers, bits ROOT_DIV.
* Used with functions \ref Cy_SysClk_ClkHfSetDivider and \ref Cy_SysClk_ClkHfGetDivider.
*/
typedef enum
{
    CY_SYSCLK_CLKHF_NO_DIVIDE   = 0U,    /**< don't divide clkHf */
    CY_SYSCLK_CLKHF_DIVIDE_BY_2 = 1U,    /**< divide clkHf by 2 */
    CY_SYSCLK_CLKHF_DIVIDE_BY_4 = 2U,    /**< divide clkHf by 4 */
    CY_SYSCLK_CLKHF_DIVIDE_BY_8 = 3U     /**< divide clkHf by 8 */
} cy_en_clkhf_dividers_t;

/** \} group_sysclk_clk_hf_enums */

#if defined (CY_IP_MXS40SRSS)
/** \cond BWC */
typedef enum
{
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_IMO   = 0U,
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_EXT   = 1U,
    CY_SYSCLK_CLKHF_CSV_SUPERVISOR_ALTHF = 2U
} cy_en_clkhf_csv_supervisor_clock_t;

typedef struct
{
    cy_en_clkhf_csv_supervisor_clock_t supervisorClock;
    uint16_t supervisingWindow;
    bool enableFrequencyFaultDetection;
    uint16_t frequencyLowerLimit;
    uint16_t frequencyUpperLimit;
    cy_en_csv_error_actions_t frequencyAction;
    bool enableLossDetection;
    cy_en_csv_loss_window_t lossWindow;
    cy_en_csv_error_actions_t lossAction;
} cy_stc_clkhf_csv_config_t;

#if (defined (CY_DEVICE_SECURE))
/** PRA structure for Cy_SysClk_ClkHfSetSource function parameters */
typedef struct
{
    uint32_t                  clkHf;         /**< clkHF  */
    cy_en_clkhf_in_sources_t source;        /**< Source */
} cy_stc_pra_clkhfsetsource_t;

/** PRA structure for Cy_SysClk_ClkHfSetSource function parameters */
typedef struct
{
    uint32_t                  clkHf;         /**< clkHF */
    cy_en_clkhf_dividers_t divider;        /**< divider */
} cy_stc_pra_clkhfsetdivider_t;
#endif /* (defined (CY_DEVICE_SECURE)) */

#define altHfFreq (cy_BleEcoClockFreqHz)
/** \endcond */
#endif /* CY_IP_MXS40SRSS */

#if defined (CY_IP_MXS28SRSS)
/** \cond BWC */
/**
* \addtogroup group_sysclk_clk_hf_structs
* \{
*/
/**
* This structure is used to configure the clock supervisor for clkHf.
*/
/**
* \note
* This structure is available for CAT1B devices.
**/
typedef struct
{
    cy_en_clkhf_csv_supervisor_clock_t supervisorClock; /**< \ref cy_en_clkhf_csv_supervisor_clock_t */
    uint16_t supervisingWindow;                         /**< Number of supervising clock cycles */
    bool enableFrequencyFaultDetection;                 /**< 1= enabled, 0= disabled */
    uint16_t frequencyLowerLimit;                       /**< Lowest frequency in kHz that supervised clock can go */
    uint16_t frequencyUpperLimit;                       /**< Highest frequency in kHz that supervised clock can go */
    cy_en_csv_error_actions_t frequencyAction;          /**< \ref cy_en_csv_error_actions_t */
    bool enableLossDetection;                           /**< 1= enabled, 0= disabled */
    cy_en_csv_loss_window_t lossWindow;                 /**< \ref cy_en_csv_loss_window_t */
    cy_en_csv_error_actions_t lossAction;               /**< \ref cy_en_csv_error_actions_t */
} cy_stc_clkhf_csv_config_t;
/** \} group_sysclk_clk_hf_structs */
/** \endcond */

/** \cond INTERNAL */
/**
* \note
* It is available for CAT1B devices.
**/
extern uint32_t altHfFreq; /* Internal storage for BLE ECO frequency user setting */
/** \endcond */
#endif /* CY_IP_MXS28SRSS */

/**
* \addtogroup group_sysclk_clk_hf_funcs
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfEnable
****************************************************************************//**
*
* Enables the selected clkHf.
*
* \param clkHf Selects which clkHf to enable.
*
* \return \ref cy_en_sysclk_status_t
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPathSetSource
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkHfEnable(uint32_t clkHf);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of clkHf.
*
* \param clkHf Selects which clkHf to check.
*
* \return Boolean status of clkHf: true - Enabled, false - Disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfDisable
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
bool Cy_SysClk_ClkHfIsEnabled(uint32_t clkHf);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfDisable
****************************************************************************//**
*
* Disables the selected clkHf.
*
* \param clkHf Selects which clkHf to enable.
*
* \return \ref cy_en_sysclk_status_t
*
* \note clkHf[0] cannot be disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfDisable
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkHfDisable(uint32_t clkHf);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfSetSource
****************************************************************************//**
*
* Selects the source of the selected clkHf.
*
* \param clkHf selects which clkHf mux to configure.
*
* \param source \ref cy_en_clkhf_in_sources_t
*
* \return \ref cy_en_sysclk_status_t
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* CLK_HF0 frequency is decreasing.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfSetSource
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \note  It takes four cycles of the originally selected clock to switch away
* from it.  Do not disable the original clock during this time.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkHfSetSource(uint32_t clkHf, cy_en_clkhf_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfGetSource
****************************************************************************//**
*
* Reports the source of the selected clkHf.
*
* \param clkHf selects which clkHf to get the source of.
*
* \return \ref cy_en_clkhf_in_sources_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfSetSource
*
*******************************************************************************/
cy_en_clkhf_in_sources_t Cy_SysClk_ClkHfGetSource(uint32_t clkHf);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfSetDivider
****************************************************************************//**
*
* Sets the pre-divider for a clkHf.
*
* \param clkHf selects which clkHf divider to configure.
*
* \param divider \ref cy_en_clkhf_dividers_t
*
* \return \ref cy_en_sysclk_status_t
* CY_PRA_STATUS_* - For the PSoC 64 devices there are possible situations when
* function returns the PRA error status code \ref cy_en_pra_status_t instead of
* \ref cy_en_sysclk_status_t. This is because for PSoC 64 devices the function
* uses the PRA driver to change the protected registers. Refer to
* \ref cy_en_pra_status_t for more details.
*
* \note Also call \ref Cy_SysClk_ClkHfSetSource to set the clkHf source.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling
* if it affects the CLK_HF0 frequency.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* CLK_HF0 frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* CLK_HF0 frequency is decreasing.
*
* \note
* Take into account the possible platform specific clkHf (and further
* clocking chain links) frequency limitations while using this API.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfSetDivider
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkHfSetDivider(uint32_t clkHf, cy_en_clkhf_dividers_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfGetDivider
****************************************************************************//**
*
* Reports the pre-divider value for a clkHf.
*
* \param clkHf selects which clkHf to check divider of.
*
* \return \ref cy_en_clkhf_dividers_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfSetDivider
*
*******************************************************************************/
cy_en_clkhf_dividers_t Cy_SysClk_ClkHfGetDivider(uint32_t clkHf);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfGetFrequency
****************************************************************************//**
*
* Reports the frequency of the selected clkHf
*
* \param clkHf Selects the clkHf
*
* \return The frequency, in Hz.
*
* \note
* The reported frequency may be zero, which indicates unknown. This happens if
* the source input is dsi_out or clk_altlf.
*
* \note
* Calculates the HF frequency irrespective of whether HF is enabled or not.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkHfSetDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkHfGetFrequency(uint32_t clkHf);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysClk_ClkHfDirectSel
****************************************************************************//**
*
* Enable/Disable the direct source selection as IMO for CLK_HF[[n]]
*
* \param clkHf Selects the clkHf
*
* \param enable True - Selects IMO , False - Selects Root Mux
*
* \return \ref cy_en_sysclk_status_t
* CY_SYSCLK_BAD_PARAM - If clkhf is incorrect.
* CY_SYSCLK_SUCCESS - If successfully Enabled/Disabled.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_ClkHfDirectSel(uint32_t clkHf, bool enable);

/*******************************************************************************
* Function Name: Cy_SysClk_IsClkHfDirectSelEnabled
****************************************************************************//**
*
* Checks if direct source selection as IMO for CLK_HF[[n]] is enabled/disabled
*
* \param clkHf Selects the clkHf
*
* \return
* True - IMO is selected  , False - Root Mux is selected
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
bool Cy_SysClk_IsClkHfDirectSelEnabled(uint32_t clkHf);

#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN) */

/** \} group_sysclk_clk_hf_funcs */


/* ========================================================================== */
/* =========================    clk_fast SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_fast_funcs
* \{
*/

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastSetDivider
****************************************************************************//**
*
* Sets the clock divider for the fast clock, which sources the main processor.
* The source of this divider is clkHf[0].
*
* \param divider divider value between 0 and 255.
* Causes integer division of (divider value + 1), or division by 1 to 256.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* CLK_FAST frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* CLK_FAST frequency is decreasing.
*
* \note
* This API is available only for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkFastSetDivider
*
*******************************************************************************/
void Cy_SysClk_ClkFastSetDivider(uint8_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastGetDivider
****************************************************************************//**
*
* Returns the clock divider for the fast clock.
*
* \return The divider value for the fast clock.
* The integer division done is by (divider value + 1), or division by 1 to 256.
*
* \note
* This API is available only for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkFastSetDivider
*
*******************************************************************************/
uint8_t Cy_SysClk_ClkFastGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastGetFrequency
****************************************************************************//**
*
* Reports the frequency of the fast clock.
*
* \return The frequency, in Hz.
*
* \note
* This API is available only for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkFastSetDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkFastGetFrequency(void);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN) */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastSrcSetDivider
****************************************************************************//**
*
* Sets the clock divider for the fast clock, which sources the main processor.
* The source of this divider is clkHf[0].
*
* \param clkFastNum 0 for CLOCK_FAST_0 and 1 for CLOCK_FAST_1
*
* \param intDiv Integer divider
*
* \param fracDiv Fractional divider
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates before calling this function if
* CLK_FAST frequency is increasing.
*
* \note
* Call \ref Cy_SysLib_SetWaitStates after calling this function if
* CLK_FAST frequency is decreasing.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkFastSrcSetDivider(uint32_t clkFastNum, uint8_t intDiv, uint8_t fracDiv);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastSrcGetDivider
****************************************************************************//**
*
* Returns the Integer and Fractional clock divider for the fast clock.
*
* \param clkFastNum 0 for CLOCK_FAST_0 and 1 for CLOCK_FAST_1
*
* \param dividerIntValue - Integer divider
*
* \param dividerFracValue - Fractional divider
*
* \return None. Loads pointed-to variables.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkFastSrcGetDivider(uint32_t clkFastNum, uint32_t *dividerIntValue, uint32_t *dividerFracValue);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkFastSrcGetFrequency
****************************************************************************//**
*
* Reports the frequency of the fast clock.
*
* \param clkFastNum 0 for CLOCK_FAST_0 and 1 for CLOCK_FAST_1
*
* \return The frequency, in Hz.
*
* \note
* This API is available only for CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkFastSrcGetFrequency(uint32_t clkFastNum);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN) */

/** \} group_sysclk_clk_fast_funcs */

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))  || defined (CY_IP_MXS22SRSS)

/* ========================================================================== */
/* ========================    PERI SECTION    ========================== */
/* ========================================================================== */

/**
* \addtogroup group_sysclk_clk_peripheral_enums
* \{
*/
/**
* Slave control Register Numbers
* Used with functions \ref Cy_SysClk_ClkHfSetDivider and \ref Cy_SysClk_ClkHfGetDivider.
*/
typedef enum
{
    CY_SYSCLK_PERI_GROUP_SL_CTL   = 0U,    /**<Selects SL_CTL*/
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)  || defined (CY_IP_MXS22SRSS)
    CY_SYSCLK_PERI_GROUP_SL_CTL2  = 1U,    /**<Selects SL_CTL2*/
    CY_SYSCLK_PERI_GROUP_SL_CTL3  = 2U,    /**<Selects SL_CTL3*/
#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)  || defined (CY_IP_MXS22SRSS) */
} cy_en_peri_grp_sl_ctl_num_t;

/** \} group_sysclk_clk_peripheral_enums */

/** \cond internal */
/* Macro to validate if the SL control register number passed */
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS)
#define CY_SYSCLK_IS_SL_CTL_NUM_VALID(slaveCtl)           (((slaveCtl) == CY_SYSCLK_PERI_GROUP_SL_CTL) || \
                                                           ((slaveCtl) == CY_SYSCLK_PERI_GROUP_SL_CTL2) || \
                                                           ((slaveCtl) == CY_SYSCLK_PERI_GROUP_SL_CTL3))
#else
#define CY_SYSCLK_IS_SL_CTL_NUM_VALID(slaveCtl)           (((slaveCtl) == CY_SYSCLK_PERI_GROUP_SL_CTL))

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) */

/** \endcond */


/**
* \addtogroup group_sysclk_clk_peripheral_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_PeriGroupSetDivider
****************************************************************************//**
*
* Sets the divider value for a particular group
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
* \note
* Clock divider functionality is product specific, Refer to TRM before using this API
* Example:-
* For CAT1B devices Group-0 does not have the clock divider functionality.
* For CAT1C devices Group-0,1 and 2 does not have the clock divider functionality.
* For the above not supported groups this API will return success, but write will
* not happen.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PeriGroupSetDivider(uint32_t groupNum, uint32_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriGroupGetDivider
****************************************************************************//**
*
* Gets the divider value for a particular group
*
* \return Divider value
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
* \note
* Clock divider functionality is product specific, Refer to TRM before using this API
* Example:-
* For CAT1B devices Group-0 does not have the clock divider functionality.
* For CAT1C devices Group-0,1 and 2 does not have the clock divider functionality.
* For the above not supported groups this API returns zero.
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriGroupGetDivider(uint32_t groupNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriGroupSetSlaveCtl
****************************************************************************//**
*
* Sets the particular Slave Control value for a particular group
*
* \return \ref cy_en_sysclk_status_t
*
* \param groupNum Selects the PERI Group Number
*
* \param slaveCtl Selects the Slave Control Register Number
*
* \param value Value to be written
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t Cy_SysClk_PeriGroupSetSlaveCtl(uint32_t groupNum, cy_en_peri_grp_sl_ctl_num_t slaveCtl, uint32_t value);

/*******************************************************************************
* Function Name: Cy_SysClk_PeriGroupGetSlaveCtl
****************************************************************************//**
*
* Gets the particular Slave Control value for a particular group
*
* \return Divider value
*
* \param groupNum Selects the PERI Group Number
*
* \param slaveCtl Selects the Slave Control Register Number
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriGroupGetSlaveCtl(uint32_t groupNum, cy_en_peri_grp_sl_ctl_num_t slaveCtl);

/*******************************************************************************
* Function Name: Cy_SysClk_IsPeriGroupSlaveCtlSet
****************************************************************************//**
*
* Gets the mask value of particular slave control register for a particular group
*
* \return Divider value
*
* \param groupNum Selects the PERI Group Number
*
* \param slaveCtl Selects the Slave Control Register Number
*
* \param slaveMsk Selects the bit position(s) that needs to be obtained
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
bool Cy_SysClk_IsPeriGroupSlaveCtlSet(uint32_t groupNum,cy_en_peri_grp_sl_ctl_num_t slaveCtl, uint32_t slaveMsk);


/** \} group_sysclk_clk_peripheral_funcs */
#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))  || defined (CY_IP_MXS22SRSS) */

/* ========================================================================== */
/* ========================    clk_peri SECTION    ========================== */
/* ========================================================================== */
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS)

/**
* \addtogroup group_sysclk_clk_peri_funcs
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPeriSetDivider
****************************************************************************//**
*
* Sets the clock divider for the peripheral clock tree. All peripheral clock
* dividers are sourced from this clock. Also the Cortex M0+ clock divider is
* sourced from this clock. The source of this divider is clkHf[0]
*
* \param divider divider value between 0 and 255
* Causes integer division of (divider value + 1), or division by 1 to 256.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPeriSetDivider
*
*******************************************************************************/
void Cy_SysClk_ClkPeriSetDivider(uint8_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPeriGetFrequency
****************************************************************************//**
*
* Reports the frequency of the peri clock.
*
* \return The frequency, in Hz.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPeriSetDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkPeriGetFrequency(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPeriGetDivider
****************************************************************************//**
*
* Returns the clock divider of the peripheral (peri) clock.
*
* \return The divider value.
* The integer division done is by (divider value + 1), or division by 1 to 256.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPeriSetDivider
*
*******************************************************************************/
uint8_t Cy_SysClk_ClkPeriGetDivider(void);
/** \} group_sysclk_clk_peri_funcs */

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS) */

/* ========================================================================== */
/* =====================    clk_peripherals SECTION    ====================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_peripheral_enums
* \{
*/
/** Programmable clock divider types */
typedef enum
{
    CY_SYSCLK_DIV_8_BIT    = 0U, /**< Divider Type is an 8 bit divider */
    CY_SYSCLK_DIV_16_BIT   = 1U, /**< Divider Type is a 16 bit divider */
    CY_SYSCLK_DIV_16_5_BIT = 2U, /**< Divider Type is a 16.5 bit fractional divider */
    CY_SYSCLK_DIV_24_5_BIT = 3U  /**< Divider Type is a 24.5 bit fractional divider */
} cy_en_divider_types_t;
/** \} group_sysclk_clk_peripheral_enums */


/**
* \addtogroup group_sysclk_clk_peripheral_funcs
* \{
*/
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkSetDivider
****************************************************************************//**
*
* Sets one of the programmable clock dividers. This is only used for integer
* dividers. Use \ref Cy_SysClk_PeriphSetFracDivider for setting factional dividers.
*
* \pre If the specified clock divider is already enabled - it should be disabled
* prior to use this function by \ref Cy_SysClk_PeriphDisableDivider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum the divider number.
*
* \param dividerValue divider value
* Causes integer division of (divider value + 1), or division by 1 to 256
* (8-bit divider) or 1 to 65536 (16-bit divider).
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkSetDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType,
                                           uint32_t dividerNum, uint32_t dividerValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkGetDivider
****************************************************************************//**
*
* Returns the integer divider value for the specified divider. One works for
* integer dividers. Use \ref Cy_SysClk_PeriphGetFracDivider to get the fractional
* divider value
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return The divider value.
* The integer division done is by (divider value + 1), or division by 1 to 256
* (8-bit divider) or 1 to 65536 (16-bit divider).
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriPclkGetDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkGetFracDivider
****************************************************************************//**
*
* Reports the integer and fractional parts of the divider
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \param *dividerIntValue pointer to return integer divider value
*
* \param *dividerFracValue pointer to return fractional divider value
*
* \return None. Loads pointed-to variables.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
void Cy_SysClk_PeriPclkGetFracDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                    uint32_t *dividerIntValue, uint32_t *dividerFracValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkSetFracDivider
****************************************************************************//**
*
* Sets one of the programmable clock dividers. This function should only be used
* for fractional clock dividers.
*
* \pre If the specified clock divider is already enabled - it should be disabled
* prior to use this function by \ref Cy_SysClk_PeriphDisableDivider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \param dividerIntValue the integer divider value
* The source of the divider is peri_clk, which is a divided version of hf_clk[0].
* The divider value causes integer division of (divider value + 1), or division
* by 1 to 65536 (16-bit divider) or 1 to 16777216 (24-bit divider).
*
* \param dividerFracValue the fraction part of the divider
* The fractional divider can be 1-32, thus it divides the clock by 1/32 for each
* count. To divide the clock by 11/32nds set this value to 11.
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkSetFracDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                               uint32_t dividerIntValue, uint32_t dividerFracValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkAssignDivider
****************************************************************************//**
*
* Assigns a programmable divider to a selected IP block, such as a TCPWM or SCB.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkAssignDivider(en_clk_dst_t ipBlock,
                                              cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkGetAssignedDivider
****************************************************************************//**
*
* Reports which clock divider is assigned to a selected IP block.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \return The divider type and number, where bits [7:6] = type, bits[5:0] = divider
* number within that type
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriPclkGetAssignedDivider(en_clk_dst_t ipBlock);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkEnableDivider
****************************************************************************//**
*
* Enables the selected divider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \note This function also sets the phase alignment bits such that the enabled
* divider is aligned to clk_peri. See \ref Cy_SysClk_PeriphDisableDivider()
* for information on how to phase-align a divider after it is enabled.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkEnableDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkDisableDivider
****************************************************************************//**
*
* Disables a selected divider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkDisableDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkEnablePhaseAlignDivider
****************************************************************************//**
*
* First disables a selected divider (\ref Cy_SysClk_PeriphDisableDivider),
* then aligns that divider to another programmable divider, and enables the
* selected divider. The divider to align to must already be enabled in order
* to align a divider to it.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \param dividerTypePA type of divider to phase-align to; \ref cy_en_divider_types_t.
*
* \param dividerNumPA divider number of type specified to phase align to.
*
* \note
* To phase-align a divider to clk_peri, set dividerTypePA to 3 and dividerNumPA
* to 63.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriPclkEnablePhaseAlignDivider(en_clk_dst_t ipBlock, cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                        cy_en_divider_types_t dividerTypePA, uint32_t dividerNumPA);

/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkGetFrequency
****************************************************************************//**
*
* Reports the frequency of the output of a given peripheral divider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return The frequency, in Hz.
*
* \note
* The reported frequency may be zero, which indicates unknown. This happens if
* the source input is dsi_out or clk_altlf.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphGetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriPclkGetFrequency(en_clk_dst_t ipBlock,
                                       cy_en_divider_types_t dividerType,
                                       uint32_t dividerNum);

/*******************************************************************************
* Function Name: Cy_SysClk_PeriPclkGetDividerEnabled
****************************************************************************//**
*
* Reports the enabled/disabled state of the selected divider.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
bool Cy_SysClk_PeriPclkGetDividerEnabled(en_clk_dst_t ipBlock,
                                             cy_en_divider_types_t dividerType,
                                             uint32_t dividerNum);

/*******************************************************************************
* Function Name: Cy_Sysclk_PeriPclkGetClkHfNum
****************************************************************************//**
*
* Reports the corresponding CLK_HF* number for a particular PERI PCLK group
*
* \param grpNum specifies group number of PERI PCLK block.
*
* \return The CLK_HF* number.
*
* \note
* This API is available for CAT1B, CAT1C and CAT1D devices.
*
*******************************************************************************/
uint32_t Cy_Sysclk_PeriPclkGetClkHfNum(uint32_t grpNum);

#endif

/*******************************************************************************
* Function Name: Cy_SysClk_PeriphSetDivider
****************************************************************************//**
*
* Sets one of the programmable clock dividers. This is only used for integer
* dividers. Use \ref Cy_SysClk_PeriphSetFracDivider for setting factional dividers.
*
* \pre If the specified clock divider is already enabled - it should be disabled
* prior to use this function by \ref Cy_SysClk_PeriphDisableDivider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum the divider number.
*
* \param dividerValue divider value
* Causes integer division of (divider value + 1), or division by 1 to 256
* (8-bit divider) or 1 to 65536 (16-bit divider).
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkSetDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphSetDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetDivider(cy_en_divider_types_t dividerType,
                                           uint32_t dividerNum, uint32_t dividerValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphGetDivider
****************************************************************************//**
*
* Returns the integer divider value for the specified divider. One works for
* integer dividers. Use \ref Cy_SysClk_PeriphGetFracDivider to get the fractional
* divider value
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return The divider value.
* The integer division done is by (divider value + 1), or division by 1 to 256
* (8-bit divider) or 1 to 65536 (16-bit divider).
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkGetDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphSetDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriphGetDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphSetFracDivider
****************************************************************************//**
*
* Sets one of the programmable clock dividers. This function should only be used
* for fractional clock dividers.
*
* \pre If the specified clock divider is already enabled - it should be disabled
* prior to use this function by \ref Cy_SysClk_PeriphDisableDivider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \param dividerIntValue the integer divider value
* The source of the divider is peri_clk, which is a divided version of hf_clk[0].
* The divider value causes integer division of (divider value + 1), or division
* by 1 to 65536 (16-bit divider) or 1 to 16777216 (24-bit divider).
*
* \param dividerFracValue the fraction part of the divider
* The fractional divider can be 1-32, thus it divides the clock by 1/32 for each
* count. To divide the clock by 11/32nds set this value to 11.
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkSetFracDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphSetFracDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphSetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                               uint32_t dividerIntValue, uint32_t dividerFracValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphGetFracDivider
****************************************************************************//**
*
* Reports the integer and fractional parts of the divider
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \param *dividerIntValue pointer to return integer divider value
*
* \param *dividerFracValue pointer to return fractional divider value
*
* \return None. Loads pointed-to variables.
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkGetFracDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphSetFracDivider
*
*******************************************************************************/
void Cy_SysClk_PeriphGetFracDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                    uint32_t *dividerIntValue, uint32_t *dividerFracValue);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphAssignDivider
****************************************************************************//**
*
* Assigns a programmable divider to a selected IP block, such as a TCPWM or SCB.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return \ref cy_en_sysclk_status_t
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkAssignDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphAssignDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphAssignDivider(en_clk_dst_t ipBlock,
                                              cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphGetAssignedDivider
****************************************************************************//**
*
* Reports which clock divider is assigned to a selected IP block.
*
* \param ipBlock specifies ip block to connect the clock divider to.
*
* \return The divider type and number, where bits [7:6] = type, bits[5:0] = divider
* number within that type
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkGetAssignedDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphAssignDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriphGetAssignedDivider(en_clk_dst_t ipBlock);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphEnableDivider
****************************************************************************//**
*
* Enables the selected divider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \note This function also sets the phase alignment bits such that the enabled
* divider is aligned to clk_peri. See \ref Cy_SysClk_PeriphDisableDivider()
* for information on how to phase-align a divider after it is enabled.
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkEnableDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphEnableDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphDisableDivider
****************************************************************************//**
*
* Disables a selected divider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkDisableDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphDisableDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphDisableDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphEnablePhaseAlignDivider
****************************************************************************//**
*
* First disables a selected divider (\ref Cy_SysClk_PeriphDisableDivider),
* then aligns that divider to another programmable divider, and enables the
* selected divider. The divider to align to must already be enabled in order
* to align a divider to it.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \param dividerTypePA type of divider to phase-align to; \ref cy_en_divider_types_t.
*
* \param dividerNumPA divider number of type specified to phase align to.
*
* \note
* To phase-align a divider to clk_peri, set dividerTypePA to 3 and dividerNumPA
* to 63.
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkEnablePhaseAlignDivider.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphEnablePhaseAlignDivider
*
*******************************************************************************/
cy_en_sysclk_status_t
                Cy_SysClk_PeriphEnablePhaseAlignDivider(cy_en_divider_types_t dividerType, uint32_t dividerNum,
                                                        cy_en_divider_types_t dividerTypePA, uint32_t dividerNumPA);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphGetDividerEnabled
****************************************************************************//**
*
* Reports the enabled/disabled state of the selected divider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t.
*
* \param dividerNum specifies which divider of the selected type to configure.
*
* \return The enabled/disabled state; \n
* false = disabled \n
* true = enabled
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkGetDividerEnabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphGetDividerEnabled
*
*******************************************************************************/
bool Cy_SysClk_PeriphGetDividerEnabled(cy_en_divider_types_t dividerType, uint32_t dividerNum);


/*******************************************************************************
* Function Name: Cy_SysClk_PeriphGetFrequency
****************************************************************************//**
*
* Reports the frequency of the output of a given peripheral divider.
*
* \param dividerType specifies which type of divider to use; \ref cy_en_divider_types_t
*
* \param dividerNum specifies which divider of the selected type to configure
*
* \return The frequency, in Hz.
*
* \note
* The reported frequency may be zero, which indicates unknown. This happens if
* the source input is dsi_out or clk_altlf.
*
* \note
* This API is deprecated for CAT1B, CAT1C and CAT1D devices, use Cy_SysClk_PeriPclkGetFrequency.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_PeriphGetFrequency
*
*******************************************************************************/
uint32_t Cy_SysClk_PeriphGetFrequency(cy_en_divider_types_t dividerType, uint32_t dividerNum);


/** \} group_sysclk_clk_peripheral_funcs */


/* ========================================================================== */
/* =========================    clk_slow SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_slow_funcs
* \{
*/

#if defined (CY_IP_MXS40SRSS)

/*******************************************************************************
* Function Name: Cy_SysClk_ClkSlowSetDivider
****************************************************************************//**
*
* Sets the clock divider for the slow clock.
*
* \param divider Divider value between 0 and 255.
* Causes integer division of (divider value + 1), or division by 1 to 256.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkSlowSetDivider
*
*******************************************************************************/
void Cy_SysClk_ClkSlowSetDivider(uint8_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkSlowGetDivider
****************************************************************************//**
*
* Reports the divider value for the slow clock.
*
* \return The divider value.
* The integer division done is by (divider value + 1), or division by 1 to 256.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkSlowSetDivider
*
*******************************************************************************/
uint8_t Cy_SysClk_ClkSlowGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkSlowGetFrequency
****************************************************************************//**
*
* Reports the frequency of the slow clock.
*
* \return The frequency, in Hz.
*
* \note
* This API is available for CAT1A & CAT1C devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkSlowSetDivider
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkSlowGetFrequency(void);

#endif

/** \} group_sysclk_clk_slow_funcs */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_DOXYGEN)

/* ========================================================================== */
/* =========================    clk_mem SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_mem_funcs
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysClk_ClkMemSetDivider
****************************************************************************//**
*
* Sets the clock divider for the Mem clock. The source of this clock is clkHf[0].
*
* \param divider Divider value between 0 and 255.
* Causes integer division of (divider value + 1), or division by 1 to 256.
*
* \note
* Call \ref SystemCoreClockUpdate after this function calling.
*
* \note
* This API is available for only CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkMemSetDivider(uint8_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMemGetDivider
****************************************************************************//**
*
* Reports the divider value for the Mem clock.
*
* \return The divider value.
* The integer division done is by (divider value + 1), or division by 1 to 256.
*
* \note
* This API is available for only CAT1C devices.
*
*******************************************************************************/
uint8_t Cy_SysClk_ClkMemGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkMemGetFrequency
****************************************************************************//**
*
* Reports the frequency of the Mem clock.
*
* \return The frequency, in Hz.
*
* \note
* This API is available for only CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkMemGetFrequency(void);

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

/** \} group_sysclk_clk_mem_funcs */

/* ========================================================================== */
/* ===========================    clkLf SECTION    ========================== */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_lf_enums
* \{
*/
/**
* Low frequency (clkLf) input sources. See CLK_SELECT register, LFCLK_SEL bits.
* Used with functions \ref Cy_SysClk_ClkLfSetSource, and \ref Cy_SysClk_ClkLfGetSource.
*/
#if defined (CY_IP_MXS22SRSS)
typedef enum
{
    CY_SYSCLK_CLKLF_IN_PILO              = 0U, /**< clkLf is sourced by the precision low speed oscillator (PILO) */
    CY_SYSCLK_CLKLF_IN_WCO               = 1U, /**< clkLf is sourced by the watch crystal oscillator (WCO) */
    CY_SYSCLK_CLKLF_IN_ALTLF             = 2U, /**< clkLf is sourced by the Alternate Low Frequency Clock (ALTLF) */
    CY_SYSCLK_CLKLF_IN_ECO_PRESCALER     = 3U, /**< clkLf is sourced by the External Clock Oscillator (ECO Prescaler) */
    CY_SYSCLK_CLKLF_IN_ILO               = 4U, /**< clkLf is sourced by the internal low speed oscillator (ILO) */
    CY_SYSCLK_CLKLF_IN_MAX               = 5U  /**< clkLf MAX value*/
} cy_en_clklf_in_sources_t;

#else
typedef enum
{
    CY_SYSCLK_CLKLF_IN_ILO               = 0U, /**< clkLf is sourced by the internal low speed oscillator (ILO) */
    CY_SYSCLK_CLKLF_IN_WCO               = 1U, /**< clkLf is sourced by the watch crystal oscillator (WCO) */
    CY_SYSCLK_CLKLF_IN_ALTLF             = 2U, /**< clkLf is sourced by the Alternate Low Frequency Clock (ALTLF) */
    CY_SYSCLK_CLKLF_IN_PILO              = 3U, /**< clkLf is sourced by the precision low speed oscillator (PILO) */
    CY_SYSCLK_CLKLF_IN_ILO1              = 4U, /**< clkLf is sourced by the internal low speed oscillator (ILO1)*/
    CY_SYSCLK_CLKLF_IN_ECO_PRESCALER     = 5U, /**< clkLf is sourced by the External Clock Oscillator (ECO Prescaler) */
    CY_SYSCLK_CLKLF_IN_LPECO_PRESCALER   = 6U, /**< clkLf is sourced by the External Clock Oscillator (LP ECO Prescaler) */
    CY_SYSCLK_CLKLF_IN_MAX               = 7U  /**< clkLf MAX value*/
} cy_en_clklf_in_sources_t;

#endif /* defined (CY_IP_MXS22SRSS) */

/** \} group_sysclk_clk_lf_enums */

/**
* \addtogroup group_sysclk_clk_lf_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ClkLfSetSource
****************************************************************************//**
*
* Sets the source for the low frequency clock(clkLf).
*
* \param source \ref cy_en_clklf_in_sources_t
*
* \note The watchdog timer (WDT) must be unlocked before calling this function.
*
* \note  It takes four cycles of the originally selected clock to switch away
* from it.  Do not disable the original clock during this time.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkLfSetSource
*
*******************************************************************************/
void Cy_SysClk_ClkLfSetSource(cy_en_clklf_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkLfGetSource
****************************************************************************//**
*
* Reports the source for the low frequency clock (clkLf).
*
* \return \ref cy_en_clklf_in_sources_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkLfSetSource
*
*******************************************************************************/
cy_en_clklf_in_sources_t Cy_SysClk_ClkLfGetSource(void);
/** \} group_sysclk_clk_lf_funcs */


/* ========================================================================== */
/* ========================    clk_timer SECTION    ========================= */
/* ========================================================================== */
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_DOXYGEN)

/**
* \addtogroup group_sysclk_clk_timer_enums
* \{
*/
/**
* Timer clock (clk_timer) input sources. See CLK_TIMER_CTL register, TIMER_SEL
* and TIMER_HF0_DIV bits. Used with functions \ref Cy_SysClk_ClkTimerSetSource, and
* \ref Cy_SysClk_ClkTimerGetSource.
*/
typedef enum
{
    CY_SYSCLK_CLKTIMER_IN_IMO       = 0x000U, /**< clk_timer is sourced by the internal main oscillator (IMO) */
    CY_SYSCLK_CLKTIMER_IN_HF0_NODIV = 0x001U, /**< clk_timer is sourced by clkHf[0] undivided */
    CY_SYSCLK_CLKTIMER_IN_HF0_DIV2  = 0x101U, /**< clk_timer is sourced by clkHf[0] divided by 2 */
    CY_SYSCLK_CLKTIMER_IN_HF0_DIV4  = 0x201U, /**< clk_timer is sourced by clkHf[0] divided by 4 */
    CY_SYSCLK_CLKTIMER_IN_HF0_DIV8  = 0x301U  /**< clk_timer is sourced by clkHf[0] divided by 8 */
} cy_en_clktimer_in_sources_t;
/** \} group_sysclk_clk_timer_enums */

/** \cond */
#define CY_SRSS_CLK_TIMER_CTL_TIMER_Pos (SRSS_CLK_TIMER_CTL_TIMER_SEL_Pos)
#define CY_SRSS_CLK_TIMER_CTL_TIMER_Msk (SRSS_CLK_TIMER_CTL_TIMER_SEL_Msk | SRSS_CLK_TIMER_CTL_TIMER_HF0_DIV_Msk)
/** \endcond */

/**
* \addtogroup group_sysclk_clk_timer_funcs
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerSetSource
****************************************************************************//**
*
* Sets the source for the timer clock (clk_timer). The timer clock can be used
* as a source for SYSTICK as an alternate clock and one or more of the energy
* profiler counters.
*
* \param source \ref cy_en_clktimer_in_sources_t
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerSetSource
*
*******************************************************************************/
void Cy_SysClk_ClkTimerSetSource(cy_en_clktimer_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerGetSource
****************************************************************************//**
*
* Reports the source for the timer clock (clk_timer).
*
* \return \ref cy_en_clktimer_in_sources_t
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerSetSource
*
*******************************************************************************/
cy_en_clktimer_in_sources_t Cy_SysClk_ClkTimerGetSource(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerSetDivider
****************************************************************************//**
*
* Sets the divider for the timer clock (clk_timer).
*
* \param divider Divider value; valid range is 0 to 255. Divides the selected
* source (\ref Cy_SysClk_ClkTimerSetSource) by the (value + 1).
*
* \note
* Do not change the divider value while the timer clock is enabled.
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerSetDivider
*
*******************************************************************************/
void Cy_SysClk_ClkTimerSetDivider(uint8_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerGetDivider
****************************************************************************//**
*
* Reports the divider value for the timer clock (clk_timer).
*
* \return The divider value
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerSetDivider
*
*******************************************************************************/
uint8_t Cy_SysClk_ClkTimerGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerEnable
****************************************************************************//**
*
* Enables the timer clock (clk_timer). The timer clock can be used as a source
* for SYSTICK and one or more of the energy profiler counters.
*
* \note
* This API is available for CAT1A devices.
*
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerEnable
*
*******************************************************************************/
void Cy_SysClk_ClkTimerEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerDisable
****************************************************************************//**
*
* Disables the timer clock (clk_timer).
*
* \note
* This API is available for CAT1A devices.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerDisable
*
*******************************************************************************/
void Cy_SysClk_ClkTimerDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of the Timer.
*
* \return Boolean status of Timer: true - Enabled, false - Disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerDisable
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
bool Cy_SysClk_ClkTimerIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkTimerGetFrequency
****************************************************************************//**
*
* Reports the frequency of the timer clock (clk_timer).
* \note If the the timer clock is not enabled - a zero frequency is reported.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkTimerEnable
*
* \note
* This API is available for CAT1A devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkTimerGetFrequency(void);

#endif /*(defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) */


/** \} group_sysclk_clk_timer_funcs */


#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS)
/* ========================================================================== */
/* =========================    clk_pump SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_pump_enums
* \{
*/

/**
* Pump clock (clk_pump) input sources. See CLK_SELECT register, PUMP_SEL bits.
* Used with functions \ref Cy_SysClk_ClkPumpSetSource, and
* \ref Cy_SysClk_ClkPumpGetSource.
*/
/**
* \note
* This enum is available for CAT1A, CAT1B and CAT1C devices.
**/
typedef enum
{
    CY_SYSCLK_PUMP_IN_CLKPATH0  = 0UL,  /**< Pump clock input is clock path 0 */
    CY_SYSCLK_PUMP_IN_CLKPATH1  = 1UL,  /**< Pump clock input is clock path 1 */
    CY_SYSCLK_PUMP_IN_CLKPATH2  = 2UL,  /**< Pump clock input is clock path 2 */
    CY_SYSCLK_PUMP_IN_CLKPATH3  = 3UL,  /**< Pump clock input is clock path 3 */
    CY_SYSCLK_PUMP_IN_CLKPATH4  = 4UL,  /**< Pump clock input is clock path 4 */
    CY_SYSCLK_PUMP_IN_CLKPATH5  = 5UL,  /**< Pump clock input is clock path 5 */
    CY_SYSCLK_PUMP_IN_CLKPATH6  = 6UL,  /**< Pump clock input is clock path 6 */
    CY_SYSCLK_PUMP_IN_CLKPATH7  = 7UL,  /**< Pump clock input is clock path 7 */
    CY_SYSCLK_PUMP_IN_CLKPATH8  = 8UL,  /**< Pump clock input is clock path 8 */
    CY_SYSCLK_PUMP_IN_CLKPATH9  = 9UL,  /**< Pump clock input is clock path 9 */
    CY_SYSCLK_PUMP_IN_CLKPATH10 = 10UL, /**< Pump clock input is clock path 10 */
    CY_SYSCLK_PUMP_IN_CLKPATH11 = 11UL, /**< Pump clock input is clock path 11 */
    CY_SYSCLK_PUMP_IN_CLKPATH12 = 12UL, /**< Pump clock input is clock path 12 */
    CY_SYSCLK_PUMP_IN_CLKPATH13 = 13UL, /**< Pump clock input is clock path 13 */
    CY_SYSCLK_PUMP_IN_CLKPATH14 = 14UL, /**< Pump clock input is clock path 14 */
    CY_SYSCLK_PUMP_IN_CLKPATH15 = 15UL  /**< Pump clock input is clock path 15 */
} cy_en_clkpump_in_sources_t;

/**
* Pump clock (clk_pump) divide options. See CLK_SELECT register, PUMP_DIV bits.
* Used with functions \ref Cy_SysClk_ClkPumpSetDivider, and
* \ref Cy_SysClk_ClkPumpGetDivider.
*/
/**
* \note
* This enum is available for CAT1A, CAT1B and CAT1C devices.
**/
typedef enum
{
    CY_SYSCLK_PUMP_NO_DIV = 0U, /**< No division on pump clock */
    CY_SYSCLK_PUMP_DIV_2  = 1U, /**< Pump clock divided by 2 */
    CY_SYSCLK_PUMP_DIV_4  = 2U, /**< Pump clock divided by 4 */
    CY_SYSCLK_PUMP_DIV_8  = 3U, /**< Pump clock divided by 8 */
    CY_SYSCLK_PUMP_DIV_16 = 4U  /**< Pump clock divided by 16 */
} cy_en_clkpump_divide_t;
/** \} group_sysclk_clk_pump_enums */

/** \cond */
#define  CY_SYSCLK_FLL_IS_DIVIDER_VALID(div) (((div) == CY_SYSCLK_PUMP_NO_DIV) || \
                                              ((div) == CY_SYSCLK_PUMP_DIV_2)  || \
                                              ((div) == CY_SYSCLK_PUMP_DIV_4)  || \
                                              ((div) == CY_SYSCLK_PUMP_DIV_8)  || \
                                              ((div) == CY_SYSCLK_PUMP_DIV_16))
/** \endcond */

/**
* \addtogroup group_sysclk_clk_pump_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpSetSource
****************************************************************************//**
*
* Sets the source for the pump clock (clk_pump). The pump clock can be used for
* the analog pumps in the CTBm block.
*
* \param source \ref cy_en_clkpump_in_sources_t
*
* \note
* Do not change the source while the pump clock is enabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpSetSource
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkPumpSetSource(cy_en_clkpump_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpGetSource
****************************************************************************//**
*
* Reports the source for the pump clock (clk_pump).
*
* \return \ref cy_en_clkpump_in_sources_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpSetSource
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
cy_en_clkpump_in_sources_t Cy_SysClk_ClkPumpGetSource(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpSetDivider
****************************************************************************//**
*
* Sets the divider of the pump clock (clk_pump).
*
* \param divider \ref cy_en_clkpump_divide_t
*
* \note
* Do not change the divider value while the pump clock is enabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpSetDivider
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkPumpSetDivider(cy_en_clkpump_divide_t divider);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpGetDivider
****************************************************************************//**
*
* Reports the divider value for the pump clock (clk_pump).
*
* \return \ref cy_en_clkpump_divide_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpSetDivider
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
cy_en_clkpump_divide_t Cy_SysClk_ClkPumpGetDivider(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpEnable
****************************************************************************//**
*
* Enables the pump clock (clk_pump). The pump clock can be used for the analog
* pumps in the CTBm block.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpEnable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkPumpEnable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpIsEnabled
****************************************************************************//**
*
* Reports the Enabled/Disabled status of the ClkPump.
*
* \return Boolean status of ClkPump: true - Enabled, false - Disabled.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpDisable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
bool Cy_SysClk_ClkPumpIsEnabled(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpDisable
****************************************************************************//**
*
* Disables the pump clock (clk_pump).
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpDisable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
void Cy_SysClk_ClkPumpDisable(void);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkPumpGetFrequency
****************************************************************************//**
*
* Reports the frequency of the pump clock (clk_pump).
* \note If the the pump clock is not enabled - a zero frequency is reported.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkPumpEnable
*
* \note
* This API is available for CAT1A, CAT1B and CAT1C devices.
*
*******************************************************************************/
uint32_t Cy_SysClk_ClkPumpGetFrequency(void);
/** \} group_sysclk_clk_pump_funcs */
#endif /* defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) */

/* ========================================================================== */
/* ==========================    clk_bak SECTION    ========================= */
/* ========================================================================== */
/**
* \addtogroup group_sysclk_clk_bak_enums
* \{
*/
/**
* Backup domain clock (clk_bak) input sources. See BACKUP->CTL register,
* CLK_SEL bits. Used with functions \ref Cy_SysClk_ClkBakSetSource, and
* \ref Cy_SysClk_ClkBakGetSource.
*/
typedef enum
{
    CY_SYSCLK_BAK_IN_WCO,   /**< Backup domain clock input is WCO */
    CY_SYSCLK_BAK_IN_CLKLF,  /**< Backup domain clock input is clkLf */
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) || defined (CY_IP_MXS22SRSS)
    /**
    * \note
    * This parameter is available for CAT1B and CAT1C devices.
    **/
    CY_SYSCLK_BAK_IN_ILO,               /**< Backup domain clock input is ILO */
    /**
    * \note
    * This parameter is available for CAT1B devices.
    **/
    CY_SYSCLK_BAK_IN_LPECO_PRESCALER,   /**< Backup domain clock input is LPECO_PRESCALER  */
    /**
    * \note
    * This parameter is available for CAT1B devices.
    **/
    CY_SYSCLK_BAK_IN_PILO               /**< Backup domain clock input is PILO */
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS  */

} cy_en_clkbak_in_sources_t;
/** \} group_sysclk_clk_bak_enums */


/**
* \addtogroup group_sysclk_clk_bak_funcs
* \{
*/
/*******************************************************************************
* Function Name: Cy_SysClk_ClkBakSetSource
****************************************************************************//**
*
* Sets the source for the backup domain clock (clk_bak).
*
* \param source \ref cy_en_clkbak_in_sources_t
*
* \note
* clkLf is not available in all power modes.  For this reason, WCO is the
* preferred source. If the WCO is routed through the clkLf multiplexer
* (see \ref Cy_SysClk_ClkLfSetSource), select WCO directly - do not select clkLf.
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkBakSetSource
*
*******************************************************************************/
void Cy_SysClk_ClkBakSetSource(cy_en_clkbak_in_sources_t source);


/*******************************************************************************
* Function Name: Cy_SysClk_ClkBakGetSource
****************************************************************************//**
*
* Reports the source for the backup domain clock (clk_bak).
*
* \return \ref cy_en_clkbak_in_sources_t
*
* \funcusage
* \snippet sysclk/snippet/main.c snippet_Cy_SysClk_ClkBakSetSource
*
*******************************************************************************/
cy_en_clkbak_in_sources_t Cy_SysClk_ClkBakGetSource(void);
/** \} group_sysclk_clk_bak_funcs */


/** \cond */
/* Deprecated macros */
#define CY_SYSCLK_DIV_ROUND(a, b)   (CY_SYSLIB_DIV_ROUND((a),(b)))
#define CY_SYSCLK_DIV_ROUNDUP(a, b) (CY_SYSLIB_DIV_ROUNDUP((a),(b)))
/** \endcond */


#if defined(__cplusplus)
}
#endif /* __cplusplus */

#endif /* defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) */

#endif /* CY_SYSCLK_H */

/** \} group_sysclk */


/* [] END OF FILE */
