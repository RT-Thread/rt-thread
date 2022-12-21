/**************************************************************************//**
 * @file     hsusbh_reg.h
 * @brief    HSUSBH register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2021 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HSUSBH_REG_H__
#define __HSUSBH_REG_H__

#if defined ( __CC_ARM   )
    #pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HSUSBH High Speed USB Host Controller
    Memory Mapped Structure for HSUSBH Controller
@{ */

typedef struct
{
    /**
     * @var HSUSBH_T::EHCVNR
     * Offset: 0x00  EHCI Version Number Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[7:0]   |CRLEN     |Capability Registers Length
     * |        |          |This register is used as an offset to add to register base to find the beginning of the Operational Register Space defined in EHCI specification.
     * |[31:16] |VERSION   |Host Controller Interface Version Number
     * |        |          |This is a two-byte register containing a BCD encoding of the EHCI revision number supported by this host controller
     * |        |          |The most significant byte of this register represents a major revision and the least significant byte is the minor revision.
     * @var HSUSBH_T::EHCSPR
     * Offset: 0x04  EHCI Structural Parameters Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[3:0]   |N_PORTS   |Number of Physical Downstream Ports
     * |        |          |This field specifies the number of physical downstream ports implemented on this host controller
     * |        |          |The value of this field determines how many port registers are addressable in the Operational Register Space (see Table 2-8 of EHCI spec.)
     * |        |          |Valid values are in the range of 1H to FH.
     * |        |          |A zero in this field is undefined.
     * |[4]     |PPC       |Port Power Control
     * |        |          |This field indicates whether the host controller implementation includes port power control
     * |        |          |A one in this bit indicates the ports have port power switches
     * |        |          |A zero in this bit indicates the port do not have port power stitches
     * |        |          |The value of this field affects the functionality of the Port Power field in each port status and control register.
     * |[11:8]  |N_PCC     |Number of Ports Per Companion Controller
     * |        |          |This field indicates the number of ports supported per companion host controller
     * |        |          |It is used to indicate the port routing configuration to system software.
     * |        |          |For example, if N_PORTS has a value of 6 and N_CC has a value of 2 then N_PCC could have a value of 3
     * |        |          |The convention is that the first N_PCC ports are assumed to be routed to companion controller 1, the next N_PCC ports to companion controller 2, etc
     * |        |          |In the previous example, the N_PCC could have been 4, where the first 4 are routed to companion controller 1 and the last two are routed to companion controller 2.
     * |        |          |The number in this field must be consistent with N_PORTS and N_CC.
     * |[15:12] |N_CC      |Number of Companion Controller
     * |        |          |This field indicates the number of companion controllers associated with this USB 2.0 host controller.
     * |        |          |A zero in this field indicates there are no companion host controllers
     * |        |          |Port-ownership hand-off is not supported
     * |        |          |Only high-speed devices are supported on the host controller root ports.
     * |        |          |A value larger than zero in this field indicates there are companion USB 1.1 host controller(s)
     * |        |          |Port-ownership hand-offs are supported
     * |        |          |High, Full- and Low-speed devices are supported on the host controller root ports.
     * @var HSUSBH_T::EHCCPR
     * Offset: 0x08  EHCI Capability Parameters Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |AC64      |64-bit Addressing Capability
     * |        |          |0 = Data structure using 32-bit address memory pointers.
     * |        |          |1 = Data structure using 64-bit address memory pointers.
     * |[1]     |PFLF      |Programmable Frame List Flag
     * |        |          |0 = System software must use a frame list length of 1024 elements with this EHCI host controller.
     * |        |          |1 = System software can specify and use a smaller frame list and configure the host controller via the USB Command Register.
     * |[2]     |ASPC      |Asynchronous Schedule Park Capability
     * |        |          |0 = This EHCI host controller doesn't support park feature of high-speed queue heads in the Asynchronous Schedule.
     * |        |          |1 = This EHCI host controller support park feature of high-speed queue heads in the Asynchronous Schedule.
     * |[7:4]   |IST       |Isochronous Scheduling Threshold
     * |        |          |This field indicates, relative to the current position of the executing host controller, where software can reliably update the isochronous schedule.
     * |        |          |When bit [7] is zero, the value of the least significant 3 bits indicates the number of micro-frames a host controller can hold a set of isochronous data structures (one or more) before flushing the state.
     * |        |          |When bit [7] is a one, then host software assumes the host controller may cache an isochronous data structure for an entire frame.
     * |[15:8]  |EECP      |EHCI Extended Capabilities Pointer
     * |        |          |0 = No extended capabilities are implemented.
     * |        |          |1 = Extended capabilities are implemented.
     * @var HSUSBH_T::UCMDR
     * Offset: 0x10  USB Command Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |RUN       |Run/Stop (read/write)
     * |        |          |When set to a 1, the Host Controller proceeds with execution of the schedule
     * |        |          |The Host Controller continues execution as long as this bit is set to a 1
     * |        |          |When this bit is set to 0, the Host Controller completes the current and any actively pipelined transactions on the USB and then halts
     * |        |          |The Host Controller must halt within 16 micro-frames after software clears the Run bit
     * |        |          |The HC Halted bit in the status register indicates when the Host Controller has finished its pending pipelined transactions and has entered the stopped state
     * |        |          |Software must not write a one to this field unless the host controller is in the Halted state (i.e
     * |        |          |HCHalted in the USBSTS register is a one)
     * |        |          |Doing so will yield undefined results.
     * |        |          |0 = Stop.
     * |        |          |1 = Run.
     * |[1]     |HCRST     |Host Controller Reset (read/write)
     * |        |          |This control bit is used by software to reset the host controller
     * |        |          |The effects of this on Root Hub registers are similar to a Chip Hardware Reset.
     * |        |          |When software writes a one to this bit, the Host Controller resets its internal pipelines, timers, counters, state machines, etc
     * |        |          |to their initial value
     * |        |          |Any transaction currently in progress on USB is immediately terminated
     * |        |          |A USB reset is not driven on downstream ports.
     * |        |          |All operational registers, including port registers and port state machines are set to their initial values
     * |        |          |Port ownership reverts to the companion host controller(s), with the side effects
     * |        |          |Software must reinitialize the host controller in order to return the host controller to an operational state.
     * |        |          |This bit is set to zero by the Host Controller when the reset process is complete
     * |        |          |Software cannot terminate the reset process early by writing a zero to this register.
     * |        |          |Software should not set this bit to a one when the HCHalted bit in the USBSTS register is a zero
     * |        |          |Attempting to reset an actively running host controller will result in undefined behavior.
     * |[3:2]   |FLSZ      |Frame List Size (read only)
     * |        |          |This field is R/W only if Programmable Frame List Flag in the HCCPARAMS registers is set to a one
     * |        |          |This field specifies the size of the frame list
     * |        |          |The size the frame list controls which bits in the Frame Index Register should be used for the Frame List Current index
     * |        |          |Values mean:
     * |        |          |00 = 1024 elements (4096 bytes) Default value.
     * |        |          |01 = 512 elements (2048 bytes).
     * |        |          |10 = 256 elements (1024 bytes) - for resource-constrained environment.
     * |        |          |11 = Reserved.
     * |[4]     |PSEN      |Periodic Schedule Enable (read/write)
     * |        |          |This bit controls whether the host controller skips processing the Periodic Schedule. Values mean:
     * |        |          |0 = Do not process the Periodic Schedule.
     * |        |          |1 = Use the PERIODICLISTBASE register to access the Periodic Schedule.
     * |[5]     |ASEN      |Asynchronous Schedule Enable (read/write)
     * |        |          |This bit controls whether the host controller skips processing the Asynchronous Schedule. Values mean:
     * |        |          |0 = Do not process the Asynchronous Schedule.
     * |        |          |1 = Use the ASYNCLISTADDR register to access the Asynchronous Schedule.
     * |[6]     |IAAD      |Interrupt on Asynchronous Advance Doorbell (read/write)
     * |        |          |This bit is used as a doorbell by software to tell the host controller to issue an interrupt the next time it advances asynchronous schedule
     * |        |          |Software must write a 1 to this bit to ring the doorbell.
     * |        |          |When the host controller has evicted all appropriate cached schedule state, it sets the Interrupt on Asynchronous Advance status bit in the USBSTS register
     * |        |          |If the Interrupt on Asynchronous Advance Enable bit in the USBINTR register is a one then the host controller will assert an interrupt at the next interrupt threshold.
     * |        |          |The host controller sets this bit to a zero after it has set the Interrupt on Asynchronous Advance status bit in the USBSTS register to a one.
     * |        |          |Software should not write a one to this bit when the asynchronous schedule is disabled
     * |        |          |Doing so will yield undefined results.
     * |[23:16] |ITC       |Interrupt Threshold Control (read/write)
     * |        |          |This field is used by system software to select the maximum rate at which the host controller will issue interrupts
     * |        |          |The only valid values are defined below
     * |        |          |If software writes an invalid value to this register, the results are undefined
     * |        |          |Value Maximum Interrupt Interval
     * |        |          |0x00 = Reserved.
     * |        |          |0x01 = 1 micro-frame.
     * |        |          |0x02 = 2 micro-frames.
     * |        |          |0x04 = 4 micro-frames.
     * |        |          |0x08 = 8 micro-frames (default, equates to 1 ms).
     * |        |          |0x10 = 16 micro-frames (2 ms).
     * |        |          |0x20 = 32 micro-frames (4 ms).
     * |        |          |0x40 = 64 micro-frames (8 ms).
     * |        |          |Any other value in this register yields undefined results.
     * |        |          |Software modifications to this bit while HCHalted bit is equal to zero results in undefined behavior.
     * @var HSUSBH_T::USTSR
     * Offset: 0x14  USB Status Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBINT    |USB Interrupt (write 1 to clear)
     * |        |          |The Host Controller sets this bit to 1 on the completion of a USB transaction, which results in the retirement of a Transfer Descriptor that had its IOC bit set.
     * |        |          |The Host Controller also sets this bit to 1 when a short packet is detected (actual number of bytes received was less than the expected number of bytes).
     * |[1]     |UERRINT   |USB Error Interrupt (write 1 to clear)
     * |        |          |The Host Controller sets this bit to 1 when completion of a USB transaction results in an error condition (e.g., error counter underflow)
     * |        |          |If the TD on which the error interrupt occurred also had its IOC bit set, both this bit and USBINT bit are set.
     * |[2]     |PCD       |Port Change Detect (write 1 to clear)
     * |        |          |The Host Controller sets this bit to a one when any port for which the Port Owner bit is set to zero has a change bit transition from a zero to a one or a Force Port Resume bit transition from a zero to a one as a result of a J-K transition detected on a suspended port
     * |        |          |This bit will also be set as a result of the Connect Status Change being set to a one after system software has relinquished ownership of a connected port by writing a one to a port's Port Owner bit.
     * |        |          |This bit is allowed to be maintained in the Auxiliary power well
     * |        |          |Alternatively, it is also acceptable that on a D3 to D0 transition of the EHCI HC device, this bit is loaded with the OR of all of the PORTSC change bits (including: Force port resume, overcurrent change, enable/disable change and connect status change).
     * |[3]     |FLR       |Frame List Rollover (write 1 to clear)
     * |        |          |The Host Controller sets this bit to a one when the Frame List Index rolls over from its maximum value to zero
     * |        |          |The exact value at which the rollover occurs depends on the frame list size
     * |        |          |For example, if the frame list size (as programmed in the Frame List Size field of the USBCMD register) is 1024, the Frame Index Register rolls over every time FRINDEX[13] toggles
     * |        |          |Similarly, if the size is 512, the Host Controller sets this bit to a one every time FRINDEX[12] toggles.
     * |[4]     |HSERR     |Host System Error (write 1 to clear)
     * |        |          |The Host Controller sets this bit to 1 when a serious error occurs during a host system access involving the Host Controller module.
     * |[5]     |IAA       |Interrupt on Asynchronous Advance (write 1 to clear)
     * |        |          |System software can force the host controller to issue an interrupt the next time the host controller advances the asynchronous schedule by writing a one to the Interrupt on Asynchronous Advance Doorbell bit in the USBCMD register
     * |        |          |This status bit indicates the assertion of that interrupt source.
     * |[12]    |HCHalted  |HCHalted (Read Only)
     * |        |          |This bit is a zero whenever the Run/Stop bit is a one
     * |        |          |The Host Controller sets this bit to one after it has stopped executing as a result of the Run/Stop bit being set to 0, either by software or by the Host Controller hardware (e.g
     * |        |          |internal error).
     * |[13]    |RECLA     |Reclamation (Read Only)
     * |        |          |This is a read-only status bit, which is used to detect an empty asynchronous schedule.
     * |[14]    |PSS       |Periodic Schedule Status (Read Only)
     * |        |          |The bit reports the current real status of the Periodic Schedule
     * |        |          |If this bit is a zero then the status of the Periodic Schedule is disabled
     * |        |          |If this bit is a one then the status of the Periodic Schedule is enabled
     * |        |          |The Host Controller is not required to immediately disable or enable the Periodic Schedule when software transitions the Periodic Schedule Enable bit in the USBCMD register
     * |        |          |When this bit and the Periodic Schedule Enable bit are the same value, the Periodic Schedule is either enabled (1) or disabled (0).
     * |[15]    |ASS       |Asynchronous Schedule Status (Read Only)
     * |        |          |The bit reports the current real status of the Asynchronous Schedule
     * |        |          |If this bit is a zero then the status of them Asynchronous Schedule is disabled
     * |        |          |If this bit is a one then the status of the Asynchronous Schedule is enabled
     * |        |          |The Host Controller is not required to immediately disable or enable the Asynchronous Schedule when software transitions the Asynchronous Schedule Enable bit in the USBCMD register
     * |        |          |When this bit and the Asynchronous Schedule Enable bit are the same value, the Asynchronous Schedule is either enabled (1) or disabled (0).
     * @var HSUSBH_T::UIENR
     * Offset: 0x18  USB Interrupt Enable Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |USBIEN    |USB Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the USBINT bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the USBINT bit.
     * |        |          |0 = USB interrupt Disabled.
     * |        |          |1 = USB interrupt Enabled.
     * |[1]     |UERRIEN   |USB Error Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the USBERRINT bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the USBERRINT bit.
     * |        |          |0 = USB Error interrupt Disabled.
     * |        |          |1 = USB Error interrupt Enabled.
     * |[2]     |PCIEN     |Port Change Interrupt Enable or Disable Bit
     * |        |          |When this bit is a one, and the Port Change Detect bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Port Change Detect bit.
     * |        |          |0 = Port Change interrupt Disabled.
     * |        |          |1 = Port Change interrupt Enabled.
     * |[3]     |FLREN     |Frame List Rollover Enable or Disable Bit
     * |        |          |When this bit is a one, and the Frame List Rollover bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Frame List Rollover bit.
     * |        |          |0 = Frame List Rollover interrupt Disabled.
     * |        |          |1 = Frame List Rollover interrupt Enabled.
     * |[4]     |HSERREN   |Host System Error Enable or Disable Bit
     * |        |          |When this bit is a one, and the Host System Error Status bit in the USBSTS register is a one, the host controller will issue an interrupt
     * |        |          |The interrupt is acknowledged by software clearing the Host System Error bit.
     * |        |          |0 = Host System Error interrupt Disabled.
     * |        |          |1 = Host System Error interrupt Enabled.
     * |[5]     |IAAEN     |Interrupt on Asynchronous Advance Enable or Disable Bit
     * |        |          |When this bit is a one, and the Interrupt on Asynchronous Advance bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
     * |        |          |The interrupt is acknowledged by software clearing the Interrupt on Asynchronous Advance bit.
     * |        |          |0 = Interrupt on Asynchronous Advance Disabled.
     * |        |          |1 = Interrupt on Asynchronous Advance Enabled.
     * @var HSUSBH_T::UFINDR
     * Offset: 0x1C  USB Frame Index Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[13:0]  |FI        |Frame Index
     * |        |          |The value in this register increment at the end of each time frame (e.g
     * |        |          |micro-frame)
     * |        |          |Bits [N:3] are used for the Frame List current index
     * |        |          |This means that each location of the frame list is accessed 8 times (frames or micro-frames) before moving to the next index
     * |        |          |The following illustrates values of N based on the value of the Frame List Size field in the USBCMD register.
     * |        |          |FLSZ (UCMDR[3:2] Number Elements N
     * |        |          |0x0 1024 12
     * |        |          |0x1 512 11
     * |        |          |0x2 256 10
     * |        |          |0x3 Reserved
     * @var HSUSBH_T::UPFLBAR
     * Offset: 0x24  USB Periodic Frame List Base Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:12] |BADDR     |Base Address
     * |        |          |These bits correspond to memory address signals [31:12], respectively.
     * @var HSUSBH_T::UCALAR
     * Offset: 0x28  USB Current Asynchronous List Address Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[31:5]  |LPL       |Link Pointer Low
     * |        |          |These bits correspond to memory address signals [31:5], respectively
     * |        |          |This field may only reference a Queue Head (QH).
     * @var HSUSBH_T::UCFGR
     * Offset: 0x50  USB Configure Flag Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CF        |Configure Flag
     * |        |          |Host software sets this bit as the last action in its process of configuring the Host Controller
     * |        |          |This bit controls the default port-routing control logic
     * |        |          |Bit values and side-effects are listed below.
     * |        |          |0 = Port routing control logic default-routes each port to an implementation dependent classic host controller.
     * |        |          |1 = Port routing control logic default-routes all ports to this host controller.
     * @var HSUSBH_T::UPSCR
     * Offset: 0x54  USB Port Status and Control Register
     * ---------------------------------------------------------------------------------------------------
     * |Bits    |Field     |Descriptions
     * | :----: | :----:   | :---- |
     * |[0]     |CCS       |Current Connect Status (Read Only)
     * |        |          |This value reflects the current state of the port, and may not correspond directly to the event that caused the Connect Status Change bit (Bit 1) to be set.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No device is present.
     * |        |          |1 = Device is present on port.
     * |[1]     |CSC       |Connect Status Change (read/write)
     * |        |          |Indicates a change has occurred in the port's Current Connect Status
     * |        |          |The host controller sets this bit for all changes to the port device connect status, even if system software has not cleared an existing connect status change
     * |        |          |For example, the insertion status changes twice before system software has cleared the changed condition, hub hardware will be "setting" an already-set bit (i.e., the bit will remain set).Software sets this bit to 0 by writing a 1 to it.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No change.
     * |        |          |1 = Change in Current Connect Status.
     * |[2]     |PE        |Port Enabled/Disabled (read/write)
     * |        |          |Ports can only be enabled by the host controller as a part of the reset and enable
     * |        |          |Software cannot enable a port by writing a one to this field
     * |        |          |The host controller will only set this bit to a one when the reset sequence determines that the attached device is a high-speed device.
     * |        |          |Ports can be disabled by either a fault condition (disconnect event or other fault condition) or by host software
     * |        |          |Note that the bit status does not change until the port state actually changes
     * |        |          |There may be a delay in disabling or enabling a port due to other host controller and bus events.
     * |        |          |When the port is disabled, downstream propagation of data is blocked on this port, except for reset.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port Disabled.
     * |        |          |1 = Port Enabled.
     * |[3]     |PEC       |Port Enable/Disable Change (write 1 to clear)
     * |        |          |For the root hub, this bit gets set to a one only when a port is disabled due to the appropriate conditions existing at the EOF2 point (See Chapter 11 of the USB Specification for the definition of a Port Error)
     * |        |          |Software clears this bit by writing a 1 to it.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No change.
     * |        |          |1 = Port enabled/disabled status has changed.
     * |[4]     |OCA       |Overcurrent Active (Read Only)
     * |        |          |This bit will automatically transition from a one to a zero when the overcurrent condition is removed.
     * |        |          |0 = This port does not have an overcurrent condition.
     * |        |          |1 = This port currently has an overcurrent condition.
     * |[5]     |OCC       |Overcurrent Change (write 1 to clear)
     * |        |          |1 = This bit gets set to a one when there is a change to Overcurrent Active
     * |        |          |Software clears this bit by writing a one to this bit position.
     * |        |          |0 = Default.
     * |[6]     |FPR       |Force Port Resume (read/write)
     * |        |          |This functionality defined for manipulating this bit depends on the value of the Suspend bit
     * |        |          |For example, if the port is not suspended (Suspend and Enabled bits are a one) and software transitions this bit to a one, then the effects on the bus are undefined.
     * |        |          |Software sets this bit to a 1 to drive resume signaling
     * |        |          |The Host Controller sets this bit to a 1 if a J-to-K transition is detected while the port is in the Suspend state
     * |        |          |When this bit transitions to a one because a J-to-K transition is detected, the Port Change Detect bit in the USBSTS register is also set to a one
     * |        |          |If software sets this bit to a one, the host controller must not set the Port Change Detect bit.
     * |        |          |Note that when the EHCI controller owns the port, the resume sequence follows the defined sequence documented in the USB Specification Revision 2.0
     * |        |          |The resume signaling (Full-speed 'K') is driven on the port as long as this bit remains a one
     * |        |          |Software must appropriately time the Resume and set this bit to a zero when the appropriate amount of time has elapsed
     * |        |          |Writing a zero (from one) causes the port to return to high-speed mode (forcing the bus below the port into a high-speed idle)
     * |        |          |This bit will remain a one until the port has switched to the high-speed idle
     * |        |          |The host controller must complete this transition within 2 milliseconds of software setting this bit to a zero.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = No resume (K-state) detected/driven on port.
     * |        |          |1 = Resume detected/driven on port.
     * |[7]     |SUSPEND   |Suspend (read/write)
     * |        |          |Port Enabled Bit and Suspend bit of this register define the port states as follows:
     * |        |          |00 = Port Disable.
     * |        |          |01 = Port Disable.
     * |        |          |10 = Port Enable.
     * |        |          |11 = Port Suspend.
     * |        |          |When in suspend state, downstream propagation of data is blocked on this port, except for port reset
     * |        |          |The blocking occurs at the end of the current transaction, if a transaction was in progress when this bit was written to 1
     * |        |          |In the suspend state, the port is sensitive to resume detection
     * |        |          |Note that the bit status does not change until the port is suspended and that there may be a delay in suspending a port if there is a transaction currently in progress on the USB.
     * |        |          |A write of zero to this bit is ignored by the host controller
     * |        |          |The host controller will unconditionally set this bit to a zero when:
     * |        |          |Software sets the Force Port Resume bit to a zero (from a one).
     * |        |          |Software sets the Port Reset bit to a one (from a zero).
     * |        |          |If host software sets this bit to a one when the port is not enabled (i.e
     * |        |          |Port enabled bit is a zero) the results are undefined.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port not in suspend state.
     * |        |          |1 = Port in suspend state.
     * |[8]     |PRST      |Port Reset (read/write)
     * |        |          |When software writes a one to this bit (from a zero), the bus reset sequence as defined in the USB Specification Revision 2.0 is started
     * |        |          |Software writes a zero to this bit to terminate the bus reset sequence
     * |        |          |Software must keep this bit at a one long enough to ensure the reset sequence, as specified in the USB Specification Revision 2.0, completes
     * |        |          |Note: when software writes this bit to a one, it must also write a zero to the Port Enable bit.
     * |        |          |Note that when software writes a zero to this bit there may be a delay before the bit status changes to a zero
     * |        |          |The bit status will not read as a zero until after the reset has completed
     * |        |          |If the port is in high-speed mode after reset is complete, the host controller will automatically enable this port (e.g
     * |        |          |set the Port Enable bit to a one)
     * |        |          |A host controller must terminate the reset and stabilize the state of the port within 2 milliseconds of software transitioning this bit from a one to a zero
     * |        |          |For example: if the port detects that the attached device is high-speed during reset, then the host controller must have the port in the enabled state within 2ms of software writing this bit to a zero.
     * |        |          |The HCHalted bit in the USBSTS register should be a zero before software attempts to use this bit
     * |        |          |The host controller may hold Port Reset asserted to a one when the HCHalted bit is a one.
     * |        |          |This field is zero if Port Power is zero.
     * |        |          |0 = Port is not in Reset.
     * |        |          |1 = Port is in Reset.
     * |[11:10] |LSTS      |Line Status (Read Only)
     * |        |          |These bits reflect the current logical levels of the D+ (bit 11) and D- (bit 10) signal lines
     * |        |          |These bits are used for detection of low-speed USB devices prior to the port reset and enable sequence
     * |        |          |This field is valid only when the port enable bit is zero and the current connect status bit is set to a one.
     * |        |          |The encoding of the bits are:
     * |        |          |Bits[11:10] USB State Interpretation
     * |        |          |00 = SE0 Not Low-speed device, perform EHCI reset.
     * |        |          |01 = K-state Low-speed device, release ownership of port.
     * |        |          |10 = J-state Not Low-speed device, perform EHCI reset.
     * |        |          |11 = Undefined Not Low-speed device, perform EHCI reset.
     * |        |          |This value of this field is undefined if Port Power is zero.
     * |[12]    |PP        |Port Power
     * |        |          |Host controller has port power control switches
     * |        |          |This bit represents the Current setting of the switch (0 = off, 1 = on)
     * |        |          |When power is not available on a port (i.e
     * |        |          |PP equals a 0), the port is nonfunctional and will not report attaches, detaches, etc.
     * |        |          |When an overcurrent condition is detected on a powered port and PPC is a one, the PP bit in each affected port may be transitioned by the host controller from a 1 to 0 (removing power from the port).
     * |[13]    |PO        |Port Owner (read/write)
     * |        |          |This bit unconditionally goes to a 0b when the Configured bit in the CONFIGFLAG register makes a 0 to 1 transition
     * |        |          |This bit unconditionally goes to 1 whenever the Configured bit is zero.
     * |        |          |System software uses this field to release ownership of the port to a selected host controller (in the event that the attached device is not a high-speed device)
     * |        |          |Software writes a one to this bit when the attached device is not a high-speed device
     * |        |          |A one in this bit means that a companion host controller owns and controls the port.
     * |[19:16] |PTC       |Port Test Control (read/write)
     * |        |          |When this field is zero, the port is NOT operating in a test mode
     * |        |          |A non-zero value indicates that it is operating in test mode and the specific test mode is indicated by the specific value
     * |        |          |The encoding of the test mode bits are (0x6 ~ 0xF are reserved):
     * |        |          |Bits Test Mode
     * |        |          |0x0 = Test mode not enabled.
     * |        |          |0x1 = Test J_STATE.
     * |        |          |0x2 = Test K_STATE.
     * |        |          |0x3 = Test SE0_NAK.
     * |        |          |0x4 = Test Packet.
     * |        |          |0x5 = Test FORCE_ENABLE.
     */
    __I  uint32_t EHCVNR;                /*!< [0x0000] EHCI Version Number Register                                     */
    __I  uint32_t EHCSPR;                /*!< [0x0004] EHCI Structural Parameters Register                              */
    __I  uint32_t EHCCPR;                /*!< [0x0008] EHCI Capability Parameters Register                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UCMDR;                 /*!< [0x0010] USB Command Register                                             */
    __IO uint32_t USTSR;                 /*!< [0x0014] USB Status Register                                              */
    __IO uint32_t UIENR;                 /*!< [0x0018] USB Interrupt Enable Register                                    */
    __IO uint32_t UFINDR;                /*!< [0x001c] USB Frame Index Register                                         */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UPFLBAR;               /*!< [0x0024] USB Periodic Frame List Base Address Register                    */
    __IO uint32_t UCALAR;                /*!< [0x0028] USB Current Asynchronous List Address Register                   */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[9];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UCFGR;                 /*!< [0x0050] USB Configure Flag Register                                      */
    __IO uint32_t UPSCR[1];              /*!< [0x0054] USB Port Status and Control Register                             */

} HSUSBH_T;

/**
    @addtogroup HSUSBH_CONST HSUSBH Bit Field Definition
    Constant Definitions for HSUSBH Controller
@{ */

#define HSUSBH_EHCVNR_CRLEN_Pos          (0)                                               /*!< HSUSBH_T::EHCVNR: CRLEN Position       */
#define HSUSBH_EHCVNR_CRLEN_Msk          (0xfful << HSUSBH_EHCVNR_CRLEN_Pos)               /*!< HSUSBH_T::EHCVNR: CRLEN Mask           */

#define HSUSBH_EHCVNR_VERSION_Pos        (16)                                              /*!< HSUSBH_T::EHCVNR: VERSION Position     */
#define HSUSBH_EHCVNR_VERSION_Msk        (0xfffful << HSUSBH_EHCVNR_VERSION_Pos)           /*!< HSUSBH_T::EHCVNR: VERSION Mask         */

#define HSUSBH_EHCSPR_N_PORTS_Pos        (0)                                               /*!< HSUSBH_T::EHCSPR: N_PORTS Position     */
#define HSUSBH_EHCSPR_N_PORTS_Msk        (0xful << HSUSBH_EHCSPR_N_PORTS_Pos)              /*!< HSUSBH_T::EHCSPR: N_PORTS Mask         */

#define HSUSBH_EHCSPR_PPC_Pos            (4)                                               /*!< HSUSBH_T::EHCSPR: PPC Position         */
#define HSUSBH_EHCSPR_PPC_Msk            (0x1ul << HSUSBH_EHCSPR_PPC_Pos)                  /*!< HSUSBH_T::EHCSPR: PPC Mask             */

#define HSUSBH_EHCSPR_N_PCC_Pos          (8)                                               /*!< HSUSBH_T::EHCSPR: N_PCC Position       */
#define HSUSBH_EHCSPR_N_PCC_Msk          (0xful << HSUSBH_EHCSPR_N_PCC_Pos)                /*!< HSUSBH_T::EHCSPR: N_PCC Mask           */

#define HSUSBH_EHCSPR_N_CC_Pos           (12)                                              /*!< HSUSBH_T::EHCSPR: N_CC Position        */
#define HSUSBH_EHCSPR_N_CC_Msk           (0xful << HSUSBH_EHCSPR_N_CC_Pos)                 /*!< HSUSBH_T::EHCSPR: N_CC Mask            */

#define HSUSBH_EHCCPR_AC64_Pos           (0)                                               /*!< HSUSBH_T::EHCCPR: AC64 Position        */
#define HSUSBH_EHCCPR_AC64_Msk           (0x1ul << HSUSBH_EHCCPR_AC64_Pos)                 /*!< HSUSBH_T::EHCCPR: AC64 Mask            */

#define HSUSBH_EHCCPR_PFLF_Pos           (1)                                               /*!< HSUSBH_T::EHCCPR: PFLF Position        */
#define HSUSBH_EHCCPR_PFLF_Msk           (0x1ul << HSUSBH_EHCCPR_PFLF_Pos)                 /*!< HSUSBH_T::EHCCPR: PFLF Mask            */

#define HSUSBH_EHCCPR_ASPC_Pos           (2)                                               /*!< HSUSBH_T::EHCCPR: ASPC Position        */
#define HSUSBH_EHCCPR_ASPC_Msk           (0x1ul << HSUSBH_EHCCPR_ASPC_Pos)                 /*!< HSUSBH_T::EHCCPR: ASPC Mask            */

#define HSUSBH_EHCCPR_IST_Pos            (4)                                               /*!< HSUSBH_T::EHCCPR: IST Position         */
#define HSUSBH_EHCCPR_IST_Msk            (0xful << HSUSBH_EHCCPR_IST_Pos)                  /*!< HSUSBH_T::EHCCPR: IST Mask             */

#define HSUSBH_EHCCPR_EECP_Pos           (8)                                               /*!< HSUSBH_T::EHCCPR: EECP Position        */
#define HSUSBH_EHCCPR_EECP_Msk           (0xfful << HSUSBH_EHCCPR_EECP_Pos)                /*!< HSUSBH_T::EHCCPR: EECP Mask            */

#define HSUSBH_UCMDR_RUN_Pos             (0)                                               /*!< HSUSBH_T::UCMDR: RUN Position          */
#define HSUSBH_UCMDR_RUN_Msk             (0x1ul << HSUSBH_UCMDR_RUN_Pos)                   /*!< HSUSBH_T::UCMDR: RUN Mask              */

#define HSUSBH_UCMDR_HCRST_Pos           (1)                                               /*!< HSUSBH_T::UCMDR: HCRST Position        */
#define HSUSBH_UCMDR_HCRST_Msk           (0x1ul << HSUSBH_UCMDR_HCRST_Pos)                 /*!< HSUSBH_T::UCMDR: HCRST Mask            */

#define HSUSBH_UCMDR_FLSZ_Pos            (2)                                               /*!< HSUSBH_T::UCMDR: FLSZ Position         */
#define HSUSBH_UCMDR_FLSZ_Msk            (0x3ul << HSUSBH_UCMDR_FLSZ_Pos)                  /*!< HSUSBH_T::UCMDR: FLSZ Mask             */

#define HSUSBH_UCMDR_PSEN_Pos            (4)                                               /*!< HSUSBH_T::UCMDR: PSEN Position         */
#define HSUSBH_UCMDR_PSEN_Msk            (0x1ul << HSUSBH_UCMDR_PSEN_Pos)                  /*!< HSUSBH_T::UCMDR: PSEN Mask             */

#define HSUSBH_UCMDR_ASEN_Pos            (5)                                               /*!< HSUSBH_T::UCMDR: ASEN Position         */
#define HSUSBH_UCMDR_ASEN_Msk            (0x1ul << HSUSBH_UCMDR_ASEN_Pos)                  /*!< HSUSBH_T::UCMDR: ASEN Mask             */

#define HSUSBH_UCMDR_IAAD_Pos            (6)                                               /*!< HSUSBH_T::UCMDR: IAAD Position         */
#define HSUSBH_UCMDR_IAAD_Msk            (0x1ul << HSUSBH_UCMDR_IAAD_Pos)                  /*!< HSUSBH_T::UCMDR: IAAD Mask             */

#define HSUSBH_UCMDR_ITC_Pos             (16)                                              /*!< HSUSBH_T::UCMDR: ITC Position          */
#define HSUSBH_UCMDR_ITC_Msk             (0xfful << HSUSBH_UCMDR_ITC_Pos)                  /*!< HSUSBH_T::UCMDR: ITC Mask              */

#define HSUSBH_USTSR_USBINT_Pos          (0)                                               /*!< HSUSBH_T::USTSR: USBINT Position       */
#define HSUSBH_USTSR_USBINT_Msk          (0x1ul << HSUSBH_USTSR_USBINT_Pos)                /*!< HSUSBH_T::USTSR: USBINT Mask           */

#define HSUSBH_USTSR_UERRINT_Pos         (1)                                               /*!< HSUSBH_T::USTSR: UERRINT Position      */
#define HSUSBH_USTSR_UERRINT_Msk         (0x1ul << HSUSBH_USTSR_UERRINT_Pos)               /*!< HSUSBH_T::USTSR: UERRINT Mask          */

#define HSUSBH_USTSR_PCD_Pos             (2)                                               /*!< HSUSBH_T::USTSR: PCD Position          */
#define HSUSBH_USTSR_PCD_Msk             (0x1ul << HSUSBH_USTSR_PCD_Pos)                   /*!< HSUSBH_T::USTSR: PCD Mask              */

#define HSUSBH_USTSR_FLR_Pos             (3)                                               /*!< HSUSBH_T::USTSR: FLR Position          */
#define HSUSBH_USTSR_FLR_Msk             (0x1ul << HSUSBH_USTSR_FLR_Pos)                   /*!< HSUSBH_T::USTSR: FLR Mask              */

#define HSUSBH_USTSR_HSERR_Pos           (4)                                               /*!< HSUSBH_T::USTSR: HSERR Position        */
#define HSUSBH_USTSR_HSERR_Msk           (0x1ul << HSUSBH_USTSR_HSERR_Pos)                 /*!< HSUSBH_T::USTSR: HSERR Mask            */

#define HSUSBH_USTSR_IAA_Pos             (5)                                               /*!< HSUSBH_T::USTSR: IAA Position          */
#define HSUSBH_USTSR_IAA_Msk             (0x1ul << HSUSBH_USTSR_IAA_Pos)                   /*!< HSUSBH_T::USTSR: IAA Mask              */

#define HSUSBH_USTSR_HCHalted_Pos        (12)                                              /*!< HSUSBH_T::USTSR: HCHalted Position     */
#define HSUSBH_USTSR_HCHalted_Msk        (0x1ul << HSUSBH_USTSR_HCHalted_Pos)              /*!< HSUSBH_T::USTSR: HCHalted Mask         */

#define HSUSBH_USTSR_RECLA_Pos           (13)                                              /*!< HSUSBH_T::USTSR: RECLA Position        */
#define HSUSBH_USTSR_RECLA_Msk           (0x1ul << HSUSBH_USTSR_RECLA_Pos)                 /*!< HSUSBH_T::USTSR: RECLA Mask            */

#define HSUSBH_USTSR_PSS_Pos             (14)                                              /*!< HSUSBH_T::USTSR: PSS Position          */
#define HSUSBH_USTSR_PSS_Msk             (0x1ul << HSUSBH_USTSR_PSS_Pos)                   /*!< HSUSBH_T::USTSR: PSS Mask              */

#define HSUSBH_USTSR_ASS_Pos             (15)                                              /*!< HSUSBH_T::USTSR: ASS Position          */
#define HSUSBH_USTSR_ASS_Msk             (0x1ul << HSUSBH_USTSR_ASS_Pos)                   /*!< HSUSBH_T::USTSR: ASS Mask              */

#define HSUSBH_UIENR_USBIEN_Pos          (0)                                               /*!< HSUSBH_T::UIENR: USBIEN Position       */
#define HSUSBH_UIENR_USBIEN_Msk          (0x1ul << HSUSBH_UIENR_USBIEN_Pos)                /*!< HSUSBH_T::UIENR: USBIEN Mask           */

#define HSUSBH_UIENR_UERRIEN_Pos         (1)                                               /*!< HSUSBH_T::UIENR: UERRIEN Position      */
#define HSUSBH_UIENR_UERRIEN_Msk         (0x1ul << HSUSBH_UIENR_UERRIEN_Pos)               /*!< HSUSBH_T::UIENR: UERRIEN Mask          */

#define HSUSBH_UIENR_PCIEN_Pos           (2)                                               /*!< HSUSBH_T::UIENR: PCIEN Position        */
#define HSUSBH_UIENR_PCIEN_Msk           (0x1ul << HSUSBH_UIENR_PCIEN_Pos)                 /*!< HSUSBH_T::UIENR: PCIEN Mask            */

#define HSUSBH_UIENR_FLREN_Pos           (3)                                               /*!< HSUSBH_T::UIENR: FLREN Position        */
#define HSUSBH_UIENR_FLREN_Msk           (0x1ul << HSUSBH_UIENR_FLREN_Pos)                 /*!< HSUSBH_T::UIENR: FLREN Mask            */

#define HSUSBH_UIENR_HSERREN_Pos         (4)                                               /*!< HSUSBH_T::UIENR: HSERREN Position      */
#define HSUSBH_UIENR_HSERREN_Msk         (0x1ul << HSUSBH_UIENR_HSERREN_Pos)               /*!< HSUSBH_T::UIENR: HSERREN Mask          */

#define HSUSBH_UIENR_IAAEN_Pos           (5)                                               /*!< HSUSBH_T::UIENR: IAAEN Position        */
#define HSUSBH_UIENR_IAAEN_Msk           (0x1ul << HSUSBH_UIENR_IAAEN_Pos)                 /*!< HSUSBH_T::UIENR: IAAEN Mask            */

#define HSUSBH_UFINDR_FI_Pos             (0)                                               /*!< HSUSBH_T::UFINDR: FI Position          */
#define HSUSBH_UFINDR_FI_Msk             (0x3ffful << HSUSBH_UFINDR_FI_Pos)                /*!< HSUSBH_T::UFINDR: FI Mask              */

#define HSUSBH_UPFLBAR_BADDR_Pos         (12)                                              /*!< HSUSBH_T::UPFLBAR: BADDR Position      */
#define HSUSBH_UPFLBAR_BADDR_Msk         (0xffffful << HSUSBH_UPFLBAR_BADDR_Pos)           /*!< HSUSBH_T::UPFLBAR: BADDR Mask          */

#define HSUSBH_UCALAR_LPL_Pos            (5)                                               /*!< HSUSBH_T::UCALAR: LPL Position         */
#define HSUSBH_UCALAR_LPL_Msk            (0x7fffffful << HSUSBH_UCALAR_LPL_Pos)            /*!< HSUSBH_T::UCALAR: LPL Mask             */

#define HSUSBH_UCFGR_CF_Pos              (0)                                               /*!< HSUSBH_T::UCFGR: CF Position           */
#define HSUSBH_UCFGR_CF_Msk              (0x1ul << HSUSBH_UCFGR_CF_Pos)                    /*!< HSUSBH_T::UCFGR: CF Mask               */

#define HSUSBH_UPSCR_CCS_Pos             (0)                                               /*!< HSUSBH_T::UPSCR: CCS Position          */
#define HSUSBH_UPSCR_CCS_Msk             (0x1ul << HSUSBH_UPSCR_CCS_Pos)                   /*!< HSUSBH_T::UPSCR: CCS Mask              */

#define HSUSBH_UPSCR_CSC_Pos             (1)                                               /*!< HSUSBH_T::UPSCR: CSC Position          */
#define HSUSBH_UPSCR_CSC_Msk             (0x1ul << HSUSBH_UPSCR_CSC_Pos)                   /*!< HSUSBH_T::UPSCR: CSC Mask              */

#define HSUSBH_UPSCR_PE_Pos              (2)                                               /*!< HSUSBH_T::UPSCR: PE Position           */
#define HSUSBH_UPSCR_PE_Msk              (0x1ul << HSUSBH_UPSCR_PE_Pos)                    /*!< HSUSBH_T::UPSCR: PE Mask               */

#define HSUSBH_UPSCR_PEC_Pos             (3)                                               /*!< HSUSBH_T::UPSCR: PEC Position          */
#define HSUSBH_UPSCR_PEC_Msk             (0x1ul << HSUSBH_UPSCR_PEC_Pos)                   /*!< HSUSBH_T::UPSCR: PEC Mask              */

#define HSUSBH_UPSCR_OCA_Pos             (4)                                               /*!< HSUSBH_T::UPSCR: OCA Position          */
#define HSUSBH_UPSCR_OCA_Msk             (0x1ul << HSUSBH_UPSCR_OCA_Pos)                   /*!< HSUSBH_T::UPSCR: OCA Mask              */

#define HSUSBH_UPSCR_OCC_Pos             (5)                                               /*!< HSUSBH_T::UPSCR: OCC Position          */
#define HSUSBH_UPSCR_OCC_Msk             (0x1ul << HSUSBH_UPSCR_OCC_Pos)                   /*!< HSUSBH_T::UPSCR: OCC Mask              */

#define HSUSBH_UPSCR_FPR_Pos             (6)                                               /*!< HSUSBH_T::UPSCR: FPR Position          */
#define HSUSBH_UPSCR_FPR_Msk             (0x1ul << HSUSBH_UPSCR_FPR_Pos)                   /*!< HSUSBH_T::UPSCR: FPR Mask              */

#define HSUSBH_UPSCR_SUSPEND_Pos         (7)                                               /*!< HSUSBH_T::UPSCR: SUSPEND Position      */
#define HSUSBH_UPSCR_SUSPEND_Msk         (0x1ul << HSUSBH_UPSCR_SUSPEND_Pos)               /*!< HSUSBH_T::UPSCR: SUSPEND Mask          */

#define HSUSBH_UPSCR_PRST_Pos            (8)                                               /*!< HSUSBH_T::UPSCR: PRST Position         */
#define HSUSBH_UPSCR_PRST_Msk            (0x1ul << HSUSBH_UPSCR_PRST_Pos)                  /*!< HSUSBH_T::UPSCR: PRST Mask             */

#define HSUSBH_UPSCR_LSTS_Pos            (10)                                              /*!< HSUSBH_T::UPSCR: LSTS Position         */
#define HSUSBH_UPSCR_LSTS_Msk            (0x3ul << HSUSBH_UPSCR_LSTS_Pos)                  /*!< HSUSBH_T::UPSCR: LSTS Mask             */

#define HSUSBH_UPSCR_PP_Pos              (12)                                              /*!< HSUSBH_T::UPSCR: PP Position           */
#define HSUSBH_UPSCR_PP_Msk              (0x1ul << HSUSBH_UPSCR_PP_Pos)                    /*!< HSUSBH_T::UPSCR: PP Mask               */

#define HSUSBH_UPSCR_PO_Pos              (13)                                              /*!< HSUSBH_T::UPSCR: PO Position           */
#define HSUSBH_UPSCR_PO_Msk              (0x1ul << HSUSBH_UPSCR_PO_Pos)                    /*!< HSUSBH_T::UPSCR: PO Mask               */

#define HSUSBH_UPSCR_PTC_Pos             (16)                                              /*!< HSUSBH_T::UPSCR: PTC Position          */
#define HSUSBH_UPSCR_PTC_Msk             (0xful << HSUSBH_UPSCR_PTC_Pos)                   /*!< HSUSBH_T::UPSCR: PTC Mask              */

/**@}*/ /* HSUSBH_CONST */
/**@}*/ /* end of HSUSBH register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
    #pragma no_anon_unions
#endif

#endif /* __HSUSBH_REG_H__ */
