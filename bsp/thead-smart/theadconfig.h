#ifndef THEAD_CONFIG_H__
#define THAED_CONFIG_H__

#define ARCH_RISCV
#define ARCH_RISCV32
#if(__riscv_flen == 64)
#define ARCH_RISCV_FPU
#define ARCH_RISCV_FPU_D
#elif(__riscv_flen == 32)
#define ARCH_RISCV_FPU
#define ARCH_RISCV_FPU_S
#else
#endif
#ifdef __riscv_zp64
#define ARCH_RISCV_DSP
#endif

#ifdef __riscv_xthead
#ifdef __riscv_xtheade
#define CONFIG_THEAD_EXT_SPUSHEN
#endif
#endif

#endif
