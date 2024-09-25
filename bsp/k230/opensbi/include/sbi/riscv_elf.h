#ifndef __RISCV_ELF_H__
#define __RISCV_ELF_H__

#include <sbi/riscv_asm.h>

#define R_RISCV_32		1
#define R_RISCV_64		2
#define R_RISCV_RELATIVE	3

#define RELOC_TYPE		__REG_SEL(R_RISCV_64, R_RISCV_32)
#define SYM_INDEX		__REG_SEL(0x20,	0x8)
#define SYM_SIZE		__REG_SEL(0x18,0x10)

#endif
