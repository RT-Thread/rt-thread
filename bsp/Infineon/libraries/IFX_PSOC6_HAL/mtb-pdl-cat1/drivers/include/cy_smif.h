/***************************************************************************//**
* \file cy_smif.h
* \version 2.40
*
* Provides an API declaration of the Cypress SMIF driver.
*
********************************************************************************
* \copyright
* Copyright 2016-2022 Cypress Semiconductor Corporation
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
* \addtogroup group_smif
* \{
* The SPI-based communication interface to the external quad SPI (QSPI)
* high-speed memory devices.
*
* The functions and other declarations used in this driver are in cy_smif.h and
* cy_smif_memslot.h (if used). If you are using the ModusToolbox QSPI Configurator,
* also include cycfg_qspi_memslot.h.
*
* **SMIF: Serial Memory Interface**: This IP block implements an SPI-based
* communication interface for interfacing external memory devices to PSoC.
* The SMIF supports SPI, dual SPI (DSPI), quad SPI (QSPI), dual QSPI and octal SPI.
*
* Features
*   - Standard SPI Master interface
*   - Supports single/dual/quad/octal SPI memory devices
*   - Supports dual quad SPI mode
*   - Design-time configurable support for multiple (up to 4) external serial
*   memory devices
*   - eXecute-In-Place (XIP) operation mode for both read and write accesses
*   with 4KB XIP read cache and on-the-fly encryption and decryption
*   - Supports external serial memory initialization via
*   <a href="https://www.jedec.org/standards-documents/docs/jesd216b" target="_blank">
*   Serial Flash Discoverable Parameters (SFDP)</a> standard
*
* The primary usage model for the SMIF is that of an external memory interface.
* The SMIF is capable of interfacing with different types of memory, up to four
* types.
*
* \b SMIF driver is divided into three layers
*   - cy_smif.h API
*   - cy_smif_memslot.h API
*   - SMIF configuration structures
*
* The SMIF API is divided into the low-level functions and memory-slot functions. Use
* the low level API for the SMIF block initialization and for implementing a generic
* SPI communication interface using the SMIF block.
*
* The memory slot API has functions to implement the basic memory operations such as
* program, read, erase etc. These functions are implemented using the memory
* parameters in the memory device configuration data structure. The
* Cy_SMIF_MemInit() API initializes all the memory slots based on the settings
* in the array.
*
* \image html smif_3_0_p01_layers.png
*
* \note
* Above image is applicable only for SMIF v3 IP.
*
* \image html smif_1_0_p01_layers.png
*
* \note
* Above image is applicable only for SMIF v1 IP.
*
* SMIF Configuration Tool is a stand-alone application, which is a part of PDL
* (Creator) and could be found in \<PDL_DIR\>/tools/\<OS_DIR\>/SMIFConfigurationTool
* (e.g. for PDL 3.0.0 and Windows OS PDL/3.0.0/tools/win/SMIFConfigurationTool).
*
* In ModusToolbox this tool is called QSPI Configurator. QSPI Configurator is a part of
* PSoC 6 Software Library and can be found in \<ModusToolbox\>/tools/qspi-configurator-1.1
*
* Tool generates *.c and *.h file with configuration structures. These configuration
* structures are input parameters for cy_smif_memslot API level
*
* \warning The driver is not responsible for external memory persistence. You cannot edit
* a buffer during the Read/Write operations. If there is a memory error, the SMIF ip block
* can require a reset. To determine if this has happened, check the SMIF
* busy status using Cy_SMIF_BusyCheck() and implement a timeout. Reset the SMIF
* block by toggling CTL.ENABLED. Then reconfigure the SMIF block.
*
* For the Write operation, check that the SMIF driver has completed
* transferring by calling Cy_SMIF_BusyCheck(). Also, check that the memory is
* available with Cy_SMIF_MemIsBusy() before proceeding.
*
* Simple example of external flash memory programming using low level SMIF API.
* All steps mentioned in example below are incorporated in
* \ref Cy_SMIF_MemCmdWriteEnable(), \ref Cy_SMIF_MemCmdProgram(), and
* \ref Cy_SMIF_MemIsBusy() of the
* \ref group_smif_mem_slot_functions "memory slot level API".
* \warning Example is simplified, without checks of error conditions.
* \note Flash memories need erase operation before programming. Refer to
* external memory datasheet for specific memory commands.
*
* \snippet smif/snippet/main.c SMIF_API: Write example
*
* For the Read operation, before accessing the read buffer, check that it is ready
* by calling Cy_SMIF_GetTxFifoStatus().
*
* Simple example of external flash memory read using low level SMIF API. All
* steps mentioned in example below are incorporated in
* \ref Cy_SMIF_MemCmdRead() of the
* \ref group_smif_mem_slot_functions "memory slot level API".
* \warning Example is simplified, without checks of error conditions.
* \note Refer to external memory datasheet for specific memory commands.
*
* \snippet smif/snippet/main.c SMIF_API: Read example
*
* The user should invalidate the cache by calling Cy_SMIF_CacheInvalidate() when
* switching from the MMIO mode to XIP mode.
*
* \section group_smif_configuration Configuration Considerations
*
* PDL API has common parameters: base, context, config described in
* \ref page_getting_started_pdl_design "PDL Design" section.
*
* See the documentation for Cy_SMIF_Init() and Cy_SMIF_MemInit() for details
* on the required configuration structures and other initialization topics.
*
* The normal (MMIO) mode is used for implementing a generic SPI/DSPI/QSPI/dual
* QSPI/octal SPI communication interface using the SMIF block. This
* interface can be used to implement special commands like Program/Erase of
* flash, memory device configuration, sleep mode entry for memory devices or
* other special commands specific to the memory device. The transfer width
* (SPI/DSPI/QSPI/octal SPI) of a transmission is a parameter set for each
* transmit/receive operation. So these can be changed at run time.
*
* In a typical memory interface with flash memory, the SMIF is used in the
* memory mode when reading from the memory and it switches to the normal mode when
* writing to flash memory.
* A typical memory device has multiple types of commands.
*
* The SMIF interface can be used to transmit different types of commands. Each
* command has different phases: command, dummy cycles, and transmit and receive
* data which require separate APIs.
*
* \subsection group_smif_init SMIF Initialization
* Create interrupt function and allocate memory for SMIF context
* structure
* \snippet smif/snippet/main.c SMIF_INIT: context and interrupt
* SMIF driver initialization for low level API usage (cysmif.h)
* \snippet smif/snippet/main.c SMIF_INIT: low level
* Additional steps to initialize SMIF driver for memory slot level API usage
* (cy_smif_memslot.h).
* \snippet smif/snippet/main.c SMIF_INIT: memslot level
* \note Example does not include initialization of all needed configuration
* structures (\ref cy_stc_smif_mem_device_cfg_t, \ref cy_stc_smif_mem_cmd_t).
* SMIF/QSPI Configuration tool generates all configuration structures needed for
* memslot level API usage.
*
* \subsection group_smif_xip_init SMIF XIP Initialization
* The eXecute In Place (XIP) is a mode of operation where read or write commands
* to the memory device are directed through the SMIF without any use of API
* function calls. In this mode the SMIF block maps the AHB bus-accesses to
* external memory device addresses to make it behave similar to internal memory.
* This allows the CPU to execute code directly from external memory. This mode
* is not limited to code and is suitable also for data read and write accesses.
* The memory regions available for XIP addresses allocation are defined
* in a linker script file (.ld).
*
* With SMIF V3 IP, MMIO mode transactions are also allowed when the device is set
* to XIP mode. However, only blocking SMIF API's are expected to be used for erase or
* program operations as external flash will be busy for such operation and may not be
* available for XIP at that moment. Blocking API's will ensure the transaction is complete
* and then switch back to XIP.
*
* \snippet smif/snippet/main.c SMIF_INIT: XIP
* \note Example of input parameters initialization is in \ref group_smif_init
* section.
* \warning Functions that called from external memory should be declared with
* long call attribute.
*
* \subsection group_smif_xip_crypto SMIF XIP On-the-fly encryption
* In XIP mode, a cryptography component supports on-the-fly encryption for write data and
* on-the-fly decryption for read data. On-the-fly encryption/decryption in XIP mode can be
* enabled by setting the flags \ref CY_SMIF_FLAG_CRYPTO_ENABLE.
* Encryption  and  decryption  are  based  on  the  AES-128 forward block cipher: advanced
* encryption standard blockcipher with a 128-bit key. KEY[127:0] is a secret (private) key
* programmed into the CRYPTO_KEY3,...,CRYPTO_KEY0 registers using \ref Cy_SMIF_SetCryptoKey.
* These registers are software write-only. A software read returns 0. In the SMIF hardware,
* by applying AES-128 with KEY[127:0] on a plaintext PT[127:0], we get a ciphertext CT[127:0].
* In XIP mode, the XIP address is used as the plaintext PT[]. The resulting ciphertext CT[]
* is used on-the-fly and not software accessible. The XIP address is extended with the
* CRYPTO_INPUT3, ..., CRYPTO_INPUT0 registers. \ref Cy_SMIF_SetCryptoIV can be used to set
* initialization vector (96-bits).
* In XIP mode, the resulting ciphertext CT[] (of the encrypted address) is XORed with the memory
* transfers read data or write data. Note that the AES-128 block cipher is on the address of the
* data and not on the data itself.
*
* \image html smif_xip_mode_functionality.png
*
* \subsection group_smif_usage_rules Rules for PSoC6 QSPI/SMIF Block Usage
* 1. All operations must use one or more dummy cycles between the PSoC 6 Command
* and Address phase (when the PSoC 6 MCU drives the data pins) and the device's
* Response phase (when the device drives the same data pins). Bus contention may
* occur if no (zero) dummy cycles are used.
* 2. Any transfer that does not allow dummy cycles (such as Register Status
* Reads) must use the single-bit transfer mode. In single-bit mode, the PSoC 6
* drives the Command on the Data0 line and the device responds on the Data1
* line, so bus contention cannot occur.
*
* \section group_smif_more_information More Information
*
* More information regarding the Serial Memory Interface can be found in the component
* datasheet and the Technical Reference Manual (TRM).
* More information regarding the SMIF Configuration Tool are in SMIF
* Configuration Tool User Guide located in \<PDL_DIR\>/tools/\<OS_DIR\>/SMIFConfigurationTool/
* folder
*
* \section group_smif_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td rowspan="4">2.40</td>
*     <td>Enhanced \ref Cy_SMIF_MemEraseSector to compute sector boundary for erase operation and \n
*         Minor Bug fixes.
*      </td>
*     <td>Code Enhancements.</td>
*   </tr>
*   <tr>
*     <td>Added new API \ref Cy_SMIF_MemCmdPowerDown and \ref Cy_SMIF_MemCmdReleasePowerDown.</td>
*     <td>Reduce power consumption.</td>
*   </tr>
*   <tr>
*     <td>Added new API \ref Cy_SMIF_DeviceTransfer_SetMergeTimeout and \ref Cy_SMIF_DeviceTransfer_ClearMergeTimeout.</td>
*     <td>Allow user to configure merge timeout.</td>
*   </tr>
*   <tr>
*     <td>Removed Bridge API support.</td>
*     <td>Removed feature not supported in existing devices.</td>
*   </tr>
*   <tr>
*     <td rowspan="5">2.30</td>
*     <td>Octal SDR and DDR support using SFDP mode.</td>
*     <td>Octal device support.</td>
*   </tr>
*   <tr>
*     <td>Move SFDP related functionality to cy_smif_sfdp.c. </td>
*     <td>Code Enhancements.</td>
*   </tr>
*   <tr>
*     <td>Added support for new product families</td>
*     <td>Support for CAT1B and CAT1C devices.</td>
*   </tr>
*   <tr>
*     <td>Added new API's:\n
*         \ref Cy_SMIF_MemInitSfdpMode()\n
*         \ref Cy_SMIF_SetCryptoIV()\n
*         \ref Cy_SMIF_SetCryptoKey()\n
*         \ref Cy_SMIF_ConvertSlaveSlotToIndex()\n
*         \ref Cy_SMIF_SetCryptoEnable()\n
*         \ref Cy_SMIF_SetCryptoDisable()\n
*         \ref Cy_SMIF_SetReadyPollingDelay()\n
*
*         Following macros renamed:\n
*         CY_SMIF_WRITE_STATUS_REG2_CMD to CY_SMIF_WRITE_STATUS_REG2_T1_CMD.</td>
*     <td>Support for SFDP 1.0 devices.</td>
*   </tr>
*   <tr>
*     <td>Added new API's for CAT1D devices\n
*         \ref Cy_SMIF_SetRxCaptureMode()\n
*         Cy_SMIF_Bridge_Enable()\n
*         Cy_SMIF_Bridge_SetPortPriority()\n
*         Cy_SMIF_Bridge_SetSimpleRemapRegion()\n
*         Cy_SMIF_Bridge_SetInterleavingRemapRegion()\n
*         \ref Cy_SMIF_MemOctalEnable()\n
      </td>
*     <td>Support for CAT1D devices.</td>
*   </tr>
*   <tr>
*     <td>2.20</td>
*     <td>Bug fixes in \ref Cy_SMIF_MemEraseSector for Hybrid memory configuration.
*         Updated \ref Cy_SMIF_MemIsReady to use \ref Cy_SysLib_Rtos_Delay and \ref Cy_SysLib_Rtos_DelayUs.</td>
*     <td>Code enhancement.</td>
*   </tr>
*   <tr>
*     <td>2.10</td>
*     <td>New silicon family support.</td>
*     <td>Added extended API for DDR support.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">2.0</td>
*     <td>Reworked the \ref Cy_SMIF_MemRead and \ref Cy_SMIF_MemWrite functions to use polling instead of interrupts.</td>
*     <td>Extend the usability of these functions.</td>
*   </tr>
*   <tr>
*    <td>Reworked the length-parameter check in the \ref Cy_SMIF_MemEraseSector function.
*     The Erase operation is not performed and \ref CY_SMIF_SUCCESS is no longer returned when the sectors are not aligned.</td>
*     <td>Fix the user error-handling of the length parameter.</td>
*   </tr>
*   <tr>
*    <td>Fixed the address-parameter check in the \ref Cy_SMIF_MemLocateHybridRegion function.
*     \ref CY_SMIF_SUCCESS or \ref CY_SMIF_NOT_HYBRID_MEM is no longer returned when the address exceeds the memory size.</td>
*     <td>Address a defect.</td>
*   </tr>
*   <tr>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.50.1</td>
*     <td>Minor documentation updates. </td>
*     <td>Documentation improvement. </td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>Added a new function: \ref Cy_SMIF_MemLocateHybridRegion.\n
*     Added a new structure \ref cy_stc_smif_hybrid_region_info_t.\n
*     Updated the \ref Cy_SMIF_MemEraseSector and \ref Cy_SMIF_MemCmdSectorErase functions.\n
*     Updated the \ref Cy_SMIF_MemSfdpDetect function. \n
*     Updated the \ref cy_stc_smif_mem_device_cfg_t structure.</td>
*     <td>Support for memories with hybrid regions.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.40.1</td>
*     <td>The \ref Cy_SMIF_MemInit is changed. </td>
*     <td>Corrected a false assertion during initialization in SFDP mode.</td>
*   </tr>
*   <tr>
*     <td>Minor documentation updates. </td>
*     <td></td>
*   </tr>
*   <tr>
*     <td rowspan="5">1.40</td>
*     <td>The following functions are renamed:\n
*        Cy_SMIF_GetTxfrStatus into Cy_SMIF_GetTransferStatus;\n
*        Cy_SMIF_Memslot_Init into Cy_SMIF_MemInit;\n
*        Cy_SMIF_Memslot_DeInit into Cy_SMIF_MemDeInit;\n
*        Cy_SMIF_Memslot_CmdWriteEnable into Cy_SMIF_MemCmdWriteEnable;\n
*        Cy_SMIF_Memslot_CmdWriteDisable into Cy_SMIF_MemCmdWriteDisable;\n
*        Cy_SMIF_Memslot_IsBusy into Cy_SMIF_MemIsBusy;\n
*        Cy_SMIF_Memslot_QuadEnable into Cy_SMIF_MemQuadEnable;\n
*        Cy_SMIF_Memslot_CmdReadSts into Cy_SMIF_MemCmdReadStatus;\n
*        Cy_SMIF_Memslot_CmdWriteSts into Cy_SMIF_MemCmdWriteStatus;\n
*        Cy_SMIF_Memslot_CmdChipErase into Cy_SMIF_MemCmdChipErase;\n
*        Cy_SMIF_Memslot_CmdSectorErase into Cy_SMIF_MemCmdSectorErase;\n
*        Cy_SMIF_Memslot_SfdpDetect into Cy_SMIF_MemSfdpDetect;\n
*        Cy_SMIF_Memslot_CmdProgram into Cy_SMIF_MemCmdProgram;\n
*        Cy_SMIF_Memslot_CmdRead into Cy_SMIF_MemCmdRead.\n
*          The following ENUMa are renamed:\n
*        CY_SMIF_SEND_CMPLT into CY_SMIF_SEND_COMPLETE;\n
*        CY_SMIF_REC_CMPLT into CY_SMIF_RX_COMPLETE;\n
*        CY_SMIF_REC_BUSY into CY_SMIF_RX_BUSY;\n
*        CY_SMIF_SEL_INV_INTERNAL_CLK into CY_SMIF_SEL_INVERTED_INTERNAL_CLK;\n
*        CY_SMIF_SEL_INV_FEEDBACK_CLK into CY_SMIF_SEL_INVERTED_FEEDBACK_CLK;\n
*        cy_en_smif_cache_en_t into cy_en_smif_cache_t.\n
*          The following MACROs are renamed:\n
*        CY_SMIF_FLAG_WR_EN into CY_SMIF_FLAG_WRITE_ENABLE;\n
*        CY_SMIF_FLAG_CRYPTO_EN into CY_SMIF_FLAG_CRYPTO_ENABLE;\n
*        CY_SMIF_SFDP_SING_BYTE_00 into CY_SMIF_SFDP_SIGNATURE_BYTE_00;\n
*        CY_SMIF_SFDP_SING_BYTE_01 into CY_SMIF_SFDP_SIGNATURE_BYTE_01;\n
*        CY_SMIF_SFDP_SING_BYTE_02 into CY_SMIF_SFDP_SIGNATURE_BYTE_02;\n
*        CY_SMIF_SFDP_SING_BYTE_03 into CY_SMIF_SFDP_SIGNATURE_BYTE_03;\n
*        CY_SMIF_WR_STS_REG1_CMD into CY_SMIF_WRITE_STATUS_REG1_CMD;\n
*        CY_SMIF_WR_DISABLE_CMD into CY_SMIF_WRITE_DISABLE_CMD;\n
*        CY_SMIF_RD_STS_REG1_CMD into CY_SMIF_READ_STATUS_REG1_CMD;\n
*        CY_SMIF_WR_ENABLE_CMD into CY_SMIF_WRITE_ENABLE_CMD;\n
*        CY_SMIF_RD_STS_REG2_T1_CMD into CY_SMIF_READ_STATUS_REG2_T1_CMD;\n
*        CY_SMIF_WR_STS_REG2_CMD into CY_SMIF_WRITE_STATUS_REG2_CMD;\n
*        CY_SMIF_RD_STS_REG2_T2_CMD into CY_SMIF_READ_STATUS_REG2_T2_CMD;\n
*        CY_SMIF_QE_BIT_STS_REG2_T1 into CY_SMIF_QE_BIT_STATUS_REG2_T1;\n
*        CY_SMIF_STS_REG_BUSY_MASK into CY_SMIF_STATUS_REG_BUSY_MASK.\n
*      </td>
*      <td rowspan="2">Documentation improvement.</td>
*   </tr>
*   <tr>
*     <td>Updated the description of the Cy_SMIF_MemInit() function.
*         Updated the Cy_SMIF_Encrypt() function usage example.
*     </td>
*   </tr>
*   <tr>
*     <td>The type of arguments that are not modified by the functions are set to const.
*     </td>
*     <td>Usability improvement.
*     </td>
*   </tr>
*   <tr>
*     <td>The Cy_SMIF_MemSfdpDetect() function is updated to support new
*         commands for 4 bytes addressing.
*     </td>
*     <td>Memory devices with new 4 byte addressing commands support.
*     </td>
*   </tr>
*   <tr>
*     <td>Added the blocking functions which take care of the
*         busy-status check of the memory:
*         - \ref  Cy_SMIF_MemIsReady
*         - \ref  Cy_SMIF_MemIsQuadEnabled
*         - \ref  Cy_SMIF_MemEnableQuadMode
*         - \ref  Cy_SMIF_MemRead
*         - \ref  Cy_SMIF_MemWrite
*         - \ref  Cy_SMIF_MemEraseSector
*         - \ref  Cy_SMIF_MemEraseChip
*     </td>
*     <td>Added new high-level blocking functions.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="5">1.30</td>
*     <td>The CY_SMIF_CMD_FIFO_WR_RX_COUNT_Msk value is changed to 0x0000FFFFUL.</td>
*     <td rowspan="4">Driver maintenance.</td>
*   </tr>
*   <tr>
*     <td>Added the check of the size parameter in the Cy_SMIF_TransmitData() function.</td>
*   </tr>
*   <tr>
*     <td>Added conditional check for presence of the SMIF hardware IP.</td>
*   </tr>
*   <tr>
*     <td>Fixed the wrong erase command in the SFDP protocol for devices with Erase Type 3.</td>
*   </tr>
*   <tr>
*     <td>Updated the General Description section with minor changes.
*         Updated the ordering of the parameters descriptions for some functions.
*         Added the text saying that the Cy_SMIF_MemInit() function is applicable
*      to use the external memory as memory-mapped to PSoC (XIP mode).
*         Added the snippet for the Cy_SMIF_Encrypt() function to show how to use this function.
*         Added below the picture in the Low-Level Functions section the sequence of PDL
*      functions required in a Read or Write transaction.
*         Added the text below the picture about the address.
*         Updated DUMMY COUNT in this picture.
*         Added checking of the size parameter in the Cy_SMIF_TransmitData() function.
*     </td>
*     <td>Documentation improvement.</td>
*   </tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>Added upper limit to size parameter in several functions.</td>
*     <td>Documentation improvement.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added a new return status and transfer width option for the case when the memory command is not supported.</td>
*     <td>Improved the memory command structure usability.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.11</td>
*     <td>Fixed internal function that writes to the SMIF FIFO</td>
*     <td>The write function stuck in the loop when write speed in external
*         memory is significantly lower than PSoC CPU core speed and write
*         transfer is not finished during the single function call.
*     </td>
*   </tr>
*   <tr>
*     <td>Added optional mode part to the program command flow</td>
*     <td>Extend usability of program command</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Added Low Power Callback section</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Fix write to external memory from CM0+ core. Add checks of API input parameters.
*         Minor documentation updates</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_smif_macros Macros
* \{
* \defgroup group_smif_macros_status Status Macros
* \defgroup group_smif_macros_cmd Command Macros
* \defgroup group_smif_macros_flags External Memory Flags
* \defgroup group_smif_macros_sfdp SFDP Macros
* \defgroup group_smif_macros_isr Interrupt Macros
* \}
* \defgroup group_smif_functions Functions
* \{
* \defgroup group_smif_low_level_functions Low Level Functions
* \{
* The SMIF interface can be used to transmit different types of commands.
* Each command has different phases: command, dummy cycles, and transmit and receive data which require separate APIs.
*
* During the time that Slave Select line is active (LOW) the clock signal (CLK) is toggled while command information is first
* transferred on the data (IO) signals from the master to the slave. The clock continues to toggle during any period required for
* information access in the slave. The clock continues to toggle during the transfer of read data from the slave to the master
* or write data from the master to the slave. When the master has transferred the desired amount of data, the master drives the
* Slave Select line inactive (HIGH).
* Basic flow for read/write commands using \ref Cy_SMIF_TransmitCommand, \ref Cy_SMIF_TransmitData, \ref Cy_SMIF_ReceiveData and
* \ref Cy_SMIF_SendDummyCycles with a Quad SPI interface.
*
*  \image html smif_1_0_p03_rw_cmd.png
*
* The sequence of the PDL functions required in a read or write transaction is:
* \ref Cy_SMIF_TransmitCommand() ->
* \ref Cy_SMIF_SendDummyCycles() ->
* \ref Cy_SMIF_ReceiveData() / \ref Cy_SMIF_TransmitData() ->
* \ref Cy_SMIF_BusyCheck().
* The address is sent as part of the Cy_SMIF_TransmitCommand() function.
* No separate function call is required.
*
* \}
* \defgroup group_smif_mem_slot_functions Memory Slot Functions
* \defgroup group_smif_functions_syspm_callback  Low Power Callback
* \}
* \defgroup group_smif_data_structures Data Structures
* \{
* \defgroup group_smif_data_structures_memslot SMIF Memory Description Structures
* General hierarchy of memory structures are:
*
* \image html smif_3_0_p02_memslot_stc.png
*
* \note
* Above image is applicable only for SMIF v3 IP.
*
* \image html smif_1_0_p02_memslot_stc.png
*
* \note
* Above image is applicable only for SMIF v1 IP.
*
* Top structure is \ref cy_stc_smif_block_config_t, which could have links up to
* 4 \ref cy_stc_smif_mem_config_t which describes each connected to the SMIF
* external memory.
* \}
* \defgroup group_smif_enums Enumerated Types
*/

#if !defined (CY_SMIF_H)
#define CY_SMIF_H

#include "cy_device.h"

#if defined (CY_IP_MXSMIF)

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*            Constants
****************************************/

/**
* \addtogroup group_smif_macros
* \{
*/

/** The driver major version */
#define CY_SMIF_DRV_VERSION_MAJOR       2

/** The driver minor version */
#define CY_SMIF_DRV_VERSION_MINOR       40

/** One microsecond timeout for Cy_SMIF_TimeoutRun() */
#define CY_SMIF_WAIT_1_UNIT             (1U)

/** The SMIF driver ID, reported as part of an unsuccessful API return status
 * \ref cy_en_smif_status_t */
#define CY_SMIF_ID                      CY_PDL_DRV_ID(0x2CUL)


/**
* \addtogroup group_smif_macros_isr
* \{
*/

/** Enable XIP_ALIGNMENT_ERROR interrupt see TRM for details */
#define CY_SMIF_ALIGNMENT_ERROR                 (SMIF_INTR_XIP_ALIGNMENT_ERROR_Msk)
/** Enable RX_DATA_FIFO_UNDERFLOW interrupt see TRM for details */
#define CY_SMIF_RX_DATA_FIFO_UNDERFLOW          (SMIF_INTR_RX_DATA_FIFO_UNDERFLOW_Msk)
/** Enable TX_DATA_FIFO_OVERFLOW interrupt see TRM for details */
#define CY_SMIF_TX_DATA_FIFO_OVERFLOW           (SMIF_INTR_TX_DATA_FIFO_OVERFLOW_Msk)
/** Enable TX_CMD_FIFO_OVERFLOW interrupt see TRM for details */
#define CY_SMIF_TX_COMMAND_FIFO_OVERFLOW        (SMIF_INTR_TX_CMD_FIFO_OVERFLOW_Msk)
/** Enable TR_TX_REQ interrupt see TRM for details */
#define CY_SMIF_TX_DATA_FIFO_LEVEL_TRIGGER      (SMIF_INTR_TR_TX_REQ_Msk)
/** Enable TR_RX_REQ interrupt see TRM for details */
#define CY_SMIF_RX_DATA_FIFO_LEVEL_TRIGGER      (SMIF_INTR_TR_RX_REQ_Msk)

/** \} group_smif_macros_isr */

/** \cond INTERNAL */

#if ((CY_IP_MXSMIF_VERSION==2) || (CY_IP_MXSMIF_VERSION==3))
#define SMIF_INTR_RX_DATA_FIFO_UNDERFLOW_Msk SMIF_INTR_RX_DATA_MMIO_FIFO_UNDERFLOW_Msk
#define SMIF_RX_DATA_FIFO_CTL SMIF_RX_DATA_MMIO_FIFO_CTL
#define SMIF_RX_DATA_FIFO_RD4 SMIF_RX_DATA_MMIO_FIFO_RD4
#define SMIF_RX_DATA_FIFO_RD1 SMIF_RX_DATA_MMIO_FIFO_RD1
#define SMIF_RX_DATA_FIFO_RD2 SMIF_RX_DATA_MMIO_FIFO_RD2
#endif /* CY_IP_MXSMIF_VERSION */

#if (CY_IP_MXSMIF_VERSION==2)
 /* SMIF IP V2 do not use register name MMIO */
#define SMIF_TX_CMD_MMIO_FIFO_WR        SMIF_TX_CMD_FIFO_WR
#define SMIF_TX_DATA_MMIO_FIFO_WR1ODD   SMIF_TX_DATA_FIFO_WR1ODD
#define SMIF_TX_DATA_MMIO_FIFO_WR1      SMIF_TX_DATA_FIFO_WR1
#endif

#if (CY_IP_MXSMIF_VERSION==3)
#define SMIF_TX_DATA_FIFO_CTL SMIF_TX_DATA_MMIO_FIFO_CTL
#define SMIF_TX_DATA_FIFO_WR4 SMIF_TX_DATA_MMIO_FIFO_WR4
#define SMIF_TX_DATA_FIFO_WR1 SMIF_TX_DATA_MMIO_FIFO_WR1
#define SMIF_TX_DATA_FIFO_WR2 SMIF_TX_DATA_MMIO_FIFO_WR2
#define SMIF_CRYPTO_CMD_START_Msk SMIF_SMIF_CRYPTO_CRYPTO_CMD_START_Msk
#define SMIF_CRYPTO_CMD_START_Pos SMIF_SMIF_CRYPTO_CRYPTO_CMD_START_Pos
#endif /* CY_IP_MXSMIF_VERSION */

#define CY_SMIF_CMD_FIFO_TX_MODE            (0UL)
#define CY_SMIF_CMD_FIFO_TX_COUNT_MODE      (1UL)
#define CY_SMIF_CMD_FIFO_RX_COUNT_MODE      (2UL)
#define CY_SMIF_CMD_FIFO_DUMMY_COUNT_MODE   (3UL)

#if (CY_IP_MXSMIF_VERSION>=2)
#define CY_SMIF_TX_CMD_FIFO_STATUS_RANGE    (8U)
#else
#define CY_SMIF_TX_CMD_FIFO_STATUS_RANGE    (4U)
#endif /* CY_IP_MXSMIF_VERSION */

#define CY_SMIF_TX_DATA_FIFO_STATUS_RANGE   (8U)
#define CY_SMIF_RX_DATA_FIFO_STATUS_RANGE   (8U)

#define CY_SMIF_ONE_BYTE                    (1U)
#define CY_SMIF_TWO_BYTES                   (2U)
#define CY_SMIF_THREE_BYTES                 (3U)
#define CY_SMIF_FOUR_BYTES                  (4U)
#define CY_SMIF_FIVE_BYTES                  (5U)
#define CY_SMIF_SIX_BYTES                   (6U)
#define CY_SMIF_SEVEN_BYTES                 (7U)
#define CY_SMIF_EIGHT_BYTES                 (8U)

#define CY_SMIF_CRYPTO_FIRST_WORD           (0U)
#define CY_SMIF_CRYPTO_SECOND_WORD          (4U)
#define CY_SMIF_CRYPTO_THIRD_WORD           (8U)
#define CY_SMIF_CRYPTO_FOURTH_WORD          (12U)

#define CY_SMIF_CRYPTO_START                (1UL)
#define CY_SMIF_CRYPTO_COMPLETED            (0UL)
#define CY_SMIF_CRYPTO_ADDR_MASK            (0xFFFFFFF0UL)
#define CY_SMIF_AES128_BYTES                (16U)

#define CY_SMIF_CTL_REG_DEFAULT             (0x00000300U) /* 3 - [13:12] CLOCK_IF_RX_SEL  */

#define CY_SMIF_SFDP_FAIL                   (0x08U)
#define CY_SMIF_SFDP_FAIL_SS0_POS           (0x00U)
#define CY_SMIF_SFDP_FAIL_SS1_POS           (0x01U)
#define CY_SMIF_SFDP_FAIL_SS2_POS           (0x02U)
#define CY_SMIF_SFDP_FAIL_SS3_POS           (0x03U)

#define CY_SMIF_MAX_DESELECT_DELAY          (7U)
#define CY_SMIF_MAX_TX_TR_LEVEL             (8U)
#define CY_SMIF_MAX_RX_TR_LEVEL             (8U)

#define CY_SMIF_MODE_VALID(mode)            ((CY_SMIF_NORMAL == (cy_en_smif_mode_t)(mode)) || \
                                             (CY_SMIF_MEMORY == (cy_en_smif_mode_t)(mode)))
#define CY_SMIF_BLOCK_EVENT_VALID(event)    ((CY_SMIF_BUS_ERROR == (cy_en_smif_error_event_t)(event)) || \
                                             (CY_SMIF_WAIT_STATES == (cy_en_smif_error_event_t)(event)))
#if (CY_IP_MXSMIF_VERSION>=2)
#define CY_SMIF_CLOCK_SEL_VALID(clkSel)     ((CY_SMIF_SEL_OUTPUT_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INVERTED_OUTPUT_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INTERNAL_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INVERTED_INTERNAL_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_FEEDBACK_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INVERTED_FEEDBACK_CLK == (cy_en_smif_clk_select_t)(clkSel)))
#else
#define CY_SMIF_CLOCK_SEL_VALID(clkSel)     ((CY_SMIF_SEL_INTERNAL_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INVERTED_INTERNAL_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_FEEDBACK_CLK == (cy_en_smif_clk_select_t)(clkSel)) || \
                                             (CY_SMIF_SEL_INVERTED_FEEDBACK_CLK == (cy_en_smif_clk_select_t)(clkSel)))
#endif /* CY_IP_MXSMIF_VERSION */

#define CY_SMIF_DESELECT_DELAY_VALID(delay) ((delay) <= CY_SMIF_MAX_DESELECT_DELAY)
#define CY_SMIF_SLAVE_SEL_VALID(ss)         ((CY_SMIF_SLAVE_SELECT_0 == (ss)) || \
                                             (CY_SMIF_SLAVE_SELECT_1 == (ss)) || \
                                             (CY_SMIF_SLAVE_SELECT_2 == (ss)) || \
                                             (CY_SMIF_SLAVE_SELECT_3 == (ss)))
#define CY_SMIF_DATA_SEL_VALID(ss)          ((CY_SMIF_DATA_SEL0 == (ss)) || \
                                             (CY_SMIF_DATA_SEL1 == (ss)) || \
                                             (CY_SMIF_DATA_SEL2 == (ss)) || \
                                             (CY_SMIF_DATA_SEL3 == (ss)))
#define CY_SMIF_TXFR_WIDTH_VALID(width)     ((CY_SMIF_WIDTH_SINGLE == (width)) || \
                                             (CY_SMIF_WIDTH_DUAL == (width))   || \
                                             (CY_SMIF_WIDTH_QUAD == (width))   || \
                                             (CY_SMIF_WIDTH_OCTAL == (width))  || \
                                             (CY_SMIF_WIDTH_NA == (width)))
#define CY_SMIF_CMD_PARAM_VALID(param, paramSize)  (((paramSize) > 0U)? (NULL != (param)) : (true))

#define CY_SMIF_WIDTH_NA_VALID(paramWidth, paramSize)   (((paramSize) > 0U)? \
                                                         (CY_SMIF_WIDTH_NA != (paramWidth)) : (true))
#define CY_SMIF_CMD_DATA_RATE_VALID(rate)   ((CY_SMIF_SDR == (rate)) || \
                                             (CY_SMIF_DDR == (rate)))
#define CY_SMIF_CMD_PARAM_DATA_RATE_VALID(rate)   ((CY_SMIF_SDR == (rate)) || \
                                                    (CY_SMIF_DDR == (rate)))
#define CY_SMIF_DATA_DATA_RATE_VALID(rate)   ((CY_SMIF_SDR == (rate)) || \
                                               (CY_SMIF_DDR == (rate)))

#define CY_SMIF_BUFFER_SIZE_MAX             (65536UL)
#define CY_SMIF_BUF_SIZE_VALID(size)        (((CY_SMIF_BUFFER_SIZE_MAX) >= (size)) && ((0UL) < (size)))

/***************************************
*        Command FIFO Register
***************************************/

#if (CY_IP_MXSMIF_VERSION>=2)
/* SMIF->TX_CMD_FIFO_MMIO_WR Commands Fields */
#define CY_SMIF_CMD_MMIO_FIFO_WR_MODE_Pos            (24UL)           /* [26:24]         Command data mode */
#define CY_SMIF_CMD_MMIO_FIFO_WR_MODE_Msk            (0x07000000UL)   /* DATA[26:24]       Command data mode    */

#define CY_SMIF_CMD_MMIO_FIFO_WR_SS_Pos              (20UL)           /* [23:20]         Slave select         */
#define CY_SMIF_CMD_MMIO_FIFO_WR_SS_Msk              (0x00F00000UL)   /* DATA[23:20]     Slave select         */

#define CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE_Pos       (19UL)           /* [19]            Last byte            */
#define CY_SMIF_CMD_MMIO_FIFO_WR_LAST_BYTE_Msk       (0x00080000UL)   /* DATA[19]        Last byte               */

#define CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE_Pos       (18UL)           /* [18]         Data Rate         */
#define CY_SMIF_CMD_MMIO_FIFO_WR_DATA_RATE_Msk       (0x00040000UL)   /* DATA[18]     Data Rate         */

#define CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH_Pos           (16UL)           /* [17:16]         Transfer width       */
#define CY_SMIF_CMD_MMIO_FIFO_WR_WIDTH_Msk           (0x00030000UL)   /* DATA[17:16]     Transfer width  */

#define CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2_Pos   (8UL)            /* [15:8] */
#define CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_2_Msk   (0x0000FF00UL)   /* DATA[15:8] second byte */

#define CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1_Pos   (0UL)            /* [7:0]         first byte         */
#define CY_SMIF_CMD_MMIO_FIFO_WR_TXDATA_BYTE_1_Msk   (0x000000FFUL)   /* DATA[7:0]     first byte         */

#define CY_SMIF_CMD_MMIO_FIFO_WR_DUMMY_Pos           (0UL)            /* [0]             Dummy count          */
#define CY_SMIF_CMD_MMIO_FIFO_WR_DUMMY_Msk           (0x0000FFFFUL)   /* DATA[15:0]      Dummy count          */

#define CY_SMIF_CMD_MMIO_FIFO_WR_TX_COUNT_Msk        (0x0000FFFFUL)   /* DATA[15:0]      TX count             */
#define CY_SMIF_CMD_MMIO_FIFO_WR_TX_COUNT_Pos        (0UL)            /* [0]             TX count             */

#define CY_SMIF_CMD_MMIO_FIFO_WR_RX_COUNT_Msk        (0x0000FFFFUL)   /* DATA[15:0]      RX count             */
#define CY_SMIF_CMD_MMIO_FIFO_WR_RX_COUNT_Pos        (0UL)            /* [0]             RX count             */
#else
/* SMIF->TX_CMD_FIFO_WR  */
#define CY_SMIF_TX_CMD_FIFO_WR_MODE_POS         (18U)   /* [19:18]  Command data mode */
#define CY_SMIF_TX_CMD_FIFO_WR_WIDTH_POS        (16U)   /* [17:16]  Transfer width    */
#define CY_SMIF_TX_CMD_FIFO_WR_LAST_BYTE_POS    (15U)   /* [15]     Last byte      */
#define CY_SMIF_TX_CMD_FIFO_WR_SS_POS           (8U)    /* [11:8]   Slave select      */
#define CY_SMIF_TX_CMD_FIFO_WR_TXDATA_POS       (0U)    /* [0]      Transmitted byte  */
#define CY_SMIF_TX_CMD_FIFO_WR_DUMMY_POS        (0U)    /* [0]      Dummy count       */
#define CY_SMIF_TX_CMD_FIFO_WR_TX_COUNT_POS     (0U)    /* [0]      TX count          */
#define CY_SMIF_TX_CMD_FIFO_WR_RX_COUNT_POS     (0U)    /* [0]      RX count          */

/* SMIF->TX_CMD_FIFO_WR Commands Fields */
#define CY_SMIF_CMD_FIFO_WR_MODE_Pos            (18UL)           /* [19:18]         Command data mode */
#define CY_SMIF_CMD_FIFO_WR_MODE_Msk            (0x000C0000UL)   /* DATA[19:18]       Command data mode    */

#define CY_SMIF_CMD_FIFO_WR_WIDTH_Pos           (16UL)           /* [17:16]         Transfer width       */
#define CY_SMIF_CMD_FIFO_WR_WIDTH_Msk           (0x00030000UL)   /* DATA[17:16]     Transfer width       */

#define CY_SMIF_CMD_FIFO_WR_LAST_BYTE_Pos       (15UL)           /* [15]            Last byte            */
#define CY_SMIF_CMD_FIFO_WR_LAST_BYTE_Msk       (0x00008000UL)   /* DATA[15]        Last byte            */

#define CY_SMIF_CMD_FIFO_WR_SS_Pos              (8UL)            /* [11:8]          Slave select         */
#define CY_SMIF_CMD_FIFO_WR_SS_Msk              (0x00000F00UL)   /* DATA[11:8]      Slave select         */

#define CY_SMIF_CMD_FIFO_WR_TXDATA_Pos          (0UL)            /* [0]             Transmitted byte     */
#define CY_SMIF_CMD_FIFO_WR_TXDATA_Msk          (0x000000FFUL)   /* DATA[7:0]         Transmitted byte     */
#define CY_SMIF_CMD_FIFO_WR_DUMMY_Pos           (0UL)            /* [0]             Dummy count          */
#define CY_SMIF_CMD_FIFO_WR_DUMMY_Msk           (0x0000FFFFUL)   /* DATA[15:0]      Dummy count          */
#define CY_SMIF_CMD_FIFO_WR_TX_COUNT_Msk        (0x0000FFFFUL)   /* DATA[15:0]      TX count             */
#define CY_SMIF_CMD_FIFO_WR_TX_COUNT_Pos        (0UL)            /* [0]             TX count             */
#define CY_SMIF_CMD_FIFO_WR_RX_COUNT_Msk        (0x0000FFFFUL)   /* DATA[15:0]      RX count             */
#define CY_SMIF_CMD_FIFO_WR_RX_COUNT_Pos        (0UL)            /* [0]             RX count             */
#endif /* CY_IP_MXSMIF_VERSION */

#if (CY_IP_MXSMIF_VERSION == 5u)
#define CY_SMIF_CORE_0_HF 3U
#define CY_SMIF_CORE_1_HF 4U
#endif

/** \endcond */
/** \} group_smif_macros */


/**
* \addtogroup group_smif_enums
* \{
*/

/** The Transfer width options for the command, data, the address and the mode. */
typedef enum
{
    CY_SMIF_WIDTH_SINGLE   = 0U,    /**< Single SPI mode. */
    CY_SMIF_WIDTH_DUAL     = 1U,    /**< Dual SPI mode. */
    CY_SMIF_WIDTH_QUAD     = 2U,    /**< Quad SPI mode. */
    CY_SMIF_WIDTH_OCTAL    = 3U,    /**< Octal SPI mode. */
    CY_SMIF_WIDTH_NA       = 0xFFU  /**< The specific width parameter is not applicable for this memory command. */
} cy_en_smif_txfr_width_t;

/** The SMIF error-event selection. */
typedef enum
{
    /**< Generates a bus error. */
    CY_SMIF_BUS_ERROR           = 0UL,
    /** Stalls the bus with the wait states. This option will increase the
     * interrupt latency.
     */
    CY_SMIF_WAIT_STATES         = 1UL
} cy_en_smif_error_event_t;

/** The data line-selection options for a slave device. */
typedef enum
{
    /**
    * smif.spi_data[0] = DATA0, smif.spi_data[1] = DATA1, ..., smif.spi_data[7] = DATA7.
    * This value is allowed for the SPI, DSPI, QSPI, dual QSPI, and octal SPI modes.
    */
    CY_SMIF_DATA_SEL0      = 0,
    /**
    * smif.spi_data[2] = DATA0, smif.spi_data[3] = DATA1.
    * This value is only allowed for the SPI and DSPI modes.
    */
    CY_SMIF_DATA_SEL1      = 1,
    /**
    * smif.spi_data[4] = DATA0, smif.spi_data[5] = DATA1, ..., smif.spi_data[7] = DATA3.
    * This value is only allowed for the SPI, DSPI, QSPI and dual QSPI modes.
    */
    CY_SMIF_DATA_SEL2      = 2,
    /**
    * smif.spi_data[6] = DATA0, smif.spi_data[7] = DATA1.
    * This value is only allowed for the SPI and DSPI modes.
    */
    CY_SMIF_DATA_SEL3      = 3
} cy_en_smif_data_select_t;

/** The SMIF modes to work with an external memory. */
typedef enum
{
    CY_SMIF_NORMAL,         /**< Command mode (MMIO mode). */
    CY_SMIF_MEMORY          /**< XIP (eXecute In Place) mode. */
} cy_en_smif_mode_t;

/** The SMIF transfer status return values. */
typedef enum
{
    CY_SMIF_STARTED,       /**< The SMIF started. */
    CY_SMIF_SEND_COMPLETE, /**< The data transmission is complete. */
    CY_SMIF_SEND_BUSY,     /**< The data transmission is in progress. */
    CY_SMIF_RX_COMPLETE,   /**< The data reception is completed. */
    CY_SMIF_RX_BUSY,       /**< The data reception is in progress. */
    CY_SMIF_XIP_ERROR,     /**< An XIP alignment error. */
    CY_SMIF_CMD_ERROR,     /**< A TX CMD FIFO overflow. */
    CY_SMIF_TX_ERROR,      /**< A TX DATA FIFO overflow. */
    CY_SMIF_RX_ERROR       /**< An RX DATA FIFO underflow. */

} cy_en_smif_txfr_status_t;

/** The SMIF API return values. */
typedef enum
{
    CY_SMIF_SUCCESS = 0x00U,           /**< Successful SMIF operation. */
    CY_SMIF_CMD_FIFO_FULL   = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x01U,     /**< The command is cancelled. The command FIFO is full. */
    CY_SMIF_EXCEED_TIMEOUT  = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x02U,    /**< The SMIF operation timeout exceeded. */
    /**
    * The device does not have a QE bit. The device detects
    * 1-1-4 and 1-4-4 Reads based on the instruction.
    */
    CY_SMIF_NO_QE_BIT       = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x03U,
    CY_SMIF_BAD_PARAM       = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x04U,   /**< The SMIF API received the wrong parameter */
    CY_SMIF_NO_SFDP_SUPPORT = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x05U,   /**< The external memory does not support SFDP (JESD216B). */
    CY_SMIF_NOT_HYBRID_MEM  = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x06U,   /**< The external memory is not hybrid */
    CY_SMIF_SFDP_CORRUPTED_TABLE = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x07U, /**< The SFDP table is corrupted */
    /** Failed to initialize the slave select 0 external memory by auto detection (SFDP). */
    CY_SMIF_SFDP_SS0_FAILED = CY_SMIF_ID |CY_PDL_STATUS_ERROR |
                            ((uint32_t)CY_SMIF_SFDP_FAIL << CY_SMIF_SFDP_FAIL_SS0_POS),
    /** Failed to initialize the slave select 1 external memory by auto detection (SFDP). */
    CY_SMIF_SFDP_SS1_FAILED = CY_SMIF_ID | CY_PDL_STATUS_ERROR |
                            ((uint32_t)CY_SMIF_SFDP_FAIL << CY_SMIF_SFDP_FAIL_SS1_POS),
    /** Failed to initialize the slave select 2 external memory by auto detection (SFDP). */
    CY_SMIF_SFDP_SS2_FAILED = CY_SMIF_ID |CY_PDL_STATUS_ERROR |
                            ((uint32_t)CY_SMIF_SFDP_FAIL << CY_SMIF_SFDP_FAIL_SS2_POS),
    /** Failed to initialize the slave select 3 external memory by auto detection (SFDP). */
    CY_SMIF_SFDP_SS3_FAILED = CY_SMIF_ID |CY_PDL_STATUS_ERROR |
                            ((uint32_t)CY_SMIF_SFDP_FAIL << CY_SMIF_SFDP_FAIL_SS3_POS),
    /** The command API is not supported for this memory device. */
    CY_SMIF_CMD_NOT_FOUND = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x80U,
    /** SFDP Buffer Insufficient. */
    CY_SMIF_SFDP_BUFFER_INSUFFICIENT = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x81U,
    /**
    * The device does not have a OE bit. The device detects
    * 1-1-8 and 1-8-8 Reads based on the instruction.
    */
    CY_SMIF_NO_OE_BIT       = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x82U,
    /** SMIF is currently busy and cannot accept the request */
    CY_SMIF_BUSY            = CY_SMIF_ID |CY_PDL_STATUS_ERROR | 0x83U,
} cy_en_smif_status_t;

/** The SMIF slave select definitions for the driver API. Each slave select is
 * represented by an enumeration that has the bit corresponding to the slave
 * select number set. */
typedef enum
{
   CY_SMIF_SLAVE_SELECT_0 = 1U,  /**< The SMIF slave select 0  */
   CY_SMIF_SLAVE_SELECT_1 = 2U,  /**< The SMIF slave select 1  */
   CY_SMIF_SLAVE_SELECT_2 = 4U,  /**< The SMIF slave select 2  */
   CY_SMIF_SLAVE_SELECT_3 = 8U   /**< The SMIF slave select 3  */
} cy_en_smif_slave_select_t;

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/** Specifies receive capture mode. */
/**
* \note
* This enum is available for CAT1D devices.
**/
typedef enum
{
    CY_SMIF_SEL_NORMAL_SPI = 0U,                   /**< Normal SPI without DLP. */
    CY_SMIF_SEL_NORMAL_SPI_WITH_DLP = 1U,          /**< Normal SPI with DLP (Data Learning Pattern). */
    CY_SMIF_SEL_XSPI_HYPERBUS_WITH_DQS = 2U,       /**< xSPI or HYPER BUS with Data strobe line. */
} cy_en_smif_capture_mode_t;
#endif

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)

/** Specifies the clock source for the receiver clock. */
/**
* \note
* This enum is available for CAT1B and CAT1C devices.
**/
typedef enum
{
   CY_SMIF_SEL_OUTPUT_CLK   = 0U,  /**< The SMIF output clock */
   CY_SMIF_SEL_INVERTED_OUTPUT_CLK   = 1U,  /**< The SMIF inverted output clock */
   CY_SMIF_SEL_FEEDBACK_CLK     = 2U,  /**< The SMIF feedback clock */
   CY_SMIF_SEL_INVERTED_FEEDBACK_CLK = 3U,   /**< The SMIF feedback inverted clock */
   CY_SMIF_SEL_INTERNAL_CLK     = 4U,  /**< The SMIF internal clock */
   CY_SMIF_SEL_INVERTED_INTERNAL_CLK = 5U,  /**< The SMIF internal inverted clock */
} cy_en_smif_clk_select_t;
#endif
#if (CY_IP_MXSMIF_VERSION==1) || defined (CY_DOXYGEN)
/**
* \note
* This enum is available for CAT1A devices.
**/
typedef enum
{
   CY_SMIF_SEL_INTERNAL_CLK     = 0U,  /**< The SMIF internal clock */
   CY_SMIF_SEL_INVERTED_INTERNAL_CLK = 1U,  /**< The SMIF internal inverted clock */
   CY_SMIF_SEL_FEEDBACK_CLK     = 2U,  /**< The SMIF feedback clock */
   CY_SMIF_SEL_INVERTED_FEEDBACK_CLK = 3U   /**< The SMIF feedback inverted clock */
} cy_en_smif_clk_select_t;
#endif /* CY_IP_MXSMIF_VERSION */

/** Specifies enabled type of SMIF cache. */
typedef enum
{
    CY_SMIF_CACHE_SLOW      = 1U,   /**< The SMIF slow cache (in the clk_slow domain) see TRM for details */
    CY_SMIF_CACHE_FAST      = 2U,   /**< The SMIF fast cache  (in the clk_fast domain) see TRM for details */
    CY_SMIF_CACHE_BOTH      = 3U    /**< The SMIF both caches */
} cy_en_smif_cache_t;

/** Specifies the quad enable requirement case.
 * JEDEC Basic Flash Parameter Table: 15th DWORD
**/
typedef enum
{
    CY_SMIF_SFDP_QER_0   = 0, /**< No QE Bit */
    CY_SMIF_SFDP_QER_1   = 1, /**< Bit 1 of Status Register 2 - Write uses 2 bytes using 01h */
    CY_SMIF_SFDP_QER_2   = 2, /**< Bit 6 of Status Register 1 - Write uses 1 byte */
    CY_SMIF_SFDP_QER_3   = 3, /**< Bit 7 of Status Register 2- Write uses 1 byte */
    CY_SMIF_SFDP_QER_4   = 4, /**< Bit 1 of Status Register 2 - Write uses 1 or 2 bytes */
    CY_SMIF_SFDP_QER_5   = 5, /**< Bit 1 of Status Register 2 - Write status uses 01h */
    CY_SMIF_SFDP_QER_6   = 6, /**< Bit 1 of Status Register 2 - Write uses 1 byte using 31h */
} cy_en_smif_qer_t;

/** Specifies the memory interface frequency range of operation.
**/
typedef enum
{
    CY_SMIF_100MHZ_OPERATION   = 0, /**< 100 MHz default operation */
    CY_SMIF_133MHZ_OPERATION   = 1, /**< 133 MHz operation */
    CY_SMIF_166MHZ_OPERATION   = 2, /**< 166 MHz operation */
    CY_SMIF_200MHZ_OPERATION   = 3, /**< 200 MHz operation */
} cy_en_smif_interface_freq_t;

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
/** Specifies the data rate. */
/**
* \note
* This enum is available for CAT1B, CAT1C and CAT1D devices.
**/
typedef enum
{
    CY_SMIF_SDR = 0,    /**< The SMIF Single Data Rate (SDR) */
    CY_SMIF_DDR = 1,    /**< The SMIF Double Data Rate (DDR) */
} cy_en_smif_data_rate_t;

/** Specifies the presence of the field. */
/**
* \note
* This enum is available for CAT1B, CAT1C and CAT1D devices.
**/
typedef enum
{
    CY_SMIF_NOT_PRESENT   = 0,
    CY_SMIF_PRESENT_1BYTE = 1,
    CY_SMIF_PRESENT_2BYTE = 2,
} cy_en_smif_field_presence_t;

/** Specifies the merge transaction timeout in terms of clock cycles. */
/**
* \note
* This enum is available for CAT1B, CAT1C and CAT1D devices.
**/
typedef enum
{
    CY_SMIF_MERGE_TIMEOUT_1_CYCLE      = 0,
    CY_SMIF_MERGE_TIMEOUT_16_CYCLES    = 1,
    CY_SMIF_MERGE_TIMEOUT_256_CYCLES   = 2,
    CY_SMIF_MERGE_TIMEOUT_4096_CYCLES  = 3,
    CY_SMIF_MERGE_TIMEOUT_65536_CYCLES = 4,
} cy_en_smif_merge_timeout_t;

#endif /* CY_IP_MXSMIF_VERSION */

/** \cond INTERNAL */
/*******************************************************************************
* These are legacy macros. They are left here just for backward compatibility.
* Do not use them in new designs.
*******************************************************************************/

#define CY_SMIF_SEND_CMPLT                          CY_SMIF_SEND_COMPLETE
#define CY_SMIF_REC_CMPLT                           CY_SMIF_RX_COMPLETE
#define CY_SMIF_REC_BUSY                            CY_SMIF_RX_BUSY
#define CY_SMIF_SEL_INV_INTERNAL_CLK                CY_SMIF_SEL_INVERTED_INTERNAL_CLK
#define CY_SMIF_SEL_INV_FEEDBACK_CLK                CY_SMIF_SEL_INVERTED_FEEDBACK_CLK
#define cy_en_smif_cache_en_t                       cy_en_smif_cache_t
#define Cy_SMIF_GetTxfrStatus                       Cy_SMIF_GetTransferStatus

/** \endcond */

/** \} group_smif_enums */


/**
* \addtogroup group_smif_data_structures
* \{
*/

/***************************************************************************//**
*
* The SMIF user callback function type called at the end of a transfer.
*
* \param event
* The event which caused a callback call.
*
*******************************************************************************/
typedef void (*cy_smif_event_cb_t)(uint32_t event);


/** The SMIF configuration structure. */
typedef struct
{
    uint32_t mode;              /**<  Specifies the mode of operation \ref cy_en_smif_mode_t. */
    uint32_t deselectDelay;     /**<  Specifies the minimum duration of SPI de-selection between SPI transfers:
                                *   - "0": 1 clock cycle.
                                *   - "1": 2 clock cycles.
                                *   - "2": 3 clock cycles.
                                *   - "3": 4 clock cycles.
                                *   - "4": 5 clock cycles.
                                *   - "5": 6 clock cycles.
                                *   - "6": 7 clock cycles.
                                *   - "7": 8 clock cycles. */
    uint32_t rxClockSel;        /**< Specifies the clock source for the receiver
                                *  clock \ref cy_en_smif_clk_select_t. */
    uint32_t blockEvent;        /**< Specifies what happens when there is a Read
                                * from an empty RX FIFO or a Write to a full
                                * TX FIFO. \ref cy_en_smif_error_event_t. */
} cy_stc_smif_config_t;

/** The SMIF internal context data. The user must not modify it. */
typedef struct
{
    uint8_t const volatile * volatile txBufferAddress;    /**<  The pointer to the data to transfer */
    uint32_t txBufferSize;                          /**<  The size of the data to transmit in bytes */
    /**
    * The transfer counter. The number of the transmitted bytes = txBufferSize - txBufferCounter
    */
    uint32_t volatile txBufferCounter;
    uint8_t volatile * volatile rxBufferAddress;    /**<  The pointer to the variable where the received data is stored */
    uint32_t rxBufferSize;                          /**<  The size of the data to be received in bytes */
    /**
    * The transfer counter. The number of the received bytes = rxBufferSize - rxBufferCounter
    */
    uint32_t volatile rxBufferCounter;
    /**
    * The status of the transfer. The transmitting / receiving is completed / in progress
    */
    uint32_t volatile transferStatus;
    cy_smif_event_cb_t volatile txCompleteCb;          /**< The user-defined callback executed at the completion of a transmission */
    cy_smif_event_cb_t volatile rxCompleteCb;          /**< The user-defined callback executed at the completion of a reception */
    /**
    * The timeout in microseconds for the blocking functions. This timeout value applies to all blocking APIs.
    */
    uint32_t timeout;
    /**
    * The timeout in microseconds for polling memory device on its readiness.
    */
    uint16_t memReadyPollDealy;
#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t  preCmdDataRate; /**< preferred command data rate */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_txfr_width_t preCmdWidth; /**< preferred command data rate */
    /**
    * \note
    * This parameter is available for CAT1B, CAT1C and CAT1D devices.
    **/
    cy_en_smif_data_rate_t  preXIPDataRate; /**< preferred XIP data rate */
#endif /* CY_IP_MXSMIF_VERSION */
} cy_stc_smif_context_t;

/** \} group_smif_data_structures */


/**
* \addtogroup group_smif_low_level_functions
* \{
*/

cy_en_smif_status_t Cy_SMIF_Init(SMIF_Type *base, cy_stc_smif_config_t const *config,
                                uint32_t timeout,
                                cy_stc_smif_context_t *context);
void Cy_SMIF_DeInit(SMIF_Type *base);
void Cy_SMIF_SetDataSelect(SMIF_Type *base, cy_en_smif_slave_select_t slaveSelect,
                                cy_en_smif_data_select_t dataSelect);
void Cy_SMIF_SetMode(SMIF_Type *base, cy_en_smif_mode_t mode);
cy_en_smif_mode_t Cy_SMIF_GetMode(SMIF_Type const *base);
cy_en_smif_status_t Cy_SMIF_TransmitCommand(SMIF_Type *base,
                                uint8_t cmd,
                                cy_en_smif_txfr_width_t cmdTxfrWidth,
                                uint8_t const cmdParam[], uint32_t paramSize,
                                cy_en_smif_txfr_width_t paramTxfrWidth,
                                cy_en_smif_slave_select_t slaveSelect, uint32_t completeTxfr,
                                cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_TransmitData(SMIF_Type *base,
                                uint8_t const *txBuffer, uint32_t size,
                                cy_en_smif_txfr_width_t transferWidth,
                                cy_smif_event_cb_t TxCompleteCb,
                                cy_stc_smif_context_t *context);
cy_en_smif_status_t  Cy_SMIF_TransmitDataBlocking(SMIF_Type *base,
                                uint8_t const *txBuffer,
                                uint32_t size,
                                cy_en_smif_txfr_width_t transferWidth,
                                cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_ReceiveData(SMIF_Type *base,
                                uint8_t *rxBuffer, uint32_t size,
                                cy_en_smif_txfr_width_t transferWidth,
                                cy_smif_event_cb_t RxCompleteCb,
                                cy_stc_smif_context_t *context);
cy_en_smif_status_t  Cy_SMIF_ReceiveDataBlocking(SMIF_Type *base,
                                uint8_t *rxBuffer,
                                uint32_t size,
                                cy_en_smif_txfr_width_t transferWidth,
                                cy_stc_smif_context_t const *context);
cy_en_smif_status_t Cy_SMIF_SendDummyCycles(SMIF_Type *base, uint32_t cycles);
uint32_t Cy_SMIF_GetTransferStatus(SMIF_Type const *base, cy_stc_smif_context_t const *context);
void Cy_SMIF_Enable(SMIF_Type *base, cy_stc_smif_context_t *context);

#if (CY_IP_MXSMIF_VERSION>=2) || defined (CY_DOXYGEN)
cy_en_smif_status_t Cy_SMIF_TransmitCommand_Ext(SMIF_Type *base,
                                                 uint16_t cmd,
                                                 bool isCommand2byte,
                                                 cy_en_smif_txfr_width_t cmdTxfrWidth,
                                                 cy_en_smif_data_rate_t cmdDataRate,
                                                 uint8_t const cmdParam[],
                                                 uint32_t paramSize,
                                                 cy_en_smif_txfr_width_t paramTxfrWidth,
                                                 cy_en_smif_data_rate_t paramDataRate,
                                                 cy_en_smif_slave_select_t slaveSelect,
                                                 uint32_t completeTxfr,
                                                 cy_stc_smif_context_t const *context);

cy_en_smif_status_t Cy_SMIF_TransmitData_Ext(SMIF_Type *base,
                                                uint8_t const *txBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataDataRate,
                                                cy_smif_event_cb_t TxCmpltCb,
                                                cy_stc_smif_context_t *context);

cy_en_smif_status_t Cy_SMIF_TransmitDataBlocking_Ext(SMIF_Type *base,
                                                uint8_t const *txBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataDataRate,
                                                cy_stc_smif_context_t const *context);

cy_en_smif_status_t Cy_SMIF_ReceiveData_Ext(SMIF_Type *base,
                                                uint8_t *rxBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataRate,
                                                cy_smif_event_cb_t RxCmpltCb,
                                                cy_stc_smif_context_t *context);

cy_en_smif_status_t Cy_SMIF_ReceiveDataBlocking_Ext(SMIF_Type *base,
                                                uint8_t *rxBuffer,
                                                uint32_t size,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataRate,
                                                cy_stc_smif_context_t const *context);

cy_en_smif_status_t Cy_SMIF_SendDummyCycles_Ext(SMIF_Type *base,
                                                cy_en_smif_txfr_width_t transferWidth,
                                                cy_en_smif_data_rate_t dataRate,
                                                uint32_t cycles);
void Cy_SMIF_DeviceTransfer_SetMergeTimeout(SMIF_Type *base, cy_en_smif_slave_select_t slave, cy_en_smif_merge_timeout_t timeout);
void Cy_SMIF_DeviceTransfer_ClearMergeTimeout(SMIF_Type *base, cy_en_smif_slave_select_t slave);

#endif /* CY_IP_MXSMIF_VERSION */

__STATIC_INLINE void Cy_SMIF_Disable(SMIF_Type *base);
__STATIC_INLINE void  Cy_SMIF_SetInterruptMask(SMIF_Type *base, uint32_t interrupt);
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptMask(SMIF_Type const *base);
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptStatusMasked(SMIF_Type const *base);
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptStatus(SMIF_Type const *base);
__STATIC_INLINE void  Cy_SMIF_SetInterrupt(SMIF_Type *base, uint32_t interrupt);
__STATIC_INLINE void  Cy_SMIF_ClearInterrupt(SMIF_Type *base, uint32_t interrupt);
__STATIC_INLINE void  Cy_SMIF_SetTxFifoTriggerLevel(SMIF_Type *base, uint32_t level);
__STATIC_INLINE void  Cy_SMIF_SetRxFifoTriggerLevel(SMIF_Type *base, uint32_t level);
__STATIC_INLINE uint32_t  Cy_SMIF_GetCmdFifoStatus(SMIF_Type const *base);
__STATIC_INLINE uint32_t  Cy_SMIF_GetTxFifoStatus(SMIF_Type const *base);
__STATIC_INLINE uint32_t  Cy_SMIF_GetRxFifoStatus(SMIF_Type const *base);
cy_en_smif_status_t  Cy_SMIF_Encrypt(SMIF_Type *base,
                                uint32_t address,
                                uint8_t data[],
                                uint32_t size,
                                cy_stc_smif_context_t const *context);
__STATIC_INLINE bool Cy_SMIF_BusyCheck(SMIF_Type const *base);
__STATIC_INLINE void Cy_SMIF_Interrupt(SMIF_Type *base, cy_stc_smif_context_t *context);
cy_en_smif_status_t Cy_SMIF_CacheEnable(SMIF_Type *base, cy_en_smif_cache_t cacheType);
cy_en_smif_status_t Cy_SMIF_CacheDisable(SMIF_Type *base, cy_en_smif_cache_t cacheType);
cy_en_smif_status_t Cy_SMIF_CachePrefetchingEnable(SMIF_Type *base, cy_en_smif_cache_t cacheType);
cy_en_smif_status_t Cy_SMIF_CachePrefetchingDisable(SMIF_Type *base, cy_en_smif_cache_t cacheType);
cy_en_smif_status_t Cy_SMIF_CacheInvalidate(SMIF_Type *base, cy_en_smif_cache_t cacheType);
void Cy_SMIF_SetCryptoKey(SMIF_Type *base, uint32_t *key);
void Cy_SMIF_SetCryptoIV(SMIF_Type *base, uint32_t *nonce);
cy_en_smif_status_t Cy_SMIF_SetCryptoEnable(SMIF_Type *base, cy_en_smif_slave_select_t slaveId);
cy_en_smif_status_t Cy_SMIF_SetCryptoDisable(SMIF_Type *base, cy_en_smif_slave_select_t slaveId);
cy_en_smif_status_t Cy_SMIF_ConvertSlaveSlotToIndex(cy_en_smif_slave_select_t ss, uint32_t *device_idx);
#if (CY_IP_MXSMIF_VERSION>=5) || defined (CY_DOXYGEN)
void Cy_SMIF_SetRxCaptureMode(SMIF_Type *base, cy_en_smif_capture_mode_t mode);
#endif
/** \addtogroup group_smif_functions_syspm_callback
* The driver supports SysPm callback for Deep Sleep and Hibernate transition.
* \{
*/
#if defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS40SSRSS)
cy_en_syspm_status_t Cy_SMIF_DeepSleepCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
cy_en_syspm_status_t Cy_SMIF_HibernateCallback(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
#endif
/** \} */


/***************************************
*  Internal SMIF function declarations
****************************************/
/** \cond INTERNAL */
__STATIC_INLINE void Cy_SMIF_PushTxFifo(SMIF_Type *baseaddr, cy_stc_smif_context_t *context);      /**< Writes transmitted data into the FIFO. */
__STATIC_INLINE void Cy_SMIF_PopRxFifo(SMIF_Type *baseaddr, cy_stc_smif_context_t *context);       /**< Reads received data from the FIFO. */
__STATIC_INLINE uint32_t Cy_SMIF_PackBytesArray(uint8_t const buff[], bool fourBytes);
__STATIC_INLINE void Cy_SMIF_UnPackByteArray(uint32_t inValue, uint8_t outBuff[], bool fourBytes);
__STATIC_INLINE cy_en_smif_status_t Cy_SMIF_TimeoutRun(uint32_t *timeoutUnits);
__STATIC_INLINE SMIF_DEVICE_Type volatile * Cy_SMIF_GetDeviceBySlot(SMIF_Type *base,
                                cy_en_smif_slave_select_t slaveSelect);
/** \endcond */

/** \} group_smif_low_level_functions */


/**
* \addtogroup group_smif_low_level_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SMIF_Disable
****************************************************************************//**
*
* Disables the operation of the SMIF block. The SMIF block can be disabled only
* when it is not in the active state. Use the Cy_SMIF_BusyCheck() API to check
* it before calling this API. Make sure the clock supplied to SMIF block is also
* disabled before calling this API using \ref Cy_SysClk_ClkHfDisable
*
* \param base
* Holds the base address of the SMIF block registers.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SMIF_Disable(SMIF_Type *base)
{
    SMIF_CTL(base) &= ~SMIF_CTL_ENABLED_Msk;

}


/*******************************************************************************
* Function Name: Cy_SMIF_SetInterruptMask
****************************************************************************//**
*
* This function is used to set an interrupt mask for the SMIF Interrupt.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param interrupt
* This is the mask for different source options that can be masked. See
* \ref group_smif_macros_isr "Interrupt Macros" for possible values.
*
*******************************************************************************/
__STATIC_INLINE void  Cy_SMIF_SetInterruptMask(SMIF_Type *base, uint32_t interrupt)
{
    SMIF_INTR_MASK(base) = interrupt;
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetInterruptMask
****************************************************************************//**
*
* This function is used to read an interrupt mask for the SMIF Interrupt.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns the mask set for the SMIF interrupt.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptMask(SMIF_Type const *base)
{
  return (SMIF_INTR_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetInterruptStatusMasked
****************************************************************************//**
*
* This function is used to read an active masked interrupt. This function can
* be used in the interrupt service-routine to find which source triggered the
* interrupt.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns a word with bits set at positions corresponding to the
* interrupts triggered in the system.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptStatusMasked(SMIF_Type const *base)
{
  return (SMIF_INTR_MASKED(base));
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetInterruptStatus
****************************************************************************//**
*
* This function is used to read an active interrupt. This status is the unmasked
* result, so will also show interrupts that will not generate active interrupts.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns a word with bits set at positions corresponding to the
* interrupts triggered in the system.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetInterruptStatus(SMIF_Type const *base)
{
  return (SMIF_INTR(base));
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetInterrupt
****************************************************************************//**
*
* This function is used to set an interrupt source. This function can be used
* to activate interrupts through the software.
*
* \note Interrupt sources set using this interrupt will generate interrupts only
* if they are not masked.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param interrupt
* An encoded integer with a bit set corresponding to the interrupt to be
* triggered. See \ref group_smif_macros_isr "Interrupt Macros" for possible
* values.
*
*******************************************************************************/
__STATIC_INLINE void  Cy_SMIF_SetInterrupt(SMIF_Type *base, uint32_t interrupt)
{
    SMIF_INTR_SET(base) = interrupt;
}


/*******************************************************************************
* Function Name: Cy_SMIF_ClearInterrupt
****************************************************************************//**
*
* This function is used to clear an interrupt source. This function can be used
* in the user code to clear all pending interrupts.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param interrupt
* An encoded integer with a bit set corresponding to the interrupt that must
* be cleared. See \ref group_smif_macros_isr "Interrupt Macros" for possible
* values.
*
*******************************************************************************/
__STATIC_INLINE void  Cy_SMIF_ClearInterrupt(SMIF_Type *base, uint32_t interrupt)
{
    SMIF_INTR(base) = interrupt;

    /* Ensure that the initial Write has been flushed out to the hardware. */
    interrupt = SMIF_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetTxFifoTriggerLevel()
****************************************************************************//**
*
* This function is used to set a trigger level for the TX FIFO. This value must
* be an integer between 0 and 7. For the normal mode only.
* The triggering is active when TX_DATA_FIFO_STATUS <= level.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param level
* The trigger level to set (0-8).
*
*******************************************************************************/
__STATIC_INLINE void  Cy_SMIF_SetTxFifoTriggerLevel(SMIF_Type *base, uint32_t level)
{
    CY_ASSERT_L2(level <= CY_SMIF_MAX_TX_TR_LEVEL);
    SMIF_TX_DATA_FIFO_CTL(base) = level;
}


/*******************************************************************************
* Function Name: Cy_SMIF_SetRxFifoTriggerLevel()
****************************************************************************//**
*
* This function is used to set a trigger level for the RX FIFO. This value must
* be an integer between 0 and 7. For the normal mode only.
* The triggering is active when RX_DATA_FIFOSTATUS > level.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param level
* The trigger level to set(0-8).
*
*******************************************************************************/
__STATIC_INLINE void  Cy_SMIF_SetRxFifoTriggerLevel(SMIF_Type *base, uint32_t level)
{
    CY_ASSERT_L2(level <= CY_SMIF_MAX_RX_TR_LEVEL);
    SMIF_RX_DATA_FIFO_CTL(base) = level;
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetCmdFifoStatus()
****************************************************************************//**
*
* This function is used to read the status of the CMD FIFO.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns the number of the entries in the CMD FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetCmdFifoStatus(SMIF_Type const *base)
{
#if (CY_IP_MXSMIF_VERSION>=3)
    return (_FLD2VAL(SMIF_TX_CMD_MMIO_FIFO_STATUS_USED4, SMIF_TX_CMD_MMIO_FIFO_STATUS(base)));
#elif (CY_IP_MXSMIF_VERSION == 2)
    return (_FLD2VAL(SMIF_TX_CMD_FIFO_STATUS_USED4, SMIF_TX_CMD_FIFO_STATUS(base)));
#else
    return (_FLD2VAL(SMIF_TX_CMD_FIFO_STATUS_USED3, SMIF_TX_CMD_FIFO_STATUS(base)));
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetTxFifoStatus()
****************************************************************************//**
*
* This function is used to read the status of the TX FIFO.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns the number of the entries in the TX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetTxFifoStatus(SMIF_Type const *base)
{
#if (CY_IP_MXSMIF_VERSION>=3)
    return (_FLD2VAL(SMIF_TX_DATA_MMIO_FIFO_STATUS_USED4, SMIF_TX_DATA_MMIO_FIFO_STATUS(base)));
#else
    return (_FLD2VAL(SMIF_TX_DATA_FIFO_STATUS_USED4, SMIF_TX_DATA_FIFO_STATUS(base)));
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetRxFifoStatus()
****************************************************************************//**
*
* This function is used to read the status of the RX FIFO.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns the number of the entries in the RX FIFO.
*
*******************************************************************************/
__STATIC_INLINE uint32_t  Cy_SMIF_GetRxFifoStatus(SMIF_Type const *base)
{
#if (CY_IP_MXSMIF_VERSION>=2)
    return (_FLD2VAL(SMIF_RX_DATA_MMIO_FIFO_STATUS_USED4, SMIF_RX_DATA_MMIO_FIFO_STATUS(base)));
#else
    return (_FLD2VAL(SMIF_RX_DATA_FIFO_STATUS_USED4, SMIF_RX_DATA_FIFO_STATUS(base)));
#endif /* CY_IP_MXSMIF_VERSION */
}


/*******************************************************************************
* Function Name: Cy_SMIF_BusyCheck
****************************************************************************//**
*
* This function provides the status of the IP block (False - not busy,
* True - busy).
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \return Returns an IP block status.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_SMIF_BusyCheck(SMIF_Type const *base)
{
  return (1UL == _FLD2VAL(SMIF_STATUS_BUSY, SMIF_STATUS(base)));
}


/*******************************************************************************
* Function Name: Cy_SMIF_Interrupt
****************************************************************************//**
*
* The Interrupt Service Routine for the SMIF. The interrupt code will be
* responsible for the FIFO operations on FIFO interrupts during ongoing transfers.
* The user must place a call to this interrupt function in the interrupt
* routine corresponding to the interrupt attached to the SMIF. If the
* user does not do this, will break: the functionality of all the API functions in
* the SMIF driver that use SMIF interrupts to affect transfers.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* \globalvars
*  - context->txBufferAddress - The pointer to the data to be transferred.
*
*  - context->txBufferSize - The size of txBuffer.
*
*  - context->txBufferCounter - The number of data entries left to be transferred.
*
* All the Global variables described above are used when the Software Buffer is
* used.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SMIF_Interrupt(SMIF_Type *base, cy_stc_smif_context_t *context)
{
    uint32_t interruptStatus = Cy_SMIF_GetInterruptStatusMasked(base);

    /* Check which interrupt occurred */
    if (0U != (interruptStatus & SMIF_INTR_TR_TX_REQ_Msk))
    {
        /* Send data */
        Cy_SMIF_PushTxFifo(base, context);

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_TR_TX_REQ_Msk);
    }
    else if (0U != (interruptStatus & SMIF_INTR_TR_RX_REQ_Msk))
    {
        /* Receive data */
        Cy_SMIF_PopRxFifo(base, context);

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_TR_RX_REQ_Msk);
    }
    else if (0U != (interruptStatus & SMIF_INTR_XIP_ALIGNMENT_ERROR_Msk))
    {
        /* An XIP alignment error */
        context->transferStatus = (uint32_t) CY_SMIF_XIP_ERROR;

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_XIP_ALIGNMENT_ERROR_Msk);
    }

    else if (0U != (interruptStatus & SMIF_INTR_TX_CMD_FIFO_OVERFLOW_Msk))
    {
        /* TX CMD FIFO overflow */
        context->transferStatus = (uint32_t) CY_SMIF_CMD_ERROR;

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_TX_CMD_FIFO_OVERFLOW_Msk);
    }

    else if (0U != (interruptStatus & SMIF_INTR_TX_DATA_FIFO_OVERFLOW_Msk))
    {
        /* A TX DATA FIFO overflow */
        context->transferStatus = (uint32_t) CY_SMIF_TX_ERROR;

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_TX_DATA_FIFO_OVERFLOW_Msk);
    }

    else if (0U != (interruptStatus & SMIF_INTR_RX_DATA_FIFO_UNDERFLOW_Msk))
    {
        /* RX DATA FIFO underflow */
        context->transferStatus = (uint32_t) CY_SMIF_RX_ERROR;

        Cy_SMIF_ClearInterrupt(base, SMIF_INTR_RX_DATA_FIFO_UNDERFLOW_Msk);
    }
    else
    {
        /* Processing of errors */
    }
}


/*******************************************************************************
*  Internal SMIF in-line functions
*******************************************************************************/

/** \cond INTERNAL */

/*******************************************************************************
* Function Name: Cy_SMIF_PushTxFifo
***************************************************************************//***
*
* \internal
*
* \param baseaddr
* Holds the base address of the SMIF block registers.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* This function writes data in the TX FIFO SMIF buffer by 4, 2, or 1 bytes based
* on the residual number of bytes and the available space in the TX FIFO.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SMIF_PushTxFifo(SMIF_Type *baseaddr, cy_stc_smif_context_t *context)
{
    /* The variable that shows which is smaller: the free FIFO size or amount of bytes to be sent */
    uint32_t writeBytes;
    uint32_t freeFifoBytes;
    uint32_t buffCounter = context->txBufferCounter;
    uint8_t *buff = (uint8_t*) context->txBufferAddress;

    freeFifoBytes = CY_SMIF_TX_DATA_FIFO_STATUS_RANGE - Cy_SMIF_GetTxFifoStatus(baseaddr);
    writeBytes = (freeFifoBytes > buffCounter)? buffCounter: freeFifoBytes;

    /* Check that after a FIFO Write, no data/FIFO space remains */
    while (0U != writeBytes)
    {
        /* The first main use case for long transfers */
        if (writeBytes == CY_SMIF_EIGHT_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[4U], true);
        }
        /* The second main use case for short transfers */
        else if(writeBytes == CY_SMIF_ONE_BYTE)
        {
#if (CY_IP_MXSMIF_VERSION>=2)
            if((context->preCmdDataRate == CY_SMIF_DDR) &&(context->preCmdWidth == CY_SMIF_WIDTH_OCTAL))
            {
                SMIF_TX_DATA_MMIO_FIFO_WR1ODD(baseaddr) = buff[0U];
            }
            else
            {
                SMIF_TX_DATA_MMIO_FIFO_WR1(baseaddr) = buff[0U];
            }
#else
            SMIF_TX_DATA_FIFO_WR1(baseaddr) = buff[0U];
#endif /* CY_IP_MXSMIF_VERSION */
        }
        else if(writeBytes == CY_SMIF_TWO_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR2(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], false);
        }
        else if(writeBytes == CY_SMIF_THREE_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR2(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], false);
            SMIF_TX_DATA_FIFO_WR1(baseaddr) = buff[2U];
        }
        else if(writeBytes == CY_SMIF_FOUR_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
        }
        else if(writeBytes == CY_SMIF_FIVE_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
            SMIF_TX_DATA_FIFO_WR1(baseaddr) = buff[4U];
        }
        else if(writeBytes == CY_SMIF_SIX_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
            SMIF_TX_DATA_FIFO_WR2(baseaddr) = Cy_SMIF_PackBytesArray(&buff[4U], false);
        }
        else if(writeBytes == CY_SMIF_SEVEN_BYTES)
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
            SMIF_TX_DATA_FIFO_WR2(baseaddr) = Cy_SMIF_PackBytesArray(&buff[4U], false);
            SMIF_TX_DATA_FIFO_WR1(baseaddr) = buff[6U];
        }
        else /* The  future IP block with FIFO > 8*/
        {
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[0U], true);
            SMIF_TX_DATA_FIFO_WR4(baseaddr) = Cy_SMIF_PackBytesArray(&buff[4U], true);
            writeBytes = CY_SMIF_EIGHT_BYTES;
        }
        buff = &buff[writeBytes];
        buffCounter -= writeBytes;
        /* Check if we already got new data in TX_FIFO */
        freeFifoBytes = CY_SMIF_TX_DATA_FIFO_STATUS_RANGE - Cy_SMIF_GetTxFifoStatus(baseaddr);
        writeBytes = (freeFifoBytes > buffCounter)? buffCounter: freeFifoBytes;
    }

    /* Save changes in the context */
    context->txBufferAddress = buff;
    context->txBufferCounter = buffCounter;

    /* Check if all bytes are sent */
    if (0u == buffCounter)
    {
        /* Disable the TR_TX_REQ interrupt */
        Cy_SMIF_SetInterruptMask(baseaddr, Cy_SMIF_GetInterruptMask(baseaddr) & ~SMIF_INTR_TR_TX_REQ_Msk);

        context->transferStatus = (uint32_t) CY_SMIF_SEND_COMPLETE;
        if (NULL != context->txCompleteCb)
        {
            context->txCompleteCb((uint32_t) CY_SMIF_SEND_COMPLETE);
        }
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_PopRxFifo
***************************************************************************//***
*
* \internal
*
* \param baseaddr
* Holds the base address of the SMIF block registers.
*
* \param context
* Passes a configuration structure that contains the transfer parameters of the
* SMIF block.
*
* This function reads data from the RX FIFO SMIF buffer by 4, 2, or 1 bytes
* based on the data availability in the RX FIFO and amount of bytes to be
* received.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SMIF_PopRxFifo(SMIF_Type *baseaddr, cy_stc_smif_context_t *context)
{
    /* The variable that shows which is smaller: the free FIFO size or amount of bytes to be received */
    uint32_t readBytes;
    uint32_t loadedFifoBytes;
    uint32_t buffCounter = context->rxBufferCounter;
    uint8_t *buff = (uint8_t*) context->rxBufferAddress;

    loadedFifoBytes = Cy_SMIF_GetRxFifoStatus(baseaddr);
    readBytes = (loadedFifoBytes > buffCounter)? buffCounter: loadedFifoBytes;

    /* Check that after a FIFO Read, no new data is available */
    while (0U != readBytes)
    {
        if (readBytes == CY_SMIF_EIGHT_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[4U], true);
        }
        else if(readBytes == CY_SMIF_ONE_BYTE)
        {
            buff[0U] = (uint8_t)SMIF_RX_DATA_FIFO_RD1(baseaddr);
        }
        else if(readBytes == CY_SMIF_TWO_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD2(baseaddr), &buff[0U], false);
        }
        else if(readBytes == CY_SMIF_THREE_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD2(baseaddr), &buff[0U], false);
            buff[2U] = (uint8_t)SMIF_RX_DATA_FIFO_RD1(baseaddr);
        }
        else if(readBytes == CY_SMIF_FOUR_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
        }
        else if(readBytes == CY_SMIF_FIVE_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
            buff[4U] = (uint8_t)SMIF_RX_DATA_FIFO_RD1(baseaddr);
        }
        else if(readBytes == CY_SMIF_SIX_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD2(baseaddr), &buff[4U], false);
        }
        else if(readBytes == CY_SMIF_SEVEN_BYTES)
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD2(baseaddr), &buff[4U], false);
            buff[6U] = (uint8_t)SMIF_RX_DATA_FIFO_RD1(baseaddr);
        }
        else /* The IP block FIFO > 8*/
        {
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[0U], true);
            Cy_SMIF_UnPackByteArray(SMIF_RX_DATA_FIFO_RD4(baseaddr), &buff[4U], true);
            readBytes = CY_SMIF_EIGHT_BYTES;
        }

        buff = &buff[readBytes];
        buffCounter -= readBytes;
        /* Check if we already got new data in RX_FIFO */
        loadedFifoBytes = Cy_SMIF_GetRxFifoStatus(baseaddr);
        readBytes = (loadedFifoBytes > buffCounter)? buffCounter: loadedFifoBytes;
    }

    /* Save changes in the context */
    context->rxBufferAddress = buff;
    context->rxBufferCounter = buffCounter;

    /* Check if all bytes are received */
    if (0UL == buffCounter)
    {
        /* Disable the TR_RX_REQ interrupt */
        Cy_SMIF_SetInterruptMask(baseaddr, Cy_SMIF_GetInterruptMask(baseaddr) & ~SMIF_INTR_TR_RX_REQ_Msk);
        context->transferStatus = (uint32_t) CY_SMIF_RX_COMPLETE;
        if (NULL != context->rxCompleteCb)
        {
            context->rxCompleteCb((uint32_t) CY_SMIF_RX_COMPLETE);
        }
    }

    context->rxBufferCounter = buffCounter;
}


/*******************************************************************************
* Function Name: Cy_SMIF_PackBytesArray
***************************************************************************//***
*
* \internal
*
* This function packs 0-numBytes of the buff byte array into a 4-byte value.
*
* \param buff
* The byte array to pack.
*
* \param fourBytes
*  - True: The pack is for a 32-bit value.
*  - False: The pack is for a 16-bit value.
*
* \return
*  The 4-byte value packed from the byte array.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SMIF_PackBytesArray(uint8_t const buff[], bool fourBytes)
{
    uint32_t result = 0UL;

    result = ((uint32_t)buff[1UL] << 8UL) | (uint32_t)buff[0UL];

    if(fourBytes)
    {
        result |= ((uint32_t)buff[3UL] << 24UL) | ((uint32_t)buff[2UL] << 16UL);
    }

    return result;
}


/*******************************************************************************
* Function Name: Cy_SMIF_UnPackByteArray
***************************************************************************//***
*
* \internal
*
* This function unpacks 0-numBytes from a 4-byte value into the byte array outBuff.
*
* \param smifReg
*  The 4-byte value to unpack.
*
* \param outBuff
* The byte array to fill.
*
* \param fourBytes
*  - The True unpack is for a 32-bit value.
*  - The False unpack is for a 16-bit value.
*
*******************************************************************************/
__STATIC_INLINE void Cy_SMIF_UnPackByteArray(uint32_t inValue, uint8_t outBuff[], bool fourBytes)
{
    outBuff[0UL] = (uint8_t)(inValue & 0xFFUL);
    outBuff[1UL] = (uint8_t)((inValue >> 8UL ) & 0xFFUL);

    if(fourBytes)
    {
        outBuff[2UL] = (uint8_t)((inValue >> 16UL) & 0xFFUL);
        outBuff[3UL] = (uint8_t)((inValue >> 24UL) & 0xFFUL);
    }
}


/*******************************************************************************
* Function Name: Cy_SMIF_TimeoutRun
****************************************************************************//**
*
* \internal
*
* This function checks if the timeout is expired. Use the Cy_SysLib_DelayUs() function for
* implementation.
*
* \param timeoutUnits
*  The pointer to the timeout. The timeout measured in microseconds is multiplied by
*  CY_SMIF_WAIT_1_UNIT.
*
* \return
* A timeout status:
*     - \ref CY_SMIF_SUCCESS - The timeout has not expired or input timeoutUnits is 0.
*     - \ref CY_SMIF_EXCEED_TIMEOUT - The timeout has expired.
*
*******************************************************************************/
__STATIC_INLINE cy_en_smif_status_t Cy_SMIF_TimeoutRun(uint32_t *timeoutUnits)
{
    cy_en_smif_status_t status = CY_SMIF_SUCCESS;
    if (*timeoutUnits > 0u)
    {
        Cy_SysLib_DelayUs(CY_SMIF_WAIT_1_UNIT);
        --(*timeoutUnits);
        status = (0u == (*timeoutUnits))? CY_SMIF_EXCEED_TIMEOUT: CY_SMIF_SUCCESS;
    }
    return status;
}


/*******************************************************************************
* Function Name: Cy_SMIF_GetDeviceBySlot
****************************************************************************//**
*
* \internal
* This function returns the address of the SMIF device registers structure by the slave
* slot number.
*
* \param base
* Holds the base address of the SMIF block registers.
*
* \param slaveSelect
* The slave device ID. This number is either CY_SMIF_SLAVE_SELECT_0 or
* CY_SMIF_SLAVE_SELECT_1 or CY_SMIF_SLAVE_SELECT_2 or CY_SMIF_SLAVE_SELECT_3
* (\ref cy_en_smif_slave_select_t). It defines the slave-select line to use
* during the transmission.
*
*******************************************************************************/
__STATIC_INLINE SMIF_DEVICE_Type volatile * Cy_SMIF_GetDeviceBySlot(SMIF_Type *base,
                                            cy_en_smif_slave_select_t slaveSelect)
{
    SMIF_DEVICE_Type volatile *device;
    /* Connect the slave to its data lines */
    switch (slaveSelect)
    {
        case CY_SMIF_SLAVE_SELECT_0:
            device = &(SMIF_DEVICE_IDX(base, 0));
            break;
        case CY_SMIF_SLAVE_SELECT_1:
            device = &(SMIF_DEVICE_IDX(base, 1));
            break;
        case CY_SMIF_SLAVE_SELECT_2:
            device = &(SMIF_DEVICE_IDX(base, 2));
            break;
        case CY_SMIF_SLAVE_SELECT_3:
            device = &(SMIF_DEVICE_IDX(base, 3));
            break;
        default:
            /* A user error */
            device = NULL;
            break;
    }

    return device;
}
/** \endcond */
/** \} group_smif_low_level_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSMIF */

#endif /* (CY_SMIF_H) */

/** \} group_smif */


/* [] END OF FILE */
