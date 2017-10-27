#include "nds32_intrinsic.h"
#include "nds32.h"

#ifndef VECTOR_BASE
#define VECTOR_BASE	0x00000000
#endif

#define PSW_MSK                                         \
        (PSW_mskGIE | PSW_mskINTL | PSW_mskPOM | PSW_mskIFCON | PSW_mskCPL)
#define PSW_INIT                                        \
        (0x0UL << PSW_offGIE                            \
         | 0x0UL << PSW_offINTL                         \
         | 0x1UL << PSW_offPOM                          \
         | 0x0UL << PSW_offIFCON                        \
         | 0x7UL << PSW_offCPL)

#define IVB_MSK                                         \
        (IVB_mskEVIC | IVB_mskESZ | IVB_mskIVBASE)
#define IVB_INIT                                        \
        ((VECTOR_BASE >> IVB_offIVBASE) << IVB_offIVBASE\
         | 0x1UL << IVB_offESZ                          \
         | 0x0UL << IVB_offEVIC)


#pragma weak c_startup = c_startup_common

void c_startup(void);

/*
 * Default c_startup() function which used for those relocation from LMA to VMA.
 */
static void c_startup_common(void)
{
#ifdef XIP_MODE
	/* Data section initialization */
#define MEMCPY(des, src, n)     __builtin_memcpy ((des), (src), (n))
	extern char __rw_lma_start, __rw_lma_end, __rw_vma_start;
	unsigned int size = &__rw_lma_end - &__rw_lma_start;

	/* Copy data section from LMA to VMA */
	MEMCPY(&__rw_vma_start, &__rw_lma_start, size);
#else
	/* We do nothing for those LMA equal to VMA */
#endif
}

static void cpu_init(void)
{
	unsigned int reg;

	/* Set PSW GIE/INTL to 0, superuser & CPL to 7 */
	reg = (__nds32__mfsr(NDS32_SR_PSW) & ~PSW_MSK) | PSW_INIT;
	__nds32__mtsr(reg, NDS32_SR_PSW);
	__nds32__isb();

	/* Set vector size: 16 byte, base: VECTOR_BASE, mode: IVIC */
	reg = (__nds32__mfsr(NDS32_SR_IVB) & ~IVB_MSK) | IVB_INIT;
	__nds32__mtsr(reg, NDS32_SR_IVB);

	/*
	* Check interrupt priority programmable (IVB.PROG_PRI_LVL)
	* 0: Fixed priority, 1: Programmable priority
	*/
	if (reg & IVB_mskPROG_PRI_LVL)
	{
		/* Set PPL2FIX_EN to 0 to enable Programmable Priority Level */
		__nds32__mtsr(0x0, NDS32_SR_INT_CTRL);
	}

	/* Mask and clear hardware interrupts */
	if (reg & IVB_mskIVIC_VER)
	{
		/* IVB.IVIC_VER >= 1*/
		__nds32__mtsr(0x0, NDS32_SR_INT_MASK2);
		__nds32__mtsr(-1, NDS32_SR_INT_PEND2);
	}
	else
	{
		__nds32__mtsr(__nds32__mfsr(NDS32_SR_INT_MASK) & ~0xFFFF, NDS32_SR_INT_MASK);
	}
}

/*
 * Vectors initialization. This means to copy exception handler code to
 * vector entry base address.
 */
static void vector_init(void)
{
	extern unsigned int OS_Int_Vectors, OS_Int_Vectors_End;

	if ((unsigned int)&OS_Int_Vectors != VECTOR_BASE)
	{
		volatile unsigned int *vector_srcptr = &OS_Int_Vectors;
		volatile unsigned int *vector_dstptr = (unsigned int *)VECTOR_BASE;

		/* copy vector table to VECTOR_BASE */
		while (vector_srcptr != &OS_Int_Vectors_End)
			*vector_dstptr++ = *vector_srcptr++;
	}
}

/*
 * NDS32 reset handler to reset all devices sequentially and call application
 * entry function.
 */
void reset(void)
{
	extern void hardware_init(void);
	extern void bsp_init(void);
	extern void rtthread_startup(void);

	/*
	 * Initialize CPU to a post-reset state, ensuring the ground doesn't
	 * shift under us while we try to set things up.
	*/
	cpu_init();

	/*
	 * Initialize LMA/VMA sections.
	 * Relocation for any sections that need to be copied from LMA to VMA.
	 */
	c_startup();

	/* Copy vector table to vector base address */
	vector_init();

	/* Call platform specific hardware initialization */
	hardware_init();

	/* Setup the OS system required initialization */
	bsp_init();

	/* Application enrty function */
	rtthread_startup();

	/* Never go back here! */
	while(1);
}
