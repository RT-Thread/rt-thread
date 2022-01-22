#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#define MSR_ME      (1<<12)     /* Machine Check Enable */
#define MSR_EE      (1<<15)     /* External Interrupt Enable */
#define MSR_CE      (1<<17)     /* Critical Interrupt Enable */

#define GPR0    0
#define GPR2    4
#define GPR3    8
#define GPR4    12
#define GPR5    16
#define GPR6    20
#define GPR7    24
#define GPR8    28
#define GPR9    32
#define GPR10   36
#define GPR11   40
#define GPR12   44
#define GPR13   48
#define GPR14   52
#define GPR15   56
#define GPR16   60
#define GPR17   64
#define GPR18   68
#define GPR19   72
#define GPR20   76
#define GPR21   80
#define GPR22   84
#define GPR23   88
#define GPR24   92
#define GPR25   96
#define GPR26   100
#define GPR27   104
#define GPR28   108
#define GPR29   112
#define GPR30   116
#define GPR31   120
#define USPRG0  (GPR31 + 4)
#define CR      (USPRG0 + 4)
#define XER     (CR + 4)
#define CTR     (XER + 4)
#define LR      (CTR + 4)
#define SRR0    (LR + 4)
#define SRR1    (SRR0 + 4)
#define STACK_FRAME_SIZE (SRR1 + 4)

#endif
