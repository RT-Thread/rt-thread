/***************************************************************************//**
* \file cy_usb_dev.h
* \version 2.10
*
* Provides API declarations of the USBFS device middleware.
*
********************************************************************************
* \copyright
* (c) 2018-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


/**
* \mainpage USB Device Middleware Library 2.10
*
* The USB Device middleware provides a full-speed USB 2.0 Chapter 9 specification
* -compliant device framework. It uses the USBFS driver from PDL to interface
* with the hardware. The middleware provides support for Audio, CDC, and HID
* classes. Also, it allows implementing other class support.
* The USB Configurator tool makes it easy to construct the USB
* Device descriptor.
*
* <b>Features:</b>
* * USB Full-Speed Device Framework
* * \ref group_usb_dev_cfg_tool
* * The following USB Classes are supported:
*   * \ref group_usb_dev_audio_class_info
*   * \ref group_usb_dev_cdc_class_info
*   * \ref group_usb_dev_hid_class_info
*
********************************************************************************
* \section section_usb_dev_general General Description
********************************************************************************
*
* The USB Device structure is divided into  layers. The implementation
* is event-driven: the USBFS driver receives interrupts from the hardware and
* provides callbacks to the USB Device layer which implements them and provides
* events to the Class layer. A simplified image is shown below. \n \n
* \image html usb_dev_solution_struct.png
*
* Include cy_usb_dev.h along with the header for the USB class to be used
* (cy_usb_dev_hid.h, cy_usb_dev_cdc.h, cy_usb_dev_audio.h) to get access to
* all the functions and other declarations in this library.
* If you use ModusToolbox USB Device Configurator, also include cycfg_usbdev.h.
*
********************************************************************************
* \section section_usb_dev_quick_start Quick Start Guide
********************************************************************************
*
* Cypress USB Device middleware can be used in various software environments.
* Refer to the \ref section_usb_dev_toolchain.
* The quickest way to get started is using the Code Examples.
* Cypress Semiconductor continuously extends its portfolio of code examples
* at <a href="http://www.cypress.com"><b>Cypress Semiconductor website</b></a>
* and at <a href="https://github.com/cypresssemiconductorco">
* <b>Cypress Semiconductor GitHub</b></a>.
*
* This quick start guide is for an environment configured to use for development
* MTB CAT1A Peripheral Driver Library (PSoC6) or MTB CAT2 Peripheral Driver Library
* (PSoC4 & PMG1) included in the project.
*
* To easily run a USB, use the ModusToolbox USBCommDevice or USBM project.
* The steps below show how to set up a USB Device based on a basic
* ModusToolbox project (like Hello_World).
*
* The following steps set up a USB device recognized as an standard HID device -
* USB mouse and moves it from right to the left, and vice-versa.
* \note Some steps contain a corresponding to the figure below number in
* brackets.
*
* \subsection subsection_qsg_step1 STEP 1: Enable the USB Device middleware.
*
* Launch ModusToolbox Library Manager and enable the USB Device middleware.
* This step is required only if the ModusToolbox IDE is used. Otherwise, ensure
* the USB Device Middleware is included in your project.
*
* \subsection subsection_qsg_step2 STEP 2: Generate initialization code.
*
* 1.  Launch the ModusToolbox Device Configurator Tool and switch to the
*     Peripherals tab (#1.1).
* 2.  Enable the USB personality under Communication and enter Alias (#1.2).
*     We use USBHID in \ref section_usb_dev_quick_start
* 3.  Go to the Parameters pane and configure the USB personality: assign
*     the peripheral clock divider (#1.3) for Clock (Bus Reset).
*     Any available free divider can be used.
*     This is not required to be done for the PMG1 family of devices.
* 4.  Set Endpoint Mask to 1 to enable data endpoint 1 (#1.4) Enabled data
*     endpoints must match the descriptor tree in the USB Configurator.
*     \image html usb_dev_device_cfg.png
* 5.  Switch to the System tab (#2.1).
* 6.  Check the IMO clock is enabled (#2.2). Select Trim with USB (#2.3)
* 7.  Select one of the PLLs, if your device supports more than one.
*     Enable the PLL and set a frequency of 48 MHz (#2.4).
* 8.  Select the CLK_HF3 USB clock (#2.5). Assign the source clock to
*     the CLK_PATH connected to the configured previously PLL.<br>
*     (Not required for PMG1 devices) (#2.6).
* 9.  Check the FLL clock is enabled (Not required for PMG1 devices) (#2.7).
* 10. Select File->Save to generate initialization code.
*     \image html usb_dev_system_cfg.png
*
* \subsection subsection_qsg_step3 STEP 3: Generate USB descriptors.
*
* 1. Run the USB Configurator.
* 2. In the Device Descriptor node, set bDeviceClass - 0x02(#3.1),
*    iProduct - the device name to identify among connected devices. We use
*    "USB Device Quick Start guide"(#3.2).
* 3. Remove default Alternate Settings.
* 4. Add HID Alternate Settings.
* 5. Add HID Descriptor and select 3-Button Mouse in HID Report (#3.3).
* 6. Add Endpoint Descriptor and set: direction - IN,
*    Transfer Type - Interrupt, wMaxPacketSize - 3, bInterval - 10(#3.4).
* 7. Perform File->Save to generate initialization code. If configuration is
*    saved for the first time, choose a name (like design.cyusbdev) and save it
*    to the project root.
*    \image html usb_dev_configurator.png
*
* \subsection subsection_qsg_step4 STEP 4: Update main.c
*
* 1. Include the USB headers to get access to the generated descriptor
*    structures, USB driver, device, and class layers APIs.
*    \snippet usb_dev/snippet/main.c snipped_cy_usb_dev_headers
* 2. Declare the USB context global variables:
*    \snippet usb_dev/snippet/main.c snipped_cy_usb_dev_hid_globals
* 3. Configure the USB interrupt structures and declare interrupt handlers
*    (refer to the Configure Interrupts section of the USBFS
*    driver in the PDL API Reference).
*    \snippet usb_dev/snippet/main.c snipped_cy_usb_dev_interrupt_configuration
* 4. Implement the interrupt handlers:
*    \snippet usb_dev/snippet/main.c snipped_cy_usb_dev_interrupt_handlers
* 5. Update the main() function with the USB and interrupt initialization
*    routines:
*    \snippet usb_dev/snippet/main.c snipped_USB_Dev_InitEnableHID
* 6. Example of the routine to move mouse from right to the left,
*    and vice-versa.
*    \snippet usb_dev/snippet/main.c snipped_USB_Dev_MouseMove
*
* \subsection subsection_qsg_step5 STEP 5: Build and program the device.
*
* Connect the device to the Host PC. On the PC, verify a new USB device was
* enumerated as a mouse device. The mouse's cursor shall move left to
* right and vice-versa.
*
********************************************************************************
* \section group_usb_dev_configuration Configuration Considerations
********************************************************************************
*
* This section explains how to configure the USB Device for operation.
*
********************************************************************************
* \subsection group_usb_dev_config_drv Configure USBFS driver
********************************************************************************
*
* The driver and system resources configuration details are provided in the
* USBFS driver section Configuration Considerations in the PDL API Reference
* Manual. The provided code snippets expect that driver and system resources
* configuration is done.
*
********************************************************************************
* \subsection group_usb_dev_config_descr Construct USB Device Descriptors
********************************************************************************
*
* Run standalone USB Configurator tool to construct the USB Device descriptors.
* After USB Device descriptors are
* constructed, save generated source and header files. Add these files to your
* project. Open header files to get external definitions for:
* * USB Device configuration structure \ref cy_stc_usb_dev_config_t instance.
* * Array of USB Devices structures \ref cy_stc_usb_dev_device_t.
* * CDC and/or HID class configuration structure instances.
*
* These definitions will be required in the configuration steps provided below.
*
********************************************************************************
* \subsection group_usb_dev_config Configure USB Device
********************************************************************************
*
* To initialize the USB Device middleware, call \ref Cy_USB_Dev_Init function
* providing:
* * The pointer to the USBFS instance.
* * The pointer to the filled USBFS driver configuration structure cy_stc_usbfs_dev_drv_config_t.
* * The pointer to the allocated USBFS driver context structure cy_stc_usbfs_dev_drv_context_t.
* * The pointer to the generated middleware USB Device structure \ref cy_stc_usb_dev_device_t.
* * The pointer to the generated middleware USB Device configuration structure \ref cy_stc_usb_dev_config_t.
* * The pointer to the allocated middleware USB Device context structure \ref cy_stc_usb_dev_context_t.
*
********************************************************************************
* \subsection group_usb_dev_config_class Configure USB Classes
********************************************************************************
*
* The USB Device middleware provides support of Audio, HID, and CDC classes.
* Each class has own initialization function. This function must be called
* after \ref Cy_USB_Dev_Init to initialize class data and register it. The
* class-specific request will be passed to the class handler after registration.
* Note that the USB Configurator tool generates HID and CDC Class configuration
* structures that are required class initialization. Find these structure
* external declaration in the generated header file.
*
* To initialize the Audio Class, call \ref Cy_USB_Dev_Audio_Init function
* providing:
* * The NULL pointer (reserved for possible future use).
* * The pointer to the allocated Audio Class context structure \ref cy_stc_usb_dev_audio_context_t.
* * The pointer to the allocated USB Device context structure \ref cy_stc_usb_dev_context_t.
*
* To initialize the CDC Class, call \ref Cy_USB_Dev_CDC_Init function
* providing:
* * The pointer to the populated CDC Class configuration structure \ref cy_stc_usb_dev_cdc_config_t.
* * The pointer to the allocated CDC Class context structure \ref cy_stc_usb_dev_cdc_context_t.
* * The pointer to the allocated USB Device context structure \ref cy_stc_usb_dev_context_t.
*
* To initialize the HID Class, call \ref Cy_USB_Dev_HID_Init function
* providing:
* * The pointer to the populated HID Class configuration structure \ref cy_stc_usb_dev_hid_config_t.
* * The pointer to the allocated HID Class context structure \ref cy_stc_usb_dev_hid_context_t.
* * The pointer to the allocated USB Device context structure \ref cy_stc_usb_dev_context_t.
*
********************************************************************************
* \subsection group_usb_dev_config_enable Enable USB Device
********************************************************************************
*
* Finally, enable the USB Device operation calling \ref Cy_USB_Dev_Connect.
* This function call enables pull-up on D+ to signal USB Device connection on
* USB Bus. The USB Host detects device connection and starts device enumeration.
* It requests the device descriptors to define device capabilities and finally
* sets device configuration for the following operation.
* The \ref Cy_USB_Dev_Connect provides an argument to block until enumeration
* completes or exits after the USB Device is enabled.
*
* \snippet usb_dev/snippet/main.c snipped_Cy_USB_Dev_InitEnable
*
* \note
* The interrupts are mandatory for the USB Device operation. Therefore, USBFS
* interrupts must be enabled in the NVIC and global interrupts must be
* enabled as well.
*
********************************************************************************
* \section section_usb_dev_design Design Considerations
********************************************************************************
*
* The typical use case is that application calls the middleware API interface
* provided by the USB Device or Class layer to implement application logic.
* However, some features are provided only by the USBFS driver layer. Therefore, if
* the application needs them, the driver API interface must be used. The list of
* these features is provided in the section \ref group_usb_dev_drv_features.
*
********************************************************************************
* \subsection group_usb_dev_cfg_tool USB Configurator
********************************************************************************
*
* The standalone USB Configurator tool helps construct USB Device descriptors.
* The USB device descriptors
* provide to the USB Host complete information about the connected device. The tool
* output are generated source and header files that contain information about the
* USB Device: device descriptors plus structures that help access device
* descriptors. Generated files are mandatory for the middleware operation and must be
* added to your project. The header file provides access to
* instances of the USB Device configuration structure \ref cy_stc_usb_dev_config_t
* and array of the USB Device structures \ref cy_stc_usb_dev_device_t. Both these
* definitions are required for USB Device configuration. The tool also generates
* instances of configuration structures required for CDC and HID Class
* configuration.
*
* A detailed information about USB Descriptors is provided by the
* [USB Specification](http://www.usb.org/developers/docs/usb20_docs/)
*
* The USB Configurator tool provides the User Guide, which can be found in the
* documentation.
*
********************************************************************************
* \subsection group_usb_dev_std_requests Standard Request Support
********************************************************************************
*
* The USB Device supports standard requests listed in the table below.
*
* <table class="doxtable">
*   <tr><th>Standard Request</th><th>Request Processing Description</th><th>USB Spec Reference</th></tr>
*   <tr>
*     <td>CLEAR_FEATURE</td>
*     <td>Clears or disables a specific feature. Support recipients: Device,
*     Interface and Endpoint. The TEST_MODE feature selector is not supported.</td>
*     <td>9.4.1</td>
*   </tr>
*   <tr>
*     <td>GET_CONFIGURATION</td>
*     <td>Returns the current device configuration value.</td>
*     <td>9.4.2</td>
*   </tr>
*   <tr>
*     <td>GET_DESCRIPTOR</td>
*     <td>Returns the specified descriptor if the descriptor exists.</td>
*     <td>9.4.3</td>
*   </tr>
*   <tr>
*     <td>GET_INTERFACE</td>
*     <td>Returns the selected alternate interface setting for the specified
*     interface.</td>
*     <td>9.4.4</td>
*   </tr>
*   <tr>
*     <td>GET_STATUS</td>
*     <td>Returns status for the specified recipient. Support recipients:
*     Device, Interface, and Endpoint.</td>
*     <td>9.4.5</td>
*   </tr>
*   <tr>
*     <td>SET_ADDRESS</td>
*     <td>Sets the device address for all future device accesses.</td>
*     <td>9.4.6</td>
*   </tr>
*   <tr>
*     <td>SET_CONFIGURATION</td>
*     <td>Sets the device configuration. After this request, the device is ready for
*      communication.</td>
*     <td>9.4.7</td>
*   </tr>
*   <tr>
*     <td>SET_DESCRIPTOR</td>
*     <td>Not supported (optional request).</td>
*     <td>9.4.8</td>
*   </tr>
*   <tr>
*     <td>SET_FEATURE</td>
*     <td>Enables a specific feature. Support recipients: Device, Interface, and Endpoint.
*     The TEST_MODE feature selector is not supported.</td>
*     <td>9.4.9</td>
*   </tr>
*   <tr>
*     <td>SET_INTERFACE</td>
*     <td>Allows the USB Host to select an alternate setting for the specified
*     interface.</td>
*     <td>9.4.10</td>
*   </tr>
*   <tr>
*     <td>SYNCH_FRAME</td>
*     <td>Not supported.</td>
*     <td>9.4.11</td>
*   </tr>
* </table>
*
********************************************************************************
* \subsection group_usb_dev_audio_class_info Audio Class
********************************************************************************
*
* The USB Audio class can be used in a large amount of applications,
* either Made for iPod (MFI) or general USB Audio based. These applications
* consist of, but are not limited to, speakers, microphones, headsets, music
* creation tools (DJ equipment, guitar jacks, etc), and mixers.
* An additional application for the Audio class is in Musical Instrument
* Digital Interface (MIDI) applications. This interface uses a digital UART-like
* interface and allows the information to be sent across to the Host to
* be used with software applications, such as Apple Garage Band. Various
* instruments, such as electronic pianos, interface with MIDI.
*
* A detailed description about Audio Class is provided by the
* [USB Implementers Forum (USB-IF) Class Documentation]
* (http://www.usb.org/developers/docs/devclass_docs/)
*
* The Audio Class does not provide support any of Audio v1.0 or v2.0 requests
* processing and provides only the API interface to register Audio request handlers
* implemented on the application level. However, \ref group_usb_dev_cfg_tool
* supports Audio v1.0 or v2.0 descriptors.
*
* \note
* The MIDI Class support is not available in this version.
*
********************************************************************************
* \subsection group_usb_dev_cdc_class_info CDC: Communication Device Class
********************************************************************************
*
* Common use case for this class in a PSoC design is to replace a legacy serial
* (RS232) COM port with a USB connection. This allows customers to use
* legacy serial software while updating the communication interface to
* something more readily available on today's computers. The type of data
* that might be streamed across USB can vary depending on the end application.
* This could be as simple as streaming raw ADC counts to an entire command
* protocol. Additionally, CDC is extremely useful for debug purposes.
* Users can easily develop a USB interface that can send and receive
* information across CDC. On the Host side, GUI applications are widely
* available to view the data being transmitted, such as TeraTerm, Terminal,
* or Hyper-Terminal (depending on version of Microsoft Windows).
*
* A detailed description about CDC class is provided by the
* [USB Implementers Forum (USB-IF) Class Documentation]
* (http://www.usb.org/developers/docs/devclass_docs/)
*
* The CDC Class supports requests listed in the table below.
* <table class="doxtable">
*   <tr><th>Class Request</th><th>Request Processing Description</th><th>Communications Class Subclass Specification for PSTN Devices</th></tr>
*   <tr>
*     <td>SET_LINE_CODING</td>
*     <td>Allows the host to specify typical asynchronous line-character
*      formatting properties such as: data terminal rate, number of stop bits,
*      parity type and number of data bits. It applies to data transfers both
*      from the Host to the Device and from the Device to the Host.</td>
*     <td>6.3.10</td>
*   </tr>
*   <tr>
*     <td>GET_LINE_CODING</td>
*     <td>Allows the host to discover the currently configured line coding.</td>
*     <td>6.3.11</td>
*   </tr>
*   <tr>
*     <td>SET_CONTROL_LINE_STATE</td>
*     <td>Generates RS-232/V.24 style control signals - RTS and DTR.</td>
*     <td>6.3.12</td>
*   </tr>
* </table>
*
* The CDC Class supports notifications listed in the table below.
* <table class="doxtable">
*   <tr><th>Class Notification</th><th>Notification Processing Description</th><th>Communications Class Subclass Specification for PSTN Devices</th></tr>
*   <tr>
*     <td>SERIAL_STATE</td>
*     <td>Allows the Host to read the current state of the carrier detect (CD),
*      DSR, break, and ring signal (RI).</td>
*     <td>6.3.4</td>
*   </tr>
* </table>
*
********************************************************************************
* \subsection group_usb_dev_hid_class_info HID: Human Interface Device
********************************************************************************
*
* There are many possible use cases for HID depending on the end application.
* A keyboard/keypad is a common HID application that has been implemented
* previously with PSoC. Additionally, customers can use PSoC to implement a
* PC mouse or game controller device. A more generic use case seen is with
* regards to customers using USB as general-purpose interface between PSoC and
* the Host, without conforming to specific USAGE such as a Keyboard, Mouse, etc.
* Instead the user configures the HID descriptor to be a generic device, which
* allows them to transfer Vendor-Specific information, such as ADC data,
* button presses, etc., across the HID protocol. This allows customers to
* perform custom/generic data transfers over USB, without needing to provide
* an INF or SYS file during enumeration or worry about WHQL certification.
* All this is accomplished using the HID drivers that are built into all
* modern operation systems today. This includes Windows, Mac, and Linux.
*
* A detailed description about HID is provided by the
* [USB Implementers Forum (USB-IF) Class Documentation]
* (http://www.usb.org/developers/docs/devclass_docs/)
*
* The HID Class supports requests listed in the table below.
* <table class="doxtable">
*   <tr><th>Class Request</th><th>Request Processing Description</th><th>HID Spec Reference</th></tr>
*   <tr>
*     <td>GET_REPORT</td>
*     <td>Allows the USB Host to receive a report via the control pipe.</td>
*     <td>7.2.1</td>
*   </tr>
*   <tr>
*     <td>SET_REPORT</td>
*     <td>Allows the USB Host to send a report via the control pipe (set a
*         state of input, output, or feature report controls).</td>
*     <td>7.2.2</td>
*   </tr>
*   <tr>
*     <td>GET_IDLE</td>
*     <td>Reads the current idle rate for a particular Input report. \n
*      The recommended default idle rate (rate when the device is initialized)
*      is 500 milliseconds for keyboards (delay before first repeat rate) and
*      infinity for joysticks and mice.</td>
*     <td>7.2.3</td>
*   </tr>
*   <tr>
*     <td>SET_IDLE</td>
*     <td>Sets idle rate for a particular report. This request is used to limit
*      the reporting frequency of an interrupt in endpoint.\n
*      When the idle rate byte is 0 (zero), the duration is indefinite.
*      The endpoint reports only when a change is detected in the report data.
*      When the idle rate byte is non-zero, then a fixed duration is
*      used (defined by idle rate).</td>
*     <td>7.2.4</td>
*   </tr>
*   <tr>
*     <td>GET_PROTOCOL</td>
*     <td>Reads which protocol is currently active (either the boot or the
*         report protocol).</td>
*     <td>7.2.5</td>
*   </tr>
*   <tr>
*     <td>SET_PROTOCOL</td>
*     <td>Switches between the boot protocol and the report protocol (or vice versa).</td>
*     <td>7.2.6</td>
*   </tr>
* </table>
*
********************************************************************************
* \subsection group_usb_dev_class_x Adding Custom Class
********************************************************************************
*
* The USB Device middleware provides API interface that allows the user to
* implement custom class support. The middleware notifies registered class about
* following events:
* * Bus Reset detected ( \ref cy_cb_usb_dev_bus_reset_t ).
* * Set Configuration request received ( \ref cy_cb_usb_dev_set_config_t ).
* * Set Interface request received ( \ref cy_cb_usb_dev_set_interface_t ).
* * Setup packet received ( \ref cy_cb_usb_dev_request_received_t ).
* * Data is received in response for current setup packet ( \ref cy_cb_usb_dev_request_cmplt_t ).
*
* To create a new custom Class, follow the steps below:
* 1. Implement functions to service events (from the list above) required
*    for class operation. Typically, class should implement service of class-specific
*    requests therefore needs to implement functions defined by \ref cy_cb_usb_dev_request_received_t
*    and \ref cy_cb_usb_dev_request_cmplt_t.
* 2. Initialize instance of \ref cy_stc_usb_dev_class_t structure using implemented
*    service functions. Provide NULL pointer as function pointer if class does not
*    use this event.
* 3. Allocate instance of \ref cy_stc_usb_dev_class_ll_item_t structure to
*    provide storage for a linked list item of the class.
* 4. The class might need a context to store class-specific data. If needed,
*    define context type specific for this class and allocate it.
* 5. To enable class operation, this needs to be registered using
*    \ref Cy_USB_Dev_RegisterClass function after USB Device middleware is
*    initialized.
*
* Any of supported classes can be taken as an example to implement a custom class.
*
********************************************************************************
* \subsection group_usb_dev_vendor Vendor-Specific Requests Support
********************************************************************************
*
* The vendor-specific requests are STALLed by USB Device middleware by default.
* The exception is MS OS String vendor-specific request to retrieve an OS Feature
* Descriptor (Note that USB device must contain MS OS String descriptor to handle
* this vendor-specific by middleware).
* The middleware provides the \ref Cy_USB_Dev_RegisterVendorCallbacks function
* to register callbacks to handle vendor-specific requests.
*
********************************************************************************
* \subsection group_usb_dev_ep_buf_alloc Allocate Data Endpoint Buffer
********************************************************************************
*
* The application allocates buffers for data endpoints to operate. The buffer
* allocation depends on USBFS driver endpoint buffer access type configuration.
* It specifies which hardware register set 8-bit or 16-bit is used to access
* hardware endpoints buffer. The 16-bit access requires that the specific rules for
* the endpoints buffer allocation must be met (See Hardware Buffer Access
* section of the USBFS driver for more information). \n
* To make endpoint buffer allocation configuration independent, use
* the \ref CY_USB_DEV_ALLOC_ENDPOINT_BUFFER macro.
*
********************************************************************************
* \subsection group_usb_dev_self_powered_dev Self-Powered Devices
********************************************************************************
*
* The USB Device responds to GET_STATUS requests based on the status set with
* the \ref Cy_USB_Dev_SetPowerStatus function. To set the correct status,
* \ref Cy_USB_Dev_SetPowerStatus must be called during initialization if USB
* Device is configured as self-powered. The \ref Cy_USB_Dev_SetPowerStatus must
* be called any time the device changes status. A self-powered device also requires
* monitoring VBUS to control pull-up resistors. The pull-up resistor does
* not supply power to the data line until you call \ref Cy_USB_Dev_Connect.
* \ref Cy_USB_Dev_Disconnect disconnects the pull-up resistor from the data line.
* Find information about how to add VBUS monitoring in your application in the USBFS driver
* section VBUS Detection in the PDL API Reference Manual.
*
********************************************************************************
* \subsection group_usb_dev_std_timeout Timeout Function Redefinition
********************************************************************************
*
* The USB Device middleware provides following blocking functions: \ref Cy_USB_Dev_ReadEpBlocking,
* \ref Cy_USB_Dev_WriteEpBlocking, and \ref Cy_USB_Dev_Connect (the behavior
* defined by the blocking parameter of the connect function). The blocking functions
* parameter timeout defines how many milliseconds to wait before timeout.
* The SysLib driver function Cy_SysLib_Delay is used to implement a 1 millisecond
* wait cycle. The middleware provides function \ref Cy_USB_Dev_OverwriteHandleTimeout
* that allows overriding the wait function implementation. This might be
* useful when an operation system is used in your application.
*
* \note
* The blocking function must be used carefully to not cause application lock-up.
* The preferred solution is using non-blocking functions.
*
********************************************************************************
* \subsection group_usb_dev_drv_features Driver Features
********************************************************************************
*
* There are driver features that do not have corresponding an API
* interface provided in the middleware. However, the application might need
* these features for USB Device implementation. If there is such a need, the
* driver functions must be used. These features are listed below:
* * Data Endpoint 1 - 8 Completion, SOF received and LPM transfer ACKed events
*   notification.
* * Low power support: Suspend / Resume, Remote wakeup signaling.
* * Link Power Management (LPM) support.
*
* Find more information in the appropriate section of the USBFS driver documentation
* provided in the PDL API Reference Manual.
*
********************************************************************************
* \section section_usb_dev_toolchain Supported Software and Tools
********************************************************************************
*
* For supported software and tools, refer to the Supported Software and Tools
* section in in the
* [RELEASE.md](https://github.com/Infineon/usbdev/blob/master/RELEASE.md#supported-software-and-tools)
*
********************************************************************************
* \section section_usb_dev_errata Errata
********************************************************************************
*
* This section lists the known problems with the USB Device middleware.
*
* <table class="doxtable">
*   <tr><th>Cypress ID</th><th>Known Issue</th><th>Workaround</th></tr>
*   <tr>
*     <td>DRIVERS-1401</td>
*     <td>
*         The USB Device ignores LPM requests after wake up from Deep Sleep.
*     </td>
*     <td>
*         Call USBFS driver Cy_USBFS_Dev_Drv_Lpm_SetResponse() after calling
*         Cy_USBFS_Dev_Drv_Resume() to restore response to the LPM packets.
*     </td>
*   </tr>
*   <tr>
*     <td>DRIVERS-1427</td>
*     <td>
*         The USB Device modes with DMA do not work after wake up from Deep
*         Sleep, due to incorrect restore of the ARB_CFG register.
*     </td>
*     <td>
*         Save ARB_CFG values before entering Deep Sleep and restore it after
*         calling of Cy_USBFS_Dev_Drv_Resume.
*         \snippet usb_dev/snippet/main.c snippet_WorkaroundDmaResume
*     </td>
*   </tr>
* </table>
*
********************************************************************************
* \section group_usb_dev_changelog Changelog
********************************************************************************
*
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td rowspan="4">2.10</td>
*     <td>Updated Documentation</td>
*     <td>PMG1 Integration</td>
*   </tr>
*   <tr>
*     <td>Fixed vendor request handling</td>
*     <td>Defect Fixes</td>
*   </tr>
*   <tr>
*     <td>Added support for configurations without any data endpoints</td>
*     <td>Defect Fixes </td>
*   </tr>
*   <tr>
*     <td>Minor enhancements in several functions.</td>
*     <td>Enabled compliance with MISRA-C:2012 standard.</td>
*   </tr>
*   </tr>
*   <tr>
*     <td rowspan="5">2.0</td>
*     <td>Updated the internal processing  to support USBFS driver updates.</td>
*     <td>The USBFS driver is updated to v2.0.</td>
*   </tr>
*   <tr>
*     <td>Moved the timeout from Cy_USB_Dev_AbortEpTransfer() to the driver layer.
*         The maximum function's wait time is significantly reduced.</td>
*     <td>Align with the changes of the USBFS driver.</td>
*   </tr>
*   <tr>
*     <td>Changed the functions parameter name and the structure member name class to classObj.</td>
*     <td>Fixed the ambiguity related to the usage of the C++ keyword class as a name.</td>
*   </tr>
*   <tr>
*     <td>Enclosed middleware sources within a conditional compilation to
*         exclude the USB Device middleware for devices without USB hardware.</td>
*     <td>Fixed a compilation error for devices without USB hardware.</td>
*   </tr>
*   <tr>
*     <td>Updated the major and minor version defines to follow the naming convention.</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>The initial version.</td>
*     <td></td>
*   </tr>
* </table>
*
********************************************************************************
* \section group_usb_dev_more_information More Information
********************************************************************************
*
* For more information, refer to the links in the
* [README.md](https://github.com/Infineon/usbdev/blob/master/README.md#more-information)
*
* \note
* The links to the other software component's documentation (middleware and PDL)
* point to GitHub to the software latest available version.
* To get documentation of the specified version, download from GitHub and unzip
* the component archive. The documentation is available in the <i>docs</i> folder.
*
********************************************************************************
* \defgroup group_usb_device Device
* This section provides an API description for the core functionality of the
* USB Device: initialization, status information, data transfers, and class
* support.
* \{
*    \defgroup group_usb_dev_macros Macros
*    \{
*        \defgroup group_usb_dev_macros_device_descr Descriptors
*    \}
*
*    \defgroup group_usb_dev_functions Functions
*    \{
*        \defgroup group_usb_dev_functions_common        Initialization Functions
*        \defgroup group_usb_dev_functions_service       Service Functions
*        \defgroup group_usb_dev_functions_data_transfer Data Transfer Functions
*        \defgroup group_usb_dev_functions_vendor_support Vendor Request Support Functions
*        \defgroup group_usb_dev_functions_class_support Class Support Functions
*     \}
*
*     \defgroup group_usb_dev_data_structures Data Structures
*     \{
*         \defgroup group_usb_dev_structures_device       Device Information
*         \defgroup group_usb_dev_structures_device_descr Device Descriptors
*         \defgroup group_usb_dev_structures_control      Control Transfer
*         \defgroup group_usb_dev_structures_class        Class Support
*         \defgroup group_usb_dev_structures_func_ptr     Function Pointers
*     \}
*
*     \defgroup group_usb_dev_enums Enumerated Types
* \}
*
* \defgroup group_usb_dev_audio Audio Class
* \defgroup group_usb_dev_cdc CDC Class
* \defgroup group_usb_dev_hid HID Class
*
*/


#if !defined(CY_USB_DEV_H)
#define CY_USB_DEV_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "cy_usbfs_dev_drv.h"
#include "cy_usb_dev_descr.h"

#if (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS))

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_usb_dev_macros
* \{
*/

/*******************************************************************************
*                          Middleware Version
*******************************************************************************/

/** USB Device Middleware major version */
#define CY_USB_DEV_MW_VERSION_MAJOR  (2)

/** USB Device Middleware minor version */
#define CY_USB_DEV_MW_VERSION_MINOR  (10)

/** USB Device Middleware identifier */
#define CY_USB_DEV_ID             CY_PDL_DRV_ID(0x08U)

/** Maximum number of interfaces (this equals to the maximum number of hardware
* endpoints where each interface has at least one endpoint).
*/
#define CY_USB_DEV_NUM_INTERFACES_MAX   CY_USBFS_DEV_DRV_NUM_EPS_MAX

/** USBFS Device endpoint 0 packet size */
#define CY_USB_DEV_EP0_PACKET_SIZE      CY_USBFS_DEV_DRV_EP0_BUFFER_SIZE

/** Length of serial string number generated from silicon ID */
#define CY_USB_DEV_SN_STRING_LENGTH     (32U)

/** Length of serial string number */
#define CY_USB_DEV_SN_STRING_DESR_LENGTH    (CY_USB_DEV_SN_STRING_LENGTH + 2U)
/** \} group_usb_dev_macros */


/*******************************************************************************
*                              Enumerated Types
*******************************************************************************/

/**
* \addtogroup group_usb_dev_enums
* \{
*/

/** USBFS Device return codes */
typedef enum
{
    /** Operation completed successfully */
    CY_USB_DEV_SUCCESS = 0U,

    /** One or more input parameters are invalid */
    CY_USB_DEV_BAD_PARAM           = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 1U),

    /** The request is not handled */
    CY_USB_DEV_REQUEST_NOT_HANDLED = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 2U),

    /** Timeout occurred for the operation  */
    CY_USB_DEV_TIMEOUT            = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 3U),

    /** The hardware is busy executing previous operation */
    CY_USB_DEV_DRV_HW_BUSY         = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 4U),

    /** The hardware is disabled */
    CY_USB_DEV_DRV_HW_DISABLED     = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 5U),

    /** The hardware error occurred during operation */
    CY_USB_DEV_DRV_HW_ERROR        = (CY_USB_DEV_ID | CY_PDL_STATUS_ERROR | 6U),

} cy_en_usb_dev_status_t;

/** Device states */
typedef enum
{
    CY_USB_DEV_DISABLED,   /**< Device is disabled */
    CY_USB_DEV_ATTACHED,   /**< Device is attached */
    CY_USB_DEV_POWERED,    /**< Device is powered */
    CY_USB_DEV_DEFAULT,    /**< Device is in default state (after bus reset) */
    CY_USB_DEV_ADDRESSED,  /**< Device set address (device is ready to communicate using this address) */
    CY_USB_DEV_CONFIGURED  /**< Device is configured (device is ready to communicate using data endpoints) */
} cy_en_usb_dev_state_t;

/** Power Status */
typedef enum
{
    CY_USB_DEV_STATUS_BUS_POWERED,    /**< Device is bus powered */
    CY_USB_DEV_STATUS_SELF_POWERED    /**< Device is self powered */
} cy_en_usb_dev_power_status_t;

/** Callback events */
typedef enum
{
    CY_USB_DEV_EVENT_BUS_RESET,     /**< Bus Reset detected */
    CY_USB_DEV_EVENT_SET_CONFIG,    /**< SET_CONFIGURATION request received */
    CY_USB_DEV_EVENT_SET_INTERFACE  /**< SET_INTERFACE request received */
} cy_en_usb_dev_callback_events_t;
/** \} group_usb_dev_enums */


/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_usb_dev_structures_control
* \{
*/

/** Parsed bmRequest */
typedef struct
{
    uint8_t direction;  /**< Transfer direction */
    uint8_t type;       /**< Transfer type */
    uint8_t recipient;  /**< Transfer recipient */
} cy_stc_usb_dev_bm_request;

/** Store request */
typedef struct
{
    cy_stc_usb_dev_bm_request bmRequestType; /**< Request type */
    uint8_t  bRequest;  /**< Request value */
    uint16_t wValue;    /**< Request value (2 bytes) */
    uint16_t wIndex;    /**< Request index (2 bytes) */
    uint16_t wLength;   /**< Request length (2 bytes) */
} cy_stc_usb_dev_setup_packet_t;

/** Execute transfer use this structure */
typedef struct
{
    cy_stc_usb_dev_setup_packet_t setup;  /**< Request packet */
    uint8_t  *ptr;          /**< Pointer to data to transfer or space to store data */
    uint8_t  *buffer;       /**< Pointer to buffer to store data send from host to device during control transfer */
    uint16_t remaining;     /**< Number of bytes remaining to complete send or receive */
    uint16_t size;          /**< Number of bytes to send or receive */
    uint16_t bufferSize;    /**< Size of the buffer to store data */
    uint8_t  direction;     /**< Transfer direction */
    bool     zlp;           /**< Defines whether zero length packet is needed to complete data stage */
    bool     notify;        /**< Defines whether trigger callback that notifies end of data stage (device received data) */
} cy_stc_usb_dev_control_transfer_t;

/** \} group_usb_dev_structures_control */


/** \cond INTERNAL */
/** Get compiler know what is cy_stc_usb_dev_context.
* The cy_stc_usb_dev_context_t is defined below.
*/
struct cy_stc_usb_dev_context;
/** \endcond */


/**
* \addtogroup group_usb_dev_structures_func_ptr
* \{
*/

/**
* Pointer to a function that implements a callback for the following events:
* Bus Reset detected, SET_CONFIGURATION request received and SET_INTERFACE request
* received. The notified events are defined by event argument
* (see \ref cy_en_usb_dev_callback_events_t).
* Only one event is notified when callback invoked.
* This callback invoked in the USB interrupt handler context and must be short
* as possible. \n
* Input arguments:
* * Bus Reset detected event: ignore wValue and wIndex arguments.
* * SET_CONFIGURATION request received event: the wValue is new configuration
*   value and wIndex can be ignored.
* * SET_CONFIGURATION request received event: the wValue is new alternative
*   setting value and wIndex interface value to which alternate belongs. \n
*
* The returned status defines following operation:
* * Bus Reset detected event: status is ignored and event processing is passed to
*   class event handlers.
* * SET_CONFIGURATION or SET_INTERFACE received event: the returned status defines
*   following request processing. If returned status fail the request is
*   STALLed and event notification stops.
*   If returned status is success the event is notified to the appropriate class
*   event handlers which status defines request response STALL or ACK.
*/
typedef cy_en_usb_dev_status_t (* cy_cb_usb_dev_events_callback_t)(cy_en_usb_dev_callback_events_t event,
                                                                   uint32_t wValue, uint32_t wIndex,
                                                                   struct cy_stc_usb_dev_context *devContext);

/**
* Pointer to a function that implements a timeout handler. The function accepts the
* number of milliseconds that remain to wait before timeout expires.
* This returns the number of milliseconds remaining to wait minus the milliseconds
* that have elapsed inside the function.
*/
typedef int32_t (* cy_fn_usb_dev_handle_timeout_ptr_t)(int32_t milliseconds);

/**
* Pointer to function that returns pointer to uint8_t array, which contains a serial number string
* and accepts the device context \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that returns serial number string.
*/
typedef uint8_t * (* cy_fn_usb_dev_sn_string_ptr_t)(void);

/**
* Pointer to function that returns nothing and accepts a pointer to void and a pointer to \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that notifies the class about a bus reset event.
*/
typedef void (* cy_cb_usb_dev_bus_reset_t)(void *classData, struct cy_stc_usb_dev_context *devContext);

/**
* Pointer to function that returns the status of operation and accepts received configuration number,
* pointer to class context, and pointer to device context \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that notifies the class about a set configuration request event.
*/
typedef cy_en_usb_dev_status_t (* cy_cb_usb_dev_set_config_t)(uint32_t configuration, void *classData,
                                                              struct cy_stc_usb_dev_context *devContext);

/**
* Pointer to function that returns the status of operation and accepts received interface
* alternate settings number, pointer to class context, and pointer to device context \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that notifies the class about a set interface request event.
*/
typedef cy_en_usb_dev_status_t (* cy_cb_usb_dev_set_interface_t)(uint32_t interface, uint32_t alternate,
                                                                 void *classContext,
                                                                 struct cy_stc_usb_dev_context *devContext);

/**
* Pointer to function that returns the status of operation and accepts pointer to received control transfer
* number, pointer to class context, and pointer to device context \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that notifies the class about a request received event.
*/
typedef cy_en_usb_dev_status_t (* cy_cb_usb_dev_request_received_t)(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                    void *classContext,
                                                                    struct cy_stc_usb_dev_context *devContext);

/**
* Pointer to function that returns status of operation and accepts pointer to received control transfer
* number, pointer to class context, and pointer to device context \ref cy_stc_usb_dev_context_t.
* This type is used to define a callback that notifies the class that a request completed (data is received in
* response for current request) event.
*/
typedef cy_en_usb_dev_status_t (* cy_cb_usb_dev_request_cmplt_t)(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                void *classContext,
                                                                struct cy_stc_usb_dev_context *devContext);

/** \} group_usb_dev_structures_func_ptr */

/**
* \addtogroup group_usb_dev_structures_class
* \{
*/

/** Class support definition - each class must provide this structure */
typedef struct
{
    /** Called after bus reset is serviced. Initialize Class here */
    cy_cb_usb_dev_bus_reset_t busReset;

    /**
    * Called after Set Configuration request is received.
    * The endpoint available for this configuration must be configured here.
    * Returns status of the event processing.
    */
    cy_cb_usb_dev_set_config_t setConfiguration;

    /**
    * Called after Set Interface request is received.
    * Probably the endpoint configuration requires correction here.
    * Returns status of the event processing.
    */
    cy_cb_usb_dev_set_interface_t setInterface;

    /**
    * This function is called when a setup packet was received from the USB Host but
    * was not recognized. Therefore, it might require the user to do the class processing.
    */
    cy_cb_usb_dev_request_received_t requestReceived;

    /**
    * This function is called when the USB Device received data from the USB Host
    * as part of current request processing. The requestReceivedHandle function
    * must enable notification to trigger this event. This makes sense only when CDC
    * request processing requires a data stage.
    */
    cy_cb_usb_dev_request_cmplt_t requestCompleted;

} cy_stc_usb_dev_class_t;


/** Class linked list element. It includes class and class data pointers
* and  pointer to the next class linked list element.
*/
typedef struct cy_stc_usb_dev_class_ll_item
{
    /** Next item in the class driver linked list */
    struct cy_stc_usb_dev_class_ll_item *next;

    /** Pointer to the class structure */
    cy_stc_usb_dev_class_t *classObj;

    /** Pointer to the class data (context) */
    void *classData;

} cy_stc_usb_dev_class_ll_item_t;
/** \} group_usb_dev_structures_class */


/**
* \addtogroup group_usb_dev_data_structures
* \{
*/
/** USB Device configuration structure */
typedef struct
{
    /** Pointer to the buffer to store data received from the USB Host through
    * Endpoint 0. The buffer size must be large enough to store received data
    * for all supported requests.
    */
    uint8_t  *ep0Buffer;

    /** Buffer size for Endpoint 0 */
    uint16_t  ep0BufferSize;

} cy_stc_usb_dev_config_t;


/** USB Device context structure.
* All fields for the USB Device context structure are internal. Firmware never
* reads or writes these values. Firmware allocates the structure and provides
* the address of the structure to the middleware in function calls. Firmware
* must ensure that the defined instance of this structure remains in scope while
* the middleware is in use.
*/
typedef struct cy_stc_usb_dev_context
{
    /** \cond INTERNAL*/

    /** Device state */
    volatile cy_en_usb_dev_state_t state;

    /** Configuration changed status */
    volatile bool configChanged;

    /** Device status */
    volatile uint8_t status;

    /** Device configuration */
    volatile uint8_t configuration;

    /** Device interface alternate settings */
    volatile uint8_t alternate[CY_USB_DEV_NUM_INTERFACES_MAX];

    /** Storage for serial number string descriptor (constructed from silicon ID) */
    uint8_t serialNumDescr[CY_USB_DEV_SN_STRING_DESR_LENGTH];

    /** Pointer to function that implements timeout in milliseconds */
    cy_fn_usb_dev_handle_timeout_ptr_t handleTimeout;

    /** Control transfer data */
    cy_stc_usb_dev_control_transfer_t ControlTransfer;

    /** Pointers to structure that describes device */
    const cy_stc_usb_dev_device_t *devDescriptors;

    /** Pointer to function that returns serial string */
    cy_fn_usb_dev_sn_string_ptr_t getSerialNumString;

    /** Callback for events: bus reset, set configuration and set interface */
    cy_cb_usb_dev_events_callback_t eventsCallback;

    /** Vendor-Specific callback to handle Setup packet received event */
    cy_cb_usb_dev_request_received_t vndRequestReceived;

    /** Vendor-Specific callback to handle notification that OUT stage is completed */
    cy_cb_usb_dev_request_cmplt_t vndRequestCompleted;

    /** Pointer to linked list of class structures */
    cy_stc_usb_dev_class_ll_item_t *classRoot;

    /** Pointer to driver base address */
    USBFS_Type *drvBase;

    /** Pointer to driver context */
    struct cy_stc_usbfs_dev_drv_context *drvContext;

    /** \endcond */
} cy_stc_usb_dev_context_t;
/** \} group_usb_dev_data_structures */


/*******************************************************************************
*                            Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_usb_dev_functions_common
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_Init(USBFS_Type *base,
                                       struct cy_stc_usbfs_dev_drv_config const *drvConfig,
                                       struct cy_stc_usbfs_dev_drv_context      *drvContext,
                                       cy_stc_usb_dev_device_t  const *device,
                                       cy_stc_usb_dev_config_t  const *config,
                                       cy_stc_usb_dev_context_t       *context);

void Cy_USB_Dev_DeInit(cy_stc_usb_dev_context_t *context);
cy_en_usb_dev_status_t Cy_USB_Dev_Connect(bool blocking, int32_t timeout,
                                          cy_stc_usb_dev_context_t *context);
void Cy_USB_Dev_Disconnect(cy_stc_usb_dev_context_t *context);
/** \} group_usb_dev_functions_common */


/**
* \addtogroup group_usb_dev_functions_service
* \{
*/
__STATIC_INLINE void Cy_USB_Dev_RegisterEventsCallback(cy_cb_usb_dev_events_callback_t callback,
                                                       cy_stc_usb_dev_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_GetConfiguration     (cy_stc_usb_dev_context_t const *context);
__STATIC_INLINE uint32_t Cy_USB_Dev_GetAlternateSettings (uint32_t interface,
                                                          cy_stc_usb_dev_context_t const *context);
__STATIC_INLINE bool    Cy_USB_Dev_IsConfigurationChanged(cy_stc_usb_dev_context_t *context);

__STATIC_INLINE bool Cy_USB_Dev_IsRemoteWakeupEnabled(cy_stc_usb_dev_context_t const *context);
__STATIC_INLINE void Cy_USB_Dev_SetPowerStatus       (cy_en_usb_dev_power_status_t status,
                                                      cy_stc_usb_dev_context_t     *context);

__STATIC_INLINE uint8_t* Cy_USB_Dev_GetSerialNumberString(cy_stc_usb_dev_context_t *context);
__STATIC_INLINE void     Cy_USB_Dev_RegisterSerialNumStringCallback(cy_fn_usb_dev_sn_string_ptr_t callback,
                                                                    cy_stc_usb_dev_context_t  *context);
__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlRead(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                   uint8_t *ptr,
                                                                   uint32_t size);

__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlWrite(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                    uint32_t size);

__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlWriteResult(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                                          uint8_t *ptr);
/** \cond INTERNAL */
__STATIC_INLINE uint32_t Cy_USB_Dev_GetConfigurationIdx(cy_stc_usb_dev_context_t const *context);
/** \endcond */

/** \} group_usb_dev_functions_service */


/**
* \addtogroup group_usb_dev_functions_data_transfer
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_StartReadEp(uint32_t endpoint,
                                              cy_stc_usb_dev_context_t *context);

cy_en_usb_dev_status_t Cy_USB_Dev_ReadEpBlocking(uint32_t endpoint,
                                                 uint8_t  *buffer,
                                                 uint32_t size,
                                                 uint32_t *actSize,
                                                 int32_t  timeout,
                                                 cy_stc_usb_dev_context_t *context);

cy_en_usb_dev_status_t Cy_USB_Dev_ReadEpNonBlocking(uint32_t  endpoint,
                                                    uint8_t  *buffer,
                                                    uint32_t  size,
                                                    uint32_t *actSize,
                                                    cy_stc_usb_dev_context_t *context);

cy_en_usb_dev_status_t Cy_USB_Dev_AbortEpTransfer(uint32_t endpoint,
                                                  cy_stc_usb_dev_context_t *context);

__STATIC_INLINE uint32_t Cy_USB_Dev_GetEpNumToRead(uint32_t endpoint,
                                                   cy_stc_usb_dev_context_t const *context);


cy_en_usb_dev_status_t Cy_USB_Dev_WriteEpBlocking(uint32_t endpoint,
                                                  uint8_t const *buffer,
                                                  uint32_t size,
                                                  int32_t  timeout,
                                                  cy_stc_usb_dev_context_t *context);

cy_en_usb_dev_status_t Cy_USB_Dev_WriteEpNonBlocking(uint32_t endpoint,
                                                     uint8_t const *buffer,
                                                     uint32_t size,
                                                     cy_stc_usb_dev_context_t *context);

__STATIC_INLINE void Cy_USB_Dev_OverwriteHandleTimeout(cy_fn_usb_dev_handle_timeout_ptr_t handleTimeout,
                                                       cy_stc_usb_dev_context_t *context);
/** \} group_usb_dev_functions_data_transfer */


/**
* \addtogroup group_usb_dev_functions_class_support
* \{
*/
cy_en_usb_dev_status_t Cy_USB_Dev_RegisterClass(cy_stc_usb_dev_class_ll_item_t *classItem,
                                                    cy_stc_usb_dev_class_t     *classObj,
                                                    void                       *classContext,
                                                    cy_stc_usb_dev_context_t   *context);

__STATIC_INLINE void Cy_USB_Dev_RegisterClassBusResetCallback(cy_cb_usb_dev_bus_reset_t callback,
                                                              cy_stc_usb_dev_class_t    *classObj);

__STATIC_INLINE void Cy_USB_Dev_RegisterClassSetConfigCallback(cy_cb_usb_dev_set_config_t callback,
                                                               cy_stc_usb_dev_class_t     *classObj);

__STATIC_INLINE void Cy_USB_Dev_RegisterClassSetInterfaceCallback(cy_cb_usb_dev_set_interface_t callback,
                                                                  cy_stc_usb_dev_class_t        *classObj);

__STATIC_INLINE void Cy_USB_Dev_RegisterClassRequestRcvdCallback(cy_cb_usb_dev_request_received_t callback,
                                                                 cy_stc_usb_dev_class_t           *classObj);

__STATIC_INLINE void Cy_USB_Dev_RegisterClassRequestCmpltCallback(cy_cb_usb_dev_request_cmplt_t callback,
                                                                  cy_stc_usb_dev_class_t        *classObj);
/** \} group_usb_dev_functions_class_support */

/**
* \addtogroup group_usb_dev_functions_vendor_support
* \{
*/
__STATIC_INLINE void Cy_USB_Dev_RegisterVendorCallbacks(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                        cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                        cy_stc_usb_dev_context_t     *context);
/** \} group_usb_dev_functions_vendor_support */


/*******************************************************************************
*                                 API Constants
*******************************************************************************/

/**
* \addtogroup group_usb_dev_macros
* \{
*/

/** Timeout value that defines wait forever */
#define CY_USB_DEV_WAIT_FOREVER            (0)

/** Allocates static buffer for data endpoint. The size parameter must be a constant.
* The allocated buffer is aligned on a 2 byte boundary. <b>An odd buffer size is
* converted to even consuming 1 extra byte. The application must discard this
* extra byte</b>. This manipulation is needed to support different 8-bit and 16-bit
* hardware buffer access types in the driver (See Hardware Buffer Access
* section of the USBFS driver for more information).
*/
#define CY_USB_DEV_ALLOC_ENDPOINT_BUFFER(buf, size)  CY_USBFS_DEV_DRV_ALLOC_ENDPOINT_BUFFER(buf,size)

/* bmRequestType.Type: transfer direction */
#define CY_USB_DEV_DIR_HOST_TO_DEVICE    (0U) /**< Transfer direction from Host to Device (setup packet) */
#define CY_USB_DEV_DIR_DEVICE_TO_HOST    (1U) /**< Transfer direction from Device to Host (setup packet) */

/* bmRequestType.Type */
#define CY_USB_DEV_STANDARD_TYPE  (0U)    /**< Standard request type (setup packet) */
#define CY_USB_DEV_CLASS_TYPE     (1U)    /**< Class-specific request type (setup packet) */
#define CY_USB_DEV_VENDOR_TYPE    (2U)    /**< Vendor-specific request type (setup packet) */
#define CY_USB_DEV_RESERVED_TYPE  (3U)    /**< Reserved request type (setup packet) */

/* bmRequestType.Recipient */
#define CY_USB_DEV_RECIPIENT_DEVICE       (0U)    /**< Request recipient device (setup packet) */
#define CY_USB_DEV_RECIPIENT_INTERFACE    (1U)    /**< Request recipient interface (setup packet) */
#define CY_USB_DEV_RECIPIENT_ENDPOINT     (2U)    /**< Request recipient endpoint (setup packet) */
#define CY_USB_DEV_RECIPIENT_OTHER        (3U)    /**< Request recipient other (setup packet) */

/* USB v2.0 spec: Table 9-4. Standard Request Codes */
#define CY_USB_DEV_RQST_GET_STATUS        (0U)    /**< GET_STATUS standard request */
#define CY_USB_DEV_RQST_CLEAR_FEATURE     (1U)    /**< CLEAR_FEATURE standard request */
#define CY_USB_DEV_RQST_SET_FEATURE       (3U)    /**< SET_FEATURE standard request */
#define CY_USB_DEV_RQST_SET_ADDRESS       (5U)    /**< SET_ADDRESS standard request */
#define CY_USB_DEV_RQST_GET_DESCRIPTOR    (6U)    /**< GET_DESCRIPTOR standard request */
#define CY_USB_DEV_RQST_SET_DESCRIPTOR    (7U)    /**< SET_DESCRIPTOR standard request */
#define CY_USB_DEV_RQST_GET_CONFIGURATION (8U)    /**< GET_CONFIGURATION standard request */
#define CY_USB_DEV_RQST_SET_CONFIGURATION (9U)    /**< SET_CONFIGURATION standard request */
#define CY_USB_DEV_RQST_GET_INTERFACE     (10U)   /**< GET_INTERFACE standard request */
#define CY_USB_DEV_RQST_SET_INTERFACE     (11U)   /**< SET_INTERFACE standard request */
#define CY_USB_DEV_RQST_SYNCH_FRAME       (12U)   /**< SYNCH_FRAME standard request */

/* USB v2.0 spec: Table 9-6. Standard Feature Selectors */
#define CY_USB_DEV_DEVICE_REMOTE_WAKEUP   (1U)    /**< REMOTE_WAKEUP feature selector */
#define CY_USB_DEV_ENDPOINT_HALT          (0U)    /**< ENDPOINT_HALT feature selector */
#define CY_USB_DEV_ENDPOINT_STATUS_HALT   (1U)    /**< ENDPOINT_STATUS_HALT feature selector */
#define CY_USB_DEV_TEST_MODE              (2U)    /**< TEST_MODE feature selector */

/** \cond INTERNAL */
/* Vendor Specific Request: Microsoft OS String Descriptor */
#define CY_USB_DEV_RQST_GET_EXTENDED_CONFIG_DESCR   (0x01U)

/* Start position of SN string in SN string descriptor */
#define CY_USB_DEV_STRING_DESCR_SN_STR_POS  (2U)

/* USB v2.0 spec: Table 9-5. Descriptor Types */
#define CY_USB_DEV_GET_DESCR_TYPE(wValue) (CY_HI8(wValue))
#define CY_USB_DEV_GET_DESCR_IDX(wValue)  (CY_LO8(wValue))

/* Device status */
#define CY_USB_DEV_STATUS_BUS_POWERED_MASK    (0x0U)
#define CY_USB_DEV_STATUS_SELF_POWERED_MASK   (0x1U)
#define CY_USB_DEV_STATUS_REMOTE_WAKEUP_MASK  (0x2U)

/* Endpoint direction bit */
#define CY_USB_DEV_EP_IN_DIRECTION  (0x80U)
#define CY_USB_DEV_EP_NUM_MASK      (0x0FU)

#define CY_USB_DEV_EPADDR2EP(endpointAddr)      ((uint32_t) (endpointAddr) & CY_USB_DEV_EP_NUM_MASK)
#define CY_USB_DEV_IS_EP_DIR_IN(endpointAddr)   (0U != ((endpointAddr) & CY_USB_DEV_EP_IN_DIRECTION))
#define CY_USB_DEV_IS_EP_DIR_OUT(endpointAddr)  (0U == ((endpointAddr) & CY_USB_DEV_EP_IN_DIRECTION))

#if (CY_CPU_CORTEX_M0P)
    #define CY_USB_DEV_GET_CFG_WORD(addr)  ( (uint16_t) (((uint16_t) (* (((uint8_t const volatile *) (addr)) + 1U))) << 8U) | \
                                                                     (* (( uint8_t const volatile *) (addr))) )
#else
    #define CY_USB_DEV_GET_CFG_WORD(addr)  (* ((uint16_t const *) (addr)) )
#endif

/*
* These defines are obsolete and kept for backward compatibility only.
* They will be removed in the future versions.
*/
#define CY_USB_DEV_VERSION_MAJOR  (CY_USB_DEV_MW_VERSION_MAJOR)
#define CY_USB_DEV_VERSION_MINOR  (CY_USB_DEV_MW_VERSION_MINOR)

/** \endcond */

/** \} group_usb_dev_macros */


/*******************************************************************************
*                        In-line Function Implementation
*******************************************************************************/

/**
* \addtogroup group_usb_dev_functions_service
* \{
*/
/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterEventsCallback
****************************************************************************//**
*
* Registers a callback function to notify number of events: Bus Reset detected,
* SET_CONFIGURATION request received and SET_INTERFACE request received.
* To remove the callback function, pass NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterEventsCallback(cy_cb_usb_dev_events_callback_t callback,
                                                       cy_stc_usb_dev_context_t *context)
{
    context->eventsCallback = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_GetConfiguration
****************************************************************************//**
*
* Returns USB Device configuration.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Configuration value. The configuration value is 0 until USB Device
* was not enumerated by the USB Host.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_GetConfiguration(cy_stc_usb_dev_context_t const *context)
{
    return (uint32_t) context->configuration;
}


/** \cond INTERNAL */
/*******************************************************************************
* Function Name: Cy_USB_Dev_GetConfigurationIdx
****************************************************************************//**
*
* This function returns current USB Device configuration index.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Configuration index. If device is not configured, returns 0.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_GetConfigurationIdx(cy_stc_usb_dev_context_t const *context)
{
    uint32_t configIdx = 0UL;

    if (CY_USB_DEV_CONFIGURED == context->state)
    {
        configIdx = (uint32_t) context->configuration - 1UL;
    }

    return configIdx;
}
/** \endcond */


/*******************************************************************************
* Function Name: Cy_USB_Dev_GetAlternateSettings
****************************************************************************//**
*
* Returns alternate setting for a certain interface.
* This function is useful to determine which alternate settings are active for
* a certain interface.
*
* \param interface
* Interface number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Alternate settings value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_GetAlternateSettings(uint32_t interface,
                                                         cy_stc_usb_dev_context_t const *context)
{
    CY_ASSERT_L1(interface < CY_USB_DEV_NUM_INTERFACES_MAX);

    return (uint32_t) context->alternate[interface];
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_IsConfigurationChanged
****************************************************************************//**
*
* Returns configuration state that is cleared after read.
* This function is useful to determine which configuration or alternate settings
* of the interface were changed. After configuration state has been changed,
* \ref group_usb_dev_functions_data_transfer functions should be used to start
* communication with the USB Host.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* True - if configuration has been changed since last call. False - otherwise.
*
* \note
* This function is not interrupt-protected and to prevent a race condition,
* it should be protected from the USBFS interruption in the place where it
* is called.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_USB_Dev_IsConfigurationChanged(cy_stc_usb_dev_context_t *context)
{
    bool isChanged = context->configChanged;

    if (isChanged)
    {
        context->configChanged = false;
    }

    return isChanged;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_SetPowerStatus
****************************************************************************//**
*
* Sets Power status to report it when USB Host issues GET_STATUS standard
* requests. Call this function any time when power source is changed from
* Self-Powered to Bus-Powered or vice versa.
*
* \param status
* Power status \ref cy_en_usb_dev_power_status_t
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_SetPowerStatus(cy_en_usb_dev_power_status_t status,
                                               cy_stc_usb_dev_context_t     *context)
{
    if (status == CY_USB_DEV_STATUS_SELF_POWERED)
    {
        context->status |= (uint8_t) CY_USB_DEV_STATUS_SELF_POWERED_MASK;
    }
    else
    {
        context->status &= (uint8_t) ~CY_USB_DEV_STATUS_SELF_POWERED_MASK;
    }
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_IsRemoteWakeupEnabled
****************************************************************************//**
*
* Returns Remote Wakeup status.
* This function is useful to determine whether Remote Wakeup was enabled by the USB
* Host when USB Device supports this option.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* True - if Remote Wakeup was enabled by the USB Host. False - otherwise.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_USB_Dev_IsRemoteWakeupEnabled(cy_stc_usb_dev_context_t const *context)
{
    return (0U != (context->status & CY_USB_DEV_STATUS_REMOTE_WAKEUP_MASK));
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_GetSerialNumberString
****************************************************************************//**
*
* Returns pointer to the serial number string generated from silicon ID.
* The string length is \ref CY_USB_DEV_SN_STRING_LENGTH.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* The pointer to the serial number string.
*
*******************************************************************************/
__STATIC_INLINE uint8_t* Cy_USB_Dev_GetSerialNumberString(cy_stc_usb_dev_context_t *context)
{
    return &context->serialNumDescr[CY_USB_DEV_STRING_DESCR_SN_STR_POS];
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterSerialNumStringCallback
****************************************************************************//**
*
* Registers a callback function that returns the serial string descriptor when
* it is requested by the USB Host.
*
* \param callback
* The pointer to a callback function.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterSerialNumStringCallback(cy_fn_usb_dev_sn_string_ptr_t callback,
                                                                cy_stc_usb_dev_context_t  *context)
{
    context->getSerialNumString = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_SetupControlRead
****************************************************************************//**
*
* Setup control read (Host reads) transfer.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param ptr
* The pointer to the data which will be read by the Host.
*
* \param size
* Number of bytes to read.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS (there is input parameters verification).
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlRead(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                   uint8_t  *ptr,
                                                                   uint32_t size)
{
    /* Setup control transfer (Host reads) */
    transfer->ptr       = ptr;
    transfer->remaining = (uint16_t) size;

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_SetupControlWrite
****************************************************************************//**
*
* Setup control write transfer (Host writes) and sets \ref CY_USB_DEV_SUCCESS status
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param size
* Number of bytes which Host is allowed to write.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS (there is input parameters verification).
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlWrite(cy_stc_usb_dev_control_transfer_t *transfer,
                                                                    uint32_t size)
{
    /* Setup control transfer (Host writes) */
    transfer->remaining = (uint16_t) size;
    transfer->notify    = true;

    return CY_USB_DEV_SUCCESS;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_SetupControlWriteResult
****************************************************************************//**
*
* Copies data received from the Host into the specified memory location. There
* must provide enough place to store number of bytes provided in
* \ref Cy_USB_Dev_SetupControlWrite.
*
* \param transfer
* Pointer to structure that holds SETUP packet and information for
* request processing.
*
* \param ptr
* The pointer to the memory location to copy to.
*
* \return
* Returns \ref CY_USB_DEV_SUCCESS (there is input parameters verification).
*
*******************************************************************************/
__STATIC_INLINE cy_en_usb_dev_status_t Cy_USB_Dev_SetupControlWriteResult(cy_stc_usb_dev_control_transfer_t const *transfer,
                                                                         uint8_t *ptr)
{
    /* Copy data from internal buffer to the user provided location */
    (void) memcpy(ptr, transfer->buffer, (uint32_t) transfer->size);

    return CY_USB_DEV_SUCCESS;
}
/** \} group_usb_dev_functions_service */


/**
* \addtogroup group_usb_dev_functions_data_transfer
* \{
*/
/*******************************************************************************
* Function Name: Cy_USB_Dev_GetEpNumToRead
****************************************************************************//**
*
* Returns the number of bytes that available to be read from a certain
* endpoint buffer. Before calling this function ensure that the Host wrote data
* into the endpoint. The returned value is updated after the Host access to the
* endpoint but remains unchanged after data has been read from the endpoint
* buffer.
*
* \param endpoint
* The OUT data endpoint number.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \return
* Number of bytes in OUT endpoint buffer.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_USB_Dev_GetEpNumToRead(uint32_t endpoint,
                                                   cy_stc_usb_dev_context_t const *context)
{
    return Cy_USBFS_Dev_Drv_GetEndpointCount(context->drvBase, endpoint);
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_OverwriteHandleTimeout
****************************************************************************//**
*
* Overwrite the handle timeout function that is implemented internally.
* The internal implementation converts one timeout unit to milliseconds.
*
* \param handleTimeout
* The pointer to function to be executed to handle timeout for blocking
* operations.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_OverwriteHandleTimeout(cy_fn_usb_dev_handle_timeout_ptr_t handleTimeout,
                                                       cy_stc_usb_dev_context_t *context)
{
    context->handleTimeout = handleTimeout;
}
/** \} group_usb_dev_functions_data_transfer */

/**
* \addtogroup group_usb_dev_functions_class_support
* \{
*/
/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClassBusResetCallback
****************************************************************************//**
*
* Registers a callback function to notify a certain class about a Bus Reset event.
* To remove the callback function, pass NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param classObj
* The pointer to the class structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterClassBusResetCallback(cy_cb_usb_dev_bus_reset_t callback,
                                                              cy_stc_usb_dev_class_t    *classObj)
{
    classObj->busReset = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClassSetConfigCallback
****************************************************************************//**
*
* Registers a callback function to notify a certain class that SET_CONFIGURATION
* request was received from USB Host.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param classObj
* The pointer to the class structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterClassSetConfigCallback(cy_cb_usb_dev_set_config_t callback,
                                                               cy_stc_usb_dev_class_t     *classObj)

{
    classObj->setConfiguration = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClassSetInterfaceCallback
****************************************************************************//**
*
* Registers a callback function to notify a certain class that SET_INTERFACE
* request was received from the USB Host.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param classObj
* The pointer to the class structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterClassSetInterfaceCallback(cy_cb_usb_dev_set_interface_t callback,
                                                                  cy_stc_usb_dev_class_t        *classObj)
{
    classObj->setInterface = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClassRequestRcvdCallback
****************************************************************************//**
*
* Registers a callback function to notify a certain class that setup packet was
* received from USB Host but was not recognized. Therefore, this might require
* manual class processing.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param classObj
* The pointer to the class structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterClassRequestRcvdCallback(cy_cb_usb_dev_request_received_t callback,
                                                                 cy_stc_usb_dev_class_t           *classObj)
{
    classObj->requestReceived = callback;
}


/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterClassRequestCmpltCallback
****************************************************************************//**
*
* Registers a callback function to notify a certain class that the USB Device
* received data from the USB Host as part of current request processing.
* The class setup packet callback function must enable notification to trigger
* this event. This makes sense only when class request processing requires a data
* stage.
* To remove callback function pass NULL as function pointer.
*
* \param callback
* The pointer to a callback function.
*
* \param classObj
* The pointer to the class structure.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterClassRequestCmpltCallback(cy_cb_usb_dev_request_cmplt_t callback,
                                                                  cy_stc_usb_dev_class_t        *classObj)
{
    classObj->requestCompleted = callback;
}
/** \} group_usb_dev_functions_class_support */

/**
* \addtogroup group_usb_dev_functions_vendor_support
* \{
*/
/*******************************************************************************
* Function Name: Cy_USB_Dev_RegisterVendorCallbacks
****************************************************************************//**
*
* Registering user callback to handle Vendor-Specific requests.
*
* \param requestReceivedHandle
* The pointer to a callback function.
* This function is called when setup packet was received from USB Host but was
* not recognized. Therefore this might require manual class processing.
* To remove the callback function, pass a NULL as the function pointer.
*
* \param requestCompletedHandle
* The pointer to a callback function.
* This function is called when the USB Device received data from the USB Host
* as part of current request processing. The requestReceivedHandle function
* must enable notification to trigger this event. This makes sense only when CDC
* request processing requires a data stage.
* To remove callback function pass NULL as function pointer.
*
* \param context
* The pointer to the context structure \ref cy_stc_usb_dev_context_t allocated
* by the user. The structure is used during the USB Device operation for internal
* configuration and data retention. The user must not modify anything in this
* structure.
*
* \note
* The callbacks registered by this function does not overrides processing of
* MS OS String vendor-specific request to retrieve an OS Feature Descriptor.
*
*******************************************************************************/
__STATIC_INLINE void Cy_USB_Dev_RegisterVendorCallbacks(cy_cb_usb_dev_request_received_t requestReceivedHandle,
                                                        cy_cb_usb_dev_request_cmplt_t    requestCompletedHandle,
                                                        cy_stc_usb_dev_context_t     *context)
{
    context->vndRequestReceived  = requestReceivedHandle;
    context->vndRequestCompleted = requestCompletedHandle;
}
/** \} group_usb_dev_functions_vendor_support */

/** \} group_usb_dev */

#if defined(__cplusplus)
}
#endif

#endif /* (defined(CY_IP_MXUSBFS) || defined(CY_IP_M0S8USBDSS)) */

#endif /* (CY_USB_DEV_H) */


/* [] END OF FILE */
