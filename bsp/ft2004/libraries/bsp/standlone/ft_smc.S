

/*******************************************************************************
*
* FSmc_Call - initiate SMC call
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
* void FSmc_Call
*     (
*     FSmc_Data_t * input,  /@ r0 - input register values @/
*     FSmc_Data_t * output  /@ r1 - output register values @/
*     )
*/

.arm
.align 4     
.globl FSmc_Call   
FSmc_Call:
    STMDB   sp!, {r0-r7}        /* save clobbered registers to stack */
    ldr     r12, [sp, #(4 * 0)] /* get 1st argument (ptr to input struct) */
    ldmia   r12, {r0-r7}        /* save input argument to r0-r7 */
    smc     #0
    ldr	    r12, [sp, #(4 * 1)] /* get 2th argument (ptr to output result) */
    stmia   r12, {r0-r7}        /* get output argument from r0-r7 */
    ldmfd   sp!, {r0-r7}        /* restore clobbered registers from stack */
    bx	    lr
.size FSmc_Call, .- FSmc_Call
