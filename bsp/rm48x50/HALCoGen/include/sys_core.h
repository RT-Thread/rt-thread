/** @file sys_core.h
*   @brief System Core Header File
*   @date 29.May.2013
*   @version 03.05.02
*   
*   This file contains:
*   - Core Interface Functions
*   .
*   which are relevant for the System driver.
*/

/* (c) Texas Instruments 2009-2013, All rights reserved. */

#ifndef __SYS_CORE_H__
#define __SYS_CORE_H__

#include "sys_common.h"

/* USER CODE BEGIN (0) */
/* USER CODE END */


/* System Core Interface Functions */

/** @fn void _coreInitRegisters_(void)
*   @brief Initialize Core register
*/
void _coreInitRegisters_(void);

/** @fn void _coreInitStackPointer_(void)
*   @brief Initialize Core stack pointer
*/
void _coreInitStackPointer_(void);

/** @fn void _getCPSRValue_(void)
*   @brief Get CPSR Value
*/
uint32 _getCPSRValue_(void);

/** @fn void _gotoCPUIdle_(void)
*   @brief Take CPU to Idle state
*/
void _gotoCPUIdle_(void);

/** @fn void _coreEnableIrqVicOffset_(void)
*   @brief Enable Irq offset propagation via Vic controller
*/
void _coreEnableIrqVicOffset_(void);

/** @fn void _coreEnableVfp_(void)
*   @brief Enable vector floating point unit
*/
void _coreEnableVfp_(void);

/** @fn void _coreEnableEventBusExport_(void)
*   @brief Enable event bus export for external monitoring modules
*   @note It is required to enable event bus export to process ecc issues.
*
*   This function enables event bus exports to external monitoring modules
*   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
*/
void _coreEnableEventBusExport_(void);

/** @fn void _coreDisableEventBusExport_(void)
*   @brief Disable event bus export for external monitoring modules
*
*   This function disables event bus exports to external monitoring modules
*   like tightly coupled RAM wrapper, Flash wrapper and error signaling module.
*/
void _coreDisableEventBusExport_(void);

/** @fn void _coreEnableRamEcc_(void)
*   @brief Enable external ecc error for RAM odd and even bank
*   @note It is required to enable event bus export to process ecc issues.
*/
void _coreEnableRamEcc_(void);

/** @fn void _coreDisableRamEcc_(void)
*   @brief Disable external ecc error for RAM odd and even bank
*/
void _coreDisableRamEcc_(void);

/** @fn void _coreEnableFlashEcc_(void)
*   @brief Enable external ecc error for the Flash
*   @note It is required to enable event bus export to process ecc issues.
*/
void _coreEnableFlashEcc_(void);

/** @fn void _coreDisableFlashEcc_(void)
*   @brief Disable external ecc error for the Flash
*/
void _coreDisableFlashEcc_(void);

/** @fn uint32 _coreGetDataFault_(void)
*   @brief Get core data fault status register
*   @return The function will return the data fault status register value:
*           - bit [10,3..0]: 
*                            - 0b00001: Alignment                -> address is valid
*                            - 0b00000: Background               -> address is valid
*                            - 0b01101: Permission               -> address is valid
*                            - 0b01000: Precise External Abort   -> address is valid
*                            - 0b10110: Imprecise External Abort -> address is unpredictable
*                            - 0b11001: Precise ECC Error        -> address is valid
*                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
*                            - 0b00010: Debug                    -> address is unchanged
*           - bit [11]: 
*                            - 0: Read
*                            - 1: Write
*           - bit [12]: 
*                            - 0: AXI Decode Error (DECERR)
*                            - 1: AXI Slave Error (SLVERR)
*/
uint32 _coreGetDataFault_(void);

/** @fn void _coreClearDataFault_(void)
*   @brief Clear core data fault status register
*/
void _coreClearDataFault_(void);

/** @fn uint32 _coreGetInstructionFault_(void)
*   @brief Get core instruction fault status register
*   @return The function will return the instruction fault status register value:
*           - bit [10,3..0]: 
*                            - 0b00001: Alignment                -> address is valid
*                            - 0b00000: Background               -> address is valid
*                            - 0b01101: Permission               -> address is valid
*                            - 0b01000: Precise External Abort   -> address is valid
*                            - 0b10110: Imprecise External Abort -> address is unpredictable
*                            - 0b11001: Precise ECC Error        -> address is valid
*                            - 0b11000: Imprecise ECC Error      -> address is unpredictable
*                            - 0b00010: Debug                    -> address is unchanged
*           - bit [12]: 
*                            - 0: AXI Decode Error (DECERR)
*                            - 1: AXI Slave Error (SLVERR)
*/
uint32 _coreGetInstructionFault_(void);

/** @fn void _coreClearInstructionFault_(void)
*   @brief Clear core instruction fault status register
*/
void _coreClearInstructionFault_(void);

/** @fn uint32 _coreGetDataFaultAddress_(void)
*   @brief Get core data fault address register
*   @return The function will return the data fault address:
*/
uint32 _coreGetDataFaultAddress_(void);

/** @fn void _coreClearDataFaultAddress_(void)
*   @brief Clear core data fault address register
*/
void _coreClearDataFaultAddress_(void);

/** @fn uint32 _coreGetInstructionFaultAddress_(void)
*   @brief Get core instruction fault address register
*   @return The function will return the instruction fault address:
*/
uint32 _coreGetInstructionFaultAddress_(void);

/** @fn void _coreClearInstructionFaultAddress_(void)
*   @brief Clear core instruction fault address register
*/
void _coreClearInstructionFaultAddress_(void);

/** @fn uint32 _coreGetAuxiliaryDataFault_(void)
*   @brief Get core auxiliary data fault status register
*   @return The function will return the auxiliary data fault status register value:
*           - bit [13..5]:
*                            - Index value for access giving error
*           - bit [21]: 
*                            - 0: Unrecoverable error
*                            - 1: Recoverable error
*           - bit [23..22]:
*                            - 0: Side cache
*                            - 1: Side ATCM (Flash)
*                            - 2: Side BTCM (RAM)
*                            - 3: Reserved
*           - bit [27..24]: 
*                            - Cache way or way in which error occurred
*/
uint32 _coreGetAuxiliaryDataFault_(void);

/** @fn void _coreClearAuxiliaryDataFault_(void)
*   @brief Clear core auxiliary data fault status register
*/
void _coreClearAuxiliaryDataFault_(void);

/** @fn uint32 _coreGetAuxiliaryInstructionFault_(void)
*   @brief Get core auxiliary instruction fault status register
*   @return The function will return the auxiliary instruction fault status register value:
*           - bit [13..5]:
*                            - Index value for access giving error
*           - bit [21]: 
*                            - 0: Unrecoverable error
*                            - 1: Recoverable error
*           - bit [23..22]:
*                            - 0: Side cache
*                            - 1: Side ATCM (Flash)
*                            - 2: Side BTCM (RAM)
*                            - 3: Reserved
*           - bit [27..24]: 
*                            - Cache way or way in which error occurred
*/
uint32 _coreGetAuxiliaryInstructionFault_(void);

/** @fn void _coreClearAuxiliaryInstructionFault_(void)
*   @brief Clear core auxiliary instruction fault status register
*/
void _coreClearAuxiliaryInstructionFault_(void);

/** @fn void _disable_interrupt_(void)
*   @brief Disable IRQ and FIQ Interrupt mode in CPSR register
*
*   This function disables IRQ and FIQ Interrupt mode in CPSR register.
*/
void _disable_interrupt_(void);

/** @fn void _disable_IRQ_interrupt_(void)
*   @brief Disable IRQ Interrupt mode in CPSR register
*
*   This function disables IRQ Interrupt mode in CPSR register.
*/
void _disable_IRQ_interrupt_(void);

/** @fn void _disable_FIQ_interrupt_(void)
*   @brief Disable FIQ Interrupt mode in CPSR register
*
*   This function disables IRQ Interrupt mode in CPSR register.
*/
void _disable_FIQ_interrupt_(void);

/** @fn void _enable_interrupt_(void)
*   @brief Enable IRQ and FIQ Interrupt mode in CPSR register
*
*   This function Enables IRQ and FIQ Interrupt mode in CPSR register.
*   User must call this function to enable Interrupts in non-OS environments.
*/
void _enable_interrupt_(void);

/** @fn void _esmCcmErrorsClear_(void)
*   @brief Clears ESM Error caused due to CCM Errata in RevA Silicon
*
*   This function Clears ESM Error caused due to CCM Errata 
*   in RevA Silicon immediately after powerup.
*/
void _esmCcmErrorsClear_(void);

/** @fn void _errata_CORTEXR4_66_(void)
*   @brief Work Around for Errata CORTEX-R4#66
*
*   This function Disable out-of-order completion for divide 
*   instructions in Auxiliary Control register.
*/
void _errata_CORTEXR4_66_(void);

/** @fn void _errata_CORTEXR4_57_(void)
*   @brief Work Around for Errata CORTEX-R4#57
*
*   Disable out-of-order single-precision floating point  
*   multiply-accumulate instruction completion.
*/
void _errata_CORTEXR4_57_(void);

#endif
