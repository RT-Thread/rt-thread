/**
 * \file
 *
 * \brief SAM Peripheral Access Controller Driver
 *
 * Copyright (C) 2012-2016 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#ifndef PAC_H_INCLUDED
#define PAC_H_INCLUDED

/**
 * \defgroup asfdoc_sam0_pac_group SAM Peripheral Access Controller (PAC) Driver
 *
 * This driver for Atmel&reg; | SMART ARM&reg;-based microcontroller provides
 * an interface for the locking and unlocking of peripheral registers within
 * the device. When a peripheral is locked, accidental writes to the peripheral
 * will be blocked and a CPU exception will be raised.
 *
 * The following peripherals are used by this module:
 *  - PAC (Peripheral Access Controller)
 *
 * The following devices can use this module:
 *  - Atmel | SMART SAM D20/D21
 *  - Atmel | SMART SAM R21
 *  - Atmel | SMART SAM D09/D10/D11
 *  - Atmel | SMART SAM L21/L22
 *  - Atmel | SMART SAM DA1
 *  - Atmel | SMART SAM C20/C21
 *  - Atmel | SMART SAM HA1
 *
 * The outline of this documentation is as follows:
 *  - \ref asfdoc_sam0_pac_prerequisites
 *  - \ref asfdoc_sam0_pac_module_overview
 *  - \ref asfdoc_sam0_pac_special_considerations
 *  - \ref asfdoc_sam0_pac_extra_info
 *  - \ref asfdoc_sam0_pac_examples
 *  - \ref asfdoc_sam0_pac_api_overview
 *
 *
 * \section asfdoc_sam0_pac_prerequisites Prerequisites
 *
 * There are no prerequisites for this module.
 *
 *
 * \section asfdoc_sam0_pac_module_overview Module Overview
 *
 * The SAM devices are fitted with a Peripheral Access Controller (PAC)
 * that can be used to lock and unlock write access to a peripheral's
 * registers (see \ref asfdoc_sam0_pac_non_write_protected). Locking a
 * peripheral minimizes the risk of unintended configuration changes to a
 * peripheral as a consequence of \ref asfdoc_sam0_pac_code_run_away
 * or use of a \ref asfdoc_sam0_pac_module_pointer.
 *
 * Physically, the PAC restricts write access through the AHB bus to registers
 * used by the peripheral, making the register non-writable. PAC locking of
 * modules should be implemented in configuration critical applications where
 * avoiding unintended peripheral configuration changes are to be regarded in
 * the highest of priorities.
 *
 * All interrupt must be disabled while a peripheral is unlocked to make sure
 * correct lock/unlock scheme is upheld.
 *
 * \subsection asfdoc_sam0_pac_locking_scheme Locking Scheme
 * The module has a built in safety feature requiring that an already locked
 * peripheral is not relocked, and that already unlocked peripherals are not
 * unlocked again. Attempting to unlock and already unlocked peripheral, or
 * attempting to lock a peripheral that is currently locked will generate a
 * CPU exception. This implies that the implementer must keep
 * strict control over the peripheral's lock-state before modifying them. With
 * this added safety, the probability of stopping runaway code increases as
 * the program pointer can be caught inside the exception handler, and necessary
 * countermeasures can be initiated. The implementer should also consider using
 * sanity checks after an unlock has been performed to further increase the
 * security.
 *
 * \subsection asfdoc_sam0_pac_correct_implementation Recommended Implementation
 * A recommended implementation of the PAC can be seen in
 * \ref asfdoc_sam0_pac_rec_imp_diagram "the figure below".
 *
 * \anchor asfdoc_sam0_pac_rec_imp_diagram
 * \dot
 *	digraph correct {
 *		subgraph cluster_a {
 *			style="filled, dotted";
 *			coler=lightgray;
 *			init [label="Initialize Peripheral", shape=box];
 *			lock [label="Lock peripheral", shape=box];
 *			label="Initialization and code";
 *			init -> lock;
 *		}
 *		subgraph cluster_b {
 *			cli [label="Disable global interrupts", shape=box,
 *				style=dotted];
 *			unlock [label="Unlock peripheral", shape=box];
 *			sanity [label="Sanity Check", shape=box, style=dotted];
 *			modify [label="Modify peripheral", shape=box];
 *			lock2 [label="Lock peripheral", shape=box];
 *			sei [label="Enable global interrupts", shape=box
 *				style=dotted];
*
 *			label="Peripheral Modification";
 *			cli -> unlock;
 *			unlock -> sanity
 *			sanity -> modify;
 *			modify -> lock2;
 *			lock2 -> sei;
 *		}
 *		lock -> cli [label=
 *			"Other initialization\n and enable interrupts if applicable"
 *				, style=dotted];
 *	}
 * \enddot
 *
 * \subsection asfdoc_sam0_pac_enabled_interrupt Why Disable Interrupts
 * Global interrupts must be disabled while a peripheral is unlocked as an
 * interrupt handler would not know the current state of the peripheral lock. If
 * the interrupt tries to alter the lock state, it can cause an exception as it
 * potentially tries to unlock an already unlocked peripheral. Reading current
 * lock state is to be avoided as it removes the security provided by the PAC
 * (\ref asfdoc_sam0_pac_check_lock).
 *
 * \note Global interrupts should also be disabled when a peripheral is unlocked
 *       inside an interrupt handler.
 *
 * An example to illustrate the potential hazard of not disabling interrupts is
 * shown in \ref asfdoc_sam0_pac_int_hazard_diagram "the diagram below".
 *
 * \anchor asfdoc_sam0_pac_int_hazard_diagram
 * \dot
 *	digraph enabled_interrupt {
 *		subgraph cluster_0{
 *			label="Main routine";
 *			{node [style="filled", color=black, fillcolor=white]
 *			init [label="Initialize and lock peripherals", shape=box];
 *			main_unlock [label="Unlock peripheral",	shape=box,
 *				fillcolor=green];
 *			main_modify [label="Modify peripheral", shape=box];}
 *			main_lock [label="Lock peripheral", shape=box];
 *			init -> main_unlock [label="User code"];
 *			main_unlock -> main_modify;
 *			main_modify -> main_lock [style=dotted];
 *		}
 *		subgraph cluster_1 {
 *			label="Interrupt handler";
 *			int_unlock [label="Unlock peripheral", shape=box,
 *				style=filled, fillcolor=red];
 *			int_modify [label="Modify peripheral", shape=box];
 *			int_lock [label="Lock peripheral", shape=box];
 *			int_unlock -> int_modify [style=dotted];
 *			int_modify -> int_lock [style=dotted];
 *		}
 *		exception [label="Exception", shape=box, style=filled, fillcolor=red];
 *		main_modify -> int_unlock [label=" Interrupt"];
 *		int_unlock -> exception;
 *		exception -> exception;
 *	}
 * \enddot
 *
 * \subsection asfdoc_sam0_pac_code_run_away Run-away Code
 * Run-away code can be caused by the MCU being operated outside its
 * specification, faulty code, or EMI issues. If a runaway code occurs, it is
 * favorable to catch the issue as soon as possible. With a correct
 * implementation of the PAC, the runaway code can potentially be stopped.
 *
 * A graphical example showing how a PAC implementation will behave for
 * different circumstances of runaway code in shown in
 * \ref asfdoc_sam0_pac_code_runaway_diagram "the first" and
 * \ref asfdoc_sam0_pac_code_runaway_diagram2 "second figures below".
 *
 * \anchor asfdoc_sam0_pac_code_runaway_diagram
 * \dot
 *	digraph run_away {
 *	   subgraph cluster_away1{
 *		rankdir=TB;
 *		color=white;
 *		runaway1 [label="Run-away code", shape=box];
 *		node [shape=plaintext];
 *		program1 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td>0x0020</td>
 *					<td>initialize peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0025</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>...</td>
 *					<td>...</td>
 *				</tr>
 *				<tr>
 *					<td>0x0080</td>
 *					<td>set sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="green">...</td>
 *					<td BGCOLOR="green">...</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0115</td>
 *					<td BGCOLOR="green">disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0120</td>
 *					<td BGCOLOR="green">unlock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="red">0x0125</td>
 *					<td BGCOLOR="red">check sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td>0x0130</td>
 *					<td>modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0140</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0145</td>
 *					<td>disable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway1 -> program1:f0;
 *			label="1. Run-away code is caught in sanity check.\nA CPU exception is executed."
 *		}
 *	   subgraph cluster_away2{
 *		rankdir=TB;
 *		runaway2 [label="Run-away code", shape=box];
 *		color=white;
 *		node [shape=plaintext];
 *		program2 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td>0x0020</td>
 *					<td>initialize peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0025</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>...</td>
 *					<td>...</td>
 *				</tr>
 *				<tr>
 *					<td>0x0080</td>
 *					<td>set sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td >...</td>
 *					<td >...</td>
 *				</tr>
 *				<tr>
 *					<td >0x0115</td>
 *					<td >disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td >0x0120</td>
 *					<td >unlock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td >0x0125</td>
 *					<td >check sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="red">0x0130</td>
 *					<td BGCOLOR="red">modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0140</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0145</td>
 *					<td>disable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway2 -> program2:f0;
 *			label="2. Run-away code is caught when modifying\nlocked peripheral. A CPU exception is executed."
 *		}
 *	}
 * \enddot
 *
 * \anchor asfdoc_sam0_pac_code_runaway_diagram2
 * \dot
 *	digraph run_away2 {
 *	   subgraph cluster_away3{
 *		rankdir=TB;
 *		runaway3 [label="Run-away code", shape=box];
 *		color=white;
 *		node [shape=plaintext];
 *		program3 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td>0x0020</td>
 *					<td>initialize peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0025</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>...</td>
 *					<td>...</td>
 *				</tr>
 *				<tr>
 *					<td>0x0080</td>
 *					<td>set sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td >...</td>
 *					<td >...</td>
 *				</tr>
 *				<tr>
 *					<td >0x0115</td>
 *					<td >disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td >0x0120</td>
 *					<td >unlock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td >0x0125</td>
 *					<td >check sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td >0x0130</td>
 *					<td >modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="red">0x0140</td>
 *					<td BGCOLOR="red">lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0145</td>
 *					<td>disable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway3 -> program3:f0;
 *			label="3. Run-away code is caught when locking\nlocked peripheral. A CPU exception is executed."
 *		}
 *	subgraph cluster_away4 {
 *		rankdir=TB;
 *		runaway4 [label="Run-away code", shape=box];
 *		color=white;
 *		node [shape=plaintext];
 *		program4 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td>0x0020</td>
 *					<td>initialize peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0025</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="green">...</td>
 *					<td BGCOLOR="green">...</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0080</td>
 *					<td BGCOLOR="green">set sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">...</td>
 *					<td BGCOLOR="green">...</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0115</td>
 *					<td BGCOLOR="green">disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0120</td>
 *					<td BGCOLOR="green">unlock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0125</td>
 *					<td BGCOLOR="green">check sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0130</td>
 *					<td BGCOLOR="green">modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0140</td>
 *					<td BGCOLOR="green">lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0145</td>
 *					<td BGCOLOR="green">disable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway4 -> program4:f0;
 *			label="4. Run-away code is not caught.\n "
 *		}
 *	}
 * \enddot
 *
 * In the example, green indicates that the command is allowed, red indicates
 * where the runaway code will be caught, and the arrow where the runaway
 * code enters the application. In special circumstances, like example 4
 * above, the runaway code will not be caught. However, the protection scheme
 * will greatly enhance peripheral configuration security from being affected by
 * runaway code.
 *
 * \subsubsection asfdoc_sam0_pac_bitwise_code Key-Argument
 * To protect the module functions against runaway code themselves, a key
 * is required as one of the input arguments. The key-argument will make sure
 * that runaway code entering the function without a function call will be
 * rejected before inflicting any damage. The argument is simply set to be
 * the bitwise inverse of the module flag, i.e.
 *
 * \code
	system_peripheral_<lock_state>(SYSTEM_PERIPHERAL_<module>,
			~SYSTEM_PERIPHERAL_<module>);
\endcode
 *
 * Where the lock state can be either lock or unlock, and module refer to the
 * peripheral that is to be locked/unlocked.
 *
 * \subsection asfdoc_sam0_pac_module_pointer Faulty Module Pointer
 * The PAC also protects the application from user errors such as the use of
 * incorrect module pointers in function arguments, given that the module is
 * locked. It is therefore recommended that any unused peripheral is locked
 * during application initialization.
 *
 * \subsection asfdoc_sam0_pac_no_inline Use of __no_inline
 * Using the function attribute \c __no_inline will ensure that there will only be
 * one copy of each functions in the PAC driver API in the application. This will
 * lower the likelihood that runaway code will hit any of these functions.
 *
 * \subsection asfdoc_sam0_pac_module_overview_physical Physical Connection
 *
 * \ref asfdoc_sam0_pac_int_connections "The diagram below" shows how this
 * module is interconnected within the device.
 *
 * \anchor asfdoc_sam0_pac_int_connections
 * \dot
 * digraph overview {
 *	nodesep = .05;
 *	rankdir=LR;
 *
 *	ahb [label="Peripheral bus", shape=ellipse, style=filled, fillcolor=lightgray];
 *	pac [label="<f0>PAC|<f1>Lock|<f2>Open|<f3>Open",
 *		 height=2.5, shape=record, width=.1];
 *	per1 [label="Peripheral1", shape=ellipse, style=filled, fillcolor=lightgray];
 *	per2 [label="Peripheral2", shape=ellipse, style=filled, fillcolor=lightgray];
 *	per3 [label="Peripheral3", shape=ellipse, style=filled, fillcolor=lightgray];
 *	edge [dir="both"];
 *	ahb -> pac:f1 [label="Read/Write"];
 *	ahb -> pac:f2 [label="Read/Write"];
 *	ahb -> pac:f3 [label="Read/Write"];
 *	edge [dir="back"];
 *	pac:f1 -> per1 [label="Read"];
 *	edge [dir="both"];
 *	pac:f2 -> per2 [label="Read/Write"];
 *	pac:f3 -> per3 [label="Read/Write"];
 *	{rank=same; per1 per2 per3 }
 * }
 * \enddot
 *
 *
 * \section asfdoc_sam0_pac_special_considerations Special Considerations
 *
 * \subsection asfdoc_sam0_pac_non_write_protected Non-Writable Registers
 * Not all registers in a given peripheral can be set non-writable. Which
 * registers this applies to is showed in \ref asfdoc_sam0_pac_non_write_list
 * and the peripheral's subsection "Register Access Protection" in the device
 * datasheet.
 *
 * \subsection asfdoc_sam0_pac_check_lock Reading Lock State
 * Reading the state of the peripheral lock is to be avoided as it greatly
 * compromises the protection initially provided by the PAC. If a lock/unlock
 * is implemented conditionally, there is a risk that eventual errors are not
 * caught in the protection scheme. Examples indicating the issue are shown
 * in \ref asfdoc_sam0_pac_lock_errors_diagram "the diagram below".
 *
 * \anchor asfdoc_sam0_pac_lock_errors_diagram
 * \dot
 *	digraph read_lock {
 *	   subgraph cluster_read1{
 *		rankdir=TB;
 *		color=white;
 *		runaway1 [label="Run-away code\nwith peripheral unlocked", shape=box];
 *		node [shape=plaintext];
 *		program1 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="green">...</td>
 *					<td BGCOLOR="green">...</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0100</td>
 *					<td BGCOLOR="green">check if locked</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0102</td>
 *					<td BGCOLOR="green">disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0105</td>
 *					<td BGCOLOR="green">unlock if locked</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0110</td>
 *					<td BGCOLOR="green">check sanity</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0115</td>
 *					<td BGCOLOR="green">modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0120</td>
 *					<td BGCOLOR="green">lock if previously locked</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0125</td>
 *					<td BGCOLOR="green">enable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway1 -> program1:f0;
 *			label="1. Wrong implementation.\n "
 *		}
 *	   subgraph cluster_read2{
 *		rankdir=TB;
 *		color=white;
 *		runaway2 [label="Run-away code\nwith peripheral unlocked", shape=box];
 *		node [shape=plaintext];
 *		program2 [label=<
 *			<table>
 *				<tr>
 *					<td>PC#</td>
 *					<td>Code</td>
 *				</tr>
 *				<tr>
 *					<td port="f0" BGCOLOR="green">...</td>
 *					<td BGCOLOR="green">...</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="green">0x0100</td>
 *					<td BGCOLOR="green">disable interrupts</td>
 *				</tr>
 *				<tr>
 *					<td BGCOLOR="red">0x0120</td>
 *					<td BGCOLOR="red">unlock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0125</td>
 *					<td>check sanity argument</td>
 *				</tr>
 *				<tr>
 *					<td>0x0130</td>
 *					<td>modify peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0140</td>
 *					<td>lock peripheral</td>
 *				</tr>
 *				<tr>
 *					<td>0x0145</td>
 *					<td>disable interrupts</td>
 *				</tr>
 *			</table>
 *			>]
 *			runaway2 -> program2:f0;
 *
 *			label="2. Correct implementation.\n "
 *		}
 *	}
 * \enddot
 *
 * In the left figure above, one can see the runaway code continues as all
 * illegal operations are conditional. On the right side figure, the runaway
 * code is caught as it tries to unlock the peripheral.
 *
 * \section asfdoc_sam0_pac_extra_info Extra Information
 *
 * For extra information, see \ref asfdoc_sam0_pac_extra. This includes:
 *  - \ref asfdoc_sam0_pac_extra_acronyms
 *  - \ref asfdoc_sam0_pac_extra_dependencies
 *  - \ref asfdoc_sam0_pac_extra_errata
 *  - \ref asfdoc_sam0_pac_extra_history
 *
 *
 * \section asfdoc_sam0_pac_examples Examples
 *
 * For a list of examples related to this driver, see
 * \ref asfdoc_sam0_pac_exqsg.
 *
 *
 * \section asfdoc_sam0_pac_api_overview API Overview
 * @{
 */

#include <compiler.h>
#include <system.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Retrieves the ID of a specified peripheral name, giving its peripheral bus
 * location.
 *
 * \param[in] peripheral  Name of the peripheral instance
 *
 * \returns Bus ID of the specified peripheral instance.
 */
#define SYSTEM_PERIPHERAL_ID(peripheral)    ID_##peripheral

/** \name Peripheral Lock and Unlock
 * @{
 */
__no_inline enum status_code system_peripheral_lock(
		const uint32_t peripheral_id,
		const uint32_t key);

__no_inline enum status_code system_peripheral_unlock(
		const uint32_t peripheral_id,
		const uint32_t key);
/** @}  */

#if (SAML21) || (SAML22) || (SAMC20) || (SAMC21) || (SAMR30) || defined(__DOXYGEN__)
/** \name APIs available for SAM L21/L22/C20/C21.
 * @{
 */
__no_inline enum status_code system_peripheral_lock_always(
		const uint32_t peripheral_id,
		const uint32_t key);

/**
 * \brief Enable PAC interrupt.
 *
 * Enable PAC interrupt so can trigger execution on peripheral access error,
 * see \ref SYSTEM_Handler().
 *
 */
static inline void system_pac_enable_interrupt(void)
{
	PAC->INTENSET.reg = PAC_INTENSET_ERR;
}

/**
 * \brief Disable PAC interrupt.
 *
 * Disable PAC interrupt on peripheral access error.
 *
 */
static inline void system_pac_disable_interrupt(void)
{
	PAC->INTENCLR.reg = PAC_INTENCLR_ERR;
}

/**
 * \brief Enable PAC event output.
 *
 * Enable PAC event output on peripheral access error.
 *
 */
static inline void system_pac_enable_event(void)
{
	PAC->EVCTRL.reg = PAC_EVCTRL_ERREO;
}

/**
 * \brief Disable PAC event output.
 *
 * Disable PAC event output on peripheral access error.
 *
 */
static inline void system_pac_disable_event(void)
{
	PAC->EVCTRL.reg &= (~PAC_EVCTRL_ERREO);
}

/** @}  */
#endif

#ifdef __cplusplus
}
#endif

/** @}  */

/**
 * \page asfdoc_sam0_pac_extra Extra Information for PAC Driver
 *
 * \section asfdoc_sam0_pac_extra_acronyms Acronyms
 * Below is a table listing the acronyms used in this module, along with their
 * intended meanings.
 *
 * <table>
 *	<tr>
 *		<th>Acronym</td>
 *		<th>Description</td>
 *	</tr>
 *  <tr>
 *		<td>AC</td>
 *		<td>Analog Comparator</td>
 *	</tr>
 *	<tr>
 *		<td>ADC</td>
 *		<td>Analog-to-Digital Converter</td>
 *	</tr>
 *	<tr>
 *		<td>EVSYS</td>
 *		<td>Event System</td>
 *	</tr>
 *	<tr>
 *		<td>NMI</td>
 *		<td>Non-Maskable Interrupt</td>
 *	</tr>
 *	<tr>
 *		<td>NVMCTRL</td>
 *		<td>Non-Volatile Memory Controller</td>
 *	</tr>
 *	<tr>
 *		<td>PAC</td>
 *		<td>Peripheral Access Controller</td>
 *	</tr>
  *	<tr>
 *		<td>PM</td>
 *		<td>Power Manager</td>
 *	</tr>
 *	<tr>
 *		<td>RTC</td>
 *		<td>Real-Time Counter</td>
 *	</tr>
 *	<tr>
 *		<td>SERCOM</td>
 *		<td>Serial Communication Interface</td>
 *	</tr>
 *	<tr>
 *		<td>SYSCTRL</td>
 *		<td>System Controller</td>
 *	</tr>
 *	<tr>
 *		<td>TC</td>
 *		<td>Timer/Counter</td>
 *	</tr>
 *	<tr>
 *		<td>WDT</td>
 *		<td>Watch Dog Timer</td>
 *	</tr>
 * </table>
 *
 *
 * \section asfdoc_sam0_pac_extra_dependencies Dependencies
 * This driver has the following dependencies:
 *
 *  - None
 *
 *
 * \section asfdoc_sam0_pac_extra_errata Errata
 * There are no errata related to this driver.
 *
 *
 * \section asfdoc_sam0_pac_extra_history Module History
 * An overview of the module history is presented in the table below, with
 * details on the enhancements and fixes made to the module since its first
 * release. The current version of this corresponds to the newest version in
 * the table.
 *
 * <table>
 *	<tr>
 *		<th>Changelog</th>
 *	</tr>
 *	<tr>
 *		<td>Initial Release</td>
 *	</tr>
 * </table>
 */

/**
 * \page asfdoc_sam0_pac_exqsg Examples for PAC Driver
 *
 * This is a list of the available Quick Start guides (QSGs) and example
 * applications for \ref asfdoc_sam0_pac_group. QSGs are simple examples with
 * step-by-step instructions to configure and use this driver in a selection of
 * use cases. Note that a QSG can be compiled as a standalone application or be
 * added to the user application.
 *
 *  - \subpage asfdoc_sam0_pac_basic_use_case
 */

/**
 * \page asfdoc_sam0_pac_non_write_list List of Non-Write Protected Registers
 *
 * Look in device datasheet peripheral's subsection "Register Access
 * Protection" to see which is actually available for your device.
 * <table>
 *	<tr>
 *		<th>Module</th>
 *		<th>Non-write protected register</th>
 *	</tr>
 *	<tr>
 *		<td>AC</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUSA</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUSB</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUSC</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>ADC</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>RESULT</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>EVSYS</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>CHSTATUS</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>NVMCTRL</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>PM</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>PORT</td>
 *		<td>N/A</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>RTC</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>READREQ</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>SYSCTRL</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>SERCOM</td>
 *		<td>INTFALG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>DATA</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>TC</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr><td colspan="2"/></tr>
 *	<tr>
 *		<td>WDT</td>
 *		<td>INTFLAG</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>STATUS</td>
 *	</tr>
 *	<tr>
 *		<td></td>
 *		<td>(CLEAR)</td>
 *	</tr>
 * </table>
 *
 * \page asfdoc_sam0_pac_document_revision_history Document Revision History
 *
 * <table>
 *	<tr>
 *		<th>Doc. Rev.</td>
 *		<th>Date</td>
 *		<th>Comments</td>
 *	</tr>
 *	<tr>
 *		<td>42107F</td>
 *		<td>12/2015</td>
 *		<td>Added support for SAM L21/L22, SAM C20/C21, SAM D09, and SAM DA1</td>
 *	</tr>
 *	<tr>
 *		<td>42107E</td>
 *		<td>12/2014</td>
 *		<td>Added support for SAM R21 and SAM D10/D11</td>
 *	</tr>
 *	<tr>
 *		<td>42107D</td>
 *		<td>01/2014</td>
 *		<td>Added support for SAM D21</td>
 *	</tr>
 *	<tr>
 *		<td>42107C</td>
 *		<td>10/2013</td>
 *		<td>Extended acronyms list</td>
 *	</tr>
 *	<tr>
 *		<td>42107B</td>
 *		<td>06/2013</td>
 *		<td>Corrected documentation typos</td>
 *	</tr>
 *	<tr>
 *		<td>42107A</td>
 *		<td>06/2013</td>
 *		<td>Initial document release</td>
 *	</tr>
 * </table>
 */

#endif /* PAC_H_INCLUDED */

