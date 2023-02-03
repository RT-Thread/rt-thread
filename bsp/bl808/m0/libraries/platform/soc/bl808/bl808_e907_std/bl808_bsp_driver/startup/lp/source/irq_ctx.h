#ifndef __IRQ_CTX_H__
#define __IRQ_CTX_H__

/****************************************************************************
 * Included Files
 ****************************************************************************/

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* Configuration ************************************************************/

/* Processor PC */

#define REG_EPC_NDX 0

/* General pupose registers
 * $0: Zero register does not need to be saved
 * $1: ra (return address)
 */

#define REG_X1_NDX 1

/* $2: Stack POinter
 * $3: Global Pointer
 * $4: Thread Pointer
 */

#define REG_X2_NDX 2
#define REG_X3_NDX 3
#define REG_X4_NDX 4

/* $5-$7 = t0-t3: Temporary registers */

#define REG_X5_NDX 5
#define REG_X6_NDX 6
#define REG_X7_NDX 7

/* $8: s0 / fp Frame pointer */

#define REG_X8_NDX 8

/* $89 s1 Saved register */

#define REG_X9_NDX 9

/* $10-$17 = a0-a7: Argument registers */

#define REG_X10_NDX 10
#define REG_X11_NDX 11
#define REG_X12_NDX 12
#define REG_X13_NDX 13
#define REG_X14_NDX 14
#define REG_X15_NDX 15

/* Interrupt Context register */

#define REG_INT_CTX_NDX 16

#define INT_XCPT_REGS 17

#define INT_XCPT_SIZE (4 * INT_XCPT_REGS)

#define XCPTCONTEXT_REGS (INT_XCPT_REGS)

#define XCPTCONTEXT_SIZE (4 * XCPTCONTEXT_REGS)

/* In assembly language, values have to be referenced as byte address
 * offsets.  But in C, it is more convenient to reference registers as
 * register save table offsets.
 */

#ifdef __ASSEMBLY__
#define REG_EPC     (4 * REG_EPC_NDX)
#define REG_X1      (4 * REG_X1_NDX)
#define REG_X2      (4 * REG_X2_NDX)
#define REG_X3      (4 * REG_X3_NDX)
#define REG_X4      (4 * REG_X4_NDX)
#define REG_X5      (4 * REG_X5_NDX)
#define REG_X6      (4 * REG_X6_NDX)
#define REG_X7      (4 * REG_X7_NDX)
#define REG_X8      (4 * REG_X8_NDX)
#define REG_X9      (4 * REG_X9_NDX)
#define REG_X10     (4 * REG_X10_NDX)
#define REG_X11     (4 * REG_X11_NDX)
#define REG_X12     (4 * REG_X12_NDX)
#define REG_X13     (4 * REG_X13_NDX)
#define REG_X14     (4 * REG_X14_NDX)
#define REG_X15     (4 * REG_X15_NDX)
#define REG_INT_CTX (4 * REG_INT_CTX_NDX)

#else
#define REG_EPC     REG_EPC_NDX
#define REG_X1      REG_X1_NDX
#define REG_X2      REG_X2_NDX
#define REG_X3      REG_X3_NDX
#define REG_X4      REG_X4_NDX
#define REG_X5      REG_X5_NDX
#define REG_X6      REG_X6_NDX
#define REG_X7      REG_X7_NDX
#define REG_X8      REG_X8_NDX
#define REG_X9      REG_X9_NDX
#define REG_X10     REG_X10_NDX
#define REG_X11     REG_X11_NDX
#define REG_X12     REG_X12_NDX
#define REG_X13     REG_X13_NDX
#define REG_X14     REG_X14_NDX
#define REG_X15     REG_X15_NDX
#define REG_INT_CTX REG_INT_CTX_NDX

#endif

/* Now define more user friendly alternative name that can be used either
 * in assembly or C contexts.
 */

/* $1 = ra: Return address */

#define REG_RA REG_X1

/* $2 = sp:  The value of the stack pointer on return from the exception */

#define REG_SP REG_X2

/* $3 = gp: Only needs to be saved under conditions where there are
 * multiple, per-thread values for the GP.
 */

#define REG_GP REG_X3

/* $4 = tp:  Thread Pointer */

#define REG_TP REG_X4

/* $5-$7 = t0-t2: Caller saved temporary registers */

#define REG_T0 REG_X5
#define REG_T1 REG_X6
#define REG_T2 REG_X7

/* $8 = either s0 or fp:  Depends if a frame pointer is used or not */

#define REG_S0 REG_X8
#define REG_FP REG_X8

/* $9 = s1: Caller saved register */

#define REG_S1 REG_X9

/* $10-$17 = a0-a7: Argument registers */

#define REG_A0 REG_X10
#define REG_A1 REG_X11
#define REG_A2 REG_X12
#define REG_A3 REG_X13
#define REG_A4 REG_X14
#define REG_A5 REG_X15

/****************************************************************************
 * Public Types
 ****************************************************************************/

/****************************************************************************
 * Public Variables
 ****************************************************************************/

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

#endif /* __IRQ_CTX_H__ */
