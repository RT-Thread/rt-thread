/*
 * Copyright : (C) 2022 Phytium Information Technology, Inc. 
 * All Rights Reserved.
 *  
 * This program is OPEN SOURCE software: you can redistribute it and/or modify it  
 * under the terms of the Phytium Public License as published by the Phytium Technology Co.,Ltd,  
 * either version 1.0 of the License, or (at your option) any later version. 
 *  
 * This program is distributed in the hope that it will be useful,but WITHOUT ANY WARRANTY;  
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the Phytium Public License for more details. 
 *  
 * 
 * FilePath: smccc-call.S
 * Date: 2022-02-10 14:53:41
 * LastEditTime: 2022-02-17 17:28:10
 * Description:  This file is for initiating SMC call
 * 
 * Modify History: 
 *  Ver   Who        Date         Changes
 * ----- ------     --------    --------------------------------------
 * 1.0   huanghe     2021/7/3     first release
 */


/*******************************************************************************
*
* FSmcCall - initiate SMC call
*
* This routine initiates SMC call which traps the processor into Monitor Mode.
* The ARM SMC Call Convetion defines that up to eight registers can be exchanged
* during an SMC call. The input parameter contains eight INT32 valeus which are
* to be passed in the SMC call; similarily the output parameter also contains
* eight INT32 values which are returned from the SMC call.
*
* \NOMANUAL
*
* RETURNS: OK
*
* void FSmcCall
*     (
*     FSmc_Data_t * input,  /@ r0 - input register values @/
*     FSmc_Data_t * output  /@ r1 - output register values @/
*     )
*/

.arm
.align 4     
.globl FSmcCall   
FSmcCall:
    STMDB   sp!, {r0-r7}        /* save clobbered registers to stack */
    ldr     r12, [sp, #(4 * 0)] /* get 1st argument (ptr to input struct) */
    ldmia   r12, {r0-r7}        /* save input argument to r0-r7 */
    smc     #0
    ldr	    r12, [sp, #(4 * 1)] /* get 2th argument (ptr to output result) */
    stmia   r12, {r0-r7}        /* get output argument from r0-r7 */
    ldmfd   sp!, {r0-r7}        /* restore clobbered registers from stack */
    bx	    lr
.size FSmcCall, .- FSmcCall
