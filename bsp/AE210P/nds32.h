#ifndef __NDS32_H__
#define __NDS32_H__

#include "nds32_defs.h"

/* Support FPU */
#if defined(__NDS32_EXT_FPU_DP__) || defined(__NDS32_EXT_FPU_SP__)
#define __TARGET_FPU_EXT
#if defined(__NDS32_EXT_FPU_CONFIG_0__)
#define FPU_REGS        8
#elif defined(__NDS32_EXT_FPU_CONFIG_1__)
#define FPU_REGS        16
#elif defined(__NDS32_EXT_FPU_CONFIG_2__)
#define FPU_REGS        32
#elif defined(__NDS32_EXT_FPU_CONFIG_3__)
#define FPU_REGS        64
#else
#error FPU register numbers no defined
#endif
#endif

/* Support IFC */
#ifdef __NDS32_EXT_IFC__
#ifndef CONFIG_NO_NDS32_EXT_IFC
#define __TARGET_IFC_EXT
#endif
#endif

/* Support ZOL */
#ifdef CONFIG_HWZOL
#define __TARGET_ZOL_EXT
#endif

#ifndef __ASSEMBLER__

#include "nds32_intrinsic.h"

#define GIE_ENABLE()                    __nds32__gie_en()
#define GIE_DISABLE()                   __nds32__gie_dis()

#ifdef CONFIG_CPU_DCACHE_ENABLE

#define NDS_DCache_Flush                nds32_dcache_flush
#define NDS_DCache_Invalidate_Flush     nds32_dcache_invalidate
#define NDS_DCache_Writeback            nds32_dcache_flush_range

#else

#define NDS_DCache_Flush()              ((void)0)
#define NDS_DCache_Invalidate_Flush()   ((void)0)
#define NDS_DCache_Writeback()          ((void)0)

#endif

static inline void GIE_SAVE(unsigned long *var)
{
	*var = __nds32__mfsr(NDS32_SR_PSW);
	GIE_DISABLE();
}

static inline void GIE_RESTORE(unsigned long var)
{
	if (var & PSW_mskGIE)
		GIE_ENABLE();
}

extern void *OS_CPU_Vector_Table[32];
typedef void (*isr_t)(int vector);

static inline void register_isr(int vector, isr_t isr, isr_t *old)
{
	if (old)
		*old = OS_CPU_Vector_Table[vector];

	OS_CPU_Vector_Table[vector] = isr;
}

#endif /* __ASSEMBLER__ */

#endif /* __NDS32_H__ */
