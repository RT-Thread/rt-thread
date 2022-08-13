/***************************************************************************//**
* \file cy_csdidac.h
* \version 2.10
*
* \brief
* This file provides the function prototypes and constants specific
* to the CSDIDAC middleware.
*
********************************************************************************
* \copyright
* Copyright 2019-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
/**
* \mainpage CSDIDAC Middleware Library
*
* The CSDIDAC middleware is the IDAC solution that uses the
* CSD HW block. Any GPIO that can be connected to AMUX-A/B (refer to the
* particular device datasheet for information) can be an CSDIDAC output
* under software control.
* The CSD HW block is mainly used to implement the touch sense applications and
* proximity sensors (refer to the
* <a href="https://cypresssemiconductorco.github.io/capsense/capsense_api_reference_manual/html/index.html">
* <b>CapSense Middleware API Reference Guide</b></a>), but can also
* be used to implement the IDAC, which is especially useful for the devices that
* do not include another hardware option to implement IDAC.
*
* <b>Features:</b>
* * A two-channel IDAC with the 7-bit resolution.
* * The IDAC A and IDAC B channels can be enabled/disabled independently.
* * The IDAC A and IDAC B channels can be configured with sourcing/sinking
*   current independently.
* * The IDAC A and IDAC B channels can be joined to increase a maximum output
*   current.
* * The IDAC A and IDAC B channels can be enabled/disabled simultaneously
*   by using the CY_CSDIDAC_AB option.
* * The 0 to 609.6 uA (609600 nA) current range is available for each IDAC
*   channel.
* * Each IDAC can use independently one of the six available LSB depending
*   on a desired output current:
*
* <table class="doxtable">
*   <tr><th>LSB Index</th><th>LSB</th><th>Available Current Range</th></tr>
*   <tr>
*     <td>0</td>
*     <td>37.5 nA</td>
*     <td>0 to 4762.5 nA</td>
*   </tr>
*   <tr>
*     <td>1</td>
*     <td>75.0 nA</td>
*     <td>0 to 9525.0 nA</td>
*   </tr>
*   <tr>
*     <td>2</td>
*     <td>0.3 uA</td>
*     <td>0 to  38.1 uA</td>
*   </tr>
*   <tr>
*     <td>3</td>
*     <td>0.6 uA</td>
*     <td>0 to  76.2 uA</td>
*   </tr>
*   <tr>
*     <td>4</td>
*     <td>2.4 uA</td>
*     <td>0 to 304.8 uA</td>
*   </tr>
*   <tr>
*     <td>5</td>
*     <td>4.8 uA</td>
*     <td>0 to 609.6 uA</td>
*   </tr>
* </table>
*
********************************************************************************
* \section section_csdidac_general General Description
********************************************************************************
*
* Include cy_csdidac.h to get access to all functions and other declarations in
* this library.
* The \ref section_csdidac_quick_start is offered in this API Reference Guide.
*
* Refer to the \ref section_csdidac_toolchain for the compatibility
* information.
*
* Refer to the \ref group_csdidac_changelog for the differences between the
* middleware versions.
* \ref group_csdidac_changelog also describes the impact of changes to
* your code.
*
* The CSD HW block enables the multiple sensing capabilities on PSoC devices
* including the self-cap and mutual-cap capacitive touch sensing solution,
* 10-bit ADC, IDAC, and Comparator. The CSD driver is a low-level
* peripheral driver, a wrapper to manage access to the CSD HW block.
* Any middleware access to the CSD HW block is through the CSD Driver.
*
* The CSD HW block can support only one function at a time. However, all
* supported functionality (like CapSense, CSDADC, CSDIDAC, etc.) can be
* time-multiplexed in a design. I.e. you can save the existing state
* of the CapSense middleware, restore the state of the CSDIDAC middleware,
* perform DAC operations, and then switch back to the CapSense functionality.
* For more details and code examples, refer to the description of the
* Cy_CSDIDAC_Save() and Cy_CSDIDAC_Restore() functions.
*
* \image html capsense_solution.png "CapSense Solution" width=800px
* \image latex capsense_solution.png
*
* This section describes only the CSDIDAC middleware. Refer to the corresponding
* sections for documentation of other middleware supported by the CSD HW block.
* The CSDIDAC library is designed to be used with the CSD driver.
* The application program does not need to interact with the CSD driver
* and/or other drivers such as GPIO or SysClk directly. All of that is
* configured and managed by the middleware.
*
* The Cy_CSDIDAC API is described in the following sections:
* * \ref group_csdidac_macros
* * \ref group_csdidac_data_structures
* * \ref group_csdidac_enums
* * \ref group_csdidac_functions
*
********************************************************************************
* \section section_csdidac_quick_start Quick Start Guide
********************************************************************************
*
* The CSDIDAC middleware can be used in various Development Environments
* such as ModusToolbox, MBED, etc. Refer to the \ref section_csdidac_toolchain.
* The quickest way to get started is using the Code Examples.
* The continually expanding portfolio of the code examples is available
* at the <a href="http://www.cypress.com"><b>Cypress Semiconductor website</b></a>
* and on <a href="https://github.com/cypresssemiconductorco">
* <b>GitHub</b></a>.
*
* This quick start guide assumes that the environment is configured to use the
* PSoC 6 Peripheral Driver Library(psoc6pdl) for development and the
* PSoC 6 Peripheral Driver Library(psoc6pdl) is included in the project.
*
* The steps required to set up the CSDIDAC and get the
* desired current:
*
* 1. Set up the CSDIDAC configuration manually or by using the Device Configurator
*    as described in the \ref section_csdidac_configuration section.
* \note
* Put the CSDIDAC name to the Alias field of the CSD resource if the
* Device Configurator is used.
*
* 2. Include cy_csdidac.h to get access to all CSDIDAC API and cy_pdl.h to get
*    access to API of peripheral drivers according to the example below:
* \snippet csdidac/snippet/main.c snippet_required_includes
* 3. If you use the MBED OS, include the cycfg.h file to get access to the
*    System Configuration:
* \snippet csdidac/snippet/main.c snippet_mbed_required_includes
* 4. Declare the 'cy_csdidac_context' variable as per example below:
* \snippet csdidac/snippet/main.c snippet_csdidac_context_declaration
* 5. Update the main() routine with the following code:
* \snippet csdidac/snippet/main.c snippet_Cy_CSDIDAC_Usage
*
********************************************************************************
* \section section_csdidac_configuration Configuration Considerations
********************************************************************************
*
* The CSDIDAC middleware operates on the top of the CSD Driver included in the
* PSoC 6 Peripheral Driver Library (psoc6pdl). Refer to the "CSD(CapSense
* Sigma Delta)" section of the PSoC 6 Peripheral Driver Library (psoc6pdl) API
* Reference Manual.
* This section guides how to set up the CSDIDAC middleware for the operation
* with the following parameters:
* 1. Device VDDA: 3.3V.
* 2. Device Peri Clock frequency: 48MHz.
* 3. IDAC A is sourcing current of 50 uA to GPIO pin P0[4].
* 4. IDAC B is sinking current of 0.5uA from GPIO pin P0[5].
*
* There are two methods for the CSDIDAC Middleware configuration:
* 1. \ref subsection_csdidac_mtb_configuring
* 2. \ref subsection_csdidac_manual_configuring
*
* Generation of the initialization code using the
* <a href="https://www.cypress.com/ModusToolboxDeviceConfig">
* <b>ModusToolbox Device Configurator Tool </b></a> which is part of the
* <a href="https://www.cypress.com/products/modustoolbox-software-environment">
* <b>ModusToolbox</b></a>, greatly simplifies the PSoC configuration.
* The <a href="https://www.cypress.com/ModusToolboxDeviceConfig"><b>ModusToolbox
* Device Configurator Tool </b></a> provides the user interface to set up and
* automatically generate the initialization code (including analog routing) and
* configuration structures.
*
* Manual implementation of the initialization code (including analog routing)
* and configuration structures is recommended for expert Users only. This will
* include the code for the following settings which in case of the
* Device Configurator usage are generated automatically based upon the settings
* entered in its UI:
*  * Assigning the Peripheral Clock Divider.
*  * Configuring the HSIOM_AMUX_SPLIT_CTL switches to route signal from input
*    pins configured as the CSDIDAC channels to the CSD HW block.
*  * Declaration and initialization of the CSDIDAC configuration structure.
*  * Declaration and initialization of the CSD HW driver context structure.
*  * Definition of the of the CSD HW block base address.
*
********************************************************************************
* \subsection subsection_csdidac_mtb_configuring Use ModusToolbox Device Configurator Tool to generate initialization code
********************************************************************************
*
* The steps required to generate the initialization code using the
* <a href="https://www.cypress.com/ModusToolboxDeviceConfig">
* <b>ModusToolbox Device Configurator Tool </b></a>:
* 1. Launch the ModusToolbox Middleware Selector and enable the CSD IDAC
*    middleware. This step is required only if the ModusToolbox IDE is used.
*    Otherwise, ensure the CSDIDAC Middleware is included in your project.
* 2. Launch the ModusToolbox Device Configurator Tool.
* 3. Switch to the System tab. Configure the CLK_PERI frequency to achieve 48MHz
*    (you may need to change the FLL or PLL frequency) and set the VDDA voltage
*    to 3.3V in Power/MCU Personality.
* 4. Switch to the Peripherals tab (#1 in the figure below). Enable the
*    CSD personality under System (#2 in the figure below) and
*    enter Alias (#3 in the figure below). We use CSDIDAC in
*    \ref section_csdidac_quick_start.
* 5. Go to the Parameters pane and configure the CSD Personality:
*  * Assign the peripheral clock divider by using the Clock
*    combo box(#4 in the figure below). Any free divider can be used.
*  * Set the Enable CSDIDAC check box (#5 in the figure below).
*  * Configure the CSDIDAC with the desired parameters per
*    \ref section_csdidac_configuration (#5 in the figure below).
*  * Assign the CSDIDAC Channels to pins per \ref section_csdidac_configuration
*    (#6 in the figure below).
* 6. Switch to the Peripheral Clocks tab and configure the assigned peripheral
*    clock divider. The Max supported clock frequency for the CSD HW block
*    is 50 MHz. The divider value "1" can be used, because in the current case the
*    Peri Clock frequency is 48 MHz.
* 7. Perform File->Save to generate the initialization code.
*
* \image html csdidac_config.png "CSDIDAC configuration" width=1172px
* \image latex csdidac_config.png
*
* Now, all required CSDIDAC initialization code and configuration prerequisites
* will be generated:
* * The Peripheral Clock Divider assignment and analog routing are parts of
*   the init_cycfg_all() routine. Place the call of the init_cycfg_all() function
*   before using any CSDIDAC API functions to ensure initialization of all
*   external resources required for the CSDIDAC operation.
*   Refer to the main() routine code snippet in
*   \ref section_csdidac_quick_start
* * The CSDIDAC configuration structure declaration in the
*   cycfg_peripherals.h file and its initialization in the
*   cycfg_peripherals.c file. The variable name is
*   \<Alias_Name\>_csdidac_config.
* * The CSD HW driver context structure declaration in the
*   cycfg_peripherals.h file and its initialization in the
*   cycfg_peripherals.c file. The variable name is
*   cy_csd_\<CSD_Block_Index\>_context.
* * The CSD HW block base address definition is in the
*   cycfg_peripherals.h file. The definition name is \<Alias_Name\>_HW.
*
* The generated code will be available under the GeneratedSource folder.
*
* Refer to \ref section_csdidac_quick_start section for the application layer
* code required to set up the CSDIDAC and to get the desired current on the
* assigned pin.
*
********************************************************************************
* \subsection subsection_csdidac_manual_configuring Implement the initialization code manually
********************************************************************************
*
* The steps required to implement the initialization code manually:
* 1. Launch the ModusToolbox Middleware Selector and enable the
*    CSD IDAC middleware. This step is required only if the ModusToolbox IDE
*    is used.
*    Otherwise, ensure the CSDIDAC Middleware is included in your project.
* 2. Define the CSD HW block base address. See the code example below:
* \snippet csdidac/snippet/main.c snippet_csd_hw_definition
* 3. Declare the CSD HW driver context structure and initialize the
*    lockKey field with the CY_CSD_NONE_KEY value. See the code example below:
* \snippet csdidac/snippet/main.c snippet_csd_context_declaration
* 4. Declare the CSDIDAC configuration structure and initialize it according
*    to the desired parameters. See the code example below:
* \snippet csdidac/snippet/main.c snippet_csdidac_config_declaration
* 5. Assign the Peripheral Clock Divider to the CSD HW block and configure
*    the divider value.
*    See the code example below and refer to the main() routine code snippet in
*    \ref section_csdidac_quick_start
* \snippet csdidac/snippet/main.c snippet_Cy_CSDIDAC_Clock_Assignment
* 6. Set the configuration of the HSIOM_AMUX_SPLIT_CTL switches to route signal
*    from CSD HW block to the pins configured as the CSDIDAC output channels.
*
*    The AMUX bus has segments that are separated with the HSIOM_AMUX_SPLIT_CTL switches.
*    The code below closes the AMUX_SPLIT_CTL switches, which route the IDAC output
*    signal from the CSD block to the pin. In this example, IDAC output channels
*    are assigned to the P0[4] and P[5] pins. The AMUX_SPLIT_CTL[5] and AMUX_SPLIT_CTL[6]
*    switches must be closed in the PSoC6 device. The P0[4] and P[5] pins in the
*    PSoC4 device belong to the AMUX bus segment, which is connected to the CSD block
*    directly. In this case, the AMUX_SPLIT_CTL switches are not closed.
*    Refer to the
*    <a href="http://www.cypress.com/trm218176"><b>Technical Reference Manual
*    (TRM)</b></a> for more information regarding the analog interconnection.
*    See the code example below and refer to the main() routine code snippet in
*    \ref section_csdidac_quick_start
* \snippet csdidac/snippet/main.c snippet_Cy_CSDIDAC_Amux_Configuration
* \note
* If you use a KIT, check on the schematics, if pins P0[4] and P0[5] are
* free. If not, use some other pins and update the AMUX_SPLIT_CTL registers.
* \note
* Some CSDIDAC configurations are restricted. The CSD personality has a
* mechanism to prevent writing an invalid configuration. If CSDIDAC is manually
* created, avoid the following combinations:
*  * both IDAC channels are disabled
*  * one IDAC channel is disabled and another channel is joined to it
*  * the IDAC A channel and IDAC B channel are joined to each other
*
* Refer to \ref section_csdidac_quick_start section for the application layer
* code required to set up the CSDIDAC and to get the desired current on the
* assigned pin.
*
********************************************************************************
* \section group_csdadc_use_cases Use Cases
********************************************************************************
*
* This section provides descriptions and links to additional documentation for
* some specific CSDIDAC use cases.
*
********************************************************************************
* \subsection group_csdidac_low_power_design Low power design
********************************************************************************
* The CSD HW block and CSDIDAC middleware can operate in CPU active and
* CPU sleep power modes. It is also
* possible to switch between low power and ultra low power system modes.
* In System Deep Sleep and Hibernate power modes, the CSD HW block is powered off and
* CSDIDAC operations are not performed. Before entering CPU / System Deep Sleep,
* disable CSDIDAC output current generation. If output
* currents are not disabled, a CPU Deep Sleep transition will fail.
* When the device wakes up from CPU / System Deep Sleep, the CSD HW block resumes operation
* without the need for re-initialization and the CSDIDAC operations can be
* continued with configuration that was set before a CPU / System Deep Sleep transition.
* When the device wakes up from Hibernate power mode, the CSD HW block
* does not retain the configuration and CSDIDAC requires re-initialization.
*
* \note
* 1. Analog start up time for the CSD HW block is 25 us for PSoC6 devices and
*    10 us for PSoC4 devices. Initiate any kind of operation only after 25 us
*    for PSoC6 devices and 10 us for PSoC4 devices from System Deep Sleep / Hibernate exit.
*
* 2. Entering CPU Deep Sleep mode does not mean the device enters
*    System Deep Sleep. For more detail about switching to System Deep Sleep,
*    refer to the device TRM.
*
* Refer to the Cy_CSDIDAC_DeepSleepCallback() function description and to the
* SysPm (System Power Management) driver documentation for the low power design
* considerations.
*
* <b>Sleep mode</b><br>
* The CSD HW block can operate in CPU sleep mode. The user can start CSDIDAC
* and move CPU into sleep mode to reduce power consumption. After wake-up CPU
* from sleep, the user can perform other operations, e.g. disable IDACs.
* Then, the user configures the CSDIDAC middleware as described in
* \ref section_csdidac_configuration, and updates the main() routine with
* the following code:
* \snippet csdidac/snippet/main.c snippet_Cy_CSDIDAC_Sleep
*
* <b>Deep Sleep mode</b><br>
* To use the CSDIDAC middleware in CPU / System Deep Sleep mode, the user configures
* a wake-up source (e.g. a pin, WDT, LPC or another entities, that are active
* in CPU / System Deep Sleep mode), configures the CSDIDAC middleware as described in
* \ref section_csdidac_configuration, configures CSDIDAC and other drivers' and
* middleware's (if present) Deep Sleep Callback structures, registers
* callbacks, and updates the main() routine with the following code:
* \snippet csdidac/snippet/main.c snippet_CSDIDAC_DeepSleep_structures
* \snippet csdidac/snippet/main.c snippet_Cy_CSDIDAC_DeepSleep
*
********************************************************************************
* \subsection group_csdidac_time_multiplexing Time-multiplexing operation
********************************************************************************
* Refer to the <a href="https://cypresssemiconductorco.github.io/capsense/capsense_api_reference_manual/html/index.html">
* <b>CapSense Middleware API Reference Guide</b></a> for implementation of the
* time-multiplexing operation by using common CSD HW block.
*
********************************************************************************
* \section section_csdidac_toolchain Supported Software and Tools
********************************************************************************
*
* This version of the CSDIDAC Middleware was validated for compatibility
* with the following Software and Tools:
*
* <table class="doxtable">
*   <tr>
*     <th>Software and Tools</th>
*     <th>Version</th>
*   </tr>
*   <tr>
*     <td>ModusToolbox Software Environment</td>
*     <td>2.1</td>
*   </tr>
*   <tr>
*     <td>- ModusToolbox Device Configurator</td>
*     <td>2.1</td>
*   </tr>
*   <tr>
*     <td>- ModusToolbox CSD Personality for PSoC4 devices in Device Configurator</td>
*     <td>1.0</td>
*   </tr>
*   <tr>
*     <td>- ModusToolbox CSD Personality for PSoC6 devices in Device Configurator</td>
*     <td>2.0</td>
*   </tr>
*   <tr>
*     <td>PSoC4 Peripheral Driver Library (PDL)</td>
*     <td>1.0.0</td>
*   </tr>
*   <tr>
*     <td>PSoC6 Peripheral Driver Library (PDL)</td>
*     <td>1.5.0</td>
*   </tr>
*   <tr>
*     <td>GCC Compiler</td>
*     <td>7.2.1</td>
*   </tr>
*   <tr>
*     <td>IAR Compiler</td>
*     <td>8.32</td>
*   </tr>
*   <tr>
*     <td>Arm Compiler 6</td>
*     <td>6.11</td>
*   </tr>
*   <tr>
*     <td>MBED OS (only for PSoC6)</td>
*     <td>5.15.1</td>
*   </tr>
*   <tr>
*     <td>FreeRTOS</td>
*     <td>10.0.1</td>
*   </tr>
* </table>
*
********************************************************************************
* \section section_csdidac_update Update to Newer Versions
********************************************************************************
* Consult \ref group_csdidac_changelog to learn about the design impact of the
* newer version. Set up your environment in accordance with
* \ref section_csdidac_toolchain. You might need to re-generate the configuration
* structures for either the device initialization code or the middleware
* initialization code.
*
* Ensure:
* * The specified version of the ModusToolbox Device Configurator and
*   the CSD personality are used to re-generate the device configuration.
* * The toolchains are set up properly for your environment per the settings
*   outlined in the Supported Software and Tools.
* * The project is re-built once the the toolchains are configured and the
*   configuration is completed.
*
********************************************************************************
* \section group_csdidac_MISRA MISRA-C Compliance
********************************************************************************
*
* The Cy_CSDIDAC library has the following specific deviations:
*
* <table class="doxtable">
*   <tr>
*     <th>MISRA Rule</th>
*     <th>Rule Class (Required/Advisory)</th>
*     <th>Rule Description</th>
*     <th>Description of Deviation(s)</th>
*   </tr>
*   <tr>
*     <td>11.4</td>
*     <td>A</td>
*     <td>Do not perform a conversion between the pointer to an object
*         and an integer type.</td>
*     <td>Such a conversion is performed with CSDIDAC context
*         in the DeepSleepCallback() function.
*         This case is verified on correct operation.</td>
*   </tr>
*   <tr>
*     <td>1.2</td>
*     <td rowspan=2> R</td>
*     <td rowspan=2> Constant: De-reference of the NULL pointer.</td>
*     <td rowspan=2> These violations are reported as a result of using
*         offset macros of the CSD Driver with corresponding documented
*         violation 20.6. Refer to the CSD Driver API Reference Guide.</td>
*   </tr>
*   <tr>
*     <td>20.3</td>
*   </tr>
* </table>
*
********************************************************************************
* \section group_csdidac_changelog Changelog
********************************************************************************
*
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td rowspan="2">2.10</td>
*     <td>Added the support of PSoC 4 CapSense Forth Generation devices</td>
*     <td>Devices support</td>
*   </tr>
*   <tr>
*     <td>Minor documentation update</td>
*     <td>Documentation cleanup</td>
*   </tr>
*   <tr>
*     <td rowspan="5">2.0</td>
*     <td>The joining two IDAC channels option is added to increase
*         the maximum CSDIDAC output current </td>
*     <td>Feature enchancement</td>
*   </tr>
*   <tr>
*     <td>The cy_stc_csdidac_config_t structure is changed: the periClk field
*         replaced with cpuClk, busOnlyA and busOnlyB fields replaced with
*         configA and configB fields respectively, the field order is changed.
*         The \ref cy_en_csdidac_channel_config_t enumeration type is added.</td>
*     <td>User experience improvement</td>
*   </tr>
*   <tr>
*     <td>The \ref CY_CSDIDAC_HW_FAILURE  and
*         the \ref CY_CSDIDAC_BAD_CONFIGURATION return status cases are added
*         to the \ref cy_en_csdidac_status_t enumeration type</td>
*     <td>User experience improvement</td>
*   </tr>
*   <tr>
*     <td>The \ref CY_CSDIDAC_AB choosing case for both IDACs is added
*         to the \ref cy_en_csdidac_choice_t enumeration type</td>
*     <td>Feature enchancement</td>
*   </tr>
*   <tr>
*     <td>The CSDIDAC MW sources are enclosed with the conditional compilation to
*         ensure a successful compilation for non-CapSense-capable devices</td>
*     <td>Compilation for non-CapSense-capable devices</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>The initial version</td>
*     <td></td>
*   </tr>
* </table>
*
********************************************************************************
* \section group_csdidac_more_information More Information
********************************************************************************
*
* Important information about the CapSense-technology overview, appropriate
* device for the design, CapSense system and sensor design guidelines,
* different interfaces and tuning guidelines necessary for a successful design
* of a CapSense system is available in the Getting Started with CapSense
* document and the product-specific CapSense design guide. It is highly
* recommended to start with these documents. They can be found at www.cypress.com.
*
* For more information, refer to the following documents:
*
* * CapSense and CSDIDAC Overview:
*
*   * <a href="https://github.com/cypresssemiconductorco/mbed-os-example-csdidac"><b>CSDIDAC Middleware
*     Code Example for MBED OS</b></a>
*
*   * <a href="https://cypresssemiconductorco.github.io/capsense/capsense_api_reference_manual/html/index.html">
*     <b>CapSense Middleware API Reference Guide</b></a>
*
* * ModusToolbox Overview:
*
*   * <a href="https://www.cypress.com/products/modustoolbox-software-environment">
*     <b>ModusToolbox Software Environment, Quick Start Guide, Documentation,
*     and Videos</b></a>
*
*   * <a href="https://www.cypress.com/ModusToolboxDeviceConfig"><b>ModusToolbox
*     Device Configurator Tool Guide</b></a>
*
* * Kits:
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-145-40xx-psoc-4000s-capsense-prototyping-kit">
*     <b>CY8CKIT-145-40XX PSoC 4000S CapSense Prototyping Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-149-psoc-4100s-plus-prototyping-kit">
*     <b>CY8CKIT-149 PSoC 4100S Plus Prototyping Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-041-psoc-4-s-series-pioneer-kit">
*     <b>CY8CKIT-041-40XX PSoC 4 S-Series Pioneer Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/cy8ckit-041-41xx-psoc-4100s-capsense-pioneer-kit">
*     <b>CY8CKIT-041-41XX PSoC 4100S CapSense Pioneer Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-6-ble-pioneer-kit-cy8ckit-062-ble">
*     <b>CY8CKIT-062-BLE PSoC 6 BLE Pioneer Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-6-wifi-bt-pioneer-kit-cy8ckit-062-wifi-bt">
*     <b>CY8CKIT-062-WiFi-BT PSoC 6 WiFi-BT Pioneer Kit</b></a>
*
*   * <a href="https://www.cypress.com/documentation/development-kitsboards/psoc-6-wi-fi-bt-prototyping-kit-cy8cproto-062-4343w">
*     <b>CY8CPROTO-062-4343W PSoC 6 Wi-Fi BT Prototyping Kit</b></a>
*
* * General Information:
*
*   * <a href="https://github.com/cypresssemiconductorco.github.io/psoc4pdl/pdl_api_reference_manual/html/index.html">
*     <b>PSoC 4 PDL API Reference</b></a>
*
*   * <a href="https://github.com/cypresssemiconductorco/psoc6pdl">
*     <b>PSoC 6 PDL API Reference</b></a>
*
*   * <a href="https://www.cypress.com/documentation/technical-reference-manuals/psoc-6-mcu-psoc-63-ble-architecture-technical-reference">
*     <b>PSoC 6 Technical Reference Manual</b></a>
*
*   * <a href="http://www.cypress.com/ds218787">
*     <b>PSoC 63 with BLE Datasheet Programmable System-on-Chip datasheet</b></a>
*
*   * <a href="https://www.cypress.com/documentation/technical-reference-manuals/psoc-4000s-family-psoc-4-architecture-technical-reference">
*     <b>PSoC 4000S Family: PSoC 4 Architecture Technical Reference Manual (TRM)</b></a>
*
*   * <a href="https://www.cypress.com/documentation/technical-reference-manuals/psoc-4100s-and-psoc-4100s-plus-psoc-4-architecture">
*     <b>PSoC 4100S and PSoC 4100S Plus: PSoC 4 Architecture Technical Reference Manual (TRM)</b></a>
*
*   * <a href="https://github.com/cypresssemiconductorco"><b>
*     Cypress Semiconductor GitHub</b></a>
*
*   * <a href="http://www.cypress.com"><b>Cypress Semiconductor</b></a>
*
* \note
* The links to another software component's documentation (middleware and PDL)
* point to GitHub to the latest available version of the software.
* To get documentation of the specified version, download from GitHub and unzip
* the component archive. The documentation is available in the <i>docs</i> folder.
*
* \defgroup group_csdidac_macros Macros
* \brief
* This section describes the CSDIDAC macros. These macros can be used for
* checking a maximum IDAC code and a maximum IDAC output current.
* For detailed information about macros, see each macro description.
*
* \defgroup group_csdidac_enums Enumerated types
* \brief
* Describes the enumeration types defined by the CSDIDAC. These enumerations
* can be used for checking CSDIDAC functions' return status,
* for defining a CSDIDAC LSB and polarity, and for choosing IDAC for an
* operation and defining its states.  For detailed information about
* enumerations, see each enumeration description.
*
* \defgroup group_csdidac_data_structures Data Structures
* \brief
* Describes the data structures defined by the CSDIDAC. The CSDIDAC
* middleware use structures for output channel pins,
* middleware configuration, and context. The pin structure is included
* in the configuration structure and both of them can be defined by the
* user with the CSD personality in the Device Configurator or manually
* if the user doesn't use ModusToolbox.
* The context structure contains a copy of the configuration structure
* and current CSDIDAC middleware state data. The context
* structure should be allocated by the user and be passed to all
* CSDIDAC middleware functions. CSDIDAC middleware structure sizes
* are shown in the table below:
*
* <table class="doxtable">
*   <tr><th>Structure</th><th>Size in bytes (w/o padding)</th></tr>
*   <tr>
*     <td>cy_stc_csdidac_pin_t</td>
*     <td>5</td>
*   </tr>
*   <tr>
*     <td>cy_stc_csdidac_config_t</td>
*     <td>23</td>
*   </tr>
*   <tr>
*     <td>cy_stc_csdidac_context_t</td>
*     <td>31</td>
*   </tr>
* </table>
*
* \defgroup group_csdidac_functions Functions
* \brief
* This section describes the CSDIDAC Function Prototypes.
*/

/******************************************************************************/


#if !defined(CY_CSDIDAC_H)
#define CY_CSDIDAC_H

#include "cy_device_headers.h"
#include "cy_csd.h"

#if (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2))

/* The C binding of definitions to build with the C++ compiler. */
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
* \addtogroup group_csdidac_macros
* \{
*/
/** Middleware major version */
#define CY_CSDIDAC_MW_VERSION_MAJOR             (2)

/** Middleware minor version */
#define CY_CSDIDAC_MW_VERSION_MINOR             (10)

/** Middleware version */
#define CY_CSDIDAC_MW_VERSION                   (210)

/** CSDIDAC ID. The user can identify the CSDIDAC middleware error codes by this macro. */
#define CY_CSDIDAC_ID                           (CY_PDL_DRV_ID(0x44u))

/**
* The CSDIDAC max code value. The user provides the code
* parameter for the Cy_CSDIDAC_OutputEnableExt() function
* in the range from 0u to CY_CSDIDAC_MAX_CODE.
*/
#define CY_CSDIDAC_MAX_CODE                     (127u)

/**
* The CSDIDAC max output current value. The user provides
* the value of the current parameter for the Cy_CSDIDAC_OutputEnable()
* function in range from 0 to +/-(CY_CSDIDAC_MAX_CURRENT_NA).
*/
#define CY_CSDIDAC_MAX_CURRENT_NA               (609600uL)

/** \} group_csdidac_macros */

/***************************************
* Enumerated Types and Parameters
***************************************/
/**
* \addtogroup group_csdidac_enums
* \{
*/

/** CSDIDAC return enumeration type */
typedef enum
{
    CY_CSDIDAC_SUCCESS           = (0u),
                                            /**< The operation executed successfully. */
    CY_CSDIDAC_BAD_PARAM         = (CY_CSDIDAC_ID + (uint32_t)CY_PDL_STATUS_ERROR + 1u),
                                            /**<
                                             * An input parameter is invalid.
                                             * The user checks whether all
                                             * the input parameters are valid.
                                             */
    CY_CSDIDAC_HW_BUSY           = (CY_CSDIDAC_ID + (uint32_t)CY_PDL_STATUS_ERROR + 2u),
                                            /**<
                                             * The CSD HW block is busy,
                                             * i.e. any of current channel (A or B)
                                             * is enabled.
                                             */
    CY_CSDIDAC_HW_LOCKED         = (CY_CSDIDAC_ID + (uint32_t)CY_PDL_STATUS_ERROR + 3u),
                                            /**<
                                             * The CSD HW block is acquired and
                                             * locked by other middleware
                                             * or application. The CSDIDAC
                                             * middleware waits for
                                             * the CSD HW block release
                                             * to acquire it for use.
                                             */
    CY_CSDIDAC_HW_FAILURE         = (CY_CSDIDAC_ID + (uint32_t)CY_PDL_STATUS_ERROR + 4u),
                                            /**<
                                             * A CSD HW block failure. The possible reasons:
                                             *  - No peripheral clock assigned to the CSD HW block.
                                             *  - Peripheral clock assigned to the CSD HW block is disabled.
                                             *  - The CSD HW clock frequency is less than 100 kHz.
                                             *  - The configuration CSD HW block registers are corrupted.
                                             *  - The CSD HW block is damaged.
                                             */
    CY_CSDIDAC_BAD_CONFIGURATION  = (CY_CSDIDAC_ID + (uint32_t)CY_PDL_STATUS_ERROR + 5u),
                                            /**<
                                             * The CSDIDAC configuration structure initialization issue.
                                             * The possible reasons:
                                             *  - The base pointer is initialized with NULL.
                                             *  - The csdCxtPtr pointer is initialized with NULL.
                                             *  - The configA or configB fields are not enumerators of the
                                             *    \ref cy_en_csdidac_channel_config_t type.
                                             *  - The ptrPinA (ptrPinB) field is initialized with NULL
                                             *    when configA (configB) is initialized with \ref CY_CSDIDAC_GPIO.
                                             *  - The configA and configB fields are initialized with \ref CY_CSDIDAC_DISABLED
                                             *    simultaneously.
                                             *  - The configA and configB fields are initialized with \ref CY_CSDIDAC_JOIN
                                             *    simultaneously.
                                             *  - The configA (configB) field is initialized with \ref CY_CSDIDAC_JOIN
                                             *    when configB (configA) is initialized with \ref CY_CSDIDAC_DISABLED.
                                             */
} cy_en_csdidac_status_t;

/**
* The CSDIDAC output current LSB enumeration type. The user can choose
* LSB when the Cy_CSDIDAC_OutputEnableExt() function is called and
* can check which LSB was chosen by the Cy_CSDIDAC_OutputEnable()
* function in the cy_stc_csdidac_context_t structure.
*/

typedef enum
{
    CY_CSDIDAC_LSB_37_IDX   = 0u,           /**< Index for 37.5 nA LSB */
    CY_CSDIDAC_LSB_75_IDX   = 1u,           /**< Index for 75.0 nA LSB */
    CY_CSDIDAC_LSB_300_IDX  = 2u,           /**< Index for 0.3 uA LSB */
    CY_CSDIDAC_LSB_600_IDX  = 3u,           /**< Index for 0.6 uA LSB */
    CY_CSDIDAC_LSB_2400_IDX = 4u,           /**< Index for 2.4 uA LSB */
    CY_CSDIDAC_LSB_4800_IDX = 5u,           /**< Index for 4.8 uA LSB */
}cy_en_csdidac_lsb_t;

/**
* The CSDIDAC polarity enumeration type. The user can choose the polarity
* when the Cy_CSDIDAC_OutputEnableExt() function is called and can
* check which polarity was chosen by the Cy_CSDIDAC_OutputEnable()
* function in the cy_stc_csdidac_context_t structure.
*/
typedef enum
{
    CY_CSDIDAC_SOURCE       = 0u,           /**< Source polarity */
    CY_CSDIDAC_SINK         = 1u,           /**< Sink polarity */
}cy_en_csdidac_polarity_t;

/**
* The CSDIDAC channel enabling enumeration type. The user can check which
* channel (A or B or both) is currently enabled
* in the cy_stc_csdidac_context_t structure.
*/
typedef enum
{
    CY_CSDIDAC_DISABLE      = 0u,           /**< The channel is disabled. */
    CY_CSDIDAC_ENABLE       = 1u,           /**< The channel is enabled. */
}cy_en_csdidac_state_t;

/**
* The CSDIDAC choosing enumeration type. The user can choose channel A or B
* to operate with the Cy_CSDIDAC_OutputEnableExt(), Cy_CSDIDAC_OutputDisable(),
* or Cy_CSDIDAC_OutputEnable() functions.
*/
typedef enum
{
  CY_CSDIDAC_A              = 0uL,          /**< The IDAC A is chosen for an operation */
  CY_CSDIDAC_B              = 1uL,          /**< The IDAC B is chosen for an operation */
  CY_CSDIDAC_AB             = 2uL,          /**< Both IDACs are chosen for an operation */
} cy_en_csdidac_choice_t;

/**
* The CSDIDAC channel configuration defines either disabled or enabled with
* specific routing.
*/
typedef enum
{
    CY_CSDIDAC_DISABLED   = 0u,             /**< The IDAC channel is disabled. */
    CY_CSDIDAC_GPIO       = 1u,             /**< The IDAC channel is enabled and routed to a pin. */
    CY_CSDIDAC_AMUX       = 2u,             /**< The IDAC channel is enabled and routed to a corresponding analog bus. */
    CY_CSDIDAC_JOIN       = 3u,             /**< The IDAC channel is enabled and routed to the other IDAC channel. */
}cy_en_csdidac_channel_config_t;

/** \} group_csdidac_enums */


/***************************************
* Data Structure Definitions
***************************************/
/**
* \addtogroup group_csdidac_data_structures
* \{
*/

/** The CSDIDAC pin structure. */
typedef struct {
    GPIO_PRT_Type * ioPcPtr;                /**< The pointer to the channel IO PC register. */
    uint8_t pin;                            /**< The channel IO pin. */
} cy_stc_csdidac_pin_t;

/** The CSDIDAC configuration structure */
typedef struct
{
    CSD_Type * base;                        /**< The pointer to the CSD HW Block. */
    cy_stc_csd_context_t * csdCxtPtr;       /**< The pointer to the context of the CSD driver. */
    cy_en_csdidac_channel_config_t configA; /**< The IDAC A channel configuration. */
    cy_en_csdidac_channel_config_t configB; /**< The IDAC B channel configuration. */
    const cy_stc_csdidac_pin_t * ptrPinA;   /**< The pointer to the IDAC A pin structure. */
    const cy_stc_csdidac_pin_t * ptrPinB;   /**< The pointer to the IDAC B pin structure. */
    uint32_t cpuClk;                        /**< CPU Clock in Hz. */
    uint8_t csdInitTime;                    /**< The CSD HW Block initialization time. */
} cy_stc_csdidac_config_t;

/** The CSDIDAC context structure, that contains the internal middleware data. */
typedef struct{
    cy_stc_csdidac_config_t cfgCopy;        /**< A configuration structure copy. */
    cy_en_csdidac_polarity_t polarityA;     /**< The current IdacA polarity. */
    cy_en_csdidac_lsb_t lsbA;               /**< The current IdacA LSB. */
    uint8_t codeA;                          /**< The current IdacA code. */
    cy_en_csdidac_state_t channelStateA;    /**< The IDAC channel A is enabled. */
    cy_en_csdidac_polarity_t polarityB;     /**< The current IdacB polarity. */
    cy_en_csdidac_lsb_t lsbB;               /**< The current IdacB LSB. */
    uint8_t codeB;                          /**< The current IdacB code. */
    cy_en_csdidac_state_t channelStateB;    /**< The IDAC channel B is enabled. */
}cy_stc_csdidac_context_t;

/** \} group_csdidac_data_structures */


/*******************************************************************************
* Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_csdidac_functions
* \{
*/
cy_en_csdidac_status_t Cy_CSDIDAC_Init(
                const cy_stc_csdidac_config_t * config,
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_DeInit(
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_WriteConfig(
                const cy_stc_csdidac_config_t * config,
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_Wakeup(
                const cy_stc_csdidac_context_t * context);
cy_en_syspm_status_t Cy_CSDIDAC_DeepSleepCallback(
                cy_stc_syspm_callback_params_t * callbackParams,
                cy_en_syspm_callback_mode_t mode);
cy_en_csdidac_status_t Cy_CSDIDAC_Save(
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_Restore(
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_OutputEnable(
                cy_en_csdidac_choice_t ch,
                int32_t current,
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_OutputEnableExt(
                cy_en_csdidac_choice_t outputCh,
                cy_en_csdidac_polarity_t polarity,
                cy_en_csdidac_lsb_t lsbIndex,
                uint32_t idacCode,
                cy_stc_csdidac_context_t * context);
cy_en_csdidac_status_t Cy_CSDIDAC_OutputDisable(
                cy_en_csdidac_choice_t ch,
                cy_stc_csdidac_context_t * context);

/** \} group_csdidac_functions */


/*******************************************************************************
* Function Name: Cy_CSDIDAC_IsIdacLsbValid
****************************************************************************//**
*
* Performs verification if the value passed through the idacLsbVal
* parameter is the enumerator of the \ref cy_en_csdidac_lsb_t type.
*
* \param idacLsbVal
* The input value for verification.
*
* \return status
* Returns the verification status:
* - true  - Indicates that the verification succeeded.
* - false - Indicates that the verification failed.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CSDIDAC_IsIdacLsbValid(cy_en_csdidac_lsb_t idacLsbVal)
{
    bool retVal;

    switch(idacLsbVal)
    {
        case CY_CSDIDAC_LSB_37_IDX:
        case CY_CSDIDAC_LSB_75_IDX:
        case CY_CSDIDAC_LSB_300_IDX:
        case CY_CSDIDAC_LSB_600_IDX:
        case CY_CSDIDAC_LSB_2400_IDX:
        case CY_CSDIDAC_LSB_4800_IDX:
            retVal = true;
            break;

        default:
            retVal = false;
            break;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_IsIdacPolarityValid
****************************************************************************//**
*
* Performs verification if the value passed through the idacPolarityVal
* parameter is the enumerator of the \ref cy_en_csdidac_polarity_t type.
*
* \param idacPolarityVal
* The input value for verification.
*
* \return status
* Returns the verification status:
* - true  - Indicates that the verification succeeded.
* - false - Indicates that the verification failed.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CSDIDAC_IsIdacPolarityValid(cy_en_csdidac_polarity_t idacPolarityVal)
{
    bool retVal;

    switch(idacPolarityVal)
    {
        case CY_CSDIDAC_SOURCE:
        case CY_CSDIDAC_SINK:
            retVal = true;
            break;

        default:
            retVal = false;
            break;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_IsIdacChoiceValid
****************************************************************************//**
*
* Performs verification if the value passed through the idacChoiceVal
* parameter is the enumerator of the \ref cy_en_csdidac_choice_t type.
*
* Performs verification that both IDACs are not disabled if CY_CSDIDAC_AB is
* passed through the idacChoiceVal parameter.
*
* \param idacChoiceVal
* The input value for verification.
*
* \param idacAConfigVal
* The IDACA channel configuration.
*
* \param idacBConfigVal
* The IDACB channel configuration.
*
* \return status
* Returns the verification status:
* - true  - Indicates that the verification succeeded.
* - false - Indicates that the verification failed.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CSDIDAC_IsIdacChoiceValid(cy_en_csdidac_choice_t idacChoiceVal,
                                                  cy_en_csdidac_channel_config_t idacAConfigVal,
                                                  cy_en_csdidac_channel_config_t idacBConfigVal)
{
    bool retVal;

    switch(idacChoiceVal)
    {
        case CY_CSDIDAC_A:
        case CY_CSDIDAC_B:
            retVal = true;
            break;
        case CY_CSDIDAC_AB:
            if((CY_CSDIDAC_DISABLED != idacAConfigVal) &&
               (CY_CSDIDAC_DISABLED != idacBConfigVal))
            {
                retVal = true;
            }
            else
            {
                retVal = false;
            }
            break;

        default:
            retVal = false;
            break;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_IsIdacChConfigValid
****************************************************************************//**
*
* Performs verification if the value passed through the idacChConfigVal
* parameter is the enumerator of the \ref cy_en_csdidac_channel_config_t type.
*
* \param idacChConfigVal
* The input value for verification.
*
* \return status
* Returns the verification status:
* - true  - Indicates that the verification succeeded.
* - false - Indicates that the verification failed.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CSDIDAC_IsIdacChConfigValid(cy_en_csdidac_channel_config_t idacChConfigVal)
{
    bool retVal;

    switch(idacChConfigVal)
    {
        case CY_CSDIDAC_DISABLED:
        case CY_CSDIDAC_GPIO:
        case CY_CSDIDAC_AMUX:
        case CY_CSDIDAC_JOIN:
            retVal = true;
            break;

        default:
            retVal = false;
            break;
    }

    return(retVal);
}


/*******************************************************************************
* Function Name: Cy_CSDIDAC_IsIdacConfigValid
****************************************************************************//**
*
* Performs verification of the CSDIDAC data structure initialization.
*
* \param config
* The pointer to the CSDIDSC configuration structure \ref cy_stc_csdidac_config_t.
*
* \return status
* Returns the verification status:
* - true  - Indicates that the verification succeeded.
* - false - Indicates that the verification failed.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_CSDIDAC_IsIdacConfigValid(const cy_stc_csdidac_config_t * config)
{
    bool retVal = true;

    if((NULL != config->base) && (NULL != config->csdCxtPtr))
    {
        if(((CY_CSDIDAC_GPIO == config->configA) && (NULL == config->ptrPinA)) ||
           ((CY_CSDIDAC_GPIO == config->configB) && (NULL == config->ptrPinB)) ||
           ((CY_CSDIDAC_DISABLED == config->configA) && (CY_CSDIDAC_DISABLED == config->configB)) ||
           ((CY_CSDIDAC_JOIN == config->configA) && (CY_CSDIDAC_DISABLED == config->configB)) ||
           ((CY_CSDIDAC_JOIN == config->configB) && (CY_CSDIDAC_DISABLED == config->configA)) ||
           (false == Cy_CSDIDAC_IsIdacChConfigValid(config->configA)) ||
           (false == Cy_CSDIDAC_IsIdacChConfigValid(config->configB)) ||
           ((CY_CSDIDAC_JOIN == config->configA) && (CY_CSDIDAC_JOIN == config->configB)))
        {
            retVal = false;
        }
    }
    else
    {
        retVal = false;
    }

    return(retVal);
}




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* (defined(CY_IP_MXCSDV2) || defined(CY_IP_M0S8CSDV2)) */

#endif /* CY_CSDIDAC_H */


/* [] END OF FILE */
